#pragma once

#include "arm/base.h"

#define GPIO_NUM            58
#define GPIO_NUM_BANKS      3
#define GPIO_OFFSET         0x00200000

struct GpioData {
    volatile unsigned int reserved;
    volatile unsigned int val[2];
};

struct GpioRegs {
    /* GPIO Function Select */
    volatile unsigned int gpfsel[6];
    /* GPIO Pin Output Set */
    struct GpioData gpset;
    /* GPIO Pin Output Clear */
    struct GpioData gpclr;
    /* GPIO Pin Level */
    struct GpioData gplev;
    /* GPIO Pin Event Detect Status */
    struct GpioData gpeds;
    /* GPIO Pin Rising Edge Detect Enable */
    struct GpioData gpren;
    /* GPIO Pin Falling Edge Detect Enable */
    struct GpioData gpfen;
    /* GPIO Pin High Detect Enable */
    struct GpioData gphen;
    /* GPIO Pin Low Detect Enable */
    struct GpioData gplen;
    /* GPIO Pin Async. Rising Edge Detect */
    struct GpioData gparen;
    /* GPIO Pin Async. Falling Edge Detect */
    struct GpioData gpafen;
    /* GPIO Pull-up / Pull-down Registers */
    volatile unsigned int reserved;
    volatile unsigned int gpio_pup_pdn_cntrl_reg[4];
};

struct GpioRegs *const gpio = (struct GpioRegs *)(PBASE + GPIO_OFFSET);
