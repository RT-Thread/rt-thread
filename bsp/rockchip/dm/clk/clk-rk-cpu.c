/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk-rk-cpu.h"

static rt_ubase_t rockchip_cpu_clk_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    void *base;
    rt_uint32_t clksel0;
    struct rockchip_cpu_clk_cell *cpu_clk_cell = cell_to_rockchip_cpu_cell(cell);
    const struct rockchip_cpu_clk_reg_data *reg_data = cpu_clk_cell->reg_data;

    base = cpu_clk_cell->rk_cell.provider->reg_base;

    clksel0 = HWREG32(base + reg_data->core_reg[0]);
    clksel0 >>= reg_data->div_core_shift[0];
    clksel0 &= reg_data->div_core_mask[0];

    return parent_rate / (clksel0 + 1);
}

const struct rt_clk_ops rockchip_cpu_clk_ops =
{
    .recalc_rate = rockchip_cpu_clk_recalc_rate,
};

static const struct rockchip_cpu_clk_rate_table *rockchip_get_cpu_clk_settings(
        struct rockchip_cpu_clk_cell *cpu_clk_cell, rt_ubase_t rate)
{
    const struct rockchip_cpu_clk_rate_table *rate_table = cpu_clk_cell->rate_table;

    for (int i = 0; i < cpu_clk_cell->rate_count; ++i)
    {
        if (rate == rate_table[i].prate)
        {
            return &rate_table[i];
        }
    }

    return RT_NULL;
}

static void rockchip_cpu_clk_set_dividers(struct rockchip_cpu_clk_cell *cpu_clk_cell,
    const struct rockchip_cpu_clk_rate_table *rate)
{
    void *base = cpu_clk_cell->rk_cell.provider->reg_base;

    /* Alternate parent is active now. set the dividers */
    for (int i = 0; i < RT_ARRAY_SIZE(rate->divs); ++i)
    {
        const struct rockchip_cpu_clk_clksel *clksel = &rate->divs[i];

        if (!clksel->reg)
        {
            continue;
        }

        HWREG32(base + clksel->reg) = clksel->val;
    }
}

static void rockchip_cpu_clk_set_pre_muxs(struct rockchip_cpu_clk_cell *cpu_clk_cell,
        const struct rockchip_cpu_clk_rate_table *rate)
{
    void *base = cpu_clk_cell->rk_cell.provider->reg_base;

    /* Alternate parent is active now. set the pre_muxs */
    for (int i = 0; i < RT_ARRAY_SIZE(rate->pre_muxs); ++i)
    {
        const struct rockchip_cpu_clk_clksel *clksel = &rate->pre_muxs[i];

        if (!clksel->reg)
        {
            break;
        }

        HWREG32(base + clksel->reg) = clksel->val;
    }
}

static void rockchip_cpu_clk_set_post_muxs(struct rockchip_cpu_clk_cell *cpu_clk_cell,
        const struct rockchip_cpu_clk_rate_table *rate)
{
    void *base = cpu_clk_cell->rk_cell.provider->reg_base;

    /* Alternate parent is active now. set the muxs */
    for (int i = 0; i < RT_ARRAY_SIZE(rate->post_muxs); ++i)
    {
        const struct rockchip_cpu_clk_clksel *clksel = &rate->post_muxs[i];

        if (!clksel->reg)
        {
            break;
        }

        HWREG32(base + clksel->reg) = clksel->val;
    }
}

static int rockchip_cpu_clk_pre_rate_change(struct rockchip_cpu_clk_cell *cpu_clk_cell,
        rt_ubase_t old_rate, rt_ubase_t new_rate)
{
    rt_ubase_t alt_prate, alt_div;
    void *base = cpu_clk_cell->rk_cell.provider->reg_base;
    const struct rockchip_cpu_clk_reg_data *reg_data = cpu_clk_cell->reg_data;
    const struct rockchip_cpu_clk_rate_table *rate;

    /* Check validity of the new rate */
    if (!(rate = rockchip_get_cpu_clk_settings(cpu_clk_cell, new_rate)))
    {
        return -RT_EINVAL;
    }

    alt_prate = rt_clk_cell_get_rate(&cpu_clk_cell->rk_cell_alt_parent->cell);

    /*
     * If the old parent clock speed is less than the clock speed
     * of the alternate parent, then it should be ensured that at no point
     * the armclk speed is more than the old_rate until the dividers are
     * set.
     */
    if (alt_prate > old_rate)
    {
        /* Calculate dividers */
        alt_div =  RT_DIV_ROUND_UP(alt_prate, old_rate) - 1;

        if (alt_div > reg_data->div_core_mask[0])
        {
            alt_div = reg_data->div_core_mask[0];
        }

        /*
         * Change parents and add dividers in a single transaction.
         *
         * NOTE: we do this in a single transaction so we're never
         * dividing the primary parent by the extra dividers that were
         * needed for the alt.
         */

        for (int i = 0; i < reg_data->num_cores; ++i)
        {
            HWREG32(base + reg_data->core_reg[i]) = HIWORD_UPDATE(
                    alt_div,
                    reg_data->div_core_mask[i],
                    reg_data->div_core_shift[i]);
        }
    }

    rockchip_cpu_clk_set_pre_muxs(cpu_clk_cell, rate);

    /* select alternate parent */
    if (reg_data->mux_core_reg)
    {
        HWREG32(base + reg_data->mux_core_reg) = HIWORD_UPDATE(
                reg_data->mux_core_alt,
                reg_data->mux_core_mask,
                reg_data->mux_core_shift);
    }
    else
    {
        HWREG32(base + reg_data->core_reg[0]) = HIWORD_UPDATE(
                reg_data->mux_core_alt,
                reg_data->mux_core_mask,
                reg_data->mux_core_shift);
    }

    return RT_EOK;
}

