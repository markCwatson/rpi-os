#include "timer.h"
#include "arm/timer.h"
#include "arm/base.h"
#include "kernel.h"

static unsigned int intervals[4] = { 0 };

void timer_init(unsigned int id, unsigned int interval) {
    intervals[id] = interval;
    timer->compare[id] = timer->counter_lo + interval;
}

void timer_cancel(unsigned int id) {
    intervals[id] = 0;
    timer->compare[id] = 0;
}

void timer_irq_handler(unsigned int type) {
    if (type == 1U) {
        timer->control_status |= SYS_TIMER_IRQ_1;
        timer->compare[1U] = timer->counter_lo + intervals[1U];
    }
}
