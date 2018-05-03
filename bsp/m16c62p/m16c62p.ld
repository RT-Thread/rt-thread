MEMORY
{
  ram (rw) : o = 0x0000400, l = 31k
  rom (rx) : o = 0x00A0000, l = 384k
  nrom(rx) : o = 0x0000F000, l = 4k
  xram(rw) : o = 0x00028000, l = 4k
}

_system_stack_size = 0x800;

SECTIONS
{
	/* Variable Vector Section */
	.var_vects 0x000FA000 :	
	{
		KEEP(*( .var_vects))
	} > rom
	
	.text 0x000DD000 :
	{
		*(.text)
		*(.text.*)

		/* section information for finsh shell */
		. = ALIGN(4);
		___fsymtab_start = .;
		KEEP(*(FSymTab))
		___fsymtab_end = .;
		. = ALIGN(4);
		___vsymtab_start = .;
		KEEP(*(VSymTab))
		___vsymtab_end = .;
		. = ALIGN(4);

		etext = .;
	} > rom
	
	.rodata : 
	{
		_rodata = .;
		*(.rodata)
		*(.rodata.*)	
		*(.frodata)
		_erodata = .;
	} > rom

	.init :
	{
		*(.init)
	} > rom

	.fini :
	{
		*(.fini)
	} > rom

	.got :
	{
		*(.got)
		*(.got.plt)
	} > rom
	
	.eh_frame_hdr :
	{
		*(.eh_frame_hdr)
	} > rom

	.eh_frame :
	{
		*(.eh_frame)
	} > rom

	.jcr :
	{
		*(.jcr)
	} > rom

	.tors :
	{
		__CTOR_LIST__ = .;
		___ctors = .;
		*(.ctors)
		___ctors_end = .;
		__CTOR_END__ = .;
		__DTOR_LIST__ = .;
		___dtors = .;
		*(.dtors)
		___dtors_end = .;
		__DTOR_END__ = .;
		_mdata = .;
	} > rom
	
	.data 0x00000400 : AT (_mdata)
	{
		_data = .;
		*(.data)
		*(.data.*)
		*(.ndata)
		*(.ndata.*)
		*(.plt)
		_edata = .;
	} > ram
	
	.bss :
	{
		_bss = .;
		*(.bss)
		*(COMMON)
		*(.nbss)
		_ebss = .;
		_end = .;
	} > ram

	.gcc_exc :
	{
		*(.gcc_exc)
	} > ram
	
	/* User Stack Pointer */
/*
	.ustack 0x00003000 :
	{
		_ustack = .;
	} > ram
*/

	/* Interrupt Stack Pointer */
	.istack :
	{
		. = . + _system_stack_size;
		. = ALIGN(4);
		_istack = .;
	} > ram

        . = ALIGN(4);
	_user_ram_end = .;
	
	.nrodata 0x0000F000 : 
	{
		_nrodata = .;
		*(.nrodata)
		*(.nrodata.*)
		_enrodata = .;
	} > nrom	
	
	.fdata 0x00028000 : AT (_mdata + SIZEOF(.data))
	{
		_fdata = .;
		*(.fdata)
		*(.fdata.*)
		_efdata = .;
	} > xram
	.fbss :
	{
		_fbss = .;
		*(.fbss)
		*(.fbss.*)
		_efbss = .;
	} > xram

	/* Fixed Vector Section */
	.vects 0x000FFFDC :	
	{
		KEEP(*( .vects))
	} > rom

}