/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-22     quanzhao     first version
 */

#ifndef __VEXPRESS_A9_H__
#define __VEXPRESS_A9_H__

/* for 'rt_inline' */
#include <rtdef.h>
/* SOC-relative definitions */
#include "realview.h"

/* the maximum entries of the exception table */
#define MAX_HANDLERS    NR_IRQS_PBA8

/* the basic constants and interfaces needed by gic */
rt_inline rt_uint32_t platform_get_gic_dist_base(void)
{
    return REALVIEW_GIC_DIST_BASE;
}

rt_inline rt_uint32_t platform_get_gic_cpu_base(void)
{
    return REALVIEW_GIC_CPU_BASE;
}

#define GIC_IRQ_START   0

#define GIC_ACK_INTID_MASK  0x000003ff

#endif  /* __VEXPRESS_A9_H__ */
