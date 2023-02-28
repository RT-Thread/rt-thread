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
ENTRY(risc_e906_start)

StackSize = 0x0400; /*  1KB */

MEMORY
{
    code_memory       (rx)  : ORIGIN = 0x22030000, LENGTH = 128K
    ram_wifi          (!rx) : ORIGIN = 0x22050000, LENGTH = 32K
    ram_memory        (!rx) : ORIGIN = 0x22020000, LENGTH = 28K
    itcm_memory       (rx)  : ORIGIN = 0x22027000, LENGTH = 2K
    dtcm_memory       (rx)  : ORIGIN = 0x22027800, LENGTH = 2K
    test_ocram        (!rx) : ORIGIN = 0x22028000, LENGTH = 32K
}

SECTIONS
{
    PROVIDE(__metal_chicken_bit = 0);
    
    .text :
    {
        . = ALIGN(4);
        __text_code_start__ = .;
        
        KEEP (*(SORT_NONE(_start)))
        KEEP (*(SORT_NONE(risc_e906_start)))
        
        *(.text)
        *(.text.*)
        
        *(.rodata)
        *(.rodata.*)
    
        *(.srodata)
        *(.srodata.*)
        
        *(.tcm_code)
        *(.tcm_const)
        *(.sclock_rlt_code)
        *(.sclock_rlt_const)

        /* static cli cmds */
        . = ALIGN(4);
        _bl_static_cli_cmds_start = .;
        KEEP(*(.static_cli_cmds))
        *(.static_cli_cmds)
        _bl_static_cli_cmds_end = .;    
        
        /* static blog code1 */
        . = ALIGN(4);
        _bl_static_blogcomponent_code_start = .;
        KEEP(SORT(*)(.static_blogcomponent_code*))
        *(.static_blogcomponent_code*)
        _bl_static_blogcomponent_code_end = .;
    
        /* static blog code2 */
        . = ALIGN(4);
        _bl_static_blogfile_code_start = .;
        KEEP(SORT(*)(.static_blogfile_code*))
        *(.static_blogfile_code*)
        _bl_static_blogfile_code_end = .;
    
        /* static blog code3 */
        . = ALIGN(4);
        _bl_static_blogpri_code_start = .;
        KEEP(SORT(*)(.static_blogpri_code*))
        *(.static_blogpri_code*)
        _bl_static_blogpri_code_end = .;
    
        /* static fw attribute entry */
        . = ALIGN(4);
        _bl_static_fw_cfg_entry_start = .;
        KEEP(*(.wifi.cfg.entry))
        _bl_static_fw_cfg_entry_end = .;
        . = ALIGN(4);

        __text_code_end__ = .;
    } > code_memory

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

    PROVIDE( _heap_wifi_start = . );
    PROVIDE( _heap_wifi_size = ORIGIN(ram_wifi) + LENGTH(ram_wifi) - _heap_wifi_start );

    /*SYMOBOL used in code*/
    PROVIDE( _ld_bl_static_cli_cmds_start = _bl_static_cli_cmds_start );
    PROVIDE( _ld_bl_static_cli_cmds_end   = _bl_static_cli_cmds_end );

    . = ALIGN(4);
    __itcm_load_addr = .;
    
    .itcm_region : AT (__itcm_load_addr)
    {
        . = ALIGN(4);
        __tcm_code_start__ = .;
        
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
        
        _bt_gatt_service_static_list_start = .;
        KEEP(*(SORT_BY_NAME("._bt_gatt_service_static.static.*")))
        _bt_gatt_service_static_list_end = .;
        _bt_l2cap_fixed_chan_list_start = .;
        KEEP(*(SORT_BY_NAME("._bt_l2cap_fixed_chan.static.*")))
        _bt_l2cap_fixed_chan_list_end = .;
        _bt_l2cap_br_fixed_chan_list_start = .;
        KEEP(*(SORT_BY_NAME("._bt_l2cap_br_fixed_chan.static.*")))
        _bt_l2cap_br_fixed_chan_list_end = .;

        . = ALIGN(4);
        __ram_data_end__ = .;
    } > ram_memory
    
    .noinit_data (NOLOAD) :
    {
        . = ALIGN(4);
        __noinit_data_start__ = .;
        
        *(.noinit_data*)
        
        . = ALIGN(4);
        __noinit_data_end__ = .;
    } > ram_memory
    
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

    .heap (NOLOAD):
    {
        . = ALIGN(4);
        __HeapBase = .;
        _heap_start = .;
        
        /*__end__ = .;*/
        /*end = __end__;*/
        KEEP(*(.heap*))
        
        . = ALIGN(4);
        __HeapLimit = .;
    } > ram_memory
    __HeapLimit = ORIGIN(ram_memory) + LENGTH(ram_memory);
    _heap_size = __HeapLimit - __HeapBase;

    /* keep my variable even if not referenced */
    /* .testmem_at_ocram (NOLOAD) : 
    {
        PROVIDE( __testmem_at_ocram_start_addr = ADDR(.testmem_at_ocram) );
        PROVIDE( __testmem_at_wram_start_addr = ADDR(.testmem_at_ocram) + SIZEOF(.testmem_at_ocram) );
        KEEP(*(.testmem_at_ocram))
    } > ram_test */

    /* __testmem_at_ocram_start_addr = ORIGIN(ram_test);
    __testmem_at_wram_start_addr = ORIGIN(wifi_ram); */

    __testmem_at_ocram_start_addr = ORIGIN(test_ocram);
    __testmem_at_wram_start_addr = ORIGIN(ram_wifi);
}

PROVIDE( _ld_ram_size0 = LENGTH(ram_memory) );
PROVIDE( _ld_ram_addr0 = ORIGIN(ram_memory) );
PROVIDE( _ld_ram_size1 = 0);
PROVIDE( _ld_ram_addr1 = 0);
PROVIDE( _ld_ram_size2 = LENGTH(ram_wifi) );
PROVIDE( _ld_ram_addr2 = ORIGIN(ram_wifi) );

/* blog */
PROVIDE( _ld_bl_static_blogcomponent_code_start = _bl_static_blogcomponent_code_start );
PROVIDE( _ld_bl_static_blogcomponent_code_end   = _bl_static_blogcomponent_code_end );
PROVIDE( _ld_bl_static_blogfile_code_start = _bl_static_blogfile_code_start );
PROVIDE( _ld_bl_static_blogfile_code_end   = _bl_static_blogfile_code_end );
PROVIDE( _ld_bl_static_blogpri_code_start = _bl_static_blogpri_code_start );
PROVIDE( _ld_bl_static_blogpri_code_end   = _bl_static_blogpri_code_end );


PROVIDE( _ld_bl_static_cfg_entry_start = _bl_static_fw_cfg_entry_start );
PROVIDE( _ld_bl_static_cfg_entry_end   = _bl_static_fw_cfg_entry_end );
