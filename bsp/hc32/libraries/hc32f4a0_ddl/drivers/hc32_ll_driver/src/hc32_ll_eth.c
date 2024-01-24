/**
 *******************************************************************************
 * @file  hc32_ll_eth.c
 * @brief This file provides firmware functions to manage the Ethernet MAC
 *        Controller(ETH).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-09-30       CDT             Optimize ETH start and stop timing
                                    Modify the process of obtaining PHY status
                                    Modify the process of auto-negotiation disable
                                    Modify ETH_PTP_UpdateBasicAddend function
                                    Modify typo
                                    Modify the clock division of SMIC
                                    Modify operation sequence of ETH_DeInit function
                                    Add ETH_MAC_SetInterface function
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_eth.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_ETH ETH
 * @brief Initial Configuration Driver Library
 * @{
 */

#if (LL_ETH_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ETH_Local_Macros ETH Local Macros
 * @{
 */

/* Ethernet register Mask */
#define ETH_MAC_IFCONFR_CLR_MASK                    (ETH_MAC_IFCONFR_RCKINV | ETH_MAC_IFCONFR_TCKINV)
#define ETH_MAC_CONFIGR_CLR_MASK                    (0x72CF7EF0UL)
#define ETH_MAC_FLOCTLR_CLR_MASK                    (0xFFFF00BEUL)
#define ETH_MAC_FLTCTLR_CLR_MASK                    (0x802107FFUL)
#define ETH_MAC_SMIADDR_CLR_MASK                    (0x0000FFC3UL)
#define ETH_DMA_BUSMODR_CLR_MASK                    (0x0FFFFFFEUL)
#define ETH_DMA_OPRMODR_CLR_MASK                    (0x0721C0FCUL)
#define ETH_PTP_TSPCTLR_CLR_MASK                    (0x0007FF02UL)

/* Ethernet MAC Address byte length */
#define ETH_MAC_ADDR_BYTE_LEN                       (6U)
/* Ethernet DMA Tx descriptors Collision Count Shift */
#define ETH_DMA_TXDESC_COLLISION_CNT_SHIFT          (3UL)
/* Ethernet DMA Rx descriptors Frame Length Shift */
#define ETH_DMA_RXDESC_FRAME_LEN_SHIFT              (16UL)
/* Ethernet DMA Tx/Rx descriptors Buffer2 Size Shift */
#define ETH_DMA_DESC_BUF2_SIZE_SHIFT                (16UL)
/* Ethernet Remote Wake-up frame register length */
#define ETH_WAKEUP_REG_LEN                          (8U)
/* Ethernet PTP PPS channel 1 time register address Shift */
#define ETH_PTP_PPS1_TIME_REG_ADDR_SHIFT            (0x64U)

/* Wait timeout(ms) */
#define ETH_WR_REG_TIMEOUT                          (50UL)
#define ETH_SW_RST_TIMEOUT                          (200UL)
#define ETH_LINK_STATUS_TIMEOUT                     (3000UL)
#define ETH_AUTO_NEGO_CPLT_TIMEOUT                  (3000UL)

/** Get the specified register address */
#define ETH_MAC_MACADHR_ADDR(__SHIFT__)             (__IO uint32_t *)((uint32_t)(&(CM_ETH->MAC_MACADHR0)) + \
                                                                      (uint32_t)(__SHIFT__))
#define ETH_MAC_MACADLR_ADDR(__SHIFT__)             (__IO uint32_t *)((uint32_t)(&(CM_ETH->MAC_MACADLR0)) + \
                                                                      (uint32_t)(__SHIFT__))
#define ETH_PTP_TMTSECR_ADDR(__SHIFT__)             (__IO uint32_t *)((uint32_t)(&(CM_ETH->PTP_TMTSECR0)) + \
                                                                      (uint32_t)(__SHIFT__))
#define ETH_PTP_TMTNSER_ADDR(__SHIFT__)             (__IO uint32_t *)((uint32_t)(&(CM_ETH->PTP_TMTNSER0)) + \
                                                                      (uint32_t)(__SHIFT__))

/**
 * @defgroup ETH_Check_Parameters_Validity ETH Check Parameters Validity
 * @{
 */
#define IS_ETH_PHY_ADDR(x)                                  ((x) < 0x20U)
#define IS_ETH_PHY_REG(x)                                   ((x) < 0x20U)

#define IS_ETH_AUTO_NEGO(x)                                                    \
(   ((x) == ETH_AUTO_NEGO_DISABLE)                          ||                 \
    ((x) == ETH_AUTO_NEGO_ENABLE))

#define IS_ETH_MAC_IF(x)                                                       \
(   ((x) == ETH_MAC_IF_MII)                                 ||                 \
    ((x) == ETH_MAC_IF_RMII))

#define IS_ETH_MAC_SPEED(x)                                                    \
(   ((x) == ETH_MAC_SPEED_10M)                              ||                 \
    ((x) == ETH_MAC_SPEED_100M))

#define IS_ETH_MAC_DUPLEX_MD(x)                                                \
(   ((x) == ETH_MAC_DUPLEX_MD_HALF)                         ||                 \
    ((x) == ETH_MAC_DUPLEX_MD_FULL))

#define IS_ETH_MAC_CHECKSUM_MD(x)                                              \
(   ((x) == ETH_MAC_CHECKSUM_MD_SW)                         ||                 \
    ((x) == ETH_MAC_CHECKSUM_MD_HW))

#define IS_ETH_RX_MD(x)                                                        \
(   ((x) == ETH_RX_MD_POLLING)                              ||                 \
    ((x) == ETH_RX_MD_INT))

#define IS_ETH_MAC_TX_CLK_POLARITY(x)                                          \
(   ((x) == ETH_MAC_TX_CLK_POLARITY_KEEP)                   ||                 \
    ((x) == ETH_MAC_TX_CLK_POLARITY_INVERSE))

#define IS_ETH_MAC_RX_CLK_POLARITY(x)                                          \
(   ((x) == ETH_MAC_RX_CLK_POLARITY_KEEP)                   ||                 \
    ((x) == ETH_MAC_RX_CLK_POLARITY_INVERSE))

#define IS_ETH_MAC_SRC_ADDR_MD(x)                                              \
(   ((x) == ETH_MAC_SRC_ADDR_MD_BY_DMA_TXDESC)              ||                 \
    ((x) == ETH_MAC_SRC_ADDR_MD_INSERT_MACADDR0)            ||                 \
    ((x) == ETH_MAC_SRC_ADDR_MD_REPLACE_MACADDR0)           ||                 \
    ((x) == ETH_MAC_SRC_ADDR_MD_INSERT_MACADDR1)            ||                 \
    ((x) == ETH_MAC_SRC_ADDR_MD_REPLACE_MACADDR1))

#define IS_ETH_MAC_TYPE_FRAME_STRIP_FCS(x)                                     \
(   ((x) == ETH_MAC_TYPE_FRAME_STRIP_FCS_DISABLE)           ||                 \
    ((x) == ETH_MAC_TYPE_FRAME_STRIP_FCS_ENABLE))

#define IS_ETH_MAC_WATCHDOG(x)                                                 \
(   ((x) == ETH_MAC_WATCHDOG_DISABLE)                       ||                 \
    ((x) == ETH_MAC_WATCHDOG_ENABLE))

#define IS_ETH_MAC_JABBER(x)                                                   \
(   ((x) == ETH_MAC_JABBER_DISABLE)                         ||                 \
    ((x) == ETH_MAC_JABBER_ENABLE))

#define IS_ETH_MAC_INTERFRAME_GAP(x)                                           \
(   ((x) == ETH_MAC_INTERFRAME_GAP_96BIT)                   ||                 \
    ((x) == ETH_MAC_INTERFRAME_GAP_88BIT)                   ||                 \
    ((x) == ETH_MAC_INTERFRAME_GAP_80BIT)                   ||                 \
    ((x) == ETH_MAC_INTERFRAME_GAP_72BIT)                   ||                 \
    ((x) == ETH_MAC_INTERFRAME_GAP_64BIT)                   ||                 \
    ((x) == ETH_MAC_INTERFRAME_GAP_56BIT)                   ||                 \
    ((x) == ETH_MAC_INTERFRAME_GAP_48BIT)                   ||                 \
    ((x) == ETH_MAC_INTERFRAME_GAP_40BIT))

#define IS_ETH_MAC_CARRIER_SENSE(x)                                            \
(   ((x) == ETH_MAC_CARRIER_SENSE_DISABLE)                  ||                 \
    ((x) == ETH_MAC_CARRIER_SENSE_ENABLE))

#define IS_ETH_MAC_RX_OWN(x)                                                   \
(   ((x) == ETH_MAC_RX_OWN_DISABLE)                         ||                 \
    ((x) == ETH_MAC_RX_OWN_ENABLE))

#define IS_ETH_MAC_CHECKSUM_OFFLOAD(x)                                         \
(   ((x) == ETH_MAC_CHECKSUM_OFFLOAD_DISABLE)               ||                 \
    ((x) == ETH_MAC_CHECKSUM_OFFLOAD_ENABLE))

#define IS_ETH_MAC_RETRY_TRANS(x)                                              \
(   ((x) == ETH_MAC_RETRY_TRANS_DISABLE)                    ||                 \
    ((x) == ETH_MAC_RETRY_TRANS_ENABLE))

#define IS_ETH_MAC_AUTO_STRIP_PAD_FCS(x)                                       \
(   ((x) == ETH_MAC_AUTO_STRIP_PAD_FCS_DISABLE)             ||                 \
    ((x) == ETH_MAC_AUTO_STRIP_PAD_FCS_ENABLE))

#define IS_ETH_MAC_BACKOFF_LIMIT(x)                                            \
(   ((x) == ETH_MAC_BACKOFF_LIMIT10)                        ||                 \
    ((x) == ETH_MAC_BACKOFF_LIMIT8)                         ||                 \
    ((x) == ETH_MAC_BACKOFF_LIMIT4)                         ||                 \
    ((x) == ETH_MAC_BACKOFF_LIMIT1))

#define IS_ETH_MAC_DEFERRAL_CHECK(x)                                           \
(   ((x) == ETH_MAC_DEFERRAL_CHECK_DISABLE)                 ||                 \
    ((x) == ETH_MAC_DEFERRAL_CHECK_ENABLE))

#define IS_ETH_MAC_ZERO_QUANTA_PAUSE(x)                                        \
(   ((x) == ETH_MAC_ZERO_QUANTA_PAUSE_DISABLE)              ||                 \
    ((x) == ETH_MAC_ZERO_QUANTA_PAUSE_ENABLE))

#define IS_ETH_MAC_PAUSE_LOW_THRESHOLD(x)                                      \
(   ((x) == ETH_MAC_PAUSE_LOW_THRESHOLD_MINUS4)             ||                 \
    ((x) == ETH_MAC_PAUSE_LOW_THRESHOLD_MINUS28)            ||                 \
    ((x) == ETH_MAC_PAUSE_LOW_THRESHOLD_MINUS144)           ||                 \
    ((x) == ETH_MAC_PAUSE_LOW_THRESHOLD_MINUS256))

#define IS_ETH_MAC_UNICAST_PAUSE_FRAME_DETECT(x)                               \
(   ((x) == ETH_MAC_UNICAST_PAUSE_FRAME_DETECT_DISABLE)     ||                 \
    ((x) == ETH_MAC_UNICAST_PAUSE_FRAME_DETECT_ENABLE))

#define IS_ETH_MAC_RX_FLOW_CTRL(x)                                             \
(   ((x) == ETH_MAC_RX_FLOW_CTRL_DISABLE)                   ||                 \
    ((x) == ETH_MAC_RX_FLOW_CTRL_ENABLE))

#define IS_ETH_MAC_TRANS_FLOW_CTRL(x)                                          \
(   ((x) == ETH_MAC_TRANS_FLOW_CTRL_DISABLE)                ||                 \
    ((x) == ETH_MAC_TRANS_FLOW_CTRL_ENABLE))

#define IS_ETH_MAC_RX_ALL(x)                                                   \
(   ((x) == ETH_MAC_RX_ALL_DISABLE)                         ||                 \
    ((x) == ETH_MAC_RX_ALL_ENABLE))

#define IS_ETH_MAC_DROP_NOT_TCPUDP(x)                                          \
(   ((x) == ETH_MAC_DROP_NOT_TCPUDP_DISABLE)                ||                 \
    ((x) == ETH_MAC_DROP_NOT_TCPUDP_ENABLE))

#define IS_ETH_MAC_VLAN_TAG_FILTER(x)                                          \
(   ((x) == ETH_MAC_VLAN_TAG_FILTER_DISABLE)                ||                 \
    ((x) == ETH_MAC_VLAN_TAG_FILTER_ENABLE))

#define IS_ETH_MAC_SRC_ADDR_FILTER(x)                                          \
(   ((x) == ETH_MAC_SRC_ADDR_FILTER_DISABLE)                ||                 \
    ((x) == ETH_MAC_SRC_ADDR_FILTER_NORMAL)                 ||                 \
    ((x) == ETH_MAC_SRC_ADDR_FILTER_INVERSE))

#define IS_ETH_MAC_PASS_CTRL_FRAME(x)                                          \
(   ((x) == ETH_MAC_PASS_CTRL_FRAME_BLOCK_ALL)              ||                 \
    ((x) == ETH_MAC_PASS_CTRL_FRAME_FORWARD_NOT_PAUSE)      ||                 \
    ((x) == ETH_MAC_PASS_CTRL_FRAME_FORWARD_ALL)            ||                 \
    ((x) == ETH_MAC_PASS_CTRL_FRAME_FORWARD_PASS_FILTER))

#define IS_ETH_MAC_BROADCAST_FRAME(x)                                          \
(   ((x) == ETH_MAC_RX_BROADCAST_FRAME_DISABLE)             ||                 \
    ((x) == ETH_MAC_RX_BROADCAST_FRAME_ENABLE))

#define IS_ETH_MAC_DEST_ADDR_FILTER(x)                                         \
(   ((x) == ETH_MAC_DEST_ADDR_FILTER_NORMAL)                ||                 \
    ((x) == ETH_MAC_DEST_ADDR_FILTER_INVERSE))

#define IS_ETH_MAC_MULTICAST_FRAME_FILTER(x)                                   \
(   ((x) == ETH_MAC_MULTICAST_FRAME_FILTER_NONE)            ||                 \
    ((x) == ETH_MAC_MULTICAST_FRAME_FILTER_PERFECT)         ||                 \
    ((x) == ETH_MAC_MULTICAST_FRAME_FILTER_HASHTABLE)       ||                 \
    ((x) == ETH_MAC_MULTICAST_FRAME_FILTER_PERFECT_HASHTABLE))

#define IS_ETH_MAC_UNICAST_FRAME_FILTER(x)                                     \
(   ((x) == ETH_MAC_UNICAST_FRAME_FILTER_PERFECT)           ||                 \
    ((x) == ETH_MAC_UNICAST_FRAME_FILTER_HASHTABLE)         ||                 \
    ((x) == ETH_MAC_UNICAST_FRAME_FILTER_PERFECT_HASHTABLE))

#define IS_ETH_MAC_PROMISCUOUS_MD(x)                                           \
(   ((x) == ETH_MAC_PROMISCUOUS_MD_DISABLE)                 ||                 \
    ((x) == ETH_MAC_PROMISCUOUS_MD_ENABLE))

#define IS_ETH_MAC_TXVLAN_MD(x)                                                \
(   ((x) == ETH_MAC_TXVLAN_MD_BY_DMA_TXDESC)                ||                 \
    ((x) == ETH_MAC_TXVLAN_MD_BYPASS)                       ||                 \
    ((x) == ETH_MAC_TXVLAN_MD_REMOVE_TAG)                   ||                 \
    ((x) == ETH_MAC_TXVLAN_MD_INSERT_TAG)                   ||                 \
    ((x) == ETH_MAC_TXVLAN_MD_REPLACE_TAG))

#define IS_ETH_MAC_RXVLAN_FILTER(x)                                            \
(   ((x) == ETH_MAC_RXVLAN_FILTER_NORMAL)                   ||                 \
    ((x) == ETH_MAC_RXVLAN_FILTER_INVERSE)                  ||                 \
    ((x) == ETH_MAC_RXVLAN_FILTER_NORMAL_HASHTABLE)         ||                 \
    ((x) == ETH_MAC_RXVLAN_FILTER_INVERSE_HASHTABLE))

#define IS_ETH_MAC_RXVLAN_CMP(x)                                               \
(   ((x) == ETH_MAC_RXVLAN_CMP_16BIT)                       ||                 \
    ((x) == ETH_MAC_RXVLAN_CMP_12BIT))

#define IS_ETH_MAC_L4_DEST_PORT_FILTER(x)                                      \
(   ((x) == ETH_MAC_L4_DEST_PORT_FILTER_DISABLE)            ||                 \
    ((x) == ETH_MAC_L4_DEST_PORT_FILTER_NORMAL)             ||                 \
    ((x) == ETH_MAC_L4_DEST_PORT_FILTER_INVERSE))

#define IS_ETH_MAC_L4_SRC_PORT_FILTER(x)                                       \
(   ((x) == ETH_MAC_L4_SRC_PORT_FILTER_DISABLE)             ||                 \
    ((x) == ETH_MAC_L4_SRC_PORT_FILTER_NORMAL)              ||                 \
    ((x) == ETH_MAC_L4_SRC_PORT_FILTER_INVERSE))

#define IS_ETH_MAC_L4_PORT_FILTER_PROTOCOL(x)                                  \
(   ((x) == ETH_MAC_L4_PORT_FILTER_PROTOCOL_TCP)            ||                 \
    ((x) == ETH_MAC_L4_PORT_FILTER_PROTOCOL_UDP))

#define IS_ETH_MAC_L3_DEST_ADDR_FILTER_MASK(x)                                 \
(   ((x) | ETH_MAC_L3_DEST_ADDR_FILTER_MASK_BIT30_0) ==                        \
    ETH_MAC_L3_DEST_ADDR_FILTER_MASK_BIT30_0)

#define IS_ETH_MAC_L3_SRC_ADDR_FILTER_MASK(x)                                  \
(   ((x) | ETH_MAC_L3_SRC_ADDR_FILTER_MASK_BIT30_0) ==                         \
    ETH_MAC_L3_SRC_ADDR_FILTER_MASK_BIT30_0)

#define IS_ETH_MAC_L3_DEST_SRC_ADDR_FILTER_MASK(x)                             \
(   ((x) | ETH_MAC_L3_DEST_SRC_ADDR_FILTER_MASK_BIT126_0) ==                   \
    ETH_MAC_L3_DEST_SRC_ADDR_FILTER_MASK_BIT126_0)

#define IS_ETH_MAC_L3_DEST_ADDR_FILTER(x)                                      \
(   ((x) == ETH_MAC_L3_DEST_ADDR_FILTER_DISABLE)            ||                 \
    ((x) == ETH_MAC_L3_DEST_ADDR_FILTER_NORMAL)             ||                 \
    ((x) == ETH_MAC_L3_DEST_ADDR_FILTER_INVERSE))

#define IS_ETH_MAC_L3_SRC_ADDR_FILTER(x)                                       \
(   ((x) == ETH_MAC_L3_SRC_ADDR_FILTER_DISABLE)             ||                 \
    ((x) == ETH_MAC_L3_SRC_ADDR_FILTER_NORMAL)              ||                 \
    ((x) == ETH_MAC_L3_SRC_ADDR_FILTER_INVERSE))

#define IS_ETH_MAC_L3_ADDR_FILTER_PROTOCOL(x)                                  \
(   ((x) == ETH_MAC_L3_ADDR_FILTER_PROTOCOL_IPV4)           ||                 \
    ((x) == ETH_MAC_L3_ADDR_FILTER_PROTOCOL_IPV6))

#define IS_ETH_MAC_ADDR_NORMAL_INDEX(x)                                        \
(   ((x) == ETH_MAC_ADDR_IDX0)                              ||                 \
    ((x) == ETH_MAC_ADDR_IDX1)                              ||                 \
    ((x) == ETH_MAC_ADDR_IDX2)                              ||                 \
    ((x) == ETH_MAC_ADDR_IDX3)                              ||                 \
    ((x) == ETH_MAC_ADDR_IDX4))

#define IS_ETH_MAC_ADDR_SPEC_INDEX(x)                                          \
(   ((x) == ETH_MAC_ADDR_IDX1)                              ||                 \
    ((x) == ETH_MAC_ADDR_IDX2)                              ||                 \
    ((x) == ETH_MAC_ADDR_IDX3)                              ||                 \
    ((x) == ETH_MAC_ADDR_IDX4))

#define IS_ETH_MAC_ADDR_FILTER(x)                                              \
(   ((x) == ETH_MAC_ADDR_FILTER_DISABLE)                    ||                 \
    ((x) == ETH_MAC_ADDR_FILTER_PERFECT_DEST_ADDR)          ||                 \
    ((x) == ETH_MAC_ADDR_FILTER_PERFECT_SRC_ADDR))

#define IS_ETH_MAC_ADDR_MASK(x)                                                \
(   ((x) | ETH_MAC_ADDR_MASK_ALL) == ETH_MAC_ADDR_MASK_ALL)

#define IS_ETH_MAC_INT_FLAG(x)                                                 \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_MAC_INT_FLAG_ALL) == ETH_MAC_INT_FLAG_ALL))

#define IS_ETH_MAC_INT(x)                                                      \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_MAC_INT_ALL) == ETH_MAC_INT_ALL))

#define IS_ETH_DMA_BURST_MD(x)                                                 \
(   ((x) == ETH_DMA_BURST_MD_NORMAL)                        ||                 \
    ((x) == ETH_DMA_BURST_MD_FIXED)                         ||                 \
    ((x) == ETH_DMA_BURST_MD_MIXED))

#define IS_ETH_DMA_ADDR_ALIGN(x)                                               \
(   ((x) == ETH_DMA_ADDR_ALIGN_DISABLE)                     ||                 \
    ((x) == ETH_DMA_ADDR_ALIGN_ENABLE))

#define IS_ETH_DMA_RX_BURST_LEN(x)                                             \
(   ((x) == ETH_DMA_RX_BURST_LEN_1BEAT)                     ||                 \
    ((x) == ETH_DMA_RX_BURST_LEN_2BEAT)                     ||                 \
    ((x) == ETH_DMA_RX_BURST_LEN_4BEAT)                     ||                 \
    ((x) == ETH_DMA_RX_BURST_LEN_8BEAT)                     ||                 \
    ((x) == ETH_DMA_RX_BURST_LEN_16BEAT)                    ||                 \
    ((x) == ETH_DMA_RX_BURST_LEN_32BEAT)                    ||                 \
    ((x) == ETH_DMA_RX_BURST_LEN_8XPBL_8BEAT)               ||                 \
    ((x) == ETH_DMA_RX_BURST_LEN_8XPBL_16BEAT)              ||                 \
    ((x) == ETH_DMA_RX_BURST_LEN_8XPBL_32BEAT)              ||                 \
    ((x) == ETH_DMA_RX_BURST_LEN_8XPBL_64BEAT)              ||                 \
    ((x) == ETH_DMA_RX_BURST_LEN_8XPBL_128BEAT)             ||                 \
    ((x) == ETH_DMA_RX_BURST_LEN_8XPBL_256BEAT))

#define IS_ETH_DMA_TX_BURST_LEN(x)                                             \
(   ((x) == ETH_DMA_TX_BURST_LEN_1BEAT)                     ||                 \
    ((x) == ETH_DMA_TX_BURST_LEN_2BEAT)                     ||                 \
    ((x) == ETH_DMA_TX_BURST_LEN_4BEAT)                     ||                 \
    ((x) == ETH_DMA_TX_BURST_LEN_8BEAT)                     ||                 \
    ((x) == ETH_DMA_TX_BURST_LEN_16BEAT)                    ||                 \
    ((x) == ETH_DMA_TX_BURST_LEN_32BEAT)                    ||                 \
    ((x) == ETH_DMA_TX_BURST_LEN_8XPBL_8BEAT)               ||                 \
    ((x) == ETH_DMA_TX_BURST_LEN_8XPBL_16BEAT)              ||                 \
    ((x) == ETH_DMA_TX_BURST_LEN_8XPBL_32BEAT)              ||                 \
    ((x) == ETH_DMA_TX_BURST_LEN_8XPBL_64BEAT)              ||                 \
    ((x) == ETH_DMA_TX_BURST_LEN_8XPBL_128BEAT)             ||                 \
    ((x) == ETH_DMA_TX_BURST_LEN_8XPBL_256BEAT))

#define IS_ETH_DMA_ENHANCE_DESC(x)                                             \
(   ((x) == ETH_DMA_ENHANCE_DESC_DISABLE)                   ||                 \
    ((x) == ETH_DMA_ENHANCE_DESC_ENABLE))

#define IS_ETH_DMA_DESC_SKIP_LEN(x)                         ((x) < 0x20U)

#define IS_ETH_DMA_PRIO_ARBITRATION(x)                                         \
(   ((x) == ETH_DMA_ARBITRATION_LOOP_RXTX_1_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_LOOP_RXTX_2_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_LOOP_RXTX_3_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_LOOP_RXTX_4_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_LOOP_TXRX_1_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_LOOP_TXRX_2_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_LOOP_TXRX_3_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_LOOP_TXRX_4_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_FIXED_RX_PRIOR_TX)          ||                 \
    ((x) == ETH_DMA_ARBITRATION_FIXED_TX_PRIOR_RX))

