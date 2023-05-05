#include "i2c.h"

#include <stm32.h>

#include "driver_mcu_debug.h"
#include "clock.h"
#include "common.h"

#include <string.h>
#include <stdlib.h>

//TODO: implement FM mode in addition to SM mode
//TODO: more agile communication freq settings

//TODO: make sure this function is implemented correctly, probably should check for ongoing transmissions
static void _apply_timing_conf(i2c_driver_t *i2c){
    I2C_TypeDef *_device = i2c->device.device;

    if(i2c->device.peripheral_clock < 2000000){
        DRIVER_MCU_DEBUG_ERROR("I2C peripheral '%s' freq is too low! %iHz < 2000000Hz!", i2c->i2c_name, i2c->device.peripheral_clock);
    }

    uint32_t fpclk = i2c->device.peripheral_clock / 1000000;    //now we are using implicit 10^{-6}

    //set frequency peripheral is using
    _device->CR2 &= ~(I2C_CR2_FREQ_Msk);
    _device->CR2 |= (fpclk << I2C_CR2_FREQ_Pos);

    //set sm 100khz
    _device->CCR &= ~(I2C_CCR_CCR_Msk | I2C_CCR_FS_Msk | I2C_CCR_DUTY_Msk);
    _device->CCR |= ((fpclk * 5) << I2C_CCR_CCR_Pos); //5 is magic number to get 100kHz SCL, see RM0390 page 791

    //set trise
    _device->TRISE &= ~(I2C_TRISE_TRISE_Msk);
    _device->TRISE |= ((fpclk + 1) << I2C_TRISE_TRISE_Pos); //for 100kHz SCL formula become 10^{-6} * F_{pclk} + 1, see RM0390 page 792
}

static void _enable_peripheral(i2c_driver_t *i2c){
    I2C_TypeDef *_device = i2c->device.device;
    _device->CR1 |= I2C_CR1_PE;
}

void i2c_driver_init(i2c_driver_t **i2c, void *device, gpio_driver_t *sda, gpio_driver_t *scl){
    i2c_driver_t *tmp = (i2c_driver_t *)malloc(sizeof(i2c_driver_t));

    if(tmp == NULL){
        DRIVER_MCU_DEBUG_ERROR("%s", "Malloc failed!");
        *i2c = NULL;
        return;
    }

    memset(tmp, 0, sizeof(i2c_driver_t));

    tmp->device.device = device;
    tmp->device.peripheral_clock = clock_get_peripheral_clock(device);
    tmp->gpio.scl = scl;
    tmp->gpio.sda = sda;
    tmp->i2c_name = default_driver_mcu_name;

    clock_enable_peripheral_clock(device);

    _apply_timing_conf(tmp);
    _enable_peripheral(tmp);

    *i2c = tmp;
}

void i2c_driver_write_byte(i2c_driver_t *i2c, uint8_t address, uint8_t byte){
    i2c_driver_write_buffer(i2c, address, 1, &byte);
}

void i2c_driver_write_buffer(i2c_driver_t *i2c, uint8_t address, unsigned len, uint8_t *buff){
    I2C_TypeDef *_device = i2c->device.device;

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    volatile uint32_t tmp = 0;
    #pragma GCC diagnostic pop

    _device->CR1 |= I2C_CR1_START;

    //wait for start to be generated
    while((_device->SR1 & I2C_SR1_SB) != I2C_SR1_SB) __NOP();

    //send address
    _device->DR = (address << 1);

    //wait for address to be sent
    while((_device->SR1 & I2C_SR1_ADDR) != I2C_SR1_ADDR) __NOP();

    //this will clear status register
    tmp = _device->SR1;
    tmp = _device->SR2;

    for(unsigned i = 0; i < len; i++){
        //put data for sending
        _device->DR = buff[i];

        //wait again to complete sending
        while((_device->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE) __NOP();
    }

    //generate stop
    _device->CR1 |= I2C_CR1_STOP;
}

uint8_t i2c_driver_read_byte(i2c_driver_t *i2c, uint8_t address){
    uint8_t tmp = 0;
    i2c_driver_read_buffer(i2c, address, 1, &tmp);
    return tmp;
}

void i2c_driver_read_buffer(i2c_driver_t *i2c, uint8_t address, unsigned len, uint8_t *buff){
    I2C_TypeDef *_device = i2c->device.device;

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    volatile uint32_t tmp = 0;
    #pragma GCC diagnostic pop

    _device->CR1 |= I2C_CR1_START | I2C_CR1_ACK;

    //wait for start to be generated
    while((_device->SR1 & I2C_SR1_SB) != I2C_SR1_SB) __NOP();

    //send address
    _device->DR = ((address << 1) | 0x01);

    if(len == 1){
        //clear ack flag
        _device->CR1 &= ~(I2C_CR1_ACK);
    }

    //wait for address to be sent
    while((_device->SR1 & I2C_SR1_ADDR) != I2C_SR1_ADDR) __NOP();

    //this will clear status register
    tmp = _device->SR1;
    tmp = _device->SR2;

    for(unsigned i = 0; i < len; i++){
        if(i == len - 2){   //N-2
            while((_device->SR1 & I2C_SR1_BTF) != I2C_SR1_BTF) __NOP();
            _device->CR1 &= ~(I2C_CR1_ACK);
        }
        else if(i == len - 1){  //N-1

            if(len == 1)
                while((_device->SR1 & I2C_SR1_RXNE) != I2C_SR1_RXNE) __NOP();
            else
                while((_device->SR1 & I2C_SR1_BTF) != I2C_SR1_BTF) __NOP();

            _device->CR1 |= I2C_CR1_STOP;
        }
        else{
            while((_device->SR1 & I2C_SR1_RXNE) != I2C_SR1_RXNE) __NOP();
        }
        buff[i] = _device->DR;
    }
}

//TODO: test this function
void i2c_driver_reconfigure_clock(i2c_driver_t *i2c){
    i2c->device.peripheral_clock = clock_get_peripheral_clock(i2c->device.device);
    _apply_timing_conf(i2c);
}

void i2c_driver_set_name(i2c_driver_t *i2c, const char *i2c_name){
    i2c->i2c_name = i2c_name;
}
