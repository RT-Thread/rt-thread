SECTIONS
{
    .text 0 : { *(.text*) }
    .data 0 : { *(.data*) }
    .bss 0 : { *(.bss*) }
    .common 0 : { *(COMMON) }
}
