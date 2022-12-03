// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright 2016 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@free-electrons.com>
 */
#include "ccu.h"
#include "ccu_common.h"
#include "ccu_gate.h"
#include "ccu_reset.h"
#include <hal_log.h>
#include <hal_timer.h>
#include <stdlib.h>

/* FIXME: use udelay provided by OS */
static void __clk_udelay(u32 ns)
{
    u32 i;
    ns *= 100;
    for (i = 0; i < ns; i ++)
    {
        ;
    }
}

void ccu_helper_wait_for_lock(struct ccu_common *common, u32 lock)
{
    unsigned long addr;
    u32 reg, loop = 5000;

    if (!lock)
    {
        return;
    }

    if (common->features & CCU_FEATURE_LOCK_REG)
    {
        addr = common->base + common->lock_reg;
    }
    else
    {
        addr = common->base + common->reg;
    }

    while (--loop)
    {
        reg = readl(addr);
        if (reg & lock)
        {
            __clk_udelay(20);
            break;
        }
        __clk_udelay(1);
    }
    if (!loop)
    {
        hal_log_warn("ccu wait for lock failed\n");
    }
}

int ccu_common_init(unsigned long reg, const struct sunxi_ccu_desc *desc)
{
    struct ccu_reset *reset;
    int i;
    int ret;

    if (!desc)
    {
        return 0;
    }

    for (i = 0; i < desc->num_ccu_clks; i++)
    {
        struct ccu_common *cclk = desc->ccu_clks[i];

        if (!cclk)
        {
            continue;
        }

        cclk->base = reg;
    }

    for (i = 0; i < desc->hw_clks->num; i++)
    {
        struct clk_hw *hw = desc->hw_clks->hws[i];
        const char *name;

        if (!hw)
        {
            break;
        }

        name = hw->init->name;
        hw->type = desc->clk_type;
        hw->id = i;
        ret = clk_hw_register(hw);
        if (ret)
        {
            printf("Couldn't register clock %d - %s\n", i, name);
            goto err_clk_unreg;
        }

    }

    reset = (struct ccu_reset *)malloc(sizeof(*reset));
    if (!reset)
    {
        hal_log_err("can't malloc reset struct!\n");
        ret = -1;
        goto err_clk_unreg;
    }
    reset->base = reg;
    reset->reset_map = desc->resets;
    reset->rcdev.ops = &ccu_reset_ops;
    reset->rcdev.type = desc->reset_type;
    reset->rcdev.nr_resets = desc->num_resets;

    ret = reset_control_register(&reset->rcdev);
    if (ret)
    {
        goto err_rst_unreg;
    }

    return ret;

err_rst_unreg:

    free(reset);

err_clk_unreg:
    while (i-- >= 0)
    {
        struct clk_hw *hw = desc->hw_clks->hws[i];

        clk_hw_unregister(hw);
    }

    return ret;
}

void set_reg(unsigned long addr, u32 val, u8 bw, u8 bs)
{
    u32 mask = (1UL << bw) - 1UL;
    u32 tmp = 0;

    tmp = readl(addr);
    tmp &= ~(mask << bs);

    writel(tmp | ((val & mask) << bs), addr);
}

void set_reg_key(unsigned long addr,
                 u32 key, u8 kbw, u8 kbs,
                 u32 val, u8 bw, u8 bs)
{
    u32 mask = (1UL << bw) - 1UL;
    u32 kmask = (1UL << kbw) - 1UL;
    u32 tmp = 0;

    tmp = readl(addr);
    tmp &= ~(mask << bs);

    writel(tmp | ((val & mask) << bs) | ((key & kmask) << kbs), addr);
}

