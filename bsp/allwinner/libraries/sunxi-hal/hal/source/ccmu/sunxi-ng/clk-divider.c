// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2011 Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>
 * Copyright (C) 2011 Richard Zhao, Linaro <richard.zhao@linaro.org>
 * Copyright (C) 2011-2012 Mike Turquette, Linaro Ltd <mturquette@linaro.org>
 *
 * Adjustable divider clock implementation
 */
#include "ccu.h"
#include <stdlib.h>
/*
 * DOC: basic adjustable divider clock that cannot gate
 *
 * Traits of this clock:
 * prepare - clk_prepare only ensures that parents are prepared
 * enable - clk_enable only ensures that parents are enabled
 * rate - rate is adjustable.  clk->rate = ceiling(parent->rate / divisor)
 * parent - fixed parent.  No clk_set_parent support
 */

static inline u32 clk_div_readl(struct clk_divider *divider)
{
    return readl(divider->reg);
}

static inline void clk_div_writel(struct clk_divider *divider, u32 val)
{
    writel(val, divider->reg);
}

static unsigned int _get_table_maxdiv(const struct clk_div_table *table,
                                      u8 width)
{
    unsigned int maxdiv = 0, mask = clk_div_mask(width);
    const struct clk_div_table *clkt;

    for (clkt = table; clkt->div; clkt++)
        if (clkt->div > maxdiv && clkt->val <= mask)
        {
            maxdiv = clkt->div;
        }
    return maxdiv;
}

static unsigned int _get_table_mindiv(const struct clk_div_table *table)
{
    unsigned int mindiv = UINT_MAX;
    const struct clk_div_table *clkt;

    for (clkt = table; clkt->div; clkt++)
        if (clkt->div < mindiv)
        {
            mindiv = clkt->div;
        }
    return mindiv;
}

static unsigned int _get_maxdiv(const struct clk_div_table *table, u8 width,
                                unsigned long flags)
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

static unsigned int _get_table_div(const struct clk_div_table *table,
                                   unsigned int val)
{
    const struct clk_div_table *clkt;

    for (clkt = table; clkt->div; clkt++)
        if (clkt->val == val)
        {
            return clkt->div;
        }
    return 0;
}

static unsigned int _get_div(const struct clk_div_table *table,
                             unsigned int val, unsigned long flags, u8 width)
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

static unsigned int _get_table_val(const struct clk_div_table *table,
                                   unsigned int div)
{
    const struct clk_div_table *clkt;

    for (clkt = table; clkt->div; clkt++)
        if (clkt->div == div)
        {
            return clkt->val;
        }
    return 0;
}

static inline int __ffs(uint32_t value)
{
    uint32_t offset;

    for (offset = 0; offset < sizeof(value) * 8; offset++)
    {
        if (value & (1 << offset))
        {
            return offset;
        }
    }
    return -1;
}

