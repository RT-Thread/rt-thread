/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

#include <rtdevice.h>
#include <rtthread.h>
#include <dt-bindings/phye/phye.h>

#include <cpuport.h>

#define DBG_TAG "phye.rockchip.naneng-combphy"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define BIT_WRITEABLE_SHIFT     16
#define BIT_FLUSH               0xffffffff

struct rockchip_combphy;

struct combphy_reg
{
    rt_uint32_t offset;
    rt_uint16_t bitend;
    rt_uint16_t bitstart;
    rt_uint16_t disable;
    rt_uint16_t enable;
};

struct rockchip_combphy_grfcfg
{
    struct combphy_reg pcie_mode_set;
    struct combphy_reg usb_mode_set;
    struct combphy_reg sgmii_mode_set;
    struct combphy_reg qsgmii_mode_set;
    struct combphy_reg pipe_rxterm_set;
    struct combphy_reg pipe_txelec_set;
    struct combphy_reg pipe_txcomp_set;
    struct combphy_reg pipe_clk_24m;
    struct combphy_reg pipe_clk_25m;
    struct combphy_reg pipe_clk_100m;
    struct combphy_reg pipe_phymode_sel;
    struct combphy_reg pipe_rate_sel;
    struct combphy_reg pipe_rxterm_sel;
    struct combphy_reg pipe_txelec_sel;
    struct combphy_reg pipe_txcomp_sel;
    struct combphy_reg pipe_clk_ext;
    struct combphy_reg pipe_sel_usb;
    struct combphy_reg pipe_sel_qsgmii;
    struct combphy_reg pipe_phy_status;
    struct combphy_reg con0_for_pcie;
    struct combphy_reg con1_for_pcie;
    struct combphy_reg con2_for_pcie;
    struct combphy_reg con3_for_pcie;
    struct combphy_reg con0_for_sata;
    struct combphy_reg con1_for_sata;
    struct combphy_reg con2_for_sata;
    struct combphy_reg con3_for_sata;
    struct combphy_reg pipe_con0_for_sata;
    struct combphy_reg pipe_con1_for_sata;
    struct combphy_reg pipe_sgmii_mac_sel;
    struct combphy_reg pipe_xpcs_phy_ready;
    struct combphy_reg u3otg0_port_en;
    struct combphy_reg u3otg1_port_en;
    struct combphy_reg pipe_phy_grf_reset;
};

struct rockchip_combphy_cfg
{
    rt_bool_t force_det_out; /* Tx detect Rx errata */
    const struct rockchip_combphy_grfcfg *grfcfg;
    rt_err_t (*combphy_cfg)(struct rockchip_combphy *rk_cphy);
};

struct rockchip_combphy
{
    struct rt_phye parent;

    void *regs;
    rt_uint8_t type;

    struct rt_syscon *pipe_grf;
    struct rt_syscon *phy_grf;
    struct rt_reset_control *apb_rstc;
    struct rt_reset_control *phy_rstc;
    struct rt_clk *refclk;
    struct rt_clk_array *clk_arr;
    const struct rockchip_combphy_cfg *cfg;
    const struct rockchip_combphy_grfcfg *grfcfg;
};

#define raw_to_rockchip_combphy(raw) rt_container_of(raw, struct rockchip_combphy, parent)

static void rockchip_combphy_updatel(struct rockchip_combphy *rk_cphy,
        rt_uint32_t mask, rt_uint32_t val, int offset)
{
    rt_uint32_t tmp;

    tmp = HWREG32(rk_cphy->regs + offset);
    tmp = (tmp & (~mask)) | val;
    HWREG32(rk_cphy->regs + offset) = tmp;
}

static rt_err_t rockchip_combphy_param_write(struct rt_syscon *regmap,
        const struct combphy_reg *reg, rt_bool_t en)
{
    rt_uint32_t val, mask, tmp;

    tmp = en ? reg->enable : reg->disable;
    mask = RT_GENMASK(reg->bitend, reg->bitstart);
    val = (tmp << reg->bitstart) | (mask << BIT_WRITEABLE_SHIFT);

    return rt_syscon_write(regmap, reg->offset, val);
}

static rt_uint32_t rockchip_combphy_is_ready(struct rockchip_combphy *rk_cphy)
{
    rt_uint32_t mask, val;
    const struct rockchip_combphy_grfcfg *grfcfg = rk_cphy->cfg->grfcfg;

    mask = RT_GENMASK(grfcfg->pipe_phy_status.bitend, grfcfg->pipe_phy_status.bitstart);

    rt_syscon_read(rk_cphy->phy_grf, grfcfg->pipe_phy_status.offset, &val);
    val = (val & mask) >> grfcfg->pipe_phy_status.bitstart;

    return val;
}

/* Platfrom configure */
static rt_err_t rk3528_combphy_cfg(struct rockchip_combphy *rk_cphy)
{
    rt_ubase_t rate;
    struct rt_device *dev = rk_cphy->parent.dev;
    const struct rockchip_combphy_grfcfg *grfcfg = rk_cphy->cfg->grfcfg;

    switch (rk_cphy->type)
    {
    case PHY_TYPE_PCIE:
        /* Set SSC downward spread spectrum */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(5, 4), 0x1 << 4, 0x18);

        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con0_for_pcie, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con1_for_pcie, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con2_for_pcie, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con3_for_pcie, RT_TRUE);
        break;

    case PHY_TYPE_USB3:
        /* Set SSC downward spread spectrum */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(5, 4), 0x1 << 4, 0x18);

        /* Enable adaptive CTLE for USB3.0 Rx */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(17, 17), 0x01 << 17, 0x200);

        /* Set slow slew rate control for PI */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(2, 0), 0x07, 0x204);

        /* Set CDR phase path with 2x gain */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(5, 5), 0x01 << 5, 0x204);

        /* Set Rx squelch input filler bandwidth */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(2, 0), 0x06, 0x20c);

        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_txcomp_sel, RT_FALSE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_txelec_sel, RT_FALSE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->usb_mode_set, RT_TRUE);
        break;

    default:
        LOG_E("Incompatible PHY type");
        return -RT_EINVAL;
    }

    rate = rt_clk_get_rate(rk_cphy->refclk);

    switch (rate)
    {
    case 24000000:
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_24m, RT_TRUE);

        if (rk_cphy->type == PHY_TYPE_USB3)
        {
            /* Set ssc_cnt[10:0]=00101111101 & 31.5KHz */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(10, 0), 0x17d, 0x100);
        }
        else if (rk_cphy->type == PHY_TYPE_PCIE)
        {
            /* tx_trim[14]=1, Enable the counting clock of the rterm detect */
            rockchip_combphy_updatel(rk_cphy, 0, 1 << 14, 0x218);
        }
        break;

    case 100000000:
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_100m, RT_TRUE);

        if (rk_cphy->type == PHY_TYPE_PCIE)
        {
            /* PLL KVCO tuning fine */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(12, 10), 0x2 << 10, 0x18);

            /* su_trim[6:4]=111, [10:7]=1001, [2:0]=000, swing 650mv */
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x570804f0, 0x18);
        }
        break;

    default:
        LOG_E("Unsupported rate: %lu", rate);
        return -RT_EINVAL;
    }

    if (rt_dm_dev_prop_read_bool(dev, "rockchip,ext-refclk"))
    {
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_ext, RT_TRUE);

        if (rk_cphy->type == PHY_TYPE_PCIE && rate == 100000000)
        {
            /*
             * PLL charge pump current adjust = 111
             * PLL LPF R1 adjust = 1001
             * PLL KVCO adjust = 000 (min)
             * PLL KVCO fine tuning signals = 01
             */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(2, 0), RT_BIT(29) | (0x7 << 4 | 0x9 << 7), 0x108);
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(12, 10), 0x2 << 10, 0x18);
        }
    }

    if (rk_cphy->type == PHY_TYPE_PCIE)
    {
        if (rt_dm_dev_prop_read_bool(dev, "rockchip,enable-ssc"))
        {
            rockchip_combphy_updatel(rk_cphy, 0, RT_BIT(20), 0x100);
        }
    }

    return RT_EOK;
}

