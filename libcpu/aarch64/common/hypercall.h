/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-24     GuEe-GUI     first version
 */

#ifndef __HYPERCALL_H__
#define __HYPERCALL_H__

#include <rtdef.h>

rt_inline rt_uint32_t rt_hw_hypercall(rt_uint32_t w0, rt_uint64_t x1, rt_uint64_t x2,
        rt_uint64_t x3, rt_uint64_t x4, rt_uint64_t x5, rt_uint64_t x6, rt_uint32_t w7)
{
    register rt_uint64_t ret __asm__ ("x0");
    __asm__ volatile ("hvc #0");

    return (rt_uint32_t)ret;
}

rt_err_t rt_hv_stage2_map(unsigned long paddr, unsigned long size);

#endif
