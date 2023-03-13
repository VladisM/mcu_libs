#include "gpio.h"

#include <stm32.h>

#include "driver_mcu_debug.h"
#include "clock.h"

#include <string.h>
#include <stdlib.h>

//TODO: Add error handling! It should end up in some kind of error loop if illegal thing happen (eg. writing input pin).

//TODO: Add analog config

#define DEFAULT_MODER   MODER_INPUT
#define DEFAULT_OTYPER  OTYPER_PUSH_PULL
#define DEFAULT_OSPEDR  OSPEEDR_LOW
#define DEFAULT_AFR     AFR_0
#define DEFAULT_PUPDR   PUPDR_NONE

static void _gpio_config(gpio_driver_t *gpio, gpio_moder_t moder, gpio_otyper_t otyper, gpio_ospeedr_t ospeedr, gpio_afr_t afr, gpio_pupdr_t pupdr){
    gpio->config.moder = moder;
    gpio->config.otyper = otyper;
    gpio->config.ospeedr = ospeedr;
    gpio->config.afr = afr;
    gpio->config.pupdr = pupdr;
}

static inline uint32_t _gpio_get_moder(gpio_moder_t moder){
    return moder;
}

static inline uint32_t _gpio_get_otyper(gpio_otyper_t otyper){
    return otyper;
}

static inline uint32_t _gpio_get_ospeedr(gpio_ospeedr_t ospeedr){
    return ospeedr;
}

static inline uint32_t _gpio_get_pupdr(gpio_pupdr_t pupdr){
    return pupdr;
}

static inline uint32_t _gpio_get_afr(gpio_afr_t afr){
    return afr;
}

static void _gpio_clear(gpio_driver_t *gpio){
    GPIO_TypeDef *_device = gpio->device;

    _device->MODER   &= ~(0x3UL << (gpio->pin * 2));
    _device->OTYPER  &= ~(0x1UL << (gpio->pin * 1));
    _device->OSPEEDR &= ~(0x3UL << (gpio->pin * 2));
    _device->PUPDR   &= ~(0x3UL << (gpio->pin * 2));

    if(gpio->pin < 8){
        _device->AFR[0] &= ~(0xFUL << (gpio->pin * 4));
    }
    else{
        _device->AFR[1] &= ~(0xFUL << ((gpio->pin - 8) * 4));
    }

    _device->ODR &= ~(0x1UL << gpio->pin);

    gpio->enabled = false;
}

static void _gpio_enable(gpio_driver_t *gpio){
    GPIO_TypeDef *_device = gpio->device;

    //configure pin again
    _device->MODER   |= (_gpio_get_moder(gpio->config.moder)     << (gpio->pin * 2));
    _device->OTYPER  |= (_gpio_get_otyper(gpio->config.otyper)   << (gpio->pin * 1));
    _device->OSPEEDR |= (_gpio_get_ospeedr(gpio->config.ospeedr) << (gpio->pin * 2));
    _device->PUPDR   |= (_gpio_get_pupdr(gpio->config.pupdr)     << (gpio->pin * 2));

    if(gpio->pin < 8){
        _device->AFR[0] |= (_gpio_get_afr(gpio->config.afr) << (gpio->pin * 4));
    }
    else{
        _device->AFR[1] |= (_gpio_get_afr(gpio->config.afr) << ((gpio->pin - 8) * 4));
    }

    gpio->enabled = true;
}

static void _gpio_reconfigure(gpio_driver_t *gpio){
    _gpio_clear(gpio);
    _gpio_enable(gpio);
}

static bool _check_enabled(gpio_driver_t *gpio){
    if(gpio->enabled == false){
        DRIVER_MCU_DEBUG_ERROR("Pin '%s.%d'. Signal '%s'. %s", gpio->port_name, gpio->pin, gpio->signal_name, "Accessing but not configured.");
        return false;
    }

    return true;
}

static bool _check_writeable(gpio_driver_t *gpio){
    if(gpio->config.moder != MODER_OUTPUT){
        DRIVER_MCU_DEBUG_ERROR("Pin '%s.%d'. Signal '%s'. %s", gpio->port_name, gpio->pin, gpio->signal_name, "Writing but not output mode.");
        return false;
    }

    return true;
}

void gpio_driver_init(gpio_driver_t **gpio, void *device, uint8_t pin){
    gpio_driver_t *tmp = (gpio_driver_t *)malloc(sizeof(gpio_driver_t));

    if(tmp == NULL){
        DRIVER_MCU_DEBUG_ERROR("%s", "Malloc failed!");
        *gpio = NULL;
        return;
    }

    memset(tmp, 0, sizeof(gpio_driver_t));

    tmp->device = device;
    tmp->pin = pin;
    tmp->enabled = false;

    #ifndef NDEBUG
    tmp->port_name = "N/A";
    tmp->signal_name = "N/A";
    #endif

    clock_enable_peripheral_clock(device);

    *gpio = tmp;
}

void gpio_driver_config_as_output(gpio_driver_t *gpio, gpio_otyper_t otyper, gpio_ospeedr_t ospeedr, gpio_pupdr_t pupdr){
    _gpio_config(gpio, MODER_OUTPUT, otyper, ospeedr, DEFAULT_AFR, pupdr);
    _gpio_reconfigure(gpio);
}

void gpio_driver_config_as_input(gpio_driver_t *gpio, gpio_pupdr_t pupdr){
    _gpio_config(gpio, MODER_INPUT, DEFAULT_OTYPER, DEFAULT_OSPEDR, DEFAULT_AFR, pupdr);
    _gpio_reconfigure(gpio);
}

void gpio_driver_config_as_alternate(gpio_driver_t *gpio, gpio_otyper_t otyper, gpio_ospeedr_t ospeedr, gpio_pupdr_t pupdr, gpio_afr_t afr){
    _gpio_config(gpio, MODER_ALTERNATE, otyper, ospeedr, afr, pupdr);
    _gpio_reconfigure(gpio);
}

bool gpio_driver_read(gpio_driver_t *gpio){
    if(!_check_enabled(gpio)) return false;

    GPIO_TypeDef *_device = gpio->device;
    return (_device->IDR & (0x1UL << gpio->pin));
}

void gpio_driver_set(gpio_driver_t *gpio, bool value){
    if(!_check_enabled(gpio)) return;
    if(!_check_writeable(gpio)) return;

    GPIO_TypeDef *_device = gpio->device;
    _device->BSRR |= (value ? (0x1UL << (gpio->pin + 0)) : (0x1UL << (gpio->pin + 16)));
}

void gpio_driver_toggle(gpio_driver_t *gpio){
    if(!_check_enabled(gpio)) return;
    if(!_check_writeable(gpio)) return;

    GPIO_TypeDef *_device = gpio->device;
    _device->ODR ^= (0x1UL << (gpio->pin));
}

#ifndef NDEBUG
void gpio_driver_set_name(gpio_driver_t *gpio, const char *port_name, const char *signal_name){
    gpio->port_name = port_name;
    gpio->signal_name = signal_name;
}
#endif