static const struct rockchip_combphy_grfcfg rk3528_combphy_grfcfgs =
{
    /* pipe-phy-grf */
    .pcie_mode_set      = { 0x48000,  5,  0, 0x0000, 0x0011 },
    .usb_mode_set       = { 0x48000,  5,  0, 0x0000, 0x0004 },
    .pipe_rxterm_set    = { 0x48000, 12, 12, 0x0000, 0x0001 },
    .pipe_txelec_set    = { 0x48004,  1,  1, 0x0000, 0x0001 },
    .pipe_txcomp_set    = { 0x48004,  4,  4, 0x0000, 0x0001 },
    .pipe_clk_24m       = { 0x48004, 14, 13, 0x0000, 0x0000 },
    .pipe_clk_100m      = { 0x48004, 14, 13, 0x0000, 0x0002 },
    .pipe_rxterm_sel    = { 0x48008,  8,  8, 0x0000, 0x0001 },
    .pipe_txelec_sel    = { 0x48008, 12, 12, 0x0000, 0x0001 },
    .pipe_txcomp_sel    = { 0x48008, 15, 15, 0x0000, 0x0001 },
    .pipe_clk_ext       = { 0x4800c,  9,  8, 0x0002, 0x0001 },
    .pipe_phy_status    = { 0x48034,  6,  6, 0x0001, 0x0000 },
    .con0_for_pcie      = { 0x48000, 15,  0, 0x0000, 0x0110 },
    .con1_for_pcie      = { 0x48004, 15,  0, 0x0000, 0x0000 },
    .con2_for_pcie      = { 0x48008, 15,  0, 0x0000, 0x0101 },
    .con3_for_pcie      = { 0x4800c, 15,  0, 0x0000, 0x0200 },
    /* pipe-grf */
    .u3otg0_port_en     = { 0x40044, 15,  0, 0x0181, 0x1100 },
};

static const struct rockchip_combphy_cfg rk3528_combphy_cfgs =
{
    .grfcfg = &rk3528_combphy_grfcfgs,
    .combphy_cfg = rk3528_combphy_cfg,
};

static rt_err_t rk3562_combphy_cfg(struct rockchip_combphy *rk_cphy)
{
    rt_ubase_t rate;
    struct rt_device *dev = rk_cphy->parent.dev;
    const struct rockchip_combphy_grfcfg *grfcfg = rk_cphy->cfg->grfcfg;

    switch (rk_cphy->type)
    {
    case PHY_TYPE_PCIE:
        /* Set SSC downward spread spectrum */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(5, 4), 0x1 << 4, 0x7c);

        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con0_for_pcie, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con1_for_pcie, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con2_for_pcie, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con3_for_pcie, RT_TRUE);
        break;
    case PHY_TYPE_USB3:
        /* Set SSC downward spread spectrum */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(5, 4), 0x1 << 4, 0x7c);

        /* Enable adaptive CTLE for USB3.0 Rx */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(0, 0), 0x01, 0x38);

        /* Set PLL KVCO fine tuning signals */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(4, 2), 0x2 << 2, 0x80);

        /* Set PLL LPF R1 to su_trim[10:7]=1001 */
        rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x4, 0x2c);

        /* Set PLL input clock divider 1/2 */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 6), 0x1 << 6, 0x14);

        /* Set PLL loop divider */
        rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x32, 0x44);

        /* Set PLL KVCO to min and set PLL charge pump current to max */
        rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0xf0, 0x28);

        /* Set Rx squelch input filler bandwidth */
        rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x0e, 0x50);

        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_sel_usb, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_txcomp_sel, RT_FALSE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_txelec_sel, RT_FALSE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->usb_mode_set, RT_TRUE);
        break;

    default:
        LOG_E("Incompatible PHY type");
        return -RT_EINVAL;
    }

    rate = rt_clk_get_rate(rk_cphy->refclk);

    switch (rate)
    {
    case 24000000:
        if (rk_cphy->type == PHY_TYPE_USB3)
        {
            /* Set ssc_cnt[9:0]=0101111101 & 31.5KHz */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 6), 0x1 << 6, 0x38);

            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 0), 0x5f, 0x3c);
        }
        break;

    case 25000000:
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_25m, RT_TRUE);
        break;

    case 100000000:
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_100m, RT_TRUE);

        if (rk_cphy->type == PHY_TYPE_PCIE)
        {
            /* PLL KVCO tuning fine */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(4, 2), 0x2 << 2, 0x80);

            /* Enable controlling random jitter, aka RMJ */
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x4, 0x2c);

            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 6), 0x1 << 6, 0x14);

            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x32, 0x44);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0xf0, 0x28);

            /* CKDRV output swing adjust to 650mv */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(4, 1), 0xb << 1, 0x34);
        }
        break;

    default:
        LOG_E("Unsupported rate: %lu", rate);
        return -RT_EINVAL;
    }

    if (rt_dm_dev_prop_read_bool(dev, "rockchip,ext-refclk"))
    {
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_ext, RT_TRUE);

        if (rk_cphy->type == PHY_TYPE_PCIE && rate == 100000000)
        {
            rockchip_combphy_updatel(rk_cphy, 0, 0x3 << 4 | 0x1 << 7, 0x30);

            rockchip_combphy_updatel(rk_cphy, 0, 0x1, 0x34);
        }
    }

    if (rt_dm_dev_prop_read_bool(dev, "rockchip,enable-ssc"))
    {
        rockchip_combphy_updatel(rk_cphy, 0, RT_BIT(4), 0x1c);
    }

    return RT_EOK;
}

