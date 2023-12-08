OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
SECTIONS
{
    _text_offset = 0x80000;
    . = 0x80000000 + _text_offset;
    .text :
    {
        PROVIDE(__text_start = .);
        KEEP(*(.text.entrypoint))
        *(.vectors)
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)
        *(.gnu.linkonce.t*)
        . = ALIGN(8);
        PROVIDE(__rt_utest_tc_tab_start = .);
        KEEP(*(UtestTcTab))
        PROVIDE(__rt_utest_tc_tab_end = .);
        . = ALIGN(8);
        PROVIDE(__fsymtab_start = .);
        KEEP(*(FSymTab))
        PROVIDE(__fsymtab_end = .);
        . = ALIGN(8);
        PROVIDE(__vsymtab_start = .);
        KEEP(*(VSymTab))
        PROVIDE(__vsymtab_end = .);
        . = ALIGN(8);
        . = ALIGN(8);
        PROVIDE(__rtmsymtab_start = .);
        KEEP(*(RTMSymTab))
        PROVIDE(__rtmsymtab_end = .);
        . = ALIGN(8);
        PROVIDE(__rt_init_start = .);
        KEEP(*(SORT(.rti_fn*)))
        PROVIDE(__rt_init_end = .);
        . = ALIGN(16);
        PROVIDE(__rt_ofw_data_start = .);
        KEEP(*(SORT(.rt_ofw_data.*)))
        PROVIDE(__rt_ofw_data_end = .);
        . = ALIGN(16);
        PROVIDE(__text_end = .);
    }
    .eh_frame_hdr :
    {
        *(.eh_frame_hdr)
        *(.eh_frame_entry)
    }
    .eh_frame : ONLY_IF_RO { KEEP (*(.eh_frame)) }
    . = ALIGN(8);
    .data :
    {
        *(.data)
        *(.data.*)
        *(.data1)
        *(.data1.*)
        . = ALIGN(16);
        _gp = ABSOLUTE(.);
        *(.sdata)
        *(.sdata.*)
        *(.rel.local)
    }
    . = ALIGN(8);
    .cherryusb (ALIGN(64)):
    {
        /* section information for usbh class */
        __usbh_class_info_start__ = .;
        KEEP(*(.usbh_class_info))
        __usbh_class_info_end__ = .;
    }
    . = ALIGN(8);
    .ctors :
    {
        PROVIDE(__ctors_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE(__ctors_end = .);
    }
    .dtors :
    {
        PROVIDE(__dtors_start = .);
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))
        PROVIDE(__dtors_end = .);
    }
    . = ALIGN(16);
    .bss :
    {
        PROVIDE(__bss_noclean_start = .);
        *(.bss.noclean.*)
        PROVIDE(__bss_noclean_end = .);
        . = ALIGN(8);
        PROVIDE(__bss_start = .);
        *(.bss)
        *(.bss.*)
        *(.dynbss)
        *(COMMON)
        . = ALIGN(8);
        PROVIDE(__bss_end = .);
    }
    _end = .;
    .stab 0 : { *(.stab) }
    .stabstr 0 : { *(.stabstr) }
    .stab.excl 0 : { *(.stab.excl) }
    .stab.exclstr 0 : { *(.stab.exclstr) }
    .stab.index 0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment 0 : { *(.comment) }
    .debug 0 : { *(.debug) }
    .line 0 : { *(.line) }
    .debug_srcinfo 0 : { *(.debug_srcinfo) }
    .debug_sfnames 0 : { *(.debug_sfnames) }
    .debug_aranges 0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    .debug_info 0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev 0 : { *(.debug_abbrev) }
    .debug_line 0 : { *(.debug_line) }
    .debug_frame 0 : { *(.debug_frame) }
    .debug_str 0 : { *(.debug_str) }
    .debug_loc 0 : { *(.debug_loc) }
    .debug_macinfo 0 : { *(.debug_macinfo) }
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames 0 : { *(.debug_varnames) }
    __data_size = SIZEOF(.data);
    __bss_size = SIZEOF(.bss);
}
