// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@free-electrons.com>
 */
#include "ccu.h"
#include "ccu_reset.h"
#include <hal_timer.h>
#include <hal_log.h>
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

static int ccu_reset_assert(struct reset_control_dev *rcdev,
                            hal_reset_id_t id)
{
    struct ccu_reset *ccu = rc_to_ccu_reset(rcdev);
    const struct ccu_reset_map *map = &ccu->reset_map[id];
    u32 reg;
    u32 __cspr;

    __cspr = hal_spin_lock_irqsave(&ccu->lock);

    reg = readl(ccu->base + map->reg);
    writel(reg & ~map->bit, ccu->base + map->reg);

    hal_spin_unlock_irqrestore(&ccu->lock, __cspr);

    return 0;
}

static int ccu_reset_deassert(struct reset_control_dev *rcdev,
                              hal_reset_id_t id)
{
    struct ccu_reset *ccu = rc_to_ccu_reset(rcdev);

    const struct ccu_reset_map *map = &ccu->reset_map[id];
    u32 reg;
    u32 __cspr;

    __cspr = hal_spin_lock_irqsave(&ccu->lock);

    reg = readl(ccu->base + map->reg);
    writel(reg | map->bit, ccu->base + map->reg);

    hal_spin_unlock_irqrestore(&ccu->lock, __cspr);

    return 0;
}

static int ccu_reset_reset(struct reset_control_dev *rcdev,
                           hal_reset_id_t id)
{
    ccu_reset_assert(rcdev, id);
    __clk_udelay(10);
    ccu_reset_deassert(rcdev, id);

    return 0;
}

static int ccu_reset_status(struct reset_control_dev *rcdev,
                            hal_reset_id_t id)
{
    struct ccu_reset *ccu = rc_to_ccu_reset(rcdev);
    const struct ccu_reset_map *map = &ccu->reset_map[id];

    /*
     * The reset control API expects 0 if reset is not asserted,
     * which is the opposite of what our hardware uses.
     */
    return !(map->bit & readl(ccu->base + map->reg));
}

const struct reset_control_ops ccu_reset_ops =
{
    .assert     = ccu_reset_assert,
    .deassert   = ccu_reset_deassert,
    .reset      = ccu_reset_reset,
    .status     = ccu_reset_status,
};
