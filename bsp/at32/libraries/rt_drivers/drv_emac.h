/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 * 2024-09-02     shelton      add support phy lan8720 and yt8512
 */

#ifndef __DRV_EMAC_H__
#define __DRV_EMAC_H__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include "drv_common.h"

#define CRYSTAL_ON_PHY                  0           /* phy does not with crystal */

/* the phy basic control register */
#define PHY_BASIC_CONTROL_REG           0x00U
#define PHY_RESET_MASK                  (1<<15)
#define PHY_AUTO_NEGOTIATION_MASK       (1<<12)

/* the phy basic status register */
#define PHY_BASIC_STATUS_REG            0x01U
#define PHY_LINKED_STATUS_MASK          (1<<2)
#define PHY_AUTONEGO_COMPLETE_MASK      (1<<5)

/* the phy id one register */
#define PHY_ID1_REG                     0x02U
/* the phy id two register */
#define PHY_ID2_REG                     0x03U
/* the phy auto-negotiate advertise register */
#define PHY_AUTONEG_ADVERTISE_REG       0x04U

#if defined (PHY_USING_DM9162)
  #define PHY_CONTROL_REG               (0x00)       /*!< basic mode control register */
  #define PHY_STATUS_REG                (0x01)       /*!< basic mode status register */
  #define PHY_SPECIFIED_CS_REG          (0x11)       /*!< specified configuration and status register */
  /* phy control register */
  #define PHY_AUTO_NEGOTIATION_BIT      (0x1000)     /*!< enable auto negotiation */
  #define PHY_LOOPBACK_BIT              (0x4000)     /*!< enable loopback */
  #define PHY_RESET_BIT                 (0x8000)     /*!< reset phy */
  /* phy status register */
  #define PHY_LINKED_STATUS_BIT         (0x0004)     /*!< link status */
  #define PHY_NEGO_COMPLETE_BIT         (0x0020)     /*!< auto negotiation complete */
  /* phy specified control/status register */
  #define PHY_FULL_DUPLEX_100MBPS_BIT   (0x8000)     /*!< full duplex 100 mbps */
  #define PHY_HALF_DUPLEX_100MBPS_BIT   (0x4000)     /*!< half duplex 100 mbps */
  #define PHY_FULL_DUPLEX_10MBPS_BIT    (0x2000)     /*!< full duplex 10 mbps */
  #define PHY_HALF_DUPLEX_10MBPS_BIT    (0x1000)     /*!< half duplex 10 mbps */
  #define PHY_DUPLEX_MODE               (PHY_FULL_DUPLEX_100MBPS_BIT | PHY_FULL_DUPLEX_10MBPS_BIT)    /*!< full duplex mode */
  #define PHY_SPEED_MODE                (PHY_FULL_DUPLEX_10MBPS_BIT | PHY_HALF_DUPLEX_10MBPS_BIT)     /*!< 10 mbps */
  /*  the phy interrupt source flag register. */
  #define PHY_INTERRUPT_FLAG_REG        0x15U
  /*  the phy interrupt mask register. */
  #define PHY_INTERRUPT_MASK_REG        0x15U
  #define PHY_INT_MASK                  0
#elif defined (PHY_USING_DP83848)
  #define PHY_CONTROL_REG               (0x00)       /*!< basic mode control register */
  #define PHY_STATUS_REG                (0x01)       /*!< basic mode status register */
  #define PHY_SPECIFIED_CS_REG          (0x10)       /*!< phy status register */
  /* phy control register */
  #define PHY_AUTO_NEGOTIATION_BIT      (0x1000)     /*!< enable auto negotiation */
  #define PHY_LOOPBACK_BIT              (0x4000)     /*!< enable loopback */
  #define PHY_RESET_BIT                 (0x8000)     /*!< reset phy */
  /* phy status register */
  #define PHY_LINKED_STATUS_BIT         (0x0004)     /*!< link status */
  #define PHY_NEGO_COMPLETE_BIT         (0x0020)     /*!< auto negotiation complete */

  #define PHY_DUPLEX_MODE               (0x0004)     /*!< full duplex mode */
  #define PHY_SPEED_MODE                (0x0002)     /*!< 10 mbps */

  /*  the phy interrupt source flag register. */
  #define PHY_INTERRUPT_FLAG_REG        0x12U
  #define PHY_LINK_CHANGE_FLAG          (1<<13)
  /*  the phy interrupt control register. */
  #define PHY_INTERRUPT_CTRL_REG        0x11U
  #define PHY_INTERRUPT_EN              ((1<<0)|(1<<1))
  /*  the phy interrupt mask register. */
  #define PHY_INTERRUPT_MASK_REG        0x12U
  #define PHY_INT_MASK                  (1<<5)
