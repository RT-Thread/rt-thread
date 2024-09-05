/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-13     flybreak     the first version
 * 2023-04-12     ErikChan     support rt_bus
 */

#include <rtthread.h>

#include <string.h>
#include <stdlib.h>

#define DBG_TAG "dev_bus"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_DEV_BUS

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

#endif

#ifdef RT_USING_DM
#include <drivers/core/bus.h>

static struct rt_spinlock bus_lock = {};
static rt_list_t bus_nodes = RT_LIST_OBJECT_INIT(bus_nodes);

static void _dm_bus_lock(struct rt_spinlock *spinlock)
{
    rt_hw_spin_lock(&spinlock->lock);
}

static void _dm_bus_unlock(struct rt_spinlock *spinlock)
{
    rt_hw_spin_unlock(&spinlock->lock);
}

/**
 *  @brief This function loop the dev_list of the bus, and call fn in each loop
 *
 *  @param bus the target bus
 *
 *  @param data the data push when call fn
 *
 *  @param fn  the function callback in each loop
 *
 *  @return the error code, RT_EOK on added successfully.
 */
rt_err_t rt_bus_for_each_dev(rt_bus_t bus, void *data, int (*fn)(rt_device_t dev, void *))
{
    rt_device_t dev;
    rt_err_t err = -RT_EEMPTY;
    rt_list_t *dev_list;
    struct rt_spinlock *dev_lock;

    RT_ASSERT(bus != RT_NULL);

    dev_list = &bus->dev_list;
    dev_lock = &bus->dev_lock;

    _dm_bus_lock(dev_lock);
    dev = rt_list_entry(dev_list->next, struct rt_device, node);
    _dm_bus_unlock(dev_lock);

    while (&dev->node != dev_list)
    {
        if (!fn(dev, data))
        {
            err = RT_EOK;

            break;
        }

        _dm_bus_lock(dev_lock);
        dev = rt_list_entry(dev->node.next, struct rt_device, node);
        _dm_bus_unlock(dev_lock);
    }

    return err;
}

/**
 *  @brief This function loop the drv_list of the bus, and call fn in each loop
 *
 *  @param bus the target bus
 *
 *  @param data the data push when call fn
 *
 *  @param fn  the function callback in each loop
 *
 *  @return the error code, RT_EOK on added successfully.
 */
rt_err_t rt_bus_for_each_drv(rt_bus_t bus, void *data, int (*fn)(rt_driver_t drv, void *))
{
    rt_driver_t drv;
    rt_err_t err = -RT_EEMPTY;
    rt_list_t *drv_list;
    struct rt_spinlock *drv_lock;

    RT_ASSERT(bus != RT_NULL);

    drv_list = &bus->drv_list;
    drv_lock = &bus->drv_lock;

    _dm_bus_lock(drv_lock);
    drv = rt_list_entry(drv_list->next, struct rt_driver, node);
    _dm_bus_unlock(drv_lock);

    while (&drv->node != drv_list)
    {
        if (!fn(drv, data))
        {
            err = RT_EOK;

            break;
        }

        _dm_bus_lock(drv_lock);
        drv = rt_list_entry(drv->node.next, struct rt_driver, node);
        _dm_bus_unlock(drv_lock);
    }

    return err;
}

static rt_err_t bus_probe(rt_driver_t drv, rt_device_t dev)
{
    rt_bus_t bus = drv->bus;
    rt_err_t err = -RT_EEMPTY;

    if (!bus)
    {
        bus = dev->bus;
    }

    if (!dev->drv && bus->match(drv, dev))
    {
        dev->drv = drv;

        err = bus->probe(dev);

        if (err)
        {
            dev->drv = RT_NULL;
        }
    }

    return err;
}

static int bus_probe_driver(rt_device_t dev, void *drv_ptr)
{
    bus_probe(drv_ptr, dev);

    /*
     * The driver is shared by multiple devices,
     * so we always return the '1' to enumerate all devices.
     */
    return 1;
}

static int bus_probe_device(rt_driver_t drv, void *dev_ptr)
{
    rt_err_t err;

    err = bus_probe(drv, dev_ptr);

    if (!err)
    {
        rt_bus_t bus = drv->bus;

        _dm_bus_lock(&bus->drv_lock);
        ++drv->ref_count;
        _dm_bus_unlock(&bus->drv_lock);
    }

    return err;
}

/**
 *  @brief This function add a driver to the drv_list of a specific bus
 *
 *  @param bus the bus to add
 *
 *  @param drv the driver to be added
 *
 *  @return the error code, RT_EOK on added successfully.
 */
rt_err_t rt_bus_add_driver(rt_bus_t bus, rt_driver_t drv)
{
    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(drv != RT_NULL);

    drv->bus = bus;
    rt_list_init(&drv->node);

    _dm_bus_lock(&bus->drv_lock);
    rt_list_insert_before(&bus->drv_list, &drv->node);
    _dm_bus_unlock(&bus->drv_lock);

    rt_bus_for_each_dev(bus, drv, bus_probe_driver);

    return RT_EOK;
}

/**
 *  @brief This function add a device to the dev_list of a specific bus
 *
 *  @param bus the bus to add
 *
 *  @param dev the device to be added
 *
 *  @return the error code, RT_EOK on added successfully.
 */
rt_err_t rt_bus_add_device(rt_bus_t bus, rt_device_t dev)
{
    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(dev != RT_NULL);

    dev->bus = bus;
    rt_list_init(&dev->node);

    _dm_bus_lock(&bus->dev_lock);
    rt_list_insert_before(&bus->dev_list, &dev->node);
    _dm_bus_unlock(&bus->dev_lock);

    rt_bus_for_each_drv(bus, dev, bus_probe_device);

    return RT_EOK;
}

