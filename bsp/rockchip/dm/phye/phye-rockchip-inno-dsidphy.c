/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include <drivers/clk.h>
#include <drivers/misc.h>
#include <drivers/ofw_io.h>
#include <drivers/phye.h>
#include <drivers/platform.h>
#include <drivers/reset.h>

#define DBG_TAG "phye.inno-dsi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define UPDATE(v, h, l)         (((v) << (l)) & RT_GENMASK((h), (l)))
#define PHY_REG(first, second)  (((((first) & 0x7) << 5) | ((second) & 0x1f)) << 2)

/* Analog reg00. */
#define BANDGAP_POWER_MASK      RT_BIT(7)
#define BANDGAP_POWER_DOWN      RT_BIT(7)
#define BANDGAP_POWER_ON        0
#define LANE_EN_MASK            RT_GENMASK(6, 2)
#define LANE_EN_CK              RT_BIT(6)
#define LANE_EN_3               RT_BIT(5)
#define LANE_EN_2               RT_BIT(4)
#define LANE_EN_1               RT_BIT(3)
#define LANE_EN_0               RT_BIT(2)
#define POWER_WORK_MASK         RT_GENMASK(1, 0)
#define POWER_WORK_ENABLE       UPDATE(1, 1, 0)
#define POWER_WORK_DISABLE      UPDATE(2, 1, 0)

/* Analog reg01, reg03, reg04, reg08 and reg0b. */
#define REG_SYNCRST_MASK        RT_BIT(2)
#define REG_SYNCRST_RESET       RT_BIT(2)
#define REG_SYNCRST_NORMAL      0
#define REG_LDOPD_MASK          RT_BIT(1)
#define REG_LDOPD_POWER_DOWN    RT_BIT(1)
#define REG_LDOPD_POWER_ON      0
#define REG_PLLPD_MASK          RT_BIT(0)
#define REG_PLLPD_POWER_DOWN    RT_BIT(0)
#define REG_PLLPD_POWER_ON      0
#define REG_FBDIV_HI_MASK       RT_BIT(5)
#define REG_FBDIV_HI(x)         UPDATE((x) >> 8, 5, 5)
#define REG_PREDIV_MASK         RT_GENMASK(4, 0)
#define REG_PREDIV(x)           UPDATE(x, 4, 0)
#define REG_FBDIV_LO_MASK       RT_GENMASK(7, 0)
#define REG_FBDIV_LO(x)         UPDATE(x, 7, 0)
#define PLL_POST_DIV_EN_MASK    RT_BIT(5)
#define PLL_POST_DIV_ENABLE     RT_BIT(5)
#define CLK_LANE_VOD_MASK       RT_GENMASK(3, 0)
#define CLK_LANE_VOD(x)         UPDATE(x, 3, 0)
#define VOD_MAX_RANGE           0xf

/* Digital reg00. */
#define REG_DIG_RSTN_MASK       RT_BIT(0)
#define REG_DIG_RSTN_NORMAL     RT_BIT(0)
#define REG_DIG_RSTN_RESET      0

