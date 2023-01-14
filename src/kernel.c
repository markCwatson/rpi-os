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

void kernel_main(void) {
    uart_init();
    uart_send_string("rpi-os initializing...\n");

    irq_vector_init();
    timer_init(1U, 100000U);
    irq_enable_controller();
    irq_enable();

    int res = fork_process((unsigned long)task1, 0);
    if (res < 0) {
        uart_send_string("[Error] fork_process failed!\n");
    }

    while (1) {
        sched_schedule();
    }
}
