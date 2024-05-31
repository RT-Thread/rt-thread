/*
 * Copyright 2021-2023 HPMicro
 * SPDX-License-Identifier: BSD-3-Clause
 */

ENTRY(_start)

STACK_SIZE = DEFINED(_stack_size) ? _stack_size : 0x4000;
HEAP_SIZE = DEFINED(_heap_size) ? _heap_size : 256K;
SDRAM_SIZE = DEFINED(_sdram_size) ? _sdram_size : 16M;
NONCACHEABLE_SIZE = DEFINED(_noncacheable_size) ? _noncacheable_size : 4M;

MEMORY
{
    ILM (wx) : ORIGIN = 0, LENGTH = 256K
    DLM (w) : ORIGIN = 0x80000, LENGTH = 256K
    AXI_SRAM (wx) : ORIGIN = 0x1080000, LENGTH = 1536K
    NONCACHEABLE_RAM (wx) : ORIGIN = 0x40000000 + SDRAM_SIZE - NONCACHEABLE_SIZE, LENGTH = NONCACHEABLE_SIZE
    SDRAM (wx) : ORIGIN = 0x40000000, LENGTH = SDRAM_SIZE - NONCACHEABLE_SIZE
    AHB_SRAM (w) : ORIGIN = 0xF0300000, LENGTH = 32k
    APB_SRAM (w): ORIGIN = 0xF40F0000, LENGTH = 8k
}

