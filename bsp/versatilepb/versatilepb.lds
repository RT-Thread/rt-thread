MEMORY
{
	RESERVED	(r)		: ORIGIN = 0x00000000, LENGTH = 32K
	INIT_RAM	(rwx)	: ORIGIN = 0x00008000, LENGTH = 32K
	RAM			(rwx)	: ORIGIN = 0x00010000, LENGTH = 128M
}
ENTRY(start)
SECTIONS
{
    /*
	 * Our init section allows us to place the bootstrap code at address 0x8000
	 *
	 * This is where the Graphics processor forces the ARM to start execution.
	 * However the interrupt vector code remains at 0x0000, and so we must copy the correct
	 * branch instructions to 0x0000 - 0x001C in order to get the processor to handle interrupts.
	 *
	 */
	.init : {
		KEEP(*(.init))
	} > INIT_RAM = 0

	.module_entries : {
		__module_entries_start = .;
	  	KEEP(*(.module_entries))
		KEEP(*(.module_entries.*))
		__module_entries_end = .;
		__module_entries_size = SIZEOF(.module_entries);
	} > RAM

    .text : 
    {
        *(.text)
        *(.gnu.linkonce.t*)
        
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

        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;
        . = ALIGN(4);

        /* section information for modules */
        . = ALIGN(4);
        __rtmsymtab_start = .;
        KEEP(*(RTMSymTab))
        __rtmsymtab_end = .;
    } > RAM

    . = ALIGN(4);
    .rodata : { *(.rodata) *(.rodata.*) *(.gnu.linkonce.r*) *(.eh_frame) } > RAM

    . = ALIGN(4);
    .ctors :
    {
        PROVIDE(__ctors_start__ = .);
        KEEP(*(SORT(.ctors.*)))
        KEEP(*(.ctors))
        PROVIDE(__ctors_end__ = .);
    } > RAM

    .dtors :
    {
        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))
        PROVIDE(__dtors_end__ = .);
    } > RAM

    . = ALIGN(4);
    .data :
    {
        *(.data)
        *(.data.*)
        *(.gnu.linkonce.d*)
    } > RAM

    . = ALIGN(4);
    .nobss : { *(.nobss) } > RAM
    
    . = ALIGN(4);
    
    .bss : { 
        __bss_start__ = .;
        *(.bss)
        *(.bss.*)
         __bss_end__ = .;
    } > RAM

    /* stabs debugging sections. */
    .stab 0 : { *(.stab) } > RAM
    .stabstr 0 : { *(.stabstr) } > RAM
    .stab.excl 0 : { *(.stab.excl) } > RAM
    .stab.exclstr 0 : { *(.stab.exclstr) } > RAM
    .stab.index 0 : { *(.stab.index) } > RAM
    .stab.indexstr 0 : { *(.stab.indexstr) } > RAM
    .comment 0 : { *(.comment) } > RAM
    .debug_abbrev 0 : { *(.debug_abbrev) } > RAM
    .debug_info 0 : { *(.debug_info) } > RAM
    .debug_line 0 : { *(.debug_line) } > RAM
    .debug_pubnames 0 : { *(.debug_pubnames) } > RAM
    .debug_aranges 0 : { *(.debug_aranges) } > RAM

    _end = .;
}
