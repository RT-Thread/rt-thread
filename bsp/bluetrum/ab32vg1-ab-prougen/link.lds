/* Define the flash max size */
__max_flash_size = 768k;

__comm_ram_size = 104k;
__heap_ram_size = 14k;

__base = 0x10000000;

__comm_vma = 0x12800;
__heap_vma = __comm_vma + __comm_ram_size;

__ram1_vma = 0x50000;

MEMORY
{
    init            : org = __base,             len = 512
    flash(rx)       : org = __base + 512,       len = __max_flash_size
    comm(rx)        : org = __comm_vma,         len = __comm_ram_size

    data            : org = 0x11000,            len = 5k
    stack           : org = 0x12400,            len = 1k
    heap            : org = __heap_vma,         len = __heap_ram_size
    ram1(rx)        : org = __ram1_vma,         len = 0x7a00
}

SECTIONS
{
    .init : {
        *(.reset)
    } > init

    .ram1 __ram1_vma : {
        /*board\\ports\\*.o(.text*)*/
        *hal_drivers\\*.o(.text*)
        *hal_libraries\\ab32vg1_hal\\*.o(.text*)
        *components\\drivers\\*.o(.text* .rodata*)
        *components\\libc\\*.o(.text*)
        *ab32vg1_hal_msp.o(.text*)
        *components.o(.text* .rodata*)
        *ipc.o(.text* .rodata*)
        . = ALIGN(32);
    } > ram1 AT > flash

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

        . = ALIGN(32);
    } > ram1 AT > flash

    .comm : {
        KEEP(*(.vector))
        *(.text*)
        *(.rodata*)
        *(.srodata*)
        *(.rela*)
        *(.data*)
	    *(.sdata*)
        . = ALIGN(512);
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
        . = 0x400;
        __irq_stack = .;
    } > stack
    __irq_stack_size = __irq_stack - __irq_stack_start;

    .heap : {
        __heap_start = .;
        . = __heap_ram_size;
        __heap_end = .;
    } > heap
}

/* Calc the lma */
__bank_size = SIZEOF(.flash);
__comm_lma = LOADADDR(.comm);
__comm_size = SIZEOF(.comm);
__ram1_lma = LOADADDR(.ram1);
__ram1_size = SIZEOF(.ram1) + SIZEOF(.rti);
