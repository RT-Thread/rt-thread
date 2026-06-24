/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "dvfs.event"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

rt_err_t rt_dvfs_event_register(struct rt_dvfs_event *ev)
{
    if (!ev || !ev->dev || !ev->ops)
    {
        return -RT_EINVAL;
    }

    RT_ASSERT(ev->ops->ready != RT_NULL);
    RT_ASSERT(ev->ops->read != RT_NULL);

    ev->enable_count = 0;
    rt_spin_lock_init(&ev->lock);

    rt_dm_dev_bind_fwdata(ev->dev, RT_NULL, ev);

    return RT_EOK;
}

rt_err_t rt_dvfs_event_unregister(struct rt_dvfs_event *ev)
{
    if (!ev || !ev->dev)
    {
        return -RT_EINVAL;
    }

#ifdef RT_USING_OFW
    if (ev->dev->ofw_node)
    {
        struct rt_ofw_node *np = ev->dev->ofw_node;

        if (rt_ref_read(&np->ref) > 1)
        {
            return -RT_EBUSY;
        }
    }
#endif /* RT_USING_OFW */

    rt_dvfs_event_disable(ev);

    rt_dm_dev_unbind_fwdata(ev->dev, RT_NULL);

    return RT_EOK;
}

rt_err_t rt_dvfs_event_ready(struct rt_dvfs_event *ev)
{
    rt_err_t err;

    if (!ev)
    {
        return -RT_EINVAL;
    }

    if (!rt_dvfs_event_is_enabled(ev))
    {
        return -RT_EIO;
    }

    rt_spin_lock(&ev->lock);
    err = ev->ops->ready(ev);
    rt_spin_unlock(&ev->lock);

    return err;
}

rt_err_t rt_dvfs_event_read(struct rt_dvfs_event *ev, struct rt_dvfs_event_data *evd)
{
    rt_err_t err;

    if (!ev || !evd)
    {
        return -RT_EINVAL;
    }

    if (!rt_dvfs_event_is_enabled(ev))
    {
        return -RT_EIO;
    }

    evd->total_count = 0;
    evd->load_count = 0;

    rt_spin_lock(&ev->lock);
    err = ev->ops->read(ev, evd);
    rt_spin_unlock(&ev->lock);

    return err;
}

rt_err_t rt_dvfs_event_enable(struct rt_dvfs_event *ev)
{
    rt_err_t err = RT_EOK;

    if (!ev)
    {
        return -RT_EINVAL;
    }

    rt_spin_lock(&ev->lock);

    if (ev->ops->enable && ev->enable_count == 0)
    {
        if ((err = ev->ops->enable(ev)))
        {
            goto _out_lock;
        }
    }
    ++ev->enable_count;

_out_lock:
    rt_spin_unlock(&ev->lock);

    return err;
}

rt_err_t rt_dvfs_event_disable(struct rt_dvfs_event *ev)
{
    rt_err_t err = RT_EOK;

    if (!ev)
    {
        return -RT_EINVAL;
    }

    rt_spin_lock(&ev->lock);

    if (ev->enable_count <= 0)
    {
        LOG_W("%s: No enabled before", rt_dm_dev_get_name(ev->dev));
        err = -RT_EIO;
        goto _out_lock;
    }

    if (ev->ops->disable && ev->enable_count == 1)
    {
        if ((err = ev->ops->disable(ev)))
        {
            goto _out_lock;
        }
    }
    --ev->enable_count;

_out_lock:
    rt_spin_unlock(&ev->lock);

    return err;
}

rt_bool_t rt_dvfs_event_is_enabled(struct rt_dvfs_event *ev)
{
    rt_bool_t res;

    if (!ev)
    {
        return RT_FALSE;
    }

    rt_spin_lock(&ev->lock);

    res = ev->enable_count > 0;

    rt_spin_unlock(&ev->lock);

    return res;
}

rt_err_t rt_dvfs_event_reset(struct rt_dvfs_event *ev)
{
    rt_err_t err;

    if (!ev)
    {
        return -RT_EINVAL;
    }

    if (!rt_dvfs_event_is_enabled(ev))
    {
        return -RT_EIO;
    }

    rt_spin_lock(&ev->lock);

    if (ev->ops->reset)
    {
        err = ev->ops->reset(ev);
    }
    else
    {
        err = RT_EOK;
    }

    rt_spin_unlock(&ev->lock);

    return err;
}

struct rt_dvfs_event *rt_dvfs_event_get(struct rt_device *dev, const char *name, int index)
{
    struct rt_dvfs_event *ev = rt_err_ptr(-RT_ENOSYS);

#ifdef RT_USING_OFW
    if (dev->ofw_node)
    {
        struct rt_ofw_node *np = rt_ofw_parse_phandle(dev->ofw_node, name, index);

        if (!np)
        {
            return rt_err_ptr(-RT_EEMPTY);
        }

        ev = rt_ofw_data(np);
    }
#endif /* RT_USING_OFW */

    return ev;
}

void rt_dvfs_event_put(struct rt_dvfs_event *ev)
{
    if (!ev)
    {
        return;
    }

#ifdef RT_USING_OFW
    rt_ofw_node_put(ev->dev->ofw_node);
#endif
}
