/*
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
 * @file     gcc_hbird_flashxip.ld
 * @brief    GNU Linker Script for Nuclei N/NX based device in FlashXIP Download Mode
 * @version  V1.0.0
 * @date     17. Dec 2019
 ******************************************************************************/

/*********** Use Configuration Wizard in Context Menu *************************/

OUTPUT_ARCH( "riscv" )
/********************* Flash Configuration ************************************
 * <h> Flash Configuration
 * <o0> Flash Base Address <0x0-0xFFFFFFFF:8>
 * <o1> Flash Size (in Bytes) <0x0-0xFFFFFFFF:8>
 * </h>
 */
__ROM_BASE = 0x20000000;
__ROM_SIZE = 0x00400000;

/*--------------------- ILM RAM Configuration ---------------------------
 * <h> ILM RAM Configuration
 * <o0> ILM RAM Base Address    <0x0-0xFFFFFFFF:8>
 * <o1> ILM RAM Size (in Bytes) <0x0-0xFFFFFFFF:8>
 * </h>
 */
__ILM_RAM_BASE = 0x80000000;
__ILM_RAM_SIZE = 0x00010000;

/*--------------------- Embedded RAM Configuration ---------------------------
 * <h> RAM Configuration
 * <o0> RAM Base Address    <0x0-0xFFFFFFFF:8>
 * <o1> RAM Size (in Bytes) <0x0-0xFFFFFFFF:8>
 * </h>
*/
__RAM_BASE = 0x90000000;
__RAM_SIZE = 0x00010000;

/********************* Stack / Heap Configuration ****************************
 * <h> Stack / Heap Configuration
 * <o0> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
 * <o1> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
 * </h>
 */
__STACK_SIZE = 0x00000800;
__HEAP_SIZE  = 0x00000800;

/**************************** end of configuration section ********************/

/* Define base address and length of flash and ram */
MEMORY
{
  flash (rxai!w) : ORIGIN = __ROM_BASE, LENGTH = __ROM_SIZE
  ram (wxa!ri) : ORIGIN = __RAM_BASE, LENGTH = __RAM_SIZE
}
/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH,ILM and RAM.
 * It references following symbols, which must be defined in code:
 *   _Start : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   _ilm_lma
 *   _ilm
 *   __etext
 *   _etext
 *   etext
 *   _eilm
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   _data_lma
 *   _edata
 *   edata
 *   __data_end__
 *   __bss_start
 *   __fbss
 *   _end
 *   end
 *   __heap_end
 *   __StackLimit
 *   __StackTop
 *   __STACK_SIZE
 */
/* Define entry label of program */
ENTRY(_start)
SECTIONS
{
  __STACK_SIZE = DEFINED(__STACK_SIZE) ? __STACK_SIZE : 2K;

  .init           :
  {
    /* vector table locate at flash */
    *(.vtable)
    KEEP (*(SORT_NONE(.init)))
  } >flash AT>flash

  .ilalign         :
  {
    . = ALIGN(4);
    /* Create a section label as _ilm_lma which located at flash */
    PROVIDE( _ilm_lma = . );
  } >flash AT>flash

  .ialign         :
  {
    /* Create a section label as _ilm which located at flash */
    PROVIDE( _ilm = . );
  } >flash AT>flash

  /* Code section located at flash */
  .text           :
  {
    *(.text.unlikely .text.unlikely.*)
    *(.text.startup .text.startup.*)
    *(.text .text.*)
    *(.gnu.linkonce.t.*)
  } >flash AT>flash

  .rodata : ALIGN(4)
  {
    . = ALIGN(4);
    *(.rdata)
    *(.rodata .rodata.*)
    /* section information for initial. */
    . = ALIGN(4);
    __rt_init_start = .;
    KEEP(*(SORT(.rti_fn*)))
    __rt_init_end = .;
    /* section information for finsh shell */
    . = ALIGN(4);
    __fsymtab_start = .;
    KEEP(*(FSymTab))
    __fsymtab_end = .;
    . = ALIGN(4);
    __vsymtab_start = .;
    KEEP(*(VSymTab))
    __vsymtab_end = .;
    *(.gnu.linkonce.r.*)
    . = ALIGN(8);
    *(.srodata.cst16)
    *(.srodata.cst8)
    *(.srodata.cst4)
    *(.srodata.cst2)
    *(.srodata .srodata.*)
  } >flash AT>flash

  .fini           :
  {
    KEEP (*(SORT_NONE(.fini)))
  } >flash AT>flash

  . = ALIGN(4);

  PROVIDE (__etext = .);
  PROVIDE (_etext = .);
  PROVIDE (etext = .);
  PROVIDE( _eilm = . );


  .preinit_array  :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >flash AT>flash

  .init_array     :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >flash AT>flash

  .fini_array     :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
    KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >flash AT>flash

  .ctors          :
  {
    /* gcc uses crtbegin.o to find the start of
     * the constructors, so we make sure it is
     * first.  Because this is a wildcard, it
     * doesn't matter if the user does not
     * actually link against crtbegin.o; the
     * linker won't look for a file to match a
     * wildcard.  The wildcard also means that it
     * doesn't matter which directory crtbegin.o
     * is in.
     */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
     * the crtend.o file until after the sorted ctors.
     * The .ctor section from the crtend file contains the
     * end of ctors marker and it must be last
     */
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  } >flash AT>flash

  .dtors          :
  {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  } >flash AT>flash

  .lalign         :
  {
    . = ALIGN(4);
    PROVIDE( _data_lma = . );
  } >flash AT>flash

  .dalign         :
  {
    . = ALIGN(4);
    PROVIDE( _data = . );
  } >ram AT>flash

  /* Define data section virtual address is ram and physical address is flash */
  .data          :
  {
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    . = ALIGN(8);
    PROVIDE( __global_pointer$ = . + 0x800 );
    *(.sdata .sdata.* .sdata*)
    *(.gnu.linkonce.s.*)
  } >ram AT>flash

  . = ALIGN(4);
  PROVIDE( _edata = . );
  PROVIDE( edata = . );

  PROVIDE( _fbss = . );
  PROVIDE( __bss_start = . );
  .bss            :
  {
    *(.sbss*)
    *(.gnu.linkonce.sb.*)
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
  } >ram AT>ram

  . = ALIGN(8);
  PROVIDE( _end = . );
  PROVIDE( end = . );
  /* Define stack and head location at ram */
  .stack ORIGIN(ram) + LENGTH(ram) - __STACK_SIZE :
  {
    PROVIDE( _heap_end = . );
    . = __STACK_SIZE;
    PROVIDE( _sp = . );
  } >ram AT>ram
}
