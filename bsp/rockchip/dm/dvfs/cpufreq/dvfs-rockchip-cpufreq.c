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

#define DBG_TAG "dvfs.cpufreq"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <opp-select.h>

struct cpufreq_cluster
{
    rt_list_t list;
    struct rt_dvfs_cpufreq cpufreq;
    struct opp_info opp_info;
    struct rt_platform_device *pdev;
#ifdef RT_THERMAL_COOL_DVFS
    struct rt_platform_device *cool_pdev;
#endif
    RT_BITMAP_DECLARE(cpus_map, RT_CPUS_NR);
};

static rt_list_t cluster_list = RT_LIST_OBJECT_INIT(cluster_list);

static struct cpufreq_cluster *cluster_by_opp(struct rt_ofw_node *opp_np)
{
    struct cpufreq_cluster *cluster;

    if (!opp_np)
    {
        return RT_NULL;
    }

    rt_list_for_each_entry(cluster, &cluster_list, list)
    {
        if (cluster->opp_info.opp_np == opp_np)
        {
            return cluster;
        }
    }

    return RT_NULL;
}

static rt_bool_t cpu_shares_opp(struct rt_ofw_node *cpu_np,
        struct rt_ofw_node *opp_np)
{
    struct rt_ofw_node *cpu_opp;

    cpu_opp = rt_ofw_parse_phandle(cpu_np, "operating-points-v2", 0);
    if (!cpu_opp)
    {
        return RT_FALSE;
    }

    if (cpu_opp == opp_np)
    {
        rt_ofw_node_put(cpu_opp);
        return RT_TRUE;
    }

    rt_ofw_node_put(cpu_opp);
    return RT_FALSE;
}

static rt_err_t scaling_set_opp(struct rt_dvfs_scaling *scaling,
        struct rt_dvfs_opp *opp)
{
    struct cpufreq_cluster *cluster = scaling->priv;

    return cpufreq_set_opp(scaling, opp, &cluster->opp_info);
}

static rt_err_t cpufreq_parse_opp(struct rt_dvfs_scaling *dvfs,
        struct rt_dvfs_opp *opp, void *fw_np)
{
    struct cpufreq_cluster *cluster = dvfs->priv;

    return opp_parse(dvfs, opp, (struct rt_ofw_node *)fw_np, &cluster->opp_info);
}

static struct rt_dvfs_scaling_ops cpufreq_ops =
{
    .set_opp = scaling_set_opp,
    .parse_opp = cpufreq_parse_opp,
};

#ifdef RT_THERMAL_COOL_DVFS
static rt_err_t cluster_cool_register(struct cpufreq_cluster *cluster,
        struct rt_ofw_node *cpu_np, struct rt_dvfs_scaling *scaling)
{
    rt_err_t err;
    struct rt_platform_device *cool;

    if (!rt_ofw_prop_read_bool(cpu_np, "#cooling-cells"))
    {
        return RT_EOK;
    }

    if (!(cool = rt_platform_device_alloc("dvfs-cool")))
    {
        return -RT_ENOMEM;
    }

    cool->parent.ofw_node = cpu_np;
    rt_ofw_node_get(cpu_np);
    cool->priv = scaling;

    if ((err = rt_platform_device_register(cool)))
    {
        rt_ofw_node_put(cpu_np);
        rt_free(cool);
        return err;
    }

    cluster->cool_pdev = cool;

    return RT_EOK;
}

static void cluster_cool_unregister(struct cpufreq_cluster *cluster)
{
    struct rt_platform_device *cool = cluster->cool_pdev;

    if (!cool)
    {
        return;
    }

    rt_bus_remove_device(&cool->parent);
    rt_ofw_node_put(cool->parent.ofw_node);
    rt_free(cool);
    cluster->cool_pdev = RT_NULL;
}
#endif /* RT_THERMAL_COOL_DVFS */

static void cluster_destroy(struct cpufreq_cluster *cluster,
        struct rt_device *dev, struct rt_dvfs_scaling *scaling)
{
#ifdef RT_THERMAL_COOL_DVFS
    cluster_cool_unregister(cluster);
#endif

    if (scaling)
    {
        rt_dvfs_cpufreq_unregister(&cluster->cpufreq);
    }

    if (dev)
    {
        opp_table_uninit(dev, &cluster->opp_info);
        rt_device_unregister(dev);
        rt_ofw_node_put(dev->ofw_node);
    }

    if (cluster->pdev)
    {
        rt_free(cluster->pdev);
        cluster->pdev = RT_NULL;
    }
}

static rt_err_t cluster_init(struct cpufreq_cluster *cluster,
        struct rt_ofw_node *cpu_np, struct rt_ofw_node *opp_np)
{
    rt_err_t err;
    const char *reg_name;
    struct rt_device *dev;
    struct rt_dvfs_scaling *scaling;
    struct rt_platform_device *pdev;

    if (!(reg_name = regulator_name(cpu_np)))
    {
        LOG_W("%s: no cpu supply property, skip cluster",
              rt_ofw_node_full_name(cpu_np));
        return -RT_ENOENT;
    }

