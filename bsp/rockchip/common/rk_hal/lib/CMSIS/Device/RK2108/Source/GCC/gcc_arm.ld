/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2019-2021 Rockchip Electronics Co., Ltd.
 */

MEMORY
{
    FLASH  (rx)  : ORIGIN = 0x18000000, LENGTH = 16M  /* Nor Flash */
    SRAM_I (rx)  : ORIGIN = 0x04000000, LENGTH = 1M   /* SRAM */
    SRAM_D (rxw) : ORIGIN = 0x20000000, LENGTH = 1M   /* SRAM */
}

MAIN_STACK_SIZE     = 0x400;

ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {
        . = ALIGN(32);
        KEEP(*(.vectors))
        . = ALIGN(32);

        *(.text*)
        KEEP(*(.init))
        KEEP(*(.fini))
        *(.rodata*)

        KEEP(*(.eh_frame*))
    } > SRAM_I

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > SRAM_I

    .ARM.exidx   :
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > SRAM_I

    .ctors :
    {
        . = ALIGN(32);
        PROVIDE(__ctors_start__ = .);
        KEEP(*(SORT(.ctors.*)))
        KEEP(*(.ctors))
        . = ALIGN(32);
        PROVIDE(__ctors_end__ = .);
    } > SRAM_I

    .dtors :
    {
        . = ALIGN(32);
        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))
        . = ALIGN(32);
        PROVIDE(__dtors_end__ = .);
    } > SRAM_I

    .copy.table :
    {
        . = ALIGN(32);
        PROVIDE(__copy_table_start__ = .);
        LONG (__etext)
        LONG (__data_start__)
        LONG ((__data_end__ - __data_start__) / 4)
        PROVIDE(__copy_table_end__ = .);
    } > SRAM_I

    .zero.table :
    {
        . = ALIGN(32);
        PROVIDE(__zero_table_start__ = .);
        LONG (__bss_start__)
        LONG ((__bss_end__ - __bss_start__) / 4)
        PROVIDE(__zero_table_end__ = .);
    } > SRAM_I

/**
 * Location counter can end up 2byte aligned with narrow Thumb code but
 * __etext is assumed by startup code to be the LMA of a section in RAM
 * which must be 4byte aligned. In addition, 32byte cacheline alignment
 * is required here, because of RK2108 with cache.
 */
    __etext = ALIGN (32);

    SRAM_DATA_DEST = ORIGIN(SRAM_D) + __etext - ORIGIN(SRAM_I);

    .data SRAM_DATA_DEST : AT (__etext)
    {
        __data_start__ = ALIGN (32);
        *(vtable)
        *(.data)
        *(.data.*)

        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);

        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);

        KEEP(*(.jcr*))
        . = ALIGN(4);
        _gp = ABSOLUTE(.);     /* Base of small data */

        . = ALIGN(32);
        /* All data end */
        __data_end__ = .;
    } > SRAM_D

    .bss :
    {
        . = ALIGN(32);
        __bss_start__ = .;
        *(.bss)
        *(.bss.*)
        *(.dynbss)
        *(COMMON)
        . = ALIGN(32);
        __bss_end__ = .;
    } > SRAM_D

    .stack :
    {
        . = ALIGN(32);
        __StackLimit = .;
        . = . + MAIN_STACK_SIZE;
        . = ALIGN(32);
        __StackTop = .;
        __stack = __StackTop;
    } > SRAM_D

    .heap :
    {
        . = ALIGN(32);
        __end__ = .;
        PROVIDE(end = .);
        . = ORIGIN(SRAM_D) + LENGTH(SRAM_D);
        __HeapLimit = .;
    } > SRAM_D
}
