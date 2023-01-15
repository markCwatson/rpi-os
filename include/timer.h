#pragma once

#include <stdint.h>

int8_t timer_init(uint32_t id, uint32_t interval);
void timer_cancel(uint32_t id);
void timer_irq_handler(uint32_t type);
