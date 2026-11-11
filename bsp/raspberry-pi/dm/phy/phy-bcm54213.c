/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-18     GuEe-GUI     BCM54213PE PHY for BCM2711 GENET
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/phy.h>

#define DBG_TAG "phy.bcm54213"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* BCM54213PE on Raspberry Pi 4 (BCM2711 GENET) */
#define PHY_ID_BCM54213PE               0x600d84a2

#define MII_BCM54XX_AUX_CTL             0x18
#define MII_BCM54XX_SHD                 0x1c

#define MII_BCM54XX_AUXCTL_SHDWSEL_MISC 0x07
#define MII_BCM54XX_AUXCTL_SHDWSEL_MASK 0x0007
#define MII_BCM54XX_AUXCTL_SHDWSEL_READ_SHIFT 12
#define  AUXCTL_MISC_RGMII_SKEW_EN      (1 << 8)
#define  AUXCTL_MISC_WREN               (1 << 15)

#define MII_BCM54XX_SHD_WRITE           (1 << 15)
#define MII_BCM54XX_SHD_VAL(x)          (((x) & 0x1f) << 10)
#define MII_BCM54XX_SHD_DATA(x)         (((x) & 0x3ff) << 0)

#define BCM54810_SHD_CLK_CTL            0x3
#define  CLK_CTL_GTXCLK_EN              (1 << 9)

static int bcm54xx_auxctl_read(struct rt_phy_device *phydev, rt_uint16_t regnum)
{
    rt_phy_write(phydev, RT_MDIO_DEVAD_NONE, MII_BCM54XX_AUX_CTL,
                 MII_BCM54XX_AUXCTL_SHDWSEL_MASK |
                 (regnum << MII_BCM54XX_AUXCTL_SHDWSEL_READ_SHIFT));

    return rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, MII_BCM54XX_AUX_CTL);
}

static int bcm54xx_auxctl_write(struct rt_phy_device *phydev, rt_uint16_t regnum, rt_uint16_t val)
{
    return rt_phy_write(phydev, RT_MDIO_DEVAD_NONE, MII_BCM54XX_AUX_CTL, regnum | val);
}

static int bcm_phy_read_shadow(struct rt_phy_device *phydev, rt_uint16_t shadow)
{
    int val;

    rt_phy_write(phydev, RT_MDIO_DEVAD_NONE, MII_BCM54XX_SHD, MII_BCM54XX_SHD_VAL(shadow));
    val = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, MII_BCM54XX_SHD);

    return MII_BCM54XX_SHD_DATA(val);
}

static int bcm_phy_write_shadow(struct rt_phy_device *phydev, rt_uint16_t shadow, rt_uint16_t val)
{
    return rt_phy_write(phydev, RT_MDIO_DEVAD_NONE, MII_BCM54XX_SHD,
                        MII_BCM54XX_SHD_WRITE | MII_BCM54XX_SHD_VAL(shadow) | MII_BCM54XX_SHD_DATA(val));
}

static int bcm54xx_config_clock_delay(struct rt_phy_device *phydev)
{
    int val, err;

    val = bcm54xx_auxctl_read(phydev, MII_BCM54XX_AUXCTL_SHDWSEL_MISC);
    if (val < 0)
    {
        return val;
    }

    val |= AUXCTL_MISC_WREN;

    if (phydev->interface == RT_PHY_INTERFACE_MODE_RGMII ||
        phydev->interface == RT_PHY_INTERFACE_MODE_RGMII_TXID)
    {
        val &= ~AUXCTL_MISC_RGMII_SKEW_EN;
    }
    else if (phydev->interface == RT_PHY_INTERFACE_MODE_RGMII_ID ||
             phydev->interface == RT_PHY_INTERFACE_MODE_RGMII_RXID)
    {
        val |= AUXCTL_MISC_RGMII_SKEW_EN;
    }

    err = bcm54xx_auxctl_write(phydev, MII_BCM54XX_AUXCTL_SHDWSEL_MISC, val);
    if (err < 0)
    {
        return err;
    }

    val = bcm_phy_read_shadow(phydev, BCM54810_SHD_CLK_CTL);
    if (val < 0)
    {
        return val;
    }

    if (phydev->interface == RT_PHY_INTERFACE_MODE_RGMII ||
        phydev->interface == RT_PHY_INTERFACE_MODE_RGMII_RXID)
    {
        val &= ~CLK_CTL_GTXCLK_EN;
    }
    else if (phydev->interface == RT_PHY_INTERFACE_MODE_RGMII_ID ||
             phydev->interface == RT_PHY_INTERFACE_MODE_RGMII_TXID)
    {
        val |= CLK_CTL_GTXCLK_EN;
    }

    return bcm_phy_write_shadow(phydev, BCM54810_SHD_CLK_CTL, val);
}

static int bcm54213pe_config(struct rt_phy_device *phydev)
{
    int err;

    err = bcm54xx_config_clock_delay(phydev);
    if (err < 0)
    {
        return err;
    }

    LOG_D("PHY config if=%d", phydev->interface);

    return rt_genphy_config(phydev);
}

static int bcm54213pe_read_bmsr(struct rt_phy_device *phydev)
{
    int bmsr;

    /* BMSR link status is latch-low; read twice for current value */
    bmsr = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_BMSR);
    if (bmsr < 0)
    {
        return bmsr;
    }

    return rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_BMSR);
}

static int bcm54213pe_startup(struct rt_phy_device *phydev)
{
    int bmsr;

    /*
     * Non-blocking startup: do not wait for autoneg in init context.
     * Link-up / retry is handled by GENET link IRQ work and periodic poll.
     */
    bmsr = bcm54213pe_read_bmsr(phydev);
    if (bmsr < 0)
    {
        return bmsr;
    }

    if (bmsr & RT_BMSR_LSTATUS)
    {
        phydev->link = 1;
        rt_genphy_parse_link(phydev);
        LOG_I("PHY up: speed=%d duplex=%d", phydev->speed, phydev->duplex);
        return 0;
    }

    phydev->link = 0;
    LOG_I("PHY link down at boot, defer to link event / retry work");
    return 0;
}

static struct rt_phy_driver bcm54213pe_driver =
{
    .uid        = PHY_ID_BCM54213PE,
    .mask       = 0xffffffff,
    .name       = "Broadcom BCM54213PE",
    .features   = RT_PHY_GBIT_FEATURES,
    .config     = bcm54213pe_config,
    .startup    = bcm54213pe_startup,
};

static int bcm54213_phy_drv_register(void)
{
    rt_phy_driver_register(&bcm54213pe_driver);

    return 0;
}
INIT_PLATFORM_EXPORT(bcm54213_phy_drv_register);
