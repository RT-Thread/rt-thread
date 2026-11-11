/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/ofw_io.h>
#include <drivers/ofw.h>
#include <drivers/platform.h>
#include <drivers/syscon.h>
#include <drivers/clk.h>
#include <drivers/phy.h>
#include <drivers/reset.h>

#include "rockchip.h"
#include "dwmac-platform.h"

#define DBG_TAG "eth.dwmac.rk"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define GRF_BIT(nr)                     (RT_BIT(nr) | RT_BIT((nr) + 16))
#define GRF_CLR_BIT(nr)                 RT_BIT((nr) + 16)

#define DELAY_ENABLE(soc, tx, rx) \
    ((((tx) >= 0) ? soc##_GMAC_TXCLK_DLY_ENABLE : soc##_GMAC_TXCLK_DLY_DISABLE) | \
     (((rx) >= 0) ? soc##_GMAC_RXCLK_DLY_ENABLE : soc##_GMAC_RXCLK_DLY_DISABLE))

#define DELAY_ENABLE_BY_ID(soc, tx, rx, id) \
    ((((tx) >= 0) ? soc##_GMAC_TXCLK_DLY_ENABLE(id) : soc##_GMAC_TXCLK_DLY_DISABLE(id)) | \
     (((rx) >= 0) ? soc##_GMAC_RXCLK_DLY_ENABLE(id) : soc##_GMAC_RXCLK_DLY_DISABLE(id)))

#define DELAY_VALUE(soc, tx, rx) \
    ((((tx) >= 0) ? soc##_GMAC_CLK_TX_DL_CFG(tx) : 0) | \
     (((rx) >= 0) ? soc##_GMAC_CLK_RX_DL_CFG(rx) : 0))

struct dwmac_rk_soc;

struct dwmac_rk_priv
{
    struct rt_syscon *grf;
    struct rt_syscon *php_grf;
    int id;
    int tx_delay;
    int rx_delay;
    rt_bool_t clock_input;
    struct rt_clk *clk_phy;
    struct rt_clk *pclk_xpcs;
    struct rt_clk *clk_xpcs_eee;
    const struct dwmac_rk_soc *soc;
};

struct dwmac_rk_soc
{
    void (*set_rgmii)(struct dwmac_rk_priv *priv, int tx_delay, int rx_delay);
    void (*set_rmii)(struct dwmac_rk_priv *priv);
    rt_err_t (*fix_link_speed)(struct dwmac_eth *eth, int speed);
    void (*clock_selection)(struct dwmac_rk_priv *priv, rt_bool_t input, rt_bool_t enable);
    rt_bool_t need_php_grf;
};

static void dwmac_rk_setup_interface(struct dwmac_eth *eth);

static rt_err_t dwmac_rk_clk_prepare_enable(struct rt_clk *clk)
{
    if (rt_is_err_or_null(clk))
    {
        return RT_EOK;
    }

    return rt_clk_prepare_enable(clk);
}

static void dwmac_rk_clk_disable_unprepare(struct rt_clk *clk)
{
    if (!rt_is_err_or_null(clk))
    {
        rt_clk_disable_unprepare(clk);
    }
}

static long dwmac_rgmii_clock(int speed)
{
    switch (speed)
    {
    case SPEED_10:
        return 2500000;
    case SPEED_100:
        return 25000000;
    case SPEED_1000:
        return 125000000;
    default:
        return -1;
    }
}

static rt_err_t dwmac_rk_clk_set_rate_path(struct rt_clk *clk, rt_ubase_t rate)
{
    struct rt_clk_cell *cell, *parent_cell;
    struct rt_clk *parent_clk;
    rt_err_t err;

    if (rt_clk_get_rate(clk) == rate)
    {
        return RT_EOK;
    }

    err = rt_clk_set_rate(clk, rate);
    if (err != -RT_ENOSYS)
    {
        return err;
    }

    cell = clk->cell;
    if (cell->flags & RT_CLK_F_SET_RATE_PARENT)
    {
        parent_cell = rt_clk_cell_get_parent(cell);
        parent_clk = parent_cell ? rt_clk_cell_get_clk(parent_cell, RT_NULL) : RT_NULL;
        if (parent_clk)
        {
            err = dwmac_rk_clk_set_rate_path(parent_clk, rate);
            if (!err && rt_clk_get_rate(clk) == rate)
            {
                return RT_EOK;
            }
        }
    }

    /* Rockchip speed clocks are muxes whose parents provide the exact rates. */
    for (rt_uint8_t index = 0; index < cell->parents_nr; ++index)
    {
        parent_cell = rt_clk_cell_get_parent_by_index(cell, index);
        if (!parent_cell)
        {
            continue;
        }

        parent_clk = rt_clk_cell_get_clk(parent_cell, RT_NULL);
        if (!parent_clk || rt_clk_get_rate(parent_clk) != (rt_ubase_t)rate)
        {
            continue;
        }

        return rt_clk_set_parent(clk, parent_clk);
    }

    return -RT_ENOSYS;
}

static rt_err_t dwmac_rk_clk_set_rate(struct dwmac_eth *eth, long rate)
{
    if (rt_is_err_or_null(eth->mac_clk_speed) || rate < 0)
    {
        return rate < 0 ? -RT_EINVAL : RT_EOK;
    }

    return dwmac_rk_clk_set_rate_path(eth->mac_clk_speed, rate);
}

static int dwmac_rk_gmac_id(struct rt_ofw_node *np)
{
    int id = rt_ofw_get_alias_id(np, "ethernet");

    return id < 0 ? 0 : id;
}

static rt_err_t dwmac_rk_parse_common(struct dwmac_eth *eth,
        const struct dwmac_rk_soc *soc)
{
    struct dwmac_rk_priv *priv = eth->plat_priv;
    struct rt_ofw_node *np = eth->dev->ofw_node;
    struct rt_ofw_node *phy_np;
    const char *clock_in_out = RT_NULL;

    if (!priv)
    {
        priv = rt_calloc(1, sizeof(*priv));
        if (!priv)
        {
            return -RT_ENOMEM;
        }
        eth->plat_priv = priv;
    }

    priv->soc = soc;

    priv->grf = rt_syscon_find_by_ofw_phandle(np, "rockchip,grf");
    if (rt_is_err_or_null(priv->grf))
    {
        LOG_E("rockchip,grf not found");
        return -RT_EIO;
    }

    if (soc->need_php_grf)
    {
        priv->php_grf = rt_syscon_find_by_ofw_phandle(np, "rockchip,php_grf");
        if (rt_is_err_or_null(priv->php_grf))
        {
            LOG_E("rockchip,php_grf not found");
            return -RT_EIO;
        }
    }

    priv->id = dwmac_rk_gmac_id(np);

    if (rt_ofw_prop_read_u32(np, "tx_delay", (rt_uint32_t *)&priv->tx_delay))
    {
        priv->tx_delay = 0x30;
    }

    if (rt_ofw_prop_read_u32(np, "rx_delay", (rt_uint32_t *)&priv->rx_delay))
    {
        priv->rx_delay = 0x10;
    }

    if (rt_ofw_prop_read_string(np, "clock_in_out", &clock_in_out) ||
        !clock_in_out)
    {
        priv->clock_input = RT_TRUE;
    }
    else
    {
        priv->clock_input = !rt_strcmp(clock_in_out, "input");
    }

    LOG_I("gmac%d clock_in_out=%s clock_input=%d", priv->id,
            clock_in_out ? clock_in_out : "<missing>", priv->clock_input);

    if (eth->phy_interface == RT_PHY_INTERFACE_MODE_SGMII ||
        eth->phy_interface == RT_PHY_INTERFACE_MODE_QSGMII)
    {
        priv->pclk_xpcs = rt_clk_get_by_name(eth->dev, "pclk_xpcs");
        priv->clk_xpcs_eee = rt_clk_get_by_name(eth->dev, "clk_xpcs_eee");
    }

    phy_np = rt_ofw_parse_phandle(np, "phy-handle", 0);
    if (phy_np)
    {
        priv->clk_phy = rt_ofw_get_clk(phy_np, 0);
        rt_ofw_node_put(phy_np);
    }

    return RT_EOK;
}

/* RK3308 */
#define RK3308_GRF_MAC_CON0             0x04a0

#define RK3308_MAC_PHY_INTF_SEL_RMII    \
        (GRF_CLR_BIT(4) | GRF_CLR_BIT(5) | GRF_BIT(6))
#define RK3308_MAC_SPEED_10M            GRF_CLR_BIT(0)
#define RK3308_MAC_SPEED_100M           GRF_BIT(0)

static void dwmac_rk3308_set_rmii(struct dwmac_rk_priv *priv)
{
    rt_syscon_write(priv->grf, RK3308_GRF_MAC_CON0, RK3308_MAC_PHY_INTF_SEL_RMII);
}

static rt_err_t dwmac_rk3308_fix_link_speed(struct dwmac_eth *eth, int speed)
{
    struct dwmac_rk_priv *priv = eth->plat_priv;
    rt_err_t err;
    long rate;

    switch (speed)
    {
    case SPEED_10:
        rt_syscon_write(priv->grf, RK3308_GRF_MAC_CON0, RK3308_MAC_SPEED_10M);
        rate = 2500000;
        break;
    case SPEED_100:
        rt_syscon_write(priv->grf, RK3308_GRF_MAC_CON0, RK3308_MAC_SPEED_100M);
        rate = 25000000;
        break;
    default:
        return -RT_EINVAL;
    }

    err = dwmac_rk_clk_set_rate(eth, rate);
    return err;
}

static const struct dwmac_rk_soc dwmac_rk3308_soc =
{
    .set_rmii = dwmac_rk3308_set_rmii,
    .fix_link_speed = dwmac_rk3308_fix_link_speed,
};

/* RK3528 */
#define RK3528_VO_GRF_GMAC_CON          0x60018
#define RK3528_VPU_GRF_GMAC_CON5        0x40018
#define RK3528_VPU_GRF_GMAC_CON6        0x4001c

#define RK3528_GMAC_RXCLK_DLY_ENABLE    GRF_BIT(15)
#define RK3528_GMAC_RXCLK_DLY_DISABLE   GRF_CLR_BIT(15)
#define RK3528_GMAC_TXCLK_DLY_ENABLE    GRF_BIT(14)
#define RK3528_GMAC_TXCLK_DLY_DISABLE   GRF_CLR_BIT(14)
#define RK3528_GMAC_CLK_RX_DL_CFG(val)  HIWORD_UPDATE(val, 0xFF, 8)
#define RK3528_GMAC_CLK_TX_DL_CFG(val)  HIWORD_UPDATE(val, 0xFF, 0)

#define RK3528_GMAC0_PHY_INTF_SEL_RMII  GRF_BIT(1)
#define RK3528_GMAC1_PHY_INTF_SEL_RGMII GRF_CLR_BIT(8)
#define RK3528_GMAC1_PHY_INTF_SEL_RMII  GRF_BIT(8)
#define RK3528_GMAC1_CLK_SELET_CRU      GRF_CLR_BIT(12)
#define RK3528_GMAC1_CLK_SELET_IO       GRF_BIT(12)
#define RK3528_GMAC0_CLK_RMII_DIV2      GRF_BIT(3)
#define RK3528_GMAC1_CLK_RMII_DIV2      GRF_BIT(10)
#define RK3528_GMAC0_CLK_RMII_DIV20     GRF_CLR_BIT(3)
#define RK3528_GMAC1_CLK_RMII_DIV20     GRF_CLR_BIT(10)
#define RK3528_GMAC1_CLK_RGMII_DIV1     (GRF_CLR_BIT(11) | GRF_CLR_BIT(10))
#define RK3528_GMAC1_CLK_RGMII_DIV5     (GRF_BIT(11) | GRF_BIT(10))
#define RK3528_GMAC1_CLK_RGMII_DIV50    (GRF_BIT(11) | GRF_CLR_BIT(10))
#define RK3528_GMAC0_CLK_RMII_GATE      GRF_BIT(2)
#define RK3528_GMAC0_CLK_RMII_NOGATE   GRF_CLR_BIT(2)
#define RK3528_GMAC1_CLK_RMII_GATE      GRF_BIT(9)
#define RK3528_GMAC1_CLK_RMII_NOGATE   GRF_CLR_BIT(9)

static void dwmac_rk3528_set_rgmii(struct dwmac_rk_priv *priv,
        int tx_delay, int rx_delay)
{
    if (priv->id != 1)
    {
        LOG_W("RGMII on rk3528 gmac0 is not supported");
        return;
    }

    rt_syscon_write(priv->grf, RK3528_VPU_GRF_GMAC_CON5,
            RK3528_GMAC1_PHY_INTF_SEL_RGMII |
            DELAY_ENABLE(RK3528, tx_delay, rx_delay));
    rt_syscon_write(priv->grf, RK3528_VPU_GRF_GMAC_CON6,
            DELAY_VALUE(RK3528, tx_delay, rx_delay));
}

static void dwmac_rk3528_set_rmii(struct dwmac_rk_priv *priv)
{
    if (priv->id == 1)
    {
        rt_syscon_write(priv->grf, RK3528_VPU_GRF_GMAC_CON5,
                RK3528_GMAC1_PHY_INTF_SEL_RMII);
    }
    else
    {
        rt_syscon_write(priv->grf, RK3528_VO_GRF_GMAC_CON,
                RK3528_GMAC0_PHY_INTF_SEL_RMII | RK3528_GMAC0_CLK_RMII_DIV2);
    }
}

static rt_err_t dwmac_rk3528_fix_link_speed(struct dwmac_eth *eth, int speed)
{
    struct dwmac_rk_priv *priv = eth->plat_priv;
    rt_uint32_t val = 0, offset;

    switch (speed)
    {
    case SPEED_10:
        val = (priv->id == 1) ? RK3528_GMAC1_CLK_RMII_DIV20 :
                                RK3528_GMAC0_CLK_RMII_DIV20;
        break;
    case SPEED_100:
        val = (priv->id == 1) ? RK3528_GMAC1_CLK_RMII_DIV2 :
                                RK3528_GMAC0_CLK_RMII_DIV2;
        break;
    case SPEED_1000:
        if (priv->id != 1)
        {
            return -RT_EINVAL;
        }
        val = RK3528_GMAC1_CLK_RGMII_DIV1;
        break;
    default:
        return -RT_EINVAL;
    }

    offset = (priv->id == 1) ? RK3528_VPU_GRF_GMAC_CON5 : RK3528_VO_GRF_GMAC_CON;
    rt_syscon_write(priv->grf, offset, val);

    return RT_EOK;
}

static void dwmac_rk3528_clock_selection(struct dwmac_rk_priv *priv,
        rt_bool_t input, rt_bool_t enable)
{
    rt_uint32_t value;

    if (priv->id == 1)
    {
        value = input ? RK3528_GMAC1_CLK_SELET_IO : RK3528_GMAC1_CLK_SELET_CRU;
        value |= enable ? RK3528_GMAC1_CLK_RMII_NOGATE : RK3528_GMAC1_CLK_RMII_GATE;
        rt_syscon_write(priv->grf, RK3528_VPU_GRF_GMAC_CON5, value);
    }
    else
    {
        value = enable ? RK3528_GMAC0_CLK_RMII_NOGATE : RK3528_GMAC0_CLK_RMII_GATE;
        rt_syscon_write(priv->grf, RK3528_VO_GRF_GMAC_CON, value);
    }
}

static const struct dwmac_rk_soc dwmac_rk3528_soc =
{
    .set_rgmii = dwmac_rk3528_set_rgmii,
    .set_rmii = dwmac_rk3528_set_rmii,
    .fix_link_speed = dwmac_rk3528_fix_link_speed,
    .clock_selection = dwmac_rk3528_clock_selection,
};

/* RK3568 */
#define RK3568_GRF_GMAC0_CON0           0x0380
#define RK3568_GRF_GMAC0_CON1           0x0384
#define RK3568_GRF_GMAC1_CON0           0x0388
#define RK3568_GRF_GMAC1_CON1           0x038c

#define RK3568_GMAC_PHY_INTF_SEL_RGMII  \
        (GRF_BIT(4) | GRF_CLR_BIT(5) | GRF_CLR_BIT(6))
#define RK3568_GMAC_PHY_INTF_SEL_RMII   \
        (GRF_CLR_BIT(4) | GRF_CLR_BIT(5) | GRF_BIT(6))
#define RK3568_GMAC_RXCLK_DLY_ENABLE    GRF_BIT(1)
#define RK3568_GMAC_RXCLK_DLY_DISABLE   GRF_CLR_BIT(1)
#define RK3568_GMAC_TXCLK_DLY_ENABLE    GRF_BIT(0)
#define RK3568_GMAC_TXCLK_DLY_DISABLE   GRF_CLR_BIT(0)
#define RK3568_GMAC_CLK_RX_DL_CFG(val)   HIWORD_UPDATE(val, 0x7f, 8)
#define RK3568_GMAC_CLK_TX_DL_CFG(val)   HIWORD_UPDATE(val, 0x7f, 0)

static void dwmac_rk3568_set_rgmii(struct dwmac_rk_priv *priv,
        int tx_delay, int rx_delay)
{
    rt_uint32_t con0, con1;

    con0 = (priv->id == 1) ? RK3568_GRF_GMAC1_CON0 : RK3568_GRF_GMAC0_CON0;
    con1 = (priv->id == 1) ? RK3568_GRF_GMAC1_CON1 : RK3568_GRF_GMAC0_CON1;

    rt_syscon_write(priv->grf, con1,
            RK3568_GMAC_PHY_INTF_SEL_RGMII |
            DELAY_ENABLE(RK3568, tx_delay, rx_delay));
    rt_syscon_write(priv->grf, con0, DELAY_VALUE(RK3568, tx_delay, rx_delay));
}

static void dwmac_rk3568_set_rmii(struct dwmac_rk_priv *priv)
{
    rt_uint32_t con1;

    con1 = (priv->id == 1) ? RK3568_GRF_GMAC1_CON1 : RK3568_GRF_GMAC0_CON1;
    rt_syscon_write(priv->grf, con1, RK3568_GMAC_PHY_INTF_SEL_RMII);
}

static rt_err_t dwmac_rk3568_fix_link_speed(struct dwmac_eth *eth, int speed)
{
    struct dwmac_rk_priv *priv = eth->plat_priv;
    rt_err_t err;
    long rate = dwmac_rgmii_clock(speed);

    if (rate < 0)
    {
        return -RT_EINVAL;
    }

    err = dwmac_rk_clk_set_rate(eth, rate);
    if (err)
    {
        LOG_W("gmac%d set clk_mac_speed rate=%ld failed: %s",
                priv ? priv->id : -1, rate, rt_strerror(err));
    }

    return err;
}

static const struct dwmac_rk_soc dwmac_rk3568_soc =
{
    .set_rgmii = dwmac_rk3568_set_rgmii,
    .set_rmii = dwmac_rk3568_set_rmii,
    .fix_link_speed = dwmac_rk3568_fix_link_speed,
};

/* RK3576 */
#define RK3576_VCCIO0_1_3_IOC_CON2          0x6408
#define RK3576_VCCIO0_1_3_IOC_CON4          0x6410

#define RK3576_GRF_GMAC_CON0                0x0020
#define RK3576_GRF_GMAC_CON1                0x0024

#define RK3576_GMAC_RXCLK_DLY_ENABLE        GRF_BIT(15)
#define RK3576_GMAC_RXCLK_DLY_DISABLE       GRF_CLR_BIT(15)
#define RK3576_GMAC_TXCLK_DLY_ENABLE        GRF_BIT(7)
#define RK3576_GMAC_TXCLK_DLY_DISABLE       GRF_CLR_BIT(7)
#define RK3576_GMAC_CLK_RX_DL_CFG(val)      HIWORD_UPDATE(val, 0x7f, 8)
#define RK3576_GMAC_CLK_TX_DL_CFG(val)      HIWORD_UPDATE(val, 0x7f, 0)

#define RK3576_GMAC_RMII_MODE               GRF_BIT(3)
#define RK3576_GMAC_RGMII_MODE              GRF_CLR_BIT(3)
#define RK3576_GMAC_CLK_SELET_IO            GRF_BIT(7)
#define RK3576_GMAC_CLK_SELET_CRU           GRF_CLR_BIT(7)
#define RK3576_GMAC_CLK_RMII_DIV2            GRF_BIT(5)
#define RK3576_GMAC_CLK_RMII_DIV20          GRF_CLR_BIT(5)
#define RK3576_GMAC_CLK_RGMII_DIV1          (GRF_CLR_BIT(6) | GRF_CLR_BIT(5))
#define RK3576_GMAC_CLK_RGMII_DIV5          (GRF_BIT(6) | GRF_BIT(5))
#define RK3576_GMAC_CLK_RGMII_DIV50         (GRF_BIT(6) | GRF_CLR_BIT(5))
#define RK3576_GMAC_CLK_RMII_GATE           GRF_BIT(4)
#define RK3576_GMAC_CLK_RMII_NOGATE         GRF_CLR_BIT(4)

static void dwmac_rk3576_set_rgmii(struct dwmac_rk_priv *priv,
        int tx_delay, int rx_delay)
{
    rt_uint32_t offset_con;

    offset_con = (priv->id == 1) ? RK3576_GRF_GMAC_CON1 : RK3576_GRF_GMAC_CON0;
    rt_syscon_write(priv->grf, offset_con, RK3576_GMAC_RGMII_MODE);

    offset_con = (priv->id == 1) ? RK3576_VCCIO0_1_3_IOC_CON4 :
                                   RK3576_VCCIO0_1_3_IOC_CON2;

    rt_syscon_write(priv->php_grf, offset_con,
            DELAY_ENABLE(RK3576, tx_delay, rx_delay));
    rt_syscon_write(priv->php_grf, offset_con + 0x4,
            DELAY_ENABLE(RK3576, tx_delay, rx_delay));
    rt_syscon_write(priv->php_grf, offset_con,
            DELAY_VALUE(RK3576, tx_delay, rx_delay));
    rt_syscon_write(priv->php_grf, offset_con + 0x4,
            DELAY_VALUE(RK3576, tx_delay, rx_delay));
}

static void dwmac_rk3576_set_rmii(struct dwmac_rk_priv *priv)
{
    rt_uint32_t offset_con;

    offset_con = (priv->id == 1) ? RK3576_GRF_GMAC_CON1 : RK3576_GRF_GMAC_CON0;
    rt_syscon_write(priv->grf, offset_con, RK3576_GMAC_RMII_MODE);
}

static rt_err_t dwmac_rk3576_fix_link_speed(struct dwmac_eth *eth, int speed)
{
    struct dwmac_rk_priv *priv = eth->plat_priv;
    rt_uint32_t val = 0, offset_con;

    switch (speed)
    {
    case SPEED_10:
        val = (eth->phy_interface == RT_PHY_INTERFACE_MODE_RMII) ?
                RK3576_GMAC_CLK_RMII_DIV20 : RK3576_GMAC_CLK_RGMII_DIV50;
        break;
    case SPEED_100:
        val = (eth->phy_interface == RT_PHY_INTERFACE_MODE_RMII) ?
                RK3576_GMAC_CLK_RMII_DIV2 : RK3576_GMAC_CLK_RGMII_DIV5;
        break;
    case SPEED_1000:
        if (eth->phy_interface == RT_PHY_INTERFACE_MODE_RMII)
        {
            return -RT_EINVAL;
        }
        val = RK3576_GMAC_CLK_RGMII_DIV1;
        break;
    default:
        return -RT_EINVAL;
    }

    offset_con = (priv->id == 1) ? RK3576_GRF_GMAC_CON1 : RK3576_GRF_GMAC_CON0;
    rt_syscon_write(priv->grf, offset_con, val);

    return RT_EOK;
}

static void dwmac_rk3576_clock_selection(struct dwmac_rk_priv *priv,
        rt_bool_t input, rt_bool_t enable)
{
    rt_uint32_t val, offset_con;

    val = input ? RK3576_GMAC_CLK_SELET_IO : RK3576_GMAC_CLK_SELET_CRU;
    val |= enable ? RK3576_GMAC_CLK_RMII_NOGATE : RK3576_GMAC_CLK_RMII_GATE;

    offset_con = (priv->id == 1) ? RK3576_GRF_GMAC_CON1 : RK3576_GRF_GMAC_CON0;
    rt_syscon_write(priv->grf, offset_con, val);
}

static const struct dwmac_rk_soc dwmac_rk3576_soc =
{
    .set_rgmii = dwmac_rk3576_set_rgmii,
    .set_rmii = dwmac_rk3576_set_rmii,
    .fix_link_speed = dwmac_rk3576_fix_link_speed,
    .clock_selection = dwmac_rk3576_clock_selection,
    .need_php_grf = RT_TRUE,
};

/* RK3588 */
#define RK3588_GRF_GMAC_CON7            0x031c
#define RK3588_GRF_GMAC_CON8            0x0320
#define RK3588_GRF_GMAC_CON9            0x0324
#define RK3588_GRF_GMAC_CON0            0x0008
#define RK3588_GRF_CLK_CON1             0x0070

#define RK3588_GMAC_RXCLK_DLY_ENABLE(id)    GRF_BIT(2 * (id) + 3)
#define RK3588_GMAC_RXCLK_DLY_DISABLE(id)   GRF_CLR_BIT(2 * (id) + 3)
#define RK3588_GMAC_TXCLK_DLY_ENABLE(id)    GRF_BIT(2 * (id) + 2)
#define RK3588_GMAC_TXCLK_DLY_DISABLE(id)   GRF_CLR_BIT(2 * (id) + 2)
#define RK3588_GMAC_CLK_RX_DL_CFG(val)      HIWORD_UPDATE(val, 0xFF, 8)
#define RK3588_GMAC_CLK_TX_DL_CFG(val)      HIWORD_UPDATE(val, 0xFF, 0)

#define RK3588_GMAC_PHY_INTF_SEL_RGMII(id)  \
        (GRF_BIT(3 + (id) * 6) | GRF_CLR_BIT(4 + (id) * 6) | GRF_CLR_BIT(5 + (id) * 6))
#define RK3588_GMAC_PHY_INTF_SEL_RMII(id)   \
        (GRF_CLR_BIT(3 + (id) * 6) | GRF_CLR_BIT(4 + (id) * 6) | GRF_BIT(5 + (id) * 6))
#define RK3588_GMAC_CLK_RMII_MODE(id)       GRF_BIT(5 * (id))
#define RK3588_GMAC_CLK_RGMII_MODE(id)      GRF_CLR_BIT(5 * (id))
#define RK3588_GMAC_CLK_SELET_CRU(id)       GRF_BIT(5 * (id) + 4)
#define RK3588_GMAC_CLK_SELET_IO(id)        GRF_CLR_BIT(5 * (id) + 4)
#define RK3588_GMA_CLK_RMII_DIV2(id)        GRF_BIT(5 * (id) + 2)
#define RK3588_GMA_CLK_RMII_DIV20(id)       GRF_CLR_BIT(5 * (id) + 2)
#define RK3588_GMAC_CLK_RGMII_DIV1(id)      \
        (GRF_CLR_BIT(5 * (id) + 2) | GRF_CLR_BIT(5 * (id) + 3))
#define RK3588_GMAC_CLK_RGMII_DIV5(id)      \
        (GRF_BIT(5 * (id) + 2) | GRF_BIT(5 * (id) + 3))
#define RK3588_GMAC_CLK_RGMII_DIV50(id)     \
        (GRF_BIT(5 * (id) + 2) | GRF_CLR_BIT(5 * (id) + 3))
#define RK3588_GMAC_CLK_RMII_GATE(id)       GRF_BIT(5 * (id) + 1)
#define RK3588_GMAC_CLK_RMII_NOGATE(id)     GRF_CLR_BIT(5 * (id) + 1)

static void dwmac_rk3588_set_rgmii(struct dwmac_rk_priv *priv,
        int tx_delay, int rx_delay)
{
    rt_uint32_t offset_con;
    int id = priv->id;

    offset_con = (id == 1) ? RK3588_GRF_GMAC_CON9 : RK3588_GRF_GMAC_CON8;

    rt_syscon_write(priv->php_grf, RK3588_GRF_GMAC_CON0,
            RK3588_GMAC_PHY_INTF_SEL_RGMII(id));
    rt_syscon_write(priv->php_grf, RK3588_GRF_CLK_CON1,
            RK3588_GMAC_CLK_RGMII_MODE(id));
    rt_syscon_write(priv->grf, RK3588_GRF_GMAC_CON7,
            DELAY_ENABLE_BY_ID(RK3588, tx_delay, rx_delay, id));
    rt_syscon_write(priv->grf, offset_con,
            DELAY_VALUE(RK3588, tx_delay, rx_delay));
}

static void dwmac_rk3588_set_rmii(struct dwmac_rk_priv *priv)
{
    int id = priv->id;

    rt_syscon_write(priv->php_grf, RK3588_GRF_GMAC_CON0,
            RK3588_GMAC_PHY_INTF_SEL_RMII(id));
    rt_syscon_write(priv->php_grf, RK3588_GRF_CLK_CON1,
            RK3588_GMAC_CLK_RMII_MODE(id));
}

static rt_err_t dwmac_rk3588_fix_link_speed(struct dwmac_eth *eth, int speed)
{
    struct dwmac_rk_priv *priv = eth->plat_priv;
    rt_uint32_t val = 0;
    int id = priv->id;

    switch (speed)
    {
    case SPEED_10:
        val = (eth->phy_interface == RT_PHY_INTERFACE_MODE_RMII) ?
                RK3588_GMA_CLK_RMII_DIV20(id) : RK3588_GMAC_CLK_RGMII_DIV50(id);
        break;
    case SPEED_100:
        val = (eth->phy_interface == RT_PHY_INTERFACE_MODE_RMII) ?
                RK3588_GMA_CLK_RMII_DIV2(id) : RK3588_GMAC_CLK_RGMII_DIV5(id);
        break;
    case SPEED_1000:
        if (eth->phy_interface == RT_PHY_INTERFACE_MODE_RMII)
        {
            return -RT_EINVAL;
        }
        val = RK3588_GMAC_CLK_RGMII_DIV1(id);
        break;
    default:
        return -RT_EINVAL;
    }

    rt_syscon_write(priv->php_grf, RK3588_GRF_CLK_CON1, val);

    return RT_EOK;
}

static void dwmac_rk3588_clock_selection(struct dwmac_rk_priv *priv,
        rt_bool_t input, rt_bool_t enable)
{
    rt_uint32_t val;
    int id = priv->id;

    val = input ? RK3588_GMAC_CLK_SELET_IO(id) : RK3588_GMAC_CLK_SELET_CRU(id);
    val |= enable ? RK3588_GMAC_CLK_RMII_NOGATE(id) : RK3588_GMAC_CLK_RMII_GATE(id);
    rt_syscon_write(priv->php_grf, RK3588_GRF_CLK_CON1, val);
}

static const struct dwmac_rk_soc dwmac_rk3588_soc =
{
    .set_rgmii = dwmac_rk3588_set_rgmii,
    .set_rmii = dwmac_rk3588_set_rmii,
    .fix_link_speed = dwmac_rk3588_fix_link_speed,
    .clock_selection = dwmac_rk3588_clock_selection,
    .need_php_grf = RT_TRUE,
};

static rt_err_t dwmac_rk_parse_ofw(struct dwmac_eth *eth,
        const struct dwmac_rk_soc *soc)
{
    rt_err_t err;

    err = dwmac_rk_parse_common(eth, soc);
    if (err)
    {
        return err;
    }

    switch (eth->phy_interface)
    {
    case RT_PHY_INTERFACE_MODE_RGMII:
    case RT_PHY_INTERFACE_MODE_RGMII_ID:
    case RT_PHY_INTERFACE_MODE_RGMII_RXID:
    case RT_PHY_INTERFACE_MODE_RGMII_TXID:
        if (!rt_is_err_or_null(eth->mac_clk_rx))
        {
            rt_clk_put(eth->mac_clk_rx);
            eth->mac_clk_rx = RT_NULL;
        }
        if (!rt_is_err_or_null(eth->clk_mac_refout))
        {
            rt_clk_put(eth->clk_mac_refout);
            eth->clk_mac_refout = RT_NULL;
        }
        break;
    default:
        break;
    }

    return RT_EOK;
}

static void dwmac_rk_setup_interface(struct dwmac_eth *eth)
{
    struct dwmac_rk_priv *priv = eth->plat_priv;
    const struct dwmac_rk_soc *soc = priv->soc;

    switch (eth->phy_interface)
    {
    case RT_PHY_INTERFACE_MODE_RGMII:
        if (soc->set_rgmii)
        {
            soc->set_rgmii(priv, priv->tx_delay, priv->rx_delay);
        }
        break;
    case RT_PHY_INTERFACE_MODE_RGMII_ID:
        if (soc->set_rgmii)
        {
            soc->set_rgmii(priv, -1, -1);
        }
        break;
    case RT_PHY_INTERFACE_MODE_RGMII_RXID:
        if (soc->set_rgmii)
        {
            soc->set_rgmii(priv, priv->tx_delay, -1);
        }
        break;
    case RT_PHY_INTERFACE_MODE_RGMII_TXID:
        if (soc->set_rgmii)
        {
            soc->set_rgmii(priv, -1, priv->rx_delay);
        }
        break;
    case RT_PHY_INTERFACE_MODE_RMII:
        if (soc->set_rmii)
        {
            soc->set_rmii(priv);
        }
        if (soc->clock_selection)
        {
            soc->clock_selection(priv, priv->clock_input, RT_TRUE);
        }
        else if (!priv->clock_input && !rt_is_err_or_null(eth->mac_clk_speed))
        {
            rt_clk_set_rate(eth->mac_clk_speed, 50000000);
        }
        break;
    default:
        LOG_W("unsupported phy-mode %d, assume RGMII", eth->phy_interface);
        if (soc->set_rgmii)
        {
            soc->set_rgmii(priv, priv->tx_delay, priv->rx_delay);
        }
        break;
    }
}

static rt_err_t dwmac_rk_init(struct dwmac_eth *eth)
{
    struct dwmac_rk_priv *priv = eth->plat_priv;
    rt_err_t err;

    if (!priv || rt_is_err_or_null(priv->grf) || !priv->soc)
    {
        return -RT_EIO;
    }

    err = dwmac_rk_clk_prepare_enable(priv->clk_phy);
    if (err)
    {
        return err;
    }
    if ((err = dwmac_rk_clk_prepare_enable(priv->pclk_xpcs)))
    {
        goto _fail_clk_phy;
    }
    if ((err = dwmac_rk_clk_prepare_enable(priv->clk_xpcs_eee)))
    {
        goto _fail_pclk_xpcs;
    }

    dwmac_rk_setup_interface(eth);

    return RT_EOK;

_fail_pclk_xpcs:
    dwmac_rk_clk_disable_unprepare(priv->pclk_xpcs);
_fail_clk_phy:
    dwmac_rk_clk_disable_unprepare(priv->clk_phy);

    return err;
}

static rt_err_t dwmac_rk_fix_link_speed(struct dwmac_eth *eth, int speed)
{
    struct dwmac_rk_priv *priv = eth->plat_priv;

    if (priv && priv->soc && priv->soc->fix_link_speed)
    {
        return priv->soc->fix_link_speed(eth, speed);
    }

    return dwmac_rk_clk_set_rate(eth, dwmac_rgmii_clock(speed));
}

static void dwmac_rk_exit(struct dwmac_eth *eth)
{
    struct dwmac_rk_priv *priv = eth->plat_priv;

    if (priv)
    {
        dwmac_rk_clk_disable_unprepare(priv->clk_xpcs_eee);
        dwmac_rk_clk_disable_unprepare(priv->pclk_xpcs);
        dwmac_rk_clk_disable_unprepare(priv->clk_phy);
        if (!rt_is_err_or_null(priv->clk_xpcs_eee))
        {
            rt_clk_put(priv->clk_xpcs_eee);
        }
        if (!rt_is_err_or_null(priv->pclk_xpcs))
        {
            rt_clk_put(priv->pclk_xpcs);
        }
        if (!rt_is_err_or_null(priv->clk_phy))
        {
            rt_clk_put(priv->clk_phy);
        }
    }

    rt_free(priv);
    eth->plat_priv = RT_NULL;
}

#define DWMAC_RK_DEFINE(soc_name) \
    static rt_err_t dwmac_##soc_name##_parse_ofw(struct dwmac_eth *eth) \
    { \
        return dwmac_rk_parse_ofw(eth, &dwmac_##soc_name##_soc); \
    } \
    static const struct dwmac_plat_ops dwmac_##soc_name##_plat_ops = \
    { \
        .parse_ofw = dwmac_##soc_name##_parse_ofw, \
        .init = dwmac_rk_init, \
        .exit = dwmac_rk_exit, \
        .fix_link_speed = dwmac_rk_fix_link_speed, \
    }; \
    static const struct dwmac_config dwmac_##soc_name##_config = \
    { \
        .core_type = DWMAC_CORE_GMAC4, \
        .caps = DWMAC_CAP_TSO | DWMAC_CAP_PTP, \
        .dma_pbl = DWMAC_DMA_PBL, \
        .plat = &dwmac_##soc_name##_plat_ops, \
    };

DWMAC_RK_DEFINE(rk3308)
DWMAC_RK_DEFINE(rk3528)
DWMAC_RK_DEFINE(rk3568)
DWMAC_RK_DEFINE(rk3576)
DWMAC_RK_DEFINE(rk3588)

#undef DWMAC_RK_DEFINE

static const struct rt_ofw_node_id dwmac_rockchip_ofw_ids[] =
{
    { .compatible = "rockchip,rk3308-mac", .data = &dwmac_rk3308_config },
    { .compatible = "rockchip,rk3528-gmac", .data = &dwmac_rk3528_config },
    { .compatible = "rockchip,rk3568-gmac", .data = &dwmac_rk3568_config },
    { .compatible = "rockchip,rk3576-gmac", .data = &dwmac_rk3576_config },
    { .compatible = "rockchip,rk3588-gmac", .data = &dwmac_rk3588_config },
    { /* sentinel */ }
};

static void dwmac_rockchip_hw_stop(struct dwmac_eth *eth)
{
    rt_uint32_t val;

    if (!eth || !eth->mac_base)
    {
        return;
    }

    val = dwmac_readl(eth, GMAC_CONFIG);
    dwmac_writel(eth, GMAC_CONFIG, val & ~(GMAC_CONFIG_TE | GMAC_CONFIG_RE));

    val = dwmac_readl(eth, DMA_CHAN_TX_CONTROL(DWMAC_CHAN));
    dwmac_writel(eth, DMA_CHAN_TX_CONTROL(DWMAC_CHAN), val & ~DMA_CONTROL_ST);

    val = dwmac_readl(eth, DMA_CHAN_RX_CONTROL(DWMAC_CHAN));
    dwmac_writel(eth, DMA_CHAN_RX_CONTROL(DWMAC_CHAN), val & ~DMA_CONTROL_SR);

    dwmac_writel(eth, DMA_CHAN_INTR_ENA(DWMAC_CHAN), 0);
    dwmac_writel(eth, DMA_CHAN_STATUS(DWMAC_CHAN), 0xffffffff);
    rt_hw_us_delay(100);
}

static rt_err_t dwmac_rockchip_probe(struct rt_platform_device *pdev)
{
    const struct dwmac_config *cfg = pdev->id->data;

    if (!cfg)
    {
        return -RT_EINVAL;
    }

    return dwmac_platform_register(pdev, cfg);
}

static rt_err_t dwmac_rockchip_remove(struct rt_platform_device *pdev)
{
    return dwmac_platform_remove(pdev);
}

static rt_err_t dwmac_rockchip_shutdown(struct rt_platform_device *pdev)
{
    dwmac_rockchip_hw_stop(pdev->parent.user_data);

    return dwmac_platform_remove(pdev);
}

static struct rt_platform_driver dwmac_rockchip_driver =
{
    .name = "dwmac-rockchip",
    .ids = dwmac_rockchip_ofw_ids,
    .probe = dwmac_rockchip_probe,
    .remove = dwmac_rockchip_remove,
    .shutdown = dwmac_rockchip_shutdown,
};

RT_PLATFORM_DRIVER_EXPORT(dwmac_rockchip_driver);
