/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#define ROCKCHIP_MMC_DELAY_SEL          RT_BIT(11)
#define ROCKCHIP_MMC_DEGREE_OFFSET      1
#define ROCKCHIP_MMC_DEGREE_MASK        (0x3 << ROCKCHIP_MMC_DEGREE_OFFSET)
#define ROCKCHIP_MMC_DELAYNUM_OFFSET    3
#define ROCKCHIP_MMC_DELAYNUM_MASK      (0xff << ROCKCHIP_MMC_DELAYNUM_OFFSET)
/*
 * Each fine delay is between 44ps-77ps. Assume each fine delay is 60ps to
 * simplify calculations. So 45degs could be anywhere between 33deg and 57.8deg.
 */
#define ROCKCHIP_MMC_DELAY_ELEMENT_PSEC 60

#define PSECS_PER_SEC 1000000000000LL

#define RK3288_MMC_CLKGEN_DIV 2

rt_inline rt_ubase_t rk_clk_mmc_recalc(rt_ubase_t parent_rate)
{
    return parent_rate / RK3288_MMC_CLKGEN_DIV;
}

static rt_err_t rk_clk_mmc_set_phase(rt_ubase_t rate, void *reg, int shift,
        int degrees)
{
    rt_uint32_t raw_value, delay;
    rt_uint8_t nineties, remainder, delay_num;

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
        LOG_E("Invalid CLK rate in phase setting");

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
    delay = RT_DIV_ROUND_CLOSEST(delay, (rate / 1000) * 36 *
                (ROCKCHIP_MMC_DELAY_ELEMENT_PSEC / 10));

    delay_num = (rt_uint8_t)rt_min_t(rt_uint32_t, delay, 255);

    raw_value = delay_num ? ROCKCHIP_MMC_DELAY_SEL : 0;
    raw_value |= delay_num << ROCKCHIP_MMC_DELAYNUM_OFFSET;
    raw_value |= nineties;
    HWREG32(reg) = HIWORD_UPDATE(raw_value, 0x07ff, shift);

    return RT_EOK;
}

static rt_base_t rk_clk_mmc_get_phase(rt_ubase_t rate, void *reg, int shift)
{
    rt_uint16_t degrees;
    rt_uint32_t raw_value, delay_num = 0;

    /* Constant signal, no measurable phase shift */
    if (!rate)
    {
        return 0;
    }

    raw_value = HWREG32(reg) >> shift;
    degrees = (raw_value & ROCKCHIP_MMC_DEGREE_MASK) * 90;

    if (raw_value & ROCKCHIP_MMC_DELAY_SEL)
    {
        /* degrees/delaynum * 1000000 */
        rt_ubase_t factor = (ROCKCHIP_MMC_DELAY_ELEMENT_PSEC / 10) *
                36 * (rate / 10000);

        delay_num = (raw_value & ROCKCHIP_MMC_DELAYNUM_MASK);
        delay_num >>= ROCKCHIP_MMC_DELAYNUM_OFFSET;
        degrees += RT_DIV_ROUND_CLOSEST(delay_num * factor, 1000000);
    }

    return degrees % 360;
}
