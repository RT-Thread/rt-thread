/***************************************************************************//**
* \file cyw20829_ns.ld
* \version 1.0.0
*
* Linker file for the GNU C compiler.
*
* The main purpose of the linker script is to describe how the sections in the
* input files should be mapped into the output file, and to control the memory
* layout of the output file.
*
* \note The entry point location is fixed and starts at 0x10000000. The valid
* application image should be placed there.
*
* \note The linker files included with the PDL template projects must be generic
* and handle all common use cases. Your project may not use every section
* defined in the linker files. In that case you may see warnings during the
* build process. In your project, you can simply comment out or remove the
* relevant code in the linker file.
*
********************************************************************************
* \copyright
* Copyright 2016-2021 Cypress Semiconductor Corporation
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
*******************************************************************************/

CODE_ROM_NS_CBUS_START = 0x00000000;
CODE_ROM_NS_CBUS_SIZE = 0x00010000;
CODE_SRAM0_NS_CBUS_START = 0x04004200;
CODE_SRAM0_NS_CBUS_SIZE = 0x0000E000;
CODE_XIP_NS_CBUS_START = 0x08000000;
CODE_XIP_NS_CBUS_SIZE = 0x08000000;

DATA_ROM_NS_SAHB_START = 0x00000000;
DATA_ROM_NS_SAHB_SIZE  = 0x00000000;
BSS_ROM_NS_SAHB_START = 0x00000000;
BSS_ROM_NS_SAHB_SIZE = 0x00000000;
DATA1_SRAM0_NS_SAHB_START = 0x20000800;
DATA1_SRAM0_NS_SAHB_SIZE  = 0x00003800;
DATA_SRAM0_NS_SAHB_START = 0x20012200;
DATA_SRAM0_NS_SAHB_SIZE  = 0x0000DE00;
BSS_SRAM0_NS_SAHB_START = 0x20000000;
BSS_SRAM0_NS_SAHB_SIZE = 0x00000000;
DATA_XIP_NS_SAHB_START = 0x60000000;
DATA_XIP_NS_SAHB_SIZE  = 0x00000000;
BSS_XIP_NS_SAHB_START = 0x60000000;
BSS_XIP_NS_SAHB_SIZE = 0x00000000;


OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
GROUP(-lgcc -lc -lnosys )
SEARCH_DIR(.)
GROUP(libgcc.a libc.a libm.a libnosys.a)
ENTRY(Reset_Handler)

/* The size of the stack section at the end of CM33 SRAM */
STACK_SIZE = 0x1000;

/* The size of the MCU boot header area at the start of FLASH */
BOOT_HEADER_SIZE = 0x00;

/* LMA for ram */
ram_lma = 0x20004200;

/* Force symbol to be entered in the output file as an undefined symbol. Doing
* this may, for example, trigger linking of additional modules from standard
* libraries. You may list several symbols for each EXTERN, and you may use
* EXTERN multiple times. This command has the same effect as the -u command-line
* option.
*/
EXTERN(Reset_Handler)

/* The MEMORY section below describes the location and size of blocks of memory in the target.
* Use this section to specify the memory regions available for allocation.
*/
MEMORY
{
    /* The ram and code regions control RAM and code memory allocation for the CM33 core.
     */
    data1            (rwx)   : ORIGIN = DATA1_SRAM0_NS_SAHB_START,  LENGTH = DATA1_SRAM0_NS_SAHB_SIZE
    data             (rwx)   : ORIGIN = DATA_SRAM0_NS_SAHB_START,   LENGTH = DATA_SRAM0_NS_SAHB_SIZE
    code             (rx)    : ORIGIN = CODE_SRAM0_NS_CBUS_START,   LENGTH = CODE_SRAM0_NS_CBUS_SIZE


    /* The following regions define device specific memory regions and must not be changed. */
    xip               (rx)    : ORIGIN = CODE_XIP_NS_CBUS_START, LENGTH = CODE_XIP_NS_CBUS_SIZE   /* 128 MB */
}

/* Library configurations */
GROUP(libgcc.a libc.a libm.a libnosys.a)

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 *   __Vectors_End
 *   __Vectors_Size
 */


