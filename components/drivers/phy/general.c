/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-08     zhujiale    the first version
 */
#include <rtthread.h>
#include <drivers/phy.h>
#include "general_phy.h"
#define DBG_TAG "rtdm.phy"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static int __genphy_set_adv(int adv,int advertise)
{
    adv &= ~(RT_ADVERTISE_ALL | RT_ADVERTISE_100BASE4 | RT_ADVERTISE_PAUSE_CAP |
         RT_ADVERTISE_PAUSE_ASYM);
    if (advertise & RT_ADVERTISED__10baseT_Half)
        adv |= RT_ADVERTISE_10HALF;
    if (advertise & RT_ADVERTISED__10baseT_Full)
        adv |= RT_ADVERTISE_10FULL;
    if (advertise & RT_ADVERTISED__100baseT_Half)
        adv |= RT_ADVERTISE_100HALF;
    if (advertise & RT_ADVERTISED__100baseT_Full)
        adv |= RT_ADVERTISE_100FULL;
    if (advertise & RT_ADVERTISED__Pause)
        adv |= RT_ADVERTISE_PAUSE_CAP;
    if (advertise & RT_ADVERTISED__Asym_Pause)
        adv |= RT_ADVERTISE_PAUSE_ASYM;
    if (advertise & RT_ADVERTISED__1000baseX_Half)
        adv |= RT_ADVERTISE_1000XHALF;
    if (advertise & RT_ADVERTISED__1000baseX_Full)
        adv |= RT_ADVERTISE_1000XFULL;

    return adv;
}
static int __genphy_config_advert(struct rt_phy_device *phydev)
{
    rt_uint32_t advertise;
    int oldadv, adv, bmsr;
    int err, changed = 0;

    phydev->advertising &= phydev->supported;
    advertise = phydev->advertising;

    adv = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_ADVERTISE);
    oldadv = adv;

    if (adv < 0)
        return adv;

    adv = __genphy_set_adv(adv, advertise);

    if (adv != oldadv)
    {
        err = rt_phy_write(phydev, RT_MDIO_DEVAD_NONE, RT_MII_ADVERTISE, adv);

        if (err < 0)
            return err;
        changed = 1;
    }

    bmsr = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_BMSR);
    if (bmsr < 0)
        return bmsr;

    if (!(bmsr & RT_BMSR_ESTATEN))
        return changed;

    adv = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_CTRL1000);
    oldadv = adv;

    if (adv < 0)
        return adv;

    adv &= ~(RT_ADVERTISE_1000FULL | RT_ADVERTISE_1000HALF);

    if (phydev->supported & (RT_SUPPORTED_1000baseT_Half |
                RT_SUPPORTED_1000baseT_Full))
                {
        if (advertise & RT_SUPPORTED_1000baseT_Half)
            adv |= RT_ADVERTISE_1000HALF;
        if (advertise & RT_SUPPORTED_1000baseT_Full)
            adv |= RT_ADVERTISE_1000FULL;
    }

    if (adv != oldadv)
        changed = 1;

    err = rt_phy_write(phydev, RT_MDIO_DEVAD_NONE, RT_MII_CTRL1000, adv);
    if (err < 0)
        return err;

    return changed;
}

int __genphy_restart_aneg(struct rt_phy_device *phydev)
{
    int ctl;

    ctl = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_BMCR);

    if (ctl < 0)
        return ctl;

    ctl |= (RT_BMCR_ANENABLE | RT_BMCR_ANRESTART);

    ctl &= ~(RT_BMCR_ISOLATE);

    ctl = rt_phy_write(phydev, RT_MDIO_DEVAD_NONE, RT_MII_BMCR, ctl);

    return ctl;
}

int rt_genphy_config_aneg(struct rt_phy_device *phydev)
{
    int result;
    int err;
    int ctl = RT_BMCR_ANRESTART;
    if (phydev->autoneg != AUTONEG_ENABLE)
    {
        phydev->pause = 0;

        if (phydev->speed == SPEED_1000)
            ctl |= RT_BMCR_SPEED1000;
        else if (phydev->speed == SPEED_100)
            ctl |= RT_BMCR_SPEED100;

        if (phydev->duplex == DUPLEX_FULL)
            ctl |= RT_BMCR_FULLDPLX;

        err = rt_phy_write(phydev, RT_MDIO_DEVAD_NONE, RT_MII_BMCR, ctl);

        return err;
    }

    result = __genphy_config_advert(phydev);

    if (result < 0)
        return result;

    if (result == 0)
    {
        int ctl = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_BMCR);

        if (ctl < 0)
            return ctl;

        if (!(ctl & RT_BMCR_ANENABLE) || (ctl & RT_BMCR_ISOLATE))
            result = 1;
    }

    if (result > 0)
        result = __genphy_restart_aneg(phydev);

    return result;
}

int rt_genphy_update_link(struct rt_phy_device *phydev)
{
    unsigned int mii_reg;

    mii_reg = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_BMSR);

    if (phydev->link && mii_reg & RT_BMSR_LSTATUS)
        return 0;

    if ((phydev->autoneg == AUTONEG_ENABLE) &&
        !(mii_reg & RT_BMSR_ANEGCOMPLETE))
        {
        int i = 0;
        rt_kprintf("Waiting for PHY auto negotiation to complete");
        while (!(mii_reg & RT_BMSR_ANEGCOMPLETE))
        {

            if (i > (RT_PHY_ANEG_TIMEOUT))
            {
                LOG_E(" TIMEOUT !\n");
                phydev->link = 0;
                return -ETIMEDOUT;
            }

            mii_reg = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_BMSR);

            rt_thread_delay(100);
        }
        LOG_D(" done\n");
        phydev->link = 1;
    } else {
        mii_reg = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_BMSR);

        if (mii_reg & RT_BMSR_LSTATUS)
            phydev->link = 1;
        else
            phydev->link = 0;
    }

    return 0;
}

