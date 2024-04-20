OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)

SECTIONS
{
    . = SIZEOF_HEADERS;

    .hash       : { *(.hash) }          :text
    .dynsym     : { *(.dynsym) }
    .dynstr     : { *(.dynstr) }

    .dynamic    : { *(.dynamic) }       :text   :dynamic

    .rodata     : { *(.rodata*) }       :text

    .text       : { *(.text*) }         :text

    /DISCARD/   : {
        *(.data .data.* .sdata*)
        *(.bss .sbss .dynbss .dynsbss)
    }
}

PHDRS
{
    text        PT_LOAD     FLAGS(5) FILEHDR PHDRS;
    dynamic     PT_DYNAMIC  FLAGS(4);
}

VERSION
{
    LINUX_2.6.39 {
    global:
        __kernel_clock_gettime;
    local: *;
    };
}