#define IS_ETH_DMA_DROP_CHECKSUM_ERR_FRAME(x)                                  \
(   ((x) == ETH_DMA_DROP_CHECKSUM_ERR_FRAME_DISABLE)        ||                 \
    ((x) == ETH_DMA_DROP_CHECKSUM_ERR_FRAME_ENABLE))

#define IS_ETH_DMA_RX_STORE_FORWARD(x)                                         \
(   ((x) == ETH_DMA_RX_STORE_FORWARD_DISABLE)               ||                 \
    ((x) == ETH_DMA_RX_STORE_FORWARD_ENABLE))

#define IS_ETH_DMA_FLUSH_RX_FRAME(x)                                           \
(   ((x) == ETH_DMA_FLUSH_RX_FRAME_DISABLE)                 ||                 \
    ((x) == ETH_DMA_FLUSH_RX_FRAME_ENABLE))

#define IS_ETH_DMA_TRANS_STORE_FORWARD(x)                                      \
(   ((x) == ETH_DMA_TRANS_STORE_FORWARD_DISABLE)            ||                 \
    ((x) == ETH_DMA_TRANS_STORE_FORWARD_ENABLE))

#define IS_ETH_DMA_TRANS_THRESHOLD(x)                                          \
(   ((x) == ETH_DMA_TRANS_THRESHOLD_64BYTE)                 ||                 \
    ((x) == ETH_DMA_TRANS_THRESHOLD_128BYTE)                ||                 \
    ((x) == ETH_DMA_TRANS_THRESHOLD_192BYTE)                ||                 \
    ((x) == ETH_DMA_TRANS_THRESHOLD_256BYTE)                ||                 \
    ((x) == ETH_DMA_TRANS_THRESHOLD_40BYTE)                 ||                 \
    ((x) == ETH_DMA_TRANS_THRESHOLD_32BYTE)                 ||                 \
    ((x) == ETH_DMA_TRANS_THRESHOLD_24BYTE)                 ||                 \
    ((x) == ETH_DMA_TRANS_THRESHOLD_16BYTE))

#define IS_ETH_DMA_FORWARD_ERR_FRAME(x)                                        \
(   ((x) == ETH_DMA_FORWARD_ERR_FRAME_DISABLE)              ||                 \
    ((x) == ETH_DMA_FORWARD_ERR_FRAME_ENABLE))

#define IS_ETH_DMA_FORWARD_UNDERSIZE_FRAME(x)                                  \
(   ((x) == ETH_DMA_FORWARD_UNDERSIZE_FRAME_DISABLE)        ||                 \
    ((x) == ETH_DMA_FORWARD_UNDERSIZE_FRAME_ENABLE))

#define IS_ETH_DMA_DROP_JUMBO_FRAME(x)                                         \
(   ((x) == ETH_DMA_DROP_JUMBO_FRAME_DISABLE)               ||                 \
    ((x) == ETH_DMA_DROP_JUMBO_FRAME_ENABLE))

#define IS_ETH_DMA_RX_THRESHOLD(x)                                             \
(   ((x) == ETH_DMA_RX_THRESHOLD_64BYTE)                    ||                 \
    ((x) == ETH_DMA_RX_THRESHOLD_32BYTE)                    ||                 \
    ((x) == ETH_DMA_RX_THRESHOLD_96BYTE)                    ||                 \
    ((x) == ETH_DMA_RX_THRESHOLD_128BYTE))

#define IS_ETH_DMA_SEC_FRAME_OPERA(x)                                          \
(   ((x) == ETH_DMA_SEC_FRAME_OPERA_DISABLE)                ||                 \
    ((x) == ETH_DMA_SEC_FRAME_OPERA_ENABLE))

#define IS_ETH_DMA_FLAG(x)                                                     \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_DMA_FLAG_ALL) == ETH_DMA_FLAG_ALL))

#define IS_ETH_DMA_CLR_FLAG(x)                                                 \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_DMA_FLAG_CLR_ALL) == ETH_DMA_FLAG_CLR_ALL))

#define IS_ETH_DMA_INT(x)                                                      \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_DMA_INT_ALL) == ETH_DMA_INT_ALL))

#define IS_ETH_DMA_MISS_FRAME_TYPE(x)                                          \
(   ((x) == ETH_DMA_OVF_RXFIFO_CNT)                         ||                 \
    ((x) == ETH_DMA_OVF_MISS_FRAME_CNT))

#define IS_ETH_DMA_DESC_OWN(x)                                                 \
(   ((x) == ETH_DMA_DESC_OWN_CPU)                           ||                 \
    ((x) == ETH_DMA_DESC_OWN_DMA))

#define IS_ETH_DMA_DESC_BUF(x)                                                 \
(   ((x) == ETH_DMA_DESC_BUF1)                              ||                 \
    ((x) == ETH_DMA_DESC_BUF2))

#define IS_ETH_DMA_TXDESC_BUF_SIZE(x)                       ((x) <= 0x1FFFFFFFUL)

#define IS_ETH_DMA_TXDESC_CHECKSUM_CTRL(x)                                     \
(   ((x) == ETH_DMA_TXDESC_CHECKSUM_BYPASS)                 ||                 \
    ((x) == ETH_DMA_TXDESC_CHECKSUM_IPV4_HEADER)            ||                 \
    ((x) == ETH_DMA_TXDESC_CHECKSUM_TCPUDPICMP_SEGMENT)     ||                 \
    ((x) == ETH_DMA_TXDESC_CHECKSUM_TCPUDPICMP_FULL))

#define IS_ETH_DMA_TXDESC_VLAN_CTRL(x)                                         \
(   ((x) == ETH_DMA_TXDESC_VLAN_BYPASS)                     ||                 \
    ((x) == ETH_DMA_TXDESC_VLAN_REMOVE_TAG)                 ||                 \
    ((x) == ETH_DMA_TXDESC_VLAN_INSERT_TAG)                 ||                 \
    ((x) == ETH_DMA_TXDESC_VLAN_REPLACE_TAG))

#define IS_ETH_DMA_TXDESC_SRC_ADDR_CTRL(x)                                     \
(   ((x) == ETH_DMA_TXDESC_SRC_ADDR_BYPASS)                 ||                 \
    ((x) == ETH_DMA_TXDESC_SRC_ADDR_INSERT_MACADDR0)        ||                 \
    ((x) == ETH_DMA_TXDESC_SRC_ADDR_REPLACE_MACADDR0)       ||                 \
    ((x) == ETH_DMA_TXDESC_SRC_ADDR_INSERT_MACADDR1)        ||                 \
    ((x) == ETH_DMA_TXDESC_SRC_ADDR_REPLACE_MACADDR1))

#define IS_ETH_PMT_FLAG(x)                                                     \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_PMT_FLAG_ALL) == ETH_PMT_FLAG_ALL))

#define IS_ETH_PMT_WAKEUP_SRC(x)                                               \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_PMT_WAKEUP_SRC_ALL) == ETH_PMT_WAKEUP_SRC_ALL))

#define IS_ETH_MMC_CNT_PRESET_MD(x)                                            \
(   ((x) == ETH_MMC_CNT_PRESET_MD_DISABLE)                  ||                 \
    ((x) == ETH_MMC_CNT_PRESET_MD_HALF_VALUE)               ||                 \
    ((x) == ETH_MMC_CNT_PRESET_MD_FULL_VALUE))

#define IS_ETH_MMC_RD_RST(x)                                                   \
(   ((x) == ETH_MMC_RD_RST_DISABLE)                         ||                 \
    ((x) == ETH_MMC_RD_RST_ENABLE))

#define IS_ETH_MMC_CNT_RELOAD(x)                                               \
(   ((x) == ETH_MMC_CNT_RELOAD_DISABLE)                     ||                 \
    ((x) == ETH_MMC_CNT_RELOAD_ENABLE))

#define IS_ETH_MMC_TX_FLAG(x)                                                  \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_MMC_FLAG_TX_ALL) == ETH_MMC_FLAG_TX_ALL))

#define IS_ETH_MMC_RX_FLAG(x)                                                  \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_MMC_FLAG_RX_ALL) == ETH_MMC_FLAG_RX_ALL))

#define IS_ETH_MMC_TX_INT(x)                                                   \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_MMC_INT_TX_ALL) == ETH_MMC_INT_TX_ALL))

#define IS_ETH_MMC_RX_INT(x)                                                   \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_MMC_INT_RX_ALL) == ETH_MMC_INT_RX_ALL))

#define IS_ETH_MMC_REG(x)                                                      \
(   ((x) == ETH_MMC_REG_TXBRGFR)                            ||                 \
    ((x) == ETH_MMC_REG_TXMUGFR)                            ||                 \
    ((x) == ETH_MMC_REG_TXDEEFR)                            ||                 \
    ((x) == ETH_MMC_REG_TXLCEFR)                            ||                 \
    ((x) == ETH_MMC_REG_TXECEFR)                            ||                 \
    ((x) == ETH_MMC_REG_TXCAEFR)                            ||                 \
    ((x) == ETH_MMC_REG_TXUNGFR)                            ||                 \
    ((x) == ETH_MMC_REG_TXEDEFR)                            ||                 \
    ((x) == ETH_MMC_REG_RXBRGFR)                            ||                 \
    ((x) == ETH_MMC_REG_RXMUGFR)                            ||                 \
    ((x) == ETH_MMC_REG_RXCREFR)                            ||                 \
    ((x) == ETH_MMC_REG_RXALEFR)                            ||                 \
    ((x) == ETH_MMC_REG_RXRUEFR)                            ||                 \
    ((x) == ETH_MMC_REG_RXUNGFR)                            ||                 \
    ((x) == ETH_MMC_REG_RXLEEFR)                            ||                 \
    ((x) == ETH_MMC_REG_RXOREFR))

#define IS_ETH_PTP_DEST_ADDR_FILTER(x)                                         \
(   ((x) == ETH_PTP_DEST_ADDR_FILTER_DISABLE)               ||                 \
    ((x) == ETH_PTP_DEST_ADDR_FILTER_ENABLE))

#define IS_ETH_PTP_DATAGRAM_TYPE(x)                                            \
(   ((x) == ETH_PTP_DATAGRAM_TYPE_SYNC_FOLLOW_DELAY)        ||                 \
    ((x) == ETH_PTP_DATAGRAM_TYPE_SYNC)                     ||                 \
    ((x) == ETH_PTP_DATAGRAM_TYPE_DELAY)                    ||                 \
    ((x) == ETH_PTP_DATAGRAM_TYPE_SYNC_FOLLOW_DELAY_PDELAY) ||                 \
    ((x) == ETH_PTP_DATAGRAM_TYPE_SYNC_PDELAY)              ||                 \
    ((x) == ETH_PTP_DATAGRAM_TYPE_DELAY_PDELAY)             ||                 \
    ((x) == ETH_PTP_DATAGRAM_TYPE_SYNC_DELAY)               ||                 \
    ((x) == ETH_PTP_DATAGRAM_TYPE_PDELAY))

#define IS_ETH_PTP_FRAME_TYPE(x)                                               \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_PTP_FRAME_TYPE_ALL) == ETH_PTP_FRAME_TYPE_ALL))

#define IS_ETH_PTP_DATAGRAM_VER(x)                                             \
(   ((x) == ETH_PTP_DATAGRAM_VER_IEEE1588V1)                ||                 \
    ((x) == ETH_PTP_DATAGRAM_VER_IEEE1588V2))

#define IS_ETH_PTP_SUBSEC_SCALE(x)                                             \
(   ((x) == ETH_PTP_SUBSEC_SCALE_HEX)                       ||                 \
    ((x) == ETH_PTP_SUBSEC_SCALE_DEC))

#define IS_ETH_PTP_CALIB_MD(x)                                                 \
(   ((x) == ETH_PTP_CALIB_MD_COARSE)                        ||                 \
    ((x) == ETH_PTP_CALIB_MD_FINE))

#define IS_ETH_PTP_TIME_UPDATE_SIGN(x)                                         \
(   ((x) == ETH_PTP_TIME_UPDATE_SIGN_MINUS)                 ||                 \
    ((x) == ETH_PTP_TIME_UPDATE_SIGN_PLUS))

#define IS_ETH_PTP_FLAG(x)                                                     \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_PTP_FLAG_ALL) == ETH_PTP_FLAG_ALL))

#define IS_ETH_PPS_CH(x)                                                       \
(   ((x) == ETH_PPS_CH0)                                    ||                 \
    ((x) == ETH_PPS_CH1))

#define IS_ETH_PPS_TRIG_FUNC(x)                                                \
(   ((x) == ETH_PPS_TRIG_FUNC_INT_EVT)                      ||                 \
    ((x) == ETH_PPS_TRIG_FUNC_INT_PPS_EVT)                  ||                 \
    ((x) == ETH_PPS_TRIG_FUNC_PPS_EVT))

#define IS_ETH_PPS_OUTPUT_MD(x)                                                \
(   ((x) == ETH_PPS_OUTPUT_MD_CONTINUE)                     ||                 \
    ((x) == ETH_PPS_OUTPUT_MD_ONCE))

#define IS_ETH_PPS_OUTPUT_FREQ(x)                                              \
(   ((x) == ETH_PPS_OUTPUT_FREQ_1HZ)                        ||                 \
    ((x) == ETH_PPS_OUTPUT_FREQ_2HZ)                        ||                 \
    ((x) == ETH_PPS_OUTPUT_FREQ_4HZ)                        ||                 \
    ((x) == ETH_PPS_OUTPUT_FREQ_8HZ)                        ||                 \
    ((x) == ETH_PPS_OUTPUT_FREQ_16HZ)                       ||                 \
    ((x) == ETH_PPS_OUTPUT_FREQ_32HZ)                       ||                 \
    ((x) == ETH_PPS_OUTPUT_FREQ_64HZ)                       ||                 \
    ((x) == ETH_PPS_OUTPUT_FREQ_128HZ)                      ||                 \
    ((x) == ETH_PPS_OUTPUT_FREQ_256HZ)                      ||                 \
    ((x) == ETH_PPS_OUTPUT_FREQ_512HZ)                      ||                 \
    ((x) == ETH_PPS_OUTPUT_FREQ_1024HZ)                     ||                 \
    ((x) == ETH_PPS_OUTPUT_FREQ_2048HZ)                     ||                 \
    ((x) == ETH_PPS_OUTPUT_FREQ_4096HZ)                     ||                 \
    ((x) == ETH_PPS_OUTPUT_FREQ_8192HZ)                     ||                 \
    ((x) == ETH_PPS_OUTPUT_FREQ_16384HZ)                    ||                 \
    ((x) == ETH_PPS_OUTPUT_FREQ_32768HZ)                    ||                 \
    ((x) == ETH_PPS_OUTPUT_ONE_PULSE))

#define IS_ETH_PPS1_COMPLEX_FUNC(ch, mode, freq)                               \
(   ((ch)    == ETH_PPS_CH0)                                ||                 \
    (((mode) == ETH_PPS_OUTPUT_MD_CONTINUE)                 &&                 \
    ((freq)  == ETH_PPS_OUTPUT_ONE_PULSE)))

#define IS_ETH_PTP_SUB_SEC(x)                               ((x) <= 0x7FFFFFFFUL)

#define IS_ETH_DMA_TXDESC_STATUS(x)                                            \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_DMA_TXDESC_STATUS_ALL) == ETH_DMA_TXDESC_STATUS_ALL))

#define IS_ETH_DMA_RXDESC_STATUS(x)                                             \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_DMA_RXDESC_STATUS_ALL) == ETH_DMA_RXDESC_STATUS_ALL))

#define IS_ETH_DMA_RXDESC_EXTEND_STATUS(x)                                     \
(   ((x) != 0U)                                             &&                 \
    (((x) | ETH_DMA_RXDESC_EXTEND_STATUS_ALL) ==                               \
    ETH_DMA_RXDESC_EXTEND_STATUS_ALL))

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup ETH_Global_Functions ETH Global Functions
 * @{
 */

/**
 * @brief  De-Initialize ETH.
 * @param  None
 * @retval int32_t:
 *           - LL_OK: De-Initialize success
 *           - LL_ERR_TIMEOUT: De-Initialize timeout
 */
int32_t ETH_DeInit(void)
{
    int32_t i32Ret;

    i32Ret = ETH_DMA_SoftwareReset();
    if (LL_OK == i32Ret) {
        ETH_DMA_DeInit();
        ETH_MAC_DeInit();
        ETH_MACADDR_DeInit(ETH_MAC_ADDR_IDX0);
        ETH_MACADDR_DeInit(ETH_MAC_ADDR_IDX1);
        ETH_MACADDR_DeInit(ETH_MAC_ADDR_IDX2);
        ETH_MACADDR_DeInit(ETH_MAC_ADDR_IDX3);
        ETH_MACADDR_DeInit(ETH_MAC_ADDR_IDX4);
        ETH_MAC_L3L4FilterDeInit();
        ETH_PTP_DeInit();
        ETH_PPS_DeInit(ETH_PPS_CH0);
        ETH_PPS_DeInit(ETH_PPS_CH1);
        i32Ret = ETH_MMC_DeInit();
    }

    return i32Ret;
}

/**
 * @brief  Initialize ETH.
 * @param  [in] pstcEthHandle           Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] pstcEthInit             Pointer to a @ref stc_eth_init_t structure
 * @retval int32_t:
 *           - LL_OK: ETH Initialize success
 *           - LL_ERR_INVD_PARAM: pstcEthHandle == NULL or pstcEthInit == NULL or PHY Address error
 *           - LL_ERR_TIMEOUT: Initialize timeout
 */
int32_t ETH_Init(stc_eth_handle_t *pstcEthHandle, stc_eth_init_t *pstcEthInit)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_OK;
    uint32_t u32TempReg;
    uint32_t u32BusClk;
    uint32_t u32PhyTimeout;
    uint16_t u16PhyReg = 0U;

    if ((NULL == pstcEthHandle) || (NULL == pstcEthInit)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_AUTO_NEGO(pstcEthHandle->stcCommInit.u16AutoNego));
        DDL_ASSERT(IS_ETH_MAC_CHECKSUM_MD(pstcEthHandle->stcCommInit.u32ChecksumMode));
        DDL_ASSERT(IS_ETH_RX_MD(pstcEthHandle->stcCommInit.u32ReceiveMode));
        DDL_ASSERT(IS_ETH_MAC_IF(pstcEthHandle->stcCommInit.u32Interface));

        /* Select MII or RMII Mode*/
        MODIFY_REG32(CM_ETH->MAC_IFCONFR, ETH_MAC_IFCONFR_IFSEL, pstcEthHandle->stcCommInit.u32Interface);
        /* ETH software reset */
        if (LL_OK != ETH_DMA_SoftwareReset()) {
            i32Ret = LL_ERR_TIMEOUT;
        } else {
            /* Get ETH frequency value */
            u32BusClk = SystemCoreClock / (0x01UL << (READ_REG32_BIT(CM_CMU->SCFGR,
                                                                     CMU_SCFGR_PCLK1S) >> CMU_SCFGR_PCLK1S_POS));
            /* Set SMIC bits depending on PCLK1 clock value */
            /* PCLK1 Clock Range between 20-35 MHz */
            if ((u32BusClk >= 20000000UL) && (u32BusClk <= 35000000UL)) {
                u32TempReg = ETH_MAC_SMIADDR_SMIC_1;
            } else if ((u32BusClk > 35000000UL) && (u32BusClk <= 60000000UL)) {     /* PCLK1 Clock Range between 35-60 MHz */
                u32TempReg = ETH_MAC_SMIADDR_SMIC_1 | ETH_MAC_SMIADDR_SMIC_0;
            } else if ((u32BusClk > 60000000UL) && (u32BusClk <= 100000000UL)) {    /* PCLK1 Clock Range between 60-100 MHz */
                u32TempReg = 0UL;
            } else {    /* PCLK1 Clock Range between 100-120 MHz */
                u32TempReg = ETH_MAC_SMIADDR_SMIC_0;
            }
            /* Configure the ETH MDC Clock Range */
            MODIFY_REG32(CM_ETH->MAC_SMIADDR, ETH_MAC_SMIADDR_SMIC, u32TempReg);

            /* PHY initialization and configuration */
            /* Reset the PHY */
            if (LL_OK != (ETH_PHY_WriteReg(pstcEthHandle, PHY_BCR, PHY_SOFT_RESET))) {
                i32Ret = LL_ERR_TIMEOUT;
            } else {
                /* Delay to assure PHY reset */
                DDL_DelayMS(ETH_PHY_RST_DELAY);
                if (ETH_AUTO_NEGO_DISABLE != pstcEthHandle->stcCommInit.u16AutoNego) {
                    u32PhyTimeout = ETH_PHY_RD_TIMEOUT * (HCLK_VALUE / 20000UL);
                    /* Wait for link status */
                    u32Count = ETH_LINK_STATUS_TIMEOUT * (HCLK_VALUE / 20000UL);
                    while (PHY_LINK_STATUS != (u16PhyReg & PHY_LINK_STATUS)) {
                        if (0UL == u32Count) {
                            break;
                        }
                        if (LL_ERR_TIMEOUT == ETH_PHY_ReadReg(pstcEthHandle, PHY_BSR, &u16PhyReg)) {
                            u32Count = (u32Count > u32PhyTimeout) ? (u32Count - u32PhyTimeout) : 0UL;
                        } else {
                            u32Count = (u32Count > u32PhyTimeout) ? (u32Count - (u32PhyTimeout / 150U)) : 0UL;
                        }
                    }

                    if ((0x0000U == u16PhyReg) || (0xFFFFU == u16PhyReg)) {
                        i32Ret = LL_ERR_INVD_PARAM;
                    } else if (PHY_LINK_STATUS != (u16PhyReg & PHY_LINK_STATUS)) {
                        i32Ret = LL_ERR_TIMEOUT;
                    } else {
                        /* Enable Auto-Negotiation */
                        if (LL_OK != (ETH_PHY_WriteReg(pstcEthHandle, PHY_BCR, PHY_AUTONEGOTIATION))) {
                            i32Ret = LL_ERR_TIMEOUT;
                        } else {
                            /* Wait until the auto-negotiation will be completed */
                            u32Count = ETH_AUTO_NEGO_CPLT_TIMEOUT * (HCLK_VALUE / 20000UL);
                            while (PHY_AUTONEGO_COMPLETE != (u16PhyReg & PHY_AUTONEGO_COMPLETE)) {
                                if (0UL == u32Count) {
                                    break;
                                }
                                if (LL_ERR_TIMEOUT == ETH_PHY_ReadReg(pstcEthHandle, PHY_BSR, &u16PhyReg)) {
                                    u32Count = (u32Count > u32PhyTimeout) ? (u32Count - u32PhyTimeout) : 0UL;
                                } else {
                                    u32Count = (u32Count > u32PhyTimeout) ? (u32Count - (u32PhyTimeout / 150U)) : 0UL;
                                }
                            }

                            if (PHY_AUTONEGO_COMPLETE != (u16PhyReg & PHY_AUTONEGO_COMPLETE)) {
                                i32Ret = LL_ERR_TIMEOUT;
                            } else {
                                /* Read the result of the auto-negotiation */
                                (void)ETH_PHY_ReadReg(pstcEthHandle, PHY_SR, &u16PhyReg);
                                /* Configure ETH duplex mode according to the result of automatic negotiation */
                                if (0U != (u16PhyReg & PHY_DUPLEX_STATUS)) {
                                    pstcEthHandle->stcCommInit.u32DuplexMode = ETH_MAC_DUPLEX_MD_FULL;
                                } else {
                                    pstcEthHandle->stcCommInit.u32DuplexMode = ETH_MAC_DUPLEX_MD_HALF;
                                }
                                /* Configure ETH speed according to the result of automatic negotiation */
                                if (0U != (u16PhyReg & PHY_SPEED_STATUS)) {
                                    pstcEthHandle->stcCommInit.u32Speed = ETH_MAC_SPEED_100M;
                                } else {
                                    pstcEthHandle->stcCommInit.u32Speed = ETH_MAC_SPEED_10M;
                                }
                            }
                        }
                    }
                } else {    /* AutoNegotiation Disable */
                    DDL_ASSERT(IS_ETH_MAC_SPEED(pstcEthHandle->stcCommInit.u32Speed));
                    DDL_ASSERT(IS_ETH_MAC_DUPLEX_MD(pstcEthHandle->stcCommInit.u32DuplexMode));

                    if (LL_OK != ETH_PHY_WriteReg(pstcEthHandle, PHY_BCR,
                                                  ((uint16_t)(pstcEthHandle->stcCommInit.u32DuplexMode >> 3U) |
                                                   (uint16_t)(pstcEthHandle->stcCommInit.u32Speed >> 1U)))) {
                        i32Ret = LL_ERR_TIMEOUT;
                    } else {
                        /* Wait for link status */
                        u32PhyTimeout = ETH_PHY_RD_TIMEOUT * (HCLK_VALUE / 20000UL);
                        u32Count = ETH_LINK_STATUS_TIMEOUT * (HCLK_VALUE / 20000UL);
                        while (PHY_LINK_STATUS != (u16PhyReg & PHY_LINK_STATUS)) {
                            if (0UL == u32Count) {
                                break;
                            }
                            if (LL_ERR_TIMEOUT == ETH_PHY_ReadReg(pstcEthHandle, PHY_BSR, &u16PhyReg)) {
                                u32Count = (u32Count > u32PhyTimeout) ? (u32Count - u32PhyTimeout) : 0UL;
                            } else {
                                u32Count = (u32Count > u32PhyTimeout) ? (u32Count - (u32PhyTimeout / 150U)) : 0UL;
                            }
                        }
                        if ((0x0000U == u16PhyReg) || (0xFFFFU == u16PhyReg)) {
                            i32Ret = LL_ERR_INVD_PARAM;
                        } else if (PHY_LINK_STATUS != (u16PhyReg & PHY_LINK_STATUS)) {
                            i32Ret = LL_ERR_TIMEOUT;
                        } else {
                            /* Reserved */
                        }
                    }
                }
            }

            /* Auto-negotiation failed */
            if (LL_OK != i32Ret) {
                pstcEthHandle->stcCommInit.u32DuplexMode = ETH_MAC_DUPLEX_MD_FULL;
                pstcEthHandle->stcCommInit.u32Speed      = ETH_MAC_SPEED_100M;
            }
            /* Config checksum offload */
            if (ETH_MAC_CHECKSUM_MD_HW == pstcEthHandle->stcCommInit.u32ChecksumMode) {
                pstcEthInit->stcMacInit.u32ChecksumOffload = ETH_MAC_CHECKSUM_OFFLOAD_ENABLE;
            } else {
                pstcEthInit->stcMacInit.u32ChecksumOffload = ETH_MAC_CHECKSUM_OFFLOAD_DISABLE;
            }

            /* Config MAC,DMA,MMC and PTP */
            (void)ETH_MAC_Init(pstcEthHandle, &pstcEthInit->stcMacInit);
            (void)ETH_DMA_Init(&pstcEthInit->stcDmaInit);
            /* Mask all MMC interrupts */
            ETH_MMC_TxIntCmd(ETH_MMC_INT_TX_ALL, DISABLE);
            ETH_MMC_RxIntCmd(ETH_MMC_INT_RX_ALL, DISABLE);
            /* Enable the ETH Rx Interrupt */
            if (ETH_RX_MD_INT == pstcEthHandle->stcCommInit.u32ReceiveMode) {
                ETH_DMA_IntCmd(ETH_DMA_INT_NIE | ETH_DMA_INT_RIE, ENABLE);
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_eth_comm_init_t to default values.
 * @param  [out] pstcCommInit           Pointer to a @ref stc_eth_comm_init_t structure
 * @retval int32_t:
 *           - LL_OK: Structure Initialize success
 *           - LL_ERR_INVD_PARAM: pstcCommInit == NULL
 */
int32_t ETH_CommStructInit(stc_eth_comm_init_t *pstcCommInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcCommInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcCommInit->u16AutoNego       = ETH_AUTO_NEGO_ENABLE;
        pstcCommInit->u16PhyAddr        = ETH_PHY_ADDR;
        pstcCommInit->au8MacAddr[0]     = ETH_MAC_ADDR0;
        pstcCommInit->au8MacAddr[1]     = ETH_MAC_ADDR1;
        pstcCommInit->au8MacAddr[2]     = ETH_MAC_ADDR2;
        pstcCommInit->au8MacAddr[3]     = ETH_MAC_ADDR3;
        pstcCommInit->au8MacAddr[4]     = ETH_MAC_ADDR4;
        pstcCommInit->au8MacAddr[5]     = ETH_MAC_ADDR5;
        pstcCommInit->u32Interface      = ETH_MAC_IF_MII;
        pstcCommInit->u32Speed          = ETH_MAC_SPEED_100M;
        pstcCommInit->u32DuplexMode     = ETH_MAC_DUPLEX_MD_FULL;
        pstcCommInit->u32ChecksumMode   = ETH_MAC_CHECKSUM_MD_HW;
        pstcCommInit->u32ReceiveMode    = ETH_RX_MD_POLLING;
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_eth_init_t to default values.
 * @param  [out] pstcEthInit            Pointer to a @ref stc_eth_init_t structure
 * @retval int32_t:
 *           - LL_OK: Structure Initialize success
 *           - LL_ERR_INVD_PARAM: pstcEthInit == NULL
 */
int32_t ETH_StructInit(stc_eth_init_t *pstcEthInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcEthInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        (void)ETH_MAC_StructInit(&pstcEthInit->stcMacInit);
        (void)ETH_DMA_StructInit(&pstcEthInit->stcDmaInit);
    }

    return i32Ret;
}

/**
 * @brief  Enable MAC and DMA Transmission/Reception
 * @param  None
 * @retval int32_t:
 *           - LL_OK: Enable success
 *           - LL_ERR_TIMEOUT: Enable timeout
 */
int32_t ETH_Start(void)
{
    int32_t i32Ret;

    /* Flush Transmit FIFO */
    i32Ret = ETH_DMA_FlushTransFIFO();
    if (LL_OK == i32Ret) {
        /* Enable DMA Transmit */
        ETH_DMA_TransCmd(ENABLE);
        /* Enable DMA Receive */
        ETH_DMA_ReceiveCmd(ENABLE);
        /* Enable MAC Transmit */
        ETH_MAC_TransCmd(ENABLE);
        /* Enable MAC Receive */
        ETH_MAC_ReceiveCmd(ENABLE);
    }

    return i32Ret;
}

/**
 * @brief  Disable MAC and DMA Transmission/Reception
 * @param  None
 * @retval int32_t:
 *           - LL_OK: Disable success
 *           - LL_ERR_TIMEOUT: Disable timeout
 */
int32_t ETH_Stop(void)
{
    int32_t i32Ret;

    /* Disable MAC Receive */
    ETH_MAC_ReceiveCmd(DISABLE);
    /* Disable MAC Transmit */
    ETH_MAC_TransCmd(DISABLE);
    /* Disable DMA Transmit */
    ETH_DMA_TransCmd(DISABLE);
    /* Disable DMA Receive */
    ETH_DMA_ReceiveCmd(DISABLE);
    /* Flush Transmit FIFO */
    i32Ret = ETH_DMA_FlushTransFIFO();

    return i32Ret;
}

/******************************************************************************/
/*                             PHY Functions                                  */
/******************************************************************************/
/**
 * @brief  Write PHY register
 * @note   More PHY register could be written depending on the used PHY.
 * @param  [in] pstcEthHandle           Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] u16Reg                  PHY register address
 *         This parameter can be one of the following values:
 *           @arg PHY_BCR:              PHY Basic Control Register
 *           @arg other value:          The value range from 1 to 31
 * @param  [in] u16Value                PHY register value
 * @retval int32_t:
 *           - LL_OK: Write register success
 *           - LL_ERR_INVD_PARAM: pstcEthHandle == NULL
 *           - LL_ERR_TIMEOUT: Write timeout
 */
int32_t ETH_PHY_WriteReg(stc_eth_handle_t *pstcEthHandle, uint16_t u16Reg, uint16_t u16Value)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_OK;

    if (NULL == pstcEthHandle) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_PHY_ADDR(pstcEthHandle->stcCommInit.u16PhyAddr));
        DDL_ASSERT(IS_ETH_PHY_REG(u16Reg));

        /* Set the MAC_SMIDATR register */
        WRITE_REG32(CM_ETH->MAC_SMIDATR, u16Value);
        /* Set the MAC_SMIADDR register */
        /* Keep only the MDC Clock Range SMIC[3:0] bits value */
        MODIFY_REG32(CM_ETH->MAC_SMIADDR, ETH_MAC_SMIADDR_CLR_MASK,
                     (((uint32_t)(pstcEthHandle->stcCommInit.u16PhyAddr) << ETH_MAC_SMIADDR_SMIA_POS) |
                      ((uint32_t)u16Reg << ETH_MAC_SMIADDR_SMIR_POS) | ETH_MAC_SMIADDR_SMIW | ETH_MAC_SMIADDR_SMIB));
        /* Check for the Busy flag */
        u32Count = ETH_PHY_WR_TIMEOUT * (HCLK_VALUE / 20000UL);
        while (0UL != READ_REG32_BIT(CM_ETH->MAC_SMIADDR, ETH_MAC_SMIADDR_SMIB)) {
            if (0UL == u32Count) {
                i32Ret = LL_ERR_TIMEOUT;
                break;
            }
            u32Count--;
        }
    }

    return i32Ret;
}

