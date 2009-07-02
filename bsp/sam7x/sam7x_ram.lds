OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
MEMORY
{
	DATA (rw) : ORIGIN = 0x00200000, LENGTH = 0x00010000
}
ENTRY(_start)
SECTIONS
{
	.text :
	{
		*(.init)
		*(.text)
	} > DATA = 0

	. = ALIGN(4);
	.rodata :
	{
		*(.rodata)
	} > DATA

	. = ALIGN(4);
	.data : 
	{
		*(.data)
	} > DATA

	. = ALIGN(4);
	__bss_start = .;
	.bss :
	{
		*(.bss)
	} > DATA
	__bss_end = .;

	_end = .;
}