/**
 *  @brief This function remove a driver from bus
 *
 *  @param drv the driver to be removed
 *
 *  @return the error code, RT_EOK on added successfully.
 */
rt_err_t rt_bus_remove_driver(rt_driver_t drv)
{
    rt_err_t err;
    rt_bus_t bus;

    RT_ASSERT(drv != RT_NULL);
    RT_ASSERT(drv->bus != RT_NULL);

    bus = drv->bus;

    LOG_D("Bus(%s) remove driver %s", bus->name, drv->parent.name);

    _dm_bus_lock(&bus->drv_lock);

    if (drv->ref_count)
    {
        err = -RT_EBUSY;
    }
    else
    {
        rt_list_remove(&drv->node);
        err = RT_EOK;
    }

    _dm_bus_unlock(&bus->drv_lock);

    return err;
}

/**
 *  @brief This function remove a device from bus
 *
 *  @param dev the device to be removed
 *
 *  @return the error code, RT_EOK on added successfully.
 */
rt_err_t rt_bus_remove_device(rt_device_t dev)
{
    rt_bus_t bus;
    rt_driver_t drv;
    rt_err_t err = RT_EOK;

    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(dev->bus != RT_NULL);

    bus = dev->bus;
    drv = dev->drv;

    LOG_D("Bus(%s) remove device %s", bus->name, dev->parent.name);

    _dm_bus_lock(&bus->dev_lock);
    rt_list_remove(&dev->node);
    _dm_bus_unlock(&bus->dev_lock);

    if (dev->bus->remove)
    {
        err = dev->bus->remove(dev);
    }
    else if (drv)
    {
        if (drv->remove)
        {
            err = drv->remove(dev);
        }

        /* device and driver are in the same bus */
        _dm_bus_lock(&bus->drv_lock);
        --drv->ref_count;
        _dm_bus_unlock(&bus->drv_lock);
    }

    return err;
}

struct bus_shutdown_info
{
    rt_bus_t bus;

    rt_err_t err;
};

static int device_shutdown(rt_device_t dev, void *info_ptr)
{
    rt_bus_t bus;
    rt_err_t err = RT_EOK;
    struct bus_shutdown_info *info = info_ptr;

    bus = info->bus;

    if (bus->shutdown)
    {
        LOG_D("Device(%s) shutdown", dev->parent.name);
        err = bus->shutdown(dev);
        LOG_D("  Result: %s", rt_strerror(err));
    }
    else if (dev->drv && dev->drv->shutdown)
    {
        LOG_D("Device(%s) shutdown", dev->parent.name);
        err = dev->drv->shutdown(dev);
        LOG_D("  Result: %s", rt_strerror(err));
    }

    if (err)
    {
        /* Only get the last one while system not crash */
        info->err = err;
    }

    /* Go on, we want to ask all devices to shutdown */
    return 1;
}

/**
 *  @brief This function call all buses' shutdown
 *
 *  @return the error code, RT_EOK on shutdown successfully.
 */
rt_err_t rt_bus_shutdown(void)
{
    rt_bus_t bus = RT_NULL;
    struct bus_shutdown_info info =
    {
        .err = RT_EOK,
    };

    _dm_bus_lock(&bus_lock);

    rt_list_for_each_entry(bus, &bus_nodes, list)
    {
        info.bus = bus;
        rt_bus_for_each_dev(bus, &info, device_shutdown);
    }

    _dm_bus_unlock(&bus_lock);

    return info.err;
}

/**
 *  @brief This function find a bus by name
 *  @param bus the name to be finded
 *
 *  @return the bus finded by name.
 */
rt_bus_t rt_bus_find_by_name(const char *name)
{
    rt_bus_t bus = RT_NULL;

    RT_ASSERT(name != RT_NULL);

    _dm_bus_lock(&bus_lock);

    rt_list_for_each_entry(bus, &bus_nodes, list)
    {
        if (!rt_strncmp(bus->name, name, RT_NAME_MAX))
        {
            break;
        }
    }

    _dm_bus_unlock(&bus_lock);

    return bus;
}

/**
 *  @brief This function transfer dev_list and drv_list to the other bus
 *
 *  @param new_bus the bus to transfer
 *
 *  @param dev the target device
 *
 *  @return the error code, RT_EOK on added successfully.
 */
rt_err_t rt_bus_reload_driver_device(rt_bus_t new_bus, rt_device_t dev)
{
    rt_bus_t old_bus;

    RT_ASSERT(new_bus != RT_NULL);
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(dev->bus != RT_NULL);
    RT_ASSERT(dev->bus != new_bus);

    old_bus = dev->bus;

    _dm_bus_lock(&old_bus->dev_lock);
    rt_list_remove(&dev->node);
    _dm_bus_unlock(&old_bus->dev_lock);

    return rt_bus_add_device(new_bus, dev);
}

/**
 *  @brief This function register a bus
 *  @param bus the bus to be registered
 *
 *  @return the error code, RT_EOK on registeration successfully.
 */
rt_err_t rt_bus_register(rt_bus_t bus)
{
    RT_ASSERT(bus != RT_NULL);

    rt_list_init(&bus->list);
    rt_list_init(&bus->dev_list);
    rt_list_init(&bus->drv_list);

    rt_spin_lock_init(&bus->dev_lock);
    rt_spin_lock_init(&bus->drv_lock);

    _dm_bus_lock(&bus_lock);

    rt_list_insert_before(&bus_nodes, &bus->list);

    _dm_bus_unlock(&bus_lock);

    return RT_EOK;
}
#endif
