#include "irq.h"
#include "timer.h"
#include "kernel.h"

void irq_vector_init(void);
void irq_enable(void);
void irq_disable(void);

struct arm_irq_regs_2711 {
    volatile unsigned int irq0_pending_0;
    volatile unsigned int irq0_pending_1;
    volatile unsigned int irq0_pending_2;
    volatile unsigned int res0;
    volatile unsigned int irq0_enable_0;
    volatile unsigned int irq0_enable_1;
    volatile unsigned int irq0_enable_2;
    volatile unsigned int res1;
    volatile unsigned int irq0_disable_0;
    volatile unsigned int irq0_disable_1;
    volatile unsigned int irq0_disable_2;
};

typedef struct arm_irq_regs_2711 arm_irq_regs;

#define REGS_IRQ ((arm_irq_regs *)(PERIPHERAL_BASE + 0x0000B200)) // \todo: confirm this offset

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