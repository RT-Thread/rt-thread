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
#include <rtdevice.h>

#define DBG_TAG "thermal.cool.dvfs"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct dvfs_cool
{
    struct rt_thermal_cooling_device parent;

    struct rt_dvfs_scaling *dvfs;
};

#define raw_to_dvfs_cool(raw) rt_container_of(raw, struct dvfs_cool, parent)

static rt_err_t dvfs_cool_get_max_level(struct rt_thermal_cooling_device *cdev,
        rt_ubase_t *out_level)
{
    struct dvfs_cool *dvfs_cool = raw_to_dvfs_cool(cdev);
    struct rt_dvfs_scaling *dvfs = dvfs_cool->dvfs;

    rt_dvfs_scaling_enter(dvfs);

    if (dvfs->opp_table->opp_nodes.next)
    {
        *out_level = rt_list_len(&dvfs->opp_table->opp_nodes);

        if (*out_level > 0)
        {
            (*out_level)--;
        }
    }
    else
    {
        *out_level = 0;
    }

    rt_dvfs_scaling_leave(dvfs);

    return RT_EOK;
}

static rt_err_t dvfs_cool_get_cur_level(struct rt_thermal_cooling_device *cdev,
        rt_ubase_t *out_level)
{
    struct rt_dvfs_opp *opp;
    struct dvfs_cool *dvfs_cool = raw_to_dvfs_cool(cdev);
    struct rt_dvfs_scaling *dvfs = dvfs_cool->dvfs;

    rt_dvfs_scaling_enter(dvfs);

    *out_level = 0;
    rt_list_for_each_entry(opp, &dvfs->opp_table->opp_nodes, list)
    {
        if (opp == dvfs->opp_table->current_opp)
        {
            break;
        }

        (*out_level)++;
    }

    rt_dvfs_scaling_leave(dvfs);

    return RT_EOK;
}

static rt_err_t dvfs_cool_set_cur_level(struct rt_thermal_cooling_device *cdev,
        rt_ubase_t level)
{
    struct rt_dvfs_opp *opp, *target_opp = RT_NULL;
    struct dvfs_cool *dvfs_cool = raw_to_dvfs_cool(cdev);
    struct rt_dvfs_scaling *dvfs = dvfs_cool->dvfs;

    rt_dvfs_scaling_enter(dvfs);

    rt_list_for_each_entry(opp, &dvfs->opp_table->opp_nodes, list)
    {
        if (!level)
        {
            target_opp = opp;
            break;
        }

        --level;
    }

    rt_dvfs_scaling_leave(dvfs);

    if (target_opp)
    {
        return rt_dvfs_scaling_apply_opp(dvfs, target_opp);
    }

    return -RT_EINVAL;
}

const static struct rt_thermal_cooling_device_ops dvfs_cool_ops =
{
    .get_max_level = dvfs_cool_get_max_level,
    .get_cur_level = dvfs_cool_get_cur_level,
    .set_cur_level = dvfs_cool_set_cur_level,
};

static rt_err_t dvfs_cool_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct dvfs_cool *dvfs_cool;
    struct rt_device *dev = &pdev->parent;

    if (!pdev->priv)
    {
        return -RT_EINVAL;
    }

    if (!(dvfs_cool = rt_calloc(1, sizeof(*dvfs_cool))))
    {
        return -RT_ENOMEM;
    }
    dvfs_cool->dvfs = pdev->priv;

    rt_dm_dev_set_name(&dvfs_cool->parent.parent, "%s-cool",
            rt_dm_dev_get_name(dvfs_cool->dvfs->dev));
    dvfs_cool->parent.parent.ofw_node = dev->ofw_node;
    dvfs_cool->parent.ops = &dvfs_cool_ops;

    if ((err = rt_thermal_cooling_device_register(&dvfs_cool->parent)))
    {
        goto _fail;
    }

    dev->user_data = dvfs_cool;

    return RT_EOK;

_fail:
    rt_free(dvfs_cool);

    return err;
}

static rt_err_t dvfs_cool_remove(struct rt_platform_device *pdev)
{
    struct dvfs_cool *dvfs_cool = pdev->parent.user_data;

    rt_thermal_cooling_device_unregister(&dvfs_cool->parent);
    rt_free(dvfs_cool);

    return RT_EOK;
}

static struct rt_platform_driver dvfs_cool_driver =
{
    .name = "dvfs-cool",

    .probe = dvfs_cool_probe,
    .remove = dvfs_cool_remove,
};
RT_PLATFORM_DRIVER_EXPORT(dvfs_cool_driver);
