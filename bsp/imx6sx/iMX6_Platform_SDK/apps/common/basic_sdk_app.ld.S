/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

/*
 * OCRAM
 */
#if defined(CHIP_MX6SDL) || defined(CHIP_MX6SL)
    // mx6sl and mx6sdl both have 128kB of OCRAM.
    #define OCRAM_LEN 128K
#elif defined(CHIP_MX6DQ)
    // mx6dq has 256kB of OCRAM
    #define OCRAM_LEN 256K
#else
    #error Unknown chip!
#endif

/*
 * External DDR
 */
#if defined(CHIP_MX6SL)
    // mx6sl has only one DDR chip select that starts at a different address
    #define DDR_ORG 0x80000000
#elif defined(CHIP_MX6SDL) || defined(CHIP_MX6DQ)
    // mx6dq and mx6sdl DDR memory starts at this address
    #define DDR_ORG 0x10000000
#else
    #error Unknown chip!
#endif

#if defined(BOARD_SABRE_AI)
    // mx6dq and mx6sdl sabre-ai board has 2GB of DDR3
    #define DDR_LEN 2048M
#else
    // all other boards have 1GB of DDR3
    #define DDR_LEN 1024M
#endif

// Maximum size of the signed image
#if !defined(MAX_IMAGE_SIZE)
#define MAX_IMAGE_SIZE 4M
#endif

// Maximum size of HAB CSF data
#if !defined(MAX_HAB_CSF_DATA_SIZE)
#define MAX_HAB_CSF_DATA_SIZE 8K
#endif

// Size of stacks section
#if !defined(STACK_SIZE)
#define STACK_SIZE 48K
#endif

// Size of the malloc heap, defaults to 128MB
#if !defined(HEAP_SIZE)
#define HEAP_SIZE 128M
#endif

// Size of the L1 page table.
#define L1_PAGE_TABLE_SIZE 16K

// Size of the RAM vectors table at the top of OCRAM.
//
// The vectors in ROM at address 0 point to these RAM vectors.
#define RAM_VECTORS_SIZE 72

INPUT (crtbegin.o crti.o crtend.o crtn.o)

MEMORY
{
    OCRAM (rwx) : ORIGIN = 0x00900000, LENGTH = OCRAM_LEN
    DDR (rwx)   : ORIGIN = DDR_ORG, LENGTH = DDR_LEN
}

SECTIONS
{
/*
 * -- OCRAM --
 *
 * Nothing in OCRAM can be loaded at boot, because the boot image must be a contiguous
 * region of memory.
 */

    /* MMU L1 page table */
    .l1_page_table (NOLOAD) :
    {
        __l1_page_table_start = .;
        . += L1_PAGE_TABLE_SIZE;
    } > OCRAM

    /* allocate a heap in ocram */
    .heap.ocram (NOLOAD) : ALIGN(4)
    {
        __heap_ocram_start = .;
        . += LENGTH(OCRAM) - L1_PAGE_TABLE_SIZE - RAM_VECTORS_SIZE ;
        __heap_ocram_end = .;
    } > OCRAM
    
    /* RAM vector table comes at the end of OCRAM */
    .ram_vectors (ORIGIN(OCRAM) + LENGTH(OCRAM) - RAM_VECTORS_SIZE) (NOLOAD) :
    {
        __ram_vectors_start = .;
        . += RAM_VECTORS_SIZE;
        __ram_vectors_end = .;
    } > OCRAM


/*
 * -- DDR --
 */

    /* -- read-only sections -- */
    
    _start_image_add = ORIGIN(DDR);
    
    .ivt (ORIGIN(DDR)) :
    {
        . = . + 0x400;
        *(.ivt)
    } > DDR
    
    .boot_data :
    {
        __start_boot_data = .;
        *(.boot_data)
    } > DDR
    
    /* aligned to ease the hexdump read of generated binary */ 
    .dcd_hdr : ALIGN(16)
    {
        __start_dcd = .;
        *(.dcd_hdr)
    } > DDR
    .dcd_wrt_cmd :
    {
        *(.dcd_wrt_cmd)
    } > DDR
    .dcd_data :
    {
        *(.dcd_data)
    } > DDR
    
    .text : ALIGN(8)
    {
        CREATE_OBJECT_SYMBOLS
        *(.startup)
        *(.text .text.* .gnu.linkonce.t.*)
        *(.glue_7t) *(.glue_7) *(.vfp11_veneer)
        
        *(.ARM.extab* .gnu.linkonce.armextab.*)
        *(.gcc_except_table)
    } > DDR

    .ctors :
    {
        /* gcc uses crtbegin.o to find the start of
           the constructors, so we make sure it is
           first.  Because this is a wildcard, it
           doesn't matter if the user does not
           actually link against crtbegin.o; the
           linker won't look for a file to match a
           wildcard.  The wildcard also means that it
           doesn't matter which directory crtbegin.o
           is in.  */
        KEEP (*crtbegin.o(.ctors))
        KEEP (*crtbegin?.o(.ctors))
        /* We don't want to include the .ctor section from
           the crtend.o file until after the sorted ctors.
           The .ctor section from the crtend file contains the
           end of ctors marker and it must be last */
        KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*(.ctors))
    } > DDR
    .dtors :
    {
        KEEP (*crtbegin.o(.dtors))
        KEEP (*crtbegin?.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*(.dtors))
    } > DDR

    .rodata :
    {
        *(.rodata .rodata.* .gnu.linkonce.r.*)

        . = ALIGN(4);
        KEEP(*(.init))

        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        __init_array_end = .;
        
        . = ALIGN(4);
        KEEP(*(.fini))
        
        . = ALIGN(4);
        __fini_array_start = .;
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        __fini_array_end = .;

    } > DDR

    /* Unwind index. This section is related to C++ exceptions, and is required even
       though exceptions are disabled with -fno-exceptions. */
    PROVIDE_HIDDEN(__exidx_start = .);
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > DDR
    PROVIDE_HIDDEN(__exidx_end = .);

    /* -- read-write sections -- */
    
    .data : ALIGN(8)
    {
        *(.data .data.* .gnu.linkonce.d.*)
        SORT(CONSTRUCTORS)
    } > DDR

    /* Reserve some space for HAB CSF data */
    .hab.data (_start_image_add + MAX_IMAGE_SIZE) : ALIGN(4)
    {
        __hab_data = .;
        . += MAX_HAB_CSF_DATA_SIZE;
        . = ALIGN (32);
        __hab_data_end = .;
    } > DDR
    /* End of HAB reserved space (must place it before BSS section) */

    _image_size = . - _start_image_add;

    /* The .bss section comes after the hab data because it is not signed */
    .bss :
    {
        __bss_start__ = .;
        *(.shbss)
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
        *(.bss)
        __bss_end__ = .;
    } > DDR

    /* Region to contain exception handler stacks */
    .stacks (NOLOAD) :
    {
        __stacks_start = .;
        . += STACK_SIZE;
        __stacks_end = .;
        top_of_stacks = .;
    } > DDR
    
    /* define range of the malloc heap */
    free_memory_start = ALIGN(32); /* malloc starts allocating from here */
    . += HEAP_SIZE;
    free_memory_end = .;

    _end = .;
}
