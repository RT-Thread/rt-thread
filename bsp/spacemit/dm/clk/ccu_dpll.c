/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include "ccu_dpll.h"

#define DBG_TAG "clk.ccu.dpll"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define DPLL_MIN_FREQ                   1700000000
#define DPLL_MAX_FREQ                   3400000000

#define pll_readl(reg)                  HWREG32(reg)
#define pll_readl_pll_swcr1(p)          pll_readl(p.base + p.reg_ctrl)
#define pll_readl_pll_swcr2(p)          pll_readl(p.base + p.reg_sel)

#define pll_writel(val, reg)            HWREG32(reg) = val
#define pll_writel_pll_swcr1(val, p)    pll_writel(val, p.base + p.reg_ctrl)
#define pll_writel_pll_swcr2(val, p)    pll_writel(val, p.base + p.reg_sel)

/* Unified dpllx_swcr1 for dpll1~2 */
union dpllx_swcr1
{
    struct
    {
        rt_uint32_t reg0:8;
        rt_uint32_t reg1:8;
        rt_uint32_t reg2:8;
        rt_uint32_t reg3:8;
    } b;
    rt_uint32_t v;
};

/* Unified dpllx_swcr2 for dpll1~2 */
union dpllx_swcr2
{
    struct
    {
        rt_uint32_t reg4:8;
        rt_uint32_t reg5:8;
        rt_uint32_t reg6:8;
        rt_uint32_t reg7:8;
    } b;
    rt_uint32_t v;
};

/* Frequency unit Mhz, return pll vco freq */
static rt_ubase_t __get_vco_freq_raw(struct rt_clk_cell *cell)
{
    rt_uint32_t reg0, reg1, reg2, reg3, reg4, reg5, reg6, reg7, size;
    union dpllx_swcr1 swcr1;
    union dpllx_swcr2 swcr2;
    struct ccu_dpll_rate_tbl *freq_pll_regs_table;
    struct ccu_dpll *p = cell_to_ccu_dpll(cell);

    swcr1.v = pll_readl_pll_swcr1(p->common);
    swcr2.v = pll_readl_pll_swcr2(p->common);

    reg0 = swcr1.b.reg0;
    reg1 = swcr1.b.reg1;
    reg2 = swcr1.b.reg2;
    reg3 = swcr1.b.reg3;
    reg4 = swcr2.b.reg4;
    reg5 = swcr2.b.reg5;
    reg6 = swcr2.b.reg6;
    reg7 = swcr2.b.reg7;

    freq_pll_regs_table = p->dpll.rate_tbl;
    size = p->dpll.tbl_size;

    for (int i = 0; i < size; ++i)
    {
        struct ccu_dpll_rate_tbl *item = &freq_pll_regs_table[i];

        if (item->reg0 == reg0 &&
            item->reg1 == reg1 &&
            item->reg2 == reg2 &&
            item->reg3 == reg3 &&
            item->reg4 == reg4 &&
            item->reg5 == reg5 &&
            item->reg6 == reg6 &&
            item->reg7 == reg7)
        {
            return item->rate;
        }
    }

    LOG_E("Unknown rate for clock %s", cell->name);

    return 0;
}

static rt_ubase_t ccu_dpll_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    return __get_vco_freq_raw(cell);
}

static rt_base_t ccu_dpll_round_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t *prate)
{
    rt_ubase_t max_rate = 0;
    struct ccu_dpll *p = cell_to_ccu_dpll(cell);
    struct ccu_dpll_config *params = &p->dpll;

    if (rate > DPLL_MAX_FREQ || rate < DPLL_MIN_FREQ)
    {
        LOG_E("%s %lu rate out of range", cell->name, rate);
        return -RT_EINVAL;
    }

    if (params->rate_tbl)
    {
        for (int i = 0; i < params->tbl_size; ++i)
        {
            struct ccu_dpll_rate_tbl *item = &params->rate_tbl[i];

            if (item->rate <= rate)
            {
                if (max_rate < item->rate)
                {
                    max_rate = item->rate;
                }
            }
        }
    }
    else
    {
        LOG_E("%s don't find freq table for pll", cell->name);
    }

    return max_rate;
}

const struct rt_clk_ops ccu_dpll_ops =
{
    .recalc_rate = ccu_dpll_recalc_rate,
    .round_rate = ccu_dpll_round_rate,
};
