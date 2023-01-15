/* Entry point for the kernel image. That symbol was declared in the boot.S file
 * Since we are actually booting a binary image, the entry is completely irrelevant, 
 * but it has to be there in the elf file we build as intermediate file. */
ENTRY(_start)

SECTIONS
{
    /* Kernel load address for AArch64 */
    /* Starts at LOADER_ADDR. */
    . = 0x80000; 
    __start = .;

    /* Text (code) section */
    __text_start = .;    
    .text : { 
        /* Startup/boot code (see boot.S) */
        /* Put at the beginning of the kernel image */
        KEEP(*(.text.boot)) 
        /* All Kernel code from all related .o files */
        *(.text .text.* .gnu.linkonce.t*) 
    }
    /* align to page size */
    . = ALIGN(4096);
    __text_end = .;

    /* Read-only data section */
    __rodata_start = .;
    .rodata : { 
        *(.rodata .rodata.* .gnu.linkonce.r*) 
    }
    . = ALIGN(4096);
    __rodata_end = .;

    /* Read-write data section */
    __data_start = .;
    .data : { 
        *(.data .data.* .gnu.linkonce.d*) 
    }
    . = ALIGN(4096);
    __data_end = .;

    /* Initialized to zero section */
    __bss_start = .;
    .bss (NOLOAD) : {
        bss = .;
        *(.bss .bss.*)
    }
    . = ALIGN(4096);
    __bss_end = .;
    __bss_size = __bss_end - __bss_start;

    __end = .;
    __kernel_image_size = __start - __end;
}