static const struct rockchip_combphy_grfcfg rk3562_combphy_grfcfgs =
{
    /* pipe-phy-grf */
    .pcie_mode_set      = { 0x0000,  5,  0, 0x0000, 0x0011 },
    .usb_mode_set       = { 0x0000,  5,  0, 0x0000, 0x0004 },
    .pipe_rxterm_set    = { 0x0000, 12, 12, 0x0000, 0x0001 },
    .pipe_txelec_set    = { 0x0004,  1,  1, 0x0000, 0x0001 },
    .pipe_txcomp_set    = { 0x0004,  4,  4, 0x0000, 0x0001 },
    .pipe_clk_25m       = { 0x0004, 14, 13, 0x0000, 0x0001 },
    .pipe_clk_100m      = { 0x0004, 14, 13, 0x0000, 0x0002 },
    .pipe_phymode_sel   = { 0x0008,  1,  1, 0x0000, 0x0001 },
    .pipe_rate_sel      = { 0x0008,  2,  2, 0x0000, 0x0001 },
    .pipe_rxterm_sel    = { 0x0008,  8,  8, 0x0000, 0x0001 },
    .pipe_txelec_sel    = { 0x0008, 12, 12, 0x0000, 0x0001 },
    .pipe_txcomp_sel    = { 0x0008, 15, 15, 0x0000, 0x0001 },
    .pipe_clk_ext       = { 0x000c,  9,  8, 0x0002, 0x0001 },
    .pipe_sel_usb       = { 0x000c, 14, 13, 0x0000, 0x0001 },
    .pipe_phy_status    = { 0x0034,  6,  6, 0x0001, 0x0000 },
    .con0_for_pcie      = { 0x0000, 15,  0, 0x0000, 0x1000 },
    .con1_for_pcie      = { 0x0004, 15,  0, 0x0000, 0x0000 },
    .con2_for_pcie      = { 0x0008, 15,  0, 0x0000, 0x0101 },
    .con3_for_pcie      = { 0x000c, 15,  0, 0x0000, 0x0200 },
    .pipe_phy_grf_reset = { 0x0014,  1,  0, 0x0003, 0x0001 },
    /* peri-grf */
    .u3otg0_port_en     = { 0x0094, 15,  0, 0x0181, 0x1100 },
};

static const struct rockchip_combphy_cfg rk3562_combphy_cfgs =
{
    .grfcfg = &rk3562_combphy_grfcfgs,
    .combphy_cfg = rk3562_combphy_cfg,
    .force_det_out = RT_TRUE,
};

static rt_err_t rk3568_combphy_cfg(struct rockchip_combphy *rk_cphy)
{
    rt_ubase_t rate;
    struct rt_device *dev = rk_cphy->parent.dev;
    const struct rockchip_combphy_grfcfg *grfcfg = rk_cphy->cfg->grfcfg;

    switch (rk_cphy->type)
    {
    case PHY_TYPE_PCIE:
        /* Set SSC downward spread spectrum */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(5, 4), 0x1 << 4, 0x7c);

        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con0_for_pcie, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con1_for_pcie, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con2_for_pcie, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con3_for_pcie, RT_TRUE);
        break;

    case PHY_TYPE_USB3:
        /* Set SSC downward spread spectrum */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(5, 4), 0x1 << 4, 0x7c);

        /* Enable adaptive CTLE for USB3.0 Rx */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(0, 0), 0x01, 0x38);

        /* Set PLL KVCO fine tuning signals */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(4, 2), 0x2 << 2, 128);

        /* Set PLL LPF R1 to su_trim[10:7]=1001 */
        rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x4, 0x2c);

        /* Set PLL input clock divider 1/2 */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 6), 0x1 << 6, 0x14);

        /* Set PLL loop divider */
        rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x32, 0x44);

        /* Set PLL KVCO to min and set PLL charge pump current to max */
        rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0xf0, 0x28);

        /* Set Rx squelch input filler bandwidth */
        rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x0e, 0x50);

        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_sel_usb, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_txcomp_sel, RT_FALSE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_txelec_sel, RT_FALSE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->usb_mode_set, RT_TRUE);
        break;

    case PHY_TYPE_SATA:
        rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x41, 0x38);
        rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x8f, 0x18);

        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con0_for_sata, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con1_for_sata, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con2_for_sata, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con3_for_sata, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->pipe_grf, &grfcfg->pipe_con0_for_sata, RT_TRUE);
        break;

    case PHY_TYPE_SGMII:
        rockchip_combphy_param_write(rk_cphy->pipe_grf, &grfcfg->pipe_xpcs_phy_ready, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_phymode_sel, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_sel_qsgmii, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->sgmii_mode_set, RT_TRUE);
        break;

    case PHY_TYPE_QSGMII:
        rockchip_combphy_param_write(rk_cphy->pipe_grf, &grfcfg->pipe_xpcs_phy_ready, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_phymode_sel, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_rate_sel, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_sel_qsgmii, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->qsgmii_mode_set, RT_TRUE);
        break;

    default:
        LOG_E("Incompatible PHY type");
        return -RT_EINVAL;
    }

    rate = rt_clk_get_rate(rk_cphy->refclk);

    switch (rate)
    {
    case 24000000:
        if (rk_cphy->type == PHY_TYPE_USB3 || rk_cphy->type == PHY_TYPE_SATA)
        {
            /* Set ssc_cnt[9:0]=0101111101 & 31.5KHz */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 6), 0x1 << 6, 0x38);

            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 0), 0x5f, 0x3c);
        }
        break;

    case 25000000:
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_25m, RT_TRUE);
        break;

    case 100000000:
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_100m, RT_TRUE);

        if (rk_cphy->type == PHY_TYPE_PCIE)
        {
            /* PLL KVCO tuning fine */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(4, 2), 0x2 << 2, 0x80);

            /* Enable controlling random jitter, aka RMJ */
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x4, 0x2c);

            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 6), 0x1 << 6, 0x14);

            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x32, 0x44);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0xf0, 0x28);
        }
        else if (rk_cphy->type == PHY_TYPE_SATA)
        {
            /* Downward spread spectrum +500ppm */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 4), 0x5 << 4, 0x7c);
        }
        break;

    default:
        LOG_E("Unsupported rate: %lu", rate);
        return -RT_EINVAL;
    }

    if (rt_dm_dev_prop_read_bool(dev, "rockchip,ext-refclk"))
    {
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_ext, RT_TRUE);

        if (rk_cphy->type == PHY_TYPE_PCIE && rate == 100000000)
        {
            rockchip_combphy_updatel(rk_cphy, 0, 0x3 << 4 | 0x1 << 7, 0x30);

            rockchip_combphy_updatel(rk_cphy, 0, 0x1, 0x34);
        }
    }

    if (rt_dm_dev_prop_read_bool(dev, "rockchip,enable-ssc"))
    {
        rockchip_combphy_updatel(rk_cphy, 0, RT_BIT(4), 0x1c);
    }

    return RT_EOK;
}

