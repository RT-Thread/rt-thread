/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __THERMAL_DM_H__
#define __THERMAL_DM_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <drivers/ofw.h>

enum rt_thermal_trip_type thermal_type(const char *type);

rt_err_t thermal_bind(struct rt_thermal_cooling_device *cdev,
        struct rt_thermal_zone_device *zdev);
rt_err_t thermal_unbind(struct rt_thermal_cooling_device *cdev,
        struct rt_thermal_zone_device *zdev);

#endif /* __THERMAL_DM_H__ */
