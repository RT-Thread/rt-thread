/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

/* GCC v850 C names carry a "_" prefix */
OUTPUT_ARCH(v850:rh850)
ENTRY(__start)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 8M
    RAM   (rwx) : ORIGIN = 0xfdc00000, LENGTH = 128K
    CRAM  (rwx) : ORIGIN = 0xfe000000, LENGTH = 0x138000
}

__stack_size = 0x1000;

SECTIONS
{
    .vectors ORIGIN(FLASH) :
    {
        KEEP(*(.vectors))
    } > FLASH

    .text :
    {
        *(.text.startup)
        *(.text .text.*)

        . = ALIGN(4);
        ___fsymtab_start = .;
        KEEP(*(FSymTab))
        ___fsymtab_end = .;

        . = ALIGN(4);
        ___vsymtab_start = .;
        KEEP(*(VSymTab))
        ___vsymtab_end = .;

        . = ALIGN(4);
        ___rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        ___rt_init_end = .;

        . = ALIGN(4);
        ___rt_utest_tc_tab_start = .;
        KEEP(*(UtestTcTab))
        ___rt_utest_tc_tab_end = .;
    } > FLASH

    .rodata :
    {
        *(.rodata .rodata.*)
        *(.rosdata .rosdata.* .rozdata .rozdata.*)
        . = ALIGN(4);
    } > FLASH

    .data : ALIGN(4)
    {
        __data_start = .;
        *(.data .data.*)
        *(.sdata .sdata.* .tdata .tdata.* .zdata .zdata.*)
        . = ALIGN(4);
        __data_end = .;
    } > RAM AT > FLASH
    __data_load = LOADADDR(.data);

    .bss (NOLOAD) : ALIGN(4)
    {
        __bss_start = .;
        *(.bss .bss.*)
        *(.sbss .sbss.* .tbss .tbss.* .zbss .zbss.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
    } > RAM

    .stack (NOLOAD) : ALIGN(8)
    {
        . += __stack_size;
        __stack_top = .;
    } > RAM

    _rh850_heap_start = ORIGIN(CRAM);
    _rh850_heap_end = ORIGIN(CRAM) + LENGTH(CRAM);
}

ASSERT(ADDR(.vectors) == 0, "vectors must be at the reset address 0")
