#ifndef EEPROM_H_Included
#define EEPROM_H_Included

#include <stdint.h>
#include <stdbool.h>

#include <driver_mcu.h>

#include "sizes.h"

typedef struct{
    struct {
        uint32_t memory_size;
        uint32_t page_size;
        uint8_t i2c_address;
        unsigned write_delay_ms;
        unsigned address_bytes_count;
    } config;
    struct {
        i2c_driver_t *i2c;
    } bus;
    bool enabled;
    const char *eeprom_name;
} eeprom_driver_t;

void eeprom_driver_init(eeprom_driver_t **eeprom, i2c_driver_t *i2c, uint8_t address);

void eeprom_driver_config(eeprom_driver_t *eeprom, uint32_t size, uint32_t page_size, unsigned write_delay, unsigned address_bytes_count);

void eeprom_driver_write_byte(eeprom_driver_t *eeprom, uint32_t address, uint8_t data);
uint8_t eeprom_driver_read_byte(eeprom_driver_t *eeprom, uint32_t address);

void eeprom_driver_read(eeprom_driver_t *eeprom, uint8_t *buffer);
void eeprom_driver_write(eeprom_driver_t *eeprom, uint8_t *buffer);

uint32_t eeprom_driver_get_size(eeprom_driver_t *eeprom);

void eeprom_driver_set_name(eeprom_driver_t *eeprom, const char *eeprom_name);

#endif
