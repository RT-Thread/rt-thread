/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
 */
 
#include <vdso_config.h>    

    .globl __vdso_text_start, __vdso_text_end
    .section .rodata
    .balign VDSO_PAGE_SIZE
__vdso_text_start:
    .incbin VDSO_PATH
    .balign VDSO_PAGE_SIZE
__vdso_text_end:

    .previous
