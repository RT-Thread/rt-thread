OUTPUT_ARCH( "riscv" )

ENTRY( _start )

MEMORY
{
  flash (rxai!w) : ORIGIN = 0x20400000, LENGTH = 16M
  ram (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 16K
}

PHDRS
{
  flash PT_LOAD;
  ram_init PT_LOAD;
  ram PT_NULL;
}


SECTIONS
{
    __stack_size = DEFINED(__stack_size) ? __stack_size : 512;
    . = 0x20400000;

    . = ALIGN(4);
    .init           :
    {
	    KEEP (*(SORT_NONE(.init)))
    } >flash AT>flash :flash

    .text : 
    {
        *(.init)
	__init_end__ = .;
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
    }>flash AT>flash :flash

    .fini           :
    {
	    KEEP (*(SORT_NONE(.fini)))
    } >flash AT>flash :flash

    PROVIDE (__etext = .);
    PROVIDE (_etext = .);
    PROVIDE (etext = .);


    . = ALIGN(4);
    .rodata : { 
	    *(.rodata) ;
	    *(.rodata.*) ;
	    *(.gnu.linkonce.r*) ;
	    *(.eh_frame) 
    }>flash AT>flash :flash

    . = ALIGN(4);
    .ctors :
    {
        PROVIDE(__ctors_start__ = .);
        KEEP(*(SORT(.ctors.*)))
        KEEP(*(.ctors))
        PROVIDE(__ctors_end__ = .);
    }>flash AT>flash :flash

    .dtors :
    {
        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))
        PROVIDE(__dtors_end__ = .);
    }>flash AT>flash :flash

    .lalign         :
    {
	    . = ALIGN(4);
	    PROVIDE( _data_lma = . );
    } >flash AT>flash :flash

    .dalign         :
    {
	    . = ALIGN(4);
	    PROVIDE( _data = . );
    } >ram AT>flash :ram_init

    . = ALIGN(4);
    .data :
    {
        *(.data)
        *(.data.*)
	. = ALIGN(8);
	PROVIDE( __global_pointer$ = . + 0x800 );
	*(.sdata .sdata.*)
	*(.gnu.linkonce.s.*)
	. = ALIGN(8);
	*(.srodata.cst16)
	*(.srodata.cst8)
	*(.srodata.cst4)
	*(.srodata.cst2)
	*(.srodata .srodata.*)
        *(.gnu.linkonce.d*)
    }>ram AT>flash :ram_init

    . = ALIGN(4);
    .nobss : { *(.nobss) }
    
    . = ALIGN(4);
    PROVIDE( _edata = . );
    PROVIDE( edata = . );

    PROVIDE( _fbss = . );
    PROVIDE( __bss_start = . );
    __bss_start__ = .;
    .bss : { 
	    *(.bss)
	    *(.sbss*)
	    *(.gnu.linkonce.sb.*)
	    *(.bss .bss.*)
	    *(.gnu.linkonce.b.*)
	    *(COMMON)
    	    . = ALIGN(4);
    }>ram AT>flash :ram
    _end = .;
    __bss_end__ = .;

    .stack ORIGIN(ram) + LENGTH(ram) - __stack_size :
    {
	    PROVIDE( _heap_end = . );
	    . = __stack_size;
	    PROVIDE( _sp = . );
    } >ram AT>ram :ram
    /* stabs debugging sections. */
    .stab 0 : { *(.stab) }
    .stabstr 0 : { *(.stabstr) }
    .stab.excl 0 : { *(.stab.excl) }
    .stab.exclstr 0 : { *(.stab.exclstr) }
    .stab.index 0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment 0 : { *(.comment) }
    .debug_abbrev 0 : { *(.debug_abbrev) }
    .debug_info 0 : { *(.debug_info) }
    .debug_line 0 : { *(.debug_line) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    .debug_aranges 0 : { *(.debug_aranges) }

}
