/*
 * linker script for GD32E230x with GNU ld
 * Adapted from GD32E50x version.
 * Corrected by Gemini to fix oversized .bin file and subsequent linker errors.
 */

MEMORY
{
    /* 
     * IMPORTANT: Please check your specific chip's datasheet for correct memory sizes.
     * The following values are for a GD32E230 with 64KB Flash and 8KB SRAM.
     */
    CODE (rx) : ORIGIN = 0x08000000, LENGTH = 64k /* MODIFIED: 64KB flash */
    DATA (rw) : ORIGIN = 0x20000000, LENGTH = 8k  /* MODIFIED: 8KB sram */
}

/* Program Entry, set to mark it as "used" and avoid gc */
ENTRY(Reset_Handler)

/* 
 * Define the size of the stack used by the system. 
 * This is for the main stack pointer (MSP), used before RT-Thread scheduler starts and in interrupts.
 * Increased to 1KB for safety.
 */
_system_stack_size = 0x400; /* MODIFIED: 1024 bytes */

SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        _stext = .;
        KEEP(*(.isr_vector))            /* Startup code */
        . = ALIGN(4);
        *(.text)                        /* remaining code */
        *(.text.*)                      /* remaining code */
        *(.rodata)                      /* read-only data (constants) */
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)
        *(.gnu.linkonce.t*)

        /* section information for finsh shell */
        . = ALIGN(4);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;
        . = ALIGN(4);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;
        . = ALIGN(4);

        /* section information for initial. */
        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;
        . = ALIGN(4);

        . = ALIGN(4);
        _etext = .;
    } > CODE

    /* 
     * The .ARM.exidx section is needed for exception handling and stack unwinding.
     * It should be placed in a loadable region like CODE.
     */
    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > CODE
    
    /*
     * Define the load address for the .data section.
     * It should immediately follow the .ARM.exidx section in Flash.
     */
    _sidata = __exidx_end;

    /* .data section which is used for initialized data */
    .data : AT (_sidata)
    {
        . = ALIGN(4);
        _sdata = . ;
        *(.data)
        *(.data.*)
        *(.gnu.linkonce.d*)
        . = ALIGN(4);
        _edata = . ;
    } > DATA

    /* Main stack, located at the top of the RAM region */
    .stack (NOLOAD):
    {
        . = ALIGN(8);
        _sstack = .;
        . = . + _system_stack_size;
        . = ALIGN(8);
        _estack = .;
    } > DATA

    /* .bss section which is used for uninitialized data */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = . ;
    } > DATA

    /* Define __bss_end for C code to find the heap start. */
    __bss_end = _ebss;

    _end = .;
    
    /******************************************************************************
     * Corrected section to discard unwanted information from the final binary. *
     ******************************************************************************/
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )

        /* Discard all debugging and comment sections using the correct wildcard syntax */
        *(.comment)
        *(.debug*)
        *(.line)
        *(.stab)
        *(.stabstr)
        *(.note.gnu.build-id)
        *(.ARM.attributes)
    }
}