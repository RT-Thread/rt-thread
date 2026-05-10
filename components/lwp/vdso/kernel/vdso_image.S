/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
 */
 
#include <vdso_constants.h>

    .globl __rt_vdso_image_start, __rt_vdso_image_end
    .section .rodata
    .balign RT_VDSO_PAGE_SIZE
__rt_vdso_image_start:
    .incbin RT_VDSO_IMAGE_PATH
    .balign RT_VDSO_PAGE_SIZE
__rt_vdso_image_end:

    .previous
