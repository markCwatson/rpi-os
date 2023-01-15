#pragma once

#include <stdint.h>
#include "arm/base.h"

#define TIMER_OFFSET    0x00003000

struct timer_regs {
    volatile uint32_t control_status;
    volatile uint32_t counter_lo;
    volatile uint32_t counter_hi;
    volatile uint32_t compare[4];
};

struct timer_regs *const timer = (struct timer_regs *)(PBASE + TIMER_OFFSET);