SECTIONS
{
    .start : {
        . = ALIGN(8);
        KEEP(*(.start))
    } > AXI_SRAM

    .vectors : {
        . = ALIGN(8);
        KEEP(*(.isr_vector))
        KEEP(*(.vector_table))
        . = ALIGN(8);
    } > AXI_SRAM

    .text : {
        . = ALIGN(8);
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        *(.srodata)
        *(.srodata*)

        *(.hash)
        *(.dyn*)
        *(.gnu*)
        *(.pl*)
        *(FalPartTable)

        KEEP(*(.eh_frame))
        *(.eh_frame*)

        KEEP (*(.init))
        KEEP (*(.fini))
        . = ALIGN(8);

        /*********************************************
         *
         *      RT-Thread related sections - Start
         *
        *********************************************/
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

        /* section information for modules */
        . = ALIGN(4);
        __rtmsymtab_start = .;
        KEEP(*(RTMSymTab))
        __rtmsymtab_end = .;

        /* RT-Thread related sections - end */

        /* section information for usbh class */
        . = ALIGN(8);
        __usbh_class_info_start__ = .;
        KEEP(*(.usbh_class_info))
        __usbh_class_info_end__ = .;

        PROVIDE (__etext = .);
        PROVIDE (_etext = .);
        PROVIDE (etext = .);
    } > AXI_SRAM

    .rel : {
        KEEP(*(.rel*))
    } > AXI_SRAM

    .fast_ram (NOLOAD) : {
        KEEP(*(.fast_ram))
    } > DLM

    .bss(NOLOAD) : {
        . = ALIGN(8);
        __bss_start__ = .;
        *(.bss)
        *(.bss*)
        *(.sbss*)
        *(.scommon)
        *(.scommon*)
        *(.dynsbss*)
        *(COMMON)
        . = ALIGN(8);
        _end = .;
        __bss_end__ = .;
    } > AXI_SRAM

    /* Note: .tbss and .tdata should be adjacent */
    .tbss(NOLOAD) : {
        . = ALIGN(8);
        __tbss_start__ = .;
        *(.tbss*)
        *(.tcommon*)
        _end = .;
        __tbss_end__ = .;
    } > AXI_SRAM

    .tdata : AT(etext) {
        . = ALIGN(8);
        __tdata_start__ = .;
        __thread_pointer = .;
        *(.tdata)
        *(.tdata*)
        . = ALIGN(8);
        __tdata_end__ = .;
    } > AXI_SRAM

    .data : AT(etext + __tdata_end__ - __tdata_start__) {
        . = ALIGN(8);
        __data_start__ = .;
        __global_pointer$ = . + 0x800;
        *(.data)
        *(.data*)
        *(.sdata)
        *(.sdata*)

        KEEP(*(.jcr))
        KEEP(*(.dynamic))
        KEEP(*(.got*))
        KEEP(*(.got))
        KEEP(*(.gcc_except_table))
        KEEP(*(.gcc_except_table.*))

        . = ALIGN(8);
        PROVIDE(__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE(__preinit_array_end = .);

        . = ALIGN(8);
        PROVIDE(__init_array_start = .);
        KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE(__init_array_end = .);

        . = ALIGN(8);
        PROVIDE(__finit_array_start = .);
        KEEP(*(SORT_BY_INIT_PRIORITY(.finit_array.*)))
        KEEP(*(.finit_array))
        PROVIDE(__finit_array_end = .);

        . = ALIGN(8);
        PROVIDE(__ctors_start__ = .);
        KEEP(*crtbegin*.o(.ctors))
        KEEP(*(EXCLUDE_FILE (*crtend*.o) .ctors))
        KEEP(*(SORT(.ctors.*)))
        KEEP(*(.ctors))
        PROVIDE(__ctors_end__ = .);

        . = ALIGN(8);
        KEEP(*crtbegin*.o(.dtors))
        KEEP(*(EXCLUDE_FILE (*crtend*.o) .dtors))
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))

        . = ALIGN(8);
        __data_end__ = .;
        PROVIDE (__edata = .);
        PROVIDE (_edata = .);
        PROVIDE (edata = .);
    } > AXI_SRAM

    .fast : AT(etext + __data_end__ - __tdata_start__) {
        . = ALIGN(8);
        PROVIDE(__ramfunc_start__ = .);
        *(.fast)
        . = ALIGN(8);
        PROVIDE(__ramfunc_end__ = .);
    } > AXI_SRAM

    .noncacheable.init : AT(etext + __data_end__ - __tdata_start__ + __ramfunc_end__ - __ramfunc_start__) {
        . = ALIGN(8);
        __noncacheable_init_start__ = .;
        KEEP(*(.noncacheable.init))
        __noncacheable_init_end__ = .;
        . = ALIGN(8);
    } > NONCACHEABLE_RAM

    .noncacheable.bss (NOLOAD) : {
        . = ALIGN(8);
        KEEP(*(.noncacheable))
        __noncacheable_bss_start__ = .;
        KEEP(*(.noncacheable.bss))
        __noncacheable_bss_end__ = .;
        . = ALIGN(8);
    } > NONCACHEABLE_RAM

    __noncacheable_start__ = ORIGIN(NONCACHEABLE_RAM);
    __noncacheable_end__ = ORIGIN(NONCACHEABLE_RAM) + LENGTH(NONCACHEABLE_RAM);

     .ahb_sram (NOLOAD) : {
        KEEP(*(.ahb_sram))
    } > AHB_SRAM

    .apb_sram (NOLOAD) : {
        KEEP(*(.backup_sram))
    } > APB_SRAM

    .fast_ram (NOLOAD) : {
        KEEP(*(.fast_ram))
    } > DLM

    .stack(NOLOAD) : {
        . = ALIGN(8);
        __stack_base__ = .;
        . += STACK_SIZE;
        PROVIDE (_stack = .);
        PROVIDE (_stack_in_dlm = .);
        PROVIDE (__rt_rvstack = .);
    } > AXI_SRAM

    .framebuffer (NOLOAD) : {
        KEEP(*(.framebuffer))
    } > SDRAM

    .heap (NOLOAD) : {
        . = ALIGN(8);
        __heap_start__ = .;
        . += HEAP_SIZE;
        __heap_end__ = .;

    } > SDRAM
}
