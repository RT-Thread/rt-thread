/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <drivers/clk.h>
#include <drivers/dvfs.h>
#include <drivers/regulator.h>

#define DBG_TAG "dvfs.spacemit"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SPACEMIT_PRODUCT_ID_M1          0x36070000U
#define SPACEMIT_K1_MAX_FREQ            1600000000UL
#define SPACEMIT_M1_MAX_FREQ            1800000000UL
#define SPACEMIT_TURBO0_FREQ            1600000000UL
#define SPACEMIT_TURBO1_FREQ            3200000000UL
#define SPACEMIT_STABLE_FREQ            1200000000UL
#define SPACEMIT_FREQ_TOLERANCE         1000000UL
#define SPACEMIT_STABLE_TOLERANCE       50000000UL
#define SPACEMIT_DEFAULT_CCI_FREQ       614000000UL
#define SPACEMIT_DEFAULT_LATENCY_NS     200000U
#define SPACEMIT_DEFAULT_RETRY_NS       100000U
#define SPACEMIT_DRO_TABLE0_MAX         135U
#define SPACEMIT_DRO_TABLE1_MAX         142U

struct spacemit_cpufreq_opp
{
    rt_ubase_t cluster_hz[2];
    rt_ubase_t tcm_hz;
    rt_ubase_t ace_hz;
};

struct spacemit_cpufreq
{
    struct rt_dvfs_cpufreq cpufreq;
    struct rt_platform_device *pdev;
    struct rt_ofw_node *cpu_np;
    struct rt_ofw_node *opp_np;

    struct rt_regulator *supply;
    struct rt_clk *cluster[2];
    struct rt_clk *ace[2];
    struct rt_clk *tcm;
    struct rt_clk *cci;
    struct rt_clk *pll3;
    struct rt_clk *hi[2];

    struct rt_mutex lock;
    rt_bool_t lock_ready;
    rt_bool_t dev_registered;
    rt_bool_t is_m1;
    rt_uint32_t silicon_id;
    rt_uint32_t opp_index;
};

static struct spacemit_cpufreq *spacemit_cpufreq_data;

static rt_ubase_t rate_delta(rt_ubase_t a, rt_ubase_t b)
{
    return a > b ? a - b : b - a;
}

static rt_bool_t rate_matches(rt_ubase_t actual, rt_ubase_t target)
{
    return rate_delta(actual, target) <= SPACEMIT_FREQ_TOLERANCE;
}

static rt_ubase_t spacemit_mux_hw_rate(struct rt_clk *clk)
{
    rt_uint8_t parent_index;
    struct rt_clk_cell *parent_cell;

    parent_index = rt_clk_cell_get_parent_index(clk->cell);
    if (parent_index == RT_UINT8_MAX)
    {
        return 0;
    }

    parent_cell = rt_clk_cell_get_parent_by_index(clk->cell, parent_index);

    return parent_cell ? rt_clk_cell_get_rate(parent_cell) : 0;
}

static rt_err_t spacemit_get_clk(struct rt_ofw_node *np, const char *name,
        struct rt_clk **out_clk)
{
    struct rt_clk *clk;

    clk = rt_ofw_get_clk_by_name(np, name);

    if (rt_is_err_or_null(clk))
    {
        rt_err_t err = clk ? rt_ptr_err(clk) : -RT_ENOENT;

        LOG_E("%s: get clock %s failed: %s",
                rt_ofw_node_full_name(np), name, rt_strerror(err));
        return err;
    }

    *out_clk = clk;

    return RT_EOK;
}

static rt_err_t spacemit_set_rate(struct rt_clk *clk, rt_ubase_t target,
        const char *name, rt_ubase_t tolerance)
{
    rt_err_t err;
    rt_ubase_t actual;

    if ((err = rt_clk_set_rate(clk, target)))
    {
        LOG_E("set %s to %lu Hz failed: %s", name, target, rt_strerror(err));
        return err;
    }

    actual = rt_clk_get_rate(clk);
    if (rate_delta(actual, target) > tolerance)
    {
        LOG_E("%s rate mismatch: requested %lu Hz, got %lu Hz",
                name, target, actual);
        return -RT_EIO;
    }

    return RT_EOK;
}