/**
 * @brief  Read PHY register.
 * @note   More PHY register could be read depending on the used PHY.
 * @param  [in] pstcEthHandle           Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] u16Reg                  PHY register address
 *         This parameter can be one of the following values:
 *           @arg PHY_BCR:              PHY Basic Control Register
 *           @arg PHY_BSR:              PHY Basic Status Register
 *           @arg other value:          The value range from 2 to 31
 * @param  [out] pu16Value              Pointer to PHY register value
 * @retval int32_t:
 *           - LL_OK: Read register success
 *           - LL_ERR_INVD_PARAM: pstcEthHandle == NULL or pu16Value == NULL
 *           - LL_ERR_TIMEOUT: Read timeout
 */
int32_t ETH_PHY_ReadReg(stc_eth_handle_t *pstcEthHandle, uint16_t u16Reg, uint16_t *pu16Value)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_OK;

    if ((NULL == pstcEthHandle) || (NULL == pu16Value)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_PHY_ADDR(pstcEthHandle->stcCommInit.u16PhyAddr));
        DDL_ASSERT(IS_ETH_PHY_REG(u16Reg));

        *pu16Value = 0U;
        /* Set the MAC_SMIADDR register */
        /* Keep only the MDC Clock Range SMIC[3:0] bits value */
        MODIFY_REG32(CM_ETH->MAC_SMIADDR, ETH_MAC_SMIADDR_CLR_MASK,
                     (((uint32_t)(pstcEthHandle->stcCommInit.u16PhyAddr) << ETH_MAC_SMIADDR_SMIA_POS) |
                      ((uint32_t)u16Reg << ETH_MAC_SMIADDR_SMIR_POS) | ETH_MAC_SMIADDR_SMIB));
        /* Check for the Busy flag */
        u32Count = ETH_PHY_RD_TIMEOUT * (HCLK_VALUE / 20000UL);
        while (0UL != READ_REG32_BIT(CM_ETH->MAC_SMIADDR, ETH_MAC_SMIADDR_SMIB)) {
            if (0UL == u32Count) {
                i32Ret = LL_ERR_TIMEOUT;
                break;
            }
            u32Count--;
        }
        if (LL_ERR_TIMEOUT != i32Ret) {
            /* Get the MAC_SMIDATR value */
            *pu16Value = (uint16_t)(READ_REG32(CM_ETH->MAC_SMIDATR));
        }
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable PHY loopback.
 * @param  [in] pstcEthHandle           Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *           - LL_OK: Set loopback success
 *           - LL_ERR_INVD_PARAM: pstcEthHandle == NULL
 *           - LL_ERR: Communication error
 */
int32_t ETH_PHY_LoopBackCmd(stc_eth_handle_t *pstcEthHandle, en_functional_state_t enNewState)
{
    int32_t i32Ret;
    uint16_t u16Value;

    if (NULL == pstcEthHandle) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_PHY_ADDR(pstcEthHandle->stcCommInit.u16PhyAddr));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        i32Ret = ETH_PHY_ReadReg(pstcEthHandle, PHY_BCR, &u16Value);
        if (i32Ret == LL_OK) {
            if (DISABLE != enNewState) {
                SET_REG16_BIT(u16Value, PHY_LOOPBACK);
            } else {
                CLR_REG16_BIT(u16Value, PHY_LOOPBACK);
            }
            if (LL_OK != ETH_PHY_WriteReg(pstcEthHandle, PHY_BCR, u16Value)) {
                i32Ret = LL_ERR;
            }
        }
    }

    return i32Ret;
}

/******************************************************************************/
/*                             MAC Functions                                  */
/******************************************************************************/
/**
 * @brief  De-Initialize MAC.
 * @param  None
 * @retval None
 */
void ETH_MAC_DeInit(void)
{
    WRITE_REG32(CM_ETH->MAC_IFCONFR,  0UL);
    WRITE_REG32(CM_ETH->MAC_CONFIGR,  0x00008000UL);
    MODIFY_REG32(CM_ETH->MAC_FLTCTLR, ETH_MAC_FLTCTLR_CLR_MASK, 0UL);
    WRITE_REG32(CM_ETH->MAC_FLOCTLR,  0UL);
    WRITE_REG32(CM_ETH->MAC_INTMSKR,  0UL);
    WRITE_REG32(CM_ETH->MAC_SMIADDR,  0UL);
    WRITE_REG32(CM_ETH->MAC_SMIDATR,  0UL);
    WRITE_REG32(CM_ETH->MAC_RTWKFFR,  0UL);
    WRITE_REG32(CM_ETH->MAC_PMTCTLR,  0UL);
    WRITE_REG32(CM_ETH->MAC_HASHTLR,  0UL);
    WRITE_REG32(CM_ETH->MAC_HASHTHR,  0UL);
    WRITE_REG32(CM_ETH->MAC_VTACTLR,  0UL);
    WRITE_REG32(CM_ETH->MAC_VTAFLTR,  0UL);
    WRITE_REG32(CM_ETH->MAC_VLAHTBR,  0UL);
}

/**
 * @brief  Initialize MAC.
 * @param  [in] pstcEthHandle           Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] pstcMacInit             Pointer to a @ref stc_eth_mac_init_t structure
 * @retval int32_t:
 *           - LL_OK: MAC Initialize success
 *           - LL_ERR_INVD_PARAM: pstcEthHandle == NULL or pstcMacInit == NULL
 */
int32_t ETH_MAC_Init(stc_eth_handle_t *pstcEthHandle, const stc_eth_mac_init_t *pstcMacInit)
{
    int32_t i32Ret = LL_OK;

    if ((NULL == pstcEthHandle) || (NULL == pstcMacInit)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_MAC_TX_CLK_POLARITY(pstcMacInit->u32TxClockPolarity));
        DDL_ASSERT(IS_ETH_MAC_RX_CLK_POLARITY(pstcMacInit->u32RxClockPolarity));
        DDL_ASSERT(IS_ETH_MAC_SRC_ADDR_MD(pstcMacInit->u32SrcAddrMode));
        DDL_ASSERT(IS_ETH_MAC_TYPE_FRAME_STRIP_FCS(pstcMacInit->u32TypeFrameStripFCS));
        DDL_ASSERT(IS_ETH_MAC_WATCHDOG(pstcMacInit->u32Watchdog));
        DDL_ASSERT(IS_ETH_MAC_JABBER(pstcMacInit->u32Jabber));
        DDL_ASSERT(IS_ETH_MAC_INTERFRAME_GAP(pstcMacInit->u32InterframeGap));
        DDL_ASSERT(IS_ETH_MAC_CARRIER_SENSE(pstcMacInit->u32CarrierSense));
        DDL_ASSERT(IS_ETH_MAC_SPEED(pstcEthHandle->stcCommInit.u32Speed));
        DDL_ASSERT(IS_ETH_MAC_RX_OWN(pstcMacInit->u32ReceiveOwn));
        DDL_ASSERT(IS_ETH_MAC_DUPLEX_MD(pstcEthHandle->stcCommInit.u32DuplexMode));
        DDL_ASSERT(IS_ETH_MAC_CHECKSUM_OFFLOAD(pstcMacInit->u32ChecksumOffload));
        DDL_ASSERT(IS_ETH_MAC_RETRY_TRANS(pstcMacInit->u32RetryTrans));
        DDL_ASSERT(IS_ETH_MAC_AUTO_STRIP_PAD_FCS(pstcMacInit->u32AutoStripPadFCS));
        DDL_ASSERT(IS_ETH_MAC_BACKOFF_LIMIT(pstcMacInit->u32BackOffLimit));
        DDL_ASSERT(IS_ETH_MAC_DEFERRAL_CHECK(pstcMacInit->u32DeferralCheck));
        DDL_ASSERT(IS_ETH_MAC_ZERO_QUANTA_PAUSE(pstcMacInit->u32ZeroQuantaPause));
        DDL_ASSERT(IS_ETH_MAC_PAUSE_LOW_THRESHOLD(pstcMacInit->u32PauseLowThreshold));
        DDL_ASSERT(IS_ETH_MAC_UNICAST_PAUSE_FRAME_DETECT(pstcMacInit->u32UnicastPauseFrame));
        DDL_ASSERT(IS_ETH_MAC_RX_FLOW_CTRL(pstcMacInit->u32ReceiveFlowControl));
        DDL_ASSERT(IS_ETH_MAC_TRANS_FLOW_CTRL(pstcMacInit->u32TransFlowControl));
        DDL_ASSERT(IS_ETH_MAC_RX_ALL(pstcMacInit->u32ReceiveAll));
        DDL_ASSERT(IS_ETH_MAC_DROP_NOT_TCPUDP(pstcMacInit->u32DropNotTcpUdp));
        DDL_ASSERT(IS_ETH_MAC_VLAN_TAG_FILTER(pstcMacInit->u32VlanTagFilter));
        DDL_ASSERT(IS_ETH_MAC_SRC_ADDR_FILTER(pstcMacInit->u32SrcAddrFilter));
        DDL_ASSERT(IS_ETH_MAC_PASS_CTRL_FRAME(pstcMacInit->u32PassControlFrame));
        DDL_ASSERT(IS_ETH_MAC_BROADCAST_FRAME(pstcMacInit->u32BroadcastFrame));
        DDL_ASSERT(IS_ETH_MAC_DEST_ADDR_FILTER(pstcMacInit->u32DestAddrFilter));
        DDL_ASSERT(IS_ETH_MAC_MULTICAST_FRAME_FILTER(pstcMacInit->u32MulticastFrameFilter));
        DDL_ASSERT(IS_ETH_MAC_UNICAST_FRAME_FILTER(pstcMacInit->u32UnicastFrameFilter));
        DDL_ASSERT(IS_ETH_MAC_PROMISCUOUS_MD(pstcMacInit->u32PromiscuousMode));
        DDL_ASSERT(IS_ETH_MAC_TXVLAN_MD(pstcMacInit->u32TxVlanMode));
        DDL_ASSERT(IS_ETH_MAC_RXVLAN_FILTER(pstcMacInit->u32RxVlanFilter));
        DDL_ASSERT(IS_ETH_MAC_RXVLAN_CMP(pstcMacInit->u32RxVlanCompare));

        /* Set MAC_IFCONFR register */
        MODIFY_REG32(CM_ETH->MAC_IFCONFR, ETH_MAC_IFCONFR_CLR_MASK,
                     (pstcMacInit->u32TxClockPolarity | pstcMacInit->u32RxClockPolarity));
        /* Set MAC_CONFIGR register */
        MODIFY_REG32(CM_ETH->MAC_CONFIGR, ETH_MAC_CONFIGR_CLR_MASK,
                     (pstcMacInit->u32SrcAddrMode         | pstcMacInit->u32TypeFrameStripFCS        |
                      pstcMacInit->u32Watchdog            | pstcMacInit->u32Jabber                   |
                      pstcMacInit->u32InterframeGap       | pstcMacInit->u32CarrierSense             |
                      pstcEthHandle->stcCommInit.u32Speed | pstcMacInit->u32ReceiveOwn               |
                      pstcMacInit->u32DeferralCheck       | pstcEthHandle->stcCommInit.u32DuplexMode |
                      pstcMacInit->u32ChecksumOffload     | pstcMacInit->u32RetryTrans               |
                      pstcMacInit->u32AutoStripPadFCS     | pstcMacInit->u32BackOffLimit));
        /* Set MAC_FLOCTLR register */
        MODIFY_REG32(CM_ETH->MAC_FLOCTLR, ETH_MAC_FLOCTLR_CLR_MASK,
                     ((((uint32_t)pstcMacInit->u16PauseTime) << 16U) | pstcMacInit->u32ZeroQuantaPause   |
                      pstcMacInit->u32PauseLowThreshold              | pstcMacInit->u32UnicastPauseFrame |
                      pstcMacInit->u32ReceiveFlowControl             | pstcMacInit->u32TransFlowControl));
        /* Set MAC_FLTCTLR register */
        MODIFY_REG32(CM_ETH->MAC_FLTCTLR, ETH_MAC_FLTCTLR_CLR_MASK,
                     (pstcMacInit->u32ReceiveAll           | pstcMacInit->u32DropNotTcpUdp    |
                      pstcMacInit->u32PromiscuousMode      | pstcMacInit->u32VlanTagFilter    |
                      pstcMacInit->u32SrcAddrFilter        | pstcMacInit->u32PassControlFrame |
                      pstcMacInit->u32BroadcastFrame       | pstcMacInit->u32DestAddrFilter   |
                      pstcMacInit->u32MulticastFrameFilter | pstcMacInit->u32UnicastFrameFilter));
        /* Set Hash table register */
        WRITE_REG32(CM_ETH->MAC_HASHTLR, pstcMacInit->u32HashTableLow);
        WRITE_REG32(CM_ETH->MAC_HASHTHR, pstcMacInit->u32HashTableHigh);
        /* Set Tx VLAN register */
        WRITE_REG32(CM_ETH->MAC_VTACTLR, (pstcMacInit->u32TxVlanMode | pstcMacInit->u16TxVlanTag));
        /* Set Rx VLAN register */
        WRITE_REG32(CM_ETH->MAC_VTAFLTR, (pstcMacInit->u32RxVlanFilter | pstcMacInit->u32RxVlanCompare |
                                          pstcMacInit->u16RxVlanTag));
        WRITE_REG32(CM_ETH->MAC_VLAHTBR, pstcMacInit->u16RxVlanHashTable);
        /* Config MAC address in ETH MAC0 */
        (void)ETH_MACADDR_SetAddr(ETH_MAC_ADDR_IDX0, pstcEthHandle->stcCommInit.au8MacAddr);
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_eth_mac_init_t to default values.
 * @param  [out] pstcMacInit            Pointer to a @ref stc_eth_mac_init_t structure
 * @retval int32_t:
 *           - LL_OK: Structure Initialize success
 *           - LL_ERR_INVD_PARAM: pstcMacInit == NULL
 */
int32_t ETH_MAC_StructInit(stc_eth_mac_init_t *pstcMacInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcMacInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcMacInit->u32TxClockPolarity     = ETH_MAC_TX_CLK_POLARITY_KEEP;
        pstcMacInit->u32RxClockPolarity     = ETH_MAC_RX_CLK_POLARITY_KEEP;
        pstcMacInit->u32SrcAddrMode         = ETH_MAC_TXVLAN_MD_BY_DMA_TXDESC;
        pstcMacInit->u32TypeFrameStripFCS   = ETH_MAC_TYPE_FRAME_STRIP_FCS_DISABLE;
        pstcMacInit->u32Watchdog            = ETH_MAC_WATCHDOG_ENABLE;
        pstcMacInit->u32Jabber              = ETH_MAC_JABBER_ENABLE;
        pstcMacInit->u32InterframeGap       = ETH_MAC_INTERFRAME_GAP_96BIT;
        pstcMacInit->u32CarrierSense        = ETH_MAC_CARRIER_SENSE_ENABLE;
        pstcMacInit->u32ReceiveOwn          = ETH_MAC_RX_OWN_ENABLE;
        pstcMacInit->u32ChecksumOffload     = ETH_MAC_CHECKSUM_OFFLOAD_DISABLE;
        pstcMacInit->u32RetryTrans          = ETH_MAC_RETRY_TRANS_DISABLE;
        pstcMacInit->u32AutoStripPadFCS     = ETH_MAC_AUTO_STRIP_PAD_FCS_DISABLE;
        pstcMacInit->u32BackOffLimit        = ETH_MAC_BACKOFF_LIMIT10;
        pstcMacInit->u32DeferralCheck       = ETH_MAC_DEFERRAL_CHECK_DISABLE;
        pstcMacInit->u16PauseTime           = 0U;
        pstcMacInit->u32ZeroQuantaPause     = ETH_MAC_ZERO_QUANTA_PAUSE_DISABLE;
        pstcMacInit->u32PauseLowThreshold   = ETH_MAC_PAUSE_LOW_THRESHOLD_MINUS4;
        pstcMacInit->u32UnicastPauseFrame   = ETH_MAC_UNICAST_PAUSE_FRAME_DETECT_DISABLE;
        pstcMacInit->u32ReceiveFlowControl  = ETH_MAC_RX_FLOW_CTRL_DISABLE;
        pstcMacInit->u32TransFlowControl    = ETH_MAC_TRANS_FLOW_CTRL_DISABLE;
        pstcMacInit->u32ReceiveAll          = ETH_MAC_RX_ALL_DISABLE;
        pstcMacInit->u32DropNotTcpUdp       = ETH_MAC_DROP_NOT_TCPUDP_DISABLE;

        pstcMacInit->u32VlanTagFilter           = ETH_MAC_VLAN_TAG_FILTER_DISABLE;
        pstcMacInit->u32SrcAddrFilter           = ETH_MAC_SRC_ADDR_FILTER_DISABLE;
        pstcMacInit->u32PassControlFrame        = ETH_MAC_PASS_CTRL_FRAME_FORWARD_NOT_PAUSE;
        pstcMacInit->u32BroadcastFrame          = ETH_MAC_RX_BROADCAST_FRAME_ENABLE;
        pstcMacInit->u32DestAddrFilter          = ETH_MAC_DEST_ADDR_FILTER_NORMAL;
        pstcMacInit->u32MulticastFrameFilter    = ETH_MAC_MULTICAST_FRAME_FILTER_PERFECT;
        pstcMacInit->u32UnicastFrameFilter      = ETH_MAC_UNICAST_FRAME_FILTER_PERFECT;
        pstcMacInit->u32PromiscuousMode         = ETH_MAC_PROMISCUOUS_MD_DISABLE;
        pstcMacInit->u32HashTableHigh           = 0UL;
        pstcMacInit->u32HashTableLow            = 0UL;
        pstcMacInit->u32TxVlanMode              = ETH_MAC_TXVLAN_MD_BYPASS;
        pstcMacInit->u16TxVlanTag               = 0U;
        pstcMacInit->u32RxVlanFilter            = ETH_MAC_RXVLAN_FILTER_NORMAL;
        pstcMacInit->u32RxVlanCompare           = ETH_MAC_RXVLAN_CMP_16BIT;
        pstcMacInit->u16RxVlanTag               = 0U;
        pstcMacInit->u16RxVlanHashTable         = 0U;
    }

    return i32Ret;
}

