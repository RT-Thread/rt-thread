/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk-rk-divider.h"

struct clk_rate_request
{
    rt_ubase_t rate;
    rt_ubase_t best_parent_rate;
    struct rt_clk_cell *best_parent_cell;
};

#define clk_div_mask(width) ((1 << (width)) - 1)

rt_inline rt_uint32_t clk_div_readl(struct rockchip_clk_cell *rk_cell)
{
    void *base = rk_cell->provider->reg_base;

    base += rk_cell->div_offset ? : rk_cell->muxdiv_offset;

    if (rk_cell->div_flags & CLK_DIVIDER_BIG_ENDIAN)
    {
        return rt_be32_to_cpu(HWREG32(base));
    }

    return HWREG32(base);
}

rt_inline void clk_div_writel(struct rockchip_clk_cell *rk_cell, rt_uint32_t val)
{
    void *base = rk_cell->provider->reg_base;

    base += rk_cell->div_offset ? : rk_cell->muxdiv_offset;

    if (rk_cell->div_flags & CLK_DIVIDER_BIG_ENDIAN)
    {
        HWREG32(base) = rt_cpu_to_be32(val);
    }
    else
    {
        HWREG32(base) = val;
    }
}

static rt_uint32_t _get_table_maxdiv(const struct clk_div_table *table, rt_uint8_t width)
{
    rt_uint32_t maxdiv = 0, mask = clk_div_mask(width);
    const struct clk_div_table *clkt;

    for (clkt = table; clkt->div; ++clkt)
    {
        if (clkt->div > maxdiv && clkt->val <= mask)
        {
            maxdiv = clkt->div;
        }
    }
    return maxdiv;
}

static rt_uint32_t _get_table_mindiv(const struct clk_div_table *table)
{
    rt_uint32_t mindiv = RT_UINT32_MAX;
    const struct clk_div_table *clkt;

    for (clkt = table; clkt->div; ++clkt)
    {
        if (clkt->div < mindiv)
        {
            mindiv = clkt->div;
        }
    }
    return mindiv;
}

static rt_uint32_t _get_maxdiv(const struct clk_div_table *table, rt_uint8_t width, rt_ubase_t flags)
{
    if (flags & CLK_DIVIDER_ONE_BASED)
    {
        return clk_div_mask(width);
    }
    if (flags & CLK_DIVIDER_POWER_OF_TWO)
    {
        return 1 << clk_div_mask(width);
    }
    if (table)
    {
        return _get_table_maxdiv(table, width);
    }

    return clk_div_mask(width) + 1;
}

static rt_uint32_t _get_table_div(const struct clk_div_table *table, rt_uint32_t val)
{
    const struct clk_div_table *clkt;

    for (clkt = table; clkt->div; ++clkt)
    {
        if (clkt->val == val)
        {
            return clkt->div;
        }
    }

    return 0;
}

static rt_uint32_t _get_div(const struct clk_div_table *table,
        rt_uint32_t val, rt_ubase_t flags, rt_uint8_t width)
{
    if (flags & CLK_DIVIDER_ONE_BASED)
    {
        return val;
    }
    if (flags & CLK_DIVIDER_POWER_OF_TWO)
    {
        return 1 << val;
    }
    if (flags & CLK_DIVIDER_MAX_AT_ZERO)
    {
        return val ? val : clk_div_mask(width) + 1;
    }
    if (table)
    {
        return _get_table_div(table, val);
    }
    return val + 1;
}

static rt_uint32_t _get_table_val(const struct clk_div_table *table, rt_uint32_t div)
{
    const struct clk_div_table *clkt;

    for (clkt = table; clkt->div; ++clkt)
    {
        if (clkt->div == div)
        {
            return clkt->val;
        }
    }

    return 0;
}

static rt_uint32_t _get_val(const struct clk_div_table *table,
        rt_uint32_t div, rt_ubase_t flags, rt_uint8_t width)
{
    if (flags & CLK_DIVIDER_ONE_BASED)
    {
        return div;
    }
    if (flags & CLK_DIVIDER_POWER_OF_TWO)
    {
        return __rt_ffs(div) - 1;
    }
    if (flags & CLK_DIVIDER_MAX_AT_ZERO)
    {
        return (div == clk_div_mask(width) + 1) ? 0 : div;
    }
    if (table)
    {
        return  _get_table_val(table, div);
    }
    return div - 1;
}

