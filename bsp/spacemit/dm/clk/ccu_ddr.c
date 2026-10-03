/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include "ccu_ddr.h"

#define DBG_TAG "clk.ccu.ddr"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define PMU_AP_IMR              0x098
#define AP_DCLK_FC_DONE_INT_MSK RT_BIT(15)
#define DCLK_FC_DONE_INT_MSK    RT_BIT(4)

#define PMU_AP_ISR              0x0a0
#define AP_DCLK_FC_DONE_INT_STS RT_BIT(15)
#define DCLK_FC_DONE_INT_STS    RT_BIT(4)
#define AP_FC_STS               RT_BIT(1)

#define DFC_AP                  0x180
#define DFC_FREQ_LV             0x1
#define DFC_REQ                 RT_BIT(0)

#define DFC_STATUS              0x188
#define DFC_CAUSE_SHIFT         0x7
#define DFC_STS                 RT_BIT(0)

/* Enable/disable ddr frequency change done interrupt */
static void ccu_ddr_enable_dfc_int(struct ccu_common *common, rt_bool_t enable)
{
    rt_uint32_t val;
    rt_ubase_t level;

    level = rt_spin_lock_irqsave(common->lock);

    val = HWREG32(common->base + PMU_AP_IMR);
    if (enable)
    {
        val |= AP_DCLK_FC_DONE_INT_MSK;
    }
    else
    {
        val &= ~AP_DCLK_FC_DONE_INT_MSK;
    }
    HWREG32(common->base + PMU_AP_IMR) = val;

    rt_spin_unlock_irqrestore(common->lock, level);
}

/* clear ddr frequency change done interrupt status*/
static void ccu_ddr_clear_dfc_int_status(struct ccu_common *common)
{
    rt_uint32_t val;
    rt_ubase_t level;

    level = rt_spin_lock_irqsave(common->lock);

    val = HWREG32(common->base + PMU_AP_ISR);
    val &= ~(AP_DCLK_FC_DONE_INT_STS | AP_FC_STS);
    HWREG32(common->base + PMU_AP_ISR) = val;

    rt_spin_unlock_irqrestore(common->lock, level);
}

static rt_err_t ccu_ddr_wait_freq_change_done(struct ccu_common *common)
{
    int timeout = 100;

    while (--timeout)
    {
        rt_hw_us_delay(10);

        if (HWREG32(common->base + PMU_AP_ISR) & AP_DCLK_FC_DONE_INT_STS)
        {
            break;
        }
    }

    if (!timeout)
    {
        LOG_E("%s:%s timeout, can not wait dfc done interrupt", __func__, common->cell.name);
        return -RT_EBUSY;
    }

    return RT_EOK;
}

static rt_err_t ccu_ddr_freq_chg(struct ccu_common *common,
        struct ccu_mux_config *mux, rt_uint8_t level_no)
{
    rt_ubase_t level;
    rt_uint32_t reg, timeout;

    if (level_no > MAX_FREQ_LV)
    {
        LOG_E("%s:%s invalid %d freq level", __func__, common->cell.name, level_no);
        return -RT_EINVAL;
    }

    /* Check if dfc in progress */
    timeout = 1000;
    while (--timeout)
    {
        if (!(HWREG32(common->base + DFC_STATUS) & DFC_STS))
        {
            break;
        }
        rt_hw_us_delay(10);
    }

    if (!timeout)
    {
        LOG_E("%s:%s another dfc is in pregress. status: %#x",
                __func__, common->cell.name, HWREG32(common->base + DFC_STATUS));
        return -RT_EBUSY;
    }

    level = rt_spin_lock_irqsave(common->lock);

    reg = HWREG32(common->base + common->reg_sel);
    reg &= ~RT_GENMASK(mux->width + mux->shift - 1, mux->shift);
    HWREG32(common->base + common->reg_sel) = reg | (level_no << mux->shift) | common->fc;

    rt_spin_unlock_irqrestore(common->lock, level);

    timeout = 1000;
    while (--timeout)
    {
        rt_hw_us_delay(10);

        if (!(HWREG32(common->base + DFC_STATUS) & DFC_STS))
        {
            break;
        }
    }

