/*
 * S100 MCU1 linker script for RT-Thread on Cortex-R52.
 *
 * This keeps the current MCU1 memory layout from the FreeRTOS image and
 * adds the symbols/sections RT-Thread's Cortex-R52 GCC port expects.
 */

OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(EL2_core_exceptions_table)

STACK_SIZE     = DEFINED(__stack_size__)     ? __stack_size__     : 0x0000C000;
STACK_SIZE_EXC = DEFINED(__stack_size_exc__) ? __stack_size_exc__ : 0x0000C000;

MEMORY
{
    FLASH_STARTUP      (rx)  : ORIGIN = 0x0CAB0000, LENGTH = 4K
    FLASH              (rwx) : ORIGIN = 0x0CAB1000, LENGTH = 2154K
    RTOS_HEAP          (rw)  : ORIGIN = 0x0CCCB000, LENGTH = 512K
    CAN_Reserved       (rw)  : ORIGIN = 0x0CD4B000, LENGTH = 64K
    LOG_SHARE_Reserved (rw)  : ORIGIN = 0x0CD5B000, LENGTH = 8K
    SCMI_IPC_Reserved  (rw)  : ORIGIN = 0x0CD5D000, LENGTH = 12K
    ATCM_Reserved      (rwx) : ORIGIN = 0x0A000000, LENGTH = 64K
}

SECTIONS
{
    .startup :
    {
        . = ALIGN(32);
        __startup_start = .;
        KEEP(*(.EL2_core_exceptions_table))

        . = ALIGN(32);
        KEEP(*(.EL1_core_exceptions_table))

        . = ALIGN(32);
        KEEP(*(.EL2_Reset_Handler))

        . = ALIGN(4);
        KEEP(*(.text.entrypoint))
        KEEP(*(.vectors))

        . = ALIGN(32);
        __startup_end = .;
    } > FLASH_STARTUP

    .text :
    {
        PROVIDE(__text_start = .);
        *(.text)                        /* remaining code */
        *(.text.*)                      /* remaining code */
        *(.glue_7)
        *(.glue_7t)

        /* section information for utest */
        . = ALIGN(8);
        PROVIDE(__rt_utest_tc_tab_start = .);
        KEEP(*(UtestTcTab))
        PROVIDE(__rt_utest_tc_tab_end = .);

        /* section information for finsh shell */
        . = ALIGN(8);
        PROVIDE(__fsymtab_start = .);
        KEEP(*(FSymTab))
        PROVIDE(__fsymtab_end = .);
        . = ALIGN(8);
        PROVIDE(__vsymtab_start = .);
        KEEP(*(VSymTab))
        PROVIDE(__vsymtab_end = .);
        . = ALIGN(8);

        /* section information for modules */
        . = ALIGN(8);
        PROVIDE(__rtmsymtab_start = .);
        KEEP(*(RTMSymTab))
        PROVIDE(__rtmsymtab_end = .);

        /* section information for initialization */
        . = ALIGN(8);
        PROVIDE(__rt_init_start = .);
        KEEP(*(SORT(.rti_fn*)))
        PROVIDE(__rt_init_end = .);

        /* section information for usb usbh_class_info */
        . = ALIGN(4);
        __usbh_class_info_start__ = .;
        KEEP(*(.usbh_class_info))
        . = ALIGN(4);
        __usbh_class_info_end__ = .;

        PROVIDE(__text_end = .);
    } > FLASH

    .resource_table :
    {
        . = ALIGN(8);
        __resource_table_start = .;
        KEEP(*(.resource_table))
        KEEP(*(.resource_table.*))
        . = ALIGN(8);
        __resource_table_end = .;
    } > FLASH

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    .ARM.exidx   :
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > FLASH

    .const :
    {
        . = ALIGN(32);
        *(.const)
        *(.rodata .rodata.*)
    } > FLASH

    .data :
    {
        . = ALIGN(64);
        __image_rw_start__ = .;
        __data_start__ = .;      /* Create a global symbol at data start. */
        *(.data .data.*)         /* .data sections */
        . = ALIGN(64);
        __data_end__ = .;        /* Define a global symbol at data end. */
    } > FLASH

    .bss (NOLOAD):
    {
        /*
         * We need some free space to page or cpu stack, move .bss.noclean.*
         * to optimize size.
         */
        . = ALIGN(16);
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
    } > FLASH

    .stack (NOLOAD) :
    {
        . = ALIGN(64);
        __STACK_START = .;
        __StackLimit = .;
        __stack_start__ = .;
        . += STACK_SIZE;
        __stack_end__ = .;
        __StackTop = .;
    } > FLASH

    .stack_exc (NOLOAD) :
    {
        . = ALIGN(64);
        __StackLimit_exc = .;
        __stack_start_exc__ = .;
        . += STACK_SIZE_EXC;
        __stack_end_exc__ = .;
        __StackTop_exc = .;
        . = ALIGN(64);
        __image_rw_end__ = .;
    } > FLASH

    _end = .;
    /*-------- LABELS USED IN CODE -------------------------------*/
    SRAM_START_ADDR         = ORIGIN(FLASH_STARTUP);
    FLASH_STARTUP_LEN       = LENGTH(FLASH_STARTUP);
    FLASH_SEC_ADDR          = ORIGIN(FLASH);
    MCU_LOG_START_ADDR      = ORIGIN(LOG_SHARE_Reserved);
    MCU_LOG_SIZE            = LENGTH(LOG_SHARE_Reserved);
    __SCMI_IPC_START_ADDR   = ORIGIN(SCMI_IPC_Reserved);
    __SCMI_IPC_SIZE         = LENGTH(SCMI_IPC_Reserved);
    NON_SECURE_START_ADDR   = ORIGIN(LOG_SHARE_Reserved);
    CAN_START_ADDR          = ORIGIN(CAN_Reserved);
    ATCM_START_ADDR         = ORIGIN(ATCM_Reserved);
    ATCM_SIZE               = LENGTH(ATCM_Reserved);
    OS_HEAP_START_ADDR      = ORIGIN(RTOS_HEAP);
    OS_HEAP_END_ADDR        = ORIGIN(RTOS_HEAP) + LENGTH(RTOS_HEAP);
    OS_HEAP_SIZE            = LENGTH(RTOS_HEAP);
    
    /* Keep __image_rw_end__ ~ OS_HEAP_START_ADDR unmapped as a guard gap. */

    PROVIDE(SRAM_SIZE = 0x34FFFF);
    PROVIDE(MCU0_LOG_START_ADDR = 0x0CAAB000); /* Base addr from MCU0 link region "LOG_SHARE_Reserved" */
    PROVIDE(MCU_STATE_START_ADDR = 0x0C800800);/* Base addr from MCU0 link region "MCU_STATE_Reserved" */

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
