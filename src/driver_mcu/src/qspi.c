#include "qspi.h"

#include <stm32.h>

#include "driver_mcu_debug.h"
#include "clock.h"
#include "common.h"

#include <string.h>
#include <stdlib.h>

//TODO: implement direct mode
//TODO: implement support for dual flash
//TODO: make sure indirect mode work

#ifdef DRIVER_MCU_DEBUG_ENABLED
static const char *qspi_error_reconfigure_bus_clock = "Cannot reconfigure bus clock!";
static const char *qspi_error_reconfigure_per_clock = "Cannot reconfigure peripheral clock!";
static const char *qspi_error_peri_not_high_enough = "Peripheral clock is not high enough.";
static const char *qspi_error_peri_not_integer_mul = "Bus clock is not integer multiply of peripheral clock.";
static const char *qspi_error_init = "Cannot initialize qspi peripheral!";
#endif

static bool _apply_timing_conf(qspi_driver_t *qspi, uint32_t prescaler){
    QUADSPI_TypeDef *_device = qspi->device.device;

    if(prescaler == 0){
        DRIVER_MCU_DEBUG_ERROR("QUADSPI %s trying to set invalid prescaler (%d)!", qspi->qspi_name, prescaler);
        return false;
    }

    _device->CR &= ~(QUADSPI_CR_PRESCALER_Msk);
    _device->CR |= (((prescaler - 1) << QUADSPI_CR_PRESCALER_Pos) & QUADSPI_CR_PRESCALER_Msk);

    return true;
}

static void _enable_peripheral(qspi_driver_t *qspi){
    QUADSPI_TypeDef *_device = qspi->device.device;

    _device->CR |= QUADSPI_CR_EN;
}

static void _qspi_clear(qspi_driver_t *qspi){
    QUADSPI_TypeDef *_device = qspi->device.device;

    _device->CR = 0x00000000UL;
    _device->DCR = 0x00000000UL;
    _device->FCR = 0x00000000UL;
    _device->DLR = 0x00000000UL;
    _device->CCR = 0x00000000UL;
    _device->AR = 0x00000000UL;
    _device->ABR = 0x00000000UL;
    _device->DR = 0x00000000UL;
    _device->PSMKR = 0x00000000UL;
    _device->PSMAR = 0x00000000UL;
    _device->PIR = 0x00000000UL;
    _device->LPTR = 0x00000000UL;
}

void qspi_driver_init(qspi_driver_t **qspi, void *device, uint32_t bus_clock, gpio_driver_t *io0, gpio_driver_t *io1, gpio_driver_t *io2, gpio_driver_t *io3, gpio_driver_t *sck, gpio_driver_t *ncs){
    DRIVER_MCU_DEBUG_INFO("Initializing QSPI peripheral.");

    uint32_t peripheral_clock = clock_get_peripheral_clock(device);

    if(peripheral_clock < bus_clock){
        DRIVER_MCU_DEBUG_ERROR("%s %s F_{bus} = %d, F_{per} = %d", qspi_error_init, qspi_error_peri_not_high_enough, bus_clock, peripheral_clock);
        *qspi = NULL;
        return;
    }

    if((peripheral_clock % bus_clock) != 0){
        DRIVER_MCU_DEBUG_ERROR("%s %s F_{bus} = %d, F_{per} = %d", qspi_error_init, qspi_error_peri_not_integer_mul, bus_clock, peripheral_clock);
        *qspi = NULL;
        return;
    }

    qspi_driver_t *tmp = (qspi_driver_t *)malloc(sizeof(qspi_driver_t));

    if(tmp == NULL){
        DRIVER_MCU_DEBUG_ERROR("%s", "Malloc failed!");
        *qspi = NULL;
        return;
    }

    memset(tmp, 0, sizeof(qspi_driver_t));

    tmp->device.device = device;
    tmp->device.peripheral_clock = peripheral_clock;

    tmp->gpio.io0 = io0;
    tmp->gpio.io1 = io1;
    tmp->gpio.io2 = io2;
    tmp->gpio.io3 = io3;
    tmp->gpio.sck = sck;
    tmp->gpio.ncs = ncs;

    tmp->qspi_name = default_driver_mcu_name;

    clock_enable_peripheral_clock(device);

    _qspi_clear(tmp);

    if(!_apply_timing_conf(tmp, peripheral_clock / bus_clock)){
        clock_disable_peripheral_clock(device);
        free(tmp);
        *qspi = NULL;
        return;
    }

    _enable_peripheral(tmp);

    *qspi = tmp;
}

