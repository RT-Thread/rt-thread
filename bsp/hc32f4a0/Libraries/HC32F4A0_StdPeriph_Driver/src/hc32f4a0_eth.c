/**
 *******************************************************************************
 * @file  hc32f4a0_eth.c
 * @brief This file provides firmware functions to manage the Ethernet MAC
 *        Controller(ETH).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
   2020-07-03       Yangjp          Optimize stc_eth_mac_init_t structure
   2020-08-11       Yangjp          Fixed a known potential risk in ETH_Init function
   2020-09-04       Yangjp          Optimize timeout handling in functions
   2020-11-26       Yangjp          Fixed a known potential risk in ETH_DMA_GetReceiveFrame_Interrupt function
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_eth.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_ETH ETH
 * @brief Initial Configuration Driver Library
 * @{
 */

#if (DDL_ETH_ENABLE == DDL_ON)

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

/* Ethernet MAC_IFCONFR register Mask */
#define ETH_MAC_IFCONFR_CLEAR_MASK                          (ETH_MAC_IFCONFR_RCKINV | ETH_MAC_IFCONFR_TCKINV)

/* Ethernet MAC_CONFIGR register Mask */
#define ETH_MAC_CONFIGR_CLEAR_MASK                          (0x72CF7EF0UL)

/* Ethernet MAC_FLOCTLR register Mask */
#define ETH_MAC_FLOCTLR_CLEAR_MASK                          (0xFFFF00BEUL)

/* Ethernet MAC_FLTCTLR register Mask */
#define ETH_MAC_FLTCTLR_CLEAR_MASK                          (0x802107FFUL)

/* Ethernet MAC_SMIADDR register Mask */
#define ETH_MAC_SMIADDR_CLEAR_MASK                          (0x0000FFC3UL)

/* Ethernet DMA_BUSMODR register Mask */
#define ETH_DMA_BUSMODR_CLEAR_MASK                          (0x0FFFFFFEUL)

/* Ethernet DMA_OPRMODR register Mask */
#define ETH_DMA_OPRMODR_CLEAR_MASK                          (0x0721C0FCUL)

/* Ethernet PTP_TSPCTLR register Mask */
#define ETH_PTP_TSPCTLR_CLEAR_MASK                          (0x0007FE02UL)

/* Ethernet MAC Address byte length */
#define ETH_MAC_ADDRESS_BYTE_LENGTH                         (6U)

/* Ethernet DMA Tx descriptors Collision Count Shift */
#define ETH_DMATXDESC_COLLISION_COUNTSHIFT                  (3UL)

/* Ethernet DMA Rx descriptors Frame Length Shift */
#define ETH_DMARXDESC_FRAME_LENGTHSHIFT                     (16UL)

/* Ethernet DMA Tx/Rx descriptors Buffer2 Size Shift */
#define ETH_DMADESC_BUFFER2_SIZESHIFT                       (16UL)

/* Ethernet Remote Wake-up frame register length */
#define ETH_WAKEUP_REGISTER_LENGTH                          (8U)

/* Ethernet PTP PPS channel 1 time register address Shift */
#define ETH_PTP_PPS1_TIME_REG_ADDRSHIFT                     (0x64U)

/* Wait timeout(ms) */
#define ETH_TIMEOUT_WRITE_REGISTER                          (50UL)
#define ETH_TIMEOUT_SOFTWARE_RESET                          (200UL)
#define ETH_TIMEOUT_LINK_STATUS                             (500UL)
#define ETH_TIMEOUT_AUTONEGO_COMPLETE                       (1000UL)


/**
 * @defgroup ETH_MAC_Address_Register ETH MAC Address Register
 * @brief Get the specified register address of the ETH MAC Address
 * @{
 */
#define ETH_MAC_MACADHRx(__SHIFT__)         ((uint32_t)(&(M4_ETH->MAC_MACADHR0)) + (uint32_t)(__SHIFT__))
#define ETH_MAC_MACADLRx(__SHIFT__)         ((uint32_t)(&(M4_ETH->MAC_MACADLR0)) + (uint32_t)(__SHIFT__))
/**
 * @}
 */

/**
 * @defgroup ETH_PTP_Register ETH PTP Register
 * @brief Get the specified register address of the ETH PTP PPS channel
 * @{
 */
#define ETH_PTP_TMTSECRx(__SHIFT__)         ((uint32_t)(&(M4_ETH->PTP_TMTSECR0)) + (uint32_t)(__SHIFT__))
#define ETH_PTP_TMTNSERx(__SHIFT__)         ((uint32_t)(&(M4_ETH->PTP_TMTNSER0)) + (uint32_t)(__SHIFT__))
/**
 * @}
 */

/**
 * @defgroup ETH_Check_Parameters_Validity ETH Check Parameters Validity
 * @{
 */
#define IS_ETH_PHY_ADDRESS(x)                               ((x) < 0x20U)

#define IS_ETH_PHY_REGISTER(x)                              ((x) < 0x20U)

#define IS_ETH_AUTO_NEGOTIATION(x)                                             \
(   ((x) == ETH_AUTO_NEGOTIATION_DISABLE)                   ||                 \
    ((x) == ETH_AUTO_NEGOTIATION_ENABLE))

#define IS_ETH_MAC_CHECKSUM_MODE(x)                                            \
(   ((x) == ETH_MAC_CHECKSUM_MODE_SOFTWARE)                 ||                 \
    ((x) == ETH_MAC_CHECKSUM_MODE_HARDWARE))

#define IS_ETH_RX_MODE(x)                                                      \
(   ((x) == ETH_RX_MODE_POLLING)                            ||                 \
    ((x) == ETH_RX_MODE_INTERRUPT))

#define IS_ETH_MAC_MEDIA_INTERFACE(x)                                          \
(   ((x) == ETH_MAC_MEDIA_INTERFACE_MII)                    ||                 \
    ((x) == ETH_MAC_MEDIA_INTERFACE_RMII))

#define IS_ETH_MAC_SPEED(x)                                                    \
(   ((x) == ETH_MAC_SPEED_10M)                              ||                 \
    ((x) == ETH_MAC_SPEED_100M))

#define IS_ETH_MAC_DUPLEX_MODE(x)                                              \
(   ((x) == ETH_MAC_MODE_HALFDUPLEX)                        ||                 \
    ((x) == ETH_MAC_MODE_FULLDUPLEX))

#define IS_ETH_MAC_TX_CLK_POLARITY(x)                                          \
(   ((x) == ETH_MAC_TX_CLK_POLARITY_KEEP)                   ||                 \
    ((x) == ETH_MAC_TX_CLK_POLARITY_INVERSE))

#define IS_ETH_MAC_RX_REF_CLK_POLARITY(x)                                      \
(   ((x) == ETH_MAC_RX_REF_CLK_POLARITY_KEEP)               ||                 \
    ((x) == ETH_MAC_RX_REF_CLK_POLARITY_INVERSE))

#define IS_ETH_MAC_SA_MODE(x)                                                  \
(   ((x) == ETH_MAC_SA_MODE_BY_DMATXDESC)                   ||                 \
    ((x) == ETH_MAC_SA_MODE_INSTER_MACADDR0)                ||                 \
    ((x) == ETH_MAC_SA_MODE_REPLACE_MACADDR0)               ||                 \
    ((x) == ETH_MAC_SA_MODE_INSTER_MACADDR1)                ||                 \
    ((x) == ETH_MAC_SA_MODE_REPLACE_MACADDR1))

#define IS_ETH_MAC_TYPEFRAME_STRIP_FCS(x)                                      \
(   ((x) == ETH_MAC_TYPEFRAME_STRIP_FCS_DISABLE)            ||                 \
    ((x) == ETH_MAC_TYPEFRAME_STRIP_FCS_ENABLE))

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

#define IS_ETH_MAC_CARRIER_SENCE(x)                                            \
(   ((x) == ETH_MAC_CARRIER_SENCE_DISABLE)                  ||                 \
    ((x) == ETH_MAC_CARRIER_SENCE_ENABLE))

#define IS_ETH_MAC_RECEIVE_OWN(x)                                              \
(   ((x) == ETH_MAC_RECEIVE_OWN_DISABLE)                    ||                 \
    ((x) == ETH_MAC_RECEIVE_OWN_ENABLE))

#define IS_ETH_MAC_CHECKSUM_OFFLAOD(x)                                         \
(   ((x) == ETH_MAC_CHECKSUM_OFFLAOD_DISABLE)               ||                 \
    ((x) == ETH_MAC_CHECKSUM_OFFLAOD_ENABLE))

#define IS_ETH_MAC_RETRY_TRANSMIT(x)                                           \
(   ((x) == ETH_MAC_RETRY_TRANSMIT_DISABLE)                 ||                 \
    ((x) == ETH_MAC_RETRY_TRANSMIT_ENABLE))

#define IS_ETH_MAC_AUTO_STRIP_PAD_FCS(x)                                       \
(   ((x) == ETH_MAC_AUTO_STRIP_PAD_FCS_DISABLE)             ||                 \
    ((x) == ETH_MAC_AUTO_STRIP_PAD_FCS_ENABLE))

#define IS_ETH_MAC_BACKOFF_LIMIT(x)                                            \
(   ((x) == ETH_MAC_BACKOFF_LIMIT_10)                       ||                 \
    ((x) == ETH_MAC_BACKOFF_LIMIT_8)                        ||                 \
    ((x) == ETH_MAC_BACKOFF_LIMIT_4)                        ||                 \
    ((x) == ETH_MAC_BACKOFF_LIMIT_1))

#define IS_ETH_MAC_DEFFERRAL_CHECK(x)                                          \
(   ((x) == ETH_MAC_DEFFERRAL_CHECK_DISABLE)                ||                 \
    ((x) == ETH_MAC_DEFFERRAL_CHECK_ENABLE))

#define IS_ETH_MAC_ZERO_QUANTA_PAUSE(x)                                        \
(   ((x) == ETH_MAC_ZERO_QUANTA_PAUSE_DISABLE)              ||                 \
    ((x) == ETH_MAC_ZERO_QUANTA_PAUSE_ENABLE))

#define IS_ETH_MAC_PAUSE_LOWTHRESHOLD(x)                                       \
(   ((x) == ETH_MAC_PAUSE_LOWTHRESHOLD_MINUS4)              ||                 \
    ((x) == ETH_MAC_PAUSE_LOWTHRESHOLD_MINUS28)             ||                 \
    ((x) == ETH_MAC_PAUSE_LOWTHRESHOLD_MINUS144)            ||                 \
    ((x) == ETH_MAC_PAUSE_LOWTHRESHOLD_MINUS256))

#define IS_ETH_MAC_UNICAST_PAUSEFRAME_DETECT(x)                                \
(   ((x) == ETH_MAC_UNICAST_PAUSEFRAME_DETECT_DISABLE)      ||                 \
    ((x) == ETH_MAC_UNICAST_PAUSEFRAME_DETECT_ENABLE))

#define IS_ETH_MAC_RECEIVE_FLOWCONTROL(x)                                      \
(   ((x) == ETH_MAC_RECEIVE_FLOWCONTROL_DISABLE)            ||                 \
    ((x) == ETH_MAC_RECEIVE_FLOWCONTROL_ENABLE))

#define IS_ETH_MAC_TRANSMIT_FLOWCONTROL(x)                                     \
(   ((x) == ETH_MAC_TRANSMIT_FLOWCONTROL_DISABLE)           ||                 \
    ((x) == ETH_MAC_TRANSMIT_FLOWCONTROL_ENABLE))

#define IS_ETH_MAC_RECEIVE_All(x)                                              \
(   ((x) == ETH_MAC_RECEIVE_All_DISABLE)                    ||                 \
    ((x) == ETH_MAC_RECEIVE_ALL_ENABLE))

#define IS_ETH_MAC_DROP_NOT_TCPUDP(x)                                          \
(   ((x) == ETH_MAC_DROP_NOT_TCPUDP_DISABLE)                ||                 \
    ((x) == ETH_MAC_DROP_NOT_TCPUDP_ENABLE))

#define IS_ETH_MAC_VLAN_TAG_FILTER(x)                                          \
(   ((x) == ETH_MAC_VLAN_TAG_FILTER_DISABLE)                ||                 \
    ((x) == ETH_MAC_VLAN_TAG_FILTER_ENABLE))

#define IS_ETH_MAC_SOURCE_ADDR_FILTER(x)                                       \
(   ((x) == ETH_MAC_SOURCE_ADDR_FILTER_DISABLE)             ||                 \
    ((x) == ETH_MAC_SOURCE_ADDR_FILTER_NORMAL)              ||                 \
    ((x) == ETH_MAC_SOURCE_ADDR_FILTER_INVERSE))

#define IS_ETH_MAC_PASS_CTRLFRAME(x)                                           \
(   ((x) == ETH_MAC_PASS_CTRLFRAME_BLOCK_ALL)               ||                 \
    ((x) == ETH_MAC_PASS_CTRLFRAME_FORWARD_NOTPAUSE_ALL)    ||                 \
    ((x) == ETH_MAC_PASS_CTRLFRAME_FORWARD_ALL)             ||                 \
    ((x) == ETH_MAC_PASS_CTRLFRAME_FORWARD_PASSADDRFILTER))

#define IS_ETH_MAC_BROADCASTFRAME_RECEPTION(x)                                 \
(   ((x) == ETH_MAC_BROADCASTFRAME_RECEPTION_DISABLE)       ||                 \
    ((x) == ETH_MAC_BROADCASTFRAME_RECEPTION_ENABLE))

#define IS_ETH_MAC_DESTINATION_ADDR_FILTER(x)                                  \
(   ((x) == ETH_MAC_DESTINATION_ADDR_FILTER_NORMAL)         ||                 \
    ((x) == ETH_MAC_DESTINATION_ADDR_FILTER_INVERSE))

#define IS_ETH_MAC_MULTICASTFRAME_FILTER(x)                                    \
(   ((x) == ETH_MAC_MULTICASTFRAME_FILTER_NONE)             ||                 \
    ((x) == ETH_MAC_MULTICASTFRAME_FILTER_PERFECT)          ||                 \
    ((x) == ETH_MAC_MULTICASTFRAME_FILTER_HASHTABLE)        ||                 \
    ((x) == ETH_MAC_MULTICASTFRAME_FILTER_PERFECTHASHTABLE))

#define IS_ETH_MAC_UNICASTFRAME_FILTER(x)                                      \
(   ((x) == ETH_MAC_UNICASTFRAME_FILTER_PERFECT)            ||                 \
    ((x) == ETH_MAC_UNICASTFRAME_FILTER_HASHTABLE)          ||                 \
    ((x) == ETH_MAC_UNICASTFRAME_FILTER_PERFECTHASHTABLE))

#define IS_ETH_MAC_PROMISCUOUS_MODE(x)                                         \
(   ((x) == ETH_MAC_PROMISCUOUS_MODE_DISABLE)               ||                 \
    ((x) == ETH_MAC_PROMISCUOUS_MODE_ENABLE))

#define IS_ETH_MAC_TXVLAN_MODE(x)                                              \
(   ((x) == ETH_MAC_TXVLAN_MODE_BY_DMATXDESC)               ||                 \
    ((x) == ETH_MAC_TXVLAN_MODE_BYPASS)                     ||                 \
    ((x) == ETH_MAC_TXVLAN_MODE_REMOVE_TAG)                 ||                 \
    ((x) == ETH_MAC_TXVLAN_MODE_INSERT_TAG)                 ||                 \
    ((x) == ETH_MAC_TXVLAN_MODE_REPLACE_TAG))

#define IS_ETH_MAC_RXVLAN_FILTER(x)                                            \
(   ((x) == ETH_MAC_RXVLAN_FILTER_NORMAL)                   ||                 \
    ((x) == ETH_MAC_RXVLAN_FILTER_INVERSE)                  ||                 \
    ((x) == ETH_MAC_RXVLAN_FILTER_NORMAL_HASHTABLE)         ||                 \
    ((x) == ETH_MAC_RXVLAN_FILTER_INVERSE_HASHTABLE))

#define IS_ETH_MAC_RXVLAN_COMPARISON(x)                                        \
(   ((x) == ETH_MAC_RXVLAN_COMPARISON_16BIT)                ||                 \
    ((x) == ETH_MAC_RXVLAN_COMPARISON_12BIT))

#define IS_ETH_MAC_L4_DESTPORT_FILTER(x)                                       \
(   ((x) == ETH_MAC_L4_DESTPORT_FILTER_DISABLE)             ||                 \
    ((x) == ETH_MAC_L4_DESTPORT_FILTER_NORMAL)              ||                 \
    ((x) == ETH_MAC_L4_DESTPORT_FILTER_INVERSE))

#define IS_ETH_MAC_L4_SOURCEPORT_FILTER(x)                                     \
(   ((x) == ETH_MAC_L4_SOURCEPORT_FILTER_DISABLE)           ||                 \
    ((x) == ETH_MAC_L4_SOURCEPORT_FILTER_NORMAL)            ||                 \
    ((x) == ETH_MAC_L4_SOURCEPORT_FILTER_INVERSE))

#define IS_ETH_MAC_L4_PORT_FILTER_PROTOCOL(x)                                  \
(   ((x) == ETH_MAC_L4_PORT_FILTER_PROTOCOL_TCP)            ||                 \
    ((x) == ETH_MAC_L4_PORT_FILTER_PROTOCOL_UDP))

#define IS_ETH_MAC_L3_DA_FILTER_MASK(x)                                        \
(   ((x) | ETH_MAC_L34CTLR_L3HDBM) == ETH_MAC_L34CTLR_L3HDBM)

#define IS_ETH_MAC_L3_SA_FILTER_MASK(x)                                        \
(   ((x) | ETH_MAC_L34CTLR_L3HSBM) == ETH_MAC_L34CTLR_L3HSBM)

#define IS_ETH_MAC_L3_DA_SA_FILTER_MASK(x)                                     \
(   0UL == ((x) & ((uint32_t)(~(ETH_MAC_L34CTLR_L3HSBM      |                  \
                                ETH_MAC_L34CTLR_L3HDBM_0    |                  \
                                ETH_MAC_L34CTLR_L3HDBM_1)))))

#define IS_ETH_MAC_L3_DA_FILTER(x)                                             \
(   ((x) == ETH_MAC_L3_DA_FILTER_DISABLE)                   ||                 \
    ((x) == ETH_MAC_L3_DA_FILTER_NORMAL)                    ||                 \
    ((x) == ETH_MAC_L3_DA_FILTER_INVERSE))

#define IS_ETH_MAC_L3_SA_FILTER(x)                                             \
(   ((x) == ETH_MAC_L3_SA_FILTER_DISABLE)                   ||                 \
    ((x) == ETH_MAC_L3_SA_FILTER_NORMAL)                    ||                 \
    ((x) == ETH_MAC_L3_SA_FILTER_INVERSE))

#define IS_ETH_MAC_L3_ADDR_FILTER_PROTOCOL(x)                                  \
(   ((x) == ETH_MAC_L3_ADDR_FILTER_PROTOCOL_IPV4)           ||                 \
    ((x) == ETH_MAC_L3_ADDR_FILTER_PROTOCOL_IPV6))

#define IS_ETH_MAC_INTERRUPT_FLAG(x)                                           \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(ETH_MAC_INT_FLAG_TSPIS     |                  \
                                 ETH_MAC_INT_FLAG_MMCTXIS   |                  \
                                 ETH_MAC_INT_FLAG_MMCRXIS   |                  \
                                 ETH_MAC_INT_FLAG_MMCIS     |                  \
                                 ETH_MAC_INT_FLAG_PMTIS))))))

#define IS_ETH_MAC_INTERRUPT(x)                                                \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(ETH_MAC_INT_TSPIM          |                  \
                                 ETH_MAC_INT_PMTIM))))))

#define IS_ETH_MAC_ADDRESS_NORMAL_INDEX(x)                                     \
(   ((x) == ETH_MAC_ADDRESS0)                               ||                 \
    ((x) == ETH_MAC_ADDRESS1)                               ||                 \
    ((x) == ETH_MAC_ADDRESS2)                               ||                 \
    ((x) == ETH_MAC_ADDRESS3)                               ||                 \
    ((x) == ETH_MAC_ADDRESS4))

#define IS_ETH_MAC_ADDRESS_SPECIAL_INDEX(x)                                    \
(   ((x) == ETH_MAC_ADDRESS1)                               ||                 \
    ((x) == ETH_MAC_ADDRESS2)                               ||                 \
    ((x) == ETH_MAC_ADDRESS3)                               ||                 \
    ((x) == ETH_MAC_ADDRESS4))

#define IS_ETH_MAC_ADDRESS_FILTER(x)                                           \
(   ((x) == ETH_MAC_ADDRESS_FILTER_DISABLE)                 ||                 \
    ((x) == ETH_MAC_ADDRESS_FILTER_PERFECT_DA)              ||                 \
    ((x) == ETH_MAC_ADDRESS_FILTER_PERFECT_SA))

#define IS_ETH_MAC_ADDRESS_MASK(x)                                             \
(   ((x) | ETH_MAC_ADDRESS_MASK_ALL) == ETH_MAC_ADDRESS_MASK_ALL)

#define IS_ETH_DMA_DESC_SKIP_LENGTH(x)                      ((x) < 0x20U)

#define IS_ETH_DMA_BURST_MODE(x)                                               \
(   ((x) == ETH_DMA_BURST_MODE_NORMAL)                      ||                 \
    ((x) == ETH_DMA_BURST_MODE_FIXED)                       ||                 \
    ((x) == ETH_DMA_BURST_MODE_MIXED))

#define IS_ETH_DMA_ADDRESS_ALIGN(x)                                            \
(   ((x) == ETH_DMA_ADDRESS_ALIGN_DISABLE)                  ||                 \
    ((x) == ETH_DMA_ADDRESS_ALIGN_ENABLE))

#define IS_ETH_DMA_RX_BURST_LENGTH(x)                                          \
(   ((x) == ETH_DMA_RX_BURST_LENGTH_1BEAT)                  ||                 \
    ((x) == ETH_DMA_RX_BURST_LENGTH_2BEAT)                  ||                 \
    ((x) == ETH_DMA_RX_BURST_LENGTH_4BEAT)                  ||                 \
    ((x) == ETH_DMA_RX_BURST_LENGTH_8BEAT)                  ||                 \
    ((x) == ETH_DMA_RX_BURST_LENGTH_16BEAT)                 ||                 \
    ((x) == ETH_DMA_RX_BURST_LENGTH_32BEAT)                 ||                 \
    ((x) == ETH_DMA_RX_BURST_LENGTH_8XPBL_8BEAT)            ||                 \
    ((x) == ETH_DMA_RX_BURST_LENGTH_8XPBL_16BEAT)           ||                 \
    ((x) == ETH_DMA_RX_BURST_LENGTH_8XPBL_32BEAT)           ||                 \
    ((x) == ETH_DMA_RX_BURST_LENGTH_8XPBL_64BEAT)           ||                 \
    ((x) == ETH_DMA_RX_BURST_LENGTH_8XPBL_128BEAT)          ||                 \
    ((x) == ETH_DMA_RX_BURST_LENGTH_8XPBL_256BEAT))

#define IS_ETH_DMA_TX_BURST_LENGTH(x)                                          \
(   ((x) == ETH_DMA_TX_BURST_LENGTH_1BEAT)                  ||                 \
    ((x) == ETH_DMA_TX_BURST_LENGTH_2BEAT)                  ||                 \
    ((x) == ETH_DMA_TX_BURST_LENGTH_4BEAT)                  ||                 \
    ((x) == ETH_DMA_TX_BURST_LENGTH_8BEAT)                  ||                 \
    ((x) == ETH_DMA_TX_BURST_LENGTH_16BEAT)                 ||                 \
    ((x) == ETH_DMA_TX_BURST_LENGTH_32BEAT)                 ||                 \
    ((x) == ETH_DMA_TX_BURST_LENGTH_8XPBL_8BEAT)            ||                 \
    ((x) == ETH_DMA_TX_BURST_LENGTH_8XPBL_16BEAT)           ||                 \
    ((x) == ETH_DMA_TX_BURST_LENGTH_8XPBL_32BEAT)           ||                 \
    ((x) == ETH_DMA_TX_BURST_LENGTH_8XPBL_64BEAT)           ||                 \
    ((x) == ETH_DMA_TX_BURST_LENGTH_8XPBL_128BEAT)          ||                 \
    ((x) == ETH_DMA_TX_BURST_LENGTH_8XPBL_256BEAT))

#define IS_ETH_DMA_ENHANCE_DESCRIPTOR(x)                                       \
(   ((x) == ETH_DMA_ENHANCE_DESCRIPTOR_DISABLE)             ||                 \
    ((x) == ETH_DMA_ENHANCE_DESCRIPTOR_ENABLE))

#define IS_ETH_DMA_PRIORITY_ARBITRATION(x)                                     \
(   ((x) == ETH_DMA_ARBITRATION_LOOP_RXTX_1_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_LOOP_RXTX_2_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_LOOP_RXTX_3_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_LOOP_RXTX_4_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_LOOP_TXRX_1_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_LOOP_TXRX_2_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_LOOP_TXRX_3_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_LOOP_TXRX_4_1)              ||                 \
    ((x) == ETH_DMA_ARBITRATION_FIXED_RXPRIORTX)            ||                 \
    ((x) == ETH_DMA_ARBITRATION_FIXED_TXPRIORRX))

