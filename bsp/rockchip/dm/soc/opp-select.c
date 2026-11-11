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

#define DBG_TAG "dvfs.opp"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <opp-select.h>
#ifdef RT_SOC_ROCKCHIP_PVTM
#include <rockchip.h>
#endif

static rt_err_t rk3588_get_soc_info(struct rt_device *dev, struct rt_ofw_node *np,
        int *bin, int *process)
{
    rt_uint8_t value = 0;
    rt_err_t err;

    if (bin)
    {
        if (!(err = nvmem_cell_read_u8(np, "specification_serial_number", &value)))
        {
            if (value == 0xb)
            {
                *bin = 0;
            }
            else if (value == 0x1)
            {
                *bin = 1;
            }
            else if (value == 0x10)
            {
                *bin = 1;
            }
            LOG_D("%s: bin=%d", rt_dm_dev_get_name(dev), *bin);
        }
    }

    RT_UNUSED(process);
    return RT_EOK;
}

static const struct opp_data rk3588_cpu_opp_data =
{
    .get_soc_info = rk3588_get_soc_info,
};

static const struct rt_ofw_node_id cpu_opp_ids[] =
{
    { .compatible = "rockchip,rk3588", .data = &rk3588_cpu_opp_data },
    { .compatible = "rockchip,rk3576" },
    { .compatible = "rockchip,rk3568" },
    { .compatible = "rockchip,rk3399" },
    { .compatible = "rockchip,rk3308" },
    { .compatible = "rockchip,rk3328" },
    { .compatible = "rockchip,px30" },
    { /* sentinel */ }
};

void get_opp_data(const struct rt_ofw_node_id *matches, struct opp_info *info)
{
    struct rt_ofw_node *soc_np;
    const struct rt_ofw_node_id *match;

    if (!info)
    {
        return;
    }

    if (!matches)
    {
        matches = cpu_opp_ids;
    }

    if (!(soc_np = rt_ofw_find_node_by_compatible(RT_NULL, "rockchip,rk3588")))
    {
        return;
    }

    match = rt_ofw_node_match(soc_np, matches);
    if (match && match->data)
    {
        info->data = match->data;
    }
}

rt_err_t nvmem_cell_read_u8(struct rt_ofw_node *np, const char *cell_id,
        rt_uint8_t *val)
{
    struct rt_device dev = { .ofw_node = (struct rt_ofw_node *)np };
    struct rt_nvmem_cell *cell;
    rt_ssize_t ret;

    if (!np || !val)
    {
        return -RT_EINVAL;
    }

    cell = rt_nvmem_get_cell_by_name(&dev, cell_id);
    if (rt_is_err_or_null(cell))
    {
        return -RT_ENOENT;
    }

    ret = rt_nvmem_cell_read_u8(cell, val);
    rt_nvmem_put_cell(cell);

    return ret < 0 ? (rt_err_t)ret : RT_EOK;
}

static rt_err_t read_leakage(struct rt_ofw_node *opp_np, int *leakage)
{
    rt_uint8_t value = 0;
    rt_err_t err;

    if (!opp_np || !leakage)
    {
        return -RT_EINVAL;
    }

    err = nvmem_cell_read_u8(opp_np, "leakage", &value);
    if (!err)
    {
        *leakage = value;
    }

    return err;
}

static rt_err_t get_soc_info_default(struct rt_device *dev,
        struct rt_ofw_node *np, int *bin, int *process)
{
    rt_uint8_t value = 0;
    rt_err_t err;

    if (bin)
    {
        err = nvmem_cell_read_u8(np, "performance", &value);
        if (!err)
        {
            *bin = value;
            LOG_D("%s: bin=%d", rt_dm_dev_get_name(dev), *bin);
        }
    }

    RT_UNUSED(process);
    return RT_EOK;
}

static const struct opp_data default_opp_data =
{
    .get_soc_info = get_soc_info_default,
};

void opp_dvfs_lock(struct opp_info *info)
{
    if (info)
    {
        rt_spin_lock(&info->dvfs_lock);
    }
}

void opp_dvfs_unlock(struct opp_info *info)
{
    if (info)
    {
        rt_spin_unlock(&info->dvfs_lock);
    }
}

