/*
 * Copyright (c) 2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef DRV_TSW_PHY_H
#define DRV_TSW_PHY_H

#include "hpm_ioc_regs.h"
#include <rtdevice.h>

#if defined(BSP_USING_TSW_PHY_RTL8211)
#include "hpm_rtl8211.h"
#endif

#ifndef PHY_MDIO_CLK_FREQ
#define PHY_MDIO_CLK_FREQ (2500000U)
#endif

#ifndef PHY_MDIO_CSR_CLK_FREQ
#define PHY_MDIO_CSR_CLK_FREQ (100000000U)
#endif

enum phy_link_status {
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

#endif /* DRV_TSW_PHY_H */




