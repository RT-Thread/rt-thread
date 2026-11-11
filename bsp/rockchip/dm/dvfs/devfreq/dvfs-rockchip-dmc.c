/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "dvfs.rockchip.dmc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct rockchip_dmcfreq
{
    struct rt_dvfs_devfreq devfreq;
    struct rt_platform_device *pdev;
};

static const struct rt_ofw_node_id dfi_compat_ids[] =
{
    { .compatible = "rockchip,rk3568-dfi" },
    { .compatible = "rockchip,rk3562-dfi" },
    { .compatible = "rockchip,px30-dfi" },
    { /* sentinel */ }
};

static rt_err_t rockchip_dmc_bind_dfi_event(struct rockchip_dmcfreq *dmc,
        struct rt_device *dev)
{
    struct rt_ofw_node *np = dev->ofw_node, *ev_np;

    for (int i = 0; ; ++i)
    {
        if (!(ev_np = rt_ofw_parse_phandle(np, "devfreq-events", i)))
        {
            break;
        }

        if (rt_ofw_node_match(ev_np, dfi_compat_ids))
        {
            dmc->devfreq.ev = rt_ofw_data(ev_np);
        }

        rt_ofw_node_put(ev_np);

        if (dmc->devfreq.ev)
        {
            break;
        }
    }

    if (!dmc->devfreq.ev)
    {
        LOG_W("%s: no DFI devfreq-event", rt_dm_dev_get_name(dev));
        return -RT_ENOENT;
    }

    return RT_EOK;
}

static rt_err_t rockchip_dmc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rockchip_dmcfreq *dmc;
    struct rt_dvfs_scaling *scaling;

    if (!(dmc = rt_calloc(1, sizeof(*dmc))))
    {
        return -RT_ENOMEM;
    }

    dmc->pdev = pdev;
    scaling = rt_dvfs_devfreq_to_scaling(&dmc->devfreq);

    rt_dm_dev_set_name_auto(dev, "dmc");

    if ((err = rt_device_register(dev, rt_dm_dev_get_name(dev), RT_DEVICE_FLAG_DEACTIVATE)))
    {
        rt_free(dmc);
        return err;
    }

    scaling->dev = dev;
    scaling->ops = &rt_dvfs_devfreq_ops;
    scaling->clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(scaling->clk))
    {
        LOG_W("%s: no dmc clk, event test only", rt_dm_dev_get_name(dev));
        scaling->clk = RT_NULL;
    }

    scaling->supply = rt_regulator_get(dev, "center");
    if (rt_is_err(scaling->supply))
    {
        scaling->supply = RT_NULL;
    }

    if ((err = rockchip_dmc_bind_dfi_event(dmc, dev)))
    {
        goto _fail;
    }

    if ((err = rt_dvfs_devfreq_register(&dmc->devfreq)))
    {
        goto _fail;
    }

    if ((err = rt_dvfs_scaling_set_governor(scaling, RT_DVFS_GOVERNOR_TYPE_ONDEMAND)))
    {
        LOG_W("%s: ondemand failed: %s", rt_dm_dev_get_name(dev), rt_strerror(err));
    }

    pdev->priv = dmc;

    LOG_I("%s: event-only devfreq ready, freq %lu-%lu Hz",
          rt_dm_dev_get_name(dev), scaling->min_freq, scaling->max_freq);

    return RT_EOK;

_fail:
    if (scaling->clk)
    {
        rt_clk_put(scaling->clk);
    }
    if (scaling->supply)
    {
        rt_regulator_put(scaling->supply);
    }
    rt_device_unregister(dev);
    rt_free(dmc);
    return err;
}

static rt_err_t rockchip_dmc_remove(struct rt_platform_device *pdev)
{
    struct rockchip_dmcfreq *dmc = pdev->priv;

    if (!dmc)
    {
        return RT_EOK;
    }

    rt_dvfs_devfreq_unregister(&dmc->devfreq);

    struct rt_dvfs_scaling *scaling = rt_dvfs_devfreq_to_scaling(&dmc->devfreq);
    if (scaling->clk)
    {
        rt_clk_put(scaling->clk);
    }
    if (scaling->supply)
    {
        rt_regulator_put(scaling->supply);
    }

    rt_device_unregister(&pdev->parent);
    rt_free(dmc);
    pdev->priv = RT_NULL;

    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_dmc_ofw_ids[] =
{
    { .compatible = "rockchip,rk3568-dmc" },
    { .compatible = "rockchip,rk3562-dmc" },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_dmc_driver =
{
    .name = "rockchip-dmc",
    .ids = rockchip_dmc_ofw_ids,
    .probe = rockchip_dmc_probe,
    .remove = rockchip_dmc_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_dmc_driver);
