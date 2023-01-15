#include <stdint.h>
#include "irq.h"
#include "timer.h"
#include "mini_uart.h"
#include "utils.h"
#include "fork.h"
#include "sched.h"

void task1(void) {
    while (1) {
        delay(1000000);
        uart_send_string("Tick\n");
    }
}

/*
 * Inputs are passed into kernel_main from the RPi firmware, running on the GPU, per 
 * the ARM boot protocol for AArch64.
 *
 * x0 is the 32 bit address of the Device Tree Blob (the upper 32 bits may not be cleared). 
 * x1-x3 are cleared to zero for now, but reserved for future use.
 * 
 * \todo: Although they are not used right now, boot.S should preserve x0-x3
 */
void kernel_main(uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3) {
    uart_init();
    uart_send_string("rpi-os initializing...\n");

    irq_vector_init();
    timer_init(1U, 100000U);
    irq_enable_controller();
    irq_enable();

    int8_t res = fork_process(task1, 0);
    if (res < 0) {
        uart_send_string("[Error] fork_process failed!\n");
    }

    while (1) {
        sched_schedule();
    }
}
