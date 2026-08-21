/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-10-15     IronsideZhang     first version
 */


OUTPUT_ARCH( "riscv" )
ENTRY(_start)

MEMORY
{
   SRAM : ORIGIN = 0x80200000, LENGTH = 32M
}

__STACKSIZE__ = 4096;

SECTIONS
{    
    . = 0x80200000;
    
    .text :    {
        
        __text_start = .;
        *(.start)
        . = ALIGN(8);
        
        *(.text)
        *(.text.*)
        . = ALIGN(8);
        
        *(.rodata)
        *(.rodata.*)
        . = ALIGN(8);
        
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
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

        _etext = .;
    } > SRAM 

    __text_end = .;

    /*   
     * LMA (Load Memory Address) 默认等于 VMA (Virtual Memory Address)
     */
    .data :
    {
        . = ALIGN(8);
        __data_start = .;
   
        PROVIDE( __global_pointer$ = . + 0x800 );

        *(.data)
        *(.data.*)
        *(.sdata)
        *(.sdata.*)

        . = ALIGN(8);
        __data_end = .;
    } > SRAM

    /*
     * BSS 段 (未初始化数据)
     */
    .bss :
    {
        . = ALIGN(8);
        __bss_start = .;

        *(.sbss)
        *(.sbss.*)
        *(.scommon)

        *(.bss)
        *(.bss.*)
        *(COMMON)

        . = ALIGN(8);
        __bss_end = .;
    } > SRAM

    /*
     * 初始栈空间定义
     * 阶段一：只为启动核心 (hart 0) 定义一个栈
     * 阶段二 (SMP)：这里会为每个核心定义一个栈
     */
    .stack (NOLOAD) :
    {
        . = ALIGN(16);
        __stack_start__ = .;
        . += __STACKSIZE__;
        __stack_end__ = .;
    } > SRAM

    _end = .;

    /DISCARD/ :
    {
        *(.eh_frame)
        *(.comment)
    }
}