/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-24     GuEe-GUI     first version
 */

#include <hypercall.h>

rt_err_t rt_hv_stage2_map(unsigned long paddr, unsigned long size)
{
    return rt_hw_hypercall(120, paddr & (~4095), (paddr & (~4095)) + size, (1 << 0) | (1 << 1) | (1 << 4), 0, 0, 0, 0);
}
