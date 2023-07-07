/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-12     ErikChan      the first version
 */

#include <rtthread.h>

#include <drivers/platform.h>
#include <drivers/core/bus.h>
#include <drivers/core/dm.h>

static struct rt_bus platform_bus;

/**
 *  @brief This function create a platform device.
 *
 *  @param name is name of the platform device.
 *
 *  @return a new platform device.
 */
struct rt_platform_device *rt_platform_device_alloc(const char *name)
{
    struct rt_platform_device *pdev = rt_calloc(1, sizeof(*pdev));

    pdev->parent.bus = &platform_bus;
    pdev->name = name;

    return pdev;
}

/**
 *  @brief This function register a rt_driver to platform bus.
 *
 *  @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_platform_driver_register(struct rt_platform_driver *pdrv)
{
    RT_ASSERT(pdrv != RT_NULL);

    pdrv->parent.bus = &platform_bus;

    return rt_driver_register(&pdrv->parent);
}

/**
 *  @brief This function register a rt_device to platform bus.
 *
 *  @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_platform_device_register(struct rt_platform_device *pdev)
{
    RT_ASSERT(pdev != RT_NULL);

    return rt_bus_add_device(&platform_bus, &pdev->parent);
}

static rt_bool_t platform_match(rt_driver_t drv, rt_device_t dev)
{
    struct rt_ofw_node *np = dev->ofw_node;
    struct rt_platform_driver *pdrv = rt_container_of(drv, struct rt_platform_driver, parent);
    struct rt_platform_device *pdev = rt_container_of(dev, struct rt_platform_device, parent);

    if (np)
    {
        /* 1、match with ofw node */
        pdev->id = rt_ofw_node_match(np, pdrv->ids);

        return !!pdev->id;
    }
    else if (pdev->name && pdrv->name)
    {
        /* 2、match with name */
        if (pdev->name == pdrv->name)
        {
            return RT_TRUE;
        }
        else
        {
            return !rt_strcmp(pdrv->name, pdev->name);
        }
    }

    return RT_FALSE;
}

static rt_err_t platform_probe(rt_device_t dev)
{
    rt_err_t err;
    struct rt_ofw_node *np = dev->ofw_node;
    struct rt_platform_driver *pdrv = rt_container_of(dev->drv, struct rt_platform_driver, parent);
    struct rt_platform_device *pdev = rt_container_of(dev, struct rt_platform_device, parent);

    err = pdrv->probe(pdev);

    if (!err)
    {
        if (np)
        {
            rt_ofw_node_set_flag(np, RT_OFW_F_READLY);
        }
    }
    else
    {
        if (np)
        {
            rt_ofw_data(np) = &pdev->parent;
        }
    }

    return err;
}

static struct rt_bus platform_bus =
{
    .name = "platform",
    .match = platform_match,
    .probe = platform_probe,
};

static int platform_bus_init(void)
{
    rt_bus_register(&platform_bus);

    return 0;
}
INIT_CORE_EXPORT(platform_bus_init);