#define IS_ETH_DMA_DROP_CHECKSUM_ERRORFRAME(x)                                 \
(   ((x) == ETH_DMA_DROP_CHECKSUM_ERRORFRAME_DISABLE)       ||                 \
    ((x) == ETH_DMA_DROP_CHECKSUM_ERRORFRAME_ENABLE))

#define IS_ETH_DMA_RECEIVE_STORE_FORWARD(x)                                    \
(   ((x) == ETH_DMA_RECEIVE_STORE_FORWARD_DISABLE)          ||                 \
    ((x) == ETH_DMA_RECEIVE_STORE_FORWARD_ENABLE))

#define IS_ETH_DMA_FLUSH_RECEIVEDFRAME(x)                                      \
(   ((x) == ETH_DMA_FLUSH_RECEIVEDFRAME_DISABLE)            ||                 \
    ((x) == ETH_DMA_FLUSH_RECEIVEDFRAME_ENABLE))

#define IS_ETH_DMA_TRANSMIT_STORE_FORWARD(x)                                   \
(   ((x) == ETH_DMA_TRANSMIT_STORE_FORWARD_DISABLE)         ||                 \
    ((x) == ETH_DMA_TRANSMIT_STORE_FORWARD_ENABLE))

#define IS_ETH_DMA_TRANSMIT_THRESHOLD(x)                                       \
(   ((x) == ETH_DMA_TRANSMIT_THRESHOLD_64BYTE)              ||                 \
    ((x) == ETH_DMA_TRANSMIT_THRESHOLD_128BYTE)             ||                 \
    ((x) == ETH_DMA_TRANSMIT_THRESHOLD_192BYTE)             ||                 \
    ((x) == ETH_DMA_TRANSMIT_THRESHOLD_256BYTE)             ||                 \
    ((x) == ETH_DMA_TRANSMIT_THRESHOLD_40BYTE)              ||                 \
    ((x) == ETH_DMA_TRANSMIT_THRESHOLD_32BYTE)              ||                 \
    ((x) == ETH_DMA_TRANSMIT_THRESHOLD_24BYTE)              ||                 \
    ((x) == ETH_DMA_TRANSMIT_THRESHOLD_16BYTE))

#define IS_ETH_DMA_FORWARD_ERRORFRAME(x)                                       \
(   ((x) == ETH_DMA_FORWARD_ERRORFRAME_DISABLE)             ||                 \
    ((x) == ETH_DMA_FORWARD_ERRORFRAME_ENABLE))

#define IS_ETH_DMA_FORWARD_UNDERSIZE_GOODFRAME(x)                              \
(   ((x) == ETH_DMA_FORWARD_UNDERSIZE_GOODFRAME_DISABLE)    ||                 \
    ((x) == ETH_DMA_FORWARD_UNDERSIZE_GOODFRAME_ENABLE))

#define IS_ETH_DMA_DROP_JUMBO_FRAME(x)                                         \
(   ((x) == ETH_DMA_DROP_JUMBO_FRAME_DISABLE)               ||                 \
    ((x) == ETH_DMA_DROP_JUMBO_FRAME_ENABLE))

#define IS_ETH_DMA_RECEIVE_THRESHOLD(x)                                        \
(   ((x) == ETH_DMA_RECEIVE_THRESHOLD_64BYTE)               ||                 \
    ((x) == ETH_DMA_RECEIVE_THRESHOLD_32BYTE)               ||                 \
    ((x) == ETH_DMA_RECEIVE_THRESHOLD_96BYTE)               ||                 \
    ((x) == ETH_DMA_RECEIVE_THRESHOLD_128BYTE))

#define IS_ETH_DMA_SECONDFRAME_OPERARTE(x)                                     \
(   ((x) == ETH_DMA_SECONDFRAME_OPERARTE_DISABLE)           ||                 \
    ((x) == ETH_DMA_SECONDFRAME_OPERARTE_ENABLE))

#define IS_ETH_DMA_INTERRUPT(x)                                                \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(ETH_DMA_INT_NIE            |                  \
                                 ETH_DMA_INT_AIE            |                  \
                                 ETH_DMA_INT_ERE            |                  \
                                 ETH_DMA_INT_FBE            |                  \
                                 ETH_DMA_INT_ETE            |                  \
                                 ETH_DMA_INT_RWE            |                  \
                                 ETH_DMA_INT_RSE            |                  \
                                 ETH_DMA_INT_RUE            |                  \
                                 ETH_DMA_INT_RIE            |                  \
                                 ETH_DMA_INT_UNE            |                  \
                                 ETH_DMA_INT_OVE            |                  \
                                 ETH_DMA_INT_TJE            |                  \
                                 ETH_DMA_INT_TUE            |                  \
                                 ETH_DMA_INT_TSE            |                  \
                                 ETH_DMA_INT_TIE))))))

#define IS_ETH_DMA_FLAG(x)                                                     \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(ETH_DMA_FLAG_PTPS          |                  \
                                 ETH_DMA_FLAG_PMTS          |                  \
                                 ETH_DMA_FLAG_MMCS          |                  \
                                 ETH_DMA_FLAG_NIS           |                  \
                                 ETH_DMA_FLAG_AIS           |                  \
                                 ETH_DMA_FLAG_ERS           |                  \
                                 ETH_DMA_FLAG_FBS           |                  \
                                 ETH_DMA_FLAG_ETS           |                  \
                                 ETH_DMA_FLAG_RWS           |                  \
                                 ETH_DMA_FLAG_RSS           |                  \
                                 ETH_DMA_FLAG_RUS           |                  \
                                 ETH_DMA_FLAG_RIS           |                  \
                                 ETH_DMA_FLAG_UNS           |                  \
                                 ETH_DMA_FLAG_OVS           |                  \
                                 ETH_DMA_FLAG_TJS           |                  \
                                 ETH_DMA_FLAG_TUS           |                  \
                                 ETH_DMA_FLAG_TSS           |                  \
                                 ETH_DMA_FLAG_TIS))))))

#define IS_ETH_DMA_MISS_FRAME_TYPE(x)                                          \
(   ((x) == ETH_DMA_OVERFLOW_RXFIFO_COUNTER)                ||                 \
    ((x) == ETH_DMA_OVERFLOW_MISSFRAME_COUNTER))

#define IS_ETH_DMATXDESC_BUFFER_SIZE(x)                    ((x) <= 0x1FFFFFFFUL)

#define IS_ETH_DMATXDESC_CHECKSUM_CONTROL(x)                                   \
(   ((x) == ETH_DMATXDESC_CHECKSUM_BYPASS)                  ||                 \
    ((x) == ETH_DMATXDESC_CHECKSUM_IPV4HEADER)              ||                 \
    ((x) == ETH_DMATXDESC_CHECKSUM_TCPUDPICMP_SEGMENT)      ||                 \
    ((x) == ETH_DMATXDESC_CHECKSUM_TCPUDPICMP_FULL))

#define IS_ETH_DMATXDESC_VLAN_CONTROL(x)                                       \
(   ((x) == ETH_DMATXDESC_VLAN_BYPASS)                      ||                 \
    ((x) == ETH_DMATXDESC_VLAN_REMOVE_TAG)                  ||                 \
    ((x) == ETH_DMATXDESC_VLAN_INSERT_TAG)                  ||                 \
    ((x) == ETH_DMATXDESC_VLAN_REPLACE_TAG))

#define IS_ETH_DMATXDESC_SA_CONTROL(x)                                         \
(   ((x) == ETH_DMATXDESC_SA_BYPASS)                        ||                 \
    ((x) == ETH_DMATXDESC_SA_INSTER_MACADDR0)               ||                 \
    ((x) == ETH_DMATXDESC_SA_REPLACE_MACADDR0)              ||                 \
    ((x) == ETH_DMATXDESC_SA_INSTER_MACADDR1)               ||                 \
    ((x) == ETH_DMATXDESC_SA_REPLACE_MACADDR1))

#define IS_ETH_DMATXDESC_STATUS(x)                                             \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(ETH_DMATXDESC_OWN          |                  \
                                 ETH_DMATXDESC_IOC          |                  \
                                 ETH_DMATXDESC_TLS          |                  \
                                 ETH_DMATXDESC_TFS          |                  \
                                 ETH_DMATXDESC_DCRC         |                  \
                                 ETH_DMATXDESC_DPAD         |                  \
                                 ETH_DMATXDESC_TTSE         |                  \
                                 ETH_DMATXDESC_CRCR         |                  \
                                 ETH_DMATXDESC_TER          |                  \
                                 ETH_DMATXDESC_TSAC         |                  \
                                 ETH_DMATXDESC_TTSS         |                  \
                                 ETH_DMATXDESC_IHE          |                  \
                                 ETH_DMATXDESC_ETSUM        |                  \
                                 ETH_DMATXDESC_JTE          |                  \
                                 ETH_DMATXDESC_FFF          |                  \
                                 ETH_DMATXDESC_TPCE         |                  \
                                 ETH_DMATXDESC_LOCE         |                  \
                                 ETH_DMATXDESC_NCE          |                  \
                                 ETH_DMATXDESC_TLCE         |                  \
                                 ETH_DMATXDESC_ECE          |                  \
                                 ETH_DMATXDESC_VLF          |                  \
                                 ETH_DMATXDESC_EDE          |                  \
                                 ETH_DMATXDESC_UDE          |                  \
                                 ETH_DMATXDESC_DEE))))))

#define IS_ETH_DMARXDESC_STATUS(x)                                             \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(ETH_DMARXDESC_OWN          |                  \
                                 ETH_DMARXDESC_DAF          |                  \
                                 ETH_DMARXDESC_ERSUM        |                  \
                                 ETH_DMARXDESC_DPE          |                  \
                                 ETH_DMARXDESC_SAF          |                  \
                                 ETH_DMARXDESC_LEE          |                  \
                                 ETH_DMARXDESC_OVE          |                  \
                                 ETH_DMARXDESC_VLAT         |                  \
                                 ETH_DMARXDESC_RFS          |                  \
                                 ETH_DMARXDESC_RLS          |                  \
                                 ETH_DMARXDESC_IPE_TSPA_GF  |                  \
                                 ETH_DMARXDESC_RLCE         |                  \
                                 ETH_DMARXDESC_FRAT         |                  \
                                 ETH_DMARXDESC_WTE          |                  \
                                 ETH_DMARXDESC_REE          |                  \
                                 ETH_DMARXDESC_DBE          |                  \
                                 ETH_DMARXDESC_CRE          |                  \
                                 ETH_DMARXDESC_DAS_ESA))))))

#define IS_ETH_DMARXDESC_EXTEND_STATUS(x)                                      \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(ETH_DMARXDESC_L4FMS        |                  \
                                 ETH_DMARXDESC_L3FMS        |                  \
                                 ETH_DMARXDESC_TSPD         |                  \
                                 ETH_DMARXDESC_PTPV         |                  \
                                 ETH_DMARXDESC_PTPFT        |                  \
                                 ETH_DMARXDESC_IPV6DR       |                  \
                                 ETH_DMARXDESC_IPV4DR       |                  \
                                 ETH_DMARXDESC_IPCB         |                  \
                                 ETH_DMARXDESC_IPPE         |                  \
                                 ETH_DMARXDESC_IPHE))))))

#define IS_ETH_DMADESC_OWN(x)                                                  \
(   ((x) == ETH_DMADESC_OWN_CPU)                            ||                 \
    ((x) == ETH_DMADESC_OWN_DMA))

#define IS_ETH_DMADESC_BUFFER(x)                                               \
(   ((x) == ETH_DMADESC_BUFFER1)                            ||                 \
    ((x) == ETH_DMADESC_BUFFER2))

#define IS_ETH_PMT_FLAG(x)                                                     \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(ETH_PMT_FLAG_RTWKFR        |                  \
                                 ETH_PMT_FLAG_WKFR          |                  \
                                 ETH_PMT_FLAG_MPFR))))))

#define IS_ETH_MMC_COUNTER_PRESETMODE(x)                                       \
(   ((x) == ETH_MMC_COUNTER_PRESETMODE_DISABLE)             ||                 \
    ((x) == ETH_MMC_COUNTER_PRESETMODE_HALFVALUE)           ||                 \
    ((x) == ETH_MMC_COUNTER_PRESETMODE_FULLVALUE))

#define IS_ETH_MMC_READ_RESET(x)                                               \
(   ((x) == ETH_MMC_READ_RESET_ENABLE)                      ||                 \
    ((x) == ETH_MMC_READ_RESET_DISABLE))

#define IS_ETH_MMC_COUNTER_RELOAD(x)                                           \
(   ((x) == ETH_MMC_COUNTER_RELOAD_ENABLE)                  ||                 \
    ((x) == ETH_MMC_COUNTER_RELOAD_DISABLE))

#define IS_ETH_MMC_TX_INTERRUPT(x)                                             \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(ETH_MMC_INT_TXEDEIM        |                  \
                                 ETH_MMC_INT_TXUGIM         |                  \
                                 ETH_MMC_INT_TXCAEIM        |                  \
                                 ETH_MMC_INT_TXECEIM        |                  \
                                 ETH_MMC_INT_TXLCEIM        |                  \
                                 ETH_MMC_INT_TXDEEIM        |                  \
                                 ETH_MMC_INT_TXMGIM         |                  \
                                 ETH_MMC_INT_TXBGIM))))))

#define IS_ETH_MMC_RX_INTERRUPT(x)                                             \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(ETH_MMC_INT_RXOEIM         |                  \
                                 ETH_MMC_INT_RXLEIM         |                  \
                                 ETH_MMC_INT_RXUGIM         |                  \
                                 ETH_MMC_INT_RXREIM         |                  \
                                 ETH_MMC_INT_RXAEIM         |                  \
                                 ETH_MMC_INT_RXCEIM         |                  \
                                 ETH_MMC_INT_RXMGIM         |                  \
                                 ETH_MMC_INT_RXBGIM))))))

#define IS_ETH_MMC_TX_FLAG(x)                                                  \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(ETH_MMC_FLAG_TXEDEIS       |                  \
                                 ETH_MMC_FLAG_TXUGIS        |                  \
                                 ETH_MMC_FLAG_TXCAEIS       |                  \
                                 ETH_MMC_FLAG_TXECEIS       |                  \
                                 ETH_MMC_FLAG_TXLCEIS       |                  \
                                 ETH_MMC_FLAG_TXDEEIS       |                  \
                                 ETH_MMC_FLAG_TXMGIS        |                  \
                                 ETH_MMC_FLAG_TXBGIS))))))

#define IS_ETH_MMC_RX_FLAG(x)                                                  \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(ETH_MMC_FLAG_RXOEIS        |                  \
                                 ETH_MMC_FLAG_RXLEIS        |                  \
                                 ETH_MMC_FLAG_RXUGIS        |                  \
                                 ETH_MMC_FLAG_RXREIS        |                  \
                                 ETH_MMC_FLAG_RXAEIS        |                  \
                                 ETH_MMC_FLAG_RXCEIS        |                  \
                                 ETH_MMC_FLAG_RXMGIS        |                  \
                                 ETH_MMC_FLAG_RXBGIS))))))

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

#define IS_ETH_PTP_FRAME_DA_FILTER(x)                                          \
(   ((x) == ETH_PTP_FRAME_DA_FILTER_ENABLE)                 ||                 \
    ((x) == ETH_PTP_FRAME_DA_FILTER_DISABLE))

#define IS_ETH_PTP_DATAGRAM_VERSION(x)                                         \
(   ((x) == ETH_PTP_DATAGRAM_VERSION_IEEE1588V1)            ||                 \
    ((x) == ETH_PTP_DATAGRAM_VERSION_IEEE1588V2))

#define IS_ETH_PTP_SUBSECOND_SCALE(x)                                          \
(   ((x) == ETH_PTP_SUBSECOND_SCALE_HEX)                    ||                 \
    ((x) == ETH_PTP_SUBSECOND_SCALE_DEC))

#define IS_ETH_PTP_DATAGRAM_TYPE(x)                                            \
(   ((x) == ETH_PTP_DATAGRAM_TYPE_SYNC_FOLLOW_DELAY)        ||                 \
    ((x) == ETH_PTP_DATAGRAM_TYPE_SYNC)                     ||                 \
    ((x) == ETH_PTP_DATAGRAM_TYPE_DELAY)                    ||                 \
    ((x) == ETH_PTP_DATAGRAM_TYPE_SYNC_FOLLOW_DELAY_PDELAY) ||                 \
    ((x) == ETH_PTP_DATAGRAM_TYPE_SYNC_PDELAY)              ||                 \
    ((x) == ETH_PTP_DATAGRAM_TYPE_DELAY_PDEALY)             ||                 \
    ((x) == ETH_PTP_DATAGRAM_TYPE_SYNC_DELAY)               ||                 \
    ((x) == ETH_PTP_DATAGRAM_TYPE_PDELAY))

#define IS_ETH_PTP_FRAME_TYPE(x)                                               \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(ETH_PTP_FRAME_TYPE_IPV4FRAME       |          \
                                 ETH_PTP_FRAME_TYPE_IPV6FRAME       |          \
                                 ETH_PTP_FRAME_TYPE_ETHERNETFRAME   |          \
                                 ETH_PTP_FRAME_TYPE_ALL_RECEIVEFRAME))))))

#define IS_ETH_PTP_CALIBRATION_MODE(x)                                         \
(   ((x) == ETH_PTP_CALIBRATION_MODE_COARSE)                ||                 \
    ((x) == ETH_PTP_CALIBRATION_MODE_FINE))

#define IS_ETH_PTP_TIME_UPDATE_SIGN(x)                                         \
(   ((x) == ETH_PTP_TIME_UPDATE_SIGN_MINUS)                 ||                 \
    ((x) == ETH_PTP_TIME_UPDATE_SIGN_PLUS))

#define IS_ETH_PTP_FLAG(x)                                                     \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(ETH_PTP_FLAG_TSERR1        |                  \
                                 ETH_PTP_FLAG_TSTAR1        |                  \
                                 ETH_PTP_FLAG_TSERR0        |                  \
                                 ETH_PTP_FLAG_TSTAR0        |                  \
                                 ETH_PTP_FLAG_TSOVF))))))

#define IS_ETH_PPS1_COMPLEX_FUNC(ch, mode, freq)                               \
(   ((ch)    == ETH_PPS_TARGET_CH0)                         ||                 \
    (((mode) == ETH_PPS_OUTPUT_MODE_CONTINUE)               &&                 \
    ((freq)  == ETH_PPS_OUTPUT_ONE_PULSE)))

#define IS_ETH_PTP_SUB_SECOND(x)                            ((x) <= 0x7FFFFFFFUL)

#define IS_ETH_PPS_TARGET_TIME_FUNC(x)                                         \
(   ((x) == ETH_PPS_TARGET_TIME_FUNC_INT_EVENT)             ||                 \
    ((x) == ETH_PPS_TARGET_TIME_FUNC_INT_PPS_EVENT)         ||                 \
    ((x) == ETH_PPS_TARGET_TIME_FUNC_PPS_EVENT))

#define IS_ETH_PPS_TARGET_CH(x)                                                \
(   ((x) == ETH_PPS_TARGET_CH0)                             ||                 \
    ((x) == ETH_PPS_TARGET_CH1))

#define IS_ETH_PPS_OUTPUT_MODE(x)                                              \
(   ((x) == ETH_PPS_OUTPUT_MODE_CONTINUE)                   ||                 \
    ((x) == ETH_PPS_OUTPUT_MODE_SINGLE))

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
 * @retval An en_result_t enumeration value:
 *           - Ok: De-Initialize success
 *           - ErrorTimeout: De-Initialize timeout
 */
en_result_t ETH_DeInit(void)
{
    en_result_t enRet;

    ETH_MAC_DeInit();
    ETH_DMA_DeInit();
    ETH_MACADDR_DeInit(ETH_MAC_ADDRESS0);
    ETH_MACADDR_DeInit(ETH_MAC_ADDRESS1);
    ETH_MACADDR_DeInit(ETH_MAC_ADDRESS2);
    ETH_MACADDR_DeInit(ETH_MAC_ADDRESS3);
    ETH_MACADDR_DeInit(ETH_MAC_ADDRESS4);
    ETH_MAC_L3L4FilterDeInit();
    ETH_PTP_DeInit();
    ETH_PPS_DeInit(ETH_PPS_TARGET_CH0);
    ETH_PPS_DeInit(ETH_PPS_TARGET_CH1);
    enRet = ETH_MMC_DeInit();
    if (Ok == enRet)
    {
        enRet = ETH_DMA_SoftwareReset();
    }

    return enRet;
}

/**
 * @brief  Initialize ETH.
 * @param  [in] pstcEthHandle               Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] pstcEthInit                 Pointer to a @ref stc_eth_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: ETH Initialize success
 *           - ErrorInvalidParameter: pstcEthHandle == NULL or pstcEthInit == NULL or
 *                                    PHY Address error
 *           - ErrorTimeout: Initialize timeout
 */
