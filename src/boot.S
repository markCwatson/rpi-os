#include "arm/sysregs.h"
#include "mm.h"

// Define section for Linker
.section ".text.boot"

// Execution begins at the start function
// _start ensures only core0 runs
.global _start
_start:
    mrs  x1, mpidr_el1       // Move Multiprocessor Affinity (system) Register into x1 
    and  x1, x1, #3 
    cbz  x1, setup_el1       // Check processor ID is zero, else hang
hang:  
    wfe                      // Wait for event
    b    hang

// Setup for Exception Level 1 (EL1)
setup_el1:
    ldr	 x0, =SCTLR_VALUE_MMU_DISABLED
    msr	 sctlr_el1, x0		
    ldr	 x0, =HCR_VALUE
    msr	 hcr_el2, x0
    ldr	 x0, =SCR_VALUE
    msr	 scr_el3, x0
    ldr	 x0, =SPSR_VALUE
    msr	 spsr_el3, x0
    adr	 x0, main_core		
    msr	 elr_el3, x0
    eret

main_core:  
    adr x0, __bss_start
    adr x1, __bss_size
    bl mm_zero         

go_to_main:  
    mov	sp, #LOW_MEMORY
    bl   kernel_main         // Call kernel_main in kernel.c
    b    hang
    