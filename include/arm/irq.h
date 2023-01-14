#pragma once

#include "arm/base.h"

#define IRQ_BASIC_PENDING   (PBASE + 0x0000B200)
#define IRQ_PENDING_1       (PBASE + 0x0000B204)
#define IRQ_PENDING_2       (PBASE + 0x0000B208)
#define FIQ_CONTROL         (PBASE + 0x0000B20C)
#define ENABLE_IRQS_1       (PBASE + 0x0000B210)
#define ENABLE_IRQS_2       (PBASE + 0x0000B214)
#define ENABLE_BASIC_IRQS   (PBASE + 0x0000B218)
#define DISABLE_IRQS_1      (PBASE + 0x0000B21C)
#define DISABLE_IRQS_2      (PBASE + 0x0000B220)
#define DISABLE_BASIC_IRQS  (PBASE + 0x0000B224)

#define SYSTEM_TIMER_IRQ_0  (1 << 0)
#define SYSTEM_TIMER_IRQ_1  (1 << 1)
#define SYSTEM_TIMER_IRQ_2  (1 << 2)
#define SYSTEM_TIMER_IRQ_3  (1 << 3)

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

#define IRQ_OFFSET  0x0000B200
#define REGS_IRQ    ((struct arm_irq_regs_2711 *)(PBASE + IRQ_OFFSET))
