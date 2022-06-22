/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include <mips.h>

    .section ".text", "ax"
    .set noreorder

    .globl  rt_cpu_early_init
rt_cpu_early_init:
     mfc0	t0, CP0_CONFIG
     ori	t0, 3
     mtc0	t0, CP0_CONFIG
     ehb
     jr	ra