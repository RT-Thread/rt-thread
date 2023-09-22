/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-12     ErikChan      the first version
 * 2023-10-13     zmshahaha    distinguish ofw and none-ofw situation
 */

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef RT_USING_OFW
#include <drivers/ofw.h>
#endif

#include <drivers/core/driver.h>

struct rt_platform_device
{
    struct rt_device parent;

    const char *name;

#ifdef RT_USING_OFW
    const struct rt_ofw_node_id *id;
#endif

    void *priv;
};

struct rt_platform_driver
{
    struct rt_driver parent;

    const char *name;

#ifdef RT_USING_OFW
    const struct rt_ofw_node_id *ids;
#endif

    rt_err_t (*probe)(struct rt_platform_device *pdev);
};

struct rt_platform_device *rt_platform_device_alloc(const char *name);

rt_err_t rt_platform_driver_register(struct rt_platform_driver *pdrv);
rt_err_t rt_platform_device_register(struct rt_platform_device *pdev);

#define RT_PLATFORM_DRIVER_EXPORT(driver)  RT_DRIVER_EXPORT(driver, platform, BUILIN)

#endif /* __PLATFORM_H__ */
