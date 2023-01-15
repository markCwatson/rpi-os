#pragma once

#include <stdint.h>

void ret_from_fork(void);
int8_t fork_process(void (*fn)(void), uint32_t arg);
