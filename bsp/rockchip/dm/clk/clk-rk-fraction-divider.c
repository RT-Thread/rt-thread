/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk-rk-fraction-divider.h"
#include "clk-rk-mux.h"
#include "clk-rk-gate.h"

struct u32_fract
{
    rt_uint32_t numerator;
    rt_uint32_t denominator;
};

#define CLK_FD_MSHIFT   16
#define CLK_FD_MWIDTH   16
#define CLK_FD_NSHIFT   0
#define CLK_FD_NWIDTH   16

rt_inline rt_uint32_t clk_fd_readl(struct rockchip_clk_cell *rk_cell)
{
    void *base = rk_cell->provider->reg_base;

    if (rk_cell->div_flags & CLK_FRAC_DIVIDER_BIG_ENDIAN)
    {
        return rt_be32_to_cpu(HWREG32(base + rk_cell->muxdiv_offset));
    }

    return HWREG32(base + rk_cell->muxdiv_offset);
}

rt_inline void clk_fd_writel(struct rockchip_clk_cell *rk_cell, rt_uint32_t val)
{
    void *base = rk_cell->provider->reg_base;

    if (rk_cell->div_flags & CLK_FRAC_DIVIDER_BIG_ENDIAN)
    {
        HWREG32(base + rk_cell->muxdiv_offset) = rt_cpu_to_be32(val);
    }
    else
    {
        HWREG32(base + rk_cell->muxdiv_offset) = val;
    }
}

static void clk_fd_get_div(struct rt_clk_cell *cell, struct u32_fract *fract)
{
    rt_ubase_t m, n;
    rt_uint32_t val, mmask, nmask;
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    val = clk_fd_readl(rk_cell);

    mmask = RT_GENMASK(CLK_FD_MWIDTH - 1, 0) << CLK_FD_MSHIFT;
    nmask = RT_GENMASK(CLK_FD_NWIDTH - 1, 0) << CLK_FD_NSHIFT;

    m = (val & mmask) >> CLK_FD_MSHIFT;
    n = (val & nmask) >> CLK_FD_NSHIFT;

    if (rk_cell->div_flags & CLK_FRAC_DIVIDER_ZERO_BASED)
    {
        ++m;
        ++n;
    }

    fract->numerator = m;
    fract->denominator = n;
}

static rt_ubase_t clk_fd_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    rt_uint64_t ret;
    struct u32_fract fract;

    clk_fd_get_div(cell, &fract);

    if (!fract.numerator || !fract.denominator)
    {
        return parent_rate;
    }

    ret = (rt_uint64_t)parent_rate * fract.numerator;
    rt_do_div(ret, fract.denominator);

    return ret;
}

static void clk_fractional_divider_general_approximation(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t *parent_rate, rt_ubase_t *m, rt_ubase_t *n)
{
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    /*
     * Get rate closer to *parent_rate to guarantee there is no overflow
     * for m and n. In the result it will be the nearest rate left shifted
     * by (scale - CLK_FD_NWIDTH) bits.
     *
     * For the detailed explanation see the top comment in this file.
     */
    if (rk_cell->div_flags & CLK_FRAC_DIVIDER_POWER_OF_TWO_PS)
    {
        rt_ubase_t scale = fls_long(*parent_rate / rate - 1);

        if (scale > CLK_FD_NWIDTH)
        {
            rate <<= scale - CLK_FD_NWIDTH;
        }
    }

    rational_best_approximation(rate, *parent_rate,
            RT_GENMASK(CLK_FD_MWIDTH - 1, 0), RT_GENMASK(CLK_FD_NWIDTH - 1, 0), m, n);
}

/*
 * fractional divider must set that denominator is 20 times larger than
 * numerator to generate precise clock frequency.
 */
