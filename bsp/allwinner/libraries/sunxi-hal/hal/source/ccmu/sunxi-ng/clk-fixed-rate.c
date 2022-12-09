// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2010-2011 Canonical Ltd <jeremy.kerr@canonical.com>
 * Copyright (C) 2011-2012 Mike Turquette, Linaro Ltd <mturquette@linaro.org>
 *
 * Fixed rate clock implementation
 */
#include "ccu.h"
#include "clk-fixed-rate.h"
#include <stdlib.h>
/*
 * DOC: basic fixed-rate clock that cannot gate
 *
 * Traits of this clock:
 * prepare - clk_(un)prepare only ensures parents are prepared
 * enable - clk_enable only ensures parents are enabled
 * rate - rate is always a fixed value.  No clk_set_rate support
 * parent - fixed parent.  No clk_set_parent support
 */

static unsigned long clk_fixed_rate_recalc_rate(struct clk_hw *hw,
        unsigned long parent_rate)
{
    return to_clk_fixed_rate(hw)->fixed_rate;
}

static unsigned long clk_fixed_rate_recalc_accuracy(struct clk_hw *hw,
        unsigned long parent_accuracy)
{
    return to_clk_fixed_rate(hw)->fixed_accuracy;
}

const struct clk_ops clk_fixed_rate_ops =
{
    .recalc_rate = clk_fixed_rate_recalc_rate,
    .recalc_accuracy = clk_fixed_rate_recalc_accuracy,
};

/**
 * clk_hw_register_fixed_rate_with_accuracy - register fixed-rate clock with
 * the clock framework
 * @dev: device that is registering this clock
 * @name: name of this clock
 * @parent_name: name of clock's parent
 * @flags: framework-specific flags
 * @fixed_rate: non-adjustable clock rate
 * @fixed_accuracy: non-adjustable clock rate
 */
int clk_hw_register_fixed_rate_with_accuracy(
    const char *name, u32 id, const char *parent_name, unsigned long flags,
    unsigned long fixed_rate, unsigned long fixed_accuracy)
{
    struct clk_fixed_rate *fixed;
    struct clk_hw *hw;
    struct clk_init_data init;
    int ret;

    /* allocate fixed-rate clock */
    fixed = (struct clk_fixed_rate *)malloc(sizeof(*fixed));
    if (!fixed)
    {
        return -1;
    }

    init.name = name;
    init.ops = &clk_fixed_rate_ops;
    init.flags = flags;
    init.parent_names = (parent_name ? &parent_name : NULL);
    init.num_parents = (parent_name ? 1 : 0);

    /* struct clk_fixed_rate assignments */
    fixed->fixed_rate = fixed_rate;
    fixed->fixed_accuracy = fixed_accuracy;
    fixed->hw.init = &init;

    /* register the clock */
    hw = &fixed->hw;
    hw->type = HAL_SUNXI_FIXED_CCU;
    hw->id = id;
    ret = clk_hw_register(hw);
    if (ret)
    {
        free(fixed);
        hw = NULL;
        return -1;
    }

    return 0;
}

int clk_register_fixed_rate_with_accuracy(const char *name, u32 id,
        const char *parent_name, unsigned long flags,
        unsigned long fixed_rate, unsigned long fixed_accuracy)
{
    return clk_hw_register_fixed_rate_with_accuracy(name, id, parent_name,
            flags, fixed_rate, fixed_accuracy);
}

int sunxi_fixed_clk_init(void)
{
    int ret = -1;

    ret = clk_register_fixed_rate_with_accuracy("dcxo24M", CLK_SRC_HOSC24M, NULL, 0, 24000000, 0);
    if (ret)
    {
        printf("register clock dcxo24M error\n");
    }

    ret = clk_register_fixed_rate_with_accuracy("fix_losc", CLK_SRC_LOSC, NULL, 0, 32768, 0);
    if (ret)
    {
        printf("register clock dcxo24M error\n");
    }

    ret = clk_register_fixed_rate_with_accuracy("rc-16m", CLK_SRC_RC_16M, NULL, 0, 16000000, 300000000);
    if (ret)
    {
        printf("register clock dcxo24M error\n");
    }

    ret = clk_register_fixed_rate_with_accuracy("ext-32k", CLK_SRC_EXT_32K, NULL, 0, 32768, 0);
    if (ret)
    {
        printf("register clock dcxo24M error\n");
    }

    return ret;
}
