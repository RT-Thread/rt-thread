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
#include <drivers/syscon.h>

#define DBG_TAG "phye.dcphy"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define UPDATE(v, h, l)         (((v) << (l)) & (((2U << (h)) - 1U) & ~((1U << (l)) - 1U)))

#define BIAS_CON0               0x0000
#define BIAS_CON1               0x0004
#define BIAS_CON2               0x0008
#define PLL_CON0                0x0100
#define PLL_CON1                0x0104
#define PLL_CON2                0x0108
#define PLL_CON5                0x0114
#define PLL_CON7                0x011c
#define PLL_CON8                0x0120
#define PLL_STAT0               0x0140
#define DPHY_MC_GNR_CON0        0x0300
#define DPHY_MC_GNR_CON1        0x0304
#define DPHY_MC_ANA_CON0        0x0308
#define DPHY_MC_TIME_CON0       0x0330
#define DPHY_MC_TIME_CON1       0x0334
#define DPHY_MC_TIME_CON2       0x0338
#define DPHY_MC_TIME_CON3       0x033c
#define DPHY_MC_TIME_CON4       0x0340
#define COMBO_MD0_GNR_CON0      0x0400
#define COMBO_MD0_GNR_CON1      0x0404
#define COMBO_MD0_ANA_CON0      0x0408
#define COMBO_MD0_TIME_CON0     0x0430
#define COMBO_MD0_TIME_CON1     0x0434
#define COMBO_MD0_TIME_CON2     0x0438
#define COMBO_MD1_GNR_CON0      0x0500
#define COMBO_MD1_GNR_CON1      0x0504
#define COMBO_MD1_TIME_CON0     0x0530
#define COMBO_MD1_TIME_CON1     0x0534
#define COMBO_MD1_TIME_CON2     0x0538
#define COMBO_MD2_GNR_CON0      0x0600
#define COMBO_MD2_GNR_CON1      0x0604
#define COMBO_MD2_TIME_CON0     0x0630
#define COMBO_MD2_TIME_CON1     0x0634
#define COMBO_MD2_TIME_CON2     0x0638
#define DPHY_MD3_GNR_CON0       0x0700
#define DPHY_MD3_GNR_CON1       0x0704

#define PLL_EN                  RT_BIT(12)
#define PLL_LOCK                RT_BIT(0)
#define PHY_ENABLE              RT_BIT(0)
#define RESET_N_SEL             RT_BIT(10)
#define PLL_ENABLE_SEL          RT_BIT(8)
#define HSTX_CLK_SEL            RT_BIT(12)
#define EDGE_CON_EN             RT_BIT(8)
#define EDGE_CON(x)             UPDATE(x, 14, 12)

struct rk_dcphy_timing
{
    rt_uint16_t max_lane_mbps;
    rt_uint8_t lpx;
    rt_uint8_t clk_prepare;
    rt_uint8_t clk_zero;
    rt_uint8_t clk_pre;
    rt_uint8_t clk_post;
    rt_uint8_t clk_trail_eot;
    rt_uint8_t hs_exit;
    rt_uint8_t prepare_3;
    rt_uint8_t trail_3;
    rt_uint8_t zero_3;
};

struct rk_mipi_dcphy_pll
{
    rt_uint8_t prediv;
    rt_uint16_t fbdiv;
    rt_uint16_t dsm;
    rt_uint8_t scaler;
    rt_uint64_t rate;
};

struct rk_mipi_dcphy
{
    struct rt_phye parent;

    void *regs;
    struct rt_clk *pclk;
    struct rt_clk *ref_clk;
    struct rt_reset_control *m_phy_rst;
    struct rt_reset_control *apb_rst;

    rt_uint32_t lane_mbps;
    rt_uint32_t lanes;
    enum rt_phye_mode mode;

    struct rk_mipi_dcphy_pll pll;
};

