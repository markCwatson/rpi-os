#include "timer.h"
#include "arm/timer.h"
#include "arm/base.h"
#include "kernel.h"

static unsigned int intervals[4] = { 0 };

void timer_init(unsigned int id, unsigned int interval) {
    intervals[id] = interval;
    REGS_TIMER->compare[id] = REGS_TIMER->counter_lo + interval;
}

void timer_cancel(unsigned int id) {
    intervals[id] = 0;
    REGS_TIMER->compare[id] = 0;
}

void timer_irq_handler(unsigned int type) {
    if (type == 1U) {
        REGS_TIMER->control_status |= SYS_TIMER_IRQ_1;
        REGS_TIMER->compare[1U] = REGS_TIMER->counter_lo + intervals[1U];
    }
}
