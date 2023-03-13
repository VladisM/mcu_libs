#include "button.h"

#include "driver_dev_debug.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void button_driver_init(button_driver_t **button, gpio_driver_t *pin){
    button_driver_t *tmp = (button_driver_t *)malloc(sizeof(button_driver_t));

    if(tmp == NULL){
        DRIVER_DEV_DEBUG_ERROR("%s", "Malloc failed!");
        *button = NULL;
        return;
    }

    memset(tmp, 0, sizeof(button_driver_t));

    tmp->pin = pin;

    tmp->button_state_n_minus_1 = !gpio_driver_read(tmp->pin);
    tmp->button_state_n_minus_2 = !gpio_driver_read(tmp->pin);

    #ifndef NDEBUG
    tmp->button_name = "N/A";
    #endif

    *button = tmp;
}

void button_driver_periodic(button_driver_t *button){
    button->button_state_n_minus_2 = button->button_state_n_minus_1;
    button->button_state_n_minus_1 = !gpio_driver_read(button->pin);
}

bool button_driver_read(button_driver_t *button){
    if(button->button_state_n_minus_2 == button->button_state_n_minus_1){
        return button->button_state_n_minus_1;
    }
    else{
        return false;
    }
}

#ifndef NDEBUG
void button_driver_set_name(button_driver_t *button, const char *button_name){
    button->button_name = button_name;
}
#endif
