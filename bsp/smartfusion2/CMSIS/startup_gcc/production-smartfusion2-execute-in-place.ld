/*******************************************************************************
 * (c) Copyright 2015 Microsemi SoC Products Group.  All rights reserved.
 * 
 * file name : production-smartfusion2-execute-in-place.ld
 * SmartFusion2 Cortex-M3 linker script for creating a SoftConsole downloadable
 * image executing in SmartFusion2 internal eNVM.
 * 
 * Some current (April 2015) dev kit memory map possibilities are
 * --Type-------Device-----------address start---address end----size---Dbus--RAM IC-------SF2--Comment---------------
 * --eNVM-------M2S010-----------0x60000000------0x6007FFFF-----256KB---------------------010------------------------
 * --eNVM-------M2S090-----------0x60000000------0x6007FFFF-----512KB---------------------090------------------------
 * --eSRAM------M2Sxxx-----------0x20000000------0x2000FFFF-----64KB----------------------xxx--All have same amount--
 * --eSRAM------M2Sxxx-----------0x20000000------0x20013FFF-----80KB----------------------xxx--If ECC/SECDED not used
 * --Fabric-----M2S010-----------0x30000000------0x6007FFFF-----400Kb---------------------010--note-K bits-----------
 * --Fabric-----M2S090-----------0x30000000------0x6007FFFF-----2074Kb--------------------090--note-K bits-----------
 * --LPDDR------STARTER-KIT------0xA0000000------0xA3FFFFFF-----64MB---16--MT46H32M16-----050------------------------
 * --LPDDR------484-STARTER-KIT--0xA0000000------0xA3FFFFFF-----64MB---16--MT46H32M16-----010------------------------
 * --LPDDR------SEC-EVAL-KIT-----0xA0000000------0xA3FFFFFF-----64MB---16--MT46H32M16LF---090--Security eval kit-----
 * --DDR3-------ADevKit----------0xA0000000------0xBFFFFFFF-----1GB----32--MT41K256M8DA---150------------------------
 * --Some older physical memory map possibilities are
 * --Type-------location---------address start---address end----size---Dbus---RAM IC------SF2--Comment--------------
 * --LPDDR------EVAL KIT---------0xA0000000------0xA3FFFFFF-----64MB-=-16--MT46H32M16LF---025--Eval Kit--------------
 * --DDR3-------DevKit-----------0xA0000000------0xAFFFFFFF-----512MB--16--MT41K256M8DA---050------------------------
 *
 * Example linker scripts use lowest practicl values so will work accross dev kits
 * eNVM=256KB  eRAM=64KB  External memory = 64MB  
 *
 * On reset, the eNVM region is mapped to 0x00000000 
 * This is changed below by setting the __smartfusion2_memory_remap variable as required.
 * Options are detailed below.
 *
 * SVN $Revision: 7454 $
 * SVN $Date: 2015-06-08 20:28:07 +0530 (Mon, 08 Jun 2015) $
 */
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
GROUP(-lc -lgcc -lm)
OUTPUT_ARCH(arm)
ENTRY(Reset_Handler)
SEARCH_DIR(.)
__DYNAMIC  =  0;

/*******************************************************************************
 * Start of board customization.
 *******************************************************************************/
MEMORY
{
	/*
	*	In general, example LD scripts use lowest common memory footprint
	*	so will work with all devices.
	*/
	/*
	* WARNING: The words "SOFTCONSOLE", "FLASH", and "USE", the colon ":", and
	*          the name of the type of flash memory are all in a specific order.
	*          Please do not modify that comment line, in order to ensure
	*          debugging of your application will use the flash memory correctly.
	*/
	
	/* SOFTCONSOLE FLASH USE: microsemi-smartfusion2-envm */
	rom (rx)  : ORIGIN = 0x00000000, LENGTH = 256k
	
	/* SmartFusion2 internal eSRAM */
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 64k
}

RAM_START_ADDRESS 	= 0x20000000;     		/* Must be the same value MEMORY region ram ORIGIN above. */
RAM_SIZE 			= 64k;                  /* Must be the same value MEMORY region ram LENGTH above. */
MAIN_STACK_SIZE 	= 4k;               	/* Cortex main stack size. */
MIN_SIZE_HEAP 		= 4k;					/* needs to be calculated for your application */

