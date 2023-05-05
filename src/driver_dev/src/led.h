#ifndef LED_H_included
#define LED_H_included

#include <driver_mcu.h>

typedef enum {
    LED_ON = 0,
    LED_OFF
} led_state_t;

typedef struct{
    gpio_driver_t *pin;
    const char *led_name;
} led_driver_t;

void led_driver_init(led_driver_t **led, gpio_driver_t *pin);
void led_driver_set(led_driver_t *led, led_state_t state);

void led_driver_set_name(led_driver_t *led, const char *led_name);

#endif