static const struct rk_dcphy_timing rk_dcphy_timings[] =
{
    { 2500, 31, 114, 30, 27, 30, 54, 26, 23, 43, 36 },
    { 1500, 30, 110, 29, 26, 29, 52, 25, 22, 42, 35 },
    { 1000, 31, 113, 30, 27, 30, 54, 26, 23, 43, 36 },
    { 800, 30, 108, 29, 26, 28, 51, 25, 22, 41, 34 },
    { 600, 29, 106, 28, 25, 27, 50, 24, 21, 40, 33 },
    { 500, 28, 104, 27, 25, 27, 49, 24, 21, 39, 32 },
};

#define raw_to_rk_mipi_dcphy(raw) rt_container_of(raw, struct rk_mipi_dcphy, parent)

rt_inline void dcphy_write(struct rk_mipi_dcphy *dcphy, rt_uint32_t reg, rt_uint32_t val)
{
    HWREG32((rt_uint8_t *)dcphy->regs + reg) = val;
}

rt_inline void dcphy_set_bits(struct rk_mipi_dcphy *dcphy, rt_uint32_t reg,
        rt_uint32_t mask, rt_uint32_t val)
{
    rt_uint32_t v = HWREG32((rt_uint8_t *)dcphy->regs + reg);

    dcphy_write(dcphy, reg, (v & ~mask) | (val & mask));
}

static const struct rk_dcphy_timing *dcphy_get_timing(rt_uint32_t lane_mbps)
{
    rt_size_t i;

    for (i = 0; i < RT_ARRAY_SIZE(rk_dcphy_timings); ++i)
    {
        if (lane_mbps <= rk_dcphy_timings[i].max_lane_mbps)
        {
            return &rk_dcphy_timings[i];
        }
    }

    return &rk_dcphy_timings[RT_ARRAY_SIZE(rk_dcphy_timings) - 1];
}

static void dcphy_pll_calc(struct rk_mipi_dcphy *dcphy, rt_uint64_t rate_hz)
{
    rt_ubase_t prate = rt_clk_get_rate(dcphy->ref_clk);
    rt_uint16_t fbdiv;

    if (!prate)
    {
        prate = 24000000;
    }

    dcphy->pll.prediv = 1;
    dcphy->pll.scaler = 0;
    dcphy->pll.dsm = 0;

    fbdiv = (rt_uint16_t)(rate_hz / prate);
    if (fbdiv < 16)
    {
        fbdiv = 16;
    }
    if (fbdiv > 1023)
    {
        fbdiv = 1023;
    }

    dcphy->pll.fbdiv = fbdiv;
    dcphy->pll.rate = (prate / dcphy->pll.prediv) * fbdiv;
}

static void dcphy_pll_program(struct rk_mipi_dcphy *dcphy)
{
    dcphy_set_bits(dcphy, PLL_CON0, UPDATE(0x7, 10, 8) | UPDATE(0x3f, 5, 0),
            UPDATE(0, 10, 8) | UPDATE(dcphy->pll.prediv, 5, 0));
    dcphy_write(dcphy, PLL_CON1, dcphy->pll.dsm);
    dcphy_set_bits(dcphy, PLL_CON2, UPDATE(0x3ff, 9, 0), UPDATE(dcphy->pll.fbdiv, 9, 0));
    dcphy_write(dcphy, PLL_CON5, RESET_N_SEL | PLL_ENABLE_SEL);
    dcphy_write(dcphy, PLL_CON7, UPDATE(0xf000, 15, 0));
    dcphy_write(dcphy, PLL_CON8, UPDATE(0xf000, 15, 0));
}

static rt_err_t dcphy_pll_enable(struct rk_mipi_dcphy *dcphy)
{
    rt_int32_t i;

    dcphy_set_bits(dcphy, PLL_CON0, PLL_EN, PLL_EN);

    for (i = 0; i < 20000; ++i)
    {
        if (HWREG32((rt_uint8_t *)dcphy->regs + PLL_STAT0) & PLL_LOCK)
        {
            return RT_EOK;
        }

        rt_hw_us_delay(1);
    }

    LOG_W("DCPHY PLL lock timeout");

    return -RT_ETIMEOUT;
}