static const struct rockchip_combphy_grfcfg rk3568_combphy_grfcfgs =
{
    /* pipe-phy-grf */
    .pcie_mode_set          = { 0x0000,  5,  0, 0x0000, 0x0011 },
    .usb_mode_set           = { 0x0000,  5,  0, 0x0000, 0x0004 },
    .sgmii_mode_set         = { 0x0000,  5,  0, 0x0000, 0x0001 },
    .qsgmii_mode_set        = { 0x0000,  5,  0, 0x0000, 0x0021 },
    .pipe_rxterm_set        = { 0x0000, 12, 12, 0x0000, 0x0001 },
    .pipe_txelec_set        = { 0x0004,  1,  1, 0x0000, 0x0001 },
    .pipe_txcomp_set        = { 0x0004,  4,  4, 0x0000, 0x0001 },
    .pipe_clk_25m           = { 0x0004, 14, 13, 0x0000, 0x0001 },
    .pipe_clk_100m          = { 0x0004, 14, 13, 0x0000, 0x0002 },
    .pipe_phymode_sel       = { 0x0008,  1,  1, 0x0000, 0x0001 },
    .pipe_rate_sel          = { 0x0008,  2,  2, 0x0000, 0x0001 },
    .pipe_rxterm_sel        = { 0x0008,  8,  8, 0x0000, 0x0001 },
    .pipe_txelec_sel        = { 0x0008, 12, 12, 0x0000, 0x0001 },
    .pipe_txcomp_sel        = { 0x0008, 15, 15, 0x0000, 0x0001 },
    .pipe_clk_ext           = { 0x000c,  9,  8, 0x0002, 0x0001 },
    .pipe_sel_usb           = { 0x000c, 14, 13, 0x0000, 0x0001 },
    .pipe_sel_qsgmii        = { 0x000c, 15, 13, 0x0000, 0x0007 },
    .pipe_phy_status        = { 0x0034,  6,  6, 0x0001, 0x0000 },
    .con0_for_pcie          = { 0x0000, 15,  0, 0x0000, 0x1000 },
    .con1_for_pcie          = { 0x0004, 15,  0, 0x0000, 0x0000 },
    .con2_for_pcie          = { 0x0008, 15,  0, 0x0000, 0x0101 },
    .con3_for_pcie          = { 0x000c, 15,  0, 0x0000, 0x0200 },
    .con0_for_sata          = { 0x0000, 15,  0, 0x0000, 0x0119 },
    .con1_for_sata          = { 0x0004, 15,  0, 0x0000, 0x0040 },
    .con2_for_sata          = { 0x0008, 15,  0, 0x0000, 0x80c3 },
    .con3_for_sata          = { 0x000c, 15,  0, 0x0000, 0x4407 },
    /* pipe-grf */
    .pipe_con0_for_sata     = { 0x0000, 15,  0, 0x0000, 0x2220 },
    .pipe_sgmii_mac_sel     = { 0x0040,  1,  1, 0x0000, 0x0001 },
    .pipe_xpcs_phy_ready    = { 0x0040,  2,  2, 0x0000, 0x0001 },
    .u3otg0_port_en         = { 0x0104, 15,  0, 0x0181, 0x1100 },
    .u3otg1_port_en         = { 0x0144, 15,  0, 0x0181, 0x1100 },
};

static const struct rockchip_combphy_cfg rk3568_combphy_cfgs =
{
    .grfcfg = &rk3568_combphy_grfcfgs,
    .combphy_cfg = rk3568_combphy_cfg,
    .force_det_out = RT_TRUE,
};

static rt_err_t rk3576_combphy_cfg(struct rockchip_combphy *rk_cphy)
{
    rt_ubase_t rate;
    struct rt_device *dev = rk_cphy->parent.dev;
    const struct rockchip_combphy_grfcfg *grfcfg = rk_cphy->cfg->grfcfg;

    switch (rk_cphy->type)
    {
    case PHY_TYPE_PCIE:
        /* Set SSC downward spread spectrum */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(5, 4), RT_BIT(4), 0x7c);

        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con0_for_pcie, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con1_for_pcie, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con2_for_pcie, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con3_for_pcie, RT_TRUE);
        break;

    case PHY_TYPE_USB3:
        /* Set SSC downward spread spectrum */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(5, 4), RT_BIT(4), 0x7c);

        /* Enable adaptive CTLE for USB3.0 Rx */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(0, 0), RT_BIT(0), 0x38);

        /* Set PLL KVCO fine tuning signals */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(4, 2), RT_BIT(3), 0x80);

        /* Set PLL LPF R1 to su_trim[10:7]=1001 */
        HWREG32(rk_cphy->regs + (0xb << 2)) = 0x4;

        /* Set PLL input clock divider 1/2 */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 6), RT_BIT(6), 0x14);

        /* Set PLL loop divider */
        HWREG32(rk_cphy->regs + (0x11 << 2)) = 0x32;

        /* Set PLL KVCO to min and set PLL charge pump current to max */
        HWREG32(rk_cphy->regs + (0xa << 2)) = 0xf0;

        /* Set Rx squelch input filler bandwidth */
        HWREG32(rk_cphy->regs + (0x14 << 2)) = 0x0d;

        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_txcomp_sel, RT_FALSE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_txelec_sel, RT_FALSE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->usb_mode_set, RT_TRUE);
        break;

    case PHY_TYPE_SATA:
        /* Enable adaptive CTLE for SATA Rx */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(0, 0), RT_BIT(0), 0x38);

        /* Set tx_rterm = 50 ohm and rx_rterm = 43.5 ohm */
        HWREG32(rk_cphy->regs + (0x06 << 2)) = 0x8f;

        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con0_for_sata, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con1_for_sata, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con2_for_sata, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con3_for_sata, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->pipe_grf, &grfcfg->pipe_con0_for_sata, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->pipe_grf, &grfcfg->pipe_con1_for_sata, RT_TRUE);
        break;

    default:
        LOG_E("Incompatible PHY type");
        return -RT_EINVAL;
    }

    rate = rt_clk_get_rate(rk_cphy->refclk);

    switch (rate)
    {
    case 24000000:
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_24m, RT_TRUE);

        if (rk_cphy->type == PHY_TYPE_USB3 || rk_cphy->type == PHY_TYPE_SATA)
        {
            /* Set ssc_cnt[9:0]=0101111101 & 31.5KHz */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 6), RT_BIT(6), 0xe << 2);

            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 0), 0x5f, 0xf << 2);
        }
        else if (rk_cphy->type == PHY_TYPE_PCIE)
        {
            /* PLL KVCO tuning fine */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(4, 2), 0x4 << 2, 0x20 << 2);

            /* Set up rx_trim */
            HWREG32(rk_cphy->regs + (0x1b << 2)) = 0x0;

            /* Set up su_trim: T0_1 */
            HWREG32(rk_cphy->regs + (0xa << 2)) = 0x90;
            HWREG32(rk_cphy->regs + (0xb << 2)) = 0x02;
            HWREG32(rk_cphy->regs + (0xd << 2)) = 0x57;

            HWREG32(rk_cphy->regs + (0xf << 2)) = 0x5f;
        }
        break;

    case 25000000:
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_25m, RT_TRUE);
        break;

    case 100000000:
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_100m, RT_TRUE);

        if (rk_cphy->type == PHY_TYPE_PCIE)
        {
            /* gate_tx_pck_sel length select work for L1SS */
            HWREG32(rk_cphy->regs + 0x74) = 0xc0;

            /* PLL KVCO tuning fine */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(4, 2), 0x4 << 2, 0x20 << 2);

            /* Set up rx_trim: PLL LPF C1 85pf R1 1.25kohm */
            HWREG32(rk_cphy->regs + (0x1b << 2)) = 0x4c;

            /* Set up su_trim: T3_P1 650mv */
            HWREG32(rk_cphy->regs + (0xa << 2)) = 0x90;
            HWREG32(rk_cphy->regs + (0xb << 2)) = 0x43;
            HWREG32(rk_cphy->regs + (0xc << 2)) = 0x88;
            HWREG32(rk_cphy->regs + (0xd << 2)) = 0x56;
        }
        else if (rk_cphy->type == PHY_TYPE_SATA)
        {
            /* downward spread spectrum +500ppm */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 4), 0x50, 0x1f << 2);

            /* ssc ppm adjust to 3500ppm */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(3, 0), 0x7, 0x9 << 2);
        }
        break;

    default:
        LOG_E("Unsupported rate: %lu", rate);
        return -RT_EINVAL;
    }

    if (rt_dm_dev_prop_read_bool(dev, "rockchip,ext-refclk"))
    {
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_ext, RT_TRUE);

        if (rk_cphy->type == PHY_TYPE_PCIE && rate == 100000000)
        {
            HWREG32(rk_cphy->regs + (0x20 << 2)) = 0x10;

            HWREG32(rk_cphy->regs + (0x1b << 2)) = 0x0c;

            /* Set up su_trim: T3_P1 650mv */
            HWREG32(rk_cphy->regs + (0xa << 2)) = 0x90;
            HWREG32(rk_cphy->regs + (0xb << 2)) = 0x43;
            HWREG32(rk_cphy->regs + (0xc << 2)) = 0x88;
            HWREG32(rk_cphy->regs + (0xd << 2)) = 0x56;
        }
    }

    if (rt_dm_dev_prop_read_bool(dev, "rockchip,enable-ssc"))
    {
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(4, 4), RT_BIT(4), 0x7 << 2);

        if (rk_cphy->type == PHY_TYPE_PCIE && rate == 24000000)
        {
            /* Xin24M T0_1 650mV */
            HWREG32(rk_cphy->regs + (0x10 << 2)) = 0x00;
            HWREG32(rk_cphy->regs + (0x11 << 2)) = 0x32;
            HWREG32(rk_cphy->regs + (0x1b << 2)) = 0x00;
            HWREG32(rk_cphy->regs + (0x0a << 2)) = 0x90;
            HWREG32(rk_cphy->regs + (0x0b << 2)) = 0x02;
            HWREG32(rk_cphy->regs + (0x0c << 2)) = 0x08;
            HWREG32(rk_cphy->regs + (0x0d << 2)) = 0x57;
            HWREG32(rk_cphy->regs + (0x0e << 2)) = 0x40;
            HWREG32(rk_cphy->regs + (0x0f << 2)) = 0x5f;
            HWREG32(rk_cphy->regs + (0x20 << 2)) = 0x10;
        }
    }

    return RT_EOK;
}

