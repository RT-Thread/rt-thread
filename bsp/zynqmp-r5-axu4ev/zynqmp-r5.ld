MEMORY
{
   psu_ocm_ram_0_MEM_0 : ORIGIN = 0xFFFC0000, LENGTH = 0x40000
   psu_qspi_linear_0_MEM_0 : ORIGIN = 0xC0000000, LENGTH = 0x20000000
   psu_r5_0_atcm_MEM_0 : ORIGIN = 0x0, LENGTH = 0x10000
   psu_r5_0_btcm_MEM_0 : ORIGIN = 0x20000, LENGTH = 0x10000
   psu_r5_ddr_0_MEM_0 : ORIGIN = 0x100000, LENGTH = 0x7FE00000
   psu_r5_tcm_ram_0_MEM_0 : ORIGIN = 0x0, LENGTH = 0x40000
}

ENTRY(_reset)

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
SECTIONS
{
    .vectors :
    {
        KEEP (*(.vectors))
        *(.boot)
        *(.text.isr)
    } > psu_r5_0_atcm_MEM_0

    __text_start = .;
    .text :
    {
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
    } > psu_r5_ddr_0_MEM_0 = 0
    __text_end = .;

    __exidx_start = .;
    .ARM.exidx   : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) } > psu_r5_ddr_0_MEM_0
    __exidx_end = .;

    .note-ABI-tag :
    {
        KEEP (*(.note-ABI-tag))
    } > psu_r5_ddr_0_MEM_0

    .note.gnu.build-id :
    {
        KEEP (*(.note.gnu.build-id))
    } > psu_r5_ddr_0_MEM_0

    __rodata_start = .;
    .rodata   : { *(.rodata) *(.rodata.*) } > psu_r5_ddr_0_MEM_0
    __rodata_end = .;

    . = ALIGN(4);
    .ctors :
    {
        PROVIDE(__ctors_start__ = .);
        /* new GCC version uses .init_array */
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE(__ctors_end__ = .);
    } > psu_r5_ddr_0_MEM_0

    .dtors :
    {
        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))
        PROVIDE(__dtors_end__ = .);
    } > psu_r5_ddr_0_MEM_0

    . = ALIGN(4);
    __data_start = .;
    .data :
    {
        *(.data)
        *(.data.*)
    } > psu_r5_ddr_0_MEM_0
    __data_end = .;

    . = ALIGN(4);
    __bss_start = .;
    .bss       :
    {
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
    } > psu_r5_ddr_0_MEM_0
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