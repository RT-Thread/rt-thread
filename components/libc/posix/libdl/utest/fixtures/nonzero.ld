SECTIONS
{
    .text 0x1000 : { *(.text*) }
    .rodata 0x1800 : { *(.rodata*) }
    .data 0x2000 : { *(.data*) }
    .bss 0x3000 : { *(.bss*) }
}
