/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include "ccu_ddn.h"

#define DBG_TAG "clk.ccu.ddn"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/*
 * It is M/N clock
 *
 * Fout from synthesizer can be given from two equations:
 * numerator/denominator = Fin / (Fout * factor)
 */

static void ccu_ddn_disable(struct rt_clk_cell *cell)
{
    rt_uint32_t reg;
    rt_ubase_t level;
    struct ccu_ddn *ddn = cell_to_ccu_ddn(cell);
    struct ccu_common *common = &ddn->common;

    if (!ddn->gate)
    {
        return;
    }

    level = rt_spin_lock_irqsave(common->lock);

    reg = HWREG32(common->base + common->reg_sel);
    HWREG32(common->base + common->reg_sel) = reg & ~ddn->gate;

    rt_spin_unlock_irqrestore(common->lock, level);
}

static rt_err_t ccu_ddn_enable(struct rt_clk_cell *cell)
{
    rt_uint32_t reg;
    rt_ubase_t level;
    struct ccu_ddn *ddn = cell_to_ccu_ddn(cell);
    struct ccu_common *common = &ddn->common;

    if (!ddn->gate)
    {
        return RT_EOK;
    }

    level = rt_spin_lock_irqsave(common->lock);

    reg = HWREG32(common->base + common->reg_sel);
    HWREG32(common->base + common->reg_sel) = reg | ddn->gate;

    rt_spin_unlock_irqrestore(common->lock, level);

    return RT_EOK;
}

static rt_bool_t ccu_ddn_is_enabled(struct rt_clk_cell *cell)
{
    struct ccu_ddn *ddn = cell_to_ccu_ddn(cell);
    struct ccu_common *common = &ddn->common;

    if (!ddn->gate)
    {
        return RT_TRUE;
    }

    return HWREG32(common->base + common->reg_sel) & ddn->gate;
}

static rt_ubase_t ccu_ddn_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    rt_ubase_t rate;
    rt_uint32_t val, num, den;
    struct ccu_ddn *ddn = cell_to_ccu_ddn(cell);
    struct ccu_ddn_config *params = &ddn->ddn;

    val = HWREG32(ddn->common.base + ddn->common.reg_ctrl);

    /* Calculate numerator */
    num = (val >> params->info->num_shift) & params->info->num_mask;

    /* Calculate denominator */
    den = (val >> params->info->den_shift) & params->info->den_mask;

    if (!den)
    {
        return 0;
    }

    rate = (((parent_rate / 10000)  * den) / (num * params->info->factor)) * 10000;

    return rate;
}

static rt_base_t ccu_ddn_round_rate(struct rt_clk_cell *cell, rt_ubase_t drate, rt_ubase_t *prate)
{
    int i;
    rt_ubase_t result, rate = 0, prev_rate;
    struct ccu_ddn *ddn = cell_to_ccu_ddn(cell);
    struct ccu_ddn_config *params = &ddn->ddn;

    for (i = 0; i < params->tbl_size; ++i)
    {
        prev_rate = rate;
        rate = (((*prate / 10000) * params->tbl[i].den) /
                (params->tbl[i].num * params->info->factor)) * 10000;

        if (rate > drate)
        {
            break;
        }
    }

    if (i == 0 || i == params->tbl_size)
    {
        result = rate;
    }
    else
    {
        if (drate - prev_rate > rate - drate)
        {
            result = rate;
        }
        else
        {
            result = prev_rate;
        }
    }

    return result;
}

/* Configures new clock rate */
static rt_err_t ccu_ddn_set_rate(struct rt_clk_cell *cell, rt_ubase_t drate, rt_ubase_t prate)
{
    int i;
    rt_ubase_t val, rate = 0, level;
    struct ccu_ddn *ddn = cell_to_ccu_ddn(cell);
    struct ccu_common *common = &ddn->common;
    struct ccu_ddn_config *params = &ddn->ddn;

    for (i = 0; i < params->tbl_size; ++i)
    {
        rate = (((prate / 10000) * params->tbl[i].den) /
                (params->tbl[i].num * params->info->factor)) * 10000;

        if (rate > drate)
        {
            break;
        }
    }

    if (i > 0)
    {
        --i;
    }

    if (ddn->common.lock)
    {
        level = rt_spin_lock_irqsave(common->lock);
    }

    val = HWREG32(ddn->common.base + ddn->common.reg_ctrl);

    val &= ~(params->info->num_mask << params->info->num_shift);
    val |= (params->tbl[i].num & params->info->num_mask) << params->info->num_shift;

    val &= ~(params->info->den_mask << params->info->den_shift);
    val |= (params->tbl[i].den & params->info->den_mask) << params->info->den_shift;

    HWREG32(ddn->common.base + ddn->common.reg_ctrl) = val;

    if (ddn->common.lock)
    {
        rt_spin_unlock_irqrestore(common->lock, level);
    }

    return RT_EOK;
}

const struct rt_clk_ops ccu_ddn_ops =
{
    .disable = ccu_ddn_disable,
    .enable = ccu_ddn_enable,
    .is_enabled = ccu_ddn_is_enabled,
    .recalc_rate = ccu_ddn_recalc_rate,
    .round_rate = ccu_ddn_round_rate,
    .set_rate = ccu_ddn_set_rate,
};