static rt_err_t spacemit_set_mux_rate(struct rt_clk *clk, rt_ubase_t target,
        const char *name, rt_ubase_t tolerance)
{
    rt_err_t err;
    rt_ubase_t actual;

    if ((err = rt_clk_set_rate(clk, target)))
    {
        LOG_E("set %s to %lu Hz failed: %s", name, target, rt_strerror(err));
        return err;
    }

    actual = spacemit_mux_hw_rate(clk);
    if (!actual || rate_delta(actual, target) > tolerance)
    {
        LOG_E("%s hardware rate mismatch: requested %lu Hz, got %lu Hz",
                name, target, actual);
        return -RT_EIO;
    }

    return RT_EOK;
}

static rt_err_t spacemit_set_binary_div(struct rt_clk *clk, const char *name)
{
    struct rt_clk *parent = rt_clk_get_parent(clk);
    rt_ubase_t parent_rate;

    if (!parent || !(parent_rate = rt_clk_get_rate(parent)))
    {
        LOG_E("%s has no valid parent rate", name);
        return -RT_EIO;
    }

    return spacemit_set_rate(clk, parent_rate / 2, name,
            SPACEMIT_FREQ_TOLERANCE);
}

static rt_err_t spacemit_set_voltage(struct spacemit_cpufreq *priv,
        rt_ubase_t uvolt)
{
    rt_err_t err = rt_regulator_set_voltage(priv->supply, uvolt, uvolt);

    if (err)
    {
        LOG_E("set CPU voltage to %lu uV failed: %s", uvolt,
                rt_strerror(err));
    }

    return err;
}

static int spacemit_current_voltage(struct rt_dvfs_scaling *scaling,
        struct spacemit_cpufreq *priv)
{
    int uvolt = rt_regulator_get_voltage(priv->supply);

    if (uvolt <= 0 && scaling->opp_table && scaling->opp_table->current_opp)
    {
        uvolt = (int)scaling->opp_table->current_opp->uvolt;
    }

    return uvolt;
}

static rt_err_t spacemit_prepare_dependent_clks(struct spacemit_cpufreq *priv)
{
    rt_err_t err;

    if ((err = spacemit_set_binary_div(priv->ace[0], "ace0")))
    {
        return err;
    }
    if ((err = spacemit_set_binary_div(priv->ace[1], "ace1")))
    {
        return err;
    }

    return spacemit_set_binary_div(priv->tcm, "tcm");
}

static rt_err_t spacemit_finish_dependent_clks(struct spacemit_cpufreq *priv,
        const struct spacemit_cpufreq_opp *opp_data)
{
    rt_err_t err;

    if ((err = spacemit_set_rate(priv->tcm, opp_data->tcm_hz, "tcm",
            SPACEMIT_FREQ_TOLERANCE)))
    {
        return err;
    }
    if ((err = spacemit_set_rate(priv->ace[0], opp_data->ace_hz, "ace0",
            SPACEMIT_FREQ_TOLERANCE)))
    {
        return err;
    }

    return spacemit_set_rate(priv->ace[1], opp_data->ace_hz, "ace1",
            SPACEMIT_FREQ_TOLERANCE);
}