static int _round_up_table(const struct clk_div_table *table, int div)
{
    int up = RT_UINT32_MAX >> 1;
    const struct clk_div_table *clkt;

    for (clkt = table; clkt->div; ++clkt)
    {
        if (clkt->div == div)
        {
            return clkt->div;
        }
        else if (clkt->div < div)
        {
            continue;
        }

        if (clkt->div - div < up - div)
        {
            up = clkt->div;
        }
    }

    return up;
}

static int _round_down_table(const struct clk_div_table *table, int div)
{
    int down = _get_table_mindiv(table);
    const struct clk_div_table *clkt;

    for (clkt = table; clkt->div; ++clkt)
    {
        if (clkt->div == div)
        {
            return clkt->div;
        }
        else if (clkt->div > div)
        {
            continue;
        }

        if (div - clkt->div < div - down)
        {
            down = clkt->div;
        }
    }

    return down;
}

static int _div_round_up(const struct clk_div_table *table,
        rt_ubase_t parent_rate, rt_ubase_t rate, rt_ubase_t flags)
{
    int div = RT_DIV_ROUND_UP_ULL((rt_uint64_t)parent_rate, rate);

    if (flags & CLK_DIVIDER_POWER_OF_TWO)
    {
        div = __roundup_pow_of_two(div);
    }
    if (table)
    {
        div = _round_up_table(table, div);
    }

    return div;
}

static int _div_round_closest(const struct clk_div_table *table,
        rt_ubase_t parent_rate, rt_ubase_t rate, rt_ubase_t flags)
{
    int up, down;
    rt_ubase_t up_rate, down_rate;

    up = RT_DIV_ROUND_UP_ULL((rt_uint64_t)parent_rate, rate);
    down = parent_rate / rate;

    if (flags & CLK_DIVIDER_POWER_OF_TWO)
    {
        up = __roundup_pow_of_two(up);
        down = __rounddown_pow_of_two(down);
    }
    else if (table)
    {
        up = _round_up_table(table, up);
        down = _round_down_table(table, down);
    }

    up_rate = RT_DIV_ROUND_UP_ULL((rt_uint64_t)parent_rate, up);
    down_rate = RT_DIV_ROUND_UP_ULL((rt_uint64_t)parent_rate, down);

    return (rate - up_rate) <= (down_rate - rate) ? up : down;
}

static int _div_round(const struct clk_div_table *table,
        rt_ubase_t parent_rate, rt_ubase_t rate, rt_ubase_t flags)
{
    if (flags & CLK_DIVIDER_ROUND_CLOSEST)
    {
        return _div_round_closest(table, parent_rate, rate, flags);
    }

    return _div_round_up(table, parent_rate, rate, flags);
}

static rt_bool_t _is_best_div(rt_ubase_t rate, rt_ubase_t now, rt_ubase_t best, rt_ubase_t flags)
{
    if (flags & CLK_DIVIDER_ROUND_CLOSEST)
    {
        return rt_abs(rate - now) < rt_abs(rate - best);
    }

    return now <= rate && now > best;
}

static int _next_div(const struct clk_div_table *table, int div, rt_ubase_t flags)
{
    ++div;

    if (flags & CLK_DIVIDER_POWER_OF_TWO)
    {
        return __roundup_pow_of_two(div);
    }
    if (table)
    {
        return _round_up_table(table, div);
    }

    return div;
}

