/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-10     Siwei Xu     Add i.MX91 SDK
 */
#include "imx91.h"

#include "MIMX9131.h"

#include <rtconfig.h>
#include <ioremap.h>

rt_base_t platform_get_gic_dist_base(void)
{
    return (rt_base_t)rt_ioremap((void *)GIC_DISTRIBUTOR_BASE, GIC_DISTRIBUTOR_SIZE);
}

rt_base_t platform_get_gic_redist_base(void)
{
    return (rt_base_t)rt_ioremap((void *)GIC_REDISTRIBUTOR_BASE, GIC_REDISTRIBUTOR_SIZE);
}

rt_base_t platform_get_gic_cpu_base(void)
{
    return (rt_base_t)rt_ioremap((void *)GIC_REDISTRIBUTOR_BASE, GIC_REDISTRIBUTOR_SIZE);
}
