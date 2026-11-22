OUTPUT_ARCH("riscv")

__STACKSIZE__ = 8192;

MEMORY
{
    DRAM : ORIGIN = 0x40000000, LENGTH = 0x00200000
}

ENTRY(_start)

SECTIONS
{
    . = 0x40000000;

    .start :
    {
        *(.start)
    } > DRAM

    . = ALIGN(8);

    .text :
    {
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.rodata*)
        *(.srodata)
        *(.srodata*)
        . = ALIGN(8);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;
        . = ALIGN(8);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;
        . = ALIGN(8);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;
        . = ALIGN(8);
        __rt_utest_tc_tab_start = .;
        KEEP(*(UtestTcTab))
        __rt_utest_tc_tab_end = .;
        . = ALIGN(8);
        _etext = .;
    } > DRAM

    .data :
    {
        *(.data)
        *(.data.*)
        . = ALIGN(8);
        PROVIDE(__global_pointer$ = . + 0x800);
        *(.sdata)
        *(.sdata.*)
    } > DRAM

    .stack :
    {
        . = ALIGN(16);
        __stack_start__ = .;
        . += __STACKSIZE__;
        __stack_cpu0 = .;
        PROVIDE(__rt_rvstack = .);
        PROVIDE(__stack = .);
        . += __STACKSIZE__;
        __stack_cpu1 = .;
    } > DRAM

    .sbss :
    {
        __bss_start = .;
        *(.sbss)
        *(.sbss.*)
        *(.scommon)
    } > DRAM

    .bss :
    {
        *(.bss)
        *(.bss.*)
        *(COMMON)
        __bss_end = .;
    } > DRAM

    _end = .;
}
