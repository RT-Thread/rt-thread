/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <drivers/ofw.h>
#include <drivers/rpmsg.h>
#include <drivers/core/bus.h>
#include <drivers/core/power_domain.h>

#define DBG_TAG "rtdm.rpmsg"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_uint32_t rpmsg_mode = RT_RPMSG_MODE_SLAVE;

static int rpmsg_mode_setup(void)
{
    const char *mode = RT_NULL;

#ifdef RT_USING_OFW
    mode = rt_ofw_bootargs_select("rpmsg.mode=", 0);
#endif

    if (!mode)
    {
        goto _end;
    }

    if (!rt_strcmp(mode, "master"))
    {
        rpmsg_mode = RT_RPMSG_MODE_MASTER;
    }
    else if (!rt_strcmp(mode, "slave"))
    {
        rpmsg_mode = RT_RPMSG_MODE_SLAVE;
    }
    else
    {
        LOG_W("Unknown mode of RPMsg: %s", mode);

        return (int)-RT_EINVAL;
    }

_end:
    LOG_D("RPMsg mode: %s", rpmsg_mode == RT_RPMSG_MODE_MASTER ? "master" : "slave");

    return 0;
}
INIT_CORE_EXPORT(rpmsg_mode_setup);

rt_uint32_t rt_rpmsg_mode(void)
{
    return rpmsg_mode;
}

struct rt_rpmsg_endpoint *rt_rpmsg_create_endpoint(struct rt_rpmsg_device *rdev,
        struct rt_rpmsg_endpoint_info *info, rt_rpmsg_rx_callback rx_cb)
{
    rt_err_t err;
    rt_ubase_t level;
    struct rt_rpmsg_endpoint *ept;

    RT_ASSERT(rdev != RT_NULL);
    RT_ASSERT(info != RT_NULL);

    ept = rt_calloc(1, sizeof(*ept));

    if (!ept)
    {
        return rt_err_ptr(-RT_ENOMEM);
    }
    ept->rdev = rdev;

    rt_memcpy(&ept->info, info, sizeof(ept->info));
    ept->rx_callback = rx_cb ? : rt_container_of(rdev->parent.drv,
            struct rt_rpmsg_driver, parent)->rx_callback;

    RT_ASSERT(ept->rx_callback != RT_NULL);

    err = rdev->ops->create_endpoint(rdev, ept, info);

    if (err)
    {
        rt_free(ept);
        return rt_err_ptr(err);
    }

    rt_spin_lock_init(&ept->lock);

    rt_list_init(&ept->list);
    level = rt_spin_lock_irqsave(&rdev->lock);
    rt_list_insert_before(&rdev->ept_nodes, &ept->list);
    rt_spin_unlock_irqrestore(&rdev->lock, level);

    return ept;
}

rt_err_t rt_rpmsg_destroy_endpoint(struct rt_rpmsg_device *rdev,
        struct rt_rpmsg_endpoint *ept)
{
    rt_err_t err;
    rt_ubase_t level;

    RT_ASSERT(rdev != RT_NULL);
    RT_ASSERT(ept != RT_NULL);

    err = rdev->ops->destroy_endpoint(rdev, ept);

    if (err)
    {
        return err;
    }

    level = rt_spin_lock_irqsave(&rdev->lock);
    rt_list_remove(&ept->list);
    rt_spin_unlock_irqrestore(&rdev->lock, level);

    rt_free(ept);

    return RT_EOK;
}

struct rt_rpmsg_endpoint *rt_rpmsg_find_endpoint(struct rt_rpmsg_device *rdev,
        struct rt_rpmsg_endpoint_info *info)
{
    rt_ubase_t level;
    struct rt_rpmsg_endpoint *ept = RT_NULL, *ept_tmp;

    RT_ASSERT(rdev != RT_NULL);
    RT_ASSERT(info != RT_NULL);

    level = rt_spin_lock_irqsave(&rdev->lock);

    rt_list_for_each_entry(ept_tmp, &rdev->ept_nodes, list)
    {
        if (info->src != RT_RPMSG_ADDR_ANY && info->src != ept_tmp->info.src)
        {
            continue;
        }

        if (info->dst != RT_RPMSG_ADDR_ANY && info->dst != ept_tmp->info.dst)
        {
            continue;
        }

        if (info->name[0] &&
            rt_strncmp(info->name, ept_tmp->info.name, RT_RPMSG_NAME_SIZE))
        {
            continue;
        }

        ept = ept_tmp;
        break;
    }

    rt_spin_unlock_irqrestore(&rdev->lock, level);

    return ept;
}

rt_err_t rt_rpmsg_send(struct rt_rpmsg_endpoint *ept,
        const void *data, rt_size_t len)
{
    RT_ASSERT(ept != RT_NULL);

    return rt_rpmsg_sendto(ept, ept->info.dst, data, len);
}

