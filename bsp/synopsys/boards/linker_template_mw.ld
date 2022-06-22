#define __ASSEMBLY__
#include <target_mem_config.h>

MEMORY {
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

SECTIONS {

	GROUP : {
		.image_head: {
			. = . + IMAGE_HEAD_SIZE;
		}
		.init_bootstrap:{
			_f_init = .;
			*(.init_vector .init_vector.*)
			*(.init_bootstrap .init_bootstrap.*)
			_e_init = .;
		}
		.vector ALIGN(1024): {
			_f_vector = .;
			*(.vector .vector.*)
			_e_vector = .;
		}
	} > REGION_ROM

#if (REGION_XCCM_SIZE != 0)
	GROUP (NOLOAD): {
		.x_ccm ALIGN(8): {
			_f_x_ccm = .;
			*(.x_ccm)
			*(.x_ccm.*)
			_e_x_ccm = .;
		}
	} > REGION_XCCM
#endif

#if (REGION_YCCM_SIZE != 0)
	GROUP (NOLOAD): {
		.y_ccm ALIGN(8): {
			_f_y_ccm = .;
			*(.y_ccm)
			*(.y_ccm.*)
			_e_y_ccm = .;
		}
	} > REGION_YCCM
#endif

	GROUP : {

		.text ALIGN(4): {
			_f_text = .;
			*(TYPE text)
			*(.text*)
			_e_text = .;
		}

		.rodata  ALIGN(4): {
			_f_rodata = .;

			_fctors = .;
			*(.ctors*)
			_ectors = .;
			_fdtors = .;
			*(.dtors*)
			_edtors = .;
			_feh_frame = .;
			*(.eh_frame*)
			_eeh_frame = .;

			*(TYPE lit)

			/* section information for finsh shell */
			. = ALIGN(4);
			__fsymtab_start = .;
			*(FSymTab*)
			__fsymtab_end = .;
			. = ALIGN(4);
			__vsymtab_start = .;
			*(VSymTab*)
			__vsymtab_end = .;

			. = ALIGN(4);
			__rt_init_start = .;
			*(.rti_fn*)
			__rt_init_end = .;
			. = ALIGN(4);

			_e_rodata = .;
		}

	} > REGION_ROM


	GROUP : {
		.data ALIGN(8): {
			_f_data = .;
			_f_sdata = .;
			*(.sdata)
			*(.sbss)
			_e_sdata = .;
			*(TYPE data)
		}
#if defined(EMBARC_UNIT_TEST)
		.unit_test ALIGN(8): {
			_f_embarc_unittest = .;
			KEEP(*(".embarc_unittest"))
			_e_embarc_unittest = .;
		}
#endif
		.tls ALIGN(8): {
			*(.tls*)
			_e_data = .;
		}
	} > REGION_RAM AT > REGION_ROM

	GROUP (NOLOAD) : {
		.bss ALIGN(8): {
			_f_bss = .;
			*(TYPE bss)
			_e_bss = .;
		}
		.stack ALIGN(4) SIZE(_STACKSIZE): {}
		.heap? ALIGN(4) SIZE(_HEAPSIZE): {}
	} > REGION_RAM

	_f_stack = ADDR(.stack);
	_e_stack = ADDR(.stack) + SIZEOF(.stack);
	_f_heap = ADDR(.heap);
	_e_heap = ADDR(.heap) + SIZEOF(.heap);

	_load_addr_text = LOADADDR(.text);
	_load_addr_rodata = LOADADDR(.rodata);
	_load_addr_data = LOADADDR(.data);
}
