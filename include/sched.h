#ifndef _SCHED_H
#define _SCHED_H

#define CPU_CONTEXT_OFFSET  0 

#ifndef __ASSEMBLER__

struct cpu_context {
    unsigned long x19;
    unsigned long x20;
    unsigned long x21;
    unsigned long x22;
    unsigned long x23;
    unsigned long x24;
    unsigned long x25;
    unsigned long x26;
    unsigned long x27;
    unsigned long x28;
    unsigned long fp;
    unsigned long sp;
    unsigned long pc;
};

struct task_struct {
    struct cpu_context cpu_context;
    long state;	
    long counter;
    long priority;
    long preempt_count;
};

void sched_init(void);
void sched_preempt_disable(void);
void sched_preempt_enable(void);
void sched_schedule(void);
void sched_timer_tick(void);
void sched_switch_to(struct task_struct *next);

#endif
#endif