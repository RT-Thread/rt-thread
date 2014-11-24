/******************************************************************************
 *
 * CME_M7.ld - Linker configuration file for project.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-11-02     aozima       first implementation
 *
 *****************************************************************************/

/* Program Entry, set to mark it as "used" and avoid gc */
MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K /* !!! real 128K, up to 256K for linker. */
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS
{
    .text :
    {
        _text = .;
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)

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

        /* section information for components init. */
        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;
        . = ALIGN(4);

    } > FLASH

    /* .ARM.exidx is sorted, so has to go in its own output section.  */
    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)

        /* This is used by the startup in order to initialize the .data secion */
        _sidata = .;
    } > FLASH
    __exidx_end = .;

	/* end of all text. */
    _etext = .;
	
    .data : AT(_etext)
    {
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > SRAM

    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM
    __bss_end = .;

}
