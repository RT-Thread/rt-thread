/*
 * Copyright (c) 2021 HPMicro
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

/** @note PHY: LAN8720A */

#define PHY_NAME    ("LAN8720A")
#define PHY_ID1     (7U)

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

/* The PHY SPECIAL MODES REGISTER */
#define PHY_SPECIAL_MODES_REG       (0x12U)

/*  The PHY interrupt source flag register. */
#define PHY_INTERRUPT_FLAG_REG      (0x1dU)

/*  The PHY interrupt mask register. */
#define PHY_INTERRUPT_MASK_REG      (0x1eU)
#define PHY_LINK_DOWN_MASK          (1 << 4)
#define PHY_AUTO_NEGO_COMPLETE_MASK (1 << 6)

/*  The PHY status register. */
#define PHY_STATUS_REG              (0x1fU)
#define PHY_10M_MASK                (1 << 2)
#define PHY_100M_MASK               (1 << 3)
#define PHY_FULL_DUPLEX_MASK        (1 << 4)
#define PHY_STATUS_SPEED_10M(SR)    ((SR) & PHY_10M_MASK)
#define PHY_STATUS_SPEED_100M(SR)   ((SR) & PHY_100M_MASK)
#define PHY_STATUS_FULL_DUPLEX(SR)  ((SR) & PHY_FULL_DUPLEX_MASK)

/* PHY0 register list */
#define PHY0_REG_LIST  PHY_BASIC_CONTROL_REG,\
                       PHY_BASIC_STATUS_REG,\
                       PHY_ID1_REG,\
                       PHY_ID2_REG,\
                       PHY_SPECIAL_MODES_REG,\
                       PHY_INTERRUPT_FLAG_REG,\
                       PHY_INTERRUPT_MASK_REG,\
                       PHY_STATUS_REG

/* PHY0 register index */
#define PHY0_BASIC_STATUS_REG_IDX (1U)
#define PHY0_ID1_REG_IDX          (2U)
#define PHY0_STATUS_REG_IDX       (7U)

/* PHY1 register list */
#define PHY1_REG_LIST  PHY_BASIC_CONTROL_REG,\
                       PHY_BASIC_STATUS_REG,\
                       PHY_ID1_REG,\
                       PHY_ID2_REG,\
                       PHY_SPECIAL_MODES_REG,\
                       PHY_INTERRUPT_FLAG_REG,\
                       PHY_INTERRUPT_MASK_REG,\
                       PHY_STATUS_REG

/* PHY1 register index */
#define PHY_BASIC_STATUS_REG_IDX (1U)
#define PHY_ID1_REG_IDX          (2U)
#define PHY_STATUS_REG_IDX       (7U)

#endif
