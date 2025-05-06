/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __REGULATOR_DM_H__
#define __REGULATOR_DM_H__

#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_OFW
rt_err_t regulator_ofw_parse(struct rt_ofw_node *np, struct rt_regulator_param *param);
#else
rt_inline rt_err_t regulator_ofw_parse(struct rt_ofw_node *np, struct rt_regulator_param *param);
{
    return RT_EOK;
}
#endif /* RT_USING_OFW */

#endif /* __REGULATOR_DM_H__ */