static void qspi_indirect_config(qspi_driver_t *qspi){

    //operation config
    uint32_t operation_config = 0;

    switch(qspi->operation_config.operation){
        case OPERATION_WRITE:                                               break;
        case OPERATION_READ:    operation_config |= QUADSPI_CCR_FMODE_0;    break;
    }

    qspi->tmp_config.CCR &= ~(QUADSPI_CCR_FMODE_Msk);
    qspi->tmp_config.CCR |= operation_config;

    //instruction config
    uint32_t instruction_config = 0;

    instruction_config = ((qspi->operation_config.instruction.instruction << QUADSPI_CCR_INSTRUCTION_Pos) & QUADSPI_CCR_INSTRUCTION_Msk);

    switch(qspi->operation_config.instruction.mode){
        case MODE_SKIP:                                                                         break;
        case MODE_SINGLE:   instruction_config |= QUADSPI_CCR_IMODE_0;                          break;
        case MODE_DUAL:     instruction_config |= QUADSPI_CCR_IMODE_1;                          break;
        case MODE_QUAD:     instruction_config |= QUADSPI_CCR_IMODE_0 | QUADSPI_CCR_IMODE_1;    break;
    }

    qspi->tmp_config.CCR &= ~(QUADSPI_CCR_IMODE_Msk | QUADSPI_CCR_INSTRUCTION_Msk);
    qspi->tmp_config.CCR |= instruction_config;

    //address config
    uint32_t address_config = 0;

    switch(qspi->operation_config.address.mode){
        case MODE_SKIP:                                                                       break;
        case MODE_SINGLE:   address_config |= QUADSPI_CCR_ADMODE_0;                           break;
        case MODE_DUAL:     address_config |= QUADSPI_CCR_ADMODE_1;                           break;
        case MODE_QUAD:     address_config |= QUADSPI_CCR_ADMODE_0 | QUADSPI_CCR_ADMODE_1;    break;
    }

    switch(qspi->operation_config.address.length){
        case LENGTH_ONE_B:                                                                        break;
        case LENGTH_TWO_B:      address_config |= QUADSPI_CCR_ADSIZE_0;                           break;
        case LENGTH_THREE_B:    address_config |= QUADSPI_CCR_ADSIZE_1;                           break;
        case LENGTH_FOUR_B:     address_config |= QUADSPI_CCR_ADSIZE_0 | QUADSPI_CCR_ADSIZE_1;    break;
    }

    qspi->tmp_config.CCR &= ~(QUADSPI_CCR_ADMODE_Msk | QUADSPI_CCR_ADSIZE_Msk);
    qspi->tmp_config.CCR |= address_config;

    qspi->tmp_config.AR = qspi->operation_config.address.address;

    //alternate config
    uint32_t alternate_config = 0;

    switch(qspi->operation_config.alternate.mode){
        case MODE_SKIP:                                                                         break;
        case MODE_SINGLE:   alternate_config |= QUADSPI_CCR_ABMODE_0;                           break;
        case MODE_DUAL:     alternate_config |= QUADSPI_CCR_ABMODE_1;                           break;
        case MODE_QUAD:     alternate_config |= QUADSPI_CCR_ABMODE_0 | QUADSPI_CCR_ABMODE_1;    break;
    }

    switch(qspi->operation_config.alternate.length){
        case LENGTH_ONE_B:                                                                          break;
        case LENGTH_TWO_B:      alternate_config |= QUADSPI_CCR_ABSIZE_0;                           break;
        case LENGTH_THREE_B:    alternate_config |= QUADSPI_CCR_ABSIZE_1;                           break;
        case LENGTH_FOUR_B:     alternate_config |= QUADSPI_CCR_ABSIZE_0 | QUADSPI_CCR_ABSIZE_1;    break;
    }

    qspi->tmp_config.CCR &= ~(QUADSPI_CCR_ABMODE_Msk | QUADSPI_CCR_ABSIZE_Msk);
    qspi->tmp_config.CCR |= alternate_config;

    qspi->tmp_config.ABR = qspi->operation_config.alternate.alternate;

    //dummy cycles
    uint32_t dummy_config = 0;

    dummy_config = ((qspi->operation_config.dummy.cycles << QUADSPI_CCR_DCYC_Pos) & QUADSPI_CCR_DCYC_Msk);

    qspi->tmp_config.CCR &= ~(QUADSPI_CCR_DCYC);
    qspi->tmp_config.CCR |= dummy_config;

    //data config
    uint32_t data_config = 0;

    switch(qspi->operation_config.data.mode){
        case MODE_SKIP:                                                                     break;
        case MODE_SINGLE:   data_config |= QUADSPI_CCR_DMODE_0;                             break;
        case MODE_DUAL:     data_config |= QUADSPI_CCR_DMODE_1;                             break;
        case MODE_QUAD:     data_config |= QUADSPI_CCR_DMODE_0 | QUADSPI_CCR_DMODE_1;       break;
    }

    qspi->tmp_config.CCR &= ~(QUADSPI_CCR_DMODE_Msk);
    qspi->tmp_config.CCR |= data_config;

    if(qspi->operation_config.data.count != 0){
        qspi->tmp_config.DLR = qspi->operation_config.data.count - 1;
    }
    else{
        qspi->tmp_config.DLR = 0;
    }
}