#elif defined (PHY_USING_LAN8720)
  #define PHY_CONTROL_REG               (0x00)       /*!< basic mode control register */
  #define PHY_STATUS_REG                (0x01)       /*!< basic mode status register */
  #define PHY_SPECIFIED_CS_REG          (0x1F)       /*!< specified configuration and status register */
  /* phy control register */
  #define PHY_AUTO_NEGOTIATION_BIT      (0x1000)     /*!< enable auto negotiation */
  #define PHY_LOOPBACK_BIT              (0x4000)     /*!< enable loopback */
  #define PHY_RESET_BIT                 (0x8000)     /*!< reset phy */
  /* phy status register */
  #define PHY_LINKED_STATUS_BIT         (0x0004)     /*!< link status */
  #define PHY_NEGO_COMPLETE_BIT         (0x0020)     /*!< auto negotiation complete */
  /* phy specified control/status register */
  #define PHY_FULL_DUPLEX_100MBPS_BIT   (0x0018)     /*!< full duplex 100 mbps */
  #define PHY_HALF_DUPLEX_100MBPS_BIT   (0x0008)     /*!< half duplex 100 mbps */
  #define PHY_FULL_DUPLEX_10MBPS_BIT    (0x0014)     /*!< full duplex 10 mbps */
  #define PHY_HALF_DUPLEX_10MBPS_BIT    (0x0004)     /*!< half duplex 10 mbps */
  #define PHY_DUPLEX_MODE               (0x0100)     /*!< full duplex mode */
  #define PHY_SPEED_MODE                (0x2000)     /*!< 100 mbps */
  /*  the phy interrupt source flag register. */
  #define PHY_INTERRUPT_FLAG_REG        0x1DU
  /*  the phy interrupt mask register. */
  #define PHY_INTERRUPT_MASK_REG        0x1EU
  #define PHY_INT_MASK                  (1<<4)
#elif defined (PHY_USING_YT8512)
  #define PHY_CONTROL_REG               (0x00)       /*!< basic mode control register */
  #define PHY_STATUS_REG                (0x01)       /*!< basic mode status register */
  #define PHY_SPECIFIED_CS_REG          (0x11)       /*!< phy status register */
  /* phy control register */
  #define PHY_AUTO_NEGOTIATION_BIT      (0x1000)     /*!< enable auto negotiation */
  #define PHY_LOOPBACK_BIT              (0x4000)     /*!< enable loopback */
  #define PHY_RESET_BIT                 (0x8000)     /*!< reset phy */
  /* phy status register */
  #define PHY_LINKED_STATUS_BIT         (0x0004)     /*!< link status */
  #define PHY_NEGO_COMPLETE_BIT         (0x0020)     /*!< auto negotiation complete */

  #define PHY_DUPLEX_MODE               (0x2000)     /*!< full duplex mode */
  #define PHY_SPEED_MODE                (0x4000)     /*!< 100 mbps */

  /*  the phy interrupt source flag register. */
  #define PHY_INTERRUPT_FLAG_REG        0x13U
  #define PHY_LINK_CHANGE_FLAG          (3<<10)
  /*  the phy interrupt mask register. */
  #define PHY_INTERRUPT_MASK_REG        0x12U
  #define PHY_INT_MASK                  (3<<10)
#endif

#endif /* __DRV_EMAC_H__ */
