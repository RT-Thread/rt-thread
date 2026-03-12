/*
 * Copyright 2021-2025 HPMicro
 * SPDX-License-Identifier: BSD-3-Clause
 */

ENTRY(_start)

STACK_SIZE = DEFINED(_stack_size) ? _stack_size : 0x4000;
HEAP_SIZE = DEFINED(_heap_size) ? _heap_size : 128K;
FLASH_SIZE = DEFINED(_flash_size) ? _flash_size : 16M;
NONCACHEABLE_SIZE = DEFINED(_noncacheable_size) ? _noncacheable_size : 128K;
SDRAM_SIZE = DEFINED(_sdram_size) ? _sdram_size : 256M;

MEMORY
{
    XPI0 (rx) : ORIGIN = 0x80000000, LENGTH = FLASH_SIZE
    ILM (wx) : ORIGIN = 0, LENGTH = 256K
    DLM (w) : ORIGIN = 0x80000, LENGTH = 256K
    AXI_SRAM (wx) : ORIGIN = 0x1200000, LENGTH = 384K
    NONCACHEABLE_RAM (wx) : ORIGIN = 0x01260000, LENGTH = NONCACHEABLE_SIZE
    SDRAM (wx) : ORIGIN = 0x40000000, LENGTH = SDRAM_SIZE
    AHB_SRAM (w) : ORIGIN = 0xF0400000, LENGTH = 32k
    APB_SRAM (w): ORIGIN = 0xF4130000, LENGTH = 16k
}

__nor_cfg_option_load_addr__ = ORIGIN(XPI0) + 0x400;
__boot_header_load_addr__ = ORIGIN(XPI0) + 0x1000;
__app_load_addr__ = ORIGIN(XPI0) + 0x3000;
__boot_header_length__ = __boot_header_end__ - __boot_header_start__;
__app_offset__ = __app_load_addr__ - __boot_header_load_addr__;