static rt_err_t spacemit_prepare_turbo_clks(struct spacemit_cpufreq *priv,
        rt_ubase_t old_freq, rt_ubase_t new_freq)
{
    rt_err_t err;

    if (new_freq < SPACEMIT_TURBO0_FREQ)
    {
        return RT_EOK;
    }

    if (old_freq >= SPACEMIT_TURBO0_FREQ)
    {
        if ((err = spacemit_set_mux_rate(priv->cluster[0],
                SPACEMIT_STABLE_FREQ, "cls0-stable",
                SPACEMIT_STABLE_TOLERANCE)))
        {
            return err;
        }
        if ((err = spacemit_set_mux_rate(priv->cluster[1],
                SPACEMIT_STABLE_FREQ, "cls1-stable",
                SPACEMIT_STABLE_TOLERANCE)))
        {
            return err;
        }
    }

    if (new_freq == SPACEMIT_TURBO0_FREQ)
    {
        if ((err = spacemit_set_rate(priv->pll3, SPACEMIT_TURBO1_FREQ,
                "pll3", SPACEMIT_FREQ_TOLERANCE)))
        {
            return err;
        }
    }
    else
    {
        if ((err = spacemit_set_rate(priv->pll3, new_freq, "pll3",
                SPACEMIT_FREQ_TOLERANCE)))
        {
            return err;
        }
    }

    if ((err = spacemit_set_mux_rate(priv->hi[0], new_freq, "c0hi",
            SPACEMIT_FREQ_TOLERANCE)))
    {
        return err;
    }

    return spacemit_set_mux_rate(priv->hi[1], new_freq, "c1hi",
            SPACEMIT_FREQ_TOLERANCE);
}

static rt_err_t spacemit_cpufreq_set_opp(struct rt_dvfs_scaling *scaling,
        struct rt_dvfs_opp *opp)
{
    rt_err_t err;
    int old_uvolt;
    rt_bool_t voltage_raised = RT_FALSE;
    rt_ubase_t old_rate[2], old_freq, new_freq;
    struct spacemit_cpufreq *priv = scaling->priv;
    struct spacemit_cpufreq_opp *opp_data = opp->priv;

    if (!priv || !opp_data)
    {
        return -RT_EINVAL;
    }

    if ((err = rt_mutex_take(&priv->lock, RT_WAITING_FOREVER)))
    {
        return err;
    }

    old_rate[0] = spacemit_mux_hw_rate(priv->cluster[0]);
    old_rate[1] = spacemit_mux_hw_rate(priv->cluster[1]);
    old_freq = rt_max(old_rate[0], old_rate[1]);
    new_freq = rt_max(opp_data->cluster_hz[0], opp_data->cluster_hz[1]);
    old_uvolt = spacemit_current_voltage(scaling, priv);

    if ((old_uvolt > 0 && opp->uvolt > (rt_ubase_t)old_uvolt) ||
        (old_uvolt <= 0 && new_freq > old_freq))
    {
        if ((err = spacemit_set_voltage(priv, opp->uvolt)))
        {
            goto _out;
        }

        voltage_raised = RT_TRUE;
        rt_dvfs_ns_sleep(scaling->transition_latency);
    }

    if ((err = spacemit_prepare_dependent_clks(priv)))
    {
        goto _out;
    }
    if ((err = spacemit_prepare_turbo_clks(priv, old_freq, new_freq)))
    {
        goto _out;
    }

    {
        rt_err_t err0, err1;

        err0 = spacemit_set_mux_rate(priv->cluster[0], opp_data->cluster_hz[0],
                "cls0", SPACEMIT_FREQ_TOLERANCE);
        err1 = spacemit_set_mux_rate(priv->cluster[1], opp_data->cluster_hz[1],
                "cls1", SPACEMIT_FREQ_TOLERANCE);
        if (err0 || err1)
        {
            err = err0 ? err0 : err1;
            goto _out;
        }
    }

    if ((err = spacemit_finish_dependent_clks(priv, opp_data)))
    {
        goto _out;
    }

    if (old_uvolt > 0 && opp->uvolt < (rt_ubase_t)old_uvolt &&
        !voltage_raised)
    {
        if ((err = spacemit_set_voltage(priv, opp->uvolt)))
        {
            goto _out;
        }
    }

    scaling->cur_freq = opp->freq;
    scaling->opp_table->current_opp = opp;

    LOG_D("CPU OPP: %lu Hz @ %lu uV (hw %lu/%lu Hz)",
            opp->freq, opp->uvolt,
            spacemit_mux_hw_rate(priv->cluster[0]),
            spacemit_mux_hw_rate(priv->cluster[1]));

_out:
    if (err && voltage_raised)
    {
        LOG_W("CPU clock transition failed after voltage raise; keeping %lu uV",
                opp->uvolt);
    }