    if (!timeout)
    {
        LOG_E("%s dfc error! status: %#x", common->cell.name, HWREG32(common->base + DFC_STATUS));
        return -RT_EBUSY;
    }

    return RT_EOK;
}

static rt_ubase_t ccu_ddr_calc_best_rate(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_uint32_t *mux_val)
{
    rt_ubase_t parent_rate = 0, best_rate = 0;
    struct rt_clk_cell *parent;

    for (int i = 0; i < cell->parents_nr; ++i)
    {
        parent = rt_clk_cell_get_parent_by_index(cell, i);

        if (!parent)
        {
            continue;
        }

        parent_rate = rt_clk_cell_get_rate(parent);

        if (rt_abs(parent_rate - rate) < rt_abs(best_rate - rate))
        {
            best_rate = parent_rate;
            *mux_val = i;
        }
    }

    return best_rate;
}

static rt_ubase_t ccu_ddr_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    return parent_rate;
}

static rt_base_t ccu_ddr_round_rate(struct rt_clk_cell *cell, rt_ubase_t drate, rt_ubase_t *prate)
{
    return drate;
}

static rt_err_t ccu_ddr_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_uint32_t cur_mux, mux_val = 0, reg = 0;
    struct ccu_ddr *ddr = cell_to_ccu_ddr(cell);
    struct ccu_common *common = &ddr->common;
    struct ccu_mux_config *mux = ddr->mux ? : RT_NULL;

    if (!mux)
    {
        return RT_EOK;
    }

    ccu_ddr_calc_best_rate(cell, rate, &mux_val);

    reg = HWREG32(common->base + common->reg_sel);

    if (mux)
    {
        cur_mux = reg >> mux->shift;
        cur_mux &= (1 << mux->width) - 1;

        if (cur_mux != mux_val)
        {
            rt_clk_cell_set_parent(cell, rt_clk_cell_get_parent_by_index(cell, mux_val));
        }
    }

    return RT_EOK;
}

static rt_err_t ccu_ddr_set_parent(struct rt_clk_cell *cell, rt_uint8_t idx)
{
    rt_err_t err;
    struct ccu_ddr *ddr = cell_to_ccu_ddr(cell);
    struct ccu_common *common = &ddr->common;
    struct ccu_mux_config *mux = ddr->mux;

    if (!mux)
    {
        return RT_EOK;
    }

    if (mux->table)
    {
        idx = mux->table[idx];
    }

    /* Request change begin */
    ccu_ddr_enable_dfc_int(common, RT_TRUE);

    /* Change parent*/
    if ((err = ccu_ddr_freq_chg(common, mux, idx)))
    {
        LOG_E("%s:%s ddr_freq_chg fail", __func__, common->cell.name);
        return err;
    }

    /* Wait for frequency change done */
    if ((err = ccu_ddr_wait_freq_change_done(common)))
    {
        LOG_E("%s: %s timeout", __func__, "wait_freq_change_done");
        return err;
    }

    ccu_ddr_clear_dfc_int_status(common);
    ccu_ddr_enable_dfc_int(common, RT_FALSE);

    return RT_EOK;
}

static rt_uint8_t ccu_ddr_get_parent(struct rt_clk_cell *cell)
{
    rt_uint32_t reg;
    rt_uint8_t parent;
    struct ccu_ddr *ddr = cell_to_ccu_ddr(cell);
    struct ccu_common *common = &ddr->common;
    struct ccu_mux_config *mux = ddr->mux;

    if (!mux)
    {
        return 0;
    }

    reg = HWREG32(common->base + common->reg_sel);

    parent = reg >> mux->shift;
    parent &= (1 << mux->width) - 1;

    if (mux->table)
    {
        for (int i = 0; i < common->cell.parents_nr; ++i)
        {
            if (mux->table[i] == parent)
            {
                return i;
            }
        }
    }

    return parent;
}

const struct rt_clk_ops ccu_ddr_ops =
{
    .recalc_rate = ccu_ddr_recalc_rate,
    .round_rate = ccu_ddr_round_rate,
    .set_rate = ccu_ddr_set_rate,
    .set_parent = ccu_ddr_set_parent,
    .get_parent = ccu_ddr_get_parent,
};
