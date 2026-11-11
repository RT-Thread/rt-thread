/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#ifndef __OPP_SELECT_H__
#define __OPP_SELECT_H__

#include <rtthread.h>
#include <rtdevice.h>

struct opp_info;

struct volt_rm_table
{
    int volt;
    int rm;
};

struct opp_data
{
    rt_err_t (*get_soc_info)(struct rt_device *dev, struct rt_ofw_node *np,
            int *bin, int *process);
    rt_err_t (*set_soc_info)(struct rt_device *dev, struct rt_ofw_node *np,
            struct opp_info *info);
    rt_err_t (*set_read_margin)(struct rt_device *dev,
            struct opp_info *opp_info, rt_uint32_t rm);
    rt_err_t (*config_regulators)(struct rt_device *dev,
            struct rt_dvfs_opp *old_opp, struct rt_dvfs_opp *new_opp,
            struct opp_info *info);
};

struct opp_info
{
    struct rt_device *dev;
    struct rt_ofw_node *opp_np;
    const struct opp_data *data;

    struct rt_clk *clk;
    struct rt_regulator *supply;
    struct rt_regulator *mem_supply;

    int bin;
    int process;
    int volt_sel;
    int scale;
    int leakage;

    rt_bool_t is_runtime_active;

    struct rt_spinlock dvfs_lock;
};

#if defined(RT_DVFS_ROCKCHIP_CPUFREQ)

void get_opp_data(const struct rt_ofw_node_id *matches, struct opp_info *info);

rt_err_t nvmem_cell_read_u8(struct rt_ofw_node *np, const char *cell_id,
        rt_uint8_t *val);

const char *regulator_name(struct rt_ofw_node *cpu_np);

rt_err_t opp_table_init(struct rt_device *dev, struct opp_info *info,
        const char *reg_name);

void opp_table_uninit(struct rt_device *dev, struct opp_info *info);

rt_err_t opp_table_adjust(struct rt_device *dev, struct opp_info *info,
        struct rt_dvfs_scaling *scaling);

rt_err_t opp_parse(struct rt_dvfs_scaling *dvfs, struct rt_dvfs_opp *opp,
        struct rt_ofw_node *opp_np, struct opp_info *info);

rt_err_t cpufreq_set_opp(struct rt_dvfs_scaling *scaling, struct rt_dvfs_opp *opp,
        struct opp_info *info);

rt_err_t cpufreq_sync_hw_state(struct rt_dvfs_scaling *scaling);

void opp_dvfs_lock(struct opp_info *info);
void opp_dvfs_unlock(struct opp_info *info);

#else

static inline void get_opp_data(const struct rt_ofw_node_id *matches,
        struct opp_info *info)
{
    RT_UNUSED(matches);
    RT_UNUSED(info);
}

static inline rt_err_t opp_table_init(struct rt_device *dev,
        struct opp_info *info, const char *reg_name)
{
    RT_UNUSED(dev);
    RT_UNUSED(info);
    RT_UNUSED(reg_name);
    return -RT_ENOSYS;
}

#endif /* RT_DVFS_ROCKCHIP_CPUFREQ */

#endif /* __OPP_SELECT_H__ */