static void opp_pick_voltages(struct rt_ofw_node *opp_np, struct opp_info *info,
        rt_ubase_t *cpu_uvolt, rt_ubase_t *mem_uvolt)
{
    int nr, l = 0;
    char prop_name[20];
    rt_uint32_t uvolt[6] = {0};

    if (info->leakage > 0)
    {
        l = info->leakage;
    }
    else if (info->volt_sel > 0)
    {
        l = info->volt_sel;
    }

    if (l > 0 && l <= 7)
    {
        rt_snprintf(prop_name, sizeof(prop_name), "opp-microvolt-L%d", l);
        nr = rt_ofw_prop_read_u32_array_index(opp_np, prop_name, 0,
                RT_ARRAY_SIZE(uvolt), uvolt);
        if (nr >= 2)
        {
            *cpu_uvolt = uvolt[1] ? uvolt[1] : uvolt[0];
            if (nr >= 6)
            {
                *mem_uvolt = uvolt[4] ? uvolt[4] : uvolt[3];
            }
            return;
        }
    }

    nr = rt_ofw_prop_read_u32_array_index(opp_np, "opp-microvolt", 0,
            RT_ARRAY_SIZE(uvolt), uvolt);
    if (nr >= 2)
    {
        *cpu_uvolt = uvolt[1] ? uvolt[1] : uvolt[0];
        if (nr >= 6)
        {
            *mem_uvolt = uvolt[4] ? uvolt[4] : uvolt[3];
        }
    }
    else if (nr >= 1)
    {
        *cpu_uvolt = uvolt[0];
    }
}

rt_err_t opp_parse(struct rt_dvfs_scaling *dvfs, struct rt_dvfs_opp *opp,
        struct rt_ofw_node *opp_np, struct opp_info *info)
{
    rt_ubase_t cpu_uvolt = opp->uvolt;
    rt_ubase_t mem_uvolt = 0;

    if (!opp || !opp_np || !info)
    {
        return -RT_EINVAL;
    }

    opp_pick_voltages(opp_np, info, &cpu_uvolt, &mem_uvolt);
    opp->uvolt = cpu_uvolt;
    opp->priv = (void *)(rt_ubase_t)mem_uvolt;

    opp->available = RT_TRUE;

    if (rt_ofw_prop_read_bool(opp_np, "opp-suspend"))
    {
        dvfs->suspend_freq = opp->freq;
    }

    return RT_EOK;
}

static rt_err_t parse_opp_table_props(struct rt_ofw_node *opp_np,
        struct opp_info *info)
{
    if (!opp_np || !info)
    {
        return -RT_EINVAL;
    }

    info->opp_np = opp_np;
    rt_ofw_node_get(opp_np);

    info->bin = -1;
    info->process = -1;
    info->volt_sel = -1;
    info->scale = 0;
    info->leakage = 0;

    read_leakage(opp_np, &info->leakage);

    if (info->data && info->data->get_soc_info)
    {
        info->data->get_soc_info(info->dev, opp_np, &info->bin, &info->process);
    }
    else
    {
        get_soc_info_default(info->dev, opp_np, &info->bin, &info->process);
    }

    return RT_EOK;
}

const char *regulator_name(struct rt_ofw_node *cpu_np)
{
    struct rt_ofw_node *np;

    np = rt_ofw_parse_phandle(cpu_np, "cpu-supply", 0);
    if (np)
    {
        rt_ofw_node_put(np);
        return "cpu";
    }

    np = rt_ofw_parse_phandle(cpu_np, "cpu0-supply", 0);
    if (np)
    {
        rt_ofw_node_put(np);
        return "cpu0";
    }

    return RT_NULL;
}

rt_err_t opp_table_init(struct rt_device *dev, struct opp_info *info,
        const char *reg_name)
{
    rt_err_t err;
    struct rt_ofw_node *cpu_np = dev->ofw_node, *opp_np;

    if (!dev || !info || !cpu_np)
    {
        return -RT_EINVAL;
    }

    rt_memset(info, 0, sizeof(*info));
    rt_spin_lock_init(&info->dvfs_lock);

    info->dev = dev;
    info->is_runtime_active = RT_TRUE;
    info->data = &default_opp_data;

    if (!(opp_np = rt_ofw_parse_phandle(cpu_np, "operating-points-v2", 0)))
    {
        LOG_E("%s: no operating-points-v2", rt_dm_dev_get_name(dev));
        return -RT_ENOENT;
    }

    get_opp_data(RT_NULL, info);

    if ((err = parse_opp_table_props(opp_np, info)))
    {
        rt_ofw_node_put(opp_np);
        return err;
    }

    if (!reg_name)
    {
        reg_name = regulator_name(cpu_np);
    }
    if (!reg_name)
    {
        LOG_E("%s: no cpu supply", rt_dm_dev_get_name(dev));
        err = -RT_ENOENT;
        goto _out;
    }

    info->clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(info->clk))
    {
        LOG_E("%s: get clk failed", rt_dm_dev_get_name(dev));
        err = rt_ptr_err(info->clk);
        goto _out;
    }

    if ((err = rt_clk_prepare_enable(info->clk)))
    if (err)
    {
        LOG_E("%s: enable clk failed: %s",
              rt_dm_dev_get_name(dev), rt_strerror(err));
        rt_clk_put(info->clk);
        info->clk = RT_NULL;
        goto _out;
    }

    info->supply = rt_regulator_get(dev, reg_name);
    if (rt_is_err(info->supply))
    {
        err = rt_ptr_err(info->supply);
        LOG_E("%s: get %s supply failed: %s",
              rt_dm_dev_get_name(dev), reg_name, rt_strerror(err));
        info->supply = RT_NULL;
        goto _out;
    }

    if (rt_ofw_prop_read_bool(cpu_np, "mem-supply"))
    {
        info->mem_supply = rt_regulator_get(dev, "mem");
        if (rt_is_err(info->mem_supply))
        {
            info->mem_supply = RT_NULL;
        }
    }

    rt_ofw_node_put(opp_np);
    return RT_EOK;

