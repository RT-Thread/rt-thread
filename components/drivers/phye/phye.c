/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

#define DBG_TAG "rtdm.phye"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <rtdevice.h>
#include <rtthread.h>

rt_err_t rt_phye_register(struct rt_phye *phye)
{
    rt_err_t err;

    if (phye && phye->dev && phye->ops)
    {
        err = RT_EOK;

        rt_spin_lock_init(&phye->lock);
        rt_dm_dev_bind_fwdata(phye->dev, RT_NULL, phye);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t rt_phye_unregister(struct rt_phye *phye)
{
    rt_err_t err;

    if (phye)
    {
        err = RT_EOK;

        rt_spin_lock(&phye->lock);

        if (phye->dev->ref_count)
        {
            err = -RT_EBUSY;
            LOG_E("%s is busy in unregister", rt_dm_dev_get_name(phye->dev));
        }

        rt_dm_dev_unbind_fwdata(phye->dev, RT_NULL);

        rt_spin_unlock(&phye->lock);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t rt_phye_init(struct rt_phye *phye)
{
    rt_err_t err;

    if (!phye)
    {
        return RT_EOK;
    }

    err = RT_EOK;

    rt_spin_lock(&phye->lock);

    if (phye->init_count == 0 && phye->ops->init)
    {
        if ((err = phye->ops->init(phye)))
        {
            goto _out_lock;
        }
    }
    ++phye->init_count;

_out_lock:
    rt_spin_unlock(&phye->lock);

    return err;
}

rt_err_t rt_phye_exit(struct rt_phye *phye)
{
    rt_err_t err;

    if (!phye)
    {
        return RT_EOK;
    }

    err = RT_EOK;

    rt_spin_lock(&phye->lock);

    if (phye->init_count == 1 && phye->ops->exit)
    {
        if ((err = phye->ops->exit(phye)))
        {
            goto _out_lock;
        }
    }
    if (phye->init_count)
    {
        --phye->init_count;
    }

_out_lock:
    rt_spin_unlock(&phye->lock);

    return err;
}

rt_err_t rt_phye_reset(struct rt_phye *phye)
{
    rt_err_t err;

    if (!phye)
    {
        return RT_EOK;
    }

    err = RT_EOK;

    rt_spin_lock(&phye->lock);

    if (phye->ops->reset)
    {
        err = phye->ops->reset(phye);
    }

    rt_spin_unlock(&phye->lock);

    return err;
}

rt_err_t rt_phye_power_on(struct rt_phye *phye)
{
    rt_err_t err;

    if (!phye)
    {
        return RT_EOK;
    }

    err = RT_EOK;

    rt_spin_lock(&phye->lock);

    if (phye->power_count == 0 && phye->ops->power_on)
    {
        if ((err = phye->ops->power_on(phye)))
        {
            goto _out_lock;
        }
    }
    ++phye->power_count;

_out_lock:
    rt_spin_unlock(&phye->lock);

    return err;
}

rt_err_t rt_phye_power_off(struct rt_phye *phye)
{
    rt_err_t err;

    if (!phye)
    {
        return RT_EOK;
    }

    err = RT_EOK;

    rt_spin_lock(&phye->lock);

    if (phye->power_count == 1 && phye->ops->power_off)
    {
        if ((err = phye->ops->power_off(phye)))
        {
            goto _out_lock;
        }
    }
    if (phye->power_count)
    {
        --phye->power_count;
    }

_out_lock:
    rt_spin_unlock(&phye->lock);

    return err;
}

rt_err_t rt_phye_set_mode(struct rt_phye *phye, enum rt_phye_mode mode, int submode)
{
    rt_err_t err;

    if (!phye)
    {
        return RT_EOK;
    }

    if (mode < RT_PHYE_MODE_MAX &&
        (submode == RT_PHYE_MODE_INVALID || submode >= RT_PHYE_MODE_MAX))
    {
        err = RT_EOK;

        rt_spin_lock(&phye->lock);

        if (phye->ops->set_mode)
        {
            err = phye->ops->set_mode(phye, mode, submode);
        }

        rt_spin_unlock(&phye->lock);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

static struct rt_phye *ofw_phye_get_by_index(struct rt_ofw_node *np, int index)
{
    struct rt_phye *phye = RT_NULL;
#ifdef RT_USING_OFW
    rt_err_t err;
    struct rt_ofw_node *phye_np;
    struct rt_ofw_cell_args phye_args;

    if (!rt_ofw_parse_phandle_cells(np, "phys", "#phy-cells", index, &phye_args))
    {
        phye_np = phye_args.data;

        if (!rt_ofw_data(phye_np))
        {
            rt_platform_ofw_request(phye_np);
        }

        phye = rt_ofw_data(phye_np);
        rt_ofw_node_put(phye_np);

        if (phye && phye->ops->ofw_parse)
        {
            if ((err = phye->ops->ofw_parse(phye, &phye_args)))
            {
                phye = rt_err_ptr(err);
            }
        }
    }
#endif /* RT_USING_OFW */
    return phye;
}

struct rt_phye *rt_phye_get_by_index(struct rt_device *dev, int index)
{
    struct rt_phye *phye = RT_NULL;

    if (!dev || index < 0)
    {
        return rt_err_ptr(-RT_EINVAL);
    }

    if (dev->ofw_node)
    {
        phye = ofw_phye_get_by_index(dev->ofw_node, index);
    }

    if (!rt_is_err_or_null(phye))
    {
        rt_spin_lock(&phye->lock);
        ++phye->dev->ref_count;
        rt_spin_unlock(&phye->lock);
    }

    return phye;
}

struct rt_phye *rt_phye_get_by_name(struct rt_device *dev, const char *id)
{
    int index;

    if (!dev || !id)
    {
        return rt_err_ptr(-RT_EINVAL);
    }

    index = rt_dm_dev_prop_index_of_string(dev, "phy-names", id);

    if (index >= 0)
    {
        return rt_phye_get_by_index(dev, index);
    }

    return RT_NULL;
}

void rt_phye_put(struct rt_phye *phye)
{
    if (phye)
    {
        rt_spin_lock(&phye->lock);
        --phye->dev->ref_count;
        rt_spin_unlock(&phye->lock);
    }
}
