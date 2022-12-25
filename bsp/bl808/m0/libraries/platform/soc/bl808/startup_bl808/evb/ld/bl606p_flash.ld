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
BOOT2_PT_ADDR = 0x62047e00;
BOOT2_FLASHCFG_ADDR = 0x62047f14;

MEMORY
{
    flash    (rxai!w) : ORIGIN = 0x58000000, LENGTH = 4M
    xram_memory (!rx) : ORIGIN = 0x22020000, LENGTH = 16K 
    ram_memory  (!rx) : ORIGIN = 0x22024000, LENGTH = 48K
    ram_wifi    (!rx) : ORIGIN = 0x22030000, LENGTH = 96K 
    ram_psram  (!rx)  : ORIGIN = 0x54000000, LENGTH = 4M
    bugkill   (rxai!w) : ORIGIN = 0xD0000000, LENGTH = 16M
}

SECTIONS
{
    PROVIDE(__metal_chicken_bit = 0);
    
    .text.boot :
    {
        . = ALIGN(4);
    
        *(.text.entry)

        . = ALIGN(4);
    } > flash

    .bugkiller_command :
    {
        PROVIDE( __bugkiller_command_start = ADDR(.bugkiller_command) );
        PROVIDE( __bugkiller_command_end = ADDR(.bugkiller_command) + SIZEOF(.bugkiller_command) );
        KEEP (*(.static_bugkiller_command))
    } > bugkill

    .bugkiller :
    {
        KEEP (*(.bugkiller_code))
        KEEP (*bugkiller*.o(.rodata* .text* .data* .sdata* .sbss*))
    } > bugkill

    .psram_ram_data_region : 
    {
        . = ALIGN(4);
        __psram_ram_data_start__ = .;
 
        *(.psram_data.*)
        *liblwip.a:*.o(.text*)
        *libwifi.a:*.o(.text*)
        *libwifi_manager.a:*.o(.text*)
        *libfreertos_e907.a:*.o(.text*)
        *libnetutils.a:*.o(.text*)
        *libutils.a:*.o(.text*)
        *libstartup_bl808.a:debug.o(.text*)

        *liblwip.a:*.o(.rodata*)
        *libwifi.a:*.o(.rodata*)
        *libwifi_manager.a:*.o(.rodata*)
        *libfreertos_e907.a:*.o(.rodata*)
        *libnetutils.a:*.o(.rodata*)
        *libutils.a:*.o(.rodata*)
        *libstartup_bl808.a:debug.o(.rodata*)
        
        . = ALIGN(4);
        __psram_ram_data_end__ = .;
    } > ram_psram AT > flash

    .text :
    {
        . = ALIGN(4);
    
        *(.text)
        *(.text.*)

        . = ALIGN(4);
    } > flash

    .rodata :
    {
        . = ALIGN(4);
        
        *(.rodata)
        *(.rodata.*)
    
        *(.srodata)
        *(.srodata.*)

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

    } > flash

    .itcm_region :
    {
        . = ALIGN(4);
        __tcm_code_start__ = .;

        *(.tcm_code)
        *(.tcm_code.*)
        *(.tcm_const)
        *(.tcm_const.*)
        *(.sclock_rlt_code)
        *(.sclock_rlt_code.*)
        *(.sclock_rlt_const)
        *(.sclock_rlt_const.*)
        
        . = ALIGN(4);
        __tcm_code_end__ = .;
    } > ram_psram AT > flash

    .dtcm_region : 
    {
        . = ALIGN(4);
        __tcm_data_start__ = .;
        
        *(.tcm_data)
        
        . = ALIGN(4);
        __tcm_data_end__ = .;
    } > ram_psram AT > flash

    .stack_dummy (NOLOAD):
    {
	PROVIDE ( _sp_base = . );
        . = ALIGN(64);
        __stack_protect_start = .;
        . = . + 256;
        __stack_protect_end = .;
        . = . + StackSize;
        . = ALIGN(64);
	PROVIDE( _sp_main = . );
    } > ram_psram

    .system_ram_data_region : 
    {
        . = ALIGN(4);
        __system_ram_data_start__ = .;
 
        *(.system_ram)
        
        . = ALIGN(4);
        __system_ram_data_end__ = .;
    } > ram_psram AT > flash

    .data : 
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
    } > ram_psram AT > flash

    .xrambss  (NOLOAD) :
    {
        __xram_load_addr = .;
        
        . = ALIGN(4);
        __xram_data_start__ = .;

        *(.static_xram_region)

        __xram_data_end__ = .;
        . = ALIGN(4);
    } > xram_memory

    .ocram_bss_region (NOLOAD) :
    {
        . = ALIGN(4);
        __ocram_bss_start__ = .;

        *(.nocache_ram)

        . = ALIGN(4);
        __ocram_bss_end__ = .;
    } > ram_memory

    .boot2 (NOLOAD) :
    {
        PROVIDE ( __boot2_pt_addr_start = . );
        *(.bss.boot2_partition_table)
        PROVIDE ( __boot2_pt_addr_end   = . );

        PROVIDE ( __boot2_flashCfg_start = . );
        *(.bss.boot2_flashCfg)
        PROVIDE ( __boot2_flashCfg_end = . );

    } > ram_psram
    
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
        
        *(.bss*)
        *(.sbss*)
        *(.noinit_data*)
        *(COMMON)
 
        . = ALIGN(4);
        __bss_end__ = .;
    } > ram_psram 

    .heap (NOLOAD):
    {
        . = ALIGN(4);
        __HeapBase = .;
        _heap_start = .;
        
        KEEP(*(.heap*))
        
        . = ALIGN(4);
        __HeapLimit = .;
        _heap_end = .;
    } > ram_psram 

    __StackTop = ADDR(.stack_dummy) + SIZEOF(.stack_dummy);
    PROVIDE( __freertos_irq_stack_top = __StackTop);
    __StackLimit = ADDR(.stack_dummy);

    __HeapLimit = ORIGIN(ram_psram) + LENGTH(ram_psram);
    _heap_size = __HeapLimit - _heap_start;

    PROVIDE( __itcm_load_addr = LOADADDR(.itcm_region));
    PROVIDE( __dtcm_load_addr = LOADADDR(.dtcm_region));
    PROVIDE( __system_ram_load_addr = LOADADDR(.system_ram_data_region));
    PROVIDE( __psram_ram_load_addr = LOADADDR(.psram_ram_data_region));
    PROVIDE( __ram_load_addr = LOADADDR(.data));

    /*SYMOBOL used in code*/
    PROVIDE( _ld_bl_static_cli_cmds_start = _bl_static_cli_cmds_start );
    PROVIDE( _ld_bl_static_cli_cmds_end   = _bl_static_cli_cmds_end );

    /*BOOT2 sections*/
    PROVIDE ( __boot2_pt_addr_src = BOOT2_PT_ADDR );
    PROVIDE ( __boot2_flashCfg_src = BOOT2_FLASHCFG_ADDR );
    
    PROVIDE( _ld_ram_size0 = LENGTH(flash) );
    PROVIDE( _ld_ram_addr0 = ORIGIN(flash) );
    PROVIDE( _ld_ram_size1 = LENGTH(ram_psram) );
    PROVIDE( _ld_ram_addr1 = ORIGIN(ram_psram) );
    PROVIDE( _ld_ram_size2 = LENGTH(ram_wifi) );
    PROVIDE( _ld_ram_addr2 = ORIGIN(ram_wifi) );
    PROVIDE( _ld_ram_size3 = LENGTH(ram_memory) );
    PROVIDE( _ld_ram_addr3 = ORIGIN(ram_memory) );
    PROVIDE( _ld_ram_size4 = LENGTH(xram_memory) );
    PROVIDE( _ld_ram_addr4 = ORIGIN(xram_memory) );
 
    /* blog */
    PROVIDE( _ld_bl_static_blogcomponent_code_start = _bl_static_blogcomponent_code_start );
    PROVIDE( _ld_bl_static_blogcomponent_code_end   = _bl_static_blogcomponent_code_end );
    PROVIDE( _ld_bl_static_blogfile_code_start = _bl_static_blogfile_code_start );
    PROVIDE( _ld_bl_static_blogfile_code_end   = _bl_static_blogfile_code_end );
    PROVIDE( _ld_bl_static_blogpri_code_start = _bl_static_blogpri_code_start );
    PROVIDE( _ld_bl_static_blogpri_code_end   = _bl_static_blogpri_code_end );

    PROVIDE( _ld_bl_static_cfg_entry_start = _bl_static_fw_cfg_entry_start );
    PROVIDE( _ld_bl_static_cfg_entry_end   = _bl_static_fw_cfg_entry_end );
}
