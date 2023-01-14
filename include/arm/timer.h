#pragma once

struct timer_regs {
    volatile unsigned int control_status;
    volatile unsigned int counter_lo;
    volatile unsigned int counter_hi;
    volatile unsigned int compare[4];
};

#define TIMER_OFFSET    0x00003000
#define REGS_TIMER      ((struct timer_regs *)(PBASE + TIMER_OFFSET))