/* Per-lane timing registers. */
#define T_LPX_CNT_MASK          RT_GENMASK(5, 0)
#define T_LPX_CNT(x)            UPDATE(x, 5, 0)
#define T_HS_ZERO_HI_MASK       RT_BIT(7)
#define T_HS_ZERO_HI(x)         UPDATE((x) >> 6, 7, 7)
#define T_HS_PREPARE_MASK       RT_GENMASK(6, 0)
#define T_HS_PREPARE(x)         UPDATE(x, 6, 0)
#define T_HS_ZERO_LO_MASK       RT_GENMASK(5, 0)
#define T_HS_ZERO_LO(x)         UPDATE(x, 5, 0)
#define T_HS_TRAIL_MASK         RT_GENMASK(6, 0)
#define T_HS_TRAIL(x)           UPDATE(x, 6, 0)
#define T_HS_EXIT_LO_MASK       RT_GENMASK(4, 0)
#define T_HS_EXIT_LO(x)         UPDATE(x, 4, 0)
#define T_CLK_POST_LO_MASK      RT_GENMASK(3, 0)
#define T_CLK_POST_LO(x)        UPDATE(x, 3, 0)
#define T_WAKEUP_HI_MASK        RT_GENMASK(1, 0)
#define T_WAKEUP_HI(x)          UPDATE((x) >> 8, 1, 0)
#define T_WAKEUP_LO_MASK        RT_GENMASK(7, 0)
#define T_WAKEUP_LO(x)          UPDATE(x, 7, 0)
#define T_CLK_PRE_MASK          RT_GENMASK(3, 0)
#define T_CLK_PRE(x)            UPDATE(x, 3, 0)
#define T_CLK_POST_HI_MASK      RT_GENMASK(7, 6)
#define T_CLK_POST_HI(x)        UPDATE((x) >> 4, 7, 6)
#define T_TA_GO_MASK            RT_GENMASK(5, 0)
#define T_TA_GO(x)              UPDATE(x, 5, 0)
#define T_HS_EXIT_HI_MASK       RT_BIT(6)
#define T_HS_EXIT_HI(x)         UPDATE((x) >> 5, 6, 6)
#define T_TA_SURE_MASK          RT_GENMASK(5, 0)
#define T_TA_SURE(x)            UPDATE(x, 5, 0)
#define T_TA_WAIT_MASK          RT_GENMASK(5, 0)
#define T_TA_WAIT(x)            UPDATE(x, 5, 0)

/* LVDS register bank reg03 is also the protocol mode selector. */
#define MODE_ENABLE_MASK        RT_GENMASK(2, 0)
#define MIPI_MODE_ENABLE        RT_BIT(0)

#define PSEC_PER_SEC            1000000000000ULL
#define INNO_DPHY_MAX_RATE      2500000000ULL

enum inno_dphy_part
{
    INNO_PART_ANALOG,
    INNO_PART_DIGITAL,
    INNO_PART_CLOCK_LANE,
    INNO_PART_DATA0_LANE,
    INNO_PART_DATA1_LANE,
    INNO_PART_DATA2_LANE,
    INNO_PART_DATA3_LANE,
    INNO_PART_LVDS,
};

struct inno_dphy_timing
{
    rt_uint16_t max_lane_mbps;
    rt_uint8_t lpx;
    rt_uint8_t hs_prepare;
    rt_uint8_t clk_hs_zero;
    rt_uint8_t data_hs_zero;
    rt_uint8_t hs_trail;
};

struct inno_dsidphy
{
    struct rt_phye parent;
    void *regs;
    struct rt_clk *ref_clk;
    struct rt_clk *pclk;
    struct rt_reset_control *apb_rst;
    struct rt_phye_configure_opts_mipi_dphy cfg;
    rt_uint32_t lanes;
    rt_uint8_t prediv;
    rt_uint16_t fbdiv;
    rt_uint64_t rate;
};

#define phye_to_inno(phye) rt_container_of(phye, struct inno_dsidphy, parent)

static const struct inno_dphy_timing rk3568_dphy_timings[] =
{
    {  110, 0x02, 0x7f, 0x16, 0x02, 0x02 },
    {  150, 0x02, 0x7f, 0x16, 0x03, 0x02 },
    {  200, 0x02, 0x7f, 0x17, 0x04, 0x02 },
    {  250, 0x02, 0x7f, 0x17, 0x05, 0x04 },
    {  300, 0x02, 0x7f, 0x18, 0x06, 0x04 },
    {  400, 0x03, 0x7e, 0x19, 0x07, 0x04 },
    {  500, 0x03, 0x7c, 0x1b, 0x07, 0x08 },
    {  600, 0x03, 0x70, 0x1d, 0x08, 0x10 },
    {  700, 0x05, 0x40, 0x1e, 0x08, 0x30 },
    {  800, 0x05, 0x02, 0x1f, 0x09, 0x30 },
    { 1000, 0x05, 0x08, 0x20, 0x09, 0x30 },
    { 1200, 0x06, 0x03, 0x32, 0x14, 0x0f },
    { 1400, 0x09, 0x03, 0x32, 0x14, 0x0f },
    { 1600, 0x0d, 0x42, 0x36, 0x0e, 0x0f },
    { 1800, 0x0e, 0x47, 0x7a, 0x0e, 0x0f },
    { 2000, 0x11, 0x64, 0x7a, 0x0e, 0x0b },
    { 2200, 0x13, 0x64, 0x7e, 0x15, 0x0b },
    { 2400, 0x13, 0x33, 0x7f, 0x15, 0x6a },
    { 2500, 0x15, 0x54, 0x7f, 0x15, 0x6a },
};