static const struct rockchip_combphy_grfcfg rk3576_combphy_grfcfgs =
{
    /* pipe-phy-grf */
    .pcie_mode_set      = { 0x0000, 5, 0, 0x00, 0x11 },
    .usb_mode_set       = { 0x0000, 5, 0, 0x00, 0x04 },
    .pipe_rxterm_set    = { 0x0000, 12, 12, 0x00, 0x01 },
    .pipe_txelec_set    = { 0x0004, 1, 1, 0x00, 0x01 },
    .pipe_txcomp_set    = { 0x0004, 4, 4, 0x00, 0x01 },
    .pipe_clk_24m       = { 0x0004, 14, 13, 0x00, 0x00 },
    .pipe_clk_25m       = { 0x0004, 14, 13, 0x00, 0x01 },
    .pipe_clk_100m      = { 0x0004, 14, 13, 0x00, 0x02 },
    .pipe_phymode_sel   = { 0x0008, 1, 1, 0x00, 0x01 },
    .pipe_rate_sel      = { 0x0008, 2, 2, 0x00, 0x01 },
    .pipe_rxterm_sel    = { 0x0008, 8, 8, 0x00, 0x01 },
    .pipe_txelec_sel    = { 0x0008, 12, 12, 0x00, 0x01 },
    .pipe_txcomp_sel    = { 0x0008, 15, 15, 0x00, 0x01 },
    .pipe_clk_ext       = { 0x000c, 9, 8, 0x02, 0x01 },
    .pipe_phy_status    = { 0x0034, 6, 6, 0x01, 0x00 },
    .con0_for_pcie      = { 0x0000, 15, 0, 0x00, 0x1000 },
    .con1_for_pcie      = { 0x0004, 15, 0, 0x00, 0x0000 },
    .con2_for_pcie      = { 0x0008, 15, 0, 0x00, 0x0101 },
    .con3_for_pcie      = { 0x000c, 15, 0, 0x00, 0x0200 },
    .con0_for_sata      = { 0x0000, 15, 0, 0x00, 0x0129 },
    .con1_for_sata      = { 0x0004, 15, 0, 0x00, 0x0000 },
    .con2_for_sata      = { 0x0008, 15, 0, 0x00, 0x80c1 },
    .con3_for_sata      = { 0x000c, 15, 0, 0x00, 0x0407 },
    .pipe_phy_grf_reset = { 0x0014, 1, 0, 0x3, 0x1 },
    /* php-grf */
    .pipe_con0_for_sata = { 0x001c, 2, 0, 0x00, 0x2 },
    .pipe_con1_for_sata = { 0x0020, 2, 0, 0x00, 0x2 },
    .u3otg1_port_en     = { 0x0038, 15, 0, 0x0189, 0x1100 },
};

static const struct rockchip_combphy_cfg rk3576_combphy_cfgs =
{
    .grfcfg = &rk3576_combphy_grfcfgs,
    .combphy_cfg = rk3576_combphy_cfg,
    .force_det_out = RT_TRUE,
};

