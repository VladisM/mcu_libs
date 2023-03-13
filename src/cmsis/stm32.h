#ifndef STM32_H_included
#define STM32_H_included

#if defined(STM32F4)
    #include "stm32f4/Include/stm32f4xx.h"
#else
    #error Not specified MCU family!
#endif

#endif