static void inno_update_bits(struct inno_dsidphy *inno, rt_uint8_t part,
        rt_uint8_t second, rt_uint8_t mask, rt_uint8_t val)
{
    volatile rt_uint32_t *reg;
    rt_uint32_t tmp;

    reg = (volatile rt_uint32_t *)((rt_uint8_t *)inno->regs + PHY_REG(part, second));
    tmp = *reg;
    *reg = (tmp & ~mask) | (val & mask);
}

static rt_err_t inno_pll_calc(struct inno_dsidphy *inno, rt_uint64_t requested)
{
    rt_uint64_t prate = rt_clk_get_rate(inno->ref_clk);
    rt_uint64_t fref, target, best_rate = 0;
    rt_uint32_t min_prediv, max_prediv, prediv;
    rt_uint64_t best_delta = ~(rt_uint64_t)0;
    rt_uint8_t best_prediv = 0;
    rt_uint16_t best_fbdiv = 0;

    if (!prate)
    {
        prate = 24000000;
    }

    fref = prate / 2;
    target = requested > 1000000000ULL ? 1000000000ULL : requested;
    if (!fref || !target)
    {
        return -RT_EINVAL;
    }

    min_prediv = (rt_uint32_t)RT_DIV_ROUND_UP_ULL(fref, 40000000);
    max_prediv = (rt_uint32_t)(fref / 5000000);

    for (prediv = min_prediv; prediv <= max_prediv; ++prediv)
    {
        rt_uint64_t rate, delta;
        rt_uint32_t fbdiv;

        if (!prediv)
        {
            continue;
        }

        fbdiv = (rt_uint32_t)((target * prediv) / fref);
        if (fbdiv == 15 || fbdiv < 12 || fbdiv > 511)
        {
            continue;
        }

        rate = (fref * fbdiv) / prediv;
        delta = target > rate ? target - rate : rate - target;
        if (delta < best_delta)
        {
            best_delta = delta;
            best_prediv = (rt_uint8_t)prediv;
            best_fbdiv = (rt_uint16_t)fbdiv;
            best_rate = rate;
        }
        if (!delta)
        {
            break;
        }
    }

    if (!best_rate)
    {
        return -RT_EINVAL;
    }

    inno->prediv = best_prediv;
    inno->fbdiv = best_fbdiv;
    inno->rate = best_rate;

    return RT_EOK;
}

static const struct inno_dphy_timing *inno_get_timing(rt_uint32_t lane_mbps)
{
    rt_size_t i;

    for (i = 0; i < RT_ARRAY_SIZE(rk3568_dphy_timings); ++i)
    {
        if (lane_mbps <= rk3568_dphy_timings[i].max_lane_mbps)
        {
            return &rk3568_dphy_timings[i];
        }
    }

    return &rk3568_dphy_timings[RT_ARRAY_SIZE(rk3568_dphy_timings) - 1];
}

static void inno_pll_enable(struct inno_dsidphy *inno)
{
    inno_update_bits(inno, INNO_PART_ANALOG, 0x03,
            REG_PREDIV_MASK, REG_PREDIV(inno->prediv));
    inno_update_bits(inno, INNO_PART_ANALOG, 0x03,
            REG_FBDIV_HI_MASK, REG_FBDIV_HI(inno->fbdiv));
    inno_update_bits(inno, INNO_PART_ANALOG, 0x04,
            REG_FBDIV_LO_MASK, REG_FBDIV_LO(inno->fbdiv));
    inno_update_bits(inno, INNO_PART_ANALOG, 0x08,
            PLL_POST_DIV_EN_MASK, PLL_POST_DIV_ENABLE);
    inno_update_bits(inno, INNO_PART_ANALOG, 0x0b,
            CLK_LANE_VOD_MASK, CLK_LANE_VOD(VOD_MAX_RANGE));
    inno_update_bits(inno, INNO_PART_ANALOG, 0x01,
            REG_LDOPD_MASK | REG_PLLPD_MASK,
            REG_LDOPD_POWER_ON | REG_PLLPD_POWER_ON);
}

