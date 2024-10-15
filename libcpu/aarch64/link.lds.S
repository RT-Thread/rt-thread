/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2017-5-30      bernard      first version
 */

#include "rtconfig.h"

OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)

#ifndef ARCH_TEXT_OFFSET
#define ARCH_TEXT_OFFSET 0x200000   /* We always boot in address where is 2MB aligned */
#endif

#ifndef ARCH_RAM_OFFSET
#define ARCH_RAM_OFFSET 0
#endif

SECTIONS
{
    _text_offset = ARCH_TEXT_OFFSET;

#ifdef RT_USING_SMART
    . = KERNEL_VADDR_START + _text_offset;
#else
    . = ARCH_RAM_OFFSET + _text_offset;
#endif

    .text :
    {
        PROVIDE(__text_start = .);

        KEEP(*(.text.entrypoint))       /* The entry point */
        *(.vectors)
        *(.text)                        /* remaining code */
        *(.text.*)                      /* remaining code */

        *(.rodata)                      /* read-only data (constants) */
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)
        *(.gnu.linkonce.t*)

        /* section information for utest */
        . = ALIGN(8);
        PROVIDE(__rt_utest_tc_tab_start = .);
        KEEP(*(UtestTcTab))
        PROVIDE(__rt_utest_tc_tab_end = .);

        /* section information for finsh shell */
        . = ALIGN(8);
        PROVIDE(__fsymtab_start = .);
        KEEP(*(FSymTab))
        PROVIDE(__fsymtab_end = .);
        . = ALIGN(8);
        PROVIDE(__vsymtab_start = .);
        KEEP(*(VSymTab))
        PROVIDE(__vsymtab_end = .);
        . = ALIGN(8);

        /* section information for modules */
        . = ALIGN(8);
        PROVIDE(__rtmsymtab_start = .);
        KEEP(*(RTMSymTab))
        PROVIDE(__rtmsymtab_end = .);

        /* section information for initialization */
        . = ALIGN(8);
        PROVIDE(__rt_init_start = .);
        KEEP(*(SORT(.rti_fn*)))
        PROVIDE(__rt_init_end = .);

        /* section information for rt_ofw. */
        . = ALIGN(16);
        PROVIDE(__rt_ofw_data_start = .);
        KEEP(*(SORT(.rt_ofw_data.*)))
        PROVIDE(__rt_ofw_data_end = .);
        . = ALIGN(16);

        /* section information for usb usbh_class_info */
        . = ALIGN(4);
        __usbh_class_info_start__ = .;
        KEEP(*(.usbh_class_info))
        . = ALIGN(4);
        __usbh_class_info_end__ = .;

        PROVIDE(__text_end = .);
    }

    .eh_frame_hdr :
    {
        *(.eh_frame_hdr)
        *(.eh_frame_entry)
    }
    .eh_frame : ONLY_IF_RO { KEEP (*(.eh_frame)) }

    . = ALIGN(8);
    .data :
    {
        *(.data)
        *(.data.*)

        *(.data1)
        *(.data1.*)

        . = ALIGN(16);
        _gp = ABSOLUTE(.);     /* Base of small data */

        *(.sdata)
        *(.sdata.*)
        *(.rel.local)
    }

    . = ALIGN(8);
    .ctors :
    {
        PROVIDE(__ctors_start__ = .);
        /* new GCC version uses .init_array */
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE(__ctors_end__ = .);
    }

    .dtors :
    {
        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))
        PROVIDE(__dtors_end__ = .);
    }

    . = ALIGN(16);
    .bss :
    {
        /*
         * We need some free space to page or cpu stack, move .bss.noclean.*
         * to optimize size.
         */
        PROVIDE(__bss_noclean_start = .);
        *(.bss.noclean.*)
        PROVIDE(__bss_noclean_end = .);
        . = ALIGN(8);
        PROVIDE(__bss_start = .);
        *(.bss)
        *(.bss.*)
        *(.dynbss)
        *(COMMON)
        . = ALIGN(8);
        PROVIDE(__bss_end = .);
    }

    /*
     * We should make the bootloader know the size of memory we need,
     * so we MUST calc the image's size with section '.bss'.
     */
    _end = .;

    /* Stabs debugging sections.  */
    .stab          0 : { *(.stab) }
    .stabstr       0 : { *(.stabstr) }
    .stab.excl     0 : { *(.stab.excl) }
    .stab.exclstr  0 : { *(.stab.exclstr) }
    .stab.index    0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment) }
    /* DWARF debug sections.
     * Symbols in the DWARF debugging sections are relative to the beginning
     * of the section so we begin them at 0.  */
    /* DWARF 1 */
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }
    /* GNU DWARF 1 extensions */
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }
    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    /* DWARF 2 */
    .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }
    /* SGI/MIPS DWARF 2 extensions */
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }

    __data_size = SIZEOF(.data);
    __bss_size = SIZEOF(.bss);
}
