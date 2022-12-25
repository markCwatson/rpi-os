#include "arm/sysregs.h"

.section ".text.boot"

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
    ldr  x1, =_start         
    mov  sp, x1              // Set stack pointer to _start
    ldr  x1, =__bss_start    // Setup BSS for initializing to zero
    ldr  w2, =__bss_size     
clean_bss:  
    cbz  w2, go_to_main  
    str  xzr, [x1], #8       // Store zero at address of x1 then increment address by 8 (post indexing)
    sub  w2, w2, #1          // Scan through BSS secition until w2=0 then jump to go_to_main
    cbnz w2, clean_bss            

go_to_main:  
    bl   kernel_main         // Call kernel_main in kernel.c
    b    hang