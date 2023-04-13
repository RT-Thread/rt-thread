/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-13     flybreak     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <string.h>
#include <stdlib.h>

#define DBG_TAG "dev_bus"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#if defined(RT_USING_POSIX_DEVIO)
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <dfs_file.h>

static int bus_fops_open(struct dfs_file *fd)
{
    LOG_D("bus fops open");
    return 0;
}

static int bus_fops_close(struct dfs_file *fd)
{
    LOG_D("bus fops close");
    return 0;
}

static const struct dfs_file_ops bus_fops =
{
    bus_fops_open,
    bus_fops_close,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
};
#endif

rt_device_t rt_device_bus_create(char *name, int attach_size)
{
    rt_err_t result = RT_EOK;
    rt_device_t dev = rt_device_create(RT_Device_Class_Bus, 0);

    result = rt_device_register(dev, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE);
    if (result < 0)
    {
        rt_kprintf("dev bus [%s] register failed!, ret=%d\n", name, result);
        return RT_NULL;
    }
#if defined(RT_USING_POSIX_DEVIO)
    dev->fops = &bus_fops;
#endif

    LOG_D("bus create");
    return dev;
}

rt_err_t rt_device_bus_destroy(rt_device_t dev)
{
    rt_device_unregister(dev);
    dev->parent.type = RT_Object_Class_Device;
    rt_device_destroy(dev);
    LOG_D("bus destroy");
    return RT_EOK;
}