static inline bool is_fifo_full(QUADSPI_TypeDef *_device){
    if(((_device->SR & QUADSPI_SR_FLEVEL_Msk) >> QUADSPI_SR_FLEVEL_Pos) < 32) return false;
    else return true;
}

static inline bool is_fifo_empty(QUADSPI_TypeDef *_device){
    if(((_device->SR & QUADSPI_SR_FLEVEL_Msk) >> QUADSPI_SR_FLEVEL_Pos) == 0) return true;
    else return false;
}

static inline bool is_busy(QUADSPI_TypeDef *_device){
    if((_device->SR & QUADSPI_SR_BUSY) == QUADSPI_SR_BUSY) return true;
    else return false;
}

#ifdef DRIVER_MCU_DEBUG_ENABLED
static inline void print_command_config(qspi_driver_t *qspi){
    uint32_t cmd = ((qspi->tmp_config.CCR & QUADSPI_CCR_INSTRUCTION_Msk) >> QUADSPI_CCR_INSTRUCTION_Pos);
    uint32_t adr = qspi->tmp_config.AR;
    uint32_t data_byte = qspi->tmp_config.DLR + 1;

    char *rw = ((qspi->tmp_config.CCR & QUADSPI_CCR_FMODE_Msk) == QUADSPI_CCR_FMODE_0) ? "read" : "write";

    if((qspi->tmp_config.CCR & QUADSPI_CCR_ADMODE_Msk) != 0){
        DRIVER_MCU_DEBUG_INFO("%s running command: 0x%X as %s request of %d bytes to address 0x%X", qspi->qspi_name, cmd, rw, data_byte, adr);
    }
    else{
        DRIVER_MCU_DEBUG_INFO("%s running command: 0x%X as %s request of %d bytes without address", qspi->qspi_name, cmd, rw, data_byte);
    }
}
#endif

void qspi_driver_trigger(qspi_driver_t *qspi){
    QUADSPI_TypeDef *_device = qspi->device.device;

    qspi_indirect_config(qspi);

    #ifdef DRIVER_MCU_DEBUG_ENABLED
    print_command_config(qspi);
    #endif

    while(is_busy(_device)) __NOP();

    if(qspi->operation_config.operation == OPERATION_READ){
        _device->ABR = qspi->tmp_config.ABR;
        _device->DLR = qspi->tmp_config.DLR;

        if(qspi->operation_config.address.mode != MODE_SKIP){
            _device->CCR = qspi->tmp_config.CCR;
            _device->AR = qspi->tmp_config.AR;
        }
        else{
            _device->CCR = qspi->tmp_config.CCR;
        }

        for(uint32_t i = 0; i < qspi->operation_config.data.count; i++){
            while(is_fifo_empty(_device))
                __NOP();

            //to ensure DR will be accessed by 1byte read instruction
            volatile uint8_t *ptr = (uint8_t *)(&_device->DR);

            qspi->operation_config.data.buffer[i] = *ptr;
        }

        while(is_busy(_device)) __NOP();

        _device->FCR |= QUADSPI_FCR_CTCF;
    }

    else if(qspi->operation_config.operation == OPERATION_WRITE){
        _device->ABR = qspi->tmp_config.ABR;
        _device->DLR = qspi->tmp_config.DLR;

        _device->CCR = qspi->tmp_config.CCR;
        _device->AR = qspi->tmp_config.AR;

        for(uint32_t i = 0; i < qspi->operation_config.data.count; i++){
            while(is_fifo_full(_device))
                __NOP();

            //to ensure DR will be accessed by 1byte write instruction
            volatile uint8_t *ptr = (uint8_t *)(&_device->DR);

            *ptr = qspi->operation_config.data.buffer[i];
        }

        while(is_busy(_device)) __NOP();

        _device->FCR |= QUADSPI_FCR_CTCF;
    }
}

void qspi_driver_set_spimode(qspi_driver_t *qspi, qspi_spi_operation_t mode){
    QUADSPI_TypeDef *_device = qspi->device.device;

    _device->DCR &= ~(QUADSPI_DCR_CKMODE_Msk);

    if(mode == SPI_MODE_3){
        _device->DCR |= QUADSPI_DCR_CKMODE;
    }
}

