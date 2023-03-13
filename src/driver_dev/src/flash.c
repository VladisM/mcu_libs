#include "flash.h"

#include "driver_dev_debug.h"

#include <string.h>
#include <stdlib.h>

#define NORD_OPCODE 0x03U
#define RDSR_OPCODE 0x05U
#define CER_OPCODE 0xC7U
#define SER_OPCODE 0xD7U
#define PP_OPCODE 0x02U
#define WREN_OPCODE 0x06U

#define SR_SRWD (1 << 7)
#define SR_QE   (1 << 6)
#define SR_BP3  (1 << 5)
#define SR_BP2  (1 << 4)
#define SR_BP1  (1 << 3)
#define SR_BP0  (1 << 2)
#define SR_WEL  (1 << 1)
#define SR_WIP  (1 << 0)

#define PAGE_SIZE 256

//TODO: better error handling

static inline qspi_length_t translate_length(flash_driver_t *flash, unsigned length){
    switch(length){
        case 1: return LENGTH_ONE_B;
        case 2: return LENGTH_TWO_B;
        case 3: return LENGTH_THREE_B;
        case 4: return LENGTH_FOUR_B;
        default:
            DRIVER_DEV_DEBUG_ERROR("FLASH '%s'. %s", flash->flash_name, "Using wrong length of transfer.");
            return 0;
    }
}

static qspi_length_t get_length(flash_driver_t *flash){
    return translate_length(flash, flash->config.address_bytes_count);
}

static void NORD(flash_driver_t *flash, uint32_t address, uint8_t *data, uint32_t count){
    qspi_driver_set_instruction(flash->bus.qspi, NORD_OPCODE, MODE_SINGLE);
    qspi_driver_set_address(flash->bus.qspi, address, get_length(flash), MODE_SINGLE);
    qspi_driver_set_alternate(flash->bus.qspi, 0, LENGTH_ONE_B, MODE_SKIP);
    qspi_driver_set_dummy(flash->bus.qspi, 0);
    qspi_driver_set_data(flash->bus.qspi, count, data, MODE_SINGLE);

    qspi_driver_set_operation(flash->bus.qspi, OPERATION_READ);

    qspi_driver_trigger(flash->bus.qspi);
}

static void SER(flash_driver_t *flash, uint32_t address){
    qspi_driver_set_instruction(flash->bus.qspi, SER_OPCODE, MODE_SINGLE);
    qspi_driver_set_address(flash->bus.qspi, address, get_length(flash), MODE_SINGLE);
    qspi_driver_set_alternate(flash->bus.qspi, 0, LENGTH_ONE_B, MODE_SKIP);
    qspi_driver_set_dummy(flash->bus.qspi, 0);
    qspi_driver_set_data(flash->bus.qspi, 0, NULL, MODE_SKIP);

    qspi_driver_set_operation(flash->bus.qspi, OPERATION_WRITE);

    qspi_driver_trigger(flash->bus.qspi);
}

static uint8_t RDSR(flash_driver_t *flash){
    uint8_t data_in = 0;

    qspi_driver_set_instruction(flash->bus.qspi, RDSR_OPCODE, MODE_SINGLE);
    qspi_driver_set_address(flash->bus.qspi, 0, LENGTH_ONE_B, MODE_SKIP);
    qspi_driver_set_alternate(flash->bus.qspi, 0, LENGTH_ONE_B, MODE_SKIP);
    qspi_driver_set_dummy(flash->bus.qspi, 0);
    qspi_driver_set_data(flash->bus.qspi, 1, &data_in, MODE_SINGLE);

    qspi_driver_set_operation(flash->bus.qspi, OPERATION_READ);

    qspi_driver_trigger(flash->bus.qspi);

    return data_in;
}

static void CER(flash_driver_t *flash){
    qspi_driver_set_instruction(flash->bus.qspi, CER_OPCODE, MODE_SINGLE);
    qspi_driver_set_address(flash->bus.qspi, 0, LENGTH_ONE_B, MODE_SKIP);
    qspi_driver_set_alternate(flash->bus.qspi, 0, LENGTH_ONE_B, MODE_SKIP);
    qspi_driver_set_dummy(flash->bus.qspi, 0);
    qspi_driver_set_data(flash->bus.qspi, 0, NULL, MODE_SKIP);

    qspi_driver_set_operation(flash->bus.qspi, OPERATION_WRITE);

    qspi_driver_trigger(flash->bus.qspi);
}

static void PP(flash_driver_t *flash, uint32_t address, uint8_t *data){
    qspi_driver_set_instruction(flash->bus.qspi, PP_OPCODE, MODE_SINGLE);
    qspi_driver_set_address(flash->bus.qspi, address, get_length(flash), MODE_SINGLE);
    qspi_driver_set_alternate(flash->bus.qspi, 0, LENGTH_ONE_B, MODE_SKIP);
    qspi_driver_set_dummy(flash->bus.qspi, 0);
    qspi_driver_set_data(flash->bus.qspi, PAGE_SIZE, data, MODE_SINGLE);

    qspi_driver_set_operation(flash->bus.qspi, OPERATION_WRITE);

    qspi_driver_trigger(flash->bus.qspi);
}

