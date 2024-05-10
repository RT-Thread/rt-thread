#include <vdso_config.h>    

    .globl __vdso_text_start, __vdso_text_end
    .section .rodata
	.balign PAGE_SIZE
__vdso_text_start:
    .incbin VDSO_PATH
    .balign PAGE_SIZE
__vdso_text_end:

    .previous