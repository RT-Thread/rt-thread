/*
 * Copyright (c) 2023-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef DRV_ENET_PHY_H
#define DRV_ENET_PHY_H

#include "hpm_ioc_regs.h"
#include <rtdevice.h>

#if defined(BSP_USING_ENET_PHY_DP83867)
#include "hpm_dp83867.h"
#endif

#if defined(BSP_USING_ENET_PHY_RTL8211)
#include "hpm_rtl8211.h"
#endif

#if defined(BSP_USING_ENET_PHY_DP83848)
#include "hpm_dp83848.h"
#endif

#if defined(BSP_USING_ENET_PHY_RTL8201)
#include "hpm_rtl8201.h"
#endif

#if defined(BSP_USING_ENET_PHY_LAN8720)
#include "hpm_lan8720.h"
#endif

#ifndef PHY_AUTO_NEGO
#define PHY_AUTO_NEGO  (1U)
#endif

#ifndef PHY_MDIO_CSR_CLK_FREQ
#define PHY_MDIO_CSR_CLK_FREQ (200000000U)
#endif

enum phy_link_status
{
   PHY_LINK_DOWN = 0U,
   PHY_LINK_UP
};

typedef struct {
    rt_uint32_t phy_speed;
    rt_uint32_t phy_duplex;
} phy_info_t;

typedef struct {
    rt_uint32_t phy_link;
    rt_phy_t phy;
    phy_info_t phy_info;
} phy_device_t;

#endif /* DRV_ENET_PHY_H */




