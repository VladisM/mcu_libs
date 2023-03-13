#include "debug.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <inttypes.h>

static debug_config_t _debug_config;

static uint32_t get_elapsed_time(void){
    if(_debug_config.get_elapsed_ms != NULL){
        return _debug_config.get_elapsed_ms();
    }
    else{
        return 0;
    }
}

void debug_init(debug_config_t *debug_config){
    memcpy(&_debug_config, debug_config, sizeof(debug_config_t));

    debug_print("\r\n\r\n");
    DEBUG_INFO("Debug initialized.");
}

void debug_print(const char * format, ...){

    uint32_t timestamp = get_elapsed_time();

    if(timestamp < 1000)
        printf("[    0.%0*"PRIu32"] ", 3, timestamp);
    else
        printf("[%*"PRIu32".%0*"PRIu32"] ", 5, (timestamp / 1000), 3, (timestamp % 1000));

    va_list argptr;
    va_start(argptr, format);
    vprintf(format, argptr);
    va_end(argptr);

    fflush(stdout);
}