en_result_t ETH_Init(stc_eth_handle_t *pstcEthHandle, stc_eth_init_t *pstcEthInit)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Ok;
    uint32_t u32TempReg;
    uint32_t u32BusClk;
    uint32_t u32PhyTimeout;
    uint16_t u16PhyReg = 0U;

    if ((NULL == pstcEthHandle) || (NULL == pstcEthInit))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_AUTO_NEGOTIATION(pstcEthHandle->stcCommInit.u16AutoNegotiation));
        DDL_ASSERT(IS_ETH_MAC_CHECKSUM_MODE(pstcEthHandle->stcCommInit.u32ChecksumMode));
        DDL_ASSERT(IS_ETH_RX_MODE(pstcEthHandle->stcCommInit.u32RxMode));
        DDL_ASSERT(IS_ETH_MAC_MEDIA_INTERFACE(pstcEthHandle->stcCommInit.u32MediaInterface));

        /* Select MII or RMII Mode*/
        MODIFY_REG32(M4_ETH->MAC_IFCONFR, ETH_MAC_IFCONFR_IFSEL, pstcEthHandle->stcCommInit.u32MediaInterface);
        /* ETH software reset */
        if (Ok != ETH_DMA_SoftwareReset())
        {
            enRet = ErrorTimeout;
        }
        else
        {
            /* Get ETH frequency value */
            u32BusClk = SystemCoreClock / (0x01UL << (READ_REG32_BIT(M4_CMU->SCFGR, CMU_SCFGR_PCLK1S) >> CMU_SCFGR_PCLK1S_POS));
            /* Set SMIC bits depending on PCLK1 clock value */
            /* PCLK1 Clock Range between 20-35 MHz */
            if ((u32BusClk >= 20000000UL) && (u32BusClk < 35000000UL))
            {
                u32TempReg = ETH_MAC_SMIADDR_SMIC_1;
            }
            /* PCLK1 Clock Range between 35-60 MHz */
            else if ((u32BusClk >= 35000000UL) && (u32BusClk < 60000000UL))
            {
                u32TempReg = ETH_MAC_SMIADDR_SMIC_1 | ETH_MAC_SMIADDR_SMIC_0;
            }
            /* PCLK1 Clock Range between 60-100 MHz */
            else if ((u32BusClk >= 60000000UL) && (u32BusClk < 100000000UL))
            {
                u32TempReg = 0UL;
            }
            /* PCLK1 Clock Range between 100-120 MHz */
            else
            {
                u32TempReg = ETH_MAC_SMIADDR_SMIC_0;
            }
            /* Configure the ETH MDC Clock Range */
            MODIFY_REG32(M4_ETH->MAC_SMIADDR, ETH_MAC_SMIADDR_SMIC, u32TempReg);

            /* PHY initialization and configuration */
            /* Reset the PHY */
            if (Ok != (ETH_PHY_WriteRegister(pstcEthHandle, PHY_BCR, PHY_SOFT_RESET)))
            {
                enRet = ErrorTimeout;
            }
            else
            {
                /* Delay to assure PHY reset */
                DDL_DelayMS(PHY_RESET_DELAY);

                if (ETH_AUTO_NEGOTIATION_DISABLE != pstcEthHandle->stcCommInit.u16AutoNegotiation)
                {
                    u32PhyTimeout = PHY_READ_TIMEOUT * (HCLK_VALUE / 20000UL);
                    /* Wait for linke status */
                    u32Count = ETH_TIMEOUT_LINK_STATUS * (HCLK_VALUE / 20000UL);
                    while (PHY_LINK_STATUS != (u16PhyReg & PHY_LINK_STATUS))
                    {
                        if (0UL == u32Count)
                        {
                            break;
                        }
                        if (ErrorTimeout == ETH_PHY_ReadRegister(pstcEthHandle, PHY_BSR, &u16PhyReg))
                        {
                            u32Count = (u32Count > u32PhyTimeout) ? (u32Count - u32PhyTimeout) : 0UL;
                        }
                        else
                        {
                            u32Count = (u32Count > u32PhyTimeout) ? (u32Count - (u32PhyTimeout / 150U)) : 0UL;
                        }
                    }

                    if ((0x0000U == u16PhyReg) || (0xFFFFU == u16PhyReg))
                    {
                        enRet = ErrorInvalidParameter;
                    }
                    else if (PHY_LINK_STATUS != (u16PhyReg & PHY_LINK_STATUS))
                    {
                        enRet = ErrorTimeout;
                    }
                    else
                    {
                        /* Enable Auto-Negotiation */
                        if (Ok != (ETH_PHY_WriteRegister(pstcEthHandle, PHY_BCR, PHY_AUTONEGOTIATION)))
                        {
                            enRet = ErrorTimeout;
                        }
                        else
                        {
                            /* Wait until the auto-negotiation will be completed */
                            u32Count = ETH_TIMEOUT_AUTONEGO_COMPLETE * (HCLK_VALUE / 20000UL);
                            while (PHY_AUTONEGO_COMPLETE != (u16PhyReg & PHY_AUTONEGO_COMPLETE))
                            {
                                if (0UL == u32Count)
                                {
                                    break;
                                }
                                if (ErrorTimeout == ETH_PHY_ReadRegister(pstcEthHandle, PHY_BSR, &u16PhyReg))
                                {
                                    u32Count = (u32Count > u32PhyTimeout) ? (u32Count - u32PhyTimeout) : 0UL;
                                }
                                else
                                {
                                    u32Count = (u32Count > u32PhyTimeout) ? (u32Count - (u32PhyTimeout / 150U)) : 0UL;
                                }
                            }

                            if (PHY_AUTONEGO_COMPLETE != (u16PhyReg & PHY_AUTONEGO_COMPLETE))
                            {
                                enRet = ErrorTimeout;
                            }
                            else
                            {
                                /* Read the result of the auto-negotiation */
                                /* Configure ETH duplex mode according to the result of automatic negotiation */
                                if (0U != (u16PhyReg & (uint16_t)(PHY_100BASE_TX_FD | PHY_10BASE_T_FD)))
                                {
                                    pstcEthHandle->stcCommInit.u32DuplexMode = ETH_MAC_MODE_FULLDUPLEX;
                                }
                                else
                                {
                                    pstcEthHandle->stcCommInit.u32DuplexMode = ETH_MAC_MODE_HALFDUPLEX;
                                }

                                /* Configure ETH speed according to the result of automatic negotiation */
                                if (0U != (u16PhyReg & (uint16_t)(PHY_100BASE_TX_FD | PHY_100BASE_TX_HD)))
                                {
                                    pstcEthHandle->stcCommInit.u32Speed = ETH_MAC_SPEED_100M;
                                }
                                else
                                {
                                    pstcEthHandle->stcCommInit.u32Speed = ETH_MAC_SPEED_10M;
                                }
                            }
                        }
                    }
                }
                /* AutoNegotiation Disable */
                else
                {
                    DDL_ASSERT(IS_ETH_MAC_SPEED(pstcEthHandle->stcCommInit.u32Speed));
                    DDL_ASSERT(IS_ETH_MAC_DUPLEX_MODE(pstcEthHandle->stcCommInit.u32DuplexMode));

                    if (Ok != ETH_PHY_WriteRegister(pstcEthHandle, PHY_BCR,
                                                    ((uint16_t)(pstcEthHandle->stcCommInit.u32DuplexMode >> 3U) |
                                                    (uint16_t)(pstcEthHandle->stcCommInit.u32Speed >> 1U))))
                    {
                        enRet = ErrorTimeout;
                    }
                    else
                    {
                        /* Delay to assure PHY configuration */
                        DDL_DelayMS(PHY_CONFIG_DELAY);
                    }
                }
            }

            /* Auto-negotiation failed */
            if (Ok != enRet)
            {
                pstcEthHandle->stcCommInit.u32DuplexMode = ETH_MAC_MODE_FULLDUPLEX;
                pstcEthHandle->stcCommInit.u32Speed      = ETH_MAC_SPEED_100M;
            }

            /* Config checksum offload */
            if(ETH_MAC_CHECKSUM_MODE_HARDWARE == pstcEthHandle->stcCommInit.u32ChecksumMode)
            {
                pstcEthInit->stcMacInit.u32ChecksumOffload = ETH_MAC_CHECKSUM_OFFLAOD_ENABLE;
            }
            else
            {
                pstcEthInit->stcMacInit.u32ChecksumOffload = ETH_MAC_CHECKSUM_OFFLAOD_DISABLE;
            }

            /* Config MAC,DMA,MMC and PTP */
            (void)ETH_MAC_Init(pstcEthHandle, &pstcEthInit->stcMacInit);
            (void)ETH_DMA_Init(&pstcEthInit->stcDmaInit);
            /* Enable the ETH Rx Interrupt */
            if(ETH_RX_MODE_INTERRUPT == pstcEthHandle->stcCommInit.u32RxMode)
            {
                ETH_DMA_IntCmd(ETH_DMA_INT_NIE | ETH_DMA_INT_RIE, Enable);
            }
        }
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_eth_comm_init_t to default values.
 * @param  [out] pstcCommInit               Pointer to a @ref stc_eth_comm_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Structure Initialize success
 *           - ErrorInvalidParameter: pstcCommInit == NULL
 */
en_result_t ETH_CommStructInit(stc_eth_comm_init_t *pstcCommInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcCommInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcCommInit->u16AutoNegotiation = ETH_AUTO_NEGOTIATION_ENABLE;
        pstcCommInit->u16PHYAddress      = PHY_ADDRESS;
        pstcCommInit->au8MACAddr[0]      = ETH_MAC_ADDR0;
        pstcCommInit->au8MACAddr[1]      = ETH_MAC_ADDR1;
        pstcCommInit->au8MACAddr[2]      = ETH_MAC_ADDR2;
        pstcCommInit->au8MACAddr[3]      = ETH_MAC_ADDR3;
        pstcCommInit->au8MACAddr[4]      = ETH_MAC_ADDR4;
        pstcCommInit->au8MACAddr[5]      = ETH_MAC_ADDR5;
        pstcCommInit->u32MediaInterface  = ETH_MAC_MEDIA_INTERFACE_MII;
        pstcCommInit->u32Speed           = ETH_MAC_SPEED_100M;
        pstcCommInit->u32DuplexMode      = ETH_MAC_MODE_FULLDUPLEX;
        pstcCommInit->u32ChecksumMode    = ETH_MAC_CHECKSUM_MODE_HARDWARE;
        pstcCommInit->u32RxMode          = ETH_RX_MODE_POLLING;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_eth_init_t to default values.
 * @param  [out] pstcEthInit                Pointer to a @ref stc_eth_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Structure Initialize success
 *           - ErrorInvalidParameter: pstcEthInit == NULL
 */
en_result_t ETH_StructInit(stc_eth_init_t *pstcEthInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcEthInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        (void)ETH_MAC_StructInit(&pstcEthInit->stcMacInit);
        (void)ETH_DMA_StructInit(&pstcEthInit->stcDmaInit);
    }

    return enRet;
}

/**
 * @brief  Enable MAC and DMA Transmission/Reception
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Enable success
 *           - ErrorTimeout: Enable timeout
 */
en_result_t ETH_Start(void)
{
    en_result_t enRet;

    /* Flush Transmit FIFO */
    enRet = ETH_DMA_FlushTransmitFIFO();
    if (Ok == enRet)
    {
        /* Enable MAC Transmit */
        ETH_MAC_TransmitCmd(Enable);
        /* Enable MAC Receive */
        ETH_MAC_ReceiveCmd(Enable);
        /* Enable DMA Transmit */
        ETH_DMA_TransmitCmd(Enable);
        /* Enable DMA Receive */
        ETH_DMA_ReceiveCmd(Enable);
    }

    return enRet;
}

/**
 * @brief  Disable MAC and DMA Transmission/Reception
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Disable success
 *           - ErrorTimeout: Disable timeout
 */
en_result_t ETH_Stop(void)
{
    en_result_t enRet;

    /* Disable DMA Transmit */
    ETH_DMA_TransmitCmd(Disable);
    /* Disable DMA Receive */
    ETH_DMA_ReceiveCmd(Disable);
    /* Disable MAC Receive */
    ETH_MAC_ReceiveCmd(Disable);
    /* Disable MAC Transmit */
    ETH_MAC_TransmitCmd(Disable);
    /* Flush Transmit FIFO */
    enRet = ETH_DMA_FlushTransmitFIFO();

    return enRet;
}

/******************************************************************************/
/*                             PHY Functions                                  */
/******************************************************************************/
/**
 * @brief  Write PHY register
 * @note   More PHY register could be written depending on the used PHY.
 * @param  [in] pstcEthHandle               Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] u16Reg                      PHY register address
 *         This parameter can be one of the following values:
 *           @arg PHY_BCR:      PHY Basic Control Register
 *           @arg other value:  The value range from 1 to 31
 * @param  [in] u16RegVal                   PHY register value
 * @retval An en_result_t enumeration value:
 *           - Ok: Write register success
 *           - ErrorInvalidParameter: pstcEthHandle == NULL
 *           - ErrorTimeout: Write timeout
 */
en_result_t ETH_PHY_WriteRegister(stc_eth_handle_t *pstcEthHandle, uint16_t u16Reg, uint16_t u16RegVal)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Ok;

    if (NULL == pstcEthHandle)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_PHY_ADDRESS(pstcEthHandle->stcCommInit.u16PHYAddress));
        DDL_ASSERT(IS_ETH_PHY_REGISTER(u16Reg));

        /* Set the MAC_SMIDATR register */
        WRITE_REG32(M4_ETH->MAC_SMIDATR, u16RegVal);
        /* Set the MAC_SMIADDR register */
        /* Keep only the MDC Clock Range SMIC[3:0] bits value */
        MODIFY_REG32(M4_ETH->MAC_SMIADDR, ETH_MAC_SMIADDR_CLEAR_MASK,
                    (((uint32_t)(pstcEthHandle->stcCommInit.u16PHYAddress) << ETH_MAC_SMIADDR_SMIA_POS) |
                    ((uint32_t)u16Reg << ETH_MAC_SMIADDR_SMIR_POS) | ETH_MAC_SMIADDR_SMIW | ETH_MAC_SMIADDR_SMIB));
        /* Check for the Busy flag */
        u32Count = PHY_WRITE_TIMEOUT * (HCLK_VALUE / 20000UL);
        while (0UL != READ_REG32_BIT(M4_ETH->MAC_SMIADDR, ETH_MAC_SMIADDR_SMIB))
        {
            if (0UL == u32Count)
            {
                enRet = ErrorTimeout;
                break;
            }
            u32Count--;
        }
    }

    return enRet;
}

/**
 * @brief  Read PHY register.
 * @note   More PHY register could be read depending on the used PHY.
 * @param  [in] pstcEthHandle               Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] u16Reg                      PHY register address
 *         This parameter can be one of the following values:
 *           @arg PHY_BCR:      PHY Basic Control Register
 *           @arg PHY_BSR:      PHY Basic Status Register
 *           @arg other value:  The value range from 2 to 31
 * @param  [out] pu16RegVal                 Pointer to PHY register value
 * @retval An en_result_t enumeration value:
 *           - Ok: Read register success
 *           - ErrorInvalidParameter: pstcEthHandle == NULL or pu16RegVal == NULL
 *           - ErrorTimeout: Read timeout
 */
en_result_t ETH_PHY_ReadRegister(stc_eth_handle_t *pstcEthHandle, uint16_t u16Reg, uint16_t *pu16RegVal)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Ok;

    if ((NULL == pstcEthHandle) || (NULL == pu16RegVal))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_PHY_ADDRESS(pstcEthHandle->stcCommInit.u16PHYAddress));
        DDL_ASSERT(IS_ETH_PHY_REGISTER(u16Reg));

        *pu16RegVal = 0U;
        /* Set the MAC_SMIADDR register */
        /* Keep only the MDC Clock Range SMIC[3:0] bits value */
        MODIFY_REG32(M4_ETH->MAC_SMIADDR, ETH_MAC_SMIADDR_CLEAR_MASK,
                    (((uint32_t)(pstcEthHandle->stcCommInit.u16PHYAddress) << ETH_MAC_SMIADDR_SMIA_POS) |
                    ((uint32_t)u16Reg << ETH_MAC_SMIADDR_SMIR_POS) | ETH_MAC_SMIADDR_SMIB));
        /* Check for the Busy flag */
        u32Count = PHY_READ_TIMEOUT * (HCLK_VALUE / 20000UL);
        while (0UL != READ_REG32_BIT(M4_ETH->MAC_SMIADDR, ETH_MAC_SMIADDR_SMIB))
        {
            if (0UL == u32Count)
            {
                enRet = ErrorTimeout;
                break;
            }
            u32Count--;
        }

        if (ErrorTimeout != enRet)
        {
            /* Get the MAC_SMIDATR value */
            *pu16RegVal = (uint16_t)(READ_REG32(M4_ETH->MAC_SMIDATR));
        }
    }

    return enRet;
}

/**
 * @brief  Enabele or disable PHY loopback.
 * @param  [in] pstcEthHandle               Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval An en_result_t enumeration value:
 *           - Ok: Set loopback success
 *           - ErrorInvalidParameter: pstcEthHandle == NULL
 *           - Error: Communication error
 */
en_result_t ETH_PHY_LoopBackCmd(stc_eth_handle_t *pstcEthHandle, en_functional_state_t enNewSta)
{
    en_result_t enRet;
    uint16_t u16RegVal;

    if (NULL == pstcEthHandle)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_PHY_ADDRESS(pstcEthHandle->stcCommInit.u16PHYAddress));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

        enRet = ETH_PHY_ReadRegister(pstcEthHandle, PHY_BCR, &u16RegVal);
        if (enRet == Ok)
        {
            if (Disable != enNewSta)
            {
                SET_REG16_BIT(u16RegVal, PHY_LOOPBACK);
            }
            else
            {
                CLEAR_REG16_BIT(u16RegVal, PHY_LOOPBACK);
            }
            if (Ok != ETH_PHY_WriteRegister(pstcEthHandle, PHY_BCR, u16RegVal))
            {
                enRet = Error;
            }
        }
    }

    return enRet;
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
    WRITE_REG32(M4_ETH->MAC_IFCONFR,  0UL);
    WRITE_REG32(M4_ETH->MAC_CONFIGR,  0x00008000UL);
    MODIFY_REG32(M4_ETH->MAC_FLTCTLR, ETH_MAC_FLTCTLR_CLEAR_MASK, 0UL);
    WRITE_REG32(M4_ETH->MAC_FLOCTLR,  0UL);
    WRITE_REG32(M4_ETH->MAC_INTMSKR,  0UL);
    WRITE_REG32(M4_ETH->MAC_SMIADDR,  0UL);
    WRITE_REG32(M4_ETH->MAC_SMIDATR,  0UL);
    WRITE_REG32(M4_ETH->MAC_RTWKFFR,  0UL);
    WRITE_REG32(M4_ETH->MAC_PMTCTLR,  0UL);
    WRITE_REG32(M4_ETH->MAC_HASHTLR,  0UL);
    WRITE_REG32(M4_ETH->MAC_HASHTHR,  0UL);
    WRITE_REG32(M4_ETH->MAC_VTACTLR,  0UL);
    WRITE_REG32(M4_ETH->MAC_VTAFLTR,  0UL);
    WRITE_REG32(M4_ETH->MAC_VLAHTBR,  0UL);
}

/**
 * @brief  Initialize MAC.
 * @param  [in] pstcEthHandle               Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] pstcMacInit                 Pointer to a @ref stc_eth_mac_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: MAC Initialize success
 *           - ErrorInvalidParameter: pstcEthHandle == NULL or pstcMacInit == NULL
 */
en_result_t ETH_MAC_Init(stc_eth_handle_t *pstcEthHandle, const stc_eth_mac_init_t *pstcMacInit)
{
    en_result_t enRet = Ok;

    if ((NULL == pstcEthHandle) || (NULL == pstcMacInit))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_MAC_TX_CLK_POLARITY(pstcMacInit->u32TxClkPolarity));
        DDL_ASSERT(IS_ETH_MAC_RX_REF_CLK_POLARITY(pstcMacInit->u32RxRefClkPolarity));
        DDL_ASSERT(IS_ETH_MAC_SA_MODE(pstcMacInit->u32SAInsertMode));
        DDL_ASSERT(IS_ETH_MAC_TYPEFRAME_STRIP_FCS(pstcMacInit->u32TypeFrameStripFCS));
        DDL_ASSERT(IS_ETH_MAC_WATCHDOG(pstcMacInit->u32Watchdog));
        DDL_ASSERT(IS_ETH_MAC_JABBER(pstcMacInit->u32Jabber));
        DDL_ASSERT(IS_ETH_MAC_INTERFRAME_GAP(pstcMacInit->u32InterFrameGap));
        DDL_ASSERT(IS_ETH_MAC_CARRIER_SENCE(pstcMacInit->u32CarrierSense));
        DDL_ASSERT(IS_ETH_MAC_SPEED(pstcEthHandle->stcCommInit.u32Speed));
        DDL_ASSERT(IS_ETH_MAC_RECEIVE_OWN(pstcMacInit->u32ReceiveOwn));
        DDL_ASSERT(IS_ETH_MAC_DUPLEX_MODE(pstcEthHandle->stcCommInit.u32DuplexMode));
        DDL_ASSERT(IS_ETH_MAC_CHECKSUM_OFFLAOD(pstcMacInit->u32ChecksumOffload));
        DDL_ASSERT(IS_ETH_MAC_RETRY_TRANSMIT(pstcMacInit->u32RetryTransmit));
        DDL_ASSERT(IS_ETH_MAC_AUTO_STRIP_PAD_FCS(pstcMacInit->u32AutoStripPadFCS));
        DDL_ASSERT(IS_ETH_MAC_BACKOFF_LIMIT(pstcMacInit->u32BackOffLimit));
        DDL_ASSERT(IS_ETH_MAC_DEFFERRAL_CHECK(pstcMacInit->u32DeferralCheck));
        DDL_ASSERT(IS_ETH_MAC_ZERO_QUANTA_PAUSE(pstcMacInit->u32ZeroQuantaPause));
        DDL_ASSERT(IS_ETH_MAC_PAUSE_LOWTHRESHOLD(pstcMacInit->u32PauseLowThreshold));
        DDL_ASSERT(IS_ETH_MAC_UNICAST_PAUSEFRAME_DETECT(pstcMacInit->u32UnicastPauseFrameDetect));
        DDL_ASSERT(IS_ETH_MAC_RECEIVE_FLOWCONTROL(pstcMacInit->u32ReceiveFlowControl));
        DDL_ASSERT(IS_ETH_MAC_TRANSMIT_FLOWCONTROL(pstcMacInit->u32TransmitFlowControl));
        DDL_ASSERT(IS_ETH_MAC_RECEIVE_All(pstcMacInit->u32ReceiveAll));
        DDL_ASSERT(IS_ETH_MAC_DROP_NOT_TCPUDP(pstcMacInit->u32DropNotTcpUdp));
        DDL_ASSERT(IS_ETH_MAC_VLAN_TAG_FILTER(pstcMacInit->u32VlanTagFilter));
        DDL_ASSERT(IS_ETH_MAC_SOURCE_ADDR_FILTER(pstcMacInit->u32SAFilter));
        DDL_ASSERT(IS_ETH_MAC_PASS_CTRLFRAME(pstcMacInit->u32PassControlFrame));
        DDL_ASSERT(IS_ETH_MAC_BROADCASTFRAME_RECEPTION(pstcMacInit->u32BroadcastFrameReception));
        DDL_ASSERT(IS_ETH_MAC_DESTINATION_ADDR_FILTER(pstcMacInit->u32DAFilter));
        DDL_ASSERT(IS_ETH_MAC_MULTICASTFRAME_FILTER(pstcMacInit->u32MulticastFrameFilter));
        DDL_ASSERT(IS_ETH_MAC_UNICASTFRAME_FILTER(pstcMacInit->u32UnicastFrameFilter));
        DDL_ASSERT(IS_ETH_MAC_PROMISCUOUS_MODE(pstcMacInit->u32PromiscuousMode));
        DDL_ASSERT(IS_ETH_MAC_TXVLAN_MODE(pstcMacInit->u32TxVlanInsertMode));
        DDL_ASSERT(IS_ETH_MAC_RXVLAN_FILTER(pstcMacInit->u32RxVlanFilter));
        DDL_ASSERT(IS_ETH_MAC_RXVLAN_COMPARISON(pstcMacInit->u32RxVlanComparison));

        /* Set MAC_IFCONFR register */
        MODIFY_REG32(M4_ETH->MAC_IFCONFR, ETH_MAC_IFCONFR_CLEAR_MASK,
                     (pstcMacInit->u32TxClkPolarity | pstcMacInit->u32RxRefClkPolarity));
        /* Set MAC_CONFIGR register */
        MODIFY_REG32(M4_ETH->MAC_CONFIGR, ETH_MAC_CONFIGR_CLEAR_MASK,
                     (pstcMacInit->u32SAInsertMode        | pstcMacInit->u32TypeFrameStripFCS        |
                      pstcMacInit->u32Watchdog            | pstcMacInit->u32Jabber                   |
                      pstcMacInit->u32InterFrameGap       | pstcMacInit->u32CarrierSense             |
                      pstcEthHandle->stcCommInit.u32Speed | pstcMacInit->u32ReceiveOwn               |
                      pstcMacInit->u32DeferralCheck       | pstcEthHandle->stcCommInit.u32DuplexMode |
                      pstcMacInit->u32ChecksumOffload     | pstcMacInit->u32RetryTransmit            |
                      pstcMacInit->u32AutoStripPadFCS     | pstcMacInit->u32BackOffLimit));
        /* Set MAC_FLOCTLR register */
        MODIFY_REG32(M4_ETH->MAC_FLOCTLR, ETH_MAC_FLOCTLR_CLEAR_MASK,
                     ((((uint32_t)pstcMacInit->u16PauseTime) << 16U) | pstcMacInit->u32ZeroQuantaPause         |
                      pstcMacInit->u32PauseLowThreshold              | pstcMacInit->u32UnicastPauseFrameDetect |
                      pstcMacInit->u32ReceiveFlowControl             | pstcMacInit->u32TransmitFlowControl));
        /* Set MAC_FLTCTLR register */
        MODIFY_REG32(M4_ETH->MAC_FLTCTLR, ETH_MAC_FLTCTLR_CLEAR_MASK,
                     (pstcMacInit->u32ReceiveAll              | pstcMacInit->u32DropNotTcpUdp         |
                      pstcMacInit->u32PromiscuousMode         | pstcMacInit->u32VlanTagFilter         |
                      pstcMacInit->u32SAFilter                | pstcMacInit->u32PassControlFrame      |
                      pstcMacInit->u32BroadcastFrameReception | pstcMacInit->u32DAFilter              |
                      pstcMacInit->u32MulticastFrameFilter    | pstcMacInit->u32UnicastFrameFilter));
        /* Set Hash table register */
        WRITE_REG32(M4_ETH->MAC_HASHTLR, pstcMacInit->u32HashTableLow);
        WRITE_REG32(M4_ETH->MAC_HASHTHR, pstcMacInit->u32HashTableHigh);
        /* Set Tx VLAN register */
        WRITE_REG32(M4_ETH->MAC_VTACTLR, (pstcMacInit->u32TxVlanInsertMode | pstcMacInit->u16TxVlanTag));
        /* Set Rx VLAN register */
        WRITE_REG32(M4_ETH->MAC_VTAFLTR, (pstcMacInit->u32RxVlanFilter |
                    pstcMacInit->u32RxVlanComparison | pstcMacInit->u16RxVlanTag));
        WRITE_REG32(M4_ETH->MAC_VLAHTBR, pstcMacInit->u16RxVlanHashTable);
        /* Config MAC address in ETH MAC0 */
        (void)ETH_MACADDR_SetAddress(ETH_MAC_ADDRESS0, pstcEthHandle->stcCommInit.au8MACAddr);
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_eth_mac_init_t to default values.
 * @param  [out] pstcMacInit                Pointer to a @ref stc_eth_mac_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Structure Initialize success
 *           - ErrorInvalidParameter: pstcMacInit == NULL
 */