static void WREN(flash_driver_t *flash){
    qspi_driver_set_instruction(flash->bus.qspi, WREN_OPCODE, MODE_SINGLE);
    qspi_driver_set_address(flash->bus.qspi, 0, LENGTH_ONE_B, MODE_SKIP);
    qspi_driver_set_alternate(flash->bus.qspi, 0, LENGTH_ONE_B, MODE_SKIP);
    qspi_driver_set_dummy(flash->bus.qspi, 0);
    qspi_driver_set_data(flash->bus.qspi, 0, NULL, MODE_SKIP);

    qspi_driver_set_operation(flash->bus.qspi, OPERATION_WRITE);

    qspi_driver_trigger(flash->bus.qspi);
}

static bool _check_enabled(flash_driver_t *flash){
    if(flash->enabled == false){
        DRIVER_DEV_DEBUG_ERROR("FLASH '%s'. %s", flash->flash_name, "Accessing but not configured.");
        return false;
    }

    return true;
}

static bool _check_valid_range(flash_driver_t *flash, uint32_t address){
    if(flash->config.memory_size < address){
        DRIVER_DEV_DEBUG_ERROR("FLASH '%s'. %s", flash->flash_name, "Address out of range.");
        return false;
    }

    return true;
}

static bool _check_valid_sector(flash_driver_t *flash, unsigned sector){
    if(flash->config.memory_size < sector * flash->config.sector_size){
        DRIVER_DEV_DEBUG_ERROR("FLASH '%s'. %s", flash->flash_name, "Sector out of range.");
        return false;
    }

    return true;
}

void flash_driver_init(flash_driver_t **flash, qspi_driver_t *qspi){
    flash_driver_t *tmp = (flash_driver_t *)malloc(sizeof(flash_driver_t));

    if(tmp == NULL){
        DRIVER_DEV_DEBUG_ERROR("%s", "Malloc failed!");
        *flash = NULL;
        return;
    }

    memset(tmp, 0, sizeof(flash_driver_t));

    tmp->bus.qspi = qspi;
    tmp->enabled = false;

    #ifndef NDEBUG
    tmp->flash_name = "N/A";
    #endif

    *flash = tmp;
}

void flash_driver_config(flash_driver_t *flash, uint32_t flash_size, uint32_t sector_size, unsigned address_bytes_count){
    flash->config.sector_size = sector_size;
    flash->config.memory_size = flash_size;
    flash->config.address_bytes_count = address_bytes_count;
    flash->enabled = true;
}

uint8_t flash_driver_read_byte(flash_driver_t *flash, uint32_t address){
    if(!_check_enabled(flash)) return 0;
    if(!_check_valid_range(flash, address)) return 0;

    uint8_t tmp = 0;
    NORD(flash, address, &tmp, 1);
    return tmp;
}

void flash_driver_write_sector(flash_driver_t *flash, unsigned sector, uint8_t *data){
    if(!_check_enabled(flash)) return;
    if(!_check_valid_sector(flash, sector)) return;

    for(uint32_t i = 0; i < (flash->config.sector_size / PAGE_SIZE); i++){
        uint32_t page_address = (sector * flash->config.sector_size) + (i * PAGE_SIZE);

        WREN(flash);
        PP(flash, page_address, data + (i * PAGE_SIZE));
        while((RDSR(flash) & SR_WIP) == SR_WIP);    //wait till write isn't complete
    }
}

void flash_driver_read_sector(flash_driver_t *flash, unsigned sector, uint8_t *data){
    if(!_check_enabled(flash)) return;
    if(!_check_valid_sector(flash, sector)) return;

    NORD(flash, sector * flash->config.sector_size, data, flash->config.sector_size);
}

void flash_driver_mass_erase(flash_driver_t *flash){
    if(!_check_enabled(flash)) return;

    WREN(flash);
    CER(flash);
    while((RDSR(flash) & SR_WIP) == SR_WIP);    //wait till erase isn't complete
}

void flash_driver_sector_erase(flash_driver_t *flash, unsigned sector){
    if(!_check_enabled(flash)) return;
    if(!_check_valid_sector(flash, sector)) return;

    WREN(flash);
    SER(flash, sector * flash->config.sector_size);
    while((RDSR(flash) & SR_WIP) == SR_WIP);    //wait till erase isn't complete
}

uint32_t flash_driver_get_size(flash_driver_t *flash){
    return flash->config.memory_size;
}

uint32_t flash_driver_get_sector_size(flash_driver_t *flash){
    return flash->config.sector_size;
}

uint32_t flash_driver_get_sector_count(flash_driver_t *flash){
    return flash->config.memory_size / flash->config.sector_size;
}


#ifndef NDEBUG
void flash_driver_set_name(flash_driver_t *flash, const char *flash_name){
    flash->flash_name = flash_name;
}
#endif
