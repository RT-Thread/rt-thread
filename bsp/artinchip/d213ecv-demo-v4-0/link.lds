/* D213ECV-DEMO-V4-0: 128 MiB DDR, loader-owned upper 8 MiB.
 * SPDX-License-Identifier: Apache-2.0
 */
OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
    DRAM (rwx) : ORIGIN = 0x40000000, LENGTH = 0x07800000 /* top 8 MiB reserved for the loader */
}

SECTIONS
{
    . = ORIGIN(DRAM);

    .text : {
        PROVIDE(__text_start = .);
        KEEP(*(.start))
        KEEP(*(.text.start))
        KEEP(*(.text.entry))
        *(.text)
        *(.text.*)
        *(.gnu.linkonce.t*)
        . = ALIGN(8);

        . = ALIGN(8);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;
        . = ALIGN(8);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;
        . = ALIGN(8);
        __rtmsymtab_start = .;
        KEEP(*(RTMSymTab))
        __rtmsymtab_end = .;
        . = ALIGN(8);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;
        . = ALIGN(8);

        . = ALIGN(8);

        . = ALIGN(8);
        __etext = .;
    } > DRAM

    .rodata : {
        . = ALIGN(8);
        __srodata = .;
        *(.rodata)
        *(.rodata.*)
        *(.srodata)
        *(.srodata.*)
        *(.rdata)
        *(.rdata.*)
        . = ALIGN(8);
        __ctors_start__ = .;
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        __ctors_end__ = .;
        __dtors_start__ = .;
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        __dtors_end__ = .;
        . = ALIGN(8);
        __rodata_end__ = .;
    } > DRAM

    .data : {
        . = ALIGN(8);
        __data_start__ = .;
        __global_pointer$ = . + 0x800;
        *(.data)
        *(.data.*)
        *(.sdata)
        *(.sdata.*)
        *(.gnu.linkonce.d*)
        . = ALIGN(8);
        __data_end__ = .;
    } > DRAM

    .bss (NOLOAD) : {
        . = ALIGN(8);
        __bss_noclean_start = .;
        *(.bss.noclean.*)
        __bss_noclean_end = .;
        . = ALIGN(8);
        __bss_start = .;
        *(.bss)
        *(.bss.*)
        *(.sbss)
        *(.sbss.*)
        *(COMMON)
        . = ALIGN(8);
        __bss_end = .;
    } > DRAM

    .percpu (NOLOAD) : {
        . = ALIGN(16);
        __percpu_start = .;
        *(.percpu)
        __percpu_end = .;
        __percpu_real_end = .;
    } > DRAM

    _end = .;
    __bss_start__ = __bss_start;
    __bss_end__ = __bss_end;

    . = ALIGN(16);
    __heap_start = .;

    __heap_end = ORIGIN(DRAM) + LENGTH(DRAM);

    /DISCARD/ : {
        *(.eh_frame)
        *(.eh_frame_hdr)
        *(.comment)
    }
}

ASSERT(__data_end__ <= __bss_start__, "data overlaps bss")
ASSERT(__bss_end__ <= __heap_start, "bss overlaps heap")
ASSERT(__percpu_start <= __percpu_end, "percpu section is invalid")
ASSERT(__heap_start < __heap_end, "heap is empty")
ASSERT((__percpu_end & 15) == 0, "early stack is not ABI aligned")
