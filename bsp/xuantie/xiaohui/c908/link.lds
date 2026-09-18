/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "board/mem_layout.h"

OUTPUT_ARCH( "riscv" )

MEMORY
{
   KERNEL     : ORIGIN = KERNEL_VADDR_START + MEM_PHYS_BASE + MEM_OPENSBI_SIZE, LENGTH = MEM_KERNEL_SIZE
}

/* __STACKSIZE__ comes from rtconfig.h as a preprocessor macro */

ENTRY(_start)
SECTIONS
{
    . = ORIGIN(KERNEL);

    __sram_base = ORIGIN(KERNEL);
    __sram_size = LENGTH(KERNEL);
    __sram_end = __sram_base + __sram_size;

    __text_start = .;
    .start : AT(ADDR(.start) - KERNEL_VADDR_START)
    {
        KEEP(*(.start));
    } > KERNEL

    . = ALIGN(8);

    .text : AT(ADDR(.text) - KERNEL_VADDR_START)
    {
        *(.text)                        /* remaining code */
        *(.text.*)                      /* remaining code */
        *(.rodata)                      /* read-only data (constants) */
        *(.rodata*)
        *(.srodata*)
        *(.glue_7)
        *(.glue_7t)
        *(.gnu.linkonce.t*)

        /* section information for finsh shell */
        . = ALIGN(8);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;
        . = ALIGN(8);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;
        . = ALIGN(8);

        /* section information for initial. */
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
    } > KERNEL

    .eh_frame_hdr : AT(ADDR(.eh_frame_hdr) - KERNEL_VADDR_START)
    {
         *(.eh_frame_hdr)
         *(.eh_frame_entry)
    } > KERNEL
    .eh_frame : AT(ADDR(.eh_frame) - KERNEL_VADDR_START) ONLY_IF_RO { KEEP (*(.eh_frame)) } > KERNEL

    . = ALIGN(8);
    __text_end = .;
    __text_size = __text_end - __text_start;

    .data : AT(ADDR(.data) - KERNEL_VADDR_START)
    {
        *(.data)
        *(.data.*)

        *(.data1)
        *(.data1.*)

        *(.got)
        *(.got.plt)

        . = ALIGN(8);
        PROVIDE( __global_pointer$ = . + 0x800 );

        *(.sdata)
        *(.sdata.*)
    } > KERNEL

    /* stack for dual core */
    .stack : AT(ADDR(.stack) - KERNEL_VADDR_START)
    {
        . = ALIGN(64);
        __stack_start__ = .;

        . += __STACKSIZE__;
        __stack_cpu0 = .;

        . += __STACKSIZE__;
        __stack_cpu1 = .;
    } > KERNEL

    . = ALIGN(8);

    .osdebug : AT(ADDR(.osdebug) - KERNEL_VADDR_START)
    {
        _osdebug_start = .;
        . += 87K;
        _osdebug_end = .;
    } > KERNEL

    . = ALIGN(8);

    .sbss : AT(ADDR(.sbss) - KERNEL_VADDR_START)
    {
        __bss_start = .;
        *(.sbss)
        *(.sbss.*)
        *(.dynsbss)
        *(.scommon)
    } > KERNEL

    .bss : AT(ADDR(.bss) - KERNEL_VADDR_START)
    {
        *(.bss)
        *(.bss.*)
        *(.dynbss)
        *(COMMON)
        __bss_end = .;
    } > KERNEL

#ifdef RT_USING_SMP
    .percpu (NOLOAD) :
    {
        /* 2MB Align for MMU early map */
        . = ALIGN(0x200000);
        PROVIDE(__percpu_start = .);

        *(.percpu)

        /* 2MB Align for MMU early map */
        . = ALIGN(0x200000);

        PROVIDE(__percpu_end = .);

        /* Clone the area */
        . = __percpu_end + (__percpu_end - __percpu_start) * (RT_CPUS_NR - 1);
        PROVIDE(__percpu_real_end = .);
    } > KERNEL
#endif

    _end = .;

    /* Stabs debugging sections.s */
    .stab          0 : { *(.stab) }
    .stabstr       0 : { *(.stabstr) }
    .stab.excl     0 : { *(.stab.excl) }
    .stab.exclstr  0 : { *(.stab.exclstr) }
    .stab.index    0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment) }
    /* DWARF debug sections. */
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }
}
