SECTIONS
{
    /* Kernel load address for AArch64 */
    . = 0x80000;     

    .text : { 
        /* Startup/boot code (see boot.S) */
        KEEP(*(.text.boot)) 
        /* All Kernel code from all related .o files */
        *(.text .text.* .gnu.linkonce.t*) 
    }

    .rodata : { 
        *(.rodata .rodata.* .gnu.linkonce.r*) 
    }

    PROVIDE(_data = .);

    .data : { 
        *(.data .data.* .gnu.linkonce.d*) 
    }

    .bss (NOLOAD) : {
        . = ALIGN(0x8);
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    }

    _end = .;
}

__bss_size = (__bss_end - __bss_start) >> 3;
