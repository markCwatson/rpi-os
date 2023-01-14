#include "fork.h"
#include "mm.h"
#include "sched.h"

int fork_process(unsigned long fn, unsigned long arg) {
    sched_preempt_disable();
    struct task_struct *p;

    p = (struct task_struct *)mm_get_free_page();
    if (!p)
        return -1;

    p->priority = sched_get_current_priority();
    p->state = TASK_RUNNING_STATE;
    p->counter = p->priority;
    p->preempt_count = 1;               // disable preemtion until schedule_tail

    p->cpu_context.x19 = fn;
    p->cpu_context.x20 = arg;
    p->cpu_context.pc = (unsigned long)ret_from_fork;
    p->cpu_context.sp = (unsigned long)p + THREAD_SIZE;

    int ret = sched_add_fork(p);
    if (ret < 0)
        mm_free_page((unsigned long)p);

    sched_preempt_enable();
    return ret;
}
