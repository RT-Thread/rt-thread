/****************************************************************************************
* @file map.txt
*
* @brief This file is the map file (gnuarm or armgcc).
*
* Copyright (C) BouffaloLab 2018
*
****************************************************************************************
*/

/* configure the CPU type */
OUTPUT_ARCH( "riscv" )
/* link with the standard c library */
INPUT(-lc)
/* link with the standard GCC library */
INPUT(-lgcc)
/* configure the entry point */
ENTRY(Reset_Handler)

StackSize = 0x0400; /*  1KB */
HeapSize  = 0x0400; /*  1KB */

MEMORY
{
    code_memory (rx)  : ORIGIN = 0x3eff0000, LENGTH = 64K
    itcm_memory (rx)  : ORIGIN = 0x3eff0000, LENGTH = 64K
    dtcm_memory (rx)  : ORIGIN = 0x3f000000, LENGTH = 32K
    ram_memory  (!rx) : ORIGIN = 0x3f008000, LENGTH = 32K
    xram_memory (!rx) : ORIGIN = 0x40004000, LENGTH = 16K
}

SECTIONS
{
    PROVIDE(__metal_chicken_bit = 0);
    
    .text :
    {
        . = ALIGN(4);
        __text_code_start__ = .;
        
        KEEP (*(SORT_NONE(_start)))
        KEEP (*(SORT_NONE(Reset_Handler)))
        
        *(.text)
        *(.text.*)
        
        /*put .rodata**/
        *(EXCLUDE_FILE( *bl808_glb*.o* \
                        *bl808_pds*.o* \
                        *bl808_common*.o* \
                        *bl808_sf_cfg*.o* \
                        *bl808_sf_ctrl*.o* \
                        *bl808_sflash*.o* \
                        *bl808_xip_sflash*.o* \
                        *bl808_ef_ctrl*.o* \
                        *bl808_sf_cfg_ext*.o* \
                        *bl808_sflash_ext*.o* \
                        *bl808_xip_sflash_ext*.o*) .rodata*)
        
        *(.srodata)
        *(.srodata.*)
        
        *(.tcm_code)
        *(.tcm_const)
        *(.sclock_rlt_code)
        *(.sclock_rlt_const)
        
        . = ALIGN(4);
        __text_code_end__ = .;
    } > code_memory
    
    . = ALIGN(4);
    __itcm_load_addr = .;
    
    .itcm_region : AT (__itcm_load_addr)
    {
        . = ALIGN(4);
        __tcm_code_start__ = .;

        *(.tcm_code.*)
        *(.tcm_cons.t*)
        *(.sclock_rlt_code.*)
        *(.sclock_rlt_const.*)

        *bl808_glb*.o*(.rodata*)
        *bl808_pds*.o*(.rodata*)
        *bl808_common*.o*(.rodata*)
        *bl808_sf_cfg*.o*(.rodata*)
        *bl808_sf_ctrl*.o*(.rodata*)
        *bl808_sflash*.o*(.rodata*)
        *bl808_xip_sflash*.o*(.rodata*)
        *bl808_ef_ctrl*.o*(.rodata*)

        . = ALIGN(4);
        __tcm_code_end__ = .;
    } > itcm_memory
    
    __dtcm_load_addr = __itcm_load_addr + SIZEOF(.itcm_region);
    
    .dtcm_region : AT (__dtcm_load_addr)
    {
        . = ALIGN(4);
        __tcm_data_start__ = .;
        
        *(.tcm_data)
        /* *finger_print.o(.data*) */
        
        . = ALIGN(4);
        __tcm_data_end__ = .;
    } > dtcm_memory

    /* .heap_dummy section doesn't contains any symbols. It is only
     * used for linker to calculate size of heap sections, and assign
     * values to heap symbols later */
    .heap_dummy (NOLOAD):
    {
        . = ALIGN(0x4);
        . = . + HeapSize;
        . = ALIGN(0x4);
    } > dtcm_memory

    _HeapBase = ORIGIN(dtcm_memory) + LENGTH(dtcm_memory) - StackSize - HeapSize;  
    _HeapSize = HeapSize;
    
    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(_HeapBase >= __tcm_data_end__, "region RAM overflowed with stack")

    /*************************************************************************/
    /* .stack_dummy section doesn't contains any symbols. It is only
     * used for linker to calculate size of stack sections, and assign
     * values to stack symbols later */
    .stack_dummy (NOLOAD):
    {
        . = ALIGN(0x4);
        . = . + StackSize;
        . = ALIGN(0x4);
    } > dtcm_memory
    
    /* Set stack top to end of RAM, and stack limit move down by
     * size of stack_dummy section */
    __StackTop = ORIGIN(dtcm_memory) + LENGTH(dtcm_memory);
    PROVIDE( __freertos_irq_stack_top = __StackTop);
    __StackLimit = __StackTop - SIZEOF(.stack_dummy);
    
    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(__StackLimit >= __tcm_data_end__, "region RAM overflowed with stack")
    /*************************************************************************/
    
    __system_ram_load_addr = __dtcm_load_addr + SIZEOF(.dtcm_region);
    
    .system_ram_data_region : AT (__system_ram_load_addr)
    {
        . = ALIGN(4);
        __system_ram_data_start__ = .;
        
        *(.system_ram)
        
        . = ALIGN(4);
        __system_ram_data_end__ = .;
    } > ram_memory
    
    __ram_load_addr = __system_ram_load_addr + SIZEOF(.system_ram_data_region);
    
    /* Data section */
    RAM_DATA : AT (__ram_load_addr)
    {
        . = ALIGN(4);
        __ram_data_start__ = .;
        
        PROVIDE( __global_pointer$ = . + 0x800 );
        
        *(.data)
        *(.data.*)
        *(.sdata)
        *(.sdata.*)
        *(.sdata2)
        *(.sdata2.*)
        
        . = ALIGN(4);
        __ram_data_end__ = .;
    } > ram_memory
    
    __etext_final = (__ram_load_addr + SIZEOF (RAM_DATA));
    ASSERT(__etext_final <= ORIGIN(code_memory) + LENGTH(code_memory), "code memory overflow")

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        
        *(.bss*)
        *(.sbss*)
        *(COMMON)
        
        . = ALIGN(4);
        __bss_end__ = .;
    } > ram_memory
    
    .noinit_data (NOLOAD) :
    {
        . = ALIGN(4);
        __noinit_data_start__ = .;
        
        *(.noinit_data*)
        
        . = ALIGN(4);
        __noinit_data_end__ = .;
    } > ram_memory
    
    .heap (NOLOAD):
    {
        . = ALIGN(4);
        __HeapBase = .;
        
        /*__end__ = .;*/
        /*end = __end__;*/
        KEEP(*(.heap*))
        
        . = ALIGN(4);
        __HeapLimit = .;
    } > ram_memory
    __HeapLimit = ORIGIN(ram_memory) + LENGTH(ram_memory);
    
}