static void inno_reset(struct inno_dsidphy *inno)
{
    inno_update_bits(inno, INNO_PART_ANALOG, 0x01,
            REG_SYNCRST_MASK, REG_SYNCRST_RESET);
    rt_hw_us_delay(1);
    inno_update_bits(inno, INNO_PART_ANALOG, 0x01,
            REG_SYNCRST_MASK, REG_SYNCRST_NORMAL);

    inno_update_bits(inno, INNO_PART_DIGITAL, 0x00,
            REG_DIG_RSTN_MASK, REG_DIG_RSTN_RESET);
    rt_hw_us_delay(1);
    inno_update_bits(inno, INNO_PART_DIGITAL, 0x00,
            REG_DIG_RSTN_MASK, REG_DIG_RSTN_NORMAL);
}

static void inno_timing_init(struct inno_dsidphy *inno)
{
    const struct rt_phye_configure_opts_mipi_dphy *cfg = &inno->cfg;
    const struct inno_dphy_timing *timing;
    rt_uint32_t byteclk, esc_div, esc_clk;
    rt_uint32_t byte_period, esc_period;
    rt_uint32_t hs_exit, clk_post, clk_pre;
    rt_uint32_t ta_go, ta_sure, ta_wait;
    rt_uint32_t part, hs_zero;

    byteclk = (rt_uint32_t)(inno->rate / 8);
    esc_div = RT_DIV_ROUND_UP(byteclk, 20000000);
    if (!esc_div)
    {
        esc_div = 1;
    }
    esc_clk = byteclk / esc_div;
    byte_period = (rt_uint32_t)(PSEC_PER_SEC / byteclk);
    esc_period = (rt_uint32_t)(PSEC_PER_SEC / esc_clk);

    hs_exit = RT_DIV_ROUND_UP(cfg->hs_exit, byte_period);
    clk_post = RT_DIV_ROUND_UP(cfg->clk_post, byte_period);
    clk_pre = RT_DIV_ROUND_UP(cfg->clk_pre, byte_period);
    ta_go = RT_DIV_ROUND_UP(cfg->lpx * 4, esc_period);
    ta_sure = RT_DIV_ROUND_UP(cfg->lpx, esc_period);
    ta_wait = RT_DIV_ROUND_UP(cfg->lpx * 5, esc_period);
    timing = inno_get_timing((rt_uint32_t)(inno->rate / 1000000));

    for (part = INNO_PART_CLOCK_LANE; part <= INNO_PART_DATA3_LANE; ++part)
    {
        hs_zero = part == INNO_PART_CLOCK_LANE ?
                timing->clk_hs_zero : timing->data_hs_zero;

        inno_update_bits(inno, part, 0x05, T_LPX_CNT_MASK, T_LPX_CNT(timing->lpx));
        inno_update_bits(inno, part, 0x06, T_HS_PREPARE_MASK,
                T_HS_PREPARE(timing->hs_prepare));
        inno_update_bits(inno, part, 0x06, T_HS_ZERO_HI_MASK, T_HS_ZERO_HI(hs_zero));
        inno_update_bits(inno, part, 0x07, T_HS_ZERO_LO_MASK, T_HS_ZERO_LO(hs_zero));
        inno_update_bits(inno, part, 0x08, T_HS_TRAIL_MASK, T_HS_TRAIL(timing->hs_trail));
        inno_update_bits(inno, part, 0x11, T_HS_EXIT_HI_MASK, T_HS_EXIT_HI(hs_exit));
        inno_update_bits(inno, part, 0x09, T_HS_EXIT_LO_MASK, T_HS_EXIT_LO(hs_exit));
        inno_update_bits(inno, part, 0x10, T_CLK_POST_HI_MASK, T_CLK_POST_HI(clk_post));
        inno_update_bits(inno, part, 0x0a, T_CLK_POST_LO_MASK, T_CLK_POST_LO(clk_post));
        inno_update_bits(inno, part, 0x0e, T_CLK_PRE_MASK, T_CLK_PRE(clk_pre));
        inno_update_bits(inno, part, 0x0c, T_WAKEUP_HI_MASK, T_WAKEUP_HI(0x3ff));
        inno_update_bits(inno, part, 0x0d, T_WAKEUP_LO_MASK, T_WAKEUP_LO(0x3ff));
        inno_update_bits(inno, part, 0x10, T_TA_GO_MASK, T_TA_GO(ta_go));
        inno_update_bits(inno, part, 0x11, T_TA_SURE_MASK, T_TA_SURE(ta_sure));
        inno_update_bits(inno, part, 0x12, T_TA_WAIT_MASK, T_TA_WAIT(ta_wait));
    }
}

