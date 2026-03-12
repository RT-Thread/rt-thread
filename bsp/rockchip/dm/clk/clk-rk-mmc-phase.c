/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk-rk-mmc-phase.h"

#define ROCKCHIP_MMC_DELAY_SEL          RT_BIT(10)
#define ROCKCHIP_MMC_DEGREE_MASK        0x3
#define ROCKCHIP_MMC_DELAYNUM_OFFSET    2
#define ROCKCHIP_MMC_DELAYNUM_MASK      (0xff << ROCKCHIP_MMC_DELAYNUM_OFFSET)
/*
 * Each fine delay is between 44ps-77ps. Assume each fine delay is 60ps to
 * simplify calculations. So 45degs could be anywhere between 33deg and 57.8deg.
 */
#define ROCKCHIP_MMC_DELAY_ELEMENT_PSEC 60

#define PSECS_PER_SEC                   1000000000000LL

#define RK3288_MMC_CLKGEN_DIV           2

static rt_ubase_t rockchip_mmc_recalc(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    return parent_rate / RK3288_MMC_CLKGEN_DIV;
}

static rt_err_t rockchip_mmc_set_phase(struct rt_clk_cell *cell, int degrees)
{
    rt_ubase_t rate;
    rt_uint32_t raw_value, delay;
    rt_uint8_t nineties, remainder, delay_num;
    struct rockchip_mmc_clk_cell *mmc_cell = cell_to_rockchip_mmc_clk_cell(cell);
    struct rockchip_clk_cell *rk_cell = &mmc_cell->rk_cell;

    rate = rt_clk_cell_get_rate(cell);

    /*
     * The below calculation is based on the output clock from
     * MMC host to the card, which expects the phase clock inherits
     * the clock rate from its parent, namely the output clock
     * provider of MMC host. However, things may go wrong if
     * (1) It is orphan.
     * (2) It is assigned to the wrong parent.
     *
     * This check help debug the case (1), which seems to be the
     * most likely problem we often face and which makes it difficult
     * for people to debug unstable mmc tuning results.
     */
    if (!rate)
    {
        return -RT_EINVAL;
    }

    nineties = degrees / 90;
    remainder = (degrees % 90);

    /*
     * Due to the inexact nature of the "fine" delay, we might
     * actually go non-monotonic.  We don't go _too_ monotonic
     * though, so we should be OK.  Here are options of how we may
     * work:
     *
     * Ideally we end up with:
     *   1.0, 2.0, ..., 69.0, 70.0, ...,  89.0, 90.0
     *
     * On one extreme (if delay is actually 44ps):
     *   .73, 1.5, ..., 50.6, 51.3, ...,  65.3, 90.0
     * The other (if delay is actually 77ps):
     *   1.3, 2.6, ..., 88.6. 89.8, ..., 114.0, 90
     *
     * It's possible we might make a delay that is up to 25
     * degrees off from what we think we're making.  That's OK
     * though because we should be REALLY far from any bad range.
     */

    /*
     * Convert to delay; do a little extra work to make sure we
     * don't overflow 32-bit / 64-bit numbers.
     */
    delay = 10000000; /* PSECS_PER_SEC / 10000 / 10 */
    delay *= remainder;
    delay = RT_DIV_ROUND_CLOSEST(delay,
            (rate / 1000) * 36 * (ROCKCHIP_MMC_DELAY_ELEMENT_PSEC / 10));

    delay_num = (rt_uint8_t)rt_min_t(rt_uint32_t, delay, 255);

    raw_value = delay_num ? ROCKCHIP_MMC_DELAY_SEL : 0;
    raw_value |= delay_num << ROCKCHIP_MMC_DELAYNUM_OFFSET;
    raw_value |= nineties;

    HWREG32(rk_cell->provider->reg_base + rk_cell->muxdiv_offset) =
            HIWORD_UPDATE(raw_value, 0x07ff, rk_cell->div_shift);

    return RT_EOK;
}

static rt_base_t rockchip_mmc_get_phase(struct rt_clk_cell *cell)
{
    rt_ubase_t rate;
    rt_uint16_t degrees;
    rt_uint32_t raw_value, delay_num = 0;
    struct rockchip_mmc_clk_cell *mmc_cell = cell_to_rockchip_mmc_clk_cell(cell);
    struct rockchip_clk_cell *rk_cell = &mmc_cell->rk_cell;

    rate = rt_clk_cell_get_rate(cell);

    /* Constant signal, no measurable phase shift */
    if (!rate)
    {
        return 0;
    }

    raw_value = HWREG32(rk_cell->provider->reg_base + rk_cell->muxdiv_offset) >> rk_cell->div_shift;

    degrees = (raw_value & ROCKCHIP_MMC_DEGREE_MASK) * 90;

    if (raw_value & ROCKCHIP_MMC_DELAY_SEL)
    {
        /* degrees/delaynum * 1000000 */
        rt_ubase_t factor = (ROCKCHIP_MMC_DELAY_ELEMENT_PSEC / 10) * 36 * (rate / 10000);

        delay_num = (raw_value & ROCKCHIP_MMC_DELAYNUM_MASK);
        delay_num >>= ROCKCHIP_MMC_DELAYNUM_OFFSET;
        degrees += RT_DIV_ROUND_CLOSEST(delay_num * factor, 1000000);
    }

    return degrees % 360;
}

const struct rt_clk_ops rockchip_mmc_clk_ops =
{
    .recalc_rate = rockchip_mmc_recalc,
    .set_phase = rockchip_mmc_set_phase,
    .get_phase = rockchip_mmc_get_phase,
};

static rt_err_t rockchip_mmc_clk_rate_notify(struct rt_clk_notifier *notifier,
        rt_ubase_t msg, rt_ubase_t old_rate, rt_ubase_t new_rate)
{
    struct rockchip_mmc_clk_cell *mmc_cell = rt_container_of(notifier, struct rockchip_mmc_clk_cell, notifier);

    if (old_rate <= new_rate)
    {
        return RT_EOK;
    }

    if (msg == RT_CLK_MSG_PRE_RATE_CHANGE)
    {
        mmc_cell->cached_phase = rockchip_mmc_get_phase(&mmc_cell->rk_cell.cell);
    }
    else if (mmc_cell->cached_phase != -RT_EINVAL && msg == RT_CLK_MSG_POST_RATE_CHANGE)
    {
        rockchip_mmc_set_phase(&mmc_cell->rk_cell.cell, mmc_cell->cached_phase);
    }

    return RT_EOK;
}

void rockchip_mmc_clk_cell_setup(struct rockchip_clk_cell *rk_cell)
{
    struct rt_clk_cell *cell = &rk_cell->cell;
    struct rockchip_mmc_clk_cell *mmc_cell = cell_to_rockchip_mmc_clk_cell(cell);

    mmc_cell->notifier.callback = rockchip_mmc_clk_rate_notify;

    rt_clk_notifier_register(rt_clk_cell_get_clk(cell, RT_NULL), &mmc_cell->notifier);
}
