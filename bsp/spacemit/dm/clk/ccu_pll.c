/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include "ccu_pll.h"

#define DBG_TAG "clk.ccu.pll"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define PLL_MIN_FREQ                    600000000
#define PLL_MAX_FREQ                    3400000000
#define PLL_DELAYTIME                   590 /* 590 * 5us */

#define pll_readl(reg)                  HWREG32(reg)
#define pll_readl_pll_swcr1(p)          pll_readl(p.base + p.reg_ctrl)
#define pll_readl_pll_swcr2(p)          pll_readl(p.base + p.reg_sel)
#define pll_readl_pll_swcr3(p)          pll_readl(p.base + p.reg_xtc)

#define pll_writel(val, reg)            HWREG32(reg) = val;
#define pll_writel_pll_swcr1(val, p)    pll_writel(val, p.base + p.reg_ctrl)
#define pll_writel_pll_swcr2(val, p)    pll_writel(val, p.base + p.reg_sel)
#define pll_writel_pll_swcr3(val, p)    pll_writel(val, p.base + p.reg_xtc)

/* Unified pllx_swcr1 for pll1~3 */
union pllx_swcr1
{
    struct
    {
        rt_uint32_t reg5:8;
        rt_uint32_t reg6:8;
        rt_uint32_t reg7:8;
        rt_uint32_t reg8:8;
    } b;
    rt_uint32_t v;
};

/* Unified pllx_swcr2 for pll1~3 */
union pllx_swcr2
{
    struct
    {
        rt_uint32_t div1_en:1;
        rt_uint32_t div2_en:1;
        rt_uint32_t div3_en:1;
        rt_uint32_t div4_en:1;
        rt_uint32_t div5_en:1;
        rt_uint32_t div6_en:1;
        rt_uint32_t div7_en:1;
        rt_uint32_t div8_en:1;
        rt_uint32_t reserved1:4;
        rt_uint32_t atest_en:1;
        rt_uint32_t cktest_en:1;
        rt_uint32_t dtest_en:1;
        rt_uint32_t rdo:2;
        rt_uint32_t mon_cfg:4;
        rt_uint32_t reserved2:11;
    } b;
    rt_uint32_t v;
};

/* Unified pllx_swcr3 for pll1~3 */
union pllx_swcr3
{
    struct
    {
        rt_uint32_t div_frc:24;
        rt_uint32_t div_int:7;
        rt_uint32_t pll_en:1;
    } b;
    rt_uint32_t v;
};

static rt_bool_t ccu_pll_is_enabled(struct rt_clk_cell *cell)
{
    rt_bool_t enabled;
    union pllx_swcr3 swcr3;
    struct ccu_pll *p = cell_to_ccu_pll(cell);

    swcr3.v = pll_readl_pll_swcr3(p->common);
    enabled = !!swcr3.b.pll_en;

    return enabled;
}

/* Frequency unit Mhz, return pll vco freq */
static rt_ubase_t __get_vco_freq(struct rt_clk_cell *cell)
{
    rt_uint32_t div_int, div_frc, reg5, reg6, reg7, reg8, size;
    union pllx_swcr1 swcr1;
    union pllx_swcr3 swcr3;
    struct ccu_pll_rate_tbl *freq_pll_regs_table;
    struct ccu_pll *p = cell_to_ccu_pll(cell);

    swcr1.v = pll_readl_pll_swcr1(p->common);
    swcr3.v = pll_readl_pll_swcr3(p->common);

    reg5 = swcr1.b.reg5;
    reg6 = swcr1.b.reg6;
    reg7 = swcr1.b.reg7;
    reg8 = swcr1.b.reg8;

    div_int = swcr3.b.div_int;
    div_frc = swcr3.b.div_frc;

    freq_pll_regs_table = p->pll.rate_tbl;
    size = p->pll.tbl_size;

    for (int i = 0; i < size; ++i)
    {
        struct ccu_pll_rate_tbl *item = &freq_pll_regs_table[i];

        if (item->reg5 == reg5 && item->reg6 == reg6 &&
            item->reg7 == reg7 && item->reg8 == reg8 &&
            item->div_int == div_int && item->div_frac == div_frc)
        {
            return item->rate;
        }
    }

    LOG_E("Unknown rate for clock %s", cell->name);

    return 0;
}