static void dcphy_bias_enable(struct rk_mipi_dcphy *dcphy)
{
    RT_UNUSED(dcphy);

    dcphy_write(dcphy, BIAS_CON0, 0x0010);
    dcphy_write(dcphy, BIAS_CON1, 0x0110);
    dcphy_write(dcphy, BIAS_CON2, 0x0007);
}

static void dcphy_dphy_clk_timing(struct rk_mipi_dcphy *dcphy, const struct rk_dcphy_timing *t)
{
    rt_uint32_t val;

    dcphy_write(dcphy, DPHY_MC_GNR_CON0, 0xf000);
    dcphy_write(dcphy, DPHY_MC_ANA_CON0, EDGE_CON(7) | EDGE_CON_EN | UPDATE(0x5, 7, 4) | UPDATE(0x5, 3, 0));

    val = (dcphy->lane_mbps < 1500) ? HSTX_CLK_SEL : 0;
    val |= UPDATE(t->lpx, 11, 4);
    dcphy_write(dcphy, DPHY_MC_TIME_CON0, val);
    dcphy_write(dcphy, DPHY_MC_TIME_CON1, UPDATE(t->clk_zero, 15, 8) | UPDATE(t->clk_prepare, 7, 0));
    dcphy_write(dcphy, DPHY_MC_TIME_CON2, UPDATE(t->hs_exit, 15, 8) | UPDATE(t->clk_trail_eot, 7, 0));
    dcphy_write(dcphy, DPHY_MC_TIME_CON3, UPDATE(t->clk_post, 7, 0));
    dcphy_write(dcphy, DPHY_MC_TIME_CON4, 0x1f4);
}

static void dcphy_dphy_data_timing(struct rk_mipi_dcphy *dcphy, const struct rk_dcphy_timing *t)
{
    rt_uint32_t val = UPDATE(t->zero_3, 15, 8) | UPDATE(t->prepare_3, 7, 0);
    rt_uint32_t val2 = UPDATE(t->hs_exit, 15, 8) | UPDATE(t->trail_3, 7, 0);

    dcphy_write(dcphy, COMBO_MD0_ANA_CON0, UPDATE(0x5, 7, 4) | UPDATE(0x5, 3, 0));
    dcphy_write(dcphy, COMBO_MD0_TIME_CON0, UPDATE(t->lpx, 11, 4));
    dcphy_write(dcphy, COMBO_MD0_TIME_CON1, val);
    dcphy_write(dcphy, COMBO_MD0_TIME_CON2, val2);

    dcphy_write(dcphy, COMBO_MD1_TIME_CON0, UPDATE(t->lpx, 11, 4));
    dcphy_write(dcphy, COMBO_MD1_TIME_CON1, val);
    dcphy_write(dcphy, COMBO_MD1_TIME_CON2, val2);

    dcphy_write(dcphy, COMBO_MD2_TIME_CON0, UPDATE(t->lpx, 11, 4));
    dcphy_write(dcphy, COMBO_MD2_TIME_CON1, val);
    dcphy_write(dcphy, COMBO_MD2_TIME_CON2, val2);
}

static void dcphy_dphy_lane_enable(struct rk_mipi_dcphy *dcphy)
{
    dcphy_write(dcphy, DPHY_MC_GNR_CON1, UPDATE(0x2000, 15, 0));
    dcphy_set_bits(dcphy, DPHY_MC_GNR_CON0, PHY_ENABLE, PHY_ENABLE);

    if (dcphy->lanes >= 4)
    {
        dcphy_write(dcphy, DPHY_MD3_GNR_CON1, UPDATE(0x2000, 15, 0));
        dcphy_set_bits(dcphy, DPHY_MD3_GNR_CON0, PHY_ENABLE, PHY_ENABLE);
    }

    if (dcphy->lanes >= 3)
    {
        dcphy_write(dcphy, COMBO_MD2_GNR_CON1, UPDATE(0x2000, 15, 0));
        dcphy_set_bits(dcphy, COMBO_MD2_GNR_CON0, PHY_ENABLE, PHY_ENABLE);
    }

    if (dcphy->lanes >= 2)
    {
        dcphy_write(dcphy, COMBO_MD1_GNR_CON1, UPDATE(0x2000, 15, 0));
        dcphy_set_bits(dcphy, COMBO_MD1_GNR_CON0, PHY_ENABLE, PHY_ENABLE);
    }

    dcphy_write(dcphy, COMBO_MD0_GNR_CON1, UPDATE(0x2000, 15, 0));
    dcphy_set_bits(dcphy, COMBO_MD0_GNR_CON0, PHY_ENABLE, PHY_ENABLE);
}