/**
 * @brief  Set MAC interface.
 * @param  [in] u32Interface            The media interface.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_IF_MII:       MII interface
 *           @arg ETH_MAC_IF_RMII:      RMII interface
 * @retval None
 */
void ETH_MAC_SetInterface(uint32_t u32Interface)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_MAC_IF(u32Interface));

    if (ETH_MAC_IF_RMII != u32Interface) {
        WRITE_REG32(bCM_ETH->MAC_IFCONFR_b.IFSEL, DISABLE);
    } else {
        WRITE_REG32(bCM_ETH->MAC_IFCONFR_b.IFSEL, ENABLE);
    }
}

/**
 * @brief  Set MAC duplex mode and speed.
 * @param  [in] u32Mode                 MAC duplex mode
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MAC_DUPLEX_MD_HALF:   Half duplex mode
 *           @arg ETH_MAC_DUPLEX_MD_FULL:   Full duplex mode
 * @param  [in] u32Speed                MAC speed
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MAC_SPEED_10M:    10Mbps
 *           @arg ETH_MAC_SPEED_100M:   100Mbps
 * @retval None
 */
void ETH_MAC_SetDuplexSpeed(uint32_t u32Mode, uint32_t u32Speed)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_MAC_DUPLEX_MD(u32Mode));
    DDL_ASSERT(IS_ETH_MAC_SPEED(u32Speed));

    MODIFY_REG32(CM_ETH->MAC_CONFIGR, (ETH_MAC_CONFIGR_FES | ETH_MAC_CONFIGR_DM), (u32Mode | u32Speed));
}

/**
 * @brief  Set MAC hash table.
 * @param  [in] u32HashHigh             Hash table high value.
 * @param  [in] u32HashLow              Hash table low value.
 * @retval None
 */
void ETH_MAC_SetHashTable(uint32_t u32HashHigh, uint32_t u32HashLow)
{
    WRITE_REG32(CM_ETH->MAC_HASHTLR, u32HashLow);
    WRITE_REG32(CM_ETH->MAC_HASHTHR, u32HashHigh);
}

/**
 * @brief  Set MAC Tx VLAN tag value.
 * @param  [in] u16TxTag                The tag value of Tx VLAN.
 * @retval None
 */
void ETH_MAC_SetTxVlanTagValue(uint16_t u16TxTag)
{
    MODIFY_REG32(CM_ETH->MAC_VTACTLR, ETH_MAC_VTACTLR_VLANV, u16TxTag);
}

/**
 * @brief  Set MAC Rx VLAN tag value.
 * @param  [in] u16RxTag                The tag value of Rx VLAN.
 * @retval None
 */
void ETH_MAC_SetRxVlanTagValue(uint16_t u16RxTag)
{
    MODIFY_REG32(CM_ETH->MAC_VTAFLTR, ETH_MAC_VTAFLTR_VLFLT, u16RxTag);
}

/**
 * @brief  Set MAC Rx VLAN hash table.
 * @param  [in] u16HashValue            The value of Rx VLAN hash table.
 * @retval None
 */
void ETH_MAC_SetRxVlanHashTable(uint16_t u16HashValue)
{
    WRITE_REG32(CM_ETH->MAC_VLAHTBR, u16HashValue);
}

/**
 * @brief  Enable or disable MAC loopback.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_MAC_LoopBackCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_ETH->MAC_CONFIGR_b.LM, enNewState);
}

/**
 * @brief  Enable or disable MAC Back Pressure.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_MAC_BackPressureCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_ETH->MAC_FLOCTLR_b.FCA_BPA, enNewState);
}

/**
 * @brief  Enable or disable MAC Transmit.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_MAC_TransCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_ETH->MAC_CONFIGR_b.TE, enNewState);
    DDL_DelayUS(300);
}

/**
 * @brief  Enable or disable MAC Receive.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_MAC_ReceiveCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_ETH->MAC_CONFIGR_b.RE, enNewState);
    DDL_DelayUS(300);
}

/**
 * @brief  Enable or disable MAC interrupt.
 * @param  [in] u32IntType              MAC interrupt source type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MAC_INT_TSPIM:    Time stamp trigger interrupt (on MAC)
 *           @arg ETH_MAC_INT_PMTIM:    PMT interrupt (on MAC)
 *           @arg ETH_MAC_INT_ALL:      All of the above
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_MAC_IntCmd(uint32_t u32IntType, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_MAC_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        CLR_REG32_BIT(CM_ETH->MAC_INTMSKR, u32IntType);
    } else {
        SET_REG32_BIT(CM_ETH->MAC_INTMSKR, u32IntType);
    }
}

/**
 * @brief  Get MAC interrupt status.
 * @param  [in] u32Flag                 MAC interrupt flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MAC_INT_FLAG_TSPIS:   Time stamp trigger flag (on MAC)
 *           @arg ETH_MAC_INT_FLAG_MMCTXIS: MMC transmit flag
 *           @arg ETH_MAC_INT_FLAG_MMCRXIS: MMC receive flag
 *           @arg ETH_MAC_INT_FLAG_MMCIS:   MMC flag (on MAC)
 *           @arg ETH_MAC_INT_FLAG_PMTIS:   PMT flag (on MAC)
 *           @arg ETH_MAC_INT_FLAG_ALL:     All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t ETH_MAC_GetIntStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_MAC_INT_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(CM_ETH->MAC_INTSTSR, u32Flag))) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/******************************************************************************/
/*                          MAC Address Functions                             */
/******************************************************************************/
/**
 * @brief  De-Initialize MAC Address.
 * @param  [in] u32Index                MAC address index.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDR_IDX0:    MAC address 0
 *           @arg ETH_MAC_ADDR_IDX1:    MAC address 1
 *           @arg ETH_MAC_ADDR_IDX2:    MAC address 2
 *           @arg ETH_MAC_ADDR_IDX3:    MAC address 3
 *           @arg ETH_MAC_ADDR_IDX4:    MAC address 4
 * @retval None
 */
void ETH_MACADDR_DeInit(uint32_t u32Index)
{
    __IO uint32_t *MACADHR;
    __IO uint32_t *MACADLR;
    uint32_t u32MacHigh = 0x0000FFFFUL;

    DDL_ASSERT(IS_ETH_MAC_ADDR_NORMAL_INDEX(u32Index));

    MACADHR = ETH_MAC_MACADHR_ADDR(u32Index);
    MACADLR = ETH_MAC_MACADLR_ADDR(u32Index);
    if (ETH_MAC_ADDR_IDX0 == u32Index) {
        u32MacHigh |= 0x80000000UL;
    }
    WRITE_REG32(*MACADHR, u32MacHigh);
    WRITE_REG32(*MACADLR, 0xFFFFFFFFUL);
}

/**
 * @brief  Initialize MAC Address.
 * @param  [in] u32Index                MAC address index.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDR_IDX0:    MAC address 0
 *           @arg ETH_MAC_ADDR_IDX1:    MAC address 1
 *           @arg ETH_MAC_ADDR_IDX2:    MAC address 2
 *           @arg ETH_MAC_ADDR_IDX3:    MAC address 3
 *           @arg ETH_MAC_ADDR_IDX4:    MAC address 4
 * @param  [in] pstcMacAddrInit         Pointer to a @ref stc_eth_mac_addr_config_t structure
 * @retval int32_t:
 *           - LL_OK: MAC Address Initialize success
 *           - LL_ERR_INVD_PARAM: pstcMacAddrInit == NULL
 */
int32_t ETH_MACADDR_Init(uint32_t u32Index, const stc_eth_mac_addr_config_t *pstcMacAddrInit)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t *MACADHR;
    __IO uint32_t *MACADLR;
    uint32_t u32TempReg;
    uint32_t *pu32AddrLow;

    if (NULL == pstcMacAddrInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_MAC_ADDR_NORMAL_INDEX(u32Index));
        DDL_ASSERT(IS_ETH_MAC_ADDR_FILTER(pstcMacAddrInit->u32MacAddrFilter));
        DDL_ASSERT(IS_ETH_MAC_ADDR_MASK(pstcMacAddrInit->u32MacAddrMask));

        MACADHR = ETH_MAC_MACADHR_ADDR(u32Index);
        MACADLR = ETH_MAC_MACADLR_ADDR(u32Index);
        /* Set MAC address high register */
        u32TempReg = ((uint32_t)pstcMacAddrInit->au8MacAddr[5] << 8U) | (uint32_t)pstcMacAddrInit->au8MacAddr[4];
        if (ETH_MAC_ADDR_IDX0 != u32Index) {
            u32TempReg |= pstcMacAddrInit->u32MacAddrFilter | pstcMacAddrInit->u32MacAddrMask;
        }
        WRITE_REG32(*MACADHR, u32TempReg);
        /* Set MAC address low register */
        pu32AddrLow = (uint32_t *)((uint32_t) & (pstcMacAddrInit->au8MacAddr[0]));
        WRITE_REG32(*MACADLR, *pu32AddrLow);
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_eth_mac_addr_config_t to default values.
 * @param  [out] pstcMacAddrInit        Pointer to a @ref stc_eth_mac_addr_config_t structure
 * @retval int32_t:
 *           - LL_OK: Structure Initialize success
 *           - LL_ERR_INVD_PARAM: pstcMacAddrInit == NULL
 */
int32_t ETH_MACADDR_StructInit(stc_eth_mac_addr_config_t *pstcMacAddrInit)
{
    int32_t i32Ret = LL_OK;
    uint8_t i;

    if (NULL == pstcMacAddrInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcMacAddrInit->u32MacAddrFilter = ETH_MAC_ADDR_FILTER_DISABLE;
        pstcMacAddrInit->u32MacAddrMask   = ETH_MAC_ADDR_MASK_DISABLE;
        for (i = 0U; i < ETH_MAC_ADDR_BYTE_LEN; i++) {
            pstcMacAddrInit->au8MacAddr[i] = 0x00U;
        }
    }

    return i32Ret;
}

/**
 * @brief  Set MAC Address.
 * @param  [in] u32Index                MAC address index.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDR_IDX0:    MAC address 0
 *           @arg ETH_MAC_ADDR_IDX1:    MAC address 1
 *           @arg ETH_MAC_ADDR_IDX2:    MAC address 2
 *           @arg ETH_MAC_ADDR_IDX3:    MAC address 3
 *           @arg ETH_MAC_ADDR_IDX4:    MAC address 4
 * @param  [in] au8Addr                 Pointer to MAC address buffer(6 bytes).
 * @retval int32_t:
 *           - LL_OK: Set address success
 *           - LL_ERR_INVD_PARAM: au8Addr == NULL
 */
int32_t ETH_MACADDR_SetAddr(uint32_t u32Index, uint8_t au8Addr[])
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t *MACADHR;
    __IO uint32_t *MACADLR;
    uint32_t u32TempReg;
    uint32_t *pu32AddrLow;

    if (NULL == au8Addr) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_MAC_ADDR_NORMAL_INDEX(u32Index));

        MACADHR = ETH_MAC_MACADHR_ADDR(u32Index);
        MACADLR = ETH_MAC_MACADLR_ADDR(u32Index);
        /* Set MAC address high register */
        u32TempReg = ((uint32_t)au8Addr[5] << 8U) | (uint32_t)au8Addr[4];
        WRITE_REG32(*MACADHR, u32TempReg);
        /* Set MAC address low register */
        pu32AddrLow = (uint32_t *)((uint32_t) & (au8Addr[0]));
        WRITE_REG32(*MACADLR, *pu32AddrLow);
    }

    return i32Ret;
}

/**
 * @brief  Get MAC Address.
 * @param  [in] u32Index                MAC address index.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDR_IDX0:    MAC address 0
 *           @arg ETH_MAC_ADDR_IDX1:    MAC address 1
 *           @arg ETH_MAC_ADDR_IDX2:    MAC address 2
 *           @arg ETH_MAC_ADDR_IDX3:    MAC address 3
 *           @arg ETH_MAC_ADDR_IDX4:    MAC address 4
 * @param  [out] au8Addr                Pointer to MAC address buffer(6 bytes).
 * @retval int32_t:
 *           - LL_OK: Set address success
 *           - LL_ERR_INVD_PARAM: au8Addr == NULL
 */
int32_t ETH_MACADDR_GetAddr(uint32_t u32Index, uint8_t au8Addr[])
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t *MACADHR;
    __IO uint32_t *MACADLR;
    uint32_t u32TempReg;
    uint32_t *pu32AddrLow;

    if (NULL == au8Addr) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_MAC_ADDR_NORMAL_INDEX(u32Index));

        MACADHR    = ETH_MAC_MACADHR_ADDR(u32Index);
        MACADLR    = ETH_MAC_MACADLR_ADDR(u32Index);
        /* Get MAC address high */
        u32TempReg = READ_REG32(*MACADHR);
        au8Addr[5] = (uint8_t)((u32TempReg >> 8U) & 0x000000FFUL);
        au8Addr[4] = (uint8_t)(u32TempReg & 0x000000FFUL);
        /* Get MAC address low */
        pu32AddrLow = (uint32_t *)((uint32_t) & (au8Addr[0]));
        *pu32AddrLow = READ_REG32(*MACADLR);
    }

    return i32Ret;
}

/**
 * @brief  Set MAC Address filter mode.
 * @param  [in] u32Index                MAC address index.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDR_IDX1:    MAC address 1
 *           @arg ETH_MAC_ADDR_IDX2:    MAC address 2
 *           @arg ETH_MAC_ADDR_IDX3:    MAC address 3
 *           @arg ETH_MAC_ADDR_IDX4:    MAC address 4
 * @param  [in] u32Mode                 MAC address filter mode.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDR_FILTER_DISABLE:              Disable perfect filter with MAC address.
 *           @arg ETH_MAC_ADDR_FILTER_PERFECT_DEST_ADDR:    Filter the DA address of the received frame with MAC address.
 *           @arg ETH_MAC_ADDR_FILTER_PERFECT_SRC_ADDR:     Filter the SA address of the received frame with MAC address.
 * @retval None
 */
void ETH_MACADDR_SetFilterMode(uint32_t u32Index, uint32_t u32Mode)
{
    __IO uint32_t *MACADHR;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_MAC_ADDR_SPEC_INDEX(u32Index));
    DDL_ASSERT(IS_ETH_MAC_ADDR_FILTER(u32Mode));

    MACADHR = ETH_MAC_MACADHR_ADDR(u32Index);
    MODIFY_REG32(*MACADHR, (ETH_MAC_MACADHR1_SA1 | ETH_MAC_MACADHR1_AE1), u32Mode);
}

/**
 * @brief  Set MAC Address Transmit priority ratio.
 * @param  [in] u32Index                MAC address index.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDR_IDX1:    MAC address 1
 *           @arg ETH_MAC_ADDR_IDX2:    MAC address 2
 *           @arg ETH_MAC_ADDR_IDX3:    MAC address 3
 *           @arg ETH_MAC_ADDR_IDX4:    MAC address 4
 * @param  [in] u32Mask                 MAC address filter mask.
 *         This parameter can be one of the following values or any combination of BYTE1 through BYTE6:
 *           @arg ETH_MAC_ADDR_MASK_DISABLE: Disable MAC Address Mask
 *           @arg ETH_MAC_ADDR_MASK_BYTE6:   Mask MAC Address high reg bits [15:8]
 *           @arg ETH_MAC_ADDR_MASK_BYTE5:   Mask MAC Address high reg bits [7:0]
 *           @arg ETH_MAC_ADDR_MASK_BYTE4:   Mask MAC Address low reg bits [31:24]
 *           @arg ETH_MAC_ADDR_MASK_BYTE3:   Mask MAC Address low reg bits [23:16]
 *           @arg ETH_MAC_ADDR_MASK_BYTE2:   Mask MAC Address low reg bits [15:8]
 *           @arg ETH_MAC_ADDR_MASK_BYTE1:   Mask MAC Address low reg bits [7:0]
 *           @arg ETH_MAC_ADDR_MASK_ALL:     Mask MAC Address low reg bits [31:0] and low high bits [15:0]
 * @retval None
 */
void ETH_MACADDR_SetFilterMask(uint32_t u32Index, uint32_t u32Mask)
{
    __IO uint32_t *MACADHR;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_MAC_ADDR_SPEC_INDEX(u32Index));
    DDL_ASSERT(IS_ETH_MAC_ADDR_MASK(u32Mask));

    MACADHR = ETH_MAC_MACADHR_ADDR(u32Index);
    MODIFY_REG32(*MACADHR, ETH_MAC_MACADHR1_MBC1, u32Mask);
}

/******************************************************************************/
/*                        MAC L3L4 Filter Functions                           */
/******************************************************************************/
/**
 * @brief  De-Initialize MAC L3L4 Filter.
 * @param  None
 * @retval None
 */
void ETH_MAC_L3L4FilterDeInit(void)
{
    WRITE_REG32(bCM_ETH->MAC_FLTCTLR_b.IPFE, DISABLE);
    WRITE_REG32(CM_ETH->MAC_L34CTLR,  0UL);
    WRITE_REG32(CM_ETH->MAC_L4PORTR,  0UL);
    WRITE_REG32(CM_ETH->MAC_L3ADDRR0, 0UL);
    WRITE_REG32(CM_ETH->MAC_L3ADDRR1, 0UL);
    WRITE_REG32(CM_ETH->MAC_L3ADDRR2, 0UL);
    WRITE_REG32(CM_ETH->MAC_L3ADDRR3, 0UL);
}

/**
 * @brief  Initialize MAC L3L4 Filter.
 * @param  [in] pstcL3L4FilterInit      Pointer to a @ref stc_eth_l3l4_filter_config_t structure
 * @retval int32_t:
 *           - LL_OK: MAC L3L4 Filter Initialize success
 *           - LL_ERR_INVD_PARAM: pstcL3L4FilterInit == NULL
 */
int32_t ETH_MAC_L3L4FilterInit(const stc_eth_l3l4_filter_config_t *pstcL3L4FilterInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcL3L4FilterInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_MAC_L4_DEST_PORT_FILTER(pstcL3L4FilterInit->u32DestPortFilter));
        DDL_ASSERT(IS_ETH_MAC_L4_SRC_PORT_FILTER(pstcL3L4FilterInit->u32SrcPortFilter));
        DDL_ASSERT(IS_ETH_MAC_L4_PORT_FILTER_PROTOCOL(pstcL3L4FilterInit->u32PortFilterProtocol));
        DDL_ASSERT(IS_ETH_MAC_L3_DEST_ADDR_FILTER_MASK(pstcL3L4FilterInit->u32Ip4DestAddrFilterMask));
        DDL_ASSERT(IS_ETH_MAC_L3_SRC_ADDR_FILTER_MASK(pstcL3L4FilterInit->u32Ip4SrcAddrFilterMask));
        DDL_ASSERT(IS_ETH_MAC_L3_DEST_SRC_ADDR_FILTER_MASK(pstcL3L4FilterInit->u32Ip6AddrFilterMask));
        DDL_ASSERT(IS_ETH_MAC_L3_DEST_ADDR_FILTER(pstcL3L4FilterInit->u32DestAddrFilter));
        DDL_ASSERT(IS_ETH_MAC_L3_SRC_ADDR_FILTER(pstcL3L4FilterInit->u32SrcAddrFilter));
        DDL_ASSERT(IS_ETH_MAC_L3_ADDR_FILTER_PROTOCOL(pstcL3L4FilterInit->u32AddrFilterProtocol));

        /* Set L3/L4 control register */
        if (ETH_MAC_L3_ADDR_FILTER_PROTOCOL_IPV4 != pstcL3L4FilterInit->u32AddrFilterProtocol) {
            WRITE_REG32(CM_ETH->MAC_L34CTLR,
                        (pstcL3L4FilterInit->u32DestPortFilter     | pstcL3L4FilterInit->u32SrcPortFilter     |
                         pstcL3L4FilterInit->u32PortFilterProtocol | pstcL3L4FilterInit->u32Ip6AddrFilterMask |
                         pstcL3L4FilterInit->u32DestAddrFilter     | pstcL3L4FilterInit->u32SrcAddrFilter     |
                         pstcL3L4FilterInit->u32AddrFilterProtocol));
            WRITE_REG32(CM_ETH->MAC_L3ADDRR0, pstcL3L4FilterInit->au32Ip6AddrFilterValue[0]);
            WRITE_REG32(CM_ETH->MAC_L3ADDRR1, pstcL3L4FilterInit->au32Ip6AddrFilterValue[1]);
            WRITE_REG32(CM_ETH->MAC_L3ADDRR2, pstcL3L4FilterInit->au32Ip6AddrFilterValue[2]);
            WRITE_REG32(CM_ETH->MAC_L3ADDRR3, pstcL3L4FilterInit->au32Ip6AddrFilterValue[3]);
        } else {    /* IPv4 protocol*/
            WRITE_REG32(CM_ETH->MAC_L34CTLR,
                        (pstcL3L4FilterInit->u32DestPortFilter       | pstcL3L4FilterInit->u32SrcPortFilter         |
                         pstcL3L4FilterInit->u32PortFilterProtocol   | pstcL3L4FilterInit->u32Ip4DestAddrFilterMask |
                         pstcL3L4FilterInit->u32Ip4SrcAddrFilterMask | pstcL3L4FilterInit->u32DestAddrFilter        |
                         pstcL3L4FilterInit->u32SrcAddrFilter        | pstcL3L4FilterInit->u32AddrFilterProtocol));
            WRITE_REG32(CM_ETH->MAC_L3ADDRR0, pstcL3L4FilterInit->u32Ip4SrcAddrFilterValue);
            WRITE_REG32(CM_ETH->MAC_L3ADDRR1, pstcL3L4FilterInit->u32Ip4DestAddrFilterValue);
        }
        WRITE_REG32(CM_ETH->MAC_L4PORTR, ((((uint32_t)pstcL3L4FilterInit->u16DestProtFilterValue) <<
                                           ETH_MAC_L4PORTR_L4DPVAL_POS) | pstcL3L4FilterInit->u16SrcProtFilterValue));
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_eth_l3l4_filter_config_t to default values.
 * @param  [out] pstcL3L4FilterInit     Pointer to a @ref stc_eth_l3l4_filter_config_t structure
 * @retval int32_t:
 *           - LL_OK: Structure Initialize success
 *           - LL_ERR_INVD_PARAM: pstcL3L4FilterInit == NULL
 */
int32_t ETH_MAC_L3L4FilterStructInit(stc_eth_l3l4_filter_config_t *pstcL3L4FilterInit)
{
    int32_t i32Ret = LL_OK;
    uint8_t i;

    if (NULL == pstcL3L4FilterInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcL3L4FilterInit->u32DestPortFilter           = ETH_MAC_L4_DEST_PORT_FILTER_DISABLE;
        pstcL3L4FilterInit->u32SrcPortFilter            = ETH_MAC_L4_SRC_PORT_FILTER_DISABLE;
        pstcL3L4FilterInit->u32PortFilterProtocol       = ETH_MAC_L4_PORT_FILTER_PROTOCOL_TCP;
        pstcL3L4FilterInit->u32Ip4DestAddrFilterMask    = ETH_MAC_L3_DEST_ADDR_FILTER_MASK_NONE;
        pstcL3L4FilterInit->u32Ip4SrcAddrFilterMask     = ETH_MAC_L3_SRC_ADDR_FILTER_MASK_NONE;
        pstcL3L4FilterInit->u32Ip6AddrFilterMask        = ETH_MAC_L3_DEST_SRC_ADDR_FILTER_MASK_NONE;
        pstcL3L4FilterInit->u32DestAddrFilter           = ETH_MAC_L3_DEST_ADDR_FILTER_DISABLE;
        pstcL3L4FilterInit->u32SrcAddrFilter            = ETH_MAC_SRC_ADDR_FILTER_DISABLE;
        pstcL3L4FilterInit->u32AddrFilterProtocol       = ETH_MAC_L3_ADDR_FILTER_PROTOCOL_IPV4;
        pstcL3L4FilterInit->u16DestProtFilterValue      = 0U;
        pstcL3L4FilterInit->u16SrcProtFilterValue       = 0U;
        pstcL3L4FilterInit->u32Ip4DestAddrFilterValue   = 0UL;
        pstcL3L4FilterInit->u32Ip4SrcAddrFilterValue    = 0UL;
        for (i = 0U; i < 4U; i++) {
            pstcL3L4FilterInit->au32Ip6AddrFilterValue[i] = 0UL;
        }
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable MAC L3L4 Filter function.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_MAC_L3L4FilterCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_ETH->MAC_FLTCTLR_b.IPFE, enNewState);
}

