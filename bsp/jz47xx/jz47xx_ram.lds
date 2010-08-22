/*
 * File      : jz47xx_ram.lds
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-17     swkyer       first version
 * 2010-08-23     bernard      change to jz47xx
 */

ENTRY(_entry)
SECTIONS
{
	.start 0x80000000:
    {
        *(.start);
    }
    
    .text ALIGN(0x4) : 
    {
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
    }
    
	.data ALIGN(0x4) : 
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

	__bss_start = ABSOLUTE(.);
	.sbss : 
  	{
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
 	}
	__bss_end = ABSOLUTE(.);
	
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