    rt_mutex_release(&priv->lock);

    return err;
}

static const struct rt_dvfs_scaling_ops spacemit_cpufreq_ops =
{
    .set_opp = spacemit_cpufreq_set_opp,
};

static int spacemit_select_opp_index(struct spacemit_cpufreq *priv)
{
    rt_uint32_t wafer = 0, product = 0, dro = 0;
    struct rt_ofw_node *root, *cpus;
    int index = 0;

    root = rt_ofw_find_node_by_path("/");
    if (root)
    {
        rt_ofw_prop_read_u32(root, "wafer-id", &wafer);
        rt_ofw_prop_read_u32(root, "product-id", &product);
        rt_ofw_node_put(root);
    }

    priv->silicon_id = (wafer << 16) | (product & 0xffffU);
    priv->is_m1 = priv->silicon_id == SPACEMIT_PRODUCT_ID_M1;

    cpus = rt_ofw_find_node_by_path("/cpus");
    if (cpus)
    {
        rt_ofw_prop_read_u32(cpus, "svt-dro", &dro);
        rt_ofw_node_put(cpus);
    }

    if (priv->is_m1)
    {
        if (dro <= SPACEMIT_DRO_TABLE0_MAX)
        {
            index = 0;
        }
        else if (dro <= SPACEMIT_DRO_TABLE1_MAX)
        {
            index = 1;
        }
        else
        {
            index = 2;
        }
    }

    LOG_D("silicon=0x%08x svt-dro=%u OPP table=%d max=%lu Hz",
            priv->silicon_id, dro, index,
            priv->is_m1 ? SPACEMIT_M1_MAX_FREQ : SPACEMIT_K1_MAX_FREQ);

    return index;
}

static rt_err_t spacemit_parse_opps(struct spacemit_cpufreq *priv,
        struct rt_dvfs_scaling *scaling)
{
    int count = 0;
    struct rt_ofw_node *opp_np;

    rt_ofw_foreach_available_child_node(priv->opp_np, opp_np)
    {
        int hz_nr;
        rt_uint32_t uvolt = 0, latency = 0;
        rt_uint64_t hz[2] = {0}, tcm_hz = 0, ace_hz = 0;
        struct rt_dvfs_opp *opp;
        struct spacemit_cpufreq_opp *opp_data;

        hz_nr = rt_ofw_prop_read_u64_array_index(opp_np, "opp-hz", 0,
                RT_ARRAY_SIZE(hz), hz);
        if (hz_nr < 1 || rt_ofw_prop_read_u32(opp_np, "opp-microvolt", &uvolt))
        {
            LOG_W("skip invalid OPP %s", rt_ofw_node_full_name(opp_np));
            continue;
        }

        if (hz_nr < 2)
        {
            hz[1] = hz[0];
        }
        if (rt_ofw_prop_read_u64(opp_np, "tcm-hz", &tcm_hz))
        {
            tcm_hz = hz[0] / 2;
        }
        if (rt_ofw_prop_read_u64(opp_np, "ace-hz", &ace_hz))
        {
            ace_hz = hz[0] / 2;
        }

        if (!(opp_data = rt_calloc(1, sizeof(*opp_data))))
        {
            return -RT_ENOMEM;
        }

        opp_data->cluster_hz[0] = (rt_ubase_t)hz[0];
        opp_data->cluster_hz[1] = (rt_ubase_t)hz[1];
        opp_data->tcm_hz = (rt_ubase_t)tcm_hz;
        opp_data->ace_hz = (rt_ubase_t)ace_hz;

        opp = rt_dvfs_scaling_add_opp(scaling, (rt_ubase_t)hz[0], uvolt);
        if (!opp)
        {
            rt_free(opp_data);
            return -RT_ENOMEM;
        }

        opp->priv = opp_data;
        if (!priv->is_m1 && opp->freq > SPACEMIT_K1_MAX_FREQ)
        {
            opp->available = RT_FALSE;
        }

        if (!rt_ofw_prop_read_u32(opp_np, "clock-latency-ns", &latency) &&
            latency > scaling->transition_latency)
        {
            scaling->transition_latency = latency;
        }

        ++count;
    }