static rt_err_t rockchip_cpu_clk_post_rate_change(struct rockchip_cpu_clk_cell *cpu_clk_cell,
        rt_ubase_t old_rate, rt_ubase_t new_rate)
{
    void *base = cpu_clk_cell->rk_cell.provider->reg_base;
    const struct rockchip_cpu_clk_rate_table *rate;
    const struct rockchip_cpu_clk_reg_data *reg_data = cpu_clk_cell->reg_data;

    if (!(rate = rockchip_get_cpu_clk_settings(cpu_clk_cell, new_rate)))
    {
        return -RT_EINVAL;
    }

    if (old_rate < new_rate)
    {
        rockchip_cpu_clk_set_dividers(cpu_clk_cell, rate);
    }

    /*
     * post-rate change event, re-mux to primary parent and remove dividers.
     *
     * NOTE: we do this in a single transaction so we're never dividing the
     * primary parent by the extra dividers that were needed for the alt.
     */

    if (reg_data->mux_core_reg)
    {
        HWREG32(base + reg_data->mux_core_reg) = HIWORD_UPDATE(
                reg_data->mux_core_main,
                reg_data->mux_core_mask,
                reg_data->mux_core_shift);
    }
    else
    {
        HWREG32(base + reg_data->core_reg[0]) = HIWORD_UPDATE(
                reg_data->mux_core_main,
                reg_data->mux_core_mask,
                reg_data->mux_core_shift);
    }

    rockchip_cpu_clk_set_post_muxs(cpu_clk_cell, rate);

    /* Remove dividers */
    for (int i = 0; i < reg_data->num_cores; ++i)
    {
        HWREG32(base + reg_data->core_reg[i]) = HIWORD_UPDATE(
                    0,
                    reg_data->div_core_mask[i],
                    reg_data->div_core_shift[i]);
    }

    if (old_rate > new_rate)
    {
        rockchip_cpu_clk_set_dividers(cpu_clk_cell, rate);
    }

    return RT_EOK;
}

static rt_err_t rockchip_cpu_clk_notify(struct rt_clk_notifier *notifier,
        rt_ubase_t msg, rt_ubase_t old_rate, rt_ubase_t new_rate)
{
    rt_err_t err = RT_EOK;
    struct rockchip_cpu_clk_cell *cpu_cell;

    cpu_cell = rt_container_of(notifier, struct rockchip_cpu_clk_cell, notifier);

    if (msg == RT_CLK_MSG_PRE_RATE_CHANGE)
    {
        err = rockchip_cpu_clk_pre_rate_change(cpu_cell, old_rate, new_rate);
    }
    else if (msg == RT_CLK_MSG_POST_RATE_CHANGE)
    {
        err = rockchip_cpu_clk_post_rate_change(cpu_cell, old_rate, new_rate);
    }

    return err;
}

void rockchip_cpu_clk_cell_init(struct rockchip_clk_cell *rk_cell)
{
    struct rockchip_cpu_clk_cell *cpu_clk_cell = cell_to_rockchip_cpu_cell(&rk_cell->cell);

    rk_cell->cell.parents_nr = 1;
    rk_cell->cell.parent_name = cpu_clk_cell->rk_cell_parent->cell.name;

    if (cpu_clk_cell->rate_count > 0)
    {
        rk_cell->cell.flags |= RT_CLK_F_SET_RATE_PARENT;
    }
}

void rockchip_cpu_clk_cell_setup(struct rockchip_clk_cell *rk_cell)
{
    struct rockchip_cpu_clk_cell *cpu_clk_cell = cell_to_rockchip_cpu_cell(&rk_cell->cell);

    rt_clk_prepare_enable(rt_clk_cell_get_clk(&cpu_clk_cell->rk_cell_alt_parent->cell, RT_NULL));

    cpu_clk_cell->notifier.callback = rockchip_cpu_clk_notify;

    rt_clk_notifier_register(rt_clk_cell_get_clk(&cpu_clk_cell->rk_cell_parent->cell, RT_NULL),
            &cpu_clk_cell->notifier);
}
