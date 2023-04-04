/*!
 * @file       gcc_APM32S10xx8.ld
 *
 * @brief      Linker script for APM32S10xx8 Device with
 *             64KByte FLASH, 36KByte RAM
 *
 * @version    V1.0.0
 *
 * @date       2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2022-2023 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Entry Point */
ENTRY(Reset_Handler)

/* Flash Configuration*/
/* Flash Base Address */
_rom_base = 0x8000000;
/*Flash Size (in Bytes) */
_rom_size = 0x0010000;

/* Embedded RAM Configuration */
/* RAM Base Address           */
_ram_base = 0x20000000;
/* RAM Size (in Bytes) */
_ram_size = 0x00009000;

/* Stack / Heap Configuration */
_end_stack = 0x20009000;
/* Heap Size (in Bytes) */
_heap_size = 0x200;
/* Stack Size (in Bytes) */
_stack_size = 0x400;

MEMORY
{
FLASH (rx)      : ORIGIN = _rom_base, LENGTH = _rom_size
RAM (xrw)       : ORIGIN = _ram_base, LENGTH = _ram_size
}

SECTIONS
{
  .apm32_isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.apm32_isr_vector))
    . = ALIGN(4);
  } >FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;
  } >FLASH

  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  _start_address_init_data = LOADADDR(.data);

  .data :
  {
    . = ALIGN(4);
    _start_address_data = .;
    *(.data)
    *(.data*)

    . = ALIGN(4);
    _end_address_data = .;
  } >RAM AT> FLASH


  . = ALIGN(4);
  .bss :
  {

    _start_address_bss = .;
    __bss_start__ = _start_address_bss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _end_address_bss = .;
    __bss_end__ = _end_address_bss;
  } >RAM

  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _heap_size;
    . = . + _stack_size;
    . = ALIGN(8);
  } >RAM

  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}

