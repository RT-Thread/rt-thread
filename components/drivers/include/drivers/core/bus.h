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

    char *name;
    struct rt_bus *bus;

    rt_list_t list;
    rt_list_t children;
    rt_list_t dev_list;
    rt_list_t drv_list;

    struct rt_spinlock spinlock;

    rt_bool_t (*match)(rt_driver_t drv, rt_device_t dev);
    rt_err_t  (*probe)(rt_device_t dev);
};

rt_bus_t rt_bus_root(void);

rt_err_t rt_bus_for_each_dev(rt_bus_t bus, rt_driver_t drv, int (*fn)(rt_driver_t drv, rt_device_t dev));
rt_err_t rt_bus_for_each_drv(rt_bus_t bus, rt_device_t dev, int (*fn)(rt_driver_t drv, rt_device_t dev));

rt_err_t rt_bus_add(rt_bus_t bus);
rt_err_t rt_bus_add_driver(rt_bus_t bus, rt_driver_t drv);
rt_err_t rt_bus_add_device(rt_bus_t bus, rt_device_t dev);
rt_err_t rt_bus_remove_driver(rt_driver_t drv);
rt_err_t rt_bus_remove_device(rt_device_t dev);

rt_bus_t rt_bus_find_by_name(char *name);
rt_err_t rt_bus_reload_driver_device(rt_bus_t new_bus, rt_device_t dev);

rt_err_t rt_bus_register(rt_bus_t bus);

#endif /* __BUS_H__ */
