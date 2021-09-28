/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-29     Carl    the first version
 *
 */

#ifndef __FT2004_H__
#define __FT2004_H__

#include <rthw.h>
#include <rtthread.h>
#include "ft_parameters.h"

#define ARM_GIC_NR_IRQS 160
#define ARM_GIC_MAX_NR 1
#define MAX_HANDLERS 160
#define GIC_IRQ_START 0
#define GIC_ACK_INTID_MASK 0x000003ff
rt_uint64_t get_main_cpu_affval(void);

rt_inline rt_uint32_t platform_get_gic_dist_base(void)
{
    return FT_GICV3_DISTRIBUTOR_BASEADDRESS;
}

#endif // !
