#ifndef _DEBUG_H_included
#define _DEBUG_H_included

#include <stdint.h>

typedef struct {
    uint32_t (*get_elapsed_ms)(void);
} debug_config_t;

#ifndef NDEBUG

    #define DEBUG_INIT(x)            debug_init(x)
    #define DEBUG_INFO(format, ...)  debug_print("INFO : " format "\r\n", ## __VA_ARGS__ )
    #define DEBUG_WARN(format, ...)  debug_print("WARN : " format "\r\n", ## __VA_ARGS__ )
    #define DEBUG_ERROR(format, ...) debug_print("ERROR: " format "\r\n", ## __VA_ARGS__ )

#else

    #define DEBUG_INIT(x)
    #define DEBUG_INFO(format, ...)
    #define DEBUG_WARN(format, ...)
    #define DEBUG_ERROR(format, ...)

#endif

void debug_init(debug_config_t *debug_config);
void debug_print(const char * format, ...);

#endif
