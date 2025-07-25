/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-09-23     LZerro       first version
 */

#ifndef __DRV_ETH_H__
#define __DRV_ETH_H__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <board.h>
#include "eth_config.h"

/* The PHY basic control register */
#define PHY_BASIC_CONTROL_REG       0x00U
#define PHY_RESET_MASK              (1<<15)
#define PHY_AUTO_NEGOTIATION_MASK   (1<<12)

/* The PHY basic status register */
#define PHY_BASIC_STATUS_REG        0x01U
#define PHY_LINKED_STATUS_MASK      (1<<2)
#define PHY_AUTONEGO_COMPLETE_MASK  (1<<5)

/* The PHY ID one register */
#define PHY_ID1_REG                 0x02U
/* The PHY ID two register */
#define PHY_ID2_REG                 0x03U
/* The PHY auto-negotiate advertise register */
#define PHY_AUTONEG_ADVERTISE_REG   0x04U

/** PHY duplex mode */
typedef enum
{
    CY_ECM_DUPLEX_HALF,    /**< Half duplex */
    CY_ECM_DUPLEX_FULL,    /**< Full duplex */
    CY_ECM_DUPLEX_AUTO     /**< Both half/full duplex */
} cy_ecm_duplex_t;

/** PHY speed */
typedef enum
{
    CY_ECM_PHY_SPEED_10M,   /**< 10 Mbps */
    CY_ECM_PHY_SPEED_100M,  /**< 100 Mbps */
    CY_ECM_PHY_SPEED_1000M, /**< 1000 Mbps */
    CY_ECM_PHY_SPEED_AUTO   /**< All 10/100/1000 Mbps */
} cy_ecm_phy_speed_t;

/** Standard interface type */
typedef enum
{
    CY_ECM_SPEED_TYPE_MII,   /**< Media-Independent Interface (MII) */
    CY_ECM_SPEED_TYPE_GMII,  /**< Gigabit Media-Independent Interface (GMII) */
    CY_ECM_SPEED_TYPE_RGMII, /**< Reduced Gigabit Media-Independent Interface (RGMII) */
    CY_ECM_SPEED_TYPE_RMII   /**< Reduced Media-Independent Interface (RMII) */
} cy_ecm_speed_type_t;

typedef struct
{
    cy_ecm_speed_type_t interface_speed_type; /**< Standard interface to be used for data transfer  */
    cy_ecm_phy_speed_t phy_speed;             /**< Physical transfer speed */
    cy_ecm_duplex_t mode;                     /**< Transfer mode */
} cy_ecm_phy_config_t;

extern int eth_index_internal;


#define ETH_INTERFACE_TYPE ETH1

 /* After hardware initialization, max wait time to get the physical link up */
#define MAX_WAIT_ETHERNET_PHY_STATUS          (10000)

#define REGISTER_ADDRESS_PHY_REG_BMCR       PHYREG_00_BMCR          /* BMCR register (0x0000) to read the speed and duplex mode */
#define REGISTER_PHY_REG_DUPLEX_MASK        PHYBMCR_FULL_DUPLEX_Msk /* Bit 8 of BMCR register to read the duplex mode */
#define REGISTER_PHY_REG_SPEED_MASK         (0x2040)                /* Bit 6, 13: BMCR register to read the speed */
#define REGISTER_PHY_REG_SPEED_MASK_10M     (0x0000)                /* Bit 6, 13: Both are set to 0 for 10M speed */
#define REGISTER_PHY_REG_SPEED_MASK_100M    (0x2000)                /* Bit 6, 13: Set to 0 and 1 respectively for 100M speed */
#define REGISTER_PHY_REG_SPEED_MASK_1000M   (0x0040)                /* Bit 6, 13: Set to 1 and 0 respectively for 1000M speed */

#endif /* __DRV_ETH_H__ */