    if (!count)
    {
        return -RT_ENOENT;
    }

    scaling->opp_table->share = RT_TRUE;
    scaling->opp_table->priv = priv->opp_np;

    return RT_EOK;
}

static void spacemit_free_opps(struct rt_dvfs_scaling *scaling)
{
    struct rt_dvfs_opp *opp;

    if (!scaling->opp_table)
    {
        return;
    }

    rt_list_for_each_entry(opp, &scaling->opp_table->opp_nodes, list)
    {
        rt_free(opp->priv);
        opp->priv = RT_NULL;
    }

    rt_dvfs_scaling_remove_opp_all(scaling);
    rt_free(scaling->opp_table);
    scaling->opp_table = RT_NULL;
}

static rt_err_t spacemit_get_resources(struct spacemit_cpufreq *priv)
{
    rt_err_t err;
    struct rt_device *dev = &priv->pdev->parent;

    if ((err = spacemit_get_clk(priv->cpu_np, "cls0", &priv->cluster[0])) ||
        (err = spacemit_get_clk(priv->cpu_np, "cls1", &priv->cluster[1])) ||
        (err = spacemit_get_clk(priv->opp_np, "ace0", &priv->ace[0])) ||
        (err = spacemit_get_clk(priv->opp_np, "ace1", &priv->ace[1])) ||
        (err = spacemit_get_clk(priv->opp_np, "tcm", &priv->tcm)) ||
        (err = spacemit_get_clk(priv->opp_np, "cci", &priv->cci)) ||
        (err = spacemit_get_clk(priv->opp_np, "pll3", &priv->pll3)) ||
        (err = spacemit_get_clk(priv->opp_np, "c0hi", &priv->hi[0])) ||
        (err = spacemit_get_clk(priv->opp_np, "c1hi", &priv->hi[1])))
    {
        return err;
    }

    priv->supply = rt_regulator_get(dev, "clst");
    if (rt_is_err_or_null(priv->supply))
    {
        err = priv->supply ? rt_ptr_err(priv->supply) : -RT_ENOENT;
        priv->supply = RT_NULL;
        LOG_E("get clst supply failed: %s", rt_strerror(err));
        return err;
    }

    return RT_EOK;
}

static void spacemit_put_resources(struct spacemit_cpufreq *priv)
{
    struct rt_clk **clks[] =
    {
        &priv->cluster[0], &priv->cluster[1],
        &priv->ace[0], &priv->ace[1], &priv->tcm, &priv->cci,
        &priv->pll3, &priv->hi[0], &priv->hi[1],
    };

    for (int i = 0; i < RT_ARRAY_SIZE(clks); ++i)
    {
        if (*clks[i])
        {
            rt_clk_put(*clks[i]);
            *clks[i] = RT_NULL;
        }
    }

    if (priv->supply)
    {
        rt_regulator_put(priv->supply);
        priv->supply = RT_NULL;
    }
}

static struct rt_dvfs_opp *spacemit_closest_opp(
        struct rt_dvfs_scaling *scaling, rt_ubase_t rate)
{
    rt_ubase_t best_delta = ~0UL;
    struct rt_dvfs_opp *opp, *best = RT_NULL;

    rt_list_for_each_entry(opp, &scaling->opp_table->opp_nodes, list)
    {
        rt_ubase_t delta;

        if (!opp->available || opp->freq > scaling->max_freq)
        {
            continue;
        }

        delta = rate_delta(rate, opp->freq);
        if (!best || delta < best_delta)
        {
            best = opp;
            best_delta = delta;
        }
    }

    return best;
}

static rt_err_t spacemit_sync_hw_state(struct spacemit_cpufreq *priv,
        struct rt_dvfs_scaling *scaling)
{
    rt_err_t err;
    int uvolt;
    rt_ubase_t rate[2], max_rate;
    struct rt_dvfs_opp *opp;
    struct spacemit_cpufreq_opp *opp_data;

