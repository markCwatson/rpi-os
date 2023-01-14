#include "irq.h"
#include "arm/irq.h"
#include "timer.h"
#include "kernel.h"

void irq_vector_init(void);
void irq_enable(void);
void irq_disable(void);

void irq_enable_controller(void) {
    irq->irq0_enable_0 = SYS_TIMER_IRQ_1;
}

void irq_disable_controller(void) {
    irq->irq0_enable_0 = 0;
}

void irq_handler(void) {
    unsigned int irq_pending = irq->irq0_pending_0;

    while (irq_pending) {
        if (irq_pending & SYS_TIMER_IRQ_1) {
            irq_pending &= ~SYS_TIMER_IRQ_1;
            
            timer_irq_handler(1U);
        }
    }
}
