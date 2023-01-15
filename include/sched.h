#pragma once

#define CPU_CONTEXT_OFFSET  0 
#define TASK_RUNNING_STATE  0
#define THREAD_SIZE         4096

#ifndef __ASSEMBLER__

#include <stdint.h>

struct cpu_context {
    uint64_t x19;
    uint64_t x20;
    uint64_t x21;
    uint64_t x22;
    uint64_t x23;
    uint64_t x24;
    uint64_t x25;
    uint64_t x26;
    uint64_t x27;
    uint64_t x28;
    uint64_t fp;
    uint64_t sp;
    uint64_t pc;
};

struct task_struct {
    struct cpu_context cpu_context;
    int32_t state;	
    int32_t counter;
    int32_t priority;
    int32_t preempt_count;
};

void sched_init(void);
void sched_preempt_disable(void);
void sched_preempt_enable(void);
void sched_schedule(void);
void sched_timer_tick(void);
void sched_switch_to(struct task_struct *next);
int32_t sched_get_current_priority(void);
int8_t sched_add_fork(struct task_struct *p);

#endif
