/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2022-08-24     GuEe-GUI       first version
 */

#include <rtconfig.h>

    .data

    .align 8
    .globl rt_hw_builtin_fdt
rt_hw_builtin_fdt:
#ifdef RT_BUILTIN_FDT_PATH
    .incbin RT_BUILTIN_FDT_PATH
#endif
