    .globl __vdso_text_start
    .section .data.vdso.text
__vdso_text_start:
    .incbin "../usr/build/librtos_vdso.so"