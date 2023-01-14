#pragma once

#include "arm/base.h"

#define AUX_OFFSET  0x00215000

struct AuxRegs {
    volatile unsigned int irq_status;
    volatile unsigned int enables;
    volatile unsigned int reserved[14];
    volatile unsigned int mu_io;
    volatile unsigned int mu_ier;
    volatile unsigned int mu_iir;
    volatile unsigned int mu_lcr;
    volatile unsigned int mu_mcr;
    volatile unsigned int mu_lsr;
    volatile unsigned int mu_msr;
    volatile unsigned int mu_scratch;
    volatile unsigned int mu_control;
    volatile unsigned int mu_status;
    volatile unsigned int mu_baud_rate;
};

struct AuxRegs *const aux = (struct AuxRegs *)(PBASE + AUX_OFFSET);
