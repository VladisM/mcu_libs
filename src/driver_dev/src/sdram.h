#ifndef SDRAM_H_included
#define SDRAM_H_included

#include <stdint.h>

#include <driver_mcu.h>

#include "sizes.h"

typedef struct{
    struct {
        uint32_t memory_size;
        void *memory_ptr;
    } config;
    struct {
        fmc_driver_t *fmc;
    } bus;
    const char *sdram_name;
} sdram_driver_t;


void sdram_driver_init(sdram_driver_t **sdram, fmc_driver_t *fmc);
void sdram_driver_config(sdram_driver_t *sdram, uint32_t size);

void *sdram_driver_get_address(sdram_driver_t *sdram);
uint32_t sdram_driver_get_size(sdram_driver_t *sdram);

uint8_t sdram_driver_read_byte(sdram_driver_t *sdram, uint32_t address);
uint16_t sdram_driver_read_hword(sdram_driver_t *sdram, uint32_t address);
uint32_t sdram_driver_read_word(sdram_driver_t *sdram, uint32_t address);

void sdram_driver_write_byte(sdram_driver_t *sdram, uint32_t address, uint8_t byte);
void sdram_driver_write_hword(sdram_driver_t *sdram, uint32_t address, uint16_t hword);
void sdram_driver_write_word(sdram_driver_t *sdram, uint32_t address, uint32_t word);

void sdram_driver_read_u8(sdram_driver_t *sdram, uint32_t address, uint32_t len, uint8_t *data);
void sdram_driver_read_u16(sdram_driver_t *sdram, uint32_t address, uint32_t len, uint16_t *data);
void sdram_driver_read_u32(sdram_driver_t *sdram, uint32_t address, uint32_t len, uint32_t *data);

void sdram_driver_write_u8(sdram_driver_t *sdram, uint32_t address, uint32_t len, uint8_t *data);
void sdram_driver_write_u16(sdram_driver_t *sdram, uint32_t address, uint32_t len, uint16_t *data);
void sdram_driver_write_u32(sdram_driver_t *sdram, uint32_t address, uint32_t len, uint32_t *data);

void sdram_driver_set_name(sdram_driver_t *sdram, const char *sdram_name);

#endif
