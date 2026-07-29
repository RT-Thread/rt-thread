/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-06-24     ox-horse         first version
 */

#ifndef __DRV_ETH_H__
#define __DRV_ETH_H__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <board.h>
#include "n32h7xx_eth.h"
#include "n32h7xx_rcc.h"
#include "n32h7xx_pwr.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ======================= ETH Instance Selection ======================= */

#if defined(BSP_USING_ETH1)
#define ETH                             ETH1
#define ETH_RCC_ENABLE_AHB_PERIPHEN_CLK RCC_EnableAHB2PeriphClk2
#define ETH_RCC_AHB_PERIPHEN_CLK        RCC_AHB2_PERIPHEN_M7_ETH1CLK
#define ETH_RCC_AHB_PERIPHEN            (RCC_AHB2_PERIPHEN_M7_ETH1MAC | \
                                         RCC_AHB2_PERIPHEN_M7_ETH1TX |  \
                                         RCC_AHB2_PERIPHEN_M7_ETH1RX)
#define ETH_GLOBAL_IRQ                  ETH1_IRQn
#define ETH_PWR_CTRL                    HSC1_ETH1_PWRCTRL
#define ETH_GLOBAL_IRQHANDLER           ETH1_IRQHandler

#elif defined(BSP_USING_ETH2)
#define ETH                             ETH2
#define ETH_RCC_ENABLE_AHB_PERIPHEN_CLK RCC_EnableAHB1PeriphClk2
#define ETH_RCC_AHB_PERIPHEN_CLK        RCC_AHB1_PERIPHEN_M7_ETH2CLK
#define ETH_RCC_AHB_PERIPHEN            (RCC_AHB1_PERIPHEN_M7_ETH2MAC | \
                                         RCC_AHB1_PERIPHEN_M7_ETH2TX |  \
                                         RCC_AHB1_PERIPHEN_M7_ETH2RX)
#define ETH_GLOBAL_IRQ                  ETH2_IRQn
#define ETH_PWR_CTRL                    HSC2_ETH2_PWRCTRL
#define ETH_GLOBAL_IRQHANDLER           ETH2_IRQHandler

#endif /* BSP_USING_ETH1 / BSP_USING_ETH2 */

/* ======================= Media Interface Selection ======================= */

#if defined(ETH_INTERFACE_USING_GMII)
#define ETH_MEDIA_INTERFACE ETH_GMII_MODE
#elif defined(ETH_INTERFACE_USING_MII)
#define ETH_MEDIA_INTERFACE ETH_MII_MODE
#elif defined(ETH_INTERFACE_USING_RMII)
#define ETH_MEDIA_INTERFACE ETH_RMII_MODE
#else
#define ETH_MEDIA_INTERFACE ETH_GMII_MODE
#endif

/* ======================= Standard IEEE 802.3 PHY Registers ======================= */

#define PHY_BASIC_CONTROL_REG     0x00U
#define PHY_BASIC_STATUS_REG      0x01U
#define PHY_ID1_REG               0x02U
#define PHY_ID2_REG               0x03U
#define PHY_AUTONEG_ADVERTISE_REG 0x04U
#define PHY_AUTONEG_LINK_PARTNER  0x05U
#define PHY_GIGABIT_CONTROL_REG   0x09U  /* 1000BASE-T Control Register */
#define PHY_GIGABIT_STATUS_REG    0x0AU  /* 1000BASE-T Status Register */

/* Basic Control Register bits */
#define PHY_RESET_MASK            (1 << 15)
#define PHY_LOOPBACK_MASK         (1 << 14)
#define PHY_AUTO_NEGOTIATION_MASK (1 << 12)
#define PHY_POWER_DOWN_MASK       (1 << 11)
#define PHY_RESTART_AUTONEG_MASK  (1 << 9)
#define PHY_DUPLEX_MODE_MASK      (1 << 8)

/* Basic Status Register bits */
#define PHY_100BASE_T4_MASK        (1 << 15)
#define PHY_100BASE_TX_FD_MASK     (1 << 14)
#define PHY_100BASE_TX_HD_MASK     (1 << 13)
#define PHY_10BASE_T_FD_MASK       (1 << 12)
#define PHY_10BASE_T_HD_MASK       (1 << 11)
#define PHY_1000BASE_T_FD_MASK     (1 << 10)
#define PHY_1000BASE_T_HD_MASK     (1 << 9)
#define PHY_LINKED_STATUS_MASK     (1 << 2)
#define PHY_AUTONEGO_COMPLETE_MASK (1 << 5)

/* ======================= DM9119INP PHY Specific Registers ======================= */

#ifdef PHY_USING_DM9119INP
/* DM9119INP is a Gigabit PHY supporting GMII/MII/RMII */
#define PHY_DM9119INP_ID1 0x006EU
#define PHY_DM9119INP_ID2 0x3212U

/* DM9119INP PHY Specific Status Register (0x11)
 * bit[15:14] = 00 → 10M, 01 → 100M, 10 → 1000M
 * bit[13]    = 1  → Full-Duplex, 0 → Half-Duplex */
#define PHY_SDSR                   0x11U
#define PHY_Status_SPEED_1000M(sr) (((sr) & (1 << 15)) != 0)
#define PHY_Status_SPEED_100M(sr)  (((sr) & (1 << 14)) != 0)
#define PHY_Status_SPEED_10M(sr)   (!PHY_Status_SPEED_1000M(sr) && !PHY_Status_SPEED_100M(sr))
#define PHY_Status_FULL_DUPLEX(sr) (((sr) & (1 << 13)) != 0)

