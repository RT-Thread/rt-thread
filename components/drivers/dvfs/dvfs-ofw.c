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

#define DBG_TAG "dvfs.ofw"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_err_t ofw_dvfs_setup(struct rt_platform_device *pdev,
        struct rt_dvfs_devfreq *devfreq, rt_bool_t is_cpu)
{
    struct rt_device *dev = &pdev->parent;
    struct rt_dvfs_scaling *scaling = rt_dvfs_devfreq_to_scaling(devfreq);
    rt_err_t err;

    if (!devfreq)
    {
        return -RT_EINVAL;
    }

    scaling->dev = dev;
    scaling->ops = &rt_dvfs_devfreq_ops;

    if (!scaling->clk)
    {
        scaling->clk = rt_clk_get_by_index(dev, 0);
        if (rt_is_err(scaling->clk))
        {
            LOG_E("Get clock failed");
            return rt_ptr_err(scaling->clk);
        }
    }

    if (!scaling->supply)
    {
        if (is_cpu)
        {
            scaling->supply = rt_regulator_get(dev, "cpu");
        }
        else
        {
            scaling->supply = rt_regulator_get(dev, "dev");
            if (rt_is_err(scaling->supply))
            {
                scaling->supply = rt_regulator_get(dev, "mem");
            }
        }

        if (rt_is_err(scaling->supply))
        {
            scaling->supply = RT_NULL;
        }
    }

    if (!scaling->transition_latency)
    {
        scaling->transition_latency = 1000000;
    }

    if (!scaling->retry_delay)
    {
        scaling->retry_delay = 100000;
    }

#ifdef RT_USING_DVFS_EVENT
    if (!is_cpu && !devfreq->ev && dev->ofw_node)
    {
        devfreq->ev = rt_dvfs_event_get(dev, "devfreq-event", 0);
        if (rt_is_err_or_null(devfreq->ev))
        {
            devfreq->ev = RT_NULL;
            LOG_D("%s: no devfreq-event", rt_dm_dev_get_name(dev));
        }
    }
#endif

    err = rt_dvfs_devfreq_register(devfreq);
    if (err)
    {
        LOG_E("Register devfreq failed: %s", rt_strerror(err));
        goto fail;
    }

    err = rt_dvfs_scaling_set_governor(scaling, RT_DVFS_GOVERNOR_TYPE_ONDEMAND);
    if (err)
    {
        LOG_W("Set ondemand governor failed: %s", rt_strerror(err));
        err = rt_dvfs_scaling_set_governor(scaling, RT_DVFS_GOVERNOR_TYPE_PERFORMANCE);
    }

    LOG_D("Devfreq registered for %s, freq range: %lu-%lu Hz",
          rt_dm_dev_get_name(dev), scaling->min_freq, scaling->max_freq);

    return RT_EOK;

fail:
    if (scaling->clk)
    {
        rt_clk_put(scaling->clk);
        scaling->clk = RT_NULL;
    }
    if (scaling->supply)
    {
        rt_regulator_put(scaling->supply);
        scaling->supply = RT_NULL;
    }
    return err;
}

static rt_err_t ofw_cpufreq_probe(struct rt_platform_device *pdev)
{
    struct rt_dvfs_cpufreq *cpufreq = pdev->priv;

    if (!cpufreq)
    {
        LOG_E("No cpufreq data");
        return -RT_EINVAL;
    }

    return ofw_dvfs_setup(pdev, rt_dvfs_cpufreq_to_devfreq(cpufreq), RT_TRUE);
}

static rt_err_t ofw_cpufreq_remove(struct rt_platform_device *pdev)
{
    struct rt_dvfs_cpufreq *cpufreq = pdev->priv;

    if (cpufreq)
    {
        rt_dvfs_cpufreq_unregister(cpufreq);
        pdev->priv = RT_NULL;
    }

    return RT_EOK;
}

static rt_err_t ofw_devfreq_probe(struct rt_platform_device *pdev)
{
    struct rt_dvfs_devfreq *devfreq = pdev->priv;

    if (!devfreq)
    {
        LOG_E("No devfreq data");
        return -RT_EINVAL;
    }

    return ofw_dvfs_setup(pdev, devfreq, RT_FALSE);
}

static rt_err_t ofw_devfreq_remove(struct rt_platform_device *pdev)
{
    struct rt_dvfs_devfreq *devfreq = pdev->priv;

    if (devfreq)
    {
        rt_dvfs_devfreq_unregister(devfreq);
        pdev->priv = RT_NULL;
    }

    return RT_EOK;
}

static struct rt_platform_driver ofw_cpufreq_driver =
{
    .name = "ofw-cpufreq",
    .probe = ofw_cpufreq_probe,
    .remove = ofw_cpufreq_remove,
};
RT_PLATFORM_DRIVER_EXPORT(ofw_cpufreq_driver);

static struct rt_platform_driver ofw_devfreq_driver =
{
    .name = "ofw-devfreq",
    .probe = ofw_devfreq_probe,
    .remove = ofw_devfreq_remove,
};
RT_PLATFORM_DRIVER_EXPORT(ofw_devfreq_driver);
