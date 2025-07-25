 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

INCLUDE "link_stacksize.lds"

MEMORY
{
   DRAM : ORIGIN = 0xFFFFFFC000200000, LENGTH = 0x1000000 - 0x200000
}

ENTRY(_start)
SECTIONS
{
  /* . = 0x80200000 ; */
  . = 0xFFFFFFC000200000;

  /* __STACKSIZE__ = 4096; */
  __text_start = .;
  .start :
  {
    *(.start);
  } > DRAM
  . = ALIGN(8);
  .text :
  {
    *(.text)
    *(.text.*)
    *(.rodata)
    *(.rodata*)
    *(.glue_7)
    *(.glue_7t)
    *(.gnu.linkonce.t*)
    . = ALIGN(8);
    __fsymtab_start = .;
    KEEP(*(FSymTab))
    __fsymtab_end = .;
    . = ALIGN(8);
    __vsymtab_start = .;
    KEEP(*(VSymTab))
    __vsymtab_end = .;
    . = ALIGN(8);
    . = ALIGN(8);
    __rt_init_start = .;
    KEEP(*(SORT(.rti_fn*)))
    __rt_init_end = .;
    . = ALIGN(8);
    __rt_utest_tc_tab_start = .;
    KEEP(*(UtestTcTab))
    __rt_utest_tc_tab_end = .;
    . = ALIGN(8);
    __usbh_class_info_start__ = .;
    KEEP(*(.usbh_class_info))
    __usbh_class_info_end__ = .;
    . = ALIGN(8);
    _etext = .;
  } > DRAM
  .eh_frame_hdr :
  {
    *(.eh_frame_hdr)
    *(.eh_frame_entry)
  } > DRAM
  .eh_frame : ONLY_IF_RO { KEEP (*(.eh_frame)) } > DRAM
  . = ALIGN(8);
  __text_end = .;
  __text_size = __text_end - __text_start;
  .data :
  {
    *(.data)
    *(.data.*)
    *(.data1)
    *(.data1.*)
    . = ALIGN(8);
    PROVIDE( __global_pointer$ = . + 0x800 );
    *(.sdata)
    *(.sdata.*)
  } > DRAM
  .stack :
  {
    . = ALIGN(64);
    __stack_start__ = .;
    . += 65536;
    __stack_cpu0 = .;
    . += 65536;
    __stack_cpu1 = .;
  } > DRAM
  . = ALIGN(8);
  .osdebug :
  {
    _osdebug_start = .;
    . += 87K;
    _osdebug_end = .;
  } > DRAM
  . = ALIGN(8);
  .sbss :
  {
    __bss_start = .;
    *(.sbss)
    *(.sbss.*)
    *(.dynsbss)
    *(.scommon)
  } > DRAM
  .bss :
  {
    *(.bss)
    *(.bss.*)
    *(.dynbss)
    *(COMMON)
    . = ALIGN(64);
    __bss_end = .;
  } > DRAM
  _end = .;
  .stab 0 : { *(.stab) }
  .stabstr 0 : { *(.stabstr) }
  .stab.excl 0 : { *(.stab.excl) }
  .stab.exclstr 0 : { *(.stab.exclstr) }
  .stab.index 0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment 0 : { *(.comment) }
  .debug 0 : { *(.debug) }
  .line 0 : { *(.line) }
  .debug_srcinfo 0 : { *(.debug_srcinfo) }
  .debug_sfnames 0 : { *(.debug_sfnames) }
  .debug_aranges 0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  .debug_info 0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev 0 : { *(.debug_abbrev) }
  .debug_line 0 : { *(.debug_line) }
  .debug_frame 0 : { *(.debug_frame) }
  .debug_str 0 : { *(.debug_str) }
  .debug_loc 0 : { *(.debug_loc) }
  .debug_macinfo 0 : { *(.debug_macinfo) }
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames 0 : { *(.debug_varnames) }
}
