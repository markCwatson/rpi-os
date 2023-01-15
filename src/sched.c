#include "sched.h"
#include "irq.h"
		
#define NR_TASKS            64 

#define FIRST_TASK task[0]
#define LAST_TASK task[NR_TASKS - 1]

#define INIT_TASK                               \
/*cpu_context*/	{ {0,0,0,0,0,0,0,0,0,0,0,0,0},  \
/* state etc */	0,0,1,0                         \
}

static struct task_struct init_task = INIT_TASK;
struct task_struct *current = &init_task;
struct task_struct *task[NR_TASKS] = {&init_task, };
uint8_t nr_tasks = 1;

/*
 * Defined in sched.S to be able to access registers.
 */
extern void cpu_switch_to(struct task_struct *prev, struct task_struct *next);

/*
 * This scheduling algorithm is from Linux 0.0.1, adapted by matyukevich.
 */
static void schedule(void) {
    sched_preempt_disable();
    uint8_t next;
    int32_t max_counter;
    struct task_struct *p;

    while (1) {
        max_counter = -1;
        next = 0;

        // Find the task in TASK_RUNNING state with the max non-zero counter
        for (uint8_t i = 0; i < NR_TASKS; i++) {
            p = task[i];

            if (p && (p->state == TASK_RUNNING_STATE) && (p->counter > max_counter)) {
                max_counter = p->counter;
                next = i;
            }
        }

        // Break and setup the task with max counter that is in the TASK_RUNNING state
        if (max_counter)
            break;

        // If no such task exists: a) no task is in TASK_RUNNING (all waiting for interrupts), or
        //                         b) all counters are zero.
        // Then increment their counters...
        for (uint8_t i = 0; i < NR_TASKS; i++) {
            p = task[i];

            if (p)
                p->counter = (p->counter >> 1) + p->priority;
        }

        // ... and repeat process until interrupt occurs.
    }

    sched_switch_to(task[next]);
    sched_preempt_enable();
}

void sched_preempt_disable(void) {
    current->preempt_count++;
}

void sched_preempt_enable(void) {
    current->preempt_count--;
}

void sched_schedule(void) {
    current->counter = 0;
    schedule();
}

void sched_switch_to(struct task_struct *next) {
    if (current == next) 
        return;

    struct task_struct *prev = current;
    current = next;
    cpu_switch_to(prev, next);
}

void sched_schedule_tail(void) {
    sched_preempt_enable();
}

void sched_timer_tick(void) {
    --current->counter;

    if ((current->counter > 0) || (current->preempt_count > 0))
        return;
    
    current->counter = 0;

    irq_enable();
    schedule();
    irq_disable();
}

int32_t sched_get_current_priority(void) {
    return current->priority;
}

int8_t sched_add_fork(struct task_struct *p) {
    if (nr_tasks++ >= NR_TASKS)
        return -1;

    task[nr_tasks] = p;
    return 0;
}