static void __genphy_auto_neg(struct rt_phy_device *phydev,int mii_reg)
{
    rt_uint32_t lpa = 0;
    int gblpa = 0;
    rt_uint32_t estatus = 0;

    if (phydev->supported & (RT_SUPPORTED_1000baseT_Full |
                RT_SUPPORTED_1000baseT_Half))
                {

        gblpa = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_STAT1000);
        if (gblpa < 0)
        {
            LOG_D("Could not read RT_MII_STAT1000. Ignoring gigabit capability\n");
            gblpa = 0;
        }
        gblpa &= rt_phy_read(phydev,
                RT_MDIO_DEVAD_NONE, RT_MII_CTRL1000) << 2;
    }

    phydev->speed = SPEED_10;
    phydev->duplex = DUPLEX_HALF;

    if (gblpa & (RT_PHY_1000BTSR_1000FD | RT_PHY_1000BTSR_1000HD))
    {
        phydev->speed = SPEED_1000;

        if (gblpa & RT_PHY_1000BTSR_1000FD)
            phydev->duplex = DUPLEX_FULL;

        return ;
    }

    lpa = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_ADVERTISE);
    lpa &= rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_LPA);

    if (lpa & (RT_LINK_PARTNER__100FULL | RT_LINK_PARTNER__100HALF))
    {
        phydev->speed = SPEED_100;

        if (lpa & RT_LINK_PARTNER__100FULL)
            phydev->duplex = DUPLEX_FULL;

    } else if (lpa & RT_LINK_PARTNER__10FULL)
    {
        phydev->duplex = DUPLEX_FULL;
    }

    if ((mii_reg & RT_BMSR_ESTATEN) && !(mii_reg & RT_BMSR_ERCAP))
        estatus = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE,
                    RT_MII_ESTATUS);

    if (estatus & (RT_SUPORT_1000B_XFULL | RT_SUPORT_1000B_XHALF |
            RT_SUPORT_1000B_TFULL | RT_SUPORT_1000B_THALF))
            {
        phydev->speed = SPEED_1000;
        if (estatus & (RT_SUPORT_1000B_XFULL | RT_SUPORT_1000B_TFULL))
            phydev->duplex = DUPLEX_FULL;
    }
}
int rt_genphy_parse_link(struct rt_phy_device *phydev)
{
    int mii_reg = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_BMSR);

    if (phydev->autoneg == AUTONEG_ENABLE)
    {
        __genphy_auto_neg(phydev, mii_reg);
    } else {
        rt_uint32_t bmcr = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_BMCR);

        phydev->speed = SPEED_10;
        phydev->duplex = DUPLEX_HALF;

        if (bmcr & RT_BMCR_FULLDPLX)
            phydev->duplex = DUPLEX_FULL;

        if (bmcr & RT_BMCR_SPEED1000)
            phydev->speed = SPEED_1000;
        else if (bmcr & RT_BMCR_SPEED100)
            phydev->speed = SPEED_100;
    }

    return 0;
}

int rt_genphy_config(struct rt_phy_device *phydev)
{
    int val;
    rt_uint32_t features;

    features = (RT_SUPPORTED_TP | RT_SUPPORTED_MII
            | RT_SUPPORTED_AUI | RT_SUPPORTED_FIBRE |
            RT_SUPPORTED_BNC);

    val = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_BMSR);

    if (val < 0)
        return val;

    if (val & RT_BMSR_ANEGCAPABLE)
        features |= RT_SUPPORTED_Autoneg;

    if (val & RT_BMSR_100FULL)
        features |= RT_SUPPORTED_100baseT_Full;
    if (val & RT_BMSR_100HALF)
        features |= RT_SUPPORTED_100baseT_Half;
    if (val & RT_BMSR_10FULL)
        features |= RT_SUPPORTED_10baseT_Full;
    if (val & RT_BMSR_10HALF)
        features |= RT_SUPPORTED_10baseT_Half;

    if (val & RT_BMSR_ESTATEN)
    {
        val = rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_ESTATUS);

        if (val < 0)
            return val;

        if (val & RT_SUPORT_1000B_TFULL)
            features |= RT_SUPPORTED_1000baseT_Full;
        if (val & RT_SUPORT_1000B_THALF)
            features |= RT_SUPPORTED_1000baseT_Half;
        if (val & RT_SUPORT_1000B_XFULL)
            features |= RT_SUPPORTED_1000baseX_Full;
        if (val & RT_SUPORT_1000B_XHALF)
            features |= RT_SUPPORTED_1000baseX_Half;
    }

    phydev->supported &= features;
    phydev->advertising &= features;

    rt_genphy_config_aneg(phydev);

    return 0;
}

int rt_genphy_startup(struct rt_phy_device *phydev)
{
    int ret;

    ret = rt_genphy_update_link(phydev);
    if (ret)
        return ret;

    return rt_genphy_parse_link(phydev);
}
