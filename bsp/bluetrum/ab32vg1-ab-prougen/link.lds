/* Define the flash max size */
__max_flash_size = 1024k;

__data_ram_size = 8k;
__stack_ram_size = 4k;
__comm_ram_size = 83k;
__heap_ram_size = 29k;

__base = 0x10000000;

__data_vma = 0x11000;
__stack_vma = __data_vma + __data_ram_size;
__comm_vma = __stack_vma + __stack_ram_size;
__heap_vma = __comm_vma + __comm_ram_size;

__ram1_vma = 0x50000;

MEMORY
{
    init            : org = __base,             len = 512
    flash(rx)       : org = __base + 512,       len = __max_flash_size
    comm(rx)        : org = __comm_vma,         len = __comm_ram_size

    data            : org = __data_vma,         len = __data_ram_size
    stack           : org = __stack_vma,        len = __stack_ram_size
    heap            : org = __heap_vma,         len = __heap_ram_size
    ram1(rx)        : org = __ram1_vma,         len = 0x7a00
}

SECTIONS
{
    .init : {
        *(.reset)
    } > init

    .ram1 __ram1_vma : {
        *components*drivers**.o(.text* .rodata*)
        *device.o(.text*)
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
        KEEP (*(.vector))
        EXCLUDE_FILE (*hal_drivers**.o *ab32vg1_hal**.o *components*finsh**.o *components*libc**.o *rt-thread*src**.o *kernel*src**.o *romfs.o *lib_a**.o) *(.text*)
        *idle.o (.text*)
        *ipc.o (.text*)
        *irq.o (.text*)
        *scheduler.o (.text*)
        *timer.o (.text*)
        *kservice.o (.text*)
        EXCLUDE_FILE (*romfs.o *lib_a**.o) *(.rodata*)
        *(.srodata*)
        *(.rela*)
        *(.data*)
	    *(.sdata*)
        . = ALIGN(512);
    } > comm AT > flash

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
        . = __stack_ram_size;
        __irq_stack = .;
    } > stack
    __irq_stack_size = __irq_stack - __irq_stack_start;

    .heap (NOLOAD) : {
        __heap_start = .;
        . = __heap_ram_size;
        __heap_end = .;
    } > heap

    .flash : {
        *(.text*)
        *(.rodata*)
        . = ALIGN(512);
    } > flash
}

/* Calc the lma */
__bank_size = SIZEOF(.flash);
__comm_lma = LOADADDR(.comm);
__comm_size = SIZEOF(.comm);
__ram1_lma = LOADADDR(.ram1);
__ram1_size = SIZEOF(.ram1) + SIZEOF(.rti);
