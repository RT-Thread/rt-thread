INCLUDE memory_regions.ld
MEMORY
{
	RAM (rwx) : ORIGIN = RAM_START, LENGTH = RAM_LENGTH
	RAMCODE (rx) : ORIGIN = RAMCODE_START, LENGTH = RAMCODE_LENGTH
	FLASH (rx) : ORIGIN = FLASH_START, LENGTH = FLASH_LENGTH
	IPDRAM (rwx) : ORIGIN = IPDRAM_START, LENGTH = IPDRAM_LENGTH
	FRAGRAM (rwx) : ORIGIN = FRAGRAM_START, LENGTH = FRAGRAM_LENGTH
	MACHW_MIB (rwx) : ORIGIN = MACHW_MIB_START, LENGTH = MACHW_MIB_LENGTH
}

/* code entry point...need to define to keep crt0 _start out */
ENTRY( Reset_Handler)
/* Library configurations */
GROUP(libgcc.a libc.a libm.a)

SECTIONS
{
	/***** FLASH memory section allocations ******/
	.flash.startof (READONLY) :
	{
		__ddsc_FLASH_START = .;
		__ROM_Start = .;

	}> FLASH
	/* MCU vector table */
	__flash_vectors$$ (READONLY) :
	{
		__flash_vectors$$Base = .; _VECTORS = .;
		PROVIDE(__Vectors = .);
		KEEP(*(.fixed_vectors*))
		KEEP(*(.application_vectors*))
		__Vectors_End = .;
		__flash_vectors$$Limit = .;
	}> FLASH
	__Vectors_Size = __Vectors_End - __flash_vectors$$Base;
	__flash_noinit$$ (NOLOAD) :
	{
		__flash_noinit$$Base = .;
		/* section.flash.noinit */
		*(.flash_noinit)
		__flash_noinit$$Limit = .;
	}> FLASH
	/***** IPDRAM memory section allocations ******/
	.ipdram.startof :
	{
		__ddsc_IPDRAM_START = .;

	}> IPDRAM
	/* ipdram initialized from flash */
	__ipdram_from_flash$$ : ALIGN(4)
	{
		__ipdram_from_flash$$Base = .;__ipdram_from_flash$$Load = LOADADDR(__ipdram_from_flash$$);
		/* section.ipdram.from_flash */
		*(.ipdram_from_flash)
		/* section.ipdram.code_from_flash */
		*(.ipdram_code_from_flash)
		. = ALIGN(4);
		__ipdram_from_flash$$Limit = .;
	}> IPDRAM AT > FLASH
	/* Non-initialized ipdram */
	__ipdram_noinit$$ (NOLOAD) :
	{
		__ipdram_noinit$$Base = .;
		/* section.ipdram.noinit */
		*(.ipdram_noinit)
		__ipdram_noinit$$Limit = .;
	}> IPDRAM
	/* Zeroed ipdram */
	__ipdram_zero$$ (NOLOAD) : ALIGN(4)
	{
		__ipdram_zero$$Base = .;
		/* section.ipdram.zero */
		*(.ipdram)
		. = ALIGN(4);
		__ipdram_zero$$Limit = .;
	}> IPDRAM
	.ipdram.endof ALIGN(.,512) :
	{
		__ddsc_IPDRAM_END = .;

	}> IPDRAM

	/***** FRAGRAM memory section allocations ******/
	.fragram.startof :
	{
		__ddsc_FRAGRAM_START = .;

	}> FRAGRAM
	/* fragram initialized from flash */
	__fragram_from_flash$$ : ALIGN(4)
	{
		__fragram_from_flash$$Base = .;__fragram_from_flash$$Load = LOADADDR(__fragram_from_flash$$);
		/* section.fragram.from_flash */
		*(.fragram_from_flash)
		/* section.fragram.code_from_flash */
		*(.fragram_code_from_flash)
		. = ALIGN(4);
		__fragram_from_flash$$Limit = .;
	}> FRAGRAM AT > FLASH
	/* Non-initialized fragram */
	__fragram_noinit$$ (NOLOAD) :
	{
		__fragram_noinit$$Base = .;
		/* section.fragram.noinit */
		*(.fragram_noinit)
		__fragram_noinit$$Limit = .;
	}> FRAGRAM
	/* Zeroed fragram */
	__fragram_zero$$ (NOLOAD) : ALIGN(4)
	{
		__fragram_zero$$Base = .;
		/* section.fragram.zero */
		*(.fragram)
		. = ALIGN(4);
		__fragram_zero$$Limit = .;
	}> FRAGRAM
	.fragram.endof ALIGN(.,512) :
	{
		__ddsc_FRAGRAM_END = .;

	}> FRAGRAM

	/***** MACHW_MIB memory section allocations ******/
	.machw_mib.startof :
	{
		__ddsc_MACHW_MIB_START = .;

	}> MACHW_MIB
	/* machw_mib initialized from flash */
	__machw_mib_from_flash$$ : ALIGN(4)
	{
		__machw_mib_from_flash$$Base = .;__machw_mib_from_flash$$Load = LOADADDR(__machw_mib_from_flash$$);
		/* section.machw_mib.from_flash */
		*(.machw_mib_from_flash)
		/* section.machw_mib.code_from_flash */
		*(.machw_mib_code_from_flash)
		. = ALIGN(4);
		__machw_mib_from_flash$$Limit = .;
	}> MACHW_MIB AT > FLASH
	/* Non-initialized machw_mib */
	__machw_mib_noinit$$ (NOLOAD) :
	{
		__machw_mib_noinit$$Base = .;
		/* section.machw_mib.noinit */
		*(.machw_mib_noinit)
		__machw_mib_noinit$$Limit = .;
	}> MACHW_MIB
	/* Zeroed machw_mib */
	__machw_mib_zero$$ (NOLOAD) : ALIGN(4)
	{
		__machw_mib_zero$$Base = .;
		/* section.machw_mib.zero */
		*(.machw_mib)
		. = ALIGN(4);
		__machw_mib_zero$$Limit = .;
	}> MACHW_MIB
	.machw_mib.endof ALIGN(.,512) :
	{
		__ddsc_MACHW_MIB_END = .;

	}> MACHW_MIB

	/***** RAM memory section allocations ******/
	.ram.startof :
	{
		__ddsc_RAM_START = .;

	}> RAM
	__ram_dtc_vector$$ (NOLOAD) :
	{
		__ram_dtc_vector$$Base = .;
		*(.fsp_dtc_vector_table)
		__ram_dtc_vector$$Limit = .;
	}> RAM
	/* ram initialized from flash */
	__ram_from_flash$$ : ALIGN(4)
	{
		__ram_from_flash$$Base = .;__ram_from_flash$$Load = LOADADDR(__ram_from_flash$$);
		__data_start__ = .;
		/* section.ram.from_flash */
		*(.ram_from_flash)
		*(.data*)
		*(vtable)
		. = ALIGN(4);
		__data_end__ = .;
		__ram_from_flash$$Limit = .;
	}> RAM AT > FLASH
	__etext = LOADADDR(__ram_from_flash$$);
	/* Main Stack */
	__ram_main_stack$$ (NOLOAD) :
	{
		__ram_main_stack$$Base = .;
		/* section.ram.main_stack */
		*(.bss.g_main_stack)
		__ram_main_stack$$Limit = .;
	}> RAM
	/* Non-initialized ram */
	__ram_noinit$$ (NOLOAD) :
	{
		__ram_noinit$$Base = .;
		/* section.ram.noinit */
		*(.bss.g_heap)
		*(.ram_noinit)
		*(.noinit)
		__ram_noinit$$Limit = .;
	}> RAM
	/* Zeroed ram */
	__ram_zero$$ (NOLOAD) : ALIGN(4)
	{
		__ram_zero$$Base = .;
		__bss_start__ = .;
		/* section.ram.zero */
		*(.ram)
		*(.bss*)
		. = ALIGN(4);
		__bss_end__ = .;
		__ram_zero$$Limit = .;
	}> RAM
	/* Thread Stacks */
	__ram_thread_stack$$ (NOLOAD) : ALIGN(8)
	{
		__ram_thread_stack$$Base = .;
		KEEP(*(.stack?*))
		__ram_thread_stack$$Limit = .;
	}> RAM
	.ram.endof ALIGN(.,512) :
	{
		__ddsc_RAM_END = .;

	}> RAM

	__flash_readonly$$ (READONLY) :
	{
		__flash_readonly$$Base = .;
		/* section.flash.readonly */
		*(.flash)
		/* section.flash.code */
		*(.flash_code)
		*(.text*)
		*(.rodata*)
		KEEP(*(.mcuboot_sce9_key))
		KEEP(*(.version))
		KEEP(*(.init))
		KEEP(*(.fini))

		/* RT-Thread metadata must live in normal flash, not in the MCU vector table. */
		. = ALIGN(4);
		__fsymtab_start = .;
		KEEP(*(FSymTab))
		__fsymtab_end = .;

		. = ALIGN(4);
		__vsymtab_start = .;
		KEEP(*(VSymTab))
		__vsymtab_end = .;

		. = ALIGN(4);
		__rt_utest_tc_tab_start = .;
		KEEP(*(UtestTcTab))
		__rt_utest_tc_tab_end = .;

		. = ALIGN(4);
		__rt_init_start = .;
		KEEP(*(SORT(.rti_fn*)))
		__rt_init_end = .;

		. = ALIGN(4);
		KEEP(*(FalPartTable))
		__flash_readonly$$Limit = .;
	}> FLASH
	__flash_ctor$$ (READONLY) :
	{

		*crtbegin.o(.ctors)
		*crtbegin?.o(.ctors)
		EXCLUDE_FILE (*crtend?.o *crtend.o) *(.ctors)
		*(SORT(.ctors.*))
		*(.ctors)
		*crtbegin.o(.dtors)
		*crtbegin?.o(.dtors)
		EXCLUDE_FILE (*crtend?.o *crtend.o) *(.dtors)
		*(SORT(.dtors.*))
		*(.dtors)

	}> FLASH
	__flash_preinit_array$$ (READONLY) :
	{
		__preinit_array_start = .;
		KEEP(*(.preinit_array))
		__preinit_array_end = .;
	}> FLASH
	__flash_.got$$ (READONLY) :
	{

		*(.got.plt)
		*(.got)

	}> FLASH
	__flash_init_array$$ (READONLY) :
	{
		__init_array_start = .;
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		__init_array_end = .;
	}> FLASH
	__flash_fini_array$$ (READONLY) :
	{
		__fini_array_start = .;
		KEEP(*(SORT(.fini_array.*)))
		KEEP(*(.fini_array))
		__fini_array_end = .;
	}> FLASH
	/* .ARM.extab sections contain exception unwinding information. */
	__flash_arm.extab$$ (READONLY) :
	{

		*(.ARM.extab*)
		*(.gnu.linkonce.armextab.*)

	}> FLASH
	/* .ARM.exidx sections contains index entries for section unwinding. */
	__flash_arm.exidx$$ (READONLY) :
	{
		__exidx_start = .;
		*(.ARM.exidx*)
		*(.gnu.linkonce.armexidx.*)
		__exidx_end = .;
	}> FLASH
	.flash.endof ALIGN(.,512) (READONLY) :
	{
		__ddsc_FLASH_END = .;
		__ROM_End = .;

	}> FLASH

	/***** RAMCODE memory section allocations ******/
	.ramcode.startof (READONLY) :
	{

		. += __ddsc_RAM_END - __ddsc_RAM_START; __ddsc_RAMCODE_START = .;

	}> RAMCODE
	/* ramcode initialized from flash */
	__ramcode_from_flash$$ (READONLY) :
	{
		__ramcode_from_flash$$Base = .;__ramcode_from_flash$$Load = LOADADDR(__ramcode_from_flash$$);
		/* section.ram.code_from_flash */
		*(.ram_code_from_flash)
		*libnosys.a:sbrk.o(.text*)
		*libgcc.a:_aeabi_uldivmod.o(.text*)
		*libgcc.a:_muldi3.o(.text*)
		*libmacsw.a:txl_he.o(.text*)
		*libmacsw.a:txl_cntrl.o(.text*)
		*libmacsw.a:txl_hwdesc.o(.text*)
		*libgcc.a:_dvmd_tls.o(.text*)
		*libgcc.a:bpabi.o(.text*)
		*libgcc.a:_udivdi3.o(.text*)
		*libgcc.a:_clzdi2.o(.text*)
		*libgcc.a:_clzsi2.o(.text*)
		__ramcode_from_flash$$Limit = .;
	}> RAMCODE AT > FLASH
	.ramcode.endof ALIGN(.,512) (READONLY) :
	{
		__ddsc_RAMCODE_END = .;

	}> RAMCODE

}

PROVIDE( __StackLimit = __ram_main_stack$$Base);
PROVIDE( __StackTop = __ram_main_stack$$Limit);
PROVIDE( __StackTopAll = __ram_thread_stack$$Limit);
PROVIDE( __stack = __StackTop);
PROVIDE( __HeapBase = ALIGN(ORIGIN(RAM) + (__ddsc_RAMCODE_END - ORIGIN(RAMCODE)), 8));
PROVIDE( __HeapLimit = ORIGIN(RAM) + LENGTH(RAM));
PROVIDE( __RAM_segment_used_end__ = __HeapBase);
PROVIDE( __bss_start__ = __ram_zero$$Base);
PROVIDE( __bss_end__ = __ram_zero$$Limit);
PROVIDE( end = __HeapBase);
PROVIDE( _end = __HeapBase);
PROVIDE( __end__ = __HeapBase);

ASSERT(__HeapBase <= __HeapLimit, "RAM overflow: no space left for RT-Thread heap");

