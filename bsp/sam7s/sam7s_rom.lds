OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
MEMORY
{
	CODE (rx) : ORIGIN = 0x00000000, LENGTH = 0x00010000
	DATA (rw) : ORIGIN = 0x00200000, LENGTH = 0x00004000
}
ENTRY(_start)
SECTIONS
{
	.text :
	{
		*(.init)
		*(.text)
	} > CODE = 0

	. = ALIGN(4);
	.rodata :
	{
		*(.rodata .rodata.*)
	} > CODE

	_etext = . ;
	PROVIDE (etext = .);

	/* .data section which is used for initialized data */

	.data : AT (_etext)
	{
		_data = . ;
		*(.data)
		SORT(CONSTRUCTORS)
	} >DATA
	. = ALIGN(4);

	_edata = . ;
	PROVIDE (edata = .);

	. = ALIGN(4);
	__bss_start = .;
	.bss :
	{
		*(.bss)
	} > DATA
	__bss_end = .;

	_end = .;
}
