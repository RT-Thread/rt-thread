/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-24     chinesebear  first version
 */
#include "mii.h"

static inline unsigned int mii_nway_result(unsigned int negotiated)
{
    unsigned int ret;

    if (negotiated & LPA_100FULL)
        ret = LPA_100FULL;
    else if (negotiated & LPA_100BASE4)
        ret = LPA_100BASE4;
    else if (negotiated & LPA_100HALF)
        ret = LPA_100HALF;
    else if (negotiated & LPA_10FULL)
        ret = LPA_10FULL;
    else
        ret = LPA_10HALF;

    return ret;
}

static int mii_check_gmii_support(struct mii_if_info *mii)
{
    int reg;

    reg = mii->mdio_read(mii->dev, mii->phy_id, MII_BMSR);
    if (reg & BMSR_ESTATEN)
    {
        reg = mii->mdio_read(mii->dev, mii->phy_id, MII_ESTATUS);
        if (reg & (ESTATUS_1000_TFULL | ESTATUS_1000_THALF))
            return 1;
    }

    return 0;
}

static int mii_ethtool_gset(struct mii_if_info *mii, struct ethtool_cmd *ecmd)
{
    struct synopGMACNetworkAdapter *dev = mii->dev;
    u32 advert, bmcr, lpa, nego;
    u32 advert2 = 0, bmcr2 = 0, lpa2 = 0;

    ecmd->supported =
        (SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
         SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
         SUPPORTED_Autoneg | SUPPORTED_TP | SUPPORTED_MII);
    if (mii->supports_gmii)
        ecmd->supported |= SUPPORTED_1000baseT_Half |
                           SUPPORTED_1000baseT_Full;

    /* only supports twisted-pair */
    ecmd->port = PORT_MII;

    /* only supports internal transceiver */
    ecmd->transceiver = XCVR_INTERNAL;

    /* this isn't fully supported at higher layers */
    ecmd->phy_address = mii->phy_id;

    ecmd->advertising = ADVERTISED_TP | ADVERTISED_MII;
    advert = mii->mdio_read(dev, mii->phy_id, MII_ADVERTISE);
    if (mii->supports_gmii)
        advert2 = mii->mdio_read(dev, mii->phy_id, MII_CTRL1000);

    if (advert & ADVERTISE_10HALF)
        ecmd->advertising |= ADVERTISED_10baseT_Half;
    if (advert & ADVERTISE_10FULL)
        ecmd->advertising |= ADVERTISED_10baseT_Full;
    if (advert & ADVERTISE_100HALF)
        ecmd->advertising |= ADVERTISED_100baseT_Half;
    if (advert & ADVERTISE_100FULL)
        ecmd->advertising |= ADVERTISED_100baseT_Full;
    if (advert2 & ADVERTISE_1000HALF)
        ecmd->advertising |= ADVERTISED_1000baseT_Half;
    if (advert2 & ADVERTISE_1000FULL)
        ecmd->advertising |= ADVERTISED_1000baseT_Full;

    bmcr = mii->mdio_read(dev, mii->phy_id, MII_BMCR);
    lpa = mii->mdio_read(dev, mii->phy_id, MII_LPA);
    if (mii->supports_gmii)
    {
        bmcr2 = mii->mdio_read(dev, mii->phy_id, MII_CTRL1000);
        lpa2 = mii->mdio_read(dev, mii->phy_id, MII_STAT1000);
    }
    if (bmcr & BMCR_ANENABLE)
    {
        ecmd->advertising |= ADVERTISED_Autoneg;
        ecmd->autoneg = AUTONEG_ENABLE;

        nego = mii_nway_result(advert & lpa);
        if ((bmcr2 & (ADVERTISE_1000HALF | ADVERTISE_1000FULL)) &
                (lpa2 >> 2))
            ecmd->speed = SPEED_1000;
        else if (nego == LPA_100FULL || nego == LPA_100HALF)
            ecmd->speed = SPEED_100;
        else
            ecmd->speed = SPEED_10;
        if ((lpa2 & LPA_1000FULL) || nego == LPA_100FULL ||
                nego == LPA_10FULL)
        {
            ecmd->duplex = DUPLEX_FULL;
            mii->full_duplex = 1;
        }
        else
        {
            ecmd->duplex = DUPLEX_HALF;
            mii->full_duplex = 0;
        }
    }
    else
    {
        ecmd->autoneg = AUTONEG_DISABLE;

        ecmd->speed = ((bmcr & BMCR_SPEED1000 &&
                        (bmcr & BMCR_SPEED100) == 0) ? SPEED_1000 :
                       (bmcr & BMCR_SPEED100) ? SPEED_100 : SPEED_10);
        ecmd->duplex = (bmcr & BMCR_FULLDPLX) ? DUPLEX_FULL : DUPLEX_HALF;
    }

    /* ignore maxtxpkt, maxrxpkt for now */

    return 0;
}

static int mii_link_ok(struct mii_if_info *mii)
{
    /* first, a dummy read, needed to latch some MII phys */
    mii->mdio_read(mii->dev, mii->phy_id, MII_BMSR);
    if (mii->mdio_read(mii->dev, mii->phy_id, MII_BMSR) & BMSR_LSTATUS)
        return 1;
    return 0;
}
