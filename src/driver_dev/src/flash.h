#ifndef FLASH_H_included
#define FLASH_H_included

#include <stdint.h>
#include <stdbool.h>

#include <driver_mcu.h>

#include "sizes.h"

typedef struct {
    struct {
        uint32_t memory_size;
        uint32_t sector_size;
        unsigned address_bytes_count;
    } config;
    struct {
        qspi_driver_t *qspi;
    } bus;
    bool enabled;
    const char *flash_name;
} flash_driver_t;

void flash_driver_init(flash_driver_t **flash, qspi_driver_t *qspi);

void flash_driver_config(flash_driver_t *flash, uint32_t flash_size, uint32_t sector_size, unsigned address_bytes_count);

uint8_t flash_driver_read_byte(flash_driver_t *flash, uint32_t address);

void flash_driver_write_sector(flash_driver_t *flash, unsigned sector, uint8_t *data);
void flash_driver_read_sector(flash_driver_t *flash, unsigned sector, uint8_t *data);

void flash_driver_mass_erase(flash_driver_t *flash);
void flash_driver_sector_erase(flash_driver_t *flash, unsigned sector);

uint32_t flash_driver_get_size(flash_driver_t *flash);
uint32_t flash_driver_get_sector_size(flash_driver_t *flash);
uint32_t flash_driver_get_sector_count(flash_driver_t *flash);

void flash_driver_set_name(flash_driver_t *flash, const char *flash_name);

#endif