rt_err_t rt_rpmsg_sendto(struct rt_rpmsg_endpoint *ept, rt_uint32_t dst,
        const void *data, rt_size_t len)
{
    RT_ASSERT(ept != RT_NULL);

    return rt_rpmsg_sendto_wait(ept, dst, data, len, 0);
}

rt_err_t rt_rpmsg_send_wait(struct rt_rpmsg_endpoint *ept,
        const void *data, rt_size_t len, rt_int32_t timeout)
{
    RT_ASSERT(ept != RT_NULL);

    return rt_rpmsg_sendto_wait(ept, ept->info.dst, data, len, timeout);
}

rt_err_t rt_rpmsg_sendto_wait(struct rt_rpmsg_endpoint *ept, rt_uint32_t dst,
        const void *data, rt_size_t len, rt_int32_t timeout)
{
    rt_err_t err;
    struct rt_rpmsg_device *rdev;

    RT_ASSERT(ept != RT_NULL);
    rdev = ept->rdev;

    rt_hw_spin_lock(&ept->lock.lock);

    err = rdev->ops->send(rdev, ept->info.src, dst, data, len, timeout);

    rt_hw_spin_unlock(&ept->lock.lock);

    return err;
}

static struct rt_bus rpmsg_bus;

rt_err_t rt_rpmsg_driver_register(struct rt_rpmsg_driver *rdrv)
{
    RT_ASSERT(rdrv != RT_NULL);

    rdrv->parent.bus = &rpmsg_bus;

    return rt_driver_register(&rdrv->parent);
}

rt_err_t rt_rpmsg_device_register(struct rt_rpmsg_device *rdev)
{
    rt_err_t err;

    if ((err = rt_dm_dev_set_name_auto(&rdev->parent, rdev->id.name)) < 0)
    {
        return err;
    }

    rt_list_init(&rdev->ept_nodes);
    rt_spin_lock_init(&rdev->lock);

    return rt_bus_add_device(&rpmsg_bus, &rdev->parent);
}

static rt_bool_t rpmsg_match(rt_driver_t drv, rt_device_t dev)
{
    const struct rt_rpmsg_device_id *id;
    struct rt_rpmsg_driver *rdrv = rt_container_of(drv, struct rt_rpmsg_driver, parent);
    struct rt_rpmsg_device *rdev = rt_container_of(dev, struct rt_rpmsg_device, parent);

    for (id = rdrv->ids; id->name[0]; ++id)
    {
        if (!rt_strncmp(id->name, rdev->id.name, RT_RPMSG_NAME_SIZE))
        {
            rdev->id.data = id->data;

            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

static rt_err_t rpmsg_probe(rt_device_t dev)
{
    rt_err_t err;
    struct rt_rpmsg_driver *rdrv = rt_container_of(dev->drv, struct rt_rpmsg_driver, parent);
    struct rt_rpmsg_device *rdev = rt_container_of(dev, struct rt_rpmsg_device, parent);

    err = rt_dm_power_domain_attach(dev, RT_TRUE);

    if (err && err != -RT_EEMPTY)
    {
        LOG_E("Attach power domain error = %s in device %s",
                rt_dm_dev_get_name(dev), rt_strerror(err));

        return err;
    }

    err = rdrv->probe(rdev);

    if (!err)
    {
        rt_dm_power_domain_detach(dev, RT_TRUE);
    }

    return err;
}

static rt_err_t rpmsg_remove(rt_device_t dev)
{
    rt_ubase_t level;
    struct rt_rpmsg_endpoint *ept, *ept_next;
    struct rt_rpmsg_driver *rdrv = rt_container_of(dev->drv, struct rt_rpmsg_driver, parent);
    struct rt_rpmsg_device *rdev = rt_container_of(dev, struct rt_rpmsg_device, parent);

    level = rt_spin_lock_irqsave(&rdev->lock);

    rt_list_for_each_entry_safe(ept, ept_next, &rdev->ept_nodes, list)
    {
        rt_spin_unlock_irqrestore(&rdev->lock, level);

        rt_rpmsg_destroy_endpoint(rdev, ept);

        level = rt_spin_lock_irqsave(&rdev->lock);
    }

    rt_spin_unlock_irqrestore(&rdev->lock, level);

    if (rdrv && rdrv->remove)
    {
        rdrv->remove(rdev);
    }

    rt_dm_power_domain_detach(dev, RT_TRUE);

    return RT_EOK;
}

static struct rt_bus rpmsg_bus =
{
    .name = "rpmsg",
    .match = rpmsg_match,
    .probe = rpmsg_probe,
    .remove = rpmsg_remove,
};

static int rpmsg_bus_init(void)
{
    rt_bus_register(&rpmsg_bus);

    return 0;
}
INIT_CORE_EXPORT(rpmsg_bus_init);
