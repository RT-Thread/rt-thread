/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-12     ErikChan      the first version
 */

#ifndef __CORE_BUS_H__
#define __CORE_BUS_H__

#include <rthw.h>
#include <rtdef.h>
#include <drivers/core/driver.h>

typedef struct rt_bus *rt_bus_t;

struct rt_bus
{
    struct rt_object parent;    /**< inherit from rt_object */

    const char *name;

    rt_list_t list;
    rt_list_t dev_list;
    rt_list_t drv_list;

    struct rt_spinlock dev_lock;
    struct rt_spinlock drv_lock;

    rt_bool_t (*match)(rt_driver_t drv, rt_device_t dev);
    rt_err_t  (*probe)(rt_device_t dev);
    rt_err_t  (*remove)(rt_device_t dev);
    rt_err_t  (*shutdown)(rt_device_t dev);
};

rt_err_t rt_bus_for_each_dev(rt_bus_t bus, void *data, int (*fn)(rt_device_t dev, void *));
rt_err_t rt_bus_for_each_drv(rt_bus_t bus, void *data, int (*fn)(rt_driver_t drv, void *));

rt_err_t rt_bus_add_driver(rt_bus_t bus, rt_driver_t drv);
rt_err_t rt_bus_add_device(rt_bus_t bus, rt_device_t dev);
rt_err_t rt_bus_remove_driver(rt_driver_t drv);
rt_err_t rt_bus_remove_device(rt_device_t dev);

rt_err_t rt_bus_shutdown(void);

rt_bus_t rt_bus_find_by_name(const char *name);
rt_err_t rt_bus_reload_driver_device(rt_bus_t new_bus, rt_device_t dev);

rt_err_t rt_bus_register(rt_bus_t bus);

#endif /* __BUS_H__ */