en_result_t ETH_MAC_StructInit(stc_eth_mac_init_t *pstcMacInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcMacInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcMacInit->u32TxClkPolarity           = ETH_MAC_TX_CLK_POLARITY_KEEP;
        pstcMacInit->u32RxRefClkPolarity        = ETH_MAC_RX_REF_CLK_POLARITY_KEEP;
        pstcMacInit->u32SAInsertMode            = ETH_MAC_SA_MODE_BY_DMATXDESC;
        pstcMacInit->u32TypeFrameStripFCS       = ETH_MAC_TYPEFRAME_STRIP_FCS_DISABLE;
        pstcMacInit->u32Watchdog                = ETH_MAC_WATCHDOG_ENABLE;
        pstcMacInit->u32Jabber                  = ETH_MAC_JABBER_ENABLE;
        pstcMacInit->u32InterFrameGap           = ETH_MAC_INTERFRAME_GAP_96BIT;
        pstcMacInit->u32CarrierSense            = ETH_MAC_CARRIER_SENCE_ENABLE;
        pstcMacInit->u32ReceiveOwn              = ETH_MAC_RECEIVE_OWN_ENABLE;
        pstcMacInit->u32ChecksumOffload         = ETH_MAC_CHECKSUM_OFFLAOD_DISABLE;
        pstcMacInit->u32RetryTransmit           = ETH_MAC_RETRY_TRANSMIT_DISABLE;
        pstcMacInit->u32AutoStripPadFCS         = ETH_MAC_AUTO_STRIP_PAD_FCS_DISABLE;
        pstcMacInit->u32BackOffLimit            = ETH_MAC_BACKOFF_LIMIT_10;
        pstcMacInit->u32DeferralCheck           = ETH_MAC_DEFFERRAL_CHECK_DISABLE;
        pstcMacInit->u16PauseTime               = 0U;
        pstcMacInit->u32ZeroQuantaPause         = ETH_MAC_ZERO_QUANTA_PAUSE_DISABLE;
        pstcMacInit->u32PauseLowThreshold       = ETH_MAC_PAUSE_LOWTHRESHOLD_MINUS4;
        pstcMacInit->u32UnicastPauseFrameDetect = ETH_MAC_UNICAST_PAUSEFRAME_DETECT_DISABLE;
        pstcMacInit->u32ReceiveFlowControl      = ETH_MAC_RECEIVE_FLOWCONTROL_DISABLE;
        pstcMacInit->u32TransmitFlowControl     = ETH_MAC_TRANSMIT_FLOWCONTROL_DISABLE;
        pstcMacInit->u32ReceiveAll              = ETH_MAC_RECEIVE_All_DISABLE;
        pstcMacInit->u32DropNotTcpUdp           = ETH_MAC_DROP_NOT_TCPUDP_DISABLE;

        pstcMacInit->u32VlanTagFilter           = ETH_MAC_VLAN_TAG_FILTER_DISABLE;
        pstcMacInit->u32SAFilter                = ETH_MAC_SOURCE_ADDR_FILTER_DISABLE;
        pstcMacInit->u32PassControlFrame        = ETH_MAC_PASS_CTRLFRAME_FORWARD_NOTPAUSE_ALL;
        pstcMacInit->u32BroadcastFrameReception = ETH_MAC_BROADCASTFRAME_RECEPTION_ENABLE;
        pstcMacInit->u32DAFilter                = ETH_MAC_DESTINATION_ADDR_FILTER_NORMAL;
        pstcMacInit->u32MulticastFrameFilter    = ETH_MAC_MULTICASTFRAME_FILTER_PERFECT;
        pstcMacInit->u32UnicastFrameFilter      = ETH_MAC_UNICASTFRAME_FILTER_PERFECT;
        pstcMacInit->u32PromiscuousMode         = ETH_MAC_PROMISCUOUS_MODE_DISABLE;
        pstcMacInit->u32HashTableHigh           = 0UL;
        pstcMacInit->u32HashTableLow            = 0UL;
        pstcMacInit->u32TxVlanInsertMode        = ETH_MAC_TXVLAN_MODE_BYPASS;
        pstcMacInit->u16TxVlanTag               = 0U;
        pstcMacInit->u32RxVlanFilter            = ETH_MAC_RXVLAN_FILTER_NORMAL;
        pstcMacInit->u32RxVlanComparison        = ETH_MAC_RXVLAN_COMPARISON_16BIT;
        pstcMacInit->u16RxVlanTag               = 0U;
        pstcMacInit->u16RxVlanHashTable         = 0U;
    }

    return enRet;
}

/**
 * @brief  Set MAC duplex mode and speed.
 * @param  [in] u32DuplexMode               MAC duplex mode
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MAC_MODE_HALFDUPLEX:  Half duplex mode
 *           @arg ETH_MAC_MODE_FULLDUPLEX:  Full duplex mode
 * @param  [in] u32Speed                    MAC speed
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MAC_SPEED_10M:        10Mbps
 *           @arg ETH_MAC_SPEED_100M:       100Mbps
 * @retval None
 */
void ETH_MAC_SetDuplexSpeed(uint32_t u32DuplexMode, uint32_t u32Speed)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_MAC_DUPLEX_MODE(u32DuplexMode));
    DDL_ASSERT(IS_ETH_MAC_SPEED(u32Speed));

    MODIFY_REG32(M4_ETH->MAC_CONFIGR, (ETH_MAC_CONFIGR_FES | ETH_MAC_CONFIGR_DM),
                 (u32DuplexMode | u32Speed));
}

/**
 * @brief  Set MAC hash table.
 * @param  [in] u32HashHigh                 Hash table high value.
 * @param  [in] u32HashLow                  Hash table low value.
 * @retval None
 */
void ETH_MAC_SetHashTable(uint32_t u32HashHigh, uint32_t u32HashLow)
{
    WRITE_REG32(M4_ETH->MAC_HASHTLR, u32HashLow);
    WRITE_REG32(M4_ETH->MAC_HASHTHR, u32HashHigh);
}

/**
 * @brief  Set MAC Tx VLAN tag value.
 * @param  [in] u16TxTag                    The tag value of Tx VLAN.
 * @retval None
 */
void ETH_MAC_SetTxVlanTagVal(uint16_t u16TxTag)
{
    MODIFY_REG32(M4_ETH->MAC_VTACTLR, ETH_MAC_VTACTLR_VLANV, u16TxTag);
}

/**
 * @brief  Set MAC Rx VLAN tag value.
 * @param  [in] u16RxTag                    The tag value of Rx VLAN.
 * @retval None
 */
void ETH_MAC_SetRxVlanTagVal(uint16_t u16RxTag)
{
    MODIFY_REG32(M4_ETH->MAC_VTAFLTR, ETH_MAC_VTAFLTR_VLFLT, u16RxTag);
}

/**
 * @brief  Set MAC Rx VLAN hash table.
 * @param  [in] u16HashVal                  The value of Rx VLAN hash table.
 * @retval None
 */
void ETH_MAC_SetRxVlanHashTable(uint16_t u16HashVal)
{
    WRITE_REG32(M4_ETH->MAC_VLAHTBR, u16HashVal);
}

/**
 * @brief  Enable or disable MAC loopback.
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_MAC_LoopBackCmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_ETH->MAC_CONFIGR_b.LM, enNewSta);
}

/**
 * @brief  Enable or disable MAC Back Pressure.
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_MAC_BackPressureCmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_ETH->MAC_FLOCTLR_b.FCA_BPA, enNewSta);
}

/**
 * @brief  Enable or disable MAC Transmit.
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_MAC_TransmitCmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_ETH->MAC_CONFIGR_b.TE, enNewSta);
}

/**
 * @brief  Enable or disable MAC Receive.
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_MAC_ReceiveCmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_ETH->MAC_CONFIGR_b.RE, enNewSta);
}

/**
 * @brief  Enable or disable MAC interrupt.
 * @param  [in] u32IntSrc                   MAC interrupt source type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MAC_INT_TSPIM:        Time stamp trigger interrupt (on MAC)
 *           @arg ETH_MAC_INT_PMTIM:        PMT interrupt (on MAC)
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_MAC_IntCmd(uint32_t u32IntSrc, en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_MAC_INTERRUPT(u32IntSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    if (Disable != enNewSta)
    {
        CLEAR_REG32_BIT(M4_ETH->MAC_INTMSKR, u32IntSrc);
    }
    else
    {
        SET_REG32_BIT(M4_ETH->MAC_INTMSKR, u32IntSrc);
    }
}

/**
 * @brief  Get MAC interrupt status.
 * @param  [in] u32Flag                     MAC interrupt flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MAC_INT_FLAG_TSPIS:   Time stamp trigger flag (on MAC)
 *           @arg ETH_MAC_INT_FLAG_MMCTXIS: MMC transmit flag
 *           @arg ETH_MAC_INT_FLAG_MMCRXIS: MMC receive flag
 *           @arg ETH_MAC_INT_FLAG_MMCIS:   MMC flag (on MAC)
 *           @arg ETH_MAC_INT_FLAG_PMTIS:   PMT flag (on MAC)
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t ETH_MAC_GetIntStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_MAC_INTERRUPT_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(M4_ETH->MAC_INTSTSR, u32Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/******************************************************************************/
/*                          MAC Address Functions                             */
/******************************************************************************/
/**
 * @brief  De-Initialize MAC Address.
 * @param  [in] u32Index                    MAC address index.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDRESS0:         MAC address 0
 *           @arg ETH_MAC_ADDRESS1:         MAC address 1
 *           @arg ETH_MAC_ADDRESS2:         MAC address 2
 *           @arg ETH_MAC_ADDRESS3:         MAC address 3
 *           @arg ETH_MAC_ADDRESS4:         MAC address 4
 * @retval None
 */
void ETH_MACADDR_DeInit(uint32_t u32Index)
{
    __IO uint32_t *MACADHR;
    __IO uint32_t *MACADLR;
    uint32_t u32MacHigh = 0x0000FFFFUL;

    DDL_ASSERT(IS_ETH_MAC_ADDRESS_NORMAL_INDEX(u32Index));

    MACADHR = (__IO uint32_t *)ETH_MAC_MACADHRx(u32Index);
    MACADLR = (__IO uint32_t *)ETH_MAC_MACADLRx(u32Index);
    if (ETH_MAC_ADDRESS0 == u32Index)
    {
        u32MacHigh |= 0x80000000UL;
    }
    WRITE_REG32(*MACADHR, u32MacHigh);
    WRITE_REG32(*MACADLR, 0xFFFFFFFFUL);
}

/**
 * @brief  Initialize MAC Address.
 * @param  [in] u32Index                    MAC address index.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDRESS0:         MAC address 0
 *           @arg ETH_MAC_ADDRESS1:         MAC address 1
 *           @arg ETH_MAC_ADDRESS2:         MAC address 2
 *           @arg ETH_MAC_ADDRESS3:         MAC address 3
 *           @arg ETH_MAC_ADDRESS4:         MAC address 4
 * @param  [in] pstcMacAddrInit             Pointer to a @ref stc_eth_mac_addr_config_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: MAC Address Initialize success
 *           - ErrorInvalidParameter: pstcMacAddrInit == NULL
 */
en_result_t ETH_MACADDR_Init(uint32_t u32Index, const stc_eth_mac_addr_config_t *pstcMacAddrInit)
{
    en_result_t enRet = Ok;
    __IO uint32_t *MACADHR;
    __IO uint32_t *MACADLR;
    uint32_t u32TempReg;
    uint32_t *pu32AddrLow;

    if (NULL == pstcMacAddrInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_MAC_ADDRESS_NORMAL_INDEX(u32Index));
        DDL_ASSERT(IS_ETH_MAC_ADDRESS_FILTER(pstcMacAddrInit->u32MacAddrFilter));
        DDL_ASSERT(IS_ETH_MAC_ADDRESS_MASK(pstcMacAddrInit->u32MacAddrMask));

        MACADHR = (__IO uint32_t *)ETH_MAC_MACADHRx(u32Index);
        MACADLR = (__IO uint32_t *)ETH_MAC_MACADLRx(u32Index);
        /* Set MAC address high register */
        u32TempReg = ((uint32_t)pstcMacAddrInit->au8MACAddr[5] << 8U) | (uint32_t)pstcMacAddrInit->au8MACAddr[4];
        if (ETH_MAC_ADDRESS0 != u32Index)
        {
            u32TempReg |= pstcMacAddrInit->u32MacAddrFilter | pstcMacAddrInit->u32MacAddrMask;
        }
        WRITE_REG32(*MACADHR, u32TempReg);
        /* Set MAC address low register */
        pu32AddrLow = (uint32_t *)((uint32_t)&(pstcMacAddrInit->au8MACAddr[0]));
        WRITE_REG32(*MACADLR, *pu32AddrLow);
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_eth_mac_addr_config_t to default values.
 * @param  [out] pstcMacAddrInit            Pointer to a @ref stc_eth_mac_addr_config_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Structure Initialize success
 *           - ErrorInvalidParameter: pstcMacAddrInit == NULL
 */
en_result_t ETH_MACADDR_StructInit(stc_eth_mac_addr_config_t *pstcMacAddrInit)
{
    en_result_t enRet = Ok;
    uint8_t i;

    if (NULL == pstcMacAddrInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcMacAddrInit->u32MacAddrFilter = ETH_MAC_ADDRESS_FILTER_DISABLE;
        pstcMacAddrInit->u32MacAddrMask = ETH_MAC_ADDRESS_MASK_DISABLE;
        for (i=0U; i<ETH_MAC_ADDRESS_BYTE_LENGTH; i++)
        {
            pstcMacAddrInit->au8MACAddr[i] = 0x00U;
        }
    }

    return enRet;
}

/**
 * @brief  Set MAC Address.
 * @param  [in] u32Index                    MAC address index.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDRESS0:         MAC address 0
 *           @arg ETH_MAC_ADDRESS1:         MAC address 1
 *           @arg ETH_MAC_ADDRESS2:         MAC address 2
 *           @arg ETH_MAC_ADDRESS3:         MAC address 3
 *           @arg ETH_MAC_ADDRESS4:         MAC address 4
 * @param  [in] au8Addr                     Pointer to MAC address buffer(6 bytes).
 * @retval An en_result_t enumeration value:
 *           - Ok: Set address success
 *           - ErrorInvalidParameter: au8Addr == NULL
 */
en_result_t ETH_MACADDR_SetAddress(uint32_t u32Index, uint8_t au8Addr[])
{
    en_result_t enRet = Ok;
    __IO uint32_t *MACADHR;
    __IO uint32_t *MACADLR;
    uint32_t u32TempReg;
    uint32_t *pu32AddrLow;

    if (NULL == au8Addr)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_MAC_ADDRESS_NORMAL_INDEX(u32Index));

        MACADHR = (__IO uint32_t *)ETH_MAC_MACADHRx(u32Index);
        MACADLR = (__IO uint32_t *)ETH_MAC_MACADLRx(u32Index);
        /* Set MAC address high register */
        u32TempReg = ((uint32_t)au8Addr[5] << 8U) | (uint32_t)au8Addr[4];
        WRITE_REG32(*MACADHR, u32TempReg);
        /* Set MAC address low register */
        pu32AddrLow = (uint32_t *)((uint32_t)&(au8Addr[0]));
        WRITE_REG32(*MACADLR, *pu32AddrLow);
    }

    return enRet;
}

/**
 * @brief  Get MAC Address.
 * @param  [in] u32Index                    MAC address index.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDRESS0:         MAC address 0
 *           @arg ETH_MAC_ADDRESS1:         MAC address 1
 *           @arg ETH_MAC_ADDRESS2:         MAC address 2
 *           @arg ETH_MAC_ADDRESS3:         MAC address 3
 *           @arg ETH_MAC_ADDRESS4:         MAC address 4
 * @param  [out] au8Addr                    Pointer to MAC address buffer(6 bytes).
 * @retval An en_result_t enumeration value:
 *           - Ok: Set address success
 *           - ErrorInvalidParameter: au8Addr == NULL
 */
en_result_t ETH_MACADDR_GetAddress(uint32_t u32Index, uint8_t au8Addr[])
{
    en_result_t enRet = Ok;
    __IO uint32_t *MACADHR;
    __IO uint32_t *MACADLR;
    uint32_t u32TempReg;
    uint32_t *pu32AddrLow;

    if (NULL == au8Addr)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_MAC_ADDRESS_NORMAL_INDEX(u32Index));

        MACADHR    = (__IO uint32_t *)ETH_MAC_MACADHRx(u32Index);
        MACADLR    = (__IO uint32_t *)ETH_MAC_MACADLRx(u32Index);
        /* Get MAC address high */
        u32TempReg = READ_REG32(*MACADHR);
        au8Addr[5] = (uint8_t)((u32TempReg >> 8U) & 0x000000FFUL);
        au8Addr[4] = (uint8_t)(u32TempReg & 0x000000FFUL);
        /* Get MAC address low */
        pu32AddrLow = (uint32_t *)((uint32_t)&(au8Addr[0]));
        *pu32AddrLow = READ_REG32(*MACADLR);
    }

    return enRet;
}

/**
 * @brief  Set MAC Address filter mode.
 * @param  [in] u32Index                    MAC address index.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDRESS1:         MAC address 1
 *           @arg ETH_MAC_ADDRESS2:         MAC address 2
 *           @arg ETH_MAC_ADDRESS3:         MAC address 3
 *           @arg ETH_MAC_ADDRESS4:         MAC address 4
 * @param  [in] u32Mode                     MAC address filter mode.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDRESS_FILTER_DISABLE:       Disable perfect filter with MAC address.
 *           @arg ETH_MAC_ADDRESS_FILTER_PERFECT_DA:    Filter the DA address of the received frame with MAC address.
 *           @arg ETH_MAC_ADDRESS_FILTER_PERFECT_SA:    Filter the SA address of the received frame with MAC address.
 * @retval None
 */
void ETH_MACADDR_SetFilterMode(uint32_t u32Index, uint32_t u32Mode)
{
    __IO uint32_t *MACADHR;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_MAC_ADDRESS_SPECIAL_INDEX(u32Index));
    DDL_ASSERT(IS_ETH_MAC_ADDRESS_FILTER(u32Mode));

    MACADHR = (__IO uint32_t *)ETH_MAC_MACADHRx(u32Index);
    MODIFY_REG32(*MACADHR, (ETH_MAC_MACADHR1_SA1 | ETH_MAC_MACADHR1_AE1), u32Mode);
}

/**
 * @brief  Set MAC Address Transmit priority ratio.
 * @param  [in] u32Index                    MAC address index.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDRESS1:         MAC address 1
 *           @arg ETH_MAC_ADDRESS2:         MAC address 2
 *           @arg ETH_MAC_ADDRESS3:         MAC address 3
 *           @arg ETH_MAC_ADDRESS4:         MAC address 4
 * @param  [in] u32Mask                     MAC address filter mask.
 *         This parameter can be one of the following values or any combination
 *         of BYTE1 through BYTE6:
 *           @arg ETH_MAC_ADDRESS_MASK_DISABLE: Disable MAC Address Mask
 *           @arg ETH_MAC_ADDRESS_MASK_BYTE6:   Mask MAC Address high reg bits [15:8]
 *           @arg ETH_MAC_ADDRESS_MASK_BYTE5:   Mask MAC Address high reg bits [7:0]
 *           @arg ETH_MAC_ADDRESS_MASK_BYTE4:   Mask MAC Address low reg bits [31:24]
 *           @arg ETH_MAC_ADDRESS_MASK_BYTE3:   Mask MAC Address low reg bits [23:16]
 *           @arg ETH_MAC_ADDRESS_MASK_BYTE2:   Mask MAC Address low reg bits [15:8]
 *           @arg ETH_MAC_ADDRESS_MASK_BYTE1:   Mask MAC Address low reg bits [7:0]
 *           @arg ETH_MAC_ADDRESS_MASK_ALL:     Mask MAC Address low reg bits [31:0] and low high bits [15:0]
 * @retval None
 */
void ETH_MACADDR_SetFilterMask(uint32_t u32Index, uint32_t u32Mask)
{
    __IO uint32_t *MACADHR;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_MAC_ADDRESS_SPECIAL_INDEX(u32Index));
    DDL_ASSERT(IS_ETH_MAC_ADDRESS_MASK(u32Mask));

    MACADHR = (__IO uint32_t *)ETH_MAC_MACADHRx(u32Index);
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
    WRITE_REG32(bM4_ETH->MAC_FLTCTLR_b.IPFE, Disable);
    WRITE_REG32(M4_ETH->MAC_L34CTLR,  0UL);
    WRITE_REG32(M4_ETH->MAC_L4PORTR,  0UL);
    WRITE_REG32(M4_ETH->MAC_L3ADDRR0, 0UL);
    WRITE_REG32(M4_ETH->MAC_L3ADDRR1, 0UL);
    WRITE_REG32(M4_ETH->MAC_L3ADDRR2, 0UL);
    WRITE_REG32(M4_ETH->MAC_L3ADDRR3, 0UL);
}

/**
 * @brief  Initialize MAC L3L4 Filter.
 * @param  [in] pstcL3L4FilterInit          Pointer to a @ref stc_eth_l3l4_filter_config_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: MAC L3L4 Filter Initialize success
 *           - ErrorInvalidParameter: pstcL3L4FilterInit == NULL
 */
en_result_t ETH_MAC_L3L4FilterInit(const stc_eth_l3l4_filter_config_t *pstcL3L4FilterInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcL3L4FilterInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_MAC_L4_DESTPORT_FILTER(pstcL3L4FilterInit->u32L4DestPortFilter));
        DDL_ASSERT(IS_ETH_MAC_L4_SOURCEPORT_FILTER(pstcL3L4FilterInit->u32L4SourcePortFilter));
        DDL_ASSERT(IS_ETH_MAC_L4_PORT_FILTER_PROTOCOL(pstcL3L4FilterInit->u32L4PortFilterProtocol));
        DDL_ASSERT(IS_ETH_MAC_L3_DA_FILTER_MASK(pstcL3L4FilterInit->u32L3Ipv4DAFilterMask));
        DDL_ASSERT(IS_ETH_MAC_L3_SA_FILTER_MASK(pstcL3L4FilterInit->u32L3Ipv4SAFilterMask));
        DDL_ASSERT(IS_ETH_MAC_L3_DA_SA_FILTER_MASK(pstcL3L4FilterInit->u32L3Ipv6AddrFilterMask));
        DDL_ASSERT(IS_ETH_MAC_L3_DA_FILTER(pstcL3L4FilterInit->u32L3DAFilter));
        DDL_ASSERT(IS_ETH_MAC_L3_SA_FILTER(pstcL3L4FilterInit->u32L3SAFilter));
        DDL_ASSERT(IS_ETH_MAC_L3_ADDR_FILTER_PROTOCOL(pstcL3L4FilterInit->u32L3AddrFilterProtocol));

        /* Set L3/L4 control register */
        if (ETH_MAC_L3_ADDR_FILTER_PROTOCOL_IPV4 != pstcL3L4FilterInit->u32L3AddrFilterProtocol)
        {
            WRITE_REG32(M4_ETH->MAC_L34CTLR,
                        (pstcL3L4FilterInit->u32L4DestPortFilter     | pstcL3L4FilterInit->u32L4SourcePortFilter   |
                         pstcL3L4FilterInit->u32L4PortFilterProtocol | pstcL3L4FilterInit->u32L3Ipv6AddrFilterMask |
                         pstcL3L4FilterInit->u32L3DAFilter           | pstcL3L4FilterInit->u32L3SAFilter           |
                         pstcL3L4FilterInit->u32L3AddrFilterProtocol));
            WRITE_REG32(M4_ETH->MAC_L3ADDRR0, pstcL3L4FilterInit->au32L3Ipv6AddrFilterValue[0]);
            WRITE_REG32(M4_ETH->MAC_L3ADDRR1, pstcL3L4FilterInit->au32L3Ipv6AddrFilterValue[1]);
            WRITE_REG32(M4_ETH->MAC_L3ADDRR2, pstcL3L4FilterInit->au32L3Ipv6AddrFilterValue[2]);
            WRITE_REG32(M4_ETH->MAC_L3ADDRR3, pstcL3L4FilterInit->au32L3Ipv6AddrFilterValue[3]);
        }
        /* IPv4 protocol*/
        else
        {
            WRITE_REG32(M4_ETH->MAC_L34CTLR,
                        (pstcL3L4FilterInit->u32L4DestPortFilter     | pstcL3L4FilterInit->u32L4SourcePortFilter |
                         pstcL3L4FilterInit->u32L4PortFilterProtocol | pstcL3L4FilterInit->u32L3Ipv4DAFilterMask |
                         pstcL3L4FilterInit->u32L3Ipv4SAFilterMask   | pstcL3L4FilterInit->u32L3DAFilter         |
                         pstcL3L4FilterInit->u32L3SAFilter           | pstcL3L4FilterInit->u32L3AddrFilterProtocol));
            WRITE_REG32(M4_ETH->MAC_L3ADDRR0, pstcL3L4FilterInit->u32L3Ipv4SAFilterValue);
            WRITE_REG32(M4_ETH->MAC_L3ADDRR1, pstcL3L4FilterInit->u32L3Ipv4DAFilterValue);
        }
        WRITE_REG32(M4_ETH->MAC_L4PORTR, ((((uint32_t)pstcL3L4FilterInit->u16L4DestProtFilterValue) << ETH_MAC_L4PORTR_L4DPVAL_POS) |
                    pstcL3L4FilterInit->u16L4SourceProtFilterValue));
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_eth_l3l4_filter_config_t to default values.
 * @param  [out] pstcL3L4FilterInit         Pointer to a @ref stc_eth_l3l4_filter_config_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Structure Initialize success
 *           - ErrorInvalidParameter: pstcL3L4FilterInit == NULL
 */
