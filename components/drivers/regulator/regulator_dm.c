/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include "regulator_dm.h"

#ifdef RT_USING_OFW
rt_err_t regulator_ofw_parse(struct rt_ofw_node *np, struct rt_regulator_param *param)
{
    rt_uint32_t pval;

    param->name = rt_ofw_prop_read_raw(np, "regulator-name", RT_NULL);

    if (!rt_ofw_prop_read_u32(np, "regulator-min-microvolt", &pval))
    {
        param->min_uvolt = pval;
    }

    if (!rt_ofw_prop_read_u32(np, "regulator-max-microvolt", &pval))
    {
        param->max_uvolt = pval;
    }

    if (!rt_ofw_prop_read_u32(np, "regulator-min-microamp", &pval))
    {
        param->min_uamp = pval;
    }

    if (!rt_ofw_prop_read_u32(np, "regulator-max-microamp", &pval))
    {
        param->max_uamp = pval;
    }

    if (!rt_ofw_prop_read_u32(np, "regulator-ramp-delay", &pval))
    {
        param->ramp_delay = pval;
    }

    if (!rt_ofw_prop_read_u32(np, "regulator-enable-ramp-delay", &pval))
    {
        param->enable_delay = pval;
    }

    param->enable_active_high = rt_ofw_prop_read_bool(np, "enable-active-high");
    param->boot_on = rt_ofw_prop_read_bool(np, "regulator-boot-on");
    param->always_on = rt_ofw_prop_read_bool(np, "regulator-always-on");
    param->soft_start = rt_ofw_prop_read_bool(np, "regulator-soft-start");
    param->pull_down = rt_ofw_prop_read_bool(np, "regulator-pull-down");
    param->over_current_protection = rt_ofw_prop_read_bool(np, "regulator-over-current-protection");

    return RT_EOK;
}
#endif /* RT_USING_OFW */