    rate[0] = spacemit_mux_hw_rate(priv->cluster[0]);
    rate[1] = spacemit_mux_hw_rate(priv->cluster[1]);
    max_rate = rt_max(rate[0], rate[1]);
    opp = spacemit_closest_opp(scaling, max_rate);
    if (!opp)
    {
        return -RT_ENOENT;
    }

    opp_data = opp->priv;
    if (rate_matches(rate[0], opp_data->cluster_hz[0]) &&
        rate_matches(rate[1], opp_data->cluster_hz[1]))
    {
        uvolt = rt_regulator_get_voltage(priv->supply);
        if (uvolt > 0 && (rt_ubase_t)uvolt < opp->uvolt)
        {
            if ((err = spacemit_set_voltage(priv, opp->uvolt)))
            {
                return err;
            }
            rt_dvfs_ns_sleep(scaling->transition_latency);
        }

        if ((err = spacemit_finish_dependent_clks(priv, opp_data)))
        {
            return err;
        }

        scaling->cur_freq = opp->freq;
        scaling->opp_table->current_opp = opp;
        return RT_EOK;
    }

    LOG_W("synchronizing boot CPU clocks %lu/%lu Hz to OPP %lu Hz",
            rate[0], rate[1], opp->freq);

    scaling->cur_freq = max_rate;
    scaling->opp_table->current_opp = RT_NULL;

    return rt_dvfs_scaling_apply_opp(scaling, opp);
}

static void spacemit_fill_cpu_map(struct rt_dvfs_cpufreq *cpufreq)
{
    int cpu_id = 0;
    struct rt_ofw_node *cpu_np = RT_NULL;

    cpufreq->master_cpu = 0;
    rt_ofw_foreach_cpu_node(cpu_np)
    {
        if (cpu_id < RT_CPUS_NR)
        {
            rt_bitmap_set_bit(cpufreq->cpus_map, cpu_id);
        }
        ++cpu_id;
    }
}

static void spacemit_cpufreq_destroy(struct spacemit_cpufreq *priv,
        rt_bool_t scaling_registered)
{
    struct rt_dvfs_scaling *scaling;

    if (!priv)
    {
        return;
    }

    scaling = rt_dvfs_cpufreq_to_scaling(&priv->cpufreq);
    if (scaling_registered)
    {
        rt_dvfs_cpufreq_unregister(&priv->cpufreq);
    }

    spacemit_free_opps(scaling);
    spacemit_put_resources(priv);

    if (priv->lock_ready)
    {
        rt_mutex_detach(&priv->lock);
    }

    if (priv->pdev)
    {
        if (priv->dev_registered)
        {
            rt_device_unregister(&priv->pdev->parent);
        }
        rt_ofw_node_put(priv->pdev->parent.ofw_node);
        rt_free(priv->pdev);
    }
    rt_ofw_node_put(priv->opp_np);
    rt_ofw_node_put(priv->cpu_np);
    rt_free(priv);
}

