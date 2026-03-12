/*
 * Copyright 2021-2025 HPMicro
 * SPDX-License-Identifier: BSD-3-Clause
 */

ENTRY(_start)

STACK_SIZE = DEFINED(_stack_size) ? _stack_size : 0x4000;
HEAP_SIZE = DEFINED(_heap_size) ? _heap_size : 256K;
SDRAM_SIZE = DEFINED(_sdram_size) ? _sdram_size : 32M;
NONCACHEABLE_SIZE = DEFINED(_noncacheable_size) ? _noncacheable_size : 256K;

MEMORY
{
    ILM (wx) : ORIGIN = 0x00000000, LENGTH = 256K
    DLM (w) : ORIGIN = 0x00080000, LENGTH = 256K
    AXI_SRAM (wx) : ORIGIN = 0x01080000, LENGTH = 512K
    AXI_SRAM1 (w) : ORIGIN = 0x01100000, LENGTH = 768K
    NONCACHEABLE_RAM (wx) : ORIGIN = 0x11C0000, LENGTH = NONCACHEABLE_SIZE
    SDRAM (wx) : ORIGIN = 0x40000000, LENGTH = SDRAM_SIZE
    AHB_SRAM (w) : ORIGIN = 0xF0300000, LENGTH = 32k
    APB_SRAM (w): ORIGIN = 0xF40F0000, LENGTH = 8k
}

