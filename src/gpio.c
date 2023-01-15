#include "gpio.h"
#include "arm/gpio.h"
#include "utils.h"

int8_t gpio_pin_set_function(uint8_t pin_num, GpioFunc func) {
    if (pin_num >= GPIO_NUM)
        return -1;

    if (func >= GPIO_ALT_FUNC_MAX)
        return -2;

    /* Limit start bit to values 0, 3, 6, ..., 27*/
    uint8_t start_bit = (pin_num * 3) % 30;
    /* Limit index to 0 to 5*/
    uint8_t index = pin_num / 10;

    volatile uint8_t selector = gpio->gpfsel[index];
    /* Clear the three function bits */
    selector &= ~(7 << start_bit);
    /* Set the three function bits per caller */
    selector |= (func << start_bit);
    gpio->gpfsel[index] = selector;
    return 0;
}

int8_t gpio_pin_set_resistor(uint8_t pin_num, GpioResistor res) {
    if (pin_num >= GPIO_NUM)
        return -1;

    if (res >= GPIO_RESISTOR_MAX)
        return -2;

    /* Limit start bit to values 0, 2, 4, ..., 30*/
    uint8_t start_bit = (pin_num * 2) % 32;
    /* Limit index to 0 to 3*/
    uint8_t index = pin_num / 16;

    volatile uint8_t selector = gpio->gpio_pup_pdn_cntrl_reg[index];
    /* Clear the 2 function bits */
    selector &= ~(3 << start_bit);
    /* Set the 2 function bits per caller */
    selector |= (res << start_bit);
    gpio->gpio_pup_pdn_cntrl_reg[index] = selector;
    return 0;
}
