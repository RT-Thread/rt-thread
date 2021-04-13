/* Define the flash max size */
__max_flash_size = 1024k;

__data_ram_size = 8k;
__stack_ram_size = 4k;
__comm_ram_size = 42k;
__heap_ram_size = 70k;

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
        . = ALIGN(4);
        /* section information for initial */
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;

        . = ALIGN(4);
        PROVIDE(__ctors_start__ = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        PROVIDE(__ctors_end__ = .);

        . = ALIGN(4);
        *save-restore.o (.text* .rodata*)
        *libcpu*cpu*context_gcc.o (.text* .rodata*)
        *libcpu*cpu*interrupt.o (.text* .rodata*)
        *libcpu**.o (.rodata*)

        *components*drivers*misc*pin.o(.text*)
        *components*drivers*misc*adc.o(.text*)

        . = ALIGN(4);
        *src*ipc.o (.text* .rodata*)
        *src*irq.o (.text* .rodata*)
        *src*object.o (.text* .rodata*)
        *src*thread.o (.text* .rodata*)
        *src*timer.o (.text* .rodata*)
        *src*mempool.o (.text* .rodata*)
        *src*scheduler.o (.text* .rodata*)
        *src*clock.o (.text* .rodata*)
        *src*kservice.o (.text* .rodata*)
        *src*device.o (.text* .rodata*)
        *src*idle.o (.text* .rodata*)
        *src*components.o (.text* .rodata*)
    } > ram1 AT > flash

    .comm __comm_vma : {
        . = ALIGN(4);
        KEEP(*(.vector))
        *(.irq*)
        /*applications**.o (.text .rodata)*/
        *hal_libraries*ab32vg1_hal**.o (.text .rodata)
        *(.text.unlikely)
        *(.text.startup)
        *hal_drivers**.o (.rodata)
        *audio*drv_sound.o (.rodata)
        *system_ab32vgx.o (.rodata)
        EXCLUDE_FILE(*lib_a**.o *cp-demangle.o *cp-demangle.o 
        *src*mem.o *src*memheap.o *dfs**.o *components.o *drivers*sdio**.o *cmd.o *msh_file.o
        *drv_sdio.o *drv_wdt.o) *(.rodata.str1.4)
        EXCLUDE_FILE(*lib_a**.o *unwind*.o) *(.srodata)
        *(.rela*)
        *(.data*)
        *(.sdata*)
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
        . = ALIGN(4);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;

        . = ALIGN(4);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;

        . = ALIGN(4);
        *(.text*)
        *(.rodata*)
        *(.srodata*)
        . = ALIGN(512);
    } > flash
}

/* Calc the lma */
__bank_size = SIZEOF(.flash);
__comm_lma = LOADADDR(.comm);
__comm_size = SIZEOF(.comm);
__ram1_lma = LOADADDR(.ram1);
__ram1_size = SIZEOF(.ram1);