SECTIONS
{
    .start : {
        . = ALIGN(8);
        KEEP(*(.start))
    } > AXI_SRAM

    .vectors : {
        . = ALIGN(8);
        KEEP(*(.isr_vector))
        KEEP(*(.vector_table))
        . = ALIGN(8);
    } > AXI_SRAM

    .text : {
        . = ALIGN(8);
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        *(.srodata)
        *(.srodata*)

        *(.hash)
        *(.dyn*)
        *(.gnu*)
        *(.pl*)
        *(FalPartTable)

        KEEP(*(.eh_frame))
        *(.eh_frame*)

        KEEP (*(.init))
        KEEP (*(.fini))
        . = ALIGN(8);

        /*********************************************
         *
         *      RT-Thread related sections - Start
         *
        *********************************************/
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

        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;
        . = ALIGN(4);

        /* section information for modules */
        . = ALIGN(4);
        __rtmsymtab_start = .;
        KEEP(*(RTMSymTab))
        __rtmsymtab_end = .;

        /* RT-Thread related sections - end */


        /* section information for usbh class */
        . = ALIGN(8);
        __usbh_class_info_start__ = .;
        KEEP(*(.usbh_class_info))
        __usbh_class_info_end__ = .;
		. = ALIGN(8);
    } > AXI_SRAM

    .eh_frame :
    {
        __eh_frame_start = .;
        KEEP(*(.eh_frame))
        __eh_frame_end = .;
    }  > AXI_SRAM

    .eh_frame_hdr :
    {
        KEEP(*(.eh_frame_hdr))
    }  > AXI_SRAM
    __eh_frame_hdr_start = SIZEOF(.eh_frame_hdr) > 0 ? ADDR(.eh_frame_hdr) : 0;
    __eh_frame_hdr_end = SIZEOF(.eh_frame_hdr) > 0 ? . : 0;

    .rel : {
        KEEP(*(.rel*))
    } > AXI_SRAM

     PROVIDE (__etext = .);
     PROVIDE (_etext = .);
     PROVIDE (etext = .);

    .fast_ram (NOLOAD) : {
        KEEP(*(.fast_ram))
    } > DLM

    /* NOTE:
       Please keep in mind that the load section for rw data is after .text section
       Here end user should avoid place any NOLOAD sections (such as .bss) in the space between .text section
       and data load section if all sections are placed into the same adjacent space. Otherwise, the following conditions must be taken into account:
         1. The size for all NOLOAD sections smust be added during computing __data_load_addr__
         2. the generated binary file will be larger because the space occupied by
             NOLOAD sections will be filled
     */
    __data_load_addr__ = __etext;
    .data : AT(__data_load_addr__) {
        __data_start__ = .;
        . = ALIGN(8);
        __global_pointer$ = . + 0x800;
        *(.data)
        *(.data*)
        *(.sdata)
        *(.sdata*)

        KEEP(*(.jcr))
        KEEP(*(.dynamic))
        KEEP(*(.got*))
        KEEP(*(.got))
        KEEP(*(.gcc_except_table))
        KEEP(*(.gcc_except_table.*))

        . = ALIGN(8);
        PROVIDE(__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE(__preinit_array_end = .);

        . = ALIGN(8);
        PROVIDE(__init_array_start = .);
        KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE(__init_array_end = .);

        . = ALIGN(8);
        PROVIDE(__fini_array_start = .);
        KEEP(*(SORT_BY_INIT_PRIORITY(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE(__fini_array_end = .);

        . = ALIGN(8);
        PROVIDE(__ctors_start__ = .);
        KEEP(*crtbegin*.o(.ctors))
        KEEP(*(EXCLUDE_FILE (*crtend*.o) .ctors))
        KEEP(*(SORT(.ctors.*)))
        KEEP(*(.ctors))
        PROVIDE(__ctors_end__ = .);

        . = ALIGN(8);
        KEEP(*crtbegin*.o(.dtors))
        KEEP(*(EXCLUDE_FILE (*crtend*.o) .dtors))
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))

        . = ALIGN(8);
        __data_end__ = .;
        PROVIDE (__edata = .);
        PROVIDE (_edata = .);
        PROVIDE (edata = .);
    } > AXI_SRAM

    __fast_load_addr__ = __data_load_addr__ + SIZEOF(.data);
    .fast : AT(__fast_load_addr__) {
        PROVIDE(__ramfunc_start__ = .);
        . = ALIGN(8);
        *(.fast)
        . = ALIGN(8);
        PROVIDE(__ramfunc_end__ = .);
    } > AXI_SRAM

    __noncacheable_init_load_addr__ = __fast_load_addr__ + SIZEOF(.fast);
    .noncacheable.init : AT(__noncacheable_init_load_addr__) {
        . = ALIGN(8);
        __noncacheable_init_start__ = .;
        KEEP(*(.noncacheable.init))
        __noncacheable_init_end__ = .;
        . = ALIGN(8);
    } > NONCACHEABLE_RAM

     __fast_ram_init_load_addr__ = __noncacheable_init_load_addr__ + SIZEOF(.noncacheable.init);
    .fast_ram.init : AT(__fast_ram_init_load_addr__) {
        . = ALIGN(8);
        __fast_ram_init_start__ = .;
        KEEP(*(.fast_ram.init))
        KEEP(*(.fast_ram.init.*))
        __fast_ram_init_end__ = .;
        . = ALIGN(8);
    } > DLM

    /* Note: .tbss and .tdata should be adjacent */
    __tdata_load_addr__ = __fast_ram_init_load_addr__ + SIZEOF(.fast_ram.init);
    .tdata : AT(__tdata_load_addr__) {
        . = ALIGN(8);
        __tdata_start__ = .;
        __thread_pointer = .;
        *(.tdata)
        *(.tdata*)
        *(.gnu.linkonce.td.*)
        . = ALIGN(8);
        __tdata_end__ = .;
    } > AXI_SRAM

    /* Note: Place all NOLOAD sections together */
    .tbss(NOLOAD) : {
        . += SIZEOF(.noncacheable.init);
        . = ALIGN(8);
        __tbss_start__ = .;
        *(.tbss*)
        *(.gnu.linkonce.tb.*)
        *(.tcommon*)
        _end = .;
        __tbss_end__ = .;
    } > AXI_SRAM1

    .bss(NOLOAD) : {
        . = ALIGN(8);
        __bss_start__ = .;
        *(.bss)
        *(.bss*)
        *(.sbss*)
        *(.scommon)
        *(.scommon*)
        *(.dynsbss*)
        *(COMMON)
        . = ALIGN(8);
        _end = .;
        __bss_end__ = .;
    } > AXI_SRAM1

    .noncacheable.bss (NOLOAD) : {
        . = ALIGN(8);
        KEEP(*(.noncacheable))
        KEEP(*(.noncacheable.non_init))
        KEEP(*(.noncacheable.non_init.*))
        __noncacheable_bss_start__ = .;
        KEEP(*(.noncacheable.bss))
        KEEP(*(.noncacheable.bss.*))
        __noncacheable_bss_end__ = .;
        . = ALIGN(8);
    } > NONCACHEABLE_RAM

    __noncacheable_start__ = ORIGIN(NONCACHEABLE_RAM);
    __noncacheable_end__ = ORIGIN(NONCACHEABLE_RAM) + LENGTH(NONCACHEABLE_RAM);

     .ahb_sram (NOLOAD) : {
        KEEP(*(.ahb_sram))
    } > AHB_SRAM

    .apb_sram (NOLOAD) : {
        KEEP(*(.backup_sram))
    } > APB_SRAM

    .stack(NOLOAD) : {
        . = ALIGN(8);
        __stack_base__ = .;
        . += STACK_SIZE;
        PROVIDE (_stack = .);
        PROVIDE (_stack_in_dlm = .);
        PROVIDE (__rt_rvstack = .);
    } > AXI_SRAM1

    .framebuffer (NOLOAD) : {
        KEEP(*(.framebuffer))
    } > AXI_SRAM1

    .heap (NOLOAD) : {
        . = ALIGN(8);
        __heap_start__ = .;
        . += HEAP_SIZE;
        __heap_end__ = .;

    } > AXI_SRAM1

    .sdram (NOLOAD) : {
        . = ALIGN(8);
        __sdram_start__ = .;
        __sdram_end__ = .;
    } > SDRAM
}