static int clk_divider_bestdiv(struct rt_clk_cell *cell, struct rt_clk_cell *parent,
        rt_ubase_t rate, rt_ubase_t *best_parent_rate,
        const struct clk_div_table *table, rt_uint8_t width, rt_ubase_t flags)
{
    int bestdiv = 0;
    rt_ubase_t parent_rate, best = 0, now, maxdiv, parent_rate_saved = *best_parent_rate;

    if (!rate)
    {
        rate = 1;
    }

    maxdiv = _get_maxdiv(table, width, flags);

    if (!(cell->flags & RT_CLK_F_SET_RATE_PARENT))
    {
        parent_rate = *best_parent_rate;
        bestdiv = _div_round(table, parent_rate, rate, flags);
        bestdiv = bestdiv == 0 ? 1 : bestdiv;
        bestdiv = bestdiv > maxdiv ? maxdiv : bestdiv;
        return bestdiv;
    }

    /*
     * The maximum divider we can use without overflowing
     * rt_ubase_t in rate * i below
     */
    maxdiv = rt_min((~0UL) / rate, maxdiv);

    for (int i = _next_div(table, 0, flags); i <= maxdiv; i = _next_div(table, i, flags))
    {
        if (rate * i == parent_rate_saved)
        {
            /*
             * It's the most ideal case if the requested rate can be
             * divided from parent clock without needing to change
             * parent rate, so return the divider immediately.
             */
            *best_parent_rate = parent_rate_saved;
            return i;
        }

        parent_rate = rt_clk_cell_round_rate(parent, rate * i);
        now = RT_DIV_ROUND_UP_ULL((rt_uint64_t)parent_rate, i);

        if (_is_best_div(rate, now, best, flags))
        {
            bestdiv = i;
            best = now;
            *best_parent_rate = parent_rate;
        }
    }

    if (!bestdiv)
    {
        bestdiv = _get_maxdiv(table, width, flags);
        *best_parent_rate = rt_clk_cell_round_rate(parent, 1);
    }

    return bestdiv;
}

rt_inline rt_bool_t is_power_of_2(rt_ubase_t n)
{
    return (n != 0 && ((n & (n - 1)) == 0));
}

static rt_bool_t _is_valid_table_div(const struct clk_div_table *table, rt_uint32_t div)
{
    const struct clk_div_table *clkt;

    for (clkt = table; clkt->div; ++clkt)
    {
        if (clkt->div == div)
        {
            return RT_TRUE;
        }
    }
    return RT_FALSE;
}

static rt_bool_t _is_valid_div(const struct clk_div_table *table, rt_uint32_t div, rt_ubase_t flags)
{
    if (flags & CLK_DIVIDER_POWER_OF_TWO)
    {
        return is_power_of_2(div);
    }

    if (table)
    {
        return _is_valid_table_div(table, div);
    }

    return RT_TRUE;
}

static int divider_get_val(rt_ubase_t rate, rt_ubase_t parent_rate,
        const struct clk_div_table *table, rt_uint8_t width, rt_ubase_t flags)
{
    rt_uint32_t div, value;

    div = RT_DIV_ROUND_UP_ULL((rt_uint64_t)parent_rate, rate);

    if (!_is_valid_div(table, div, flags))
    {
        return -RT_EINVAL;
    }

    value = _get_val(table, div, flags, width);

    return rt_min_t(rt_uint32_t, value, clk_div_mask(width));
}

static int divider_determine_rate(struct rt_clk_cell *cell, struct clk_rate_request *req,
        const struct clk_div_table *table, rt_uint8_t width, rt_ubase_t flags)
{
    int div;

    div = clk_divider_bestdiv(cell, req->best_parent_cell, req->rate,
            &req->best_parent_rate, table, width, flags);

    req->rate = RT_DIV_ROUND_UP_ULL((rt_uint64_t)req->best_parent_rate, div);

    return 0;
}

static int divider_ro_determine_rate(struct rt_clk_cell *cell, struct clk_rate_request *req,
        const struct clk_div_table *table, rt_uint8_t width, rt_ubase_t flags, rt_uint32_t val)
{
    int div;

    div = _get_div(table, val, flags, width);

    /* Even a read-only clock can propagate a rate change */
    if (cell->flags & RT_CLK_F_SET_RATE_PARENT)
    {
        if (!req->best_parent_cell)
        {
            return -RT_EINVAL;
        }

        req->best_parent_rate = rt_clk_cell_round_rate(req->best_parent_cell, req->rate * div);
    }

    req->rate = RT_DIV_ROUND_UP_ULL((rt_uint64_t)req->best_parent_rate, div);

    return 0;
}

