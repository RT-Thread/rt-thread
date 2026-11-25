/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-3-15      GuEe-GUI     the first version
 */

#include "rockchip-audio-clock.h"

rt_err_t rockchip_audio_set_mclk(struct rt_clk *mclk, rt_ubase_t rate)
{
    struct rt_clk_cell *cell;
    struct rt_clk_cell *parent;
    struct rt_clk *clk;
    rt_err_t err;
    rt_uint8_t index;

    if (rt_is_err_or_null(mclk))
    {
        return -RT_EINVAL;
    }
    cell = mclk->cell;

    /* Skip pass-through gates and configure the first programmable clock. */
    while (cell->parents_nr == 1 && !cell->ops->set_rate)
    {
        cell = rt_clk_cell_get_parent_by_index(cell, 0);
        if (!cell)
        {
            return -RT_ENOSYS;
        }
    }

    if (cell->ops->set_rate)
    {
        clk = rt_clk_cell_get_clk(cell, RT_NULL);
        return clk ? rt_clk_set_rate(clk, rate) : -RT_ENOMEM;
    }

    /* I2S and SAI muxes use an internal fractional clock for audio rates. */
    for (index = 0; index < cell->parents_nr; ++index)
    {
        rt_ubase_t flags;

        parent = rt_clk_cell_get_parent_by_index(cell, index);
        if (!parent || !parent->ops->set_rate)
        {
            continue;
        }
        if (rt_clk_cell_round_rate(parent, rate) != rate)
        {
            continue;
        }
        clk = rt_clk_cell_get_clk(parent, RT_NULL);
        if (!clk)
        {
            continue;
        }

        /* Keep the fractional divider's high-rate source, as in the I2S path. */
        flags = parent->flags;
        parent->flags &= ~RT_CLK_F_SET_RATE_PARENT;
        err = rt_clk_set_rate(clk, rate);
        parent->flags = flags;
        if (err)
        {
            continue;
        }
        return rt_clk_cell_set_parent(cell, parent);
    }
    return -RT_ENOSYS;
}
