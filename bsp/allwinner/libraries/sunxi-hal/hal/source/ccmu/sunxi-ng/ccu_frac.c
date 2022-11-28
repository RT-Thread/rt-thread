// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@free-electrons.com>
 */
#include "ccu.h"
#include "ccu_frac.h"
#include <hal_log.h>

bool ccu_frac_helper_is_enabled(struct ccu_common *common,
                                struct ccu_frac_internal *cf)
{
    if (!(common->features & CCU_FEATURE_FRACTIONAL))
    {
        return false;
    }

    return !(readl(common->base + common->reg) & cf->enable);
}

void ccu_frac_helper_enable(struct ccu_common *common,
                            struct ccu_frac_internal *cf)
{
    u32 reg;
    u32 __cspr;

    if (!(common->features & CCU_FEATURE_FRACTIONAL))
    {
        return;
    }

    __cspr = hal_spin_lock_irqsave(&common->lock);
    reg = readl(common->base + common->reg);
    writel(reg & ~cf->enable, common->base + common->reg);
    hal_spin_unlock_irqrestore(&common->lock, __cspr);
}

void ccu_frac_helper_disable(struct ccu_common *common,
                             struct ccu_frac_internal *cf)
{
    u32 reg;
    u32 __cspr;

    if (!(common->features & CCU_FEATURE_FRACTIONAL))
    {
        return;
    }

    __cspr = hal_spin_lock_irqsave(&common->lock);
    reg = readl(common->base + common->reg);
    writel(reg | cf->enable, common->base + common->reg);
    hal_spin_unlock_irqrestore(&common->lock, __cspr);
}

bool ccu_frac_helper_has_rate(struct ccu_common *common,
                              struct ccu_frac_internal *cf,
                              unsigned long rate)
{
    if (!(common->features & CCU_FEATURE_FRACTIONAL))
    {
        return false;
    }

    return (cf->rates[0] == rate) || (cf->rates[1] == rate);
}

unsigned long ccu_frac_helper_read_rate(struct ccu_common *common,
                                        struct ccu_frac_internal *cf)
{
    u32 reg;

    hal_log_debug("%s: Read fractional\n", clk_hw_get_name(&common->hw));

    if (!(common->features & CCU_FEATURE_FRACTIONAL))
    {
        return 0;
    }

    hal_log_debug("%s: clock is fractional (rates %lu and %lu)\n",
                  clk_hw_get_name(&common->hw), cf->rates[0], cf->rates[1]);

    reg = readl(common->base + common->reg);

    hal_log_debug("%s: clock reg is 0x%x (select is 0x%x)\n",
                  clk_hw_get_name(&common->hw), reg, cf->select);

    return (reg & cf->select) ? cf->rates[1] : cf->rates[0];
}

int ccu_frac_helper_set_rate(struct ccu_common *common,
                             struct ccu_frac_internal *cf,
                             unsigned long rate, u32 lock)
{
    u32 reg, sel;
    u32 __cspr;

    if (!(common->features & CCU_FEATURE_FRACTIONAL))
    {
        return -1;
    }

    if (cf->rates[0] == rate)
    {
        sel = 0;
    }
    else if (cf->rates[1] == rate)
    {
        sel = cf->select;
    }
    else
    {
        return -1;
    }

    __cspr = hal_spin_lock_irqsave(&common->lock);
    reg = readl(common->base + common->reg);
    reg &= ~cf->select;
    writel(reg | sel, common->base + common->reg);
    hal_spin_unlock_irqrestore(&common->lock, __cspr);

    ccu_helper_wait_for_lock(common, lock);
    return 0;
}
