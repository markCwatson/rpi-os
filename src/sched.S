#include "sched.h"

.globl cpu_switch_to
cpu_switch_to:
    // Store callee-saved registers. 
    // This will save the context of the currently running task A in preparation for a context switch to task B.
    mov x10, #CPU_CONTEXT_OFFSET    // offset of cpu_context in task_struct 
    add x8, x0, x10                 // x0 is currently running task
    mov x9, sp                      // move stack pointer to x9
    stp x19, x20, [x8], #16         // save x19/x20 to first 2 members of cpu_context then increment x8 to start of next pair
    stp x21, x22, [x8], #16         // ...
    stp x23, x24, [x8], #16
    stp x25, x26, [x8], #16
    stp x27, x28, [x8], #16
    stp x29, x9, [x8], #16          // save x29 into fp member and the stack pointer into sp member.
    str x30, [x8]                   // save x30 to pc member

    // Restore callee-saved registers
    // This will restore the context of task B so it can now run.
    add x8, x1, x10                 // x1 is next task to run. x8 now points to cpu_context in of next task task_struct.
    ldp x19, x20, [x8], #16         // load x19/x20 with first 2 members of cpu_context then increment x8 to start of next pair
    ldp x21, x22, [x8], #16         // ...
    ldp x23, x24, [x8], #16
    ldp x25, x26, [x8], #16
    ldp x27, x28, [x8], #16
    ldp x29, x9, [x8], #16          // load x29 with fp and x9 with sp
    ldr x30, [x8]                   // load x30 with pc member
    mov sp, x9                      // move sp member (in x9) into the stack pointer. The stack pointer now points to start of task B's stack.
    ret