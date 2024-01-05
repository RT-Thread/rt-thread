OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
SECTIONS
{
    . = 0x60010000;

    __text_start = .;
    .text :
    {
        *(.vectors)
        *(.text)
        *(.text.*)

        /* section information for utest */
        . = ALIGN(4);
        __rt_utest_tc_tab_start = .;
        KEEP(*(UtestTcTab))
        __rt_utest_tc_tab_end = .;

        /* section information for finsh shell */
        . = ALIGN(4);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;
        . = ALIGN(4);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;

        /* section information for var export */
        . = ALIGN(4);
        __ve_table_start = .;
        KEEP(*(SORT(*.VarExpTab.*)))
        __ve_table_end = .;

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
    } =0
    __text_end = .;

    .ARM.exidx   :
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    }

    __rodata_start = .;
    .rodata   : { *(.rodata) *(.rodata.*) }
    __rodata_end = .;

    . = ALIGN(4);
    .ctors :
    {
        PROVIDE(__ctors_start__ = .);
        /* new GCC version uses .init_array */
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE(__ctors_end__ = .);
    }

    .dtors :
    {
        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE(__dtors_end__ = .);
    }

    . = ALIGN(8);
    __data_start = .;
    .data :
    {
        *(.data)
        *(.data.*)
    }
    __data_end = .;

    . = ALIGN(8);
    .tdata :
    {
         __tdata_start = .;
        *(.tdata .tdata.* .gnu.linkonce.td.*)
        __tdata_end = .;
    }
    __tdata_source = LOADADDR(.tdata);
    __tdata_size = SIZEOF(.tdata);

    /*
     * TLS zeroed data is relocated as if it immediately followed
     * the tdata values. However, the linker 'magically' erases the
     * memory allocation so that no ROM is consumed by this
     * section
     */
    .tbss :
    {
        *(.tbss .tbss.* .gnu.linkonce.tb.*)
        *(.tcommon)
        __tbss_end = .;
    }
    __tls_size = __tbss_end - __tdata_start;
    __tbss_size = __tls_size - __tdata_size;
    PROVIDE( __tbss_offset = ADDR(.tbss) - ADDR(.tdata) );
    PROVIDE( __tls_align = MAX(ALIGNOF(.tdata), ALIGNOF(.tbss)) );
    PROVIDE( __arm32_tls_tcb_offset = MAX(8, __tls_align) );
    PROVIDE( __arm64_tls_tcb_offset = MAX(16, __tls_align) );

    . = ALIGN(4);
    __bss_start = .;
    .bss       :
    {
    *(.bss)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
    }
    . = ALIGN(4);
    __bss_end = .;

    /* Stabs debugging sections.  */
    .stab 0 : { *(.stab) }
    .stabstr 0 : { *(.stabstr) }
    .stab.excl 0 : { *(.stab.excl) }
    .stab.exclstr 0 : { *(.stab.exclstr) }
    .stab.index 0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment 0 : { *(.comment) }

    _end = .;
}