void qspi_driver_set_csht(qspi_driver_t *qspi, int csht){
    QUADSPI_TypeDef *_device = qspi->device.device;

    _device->DCR &= ~(QUADSPI_DCR_CSHT_Msk);
    _device->DCR |= ((csht << QUADSPI_DCR_CSHT_Pos) & QUADSPI_DCR_CSHT_Msk);
}

void qspi_driver_set_fsize(qspi_driver_t *qspi, int fsize){
    QUADSPI_TypeDef *_device = qspi->device.device;

    _device->DCR &= ~(QUADSPI_DCR_FSIZE_Msk);
    _device->DCR |= ((fsize << QUADSPI_DCR_FSIZE_Pos) & QUADSPI_DCR_FSIZE_Msk);
}

void qspi_driver_set_instruction(qspi_driver_t *qspi, uint8_t instruction, qspi_mode_t mode){
    qspi->operation_config.instruction.instruction = instruction;
    qspi->operation_config.instruction.mode = mode;
}

void qspi_driver_set_address(qspi_driver_t *qspi, uint32_t address, qspi_length_t length, qspi_mode_t mode){
    qspi->operation_config.address.address = address;
    qspi->operation_config.address.length = length;
    qspi->operation_config.address.mode = mode;
}

void qspi_driver_set_alternate(qspi_driver_t *qspi, uint32_t alternate, qspi_length_t length, qspi_mode_t mode){
    qspi->operation_config.alternate.alternate = alternate;
    qspi->operation_config.alternate.length = length;
    qspi->operation_config.alternate.mode = mode;
}

void qspi_driver_set_dummy(qspi_driver_t *qspi, uint8_t cycles){
    qspi->operation_config.dummy.cycles = cycles;
}

void qspi_driver_set_data(qspi_driver_t *qspi, uint32_t count, uint8_t *buffer, qspi_mode_t mode){
    qspi->operation_config.data.buffer = buffer;
    qspi->operation_config.data.count = count;
    qspi->operation_config.data.mode = mode;
}

void qspi_driver_set_operation(qspi_driver_t *qspi, qspi_operation_t operation){
    qspi->operation_config.operation = operation;
}

uint32_t qspi_driver_get_bus_clock(qspi_driver_t *qspi){
    QUADSPI_TypeDef *_device = qspi->device.device;
    uint32_t div = ((_device->CR & QUADSPI_CR_PRESCALER) >> QUADSPI_CR_PRESCALER_Pos) + 1;
    return qspi->device.peripheral_clock / div;
}

bool qspi_driver_reconfigure_bus_clock(qspi_driver_t *qspi, uint32_t bus_clock){
    uint32_t peripheral_clock = clock_get_peripheral_clock(qspi->device.device);

    if(peripheral_clock < bus_clock){
        DRIVER_MCU_DEBUG_ERROR("%s (%s) %s F_{bus} = %d, F_{per} = %d", qspi_error_reconfigure_bus_clock, qspi->qspi_name, qspi_error_peri_not_high_enough, bus_clock, peripheral_clock);
        return false;
    }

    if((peripheral_clock % bus_clock) != 0){
        DRIVER_MCU_DEBUG_ERROR("%s (%s) %s F_{bus} = %d, F_{per} = %d", qspi_error_reconfigure_bus_clock, qspi->qspi_name, qspi_error_peri_not_integer_mul, bus_clock, peripheral_clock);
        return false;
    }

    return _apply_timing_conf(qspi, peripheral_clock / bus_clock);
}

bool qspi_driver_reconfigure_peripheral_clock(qspi_driver_t *qspi){
    uint32_t actual_bus_clock = qspi_driver_get_bus_clock(qspi);
    uint32_t new_peripheral_clock = clock_get_peripheral_clock(qspi->device.device);

    if(new_peripheral_clock > actual_bus_clock){
        DRIVER_MCU_DEBUG_ERROR("%s (%s) %s F_{bus} = %d, F_{per} = %d", qspi_error_reconfigure_per_clock, qspi->device, qspi_error_peri_not_high_enough, actual_bus_clock, new_peripheral_clock);
        return false;
    }

    if((new_peripheral_clock % actual_bus_clock) != 0){
        DRIVER_MCU_DEBUG_ERROR("%s (%s) %s F_{bus} = %d, F_{per} = %d", qspi_error_reconfigure_per_clock, qspi->qspi_name, qspi_error_peri_not_integer_mul, actual_bus_clock, new_peripheral_clock);
        return false;
    }

    if(!_apply_timing_conf(qspi, (new_peripheral_clock / actual_bus_clock))){
        return false;
    }

    qspi->device.peripheral_clock = clock_get_peripheral_clock(qspi->device.device);

    return true;
}

void qspi_driver_set_name(qspi_driver_t *qspi, const char *qspi_name){
    qspi->qspi_name = qspi_name;
}
