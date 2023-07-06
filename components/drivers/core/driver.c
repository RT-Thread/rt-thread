/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <drivers/core/bus.h>

#if defined(RT_USING_POSIX_DEVIO)
#include <rtdevice.h> /* for wqueue_init */
#endif

/**
 * This function attach a driver to bus
 *
 * @param drv the driver to be attached
 */
rt_err_t rt_driver_register(rt_driver_t drv)
{
    rt_err_t ret;
    struct rt_bus *bus = RT_NULL;

    RT_ASSERT(drv != RT_NULL);

    if (drv->bus)
    {
        bus = drv->bus;
        ret = rt_bus_add_driver(bus, drv);
    }
    else
    {
        ret = -RT_EINVAL;
    }

    return ret;
}
RTM_EXPORT(rt_driver_register);

/**
 * This function remove driver from system.
 *
 * @param drv the driver to be removed
 */
rt_err_t rt_driver_unregister(rt_driver_t drv)
{
    rt_err_t ret;

    ret = rt_bus_remove_driver(drv);

    return ret;
}
RTM_EXPORT(rt_driver_register);
