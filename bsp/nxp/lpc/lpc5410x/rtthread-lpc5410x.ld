/*
 *  - Up to 512 kB on-chip flash memory
 *  - Up to 96 kB main SRAM.
 *  - An additional 8 kB SRAM. with GNU ld
 *    Date           Author       Notes
 *    2014-11-02     aozima       first implementation
 *    2014-12-16     RT_learning  change little for support LPC5410x
 */

/* Program Entry, set to mark it as "used" and avoid gc */
MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 512K /* */
    SRAM (rwx) : ORIGIN = 0x02000000, LENGTH = 96K
}

_system_stack_size = 0x200;

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
