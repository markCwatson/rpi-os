#pragma once

#include "arm/base.h"

#define TIMER_OFFSET    0x00003000

struct timer_regs {
    volatile unsigned int control_status;
    volatile unsigned int counter_lo;
    volatile unsigned int counter_hi;
    volatile unsigned int compare[4];
};

struct timer_regs *const timer = (struct timer_regs *)(PBASE + TIMER_OFFSET);
