OUTPUT_FORMAT("elf32-littleunicore32", "elf32-bigunicore32", "elf32-littleunicore32")
OUTPUT_ARCH(unicore32)
ENTRY(_start)
SEARCH_DIR("/usr/unicore/gnu-toolchain-unicore/uc4-1.0-beta-hard-RHELAS5/unicore32-linux/lib");
SECTIONS
{
	. = 0x00000000;

	. = ALIGN(4);
	.text :
	{
		*(.init)
		*(.text)
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

		/* section information for modules */
		. = ALIGN(4);
		__rtmsymtab_start = .;
		KEEP(*(RTMSymTab))
		__rtmsymtab_end = .;
	}

	. = ALIGN(4);
	.rodata : { *(.rodata) *(.rodata.*) *(.gnu.linkonce.r*) *(.eh_frame) }

	. = ALIGN(4);
	.ctors :
	{
		PROVIDE(__ctors_start__ = .);
		KEEP(*(SORT(.ctors.*)))
		KEEP(*(.ctors))
		PROVIDE(__ctors_end__ = .);
	}

	.dtors :
	{
		PROVIDE(__dtors_start__ = .);
		KEEP(*(SORT(.dtors.*)))
		KEEP(*(.dtors))
		PROVIDE(__dtors_end__ = .);
	}

	. = ALIGN(4);
	.data :
	{
		*(.data)
		*(.data.*)
		*(.gnu.linkonce.d*)
	}

	. = ALIGN(4);
	.nobss : { *(.nobss) }

  /*. = 0x00300000*/
	. = ALIGN(4);
	__bss_start = .;
	.bss : { *(.bss) }
	__bss_end = .;

	/* stabs debugging sections. */
	.stab 0 : { *(.stab) }
	.stabstr 0 : { *(.stabstr) }
	.stab.excl 0 : { *(.stab.excl) }
	.stab.exclstr 0 : { *(.stab.exclstr) }
	.stab.index 0 : { *(.stab.index) }
	.stab.indexstr 0 : { *(.stab.indexstr) }
	.comment 0 : { *(.comment) }
	.debug_abbrev 0 : { *(.debug_abbrev) }
	.debug_info 0 : { *(.debug_info) }
	.debug_line 0 : { *(.debug_line) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	.debug_aranges 0 : { *(.debug_aranges) }

	_end = .;
}