/**
 * @brief  Set L4 port filter protocol.
 * @param  [in] u32Protocol             MAC L4 port filter protocol.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_L4_PORT_FILTER_PROTOCOL_TCP:  Port filter for TCP frame
 *           @arg ETH_MAC_L4_PORT_FILTER_PROTOCOL_UDP:  Port filter for UDP frame
 * @retval None
 */
void ETH_MAC_SetPortFilterProtocol(uint32_t u32Protocol)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_MAC_L4_PORT_FILTER_PROTOCOL(u32Protocol));

    WRITE_REG32(bCM_ETH->MAC_L34CTLR_b.L4PEN, (u32Protocol >> ETH_MAC_L34CTLR_L4PEN_POS));
}

/**
 * @brief  Set L4 Destination port filter value.
 * @param  [in] u16Port                 The value of Destination port.
 * @retval None
 */
void ETH_MAC_SetDestPortFilterValue(uint16_t u16Port)
{
    MODIFY_REG32(CM_ETH->MAC_L4PORTR, ETH_MAC_L4PORTR_L4DPVAL, ((uint32_t)u16Port << 16U));
}

/**
 * @brief  Set L4 Source port filter value.
 * @param  [in] u16Port                 The value of Source port.
 * @retval None
 */
void ETH_MAC_SetSrcPortFilterValue(uint16_t u16Port)
{
    MODIFY_REG32(CM_ETH->MAC_L4PORTR, ETH_MAC_L4PORTR_L4SPVAL, u16Port);
}

/**
 * @brief  Set L3 address filter protocol.
 * @param  [in] u32Protocol             MAC L3 address filter protocol.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_L3_ADDR_FILTER_PROTOCOL_IPV4: Ip Address filter for IPv4
 *           @arg ETH_MAC_L3_ADDR_FILTER_PROTOCOL_IPV6: Ip Address filter for IPv6
 * @retval None
 */
void ETH_MAC_SetAddrFilterProtocol(uint32_t u32Protocol)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_MAC_L3_ADDR_FILTER_PROTOCOL(u32Protocol));

    WRITE_REG32(bCM_ETH->MAC_L34CTLR_b.L3PEN, u32Protocol);
}

/**
 * @brief  Set L3 Destination address filter value of IPv4.
 * @param  [in] u32Addr                 The value of Destination address.
 * @retval None
 */
void ETH_MAC_SetIpv4DestAddrFilterValue(uint32_t u32Addr)
{
    WRITE_REG32(CM_ETH->MAC_L3ADDRR1, u32Addr);
}

/**
 * @brief  Set L3 Source address filter value of IPv4.
 * @param  [in] u32Addr                 The value of Source address.
 * @retval None
 */
void ETH_MAC_SetIpv4SrcAddrFilterValue(uint32_t u32Addr)
{
    WRITE_REG32(CM_ETH->MAC_L3ADDRR0, u32Addr);
}

/**
 * @brief  Set L3 Destination/Source Address filter value of IPv6.
 * @param  [in] au32Addr                Pointer to Destination/Source Address buffer(4 words).
 * @retval int32_t:
 *           - LL_OK: Set Address filter value success
 *           - LL_ERR_INVD_PARAM: au32Addr == NULL
 */
int32_t ETH_MAC_SetIpv6AddrFilterValue(const uint32_t au32Addr[])
{
    int32_t i32Ret = LL_OK;

    if (NULL == au32Addr) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        WRITE_REG32(CM_ETH->MAC_L3ADDRR0, au32Addr[0]);
        WRITE_REG32(CM_ETH->MAC_L3ADDRR1, au32Addr[1]);
        WRITE_REG32(CM_ETH->MAC_L3ADDRR2, au32Addr[2]);
        WRITE_REG32(CM_ETH->MAC_L3ADDRR3, au32Addr[3]);
    }

    return i32Ret;
}

/******************************************************************************/
/*                              DMA Functions                                 */
/******************************************************************************/
/**
 * @brief  De-Initialize DMA.
 * @param  None
 * @retval None
 */
void ETH_DMA_DeInit(void)
{
    WRITE_REG32(CM_ETH->DMA_BUSMODR, 0x00020101UL);
    WRITE_REG32(CM_ETH->DMA_OPRMODR, 0U);
    WRITE_REG32(CM_ETH->DMA_INTENAR, 0U);
    WRITE_REG32(CM_ETH->DMA_REVWDTR, 0U);
    WRITE_REG32(CM_ETH->DMA_TXDLADR, 0U);
    WRITE_REG32(CM_ETH->DMA_RXDLADR, 0U);
}

/**
 * @brief  Initialize DMA.
 * @param  [in] pstcDmaInit             Pointer to a @ref stc_eth_dma_init_t structure
 * @retval int32_t:
 *           - LL_OK: DMA Initialize success
 *           - LL_ERR_INVD_PARAM: pstcDmaInit == NULL
 */
int32_t ETH_DMA_Init(const stc_eth_dma_init_t *pstcDmaInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcDmaInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMA_BURST_MD(pstcDmaInit->u32BurstMode));
        DDL_ASSERT(IS_ETH_DMA_ADDR_ALIGN(pstcDmaInit->u32AddrAlign));
        DDL_ASSERT(IS_ETH_DMA_RX_BURST_LEN(pstcDmaInit->u32RxBurstLen));
        DDL_ASSERT(IS_ETH_DMA_TX_BURST_LEN(pstcDmaInit->u32TxBurstLen));
        DDL_ASSERT(IS_ETH_DMA_ENHANCE_DESC(pstcDmaInit->u32EnhanceDesc));
        DDL_ASSERT(IS_ETH_DMA_DESC_SKIP_LEN(pstcDmaInit->u32DescSkipLen));
        DDL_ASSERT(IS_ETH_DMA_PRIO_ARBITRATION(pstcDmaInit->u32Arbitration));
        DDL_ASSERT(IS_ETH_DMA_DROP_CHECKSUM_ERR_FRAME(pstcDmaInit->u32DropChecksumErrorFrame));
        DDL_ASSERT(IS_ETH_DMA_RX_STORE_FORWARD(pstcDmaInit->u32ReceiveStoreForward));
        DDL_ASSERT(IS_ETH_DMA_FLUSH_RX_FRAME(pstcDmaInit->u32FlushReceiveFrame));
        DDL_ASSERT(IS_ETH_DMA_TRANS_STORE_FORWARD(pstcDmaInit->u32TransStoreForward));
        DDL_ASSERT(IS_ETH_DMA_TRANS_THRESHOLD(pstcDmaInit->u32TransThreshold));
        DDL_ASSERT(IS_ETH_DMA_FORWARD_ERR_FRAME(pstcDmaInit->u32ForwardErrorFrame));
        DDL_ASSERT(IS_ETH_DMA_FORWARD_UNDERSIZE_FRAME(pstcDmaInit->u32ForwardUndersizeFrame));
        DDL_ASSERT(IS_ETH_DMA_DROP_JUMBO_FRAME(pstcDmaInit->u32DropJumboFrame));
        DDL_ASSERT(IS_ETH_DMA_RX_THRESHOLD(pstcDmaInit->u32ReceiveThreshold));
        DDL_ASSERT(IS_ETH_DMA_SEC_FRAME_OPERA(pstcDmaInit->u32SecFrameOperate));

        /* Set Bus mode register */
        MODIFY_REG32(CM_ETH->DMA_BUSMODR, ETH_DMA_BUSMODR_CLR_MASK,
                     (pstcDmaInit->u32BurstMode   | pstcDmaInit->u32AddrAlign   | pstcDmaInit->u32RxBurstLen  |
                      pstcDmaInit->u32TxBurstLen  | pstcDmaInit->u32EnhanceDesc | pstcDmaInit->u32DescSkipLen |
                      pstcDmaInit->u32Arbitration | ETH_DMA_BUSMODR_SPBL));
        /* Set Operation mode register */
        MODIFY_REG32(CM_ETH->DMA_OPRMODR, ETH_DMA_OPRMODR_CLR_MASK,
                     (pstcDmaInit->u32DropChecksumErrorFrame | pstcDmaInit->u32ReceiveStoreForward |
                      pstcDmaInit->u32FlushReceiveFrame      | pstcDmaInit->u32TransStoreForward   |
                      pstcDmaInit->u32TransThreshold         | pstcDmaInit->u32ForwardErrorFrame   |
                      pstcDmaInit->u32ForwardUndersizeFrame  | pstcDmaInit->u32DropJumboFrame      |
                      pstcDmaInit->u32ReceiveThreshold       | pstcDmaInit->u32SecFrameOperate));
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_eth_dma_init_t to default values.
 * @param  [out] pstcDmaInit            Pointer to a @ref stc_eth_dma_init_t structure
 * @retval int32_t:
 *           - LL_OK: Structure Initialize success
 *           - LL_ERR_INVD_PARAM: pstcDmaInit == NULL
 */
int32_t ETH_DMA_StructInit(stc_eth_dma_init_t *pstcDmaInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcDmaInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcDmaInit->u32BurstMode               = ETH_DMA_BURST_MD_FIXED;
        pstcDmaInit->u32AddrAlign               = ETH_DMA_ADDR_ALIGN_ENABLE;
        pstcDmaInit->u32RxBurstLen              = ETH_DMA_RX_BURST_LEN_32BEAT;
        pstcDmaInit->u32TxBurstLen              = ETH_DMA_TX_BURST_LEN_32BEAT;
        pstcDmaInit->u32EnhanceDesc             = ETH_DMA_ENHANCE_DESC_ENABLE;
        pstcDmaInit->u32DescSkipLen             = 0U;
        pstcDmaInit->u32Arbitration             = ETH_DMA_ARBITRATION_LOOP_RXTX_1_1;
        pstcDmaInit->u32DropChecksumErrorFrame  = ETH_DMA_DROP_CHECKSUM_ERR_FRAME_ENABLE;
        pstcDmaInit->u32ReceiveStoreForward     = ETH_DMA_RX_STORE_FORWARD_ENABLE;
        pstcDmaInit->u32FlushReceiveFrame       = ETH_DMA_FLUSH_RX_FRAME_ENABLE;
        pstcDmaInit->u32TransStoreForward       = ETH_DMA_TRANS_STORE_FORWARD_ENABLE;
        pstcDmaInit->u32TransThreshold          = ETH_DMA_TRANS_THRESHOLD_64BYTE;
        pstcDmaInit->u32ForwardErrorFrame       = ETH_DMA_FORWARD_ERR_FRAME_DISABLE;
        pstcDmaInit->u32ForwardUndersizeFrame   = ETH_DMA_FORWARD_UNDERSIZE_FRAME_DISABLE;
        pstcDmaInit->u32DropJumboFrame          = ETH_DMA_DROP_JUMBO_FRAME_DISABLE;
        pstcDmaInit->u32ReceiveThreshold        = ETH_DMA_RX_THRESHOLD_64BYTE;
        pstcDmaInit->u32SecFrameOperate         = ETH_DMA_SEC_FRAME_OPERA_ENABLE;
    }

    return i32Ret;
}

/**
 * @brief  Set DMA software reset.
 * @param  None
 * @retval int32_t:
 *           - LL_OK: Software reset success
 *           - LL_ERR_TIMEOUT: Reset timeout
 */
int32_t ETH_DMA_SoftwareReset(void)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_OK;

    WRITE_REG32(bCM_ETH->DMA_BUSMODR_b.SWR, 1U);
    u32Count = ETH_SW_RST_TIMEOUT * (HCLK_VALUE / 20000UL);
    while (0UL != READ_REG32(bCM_ETH->DMA_BUSMODR_b.SWR)) {
        if (0UL == u32Count) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
        u32Count--;
    }

    return i32Ret;
}

/**
 * @brief  Set DMA Transmit priority ratio.
 * @param  [in] u32Ratio                Priority ratio
 *         This parameter can be one of the following values:
 *           @arg ETH_DMA_ARBITRATION_LOOP_RXTX_1_1:        Rx:Tx = 1:1
 *           @arg ETH_DMA_ARBITRATION_LOOP_RXTX_2_1:        Rx:Tx = 2:1
 *           @arg ETH_DMA_ARBITRATION_LOOP_RXTX_3_1:        Rx:Tx = 3:1
 *           @arg ETH_DMA_ARBITRATION_LOOP_RXTX_4_1:        Rx:Tx = 4:1
 *           @arg ETH_DMA_ARBITRATION_LOOP_TXRX_1_1:        Tx:Rx = 1:1
 *           @arg ETH_DMA_ARBITRATION_LOOP_TXRX_2_1:        Tx:Rx = 2:1
 *           @arg ETH_DMA_ARBITRATION_LOOP_TXRX_3_1:        Tx:Rx = 3:1
 *           @arg ETH_DMA_ARBITRATION_LOOP_TXRX_4_1:        Tx:Rx = 4:1
 *           @arg ETH_DMA_ARBITRATION_FIXED_RX_PRIOR_TX:    Fixed priority: Rx is higher than Tx
 *           @arg ETH_DMA_ARBITRATION_FIXED_TX_PRIOR_RX:    Fixed priority: Tx is higher than Rx
 * @retval None
 */
void ETH_DMA_SetTransPriorityRatio(uint32_t u32Ratio)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_DMA_PRIO_ARBITRATION(u32Ratio));

    MODIFY_REG32(CM_ETH->DMA_BUSMODR, (ETH_DMA_BUSMODR_TXPR | ETH_DMA_BUSMODR_PRAT | ETH_DMA_BUSMODR_DMAA), u32Ratio);
}

/**
 * @brief  Set DMA Rx watchdog counter.
 * @param  [in] u8Value                 The value of Watchdog timer
 * @retval None
 */
void ETH_DMA_SetRxWatchdogCounter(uint8_t u8Value)
{
    WRITE_REG32(CM_ETH->DMA_REVWDTR, u8Value);
}

/**
 * @brief  Flush transmit FIFO.
 * @param  None
 * @retval int32_t:
 *           - LL_OK: Flush transmit FIFO success
 *           - LL_ERR_TIMEOUT: Flush timeout
 */
int32_t ETH_DMA_FlushTransFIFO(void)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_OK;

    WRITE_REG32(bCM_ETH->DMA_OPRMODR_b.FTF, 1U);
    u32Count = ETH_WR_REG_TIMEOUT * (HCLK_VALUE / 20000UL);
    while (0UL != READ_REG32(bCM_ETH->DMA_OPRMODR_b.FTF)) {
        if (0UL == u32Count) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
        u32Count--;
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable DMA transmit.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_DMA_TransCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_ETH->DMA_OPRMODR_b.STT, enNewState);
    DDL_DelayUS(300);
}

/**
 * @brief  Enable or disable DMA receive.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_DMA_ReceiveCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_ETH->DMA_OPRMODR_b.STR, enNewState);
    DDL_DelayUS(300);
}

/**
 * @brief  Enable or disable DMA interrupt.
 * @param  [in] u32IntType              DMA interrupt source
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_DMA_INT_NIE:      Normal interrupt summary
 *           @arg ETH_DMA_INT_AIE:      Abnormal interrupt summary
 *           @arg ETH_DMA_INT_ERE:      Early receive interrupt
 *           @arg ETH_DMA_INT_FBE:      Fatal bus error interrupt
 *           @arg ETH_DMA_INT_ETE:      Early transmit interrupt
 *           @arg ETH_DMA_INT_RWE:      Receive watchdog timeout interrupt
 *           @arg ETH_DMA_INT_RSE:      Receive process stopped interrupt
 *           @arg ETH_DMA_INT_RUE:      Receive buffer unavailable interrupt
 *           @arg ETH_DMA_INT_RIE:      Receive interrupt
 *           @arg ETH_DMA_INT_UNE:      Transmit Underflow interrupt
 *           @arg ETH_DMA_INT_OVE:      Receive Overflow interrupt
 *           @arg ETH_DMA_INT_TJE:      Transmit jabber timeout interrupt
 *           @arg ETH_DMA_INT_TUE:      Transmit buffer unavailable interrupt
 *           @arg ETH_DMA_INT_TSE:      Transmit process stopped interrupt
 *           @arg ETH_DMA_INT_TIE:      Transmit interrupt
 *           @arg ETH_DMA_INT_ALL:      All of the above
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_DMA_IntCmd(uint32_t u32IntType, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_DMA_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        SET_REG32_BIT(CM_ETH->DMA_INTENAR, u32IntType);
    } else {
        CLR_REG32_BIT(CM_ETH->DMA_INTENAR, u32IntType);
    }
}

/**
 * @brief  Get DMA flag status.
 * @param  [in] u32Flag                 DMA flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_DMA_FLAG_PTPS:    Time-stamp trigger status
 *           @arg ETH_DMA_FLAG_PMTS:    PMT trigger status
 *           @arg ETH_DMA_FLAG_MMCS:    MMC trigger status
 *           @arg ETH_DMA_FLAG_NIS:     Normal interrupt summary flag
 *           @arg ETH_DMA_FLAG_AIS:     Abnormal interrupt summary flag
 *           @arg ETH_DMA_FLAG_ERS:     Early receive flag
 *           @arg ETH_DMA_FLAG_FBS:     Fatal bus error flag
 *           @arg ETH_DMA_FLAG_ETS:     Early transmit flag
 *           @arg ETH_DMA_FLAG_RWS:     Receive watchdog timeout flag
 *           @arg ETH_DMA_FLAG_RSS:     Receive stopped flag
 *           @arg ETH_DMA_FLAG_RUS:     Receive buffer unavailable flag
 *           @arg ETH_DMA_FLAG_RIS:     Receive flag
 *           @arg ETH_DMA_FLAG_UNS:     Transmit Underflow flag
 *           @arg ETH_DMA_FLAG_OVS:     Receive Overflow flag
 *           @arg ETH_DMA_FLAG_TJS:     Transmit jabber timeout flag
 *           @arg ETH_DMA_FLAG_TUS:     Transmit buffer unavailable flag
 *           @arg ETH_DMA_FLAG_TSS:     Transmit stopped flag
 *           @arg ETH_DMA_FLAG_TIS:     Transmit interrupt flag
 *           @arg ETH_DMA_FLAG_ALL:     All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t ETH_DMA_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_DMA_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(CM_ETH->DMA_DMASTSR, u32Flag))) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/**
 * @brief  Clear DMA flag.
 * @param  [in] u32Flag                 DMA flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_DMA_FLAG_NIS:     Normal interrupt summary flag
 *           @arg ETH_DMA_FLAG_AIS:     Abnormal interrupt summary flag
 *           @arg ETH_DMA_FLAG_ERS:     Early receive flag
 *           @arg ETH_DMA_FLAG_FBS:     Fatal bus error flag
 *           @arg ETH_DMA_FLAG_ETS:     Early transmit flag
 *           @arg ETH_DMA_FLAG_RWS:     Receive watchdog timeout flag
 *           @arg ETH_DMA_FLAG_RSS:     Receive stopped flag
 *           @arg ETH_DMA_FLAG_RUS:     Receive buffer unavailable flag
 *           @arg ETH_DMA_FLAG_RIS:     Receive flag
 *           @arg ETH_DMA_FLAG_UNS:     Transmit Underflow flag
 *           @arg ETH_DMA_FLAG_OVS:     Receive Overflow flag
 *           @arg ETH_DMA_FLAG_TJS:     Transmit jabber timeout flag
 *           @arg ETH_DMA_FLAG_TUS:     Transmit buffer unavailable flag
 *           @arg ETH_DMA_FLAG_TSS:     Transmit stopped flag
 *           @arg ETH_DMA_FLAG_TIS:     Transmit interrupt flag
 *           @arg ETH_DMA_FLAG_CLR_ALL: All of the above
 * @retval None
 */
void ETH_DMA_ClearStatus(uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_DMA_CLR_FLAG(u32Flag));

    WRITE_REG32(CM_ETH->DMA_DMASTSR, u32Flag);
}

/**
 * @brief  Get DMA overflow flag status.
 * @param  [in] u32Flag                 DMA overflow flag type
 *         This parameter can be one of the following values:
 *           @arg ETH_DMA_OVF_RXFIFO_CNT:       Overflow bit for FIFO overflow counter
 *           @arg ETH_DMA_OVF_MISS_FRAME_CNT:   Overflow bit for miss frame counter
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t ETH_DMA_GetOvfStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_DMA_MISS_FRAME_TYPE(u32Flag));

    if (0UL != (READ_REG32_BIT(CM_ETH->DMA_RFRCNTR, u32Flag))) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/******************************************************************************/
/*                          DMA descriptor Functions                          */
/******************************************************************************/
/**
 * @brief  Initializes DMA Tx descriptor in chain mode.
 * @param  [in] pstcEthHandle           Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] astcTxDescTab           Pointer to the first Tx desc list
 * @param  [in] au8TxBuf                Pointer to the first TxBuffer list
 * @param  [in] u32TxBufCnt             Number of the Tx desc in the list
 * @retval int32_t:
 *           - LL_OK: Initializes Tx chain mode success
 *           - LL_ERR_INVD_PARAM: pstcEthHandle == NULL or astcTxDescTab == NULL or au8TxBuf == NULL or u32TxBufCnt == 0
 */
int32_t ETH_DMA_TxDescListInit(stc_eth_handle_t *pstcEthHandle, stc_eth_dma_desc_t astcTxDescTab[],
                               const uint8_t au8TxBuf[], uint32_t u32TxBufCnt)
{
    uint32_t i;
    stc_eth_dma_desc_t *pstcTxDesc;
    int32_t i32Ret = LL_OK;

    if ((NULL == pstcEthHandle) || (NULL == astcTxDescTab) || (NULL == au8TxBuf) || (0UL == u32TxBufCnt)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Set the DMATxDesc pointer with the first in the astcTxDescTab list */
        pstcEthHandle->stcTxDesc = astcTxDescTab;
        /* Fill each DMATxDesc descriptor */
        for (i = 0U; i < u32TxBufCnt; i++) {
            pstcTxDesc = &astcTxDescTab[i];
            /* Set Second Address Chained */
            pstcTxDesc->u32ControlStatus = ETH_DMA_TXDESC_TSAC;
            /* Set Buffer1 address pointer */
            pstcTxDesc->u32Buf1Addr = (uint32_t)(&au8TxBuf[i * ETH_TX_BUF_SIZE]);
            /* Set the DMA Tx descriptors checksum insertion */
            if (ETH_MAC_CHECKSUM_MD_HW == pstcEthHandle->stcCommInit.u32ChecksumMode) {
                SET_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_CIC_TCPUDPICMP_FULL);
            }
            /* Initialize the next descriptor with the Next Descriptor Polling */
            if (i < (u32TxBufCnt - 1U)) {
                pstcTxDesc->u32Buf2NextDescAddr = (uint32_t)(&astcTxDescTab[i + 1U]);
            } else {
                pstcTxDesc->u32Buf2NextDescAddr = (uint32_t)astcTxDescTab;
            }
        }
        /* Set Transmit Descriptor List Address Register */
        WRITE_REG32(CM_ETH->DMA_TXDLADR, (uint32_t)astcTxDescTab);
    }

    return i32Ret;
}

/**
 * @brief  Initializes DMA Rx descriptor in chain mode.
 * @param  [in] pstcEthHandle           Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] astcRxDescTab           Pointer to the first Rx desc list
 * @param  [in] au8RxBuf                Pointer to the first RxBuffer list
 * @param  [in] u32RxBufCnt             Number of the Rx desc in the list
 * @retval int32_t:
 *           - LL_OK: Initializes Rx chain mode success
 *           - LL_ERR_INVD_PARAM: pstcEthHandle == NULL or astcRxDescTab == NULL or au8RxBuf == NULL or u32RxBufCnt == 0
 */
int32_t ETH_DMA_RxDescListInit(stc_eth_handle_t *pstcEthHandle, stc_eth_dma_desc_t astcRxDescTab[],
                               const uint8_t au8RxBuf[], uint32_t u32RxBufCnt)
{
    uint32_t i;
    stc_eth_dma_desc_t *pstcRxDesc;
    int32_t i32Ret = LL_OK;

    if ((NULL == pstcEthHandle) || (NULL == astcRxDescTab) || (NULL == au8RxBuf) || (0UL == u32RxBufCnt)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Set the DMARxDesc pointer with the first in the astcRxDescTab list */
        pstcEthHandle->stcRxDesc = astcRxDescTab;
        /* Fill each DMARxDesc descriptor */
        for (i = 0UL; i < u32RxBufCnt; i++) {
            pstcRxDesc = &astcRxDescTab[i];
            /* Set Own bit of the Rx descriptor */
            pstcRxDesc->u32ControlStatus  = ETH_DMA_RXDESC_OWN;
            /* Set Buffer1 size and Second Address Chained */
            pstcRxDesc->u32ControlBufSize = ETH_RX_BUF_SIZE | ETH_DMA_RXDESC_RSAC;
            /* Set Buffer1 address pointer */
            pstcRxDesc->u32Buf1Addr       = (uint32_t)(&au8RxBuf[i * ETH_RX_BUF_SIZE]);
            /* Set the DMA Rx Descriptor interrupt */
            if (ETH_RX_MD_INT == pstcEthHandle->stcCommInit.u32ReceiveMode) {
                CLR_REG32_BIT(pstcRxDesc->u32ControlBufSize, ETH_DMA_RXDESC_DIC);
            }
            /* Initialize the next descriptor with the Next Descriptor Polling */
            if (i < (u32RxBufCnt - 1U)) {
                pstcRxDesc->u32Buf2NextDescAddr = (uint32_t)(&astcRxDescTab[i + 1U]);
            } else {
                pstcRxDesc->u32Buf2NextDescAddr = (uint32_t)astcRxDescTab;
            }
        }
        /* Set Receive Descriptor List Address Register */
        WRITE_REG32(CM_ETH->DMA_RXDLADR, (uint32_t)astcRxDescTab);
    }

    return i32Ret;
}

