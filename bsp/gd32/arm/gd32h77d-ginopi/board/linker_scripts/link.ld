/* memory map */
MEMORY
{
  CNVM_BOOT (rx)  : ORIGIN = 0x08000000, LENGTH = 8
  CNVM    (rx)  : ORIGIN = 0x08010000, LENGTH = 1984K
  ECNVM   (rx)  : ORIGIN = 0x08200000, LENGTH = 7680K
  AXISRAM (xrw) : ORIGIN = 0x24000000, LENGTH = 768K
  SRAM1   (xrw) : ORIGIN = 0x30004000, LENGTH = 16K
  ITCMRAM (xrw) : ORIGIN = 0x00000000, LENGTH = 128K
  DTCMRAM (xrw) : ORIGIN = 0x20000000, LENGTH = 256K
}

ENTRY(Reset_Handler)
_system_stack_size = 0x1000;

SECTIONS
{
    .boot_fuction_table ORIGIN(CNVM_BOOT) :
    {
        . = ALIGN(4);
        KEEP(*(.boot_fuction_table))
        . = ALIGN(4);
    } > CNVM_BOOT

    ASSERT(SIZEOF(.boot_fuction_table) == 8, "invalid boot function table size")

    /* The application vector table starts at 0x08010000. */
    .vectors ORIGIN(CNVM) :
    {
        . = ALIGN(4);
        KEEP(*(.vectors))
        KEEP(*(.isr_vector))
        . = ALIGN(4);
        __Vectors_End = .;
        __Vectors_Size = __Vectors_End - __gVectors;
    } > CNVM

    __Vectors = __gVectors;

    /* Keep startup code in CNVM so DAP-Link/PyOCD can program the primary flash region. */
    .reset :
    {
        . = ALIGN(4);
        _stext = .;
        KEEP(*(.text.Reset_Handler))
        . = ALIGN(4);
    } > CNVM = 0

    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text.*)
        *(.gnu.linkonce.t*)
        *(.glue_7)
        *(.glue_7t)
        *(.eh_frame*)
        KEEP(*(.init))
        KEEP(*(.fini))

        *(.rodata)
        *(.rodata*)
        *(.gnu.linkonce.r*)

        /* section information for finsh shell */
        . = ALIGN(4);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;

        . = ALIGN(4);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;

        /* section information for RT-Thread initialization */
        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;

        /* section information for utest */
        . = ALIGN(4);
        __rt_utest_tc_tab_start = .;
        KEEP(*(UtestTcTab))
        __rt_utest_tc_tab_end = .;

        . = ALIGN(4);
        _etext = .;
    } > CNVM = 0

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > CNVM

    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > CNVM

    .preinit_array (READONLY) :
    {
        PROVIDE_HIDDEN(__preinit_array_start = .);
        KEEP(*(.preinit_array*))
        PROVIDE_HIDDEN(__preinit_array_end = .);
    } > CNVM

    .init_array (READONLY) :
    {
        PROVIDE_HIDDEN(__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array*))
        PROVIDE_HIDDEN(__init_array_end = .);
    } > CNVM

    .fini_array (READONLY) :
    {
        PROVIDE_HIDDEN(__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array*))
        PROVIDE_HIDDEN(__fini_array_end = .);
    } > CNVM

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data.*)
        *(.gnu.linkonce.d*)
        . = ALIGN(4);
        _edata = .;
    } > AXISRAM AT> CNVM
    _sidata = LOADADDR(.data);

    /* Reserve the MSP before the RT-Thread heap begins at __bss_end. */
    .stack (NOLOAD) :
    {
        . = ALIGN(8);
        _sstack = .;
        . = . + _system_stack_size;
        . = ALIGN(8);
        _estack = .;
        PROVIDE(_sp = _estack);
    } > AXISRAM

    /* Select the CPU-only pool before the generic .bss.* rule below.
     * TLSF initializes this memory itself; it is not a DMA buffer. */
    .lvgl_heap (NOLOAD) :
    {
        . = ALIGN(8);
        KEEP(*(.bss.lvgl_heap))
        . = ALIGN(8);
    } > DTCMRAM

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        _sbss = .;
        __bss_start = .;
        __bss_start__ = .;
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
        __bss_end = .;
        __bss_end__ = .;
    } > AXISRAM

    .enet_dma (NOLOAD) :
    {
        . = ALIGN(32);
        KEEP(*(.enet_dma))
        . = ALIGN(32);
    } > SRAM1

    PROVIDE(end = __bss_end);
    PROVIDE(_end = __bss_end);

    .itcmram :
    {
        . = ALIGN(4);
        _sitcmram = .;
        *(.itcmram)
        *(.itcmram*)
        . = ALIGN(4);
        _eitcmram = .;
    } > ITCMRAM AT> CNVM
    _siitcmram = LOADADDR(.itcmram);

    .dtcmram :
    {
        . = ALIGN(4);
        _sdtcmram = .;
        *(.dtcmram)
        *(.dtcmram*)
        . = ALIGN(4);
        _edtcmram = .;
    } > DTCMRAM AT> CNVM
    _sidtcmram = LOADADDR(.dtcmram);

    /* Stabs debugging sections. */
    .stab          0 : { *(.stab) }
    .stabstr       0 : { *(.stabstr) }
    .stab.excl     0 : { *(.stab.excl) }
    .stab.exclstr  0 : { *(.stab.exclstr) }
    .stab.index    0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment) }

    /* DWARF debugging sections. */
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames 0 : { *(.debug_varnames) }
}

ASSERT(SIZEOF(.vectors) > 0, "missing interrupt vector table")
ASSERT(ADDR(.vectors) == ORIGIN(CNVM), "vector table must start at CNVM base")
ASSERT(SIZEOF(.reset) > 0, "missing Reset_Handler")
ASSERT(SIZEOF(.enet_dma) <= LENGTH(SRAM1), "ENET DMA data exceeds SRAM1")
ASSERT(SIZEOF(.lvgl_heap) + SIZEOF(.dtcmram) <= LENGTH(DTCMRAM), "LVGL pool exceeds DTCM")

/* input sections */
GROUP(libgcc.a libc.a libm.a libnosys.a)