static void dcphy_dphy_lane_disable(struct rk_mipi_dcphy *dcphy)
{
    dcphy_set_bits(dcphy, DPHY_MC_GNR_CON0, PHY_ENABLE, 0);
    dcphy_set_bits(dcphy, COMBO_MD0_GNR_CON0, PHY_ENABLE, 0);
    dcphy_set_bits(dcphy, COMBO_MD1_GNR_CON0, PHY_ENABLE, 0);
    dcphy_set_bits(dcphy, COMBO_MD2_GNR_CON0, PHY_ENABLE, 0);
    dcphy_set_bits(dcphy, DPHY_MD3_GNR_CON0, PHY_ENABLE, 0);
}

static rt_err_t rk_mipi_dcphy_configure(struct rt_phye *phye, union rt_phye_configure_opts *opts)
{
    struct rk_mipi_dcphy *dcphy = raw_to_rk_mipi_dcphy(phye);
    rt_uint64_t target_rate = opts->mipi_dphy.hs_clk_rate;
    rt_uint32_t lanes = opts->mipi_dphy.lanes;

    if (dcphy->mode != RT_PHYE_MODE_MIPI_DPHY)
    {
        return -RT_ENOSYS;
    }

    if (lanes > 4)
    {
        lanes = 4;
    }
    if (!lanes)
    {
        lanes = 4;
    }

    dcphy->lanes = lanes;
    dcphy_pll_calc(dcphy, target_rate);

    dcphy->lane_mbps = (rt_uint32_t)(dcphy->pll.rate / 1000000ULL);
    if (dcphy->lane_mbps < 200)
    {
        dcphy->lane_mbps = 500;
        dcphy_pll_calc(dcphy, 500000000ULL);
    }

    opts->mipi_dphy.hs_clk_rate = dcphy->pll.rate;
    opts->mipi_dphy.lanes = dcphy->lanes;

    return RT_EOK;
}

static rt_err_t rk_mipi_dcphy_init(struct rt_phye *phye)
{
    struct rk_mipi_dcphy *dcphy = raw_to_rk_mipi_dcphy(phye);

    rt_clk_prepare_enable(dcphy->pclk);
    rt_clk_prepare_enable(dcphy->ref_clk);

    if (!rt_is_err_or_null(dcphy->apb_rst))
    {
        rt_reset_control_deassert(dcphy->apb_rst);
    }

    return RT_EOK;
}

static rt_err_t rk_mipi_dcphy_exit(struct rt_phye *phye)
{
    struct rk_mipi_dcphy *dcphy = raw_to_rk_mipi_dcphy(phye);

    rt_clk_disable_unprepare(dcphy->ref_clk);
    rt_clk_disable_unprepare(dcphy->pclk);

    return RT_EOK;
}