/*******************************************************************************
 * End of board customization.
 *******************************************************************************/
 
PROVIDE (__main_stack_start = RAM_START_ADDRESS + RAM_SIZE);
PROVIDE (__process_stack_start = __main_stack_start - MAIN_STACK_SIZE);
PROVIDE (_estack = __main_stack_start);
PROVIDE (__mirrored_nvm = 0);   /* Indicate to startup code that NVM is not mirrored to VMA address .text copy is required. */

/*
 * Remap instruction for startup code and debugger:
 *  0: remap eNVM to address 0x00000000
 *  1: remap eSRAM to address 0x00000000
 *  2: remap external DDR memory to address 0x00000000
 */
PROVIDE (__smartfusion2_memory_remap = 0);

SECTIONS
{
  .vector_table :
  {
    __vector_table_load = LOADADDR(.vector_table);
    __vector_table_start = .;
    __vector_table_vma_base_address = .;
    KEEP(*(.isr_vector))
    . = ALIGN(0x10);
    _evector_table = .;
  } >rom
  
  .boot_code : ALIGN(0x10) /* When all code in NVRAM, no requirement for this section- but adds clarity when looking at .lst file */
  {
  	*(.boot_code)
  	. = ALIGN(0x10);
  } >rom
  
  .text : ALIGN(0x10)
  {
    CREATE_OBJECT_SYMBOLS
    __text_load = LOADADDR(.text);
    __text_start = .;
    
    *(.text .text.* .gnu.linkonce.t.*)
    *(.plt)
    *(.gnu.warning)
    *(.glue_7t) *(.glue_7) *(.vfp11_veneer)

    . = ALIGN(0x4);
    /* These are for running static constructors and destructors under ELF.  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*crtend.o(.ctors))
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*crtend.o(.dtors))

    *(.rodata .rodata.* .gnu.linkonce.r.*)

    *(.ARM.extab* .gnu.linkonce.armextab.*)
    *(.gcc_except_table) 
    *(.eh_frame_hdr)
    *(.eh_frame)

    KEEP (*(.vector_table))
    KEEP (*(.init))
    KEEP (*(.fini))

    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    PROVIDE_HIDDEN (__init_array_end = .);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(.fini_array))
    KEEP (*(SORT(.fini_array.*)))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(0x10);
  } >rom
  /* .ARM.exidx is sorted, so has to go in its own output section.  */
   __exidx_start = .;
  .ARM.exidx :
  {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } >rom
  __exidx_end = .;
  _etext = .;

  .data : ALIGN(0x10)
  {
    __data_load = LOADADDR(.data);
    _sidata = LOADADDR (.data);
    __data_start = .;
    _sdata = .;
    KEEP(*(.jcr))
    *(.got.plt) *(.got)
    *(.shdata)
    *(.data .data.* .gnu.linkonce.d.*)
    . = ALIGN(0x10);
    _edata = .;
  } >ram AT>rom

  .bss : ALIGN(0x10)
  {
    __bss_start__ = . ;
    _sbss = .;
    *(.shbss)
    *(.bss .bss.* .gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(0x10);
    __bss_end__ = .;
    _end = .;
    __end = _end;
    _ebss = .;
    PROVIDE(end = .);
  } >ram AT>rom

  .heap : ALIGN(0x10)
  {
    __heap_start__ = .;
    . += MIN_SIZE_HEAP;			/* will generate error if this minimum size not available */
    . += ((ABSOLUTE(RAM_START_ADDRESS) + RAM_SIZE - MAIN_STACK_SIZE) - .); /* assumes stack starts after heap */
    _eheap = .;
  } >ram
  
  .stack : ALIGN(0x10)
  {
    __stack_start__ = .;
    . += MAIN_STACK_SIZE;
    _estack = .;
  } >ram
  
  .stab 0 (NOLOAD) :
  {
    *(.stab)
  }

  .stabstr 0 (NOLOAD) :
  {
    *(.stabstr)
  }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
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
  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
  .ARM.attributes 0 : { KEEP (*(.ARM.attributes)) }
  /DISCARD/ : { *(.note.GNU-stack)  }
}
