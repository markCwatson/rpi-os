#include "irq.h"
#include "timer.h"

void kernel_main(void) {
    irq_vector_init();
    timer_init(1U, 100000U);
    irq_enable_controller();
    irq_enable();

    while (1);
}