en_result_t ETH_MAC_L3L4FilterStructInit(stc_eth_l3l4_filter_config_t *pstcL3L4FilterInit)
{
    en_result_t enRet = Ok;
    uint8_t i;

    if (NULL == pstcL3L4FilterInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcL3L4FilterInit->u32L4DestPortFilter        = ETH_MAC_L4_DESTPORT_FILTER_DISABLE;
        pstcL3L4FilterInit->u32L4SourcePortFilter      = ETH_MAC_L4_SOURCEPORT_FILTER_DISABLE;
        pstcL3L4FilterInit->u32L4PortFilterProtocol    = ETH_MAC_L4_PORT_FILTER_PROTOCOL_TCP;
        pstcL3L4FilterInit->u32L3Ipv4DAFilterMask      = ETH_MAC_L3_DA_FILTER_MASK_NONE;
        pstcL3L4FilterInit->u32L3Ipv4SAFilterMask      = ETH_MAC_L3_SA_FILTER_MASK_NONE;
        pstcL3L4FilterInit->u32L3Ipv6AddrFilterMask    = ETH_MAC_L3_DA_SA_FILTER_MASK_NONE;
        pstcL3L4FilterInit->u32L3DAFilter              = ETH_MAC_L3_DA_FILTER_DISABLE;
        pstcL3L4FilterInit->u32L3SAFilter              = ETH_MAC_L3_SA_FILTER_DISABLE;
        pstcL3L4FilterInit->u32L3AddrFilterProtocol    = ETH_MAC_L3_ADDR_FILTER_PROTOCOL_IPV4;
        pstcL3L4FilterInit->u16L4DestProtFilterValue   = 0U;
        pstcL3L4FilterInit->u16L4SourceProtFilterValue = 0U;
        pstcL3L4FilterInit->u32L3Ipv4DAFilterValue     = 0UL;
        pstcL3L4FilterInit->u32L3Ipv4SAFilterValue     = 0UL;
        for (i=0U; i<4U; i++)
        {
            pstcL3L4FilterInit->au32L3Ipv6AddrFilterValue[i] = 0UL;
        }
    }

    return enRet;
}

/**
 * @brief  Enable or disable MAC L3L4 Filter function.
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_MAC_L3L4FilterCmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_ETH->MAC_FLTCTLR_b.IPFE, enNewSta);
}

/**
 * @brief  Set L4 port filter protocol.
 * @param  [in] u32PortProtocol             MAC L4 port filter protocol.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_L4_PORT_FILTER_PROTOCOL_TCP:  Port filter for TCP frame
 *           @arg ETH_MAC_L4_PORT_FILTER_PROTOCOL_UDP:  Port filter for UDP frame
 * @retval None
 */
void ETH_MAC_SetPortFilterProtocol(uint32_t u32PortProtocol)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_MAC_L4_PORT_FILTER_PROTOCOL(u32PortProtocol));

    WRITE_REG32(bM4_ETH->MAC_L34CTLR_b.L4PEN, (u32PortProtocol >> ETH_MAC_L34CTLR_L4PEN_POS));
}

/**
 * @brief  Set L4 Destination port filter value.
 * @param  [in] u16Port                     The value of Destination port.
 * @retval None
 */
void ETH_MAC_SetDestPortFilterVal(uint16_t u16Port)
{
    MODIFY_REG32(M4_ETH->MAC_L4PORTR, ETH_MAC_L4PORTR_L4DPVAL, ((uint32_t)u16Port << 16U));
}

/**
 * @brief  Set L4 Source port filter value.
 * @param  [in] u16Port                     The value of Source port.
 * @retval None
 */
void ETH_MAC_SetSrcPortFilterVal(uint16_t u16Port)
{
    MODIFY_REG32(M4_ETH->MAC_L4PORTR, ETH_MAC_L4PORTR_L4SPVAL, u16Port);
}

/**
 * @brief  Set L3 address filter protocol.
 * @param  [in] u32AddrProtocol             MAC L3 address filter protocol.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_L3_ADDR_FILTER_PROTOCOL_IPV4: Ip Address filter for IPv4
 *           @arg ETH_MAC_L3_ADDR_FILTER_PROTOCOL_IPV6: Ip Address filter for IPv6
 * @retval None
 */
void ETH_MAC_SetAddrFilterProtocol(uint32_t u32AddrProtocol)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_MAC_L3_ADDR_FILTER_PROTOCOL(u32AddrProtocol));

    WRITE_REG32(bM4_ETH->MAC_L34CTLR_b.L3PEN, u32AddrProtocol);
}

/**
 * @brief  Set L3 Destination address filter value of IPv4.
 * @param  [in] u32Addr                     The value of Destination address.
 * @retval None
 */
void ETH_MAC_SetIpv4DestAddrFilterVal(uint32_t u32Addr)
{
    WRITE_REG32(M4_ETH->MAC_L3ADDRR1, u32Addr);
}

/**
 * @brief  Set L3 Source address filter value of IPv4.
 * @param  [in] u32Addr                     The value of Source address.
 * @retval None
 */
void ETH_MAC_SetIpv4SrcAddrFilterVal(uint32_t u32Addr)
{
    WRITE_REG32(M4_ETH->MAC_L3ADDRR0, u32Addr);
}

/**
 * @brief  Set L3 Destination/Source Address filter value of IPv6.
 * @param  [in] au32Addr                    Pointer to Destination/Source Address buffer(4 words).
 * @retval An en_result_t enumeration value:
 *           - Ok: Set Address filter value success
 *           - ErrorInvalidParameter: au32Addr == NULL
 */
en_result_t ETH_MAC_SetIpv6AddrFilterVal(const uint32_t au32Addr[])
{
    en_result_t enRet = Ok;

    if (NULL == au32Addr)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        WRITE_REG32(M4_ETH->MAC_L3ADDRR0, au32Addr[0]);
        WRITE_REG32(M4_ETH->MAC_L3ADDRR1, au32Addr[1]);
        WRITE_REG32(M4_ETH->MAC_L3ADDRR2, au32Addr[2]);
        WRITE_REG32(M4_ETH->MAC_L3ADDRR3, au32Addr[3]);
    }

    return enRet;
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
    WRITE_REG32(M4_ETH->DMA_BUSMODR, 0x00020101UL);
    WRITE_REG32(M4_ETH->DMA_OPRMODR, 0U);
    WRITE_REG32(M4_ETH->DMA_INTENAR, 0U);
    WRITE_REG32(M4_ETH->DMA_REVWDTR, 0U);
    WRITE_REG32(M4_ETH->DMA_TXDLADR, 0U);
    WRITE_REG32(M4_ETH->DMA_RXDLADR, 0U);
}

/**
 * @brief  Initialize DMA.
 * @param  [in] pstcDmaInit                 Pointer to a @ref stc_eth_dma_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: DMA Initialize success
 *           - ErrorInvalidParameter: pstcDmaInit == NULL
 */
en_result_t ETH_DMA_Init(const stc_eth_dma_init_t *pstcDmaInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcDmaInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMA_BURST_MODE(pstcDmaInit->u32BurstMode));
        DDL_ASSERT(IS_ETH_DMA_ADDRESS_ALIGN(pstcDmaInit->u32AddressAlign));
        DDL_ASSERT(IS_ETH_DMA_RX_BURST_LENGTH(pstcDmaInit->u32RxDMABurstLength));
        DDL_ASSERT(IS_ETH_DMA_TX_BURST_LENGTH(pstcDmaInit->u32TxDMABurstLength));
        DDL_ASSERT(IS_ETH_DMA_ENHANCE_DESCRIPTOR(pstcDmaInit->u32EnhanceDescriptor));
        DDL_ASSERT(IS_ETH_DMA_DESC_SKIP_LENGTH(pstcDmaInit->u32DescriptorSkipLength));
        DDL_ASSERT(IS_ETH_DMA_PRIORITY_ARBITRATION(pstcDmaInit->u32DMAArbitration));
        DDL_ASSERT(IS_ETH_DMA_DROP_CHECKSUM_ERRORFRAME(pstcDmaInit->u32DropChecksumErrorFrame));
        DDL_ASSERT(IS_ETH_DMA_RECEIVE_STORE_FORWARD(pstcDmaInit->u32ReceiveStoreForward));
        DDL_ASSERT(IS_ETH_DMA_FLUSH_RECEIVEDFRAME(pstcDmaInit->u32FlushReceiveFrame));
        DDL_ASSERT(IS_ETH_DMA_TRANSMIT_STORE_FORWARD(pstcDmaInit->u32TransmitStoreForward));
        DDL_ASSERT(IS_ETH_DMA_TRANSMIT_THRESHOLD(pstcDmaInit->u32TransmitThreshold));
        DDL_ASSERT(IS_ETH_DMA_FORWARD_ERRORFRAME(pstcDmaInit->u32ForwardErrorFrame));
        DDL_ASSERT(IS_ETH_DMA_FORWARD_UNDERSIZE_GOODFRAME(pstcDmaInit->u32ForwardUndersizeGoodFrame));
        DDL_ASSERT(IS_ETH_DMA_DROP_JUMBO_FRAME(pstcDmaInit->u32DropJumboFrame));
        DDL_ASSERT(IS_ETH_DMA_RECEIVE_THRESHOLD(pstcDmaInit->u32ReceiveThreshold));
        DDL_ASSERT(IS_ETH_DMA_SECONDFRAME_OPERARTE(pstcDmaInit->u32SecondFrameOperate));

        /* Set Bus mode register */
        MODIFY_REG32(M4_ETH->DMA_BUSMODR, ETH_DMA_BUSMODR_CLEAR_MASK,
                     (pstcDmaInit->u32BurstMode        | pstcDmaInit->u32AddressAlign      | pstcDmaInit->u32RxDMABurstLength     |
                      pstcDmaInit->u32TxDMABurstLength | pstcDmaInit->u32EnhanceDescriptor | pstcDmaInit->u32DescriptorSkipLength |
                      pstcDmaInit->u32DMAArbitration   | ETH_DMA_BUSMODR_SPBL));
        /* Set Operation mode register */
        MODIFY_REG32(M4_ETH->DMA_OPRMODR, ETH_DMA_OPRMODR_CLEAR_MASK,
                     (pstcDmaInit->u32DropChecksumErrorFrame    | pstcDmaInit->u32ReceiveStoreForward | pstcDmaInit->u32FlushReceiveFrame |
                      pstcDmaInit->u32TransmitStoreForward      | pstcDmaInit->u32TransmitThreshold   | pstcDmaInit->u32ForwardErrorFrame |
                      pstcDmaInit->u32ForwardUndersizeGoodFrame | pstcDmaInit->u32DropJumboFrame      | pstcDmaInit->u32ReceiveThreshold  |
                      pstcDmaInit->u32SecondFrameOperate));
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_eth_dma_init_t to default values.
 * @param  [out] pstcDmaInit                Pointer to a @ref stc_eth_dma_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Structure Initialize success
 *           - ErrorInvalidParameter: pstcDmaInit == NULL
 */
en_result_t ETH_DMA_StructInit(stc_eth_dma_init_t *pstcDmaInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcDmaInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcDmaInit->u32BurstMode                 = ETH_DMA_BURST_MODE_FIXED;
        pstcDmaInit->u32AddressAlign              = ETH_DMA_ADDRESS_ALIGN_ENABLE;
        pstcDmaInit->u32RxDMABurstLength          = ETH_DMA_RX_BURST_LENGTH_32BEAT;
        pstcDmaInit->u32TxDMABurstLength          = ETH_DMA_TX_BURST_LENGTH_32BEAT;
        pstcDmaInit->u32EnhanceDescriptor         = ETH_DMA_ENHANCE_DESCRIPTOR_ENABLE;
        pstcDmaInit->u32DescriptorSkipLength      = 0U;
        pstcDmaInit->u32DMAArbitration            = ETH_DMA_ARBITRATION_LOOP_RXTX_1_1;
        pstcDmaInit->u32DropChecksumErrorFrame    = ETH_DMA_DROP_CHECKSUM_ERRORFRAME_ENABLE;
        pstcDmaInit->u32ReceiveStoreForward       = ETH_DMA_RECEIVE_STORE_FORWARD_ENABLE;
        pstcDmaInit->u32FlushReceiveFrame         = ETH_DMA_FLUSH_RECEIVEDFRAME_ENABLE;
        pstcDmaInit->u32TransmitStoreForward      = ETH_DMA_TRANSMIT_STORE_FORWARD_ENABLE;
        pstcDmaInit->u32TransmitThreshold         = ETH_DMA_TRANSMIT_THRESHOLD_64BYTE;
        pstcDmaInit->u32ForwardErrorFrame         = ETH_DMA_FORWARD_ERRORFRAME_DISABLE;
        pstcDmaInit->u32ForwardUndersizeGoodFrame = ETH_DMA_FORWARD_UNDERSIZE_GOODFRAME_DISABLE;
        pstcDmaInit->u32DropJumboFrame            = ETH_DMA_DROP_JUMBO_FRAME_DISABLE;
        pstcDmaInit->u32ReceiveThreshold          = ETH_DMA_RECEIVE_THRESHOLD_64BYTE;
        pstcDmaInit->u32SecondFrameOperate        = ETH_DMA_SECONDFRAME_OPERARTE_ENABLE;
    }

    return enRet;
}

/**
 * @brief  Set DMA software reset.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Software reset success
 *           - ErrorTimeout: Reset timeout
 */
en_result_t ETH_DMA_SoftwareReset(void)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Ok;

    WRITE_REG32(bM4_ETH->DMA_BUSMODR_b.SWR, 1U);
    u32Count = ETH_TIMEOUT_SOFTWARE_RESET * (HCLK_VALUE / 20000UL);
    while (0UL != READ_REG32(bM4_ETH->DMA_BUSMODR_b.SWR))
    {
        if (0UL == u32Count)
        {
            enRet = ErrorTimeout;
            break;
        }
        u32Count--;
    }

    return enRet;
}

/**
 * @brief  Set DMA Transmit priority ratio.
 * @param  [in] u32PrioRatio                Priority ratio
 *         This parameter can be one of the following values:
 *           @arg ETH_DMA_ARBITRATION_LOOP_RXTX_1_1:        Rx:Tx = 1:1
 *           @arg ETH_DMA_ARBITRATION_LOOP_RXTX_2_1:        Rx:Tx = 2:1
 *           @arg ETH_DMA_ARBITRATION_LOOP_RXTX_3_1:        Rx:Tx = 3:1
 *           @arg ETH_DMA_ARBITRATION_LOOP_RXTX_4_1:        Rx:Tx = 4:1
 *           @arg ETH_DMA_ARBITRATION_LOOP_TXRX_1_1:        Tx:Rx = 1:1
 *           @arg ETH_DMA_ARBITRATION_LOOP_TXRX_2_1:        Tx:Rx = 2:1
 *           @arg ETH_DMA_ARBITRATION_LOOP_TXRX_3_1:        Tx:Rx = 3:1
 *           @arg ETH_DMA_ARBITRATION_LOOP_TXRX_4_1:        Tx:Rx = 4:1
 *           @arg ETH_DMA_ARBITRATION_FIXED_RXPRIORTX:      Fixed priority: Rx is higher than Tx
 *           @arg ETH_DMA_ARBITRATION_FIXED_TXPRIORRX:      Fixed priority: Tx is higher than Rx
 * @retval None
 */
void ETH_DMA_SetTransPrioRatio(uint32_t u32PrioRatio)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_DMA_PRIORITY_ARBITRATION(u32PrioRatio));

    MODIFY_REG32(M4_ETH->DMA_BUSMODR,
                 (ETH_DMA_BUSMODR_TXPR | ETH_DMA_BUSMODR_PRAT | ETH_DMA_BUSMODR_DMAA),
                 u32PrioRatio);
}

/**
 * @brief  Set DMA Rx watchdog counter.
 * @param  [in] u8Value                     The value of Watchdog timer
 * @retval None
 */
void ETH_DMA_SetRxWatchdogCounter(uint8_t u8Value)
{
    WRITE_REG32(M4_ETH->DMA_REVWDTR, u8Value);
}

/**
 * @brief  Flush transmit FIFO.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Flush transmit FIFO success
 *           - ErrorTimeout: Flush timeout
 */
en_result_t ETH_DMA_FlushTransmitFIFO(void)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Ok;

    WRITE_REG32(bM4_ETH->DMA_OPRMODR_b.FTF, 1U);
    u32Count = ETH_TIMEOUT_WRITE_REGISTER * (HCLK_VALUE / 20000UL);
    while (0UL != READ_REG32(bM4_ETH->DMA_OPRMODR_b.FTF))
    {
        if (0UL == u32Count)
        {
            enRet = ErrorTimeout;
            break;
        }
        u32Count--;
    }

    return enRet;
}

/**
 * @brief  Enable or disable DMA transmit.
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_DMA_TransmitCmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_ETH->DMA_OPRMODR_b.STT, enNewSta);
}

/**
 * @brief  Enable or disable DMA receive.
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_DMA_ReceiveCmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_ETH->DMA_OPRMODR_b.STR, enNewSta);
}

/**
 * @brief  Enable or disable DMA interrupt.
 * @param  [in] u32IntSrc                   DMA interrupt source
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_DMA_INT_NIE:          Normal interrupt summary
 *           @arg ETH_DMA_INT_AIE:          Abnormal interrupt summary
 *           @arg ETH_DMA_INT_ERE:          Early receive interrupt
 *           @arg ETH_DMA_INT_FBE:          Fatal bus error interrupt
 *           @arg ETH_DMA_INT_ETE:          Early transmit interrupt
 *           @arg ETH_DMA_INT_RWE:          Receive watchdog timeout interrupt
 *           @arg ETH_DMA_INT_RSE:          Receive process stopped interrupt
 *           @arg ETH_DMA_INT_RUE:          Receive buffer unavailable interrupt
 *           @arg ETH_DMA_INT_RIE:          Receive interrupt
 *           @arg ETH_DMA_INT_UNE:          Transmit Underflow interrupt
 *           @arg ETH_DMA_INT_OVE:          Receive Overflow interrupt
 *           @arg ETH_DMA_INT_TJE:          Transmit jabber timeout interrupt
 *           @arg ETH_DMA_INT_TUE:          Transmit buffer unavailable interrupt
 *           @arg ETH_DMA_INT_TSE:          Transmit process stopped interrupt
 *           @arg ETH_DMA_INT_TIE:          Transmit interrupt
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_DMA_IntCmd(uint32_t u32IntSrc, en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_DMA_INTERRUPT(u32IntSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    if (Disable != enNewSta)
    {
        SET_REG32_BIT(M4_ETH->DMA_INTENAR, u32IntSrc);
    }
    else
    {
        CLEAR_REG32_BIT(M4_ETH->DMA_INTENAR, u32IntSrc);
    }
}

/**
 * @brief  Get DMA flag status.
 * @param  [in] u32Flag                     DMA flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_DMA_FLAG_PTPS:        Time-stamp trigger status
 *           @arg ETH_DMA_FLAG_PMTS:        PMT trigger status
 *           @arg ETH_DMA_FLAG_MMCS:        MMC trigger status
 *           @arg ETH_DMA_FLAG_NIS:         Normal interrupt summary flag
 *           @arg ETH_DMA_FLAG_AIS:         Abnormal interrupt summary flag
 *           @arg ETH_DMA_FLAG_ERS:         Early receive flag
 *           @arg ETH_DMA_FLAG_FBS:         Fatal bus error flag
 *           @arg ETH_DMA_FLAG_ETS:         Early transmit flag
 *           @arg ETH_DMA_FLAG_RWS:         Receive watchdog timeout flag
 *           @arg ETH_DMA_FLAG_RSS:         Receive stopped flag
 *           @arg ETH_DMA_FLAG_RUS:         Receive buffer unavailable flag
 *           @arg ETH_DMA_FLAG_RIS:         Receive flag
 *           @arg ETH_DMA_FLAG_UNS:         Transmit Underflow flag
 *           @arg ETH_DMA_FLAG_OVS:         Receive Overflow flag
 *           @arg ETH_DMA_FLAG_TJS:         Transmit jabber timeout flag
 *           @arg ETH_DMA_FLAG_TUS:         Transmit buffer unavailable flag
 *           @arg ETH_DMA_FLAG_TSS:         Transmit stopped flag
 *           @arg ETH_DMA_FLAG_TIS:         Transmit interrupt flag
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t ETH_DMA_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_DMA_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(M4_ETH->DMA_DMASTSR, u32Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/**
 * @brief  Get DMA overflow flag status.
 * @param  [in] u32Flag                     DMA overflow flag type
 *         This parameter can be one of the following values:
 *           @arg ETH_DMA_OVERFLOW_RXFIFO_COUNTER:          Overflow bit for FIFO overflow counter
 *           @arg ETH_DMA_OVERFLOW_MISSFRAME_COUNTER:       Overflow bit for miss frame counter
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t ETH_DMA_GetOvfStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_DMA_MISS_FRAME_TYPE(u32Flag));

    if (0UL != (READ_REG32_BIT(M4_ETH->DMA_RFRCNTR, u32Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/******************************************************************************/
/*                          DMA descriptor Functions                          */
/******************************************************************************/
/**
 * @brief  Initializes DMA Tx descriptor in chain mode.
 * @param  [in] pstcEthHandle               Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] astcTxDescTab               Pointer to the first Tx desc list
 * @param  [in] au8TxBuffer                 Pointer to the first TxBuffer list
 * @param  [in] u32TxBufferCnt              Number of the Tx desc in the list
 * @retval An en_result_t enumeration value:
 *           - Ok: Initializes Tx chain mode success
 *           - ErrorInvalidParameter: pstcEthHandle == NULL or astcTxDescTab == NULL or
 *                                    au8TxBuffer == NULL or u32TxBufferCnt == 0
 */
en_result_t ETH_DMA_TxDescListInit(stc_eth_handle_t *pstcEthHandle, stc_eth_dma_desc_t astcTxDescTab[], const uint8_t au8TxBuffer[], uint32_t u32TxBufferCnt)
{
    uint32_t i;
    stc_eth_dma_desc_t *pstcTxDesc;
    en_result_t enRet = Ok;

    if ((NULL == pstcEthHandle) || (NULL == astcTxDescTab) || (NULL == au8TxBuffer) || (0UL== u32TxBufferCnt))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Set the DMATxDesc pointer with the first in the astcTxDescTab list */
        pstcEthHandle->stcTxDesc = astcTxDescTab;

        /* Fill each DMATxDesc descriptor */
        for (i=0U; i<u32TxBufferCnt; i++)
        {
            pstcTxDesc = &astcTxDescTab[i];
            /* Set Second Address Chained */
            pstcTxDesc->u32ControlStatus = ETH_DMATXDESC_TSAC;
            /* Set Buffer1 address pointer */
            pstcTxDesc->u32Buffer1Addr = (uint32_t)(&au8TxBuffer[i * ETH_TXBUF_SIZE]);
            /* Set the DMA Tx descriptors checksum insertion */
            if (ETH_MAC_CHECKSUM_MODE_HARDWARE == pstcEthHandle->stcCommInit.u32ChecksumMode)
            {
                SET_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMATXDESC_CIC_TCPUDPICMP_FULL);
            }

            /* Initialize the next descriptor with the Next Descriptor Polling */
            if (i < (u32TxBufferCnt - 1U))
            {
                pstcTxDesc->u32Buffer2NextDescAddr = (uint32_t)(&astcTxDescTab[i + 1U]);
            }
            else
            {
                pstcTxDesc->u32Buffer2NextDescAddr = (uint32_t)astcTxDescTab;
            }
        }

        /* Set Transmit Descriptor List Address Register */
        WRITE_REG32(M4_ETH->DMA_TXDLADR, (uint32_t)astcTxDescTab);
    }

    return enRet;
}

/**
 * @brief  Initializes DMA Rx descriptor in chain mode.
 * @param  [in] pstcEthHandle               Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] astcRxDescTab               Pointer to the first Rx desc list
 * @param  [in] au8RxBuffer                 Pointer to the first RxBuffer list
 * @param  [in] u32RxBufferCnt              Number of the Rx desc in the list
 * @retval An en_result_t enumeration value:
 *           - Ok: Initializes Rx chain mode success
 *           - ErrorInvalidParameter: pstcEthHandle == NULL or astcRxDescTab == NULL or
 *                                    au8RxBuffer == NULL or u32RxBufferCnt == 0
 */
en_result_t ETH_DMA_RxDescListInit(stc_eth_handle_t *pstcEthHandle, stc_eth_dma_desc_t astcRxDescTab[], const uint8_t au8RxBuffer[], uint32_t u32RxBufferCnt)
{
    uint32_t i;
    stc_eth_dma_desc_t *pstcRxDesc;
    en_result_t enRet = Ok;

    if ((NULL == pstcEthHandle) || (NULL == astcRxDescTab) || (NULL == au8RxBuffer) || (0UL == u32RxBufferCnt))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Set the DMARxDesc pointer with the first in the astcRxDescTab list */
        pstcEthHandle->stcRxDesc = astcRxDescTab;

        /* Fill each DMARxDesc descriptor */
        for (i=0UL; i<u32RxBufferCnt; i++)
        {
            pstcRxDesc = &astcRxDescTab[i];
            /* Set Own bit of the Rx descriptor */
            pstcRxDesc->u32ControlStatus     = ETH_DMARXDESC_OWN;
            /* Set Buffer1 size and Second Address Chained */
            pstcRxDesc->u32ControlBufferSize = ETH_RXBUF_SIZE | ETH_DMARXDESC_RSAC;
            /* Set Buffer1 address pointer */
            pstcRxDesc->u32Buffer1Addr       = (uint32_t)(&au8RxBuffer[i * ETH_RXBUF_SIZE]);
            /* Set the DMA Rx Descriptor interrupt */
            if (ETH_RX_MODE_INTERRUPT == pstcEthHandle->stcCommInit.u32RxMode)
            {
                CLEAR_REG32_BIT(pstcRxDesc->u32ControlBufferSize, ETH_DMARXDESC_DIC);
            }

            /* Initialize the next descriptor with the Next Descriptor Polling */
            if (i < (u32RxBufferCnt - 1U))
            {
                pstcRxDesc->u32Buffer2NextDescAddr = (uint32_t)(&astcRxDescTab[i + 1U]);
            }
            else
            {
                pstcRxDesc->u32Buffer2NextDescAddr = (uint32_t)astcRxDescTab;
            }
        }

        /* Set Receive Descriptor List Address Register */
        WRITE_REG32(M4_ETH->DMA_RXDLADR, (uint32_t)astcRxDescTab);
    }

    return enRet;
}