_out:
    rt_ofw_node_put(opp_np);
    if (!rt_is_err(info->clk))
    {
        rt_clk_put(info->clk);
    }
    return err;
}

void opp_table_uninit(struct rt_device *dev, struct opp_info *info)
{
    RT_UNUSED(dev);

    if (!info)
    {
        return;
    }

    if (!rt_is_err(info->clk))
    {
        rt_clk_disable_unprepare(info->clk);
        rt_clk_put(info->clk);
        info->clk = RT_NULL;
    }

    if (info->supply)
    {
        rt_regulator_put(info->supply);
        info->supply = RT_NULL;
    }

    if (info->mem_supply)
    {
        rt_regulator_put(info->mem_supply);
        info->mem_supply = RT_NULL;
    }

    if (info->opp_np)
    {
        rt_ofw_node_put(info->opp_np);
        info->opp_np = RT_NULL;
    }
}

#ifdef RT_SOC_ROCKCHIP_PVTM
static rt_err_t nvmem_cell_read_u16(struct rt_ofw_node *np, const char *cell_id,
        rt_uint16_t *val)
{
    rt_ssize_t ret;
    struct rt_device dev = { .ofw_node = (struct rt_ofw_node *)np };
    struct rt_nvmem_cell *cell;

    if (!np || !val)
    {
        return -RT_EINVAL;
    }

    cell = rt_nvmem_get_cell_by_name(&dev, cell_id);
    if (rt_is_err_or_null(cell))
    {
        return -RT_ENOENT;
    }

    ret = rt_nvmem_cell_read_u16(cell, val);
    rt_nvmem_put_cell(cell);

    return ret < 0 ? (rt_err_t)ret : RT_EOK;
}

static rt_err_t get_prop_sel(struct rt_ofw_node *np, const char *prop_name,
        rt_int32_t value, int *sel)
{
    rt_uint32_t tuple[3], count;
    int picked = -1;

    if (!np || !prop_name || !sel)
    {
        return -RT_EINVAL;
    }

    count = rt_ofw_prop_count_of_size(np, prop_name, sizeof(rt_uint32_t));
    if (count < 0 || (count % 3) != 0)
    {
        return -RT_EINVAL;
    }

    for (rt_uint32_t i = 0; i < count; i += 3)
    {
        if (rt_ofw_prop_read_u32_array_index(np, prop_name, i, 3, tuple))
        {
            continue;
        }

        if (value >= (rt_int32_t)tuple[0])
        {
            picked = (int)tuple[2];
        }
    }

    if (picked < 0)
    {
        return -RT_ENOENT;
    }

    *sel = picked;
    return RT_EOK;
}

static rt_int32_t read_pvtm(struct rt_ofw_node *opp_np)
{
    rt_uint16_t tmp = 0;
    rt_uint32_t ch[2] = {0}, sample_time = 1000, pvtm;

    if (!opp_np)
    {
        return -RT_EINVAL;
    }

    if (!nvmem_cell_read_u16(opp_np, "pvtm", &tmp))
    {
        return (rt_int32_t)(tmp * 10);
    }

    if (rt_ofw_prop_read_u32_array_index(opp_np, "rockchip,pvtm-ch", 0, 2, ch))
    {
        return -RT_ENOENT;
    }

    rt_ofw_prop_read_u32(opp_np, "rockchip,pvtm-sample-time", &sample_time);

    pvtm = rockchip_get_pvtm_value(ch[0], ch[1], sample_time);
    if (pvtm <= 0)
    {
        return pvtm;
    }

    return pvtm;
}