static void rockchip_fractional_approximation(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t *parent_rate, rt_ubase_t *m, rt_ubase_t *n)
{
    struct rt_clk_cell *p_parent;
    rt_ubase_t p_rate, p_parent_rate;
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    if (rate == 0)
    {
        *m = 0;
        *n = 1;
        return;
    }

    p_rate = rt_clk_cell_get_rate(rt_clk_cell_get_parent(cell));

    if (rate * 20 > p_rate && p_rate % rate != 0)
    {
        p_parent = rt_clk_cell_get_parent(rt_clk_cell_get_parent(cell));

        if (!p_parent)
        {
            *parent_rate = p_rate;
        }
        else
        {
            p_parent_rate = rt_clk_cell_get_rate(p_parent);
            *parent_rate = p_parent_rate;
        }

        if (*parent_rate == 0)
        {
            *m = 0;
            *n = 1;
            return;
        }

        if (*parent_rate < rate * 20)
        {
            /*
             * Fractional frequency divider to do
             * integer frequency divider does not need 20 times the limit.
             */
            if (!(*parent_rate % rate))
            {
                *m = 1;
                *n = *parent_rate / rate;
                return;
            }
            else if (!(rk_cell->div_flags & CLK_FRAC_DIVIDER_NO_LIMIT))
            {
                *m = 0;
                *n = 1;
                return;
            }
        }
    }

    rk_cell->div_flags |= CLK_FRAC_DIVIDER_POWER_OF_TWO_PS;

    clk_fractional_divider_general_approximation(cell, rate, parent_rate, m, n);
}

static rt_base_t clk_fd_round_rate(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t *parent_rate)
{
    rt_ubase_t m, n;
    rt_uint64_t ret;

    if (!rate || rate >= *parent_rate)
    {
        return *parent_rate;
    }

    rockchip_fractional_approximation(cell, rate, parent_rate, &m, &n);

    ret = (rt_uint64_t)*parent_rate * m;
    rt_do_div(ret, n);

    return ret;
}

static rt_err_t clk_fd_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_ubase_t m, n;
    rt_uint32_t mmask, nmask, val;
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    rational_best_approximation(rate, parent_rate,
            RT_GENMASK(CLK_FD_MWIDTH - 1, 0), RT_GENMASK(CLK_FD_NWIDTH - 1, 0), &m, &n);

    if (rk_cell->div_flags & CLK_FRAC_DIVIDER_ZERO_BASED)
    {
        --m;
        --n;
    }

    mmask = RT_GENMASK(CLK_FD_MWIDTH - 1, 0) << CLK_FD_MSHIFT;
    nmask = RT_GENMASK(CLK_FD_NWIDTH - 1, 0) << CLK_FD_NSHIFT;

    /*
     * When compensation the fractional divider,
     * the [1:0] bits of the numerator register are omitted,
     * which will lead to a large deviation in the result.
     * Therefore, it is required that the numerator must
     * be greater than 4.
     *
     * Note that there are some exceptions here:
     * If there is an even frac div, we need to keep the original
     * numerator(<4) and denominator. Otherwise, it may cause the
     * issue that the duty ratio is not 50%.
     */
    if (m < 4 && m != 0)
    {
        if (n % 2 == 0)
        {
            val = 1;
        }
        else
        {
            val = RT_DIV_ROUND_UP(4, m);
        }

        n *= val;
        m *= val;

        if (n > nmask)
        {
            n = nmask;
        }
    }

    mmask = RT_GENMASK(CLK_FD_MWIDTH - 1, 0) << CLK_FD_MSHIFT;
    nmask = RT_GENMASK(CLK_FD_NWIDTH - 1, 0) << CLK_FD_NSHIFT;

    val = clk_fd_readl(rk_cell);
    val &= ~(mmask | nmask);
    val |= (m << CLK_FD_MSHIFT) | (n << CLK_FD_NSHIFT);
    clk_fd_writel(rk_cell, val);

    return RT_EOK;
}

