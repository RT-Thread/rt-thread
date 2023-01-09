/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-17     swkyer       first version
 * 2010-09-04     bernard      move the beginning entry to 0x80200000
 * 2019-12-04     Jiaxun Yang  Adapt new memory layout
 */

OUTPUT_ARCH(mips)
GROUP(-lgcc -lc)

ENTRY(_start)
SECTIONS
{
    . = 0x80200000;
    .text :
    {
    start = ABSOLUTE(.);
     *(.selfboot);
     *(.selfboot_data);
    . = ALIGN(4);
    __selfboot_end = .;
    . = ALIGN(0x1000);
    __ebase_entry = .;
        KEEP(*(.exc_vectors))
        __ebase_end = .;
     *(.start);
         *(.text)
         *(.text.*)
         *(.rodata)
         *(.rodata.*)
         *(.rodata1)
         *(.rodata1.*)

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
    }

    .eh_frame_hdr :
    {
         *(.eh_frame_hdr)
         *(.eh_frame_entry)
    }
    .eh_frame : ONLY_IF_RO { KEEP (*(.eh_frame)) }

    . = ALIGN(4);
    .data :
    {
         *(.data)
         *(.data.*)

         *(.data1)
         *(.data1.*)

         . = ALIGN(8);
         _gp = ABSOLUTE(.);     /* Base of small data */

         *(.sdata)
         *(.sdata.*)
    }
    _edata = .;

    .stack :
    {
        . = ALIGN(8);
        _system_stack_start = .;
        . = . + 0x400; /* 1kb system stack */
        _system_stack = .;
    }

    .sbss :
    {
        __bss_start = .;
        *(.sbss)
        *(.sbss.*)
        *(.dynsbss)
        *(.scommon)
    }

    .bss :
    {
        *(.bss)
        *(.bss.*)
        *(.dynbss)
        *(COMMON)
        __bss_end = .;
    }
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
}
