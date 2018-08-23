

ENTRY(Reset_Handler)

INCLUDE "export-rom_symbol_v01.txt"

MEMORY
{
	ROM (rx) : 			ORIGIN = 0x00000000, LENGTH = 0x80000	/* ROM: 512k */
	ROMBSS_RAM (rw)  : 		ORIGIN = 0x10000000, LENGTH = 0x2000	/* ROM BSS RAM: 8K */
	BOOTLOADER_RAM (rwx)  : 	ORIGIN = 0x10002000, LENGTH = 0x3000	/* BOOT Loader RAM: 12K */
	BD_RAM (rwx)  : 		ORIGIN = 0x10005000, LENGTH = 0x2B000	/* MAIN RAM: 228 */
	MSP_RAM (wx)  : 		ORIGIN = 0x1003E000, LENGTH = 0x1000	/* MSP RAM: 4k */
	RDP_RAM (wx)  : 		ORIGIN = 0x1003F000, LENGTH = 0xFF0	/* RDP RAM: 4k-0x10 */

	XIPBOOT (rx)  :			ORIGIN = 0x08000000+0x20, LENGTH = 0x04000-0x20	/* XIPBOOT: 32k, 32 Bytes resvd for header*/
	XIPSYS (r) :			ORIGIN = 0x08009000, LENGTH = 0x1000	/* XIPSYS: 4K system data in flash */
	XIPCAL (r) :			ORIGIN = 0x0800A000, LENGTH = 0x1000	/* XIPCAL: 4K calibration data in flash */
	XIP1 (rx)  : 			ORIGIN = 0x0800B000+0x20, LENGTH = 0x75000-0x20	/* XIP1: 468k, 32 Bytes resvd for header */
	XIP2 (rx)  : 			ORIGIN = 0x08080000+0x20, LENGTH = 0x75000-0x20	/* XIP2: 468k, 32 Bytes resvd for header */
}



SECTIONS
{
	.rom.text : { } > ROM
	.rom.rodata : { } > ROM
	.hal.rom.bss : { } > ROMBSS_RAM

	/* image1 entry, this section should in RAM and fixed address for ROM */
	.ram_image1.entry :
	{
		__ram_image1_text_start__ = .;
		__ram_start_table_start__ = .;
		KEEP(*(SORT(.image1.entry.data*)))
		__ram_start_table_end__ = .;

		__image1_validate_code__ = .;
		KEEP(*(.image1.validate.rodata*))
		KEEP(*(.image1.export.symb*))
	} > BOOTLOADER_RAM

	/*  Add . to assign the start address of the section */ 
	/*  to prevent the change of the start address by ld doing section alignment */  
	.ram_image1.text . :
	{
		/* image1 text */
		*(.boot.ram.text*)    
		*(.boot.rodata*)
	} > BOOTLOADER_RAM

	.ram_image1.data . :
	{
		__ram_image1_data_start__ = .;
		KEEP(*(.boot.ram.data*))
		__ram_image1_data_end__ = .;
	
		__ram_image1_text_end__ = .;
	} > BOOTLOADER_RAM

	.ram_image1.bss . :
	{
		__image1_bss_start__ = .;
		KEEP(*(.boot.ram.bss*))
		KEEP(*(.boot.ram.end.bss*))
		__image1_bss_end__ = .;
	} > BOOTLOADER_RAM

	.ram_image2.entry :
	{
		__ram_image2_text_start__ = .;
		__image2_entry_func__ = .;
		KEEP(*(SORT(.image2.entry.data*)))

		__image2_validate_code__ = .;
		KEEP(*(.image2.validate.rodata*)) 

	} > BD_RAM

	.ram_image2.text :
	{
	  KEEP(*(.image2.ram.text*))
	} > BD_RAM

	.ram_image2.data : 
	{
		__data_start__ = .;
		*(.data*)
		__data_end__ = .;
		__ram_image2_text_end__ = .;
		. = ALIGN(16);	
	} > BD_RAM
  
	.ram_image2.bss :
	{
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
	} > BD_RAM

	.ram_image2.skb.bss :
	{
		*(.bdsram.data*)
		__bss_end__ = .;
	} > BD_RAM

	.ram_heap.data : 
	{
		*(.bfsram.data*)
		*(.heap.stdlib*)
		. = ALIGN(4);
		__rtt_heap_start = .;
	} > BD_RAM

	.ram_rdp.text : 
	{
		__rom_top_4k_start_ = .;
		__rdp_text_start__ = .;
		KEEP(*(.rdp.ram.text*))
		KEEP(*(.rdp.ram.data*))
		__rdp_text_end__ = .;
		. = ALIGN(16);
	
	} > RDP_RAM

	.xip_image1.text :
	{
		__flash_boot_text_start__ = .;

		*(.flashboot.text*)

		__flash_boot_text_end__ = .;

		. = ALIGN(16);
	} > XIPBOOT

	.xip_image2.text : 
	{
		__flash_text_start__ = .;

		*(.img2_custom_signature*)

		*(.text*)    
		*(.rodata*)
		*(.debug_trace*)

		__flash_text_end__ = .;
	
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

        /* section information for initial. */
        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;
        . = ALIGN(4);
	
		. = ALIGN (16);
	} > XIP1
}

SECTIONS 
{ 
	/* Bootloader symbol list */  
  boot_export_symbol = 0x10002020;  
} 
