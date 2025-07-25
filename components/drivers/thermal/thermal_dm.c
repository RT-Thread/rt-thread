/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#define DBG_TAG "rtdm.thermal"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "thermal_dm.h"

enum rt_thermal_trip_type thermal_type(const char *type)
{
    if (!type)
    {
        return RT_THERMAL_TRIP_TYPE_MAX;
    }

    if (!rt_strcmp(type, "active"))
    {
        return RT_THERMAL_TRIP_ACTIVE;
    }
    else if (!rt_strcmp(type, "passive"))
    {
        return RT_THERMAL_TRIP_PASSIVE;
    }
    else if (!rt_strcmp(type, "hot"))
    {
        return RT_THERMAL_TRIP_HOT;
    }
    else if (!rt_strcmp(type, "critical"))
    {
        return RT_THERMAL_TRIP_CRITICAL;
    }

    return RT_THERMAL_TRIP_TYPE_MAX;
}

rt_err_t thermal_bind(struct rt_thermal_cooling_device *cdev,
        struct rt_thermal_zone_device *zdev)
{
    if (cdev->ops->bind)
    {
        return cdev->ops->bind(cdev, zdev);
    }

    return RT_EOK;
}

rt_err_t thermal_unbind(struct rt_thermal_cooling_device *cdev,
        struct rt_thermal_zone_device *zdev)
{
    if (cdev->ops->unbind)
    {
        return cdev->ops->unbind(cdev, zdev);
    }

    return RT_EOK;
}
