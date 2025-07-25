/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/01/11     flyingcys    The first version
 */
INCLUDE ./cvi_board_memmap.ld

_STACK_SIZE = DEFINED(_STACK_SIZE) ? _STACK_SIZE : 0x20000;
/* _HEAP_SIZE = DEFINED(_HEAP_SIZE) ? _HEAP_SIZE : 0x1000000; */
/*_HEAP_SIZE =  0x20000;*/

_EL0_STACK_SIZE = DEFINED(_EL0_STACK_SIZE) ? _EL0_STACK_SIZE : 1024;
_EL1_STACK_SIZE = DEFINED(_EL1_STACK_SIZE) ? _EL1_STACK_SIZE : 2048;
_EL2_STACK_SIZE = DEFINED(_EL2_STACK_SIZE) ? _EL2_STACK_SIZE : 1024;

/* Define Memories in the system */

MEMORY
{
   psu_ddr_0_MEM_0 : ORIGIN = CVIMMAP_FREERTOS_ADDR , LENGTH = CVIMMAP_FREERTOS_SIZE
}

/* Specify the default entry point to the program */

/*ENTRY(_vector_table)*/
ENTRY(_start)

/* Define the sections, and where they are mapped in memory */

SECTIONS
{
.text : {
   KEEP (*(.vectors))
   *(.boot)
   *(.text)
   *(.text.*)
   *(.gnu.linkonce.t.*)
   *(.plt)
   *(.gnu_warning)
   *(.gcc_execpt_table)
   *(.glue_7)
   *(.glue_7t)
   *(.ARM.extab)
   *(.gnu.linkonce.armextab.*)

   /* section information for finsh shell */
   . = ALIGN(8);
   __fsymtab_start = .;
   KEEP(*(FSymTab))
   __fsymtab_end = .;
   . = ALIGN(8);
   __vsymtab_start = .;
   KEEP(*(VSymTab))
   __vsymtab_end = .;
   . = ALIGN(8);

   /* section information for initial. */
   . = ALIGN(8);
   __rt_init_start = .;
   KEEP(*(SORT(.rti_fn*)))
   __rt_init_end = .;
   . = ALIGN(8);

   __rt_utest_tc_tab_start = .;
   KEEP(*(UtestTcTab))
   __rt_utest_tc_tab_end = .;
} > psu_ddr_0_MEM_0

.init (ALIGN(64)) : {
   KEEP (*(.init))
} > psu_ddr_0_MEM_0

.fini (ALIGN(64)) : {
   KEEP (*(.fini))
} > psu_ddr_0_MEM_0

.interp : {
   KEEP (*(.interp))
} > psu_ddr_0_MEM_0

.note-ABI-tag : {
   KEEP (*(.note-ABI-tag))
} > psu_ddr_0_MEM_0

.rodata : {
   . = ALIGN(64);
   __rodata_start = .;
   *(.rodata)
   *(.rodata.*)
   *(.srodata*)
   *(.gnu.linkonce.r.*)
   __rodata_end = .;
} > psu_ddr_0_MEM_0

.rodata1 : {
   . = ALIGN(64);
   __rodata1_start = .;
   *(.rodata1)
   *(.rodata1.*)
   __rodata1_end = .;
} > psu_ddr_0_MEM_0

.data : {
   . = ALIGN(64);
   _data = .;
   *(.data)
   *(.data.*)
   *(.sdata)
   *(.sdata.*)
   *(.gnu.linkonce.d.*)
   *(.jcr)
   *(.got)
   *(.got.plt)
   _edata = .;
} > psu_ddr_0_MEM_0

.data1 : {
   . = ALIGN(64);
   __data1_start = .;
   *(.data1)
   *(.data1.*)
   __data1_end = .;
} > psu_ddr_0_MEM_0

.got : {
   *(.got)
} > psu_ddr_0_MEM_0

.got1 : {
   *(.got1)
} > psu_ddr_0_MEM_0

.got2 : {
   *(.got2)
} > psu_ddr_0_MEM_0

.ctors : {
   . = ALIGN(64);
   __CTOR_LIST__ = .;
   ___CTORS_LIST___ = .;
   KEEP (*crtbegin.o(.ctors))
   KEEP (*(EXCLUDE_FILE(*crtend.o) .ctors))
   KEEP (*(SORT(.ctors.*)))
   KEEP (*(.ctors))
   __CTOR_END__ = .;
   ___CTORS_END___ = .;
} > psu_ddr_0_MEM_0

.dtors : {
   . = ALIGN(64);
   __DTOR_LIST__ = .;
   ___DTORS_LIST___ = .;
   KEEP (*crtbegin.o(.dtors))
   KEEP (*(EXCLUDE_FILE(*crtend.o) .dtors))
   KEEP (*(SORT(.dtors.*)))
   KEEP (*(.dtors))
   __DTOR_END__ = .;
   ___DTORS_END___ = .;
} > psu_ddr_0_MEM_0

.fixup : {
   __fixup_start = .;
   *(.fixup)
   __fixup_end = .;
} > psu_ddr_0_MEM_0

.eh_frame : {
   *(.eh_frame)
} > psu_ddr_0_MEM_0

.eh_framehdr : {
   __eh_framehdr_start = .;
   *(.eh_framehdr)
   __eh_framehdr_end = .;
} > psu_ddr_0_MEM_0

.gcc_except_table : {
   *(.gcc_except_table)
} > psu_ddr_0_MEM_0

.bss (NOLOAD) : {
   . = ALIGN(64);
   _bss = .;
   *(.bss)
   *(.bss.*)
   *(.sbss)
   *(.sbss.*)
   *(.gnu.linkonce.b.*)
   *(COMMON)
   . = ALIGN(64);
   _ebss = .;
} > psu_ddr_0_MEM_0

/*_SDA_BASE_ = __sdata_start + ((__sbss_end - __sdata_start) / 2 );*/
    _data_lma = LOADADDR(.data);

/* Generate Stack and Heap definitions */
.stack (NOLOAD) : {
   . = ALIGN(64);
   _stack_end_end = .;
   . += _STACK_SIZE;
   _stack_top = .;
  __rt_rvstack = .; 
} > psu_ddr_0_MEM_0

.heap (NOLOAD) : {
   . = ALIGN(64);
   _heap = .;
   HeapBase = .;
   _heap_start = .;
   *(.heap*)
   /*. += _HEAP_SIZE;*/
   /*_heap_size = _HEAP_SIZE; */
   _heap_end = .;
   HeapLimit = .;
} > psu_ddr_0_MEM_0

HeapLimit = ORIGIN(psu_ddr_0_MEM_0) + LENGTH(psu_ddr_0_MEM_0);
_end = .;
}

