/*
 * COPYRIGHT (C) 2015, Real-Thread Information Technology Ltd
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
    return GIC_DISTRIBUTOR_BASE;
}

rt_base_t platform_get_gic_redist_base(void)
{
    return GIC_REDISTRIBUTOR_BASE;
}

rt_base_t platform_get_gic_cpu_base(void)
{
    return GIC_REDISTRIBUTOR_BASE;
}