/**
 * @brief  Set DMA transmit frame.
 * @param  [in] pstcEthHandle           Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] u32FrameLen             Total of data to be transmit
 * @retval int32_t:
 *           - LL_OK: Set transmit frame success
 *           - LL_ERR_INVD_PARAM: pstcEthHandle == NULL
 *           - LL_ERR_INVD_MD: Descriptor is owned by the DMA
 */
int32_t ETH_DMA_SetTransFrame(stc_eth_handle_t *pstcEthHandle, uint32_t u32FrameLen)
{
    uint32_t i;
    uint32_t u32BufCnt;
    uint32_t u32Size;
    int32_t i32Ret = LL_OK;

    if ((NULL == pstcEthHandle) || (0U == u32FrameLen)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check if the descriptor is owned by the CPU */
        if (0UL != (pstcEthHandle->stcTxDesc->u32ControlStatus & ETH_DMA_TXDESC_OWN)) {
            i32Ret = LL_ERR_INVD_MD;
        } else {
            /* Get the number of needed Tx buffers for the current frame */
            if (u32FrameLen > ETH_TX_BUF_SIZE) {
                u32BufCnt = u32FrameLen / ETH_TX_BUF_SIZE;
                if (0UL != (u32FrameLen % ETH_TX_BUF_SIZE)) {
                    u32BufCnt++;
                }
            } else {
                u32BufCnt = 1U;
            }

            if (1U == u32BufCnt) {
                /* Set FIRST and LAST segment */
                SET_REG32_BIT(pstcEthHandle->stcTxDesc->u32ControlStatus, (ETH_DMA_TXDESC_TFS | ETH_DMA_TXDESC_TLS));
                /* Set frame size */
                MODIFY_REG32(pstcEthHandle->stcTxDesc->u32ControlBufSize, ETH_DMA_TXDESC_TBS1,
                             (u32FrameLen & ETH_DMA_TXDESC_TBS1));
                /* Set Own bit of the Tx descriptor */
                SET_REG32_BIT(pstcEthHandle->stcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_OWN);
                /* Point to next descriptor */
                pstcEthHandle->stcTxDesc = (stc_eth_dma_desc_t *)(pstcEthHandle->stcTxDesc->u32Buf2NextDescAddr);
            } else {
                for (i = 0U; i < u32BufCnt; i++) {
                    /* Clear FIRST and LAST segment bits */
                    CLR_REG32_BIT(pstcEthHandle->stcTxDesc->u32ControlStatus,
                                  (ETH_DMA_TXDESC_TFS | ETH_DMA_TXDESC_TLS));
                    if (0U == i) {
                        /* Set the FIRST segment bit */
                        SET_REG32_BIT(pstcEthHandle->stcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_TFS);
                    }
                    if ((u32BufCnt - 1U) == i) {
                        /* Set the last segment bit */
                        SET_REG32_BIT(pstcEthHandle->stcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_TLS);
                        u32Size = u32FrameLen - ((u32BufCnt - 1U) * ETH_TX_BUF_SIZE);
                        MODIFY_REG32(pstcEthHandle->stcTxDesc->u32ControlBufSize, ETH_DMA_TXDESC_TBS1,
                                     (u32Size & ETH_DMA_TXDESC_TBS1));
                    } else {
                        /* Set frame size */
                        MODIFY_REG32(pstcEthHandle->stcTxDesc->u32ControlBufSize, ETH_DMA_TXDESC_TBS1,
                                     (ETH_TX_BUF_SIZE & ETH_DMA_TXDESC_TBS1));
                    }

                    /* Set Own bit of the Tx descriptor */
                    SET_REG32_BIT(pstcEthHandle->stcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_OWN);
                    /* Pointer to next descriptor */
                    pstcEthHandle->stcTxDesc = (stc_eth_dma_desc_t *)(pstcEthHandle->stcTxDesc->u32Buf2NextDescAddr);
                }
            }

            /* When Tx Buffer unavailable flag is set: clear it and resume transmission */
            if (0UL != (READ_REG32_BIT(CM_ETH->DMA_DMASTSR, ETH_DMA_FLAG_TUS))) {
                /* Clear DMA TUS flag */
                WRITE_REG32(CM_ETH->DMA_DMASTSR, ETH_DMA_FLAG_TUS);
                /* Resume DMA transmission */
                WRITE_REG32(CM_ETH->DMA_TXPOLLR, 0UL);
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Get DMA receive frame.
 * @param  [in] pstcEthHandle           Pointer to a @ref stc_eth_handle_t structure
 * @retval int32_t:
 *           - LL_OK: Get receive frame success
 *           - LL_ERR_INVD_PARAM: pstcEthHandle == NULL
 *           - LL_ERR: Not completed frame received
 */
int32_t ETH_DMA_GetReceiveFrame(stc_eth_handle_t *pstcEthHandle)
{
    int32_t i32Ret = LL_ERR;

    if (NULL == pstcEthHandle) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check if segment is not owned by DMA */
        if (0UL == (pstcEthHandle->stcRxDesc->u32ControlStatus & ETH_DMA_RXDESC_OWN)) {
            /* Check if last segment */
            if (0UL != (pstcEthHandle->stcRxDesc->u32ControlStatus & ETH_DMA_RXDESC_RLS)) {
                pstcEthHandle->stcRxFrame.u32SegCount++;
                pstcEthHandle->stcRxFrame.pstcLSDesc = pstcEthHandle->stcRxDesc;
                /* Check if last segment is first segment */
                if (1U == pstcEthHandle->stcRxFrame.u32SegCount) {
                    pstcEthHandle->stcRxFrame.pstcFSDesc = pstcEthHandle->stcRxDesc;
                }

                /* Get the Frame Length of the received packet: Strip FCS */
                pstcEthHandle->stcRxFrame.u32Len = ((pstcEthHandle->stcRxDesc->u32ControlStatus &
                                                     ETH_DMA_RXDESC_FRAL) >> ETH_DMA_RXDESC_FRAME_LEN_SHIFT) - 4U;
                /* Get the address of the buffer start address */
                pstcEthHandle->stcRxFrame.u32Buf = (pstcEthHandle->stcRxFrame.pstcFSDesc)->u32Buf1Addr;
                /* Pointer to next descriptor */
                pstcEthHandle->stcRxDesc = (stc_eth_dma_desc_t *)(pstcEthHandle->stcRxDesc->u32Buf2NextDescAddr);
                /* Get success */
                i32Ret = LL_OK;
            } else if (0UL != (pstcEthHandle->stcRxDesc->u32ControlStatus & ETH_DMA_RXDESC_RFS)) {  /* Check if first segment */
                pstcEthHandle->stcRxFrame.pstcFSDesc  = pstcEthHandle->stcRxDesc;
                pstcEthHandle->stcRxFrame.pstcLSDesc  = NULL;
                pstcEthHandle->stcRxFrame.u32SegCount = 1U;
                /* Point to next descriptor */
                pstcEthHandle->stcRxDesc = (stc_eth_dma_desc_t *)(pstcEthHandle->stcRxDesc->u32Buf2NextDescAddr);
            } else {    /* Check if intermediate segment */
                pstcEthHandle->stcRxFrame.u32SegCount++;
                /* Point to next descriptor */
                pstcEthHandle->stcRxDesc = (stc_eth_dma_desc_t *)(pstcEthHandle->stcRxDesc->u32Buf2NextDescAddr);
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Get DMA receive frame in interrupt mode.
 * @param  [in] pstcEthHandle           Pointer to a @ref stc_eth_handle_t structure
 * @retval int32_t:
 *           - LL_OK: Get receive frame success
 *           - LL_ERR_INVD_PARAM: pstcEthHandle == NULL
 *           - LL_ERR: Not completed frame received
 */
int32_t ETH_DMA_GetReceiveFrame_Int(stc_eth_handle_t *pstcEthHandle)
{
    uint32_t u32DescCnt = 0U;
    int32_t i32Ret = LL_ERR;

    if (NULL == pstcEthHandle) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Scan descriptor owned by CPU */
        while ((0UL == (pstcEthHandle->stcRxDesc->u32ControlStatus & ETH_DMA_RXDESC_OWN)) &&
               (u32DescCnt < ETH_RX_BUF_SIZE)) {
            u32DescCnt++;
            /* Check if first segment in frame */
            if (ETH_DMA_RXDESC_RFS == (pstcEthHandle->stcRxDesc->u32ControlStatus &
                                       (ETH_DMA_RXDESC_RFS | ETH_DMA_RXDESC_RLS))) {
                pstcEthHandle->stcRxFrame.pstcFSDesc  = pstcEthHandle->stcRxDesc;
                pstcEthHandle->stcRxFrame.pstcLSDesc  = NULL;
                pstcEthHandle->stcRxFrame.u32SegCount = 1U;
                /* Point to next descriptor */
                pstcEthHandle->stcRxDesc = (stc_eth_dma_desc_t *)(pstcEthHandle->stcRxDesc->u32Buf2NextDescAddr);
            } else if (0UL == (pstcEthHandle->stcRxDesc->u32ControlStatus & (ETH_DMA_RXDESC_RFS | ETH_DMA_RXDESC_RLS))) {
                /* Check if intermediate segment */
                pstcEthHandle->stcRxFrame.u32SegCount++;
                /* Point to next descriptor */
                pstcEthHandle->stcRxDesc = (stc_eth_dma_desc_t *)(pstcEthHandle->stcRxDesc->u32Buf2NextDescAddr);
            } else {    /* Last segment */
                pstcEthHandle->stcRxFrame.u32SegCount++;
                /* Last segment */
                pstcEthHandle->stcRxFrame.pstcLSDesc = pstcEthHandle->stcRxDesc;
                /* Check if last segment is first segment */
                if (1U == pstcEthHandle->stcRxFrame.u32SegCount) {
                    pstcEthHandle->stcRxFrame.pstcFSDesc = pstcEthHandle->stcRxDesc;
                }

                /* Get the Frame Length of the received packet: Strip FCS */
                pstcEthHandle->stcRxFrame.u32Len = ((pstcEthHandle->stcRxDesc->u32ControlStatus &
                                                     ETH_DMA_RXDESC_FRAL) >> ETH_DMA_RXDESC_FRAME_LEN_SHIFT) - 4U;
                /* Get the address of the buffer start address */
                pstcEthHandle->stcRxFrame.u32Buf = (pstcEthHandle->stcRxFrame.pstcFSDesc)->u32Buf1Addr;
                /* Pointer to next descriptor */
                pstcEthHandle->stcRxDesc = (stc_eth_dma_desc_t *)(pstcEthHandle->stcRxDesc->u32Buf2NextDescAddr);
                /* Get success */
                i32Ret = LL_OK;
                break;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Set DMA Tx descriptor own bit.
 * @param  [in] pstcTxDesc              Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32Owner                DMA Tx descriptor owner
 *         This parameter can be one of the following values:
 *           @arg ETH_DMA_DESC_OWN_CPU: Descriptor is owned by CPU
 *           @arg ETH_DMA_DESC_OWN_DMA: Descriptor is owned by DMA
 * @retval int32_t:
 *           - LL_OK: Set Tx descriptor own bit success
 *           - LL_ERR_INVD_PARAM: pstcTxDesc == NULL
 */
int32_t ETH_DMA_SetTxDescOwn(stc_eth_dma_desc_t *pstcTxDesc, uint32_t u32Owner)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcTxDesc) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMA_DESC_OWN(u32Owner));

        if (ETH_DMA_DESC_OWN_CPU != u32Owner) {
            SET_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_OWN);
        } else {
            CLR_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_OWN);
        }
    }

    return i32Ret;
}

/**
 * @brief  Set DMA Tx descriptor buffer size.
 * @param  [in] pstcTxDesc              Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u8BufNum                Buffer sequence number
 *         This parameter can be one of the following values:
 *           @arg ETH_DMA_DESC_BUF1:    DMA Tx Desc Buffer1
 *           @arg ETH_DMA_DESC_BUF2:    DMA Tx Desc Buffer2
 * @param  [in] u32BufSize              DMA Tx buffer size
 * @retval int32_t:
 *           - LL_OK: Set Tx descriptor buffer size success
 *           - LL_ERR_INVD_PARAM: pstcTxDesc == NULL
 */
int32_t ETH_DMA_SetTxDescBufSize(stc_eth_dma_desc_t *pstcTxDesc, uint8_t u8BufNum, uint32_t u32BufSize)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32ShiftBit = 0UL;

    if (NULL == pstcTxDesc) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMA_DESC_BUF(u8BufNum));
        DDL_ASSERT(IS_ETH_DMA_TXDESC_BUF_SIZE(u32BufSize));

        /* DMA Tx Desc buffer2 */
        if (ETH_DMA_DESC_BUF1 != u8BufNum) {
            u32ShiftBit = ETH_DMA_DESC_BUF2_SIZE_SHIFT;
        }
        MODIFY_REG32(pstcTxDesc->u32ControlBufSize, (ETH_DMA_TXDESC_TBS1 << u32ShiftBit),
                     (u32BufSize << u32ShiftBit));
    }

    return i32Ret;
}

/**
 * @brief  Configure DMA Tx descriptor checksum insert.
 * @param  [in] pstcTxDesc              Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32ChecksumMode         Checksum insert mode
 *         This parameter can be one of the following values:
 *           @arg ETH_DMA_TXDESC_CHECKSUM_BYPASS:               Checksum Engine is bypassed
 *           @arg ETH_DMA_TXDESC_CHECKSUM_IPV4_HEADER:          IPv4 header checksum insertion
 *           @arg ETH_DMA_TXDESC_CHECKSUM_TCPUDPICMP_SEGMENT:   TCP/UDP/ICMP Checksum Insertion calculated over segment only
 *           @arg ETH_DMA_TXDESC_CHECKSUM_TCPUDPICMP_FULL:      TCP/UDP/ICMP Checksum Insertion fully calculated
 * @retval int32_t:
 *           - LL_OK: Configure Tx descriptor checksum insert success
 *           - LL_ERR_INVD_PARAM: pstcTxDesc == NULL
 */
int32_t ETH_DMA_TxDescChecksumInsertConfig(stc_eth_dma_desc_t *pstcTxDesc, uint32_t u32ChecksumMode)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcTxDesc) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMA_TXDESC_CHECKSUM_CTRL(u32ChecksumMode));

        MODIFY_REG32(pstcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_CIC, u32ChecksumMode);
    }

    return i32Ret;
}

/**
 * @brief  Configure DMA Tx descriptor VLAN insert.
 * @param  [in] pstcTxDesc              Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32VlanMode             VLAN insert mode
 *         This parameter can be one of the following values:
 *           @arg ETH_DMA_TXDESC_VLAN_BYPASS:       VLAN Insertion is bypassed
 *           @arg ETH_DMA_TXDESC_VLAN_REMOVE_TAG:   Remove Tag and Type fields in VLAN frame
 *           @arg ETH_DMA_TXDESC_VLAN_INSERT_TAG:   Insert VLAN Tag value in ETH_MAC_VTACTLR Register into transmit frame
 *           @arg ETH_DMA_TXDESC_VLAN_REPLACE_TAG:  Replace VLAN tag value in transmit frame with VLAN tag value in ETH_MAC_VTACTLR register
 * @retval int32_t:
 *           - LL_OK: Configure Tx descriptor VLAN insert success
 *           - LL_ERR_INVD_PARAM: pstcTxDesc == NULL
 */
int32_t ETH_DMA_TxDescVlanInsertConfig(stc_eth_dma_desc_t *pstcTxDesc, uint32_t u32VlanMode)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcTxDesc) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMA_TXDESC_VLAN_CTRL(u32VlanMode));

        MODIFY_REG32(pstcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_VLANC, u32VlanMode);
    }

    return i32Ret;
}

/**
 * @brief  Configure DMA Tx descriptor SA insert.
 * @param  [in] pstcTxDesc              Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32Mode                 SA insert mode
 *         This parameter can be one of the following values:
 *           @arg ETH_DMA_TXDESC_SAIRC_BYPASS:              Source Address Insertion or Replace Control is bypassed
 *           @arg ETH_DMA_TXDESC_SAIRC_INSERT_MACADDR0:     Insert address value in MAC address register 0 into transmit frame as SA address
 *           @arg ETH_DMA_TXDESC_SAIRC_REPLACE_MACADDR0:    Replace SA address in transmit frame with address value in MAC address register 0
 *           @arg ETH_DMA_TXDESC_SAIRC_INSERT_MACADDR1:     Insert address value in MAC address register 1 into transmit frame as SA address
 *           @arg ETH_DMA_TXDESC_SAIRC_REPLACE_MACADDR1:    Replace SA address in transmit frame with address value in MAC address register 1
 * @retval int32_t:
 *           - LL_OK: Configure Tx descriptor SA insert success
 *           - LL_ERR_INVD_PARAM: pstcTxDesc == NULL
 */
int32_t ETH_DMA_TxDescSrcAddrInsertConfig(stc_eth_dma_desc_t *pstcTxDesc, uint32_t u32Mode)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcTxDesc) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMA_TXDESC_SRC_ADDR_CTRL(u32Mode));

        MODIFY_REG32(pstcTxDesc->u32ControlBufSize, ETH_DMA_TXDESC_SAIRC, u32Mode);
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable DMA Tx descriptor add CRC.
 * @param  [in] pstcTxDesc              Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *           - LL_OK: Configure Tx add CRC success
 *           - LL_ERR_INVD_PARAM: pstcTxDesc == NULL
 */
int32_t ETH_DMA_TxDescCrcCmd(stc_eth_dma_desc_t *pstcTxDesc, en_functional_state_t enNewState)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcTxDesc) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        if (DISABLE != enNewState) {
            CLR_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_DCRC);
        } else {
            SET_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_DCRC);
        }
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable DMA Tx descriptor padding.
 * @param  [in] pstcTxDesc              Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *           - LL_OK: Configure Tx padding success
 *           - LL_ERR_INVD_PARAM: pstcTxDesc == NULL
 */
int32_t ETH_DMA_TxDescPadCmd(stc_eth_dma_desc_t *pstcTxDesc, en_functional_state_t enNewState)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcTxDesc) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        if (DISABLE != enNewState) {
            CLR_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_DPAD);
        } else {
            SET_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_DPAD);
        }
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable DMA Tx descriptor timestamp.
 * @param  [in] pstcTxDesc              Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *           - LL_OK: Configure Tx padding success
 *           - LL_ERR_INVD_PARAM: pstcTxDesc == NULL
 */
int32_t ETH_DMA_TxDescTimestamp(stc_eth_dma_desc_t *pstcTxDesc, en_functional_state_t enNewState)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcTxDesc) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        if (DISABLE != enNewState) {
            SET_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_TTSE);
        } else {
            CLR_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_TTSE);
        }
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable DMA Tx descriptor replace CRC.
 * @param  [in] pstcTxDesc              Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *           - LL_OK: Configure Tx replace CRC success
 *           - LL_ERR_INVD_PARAM: pstcTxDesc == NULL
 */
int32_t ETH_DMA_TxDescReplaceCrcCmd(stc_eth_dma_desc_t *pstcTxDesc, en_functional_state_t enNewState)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcTxDesc) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        if (DISABLE != enNewState) {
            SET_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_CRCR);
        } else {
            CLR_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_CRCR);
        }
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable DMA Tx finished interrupt.
 * @param  [in] pstcTxDesc              Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *           - LL_OK: Configure Tx interrupt configure success
 *           - LL_ERR_INVD_PARAM: pstcTxDesc == NULL
 */
int32_t ETH_DMA_TxDescIntCmd(stc_eth_dma_desc_t *pstcTxDesc, en_functional_state_t enNewState)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcTxDesc) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        if (DISABLE != enNewState) {
            SET_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_IOC);
        } else {
            CLR_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMA_TXDESC_IOC);
        }
    }

    return i32Ret;
}

/**
 * @brief  Get DMA Tx descriptor flag status.
 * @param  [in] pstcTxDesc              Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32Flag                 DMA Tx descriptor flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_DMA_TXDESC_OWN:   OWN bit
 *           @arg ETH_DMA_TXDESC_IOC:   Interrupt on Completion
 *           @arg ETH_DMA_TXDESC_TLS:   Transmit Last Segment
 *           @arg ETH_DMA_TXDESC_TFS:   Transmit First Segment
 *           @arg ETH_DMA_TXDESC_DCRC:  Disable CRC
 *           @arg ETH_DMA_TXDESC_DPAD:  Disable Padding
 *           @arg ETH_DMA_TXDESC_TTSE:  Transmit Time Stamp Enable
 *           @arg ETH_DMA_TXDESC_CRCR:  CRC Replace Control
 *           @arg ETH_DMA_TXDESC_TER:   Transmit End of Ring
 *           @arg ETH_DMA_TXDESC_TSAC:  Second Address Chained
 *           @arg ETH_DMA_TXDESC_TTSS:  Tx Time Stamp Status
 *           @arg ETH_DMA_TXDESC_IHE:   IP Header Error
 *           @arg ETH_DMA_TXDESC_ETSUM: Tx Error summary
 *           @arg ETH_DMA_TXDESC_JTE:   Jabber Timeout Error
 *           @arg ETH_DMA_TXDESC_FFF:   Frame Flushed
 *           @arg ETH_DMA_TXDESC_TPCE:  Payload Checksum Error
 *           @arg ETH_DMA_TXDESC_LOCE:  Loss Carrier Error
 *           @arg ETH_DMA_TXDESC_NCE:   No Carrier Error
 *           @arg ETH_DMA_TXDESC_TLCE:  Late Collision Error
 *           @arg ETH_DMA_TXDESC_ECE:   Excessive Collision Error
 *           @arg ETH_DMA_TXDESC_VLF:   VLAN Frame
 *           @arg ETH_DMA_TXDESC_EDE:   Excessive Deferral Error
 *           @arg ETH_DMA_TXDESC_UDE:   Underflow Error
 *           @arg ETH_DMA_TXDESC_DEE:   Deferred Error
 *           @arg ETH_DMA_TXDESC_STATUS_ALL:    All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t ETH_DMA_GetTxDescStatus(const stc_eth_dma_desc_t *pstcTxDesc, uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_DMA_TXDESC_STATUS(u32Flag));

    if (NULL != pstcTxDesc) {
        if (0UL != (pstcTxDesc->u32ControlStatus & u32Flag)) {
            enFlagSta = SET;
        }
    }

    return enFlagSta;
}

/**
 * @brief  Get DMA Tx descriptor collision count
 * @param  [in] pstcTxDesc              Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [out] pu32Count              Pointer to DMA Tx collision count
 * @retval int32_t:
 *           - LL_OK: Get collision count success
 *           - LL_ERR_INVD_PARAM: pstcTxDesc == NULL or pu32Count == NULL
 */
int32_t ETH_DMA_GetTxDescCollisionCount(const stc_eth_dma_desc_t *pstcTxDesc, uint32_t *pu32Count)
{
    int32_t i32Ret = LL_OK;

    if ((NULL == pstcTxDesc) || (NULL == pu32Count)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        *pu32Count = (pstcTxDesc->u32ControlStatus >> ETH_DMA_TXDESC_COLLISION_CNT_SHIFT) & ((uint32_t)0x0000000FUL);
    }

    return i32Ret;
}

/**
 * @brief  Get DMA Tx descriptor timestamp.
 * @param  [in] pstcTxDesc              Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [out] pu32High               Timestamp high bit time
 * @param  [out] pu32Low                Timestamp low bit time
 * @retval int32_t:
 *           - LL_OK: Get timestamp success
 *           - LL_ERR_INVD_PARAM: pstcTxDesc == NULL or pu32High == NULL or pu32Low == NULL
 */
int32_t ETH_DMA_GetTxDescTimeStamp(const stc_eth_dma_desc_t *pstcTxDesc, uint32_t *pu32High, uint32_t *pu32Low)
{
    int32_t i32Ret = LL_OK;

    if ((NULL == pstcTxDesc) || (NULL == pu32High) || (NULL == pu32Low)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        *pu32Low  = pstcTxDesc->u32TimestampLow;
        *pu32High = pstcTxDesc->u32TimestampHigh;
    }

    return i32Ret;
}

/**
 * @brief  Set DMA Rx descriptor own bit.
 * @param  [in] pstcRxDesc              Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32Owner                DMA Rx descriptor owner
 *         This parameter can be one of the following values:
 *           @arg ETH_DMA_DESC_OWN_CPU: Descriptor is owned by CPU
 *           @arg ETH_DMA_DESC_OWN_DMA: Descriptor is owned by DMA
 * @retval int32_t:
 *           - LL_OK: Set Rx descriptor own bit success
 *           - LL_ERR_INVD_PARAM: pstcRxDesc == NULL
 */
int32_t ETH_DMA_SetRxDescOwn(stc_eth_dma_desc_t *pstcRxDesc, uint32_t u32Owner)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcRxDesc) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMA_DESC_OWN(u32Owner));

        if (ETH_DMA_DESC_OWN_CPU != u32Owner) {
            SET_REG32_BIT(pstcRxDesc->u32ControlStatus, ETH_DMA_RXDESC_OWN);
        } else {
            CLR_REG32_BIT(pstcRxDesc->u32ControlStatus, ETH_DMA_RXDESC_OWN);
        }
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable DMA Rx finished interrupt.
 * @param  [in] pstcRxDesc              Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *           - LL_OK: Rx interrupt configure success
 *           - LL_ERR_INVD_PARAM: pstcRxDesc == NULL
 */
