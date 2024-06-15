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
ENTRY(__start)

StackSize    = 0x0400; /*  1KB */
HeapMinSize  = 0x1000; /*  4KB */

MEMORY
{
    fw_header_memory  (rx)  : ORIGIN = 0x58000000 - 0x1000, LENGTH = 4K
    xip_memory  (rx)  : ORIGIN = 0x58000000, LENGTH = 32M
    itcm_memory (rx)  : ORIGIN = 0x62020000, LENGTH = 20K
    dtcm_memory (rx)  : ORIGIN = 0x62025000, LENGTH = 4K
    nocache_ram_memory (!rx) : ORIGIN = 0x22026000, LENGTH = 0K
    ram_memory  (!rx) : ORIGIN = 0x22026000, LENGTH = 40K
    ram_wifi    (!rx) : ORIGIN = 0x22030000, LENGTH = 96K 
    ram_dram  (wxa)   : ORIGIN = 0x3EF80000, LENGTH = 512K
    xram_memory  (!rx) : ORIGIN = 0x40000000, LENGTH = 16K
    ram_psram  (!rx)  : ORIGIN = 0x50000000, LENGTH = 1M
}

SECTIONS
{
    .fw_header :
    {
        KEEP(*(.fw_header))
    } > fw_header_memory

    .text :
    {
        . = ALIGN(4);
        __text_code_start__ = .;

        KEEP (*(SORT_NONE(.init)))
        KEEP (*(SORT_NONE(.vector)))

        *(.text)
        *(.text.*)

        /* section information for finsh shell */
        . = ALIGN(4);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;
        . = ALIGN(4);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;
        . = ALIGN(4);

        /* section information for modules */
        . = ALIGN(4);
        __rtmsymtab_start = .;
        KEEP(*(RTMSymTab))
        __rtmsymtab_end = .;

        /* section information for initialization */
        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;

        /* section information for usb usbh_class_info */
        . = ALIGN(4);
        __usbh_class_info_start__ = .;
        KEEP(*(.usbh_class_info))
        . = ALIGN(4);
        __usbh_class_info_end__ = .;

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

        /* static fw attribute entry */
        . = ALIGN(4);
        _bl_static_fw_cfg_entry_start = .;
        KEEP(*(.wifi.cfg.entry))
        _bl_static_fw_cfg_entry_end = .;
        
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
    PROVIDE( __rt_rvstack = . );
    __StackLimit = __StackTop - SIZEOF(.stack_dummy);

    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(__StackLimit >= __tcm_data_end__, "region RAM overflowed with stack")
    /*************************************************************************/
    __nocache_ram_load_addr = __dtcm_load_addr + SIZEOF(.dtcm_region);

    .nocache_ram_region  : AT (__nocache_ram_load_addr)
    {
        . = ALIGN(4);
        __nocache_ram_data_start__ = .;

        *(.nocache_ram)

        . = ALIGN(4);
        __nocache_ram_data_end__ = .;
    } > nocache_ram_memory

    __ram_load_addr = __nocache_ram_load_addr + SIZEOF(.nocache_ram_region);

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
        __bflog_tags_start__ = .;
        *(.bflog_tags_array)
        . = ALIGN(4);
        __bflog_tags_end__ = .;
        __ram_data_end__ = .;
    } > ram_memory

    __etext_final = (__ram_load_addr + SIZEOF (RAM_DATA));
    ASSERT(__etext_final <= ORIGIN(xip_memory) + LENGTH(xip_memory), "code memory overflow")

    .wifibss  (NOLOAD) :
    {
        PROVIDE( __wifi_bss_start = ADDR(.wifibss) );
        PROVIDE( __wifi_bss_end = ADDR(.wifibss) + SIZEOF(.wifibss) );
        *ipc_shared.o(COMMON)
        *sdu_shared.o(COMMON)
        *hal_desc.o(COMMON)
        *txl_buffer_shared.o(COMMON)
        *txl_frame_shared.o(COMMON)
        *scan_shared.o(COMMON)
        *scanu_shared.o(COMMON)
        *mfp_bip.o(COMMON)
        *me_mic.o(COMMON)
        *bl_sta_mgmt_others.o(COMMON)
        *bl_pmk_mgmt.o(COMMON)
        *bl_pmk_mgmt_internal.o(COMMON)
        *libwifi_drv.a:bl_utils.o(COMMON)
        *libwifi_drv.a:bl_utils.o(.bss*)
        *(.wifi_ram*)
        . = ALIGN(16);
    } > ram_wifi

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        __bss_start__ = .;

        *interrupt*.o*(.bss*)
        *riscv_fpu*.o*(.bss*)
        *start*.o*(.bss*)
        *system_bl808*.o*(.bss*)
        *vector*.o*(.bss*)
        *bl808_*.o*(.bss*)
        *bflb_*.o*(.bss*)

        *(.sbss*)

        . = ALIGN(4);
        __bss_end__ = .;
    } > ram_memory

    .drambss (NOLOAD) :
    {
        . = ALIGN(4);
        __drambss_start__ = .;

        . = ALIGN(4);
        __drambss_end__ = .;
    } > ram_dram

    .psrambss (NOLOAD) :
    {
        . = ALIGN(4);
        __psrambss_start__ = .;

        *(EXCLUDE_FILE( *interrupt*.o* \
        *riscv_fpu*.o* \
        *start*.o* \
        *system_bl808*.o* \
        *vector*.o* \
        *bl808_*.o* \
        *bflb_*.o* ) .bss*)
        *(COMMON)

        . = ALIGN(4);
        __psrambss_end__ = .;
    } > ram_psram

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
        __nocache_noinit_ram_data_start__ = .;

        *(.nocache_noinit_ram)
        *(.noncacheable)

        . = ALIGN(4);
        __nocache_noinit_ram_data_end__ = .;
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
    } > ram_psram

    __HeapLimit = ORIGIN(ram_psram) + LENGTH(ram_psram);
    ASSERT(__HeapLimit - __HeapBase >= HeapMinSize, "heap region overflow")

    PROVIDE( _ld_ram_size2 = LENGTH(ram_wifi) );
    PROVIDE( _ld_ram_addr2 = ORIGIN(ram_wifi) );

    PROVIDE( _ld_bl_static_cfg_entry_start = _bl_static_fw_cfg_entry_start );
    PROVIDE( _ld_bl_static_cfg_entry_end   = _bl_static_fw_cfg_entry_end );
}

