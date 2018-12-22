/*
 * File      : x1000_ram.lds
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * 2015-12-12     bernard       first version
 */

OUTPUT_FORMAT("elf32-tradlittlemips", "elf32-tradlittlemips", "elf32-tradlittlemips")
OUTPUT_ARCH(mips)

MEMORY
{
   /* 16M SDRAM */
   DRAM : ORIGIN = 0x80800000, LENGTH = 0x01800000
   /* 16K SRAM  */
   IRAM : ORIGIN = 0x80000000, LENGTH = 0x00004000
}

ENTRY(_start)
SECTIONS
{
    .start :
    {
        *(.start);
    } > DRAM

    . = ALIGN(4);

    .text : 
    {
        *(.text)                        /* remaining code */
        *(.text.*)                      /* remaining code */
        *(.rodata)                      /* read-only data (constants) */
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)
        *(.gnu.linkonce.t*)
     
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

        /* section information for initial. */
        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;
        . = ALIGN(4);

        /* section information for modules */
        . = ALIGN(4);
        __rtmsymtab_start = .;
        KEEP(*(RTMSymTab))
        __rtmsymtab_end = .;

        . = ALIGN(4);
        _etext = .;
    } > DRAM

    .eh_frame_hdr : 
    { 
         *(.eh_frame_hdr) 
         *(.eh_frame_entry)
         *(.eh_frame_entry.*)
    } > DRAM
    .eh_frame : ONLY_IF_RO { KEEP (*(.eh_frame)) } > DRAM

    . = ALIGN(4);
    .ctors :
    {
        PROVIDE(__ctors_start__ = .);
        KEEP(*(SORT(.ctors.*)))
        KEEP(*(.ctors))
        PROVIDE(__ctors_end__ = .);
    } > DRAM

    .dtors :
    {
        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))
        PROVIDE(__dtors_end__ = .);
    } > DRAM

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
    } > DRAM

    . = ALIGN(4);
    _iramat = .;

    .iram : AT(_iramat)
    {
        _iramstart = .;
        *(.vectors.1);
        . = 0x100;
        *(.vectors.2);
        . = 0x180;
        *(.vectors.3);
        . = 0x200;
        *(.vectors.4);
        *(.vectors);

        *(.icode);
        *(.irodata);
        *(.idata);
        KEEP(*(.vectors*))
        _iramend = .;
    } > IRAM
    _iramcopy = LOADADDR(.iram);

    .sbss : 
    {
    __bss_start = .;
        *(.sbss)
        *(.sbss.*)
        *(.dynsbss)
        *(.scommon)
    } > DRAM

    .bss :
    {
        *(.bss)
        *(.bss.*)
        *(.dynbss)
        *(COMMON)
    __bss_end = .;
    } > DRAM
    
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
