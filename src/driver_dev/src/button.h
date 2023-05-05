#ifndef BUTTON_H_included
#define BUTTON_H_included

#include <stdbool.h>

#include <driver_mcu.h>

typedef struct {
    gpio_driver_t *pin;
    volatile bool button_state_n_minus_2;
    volatile bool button_state_n_minus_1;
    const char *button_name;
}button_driver_t;

void button_driver_init(button_driver_t **button, gpio_driver_t *pin);
void button_driver_periodic(button_driver_t *button);
bool button_driver_read(button_driver_t *button);

void button_driver_set_name(button_driver_t *button, const char *button_name);

#endif
