#ifndef I2C_H_included
#define I2C_H_included

#include "gpio.h"

typedef struct{
    struct {
        void *device;
        uint32_t peripheral_clock;
    } device;
    struct {
        gpio_driver_t *sda;
        gpio_driver_t *scl;
    } gpio;
    const char *i2c_name;
} i2c_driver_t;

void i2c_driver_init(i2c_driver_t **i2c, void *device, gpio_driver_t *sda, gpio_driver_t *scl);

void i2c_driver_write_byte(i2c_driver_t *i2c, uint8_t address, uint8_t byte);
void i2c_driver_write_buffer(i2c_driver_t *i2c, uint8_t address, unsigned len, uint8_t *buffer);

uint8_t i2c_driver_read_byte(i2c_driver_t *i2c, uint8_t address);
void i2c_driver_read_buffer(i2c_driver_t *i2c, uint8_t address, unsigned len, uint8_t *buff);

void i2c_driver_reconfigure_clock(i2c_driver_t *i2c);

void i2c_driver_set_name(i2c_driver_t *i2c, const char *i2c_name);

#endif
