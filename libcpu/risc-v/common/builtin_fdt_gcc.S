/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-20     GuEe-GUI     The first version
 */

#include <asm-generic.h>

    .section ".data"

    .align RISCV_SZPTR
    .globl rt_hw_builtin_fdt
rt_hw_builtin_fdt:
#ifdef RT_BUILTIN_FDT_PATH
    .incbin RT_BUILTIN_FDT_PATH
#endif
