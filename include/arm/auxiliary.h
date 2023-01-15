#pragma once

#include <stdint.h>
#include "arm/base.h"

#define AUX_OFFSET  0x00215000

struct AuxRegs {
    volatile uint32_t irq_status;
    volatile uint32_t enables;
    volatile uint32_t reserved[14];
    volatile uint32_t mu_io;
    volatile uint32_t mu_ier;
    volatile uint32_t mu_iir;
    volatile uint32_t mu_lcr;
    volatile uint32_t mu_mcr;
    volatile uint32_t mu_lsr;
    volatile uint32_t mu_msr;
    volatile uint32_t mu_scratch;
    volatile uint32_t mu_control;
    volatile uint32_t mu_status;
    volatile uint32_t mu_baud_rate;
};

struct AuxRegs *const aux = (struct AuxRegs *)(PBASE + AUX_OFFSET);
