/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtconfig.h>

    .section .rodata.dtb, "a", %progbits
    .balign 8
    .global rt_hw_builtin_fdt
    .type rt_hw_builtin_fdt, %object
rt_hw_builtin_fdt:
#ifdef RT_BUILTIN_FDT_PATH
    .incbin RT_BUILTIN_FDT_PATH
#endif
    .size rt_hw_builtin_fdt, . - rt_hw_builtin_fdt