static rt_err_t rk_mipi_dcphy_power_on(struct rt_phye *phye)
{
    struct rk_mipi_dcphy *dcphy = raw_to_rk_mipi_dcphy(phye);
    const struct rk_dcphy_timing *timing;

    if (dcphy->mode != RT_PHYE_MODE_MIPI_DPHY)
    {
        return -RT_ENOSYS;
    }

    if (!dcphy->lane_mbps)
    {
        dcphy->lane_mbps = 500;
        dcphy->lanes = 4;
        dcphy_pll_calc(dcphy, 500000000ULL);
    }

    timing = dcphy_get_timing(dcphy->lane_mbps);

    if (!rt_is_err_or_null(dcphy->m_phy_rst))
    {
        rt_reset_control_assert(dcphy->m_phy_rst);
    }

    dcphy_bias_enable(dcphy);
    dcphy_pll_program(dcphy);
    dcphy_dphy_clk_timing(dcphy, timing);
    dcphy_dphy_data_timing(dcphy, timing);
    dcphy_pll_enable(dcphy);
    dcphy_dphy_lane_enable(dcphy);

    if (!rt_is_err_or_null(dcphy->m_phy_rst))
    {
        rt_reset_control_deassert(dcphy->m_phy_rst);
    }

    rt_thread_mdelay(1);

    return RT_EOK;
}

static rt_err_t rk_mipi_dcphy_power_off(struct rt_phye *phye)
{
    struct rk_mipi_dcphy *dcphy = raw_to_rk_mipi_dcphy(phye);

    dcphy_dphy_lane_disable(dcphy);
    dcphy_set_bits(dcphy, PLL_CON0, PLL_EN, 0);

    return RT_EOK;
}

static rt_err_t rk_mipi_dcphy_set_mode(struct rt_phye *phye, enum rt_phye_mode mode, int submode)
{
    struct rk_mipi_dcphy *dcphy = raw_to_rk_mipi_dcphy(phye);

    RT_UNUSED(submode);

    dcphy->mode = mode;

    return RT_EOK;
}

static const struct rt_phye_ops rk_mipi_dcphy_ops =
{
    .init = rk_mipi_dcphy_init,
    .exit = rk_mipi_dcphy_exit,
    .power_on = rk_mipi_dcphy_power_on,
    .power_off = rk_mipi_dcphy_power_off,
    .set_mode = rk_mipi_dcphy_set_mode,
    .configure = rk_mipi_dcphy_configure,
};

static rt_err_t rk_mipi_dcphy_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node;
    struct rk_mipi_dcphy *dcphy = rt_calloc(1, sizeof(*dcphy));
    rt_err_t err;

    if (!dcphy)
    {
        return -RT_ENOMEM;
    }

    dcphy->regs = rt_ofw_iomap(np, 0);

    if (!dcphy->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    dcphy->pclk = rt_clk_get_by_name(dev, "pclk");
    dcphy->ref_clk = rt_clk_get_by_name(dev, "ref");

    if (rt_is_err_or_null(dcphy->pclk) || rt_is_err_or_null(dcphy->ref_clk))
    {
        err = -RT_EIO;
        goto _fail_unmap;
    }

    dcphy->m_phy_rst = rt_reset_control_get_by_name(dev, "m_phy");
    dcphy->apb_rst = rt_reset_control_get_by_name(dev, "apb");

    dcphy->lanes = 4;
    dcphy->mode = RT_PHYE_MODE_MIPI_DPHY;

    dcphy->parent.dev = dev;
    dcphy->parent.ops = &rk_mipi_dcphy_ops;

    if ((err = rt_phye_register(&dcphy->parent)))
    {
        goto _fail_unmap;
    }

    dev->user_data = dcphy;

    LOG_I("MIPI DCPHY %s probed", np->name);

    return RT_EOK;

_fail_unmap:
    rt_iounmap(dcphy->regs);
_fail:
    rt_free(dcphy);

    return err;
}

static const struct rt_ofw_node_id rk_mipi_dcphy_ids[] =
{
    { .compatible = "rockchip,rk3576-mipi-dcphy" },
    { .compatible = "rockchip,rk3588-mipi-dcphy" },
    { /* sentinel */ }
};

static struct rt_platform_driver rk_mipi_dcphy_driver =
{
    .name = "phy-rockchip-mipi-dcphy",
    .ids = rk_mipi_dcphy_ids,
    .probe = rk_mipi_dcphy_probe,
};
RT_PLATFORM_DRIVER_EXPORT(rk_mipi_dcphy_driver);
