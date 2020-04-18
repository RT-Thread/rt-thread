#define __ASSEMBLY__
#include <target_mem_config.h>

MEMORY
{
#if (REGION_ICCM_SIZE != 0)
	REGION_ICCM :		ORIGIN = REGION_ICCM_START,	LENGTH = REGION_ICCM_SIZE
#endif
#if (REGION_DCCM_SIZE !=0)
	REGION_DCCM :		ORIGIN = REGION_DCCM_START,	LENGTH = REGION_DCCM_SIZE
#endif
#if (REGION_XCCM_SIZE != 0)
	REGION_XCCM :		ORIGIN = REGION_XCCM_START,	LENGTH = REGION_XCCM_SIZE
#endif
#if (REGION_YCCM_SIZE != 0)
	REGION_YCCM :		ORIGIN = REGION_YCCM_START,	LENGTH = REGION_YCCM_SIZE
#endif
#if (REGION_EXT_ROM_SIZE != 0)
	REGION_EXT_ROM :	ORIGIN = REGION_EXT_ROM_START,	LENGTH = REGION_EXT_ROM_SIZE
#endif
#if (REGION_EXT_RAM_SIZE != 0)
	REGION_EXT_RAM :	ORIGIN = REGION_EXT_RAM_START,	LENGTH = REGION_EXT_RAM_SIZE
#endif
}

ENTRY(_start)

SECTIONS
{
	.init :
	{
		. = . + IMAGE_HEAD_SIZE;
		_f_init = .;
		KEEP (*(.init_vector .init_vector.*))
		KEEP (*(.init_bootstrap .init_bootstrap.*))
		_e_init = .;
	} > REGION_ROM

	.vector : ALIGN(1024)
	{
		_f_vector = .;
		*(.vector .vector.*)
		_e_vector = .;
	} > REGION_ROM

#if (REGION_XCCM_SIZE != 0)
	.x_ccm (NOLOAD) : ALIGN(8)
	{
		_f_x_ccm = .;
		*(.x_ccm .x_cmm.*)
		_e_x_ccm = .;
	} > REGION_XCCM
#endif

#if (REGION_YCCM_SIZE != 0)
	.y_ccm (NOLOAD) : ALIGN(8)
	{
		_f_y_ccm = .;
		*(.y_ccm .y_ccm.*)
		_e_y_ccm = .;
	} > REGION_YCCM
#endif
	.text : ALIGN(4)
	{
		_f_text = .;
		*(.text .text.* .gnu.linkonce.t.*)
		_e_text = .;
	} > REGION_ROM

	.rodata : ALIGN(4)
	{
		_f_rodata = .;

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
		__rt_init_start = .;
		KEEP(*(SORT(.rti_fn*)))
		__rt_init_end = .;
		. = ALIGN(4);

		. = ALIGN(4);
		__CTOR_LIST__ = .;
		LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2)
		KEEP(*(SORT_BY_NAME(".ctors*")))
		LONG(0)
		__CTOR_END__ = .;

		. = ALIGN(4);
		__init_array_start = .;
		KEEP(*(SORT_BY_NAME(".init_array*")))
		__init_array_end = .;

		. = ALIGN(4);
		__DTOR_LIST__ = .;
		LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2)
		KEEP(*(SORT_BY_NAME(".dtors*")))
		LONG(0)
		__DTOR_END__ = .;

		*(.rodata .rodata.* .gnu.linkonce.r.*)
		_e_rodata = .;
	} > REGION_ROM

	.data : ALIGN(4)
	{
		_f_data = .;
		*(.data .data.* .gnu.linkonce.d.*)
		_f_sdata = .;
		__SDATA_BEGIN__ = .;
		*(.sdata .sdata.* .gnu.linkonce.s.*)
		PROVIDE (__sbss_start = .);
		PROVIDE (___sbss_start = .);
		_f_sbss = .;
		*(.dynsbss)
		*(.sbss .sbss.* .gnu.linkonce.sb.*)
		*(.scommon)
		_e_sbss = .;
		PROVIDE (__sbss_end = .);
		PROVIDE (___sbss_end = .);
#if defined(EMBARC_UNIT_TEST)
		. = ALIGN(8);
		_f_embarc_unittest = .;
		KEEP(*(.embarc_unittest))
		_e_embarc_unittest = .;
#endif
		_e_sdata = .;
		_e_data = .;
	} > REGION_RAM AT > REGION_ROM

	.bss (NOLOAD) : ALIGN(8)
	{
		_f_bss = .;
		*(.dynbss)
		*(.bss .bss.* .gnu.linkonce.b.*)
		*(COMMON)
		_e_bss = .;
	} > REGION_RAM

	.stack (NOLOAD) :
	{
		. = ALIGN(4);
		_f_stack = .;
		. = . + _STACKSIZE;
		_e_stack = .;
	} > REGION_RAM

	.heap (NOLOAD) :
	{
		. = ALIGN(4);
		__start_heap = . ;
		_f_heap = .;
		. = . + _HEAPSIZE;
		_e_heap = .;
		__end_heap = . ;
	} > REGION_RAM

	_load_addr_text = LOADADDR(.text);
	_load_addr_rodata = LOADADDR(.rodata);
	_load_addr_data = LOADADDR(.data);
}
