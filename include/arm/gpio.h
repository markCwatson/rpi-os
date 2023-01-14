#pragma once

#include "arm/base.h"

struct GpioPinData {
    volatile unsigned int reserved;
    volatile unsigned int data[2];
};

struct GpioRegs {
    volatile unsigned int func_select[6];
    struct GpioPinData output_set;
    struct GpioPinData output_clear;
    struct GpioPinData level;
    struct GpioPinData ev_detect_status;
    struct GpioPinData re_detect_enable;
    struct GpioPinData fe_detect_enable;
    struct GpioPinData hi_detect_enable;
    struct GpioPinData lo_detect_enable;
    struct GpioPinData async_re_detect;
    struct GpioPinData async_fe_detect;
    volatile unsigned int reserved;
    volatile unsigned int pupd_enable;
    volatile unsigned int pupd_enable_clocks[2];
};

#define GPIO_OFFSET     0x00200000
#define REGS_GPIO       ((struct GpioRegs *)(PBASE + GPIO_OFFSET))
