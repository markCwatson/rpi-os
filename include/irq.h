#pragma once

void irq_enable_controller(void);
void irq_disable_controller(void);
void irq_handler(void);

extern void irq_vector_init(void);
extern void irq_enable(void);
extern void irq_disable(void);
