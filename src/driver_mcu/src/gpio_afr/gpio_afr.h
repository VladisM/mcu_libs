#ifndef GPIO_AFR_H_included
#define GPIO_AFR_H_included

#if defined(STM32F405xx)
    #include "stm32f4/afr_STM32F405xx.h"
#elif defined(STM32F415xx)
    #include "stm32f4/afr_STM32F415xx.h"
#elif defined(STM32F407xx)
    #include "stm32f4/afr_STM32F407xx.h"
#elif defined(STM32F417xx)
    #include "stm32f4/afr_STM32F417xx.h"
#elif defined(STM32F427xx)
    #include "stm32f4/afr_STM32F427xx.h"
#elif defined(STM32F437xx)
    #include "stm32f4/afr_STM32F437xx.h"
#elif defined(STM32F429xx)
    #include "stm32f4/afr_STM32F429xx.h"
#elif defined(STM32F439xx)
    #include "stm32f4/afr_STM32F439xx.h"
#elif defined(STM32F401xC)
    #include "stm32f4/afr_STM32F401xC.h"
#elif defined(STM32F401xE)
    #include "stm32f4/afr_STM32F401xE.h"
#elif defined(STM32F410Tx)
    #include "stm32f4/afr_STM32F410Tx.h"
#elif defined(STM32F410Cx)
    #include "stm32f4/afr_STM32F410Cx.h"
#elif defined(STM32F410Rx)
    #include "stm32f4/afr_STM32F410Rx.h"
#elif defined(STM32F411xE)
    #include "stm32f4/afr_STM32F411xE.h"
#elif defined(STM32F446xx)
    #include "stm32f4/afr_STM32F446xx.h"
#elif defined(STM32F469xx)
    #include "stm32f4/afr_STM32F469xx.h"
#elif defined(STM32F479xx)
    #include "stm32f4/afr_STM32F479xx.h"
#elif defined(STM32F412Cx)
    #include "stm32f4/afr_STM32F412Cx.h"
#elif defined(STM32F412Rx)
    #include "stm32f4/afr_STM32F412Rx.h"
#elif defined(STM32F412Vx)
    #include "stm32f4/afr_STM32F412Vx.h"
#elif defined(STM32F412Zx)
    #include "stm32f4/afr_STM32F412Zx.h"
#elif defined(STM32F413xx)
    #include "stm32f4/afr_STM32F413xx.h"
#elif defined(STM32F423xx)
    #include "stm32f4/afr_STM32F423xx.h"
#else
    #error "Missing afr definitions for specified MCU!"
#endif

#endif
