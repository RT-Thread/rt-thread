OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	. =0xA0000000;

    . = ALIGN(4);
    __text_start = .;
    .text : 
    {
        *(.init)
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
    }
    __text_end = .;

    . = ALIGN(4);
    __rodata_start = .;
    .rodata : { *(.rodata) *(.rodata.*) *(.gnu.linkonce.r*) *(.eh_frame) }
    __rodata_end = .;

    . = ALIGN(4);
    .ctors :
    {
        PROVIDE(__ctors_start__ = .);
        KEEP(*(SORT(.ctors.*)))
        KEEP(*(.ctors))
        PROVIDE(__ctors_end__ = .);
    }

    .dtors :
    {
        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))
        PROVIDE(__dtors_end__ = .);
    }

    . = ALIGN(4);
    __data_start = .;
    .data :
    {
        *(.data)
        *(.data.*)
        *(.gnu.linkonce.d*)
    }
    __data_end = .;

    . = ALIGN(4);
    .nobss : { *(.nobss) }

    . = ALIGN(4);
    __bss_start = .;
    .bss : { *(.bss) }
    __bss_end = .;

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

    _end = .;
}
