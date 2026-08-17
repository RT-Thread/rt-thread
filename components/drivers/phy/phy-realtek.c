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
#include <drivers/phy.h>

#define DBG_TAG "rtdm.phy.rtl"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define RTL8211F_PHY_ID             0x001cc916
#define RTL8211FVD_PHY_ID           0x001cc878
#define RTL8211F_PHY_ID_MASK        0x001fffff

#define RTL8211F_PAGE_SELECT        0x1f

#define RTL8211F_PHYCR_PAGE         0x0a43
#define RTL8211F_PHYCR1             0x18
#define RTL8211F_PHYCR2             0x19

#define RTL8211F_RGMII_PAGE         0x0d08
#define RTL8211F_TXCR               0x11
#define RTL8211F_RXCR               0x15
#define RTL8211F_TX_DELAY           RT_BIT(8)
#define RTL8211F_RX_DELAY           RT_BIT(3)

#define RTL8211F_ALDPS_PLL_OFF      RT_BIT(1)
#define RTL8211F_ALDPS_ENABLE       RT_BIT(2)
#define RTL8211F_ALDPS_XTAL_OFF     RT_BIT(12)
#define RTL8211F_CLKOUT_EN          RT_BIT(0)

struct rtl821x_priv
{
    rt_uint16_t phycr1;
    rt_uint16_t phycr2;
    rt_bool_t has_phycr2;
};

static int rtl8211f_read_page(struct rt_phy_device *phydev)
{
    return rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RTL8211F_PAGE_SELECT);
}

static int rtl8211f_write_page(struct rt_phy_device *phydev, int page)
{
    return rt_phy_write(phydev, RT_MDIO_DEVAD_NONE, RTL8211F_PAGE_SELECT, page);
}

static int rtl8211f_read_paged(struct rt_phy_device *phydev, int page, int reg)
{
    int oldpage, val;

    oldpage = rtl8211f_read_page(phydev);
    if (oldpage < 0)
        return oldpage;

    val = rtl8211f_write_page(phydev, page);
    if (val < 0)
        return val;

    val = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, reg);
    rtl8211f_write_page(phydev, oldpage);

    return val;
}

static int rtl8211f_modify_paged(struct rt_phy_device *phydev, int page,
        int reg, rt_uint16_t mask, rt_uint16_t set)
{
    int oldpage, val, ret;

    oldpage = rtl8211f_read_page(phydev);
    if (oldpage < 0)
        return oldpage;

    ret = rtl8211f_write_page(phydev, page);
    if (ret < 0)
        return ret;

    val = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, reg);
    if (val < 0)
    {
        rtl8211f_write_page(phydev, oldpage);
        return val;
    }

    val &= ~mask;
    val |= set & mask;

    ret = rt_phy_write(phydev, RT_MDIO_DEVAD_NONE, reg, val);
    rtl8211f_write_page(phydev, oldpage);

    return ret;
}

static int rtl8211f_config_delay(struct rt_phy_device *phydev)
{
    rt_uint16_t tx_delay = 0;
    rt_uint16_t rx_delay = 0;
    int ret;

    switch (phydev->interface)
    {
    case RT_PHY_INTERFACE_MODE_RGMII:
        break;
    case RT_PHY_INTERFACE_MODE_RGMII_RXID:
        rx_delay = RTL8211F_RX_DELAY;
        break;
    case RT_PHY_INTERFACE_MODE_RGMII_TXID:
        tx_delay = RTL8211F_TX_DELAY;
        break;
    case RT_PHY_INTERFACE_MODE_RGMII_ID:
        tx_delay = RTL8211F_TX_DELAY;
        rx_delay = RTL8211F_RX_DELAY;
        break;
    default:
        return 0;
    }

    ret = rtl8211f_modify_paged(phydev, RTL8211F_RGMII_PAGE, RTL8211F_TXCR,
            RTL8211F_TX_DELAY, tx_delay);
    if (ret < 0)
        return ret;

    return rtl8211f_modify_paged(phydev, RTL8211F_RGMII_PAGE, RTL8211F_RXCR,
            RTL8211F_RX_DELAY, rx_delay);
}

