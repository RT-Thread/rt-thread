/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtconfig.h>

#define FDT_STRINGIFY_(value) #value
#define FDT_STRINGIFY(value)  FDT_STRINGIFY_(value)

#ifdef RT_BUILTIN_FDT_PATH
__asm(
    ".section .rodata.dtb, \"a\", %progbits\n"
    ".balign 8\n"
    ".global rt_hw_builtin_fdt\n"
    ".type rt_hw_builtin_fdt, %object\n"
    "rt_hw_builtin_fdt:\n"
    ".incbin " FDT_STRINGIFY(RT_BUILTIN_FDT_PATH) "\n"
                                                  ".size rt_hw_builtin_fdt, . - rt_hw_builtin_fdt\n");
#endif
