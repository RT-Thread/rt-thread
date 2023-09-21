/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef ETH_PHY_PORT_H
#define ETH_PHY_PORT_H

#include "hpm_ioc_regs.h"
#include <rtdevice.h>

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

/** @note PHY: RTL8201 */

#define PHY_NAME    ("RTL8201")
#define PHY_ID1     (0x1CU)

/* The PHY basic control register */
#define PHY_BASIC_CONTROL_REG       (0x00U)
#define PHY_RESET_MASK              (1U << 15)
#define PHY_AUTO_NEGOTIATION_MASK   (1U << 12)

/* The PHY basic status register */
#define PHY_BASIC_STATUS_REG        (0x01U)
#define PHY_LINKED_STATUS_MASK      (1U << 2)
#define PHY_AUTONEGO_COMPLETE_MASK  (1U << 5)

/* The PHY ID one register */
#define PHY_ID1_REG                 (0x02U)

/* The PHY ID two register */
#define PHY_ID2_REG                 (0x03U)

/* The PHY auto-negotiate advertise register */
#define PHY_AUTONEG_ADVERTISE_REG   (0x04U)

/*  The PHY status register. */
#define PHY_STATUS_REG              (0x00U)
#define PHY_10M_MASK                (1 << 13)
#define PHY_100M_MASK               (1 << 13)
#define PHY_FULL_DUPLEX_MASK        (1 << 8)
#define PHY_STATUS_SPEED_10M(SR)    ((SR) & PHY_100M_MASK) ? 0: 1
#define PHY_STATUS_SPEED_100M(SR)   ((SR) & PHY_100M_MASK)
#define PHY_STATUS_FULL_DUPLEX(SR)  ((SR) & PHY_FULL_DUPLEX_MASK)

/* PHY0 register list */
#define PHY0_REG_LIST  PHY_BASIC_CONTROL_REG,\
                       PHY_BASIC_STATUS_REG,\
                       PHY_ID1_REG,\
                       PHY_ID2_REG,\
                       PHY_AUTONEG_ADVERTISE_REG,\
                       PHY_STATUS_REG

/* PHY0 register index */
#define PHY_BASIC_STATUS_REG_IDX (1U)
#define PHY_ID1_REG_IDX          (2U)
#define PHY_STATUS_REG_IDX       (5U)

#endif
