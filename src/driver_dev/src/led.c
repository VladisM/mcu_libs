#include "led.h"

#include "driver_dev_debug.h"
#include "common.h"

#include <string.h>
#include <stdlib.h>

void led_driver_init(led_driver_t **led, gpio_driver_t *pin){
    DEBUG_INFO("Initializing led driver.");

    led_driver_t *tmp = (led_driver_t *)malloc(sizeof(led_driver_t));

    if(tmp == NULL){
        DRIVER_DEV_DEBUG_ERROR("%s", "Malloc failed!");
        *led = NULL;
        return;
    }

    memset(tmp, 0, sizeof(led_driver_t));

    tmp->pin = pin;
    tmp->led_name = default_driver_dev_name;

    led_driver_set(tmp, LED_OFF);

    *led = tmp;
}

void led_driver_set(led_driver_t *led, led_state_t state){

    #ifdef DRIVER_DEV_DEBUG_ENABLED
    char *state_s = state == LED_ON ? "ON" : "OFF";
    DRIVER_DEV_DEBUG_INFO("Set %s to %s", led->led_name, state_s);
    #endif

    gpio_driver_set(led->pin, (state == LED_ON) ? false : true);
}

void led_driver_set_name(led_driver_t *led, const char *led_name){
    led->led_name = led_name;
}