static rt_err_t rk3588_combphy_cfg(struct rockchip_combphy *rk_cphy)
{
    rt_ubase_t rate;
    struct rt_device *dev = rk_cphy->parent.dev;
    const struct rockchip_combphy_grfcfg *grfcfg = rk_cphy->cfg->grfcfg;

    switch (rk_cphy->type)
    {
    case PHY_TYPE_PCIE:
        /* Set SSC downward spread spectrum */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(5, 4), 0x1 << 4, 0x7c);

        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con0_for_pcie, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con1_for_pcie, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con2_for_pcie, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con3_for_pcie, RT_TRUE);
        break;

    case PHY_TYPE_USB3:
        /* Set SSC downward spread spectrum */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(5, 4), 0x1 << 4, 0x7c);

        /* Enable adaptive CTLE for USB3.0 Rx */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(0, 0), 0x01, 0x38);

        /* Set PLL KVCO fine tuning signals */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(4, 2), 0x2 << 2, 0x80);

        /* Set PLL LPF R1 to su_trim[10:7]=1001 */
        rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x4, 0x2c);

        /* Set PLL input clock divider 1/2 */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 6), 0x1 << 6, 0x14);

        /* Set PLL loop divider */
        rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x32, 0x44);

        /* Set PLL KVCO to min and set PLL charge pump current to max */
        rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0xf0, 0x28);

        /* Set Rx squelch input filler bandwidth */
        rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x0d, 0x50);

        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_txcomp_sel, RT_FALSE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_txelec_sel, RT_FALSE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->usb_mode_set, RT_TRUE);
        break;

    case PHY_TYPE_SATA:
        /* Enable adaptive CTLE for SATA Rx */
        rockchip_combphy_updatel(rk_cphy, RT_GENMASK(0, 0), 0x1, 0x38);

        /* Set tx_rterm = 50 ohm and rx_rterm = 43.5 ohm */
        rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x8f, 0x18);

        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con0_for_sata, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con1_for_sata, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con2_for_sata, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->con3_for_sata, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->pipe_grf, &grfcfg->pipe_con0_for_sata, RT_TRUE);
        rockchip_combphy_param_write(rk_cphy->pipe_grf, &grfcfg->pipe_con1_for_sata, RT_TRUE);
        break;

    case PHY_TYPE_SGMII:
    case PHY_TYPE_QSGMII:
    default:
        LOG_E("Incompatible PHY type");
        return -RT_EINVAL;
    }

    rate = rt_clk_get_rate(rk_cphy->refclk);

    switch (rate)
    {
    case 24000000:
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_24m, RT_TRUE);

        if (rk_cphy->type == PHY_TYPE_USB3 || rk_cphy->type == PHY_TYPE_SATA)
        {
            /* Set ssc_cnt[9:0]=0101111101 & 31.5KHz */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 6), 0x1 << 6, 0x38);

            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 0), 0x5f, 0x3c);
        }
        else if (rk_cphy->type == PHY_TYPE_PCIE)
        {
            /* PLL KVCO tuning fine */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(4, 2), 0x4 << 2, 0x80);

            /* Set up rx_trim */
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x0, 0x6c);

            /* Set up su_trim: T0_1 */
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x90, 0x28);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x02, 0x2c);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x57, 0x34);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x5f, 0x3c);
        }
        break;
    case 25000000:
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_25m, RT_TRUE);
        break;

    case 100000000:
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_100m, RT_TRUE);

        if (rk_cphy->type == PHY_TYPE_PCIE)
        {
            /* gate_tx_pck_sel length select work for L1SS */
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0xc0, 0x74);

            /* PLL KVCO tuning fine */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(4, 2), 0x4 << 2, 0x80);

            /* Set up rx_trim: PLL LPF C1 85pf R1 1.25kohm */
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x4c, 0x6c);

            /* Set up su_trim: T3_P1 650mv */
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x90, 0x28);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x43, 0x2c);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x88, 0x30);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x56, 0x34);
        }
        else if (rk_cphy->type == PHY_TYPE_SATA)
        {
            /* downward spread spectrum +500ppm */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(7, 4), 0x5 << 4, 0x7c);

            /* ssc ppm adjust to 3500ppm */
            rockchip_combphy_updatel(rk_cphy, RT_GENMASK(3, 0), 0x7, 0x24);
        }
        break;

    default:
        LOG_E("Unsupported rate: %lu", rate);
        return -RT_EINVAL;
    }

    if (rt_dm_dev_prop_read_bool(dev, "rockchip,ext-refclk"))
    {
        rockchip_combphy_param_write(rk_cphy->phy_grf, &grfcfg->pipe_clk_ext, RT_TRUE);

        if (rk_cphy->type == PHY_TYPE_PCIE && rate == 100000000)
        {
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x10, 0x80);

            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x0c, 0x6c);

            /* Set up su_trim: T3_P1 650mv */
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x90, 0x28);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x43, 0x2c);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x88, 0x30);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x56, 0x34);
        }
    }

    if (rt_dm_dev_prop_read_bool(dev, "rockchip,enable-ssc"))
    {
        rockchip_combphy_updatel(rk_cphy, 0, RT_BIT(4), 0x1c);

        if (rk_cphy->type == PHY_TYPE_PCIE && rate == 24000000)
        {
            /* Xin24M T0_1 650mV */
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x00, 0x40);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x32, 0x44);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x00, 0x6c);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x90, 0x28);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x02, 0x2c);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x08, 0x30);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x57, 0x34);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x40, 0x38);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x5f, 0x3c);
            rockchip_combphy_updatel(rk_cphy, BIT_FLUSH, 0x10, 0x80);
        }
    }

    return RT_EOK;
}

static const struct rockchip_combphy_grfcfg rk3588_combphy_grfcfgs =
{
    /* pipe-phy-grf */
    .pcie_mode_set      = { 0x0000,  5,  0, 0x00, 0x0011 },
    .usb_mode_set       = { 0x0000,  5,  0, 0x00, 0x0004 },
    .pipe_rxterm_set    = { 0x0000, 12, 12, 0x00, 0x0001 },
    .pipe_txelec_set    = { 0x0004,  1,  1, 0x00, 0x0001 },
    .pipe_txcomp_set    = { 0x0004,  4,  4, 0x00, 0x0001 },
    .pipe_clk_24m       = { 0x0004, 14, 13, 0x00, 0x0000 },
    .pipe_clk_25m       = { 0x0004, 14, 13, 0x00, 0x0001 },
    .pipe_clk_100m      = { 0x0004, 14, 13, 0x00, 0x0002 },
    .pipe_rxterm_sel    = { 0x0008,  8,  8, 0x00, 0x0001 },
    .pipe_txelec_sel    = { 0x0008, 12, 12, 0x00, 0x0001 },
    .pipe_txcomp_sel    = { 0x0008, 15, 15, 0x00, 0x0001 },
    .pipe_clk_ext       = { 0x000c,  9,  8, 0x02, 0x0001 },
    .pipe_phy_status    = { 0x0034,  6,  6, 0x01, 0x0000 },
    .con0_for_pcie      = { 0x0000, 15,  0, 0x00, 0x1000 },
    .con1_for_pcie      = { 0x0004, 15,  0, 0x00, 0x0000 },
    .con2_for_pcie      = { 0x0008, 15,  0, 0x00, 0x0101 },
    .con3_for_pcie      = { 0x000c, 15,  0, 0x00, 0x0200 },
    .con0_for_sata      = { 0x0000, 15,  0, 0x00, 0x0129 },
    .con1_for_sata      = { 0x0004, 15,  0, 0x00, 0x0000 },
    .con2_for_sata      = { 0x0008, 15,  0, 0x00, 0x80c1 },
    .con3_for_sata      = { 0x000c, 15,  0, 0x00, 0x0407 },
    /* pipe-grf */
    .pipe_con0_for_sata = { 0x0000, 11,  5, 0x00, 0x0022 },
    .pipe_con1_for_sata = { 0x0004,  2,  0, 0x00, 0x0002 },
};