/**
 * @brief  Set DMA transmit frame.
 * @param  [in] pstcEthHandle               Pointer to a @ref stc_eth_handle_t structure
 * @param  [in] u32FrameLength              Total of data to be transmit
 * @retval An en_result_t enumeration value:
 *           - Ok: Set transmit frame success
 *           - ErrorInvalidParameter: pstcEthHandle == NULL
 *           - ErrorInvalidMode: Descriptor is owned by the DMA
 */
en_result_t ETH_DMA_SetTransmitFrame(stc_eth_handle_t *pstcEthHandle, uint32_t u32FrameLength)
{
    uint32_t i;
    uint32_t u32BufCnt;
    uint32_t u32Size;
    en_result_t enRet = Ok;

    if ((NULL == pstcEthHandle) || (0U == u32FrameLength))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check if the descriptor is owned by the CPU */
        if (0UL != (pstcEthHandle->stcTxDesc->u32ControlStatus & ETH_DMATXDESC_OWN))
        {
            enRet = ErrorInvalidMode;
        }
        else
        {
            /* Get the number of needed Tx buffers for the current frame */
            if (u32FrameLength > ETH_TXBUF_SIZE)
            {
                u32BufCnt = u32FrameLength / ETH_TXBUF_SIZE;
                if (0UL != (u32FrameLength % ETH_TXBUF_SIZE))
                {
                    u32BufCnt++;
                }
            }
            else
            {
                u32BufCnt = 1U;
            }

            if (1U == u32BufCnt)
            {
                /* Set FIRST and LAST segment */
                SET_REG32_BIT(pstcEthHandle->stcTxDesc->u32ControlStatus, (ETH_DMATXDESC_TFS | ETH_DMATXDESC_TLS));
                /* Set frame size */
                MODIFY_REG32(pstcEthHandle->stcTxDesc->u32ControlBufferSize, ETH_DMATXDESC_TBS1, (u32FrameLength & ETH_DMATXDESC_TBS1));
                /* Set Own bit of the Tx descriptor */
                SET_REG32_BIT(pstcEthHandle->stcTxDesc->u32ControlStatus, ETH_DMATXDESC_OWN);
                /* Point to next descriptor */
                pstcEthHandle->stcTxDesc = (stc_eth_dma_desc_t *)(pstcEthHandle->stcTxDesc->u32Buffer2NextDescAddr);
            }
            else
            {
                for (i=0U; i<u32BufCnt; i++)
                {
                    /* Clear FIRST and LAST segment bits */
                    CLEAR_REG32_BIT(pstcEthHandle->stcTxDesc->u32ControlStatus, (ETH_DMATXDESC_TFS | ETH_DMATXDESC_TLS));
                    if (0U == i)
                    {
                        /* Set the FIRST segment bit */
                        SET_REG32_BIT(pstcEthHandle->stcTxDesc->u32ControlStatus, ETH_DMATXDESC_TFS);
                    }

                    if ((u32BufCnt - 1U) == i)
                    {
                        /* Set the last segment bit */
                        SET_REG32_BIT(pstcEthHandle->stcTxDesc->u32ControlStatus, ETH_DMATXDESC_TLS);
                        u32Size = u32FrameLength - ((u32BufCnt - 1U) * ETH_TXBUF_SIZE);
                        MODIFY_REG32(pstcEthHandle->stcTxDesc->u32ControlBufferSize, ETH_DMATXDESC_TBS1, (u32Size & ETH_DMATXDESC_TBS1));
                    }
                    else
                    {
                        /* Set frame size */
                        MODIFY_REG32(pstcEthHandle->stcTxDesc->u32ControlBufferSize, ETH_DMATXDESC_TBS1, (ETH_TXBUF_SIZE & ETH_DMATXDESC_TBS1));
                    }

                    /* Set Own bit of the Tx descriptor */
                    SET_REG32_BIT(pstcEthHandle->stcTxDesc->u32ControlStatus, ETH_DMATXDESC_OWN);
                    /* Pointer to next descriptor */
                    pstcEthHandle->stcTxDesc = (stc_eth_dma_desc_t *)(pstcEthHandle->stcTxDesc->u32Buffer2NextDescAddr);
                }
            }

            /* When Tx Buffer unavailable flag is set: clear it and resume transmission */
            if (0UL != (READ_REG32_BIT(M4_ETH->DMA_DMASTSR, ETH_DMA_FLAG_TUS)))
            {
                /* Clear DMA TUS flag */
                WRITE_REG32(M4_ETH->DMA_DMASTSR, ETH_DMA_FLAG_TUS);
                /* Resume DMA transmission */
                WRITE_REG32(M4_ETH->DMA_TXPOLLR, 0UL);
            }
        }
    }

    return enRet;
}

/**
 * @brief  Get DMA receive frame.
 * @param  [in] pstcEthHandle               Pointer to a @ref stc_eth_handle_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Get receive frame success
 *           - ErrorInvalidParameter: pstcEthHandle == NULL
 *           - Error: Not completed frame received
 */
en_result_t ETH_DMA_GetReceiveFrame(stc_eth_handle_t *pstcEthHandle)
{
    en_result_t enRet = Error;

    if (NULL == pstcEthHandle)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check if segment is not owned by DMA */
        if (0UL == (pstcEthHandle->stcRxDesc->u32ControlStatus & ETH_DMARXDESC_OWN))
        {
            /* Check if last segment */
            if (0UL != (pstcEthHandle->stcRxDesc->u32ControlStatus & ETH_DMARXDESC_RLS))
            {
                pstcEthHandle->stcRxFrame.u32SegCount++;
                pstcEthHandle->stcRxFrame.pstcLSDesc = pstcEthHandle->stcRxDesc;
                /* Check if last segment is first segment */
                if (1U == pstcEthHandle->stcRxFrame.u32SegCount)
                {
                    pstcEthHandle->stcRxFrame.pstcFSDesc = pstcEthHandle->stcRxDesc;
                }

                /* Get the Frame Length of the received packet: Strip FCS */
                pstcEthHandle->stcRxFrame.u32Length = ((pstcEthHandle->stcRxDesc->u32ControlStatus & ETH_DMARXDESC_FRAL) >> ETH_DMARXDESC_FRAME_LENGTHSHIFT) - 4U;
                /* Get the address of the buffer start address */
                pstcEthHandle->stcRxFrame.u32Buffer = (pstcEthHandle->stcRxFrame.pstcFSDesc)->u32Buffer1Addr;
                /* Pointer to next descriptor */
                pstcEthHandle->stcRxDesc              = (stc_eth_dma_desc_t*)(pstcEthHandle->stcRxDesc->u32Buffer2NextDescAddr);
                /* Get success */
                enRet = Ok;
            }
            /* Check if first segment */
            else if (0UL != (pstcEthHandle->stcRxDesc->u32ControlStatus & ETH_DMARXDESC_RFS))
            {
                pstcEthHandle->stcRxFrame.pstcFSDesc  = pstcEthHandle->stcRxDesc;
                pstcEthHandle->stcRxFrame.pstcLSDesc  = NULL;
                pstcEthHandle->stcRxFrame.u32SegCount = 1U;
                /* Point to next descriptor */
                pstcEthHandle->stcRxDesc = (stc_eth_dma_desc_t*)(pstcEthHandle->stcRxDesc->u32Buffer2NextDescAddr);
            }
            /* Check if intermediate segment */
            else
            {
                pstcEthHandle->stcRxFrame.u32SegCount++;
                /* Point to next descriptor */
                pstcEthHandle->stcRxDesc = (stc_eth_dma_desc_t*)(pstcEthHandle->stcRxDesc->u32Buffer2NextDescAddr);
            }
        }
    }

    return enRet;
}

/**
 * @brief  Get DMA receive frame in interrupt mode.
 * @param  [in] pstcEthHandle               Pointer to a @ref stc_eth_handle_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Get receive frame success
 *           - ErrorInvalidParameter: pstcEthHandle == NULL
 *           - Error: Not completed frame received
 */
en_result_t ETH_DMA_GetReceiveFrame_Interrupt(stc_eth_handle_t *pstcEthHandle)
{
    uint32_t u32DescCnt = 0U;
    en_result_t enRet = Error;

    if (NULL == pstcEthHandle)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Scan descriptor owned by CPU */
        while ((0UL == (pstcEthHandle->stcRxDesc->u32ControlStatus & ETH_DMARXDESC_OWN)) && (u32DescCnt < ETH_RXBUF_SIZE))
        {
            u32DescCnt++;
            /* Check if first segment in frame */
            if (ETH_DMARXDESC_RFS == (pstcEthHandle->stcRxDesc->u32ControlStatus & (ETH_DMARXDESC_RFS | ETH_DMARXDESC_RLS)))
            {
                pstcEthHandle->stcRxFrame.pstcFSDesc  = pstcEthHandle->stcRxDesc;
                pstcEthHandle->stcRxFrame.pstcLSDesc  = NULL;
                pstcEthHandle->stcRxFrame.u32SegCount = 1U;
                /* Point to next descriptor */
                pstcEthHandle->stcRxDesc = (stc_eth_dma_desc_t*)(pstcEthHandle->stcRxDesc->u32Buffer2NextDescAddr);
            }
            /* Check if intermediate segment */
            else if (0UL == (pstcEthHandle->stcRxDesc->u32ControlStatus & (ETH_DMARXDESC_RFS | ETH_DMARXDESC_RLS)))
            {
                pstcEthHandle->stcRxFrame.u32SegCount++;
                /* Point to next descriptor */
                pstcEthHandle->stcRxDesc = (stc_eth_dma_desc_t*)(pstcEthHandle->stcRxDesc->u32Buffer2NextDescAddr);
            }
            /* Last segment */
            else
            {
                pstcEthHandle->stcRxFrame.u32SegCount++;
                /* Last segment */
                pstcEthHandle->stcRxFrame.pstcLSDesc = pstcEthHandle->stcRxDesc;
                /* Check if last segment is first segment */
                if (1U == pstcEthHandle->stcRxFrame.u32SegCount)
                {
                    pstcEthHandle->stcRxFrame.pstcFSDesc = pstcEthHandle->stcRxDesc;
                }

                /* Get the Frame Length of the received packet: Strip FCS */
                pstcEthHandle->stcRxFrame.u32Length = ((pstcEthHandle->stcRxDesc->u32ControlStatus & ETH_DMARXDESC_FRAL) >> ETH_DMARXDESC_FRAME_LENGTHSHIFT) - 4U;
                /* Get the address of the buffer start address */
                pstcEthHandle->stcRxFrame.u32Buffer = (pstcEthHandle->stcRxFrame.pstcFSDesc)->u32Buffer1Addr;
                /* Pointer to next descriptor */
                pstcEthHandle->stcRxDesc = (stc_eth_dma_desc_t*)(pstcEthHandle->stcRxDesc->u32Buffer2NextDescAddr);
                /* Get success */
                enRet = Ok;
                break;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Set DMA Tx descriptor own bit.
 * @param  [in] pstcTxDesc                  Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32Owner                    DMA Tx descriptor owner
 *         This parameter can be one of the following values:
 *           @arg ETH_DMADESC_OWN_CPU:      Descriptor is owned by CPU
 *           @arg ETH_DMADESC_OWN_DMA:      Descriptor is owned by DMA
 * @retval An en_result_t enumeration value:
 *           - Ok: Set Tx descriptor own bit success
 *           - ErrorInvalidParameter: pstcTxDesc == NULL
 */
en_result_t ETH_DMA_SetTxDescOwn(stc_eth_dma_desc_t *pstcTxDesc, uint32_t u32Owner)
{
    en_result_t enRet = Ok;

    if (NULL == pstcTxDesc)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMADESC_OWN(u32Owner));

        if (ETH_DMADESC_OWN_CPU != u32Owner)
        {
            SET_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMATXDESC_OWN);
        }
        else
        {
            CLEAR_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMATXDESC_OWN);
        }
    }

    return enRet;
}

/**
 * @brief  Set DMA Tx descriptor buffer size.
 * @param  [in] pstcTxDesc                  Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u8BufferNum                 Buffer sequence number
 *         This parameter can be one of the following values:
 *           @arg ETH_DMADESC_BUFFER1:      DMA Tx Desc Buffer1
 *           @arg ETH_DMADESC_BUFFER2:      DMA Tx Desc Buffer2
 * @param  [in] u32BufferSize               DMA Tx buffer size
 * @retval An en_result_t enumeration value:
 *           - Ok: Set Tx descriptor buffer size success
 *           - ErrorInvalidParameter: pstcTxDesc == NULL
 */
en_result_t ETH_DMA_SetTxDescBufferSize(stc_eth_dma_desc_t *pstcTxDesc, uint8_t u8BufferNum, uint32_t u32BufferSize)
{
    en_result_t enRet = Ok;
    uint32_t u32ShiftBit = 0UL;

    if (NULL == pstcTxDesc)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMADESC_BUFFER(u8BufferNum));
        DDL_ASSERT(IS_ETH_DMATXDESC_BUFFER_SIZE(u32BufferSize));

        /* DMA Tx Desc buffer2 */
        if (ETH_DMADESC_BUFFER1 != u8BufferNum)
        {
            u32ShiftBit = ETH_DMADESC_BUFFER2_SIZESHIFT;
        }
        MODIFY_REG32(pstcTxDesc->u32ControlBufferSize, (ETH_DMATXDESC_TBS1 << u32ShiftBit),
                     (u32BufferSize << u32ShiftBit));
    }

    return enRet;
}

/**
 * @brief  Configure DMA Tx descriptor checksum insert.
 * @param  [in] pstcTxDesc                  Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32ChecksumMode             Checksum insert mode
 *         This parameter can be one of the following values:
 *           @arg ETH_DMATXDESC_CHECKSUM_BYPASS:                Checksum Engine is bypassed
 *           @arg ETH_DMATXDESC_CHECKSUM_IPV4HEADER:            IPv4 header checksum insertion
 *           @arg ETH_DMATXDESC_CHECKSUM_TCPUDPICMP_SEGMENT:    TCP/UDP/ICMP Checksum Insertion calculated over segment only
 *           @arg ETH_DMATXDESC_CHECKSUM_TCPUDPICMP_FULL:       TCP/UDP/ICMP Checksum Insertion fully calculated
 * @retval An en_result_t enumeration value:
 *           - Ok: Configure Tx descriptor checksum insert success
 *           - ErrorInvalidParameter: pstcTxDesc == NULL
 */
en_result_t ETH_DMA_TxDescChecksumInsertConfig(stc_eth_dma_desc_t *pstcTxDesc, uint32_t u32ChecksumMode)
{
    en_result_t enRet = Ok;

    if (NULL == pstcTxDesc)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMATXDESC_CHECKSUM_CONTROL(u32ChecksumMode));

        MODIFY_REG32(pstcTxDesc->u32ControlStatus, ETH_DMATXDESC_CIC, u32ChecksumMode);
    }

    return enRet;
}

/**
 * @brief  Configure DMA Tx descriptor VLAN insert.
 * @param  [in] pstcTxDesc                  Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32VlanMode                 VLAN insert mode
 *         This parameter can be one of the following values:
 *           @arg ETH_DMATXDESC_VLAN_BYPASS:            VLAN Insertion is bypassed
 *           @arg ETH_DMATXDESC_VLAN_REMOVE_TAG:        Remove Tag and Type fields in VLAN frame
 *           @arg ETH_DMATXDESC_VLAN_INSERT_TAG:        Insert VLAN Tag value in ETH_MAC_VTACTLR Register into transmit frame
 *           @arg ETH_DMATXDESC_VLAN_REPLACE_TAG:       Replace VLAN tag value in transmit frame with VLAN tag value in ETH_MAC_VTACTLR register
 * @retval An en_result_t enumeration value:
 *           - Ok: Configure Tx descriptor VLAN insert success
 *           - ErrorInvalidParameter: pstcTxDesc == NULL
 */
en_result_t ETH_DMA_TxDescVlanInsertConfig(stc_eth_dma_desc_t *pstcTxDesc, uint32_t u32VlanMode)
{
    en_result_t enRet = Ok;

    if (NULL == pstcTxDesc)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMATXDESC_VLAN_CONTROL(u32VlanMode));

        MODIFY_REG32(pstcTxDesc->u32ControlStatus, ETH_DMATXDESC_VLANC, u32VlanMode);
    }

    return enRet;
}

/**
 * @brief  Configure DMA Tx descriptor SA insert.
 * @param  [in] pstcTxDesc                  Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32SAMode                   SA insert mode
 *         This parameter can be one of the following values:
 *           @arg ETH_DMATXDESC_SA_BYPASS:              Source Address Insertion or Replace Control is bypassed
 *           @arg ETH_DMATXDESC_SA_INSTER_MACADDR0:     Insert address value in MAC address register 0 into transmit frame as SA address
 *           @arg ETH_DMATXDESC_SA_REPLACE_MACADDR0:    Replace SA address in transmit frame with address value in MAC address register 0
 *           @arg ETH_DMATXDESC_SA_INSTER_MACADDR1:     Insert address value in MAC address register 1 into transmit frame as SA address
 *           @arg ETH_DMATXDESC_SA_REPLACE_MACADDR1:    Replace SA address in transmit frame with address value in MAC address register 1
 * @retval An en_result_t enumeration value:
 *           - Ok: Configure Tx descriptor SA insert success
 *           - ErrorInvalidParameter: pstcTxDesc == NULL
 */
en_result_t ETH_DMA_TxDescSAInsertConfig(stc_eth_dma_desc_t *pstcTxDesc, uint32_t u32SAMode)
{
    en_result_t enRet = Ok;

    if (NULL == pstcTxDesc)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMATXDESC_SA_CONTROL(u32SAMode));

        MODIFY_REG32(pstcTxDesc->u32ControlBufferSize, ETH_DMATXDESC_SAIRC, u32SAMode);
    }

    return enRet;
}

/**
 * @brief  Enable or disable DMA Tx descriptor add CRC.
 * @param  [in] pstcTxDesc                  Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval An en_result_t enumeration value:
 *           - Ok: Configure Tx add CRC success
 *           - ErrorInvalidParameter: pstcTxDesc == NULL
 */
en_result_t ETH_DMA_TxDescCRCCmd(stc_eth_dma_desc_t *pstcTxDesc, en_functional_state_t enNewSta)
{
    en_result_t enRet = Ok;

    if (NULL == pstcTxDesc)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

        if (Disable != enNewSta)
        {
            CLEAR_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMATXDESC_DCRC);
        }
        else
        {
            SET_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMATXDESC_DCRC);
        }
    }

    return enRet;
}

/**
 * @brief  Enable or disable DMA Tx descriptor padding.
 * @param  [in] pstcTxDesc                  Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval An en_result_t enumeration value:
 *           - Ok: Configure Tx padding success
 *           - ErrorInvalidParameter: pstcTxDesc == NULL
 */
en_result_t ETH_DMA_TxDescPADCmd(stc_eth_dma_desc_t *pstcTxDesc, en_functional_state_t enNewSta)
{
    en_result_t enRet = Ok;

    if (NULL == pstcTxDesc)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

        if (Disable != enNewSta)
        {
            CLEAR_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMATXDESC_DPAD);
        }
        else
        {
            SET_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMATXDESC_DPAD);
        }
    }

    return enRet;
}

/**
 * @brief  Enable or disable DMA Tx descriptor timestamp.
 * @param  [in] pstcTxDesc                  Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval An en_result_t enumeration value:
 *           - Ok: Configure Tx padding success
 *           - ErrorInvalidParameter: pstcTxDesc == NULL
 */
en_result_t ETH_DMA_TxDescTimestamp(stc_eth_dma_desc_t *pstcTxDesc, en_functional_state_t enNewSta)
{
    en_result_t enRet = Ok;

    if (NULL == pstcTxDesc)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

        if (Disable != enNewSta)
        {
            SET_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMATXDESC_TTSE);
        }
        else
        {
            CLEAR_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMATXDESC_TTSE);
        }
    }

    return enRet;
}

/**
 * @brief  Enable or disable DMA Tx descriptor replace CRC.
 * @param  [in] pstcTxDesc                  Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval An en_result_t enumeration value:
 *           - Ok: Configure Tx replace CRC success
 *           - ErrorInvalidParameter: pstcTxDesc == NULL
 */
en_result_t ETH_DMA_TxDescReplaceCRCCmd(stc_eth_dma_desc_t *pstcTxDesc, en_functional_state_t enNewSta)
{
    en_result_t enRet = Ok;

    if (NULL == pstcTxDesc)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

        if (Disable != enNewSta)
        {
            SET_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMATXDESC_CRCR);
        }
        else
        {
            CLEAR_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMATXDESC_CRCR);
        }
    }

    return enRet;
}

/**
 * @brief  Enable or disable DMA Tx finished interrupt.
 * @param  [in] pstcTxDesc                  Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval An en_result_t enumeration value:
 *           - Ok: Configure Tx interrupt configure success
 *           - ErrorInvalidParameter: pstcTxDesc == NULL
 */
en_result_t ETH_DMA_TxDescIntCmd(stc_eth_dma_desc_t *pstcTxDesc, en_functional_state_t enNewSta)
{
    en_result_t enRet = Ok;

    if (NULL == pstcTxDesc)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

        if (Disable != enNewSta)
        {
            SET_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMATXDESC_IOC);
        }
        else
        {
            CLEAR_REG32_BIT(pstcTxDesc->u32ControlStatus, ETH_DMATXDESC_IOC);
        }
    }

    return enRet;
}

/**
 * @brief  Get DMA Tx descriptor flag status.
 * @param  [in] pstcTxDesc                  Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32Flag                     DMA Tx descriptor flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_DMATXDESC_OWN:        OWN bit
 *           @arg ETH_DMATXDESC_IOC:        Interrupt on Completion
 *           @arg ETH_DMATXDESC_TLS:        Transmit Last Segment
 *           @arg ETH_DMATXDESC_TFS:        Transmit First Segment
 *           @arg ETH_DMATXDESC_DCRC:       Disable CRC
 *           @arg ETH_DMATXDESC_DPAD:       Disable Padding
 *           @arg ETH_DMATXDESC_TTSE:       Transmit Time Stamp Enable
 *           @arg ETH_DMATXDESC_CRCR:       CRC Replace Control
 *           @arg ETH_DMATXDESC_TER:        Transmit End of Ring
 *           @arg ETH_DMATXDESC_TSAC:       Second Address Chained
 *           @arg ETH_DMATXDESC_TTSS:       Tx Time Stamp Status
 *           @arg ETH_DMATXDESC_IHE:        IP Header Error
 *           @arg ETH_DMATXDESC_ETSUM:      Tx Error summary
 *           @arg ETH_DMATXDESC_JTE:        Jabber Timeout Error
 *           @arg ETH_DMATXDESC_FFF:        Frame Flushed
 *           @arg ETH_DMATXDESC_TPCE:       Payload Checksum Error
 *           @arg ETH_DMATXDESC_LOCE:       Loss Carrier Error
 *           @arg ETH_DMATXDESC_NCE:        No Carrier Error
 *           @arg ETH_DMATXDESC_TLCE:       Late Collision Error
 *           @arg ETH_DMATXDESC_ECE:        Excessive Collision Error
 *           @arg ETH_DMATXDESC_VLF:        VLAN Frame
 *           @arg ETH_DMATXDESC_EDE:        Excessive Deferral Error
 *           @arg ETH_DMATXDESC_UDE:        Underflow Error
 *           @arg ETH_DMATXDESC_DEE:        Deferred Error
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t ETH_DMA_GetTxDescStatus(const stc_eth_dma_desc_t *pstcTxDesc, uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_DMATXDESC_STATUS(u32Flag));

    if (NULL != pstcTxDesc)
    {
        if (0UL != (pstcTxDesc->u32ControlStatus & u32Flag))
        {
            enFlagSta = Set;
        }
    }

    return enFlagSta;
}

/**
 * @brief  Get DMA Tx descriptor collision count
 * @param  [in] pstcTxDesc                  Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [out] pu32ColliCnt               Pointer to DMA Tx collision count
 * @retval An en_result_t enumeration value:
 *           - Ok: Get collision count success
 *           - ErrorInvalidParameter: pstcTxDesc == NULL or pu32ColliCnt == NULL
 */
en_result_t ETH_DMA_GetTxDescCollisionCnt(const stc_eth_dma_desc_t *pstcTxDesc, uint32_t *pu32ColliCnt)
{
    en_result_t enRet = Ok;

    if ((NULL == pstcTxDesc) || (NULL == pu32ColliCnt))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        *pu32ColliCnt = (pstcTxDesc->u32ControlStatus >> ETH_DMATXDESC_COLLISION_COUNTSHIFT) & ((uint32_t)0x0000000FUL);
    }

    return enRet;
}

/**
 * @brief  Get DMA Tx descriptor timestamp.
 * @param  [in] pstcTxDesc                  Pointer to a DMA Tx descriptor @ref stc_eth_dma_desc_t
 * @param  [out] pu32High                   Timestamp high bit time
 * @param  [out] pu32Low                    Timestamp low bit time
 * @retval An en_result_t enumeration value:
 *           - Ok: Get timestamp success
 *           - ErrorInvalidParameter: pstcTxDesc == NULL or pu32High == NULL or pu32Low == NULL
 */
