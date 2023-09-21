/*
 * Copyright (c) 2021-2023 HPMicro
 * SPDX-License-Identifier: BSD-3-Clause
 */

ENTRY(_start)

STACK_SIZE = DEFINED(_stack_size) ? _stack_size : 0x4000;
HEAP_SIZE = DEFINED(_heap_size) ? _heap_size : 0x4000;

MEMORY
{
    ILM (wx) : ORIGIN = 0x00020000, LENGTH = 128K
    DLM (w) : ORIGIN = 0x000A0000, LENGTH = 96K
    NONCACHEABLE_RAM (w) : ORIGIN = 0x000B8000, LENGTH = 32K
    SHARE_RAM (w) : ORIGIN = 0x010BC000, LENGTH = 16K
}

SECTIONS
{
    .start : {
        . = ALIGN(8);
        KEEP(*(.start))
    } > ILM

    .vectors : {
        . = ALIGN(8);
        KEEP(*(.isr_vector))
        KEEP(*(.vector_table))
        . = ALIGN(8);
    } > ILM

    .rel : {
        KEEP(*(.rel*))
    } > ILM

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

        KEEP(*(.eh_frame))
        *(.eh_frame*)

        KEEP (*(.init))
        KEEP (*(.fini))

        /* section information for usbh class */
        . = ALIGN(8);
        __usbh_class_info_start__ = .;
        KEEP(*(.usbh_class_info))
        __usbh_class_info_end__ = .;

        . = ALIGN(8);
        PROVIDE (__etext = .);
        PROVIDE (_etext = .);
        PROVIDE (etext = .);
    } > ILM

    .data : AT(etext) {
        . = ALIGN(8);
        __data_start__ = .;
        __global_pointer$ = . + 0x800;
        *(.data)
        *(.data*)
        *(.sdata)
        *(.sdata*)
        *(.tdata)
        *(.tdata*)

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
        KEEP(*crtbegin*.o(.ctors))
        KEEP(*(EXCLUDE_FILE (*crtend*.o) .ctors))
        KEEP(*(SORT(.ctors.*)))
        KEEP(*(.ctors))

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
    } > DLM

    .fast : AT(etext + __data_end__ - __data_start__) {
        . = ALIGN(8);
        PROVIDE(__ramfunc_start__ = .);
        *(.fast)
        . = ALIGN(8);
        PROVIDE(__ramfunc_end__ = .);
    } > ILM

    .bss (NOLOAD) : {
        . = ALIGN(8);
        __bss_start__ = .;
        *(.bss)
        *(.bss*)
        *(.tbss*)
        *(.sbss*)
        *(.scommon)
        *(.scommon*)
        *(.tcommon*)
        *(.dynsbss*)
        *(COMMON)
        . = ALIGN(8);
        _end = .;
        __bss_end__ = .;
    } > DLM

    .framebuffer (NOLOAD) : {
        . = ALIGN(8);
        KEEP(*(.framebuffer))
        . = ALIGN(8);
    } > DLM

    .noncacheable.init : AT(etext + __data_end__ - __data_start__ + __ramfunc_end__ - __ramfunc_start__) {
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

    .sh_mem (NOLOAD) : {
        KEEP(*(.sh_mem))
    } > SHARE_RAM

    .fast_ram (NOLOAD) : {
        KEEP(*(.fast_ram))
    } > DLM

    .heap (NOLOAD) : {
        . = ALIGN(8);
        __heap_start__ = .;
        . += HEAP_SIZE;
        __heap_end__ = .;
    } > DLM

    .stack (NOLOAD) : {
        . = ALIGN(8);
        __stack_base__ = .;
        . += STACK_SIZE;
        . = ALIGN(8);
        PROVIDE (_stack = .);
        PROVIDE (_stack_safe = .);
    } > DLM

    __noncacheable_start__ = ORIGIN(NONCACHEABLE_RAM);
    __noncacheable_end__ = ORIGIN(NONCACHEABLE_RAM) + LENGTH(NONCACHEABLE_RAM);
    __share_mem_start__ = ORIGIN(SHARE_RAM);
    __share_mem_end__ = ORIGIN(SHARE_RAM) + LENGTH(SHARE_RAM);

    ASSERT((STACK_SIZE + HEAP_SIZE) <= 256K, "stack and heap total size larger than 256k")
}