static rt_err_t rockchip_clk_frac_notify(struct rt_clk_notifier *notifier,
        rt_ubase_t msg, rt_ubase_t old_rate, rt_ubase_t new_rate)
{
    struct rt_clk_cell *cell;
    struct rockchip_fraction_divider_clk_cell *fraction_divider_cell;

    fraction_divider_cell = rt_container_of(notifier, struct rockchip_fraction_divider_clk_cell, notifier);
    cell = &fraction_divider_cell->rk_cell_child->cell;

    if (msg == RT_CLK_MSG_PRE_RATE_CHANGE)
    {
        fraction_divider_cell->rate_change_idx = cell->ops->get_parent(cell);

        if (fraction_divider_cell->rate_change_idx != fraction_divider_cell->mux_frac_idx)
        {
            cell->ops->set_parent(cell, fraction_divider_cell->mux_frac_idx);
            fraction_divider_cell->rate_change_remuxed = 1;
        }
    }
    else if (msg == RT_CLK_MSG_POST_RATE_CHANGE)
    {
        /*
         * The RT_CLK_MSG_POST_RATE_CHANGE notifier runs directly after the
         * divider clock is set in clk_change_rate, so we'll have
         * remuxed back to the original parent before clk_change_rate
         * reaches the mux itself.
         */
        if (fraction_divider_cell->rate_change_remuxed)
        {
            cell->ops->set_parent(cell, fraction_divider_cell->rate_change_idx);
            fraction_divider_cell->rate_change_remuxed = 0;
        }
    }

    return RT_EOK;
}

static int match_string(const char * const *array, size_t n, const char *string)
{
    for (int index = 0; index < n; ++index)
    {
        const char *item = array[index];

        if (!item)
        {
            break;
        }
        if (!rt_strcmp(item, string))
        {
            return index;
        }
    }

    return -RT_EINVAL;
}

void rockchip_fraction_divider_clk_cell_init(struct rockchip_clk_cell *rk_cell)
{
    struct rockchip_fraction_divider_clk_cell *fraction_divider_cell = cell_to_rockchip_fraction_divider_clk_cell(&rk_cell->cell);

    rk_cell->cell.ops = &fraction_divider_cell->ops;
    rk_cell->cell.flags |= RT_CLK_F_SET_RATE_UNGATE;

    if (fraction_divider_cell->rk_cell_child)
    {
        struct rockchip_clk_cell *rk_cell_child = fraction_divider_cell->rk_cell_child;
        struct rt_clk_cell *cell = &rk_cell_child->cell;

        rk_cell_child->cell.flags |= RT_CLK_F_SET_RATE_PARENT;

        fraction_divider_cell->mux_frac_idx = match_string(cell->parent_names, cell->parents_nr,
                rk_cell->cell.name);

        rockchip_mux_clk_cell_init(rk_cell);

        fraction_divider_cell->ops.get_parent = rockchip_mux_clk_ops.get_parent;
        fraction_divider_cell->ops.set_parent = rockchip_mux_clk_ops.set_parent;
    }

    if (rk_cell->gate_offset >= 0)
    {
        fraction_divider_cell->ops.enable = rockchip_gate_clk_ops.enable;
        fraction_divider_cell->ops.disable = rockchip_gate_clk_ops.disable;
        fraction_divider_cell->ops.is_enabled = rockchip_gate_clk_ops.is_enabled;
    }

    fraction_divider_cell->ops.recalc_rate = clk_fd_recalc_rate;
    fraction_divider_cell->ops.round_rate = clk_fd_round_rate;
    fraction_divider_cell->ops.set_rate = clk_fd_set_rate;
}

void rockchip_fraction_divider_clk_cell_setup(struct rockchip_clk_cell *rk_cell)
{
    struct rockchip_fraction_divider_clk_cell *fraction_divider_cell = cell_to_rockchip_fraction_divider_clk_cell(&rk_cell->cell);
    struct rockchip_clk_cell *rk_cell_child = fraction_divider_cell->rk_cell_child;

    if (fraction_divider_cell->mux_frac_idx >= 0)
    {
        fraction_divider_cell->notifier.callback = rockchip_clk_frac_notify;

        rt_clk_notifier_register(rt_clk_cell_get_clk(&rk_cell_child->cell, RT_NULL),
                &fraction_divider_cell->notifier);
    }
}