static const struct rockchip_combphy_cfg rk3588_combphy_cfgs =
{
    .grfcfg = &rk3588_combphy_grfcfgs,
    .combphy_cfg = rk3588_combphy_cfg,
    .force_det_out = RT_TRUE,
};

static rt_err_t rockchip_combphy_pcie_init(struct rockchip_combphy *rk_cphy)
{
    rt_err_t err = RT_EOK;

    if (rk_cphy->cfg->combphy_cfg)
    {
        if ((err = rk_cphy->cfg->combphy_cfg(rk_cphy)))
        {
            LOG_E("Failed to init PHY for %s", "PCIe");

            return err;
        }
    }

    if (rk_cphy->cfg->force_det_out)
    {
        rockchip_combphy_updatel(rk_cphy, 0, RT_BIT(5), 0x19 << 2);
    }

    return err;
}

static rt_err_t rockchip_combphy_usb3_init(struct rockchip_combphy *rk_cphy)
{
    rt_err_t err = RT_EOK;
    struct rt_device *dev = rk_cphy->parent.dev;
    const struct rockchip_combphy_cfg *phy_cfg = rk_cphy->cfg;

    if (rt_dm_dev_prop_read_bool(dev, "rockchip,dis-u3otg0-port"))
    {
        err = rockchip_combphy_param_write(rk_cphy->pipe_grf,
                &phy_cfg->grfcfg->u3otg0_port_en, RT_FALSE);

        return err;
    }
    else if (rt_dm_dev_prop_read_bool(dev, "rockchip,dis-u3otg1-port"))
    {
        err = rockchip_combphy_param_write(rk_cphy->pipe_grf,
                &phy_cfg->grfcfg->u3otg1_port_en, RT_FALSE);

        if (rt_ofw_node_is_compatible(dev->ofw_node, "rockchip,rk3576-naneng-combphy"))
        {
            rockchip_combphy_param_write(rk_cphy->phy_grf,
                    &phy_cfg->grfcfg->usb_mode_set, RT_TRUE);
        }

        return err;
    }

    if (rk_cphy->cfg->combphy_cfg)
    {
        if ((err = rk_cphy->cfg->combphy_cfg(rk_cphy)))
        {
            LOG_E("Failed to init PHY for %s", "USB3");
        }
    }

    return err;
}

static rt_err_t rockchip_combphy_sata_init(struct rockchip_combphy *rk_cphy)
{
    rt_err_t err = RT_EOK;

    if (rk_cphy->cfg->combphy_cfg)
    {
        if ((err = rk_cphy->cfg->combphy_cfg(rk_cphy)))
        {
            LOG_E("Failed to init PHY for %s", "SATA");
        }
    }

    return err;
}

static rt_err_t rockchip_combphy_sgmii_init(struct rockchip_combphy *rk_cphy)
{
    rt_err_t err = RT_EOK;

    if (rk_cphy->cfg->combphy_cfg)
    {
        if ((err = rk_cphy->cfg->combphy_cfg(rk_cphy)))
        {
            LOG_E("Failed to init PHY for %s", "SGMII");
        }
    }

    return err;
}

static rt_err_t rockchip_combphy_qsgmii_init(struct rockchip_combphy *rk_cphy)
{
    rt_err_t err = RT_EOK;

    if (rk_cphy->cfg->combphy_cfg)
    {
        if ((err = rk_cphy->cfg->combphy_cfg(rk_cphy)))
        {
            LOG_E("Failed to init PHY for %s", "QSGMII");
        }
    }

    return err;
}

static rt_err_t rockchip_combphy_init(struct rt_phye *phy)
{
    rt_err_t err;
    struct rockchip_combphy *rk_cphy = raw_to_rockchip_combphy(phy);
    struct rt_device *dev = rk_cphy->parent.dev;
    const struct rockchip_combphy_grfcfg *cfg = rk_cphy->cfg->grfcfg;

    if ((err = rt_clk_array_prepare_enable(rk_cphy->clk_arr)))
    {
        LOG_E("Failed to enable clks error = %s", rt_strerror(err));

        return -RT_EIO;
    }

    switch (rk_cphy->type)
    {
    case PHY_TYPE_PCIE:
        err = rockchip_combphy_pcie_init(rk_cphy);
        break;
    case PHY_TYPE_USB3:
        err = rockchip_combphy_usb3_init(rk_cphy);
        break;
    case PHY_TYPE_SATA:
        err = rockchip_combphy_sata_init(rk_cphy);
        break;
    case PHY_TYPE_SGMII:
        err = rockchip_combphy_sgmii_init(rk_cphy);
        break;
    case PHY_TYPE_QSGMII:
        err = rockchip_combphy_qsgmii_init(rk_cphy);
        break;

    default:
        LOG_E("Incompatible PHY type");
        err = -RT_EINVAL;
        break;
    }

    if (err)
    {
        LOG_E("Failed to init PHY for type %d", rk_cphy->type);

        goto _out_clk;
    }

    if ((err = rt_reset_control_deassert(rk_cphy->phy_rstc)))
    {
        goto _out_clk;
    }

    if (rk_cphy->grfcfg->pipe_phy_grf_reset.enable)
    {
        rockchip_combphy_param_write(rk_cphy->phy_grf,
                &rk_cphy->grfcfg->pipe_phy_grf_reset, RT_FALSE);
    }

    if (rk_cphy->type == PHY_TYPE_USB3 &&
        !rt_dm_dev_prop_read_bool(dev, "rockchip,dis-u3otg0-port") &&
        !rt_dm_dev_prop_read_bool(dev, "rockchip,dis-u3otg1-port"))
    {
        rt_uint32_t val;
        rt_int32_t timeout_us = 1000;

        for (; timeout_us > 0; timeout_us -= 10)
        {
            val = rockchip_combphy_is_ready(rk_cphy);

            if (val == cfg->pipe_phy_status.enable)
            {
                break;
            }

            rt_hw_us_delay(10);
            rt_hw_cpu_relax();
        }

        if (timeout_us <= 0)
        {
            LOG_W("Wait PHY status ready timeout");
        }
    }

    return RT_EOK;

_out_clk:
    rt_clk_array_disable_unprepare(rk_cphy->clk_arr);

    return -RT_EIO;
}

static rt_err_t rockchip_combphy_exit(struct rt_phye *phy)
{
    struct rockchip_combphy *rk_cphy = raw_to_rockchip_combphy(phy);

    if (rk_cphy->grfcfg->pipe_phy_grf_reset.enable)
    {
        rockchip_combphy_param_write(rk_cphy->phy_grf,
                &rk_cphy->grfcfg->pipe_phy_grf_reset, RT_TRUE);
    }

    rt_clk_array_disable_unprepare(rk_cphy->clk_arr);
    rt_reset_control_assert(rk_cphy->phy_rstc);

    return RT_EOK;
}

