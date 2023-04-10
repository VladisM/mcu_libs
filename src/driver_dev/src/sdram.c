#include "sdram.h"

#include "driver_dev_debug.h"

#include <string.h>
#include <stdlib.h>

void sdram_driver_init(sdram_driver_t **sdram, fmc_driver_t *fmc){
    sdram_driver_t *tmp = (sdram_driver_t *)malloc(sizeof(sdram_driver_t));

    if(tmp == NULL){
        DRIVER_DEV_DEBUG_ERROR("%s", "Malloc failed!");
        *sdram = NULL;
        return;
    }

    memset(tmp, 0, sizeof(sdram_driver_t));

    tmp->bus.fmc = fmc;

    #ifndef NDEBUG
    tmp->sdram_name = "N/A";
    #endif

    *sdram = tmp;
}

void sdram_driver_config(sdram_driver_t *sdram, uint32_t size){
    sdram->config.memory_size = size;
    sdram->config.memory_ptr = (void *)fmc_driver_bank_5_get_address(sdram->bus.fmc);
}

void *sdram_driver_get_address(sdram_driver_t *sdram){
    return sdram->config.memory_ptr;
}

uint32_t sdram_driver_get_size(sdram_driver_t *sdram){
    return sdram->config.memory_size;
}

uint8_t sdram_driver_read_byte(sdram_driver_t *sdram, uint32_t address){
    uint8_t tmp = 0;
    sdram_driver_read_u8(sdram, address, 1, &tmp);
    return tmp;
}
uint16_t sdram_driver_read_hword(sdram_driver_t *sdram, uint32_t address){
    uint16_t tmp = 0;
    sdram_driver_read_u16(sdram, address, 1, &tmp);
    return tmp;
}
uint32_t sdram_driver_read_word(sdram_driver_t *sdram, uint32_t address){
    uint32_t tmp = 0;
    sdram_driver_read_u32(sdram, address, 1, &tmp);
    return tmp;
}

void sdram_driver_write_byte(sdram_driver_t *sdram, uint32_t address, uint8_t byte){
    sdram_driver_write_u8(sdram, address, 1, &byte);
}

void sdram_driver_write_hword(sdram_driver_t *sdram, uint32_t address, uint16_t hword){
    sdram_driver_write_u16(sdram, address, 1, &hword);
}

void sdram_driver_write_word(sdram_driver_t *sdram, uint32_t address, uint32_t word){
    sdram_driver_write_u32(sdram, address, 1, &word);
}

void sdram_driver_read_u8(sdram_driver_t *sdram, uint32_t address, uint32_t len, uint8_t *data){
    uint8_t *ptr = (uint8_t *)sdram_driver_get_address(sdram);

    for(uint32_t i = 0; i < len; i++){
        data[i] = ptr[address + i];
    }
}

void sdram_driver_read_u16(sdram_driver_t *sdram, uint32_t address, uint32_t len, uint16_t *data){
    uint16_t *ptr = (uint16_t *)sdram_driver_get_address(sdram);

    for(uint32_t i = 0; i < len; i++){
        data[i] = ptr[address + i];
    }
}

void sdram_driver_read_u32(sdram_driver_t *sdram, uint32_t address, uint32_t len, uint32_t *data){
    uint32_t *ptr = (uint32_t *)sdram_driver_get_address(sdram);

    for(uint32_t i = 0; i < len; i++){
        data[i] = ptr[address + i];
    }
}

void sdram_driver_write_u8(sdram_driver_t *sdram, uint32_t address, uint32_t len, uint8_t *data){
    uint8_t *ptr = (uint8_t *)sdram_driver_get_address(sdram);

    for(uint32_t i = 0; i < len; i++){
        ptr[address + i] = data[i];
    }
}

void sdram_driver_write_u16(sdram_driver_t *sdram, uint32_t address, uint32_t len, uint16_t *data){
    uint16_t *ptr = (uint16_t *)sdram_driver_get_address(sdram);

    for(uint32_t i = 0; i < len; i++){
        ptr[address + i] = data[i];
    }
}

void sdram_driver_write_u32(sdram_driver_t *sdram, uint32_t address, uint32_t len, uint32_t *data){
    uint32_t *ptr = (uint32_t *)sdram_driver_get_address(sdram);

    for(uint32_t i = 0; i < len; i++){
        ptr[address + i] = data[i];
    }
}

#ifndef NDEBUG
void sdram_driver_set_name(sdram_driver_t *sdram, const char *sdram_name){
    sdram->sdram_name = sdram_name;
}
#endif
