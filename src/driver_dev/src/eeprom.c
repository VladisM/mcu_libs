#include "eeprom.h"

#include "driver_dev_debug.h"
#include "common.h"

#include <stdlib.h>
#include <string.h>

//TODO: implement error handling in case of wrong config
//TODO: implement configuration check, EEPROM_SIZE % EEPROM_PAGE == 0 etc.
//TODO: remove need to setup address_bytes_count manually, compute it from EEPROM_SIZE

//this should be idealy replaced with polling, otherwise application HAVE to implement this!
void delay(uint16_t ms);

static bool _check_enabled(eeprom_driver_t *eeprom){
    if(eeprom->enabled == false){
        DRIVER_DEV_DEBUG_ERROR("EEPROM '%s'. %s", eeprom->eeprom_name, "Accessing but not configured.");
        return false;
    }

    return true;
}

static bool _check_valid_range(eeprom_driver_t *eeprom, uint32_t address){
    if(eeprom->config.memory_size < address){
        DRIVER_DEV_DEBUG_ERROR("EEPROM '%s'. %s", eeprom->eeprom_name, "Address out of range.");
        return false;
    }

    return true;
}

void eeprom_driver_init(eeprom_driver_t **eeprom, i2c_driver_t *i2c, uint8_t address){
    eeprom_driver_t *tmp = (eeprom_driver_t *)malloc(sizeof(eeprom_driver_t));

    if(tmp == NULL){
        DRIVER_DEV_DEBUG_ERROR("%s", "Malloc failed!");
        *eeprom = NULL;
        return;
    }

    memset(tmp, 0, sizeof(eeprom_driver_t));

    tmp->bus.i2c = i2c;
    tmp->config.i2c_address = address;
    tmp->enabled = false;
    tmp->eeprom_name = default_driver_dev_name;

    *eeprom = tmp;
}

void eeprom_driver_config(eeprom_driver_t *eeprom, uint32_t size, uint32_t page_size, unsigned write_delay, unsigned address_bytes_count){
    eeprom->config.memory_size = size;
    eeprom->config.page_size = page_size;
    eeprom->config.address_bytes_count = address_bytes_count;
    eeprom->config.write_delay_ms = write_delay;

    eeprom->enabled = true;
}

static void _create_address_into_buffer(eeprom_driver_t *eeprom, uint32_t address, uint8_t *buffer){

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wimplicit-fallthrough"

    switch(eeprom->config.address_bytes_count){
        case 4:
            buffer[3] = (address & 0xFF000000UL) >> 24;
        case 3:
            buffer[2] = (address & 0xFF0000UL) >> 16;
        case 2:
            buffer[1] = (address & 0xFF00UL) >> 8;
        case 1:
            buffer[0] = address & 0xFFUL;
            break;
    }

    #pragma GCC diagnostic pop
}

void eeprom_driver_write_byte(eeprom_driver_t *eeprom, uint32_t address, uint8_t data){
    if(!_check_enabled(eeprom)) return;
    if(!_check_valid_range(eeprom, address)) return;

    unsigned buffer_len = eeprom->config.address_bytes_count + 1;
    uint8_t buffer[buffer_len];

    _create_address_into_buffer(eeprom, address, buffer);
    buffer[eeprom->config.address_bytes_count] = data;

    i2c_driver_write_buffer(eeprom->bus.i2c, eeprom->config.i2c_address, buffer_len, buffer);
    delay(eeprom->config.write_delay_ms);
}

uint8_t eeprom_driver_read_byte(eeprom_driver_t *eeprom, uint32_t address){
    if(!_check_enabled(eeprom)) return 0;
    if(!_check_valid_range(eeprom, address)) return 0;

    i2c_driver_write_byte(eeprom->bus.i2c, eeprom->config.i2c_address, address);
    delay(eeprom->config.write_delay_ms);
    return i2c_driver_read_byte(eeprom->bus.i2c, eeprom->config.i2c_address);
}

void eeprom_driver_read(eeprom_driver_t *eeprom, uint8_t *buffer){
    if(!_check_enabled(eeprom)) return;

    for(uint32_t i = 0; i < (eeprom->config.memory_size / eeprom->config.page_size); i++){
        uint8_t tmp_buffer[eeprom->config.page_size];

        i2c_driver_write_byte(eeprom->bus.i2c, eeprom->config.i2c_address, (i * eeprom->config.page_size));
        delay(eeprom->config.write_delay_ms);
        i2c_driver_read_buffer(eeprom->bus.i2c, eeprom->config.i2c_address, eeprom->config.page_size, tmp_buffer);

        memcpy(buffer + (i * eeprom->config.page_size), tmp_buffer, eeprom->config.page_size);
    }
}

void eeprom_driver_write(eeprom_driver_t *eeprom, uint8_t *buffer){
    if(!_check_enabled(eeprom)) return;

    for(uint32_t i = 0; i < (eeprom->config.memory_size / eeprom->config.page_size); i++){
        uint32_t page_address = i * eeprom->config.page_size;
        unsigned buffer_len = eeprom->config.address_bytes_count + eeprom->config.page_size;

        uint8_t tmp_buffer[buffer_len];
        _create_address_into_buffer(eeprom, page_address, tmp_buffer);

        memcpy(tmp_buffer + eeprom->config.address_bytes_count, buffer + (i * eeprom->config.page_size), eeprom->config.page_size);

        i2c_driver_write_buffer(eeprom->bus.i2c, eeprom->config.i2c_address, buffer_len, tmp_buffer);
        delay(eeprom->config.write_delay_ms);
    }
}

uint32_t eeprom_driver_get_size(eeprom_driver_t *eeprom){
    return eeprom->config.memory_size;
}

void eeprom_driver_set_name(eeprom_driver_t *eeprom, const char *eeprom_name){
    eeprom->eeprom_name = eeprom_name;
}