/* DM9119INP PHY Specific Interrupt Registers
 * 0x12 Interrupt Control, 0x13 Interrupt Status */
#define PHY_INTERRUPT_CTRL_REG 0x12U
#define PHY_INTERRUPT_FLAG_REG 0x13U
#define PHY_INTERRUPT_MASK_REG 0x12U
#define PHY_INT_MASK           ((1 << 15) | (1 << 14) | (1 << 13) | (1 << 10))

#endif /* PHY_USING_DM9119INP */

/* ======================= YT8522H PHY Specific Registers ======================= */

#ifdef PHY_USING_YT8522H
/* YT8522H is a Fast Ethernet PHY supporting MII/RMII, up to 100M */
#define PHY_YT8522H_ID1 0x4F51U
#define PHY_YT8522H_ID2 0xE928U

/* YT8522H PHY Specific Status Register (0x11)
 * bit[15:14] = 00 → 10M, 01 → 100M
 * bit[13]    = 1  → Full-Duplex, 0 → Half-Duplex */
#define PHY_SDSR                   0x11U
#define PHY_Status_SPEED_100M(sr)  (((sr) & (1 << 14)) != 0)
#define PHY_Status_SPEED_10M(sr)   (!PHY_Status_SPEED_100M(sr))
#define PHY_Status_FULL_DUPLEX(sr) (((sr) & (1 << 13)) != 0)

/* YT8522H PHY Specific Interrupt Registers
 * 0x12 Interrupt Control, 0x13 Interrupt Status
 * bit15=Auto-Neg Fail, bit14=Speed Change, bit13=Duplex Change,
 * bit11=Link Fail, bit10=Link Success */
#define PHY_INTERRUPT_CTRL_REG 0x12U
#define PHY_INTERRUPT_FLAG_REG 0x13U
#define PHY_INTERRUPT_MASK_REG 0x12U
#define PHY_INT_MASK           ((1 << 15) | (1 << 14) | (1 << 13) | (1 << 11) | (1 << 10))
#endif /* PHY_USING_YT8522H */

/* ======================= RTL8211EG PHY Specific Registers ======================= */

#ifdef PHY_USING_RTL8211EG
/* RTL8211EG is a Gigabit PHY supporting GMII/MII/RMII */
#define PHY_RTL8211EG_ID1 0x001CU
#define PHY_RTL8211EG_ID2 0xC915U

/* RTL8211EG PHY Specific Status Register (0x11)
 * bit[15:14] = 00 → 10M, 01 → 100M, 10 → 1000M
 * bit[13]    = 1  → Full-Duplex, 0 → Half-Duplex
 * No unlock sequence needed — accessible via default register page. */
#define PHY_SDSR                   0x11U
#define PHY_Status_SPEED_1000M(sr) (((sr) & (1 << 15)) != 0)
#define PHY_Status_SPEED_100M(sr)  (((sr) & (1 << 14)) != 0)
#define PHY_Status_SPEED_10M(sr)   (!PHY_Status_SPEED_1000M(sr) && !PHY_Status_SPEED_100M(sr))
#define PHY_Status_FULL_DUPLEX(sr) (((sr) & (1 << 13)) != 0)

/* RTL8211EG Interrupt Registers: 0x12 Control, 0x13 Status
 * bit15=Auto-Neg Error, bit11=Auto-Neg Complete, bit10=Link Change */
#define PHY_INTERRUPT_CTRL_REG 0x12U
#define PHY_INTERRUPT_FLAG_REG 0x13U
#define PHY_INTERRUPT_MASK_REG 0x12U
#define PHY_INT_MASK           ((1 << 15) | (1 << 11) | (1 << 10))
#endif /* PHY_USING_RTL8211EG */

/* ======================= Buffer & Descriptor Configuration ======================= */

#ifndef ETH_TX_DESC_NUMBER
#define ETH_TX_DESC_NUMBER ((uint32_t)4U)
#endif
#ifndef ETH_RX_DESC_NUMBER
#define ETH_RX_DESC_NUMBER ((uint32_t)4U)
#endif

/* ETH_MAX_PACKET_SIZE is defined in n32h7xx_eth.h (1528U) */
#define ETH_TX_BUF_SIZE (ETH_TX_DESC_NUMBER * ETH_MAX_PACKET_SIZE)
#define ETH_RX_BUF_SIZE (ETH_RX_DESC_NUMBER * ETH_MAX_PACKET_SIZE)

/* ======================= PHY Link Status Flags ======================= */

#define PHY_LINK        (1 << 0)
#define PHY_10M         (1 << 1)
#define PHY_100M        (1 << 2)
#define PHY_1000M       (1 << 3)
#define PHY_FULL_DUPLEX (1 << 4)

/* ---- test/monitoring accessors (enabled via DO_ETH_TEST) ---- */
#define DO_ETH_TEST 1
#if DO_ETH_TEST
rt_uint32_t n32_eth_get_speed(void);
rt_uint32_t n32_eth_get_duplex(void);
rt_uint8_t n32_eth_get_phy_addr(void);
void n32_eth_get_mac_addr(rt_uint8_t mac[6]);
const char *n32_eth_get_phy_name(void);
#endif /* DO_ETH_TEST */

#ifdef __cplusplus
}
#endif

#endif /* __DRV_ETH_H__ */
