/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     gcc_csky.h
 * @brief    csky linker file for PHOBOS
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
MEMORY
{
    I-SRAM : ORIGIN = 0x0        , LENGTH = 0x40000   /* I-SRAM  256KB */
    D-SRAM : ORIGIN = 0x20000000 , LENGTH = 0xc0000   /* D-SRAM  768KB */
    O-SRAM : ORIGIN = 0x50000000 , LENGTH = 0x800000   /* off-chip SRAM 8MB */
    SRAM   : ORIGIN = 0x60000000 , LENGTH = 0x20000   /* on-chip SRAM 128KB */
}

PROVIDE (__StackTop = 0x200c0000 - 0x8);
PROVIDE (Stack_Size = 0x1000);

REGION_ALIAS("REGION_TEXT",    I-SRAM);
REGION_ALIAS("REGION_RODATA",  I-SRAM);
REGION_ALIAS("REGION_CUSTOM1", D-SRAM);
REGION_ALIAS("REGION_CUSTOM2", D-SRAM);
REGION_ALIAS("REGION_DATA",    D-SRAM);
REGION_ALIAS("REGION_BSS",     D-SRAM);

ENTRY(Reset_Handler)
SECTIONS
{
  .text : AT(ADDR(.text)){
  . = ALIGN(0x4) ;
  __stext = . ;
  KEEP(*startup.o(*.text*))
  *(.text)
  *(.text*)
  *(.text.*)
  *(.gnu.warning)
  *(.stub)
  *(.gnu.linkonce.t*)
  *(.glue_7t)
  *(.glue_7)
  *(.jcr)
  *(.init)
  *(.fini)
  . = ALIGN (4) ;
  PROVIDE(__ctbp = .);
  *(.call_table_data)
  *(.call_table_text)

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

	/* section information for initial. */
	. = ALIGN(4);
	__rt_init_start = .;
	KEEP(*(SORT(.rti_fn*)))
	__rt_init_end = .;
	. = ALIGN(4);
  . = ALIGN(0x10) ;
  __etext = . ;
 } > REGION_TEXT
 .eh_frame_hdr : {
  *(.eh_frame_hdr)
 } > REGION_TEXT
 .eh_frame : ONLY_IF_RO {
  KEEP (*(.eh_frame))
 } > REGION_TEXT
 .gcc_except_table : ONLY_IF_RO {
  *(.gcc_except_table .gcc_except_table.*)
 } > REGION_TEXT
 .rodata :{
  . = ALIGN(0x4) ;
  __srodata = .;
  *(.rdata)
  *(.rdata*)
  *(.rdata1)
  *(.rdata.*)
  *(.rodata)
  *(.rodata1)
  *(.rodata*)
  *(.rodata.*)
  *(.rodata.str1.4)
  . = ALIGN(0x4) ;
  __ctor_start__ = .;
  KEEP (*(SORT(.ctors.*)))
  KEEP (*(.ctors))
  __ctor_end__ = .;
  KEEP (*(SORT(.dtors.*)))
  KEEP (*(.dtors))
  __dtor_end__ = .;
  . = ALIGN(0x4) ;
  __erodata = .;
  __rodata_end__ = .;
 } > REGION_RODATA
 .data : {
  . = ALIGN(0x4) ;
  __sdata = . ;
  __data_start__ = . ;
  data_start = . ;
  KEEP(*startup.o(*.vectors*))
  *(.got.plt)
  *(.got)
  *(.gnu.linkonce.r*)
  *(.data)
  *(.data*)
  *(.data1)
  *(.data.*)
  *(.gnu.linkonce.d*)
  *(.data1)
  *(.gcc_except_table)
  *(.gcc_except_table*)
  __start_init_call = .;
  *(.initcall.init)
  __stop_init_call = .;
  __start_cmd = .;
  *(.bootloaddata.cmd)
  . = ALIGN(4) ;
  __stop_cmd = .;
  __global_pointer$ = .;
  *(.sdata)
  *(.sdata.*)
  *(.gnu.linkonce.s.*)
  *(__libc_atexit)
  *(__libc_subinit)
  *(__libc_subfreeres)
  *(.note.ABI-tag)
  __edata = .;
  __data_end__ = .;
  . = ALIGN(0x4) ;

 } > REGION_DATA AT > REGION_RODATA
 .eh_frame : ONLY_IF_RW {
  KEEP (*(.eh_frame))
 } > REGION_DATA AT > REGION_RODATA
 .gcc_except_table : ONLY_IF_RW {
  *(.gcc_except_table .gcc_except_table.*)
  __edata = .;
  __data_end__ = .;
 } > REGION_DATA AT > REGION_RODATA


 .bss : {
  . = ALIGN(0x4) ;
  __sbss = ALIGN(0x4) ;
  __bss_start__ = . ;
  *(.dynsbss)
  *(.sbss)
  *(.sbss.*)
  *(.scommon)
  *(.dynbss)
  *(.bss)
  *(.bss.*)
  *(COMMON)
  . = ALIGN(0x4) ;
  __ebss = . ;
  __end = . ;
  end = . ;
  __bss_end__ = .;
 } > REGION_BSS
  /* End of uninitalized data segement */
  PROVIDE(end = .);
}