static rt_bool_t rtl8211f_ofw_bool(struct rt_phy_device *phydev,
        const char *propname)
{
#ifdef RT_USING_OFW
    if (phydev->node)
        return rt_ofw_prop_read_bool(phydev->node, propname);
#else
    RT_UNUSED(phydev);
    RT_UNUSED(propname);
#endif

    return RT_FALSE;
}

static int rtl8211f_probe(struct rt_phy_device *phydev)
{
    struct rtl821x_priv *priv;
    int val;

    priv = rt_calloc(1, sizeof(*priv));
    if (!priv)
        return -RT_ENOMEM;

    val = rtl8211f_read_paged(phydev, RTL8211F_PHYCR_PAGE, RTL8211F_PHYCR1);
    if (val < 0)
    {
        rt_free(priv);
        return val;
    }

    priv->phycr1 = val & (RTL8211F_ALDPS_PLL_OFF | RTL8211F_ALDPS_ENABLE |
            RTL8211F_ALDPS_XTAL_OFF);
    if (rtl8211f_ofw_bool(phydev, "realtek,aldps-enable"))
    {
        priv->phycr1 |= RTL8211F_ALDPS_PLL_OFF | RTL8211F_ALDPS_ENABLE |
                RTL8211F_ALDPS_XTAL_OFF;
    }

    priv->has_phycr2 = phydev->phy_id != RTL8211FVD_PHY_ID;
    if (priv->has_phycr2)
    {
        val = rtl8211f_read_paged(phydev, RTL8211F_PHYCR_PAGE, RTL8211F_PHYCR2);
        if (val < 0)
        {
            rt_free(priv);
            return val;
        }

        priv->phycr2 = val & RTL8211F_CLKOUT_EN;
        if (rtl8211f_ofw_bool(phydev, "realtek,clkout-disable"))
            priv->phycr2 &= ~RTL8211F_CLKOUT_EN;
    }

    phydev->priv = priv;

    return 0;
}

static int rtl8211f_config_init(struct rt_phy_device *phydev)
{
    struct rtl821x_priv *priv = phydev->priv;
    int ret;

    if (!priv)
        return -RT_EINVAL;

    ret = rtl8211f_modify_paged(phydev, RTL8211F_PHYCR_PAGE, RTL8211F_PHYCR1,
            RTL8211F_ALDPS_PLL_OFF | RTL8211F_ALDPS_ENABLE |
            RTL8211F_ALDPS_XTAL_OFF, priv->phycr1);
    if (ret < 0)
        return ret;

    ret = rtl8211f_config_delay(phydev);
    if (ret < 0)
        return ret;

    if (priv->has_phycr2)
    {
        ret = rtl8211f_modify_paged(phydev, RTL8211F_PHYCR_PAGE,
                RTL8211F_PHYCR2, RTL8211F_CLKOUT_EN, priv->phycr2);
        if (ret < 0)
            return ret;

        return rt_phy_reset(phydev);
    }

    return 0;
}

static int rtl8211f_config(struct rt_phy_device *phydev)
{
    int ret;

    ret = rtl8211f_config_init(phydev);
    if (ret < 0)
        return ret;

    return rt_genphy_config(phydev);
}

static int rtl8211f_startup(struct rt_phy_device *phydev)
{
    int ret;

    ret = rt_genphy_startup(phydev);
    if (ret < 0 || !phydev->link)
    {
        if (ret < 0)
            return ret;

        return -ETIMEDOUT;
    }

    return 0;
}

static int rtl8211f_shutdown(struct rt_phy_device *phydev)
{
    if (phydev->priv)
    {
        rt_free(phydev->priv);
        phydev->priv = RT_NULL;
    }

    return 0;
}

static struct rt_phy_driver rtl8211f_driver =
{
    .uid        = RTL8211F_PHY_ID,
    .mask       = RTL8211F_PHY_ID_MASK,
    .name       = "RTL8211F",
    .features   = RT_PHY_GBIT_FEATURES,
    .probe      = rtl8211f_probe,
    .config     = rtl8211f_config,
    .startup    = rtl8211f_startup,
    .shutdown   = rtl8211f_shutdown,
};
RT_PHY_DRIVER_REGISTER(rtl8211f_driver);
