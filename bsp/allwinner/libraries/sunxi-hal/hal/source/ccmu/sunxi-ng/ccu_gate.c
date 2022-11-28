// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@free-electrons.com>
 */
#include "ccu.h"
#include "ccu_gate.h"

void ccu_gate_helper_disable(struct ccu_common *common, u32 gate)
{
    u32 reg;
    u32 __cspr;

    if (!gate)
    {
        return;
    }

    __cspr = hal_spin_lock_irqsave(&common->lock);

    reg = readl(common->base + common->reg);
    writel(reg & ~gate, common->base + common->reg);

    hal_spin_unlock_irqrestore(&common->lock, __cspr);
}

static void ccu_gate_disable(struct clk_hw *hw)
{
    struct ccu_gate *cg = hw_to_ccu_gate(hw);

    return ccu_gate_helper_disable(&cg->common, cg->enable);
}

int ccu_gate_helper_enable(struct ccu_common *common, u32 gate)
{
    u32 reg;
    u32 __cspr;

    if (!gate)
    {
        return 0;
    }

    __cspr = hal_spin_lock_irqsave(&common->lock);

    reg = readl(common->base + common->reg);
    writel(reg | gate, common->base + common->reg);

    hal_spin_unlock_irqrestore(&common->lock, __cspr);

    return 0;
}

static int ccu_gate_enable(struct clk_hw *hw)
{
    struct ccu_gate *cg = hw_to_ccu_gate(hw);

    return ccu_gate_helper_enable(&cg->common, cg->enable);
}

int ccu_gate_helper_is_enabled(struct ccu_common *common, u32 gate)
{
    u32 value;

    if (!gate)
    {
        return 1;
    }

    value = readl(common->base + common->reg);
    return !!(value & gate);
}

static int ccu_gate_is_enabled(struct clk_hw *hw)
{
    struct ccu_gate *cg = hw_to_ccu_gate(hw);

    return ccu_gate_helper_is_enabled(&cg->common, cg->enable);
}

static unsigned long ccu_gate_recalc_rate(struct clk_hw *hw,
        unsigned long parent_rate)
{
    struct ccu_gate *cg = hw_to_ccu_gate(hw);
    unsigned long rate = parent_rate;

    if (cg->common.features & CCU_FEATURE_ALL_PREDIV)
    {
        rate /= cg->common.prediv;
    }

    return rate;
}

static long ccu_gate_round_rate(struct clk_hw *hw, unsigned long rate,
                                unsigned long *prate)
{
    struct ccu_gate *cg = hw_to_ccu_gate(hw);
    int div = 1;

    if (cg->common.features & CCU_FEATURE_ALL_PREDIV)
    {
        div = cg->common.prediv;
    }

    if (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)
    {
        unsigned long best_parent = rate;

        if (cg->common.features & CCU_FEATURE_ALL_PREDIV)
        {
            best_parent *= div;
        }
        *prate = clk_hw_round_rate(clk_hw_get_parent(hw), best_parent);
    }

    return *prate / div;
}

static int ccu_gate_set_rate(struct clk_hw *hw, unsigned long rate,
                             unsigned long parent_rate)
{
    /*
     * We must report success but we can do so unconditionally because
     * clk_factor_round_rate returns values that ensure this call is a
     * nop.
     */

    return 0;
}

const struct clk_ops ccu_gate_ops =
{
    .disable    = ccu_gate_disable,
    .enable     = ccu_gate_enable,
    .is_enabled = ccu_gate_is_enabled,
    .round_rate = ccu_gate_round_rate,
    .set_rate   = ccu_gate_set_rate,
    .recalc_rate    = ccu_gate_recalc_rate,
};