static long divider_round_rate_parent(struct rt_clk_cell *cell, struct rt_clk_cell *parent,
        rt_ubase_t rate, rt_ubase_t *prate,
        const struct clk_div_table *table, rt_uint8_t width, rt_ubase_t flags)
{
    int ret;
    struct clk_rate_request req;

    req.rate = rate;
    req.best_parent_rate = *prate;
    req.best_parent_cell = parent;

    if ((ret = divider_determine_rate(cell, &req, table, width, flags)))
    {
        return ret;
    }

    *prate = req.best_parent_rate;

    return req.rate;
}

static long divider_ro_round_rate_parent(struct rt_clk_cell *cell, struct rt_clk_cell *parent,
        rt_ubase_t rate, rt_ubase_t *prate,
        const struct clk_div_table *table, rt_uint8_t width, rt_ubase_t flags, rt_uint32_t val)
{
    int ret;
    struct clk_rate_request req;

    req.rate = rate;
    req.best_parent_rate = *prate;
    req.best_parent_cell = parent;

    if ((ret = divider_ro_determine_rate(cell, &req, table, width, flags, val)))
    {
        return ret;
    }

    *prate = req.best_parent_rate;

    return req.rate;
}

static rt_ubase_t divider_recalc_rate(rt_ubase_t parent_rate, rt_uint32_t val,
        const struct clk_div_table *table, rt_ubase_t flags, rt_ubase_t width)
{
    rt_uint32_t div = _get_div(table, val, flags, width);

    if (!div)
    {
        return parent_rate;
    }

    return RT_DIV_ROUND_UP_ULL((rt_uint64_t)parent_rate, div);
}

static rt_ubase_t clk_divider_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    rt_uint32_t val;
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    val = clk_div_readl(rk_cell) >> rk_cell->div_shift;
    val &= clk_div_mask(rk_cell->div_width);

    return divider_recalc_rate(parent_rate, val,
            rk_cell->div_table, rk_cell->div_flags, rk_cell->div_width);
}

static rt_base_t clk_divider_round_rate(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t *prate)
{
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    if (rk_cell->div_flags & CLK_DIVIDER_READ_ONLY)
    {
        rt_uint32_t val;

        val = clk_div_readl(rk_cell) >> rk_cell->div_shift;
        val &= clk_div_mask(rk_cell->div_width);

        return divider_ro_round_rate_parent(cell, rt_clk_cell_get_parent(cell),
                rate, prate, rk_cell->div_table,
                rk_cell->div_width, rk_cell->div_flags, val);
    }

    return divider_round_rate_parent(cell, rt_clk_cell_get_parent(cell),
            rate, prate, rk_cell->div_table,
            rk_cell->div_width, rk_cell->div_flags);
}

static rt_err_t clk_divider_set_rate(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t parent_rate)
{
    int value;
    rt_uint32_t val;
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    value = divider_get_val(rate, parent_rate,
            rk_cell->div_table, rk_cell->div_width, rk_cell->div_flags);

    if (value < 0)
    {
        return value;
    }

    if (rk_cell->div_flags & CLK_DIVIDER_HIWORD_MASK)
    {
        val = clk_div_mask(rk_cell->div_width) << (rk_cell->div_shift + 16);
    }
    else
    {
        val = clk_div_readl(rk_cell);
        val &= ~(clk_div_mask(rk_cell->div_width) << rk_cell->div_shift);
    }
    val |= (rt_uint32_t)value << rk_cell->div_shift;
    clk_div_writel(rk_cell, val);

    return 0;
}

const struct rt_clk_ops clk_divider_ops =
{
    .recalc_rate = clk_divider_recalc_rate,
    .round_rate = clk_divider_round_rate,
    .set_rate = clk_divider_set_rate,
};

const struct rt_clk_ops clk_divider_ro_ops =
{
    .recalc_rate = clk_divider_recalc_rate,
    .round_rate = clk_divider_round_rate,
};

void rockchip_divider_clk_cell_init(struct rockchip_clk_cell *rk_cell)
{
    if (rk_cell->div_flags & CLK_DIVIDER_READ_ONLY)
    {
        rk_cell->cell.ops = &clk_divider_ro_ops;
    }
    else
    {
        rk_cell->cell.ops = &clk_divider_ops;
    }
}
