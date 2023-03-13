#ifndef CLOCK_H_included
#define CLOCK_H_included

#include <stdint.h>

void clock_enable_peripheral_clock(void *peripheral);
void clock_disable_peripheral_clock(void *peripheral);

uint32_t clock_get_peripheral_clock(void *peripheral);
uint32_t clock_get_core_clock(void);

#endif
