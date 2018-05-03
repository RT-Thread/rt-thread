OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")

OUTPUT_ARCH(arm)

MEMORY
{
    CODE (rx) : ORIGIN = 0x00000000, LENGTH = 512k /* 512KB flash */
    DATA (rw) : ORIGIN = 0x40000000, LENGTH =  32k /* 32K sram */
}

ENTRY(_start)

_undefined_tack_size = 0x40;
_abort_tack_size = 0x40;
_fiq_tack_size = 0x100;
_irq_tack_size = 0x200;
_svc_tack_size = 0x400;

SECTIONS
{
    . = 0;

    . = ALIGN(4);
    .text : 
    {
        *(.init)
        *(.text)
        *(.rodata)
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)

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

        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;
        . = ALIGN(4);

    } >CODE

    . = ALIGN(4);
    .ctors :
    {
        PROVIDE(__ctors_start__ = .);
        KEEP(*(SORT(.ctors.*)))
        KEEP(*(.ctors))
        PROVIDE(__ctors_end__ = .);
    } > CODE

    .dtors :
    {
        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))
        PROVIDE(__dtors_end__ = .);
    } > CODE

    __end_of_text__ = .;

    /* .ARM.exidx is sorted, so has to go in its own output section.  */
    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)

        /* This is used by the startup in order to initialize the .data secion */
        _sidata = .;
    } > CODE
    __exidx_end = .;

    /* .data section which is used for initialized data */
    .data : AT (_sidata)
    {
        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .data secion */
        _sdata = . ;

        *(.data)
        *(.data.*)
        *(.gnu.linkonce.d*)

        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .data secion */
        _edata = . ;
    } >DATA
    __data_end = .;

    .noinit :
    {
        *(.bss.noinit)
    } > DATA

    .stack : 
    {
        . = ALIGN(4);
        _undefined_stack_base = .;
        . = . + _undefined_tack_size;
        _undefined_stack_top = .;
        
        _abort_stack_base = .;
        . = . + _abort_tack_size;
        _abort_stack_top = .;
        
        _fiq_stack_base = .;
        . = . + _fiq_tack_size;
        _fiq_stack_top = .;
        
        _irq_stack_base = .;
        . = . + _irq_tack_size;
        _irq_stack_top = .;
        
        _svc_stack_base = .;
        . = . + _svc_tack_size;
        _svc_stack_top = .;
    } >DATA

    __bss_start = .;
    .bss :
    {
        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .bss secion */
        _sbss = .;

        *(.bss)
        *(COMMON)

        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .bss secion */
        _ebss = . ;
    } > DATA
    __bss_end = .;

    /* Align here to ensure that the .bss section occupies space up to
    _end.  Align after .bss to ensure correct alignment even if the
    .bss section disappears because there are no input sections.  */
    . = ALIGN(32 / 8);
}
