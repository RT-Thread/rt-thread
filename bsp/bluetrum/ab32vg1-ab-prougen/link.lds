/* Define the flash max size */
__max_flash_size = 768k;

__base = 0x10000000;

__comm_vma = 0x17000;
__max_comm_size = 76k;

MEMORY
{
    init            : org = __base,             len = 512
    flash(rx)       : org = __base + 512,       len = __max_flash_size
    comm(rx)        : org = __comm_vma,         len = __max_comm_size
    data            : org = 0x11000,            len = 16k
    stack           : org = 0x15000,            len = 8k
    aram            : org = 0x50000,            len = 16k
    dram            : org = 0x54000,            len = 12k
    eram            : org = 0x57000,            len = 0xa00
}

SECTIONS
{
    .init : {
        *(.reset)
    } > init

    .comm : {
        KEEP(*(.vector))
        *(.com_text*)
        *(.text*)
        *(.rodata*)
        *(.com_rodata*)
        *(.rela*)
        *(.data*)
	    *(.sdata*)
        LONG(0)
    } > comm AT > flash

    .rti : {
        . = ALIGN(4);
        /* section information for initial */
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;

        . = ALIGN(4);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;

        . = ALIGN(4);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;
    } > comm AT > flash

    .flash : {
        . = ALIGN(512);
    } > flash

    .bss (NOLOAD):
    {
        __bss_start = .;
        *(COMMON)
        *(.bss)
        *(.sbss)
        *(.buf*)
        __bss_end = .;
    } > data
    __bss_size = __bss_end - __bss_start;

    .stack (NOLOAD) : {
        __irq_stack_start = .;
        . = 0x2000;
        __irq_stack = .;
    } > stack
    __irq_stack_size = __irq_stack - __irq_stack_start;

    .code_aecram (NOLOAD): {
        __aram_start = .;
    } > aram

    .code_decram (NOLOAD): {
    } > dram

    .code_encram (NOLOAD): {
        __eram_start = .;
        . = 0xa00;
        __eram_end = .;
    } > eram
}

/* Calc the lma */
__bank_size = SIZEOF(.flash);
__comm_lma = LOADADDR(.comm);
__comm_size = SIZEOF(.comm) + SIZEOF(.rti);
