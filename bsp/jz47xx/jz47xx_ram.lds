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
 * 2010-09-04     bernard      move the beginning entry to 0x80100000
 */

OUTPUT_FORMAT("elf32-tradlittlemips", "elf32-tradlittlemips", "elf32-tradlittlemips")
OUTPUT_ARCH(mips)

MEMORY
{
   /* 16M SDRAM */
   DRAM : ORIGIN = 0x80100000, LENGTH = 0x01000000
   /* 16K SRAM  */
   IRAM : ORIGIN = 0x80000000, LENGTH = 0x00004000
}

ENTRY(_start)
SECTIONS
{
	. = 0x80100000 ;

	.start :
    {
        *(.start);
    } > DRAM

    . = ALIGN(4);

	.text : 
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
    } > DRAM

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
