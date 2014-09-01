#include <rtt_api.h>

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

SECTIONS
{
    . = VMM_BEGIN;

    __text_start = .;
    .text.share :
    {
        KEEP(*(.vectors))
        *(.text.isr)
        *(.vmm_glue)
    }
    ASSERT(SIZEOF(.text.share) <= VMM_SHARE_TEXT_PGSZ, ".text.share too big")

    . = VMM_BEGIN + VMM_SHARE_TEXT_PGSZ;
    /* the vectore page is saved here
     * {
     * }
     */

    . = VMM_SHARE_DATA_POS;
    .data.share :
    {
        __data_share_start = .;
        *(.data.share*)
        __data_share_end = .;
    }
    ASSERT(SIZEOF(.data.share) <= (VMM_SHARE_DATA_PGSZ), ".data.share is too big")

    . = VMM_SHARE_BSS_POS;
    .bss.share :
    {
        __bss_share_start = .;
        *(.bss.share*)
        __bss_share_end = .;
    }
    ASSERT(SIZEOF(.bss.share) <= (VMM_SHARE_BSS_PGSZ), ".bss.share is too big")

    . = VMM_SHARE_CTX_POS;
    .vmm.share :
    {
        /* the vmm context goes here */
        __vmm_share_start = .;
        *(.vmm.share*)
        __vmm_share_end = .;
    }
    ASSERT(SIZEOF(.vmm.share) <= (VMM_SHARE_CTX_PGSZ), "vmm share context is too big")

    . = VMM_BEGIN + VMM_SHARE_PGSZ;
    .text :
    {
        *(.vmm_init)
        *(.text)
        *(.text.*)

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
    }
    __text_end = .;

    __rodata_start = .;
    .rodata   : { *(.rodata) *(.rodata.*) }
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

    __data_start = .;
    . = ALIGN(8);
    .data :
    {
        *(.data)
        *(.data.*)
    }
    __data_end = .;

    . = ALIGN(8);
    __bss_start = __data_end;
    .bss       :
    {
    vmm_stack_start = .;
    . = vmm_stack_start + RT_VMM_STACK_SIZE;
    vmm_stack_end = .;
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