    if (!(pdev = rt_platform_device_alloc("cpufreq")))
    {
        return -RT_ENOMEM;
    }

    dev = &pdev->parent;
    dev->ofw_node = cpu_np;
    rt_ofw_node_get(cpu_np);

    rt_dm_dev_set_name_auto(dev, "cpufreq");

    if ((err = rt_device_register(dev, rt_dm_dev_get_name(dev), RT_DEVICE_FLAG_DEACTIVATE)))
    {
        rt_ofw_node_put(cpu_np);
        rt_free(pdev);
        return err;
    }

    scaling = rt_dvfs_cpufreq_to_scaling(&cluster->cpufreq);
    scaling->dev = dev;
    scaling->ops = &cpufreq_ops;
    scaling->priv = cluster;

    if ((err = opp_table_init(dev, &cluster->opp_info, reg_name)))
    {
        goto _fail;
    }

    if (cluster->opp_info.opp_np != opp_np)
    {
        rt_ofw_node_put(cluster->opp_info.opp_np);
        cluster->opp_info.opp_np = opp_np;
        rt_ofw_node_get(opp_np);
    }

    scaling->clk = cluster->opp_info.clk;
    scaling->supply = cluster->opp_info.supply;

    if (!scaling->transition_latency)
    {
        scaling->transition_latency = 1000000;
    }

    if ((err = rt_dvfs_cpufreq_register(&cluster->cpufreq)))
    {
        goto _fail;
    }

    if ((err = opp_table_adjust(dev, &cluster->opp_info, scaling)))
    {
        goto _fail_scaling;
    }

    if ((err = cpufreq_sync_hw_state(scaling)))
    {
        LOG_W("%s: sync hw state failed: %s, cpufreq may retry regulator",
              rt_dm_dev_get_name(dev), rt_strerror(err));
    }

    if ((err = rt_dvfs_scaling_set_governor(scaling, RT_DVFS_GOVERNOR_TYPE_ONDEMAND)))
    {
        rt_dvfs_scaling_set_governor(scaling, RT_DVFS_GOVERNOR_TYPE_PERFORMANCE);
    }
#ifdef RT_THERMAL_COOL_DVFS
    if ((err = cluster_cool_register(cluster, cpu_np, scaling)))
    {
        LOG_W("%s: dvfs-cool register failed: %s",
              rt_dm_dev_get_name(dev), rt_strerror(err));
    }
#endif

    cluster->pdev = pdev;
    rt_list_insert_before(&cluster_list, &cluster->list);

    LOG_D("CPUFreq cluster %s %lu-%lu Hz on %s",
          rt_ofw_node_full_name(cpu_np),
          scaling->min_freq, scaling->max_freq,
          rt_dm_dev_get_name(dev));

    return RT_EOK;

_fail_scaling:
    rt_dvfs_cpufreq_unregister(&cluster->cpufreq);
_fail:
    cluster_destroy(cluster, dev, RT_NULL);
    return err;
}

static int rockchip_dvfs_cpufreq_init(void)
{
    rt_err_t err;
    int cpu_id = 0, registered = 0;
    struct rt_ofw_node *cpu_np = RT_NULL;
    struct cpufreq_cluster *cluster;
    struct rt_ofw_node *opp_np;

    rt_ofw_foreach_cpu_node(cpu_np)
    {
        int share_id = 0;
        struct rt_ofw_node *share_np = RT_NULL;

        if (!(opp_np = rt_ofw_parse_phandle(cpu_np, "operating-points-v2", 0)))
        {
            ++cpu_id;
            continue;
        }

        if (cluster_by_opp(opp_np))
        {
            rt_ofw_node_put(opp_np);
            ++cpu_id;
            continue;
        }

        if (!(cluster = rt_calloc(1, sizeof(*cluster))))
        {
            rt_ofw_node_put(opp_np);
            return -RT_ENOMEM;
        }

        cluster->cpufreq.master_cpu = cpu_id;
        rt_bitmap_set_bit(cluster->cpus_map, cpu_id);

        rt_ofw_foreach_cpu_node(share_np)
        {
            if (cpu_shares_opp(share_np, opp_np))
            {
                rt_bitmap_set_bit(cluster->cpus_map, share_id);
            }
            ++share_id;
        }

        rt_memcpy(cluster->cpufreq.cpus_map, cluster->cpus_map,
                sizeof(cluster->cpus_map));

        err = cluster_init(cluster, cpu_np, opp_np);
        rt_ofw_node_put(opp_np);

        if (err)
        {
            LOG_W("CPUFreq cluster %s init failed: %s",
                  rt_ofw_node_full_name(cpu_np), rt_strerror(err));
            rt_free(cluster);
        }
        else
        {
            ++registered;
        }

        ++cpu_id;
    }

    if (!registered)
    {
        return (int)-RT_ENOENT;
    }

    return (int)RT_EOK;
}
INIT_APP_EXPORT(rockchip_dvfs_cpufreq_init);