en_result_t ETH_DMA_GetTxDescTimeStamp(const stc_eth_dma_desc_t *pstcTxDesc, uint32_t *pu32High, uint32_t *pu32Low)
{
    en_result_t enRet = Ok;

    if ((NULL == pstcTxDesc) || (NULL == pu32High) || (NULL == pu32Low))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        *pu32Low  = pstcTxDesc->u32TimeStampLow;
        *pu32High = pstcTxDesc->u32TimeStampHigh;
    }

    return enRet;
}

/**
 * @brief  Set DMA Rx descriptor own bit.
 * @param  [in] pstcRxDesc                  Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32Owner                    DMA Rx descriptor owner
 *         This parameter can be one of the following values:
 *           @arg ETH_DMADESC_OWN_CPU:      Descriptor is owned by CPU
 *           @arg ETH_DMADESC_OWN_DMA:      Descriptor is owned by DMA
 * @retval An en_result_t enumeration value:
 *           - Ok: Set Rx descriptor own bit success
 *           - ErrorInvalidParameter: pstcRxDesc == NULL
 */
en_result_t ETH_DMA_SetRxDescOwn(stc_eth_dma_desc_t *pstcRxDesc, uint32_t u32Owner)
{
    en_result_t enRet = Ok;

    if (NULL == pstcRxDesc)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMADESC_OWN(u32Owner));

        if (ETH_DMADESC_OWN_CPU != u32Owner)
        {
            SET_REG32_BIT(pstcRxDesc->u32ControlStatus, ETH_DMARXDESC_OWN);
        }
        else
        {
            CLEAR_REG32_BIT(pstcRxDesc->u32ControlStatus, ETH_DMARXDESC_OWN);
        }
    }

    return enRet;
}

/**
 * @brief  Enable or disable DMA Rx finished interrupt.
 * @param  [in] pstcRxDesc                  Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval An en_result_t enumeration value:
 *           - Ok: Rx interrupt configure success
 *           - ErrorInvalidParameter: pstcRxDesc == NULL
 */
en_result_t ETH_DMA_RxDescIntCmd(stc_eth_dma_desc_t *pstcRxDesc, en_functional_state_t enNewSta)
{
    en_result_t enRet = Ok;

    if (NULL == pstcRxDesc)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

        if (Disable != enNewSta)
        {
            CLEAR_REG32_BIT(pstcRxDesc->u32ControlBufferSize, ETH_DMARXDESC_DIC);
        }
        else
        {
            SET_REG32_BIT(pstcRxDesc->u32ControlBufferSize, ETH_DMARXDESC_DIC);
        }
    }

    return enRet;
}

/**
 * @brief  Get DMA Rx descriptor flag status.
 * @param  [in] pstcRxDesc                  Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32Flag                     DMA Rx descriptor flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_DMARXDESC_OWN:              OWN bit
 *           @arg ETH_DMARXDESC_DAF:              DA Filter Fail for the received frame
 *           @arg ETH_DMARXDESC_ERSUM:            Rx Error summary
 *           @arg ETH_DMARXDESC_DPE:              Descriptor Error
 *           @arg ETH_DMARXDESC_SAF:              SA Filter Fail for the received frame
 *           @arg ETH_DMARXDESC_LEE:              Length Error
 *           @arg ETH_DMARXDESC_OVE:              Overflow Error
 *           @arg ETH_DMARXDESC_VLAT              VLAN Tag
 *           @arg ETH_DMARXDESC_RFS:              First descriptor
 *           @arg ETH_DMARXDESC_RLS:              Last descriptor
 *           @arg ETH_DMARXDESC_IPE_TSPA_GF:      COE Error or Time stamp valid or jumbo frame
 *           @arg ETH_DMARXDESC_RLCE:             Late collision Error
 *           @arg ETH_DMARXDESC_FRAT:             Frame type
 *           @arg ETH_DMARXDESC_WTE:              Receive Watchdog Timeout
 *           @arg ETH_DMARXDESC_REE:              Receive error
 *           @arg ETH_DMARXDESC_DBE:              Dribble bit error
 *           @arg ETH_DMARXDESC_CRE:              CRC error
 *           @arg ETH_DMARXDESC_DAS_ESA:          MAC Address Filter/Status bit extension
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t ETH_DMA_GetRxDescStatus(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_DMARXDESC_STATUS(u32Flag));

    if (NULL != pstcRxDesc)
    {
        if (0UL != (pstcRxDesc->u32ControlStatus & u32Flag))
        {
            enFlagSta = Set;
        }
    }

    return enFlagSta;
}

/**
 * @brief  Get DMA Rx descriptor extend flag status.
 * @param  [in] pstcRxDesc                  Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u32Flag                     DMA Rx descriptor extend flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_DMARXDESC_L4FMS:      L4 Port Filter Status
 *           @arg ETH_DMARXDESC_L3FMS:      L3 Address Filter Status
 *           @arg ETH_DMARXDESC_TSPD:       Discard Time Stamp
 *           @arg ETH_DMARXDESC_PTPV:       PTP Version
 *           @arg ETH_DMARXDESC_PTPFT:      PTP Frame Type
 *           @arg ETH_DMARXDESC_IPV6DR:     IPv6 Packet Received
 *           @arg ETH_DMARXDESC_IPV4DR:     IPv4 Packet Received
 *           @arg ETH_DMARXDESC_IPCB:       COE engine Bypassed
 *           @arg ETH_DMARXDESC_IPPE:       IP Payload Error
 *           @arg ETH_DMARXDESC_IPHE:       IP Header Error
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t ETH_DMA_GetRxDescExtendStatus(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_DMARXDESC_EXTEND_STATUS(u32Flag));

    if (NULL != pstcRxDesc)
    {
        if (0UL != (pstcRxDesc->u32ExtendStatus & u32Flag))
        {
            enFlagSta = Set;
        }
    }

    return enFlagSta;
}

/**
 * @brief  Get DMA Rx descriptor payload type.
 * @param  [in] pstcRxDesc                  Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [out] pu32PayloadType            Pointer to DMA Rx payload type
 *           The payload type may be one of the following values:
 *           - ETH_DMARXDESC_IPPT_UNKNOWN:  Unknown
 *           - ETH_DMARXDESC_IPPT_UDP:      UDP
 *           - ETH_DMARXDESC_IPPT_TCP:      TCP
 *           - ETH_DMARXDESC_IPPT_ICMP:     ICMP
 * @retval An en_result_t enumeration value:
 *           - Ok: Get payload type success
 *           - ErrorInvalidParameter: pstcRxDesc == NULL or pu32PayloadType == NULL
 */
en_result_t ETH_DMA_GetRxDescPayloadType(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t *pu32PayloadType)
{
    en_result_t enRet = Ok;

    if ((NULL == pstcRxDesc) || (NULL == pu32PayloadType))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        *pu32PayloadType = pstcRxDesc->u32ExtendStatus & ETH_DMARXDESC_IPPT;
    }

    return enRet;
}

/**
 * @brief  Get DMA Rx descriptor datagram type.
 * @param  [in] pstcRxDesc                  Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [out] pu32DatagramType           Pointer to DMA Rx datagram type
 *           The payload type may be one of the following values:
 *           - ETH_DMARXDESC_MTP_NONE:                  No PTP messages
 *           - ETH_DMARXDESC_MTP_SYNC:                  SYNC message (all clock types)
 *           - ETH_DMARXDESC_MTP_FOLLOWUP:              Follow_Up message (all clock types)
 *           - ETH_DMARXDESC_MTP_DELAYREQ:              Delay_Req message (all clock types)
 *           - ETH_DMARXDESC_MTP_DELAYRESP:             Delay_Resp message (all clock types)
 *           - ETH_DMARXDESC_MTP_PDELAYREQ:             Pdelay_Req message (peer-to-peer transparent clock)
 *           - ETH_DMARXDESC_MTP_PDELAYRESP:            Pdelay_Resp message (peer-to-peer transparent clock)
 *           - ETH_DMARXDESC_MTP_PDELAYRESP_FOLLOWUP:   Pdelay_Resp_Follow_Up message (peer-to-peer transparent clock)
 *           - ETH_DMARXDESC_MTP_ANNOUNCE:              Announce message (Ordinary or Boundary clock)
 *           - ETH_DMARXDESC_MTP_MANAGEMENT:            Management message (Ordinary or Boundary clock)
 *           - ETH_DMARXDESC_MTP_SIGNALING:             Signaling message (Ordinary or Boundary clock)
 *           - ETH_DMARXDESC_MTP_DEFAULT:               Default Datagram Type
 * @retval An en_result_t enumeration value:
 *           - Ok: Get datagram type success
 *           - ErrorInvalidParameter: pstcRxDesc == NULL or pu32DatagramType == NULL
 */
en_result_t ETH_DMA_GetRxDescDatagramType(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t *pu32DatagramType)
{
    en_result_t enRet = Ok;

    if ((NULL == pstcRxDesc) || (NULL == pu32DatagramType))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        *pu32DatagramType = pstcRxDesc->u32ExtendStatus & ETH_DMARXDESC_MTP;
    }

    return enRet;
}

/**
 * @brief  Get DMA Rx descriptor frame length.
 * @param  [in] pstcRxDesc                  Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [out] pu32FrameLength            Pointer to DMA Rx frame length
 * @retval An en_result_t enumeration value:
 *           - Ok: Get frame length success
 *           - ErrorInvalidParameter: pstcRxDesc == NULL or pu32FrameLength == NULL
 */
en_result_t ETH_DMA_GetRxDescFrameLength(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t *pu32FrameLength)
{
    en_result_t enRet = Ok;

    if ((NULL == pstcRxDesc) || (NULL == pu32FrameLength))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        *pu32FrameLength = (pstcRxDesc->u32ControlStatus >> ETH_DMARXDESC_FRAME_LENGTHSHIFT) & ((uint32_t)0x00003FFFUL);
    }

    return enRet;
}

/**
 * @brief  Get DMA Rx descriptor buffer size.
 * @param  [in] pstcRxDesc                  Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [in] u8BufferNum                 Buffer sequence number
 *         This parameter can be one of the following values:
 *           @arg ETH_DMADESC_BUFFER1:      DMA Rx Desc Buffer1
 *           @arg ETH_DMADESC_BUFFER2:      DMA Rx Desc Buffer2
 * @param  [out] pu32BufferSize             Pointer to DMA Rx buffer size
 * @retval An en_result_t enumeration value:
 *           - Ok: Get buffer size success
 *           - ErrorInvalidParameter: pstcRxDesc == NULL or pu32BufferSize == NULL
 */
en_result_t ETH_DMA_GetRxDescBufferSize(const stc_eth_dma_desc_t *pstcRxDesc, uint8_t u8BufferNum, uint32_t *pu32BufferSize)
{
    en_result_t enRet = Ok;
    uint32_t u32ShiftBit = 0UL;

    if ((NULL == pstcRxDesc) || (NULL == pu32BufferSize))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_DMADESC_BUFFER(u8BufferNum));

        /* DMA Rx Desc buffer2 */
        if (ETH_DMADESC_BUFFER1 != u8BufferNum)
        {
            u32ShiftBit = ETH_DMADESC_BUFFER2_SIZESHIFT;
        }
        *pu32BufferSize = (pstcRxDesc->u32ControlBufferSize >> u32ShiftBit) & ((uint32_t)0x00001FFFUL);
    }

    return enRet;
}

/**
 * @brief  Get DMA Rx descriptor timestamp.
 * @param  [in] pstcRxDesc                  Pointer to a DMA Rx descriptor @ref stc_eth_dma_desc_t
 * @param  [out] pu32High                   Timestamp high bit time
 * @param  [out] pu32Low                    Timestamp low bit time
 * @retval An en_result_t enumeration value:
 *           - Ok: Get timestamp success
 *           - ErrorInvalidParameter: pstcRxDesc == NULL or pu32High == NULL or pu32Low == NULL
 */
en_result_t ETH_DMA_GetRxDescTimeStamp(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t *pu32High, uint32_t *pu32Low)
{
    en_result_t enRet = Ok;

    if ((NULL == pstcRxDesc) || (NULL == pu32High) || (NULL == pu32Low))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        *pu32Low  = pstcRxDesc->u32TimeStampLow;
        *pu32High = pstcRxDesc->u32TimeStampHigh;
    }

    return enRet;
}

/******************************************************************************/
/*                                PMT Functions                               */
/******************************************************************************/
/**
 * @brief  Reset PMT wakeup frame pointer.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Reset pointer success
 *           - ErrorTimeout: Reset timeout
 */
en_result_t ETH_PMT_ResetWakeupFramePointer(void)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Ok;

    WRITE_REG32(bM4_ETH->MAC_PMTCTLR_b.RTWKFR, 1U);
    u32Count = ETH_TIMEOUT_WRITE_REGISTER * (HCLK_VALUE / 20000UL);
    while (0UL != READ_REG32(bM4_ETH->MAC_PMTCTLR_b.RTWKFR))
    {
        if (0UL == u32Count)
        {
            enRet = ErrorTimeout;
            break;
        }
        u32Count--;
    }

    return enRet;
}
/**
 * @brief  Write PMT wakeup frame register.
 * @param  [in] au32RegBuffer                Pointer to wakeup frame filter register buffer(8 words).
 * @retval An en_result_t enumeration value:
 *           - Ok: Write register success
 *           - ErrorInvalidParameter: au32RegBuffer == NULL
 */
en_result_t ETH_PMT_WriteWakeupFrameRegister(const uint32_t au32RegBuffer[])
{
    uint32_t i;
    en_result_t enRet = Ok;

    if (NULL == au32RegBuffer)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        for (i=0U; i<ETH_WAKEUP_REGISTER_LENGTH; i++)
        {
            WRITE_REG32(M4_ETH->MAC_RTWKFFR, au32RegBuffer[i]);
        }
    }

    return enRet;
}

/**
 * @brief  Enable or disable PMT forward wakeup frame.
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_PMT_ForwardWakeupFrameCmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_ETH->MAC_PMTCTLR_b.RTWKTR, enNewSta);
}

/**
 * @brief  Enable or disable PMT wakeup source.
 * @param  [in] u32WakeupSrc              Wakeup source
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_PMT_WAKEUP_GLOBAL_UNICAST:    Global unicast
 *           @arg ETH_PMT_WAKEUP_WAKEUP_FRAME:      Wake-Up Frame
 *           @arg ETH_PMT_WAKEUP_MAGIC_PACKET:      Magic Packet
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_PMT_WakeupSourceCmd(uint32_t u32WakeupSrc, en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    if (Disable != enNewSta)
    {
        SET_REG32_BIT(M4_ETH->MAC_PMTCTLR, u32WakeupSrc);
    }
    else
    {
        CLEAR_REG32_BIT(M4_ETH->MAC_PMTCTLR, u32WakeupSrc);
    }
}

/**
 * @brief  Enable or disable PMT powerdown mode.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Set powerdown mode success
 *           - Error: Set powerdown mode failed
 */
en_result_t ETH_PMT_EnterPowerDown(void)
{
    en_result_t enRet = Error;

    if (0UL != READ_REG32(bM4_ETH->MAC_PMTCTLR_b.MPEN))
    {
        if (0UL != READ_REG32(bM4_ETH->MAC_PMTCTLR_b.WKEN))
        {
            WRITE_REG32(bM4_ETH->MAC_PMTCTLR_b.PWDN, Enable);
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Get PMT flag status.
 * @param  [in] u32Flag                     PMT flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_PMT_FLAG_RTWKFR:      Wake-Up Frame Filter Register Pointer Reset
 *           @arg ETH_PMT_FLAG_WKFR:        Wake-Up Frame Received
 *           @arg ETH_PMT_FLAG_MPFR:        Magic Packet Received
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t ETH_PMT_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_PMT_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(M4_ETH->MAC_PMTCTLR, u32Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/******************************************************************************/
/*                                MMC Functions                               */
/******************************************************************************/
/**
 * @brief  De-Initialize MMC.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: MMC De-Initialize success
*           - ErrorTimeout: De-Initialize timeout
 */
en_result_t ETH_MMC_DeInit(void)
{
    WRITE_REG32(M4_ETH->MMC_MMCCTLR, 0UL);
    WRITE_REG32(M4_ETH->MMC_RITCTLR, 0UL);
    WRITE_REG32(M4_ETH->MMC_TITCTLR, 0UL);

    return ETH_MMC_CounterReset();
}

/**
 * @brief  Initialize MMC.
 * @param  [in] pstcMmcInit                 Pointer to a @ref stc_eth_mmc_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: MMC Initialize success
 *           - ErrorInvalidParameter: pstcMmcInit == NULL
 */
en_result_t ETH_MMC_Init(const stc_eth_mmc_init_t *pstcMmcInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcMmcInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_MMC_COUNTER_PRESETMODE(pstcMmcInit->u32PresetMode));
        DDL_ASSERT(IS_ETH_MMC_READ_RESET(pstcMmcInit->u32ReadReset));
        DDL_ASSERT(IS_ETH_MMC_COUNTER_RELOAD(pstcMmcInit->u32ReloadMode));

        MODIFY_REG32(M4_ETH->MMC_MMCCTLR,
                     (ETH_MMC_MMCCTLR_MCPSEL | ETH_MMC_MMCCTLR_MCPSET |
                      ETH_MMC_MMCCTLR_ROR    | ETH_MMC_MMCCTLR_COS),
                     (pstcMmcInit->u32PresetMode | pstcMmcInit->u32ReadReset |
                      pstcMmcInit->u32ReloadMode));
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_eth_mmc_init_t to default values.
 * @param  [out] pstcMmcInit                Pointer to a @ref stc_eth_mmc_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Structure Initialize success
 *           - ErrorInvalidParameter: pstcMmcInit == NULL
 */
en_result_t ETH_MMC_StructInit(stc_eth_mmc_init_t *pstcMmcInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcMmcInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcMmcInit->u32PresetMode = ETH_MMC_COUNTER_PRESETMODE_DISABLE;
        pstcMmcInit->u32ReadReset  = ETH_MMC_READ_RESET_ENABLE;
        pstcMmcInit->u32ReloadMode = ETH_MMC_COUNTER_RELOAD_ENABLE;
    }

    return enRet;
}

/**
 * @brief  MMC all counter software reset.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Reset success
 *           - ErrorTimeout: Reset timeout
 */
en_result_t ETH_MMC_CounterReset(void)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Ok;

    WRITE_REG32(bM4_ETH->MMC_MMCCTLR_b.CRST, 1U);
    u32Count = ETH_TIMEOUT_WRITE_REGISTER * (HCLK_VALUE / 20000UL);
    while (0UL != READ_REG32(bM4_ETH->MMC_MMCCTLR_b.CRST))
    {
        if (0UL == u32Count)
        {
            enRet = ErrorTimeout;
            break;
        }
        u32Count--;
    }

    return enRet;
}

/**
 * @brief  Enable or disable the reset of all MMC counter after reading.
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_MMC_ResetAfterReadCmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_ETH->MMC_MMCCTLR_b.ROR, enNewSta);
}

/**
 * @brief  Enable or disable MMC function.
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_MMC_Cmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    if (Disable != enNewSta)
    {
        WRITE_REG32(bM4_ETH->MMC_MMCCTLR_b.MCF, Disable);
    }
    else
    {
        WRITE_REG32(bM4_ETH->MMC_MMCCTLR_b.MCF, Enable);
    }
}

/**
 * @brief  Enable or disable MMC transmit interrupt.
 * @param  [in] u32IntSrc                   MMC interrupt source
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MMC_INT_TXEDEIM:      Tx excessive deferral error frame interrupt
 *           @arg ETH_MMC_INT_TXUGIM:       Tx unicast good frame interrupt
 *           @arg ETH_MMC_INT_TXCAEIM:      Tx carrier error frame interrupt
 *           @arg ETH_MMC_INT_TXECEIM:      Tx excessive collision error frame interrupt
 *           @arg ETH_MMC_INT_TXLCEIM:      Tx deferral collision error frame interrupt
 *           @arg ETH_MMC_INT_TXDEEIM:      Tx deferral error frame interrupt
 *           @arg ETH_MMC_INT_TXMGIM:       Tx multicast good frame interrupt
 *           @arg ETH_MMC_INT_TXBGIM:       Tx broadcast good frame interrupt
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_MMC_TxIntCmd(uint32_t u32IntSrc, en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_MMC_TX_INTERRUPT(u32IntSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    if (Disable != enNewSta)
    {
        CLEAR_REG32_BIT(M4_ETH->MMC_TITCTLR, u32IntSrc);
    }
    else
    {
        SET_REG32_BIT(M4_ETH->MMC_TITCTLR, u32IntSrc);
    }
}

/**
 * @brief  Enable or disable MMC receive interrupt.
 * @param  [in] u32IntSrc                   MMC interrupt source
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MMC_INT_RXOEIM:       Rx out of scope error frame interrupt
 *           @arg ETH_MMC_INT_RXLEIM:       Rx length error frame interrupt
 *           @arg ETH_MMC_INT_RXUGIM:       Rx unicast good frame interrupt
 *           @arg ETH_MMC_INT_RXREIM:       Rx short error frame interrupt
 *           @arg ETH_MMC_INT_RXAEIM:       Rx alignment error frame interrupt
 *           @arg ETH_MMC_INT_RXCEIM:       Rx crc error frame interrupt
 *           @arg ETH_MMC_INT_RXMGIM:       Rx multicast good frame interrupt
 *           @arg ETH_MMC_INT_RXBGIM:       Rx broadcast good frame interrupt
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_MMC_RxIntCmd(uint32_t u32IntSrc, en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_MMC_RX_INTERRUPT(u32IntSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    if (Disable != enNewSta)
    {
        CLEAR_REG32_BIT(M4_ETH->MMC_RITCTLR, u32IntSrc);
    }
    else
    {
        SET_REG32_BIT(M4_ETH->MMC_RITCTLR, u32IntSrc);
    }
}

/**
 * @brief  Get MMC flag transmit status.
 * @param  [in] u32Flag                     MMC flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MMC_FLAG_TXEDEIS:     Tx excessive deferral error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_TXUGIS:      Tx unicast good frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_TXCAEIS:     Tx carrier error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_TXECEIS:     Tx excessive collision error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_TXLCEIS:     Tx deferral collision error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_TXDEEIS:     Tx deferral error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_TXMGIS:      Tx multicast good frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_TXBGIS:      Tx broadcast good frame counter reaches half or all the maximum value
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t ETH_MMC_GetTxStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_MMC_TX_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(M4_ETH->MMC_TRSSTSR, u32Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/**
 * @brief  Get MMC receive flag status.
 * @param  [in] u32Flag                     MMC flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_MMC_FLAG_RXOEIS:      Rx out of scope error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_RXLEIS:      Rx length error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_RXUGIS:      Rx unicast good frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_RXREIS:      Rx short error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_RXAEIS:      Rx alignment error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_RXCEIS:      Rx crc error frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_RXMGIS:      Rx multicast good frame counter reaches half or all the maximum value
 *           @arg ETH_MMC_FLAG_RXBGIS:      Rx broadcast good frame counter reaches half or all the maximum value
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t ETH_MMC_GetRxStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_MMC_RX_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(M4_ETH->MMC_REVSTSR, u32Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/**
 * @brief  Get MMC register.
 * @param  [in] u32Reg                      MMC statistics register
 *         This parameter can be one of the following values:
 *           @arg ETH_MMC_REG_TXBRGFR:      Tx broadcast good frame Statistical Register
 *           @arg ETH_MMC_REG_TXMUGFR:      Tx multicast good frame Statistical Register
 *           @arg ETH_MMC_REG_TXDEEFR:      Tx deferral error frame Statistical Register
 *           @arg ETH_MMC_REG_TXLCEFR:      Tx deferral collision error frame Statistical Register
 *           @arg ETH_MMC_REG_TXECEFR:      Tx excessive collision error frame Statistical Register
 *           @arg ETH_MMC_REG_TXCAEFR:      Tx carrier error frame Statistical Register
 *           @arg ETH_MMC_REG_TXUNGFR:      Tx unicast good frame Statistical Register
 *           @arg ETH_MMC_REG_TXEDEFR:      Tx excessive deferral error frame Statistical Register
 *           @arg ETH_MMC_REG_RXBRGFR:      Rx broadcast good frame Statistical Register
 *           @arg ETH_MMC_REG_RXMUGFR:      Rx multicast good frame Statistical Register
 *           @arg ETH_MMC_REG_RXCREFR:      Rx crc error frame Statistical Register
 *           @arg ETH_MMC_REG_RXALEFR:      Rx alignment error frame Statistical Register
 *           @arg ETH_MMC_REG_RXRUEFR:      Rx short error frame Statistical Register
 *           @arg ETH_MMC_REG_RXUNGFR:      Rx unicast good frame Statistical Register
 *           @arg ETH_MMC_REG_RXLEEFR:      Rx length error frame Statistical Register
 *           @arg ETH_MMC_REG_RXOREFR:      Rx out of scope error frame Statistical Register
 * @retval uint32_t                         MMC statistics Register value
 */
uint32_t ETH_MMC_GetRegister(uint32_t u32Reg)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_MMC_REG(u32Reg));

    return (*(__IO uint32_t *)((uint32_t)(&M4_ETH->MAC_CONFIGR) + u32Reg));
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
    WRITE_REG32(M4_ETH->PTP_TSPCTLR, 0x00002000UL);
    WRITE_REG32(M4_ETH->PTP_TSPADDR, 0UL);
    WRITE_REG32(M4_ETH->PTP_TSPNSAR, 0UL);
    WRITE_REG32(M4_ETH->PTP_TMUSECR, 0UL);
    WRITE_REG32(M4_ETH->PTP_TMUNSER, 0UL);
}

