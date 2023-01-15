#include "fork.h"
#include "mm.h"
#include "sched.h"

int8_t fork_process(void (*fn)(void), uint32_t arg) {
    sched_preempt_disable();

    struct task_struct *p = (struct task_struct *)mm_get_free_page();
    if (!p)
        return -1;

    p->priority = sched_get_current_priority();
    p->state = TASK_RUNNING_STATE;
    p->counter = p->priority;
    p->preempt_count = 1;               // disable preemtion until schedule_tail

    p->cpu_context.x19 = (uint64_t)fn;
    p->cpu_context.x20 = arg;
    p->cpu_context.pc = (uint64_t)ret_from_fork;
    p->cpu_context.sp = (uint64_t)p + THREAD_SIZE;

    int8_t ret = sched_add_fork(p);
    if (ret < 0)
        mm_free_page((void *)p);

    sched_preempt_enable();
    return ret;
}