static void apply_pvtm_sel(struct rt_device *dev, struct rt_ofw_node *opp_np,
        struct opp_info *info)
{
    char prop_name[32];
    rt_int32_t pvtm;
    int volt_sel = -1, scale_sel = -1;

    if (!dev || !opp_np || !info)
    {
        return;
    }

    if (rt_ofw_prop_read_bool(opp_np, "rockchip,pvtm-pvtpll"))
    {
        return;
    }

    pvtm = read_pvtm(opp_np);
    if (pvtm <= 0)
    {
        return;
    }

    if (info->process >= 0)
    {
        rt_snprintf(prop_name, sizeof(prop_name),
                "rockchip,p%d-pvtm-voltage-sel", info->process);
    }
    else if (info->bin > 0)
    {
        rt_snprintf(prop_name, sizeof(prop_name),
                "rockchip,pvtm-voltage-sel-B%d", info->bin);
    }
    else
    {
        rt_strncpy(prop_name, "rockchip,pvtm-voltage-sel", sizeof(prop_name));
    }

    if (!get_prop_sel(opp_np, prop_name, pvtm, &volt_sel))
    {
        info->volt_sel = volt_sel;
    }
    else if (!get_prop_sel(opp_np, "rockchip,pvtm-voltage-sel", pvtm, &volt_sel))
    {
        info->volt_sel = volt_sel;
    }

    if (info->process >= 0)
    {
        rt_snprintf(prop_name, sizeof(prop_name),
                "rockchip,p%d-pvtm-scaling-sel", info->process);
    }
    else
    {
        rt_strncpy(prop_name, "rockchip,pvtm-scaling-sel", sizeof(prop_name));
    }

    if (!get_prop_sel(opp_np, prop_name, pvtm, &scale_sel))
    {
        info->scale = scale_sel;
    }

    LOG_D("%s: pvtm=%d volt_sel=%d scale=%d",
          rt_dm_dev_get_name(dev), pvtm, info->volt_sel, info->scale);
}
#endif /* RT_SOC_ROCKCHIP_PVTM */

rt_err_t opp_table_adjust(struct rt_device *dev, struct opp_info *info,
        struct rt_dvfs_scaling *scaling)
{
    struct rt_dvfs_opp *opp;
    struct rt_ofw_node *opp_np, *opp_child_np;

    if (!dev || !info || !scaling || !scaling->opp_table)
    {
        return -RT_EINVAL;
    }

    opp_np = info->opp_np;
    if (!opp_np)
    {
        return -RT_ENOENT;
    }

#ifdef RT_SOC_ROCKCHIP_PVTM
    apply_pvtm_sel(dev, opp_np, info);
#endif

    rt_ofw_foreach_child_node(opp_np, opp_child_np)
    {
        rt_uint64_t hz = 0;

        if (rt_ofw_prop_read_u64(opp_child_np, "opp-hz", &hz))
        {
            continue;
        }

        opp = rt_dvfs_scaling_find_opp(scaling, (rt_ubase_t)hz);
        if (!opp)
        {
            continue;
        }

        opp_parse(scaling, opp, opp_child_np, info);
    }

    if (info->data && info->data->set_soc_info)
    {
        info->data->set_soc_info(dev, opp_np, info);
    }

    LOG_D("%s: OPP adjusted leakage=%d bin=%d %lu-%lu Hz",
          rt_dm_dev_get_name(dev), info->leakage, info->bin,
          scaling->min_freq, scaling->max_freq);

    return RT_EOK;
}

static rt_err_t set_regulator_volt(struct rt_regulator *reg,
        rt_ubase_t old_uvolt, rt_ubase_t new_uvolt)
{
    if (!reg)
    {
        return new_uvolt == old_uvolt ? RT_EOK : -RT_EINVAL;
    }

    if (new_uvolt == old_uvolt)
    {
        return RT_EOK;
    }

    return rt_regulator_set_voltage(reg, new_uvolt, new_uvolt);
}

rt_err_t cpufreq_sync_hw_state(struct rt_dvfs_scaling *scaling)
{
    rt_ubase_t rate;
    struct rt_dvfs_opp *opp;

    if (!scaling || !scaling->clk || !scaling->opp_table)
    {
        return -RT_EINVAL;
    }

    if (!(rate = rt_clk_get_rate(scaling->clk)))
    {
        return -RT_ENOENT;
    }

    if (!(opp = rt_dvfs_scaling_find_floor_opp(scaling, rate)))
    {
        opp = rt_dvfs_scaling_find_ceil_opp(scaling, rate);
    }
    if (!opp || !opp->available)
    {
        return -RT_ENOENT;
    }

    scaling->cur_freq = rate;
    scaling->opp_table->current_opp = opp;

    LOG_D("%s: synced hw state %lu Hz @ %lu uV",
          rt_dm_dev_get_name(scaling->dev), rate, opp->uvolt);

    return RT_EOK;
}

