/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     gcc_csky.ld
 * @brief    csky linker file
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
MEMORY
{
	I-SRAM : ORIGIN = 0x00000000 , LENGTH = 0x40000   /* I-SRAM  256KB */
	D-SRAM : ORIGIN = 0x20000000 , LENGTH = 0x8000    /* D-SRAM  32KB */
	O-SRAM : ORIGIN = 0x50000000 , LENGTH = 0x800000  /* off-chip SRAM 8MB */
	SRAM   : ORIGIN = 0x60000000 , LENGTH = 0x20000   /* on-chip SRAM 128KB */
}

__min_heap_size = 0x200;
__rt_rvstack_bss_size = 0x400;
PROVIDE (__ram_end  = 0x20007FFF);
PROVIDE (__heap_end = __ram_end);

REGION_ALIAS("REGION_TEXT",    I-SRAM);
REGION_ALIAS("REGION_RODATA",  I-SRAM);
REGION_ALIAS("REGION_DATA",    D-SRAM);
REGION_ALIAS("REGION_BSS",     D-SRAM);

ENTRY(Reset_Handler)
SECTIONS
{
 .text : {
  . = ALIGN(0x4) ;
  __stext = . ;
  KEEP(*startup_es32vf2264.o(*.text*))
  *(.text)
  *(.text*)
  *(.text.*)
  *(.gnu.warning)
  *(.stub)
  *(.gnu.linkonce.t*)
  *(.glue_7t)
  *(.glue_7)
  *(.jcr)
  KEEP (*(.init))
  KEEP (*(.fini))
  
  . = ALIGN (4) ;
  PROVIDE(__ctors_start__ = .);
  KEEP (*(SORT(.init_array.*)))
  KEEP (*(.init_array))
  PROVIDE(__ctors_end__ = .);
  
  . = ALIGN(0x40) ;
  KEEP(*startup_es32vf2264.o(*.vectors*))

  /* section information for finsh shell */
  . = ALIGN(4);
  __fsymtab_start = .;
  KEEP(*(FSymTab))
  __fsymtab_end = .;

  . = ALIGN (4) ;
  PROVIDE(__ctbp = .);
  *(.call_table_data)
  *(.call_table_text)
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
 
 
 .rodata : {
  . = ALIGN(0x4) ;
  __srodata = .;
  *(.rdata)
  *(.rdata*)
  *(.rdata1)
  *(.rdata.*)
  KEEP (*(.rti_fn.0))
  KEEP (*(.rti_fn.0.end))
  KEEP (*(.rti_fn.1))
  KEEP (*(.rti_fn.1.end))
  KEEP (*(.rti_fn.2))
  KEEP (*(.rti_fn.2.end))
  KEEP (*(.rti_fn.3))
  KEEP (*(.rti_fn.3.end))
  KEEP (*(.rti_fn.4))
  KEEP (*(.rti_fn.4.end))
  KEEP (*(.rti_fn.5))
  KEEP (*(.rti_fn.5.end))
  KEEP (*(.rti_fn.6))
  KEEP (*(.rti_fn.6.end))
  *(.rodata)
  *(.rodata1)
  *(.rodata*)
  *(.rodata.*)
  *(.rodata.str1.4)
  *(.srodata*)
  . = ALIGN(0x4) ;
  __erodata = .;
  __rodata_end__ = .;
 } > REGION_RODATA
 
 
 
 .data : {
  . = ALIGN(0x4) ;
  __sdata = . ;
  __data_start__ = . ;
  data_start = . ;
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
  PROVIDE(__dtors_start__ = .);
  KEEP(*(SORT(.dtors.*)))
  KEEP(*(.dtors))
  PROVIDE(__dtors_end__ = .);
  __stop_cmd = .;
  __global_pointer$ = .;
  *(.sdata)
  *(.sdata.*)
  *(.sdata2.*)
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
  __bss_end__ = .;
  __end = . ;
  end = . ;
 } > REGION_BSS AT > REGION_BSS
 
 
 
 ._user_heap : {
  . = ALIGN(0x4) ;
  __heap_start = .;
  . += __min_heap_size;
  . = ALIGN(0x4) ;
 } > REGION_BSS AT > REGION_BSS
 
 ._rtt_v5_use_stack1 : {
  . = ALIGN(0x4) ;
  . += __rt_rvstack_bss_size;
  __rt_rvstack = .;
  . = ALIGN(0x4) ;
 } > REGION_BSS AT > REGION_BSS
 
 
 
}
