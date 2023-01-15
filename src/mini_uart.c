#include "gpio.h"
#include "utils.h"
#include "arm/auxiliary.h"
#include "mini_uart.h"

#define AUX_UART_TXD            14
#define AUX_UART_RXD            15
#define AUX_UART_CLOCK          500000000 // Hz
#define AUX_UART_BAUD(baud)     ((AUX_UART_CLOCK / (baud * 8)) - 1)

int8_t uart_init(void) {
    int8_t ret;

    ret = gpio_pin_set_resistor(AUX_UART_TXD, GPIO_RESISTOR_NONE);
    ret += gpio_pin_set_function(AUX_UART_TXD, GPIO_ALT_FUNC_5);
    ret += gpio_pin_set_resistor(AUX_UART_RXD, GPIO_RESISTOR_NONE);
    ret += gpio_pin_set_function(AUX_UART_RXD, GPIO_ALT_FUNC_5);
    if (ret < 0)
        return ret;

    aux->enables = 1;
    aux->mu_control = 0;
    aux->mu_ier = 0;
    aux->mu_lcr = 3;
    aux->mu_mcr = 0;
    aux->mu_baud_rate = AUX_UART_BAUD(115200);
    aux->mu_control = 3;
    return 0;
}

void uart_send(const char c) {
    while(!(aux->mu_lsr & 0x20));
    aux->mu_io = c;
}

char uart_recv(void) {
    while(!(aux->mu_lsr & 1));
    return aux->mu_io & 0xFF;
}

void uart_send_string(const char *str) {
    while(*str) {
        if (*str == '\n') {
            uart_send('\r');
        }

        uart_send(*str);
        str++;
    }
}