SECTIONS
{
    .nor_cfg_option __nor_cfg_option_load_addr__ : {
        KEEP(*(.nor_cfg_option))
    } > XPI0

    .boot_header __boot_header_load_addr__ : {
        __boot_header_start__ = .;
        KEEP(*(.boot_header))
        KEEP(*(.fw_info_table))
        KEEP(*(.dc_info))
        __boot_header_end__ = .;
    } > XPI0

    .start __app_load_addr__ : {
        . = ALIGN(8);
        KEEP(*(.start))
        . = ALIGN(16);
    } > XPI0

    __vector_load_addr__ = ADDR(.start) + SIZEOF(.start);
    .vectors : AT(__vector_load_addr__) {
        . = ALIGN(16);
        __vector_ram_start__ = .;
        KEEP(*(.vector_table))
        KEEP(*(.isr_vector))

        . = ALIGN(16);
        __vector_ram_end__ = .;
    } > ILM

    .fast : AT(__fast_load_addr__) {
        . = ALIGN(16);
        __ramfunc_start__ = .;
        *(.fast)
        *(.fast.*)
        . = ALIGN(16);

        /* RT-Thread Core Start */
        KEEP(*context_gcc.o(.text* .rodata*))
        KEEP(*port*.o (.text .text* .rodata .rodata*))
        KEEP(*interrupt_gcc.o (.text .text* .rodata .rodata*))
        KEEP(*trap_common.o (.text .text* .rodata .rodata*))
        KEEP(*irq.o (.text .text* .rodata .rodata*))
        KEEP(*clock.o (.text .text* .rodata .rodata*))
        KEEP(*kservice.o (.text .text* .rodata .rodata*))
        KEEP(*scheduler*.o (.text .text* .rodata .rodata*))
        KEEP(*trap*.o (.text .text* .rodata .rodata*))
        KEEP(*idle.o (.text .text* .rodata .rodata*))
        KEEP(*ipc.o (.text .text* .rodata .rodata*))
        KEEP(*slab.o (.text .text* .rodata .rodata*))
        KEEP(*thread.o (.text .text* .rodata .rodata*))
        KEEP(*object.o (.text .text* .rodata .rodata*))
        KEEP(*timer.o (.text .text* .rodata .rodata*))
        KEEP(*mem.o (.text .text* .rodata .rodata*))
        KEEP(*memheap.o (.text .text* .rodata .rodata*))
        KEEP(*mempool.o (.text .text* .rodata .rodata*))
        /* RT-Thread Core End */

        /* HPMicro Driver Wrapper */
        KEEP(*drv_*.o (.text .text* .rodata .rodata*))
        KEEP(*api_lib*.o (.text .text* .rodata .rodata*))
        KEEP(*api_msg*.o (.text .text* .rodata .rodata*))
        KEEP(*if_api*.o (.text .text* .rodata .rodata*))
        KEEP(*netbuf*.o (.text .text* .rodata .rodata*))
        KEEP(*netdb*.o (.text .text* .rodata .rodata*))
        KEEP(*netifapi*.o (.text .text* .rodata .rodata*))
        KEEP(*sockets*.o (.text .text* .rodata .rodata*))
        KEEP(*tcpip*.o (.text .text* .rodata .rodata*))
        KEEP(*inet_chksum*.o (.text .text* .rodata .rodata*))
        KEEP(*ip*.o (.text .text* .rodata .rodata*))
        KEEP(*memp*.o (.text .text* .rodata .rodata*))
        KEEP(*netif*.o (.text .text* .rodata .rodata*))
        KEEP(*pbuf*.o (.text .text* .rodata .rodata*))
        KEEP(*tcp_in*.o (.text .text* .rodata .rodata*))
        KEEP(*tcp_out*.o (.text .text* .rodata .rodata*))
        KEEP(*tcp*.o (.text .text* .rodata .rodata*))
        KEEP(*ethernet*.o (.text .text* .rodata .rodata*))
        KEEP(*ethernetif*.o (.text .text* .rodata .rodata*))

        . = ALIGN(16);
        __ramfunc_end__ = .;
    } > ILM

    .text (__vector_load_addr__ + SIZEOF(.vectors)) : {
        . = ALIGN(16);
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

    } > XPI0

    .eh_frame :
    {
        __eh_frame_start = .;
        KEEP(*(.eh_frame))
        __eh_frame_end = .;
    }  > XPI0

    .eh_frame_hdr :
    {
        KEEP(*(.eh_frame_hdr))
    }  > XPI0
    __eh_frame_hdr_start = SIZEOF(.eh_frame_hdr) > 0 ? ADDR(.eh_frame_hdr) : 0;
    __eh_frame_hdr_end = SIZEOF(.eh_frame_hdr) > 0 ? . : 0;

    .rel : {
        KEEP(*(.rel*))
    } > XPI0

    PROVIDE (__etext = .);
    PROVIDE (_etext = .);
    PROVIDE (etext = .);

    .fast_ram (NOLOAD) : {
        KEEP(*(.fast_ram))
    } > DLM

    __fast_ram_init_load_addr__ = etext + SIZEOF(.data) + SIZEOF(.fast) + SIZEOF(.tdata) + SIZEOF(.noncacheable.init);
        .fast_ram.init : AT(__fast_ram_init_load_addr__) {
        . = ALIGN(8);
        __fast_ram_init_start__ = .;
        KEEP(*(.fast_ram.init))
        KEEP(*(.fast_ram.init.*))
        __fast_ram_init_end__ = .;
        . = ALIGN(8);
    } > DLM

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
    } > DLM

    /* Note: the .tbss and .tdata section should be adjacent */
    .tbss(NOLOAD) : {
        . = ALIGN(8);
        __tbss_start__ = .;
        *(.tbss*)
        *(.gnu.linkonce.tb.*)
        *(.tcommon*)
        _end = .;
        __tbss_end__ = .;
    } > DLM

    __tdata_load_addr__ = etext;
    .tdata : AT(__tdata_load_addr__) {
        . = ALIGN(8);
        __tdata_start__ = .;
        __thread_pointer = .;
        *(.tdata)
        *(.tdata*)
        *(.gnu.linkonce.td.*)
        . = ALIGN(8);
        __tdata_end__ = .;
    } > DLM

    __data_load_addr__ = etext + SIZEOF(.tdata);
    .data : AT(__data_load_addr__) {
        . = ALIGN(8);
        __data_start__ = .;
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
    } > DLM
    __fast_load_addr__ = etext + SIZEOF(.data) + SIZEOF(.tdata);

    __fw_size__ = SIZEOF(.start) + SIZEOF(.vectors) + SIZEOF(.rel) + SIZEOF(.text) + SIZEOF(.data) + SIZEOF(.fast) + SIZEOF(.tdata) + SIZEOF(.noncacheable.init) + SIZEOF(.fast_ram.init) + SIZEOF(.eh_frame) + SIZEOF(.eh_frame_hdr);

    .heap(NOLOAD) : {
        . = ALIGN(8);
        __heap_start__ = .;
        . += HEAP_SIZE;
        __heap_end__ = .;
    } > AXI_SRAM

    .framebuffer (NOLOAD) : {
        . = ALIGN(8);
        KEEP(*(.framebuffer))
        . = ALIGN(8);
    } > AXI_SRAM

    .stack(NOLOAD) : {
        . = ALIGN(8);
        __stack_base__ = .;
        . += STACK_SIZE;
        . = ALIGN(8);
        PROVIDE (_stack = .);
        PROVIDE (_stack_in_dlm = .);
        PROVIDE( __rt_rvstack = . );
    } > DLM

    __noncacheable_init_load_addr__ = etext + SIZEOF(.data) + SIZEOF(.tdata) + SIZEOF(.fast);
    .noncacheable.init : AT(__noncacheable_init_load_addr__) {
        . = ALIGN(8);
        __noncacheable_init_start__ = .;
        KEEP(*(.noncacheable.init))
        __noncacheable_init_end__ = .;
        . = ALIGN(8);
    } > NONCACHEABLE_RAM

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

    .ahb_sram (NOLOAD) : {
        KEEP(*(.ahb_sram))
    } > AHB_SRAM

    .apb_sram (NOLOAD) : {
        KEEP(*(.backup_sram))
    } > APB_SRAM

    __noncacheable_start__ = ORIGIN(NONCACHEABLE_RAM);
    __noncacheable_end__ = ORIGIN(NONCACHEABLE_RAM) + LENGTH(NONCACHEABLE_RAM);

    .sdram (NOLOAD) : {
        . = ALIGN(8);
        __sdram_start__ = .;
        __sdram_end__ = .;
    } > SDRAM
}
