/*
 * linker script for N32H76x with GNU ld
 * SummerGift 2026.1.24
 */

/* Program Entry, set to mark it as "used" and avoid gc */
MEMORY
{
    FLASH     (rx)  : ORIGIN = 0x15000000, LENGTH = 1920k   /* 1920 KB NOR-Flash (XIP) */
    ITCM      (xrw) : ORIGIN = 0x00000000, LENGTH =  768k   /* 768K ITCM               */
    DTCM      (xrw) : ORIGIN = 0x20000000, LENGTH =  256k   /* 256K DTCM               */
    AXI_SRAM  (xrw) : ORIGIN = 0x24000000, LENGTH =  128k   /* 128K AXI-SRAM           */
    AHB_SRAM  (xrw) : ORIGIN = 0x30000000, LENGTH =  320k   /* 320K AHB-SRAM           */
    AHB_SRAM5 (xrw) : ORIGIN = 0x30050000, LENGTH =   32k   /* 32K AHB-SRAM5 FDCAN1-8  */
}

/* Entry Point */
ENTRY(Reset_Handler)

_estack = ORIGIN(AHB_SRAM) + LENGTH(AHB_SRAM);   /* boot-time stack (AHB_SRAM top) */

_system_stack_size = 0x2000;

SECTIONS
{
    /* ===== Stage 1: Boot code in NOR-Flash (XIP) ===== */

    /* Boot vector table: SP + Reset_Handler, placed at FLASH base */
    .isr_vector_boot :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector_boot))
        . = ALIGN(4);
    } > FLASH

    /* Boot text: reset handler, lowlevel_init, _main, copy routines, Default_Handler
     *
     * SDK object files that are called during boot (before TCM copy) must also
     * be placed here.  
     *
     * We use a wildcard object-file pattern to match regardless of
     * build-dir prefix, for example ".../system_n32h7xx.o".
     */
    .text.boot :
    {
        . = ALIGN(4);
        KEEP(*(.text.reset))
        KEEP(*(.text.Default_Handler))
        *(.boot_text)
        *(.boot_text*)
        *(.rodata.boot)
        *(.rodata.boot*)

        /* SDK: system init -- called from lowlevel_init via SystemInit() */
        */system_n32h7xx.o(.text*)
        */system_n32h7xx.o(.rodata*)

        . = ALIGN(4);
    } > FLASH

    /* ===== Stage 2: Runtime image copied into ITCM as one block ===== */

    .runtime_image :
    {
        . = ALIGN(4);
        __image_copy_start__ = .;

        /* Runtime vector table sits at the start of the relocated image. */
        __tcm_vector_start__ = .;
        KEEP(*(.tcm_vector))
        __tcm_vector_end__ = .;

        . = ALIGN(4);
        /* Application code follows contiguously so _main() can copy one image. */
        __itcm_text_start__ = .;

        . = ALIGN(4);
        *(.text)                        /* remaining code */
        *(.text.*)                      /* remaining code */
        *(.rodata)                      /* read-only data (constants) */
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)
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

        /* section information for initial. */
        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;

        . = ALIGN(4);

        PROVIDE(__ctors_start__ = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        PROVIDE(__ctors_end__ = .);

        . = ALIGN(4);

        _etext = .;

        . = ALIGN(4);
        __itcm_text_end__ = .;

        __image_copy_end__ = .;
    } > ITCM AT > FLASH

    __image_copy_load_start__ = LOADADDR(.runtime_image);
    __tcm_vector_load_start__ = __image_copy_load_start__;
    __itcm_text_load_start__ = __image_copy_load_start__ + (__itcm_text_start__ - __image_copy_start__);


    /* .ARM.exidx is sorted, so has to go in its own output section.  */
    .ARM.exidx :
    {
        . = ALIGN(4);
        __exidx_start = .;

        *(.ARM.exidx* .gnu.linkonce.armexidx.*)

        . = ALIGN(4);
        __exidx_end = .;
    } > FLASH

    /* .data section which is used for initialized data */

    .data :
    {
        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .data secion */
        _sdata = . ;

        *(.data)
        *(.data.*)
        *(.gnu.linkonce.d*)

        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))
        PROVIDE(__dtors_end__ = .);

        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .data secion */
        _edata = . ;
    } > AHB_SRAM AT > FLASH
    _sidata = LOADADDR(.data);

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .bss secion */
        _sbss = .;
        __bss_start = _sbss;

        *(.bss)
        *(.bss*)
        *(COMMON)

        *(.bss.init)

        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .bss secion */
        _ebss = .;
        __bss_end = _ebss;
    } > AHB_SRAM

    _end = .;

    .stack :
    {
        . = ALIGN(4);
        _app_sstack = .;

        . = . + _system_stack_size;

        . = ALIGN(4);
        _app_estack = .;
    } > AXI_SRAM

    /* Stabs debugging sections.  */
    .stab          0 : { *(.stab) }
    .stabstr       0 : { *(.stabstr) }
    .stab.excl     0 : { *(.stab.excl) }
    .stab.exclstr  0 : { *(.stab.exclstr) }
    .stab.index    0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment) }
    /* DWARF debug sections.
     * Symbols in the DWARF debugging sections are relative to the beginning
     * of the section so we begin them at 0.  */
    /* DWARF 1 */
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }
    /* GNU DWARF 1 extensions */
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }
    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    /* DWARF 2 */
    .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }
    /* SGI/MIPS DWARF 2 extensions */
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }
}
