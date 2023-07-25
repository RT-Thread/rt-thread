/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-12     ErikChan      the first version
 */

#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <drivers/core/device.h>

struct rt_driver
{
    struct rt_bus *bus;
    rt_list_t node;

#ifdef RT_USING_DEVICE_OPS
    const struct rt_device_ops *dev_ops;
#else
    /* common device interface */
    rt_err_t  (*init)   (rt_device_t dev);
    rt_err_t  (*open)   (rt_device_t dev, rt_uint16_t oflag);
    rt_err_t  (*close)  (rt_device_t dev);
    rt_ssize_t (*read)  (rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
    rt_ssize_t (*write) (rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
    rt_err_t  (*control)(rt_device_t dev, int cmd, void *args);
#endif

    const struct filesystem_ops *fops;

    const char *name;

    int (*probe)(struct rt_device *dev);
    int (*remove)(struct rt_device *dev);

    void *priv;
};

int rt_driver_probe_device(struct rt_driver *drv, struct rt_device *dev);

rt_err_t rt_driver_register(rt_driver_t drv);
rt_err_t rt_driver_unregister(rt_driver_t drv);

#define RT_DRIVER_EXPORT(driver, bus_name, mode)    \
static int ___##driver##_register(void)             \
{                                                   \
    rt_##bus_name##_driver_register(&driver);       \
    return 0;                                       \
}                                                   \
INIT_DEVICE_EXPORT(___##driver##_register);         \

#endif /* __DRIVER_H__ */
