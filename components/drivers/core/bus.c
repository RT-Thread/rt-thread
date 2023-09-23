/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-13     flybreak     the first version
 * 2023-04-12     ErikChan     support rt_bus
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <string.h>
#include <stdlib.h>

#define DBG_TAG "dev_bus"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_DM
#include <drivers/core/bus.h>

static struct rt_bus bus_root =
{
    .name = "root",
    .children = RT_LIST_OBJECT_INIT(bus_root.children),
};
#endif

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
/**
 * @brief This function get the root bus
 */
rt_bus_t rt_bus_root(void)
{
    return &bus_root;
}

/**
 *  @brief This function loop the dev_list of the bus, and call fn in each loop
 *
 *  @param bus the target bus
 *
 *  @param drv the target drv to be matched
 *
 *  @param fn  the function callback in each loop
 *
 *  @return the error code, RT_EOK on added successfully.
 */
rt_err_t rt_bus_for_each_dev(rt_bus_t bus, rt_driver_t drv, int (*fn)(rt_driver_t drv, rt_device_t dev))
{
    rt_base_t level;
    rt_device_t dev;

    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(drv != RT_NULL);

    level = rt_spin_lock_irqsave(&bus->spinlock);

    rt_list_for_each_entry(dev, &bus->dev_list, node)
    {
        fn(drv, dev);
    }

    rt_spin_unlock_irqrestore(&bus->spinlock, level);

    return RT_EOK;
}

/**
 *  @brief This function loop the drv_list of the bus, and call fn in each loop
 *
 *  @param bus the target bus
 *
 *  @param dev the target dev to be matched
 *
 *  @param fn  the function callback in each loop
 *
 *  @return the error code, RT_EOK on added successfully.
 */
rt_err_t rt_bus_for_each_drv(rt_bus_t bus, rt_device_t dev, int (*fn)(rt_driver_t drv, rt_device_t dev))
{
    rt_err_t err;
    rt_base_t level;
    rt_driver_t drv;

    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(dev != RT_NULL);

    if (rt_list_isempty(&bus->drv_list))
    {
        return RT_EOK;
    }

    err = -RT_ERROR;

    level = rt_spin_lock_irqsave(&bus->spinlock);

    rt_list_for_each_entry(drv, &bus->drv_list, node)
    {
        if (fn(drv, dev))
        {
            err = -RT_EOK;

            break;
        }
    }

    rt_spin_unlock_irqrestore(&bus->spinlock, level);

    return err;
}

/**
 *  @brief This function add a bus to the root
 *
 *  @param bus_node the bus to be added
 *
 *  @return the error code, RT_EOK on added successfully.
 */
rt_err_t rt_bus_add(rt_bus_t bus_node)
{
    rt_base_t level;

    RT_ASSERT(bus_node != RT_NULL);

    bus_node->bus = &bus_root;
    rt_list_init(&bus_node->list);

    level = rt_spin_lock_irqsave(&bus_node->spinlock);

    rt_list_insert_before(&bus_root.children, &bus_node->list);

    rt_spin_unlock_irqrestore(&bus_node->spinlock, level);

    return RT_EOK;
}

/**
 *  @brief This function match the device and driver, probe them if match successed
 *
 *  @param drv the drv to match/probe
 *
 *  @param dev the dev to match/probe
 *
 *  @return the result of probe, 1 on added successfully.
 */
static int rt_bus_probe(rt_driver_t drv, rt_device_t dev)
{
    int ret = 0;
    rt_bus_t bus = drv->bus;

    if (!bus)
    {
        bus = dev->bus;
    }

    RT_ASSERT(bus != RT_NULL);

    if (!dev->drv && bus->match(drv, dev))
    {
        dev->drv = drv;

        ret = bus->probe(dev);

        if (ret)
        {
            dev->drv = RT_NULL;
        }
    }

    return ret;
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
    rt_base_t level;

    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(drv != RT_NULL);

    drv->bus = bus;

    level = rt_spin_lock_irqsave(&bus->spinlock);

    rt_list_insert_before(&bus->drv_list, &drv->node);

    rt_spin_unlock_irqrestore(&bus->spinlock, level);

    rt_bus_for_each_dev(drv->bus, drv, rt_bus_probe);

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
    rt_base_t level;

    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(dev != RT_NULL);

    dev->bus = bus;

    level = rt_spin_lock_irqsave(&bus->spinlock);

    rt_list_insert_before(&bus->dev_list, &dev->node);

    rt_spin_unlock_irqrestore(&bus->spinlock, level);

    rt_bus_for_each_drv(dev->bus, dev, rt_bus_probe);

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
    RT_ASSERT(drv->bus != RT_NULL);

    LOG_D("Bus(%s) remove driver %s", drv->bus->name, drv->name);

    rt_list_remove(&drv->node);

    return RT_EOK;
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
    RT_ASSERT(dev->bus != RT_NULL);

    LOG_D("Bus(%s) remove device %s", dev->bus->name, dev->name);

    rt_list_remove(&dev->node);

    return RT_EOK;
}

/**
 *  @brief This function find a bus by name
 *  @param bus the name to be finded
 *
 *  @return the bus finded by name.
 */
rt_bus_t rt_bus_find_by_name(char *name)
{
    rt_bus_t bus = RT_NULL;
    struct rt_list_node *node = RT_NULL;

    if (!rt_list_isempty(&bus_root.children))
    {
        rt_list_for_each(node, &bus_root.children)
        {
            bus = rt_list_entry(node, struct rt_bus, list);

            if (!rt_strncmp(bus->name, name, RT_NAME_MAX))
            {
                return bus;
            }
        }
    }

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
    rt_base_t level;

    RT_ASSERT(new_bus != RT_NULL);
    RT_ASSERT(dev != RT_NULL);

    level = rt_spin_lock_irqsave(&new_bus->spinlock);

    rt_list_remove(&dev->node);
    rt_list_insert_before(&new_bus->dev_list, &dev->node);

    rt_list_remove(&dev->drv->node);
    rt_list_insert_before(&new_bus->drv_list, &dev->drv->node);

    rt_spin_unlock_irqrestore(&new_bus->spinlock, level);

    return RT_EOK;
}

/**
 *  @brief This function register a bus
 *  @param bus the bus to be registered
 *
 *  @return the error code, RT_EOK on registeration successfully.
 */
rt_err_t rt_bus_register(rt_bus_t bus)
{
    rt_list_init(&bus->children);
    rt_list_init(&bus->dev_list);
    rt_list_init(&bus->drv_list);

    rt_spin_lock_init(&bus->spinlock);

    rt_bus_add(bus);

    return RT_EOK;
}
#endif