static rt_err_t rockchip_combphy_ofw_parse(struct rt_phye *phy,
        struct rt_ofw_cell_args *phy_args)
{
    struct rockchip_combphy *rk_cphy = raw_to_rockchip_combphy(phy);

    if (phy_args->args_count != 1)
    {
        LOG_E("Invalid number of arguments");

        return -RT_EINVAL;
    }

    if (rk_cphy->type != PHY_NONE && rk_cphy->type != phy_args->args[0])
    {
        LOG_W("PHY select type %d from type %d",
                phy_args->args[0], rk_cphy->type);
    }

    rk_cphy->type = phy_args->args[0];

    return RT_EOK;
}

static const struct rt_phye_ops rochchip_combphy_ops =
{
    .init = rockchip_combphy_init,
    .exit = rockchip_combphy_exit,
    .ofw_parse = rockchip_combphy_ofw_parse,
};

static void rockchip_combphy_free(struct rockchip_combphy *rk_cphy)
{
    if (rk_cphy->regs)
    {
        rt_iounmap(rk_cphy->regs);
    }

    if (!rt_is_err_or_null(rk_cphy->clk_arr))
    {
        rt_clk_array_put(rk_cphy->clk_arr);
    }

    if (!rt_is_err_or_null(rk_cphy->apb_rstc))
    {
        rt_reset_control_put(rk_cphy->apb_rstc);
    }

    if (!rt_is_err_or_null(rk_cphy->phy_rstc))
    {
        rt_reset_control_put(rk_cphy->phy_rstc);
    }

    rt_free(rk_cphy);
}

static rt_err_t rockchip_combphy_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_int32_t mac_id;
    rt_uint32_t values[4];
    struct rt_phye *phy;
    struct rt_device *dev = &pdev->parent;
    struct rockchip_combphy *rk_cphy = rt_calloc(1, sizeof(*rk_cphy));
    const struct rockchip_combphy_cfg *phy_cfg;

    if (!rk_cphy)
    {
        return -RT_ENOMEM;
    }

    phy_cfg = pdev->id->data;
    rk_cphy->type = PHY_NONE;
    rk_cphy->cfg = phy_cfg;
    rk_cphy->grfcfg = phy_cfg->grfcfg;

    rk_cphy->regs = rt_dm_dev_iomap(dev, 0);
    if (!rk_cphy->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rk_cphy->clk_arr = rt_clk_get_array(dev);
    if (rt_is_err(rk_cphy->clk_arr))
    {
        err = rt_ptr_err(rk_cphy->clk_arr);
        goto _fail;
    }

    for (int i = rk_cphy->clk_arr->count - 1; i >= 0; --i)
    {
        if (!rt_strncmp(rk_cphy->clk_arr->clks[i]->con_id, "refclk", 6))
        {
            rk_cphy->refclk = rk_cphy->clk_arr->clks[i];
        }
    }

    if (!rk_cphy->refclk)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    rk_cphy->pipe_grf = rt_syscon_find_by_ofw_phandle(dev->ofw_node, "rockchip,pipe-grf");
    if (!rk_cphy->pipe_grf)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rk_cphy->phy_grf = rt_syscon_find_by_ofw_phandle(dev->ofw_node, "rockchip,pipe-phy-grf");
    if (!rk_cphy->phy_grf)
    {
        err = -RT_EIO;
        goto _fail;
    }

    if (rt_dm_dev_prop_read_bool(dev, "rockchip,dis-u3otg0-port"))
    {
        rockchip_combphy_param_write(rk_cphy->pipe_grf,
                &phy_cfg->grfcfg->u3otg0_port_en, RT_FALSE);
    }
    else if (rt_dm_dev_prop_read_bool(dev, "rockchip,dis-u3otg1-port"))
    {
        rockchip_combphy_param_write(rk_cphy->pipe_grf,
                &phy_cfg->grfcfg->u3otg1_port_en, RT_FALSE);

        if (rt_ofw_node_is_compatible(dev->ofw_node, "rockchip,rk3576-naneng-combphy"))
        {
            rockchip_combphy_param_write(rk_cphy->phy_grf,
                    &phy_cfg->grfcfg->usb_mode_set, RT_TRUE);
        }
    }

    if (!rt_dm_dev_prop_read_s32(dev, "rockchip,sgmii-mac-sel", &mac_id) && mac_id > 0)
    {
        rockchip_combphy_param_write(rk_cphy->pipe_grf,
                &phy_cfg->grfcfg->pipe_sgmii_mac_sel, RT_TRUE);
    }

    if (rt_dm_dev_prop_read_u32_array_index(dev, "rockchip,pcie1ln-sel-bits",
            0, RT_ARRAY_SIZE(values), values) > 0)
    {
        rt_syscon_write(rk_cphy->pipe_grf, values[0],
                (RT_GENMASK(values[2], values[1]) << 16) | (values[3] << values[1]));
    }

    rk_cphy->apb_rstc = rt_reset_control_get_by_name(dev, "combphy-apb");
    if (rt_is_err(rk_cphy->apb_rstc))
    {
        err = rt_ptr_err(rk_cphy->apb_rstc);
        goto _fail;
    }

    rk_cphy->phy_rstc = rt_reset_control_get_by_name(dev, "combphy");
    if (rt_is_err(rk_cphy->phy_rstc))
    {
        err = rt_ptr_err(rk_cphy->phy_rstc);
        goto _fail;
    }

    err = rt_reset_control_assert(rk_cphy->phy_rstc);
    if (err)
    {
        goto _fail;
    }

    dev->user_data = rk_cphy;

    phy = &rk_cphy->parent;
    phy->dev = dev;
    phy->ops = &rochchip_combphy_ops;

    if ((err = rt_phye_register(phy)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rockchip_combphy_free(rk_cphy);

    return err;
}

static rt_err_t rockchip_combphy_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rockchip_combphy *rk_cphy = dev->user_data;

    rt_phye_unregister(&rk_cphy->parent);

    rockchip_combphy_free(rk_cphy);

    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_combphy_ofw_ids[] =
{
    { .compatible = "rockchip,rk3528-naneng-combphy", .data = &rk3528_combphy_cfgs },
    { .compatible = "rockchip,rk3562-naneng-combphy", .data = &rk3562_combphy_cfgs },
    { .compatible = "rockchip,rk3568-naneng-combphy", .data = &rk3568_combphy_cfgs },
    { .compatible = "rockchip,rk3576-naneng-combphy", .data = &rk3576_combphy_cfgs },
    { .compatible = "rockchip,rk3588-naneng-combphy", .data = &rk3588_combphy_cfgs },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_combphy_driver =
{
    .name = "phy-rockchip-naneng-combphy",
    .ids = rockchip_combphy_ofw_ids,

    .probe = rockchip_combphy_probe,
    .remove = rockchip_combphy_remove,
};

static int rockchip_combphy_drv_register(void)
{
    rt_platform_driver_register(&rockchip_combphy_driver);

    return 0;
}
INIT_PLATFORM_EXPORT(rockchip_combphy_drv_register);
