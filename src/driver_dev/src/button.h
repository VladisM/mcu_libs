#ifndef BUTTON_H_included
#define BUTTON_H_included

#include <stdbool.h>

#include <driver_mcu.h>

typedef struct {
    gpio_driver_t *pin;
    volatile bool button_state_n_minus_2;
    volatile bool button_state_n_minus_1;
    #ifndef NDEBUG
    const char *button_name;
    #endif
}button_driver_t;

void button_driver_init(button_driver_t **button, gpio_driver_t *pin);
void button_driver_periodic(button_driver_t *button);
bool button_driver_read(button_driver_t *button);

#ifndef NDEBUG
#define BUTTON_DRIVER_SET_NAME(button, name) button_driver_set_name((button), (name))
void button_driver_set_name(button_driver_t *button, const char *button_name);
#else
#define BUTTON_DRIVER_SET_NAME(button, name)
#endif

#endif
