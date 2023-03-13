#ifndef DRIVER_MCU_DEBUG_H_included
#define DRIVER_MCU_DEBUG_H_included

//TODO: add configurable include for application main debug
#include <debug.h>

#ifndef DEBUG_INFO
    #define DEBUG_INFO(format, ...)
#endif

#ifndef DEBUG_WARN
    #define DEBUG_WARN(format, ...)
#endif

#ifndef DEBUG_ERROR
    #define DEBUG_ERROR(format, ...)
#endif

#ifdef DRIVER_MCU_DEBUG_ENABLED

    #define DRIVER_MCU_DEBUG_INFO(format, ...)      DEBUG_INFO(format, ## __VA_ARGS__)
    #define DRIVER_MCU_DEBUG_WARN(format, ...)      DEBUG_WARN(format, ## __VA_ARGS__)
    #define DRIVER_MCU_DEBUG_ERROR(format, ...)     DEBUG_ERROR(format, ## __VA_ARGS__)

#else

    #define DRIVER_MCU_DEBUG_INFO(format, ...)
    #define DRIVER_MCU_DEBUG_WARN(format, ...)
    #define DRIVER_MCU_DEBUG_ERROR(format, ...)

#endif

#endif
