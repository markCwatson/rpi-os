#include "timer.h"
#include "arm/timer.h"
#include "arm/base.h"
#include "kernel.h"

static uint32_t intervals[4] = { 0 };

int8_t timer_init(uint32_t id, uint32_t interval) {
    intervals[id] = interval;
    timer->compare[id] = timer->counter_lo + interval;
    return 0;
}

void timer_cancel(uint32_t id) {
    intervals[id] = 0;
    timer->compare[id] = 0;
}

void timer_irq_handler(uint32_t type) {
    if (type == 1U) {
        timer->control_status |= SYS_TIMER_IRQ_1;
        timer->compare[1U] = timer->counter_lo + intervals[1U];
    }
}
