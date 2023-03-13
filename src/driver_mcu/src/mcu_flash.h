#ifndef MCU_FLASH_H_included
#define MCU_FLASH_H_included

#include <stdbool.h>

void mcu_flash_config(bool dcache_en, bool icache_en, bool prefech_en, int wait_cycles);

#endif
