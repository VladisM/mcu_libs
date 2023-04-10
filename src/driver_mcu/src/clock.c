#include "clock.h"

#include "driver_mcu_debug.h"
#include "clock_ll.h"

#include <stm32.h>

void clock_enable_peripheral_clock(void *peripheral){
    switch((uint32_t)peripheral){
        case (uint32_t)GPIOA:   RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  break;
        case (uint32_t)GPIOB:   RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;  break;
        case (uint32_t)GPIOC:   RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;  break;
        case (uint32_t)GPIOD:   RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  break;
        case (uint32_t)GPIOE:   RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;  break;
        case (uint32_t)GPIOF:   RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;  break;
        case (uint32_t)GPIOG:   RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;  break;
        case (uint32_t)GPIOH:   RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;  break;
        case (uint32_t)QUADSPI: RCC->AHB3ENR |= RCC_AHB3ENR_QSPIEN;   break;
        case (uint32_t)USART2:  RCC->APB1ENR |= RCC_APB1ENR_USART2EN; break;
        case (uint32_t)USART3:  RCC->APB1ENR |= RCC_APB1ENR_USART3EN; break;
        case (uint32_t)UART4:   RCC->APB1ENR |= RCC_APB1ENR_UART4EN;  break;
        case (uint32_t)UART5:   RCC->APB1ENR |= RCC_APB1ENR_UART5EN;  break;
        case (uint32_t)I2C1:    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;   break;
        case (uint32_t)I2C2:    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;   break;
        case (uint32_t)I2C3:    RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;   break;
        case (uint32_t)USART1:  RCC->APB2ENR |= RCC_APB2ENR_USART1EN; break;
        case (uint32_t)USART6:  RCC->APB2ENR |= RCC_APB2ENR_USART6EN; break;
        case (uint32_t)FMC_Bank1:
        case (uint32_t)FMC_Bank1E:
        case (uint32_t)FMC_Bank3:
        case (uint32_t)FMC_Bank5_6:
            RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;
            break;
        default:
            DRIVER_MCU_DEBUG_ERROR("Trying to enable clock for unknown peripheral %u", (uint32_t)peripheral);
            break;
    }
}

void clock_disable_peripheral_clock(void *peripheral){
    switch((uint32_t)peripheral){
        case (uint32_t)GPIOA:   RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOAEN);  break;
        case (uint32_t)GPIOB:   RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOBEN);  break;
        case (uint32_t)GPIOC:   RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOCEN);  break;
        case (uint32_t)GPIOD:   RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIODEN);  break;
        case (uint32_t)GPIOE:   RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOEEN);  break;
        case (uint32_t)GPIOF:   RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOFEN);  break;
        case (uint32_t)GPIOG:   RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOGEN);  break;
        case (uint32_t)GPIOH:   RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOHEN);  break;
        case (uint32_t)QUADSPI: RCC->AHB3ENR &= ~(RCC_AHB3ENR_QSPIEN);   break;
        case (uint32_t)USART2:  RCC->APB1ENR &= ~(RCC_APB1ENR_USART2EN); break;
        case (uint32_t)USART3:  RCC->APB1ENR &= ~(RCC_APB1ENR_USART3EN); break;
        case (uint32_t)UART4:   RCC->APB1ENR &= ~(RCC_APB1ENR_UART4EN);  break;
        case (uint32_t)UART5:   RCC->APB1ENR &= ~(RCC_APB1ENR_UART5EN);  break;
        case (uint32_t)I2C1:    RCC->APB1ENR &= ~(RCC_APB1ENR_I2C1EN);   break;
        case (uint32_t)I2C2:    RCC->APB1ENR &= ~(RCC_APB1ENR_I2C2EN);   break;
        case (uint32_t)I2C3:    RCC->APB1ENR &= ~(RCC_APB1ENR_I2C3EN);   break;
        case (uint32_t)USART1:  RCC->APB2ENR &= ~(RCC_APB2ENR_USART1EN); break;
        case (uint32_t)USART6:  RCC->APB2ENR &= ~(RCC_APB2ENR_USART6EN); break;
        case (uint32_t)FMC_Bank1:
        case (uint32_t)FMC_Bank1E:
        case (uint32_t)FMC_Bank3:
        case (uint32_t)FMC_Bank5_6:
            RCC->AHB3ENR &= ~(RCC_AHB3ENR_FMCEN);
            break;
        default:
            DRIVER_MCU_DEBUG_ERROR("Trying to enable clock for unknown peripheral %u", (uint32_t)peripheral);
            break;
    }
}

uint32_t clock_get_peripheral_clock(void *peripheral){
    switch((uint32_t)peripheral){
        case (uint32_t)GPIOA:
        case (uint32_t)GPIOB:
        case (uint32_t)GPIOC:
        case (uint32_t)GPIOD:
        case (uint32_t)GPIOE:
        case (uint32_t)GPIOF:
        case (uint32_t)GPIOG:
        case (uint32_t)GPIOH:
        case (uint32_t)QUADSPI:
        case (uint32_t)FMC_Bank1:
        case (uint32_t)FMC_Bank1E:
        case (uint32_t)FMC_Bank3:
        case (uint32_t)FMC_Bank5_6:
            return clock_ll_hclk_get();

        case (uint32_t)USART2:
        case (uint32_t)USART3:
        case (uint32_t)UART4:
        case (uint32_t)UART5:
        case (uint32_t)I2C1:
        case (uint32_t)I2C2:
        case (uint32_t)I2C3:
            return clock_ll_pclk1_get();

        case (uint32_t)USART1:
        case (uint32_t)USART6:
            return clock_ll_pclk2_get();

        default:
            return 0;
    }
}

uint32_t clock_get_core_clock(void){
    return clock_ll_hclk_get();
}
