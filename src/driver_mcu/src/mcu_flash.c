#include "mcu_flash.h"

#include "driver_mcu_debug.h"

#include <stm32.h>

void mcu_flash_config(bool dcache_en, bool icache_en, bool prefech_en, int wait_cycles){
    if(wait_cycles > 15){
        DRIVER_MCU_DEBUG_ERROR("Too much wait cycles!");
        return;
    }

    FLASH->ACR &= ~(FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_LATENCY_Msk | FLASH_ACR_PRFTEN_Msk);

    if(dcache_en)
        FLASH->ACR |= FLASH_ACR_DCEN;

    if(icache_en)
        FLASH->ACR |= FLASH_ACR_ICEN;

    if(prefech_en)
        FLASH->ACR |= FLASH_ACR_PRFTEN;

    FLASH->ACR |= (wait_cycles << FLASH_ACR_LATENCY_Pos);
}