int32_t ETH_DMA_RxDescIntCmd(stc_eth_dma_desc_t *pstcRxDesc, en_functional_state_t enNewState)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcRxDesc) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        if (DISABLE != enNewState) {
            CLR_REG32_BIT(pstcRxDesc->u32ControlBufSize, ETH_DMA_RXDESC_DIC);
        } else {
            SET_REG32_BIT(pstcRxDesc->u32ControlBufSize, ETH_DMA_RXDESC_DIC);
        }
    }

    return i32Ret;
}

/**
 * @brief  Get DMA Rx descriptor flag status.
 * @param  [in] pstcRxDesc              Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32Flag                 DMA Rx descriptor flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_DMA_RXDESC_OWN:           OWN bit
 *           @arg ETH_DMA_RXDESC_DAF:           DA Filter Fail for the received frame
 *           @arg ETH_DMA_RXDESC_ERSUM:         Rx Error summary
 *           @arg ETH_DMA_RXDESC_DPE:           Descriptor Error
 *           @arg ETH_DMA_RXDESC_SAF:           SA Filter Fail for the received frame
 *           @arg ETH_DMA_RXDESC_LEE:           Length Error
 *           @arg ETH_DMA_RXDESC_OVE:           Overflow Error
 *           @arg ETH_DMA_RXDESC_VLAT           VLAN Tag
 *           @arg ETH_DMA_RXDESC_RFS:           First descriptor
 *           @arg ETH_DMA_RXDESC_RLS:           Last descriptor
 *           @arg ETH_DMA_RXDESC_IPE_TSPA_GF:   COE Error or Time stamp valid or jumbo frame
 *           @arg ETH_DMA_RXDESC_RLCE:          Late collision Error
 *           @arg ETH_DMA_RXDESC_FRAT:          Frame type
 *           @arg ETH_DMA_RXDESC_WTE:           Receive Watchdog Timeout
 *           @arg ETH_DMA_RXDESC_REE:           Receive error
 *           @arg ETH_DMA_RXDESC_DBE:           Dribble bit error
 *           @arg ETH_DMA_RXDESC_CRE:           CRC error
 *           @arg ETH_DMA_RXDESC_DAS_ESA:       MAC Address Filter/Status bit extension
 *           @arg ETH_DMA_RXDESC_STATUS_ALL:    All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t ETH_DMA_GetRxDescStatus(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_DMA_RXDESC_STATUS(u32Flag));

    if (NULL != pstcRxDesc) {
        if (0UL != (pstcRxDesc->u32ControlStatus & u32Flag)) {
            enFlagSta = SET;
        }
    }

    return enFlagSta;
}

/**
 * @brief  Get DMA Rx descriptor extend flag status.
 * @param  [in] pstcRxDesc              Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32Flag                 DMA Rx descriptor extend flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_DMA_RXDESC_L4FMS:     L4 Port Filter Status
 *           @arg ETH_DMA_RXDESC_L3FMS:     L3 Address Filter Status
 *           @arg ETH_DMA_RXDESC_TSPD:      Discard Time Stamp
 *           @arg ETH_DMA_RXDESC_PTPV:      PTP Version
 *           @arg ETH_DMA_RXDESC_PTPFT:     PTP Frame Type
 *           @arg ETH_DMA_RXDESC_IPV6DR:    IPv6 Packet Received
 *           @arg ETH_DMA_RXDESC_IPV4DR:    IPv4 Packet Received
 *           @arg ETH_DMA_RXDESC_IPCB:      COE engine Bypassed
 *           @arg ETH_DMA_RXDESC_IPPE:      IP Payload Error
 *           @arg ETH_DMA_RXDESC_IPHE:      IP Header Error
 *           @arg ETH_DMA_RXDESC_EXTEND_STATUS_ALL: All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t ETH_DMA_GetRxDescExtendStatus(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_DMA_RXDESC_EXTEND_STATUS(u32Flag));

    if (NULL != pstcRxDesc) {
        if (0UL != (pstcRxDesc->u32ExtendStatus & u32Flag)) {
            enFlagSta = SET;
        }
    }

    return enFlagSta;
}

/**
 * @brief  Get DMA Rx descriptor payload type.
 * @param  [in] pstcRxDesc              Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [out] pu32PayloadType        Pointer to DMA Rx payload type
 *           The payload type may be one of the following values:
 *           - ETH_DMA_RXDESC_IPPT_UNKNOWN: Unknown
 *           - ETH_DMA_RXDESC_IPPT_UDP:     UDP
 *           - ETH_DMA_RXDESC_IPPT_TCP:     TCP
 *           - ETH_DMA_RXDESC_IPPT_ICMP:    ICMP
 * @retval int32_t:
 *           - LL_OK: Get payload type success
 *           - LL_ERR_INVD_PARAM: pstcRxDesc == NULL or pu32PayloadType == NULL
 */
int32_t ETH_DMA_GetRxDescPayloadType(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t *pu32PayloadType)
{
    int32_t i32Ret = LL_OK;

    if ((NULL == pstcRxDesc) || (NULL == pu32PayloadType)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        *pu32PayloadType = pstcRxDesc->u32ExtendStatus & ETH_DMA_RXDESC_IPPT;
    }

    return i32Ret;
}

/**
 * @brief  Get DMA Rx descriptor datagram type.
 * @param  [in] pstcRxDesc              Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [out] pu32DatagramType       Pointer to DMA Rx datagram type
 *           The payload type may be one of the following values:
 *           - ETH_DMA_RXDESC_MTP_NONE:                     No PTP messages
 *           - ETH_DMA_RXDESC_MTP_SYNC:                     SYNC message (all clock types)
 *           - ETH_DMA_RXDESC_MTP_FOLLOW_UP:                Follow_Up message (all clock types)
 *           - ETH_DMA_RXDESC_MTP_DELAY_REQ:                Delay_Req message (all clock types)
 *           - ETH_DMA_RXDESC_MTP_DELAY_RESP:               Delay_Resp message (all clock types)
 *           - ETH_DMA_RXDESC_MTP_PDELAY_REQ:               Pdelay_Req message (peer-to-peer transparent clock)
 *           - ETH_DMA_RXDESC_MTP_PDELAY_RESP:              Pdelay_Resp message (peer-to-peer transparent clock)
 *           - ETH_DMA_RXDESC_MTP_PDELAY_RESP_FOLLOW_UP:    Pdelay_Resp_Follow_Up message (peer-to-peer transparent clock)
 *           - ETH_DMA_RXDESC_MTP_ANNOUNCE:                 Announce message (Ordinary or Boundary clock)
 *           - ETH_DMA_RXDESC_MTP_MANAGEMENT:               Management message (Ordinary or Boundary clock)
 *           - ETH_DMA_RXDESC_MTP_SIGNALING:                Signaling message (Ordinary or Boundary clock)
 *           - ETH_DMA_RXDESC_MTP_DEFAULT:                  Default Datagram Type
 * @retval int32_t:
 *           - LL_OK: Get datagram type success
 *           - LL_ERR_INVD_PARAM: pstcRxDesc == NULL or pu32DatagramType == NULL
 */
int32_t ETH_DMA_GetRxDescDatagramType(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t *pu32DatagramType)
{
    int32_t i32Ret = LL_OK;

    if ((NULL == pstcRxDesc) || (NULL == pu32DatagramType)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        *pu32DatagramType = pstcRxDesc->u32ExtendStatus & ETH_DMA_RXDESC_MTP;
    }

    return i32Ret;
}

/**
 * @brief  Get DMA Rx descriptor frame length.
 * @param  [in] pstcRxDesc              Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [out] pu32FrameLen           Pointer to DMA Rx frame length
 * @retval int32_t:
 *           - LL_OK: Get frame length success
 *           - LL_ERR_INVD_PARAM: pstcRxDesc == NULL or pu32FrameLen == NULL
 */
int32_t ETH_DMA_GetRxDescFrameLen(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t *pu32FrameLen)
{
    int32_t i32Ret = LL_OK;

    if ((NULL == pstcRxDesc) || (NULL == pu32FrameLen)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        *pu32FrameLen = (pstcRxDesc->u32ControlStatus >> ETH_DMA_RXDESC_FRAME_LEN_SHIFT) & ((uint32_t)0x00003FFFUL);
    }

    return i32Ret;
}

/**
 * @brief  Get DMA Rx descriptor buffer size.
 * @param  [in] pstcRxDesc              Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u8BufNum                Buffer sequence number
 *         This parameter can be one of the following values:
 *           @arg ETH_DMA_DESC_BUF1:    DMA Rx Desc Buffer1
 *           @arg ETH_DMA_DESC_BUF2:    DMA Rx Desc Buffer2
 * @param  [out] pu32BufSize            Pointer to DMA Rx buffer size
 * @retval int32_t:
 *           - LL_OK: Get buffer size success
 *           - LL_ERR_INVD_PARAM: pstcRxDesc == NULL or pu32BufSize == NULL
 */
int32_t ETH_DMA_GetRxDescBufSize(const stc_eth_dma_desc_t *pstcRxDesc, uint8_t u8BufNum, uint32_t *pu32BufSize)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32ShiftBit = 0UL;

    if ((NULL == pstcRxDesc) || (NULL == pu32BufSize)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMA_DESC_BUF(u8BufNum));

        /* DMA Rx Desc buffer2 */
        if (ETH_DMA_DESC_BUF1 != u8BufNum) {
            u32ShiftBit = ETH_DMA_DESC_BUF2_SIZE_SHIFT;
        }
        *pu32BufSize = (pstcRxDesc->u32ControlBufSize >> u32ShiftBit) & ((uint32_t)0x00001FFFUL);
    }

    return i32Ret;
}

/**
 * @brief  Get DMA Rx descriptor timestamp.
 * @param  [in] pstcRxDesc              Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [out] pu32High               Timestamp high bit time
 * @param  [out] pu32Low                Timestamp low bit time
 * @retval int32_t:
 *           - LL_OK: Get timestamp success
 *           - LL_ERR_INVD_PARAM: pstcRxDesc == NULL or pu32High == NULL or pu32Low == NULL
 */
int32_t ETH_DMA_GetRxDescTimeStamp(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t *pu32High, uint32_t *pu32Low)
{
    int32_t i32Ret = LL_OK;

    if ((NULL == pstcRxDesc) || (NULL == pu32High) || (NULL == pu32Low)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        *pu32Low  = pstcRxDesc->u32TimestampLow;
        *pu32High = pstcRxDesc->u32TimestampHigh;
    }

    return i32Ret;
}

/******************************************************************************/
/*                                PMT Functions                               */
/******************************************************************************/
/**
 * @brief  Reset PMT wakeup frame pointer.
 * @param  None
 * @retval int32_t:
 *           - LL_OK: Reset pointer success
 *           - LL_ERR_TIMEOUT: Reset timeout
 */
int32_t ETH_PMT_ResetWakeupFramePointer(void)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_OK;

    WRITE_REG32(bCM_ETH->MAC_PMTCTLR_b.RTWKFR, 1U);
    u32Count = ETH_WR_REG_TIMEOUT * (HCLK_VALUE / 20000UL);
    while (0UL != READ_REG32(bCM_ETH->MAC_PMTCTLR_b.RTWKFR)) {
        if (0UL == u32Count) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
        u32Count--;
    }

    return i32Ret;
}
/**
 * @brief  Write PMT wakeup frame register.
 * @param  [in] au32RegBuf              Pointer to wakeup frame filter register buffer(8 words).
 * @retval int32_t:
 *           - LL_OK: Write register success
 *           - LL_ERR_INVD_PARAM: au32RegBuf == NULL
 */
int32_t ETH_PMT_WriteWakeupFrameReg(const uint32_t au32RegBuf[])
{
    uint32_t i;
    int32_t i32Ret = LL_OK;

    if (NULL == au32RegBuf) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        for (i = 0U; i < ETH_WAKEUP_REG_LEN; i++) {
            WRITE_REG32(CM_ETH->MAC_RTWKFFR, au32RegBuf[i]);
        }
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable PMT forward wakeup frame.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_PMT_ForwardWakeupFrameCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_ETH->MAC_PMTCTLR_b.RTWKTR, enNewState);
}

/**
 * @brief  Enable or disable PMT wakeup source.
 * @param  [in] u32WakeupSrc            Wakeup source
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_PMT_WAKEUP_SRC_GLOBAL_UNICAST:    Global unicast
 *           @arg ETH_PMT_WAKEUP_SRC_WAKEUP_FRAME:      Wake-Up Frame
 *           @arg ETH_PMT_WAKEUP_SRC_MAGIC_PACKET:      Magic Packet
 *           @arg ETH_PMT_WAKEUP_SRC_ALL:               All of the above
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_PMT_WakeupSrcCmd(uint32_t u32WakeupSrc, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_PMT_WAKEUP_SRC(u32WakeupSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        SET_REG32_BIT(CM_ETH->MAC_PMTCTLR, u32WakeupSrc);
    } else {
        CLR_REG32_BIT(CM_ETH->MAC_PMTCTLR, u32WakeupSrc);
    }
}

/**
 * @brief  Enable or disable PMT powerdown mode.
 * @param  None
 * @retval int32_t:
 *           - LL_OK: Set powerdown mode success
 *           - LL_ERR: Set powerdown mode failed
 */
int32_t ETH_PMT_EnterPowerDown(void)
{
    int32_t i32Ret = LL_ERR;

    if (0UL != READ_REG32(bCM_ETH->MAC_PMTCTLR_b.MPEN)) {
        if (0UL != READ_REG32(bCM_ETH->MAC_PMTCTLR_b.WKEN)) {
            WRITE_REG32(bCM_ETH->MAC_PMTCTLR_b.PWDN, ENABLE);
            i32Ret = LL_OK;
        }
    }

    return i32Ret;
}

/**
 * @brief  Get PMT flag status.
 * @param  [in] u32Flag                 PMT flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_PMT_FLAG_RTWKFR:  Wake-Up Frame Filter Register Pointer Reset
 *           @arg ETH_PMT_FLAG_WKFR:    Wake-Up Frame Received
 *           @arg ETH_PMT_FLAG_MPFR:    Magic Packet Received
 *           @arg ETH_PMT_FLAG_ALL:     All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t ETH_PMT_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_PMT_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(CM_ETH->MAC_PMTCTLR, u32Flag))) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/******************************************************************************/
/*                                MMC Functions                               */
/******************************************************************************/
/**
 * @brief  De-Initialize MMC.
 * @param  None
 * @retval int32_t:
 *           - LL_OK: MMC De-Initialize success
*           - LL_ERR_TIMEOUT: De-Initialize timeout
 */
int32_t ETH_MMC_DeInit(void)
{
    WRITE_REG32(CM_ETH->MMC_MMCCTLR, 0UL);
    WRITE_REG32(CM_ETH->MMC_RITCTLR, 0UL);
    WRITE_REG32(CM_ETH->MMC_TITCTLR, 0UL);

    return ETH_MMC_CounterReset();
}

/**
 * @brief  Initialize MMC.
 * @param  [in] pstcMmcInit             Pointer to a @ref stc_eth_mmc_init_t structure
 * @retval int32_t:
 *           - LL_OK: MMC Initialize success
 *           - LL_ERR_INVD_PARAM: pstcMmcInit == NULL
 */
int32_t ETH_MMC_Init(const stc_eth_mmc_init_t *pstcMmcInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcMmcInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_MMC_CNT_PRESET_MD(pstcMmcInit->u32PresetMode));
        DDL_ASSERT(IS_ETH_MMC_RD_RST(pstcMmcInit->u32ReadReset));
        DDL_ASSERT(IS_ETH_MMC_CNT_RELOAD(pstcMmcInit->u32Reload));

        MODIFY_REG32(CM_ETH->MMC_MMCCTLR,
                     (ETH_MMC_MMCCTLR_MCPSEL | ETH_MMC_MMCCTLR_MCPSET |
                      ETH_MMC_MMCCTLR_ROR    | ETH_MMC_MMCCTLR_COS),
                     (pstcMmcInit->u32PresetMode | pstcMmcInit->u32ReadReset |
                      pstcMmcInit->u32Reload));
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_eth_mmc_init_t to default values.
 * @param  [out] pstcMmcInit            Pointer to a @ref stc_eth_mmc_init_t structure
 * @retval int32_t:
 *           - LL_OK: Structure Initialize success
 *           - LL_ERR_INVD_PARAM: pstcMmcInit == NULL
 */
int32_t ETH_MMC_StructInit(stc_eth_mmc_init_t *pstcMmcInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcMmcInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcMmcInit->u32PresetMode = ETH_MMC_CNT_PRESET_MD_DISABLE;
        pstcMmcInit->u32ReadReset  = ETH_MMC_RD_RST_ENABLE;
        pstcMmcInit->u32Reload = ETH_MMC_CNT_RELOAD_ENABLE;
    }

    return i32Ret;
}

/**
 * @brief  MMC all counter software reset.
 * @param  None
 * @retval int32_t:
 *           - LL_OK: Reset success
 *           - LL_ERR_TIMEOUT: Reset timeout
 */
int32_t ETH_MMC_CounterReset(void)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_OK;

    WRITE_REG32(bCM_ETH->MMC_MMCCTLR_b.CRST, 1U);
    u32Count = ETH_WR_REG_TIMEOUT * (HCLK_VALUE / 20000UL);
    while (0UL != READ_REG32(bCM_ETH->MMC_MMCCTLR_b.CRST)) {
        if (0UL == u32Count) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
        u32Count--;
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable the reset of all MMC counter after reading.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_MMC_ResetAfterReadCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_ETH->MMC_MMCCTLR_b.ROR, enNewState);
}

/**
 * @brief  Enable or disable MMC function.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_MMC_Cmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        WRITE_REG32(bCM_ETH->MMC_MMCCTLR_b.MCF, DISABLE);
    } else {
        WRITE_REG32(bCM_ETH->MMC_MMCCTLR_b.MCF, ENABLE);
    }
}

/**
 * @brief  Enable or disable MMC transmit interrupt.
 * @param  [in] u32IntType              MMC interrupt source
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MMC_INT_TXEDEIM:  Tx excessive deferral error frame interrupt
 *           @arg ETH_MMC_INT_TXUGIM:   Tx unicast good frame interrupt
 *           @arg ETH_MMC_INT_TXCAEIM:  Tx carrier error frame interrupt
 *           @arg ETH_MMC_INT_TXECEIM:  Tx excessive collision error frame interrupt
 *           @arg ETH_MMC_INT_TXLCEIM:  Tx deferral collision error frame interrupt
 *           @arg ETH_MMC_INT_TXDEEIM:  Tx deferral error frame interrupt
 *           @arg ETH_MMC_INT_TXMGIM:   Tx multicast good frame interrupt
 *           @arg ETH_MMC_INT_TXBGIM:   Tx broadcast good frame interrupt
 *           @arg ETH_MMC_INT_TX_ALL:   All of the above
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_MMC_TxIntCmd(uint32_t u32IntType, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_MMC_TX_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        CLR_REG32_BIT(CM_ETH->MMC_TITCTLR, u32IntType);
    } else {
        SET_REG32_BIT(CM_ETH->MMC_TITCTLR, u32IntType);
    }
}

/**
 * @brief  Enable or disable MMC receive interrupt.
 * @param  [in] u32IntType              MMC interrupt source
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MMC_INT_RXOEIM:   Rx out of scope error frame interrupt
 *           @arg ETH_MMC_INT_RXLEIM:   Rx length error frame interrupt
 *           @arg ETH_MMC_INT_RXUGIM:   Rx unicast good frame interrupt
 *           @arg ETH_MMC_INT_RXREIM:   Rx short error frame interrupt
 *           @arg ETH_MMC_INT_RXAEIM:   Rx alignment error frame interrupt
 *           @arg ETH_MMC_INT_RXCEIM:   Rx crc error frame interrupt
 *           @arg ETH_MMC_INT_RXMGIM:   Rx multicast good frame interrupt
 *           @arg ETH_MMC_INT_RXBGIM:   Rx broadcast good frame interrupt
 *           @arg ETH_MMC_INT_RX_ALL:   All of the above
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_MMC_RxIntCmd(uint32_t u32IntType, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_MMC_RX_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        CLR_REG32_BIT(CM_ETH->MMC_RITCTLR, u32IntType);
    } else {
        SET_REG32_BIT(CM_ETH->MMC_RITCTLR, u32IntType);
    }
}

/**
 * @brief  Get MMC flag transmit status.
 * @param  [in] u32Flag                 MMC flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MMC_FLAG_TXEDEIS: Tx excessive deferral error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_TXUGIS:  Tx unicast good frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_TXCAEIS: Tx carrier error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_TXECEIS: Tx excessive collision error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_TXLCEIS: Tx deferral collision error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_TXDEEIS: Tx deferral error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_TXMGIS:  Tx multicast good frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_TXBGIS:  Tx broadcast good frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_TX_ALL:  All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t ETH_MMC_GetTxStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_MMC_TX_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(CM_ETH->MMC_TRSSTSR, u32Flag))) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/**
 * @brief  Get MMC receive flag status.
 * @param  [in] u32Flag                 MMC flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MMC_FLAG_RXOEIS:  Rx out of scope error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_RXLEIS:  Rx length error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_RXUGIS:  Rx unicast good frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_RXREIS:  Rx short error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_RXAEIS:  Rx alignment error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_RXCEIS:  Rx crc error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_RXMGIS:  Rx multicast good frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_RXBGIS:  Rx broadcast good frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_RX_ALL:  All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t ETH_MMC_GetRxStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_MMC_RX_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(CM_ETH->MMC_REVSTSR, u32Flag))) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/**
 * @brief  Get MMC register.
 * @param  [in] u32Reg                  MMC statistics register
 *         This parameter can be one of the following values:
 *           @arg ETH_MMC_REG_TXBRGFR:  Tx broadcast good frame Statistical Register
 *           @arg ETH_MMC_REG_TXMUGFR:  Tx multicast good frame Statistical Register
 *           @arg ETH_MMC_REG_TXDEEFR:  Tx deferral error frame Statistical Register
 *           @arg ETH_MMC_REG_TXLCEFR:  Tx deferral collision error frame Statistical Register
 *           @arg ETH_MMC_REG_TXECEFR:  Tx excessive collision error frame Statistical Register
 *           @arg ETH_MMC_REG_TXCAEFR:  Tx carrier error frame Statistical Register
 *           @arg ETH_MMC_REG_TXUNGFR:  Tx unicast good frame Statistical Register
 *           @arg ETH_MMC_REG_TXEDEFR:  Tx excessive deferral error frame Statistical Register
 *           @arg ETH_MMC_REG_RXBRGFR:  Rx broadcast good frame Statistical Register
 *           @arg ETH_MMC_REG_RXMUGFR:  Rx multicast good frame Statistical Register
 *           @arg ETH_MMC_REG_RXCREFR:  Rx crc error frame Statistical Register
 *           @arg ETH_MMC_REG_RXALEFR:  Rx alignment error frame Statistical Register
 *           @arg ETH_MMC_REG_RXRUEFR:  Rx short error frame Statistical Register
 *           @arg ETH_MMC_REG_RXUNGFR:  Rx unicast good frame Statistical Register
 *           @arg ETH_MMC_REG_RXLEEFR:  Rx length error frame Statistical Register
 *           @arg ETH_MMC_REG_RXOREFR:  Rx out of scope error frame Statistical Register
 * @retval uint32_t                     MMC statistics Register value
 */
uint32_t ETH_MMC_GetReg(uint32_t u32Reg)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_MMC_REG(u32Reg));

    return (*(__IO uint32_t *)((uint32_t)(&CM_ETH->MAC_CONFIGR) + u32Reg));
}

/******************************************************************************/
/*                                PTP Functions                               */
/******************************************************************************/
/**
 * @brief  De-Initialize PTP.
 * @param  None
 * @retval None
 */
void ETH_PTP_DeInit(void)
{
    WRITE_REG32(CM_ETH->PTP_TSPCTLR, 0x00002000UL);
    WRITE_REG32(CM_ETH->PTP_TSPADDR, 0UL);
    WRITE_REG32(CM_ETH->PTP_TSPNSAR, 0UL);
    WRITE_REG32(CM_ETH->PTP_TMUSECR, 0UL);
    WRITE_REG32(CM_ETH->PTP_TMUNSER, 0UL);
}

/**
 * @brief  Initialize PTP.
 * @param  [in] pstcPtpInit             Pointer to a @ref stc_eth_ptp_init_t structure
 * @retval int32_t:
 *           - LL_OK: PTP Initialize success
 *           - LL_ERR: PTP Initialize failed
 *           - LL_ERR_INVD_PARAM: pstcPtpInit == NULL
 */
