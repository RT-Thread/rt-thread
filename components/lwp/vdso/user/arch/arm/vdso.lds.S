/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2026-04-27     rcitach        init ver.
 */

#include <vdso_constants.h>

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

SECTIONS
{
    PROVIDE(__rt_vdso_data_page = . - (RT_VDSO_DATA_PAGE_COUNT * RT_VDSO_PAGE_SIZE));
    . = SIZEOF_HEADERS;

    .hash           : { *(.hash) } :text
    .gnu.hash       : { *(.gnu.hash) } :text
    .dynsym         : { *(.dynsym) } :text
    .dynstr         : { *(.dynstr) } :text
    .gnu.version    : { *(.gnu.version) } :text
    .gnu.version_d  : { *(.gnu.version_d) } :text
    .gnu.version_r  : { *(.gnu.version_r) } :text
    .dynamic        : { *(.dynamic) } :text :dynamic
    .rodata         : ALIGN(16) { *(.rodata*) } :text
    .text           : ALIGN(16) { *(.text*) } :text

    /DISCARD/ : {
        *(.data .data.* .sdata*)
        *(.bss .bss.* .sbss .sbss.*)
        *(.comment*)
        *(.note*)
        *(.eh_frame*)
        *(.interp)
    }
}

PHDRS
{
    text    PT_LOAD    FLAGS(5) FILEHDR PHDRS;
    dynamic PT_DYNAMIC FLAGS(4);
}

VERSION
{
    LINUX_2.6 {
    global:
        __vdso_clock_gettime;
    local:
        *;
    };
}