static rt_err_t ccu_pll_enable(struct rt_clk_cell *cell)
{
    rt_ubase_t level;
    rt_uint32_t delaytime = PLL_DELAYTIME;
    union pllx_swcr3 swcr3;
    struct ccu_pll *p = cell_to_ccu_pll(cell);

    if (ccu_pll_is_enabled(cell))
    {
        return RT_EOK;
    }

    level = rt_spin_lock_irqsave(p->common.lock);

    swcr3.v = pll_readl_pll_swcr3(p->common);
    swcr3.b.pll_en = 1;
    pll_writel_pll_swcr3(swcr3.v, p->common);

    rt_spin_unlock_irqrestore(p->common.lock, level);

    /* Check lock status */
    rt_hw_us_delay(50);

    while ((!(HWREG32(p->pll.lock_base + p->pll.reg_lock) & p->pll.lock_enable_bit)) && delaytime)
    {
        rt_hw_us_delay(5);
        --delaytime;
    }

    if (!delaytime)
    {
        LOG_E("%s enabling didn't get stable within 3000us", cell->name);
    }

    return RT_EOK;
}

static void ccu_pll_disable(struct rt_clk_cell *cell)
{
    rt_ubase_t level;
    union pllx_swcr3 swcr3;
    struct ccu_pll *p = cell_to_ccu_pll(cell);

    level = rt_spin_lock_irqsave(p->common.lock);

    swcr3.v = pll_readl_pll_swcr3(p->common);
    swcr3.b.pll_en = 0;
    pll_writel_pll_swcr3(swcr3.v, p->common);

    rt_spin_unlock_irqrestore(p->common.lock, level);
}

static rt_ubase_t ccu_pll_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    return __get_vco_freq(cell);
}

static rt_base_t ccu_pll_round_rate(struct rt_clk_cell *cell, rt_ubase_t drate, rt_ubase_t *prate)
{
    rt_ubase_t max_rate = 0;
    struct ccu_pll *p = cell_to_ccu_pll(cell);
    struct ccu_pll_config *params = &p->pll;

    if (drate > PLL_MAX_FREQ || drate < PLL_MIN_FREQ)
    {
        LOG_E("%s %lu rate out of range", cell->name, drate);
        return -RT_EINVAL;
    }

    if (params->rate_tbl)
    {
        for (int i = 0; i < params->tbl_size; ++i)
        {
            struct ccu_pll_rate_tbl *item = &params->rate_tbl[i];

            if (item->rate <= drate)
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

/*
 * PLL rate change requires sequence:
 * clock off -> change rate setting -> clock on
 * This function doesn't really change rate, but cache the config
 */
static rt_err_t ccu_pll_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_uint32_t div_int, div_frc, reg5 = 0, reg6 = 0, reg7 = 0, reg8 = 0;
    rt_bool_t found = RT_FALSE, pll_enabled = RT_FALSE;
    rt_ubase_t level;
    union pllx_swcr1 swcr1;
    union pllx_swcr3 swcr3;
    struct ccu_pll *p = cell_to_ccu_pll(cell);
    struct ccu_pll_config *params = &p->pll;

    if (ccu_pll_is_enabled(cell))
    {
        pll_enabled = RT_TRUE;
        ccu_pll_disable(cell);
    }

    __get_vco_freq(cell);

    /* Setp 1: calculate fbd frcd kvco and band */
    if (params->rate_tbl)
    {
        for (int i = 0; i < params->tbl_size; ++i)
        {
            struct ccu_pll_rate_tbl *item = &params->rate_tbl[i];

            if (rate == item->rate)
            {
                found = RT_TRUE;

                reg5 = item->reg5;
                reg6 = item->reg6;
                reg7 = item->reg7;
                reg8 = item->reg8;
                div_int = item->div_int;
                div_frc = item->div_frac;

                break;
            }
        }

        if (!found)
        {
            return -RT_EINVAL;
        }
    }
    else
    {
        LOG_E("%s don't find freq table for pll", cell->name);

        if (pll_enabled)
        {
            ccu_pll_enable(cell);
        }

        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(p->common.lock);

    /* Setp 2: set pll kvco/band and fbd/frcd setting */
    swcr1.v = pll_readl_pll_swcr1(p->common);
    swcr1.b.reg5 = reg5;
    swcr1.b.reg6 = reg6;
    swcr1.b.reg7 = reg7;
    swcr1.b.reg8 = reg8;
    pll_writel_pll_swcr1(swcr1.v, p->common);

    swcr3.v = pll_readl_pll_swcr3(p->common);
    swcr3.b.div_int = div_int;
    swcr3.b.div_frc = div_frc;
    pll_writel_pll_swcr3(swcr3.v, p->common);

    rt_spin_unlock_irqrestore(p->common.lock, level);

    if (pll_enabled)
    {
        ccu_pll_enable(cell);
    }

    LOG_D("%s: %s rate %lu->%lu", __func__, clk->name, old_rate, new_rate);

    return RT_EOK;
}

const struct rt_clk_ops ccu_pll_ops =
{
    .enable = ccu_pll_enable,
    .disable = ccu_pll_disable,
    .is_enabled = ccu_pll_is_enabled,
    .recalc_rate = ccu_pll_recalc_rate,
    .round_rate = ccu_pll_round_rate,
    .set_rate = ccu_pll_set_rate,
};
