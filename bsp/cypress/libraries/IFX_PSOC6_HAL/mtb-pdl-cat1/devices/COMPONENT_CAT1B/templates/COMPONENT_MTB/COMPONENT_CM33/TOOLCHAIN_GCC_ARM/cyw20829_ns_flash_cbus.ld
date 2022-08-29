/***************************************************************************//**
* \file cyw20829_ns_flash_cbus.ld
* \version 1.0.0
*
* Linker file for the GNU C compiler.
*
* The main purpose of the linker script is to describe how the sections in the
* input files should be mapped into the output file, and to control the memory
* layout of the output file.
*
* \note The entry point location starts at 0x0401e000. The valid
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
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
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

OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
GROUP(-lgcc -lc -lnosys )
SEARCH_DIR(.)
GROUP(libgcc.a libc.a libm.a libnosys.a)
ENTRY(Reset_Handler)

/* The size of the stack section at the end of CM4 SRAM */
STACK_SIZE = 0x1000;

FLASH_START_ADDR_SAHB       = 0x60000000;
FLASH_START_ADDR_CBUS       = 0x08000000;
RAM_START_ADDR_SAHB         = 0x20000000;
RAM_START_ADDR_CBUS         = 0x04000000;
RAM_END_ADDR_SAHB           = 0x20020000; /* 128K */
RAM_END_ADDR_CBUS           = 0x04020000; /* 128K */
FLASH_END_ADDR_SAHB         = 0x60080000; /* 512K */

BOOTSTRAP_OFFSET_FLASH      = 0x00000050; /* toc2=0x10, l1_desc=0x1C, sign_header=0x20 */
BOOTSTRAP_OFFSET_RAM        = 0x0001E000; /* Modify this value to change the size of Bootstrap code + Data */
APPCODE_OFFSET_FLASH        = 0x00002200;

RAMVECTORS_ALIGNMENT        = 512;

