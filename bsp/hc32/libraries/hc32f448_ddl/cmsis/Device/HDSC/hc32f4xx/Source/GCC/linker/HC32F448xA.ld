/******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 */
/*****************************************************************************/
/*  File        HC32F448xA.ld                                                */
/*  Abstract    Linker script for HC32F448 Device with                       */
/*              128KByte FLASH, 68KByte RAM                                  */
/*  Version     V1.0                                                         */
/*  Date        2023-05-31                                                   */
/*****************************************************************************/

/* Custom defines, according to section 7.7 of the user manual.
   Take OTP sector 16 for example. */
__OTP_DATA_START = 0x03000C00;
__OTP_DATA_SIZE  = 1024;
__OTP_LOCK_START = 0x03000A80;
__OTP_LOCK_SIZE  = 128;

/* Use contiguous memory regions for simple. */
MEMORY
{
    FLASH       (rx): ORIGIN = 0x00000000, LENGTH = 128K
    OTP_DATA    (rx): ORIGIN = __OTP_DATA_START, LENGTH = __OTP_DATA_SIZE
    OTP_LOCK    (rx): ORIGIN = __OTP_LOCK_START, LENGTH = __OTP_LOCK_SIZE
    RAM        (rwx): ORIGIN = 0x1FFF8000, LENGTH = 64K
    RAMB       (rwx): ORIGIN = 0x200F0000, LENGTH = 4K
    QSPI_ROM    (rx): ORIGIN = 0x98000000, LENGTH = 8M
}

ENTRY(Reset_Handler)

SECTIONS
{
    .vectors :
    {
        . = ALIGN(4);
        KEEP(*(.vectors))
        . = ALIGN(4);
    } >FLASH

    .icg_sec 0x00000400 :
    {
        KEEP(*(.icg_sec))
    } >FLASH

    .ex_rom :
    {
        . = ALIGN(4);
        KEEP(*(.ex_rom))
        . = ALIGN(4);
    } >QSPI_ROM

    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.glue_7)
        *(.glue_7t)
        *(.eh_frame)

        KEEP(*(.init))
        KEEP(*(.fini))
        . = ALIGN(4);
    } >FLASH

    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } >FLASH

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } >FLASH

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } >FLASH
    __exidx_end = .;

    .preinit_array :
    {
        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);
        . = ALIGN(4);
    } >FLASH

    .init_array :
    {
        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);
        . = ALIGN(4);
    } >FLASH

    .fini_array :
    {
        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);
        . = ALIGN(4);
    } >FLASH

    __etext = ALIGN(4);

    .otp_data_sec :
    {
        KEEP(*(.otp_data_sec))
    } >OTP_DATA

    .otp_lock_sec :
    {
        KEEP(*(.otp_lock_sec))
    } >OTP_LOCK

    .data : AT (__etext)
    {
        . = ALIGN(4);
        __data_start__ = .;
        *(vtable)
        *(.data)
        *(.data*)
        . = ALIGN(4);
        *(.ramfunc)
        *(.ramfunc*)
        . = ALIGN(4);
        __data_end__ = .;
    } >RAM

    __etext_ramb = __etext + ALIGN (SIZEOF(.data), 4);
    .ramb_data : AT (__etext_ramb)
    {
        . = ALIGN(4);
        __data_start_ramb__ = .;
        *(.ramb_data)
        *(.ramb_data*)
        . = ALIGN(4);
        __data_end_ramb__ = .;
    } >RAMB

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
    } >RAM

    .ramb_bss :
    {
        . = ALIGN(4);
        __bss_start_ramb__ = .;
        *(.ramb_bss)
        *(.ramb_bss*)
        . = ALIGN(4);
        __bss_end_ramb__ = .;
    } >RAMB

    .heap_stack (COPY) :
    {
        . = ALIGN(8);
        __end__ = .;
        PROVIDE(end = .);
        PROVIDE(_end = .);
        *(.heap*)
        . = ALIGN(8);
        __HeapLimit = .;

        __StackLimit = .;
        *(.stack*)
        . = ALIGN(8);
        __StackTop = .;
    } >RAM

    /DISCARD/ :
    {
        libc.a (*)
        libm.a (*)
        libgcc.a (*)
    }

    .ARM.attributes 0 : { *(.ARM.attributes) }

    PROVIDE(_stack = __StackTop);
    PROVIDE(_Min_Heap_Size = __HeapLimit - __HeapBase);
    PROVIDE(_Min_Stack_Size = __StackTop - __StackLimit);

    __RamEnd = ORIGIN(RAM) + LENGTH(RAM);
    ASSERT(__StackTop <= __RamEnd, "region RAM overflowed with stack")
}
