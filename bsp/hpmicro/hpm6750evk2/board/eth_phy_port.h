/*
 * Copyright (c) 2023 hpmicro
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

#ifdef BSP_USING_ETH0

    #define RGMII  (1U)

    /* RTL8211 name and ID */
    #define PHY_NAME                    ("RTL8211")
    #define PHY_ID1                     (0x001CU)
    #define PHY_ID2                     (0x32U)

    /* PHY_RTL8211 basic control register */
    #define PHY_BASIC_CONTROL_REG       (0x00U)
    #define PHY_RESET_MASK              (1U << 15)
    #define PHY_AUTO_NEGOTIATION_MASK   (1U << 12)

    /* PHY_RTL8211 basic status register */
    #define PHY_BASIC_STATUS_REG        (0x01U)
    #define PHY_LINKED_STATUS_MASK      (1U << 2)
    #define PHY_AUTONEGO_COMPLETE_MASK  (1U << 5)

    /* PHY_RTL8211 ID one register */
    #define PHY_ID1_REG                 (0x02U)

    /* PHY_RTL8211 ID two register */
    #define PHY_ID2_REG                 (0x03U)

    /* PHY_RTL8211 auto-negotiate advertise register */
    #define PHY_AUTONEG_ADVERTISE_REG   (0x04U)

    /* PHY_RTL8211 status register */
    #define PHY_STATUS_REG              (0x11U)
    #define PHY_100M_MASK               (1UL << 14)
    #define PHY_1000M_MASK              (1UL << 15)
    #define PHY_FULL_DUPLEX_MASK        (1UL << 13)
    #define PHY_STATUS_SPEED_100M(SR)   ((SR) & PHY_100M_MASK)
    #define PHY_STATUS_SPEED_1000M(SR)  ((SR) & PHY_1000M_MASK)
    #define PHY_STATUS_FULL_DUPLEX(SR)  ((SR) & PHY_FULL_DUPLEX_MASK)
    #define PHY_SPEED_SEL_SHIFT         (14U)
    /* PHY_RTL8211 interrupt control register */
    #define PHY_INTERTUPT_CTRL_REG      (0x12U)

    /* PHY_RTL8211 interrupt status register */
    #define PHY_INTERRUPT_STATUS_REG    (0x13U)

    /* PHY register index */
    typedef enum {
        PHY_BASIC_CONTROL_REG_IDX = 0,
        PHY_BASIC_STATUS_REG_IDX,
        PHY_ID1_REG_IDX,
        PHY_ID2_REG_IDX,
        PHY_AUTONEG_ADVERTISE_REG_IDX,
        PHY_STATUS_REG_IDX,
        PHY_INTERRUPT_FLAG_REG_IDX,
        PHY_INTERRUPT_MASK_REG_IDX
    } phy_reg_idx_t;

    /* ETH0 PHY register list */
    #define PHY0_REG_LIST  PHY_BASIC_CONTROL_REG,\
                           PHY_BASIC_STATUS_REG,\
                           PHY_ID1_REG,\
                           PHY_ID2_REG,\
                           PHY_AUTONEG_ADVERTISE_REG,\
                           PHY_STATUS_REG,\
                           PHY_INTERTUPT_CTRL_REG,\
                           PHY_INTERRUPT_STATUS_REG

#else
    #include "hpm_rtl8201.h"

    #define RMII  (1U)

    /* RTL8201 name and ID */
    #define PHY_NAME                    ("RTL8201")
    #define PHY_ID1                     (0x001CU)
    #define PHY_ID2                     (0x32U)

    /* RTL8201 basic control register */
    #define PHY_BASIC_CONTROL_REG       (0x00U)
    #define PHY_RESET_MASK              (1U << 15)
    #define PHY_AUTO_NEGOTIATION_MASK   (1U << 12)

    /* RTL8201 basic status register */
    #define PHY_BASIC_STATUS_REG        (0x01U)
    #define PHY_LINKED_STATUS_MASK      (1U << 2)
    #define PHY_AUTONEGO_COMPLETE_MASK  (1U << 5)

    /* RTL8201 ID one register */
    #define PHY_ID1_REG                 (0x02U)

    /* RTL8201 ID two register */
    #define PHY_ID2_REG                 (0x03U)

    /* RTL8201 auto-negotiate advertise register */
    #define PHY_AUTONEG_ADVERTISE_REG   (0x04U)

    /* RTL8201 status register */
    #define PHY_STATUS_REG              (0x00U)
    #define PHY_100M_MASK               (1UL << 13)
    #define PHY_FULL_DUPLEX_MASK        (1UL << 8)
    #define PHY_STATUS_SPEED_100M(SR)   ((SR) & PHY_100M_MASK)
    #define PHY_STATUS_FULL_DUPLEX(SR)  ((SR) & PHY_FULL_DUPLEX_MASK)

    /* RTL8201 mode setting register */
    #define PHY_RMSR_P7                     (0x10)
    #define PHY_RMSR_P7_RG_RMII_CLKDIR_MASK (0x1000U)

    /* RTL8201 page select register */
    #define PHY_PAGESEL                     (0x1f)

    /* PHY register index */
    typedef enum {
        PHY_BASIC_CONTROL_REG_IDX = 0,
        PHY_BASIC_STATUS_REG_IDX,
        PHY_ID1_REG_IDX,
        PHY_ID2_REG_IDX,
        PHY_AUTONEG_ADVERTISE_REG_IDX,
        PHY_STATUS_REG_IDX,
        PHY_RMSR_P7_IDX,
        PHY_PAGE_SEL_IDX
    } phy_reg_idx_t;

    /* ETH0 PHY register list */
    #define PHY1_REG_LIST  PHY_BASIC_CONTROL_REG,\
                           PHY_BASIC_STATUS_REG,\
                           PHY_ID1_REG,\
                           PHY_ID2_REG,\
                           PHY_AUTONEG_ADVERTISE_REG,\
                           PHY_STATUS_REG,\
                           PHY_RMSR_P7_IDX,\
                           PHY_PAGE_SEL_IDX

#endif
#endif