int32_t ETH_PTP_Init(const stc_eth_ptp_init_t *pstcPtpInit)
{
    int32_t i32Ret;

    if (NULL == pstcPtpInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_PTP_DEST_ADDR_FILTER(pstcPtpInit->u32DestAddrFilter));
        DDL_ASSERT(IS_ETH_PTP_DATAGRAM_VER(pstcPtpInit->u32DatagramVersion));
        DDL_ASSERT(IS_ETH_PTP_SUBSEC_SCALE(pstcPtpInit->u32SubsecScale));
        DDL_ASSERT(IS_ETH_PTP_DATAGRAM_TYPE(pstcPtpInit->u32SnapDatagramType));
        DDL_ASSERT(IS_ETH_PTP_FRAME_TYPE(pstcPtpInit->u32SnapFrameType));
        DDL_ASSERT(IS_ETH_PTP_CALIB_MD(pstcPtpInit->u32CalibMode));
        DDL_ASSERT(IS_ETH_PTP_SUB_SEC(pstcPtpInit->u32SubsecInitValue));

        /* Enable timestamp function */
        WRITE_REG32(bCM_ETH->PTP_TSPCTLR_b.TSPEN, (uint32_t)ENABLE);
        /* Set addend value registers */
        WRITE_REG32(CM_ETH->PTP_TSPNSAR, pstcPtpInit->u8SubsecAddend);
        WRITE_REG32(CM_ETH->PTP_TSPADDR, pstcPtpInit->u32BasicAddend);
        i32Ret = ETH_PTP_UpdateBasicAddend();
        if (LL_OK == i32Ret) {
            /* Set timestamp control register */
            MODIFY_REG32(CM_ETH->PTP_TSPCTLR, ETH_PTP_TSPCTLR_CLR_MASK,
                         (pstcPtpInit->u32DestAddrFilter | pstcPtpInit->u32SnapDatagramType |
                          pstcPtpInit->u32SnapFrameType  | pstcPtpInit->u32DatagramVersion  |
                          pstcPtpInit->u32SubsecScale    | pstcPtpInit->u32CalibMode));
            /* Set initialize value */
            WRITE_REG32(CM_ETH->PTP_TMUSECR, pstcPtpInit->u32SecInitValue);
            WRITE_REG32(CM_ETH->PTP_TMUNSER, pstcPtpInit->u32SubsecInitValue);
            i32Ret = ETH_PTP_SysTimeInit();
            if (LL_OK != i32Ret) {
                i32Ret = LL_ERR;
            }
        } else {
            i32Ret = LL_ERR;
        }
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_eth_ptp_init_t to default values.
 * @param  [out] pstcPtpInit            Pointer to a @ref stc_eth_ptp_init_t structure
 * @retval int32_t:
 *           - LL_OK: Structure Initialize success
 *           - LL_ERR_INVD_PARAM: pstcPtpInit == NULL
 */
int32_t ETH_PTP_StructInit(stc_eth_ptp_init_t *pstcPtpInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcPtpInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcPtpInit->u32DestAddrFilter      = ETH_PTP_DEST_ADDR_FILTER_DISABLE;
        pstcPtpInit->u32SnapDatagramType    = ETH_PTP_DATAGRAM_TYPE_SYNC_FOLLOW_DELAY;
        pstcPtpInit->u32SnapFrameType       = ETH_PTP_FRAME_TYPE_IPV4_FRAME;
        pstcPtpInit->u32DatagramVersion     = ETH_PTP_DATAGRAM_VER_IEEE1588V1;
        pstcPtpInit->u32SubsecScale         = ETH_PTP_SUBSEC_SCALE_HEX;
        pstcPtpInit->u32CalibMode           = ETH_PTP_CALIB_MD_COARSE;
        pstcPtpInit->u32BasicAddend         = 0UL;
        pstcPtpInit->u8SubsecAddend         = 0U;
        pstcPtpInit->u32SecInitValue        = 0UL;
        pstcPtpInit->u32SubsecInitValue     = 0UL;
    }

    return i32Ret;
}

/**
 * @brief  Set PTP snapshot datagram type.
 * @param  [in] u32DatagramType         Snapshot datagram type
 *         This parameter can be one of the following values:
 *           @arg ETH_PTP_DATAGRAM_TYPE_SYNC_FOLLOW_DELAY:         SYNC Follow_Up Delay_Req Delay_Resp
 *           @arg ETH_PTP_DATAGRAM_TYPE_SYNC:                      SYNC
 *           @arg ETH_PTP_DATAGRAM_TYPE_DELAY:                     Delay_Req
 *           @arg ETH_PTP_DATAGRAM_TYPE_SYNC_FOLLOW_DELAY_PDELAY:  SYNC Follow_Up Delay_Req Delay_Resp Pdelay_Req Pdelay_Resp Pdelay_Resp_Follow_Up
 *           @arg ETH_PTP_DATAGRAM_TYPE_SYNC_PDELAY:               SYNC Pdelay_Req Pdelay_Resp
 *           @arg ETH_PTP_DATAGRAM_TYPE_DELAY_PDELAY:              Delay_Req Pdelay_Req Pdelay_Resp
 *           @arg ETH_PTP_DATAGRAM_TYPE_SYNC_DELAY:                SYNC Delay_Req
 *           @arg ETH_PTP_DATAGRAM_TYPE_PDELAY:                    Pdelay_Req Pdelay_Resp
 * @retval None
 */
void ETH_PTP_SetSnapDatagramType(uint32_t u32DatagramType)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_PTP_DATAGRAM_TYPE(u32DatagramType));

    MODIFY_REG32(CM_ETH->PTP_TSPCTLR, ETH_PTP_TSPCTLR_TSPMTSEL, u32DatagramType);
}

/**
 * @brief  Set PTP snapshot frame type.
 * @param  [in] u32FrameType            Snapshot frame type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_PTP_FRAME_TYPE_IPV4_FRAME:    snapshot of IPv4 frame
 *           @arg ETH_PTP_FRAME_TYPE_IPV6_FRAME:    snapshot of IPv6 frame
 *           @arg ETH_PTP_FRAME_TYPE_ETH_FRAME:     snapshot of PTP over ethernet frame
 *           @arg ETH_PTP_FRAME_TYPE_RX_FRAME:      snapshot of all received frame
 *           @arg ETH_PTP_FRAME_TYPE_ALL:           All of the above
 * @retval None
 */
void ETH_PTP_SetSnapFrameType(uint32_t u32FrameType)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_PTP_FRAME_TYPE(u32FrameType));

    MODIFY_REG32(CM_ETH->PTP_TSPCTLR,
                 (ETH_PTP_TSPCTLR_TSPOVIPV4 | ETH_PTP_TSPCTLR_TSPOVIPV6 | ETH_PTP_TSPCTLR_TSPOVETH |
                  ETH_PTP_TSPCTLR_TSPEALL), u32FrameType);
}

/**
 * @brief  Set PTP timestamp calibration mode.
 * @param  [in] u32CalibMode            Timestamp calibration mode
 *         This parameter can be one of the following values:
 *           @arg ETH_PTP_CALIB_MD_COARSE:  Coarse calibration
 *           @arg ETH_PTP_CALIB_MD_FINE:    Fine calibration
 * @retval None
 */
void ETH_PTP_SetCalibMode(uint32_t u32CalibMode)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_PTP_CALIB_MD(u32CalibMode));

    WRITE_REG32(bCM_ETH->PTP_TSPCTLR_b.TSPUPSEL, u32CalibMode >> ETH_PTP_TSPCTLR_TSPUPSEL_POS);
}

/**
 * @brief  Update PTP timestamp basic addend value.
 * @note   Update Timestamp addend value by basic addend register.
 * @param  None
 * @retval int32_t:
 *           - LL_OK: Update timestamp addend value success
 *           - LL_ERR: Current state cannot be updated
 *           - LL_ERR_TIMEOUT: Update timeout
 */
int32_t ETH_PTP_UpdateBasicAddend(void)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_ERR;

    if (0UL == READ_REG32(bCM_ETH->PTP_TSPCTLR_b.TSPADUP)) {
        WRITE_REG32(bCM_ETH->PTP_TSPCTLR_b.TSPADUP, 1U);
        u32Count = ETH_WR_REG_TIMEOUT * (HCLK_VALUE / 20000UL);
        while (0UL != READ_REG32(bCM_ETH->PTP_TSPCTLR_b.TSPADUP)) {
            if (0UL == u32Count) {
                i32Ret = LL_ERR_TIMEOUT;
                break;
            }
            u32Count--;
        }

        if (LL_ERR_TIMEOUT != i32Ret) {
            i32Ret = LL_OK;
        }
    }

    return i32Ret;
}

/**
 * @brief  Update PTP timestamp system time.
 * @note   Update Timestamp system time by update second and update subsecond registers.
 * @param  None
 * @retval int32_t:
 *           - LL_OK: Update timestamp system time success
 *           - LL_ERR: Current state cannot be updated
 *           - LL_ERR_TIMEOUT: Update timeout
 */
int32_t ETH_PTP_UpdateSysTime(void)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_ERR;

    if (0UL == READ_REG32(bCM_ETH->PTP_TSPCTLR_b.TSPINI)) {
        if (0UL == READ_REG32(bCM_ETH->PTP_TSPCTLR_b.TSPUP)) {
            WRITE_REG32(bCM_ETH->PTP_TSPCTLR_b.TSPUP, 1U);
            u32Count = ETH_WR_REG_TIMEOUT * (HCLK_VALUE / 20000UL);
            while (0UL != READ_REG32(bCM_ETH->PTP_TSPCTLR_b.TSPUP)) {
                if (0UL == u32Count) {
                    i32Ret = LL_ERR_TIMEOUT;
                    break;
                }
                u32Count--;
            }

            if (LL_ERR_TIMEOUT != i32Ret) {
                i32Ret = LL_OK;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Initialize PTP timestamp system time.
 * @note   Initialize Timestamp system time by update second and update subsecond registers.
 * @param  None
 * @retval int32_t:
 *           - LL_OK: Initialize timestamp system time success
 *           - LL_ERR: Current state cannot be initialized
 *           - LL_ERR_TIMEOUT: Initialize timeout
 */
int32_t ETH_PTP_SysTimeInit(void)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_ERR;

    if (0UL == READ_REG32(bCM_ETH->PTP_TSPCTLR_b.TSPINI)) {
        WRITE_REG32(bCM_ETH->PTP_TSPCTLR_b.TSPINI, 1U);
        u32Count = ETH_WR_REG_TIMEOUT * (HCLK_VALUE / 20000UL);
        while (0UL != READ_REG32(bCM_ETH->PTP_TSPCTLR_b.TSPINI)) {
            if (0UL == u32Count) {
                i32Ret = LL_ERR_TIMEOUT;
                break;
            }
            u32Count--;
        }

        if (LL_ERR_TIMEOUT != i32Ret) {
            i32Ret = LL_OK;
        }
    }

    return i32Ret;
}

/**
 * @brief  Get PTP timestamp system time.
 * @param  [out] pu32Sec                Pointer to Timestamp system time of Second
 * @param  [out] pu32Subsec             Pointer to Timestamp system time of Subsecond
 * @retval int32_t:
 *           - LL_OK: Get timestamp system time success
 *           - LL_ERR_INVD_PARAM: pu32Sec == NULL or pu32Subsec == NULL
 */
int32_t ETH_PTP_GetSysTime(uint32_t *pu32Sec, uint32_t *pu32Subsec)
{
    int32_t i32Ret = LL_OK;

    if ((NULL == pu32Sec) || (NULL == pu32Subsec)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        *pu32Sec    = READ_REG32(CM_ETH->PTP_TMSSECR);
        *pu32Subsec = READ_REG32(CM_ETH->PTP_TMSNSER);
    }

    return i32Ret;
}

/**
 * @brief  Set PTP timestamp addend value.
 * @param  [in] u32BasicAddend          Timestamp basic addend value (Between 0x0 and 0xFFFFFFFF)
 * @param  [in] u8SubsecAddend          Timestamp subsecond addend value (Between 0x0 and 0xFF)
 * @retval None
 */
void ETH_PTP_SetBasicAddend(uint32_t u32BasicAddend, uint8_t u8SubsecAddend)
{
    WRITE_REG32(CM_ETH->PTP_TSPADDR, u32BasicAddend);
    WRITE_REG32(CM_ETH->PTP_TSPNSAR, u8SubsecAddend);
}

/**
 * @brief  Get PTP timestamp addend value.
 * @param  [out] pu32BasicAddend        Pointer to basic addend value
 * @param  [out] pu8SubsecAddend        Pointer to subsecond addend value
 * @retval int32_t:
 *           - LL_OK: Get timestamp addend value success
 *           - LL_ERR_INVD_PARAM: pu32BasicAddend == NULL or pu8SubsecAddend == NULL
 */
int32_t ETH_PTP_GetBasicAddend(uint32_t *pu32BasicAddend, uint8_t *pu8SubsecAddend)
{
    int32_t i32Ret = LL_OK;

    if ((NULL == pu32BasicAddend) || (NULL == pu8SubsecAddend)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        *pu32BasicAddend = READ_REG32(CM_ETH->PTP_TSPADDR);
        *pu8SubsecAddend = (uint8_t)(READ_REG32(CM_ETH->PTP_TSPNSAR) & ETH_PTP_TSPNSAR_TSPNSEADD);
    }

    return i32Ret;
}

/**
 * @brief  Set PTP timestamp update time.
 * @param  [in] u32Sign                 Timestamp Update Sign
 *           @arg ETH_PTP_TIME_UPDATE_SIGN_MINUS:   Minus
 *           @arg ETH_PTP_TIME_UPDATE_SIGN_PLUS:    Plus
 * @param  [in] u32Sec                  Update time of Second (Between 0x0 and 0xFFFFFFFF)
 * @param  [in] u32Subsec               Update time of Subsecond (Between 0x0 and 0x7FFFFFFF)
 * @retval None
 */
void ETH_PTP_SetUpdateTime(uint32_t u32Sign, uint32_t u32Sec, uint32_t u32Subsec)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_PTP_TIME_UPDATE_SIGN(u32Sign));
    DDL_ASSERT(IS_ETH_PTP_SUB_SEC(u32Subsec));

    WRITE_REG32(CM_ETH->PTP_TMUSECR, u32Sec);
    WRITE_REG32(CM_ETH->PTP_TMUNSER, (u32Sign | u32Subsec));
}

/**
 * @brief  Enable or disable PTP function.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_PTP_Cmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_ETH->PTP_TSPCTLR_b.TSPEN, enNewState);
}

/**
 * @brief  Enable or disable PTP interrupt.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ETH_PTP_IntCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_ETH->PTP_TSPCTLR_b.TSPINT, enNewState);
}

/**
 * @brief  Get PTP flag status.
 * @param  [in] u32Flag                 PTP flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_PTP_FLAG_TSERR1:  Target time 1 error
 *           @arg ETH_PTP_FLAG_TSTAR1:  Target time 1 reached
 *           @arg ETH_PTP_FLAG_TSERR0:  Target time 0 error
 *           @arg ETH_PTP_FLAG_TSTAR0:  Target time 0 reached
 *           @arg ETH_PTP_FLAG_TSOVF:   System time overflow
 *           @arg ETH_PTP_FLAG_ALL:     All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t ETH_PTP_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_PTP_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(CM_ETH->PTP_TSPSTSR, u32Flag))) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/******************************************************************************/
/*                            PTP PPS Functions                               */
/******************************************************************************/
/**
 * @brief  De-Initialize PTP PPS.
 * @param  [in] u8Ch                    PPS output channel
 *         This parameter can be one of the following values:
 *           @arg ETH_PPS_CH0:          PPS Channel 0
 *           @arg ETH_PPS_CH1:          PPS Channel 1
 * @retval None
 */
void ETH_PPS_DeInit(uint8_t u8Ch)
{
    uint32_t u32ShiftStep = 0UL;
    uint32_t u32ShiftBit = 0UL;
    __IO uint32_t *PTP_TMTSECR;
    __IO uint32_t *PTP_TMTNSER;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_PPS_CH(u8Ch));

    if (ETH_PPS_CH1 == u8Ch) {
        u32ShiftBit  = ETH_PTP_PPSCTLR_PPSFRE1_POS;
        u32ShiftStep = ETH_PTP_PPS1_TIME_REG_ADDR_SHIFT;
    }
    CLR_REG32_BIT(CM_ETH->PTP_PPSCTLR,
                  ((ETH_PTP_PPSCTLR_PPSFRE0 | ETH_PTP_PPSCTLR_PPSOMD | ETH_PTP_PPSCTLR_TT0SEL) << u32ShiftBit));
    /* Clear target time registers */
    PTP_TMTSECR = ETH_PTP_TMTSECR_ADDR(u32ShiftStep);
    PTP_TMTNSER = ETH_PTP_TMTNSER_ADDR(u32ShiftStep);
    WRITE_REG32(*PTP_TMTSECR, 0UL);
    WRITE_REG32(*PTP_TMTNSER, 0UL);
}

/**
 * @brief  Initialize PTP PPS.
 * @param  [in] u8Ch                    PPS output channel
 *         This parameter can be one of the following values:
 *           @arg ETH_PPS_CH0:          PPS Channel 0
 *           @arg ETH_PPS_CH1:          PPS Channel 1
 * @param  [in] pstcPpsInit             Pointer to a @ref stc_eth_pps_config_t structure
 * @retval int32_t:
 *           - LL_OK: PPS Initialize success
 *           - LL_ERR_INVD_PARAM: pstcPpsInit == NULL
 */
int32_t ETH_PPS_Init(uint8_t u8Ch, const stc_eth_pps_config_t *pstcPpsInit)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32ShiftStep = 0UL;
    uint32_t u32ShiftBit = 0UL;
    uint32_t u32RegVal;
    __IO uint32_t *PTP_TMTSECR;
    __IO uint32_t *PTP_TMTNSER;

    if (NULL == pstcPpsInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_PPS_CH(u8Ch));
        DDL_ASSERT(IS_ETH_PTP_SUB_SEC(pstcPpsInit->u32SubsecValue));
        DDL_ASSERT(IS_ETH_PPS_TRIG_FUNC(pstcPpsInit->u32TriggerFunc));
        DDL_ASSERT(IS_ETH_PPS_OUTPUT_MD(pstcPpsInit->u32OutputMode));
        DDL_ASSERT(IS_ETH_PPS_OUTPUT_FREQ(pstcPpsInit->u32OutputFreq));
        DDL_ASSERT(IS_ETH_PPS1_COMPLEX_FUNC(u8Ch, pstcPpsInit->u32OutputMode, pstcPpsInit->u32OutputFreq));

        u32RegVal = pstcPpsInit->u32OutputFreq | pstcPpsInit->u32TriggerFunc;
        if (ETH_PPS_CH1 == u8Ch) {
            u32ShiftBit  = ETH_PTP_PPSCTLR_PPSFRE1_POS;
            u32ShiftStep = ETH_PTP_PPS1_TIME_REG_ADDR_SHIFT;
        } else {
            u32RegVal |= pstcPpsInit->u32OutputMode;
        }
        MODIFY_REG32(CM_ETH->PTP_PPSCTLR,
                     ((ETH_PTP_PPSCTLR_PPSFRE0 | ETH_PTP_PPSCTLR_PPSOMD | ETH_PTP_PPSCTLR_TT0SEL) << u32ShiftBit),
                     (u32RegVal << u32ShiftBit));
        /* Set target time registers */
        PTP_TMTSECR = ETH_PTP_TMTSECR_ADDR(u32ShiftStep);
        PTP_TMTNSER = ETH_PTP_TMTNSER_ADDR(u32ShiftStep);
        WRITE_REG32(*PTP_TMTSECR, pstcPpsInit->u32SecValue);
        WRITE_REG32(*PTP_TMTNSER, pstcPpsInit->u32SubsecValue);
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_eth_pps_config_t to default values.
 * @param  [out] pstcPpsInit            Pointer to a @ref stc_eth_pps_config_t structure
 * @retval int32_t:
 *           - LL_OK: Structure Initialize success
 *           - LL_ERR_INVD_PARAM: pstcPpsInit == NULL
 */
int32_t ETH_PPS_StructInit(stc_eth_pps_config_t *pstcPpsInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcPpsInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcPpsInit->u32TriggerFunc = ETH_PPS_TRIG_FUNC_INT_EVT;
        pstcPpsInit->u32OutputMode  = ETH_PPS_OUTPUT_MD_ONCE;
        pstcPpsInit->u32OutputFreq  = ETH_PPS_OUTPUT_ONE_PULSE;
        pstcPpsInit->u32SecValue    = 0UL;
        pstcPpsInit->u32SubsecValue = 0UL;
    }

    return i32Ret;
}

/**
 * @brief  Set PTP Target time function.
 * @param  [in] u8Ch                    PPS output channel
 *         This parameter can be one of the following values:
 *           @arg ETH_PPS_CH0:          PPS Channel 0
 *           @arg ETH_PPS_CH1:          PPS Channel 1
 * @param  [in] u32Sec                  Target time of Second (Between 0x0 and 0xFFFFFFFF)
 * @param  [in] u32Subsec               Target time of Subsecond (Between 0x0 and 0x7FFFFFFF)
 * @retval None
 */
void ETH_PPS_SetTargetTime(uint8_t u8Ch, uint32_t u32Sec, uint32_t u32Subsec)
{
    uint32_t u32ShiftStep = 0UL;
    __IO uint32_t *PTP_TMTSECR;
    __IO uint32_t *PTP_TMTNSER;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_PPS_CH(u8Ch));
    DDL_ASSERT(IS_ETH_PTP_SUB_SEC(u32Subsec));

    if (ETH_PPS_CH1 == u8Ch) {
        u32ShiftStep = ETH_PTP_PPS1_TIME_REG_ADDR_SHIFT;
    }
    PTP_TMTSECR = ETH_PTP_TMTSECR_ADDR(u32ShiftStep);
    PTP_TMTNSER = ETH_PTP_TMTNSER_ADDR(u32ShiftStep);
    WRITE_REG32(*PTP_TMTSECR, u32Sec);
    WRITE_REG32(*PTP_TMTNSER, u32Subsec);
}

/**
 * @brief  Set PTP Target time function.
 * @param  [in] u8Ch                    PPS output channel
 *         This parameter can be one of the following values:
 *           @arg ETH_PPS_CH0:          PPS Channel 0
 *           @arg ETH_PPS_CH1:          PPS Channel 1
 * @param  [in] u32Func                 Arrival time trigger the function
 *         This parameter can be one of the following values:
 *           @arg ETH_PPS_TRIG_FUNC_INT_EVT:      Interrupt output event
 *           @arg ETH_PPS_TRIG_FUNC_INT_PPS_EVT:  Interrupt out event and PPS single output event
 *           @arg ETH_PPS_TRIG_FUNC_PPS_EVT:      PPS Single output event
 * @retval None
 */
void ETH_PPS_SetTriggerFunc(uint8_t u8Ch, uint32_t u32Func)
{
    uint32_t u32ShiftBit = 0UL;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_PPS_CH(u8Ch));
    DDL_ASSERT(IS_ETH_PPS_TRIG_FUNC(u32Func));

    if (ETH_PPS_CH1 == u8Ch) {
        u32ShiftBit = ETH_PTP_PPSCTLR_PPSFRE1_POS;
    }
    MODIFY_REG32(CM_ETH->PTP_PPSCTLR, (ETH_PTP_PPSCTLR_TT0SEL << u32ShiftBit), (u32Func << u32ShiftBit));
}

/**
 * @brief  Set PTP PPS0 output mode.
 * @param  [in] u32Mode                 PPS output mode
 *         This parameter can be one of the following values:
 *           @arg ETH_PPS_OUTPUT_MD_CONTINUE:   Continuous output mode
 *           @arg ETH_PPS_OUTPUT_MD_ONCE:       Single output mode
 * @retval None
 */
void ETH_PPS_SetPps0OutputMode(uint32_t u32Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_PPS_OUTPUT_MD(u32Mode));

    WRITE_REG32(bCM_ETH->PTP_PPSCTLR_b.PPSOMD, u32Mode >> ETH_PTP_PPSCTLR_PPSOMD_POS);
}

/**
 * @brief  Set PTP PPS0 output frequency.
 * @param  [in] u32Freq                 PPS output frequency
 *         This parameter can be one of the following values:
 *           @arg ETH_PPS_OUTPUT_FREQ_1HZ:      Ouput pulse is 1HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_FREQ_2HZ:      Ouput pulse is 2HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_FREQ_4HZ:      Ouput pulse is 4HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_FREQ_8HZ:      Ouput pulse is 8HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_FREQ_16HZ:     Ouput pulse is 16HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_FREQ_32HZ:     Ouput pulse is 32HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_FREQ_64HZ:     Ouput pulse is 64HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_FREQ_128HZ:    Ouput pulse is 128HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_FREQ_256HZ:    Ouput pulse is 256HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_FREQ_512HZ:    Ouput pulse is 512HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_FREQ_1024HZ:   Ouput pulse is 1024HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_FREQ_2048HZ:   Ouput pulse is 2048HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_FREQ_4096HZ:   Ouput pulse is 4096HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_FREQ_8192HZ:   Ouput pulse is 8192HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_FREQ_16384HZ:  Ouput pulse is 16384HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_FREQ_32768HZ:  Ouput pulse is 32768HZ in continuous ouput mode
 *           @arg ETH_PPS_OUTPUT_ONE_PULSE:     One pulse is generated in single ouput mode
 * @retval None
 */
void ETH_PPS_SetPps0OutputFreq(uint32_t u32Freq)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_PPS_OUTPUT_FREQ(u32Freq));

    MODIFY_REG32(CM_ETH->PTP_PPSCTLR, ETH_PTP_PPSCTLR_PPSFRE0, u32Freq);
}

/**
 * @}
 */

#endif /* LL_ETH_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