rt_err_t cpufreq_set_opp(struct rt_dvfs_scaling *scaling,
        struct rt_dvfs_opp *opp, struct opp_info *info)
{
    rt_err_t err = RT_EOK;
    struct rt_dvfs_opp *old_opp;
    rt_ubase_t old_freq, old_cpu_uvolt, new_freq, new_cpu_uvolt, new_mem_uvolt, old_mem_uvolt = 0;

    if (!scaling || !opp || !info)
    {
        return -RT_EINVAL;
    }

    opp_dvfs_lock(info);

    old_opp = scaling->opp_table ? scaling->opp_table->current_opp : RT_NULL;
    old_freq = scaling->cur_freq;
    if (old_opp)
    {
        old_cpu_uvolt = old_opp->uvolt;
        if (old_opp->priv)
        {
            old_mem_uvolt = (rt_ubase_t)old_opp->priv;
        }
    }

    new_freq = opp->freq;
    new_cpu_uvolt = opp->uvolt;
    new_mem_uvolt = opp->priv ? (rt_ubase_t)opp->priv : 0;

    opp_dvfs_unlock(info);

    if (!old_opp && scaling->clk)
    {
        rt_ubase_t hw_rate = rt_clk_get_rate(scaling->clk);

        if (hw_rate)
        {
            struct rt_dvfs_opp *hw_opp;

            if (!old_freq)
            {
                old_freq = hw_rate;
            }

            hw_opp = rt_dvfs_scaling_find_floor_opp(scaling, hw_rate);
            if (!hw_opp)
            {
                hw_opp = rt_dvfs_scaling_find_ceil_opp(scaling, hw_rate);
            }
            if (hw_opp)
            {
                if (!old_opp)
                {
                    old_opp = hw_opp;
                    old_cpu_uvolt = hw_opp->uvolt;
                    if (hw_opp->priv)
                    {
                        old_mem_uvolt = (rt_ubase_t)hw_opp->priv;
                    }
                }
            }
        }
    }

    if (info->data && info->data->config_regulators)
    {
        err = info->data->config_regulators(scaling->dev, old_opp, opp, info);
    }
    else if (new_freq > old_freq)
    {
        err = set_regulator_volt(scaling->supply, old_cpu_uvolt, new_cpu_uvolt);
        if (!err && info->mem_supply)
        {
            err = set_regulator_volt(info->mem_supply, old_mem_uvolt, new_mem_uvolt);
        }
        if (!err && scaling->transition_latency)
        {
            rt_dvfs_ns_sleep(scaling->transition_latency);
        }
        if (!err)
        {
            if (scaling->clk)
            {
                err = rt_clk_set_rate(scaling->clk, new_freq);
            }
            else
            {
                err = -RT_ENOSYS;
            }
        }
    }
    else if (new_freq < old_freq)
    {
        if (scaling->clk)
        {
            err = rt_clk_set_rate(scaling->clk, new_freq);
        }
        else
        {
            err = -RT_ENOSYS;
        }
        if (!err)
        {
            err = set_regulator_volt(scaling->supply, old_cpu_uvolt, new_cpu_uvolt);
        }
        if (!err && info->mem_supply)
        {
            err = set_regulator_volt(info->mem_supply, old_mem_uvolt, new_mem_uvolt);
        }
    }
    else
    {
        err = set_regulator_volt(scaling->supply, old_cpu_uvolt, new_cpu_uvolt);
        if (!err && info->mem_supply)
        {
            err = set_regulator_volt(info->mem_supply, old_mem_uvolt, new_mem_uvolt);
        }
    }

    opp_dvfs_lock(info);

    if (!err)
    {
        scaling->cur_freq = new_freq;
        if (scaling->opp_table)
        {
            scaling->opp_table->current_opp = opp;
        }
    }
    else
    {
        LOG_W("%s: set OPP %lu Hz/%lu uV failed at %lu Hz/%lu uV: %s",
              rt_dm_dev_get_name(scaling->dev), new_freq, new_cpu_uvolt,
              old_freq, old_cpu_uvolt, rt_strerror(err));
    }

    opp_dvfs_unlock(info);
    return err;
}