/* Memory reserved for Bootstrap code and data */
BOOTSTRAP_SIZE              = RAM_END_ADDR_SAHB - RAM_START_ADDR_SAHB - BOOTSTRAP_OFFSET_RAM; /* 0x00002000 */
/* vma for bootstrap code region */
CODE_VMA                    = RAM_START_ADDR_CBUS + BOOTSTRAP_OFFSET_RAM; /* 0x0401E000 */
/* lma for bootstrap code region */
CODE_LMA                    = FLASH_START_ADDR_SAHB + BOOTSTRAP_OFFSET_FLASH; /* 0x6000004C */
/* Maximum bootstrap code + data size */
CODE_BS_SIZE                   = BOOTSTRAP_SIZE; /* 8KB */
/* vma for bootstrap data region */
DATA_BS_VMA                 = RAM_START_ADDR_SAHB + BOOTSTRAP_OFFSET_RAM; /* 0x2001E000 */
/* vma for bootstrap and app data region */
DATA_VMA                    = RAM_START_ADDR_SAHB; /* 0x20000000 */
/* vma for appCodeRam region */
DATA_CBUS_VMA               = RAM_START_ADDR_CBUS; /* 0x04000000 */
/* lma for bootstrap and app data region */
DATA_LMA                    = CODE_LMA + CODE_BS_SIZE; /* 0x6000204C */
/* data size */
DATA_SIZE                   = RAM_END_ADDR_SAHB - DATA_VMA - BOOTSTRAP_SIZE; /* 0x1E000 */
/* vma for application XIP region */
XIP_VMA                     = FLASH_START_ADDR_CBUS + APPCODE_OFFSET_FLASH; /* 0x08002200 */
/* lma for application XIP region */
XIP_LMA                     = FLASH_START_ADDR_SAHB + APPCODE_OFFSET_FLASH; /* 0x60002200 */
/* size of XIP region */
XIP_SIZE                    = FLASH_END_ADDR_SAHB - XIP_LMA;
/* Total size of SRAM */
RAM_SIZE                    = RAM_END_ADDR_SAHB - RAM_START_ADDR_SAHB; /* 0x00020000 */
/* Size of Bootstrap data is kept same as BOOTSTRAP_SIZE */
DATA_BS_SIZE                = BOOTSTRAP_SIZE;

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
    /* The ram and flash regions control RAM and flash memory allocation for the CM33 core.
     */
    code                    (rx)    : ORIGIN = CODE_VMA,        LENGTH = CODE_BS_SIZE
    bsData                  (rwx)   : ORIGIN = DATA_BS_VMA,     LENGTH = DATA_BS_SIZE
    appCodeRam              (rx)    : ORIGIN = DATA_CBUS_VMA,   LENGTH = DATA_SIZE
    data                    (rwx)   : ORIGIN = DATA_VMA,        LENGTH = DATA_SIZE
    xip                     (rx)    : ORIGIN = XIP_VMA,         LENGTH = XIP_SIZE
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
    /* .stack_dummy section doesn't contains any symbols. It is only
     * used for linker to calculate size of stack sections, and assign
     * values to stack symbols later */
    .stack_dummy RAM_START_ADDR_SAHB (NOLOAD):
    {
        KEEP(*(.stack*))
    } > data

    /* Set stack top beginning of RAM minus the size of stack, and stack limit move down by
     * size of stack_dummy section */
    . = ALIGN(32);
    __StackTop = RAM_START_ADDR_SAHB + STACK_SIZE;
    __StackLimit = __StackTop - SIZEOF(.stack_dummy);
    PROVIDE(__stack = __StackTop);

    . = ALIGN(RAMVECTORS_ALIGNMENT);
    __ramVectors_vma__ = RAM_START_ADDR_SAHB + STACK_SIZE;

    .ramVectors __ramVectors_vma__ (NOLOAD):
    {
        __ram_vectors_start__ = .;
        KEEP(*(.ram_vectors))
        . = ALIGN(4);
        __ram_vectors_end__   = .;
    } > data

    __appTextRam_vma__ = (__ram_vectors_end__ - RAM_START_ADDR_SAHB) + RAM_START_ADDR_CBUS;
    __appTextRam_lma__ = (__zero_table_end__ - FLASH_START_ADDR_CBUS) + FLASH_START_ADDR_SAHB;
    __ezerotable = __zero_table_end__;

    .appTextRam __appTextRam_vma__ : AT (__appTextRam_lma__)
    {
        . = ALIGN(4);
        __app_text_ram_begin__ = .;
        KEEP(*(.cy_ramfunc*))
        . = ALIGN(4);

        *cy_smif.o(.text*)
        *cy_smif_memslot.o(.text*)
        *cy_smif_sfdp.o(.text*)

        . = ALIGN(4);
        __app_text_ram_end__ = .;

    } > appCodeRam

    __data_vma__ = (__app_text_ram_end__ - RAM_START_ADDR_CBUS) + RAM_START_ADDR_SAHB;
    __data_lma__ = (__app_text_ram_end__ - __app_text_ram_begin__) + __appTextRam_lma__;
    __etext =  __data_lma__ - FLASH_START_ADDR_SAHB + FLASH_START_ADDR_CBUS;

    .data __data_vma__ : AT (__data_lma__)
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

        __data_end__ = .;

    } > data

    /* Check if data is exceeding the flash size */
    ASSERT((__data_lma__ + (__data_end__ - __data_start__)) <= FLASH_END_ADDR_SAHB, "data section exceeds Flash size !")

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

    /* Use ramining RAM for Heap */
    __heap_size__ = (RAM_SIZE - ((__bss_end__ - RAM_START_ADDR_SAHB) + (RAM_END_ADDR_CBUS - __bootstrapText_vma__)) - 4);

    .heap (NOLOAD):
    {
        . = ALIGN(8);
        __HeapBase = .;
        __end1__ = .;
        end = __end1__;
        KEEP(*(.heap*))
        . += __heap_size__;
        __HeapLimit = .;
    } > data

     __bootstrapText_vma__ = ORIGIN(code);
     __bootstrapText_lma__ = CODE_LMA;

    /* Cortex-M33 bootstrap code area */
    .bootstrapText __bootstrapText_vma__ : AT (__bootstrapText_lma__)
    {
        /* Cortex-M33 code vector table */
        . = ALIGN(4);
        __bootstrapText_begin = .;

        __Vectors = . ;
        KEEP(*(.vectors))
        . = ALIGN(4);
        __Vectors_End = .;
        __Vectors_Size = __Vectors_End - __Vectors;
        __end__ = .;

        . = ALIGN(4);

        /* startup code */
        *ns_start_cyw20829.o(.text*)
        *ns_system_cyw20829.o(.text*)

        /* drivers */
        *cy_device.o(.text*)
        *cy_btss.o(.text*)
        *cy_sysclk_v2.o(.text*)
        *cy_syspm_v2.o(.text*)
        *cy_sysint_v2.o(.text*)
        *cy_syslib*.o(.text*)
        *ppu_v1.o(.text*)
        *cy_mpc.o(.text*)
        *cy_pd_ppu.o(.text*)

        KEEP(*(.cy_l1func*))

        . = ALIGN(4);
        __bootstrapText_end = .;
    } > code

    __bootstrap_zerotable_lma__ = (CODE_LMA + (__bootstrapText_end - __bootstrapText_begin));

    .bootstrapzero.table : AT (__bootstrap_zerotable_lma__)
    {
        . = ALIGN(4);
        __bootstrapzero_table_start__ = .;
        LONG (__bootstrap_bss_start__)
        LONG ((__bootstrap_bss_end__ - __bootstrap_bss_start__)/4)
        . = ALIGN(4);
        __bootstrapzero_table_end__ = .;
    } > code

    __bootstrapData_vma__ = ((__bootstrapzero_table_end__ - RAM_START_ADDR_CBUS) + RAM_START_ADDR_SAHB);
    __bootstrapData_lma__ = (__bootstrap_zerotable_lma__ + (__bootstrapzero_table_end__ - __bootstrapzero_table_start__));

    .bootstrapData __bootstrapData_vma__ : AT (__bootstrapData_lma__)
    {
        __bootstrapData_start__ = .;
        . = ALIGN(4);

        /* startup code */
        *ns_start_cyw20829.o(.data* .rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)
        *ns_system_cyw20829.o(.data* .rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)

        /* drivers */
        *cy_device.o(.data* .rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)
        *cy_btss.o(.data* .rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)
        *cy_sysclk_v2.o(.data* .rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)
        *cy_syspm_v2.o(.data* .rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)
        *cy_sysint_v2.o(.data* .rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)
        *cy_syslib.o(.data* .rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)
        *ppu_v1.o(.data* .rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)
        *cy_mpc.o(.data* .rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)
        *cy_pd_ppu.o(.data* .rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)

        KEEP(*(.cy_l1data*))

        . = ALIGN(4);
        __bootstrapData_end__ = .;
    } > bsData

    __bootstrap_size_end__ = .;
    .bootstrapBss (NOLOAD):
    {
        . = ALIGN(4);
        __bootstrap_bss_start__ = .;

        /* startup code */
        *ns_start_cyw20829.o(.bss* COMMON)
        *ns_system_cyw20829.o(.bss* COMMON)

        /* drivers */
        *cy_device.o(.bss* COMMON)
        *cy_btss.o(.bss* COMMON)
        *cy_sysclk_v2.o(.bss* COMMON)
        *cy_syspm_v2.o(.bss* COMMON)
        *cy_sysint_v2.o(.bss* COMMON)
        *cy_syslib.o(.bss* COMMON)
        *ppu_v1.o(.bss* COMMON)
        *cy_mpc.o(.bss* COMMON)
        *cy_pd_ppu.o(.bss* COMMON)
        KEEP(*(.cy_l1bss*))

        . = ALIGN(4);
        __bootstrap_bss_end__ = .;
    } > bsData

    /* Check if bootstrap code + data exceeds RAM limit */
    ASSERT(__bootstrap_bss_end__ < RAM_END_ADDR_SAHB, "bootstrap region exceeds RAM size !")

    __app_text_vma__ = ORIGIN(xip);
    __app_text_lma__ = XIP_LMA;

    /* Cortex-M33 application flash area */
    .appText (__app_text_vma__) : AT (__app_text_lma__)
    {
        /* Cortex-M33 flash vector table */
        . = ALIGN(4);
        __text_begin = .;

        *(EXCLUDE_FILE(*cy_smif.o
                        *cy_smif_memslot.o *cy_smif_sfdp.o) .text*)

        KEEP(*(.init))
        KEEP(*(.fini))

        /* Read-only code (constants). */
        *(.rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)

        KEEP(*(.eh_frame*))
        . = ALIGN(4);
        __text_end = .;

    } > xip


    .copy.table : AT (__app_text_lma__ + (__text_end - __text_begin))
    {
        . = ALIGN(4);
        __copy_table_start__ = .;

        /* Copy data section to RAM */
        LONG (__etext)                                      /* From */
        LONG (__data_start__)                               /* To   */
        LONG ((__data_end__ - __data_start__)/4)            /* Size */

        /* Copy appTextRam section to RAM */
        LONG (__ezerotable)                                         /* From */
        LONG (__ram_vectors_end__)                                  /* To   */
        LONG ((__app_text_ram_end__ - __app_text_ram_begin__)/4)    /* Size */

        . = ALIGN(4);
        __copy_table_end__ = .;
    } > xip



    .ARM.extab : AT (__app_text_lma__ + (__text_end - __text_begin) + (__copy_table_end__ - __copy_table_start__))
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > xip

    __exidx_start = .;

    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > xip
    __exidx_end = .;


    /* To clear multiple BSS sections,
     * uncomment .zero.table section and,
     * define __STARTUP_CLEAR_BSS_MULTIPLE in CAT1B devices */
    .zero.table : AT (__exidx_end - __app_text_vma__ + __app_text_lma__)
    {
        . = ALIGN(4);
        __zero_table_start__ = .;
        LONG (__bss_start__)
        LONG ((__bss_end__ - __bss_start__)/4)

        . = ALIGN(4);
        __zero_table_end__ = .;
    } > xip
}

/* start of bootstrap code sahb address */
__bootstrap_start_addr__    = RAM_START_ADDR_SAHB + BOOTSTRAP_OFFSET_RAM;
/* bootstrap size */
__bootstrap_size__          = __bootstrap_size_end__ - __bootstrap_start_addr__;