static void inno_lane_enable(struct inno_dsidphy *inno)
{
    rt_uint8_t val = LANE_EN_CK | LANE_EN_0;

    if (inno->lanes >= 2)
    {
        val |= LANE_EN_1;
    }
    if (inno->lanes >= 3)
    {
        val |= LANE_EN_2;
    }
    if (inno->lanes >= 4)
    {
        val |= LANE_EN_3;
    }

    inno_update_bits(inno, INNO_PART_ANALOG, 0x00, LANE_EN_MASK, val);
}

static rt_err_t inno_dsidphy_init(struct rt_phye *phye)
{
    struct inno_dsidphy *inno = phye_to_inno(phye);
    rt_err_t err;

    if ((err = rt_clk_prepare_enable(inno->pclk)))
    {
        return err;
    }
    if ((err = rt_clk_prepare_enable(inno->ref_clk)))
    {
        rt_clk_disable_unprepare(inno->pclk);
        return err;
    }

    if (!rt_is_err_or_null(inno->apb_rst))
    {
        rt_reset_control_deassert(inno->apb_rst);
    }

    return RT_EOK;
}

static rt_err_t inno_dsidphy_exit(struct rt_phye *phye)
{
    struct inno_dsidphy *inno = phye_to_inno(phye);

    rt_clk_disable_unprepare(inno->ref_clk);
    rt_clk_disable_unprepare(inno->pclk);

    return RT_EOK;
}

static rt_err_t inno_dsidphy_set_mode(struct rt_phye *phye,
        enum rt_phye_mode mode, int submode)
{
    RT_UNUSED(phye);
    RT_UNUSED(submode);

    return mode == RT_PHYE_MODE_MIPI_DPHY ? RT_EOK : -RT_ENOSYS;
}

static rt_err_t inno_dsidphy_configure(struct rt_phye *phye,
        union rt_phye_configure_opts *opts)
{
    struct inno_dsidphy *inno = phye_to_inno(phye);
    rt_err_t err;

    if (phye->mode != RT_PHYE_MODE_MIPI_DPHY ||
            !opts->mipi_dphy.hs_clk_rate || !opts->mipi_dphy.lanes ||
            opts->mipi_dphy.lanes > 4 ||
            opts->mipi_dphy.hs_clk_rate > INNO_DPHY_MAX_RATE)
    {
        return -RT_EINVAL;
    }

    inno->cfg = opts->mipi_dphy;
    if ((err = inno_pll_calc(inno, inno->cfg.hs_clk_rate)))
    {
        return err;
    }

    inno->cfg.hs_clk_rate = inno->rate;
    opts->mipi_dphy.hs_clk_rate = inno->rate;

    return RT_EOK;
}

