#include "uart.h"

#include <stm32.h>

#include "driver_mcu_debug.h"
#include "clock.h"

#include <string.h>
#include <stdlib.h>

//TODO: implement another profiles such as halfduplex, flow control, stop bits, data length, synchronous mode...

static void _apply_timing_conf(uart_driver_t *uart){
    USART_TypeDef *_device = uart->device.device;

    //TODO: check when BRR can be modified and ensure proper state whenever this is called! (especially important as baudrate can be reconfigured on the fly)
    _device->BRR = uart->device.peripheral_clock / uart->config.baudrate;
}

static void _enable_peripheral(uart_driver_t *uart){
    USART_TypeDef *_device = uart->device.device;

    _device->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void uart_driver_init(uart_driver_t **uart, void *device, gpio_driver_t *rx, gpio_driver_t*tx, uint32_t baudrate){

    uart_driver_t *tmp = (uart_driver_t *)malloc(sizeof(uart_driver_t));

    if(tmp == NULL){
        DRIVER_MCU_DEBUG_ERROR("%s", "Malloc failed!");
        *uart = NULL;
        return;
    }

    memset(tmp, 0, sizeof(uart_driver_t));

    tmp->config.baudrate = baudrate;
    tmp->device.device = device;
    tmp->device.peripheral_clock = clock_get_peripheral_clock(device);
    tmp->gpio.rx = rx;
    tmp->gpio.tx = tx;

    #ifndef NDEBUG
    tmp->uart_name = "N/A";
    #endif

    clock_enable_peripheral_clock(device);

    _apply_timing_conf(tmp);
    _enable_peripheral(tmp);

    *uart = tmp;
}

void uart_driver_write(uart_driver_t *uart, uint32_t len, uint8_t *data){
    for(uint32_t i = 0; i < len; i++){
        uart_driver_putc(uart, data[i]);
    }
}

void uart_driver_putc(uart_driver_t *uart, char c){
    USART_TypeDef *_device = uart->device.device;

    while((_device->SR & USART_SR_TXE) == 0) __NOP();

    _device->DR = c;

    while((_device->SR & USART_SR_TXE) == 0) __NOP();
}

void uart_driver_puts(uart_driver_t *uart, char *s){
    for(int i = 0; s[i] != '\0'; i++){
        uart_driver_putc(uart, s[i]);
    }
}

void uart_driver_reconfigure_clock(uart_driver_t *uart){
    uart->device.peripheral_clock = clock_get_peripheral_clock(uart->device.device);
    _apply_timing_conf(uart);
}

void uart_driver_reconfigure_baudrate(uart_driver_t *uart, uint32_t baudrate){
    uart->config.baudrate = baudrate;
    _apply_timing_conf(uart);
}

#ifndef NDEBUG
void uart_driver_set_name(uart_driver_t *uart, const char *uart_name){
    uart->uart_name = uart_name;
}
#endif