static unsigned int _get_val(const struct clk_div_table *table,
                             unsigned int div, unsigned long flags, u8 width)
{
    if (flags & CLK_DIVIDER_ONE_BASED)
    {
        return div;
    }
    if (flags & CLK_DIVIDER_POWER_OF_TWO)
    {
        return __ffs(div);
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

unsigned long divider_recalc_rate(struct clk_hw *hw, unsigned long parent_rate,
                                  unsigned int val,
                                  const struct clk_div_table *table,
                                  unsigned long flags, unsigned long width)
{
    unsigned int div;

    div = _get_div(table, val, flags, width);
    if (!div)
    {
        return parent_rate;
    }

    return DIV_ROUND_UP_ULL((u64)parent_rate, div);
}

static unsigned long clk_divider_recalc_rate(struct clk_hw *hw,
        unsigned long parent_rate)
{
    struct clk_divider *divider = to_clk_divider(hw);
    unsigned int val;

    val = clk_div_readl(divider) >> divider->shift;
    val &= clk_div_mask(divider->width);

    return divider_recalc_rate(hw, parent_rate, val, divider->table,
                               divider->flags, divider->width);
}

static bool _is_valid_table_div(const struct clk_div_table *table,
                                unsigned int div)
{
    const struct clk_div_table *clkt;

    for (clkt = table; clkt->div; clkt++)
        if (clkt->div == div)
        {
            return true;
        }
    return false;
}

static int is_power_of_2(unsigned long n)
{
    return (n != 0 && ((n & (n - 1)) == 0));
}

static bool _is_valid_div(const struct clk_div_table *table, unsigned int div,
                          unsigned long flags)
{
    if (flags & CLK_DIVIDER_POWER_OF_TWO)
    {
        return is_power_of_2(div);
    }
    if (table)
    {
        return _is_valid_table_div(table, div);
    }
    return true;
}

static int _round_up_table(const struct clk_div_table *table, int div)
{
    const struct clk_div_table *clkt;
    int up = INT_MAX;

    for (clkt = table; clkt->div; clkt++)
    {
        if (clkt->div == div)
        {
            return clkt->div;
        }
        else if (clkt->div < div)
        {
            continue;
        }

        if ((clkt->div - div) < (up - div))
        {
            up = clkt->div;
        }
    }

    return up;
}

static int _round_down_table(const struct clk_div_table *table, int div)
{
    const struct clk_div_table *clkt;
    int down = _get_table_mindiv(table);

    for (clkt = table; clkt->div; clkt++)
    {
        if (clkt->div == div)
        {
            return clkt->div;
        }
        else if (clkt->div > div)
        {
            continue;
        }

        if ((div - clkt->div) < (div - down))
        {
            down = clkt->div;
        }
    }

    return down;
}

int fls(int val)
{
    int  bit = 32;

    if (!val)
        return 0;
    if (!(val & 0xffff0000u))
    {
        val <<= 16;
        bit -= 16;
    }
    if (!(val & 0xff000000u))
    {
        val <<= 8;
        bit -= 8;
    }
    if (!(val & 0xf0000000u))
    {
        val <<= 4;
        bit -= 4;
    }
    if (!(val & 0xc0000000u))
    {
        val <<= 2;
        bit -= 2;
    }
    if (!(val & 0x80000000u))
    {
        bit -= 1;
    }

    return bit;
}

static int __roundup_pow_of_two(unsigned int x)
{
    return 1UL << fls(x - 1);
}

static int __rounddown_pow_of_two(unsigned int x)
{
    return (1UL << fls(x - 1)) / 2;
}

static int _div_round_up(const struct clk_div_table *table,
                         unsigned long parent_rate, unsigned long rate,
                         unsigned long flags)
{
    int div = DIV_ROUND_UP_ULL((u64)parent_rate, rate);

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
                              unsigned long parent_rate, unsigned long rate,
                              unsigned long flags)
{
    int up, down;
    unsigned long up_rate, down_rate;

    up = DIV_ROUND_UP_ULL((u64)parent_rate, rate);
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

    up_rate = DIV_ROUND_UP_ULL((u64)parent_rate, up);
    down_rate = DIV_ROUND_UP_ULL((u64)parent_rate, down);

    return (rate - up_rate) <= (down_rate - rate) ? up : down;
}

static int _div_round(const struct clk_div_table *table,
                      unsigned long parent_rate, unsigned long rate,
                      unsigned long flags)
{
    if (flags & CLK_DIVIDER_ROUND_CLOSEST)
    {
        return _div_round_closest(table, parent_rate, rate, flags);
    }

    return _div_round_up(table, parent_rate, rate, flags);
}

static bool _is_best_div(unsigned long rate, unsigned long now,
                         unsigned long best, unsigned long flags)
{
    if (flags & CLK_DIVIDER_ROUND_CLOSEST)
    {
        return abs(rate - now) < abs(rate - best);
    }

    return now <= rate && now > best;
}

static int _next_div(const struct clk_div_table *table, int div,
                     unsigned long flags)
{
    div++;

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

static int clk_divider_bestdiv(struct clk_hw *hw, struct clk_hw *parent,
                               unsigned long rate,
                               unsigned long *best_parent_rate,
                               const struct clk_div_table *table, u8 width,
                               unsigned long flags)
{
    int i, bestdiv = 0;
    unsigned long parent_rate, best = 0, now, maxdiv;
    unsigned long parent_rate_saved = *best_parent_rate;

    if (!rate)
    {
        rate = 1;
    }

    maxdiv = _get_maxdiv(table, width, flags);

    if (!(clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT))
    {
        parent_rate = *best_parent_rate;
        bestdiv = _div_round(table, parent_rate, rate, flags);
        bestdiv = bestdiv == 0 ? 1 : bestdiv;
        bestdiv = bestdiv > maxdiv ? maxdiv : bestdiv;
        return bestdiv;
    }

    /*
     * The maximum divider we can use without overflowing
     * unsigned long in rate * i below
     */
    maxdiv = min(ULONG_MAX / rate, maxdiv);

    for (i = _next_div(table, 0, flags); i <= maxdiv;
         i = _next_div(table, i, flags))
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
        parent_rate = clk_hw_round_rate(parent, rate * i);
        now = DIV_ROUND_UP_ULL((u64)parent_rate, i);
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
        *best_parent_rate = clk_hw_round_rate(parent, 1);
    }

    return bestdiv;
}

long divider_round_rate_parent(struct clk_hw *hw, struct clk_hw *parent,
                               unsigned long rate, unsigned long *prate,
                               const struct clk_div_table *table,
                               u8 width, unsigned long flags)
{
    int div;

    div = clk_divider_bestdiv(hw, parent, rate, prate, table, width, flags);

    return DIV_ROUND_UP_ULL((u64) * prate, div);
}

long divider_ro_round_rate_parent(struct clk_hw *hw, struct clk_hw *parent,
                                  unsigned long rate, unsigned long *prate,
                                  const struct clk_div_table *table, u8 width,
                                  unsigned long flags, unsigned int val)
{
    int div;

    div = _get_div(table, val, flags, width);

    /* Even a read-only clock can propagate a rate change */
    if (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)
    {
        if (!parent)
        {
            return -1;
        }

        *prate = clk_hw_round_rate(parent, rate * div);
    }

    return DIV_ROUND_UP_ULL((u64) * prate, div);
}

static long clk_divider_round_rate(struct clk_hw *hw, unsigned long rate,
                                   unsigned long *prate)
{
    struct clk_divider *divider = to_clk_divider(hw);

    /* if read only, just return current value */
    if (divider->flags & CLK_DIVIDER_READ_ONLY)
    {
        u32 val;

        val = clk_div_readl(divider) >> divider->shift;
        val &= clk_div_mask(divider->width);

        return divider_ro_round_rate(hw, rate, prate, divider->table,
                                     divider->width, divider->flags,
                                     val);
    }

    return divider_round_rate(hw, rate, prate, divider->table,
                              divider->width, divider->flags);
}

int divider_get_val(unsigned long rate, unsigned long parent_rate,
                    const struct clk_div_table *table, u8 width,
                    unsigned long flags)
{
    unsigned int div, value;

    div = DIV_ROUND_UP_ULL((u64)parent_rate, rate);

    if (!_is_valid_div(table, div, flags))
    {
        return -1;
    }

    value = _get_val(table, div, flags, width);

    return min(value, clk_div_mask(width));
}

static int clk_divider_set_rate(struct clk_hw *hw, unsigned long rate,
                                unsigned long parent_rate)
{
    struct clk_divider *divider = to_clk_divider(hw);
    int value;
    u32 val;
    u32 __cspr;

    value = divider_get_val(rate, parent_rate, divider->table,
                            divider->width, divider->flags);
    if (value < 0)
    {
        return value;
    }

    __cspr = hal_spin_lock_irqsave(&divider->lock);

    if (divider->flags & CLK_DIVIDER_HIWORD_MASK)
    {
        val = clk_div_mask(divider->width) << (divider->shift + 16);
    }
    else
    {
        val = clk_div_readl(divider);
        val &= ~(clk_div_mask(divider->width) << divider->shift);
    }
    val |= (u32)value << divider->shift;
    clk_div_writel(divider, val);

    hal_spin_unlock_irqrestore(&divider->lock, __cspr);

    return 0;
}

const struct clk_ops clk_divider_ops =
{
    .recalc_rate = clk_divider_recalc_rate,
    .round_rate = clk_divider_round_rate,
    .set_rate = clk_divider_set_rate,
};

const struct clk_ops clk_divider_ro_ops =
{
    .recalc_rate = clk_divider_recalc_rate,
    .round_rate = clk_divider_round_rate,
};

static struct clk_hw *_register_divider(const char *name,
                                        const char *parent_name, unsigned long flags,
                                        u32 reg, u8 shift, u8 width,
                                        u8 clk_divider_flags, const struct clk_div_table *table,
                                        hal_spinlock_t lock)
{
    struct clk_divider *div;
    struct clk_hw *hw;
    struct clk_init_data init;
    int ret;

    if (clk_divider_flags & CLK_DIVIDER_HIWORD_MASK)
    {
        if (width + shift > 16)
        {
            return NULL;
        }
    }

    div = malloc(sizeof(*div));
    if (!div)
    {
        return NULL;
    }

    init.name = name;
    if (clk_divider_flags & CLK_DIVIDER_READ_ONLY)
    {
        init.ops = &clk_divider_ro_ops;
    }
    else
    {
        init.ops = &clk_divider_ops;
    }
    init.flags = flags;
    init.parent_names = (parent_name ? &parent_name : NULL);
    init.num_parents = (parent_name ? 1 : 0);

    /* struct clk_divider assignments */
    div->reg = reg;
    div->shift = shift;
    div->width = width;
    div->flags = clk_divider_flags;
    div->lock = lock;
    div->hw.init = &init;
    div->table = table;

    /* register the clock */
    hw = &(div->hw);
    ret = clk_hw_register(hw);
    if (ret)
    {
        free(div);
        hw = NULL;
    }

    return hw;
}

/**
 * clk_hw_register_divider - register a divider clock with the clock framework
 * @name: name of this clock
 * @parent_name: name of clock's parent
 * @flags: framework-specific flags
 * @reg: register address to adjust divider
 * @shift: number of bits to shift the bitfield
 * @width: width of the bitfield
 * @clk_divider_flags: divider-specific flags for this clock
 * @lock: shared register lock for this clock
 */
struct clk_hw *clk_hw_register_divider(const char *name,
                                       const char *parent_name, unsigned long flags,
                                       u32 reg, u8 shift, u8 width,
                                       u8 clk_divider_flags, hal_spinlock_t lock)
{
    return _register_divider(name, parent_name, flags, reg, shift,
                             width, clk_divider_flags, NULL, lock);
}

/**
 * clk_hw_register_divider_table - register a table based divider clock with
 * the clock framework
 * @name: name of this clock
 * @parent_name: name of clock's parent
 * @flags: framework-specific flags
 * @reg: register address to adjust divider
 * @shift: number of bits to shift the bitfield
 * @width: width of the bitfield
 * @clk_divider_flags: divider-specific flags for this clock
 * @table: array of divider/value pairs ending with a div set to 0
 * @lock: shared register lock for this clock
 */
struct clk_hw *clk_hw_register_divider_table(const char *name,
        const char *parent_name, unsigned long flags,
        u32 reg, u8 shift, u8 width,
        u8 clk_divider_flags, const struct clk_div_table *table,
        hal_spinlock_t lock)
{
    return _register_divider(name, parent_name, flags, reg, shift,
                             width, clk_divider_flags, table, lock);
}

/**
 * clk_hw_unregister_divider - unregister a clk divider
 * @hw: hardware-specific clock data to unregister
 */
void clk_hw_unregister_divider(struct clk_hw *hw)
{
    struct clk_divider *div;

    div = to_clk_divider(hw);

    clk_hw_unregister(hw);
    free(div);
}
