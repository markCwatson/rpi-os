#pragma once

#include <stdint.h>

int8_t uart_init(void);
char uart_recv(void);
void uart_send(const char c);
void uart_send_string(const char *str);
