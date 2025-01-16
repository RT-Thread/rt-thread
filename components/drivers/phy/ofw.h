/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-09-25     zhujiale    the first version
 */
#ifndef __NET_OFW_H__
#define __NET_OFW_H__
#include <rtthread.h>
#include <drivers/ofw.h>
typedef enum
{
    RT_PHY_INTERFACE_MODE_NA,
    RT_PHY_INTERFACE_MODE_INTERNAL,
    RT_PHY_INTERFACE_MODE_MII,
    RT_PHY_INTERFACE_MODE_GMII,
    RT_PHY_INTERFACE_MODE_SGMII,
    RT_PHY_INTERFACE_MODE_TBI,
    RT_PHY_INTERFACE_MODE_REVMII,
    RT_PHY_INTERFACE_MODE_RMII,
    RT_PHY_INTERFACE_MODE_REVRMII,
    RT_PHY_INTERFACE_MODE_RGMII,
    RT_PHY_INTERFACE_MODE_RGMII_ID,
    RT_PHY_INTERFACE_MODE_RGMII_RXID,
    RT_PHY_INTERFACE_MODE_RGMII_TXID,
    RT_PHY_INTERFACE_MODE_RTBI,
    RT_PHY_INTERFACE_MODE_SMII,
    RT_PHY_INTERFACE_MODE_XGMII,
    RT_PHY_INTERFACE_MODE_XLGMII,
    RT_PHY_INTERFACE_MODE_MOCA,
    RT_PHY_INTERFACE_MODE_PSGMII,
    RT_PHY_INTERFACE_MODE_QSGMII,
    RT_PHY_INTERFACE_MODE_TRGMII,
    RT_PHY_INTERFACE_MODE_100BASEX,
    RT_PHY_INTERFACE_MODE_1000BASEX,
    RT_PHY_INTERFACE_MODE_2500BASEX,
    RT_PHY_INTERFACE_MODE_5GBASER,
    RT_PHY_INTERFACE_MODE_RXAUI,
    RT_PHY_INTERFACE_MODE_XAUI,
    /* 10GBASE-R, XFI, SFI - single lane 10G Serdes */
    RT_PHY_INTERFACE_MODE_10GBASER,
    RT_PHY_INTERFACE_MODE_25GBASER,
    RT_PHY_INTERFACE_MODE_USXGMII,
    /* 10GBASE-KR - with Clause 73 AN */
    RT_PHY_INTERFACE_MODE_10GKR,
    RT_PHY_INTERFACE_MODE_QUSGMII,
    RT_PHY_INTERFACE_MODE_1000BASEKX,
    RT_PHY_INTERFACE_MODE_MAX,
} rt_phy_interface;

rt_err_t rt_ofw_get_mac_addr(struct rt_ofw_node *np, rt_uint8_t *addr);
rt_err_t rt_ofw_get_mac_addr_by_name(struct rt_ofw_node *np, const char *name, rt_uint8_t *addr);
rt_err_t rt_ofw_get_interface(struct rt_ofw_node *np, rt_phy_interface *interface);

#endif
