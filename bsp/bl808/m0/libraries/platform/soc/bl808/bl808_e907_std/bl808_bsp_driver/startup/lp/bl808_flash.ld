/****************************************************************************************
* @file flash.ld
*
* @brief This file is the link script file (gnuarm or armgcc).
*
* Copyright (C) BouffaloLab 2021
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

StackSize    = 0x0400; /*  1KB */
HeapMinSize  = 0x1000; /*  4KB */

MEMORY
{
    xip_memory  (rx)  : ORIGIN = 0xD8000000, LENGTH = 32M
    itcm_memory (rx)  : ORIGIN = 0x62020000, LENGTH = 16K
    dtcm_memory (rx)  : ORIGIN = 0x62024000, LENGTH = 4K
    nocache_ram_memory (!rx) : ORIGIN = 0x22050000, LENGTH = 0K
    ram_memory  (!rx) : ORIGIN = 0x62050000, LENGTH = 12K
    xram_memory  (!rx) : ORIGIN = 0x40000000, LENGTH = 16K
}

SECTIONS
{

    .text :
    {
        . = ALIGN(4);
        __text_code_start__ = .;
        KEEP(*startup*.*o(*.text*))
        KEEP (*(SORT_NONE(_start)))
        KEEP (*(SORT_NONE(Reset_Handler)))

        *(.text)
        *(.text.*)

        /* section information for shell */
        . = ALIGN(4);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;

        . = ALIGN(4);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;

        /* section information for usb desc */
        . = ALIGN(4);
        _usb_desc_start = .;
        KEEP(*(usb_desc))
        . = ALIGN(4);
        _usb_desc_end = .;

        /*put .rodata**/
        *(EXCLUDE_FILE( *bl808_glb*.o* \
                        *bl808_glb_gpio*.o* \
                        *bl808_pds*.o* \
                        *bl808_aon*.o* \
                        *bl808_hbn*.o* \
                        *bl808_l1c*.o* \
                        *bl808_common*.o* \
                        *bl808_clock*.o* \
                        *bl808_ef_ctrl*.o* \
                        *bl808_sf_cfg*.o* \
                        *bl808_sf_ctrl*.o* \
                        *bl808_sflash*.o* \
                        *bl808_xip_sflash*.o* \
                        *bl808_romapi_patch*.o* ) .rodata*)
        
        *(.srodata)
        *(.srodata.*)
        
        . = ALIGN(4);
        __text_code_end__ = .;
    } > xip_memory

    . = ALIGN(4);
    __itcm_load_addr = .;

    .itcm_region : AT (__itcm_load_addr)
    {
        . = ALIGN(4);
        __tcm_code_start__ = .;
        
        *(.tcm_code.*)
        *(.tcm_const.*)
        *(.sclock_rlt_code.*)
        *(.sclock_rlt_const.*)
        
        *bl808_glb*.o*(.rodata*)
        *bl808_glb_gpio*.o*(.rodata*)
        *bl808_pds*.o*(.rodata*)
        *bl808_aon*.o*(.rodata*)
        *bl808_hbn*.o*(.rodata*)
        *bl808_l1c*.o*(.rodata*)
        *bl808_common*.o*(.rodata*)
        *bl808_clock*.o*(.rodata*)
        *bl808_ef_ctrl*.o*(.rodata*)
        *bl808_sf_cfg*.o*(.rodata*)
        *bl808_sf_ctrl*.o*(.rodata*)
        *bl808_sflash*.o*(.rodata*)
        *bl808_xip_sflash*.o*(.rodata*)
        *bl808_romapi_patch*.o*(.rodata*)

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
    __nocache_ram_load_addr = __dtcm_load_addr + SIZEOF(.dtcm_region);

    .nocache_ram_region (NOLOAD) : AT (__nocache_ram_load_addr)
    {
        . = ALIGN(4);
        __nocache_ram_data_start__ = .;

        *(.nocache_ram)

        . = ALIGN(4);
        __nocache_ram_data_end__ = .;
    } > nocache_ram_memory

    __system_ram_load_addr = __nocache_ram_load_addr + SIZEOF(.nocache_ram_region);

    .system_ram_data_region : AT (__system_ram_load_addr)
    {
        . = ALIGN(4);
        __system_ram_data_start__ = .;
        
        *(.system_ram)
        
        . = ALIGN(4);
        __system_ram_data_end__ = .;
    } > ram_memory

    .system_ram_noinit_data_region (NOLOAD) :
    {
        . = ALIGN(4);
        *(.system_ram_noinit)

        . = ALIGN(4);
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
    ASSERT(__etext_final <= ORIGIN(xip_memory) + LENGTH(xip_memory), "code memory overflow")
    
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

    .nocache_noinit_ram_region (NOLOAD) : 
    {
        . = ALIGN(4);
        __nocache_ram_data_start__ = .;

        *(.nocache_noinit_ram)

        . = ALIGN(4);
        __nocache_ram_data_end__ = .;
    } > nocache_ram_memory
    
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
    ASSERT(__HeapLimit - __HeapBase >= HeapMinSize, "heap region overflow")

}

