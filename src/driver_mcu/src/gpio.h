#ifndef GPIO_H_included
#define GPIO_H_included

#include <stdint.h>
#include <stdbool.h>

#include "gpio_afr/gpio_afr.h"

typedef enum{
    MODER_INPUT = 0,
    MODER_OUTPUT = 1,
    MODER_ALTERNATE = 2
} gpio_moder_t;

typedef enum{
    OTYPER_PUSH_PULL = 0,
    OTYPER_OPEN_DRAIN = 1
} gpio_otyper_t;

typedef enum{
    OSPEEDR_LOW = 0,
    OSPEEDR_MEDIUM = 1,
    OSPEEDR_FAST = 2,
    OSPEEDR_HIGH = 3
} gpio_ospeedr_t;

typedef enum{
    PUPDR_NONE = 0,
    PUPDR_PULLUP = 1,
    PUPDR_PULLDOWN = 2
} gpio_pupdr_t;

typedef enum{
    AFR_0 = 0,
    AFR_1 = 1,
    AFR_2 = 2,
    AFR_3 = 3,
    AFR_4 = 4,
    AFR_5 = 5,
    AFR_6 = 6,
    AFR_7 = 7,
    AFR_8 = 8,
    AFR_9 = 9,
    AFR_10 = 10,
    AFR_11 = 11,
    AFR_12 = 12,
    AFR_13 = 13,
    AFR_14 = 14,
    AFR_15 = 15
} gpio_afr_t;

typedef struct{
    struct{
        gpio_moder_t moder;
        gpio_otyper_t otyper;
        gpio_ospeedr_t ospeedr;
        gpio_afr_t afr;
        gpio_pupdr_t pupdr;
    }config;
    uint8_t pin;
    void *device;
    bool enabled;
    #ifndef NDEBUG
    const char *signal_name;
    const char *port_name;
    #endif
} gpio_driver_t;

void gpio_driver_init(gpio_driver_t **gpio, void *device, uint8_t pin);

void gpio_driver_config_as_output(gpio_driver_t *gpio, gpio_otyper_t otyper, gpio_ospeedr_t ospeedr, gpio_pupdr_t pupdr);
void gpio_driver_config_as_input(gpio_driver_t *gpio, gpio_pupdr_t pupdr);
void gpio_driver_config_as_alternate(gpio_driver_t *gpio, gpio_otyper_t otyper, gpio_ospeedr_t ospeedr, gpio_pupdr_t pupdr, gpio_afr_t afr);

bool gpio_driver_read(gpio_driver_t *gpio);
void gpio_driver_set(gpio_driver_t *gpio, bool value);
void gpio_driver_toggle(gpio_driver_t *gpio);

#ifndef NDEBUG
#define GPIO_DRIVER_SET_NAME(gpio, port, signal) gpio_driver_set_name((gpio), (port), (signal))
void gpio_driver_set_name(gpio_driver_t *gpio, const char *port_name, const char *signal_name);
#else
#define GPIO_DRIVER_SET_NAME(gpio, port, signal)
#endif

#endif