static int spacemit_dvfs_cpufreq_init(void)
{
    rt_err_t err;
    rt_uint64_t cci_hz = SPACEMIT_DEFAULT_CCI_FREQ;
    rt_ubase_t boot_freq;
    struct rt_device *dev;
    struct rt_ofw_node *saved_np;
    struct spacemit_cpufreq *priv;
    struct rt_dvfs_scaling *scaling;

    if (spacemit_cpufreq_data)
    {
        return RT_EOK;
    }

    if (!(priv = rt_calloc(1, sizeof(*priv))))
    {
        return -RT_ENOMEM;
    }

    priv->cpu_np = rt_ofw_get_next_cpu_node(RT_NULL);
    if (!priv->cpu_np)
    {
        err = -RT_ENOENT;
        goto _fail;
    }

    priv->opp_index = spacemit_select_opp_index(priv);
    priv->opp_np = rt_ofw_parse_phandle(priv->cpu_np, "operating-points-v2",
            priv->opp_index);
    if (!priv->opp_np && priv->opp_index)
    {
        LOG_W("OPP table %u missing, falling back to table 0", priv->opp_index);
        priv->opp_index = 0;
        priv->opp_np = rt_ofw_parse_phandle(priv->cpu_np,
                "operating-points-v2", 0);
    }
    if (!priv->opp_np)
    {
        err = -RT_ENOENT;
        goto _fail;
    }

    if (!(priv->pdev = rt_platform_device_alloc("cpufreq")))
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    dev = &priv->pdev->parent;
    dev->ofw_node = rt_ofw_node_get(priv->cpu_np);
    rt_dm_dev_set_name_auto(dev, "cpufreq");

    if ((err = rt_device_register(dev, rt_dm_dev_get_name(dev),
            RT_DEVICE_FLAG_DEACTIVATE)))
    {
        goto _fail;
    }
    priv->dev_registered = RT_TRUE;

    if ((err = rt_mutex_init(&priv->lock, "k1-cpufreq", RT_IPC_FLAG_PRIO)))
    {
        goto _fail;
    }
    priv->lock_ready = RT_TRUE;

    if ((err = spacemit_get_resources(priv)))
    {
        goto _fail;
    }

    scaling = rt_dvfs_cpufreq_to_scaling(&priv->cpufreq);
    scaling->dev = dev;
    scaling->clk = priv->cluster[0];
    scaling->supply = priv->supply;
    scaling->ops = &spacemit_cpufreq_ops;
    scaling->priv = priv;
    scaling->transition_latency = SPACEMIT_DEFAULT_LATENCY_NS;
    scaling->retry_delay = SPACEMIT_DEFAULT_RETRY_NS;

    if ((err = spacemit_parse_opps(priv, scaling)))
    {
        goto _fail;
    }

    scaling->max_freq = priv->is_m1 ? SPACEMIT_M1_MAX_FREQ :
            SPACEMIT_K1_MAX_FREQ;
    boot_freq = rt_max(spacemit_mux_hw_rate(priv->cluster[0]),
            spacemit_mux_hw_rate(priv->cluster[1]));
    scaling->cur_freq = boot_freq;
    spacemit_fill_cpu_map(&priv->cpufreq);

    rt_ofw_prop_read_u64(priv->opp_np, "cci-hz", &cci_hz);
    if ((err = spacemit_set_rate(priv->cci, (rt_ubase_t)cci_hz, "cci",
            SPACEMIT_FREQ_TOLERANCE)))
    {
        goto _fail;
    }

    saved_np = dev->ofw_node;
    dev->ofw_node = RT_NULL;
    err = rt_dvfs_cpufreq_register(&priv->cpufreq);
    dev->ofw_node = saved_np;
    if (err)
    {
        goto _fail;
    }

    if ((err = spacemit_sync_hw_state(priv, scaling)))
    {
        LOG_E("sync hardware state failed: %s", rt_strerror(err));
        spacemit_cpufreq_destroy(priv, RT_TRUE);
        return err;
    }

    if ((err = rt_dvfs_scaling_set_governor(scaling,
            RT_DVFS_GOVERNOR_TYPE_ONDEMAND)))
    {
        LOG_W("ondemand governor unavailable: %s", rt_strerror(err));
        err = rt_dvfs_scaling_set_governor(scaling,
                RT_DVFS_GOVERNOR_TYPE_PERFORMANCE);
        if (err)
        {
            spacemit_cpufreq_destroy(priv, RT_TRUE);
            return err;
        }
    }

    spacemit_cpufreq_data = priv;
    LOG_D("CPUfreq registered as %s: %lu-%lu Hz, current %lu Hz",
            rt_dm_dev_get_name(dev), scaling->min_freq, scaling->max_freq,
            scaling->cur_freq);

    return RT_EOK;

_fail:
    LOG_E("CPUfreq initialization failed: %s", rt_strerror(err));
    spacemit_cpufreq_destroy(priv, RT_FALSE);
    return err;
}
INIT_APP_EXPORT(spacemit_dvfs_cpufreq_init);
