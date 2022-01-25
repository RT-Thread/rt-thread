/*******************************************************************************
 * Copyright (C) 2017 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2018-12-18 15:37:22 -0600 (Tue, 18 Dec 2018) $ 
 * $Revision: 40072 $
 *
 ******************************************************************************/

MEMORY {
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x00040000 /* 256kB "FLASH" */
	SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00018000
}

OUTPUT_FORMAT ("elf32-littlearm")
ENTRY(Reset_Handler)
EXTERN(__start_c main __stack __section_end_heap)

SECTIONS {

    /* SRAM start/stop addresses used during startup (PreInit(), preinit.S) to initialize ECCEN register
     * and initial Error correcting state. (SEC-DED) */
    __sram_ecc_initialize_start = ORIGIN(SRAM);
    __sram_ecc_initialize_stop = (ORIGIN(SRAM) + LENGTH(SRAM));

    .text : ALIGN(0x100)
    {
        _text = .;
		__section_load_nvic = .;
		KEEP(*(.isr_vector))
		__section_load_nvic_end = .;
        
        KEEP(*startup*(.text))
        *(.text*) /* program code */
        *(.flashprog*) /* Flash program */
        KEEP(*(.init))
        KEEP(*(.fini))
        *(.rodata*)  /* read-only data: "const" */
		KEEP(*(.iota_rom_params))

        /* C++ Exception handling */
        KEEP(*(.eh_frame*))
        _etext = .;
    } > FLASH

  __section_nvic_size = __section_load_nvic_end - __section_load_nvic;
  __section_nvic_start = ORIGIN(SRAM);
  __section_nvic_end = __section_nvic_start + __section_nvic_size;

    /* it's used for C++ exception handling      */
    /* we need to keep this to avoid overlapping */
    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } > FLASH

    .data __section_nvic_end : ALIGN(0x10)
    {
        _data = ALIGN(., 4);
        *(.data*)           /*read-write initialized data: initialized global variable*/
        *(.spix_config*) /* SPIX configuration functions need to be run from SRAM */

        /* These array sections are used by __libc_init_array to call static C++ constructors */
        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);

        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);

        _edata = ALIGN(., 4);
        __section_end_data = .;

    } > SRAM AT>FLASH
    __load_data = LOADADDR(.data);

	/** Info block/OTP reserved area */
  	__virtual_otp_size = 0x400;
  	__virtual_end_otp = ORIGIN(FLASH) + LENGTH(FLASH);
  	__virtual_start_otp = __virtual_end_otp - __virtual_otp_size;


	/** Free area to program application */
  	__virtual_start_iota = ALIGN(__load_data,0x10);
  	__virtual_end_iota = __virtual_start_otp;
  	__virtual_iota_size = __virtual_end_iota - __virtual_start_iota;

  /** Work buffer */
  .iota_work __virtual_start_iota :
  {
  	. += __virtual_iota_size;
  }

  /** OTP area */
  .iota_otp __virtual_start_otp :
  {
  	. += __virtual_otp_size;
  }


    .bss :
    {
        . = ALIGN(4);
        _bss = .;
        *(.bss*)     /*read-write zero initialized data: uninitialzed global variable*/
        *(COMMON)
        _ebss = ALIGN(., 4);
    } > SRAM

    /* Set stack top to end of RAM, and stack limit move down by
     * size of stack_dummy section */

    /* .stack_dummy section doesn't contains any symbols. It is only
     * used for linker to calculate size of stack sections, and assign
     * values to stack symbols later */

	/* Stack and Heap */
  	.heap (NOLOAD) : ALIGN(0x80)
  	{
	    __section_start_heap = .;
		*(.heap*)
    	__section_end_heap = .;

  	} > SRAM

  	__section_start_heap_va = __section_start_heap;
  	__section_end_heap_va = __section_start_heap_va + SIZEOF(.heap);

  	.stack __section_end_heap : ALIGN(0x80)
  	{
	  	__section_start_stack = .;
	    *(.stack*)
	    _stack = .;
	    __section_end_stack = .;

  	} > SRAM
  	__stack_va = __stack;

    PROVIDE(__stack = _stack);

 /* ======================================================================== */
  /** RAM for STP and SCP **/
  __section_protocol_ram_end = (ORIGIN(SRAM) + LENGTH(SRAM));
  __region_end_ram = (ORIGIN(SRAM) + LENGTH(SRAM));

  /** Cryptography work buffer */
  .iota_work.sh __section_end_stack : ALIGN(0x10)
  {
  	KEEP(*(.iota_work.sh))
  } >SRAM=0

  __iota_work_sh_start = LOADADDR(.iota_work.sh);
  __iota_work_sh_end = LOADADDR(.iota_work.sh) + SIZEOF(.iota_work.sh);
  __iota_work_sh_size = SIZEOF(.iota_work.sh);

  /** Configuration Management work buffer */
  .iota_work.cm __iota_work_sh_end : ALIGN(0x10)
  {
  	KEEP(*(.iota_work.cm))
  } >SRAM=0

  __iota_work_cm_start = LOADADDR(.iota_work.cm);
  __iota_work_cm_end = LOADADDR(.iota_work.cm) + SIZEOF(.iota_work.cm);
  __iota_work_cm_size = SIZEOF(.iota_work.cm);

  /** RCE Signature check work buffer */
  .iota_work.rce __iota_work_cm_end : ALIGN(0x10)
  {
	KEEP(*(.iota_work.rce))

  } >SRAM=0

	__iota_work_rce_start = LOADADDR(.iota_work.rce);
	__iota_work_rce_end = LOADADDR(.iota_work.rce) + SIZEOF(.iota_work.rce);
	__iota_work_rce_size = SIZEOF(.iota_work.rce);

  /* ======================================================================== */

  /** STP Application, SCP Applet memory areas */
  .protocol_ram.stack __iota_work_rce_end : ALIGN(0x10)
  {
    __section_protocol_start = .;
  	/** Stack dedicated to STP/SCP application matter if needed */
   	__section_start_stp_stack = .;
   	KEEP(*(.protocol_ram.stack))
	/* . += __stack_size_stp;*/
	__stack_stp = .;

  } >SRAM
	__section_end_stp_stack = .;

  .protocol_ram.bss __section_end_stp_stack : ALIGN(0x10)
  {
    *stp_*(.bss .bss.* .gnu.linkonce.b.*)

  } >SRAM

  __section_start_bss_stp = LOADADDR(.protocol_ram.bss);
  __section_end_bss_stp = LOADADDR(.protocol_ram.bss) + SIZEOF(.protocol_ram.bss);
  __section_bss_stp_size = SIZEOF(.protocol_ram.bss);

  .protocol_ram __section_end_bss_stp : ALIGN(0x10)
  {
	/** Code part */
    KEEP(*stp_*(.data .data.* .gnu.linkonce.d.*))
    KEEP(*(.protocol_ram))

  } >SRAM
  __section_protocol_end = ALIGN(0x10);
  __scp_applet_area_size = __section_protocol_ram_end - __section_protocol_end;

  /** Lasting free internal SRAM space */
  .iota_scp_applet __section_protocol_end : ALIGN(0x10)
  {
    __scp_applet_start = .;
    . += __scp_applet_area_size;
    __scp_applet_end = .;

  } >SRAM

  __section_scp_start = LOADADDR(.protocol_ram);
  __section_scp_stop = LOADADDR(.iota_scp_applet) + SIZEOF(.iota_scp_applet);

  __section_bss_size_stp = __section_end_bss_stp - __section_start_bss_stp;
  __section_stp_size = SIZEOF(.protocol_ram.stack) + SIZEOF(.protocol_ram.bss) + SIZEOF(.protocol_ram);

    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(__StackLimit >= _ebss, "region RAM overflowed with stack")
}
