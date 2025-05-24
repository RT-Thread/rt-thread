/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2020-12-12     bernard      first version
 */

#define __ASSEMBLY__

#include "rtconfig.h"

#ifndef __riscv_xlen
#ifdef ARCH_CPU_64BIT
#define __riscv_xlen 64
#else
#define __riscv_xlen 32
#endif
#endif

#include "page_def.h"

OUTPUT_ARCH(riscv)

#ifndef ARCH_TEXT_OFFSET
#if __riscv_xlen == 64
#define ARCH_TEXT_OFFSET 0x200000
#elif __riscv_xlen == 32
#define ARCH_TEXT_OFFSET 0x400000
#else
#error "Unexpected __riscv_xlen"
#endif
#endif

#ifndef ARCH_RAM_OFFSET
#define ARCH_RAM_OFFSET 0
#endif

PHDRS
{
    text PT_LOAD FLAGS(5);   /* PF_R(4) | PF_X(1) = 0x5 (RX) */
    data PT_LOAD FLAGS(6);   /* PF_R(4) | PF_W(2) = 0x6 (RW) */
}

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

        KEEP(*(.text.start))            /* The start point */
        *(.text)                        /* Remaining code */
        *(.text.*)                      /* Remaining code */

        *(.rodata)                      /* Read-only data (constants) */
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)
        *(.gnu.linkonce.t*)

        /* section information for utest */
        . = ALIGN(RISCV_SZPTR);
        PROVIDE(__rt_utest_tc_tab_start = .);
        KEEP(*(UtestTcTab))
        PROVIDE(__rt_utest_tc_tab_end = .);

        /* section information for finsh shell */
        . = ALIGN(RISCV_SZPTR);
        PROVIDE(__fsymtab_start = .);
        KEEP(*(FSymTab))
        PROVIDE(__fsymtab_end = .);
        . = ALIGN(RISCV_SZPTR);
        PROVIDE(__vsymtab_start = .);
        KEEP(*(VSymTab))
        PROVIDE(__vsymtab_end = .);
        . = ALIGN(RISCV_SZPTR);

        /* section information for modules */
        . = ALIGN(RISCV_SZPTR);
        PROVIDE(__rtmsymtab_start = .);
        KEEP(*(RTMSymTab))
        PROVIDE(__rtmsymtab_end = .);

        /* section information for initialization */
        . = ALIGN(RISCV_SZPTR);
        PROVIDE(__rt_init_start = .);
        KEEP(*(SORT(.rti_fn*)))
        PROVIDE(__rt_init_end = .);

        /* section information for rt_ofw. */
        . = ALIGN(RISCV_SZPTR);
        PROVIDE(__rt_ofw_data_start = .);
        KEEP(*(SORT(.rt_ofw_data.*)))
        PROVIDE(__rt_ofw_data_end = .);
        . = ALIGN(RISCV_SZPTR);

        /* section information for usb usbh_class_info */
        . = ALIGN(RISCV_SZPTR);
        __usbh_class_info_start__ = .;
        KEEP(*(.usbh_class_info))
        . = ALIGN(RISCV_SZPTR);
        __usbh_class_info_end__ = .;

        PROVIDE(__text_end = .);
    } :text

    .eh_frame_hdr :
    {
        *(.eh_frame_hdr)
        *(.eh_frame_entry)
    }
    .eh_frame : ONLY_IF_RO { KEEP (*(.eh_frame)) }

    . = ALIGN(RISCV_SZPTR);
    .data :
    {
        *(.data)
        *(.data.*)

        *(.data1)
        *(.data1.*)

        . = ALIGN(ARCH_PAGE_SIZE);
        PROVIDE(__global_pointer$ = . + 0x800);

        *(.sdata)
        *(.sdata.*)

        *(.rel.local)
    } :data

    . = ALIGN(RISCV_SZPTR);
    .ctors :
    {
        PROVIDE(__ctors_start__ = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE(__ctors_end__ = .);
    }

    .dtors :
    {
        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE(__dtors_end__ = .);
    }

    .bss :
    {
        /*
         * We need some free space to page, move .bss.noclean.*
         * to optimize size.
         */
        PROVIDE(__bss_noclean_start = .);
        *(.bss.noclean.*)
        PROVIDE(__bss_noclean_end = .);
        . = ALIGN(RISCV_SZPTR);
        PROVIDE(__bss_start = .);
        *(.bss)
        *(.bss.*)
        *(.sbss)
        *(.sbss.*)
        *(.dynbss)
        *(COMMON)
        . = ALIGN(RISCV_SZPTR);
        PROVIDE(__bss_end = .);
    }

    .percpu (NOLOAD) :
    {
    #if defined(RT_USING_SMP) && defined(ARCH_MM_MMU)
        /* Align for MMU early map */
        . = ALIGN(SUPPER_PAGE_SIZE);
    #endif /* RT_USING_SMP && ARCH_MM_MMU */
        PROVIDE(__percpu_start = .);
        *(.percpu)
    #if defined(RT_USING_SMP) && defined(ARCH_MM_MMU)
        . = ALIGN(ARCH_PAGE_SIZE);
    #endif /* RT_USING_SMP && ARCH_MM_MMU */
        PROVIDE(__percpu_end = .);

        /* Clone the area */
        . = __percpu_end + (__percpu_end - __percpu_start) * (RT_CPUS_NR - 1);
    #if defined(RT_USING_SMP) && defined(ARCH_MM_MMU)
        /* Align for MMU early map */
        . = ALIGN(SUPPER_PAGE_SIZE);
    #endif /* RT_USING_SMP && ARCH_MM_MMU */
        PROVIDE(__percpu_real_end = .);

    #if defined(RT_USING_SMP) && defined(ARCH_MM_MMU)
        ASSERT(((__percpu_real_end - __percpu_start) / ARCH_PAGE_SIZE) <= (ARCH_PAGE_SIZE / RISCV_SZPTR), "Not enough L0 pages to map per-CPU");
    #endif /* RT_USING_SMP && ARCH_MM_MMU */
    }

    /*
     * We should make the bootloader know the size of memory we need,
     * so we MUST calc the image's size with section '.percpu'.
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
