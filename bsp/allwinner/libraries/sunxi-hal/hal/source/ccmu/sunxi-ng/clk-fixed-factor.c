// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2011 Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>
 */
#include "ccu.h"

/*
 * DOC: basic fixed multiplier and divider clock that cannot gate
 *
 * Traits of this clock:
 * prepare - clk_prepare only ensures that parents are prepared
 * enable - clk_enable only ensures that parents are enabled
 * rate - rate is fixed.  clk->rate = parent->rate / div * mult
 * parent - fixed parent.  No clk_set_parent support
 */

static unsigned long clk_factor_recalc_rate(struct clk_hw *hw,
        unsigned long parent_rate)
{
    struct clk_fixed_factor *fix = to_clk_fixed_factor(hw);
    unsigned long long int rate;

    rate = (unsigned long long int)parent_rate * fix->mult;
    rate /= fix->div;
    return (unsigned long)rate;
}

static long clk_factor_round_rate(struct clk_hw *hw, unsigned long rate,
                                  unsigned long *prate)
{
    struct clk_fixed_factor *fix = to_clk_fixed_factor(hw);

    if (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)
    {
        unsigned long best_parent;

        best_parent = (rate / fix->mult) * fix->div;
        *prate = clk_hw_round_rate(clk_hw_get_parent(hw), best_parent);
    }

    return (*prate / fix->div) * fix->mult;
}

static int clk_factor_set_rate(struct clk_hw *hw, unsigned long rate,
                               unsigned long parent_rate)
{
    struct clk_fixed_factor *fix = to_clk_fixed_factor(hw);
     /*
     * We must report success but we can do so unconditionally because
     * clk_factor_round_rate returns values that ensure this call is a
     * nop.
     */
    if (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)
    {
        unsigned long p_rate;

        p_rate = (rate / fix->mult) * fix->div;
    return clk_hw_set_rate(clk_hw_get_parent(hw), p_rate);

    }

    return 0;
}

const struct clk_ops clk_fixed_factor_ops =
{
    .round_rate = clk_factor_round_rate,
    .set_rate = clk_factor_set_rate,
    .recalc_rate = clk_factor_recalc_rate,
};
