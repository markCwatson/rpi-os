#include "irq.h"
#include "arm/irq.h"
#include "timer.h"
#include "kernel.h"

void irq_vector_init(void);
void irq_enable(void);
void irq_disable(void);

void irq_enable_controller(void) {
    REGS_IRQ->irq0_enable_0 = SYS_TIMER_IRQ_1;
}

void irq_disable_controller(void) {
    REGS_IRQ->irq0_enable_0 = 0;
}

void irq_handler(void) {
    unsigned int irq = REGS_IRQ->irq0_pending_0;

    while (irq) {
        if (irq & SYS_TIMER_IRQ_1) {
            irq &= ~SYS_TIMER_IRQ_1;
            
            timer_irq_handler(1U);
        }
    }
}
