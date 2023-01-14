#pragma once

void ret_from_fork(void);
int fork_process(unsigned long fn, unsigned long arg);
