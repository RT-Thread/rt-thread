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

#include <rtthread.h>

#define DBG_TAG "rtdm.pltaform"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/platform.h>
#include <drivers/core/bus.h>
#include <drivers/core/dm.h>
#include <drivers/core/power_domain.h>

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

    if (!pdev)
    {
        return RT_NULL;
    }

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
#if RT_NAME_MAX > 0
    rt_strcpy(pdrv->parent.parent.name, pdrv->name);
#else
    pdrv->parent.parent.name = pdrv->name;
#endif
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
    struct rt_platform_driver *pdrv = rt_container_of(drv, struct rt_platform_driver, parent);
    struct rt_platform_device *pdev = rt_container_of(dev, struct rt_platform_device, parent);
    struct rt_ofw_node *np = dev->ofw_node;

    /* 1、match with ofw node */
    if (np)
    {
    #ifdef RT_USING_OFW
        pdev->id = rt_ofw_node_match(np, pdrv->ids);
    #else
        pdev->id = RT_NULL;
    #endif
        if (pdev->id)
        {
            return RT_TRUE;
        }
    }

    /* 2、match with name */
    if (pdev->name && pdrv->name)
    {
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
    struct rt_platform_driver *pdrv = rt_container_of(dev->drv, struct rt_platform_driver, parent);
    struct rt_platform_device *pdev = rt_container_of(dev, struct rt_platform_device, parent);
#ifdef RT_USING_OFW
    struct rt_ofw_node *np = dev->ofw_node;
#endif

    err = rt_dm_power_domain_attach(dev, RT_TRUE);

    if (err && err != -RT_EEMPTY)
    {
        LOG_E("Attach power domain error = %s in device %s", rt_strerror(err),
        #ifdef RT_USING_OFW
            (pdev->name && pdev->name[0]) ? pdev->name : rt_ofw_node_full_name(np)
        #else
            pdev->name
        #endif
            );

        return err;
    }

    err = pdrv->probe(pdev);

    if (!err)
    {
#ifdef RT_USING_OFW
        if (np)
        {
            rt_ofw_node_set_flag(np, RT_OFW_F_READLY);
        }
#endif
    }
    else
    {
        if (err == -RT_ENOMEM)
        {
            LOG_W("System not memory in driver %s", pdrv->name);
        }

        rt_dm_power_domain_detach(dev, RT_TRUE);
    }

    return err;
}

static rt_err_t platform_remove(rt_device_t dev)
{
    struct rt_platform_driver *pdrv = rt_container_of(dev->drv, struct rt_platform_driver, parent);
    struct rt_platform_device *pdev = rt_container_of(dev, struct rt_platform_device, parent);

    if (pdrv && pdrv->remove)
    {
        pdrv->remove(pdev);
    }

    rt_dm_power_domain_detach(dev, RT_TRUE);
    rt_platform_ofw_free(pdev);

    return RT_EOK;
}

static rt_err_t platform_shutdown(rt_device_t dev)
{
    struct rt_platform_driver *pdrv = rt_container_of(dev->drv, struct rt_platform_driver, parent);
    struct rt_platform_device *pdev = rt_container_of(dev, struct rt_platform_device, parent);

    if (pdrv && pdrv->shutdown)
    {
        pdrv->shutdown(pdev);
    }

    rt_dm_power_domain_detach(dev, RT_TRUE);
    rt_platform_ofw_free(pdev);

    return RT_EOK;
}

static struct rt_bus platform_bus =
{
    .name = "platform",
    .match = platform_match,
    .probe = platform_probe,
    .remove = platform_remove,
    .shutdown = platform_shutdown,
};

static int platform_bus_init(void)
{
    rt_bus_register(&platform_bus);

    return 0;
}
INIT_CORE_EXPORT(platform_bus_init);