SECTIONS
{
    /* Cortex-M33 application code area */
    .text ORIGIN(code) + BOOT_HEADER_SIZE : AT (ram_lma + BOOT_HEADER_SIZE)
    {
        /* Cortex-M33 code vector table */
        . = ALIGN(4);
        __text_begin = .;
        __Vectors = . ;
        KEEP(*(.vectors))
        . = ALIGN(4);
        __Vectors_End = .;
        __Vectors_Size = __Vectors_End - __Vectors;
        __end__ = .;

        . = ALIGN(4);
        *(.text*)

        KEEP(*(.init))
        KEEP(*(.fini))

        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)

        /* .dtors */
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)

        /* Read-only code (constants). */
        *(.rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)

        KEEP(*(.eh_frame*))
        . = ALIGN(4);
        __text_end = .;
    } > code
    __exidx_end = .;


    .copy.table : AT (ram_lma + BOOT_HEADER_SIZE + (__text_end - __text_begin))
    {
        . = ALIGN(4);
        __copy_table_start__ = .;

        /* Copy data section to RAM */
        LONG (__etext)                                      /* From */
        LONG (__data_start__)                               /* To   */
        LONG ((__data_end__ - __data_start__)/4)            /* Size */

        /* Copy data1 section to RAM */
        LONG (__data1_lma__)                                /* From */
        LONG (__data1_start__)                              /* To   */
        LONG ((__data1_end__ - __data1_start__)/4)          /* Size */

        . = ALIGN(4);
        __copy_table_end__ = .;
    } > code


    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > code

    __exidx_start = .;

    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > code
    __exidx_end = .;


    /* To clear multiple BSS sections,
     * uncomment .zero.table section and,
     * define __STARTUP_CLEAR_BSS_MULTIPLE in CAT1B devices */
    .zero.table : AT (__exidx_end - ORIGIN(code) + ram_lma + BOOT_HEADER_SIZE)
    {
        . = ALIGN(4);
        __zero_table_start__ = .;
        LONG (__bss_start__)
        LONG ((__bss_end__ - __bss_start__)/4)

        LONG (__data1_zero_start__)
        LONG ((__data1_zero_end__ - __data1_zero_start__)/4)

        . = ALIGN(4);
        __zero_table_end__ = .;
    } > code

    __etext =  . ;


    .ramVectors (NOLOAD) : /*ALIGN(8)*/
    {
        __ram_vectors_start__ = .;
        KEEP(*(.ram_vectors))
        __ram_vectors_end__   = .;
    } > data


    .data __ram_vectors_end__ : AT (__etext - ORIGIN(code) + ram_lma + BOOT_HEADER_SIZE)
    {
        __data_start__ = .;

        *(vtable)
        *(.data*)

        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
       . = ALIGN(4);
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
       . = ALIGN(4);
        PROVIDE_HIDDEN (__init_array_end = .);

        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
       . = ALIGN(4);
        PROVIDE_HIDDEN (__fini_array_end = .);

       . = ALIGN(4);
        KEEP(*(.jcr*))
        . = ALIGN(4);

        KEEP(*(.cy_ramfunc*))
        . = ALIGN(4);

        __data_end__ = .;

    } > data


    __data1_lma__ = __etext - ORIGIN(code) + ram_lma + BOOT_HEADER_SIZE + (__data_end__ - __data_start__);

    .data1 ORIGIN(data1) : AT (__data1_lma__)
    {
        . = ALIGN(4);
        __data1_start__ = .;
        KEEP(*(.cy_data1*))
        . = ALIGN(4);
        __data1_end__ = .;

        __data1_zero_start__ = .;
        KEEP(*(.cy_zero_data1*))
        . = ALIGN(4);
        __data1_zero_end__ = .;
    } > data1


    /* Place variables in the section that should not be initialized during the
    *  device startup.
    */
    .noinit (NOLOAD) : ALIGN(8)
    {
      KEEP(*(.noinit))
    } > data


    /* The uninitialized global or static variables are placed in this section.
    *
    * The NOLOAD attribute tells linker that .bss section does not consume
    * any space in the image. The NOLOAD attribute changes the .bss type to
    * NOBITS, and that  makes linker to A) not allocate section in memory, and
    * A) put information to clear the section with all zeros during application
    * loading.
    *
    * Without the NOLOAD attribute, the .bss section might get PROGBITS type.
    * This  makes linker to A) allocate zeroed section in memory, and B) copy
    * this section to RAM during application loading.
    */
    .bss (NOLOAD):
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > data


    .heap (NOLOAD):
    {
        . = ALIGN(8);
        __HeapBase = .;
        __end__ = .;
        end = __end__;
        KEEP(*(.heap*))
        . = ORIGIN(data) + LENGTH(data) - STACK_SIZE;
        __HeapLimit = .;
    } > data


    /* .stack_dummy section doesn't contains any symbols. It is only
     * used for linker to calculate size of stack sections, and assign
     * values to stack symbols later */
    .stack_dummy (NOLOAD):
    {
        KEEP(*(.stack*))
    } > data


    /* Set stack top to end of RAM, and stack limit move down by
     * size of stack_dummy section */
    . = ALIGN(32);
    __StackTop = ORIGIN(data) + LENGTH(data);
    __StackLimit = __StackTop - SIZEOF(.stack_dummy);
    PROVIDE(__stack = __StackTop);

    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")

    /* Places the code in the Execute in Place (XIP) section. See the smif driver
    *  documentation for details.
    */
    cy_xip :
    {
        __cy_xip_start = .;
        KEEP(*(.cy_xip))
        __cy_xip_end = .;
    } > xip
}
/* EOF */