static rt_err_t inno_dsidphy_power_on(struct rt_phye *phye)
{
    struct inno_dsidphy *inno = phye_to_inno(phye);

    if (phye->mode != RT_PHYE_MODE_MIPI_DPHY || !inno->rate)
    {
        return -RT_EINVAL;
    }

    inno_update_bits(inno, INNO_PART_ANALOG, 0x00,
            BANDGAP_POWER_MASK, BANDGAP_POWER_ON);
    inno_update_bits(inno, INNO_PART_ANALOG, 0x00,
            POWER_WORK_MASK, POWER_WORK_ENABLE);
    inno_update_bits(inno, INNO_PART_LVDS, 0x03,
            MODE_ENABLE_MASK, MIPI_MODE_ENABLE);

    inno_pll_enable(inno);
    inno_reset(inno);
    inno_timing_init(inno);
    inno_lane_enable(inno);
    rt_hw_us_delay(1000);

    LOG_I("powered on: host=%u phy=%u lane(s), %u Mbps, prediv=%u fbdiv=%u",
            inno->cfg.lanes, inno->lanes, (rt_uint32_t)(inno->rate / 1000000),
            inno->prediv, inno->fbdiv);

    return RT_EOK;
}

static rt_err_t inno_dsidphy_power_off(struct rt_phye *phye)
{
    struct inno_dsidphy *inno = phye_to_inno(phye);

    inno_update_bits(inno, INNO_PART_ANALOG, 0x00, LANE_EN_MASK, 0);
    inno_update_bits(inno, INNO_PART_ANALOG, 0x01,
            REG_LDOPD_MASK | REG_PLLPD_MASK,
            REG_LDOPD_POWER_DOWN | REG_PLLPD_POWER_DOWN);
    inno_update_bits(inno, INNO_PART_ANALOG, 0x00,
            POWER_WORK_MASK, POWER_WORK_DISABLE);
    inno_update_bits(inno, INNO_PART_ANALOG, 0x00,
            BANDGAP_POWER_MASK, BANDGAP_POWER_DOWN);

    return RT_EOK;
}

static const struct rt_phye_ops inno_dsidphy_ops =
{
    .init = inno_dsidphy_init,
    .exit = inno_dsidphy_exit,
    .power_on = inno_dsidphy_power_on,
    .power_off = inno_dsidphy_power_off,
    .set_mode = inno_dsidphy_set_mode,
    .configure = inno_dsidphy_configure,
};

static rt_err_t inno_dsidphy_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node;
    struct inno_dsidphy *inno;
    rt_err_t err;

    inno = rt_calloc(1, sizeof(*inno));
    if (!inno)
    {
        return -RT_ENOMEM;
    }

    inno->regs = rt_ofw_iomap(np, 0);
    if (!inno->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    inno->ref_clk = rt_clk_get_by_name(dev, "ref");
    inno->pclk = rt_clk_get_by_name(dev, "pclk");
    if (rt_is_err_or_null(inno->ref_clk) || rt_is_err_or_null(inno->pclk))
    {
        err = -RT_EIO;
        goto _fail_clks;
    }

    inno->apb_rst = rt_reset_control_get_by_name(dev, "apb");
    inno->lanes = 4;
    rt_ofw_prop_read_u32(np, "inno,lanes", &inno->lanes);
    if (!inno->lanes || inno->lanes > 4)
    {
        inno->lanes = 4;
    }
    inno->parent.dev = dev;
    inno->parent.ops = &inno_dsidphy_ops;

    if ((err = rt_phye_register(&inno->parent)))
    {
        goto _fail_resources;
    }

    dev->user_data = inno;
    LOG_I("RK3568 DSI DPHY %s probed", rt_ofw_node_full_name(np));

    return RT_EOK;

_fail_resources:
    if (!rt_is_err_or_null(inno->apb_rst))
    {
        rt_reset_control_put(inno->apb_rst);
    }
_fail_clks:
    if (!rt_is_err_or_null(inno->pclk))
    {
        rt_clk_put(inno->pclk);
    }
    if (!rt_is_err_or_null(inno->ref_clk))
    {
        rt_clk_put(inno->ref_clk);
    }
    rt_iounmap(inno->regs);
_fail:
    rt_free(inno);
    return err;
}

static const struct rt_ofw_node_id inno_dsidphy_ids[] =
{
    { .compatible = "rockchip,rk3568-dsi-dphy" },
    { /* sentinel */ }
};

static struct rt_platform_driver inno_dsidphy_driver =
{
    .name = "rockchip-inno-dsidphy",
    .ids = inno_dsidphy_ids,
    .probe = inno_dsidphy_probe,
};
RT_PLATFORM_DRIVER_EXPORT(inno_dsidphy_driver);