/**
 * @brief  Initialize PTP.
 * @param  [in] pstcPtpInit                 Pointer to a @ref stc_eth_ptp_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: PTP Initialize success
 *           - Error: PTP Initialize failed
 *           - ErrorInvalidParameter: pstcPtpInit == NULL
 */
en_result_t ETH_PTP_Init(const stc_eth_ptp_init_t *pstcPtpInit)
{
    en_result_t enRet;

    if (NULL == pstcPtpInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_PTP_FRAME_DA_FILTER(pstcPtpInit->u32DAFilter));
        DDL_ASSERT(IS_ETH_PTP_DATAGRAM_VERSION(pstcPtpInit->u32DatagramVersion));
        DDL_ASSERT(IS_ETH_PTP_SUBSECOND_SCALE(pstcPtpInit->u32SubSecScale));
        DDL_ASSERT(IS_ETH_PTP_DATAGRAM_TYPE(pstcPtpInit->u32SnapDatagramType));
        DDL_ASSERT(IS_ETH_PTP_FRAME_TYPE(pstcPtpInit->u32SnapFrameType));
        DDL_ASSERT(IS_ETH_PTP_CALIBRATION_MODE(pstcPtpInit->u32CalibMode));
        DDL_ASSERT(IS_ETH_PTP_SUB_SECOND(pstcPtpInit->u32InitValueSubSec));

        /* Set increase value registers */
        WRITE_REG32(M4_ETH->PTP_TSPNSAR, pstcPtpInit->u8IncValueSubSec);
        WRITE_REG32(M4_ETH->PTP_TSPADDR, pstcPtpInit->u32IncValueBasic);
        enRet = ETH_PTP_UpdateBasicIncValue();
        if (Ok == enRet)
        {
            /* Set timestamp control register */
            MODIFY_REG32(M4_ETH->PTP_TSPCTLR, ETH_PTP_TSPCTLR_CLEAR_MASK,
                         (pstcPtpInit->u32DAFilter        | pstcPtpInit->u32SnapDatagramType | pstcPtpInit->u32SnapFrameType |
                          pstcPtpInit->u32DatagramVersion | pstcPtpInit->u32SubSecScale      | pstcPtpInit->u32CalibMode));
            /* Set initialize value */
            WRITE_REG32(M4_ETH->PTP_TMUSECR, pstcPtpInit->u32InitValueSec);
            WRITE_REG32(M4_ETH->PTP_TMUNSER, pstcPtpInit->u32InitValueSubSec);
            enRet = ETH_PTP_SystemTimeInit();
            if (Ok != enRet)
            {
                enRet = Error;
            }
        }
        else
        {
            enRet = Error;
        }
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_eth_ptp_init_t to default values.
 * @param  [out] pstcPtpInit                Pointer to a @ref stc_eth_ptp_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Structure Initialize success
 *           - ErrorInvalidParameter: pstcPtpInit == NULL
 */
en_result_t ETH_PTP_StructInit(stc_eth_ptp_init_t *pstcPtpInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcPtpInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcPtpInit->u32DAFilter         = ETH_PTP_FRAME_DA_FILTER_DISABLE;
        pstcPtpInit->u32SnapDatagramType = ETH_PTP_DATAGRAM_TYPE_SYNC_FOLLOW_DELAY;
        pstcPtpInit->u32SnapFrameType    = ETH_PTP_FRAME_TYPE_IPV4FRAME;
        pstcPtpInit->u32DatagramVersion  = ETH_PTP_DATAGRAM_VERSION_IEEE1588V1;
        pstcPtpInit->u32SubSecScale      = ETH_PTP_SUBSECOND_SCALE_HEX;
        pstcPtpInit->u32CalibMode        = ETH_PTP_CALIBRATION_MODE_COARSE;
        pstcPtpInit->u32IncValueBasic    = 0UL;
        pstcPtpInit->u8IncValueSubSec    = 0U;
        pstcPtpInit->u32InitValueSec     = 0UL;
        pstcPtpInit->u32InitValueSubSec  = 0UL;
    }

    return enRet;
}

/**
 * @brief  Set PTP snapshot datagram type.
 * @param  [in] u32DatagramType             Snapshot datagram type
 *         This parameter can be one of the following values:
 *           @arg ETH_PTP_DATAGRAM_TYPE_SYNC_FOLLOW_DELAY:         SYNC Follow_Up Delay_Req Delay_Resp
 *           @arg ETH_PTP_DATAGRAM_TYPE_SYNC:                      SYNC
 *           @arg ETH_PTP_DATAGRAM_TYPE_DELAY:                     Delay_Req
 *           @arg ETH_PTP_DATAGRAM_TYPE_SYNC_FOLLOW_DELAY_PDELAY:  SYNC Follow_Up Delay_Req Delay_Resp Pdelay_Req Pdelay_Resp Pdelay_Resp_Follow_Up
 *           @arg ETH_PTP_DATAGRAM_TYPE_SYNC_PDELAY:               SYNC Pdelay_Req Pdelay_Resp
 *           @arg ETH_PTP_DATAGRAM_TYPE_DELAY_PDEALY:              Delay_Req Pdelay_Req Pdelay_Resp
 *           @arg ETH_PTP_DATAGRAM_TYPE_SYNC_DELAY:                SYNC Delay_Req
 *           @arg ETH_PTP_DATAGRAM_TYPE_PDELAY:                    Pdelay_Req Pdelay_Resp
 * @retval None
 */
void ETH_PTP_SetSnapDatagramType(uint32_t u32DatagramType)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_PTP_DATAGRAM_TYPE(u32DatagramType));

    MODIFY_REG32(M4_ETH->PTP_TSPCTLR, ETH_PTP_TSPCTLR_TSPMTSEL, u32DatagramType);
}

/**
 * @brief  Set PTP snapshot frame type.
 * @param  [in] u32FrameType              Snapshot frame type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_PTP_FRAME_TYPE_IPV4FRAME:            snapshot of IPv4 frame
 *           @arg ETH_PTP_FRAME_TYPE_IPV6FRAME:            snapshot of IPv6 frame
 *           @arg ETH_PTP_FRAME_TYPE_ETHERNETFRAME:        snapshot of PTP over ethernet frame
 *           @arg ETH_PTP_FRAME_TYPE_ALL_RECEIVEFRAME:     snapshot of all received frame
 * @retval None
 */
void ETH_PTP_SetSnapFrameType(uint32_t u32FrameType)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_PTP_FRAME_TYPE(u32FrameType));

    MODIFY_REG32(M4_ETH->PTP_TSPCTLR,
                 (ETH_PTP_TSPCTLR_TSPOVIPV4 | ETH_PTP_TSPCTLR_TSPOVIPV6 |
                  ETH_PTP_TSPCTLR_TSPOVETH  | ETH_PTP_TSPCTLR_TSPEALL),
                 u32FrameType);
}

/**
 * @brief  Set PTP timestamp calibration mode.
 * @param  [in] u32CalibMode                Timestamp calibration mode
 *         This parameter can be one of the following values:
 *           @arg ETH_PTP_CALIBRATION_MODE_COARSE:    Coarse calibration
 *           @arg ETH_PTP_CALIBRATION_MODE_FINE:      Fine calibration
 * @retval None
 */
void ETH_PTP_SetCalibMode(uint32_t u32CalibMode)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_PTP_CALIBRATION_MODE(u32CalibMode));

    WRITE_REG32(bM4_ETH->PTP_TSPCTLR_b.TSPUPSEL, u32CalibMode >> ETH_PTP_TSPCTLR_TSPUPSEL_POS);
}

/**
 * @brief  Update PTP timestamp basic increase value.
 * @note   Update Timestamp increase value by basic increase register.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Update timestamp increase value success
 *           - Error: Current state cannot be updated
 *           - ErrorTimeout: Update timeout
 */
en_result_t ETH_PTP_UpdateBasicIncValue(void)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Error;

    if (0UL == READ_REG32(bM4_ETH->PTP_TSPCTLR_b.TSPADUP))
    {
        WRITE_REG32(bM4_ETH->MMC_MMCCTLR_b.CRST, 1U);
        u32Count = ETH_TIMEOUT_WRITE_REGISTER * (HCLK_VALUE / 20000UL);
        while (0UL != READ_REG32(bM4_ETH->MMC_MMCCTLR_b.CRST))
        {
            if (0UL == u32Count)
            {
                enRet = ErrorTimeout;
                break;
            }
            u32Count--;
        }

        if (ErrorTimeout != enRet)
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Update PTP timestamp system time.
 * @note   Update Timestamp system time by update second and update subsecond registers.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Update timestamp system time success
 *           - Error: Current state cannot be updated
 *           - ErrorTimeout: Update timeout
 */
en_result_t ETH_PTP_UpdateSystemTime(void)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Error;

    if (0UL == READ_REG32(bM4_ETH->PTP_TSPCTLR_b.TSPINI))
    {
        if (0UL == READ_REG32(bM4_ETH->PTP_TSPCTLR_b.TSPUP))
        {
            WRITE_REG32(bM4_ETH->PTP_TSPCTLR_b.TSPUP, 1U);
            u32Count = ETH_TIMEOUT_WRITE_REGISTER * (HCLK_VALUE / 20000UL);
            while (0UL != READ_REG32(bM4_ETH->PTP_TSPCTLR_b.TSPUP))
            {
                if (0UL == u32Count)
                {
                    enRet = ErrorTimeout;
                    break;
                }
                u32Count--;
            }

            if (ErrorTimeout != enRet)
            {
                enRet = Ok;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Initialize PTP timestamp system time.
 * @note   Initialize Timestamp system time by update second and update subsecond registers.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize timestamp system time success
 *           - Error: Current state cannot be initialized
 *           - ErrorTimeout: Initialize timeout
 */
en_result_t ETH_PTP_SystemTimeInit(void)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Error;

    if (0UL == READ_REG32(bM4_ETH->PTP_TSPCTLR_b.TSPINI))
    {
        WRITE_REG32(bM4_ETH->PTP_TSPCTLR_b.TSPINI, 1U);
        u32Count = ETH_TIMEOUT_WRITE_REGISTER * (HCLK_VALUE / 20000UL);
        while (0UL != READ_REG32(bM4_ETH->PTP_TSPCTLR_b.TSPINI))
        {
            if (0UL == u32Count)
            {
                enRet = ErrorTimeout;
                break;
            }
            u32Count--;
        }

        if (ErrorTimeout != enRet)
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Get PTP timestamp system time.
 * @param  [out] pu32Sec                    Pointer to Timestamp system time of Second
 * @param  [out] pu32SubSec                 Pointer to Timestamp system time of Subsecond
 * @retval An en_result_t enumeration value:
 *           - Ok: Get timestamp system time success
 *           - ErrorInvalidParameter: pu32Sec == NULL or pu32SubSec == NULL
 */
en_result_t ETH_PTP_GetSystemTime(uint32_t *pu32Sec, uint32_t *pu32SubSec)
{
    en_result_t enRet = Ok;

    if ((NULL == pu32Sec) || (NULL == pu32SubSec))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        *pu32Sec    = READ_REG32(M4_ETH->PTP_TMSSECR);
        *pu32SubSec = READ_REG32(M4_ETH->PTP_TMSNSER);
    }

    return enRet;
}

/**
 * @brief  Set PTP timestamp increase value.
 * @param  [in] u32BasicVal                 Timestamp increase value of Second (Between 0x0 and 0xFFFFFFFF)
 * @param  [in] u8SubSecVal                 Timestamp increase value of Subsecond (Between 0x0 and 0xFF)
 * @retval None
 */
void ETH_PTP_SetIncValue(uint32_t u32BasicVal, uint8_t u8SubSecVal)
{
    WRITE_REG32(M4_ETH->PTP_TSPADDR, u32BasicVal);
    WRITE_REG32(M4_ETH->PTP_TSPNSAR, u8SubSecVal);
}

/**
 * @brief  Get PTP timestamp increase value.
 * @param  [out] pu32BasicVal               Pointer to Timestamp increase value of basic
 * @param  [out] pu8SubSecVal               Pointer to Timestamp increase value of Subsecond
 * @retval An en_result_t enumeration value:
 *           - Ok: Get timestamp increase value success
 *           - ErrorInvalidParameter: pu32BasicVal == NULL or pu8SubSecVal == NULL
 */
en_result_t ETH_PTP_GetIncValue(uint32_t *pu32BasicVal, uint8_t *pu8SubSecVal)
{
    en_result_t enRet = Ok;

    if ((NULL == pu32BasicVal) || (NULL == pu8SubSecVal))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        *pu32BasicVal = READ_REG32(M4_ETH->PTP_TSPADDR);
        *pu8SubSecVal = (uint8_t)(READ_REG32(M4_ETH->PTP_TSPNSAR) & ETH_PTP_TSPNSAR_TSPNSEADD);
    }

    return enRet;
}

/**
 * @brief  Set PTP timestamp update time.
 * @param  [in] u32Sign                     Timestamp Update Sign
 *           @arg ETH_PTP_TIME_UPDATE_SIGN_MINUS:   Minus
 *           @arg ETH_PTP_TIME_UPDATE_SIGN_PLUS:    Plus
 * @param  [in] u32Sec                      Update time of Second (Between 0x0 and 0xFFFFFFFF)
 * @param  [in] u32SubSec                   Update time of Subsecond (Between 0x0 and 0x7FFFFFFF)
 * @retval None
 */
void ETH_PTP_SetUpdateTime(uint32_t u32Sign, uint32_t u32Sec, uint32_t u32SubSec)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_PTP_TIME_UPDATE_SIGN(u32Sign));
    DDL_ASSERT(IS_ETH_PTP_SUB_SECOND(u32SubSec));

    WRITE_REG32(M4_ETH->PTP_TMUSECR, u32Sec);
    WRITE_REG32(M4_ETH->PTP_TMUNSER, (u32Sign | u32SubSec));
}

/**
 * @brief  Enable or disable PTP function.
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_PTP_Cmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_ETH->PTP_TSPCTLR_b.TSPEN, enNewSta);
}

/**
 * @brief  Enable or disable PTP interrupt.
 * @param  [in] enNewSta                    The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void ETH_PTP_IntCmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_ETH->PTP_TSPCTLR_b.TSPINT, enNewSta);
}

/**
 * @brief  Get PTP flag status.
 * @param  [in] u32Flag                     PTP flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg ETH_PTP_FLAG_TSERR1:      Target time 1 error
 *           @arg ETH_PTP_FLAG_TSTAR1:      Target time 1 reached
 *           @arg ETH_PTP_FLAG_TSERR0:      Target time 0 error
 *           @arg ETH_PTP_FLAG_TSTAR0:      Target time 0 reached
 *           @arg ETH_PTP_FLAG_TSOVF:       System time overflow
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t ETH_PTP_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_PTP_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(M4_ETH->PTP_TSPSTSR, u32Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/******************************************************************************/
/*                            PTP PPS Functions                               */
/******************************************************************************/
/**
 * @brief  De-Initialize PTP PPS.
 * @param  [in] u8Ch                        PPS output channel
 *         This parameter can be one of the following values:
 *           @arg ETH_PPS_TARGET_CH0:       PPS Channel 0
 *           @arg ETH_PPS_TARGET_CH1:       PPS Channel 1
 * @retval None
 */
void ETH_PPS_DeInit(uint8_t u8Ch)
{
    uint32_t u32ShiftStep = 0UL;
    uint32_t u32ShiftBit = 0UL;
    __IO uint32_t *PTP_TMTSECR;
    __IO uint32_t *PTP_TMTNSER;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_PPS_TARGET_CH(u8Ch));

    if (ETH_PPS_TARGET_CH1 == u8Ch)
    {
        u32ShiftBit  = ETH_PTP_PPSCTLR_PPSFRE1_POS;
        u32ShiftStep = ETH_PTP_PPS1_TIME_REG_ADDRSHIFT;
    }
    CLEAR_REG32_BIT(M4_ETH->PTP_PPSCTLR,
                    ((ETH_PTP_PPSCTLR_PPSFRE0 | ETH_PTP_PPSCTLR_PPSOMD |
                     ETH_PTP_PPSCTLR_TT0SEL) << u32ShiftBit));
    /* Clear target time registers */
    PTP_TMTSECR = (__IO uint32_t *)ETH_PTP_TMTSECRx(u32ShiftStep);
    PTP_TMTNSER = (__IO uint32_t *)ETH_PTP_TMTNSERx(u32ShiftStep);
    WRITE_REG32(*PTP_TMTSECR, 0UL);
    WRITE_REG32(*PTP_TMTNSER, 0UL);
}

/**
 * @brief  Initialize PTP PPS.
 * @param  [in] u8Ch                        PPS output channel
 *         This parameter can be one of the following values:
 *           @arg ETH_PPS_TARGET_CH0:       PPS Channel 0
 *           @arg ETH_PPS_TARGET_CH1:       PPS Channel 1
 * @param  [in] pstcPpsInit                 Pointer to a @ref stc_eth_pps_config_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: PPS Initialize success
 *           - ErrorInvalidParameter: pstcPpsInit == NULL
 */
en_result_t ETH_PPS_Init(uint8_t u8Ch, const stc_eth_pps_config_t *pstcPpsInit)
{
    en_result_t enRet = Ok;
    uint32_t u32ShiftStep = 0UL;
    uint32_t u32ShiftBit = 0UL;
    uint32_t u32RegVal;
    __IO uint32_t *PTP_TMTSECR;
    __IO uint32_t *PTP_TMTNSER;

    if (NULL == pstcPpsInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_ETH_PPS_TARGET_CH(u8Ch));
        DDL_ASSERT(IS_ETH_PTP_SUB_SECOND(pstcPpsInit->u32TargetTimeSubSec));
        DDL_ASSERT(IS_ETH_PPS_TARGET_TIME_FUNC(pstcPpsInit->u32TargetTimeFunc));
        DDL_ASSERT(IS_ETH_PPS_OUTPUT_MODE(pstcPpsInit->u32OutputMode));
        DDL_ASSERT(IS_ETH_PPS_OUTPUT_FREQ(pstcPpsInit->u32OutputFreq));
        DDL_ASSERT(IS_ETH_PPS1_COMPLEX_FUNC(u8Ch, pstcPpsInit->u32OutputMode, pstcPpsInit->u32OutputFreq));

        u32RegVal = pstcPpsInit->u32OutputFreq | pstcPpsInit->u32TargetTimeFunc;
        if (ETH_PPS_TARGET_CH1 == u8Ch)
        {
            u32ShiftBit  = ETH_PTP_PPSCTLR_PPSFRE1_POS;
            u32ShiftStep = ETH_PTP_PPS1_TIME_REG_ADDRSHIFT;
        }
        else
        {
            u32RegVal |= pstcPpsInit->u32OutputMode;
        }
        MODIFY_REG32(M4_ETH->PTP_PPSCTLR,
                     ((ETH_PTP_PPSCTLR_PPSFRE0 | ETH_PTP_PPSCTLR_PPSOMD |
                       ETH_PTP_PPSCTLR_TT0SEL) << u32ShiftBit),
                     (u32RegVal << u32ShiftBit));
        /* Set target time registers */
        PTP_TMTSECR = (__IO uint32_t *)ETH_PTP_TMTSECRx(u32ShiftStep);
        PTP_TMTNSER = (__IO uint32_t *)ETH_PTP_TMTNSERx(u32ShiftStep);
        WRITE_REG32(*PTP_TMTSECR, pstcPpsInit->u32TargetTimeSec);
        WRITE_REG32(*PTP_TMTNSER, pstcPpsInit->u32TargetTimeSubSec);
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_eth_pps_config_t to default values.
 * @param  [out] pstcPpsInit                Pointer to a @ref stc_eth_pps_config_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Structure Initialize success
 *           - ErrorInvalidParameter: pstcPpsInit == NULL
 */
en_result_t ETH_PPS_StructInit(stc_eth_pps_config_t *pstcPpsInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcPpsInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcPpsInit->u32TargetTimeFunc   = ETH_PPS_TARGET_TIME_FUNC_INT_EVENT;
        pstcPpsInit->u32OutputMode       = ETH_PPS_OUTPUT_MODE_SINGLE;
        pstcPpsInit->u32OutputFreq       = ETH_PPS_OUTPUT_ONE_PULSE;
        pstcPpsInit->u32TargetTimeSec    = 0UL;
        pstcPpsInit->u32TargetTimeSubSec = 0UL;
    }

    return enRet;
}

/**
 * @brief  Set PTP Target time function.
 * @param  [in] u8Ch                        PPS output channel
 *         This parameter can be one of the following values:
 *           @arg ETH_PPS_TARGET_CH0:       PPS Channel 0
 *           @arg ETH_PPS_TARGET_CH1:       PPS Channel 1
 * @param  [in] u32Sec                      Target time of Second (Between 0x0 and 0xFFFFFFFF)
 * @param  [in] u32SubSec                   Target time of Subsecond (Between 0x0 and 0x7FFFFFFF)
 * @retval None
 */
void ETH_PPS_SetTargetTime(uint8_t u8Ch, uint32_t u32Sec, uint32_t u32SubSec)
{
    uint32_t u32ShiftStep = 0UL;
    __IO uint32_t *PTP_TMTSECR;
    __IO uint32_t *PTP_TMTNSER;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_PPS_TARGET_CH(u8Ch));
    DDL_ASSERT(IS_ETH_PTP_SUB_SECOND(u32SubSec));

    if (ETH_PPS_TARGET_CH1 == u8Ch)
    {
        u32ShiftStep = ETH_PTP_PPS1_TIME_REG_ADDRSHIFT;
    }
    PTP_TMTSECR = (__IO uint32_t *)ETH_PTP_TMTSECRx(u32ShiftStep);
    PTP_TMTNSER = (__IO uint32_t *)ETH_PTP_TMTNSERx(u32ShiftStep);
    WRITE_REG32(*PTP_TMTSECR, u32Sec);
    WRITE_REG32(*PTP_TMTNSER, u32SubSec);
}

/**
 * @brief  Set PTP Target time function.
 * @param  [in] u8Ch                        PPS output channel
 *         This parameter can be one of the following values:
 *           @arg ETH_PPS_TARGET_CH0:       PPS Channel 0
 *           @arg ETH_PPS_TARGET_CH1:       PPS Channel 1
 * @param  [in] u32Func                     Arrival time trigger the function
 *         This parameter can be one of the following values:
 *           @arg ETH_PPS_TARGET_TIME_FUNC_INT_EVENT:       Interrupt output event
 *           @arg ETH_PPS_TARGET_TIME_FUNC_INT_PPS_EVENT:   Interrupt out event and PPS single output event
 *           @arg ETH_PPS_TARGET_TIME_FUNC_PPS_EVENT:       PPS Single output event
 * @retval None
 */
void ETH_PPS_SetTargetTimeFunc(uint8_t u8Ch, uint32_t u32Func)
{
    uint32_t u32ShiftBit = 0UL;

    /* Check parameters */
    DDL_ASSERT(IS_ETH_PPS_TARGET_CH(u8Ch));
    DDL_ASSERT(IS_ETH_PPS_TARGET_TIME_FUNC(u32Func));

    if (ETH_PPS_TARGET_CH1 == u8Ch)
    {
        u32ShiftBit = ETH_PTP_PPSCTLR_PPSFRE1_POS;
    }
    MODIFY_REG32(M4_ETH->PTP_PPSCTLR, (ETH_PTP_PPSCTLR_TT0SEL << u32ShiftBit), (u32Func << u32ShiftBit));
}

/**
 * @brief  Set PTP PPS0 output mode.
 * @param  [in] u32OutputMode               PPS output mode
 *         This parameter can be one of the following values:
 *           @arg ETH_PPS_OUTPUT_MODE_CONTINUE: Continuous output mode
 *           @arg ETH_PPS_OUTPUT_MODE_SINGLE:   Single output mode
 * @retval None
 */
void ETH_PPS_SetPps0OutputMode(uint32_t u32OutputMode)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_PPS_OUTPUT_MODE(u32OutputMode));

    WRITE_REG32(bM4_ETH->PTP_PPSCTLR_b.PPSOMD, u32OutputMode >> ETH_PTP_PPSCTLR_PPSOMD_POS);
}

/**
 * @brief  Set PTP PPS0 output frequency.
 * @param  [in] u32OutputFreq               PPS output frequency
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
void ETH_PPS_SetPps0OutputFreq(uint32_t u32OutputFreq)
{
    /* Check parameters */
    DDL_ASSERT(IS_ETH_PPS_OUTPUT_FREQ(u32OutputFreq));

    MODIFY_REG32(M4_ETH->PTP_PPSCTLR, ETH_PTP_PPSCTLR_PPSFRE0, u32OutputFreq);
}

/**
 * @}
 */

#endif /* DDL_ETH_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
