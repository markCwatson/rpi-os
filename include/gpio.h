#pragma once

typedef enum {
    /* GPIO Pin is an input */
    GPIO_FUNC_INPUT = 0,
    /* GPIO Pin is an output */
    GPIO_FUNC_OUTPUT = 1,
    /* GPIO Pin takes alternate function 0 */
    GPIO_ALT_FUNC_0 = 4,
    /* GPIO Pin takes alternate function 1 */
    GPIO_ALT_FUNC_1 = 5,
    /* GPIO Pin takes alternate function 2 */
    GPIO_ALT_FUNC_2 = 6,
    /* GPIO Pin takes alternate function 3 */
    GPIO_ALT_FUNC_3 = 7,
    /* GPIO Pin takes alternate function 4 */
    GPIO_ALT_FUNC_4 = 3,
    /* GPIO Pin takes alternate function 5 */
    GPIO_ALT_FUNC_5 = 2,
    GPIO_ALT_FUNC_MAX
} GpioFunc;

/* For setting pull-up/down resistors on GPIO pin */
typedef enum {
    GPIO_RESISTOR_NONE = 0,
    GPIO_RESISTOR_PULL_UP,
    GPIO_RESISTOR_PULL_DOWN,
    /* Reserved */
    GPIO_RESISTOR_MAX
} GpioResistor;

int gpio_pin_set_function(unsigned int pin_num, GpioFunc func);
int gpio_pin_set_resistor(unsigned int pin_num, GpioResistor res);
