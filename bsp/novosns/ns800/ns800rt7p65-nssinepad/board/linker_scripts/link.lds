/*
 * GNU ld linker script for NS800RT7P65 (Cortex-M7)
 *
 * Memory layout derived from the existing MDK scatter file:
 *   FLASH      0x08000000  512K
 *   VT_DTCM    0x20000000    1K
 *   DTCM       0x20000400   71K  (general RW/ZI/stack region)
 *   RT_HEAP    0x20012000   16K  (reserved for rt_system_heap_init)
 *   DTCM_EXT   0x20016000   40K  (extra named sections only)
 *   SRAM1      0x20100000  128K
 *   SRAM2      0x20120000  128K
 *   BKPSRAM    0x400B7000    4K
 */

ENTRY(Reset_Handler)

_system_stack_size = 0x1000;

MEMORY
{
    FLASH    (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
    VT_DTCM  (rwx) : ORIGIN = 0x20000000, LENGTH = 0x400
    DTCM     (rwx) : ORIGIN = 0x20000400, LENGTH = 0x11C00
    RT_HEAP  (rwx) : ORIGIN = 0x20012000, LENGTH = 0x4000
    DTCM_EXT (rwx) : ORIGIN = 0x20016000, LENGTH = 0xA000
    SRAM1    (rwx) : ORIGIN = 0x20100000, LENGTH = 0x20000
    SRAM2    (rwx) : ORIGIN = 0x20120000, LENGTH = 0x20000
    BKPSRAM  (rwx) : ORIGIN = 0x400B7000, LENGTH = 0x1000
}

SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        _stext = .;
        KEEP(*(.isr_vector))

        . = ALIGN(4);
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)
        *(.gnu.linkonce.t*)
        *(.itcm)
        *(.itcm*)

        . = ALIGN(4);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;

        . = ALIGN(4);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;

        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;

        . = ALIGN(4);
        PROVIDE(__ctors_start__ = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE(__ctors_end__ = .);

        . = ALIGN(4);
        _etext = .;
    } > FLASH = 0

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        _sidata = .;
    } > FLASH
    __exidx_end = .;

    .data : AT (_sidata)
    {
        . = ALIGN(4);
        _sdata = .;

        *(.data)
        *(.data.*)
        *(.gnu.linkonce.d*)
        *(.dtcm)
        *(.dtcm*)

        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))
        PROVIDE(__dtors_end__ = .);

        . = ALIGN(4);
        _edata = .;
    } > DTCM

    .stack :
    {
        . = ALIGN(8);
        _sstack = .;
        . = . + _system_stack_size;
        . = ALIGN(8);
        _estack = .;
    } > DTCM

    __bss_start = .;
    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        _sbss = .;

        *(.bss)
        *(.bss.*)
        *(COMMON)

        . = ALIGN(4);
        _ebss = .;

        *(.bss.init)
    } > DTCM
    __bss_end = .;

    .vt_dtcm (NOLOAD) :
    {
        . = ALIGN(4);
        *(.vt_dtcm)
        *(.vt_dtcm*)
        . = ALIGN(4);
    } > VT_DTCM

    .sram1 (NOLOAD) :
    {
        . = ALIGN(4);
        *(.sram1)
        *(.sram1*)
        . = ALIGN(4);
    } > SRAM1

    .sram2 (NOLOAD) :
    {
        . = ALIGN(4);
        *(.sram2)
        *(.sram2*)
        . = ALIGN(4);
    } > SRAM2

    .bkupsram (NOLOAD) :
    {
        . = ALIGN(4);
        *(.bss.bkupsram)
        *(.bss.bkupsram*)
        . = ALIGN(4);
    } > BKPSRAM

    .dtcm_ext (NOLOAD) :
    {
        . = ALIGN(4);
        *(.dtcm_ext)
        *(.dtcm_ext*)
        . = ALIGN(4);
    } > DTCM_EXT

    .rt_heap (NOLOAD) :
    {
        . = ALIGN(8);
        PROVIDE(Image$$RW_RT_HEAD$$Base = .);
        PROVIDE(Image$$RW_RT_HEAD$$Limit = .);
        PROVIDE(__rt_heap_start = .);
        . = . + LENGTH(RT_HEAP);
        . = ALIGN(8);
        PROVIDE(Image$$RW_RT_HEAD$$End = .);
        PROVIDE(__rt_heap_end = .);
    } > RT_HEAP

    _end = .;

    .stab          0 : { *(.stab) }
    .stabstr       0 : { *(.stabstr) }
    .stab.excl     0 : { *(.stab.excl) }
    .stab.exclstr  0 : { *(.stab.exclstr) }
    .stab.index    0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment) }
    .debug         0 : { *(.debug) }
    .line          0 : { *(.line) }
    .debug_srcinfo 0 : { *(.debug_srcinfo) }
    .debug_sfnames 0 : { *(.debug_sfnames) }
    .debug_aranges 0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    .debug_info    0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev  0 : { *(.debug_abbrev) }
    .debug_line    0 : { *(.debug_line) }
    .debug_frame   0 : { *(.debug_frame) }
    .debug_str     0 : { *(.debug_str) }
    .debug_loc     0 : { *(.debug_loc) }
    .debug_macinfo 0 : { *(.debug_macinfo) }
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }
}
