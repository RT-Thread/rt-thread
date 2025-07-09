/*
** ###################################################################
**     Processors:          MIMXRT1171AVM8A
**                          MIMXRT1171AVM8B
**                          MIMXRT1171CVM8A
**                          MIMXRT1171CVM8B
**                          MIMXRT1171DVMAA
**                          MIMXRT1171DVMAB
**                          MIMXRT1172AVM8A
**                          MIMXRT1172AVM8B
**                          MIMXRT1172CVM8A
**                          MIMXRT1172CVM8B
**                          MIMXRT1172DVMAA
**                          MIMXRT1172DVMAB
**                          MIMXRT1173CVM8A_cm4
**                          MIMXRT1173CVM8A_cm7
**                          MIMXRT1173CVM8B_cm4
**                          MIMXRT1173CVM8B_cm7
**                          MIMXRT1175AVM8A_cm4
**                          MIMXRT1175AVM8A_cm7
**                          MIMXRT1175AVM8B_cm4
**                          MIMXRT1175AVM8B_cm7
**                          MIMXRT1175CVM8A_cm4
**                          MIMXRT1175CVM8A_cm7
**                          MIMXRT1175CVM8B_cm4
**                          MIMXRT1175CVM8B_cm7
**                          MIMXRT1175DVMAA_cm4
**                          MIMXRT1175DVMAA_cm7
**                          MIMXRT1175DVMAB_cm4
**                          MIMXRT1175DVMAB_cm7
**                          MIMXRT1176AVM8A_cm4
**                          MIMXRT1176AVM8A_cm7
**                          MIMXRT1176AVM8B_cm4
**                          MIMXRT1176AVM8B_cm7
**                          MIMXRT1176CVM8A_cm4
**                          MIMXRT1176CVM8A_cm7
**                          MIMXRT1176CVM8B_cm4
**                          MIMXRT1176CVM8B_cm7
**                          MIMXRT1176DVMAA_cm4
**                          MIMXRT1176DVMAA_cm7
**                          MIMXRT1176DVMAB_cm4
**                          MIMXRT1176DVMAB_cm7
**                          MIMXRT117HAVM8A_cm4
**                          MIMXRT117HAVM8A_cm7
**                          MIMXRT117HAVM8B_cm4
**                          MIMXRT117HAVM8B_cm7
**                          MIMXRT117HCVM8A_cm4
**                          MIMXRT117HCVM8A_cm7
**                          MIMXRT117HCVM8B_cm4
**                          MIMXRT117HCVM8B_cm7
**                          MIMXRT117HDVMAA_cm4
**                          MIMXRT117HDVMAA_cm7
**                          MIMXRT117HDVMAB_cm4
**                          MIMXRT117HDVMAB_cm7
**
**     Version:             rev. 2.0, 2024-10-29
**     Build:               b250520
**
**     Abstract:
**         CMSIS Peripheral Access Layer for ENET_QOS
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2025 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 0.1 (2018-03-05)
**         Initial version.
**     - rev. 1.0 (2020-12-29)
**         Update header files to align with IMXRT1170RM Rev.0.
**     - rev. 2.0 (2024-10-29)
**         Change the device header file from single flat file to multiple files based on peripherals,
**         each peripheral with dedicated header file located in periphN folder.
**
** ###################################################################
*/

/*!
 * @file PERI_ENET_QOS.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for ENET_QOS
 *
 * CMSIS Peripheral Access Layer for ENET_QOS
 */

#if !defined(PERI_ENET_QOS_H_)
#define PERI_ENET_QOS_H_                         /**< Symbol preventing repeated inclusion */

#if (defined(CPU_MIMXRT1171AVM8A) || defined(CPU_MIMXRT1171AVM8B) || defined(CPU_MIMXRT1171CVM8A) || defined(CPU_MIMXRT1171CVM8B) || defined(CPU_MIMXRT1171DVMAA) || defined(CPU_MIMXRT1171DVMAB))
#include "MIMXRT1171_COMMON.h"
#elif (defined(CPU_MIMXRT1172AVM8A) || defined(CPU_MIMXRT1172AVM8B) || defined(CPU_MIMXRT1172CVM8A) || defined(CPU_MIMXRT1172CVM8B) || defined(CPU_MIMXRT1172DVMAA) || defined(CPU_MIMXRT1172DVMAB))
#include "MIMXRT1172_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm4) || defined(CPU_MIMXRT1173CVM8B_cm4))
#include "MIMXRT1173_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm7) || defined(CPU_MIMXRT1173CVM8B_cm7))
#include "MIMXRT1173_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm4) || defined(CPU_MIMXRT1175AVM8B_cm4) || defined(CPU_MIMXRT1175CVM8A_cm4) || defined(CPU_MIMXRT1175CVM8B_cm4) || defined(CPU_MIMXRT1175DVMAA_cm4) || defined(CPU_MIMXRT1175DVMAB_cm4))
#include "MIMXRT1175_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm7) || defined(CPU_MIMXRT1175AVM8B_cm7) || defined(CPU_MIMXRT1175CVM8A_cm7) || defined(CPU_MIMXRT1175CVM8B_cm7) || defined(CPU_MIMXRT1175DVMAA_cm7) || defined(CPU_MIMXRT1175DVMAB_cm7))
#include "MIMXRT1175_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm4) || defined(CPU_MIMXRT1176AVM8B_cm4) || defined(CPU_MIMXRT1176CVM8A_cm4) || defined(CPU_MIMXRT1176CVM8B_cm4) || defined(CPU_MIMXRT1176DVMAA_cm4) || defined(CPU_MIMXRT1176DVMAB_cm4))
#include "MIMXRT1176_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm7) || defined(CPU_MIMXRT1176AVM8B_cm7) || defined(CPU_MIMXRT1176CVM8A_cm7) || defined(CPU_MIMXRT1176CVM8B_cm7) || defined(CPU_MIMXRT1176DVMAA_cm7) || defined(CPU_MIMXRT1176DVMAB_cm7))
#include "MIMXRT1176_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm4) || defined(CPU_MIMXRT117HAVM8B_cm4) || defined(CPU_MIMXRT117HCVM8A_cm4) || defined(CPU_MIMXRT117HCVM8B_cm4) || defined(CPU_MIMXRT117HDVMAA_cm4) || defined(CPU_MIMXRT117HDVMAB_cm4))
#include "MIMXRT117H_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm7) || defined(CPU_MIMXRT117HAVM8B_cm7) || defined(CPU_MIMXRT117HCVM8A_cm7) || defined(CPU_MIMXRT117HCVM8B_cm7) || defined(CPU_MIMXRT117HDVMAA_cm7) || defined(CPU_MIMXRT117HDVMAB_cm7))
#include "MIMXRT117H_cm7_COMMON.h"
#else
  #error "No valid CPU defined!"
#endif

/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- ENET_QOS Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ENET_QOS_Peripheral_Access_Layer ENET_QOS Peripheral Access Layer
 * @{
 */

/** ENET_QOS - Size of Registers Arrays */
#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_COUNT         5u
#define ENET_QOS_MAC_RXQ_CTRL_COUNT               4u
#define ENET_QOS_MAC_HW_FEAT_COUNT                4u
#define ENET_QOS_MAC_ADDRESS_COUNT                64u
#define ENET_QOS_MTL_QUEUE_COUNT                  5u
#define ENET_QOS_DMA_CH_COUNT                     5u

/** ENET_QOS - Register Layout Typedef */
typedef struct {
  __IO uint32_t MAC_CONFIGURATION;                 /**< MAC Configuration Register, offset: 0x0 */
  __IO uint32_t MAC_EXT_CONFIGURATION;             /**< MAC Extended Configuration Register, offset: 0x4 */
  __IO uint32_t MAC_PACKET_FILTER;                 /**< MAC Packet Filter, offset: 0x8 */
  __IO uint32_t MAC_WATCHDOG_TIMEOUT;              /**< Watchdog Timeout, offset: 0xC */
  __IO uint32_t MAC_HASH_TABLE_REG0;               /**< MAC Hash Table Register 0, offset: 0x10 */
  __IO uint32_t MAC_HASH_TABLE_REG1;               /**< MAC Hash Table Register 1, offset: 0x14 */
       uint8_t RESERVED_0[56];
  __IO uint32_t MAC_VLAN_TAG_CTRL;                 /**< MAC VLAN Tag Control, offset: 0x50 */
  __IO uint32_t MAC_VLAN_TAG_DATA;                 /**< MAC VLAN Tag Data, offset: 0x54 */
  __IO uint32_t MAC_VLAN_HASH_TABLE;               /**< MAC VLAN Hash Table, offset: 0x58 */
       uint8_t RESERVED_1[4];
  __IO uint32_t MAC_VLAN_INCL;                     /**< VLAN Tag Inclusion or Replacement, offset: 0x60 */
  __IO uint32_t MAC_INNER_VLAN_INCL;               /**< MAC Inner VLAN Tag Inclusion or Replacement, offset: 0x64 */
       uint8_t RESERVED_2[8];
  __IO uint32_t MAC_TX_FLOW_CTRL_Q[ENET_QOS_MAC_TX_FLOW_CTRL_Q_COUNT]; /**< MAC Q0 Tx Flow Control..MAC Q4 Tx Flow Control, array offset: 0x70, array step: 0x4 */
       uint8_t RESERVED_3[12];
  __IO uint32_t MAC_RX_FLOW_CTRL;                  /**< MAC Rx Flow Control, offset: 0x90 */
  __IO uint32_t MAC_RXQ_CTRL4;                     /**< Receive Queue Control 4, offset: 0x94 */
  __IO uint32_t MAC_TXQ_PRTY_MAP0;                 /**< Transmit Queue Priority Mapping 0, offset: 0x98 */
  __IO uint32_t MAC_TXQ_PRTY_MAP1;                 /**< Transmit Queue Priority Mapping 1, offset: 0x9C */
  __IO uint32_t MAC_RXQ_CTRL[ENET_QOS_MAC_RXQ_CTRL_COUNT]; /**< Receive Queue Control 0..Receive Queue Control 3, array offset: 0xA0, array step: 0x4 */
  __I  uint32_t MAC_INTERRUPT_STATUS;              /**< Interrupt Status, offset: 0xB0 */
  __IO uint32_t MAC_INTERRUPT_ENABLE;              /**< Interrupt Enable, offset: 0xB4 */
  __I  uint32_t MAC_RX_TX_STATUS;                  /**< Receive Transmit Status, offset: 0xB8 */
       uint8_t RESERVED_4[4];
  __IO uint32_t MAC_PMT_CONTROL_STATUS;            /**< PMT Control and Status, offset: 0xC0 */
  __IO uint32_t MAC_RWK_PACKET_FILTER;             /**< Remote Wakeup Filter, offset: 0xC4 */
       uint8_t RESERVED_5[8];
  __IO uint32_t MAC_LPI_CONTROL_STATUS;            /**< LPI Control and Status, offset: 0xD0 */
  __IO uint32_t MAC_LPI_TIMERS_CONTROL;            /**< LPI Timers Control, offset: 0xD4 */
  __IO uint32_t MAC_LPI_ENTRY_TIMER;               /**< Tx LPI Entry Timer Control, offset: 0xD8 */
  __IO uint32_t MAC_ONEUS_TIC_COUNTER;             /**< One-microsecond Reference Timer, offset: 0xDC */
       uint8_t RESERVED_6[24];
  __IO uint32_t MAC_PHYIF_CONTROL_STATUS;          /**< PHY Interface Control and Status, offset: 0xF8 */
       uint8_t RESERVED_7[20];
  __I  uint32_t MAC_VERSION;                       /**< MAC Version, offset: 0x110 */
  __I  uint32_t MAC_DEBUG;                         /**< MAC Debug, offset: 0x114 */
       uint8_t RESERVED_8[4];
  __I  uint32_t MAC_HW_FEAT[ENET_QOS_MAC_HW_FEAT_COUNT]; /**< Optional Features or Functions 0..Optional Features or Functions 3, array offset: 0x11C, array step: 0x4 */
       uint8_t RESERVED_9[212];
  __IO uint32_t MAC_MDIO_ADDRESS;                  /**< MDIO Address, offset: 0x200 */
  __IO uint32_t MAC_MDIO_DATA;                     /**< MAC MDIO Data, offset: 0x204 */
       uint8_t RESERVED_10[40];
  __IO uint32_t MAC_CSR_SW_CTRL;                   /**< CSR Software Control, offset: 0x230 */
  __IO uint32_t MAC_FPE_CTRL_STS;                  /**< Frame Preemption Control, offset: 0x234 */
       uint8_t RESERVED_11[8];
  __I  uint32_t MAC_PRESN_TIME_NS;                 /**< 32-bit Binary Rollover Equivalent Time, offset: 0x240 */
  __IO uint32_t MAC_PRESN_TIME_UPDT;               /**< MAC 1722 Presentation Time, offset: 0x244 */
       uint8_t RESERVED_12[184];
  struct {                                         /* offset: 0x300, array step: 0x8 */
    __IO uint32_t HIGH;                              /**< MAC Address0 High..MAC Address63 High, array offset: 0x300, array step: 0x8 */
    __IO uint32_t LOW;                               /**< MAC Address0 Low..MAC Address63 Low, array offset: 0x304, array step: 0x8 */
  } MAC_ADDRESS[ENET_QOS_MAC_ADDRESS_COUNT];
       uint8_t RESERVED_13[512];
  __IO uint32_t MAC_MMC_CONTROL;                   /**< MMC Control, offset: 0x700 */
  __I  uint32_t MAC_MMC_RX_INTERRUPT;              /**< MMC Rx Interrupt, offset: 0x704 */
  __I  uint32_t MAC_MMC_TX_INTERRUPT;              /**< MMC Tx Interrupt, offset: 0x708 */
  __IO uint32_t MAC_MMC_RX_INTERRUPT_MASK;         /**< MMC Rx Interrupt Mask, offset: 0x70C */
  __IO uint32_t MAC_MMC_TX_INTERRUPT_MASK;         /**< MMC Tx Interrupt Mask, offset: 0x710 */
  __I  uint32_t MAC_TX_OCTET_COUNT_GOOD_BAD;       /**< Tx Octet Count Good and Bad, offset: 0x714 */
  __I  uint32_t MAC_TX_PACKET_COUNT_GOOD_BAD;      /**< Tx Packet Count Good and Bad, offset: 0x718 */
  __I  uint32_t MAC_TX_BROADCAST_PACKETS_GOOD;     /**< Tx Broadcast Packets Good, offset: 0x71C */
  __I  uint32_t MAC_TX_MULTICAST_PACKETS_GOOD;     /**< Tx Multicast Packets Good, offset: 0x720 */
  __I  uint32_t MAC_TX_64OCTETS_PACKETS_GOOD_BAD;  /**< Tx Good and Bad 64-Byte Packets, offset: 0x724 */
  __I  uint32_t MAC_TX_65TO127OCTETS_PACKETS_GOOD_BAD; /**< Tx Good and Bad 65 to 127-Byte Packets, offset: 0x728 */
  __I  uint32_t MAC_TX_128TO255OCTETS_PACKETS_GOOD_BAD; /**< Tx Good and Bad 128 to 255-Byte Packets, offset: 0x72C */
  __I  uint32_t MAC_TX_256TO511OCTETS_PACKETS_GOOD_BAD; /**< Tx Good and Bad 256 to 511-Byte Packets, offset: 0x730 */
  __I  uint32_t MAC_TX_512TO1023OCTETS_PACKETS_GOOD_BAD; /**< Tx Good and Bad 512 to 1023-Byte Packets, offset: 0x734 */
  __I  uint32_t MAC_TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD; /**< Tx Good and Bad 1024 to Max-Byte Packets, offset: 0x738 */
  __I  uint32_t MAC_TX_UNICAST_PACKETS_GOOD_BAD;   /**< Good and Bad Unicast Packets Transmitted, offset: 0x73C */
  __I  uint32_t MAC_TX_MULTICAST_PACKETS_GOOD_BAD; /**< Good and Bad Multicast Packets Transmitted, offset: 0x740 */
  __I  uint32_t MAC_TX_BROADCAST_PACKETS_GOOD_BAD; /**< Good and Bad Broadcast Packets Transmitted, offset: 0x744 */
  __I  uint32_t MAC_TX_UNDERFLOW_ERROR_PACKETS;    /**< Tx Packets Aborted By Underflow Error, offset: 0x748 */
  __I  uint32_t MAC_TX_SINGLE_COLLISION_GOOD_PACKETS; /**< Single Collision Good Packets Transmitted, offset: 0x74C */
  __I  uint32_t MAC_TX_MULTIPLE_COLLISION_GOOD_PACKETS; /**< Multiple Collision Good Packets Transmitted, offset: 0x750 */
  __I  uint32_t MAC_TX_DEFERRED_PACKETS;           /**< Deferred Packets Transmitted, offset: 0x754 */
  __I  uint32_t MAC_TX_LATE_COLLISION_PACKETS;     /**< Late Collision Packets Transmitted, offset: 0x758 */
  __I  uint32_t MAC_TX_EXCESSIVE_COLLISION_PACKETS; /**< Excessive Collision Packets Transmitted, offset: 0x75C */
  __I  uint32_t MAC_TX_CARRIER_ERROR_PACKETS;      /**< Carrier Error Packets Transmitted, offset: 0x760 */
  __I  uint32_t MAC_TX_OCTET_COUNT_GOOD;           /**< Bytes Transmitted in Good Packets, offset: 0x764 */
  __I  uint32_t MAC_TX_PACKET_COUNT_GOOD;          /**< Good Packets Transmitted, offset: 0x768 */
  __I  uint32_t MAC_TX_EXCESSIVE_DEFERRAL_ERROR;   /**< Packets Aborted By Excessive Deferral Error, offset: 0x76C */
  __I  uint32_t MAC_TX_PAUSE_PACKETS;              /**< Pause Packets Transmitted, offset: 0x770 */
  __I  uint32_t MAC_TX_VLAN_PACKETS_GOOD;          /**< Good VLAN Packets Transmitted, offset: 0x774 */
  __I  uint32_t MAC_TX_OSIZE_PACKETS_GOOD;         /**< Good Oversize Packets Transmitted, offset: 0x778 */
       uint8_t RESERVED_14[4];
  __I  uint32_t MAC_RX_PACKETS_COUNT_GOOD_BAD;     /**< Good and Bad Packets Received, offset: 0x780 */
  __I  uint32_t MAC_RX_OCTET_COUNT_GOOD_BAD;       /**< Bytes in Good and Bad Packets Received, offset: 0x784 */
  __I  uint32_t MAC_RX_OCTET_COUNT_GOOD;           /**< Bytes in Good Packets Received, offset: 0x788 */
  __I  uint32_t MAC_RX_BROADCAST_PACKETS_GOOD;     /**< Good Broadcast Packets Received, offset: 0x78C */
  __I  uint32_t MAC_RX_MULTICAST_PACKETS_GOOD;     /**< Good Multicast Packets Received, offset: 0x790 */
  __I  uint32_t MAC_RX_CRC_ERROR_PACKETS;          /**< CRC Error Packets Received, offset: 0x794 */
  __I  uint32_t MAC_RX_ALIGNMENT_ERROR_PACKETS;    /**< Alignment Error Packets Received, offset: 0x798 */
  __I  uint32_t MAC_RX_RUNT_ERROR_PACKETS;         /**< Runt Error Packets Received, offset: 0x79C */
  __I  uint32_t MAC_RX_JABBER_ERROR_PACKETS;       /**< Jabber Error Packets Received, offset: 0x7A0 */
  __I  uint32_t MAC_RX_UNDERSIZE_PACKETS_GOOD;     /**< Good Undersize Packets Received, offset: 0x7A4 */
  __I  uint32_t MAC_RX_OVERSIZE_PACKETS_GOOD;      /**< Good Oversize Packets Received, offset: 0x7A8 */
  __I  uint32_t MAC_RX_64OCTETS_PACKETS_GOOD_BAD;  /**< Good and Bad 64-Byte Packets Received, offset: 0x7AC */
  __I  uint32_t MAC_RX_65TO127OCTETS_PACKETS_GOOD_BAD; /**< Good and Bad 64-to-127 Byte Packets Received, offset: 0x7B0 */
  __I  uint32_t MAC_RX_128TO255OCTETS_PACKETS_GOOD_BAD; /**< Good and Bad 128-to-255 Byte Packets Received, offset: 0x7B4 */
  __I  uint32_t MAC_RX_256TO511OCTETS_PACKETS_GOOD_BAD; /**< Good and Bad 256-to-511 Byte Packets Received, offset: 0x7B8 */
  __I  uint32_t MAC_RX_512TO1023OCTETS_PACKETS_GOOD_BAD; /**< Good and Bad 512-to-1023 Byte Packets Received, offset: 0x7BC */
  __I  uint32_t MAC_RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD; /**< Good and Bad 1024-to-Max Byte Packets Received, offset: 0x7C0 */
  __I  uint32_t MAC_RX_UNICAST_PACKETS_GOOD;       /**< Good Unicast Packets Received, offset: 0x7C4 */
  __I  uint32_t MAC_RX_LENGTH_ERROR_PACKETS;       /**< Length Error Packets Received, offset: 0x7C8 */
  __I  uint32_t MAC_RX_OUT_OF_RANGE_TYPE_PACKETS;  /**< Out-of-range Type Packets Received, offset: 0x7CC */
  __I  uint32_t MAC_RX_PAUSE_PACKETS;              /**< Pause Packets Received, offset: 0x7D0 */
  __I  uint32_t MAC_RX_FIFO_OVERFLOW_PACKETS;      /**< Missed Packets Due to FIFO Overflow, offset: 0x7D4 */
  __I  uint32_t MAC_RX_VLAN_PACKETS_GOOD_BAD;      /**< Good and Bad VLAN Packets Received, offset: 0x7D8 */
  __I  uint32_t MAC_RX_WATCHDOG_ERROR_PACKETS;     /**< Watchdog Error Packets Received, offset: 0x7DC */
  __I  uint32_t MAC_RX_RECEIVE_ERROR_PACKETS;      /**< Receive Error Packets Received, offset: 0x7E0 */
  __I  uint32_t MAC_RX_CONTROL_PACKETS_GOOD;       /**< Good Control Packets Received, offset: 0x7E4 */
       uint8_t RESERVED_15[4];
  __I  uint32_t MAC_TX_LPI_USEC_CNTR;              /**< Microseconds Tx LPI Asserted, offset: 0x7EC */
  __I  uint32_t MAC_TX_LPI_TRAN_CNTR;              /**< Number of Times Tx LPI Asserted, offset: 0x7F0 */
  __I  uint32_t MAC_RX_LPI_USEC_CNTR;              /**< Microseconds Rx LPI Sampled, offset: 0x7F4 */
  __I  uint32_t MAC_RX_LPI_TRAN_CNTR;              /**< Number of Times Rx LPI Entered, offset: 0x7F8 */
       uint8_t RESERVED_16[4];
  __IO uint32_t MAC_MMC_IPC_RX_INTERRUPT_MASK;     /**< MMC IPC Receive Interrupt Mask, offset: 0x800 */
       uint8_t RESERVED_17[4];
  __I  uint32_t MAC_MMC_IPC_RX_INTERRUPT;          /**< MMC IPC Receive Interrupt, offset: 0x808 */
       uint8_t RESERVED_18[4];
  __I  uint32_t MAC_RXIPV4_GOOD_PACKETS;           /**< Good IPv4 Datagrams Received, offset: 0x810 */
  __I  uint32_t MAC_RXIPV4_HEADER_ERROR_PACKETS;   /**< IPv4 Datagrams Received with Header Errors, offset: 0x814 */
  __I  uint32_t MAC_RXIPV4_NO_PAYLOAD_PACKETS;     /**< IPv4 Datagrams Received with No Payload, offset: 0x818 */
  __I  uint32_t MAC_RXIPV4_FRAGMENTED_PACKETS;     /**< IPv4 Datagrams Received with Fragmentation, offset: 0x81C */
  __I  uint32_t MAC_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS; /**< IPv4 Datagrams Received with UDP Checksum Disabled, offset: 0x820 */
  __I  uint32_t MAC_RXIPV6_GOOD_PACKETS;           /**< Good IPv6 Datagrams Received, offset: 0x824 */
  __I  uint32_t MAC_RXIPV6_HEADER_ERROR_PACKETS;   /**< IPv6 Datagrams Received with Header Errors, offset: 0x828 */
  __I  uint32_t MAC_RXIPV6_NO_PAYLOAD_PACKETS;     /**< IPv6 Datagrams Received with No Payload, offset: 0x82C */
  __I  uint32_t MAC_RXUDP_GOOD_PACKETS;            /**< IPv6 Datagrams Received with Good UDP, offset: 0x830 */
  __I  uint32_t MAC_RXUDP_ERROR_PACKETS;           /**< IPv6 Datagrams Received with UDP Checksum Error, offset: 0x834 */
  __I  uint32_t MAC_RXTCP_GOOD_PACKETS;            /**< IPv6 Datagrams Received with Good TCP Payload, offset: 0x838 */
  __I  uint32_t MAC_RXTCP_ERROR_PACKETS;           /**< IPv6 Datagrams Received with TCP Checksum Error, offset: 0x83C */
  __I  uint32_t MAC_RXICMP_GOOD_PACKETS;           /**< IPv6 Datagrams Received with Good ICMP Payload, offset: 0x840 */
  __I  uint32_t MAC_RXICMP_ERROR_PACKETS;          /**< IPv6 Datagrams Received with ICMP Checksum Error, offset: 0x844 */
       uint8_t RESERVED_19[8];
  __I  uint32_t MAC_RXIPV4_GOOD_OCTETS;            /**< Good Bytes Received in IPv4 Datagrams, offset: 0x850 */
  __I  uint32_t MAC_RXIPV4_HEADER_ERROR_OCTETS;    /**< Bytes Received in IPv4 Datagrams with Header Errors, offset: 0x854 */
  __I  uint32_t MAC_RXIPV4_NO_PAYLOAD_OCTETS;      /**< Bytes Received in IPv4 Datagrams with No Payload, offset: 0x858 */
  __I  uint32_t MAC_RXIPV4_FRAGMENTED_OCTETS;      /**< Bytes Received in Fragmented IPv4 Datagrams, offset: 0x85C */
  __I  uint32_t MAC_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS; /**< Bytes Received with UDP Checksum Disabled, offset: 0x860 */
  __I  uint32_t MAC_RXIPV6_GOOD_OCTETS;            /**< Bytes Received in Good IPv6 Datagrams, offset: 0x864 */
  __I  uint32_t MAC_RXIPV6_HEADER_ERROR_OCTETS;    /**< Bytes Received in IPv6 Datagrams with Data Errors, offset: 0x868 */
  __I  uint32_t MAC_RXIPV6_NO_PAYLOAD_OCTETS;      /**< Bytes Received in IPv6 Datagrams with No Payload, offset: 0x86C */
  __I  uint32_t MAC_RXUDP_GOOD_OCTETS;             /**< Bytes Received in Good UDP Segment, offset: 0x870 */
  __I  uint32_t MAC_RXUDP_ERROR_OCTETS;            /**< Bytes Received in UDP Segment with Checksum Errors, offset: 0x874 */
  __I  uint32_t MAC_RXTCP_GOOD_OCTETS;             /**< Bytes Received in Good TCP Segment, offset: 0x878 */
  __I  uint32_t MAC_RXTCP_ERROR_OCTETS;            /**< Bytes Received in TCP Segment with Checksum Errors, offset: 0x87C */
  __I  uint32_t MAC_RXICMP_GOOD_OCTETS;            /**< Bytes Received in Good ICMP Segment, offset: 0x880 */
  __I  uint32_t MAC_RXICMP_ERROR_OCTETS;           /**< Bytes Received in ICMP Segment with Checksum Errors, offset: 0x884 */
       uint8_t RESERVED_20[24];
  __I  uint32_t MAC_MMC_FPE_TX_INTERRUPT;          /**< MMC FPE Transmit Interrupt, offset: 0x8A0 */
  __IO uint32_t MAC_MMC_FPE_TX_INTERRUPT_MASK;     /**< MMC FPE Transmit Mask Interrupt, offset: 0x8A4 */
  __I  uint32_t MAC_MMC_TX_FPE_FRAGMENT_CNTR;      /**< MMC FPE Transmitted Fragment Counter, offset: 0x8A8 */
  __I  uint32_t MAC_MMC_TX_HOLD_REQ_CNTR;          /**< MMC FPE Transmitted Hold Request Counter, offset: 0x8AC */
       uint8_t RESERVED_21[16];
  __I  uint32_t MAC_MMC_FPE_RX_INTERRUPT;          /**< MMC FPE Receive Interrupt, offset: 0x8C0 */
  __IO uint32_t MAC_MMC_FPE_RX_INTERRUPT_MASK;     /**< MMC FPE Receive Interrupt Mask, offset: 0x8C4 */
  __I  uint32_t MAC_MMC_RX_PACKET_ASSEMBLY_ERR_CNTR; /**< MMC Receive Packet Reassembly Error Counter, offset: 0x8C8 */
  __I  uint32_t MAC_MMC_RX_PACKET_SMD_ERR_CNTR;    /**< MMC Receive Packet SMD Error Counter, offset: 0x8CC */
  __I  uint32_t MAC_MMC_RX_PACKET_ASSEMBLY_OK_CNTR; /**< MMC Receive Packet Successful Reassembly Counter, offset: 0x8D0 */
  __I  uint32_t MAC_MMC_RX_FPE_FRAGMENT_CNTR;      /**< MMC FPE Received Fragment Counter, offset: 0x8D4 */
       uint8_t RESERVED_22[40];
  __IO uint32_t MAC_L3_L4_CONTROL0;                /**< Layer 3 and Layer 4 Control of Filter 0, offset: 0x900 */
  __IO uint32_t MAC_LAYER4_ADDRESS0;               /**< Layer 4 Address 0, offset: 0x904 */
       uint8_t RESERVED_23[8];
  __IO uint32_t MAC_LAYER3_ADDR0_REG0;             /**< Layer 3 Address 0 Register 0, offset: 0x910 */
  __IO uint32_t MAC_LAYER3_ADDR1_REG0;             /**< Layer 3 Address 1 Register 0, offset: 0x914 */
  __IO uint32_t MAC_LAYER3_ADDR2_REG0;             /**< Layer 3 Address 2 Register 0, offset: 0x918 */
  __IO uint32_t MAC_LAYER3_ADDR3_REG0;             /**< Layer 3 Address 3 Register 0, offset: 0x91C */
       uint8_t RESERVED_24[16];
  __IO uint32_t MAC_L3_L4_CONTROL1;                /**< Layer 3 and Layer 4 Control of Filter 1, offset: 0x930 */
  __IO uint32_t MAC_LAYER4_ADDRESS1;               /**< Layer 4 Address 0, offset: 0x934 */
       uint8_t RESERVED_25[8];
  __IO uint32_t MAC_LAYER3_ADDR0_REG1;             /**< Layer 3 Address 0 Register 1, offset: 0x940 */
  __IO uint32_t MAC_LAYER3_ADDR1_REG1;             /**< Layer 3 Address 1 Register 1, offset: 0x944 */
  __IO uint32_t MAC_LAYER3_ADDR2_REG1;             /**< Layer 3 Address 2 Register 1, offset: 0x948 */
  __IO uint32_t MAC_LAYER3_ADDR3_REG1;             /**< Layer 3 Address 3 Register 1, offset: 0x94C */
       uint8_t RESERVED_26[16];
  __IO uint32_t MAC_L3_L4_CONTROL2;                /**< Layer 3 and Layer 4 Control of Filter 2, offset: 0x960 */
  __IO uint32_t MAC_LAYER4_ADDRESS2;               /**< Layer 4 Address 2, offset: 0x964 */
       uint8_t RESERVED_27[8];
  __IO uint32_t MAC_LAYER3_ADDR0_REG2;             /**< Layer 3 Address 0 Register 2, offset: 0x970 */
  __IO uint32_t MAC_LAYER3_ADDR1_REG2;             /**< Layer 3 Address 0 Register 2, offset: 0x974 */
  __IO uint32_t MAC_LAYER3_ADDR2_REG2;             /**< Layer 3 Address 2 Register 2, offset: 0x978 */
  __IO uint32_t MAC_LAYER3_ADDR3_REG2;             /**< Layer 3 Address 3 Register 2, offset: 0x97C */
       uint8_t RESERVED_28[16];
  __IO uint32_t MAC_L3_L4_CONTROL3;                /**< Layer 3 and Layer 4 Control of Filter 3, offset: 0x990 */
  __IO uint32_t MAC_LAYER4_ADDRESS3;               /**< Layer 4 Address 3, offset: 0x994 */
       uint8_t RESERVED_29[8];
  __IO uint32_t MAC_LAYER3_ADDR0_REG3;             /**< Layer 3 Address 0 Register 3, offset: 0x9A0 */
  __IO uint32_t MAC_LAYER3_ADDR1_REG3;             /**< Layer 3 Address 1 Register 3, offset: 0x9A4 */
  __IO uint32_t MAC_LAYER3_ADDR2_REG3;             /**< Layer 3 Address 2 Register 3, offset: 0x9A8 */
  __IO uint32_t MAC_LAYER3_ADDR3_REG3;             /**< Layer 3 Address 3 Register 3, offset: 0x9AC */
       uint8_t RESERVED_30[16];
  __IO uint32_t MAC_L3_L4_CONTROL4;                /**< Layer 3 and Layer 4 Control of Filter 4, offset: 0x9C0 */
  __IO uint32_t MAC_LAYER4_ADDRESS4;               /**< Layer 4 Address 4, offset: 0x9C4 */
       uint8_t RESERVED_31[8];
  __IO uint32_t MAC_LAYER3_ADDR0_REG4;             /**< Layer 3 Address 0 Register 4, offset: 0x9D0 */
  __IO uint32_t MAC_LAYER3_ADDR1_REG4;             /**< Layer 3 Address 1 Register 4, offset: 0x9D4 */
  __IO uint32_t MAC_LAYER3_ADDR2_REG4;             /**< Layer 3 Address 2 Register 4, offset: 0x9D8 */
  __IO uint32_t MAC_LAYER3_ADDR3_REG4;             /**< Layer 3 Address 3 Register 4, offset: 0x9DC */
       uint8_t RESERVED_32[16];
  __IO uint32_t MAC_L3_L4_CONTROL5;                /**< Layer 3 and Layer 4 Control of Filter 5, offset: 0x9F0 */
  __IO uint32_t MAC_LAYER4_ADDRESS5;               /**< Layer 4 Address 5, offset: 0x9F4 */
       uint8_t RESERVED_33[8];
  __IO uint32_t MAC_LAYER3_ADDR0_REG5;             /**< Layer 3 Address 0 Register 5, offset: 0xA00 */
  __IO uint32_t MAC_LAYER3_ADDR1_REG5;             /**< Layer 3 Address 1 Register 5, offset: 0xA04 */
  __IO uint32_t MAC_LAYER3_ADDR2_REG5;             /**< Layer 3 Address 2 Register 5, offset: 0xA08 */
  __IO uint32_t MAC_LAYER3_ADDR3_REG5;             /**< Layer 3 Address 3 Register 5, offset: 0xA0C */
       uint8_t RESERVED_34[16];
  __IO uint32_t MAC_L3_L4_CONTROL6;                /**< Layer 3 and Layer 4 Control of Filter 6, offset: 0xA20 */
  __IO uint32_t MAC_LAYER4_ADDRESS6;               /**< Layer 4 Address 6, offset: 0xA24 */
       uint8_t RESERVED_35[8];
  __IO uint32_t MAC_LAYER3_ADDR0_REG6;             /**< Layer 3 Address 0 Register 6, offset: 0xA30 */
  __IO uint32_t MAC_LAYER3_ADDR1_REG6;             /**< Layer 3 Address 1 Register 6, offset: 0xA34 */
  __IO uint32_t MAC_LAYER3_ADDR2_REG6;             /**< Layer 3 Address 2 Register 6, offset: 0xA38 */
  __IO uint32_t MAC_LAYER3_ADDR3_REG6;             /**< Layer 3 Address 3 Register 6, offset: 0xA3C */
       uint8_t RESERVED_36[16];
  __IO uint32_t MAC_L3_L4_CONTROL7;                /**< Layer 3 and Layer 4 Control of Filter 0, offset: 0xA50 */
  __IO uint32_t MAC_LAYER4_ADDRESS7;               /**< Layer 4 Address 7, offset: 0xA54 */
       uint8_t RESERVED_37[8];
  __IO uint32_t MAC_LAYER3_ADDR0_REG7;             /**< Layer 3 Address 0 Register 7, offset: 0xA60 */
  __IO uint32_t MAC_LAYER3_ADDR1_REG7;             /**< Layer 3 Address 1 Register 7, offset: 0xA64 */
  __IO uint32_t MAC_LAYER3_ADDR2_REG7;             /**< Layer 3 Address 2 Register 7, offset: 0xA68 */
  __IO uint32_t MAC_LAYER3_ADDR3_REG7;             /**< Layer 3 Address 3 Register 7, offset: 0xA6C */
  __IO uint32_t MAC_INDIR_ACCESS_CTRL;             /**< MAC_INDIR_ACCESS_CTRL, offset: 0xA70 */
  __IO uint32_t MAC_INDIR_ACCESS_DATA;             /**< MAC_INDIR_ACCESS_DATA, offset: 0xA74 */
       uint8_t RESERVED_38[136];
  __IO uint32_t MAC_TIMESTAMP_CONTROL;             /**< Timestamp Control, offset: 0xB00 */
  __IO uint32_t MAC_SUB_SECOND_INCREMENT;          /**< Subsecond Increment, offset: 0xB04 */
  __I  uint32_t MAC_SYSTEM_TIME_SECONDS;           /**< System Time Seconds, offset: 0xB08 */
  __I  uint32_t MAC_SYSTEM_TIME_NANOSECONDS;       /**< System Time Nanoseconds, offset: 0xB0C */
  __IO uint32_t MAC_SYSTEM_TIME_SECONDS_UPDATE;    /**< System Time Seconds Update, offset: 0xB10 */
  __IO uint32_t MAC_SYSTEM_TIME_NANOSECONDS_UPDATE; /**< System Time Nanoseconds Update, offset: 0xB14 */
  __IO uint32_t MAC_TIMESTAMP_ADDEND;              /**< Timestamp Addend, offset: 0xB18 */
  __IO uint32_t MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS; /**< System Time - Higher Word Seconds, offset: 0xB1C */
  __I  uint32_t MAC_TIMESTAMP_STATUS;              /**< Timestamp Status, offset: 0xB20 */
       uint8_t RESERVED_39[12];
  __I  uint32_t MAC_TX_TIMESTAMP_STATUS_NANOSECONDS; /**< Transmit Timestamp Status Nanoseconds, offset: 0xB30 */
  __I  uint32_t MAC_TX_TIMESTAMP_STATUS_SECONDS;   /**< Transmit Timestamp Status Seconds, offset: 0xB34 */
       uint8_t RESERVED_40[8];
  __IO uint32_t MAC_AUXILIARY_CONTROL;             /**< Auxiliary Timestamp Control, offset: 0xB40 */
       uint8_t RESERVED_41[4];
  __I  uint32_t MAC_AUXILIARY_TIMESTAMP_NANOSECONDS; /**< Auxiliary Timestamp Nanoseconds, offset: 0xB48 */
  __I  uint32_t MAC_AUXILIARY_TIMESTAMP_SECONDS;   /**< Auxiliary Timestamp Seconds, offset: 0xB4C */
  __IO uint32_t MAC_TIMESTAMP_INGRESS_ASYM_CORR;   /**< Timestamp Ingress Asymmetry Correction, offset: 0xB50 */
  __IO uint32_t MAC_TIMESTAMP_EGRESS_ASYM_CORR;    /**< Timestamp Egress Asymmetry Correction, offset: 0xB54 */
  __IO uint32_t MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND; /**< Timestamp Ingress Correction Nanosecond, offset: 0xB58 */
  __IO uint32_t MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND; /**< Timestamp Egress Correction Nanosecond, offset: 0xB5C */
  __IO uint32_t MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC; /**< Timestamp Ingress Correction Subnanosecond, offset: 0xB60 */
  __IO uint32_t MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC; /**< Timestamp Egress Correction Subnanosecond, offset: 0xB64 */
  __I  uint32_t MAC_TIMESTAMP_INGRESS_LATENCY;     /**< Timestamp Ingress Latency, offset: 0xB68 */
  __I  uint32_t MAC_TIMESTAMP_EGRESS_LATENCY;      /**< Timestamp Egress Latency, offset: 0xB6C */
  __IO uint32_t MAC_PPS_CONTROL;                   /**< PPS Control, offset: 0xB70 */
       uint8_t RESERVED_42[12];
  __IO uint32_t MAC_PPS0_TARGET_TIME_SECONDS;      /**< PPS0 Target Time Seconds, offset: 0xB80 */
  __IO uint32_t MAC_PPS0_TARGET_TIME_NANOSECONDS;  /**< PPS0 Target Time Nanoseconds, offset: 0xB84 */
  __IO uint32_t MAC_PPS0_INTERVAL;                 /**< PPS0 Interval, offset: 0xB88 */
  __IO uint32_t MAC_PPS0_WIDTH;                    /**< PPS0 Width, offset: 0xB8C */
  __IO uint32_t MAC_PPS1_TARGET_TIME_SECONDS;      /**< PPS1 Target Time Seconds, offset: 0xB90 */
  __IO uint32_t MAC_PPS1_TARGET_TIME_NANOSECONDS;  /**< PPS1 Target Time Nanoseconds, offset: 0xB94 */
  __IO uint32_t MAC_PPS1_INTERVAL;                 /**< PPS1 Interval, offset: 0xB98 */
  __IO uint32_t MAC_PPS1_WIDTH;                    /**< PPS1 Width, offset: 0xB9C */
  __IO uint32_t MAC_PPS2_TARGET_TIME_SECONDS;      /**< PPS2 Target Time Seconds, offset: 0xBA0 */
  __IO uint32_t MAC_PPS2_TARGET_TIME_NANOSECONDS;  /**< PPS2 Target Time Nanoseconds, offset: 0xBA4 */
  __IO uint32_t MAC_PPS2_INTERVAL;                 /**< PPS2 Interval, offset: 0xBA8 */
  __IO uint32_t MAC_PPS2_WIDTH;                    /**< PPS2 Width, offset: 0xBAC */
  __IO uint32_t MAC_PPS3_TARGET_TIME_SECONDS;      /**< PPS3 Target Time Seconds, offset: 0xBB0 */
  __IO uint32_t MAC_PPS3_TARGET_TIME_NANOSECONDS;  /**< PPS3 Target Time Nanoseconds, offset: 0xBB4 */
  __IO uint32_t MAC_PPS3_INTERVAL;                 /**< PPS3 Interval, offset: 0xBB8 */
  __IO uint32_t MAC_PPS3_WIDTH;                    /**< PPS3 Width, offset: 0xBBC */
  __IO uint32_t MAC_PTO_CONTROL;                   /**< PTP Offload Engine Control, offset: 0xBC0 */
  __IO uint32_t MAC_SOURCE_PORT_IDENTITY0;         /**< Source Port Identity 0, offset: 0xBC4 */
  __IO uint32_t MAC_SOURCE_PORT_IDENTITY1;         /**< Source Port Identity 1, offset: 0xBC8 */
  __IO uint32_t MAC_SOURCE_PORT_IDENTITY2;         /**< Source Port Identity 2, offset: 0xBCC */
  __IO uint32_t MAC_LOG_MESSAGE_INTERVAL;          /**< Log Message Interval, offset: 0xBD0 */
       uint8_t RESERVED_43[44];
  __IO uint32_t MTL_OPERATION_MODE;                /**< MTL Operation Mode, offset: 0xC00 */
       uint8_t RESERVED_44[4];
  __IO uint32_t MTL_DBG_CTL;                       /**< FIFO Debug Access Control and Status, offset: 0xC08 */
  __IO uint32_t MTL_DBG_STS;                       /**< FIFO Debug Status, offset: 0xC0C */
  __IO uint32_t MTL_FIFO_DEBUG_DATA;               /**< FIFO Debug Data, offset: 0xC10 */
       uint8_t RESERVED_45[12];
  __I  uint32_t MTL_INTERRUPT_STATUS;              /**< MTL Interrupt Status, offset: 0xC20 */
       uint8_t RESERVED_46[12];
  __IO uint32_t MTL_RXQ_DMA_MAP0;                  /**< Receive Queue and DMA Channel Mapping 0, offset: 0xC30 */
  __IO uint32_t MTL_RXQ_DMA_MAP1;                  /**< Receive Queue and DMA Channel Mapping 1, offset: 0xC34 */
       uint8_t RESERVED_47[8];
  __IO uint32_t MTL_TBS_CTRL;                      /**< Time Based Scheduling Control, offset: 0xC40 */
       uint8_t RESERVED_48[12];
  __IO uint32_t MTL_EST_CONTROL;                   /**< Enhancements to Scheduled Transmission Control, offset: 0xC50 */
  __IO uint32_t MTL_EST_EXT_CONTROL;               /**< MTL_EST_EXT_CONTROL, offset: 0xC54 */
  __IO uint32_t MTL_EST_STATUS;                    /**< Enhancements to Scheduled Transmission Status, offset: 0xC58 */
       uint8_t RESERVED_49[4];
  __IO uint32_t MTL_EST_SCH_ERROR;                 /**< EST Scheduling Error, offset: 0xC60 */
  __IO uint32_t MTL_EST_FRM_SIZE_ERROR;            /**< EST Frame Size Error, offset: 0xC64 */
  __I  uint32_t MTL_EST_FRM_SIZE_CAPTURE;          /**< EST Frame Size Capture, offset: 0xC68 */
       uint8_t RESERVED_50[4];
  __IO uint32_t MTL_EST_INTR_ENABLE;               /**< EST Interrupt Enable, offset: 0xC70 */
       uint8_t RESERVED_51[12];
  __IO uint32_t MTL_EST_GCL_CONTROL;               /**< EST GCL Control, offset: 0xC80 */
  __IO uint32_t MTL_EST_GCL_DATA;                  /**< EST GCL Data, offset: 0xC84 */
       uint8_t RESERVED_52[8];
  __IO uint32_t MTL_FPE_CTRL_STS;                  /**< Frame Preemption Control and Status, offset: 0xC90 */
  __IO uint32_t MTL_FPE_ADVANCE;                   /**< Frame Preemption Hold and Release Advance, offset: 0xC94 */
       uint8_t RESERVED_53[8];
  __IO uint32_t MTL_RXP_CONTROL_STATUS;            /**< RXP Control Status, offset: 0xCA0 */
  __IO uint32_t MTL_RXP_INTERRUPT_CONTROL_STATUS;  /**< RXP Interrupt Control Status, offset: 0xCA4 */
  __I  uint32_t MTL_RXP_DROP_CNT;                  /**< RXP Drop Count, offset: 0xCA8 */
  __I  uint32_t MTL_RXP_ERROR_CNT;                 /**< RXP Error Count, offset: 0xCAC */
  __IO uint32_t MTL_RXP_INDIRECT_ACC_CONTROL_STATUS; /**< RXP Indirect Access Control and Status, offset: 0xCB0 */
  __IO uint32_t MTL_RXP_INDIRECT_ACC_DATA;         /**< RXP Indirect Access Data, offset: 0xCB4 */
  __I  uint32_t MTL_RXP_BYPASS_CNT;                /**< MTL_RXP_BYPASS_CNT, offset: 0xCB8 */
       uint8_t RESERVED_54[68];
  struct {                                         /* offset: 0xD00, array step: 0x40 */
    __IO uint32_t MTL_TXQX_OP_MODE;                  /**< Queue 0 Transmit Operation Mode..Queue 4 Transmit Operation Mode, array offset: 0xD00, array step: 0x40 */
    __I  uint32_t MTL_TXQX_UNDRFLW;                  /**< Queue 0 Underflow Counter..Queue 4 Underflow Counter, array offset: 0xD04, array step: 0x40 */
    __I  uint32_t MTL_TXQX_DBG;                      /**< Queue 0 Transmit Debug..Queue 4 Transmit Debug, array offset: 0xD08, array step: 0x40 */
         uint8_t RESERVED_0[4];
    __IO uint32_t MTL_TXQX_ETS_CTRL;                 /**< Queue 1 ETS Control..Queue 4 ETS Control, array offset: 0xD10, array step: 0x40, valid indices: [1-4] */
    __I  uint32_t MTL_TXQX_ETS_STAT;                 /**< Queue 0 ETS Status..Queue 4 ETS Status, array offset: 0xD14, array step: 0x40 */
    __IO uint32_t MTL_TXQX_QNTM_WGHT;                /**< Queue 0 Quantum or Weights..Queue 4 idleSlopeCredit, Quantum or Weights, array offset: 0xD18, array step: 0x40 */
    __IO uint32_t MTL_TXQX_SNDSLP_CRDT;              /**< Queue 1 sendSlopeCredit..Queue 4 sendSlopeCredit, array offset: 0xD1C, array step: 0x40, valid indices: [1-4] */
    __IO uint32_t MTL_TXQX_HI_CRDT;                  /**< Queue 1 hiCredit..Queue 4 hiCredit, array offset: 0xD20, array step: 0x40, valid indices: [1-4] */
    __IO uint32_t MTL_TXQX_LO_CRDT;                  /**< Queue 1 loCredit..Queue 4 loCredit, array offset: 0xD24, array step: 0x40, valid indices: [1-4] */
         uint8_t RESERVED_1[4];
    __IO uint32_t MTL_TXQX_INTCTRL_STAT;             /**< Queue 0 Interrupt Control Status..Queue 4 Interrupt Control Status, array offset: 0xD2C, array step: 0x40 */
    __IO uint32_t MTL_RXQX_OP_MODE;                  /**< Queue 0 Receive Operation Mode..Queue 4 Receive Operation Mode, array offset: 0xD30, array step: 0x40 */
    __I  uint32_t MTL_RXQX_MISSPKT_OVRFLW_CNT;       /**< Queue 0 Missed Packet and Overflow Counter..Queue 4 Missed Packet and Overflow Counter, array offset: 0xD34, array step: 0x40 */
    __I  uint32_t MTL_RXQX_DBG;                      /**< Queue 0 Receive Debug..Queue 4 Receive Debug, array offset: 0xD38, array step: 0x40 */
    __IO uint32_t MTL_RXQX_CTRL;                     /**< Queue 0 Receive Control..Queue 4 Receive Control, array offset: 0xD3C, array step: 0x40 */
  } MTL_QUEUE[ENET_QOS_MTL_QUEUE_COUNT];
       uint8_t RESERVED_55[448];
  __IO uint32_t DMA_MODE;                          /**< DMA Bus Mode, offset: 0x1000 */
  __IO uint32_t DMA_SYSBUS_MODE;                   /**< DMA System Bus Mode, offset: 0x1004 */
  __I  uint32_t DMA_INTERRUPT_STATUS;              /**< DMA Interrupt Status, offset: 0x1008 */
  __I  uint32_t DMA_DEBUG_STATUS0;                 /**< DMA Debug Status 0, offset: 0x100C */
  __I  uint32_t DMA_DEBUG_STATUS1;                 /**< DMA Debug Status 1, offset: 0x1010 */
       uint8_t RESERVED_56[44];
  __IO uint32_t DMA_AXI_LPI_ENTRY_INTERVAL;        /**< AXI LPI Entry Interval Control, offset: 0x1040 */
       uint8_t RESERVED_57[12];
  __IO uint32_t DMA_TBS_CTRL0;                     /**< DMA_TBS_CTRL0, offset: 0x1050 */
  __IO uint32_t DMA_TBS_CTRL1;                     /**< DMA_TBS_CTRL1, offset: 0x1054 */
  __IO uint32_t DMA_TBS_CTRL2;                     /**< DMA_TBS_CTRL2, offset: 0x1058 */
  __IO uint32_t DMA_TBS_CTRL3;                     /**< DMA_TBS_CTRL3, offset: 0x105C */
       uint8_t RESERVED_58[160];
  struct {                                         /* offset: 0x1100, array step: 0x80 */
    __IO uint32_t DMA_CHX_CTRL;                      /**< DMA Channel 0 Control..Channel 4 Control, array offset: 0x1100, array step: 0x80 */
    __IO uint32_t DMA_CHX_TX_CTRL;                   /**< DMA Channel 0 Transmit Control..DMA Channel 4 Transmit Control, array offset: 0x1104, array step: 0x80 */
    __IO uint32_t DMA_CHX_RX_CTRL;                   /**< DMA Channel 0 Receive Control..DMA Channel 4 Receive Control, array offset: 0x1108, array step: 0x80 */
         uint8_t RESERVED_0[8];
    __IO uint32_t DMA_CHX_TXDESC_LIST_ADDR;          /**< Channel 0 Tx Descriptor List Address register..Channel 4 Tx Descriptor List Address, array offset: 0x1114, array step: 0x80 */
         uint8_t RESERVED_1[4];
    __IO uint32_t DMA_CHX_RXDESC_LIST_ADDR;          /**< Channel 0 Rx Descriptor List Address register..Channel 4 Rx Descriptor List Address, array offset: 0x111C, array step: 0x80 */
    __IO uint32_t DMA_CHX_TXDESC_TAIL_PTR;           /**< Channel 0 Tx Descriptor Tail Pointer..Channel 4 Tx Descriptor Tail Pointer, array offset: 0x1120, array step: 0x80 */
         uint8_t RESERVED_2[4];
    __IO uint32_t DMA_CHX_RXDESC_TAIL_PTR;           /**< Channel 0 Rx Descriptor Tail Pointer..Channel 4 Rx Descriptor Tail Pointer, array offset: 0x1128, array step: 0x80 */
    __IO uint32_t DMA_CHX_TXDESC_RING_LENGTH;        /**< Channel 0 Tx Descriptor Ring Length..Channel 4 Tx Descriptor Ring Length, array offset: 0x112C, array step: 0x80 */
    __IO uint32_t DMA_CHX_RX_CONTROL2;               /**< Channel 0 Receive Control 2 register..DMA Channel 4 Receive Control 2 register, array offset: 0x1130, array step: 0x80 */
    __IO uint32_t DMA_CHX_INT_EN;                    /**< Channel 0 Interrupt Enable..Channel 4 Interrupt Enable, array offset: 0x1134, array step: 0x80 */
    __IO uint32_t DMA_CHX_RX_INT_WDTIMER;            /**< Channel 0 Receive Interrupt Watchdog Timer..Channel 4 Receive Interrupt Watchdog Timer, array offset: 0x1138, array step: 0x80 */
    __IO uint32_t DMA_CHX_SLOT_FUNC_CTRL_STAT;       /**< Channel 0 Slot Function Control and Status..Channel 4 Slot Function Control and Status, array offset: 0x113C, array step: 0x80 */
         uint8_t RESERVED_3[4];
    __I  uint32_t DMA_CHX_CUR_HST_TXDESC;            /**< Channel 0 Current Application Transmit Descriptor..Channel 4 Current Application Transmit Descriptor, array offset: 0x1144, array step: 0x80 */
         uint8_t RESERVED_4[4];
    __I  uint32_t DMA_CHX_CUR_HST_RXDESC;            /**< Channel 0 Current Application Receive Descriptor..Channel 4 Current Application Receive Descriptor, array offset: 0x114C, array step: 0x80 */
         uint8_t RESERVED_5[4];
    __I  uint32_t DMA_CHX_CUR_HST_TXBUF;             /**< Channel 0 Current Application Transmit Buffer Address..Channel 4 Current Application Transmit Buffer Address, array offset: 0x1154, array step: 0x80 */
         uint8_t RESERVED_6[4];
    __I  uint32_t DMA_CHX_CUR_HST_RXBUF;             /**< Channel 0 Current Application Receive Buffer Address..Channel 4 Current Application Receive Buffer Address, array offset: 0x115C, array step: 0x80 */
    __IO uint32_t DMA_CHX_STAT;                      /**< DMA Channel 0 Status..DMA Channel 4 Status, array offset: 0x1160, array step: 0x80 */
    __I  uint32_t DMA_CHX_MISS_FRAME_CNT;            /**< Channel 0 Missed Frame Counter..Channel 4 Missed Frame Counter, array offset: 0x1164, array step: 0x80 */
    __I  uint32_t DMA_CHX_RXP_ACCEPT_CNT;            /**< Channel 0 RXP Frames Accepted Counter..Channel 4 RXP Frames Accepted Counter, array offset: 0x1168, array step: 0x80 */
         uint8_t RESERVED_7[20];
  } DMA_CH[ENET_QOS_DMA_CH_COUNT];
} ENET_QOS_Type;

/* ----------------------------------------------------------------------------
   -- ENET_QOS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ENET_QOS_Register_Masks ENET_QOS Register Masks
 * @{
 */

/*! @name MAC_CONFIGURATION - MAC Configuration Register */
/*! @{ */

#define ENET_QOS_MAC_CONFIGURATION_RE_MASK       (0x1U)
#define ENET_QOS_MAC_CONFIGURATION_RE_SHIFT      (0U)
/*! RE - Receiver Enable
 *  0b0..Receiver is disabled
 *  0b1..Receiver is enabled
 */
#define ENET_QOS_MAC_CONFIGURATION_RE(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_RE_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_RE_MASK)

#define ENET_QOS_MAC_CONFIGURATION_TE_MASK       (0x2U)
#define ENET_QOS_MAC_CONFIGURATION_TE_SHIFT      (1U)
/*! TE - Transmitter Enable
 *  0b0..Transmitter is disabled
 *  0b1..Transmitter is enabled
 */
#define ENET_QOS_MAC_CONFIGURATION_TE(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_TE_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_TE_MASK)

#define ENET_QOS_MAC_CONFIGURATION_PRELEN_MASK   (0xCU)
#define ENET_QOS_MAC_CONFIGURATION_PRELEN_SHIFT  (2U)
/*! PRELEN - Preamble Length for Transmit packets
 *  0b00..7 bytes of preamble
 *  0b01..5 bytes of preamble
 *  0b10..3 bytes of preamble
 *  0b11..Reserved
 */
#define ENET_QOS_MAC_CONFIGURATION_PRELEN(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_PRELEN_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_PRELEN_MASK)

#define ENET_QOS_MAC_CONFIGURATION_DC_MASK       (0x10U)
#define ENET_QOS_MAC_CONFIGURATION_DC_SHIFT      (4U)
/*! DC - Deferral Check
 *  0b0..Deferral check function is disabled
 *  0b1..Deferral check function is enabled
 */
#define ENET_QOS_MAC_CONFIGURATION_DC(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_DC_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_DC_MASK)

#define ENET_QOS_MAC_CONFIGURATION_BL_MASK       (0x60U)
#define ENET_QOS_MAC_CONFIGURATION_BL_SHIFT      (5U)
/*! BL - Back-Off Limit
 *  0b00..k = min(n,10)
 *  0b01..k = min(n,8)
 *  0b10..k = min(n,4)
 *  0b11..k = min(n,1)
 */
#define ENET_QOS_MAC_CONFIGURATION_BL(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_BL_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_BL_MASK)

#define ENET_QOS_MAC_CONFIGURATION_DR_MASK       (0x100U)
#define ENET_QOS_MAC_CONFIGURATION_DR_SHIFT      (8U)
/*! DR - Disable Retry
 *  0b0..Enable Retry
 *  0b1..Disable Retry
 */
#define ENET_QOS_MAC_CONFIGURATION_DR(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_DR_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_DR_MASK)

#define ENET_QOS_MAC_CONFIGURATION_DCRS_MASK     (0x200U)
#define ENET_QOS_MAC_CONFIGURATION_DCRS_SHIFT    (9U)
/*! DCRS - Disable Carrier Sense During Transmission
 *  0b0..Enable Carrier Sense During Transmission
 *  0b1..Disable Carrier Sense During Transmission
 */
#define ENET_QOS_MAC_CONFIGURATION_DCRS(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_DCRS_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_DCRS_MASK)

#define ENET_QOS_MAC_CONFIGURATION_DO_MASK       (0x400U)
#define ENET_QOS_MAC_CONFIGURATION_DO_SHIFT      (10U)
/*! DO - Disable Receive Own
 *  0b0..Enable Receive Own
 *  0b1..Disable Receive Own
 */
#define ENET_QOS_MAC_CONFIGURATION_DO(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_DO_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_DO_MASK)

#define ENET_QOS_MAC_CONFIGURATION_ECRSFD_MASK   (0x800U)
#define ENET_QOS_MAC_CONFIGURATION_ECRSFD_SHIFT  (11U)
/*! ECRSFD - Enable Carrier Sense Before Transmission in Full-Duplex Mode
 *  0b0..ECRSFD is disabled
 *  0b1..ECRSFD is enabled
 */
#define ENET_QOS_MAC_CONFIGURATION_ECRSFD(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_ECRSFD_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_ECRSFD_MASK)

#define ENET_QOS_MAC_CONFIGURATION_LM_MASK       (0x1000U)
#define ENET_QOS_MAC_CONFIGURATION_LM_SHIFT      (12U)
/*! LM - Loopback Mode
 *  0b0..Loopback is disabled
 *  0b1..Loopback is enabled
 */
#define ENET_QOS_MAC_CONFIGURATION_LM(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_LM_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_LM_MASK)

#define ENET_QOS_MAC_CONFIGURATION_DM_MASK       (0x2000U)
#define ENET_QOS_MAC_CONFIGURATION_DM_SHIFT      (13U)
/*! DM - Duplex Mode
 *  0b0..Half-duplex mode
 *  0b1..Full-duplex mode
 */
#define ENET_QOS_MAC_CONFIGURATION_DM(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_DM_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_DM_MASK)

#define ENET_QOS_MAC_CONFIGURATION_FES_MASK      (0x4000U)
#define ENET_QOS_MAC_CONFIGURATION_FES_SHIFT     (14U)
/*! FES - Speed
 *  0b0..10 Mbps when PS bit is 1 and 1 Gbps when PS bit is 0
 *  0b1..100 Mbps when PS bit is 1 and 2.5 Gbps when PS bit is 0
 */
#define ENET_QOS_MAC_CONFIGURATION_FES(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_FES_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_FES_MASK)

#define ENET_QOS_MAC_CONFIGURATION_PS_MASK       (0x8000U)
#define ENET_QOS_MAC_CONFIGURATION_PS_SHIFT      (15U)
/*! PS - Port Select
 *  0b0..For 1000 or 2500 Mbps operations
 *  0b1..For 10 or 100 Mbps operations
 */
#define ENET_QOS_MAC_CONFIGURATION_PS(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_PS_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_PS_MASK)

#define ENET_QOS_MAC_CONFIGURATION_JE_MASK       (0x10000U)
#define ENET_QOS_MAC_CONFIGURATION_JE_SHIFT      (16U)
/*! JE - Jumbo Packet Enable When this bit is set, the MAC allows jumbo packets of 9,018 bytes
 *    (9,022 bytes for VLAN tagged packets) without reporting a giant packet error in the Rx packet
 *    status.
 *  0b0..Jumbo packet is disabled
 *  0b1..Jumbo packet is enabled
 */
#define ENET_QOS_MAC_CONFIGURATION_JE(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_JE_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_JE_MASK)

#define ENET_QOS_MAC_CONFIGURATION_JD_MASK       (0x20000U)
#define ENET_QOS_MAC_CONFIGURATION_JD_SHIFT      (17U)
/*! JD - Jabber Disable
 *  0b0..Jabber is enabled
 *  0b1..Jabber is disabled
 */
#define ENET_QOS_MAC_CONFIGURATION_JD(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_JD_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_JD_MASK)

#define ENET_QOS_MAC_CONFIGURATION_BE_MASK       (0x40000U)
#define ENET_QOS_MAC_CONFIGURATION_BE_SHIFT      (18U)
/*! BE - Packet Burst Enable When this bit is set, the MAC allows packet bursting during
 *    transmission in the GMII half-duplex mode.
 *  0b0..Packet Burst is disabled
 *  0b1..Packet Burst is enabled
 */
#define ENET_QOS_MAC_CONFIGURATION_BE(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_BE_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_BE_MASK)

#define ENET_QOS_MAC_CONFIGURATION_WD_MASK       (0x80000U)
#define ENET_QOS_MAC_CONFIGURATION_WD_SHIFT      (19U)
/*! WD - Watchdog Disable
 *  0b0..Watchdog is enabled
 *  0b1..Watchdog is disabled
 */
#define ENET_QOS_MAC_CONFIGURATION_WD(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_WD_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_WD_MASK)

#define ENET_QOS_MAC_CONFIGURATION_ACS_MASK      (0x100000U)
#define ENET_QOS_MAC_CONFIGURATION_ACS_SHIFT     (20U)
/*! ACS - Automatic Pad or CRC Stripping When this bit is set, the MAC strips the Pad or FCS field
 *    on the incoming packets only if the value of the length field is less than 1,536 bytes.
 *  0b0..Automatic Pad or CRC Stripping is disabled
 *  0b1..Automatic Pad or CRC Stripping is enabled
 */
#define ENET_QOS_MAC_CONFIGURATION_ACS(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_ACS_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_ACS_MASK)

#define ENET_QOS_MAC_CONFIGURATION_CST_MASK      (0x200000U)
#define ENET_QOS_MAC_CONFIGURATION_CST_SHIFT     (21U)
/*! CST - CRC stripping for Type packets When this bit is set, the last four bytes (FCS) of all
 *    packets of Ether type (type field greater than 1,536) are stripped and dropped before forwarding
 *    the packet to the application.
 *  0b0..CRC stripping for Type packets is disabled
 *  0b1..CRC stripping for Type packets is enabled
 */
#define ENET_QOS_MAC_CONFIGURATION_CST(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_CST_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_CST_MASK)

#define ENET_QOS_MAC_CONFIGURATION_S2KP_MASK     (0x400000U)
#define ENET_QOS_MAC_CONFIGURATION_S2KP_SHIFT    (22U)
/*! S2KP - IEEE 802.
 *  0b0..Support upto 2K packet is disabled
 *  0b1..Support upto 2K packet is Enabled
 */
#define ENET_QOS_MAC_CONFIGURATION_S2KP(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_S2KP_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_S2KP_MASK)

#define ENET_QOS_MAC_CONFIGURATION_GPSLCE_MASK   (0x800000U)
#define ENET_QOS_MAC_CONFIGURATION_GPSLCE_SHIFT  (23U)
/*! GPSLCE - Giant Packet Size Limit Control Enable
 *  0b0..Giant Packet Size Limit Control is disabled
 *  0b1..Giant Packet Size Limit Control is enabled
 */
#define ENET_QOS_MAC_CONFIGURATION_GPSLCE(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_GPSLCE_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_GPSLCE_MASK)

#define ENET_QOS_MAC_CONFIGURATION_IPG_MASK      (0x7000000U)
#define ENET_QOS_MAC_CONFIGURATION_IPG_SHIFT     (24U)
/*! IPG - Inter-Packet Gap These bits control the minimum IPG between packets during transmission.
 *  0b000..96 bit times IPG
 *  0b001..88 bit times IPG
 *  0b010..80 bit times IPG
 *  0b011..72 bit times IPG
 *  0b100..64 bit times IPG
 *  0b101..56 bit times IPG
 *  0b110..48 bit times IPG
 *  0b111..40 bit times IPG
 */
#define ENET_QOS_MAC_CONFIGURATION_IPG(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_IPG_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_IPG_MASK)

#define ENET_QOS_MAC_CONFIGURATION_IPC_MASK      (0x8000000U)
#define ENET_QOS_MAC_CONFIGURATION_IPC_SHIFT     (27U)
/*! IPC - Checksum Offload
 *  0b0..IP header/payload checksum checking is disabled
 *  0b1..IP header/payload checksum checking is enabled
 */
#define ENET_QOS_MAC_CONFIGURATION_IPC(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_IPC_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_IPC_MASK)

#define ENET_QOS_MAC_CONFIGURATION_SARC_MASK     (0x70000000U)
#define ENET_QOS_MAC_CONFIGURATION_SARC_SHIFT    (28U)
/*! SARC - Source Address Insertion or Replacement Control
 *  0b000..mti_sa_ctrl_i and ati_sa_ctrl_i input signals control the SA field generation
 *  0b010..Contents of MAC Addr-0 inserted in SA field
 *  0b011..Contents of MAC Addr-0 replaces SA field
 *  0b110..Contents of MAC Addr-1 inserted in SA field
 *  0b111..Contents of MAC Addr-1 replaces SA field
 */
#define ENET_QOS_MAC_CONFIGURATION_SARC(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CONFIGURATION_SARC_SHIFT)) & ENET_QOS_MAC_CONFIGURATION_SARC_MASK)
/*! @} */

/*! @name MAC_EXT_CONFIGURATION - MAC Extended Configuration Register */
/*! @{ */

#define ENET_QOS_MAC_EXT_CONFIGURATION_GPSL_MASK (0x3FFFU)
#define ENET_QOS_MAC_EXT_CONFIGURATION_GPSL_SHIFT (0U)
/*! GPSL - Giant Packet Size Limit */
#define ENET_QOS_MAC_EXT_CONFIGURATION_GPSL(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_EXT_CONFIGURATION_GPSL_SHIFT)) & ENET_QOS_MAC_EXT_CONFIGURATION_GPSL_MASK)

#define ENET_QOS_MAC_EXT_CONFIGURATION_DCRCC_MASK (0x10000U)
#define ENET_QOS_MAC_EXT_CONFIGURATION_DCRCC_SHIFT (16U)
/*! DCRCC - Disable CRC Checking for Received Packets
 *  0b0..CRC Checking is enabled
 *  0b1..CRC Checking is disabled
 */
#define ENET_QOS_MAC_EXT_CONFIGURATION_DCRCC(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_EXT_CONFIGURATION_DCRCC_SHIFT)) & ENET_QOS_MAC_EXT_CONFIGURATION_DCRCC_MASK)

#define ENET_QOS_MAC_EXT_CONFIGURATION_SPEN_MASK (0x20000U)
#define ENET_QOS_MAC_EXT_CONFIGURATION_SPEN_SHIFT (17U)
/*! SPEN - Slow Protocol Detection Enable
 *  0b0..Slow Protocol Detection is disabled
 *  0b1..Slow Protocol Detection is enabled
 */
#define ENET_QOS_MAC_EXT_CONFIGURATION_SPEN(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_EXT_CONFIGURATION_SPEN_SHIFT)) & ENET_QOS_MAC_EXT_CONFIGURATION_SPEN_MASK)

#define ENET_QOS_MAC_EXT_CONFIGURATION_USP_MASK  (0x40000U)
#define ENET_QOS_MAC_EXT_CONFIGURATION_USP_SHIFT (18U)
/*! USP - Unicast Slow Protocol Packet Detect
 *  0b0..Unicast Slow Protocol Packet Detection is disabled
 *  0b1..Unicast Slow Protocol Packet Detection is enabled
 */
#define ENET_QOS_MAC_EXT_CONFIGURATION_USP(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_EXT_CONFIGURATION_USP_SHIFT)) & ENET_QOS_MAC_EXT_CONFIGURATION_USP_MASK)

#define ENET_QOS_MAC_EXT_CONFIGURATION_PDC_MASK  (0x80000U)
#define ENET_QOS_MAC_EXT_CONFIGURATION_PDC_SHIFT (19U)
/*! PDC - Packet Duplication Control
 *  0b0..Packet Duplication Control is disabled
 *  0b1..Packet Duplication Control is enabled
 */
#define ENET_QOS_MAC_EXT_CONFIGURATION_PDC(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_EXT_CONFIGURATION_PDC_SHIFT)) & ENET_QOS_MAC_EXT_CONFIGURATION_PDC_MASK)

#define ENET_QOS_MAC_EXT_CONFIGURATION_EIPGEN_MASK (0x1000000U)
#define ENET_QOS_MAC_EXT_CONFIGURATION_EIPGEN_SHIFT (24U)
/*! EIPGEN - Extended Inter-Packet Gap Enable
 *  0b0..Extended Inter-Packet Gap is disabled
 *  0b1..Extended Inter-Packet Gap is enabled
 */
#define ENET_QOS_MAC_EXT_CONFIGURATION_EIPGEN(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_EXT_CONFIGURATION_EIPGEN_SHIFT)) & ENET_QOS_MAC_EXT_CONFIGURATION_EIPGEN_MASK)

#define ENET_QOS_MAC_EXT_CONFIGURATION_EIPG_MASK (0x3E000000U)
#define ENET_QOS_MAC_EXT_CONFIGURATION_EIPG_SHIFT (25U)
/*! EIPG - Extended Inter-Packet Gap */
#define ENET_QOS_MAC_EXT_CONFIGURATION_EIPG(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_EXT_CONFIGURATION_EIPG_SHIFT)) & ENET_QOS_MAC_EXT_CONFIGURATION_EIPG_MASK)
/*! @} */

/*! @name MAC_PACKET_FILTER - MAC Packet Filter */
/*! @{ */

#define ENET_QOS_MAC_PACKET_FILTER_PR_MASK       (0x1U)
#define ENET_QOS_MAC_PACKET_FILTER_PR_SHIFT      (0U)
/*! PR - Promiscuous Mode
 *  0b0..Promiscuous Mode is disabled
 *  0b1..Promiscuous Mode is enabled
 */
#define ENET_QOS_MAC_PACKET_FILTER_PR(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PACKET_FILTER_PR_SHIFT)) & ENET_QOS_MAC_PACKET_FILTER_PR_MASK)

#define ENET_QOS_MAC_PACKET_FILTER_HUC_MASK      (0x2U)
#define ENET_QOS_MAC_PACKET_FILTER_HUC_SHIFT     (1U)
/*! HUC - Hash Unicast
 *  0b0..Hash Unicast is disabled
 *  0b1..Hash Unicast is enabled
 */
#define ENET_QOS_MAC_PACKET_FILTER_HUC(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PACKET_FILTER_HUC_SHIFT)) & ENET_QOS_MAC_PACKET_FILTER_HUC_MASK)

#define ENET_QOS_MAC_PACKET_FILTER_HMC_MASK      (0x4U)
#define ENET_QOS_MAC_PACKET_FILTER_HMC_SHIFT     (2U)
/*! HMC - Hash Multicast
 *  0b0..Hash Multicast is disabled
 *  0b1..Hash Multicast is enabled
 */
#define ENET_QOS_MAC_PACKET_FILTER_HMC(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PACKET_FILTER_HMC_SHIFT)) & ENET_QOS_MAC_PACKET_FILTER_HMC_MASK)

#define ENET_QOS_MAC_PACKET_FILTER_DAIF_MASK     (0x8U)
#define ENET_QOS_MAC_PACKET_FILTER_DAIF_SHIFT    (3U)
/*! DAIF - DA Inverse Filtering
 *  0b0..DA Inverse Filtering is disabled
 *  0b1..DA Inverse Filtering is enabled
 */
#define ENET_QOS_MAC_PACKET_FILTER_DAIF(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PACKET_FILTER_DAIF_SHIFT)) & ENET_QOS_MAC_PACKET_FILTER_DAIF_MASK)

#define ENET_QOS_MAC_PACKET_FILTER_PM_MASK       (0x10U)
#define ENET_QOS_MAC_PACKET_FILTER_PM_SHIFT      (4U)
/*! PM - Pass All Multicast
 *  0b0..Pass All Multicast is disabled
 *  0b1..Pass All Multicast is enabled
 */
#define ENET_QOS_MAC_PACKET_FILTER_PM(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PACKET_FILTER_PM_SHIFT)) & ENET_QOS_MAC_PACKET_FILTER_PM_MASK)

#define ENET_QOS_MAC_PACKET_FILTER_DBF_MASK      (0x20U)
#define ENET_QOS_MAC_PACKET_FILTER_DBF_SHIFT     (5U)
/*! DBF - Disable Broadcast Packets
 *  0b0..Enable Broadcast Packets
 *  0b1..Disable Broadcast Packets
 */
#define ENET_QOS_MAC_PACKET_FILTER_DBF(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PACKET_FILTER_DBF_SHIFT)) & ENET_QOS_MAC_PACKET_FILTER_DBF_MASK)

#define ENET_QOS_MAC_PACKET_FILTER_PCF_MASK      (0xC0U)
#define ENET_QOS_MAC_PACKET_FILTER_PCF_SHIFT     (6U)
/*! PCF - Pass Control Packets These bits control the forwarding of all control packets (including
 *    unicast and multicast Pause packets).
 *  0b00..MAC filters all control packets from reaching the application
 *  0b01..MAC forwards all control packets except Pause packets to the application even if they fail the Address filter
 *  0b10..MAC forwards all control packets to the application even if they fail the Address filter
 *  0b11..MAC forwards the control packets that pass the Address filter
 */
#define ENET_QOS_MAC_PACKET_FILTER_PCF(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PACKET_FILTER_PCF_SHIFT)) & ENET_QOS_MAC_PACKET_FILTER_PCF_MASK)

#define ENET_QOS_MAC_PACKET_FILTER_SAIF_MASK     (0x100U)
#define ENET_QOS_MAC_PACKET_FILTER_SAIF_SHIFT    (8U)
/*! SAIF - SA Inverse Filtering
 *  0b0..SA Inverse Filtering is disabled
 *  0b1..SA Inverse Filtering is enabled
 */
#define ENET_QOS_MAC_PACKET_FILTER_SAIF(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PACKET_FILTER_SAIF_SHIFT)) & ENET_QOS_MAC_PACKET_FILTER_SAIF_MASK)

#define ENET_QOS_MAC_PACKET_FILTER_SAF_MASK      (0x200U)
#define ENET_QOS_MAC_PACKET_FILTER_SAF_SHIFT     (9U)
/*! SAF - Source Address Filter Enable
 *  0b0..SA Filtering is disabled
 *  0b1..SA Filtering is enabled
 */
#define ENET_QOS_MAC_PACKET_FILTER_SAF(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PACKET_FILTER_SAF_SHIFT)) & ENET_QOS_MAC_PACKET_FILTER_SAF_MASK)

#define ENET_QOS_MAC_PACKET_FILTER_HPF_MASK      (0x400U)
#define ENET_QOS_MAC_PACKET_FILTER_HPF_SHIFT     (10U)
/*! HPF - Hash or Perfect Filter
 *  0b0..Hash or Perfect Filter is disabled
 *  0b1..Hash or Perfect Filter is enabled
 */
#define ENET_QOS_MAC_PACKET_FILTER_HPF(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PACKET_FILTER_HPF_SHIFT)) & ENET_QOS_MAC_PACKET_FILTER_HPF_MASK)

#define ENET_QOS_MAC_PACKET_FILTER_VTFE_MASK     (0x10000U)
#define ENET_QOS_MAC_PACKET_FILTER_VTFE_SHIFT    (16U)
/*! VTFE - VLAN Tag Filter Enable
 *  0b0..VLAN Tag Filter is disabled
 *  0b1..VLAN Tag Filter is enabled
 */
#define ENET_QOS_MAC_PACKET_FILTER_VTFE(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PACKET_FILTER_VTFE_SHIFT)) & ENET_QOS_MAC_PACKET_FILTER_VTFE_MASK)

#define ENET_QOS_MAC_PACKET_FILTER_IPFE_MASK     (0x100000U)
#define ENET_QOS_MAC_PACKET_FILTER_IPFE_SHIFT    (20U)
/*! IPFE - Layer 3 and Layer 4 Filter Enable
 *  0b0..Layer 3 and Layer 4 Filters are disabled
 *  0b1..Layer 3 and Layer 4 Filters are enabled
 */
#define ENET_QOS_MAC_PACKET_FILTER_IPFE(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PACKET_FILTER_IPFE_SHIFT)) & ENET_QOS_MAC_PACKET_FILTER_IPFE_MASK)

#define ENET_QOS_MAC_PACKET_FILTER_DNTU_MASK     (0x200000U)
#define ENET_QOS_MAC_PACKET_FILTER_DNTU_SHIFT    (21U)
/*! DNTU - Drop Non-TCP/UDP over IP Packets
 *  0b0..Forward Non-TCP/UDP over IP Packets
 *  0b1..Drop Non-TCP/UDP over IP Packets
 */
#define ENET_QOS_MAC_PACKET_FILTER_DNTU(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PACKET_FILTER_DNTU_SHIFT)) & ENET_QOS_MAC_PACKET_FILTER_DNTU_MASK)

#define ENET_QOS_MAC_PACKET_FILTER_RA_MASK       (0x80000000U)
#define ENET_QOS_MAC_PACKET_FILTER_RA_SHIFT      (31U)
/*! RA - Receive All
 *  0b0..Receive All is disabled
 *  0b1..Receive All is enabled
 */
#define ENET_QOS_MAC_PACKET_FILTER_RA(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PACKET_FILTER_RA_SHIFT)) & ENET_QOS_MAC_PACKET_FILTER_RA_MASK)
/*! @} */

/*! @name MAC_WATCHDOG_TIMEOUT - Watchdog Timeout */
/*! @{ */

#define ENET_QOS_MAC_WATCHDOG_TIMEOUT_WTO_MASK   (0xFU)
#define ENET_QOS_MAC_WATCHDOG_TIMEOUT_WTO_SHIFT  (0U)
/*! WTO - Watchdog Timeout
 *  0b0000..2 KB
 *  0b0001..3 KB
 *  0b0010..4 KB
 *  0b0011..5 KB
 *  0b0100..6 KB
 *  0b0101..7 KB
 *  0b0110..8 KB
 *  0b0111..9 KB
 *  0b1000..10 KB
 *  0b1001..11 KB
 *  0b1010..12 KB
 *  0b1011..13 KB
 *  0b1100..14 KB
 *  0b1101..15 KB
 *  0b1110..16383 Bytes
 *  0b1111..Reserved
 */
#define ENET_QOS_MAC_WATCHDOG_TIMEOUT_WTO(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_WATCHDOG_TIMEOUT_WTO_SHIFT)) & ENET_QOS_MAC_WATCHDOG_TIMEOUT_WTO_MASK)

#define ENET_QOS_MAC_WATCHDOG_TIMEOUT_PWE_MASK   (0x100U)
#define ENET_QOS_MAC_WATCHDOG_TIMEOUT_PWE_SHIFT  (8U)
/*! PWE - Programmable Watchdog Enable
 *  0b0..Programmable Watchdog is disabled
 *  0b1..Programmable Watchdog is enabled
 */
#define ENET_QOS_MAC_WATCHDOG_TIMEOUT_PWE(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_WATCHDOG_TIMEOUT_PWE_SHIFT)) & ENET_QOS_MAC_WATCHDOG_TIMEOUT_PWE_MASK)
/*! @} */

/*! @name MAC_HASH_TABLE_REG0 - MAC Hash Table Register 0 */
/*! @{ */

#define ENET_QOS_MAC_HASH_TABLE_REG0_HT31T0_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_HASH_TABLE_REG0_HT31T0_SHIFT (0U)
/*! HT31T0 - MAC Hash Table First 32 Bits This field contains the first 32 Bits [31:0] of the Hash table. */
#define ENET_QOS_MAC_HASH_TABLE_REG0_HT31T0(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HASH_TABLE_REG0_HT31T0_SHIFT)) & ENET_QOS_MAC_HASH_TABLE_REG0_HT31T0_MASK)
/*! @} */

/*! @name MAC_HASH_TABLE_REG1 - MAC Hash Table Register 1 */
/*! @{ */

#define ENET_QOS_MAC_HASH_TABLE_REG1_HT63T32_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_HASH_TABLE_REG1_HT63T32_SHIFT (0U)
/*! HT63T32 - MAC Hash Table Second 32 Bits This field contains the second 32 Bits [63:32] of the Hash table. */
#define ENET_QOS_MAC_HASH_TABLE_REG1_HT63T32(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HASH_TABLE_REG1_HT63T32_SHIFT)) & ENET_QOS_MAC_HASH_TABLE_REG1_HT63T32_MASK)
/*! @} */

/*! @name MAC_VLAN_TAG_CTRL - MAC VLAN Tag Control */
/*! @{ */

#define ENET_QOS_MAC_VLAN_TAG_CTRL_OB_MASK       (0x1U)
#define ENET_QOS_MAC_VLAN_TAG_CTRL_OB_SHIFT      (0U)
/*! OB - Operation Busy
 *  0b0..Operation Busy is disabled
 *  0b1..Operation Busy is enabled
 */
#define ENET_QOS_MAC_VLAN_TAG_CTRL_OB(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_CTRL_OB_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_CTRL_OB_MASK)

#define ENET_QOS_MAC_VLAN_TAG_CTRL_CT_MASK       (0x2U)
#define ENET_QOS_MAC_VLAN_TAG_CTRL_CT_SHIFT      (1U)
/*! CT - Command Type
 *  0b0..Write operation
 *  0b1..Read operation
 */
#define ENET_QOS_MAC_VLAN_TAG_CTRL_CT(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_CTRL_CT_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_CTRL_CT_MASK)

#define ENET_QOS_MAC_VLAN_TAG_CTRL_OFS_MASK      (0x7CU)
#define ENET_QOS_MAC_VLAN_TAG_CTRL_OFS_SHIFT     (2U)
/*! OFS - Offset */
#define ENET_QOS_MAC_VLAN_TAG_CTRL_OFS(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_CTRL_OFS_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_CTRL_OFS_MASK)

#define ENET_QOS_MAC_VLAN_TAG_CTRL_VTIM_MASK     (0x20000U)
#define ENET_QOS_MAC_VLAN_TAG_CTRL_VTIM_SHIFT    (17U)
/*! VTIM - VLAN Tag Inverse Match Enable
 *  0b0..VLAN Tag Inverse Match is disabled
 *  0b1..VLAN Tag Inverse Match is enabled
 */
#define ENET_QOS_MAC_VLAN_TAG_CTRL_VTIM(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_CTRL_VTIM_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_CTRL_VTIM_MASK)

#define ENET_QOS_MAC_VLAN_TAG_CTRL_ESVL_MASK     (0x40000U)
#define ENET_QOS_MAC_VLAN_TAG_CTRL_ESVL_SHIFT    (18U)
/*! ESVL - Enable S-VLAN When this bit is set, the MAC transmitter and receiver consider the S-VLAN
 *    packets (Type = 0x88A8) as valid VLAN tagged packets.
 *  0b0..S-VLAN is disabled
 *  0b1..S-VLAN is enabled
 */
#define ENET_QOS_MAC_VLAN_TAG_CTRL_ESVL(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_CTRL_ESVL_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_CTRL_ESVL_MASK)

#define ENET_QOS_MAC_VLAN_TAG_CTRL_EVLS_MASK     (0x600000U)
#define ENET_QOS_MAC_VLAN_TAG_CTRL_EVLS_SHIFT    (21U)
/*! EVLS - Enable VLAN Tag Stripping on Receive This field indicates the stripping operation on the
 *    outer VLAN Tag in received packet.
 *  0b00..Do not strip
 *  0b01..Strip if VLAN filter passes
 *  0b10..Strip if VLAN filter fails
 *  0b11..Always strip
 */
#define ENET_QOS_MAC_VLAN_TAG_CTRL_EVLS(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_CTRL_EVLS_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_CTRL_EVLS_MASK)

#define ENET_QOS_MAC_VLAN_TAG_CTRL_EVLRXS_MASK   (0x1000000U)
#define ENET_QOS_MAC_VLAN_TAG_CTRL_EVLRXS_SHIFT  (24U)
/*! EVLRXS - Enable VLAN Tag in Rx status
 *  0b0..VLAN Tag in Rx status is disabled
 *  0b1..VLAN Tag in Rx status is enabled
 */
#define ENET_QOS_MAC_VLAN_TAG_CTRL_EVLRXS(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_CTRL_EVLRXS_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_CTRL_EVLRXS_MASK)

#define ENET_QOS_MAC_VLAN_TAG_CTRL_VTHM_MASK     (0x2000000U)
#define ENET_QOS_MAC_VLAN_TAG_CTRL_VTHM_SHIFT    (25U)
/*! VTHM - VLAN Tag Hash Table Match Enable
 *  0b0..VLAN Tag Hash Table Match is disabled
 *  0b1..VLAN Tag Hash Table Match is enabled
 */
#define ENET_QOS_MAC_VLAN_TAG_CTRL_VTHM(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_CTRL_VTHM_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_CTRL_VTHM_MASK)

#define ENET_QOS_MAC_VLAN_TAG_CTRL_EDVLP_MASK    (0x4000000U)
#define ENET_QOS_MAC_VLAN_TAG_CTRL_EDVLP_SHIFT   (26U)
/*! EDVLP - Enable Double VLAN Processing
 *  0b0..Double VLAN Processing is disabled
 *  0b1..Double VLAN Processing is enabled
 */
#define ENET_QOS_MAC_VLAN_TAG_CTRL_EDVLP(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_CTRL_EDVLP_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_CTRL_EDVLP_MASK)

#define ENET_QOS_MAC_VLAN_TAG_CTRL_ERIVLT_MASK   (0x8000000U)
#define ENET_QOS_MAC_VLAN_TAG_CTRL_ERIVLT_SHIFT  (27U)
/*! ERIVLT - ERIVLT
 *  0b0..Inner VLAN tag is disabled
 *  0b1..Inner VLAN tag is enabled
 */
#define ENET_QOS_MAC_VLAN_TAG_CTRL_ERIVLT(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_CTRL_ERIVLT_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_CTRL_ERIVLT_MASK)

#define ENET_QOS_MAC_VLAN_TAG_CTRL_EIVLS_MASK    (0x30000000U)
#define ENET_QOS_MAC_VLAN_TAG_CTRL_EIVLS_SHIFT   (28U)
/*! EIVLS - Enable Inner VLAN Tag Stripping on Receive This field indicates the stripping operation
 *    on inner VLAN Tag in received packet.
 *  0b00..Do not strip
 *  0b01..Strip if VLAN filter passes
 *  0b10..Strip if VLAN filter fails
 *  0b11..Always strip
 */
#define ENET_QOS_MAC_VLAN_TAG_CTRL_EIVLS(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_CTRL_EIVLS_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_CTRL_EIVLS_MASK)

#define ENET_QOS_MAC_VLAN_TAG_CTRL_EIVLRXS_MASK  (0x80000000U)
#define ENET_QOS_MAC_VLAN_TAG_CTRL_EIVLRXS_SHIFT (31U)
/*! EIVLRXS - Enable Inner VLAN Tag in Rx Status
 *  0b0..Inner VLAN Tag in Rx status is disabled
 *  0b1..Inner VLAN Tag in Rx status is enabled
 */
#define ENET_QOS_MAC_VLAN_TAG_CTRL_EIVLRXS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_CTRL_EIVLRXS_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_CTRL_EIVLRXS_MASK)
/*! @} */

/*! @name MAC_VLAN_TAG_DATA - MAC VLAN Tag Data */
/*! @{ */

#define ENET_QOS_MAC_VLAN_TAG_DATA_VID_MASK      (0xFFFFU)
#define ENET_QOS_MAC_VLAN_TAG_DATA_VID_SHIFT     (0U)
/*! VID - VLAN Tag ID */
#define ENET_QOS_MAC_VLAN_TAG_DATA_VID(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_DATA_VID_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_DATA_VID_MASK)

#define ENET_QOS_MAC_VLAN_TAG_DATA_VEN_MASK      (0x10000U)
#define ENET_QOS_MAC_VLAN_TAG_DATA_VEN_SHIFT     (16U)
/*! VEN - VLAN Tag Enable
 *  0b0..VLAN Tag is disabled
 *  0b1..VLAN Tag is enabled
 */
#define ENET_QOS_MAC_VLAN_TAG_DATA_VEN(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_DATA_VEN_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_DATA_VEN_MASK)

#define ENET_QOS_MAC_VLAN_TAG_DATA_ETV_MASK      (0x20000U)
#define ENET_QOS_MAC_VLAN_TAG_DATA_ETV_SHIFT     (17U)
/*! ETV - 12bits or 16bits VLAN comparison
 *  0b0..16 bit VLAN comparison
 *  0b1..12 bit VLAN comparison
 */
#define ENET_QOS_MAC_VLAN_TAG_DATA_ETV(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_DATA_ETV_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_DATA_ETV_MASK)

#define ENET_QOS_MAC_VLAN_TAG_DATA_DOVLTC_MASK   (0x40000U)
#define ENET_QOS_MAC_VLAN_TAG_DATA_DOVLTC_SHIFT  (18U)
/*! DOVLTC - Disable VLAN Type Comparison
 *  0b0..VLAN type comparison is enabled
 *  0b1..VLAN type comparison is disabled
 */
#define ENET_QOS_MAC_VLAN_TAG_DATA_DOVLTC(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_DATA_DOVLTC_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_DATA_DOVLTC_MASK)

#define ENET_QOS_MAC_VLAN_TAG_DATA_ERSVLM_MASK   (0x80000U)
#define ENET_QOS_MAC_VLAN_TAG_DATA_ERSVLM_SHIFT  (19U)
/*! ERSVLM - Enable S-VLAN Match for received Frames
 *  0b0..Receive S-VLAN Match is disabled
 *  0b1..Receive S-VLAN Match is enabled
 */
#define ENET_QOS_MAC_VLAN_TAG_DATA_ERSVLM(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_DATA_ERSVLM_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_DATA_ERSVLM_MASK)

#define ENET_QOS_MAC_VLAN_TAG_DATA_ERIVLT_MASK   (0x100000U)
#define ENET_QOS_MAC_VLAN_TAG_DATA_ERIVLT_SHIFT  (20U)
/*! ERIVLT - Enable Inner VLAN Tag Comparison
 *  0b0..Inner VLAN tag comparison is disabled
 *  0b1..Inner VLAN tag comparison is enabled
 */
#define ENET_QOS_MAC_VLAN_TAG_DATA_ERIVLT(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_DATA_ERIVLT_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_DATA_ERIVLT_MASK)

#define ENET_QOS_MAC_VLAN_TAG_DATA_DMACHEN_MASK  (0x1000000U)
#define ENET_QOS_MAC_VLAN_TAG_DATA_DMACHEN_SHIFT (24U)
/*! DMACHEN - DMA Channel Number Enable
 *  0b0..DMA Channel Number is disabled
 *  0b1..DMA Channel Number is enabled
 */
#define ENET_QOS_MAC_VLAN_TAG_DATA_DMACHEN(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_DATA_DMACHEN_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_DATA_DMACHEN_MASK)

#define ENET_QOS_MAC_VLAN_TAG_DATA_DMACHN_MASK   (0xE000000U)
#define ENET_QOS_MAC_VLAN_TAG_DATA_DMACHN_SHIFT  (25U)
/*! DMACHN - DMA Channel Number */
#define ENET_QOS_MAC_VLAN_TAG_DATA_DMACHN(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_TAG_DATA_DMACHN_SHIFT)) & ENET_QOS_MAC_VLAN_TAG_DATA_DMACHN_MASK)
/*! @} */

/*! @name MAC_VLAN_HASH_TABLE - MAC VLAN Hash Table */
/*! @{ */

#define ENET_QOS_MAC_VLAN_HASH_TABLE_VLHT_MASK   (0xFFFFU)
#define ENET_QOS_MAC_VLAN_HASH_TABLE_VLHT_SHIFT  (0U)
/*! VLHT - VLAN Hash Table This field contains the 16-bit VLAN Hash Table. */
#define ENET_QOS_MAC_VLAN_HASH_TABLE_VLHT(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_HASH_TABLE_VLHT_SHIFT)) & ENET_QOS_MAC_VLAN_HASH_TABLE_VLHT_MASK)
/*! @} */

/*! @name MAC_VLAN_INCL - VLAN Tag Inclusion or Replacement */
/*! @{ */

#define ENET_QOS_MAC_VLAN_INCL_VLT_MASK          (0xFFFFU)
#define ENET_QOS_MAC_VLAN_INCL_VLT_SHIFT         (0U)
/*! VLT - VLAN Tag for Transmit Packets */
#define ENET_QOS_MAC_VLAN_INCL_VLT(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_INCL_VLT_SHIFT)) & ENET_QOS_MAC_VLAN_INCL_VLT_MASK)

#define ENET_QOS_MAC_VLAN_INCL_VLC_MASK          (0x30000U)
#define ENET_QOS_MAC_VLAN_INCL_VLC_SHIFT         (16U)
/*! VLC - VLAN Tag Control in Transmit Packets - 2'b00: No VLAN tag deletion, insertion, or
 *    replacement - 2'b01: VLAN tag deletion The MAC removes the VLAN type (bytes 13 and 14) and VLAN tag
 *    (bytes 15 and 16) of all transmitted packets with VLAN tags.
 *  0b00..No VLAN tag deletion, insertion, or replacement
 *  0b01..VLAN tag deletion
 *  0b10..VLAN tag insertion
 *  0b11..VLAN tag replacement
 */
#define ENET_QOS_MAC_VLAN_INCL_VLC(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_INCL_VLC_SHIFT)) & ENET_QOS_MAC_VLAN_INCL_VLC_MASK)

#define ENET_QOS_MAC_VLAN_INCL_VLP_MASK          (0x40000U)
#define ENET_QOS_MAC_VLAN_INCL_VLP_SHIFT         (18U)
/*! VLP - VLAN Priority Control
 *  0b0..VLAN Priority Control is disabled
 *  0b1..VLAN Priority Control is enabled
 */
#define ENET_QOS_MAC_VLAN_INCL_VLP(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_INCL_VLP_SHIFT)) & ENET_QOS_MAC_VLAN_INCL_VLP_MASK)

#define ENET_QOS_MAC_VLAN_INCL_CSVL_MASK         (0x80000U)
#define ENET_QOS_MAC_VLAN_INCL_CSVL_SHIFT        (19U)
/*! CSVL - C-VLAN or S-VLAN
 *  0b0..C-VLAN type (0x8100) is inserted or replaced
 *  0b1..S-VLAN type (0x88A8) is inserted or replaced
 */
#define ENET_QOS_MAC_VLAN_INCL_CSVL(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_INCL_CSVL_SHIFT)) & ENET_QOS_MAC_VLAN_INCL_CSVL_MASK)

#define ENET_QOS_MAC_VLAN_INCL_VLTI_MASK         (0x100000U)
#define ENET_QOS_MAC_VLAN_INCL_VLTI_SHIFT        (20U)
/*! VLTI - VLAN Tag Input When this bit is set, it indicates that the VLAN tag to be inserted or
 *    replaced in Tx packet should be taken from: - The Tx descriptor
 *  0b0..VLAN Tag Input is disabled
 *  0b1..VLAN Tag Input is enabled
 */
#define ENET_QOS_MAC_VLAN_INCL_VLTI(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_INCL_VLTI_SHIFT)) & ENET_QOS_MAC_VLAN_INCL_VLTI_MASK)

#define ENET_QOS_MAC_VLAN_INCL_CBTI_MASK         (0x200000U)
#define ENET_QOS_MAC_VLAN_INCL_CBTI_SHIFT        (21U)
/*! CBTI - Channel based tag insertion
 *  0b0..Channel based tag insertion is disabled
 *  0b1..Channel based tag insertion is enabled
 */
#define ENET_QOS_MAC_VLAN_INCL_CBTI(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_INCL_CBTI_SHIFT)) & ENET_QOS_MAC_VLAN_INCL_CBTI_MASK)

#define ENET_QOS_MAC_VLAN_INCL_ADDR_MASK         (0x7000000U)
#define ENET_QOS_MAC_VLAN_INCL_ADDR_SHIFT        (24U)
/*! ADDR - Address */
#define ENET_QOS_MAC_VLAN_INCL_ADDR(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_INCL_ADDR_SHIFT)) & ENET_QOS_MAC_VLAN_INCL_ADDR_MASK)

#define ENET_QOS_MAC_VLAN_INCL_RDWR_MASK         (0x40000000U)
#define ENET_QOS_MAC_VLAN_INCL_RDWR_SHIFT        (30U)
/*! RDWR - Read write control
 *  0b0..Read operation of indirect access
 *  0b1..Write operation of indirect access
 */
#define ENET_QOS_MAC_VLAN_INCL_RDWR(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_INCL_RDWR_SHIFT)) & ENET_QOS_MAC_VLAN_INCL_RDWR_MASK)

#define ENET_QOS_MAC_VLAN_INCL_BUSY_MASK         (0x80000000U)
#define ENET_QOS_MAC_VLAN_INCL_BUSY_SHIFT        (31U)
/*! BUSY - Busy
 *  0b0..Busy status not detected
 *  0b1..Busy status detected
 */
#define ENET_QOS_MAC_VLAN_INCL_BUSY(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VLAN_INCL_BUSY_SHIFT)) & ENET_QOS_MAC_VLAN_INCL_BUSY_MASK)
/*! @} */

/*! @name MAC_INNER_VLAN_INCL - MAC Inner VLAN Tag Inclusion or Replacement */
/*! @{ */

#define ENET_QOS_MAC_INNER_VLAN_INCL_VLT_MASK    (0xFFFFU)
#define ENET_QOS_MAC_INNER_VLAN_INCL_VLT_SHIFT   (0U)
/*! VLT - VLAN Tag for Transmit Packets */
#define ENET_QOS_MAC_INNER_VLAN_INCL_VLT(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INNER_VLAN_INCL_VLT_SHIFT)) & ENET_QOS_MAC_INNER_VLAN_INCL_VLT_MASK)

#define ENET_QOS_MAC_INNER_VLAN_INCL_VLC_MASK    (0x30000U)
#define ENET_QOS_MAC_INNER_VLAN_INCL_VLC_SHIFT   (16U)
/*! VLC - VLAN Tag Control in Transmit Packets
 *  0b00..No VLAN tag deletion, insertion, or replacement
 *  0b01..VLAN tag deletion
 *  0b10..VLAN tag insertion
 *  0b11..VLAN tag replacement
 */
#define ENET_QOS_MAC_INNER_VLAN_INCL_VLC(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INNER_VLAN_INCL_VLC_SHIFT)) & ENET_QOS_MAC_INNER_VLAN_INCL_VLC_MASK)

#define ENET_QOS_MAC_INNER_VLAN_INCL_VLP_MASK    (0x40000U)
#define ENET_QOS_MAC_INNER_VLAN_INCL_VLP_SHIFT   (18U)
/*! VLP - VLAN Priority Control
 *  0b0..VLAN Priority Control is disabled
 *  0b1..VLAN Priority Control is enabled
 */
#define ENET_QOS_MAC_INNER_VLAN_INCL_VLP(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INNER_VLAN_INCL_VLP_SHIFT)) & ENET_QOS_MAC_INNER_VLAN_INCL_VLP_MASK)

#define ENET_QOS_MAC_INNER_VLAN_INCL_CSVL_MASK   (0x80000U)
#define ENET_QOS_MAC_INNER_VLAN_INCL_CSVL_SHIFT  (19U)
/*! CSVL - C-VLAN or S-VLAN
 *  0b0..C-VLAN type (0x8100) is inserted
 *  0b1..S-VLAN type (0x88A8) is inserted
 */
#define ENET_QOS_MAC_INNER_VLAN_INCL_CSVL(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INNER_VLAN_INCL_CSVL_SHIFT)) & ENET_QOS_MAC_INNER_VLAN_INCL_CSVL_MASK)

#define ENET_QOS_MAC_INNER_VLAN_INCL_VLTI_MASK   (0x100000U)
#define ENET_QOS_MAC_INNER_VLAN_INCL_VLTI_SHIFT  (20U)
/*! VLTI - VLAN Tag Input When this bit is set, it indicates that the VLAN tag to be inserted or
 *    replaced in Tx packet should be taken from: - The Tx descriptor
 *  0b0..VLAN Tag Input is disabled
 *  0b1..VLAN Tag Input is enabled
 */
#define ENET_QOS_MAC_INNER_VLAN_INCL_VLTI(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INNER_VLAN_INCL_VLTI_SHIFT)) & ENET_QOS_MAC_INNER_VLAN_INCL_VLTI_MASK)
/*! @} */

/*! @name MAC_TX_FLOW_CTRL_Q - MAC Q0 Tx Flow Control..MAC Q4 Tx Flow Control */
/*! @{ */

#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_FCB_BPA_MASK (0x1U)
#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_FCB_BPA_SHIFT (0U)
/*! FCB_BPA - Flow Control Busy or Backpressure Activate
 *  0b0..Flow Control Busy or Backpressure Activate is disabled
 *  0b1..Flow Control Busy or Backpressure Activate is enabled
 */
#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_FCB_BPA(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_FLOW_CTRL_Q_FCB_BPA_SHIFT)) & ENET_QOS_MAC_TX_FLOW_CTRL_Q_FCB_BPA_MASK)

#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_TFE_MASK     (0x2U)
#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_TFE_SHIFT    (1U)
/*! TFE - Transmit Flow Control Enable
 *  0b0..Transmit Flow Control is disabled
 *  0b1..Transmit Flow Control is enabled
 */
#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_TFE(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_FLOW_CTRL_Q_TFE_SHIFT)) & ENET_QOS_MAC_TX_FLOW_CTRL_Q_TFE_MASK)

#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_PLT_MASK     (0x70U)
#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_PLT_SHIFT    (4U)
/*! PLT - Pause Low Threshold
 *  0b000..Pause Time minus 4 Slot Times (PT -4 slot times)
 *  0b001..Pause Time minus 28 Slot Times (PT -28 slot times)
 *  0b010..Pause Time minus 36 Slot Times (PT -36 slot times)
 *  0b011..Pause Time minus 144 Slot Times (PT -144 slot times)
 *  0b100..Pause Time minus 256 Slot Times (PT -256 slot times)
 *  0b101..Pause Time minus 512 Slot Times (PT -512 slot times)
 *  0b110..Reserved
 */
#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_PLT(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_FLOW_CTRL_Q_PLT_SHIFT)) & ENET_QOS_MAC_TX_FLOW_CTRL_Q_PLT_MASK)

#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_DZPQ_MASK    (0x80U)
#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_DZPQ_SHIFT   (7U)
/*! DZPQ - Disable Zero-Quanta Pause
 *  0b0..Zero-Quanta Pause packet generation is enabled
 *  0b1..Zero-Quanta Pause packet generation is disabled
 */
#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_DZPQ(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_FLOW_CTRL_Q_DZPQ_SHIFT)) & ENET_QOS_MAC_TX_FLOW_CTRL_Q_DZPQ_MASK)

#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_PT_MASK      (0xFFFF0000U)
#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_PT_SHIFT     (16U)
/*! PT - Pause Time */
#define ENET_QOS_MAC_TX_FLOW_CTRL_Q_PT(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_FLOW_CTRL_Q_PT_SHIFT)) & ENET_QOS_MAC_TX_FLOW_CTRL_Q_PT_MASK)
/*! @} */

/*! @name MAC_RX_FLOW_CTRL - MAC Rx Flow Control */
/*! @{ */

#define ENET_QOS_MAC_RX_FLOW_CTRL_RFE_MASK       (0x1U)
#define ENET_QOS_MAC_RX_FLOW_CTRL_RFE_SHIFT      (0U)
/*! RFE - Receive Flow Control Enable
 *  0b0..Receive Flow Control is disabled
 *  0b1..Receive Flow Control is enabled
 */
#define ENET_QOS_MAC_RX_FLOW_CTRL_RFE(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_FLOW_CTRL_RFE_SHIFT)) & ENET_QOS_MAC_RX_FLOW_CTRL_RFE_MASK)

#define ENET_QOS_MAC_RX_FLOW_CTRL_UP_MASK        (0x2U)
#define ENET_QOS_MAC_RX_FLOW_CTRL_UP_SHIFT       (1U)
/*! UP - Unicast Pause Packet Detect
 *  0b0..Unicast Pause Packet Detect disabled
 *  0b1..Unicast Pause Packet Detect enabled
 */
#define ENET_QOS_MAC_RX_FLOW_CTRL_UP(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_FLOW_CTRL_UP_SHIFT)) & ENET_QOS_MAC_RX_FLOW_CTRL_UP_MASK)

#define ENET_QOS_MAC_RX_FLOW_CTRL_PFCE_MASK      (0x100U)
#define ENET_QOS_MAC_RX_FLOW_CTRL_PFCE_SHIFT     (8U)
/*! PFCE - Priority Based Flow Control Enable
 *  0b0..Priority Based Flow Control is disabled
 *  0b1..Priority Based Flow Control is enabled
 */
#define ENET_QOS_MAC_RX_FLOW_CTRL_PFCE(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_FLOW_CTRL_PFCE_SHIFT)) & ENET_QOS_MAC_RX_FLOW_CTRL_PFCE_MASK)
/*! @} */

/*! @name MAC_RXQ_CTRL4 - Receive Queue Control 4 */
/*! @{ */

#define ENET_QOS_MAC_RXQ_CTRL4_UFFQE_MASK        (0x1U)
#define ENET_QOS_MAC_RXQ_CTRL4_UFFQE_SHIFT       (0U)
/*! UFFQE - Unicast Address Filter Fail Packets Queuing Enable.
 *  0b0..Unicast Address Filter Fail Packets Queuing is disabled
 *  0b1..Unicast Address Filter Fail Packets Queuing is enabled
 */
#define ENET_QOS_MAC_RXQ_CTRL4_UFFQE(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL4_UFFQE_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL4_UFFQE_MASK)

#define ENET_QOS_MAC_RXQ_CTRL4_UFFQ_MASK         (0xEU)
#define ENET_QOS_MAC_RXQ_CTRL4_UFFQ_SHIFT        (1U)
/*! UFFQ - Unicast Address Filter Fail Packets Queue. */
#define ENET_QOS_MAC_RXQ_CTRL4_UFFQ(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL4_UFFQ_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL4_UFFQ_MASK)

#define ENET_QOS_MAC_RXQ_CTRL4_MFFQE_MASK        (0x100U)
#define ENET_QOS_MAC_RXQ_CTRL4_MFFQE_SHIFT       (8U)
/*! MFFQE - Multicast Address Filter Fail Packets Queuing Enable.
 *  0b0..Multicast Address Filter Fail Packets Queuing is disabled
 *  0b1..Multicast Address Filter Fail Packets Queuing is enabled
 */
#define ENET_QOS_MAC_RXQ_CTRL4_MFFQE(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL4_MFFQE_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL4_MFFQE_MASK)

#define ENET_QOS_MAC_RXQ_CTRL4_MFFQ_MASK         (0xE00U)
#define ENET_QOS_MAC_RXQ_CTRL4_MFFQ_SHIFT        (9U)
/*! MFFQ - Multicast Address Filter Fail Packets Queue. */
#define ENET_QOS_MAC_RXQ_CTRL4_MFFQ(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL4_MFFQ_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL4_MFFQ_MASK)

#define ENET_QOS_MAC_RXQ_CTRL4_VFFQE_MASK        (0x10000U)
#define ENET_QOS_MAC_RXQ_CTRL4_VFFQE_SHIFT       (16U)
/*! VFFQE - VLAN Tag Filter Fail Packets Queuing Enable
 *  0b0..VLAN tag Filter Fail Packets Queuing is disabled
 *  0b1..VLAN tag Filter Fail Packets Queuing is enabled
 */
#define ENET_QOS_MAC_RXQ_CTRL4_VFFQE(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL4_VFFQE_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL4_VFFQE_MASK)

#define ENET_QOS_MAC_RXQ_CTRL4_VFFQ_MASK         (0xE0000U)
#define ENET_QOS_MAC_RXQ_CTRL4_VFFQ_SHIFT        (17U)
/*! VFFQ - VLAN Tag Filter Fail Packets Queue */
#define ENET_QOS_MAC_RXQ_CTRL4_VFFQ(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL4_VFFQ_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL4_VFFQ_MASK)
/*! @} */

/*! @name MAC_TXQ_PRTY_MAP0 - Transmit Queue Priority Mapping 0 */
/*! @{ */

#define ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ0_MASK    (0xFFU)
#define ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ0_SHIFT   (0U)
/*! PSTQ0 - Priorities Selected in Transmit Queue 0 */
#define ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ0(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ0_SHIFT)) & ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ0_MASK)

#define ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ1_MASK    (0xFF00U)
#define ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ1_SHIFT   (8U)
/*! PSTQ1 - Priorities Selected in Transmit Queue 1 This bit is similar to the PSTQ0 bit. */
#define ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ1(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ1_SHIFT)) & ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ1_MASK)

#define ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ2_MASK    (0xFF0000U)
#define ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ2_SHIFT   (16U)
/*! PSTQ2 - Priorities Selected in Transmit Queue 2 This bit is similar to the PSTQ0 bit. */
#define ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ2(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ2_SHIFT)) & ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ2_MASK)

#define ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ3_MASK    (0xFF000000U)
#define ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ3_SHIFT   (24U)
/*! PSTQ3 - Priorities Selected in Transmit Queue 3 This bit is similar to the PSTQ0 bit. */
#define ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ3(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ3_SHIFT)) & ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ3_MASK)
/*! @} */

/*! @name MAC_TXQ_PRTY_MAP1 - Transmit Queue Priority Mapping 1 */
/*! @{ */

#define ENET_QOS_MAC_TXQ_PRTY_MAP1_PSTQ4_MASK    (0xFFU)
#define ENET_QOS_MAC_TXQ_PRTY_MAP1_PSTQ4_SHIFT   (0U)
/*! PSTQ4 - Priorities Selected in Transmit Queue 4 */
#define ENET_QOS_MAC_TXQ_PRTY_MAP1_PSTQ4(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TXQ_PRTY_MAP1_PSTQ4_SHIFT)) & ENET_QOS_MAC_TXQ_PRTY_MAP1_PSTQ4_MASK)
/*! @} */

/*! @name MAC_RXQ_CTRL - Receive Queue Control 0..Receive Queue Control 3 */
/*! @{ */

#define ENET_QOS_MAC_RXQ_CTRL_AVCPQ_MASK         (0x7U)
#define ENET_QOS_MAC_RXQ_CTRL_AVCPQ_SHIFT        (0U)
/*! AVCPQ - AV Untagged Control Packets Queue
 *  0b000..Receive Queue 0
 *  0b001..Receive Queue 1
 *  0b010..Receive Queue 2
 *  0b011..Receive Queue 3
 *  0b100..Receive Queue 4
 *  0b101..Reserved
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define ENET_QOS_MAC_RXQ_CTRL_AVCPQ(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_AVCPQ_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_AVCPQ_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_PSRQ0_MASK         (0xFFU)
#define ENET_QOS_MAC_RXQ_CTRL_PSRQ0_SHIFT        (0U)
/*! PSRQ0 - Priorities Selected in the Receive Queue 0 */
#define ENET_QOS_MAC_RXQ_CTRL_PSRQ0(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_PSRQ0_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_PSRQ0_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_PSRQ4_MASK         (0xFFU)
#define ENET_QOS_MAC_RXQ_CTRL_PSRQ4_SHIFT        (0U)
/*! PSRQ4 - Priorities Selected in the Receive Queue 4 */
#define ENET_QOS_MAC_RXQ_CTRL_PSRQ4(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_PSRQ4_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_PSRQ4_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_RXQ0EN_MASK        (0x3U)
#define ENET_QOS_MAC_RXQ_CTRL_RXQ0EN_SHIFT       (0U)
/*! RXQ0EN - Receive Queue 0 Enable This field indicates whether Rx Queue 0 is enabled for AV or DCB.
 *  0b00..Queue not enabled
 *  0b01..Queue enabled for AV
 *  0b10..Queue enabled for DCB/Generic
 *  0b11..Reserved
 */
#define ENET_QOS_MAC_RXQ_CTRL_RXQ0EN(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_RXQ0EN_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_RXQ0EN_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_RXQ1EN_MASK        (0xCU)
#define ENET_QOS_MAC_RXQ_CTRL_RXQ1EN_SHIFT       (2U)
/*! RXQ1EN - Receive Queue 1 Enable This field is similar to the RXQ0EN field.
 *  0b00..Queue not enabled
 *  0b01..Queue enabled for AV
 *  0b10..Queue enabled for DCB/Generic
 *  0b11..Reserved
 */
#define ENET_QOS_MAC_RXQ_CTRL_RXQ1EN(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_RXQ1EN_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_RXQ1EN_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_PTPQ_MASK          (0x70U)
#define ENET_QOS_MAC_RXQ_CTRL_PTPQ_SHIFT         (4U)
/*! PTPQ - PTP Packets Queue
 *  0b000..Receive Queue 0
 *  0b001..Receive Queue 1
 *  0b010..Receive Queue 2
 *  0b011..Receive Queue 3
 *  0b100..Receive Queue 4
 *  0b101..Reserved
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define ENET_QOS_MAC_RXQ_CTRL_PTPQ(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_PTPQ_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_PTPQ_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_RXQ2EN_MASK        (0x30U)
#define ENET_QOS_MAC_RXQ_CTRL_RXQ2EN_SHIFT       (4U)
/*! RXQ2EN - Receive Queue 2 Enable This field is similar to the RXQ0EN field.
 *  0b00..Queue not enabled
 *  0b01..Queue enabled for AV
 *  0b10..Queue enabled for DCB/Generic
 *  0b11..Reserved
 */
#define ENET_QOS_MAC_RXQ_CTRL_RXQ2EN(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_RXQ2EN_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_RXQ2EN_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_RXQ3EN_MASK        (0xC0U)
#define ENET_QOS_MAC_RXQ_CTRL_RXQ3EN_SHIFT       (6U)
/*! RXQ3EN - Receive Queue 3 Enable This field is similar to the RXQ0EN field.
 *  0b00..Queue not enabled
 *  0b01..Queue enabled for AV
 *  0b10..Queue enabled for DCB/Generic
 *  0b11..Reserved
 */
#define ENET_QOS_MAC_RXQ_CTRL_RXQ3EN(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_RXQ3EN_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_RXQ3EN_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_DCBCPQ_MASK        (0x700U)
#define ENET_QOS_MAC_RXQ_CTRL_DCBCPQ_SHIFT       (8U)
/*! DCBCPQ - DCB Control Packets Queue
 *  0b000..Receive Queue 0
 *  0b001..Receive Queue 1
 *  0b010..Receive Queue 2
 *  0b011..Receive Queue 3
 *  0b100..Receive Queue 4
 *  0b101..Reserved
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define ENET_QOS_MAC_RXQ_CTRL_DCBCPQ(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_DCBCPQ_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_DCBCPQ_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_PSRQ1_MASK         (0xFF00U)
#define ENET_QOS_MAC_RXQ_CTRL_PSRQ1_SHIFT        (8U)
/*! PSRQ1 - Priorities Selected in the Receive Queue 1 */
#define ENET_QOS_MAC_RXQ_CTRL_PSRQ1(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_PSRQ1_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_PSRQ1_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_RXQ4EN_MASK        (0x300U)
#define ENET_QOS_MAC_RXQ_CTRL_RXQ4EN_SHIFT       (8U)
/*! RXQ4EN - Receive Queue 4 Enable This field is similar to the RXQ0EN field.
 *  0b00..Queue not enabled
 *  0b01..Queue enabled for AV
 *  0b10..Queue enabled for DCB/Generic
 *  0b11..Reserved
 */
#define ENET_QOS_MAC_RXQ_CTRL_RXQ4EN(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_RXQ4EN_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_RXQ4EN_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_UPQ_MASK           (0x7000U)
#define ENET_QOS_MAC_RXQ_CTRL_UPQ_SHIFT          (12U)
/*! UPQ - Untagged Packet Queue
 *  0b000..Receive Queue 0
 *  0b001..Receive Queue 1
 *  0b010..Receive Queue 2
 *  0b011..Receive Queue 3
 *  0b100..Receive Queue 4
 *  0b101..Reserved
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define ENET_QOS_MAC_RXQ_CTRL_UPQ(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_UPQ_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_UPQ_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_MCBCQ_MASK         (0x70000U)
#define ENET_QOS_MAC_RXQ_CTRL_MCBCQ_SHIFT        (16U)
/*! MCBCQ - Multicast and Broadcast Queue
 *  0b000..Receive Queue 0
 *  0b001..Receive Queue 1
 *  0b010..Receive Queue 2
 *  0b011..Receive Queue 3
 *  0b100..Receive Queue 4
 *  0b101..Reserved
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define ENET_QOS_MAC_RXQ_CTRL_MCBCQ(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_MCBCQ_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_MCBCQ_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_PSRQ2_MASK         (0xFF0000U)
#define ENET_QOS_MAC_RXQ_CTRL_PSRQ2_SHIFT        (16U)
/*! PSRQ2 - Priorities Selected in the Receive Queue 2 */
#define ENET_QOS_MAC_RXQ_CTRL_PSRQ2(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_PSRQ2_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_PSRQ2_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_MCBCQEN_MASK       (0x100000U)
#define ENET_QOS_MAC_RXQ_CTRL_MCBCQEN_SHIFT      (20U)
/*! MCBCQEN - Multicast and Broadcast Queue Enable This bit specifies that Multicast or Broadcast
 *    packets routing to the Rx Queue is enabled and the Multicast or Broadcast packets must be routed
 *    to Rx Queue specified in MCBCQ field.
 *  0b0..Multicast and Broadcast Queue is disabled
 *  0b1..Multicast and Broadcast Queue is enabled
 */
#define ENET_QOS_MAC_RXQ_CTRL_MCBCQEN(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_MCBCQEN_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_MCBCQEN_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_TACPQE_MASK        (0x200000U)
#define ENET_QOS_MAC_RXQ_CTRL_TACPQE_SHIFT       (21U)
/*! TACPQE - Tagged AV Control Packets Queuing Enable.
 *  0b0..Tagged AV Control Packets Queuing is disabled
 *  0b1..Tagged AV Control Packets Queuing is enabled
 */
#define ENET_QOS_MAC_RXQ_CTRL_TACPQE(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_TACPQE_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_TACPQE_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_TPQC_MASK          (0xC00000U)
#define ENET_QOS_MAC_RXQ_CTRL_TPQC_SHIFT         (22U)
/*! TPQC - Tagged PTP over Ethernet Packets Queuing Control. */
#define ENET_QOS_MAC_RXQ_CTRL_TPQC(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_TPQC_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_TPQC_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_FPRQ_MASK          (0x7000000U)
#define ENET_QOS_MAC_RXQ_CTRL_FPRQ_SHIFT         (24U)
/*! FPRQ - Frame Preemption Residue Queue */
#define ENET_QOS_MAC_RXQ_CTRL_FPRQ(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_FPRQ_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_FPRQ_MASK)

#define ENET_QOS_MAC_RXQ_CTRL_PSRQ3_MASK         (0xFF000000U)
#define ENET_QOS_MAC_RXQ_CTRL_PSRQ3_SHIFT        (24U)
/*! PSRQ3 - Priorities Selected in the Receive Queue 3 */
#define ENET_QOS_MAC_RXQ_CTRL_PSRQ3(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXQ_CTRL_PSRQ3_SHIFT)) & ENET_QOS_MAC_RXQ_CTRL_PSRQ3_MASK)
/*! @} */

/*! @name MAC_INTERRUPT_STATUS - Interrupt Status */
/*! @{ */

#define ENET_QOS_MAC_INTERRUPT_STATUS_RGSMIIIS_MASK (0x1U)
#define ENET_QOS_MAC_INTERRUPT_STATUS_RGSMIIIS_SHIFT (0U)
/*! RGSMIIIS - RGMII or SMII Interrupt Status
 *  0b0..RGMII or SMII Interrupt Status is not active
 *  0b1..RGMII or SMII Interrupt Status is active
 */
#define ENET_QOS_MAC_INTERRUPT_STATUS_RGSMIIIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_STATUS_RGSMIIIS_SHIFT)) & ENET_QOS_MAC_INTERRUPT_STATUS_RGSMIIIS_MASK)

#define ENET_QOS_MAC_INTERRUPT_STATUS_PHYIS_MASK (0x8U)
#define ENET_QOS_MAC_INTERRUPT_STATUS_PHYIS_SHIFT (3U)
/*! PHYIS - PHY Interrupt
 *  0b0..PHY Interrupt not detected
 *  0b1..PHY Interrupt detected
 */
#define ENET_QOS_MAC_INTERRUPT_STATUS_PHYIS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_STATUS_PHYIS_SHIFT)) & ENET_QOS_MAC_INTERRUPT_STATUS_PHYIS_MASK)

#define ENET_QOS_MAC_INTERRUPT_STATUS_PMTIS_MASK (0x10U)
#define ENET_QOS_MAC_INTERRUPT_STATUS_PMTIS_SHIFT (4U)
/*! PMTIS - PMT Interrupt Status
 *  0b0..PMT Interrupt status not active
 *  0b1..PMT Interrupt status active
 */
#define ENET_QOS_MAC_INTERRUPT_STATUS_PMTIS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_STATUS_PMTIS_SHIFT)) & ENET_QOS_MAC_INTERRUPT_STATUS_PMTIS_MASK)

#define ENET_QOS_MAC_INTERRUPT_STATUS_LPIIS_MASK (0x20U)
#define ENET_QOS_MAC_INTERRUPT_STATUS_LPIIS_SHIFT (5U)
/*! LPIIS - LPI Interrupt Status
 *  0b0..LPI Interrupt status not active
 *  0b1..LPI Interrupt status active
 */
#define ENET_QOS_MAC_INTERRUPT_STATUS_LPIIS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_STATUS_LPIIS_SHIFT)) & ENET_QOS_MAC_INTERRUPT_STATUS_LPIIS_MASK)

#define ENET_QOS_MAC_INTERRUPT_STATUS_MMCIS_MASK (0x100U)
#define ENET_QOS_MAC_INTERRUPT_STATUS_MMCIS_SHIFT (8U)
/*! MMCIS - MMC Interrupt Status
 *  0b0..MMC Interrupt status not active
 *  0b1..MMC Interrupt status active
 */
#define ENET_QOS_MAC_INTERRUPT_STATUS_MMCIS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_STATUS_MMCIS_SHIFT)) & ENET_QOS_MAC_INTERRUPT_STATUS_MMCIS_MASK)

#define ENET_QOS_MAC_INTERRUPT_STATUS_MMCRXIS_MASK (0x200U)
#define ENET_QOS_MAC_INTERRUPT_STATUS_MMCRXIS_SHIFT (9U)
/*! MMCRXIS - MMC Receive Interrupt Status
 *  0b0..MMC Receive Interrupt status not active
 *  0b1..MMC Receive Interrupt status active
 */
#define ENET_QOS_MAC_INTERRUPT_STATUS_MMCRXIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_STATUS_MMCRXIS_SHIFT)) & ENET_QOS_MAC_INTERRUPT_STATUS_MMCRXIS_MASK)

#define ENET_QOS_MAC_INTERRUPT_STATUS_MMCTXIS_MASK (0x400U)
#define ENET_QOS_MAC_INTERRUPT_STATUS_MMCTXIS_SHIFT (10U)
/*! MMCTXIS - MMC Transmit Interrupt Status
 *  0b0..MMC Transmit Interrupt status not active
 *  0b1..MMC Transmit Interrupt status active
 */
#define ENET_QOS_MAC_INTERRUPT_STATUS_MMCTXIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_STATUS_MMCTXIS_SHIFT)) & ENET_QOS_MAC_INTERRUPT_STATUS_MMCTXIS_MASK)

#define ENET_QOS_MAC_INTERRUPT_STATUS_MMCRXIPIS_MASK (0x800U)
#define ENET_QOS_MAC_INTERRUPT_STATUS_MMCRXIPIS_SHIFT (11U)
/*! MMCRXIPIS - MMC Receive Checksum Offload Interrupt Status
 *  0b0..MMC Receive Checksum Offload Interrupt status not active
 *  0b1..MMC Receive Checksum Offload Interrupt status active
 */
#define ENET_QOS_MAC_INTERRUPT_STATUS_MMCRXIPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_STATUS_MMCRXIPIS_SHIFT)) & ENET_QOS_MAC_INTERRUPT_STATUS_MMCRXIPIS_MASK)

#define ENET_QOS_MAC_INTERRUPT_STATUS_TSIS_MASK  (0x1000U)
#define ENET_QOS_MAC_INTERRUPT_STATUS_TSIS_SHIFT (12U)
/*! TSIS - Timestamp Interrupt Status
 *  0b0..Timestamp Interrupt status not active
 *  0b1..Timestamp Interrupt status active
 */
#define ENET_QOS_MAC_INTERRUPT_STATUS_TSIS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_STATUS_TSIS_SHIFT)) & ENET_QOS_MAC_INTERRUPT_STATUS_TSIS_MASK)

#define ENET_QOS_MAC_INTERRUPT_STATUS_TXSTSIS_MASK (0x2000U)
#define ENET_QOS_MAC_INTERRUPT_STATUS_TXSTSIS_SHIFT (13U)
/*! TXSTSIS - Transmit Status Interrupt
 *  0b0..Transmit Interrupt status not active
 *  0b1..Transmit Interrupt status active
 */
#define ENET_QOS_MAC_INTERRUPT_STATUS_TXSTSIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_STATUS_TXSTSIS_SHIFT)) & ENET_QOS_MAC_INTERRUPT_STATUS_TXSTSIS_MASK)

#define ENET_QOS_MAC_INTERRUPT_STATUS_RXSTSIS_MASK (0x4000U)
#define ENET_QOS_MAC_INTERRUPT_STATUS_RXSTSIS_SHIFT (14U)
/*! RXSTSIS - Receive Status Interrupt
 *  0b0..Receive Interrupt status not active
 *  0b1..Receive Interrupt status active
 */
#define ENET_QOS_MAC_INTERRUPT_STATUS_RXSTSIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_STATUS_RXSTSIS_SHIFT)) & ENET_QOS_MAC_INTERRUPT_STATUS_RXSTSIS_MASK)

#define ENET_QOS_MAC_INTERRUPT_STATUS_FPEIS_MASK (0x20000U)
#define ENET_QOS_MAC_INTERRUPT_STATUS_FPEIS_SHIFT (17U)
/*! FPEIS - Frame Preemption Interrupt Status
 *  0b0..Frame Preemption Interrupt status not active
 *  0b1..Frame Preemption Interrupt status active
 */
#define ENET_QOS_MAC_INTERRUPT_STATUS_FPEIS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_STATUS_FPEIS_SHIFT)) & ENET_QOS_MAC_INTERRUPT_STATUS_FPEIS_MASK)

#define ENET_QOS_MAC_INTERRUPT_STATUS_MDIOIS_MASK (0x40000U)
#define ENET_QOS_MAC_INTERRUPT_STATUS_MDIOIS_SHIFT (18U)
/*! MDIOIS - MDIO Interrupt Status
 *  0b0..MDIO Interrupt status not active
 *  0b1..MDIO Interrupt status active
 */
#define ENET_QOS_MAC_INTERRUPT_STATUS_MDIOIS(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_STATUS_MDIOIS_SHIFT)) & ENET_QOS_MAC_INTERRUPT_STATUS_MDIOIS_MASK)

#define ENET_QOS_MAC_INTERRUPT_STATUS_MFTIS_MASK (0x80000U)
#define ENET_QOS_MAC_INTERRUPT_STATUS_MFTIS_SHIFT (19U)
/*! MFTIS - MMC FPE Transmit Interrupt Status
 *  0b0..MMC FPE Transmit Interrupt status not active
 *  0b1..MMC FPE Transmit Interrupt status active
 */
#define ENET_QOS_MAC_INTERRUPT_STATUS_MFTIS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_STATUS_MFTIS_SHIFT)) & ENET_QOS_MAC_INTERRUPT_STATUS_MFTIS_MASK)

#define ENET_QOS_MAC_INTERRUPT_STATUS_MFRIS_MASK (0x100000U)
#define ENET_QOS_MAC_INTERRUPT_STATUS_MFRIS_SHIFT (20U)
/*! MFRIS - MMC FPE Receive Interrupt Status
 *  0b0..MMC FPE Receive Interrupt status not active
 *  0b1..MMC FPE Receive Interrupt status active
 */
#define ENET_QOS_MAC_INTERRUPT_STATUS_MFRIS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_STATUS_MFRIS_SHIFT)) & ENET_QOS_MAC_INTERRUPT_STATUS_MFRIS_MASK)
/*! @} */

/*! @name MAC_INTERRUPT_ENABLE - Interrupt Enable */
/*! @{ */

#define ENET_QOS_MAC_INTERRUPT_ENABLE_RGSMIIIE_MASK (0x1U)
#define ENET_QOS_MAC_INTERRUPT_ENABLE_RGSMIIIE_SHIFT (0U)
/*! RGSMIIIE - RGMII or SMII Interrupt Enable When this bit is set, it enables the assertion of the
 *    interrupt signal because of the setting of RGSMIIIS bit in MAC_INTERRUPT_STATUS register.
 *  0b0..RGMII or SMII Interrupt is disabled
 *  0b1..RGMII or SMII Interrupt is enabled
 */
#define ENET_QOS_MAC_INTERRUPT_ENABLE_RGSMIIIE(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_ENABLE_RGSMIIIE_SHIFT)) & ENET_QOS_MAC_INTERRUPT_ENABLE_RGSMIIIE_MASK)

#define ENET_QOS_MAC_INTERRUPT_ENABLE_PHYIE_MASK (0x8U)
#define ENET_QOS_MAC_INTERRUPT_ENABLE_PHYIE_SHIFT (3U)
/*! PHYIE - PHY Interrupt Enable When this bit is set, it enables the assertion of the interrupt
 *    signal because of the setting of MAC_INTERRUPT_STATUS[PHYIS].
 *  0b0..PHY Interrupt is disabled
 *  0b1..PHY Interrupt is enabled
 */
#define ENET_QOS_MAC_INTERRUPT_ENABLE_PHYIE(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_ENABLE_PHYIE_SHIFT)) & ENET_QOS_MAC_INTERRUPT_ENABLE_PHYIE_MASK)

#define ENET_QOS_MAC_INTERRUPT_ENABLE_PMTIE_MASK (0x10U)
#define ENET_QOS_MAC_INTERRUPT_ENABLE_PMTIE_SHIFT (4U)
/*! PMTIE - PMT Interrupt Enable When this bit is set, it enables the assertion of the interrupt
 *    signal because of the setting of MAC_INTERRUPT_STATUS[PMTIS].
 *  0b0..PMT Interrupt is disabled
 *  0b1..PMT Interrupt is enabled
 */
#define ENET_QOS_MAC_INTERRUPT_ENABLE_PMTIE(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_ENABLE_PMTIE_SHIFT)) & ENET_QOS_MAC_INTERRUPT_ENABLE_PMTIE_MASK)

#define ENET_QOS_MAC_INTERRUPT_ENABLE_LPIIE_MASK (0x20U)
#define ENET_QOS_MAC_INTERRUPT_ENABLE_LPIIE_SHIFT (5U)
/*! LPIIE - LPI Interrupt Enable When this bit is set, it enables the assertion of the interrupt
 *    signal because of the setting of MAC_INTERRUPT_STATUS[LPIIS].
 *  0b0..LPI Interrupt is disabled
 *  0b1..LPI Interrupt is enabled
 */
#define ENET_QOS_MAC_INTERRUPT_ENABLE_LPIIE(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_ENABLE_LPIIE_SHIFT)) & ENET_QOS_MAC_INTERRUPT_ENABLE_LPIIE_MASK)

#define ENET_QOS_MAC_INTERRUPT_ENABLE_TSIE_MASK  (0x1000U)
#define ENET_QOS_MAC_INTERRUPT_ENABLE_TSIE_SHIFT (12U)
/*! TSIE - Timestamp Interrupt Enable When this bit is set, it enables the assertion of the
 *    interrupt signal because of the setting of MAC_INTERRUPT_STATUS[TSIS].
 *  0b0..Timestamp Interrupt is disabled
 *  0b1..Timestamp Interrupt is enabled
 */
#define ENET_QOS_MAC_INTERRUPT_ENABLE_TSIE(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_ENABLE_TSIE_SHIFT)) & ENET_QOS_MAC_INTERRUPT_ENABLE_TSIE_MASK)

#define ENET_QOS_MAC_INTERRUPT_ENABLE_TXSTSIE_MASK (0x2000U)
#define ENET_QOS_MAC_INTERRUPT_ENABLE_TXSTSIE_SHIFT (13U)
/*! TXSTSIE - Transmit Status Interrupt Enable When this bit is set, it enables the assertion of the
 *    interrupt signal because of the setting of MAC_INTERRUPT_STATUS[TXSTSIS].
 *  0b0..Timestamp Status Interrupt is disabled
 *  0b1..Timestamp Status Interrupt is enabled
 */
#define ENET_QOS_MAC_INTERRUPT_ENABLE_TXSTSIE(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_ENABLE_TXSTSIE_SHIFT)) & ENET_QOS_MAC_INTERRUPT_ENABLE_TXSTSIE_MASK)

#define ENET_QOS_MAC_INTERRUPT_ENABLE_RXSTSIE_MASK (0x4000U)
#define ENET_QOS_MAC_INTERRUPT_ENABLE_RXSTSIE_SHIFT (14U)
/*! RXSTSIE - Receive Status Interrupt Enable When this bit is set, it enables the assertion of the
 *    interrupt signal because of the setting of MAC_INTERRUPT_STATUS[RXSTSIS].
 *  0b0..Receive Status Interrupt is disabled
 *  0b1..Receive Status Interrupt is enabled
 */
#define ENET_QOS_MAC_INTERRUPT_ENABLE_RXSTSIE(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_ENABLE_RXSTSIE_SHIFT)) & ENET_QOS_MAC_INTERRUPT_ENABLE_RXSTSIE_MASK)

#define ENET_QOS_MAC_INTERRUPT_ENABLE_FPEIE_MASK (0x20000U)
#define ENET_QOS_MAC_INTERRUPT_ENABLE_FPEIE_SHIFT (17U)
/*! FPEIE - Frame Preemption Interrupt Enable When this bit is set, it enables the assertion of the
 *    interrupt when FPEIS field is set in the MAC_INTERRUPT_STATUS.
 *  0b0..Frame Preemption Interrupt is disabled
 *  0b1..Frame Preemption Interrupt is enabled
 */
#define ENET_QOS_MAC_INTERRUPT_ENABLE_FPEIE(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_ENABLE_FPEIE_SHIFT)) & ENET_QOS_MAC_INTERRUPT_ENABLE_FPEIE_MASK)

#define ENET_QOS_MAC_INTERRUPT_ENABLE_MDIOIE_MASK (0x40000U)
#define ENET_QOS_MAC_INTERRUPT_ENABLE_MDIOIE_SHIFT (18U)
/*! MDIOIE - MDIO Interrupt Enable When this bit is set, it enables the assertion of the interrupt
 *    when MDIOIS field is set in the MAC_INTERRUPT_STATUS register.
 *  0b0..MDIO Interrupt is disabled
 *  0b1..MDIO Interrupt is enabled
 */
#define ENET_QOS_MAC_INTERRUPT_ENABLE_MDIOIE(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INTERRUPT_ENABLE_MDIOIE_SHIFT)) & ENET_QOS_MAC_INTERRUPT_ENABLE_MDIOIE_MASK)
/*! @} */

/*! @name MAC_RX_TX_STATUS - Receive Transmit Status */
/*! @{ */

#define ENET_QOS_MAC_RX_TX_STATUS_TJT_MASK       (0x1U)
#define ENET_QOS_MAC_RX_TX_STATUS_TJT_SHIFT      (0U)
/*! TJT - Transmit Jabber Timeout This bit indicates that the Transmit Jabber Timer expired which
 *    happens when the packet size exceeds 2,048 bytes (10,240 bytes when the Jumbo packet is enabled)
 *    and JD bit is reset in the MAC_CONFIGURATION register.
 *  0b0..No Transmit Jabber Timeout
 *  0b1..Transmit Jabber Timeout occurred
 */
#define ENET_QOS_MAC_RX_TX_STATUS_TJT(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_TX_STATUS_TJT_SHIFT)) & ENET_QOS_MAC_RX_TX_STATUS_TJT_MASK)

#define ENET_QOS_MAC_RX_TX_STATUS_NCARR_MASK     (0x2U)
#define ENET_QOS_MAC_RX_TX_STATUS_NCARR_SHIFT    (1U)
/*! NCARR - No Carrier When the DTXSTS bit is set in the MAC_OPERATION_MODE register, this bit
 *    indicates that the carrier signal from the PHY is not present at the end of preamble transmission.
 *  0b0..Carrier is present
 *  0b1..No carrier
 */
#define ENET_QOS_MAC_RX_TX_STATUS_NCARR(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_TX_STATUS_NCARR_SHIFT)) & ENET_QOS_MAC_RX_TX_STATUS_NCARR_MASK)

#define ENET_QOS_MAC_RX_TX_STATUS_LCARR_MASK     (0x4U)
#define ENET_QOS_MAC_RX_TX_STATUS_LCARR_SHIFT    (2U)
/*! LCARR - Loss of Carrier When the DTXSTS bit is set in the MAC_OPERATION_MODE register, this bit
 *    indicates that the loss of carrier occurred during packet transmission, that is, the phy_crs_i
 *    signal was inactive for one or more transmission clock periods during packet transmission.
 *  0b0..Carrier is present
 *  0b1..Loss of carrier
 */
#define ENET_QOS_MAC_RX_TX_STATUS_LCARR(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_TX_STATUS_LCARR_SHIFT)) & ENET_QOS_MAC_RX_TX_STATUS_LCARR_MASK)

#define ENET_QOS_MAC_RX_TX_STATUS_EXDEF_MASK     (0x8U)
#define ENET_QOS_MAC_RX_TX_STATUS_EXDEF_SHIFT    (3U)
/*! EXDEF - Excessive Deferral When the DTXSTS bit is set in the MAC_OPERATION_MODE register and the
 *    DC bit is set in the MAC_CONFIGURATION register, this bit indicates that the transmission
 *    ended because of excessive deferral of over 24,288 bit times (155,680 in 1000/2500 Mbps mode or
 *    when Jumbo packet is enabled).
 *  0b0..No Excessive deferral
 *  0b1..Excessive deferral
 */
#define ENET_QOS_MAC_RX_TX_STATUS_EXDEF(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_TX_STATUS_EXDEF_SHIFT)) & ENET_QOS_MAC_RX_TX_STATUS_EXDEF_MASK)

#define ENET_QOS_MAC_RX_TX_STATUS_LCOL_MASK      (0x10U)
#define ENET_QOS_MAC_RX_TX_STATUS_LCOL_SHIFT     (4U)
/*! LCOL - Late Collision When the DTXSTS bit is set in the MAC_OPERATION_MODE register, this bit
 *    indicates that the packet transmission aborted because a collision occurred after the collision
 *    window (64 bytes including Preamble in MII mode; 512 bytes including Preamble and Carrier
 *    Extension in GMII mode).
 *  0b0..No collision
 *  0b1..Late collision is sensed
 */
#define ENET_QOS_MAC_RX_TX_STATUS_LCOL(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_TX_STATUS_LCOL_SHIFT)) & ENET_QOS_MAC_RX_TX_STATUS_LCOL_MASK)

#define ENET_QOS_MAC_RX_TX_STATUS_EXCOL_MASK     (0x20U)
#define ENET_QOS_MAC_RX_TX_STATUS_EXCOL_SHIFT    (5U)
/*! EXCOL - Excessive Collisions When the DTXSTS bit is set in the MAC_OPERATION_MODE register, this
 *    bit indicates that the transmission aborted after 16 successive collisions while attempting
 *    to transmit the current packet.
 *  0b0..No collision
 *  0b1..Excessive collision is sensed
 */
#define ENET_QOS_MAC_RX_TX_STATUS_EXCOL(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_TX_STATUS_EXCOL_SHIFT)) & ENET_QOS_MAC_RX_TX_STATUS_EXCOL_MASK)

#define ENET_QOS_MAC_RX_TX_STATUS_RWT_MASK       (0x100U)
#define ENET_QOS_MAC_RX_TX_STATUS_RWT_SHIFT      (8U)
/*! RWT - Receive Watchdog Timeout This bit is set when a packet with length greater than 2,048
 *    bytes is received (10, 240 bytes when Jumbo Packet mode is enabled) and the WD bit is reset in the
 *    MAC_CONFIGURATION register.
 *  0b0..No receive watchdog timeout
 *  0b1..Receive watchdog timed out
 */
#define ENET_QOS_MAC_RX_TX_STATUS_RWT(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_TX_STATUS_RWT_SHIFT)) & ENET_QOS_MAC_RX_TX_STATUS_RWT_MASK)
/*! @} */

/*! @name MAC_PMT_CONTROL_STATUS - PMT Control and Status */
/*! @{ */

#define ENET_QOS_MAC_PMT_CONTROL_STATUS_PWRDWN_MASK (0x1U)
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_PWRDWN_SHIFT (0U)
/*! PWRDWN - Power Down When this bit is set, the MAC receiver drops all received packets until it
 *    receives the expected magic packet or remote wake-up packet.
 *  0b0..Power down is disabled
 *  0b1..Power down is enabled
 */
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_PWRDWN(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PMT_CONTROL_STATUS_PWRDWN_SHIFT)) & ENET_QOS_MAC_PMT_CONTROL_STATUS_PWRDWN_MASK)

#define ENET_QOS_MAC_PMT_CONTROL_STATUS_MGKPKTEN_MASK (0x2U)
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_MGKPKTEN_SHIFT (1U)
/*! MGKPKTEN - Magic Packet Enable When this bit is set, a power management event is generated when the MAC receives a magic packet.
 *  0b0..Magic Packet is disabled
 *  0b1..Magic Packet is enabled
 */
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_MGKPKTEN(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PMT_CONTROL_STATUS_MGKPKTEN_SHIFT)) & ENET_QOS_MAC_PMT_CONTROL_STATUS_MGKPKTEN_MASK)

#define ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPKTEN_MASK (0x4U)
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPKTEN_SHIFT (2U)
/*! RWKPKTEN - Remote Wake-Up Packet Enable When this bit is set, a power management event is
 *    generated when the MAC receives a remote wake-up packet.
 *  0b0..Remote wake-up packet is disabled
 *  0b1..Remote wake-up packet is enabled
 */
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPKTEN(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPKTEN_SHIFT)) & ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPKTEN_MASK)

#define ENET_QOS_MAC_PMT_CONTROL_STATUS_MGKPRCVD_MASK (0x20U)
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_MGKPRCVD_SHIFT (5U)
/*! MGKPRCVD - Magic Packet Received When this bit is set, it indicates that the power management
 *    event is generated because of the reception of a magic packet.
 *  0b0..No Magic packet is received
 *  0b1..Magic packet is received
 */
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_MGKPRCVD(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PMT_CONTROL_STATUS_MGKPRCVD_SHIFT)) & ENET_QOS_MAC_PMT_CONTROL_STATUS_MGKPRCVD_MASK)

#define ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPRCVD_MASK (0x40U)
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPRCVD_SHIFT (6U)
/*! RWKPRCVD - Remote Wake-Up Packet Received When this bit is set, it indicates that the power
 *    management event is generated because of the reception of a remote wake-up packet.
 *  0b0..Remote wake-up packet is received
 *  0b1..Remote wake-up packet is received
 */
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPRCVD(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPRCVD_SHIFT)) & ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPRCVD_MASK)

#define ENET_QOS_MAC_PMT_CONTROL_STATUS_GLBLUCAST_MASK (0x200U)
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_GLBLUCAST_SHIFT (9U)
/*! GLBLUCAST - Global Unicast When this bit set, any unicast packet filtered by the MAC (DAF)
 *    address recognition is detected as a remote wake-up packet.
 *  0b0..Global unicast is disabled
 *  0b1..Global unicast is enabled
 */
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_GLBLUCAST(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PMT_CONTROL_STATUS_GLBLUCAST_SHIFT)) & ENET_QOS_MAC_PMT_CONTROL_STATUS_GLBLUCAST_MASK)

#define ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPFE_MASK (0x400U)
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPFE_SHIFT (10U)
/*! RWKPFE - Remote Wake-up Packet Forwarding Enable When this bit is set along with RWKPKTEN, the
 *    MAC receiver drops all received frames until it receives the expected Wake-up frame.
 *  0b0..Remote Wake-up Packet Forwarding is disabled
 *  0b1..Remote Wake-up Packet Forwarding is enabled
 */
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPFE(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPFE_SHIFT)) & ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPFE_MASK)

#define ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPTR_MASK (0x1F000000U)
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPTR_SHIFT (24U)
/*! RWKPTR - Remote Wake-up FIFO Pointer This field gives the current value (0 to 7, 15, or 31 when
 *    4, 8, or 16 Remote Wake-up Packet Filters are selected) of the Remote Wake-up Packet Filter
 *    register pointer.
 */
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPTR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPTR_SHIFT)) & ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPTR_MASK)

#define ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKFILTRST_MASK (0x80000000U)
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKFILTRST_SHIFT (31U)
/*! RWKFILTRST - Remote Wake-Up Packet Filter Register Pointer Reset When this bit is set, the
 *    remote wake-up packet filter register pointer is reset to 3'b000.
 *  0b0..Remote Wake-Up Packet Filter Register Pointer is not Reset
 *  0b1..Remote Wake-Up Packet Filter Register Pointer is Reset
 */
#define ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKFILTRST(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKFILTRST_SHIFT)) & ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKFILTRST_MASK)
/*! @} */

/*! @name MAC_RWK_PACKET_FILTER - Remote Wakeup Filter */
/*! @{ */

#define ENET_QOS_MAC_RWK_PACKET_FILTER_WKUPFRMFTR_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RWK_PACKET_FILTER_WKUPFRMFTR_SHIFT (0U)
/*! WKUPFRMFTR - RWK Packet Filter This field contains the various controls of RWK Packet filter. */
#define ENET_QOS_MAC_RWK_PACKET_FILTER_WKUPFRMFTR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RWK_PACKET_FILTER_WKUPFRMFTR_SHIFT)) & ENET_QOS_MAC_RWK_PACKET_FILTER_WKUPFRMFTR_MASK)
/*! @} */

/*! @name MAC_LPI_CONTROL_STATUS - LPI Control and Status */
/*! @{ */

#define ENET_QOS_MAC_LPI_CONTROL_STATUS_TLPIEN_MASK (0x1U)
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_TLPIEN_SHIFT (0U)
/*! TLPIEN - Transmit LPI Entry When this bit is set, it indicates that the MAC Transmitter has
 *    entered the LPI state because of the setting of the LPIEN bit.
 *  0b0..Transmit LPI entry not detected
 *  0b1..Transmit LPI entry detected
 */
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_TLPIEN(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LPI_CONTROL_STATUS_TLPIEN_SHIFT)) & ENET_QOS_MAC_LPI_CONTROL_STATUS_TLPIEN_MASK)

#define ENET_QOS_MAC_LPI_CONTROL_STATUS_TLPIEX_MASK (0x2U)
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_TLPIEX_SHIFT (1U)
/*! TLPIEX - Transmit LPI Exit When this bit is set, it indicates that the MAC transmitter exited
 *    the LPI state after the application cleared the LPIEN bit and the LPI TW Timer has expired.
 *  0b0..Transmit LPI exit not detected
 *  0b1..Transmit LPI exit detected
 */
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_TLPIEX(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LPI_CONTROL_STATUS_TLPIEX_SHIFT)) & ENET_QOS_MAC_LPI_CONTROL_STATUS_TLPIEX_MASK)

#define ENET_QOS_MAC_LPI_CONTROL_STATUS_RLPIEN_MASK (0x4U)
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_RLPIEN_SHIFT (2U)
/*! RLPIEN - Receive LPI Entry When this bit is set, it indicates that the MAC Receiver has received
 *    an LPI pattern and entered the LPI state.
 *  0b0..Receive LPI entry not detected
 *  0b1..Receive LPI entry detected
 */
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_RLPIEN(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LPI_CONTROL_STATUS_RLPIEN_SHIFT)) & ENET_QOS_MAC_LPI_CONTROL_STATUS_RLPIEN_MASK)

#define ENET_QOS_MAC_LPI_CONTROL_STATUS_RLPIEX_MASK (0x8U)
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_RLPIEX_SHIFT (3U)
/*! RLPIEX - Receive LPI Exit When this bit is set, it indicates that the MAC Receiver has stopped
 *    receiving the LPI pattern on the GMII or MII interface, exited the LPI state, and resumed the
 *    normal reception.
 *  0b0..Receive LPI exit not detected
 *  0b1..Receive LPI exit detected
 */
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_RLPIEX(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LPI_CONTROL_STATUS_RLPIEX_SHIFT)) & ENET_QOS_MAC_LPI_CONTROL_STATUS_RLPIEX_MASK)

#define ENET_QOS_MAC_LPI_CONTROL_STATUS_TLPIST_MASK (0x100U)
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_TLPIST_SHIFT (8U)
/*! TLPIST - Transmit LPI State When this bit is set, it indicates that the MAC is transmitting the
 *    LPI pattern on the GMII or MII interface.
 *  0b0..Transmit LPI state not detected
 *  0b1..Transmit LPI state detected
 */
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_TLPIST(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LPI_CONTROL_STATUS_TLPIST_SHIFT)) & ENET_QOS_MAC_LPI_CONTROL_STATUS_TLPIST_MASK)

#define ENET_QOS_MAC_LPI_CONTROL_STATUS_RLPIST_MASK (0x200U)
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_RLPIST_SHIFT (9U)
/*! RLPIST - Receive LPI State When this bit is set, it indicates that the MAC is receiving the LPI
 *    pattern on the GMII or MII interface.
 *  0b0..Receive LPI state not detected
 *  0b1..Receive LPI state detected
 */
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_RLPIST(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LPI_CONTROL_STATUS_RLPIST_SHIFT)) & ENET_QOS_MAC_LPI_CONTROL_STATUS_RLPIST_MASK)

#define ENET_QOS_MAC_LPI_CONTROL_STATUS_LPIEN_MASK (0x10000U)
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_LPIEN_SHIFT (16U)
/*! LPIEN - LPI Enable When this bit is set, it instructs the MAC Transmitter to enter the LPI state.
 *  0b0..LPI state is disabled
 *  0b1..LPI state is enabled
 */
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_LPIEN(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LPI_CONTROL_STATUS_LPIEN_SHIFT)) & ENET_QOS_MAC_LPI_CONTROL_STATUS_LPIEN_MASK)

#define ENET_QOS_MAC_LPI_CONTROL_STATUS_PLS_MASK (0x20000U)
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_PLS_SHIFT (17U)
/*! PLS - PHY Link Status This bit indicates the link status of the PHY.
 *  0b0..link is down
 *  0b1..link is okay (UP)
 */
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_PLS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LPI_CONTROL_STATUS_PLS_SHIFT)) & ENET_QOS_MAC_LPI_CONTROL_STATUS_PLS_MASK)

#define ENET_QOS_MAC_LPI_CONTROL_STATUS_PLSEN_MASK (0x40000U)
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_PLSEN_SHIFT (18U)
/*! PLSEN - PHY Link Status Enable This bit enables the link status received on the RGMII, SGMII, or
 *    SMII Receive paths to be used for activating the LPI LS TIMER.
 *  0b0..PHY Link Status is disabled
 *  0b1..PHY Link Status is enabled
 */
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_PLSEN(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LPI_CONTROL_STATUS_PLSEN_SHIFT)) & ENET_QOS_MAC_LPI_CONTROL_STATUS_PLSEN_MASK)

#define ENET_QOS_MAC_LPI_CONTROL_STATUS_LPITXA_MASK (0x80000U)
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_LPITXA_SHIFT (19U)
/*! LPITXA - LPI Tx Automate This bit controls the behavior of the MAC when it is entering or coming
 *    out of the LPI mode on the Transmit side.
 *  0b0..LPI Tx Automate is disabled
 *  0b1..LPI Tx Automate is enabled
 */
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_LPITXA(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LPI_CONTROL_STATUS_LPITXA_SHIFT)) & ENET_QOS_MAC_LPI_CONTROL_STATUS_LPITXA_MASK)

#define ENET_QOS_MAC_LPI_CONTROL_STATUS_LPIATE_MASK (0x100000U)
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_LPIATE_SHIFT (20U)
/*! LPIATE - LPI Timer Enable This bit controls the automatic entry of the MAC Transmitter into and exit out of the LPI state.
 *  0b0..LPI Timer is disabled
 *  0b1..LPI Timer is enabled
 */
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_LPIATE(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LPI_CONTROL_STATUS_LPIATE_SHIFT)) & ENET_QOS_MAC_LPI_CONTROL_STATUS_LPIATE_MASK)

#define ENET_QOS_MAC_LPI_CONTROL_STATUS_LPITCSE_MASK (0x200000U)
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_LPITCSE_SHIFT (21U)
/*! LPITCSE - LPI Tx Clock Stop Enable When this bit is set, the MAC asserts
 *    sbd_tx_clk_gating_ctrl_o signal high after it enters Tx LPI mode to indicate that the Tx clock to MAC can be stopped.
 *  0b0..LPI Tx Clock Stop is disabled
 *  0b1..LPI Tx Clock Stop is enabled
 */
#define ENET_QOS_MAC_LPI_CONTROL_STATUS_LPITCSE(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LPI_CONTROL_STATUS_LPITCSE_SHIFT)) & ENET_QOS_MAC_LPI_CONTROL_STATUS_LPITCSE_MASK)
/*! @} */

/*! @name MAC_LPI_TIMERS_CONTROL - LPI Timers Control */
/*! @{ */

#define ENET_QOS_MAC_LPI_TIMERS_CONTROL_TWT_MASK (0xFFFFU)
#define ENET_QOS_MAC_LPI_TIMERS_CONTROL_TWT_SHIFT (0U)
/*! TWT - LPI TW Timer This field specifies the minimum time (in microseconds) for which the MAC
 *    waits after it stops transmitting the LPI pattern to the PHY and before it resumes the normal
 *    transmission.
 */
#define ENET_QOS_MAC_LPI_TIMERS_CONTROL_TWT(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LPI_TIMERS_CONTROL_TWT_SHIFT)) & ENET_QOS_MAC_LPI_TIMERS_CONTROL_TWT_MASK)

#define ENET_QOS_MAC_LPI_TIMERS_CONTROL_LST_MASK (0x3FF0000U)
#define ENET_QOS_MAC_LPI_TIMERS_CONTROL_LST_SHIFT (16U)
/*! LST - LPI LS Timer This field specifies the minimum time (in milliseconds) for which the link
 *    status from the PHY should be up (OKAY) before the LPI pattern can be transmitted to the PHY.
 */
#define ENET_QOS_MAC_LPI_TIMERS_CONTROL_LST(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LPI_TIMERS_CONTROL_LST_SHIFT)) & ENET_QOS_MAC_LPI_TIMERS_CONTROL_LST_MASK)
/*! @} */

/*! @name MAC_LPI_ENTRY_TIMER - Tx LPI Entry Timer Control */
/*! @{ */

#define ENET_QOS_MAC_LPI_ENTRY_TIMER_LPIET_MASK  (0xFFFF8U)
#define ENET_QOS_MAC_LPI_ENTRY_TIMER_LPIET_SHIFT (3U)
/*! LPIET - LPI Entry Timer This field specifies the time in microseconds the MAC waits to enter LPI
 *    mode, after it has transmitted all the frames.
 */
#define ENET_QOS_MAC_LPI_ENTRY_TIMER_LPIET(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LPI_ENTRY_TIMER_LPIET_SHIFT)) & ENET_QOS_MAC_LPI_ENTRY_TIMER_LPIET_MASK)
/*! @} */

/*! @name MAC_ONEUS_TIC_COUNTER - One-microsecond Reference Timer */
/*! @{ */

#define ENET_QOS_MAC_ONEUS_TIC_COUNTER_TIC_1US_CNTR_MASK (0xFFFU)
#define ENET_QOS_MAC_ONEUS_TIC_COUNTER_TIC_1US_CNTR_SHIFT (0U)
/*! TIC_1US_CNTR - 1US TIC Counter The application must program this counter so that the number of clock cycles of CSR clock is 1us. */
#define ENET_QOS_MAC_ONEUS_TIC_COUNTER_TIC_1US_CNTR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_ONEUS_TIC_COUNTER_TIC_1US_CNTR_SHIFT)) & ENET_QOS_MAC_ONEUS_TIC_COUNTER_TIC_1US_CNTR_MASK)
/*! @} */

/*! @name MAC_PHYIF_CONTROL_STATUS - PHY Interface Control and Status */
/*! @{ */

#define ENET_QOS_MAC_PHYIF_CONTROL_STATUS_TC_MASK (0x1U)
#define ENET_QOS_MAC_PHYIF_CONTROL_STATUS_TC_SHIFT (0U)
/*! TC - Transmit Configuration in RGMII, SGMII, or SMII When set, this bit enables the transmission
 *    of duplex mode, link speed, and link up or down information to the PHY in the RGMII, SMII, or
 *    SGMII port.
 *  0b0..Disable Transmit Configuration in RGMII, SGMII, or SMII
 *  0b1..Enable Transmit Configuration in RGMII, SGMII, or SMII
 */
#define ENET_QOS_MAC_PHYIF_CONTROL_STATUS_TC(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PHYIF_CONTROL_STATUS_TC_SHIFT)) & ENET_QOS_MAC_PHYIF_CONTROL_STATUS_TC_MASK)

#define ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LUD_MASK (0x2U)
#define ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LUD_SHIFT (1U)
/*! LUD - Link Up or Down This bit indicates whether the link is up or down during transmission of
 *    configuration in the RGMII, SGMII, or SMII interface.
 *  0b0..Link down
 *  0b1..Link up
 */
#define ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LUD(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LUD_SHIFT)) & ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LUD_MASK)

#define ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LNKMOD_MASK (0x10000U)
#define ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LNKMOD_SHIFT (16U)
/*! LNKMOD - Link Mode This bit indicates the current mode of operation of the link.
 *  0b0..Half-duplex mode
 *  0b1..Full-duplex mode
 */
#define ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LNKMOD(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LNKMOD_SHIFT)) & ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LNKMOD_MASK)

#define ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LNKSPEED_MASK (0x60000U)
#define ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LNKSPEED_SHIFT (17U)
/*! LNKSPEED - Link Speed This bit indicates the current speed of the link.
 *  0b00..2.5 MHz
 *  0b01..25 MHz
 *  0b10..125 MHz
 *  0b11..Reserved
 */
#define ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LNKSPEED(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LNKSPEED_SHIFT)) & ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LNKSPEED_MASK)

#define ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LNKSTS_MASK (0x80000U)
#define ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LNKSTS_SHIFT (19U)
/*! LNKSTS - Link Status This bit indicates whether the link is up (1'b1) or down (1'b0).
 *  0b0..Link down
 *  0b1..Link up
 */
#define ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LNKSTS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LNKSTS_SHIFT)) & ENET_QOS_MAC_PHYIF_CONTROL_STATUS_LNKSTS_MASK)
/*! @} */

/*! @name MAC_VERSION - MAC Version */
/*! @{ */

#define ENET_QOS_MAC_VERSION_SNPSVER_MASK        (0xFFU)
#define ENET_QOS_MAC_VERSION_SNPSVER_SHIFT       (0U)
/*! SNPSVER - Synopsys-defined Version */
#define ENET_QOS_MAC_VERSION_SNPSVER(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VERSION_SNPSVER_SHIFT)) & ENET_QOS_MAC_VERSION_SNPSVER_MASK)

#define ENET_QOS_MAC_VERSION_USERVER_MASK        (0xFF00U)
#define ENET_QOS_MAC_VERSION_USERVER_SHIFT       (8U)
/*! USERVER - User-defined Version (8'h10) */
#define ENET_QOS_MAC_VERSION_USERVER(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_VERSION_USERVER_SHIFT)) & ENET_QOS_MAC_VERSION_USERVER_MASK)
/*! @} */

/*! @name MAC_DEBUG - MAC Debug */
/*! @{ */

#define ENET_QOS_MAC_DEBUG_RPESTS_MASK           (0x1U)
#define ENET_QOS_MAC_DEBUG_RPESTS_SHIFT          (0U)
/*! RPESTS - MAC GMII or MII Receive Protocol Engine Status When this bit is set, it indicates that
 *    the MAC GMII or MII receive protocol engine is actively receiving data, and it is not in the
 *    Idle state.
 *  0b0..MAC GMII or MII Receive Protocol Engine Status not detected
 *  0b1..MAC GMII or MII Receive Protocol Engine Status detected
 */
#define ENET_QOS_MAC_DEBUG_RPESTS(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_DEBUG_RPESTS_SHIFT)) & ENET_QOS_MAC_DEBUG_RPESTS_MASK)

#define ENET_QOS_MAC_DEBUG_RFCFCSTS_MASK         (0x6U)
#define ENET_QOS_MAC_DEBUG_RFCFCSTS_SHIFT        (1U)
/*! RFCFCSTS - MAC Receive Packet Controller FIFO Status When this bit is set, this field indicates
 *    the active state of the small FIFO Read and Write controllers of the MAC Receive Packet
 *    Controller module.
 */
#define ENET_QOS_MAC_DEBUG_RFCFCSTS(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_DEBUG_RFCFCSTS_SHIFT)) & ENET_QOS_MAC_DEBUG_RFCFCSTS_MASK)

#define ENET_QOS_MAC_DEBUG_TPESTS_MASK           (0x10000U)
#define ENET_QOS_MAC_DEBUG_TPESTS_SHIFT          (16U)
/*! TPESTS - MAC GMII or MII Transmit Protocol Engine Status When this bit is set, it indicates that
 *    the MAC GMII or MII transmit protocol engine is actively transmitting data, and it is not in
 *    the Idle state.
 *  0b0..MAC GMII or MII Transmit Protocol Engine Status not detected
 *  0b1..MAC GMII or MII Transmit Protocol Engine Status detected
 */
#define ENET_QOS_MAC_DEBUG_TPESTS(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_DEBUG_TPESTS_SHIFT)) & ENET_QOS_MAC_DEBUG_TPESTS_MASK)

#define ENET_QOS_MAC_DEBUG_TFCSTS_MASK           (0x60000U)
#define ENET_QOS_MAC_DEBUG_TFCSTS_SHIFT          (17U)
/*! TFCSTS - MAC Transmit Packet Controller Status This field indicates the state of the MAC Transmit Packet Controller module.
 *  0b00..Idle state
 *  0b01..Waiting for one of the following: Status of the previous packet OR IPG or back off period to be over
 *  0b10..Generating and transmitting a Pause control packet (in full-duplex mode)
 *  0b11..Transferring input packet for transmission
 */
#define ENET_QOS_MAC_DEBUG_TFCSTS(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_DEBUG_TFCSTS_SHIFT)) & ENET_QOS_MAC_DEBUG_TFCSTS_MASK)
/*! @} */

/*! @name MAC_HW_FEAT - Optional Features or Functions 0..Optional Features or Functions 3 */
/*! @{ */

#define ENET_QOS_MAC_HW_FEAT_MIISEL_MASK         (0x1U)
#define ENET_QOS_MAC_HW_FEAT_MIISEL_SHIFT        (0U)
/*! MIISEL - 10 or 100 Mbps Support This bit is set to 1 when 10/100 Mbps is selected as the Mode of Operation
 *  0b0..No 10 or 100 Mbps support
 *  0b1..10 or 100 Mbps support
 */
#define ENET_QOS_MAC_HW_FEAT_MIISEL(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_MIISEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_MIISEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_NRVF_MASK           (0x7U)
#define ENET_QOS_MAC_HW_FEAT_NRVF_SHIFT          (0U)
/*! NRVF - Number of Extended VLAN Tag Filters Enabled This field indicates the Number of Extended VLAN Tag Filters selected:
 *  0b000..No Extended Rx VLAN Filters
 *  0b001..4 Extended Rx VLAN Filters
 *  0b010..8 Extended Rx VLAN Filters
 *  0b011..16 Extended Rx VLAN Filters
 *  0b100..24 Extended Rx VLAN Filters
 *  0b101..32 Extended Rx VLAN Filters
 *  0b110..Reserved
 */
#define ENET_QOS_MAC_HW_FEAT_NRVF(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_NRVF_SHIFT)) & ENET_QOS_MAC_HW_FEAT_NRVF_MASK)

#define ENET_QOS_MAC_HW_FEAT_RXFIFOSIZE_MASK     (0x1FU)
#define ENET_QOS_MAC_HW_FEAT_RXFIFOSIZE_SHIFT    (0U)
/*! RXFIFOSIZE - MTL Receive FIFO Size This field contains the configured value of MTL Rx FIFO in
 *    bytes expressed as Log to base 2 minus 7, that is, Log2(RXFIFO_SIZE) -7:
 *  0b00000..128 bytes
 *  0b00001..256 bytes
 *  0b00010..512 bytes
 *  0b00011..1024 bytes
 *  0b00100..2048 bytes
 *  0b00101..4096 bytes
 *  0b00110..8192 bytes
 *  0b00111..16384 bytes
 *  0b01000..32 KB
 *  0b01001..64 KB
 *  0b01010..128 KB
 *  0b01011..256 KB
 *  0b01100..Reserved
 */
#define ENET_QOS_MAC_HW_FEAT_RXFIFOSIZE(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_RXFIFOSIZE_SHIFT)) & ENET_QOS_MAC_HW_FEAT_RXFIFOSIZE_MASK)

#define ENET_QOS_MAC_HW_FEAT_RXQCNT_MASK         (0xFU)
#define ENET_QOS_MAC_HW_FEAT_RXQCNT_SHIFT        (0U)
/*! RXQCNT - Number of MTL Receive Queues This field indicates the number of MTL Receive queues:
 *  0b0000..1 MTL Rx Queue
 *  0b0001..2 MTL Rx Queues
 *  0b0010..3 MTL Rx Queues
 *  0b0011..4 MTL Rx Queues
 *  0b0100..5 MTL Rx Queues
 *  0b0101..Reserved
 *  0b0110..Reserved
 *  0b0111..Reserved
 */
#define ENET_QOS_MAC_HW_FEAT_RXQCNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_RXQCNT_SHIFT)) & ENET_QOS_MAC_HW_FEAT_RXQCNT_MASK)

#define ENET_QOS_MAC_HW_FEAT_GMIISEL_MASK        (0x2U)
#define ENET_QOS_MAC_HW_FEAT_GMIISEL_SHIFT       (1U)
/*! GMIISEL - 1000 Mbps Support This bit is set to 1 when 1000 Mbps is selected as the Mode of Operation
 *  0b0..No 1000 Mbps support
 *  0b1..1000 Mbps support
 */
#define ENET_QOS_MAC_HW_FEAT_GMIISEL(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_GMIISEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_GMIISEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_HDSEL_MASK          (0x4U)
#define ENET_QOS_MAC_HW_FEAT_HDSEL_SHIFT         (2U)
/*! HDSEL - Half-duplex Support This bit is set to 1 when the half-duplex mode is selected
 *  0b0..No Half-duplex support
 *  0b1..Half-duplex support
 */
#define ENET_QOS_MAC_HW_FEAT_HDSEL(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_HDSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_HDSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_PCSSEL_MASK         (0x8U)
#define ENET_QOS_MAC_HW_FEAT_PCSSEL_SHIFT        (3U)
/*! PCSSEL - PCS Registers (TBI, SGMII, or RTBI PHY interface) This bit is set to 1 when the TBI,
 *    SGMII, or RTBI PHY interface option is selected
 *  0b0..No PCS Registers (TBI, SGMII, or RTBI PHY interface)
 *  0b1..PCS Registers (TBI, SGMII, or RTBI PHY interface)
 */
#define ENET_QOS_MAC_HW_FEAT_PCSSEL(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_PCSSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_PCSSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_CBTISEL_MASK        (0x10U)
#define ENET_QOS_MAC_HW_FEAT_CBTISEL_SHIFT       (4U)
/*! CBTISEL - Queue/Channel based VLAN tag insertion on Tx Enable This bit is set to 1 when the
 *    Enable Queue/Channel based VLAN tag insertion on Tx Feature is selected.
 *  0b0..Enable Queue/Channel based VLAN tag insertion on Tx feature is not selected
 *  0b1..Enable Queue/Channel based VLAN tag insertion on Tx feature is selected
 */
#define ENET_QOS_MAC_HW_FEAT_CBTISEL(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_CBTISEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_CBTISEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_VLHASH_MASK         (0x10U)
#define ENET_QOS_MAC_HW_FEAT_VLHASH_SHIFT        (4U)
/*! VLHASH - VLAN Hash Filter Selected This bit is set to 1 when the Enable VLAN Hash Table Based Filtering option is selected
 *  0b0..VLAN Hash Filter not selected
 *  0b1..VLAN Hash Filter selected
 */
#define ENET_QOS_MAC_HW_FEAT_VLHASH(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_VLHASH_SHIFT)) & ENET_QOS_MAC_HW_FEAT_VLHASH_MASK)

#define ENET_QOS_MAC_HW_FEAT_DVLAN_MASK          (0x20U)
#define ENET_QOS_MAC_HW_FEAT_DVLAN_SHIFT         (5U)
/*! DVLAN - Double VLAN Tag Processing Selected This bit is set to 1 when the Enable Double VLAN Processing Feature is selected.
 *  0b0..Double VLAN option is not selected
 *  0b1..Double VLAN option is selected
 */
#define ENET_QOS_MAC_HW_FEAT_DVLAN(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_DVLAN_SHIFT)) & ENET_QOS_MAC_HW_FEAT_DVLAN_MASK)

#define ENET_QOS_MAC_HW_FEAT_SMASEL_MASK         (0x20U)
#define ENET_QOS_MAC_HW_FEAT_SMASEL_SHIFT        (5U)
/*! SMASEL - SMA (MDIO) Interface This bit is set to 1 when the Enable Station Management (MDIO Interface) option is selected
 *  0b0..SMA (MDIO) Interface not selected
 *  0b1..SMA (MDIO) Interface selected
 */
#define ENET_QOS_MAC_HW_FEAT_SMASEL(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_SMASEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_SMASEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_SPRAM_MASK          (0x20U)
#define ENET_QOS_MAC_HW_FEAT_SPRAM_SHIFT         (5U)
/*! SPRAM - Single Port RAM Enable This bit is set to 1 when the Use single port RAM Feature is selected.
 *  0b0..Single Port RAM feature is not selected
 *  0b1..Single Port RAM feature is selected
 */
#define ENET_QOS_MAC_HW_FEAT_SPRAM(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_SPRAM_SHIFT)) & ENET_QOS_MAC_HW_FEAT_SPRAM_MASK)

#define ENET_QOS_MAC_HW_FEAT_RWKSEL_MASK         (0x40U)
#define ENET_QOS_MAC_HW_FEAT_RWKSEL_SHIFT        (6U)
/*! RWKSEL - PMT Remote Wake-up Packet Enable This bit is set to 1 when the Enable Remote Wake-Up Packet Detection option is selected
 *  0b0..PMT Remote Wake-up Packet Enable option is not selected
 *  0b1..PMT Remote Wake-up Packet Enable option is selected
 */
#define ENET_QOS_MAC_HW_FEAT_RWKSEL(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_RWKSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_RWKSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_TXFIFOSIZE_MASK     (0x7C0U)
#define ENET_QOS_MAC_HW_FEAT_TXFIFOSIZE_SHIFT    (6U)
/*! TXFIFOSIZE - MTL Transmit FIFO Size This field contains the configured value of MTL Tx FIFO in
 *    bytes expressed as Log to base 2 minus 7, that is, Log2(TXFIFO_SIZE) -7:
 *  0b00000..128 bytes
 *  0b00001..256 bytes
 *  0b00010..512 bytes
 *  0b00011..1024 bytes
 *  0b00100..2048 bytes
 *  0b00101..4096 bytes
 *  0b00110..8192 bytes
 *  0b00111..16384 bytes
 *  0b01000..32 KB
 *  0b01001..64 KB
 *  0b01010..128 KB
 *  0b01011..Reserved
 */
#define ENET_QOS_MAC_HW_FEAT_TXFIFOSIZE(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_TXFIFOSIZE_SHIFT)) & ENET_QOS_MAC_HW_FEAT_TXFIFOSIZE_MASK)

#define ENET_QOS_MAC_HW_FEAT_TXQCNT_MASK         (0x3C0U)
#define ENET_QOS_MAC_HW_FEAT_TXQCNT_SHIFT        (6U)
/*! TXQCNT - Number of MTL Transmit Queues This field indicates the number of MTL Transmit queues:
 *  0b0000..1 MTL Tx Queue
 *  0b0001..2 MTL Tx Queues
 *  0b0010..3 MTL Tx Queues
 *  0b0011..4 MTL Tx Queues
 *  0b0100..5 MTL Tx Queues
 *  0b0101..Reserved
 *  0b0110..Reserved
 *  0b0111..Reserved
 */
#define ENET_QOS_MAC_HW_FEAT_TXQCNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_TXQCNT_SHIFT)) & ENET_QOS_MAC_HW_FEAT_TXQCNT_MASK)

#define ENET_QOS_MAC_HW_FEAT_MGKSEL_MASK         (0x80U)
#define ENET_QOS_MAC_HW_FEAT_MGKSEL_SHIFT        (7U)
/*! MGKSEL - PMT Magic Packet Enable This bit is set to 1 when the Enable Magic Packet Detection option is selected
 *  0b0..PMT Magic Packet Enable option is not selected
 *  0b1..PMT Magic Packet Enable option is selected
 */
#define ENET_QOS_MAC_HW_FEAT_MGKSEL(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_MGKSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_MGKSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_MMCSEL_MASK         (0x100U)
#define ENET_QOS_MAC_HW_FEAT_MMCSEL_SHIFT        (8U)
/*! MMCSEL - RMON Module Enable This bit is set to 1 when the Enable MAC Management Counters (MMC) option is selected
 *  0b0..RMON Module Enable option is not selected
 *  0b1..RMON Module Enable option is selected
 */
#define ENET_QOS_MAC_HW_FEAT_MMCSEL(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_MMCSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_MMCSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_ARPOFFSEL_MASK      (0x200U)
#define ENET_QOS_MAC_HW_FEAT_ARPOFFSEL_SHIFT     (9U)
/*! ARPOFFSEL - ARP Offload Enabled This bit is set to 1 when the Enable IPv4 ARP Offload option is selected
 *  0b0..ARP Offload Enable option is not selected
 *  0b1..ARP Offload Enable option is selected
 */
#define ENET_QOS_MAC_HW_FEAT_ARPOFFSEL(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_ARPOFFSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_ARPOFFSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_PDUPSEL_MASK        (0x200U)
#define ENET_QOS_MAC_HW_FEAT_PDUPSEL_SHIFT       (9U)
/*! PDUPSEL - Broadcast/Multicast Packet Duplication This bit is set to 1 when the
 *    Broadcast/Multicast Packet Duplication feature is selected.
 *  0b0..Broadcast/Multicast Packet Duplication feature is not selected
 *  0b1..Broadcast/Multicast Packet Duplication feature is selected
 */
#define ENET_QOS_MAC_HW_FEAT_PDUPSEL(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_PDUPSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_PDUPSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_FRPSEL_MASK         (0x400U)
#define ENET_QOS_MAC_HW_FEAT_FRPSEL_SHIFT        (10U)
/*! FRPSEL - Flexible Receive Parser Selected This bit is set to 1 when the Enable Flexible
 *    Programmable Receive Parser option is selected.
 *  0b0..Flexible Receive Parser feature is not selected
 *  0b1..Flexible Receive Parser feature is selected
 */
#define ENET_QOS_MAC_HW_FEAT_FRPSEL(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_FRPSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_FRPSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_FRPBS_MASK          (0x1800U)
#define ENET_QOS_MAC_HW_FEAT_FRPBS_SHIFT         (11U)
/*! FRPBS - Flexible Receive Parser Buffer size This field indicates the supported Max Number of
 *    bytes of the packet data to be Parsed by Flexible Receive Parser.
 *  0b00..64 Bytes
 *  0b01..128 Bytes
 *  0b10..256 Bytes
 *  0b11..Reserved
 */
#define ENET_QOS_MAC_HW_FEAT_FRPBS(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_FRPBS_SHIFT)) & ENET_QOS_MAC_HW_FEAT_FRPBS_MASK)

#define ENET_QOS_MAC_HW_FEAT_OSTEN_MASK          (0x800U)
#define ENET_QOS_MAC_HW_FEAT_OSTEN_SHIFT         (11U)
/*! OSTEN - One-Step Timestamping Enable This bit is set to 1 when the Enable One-Step Timestamp Feature is selected.
 *  0b0..One-Step Timestamping feature is not selected
 *  0b1..One-Step Timestamping feature is selected
 */
#define ENET_QOS_MAC_HW_FEAT_OSTEN(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_OSTEN_SHIFT)) & ENET_QOS_MAC_HW_FEAT_OSTEN_MASK)

#define ENET_QOS_MAC_HW_FEAT_PTOEN_MASK          (0x1000U)
#define ENET_QOS_MAC_HW_FEAT_PTOEN_SHIFT         (12U)
/*! PTOEN - PTP Offload Enable This bit is set to 1 when the Enable PTP Timestamp Offload Feature is selected.
 *  0b0..PTP Offload feature is not selected
 *  0b1..PTP Offload feature is selected
 */
#define ENET_QOS_MAC_HW_FEAT_PTOEN(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_PTOEN_SHIFT)) & ENET_QOS_MAC_HW_FEAT_PTOEN_MASK)

#define ENET_QOS_MAC_HW_FEAT_RXCHCNT_MASK        (0xF000U)
#define ENET_QOS_MAC_HW_FEAT_RXCHCNT_SHIFT       (12U)
/*! RXCHCNT - Number of DMA Receive Channels This field indicates the number of DMA Receive channels:
 *  0b0000..1 MTL Rx Channel
 *  0b0001..2 MTL Rx Channels
 *  0b0010..3 MTL Rx Channels
 *  0b0011..4 MTL Rx Channels
 *  0b0100..5 MTL Rx Channels
 *  0b0101..Reserved
 *  0b0110..Reserved
 *  0b0111..Reserved
 */
#define ENET_QOS_MAC_HW_FEAT_RXCHCNT(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_RXCHCNT_SHIFT)) & ENET_QOS_MAC_HW_FEAT_RXCHCNT_MASK)

#define ENET_QOS_MAC_HW_FEAT_TSSEL_MASK          (0x1000U)
#define ENET_QOS_MAC_HW_FEAT_TSSEL_SHIFT         (12U)
/*! TSSEL - IEEE 1588-2008 Timestamp Enabled This bit is set to 1 when the Enable IEEE 1588 Timestamp Support option is selected
 *  0b0..IEEE 1588-2008 Timestamp Enable option is not selected
 *  0b1..IEEE 1588-2008 Timestamp Enable option is selected
 */
#define ENET_QOS_MAC_HW_FEAT_TSSEL(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_TSSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_TSSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_ADVTHWORD_MASK      (0x2000U)
#define ENET_QOS_MAC_HW_FEAT_ADVTHWORD_SHIFT     (13U)
/*! ADVTHWORD - IEEE 1588 High Word Register Enable This bit is set to 1 when the Add IEEE 1588 Higher Word Register option is selected
 *  0b0..IEEE 1588 High Word Register option is not selected
 *  0b1..IEEE 1588 High Word Register option is selected
 */
#define ENET_QOS_MAC_HW_FEAT_ADVTHWORD(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_ADVTHWORD_SHIFT)) & ENET_QOS_MAC_HW_FEAT_ADVTHWORD_MASK)

#define ENET_QOS_MAC_HW_FEAT_EEESEL_MASK         (0x2000U)
#define ENET_QOS_MAC_HW_FEAT_EEESEL_SHIFT        (13U)
/*! EEESEL - Energy Efficient Ethernet Enabled This bit is set to 1 when the Enable Energy Efficient
 *    Ethernet (EEE) option is selected
 *  0b0..Energy Efficient Ethernet Enable option is not selected
 *  0b1..Energy Efficient Ethernet Enable option is selected
 */
#define ENET_QOS_MAC_HW_FEAT_EEESEL(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_EEESEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_EEESEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_FRPES_MASK          (0x6000U)
#define ENET_QOS_MAC_HW_FEAT_FRPES_SHIFT         (13U)
/*! FRPES - Flexible Receive Parser Table Entries size This field indicates the Max Number of Parser
 *    Entries supported by Flexible Receive Parser.
 *  0b00..64 Entries
 *  0b01..128 Entries
 *  0b10..256 Entries
 *  0b11..Reserved
 */
#define ENET_QOS_MAC_HW_FEAT_FRPES(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_FRPES_SHIFT)) & ENET_QOS_MAC_HW_FEAT_FRPES_MASK)

#define ENET_QOS_MAC_HW_FEAT_ADDR64_MASK         (0xC000U)
#define ENET_QOS_MAC_HW_FEAT_ADDR64_SHIFT        (14U)
/*! ADDR64 - Address Width.
 *  0b00..32
 *  0b01..40
 *  0b10..48
 *  0b11..Reserved
 */
#define ENET_QOS_MAC_HW_FEAT_ADDR64(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_ADDR64_SHIFT)) & ENET_QOS_MAC_HW_FEAT_ADDR64_MASK)

#define ENET_QOS_MAC_HW_FEAT_TXCOESEL_MASK       (0x4000U)
#define ENET_QOS_MAC_HW_FEAT_TXCOESEL_SHIFT      (14U)
/*! TXCOESEL - Transmit Checksum Offload Enabled This bit is set to 1 when the Enable Transmit
 *    TCP/IP Checksum Insertion option is selected
 *  0b0..Transmit Checksum Offload Enable option is not selected
 *  0b1..Transmit Checksum Offload Enable option is selected
 */
#define ENET_QOS_MAC_HW_FEAT_TXCOESEL(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_TXCOESEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_TXCOESEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_DCBEN_MASK          (0x10000U)
#define ENET_QOS_MAC_HW_FEAT_DCBEN_SHIFT         (16U)
/*! DCBEN - DCB Feature Enable This bit is set to 1 when the Enable Data Center Bridging option is selected
 *  0b0..DCB Feature is not selected
 *  0b1..DCB Feature is selected
 */
#define ENET_QOS_MAC_HW_FEAT_DCBEN(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_DCBEN_SHIFT)) & ENET_QOS_MAC_HW_FEAT_DCBEN_MASK)

#define ENET_QOS_MAC_HW_FEAT_ESTSEL_MASK         (0x10000U)
#define ENET_QOS_MAC_HW_FEAT_ESTSEL_SHIFT        (16U)
/*! ESTSEL - Enhancements to Scheduling Traffic Enable This bit is set to 1 when the Enable
 *    Enhancements to Scheduling Traffic feature is selected.
 *  0b0..Enable Enhancements to Scheduling Traffic feature is not selected
 *  0b1..Enable Enhancements to Scheduling Traffic feature is selected
 */
#define ENET_QOS_MAC_HW_FEAT_ESTSEL(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_ESTSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_ESTSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_RXCOESEL_MASK       (0x10000U)
#define ENET_QOS_MAC_HW_FEAT_RXCOESEL_SHIFT      (16U)
/*! RXCOESEL - Receive Checksum Offload Enabled This bit is set to 1 when the Enable Receive TCP/IP Checksum Check option is selected
 *  0b0..Receive Checksum Offload Enable option is not selected
 *  0b1..Receive Checksum Offload Enable option is selected
 */
#define ENET_QOS_MAC_HW_FEAT_RXCOESEL(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_RXCOESEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_RXCOESEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_ESTDEP_MASK         (0xE0000U)
#define ENET_QOS_MAC_HW_FEAT_ESTDEP_SHIFT        (17U)
/*! ESTDEP - Depth of the Gate Control List This field indicates the depth of Gate Control list expressed as Log2(DWC_EQOS_EST_DEP)-5
 *  0b000..No Depth configured
 *  0b001..64
 *  0b010..128
 *  0b011..256
 *  0b100..512
 *  0b101..1024
 *  0b110..Reserved
 */
#define ENET_QOS_MAC_HW_FEAT_ESTDEP(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_ESTDEP_SHIFT)) & ENET_QOS_MAC_HW_FEAT_ESTDEP_MASK)

#define ENET_QOS_MAC_HW_FEAT_SPHEN_MASK          (0x20000U)
#define ENET_QOS_MAC_HW_FEAT_SPHEN_SHIFT         (17U)
/*! SPHEN - Split Header Feature Enable This bit is set to 1 when the Enable Split Header Structure option is selected
 *  0b0..Split Header Feature is not selected
 *  0b1..Split Header Feature is selected
 */
#define ENET_QOS_MAC_HW_FEAT_SPHEN(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_SPHEN_SHIFT)) & ENET_QOS_MAC_HW_FEAT_SPHEN_MASK)

#define ENET_QOS_MAC_HW_FEAT_ADDMACADRSEL_MASK   (0x7C0000U)
#define ENET_QOS_MAC_HW_FEAT_ADDMACADRSEL_SHIFT  (18U)
/*! ADDMACADRSEL - MAC Addresses 1-31 Selected This bit is set to 1 when the non-zero value is
 *    selected for Enable Additional 1-31 MAC Address Registers option
 */
#define ENET_QOS_MAC_HW_FEAT_ADDMACADRSEL(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_ADDMACADRSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_ADDMACADRSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_TSOEN_MASK          (0x40000U)
#define ENET_QOS_MAC_HW_FEAT_TSOEN_SHIFT         (18U)
/*! TSOEN - TCP Segmentation Offload Enable This bit is set to 1 when the Enable TCP Segmentation
 *    Offloading for TCP/IP Packets option is selected
 *  0b0..TCP Segmentation Offload Feature is not selected
 *  0b1..TCP Segmentation Offload Feature is selected
 */
#define ENET_QOS_MAC_HW_FEAT_TSOEN(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_TSOEN_SHIFT)) & ENET_QOS_MAC_HW_FEAT_TSOEN_MASK)

#define ENET_QOS_MAC_HW_FEAT_TXCHCNT_MASK        (0x3C0000U)
#define ENET_QOS_MAC_HW_FEAT_TXCHCNT_SHIFT       (18U)
/*! TXCHCNT - Number of DMA Transmit Channels This field indicates the number of DMA Transmit channels:
 *  0b0000..1 MTL Tx Channel
 *  0b0001..2 MTL Tx Channels
 *  0b0010..3 MTL Tx Channels
 *  0b0011..4 MTL Tx Channels
 *  0b0100..5 MTL Tx Channels
 *  0b0101..Reserved
 *  0b0110..Reserved
 *  0b0111..Reserved
 */
#define ENET_QOS_MAC_HW_FEAT_TXCHCNT(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_TXCHCNT_SHIFT)) & ENET_QOS_MAC_HW_FEAT_TXCHCNT_MASK)

#define ENET_QOS_MAC_HW_FEAT_DBGMEMA_MASK        (0x80000U)
#define ENET_QOS_MAC_HW_FEAT_DBGMEMA_SHIFT       (19U)
/*! DBGMEMA - DMA Debug Registers Enable This bit is set to 1 when the Debug Mode Enable option is selected
 *  0b0..DMA Debug Registers option is not selected
 *  0b1..DMA Debug Registers option is selected
 */
#define ENET_QOS_MAC_HW_FEAT_DBGMEMA(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_DBGMEMA_SHIFT)) & ENET_QOS_MAC_HW_FEAT_DBGMEMA_MASK)

#define ENET_QOS_MAC_HW_FEAT_AVSEL_MASK          (0x100000U)
#define ENET_QOS_MAC_HW_FEAT_AVSEL_SHIFT         (20U)
/*! AVSEL - AV Feature Enable This bit is set to 1 when the Enable Audio Video Bridging option is selected.
 *  0b0..AV Feature is not selected
 *  0b1..AV Feature is selected
 */
#define ENET_QOS_MAC_HW_FEAT_AVSEL(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_AVSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_AVSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_ESTWID_MASK         (0x300000U)
#define ENET_QOS_MAC_HW_FEAT_ESTWID_SHIFT        (20U)
/*! ESTWID - Width of the Time Interval field in the Gate Control List This field indicates the
 *    width of the Configured Time Interval Field
 *  0b00..Width not configured
 *  0b01..16
 *  0b10..20
 *  0b11..24
 */
#define ENET_QOS_MAC_HW_FEAT_ESTWID(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_ESTWID_SHIFT)) & ENET_QOS_MAC_HW_FEAT_ESTWID_MASK)

#define ENET_QOS_MAC_HW_FEAT_RAVSEL_MASK         (0x200000U)
#define ENET_QOS_MAC_HW_FEAT_RAVSEL_SHIFT        (21U)
/*! RAVSEL - Rx Side Only AV Feature Enable This bit is set to 1 when the Enable Audio Video
 *    Bridging option on Rx Side Only is selected.
 *  0b0..Rx Side Only AV Feature is not selected
 *  0b1..Rx Side Only AV Feature is selected
 */
#define ENET_QOS_MAC_HW_FEAT_RAVSEL(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_RAVSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_RAVSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_MACADR32SEL_MASK    (0x800000U)
#define ENET_QOS_MAC_HW_FEAT_MACADR32SEL_SHIFT   (23U)
/*! MACADR32SEL - MAC Addresses 32-63 Selected This bit is set to 1 when the Enable Additional 32
 *    MAC Address Registers (32-63) option is selected
 *  0b0..MAC Addresses 32-63 Select option is not selected
 *  0b1..MAC Addresses 32-63 Select option is selected
 */
#define ENET_QOS_MAC_HW_FEAT_MACADR32SEL(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_MACADR32SEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_MACADR32SEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_POUOST_MASK         (0x800000U)
#define ENET_QOS_MAC_HW_FEAT_POUOST_SHIFT        (23U)
/*! POUOST - One Step for PTP over UDP/IP Feature Enable This bit is set to 1 when the Enable One
 *    step timestamp for PTP over UDP/IP feature is selected.
 *  0b0..One Step for PTP over UDP/IP Feature is not selected
 *  0b1..One Step for PTP over UDP/IP Feature is selected
 */
#define ENET_QOS_MAC_HW_FEAT_POUOST(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_POUOST_SHIFT)) & ENET_QOS_MAC_HW_FEAT_POUOST_MASK)

#define ENET_QOS_MAC_HW_FEAT_HASHTBLSZ_MASK      (0x3000000U)
#define ENET_QOS_MAC_HW_FEAT_HASHTBLSZ_SHIFT     (24U)
/*! HASHTBLSZ - Hash Table Size This field indicates the size of the hash table:
 *  0b00..No hash table
 *  0b01..64
 *  0b10..128
 *  0b11..256
 */
#define ENET_QOS_MAC_HW_FEAT_HASHTBLSZ(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_HASHTBLSZ_SHIFT)) & ENET_QOS_MAC_HW_FEAT_HASHTBLSZ_MASK)

#define ENET_QOS_MAC_HW_FEAT_MACADR64SEL_MASK    (0x1000000U)
#define ENET_QOS_MAC_HW_FEAT_MACADR64SEL_SHIFT   (24U)
/*! MACADR64SEL - MAC Addresses 64-127 Selected This bit is set to 1 when the Enable Additional 64
 *    MAC Address Registers (64-127) option is selected
 *  0b0..MAC Addresses 64-127 Select option is not selected
 *  0b1..MAC Addresses 64-127 Select option is selected
 */
#define ENET_QOS_MAC_HW_FEAT_MACADR64SEL(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_MACADR64SEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_MACADR64SEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_PPSOUTNUM_MASK      (0x7000000U)
#define ENET_QOS_MAC_HW_FEAT_PPSOUTNUM_SHIFT     (24U)
/*! PPSOUTNUM - Number of PPS Outputs This field indicates the number of PPS outputs:
 *  0b000..No PPS output
 *  0b001..1 PPS output
 *  0b010..2 PPS output
 *  0b011..3 PPS output
 *  0b100..4 PPS output
 *  0b101..Reserved
 */
#define ENET_QOS_MAC_HW_FEAT_PPSOUTNUM(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_PPSOUTNUM_SHIFT)) & ENET_QOS_MAC_HW_FEAT_PPSOUTNUM_MASK)

#define ENET_QOS_MAC_HW_FEAT_TSSTSSEL_MASK       (0x6000000U)
#define ENET_QOS_MAC_HW_FEAT_TSSTSSEL_SHIFT      (25U)
/*! TSSTSSEL - Timestamp System Time Source This bit indicates the source of the Timestamp system
 *    time: This bit is set to 1 when the Enable IEEE 1588 Timestamp Support option is selected
 *  0b00..Reserved
 *  0b01..Internal
 *  0b10..External
 *  0b11..Both
 */
#define ENET_QOS_MAC_HW_FEAT_TSSTSSEL(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_TSSTSSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_TSSTSSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_FPESEL_MASK         (0x4000000U)
#define ENET_QOS_MAC_HW_FEAT_FPESEL_SHIFT        (26U)
/*! FPESEL - Frame Preemption Enable This bit is set to 1 when the Enable Frame preemption feature is selected.
 *  0b0..Frame Preemption Enable feature is not selected
 *  0b1..Frame Preemption Enable feature is selected
 */
#define ENET_QOS_MAC_HW_FEAT_FPESEL(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_FPESEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_FPESEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_L3L4FNUM_MASK       (0x78000000U)
#define ENET_QOS_MAC_HW_FEAT_L3L4FNUM_SHIFT      (27U)
/*! L3L4FNUM - Total number of L3 or L4 Filters This field indicates the total number of L3 or L4 filters:
 *  0b0000..No L3 or L4 Filter
 *  0b0001..1 L3 or L4 Filter
 *  0b0010..2 L3 or L4 Filters
 *  0b0011..3 L3 or L4 Filters
 *  0b0100..4 L3 or L4 Filters
 *  0b0101..5 L3 or L4 Filters
 *  0b0110..6 L3 or L4 Filters
 *  0b0111..7 L3 or L4 Filters
 *  0b1000..8 L3 or L4 Filters
 */
#define ENET_QOS_MAC_HW_FEAT_L3L4FNUM(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_L3L4FNUM_SHIFT)) & ENET_QOS_MAC_HW_FEAT_L3L4FNUM_MASK)

#define ENET_QOS_MAC_HW_FEAT_SAVLANINS_MASK      (0x8000000U)
#define ENET_QOS_MAC_HW_FEAT_SAVLANINS_SHIFT     (27U)
/*! SAVLANINS - Source Address or VLAN Insertion Enable This bit is set to 1 when the Enable SA and
 *    VLAN Insertion on Tx option is selected
 *  0b0..Source Address or VLAN Insertion Enable option is not selected
 *  0b1..Source Address or VLAN Insertion Enable option is selected
 */
#define ENET_QOS_MAC_HW_FEAT_SAVLANINS(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_SAVLANINS_SHIFT)) & ENET_QOS_MAC_HW_FEAT_SAVLANINS_MASK)

#define ENET_QOS_MAC_HW_FEAT_TBSSEL_MASK         (0x8000000U)
#define ENET_QOS_MAC_HW_FEAT_TBSSEL_SHIFT        (27U)
/*! TBSSEL - Time Based Scheduling Enable This bit is set to 1 when the Time Based Scheduling feature is selected.
 *  0b0..Time Based Scheduling Enable feature is not selected
 *  0b1..Time Based Scheduling Enable feature is selected
 */
#define ENET_QOS_MAC_HW_FEAT_TBSSEL(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_TBSSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_TBSSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_ACTPHYSEL_MASK      (0x70000000U)
#define ENET_QOS_MAC_HW_FEAT_ACTPHYSEL_SHIFT     (28U)
/*! ACTPHYSEL - Active PHY Selected When you have multiple PHY interfaces in your configuration,
 *    this field indicates the sampled value of phy_intf_sel_i during reset de-assertion.
 *  0b000..GMII or MII
 *  0b001..RGMII
 *  0b010..SGMII
 *  0b011..TBI
 *  0b100..RMII
 *  0b101..RTBI
 *  0b110..SMII
 *  0b111..RevMII
 */
#define ENET_QOS_MAC_HW_FEAT_ACTPHYSEL(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_ACTPHYSEL_SHIFT)) & ENET_QOS_MAC_HW_FEAT_ACTPHYSEL_MASK)

#define ENET_QOS_MAC_HW_FEAT_ASP_MASK            (0x30000000U)
#define ENET_QOS_MAC_HW_FEAT_ASP_SHIFT           (28U)
/*! ASP - Automotive Safety Package Following are the encoding for the different Safety features
 *  0b00..No Safety features selected
 *  0b01..Only "ECC protection for external memory" feature is selected
 *  0b10..All the Automotive Safety features are selected without the "Parity Port Enable for external interface" feature
 *  0b11..All the Automotive Safety features are selected with the "Parity Port Enable for external interface" feature
 */
#define ENET_QOS_MAC_HW_FEAT_ASP(x)              (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_ASP_SHIFT)) & ENET_QOS_MAC_HW_FEAT_ASP_MASK)

#define ENET_QOS_MAC_HW_FEAT_AUXSNAPNUM_MASK     (0x70000000U)
#define ENET_QOS_MAC_HW_FEAT_AUXSNAPNUM_SHIFT    (28U)
/*! AUXSNAPNUM - Number of Auxiliary Snapshot Inputs This field indicates the number of auxiliary snapshot inputs:
 *  0b000..No auxiliary input
 *  0b001..1 auxiliary input
 *  0b010..2 auxiliary input
 *  0b011..3 auxiliary input
 *  0b100..4 auxiliary input
 *  0b101..Reserved
 */
#define ENET_QOS_MAC_HW_FEAT_AUXSNAPNUM(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_HW_FEAT_AUXSNAPNUM_SHIFT)) & ENET_QOS_MAC_HW_FEAT_AUXSNAPNUM_MASK)
/*! @} */

/*! @name MAC_MDIO_ADDRESS - MDIO Address */
/*! @{ */

#define ENET_QOS_MAC_MDIO_ADDRESS_GB_MASK        (0x1U)
#define ENET_QOS_MAC_MDIO_ADDRESS_GB_SHIFT       (0U)
/*! GB - GMII Busy The application sets this bit to instruct the SMA to initiate a Read or Write access to the MDIO slave.
 *  0b0..GMII Busy is disabled
 *  0b1..GMII Busy is enabled
 */
#define ENET_QOS_MAC_MDIO_ADDRESS_GB(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MDIO_ADDRESS_GB_SHIFT)) & ENET_QOS_MAC_MDIO_ADDRESS_GB_MASK)

#define ENET_QOS_MAC_MDIO_ADDRESS_C45E_MASK      (0x2U)
#define ENET_QOS_MAC_MDIO_ADDRESS_C45E_SHIFT     (1U)
/*! C45E - Clause 45 PHY Enable When this bit is set, Clause 45 capable PHY is connected to MDIO.
 *  0b0..Clause 45 PHY is disabled
 *  0b1..Clause 45 PHY is enabled
 */
#define ENET_QOS_MAC_MDIO_ADDRESS_C45E(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MDIO_ADDRESS_C45E_SHIFT)) & ENET_QOS_MAC_MDIO_ADDRESS_C45E_MASK)

#define ENET_QOS_MAC_MDIO_ADDRESS_GOC_0_MASK     (0x4U)
#define ENET_QOS_MAC_MDIO_ADDRESS_GOC_0_SHIFT    (2U)
/*! GOC_0 - GMII Operation Command 0 This is the lower bit of the operation command to the PHY or RevMII.
 *  0b0..GMII Operation Command 0 is disabled
 *  0b1..GMII Operation Command 0 is enabled
 */
#define ENET_QOS_MAC_MDIO_ADDRESS_GOC_0(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MDIO_ADDRESS_GOC_0_SHIFT)) & ENET_QOS_MAC_MDIO_ADDRESS_GOC_0_MASK)

#define ENET_QOS_MAC_MDIO_ADDRESS_GOC_1_MASK     (0x8U)
#define ENET_QOS_MAC_MDIO_ADDRESS_GOC_1_SHIFT    (3U)
/*! GOC_1 - GMII Operation Command 1 This bit is higher bit of the operation command to the PHY or
 *    RevMII, GOC_1 and GOC_O is encoded as follows: - 00: Reserved - 01: Write - 10: Post Read
 *    Increment Address for Clause 45 PHY - 11: Read When Clause 22 PHY or RevMII is enabled, only Write
 *    and Read commands are valid.
 *  0b0..GMII Operation Command 1 is disabled
 *  0b1..GMII Operation Command 1 is enabled
 */
#define ENET_QOS_MAC_MDIO_ADDRESS_GOC_1(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MDIO_ADDRESS_GOC_1_SHIFT)) & ENET_QOS_MAC_MDIO_ADDRESS_GOC_1_MASK)

#define ENET_QOS_MAC_MDIO_ADDRESS_SKAP_MASK      (0x10U)
#define ENET_QOS_MAC_MDIO_ADDRESS_SKAP_SHIFT     (4U)
/*! SKAP - Skip Address Packet When this bit is set, the SMA does not send the address packets
 *    before read, write, or post-read increment address packets.
 *  0b0..Skip Address Packet is disabled
 *  0b1..Skip Address Packet is enabled
 */
#define ENET_QOS_MAC_MDIO_ADDRESS_SKAP(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MDIO_ADDRESS_SKAP_SHIFT)) & ENET_QOS_MAC_MDIO_ADDRESS_SKAP_MASK)

#define ENET_QOS_MAC_MDIO_ADDRESS_CR_MASK        (0xF00U)
#define ENET_QOS_MAC_MDIO_ADDRESS_CR_SHIFT       (8U)
/*! CR - CSR Clock Range The CSR Clock Range selection determines the frequency of the MDC clock
 *    according to the CSR clock frequency used in your design: - 0000: CSR clock = 60-100 MHz; MDC
 *    clock = CSR clock/42 - 0001: CSR clock = 100-150 MHz; MDC clock = CSR clock/62 - 0010: CSR clock
 *    = 20-35 MHz; MDC clock = CSR clock/16 - 0011: CSR clock = 35-60 MHz; MDC clock = CSR clock/26
 *    - 0100: CSR clock = 150-250 MHz; MDC clock = CSR clock/102 - 0101: CSR clock = 250-300 MHz;
 *    MDC clock = CSR clock/124 - 0110: CSR clock = 300-500 MHz; MDC clock = CSR clock/204 - 0111: CSR
 *    clock = 500-800 MHz; MDC clock = CSR clock/324 The suggested range of CSR clock frequency
 *    applicable for each value (when Bit 11 = 0) ensures that the MDC clock is approximately between 1.
 */
#define ENET_QOS_MAC_MDIO_ADDRESS_CR(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MDIO_ADDRESS_CR_SHIFT)) & ENET_QOS_MAC_MDIO_ADDRESS_CR_MASK)

#define ENET_QOS_MAC_MDIO_ADDRESS_NTC_MASK       (0x7000U)
#define ENET_QOS_MAC_MDIO_ADDRESS_NTC_SHIFT      (12U)
/*! NTC - Number of Trailing Clocks This field controls the number of trailing clock cycles
 *    generated on gmii_mdc_o (MDC) after the end of transmission of MDIO frame.
 */
#define ENET_QOS_MAC_MDIO_ADDRESS_NTC(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MDIO_ADDRESS_NTC_SHIFT)) & ENET_QOS_MAC_MDIO_ADDRESS_NTC_MASK)

#define ENET_QOS_MAC_MDIO_ADDRESS_RDA_MASK       (0x1F0000U)
#define ENET_QOS_MAC_MDIO_ADDRESS_RDA_SHIFT      (16U)
/*! RDA - Register/Device Address These bits select the PHY register in selected Clause 22 PHY device. */
#define ENET_QOS_MAC_MDIO_ADDRESS_RDA(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MDIO_ADDRESS_RDA_SHIFT)) & ENET_QOS_MAC_MDIO_ADDRESS_RDA_MASK)

#define ENET_QOS_MAC_MDIO_ADDRESS_PA_MASK        (0x3E00000U)
#define ENET_QOS_MAC_MDIO_ADDRESS_PA_SHIFT       (21U)
/*! PA - Physical Layer Address This field indicates which Clause 22 PHY devices (out of 32 devices) the MAC is accessing. */
#define ENET_QOS_MAC_MDIO_ADDRESS_PA(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MDIO_ADDRESS_PA_SHIFT)) & ENET_QOS_MAC_MDIO_ADDRESS_PA_MASK)

#define ENET_QOS_MAC_MDIO_ADDRESS_BTB_MASK       (0x4000000U)
#define ENET_QOS_MAC_MDIO_ADDRESS_BTB_SHIFT      (26U)
/*! BTB - Back to Back transactions When this bit is set and the NTC has value greater than 0, then
 *    the MAC informs the completion of a read or write command at the end of frame transfer (before
 *    the trailing clocks are transmitted).
 *  0b0..Back to Back transactions disabled
 *  0b1..Back to Back transactions enabled
 */
#define ENET_QOS_MAC_MDIO_ADDRESS_BTB(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MDIO_ADDRESS_BTB_SHIFT)) & ENET_QOS_MAC_MDIO_ADDRESS_BTB_MASK)

#define ENET_QOS_MAC_MDIO_ADDRESS_PSE_MASK       (0x8000000U)
#define ENET_QOS_MAC_MDIO_ADDRESS_PSE_SHIFT      (27U)
/*! PSE - Preamble Suppression Enable When this bit is set, the SMA suppresses the 32-bit preamble
 *    and transmits MDIO frames with only 1 preamble bit.
 *  0b0..Preamble Suppression disabled
 *  0b1..Preamble Suppression enabled
 */
#define ENET_QOS_MAC_MDIO_ADDRESS_PSE(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MDIO_ADDRESS_PSE_SHIFT)) & ENET_QOS_MAC_MDIO_ADDRESS_PSE_MASK)
/*! @} */

/*! @name MAC_MDIO_DATA - MAC MDIO Data */
/*! @{ */

#define ENET_QOS_MAC_MDIO_DATA_GD_MASK           (0xFFFFU)
#define ENET_QOS_MAC_MDIO_DATA_GD_SHIFT          (0U)
/*! GD - GMII Data This field contains the 16-bit data value read from the PHY or RevMII after a
 *    Management Read operation or the 16-bit data value to be written to the PHY or RevMII before a
 *    Management Write operation.
 */
#define ENET_QOS_MAC_MDIO_DATA_GD(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MDIO_DATA_GD_SHIFT)) & ENET_QOS_MAC_MDIO_DATA_GD_MASK)

#define ENET_QOS_MAC_MDIO_DATA_RA_MASK           (0xFFFF0000U)
#define ENET_QOS_MAC_MDIO_DATA_RA_SHIFT          (16U)
/*! RA - Register Address This field is valid only when C45E is set. */
#define ENET_QOS_MAC_MDIO_DATA_RA(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MDIO_DATA_RA_SHIFT)) & ENET_QOS_MAC_MDIO_DATA_RA_MASK)
/*! @} */

/*! @name MAC_CSR_SW_CTRL - CSR Software Control */
/*! @{ */

#define ENET_QOS_MAC_CSR_SW_CTRL_RCWE_MASK       (0x1U)
#define ENET_QOS_MAC_CSR_SW_CTRL_RCWE_SHIFT      (0U)
/*! RCWE - Register Clear on Write 1 Enable When this bit is set, the access mode of some register
 *    fields changes to Clear on Write 1, the application needs to set that respective bit to 1 to
 *    clear it.
 *  0b0..Register Clear on Write 1 is disabled
 *  0b1..Register Clear on Write 1 is enabled
 */
#define ENET_QOS_MAC_CSR_SW_CTRL_RCWE(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_CSR_SW_CTRL_RCWE_SHIFT)) & ENET_QOS_MAC_CSR_SW_CTRL_RCWE_MASK)
/*! @} */

/*! @name MAC_FPE_CTRL_STS - Frame Preemption Control */
/*! @{ */

#define ENET_QOS_MAC_FPE_CTRL_STS_EFPE_MASK      (0x1U)
#define ENET_QOS_MAC_FPE_CTRL_STS_EFPE_SHIFT     (0U)
/*! EFPE - Enable Tx Frame Preemption When set Frame Preemption Tx functionality is enabled.
 *  0b0..Tx Frame Preemption is disabled
 *  0b1..Tx Frame Preemption is enabled
 */
#define ENET_QOS_MAC_FPE_CTRL_STS_EFPE(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_FPE_CTRL_STS_EFPE_SHIFT)) & ENET_QOS_MAC_FPE_CTRL_STS_EFPE_MASK)

#define ENET_QOS_MAC_FPE_CTRL_STS_SVER_MASK      (0x2U)
#define ENET_QOS_MAC_FPE_CTRL_STS_SVER_SHIFT     (1U)
/*! SVER - Send Verify mPacket When set indicates hardware to send a verify mPacket.
 *  0b0..Send Verify mPacket is disabled
 *  0b1..Send Verify mPacket is enabled
 */
#define ENET_QOS_MAC_FPE_CTRL_STS_SVER(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_FPE_CTRL_STS_SVER_SHIFT)) & ENET_QOS_MAC_FPE_CTRL_STS_SVER_MASK)

#define ENET_QOS_MAC_FPE_CTRL_STS_SRSP_MASK      (0x4U)
#define ENET_QOS_MAC_FPE_CTRL_STS_SRSP_SHIFT     (2U)
/*! SRSP - Send Respond mPacket When set indicates hardware to send a Respond mPacket.
 *  0b0..Send Respond mPacket is disabled
 *  0b1..Send Respond mPacket is enabled
 */
#define ENET_QOS_MAC_FPE_CTRL_STS_SRSP(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_FPE_CTRL_STS_SRSP_SHIFT)) & ENET_QOS_MAC_FPE_CTRL_STS_SRSP_MASK)

#define ENET_QOS_MAC_FPE_CTRL_STS_S1_SET_0_MASK  (0x8U)
#define ENET_QOS_MAC_FPE_CTRL_STS_S1_SET_0_SHIFT (3U)
/*! S1_SET_0 - Reserved, Must be set to "0". */
#define ENET_QOS_MAC_FPE_CTRL_STS_S1_SET_0(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_FPE_CTRL_STS_S1_SET_0_SHIFT)) & ENET_QOS_MAC_FPE_CTRL_STS_S1_SET_0_MASK)

#define ENET_QOS_MAC_FPE_CTRL_STS_RVER_MASK      (0x10000U)
#define ENET_QOS_MAC_FPE_CTRL_STS_RVER_SHIFT     (16U)
/*! RVER - Received Verify Frame Set when a Verify mPacket is received.
 *  0b0..Not received Verify Frame
 *  0b1..Received Verify Frame
 */
#define ENET_QOS_MAC_FPE_CTRL_STS_RVER(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_FPE_CTRL_STS_RVER_SHIFT)) & ENET_QOS_MAC_FPE_CTRL_STS_RVER_MASK)

#define ENET_QOS_MAC_FPE_CTRL_STS_RRSP_MASK      (0x20000U)
#define ENET_QOS_MAC_FPE_CTRL_STS_RRSP_SHIFT     (17U)
/*! RRSP - Received Respond Frame Set when a Respond mPacket is received.
 *  0b0..Not received Respond Frame
 *  0b1..Received Respond Frame
 */
#define ENET_QOS_MAC_FPE_CTRL_STS_RRSP(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_FPE_CTRL_STS_RRSP_SHIFT)) & ENET_QOS_MAC_FPE_CTRL_STS_RRSP_MASK)

#define ENET_QOS_MAC_FPE_CTRL_STS_TVER_MASK      (0x40000U)
#define ENET_QOS_MAC_FPE_CTRL_STS_TVER_SHIFT     (18U)
/*! TVER - Transmitted Verify Frame Set when a Verify mPacket is transmitted (triggered by setting SVER field).
 *  0b0..Not transmitted Verify Frame
 *  0b1..transmitted Verify Frame
 */
#define ENET_QOS_MAC_FPE_CTRL_STS_TVER(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_FPE_CTRL_STS_TVER_SHIFT)) & ENET_QOS_MAC_FPE_CTRL_STS_TVER_MASK)

#define ENET_QOS_MAC_FPE_CTRL_STS_TRSP_MASK      (0x80000U)
#define ENET_QOS_MAC_FPE_CTRL_STS_TRSP_SHIFT     (19U)
/*! TRSP - Transmitted Respond Frame Set when a Respond mPacket is transmitted (triggered by setting SRSP field).
 *  0b0..Not transmitted Respond Frame
 *  0b1..transmitted Respond Frame
 */
#define ENET_QOS_MAC_FPE_CTRL_STS_TRSP(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_FPE_CTRL_STS_TRSP_SHIFT)) & ENET_QOS_MAC_FPE_CTRL_STS_TRSP_MASK)
/*! @} */

/*! @name MAC_PRESN_TIME_NS - 32-bit Binary Rollover Equivalent Time */
/*! @{ */

#define ENET_QOS_MAC_PRESN_TIME_NS_MPTN_MASK     (0xFFFFFFFFU)
#define ENET_QOS_MAC_PRESN_TIME_NS_MPTN_SHIFT    (0U)
/*! MPTN - MAC 1722 Presentation Time in ns These bits indicate the value of the 32-bit binary
 *    rollover equivalent time of the PTP System Time in ns
 */
#define ENET_QOS_MAC_PRESN_TIME_NS_MPTN(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PRESN_TIME_NS_MPTN_SHIFT)) & ENET_QOS_MAC_PRESN_TIME_NS_MPTN_MASK)
/*! @} */

/*! @name MAC_PRESN_TIME_UPDT - MAC 1722 Presentation Time */
/*! @{ */

#define ENET_QOS_MAC_PRESN_TIME_UPDT_MPTU_MASK   (0xFFFFFFFFU)
#define ENET_QOS_MAC_PRESN_TIME_UPDT_MPTU_SHIFT  (0U)
/*! MPTU - MAC 1722 Presentation Time Update This field holds the init value or the update value for the presentation time. */
#define ENET_QOS_MAC_PRESN_TIME_UPDT_MPTU(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PRESN_TIME_UPDT_MPTU_SHIFT)) & ENET_QOS_MAC_PRESN_TIME_UPDT_MPTU_MASK)
/*! @} */

/*! @name HIGH - MAC Address0 High..MAC Address63 High */
/*! @{ */

#define ENET_QOS_HIGH_ADDRHI_MASK                (0xFFFFU)
#define ENET_QOS_HIGH_ADDRHI_SHIFT               (0U)
/*! ADDRHI - MAC ADDRESS12 [47:32] This field contains the upper 16 bits[47:32] of the thirteenth 6-byte MAC address. */
#define ENET_QOS_HIGH_ADDRHI(x)                  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_HIGH_ADDRHI_SHIFT)) & ENET_QOS_HIGH_ADDRHI_MASK)

#define ENET_QOS_HIGH_DCS_MASK                   (0x1F0000U)  /* Merged from fields with different position or width, of widths (3, 5), largest definition used */
#define ENET_QOS_HIGH_DCS_SHIFT                  (16U)
/*! DCS - DMA Channel Select If the PDC bit of MAC_EXT_CONFIGURATION register is not set: This field
 *    contains the binary representation of the DMA Channel number to which an Rx packet whose DA
 *    matches the MAC Address(#i) content is routed.
 */
#define ENET_QOS_HIGH_DCS(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_HIGH_DCS_SHIFT)) & ENET_QOS_HIGH_DCS_MASK)  /* Merged from fields with different position or width, of widths (3, 5), largest definition used */

#define ENET_QOS_HIGH_MBC_MASK                   (0x3F000000U)
#define ENET_QOS_HIGH_MBC_SHIFT                  (24U)
/*! MBC - Mask Byte Control These bits are mask control bits for comparing each of the MAC Address bytes. */
#define ENET_QOS_HIGH_MBC(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_HIGH_MBC_SHIFT)) & ENET_QOS_HIGH_MBC_MASK)

#define ENET_QOS_HIGH_SA_MASK                    (0x40000000U)
#define ENET_QOS_HIGH_SA_SHIFT                   (30U)
/*! SA - Source Address When this bit is set, the MAC ADDRESS31[47:0] is used to compare with the SA
 *    fields of the received packet.
 *  0b0..Compare with Destination Address
 *  0b1..Compare with Source Address
 */
#define ENET_QOS_HIGH_SA(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_HIGH_SA_SHIFT)) & ENET_QOS_HIGH_SA_MASK)

#define ENET_QOS_HIGH_AE_MASK                    (0x80000000U)
#define ENET_QOS_HIGH_AE_SHIFT                   (31U)
/*! AE - Address Enable When this bit is set, the address filter module uses the thirteenth MAC address for perfect filtering.
 *  0b0..INVALID : This bit must be always set to 1
 *  0b1..This bit is always set to 1
 */
#define ENET_QOS_HIGH_AE(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_HIGH_AE_SHIFT)) & ENET_QOS_HIGH_AE_MASK)
/*! @} */

/* The count of ENET_QOS_HIGH */
#define ENET_QOS_HIGH_COUNT                      (64U)

/*! @name LOW - MAC Address0 Low..MAC Address63 Low */
/*! @{ */

#define ENET_QOS_LOW_ADDRLO_MASK                 (0xFFFFFFFFU)
#define ENET_QOS_LOW_ADDRLO_SHIFT                (0U)
/*! ADDRLO - MAC ADDRESS12 [31:0] This field contains the lower 32 bits of thirteenth 6-byte MAC address. */
#define ENET_QOS_LOW_ADDRLO(x)                   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_LOW_ADDRLO_SHIFT)) & ENET_QOS_LOW_ADDRLO_MASK)
/*! @} */

/* The count of ENET_QOS_LOW */
#define ENET_QOS_LOW_COUNT                       (64U)

/*! @name MAC_MMC_CONTROL - MMC Control */
/*! @{ */

#define ENET_QOS_MAC_MMC_CONTROL_CNTRST_MASK     (0x1U)
#define ENET_QOS_MAC_MMC_CONTROL_CNTRST_SHIFT    (0U)
/*! CNTRST - Counters Reset When this bit is set, all counters are reset.
 *  0b0..Counters are not reset
 *  0b1..All counters are reset
 */
#define ENET_QOS_MAC_MMC_CONTROL_CNTRST(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_CONTROL_CNTRST_SHIFT)) & ENET_QOS_MAC_MMC_CONTROL_CNTRST_MASK)

#define ENET_QOS_MAC_MMC_CONTROL_CNTSTOPRO_MASK  (0x2U)
#define ENET_QOS_MAC_MMC_CONTROL_CNTSTOPRO_SHIFT (1U)
/*! CNTSTOPRO - Counter Stop Rollover When this bit is set, the counter does not roll over to zero after reaching the maximum value.
 *  0b0..Counter Stop Rollover is disabled
 *  0b1..Counter Stop Rollover is enabled
 */
#define ENET_QOS_MAC_MMC_CONTROL_CNTSTOPRO(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_CONTROL_CNTSTOPRO_SHIFT)) & ENET_QOS_MAC_MMC_CONTROL_CNTSTOPRO_MASK)

#define ENET_QOS_MAC_MMC_CONTROL_RSTONRD_MASK    (0x4U)
#define ENET_QOS_MAC_MMC_CONTROL_RSTONRD_SHIFT   (2U)
/*! RSTONRD - Reset on Read When this bit is set, the MMC counters are reset to zero after Read (self-clearing after reset).
 *  0b0..Reset on Read is disabled
 *  0b1..Reset on Read is enabled
 */
#define ENET_QOS_MAC_MMC_CONTROL_RSTONRD(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_CONTROL_RSTONRD_SHIFT)) & ENET_QOS_MAC_MMC_CONTROL_RSTONRD_MASK)

#define ENET_QOS_MAC_MMC_CONTROL_CNTFREEZ_MASK   (0x8U)
#define ENET_QOS_MAC_MMC_CONTROL_CNTFREEZ_SHIFT  (3U)
/*! CNTFREEZ - MMC Counter Freeze When this bit is set, it freezes all MMC counters to their current value.
 *  0b0..MMC Counter Freeze is disabled
 *  0b1..MMC Counter Freeze is enabled
 */
#define ENET_QOS_MAC_MMC_CONTROL_CNTFREEZ(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_CONTROL_CNTFREEZ_SHIFT)) & ENET_QOS_MAC_MMC_CONTROL_CNTFREEZ_MASK)

#define ENET_QOS_MAC_MMC_CONTROL_CNTPRST_MASK    (0x10U)
#define ENET_QOS_MAC_MMC_CONTROL_CNTPRST_SHIFT   (4U)
/*! CNTPRST - Counters Preset When this bit is set, all counters are initialized or preset to almost
 *    full or almost half according to the CNTPRSTLVL bit.
 *  0b0..Counters Preset is disabled
 *  0b1..Counters Preset is enabled
 */
#define ENET_QOS_MAC_MMC_CONTROL_CNTPRST(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_CONTROL_CNTPRST_SHIFT)) & ENET_QOS_MAC_MMC_CONTROL_CNTPRST_MASK)

#define ENET_QOS_MAC_MMC_CONTROL_CNTPRSTLVL_MASK (0x20U)
#define ENET_QOS_MAC_MMC_CONTROL_CNTPRSTLVL_SHIFT (5U)
/*! CNTPRSTLVL - Full-Half Preset When this bit is low and the CNTPRST bit is set, all MMC counters get preset to almost-half value.
 *  0b0..Full-Half Preset is disabled
 *  0b1..Full-Half Preset is enabled
 */
#define ENET_QOS_MAC_MMC_CONTROL_CNTPRSTLVL(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_CONTROL_CNTPRSTLVL_SHIFT)) & ENET_QOS_MAC_MMC_CONTROL_CNTPRSTLVL_MASK)

#define ENET_QOS_MAC_MMC_CONTROL_UCDBC_MASK      (0x100U)
#define ENET_QOS_MAC_MMC_CONTROL_UCDBC_SHIFT     (8U)
/*! UCDBC - Update MMC Counters for Dropped Broadcast Packets Note: The CNTRST bit has a higher priority than the CNTPRST bit.
 *  0b0..Update MMC Counters for Dropped Broadcast Packets is disabled
 *  0b1..Update MMC Counters for Dropped Broadcast Packets is enabled
 */
#define ENET_QOS_MAC_MMC_CONTROL_UCDBC(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_CONTROL_UCDBC_SHIFT)) & ENET_QOS_MAC_MMC_CONTROL_UCDBC_MASK)
/*! @} */

/*! @name MAC_MMC_RX_INTERRUPT - MMC Rx Interrupt */
/*! @{ */

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXGBPKTIS_MASK (0x1U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXGBPKTIS_SHIFT (0U)
/*! RXGBPKTIS - MMC Receive Good Bad Packet Counter Interrupt Status This bit is set when the
 *    rxpacketcount_gb counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXGBPKTIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXGBPKTIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXGBPKTIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXGBOCTIS_MASK (0x2U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXGBOCTIS_SHIFT (1U)
/*! RXGBOCTIS - MMC Receive Good Bad Octet Counter Interrupt Status This bit is set when the
 *    rxoctetcount_gb counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Good Bad Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive Good Bad Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXGBOCTIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXGBOCTIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXGBOCTIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXGOCTIS_MASK (0x4U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXGOCTIS_SHIFT (2U)
/*! RXGOCTIS - MMC Receive Good Octet Counter Interrupt Status This bit is set when the
 *    rxoctetcount_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Good Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive Good Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXGOCTIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXGOCTIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXGOCTIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXBCGPIS_MASK (0x8U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXBCGPIS_SHIFT (3U)
/*! RXBCGPIS - MMC Receive Broadcast Good Packet Counter Interrupt Status This bit is set when the
 *    rxbroadcastpackets_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Broadcast Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive Broadcast Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXBCGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXBCGPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXBCGPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXMCGPIS_MASK (0x10U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXMCGPIS_SHIFT (4U)
/*! RXMCGPIS - MMC Receive Multicast Good Packet Counter Interrupt Status This bit is set when the
 *    rxmulticastpackets_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Multicast Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive Multicast Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXMCGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXMCGPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXMCGPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXCRCERPIS_MASK (0x20U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXCRCERPIS_SHIFT (5U)
/*! RXCRCERPIS - MMC Receive CRC Error Packet Counter Interrupt Status This bit is set when the
 *    rxcrcerror counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive CRC Error Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive CRC Error Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXCRCERPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXCRCERPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXCRCERPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXALGNERPIS_MASK (0x40U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXALGNERPIS_SHIFT (6U)
/*! RXALGNERPIS - MMC Receive Alignment Error Packet Counter Interrupt Status This bit is set when
 *    the rxalignmenterror counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Alignment Error Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive Alignment Error Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXALGNERPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXALGNERPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXALGNERPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXRUNTPIS_MASK (0x80U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXRUNTPIS_SHIFT (7U)
/*! RXRUNTPIS - MMC Receive Runt Packet Counter Interrupt Status This bit is set when the
 *    rxrunterror counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Runt Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive Runt Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXRUNTPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXRUNTPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXRUNTPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXJABERPIS_MASK (0x100U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXJABERPIS_SHIFT (8U)
/*! RXJABERPIS - MMC Receive Jabber Error Packet Counter Interrupt Status This bit is set when the
 *    rxjabbererror counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Jabber Error Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive Jabber Error Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXJABERPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXJABERPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXJABERPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXUSIZEGPIS_MASK (0x200U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXUSIZEGPIS_SHIFT (9U)
/*! RXUSIZEGPIS - MMC Receive Undersize Good Packet Counter Interrupt Status This bit is set when
 *    the rxundersize_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Undersize Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive Undersize Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXUSIZEGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXUSIZEGPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXUSIZEGPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXOSIZEGPIS_MASK (0x400U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXOSIZEGPIS_SHIFT (10U)
/*! RXOSIZEGPIS - MMC Receive Oversize Good Packet Counter Interrupt Status This bit is set when the
 *    rxoversize_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Oversize Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive Oversize Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXOSIZEGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXOSIZEGPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXOSIZEGPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX64OCTGBPIS_MASK (0x800U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX64OCTGBPIS_SHIFT (11U)
/*! RX64OCTGBPIS - MMC Receive 64 Octet Good Bad Packet Counter Interrupt Status This bit is set
 *    when the rx64octets_gb counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive 64 Octet Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive 64 Octet Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX64OCTGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RX64OCTGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RX64OCTGBPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX65T127OCTGBPIS_MASK (0x1000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX65T127OCTGBPIS_SHIFT (12U)
/*! RX65T127OCTGBPIS - MMC Receive 65 to 127 Octet Good Bad Packet Counter Interrupt Status This bit
 *    is set when the rx65to127octets_gb counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Receive 65 to 127 Octet Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive 65 to 127 Octet Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX65T127OCTGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RX65T127OCTGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RX65T127OCTGBPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX128T255OCTGBPIS_MASK (0x2000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX128T255OCTGBPIS_SHIFT (13U)
/*! RX128T255OCTGBPIS - MMC Receive 128 to 255 Octet Good Bad Packet Counter Interrupt Status This
 *    bit is set when the rx128to255octets_gb counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive 128 to 255 Octet Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive 128 to 255 Octet Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX128T255OCTGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RX128T255OCTGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RX128T255OCTGBPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX256T511OCTGBPIS_MASK (0x4000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX256T511OCTGBPIS_SHIFT (14U)
/*! RX256T511OCTGBPIS - MMC Receive 256 to 511 Octet Good Bad Packet Counter Interrupt Status This
 *    bit is set when the rx256to511octets_gb counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive 256 to 511 Octet Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive 256 to 511 Octet Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX256T511OCTGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RX256T511OCTGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RX256T511OCTGBPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX512T1023OCTGBPIS_MASK (0x8000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX512T1023OCTGBPIS_SHIFT (15U)
/*! RX512T1023OCTGBPIS - MMC Receive 512 to 1023 Octet Good Bad Packet Counter Interrupt Status This
 *    bit is set when the rx512to1023octets_gb counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive 512 to 1023 Octet Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive 512 to 1023 Octet Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX512T1023OCTGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RX512T1023OCTGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RX512T1023OCTGBPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX1024TMAXOCTGBPIS_MASK (0x10000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX1024TMAXOCTGBPIS_SHIFT (16U)
/*! RX1024TMAXOCTGBPIS - MMC Receive 1024 to Maximum Octet Good Bad Packet Counter Interrupt Status
 *    This bit is set when the rx1024tomaxoctets_gb counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive 1024 to Maximum Octet Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive 1024 to Maximum Octet Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RX1024TMAXOCTGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RX1024TMAXOCTGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RX1024TMAXOCTGBPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXUCGPIS_MASK (0x20000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXUCGPIS_SHIFT (17U)
/*! RXUCGPIS - MMC Receive Unicast Good Packet Counter Interrupt Status This bit is set when the
 *    rxunicastpackets_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Unicast Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive Unicast Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXUCGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXUCGPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXUCGPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXLENERPIS_MASK (0x40000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXLENERPIS_SHIFT (18U)
/*! RXLENERPIS - MMC Receive Length Error Packet Counter Interrupt Status This bit is set when the
 *    rxlengtherror counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Length Error Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive Length Error Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXLENERPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXLENERPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXLENERPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXORANGEPIS_MASK (0x80000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXORANGEPIS_SHIFT (19U)
/*! RXORANGEPIS - MMC Receive Out Of Range Error Packet Counter Interrupt Status.
 *  0b0..MMC Receive Out Of Range Error Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive Out Of Range Error Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXORANGEPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXORANGEPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXORANGEPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXPAUSPIS_MASK (0x100000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXPAUSPIS_SHIFT (20U)
/*! RXPAUSPIS - MMC Receive Pause Packet Counter Interrupt Status This bit is set when the
 *    rxpausepackets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Pause Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive Pause Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXPAUSPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXPAUSPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXPAUSPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXFOVPIS_MASK (0x200000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXFOVPIS_SHIFT (21U)
/*! RXFOVPIS - MMC Receive FIFO Overflow Packet Counter Interrupt Status This bit is set when the
 *    rxfifooverflow counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive FIFO Overflow Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive FIFO Overflow Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXFOVPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXFOVPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXFOVPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXVLANGBPIS_MASK (0x400000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXVLANGBPIS_SHIFT (22U)
/*! RXVLANGBPIS - MMC Receive VLAN Good Bad Packet Counter Interrupt Status This bit is set when the
 *    rxvlanpackets_gb counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive VLAN Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive VLAN Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXVLANGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXVLANGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXVLANGBPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXWDOGPIS_MASK (0x800000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXWDOGPIS_SHIFT (23U)
/*! RXWDOGPIS - MMC Receive Watchdog Error Packet Counter Interrupt Status This bit is set when the
 *    rxwatchdog error counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Watchdog Error Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive Watchdog Error Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXWDOGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXWDOGPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXWDOGPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXRCVERRPIS_MASK (0x1000000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXRCVERRPIS_SHIFT (24U)
/*! RXRCVERRPIS - MMC Receive Error Packet Counter Interrupt Status This bit is set when the
 *    rxrcverror counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Error Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive Error Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXRCVERRPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXRCVERRPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXRCVERRPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXCTRLPIS_MASK (0x2000000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXCTRLPIS_SHIFT (25U)
/*! RXCTRLPIS - MMC Receive Control Packet Counter Interrupt Status This bit is set when the
 *    rxctrlpackets_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Control Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive Control Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXCTRLPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXCTRLPIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXCTRLPIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXLPIUSCIS_MASK (0x4000000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXLPIUSCIS_SHIFT (26U)
/*! RXLPIUSCIS - MMC Receive LPI microsecond counter interrupt status This bit is set when the
 *    Rx_LPI_USEC_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive LPI microsecond Counter Interrupt Status not detected
 *  0b1..MMC Receive LPI microsecond Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXLPIUSCIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXLPIUSCIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXLPIUSCIS_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXLPITRCIS_MASK (0x8000000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXLPITRCIS_SHIFT (27U)
/*! RXLPITRCIS - MMC Receive LPI transition counter interrupt status This bit is set when the
 *    Rx_LPI_Tran_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive LPI transition Counter Interrupt Status not detected
 *  0b1..MMC Receive LPI transition Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_RXLPITRCIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_RXLPITRCIS_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_RXLPITRCIS_MASK)
/*! @} */

/*! @name MAC_MMC_TX_INTERRUPT - MMC Tx Interrupt */
/*! @{ */

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGBOCTIS_MASK (0x1U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGBOCTIS_SHIFT (0U)
/*! TXGBOCTIS - MMC Transmit Good Bad Octet Counter Interrupt Status This bit is set when the
 *    txoctetcount_gb counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Good Bad Octet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Good Bad Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGBOCTIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGBOCTIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGBOCTIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGBPKTIS_MASK (0x2U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGBPKTIS_SHIFT (1U)
/*! TXGBPKTIS - MMC Transmit Good Bad Packet Counter Interrupt Status This bit is set when the
 *    txpacketcount_gb counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGBPKTIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGBPKTIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGBPKTIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXBCGPIS_MASK (0x4U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXBCGPIS_SHIFT (2U)
/*! TXBCGPIS - MMC Transmit Broadcast Good Packet Counter Interrupt Status This bit is set when the
 *    txbroadcastpackets_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Broadcast Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Broadcast Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXBCGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXBCGPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXBCGPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXMCGPIS_MASK (0x8U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXMCGPIS_SHIFT (3U)
/*! TXMCGPIS - MMC Transmit Multicast Good Packet Counter Interrupt Status This bit is set when the
 *    txmulticastpackets_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Multicast Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Multicast Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXMCGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXMCGPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXMCGPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX64OCTGBPIS_MASK (0x10U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX64OCTGBPIS_SHIFT (4U)
/*! TX64OCTGBPIS - MMC Transmit 64 Octet Good Bad Packet Counter Interrupt Status This bit is set
 *    when the tx64octets_gb counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit 64 Octet Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit 64 Octet Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX64OCTGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TX64OCTGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TX64OCTGBPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX65T127OCTGBPIS_MASK (0x20U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX65T127OCTGBPIS_SHIFT (5U)
/*! TX65T127OCTGBPIS - MMC Transmit 65 to 127 Octet Good Bad Packet Counter Interrupt Status This
 *    bit is set when the tx65to127octets_gb counter reaches half the maximum value, and also when it
 *    reaches the maximum value.
 *  0b0..MMC Transmit 65 to 127 Octet Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit 65 to 127 Octet Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX65T127OCTGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TX65T127OCTGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TX65T127OCTGBPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX128T255OCTGBPIS_MASK (0x40U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX128T255OCTGBPIS_SHIFT (6U)
/*! TX128T255OCTGBPIS - MMC Transmit 128 to 255 Octet Good Bad Packet Counter Interrupt Status This
 *    bit is set when the tx128to255octets_gb counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Transmit 128 to 255 Octet Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit 128 to 255 Octet Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX128T255OCTGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TX128T255OCTGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TX128T255OCTGBPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX256T511OCTGBPIS_MASK (0x80U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX256T511OCTGBPIS_SHIFT (7U)
/*! TX256T511OCTGBPIS - MMC Transmit 256 to 511 Octet Good Bad Packet Counter Interrupt Status This
 *    bit is set when the tx256to511octets_gb counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Transmit 256 to 511 Octet Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit 256 to 511 Octet Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX256T511OCTGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TX256T511OCTGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TX256T511OCTGBPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX512T1023OCTGBPIS_MASK (0x100U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX512T1023OCTGBPIS_SHIFT (8U)
/*! TX512T1023OCTGBPIS - MMC Transmit 512 to 1023 Octet Good Bad Packet Counter Interrupt Status
 *    This bit is set when the tx512to1023octets_gb counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Transmit 512 to 1023 Octet Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit 512 to 1023 Octet Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX512T1023OCTGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TX512T1023OCTGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TX512T1023OCTGBPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX1024TMAXOCTGBPIS_MASK (0x200U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX1024TMAXOCTGBPIS_SHIFT (9U)
/*! TX1024TMAXOCTGBPIS - MMC Transmit 1024 to Maximum Octet Good Bad Packet Counter Interrupt Status
 *    This bit is set when the tx1024tomaxoctets_gb counter reaches half of the maximum value or
 *    the maximum value.
 *  0b0..MMC Transmit 1024 to Maximum Octet Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit 1024 to Maximum Octet Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TX1024TMAXOCTGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TX1024TMAXOCTGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TX1024TMAXOCTGBPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXUCGBPIS_MASK (0x400U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXUCGBPIS_SHIFT (10U)
/*! TXUCGBPIS - MMC Transmit Unicast Good Bad Packet Counter Interrupt Status This bit is set when
 *    the txunicastpackets_gb counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Unicast Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Unicast Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXUCGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXUCGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXUCGBPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXMCGBPIS_MASK (0x800U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXMCGBPIS_SHIFT (11U)
/*! TXMCGBPIS - MMC Transmit Multicast Good Bad Packet Counter Interrupt Status The bit is set when
 *    the txmulticastpackets_gb counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Multicast Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Multicast Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXMCGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXMCGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXMCGBPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXBCGBPIS_MASK (0x1000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXBCGBPIS_SHIFT (12U)
/*! TXBCGBPIS - MMC Transmit Broadcast Good Bad Packet Counter Interrupt Status This bit is set when
 *    the txbroadcastpackets_gb counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Broadcast Good Bad Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Broadcast Good Bad Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXBCGBPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXBCGBPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXBCGBPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXUFLOWERPIS_MASK (0x2000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXUFLOWERPIS_SHIFT (13U)
/*! TXUFLOWERPIS - MMC Transmit Underflow Error Packet Counter Interrupt Status This bit is set when
 *    the txunderflowerror counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Underflow Error Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Underflow Error Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXUFLOWERPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXUFLOWERPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXUFLOWERPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXSCOLGPIS_MASK (0x4000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXSCOLGPIS_SHIFT (14U)
/*! TXSCOLGPIS - MMC Transmit Single Collision Good Packet Counter Interrupt Status This bit is set
 *    when the txsinglecol_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Single Collision Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Single Collision Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXSCOLGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXSCOLGPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXSCOLGPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXMCOLGPIS_MASK (0x8000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXMCOLGPIS_SHIFT (15U)
/*! TXMCOLGPIS - MMC Transmit Multiple Collision Good Packet Counter Interrupt Status This bit is
 *    set when the txmulticol_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Multiple Collision Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Multiple Collision Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXMCOLGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXMCOLGPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXMCOLGPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXDEFPIS_MASK (0x10000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXDEFPIS_SHIFT (16U)
/*! TXDEFPIS - MMC Transmit Deferred Packet Counter Interrupt Status This bit is set when the
 *    txdeferred counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Deferred Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Deferred Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXDEFPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXDEFPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXDEFPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXLATCOLPIS_MASK (0x20000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXLATCOLPIS_SHIFT (17U)
/*! TXLATCOLPIS - MMC Transmit Late Collision Packet Counter Interrupt Status This bit is set when
 *    the txlatecol counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Late Collision Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Late Collision Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXLATCOLPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXLATCOLPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXLATCOLPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXEXCOLPIS_MASK (0x40000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXEXCOLPIS_SHIFT (18U)
/*! TXEXCOLPIS - MMC Transmit Excessive Collision Packet Counter Interrupt Status This bit is set
 *    when the txexesscol counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Excessive Collision Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Excessive Collision Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXEXCOLPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXEXCOLPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXEXCOLPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXCARERPIS_MASK (0x80000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXCARERPIS_SHIFT (19U)
/*! TXCARERPIS - MMC Transmit Carrier Error Packet Counter Interrupt Status This bit is set when the
 *    txcarriererror counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Carrier Error Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Carrier Error Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXCARERPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXCARERPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXCARERPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGOCTIS_MASK (0x100000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGOCTIS_SHIFT (20U)
/*! TXGOCTIS - MMC Transmit Good Octet Counter Interrupt Status This bit is set when the
 *    txoctetcount_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Good Octet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Good Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGOCTIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGOCTIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGOCTIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGPKTIS_MASK (0x200000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGPKTIS_SHIFT (21U)
/*! TXGPKTIS - MMC Transmit Good Packet Counter Interrupt Status This bit is set when the
 *    txpacketcount_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGPKTIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGPKTIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXGPKTIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXEXDEFPIS_MASK (0x400000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXEXDEFPIS_SHIFT (22U)
/*! TXEXDEFPIS - MMC Transmit Excessive Deferral Packet Counter Interrupt Status This bit is set
 *    when the txexcessdef counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Excessive Deferral Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Excessive Deferral Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXEXDEFPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXEXDEFPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXEXDEFPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXPAUSPIS_MASK (0x800000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXPAUSPIS_SHIFT (23U)
/*! TXPAUSPIS - MMC Transmit Pause Packet Counter Interrupt Status This bit is set when the
 *    txpausepacketserror counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Pause Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Pause Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXPAUSPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXPAUSPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXPAUSPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXVLANGPIS_MASK (0x1000000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXVLANGPIS_SHIFT (24U)
/*! TXVLANGPIS - MMC Transmit VLAN Good Packet Counter Interrupt Status This bit is set when the
 *    txvlanpackets_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit VLAN Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit VLAN Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXVLANGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXVLANGPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXVLANGPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXOSIZEGPIS_MASK (0x2000000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXOSIZEGPIS_SHIFT (25U)
/*! TXOSIZEGPIS - MMC Transmit Oversize Good Packet Counter Interrupt Status This bit is set when
 *    the txoversize_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Oversize Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Transmit Oversize Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXOSIZEGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXOSIZEGPIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXOSIZEGPIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXLPIUSCIS_MASK (0x4000000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXLPIUSCIS_SHIFT (26U)
/*! TXLPIUSCIS - MMC Transmit LPI microsecond counter interrupt status This bit is set when the
 *    Tx_LPI_USEC_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit LPI microsecond Counter Interrupt Status not detected
 *  0b1..MMC Transmit LPI microsecond Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXLPIUSCIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXLPIUSCIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXLPIUSCIS_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXLPITRCIS_MASK (0x8000000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXLPITRCIS_SHIFT (27U)
/*! TXLPITRCIS - MMC Transmit LPI transition counter interrupt status This bit is set when the
 *    Tx_LPI_Tran_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit LPI transition Counter Interrupt Status not detected
 *  0b1..MMC Transmit LPI transition Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_TXLPITRCIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_TXLPITRCIS_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_TXLPITRCIS_MASK)
/*! @} */

/*! @name MAC_MMC_RX_INTERRUPT_MASK - MMC Rx Interrupt Mask */
/*! @{ */

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXGBPKTIM_MASK (0x1U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXGBPKTIM_SHIFT (0U)
/*! RXGBPKTIM - MMC Receive Good Bad Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxpacketcount_gb counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXGBPKTIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXGBPKTIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXGBPKTIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXGBOCTIM_MASK (0x2U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXGBOCTIM_SHIFT (1U)
/*! RXGBOCTIM - MMC Receive Good Bad Octet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxoctetcount_gb counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Good Bad Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Good Bad Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXGBOCTIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXGBOCTIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXGBOCTIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXGOCTIM_MASK (0x4U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXGOCTIM_SHIFT (2U)
/*! RXGOCTIM - MMC Receive Good Octet Counter Interrupt Mask Setting this bit masks the interrupt
 *    when the rxoctetcount_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Good Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Good Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXGOCTIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXGOCTIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXGOCTIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXBCGPIM_MASK (0x8U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXBCGPIM_SHIFT (3U)
/*! RXBCGPIM - MMC Receive Broadcast Good Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxbroadcastpackets_g counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive Broadcast Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Broadcast Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXBCGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXBCGPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXBCGPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXMCGPIM_MASK (0x10U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXMCGPIM_SHIFT (4U)
/*! RXMCGPIM - MMC Receive Multicast Good Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxmulticastpackets_g counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive Multicast Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Multicast Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXMCGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXMCGPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXMCGPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXCRCERPIM_MASK (0x20U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXCRCERPIM_SHIFT (5U)
/*! RXCRCERPIM - MMC Receive CRC Error Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxcrcerror counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive CRC Error Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive CRC Error Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXCRCERPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXCRCERPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXCRCERPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXALGNERPIM_MASK (0x40U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXALGNERPIM_SHIFT (6U)
/*! RXALGNERPIM - MMC Receive Alignment Error Packet Counter Interrupt Mask Setting this bit masks
 *    the interrupt when the rxalignmenterror counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive Alignment Error Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Alignment Error Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXALGNERPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXALGNERPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXALGNERPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXRUNTPIM_MASK (0x80U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXRUNTPIM_SHIFT (7U)
/*! RXRUNTPIM - MMC Receive Runt Packet Counter Interrupt Mask Setting this bit masks the interrupt
 *    when the rxrunterror counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Runt Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Runt Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXRUNTPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXRUNTPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXRUNTPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXJABERPIM_MASK (0x100U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXJABERPIM_SHIFT (8U)
/*! RXJABERPIM - MMC Receive Jabber Error Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxjabbererror counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Jabber Error Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Jabber Error Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXJABERPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXJABERPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXJABERPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXUSIZEGPIM_MASK (0x200U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXUSIZEGPIM_SHIFT (9U)
/*! RXUSIZEGPIM - MMC Receive Undersize Good Packet Counter Interrupt Mask Setting this bit masks
 *    the interrupt when the rxundersize_g counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Receive Undersize Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Undersize Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXUSIZEGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXUSIZEGPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXUSIZEGPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXOSIZEGPIM_MASK (0x400U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXOSIZEGPIM_SHIFT (10U)
/*! RXOSIZEGPIM - MMC Receive Oversize Good Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxoversize_g counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Receive Oversize Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Oversize Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXOSIZEGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXOSIZEGPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXOSIZEGPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX64OCTGBPIM_MASK (0x800U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX64OCTGBPIM_SHIFT (11U)
/*! RX64OCTGBPIM - MMC Receive 64 Octet Good Bad Packet Counter Interrupt Mask Setting this bit
 *    masks the interrupt when the rx64octets_gb counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive 64 Octet Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive 64 Octet Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX64OCTGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX64OCTGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX64OCTGBPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX65T127OCTGBPIM_MASK (0x1000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX65T127OCTGBPIM_SHIFT (12U)
/*! RX65T127OCTGBPIM - MMC Receive 65 to 127 Octet Good Bad Packet Counter Interrupt Mask Setting
 *    this bit masks the interrupt when the rx65to127octets_gb counter reaches half of the maximum
 *    value or the maximum value.
 *  0b0..MMC Receive 65 to 127 Octet Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive 65 to 127 Octet Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX65T127OCTGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX65T127OCTGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX65T127OCTGBPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX128T255OCTGBPIM_MASK (0x2000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX128T255OCTGBPIM_SHIFT (13U)
/*! RX128T255OCTGBPIM - MMC Receive 128 to 255 Octet Good Bad Packet Counter Interrupt Mask Setting
 *    this bit masks the interrupt when the rx128to255octets_gb counter reaches half of the maximum
 *    value or the maximum value.
 *  0b0..MMC Receive 128 to 255 Octet Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive 128 to 255 Octet Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX128T255OCTGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX128T255OCTGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX128T255OCTGBPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX256T511OCTGBPIM_MASK (0x4000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX256T511OCTGBPIM_SHIFT (14U)
/*! RX256T511OCTGBPIM - MMC Receive 256 to 511 Octet Good Bad Packet Counter Interrupt Mask Setting
 *    this bit masks the interrupt when the rx256to511octets_gb counter reaches half of the maximum
 *    value or the maximum value.
 *  0b0..MMC Receive 256 to 511 Octet Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive 256 to 511 Octet Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX256T511OCTGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX256T511OCTGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX256T511OCTGBPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX512T1023OCTGBPIM_MASK (0x8000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX512T1023OCTGBPIM_SHIFT (15U)
/*! RX512T1023OCTGBPIM - MMC Receive 512 to 1023 Octet Good Bad Packet Counter Interrupt Mask
 *    Setting this bit masks the interrupt when the rx512to1023octets_gb counter reaches half of the
 *    maximum value or the maximum value.
 *  0b0..MMC Receive 512 to 1023 Octet Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive 512 to 1023 Octet Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX512T1023OCTGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX512T1023OCTGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX512T1023OCTGBPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX1024TMAXOCTGBPIM_MASK (0x10000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX1024TMAXOCTGBPIM_SHIFT (16U)
/*! RX1024TMAXOCTGBPIM - MMC Receive 1024 to Maximum Octet Good Bad Packet Counter Interrupt Mask.
 *  0b0..MMC Receive 1024 to Maximum Octet Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive 1024 to Maximum Octet Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX1024TMAXOCTGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX1024TMAXOCTGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RX1024TMAXOCTGBPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXUCGPIM_MASK (0x20000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXUCGPIM_SHIFT (17U)
/*! RXUCGPIM - MMC Receive Unicast Good Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxunicastpackets_g counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Receive Unicast Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Unicast Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXUCGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXUCGPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXUCGPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXLENERPIM_MASK (0x40000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXLENERPIM_SHIFT (18U)
/*! RXLENERPIM - MMC Receive Length Error Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxlengtherror counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Length Error Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Length Error Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXLENERPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXLENERPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXLENERPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXORANGEPIM_MASK (0x80000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXORANGEPIM_SHIFT (19U)
/*! RXORANGEPIM - MMC Receive Out Of Range Error Packet Counter Interrupt Mask Setting this bit
 *    masks the interrupt when the rxoutofrangetype counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive Out Of Range Error Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Out Of Range Error Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXORANGEPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXORANGEPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXORANGEPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXPAUSPIM_MASK (0x100000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXPAUSPIM_SHIFT (20U)
/*! RXPAUSPIM - MMC Receive Pause Packet Counter Interrupt Mask Setting this bit masks the interrupt
 *    when the rxpausepackets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Pause Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Pause Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXPAUSPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXPAUSPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXPAUSPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXFOVPIM_MASK (0x200000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXFOVPIM_SHIFT (21U)
/*! RXFOVPIM - MMC Receive FIFO Overflow Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxfifooverflow counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive FIFO Overflow Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive FIFO Overflow Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXFOVPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXFOVPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXFOVPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXVLANGBPIM_MASK (0x400000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXVLANGBPIM_SHIFT (22U)
/*! RXVLANGBPIM - MMC Receive VLAN Good Bad Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxvlanpackets_gb counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Receive VLAN Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive VLAN Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXVLANGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXVLANGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXVLANGBPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXWDOGPIM_MASK (0x800000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXWDOGPIM_SHIFT (23U)
/*! RXWDOGPIM - MMC Receive Watchdog Error Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxwatchdog counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Watchdog Error Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Watchdog Error Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXWDOGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXWDOGPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXWDOGPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXRCVERRPIM_MASK (0x1000000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXRCVERRPIM_SHIFT (24U)
/*! RXRCVERRPIM - MMC Receive Error Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxrcverror counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Error Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Error Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXRCVERRPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXRCVERRPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXRCVERRPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXCTRLPIM_MASK (0x2000000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXCTRLPIM_SHIFT (25U)
/*! RXCTRLPIM - MMC Receive Control Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxctrlpackets_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive Control Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive Control Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXCTRLPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXCTRLPIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXCTRLPIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXLPIUSCIM_MASK (0x4000000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXLPIUSCIM_SHIFT (26U)
/*! RXLPIUSCIM - MMC Receive LPI microsecond counter interrupt Mask Setting this bit masks the
 *    interrupt when the Rx_LPI_USEC_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive LPI microsecond counter interrupt Mask is disabled
 *  0b1..MMC Receive LPI microsecond counter interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXLPIUSCIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXLPIUSCIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXLPIUSCIM_MASK)

#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXLPITRCIM_MASK (0x8000000U)
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXLPITRCIM_SHIFT (27U)
/*! RXLPITRCIM - MMC Receive LPI transition counter interrupt Mask Setting this bit masks the
 *    interrupt when the Rx_LPI_Tran_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive LPI transition counter interrupt Mask is disabled
 *  0b1..MMC Receive LPI transition counter interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXLPITRCIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXLPITRCIM_SHIFT)) & ENET_QOS_MAC_MMC_RX_INTERRUPT_MASK_RXLPITRCIM_MASK)
/*! @} */

/*! @name MAC_MMC_TX_INTERRUPT_MASK - MMC Tx Interrupt Mask */
/*! @{ */

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGBOCTIM_MASK (0x1U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGBOCTIM_SHIFT (0U)
/*! TXGBOCTIM - MMC Transmit Good Bad Octet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the txoctetcount_gb counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Good Bad Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Good Bad Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGBOCTIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGBOCTIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGBOCTIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGBPKTIM_MASK (0x2U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGBPKTIM_SHIFT (1U)
/*! TXGBPKTIM - MMC Transmit Good Bad Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the txpacketcount_gb counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGBPKTIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGBPKTIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGBPKTIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXBCGPIM_MASK (0x4U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXBCGPIM_SHIFT (2U)
/*! TXBCGPIM - MMC Transmit Broadcast Good Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the txbroadcastpackets_g counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Transmit Broadcast Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Broadcast Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXBCGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXBCGPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXBCGPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXMCGPIM_MASK (0x8U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXMCGPIM_SHIFT (3U)
/*! TXMCGPIM - MMC Transmit Multicast Good Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the txmulticastpackets_g counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Transmit Multicast Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Multicast Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXMCGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXMCGPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXMCGPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX64OCTGBPIM_MASK (0x10U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX64OCTGBPIM_SHIFT (4U)
/*! TX64OCTGBPIM - MMC Transmit 64 Octet Good Bad Packet Counter Interrupt Mask Setting this bit
 *    masks the interrupt when the tx64octets_gb counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Transmit 64 Octet Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit 64 Octet Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX64OCTGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX64OCTGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX64OCTGBPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX65T127OCTGBPIM_MASK (0x20U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX65T127OCTGBPIM_SHIFT (5U)
/*! TX65T127OCTGBPIM - MMC Transmit 65 to 127 Octet Good Bad Packet Counter Interrupt Mask Setting
 *    this bit masks the interrupt when the tx65to127octets_gb counter reaches half of the maximum
 *    value or the maximum value.
 *  0b0..MMC Transmit 65 to 127 Octet Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit 65 to 127 Octet Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX65T127OCTGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX65T127OCTGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX65T127OCTGBPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX128T255OCTGBPIM_MASK (0x40U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX128T255OCTGBPIM_SHIFT (6U)
/*! TX128T255OCTGBPIM - MMC Transmit 128 to 255 Octet Good Bad Packet Counter Interrupt Mask Setting
 *    this bit masks the interrupt when the tx128to255octets_gb counter reaches half of the maximum
 *    value or the maximum value.
 *  0b0..MMC Transmit 128 to 255 Octet Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit 128 to 255 Octet Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX128T255OCTGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX128T255OCTGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX128T255OCTGBPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX256T511OCTGBPIM_MASK (0x80U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX256T511OCTGBPIM_SHIFT (7U)
/*! TX256T511OCTGBPIM - MMC Transmit 256 to 511 Octet Good Bad Packet Counter Interrupt Mask Setting
 *    this bit masks the interrupt when the tx256to511octets_gb counter reaches half of the maximum
 *    value or the maximum value.
 *  0b0..MMC Transmit 256 to 511 Octet Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit 256 to 511 Octet Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX256T511OCTGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX256T511OCTGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX256T511OCTGBPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX512T1023OCTGBPIM_MASK (0x100U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX512T1023OCTGBPIM_SHIFT (8U)
/*! TX512T1023OCTGBPIM - MMC Transmit 512 to 1023 Octet Good Bad Packet Counter Interrupt Mask
 *    Setting this bit masks the interrupt when the tx512to1023octets_gb counter reaches half of the
 *    maximum value or the maximum value.
 *  0b0..MMC Transmit 512 to 1023 Octet Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit 512 to 1023 Octet Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX512T1023OCTGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX512T1023OCTGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX512T1023OCTGBPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX1024TMAXOCTGBPIM_MASK (0x200U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX1024TMAXOCTGBPIM_SHIFT (9U)
/*! TX1024TMAXOCTGBPIM - MMC Transmit 1024 to Maximum Octet Good Bad Packet Counter Interrupt Mask
 *    Setting this bit masks the interrupt when the tx1024tomaxoctets_gb counter reaches half of the
 *    maximum value or the maximum value.
 *  0b0..MMC Transmit 1024 to Maximum Octet Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit 1024 to Maximum Octet Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX1024TMAXOCTGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX1024TMAXOCTGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TX1024TMAXOCTGBPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXUCGBPIM_MASK (0x400U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXUCGBPIM_SHIFT (10U)
/*! TXUCGBPIM - MMC Transmit Unicast Good Bad Packet Counter Interrupt Mask Setting this bit masks
 *    the interrupt when the txunicastpackets_gb counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Transmit Unicast Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Unicast Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXUCGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXUCGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXUCGBPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXMCGBPIM_MASK (0x800U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXMCGBPIM_SHIFT (11U)
/*! TXMCGBPIM - MMC Transmit Multicast Good Bad Packet Counter Interrupt Mask Setting this bit masks
 *    the interrupt when the txmulticastpackets_gb counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Transmit Multicast Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Multicast Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXMCGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXMCGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXMCGBPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXBCGBPIM_MASK (0x1000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXBCGBPIM_SHIFT (12U)
/*! TXBCGBPIM - MMC Transmit Broadcast Good Bad Packet Counter Interrupt Mask Setting this bit masks
 *    the interrupt when the txbroadcastpackets_gb counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Transmit Broadcast Good Bad Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Broadcast Good Bad Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXBCGBPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXBCGBPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXBCGBPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXUFLOWERPIM_MASK (0x2000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXUFLOWERPIM_SHIFT (13U)
/*! TXUFLOWERPIM - MMC Transmit Underflow Error Packet Counter Interrupt Mask Setting this bit masks
 *    the interrupt when the txunderflowerror counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Transmit Underflow Error Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Underflow Error Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXUFLOWERPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXUFLOWERPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXUFLOWERPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXSCOLGPIM_MASK (0x4000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXSCOLGPIM_SHIFT (14U)
/*! TXSCOLGPIM - MMC Transmit Single Collision Good Packet Counter Interrupt Mask Setting this bit
 *    masks the interrupt when the txsinglecol_g counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Transmit Single Collision Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Single Collision Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXSCOLGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXSCOLGPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXSCOLGPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXMCOLGPIM_MASK (0x8000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXMCOLGPIM_SHIFT (15U)
/*! TXMCOLGPIM - MMC Transmit Multiple Collision Good Packet Counter Interrupt Mask Setting this bit
 *    masks the interrupt when the txmulticol_g counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Transmit Multiple Collision Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Multiple Collision Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXMCOLGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXMCOLGPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXMCOLGPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXDEFPIM_MASK (0x10000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXDEFPIM_SHIFT (16U)
/*! TXDEFPIM - MMC Transmit Deferred Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the txdeferred counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Deferred Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Deferred Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXDEFPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXDEFPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXDEFPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXLATCOLPIM_MASK (0x20000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXLATCOLPIM_SHIFT (17U)
/*! TXLATCOLPIM - MMC Transmit Late Collision Packet Counter Interrupt Mask Setting this bit masks
 *    the interrupt when the txlatecol counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Late Collision Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Late Collision Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXLATCOLPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXLATCOLPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXLATCOLPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXEXCOLPIM_MASK (0x40000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXEXCOLPIM_SHIFT (18U)
/*! TXEXCOLPIM - MMC Transmit Excessive Collision Packet Counter Interrupt Mask Setting this bit
 *    masks the interrupt when the txexcesscol counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Transmit Excessive Collision Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Excessive Collision Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXEXCOLPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXEXCOLPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXEXCOLPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXCARERPIM_MASK (0x80000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXCARERPIM_SHIFT (19U)
/*! TXCARERPIM - MMC Transmit Carrier Error Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the txcarriererror counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Transmit Carrier Error Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Carrier Error Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXCARERPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXCARERPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXCARERPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGOCTIM_MASK (0x100000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGOCTIM_SHIFT (20U)
/*! TXGOCTIM - MMC Transmit Good Octet Counter Interrupt Mask Setting this bit masks the interrupt
 *    when the txoctetcount_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Good Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Good Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGOCTIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGOCTIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGOCTIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGPKTIM_MASK (0x200000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGPKTIM_SHIFT (21U)
/*! TXGPKTIM - MMC Transmit Good Packet Counter Interrupt Mask Setting this bit masks the interrupt
 *    when the txpacketcount_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGPKTIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGPKTIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXGPKTIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXEXDEFPIM_MASK (0x400000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXEXDEFPIM_SHIFT (22U)
/*! TXEXDEFPIM - MMC Transmit Excessive Deferral Packet Counter Interrupt Mask Setting this bit
 *    masks the interrupt when the txexcessdef counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Transmit Excessive Deferral Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Excessive Deferral Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXEXDEFPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXEXDEFPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXEXDEFPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXPAUSPIM_MASK (0x800000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXPAUSPIM_SHIFT (23U)
/*! TXPAUSPIM - MMC Transmit Pause Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the txpausepackets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Pause Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Pause Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXPAUSPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXPAUSPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXPAUSPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXVLANGPIM_MASK (0x1000000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXVLANGPIM_SHIFT (24U)
/*! TXVLANGPIM - MMC Transmit VLAN Good Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the txvlanpackets_g counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit VLAN Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit VLAN Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXVLANGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXVLANGPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXVLANGPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXOSIZEGPIM_MASK (0x2000000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXOSIZEGPIM_SHIFT (25U)
/*! TXOSIZEGPIM - MMC Transmit Oversize Good Packet Counter Interrupt Mask Setting this bit masks
 *    the interrupt when the txoversize_g counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Transmit Oversize Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Oversize Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXOSIZEGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXOSIZEGPIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXOSIZEGPIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXLPIUSCIM_MASK (0x4000000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXLPIUSCIM_SHIFT (26U)
/*! TXLPIUSCIM - MMC Transmit LPI microsecond counter interrupt Mask Setting this bit masks the
 *    interrupt when the Tx_LPI_USEC_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit LPI microsecond counter interrupt Mask is disabled
 *  0b1..MMC Transmit LPI microsecond counter interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXLPIUSCIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXLPIUSCIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXLPIUSCIM_MASK)

#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXLPITRCIM_MASK (0x8000000U)
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXLPITRCIM_SHIFT (27U)
/*! TXLPITRCIM - MMC Transmit LPI transition counter interrupt Mask Setting this bit masks the
 *    interrupt when the Tx_LPI_Tran_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit LPI transition counter interrupt Mask is disabled
 *  0b1..MMC Transmit LPI transition counter interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXLPITRCIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXLPITRCIM_SHIFT)) & ENET_QOS_MAC_MMC_TX_INTERRUPT_MASK_TXLPITRCIM_MASK)
/*! @} */

/*! @name MAC_TX_OCTET_COUNT_GOOD_BAD - Tx Octet Count Good and Bad */
/*! @{ */

#define ENET_QOS_MAC_TX_OCTET_COUNT_GOOD_BAD_TXOCTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_OCTET_COUNT_GOOD_BAD_TXOCTGB_SHIFT (0U)
/*! TXOCTGB - Tx Octet Count Good Bad This field indicates the number of bytes transmitted,
 *    exclusive of preamble and retried bytes, in good and bad packets.
 */
#define ENET_QOS_MAC_TX_OCTET_COUNT_GOOD_BAD_TXOCTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_OCTET_COUNT_GOOD_BAD_TXOCTGB_SHIFT)) & ENET_QOS_MAC_TX_OCTET_COUNT_GOOD_BAD_TXOCTGB_MASK)
/*! @} */

/*! @name MAC_TX_PACKET_COUNT_GOOD_BAD - Tx Packet Count Good and Bad */
/*! @{ */

#define ENET_QOS_MAC_TX_PACKET_COUNT_GOOD_BAD_TXPKTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_PACKET_COUNT_GOOD_BAD_TXPKTGB_SHIFT (0U)
/*! TXPKTGB - Tx Packet Count Good Bad This field indicates the number of good and bad packets
 *    transmitted, exclusive of retried packets.
 */
#define ENET_QOS_MAC_TX_PACKET_COUNT_GOOD_BAD_TXPKTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_PACKET_COUNT_GOOD_BAD_TXPKTGB_SHIFT)) & ENET_QOS_MAC_TX_PACKET_COUNT_GOOD_BAD_TXPKTGB_MASK)
/*! @} */

/*! @name MAC_TX_BROADCAST_PACKETS_GOOD - Tx Broadcast Packets Good */
/*! @{ */

#define ENET_QOS_MAC_TX_BROADCAST_PACKETS_GOOD_TXBCASTG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_BROADCAST_PACKETS_GOOD_TXBCASTG_SHIFT (0U)
/*! TXBCASTG - Tx Broadcast Packets Good This field indicates the number of good broadcast packets transmitted. */
#define ENET_QOS_MAC_TX_BROADCAST_PACKETS_GOOD_TXBCASTG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_BROADCAST_PACKETS_GOOD_TXBCASTG_SHIFT)) & ENET_QOS_MAC_TX_BROADCAST_PACKETS_GOOD_TXBCASTG_MASK)
/*! @} */

/*! @name MAC_TX_MULTICAST_PACKETS_GOOD - Tx Multicast Packets Good */
/*! @{ */

#define ENET_QOS_MAC_TX_MULTICAST_PACKETS_GOOD_TXMCASTG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_MULTICAST_PACKETS_GOOD_TXMCASTG_SHIFT (0U)
/*! TXMCASTG - Tx Multicast Packets Good This field indicates the number of good multicast packets transmitted. */
#define ENET_QOS_MAC_TX_MULTICAST_PACKETS_GOOD_TXMCASTG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_MULTICAST_PACKETS_GOOD_TXMCASTG_SHIFT)) & ENET_QOS_MAC_TX_MULTICAST_PACKETS_GOOD_TXMCASTG_MASK)
/*! @} */

/*! @name MAC_TX_64OCTETS_PACKETS_GOOD_BAD - Tx Good and Bad 64-Byte Packets */
/*! @{ */

#define ENET_QOS_MAC_TX_64OCTETS_PACKETS_GOOD_BAD_TX64OCTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_64OCTETS_PACKETS_GOOD_BAD_TX64OCTGB_SHIFT (0U)
/*! TX64OCTGB - Tx 64Octets Packets Good_Bad This field indicates the number of good and bad packets
 *    transmitted with length 64 bytes, exclusive of preamble and retried packets.
 */
#define ENET_QOS_MAC_TX_64OCTETS_PACKETS_GOOD_BAD_TX64OCTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_64OCTETS_PACKETS_GOOD_BAD_TX64OCTGB_SHIFT)) & ENET_QOS_MAC_TX_64OCTETS_PACKETS_GOOD_BAD_TX64OCTGB_MASK)
/*! @} */

/*! @name MAC_TX_65TO127OCTETS_PACKETS_GOOD_BAD - Tx Good and Bad 65 to 127-Byte Packets */
/*! @{ */

#define ENET_QOS_MAC_TX_65TO127OCTETS_PACKETS_GOOD_BAD_TX65_127OCTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_65TO127OCTETS_PACKETS_GOOD_BAD_TX65_127OCTGB_SHIFT (0U)
/*! TX65_127OCTGB - Tx 65To127Octets Packets Good Bad This field indicates the number of good and
 *    bad packets transmitted with length between 65 and 127 (inclusive) bytes, exclusive of preamble
 *    and retried packets.
 */
#define ENET_QOS_MAC_TX_65TO127OCTETS_PACKETS_GOOD_BAD_TX65_127OCTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_65TO127OCTETS_PACKETS_GOOD_BAD_TX65_127OCTGB_SHIFT)) & ENET_QOS_MAC_TX_65TO127OCTETS_PACKETS_GOOD_BAD_TX65_127OCTGB_MASK)
/*! @} */

/*! @name MAC_TX_128TO255OCTETS_PACKETS_GOOD_BAD - Tx Good and Bad 128 to 255-Byte Packets */
/*! @{ */

#define ENET_QOS_MAC_TX_128TO255OCTETS_PACKETS_GOOD_BAD_TX128_255OCTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_128TO255OCTETS_PACKETS_GOOD_BAD_TX128_255OCTGB_SHIFT (0U)
/*! TX128_255OCTGB - Tx 128To255Octets Packets Good Bad This field indicates the number of good and
 *    bad packets transmitted with length between 128 and 255 (inclusive) bytes, exclusive of
 *    preamble and retried packets.
 */
#define ENET_QOS_MAC_TX_128TO255OCTETS_PACKETS_GOOD_BAD_TX128_255OCTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_128TO255OCTETS_PACKETS_GOOD_BAD_TX128_255OCTGB_SHIFT)) & ENET_QOS_MAC_TX_128TO255OCTETS_PACKETS_GOOD_BAD_TX128_255OCTGB_MASK)
/*! @} */

/*! @name MAC_TX_256TO511OCTETS_PACKETS_GOOD_BAD - Tx Good and Bad 256 to 511-Byte Packets */
/*! @{ */

#define ENET_QOS_MAC_TX_256TO511OCTETS_PACKETS_GOOD_BAD_TX256_511OCTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_256TO511OCTETS_PACKETS_GOOD_BAD_TX256_511OCTGB_SHIFT (0U)
/*! TX256_511OCTGB - Tx 256To511Octets Packets Good Bad This field indicates the number of good and
 *    bad packets transmitted with length between 256 and 511 (inclusive) bytes, exclusive of
 *    preamble and retried packets.
 */
#define ENET_QOS_MAC_TX_256TO511OCTETS_PACKETS_GOOD_BAD_TX256_511OCTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_256TO511OCTETS_PACKETS_GOOD_BAD_TX256_511OCTGB_SHIFT)) & ENET_QOS_MAC_TX_256TO511OCTETS_PACKETS_GOOD_BAD_TX256_511OCTGB_MASK)
/*! @} */

/*! @name MAC_TX_512TO1023OCTETS_PACKETS_GOOD_BAD - Tx Good and Bad 512 to 1023-Byte Packets */
/*! @{ */

#define ENET_QOS_MAC_TX_512TO1023OCTETS_PACKETS_GOOD_BAD_TX512_1023OCTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_512TO1023OCTETS_PACKETS_GOOD_BAD_TX512_1023OCTGB_SHIFT (0U)
/*! TX512_1023OCTGB - Tx 512To1023Octets Packets Good Bad This field indicates the number of good
 *    and bad packets transmitted with length between 512 and 1023 (inclusive) bytes, exclusive of
 *    preamble and retried packets.
 */
#define ENET_QOS_MAC_TX_512TO1023OCTETS_PACKETS_GOOD_BAD_TX512_1023OCTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_512TO1023OCTETS_PACKETS_GOOD_BAD_TX512_1023OCTGB_SHIFT)) & ENET_QOS_MAC_TX_512TO1023OCTETS_PACKETS_GOOD_BAD_TX512_1023OCTGB_MASK)
/*! @} */

/*! @name MAC_TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD - Tx Good and Bad 1024 to Max-Byte Packets */
/*! @{ */

#define ENET_QOS_MAC_TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD_TX1024_MAXOCTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD_TX1024_MAXOCTGB_SHIFT (0U)
/*! TX1024_MAXOCTGB - Tx 1024ToMaxOctets Packets Good Bad This field indicates the number of good
 *    and bad packets transmitted with length between 1024 and maxsize (inclusive) bytes, exclusive of
 *    preamble and retried packets.
 */
#define ENET_QOS_MAC_TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD_TX1024_MAXOCTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD_TX1024_MAXOCTGB_SHIFT)) & ENET_QOS_MAC_TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD_TX1024_MAXOCTGB_MASK)
/*! @} */

/*! @name MAC_TX_UNICAST_PACKETS_GOOD_BAD - Good and Bad Unicast Packets Transmitted */
/*! @{ */

#define ENET_QOS_MAC_TX_UNICAST_PACKETS_GOOD_BAD_TXUCASTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_UNICAST_PACKETS_GOOD_BAD_TXUCASTGB_SHIFT (0U)
/*! TXUCASTGB - Tx Unicast Packets Good Bad This field indicates the number of good and bad unicast packets transmitted. */
#define ENET_QOS_MAC_TX_UNICAST_PACKETS_GOOD_BAD_TXUCASTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_UNICAST_PACKETS_GOOD_BAD_TXUCASTGB_SHIFT)) & ENET_QOS_MAC_TX_UNICAST_PACKETS_GOOD_BAD_TXUCASTGB_MASK)
/*! @} */

/*! @name MAC_TX_MULTICAST_PACKETS_GOOD_BAD - Good and Bad Multicast Packets Transmitted */
/*! @{ */

#define ENET_QOS_MAC_TX_MULTICAST_PACKETS_GOOD_BAD_TXMCASTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_MULTICAST_PACKETS_GOOD_BAD_TXMCASTGB_SHIFT (0U)
/*! TXMCASTGB - Tx Multicast Packets Good Bad This field indicates the number of good and bad multicast packets transmitted. */
#define ENET_QOS_MAC_TX_MULTICAST_PACKETS_GOOD_BAD_TXMCASTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_MULTICAST_PACKETS_GOOD_BAD_TXMCASTGB_SHIFT)) & ENET_QOS_MAC_TX_MULTICAST_PACKETS_GOOD_BAD_TXMCASTGB_MASK)
/*! @} */

/*! @name MAC_TX_BROADCAST_PACKETS_GOOD_BAD - Good and Bad Broadcast Packets Transmitted */
/*! @{ */

#define ENET_QOS_MAC_TX_BROADCAST_PACKETS_GOOD_BAD_TXBCASTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_BROADCAST_PACKETS_GOOD_BAD_TXBCASTGB_SHIFT (0U)
/*! TXBCASTGB - Tx Broadcast Packets Good Bad This field indicates the number of good and bad broadcast packets transmitted. */
#define ENET_QOS_MAC_TX_BROADCAST_PACKETS_GOOD_BAD_TXBCASTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_BROADCAST_PACKETS_GOOD_BAD_TXBCASTGB_SHIFT)) & ENET_QOS_MAC_TX_BROADCAST_PACKETS_GOOD_BAD_TXBCASTGB_MASK)
/*! @} */

/*! @name MAC_TX_UNDERFLOW_ERROR_PACKETS - Tx Packets Aborted By Underflow Error */
/*! @{ */

#define ENET_QOS_MAC_TX_UNDERFLOW_ERROR_PACKETS_TXUNDRFLW_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_UNDERFLOW_ERROR_PACKETS_TXUNDRFLW_SHIFT (0U)
/*! TXUNDRFLW - Tx Underflow Error Packets This field indicates the number of packets aborted because of packets underflow error. */
#define ENET_QOS_MAC_TX_UNDERFLOW_ERROR_PACKETS_TXUNDRFLW(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_UNDERFLOW_ERROR_PACKETS_TXUNDRFLW_SHIFT)) & ENET_QOS_MAC_TX_UNDERFLOW_ERROR_PACKETS_TXUNDRFLW_MASK)
/*! @} */

/*! @name MAC_TX_SINGLE_COLLISION_GOOD_PACKETS - Single Collision Good Packets Transmitted */
/*! @{ */

#define ENET_QOS_MAC_TX_SINGLE_COLLISION_GOOD_PACKETS_TXSNGLCOLG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_SINGLE_COLLISION_GOOD_PACKETS_TXSNGLCOLG_SHIFT (0U)
/*! TXSNGLCOLG - Tx Single Collision Good Packets This field indicates the number of successfully
 *    transmitted packets after a single collision in the half-duplex mode.
 */
#define ENET_QOS_MAC_TX_SINGLE_COLLISION_GOOD_PACKETS_TXSNGLCOLG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_SINGLE_COLLISION_GOOD_PACKETS_TXSNGLCOLG_SHIFT)) & ENET_QOS_MAC_TX_SINGLE_COLLISION_GOOD_PACKETS_TXSNGLCOLG_MASK)
/*! @} */

/*! @name MAC_TX_MULTIPLE_COLLISION_GOOD_PACKETS - Multiple Collision Good Packets Transmitted */
/*! @{ */

#define ENET_QOS_MAC_TX_MULTIPLE_COLLISION_GOOD_PACKETS_TXMULTCOLG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_MULTIPLE_COLLISION_GOOD_PACKETS_TXMULTCOLG_SHIFT (0U)
/*! TXMULTCOLG - Tx Multiple Collision Good Packets This field indicates the number of successfully
 *    transmitted packets after multiple collisions in the half-duplex mode.
 */
#define ENET_QOS_MAC_TX_MULTIPLE_COLLISION_GOOD_PACKETS_TXMULTCOLG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_MULTIPLE_COLLISION_GOOD_PACKETS_TXMULTCOLG_SHIFT)) & ENET_QOS_MAC_TX_MULTIPLE_COLLISION_GOOD_PACKETS_TXMULTCOLG_MASK)
/*! @} */

/*! @name MAC_TX_DEFERRED_PACKETS - Deferred Packets Transmitted */
/*! @{ */

#define ENET_QOS_MAC_TX_DEFERRED_PACKETS_TXDEFRD_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_DEFERRED_PACKETS_TXDEFRD_SHIFT (0U)
/*! TXDEFRD - Tx Deferred Packets This field indicates the number of successfully transmitted after
 *    a deferral in the half-duplex mode.
 */
#define ENET_QOS_MAC_TX_DEFERRED_PACKETS_TXDEFRD(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_DEFERRED_PACKETS_TXDEFRD_SHIFT)) & ENET_QOS_MAC_TX_DEFERRED_PACKETS_TXDEFRD_MASK)
/*! @} */

/*! @name MAC_TX_LATE_COLLISION_PACKETS - Late Collision Packets Transmitted */
/*! @{ */

#define ENET_QOS_MAC_TX_LATE_COLLISION_PACKETS_TXLATECOL_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_LATE_COLLISION_PACKETS_TXLATECOL_SHIFT (0U)
/*! TXLATECOL - Tx Late Collision Packets This field indicates the number of packets aborted because of late collision error. */
#define ENET_QOS_MAC_TX_LATE_COLLISION_PACKETS_TXLATECOL(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_LATE_COLLISION_PACKETS_TXLATECOL_SHIFT)) & ENET_QOS_MAC_TX_LATE_COLLISION_PACKETS_TXLATECOL_MASK)
/*! @} */

/*! @name MAC_TX_EXCESSIVE_COLLISION_PACKETS - Excessive Collision Packets Transmitted */
/*! @{ */

#define ENET_QOS_MAC_TX_EXCESSIVE_COLLISION_PACKETS_TXEXSCOL_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_EXCESSIVE_COLLISION_PACKETS_TXEXSCOL_SHIFT (0U)
/*! TXEXSCOL - Tx Excessive Collision Packets This field indicates the number of packets aborted
 *    because of excessive (16) collision errors.
 */
#define ENET_QOS_MAC_TX_EXCESSIVE_COLLISION_PACKETS_TXEXSCOL(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_EXCESSIVE_COLLISION_PACKETS_TXEXSCOL_SHIFT)) & ENET_QOS_MAC_TX_EXCESSIVE_COLLISION_PACKETS_TXEXSCOL_MASK)
/*! @} */

/*! @name MAC_TX_CARRIER_ERROR_PACKETS - Carrier Error Packets Transmitted */
/*! @{ */

#define ENET_QOS_MAC_TX_CARRIER_ERROR_PACKETS_TXCARR_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_CARRIER_ERROR_PACKETS_TXCARR_SHIFT (0U)
/*! TXCARR - Tx Carrier Error Packets This field indicates the number of packets aborted because of
 *    carrier sense error (no carrier or loss of carrier).
 */
#define ENET_QOS_MAC_TX_CARRIER_ERROR_PACKETS_TXCARR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_CARRIER_ERROR_PACKETS_TXCARR_SHIFT)) & ENET_QOS_MAC_TX_CARRIER_ERROR_PACKETS_TXCARR_MASK)
/*! @} */

/*! @name MAC_TX_OCTET_COUNT_GOOD - Bytes Transmitted in Good Packets */
/*! @{ */

#define ENET_QOS_MAC_TX_OCTET_COUNT_GOOD_TXOCTG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_OCTET_COUNT_GOOD_TXOCTG_SHIFT (0U)
/*! TXOCTG - Tx Octet Count Good This field indicates the number of bytes transmitted, exclusive of preamble, only in good packets. */
#define ENET_QOS_MAC_TX_OCTET_COUNT_GOOD_TXOCTG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_OCTET_COUNT_GOOD_TXOCTG_SHIFT)) & ENET_QOS_MAC_TX_OCTET_COUNT_GOOD_TXOCTG_MASK)
/*! @} */

/*! @name MAC_TX_PACKET_COUNT_GOOD - Good Packets Transmitted */
/*! @{ */

#define ENET_QOS_MAC_TX_PACKET_COUNT_GOOD_TXPKTG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_PACKET_COUNT_GOOD_TXPKTG_SHIFT (0U)
/*! TXPKTG - Tx Packet Count Good This field indicates the number of good packets transmitted. */
#define ENET_QOS_MAC_TX_PACKET_COUNT_GOOD_TXPKTG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_PACKET_COUNT_GOOD_TXPKTG_SHIFT)) & ENET_QOS_MAC_TX_PACKET_COUNT_GOOD_TXPKTG_MASK)
/*! @} */

/*! @name MAC_TX_EXCESSIVE_DEFERRAL_ERROR - Packets Aborted By Excessive Deferral Error */
/*! @{ */

#define ENET_QOS_MAC_TX_EXCESSIVE_DEFERRAL_ERROR_TXEXSDEF_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_EXCESSIVE_DEFERRAL_ERROR_TXEXSDEF_SHIFT (0U)
/*! TXEXSDEF - Tx Excessive Deferral Error This field indicates the number of packets aborted
 *    because of excessive deferral error (deferred for more than two max-sized packet times).
 */
#define ENET_QOS_MAC_TX_EXCESSIVE_DEFERRAL_ERROR_TXEXSDEF(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_EXCESSIVE_DEFERRAL_ERROR_TXEXSDEF_SHIFT)) & ENET_QOS_MAC_TX_EXCESSIVE_DEFERRAL_ERROR_TXEXSDEF_MASK)
/*! @} */

/*! @name MAC_TX_PAUSE_PACKETS - Pause Packets Transmitted */
/*! @{ */

#define ENET_QOS_MAC_TX_PAUSE_PACKETS_TXPAUSE_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_PAUSE_PACKETS_TXPAUSE_SHIFT (0U)
/*! TXPAUSE - Tx Pause Packets This field indicates the number of good Pause packets transmitted. */
#define ENET_QOS_MAC_TX_PAUSE_PACKETS_TXPAUSE(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_PAUSE_PACKETS_TXPAUSE_SHIFT)) & ENET_QOS_MAC_TX_PAUSE_PACKETS_TXPAUSE_MASK)
/*! @} */

/*! @name MAC_TX_VLAN_PACKETS_GOOD - Good VLAN Packets Transmitted */
/*! @{ */

#define ENET_QOS_MAC_TX_VLAN_PACKETS_GOOD_TXVLANG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_VLAN_PACKETS_GOOD_TXVLANG_SHIFT (0U)
/*! TXVLANG - Tx VLAN Packets Good This field provides the number of good VLAN packets transmitted. */
#define ENET_QOS_MAC_TX_VLAN_PACKETS_GOOD_TXVLANG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_VLAN_PACKETS_GOOD_TXVLANG_SHIFT)) & ENET_QOS_MAC_TX_VLAN_PACKETS_GOOD_TXVLANG_MASK)
/*! @} */

/*! @name MAC_TX_OSIZE_PACKETS_GOOD - Good Oversize Packets Transmitted */
/*! @{ */

#define ENET_QOS_MAC_TX_OSIZE_PACKETS_GOOD_TXOSIZG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_OSIZE_PACKETS_GOOD_TXOSIZG_SHIFT (0U)
/*! TXOSIZG - Tx OSize Packets Good This field indicates the number of packets transmitted without
 *    errors and with length greater than the maxsize (1,518 or 1,522 bytes for VLAN tagged packets;
 *    2000 bytes if enabled in S2KP bit of the CONFIGURATION register).
 */
#define ENET_QOS_MAC_TX_OSIZE_PACKETS_GOOD_TXOSIZG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_OSIZE_PACKETS_GOOD_TXOSIZG_SHIFT)) & ENET_QOS_MAC_TX_OSIZE_PACKETS_GOOD_TXOSIZG_MASK)
/*! @} */

/*! @name MAC_RX_PACKETS_COUNT_GOOD_BAD - Good and Bad Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_PACKETS_COUNT_GOOD_BAD_RXPKTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_PACKETS_COUNT_GOOD_BAD_RXPKTGB_SHIFT (0U)
/*! RXPKTGB - Rx Packets Count Good Bad This field indicates the number of good and bad packets received. */
#define ENET_QOS_MAC_RX_PACKETS_COUNT_GOOD_BAD_RXPKTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_PACKETS_COUNT_GOOD_BAD_RXPKTGB_SHIFT)) & ENET_QOS_MAC_RX_PACKETS_COUNT_GOOD_BAD_RXPKTGB_MASK)
/*! @} */

/*! @name MAC_RX_OCTET_COUNT_GOOD_BAD - Bytes in Good and Bad Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_OCTET_COUNT_GOOD_BAD_RXOCTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_OCTET_COUNT_GOOD_BAD_RXOCTGB_SHIFT (0U)
/*! RXOCTGB - Rx Octet Count Good Bad This field indicates the number of bytes received, exclusive
 *    of preamble, in good and bad packets.
 */
#define ENET_QOS_MAC_RX_OCTET_COUNT_GOOD_BAD_RXOCTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_OCTET_COUNT_GOOD_BAD_RXOCTGB_SHIFT)) & ENET_QOS_MAC_RX_OCTET_COUNT_GOOD_BAD_RXOCTGB_MASK)
/*! @} */

/*! @name MAC_RX_OCTET_COUNT_GOOD - Bytes in Good Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_OCTET_COUNT_GOOD_RXOCTG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_OCTET_COUNT_GOOD_RXOCTG_SHIFT (0U)
/*! RXOCTG - Rx Octet Count Good This field indicates the number of bytes received, exclusive of preamble, only in good packets. */
#define ENET_QOS_MAC_RX_OCTET_COUNT_GOOD_RXOCTG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_OCTET_COUNT_GOOD_RXOCTG_SHIFT)) & ENET_QOS_MAC_RX_OCTET_COUNT_GOOD_RXOCTG_MASK)
/*! @} */

/*! @name MAC_RX_BROADCAST_PACKETS_GOOD - Good Broadcast Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_BROADCAST_PACKETS_GOOD_RXBCASTG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_BROADCAST_PACKETS_GOOD_RXBCASTG_SHIFT (0U)
/*! RXBCASTG - Rx Broadcast Packets Good This field indicates the number of good broadcast packets received. */
#define ENET_QOS_MAC_RX_BROADCAST_PACKETS_GOOD_RXBCASTG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_BROADCAST_PACKETS_GOOD_RXBCASTG_SHIFT)) & ENET_QOS_MAC_RX_BROADCAST_PACKETS_GOOD_RXBCASTG_MASK)
/*! @} */

/*! @name MAC_RX_MULTICAST_PACKETS_GOOD - Good Multicast Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_MULTICAST_PACKETS_GOOD_RXMCASTG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_MULTICAST_PACKETS_GOOD_RXMCASTG_SHIFT (0U)
/*! RXMCASTG - Rx Multicast Packets Good This field indicates the number of good multicast packets received. */
#define ENET_QOS_MAC_RX_MULTICAST_PACKETS_GOOD_RXMCASTG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_MULTICAST_PACKETS_GOOD_RXMCASTG_SHIFT)) & ENET_QOS_MAC_RX_MULTICAST_PACKETS_GOOD_RXMCASTG_MASK)
/*! @} */

/*! @name MAC_RX_CRC_ERROR_PACKETS - CRC Error Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_CRC_ERROR_PACKETS_RXCRCERR_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_CRC_ERROR_PACKETS_RXCRCERR_SHIFT (0U)
/*! RXCRCERR - Rx CRC Error Packets This field indicates the number of packets received with CRC error. */
#define ENET_QOS_MAC_RX_CRC_ERROR_PACKETS_RXCRCERR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_CRC_ERROR_PACKETS_RXCRCERR_SHIFT)) & ENET_QOS_MAC_RX_CRC_ERROR_PACKETS_RXCRCERR_MASK)
/*! @} */

/*! @name MAC_RX_ALIGNMENT_ERROR_PACKETS - Alignment Error Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_ALIGNMENT_ERROR_PACKETS_RXALGNERR_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_ALIGNMENT_ERROR_PACKETS_RXALGNERR_SHIFT (0U)
/*! RXALGNERR - Rx Alignment Error Packets This field indicates the number of packets received with alignment (dribble) error. */
#define ENET_QOS_MAC_RX_ALIGNMENT_ERROR_PACKETS_RXALGNERR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_ALIGNMENT_ERROR_PACKETS_RXALGNERR_SHIFT)) & ENET_QOS_MAC_RX_ALIGNMENT_ERROR_PACKETS_RXALGNERR_MASK)
/*! @} */

/*! @name MAC_RX_RUNT_ERROR_PACKETS - Runt Error Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_RUNT_ERROR_PACKETS_RXRUNTERR_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_RUNT_ERROR_PACKETS_RXRUNTERR_SHIFT (0U)
/*! RXRUNTERR - Rx Runt Error Packets This field indicates the number of packets received with runt
 *    (length less than 64 bytes and CRC error) error.
 */
#define ENET_QOS_MAC_RX_RUNT_ERROR_PACKETS_RXRUNTERR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_RUNT_ERROR_PACKETS_RXRUNTERR_SHIFT)) & ENET_QOS_MAC_RX_RUNT_ERROR_PACKETS_RXRUNTERR_MASK)
/*! @} */

/*! @name MAC_RX_JABBER_ERROR_PACKETS - Jabber Error Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_JABBER_ERROR_PACKETS_RXJABERR_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_JABBER_ERROR_PACKETS_RXJABERR_SHIFT (0U)
/*! RXJABERR - Rx Jabber Error Packets This field indicates the number of giant packets received
 *    with length (including CRC) greater than 1,518 bytes (1,522 bytes for VLAN tagged) and with CRC
 *    error.
 */
#define ENET_QOS_MAC_RX_JABBER_ERROR_PACKETS_RXJABERR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_JABBER_ERROR_PACKETS_RXJABERR_SHIFT)) & ENET_QOS_MAC_RX_JABBER_ERROR_PACKETS_RXJABERR_MASK)
/*! @} */

/*! @name MAC_RX_UNDERSIZE_PACKETS_GOOD - Good Undersize Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_UNDERSIZE_PACKETS_GOOD_RXUNDERSZG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_UNDERSIZE_PACKETS_GOOD_RXUNDERSZG_SHIFT (0U)
/*! RXUNDERSZG - Rx Undersize Packets Good This field indicates the number of packets received with
 *    length less than 64 bytes, without any errors.
 */
#define ENET_QOS_MAC_RX_UNDERSIZE_PACKETS_GOOD_RXUNDERSZG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_UNDERSIZE_PACKETS_GOOD_RXUNDERSZG_SHIFT)) & ENET_QOS_MAC_RX_UNDERSIZE_PACKETS_GOOD_RXUNDERSZG_MASK)
/*! @} */

/*! @name MAC_RX_OVERSIZE_PACKETS_GOOD - Good Oversize Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_OVERSIZE_PACKETS_GOOD_RXOVERSZG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_OVERSIZE_PACKETS_GOOD_RXOVERSZG_SHIFT (0U)
/*! RXOVERSZG - Rx Oversize Packets Good This field indicates the number of packets received without
 *    errors, with length greater than the maxsize (1,518 bytes or 1,522 bytes for VLAN tagged
 *    packets; 2000 bytes if enabled in the S2KP bit of the MAC_CONFIGURATION register).
 */
#define ENET_QOS_MAC_RX_OVERSIZE_PACKETS_GOOD_RXOVERSZG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_OVERSIZE_PACKETS_GOOD_RXOVERSZG_SHIFT)) & ENET_QOS_MAC_RX_OVERSIZE_PACKETS_GOOD_RXOVERSZG_MASK)
/*! @} */

/*! @name MAC_RX_64OCTETS_PACKETS_GOOD_BAD - Good and Bad 64-Byte Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_64OCTETS_PACKETS_GOOD_BAD_RX64OCTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_64OCTETS_PACKETS_GOOD_BAD_RX64OCTGB_SHIFT (0U)
/*! RX64OCTGB - Rx 64 Octets Packets Good Bad This field indicates the number of good and bad
 *    packets received with length 64 bytes, exclusive of the preamble.
 */
#define ENET_QOS_MAC_RX_64OCTETS_PACKETS_GOOD_BAD_RX64OCTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_64OCTETS_PACKETS_GOOD_BAD_RX64OCTGB_SHIFT)) & ENET_QOS_MAC_RX_64OCTETS_PACKETS_GOOD_BAD_RX64OCTGB_MASK)
/*! @} */

/*! @name MAC_RX_65TO127OCTETS_PACKETS_GOOD_BAD - Good and Bad 64-to-127 Byte Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_65TO127OCTETS_PACKETS_GOOD_BAD_RX65_127OCTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_65TO127OCTETS_PACKETS_GOOD_BAD_RX65_127OCTGB_SHIFT (0U)
/*! RX65_127OCTGB - Rx 65-127 Octets Packets Good Bad This field indicates the number of good and
 *    bad packets received with length between 65 and 127 (inclusive) bytes, exclusive of the preamble.
 */
#define ENET_QOS_MAC_RX_65TO127OCTETS_PACKETS_GOOD_BAD_RX65_127OCTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_65TO127OCTETS_PACKETS_GOOD_BAD_RX65_127OCTGB_SHIFT)) & ENET_QOS_MAC_RX_65TO127OCTETS_PACKETS_GOOD_BAD_RX65_127OCTGB_MASK)
/*! @} */

/*! @name MAC_RX_128TO255OCTETS_PACKETS_GOOD_BAD - Good and Bad 128-to-255 Byte Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_128TO255OCTETS_PACKETS_GOOD_BAD_RX128_255OCTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_128TO255OCTETS_PACKETS_GOOD_BAD_RX128_255OCTGB_SHIFT (0U)
/*! RX128_255OCTGB - Rx 128-255 Octets Packets Good Bad This field indicates the number of good and
 *    bad packets received with length between 128 and 255 (inclusive) bytes, exclusive of the
 *    preamble.
 */
#define ENET_QOS_MAC_RX_128TO255OCTETS_PACKETS_GOOD_BAD_RX128_255OCTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_128TO255OCTETS_PACKETS_GOOD_BAD_RX128_255OCTGB_SHIFT)) & ENET_QOS_MAC_RX_128TO255OCTETS_PACKETS_GOOD_BAD_RX128_255OCTGB_MASK)
/*! @} */

/*! @name MAC_RX_256TO511OCTETS_PACKETS_GOOD_BAD - Good and Bad 256-to-511 Byte Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_256TO511OCTETS_PACKETS_GOOD_BAD_RX256_511OCTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_256TO511OCTETS_PACKETS_GOOD_BAD_RX256_511OCTGB_SHIFT (0U)
/*! RX256_511OCTGB - Rx 256-511 Octets Packets Good Bad This field indicates the number of good and
 *    bad packets received with length between 256 and 511 (inclusive) bytes, exclusive of the
 *    preamble.
 */
#define ENET_QOS_MAC_RX_256TO511OCTETS_PACKETS_GOOD_BAD_RX256_511OCTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_256TO511OCTETS_PACKETS_GOOD_BAD_RX256_511OCTGB_SHIFT)) & ENET_QOS_MAC_RX_256TO511OCTETS_PACKETS_GOOD_BAD_RX256_511OCTGB_MASK)
/*! @} */

/*! @name MAC_RX_512TO1023OCTETS_PACKETS_GOOD_BAD - Good and Bad 512-to-1023 Byte Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_512TO1023OCTETS_PACKETS_GOOD_BAD_RX512_1023OCTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_512TO1023OCTETS_PACKETS_GOOD_BAD_RX512_1023OCTGB_SHIFT (0U)
/*! RX512_1023OCTGB - RX 512-1023 Octets Packets Good Bad This field indicates the number of good
 *    and bad packets received with length between 512 and 1023 (inclusive) bytes, exclusive of the
 *    preamble.
 */
#define ENET_QOS_MAC_RX_512TO1023OCTETS_PACKETS_GOOD_BAD_RX512_1023OCTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_512TO1023OCTETS_PACKETS_GOOD_BAD_RX512_1023OCTGB_SHIFT)) & ENET_QOS_MAC_RX_512TO1023OCTETS_PACKETS_GOOD_BAD_RX512_1023OCTGB_MASK)
/*! @} */

/*! @name MAC_RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD - Good and Bad 1024-to-Max Byte Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD_RX1024_MAXOCTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD_RX1024_MAXOCTGB_SHIFT (0U)
/*! RX1024_MAXOCTGB - Rx 1024-Max Octets Good Bad This field indicates the number of good and bad
 *    packets received with length between 1024 and maxsize (inclusive) bytes, exclusive of the
 *    preamble.
 */
#define ENET_QOS_MAC_RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD_RX1024_MAXOCTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD_RX1024_MAXOCTGB_SHIFT)) & ENET_QOS_MAC_RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD_RX1024_MAXOCTGB_MASK)
/*! @} */

/*! @name MAC_RX_UNICAST_PACKETS_GOOD - Good Unicast Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_UNICAST_PACKETS_GOOD_RXUCASTG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_UNICAST_PACKETS_GOOD_RXUCASTG_SHIFT (0U)
/*! RXUCASTG - Rx Unicast Packets Good This field indicates the number of good unicast packets received. */
#define ENET_QOS_MAC_RX_UNICAST_PACKETS_GOOD_RXUCASTG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_UNICAST_PACKETS_GOOD_RXUCASTG_SHIFT)) & ENET_QOS_MAC_RX_UNICAST_PACKETS_GOOD_RXUCASTG_MASK)
/*! @} */

/*! @name MAC_RX_LENGTH_ERROR_PACKETS - Length Error Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_LENGTH_ERROR_PACKETS_RXLENERR_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_LENGTH_ERROR_PACKETS_RXLENERR_SHIFT (0U)
/*! RXLENERR - Rx Length Error Packets This field indicates the number of packets received with
 *    length error (Length Type field not equal to packet size), for all packets with valid length field.
 */
#define ENET_QOS_MAC_RX_LENGTH_ERROR_PACKETS_RXLENERR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_LENGTH_ERROR_PACKETS_RXLENERR_SHIFT)) & ENET_QOS_MAC_RX_LENGTH_ERROR_PACKETS_RXLENERR_MASK)
/*! @} */

/*! @name MAC_RX_OUT_OF_RANGE_TYPE_PACKETS - Out-of-range Type Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_OUT_OF_RANGE_TYPE_PACKETS_RXOUTOFRNG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_OUT_OF_RANGE_TYPE_PACKETS_RXOUTOFRNG_SHIFT (0U)
/*! RXOUTOFRNG - Rx Out of Range Type Packet This field indicates the number of packets received
 *    with length field not equal to the valid packet size (greater than 1,500 but less than 1,536).
 */
#define ENET_QOS_MAC_RX_OUT_OF_RANGE_TYPE_PACKETS_RXOUTOFRNG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_OUT_OF_RANGE_TYPE_PACKETS_RXOUTOFRNG_SHIFT)) & ENET_QOS_MAC_RX_OUT_OF_RANGE_TYPE_PACKETS_RXOUTOFRNG_MASK)
/*! @} */

/*! @name MAC_RX_PAUSE_PACKETS - Pause Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_PAUSE_PACKETS_RXPAUSEPKT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_PAUSE_PACKETS_RXPAUSEPKT_SHIFT (0U)
/*! RXPAUSEPKT - Rx Pause Packets This field indicates the number of good and valid Pause packets received. */
#define ENET_QOS_MAC_RX_PAUSE_PACKETS_RXPAUSEPKT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_PAUSE_PACKETS_RXPAUSEPKT_SHIFT)) & ENET_QOS_MAC_RX_PAUSE_PACKETS_RXPAUSEPKT_MASK)
/*! @} */

/*! @name MAC_RX_FIFO_OVERFLOW_PACKETS - Missed Packets Due to FIFO Overflow */
/*! @{ */

#define ENET_QOS_MAC_RX_FIFO_OVERFLOW_PACKETS_RXFIFOOVFL_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_FIFO_OVERFLOW_PACKETS_RXFIFOOVFL_SHIFT (0U)
/*! RXFIFOOVFL - Rx FIFO Overflow Packets This field indicates the number of missed received packets because of FIFO overflow. */
#define ENET_QOS_MAC_RX_FIFO_OVERFLOW_PACKETS_RXFIFOOVFL(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_FIFO_OVERFLOW_PACKETS_RXFIFOOVFL_SHIFT)) & ENET_QOS_MAC_RX_FIFO_OVERFLOW_PACKETS_RXFIFOOVFL_MASK)
/*! @} */

/*! @name MAC_RX_VLAN_PACKETS_GOOD_BAD - Good and Bad VLAN Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_VLAN_PACKETS_GOOD_BAD_RXVLANPKTGB_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_VLAN_PACKETS_GOOD_BAD_RXVLANPKTGB_SHIFT (0U)
/*! RXVLANPKTGB - Rx VLAN Packets Good Bad This field indicates the number of good and bad VLAN packets received. */
#define ENET_QOS_MAC_RX_VLAN_PACKETS_GOOD_BAD_RXVLANPKTGB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_VLAN_PACKETS_GOOD_BAD_RXVLANPKTGB_SHIFT)) & ENET_QOS_MAC_RX_VLAN_PACKETS_GOOD_BAD_RXVLANPKTGB_MASK)
/*! @} */

/*! @name MAC_RX_WATCHDOG_ERROR_PACKETS - Watchdog Error Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_WATCHDOG_ERROR_PACKETS_RXWDGERR_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_WATCHDOG_ERROR_PACKETS_RXWDGERR_SHIFT (0U)
/*! RXWDGERR - Rx Watchdog Error Packets This field indicates the number of packets received with
 *    error because of watchdog timeout error (packets with a data load larger than 2,048 bytes (when
 *    JE and WD bits are reset in MAC_CONFIGURATION register), 10,240 bytes (when JE bit is set and
 *    WD bit is reset in MAC_CONFIGURATION register), 16,384 bytes (when WD bit is set in
 *    MAC_CONFIGURATION register) or the value programmed in the MAC_WATCHDOG_TIMEOUT register).
 */
#define ENET_QOS_MAC_RX_WATCHDOG_ERROR_PACKETS_RXWDGERR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_WATCHDOG_ERROR_PACKETS_RXWDGERR_SHIFT)) & ENET_QOS_MAC_RX_WATCHDOG_ERROR_PACKETS_RXWDGERR_MASK)
/*! @} */

/*! @name MAC_RX_RECEIVE_ERROR_PACKETS - Receive Error Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_RECEIVE_ERROR_PACKETS_RXRCVERR_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_RECEIVE_ERROR_PACKETS_RXRCVERR_SHIFT (0U)
/*! RXRCVERR - Rx Receive Error Packets This field indicates the number of packets received with
 *    Receive error or Packet Extension error on the GMII or MII interface.
 */
#define ENET_QOS_MAC_RX_RECEIVE_ERROR_PACKETS_RXRCVERR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_RECEIVE_ERROR_PACKETS_RXRCVERR_SHIFT)) & ENET_QOS_MAC_RX_RECEIVE_ERROR_PACKETS_RXRCVERR_MASK)
/*! @} */

/*! @name MAC_RX_CONTROL_PACKETS_GOOD - Good Control Packets Received */
/*! @{ */

#define ENET_QOS_MAC_RX_CONTROL_PACKETS_GOOD_RXCTRLG_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_CONTROL_PACKETS_GOOD_RXCTRLG_SHIFT (0U)
/*! RXCTRLG - Rx Control Packets Good This field indicates the number of good control packets received. */
#define ENET_QOS_MAC_RX_CONTROL_PACKETS_GOOD_RXCTRLG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_CONTROL_PACKETS_GOOD_RXCTRLG_SHIFT)) & ENET_QOS_MAC_RX_CONTROL_PACKETS_GOOD_RXCTRLG_MASK)
/*! @} */

/*! @name MAC_TX_LPI_USEC_CNTR - Microseconds Tx LPI Asserted */
/*! @{ */

#define ENET_QOS_MAC_TX_LPI_USEC_CNTR_TXLPIUSC_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_LPI_USEC_CNTR_TXLPIUSC_SHIFT (0U)
/*! TXLPIUSC - Tx LPI Microseconds Counter This field indicates the number of microseconds Tx LPI is asserted. */
#define ENET_QOS_MAC_TX_LPI_USEC_CNTR_TXLPIUSC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_LPI_USEC_CNTR_TXLPIUSC_SHIFT)) & ENET_QOS_MAC_TX_LPI_USEC_CNTR_TXLPIUSC_MASK)
/*! @} */

/*! @name MAC_TX_LPI_TRAN_CNTR - Number of Times Tx LPI Asserted */
/*! @{ */

#define ENET_QOS_MAC_TX_LPI_TRAN_CNTR_TXLPITRC_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_LPI_TRAN_CNTR_TXLPITRC_SHIFT (0U)
/*! TXLPITRC - Tx LPI Transition counter This field indicates the number of times Tx LPI Entry has occurred. */
#define ENET_QOS_MAC_TX_LPI_TRAN_CNTR_TXLPITRC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_LPI_TRAN_CNTR_TXLPITRC_SHIFT)) & ENET_QOS_MAC_TX_LPI_TRAN_CNTR_TXLPITRC_MASK)
/*! @} */

/*! @name MAC_RX_LPI_USEC_CNTR - Microseconds Rx LPI Sampled */
/*! @{ */

#define ENET_QOS_MAC_RX_LPI_USEC_CNTR_RXLPIUSC_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_LPI_USEC_CNTR_RXLPIUSC_SHIFT (0U)
/*! RXLPIUSC - Rx LPI Microseconds Counter This field indicates the number of microseconds Rx LPI is asserted. */
#define ENET_QOS_MAC_RX_LPI_USEC_CNTR_RXLPIUSC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_LPI_USEC_CNTR_RXLPIUSC_SHIFT)) & ENET_QOS_MAC_RX_LPI_USEC_CNTR_RXLPIUSC_MASK)
/*! @} */

/*! @name MAC_RX_LPI_TRAN_CNTR - Number of Times Rx LPI Entered */
/*! @{ */

#define ENET_QOS_MAC_RX_LPI_TRAN_CNTR_RXLPITRC_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RX_LPI_TRAN_CNTR_RXLPITRC_SHIFT (0U)
/*! RXLPITRC - Rx LPI Transition counter This field indicates the number of times Rx LPI Entry has occurred. */
#define ENET_QOS_MAC_RX_LPI_TRAN_CNTR_RXLPITRC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RX_LPI_TRAN_CNTR_RXLPITRC_SHIFT)) & ENET_QOS_MAC_RX_LPI_TRAN_CNTR_RXLPITRC_MASK)
/*! @} */

/*! @name MAC_MMC_IPC_RX_INTERRUPT_MASK - MMC IPC Receive Interrupt Mask */
/*! @{ */

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4GPIM_MASK (0x1U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4GPIM_SHIFT (0U)
/*! RXIPV4GPIM - MMC Receive IPV4 Good Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxipv4_gd_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV4 Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV4 Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4GPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4GPIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4GPIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4HERPIM_MASK (0x2U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4HERPIM_SHIFT (1U)
/*! RXIPV4HERPIM - MMC Receive IPV4 Header Error Packet Counter Interrupt Mask Setting this bit
 *    masks the interrupt when the rxipv4_hdrerr_pkts counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive IPV4 Header Error Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV4 Header Error Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4HERPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4HERPIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4HERPIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4NOPAYPIM_MASK (0x4U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4NOPAYPIM_SHIFT (2U)
/*! RXIPV4NOPAYPIM - MMC Receive IPV4 No Payload Packet Counter Interrupt Mask Setting this bit
 *    masks the interrupt when the rxipv4_nopay_pkts counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive IPV4 No Payload Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV4 No Payload Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4NOPAYPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4NOPAYPIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4NOPAYPIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4FRAGPIM_MASK (0x8U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4FRAGPIM_SHIFT (3U)
/*! RXIPV4FRAGPIM - MMC Receive IPV4 Fragmented Packet Counter Interrupt Mask Setting this bit masks
 *    the interrupt when the rxipv4_frag_pkts counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive IPV4 Fragmented Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV4 Fragmented Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4FRAGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4FRAGPIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4FRAGPIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4UDSBLPIM_MASK (0x10U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4UDSBLPIM_SHIFT (4U)
/*! RXIPV4UDSBLPIM - MMC Receive IPV4 UDP Checksum Disabled Packet Counter Interrupt Mask Setting
 *    this bit masks the interrupt when the rxipv4_udsbl_pkts counter reaches half of the maximum
 *    value or the maximum value.
 *  0b0..MMC Receive IPV4 UDP Checksum Disabled Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV4 UDP Checksum Disabled Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4UDSBLPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4UDSBLPIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4UDSBLPIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6GPIM_MASK (0x20U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6GPIM_SHIFT (5U)
/*! RXIPV6GPIM - MMC Receive IPV6 Good Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxipv6_gd_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV6 Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV6 Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6GPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6GPIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6GPIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6HERPIM_MASK (0x40U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6HERPIM_SHIFT (6U)
/*! RXIPV6HERPIM - MMC Receive IPV6 Header Error Packet Counter Interrupt Mask Setting this bit
 *    masks the interrupt when the rxipv6_hdrerr_pkts counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive IPV6 Header Error Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV6 Header Error Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6HERPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6HERPIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6HERPIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6NOPAYPIM_MASK (0x80U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6NOPAYPIM_SHIFT (7U)
/*! RXIPV6NOPAYPIM - MMC Receive IPV6 No Payload Packet Counter Interrupt Mask Setting this bit
 *    masks the interrupt when the rxipv6_nopay_pkts counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive IPV6 No Payload Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV6 No Payload Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6NOPAYPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6NOPAYPIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6NOPAYPIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPGPIM_MASK (0x100U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPGPIM_SHIFT (8U)
/*! RXUDPGPIM - MMC Receive UDP Good Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxudp_gd_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive UDP Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive UDP Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPGPIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPGPIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPERPIM_MASK (0x200U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPERPIM_SHIFT (9U)
/*! RXUDPERPIM - MMC Receive UDP Error Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxudp_err_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive UDP Error Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive UDP Error Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPERPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPERPIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPERPIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPGPIM_MASK (0x400U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPGPIM_SHIFT (10U)
/*! RXTCPGPIM - MMC Receive TCP Good Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxtcp_gd_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive TCP Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive TCP Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPGPIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPGPIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPERPIM_MASK (0x800U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPERPIM_SHIFT (11U)
/*! RXTCPERPIM - MMC Receive TCP Error Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxtcp_err_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive TCP Error Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive TCP Error Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPERPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPERPIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPERPIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPGPIM_MASK (0x1000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPGPIM_SHIFT (12U)
/*! RXICMPGPIM - MMC Receive ICMP Good Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxicmp_gd_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive ICMP Good Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive ICMP Good Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPGPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPGPIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPGPIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPERPIM_MASK (0x2000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPERPIM_SHIFT (13U)
/*! RXICMPERPIM - MMC Receive ICMP Error Packet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxicmp_err_pkts counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Receive ICMP Error Packet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive ICMP Error Packet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPERPIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPERPIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPERPIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4GOIM_MASK (0x10000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4GOIM_SHIFT (16U)
/*! RXIPV4GOIM - MMC Receive IPV4 Good Octet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxipv4_gd_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV4 Good Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV4 Good Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4GOIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4GOIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4GOIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4HEROIM_MASK (0x20000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4HEROIM_SHIFT (17U)
/*! RXIPV4HEROIM - MMC Receive IPV4 Header Error Octet Counter Interrupt Mask Setting this bit masks
 *    the interrupt when the rxipv4_hdrerr_octets counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive IPV4 Header Error Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV4 Header Error Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4HEROIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4HEROIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4HEROIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4NOPAYOIM_MASK (0x40000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4NOPAYOIM_SHIFT (18U)
/*! RXIPV4NOPAYOIM - MMC Receive IPV4 No Payload Octet Counter Interrupt Mask Setting this bit masks
 *    the interrupt when the rxipv4_nopay_octets counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive IPV4 No Payload Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV4 No Payload Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4NOPAYOIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4NOPAYOIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4NOPAYOIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4FRAGOIM_MASK (0x80000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4FRAGOIM_SHIFT (19U)
/*! RXIPV4FRAGOIM - MMC Receive IPV4 Fragmented Octet Counter Interrupt Mask Setting this bit masks
 *    the interrupt when the rxipv4_frag_octets counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive IPV4 Fragmented Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV4 Fragmented Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4FRAGOIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4FRAGOIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4FRAGOIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4UDSBLOIM_MASK (0x100000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4UDSBLOIM_SHIFT (20U)
/*! RXIPV4UDSBLOIM - MMC Receive IPV4 UDP Checksum Disabled Octet Counter Interrupt Mask Setting
 *    this bit masks the interrupt when the rxipv4_udsbl_octets counter reaches half of the maximum
 *    value or the maximum value.
 *  0b0..MMC Receive IPV4 UDP Checksum Disabled Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV4 UDP Checksum Disabled Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4UDSBLOIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4UDSBLOIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4UDSBLOIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6GOIM_MASK (0x200000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6GOIM_SHIFT (21U)
/*! RXIPV6GOIM - MMC Receive IPV6 Good Octet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxipv6_gd_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV6 Good Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV6 Good Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6GOIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6GOIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6GOIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6HEROIM_MASK (0x400000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6HEROIM_SHIFT (22U)
/*! RXIPV6HEROIM - MMC Receive IPV6 Good Octet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxipv6_hdrerr_octets counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Receive IPV6 Good Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV6 Good Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6HEROIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6HEROIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6HEROIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6NOPAYOIM_MASK (0x800000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6NOPAYOIM_SHIFT (23U)
/*! RXIPV6NOPAYOIM - MMC Receive IPV6 Header Error Octet Counter Interrupt Mask Setting this bit
 *    masks the interrupt when the rxipv6_nopay_octets counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Receive IPV6 Header Error Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV6 Header Error Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6NOPAYOIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6NOPAYOIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6NOPAYOIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPGOIM_MASK (0x1000000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPGOIM_SHIFT (24U)
/*! RXUDPGOIM - MMC Receive IPV6 No Payload Octet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxudp_gd_octets counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Receive IPV6 No Payload Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive IPV6 No Payload Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPGOIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPGOIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPGOIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPEROIM_MASK (0x2000000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPEROIM_SHIFT (25U)
/*! RXUDPEROIM - MMC Receive UDP Good Octet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxudp_err_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive UDP Good Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive UDP Good Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPEROIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPEROIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXUDPEROIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPGOIM_MASK (0x4000000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPGOIM_SHIFT (26U)
/*! RXTCPGOIM - MMC Receive TCP Good Octet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxtcp_gd_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive TCP Good Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive TCP Good Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPGOIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPGOIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPGOIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPEROIM_MASK (0x8000000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPEROIM_SHIFT (27U)
/*! RXTCPEROIM - MMC Receive TCP Error Octet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxtcp_err_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive TCP Error Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive TCP Error Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPEROIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPEROIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXTCPEROIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPGOIM_MASK (0x10000000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPGOIM_SHIFT (28U)
/*! RXICMPGOIM - MMC Receive ICMP Good Octet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxicmp_gd_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive ICMP Good Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive ICMP Good Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPGOIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPGOIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPGOIM_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPEROIM_MASK (0x20000000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPEROIM_SHIFT (29U)
/*! RXICMPEROIM - MMC Receive ICMP Error Octet Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the rxicmp_err_octets counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Receive ICMP Error Octet Counter Interrupt Mask is disabled
 *  0b1..MMC Receive ICMP Error Octet Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPEROIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPEROIM_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_MASK_RXICMPEROIM_MASK)
/*! @} */

/*! @name MAC_MMC_IPC_RX_INTERRUPT - MMC IPC Receive Interrupt */
/*! @{ */

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4GPIS_MASK (0x1U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4GPIS_SHIFT (0U)
/*! RXIPV4GPIS - MMC Receive IPV4 Good Packet Counter Interrupt Status This bit is set when the
 *    rxipv4_gd_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV4 Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV4 Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4GPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4GPIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4GPIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4HERPIS_MASK (0x2U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4HERPIS_SHIFT (1U)
/*! RXIPV4HERPIS - MMC Receive IPV4 Header Error Packet Counter Interrupt Status This bit is set
 *    when the rxipv4_hdrerr_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV4 Header Error Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV4 Header Error Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4HERPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4HERPIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4HERPIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4NOPAYPIS_MASK (0x4U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4NOPAYPIS_SHIFT (2U)
/*! RXIPV4NOPAYPIS - MMC Receive IPV4 No Payload Packet Counter Interrupt Status This bit is set
 *    when the rxipv4_nopay_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV4 No Payload Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV4 No Payload Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4NOPAYPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4NOPAYPIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4NOPAYPIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4FRAGPIS_MASK (0x8U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4FRAGPIS_SHIFT (3U)
/*! RXIPV4FRAGPIS - MMC Receive IPV4 Fragmented Packet Counter Interrupt Status This bit is set when
 *    the rxipv4_frag_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV4 Fragmented Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV4 Fragmented Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4FRAGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4FRAGPIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4FRAGPIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4UDSBLPIS_MASK (0x10U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4UDSBLPIS_SHIFT (4U)
/*! RXIPV4UDSBLPIS - MMC Receive IPV4 UDP Checksum Disabled Packet Counter Interrupt Status This bit
 *    is set when the rxipv4_udsbl_pkts counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Receive IPV4 UDP Checksum Disabled Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV4 UDP Checksum Disabled Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4UDSBLPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4UDSBLPIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4UDSBLPIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6GPIS_MASK (0x20U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6GPIS_SHIFT (5U)
/*! RXIPV6GPIS - MMC Receive IPV6 Good Packet Counter Interrupt Status This bit is set when the
 *    rxipv6_gd_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV6 Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV6 Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6GPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6GPIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6GPIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6HERPIS_MASK (0x40U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6HERPIS_SHIFT (6U)
/*! RXIPV6HERPIS - MMC Receive IPV6 Header Error Packet Counter Interrupt Status This bit is set
 *    when the rxipv6_hdrerr_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV6 Header Error Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV6 Header Error Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6HERPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6HERPIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6HERPIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6NOPAYPIS_MASK (0x80U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6NOPAYPIS_SHIFT (7U)
/*! RXIPV6NOPAYPIS - MMC Receive IPV6 No Payload Packet Counter Interrupt Status This bit is set
 *    when the rxipv6_nopay_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV6 No Payload Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV6 No Payload Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6NOPAYPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6NOPAYPIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6NOPAYPIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPGPIS_MASK (0x100U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPGPIS_SHIFT (8U)
/*! RXUDPGPIS - MC Receive UDP Good Packet Counter Interrupt Status This bit is set when the
 *    rxudp_gd_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive UDP Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive UDP Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPGPIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPGPIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPERPIS_MASK (0x200U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPERPIS_SHIFT (9U)
/*! RXUDPERPIS - MMC Receive UDP Error Packet Counter Interrupt Status This bit is set when the
 *    rxudp_err_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive UDP Error Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive UDP Error Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPERPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPERPIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPERPIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPGPIS_MASK (0x400U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPGPIS_SHIFT (10U)
/*! RXTCPGPIS - MMC Receive TCP Good Packet Counter Interrupt Status This bit is set when the
 *    rxtcp_gd_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive TCP Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive TCP Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPGPIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPGPIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPERPIS_MASK (0x800U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPERPIS_SHIFT (11U)
/*! RXTCPERPIS - MMC Receive TCP Error Packet Counter Interrupt Status This bit is set when the
 *    rxtcp_err_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive TCP Error Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive TCP Error Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPERPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPERPIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPERPIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPGPIS_MASK (0x1000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPGPIS_SHIFT (12U)
/*! RXICMPGPIS - MMC Receive ICMP Good Packet Counter Interrupt Status This bit is set when the
 *    rxicmp_gd_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive ICMP Good Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive ICMP Good Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPGPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPGPIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPGPIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPERPIS_MASK (0x2000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPERPIS_SHIFT (13U)
/*! RXICMPERPIS - MMC Receive ICMP Error Packet Counter Interrupt Status This bit is set when the
 *    rxicmp_err_pkts counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive ICMP Error Packet Counter Interrupt Status not detected
 *  0b1..MMC Receive ICMP Error Packet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPERPIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPERPIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPERPIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4GOIS_MASK (0x10000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4GOIS_SHIFT (16U)
/*! RXIPV4GOIS - MMC Receive IPV4 Good Octet Counter Interrupt Status This bit is set when the
 *    rxipv4_gd_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV4 Good Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV4 Good Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4GOIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4GOIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4GOIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4HEROIS_MASK (0x20000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4HEROIS_SHIFT (17U)
/*! RXIPV4HEROIS - MMC Receive IPV4 Header Error Octet Counter Interrupt Status This bit is set when
 *    the rxipv4_hdrerr_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV4 Header Error Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV4 Header Error Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4HEROIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4HEROIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4HEROIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4NOPAYOIS_MASK (0x40000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4NOPAYOIS_SHIFT (18U)
/*! RXIPV4NOPAYOIS - MMC Receive IPV4 No Payload Octet Counter Interrupt Status This bit is set when
 *    the rxipv4_nopay_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV4 No Payload Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV4 No Payload Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4NOPAYOIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4NOPAYOIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4NOPAYOIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4FRAGOIS_MASK (0x80000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4FRAGOIS_SHIFT (19U)
/*! RXIPV4FRAGOIS - MMC Receive IPV4 Fragmented Octet Counter Interrupt Status This bit is set when
 *    the rxipv4_frag_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV4 Fragmented Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV4 Fragmented Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4FRAGOIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4FRAGOIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4FRAGOIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4UDSBLOIS_MASK (0x100000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4UDSBLOIS_SHIFT (20U)
/*! RXIPV4UDSBLOIS - MMC Receive IPV4 UDP Checksum Disabled Octet Counter Interrupt Status This bit
 *    is set when the rxipv4_udsbl_octets counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Receive IPV4 UDP Checksum Disabled Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV4 UDP Checksum Disabled Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4UDSBLOIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4UDSBLOIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV4UDSBLOIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6GOIS_MASK (0x200000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6GOIS_SHIFT (21U)
/*! RXIPV6GOIS - MMC Receive IPV6 Good Octet Counter Interrupt Status This bit is set when the
 *    rxipv6_gd_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV6 Good Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV6 Good Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6GOIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6GOIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6GOIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6HEROIS_MASK (0x400000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6HEROIS_SHIFT (22U)
/*! RXIPV6HEROIS - MMC Receive IPV6 Header Error Octet Counter Interrupt Status This bit is set when
 *    the rxipv6_hdrerr_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV6 Header Error Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV6 Header Error Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6HEROIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6HEROIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6HEROIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6NOPAYOIS_MASK (0x800000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6NOPAYOIS_SHIFT (23U)
/*! RXIPV6NOPAYOIS - MMC Receive IPV6 No Payload Octet Counter Interrupt Status This bit is set when
 *    the rxipv6_nopay_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive IPV6 No Payload Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive IPV6 No Payload Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6NOPAYOIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6NOPAYOIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXIPV6NOPAYOIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPGOIS_MASK (0x1000000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPGOIS_SHIFT (24U)
/*! RXUDPGOIS - MMC Receive UDP Good Octet Counter Interrupt Status This bit is set when the
 *    rxudp_gd_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive UDP Good Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive UDP Good Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPGOIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPGOIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPGOIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPEROIS_MASK (0x2000000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPEROIS_SHIFT (25U)
/*! RXUDPEROIS - MMC Receive UDP Error Octet Counter Interrupt Status This bit is set when the
 *    rxudp_err_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive UDP Error Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive UDP Error Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPEROIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPEROIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXUDPEROIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPGOIS_MASK (0x4000000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPGOIS_SHIFT (26U)
/*! RXTCPGOIS - MMC Receive TCP Good Octet Counter Interrupt Status This bit is set when the
 *    rxtcp_gd_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive TCP Good Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive TCP Good Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPGOIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPGOIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPGOIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPEROIS_MASK (0x8000000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPEROIS_SHIFT (27U)
/*! RXTCPEROIS - MMC Receive TCP Error Octet Counter Interrupt Status This bit is set when the
 *    rxtcp_err_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive TCP Error Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive TCP Error Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPEROIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPEROIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXTCPEROIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPGOIS_MASK (0x10000000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPGOIS_SHIFT (28U)
/*! RXICMPGOIS - MMC Receive ICMP Good Octet Counter Interrupt Status This bit is set when the
 *    rxicmp_gd_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive ICMP Good Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive ICMP Good Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPGOIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPGOIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPGOIS_MASK)

#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPEROIS_MASK (0x20000000U)
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPEROIS_SHIFT (29U)
/*! RXICMPEROIS - MMC Receive ICMP Error Octet Counter Interrupt Status This bit is set when the
 *    rxicmp_err_octets counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Receive ICMP Error Octet Counter Interrupt Status not detected
 *  0b1..MMC Receive ICMP Error Octet Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPEROIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPEROIS_SHIFT)) & ENET_QOS_MAC_MMC_IPC_RX_INTERRUPT_RXICMPEROIS_MASK)
/*! @} */

/*! @name MAC_RXIPV4_GOOD_PACKETS - Good IPv4 Datagrams Received */
/*! @{ */

#define ENET_QOS_MAC_RXIPV4_GOOD_PACKETS_RXIPV4GDPKT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV4_GOOD_PACKETS_RXIPV4GDPKT_SHIFT (0U)
/*! RXIPV4GDPKT - RxIPv4 Good Packets This field indicates the number of good IPv4 datagrams received with the TCP, UDP, or ICMP payload. */
#define ENET_QOS_MAC_RXIPV4_GOOD_PACKETS_RXIPV4GDPKT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV4_GOOD_PACKETS_RXIPV4GDPKT_SHIFT)) & ENET_QOS_MAC_RXIPV4_GOOD_PACKETS_RXIPV4GDPKT_MASK)
/*! @} */

/*! @name MAC_RXIPV4_HEADER_ERROR_PACKETS - IPv4 Datagrams Received with Header Errors */
/*! @{ */

#define ENET_QOS_MAC_RXIPV4_HEADER_ERROR_PACKETS_RXIPV4HDRERRPKT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV4_HEADER_ERROR_PACKETS_RXIPV4HDRERRPKT_SHIFT (0U)
/*! RXIPV4HDRERRPKT - RxIPv4 Header Error Packets This field indicates the number of IPv4 datagrams
 *    received with header (checksum, length, or version mismatch) errors.
 */
#define ENET_QOS_MAC_RXIPV4_HEADER_ERROR_PACKETS_RXIPV4HDRERRPKT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV4_HEADER_ERROR_PACKETS_RXIPV4HDRERRPKT_SHIFT)) & ENET_QOS_MAC_RXIPV4_HEADER_ERROR_PACKETS_RXIPV4HDRERRPKT_MASK)
/*! @} */

/*! @name MAC_RXIPV4_NO_PAYLOAD_PACKETS - IPv4 Datagrams Received with No Payload */
/*! @{ */

#define ENET_QOS_MAC_RXIPV4_NO_PAYLOAD_PACKETS_RXIPV4NOPAYPKT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV4_NO_PAYLOAD_PACKETS_RXIPV4NOPAYPKT_SHIFT (0U)
/*! RXIPV4NOPAYPKT - RxIPv4 Payload Packets This field indicates the number of IPv4 datagram packets
 *    received that did not have a TCP, UDP, or ICMP payload.
 */
#define ENET_QOS_MAC_RXIPV4_NO_PAYLOAD_PACKETS_RXIPV4NOPAYPKT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV4_NO_PAYLOAD_PACKETS_RXIPV4NOPAYPKT_SHIFT)) & ENET_QOS_MAC_RXIPV4_NO_PAYLOAD_PACKETS_RXIPV4NOPAYPKT_MASK)
/*! @} */

/*! @name MAC_RXIPV4_FRAGMENTED_PACKETS - IPv4 Datagrams Received with Fragmentation */
/*! @{ */

#define ENET_QOS_MAC_RXIPV4_FRAGMENTED_PACKETS_RXIPV4FRAGPKT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV4_FRAGMENTED_PACKETS_RXIPV4FRAGPKT_SHIFT (0U)
/*! RXIPV4FRAGPKT - RxIPv4 Fragmented Packets This field indicates the number of good IPv4 datagrams received with fragmentation. */
#define ENET_QOS_MAC_RXIPV4_FRAGMENTED_PACKETS_RXIPV4FRAGPKT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV4_FRAGMENTED_PACKETS_RXIPV4FRAGPKT_SHIFT)) & ENET_QOS_MAC_RXIPV4_FRAGMENTED_PACKETS_RXIPV4FRAGPKT_MASK)
/*! @} */

/*! @name MAC_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS - IPv4 Datagrams Received with UDP Checksum Disabled */
/*! @{ */

#define ENET_QOS_MAC_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS_RXIPV4UDSBLPKT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS_RXIPV4UDSBLPKT_SHIFT (0U)
/*! RXIPV4UDSBLPKT - RxIPv4 UDP Checksum Disabled Packets This field indicates the number of good
 *    IPv4 datagrams received that had a UDP payload with checksum disabled.
 */
#define ENET_QOS_MAC_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS_RXIPV4UDSBLPKT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS_RXIPV4UDSBLPKT_SHIFT)) & ENET_QOS_MAC_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS_RXIPV4UDSBLPKT_MASK)
/*! @} */

/*! @name MAC_RXIPV6_GOOD_PACKETS - Good IPv6 Datagrams Received */
/*! @{ */

#define ENET_QOS_MAC_RXIPV6_GOOD_PACKETS_RXIPV6GDPKT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV6_GOOD_PACKETS_RXIPV6GDPKT_SHIFT (0U)
/*! RXIPV6GDPKT - RxIPv6 Good Packets This field indicates the number of good IPv6 datagrams received with the TCP, UDP, or ICMP payload. */
#define ENET_QOS_MAC_RXIPV6_GOOD_PACKETS_RXIPV6GDPKT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV6_GOOD_PACKETS_RXIPV6GDPKT_SHIFT)) & ENET_QOS_MAC_RXIPV6_GOOD_PACKETS_RXIPV6GDPKT_MASK)
/*! @} */

/*! @name MAC_RXIPV6_HEADER_ERROR_PACKETS - IPv6 Datagrams Received with Header Errors */
/*! @{ */

#define ENET_QOS_MAC_RXIPV6_HEADER_ERROR_PACKETS_RXIPV6HDRERRPKT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV6_HEADER_ERROR_PACKETS_RXIPV6HDRERRPKT_SHIFT (0U)
/*! RXIPV6HDRERRPKT - RxIPv6 Header Error Packets This field indicates the number of IPv6 datagrams
 *    received with header (length or version mismatch) errors.
 */
#define ENET_QOS_MAC_RXIPV6_HEADER_ERROR_PACKETS_RXIPV6HDRERRPKT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV6_HEADER_ERROR_PACKETS_RXIPV6HDRERRPKT_SHIFT)) & ENET_QOS_MAC_RXIPV6_HEADER_ERROR_PACKETS_RXIPV6HDRERRPKT_MASK)
/*! @} */

/*! @name MAC_RXIPV6_NO_PAYLOAD_PACKETS - IPv6 Datagrams Received with No Payload */
/*! @{ */

#define ENET_QOS_MAC_RXIPV6_NO_PAYLOAD_PACKETS_RXIPV6NOPAYPKT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV6_NO_PAYLOAD_PACKETS_RXIPV6NOPAYPKT_SHIFT (0U)
/*! RXIPV6NOPAYPKT - RxIPv6 Payload Packets This field indicates the number of IPv6 datagram packets
 *    received that did not have a TCP, UDP, or ICMP payload.
 */
#define ENET_QOS_MAC_RXIPV6_NO_PAYLOAD_PACKETS_RXIPV6NOPAYPKT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV6_NO_PAYLOAD_PACKETS_RXIPV6NOPAYPKT_SHIFT)) & ENET_QOS_MAC_RXIPV6_NO_PAYLOAD_PACKETS_RXIPV6NOPAYPKT_MASK)
/*! @} */

/*! @name MAC_RXUDP_GOOD_PACKETS - IPv6 Datagrams Received with Good UDP */
/*! @{ */

#define ENET_QOS_MAC_RXUDP_GOOD_PACKETS_RXUDPGDPKT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXUDP_GOOD_PACKETS_RXUDPGDPKT_SHIFT (0U)
/*! RXUDPGDPKT - RxUDP Good Packets This field indicates the number of good IP datagrams received with a good UDP payload. */
#define ENET_QOS_MAC_RXUDP_GOOD_PACKETS_RXUDPGDPKT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXUDP_GOOD_PACKETS_RXUDPGDPKT_SHIFT)) & ENET_QOS_MAC_RXUDP_GOOD_PACKETS_RXUDPGDPKT_MASK)
/*! @} */

/*! @name MAC_RXUDP_ERROR_PACKETS - IPv6 Datagrams Received with UDP Checksum Error */
/*! @{ */

#define ENET_QOS_MAC_RXUDP_ERROR_PACKETS_RXUDPERRPKT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXUDP_ERROR_PACKETS_RXUDPERRPKT_SHIFT (0U)
/*! RXUDPERRPKT - RxUDP Error Packets This field indicates the number of good IP datagrams received
 *    whose UDP payload has a checksum error.
 */
#define ENET_QOS_MAC_RXUDP_ERROR_PACKETS_RXUDPERRPKT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXUDP_ERROR_PACKETS_RXUDPERRPKT_SHIFT)) & ENET_QOS_MAC_RXUDP_ERROR_PACKETS_RXUDPERRPKT_MASK)
/*! @} */

/*! @name MAC_RXTCP_GOOD_PACKETS - IPv6 Datagrams Received with Good TCP Payload */
/*! @{ */

#define ENET_QOS_MAC_RXTCP_GOOD_PACKETS_RXTCPGDPKT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXTCP_GOOD_PACKETS_RXTCPGDPKT_SHIFT (0U)
/*! RXTCPGDPKT - RxTCP Good Packets This field indicates the number of good IP datagrams received with a good TCP payload. */
#define ENET_QOS_MAC_RXTCP_GOOD_PACKETS_RXTCPGDPKT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXTCP_GOOD_PACKETS_RXTCPGDPKT_SHIFT)) & ENET_QOS_MAC_RXTCP_GOOD_PACKETS_RXTCPGDPKT_MASK)
/*! @} */

/*! @name MAC_RXTCP_ERROR_PACKETS - IPv6 Datagrams Received with TCP Checksum Error */
/*! @{ */

#define ENET_QOS_MAC_RXTCP_ERROR_PACKETS_RXTCPERRPKT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXTCP_ERROR_PACKETS_RXTCPERRPKT_SHIFT (0U)
/*! RXTCPERRPKT - RxTCP Error Packets This field indicates the number of good IP datagrams received
 *    whose TCP payload has a checksum error.
 */
#define ENET_QOS_MAC_RXTCP_ERROR_PACKETS_RXTCPERRPKT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXTCP_ERROR_PACKETS_RXTCPERRPKT_SHIFT)) & ENET_QOS_MAC_RXTCP_ERROR_PACKETS_RXTCPERRPKT_MASK)
/*! @} */

/*! @name MAC_RXICMP_GOOD_PACKETS - IPv6 Datagrams Received with Good ICMP Payload */
/*! @{ */

#define ENET_QOS_MAC_RXICMP_GOOD_PACKETS_RXICMPGDPKT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXICMP_GOOD_PACKETS_RXICMPGDPKT_SHIFT (0U)
/*! RXICMPGDPKT - RxICMP Good Packets This field indicates the number of good IP datagrams received with a good ICMP payload. */
#define ENET_QOS_MAC_RXICMP_GOOD_PACKETS_RXICMPGDPKT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXICMP_GOOD_PACKETS_RXICMPGDPKT_SHIFT)) & ENET_QOS_MAC_RXICMP_GOOD_PACKETS_RXICMPGDPKT_MASK)
/*! @} */

/*! @name MAC_RXICMP_ERROR_PACKETS - IPv6 Datagrams Received with ICMP Checksum Error */
/*! @{ */

#define ENET_QOS_MAC_RXICMP_ERROR_PACKETS_RXICMPERRPKT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXICMP_ERROR_PACKETS_RXICMPERRPKT_SHIFT (0U)
/*! RXICMPERRPKT - RxICMP Error Packets This field indicates the number of good IP datagrams
 *    received whose ICMP payload has a checksum error.
 */
#define ENET_QOS_MAC_RXICMP_ERROR_PACKETS_RXICMPERRPKT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXICMP_ERROR_PACKETS_RXICMPERRPKT_SHIFT)) & ENET_QOS_MAC_RXICMP_ERROR_PACKETS_RXICMPERRPKT_MASK)
/*! @} */

/*! @name MAC_RXIPV4_GOOD_OCTETS - Good Bytes Received in IPv4 Datagrams */
/*! @{ */

#define ENET_QOS_MAC_RXIPV4_GOOD_OCTETS_RXIPV4GDOCT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV4_GOOD_OCTETS_RXIPV4GDOCT_SHIFT (0U)
/*! RXIPV4GDOCT - RxIPv4 Good Octets This field indicates the number of bytes received in good IPv4
 *    datagrams encapsulating TCP, UDP, or ICMP data.
 */
#define ENET_QOS_MAC_RXIPV4_GOOD_OCTETS_RXIPV4GDOCT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV4_GOOD_OCTETS_RXIPV4GDOCT_SHIFT)) & ENET_QOS_MAC_RXIPV4_GOOD_OCTETS_RXIPV4GDOCT_MASK)
/*! @} */

/*! @name MAC_RXIPV4_HEADER_ERROR_OCTETS - Bytes Received in IPv4 Datagrams with Header Errors */
/*! @{ */

#define ENET_QOS_MAC_RXIPV4_HEADER_ERROR_OCTETS_RXIPV4HDRERROCT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV4_HEADER_ERROR_OCTETS_RXIPV4HDRERROCT_SHIFT (0U)
/*! RXIPV4HDRERROCT - RxIPv4 Header Error Octets This field indicates the number of bytes received
 *    in IPv4 datagrams with header errors (checksum, length, version mismatch).
 */
#define ENET_QOS_MAC_RXIPV4_HEADER_ERROR_OCTETS_RXIPV4HDRERROCT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV4_HEADER_ERROR_OCTETS_RXIPV4HDRERROCT_SHIFT)) & ENET_QOS_MAC_RXIPV4_HEADER_ERROR_OCTETS_RXIPV4HDRERROCT_MASK)
/*! @} */

/*! @name MAC_RXIPV4_NO_PAYLOAD_OCTETS - Bytes Received in IPv4 Datagrams with No Payload */
/*! @{ */

#define ENET_QOS_MAC_RXIPV4_NO_PAYLOAD_OCTETS_RXIPV4NOPAYOCT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV4_NO_PAYLOAD_OCTETS_RXIPV4NOPAYOCT_SHIFT (0U)
/*! RXIPV4NOPAYOCT - RxIPv4 Payload Octets This field indicates the number of bytes received in IPv4
 *    datagrams that did not have a TCP, UDP, or ICMP payload.
 */
#define ENET_QOS_MAC_RXIPV4_NO_PAYLOAD_OCTETS_RXIPV4NOPAYOCT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV4_NO_PAYLOAD_OCTETS_RXIPV4NOPAYOCT_SHIFT)) & ENET_QOS_MAC_RXIPV4_NO_PAYLOAD_OCTETS_RXIPV4NOPAYOCT_MASK)
/*! @} */

/*! @name MAC_RXIPV4_FRAGMENTED_OCTETS - Bytes Received in Fragmented IPv4 Datagrams */
/*! @{ */

#define ENET_QOS_MAC_RXIPV4_FRAGMENTED_OCTETS_RXIPV4FRAGOCT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV4_FRAGMENTED_OCTETS_RXIPV4FRAGOCT_SHIFT (0U)
/*! RXIPV4FRAGOCT - RxIPv4 Fragmented Octets This field indicates the number of bytes received in fragmented IPv4 datagrams. */
#define ENET_QOS_MAC_RXIPV4_FRAGMENTED_OCTETS_RXIPV4FRAGOCT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV4_FRAGMENTED_OCTETS_RXIPV4FRAGOCT_SHIFT)) & ENET_QOS_MAC_RXIPV4_FRAGMENTED_OCTETS_RXIPV4FRAGOCT_MASK)
/*! @} */

/*! @name MAC_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS - Bytes Received with UDP Checksum Disabled */
/*! @{ */

#define ENET_QOS_MAC_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS_RXIPV4UDSBLOCT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS_RXIPV4UDSBLOCT_SHIFT (0U)
/*! RXIPV4UDSBLOCT - RxIPv4 UDP Checksum Disable Octets This field indicates the number of bytes
 *    received in a UDP segment that had the UDP checksum disabled.
 */
#define ENET_QOS_MAC_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS_RXIPV4UDSBLOCT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS_RXIPV4UDSBLOCT_SHIFT)) & ENET_QOS_MAC_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS_RXIPV4UDSBLOCT_MASK)
/*! @} */

/*! @name MAC_RXIPV6_GOOD_OCTETS - Bytes Received in Good IPv6 Datagrams */
/*! @{ */

#define ENET_QOS_MAC_RXIPV6_GOOD_OCTETS_RXIPV6GDOCT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV6_GOOD_OCTETS_RXIPV6GDOCT_SHIFT (0U)
/*! RXIPV6GDOCT - RxIPv6 Good Octets This field indicates the number of bytes received in good IPv6
 *    datagrams encapsulating TCP, UDP, or ICMP data.
 */
#define ENET_QOS_MAC_RXIPV6_GOOD_OCTETS_RXIPV6GDOCT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV6_GOOD_OCTETS_RXIPV6GDOCT_SHIFT)) & ENET_QOS_MAC_RXIPV6_GOOD_OCTETS_RXIPV6GDOCT_MASK)
/*! @} */

/*! @name MAC_RXIPV6_HEADER_ERROR_OCTETS - Bytes Received in IPv6 Datagrams with Data Errors */
/*! @{ */

#define ENET_QOS_MAC_RXIPV6_HEADER_ERROR_OCTETS_RXIPV6HDRERROCT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV6_HEADER_ERROR_OCTETS_RXIPV6HDRERROCT_SHIFT (0U)
/*! RXIPV6HDRERROCT - RxIPv6 Header Error Octets This field indicates the number of bytes received
 *    in IPv6 datagrams with header errors (length, version mismatch).
 */
#define ENET_QOS_MAC_RXIPV6_HEADER_ERROR_OCTETS_RXIPV6HDRERROCT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV6_HEADER_ERROR_OCTETS_RXIPV6HDRERROCT_SHIFT)) & ENET_QOS_MAC_RXIPV6_HEADER_ERROR_OCTETS_RXIPV6HDRERROCT_MASK)
/*! @} */

/*! @name MAC_RXIPV6_NO_PAYLOAD_OCTETS - Bytes Received in IPv6 Datagrams with No Payload */
/*! @{ */

#define ENET_QOS_MAC_RXIPV6_NO_PAYLOAD_OCTETS_RXIPV6NOPAYOCT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXIPV6_NO_PAYLOAD_OCTETS_RXIPV6NOPAYOCT_SHIFT (0U)
/*! RXIPV6NOPAYOCT - RxIPv6 Payload Octets This field indicates the number of bytes received in IPv6
 *    datagrams that did not have a TCP, UDP, or ICMP payload.
 */
#define ENET_QOS_MAC_RXIPV6_NO_PAYLOAD_OCTETS_RXIPV6NOPAYOCT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXIPV6_NO_PAYLOAD_OCTETS_RXIPV6NOPAYOCT_SHIFT)) & ENET_QOS_MAC_RXIPV6_NO_PAYLOAD_OCTETS_RXIPV6NOPAYOCT_MASK)
/*! @} */

/*! @name MAC_RXUDP_GOOD_OCTETS - Bytes Received in Good UDP Segment */
/*! @{ */

#define ENET_QOS_MAC_RXUDP_GOOD_OCTETS_RXUDPGDOCT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXUDP_GOOD_OCTETS_RXUDPGDOCT_SHIFT (0U)
/*! RXUDPGDOCT - RxUDP Good Octets This field indicates the number of bytes received in a good UDP segment. */
#define ENET_QOS_MAC_RXUDP_GOOD_OCTETS_RXUDPGDOCT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXUDP_GOOD_OCTETS_RXUDPGDOCT_SHIFT)) & ENET_QOS_MAC_RXUDP_GOOD_OCTETS_RXUDPGDOCT_MASK)
/*! @} */

/*! @name MAC_RXUDP_ERROR_OCTETS - Bytes Received in UDP Segment with Checksum Errors */
/*! @{ */

#define ENET_QOS_MAC_RXUDP_ERROR_OCTETS_RXUDPERROCT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXUDP_ERROR_OCTETS_RXUDPERROCT_SHIFT (0U)
/*! RXUDPERROCT - RxUDP Error Octets This field indicates the number of bytes received in a UDP segment that had checksum errors. */
#define ENET_QOS_MAC_RXUDP_ERROR_OCTETS_RXUDPERROCT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXUDP_ERROR_OCTETS_RXUDPERROCT_SHIFT)) & ENET_QOS_MAC_RXUDP_ERROR_OCTETS_RXUDPERROCT_MASK)
/*! @} */

/*! @name MAC_RXTCP_GOOD_OCTETS - Bytes Received in Good TCP Segment */
/*! @{ */

#define ENET_QOS_MAC_RXTCP_GOOD_OCTETS_RXTCPGDOCT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXTCP_GOOD_OCTETS_RXTCPGDOCT_SHIFT (0U)
/*! RXTCPGDOCT - RxTCP Good Octets This field indicates the number of bytes received in a good TCP segment. */
#define ENET_QOS_MAC_RXTCP_GOOD_OCTETS_RXTCPGDOCT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXTCP_GOOD_OCTETS_RXTCPGDOCT_SHIFT)) & ENET_QOS_MAC_RXTCP_GOOD_OCTETS_RXTCPGDOCT_MASK)
/*! @} */

/*! @name MAC_RXTCP_ERROR_OCTETS - Bytes Received in TCP Segment with Checksum Errors */
/*! @{ */

#define ENET_QOS_MAC_RXTCP_ERROR_OCTETS_RXTCPERROCT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXTCP_ERROR_OCTETS_RXTCPERROCT_SHIFT (0U)
/*! RXTCPERROCT - RxTCP Error Octets This field indicates the number of bytes received in a TCP segment that had checksum errors. */
#define ENET_QOS_MAC_RXTCP_ERROR_OCTETS_RXTCPERROCT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXTCP_ERROR_OCTETS_RXTCPERROCT_SHIFT)) & ENET_QOS_MAC_RXTCP_ERROR_OCTETS_RXTCPERROCT_MASK)
/*! @} */

/*! @name MAC_RXICMP_GOOD_OCTETS - Bytes Received in Good ICMP Segment */
/*! @{ */

#define ENET_QOS_MAC_RXICMP_GOOD_OCTETS_RXICMPGDOCT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXICMP_GOOD_OCTETS_RXICMPGDOCT_SHIFT (0U)
/*! RXICMPGDOCT - RxICMP Good Octets This field indicates the number of bytes received in a good ICMP segment. */
#define ENET_QOS_MAC_RXICMP_GOOD_OCTETS_RXICMPGDOCT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXICMP_GOOD_OCTETS_RXICMPGDOCT_SHIFT)) & ENET_QOS_MAC_RXICMP_GOOD_OCTETS_RXICMPGDOCT_MASK)
/*! @} */

/*! @name MAC_RXICMP_ERROR_OCTETS - Bytes Received in ICMP Segment with Checksum Errors */
/*! @{ */

#define ENET_QOS_MAC_RXICMP_ERROR_OCTETS_RXICMPERROCT_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_RXICMP_ERROR_OCTETS_RXICMPERROCT_SHIFT (0U)
/*! RXICMPERROCT - RxICMP Error Octets This field indicates the number of bytes received in a ICMP segment that had checksum errors. */
#define ENET_QOS_MAC_RXICMP_ERROR_OCTETS_RXICMPERROCT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_RXICMP_ERROR_OCTETS_RXICMPERROCT_SHIFT)) & ENET_QOS_MAC_RXICMP_ERROR_OCTETS_RXICMPERROCT_MASK)
/*! @} */

/*! @name MAC_MMC_FPE_TX_INTERRUPT - MMC FPE Transmit Interrupt */
/*! @{ */

#define ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_FCIS_MASK (0x1U)
#define ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_FCIS_SHIFT (0U)
/*! FCIS - MMC Tx FPE Fragment Counter Interrupt status This bit is set when the
 *    Tx_FPE_Fragment_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Tx FPE Fragment Counter Interrupt status not detected
 *  0b1..MMC Tx FPE Fragment Counter Interrupt status detected
 */
#define ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_FCIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_FCIS_SHIFT)) & ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_FCIS_MASK)

#define ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_HRCIS_MASK (0x2U)
#define ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_HRCIS_SHIFT (1U)
/*! HRCIS - MMC Tx Hold Request Counter Interrupt Status This bit is set when the Tx_Hold_Req_Cntr
 *    counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Tx Hold Request Counter Interrupt Status not detected
 *  0b1..MMC Tx Hold Request Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_HRCIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_HRCIS_SHIFT)) & ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_HRCIS_MASK)
/*! @} */

/*! @name MAC_MMC_FPE_TX_INTERRUPT_MASK - MMC FPE Transmit Mask Interrupt */
/*! @{ */

#define ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_MASK_FCIM_MASK (0x1U)
#define ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_MASK_FCIM_SHIFT (0U)
/*! FCIM - MMC Transmit Fragment Counter Interrupt Mask Setting this bit masks the interrupt when
 *    the Tx_FPE_Fragment_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Fragment Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Fragment Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_MASK_FCIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_MASK_FCIM_SHIFT)) & ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_MASK_FCIM_MASK)

#define ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_MASK_HRCIM_MASK (0x2U)
#define ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_MASK_HRCIM_SHIFT (1U)
/*! HRCIM - MMC Transmit Hold Request Counter Interrupt Mask Setting this bit masks the interrupt
 *    when the Tx_Hold_Req_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Transmit Hold Request Counter Interrupt Mask is disabled
 *  0b1..MMC Transmit Hold Request Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_MASK_HRCIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_MASK_HRCIM_SHIFT)) & ENET_QOS_MAC_MMC_FPE_TX_INTERRUPT_MASK_HRCIM_MASK)
/*! @} */

/*! @name MAC_MMC_TX_FPE_FRAGMENT_CNTR - MMC FPE Transmitted Fragment Counter */
/*! @{ */

#define ENET_QOS_MAC_MMC_TX_FPE_FRAGMENT_CNTR_TXFFC_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_MMC_TX_FPE_FRAGMENT_CNTR_TXFFC_SHIFT (0U)
/*! TXFFC - Tx FPE Fragment counter This field indicates the number of additional mPackets that has
 *    been transmitted due to preemption Exists when any one of the RX/TX MMC counters are enabled
 *    during FPE Enabled configuration.
 */
#define ENET_QOS_MAC_MMC_TX_FPE_FRAGMENT_CNTR_TXFFC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_FPE_FRAGMENT_CNTR_TXFFC_SHIFT)) & ENET_QOS_MAC_MMC_TX_FPE_FRAGMENT_CNTR_TXFFC_MASK)
/*! @} */

/*! @name MAC_MMC_TX_HOLD_REQ_CNTR - MMC FPE Transmitted Hold Request Counter */
/*! @{ */

#define ENET_QOS_MAC_MMC_TX_HOLD_REQ_CNTR_TXHRC_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_MMC_TX_HOLD_REQ_CNTR_TXHRC_SHIFT (0U)
/*! TXHRC - Tx Hold Request Counter This field indicates count of number of a hold request is given to MAC. */
#define ENET_QOS_MAC_MMC_TX_HOLD_REQ_CNTR_TXHRC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_TX_HOLD_REQ_CNTR_TXHRC_SHIFT)) & ENET_QOS_MAC_MMC_TX_HOLD_REQ_CNTR_TXHRC_MASK)
/*! @} */

/*! @name MAC_MMC_FPE_RX_INTERRUPT - MMC FPE Receive Interrupt */
/*! @{ */

#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_PAECIS_MASK (0x1U)
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_PAECIS_SHIFT (0U)
/*! PAECIS - MMC Rx Packet Assembly Error Counter Interrupt Status This bit is set when the
 *    Rx_Packet_Assemble_Err_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Rx Packet Assembly Error Counter Interrupt Status not detected
 *  0b1..MMC Rx Packet Assembly Error Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_PAECIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_PAECIS_SHIFT)) & ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_PAECIS_MASK)

#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_PSECIS_MASK (0x2U)
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_PSECIS_SHIFT (1U)
/*! PSECIS - MMC Rx Packet SMD Error Counter Interrupt Status This bit is set when the
 *    Rx_Packet_SMD_Err_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Rx Packet SMD Error Counter Interrupt Status not detected
 *  0b1..MMC Rx Packet SMD Error Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_PSECIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_PSECIS_SHIFT)) & ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_PSECIS_MASK)

#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_PAOCIS_MASK (0x4U)
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_PAOCIS_SHIFT (2U)
/*! PAOCIS - MMC Rx Packet Assembly OK Counter Interrupt Status This bit is set when the
 *    Rx_Packet_Assemble_Ok_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Rx Packet Assembly OK Counter Interrupt Status not detected
 *  0b1..MMC Rx Packet Assembly OK Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_PAOCIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_PAOCIS_SHIFT)) & ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_PAOCIS_MASK)

#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_FCIS_MASK (0x8U)
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_FCIS_SHIFT (3U)
/*! FCIS - MMC Rx FPE Fragment Counter Interrupt Status This bit is set when the
 *    Rx_FPE_Fragment_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Rx FPE Fragment Counter Interrupt Status not detected
 *  0b1..MMC Rx FPE Fragment Counter Interrupt Status detected
 */
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_FCIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_FCIS_SHIFT)) & ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_FCIS_MASK)
/*! @} */

/*! @name MAC_MMC_FPE_RX_INTERRUPT_MASK - MMC FPE Receive Interrupt Mask */
/*! @{ */

#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_PAECIM_MASK (0x1U)
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_PAECIM_SHIFT (0U)
/*! PAECIM - MMC Rx Packet Assembly Error Counter Interrupt Mask Setting this bit masks the
 *    interrupt when the R Rx_Packet_Assemble_Err_Cntr counter reaches half of the maximum value or the
 *    maximum value.
 *  0b0..MMC Rx Packet Assembly Error Counter Interrupt Mask is disabled
 *  0b1..MMC Rx Packet Assembly Error Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_PAECIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_PAECIM_SHIFT)) & ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_PAECIM_MASK)

#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_PSECIM_MASK (0x2U)
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_PSECIM_SHIFT (1U)
/*! PSECIM - MMC Rx Packet SMD Error Counter Interrupt Mask Setting this bit masks the interrupt
 *    when the R Rx_Packet_SMD_Err_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Rx Packet SMD Error Counter Interrupt Mask is disabled
 *  0b1..MMC Rx Packet SMD Error Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_PSECIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_PSECIM_SHIFT)) & ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_PSECIM_MASK)

#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_PAOCIM_MASK (0x4U)
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_PAOCIM_SHIFT (2U)
/*! PAOCIM - MMC Rx Packet Assembly OK Counter Interrupt Mask Setting this bit masks the interrupt
 *    when the Rx_Packet_Assemble_Ok_Cntr counter reaches half of the maximum value or the maximum
 *    value.
 *  0b0..MMC Rx Packet Assembly OK Counter Interrupt Mask is disabled
 *  0b1..MMC Rx Packet Assembly OK Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_PAOCIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_PAOCIM_SHIFT)) & ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_PAOCIM_MASK)

#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_FCIM_MASK (0x8U)
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_FCIM_SHIFT (3U)
/*! FCIM - MMC Rx FPE Fragment Counter Interrupt Mask Setting this bit masks the interrupt when the
 *    Tx_FPE_Fragment_Cntr counter reaches half of the maximum value or the maximum value.
 *  0b0..MMC Rx FPE Fragment Counter Interrupt Mask is disabled
 *  0b1..MMC Rx FPE Fragment Counter Interrupt Mask is enabled
 */
#define ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_FCIM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_FCIM_SHIFT)) & ENET_QOS_MAC_MMC_FPE_RX_INTERRUPT_MASK_FCIM_MASK)
/*! @} */

/*! @name MAC_MMC_RX_PACKET_ASSEMBLY_ERR_CNTR - MMC Receive Packet Reassembly Error Counter */
/*! @{ */

#define ENET_QOS_MAC_MMC_RX_PACKET_ASSEMBLY_ERR_CNTR_PAEC_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_MMC_RX_PACKET_ASSEMBLY_ERR_CNTR_PAEC_SHIFT (0U)
/*! PAEC - Rx Packet Assembly Error Counter This field indicates the number of MAC frames with
 *    reassembly errors on the Receiver, due to mismatch in the Fragment Count value.
 */
#define ENET_QOS_MAC_MMC_RX_PACKET_ASSEMBLY_ERR_CNTR_PAEC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_PACKET_ASSEMBLY_ERR_CNTR_PAEC_SHIFT)) & ENET_QOS_MAC_MMC_RX_PACKET_ASSEMBLY_ERR_CNTR_PAEC_MASK)
/*! @} */

/*! @name MAC_MMC_RX_PACKET_SMD_ERR_CNTR - MMC Receive Packet SMD Error Counter */
/*! @{ */

#define ENET_QOS_MAC_MMC_RX_PACKET_SMD_ERR_CNTR_PSEC_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_MMC_RX_PACKET_SMD_ERR_CNTR_PSEC_SHIFT (0U)
/*! PSEC - Rx Packet SMD Error Counter This field indicates the number of MAC frames rejected due to
 *    unknown SMD value and MAC frame fragments rejected due to arriving with an SMD-C when there
 *    was no preceding preempted frame.
 */
#define ENET_QOS_MAC_MMC_RX_PACKET_SMD_ERR_CNTR_PSEC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_PACKET_SMD_ERR_CNTR_PSEC_SHIFT)) & ENET_QOS_MAC_MMC_RX_PACKET_SMD_ERR_CNTR_PSEC_MASK)
/*! @} */

/*! @name MAC_MMC_RX_PACKET_ASSEMBLY_OK_CNTR - MMC Receive Packet Successful Reassembly Counter */
/*! @{ */

#define ENET_QOS_MAC_MMC_RX_PACKET_ASSEMBLY_OK_CNTR_PAOC_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_MMC_RX_PACKET_ASSEMBLY_OK_CNTR_PAOC_SHIFT (0U)
/*! PAOC - Rx Packet Assembly OK Counter This field indicates the number of MAC frames that were
 *    successfully reassembled and delivered to MAC.
 */
#define ENET_QOS_MAC_MMC_RX_PACKET_ASSEMBLY_OK_CNTR_PAOC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_PACKET_ASSEMBLY_OK_CNTR_PAOC_SHIFT)) & ENET_QOS_MAC_MMC_RX_PACKET_ASSEMBLY_OK_CNTR_PAOC_MASK)
/*! @} */

/*! @name MAC_MMC_RX_FPE_FRAGMENT_CNTR - MMC FPE Received Fragment Counter */
/*! @{ */

#define ENET_QOS_MAC_MMC_RX_FPE_FRAGMENT_CNTR_FFC_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_MMC_RX_FPE_FRAGMENT_CNTR_FFC_SHIFT (0U)
/*! FFC - Rx FPE Fragment Counter This field indicates the number of additional mPackets received
 *    due to preemption Exists when at least one of the RX/TX MMC counters are enabled during FPE
 *    Enabled configuration.
 */
#define ENET_QOS_MAC_MMC_RX_FPE_FRAGMENT_CNTR_FFC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_MMC_RX_FPE_FRAGMENT_CNTR_FFC_SHIFT)) & ENET_QOS_MAC_MMC_RX_FPE_FRAGMENT_CNTR_FFC_MASK)
/*! @} */

/*! @name MAC_L3_L4_CONTROL0 - Layer 3 and Layer 4 Control of Filter 0 */
/*! @{ */

#define ENET_QOS_MAC_L3_L4_CONTROL0_L3PEN0_MASK  (0x1U)
#define ENET_QOS_MAC_L3_L4_CONTROL0_L3PEN0_SHIFT (0U)
/*! L3PEN0 - Layer 3 Protocol Enable When this bit is set, the Layer 3 IP Source or Destination
 *    Address matching is enabled for IPv6 packets.
 *  0b0..Layer 3 Protocol is disabled
 *  0b1..Layer 3 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL0_L3PEN0(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL0_L3PEN0_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL0_L3PEN0_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL0_L3SAM0_MASK  (0x4U)
#define ENET_QOS_MAC_L3_L4_CONTROL0_L3SAM0_SHIFT (2U)
/*! L3SAM0 - Layer 3 IP SA Match Enable When this bit is set, the Layer 3 IP Source Address field is enabled for matching.
 *  0b0..Layer 3 IP SA Match is disabled
 *  0b1..Layer 3 IP SA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL0_L3SAM0(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL0_L3SAM0_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL0_L3SAM0_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL0_L3SAIM0_MASK (0x8U)
#define ENET_QOS_MAC_L3_L4_CONTROL0_L3SAIM0_SHIFT (3U)
/*! L3SAIM0 - Layer 3 IP SA Inverse Match Enable When this bit is set, the Layer 3 IP Source Address
 *    field is enabled for inverse matching.
 *  0b0..Layer 3 IP SA Inverse Match is disabled
 *  0b1..Layer 3 IP SA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL0_L3SAIM0(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL0_L3SAIM0_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL0_L3SAIM0_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL0_L3DAM0_MASK  (0x10U)
#define ENET_QOS_MAC_L3_L4_CONTROL0_L3DAM0_SHIFT (4U)
/*! L3DAM0 - Layer 3 IP DA Match Enable When this bit is set, the Layer 3 IP Destination Address field is enabled for matching.
 *  0b0..Layer 3 IP DA Match is disabled
 *  0b1..Layer 3 IP DA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL0_L3DAM0(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL0_L3DAM0_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL0_L3DAM0_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL0_L3DAIM0_MASK (0x20U)
#define ENET_QOS_MAC_L3_L4_CONTROL0_L3DAIM0_SHIFT (5U)
/*! L3DAIM0 - Layer 3 IP DA Inverse Match Enable When this bit is set, the Layer 3 IP Destination
 *    Address field is enabled for inverse matching.
 *  0b0..Layer 3 IP DA Inverse Match is disabled
 *  0b1..Layer 3 IP DA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL0_L3DAIM0(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL0_L3DAIM0_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL0_L3DAIM0_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL0_L3HSBM0_MASK (0x7C0U)
#define ENET_QOS_MAC_L3_L4_CONTROL0_L3HSBM0_SHIFT (6U)
/*! L3HSBM0 - Layer 3 IP SA Higher Bits Match IPv4 Packets: This field contains the number of lower
 *    bits of IP Source Address that are masked for matching in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL0_L3HSBM0(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL0_L3HSBM0_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL0_L3HSBM0_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL0_L3HDBM0_MASK (0xF800U)
#define ENET_QOS_MAC_L3_L4_CONTROL0_L3HDBM0_SHIFT (11U)
/*! L3HDBM0 - Layer 3 IP DA Higher Bits Match IPv4 Packets: This field contains the number of higher
 *    bits of IP Destination Address that are matched in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL0_L3HDBM0(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL0_L3HDBM0_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL0_L3HDBM0_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL0_L4PEN0_MASK  (0x10000U)
#define ENET_QOS_MAC_L3_L4_CONTROL0_L4PEN0_SHIFT (16U)
/*! L4PEN0 - Layer 4 Protocol Enable When this bit is set, the Source and Destination Port number
 *    fields of UDP packets are used for matching.
 *  0b0..Layer 4 Protocol is disabled
 *  0b1..Layer 4 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL0_L4PEN0(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL0_L4PEN0_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL0_L4PEN0_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL0_L4SPM0_MASK  (0x40000U)
#define ENET_QOS_MAC_L3_L4_CONTROL0_L4SPM0_SHIFT (18U)
/*! L4SPM0 - Layer 4 Source Port Match Enable When this bit is set, the Layer 4 Source Port number field is enabled for matching.
 *  0b0..Layer 4 Source Port Match is disabled
 *  0b1..Layer 4 Source Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL0_L4SPM0(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL0_L4SPM0_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL0_L4SPM0_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL0_L4SPIM0_MASK (0x80000U)
#define ENET_QOS_MAC_L3_L4_CONTROL0_L4SPIM0_SHIFT (19U)
/*! L4SPIM0 - Layer 4 Source Port Inverse Match Enable When this bit is set, the Layer 4 Source Port
 *    number field is enabled for inverse matching.
 *  0b0..Layer 4 Source Port Inverse Match is disabled
 *  0b1..Layer 4 Source Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL0_L4SPIM0(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL0_L4SPIM0_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL0_L4SPIM0_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL0_L4DPM0_MASK  (0x100000U)
#define ENET_QOS_MAC_L3_L4_CONTROL0_L4DPM0_SHIFT (20U)
/*! L4DPM0 - Layer 4 Destination Port Match Enable When this bit is set, the Layer 4 Destination
 *    Port number field is enabled for matching.
 *  0b0..Layer 4 Destination Port Match is disabled
 *  0b1..Layer 4 Destination Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL0_L4DPM0(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL0_L4DPM0_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL0_L4DPM0_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL0_L4DPIM0_MASK (0x200000U)
#define ENET_QOS_MAC_L3_L4_CONTROL0_L4DPIM0_SHIFT (21U)
/*! L4DPIM0 - Layer 4 Destination Port Inverse Match Enable When this bit is set, the Layer 4
 *    Destination Port number field is enabled for inverse matching.
 *  0b0..Layer 4 Destination Port Inverse Match is disabled
 *  0b1..Layer 4 Destination Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL0_L4DPIM0(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL0_L4DPIM0_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL0_L4DPIM0_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL0_DMCHN0_MASK  (0x7000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL0_DMCHN0_SHIFT (24U)
/*! DMCHN0 - DMA Channel Number When DMCHEN is set high, this field selects the DMA Channel number
 *    to which the packet passed by this filter is routed.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL0_DMCHN0(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL0_DMCHN0_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL0_DMCHN0_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL0_DMCHEN0_MASK (0x10000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL0_DMCHEN0_SHIFT (28U)
/*! DMCHEN0 - DMA Channel Select Enable When set, this bit enables the selection of the DMA channel
 *    number for the packet that is passed by this L3_L4 filter.
 *  0b0..DMA Channel Select is disabled
 *  0b1..DMA Channel Select is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL0_DMCHEN0(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL0_DMCHEN0_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL0_DMCHEN0_MASK)
/*! @} */

/*! @name MAC_LAYER4_ADDRESS0 - Layer 4 Address 0 */
/*! @{ */

#define ENET_QOS_MAC_LAYER4_ADDRESS0_L4SP0_MASK  (0xFFFFU)
#define ENET_QOS_MAC_LAYER4_ADDRESS0_L4SP0_SHIFT (0U)
/*! L4SP0 - Layer 4 Source Port Number Field When the L4PEN0 bit is reset and the L4SPM0 bit is set
 *    in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the TCP
 *    Source Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS0_L4SP0(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS0_L4SP0_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS0_L4SP0_MASK)

#define ENET_QOS_MAC_LAYER4_ADDRESS0_L4DP0_MASK  (0xFFFF0000U)
#define ENET_QOS_MAC_LAYER4_ADDRESS0_L4DP0_SHIFT (16U)
/*! L4DP0 - Layer 4 Destination Port Number Field When the L4PEN0 bit is reset and the L4DPM0 bit is
 *    set in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the
 *    TCP Destination Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS0_L4DP0(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS0_L4DP0_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS0_L4DP0_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR0_REG0 - Layer 3 Address 0 Register 0 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR0_REG0_L3A00_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR0_REG0_L3A00_SHIFT (0U)
/*! L3A00 - Layer 3 Address 0 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[31:0] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR0_REG0_L3A00(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR0_REG0_L3A00_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR0_REG0_L3A00_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR1_REG0 - Layer 3 Address 1 Register 0 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR1_REG0_L3A10_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR1_REG0_L3A10_SHIFT (0U)
/*! L3A10 - Layer 3 Address 1 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[63:32] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR1_REG0_L3A10(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR1_REG0_L3A10_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR1_REG0_L3A10_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR2_REG0 - Layer 3 Address 2 Register 0 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR2_REG0_L3A20_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR2_REG0_L3A20_SHIFT (0U)
/*! L3A20 - Layer 3 Address 2 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[95:64] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR2_REG0_L3A20(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR2_REG0_L3A20_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR2_REG0_L3A20_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR3_REG0 - Layer 3 Address 3 Register 0 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR3_REG0_L3A30_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR3_REG0_L3A30_SHIFT (0U)
/*! L3A30 - Layer 3 Address 3 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[127:96] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR3_REG0_L3A30(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR3_REG0_L3A30_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR3_REG0_L3A30_MASK)
/*! @} */

/*! @name MAC_L3_L4_CONTROL1 - Layer 3 and Layer 4 Control of Filter 1 */
/*! @{ */

#define ENET_QOS_MAC_L3_L4_CONTROL1_L3PEN1_MASK  (0x1U)
#define ENET_QOS_MAC_L3_L4_CONTROL1_L3PEN1_SHIFT (0U)
/*! L3PEN1 - Layer 3 Protocol Enable When this bit is set, the Layer 3 IP Source or Destination
 *    Address matching is enabled for IPv6 packets.
 *  0b0..Layer 3 Protocol is disabled
 *  0b1..Layer 3 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL1_L3PEN1(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL1_L3PEN1_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL1_L3PEN1_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL1_L3SAM1_MASK  (0x4U)
#define ENET_QOS_MAC_L3_L4_CONTROL1_L3SAM1_SHIFT (2U)
/*! L3SAM1 - Layer 3 IP SA Match Enable When this bit is set, the Layer 3 IP Source Address field is enabled for matching.
 *  0b0..Layer 3 IP SA Match is disabled
 *  0b1..Layer 3 IP SA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL1_L3SAM1(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL1_L3SAM1_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL1_L3SAM1_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL1_L3SAIM1_MASK (0x8U)
#define ENET_QOS_MAC_L3_L4_CONTROL1_L3SAIM1_SHIFT (3U)
/*! L3SAIM1 - Layer 3 IP SA Inverse Match Enable When this bit is set, the Layer 3 IP Source Address
 *    field is enabled for inverse matching.
 *  0b0..Layer 3 IP SA Inverse Match is disabled
 *  0b1..Layer 3 IP SA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL1_L3SAIM1(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL1_L3SAIM1_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL1_L3SAIM1_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL1_L3DAM1_MASK  (0x10U)
#define ENET_QOS_MAC_L3_L4_CONTROL1_L3DAM1_SHIFT (4U)
/*! L3DAM1 - Layer 3 IP DA Match Enable When this bit is set, the Layer 3 IP Destination Address field is enabled for matching.
 *  0b0..Layer 3 IP DA Match is disabled
 *  0b1..Layer 3 IP DA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL1_L3DAM1(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL1_L3DAM1_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL1_L3DAM1_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL1_L3DAIM1_MASK (0x20U)
#define ENET_QOS_MAC_L3_L4_CONTROL1_L3DAIM1_SHIFT (5U)
/*! L3DAIM1 - Layer 3 IP DA Inverse Match Enable When this bit is set, the Layer 3 IP Destination
 *    Address field is enabled for inverse matching.
 *  0b0..Layer 3 IP DA Inverse Match is disabled
 *  0b1..Layer 3 IP DA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL1_L3DAIM1(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL1_L3DAIM1_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL1_L3DAIM1_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL1_L3HSBM1_MASK (0x7C0U)
#define ENET_QOS_MAC_L3_L4_CONTROL1_L3HSBM1_SHIFT (6U)
/*! L3HSBM1 - Layer 3 IP SA Higher Bits Match IPv4 Packets: This field contains the number of lower
 *    bits of IP Source Address that are masked for matching in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL1_L3HSBM1(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL1_L3HSBM1_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL1_L3HSBM1_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL1_L3HDBM1_MASK (0xF800U)
#define ENET_QOS_MAC_L3_L4_CONTROL1_L3HDBM1_SHIFT (11U)
/*! L3HDBM1 - Layer 3 IP DA Higher Bits Match IPv4 Packets: This field contains the number of higher
 *    bits of IP Destination Address that are matched in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL1_L3HDBM1(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL1_L3HDBM1_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL1_L3HDBM1_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL1_L4PEN1_MASK  (0x10000U)
#define ENET_QOS_MAC_L3_L4_CONTROL1_L4PEN1_SHIFT (16U)
/*! L4PEN1 - Layer 4 Protocol Enable When this bit is set, the Source and Destination Port number
 *    fields of UDP packets are used for matching.
 *  0b0..Layer 4 Protocol is disabled
 *  0b1..Layer 4 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL1_L4PEN1(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL1_L4PEN1_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL1_L4PEN1_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL1_L4SPM1_MASK  (0x40000U)
#define ENET_QOS_MAC_L3_L4_CONTROL1_L4SPM1_SHIFT (18U)
/*! L4SPM1 - Layer 4 Source Port Match Enable When this bit is set, the Layer 4 Source Port number field is enabled for matching.
 *  0b0..Layer 4 Source Port Match is disabled
 *  0b1..Layer 4 Source Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL1_L4SPM1(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL1_L4SPM1_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL1_L4SPM1_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL1_L4SPIM1_MASK (0x80000U)
#define ENET_QOS_MAC_L3_L4_CONTROL1_L4SPIM1_SHIFT (19U)
/*! L4SPIM1 - Layer 4 Source Port Inverse Match Enable When this bit is set, the Layer 4 Source Port
 *    number field is enabled for inverse matching.
 *  0b0..Layer 4 Source Port Inverse Match is disabled
 *  0b1..Layer 4 Source Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL1_L4SPIM1(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL1_L4SPIM1_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL1_L4SPIM1_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL1_L4DPM1_MASK  (0x100000U)
#define ENET_QOS_MAC_L3_L4_CONTROL1_L4DPM1_SHIFT (20U)
/*! L4DPM1 - Layer 4 Destination Port Match Enable When this bit is set, the Layer 4 Destination
 *    Port number field is enabled for matching.
 *  0b0..Layer 4 Destination Port Match is disabled
 *  0b1..Layer 4 Destination Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL1_L4DPM1(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL1_L4DPM1_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL1_L4DPM1_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL1_L4DPIM1_MASK (0x200000U)
#define ENET_QOS_MAC_L3_L4_CONTROL1_L4DPIM1_SHIFT (21U)
/*! L4DPIM1 - Layer 4 Destination Port Inverse Match Enable When this bit is set, the Layer 4
 *    Destination Port number field is enabled for inverse matching.
 *  0b0..Layer 4 Destination Port Inverse Match is disabled
 *  0b1..Layer 4 Destination Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL1_L4DPIM1(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL1_L4DPIM1_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL1_L4DPIM1_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL1_DMCHN1_MASK  (0x7000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL1_DMCHN1_SHIFT (24U)
/*! DMCHN1 - DMA Channel Number When DMCHEN is set high, this field selects the DMA Channel number
 *    to which the packet passed by this filter is routed.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL1_DMCHN1(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL1_DMCHN1_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL1_DMCHN1_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL1_DMCHEN1_MASK (0x10000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL1_DMCHEN1_SHIFT (28U)
/*! DMCHEN1 - DMA Channel Select Enable When set, this bit enables the selection of the DMA channel
 *    number for the packet that is passed by this L3_L4 filter.
 *  0b0..DMA Channel Select is disabled
 *  0b1..DMA Channel Select is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL1_DMCHEN1(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL1_DMCHEN1_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL1_DMCHEN1_MASK)
/*! @} */

/*! @name MAC_LAYER4_ADDRESS1 - Layer 4 Address 0 */
/*! @{ */

#define ENET_QOS_MAC_LAYER4_ADDRESS1_L4SP1_MASK  (0xFFFFU)
#define ENET_QOS_MAC_LAYER4_ADDRESS1_L4SP1_SHIFT (0U)
/*! L4SP1 - Layer 4 Source Port Number Field When the L4PEN1 bit is reset and the L4SPM0 bit is set
 *    in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the TCP
 *    Source Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS1_L4SP1(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS1_L4SP1_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS1_L4SP1_MASK)

#define ENET_QOS_MAC_LAYER4_ADDRESS1_L4DP1_MASK  (0xFFFF0000U)
#define ENET_QOS_MAC_LAYER4_ADDRESS1_L4DP1_SHIFT (16U)
/*! L4DP1 - Layer 4 Destination Port Number Field When the L4PEN0 bit is reset and the L4DPM1 bit is
 *    set in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the
 *    TCP Destination Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS1_L4DP1(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS1_L4DP1_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS1_L4DP1_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR0_REG1 - Layer 3 Address 0 Register 1 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR0_REG1_L3A01_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR0_REG1_L3A01_SHIFT (0U)
/*! L3A01 - Layer 3 Address 0 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[31:0] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR0_REG1_L3A01(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR0_REG1_L3A01_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR0_REG1_L3A01_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR1_REG1 - Layer 3 Address 1 Register 1 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR1_REG1_L3A11_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR1_REG1_L3A11_SHIFT (0U)
/*! L3A11 - Layer 3 Address 1 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[63:32] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR1_REG1_L3A11(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR1_REG1_L3A11_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR1_REG1_L3A11_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR2_REG1 - Layer 3 Address 2 Register 1 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR2_REG1_L3A21_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR2_REG1_L3A21_SHIFT (0U)
/*! L3A21 - Layer 3 Address 2 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[95:64] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR2_REG1_L3A21(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR2_REG1_L3A21_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR2_REG1_L3A21_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR3_REG1 - Layer 3 Address 3 Register 1 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR3_REG1_L3A31_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR3_REG1_L3A31_SHIFT (0U)
/*! L3A31 - Layer 3 Address 3 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[127:96] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR3_REG1_L3A31(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR3_REG1_L3A31_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR3_REG1_L3A31_MASK)
/*! @} */

/*! @name MAC_L3_L4_CONTROL2 - Layer 3 and Layer 4 Control of Filter 2 */
/*! @{ */

#define ENET_QOS_MAC_L3_L4_CONTROL2_L3PEN2_MASK  (0x1U)
#define ENET_QOS_MAC_L3_L4_CONTROL2_L3PEN2_SHIFT (0U)
/*! L3PEN2 - Layer 3 Protocol Enable When this bit is set, the Layer 3 IP Source or Destination
 *    Address matching is enabled for IPv6 packets.
 *  0b0..Layer 3 Protocol is disabled
 *  0b1..Layer 3 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL2_L3PEN2(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL2_L3PEN2_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL2_L3PEN2_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL2_L3SAM2_MASK  (0x4U)
#define ENET_QOS_MAC_L3_L4_CONTROL2_L3SAM2_SHIFT (2U)
/*! L3SAM2 - Layer 3 IP SA Match Enable When this bit is set, the Layer 3 IP Source Address field is enabled for matching.
 *  0b0..Layer 3 IP SA Match is disabled
 *  0b1..Layer 3 IP SA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL2_L3SAM2(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL2_L3SAM2_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL2_L3SAM2_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL2_L3SAIM2_MASK (0x8U)
#define ENET_QOS_MAC_L3_L4_CONTROL2_L3SAIM2_SHIFT (3U)
/*! L3SAIM2 - Layer 3 IP SA Inverse Match Enable When this bit is set, the Layer 3 IP Source Address
 *    field is enabled for inverse matching.
 *  0b0..Layer 3 IP SA Inverse Match is disabled
 *  0b1..Layer 3 IP SA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL2_L3SAIM2(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL2_L3SAIM2_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL2_L3SAIM2_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL2_L3DAM2_MASK  (0x10U)
#define ENET_QOS_MAC_L3_L4_CONTROL2_L3DAM2_SHIFT (4U)
/*! L3DAM2 - Layer 3 IP DA Match Enable When this bit is set, the Layer 3 IP Destination Address field is enabled for matching.
 *  0b0..Layer 3 IP DA Match is disabled
 *  0b1..Layer 3 IP DA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL2_L3DAM2(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL2_L3DAM2_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL2_L3DAM2_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL2_L3DAIM2_MASK (0x20U)
#define ENET_QOS_MAC_L3_L4_CONTROL2_L3DAIM2_SHIFT (5U)
/*! L3DAIM2 - Layer 3 IP DA Inverse Match Enable When this bit is set, the Layer 3 IP Destination
 *    Address field is enabled for inverse matching.
 *  0b0..Layer 3 IP DA Inverse Match is disabled
 *  0b1..Layer 3 IP DA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL2_L3DAIM2(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL2_L3DAIM2_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL2_L3DAIM2_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL2_L3HSBM2_MASK (0x7C0U)
#define ENET_QOS_MAC_L3_L4_CONTROL2_L3HSBM2_SHIFT (6U)
/*! L3HSBM2 - Layer 3 IP SA Higher Bits Match IPv4 Packets: This field contains the number of lower
 *    bits of IP Source Address that are masked for matching in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL2_L3HSBM2(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL2_L3HSBM2_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL2_L3HSBM2_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL2_L3HDBM2_MASK (0xF800U)
#define ENET_QOS_MAC_L3_L4_CONTROL2_L3HDBM2_SHIFT (11U)
/*! L3HDBM2 - Layer 3 IP DA Higher Bits Match IPv4 Packets: This field contains the number of higher
 *    bits of IP Destination Address that are matched in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL2_L3HDBM2(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL2_L3HDBM2_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL2_L3HDBM2_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL2_L4PEN2_MASK  (0x10000U)
#define ENET_QOS_MAC_L3_L4_CONTROL2_L4PEN2_SHIFT (16U)
/*! L4PEN2 - Layer 4 Protocol Enable When this bit is set, the Source and Destination Port number
 *    fields of UDP packets are used for matching.
 *  0b0..Layer 4 Protocol is disabled
 *  0b1..Layer 4 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL2_L4PEN2(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL2_L4PEN2_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL2_L4PEN2_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL2_L4SPM2_MASK  (0x40000U)
#define ENET_QOS_MAC_L3_L4_CONTROL2_L4SPM2_SHIFT (18U)
/*! L4SPM2 - Layer 4 Source Port Match Enable When this bit is set, the Layer 4 Source Port number field is enabled for matching.
 *  0b0..Layer 4 Source Port Match is disabled
 *  0b1..Layer 4 Source Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL2_L4SPM2(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL2_L4SPM2_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL2_L4SPM2_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL2_L4SPIM2_MASK (0x80000U)
#define ENET_QOS_MAC_L3_L4_CONTROL2_L4SPIM2_SHIFT (19U)
/*! L4SPIM2 - Layer 4 Source Port Inverse Match Enable When this bit is set, the Layer 4 Source Port
 *    number field is enabled for inverse matching.
 *  0b0..Layer 4 Source Port Inverse Match is disabled
 *  0b1..Layer 4 Source Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL2_L4SPIM2(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL2_L4SPIM2_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL2_L4SPIM2_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL2_L4DPM2_MASK  (0x100000U)
#define ENET_QOS_MAC_L3_L4_CONTROL2_L4DPM2_SHIFT (20U)
/*! L4DPM2 - Layer 4 Destination Port Match Enable When this bit is set, the Layer 4 Destination
 *    Port number field is enabled for matching.
 *  0b0..Layer 4 Destination Port Match is disabled
 *  0b1..Layer 4 Destination Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL2_L4DPM2(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL2_L4DPM2_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL2_L4DPM2_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL2_L4DPIM2_MASK (0x200000U)
#define ENET_QOS_MAC_L3_L4_CONTROL2_L4DPIM2_SHIFT (21U)
/*! L4DPIM2 - Layer 4 Destination Port Inverse Match Enable When this bit is set, the Layer 4
 *    Destination Port number field is enabled for inverse matching.
 *  0b0..Layer 4 Destination Port Inverse Match is disabled
 *  0b1..Layer 4 Destination Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL2_L4DPIM2(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL2_L4DPIM2_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL2_L4DPIM2_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL2_DMCHN2_MASK  (0x7000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL2_DMCHN2_SHIFT (24U)
/*! DMCHN2 - DMA Channel Number When DMCHEN is set high, this field selects the DMA Channel number
 *    to which the packet passed by this filter is routed.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL2_DMCHN2(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL2_DMCHN2_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL2_DMCHN2_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL2_DMCHEN2_MASK (0x10000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL2_DMCHEN2_SHIFT (28U)
/*! DMCHEN2 - DMA Channel Select Enable When set, this bit enables the selection of the DMA channel
 *    number for the packet that is passed by this L3_L4 filter.
 *  0b0..DMA Channel Select is disabled
 *  0b1..DMA Channel Select is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL2_DMCHEN2(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL2_DMCHEN2_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL2_DMCHEN2_MASK)
/*! @} */

/*! @name MAC_LAYER4_ADDRESS2 - Layer 4 Address 2 */
/*! @{ */

#define ENET_QOS_MAC_LAYER4_ADDRESS2_L4SP2_MASK  (0xFFFFU)
#define ENET_QOS_MAC_LAYER4_ADDRESS2_L4SP2_SHIFT (0U)
/*! L4SP2 - Layer 4 Source Port Number Field When the L4PEN2 bit is reset and the L4SPM0 bit is set
 *    in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the TCP
 *    Source Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS2_L4SP2(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS2_L4SP2_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS2_L4SP2_MASK)

#define ENET_QOS_MAC_LAYER4_ADDRESS2_L4DP2_MASK  (0xFFFF0000U)
#define ENET_QOS_MAC_LAYER4_ADDRESS2_L4DP2_SHIFT (16U)
/*! L4DP2 - Layer 4 Destination Port Number Field When the L4PEN2 bit is reset and the L4DPM2 bit is
 *    set in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the
 *    TCP Destination Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS2_L4DP2(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS2_L4DP2_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS2_L4DP2_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR0_REG2 - Layer 3 Address 0 Register 2 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR0_REG2_L3A02_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR0_REG2_L3A02_SHIFT (0U)
/*! L3A02 - Layer 3 Address 0 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[31:0] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR0_REG2_L3A02(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR0_REG2_L3A02_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR0_REG2_L3A02_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR1_REG2 - Layer 3 Address 0 Register 2 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR1_REG2_L3A12_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR1_REG2_L3A12_SHIFT (0U)
/*! L3A12 - Layer 3 Address 1 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[63:32] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR1_REG2_L3A12(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR1_REG2_L3A12_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR1_REG2_L3A12_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR2_REG2 - Layer 3 Address 2 Register 2 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR2_REG2_L3A22_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR2_REG2_L3A22_SHIFT (0U)
/*! L3A22 - Layer 3 Address 2 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[95:64] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR2_REG2_L3A22(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR2_REG2_L3A22_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR2_REG2_L3A22_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR3_REG2 - Layer 3 Address 3 Register 2 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR3_REG2_L3A32_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR3_REG2_L3A32_SHIFT (0U)
/*! L3A32 - Layer 3 Address 3 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[127:96] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR3_REG2_L3A32(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR3_REG2_L3A32_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR3_REG2_L3A32_MASK)
/*! @} */

/*! @name MAC_L3_L4_CONTROL3 - Layer 3 and Layer 4 Control of Filter 3 */
/*! @{ */

#define ENET_QOS_MAC_L3_L4_CONTROL3_L3PEN3_MASK  (0x1U)
#define ENET_QOS_MAC_L3_L4_CONTROL3_L3PEN3_SHIFT (0U)
/*! L3PEN3 - Layer 3 Protocol Enable When this bit is set, the Layer 3 IP Source or Destination
 *    Address matching is enabled for IPv6 packets.
 *  0b0..Layer 3 Protocol is disabled
 *  0b1..Layer 3 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL3_L3PEN3(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL3_L3PEN3_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL3_L3PEN3_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL3_L3SAM3_MASK  (0x4U)
#define ENET_QOS_MAC_L3_L4_CONTROL3_L3SAM3_SHIFT (2U)
/*! L3SAM3 - Layer 3 IP SA Match Enable When this bit is set, the Layer 3 IP Source Address field is enabled for matching.
 *  0b0..Layer 3 IP SA Match is disabled
 *  0b1..Layer 3 IP SA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL3_L3SAM3(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL3_L3SAM3_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL3_L3SAM3_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL3_L3SAIM3_MASK (0x8U)
#define ENET_QOS_MAC_L3_L4_CONTROL3_L3SAIM3_SHIFT (3U)
/*! L3SAIM3 - Layer 3 IP SA Inverse Match Enable When this bit is set, the Layer 3 IP Source Address
 *    field is enabled for inverse matching.
 *  0b0..Layer 3 IP SA Inverse Match is disabled
 *  0b1..Layer 3 IP SA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL3_L3SAIM3(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL3_L3SAIM3_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL3_L3SAIM3_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL3_L3DAM3_MASK  (0x10U)
#define ENET_QOS_MAC_L3_L4_CONTROL3_L3DAM3_SHIFT (4U)
/*! L3DAM3 - Layer 3 IP DA Match Enable When this bit is set, the Layer 3 IP Destination Address field is enabled for matching.
 *  0b0..Layer 3 IP DA Match is disabled
 *  0b1..Layer 3 IP DA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL3_L3DAM3(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL3_L3DAM3_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL3_L3DAM3_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL3_L3DAIM3_MASK (0x20U)
#define ENET_QOS_MAC_L3_L4_CONTROL3_L3DAIM3_SHIFT (5U)
/*! L3DAIM3 - Layer 3 IP DA Inverse Match Enable When this bit is set, the Layer 3 IP Destination
 *    Address field is enabled for inverse matching.
 *  0b0..Layer 3 IP DA Inverse Match is disabled
 *  0b1..Layer 3 IP DA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL3_L3DAIM3(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL3_L3DAIM3_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL3_L3DAIM3_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL3_L3HSBM3_MASK (0x7C0U)
#define ENET_QOS_MAC_L3_L4_CONTROL3_L3HSBM3_SHIFT (6U)
/*! L3HSBM3 - Layer 3 IP SA Higher Bits Match IPv4 Packets: This field contains the number of lower
 *    bits of IP Source Address that are masked for matching in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL3_L3HSBM3(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL3_L3HSBM3_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL3_L3HSBM3_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL3_L3HDBM3_MASK (0xF800U)
#define ENET_QOS_MAC_L3_L4_CONTROL3_L3HDBM3_SHIFT (11U)
/*! L3HDBM3 - Layer 3 IP DA Higher Bits Match IPv4 Packets: This field contains the number of higher
 *    bits of IP Destination Address that are matched in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL3_L3HDBM3(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL3_L3HDBM3_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL3_L3HDBM3_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL3_L4PEN3_MASK  (0x10000U)
#define ENET_QOS_MAC_L3_L4_CONTROL3_L4PEN3_SHIFT (16U)
/*! L4PEN3 - Layer 4 Protocol Enable When this bit is set, the Source and Destination Port number
 *    fields of UDP packets are used for matching.
 *  0b0..Layer 4 Protocol is disabled
 *  0b1..Layer 4 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL3_L4PEN3(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL3_L4PEN3_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL3_L4PEN3_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL3_L4SPM3_MASK  (0x40000U)
#define ENET_QOS_MAC_L3_L4_CONTROL3_L4SPM3_SHIFT (18U)
/*! L4SPM3 - Layer 4 Source Port Match Enable When this bit is set, the Layer 4 Source Port number field is enabled for matching.
 *  0b0..Layer 4 Source Port Match is disabled
 *  0b1..Layer 4 Source Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL3_L4SPM3(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL3_L4SPM3_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL3_L4SPM3_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL3_L4SPIM3_MASK (0x80000U)
#define ENET_QOS_MAC_L3_L4_CONTROL3_L4SPIM3_SHIFT (19U)
/*! L4SPIM3 - Layer 4 Source Port Inverse Match Enable When this bit is set, the Layer 4 Source Port
 *    number field is enabled for inverse matching.
 *  0b0..Layer 4 Source Port Inverse Match is disabled
 *  0b1..Layer 4 Source Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL3_L4SPIM3(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL3_L4SPIM3_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL3_L4SPIM3_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL3_L4DPM3_MASK  (0x100000U)
#define ENET_QOS_MAC_L3_L4_CONTROL3_L4DPM3_SHIFT (20U)
/*! L4DPM3 - Layer 4 Destination Port Match Enable When this bit is set, the Layer 4 Destination
 *    Port number field is enabled for matching.
 *  0b0..Layer 4 Destination Port Match is disabled
 *  0b1..Layer 4 Destination Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL3_L4DPM3(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL3_L4DPM3_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL3_L4DPM3_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL3_L4DPIM3_MASK (0x200000U)
#define ENET_QOS_MAC_L3_L4_CONTROL3_L4DPIM3_SHIFT (21U)
/*! L4DPIM3 - Layer 4 Destination Port Inverse Match Enable When this bit is set, the Layer 4
 *    Destination Port number field is enabled for inverse matching.
 *  0b0..Layer 4 Destination Port Inverse Match is disabled
 *  0b1..Layer 4 Destination Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL3_L4DPIM3(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL3_L4DPIM3_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL3_L4DPIM3_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL3_DMCHN3_MASK  (0x7000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL3_DMCHN3_SHIFT (24U)
/*! DMCHN3 - DMA Channel Number When DMCHEN is set high, this field selects the DMA Channel number
 *    to which the packet passed by this filter is routed.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL3_DMCHN3(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL3_DMCHN3_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL3_DMCHN3_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL3_DMCHEN3_MASK (0x10000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL3_DMCHEN3_SHIFT (28U)
/*! DMCHEN3 - DMA Channel Select Enable When set, this bit enables the selection of the DMA channel
 *    number for the packet that is passed by this L3_L4 filter.
 *  0b0..DMA Channel Select is disabled
 *  0b1..DMA Channel Select is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL3_DMCHEN3(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL3_DMCHEN3_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL3_DMCHEN3_MASK)
/*! @} */

/*! @name MAC_LAYER4_ADDRESS3 - Layer 4 Address 3 */
/*! @{ */

#define ENET_QOS_MAC_LAYER4_ADDRESS3_L4SP3_MASK  (0xFFFFU)
#define ENET_QOS_MAC_LAYER4_ADDRESS3_L4SP3_SHIFT (0U)
/*! L4SP3 - Layer 4 Source Port Number Field When the L4PEN3 bit is reset and the L4SPM0 bit is set
 *    in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the TCP
 *    Source Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS3_L4SP3(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS3_L4SP3_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS3_L4SP3_MASK)

#define ENET_QOS_MAC_LAYER4_ADDRESS3_L4DP3_MASK  (0xFFFF0000U)
#define ENET_QOS_MAC_LAYER4_ADDRESS3_L4DP3_SHIFT (16U)
/*! L4DP3 - Layer 4 Destination Port Number Field When the L4PEN3 bit is reset and the L4DPM3 bit is
 *    set in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the
 *    TCP Destination Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS3_L4DP3(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS3_L4DP3_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS3_L4DP3_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR0_REG3 - Layer 3 Address 0 Register 3 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR0_REG3_L3A03_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR0_REG3_L3A03_SHIFT (0U)
/*! L3A03 - Layer 3 Address 0 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[31:0] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR0_REG3_L3A03(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR0_REG3_L3A03_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR0_REG3_L3A03_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR1_REG3 - Layer 3 Address 1 Register 3 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR1_REG3_L3A13_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR1_REG3_L3A13_SHIFT (0U)
/*! L3A13 - Layer 3 Address 1 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[63:32] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR1_REG3_L3A13(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR1_REG3_L3A13_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR1_REG3_L3A13_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR2_REG3 - Layer 3 Address 2 Register 3 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR2_REG3_L3A23_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR2_REG3_L3A23_SHIFT (0U)
/*! L3A23 - Layer 3 Address 2 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[95:64] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR2_REG3_L3A23(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR2_REG3_L3A23_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR2_REG3_L3A23_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR3_REG3 - Layer 3 Address 3 Register 3 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR3_REG3_L3A33_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR3_REG3_L3A33_SHIFT (0U)
/*! L3A33 - Layer 3 Address 3 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[127:96] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR3_REG3_L3A33(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR3_REG3_L3A33_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR3_REG3_L3A33_MASK)
/*! @} */

/*! @name MAC_L3_L4_CONTROL4 - Layer 3 and Layer 4 Control of Filter 4 */
/*! @{ */

#define ENET_QOS_MAC_L3_L4_CONTROL4_L3PEN4_MASK  (0x1U)
#define ENET_QOS_MAC_L3_L4_CONTROL4_L3PEN4_SHIFT (0U)
/*! L3PEN4 - Layer 3 Protocol Enable When this bit is set, the Layer 3 IP Source or Destination
 *    Address matching is enabled for IPv6 packets.
 *  0b0..Layer 3 Protocol is disabled
 *  0b1..Layer 3 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL4_L3PEN4(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL4_L3PEN4_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL4_L3PEN4_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL4_L3SAM4_MASK  (0x4U)
#define ENET_QOS_MAC_L3_L4_CONTROL4_L3SAM4_SHIFT (2U)
/*! L3SAM4 - Layer 3 IP SA Match Enable When this bit is set, the Layer 3 IP Source Address field is enabled for matching.
 *  0b0..Layer 3 IP SA Match is disabled
 *  0b1..Layer 3 IP SA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL4_L3SAM4(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL4_L3SAM4_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL4_L3SAM4_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL4_L3SAIM4_MASK (0x8U)
#define ENET_QOS_MAC_L3_L4_CONTROL4_L3SAIM4_SHIFT (3U)
/*! L3SAIM4 - Layer 3 IP SA Inverse Match Enable When this bit is set, the Layer 3 IP Source Address
 *    field is enabled for inverse matching.
 *  0b0..Layer 3 IP SA Inverse Match is disabled
 *  0b1..Layer 3 IP SA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL4_L3SAIM4(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL4_L3SAIM4_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL4_L3SAIM4_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL4_L3DAM4_MASK  (0x10U)
#define ENET_QOS_MAC_L3_L4_CONTROL4_L3DAM4_SHIFT (4U)
/*! L3DAM4 - Layer 3 IP DA Match Enable When this bit is set, the Layer 3 IP Destination Address field is enabled for matching.
 *  0b0..Layer 3 IP DA Match is disabled
 *  0b1..Layer 3 IP DA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL4_L3DAM4(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL4_L3DAM4_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL4_L3DAM4_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL4_L3DAIM4_MASK (0x20U)
#define ENET_QOS_MAC_L3_L4_CONTROL4_L3DAIM4_SHIFT (5U)
/*! L3DAIM4 - Layer 3 IP DA Inverse Match Enable When this bit is set, the Layer 3 IP Destination
 *    Address field is enabled for inverse matching.
 *  0b0..Layer 3 IP DA Inverse Match is disabled
 *  0b1..Layer 3 IP DA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL4_L3DAIM4(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL4_L3DAIM4_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL4_L3DAIM4_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL4_L3HSBM4_MASK (0x7C0U)
#define ENET_QOS_MAC_L3_L4_CONTROL4_L3HSBM4_SHIFT (6U)
/*! L3HSBM4 - Layer 3 IP SA Higher Bits Match IPv4 Packets: This field contains the number of lower
 *    bits of IP Source Address that are masked for matching in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL4_L3HSBM4(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL4_L3HSBM4_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL4_L3HSBM4_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL4_L3HDBM4_MASK (0xF800U)
#define ENET_QOS_MAC_L3_L4_CONTROL4_L3HDBM4_SHIFT (11U)
/*! L3HDBM4 - Layer 3 IP DA Higher Bits Match IPv4 Packets: This field contains the number of higher
 *    bits of IP Destination Address that are matched in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL4_L3HDBM4(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL4_L3HDBM4_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL4_L3HDBM4_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL4_L4PEN4_MASK  (0x10000U)
#define ENET_QOS_MAC_L3_L4_CONTROL4_L4PEN4_SHIFT (16U)
/*! L4PEN4 - Layer 4 Protocol Enable When this bit is set, the Source and Destination Port number
 *    fields of UDP packets are used for matching.
 *  0b0..Layer 4 Protocol is disabled
 *  0b1..Layer 4 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL4_L4PEN4(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL4_L4PEN4_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL4_L4PEN4_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL4_L4SPM4_MASK  (0x40000U)
#define ENET_QOS_MAC_L3_L4_CONTROL4_L4SPM4_SHIFT (18U)
/*! L4SPM4 - Layer 4 Source Port Match Enable When this bit is set, the Layer 4 Source Port number field is enabled for matching.
 *  0b0..Layer 4 Source Port Match is disabled
 *  0b1..Layer 4 Source Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL4_L4SPM4(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL4_L4SPM4_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL4_L4SPM4_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL4_L4SPIM4_MASK (0x80000U)
#define ENET_QOS_MAC_L3_L4_CONTROL4_L4SPIM4_SHIFT (19U)
/*! L4SPIM4 - Layer 4 Source Port Inverse Match Enable When this bit is set, the Layer 4 Source Port
 *    number field is enabled for inverse matching.
 *  0b0..Layer 4 Source Port Inverse Match is disabled
 *  0b1..Layer 4 Source Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL4_L4SPIM4(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL4_L4SPIM4_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL4_L4SPIM4_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL4_L4DPM4_MASK  (0x100000U)
#define ENET_QOS_MAC_L3_L4_CONTROL4_L4DPM4_SHIFT (20U)
/*! L4DPM4 - Layer 4 Destination Port Match Enable When this bit is set, the Layer 4 Destination
 *    Port number field is enabled for matching.
 *  0b0..Layer 4 Destination Port Match is disabled
 *  0b1..Layer 4 Destination Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL4_L4DPM4(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL4_L4DPM4_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL4_L4DPM4_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL4_L4DPIM4_MASK (0x200000U)
#define ENET_QOS_MAC_L3_L4_CONTROL4_L4DPIM4_SHIFT (21U)
/*! L4DPIM4 - Layer 4 Destination Port Inverse Match Enable When this bit is set, the Layer 4
 *    Destination Port number field is enabled for inverse matching.
 *  0b0..Layer 4 Destination Port Inverse Match is disabled
 *  0b1..Layer 4 Destination Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL4_L4DPIM4(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL4_L4DPIM4_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL4_L4DPIM4_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL4_DMCHN4_MASK  (0x7000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL4_DMCHN4_SHIFT (24U)
/*! DMCHN4 - DMA Channel Number When DMCHEN is set high, this field selects the DMA Channel number
 *    to which the packet passed by this filter is routed.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL4_DMCHN4(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL4_DMCHN4_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL4_DMCHN4_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL4_DMCHEN4_MASK (0x10000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL4_DMCHEN4_SHIFT (28U)
/*! DMCHEN4 - DMA Channel Select Enable When set, this bit enables the selection of the DMA channel
 *    number for the packet that is passed by this L3_L4 filter.
 *  0b0..DMA Channel Select is disabled
 *  0b1..DMA Channel Select is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL4_DMCHEN4(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL4_DMCHEN4_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL4_DMCHEN4_MASK)
/*! @} */

/*! @name MAC_LAYER4_ADDRESS4 - Layer 4 Address 4 */
/*! @{ */

#define ENET_QOS_MAC_LAYER4_ADDRESS4_L4SP4_MASK  (0xFFFFU)
#define ENET_QOS_MAC_LAYER4_ADDRESS4_L4SP4_SHIFT (0U)
/*! L4SP4 - Layer 4 Source Port Number Field When the L4PEN4 bit is reset and the L4SPM0 bit is set
 *    in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the TCP
 *    Source Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS4_L4SP4(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS4_L4SP4_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS4_L4SP4_MASK)

#define ENET_QOS_MAC_LAYER4_ADDRESS4_L4DP4_MASK  (0xFFFF0000U)
#define ENET_QOS_MAC_LAYER4_ADDRESS4_L4DP4_SHIFT (16U)
/*! L4DP4 - Layer 4 Destination Port Number Field When the L4PEN4 bit is reset and the L4DPM4 bit is
 *    set in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the
 *    TCP Destination Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS4_L4DP4(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS4_L4DP4_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS4_L4DP4_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR0_REG4 - Layer 3 Address 0 Register 4 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR0_REG4_L3A04_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR0_REG4_L3A04_SHIFT (0U)
/*! L3A04 - Layer 3 Address 0 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[31:0] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR0_REG4_L3A04(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR0_REG4_L3A04_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR0_REG4_L3A04_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR1_REG4 - Layer 3 Address 1 Register 4 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR1_REG4_L3A14_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR1_REG4_L3A14_SHIFT (0U)
/*! L3A14 - Layer 3 Address 1 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[63:32] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR1_REG4_L3A14(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR1_REG4_L3A14_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR1_REG4_L3A14_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR2_REG4 - Layer 3 Address 2 Register 4 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR2_REG4_L3A24_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR2_REG4_L3A24_SHIFT (0U)
/*! L3A24 - Layer 3 Address 2 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[95:64] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR2_REG4_L3A24(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR2_REG4_L3A24_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR2_REG4_L3A24_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR3_REG4 - Layer 3 Address 3 Register 4 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR3_REG4_L3A34_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR3_REG4_L3A34_SHIFT (0U)
/*! L3A34 - Layer 3 Address 3 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[127:96] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR3_REG4_L3A34(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR3_REG4_L3A34_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR3_REG4_L3A34_MASK)
/*! @} */

/*! @name MAC_L3_L4_CONTROL5 - Layer 3 and Layer 4 Control of Filter 5 */
/*! @{ */

#define ENET_QOS_MAC_L3_L4_CONTROL5_L3PEN5_MASK  (0x1U)
#define ENET_QOS_MAC_L3_L4_CONTROL5_L3PEN5_SHIFT (0U)
/*! L3PEN5 - Layer 3 Protocol Enable When this bit is set, the Layer 3 IP Source or Destination
 *    Address matching is enabled for IPv6 packets.
 *  0b0..Layer 3 Protocol is disabled
 *  0b1..Layer 3 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL5_L3PEN5(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL5_L3PEN5_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL5_L3PEN5_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL5_L3SAM5_MASK  (0x4U)
#define ENET_QOS_MAC_L3_L4_CONTROL5_L3SAM5_SHIFT (2U)
/*! L3SAM5 - Layer 3 IP SA Match Enable When this bit is set, the Layer 3 IP Source Address field is enabled for matching.
 *  0b0..Layer 3 IP SA Match is disabled
 *  0b1..Layer 3 IP SA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL5_L3SAM5(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL5_L3SAM5_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL5_L3SAM5_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL5_L3SAIM5_MASK (0x8U)
#define ENET_QOS_MAC_L3_L4_CONTROL5_L3SAIM5_SHIFT (3U)
/*! L3SAIM5 - Layer 3 IP SA Inverse Match Enable When this bit is set, the Layer 3 IP Source Address
 *    field is enabled for inverse matching.
 *  0b0..Layer 3 IP SA Inverse Match is disabled
 *  0b1..Layer 3 IP SA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL5_L3SAIM5(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL5_L3SAIM5_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL5_L3SAIM5_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL5_L3DAM5_MASK  (0x10U)
#define ENET_QOS_MAC_L3_L4_CONTROL5_L3DAM5_SHIFT (4U)
/*! L3DAM5 - Layer 3 IP DA Match Enable When this bit is set, the Layer 3 IP Destination Address field is enabled for matching.
 *  0b0..Layer 3 IP DA Match is disabled
 *  0b1..Layer 3 IP DA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL5_L3DAM5(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL5_L3DAM5_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL5_L3DAM5_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL5_L3DAIM5_MASK (0x20U)
#define ENET_QOS_MAC_L3_L4_CONTROL5_L3DAIM5_SHIFT (5U)
/*! L3DAIM5 - Layer 3 IP DA Inverse Match Enable When this bit is set, the Layer 3 IP Destination
 *    Address field is enabled for inverse matching.
 *  0b0..Layer 3 IP DA Inverse Match is disabled
 *  0b1..Layer 3 IP DA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL5_L3DAIM5(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL5_L3DAIM5_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL5_L3DAIM5_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL5_L3HSBM5_MASK (0x7C0U)
#define ENET_QOS_MAC_L3_L4_CONTROL5_L3HSBM5_SHIFT (6U)
/*! L3HSBM5 - Layer 3 IP SA Higher Bits Match IPv4 Packets: This field contains the number of lower
 *    bits of IP Source Address that are masked for matching in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL5_L3HSBM5(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL5_L3HSBM5_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL5_L3HSBM5_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL5_L3HDBM5_MASK (0xF800U)
#define ENET_QOS_MAC_L3_L4_CONTROL5_L3HDBM5_SHIFT (11U)
/*! L3HDBM5 - Layer 3 IP DA Higher Bits Match IPv4 Packets: This field contains the number of higher
 *    bits of IP Destination Address that are matched in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL5_L3HDBM5(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL5_L3HDBM5_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL5_L3HDBM5_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL5_L4PEN5_MASK  (0x10000U)
#define ENET_QOS_MAC_L3_L4_CONTROL5_L4PEN5_SHIFT (16U)
/*! L4PEN5 - Layer 4 Protocol Enable When this bit is set, the Source and Destination Port number
 *    fields of UDP packets are used for matching.
 *  0b0..Layer 4 Protocol is disabled
 *  0b1..Layer 4 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL5_L4PEN5(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL5_L4PEN5_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL5_L4PEN5_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL5_L4SPM5_MASK  (0x40000U)
#define ENET_QOS_MAC_L3_L4_CONTROL5_L4SPM5_SHIFT (18U)
/*! L4SPM5 - Layer 4 Source Port Match Enable When this bit is set, the Layer 4 Source Port number field is enabled for matching.
 *  0b0..Layer 4 Source Port Match is disabled
 *  0b1..Layer 4 Source Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL5_L4SPM5(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL5_L4SPM5_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL5_L4SPM5_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL5_L4SPIM5_MASK (0x80000U)
#define ENET_QOS_MAC_L3_L4_CONTROL5_L4SPIM5_SHIFT (19U)
/*! L4SPIM5 - Layer 4 Source Port Inverse Match Enable When this bit is set, the Layer 4 Source Port
 *    number field is enabled for inverse matching.
 *  0b0..Layer 4 Source Port Inverse Match is disabled
 *  0b1..Layer 4 Source Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL5_L4SPIM5(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL5_L4SPIM5_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL5_L4SPIM5_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL5_L4DPM5_MASK  (0x100000U)
#define ENET_QOS_MAC_L3_L4_CONTROL5_L4DPM5_SHIFT (20U)
/*! L4DPM5 - Layer 4 Destination Port Match Enable When this bit is set, the Layer 4 Destination
 *    Port number field is enabled for matching.
 *  0b0..Layer 4 Destination Port Match is disabled
 *  0b1..Layer 4 Destination Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL5_L4DPM5(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL5_L4DPM5_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL5_L4DPM5_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL5_L4DPIM5_MASK (0x200000U)
#define ENET_QOS_MAC_L3_L4_CONTROL5_L4DPIM5_SHIFT (21U)
/*! L4DPIM5 - Layer 4 Destination Port Inverse Match Enable When this bit is set, the Layer 4
 *    Destination Port number field is enabled for inverse matching.
 *  0b0..Layer 4 Destination Port Inverse Match is disabled
 *  0b1..Layer 4 Destination Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL5_L4DPIM5(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL5_L4DPIM5_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL5_L4DPIM5_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL5_DMCHN5_MASK  (0x7000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL5_DMCHN5_SHIFT (24U)
/*! DMCHN5 - DMA Channel Number When DMCHEN is set high, this field selects the DMA Channel number
 *    to which the packet passed by this filter is routed.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL5_DMCHN5(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL5_DMCHN5_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL5_DMCHN5_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL5_DMCHEN5_MASK (0x10000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL5_DMCHEN5_SHIFT (28U)
/*! DMCHEN5 - DMA Channel Select Enable When set, this bit enables the selection of the DMA channel
 *    number for the packet that is passed by this L3_L4 filter.
 *  0b0..DMA Channel Select is disabled
 *  0b1..DMA Channel Select is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL5_DMCHEN5(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL5_DMCHEN5_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL5_DMCHEN5_MASK)
/*! @} */

/*! @name MAC_LAYER4_ADDRESS5 - Layer 4 Address 5 */
/*! @{ */

#define ENET_QOS_MAC_LAYER4_ADDRESS5_L4SP5_MASK  (0xFFFFU)
#define ENET_QOS_MAC_LAYER4_ADDRESS5_L4SP5_SHIFT (0U)
/*! L4SP5 - Layer 4 Source Port Number Field When the L4PEN5 bit is reset and the L4SPM0 bit is set
 *    in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the TCP
 *    Source Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS5_L4SP5(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS5_L4SP5_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS5_L4SP5_MASK)

#define ENET_QOS_MAC_LAYER4_ADDRESS5_L4DP5_MASK  (0xFFFF0000U)
#define ENET_QOS_MAC_LAYER4_ADDRESS5_L4DP5_SHIFT (16U)
/*! L4DP5 - Layer 4 Destination Port Number Field When the L4PEN5 bit is reset and the L4DPM5 bit is
 *    set in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the
 *    TCP Destination Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS5_L4DP5(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS5_L4DP5_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS5_L4DP5_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR0_REG5 - Layer 3 Address 0 Register 5 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR0_REG5_L3A05_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR0_REG5_L3A05_SHIFT (0U)
/*! L3A05 - Layer 3 Address 0 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[31:0] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR0_REG5_L3A05(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR0_REG5_L3A05_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR0_REG5_L3A05_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR1_REG5 - Layer 3 Address 1 Register 5 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR1_REG5_L3A15_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR1_REG5_L3A15_SHIFT (0U)
/*! L3A15 - Layer 3 Address 1 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[63:32] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR1_REG5_L3A15(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR1_REG5_L3A15_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR1_REG5_L3A15_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR2_REG5 - Layer 3 Address 2 Register 5 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR2_REG5_L3A25_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR2_REG5_L3A25_SHIFT (0U)
/*! L3A25 - Layer 3 Address 2 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[95:64] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR2_REG5_L3A25(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR2_REG5_L3A25_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR2_REG5_L3A25_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR3_REG5 - Layer 3 Address 3 Register 5 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR3_REG5_L3A35_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR3_REG5_L3A35_SHIFT (0U)
/*! L3A35 - Layer 3 Address 3 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[127:96] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR3_REG5_L3A35(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR3_REG5_L3A35_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR3_REG5_L3A35_MASK)
/*! @} */

/*! @name MAC_L3_L4_CONTROL6 - Layer 3 and Layer 4 Control of Filter 6 */
/*! @{ */

#define ENET_QOS_MAC_L3_L4_CONTROL6_L3PEN6_MASK  (0x1U)
#define ENET_QOS_MAC_L3_L4_CONTROL6_L3PEN6_SHIFT (0U)
/*! L3PEN6 - Layer 3 Protocol Enable When this bit is set, the Layer 3 IP Source or Destination
 *    Address matching is enabled for IPv6 packets.
 *  0b0..Layer 3 Protocol is disabled
 *  0b1..Layer 3 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL6_L3PEN6(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL6_L3PEN6_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL6_L3PEN6_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL6_L3SAM6_MASK  (0x4U)
#define ENET_QOS_MAC_L3_L4_CONTROL6_L3SAM6_SHIFT (2U)
/*! L3SAM6 - Layer 3 IP SA Match Enable When this bit is set, the Layer 3 IP Source Address field is enabled for matching.
 *  0b0..Layer 3 IP SA Match is disabled
 *  0b1..Layer 3 IP SA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL6_L3SAM6(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL6_L3SAM6_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL6_L3SAM6_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL6_L3SAIM6_MASK (0x8U)
#define ENET_QOS_MAC_L3_L4_CONTROL6_L3SAIM6_SHIFT (3U)
/*! L3SAIM6 - Layer 3 IP SA Inverse Match Enable When this bit is set, the Layer 3 IP Source Address
 *    field is enabled for inverse matching.
 *  0b0..Layer 3 IP SA Inverse Match is disabled
 *  0b1..Layer 3 IP SA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL6_L3SAIM6(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL6_L3SAIM6_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL6_L3SAIM6_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL6_L3DAM6_MASK  (0x10U)
#define ENET_QOS_MAC_L3_L4_CONTROL6_L3DAM6_SHIFT (4U)
/*! L3DAM6 - Layer 3 IP DA Match Enable When this bit is set, the Layer 3 IP Destination Address field is enabled for matching.
 *  0b0..Layer 3 IP DA Match is disabled
 *  0b1..Layer 3 IP DA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL6_L3DAM6(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL6_L3DAM6_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL6_L3DAM6_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL6_L3DAIM6_MASK (0x20U)
#define ENET_QOS_MAC_L3_L4_CONTROL6_L3DAIM6_SHIFT (5U)
/*! L3DAIM6 - Layer 3 IP DA Inverse Match Enable When this bit is set, the Layer 3 IP Destination
 *    Address field is enabled for inverse matching.
 *  0b0..Layer 3 IP DA Inverse Match is disabled
 *  0b1..Layer 3 IP DA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL6_L3DAIM6(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL6_L3DAIM6_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL6_L3DAIM6_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL6_L3HSBM6_MASK (0x7C0U)
#define ENET_QOS_MAC_L3_L4_CONTROL6_L3HSBM6_SHIFT (6U)
/*! L3HSBM6 - Layer 3 IP SA Higher Bits Match IPv4 Packets: This field contains the number of lower
 *    bits of IP Source Address that are masked for matching in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL6_L3HSBM6(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL6_L3HSBM6_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL6_L3HSBM6_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL6_L3HDBM6_MASK (0xF800U)
#define ENET_QOS_MAC_L3_L4_CONTROL6_L3HDBM6_SHIFT (11U)
/*! L3HDBM6 - Layer 3 IP DA Higher Bits Match IPv4 Packets: This field contains the number of higher
 *    bits of IP Destination Address that are matched in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL6_L3HDBM6(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL6_L3HDBM6_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL6_L3HDBM6_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL6_L4PEN6_MASK  (0x10000U)
#define ENET_QOS_MAC_L3_L4_CONTROL6_L4PEN6_SHIFT (16U)
/*! L4PEN6 - Layer 4 Protocol Enable When this bit is set, the Source and Destination Port number
 *    fields of UDP packets are used for matching.
 *  0b0..Layer 4 Protocol is disabled
 *  0b1..Layer 4 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL6_L4PEN6(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL6_L4PEN6_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL6_L4PEN6_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL6_L4SPM6_MASK  (0x40000U)
#define ENET_QOS_MAC_L3_L4_CONTROL6_L4SPM6_SHIFT (18U)
/*! L4SPM6 - Layer 4 Source Port Match Enable When this bit is set, the Layer 4 Source Port number field is enabled for matching.
 *  0b0..Layer 4 Source Port Match is disabled
 *  0b1..Layer 4 Source Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL6_L4SPM6(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL6_L4SPM6_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL6_L4SPM6_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL6_L4SPIM6_MASK (0x80000U)
#define ENET_QOS_MAC_L3_L4_CONTROL6_L4SPIM6_SHIFT (19U)
/*! L4SPIM6 - Layer 4 Source Port Inverse Match Enable When this bit is set, the Layer 4 Source Port
 *    number field is enabled for inverse matching.
 *  0b0..Layer 4 Source Port Inverse Match is disabled
 *  0b1..Layer 4 Source Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL6_L4SPIM6(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL6_L4SPIM6_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL6_L4SPIM6_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL6_L4DPM6_MASK  (0x100000U)
#define ENET_QOS_MAC_L3_L4_CONTROL6_L4DPM6_SHIFT (20U)
/*! L4DPM6 - Layer 4 Destination Port Match Enable When this bit is set, the Layer 4 Destination
 *    Port number field is enabled for matching.
 *  0b0..Layer 4 Destination Port Match is disabled
 *  0b1..Layer 4 Destination Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL6_L4DPM6(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL6_L4DPM6_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL6_L4DPM6_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL6_L4DPIM6_MASK (0x200000U)
#define ENET_QOS_MAC_L3_L4_CONTROL6_L4DPIM6_SHIFT (21U)
/*! L4DPIM6 - Layer 4 Destination Port Inverse Match Enable When this bit is set, the Layer 4
 *    Destination Port number field is enabled for inverse matching.
 *  0b0..Layer 4 Destination Port Inverse Match is disabled
 *  0b1..Layer 4 Destination Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL6_L4DPIM6(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL6_L4DPIM6_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL6_L4DPIM6_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL6_DMCHN6_MASK  (0x7000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL6_DMCHN6_SHIFT (24U)
/*! DMCHN6 - DMA Channel Number When DMCHEN is set high, this field selects the DMA Channel number
 *    to which the packet passed by this filter is routed.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL6_DMCHN6(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL6_DMCHN6_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL6_DMCHN6_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL6_DMCHEN6_MASK (0x10000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL6_DMCHEN6_SHIFT (28U)
/*! DMCHEN6 - DMA Channel Select Enable When set, this bit enables the selection of the DMA channel
 *    number for the packet that is passed by this L3_L4 filter.
 *  0b0..DMA Channel Select is disabled
 *  0b1..DMA Channel Select is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL6_DMCHEN6(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL6_DMCHEN6_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL6_DMCHEN6_MASK)
/*! @} */

/*! @name MAC_LAYER4_ADDRESS6 - Layer 4 Address 6 */
/*! @{ */

#define ENET_QOS_MAC_LAYER4_ADDRESS6_L4SP6_MASK  (0xFFFFU)
#define ENET_QOS_MAC_LAYER4_ADDRESS6_L4SP6_SHIFT (0U)
/*! L4SP6 - Layer 4 Source Port Number Field When the L4PEN6 bit is reset and the L4SPM0 bit is set
 *    in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the TCP
 *    Source Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS6_L4SP6(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS6_L4SP6_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS6_L4SP6_MASK)

#define ENET_QOS_MAC_LAYER4_ADDRESS6_L4DP6_MASK  (0xFFFF0000U)
#define ENET_QOS_MAC_LAYER4_ADDRESS6_L4DP6_SHIFT (16U)
/*! L4DP6 - Layer 4 Destination Port Number Field When the L4PEN6 bit is reset and the L4DPM6 bit is
 *    set in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the
 *    TCP Destination Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS6_L4DP6(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS6_L4DP6_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS6_L4DP6_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR0_REG6 - Layer 3 Address 0 Register 6 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR0_REG6_L3A06_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR0_REG6_L3A06_SHIFT (0U)
/*! L3A06 - Layer 3 Address 0 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[31:0] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR0_REG6_L3A06(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR0_REG6_L3A06_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR0_REG6_L3A06_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR1_REG6 - Layer 3 Address 1 Register 6 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR1_REG6_L3A16_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR1_REG6_L3A16_SHIFT (0U)
/*! L3A16 - Layer 3 Address 1 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[63:32] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR1_REG6_L3A16(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR1_REG6_L3A16_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR1_REG6_L3A16_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR2_REG6 - Layer 3 Address 2 Register 6 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR2_REG6_L3A26_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR2_REG6_L3A26_SHIFT (0U)
/*! L3A26 - Layer 3 Address 2 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[95:64] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR2_REG6_L3A26(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR2_REG6_L3A26_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR2_REG6_L3A26_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR3_REG6 - Layer 3 Address 3 Register 6 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR3_REG6_L3A36_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR3_REG6_L3A36_SHIFT (0U)
/*! L3A36 - Layer 3 Address 3 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[127:96] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR3_REG6_L3A36(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR3_REG6_L3A36_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR3_REG6_L3A36_MASK)
/*! @} */

/*! @name MAC_L3_L4_CONTROL7 - Layer 3 and Layer 4 Control of Filter 0 */
/*! @{ */

#define ENET_QOS_MAC_L3_L4_CONTROL7_L3PEN7_MASK  (0x1U)
#define ENET_QOS_MAC_L3_L4_CONTROL7_L3PEN7_SHIFT (0U)
/*! L3PEN7 - Layer 3 Protocol Enable When this bit is set, the Layer 3 IP Source or Destination
 *    Address matching is enabled for IPv6 packets.
 *  0b0..Layer 3 Protocol is disabled
 *  0b1..Layer 3 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL7_L3PEN7(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL7_L3PEN7_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL7_L3PEN7_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL7_L3SAM7_MASK  (0x4U)
#define ENET_QOS_MAC_L3_L4_CONTROL7_L3SAM7_SHIFT (2U)
/*! L3SAM7 - Layer 3 IP SA Match Enable When this bit is set, the Layer 3 IP Source Address field is enabled for matching.
 *  0b0..Layer 3 IP SA Match is disabled
 *  0b1..Layer 3 IP SA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL7_L3SAM7(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL7_L3SAM7_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL7_L3SAM7_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL7_L3SAIM7_MASK (0x8U)
#define ENET_QOS_MAC_L3_L4_CONTROL7_L3SAIM7_SHIFT (3U)
/*! L3SAIM7 - Layer 3 IP SA Inverse Match Enable When this bit is set, the Layer 3 IP Source Address
 *    field is enabled for inverse matching.
 *  0b0..Layer 3 IP SA Inverse Match is disabled
 *  0b1..Layer 3 IP SA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL7_L3SAIM7(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL7_L3SAIM7_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL7_L3SAIM7_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL7_L3DAM7_MASK  (0x10U)
#define ENET_QOS_MAC_L3_L4_CONTROL7_L3DAM7_SHIFT (4U)
/*! L3DAM7 - Layer 3 IP DA Match Enable When this bit is set, the Layer 3 IP Destination Address field is enabled for matching.
 *  0b0..Layer 3 IP DA Match is disabled
 *  0b1..Layer 3 IP DA Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL7_L3DAM7(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL7_L3DAM7_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL7_L3DAM7_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL7_L3DAIM7_MASK (0x20U)
#define ENET_QOS_MAC_L3_L4_CONTROL7_L3DAIM7_SHIFT (5U)
/*! L3DAIM7 - Layer 3 IP DA Inverse Match Enable When this bit is set, the Layer 3 IP Destination
 *    Address field is enabled for inverse matching.
 *  0b0..Layer 3 IP DA Inverse Match is disabled
 *  0b1..Layer 3 IP DA Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL7_L3DAIM7(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL7_L3DAIM7_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL7_L3DAIM7_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL7_L3HSBM7_MASK (0x7C0U)
#define ENET_QOS_MAC_L3_L4_CONTROL7_L3HSBM7_SHIFT (6U)
/*! L3HSBM7 - Layer 3 IP SA Higher Bits Match IPv4 Packets: This field contains the number of lower
 *    bits of IP Source Address that are masked for matching in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL7_L3HSBM7(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL7_L3HSBM7_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL7_L3HSBM7_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL7_L3HDBM7_MASK (0xF800U)
#define ENET_QOS_MAC_L3_L4_CONTROL7_L3HDBM7_SHIFT (11U)
/*! L3HDBM7 - Layer 3 IP DA Higher Bits Match IPv4 Packets: This field contains the number of higher
 *    bits of IP Destination Address that are matched in the IPv4 packets.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL7_L3HDBM7(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL7_L3HDBM7_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL7_L3HDBM7_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL7_L4PEN7_MASK  (0x10000U)
#define ENET_QOS_MAC_L3_L4_CONTROL7_L4PEN7_SHIFT (16U)
/*! L4PEN7 - Layer 4 Protocol Enable When this bit is set, the Source and Destination Port number
 *    fields of UDP packets are used for matching.
 *  0b0..Layer 4 Protocol is disabled
 *  0b1..Layer 4 Protocol is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL7_L4PEN7(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL7_L4PEN7_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL7_L4PEN7_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL7_L4SPM7_MASK  (0x40000U)
#define ENET_QOS_MAC_L3_L4_CONTROL7_L4SPM7_SHIFT (18U)
/*! L4SPM7 - Layer 4 Source Port Match Enable When this bit is set, the Layer 4 Source Port number field is enabled for matching.
 *  0b0..Layer 4 Source Port Match is disabled
 *  0b1..Layer 4 Source Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL7_L4SPM7(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL7_L4SPM7_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL7_L4SPM7_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL7_L4SPIM7_MASK (0x80000U)
#define ENET_QOS_MAC_L3_L4_CONTROL7_L4SPIM7_SHIFT (19U)
/*! L4SPIM7 - Layer 4 Source Port Inverse Match Enable When this bit is set, the Layer 4 Source Port
 *    number field is enabled for inverse matching.
 *  0b0..Layer 4 Source Port Inverse Match is disabled
 *  0b1..Layer 4 Source Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL7_L4SPIM7(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL7_L4SPIM7_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL7_L4SPIM7_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL7_L4DPM7_MASK  (0x100000U)
#define ENET_QOS_MAC_L3_L4_CONTROL7_L4DPM7_SHIFT (20U)
/*! L4DPM7 - Layer 4 Destination Port Match Enable When this bit is set, the Layer 4 Destination
 *    Port number field is enabled for matching.
 *  0b0..Layer 4 Destination Port Match is disabled
 *  0b1..Layer 4 Destination Port Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL7_L4DPM7(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL7_L4DPM7_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL7_L4DPM7_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL7_L4DPIM7_MASK (0x200000U)
#define ENET_QOS_MAC_L3_L4_CONTROL7_L4DPIM7_SHIFT (21U)
/*! L4DPIM7 - Layer 4 Destination Port Inverse Match Enable When this bit is set, the Layer 4
 *    Destination Port number field is enabled for inverse matching.
 *  0b0..Layer 4 Destination Port Inverse Match is disabled
 *  0b1..Layer 4 Destination Port Inverse Match is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL7_L4DPIM7(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL7_L4DPIM7_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL7_L4DPIM7_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL7_DMCHN7_MASK  (0x7000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL7_DMCHN7_SHIFT (24U)
/*! DMCHN7 - DMA Channel Number When DMCHEN is set high, this field selects the DMA Channel number
 *    to which the packet passed by this filter is routed.
 */
#define ENET_QOS_MAC_L3_L4_CONTROL7_DMCHN7(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL7_DMCHN7_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL7_DMCHN7_MASK)

#define ENET_QOS_MAC_L3_L4_CONTROL7_DMCHEN7_MASK (0x10000000U)
#define ENET_QOS_MAC_L3_L4_CONTROL7_DMCHEN7_SHIFT (28U)
/*! DMCHEN7 - DMA Channel Select Enable When set, this bit enables the selection of the DMA channel
 *    number for the packet that is passed by this L3_L4 filter.
 *  0b0..DMA Channel Select is disabled
 *  0b1..DMA Channel Select is enabled
 */
#define ENET_QOS_MAC_L3_L4_CONTROL7_DMCHEN7(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_L3_L4_CONTROL7_DMCHEN7_SHIFT)) & ENET_QOS_MAC_L3_L4_CONTROL7_DMCHEN7_MASK)
/*! @} */

/*! @name MAC_LAYER4_ADDRESS7 - Layer 4 Address 7 */
/*! @{ */

#define ENET_QOS_MAC_LAYER4_ADDRESS7_L4SP7_MASK  (0xFFFFU)
#define ENET_QOS_MAC_LAYER4_ADDRESS7_L4SP7_SHIFT (0U)
/*! L4SP7 - Layer 4 Source Port Number Field When the L4PEN7 bit is reset and the L4SPM0 bit is set
 *    in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the TCP
 *    Source Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS7_L4SP7(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS7_L4SP7_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS7_L4SP7_MASK)

#define ENET_QOS_MAC_LAYER4_ADDRESS7_L4DP7_MASK  (0xFFFF0000U)
#define ENET_QOS_MAC_LAYER4_ADDRESS7_L4DP7_SHIFT (16U)
/*! L4DP7 - Layer 4 Destination Port Number Field When the L4PEN7 bit is reset and the L4DPM7 bit is
 *    set in the MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with the
 *    TCP Destination Port Number field in the IPv4 or IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER4_ADDRESS7_L4DP7(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER4_ADDRESS7_L4DP7_SHIFT)) & ENET_QOS_MAC_LAYER4_ADDRESS7_L4DP7_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR0_REG7 - Layer 3 Address 0 Register 7 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR0_REG7_L3A07_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR0_REG7_L3A07_SHIFT (0U)
/*! L3A07 - Layer 3 Address 0 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[31:0] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR0_REG7_L3A07(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR0_REG7_L3A07_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR0_REG7_L3A07_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR1_REG7 - Layer 3 Address 1 Register 7 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR1_REG7_L3A17_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR1_REG7_L3A17_SHIFT (0U)
/*! L3A17 - Layer 3 Address 1 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[63:32] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR1_REG7_L3A17(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR1_REG7_L3A17_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR1_REG7_L3A17_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR2_REG7 - Layer 3 Address 2 Register 7 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR2_REG7_L3A27_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR2_REG7_L3A27_SHIFT (0U)
/*! L3A27 - Layer 3 Address 2 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[95:64] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR2_REG7_L3A27(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR2_REG7_L3A27_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR2_REG7_L3A27_MASK)
/*! @} */

/*! @name MAC_LAYER3_ADDR3_REG7 - Layer 3 Address 3 Register 7 */
/*! @{ */

#define ENET_QOS_MAC_LAYER3_ADDR3_REG7_L3A37_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_LAYER3_ADDR3_REG7_L3A37_SHIFT (0U)
/*! L3A37 - Layer 3 Address 3 Field When the L3PEN0 and L3SAM0 bits are set in the
 *    MAC_L3_L4_CONTROL0 register, this field contains the value to be matched with Bits[127:96] of the IP Source
 *    Address field in the IPv6 packets.
 */
#define ENET_QOS_MAC_LAYER3_ADDR3_REG7_L3A37(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LAYER3_ADDR3_REG7_L3A37_SHIFT)) & ENET_QOS_MAC_LAYER3_ADDR3_REG7_L3A37_MASK)
/*! @} */

/*! @name MAC_INDIR_ACCESS_CTRL - MAC_INDIR_ACCESS_CTRL */
/*! @{ */

#define ENET_QOS_MAC_INDIR_ACCESS_CTRL_OB_MASK   (0x1U)
#define ENET_QOS_MAC_INDIR_ACCESS_CTRL_OB_SHIFT  (0U)
/*! OB - Operation Busy */
#define ENET_QOS_MAC_INDIR_ACCESS_CTRL_OB(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INDIR_ACCESS_CTRL_OB_SHIFT)) & ENET_QOS_MAC_INDIR_ACCESS_CTRL_OB_MASK)

#define ENET_QOS_MAC_INDIR_ACCESS_CTRL_COM_MASK  (0x2U)
#define ENET_QOS_MAC_INDIR_ACCESS_CTRL_COM_SHIFT (1U)
/*! COM - Command type. Indicates the register access type.
 *  0b0..Indicates a write operation
 *  0b1..Indicates a read operation
 */
#define ENET_QOS_MAC_INDIR_ACCESS_CTRL_COM(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INDIR_ACCESS_CTRL_COM_SHIFT)) & ENET_QOS_MAC_INDIR_ACCESS_CTRL_COM_MASK)

#define ENET_QOS_MAC_INDIR_ACCESS_CTRL_AUTO_MASK (0x20U)
#define ENET_QOS_MAC_INDIR_ACCESS_CTRL_AUTO_SHIFT (5U)
/*! AUTO - Auto increment enable
 *  0b0..AOFF is not incremented automatically. Software should program the correct Address Offset for each access.
 *  0b1..AOFF is incremented by 1. Software should ensure not to cause a wrap condition. Byte wise read/write is
 *       not supported when auto increment is enabled.
 */
#define ENET_QOS_MAC_INDIR_ACCESS_CTRL_AUTO(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INDIR_ACCESS_CTRL_AUTO_SHIFT)) & ENET_QOS_MAC_INDIR_ACCESS_CTRL_AUTO_MASK)

#define ENET_QOS_MAC_INDIR_ACCESS_CTRL_AOFF_MASK (0xFF00U)
#define ENET_QOS_MAC_INDIR_ACCESS_CTRL_AOFF_SHIFT (8U)
/*! AOFF - Address Offset */
#define ENET_QOS_MAC_INDIR_ACCESS_CTRL_AOFF(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INDIR_ACCESS_CTRL_AOFF_SHIFT)) & ENET_QOS_MAC_INDIR_ACCESS_CTRL_AOFF_MASK)

#define ENET_QOS_MAC_INDIR_ACCESS_CTRL_MSEL_MASK (0xF0000U)
#define ENET_QOS_MAC_INDIR_ACCESS_CTRL_MSEL_SHIFT (16U)
/*! MSEL - Mode Select */
#define ENET_QOS_MAC_INDIR_ACCESS_CTRL_MSEL(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INDIR_ACCESS_CTRL_MSEL_SHIFT)) & ENET_QOS_MAC_INDIR_ACCESS_CTRL_MSEL_MASK)
/*! @} */

/*! @name MAC_INDIR_ACCESS_DATA - MAC_INDIR_ACCESS_DATA */
/*! @{ */

#define ENET_QOS_MAC_INDIR_ACCESS_DATA_DATA_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_INDIR_ACCESS_DATA_DATA_SHIFT (0U)
/*! DATA - This field contains data to read/write for Indirect address access associated with MAC_INDIR_ACCESS_CTRL register. */
#define ENET_QOS_MAC_INDIR_ACCESS_DATA_DATA(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_INDIR_ACCESS_DATA_DATA_SHIFT)) & ENET_QOS_MAC_INDIR_ACCESS_DATA_DATA_MASK)
/*! @} */

/*! @name MAC_TIMESTAMP_CONTROL - Timestamp Control */
/*! @{ */

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENA_MASK (0x1U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENA_SHIFT (0U)
/*! TSENA - Enable Timestamp When this bit is set, the timestamp is added for Transmit and Receive packets.
 *  0b0..Timestamp is disabled
 *  0b1..Timestamp is enabled
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENA(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENA_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENA_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCFUPDT_MASK (0x2U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCFUPDT_SHIFT (1U)
/*! TSCFUPDT - Fine or Coarse Timestamp Update When this bit is set, the Fine method is used to update system timestamp.
 *  0b0..Coarse method is used to update system timestamp
 *  0b1..Fine method is used to update system timestamp
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCFUPDT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCFUPDT_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCFUPDT_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSINIT_MASK (0x4U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSINIT_SHIFT (2U)
/*! TSINIT - Initialize Timestamp When this bit is set, the system time is initialized (overwritten)
 *    with the value specified in the MAC_System_Time_Seconds_Update and
 *    MAC_System_Time_Nanoseconds_Update registers.
 *  0b0..Timestamp is not initialized
 *  0b1..Timestamp is initialized
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSINIT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_TSINIT_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK (0x8U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSUPDT_SHIFT (3U)
/*! TSUPDT - Update Timestamp When this bit is set, the system time is updated (added or subtracted)
 *    with the value specified in MAC_System_Time_Seconds_Update and
 *    MAC_System_Time_Nanoseconds_Update registers.
 *  0b0..Timestamp is not updated
 *  0b1..Timestamp is updated
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSUPDT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_TSUPDT_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK (0x20U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSADDREG_SHIFT (5U)
/*! TSADDREG - Update Addend Register When this bit is set, the content of the Timestamp Addend
 *    register is updated in the PTP block for fine correction.
 *  0b0..Addend Register is not updated
 *  0b1..Addend Register is updated
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSADDREG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_TSADDREG_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_PTGE_MASK (0x40U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_PTGE_SHIFT (6U)
/*! PTGE - Presentation Time Generation Enable When this bit is set the Presentation Time generation will be enabled.
 *  0b0..Presentation Time Generation is disabled
 *  0b1..Presentation Time Generation is enabled
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_PTGE(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_PTGE_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_PTGE_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENALL_MASK (0x100U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENALL_SHIFT (8U)
/*! TSENALL - Enable Timestamp for All Packets When this bit is set, the timestamp snapshot is
 *    enabled for all packets received by the MAC.
 *  0b0..Timestamp for All Packets disabled
 *  0b1..Timestamp for All Packets enabled
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENALL(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENALL_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENALL_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_MASK (0x200U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_SHIFT (9U)
/*! TSCTRLSSR - Timestamp Digital or Binary Rollover Control When this bit is set, the Timestamp Low
 *    register rolls over after 0x3B9A_C9FF value (that is, 1 nanosecond accuracy) and increments
 *    the timestamp (High) seconds.
 *  0b0..Timestamp Digital or Binary Rollover Control is disabled
 *  0b1..Timestamp Digital or Binary Rollover Control is enabled
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCTRLSSR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSVER2ENA_MASK (0x400U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSVER2ENA_SHIFT (10U)
/*! TSVER2ENA - Enable PTP Packet Processing for Version 2 Format When this bit is set, the IEEE
 *    1588 version 2 format is used to process the PTP packets.
 *  0b0..PTP Packet Processing for Version 2 Format is disabled
 *  0b1..PTP Packet Processing for Version 2 Format is enabled
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSVER2ENA(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_TSVER2ENA_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSVER2ENA_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPENA_MASK (0x800U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPENA_SHIFT (11U)
/*! TSIPENA - Enable Processing of PTP over Ethernet Packets When this bit is set, the MAC receiver
 *    processes the PTP packets encapsulated directly in the Ethernet packets.
 *  0b0..Processing of PTP over Ethernet Packets is disabled
 *  0b1..Processing of PTP over Ethernet Packets is enabled
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPENA(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPENA_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPENA_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPV6ENA_MASK (0x1000U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPV6ENA_SHIFT (12U)
/*! TSIPV6ENA - Enable Processing of PTP Packets Sent over IPv6-UDP When this bit is set, the MAC
 *    receiver processes the PTP packets encapsulated in IPv6-UDP packets.
 *  0b0..Processing of PTP Packets Sent over IPv6-UDP is disabled
 *  0b1..Processing of PTP Packets Sent over IPv6-UDP is enabled
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPV6ENA(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPV6ENA_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPV6ENA_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPV4ENA_MASK (0x2000U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPV4ENA_SHIFT (13U)
/*! TSIPV4ENA - Enable Processing of PTP Packets Sent over IPv4-UDP When this bit is set, the MAC
 *    receiver processes the PTP packets encapsulated in IPv4-UDP packets.
 *  0b0..Processing of PTP Packets Sent over IPv4-UDP is disabled
 *  0b1..Processing of PTP Packets Sent over IPv4-UDP is enabled
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPV4ENA(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPV4ENA_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPV4ENA_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSEVNTENA_MASK (0x4000U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSEVNTENA_SHIFT (14U)
/*! TSEVNTENA - Enable Timestamp Snapshot for Event Messages When this bit is set, the timestamp
 *    snapshot is taken only for event messages (SYNC, Delay_Req, Pdelay_Req, or Pdelay_Resp).
 *  0b0..Timestamp Snapshot for Event Messages is disabled
 *  0b1..Timestamp Snapshot for Event Messages is enabled
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSEVNTENA(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_TSEVNTENA_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSEVNTENA_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSMSTRENA_MASK (0x8000U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSMSTRENA_SHIFT (15U)
/*! TSMSTRENA - Enable Snapshot for Messages Relevant to Master When this bit is set, the snapshot
 *    is taken only for the messages that are relevant to the master node.
 *  0b0..Snapshot for Messages Relevant to Master is disabled
 *  0b1..Snapshot for Messages Relevant to Master is enabled
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSMSTRENA(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_TSMSTRENA_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSMSTRENA_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL_MASK (0x30000U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL_SHIFT (16U)
/*! SNAPTYPSEL - Select PTP packets for Taking Snapshots These bits, along with Bits 15 and 14,
 *    decide the set of PTP packet types for which snapshot needs to be taken.
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENMACADDR_MASK (0x40000U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENMACADDR_SHIFT (18U)
/*! TSENMACADDR - Enable MAC Address for PTP Packet Filtering When this bit is set, the DA MAC
 *    address (that matches any MAC Address register) is used to filter the PTP packets when PTP is
 *    directly sent over Ethernet.
 *  0b0..MAC Address for PTP Packet Filtering is disabled
 *  0b1..MAC Address for PTP Packet Filtering is enabled
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENMACADDR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENMACADDR_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENMACADDR_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_CSC_MASK  (0x80000U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_CSC_SHIFT (19U)
/*! CSC - Enable checksum correction during OST for PTP over UDP/IPv4 packets When this bit is set,
 *    the last two bytes of PTP message sent over UDP/IPv4 is updated to keep the UDP checksum
 *    correct, for changes made to origin timestamp and/or correction field as part of one step timestamp
 *    operation.
 *  0b0..checksum correction during OST for PTP over UDP/IPv4 packets is disabled
 *  0b1..checksum correction during OST for PTP over UDP/IPv4 packets is enabled
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_CSC(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_CSC_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_CSC_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_ESTI_MASK (0x100000U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_ESTI_SHIFT (20U)
/*! ESTI - External System Time Input When this bit is set, the MAC uses the external 64-bit
 *    reference System Time input for the following: - To take the timestamp provided as status - To insert
 *    the timestamp in transmit PTP packets when One-step Timestamp or Timestamp Offload feature is
 *    enabled.
 *  0b0..External System Time Input is disabled
 *  0b1..External System Time Input is enabled
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_ESTI(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_ESTI_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_ESTI_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TXTSSTSM_MASK (0x1000000U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TXTSSTSM_SHIFT (24U)
/*! TXTSSTSM - Transmit Timestamp Status Mode When this bit is set, the MAC overwrites the earlier
 *    transmit timestamp status even if it is not read by the software.
 *  0b0..Transmit Timestamp Status Mode is disabled
 *  0b1..Transmit Timestamp Status Mode is enabled
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_TXTSSTSM(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_TXTSSTSM_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_TXTSSTSM_MASK)

#define ENET_QOS_MAC_TIMESTAMP_CONTROL_AV8021ASMEN_MASK (0x10000000U)
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_AV8021ASMEN_SHIFT (28U)
/*! AV8021ASMEN - AV 802.
 *  0b0..AV 802.1AS Mode is disabled
 *  0b1..AV 802.1AS Mode is enabled
 */
#define ENET_QOS_MAC_TIMESTAMP_CONTROL_AV8021ASMEN(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_CONTROL_AV8021ASMEN_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_CONTROL_AV8021ASMEN_MASK)
/*! @} */

/*! @name MAC_SUB_SECOND_INCREMENT - Subsecond Increment */
/*! @{ */

#define ENET_QOS_MAC_SUB_SECOND_INCREMENT_SNSINC_MASK (0xFF00U)
#define ENET_QOS_MAC_SUB_SECOND_INCREMENT_SNSINC_SHIFT (8U)
/*! SNSINC - Sub-nanosecond Increment Value This field contains the sub-nanosecond increment value,
 *    represented in nanoseconds multiplied by 2^8.
 */
#define ENET_QOS_MAC_SUB_SECOND_INCREMENT_SNSINC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_SUB_SECOND_INCREMENT_SNSINC_SHIFT)) & ENET_QOS_MAC_SUB_SECOND_INCREMENT_SNSINC_MASK)

#define ENET_QOS_MAC_SUB_SECOND_INCREMENT_SSINC_MASK (0xFF0000U)
#define ENET_QOS_MAC_SUB_SECOND_INCREMENT_SSINC_SHIFT (16U)
/*! SSINC - Sub-second Increment Value The value programmed in this field is accumulated every clock
 *    cycle (of clk_ptp_i) with the contents of the sub-second register.
 */
#define ENET_QOS_MAC_SUB_SECOND_INCREMENT_SSINC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_SUB_SECOND_INCREMENT_SSINC_SHIFT)) & ENET_QOS_MAC_SUB_SECOND_INCREMENT_SSINC_MASK)
/*! @} */

/*! @name MAC_SYSTEM_TIME_SECONDS - System Time Seconds */
/*! @{ */

#define ENET_QOS_MAC_SYSTEM_TIME_SECONDS_TSS_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_SYSTEM_TIME_SECONDS_TSS_SHIFT (0U)
/*! TSS - Timestamp Second The value in this field indicates the current value in seconds of the
 *    System Time maintained by the MAC.
 */
#define ENET_QOS_MAC_SYSTEM_TIME_SECONDS_TSS(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_SYSTEM_TIME_SECONDS_TSS_SHIFT)) & ENET_QOS_MAC_SYSTEM_TIME_SECONDS_TSS_MASK)
/*! @} */

/*! @name MAC_SYSTEM_TIME_NANOSECONDS - System Time Nanoseconds */
/*! @{ */

#define ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_TSSS_MASK (0x7FFFFFFFU)
#define ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_TSSS_SHIFT (0U)
/*! TSSS - Timestamp Sub Seconds The value in this field has the sub-second representation of time, with an accuracy of 0. */
#define ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_TSSS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_TSSS_SHIFT)) & ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_TSSS_MASK)
/*! @} */

/*! @name MAC_SYSTEM_TIME_SECONDS_UPDATE - System Time Seconds Update */
/*! @{ */

#define ENET_QOS_MAC_SYSTEM_TIME_SECONDS_UPDATE_TSS_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_SYSTEM_TIME_SECONDS_UPDATE_TSS_SHIFT (0U)
/*! TSS - Timestamp Seconds The value in this field is the seconds part of the update. */
#define ENET_QOS_MAC_SYSTEM_TIME_SECONDS_UPDATE_TSS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_SYSTEM_TIME_SECONDS_UPDATE_TSS_SHIFT)) & ENET_QOS_MAC_SYSTEM_TIME_SECONDS_UPDATE_TSS_MASK)
/*! @} */

/*! @name MAC_SYSTEM_TIME_NANOSECONDS_UPDATE - System Time Nanoseconds Update */
/*! @{ */

#define ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_MASK (0x7FFFFFFFU)
#define ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_SHIFT (0U)
/*! TSSS - Timestamp Sub Seconds The value in this field is the sub-seconds part of the update. */
#define ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_SHIFT)) & ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_MASK)

#define ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB_MASK (0x80000000U)
#define ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB_SHIFT (31U)
/*! ADDSUB - Add or Subtract Time When this bit is set, the time value is subtracted with the contents of the update register.
 *  0b0..Add time
 *  0b1..Subtract time
 */
#define ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB_SHIFT)) & ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB_MASK)
/*! @} */

/*! @name MAC_TIMESTAMP_ADDEND - Timestamp Addend */
/*! @{ */

#define ENET_QOS_MAC_TIMESTAMP_ADDEND_TSAR_MASK  (0xFFFFFFFFU)
#define ENET_QOS_MAC_TIMESTAMP_ADDEND_TSAR_SHIFT (0U)
/*! TSAR - Timestamp Addend Register This field indicates the 32-bit time value to be added to the
 *    Accumulator register to achieve time synchronization.
 */
#define ENET_QOS_MAC_TIMESTAMP_ADDEND_TSAR(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_ADDEND_TSAR_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_ADDEND_TSAR_MASK)
/*! @} */

/*! @name MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS - System Time - Higher Word Seconds */
/*! @{ */

#define ENET_QOS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_MASK (0xFFFFU)
#define ENET_QOS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_SHIFT (0U)
/*! TSHWR - Timestamp Higher Word Register This field contains the most-significant 16-bits of timestamp seconds value. */
#define ENET_QOS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_SHIFT)) & ENET_QOS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_MASK)
/*! @} */

/*! @name MAC_TIMESTAMP_STATUS - Timestamp Status */
/*! @{ */

#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSSOVF_MASK (0x1U)
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSSOVF_SHIFT (0U)
/*! TSSOVF - Timestamp Seconds Overflow When this bit is set, it indicates that the seconds value of
 *    the timestamp (when supporting version 2 format) has overflowed beyond 32'hFFFF_FFFF.
 *  0b0..Timestamp Seconds Overflow status not detected
 *  0b1..Timestamp Seconds Overflow status detected
 */
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSSOVF(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_STATUS_TSSOVF_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_STATUS_TSSOVF_MASK)

#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT0_MASK (0x2U)
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT0_SHIFT (1U)
/*! TSTARGT0 - Timestamp Target Time Reached When set, this bit indicates that the value of system
 *    time is greater than or equal to the value specified in the MAC_PPS0_Target_Time_Seconds and
 *    MAC_PPS0_Target_Time_Nanoseconds registers.
 *  0b0..Timestamp Target Time Reached status not detected
 *  0b1..Timestamp Target Time Reached status detected
 */
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT0(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT0_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT0_MASK)

#define ENET_QOS_MAC_TIMESTAMP_STATUS_AUXTSTRIG_MASK (0x4U)
#define ENET_QOS_MAC_TIMESTAMP_STATUS_AUXTSTRIG_SHIFT (2U)
/*! AUXTSTRIG - Auxiliary Timestamp Trigger Snapshot This bit is set high when the auxiliary snapshot is written to the FIFO.
 *  0b0..Auxiliary Timestamp Trigger Snapshot status not detected
 *  0b1..Auxiliary Timestamp Trigger Snapshot status detected
 */
#define ENET_QOS_MAC_TIMESTAMP_STATUS_AUXTSTRIG(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_STATUS_AUXTSTRIG_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_STATUS_AUXTSTRIG_MASK)

#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR0_MASK (0x8U)
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR0_SHIFT (3U)
/*! TSTRGTERR0 - Timestamp Target Time Error This bit is set when the latest target time programmed
 *    in the MAC_PPS0_Target_Time_Seconds and MAC_PPS0_Target_Time_Nanoseconds registers elapses.
 *  0b0..Timestamp Target Time Error status not detected
 *  0b1..Timestamp Target Time Error status detected
 */
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR0(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR0_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR0_MASK)

#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT1_MASK (0x10U)
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT1_SHIFT (4U)
/*! TSTARGT1 - Timestamp Target Time Reached for Target Time PPS1 When set, this bit indicates that
 *    the value of system time is greater than or equal to the value specified in the
 *    MAC_PPS1_TARGET_TIME_SECONDS and MAC_PPS1_TARGET_TIME_NANOSECONDS registers.
 *  0b0..Timestamp Target Time Reached for Target Time PPS1 status not detected
 *  0b1..Timestamp Target Time Reached for Target Time PPS1 status detected
 */
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT1(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT1_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT1_MASK)

#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR1_MASK (0x20U)
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR1_SHIFT (5U)
/*! TSTRGTERR1 - Timestamp Target Time Error This bit is set when the latest target time programmed
 *    in the MAC_PPS1_TARGET_TIME_SECONDS and MAC_PPS1_TARGET_TIME_NANOSECONDS registers elapses.
 *  0b0..Timestamp Target Time Error status not detected
 *  0b1..Timestamp Target Time Error status detected
 */
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR1(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR1_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR1_MASK)

#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT2_MASK (0x40U)
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT2_SHIFT (6U)
/*! TSTARGT2 - Timestamp Target Time Reached for Target Time PPS2 When set, this bit indicates that
 *    the value of system time is greater than or equal to the value specified in the
 *    MAC_PPS2_TARGET_TIME_SECONDS and MAC_PPS2_TARGET_TIME_NANOSECONDS registers.
 *  0b0..Timestamp Target Time Reached for Target Time PPS2 status not detected
 *  0b1..Timestamp Target Time Reached for Target Time PPS2 status detected
 */
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT2(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT2_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT2_MASK)

#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR2_MASK (0x80U)
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR2_SHIFT (7U)
/*! TSTRGTERR2 - Timestamp Target Time Error This bit is set when the latest target time programmed
 *    in the MAC_PPS2_TARGET_TIME_SECONDS and MAC_PPS2_TARGET_TIME_NANOSECONDS registers elapses.
 *  0b0..Timestamp Target Time Error status not detected
 *  0b1..Timestamp Target Time Error status detected
 */
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR2(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR2_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR2_MASK)

#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT3_MASK (0x100U)
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT3_SHIFT (8U)
/*! TSTARGT3 - Timestamp Target Time Reached for Target Time PPS3 When this bit is set, it indicates
 *    that the value of system time is greater than or equal to the value specified in the
 *    MAC_PPS3_TARGET_TIME_SECONDS and MAC_PPS3_TARGET_TIME_NANOSECONDS registers.
 *  0b0..Timestamp Target Time Reached for Target Time PPS3 status not detected
 *  0b1..Timestamp Target Time Reached for Target Time PPS3 status detected
 */
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT3(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT3_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_STATUS_TSTARGT3_MASK)

#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR3_MASK (0x200U)
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR3_SHIFT (9U)
/*! TSTRGTERR3 - Timestamp Target Time Error This bit is set when the latest target time programmed
 *    in the MAC_PPS3_TARGET_TIME_SECONDS and MAC_PPS3_TARGET_TIME_NANOSECONDS registers elapses.
 *  0b0..Timestamp Target Time Error status not detected
 *  0b1..Timestamp Target Time Error status detected
 */
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR3(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR3_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_STATUS_TSTRGTERR3_MASK)

#define ENET_QOS_MAC_TIMESTAMP_STATUS_TXTSSIS_MASK (0x8000U)
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TXTSSIS_SHIFT (15U)
/*! TXTSSIS - Tx Timestamp Status Interrupt Status In non-EQOS_CORE configurations when drop
 *    transmit status is enabled in MTL, this bit is set when the captured transmit timestamp is updated in
 *    the MAC_TX_TIMESTAMP_STATUS_NANOSECONDS and MAC_TX_TIMESTAMP_STATUS_SECONDS registers.
 *  0b0..Tx Timestamp Status Interrupt status not detected
 *  0b1..Tx Timestamp Status Interrupt status detected
 */
#define ENET_QOS_MAC_TIMESTAMP_STATUS_TXTSSIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_STATUS_TXTSSIS_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_STATUS_TXTSSIS_MASK)

#define ENET_QOS_MAC_TIMESTAMP_STATUS_ATSSTN_MASK (0xF0000U)
#define ENET_QOS_MAC_TIMESTAMP_STATUS_ATSSTN_SHIFT (16U)
/*! ATSSTN - Auxiliary Timestamp Snapshot Trigger Identifier These bits identify the Auxiliary
 *    trigger inputs for which the timestamp available in the Auxiliary Snapshot Register is applicable.
 */
#define ENET_QOS_MAC_TIMESTAMP_STATUS_ATSSTN(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_STATUS_ATSSTN_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_STATUS_ATSSTN_MASK)

#define ENET_QOS_MAC_TIMESTAMP_STATUS_ATSSTM_MASK (0x1000000U)
#define ENET_QOS_MAC_TIMESTAMP_STATUS_ATSSTM_SHIFT (24U)
/*! ATSSTM - Auxiliary Timestamp Snapshot Trigger Missed This bit is set when the Auxiliary
 *    timestamp snapshot FIFO is full and external trigger was set.
 *  0b0..Auxiliary Timestamp Snapshot Trigger Missed status not detected
 *  0b1..Auxiliary Timestamp Snapshot Trigger Missed status detected
 */
#define ENET_QOS_MAC_TIMESTAMP_STATUS_ATSSTM(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_STATUS_ATSSTM_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_STATUS_ATSSTM_MASK)

#define ENET_QOS_MAC_TIMESTAMP_STATUS_ATSNS_MASK (0x3E000000U)
#define ENET_QOS_MAC_TIMESTAMP_STATUS_ATSNS_SHIFT (25U)
/*! ATSNS - Number of Auxiliary Timestamp Snapshots This field indicates the number of Snapshots available in the FIFO. */
#define ENET_QOS_MAC_TIMESTAMP_STATUS_ATSNS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_STATUS_ATSNS_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_STATUS_ATSNS_MASK)
/*! @} */

/*! @name MAC_TX_TIMESTAMP_STATUS_NANOSECONDS - Transmit Timestamp Status Nanoseconds */
/*! @{ */

#define ENET_QOS_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSLO_MASK (0x7FFFFFFFU)
#define ENET_QOS_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSLO_SHIFT (0U)
/*! TXTSSLO - Transmit Timestamp Status Low This field contains the 31 bits of the Nanoseconds field
 *    of the Transmit packet's captured timestamp.
 */
#define ENET_QOS_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSLO(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSLO_SHIFT)) & ENET_QOS_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSLO_MASK)

#define ENET_QOS_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSMIS_MASK (0x80000000U)
#define ENET_QOS_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSMIS_SHIFT (31U)
/*! TXTSSMIS - Transmit Timestamp Status Missed
 *  0b0..Transmit Timestamp Status Missed status not detected
 *  0b1..Transmit Timestamp Status Missed status detected
 */
#define ENET_QOS_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSMIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSMIS_SHIFT)) & ENET_QOS_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSMIS_MASK)
/*! @} */

/*! @name MAC_TX_TIMESTAMP_STATUS_SECONDS - Transmit Timestamp Status Seconds */
/*! @{ */

#define ENET_QOS_MAC_TX_TIMESTAMP_STATUS_SECONDS_TXTSSHI_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TX_TIMESTAMP_STATUS_SECONDS_TXTSSHI_SHIFT (0U)
/*! TXTSSHI - Transmit Timestamp Status High This field contains the lower 32 bits of the Seconds
 *    field of Transmit packet's captured timestamp.
 */
#define ENET_QOS_MAC_TX_TIMESTAMP_STATUS_SECONDS_TXTSSHI(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TX_TIMESTAMP_STATUS_SECONDS_TXTSSHI_SHIFT)) & ENET_QOS_MAC_TX_TIMESTAMP_STATUS_SECONDS_TXTSSHI_MASK)
/*! @} */

/*! @name MAC_AUXILIARY_CONTROL - Auxiliary Timestamp Control */
/*! @{ */

#define ENET_QOS_MAC_AUXILIARY_CONTROL_ATSFC_MASK (0x1U)
#define ENET_QOS_MAC_AUXILIARY_CONTROL_ATSFC_SHIFT (0U)
/*! ATSFC - Auxiliary Snapshot FIFO Clear
 *  0b0..Auxiliary Snapshot FIFO Clear is disabled
 *  0b1..Auxiliary Snapshot FIFO Clear is enabled
 */
#define ENET_QOS_MAC_AUXILIARY_CONTROL_ATSFC(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_AUXILIARY_CONTROL_ATSFC_SHIFT)) & ENET_QOS_MAC_AUXILIARY_CONTROL_ATSFC_MASK)

#define ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN0_MASK (0x10U)
#define ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN0_SHIFT (4U)
/*! ATSEN0 - Auxiliary Snapshot 0 Enable
 *  0b0..Auxiliary Snapshot $i is disabled
 *  0b1..Auxiliary Snapshot $i is enabled
 */
#define ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN0(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN0_SHIFT)) & ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN0_MASK)

#define ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN1_MASK (0x20U)
#define ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN1_SHIFT (5U)
/*! ATSEN1 - Auxiliary Snapshot 1 Enable
 *  0b0..Auxiliary Snapshot $i is disabled
 *  0b1..Auxiliary Snapshot $i is enabled
 */
#define ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN1(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN1_SHIFT)) & ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN1_MASK)

#define ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN2_MASK (0x40U)
#define ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN2_SHIFT (6U)
/*! ATSEN2 - Auxiliary Snapshot 2 Enable
 *  0b0..Auxiliary Snapshot $i is disabled
 *  0b1..Auxiliary Snapshot $i is enabled
 */
#define ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN2(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN2_SHIFT)) & ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN2_MASK)

#define ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN3_MASK (0x80U)
#define ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN3_SHIFT (7U)
/*! ATSEN3 - Auxiliary Snapshot 3 Enable
 *  0b0..Auxiliary Snapshot $i is disabled
 *  0b1..Auxiliary Snapshot $i is enabled
 */
#define ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN3(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN3_SHIFT)) & ENET_QOS_MAC_AUXILIARY_CONTROL_ATSEN3_MASK)
/*! @} */

/*! @name MAC_AUXILIARY_TIMESTAMP_NANOSECONDS - Auxiliary Timestamp Nanoseconds */
/*! @{ */

#define ENET_QOS_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_AUXTSLO_MASK (0x7FFFFFFFU)
#define ENET_QOS_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_AUXTSLO_SHIFT (0U)
/*! AUXTSLO - Auxiliary Timestamp Contains the lower 31 bits (nanoseconds field) of the auxiliary timestamp. */
#define ENET_QOS_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_AUXTSLO(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_AUXTSLO_SHIFT)) & ENET_QOS_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_AUXTSLO_MASK)
/*! @} */

/*! @name MAC_AUXILIARY_TIMESTAMP_SECONDS - Auxiliary Timestamp Seconds */
/*! @{ */

#define ENET_QOS_MAC_AUXILIARY_TIMESTAMP_SECONDS_AUXTSHI_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_AUXILIARY_TIMESTAMP_SECONDS_AUXTSHI_SHIFT (0U)
/*! AUXTSHI - Auxiliary Timestamp Contains the lower 32 bits of the Seconds field of the auxiliary timestamp. */
#define ENET_QOS_MAC_AUXILIARY_TIMESTAMP_SECONDS_AUXTSHI(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_AUXILIARY_TIMESTAMP_SECONDS_AUXTSHI_SHIFT)) & ENET_QOS_MAC_AUXILIARY_TIMESTAMP_SECONDS_AUXTSHI_MASK)
/*! @} */

/*! @name MAC_TIMESTAMP_INGRESS_ASYM_CORR - Timestamp Ingress Asymmetry Correction */
/*! @{ */

#define ENET_QOS_MAC_TIMESTAMP_INGRESS_ASYM_CORR_OSTIAC_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TIMESTAMP_INGRESS_ASYM_CORR_OSTIAC_SHIFT (0U)
/*! OSTIAC - One-Step Timestamp Ingress Asymmetry Correction */
#define ENET_QOS_MAC_TIMESTAMP_INGRESS_ASYM_CORR_OSTIAC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_INGRESS_ASYM_CORR_OSTIAC_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_INGRESS_ASYM_CORR_OSTIAC_MASK)
/*! @} */

/*! @name MAC_TIMESTAMP_EGRESS_ASYM_CORR - Timestamp Egress Asymmetry Correction */
/*! @{ */

#define ENET_QOS_MAC_TIMESTAMP_EGRESS_ASYM_CORR_OSTEAC_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TIMESTAMP_EGRESS_ASYM_CORR_OSTEAC_SHIFT (0U)
/*! OSTEAC - One-Step Timestamp Egress Asymmetry Correction */
#define ENET_QOS_MAC_TIMESTAMP_EGRESS_ASYM_CORR_OSTEAC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_EGRESS_ASYM_CORR_OSTEAC_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_EGRESS_ASYM_CORR_OSTEAC_MASK)
/*! @} */

/*! @name MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND - Timestamp Ingress Correction Nanosecond */
/*! @{ */

#define ENET_QOS_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_TSIC_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_TSIC_SHIFT (0U)
/*! TSIC - Timestamp Ingress Correction This field contains the ingress path correction value as
 *    defined by the Ingress Correction expression.
 */
#define ENET_QOS_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_TSIC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_TSIC_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_TSIC_MASK)
/*! @} */

/*! @name MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND - Timestamp Egress Correction Nanosecond */
/*! @{ */

#define ENET_QOS_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_TSEC_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_TSEC_SHIFT (0U)
/*! TSEC - Timestamp Egress Correction This field contains the nanoseconds part of the egress path
 *    correction value as defined by the Egress Correction expression.
 */
#define ENET_QOS_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_TSEC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_TSEC_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_TSEC_MASK)
/*! @} */

/*! @name MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC - Timestamp Ingress Correction Subnanosecond */
/*! @{ */

#define ENET_QOS_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS_MASK (0xFF00U)
#define ENET_QOS_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS_SHIFT (8U)
/*! TSICSNS - Timestamp Ingress Correction, sub-nanoseconds This field contains the sub-nanoseconds
 *    part of the ingress path correction value as defined by the "Ingress Correction" expression.
 */
#define ENET_QOS_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS_MASK)
/*! @} */

/*! @name MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC - Timestamp Egress Correction Subnanosecond */
/*! @{ */

#define ENET_QOS_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS_MASK (0xFF00U)
#define ENET_QOS_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS_SHIFT (8U)
/*! TSECSNS - Timestamp Egress Correction, sub-nanoseconds This field contains the sub-nanoseconds
 *    part of the egress path correction value as defined by the "Egress Correction" expression.
 */
#define ENET_QOS_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS_MASK)
/*! @} */

/*! @name MAC_TIMESTAMP_INGRESS_LATENCY - Timestamp Ingress Latency */
/*! @{ */

#define ENET_QOS_MAC_TIMESTAMP_INGRESS_LATENCY_ITLSNS_MASK (0xFF00U)
#define ENET_QOS_MAC_TIMESTAMP_INGRESS_LATENCY_ITLSNS_SHIFT (8U)
/*! ITLSNS - Ingress Timestamp Latency, in nanoseconds */
#define ENET_QOS_MAC_TIMESTAMP_INGRESS_LATENCY_ITLSNS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_INGRESS_LATENCY_ITLSNS_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_INGRESS_LATENCY_ITLSNS_MASK)

#define ENET_QOS_MAC_TIMESTAMP_INGRESS_LATENCY_ITLNS_MASK (0xFFF0000U)
#define ENET_QOS_MAC_TIMESTAMP_INGRESS_LATENCY_ITLNS_SHIFT (16U)
/*! ITLNS - Ingress Timestamp Latency, in sub-nanoseconds */
#define ENET_QOS_MAC_TIMESTAMP_INGRESS_LATENCY_ITLNS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_INGRESS_LATENCY_ITLNS_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_INGRESS_LATENCY_ITLNS_MASK)
/*! @} */

/*! @name MAC_TIMESTAMP_EGRESS_LATENCY - Timestamp Egress Latency */
/*! @{ */

#define ENET_QOS_MAC_TIMESTAMP_EGRESS_LATENCY_ETLSNS_MASK (0xFF00U)
#define ENET_QOS_MAC_TIMESTAMP_EGRESS_LATENCY_ETLSNS_SHIFT (8U)
/*! ETLSNS - Egress Timestamp Latency, in sub-nanoseconds */
#define ENET_QOS_MAC_TIMESTAMP_EGRESS_LATENCY_ETLSNS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_EGRESS_LATENCY_ETLSNS_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_EGRESS_LATENCY_ETLSNS_MASK)

#define ENET_QOS_MAC_TIMESTAMP_EGRESS_LATENCY_ETLNS_MASK (0xFFF0000U)
#define ENET_QOS_MAC_TIMESTAMP_EGRESS_LATENCY_ETLNS_SHIFT (16U)
/*! ETLNS - Egress Timestamp Latency, in nanoseconds */
#define ENET_QOS_MAC_TIMESTAMP_EGRESS_LATENCY_ETLNS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_TIMESTAMP_EGRESS_LATENCY_ETLNS_SHIFT)) & ENET_QOS_MAC_TIMESTAMP_EGRESS_LATENCY_ETLNS_MASK)
/*! @} */

/*! @name MAC_PPS_CONTROL - PPS Control */
/*! @{ */

#define ENET_QOS_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_MASK (0xFU)
#define ENET_QOS_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_SHIFT (0U)
/*! PPSCTRL_PPSCMD - PPS Output Frequency Control This field controls the frequency of the PPS0 output (ptp_pps_o[0]) signal. */
#define ENET_QOS_MAC_PPS_CONTROL_PPSCTRL_PPSCMD(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_SHIFT)) & ENET_QOS_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_MASK)

#define ENET_QOS_MAC_PPS_CONTROL_PPSEN0_MASK     (0x10U)
#define ENET_QOS_MAC_PPS_CONTROL_PPSEN0_SHIFT    (4U)
/*! PPSEN0 - Flexible PPS Output Mode Enable When this bit is set, Bits[3:0] function as PPSCMD.
 *  0b0..Flexible PPS Output Mode is disabled
 *  0b1..Flexible PPS Output Mode is enabled
 */
#define ENET_QOS_MAC_PPS_CONTROL_PPSEN0(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS_CONTROL_PPSEN0_SHIFT)) & ENET_QOS_MAC_PPS_CONTROL_PPSEN0_MASK)

#define ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL0_MASK (0x60U)
#define ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL0_SHIFT (5U)
/*! TRGTMODSEL0 - Target Time Register Mode for PPS0 Output This field indicates the Target Time
 *    registers (MAC_PPS0_TARGET_TIME_SECONDS and MAC_PPS0_TARGET_TIME_NANOSECONDS) mode for PPS0
 *    output signal:
 *  0b00..Target Time registers are programmed only for generating the interrupt event. The Flexible PPS function
 *        must not be enabled in this mode, otherwise spurious transitions may be observed on the corresponding
 *        ptp_pps_o output port
 *  0b01..Reserved
 *  0b10..Target Time registers are programmed for generating the interrupt event and starting or stopping the PPS0 output signal generation
 *  0b11..Target Time registers are programmed only for starting or stopping the PPS0 output signal generation. No interrupt is asserted
 */
#define ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL0(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL0_SHIFT)) & ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL0_MASK)

#define ENET_QOS_MAC_PPS_CONTROL_MCGREN0_MASK    (0x80U)
#define ENET_QOS_MAC_PPS_CONTROL_MCGREN0_SHIFT   (7U)
/*! MCGREN0 - MCGR Mode Enable for PPS0 Output This field enables the 0th PPS instance to operate in PPS or MCGR mode.
 *  0b0..0th PPS instance is enabled to operate in PPS mode
 *  0b1..0th PPS instance is enabled to operate in MCGR mode
 */
#define ENET_QOS_MAC_PPS_CONTROL_MCGREN0(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS_CONTROL_MCGREN0_SHIFT)) & ENET_QOS_MAC_PPS_CONTROL_MCGREN0_MASK)

#define ENET_QOS_MAC_PPS_CONTROL_PPSCMD1_MASK    (0xF00U)
#define ENET_QOS_MAC_PPS_CONTROL_PPSCMD1_SHIFT   (8U)
/*! PPSCMD1 - Flexible PPS1 Output Control This field controls the flexible PPS1 output (ptp_pps_o[1]) signal. */
#define ENET_QOS_MAC_PPS_CONTROL_PPSCMD1(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS_CONTROL_PPSCMD1_SHIFT)) & ENET_QOS_MAC_PPS_CONTROL_PPSCMD1_MASK)

#define ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL1_MASK (0x6000U)
#define ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL1_SHIFT (13U)
/*! TRGTMODSEL1 - Target Time Register Mode for PPS1 Output This field indicates the Target Time
 *    registers (MAC_PPS1_TARGET_TIME_SECONDS and MAC_PPS1_TARGET_TIME_NANOSECONDS) mode for PPS1
 *    output signal.
 *  0b00..Target Time registers are programmed only for generating the interrupt event. The Flexible PPS function
 *        must not be enabled in this mode, otherwise spurious transitions may be observed on the corresponding
 *        ptp_pps_o output port
 *  0b01..Reserved
 *  0b10..Target Time registers are programmed for generating the interrupt event and starting or stopping the PPS0 output signal generation
 *  0b11..Target Time registers are programmed only for starting or stopping the PPS0 output signal generation. No interrupt is asserted
 */
#define ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL1(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL1_SHIFT)) & ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL1_MASK)

#define ENET_QOS_MAC_PPS_CONTROL_MCGREN1_MASK    (0x8000U)
#define ENET_QOS_MAC_PPS_CONTROL_MCGREN1_SHIFT   (15U)
/*! MCGREN1 - MCGR Mode Enable for PPS1 Output This field enables the 1st PPS instance to operate in PPS or MCGR mode.
 *  0b0..1st PPS instance is disabled to operate in PPS or MCGR mode
 *  0b1..1st PPS instance is enabled to operate in PPS or MCGR mode
 */
#define ENET_QOS_MAC_PPS_CONTROL_MCGREN1(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS_CONTROL_MCGREN1_SHIFT)) & ENET_QOS_MAC_PPS_CONTROL_MCGREN1_MASK)

#define ENET_QOS_MAC_PPS_CONTROL_PPSCMD2_MASK    (0xF0000U)
#define ENET_QOS_MAC_PPS_CONTROL_PPSCMD2_SHIFT   (16U)
/*! PPSCMD2 - Flexible PPS2 Output Control This field controls the flexible PPS2 output (ptp_pps_o[2]) signal. */
#define ENET_QOS_MAC_PPS_CONTROL_PPSCMD2(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS_CONTROL_PPSCMD2_SHIFT)) & ENET_QOS_MAC_PPS_CONTROL_PPSCMD2_MASK)

#define ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL2_MASK (0x600000U)
#define ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL2_SHIFT (21U)
/*! TRGTMODSEL2 - Target Time Register Mode for PPS2 Output This field indicates the Target Time
 *    registers (MAC_PPS2_TARGET_TIME_SECONDS and MAC_PPS2_TARGET_TIME_NANOSECONDS) mode for PPS2
 *    output signal.
 *  0b00..Target Time registers are programmed only for generating the interrupt event. The Flexible PPS function
 *        must not be enabled in this mode, otherwise spurious transitions may be observed on the corresponding
 *        ptp_pps_o output port
 *  0b01..Reserved
 *  0b10..Target Time registers are programmed for generating the interrupt event and starting or stopping the PPS0 output signal generation
 *  0b11..Target Time registers are programmed only for starting or stopping the PPS0 output signal generation. No interrupt is asserted
 */
#define ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL2(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL2_SHIFT)) & ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL2_MASK)

#define ENET_QOS_MAC_PPS_CONTROL_MCGREN2_MASK    (0x800000U)
#define ENET_QOS_MAC_PPS_CONTROL_MCGREN2_SHIFT   (23U)
/*! MCGREN2 - MCGR Mode Enable for PPS2 Output This field enables the 2nd PPS instance to operate in PPS or MCGR mode.
 *  0b0..2nd PPS instance is disabled to operate in PPS or MCGR mode
 *  0b1..2nd PPS instance is enabled to operate in PPS or MCGR mode
 */
#define ENET_QOS_MAC_PPS_CONTROL_MCGREN2(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS_CONTROL_MCGREN2_SHIFT)) & ENET_QOS_MAC_PPS_CONTROL_MCGREN2_MASK)

#define ENET_QOS_MAC_PPS_CONTROL_PPSCMD3_MASK    (0xF000000U)
#define ENET_QOS_MAC_PPS_CONTROL_PPSCMD3_SHIFT   (24U)
/*! PPSCMD3 - Flexible PPS3 Output Control This field controls the flexible PPS3 output (ptp_pps_o[3]) signal. */
#define ENET_QOS_MAC_PPS_CONTROL_PPSCMD3(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS_CONTROL_PPSCMD3_SHIFT)) & ENET_QOS_MAC_PPS_CONTROL_PPSCMD3_MASK)

#define ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL3_MASK (0x60000000U)
#define ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL3_SHIFT (29U)
/*! TRGTMODSEL3 - Target Time Register Mode for PPS3 Output This field indicates the Target Time
 *    registers (MAC_PPS3_TARGET_TIME_SECONDS and MAC_PPS3_TARGET_TIME_NANOSECONDS) mode for PPS3
 *    output signal.
 *  0b00..Target Time registers are programmed only for generating the interrupt event. The Flexible PPS function
 *        must not be enabled in this mode, otherwise spurious transitions may be observed on the corresponding
 *        ptp_pps_o output port
 *  0b01..Reserved
 *  0b10..Target Time registers are programmed for generating the interrupt event and starting or stopping the PPS0 output signal generation
 *  0b11..Target Time registers are programmed only for starting or stopping the PPS0 output signal generation. No interrupt is asserted
 */
#define ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL3(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL3_SHIFT)) & ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL3_MASK)

#define ENET_QOS_MAC_PPS_CONTROL_MCGREN3_MASK    (0x80000000U)
#define ENET_QOS_MAC_PPS_CONTROL_MCGREN3_SHIFT   (31U)
/*! MCGREN3 - MCGR Mode Enable for PPS3 Output This field enables the 3rd PPS instance to operate in PPS or MCGR mode. */
#define ENET_QOS_MAC_PPS_CONTROL_MCGREN3(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS_CONTROL_MCGREN3_SHIFT)) & ENET_QOS_MAC_PPS_CONTROL_MCGREN3_MASK)
/*! @} */

/*! @name MAC_PPS0_TARGET_TIME_SECONDS - PPS0 Target Time Seconds */
/*! @{ */

#define ENET_QOS_MAC_PPS0_TARGET_TIME_SECONDS_TSTRH0_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_PPS0_TARGET_TIME_SECONDS_TSTRH0_SHIFT (0U)
/*! TSTRH0 - PPS Target Time Seconds Register This field stores the time in seconds. */
#define ENET_QOS_MAC_PPS0_TARGET_TIME_SECONDS_TSTRH0(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS0_TARGET_TIME_SECONDS_TSTRH0_SHIFT)) & ENET_QOS_MAC_PPS0_TARGET_TIME_SECONDS_TSTRH0_MASK)
/*! @} */

/*! @name MAC_PPS0_TARGET_TIME_NANOSECONDS - PPS0 Target Time Nanoseconds */
/*! @{ */

#define ENET_QOS_MAC_PPS0_TARGET_TIME_NANOSECONDS_TTSL0_MASK (0x7FFFFFFFU)
#define ENET_QOS_MAC_PPS0_TARGET_TIME_NANOSECONDS_TTSL0_SHIFT (0U)
/*! TTSL0 - Target Time Low for PPS Register This register stores the time in (signed) nanoseconds. */
#define ENET_QOS_MAC_PPS0_TARGET_TIME_NANOSECONDS_TTSL0(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS0_TARGET_TIME_NANOSECONDS_TTSL0_SHIFT)) & ENET_QOS_MAC_PPS0_TARGET_TIME_NANOSECONDS_TTSL0_MASK)

#define ENET_QOS_MAC_PPS0_TARGET_TIME_NANOSECONDS_TRGTBUSY0_MASK (0x80000000U)
#define ENET_QOS_MAC_PPS0_TARGET_TIME_NANOSECONDS_TRGTBUSY0_SHIFT (31U)
/*! TRGTBUSY0 - PPS Target Time Register Busy The MAC sets this bit when the PPSCMD0 field in the
 *    PPS_CONTROL register is programmed to 010 or 011.
 *  0b0..PPS Target Time Register Busy status is not detected
 *  0b1..PPS Target Time Register Busy is detected
 */
#define ENET_QOS_MAC_PPS0_TARGET_TIME_NANOSECONDS_TRGTBUSY0(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS0_TARGET_TIME_NANOSECONDS_TRGTBUSY0_SHIFT)) & ENET_QOS_MAC_PPS0_TARGET_TIME_NANOSECONDS_TRGTBUSY0_MASK)
/*! @} */

/*! @name MAC_PPS0_INTERVAL - PPS0 Interval */
/*! @{ */

#define ENET_QOS_MAC_PPS0_INTERVAL_PPSINT0_MASK  (0xFFFFFFFFU)
#define ENET_QOS_MAC_PPS0_INTERVAL_PPSINT0_SHIFT (0U)
/*! PPSINT0 - PPS Output Signal Interval These bits store the interval between the rising edges of PPS0 signal output. */
#define ENET_QOS_MAC_PPS0_INTERVAL_PPSINT0(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS0_INTERVAL_PPSINT0_SHIFT)) & ENET_QOS_MAC_PPS0_INTERVAL_PPSINT0_MASK)
/*! @} */

/*! @name MAC_PPS0_WIDTH - PPS0 Width */
/*! @{ */

#define ENET_QOS_MAC_PPS0_WIDTH_PPSWIDTH0_MASK   (0xFFFFFFFFU)
#define ENET_QOS_MAC_PPS0_WIDTH_PPSWIDTH0_SHIFT  (0U)
/*! PPSWIDTH0 - PPS Output Signal Width These bits store the width between the rising edge and
 *    corresponding falling edge of PPS0 signal output.
 */
#define ENET_QOS_MAC_PPS0_WIDTH_PPSWIDTH0(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS0_WIDTH_PPSWIDTH0_SHIFT)) & ENET_QOS_MAC_PPS0_WIDTH_PPSWIDTH0_MASK)
/*! @} */

/*! @name MAC_PPS1_TARGET_TIME_SECONDS - PPS1 Target Time Seconds */
/*! @{ */

#define ENET_QOS_MAC_PPS1_TARGET_TIME_SECONDS_TSTRH1_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_PPS1_TARGET_TIME_SECONDS_TSTRH1_SHIFT (0U)
/*! TSTRH1 - PPS Target Time Seconds Register This field stores the time in seconds. */
#define ENET_QOS_MAC_PPS1_TARGET_TIME_SECONDS_TSTRH1(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS1_TARGET_TIME_SECONDS_TSTRH1_SHIFT)) & ENET_QOS_MAC_PPS1_TARGET_TIME_SECONDS_TSTRH1_MASK)
/*! @} */

/*! @name MAC_PPS1_TARGET_TIME_NANOSECONDS - PPS1 Target Time Nanoseconds */
/*! @{ */

#define ENET_QOS_MAC_PPS1_TARGET_TIME_NANOSECONDS_TTSL1_MASK (0x7FFFFFFFU)
#define ENET_QOS_MAC_PPS1_TARGET_TIME_NANOSECONDS_TTSL1_SHIFT (0U)
/*! TTSL1 - Target Time Low for PPS Register This register stores the time in (signed) nanoseconds. */
#define ENET_QOS_MAC_PPS1_TARGET_TIME_NANOSECONDS_TTSL1(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS1_TARGET_TIME_NANOSECONDS_TTSL1_SHIFT)) & ENET_QOS_MAC_PPS1_TARGET_TIME_NANOSECONDS_TTSL1_MASK)

#define ENET_QOS_MAC_PPS1_TARGET_TIME_NANOSECONDS_TRGTBUSY1_MASK (0x80000000U)
#define ENET_QOS_MAC_PPS1_TARGET_TIME_NANOSECONDS_TRGTBUSY1_SHIFT (31U)
/*! TRGTBUSY1 - PPS Target Time Register Busy The MAC sets this bit when the PPSCMD0 field in the
 *    PPS_CONTROL register is programmed to 010 or 011.
 *  0b0..PPS Target Time Register Busy status is not detected
 *  0b1..PPS Target Time Register Busy is detected
 */
#define ENET_QOS_MAC_PPS1_TARGET_TIME_NANOSECONDS_TRGTBUSY1(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS1_TARGET_TIME_NANOSECONDS_TRGTBUSY1_SHIFT)) & ENET_QOS_MAC_PPS1_TARGET_TIME_NANOSECONDS_TRGTBUSY1_MASK)
/*! @} */

/*! @name MAC_PPS1_INTERVAL - PPS1 Interval */
/*! @{ */

#define ENET_QOS_MAC_PPS1_INTERVAL_PPSINT1_MASK  (0xFFFFFFFFU)
#define ENET_QOS_MAC_PPS1_INTERVAL_PPSINT1_SHIFT (0U)
/*! PPSINT1 - PPS Output Signal Interval These bits store the interval between the rising edges of PPS1 signal output. */
#define ENET_QOS_MAC_PPS1_INTERVAL_PPSINT1(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS1_INTERVAL_PPSINT1_SHIFT)) & ENET_QOS_MAC_PPS1_INTERVAL_PPSINT1_MASK)
/*! @} */

/*! @name MAC_PPS1_WIDTH - PPS1 Width */
/*! @{ */

#define ENET_QOS_MAC_PPS1_WIDTH_PPSWIDTH1_MASK   (0xFFFFFFFFU)
#define ENET_QOS_MAC_PPS1_WIDTH_PPSWIDTH1_SHIFT  (0U)
/*! PPSWIDTH1 - PPS Output Signal Width These bits store the width between the rising edge and
 *    corresponding falling edge of PPS0 signal output.
 */
#define ENET_QOS_MAC_PPS1_WIDTH_PPSWIDTH1(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS1_WIDTH_PPSWIDTH1_SHIFT)) & ENET_QOS_MAC_PPS1_WIDTH_PPSWIDTH1_MASK)
/*! @} */

/*! @name MAC_PPS2_TARGET_TIME_SECONDS - PPS2 Target Time Seconds */
/*! @{ */

#define ENET_QOS_MAC_PPS2_TARGET_TIME_SECONDS_TSTRH2_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_PPS2_TARGET_TIME_SECONDS_TSTRH2_SHIFT (0U)
/*! TSTRH2 - PPS Target Time Seconds Register This field stores the time in seconds. */
#define ENET_QOS_MAC_PPS2_TARGET_TIME_SECONDS_TSTRH2(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS2_TARGET_TIME_SECONDS_TSTRH2_SHIFT)) & ENET_QOS_MAC_PPS2_TARGET_TIME_SECONDS_TSTRH2_MASK)
/*! @} */

/*! @name MAC_PPS2_TARGET_TIME_NANOSECONDS - PPS2 Target Time Nanoseconds */
/*! @{ */

#define ENET_QOS_MAC_PPS2_TARGET_TIME_NANOSECONDS_TTSL2_MASK (0x7FFFFFFFU)
#define ENET_QOS_MAC_PPS2_TARGET_TIME_NANOSECONDS_TTSL2_SHIFT (0U)
/*! TTSL2 - Target Time Low for PPS Register This register stores the time in (signed) nanoseconds. */
#define ENET_QOS_MAC_PPS2_TARGET_TIME_NANOSECONDS_TTSL2(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS2_TARGET_TIME_NANOSECONDS_TTSL2_SHIFT)) & ENET_QOS_MAC_PPS2_TARGET_TIME_NANOSECONDS_TTSL2_MASK)

#define ENET_QOS_MAC_PPS2_TARGET_TIME_NANOSECONDS_TRGTBUSY2_MASK (0x80000000U)
#define ENET_QOS_MAC_PPS2_TARGET_TIME_NANOSECONDS_TRGTBUSY2_SHIFT (31U)
/*! TRGTBUSY2 - PPS Target Time Register Busy The MAC sets this bit when the PPSCMD0 field in the
 *    PPS_CONTROL register is programmed to 010 or 011.
 *  0b0..PPS Target Time Register Busy status is not detected
 *  0b1..PPS Target Time Register Busy is detected
 */
#define ENET_QOS_MAC_PPS2_TARGET_TIME_NANOSECONDS_TRGTBUSY2(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS2_TARGET_TIME_NANOSECONDS_TRGTBUSY2_SHIFT)) & ENET_QOS_MAC_PPS2_TARGET_TIME_NANOSECONDS_TRGTBUSY2_MASK)
/*! @} */

/*! @name MAC_PPS2_INTERVAL - PPS2 Interval */
/*! @{ */

#define ENET_QOS_MAC_PPS2_INTERVAL_PPSINT2_MASK  (0xFFFFFFFFU)
#define ENET_QOS_MAC_PPS2_INTERVAL_PPSINT2_SHIFT (0U)
/*! PPSINT2 - PPS Output Signal Interval These bits store the interval between the rising edges of PPS2 signal output. */
#define ENET_QOS_MAC_PPS2_INTERVAL_PPSINT2(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS2_INTERVAL_PPSINT2_SHIFT)) & ENET_QOS_MAC_PPS2_INTERVAL_PPSINT2_MASK)
/*! @} */

/*! @name MAC_PPS2_WIDTH - PPS2 Width */
/*! @{ */

#define ENET_QOS_MAC_PPS2_WIDTH_PPSWIDTH2_MASK   (0xFFFFFFFFU)
#define ENET_QOS_MAC_PPS2_WIDTH_PPSWIDTH2_SHIFT  (0U)
/*! PPSWIDTH2 - PPS Output Signal Width These bits store the width between the rising edge and
 *    corresponding falling edge of PPS0 signal output.
 */
#define ENET_QOS_MAC_PPS2_WIDTH_PPSWIDTH2(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS2_WIDTH_PPSWIDTH2_SHIFT)) & ENET_QOS_MAC_PPS2_WIDTH_PPSWIDTH2_MASK)
/*! @} */

/*! @name MAC_PPS3_TARGET_TIME_SECONDS - PPS3 Target Time Seconds */
/*! @{ */

#define ENET_QOS_MAC_PPS3_TARGET_TIME_SECONDS_TSTRH3_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_PPS3_TARGET_TIME_SECONDS_TSTRH3_SHIFT (0U)
/*! TSTRH3 - PPS Target Time Seconds Register This field stores the time in seconds. */
#define ENET_QOS_MAC_PPS3_TARGET_TIME_SECONDS_TSTRH3(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS3_TARGET_TIME_SECONDS_TSTRH3_SHIFT)) & ENET_QOS_MAC_PPS3_TARGET_TIME_SECONDS_TSTRH3_MASK)
/*! @} */

/*! @name MAC_PPS3_TARGET_TIME_NANOSECONDS - PPS3 Target Time Nanoseconds */
/*! @{ */

#define ENET_QOS_MAC_PPS3_TARGET_TIME_NANOSECONDS_TTSL3_MASK (0x7FFFFFFFU)
#define ENET_QOS_MAC_PPS3_TARGET_TIME_NANOSECONDS_TTSL3_SHIFT (0U)
/*! TTSL3 - Target Time Low for PPS Register This register stores the time in (signed) nanoseconds. */
#define ENET_QOS_MAC_PPS3_TARGET_TIME_NANOSECONDS_TTSL3(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS3_TARGET_TIME_NANOSECONDS_TTSL3_SHIFT)) & ENET_QOS_MAC_PPS3_TARGET_TIME_NANOSECONDS_TTSL3_MASK)

#define ENET_QOS_MAC_PPS3_TARGET_TIME_NANOSECONDS_TRGTBUSY3_MASK (0x80000000U)
#define ENET_QOS_MAC_PPS3_TARGET_TIME_NANOSECONDS_TRGTBUSY3_SHIFT (31U)
/*! TRGTBUSY3 - PPS Target Time Register Busy The MAC sets this bit when the PPSCMD0 field in the
 *    PPS_CONTROL register is programmed to 010 or 011.
 *  0b0..PPS Target Time Register Busy status is not detected
 *  0b1..PPS Target Time Register Busy is detected
 */
#define ENET_QOS_MAC_PPS3_TARGET_TIME_NANOSECONDS_TRGTBUSY3(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS3_TARGET_TIME_NANOSECONDS_TRGTBUSY3_SHIFT)) & ENET_QOS_MAC_PPS3_TARGET_TIME_NANOSECONDS_TRGTBUSY3_MASK)
/*! @} */

/*! @name MAC_PPS3_INTERVAL - PPS3 Interval */
/*! @{ */

#define ENET_QOS_MAC_PPS3_INTERVAL_PPSINT3_MASK  (0xFFFFFFFFU)
#define ENET_QOS_MAC_PPS3_INTERVAL_PPSINT3_SHIFT (0U)
/*! PPSINT3 - PPS Output Signal Interval These bits store the interval between the rising edges of PPS3 signal output. */
#define ENET_QOS_MAC_PPS3_INTERVAL_PPSINT3(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS3_INTERVAL_PPSINT3_SHIFT)) & ENET_QOS_MAC_PPS3_INTERVAL_PPSINT3_MASK)
/*! @} */

/*! @name MAC_PPS3_WIDTH - PPS3 Width */
/*! @{ */

#define ENET_QOS_MAC_PPS3_WIDTH_PPSWIDTH3_MASK   (0xFFFFFFFFU)
#define ENET_QOS_MAC_PPS3_WIDTH_PPSWIDTH3_SHIFT  (0U)
/*! PPSWIDTH3 - PPS Output Signal Width These bits store the width between the rising edge and
 *    corresponding falling edge of PPS0 signal output.
 */
#define ENET_QOS_MAC_PPS3_WIDTH_PPSWIDTH3(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PPS3_WIDTH_PPSWIDTH3_SHIFT)) & ENET_QOS_MAC_PPS3_WIDTH_PPSWIDTH3_MASK)
/*! @} */

/*! @name MAC_PTO_CONTROL - PTP Offload Engine Control */
/*! @{ */

#define ENET_QOS_MAC_PTO_CONTROL_PTOEN_MASK      (0x1U)
#define ENET_QOS_MAC_PTO_CONTROL_PTOEN_SHIFT     (0U)
/*! PTOEN - PTP Offload Enable When this bit is set, the PTP Offload feature is enabled.
 *  0b0..PTP Offload feature is disabled
 *  0b1..PTP Offload feature is enabled
 */
#define ENET_QOS_MAC_PTO_CONTROL_PTOEN(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PTO_CONTROL_PTOEN_SHIFT)) & ENET_QOS_MAC_PTO_CONTROL_PTOEN_MASK)

#define ENET_QOS_MAC_PTO_CONTROL_ASYNCEN_MASK    (0x2U)
#define ENET_QOS_MAC_PTO_CONTROL_ASYNCEN_SHIFT   (1U)
/*! ASYNCEN - Automatic PTP SYNC message Enable When this bit is set, PTP SYNC message is generated
 *    periodically based on interval programmed or trigger from application, when the MAC is
 *    programmed to be in Clock Master mode.
 *  0b0..Automatic PTP SYNC message is disabled
 *  0b1..Automatic PTP SYNC message is enabled
 */
#define ENET_QOS_MAC_PTO_CONTROL_ASYNCEN(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PTO_CONTROL_ASYNCEN_SHIFT)) & ENET_QOS_MAC_PTO_CONTROL_ASYNCEN_MASK)

#define ENET_QOS_MAC_PTO_CONTROL_APDREQEN_MASK   (0x4U)
#define ENET_QOS_MAC_PTO_CONTROL_APDREQEN_SHIFT  (2U)
/*! APDREQEN - Automatic PTP Pdelay_Req message Enable When this bit is set, PTP Pdelay_Req message
 *    is generated periodically based on interval programmed or trigger from application, when the
 *    MAC is programmed to be in Peer-to-Peer Transparent mode.
 *  0b0..Automatic PTP Pdelay_Req message is disabled
 *  0b1..Automatic PTP Pdelay_Req message is enabled
 */
#define ENET_QOS_MAC_PTO_CONTROL_APDREQEN(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PTO_CONTROL_APDREQEN_SHIFT)) & ENET_QOS_MAC_PTO_CONTROL_APDREQEN_MASK)

#define ENET_QOS_MAC_PTO_CONTROL_ASYNCTRIG_MASK  (0x10U)
#define ENET_QOS_MAC_PTO_CONTROL_ASYNCTRIG_SHIFT (4U)
/*! ASYNCTRIG - Automatic PTP SYNC message Trigger When this bit is set, one PTP SYNC message is transmitted.
 *  0b0..Automatic PTP SYNC message Trigger is disabled
 *  0b1..Automatic PTP SYNC message Trigger is enabled
 */
#define ENET_QOS_MAC_PTO_CONTROL_ASYNCTRIG(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PTO_CONTROL_ASYNCTRIG_SHIFT)) & ENET_QOS_MAC_PTO_CONTROL_ASYNCTRIG_MASK)

#define ENET_QOS_MAC_PTO_CONTROL_APDREQTRIG_MASK (0x20U)
#define ENET_QOS_MAC_PTO_CONTROL_APDREQTRIG_SHIFT (5U)
/*! APDREQTRIG - Automatic PTP Pdelay_Req message Trigger When this bit is set, one PTP Pdelay_Req message is transmitted.
 *  0b0..Automatic PTP Pdelay_Req message Trigger is disabled
 *  0b1..Automatic PTP Pdelay_Req message Trigger is enabled
 */
#define ENET_QOS_MAC_PTO_CONTROL_APDREQTRIG(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PTO_CONTROL_APDREQTRIG_SHIFT)) & ENET_QOS_MAC_PTO_CONTROL_APDREQTRIG_MASK)

#define ENET_QOS_MAC_PTO_CONTROL_DRRDIS_MASK     (0x40U)
#define ENET_QOS_MAC_PTO_CONTROL_DRRDIS_SHIFT    (6U)
/*! DRRDIS - Disable PTO Delay Request/Response response generation When this bit is set, the Delay
 *    Request and Delay response is not generated for received SYNC and Delay request packet
 *    respectively, as required by the programmed mode.
 *  0b0..PTO Delay Request/Response response generation is enabled
 *  0b1..PTO Delay Request/Response response generation is disabled
 */
#define ENET_QOS_MAC_PTO_CONTROL_DRRDIS(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PTO_CONTROL_DRRDIS_SHIFT)) & ENET_QOS_MAC_PTO_CONTROL_DRRDIS_MASK)

#define ENET_QOS_MAC_PTO_CONTROL_PDRDIS_MASK     (0x80U)
#define ENET_QOS_MAC_PTO_CONTROL_PDRDIS_SHIFT    (7U)
/*! PDRDIS - Disable Peer Delay Response response generation When this bit is set, the Peer Delay
 *    Response (Pdelay_Resp) response is not be generated for received Peer Delay Request (Pdelay_Req)
 *    request packet, as required by the programmed mode.
 *  0b0..Peer Delay Response response generation is enabled
 *  0b1..Peer Delay Response response generation is disabled
 */
#define ENET_QOS_MAC_PTO_CONTROL_PDRDIS(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PTO_CONTROL_PDRDIS_SHIFT)) & ENET_QOS_MAC_PTO_CONTROL_PDRDIS_MASK)

#define ENET_QOS_MAC_PTO_CONTROL_DN_MASK         (0xFF00U)
#define ENET_QOS_MAC_PTO_CONTROL_DN_SHIFT        (8U)
/*! DN - Domain Number This field indicates the domain Number in which the PTP node is operating. */
#define ENET_QOS_MAC_PTO_CONTROL_DN(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_PTO_CONTROL_DN_SHIFT)) & ENET_QOS_MAC_PTO_CONTROL_DN_MASK)
/*! @} */

/*! @name MAC_SOURCE_PORT_IDENTITY0 - Source Port Identity 0 */
/*! @{ */

#define ENET_QOS_MAC_SOURCE_PORT_IDENTITY0_SPI0_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_SOURCE_PORT_IDENTITY0_SPI0_SHIFT (0U)
/*! SPI0 - Source Port Identity 0 This field indicates bits [31:0] of sourcePortIdentity of PTP node. */
#define ENET_QOS_MAC_SOURCE_PORT_IDENTITY0_SPI0(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_SOURCE_PORT_IDENTITY0_SPI0_SHIFT)) & ENET_QOS_MAC_SOURCE_PORT_IDENTITY0_SPI0_MASK)
/*! @} */

/*! @name MAC_SOURCE_PORT_IDENTITY1 - Source Port Identity 1 */
/*! @{ */

#define ENET_QOS_MAC_SOURCE_PORT_IDENTITY1_SPI1_MASK (0xFFFFFFFFU)
#define ENET_QOS_MAC_SOURCE_PORT_IDENTITY1_SPI1_SHIFT (0U)
/*! SPI1 - Source Port Identity 1 This field indicates bits [63:32] of sourcePortIdentity of PTP node. */
#define ENET_QOS_MAC_SOURCE_PORT_IDENTITY1_SPI1(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_SOURCE_PORT_IDENTITY1_SPI1_SHIFT)) & ENET_QOS_MAC_SOURCE_PORT_IDENTITY1_SPI1_MASK)
/*! @} */

/*! @name MAC_SOURCE_PORT_IDENTITY2 - Source Port Identity 2 */
/*! @{ */

#define ENET_QOS_MAC_SOURCE_PORT_IDENTITY2_SPI2_MASK (0xFFFFU)
#define ENET_QOS_MAC_SOURCE_PORT_IDENTITY2_SPI2_SHIFT (0U)
/*! SPI2 - Source Port Identity 2 This field indicates bits [79:64] of sourcePortIdentity of PTP node. */
#define ENET_QOS_MAC_SOURCE_PORT_IDENTITY2_SPI2(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_SOURCE_PORT_IDENTITY2_SPI2_SHIFT)) & ENET_QOS_MAC_SOURCE_PORT_IDENTITY2_SPI2_MASK)
/*! @} */

/*! @name MAC_LOG_MESSAGE_INTERVAL - Log Message Interval */
/*! @{ */

#define ENET_QOS_MAC_LOG_MESSAGE_INTERVAL_LSI_MASK (0xFFU)
#define ENET_QOS_MAC_LOG_MESSAGE_INTERVAL_LSI_SHIFT (0U)
/*! LSI - Log Sync Interval This field indicates the periodicity of the automatically generated SYNC
 *    message when the PTP node is Master.
 */
#define ENET_QOS_MAC_LOG_MESSAGE_INTERVAL_LSI(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LOG_MESSAGE_INTERVAL_LSI_SHIFT)) & ENET_QOS_MAC_LOG_MESSAGE_INTERVAL_LSI_MASK)

#define ENET_QOS_MAC_LOG_MESSAGE_INTERVAL_DRSYNCR_MASK (0x700U)
#define ENET_QOS_MAC_LOG_MESSAGE_INTERVAL_DRSYNCR_SHIFT (8U)
/*! DRSYNCR - Delay_Req to SYNC Ratio In Slave mode, it is used for controlling frequency of Delay_Req messages transmitted.
 *  0b000..DelayReq generated for every received SYNC
 *  0b001..DelayReq generated every alternate reception of SYNC
 *  0b010..for every 4 SYNC messages
 *  0b011..for every 8 SYNC messages
 *  0b100..for every 16 SYNC messages
 *  0b101..for every 32 SYNC messages
 *  0b110..Reserved
 */
#define ENET_QOS_MAC_LOG_MESSAGE_INTERVAL_DRSYNCR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LOG_MESSAGE_INTERVAL_DRSYNCR_SHIFT)) & ENET_QOS_MAC_LOG_MESSAGE_INTERVAL_DRSYNCR_MASK)

#define ENET_QOS_MAC_LOG_MESSAGE_INTERVAL_LMPDRI_MASK (0xFF000000U)
#define ENET_QOS_MAC_LOG_MESSAGE_INTERVAL_LMPDRI_SHIFT (24U)
/*! LMPDRI - Log Min Pdelay_Req Interval This field indicates logMinPdelayReqInterval of PTP node. */
#define ENET_QOS_MAC_LOG_MESSAGE_INTERVAL_LMPDRI(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MAC_LOG_MESSAGE_INTERVAL_LMPDRI_SHIFT)) & ENET_QOS_MAC_LOG_MESSAGE_INTERVAL_LMPDRI_MASK)
/*! @} */

/*! @name MTL_OPERATION_MODE - MTL Operation Mode */
/*! @{ */

#define ENET_QOS_MTL_OPERATION_MODE_DTXSTS_MASK  (0x2U)
#define ENET_QOS_MTL_OPERATION_MODE_DTXSTS_SHIFT (1U)
/*! DTXSTS - Drop Transmit Status When this bit is set, the Tx packet status received from the MAC is dropped in the MTL.
 *  0b0..Drop Transmit Status is disabled
 *  0b1..Drop Transmit Status is enabled
 */
#define ENET_QOS_MTL_OPERATION_MODE_DTXSTS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_OPERATION_MODE_DTXSTS_SHIFT)) & ENET_QOS_MTL_OPERATION_MODE_DTXSTS_MASK)

#define ENET_QOS_MTL_OPERATION_MODE_RAA_MASK     (0x4U)
#define ENET_QOS_MTL_OPERATION_MODE_RAA_SHIFT    (2U)
/*! RAA - Receive Arbitration Algorithm This field is used to select the arbitration algorithm for the Rx side.
 *  0b0..Strict priority (SP)
 *  0b1..Weighted Strict Priority (WSP)
 */
#define ENET_QOS_MTL_OPERATION_MODE_RAA(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_OPERATION_MODE_RAA_SHIFT)) & ENET_QOS_MTL_OPERATION_MODE_RAA_MASK)

#define ENET_QOS_MTL_OPERATION_MODE_SCHALG_MASK  (0x60U)
#define ENET_QOS_MTL_OPERATION_MODE_SCHALG_SHIFT (5U)
/*! SCHALG - Tx Scheduling Algorithm This field indicates the algorithm for Tx scheduling:
 *  0b00..WRR algorithm
 *  0b01..WFQ algorithm when DCB feature is selected.Otherwise, Reserved
 *  0b10..DWRR algorithm when DCB feature is selected.Otherwise, Reserved
 *  0b11..Strict priority algorithm
 */
#define ENET_QOS_MTL_OPERATION_MODE_SCHALG(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_OPERATION_MODE_SCHALG_SHIFT)) & ENET_QOS_MTL_OPERATION_MODE_SCHALG_MASK)

#define ENET_QOS_MTL_OPERATION_MODE_CNTPRST_MASK (0x100U)
#define ENET_QOS_MTL_OPERATION_MODE_CNTPRST_SHIFT (8U)
/*! CNTPRST - Counters Preset When this bit is set, - MTL_TxQ[0-7]_Underflow register is initialized/preset to 12'h7F0.
 *  0b0..Counters Preset is disabled
 *  0b1..Counters Preset is enabled
 */
#define ENET_QOS_MTL_OPERATION_MODE_CNTPRST(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_OPERATION_MODE_CNTPRST_SHIFT)) & ENET_QOS_MTL_OPERATION_MODE_CNTPRST_MASK)

#define ENET_QOS_MTL_OPERATION_MODE_CNTCLR_MASK  (0x200U)
#define ENET_QOS_MTL_OPERATION_MODE_CNTCLR_SHIFT (9U)
/*! CNTCLR - Counters Reset When this bit is set, all counters are reset.
 *  0b0..Counters are not reset
 *  0b1..All counters are reset
 */
#define ENET_QOS_MTL_OPERATION_MODE_CNTCLR(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_OPERATION_MODE_CNTCLR_SHIFT)) & ENET_QOS_MTL_OPERATION_MODE_CNTCLR_MASK)

#define ENET_QOS_MTL_OPERATION_MODE_FRPE_MASK    (0x8000U)
#define ENET_QOS_MTL_OPERATION_MODE_FRPE_SHIFT   (15U)
/*! FRPE - Flexible Rx parser Enable When this bit is set to 1, the Programmable Rx Parser functionality is enabled.
 *  0b0..Flexible Rx parser is disabled
 *  0b1..Flexible Rx parser is enabled
 */
#define ENET_QOS_MTL_OPERATION_MODE_FRPE(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_OPERATION_MODE_FRPE_SHIFT)) & ENET_QOS_MTL_OPERATION_MODE_FRPE_MASK)
/*! @} */

/*! @name MTL_DBG_CTL - FIFO Debug Access Control and Status */
/*! @{ */

#define ENET_QOS_MTL_DBG_CTL_FDBGEN_MASK         (0x1U)
#define ENET_QOS_MTL_DBG_CTL_FDBGEN_SHIFT        (0U)
/*! FDBGEN - FIFO Debug Access Enable When this bit is set, it indicates that the debug mode access to the FIFO is enabled.
 *  0b0..FIFO Debug Access is disabled
 *  0b1..FIFO Debug Access is enabled
 */
#define ENET_QOS_MTL_DBG_CTL_FDBGEN(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_CTL_FDBGEN_SHIFT)) & ENET_QOS_MTL_DBG_CTL_FDBGEN_MASK)

#define ENET_QOS_MTL_DBG_CTL_DBGMOD_MASK         (0x2U)
#define ENET_QOS_MTL_DBG_CTL_DBGMOD_SHIFT        (1U)
/*! DBGMOD - Debug Mode Access to FIFO When this bit is set, it indicates that the current access to
 *    the FIFO is read, write, and debug access.
 *  0b0..Debug Mode Access to FIFO is disabled
 *  0b1..Debug Mode Access to FIFO is enabled
 */
#define ENET_QOS_MTL_DBG_CTL_DBGMOD(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_CTL_DBGMOD_SHIFT)) & ENET_QOS_MTL_DBG_CTL_DBGMOD_MASK)

#define ENET_QOS_MTL_DBG_CTL_BYTEEN_MASK         (0xCU)
#define ENET_QOS_MTL_DBG_CTL_BYTEEN_SHIFT        (2U)
/*! BYTEEN - Byte Enables This field indicates the number of data bytes valid in the data register during Write operation.
 *  0b00..Byte 0 valid
 *  0b01..Byte 0 and Byte 1 are valid
 *  0b10..Byte 0, Byte 1, and Byte 2 are valid
 *  0b11..All four bytes are valid
 */
#define ENET_QOS_MTL_DBG_CTL_BYTEEN(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_CTL_BYTEEN_SHIFT)) & ENET_QOS_MTL_DBG_CTL_BYTEEN_MASK)

#define ENET_QOS_MTL_DBG_CTL_PKTSTATE_MASK       (0x60U)
#define ENET_QOS_MTL_DBG_CTL_PKTSTATE_SHIFT      (5U)
/*! PKTSTATE - Encoded Packet State This field is used to write the control information to the Tx FIFO or Rx FIFO.
 *  0b00..Packet Data
 *  0b01..Control Word/Normal Status
 *  0b10..SOP Data/Last Status
 *  0b11..EOP Data/EOP
 */
#define ENET_QOS_MTL_DBG_CTL_PKTSTATE(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_CTL_PKTSTATE_SHIFT)) & ENET_QOS_MTL_DBG_CTL_PKTSTATE_MASK)

#define ENET_QOS_MTL_DBG_CTL_RSTALL_MASK         (0x100U)
#define ENET_QOS_MTL_DBG_CTL_RSTALL_SHIFT        (8U)
/*! RSTALL - Reset All Pointers When this bit is set, the pointers of all FIFOs are reset when FIFO Debug Access is enabled.
 *  0b0..Reset All Pointers is disabled
 *  0b1..Reset All Pointers is enabled
 */
#define ENET_QOS_MTL_DBG_CTL_RSTALL(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_CTL_RSTALL_SHIFT)) & ENET_QOS_MTL_DBG_CTL_RSTALL_MASK)

#define ENET_QOS_MTL_DBG_CTL_RSTSEL_MASK         (0x200U)
#define ENET_QOS_MTL_DBG_CTL_RSTSEL_SHIFT        (9U)
/*! RSTSEL - Reset Pointers of Selected FIFO When this bit is set, the pointers of the
 *    currently-selected FIFO are reset when FIFO Debug Access is enabled.
 *  0b0..Reset Pointers of Selected FIFO is disabled
 *  0b1..Reset Pointers of Selected FIFO is enabled
 */
#define ENET_QOS_MTL_DBG_CTL_RSTSEL(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_CTL_RSTSEL_SHIFT)) & ENET_QOS_MTL_DBG_CTL_RSTSEL_MASK)

#define ENET_QOS_MTL_DBG_CTL_FIFORDEN_MASK       (0x400U)
#define ENET_QOS_MTL_DBG_CTL_FIFORDEN_SHIFT      (10U)
/*! FIFORDEN - FIFO Read Enable When this bit is set, it enables the Read operation on selected FIFO when FIFO Debug Access is enabled.
 *  0b0..FIFO Read is disabled
 *  0b1..FIFO Read is enabled
 */
#define ENET_QOS_MTL_DBG_CTL_FIFORDEN(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_CTL_FIFORDEN_SHIFT)) & ENET_QOS_MTL_DBG_CTL_FIFORDEN_MASK)

#define ENET_QOS_MTL_DBG_CTL_FIFOWREN_MASK       (0x800U)
#define ENET_QOS_MTL_DBG_CTL_FIFOWREN_SHIFT      (11U)
/*! FIFOWREN - FIFO Write Enable When this bit is set, it enables the Write operation on selected
 *    FIFO when FIFO Debug Access is enabled.
 *  0b0..FIFO Write is disabled
 *  0b1..FIFO Write is enabled
 */
#define ENET_QOS_MTL_DBG_CTL_FIFOWREN(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_CTL_FIFOWREN_SHIFT)) & ENET_QOS_MTL_DBG_CTL_FIFOWREN_MASK)

#define ENET_QOS_MTL_DBG_CTL_FIFOSEL_MASK        (0x3000U)
#define ENET_QOS_MTL_DBG_CTL_FIFOSEL_SHIFT       (12U)
/*! FIFOSEL - FIFO Selected for Access This field indicates the FIFO selected for debug access:
 *  0b00..Tx FIFO
 *  0b01..Tx Status FIFO (only read access when SLVMOD is set)
 *  0b10..TSO FIFO (cannot be accessed when SLVMOD is set)
 *  0b11..Rx FIFO
 */
#define ENET_QOS_MTL_DBG_CTL_FIFOSEL(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_CTL_FIFOSEL_SHIFT)) & ENET_QOS_MTL_DBG_CTL_FIFOSEL_MASK)

#define ENET_QOS_MTL_DBG_CTL_PKTIE_MASK          (0x4000U)
#define ENET_QOS_MTL_DBG_CTL_PKTIE_SHIFT         (14U)
/*! PKTIE - Receive Packet Available Interrupt Status Enable When this bit is set, an interrupt is
 *    generated when EOP of received packet is written to the Rx FIFO.
 *  0b0..Receive Packet Available Interrupt Status is disabled
 *  0b1..Receive Packet Available Interrupt Status is enabled
 */
#define ENET_QOS_MTL_DBG_CTL_PKTIE(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_CTL_PKTIE_SHIFT)) & ENET_QOS_MTL_DBG_CTL_PKTIE_MASK)

#define ENET_QOS_MTL_DBG_CTL_STSIE_MASK          (0x8000U)
#define ENET_QOS_MTL_DBG_CTL_STSIE_SHIFT         (15U)
/*! STSIE - Transmit Status Available Interrupt Status Enable When this bit is set, an interrupt is
 *    generated when Transmit status is available in slave mode.
 *  0b0..Transmit Packet Available Interrupt Status is disabled
 *  0b1..Transmit Packet Available Interrupt Status is enabled
 */
#define ENET_QOS_MTL_DBG_CTL_STSIE(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_CTL_STSIE_SHIFT)) & ENET_QOS_MTL_DBG_CTL_STSIE_MASK)
/*! @} */

/*! @name MTL_DBG_STS - FIFO Debug Status */
/*! @{ */

#define ENET_QOS_MTL_DBG_STS_FIFOBUSY_MASK       (0x1U)
#define ENET_QOS_MTL_DBG_STS_FIFOBUSY_SHIFT      (0U)
/*! FIFOBUSY - FIFO Busy When set, this bit indicates that a FIFO operation is in progress in the
 *    MAC and content of the following fields is not valid: - All other fields of this register - All
 *    fields of the MTL_FIFO_DEBUG_DATA register
 *  0b0..FIFO Busy not detected
 *  0b1..FIFO Busy detected
 */
#define ENET_QOS_MTL_DBG_STS_FIFOBUSY(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_STS_FIFOBUSY_SHIFT)) & ENET_QOS_MTL_DBG_STS_FIFOBUSY_MASK)

#define ENET_QOS_MTL_DBG_STS_PKTSTATE_MASK       (0x6U)
#define ENET_QOS_MTL_DBG_STS_PKTSTATE_SHIFT      (1U)
/*! PKTSTATE - Encoded Packet State This field is used to get the control or status information of the selected FIFO.
 *  0b00..Packet Data
 *  0b01..Control Word/Normal Status
 *  0b10..SOP Data/Last Status
 *  0b11..EOP Data/EOP
 */
#define ENET_QOS_MTL_DBG_STS_PKTSTATE(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_STS_PKTSTATE_SHIFT)) & ENET_QOS_MTL_DBG_STS_PKTSTATE_MASK)

#define ENET_QOS_MTL_DBG_STS_BYTEEN_MASK         (0x18U)
#define ENET_QOS_MTL_DBG_STS_BYTEEN_SHIFT        (3U)
/*! BYTEEN - Byte Enables This field indicates the number of data bytes valid in the data register during Read operation.
 *  0b00..Byte 0 valid
 *  0b01..Byte 0 and Byte 1 are valid
 *  0b10..Byte 0, Byte 1, and Byte 2 are valid
 *  0b11..All four bytes are valid
 */
#define ENET_QOS_MTL_DBG_STS_BYTEEN(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_STS_BYTEEN_SHIFT)) & ENET_QOS_MTL_DBG_STS_BYTEEN_MASK)

#define ENET_QOS_MTL_DBG_STS_PKTI_MASK           (0x100U)
#define ENET_QOS_MTL_DBG_STS_PKTI_SHIFT          (8U)
/*! PKTI - Receive Packet Available Interrupt Status When set, this bit indicates that MAC layer has
 *    written the EOP of received packet to the Rx FIFO.
 *  0b0..Receive Packet Available Interrupt Status not detected
 *  0b1..Receive Packet Available Interrupt Status detected
 */
#define ENET_QOS_MTL_DBG_STS_PKTI(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_STS_PKTI_SHIFT)) & ENET_QOS_MTL_DBG_STS_PKTI_MASK)

#define ENET_QOS_MTL_DBG_STS_STSI_MASK           (0x200U)
#define ENET_QOS_MTL_DBG_STS_STSI_SHIFT          (9U)
/*! STSI - Transmit Status Available Interrupt Status When set, this bit indicates that the Slave
 *    mode Tx packet is transmitted, and the status is available in Tx Status FIFO.
 *  0b0..Transmit Status Available Interrupt Status not detected
 *  0b1..Transmit Status Available Interrupt Status detected
 */
#define ENET_QOS_MTL_DBG_STS_STSI(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_STS_STSI_SHIFT)) & ENET_QOS_MTL_DBG_STS_STSI_MASK)

#define ENET_QOS_MTL_DBG_STS_LOCR_MASK           (0xFFFF8000U)
#define ENET_QOS_MTL_DBG_STS_LOCR_SHIFT          (15U)
/*! LOCR - Remaining Locations in the FIFO Slave Access Mode: This field indicates the space available in selected FIFO. */
#define ENET_QOS_MTL_DBG_STS_LOCR(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_DBG_STS_LOCR_SHIFT)) & ENET_QOS_MTL_DBG_STS_LOCR_MASK)
/*! @} */

/*! @name MTL_FIFO_DEBUG_DATA - FIFO Debug Data */
/*! @{ */

#define ENET_QOS_MTL_FIFO_DEBUG_DATA_FDBGDATA_MASK (0xFFFFFFFFU)
#define ENET_QOS_MTL_FIFO_DEBUG_DATA_FDBGDATA_SHIFT (0U)
/*! FDBGDATA - FIFO Debug Data During debug or slave access write operation, this field contains the
 *    data to be written to the Tx FIFO, Rx FIFO, or TSO FIFO.
 */
#define ENET_QOS_MTL_FIFO_DEBUG_DATA_FDBGDATA(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_FIFO_DEBUG_DATA_FDBGDATA_SHIFT)) & ENET_QOS_MTL_FIFO_DEBUG_DATA_FDBGDATA_MASK)
/*! @} */

/*! @name MTL_INTERRUPT_STATUS - MTL Interrupt Status */
/*! @{ */

#define ENET_QOS_MTL_INTERRUPT_STATUS_Q0IS_MASK  (0x1U)
#define ENET_QOS_MTL_INTERRUPT_STATUS_Q0IS_SHIFT (0U)
/*! Q0IS - Queue 0 Interrupt status This bit indicates that there is an interrupt from Queue 0.
 *  0b0..Queue 0 Interrupt status not detected
 *  0b1..Queue 0 Interrupt status detected
 */
#define ENET_QOS_MTL_INTERRUPT_STATUS_Q0IS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_INTERRUPT_STATUS_Q0IS_SHIFT)) & ENET_QOS_MTL_INTERRUPT_STATUS_Q0IS_MASK)

#define ENET_QOS_MTL_INTERRUPT_STATUS_Q1IS_MASK  (0x2U)
#define ENET_QOS_MTL_INTERRUPT_STATUS_Q1IS_SHIFT (1U)
/*! Q1IS - Queue 1 Interrupt status This bit indicates that there is an interrupt from Queue 1.
 *  0b0..Queue 1 Interrupt status not detected
 *  0b1..Queue 1 Interrupt status detected
 */
#define ENET_QOS_MTL_INTERRUPT_STATUS_Q1IS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_INTERRUPT_STATUS_Q1IS_SHIFT)) & ENET_QOS_MTL_INTERRUPT_STATUS_Q1IS_MASK)

#define ENET_QOS_MTL_INTERRUPT_STATUS_Q2IS_MASK  (0x4U)
#define ENET_QOS_MTL_INTERRUPT_STATUS_Q2IS_SHIFT (2U)
/*! Q2IS - Queue 2 Interrupt status This bit indicates that there is an interrupt from Queue 2.
 *  0b0..Queue 2 Interrupt status not detected
 *  0b1..Queue 2 Interrupt status detected
 */
#define ENET_QOS_MTL_INTERRUPT_STATUS_Q2IS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_INTERRUPT_STATUS_Q2IS_SHIFT)) & ENET_QOS_MTL_INTERRUPT_STATUS_Q2IS_MASK)

#define ENET_QOS_MTL_INTERRUPT_STATUS_Q3IS_MASK  (0x8U)
#define ENET_QOS_MTL_INTERRUPT_STATUS_Q3IS_SHIFT (3U)
/*! Q3IS - Queue 3 Interrupt status This bit indicates that there is an interrupt from Queue 3.
 *  0b0..Queue 3 Interrupt status not detected
 *  0b1..Queue 3 Interrupt status detected
 */
#define ENET_QOS_MTL_INTERRUPT_STATUS_Q3IS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_INTERRUPT_STATUS_Q3IS_SHIFT)) & ENET_QOS_MTL_INTERRUPT_STATUS_Q3IS_MASK)

#define ENET_QOS_MTL_INTERRUPT_STATUS_Q4IS_MASK  (0x10U)
#define ENET_QOS_MTL_INTERRUPT_STATUS_Q4IS_SHIFT (4U)
/*! Q4IS - Queue 4 Interrupt status This bit indicates that there is an interrupt from Queue 4.
 *  0b0..Queue 4 Interrupt status not detected
 *  0b1..Queue 4 Interrupt status detected
 */
#define ENET_QOS_MTL_INTERRUPT_STATUS_Q4IS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_INTERRUPT_STATUS_Q4IS_SHIFT)) & ENET_QOS_MTL_INTERRUPT_STATUS_Q4IS_MASK)

#define ENET_QOS_MTL_INTERRUPT_STATUS_DBGIS_MASK (0x20000U)
#define ENET_QOS_MTL_INTERRUPT_STATUS_DBGIS_SHIFT (17U)
/*! DBGIS - Debug Interrupt status This bit indicates an interrupt event during the slave access.
 *  0b0..Debug Interrupt status not detected
 *  0b1..Debug Interrupt status detected
 */
#define ENET_QOS_MTL_INTERRUPT_STATUS_DBGIS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_INTERRUPT_STATUS_DBGIS_SHIFT)) & ENET_QOS_MTL_INTERRUPT_STATUS_DBGIS_MASK)

#define ENET_QOS_MTL_INTERRUPT_STATUS_ESTIS_MASK (0x40000U)
#define ENET_QOS_MTL_INTERRUPT_STATUS_ESTIS_SHIFT (18U)
/*! ESTIS - EST (TAS- 802.
 *  0b0..EST (TAS- 802.1Qbv) Interrupt status not detected
 *  0b1..EST (TAS- 802.1Qbv) Interrupt status detected
 */
#define ENET_QOS_MTL_INTERRUPT_STATUS_ESTIS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_INTERRUPT_STATUS_ESTIS_SHIFT)) & ENET_QOS_MTL_INTERRUPT_STATUS_ESTIS_MASK)

#define ENET_QOS_MTL_INTERRUPT_STATUS_MTLPIS_MASK (0x800000U)
#define ENET_QOS_MTL_INTERRUPT_STATUS_MTLPIS_SHIFT (23U)
/*! MTLPIS - MTL Rx Parser Interrupt Status This bit indicates that there is an interrupt from Rx Parser Block.
 *  0b0..MTL Rx Parser Interrupt status not detected
 *  0b1..MTL Rx Parser Interrupt status detected
 */
#define ENET_QOS_MTL_INTERRUPT_STATUS_MTLPIS(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_INTERRUPT_STATUS_MTLPIS_SHIFT)) & ENET_QOS_MTL_INTERRUPT_STATUS_MTLPIS_MASK)
/*! @} */

/*! @name MTL_RXQ_DMA_MAP0 - Receive Queue and DMA Channel Mapping 0 */
/*! @{ */

#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q0MDMACH_MASK  (0x7U)
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q0MDMACH_SHIFT (0U)
/*! Q0MDMACH - Queue 0 Mapped to DMA Channel This field controls the routing of the packet received
 *    in Queue 0 to the DMA channel: - 000: DMA Channel 0 - 001: DMA Channel 1 - 010: DMA Channel 2
 *    - 011: DMA Channel 3 - 100: DMA Channel 4 - 101: Reserved - 110: Reserved - 111: Reserved This
 *    field is valid when the Q0DDMACH field is reset.
 */
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q0MDMACH(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQ_DMA_MAP0_Q0MDMACH_SHIFT)) & ENET_QOS_MTL_RXQ_DMA_MAP0_Q0MDMACH_MASK)

#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q0DDMACH_MASK  (0x10U)
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q0DDMACH_SHIFT (4U)
/*! Q0DDMACH - Queue 0 Enabled for DA-based DMA Channel Selection When set, this bit indicates that
 *    the packets received in Queue 0 are routed to a particular DMA channel as decided in the MAC
 *    Receiver based on the DMA channel number programmed in the L3-L4 filter registers, or the
 *    Ethernet DA address.
 *  0b0..Queue 0 disabled for DA-based DMA Channel Selection
 *  0b1..Queue 0 enabled for DA-based DMA Channel Selection
 */
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q0DDMACH(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQ_DMA_MAP0_Q0DDMACH_SHIFT)) & ENET_QOS_MTL_RXQ_DMA_MAP0_Q0DDMACH_MASK)

#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q1MDMACH_MASK  (0x700U)
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q1MDMACH_SHIFT (8U)
/*! Q1MDMACH - Queue 1 Mapped to DMA Channel This field controls the routing of the received packet
 *    in Queue 1 to the DMA channel: - 000: DMA Channel 0 - 001: DMA Channel 1 - 010: DMA Channel 2
 *    - 011: DMA Channel 3 - 100: DMA Channel 4 - 101: Reserved - 110: Reserved - 111: Reserved This
 *    field is valid when the Q1DDMACH field is reset.
 */
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q1MDMACH(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQ_DMA_MAP0_Q1MDMACH_SHIFT)) & ENET_QOS_MTL_RXQ_DMA_MAP0_Q1MDMACH_MASK)

#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q1DDMACH_MASK  (0x1000U)
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q1DDMACH_SHIFT (12U)
/*! Q1DDMACH - Queue 1 Enabled for DA-based DMA Channel Selection When set, this bit indicates that
 *    the packets received in Queue 1 are routed to a particular DMA channel as decided in the MAC
 *    Receiver based on the DMA channel number programmed in the L3-L4 filter registers, or the
 *    Ethernet DA address.
 *  0b0..Queue 1 disabled for DA-based DMA Channel Selection
 *  0b1..Queue 1 enabled for DA-based DMA Channel Selection
 */
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q1DDMACH(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQ_DMA_MAP0_Q1DDMACH_SHIFT)) & ENET_QOS_MTL_RXQ_DMA_MAP0_Q1DDMACH_MASK)

#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q2MDMACH_MASK  (0x70000U)
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q2MDMACH_SHIFT (16U)
/*! Q2MDMACH - Queue 2 Mapped to DMA Channel This field controls the routing of the received packet
 *    in Queue 2 to the DMA channel: - 000: DMA Channel 0 - 001: DMA Channel 1 - 010: DMA Channel 2
 *    - 011: DMA Channel 3 - 100: DMA Channel 4 - 101: Reserved - 110: Reserved - 111: Reserved This
 *    field is valid when the Q2DDMACH field is reset.
 */
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q2MDMACH(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQ_DMA_MAP0_Q2MDMACH_SHIFT)) & ENET_QOS_MTL_RXQ_DMA_MAP0_Q2MDMACH_MASK)

#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q2DDMACH_MASK  (0x100000U)
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q2DDMACH_SHIFT (20U)
/*! Q2DDMACH - Queue 2 Enabled for DA-based DMA Channel Selection When set, this bit indicates that
 *    the packets received in Queue 2 are routed to a particular DMA channel as decided in the MAC
 *    Receiver based on the DMA channel number programmed in the L3-L4 filter registers, or the
 *    Ethernet DA address.
 *  0b0..Queue 2 disabled for DA-based DMA Channel Selection
 *  0b1..Queue 2 enabled for DA-based DMA Channel Selection
 */
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q2DDMACH(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQ_DMA_MAP0_Q2DDMACH_SHIFT)) & ENET_QOS_MTL_RXQ_DMA_MAP0_Q2DDMACH_MASK)

#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q3MDMACH_MASK  (0x7000000U)
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q3MDMACH_SHIFT (24U)
/*! Q3MDMACH - Queue 3 Mapped to DMA Channel This field controls the routing of the received packet
 *    in Queue 3 to the DMA channel: - 000: DMA Channel 0 - 001: DMA Channel 1 - 010: DMA Channel 2
 *    - 011: DMA Channel 3 - 100: DMA Channel 4 - 101: Reserved - 110: Reserved - 111: Reserved This
 *    field is valid when the Q3DDMACH field is reset.
 */
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q3MDMACH(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQ_DMA_MAP0_Q3MDMACH_SHIFT)) & ENET_QOS_MTL_RXQ_DMA_MAP0_Q3MDMACH_MASK)

#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q3DDMACH_MASK  (0x10000000U)
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q3DDMACH_SHIFT (28U)
/*! Q3DDMACH - Queue 3 Enabled for Dynamic (per packet) DMA Channel Selection When set, this bit
 *    indicates that the packets received in Queue 3 are routed to a particular DMA channel as decided
 *    in the MAC Receiver based on the DMA channel number programmed in the L3-L4 filter registers,
 *    or the Ethernet DA address.
 *  0b0..Queue 3 disabled for DA-based DMA Channel Selection
 *  0b1..Queue 3 enabled for DA-based DMA Channel Selection
 */
#define ENET_QOS_MTL_RXQ_DMA_MAP0_Q3DDMACH(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQ_DMA_MAP0_Q3DDMACH_SHIFT)) & ENET_QOS_MTL_RXQ_DMA_MAP0_Q3DDMACH_MASK)
/*! @} */

/*! @name MTL_RXQ_DMA_MAP1 - Receive Queue and DMA Channel Mapping 1 */
/*! @{ */

#define ENET_QOS_MTL_RXQ_DMA_MAP1_Q4MDMACH_MASK  (0x7U)
#define ENET_QOS_MTL_RXQ_DMA_MAP1_Q4MDMACH_SHIFT (0U)
/*! Q4MDMACH - Queue 4 Mapped to DMA Channel This field controls the routing of the packet received
 *    in Queue 4 to the DMA channel: - 000: DMA Channel 0 - 001: DMA Channel 1 - 010: DMA Channel 2
 *    - 011: DMA Channel 3 - 100: DMA Channel 4 - 101: Reserved - 110: Reserved - 111: Reserved This
 *    field is valid when the Q4DDMACH field is reset.
 */
#define ENET_QOS_MTL_RXQ_DMA_MAP1_Q4MDMACH(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQ_DMA_MAP1_Q4MDMACH_SHIFT)) & ENET_QOS_MTL_RXQ_DMA_MAP1_Q4MDMACH_MASK)

#define ENET_QOS_MTL_RXQ_DMA_MAP1_Q4DDMACH_MASK  (0x10U)
#define ENET_QOS_MTL_RXQ_DMA_MAP1_Q4DDMACH_SHIFT (4U)
/*! Q4DDMACH - Queue 4 Enabled for DA-based DMA Channel Selection When set, this bit indicates that
 *    the packets received in Queue 4 are routed to a particular DMA channel as decided in the MAC
 *    Receiver based on the DMA channel number programmed in the L3-L4 filter registers, or the
 *    Ethernet DA address.
 *  0b0..Queue 4 disabled for DA-based DMA Channel Selection
 *  0b1..Queue 4 enabled for DA-based DMA Channel Selection
 */
#define ENET_QOS_MTL_RXQ_DMA_MAP1_Q4DDMACH(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQ_DMA_MAP1_Q4DDMACH_SHIFT)) & ENET_QOS_MTL_RXQ_DMA_MAP1_Q4DDMACH_MASK)
/*! @} */

/*! @name MTL_TBS_CTRL - Time Based Scheduling Control */
/*! @{ */

#define ENET_QOS_MTL_TBS_CTRL_ESTM_MASK          (0x1U)
#define ENET_QOS_MTL_TBS_CTRL_ESTM_SHIFT         (0U)
/*! ESTM - EST offset Mode When this bit is set, the Launch Time value used in Time Based Scheduling
 *    is interpreted as an EST offset value and is added to the Base Time Register (BTR) of the
 *    current list.
 *  0b0..EST offset Mode is disabled
 *  0b1..EST offset Mode is enabled
 */
#define ENET_QOS_MTL_TBS_CTRL_ESTM(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TBS_CTRL_ESTM_SHIFT)) & ENET_QOS_MTL_TBS_CTRL_ESTM_MASK)

#define ENET_QOS_MTL_TBS_CTRL_LEOV_MASK          (0x2U)
#define ENET_QOS_MTL_TBS_CTRL_LEOV_SHIFT         (1U)
/*! LEOV - Launch Expiry Offset Valid When set indicates the LEOS field is valid.
 *  0b0..LEOS field is invalid
 *  0b1..LEOS field is valid
 */
#define ENET_QOS_MTL_TBS_CTRL_LEOV(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TBS_CTRL_LEOV_SHIFT)) & ENET_QOS_MTL_TBS_CTRL_LEOV_MASK)

#define ENET_QOS_MTL_TBS_CTRL_LEGOS_MASK         (0x70U)
#define ENET_QOS_MTL_TBS_CTRL_LEGOS_SHIFT        (4U)
/*! LEGOS - Launch Expiry GSN Offset The number GSN slots that has to be added to the Launch GSN to compute the Launch Expiry time. */
#define ENET_QOS_MTL_TBS_CTRL_LEGOS(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TBS_CTRL_LEGOS_SHIFT)) & ENET_QOS_MTL_TBS_CTRL_LEGOS_MASK)

#define ENET_QOS_MTL_TBS_CTRL_LEOS_MASK          (0xFFFFFF00U)
#define ENET_QOS_MTL_TBS_CTRL_LEOS_SHIFT         (8U)
/*! LEOS - Launch Expiry Offset The value in units of 256 nanoseconds that has to be added to the
 *    Launch time to compute the Launch Expiry time.
 */
#define ENET_QOS_MTL_TBS_CTRL_LEOS(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TBS_CTRL_LEOS_SHIFT)) & ENET_QOS_MTL_TBS_CTRL_LEOS_MASK)
/*! @} */

/*! @name MTL_EST_CONTROL - Enhancements to Scheduled Transmission Control */
/*! @{ */

#define ENET_QOS_MTL_EST_CONTROL_EEST_MASK       (0x1U)
#define ENET_QOS_MTL_EST_CONTROL_EEST_SHIFT      (0U)
/*! EEST - Enable EST When reset, the gate control list processing is halted and all gates are assumed to be in Open state.
 *  0b0..EST is disabled
 *  0b1..EST is enabled
 */
#define ENET_QOS_MTL_EST_CONTROL_EEST(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_CONTROL_EEST_SHIFT)) & ENET_QOS_MTL_EST_CONTROL_EEST_MASK)

#define ENET_QOS_MTL_EST_CONTROL_SSWL_MASK       (0x2U)
#define ENET_QOS_MTL_EST_CONTROL_SSWL_SHIFT      (1U)
/*! SSWL - Switch to S/W owned list When set indicates that the software has programmed that list
 *    that it currently owns (SWOL) and the hardware should switch to the new list based on the new
 *    BTR.
 *  0b0..Switch to S/W owned list is disabled
 *  0b1..Switch to S/W owned list is enabled
 */
#define ENET_QOS_MTL_EST_CONTROL_SSWL(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_CONTROL_SSWL_SHIFT)) & ENET_QOS_MTL_EST_CONTROL_SSWL_MASK)

#define ENET_QOS_MTL_EST_CONTROL_DDBF_MASK       (0x10U)
#define ENET_QOS_MTL_EST_CONTROL_DDBF_SHIFT      (4U)
/*! DDBF - Do not Drop frames during Frame Size Error When set, frames are not be dropped during
 *    Head-of-Line blocking due to Frame Size Error (HLBF field of MTL_EST_STATUS register).
 *  0b0..Drop frames during Frame Size Error
 *  0b1..Do not Drop frames during Frame Size Error
 */
#define ENET_QOS_MTL_EST_CONTROL_DDBF(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_CONTROL_DDBF_SHIFT)) & ENET_QOS_MTL_EST_CONTROL_DDBF_MASK)

#define ENET_QOS_MTL_EST_CONTROL_DFBS_MASK       (0x20U)
#define ENET_QOS_MTL_EST_CONTROL_DFBS_SHIFT      (5U)
/*! DFBS - Drop Frames causing Scheduling Error When set frames reported to cause HOL Blocking due
 *    to not getting scheduled (HLBS field of EST_STATUS register) after 4,8,16,32 (based on LCSE
 *    field of this register) GCL iterations are dropped.
 *  0b0..Do not Drop Frames causing Scheduling Error
 *  0b1..Drop Frames causing Scheduling Error
 */
#define ENET_QOS_MTL_EST_CONTROL_DFBS(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_CONTROL_DFBS_SHIFT)) & ENET_QOS_MTL_EST_CONTROL_DFBS_MASK)

#define ENET_QOS_MTL_EST_CONTROL_LCSE_MASK       (0xC0U)
#define ENET_QOS_MTL_EST_CONTROL_LCSE_SHIFT      (6U)
/*! LCSE - Loop Count to report Scheduling Error Programmable number of GCL list iterations before
 *    reporting an HLBS error defined in EST_STATUS register.
 *  0b00..4 iterations
 *  0b01..8 iterations
 *  0b10..16 iterations
 *  0b11..32 iterations
 */
#define ENET_QOS_MTL_EST_CONTROL_LCSE(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_CONTROL_LCSE_SHIFT)) & ENET_QOS_MTL_EST_CONTROL_LCSE_MASK)

#define ENET_QOS_MTL_EST_CONTROL_TILS_MASK       (0x700U)
#define ENET_QOS_MTL_EST_CONTROL_TILS_SHIFT      (8U)
/*! TILS - Time Interval Left Shift Amount This field provides the left shift amount for the
 *    programmed Time Interval values used in the Gate Control Lists.
 */
#define ENET_QOS_MTL_EST_CONTROL_TILS(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_CONTROL_TILS_SHIFT)) & ENET_QOS_MTL_EST_CONTROL_TILS_MASK)

#define ENET_QOS_MTL_EST_CONTROL_CTOV_MASK       (0xFFF000U)
#define ENET_QOS_MTL_EST_CONTROL_CTOV_SHIFT      (12U)
/*! CTOV - Current Time Offset Value Provides a 12 bit time offset value in nano second that is
 *    added to the current time to compensate for all the implementation pipeline delays such as the CDC
 *    sync delay, buffering delays, data path delays etc.
 */
#define ENET_QOS_MTL_EST_CONTROL_CTOV(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_CONTROL_CTOV_SHIFT)) & ENET_QOS_MTL_EST_CONTROL_CTOV_MASK)

#define ENET_QOS_MTL_EST_CONTROL_PTOV_MASK       (0xFF000000U)
#define ENET_QOS_MTL_EST_CONTROL_PTOV_SHIFT      (24U)
/*! PTOV - PTP Time Offset Value The value of PTP Clock period multiplied by 6 in nanoseconds. */
#define ENET_QOS_MTL_EST_CONTROL_PTOV(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_CONTROL_PTOV_SHIFT)) & ENET_QOS_MTL_EST_CONTROL_PTOV_MASK)
/*! @} */

/*! @name MTL_EST_EXT_CONTROL - MTL_EST_EXT_CONTROL */
/*! @{ */

#define ENET_QOS_MTL_EST_EXT_CONTROL_OVHD_MASK   (0x3FU)
#define ENET_QOS_MTL_EST_EXT_CONTROL_OVHD_SHIFT  (0U)
/*! OVHD - Overhead Bytes Value */
#define ENET_QOS_MTL_EST_EXT_CONTROL_OVHD(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_EXT_CONTROL_OVHD_SHIFT)) & ENET_QOS_MTL_EST_EXT_CONTROL_OVHD_MASK)
/*! @} */

/*! @name MTL_EST_STATUS - Enhancements to Scheduled Transmission Status */
/*! @{ */

#define ENET_QOS_MTL_EST_STATUS_SWLC_MASK        (0x1U)
#define ENET_QOS_MTL_EST_STATUS_SWLC_SHIFT       (0U)
/*! SWLC - Switch to S/W owned list Complete When "1" indicates the hardware has successfully
 *    switched to the SWOL, and the SWOL bit has been updated to that effect.
 *  0b0..Switch to S/W owned list Complete not detected
 *  0b1..Switch to S/W owned list Complete detected
 */
#define ENET_QOS_MTL_EST_STATUS_SWLC(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_STATUS_SWLC_SHIFT)) & ENET_QOS_MTL_EST_STATUS_SWLC_MASK)

#define ENET_QOS_MTL_EST_STATUS_BTRE_MASK        (0x2U)
#define ENET_QOS_MTL_EST_STATUS_BTRE_SHIFT       (1U)
/*! BTRE - BTR Error When "1" indicates a programming error in the BTR of SWOL where the programmed
 *    value is less than current time.
 *  0b0..BTR Error not detected
 *  0b1..BTR Error detected
 */
#define ENET_QOS_MTL_EST_STATUS_BTRE(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_STATUS_BTRE_SHIFT)) & ENET_QOS_MTL_EST_STATUS_BTRE_MASK)

#define ENET_QOS_MTL_EST_STATUS_HLBF_MASK        (0x4U)
#define ENET_QOS_MTL_EST_STATUS_HLBF_SHIFT       (2U)
/*! HLBF - Head-Of-Line Blocking due to Frame Size Set when HOL Blocking is noticed on one or more
 *    Queues as a result of none of the Time Intervals of gate open in the GCL being greater than or
 *    equal to the duration needed for frame size (or frame fragment size when preemption is
 *    enabled) transmission.
 *  0b0..Head-Of-Line Blocking due to Frame Size not detected
 *  0b1..Head-Of-Line Blocking due to Frame Size detected
 */
#define ENET_QOS_MTL_EST_STATUS_HLBF(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_STATUS_HLBF_SHIFT)) & ENET_QOS_MTL_EST_STATUS_HLBF_MASK)

#define ENET_QOS_MTL_EST_STATUS_HLBS_MASK        (0x8U)
#define ENET_QOS_MTL_EST_STATUS_HLBS_SHIFT       (3U)
/*! HLBS - Head-Of-Line Blocking due to Scheduling Set when the frame is not able to win arbitration
 *    and get scheduled even after 4 iterations of the GCL.
 *  0b0..Head-Of-Line Blocking due to Scheduling not detected
 *  0b1..Head-Of-Line Blocking due to Scheduling detected
 */
#define ENET_QOS_MTL_EST_STATUS_HLBS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_STATUS_HLBS_SHIFT)) & ENET_QOS_MTL_EST_STATUS_HLBS_MASK)

#define ENET_QOS_MTL_EST_STATUS_CGCE_MASK        (0x10U)
#define ENET_QOS_MTL_EST_STATUS_CGCE_SHIFT       (4U)
/*! CGCE - Constant Gate Control Error This error occurs when the list length (LLR) is 1 and the
 *    programmed Time Interval (TI) value after the optional Left Shifting is less than or equal to the
 *    Cycle Time (CTR).
 *  0b0..Constant Gate Control Error not detected
 *  0b1..Constant Gate Control Error detected
 */
#define ENET_QOS_MTL_EST_STATUS_CGCE(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_STATUS_CGCE_SHIFT)) & ENET_QOS_MTL_EST_STATUS_CGCE_MASK)

#define ENET_QOS_MTL_EST_STATUS_SWOL_MASK        (0x80U)
#define ENET_QOS_MTL_EST_STATUS_SWOL_SHIFT       (7U)
/*! SWOL - S/W owned list When '0' indicates Gate control list number "0" is owned by software and
 *    when "1" indicates the Gate Control list "1" is owned by the software.
 *  0b0..Gate control list number "0" is owned by software
 *  0b1..Gate control list number "1" is owned by software
 */
#define ENET_QOS_MTL_EST_STATUS_SWOL(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_STATUS_SWOL_SHIFT)) & ENET_QOS_MTL_EST_STATUS_SWOL_MASK)

#define ENET_QOS_MTL_EST_STATUS_BTRL_MASK        (0xF00U)
#define ENET_QOS_MTL_EST_STATUS_BTRL_SHIFT       (8U)
/*! BTRL - BTR Error Loop Count Provides the minimum count (N) for which the equation Current Time
 *    =< New BTR + (N * New Cycle Time) becomes true.
 */
#define ENET_QOS_MTL_EST_STATUS_BTRL(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_STATUS_BTRL_SHIFT)) & ENET_QOS_MTL_EST_STATUS_BTRL_MASK)

#define ENET_QOS_MTL_EST_STATUS_CGSN_MASK        (0xF0000U)
#define ENET_QOS_MTL_EST_STATUS_CGSN_SHIFT       (16U)
/*! CGSN - Current GCL Slot Number Indicates the slot number of the GCL list. */
#define ENET_QOS_MTL_EST_STATUS_CGSN(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_STATUS_CGSN_SHIFT)) & ENET_QOS_MTL_EST_STATUS_CGSN_MASK)
/*! @} */

/*! @name MTL_EST_SCH_ERROR - EST Scheduling Error */
/*! @{ */

#define ENET_QOS_MTL_EST_SCH_ERROR_SEQN_MASK     (0x1FU)
#define ENET_QOS_MTL_EST_SCH_ERROR_SEQN_SHIFT    (0U)
/*! SEQN - Schedule Error Queue Number The One Hot Encoded Queue Numbers that have experienced
 *    error/timeout described in HLBS field of status register.
 */
#define ENET_QOS_MTL_EST_SCH_ERROR_SEQN(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_SCH_ERROR_SEQN_SHIFT)) & ENET_QOS_MTL_EST_SCH_ERROR_SEQN_MASK)
/*! @} */

/*! @name MTL_EST_FRM_SIZE_ERROR - EST Frame Size Error */
/*! @{ */

#define ENET_QOS_MTL_EST_FRM_SIZE_ERROR_FEQN_MASK (0x1FU)
#define ENET_QOS_MTL_EST_FRM_SIZE_ERROR_FEQN_SHIFT (0U)
/*! FEQN - Frame Size Error Queue Number The One Hot Encoded Queue Numbers that have experienced
 *    error described in HLBF field of status register.
 */
#define ENET_QOS_MTL_EST_FRM_SIZE_ERROR_FEQN(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_FRM_SIZE_ERROR_FEQN_SHIFT)) & ENET_QOS_MTL_EST_FRM_SIZE_ERROR_FEQN_MASK)
/*! @} */

/*! @name MTL_EST_FRM_SIZE_CAPTURE - EST Frame Size Capture */
/*! @{ */

#define ENET_QOS_MTL_EST_FRM_SIZE_CAPTURE_HBFS_MASK (0x7FFFU)
#define ENET_QOS_MTL_EST_FRM_SIZE_CAPTURE_HBFS_SHIFT (0U)
/*! HBFS - Frame Size of HLBF Captures the Frame Size of the dropped frame related to queue number
 *    indicated in HBFQ field of this register.
 */
#define ENET_QOS_MTL_EST_FRM_SIZE_CAPTURE_HBFS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_FRM_SIZE_CAPTURE_HBFS_SHIFT)) & ENET_QOS_MTL_EST_FRM_SIZE_CAPTURE_HBFS_MASK)

#define ENET_QOS_MTL_EST_FRM_SIZE_CAPTURE_HBFQ_MASK (0x70000U)
#define ENET_QOS_MTL_EST_FRM_SIZE_CAPTURE_HBFQ_SHIFT (16U)
/*! HBFQ - Queue Number of HLBF Captures the binary value of the of the first Queue (number)
 *    experiencing HLBF error (see HLBF field of status register).
 */
#define ENET_QOS_MTL_EST_FRM_SIZE_CAPTURE_HBFQ(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_FRM_SIZE_CAPTURE_HBFQ_SHIFT)) & ENET_QOS_MTL_EST_FRM_SIZE_CAPTURE_HBFQ_MASK)
/*! @} */

/*! @name MTL_EST_INTR_ENABLE - EST Interrupt Enable */
/*! @{ */

#define ENET_QOS_MTL_EST_INTR_ENABLE_IECC_MASK   (0x1U)
#define ENET_QOS_MTL_EST_INTR_ENABLE_IECC_SHIFT  (0U)
/*! IECC - Interrupt Enable for Switch List When set, generates interrupt when the configuration
 *    change is successful and the hardware has switched to the new list.
 *  0b0..Interrupt for Switch List is disabled
 *  0b1..Interrupt for Switch List is enabled
 */
#define ENET_QOS_MTL_EST_INTR_ENABLE_IECC(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_INTR_ENABLE_IECC_SHIFT)) & ENET_QOS_MTL_EST_INTR_ENABLE_IECC_MASK)

#define ENET_QOS_MTL_EST_INTR_ENABLE_IEBE_MASK   (0x2U)
#define ENET_QOS_MTL_EST_INTR_ENABLE_IEBE_SHIFT  (1U)
/*! IEBE - Interrupt Enable for BTR Error When set, generates interrupt when the BTR Error occurs and is indicated in the status.
 *  0b0..Interrupt for BTR Error is disabled
 *  0b1..Interrupt for BTR Error is enabled
 */
#define ENET_QOS_MTL_EST_INTR_ENABLE_IEBE(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_INTR_ENABLE_IEBE_SHIFT)) & ENET_QOS_MTL_EST_INTR_ENABLE_IEBE_MASK)

#define ENET_QOS_MTL_EST_INTR_ENABLE_IEHF_MASK   (0x4U)
#define ENET_QOS_MTL_EST_INTR_ENABLE_IEHF_SHIFT  (2U)
/*! IEHF - Interrupt Enable for HLBF When set, generates interrupt when the Head-of-Line Blocking
 *    due to Frame Size error occurs and is indicated in the status.
 *  0b0..Interrupt for HLBF is disabled
 *  0b1..Interrupt for HLBF is enabled
 */
#define ENET_QOS_MTL_EST_INTR_ENABLE_IEHF(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_INTR_ENABLE_IEHF_SHIFT)) & ENET_QOS_MTL_EST_INTR_ENABLE_IEHF_MASK)

#define ENET_QOS_MTL_EST_INTR_ENABLE_IEHS_MASK   (0x8U)
#define ENET_QOS_MTL_EST_INTR_ENABLE_IEHS_SHIFT  (3U)
/*! IEHS - Interrupt Enable for HLBS When set, generates interrupt when the Head-of-Line Blocking
 *    due to Scheduling issue and is indicated in the status.
 *  0b0..Interrupt for HLBS is disabled
 *  0b1..Interrupt for HLBS is enabled
 */
#define ENET_QOS_MTL_EST_INTR_ENABLE_IEHS(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_INTR_ENABLE_IEHS_SHIFT)) & ENET_QOS_MTL_EST_INTR_ENABLE_IEHS_MASK)

#define ENET_QOS_MTL_EST_INTR_ENABLE_CGCE_MASK   (0x10U)
#define ENET_QOS_MTL_EST_INTR_ENABLE_CGCE_SHIFT  (4U)
/*! CGCE - Interrupt Enable for CGCE When set, generates interrupt when the Constant Gate Control
 *    Error occurs and is indicated in the status.
 *  0b0..Interrupt for CGCE is disabled
 *  0b1..Interrupt for CGCE is enabled
 */
#define ENET_QOS_MTL_EST_INTR_ENABLE_CGCE(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_INTR_ENABLE_CGCE_SHIFT)) & ENET_QOS_MTL_EST_INTR_ENABLE_CGCE_MASK)
/*! @} */

/*! @name MTL_EST_GCL_CONTROL - EST GCL Control */
/*! @{ */

#define ENET_QOS_MTL_EST_GCL_CONTROL_SRWO_MASK   (0x1U)
#define ENET_QOS_MTL_EST_GCL_CONTROL_SRWO_SHIFT  (0U)
/*! SRWO - Start Read/Write Op When set indicates a Read/Write Op has started and is in progress.
 *  0b0..Start Read/Write Op disabled
 *  0b1..Start Read/Write Op enabled
 */
#define ENET_QOS_MTL_EST_GCL_CONTROL_SRWO(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_GCL_CONTROL_SRWO_SHIFT)) & ENET_QOS_MTL_EST_GCL_CONTROL_SRWO_MASK)

#define ENET_QOS_MTL_EST_GCL_CONTROL_R1W0_MASK   (0x2U)
#define ENET_QOS_MTL_EST_GCL_CONTROL_R1W0_SHIFT  (1U)
/*! R1W0 - Read '1', Write '0': When set to '1': Read Operation When set to '0': Write Operation.
 *  0b0..Write Operation
 *  0b1..Read Operation
 */
#define ENET_QOS_MTL_EST_GCL_CONTROL_R1W0(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_GCL_CONTROL_R1W0_SHIFT)) & ENET_QOS_MTL_EST_GCL_CONTROL_R1W0_MASK)

#define ENET_QOS_MTL_EST_GCL_CONTROL_GCRR_MASK   (0x4U)
#define ENET_QOS_MTL_EST_GCL_CONTROL_GCRR_SHIFT  (2U)
/*! GCRR - Gate Control Related Registers When set to "1" indicates the R/W access is for the GCL
 *    related registers (BTR, CTR, TER, LLR) whose address is provided by GCRA.
 *  0b0..Gate Control Related Registers are disabled
 *  0b1..Gate Control Related Registers are enabled
 */
#define ENET_QOS_MTL_EST_GCL_CONTROL_GCRR(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_GCL_CONTROL_GCRR_SHIFT)) & ENET_QOS_MTL_EST_GCL_CONTROL_GCRR_MASK)

#define ENET_QOS_MTL_EST_GCL_CONTROL_DBGM_MASK   (0x10U)
#define ENET_QOS_MTL_EST_GCL_CONTROL_DBGM_SHIFT  (4U)
/*! DBGM - Debug Mode When set to "1" indicates R/W in debug mode where the memory bank (for GCL and
 *    Time related registers) is explicitly provided by DBGB value, when set to "0" SWOL bit is
 *    used to determine which bank to use.
 *  0b0..Debug Mode is disabled
 *  0b1..Debug Mode is enabled
 */
#define ENET_QOS_MTL_EST_GCL_CONTROL_DBGM(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_GCL_CONTROL_DBGM_SHIFT)) & ENET_QOS_MTL_EST_GCL_CONTROL_DBGM_MASK)

#define ENET_QOS_MTL_EST_GCL_CONTROL_DBGB_MASK   (0x20U)
#define ENET_QOS_MTL_EST_GCL_CONTROL_DBGB_SHIFT  (5U)
/*! DBGB - Debug Mode Bank Select When set to "0" indicates R/W in debug mode should be directed to
 *    Bank 0 (GCL0 and corresponding Time related registers).
 *  0b0..R/W in debug mode should be directed to Bank 0
 *  0b1..R/W in debug mode should be directed to Bank 1
 */
#define ENET_QOS_MTL_EST_GCL_CONTROL_DBGB(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_GCL_CONTROL_DBGB_SHIFT)) & ENET_QOS_MTL_EST_GCL_CONTROL_DBGB_MASK)

#define ENET_QOS_MTL_EST_GCL_CONTROL_ADDR_MASK   (0x1FF00U)
#define ENET_QOS_MTL_EST_GCL_CONTROL_ADDR_SHIFT  (8U)
/*! ADDR - Gate Control List Address: (GCLA when GCRR is "0"). */
#define ENET_QOS_MTL_EST_GCL_CONTROL_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_GCL_CONTROL_ADDR_SHIFT)) & ENET_QOS_MTL_EST_GCL_CONTROL_ADDR_MASK)

#define ENET_QOS_MTL_EST_GCL_CONTROL_ERR0_MASK   (0x100000U)
#define ENET_QOS_MTL_EST_GCL_CONTROL_ERR0_SHIFT  (20U)
/*! ERR0 - When set indicates the last write operation was aborted as software writes to GCL and GCL
 *    registers is prohibited when SSWL bit of MTL_EST_CONTROL Register is set.
 *  0b0..ERR0 is disabled
 *  0b1..ERR1 is enabled
 */
#define ENET_QOS_MTL_EST_GCL_CONTROL_ERR0(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_GCL_CONTROL_ERR0_SHIFT)) & ENET_QOS_MTL_EST_GCL_CONTROL_ERR0_MASK)

#define ENET_QOS_MTL_EST_GCL_CONTROL_ESTEIEE_MASK (0x200000U)
#define ENET_QOS_MTL_EST_GCL_CONTROL_ESTEIEE_SHIFT (21U)
/*! ESTEIEE - EST ECC Inject Error Enable When set along with EEST bit of MTL_EST_CONTROL register,
 *    enables the ECC error injection feature.
 *  0b0..EST ECC Inject Error is disabled
 *  0b1..EST ECC Inject Error is enabled
 */
#define ENET_QOS_MTL_EST_GCL_CONTROL_ESTEIEE(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_GCL_CONTROL_ESTEIEE_SHIFT)) & ENET_QOS_MTL_EST_GCL_CONTROL_ESTEIEE_MASK)

#define ENET_QOS_MTL_EST_GCL_CONTROL_ESTEIEC_MASK (0xC00000U)
#define ENET_QOS_MTL_EST_GCL_CONTROL_ESTEIEC_SHIFT (22U)
/*! ESTEIEC - ECC Inject Error Control for EST Memory When EIEE bit of this register is set,
 *    following are the errors inserted based on the value encoded in this field.
 *  0b00..Insert 1 bit error
 *  0b01..Insert 2 bit errors
 *  0b10..Insert 3 bit errors
 *  0b11..Insert 1 bit error in address field
 */
#define ENET_QOS_MTL_EST_GCL_CONTROL_ESTEIEC(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_GCL_CONTROL_ESTEIEC_SHIFT)) & ENET_QOS_MTL_EST_GCL_CONTROL_ESTEIEC_MASK)
/*! @} */

/*! @name MTL_EST_GCL_DATA - EST GCL Data */
/*! @{ */

#define ENET_QOS_MTL_EST_GCL_DATA_GCD_MASK       (0xFFFFFFFFU)
#define ENET_QOS_MTL_EST_GCL_DATA_GCD_SHIFT      (0U)
/*! GCD - Gate Control Data The data corresponding to the address selected in the MTL_GCL_CONTROL register. */
#define ENET_QOS_MTL_EST_GCL_DATA_GCD(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_EST_GCL_DATA_GCD_SHIFT)) & ENET_QOS_MTL_EST_GCL_DATA_GCD_MASK)
/*! @} */

/*! @name MTL_FPE_CTRL_STS - Frame Preemption Control and Status */
/*! @{ */

#define ENET_QOS_MTL_FPE_CTRL_STS_AFSZ_MASK      (0x3U)
#define ENET_QOS_MTL_FPE_CTRL_STS_AFSZ_SHIFT     (0U)
/*! AFSZ - Additional Fragment Size used to indicate, in units of 64 bytes, the minimum number of
 *    bytes over 64 bytes required in non-final fragments of preempted frames.
 */
#define ENET_QOS_MTL_FPE_CTRL_STS_AFSZ(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_FPE_CTRL_STS_AFSZ_SHIFT)) & ENET_QOS_MTL_FPE_CTRL_STS_AFSZ_MASK)

#define ENET_QOS_MTL_FPE_CTRL_STS_PEC_MASK       (0x1F00U)
#define ENET_QOS_MTL_FPE_CTRL_STS_PEC_SHIFT      (8U)
/*! PEC - Preemption Classification When set indicates the corresponding Queue must be classified as
 *    preemptable, when '0' Queue is classified as express.
 */
#define ENET_QOS_MTL_FPE_CTRL_STS_PEC(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_FPE_CTRL_STS_PEC_SHIFT)) & ENET_QOS_MTL_FPE_CTRL_STS_PEC_MASK)

#define ENET_QOS_MTL_FPE_CTRL_STS_HRS_MASK       (0x10000000U)
#define ENET_QOS_MTL_FPE_CTRL_STS_HRS_SHIFT      (28U)
/*! HRS - Hold/Release Status - 1: Indicates a Set-and-Hold-MAC operation was last executed and the pMAC is in Hold State.
 *  0b0..Indicates a Set-and-Release-MAC operation was last executed and the pMAC is in Release State
 *  0b1..Indicates a Set-and-Hold-MAC operation was last executed and the pMAC is in Hold State
 */
#define ENET_QOS_MTL_FPE_CTRL_STS_HRS(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_FPE_CTRL_STS_HRS_SHIFT)) & ENET_QOS_MTL_FPE_CTRL_STS_HRS_MASK)
/*! @} */

/*! @name MTL_FPE_ADVANCE - Frame Preemption Hold and Release Advance */
/*! @{ */

#define ENET_QOS_MTL_FPE_ADVANCE_HADV_MASK       (0xFFFFU)
#define ENET_QOS_MTL_FPE_ADVANCE_HADV_SHIFT      (0U)
/*! HADV - Hold Advance The maximum time in nanoseconds that can elapse between issuing a HOLD to
 *    the MAC and the MAC ceasing to transmit any preemptable frame that is in the process of
 *    transmission or any preemptable frames that are queued for transmission.
 */
#define ENET_QOS_MTL_FPE_ADVANCE_HADV(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_FPE_ADVANCE_HADV_SHIFT)) & ENET_QOS_MTL_FPE_ADVANCE_HADV_MASK)

#define ENET_QOS_MTL_FPE_ADVANCE_RADV_MASK       (0xFFFF0000U)
#define ENET_QOS_MTL_FPE_ADVANCE_RADV_SHIFT      (16U)
/*! RADV - Release Advance The maximum time in nanoseconds that can elapse between issuing a RELEASE
 *    to the MAC and the MAC being ready to resume transmission of preemptable frames, in the
 *    absence of there being any express frames available for transmission.
 */
#define ENET_QOS_MTL_FPE_ADVANCE_RADV(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_FPE_ADVANCE_RADV_SHIFT)) & ENET_QOS_MTL_FPE_ADVANCE_RADV_MASK)
/*! @} */

/*! @name MTL_RXP_CONTROL_STATUS - RXP Control Status */
/*! @{ */

#define ENET_QOS_MTL_RXP_CONTROL_STATUS_NVE_MASK (0xFFU)
#define ENET_QOS_MTL_RXP_CONTROL_STATUS_NVE_SHIFT (0U)
/*! NVE - Number of valid entries in the Instruction table This control indicates the number of
 *    valid entries in the Instruction Memory.
 */
#define ENET_QOS_MTL_RXP_CONTROL_STATUS_NVE(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_CONTROL_STATUS_NVE_SHIFT)) & ENET_QOS_MTL_RXP_CONTROL_STATUS_NVE_MASK)

#define ENET_QOS_MTL_RXP_CONTROL_STATUS_NPE_MASK (0xFF0000U)
#define ENET_QOS_MTL_RXP_CONTROL_STATUS_NPE_SHIFT (16U)
/*! NPE - Number of parsable entries in the Instruction table This control indicates the number of
 *    parsable entries in the Instruction Memory.
 */
#define ENET_QOS_MTL_RXP_CONTROL_STATUS_NPE(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_CONTROL_STATUS_NPE_SHIFT)) & ENET_QOS_MTL_RXP_CONTROL_STATUS_NPE_MASK)

#define ENET_QOS_MTL_RXP_CONTROL_STATUS_RXPI_MASK (0x80000000U)
#define ENET_QOS_MTL_RXP_CONTROL_STATUS_RXPI_SHIFT (31U)
/*! RXPI - RX Parser in Idle state This status bit is set to 1 when the Rx parser is in Idle State
 *    and waiting for a new packet for processing.
 *  0b0..RX Parser not in Idle state
 *  0b1..RX Parser in Idle state
 */
#define ENET_QOS_MTL_RXP_CONTROL_STATUS_RXPI(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_CONTROL_STATUS_RXPI_SHIFT)) & ENET_QOS_MTL_RXP_CONTROL_STATUS_RXPI_MASK)
/*! @} */

/*! @name MTL_RXP_INTERRUPT_CONTROL_STATUS - RXP Interrupt Control Status */
/*! @{ */

#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NVEOVIS_MASK (0x1U)
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NVEOVIS_SHIFT (0U)
/*! NVEOVIS - Number of Valid Entries Overflow Interrupt Status While parsing if the Instruction
 *    address found to be more than NVE (Number of Valid Entries in MTL_RXP_CONTROL register), then
 *    this bit is set to 1.
 *  0b0..Number of Valid Entries Overflow Interrupt Status not detected
 *  0b1..Number of Valid Entries Overflow Interrupt Status detected
 */
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NVEOVIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NVEOVIS_SHIFT)) & ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NVEOVIS_MASK)

#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NPEOVIS_MASK (0x2U)
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NPEOVIS_SHIFT (1U)
/*! NPEOVIS - Number of Parsable Entries Overflow Interrupt Status While parsing a packet if the
 *    number of parsed entries found to be more than NPE[] (Number of Parseable Entries in
 *    MTL_RXP_CONTROL register),then this bit is set to 1.
 *  0b0..Number of Parsable Entries Overflow Interrupt Status not detected
 *  0b1..Number of Parsable Entries Overflow Interrupt Status detected
 */
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NPEOVIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NPEOVIS_SHIFT)) & ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NPEOVIS_MASK)

#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_FOOVIS_MASK (0x4U)
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_FOOVIS_SHIFT (2U)
/*! FOOVIS - Frame Offset Overflow Interrupt Status While parsing if the Instruction table entry's
 *    'Frame Offset' found to be more than EOF offset, then then this bit is set.
 *  0b0..Frame Offset Overflow Interrupt Status not detected
 *  0b1..Frame Offset Overflow Interrupt Status detected
 */
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_FOOVIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_FOOVIS_SHIFT)) & ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_FOOVIS_MASK)

#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_PDRFIS_MASK (0x8U)
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_PDRFIS_SHIFT (3U)
/*! PDRFIS - Packet Dropped due to RF Interrupt Status If the Rx Parser result says to drop the
 *    packet by setting RF=1 in the instruction memory, then this bit is set to 1.
 *  0b0..Packet Dropped due to RF Interrupt Status not detected
 *  0b1..Packet Dropped due to RF Interrupt Status detected
 */
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_PDRFIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_PDRFIS_SHIFT)) & ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_PDRFIS_MASK)

#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NVEOVIE_MASK (0x10000U)
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NVEOVIE_SHIFT (16U)
/*! NVEOVIE - Number of Valid Entries Overflow Interrupt Enable When this bit is set, the NVEOVIS interrupt is enabled.
 *  0b0..Number of Valid Entries Overflow Interrupt is disabled
 *  0b1..Number of Valid Entries Overflow Interrupt is enabled
 */
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NVEOVIE(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NVEOVIE_SHIFT)) & ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NVEOVIE_MASK)

#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NPEOVIE_MASK (0x20000U)
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NPEOVIE_SHIFT (17U)
/*! NPEOVIE - Number of Parsable Entries Overflow Interrupt Enable When this bit is set, the NPEOVIS interrupt is enabled.
 *  0b0..Number of Parsable Entries Overflow Interrupt is disabled
 *  0b1..Number of Parsable Entries Overflow Interrupt is enabled
 */
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NPEOVIE(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NPEOVIE_SHIFT)) & ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_NPEOVIE_MASK)

#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_FOOVIE_MASK (0x40000U)
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_FOOVIE_SHIFT (18U)
/*! FOOVIE - Frame Offset Overflow Interrupt Enable When this bit is set, the FOOVIS interrupt is enabled.
 *  0b0..Frame Offset Overflow Interrupt is disabled
 *  0b1..Frame Offset Overflow Interrupt is enabled
 */
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_FOOVIE(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_FOOVIE_SHIFT)) & ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_FOOVIE_MASK)

#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_PDRFIE_MASK (0x80000U)
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_PDRFIE_SHIFT (19U)
/*! PDRFIE - Packet Drop due to RF Interrupt Enable When this bit is set, the PDRFIS interrupt is enabled.
 *  0b0..Packet Drop due to RF Interrupt is disabled
 *  0b1..Packet Drop due to RF Interrupt is enabled
 */
#define ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_PDRFIE(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_PDRFIE_SHIFT)) & ENET_QOS_MTL_RXP_INTERRUPT_CONTROL_STATUS_PDRFIE_MASK)
/*! @} */

/*! @name MTL_RXP_DROP_CNT - RXP Drop Count */
/*! @{ */

#define ENET_QOS_MTL_RXP_DROP_CNT_RXPDC_MASK     (0x7FFFFFFFU)
#define ENET_QOS_MTL_RXP_DROP_CNT_RXPDC_SHIFT    (0U)
/*! RXPDC - Rx Parser Drop count This 31-bit counter is implemented whenever a Rx Parser Drops a packet due to RF =1. */
#define ENET_QOS_MTL_RXP_DROP_CNT_RXPDC(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_DROP_CNT_RXPDC_SHIFT)) & ENET_QOS_MTL_RXP_DROP_CNT_RXPDC_MASK)

#define ENET_QOS_MTL_RXP_DROP_CNT_RXPDCOVF_MASK  (0x80000000U)
#define ENET_QOS_MTL_RXP_DROP_CNT_RXPDCOVF_SHIFT (31U)
/*! RXPDCOVF - Rx Parser Drop Counter Overflow Bit When set, this bit indicates that the
 *    MTL_RXP_DROP_CNT (RXPDC) Counter field crossed the maximum limit.
 *  0b0..Rx Parser Drop count overflow not occurred
 *  0b1..Rx Parser Drop count overflow occurred
 */
#define ENET_QOS_MTL_RXP_DROP_CNT_RXPDCOVF(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_DROP_CNT_RXPDCOVF_SHIFT)) & ENET_QOS_MTL_RXP_DROP_CNT_RXPDCOVF_MASK)
/*! @} */

/*! @name MTL_RXP_ERROR_CNT - RXP Error Count */
/*! @{ */

#define ENET_QOS_MTL_RXP_ERROR_CNT_RXPEC_MASK    (0x7FFFFFFFU)
#define ENET_QOS_MTL_RXP_ERROR_CNT_RXPEC_SHIFT   (0U)
/*! RXPEC - Rx Parser Error count This 31-bit counter is implemented whenever a Rx Parser encounters
 *    following Error scenarios - Entry address >= NVE[] - Number Parsed Entries >= NPE[] - Entry
 *    address > EOF data entry address The counter is cleared when the register is read.
 */
#define ENET_QOS_MTL_RXP_ERROR_CNT_RXPEC(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_ERROR_CNT_RXPEC_SHIFT)) & ENET_QOS_MTL_RXP_ERROR_CNT_RXPEC_MASK)

#define ENET_QOS_MTL_RXP_ERROR_CNT_RXPECOVF_MASK (0x80000000U)
#define ENET_QOS_MTL_RXP_ERROR_CNT_RXPECOVF_SHIFT (31U)
/*! RXPECOVF - Rx Parser Error Counter Overflow Bit When set, this bit indicates that the
 *    MTL_RXP_ERROR_CNT (RXPEC) Counter field crossed the maximum limit.
 *  0b0..Rx Parser Error count overflow not occurred
 *  0b1..Rx Parser Error count overflow occurred
 */
#define ENET_QOS_MTL_RXP_ERROR_CNT_RXPECOVF(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_ERROR_CNT_RXPECOVF_SHIFT)) & ENET_QOS_MTL_RXP_ERROR_CNT_RXPECOVF_MASK)
/*! @} */

/*! @name MTL_RXP_INDIRECT_ACC_CONTROL_STATUS - RXP Indirect Access Control and Status */
/*! @{ */

#define ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_ADDR_MASK (0x3FFU)
#define ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_ADDR_SHIFT (0U)
/*! ADDR - FRP Instruction Table Offset Address This field indicates the ADDR of the 32-bit entry in Rx parser instruction table. */
#define ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_ADDR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_ADDR_SHIFT)) & ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_ADDR_MASK)

#define ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_WRRDN_MASK (0x10000U)
#define ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_WRRDN_SHIFT (16U)
/*! WRRDN - Read Write Control When this bit is set to 1 indicates the write operation to the Rx Parser Memory.
 *  0b0..Read operation to the Rx Parser Memory
 *  0b1..Write operation to the Rx Parser Memory
 */
#define ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_WRRDN(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_WRRDN_SHIFT)) & ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_WRRDN_MASK)

#define ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY_MASK (0x80000000U)
#define ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY_SHIFT (31U)
/*! STARTBUSY - FRP Instruction Table Access Busy When this bit is set to 1 by the software then it
 *    indicates to start the Read/Write operation from/to the Rx Parser Memory.
 *  0b0..hardware not busy
 *  0b1..hardware is busy (Read/Write operation from/to the Rx Parser Memory)
 */
#define ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY_SHIFT)) & ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY_MASK)
/*! @} */

/*! @name MTL_RXP_INDIRECT_ACC_DATA - RXP Indirect Access Data */
/*! @{ */

#define ENET_QOS_MTL_RXP_INDIRECT_ACC_DATA_DATA_MASK (0xFFFFFFFFU)
#define ENET_QOS_MTL_RXP_INDIRECT_ACC_DATA_DATA_SHIFT (0U)
/*! DATA - FRP Instruction Table Write/Read Data Software should write this register before issuing any write command. */
#define ENET_QOS_MTL_RXP_INDIRECT_ACC_DATA_DATA(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_INDIRECT_ACC_DATA_DATA_SHIFT)) & ENET_QOS_MTL_RXP_INDIRECT_ACC_DATA_DATA_MASK)
/*! @} */

/*! @name MTL_RXP_BYPASS_CNT - MTL_RXP_BYPASS_CNT */
/*! @{ */

#define ENET_QOS_MTL_RXP_BYPASS_CNT_RXPBC_MASK   (0x7FFFFFFFU)
#define ENET_QOS_MTL_RXP_BYPASS_CNT_RXPBC_SHIFT  (0U)
/*! RXPBC - Rx Parser Bypass Count */
#define ENET_QOS_MTL_RXP_BYPASS_CNT_RXPBC(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_BYPASS_CNT_RXPBC_SHIFT)) & ENET_QOS_MTL_RXP_BYPASS_CNT_RXPBC_MASK)

#define ENET_QOS_MTL_RXP_BYPASS_CNT_RXPBCOF_MASK (0x80000000U)
#define ENET_QOS_MTL_RXP_BYPASS_CNT_RXPBCOF_SHIFT (31U)
/*! RXPBCOF - Rx Parser bypass Counter Overflow Bit. Access restriction applies. Clears on read. Self-set to 1 on internal event.
 *  0b0..Indicates that MTL_RXP_BYPASS_CNT[RXPBC] counter field has not crossed the maximum limit
 *  0b1..Indicates that MTL_RXP_BYPASS_CNT[RXPBC] counter field has crossed the maximum limit
 */
#define ENET_QOS_MTL_RXP_BYPASS_CNT_RXPBCOF(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXP_BYPASS_CNT_RXPBCOF_SHIFT)) & ENET_QOS_MTL_RXP_BYPASS_CNT_RXPBCOF_MASK)
/*! @} */

/*! @name MTL_TXQX_OP_MODE - Queue 0 Transmit Operation Mode..Queue 4 Transmit Operation Mode */
/*! @{ */

#define ENET_QOS_MTL_TXQX_OP_MODE_FTQ_MASK       (0x1U)
#define ENET_QOS_MTL_TXQX_OP_MODE_FTQ_SHIFT      (0U)
/*! FTQ - Flush Transmit Queue When this bit is set, the Tx queue controller logic is reset to its default values.
 *  0b0..Flush Transmit Queue is disabled
 *  0b1..Flush Transmit Queue is enabled
 */
#define ENET_QOS_MTL_TXQX_OP_MODE_FTQ(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_OP_MODE_FTQ_SHIFT)) & ENET_QOS_MTL_TXQX_OP_MODE_FTQ_MASK)

#define ENET_QOS_MTL_TXQX_OP_MODE_TSF_MASK       (0x2U)
#define ENET_QOS_MTL_TXQX_OP_MODE_TSF_SHIFT      (1U)
/*! TSF - Transmit Store and Forward When this bit is set, the transmission starts when a full packet resides in the MTL Tx queue.
 *  0b0..Transmit Store and Forward is disabled
 *  0b1..Transmit Store and Forward is enabled
 */
#define ENET_QOS_MTL_TXQX_OP_MODE_TSF(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_OP_MODE_TSF_SHIFT)) & ENET_QOS_MTL_TXQX_OP_MODE_TSF_MASK)

#define ENET_QOS_MTL_TXQX_OP_MODE_TXQEN_MASK     (0xCU)
#define ENET_QOS_MTL_TXQX_OP_MODE_TXQEN_SHIFT    (2U)
/*! TXQEN - Transmit Queue Enable This field is used to enable/disable the transmit queue 0.
 *  0b00..Not enabled
 *  0b01..Enable in AV mode (Reserved in non-AV)
 *  0b10..Enabled
 *  0b11..Reserved
 */
#define ENET_QOS_MTL_TXQX_OP_MODE_TXQEN(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_OP_MODE_TXQEN_SHIFT)) & ENET_QOS_MTL_TXQX_OP_MODE_TXQEN_MASK)

#define ENET_QOS_MTL_TXQX_OP_MODE_TTC_MASK       (0x70U)
#define ENET_QOS_MTL_TXQX_OP_MODE_TTC_SHIFT      (4U)
/*! TTC - Transmit Threshold Control These bits control the threshold level of the MTL Tx Queue.
 *  0b000..32
 *  0b001..64
 *  0b010..96
 *  0b011..128
 *  0b100..192
 *  0b101..256
 *  0b110..384
 *  0b111..512
 */
#define ENET_QOS_MTL_TXQX_OP_MODE_TTC(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_OP_MODE_TTC_SHIFT)) & ENET_QOS_MTL_TXQX_OP_MODE_TTC_MASK)

#define ENET_QOS_MTL_TXQX_OP_MODE_TQS_MASK       (0x1F0000U)
#define ENET_QOS_MTL_TXQX_OP_MODE_TQS_SHIFT      (16U)
/*! TQS - Transmit Queue Size This field indicates the size of the allocated Transmit queues in blocks of 256 bytes. */
#define ENET_QOS_MTL_TXQX_OP_MODE_TQS(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_OP_MODE_TQS_SHIFT)) & ENET_QOS_MTL_TXQX_OP_MODE_TQS_MASK)
/*! @} */

/* The count of ENET_QOS_MTL_TXQX_OP_MODE */
#define ENET_QOS_MTL_TXQX_OP_MODE_COUNT          (5U)

/*! @name MTL_TXQX_UNDRFLW - Queue 0 Underflow Counter..Queue 4 Underflow Counter */
/*! @{ */

#define ENET_QOS_MTL_TXQX_UNDRFLW_UFFRMCNT_MASK  (0x7FFU)
#define ENET_QOS_MTL_TXQX_UNDRFLW_UFFRMCNT_SHIFT (0U)
/*! UFFRMCNT - Underflow Packet Counter This field indicates the number of packets aborted by the
 *    controller because of Tx Queue Underflow.
 */
#define ENET_QOS_MTL_TXQX_UNDRFLW_UFFRMCNT(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_UNDRFLW_UFFRMCNT_SHIFT)) & ENET_QOS_MTL_TXQX_UNDRFLW_UFFRMCNT_MASK)

#define ENET_QOS_MTL_TXQX_UNDRFLW_UFCNTOVF_MASK  (0x800U)
#define ENET_QOS_MTL_TXQX_UNDRFLW_UFCNTOVF_SHIFT (11U)
/*! UFCNTOVF - Overflow Bit for Underflow Packet Counter This bit is set every time the Tx queue
 *    Underflow Packet Counter field overflows, that is, it has crossed the maximum count.
 *  0b0..Overflow not detected for Underflow Packet Counter
 *  0b1..Overflow detected for Underflow Packet Counter
 */
#define ENET_QOS_MTL_TXQX_UNDRFLW_UFCNTOVF(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_UNDRFLW_UFCNTOVF_SHIFT)) & ENET_QOS_MTL_TXQX_UNDRFLW_UFCNTOVF_MASK)
/*! @} */

/* The count of ENET_QOS_MTL_TXQX_UNDRFLW */
#define ENET_QOS_MTL_TXQX_UNDRFLW_COUNT          (5U)

/*! @name MTL_TXQX_DBG - Queue 0 Transmit Debug..Queue 4 Transmit Debug */
/*! @{ */

#define ENET_QOS_MTL_TXQX_DBG_TXQPAUSED_MASK     (0x1U)
#define ENET_QOS_MTL_TXQX_DBG_TXQPAUSED_SHIFT    (0U)
/*! TXQPAUSED - Transmit Queue in Pause When this bit is high and the Rx flow control is enabled, it
 *    indicates that the Tx Queue is in the Pause condition (in the full-duplex only mode) because
 *    of the following: - Reception of the PFC packet for the priorities assigned to the Tx Queue
 *    when PFC is enabled - Reception of 802.
 *  0b0..Transmit Queue in Pause status is not detected
 *  0b1..Transmit Queue in Pause status is detected
 */
#define ENET_QOS_MTL_TXQX_DBG_TXQPAUSED(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_DBG_TXQPAUSED_SHIFT)) & ENET_QOS_MTL_TXQX_DBG_TXQPAUSED_MASK)

#define ENET_QOS_MTL_TXQX_DBG_TRCSTS_MASK        (0x6U)
#define ENET_QOS_MTL_TXQX_DBG_TRCSTS_SHIFT       (1U)
/*! TRCSTS - MTL Tx Queue Read Controller Status This field indicates the state of the Tx Queue Read Controller:
 *  0b00..Idle state
 *  0b01..Read state (transferring data to the MAC transmitter)
 *  0b10..Waiting for pending Tx Status from the MAC transmitter
 *  0b11..Flushing the Tx queue because of the Packet Abort request from the MAC
 */
#define ENET_QOS_MTL_TXQX_DBG_TRCSTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_DBG_TRCSTS_SHIFT)) & ENET_QOS_MTL_TXQX_DBG_TRCSTS_MASK)

#define ENET_QOS_MTL_TXQX_DBG_TWCSTS_MASK        (0x8U)
#define ENET_QOS_MTL_TXQX_DBG_TWCSTS_SHIFT       (3U)
/*! TWCSTS - MTL Tx Queue Write Controller Status When high, this bit indicates that the MTL Tx
 *    Queue Write Controller is active, and it is transferring the data to the Tx Queue.
 *  0b0..MTL Tx Queue Write Controller status is not detected
 *  0b1..MTL Tx Queue Write Controller status is detected
 */
#define ENET_QOS_MTL_TXQX_DBG_TWCSTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_DBG_TWCSTS_SHIFT)) & ENET_QOS_MTL_TXQX_DBG_TWCSTS_MASK)

#define ENET_QOS_MTL_TXQX_DBG_TXQSTS_MASK        (0x10U)
#define ENET_QOS_MTL_TXQX_DBG_TXQSTS_SHIFT       (4U)
/*! TXQSTS - MTL Tx Queue Not Empty Status When this bit is high, it indicates that the MTL Tx Queue
 *    is not empty and some data is left for transmission.
 *  0b0..MTL Tx Queue Not Empty status is not detected
 *  0b1..MTL Tx Queue Not Empty status is detected
 */
#define ENET_QOS_MTL_TXQX_DBG_TXQSTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_DBG_TXQSTS_SHIFT)) & ENET_QOS_MTL_TXQX_DBG_TXQSTS_MASK)

#define ENET_QOS_MTL_TXQX_DBG_TXSTSFSTS_MASK     (0x20U)
#define ENET_QOS_MTL_TXQX_DBG_TXSTSFSTS_SHIFT    (5U)
/*! TXSTSFSTS - MTL Tx Status FIFO Full Status When high, this bit indicates that the MTL Tx Status FIFO is full.
 *  0b0..MTL Tx Status FIFO Full status is not detected
 *  0b1..MTL Tx Status FIFO Full status is detected
 */
#define ENET_QOS_MTL_TXQX_DBG_TXSTSFSTS(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_DBG_TXSTSFSTS_SHIFT)) & ENET_QOS_MTL_TXQX_DBG_TXSTSFSTS_MASK)

#define ENET_QOS_MTL_TXQX_DBG_PTXQ_MASK          (0x70000U)
#define ENET_QOS_MTL_TXQX_DBG_PTXQ_SHIFT         (16U)
/*! PTXQ - Number of Packets in the Transmit Queue This field indicates the current number of packets in the Tx Queue. */
#define ENET_QOS_MTL_TXQX_DBG_PTXQ(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_DBG_PTXQ_SHIFT)) & ENET_QOS_MTL_TXQX_DBG_PTXQ_MASK)

#define ENET_QOS_MTL_TXQX_DBG_STXSTSF_MASK       (0x700000U)
#define ENET_QOS_MTL_TXQX_DBG_STXSTSF_SHIFT      (20U)
/*! STXSTSF - Number of Status Words in Tx Status FIFO of Queue This field indicates the current
 *    number of status in the Tx Status FIFO of this queue.
 */
#define ENET_QOS_MTL_TXQX_DBG_STXSTSF(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_DBG_STXSTSF_SHIFT)) & ENET_QOS_MTL_TXQX_DBG_STXSTSF_MASK)
/*! @} */

/* The count of ENET_QOS_MTL_TXQX_DBG */
#define ENET_QOS_MTL_TXQX_DBG_COUNT              (5U)

/*! @name MTL_TXQX_ETS_CTRL - Queue 1 ETS Control..Queue 4 ETS Control */
/*! @{ */

#define ENET_QOS_MTL_TXQX_ETS_CTRL_AVALG_MASK    (0x4U)
#define ENET_QOS_MTL_TXQX_ETS_CTRL_AVALG_SHIFT   (2U)
/*! AVALG - AV Algorithm When Queue 4 is programmed for AV, this field configures the scheduling
 *    algorithm for this queue: This bit when set, indicates credit based shaper algorithm (CBS) is
 *    selected for Queue 4 traffic.
 *  0b0..CBS Algorithm is disabled
 *  0b1..CBS Algorithm is enabled
 */
#define ENET_QOS_MTL_TXQX_ETS_CTRL_AVALG(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_ETS_CTRL_AVALG_SHIFT)) & ENET_QOS_MTL_TXQX_ETS_CTRL_AVALG_MASK)

#define ENET_QOS_MTL_TXQX_ETS_CTRL_CC_MASK       (0x8U)
#define ENET_QOS_MTL_TXQX_ETS_CTRL_CC_SHIFT      (3U)
/*! CC - Credit Control When this bit is set, the accumulated credit parameter in the credit-based
 *    shaper algorithm logic is not reset to zero when there is positive credit and no packet to
 *    transmit in Channel 4.
 *  0b0..Credit Control is disabled
 *  0b1..Credit Control is enabled
 */
#define ENET_QOS_MTL_TXQX_ETS_CTRL_CC(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_ETS_CTRL_CC_SHIFT)) & ENET_QOS_MTL_TXQX_ETS_CTRL_CC_MASK)

#define ENET_QOS_MTL_TXQX_ETS_CTRL_SLC_MASK      (0x70U)
#define ENET_QOS_MTL_TXQX_ETS_CTRL_SLC_SHIFT     (4U)
/*! SLC - Slot Count
 *  0b000..1 slot
 *  0b001..2 slots
 *  0b010..4 slots
 *  0b011..8 slots
 *  0b100..16 slots
 *  0b101..Reserved
 */
#define ENET_QOS_MTL_TXQX_ETS_CTRL_SLC(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_ETS_CTRL_SLC_SHIFT)) & ENET_QOS_MTL_TXQX_ETS_CTRL_SLC_MASK)
/*! @} */

/* The count of ENET_QOS_MTL_TXQX_ETS_CTRL */
#define ENET_QOS_MTL_TXQX_ETS_CTRL_COUNT         (5U)

/*! @name MTL_TXQX_ETS_STAT - Queue 0 ETS Status..Queue 4 ETS Status */
/*! @{ */

#define ENET_QOS_MTL_TXQX_ETS_STAT_ABS_MASK      (0xFFFFFFU)
#define ENET_QOS_MTL_TXQX_ETS_STAT_ABS_SHIFT     (0U)
/*! ABS - Average Bits per Slot This field contains the average transmitted bits per slot. */
#define ENET_QOS_MTL_TXQX_ETS_STAT_ABS(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_ETS_STAT_ABS_SHIFT)) & ENET_QOS_MTL_TXQX_ETS_STAT_ABS_MASK)
/*! @} */

/* The count of ENET_QOS_MTL_TXQX_ETS_STAT */
#define ENET_QOS_MTL_TXQX_ETS_STAT_COUNT         (5U)

/*! @name MTL_TXQX_QNTM_WGHT - Queue 0 Quantum or Weights..Queue 4 idleSlopeCredit, Quantum or Weights */
/*! @{ */

#define ENET_QOS_MTL_TXQX_QNTM_WGHT_ISCQW_MASK   (0x1FFFFFU)
#define ENET_QOS_MTL_TXQX_QNTM_WGHT_ISCQW_SHIFT  (0U)
/*! ISCQW - Quantum or Weights When the DCB operation is enabled with DWRR algorithm for Queue 0
 *    traffic, this field contains the quantum value in bytes to be added to credit during every queue
 *    scanning cycle.
 */
#define ENET_QOS_MTL_TXQX_QNTM_WGHT_ISCQW(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_QNTM_WGHT_ISCQW_SHIFT)) & ENET_QOS_MTL_TXQX_QNTM_WGHT_ISCQW_MASK)
/*! @} */

/* The count of ENET_QOS_MTL_TXQX_QNTM_WGHT */
#define ENET_QOS_MTL_TXQX_QNTM_WGHT_COUNT        (5U)

/*! @name MTL_TXQX_SNDSLP_CRDT - Queue 1 sendSlopeCredit..Queue 4 sendSlopeCredit */
/*! @{ */

#define ENET_QOS_MTL_TXQX_SNDSLP_CRDT_SSC_MASK   (0x3FFFU)
#define ENET_QOS_MTL_TXQX_SNDSLP_CRDT_SSC_SHIFT  (0U)
/*! SSC - sendSlopeCredit Value When AV operation is enabled, this field contains the
 *    sendSlopeCredit value required for credit-based shaper algorithm for Queue 4.
 */
#define ENET_QOS_MTL_TXQX_SNDSLP_CRDT_SSC(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_SNDSLP_CRDT_SSC_SHIFT)) & ENET_QOS_MTL_TXQX_SNDSLP_CRDT_SSC_MASK)
/*! @} */

/* The count of ENET_QOS_MTL_TXQX_SNDSLP_CRDT */
#define ENET_QOS_MTL_TXQX_SNDSLP_CRDT_COUNT      (5U)

/*! @name MTL_TXQX_HI_CRDT - Queue 1 hiCredit..Queue 4 hiCredit */
/*! @{ */

#define ENET_QOS_MTL_TXQX_HI_CRDT_HC_MASK        (0x1FFFFFFFU)
#define ENET_QOS_MTL_TXQX_HI_CRDT_HC_SHIFT       (0U)
/*! HC - hiCredit Value When the AV feature is enabled, this field contains the hiCredit value
 *    required for the credit-based shaper algorithm.
 */
#define ENET_QOS_MTL_TXQX_HI_CRDT_HC(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_HI_CRDT_HC_SHIFT)) & ENET_QOS_MTL_TXQX_HI_CRDT_HC_MASK)
/*! @} */

/* The count of ENET_QOS_MTL_TXQX_HI_CRDT */
#define ENET_QOS_MTL_TXQX_HI_CRDT_COUNT          (5U)

/*! @name MTL_TXQX_LO_CRDT - Queue 1 loCredit..Queue 4 loCredit */
/*! @{ */

#define ENET_QOS_MTL_TXQX_LO_CRDT_LC_MASK        (0x1FFFFFFFU)
#define ENET_QOS_MTL_TXQX_LO_CRDT_LC_SHIFT       (0U)
/*! LC - loCredit Value When AV operation is enabled, this field contains the loCredit value
 *    required for the credit-based shaper algorithm.
 */
#define ENET_QOS_MTL_TXQX_LO_CRDT_LC(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_LO_CRDT_LC_SHIFT)) & ENET_QOS_MTL_TXQX_LO_CRDT_LC_MASK)
/*! @} */

/* The count of ENET_QOS_MTL_TXQX_LO_CRDT */
#define ENET_QOS_MTL_TXQX_LO_CRDT_COUNT          (5U)

/*! @name MTL_TXQX_INTCTRL_STAT - Queue 0 Interrupt Control Status..Queue 4 Interrupt Control Status */
/*! @{ */

#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_TXUNFIS_MASK (0x1U)
#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_TXUNFIS_SHIFT (0U)
/*! TXUNFIS - Transmit Queue Underflow Interrupt Status This bit indicates that the Transmit Queue
 *    had an underflow while transmitting the packet.
 *  0b0..Transmit Queue Underflow Interrupt Status not detected
 *  0b1..Transmit Queue Underflow Interrupt Status detected
 */
#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_TXUNFIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_INTCTRL_STAT_TXUNFIS_SHIFT)) & ENET_QOS_MTL_TXQX_INTCTRL_STAT_TXUNFIS_MASK)

#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_ABPSIS_MASK (0x2U)
#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_ABPSIS_SHIFT (1U)
/*! ABPSIS - Average Bits Per Slot Interrupt Status When set, this bit indicates that the MAC has updated the ABS value.
 *  0b0..Average Bits Per Slot Interrupt Status not detected
 *  0b1..Average Bits Per Slot Interrupt Status detected
 */
#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_ABPSIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_INTCTRL_STAT_ABPSIS_SHIFT)) & ENET_QOS_MTL_TXQX_INTCTRL_STAT_ABPSIS_MASK)

#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_TXUIE_MASK (0x100U)
#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_TXUIE_SHIFT (8U)
/*! TXUIE - Transmit Queue Underflow Interrupt Enable When this bit is set, the Transmit Queue Underflow interrupt is enabled.
 *  0b0..Transmit Queue Underflow Interrupt Status is disabled
 *  0b1..Transmit Queue Underflow Interrupt Status is enabled
 */
#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_TXUIE(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_INTCTRL_STAT_TXUIE_SHIFT)) & ENET_QOS_MTL_TXQX_INTCTRL_STAT_TXUIE_MASK)

#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_ABPSIE_MASK (0x200U)
#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_ABPSIE_SHIFT (9U)
/*! ABPSIE - Average Bits Per Slot Interrupt Enable When this bit is set, the MAC asserts the
 *    sbd_intr_o or mci_intr_o interrupt when the average bits per slot status is updated.
 *  0b0..Average Bits Per Slot Interrupt is disabled
 *  0b1..Average Bits Per Slot Interrupt is enabled
 */
#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_ABPSIE(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_INTCTRL_STAT_ABPSIE_SHIFT)) & ENET_QOS_MTL_TXQX_INTCTRL_STAT_ABPSIE_MASK)

#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_RXOVFIS_MASK (0x10000U)
#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_RXOVFIS_SHIFT (16U)
/*! RXOVFIS - Receive Queue Overflow Interrupt Status This bit indicates that the Receive Queue had
 *    an overflow while receiving the packet.
 *  0b0..Receive Queue Overflow Interrupt Status not detected
 *  0b1..Receive Queue Overflow Interrupt Status detected
 */
#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_RXOVFIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_INTCTRL_STAT_RXOVFIS_SHIFT)) & ENET_QOS_MTL_TXQX_INTCTRL_STAT_RXOVFIS_MASK)

#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_RXOIE_MASK (0x1000000U)
#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_RXOIE_SHIFT (24U)
/*! RXOIE - Receive Queue Overflow Interrupt Enable When this bit is set, the Receive Queue Overflow interrupt is enabled.
 *  0b0..Receive Queue Overflow Interrupt is disabled
 *  0b1..Receive Queue Overflow Interrupt is enabled
 */
#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_RXOIE(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_TXQX_INTCTRL_STAT_RXOIE_SHIFT)) & ENET_QOS_MTL_TXQX_INTCTRL_STAT_RXOIE_MASK)
/*! @} */

/* The count of ENET_QOS_MTL_TXQX_INTCTRL_STAT */
#define ENET_QOS_MTL_TXQX_INTCTRL_STAT_COUNT     (5U)

/*! @name MTL_RXQX_OP_MODE - Queue 0 Receive Operation Mode..Queue 4 Receive Operation Mode */
/*! @{ */

#define ENET_QOS_MTL_RXQX_OP_MODE_RTC_MASK       (0x3U)
#define ENET_QOS_MTL_RXQX_OP_MODE_RTC_SHIFT      (0U)
/*! RTC - Receive Queue Threshold Control These bits control the threshold level of the MTL Rx queue
 *    (in bytes): The received packet is transferred to the application or DMA when the packet size
 *    within the MTL Rx queue is larger than the threshold.
 *  0b00..64
 *  0b01..32
 *  0b10..96
 *  0b11..128
 */
#define ENET_QOS_MTL_RXQX_OP_MODE_RTC(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_OP_MODE_RTC_SHIFT)) & ENET_QOS_MTL_RXQX_OP_MODE_RTC_MASK)

#define ENET_QOS_MTL_RXQX_OP_MODE_FUP_MASK       (0x8U)
#define ENET_QOS_MTL_RXQX_OP_MODE_FUP_SHIFT      (3U)
/*! FUP - Forward Undersized Good Packets When this bit is set, the Rx queue forwards the undersized
 *    good packets (packets with no error and length less than 64 bytes), including pad-bytes and
 *    CRC.
 *  0b0..Forward Undersized Good Packets is disabled
 *  0b1..Forward Undersized Good Packets is enabled
 */
#define ENET_QOS_MTL_RXQX_OP_MODE_FUP(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_OP_MODE_FUP_SHIFT)) & ENET_QOS_MTL_RXQX_OP_MODE_FUP_MASK)

#define ENET_QOS_MTL_RXQX_OP_MODE_FEP_MASK       (0x10U)
#define ENET_QOS_MTL_RXQX_OP_MODE_FEP_SHIFT      (4U)
/*! FEP - Forward Error Packets When this bit is reset, the Rx queue drops packets with error status
 *    (CRC error, GMII_ER, watchdog timeout, or overflow).
 *  0b0..Forward Error Packets is disabled
 *  0b1..Forward Error Packets is enabled
 */
#define ENET_QOS_MTL_RXQX_OP_MODE_FEP(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_OP_MODE_FEP_SHIFT)) & ENET_QOS_MTL_RXQX_OP_MODE_FEP_MASK)

#define ENET_QOS_MTL_RXQX_OP_MODE_RSF_MASK       (0x20U)
#define ENET_QOS_MTL_RXQX_OP_MODE_RSF_SHIFT      (5U)
/*! RSF - Receive Queue Store and Forward When this bit is set, the DWC_ether_qos reads a packet
 *    from the Rx queue only after the complete packet has been written to it, ignoring the RTC field
 *    of this register.
 *  0b0..Receive Queue Store and Forward is disabled
 *  0b1..Receive Queue Store and Forward is enabled
 */
#define ENET_QOS_MTL_RXQX_OP_MODE_RSF(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_OP_MODE_RSF_SHIFT)) & ENET_QOS_MTL_RXQX_OP_MODE_RSF_MASK)

#define ENET_QOS_MTL_RXQX_OP_MODE_DIS_TCP_EF_MASK (0x40U)
#define ENET_QOS_MTL_RXQX_OP_MODE_DIS_TCP_EF_SHIFT (6U)
/*! DIS_TCP_EF - Disable Dropping of TCP/IP Checksum Error Packets When this bit is set, the MAC
 *    does not drop the packets which only have the errors detected by the Receive Checksum Offload
 *    engine.
 *  0b0..Dropping of TCP/IP Checksum Error Packets is enabled
 *  0b1..Dropping of TCP/IP Checksum Error Packets is disabled
 */
#define ENET_QOS_MTL_RXQX_OP_MODE_DIS_TCP_EF(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_OP_MODE_DIS_TCP_EF_SHIFT)) & ENET_QOS_MTL_RXQX_OP_MODE_DIS_TCP_EF_MASK)

#define ENET_QOS_MTL_RXQX_OP_MODE_EHFC_MASK      (0x80U)
#define ENET_QOS_MTL_RXQX_OP_MODE_EHFC_SHIFT     (7U)
/*! EHFC - Enable Hardware Flow Control When this bit is set, the flow control signal operation,
 *    based on the fill-level of Rx queue, is enabled.
 *  0b0..Hardware Flow Control is disabled
 *  0b1..Hardware Flow Control is enabled
 */
#define ENET_QOS_MTL_RXQX_OP_MODE_EHFC(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_OP_MODE_EHFC_SHIFT)) & ENET_QOS_MTL_RXQX_OP_MODE_EHFC_MASK)

#define ENET_QOS_MTL_RXQX_OP_MODE_RFA_MASK       (0xF00U)
#define ENET_QOS_MTL_RXQX_OP_MODE_RFA_SHIFT      (8U)
/*! RFA - Threshold for Activating Flow Control (in half-duplex and full-duplex These bits control
 *    the threshold (fill-level of Rx queue) at which the flow control is activated: For more
 *    information on encoding for this field, see RFD.
 */
#define ENET_QOS_MTL_RXQX_OP_MODE_RFA(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_OP_MODE_RFA_SHIFT)) & ENET_QOS_MTL_RXQX_OP_MODE_RFA_MASK)

#define ENET_QOS_MTL_RXQX_OP_MODE_RFD_MASK       (0x3C000U)
#define ENET_QOS_MTL_RXQX_OP_MODE_RFD_SHIFT      (14U)
/*! RFD - Threshold for Deactivating Flow Control (in half-duplex and full-duplex modes) These bits
 *    control the threshold (fill-level of Rx queue) at which the flow control is de-asserted after
 *    activation: - 0: Full minus 1 KB, that is, FULL 1 KB - 1: Full minus 1.
 */
#define ENET_QOS_MTL_RXQX_OP_MODE_RFD(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_OP_MODE_RFD_SHIFT)) & ENET_QOS_MTL_RXQX_OP_MODE_RFD_MASK)

#define ENET_QOS_MTL_RXQX_OP_MODE_RQS_MASK       (0x1F00000U)
#define ENET_QOS_MTL_RXQX_OP_MODE_RQS_SHIFT      (20U)
/*! RQS - Receive Queue Size This field indicates the size of the allocated Receive queues in blocks of 256 bytes. */
#define ENET_QOS_MTL_RXQX_OP_MODE_RQS(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_OP_MODE_RQS_SHIFT)) & ENET_QOS_MTL_RXQX_OP_MODE_RQS_MASK)
/*! @} */

/* The count of ENET_QOS_MTL_RXQX_OP_MODE */
#define ENET_QOS_MTL_RXQX_OP_MODE_COUNT          (5U)

/*! @name MTL_RXQX_MISSPKT_OVRFLW_CNT - Queue 0 Missed Packet and Overflow Counter..Queue 4 Missed Packet and Overflow Counter */
/*! @{ */

#define ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFPKTCNT_MASK (0x7FFU)
#define ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFPKTCNT_SHIFT (0U)
/*! OVFPKTCNT - Overflow Packet Counter This field indicates the number of packets discarded by the
 *    DWC_ether_qos because of Receive queue overflow.
 */
#define ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFPKTCNT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFPKTCNT_SHIFT)) & ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFPKTCNT_MASK)

#define ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFCNTOVF_MASK (0x800U)
#define ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFCNTOVF_SHIFT (11U)
/*! OVFCNTOVF - Overflow Counter Overflow Bit When set, this bit indicates that the Rx Queue
 *    Overflow Packet Counter field crossed the maximum limit.
 *  0b0..Overflow Counter overflow not detected
 *  0b1..Overflow Counter overflow detected
 */
#define ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFCNTOVF(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFCNTOVF_SHIFT)) & ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFCNTOVF_MASK)

#define ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_MISPKTCNT_MASK (0x7FF0000U)
#define ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_MISPKTCNT_SHIFT (16U)
/*! MISPKTCNT - Missed Packet Counter This field indicates the number of packets missed by the
 *    DWC_ether_qos because the application asserted ari_pkt_flush_i[] for this queue.
 */
#define ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_MISPKTCNT(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_MISPKTCNT_SHIFT)) & ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_MISPKTCNT_MASK)

#define ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_MISCNTOVF_MASK (0x8000000U)
#define ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_MISCNTOVF_SHIFT (27U)
/*! MISCNTOVF - Missed Packet Counter Overflow Bit When set, this bit indicates that the Rx Queue
 *    Missed Packet Counter crossed the maximum limit.
 *  0b0..Missed Packet Counter overflow not detected
 *  0b1..Missed Packet Counter overflow detected
 */
#define ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_MISCNTOVF(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_MISCNTOVF_SHIFT)) & ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_MISCNTOVF_MASK)
/*! @} */

/* The count of ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT */
#define ENET_QOS_MTL_RXQX_MISSPKT_OVRFLW_CNT_COUNT (5U)

/*! @name MTL_RXQX_DBG - Queue 0 Receive Debug..Queue 4 Receive Debug */
/*! @{ */

#define ENET_QOS_MTL_RXQX_DBG_RWCSTS_MASK        (0x1U)
#define ENET_QOS_MTL_RXQX_DBG_RWCSTS_SHIFT       (0U)
/*! RWCSTS - MTL Rx Queue Write Controller Active Status When high, this bit indicates that the MTL
 *    Rx queue Write controller is active, and it is transferring a received packet to the Rx Queue.
 *  0b0..MTL Rx Queue Write Controller Active Status not detected
 *  0b1..MTL Rx Queue Write Controller Active Status detected
 */
#define ENET_QOS_MTL_RXQX_DBG_RWCSTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_DBG_RWCSTS_SHIFT)) & ENET_QOS_MTL_RXQX_DBG_RWCSTS_MASK)

#define ENET_QOS_MTL_RXQX_DBG_RRCSTS_MASK        (0x6U)
#define ENET_QOS_MTL_RXQX_DBG_RRCSTS_SHIFT       (1U)
/*! RRCSTS - MTL Rx Queue Read Controller State This field gives the state of the Rx queue Read controller:
 *  0b00..Idle state
 *  0b01..Reading packet data
 *  0b10..Reading packet status (or timestamp)
 *  0b11..Flushing the packet data and status
 */
#define ENET_QOS_MTL_RXQX_DBG_RRCSTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_DBG_RRCSTS_SHIFT)) & ENET_QOS_MTL_RXQX_DBG_RRCSTS_MASK)

#define ENET_QOS_MTL_RXQX_DBG_RXQSTS_MASK        (0x30U)
#define ENET_QOS_MTL_RXQX_DBG_RXQSTS_SHIFT       (4U)
/*! RXQSTS - MTL Rx Queue Fill-Level Status This field gives the status of the fill-level of the Rx Queue:
 *  0b00..Rx Queue empty
 *  0b01..Rx Queue fill-level below flow-control deactivate threshold
 *  0b10..Rx Queue fill-level above flow-control activate threshold
 *  0b11..Rx Queue full
 */
#define ENET_QOS_MTL_RXQX_DBG_RXQSTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_DBG_RXQSTS_SHIFT)) & ENET_QOS_MTL_RXQX_DBG_RXQSTS_MASK)

#define ENET_QOS_MTL_RXQX_DBG_PRXQ_MASK          (0x3FFF0000U)
#define ENET_QOS_MTL_RXQX_DBG_PRXQ_SHIFT         (16U)
/*! PRXQ - Number of Packets in Receive Queue This field indicates the current number of packets in the Rx Queue. */
#define ENET_QOS_MTL_RXQX_DBG_PRXQ(x)            (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_DBG_PRXQ_SHIFT)) & ENET_QOS_MTL_RXQX_DBG_PRXQ_MASK)
/*! @} */

/* The count of ENET_QOS_MTL_RXQX_DBG */
#define ENET_QOS_MTL_RXQX_DBG_COUNT              (5U)

/*! @name MTL_RXQX_CTRL - Queue 0 Receive Control..Queue 4 Receive Control */
/*! @{ */

#define ENET_QOS_MTL_RXQX_CTRL_RXQ_WEGT_MASK     (0x7U)
#define ENET_QOS_MTL_RXQX_CTRL_RXQ_WEGT_SHIFT    (0U)
/*! RXQ_WEGT - Receive Queue Weight This field indicates the weight assigned to the Rx Queue 4. */
#define ENET_QOS_MTL_RXQX_CTRL_RXQ_WEGT(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_CTRL_RXQ_WEGT_SHIFT)) & ENET_QOS_MTL_RXQX_CTRL_RXQ_WEGT_MASK)

#define ENET_QOS_MTL_RXQX_CTRL_RXQ_FRM_ARBIT_MASK (0x8U)
#define ENET_QOS_MTL_RXQX_CTRL_RXQ_FRM_ARBIT_SHIFT (3U)
/*! RXQ_FRM_ARBIT - Receive Queue Packet Arbitration When this bit is set, the DWC_ether_qos drives
 *    the packet data to the ARI interface such that the entire packet data of currently-selected
 *    queue is transmitted before switching to other queue.
 *  0b0..Receive Queue Packet Arbitration is disabled
 *  0b1..Receive Queue Packet Arbitration is enabled
 */
#define ENET_QOS_MTL_RXQX_CTRL_RXQ_FRM_ARBIT(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_MTL_RXQX_CTRL_RXQ_FRM_ARBIT_SHIFT)) & ENET_QOS_MTL_RXQX_CTRL_RXQ_FRM_ARBIT_MASK)
/*! @} */

/* The count of ENET_QOS_MTL_RXQX_CTRL */
#define ENET_QOS_MTL_RXQX_CTRL_COUNT             (5U)

/*! @name DMA_MODE - DMA Bus Mode */
/*! @{ */

#define ENET_QOS_DMA_MODE_SWR_MASK               (0x1U)
#define ENET_QOS_DMA_MODE_SWR_SHIFT              (0U)
/*! SWR - Software Reset When this bit is set, the MAC and the DMA controller reset the logic and
 *    all internal registers of the DMA, MTL, and MAC.
 *  0b0..Software Reset is disabled
 *  0b1..Software Reset is enabled
 */
#define ENET_QOS_DMA_MODE_SWR(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_MODE_SWR_SHIFT)) & ENET_QOS_DMA_MODE_SWR_MASK)

#define ENET_QOS_DMA_MODE_DSPW_MASK              (0x100U)
#define ENET_QOS_DMA_MODE_DSPW_SHIFT             (8U)
/*! DSPW - Descriptor Posted Write When this bit is set to 0, the descriptor writes are always non-posted.
 *  0b0..Descriptor Posted Write is disabled
 *  0b1..Descriptor Posted Write is enabled
 */
#define ENET_QOS_DMA_MODE_DSPW(x)                (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_MODE_DSPW_SHIFT)) & ENET_QOS_DMA_MODE_DSPW_MASK)

#define ENET_QOS_DMA_MODE_INTM_MASK              (0x30000U)
#define ENET_QOS_DMA_MODE_INTM_SHIFT             (16U)
/*! INTM - Interrupt Mode This field defines the interrupt mode of DWC_ether_qos.
 *  0b00..See above description
 *  0b01..See above description
 *  0b10..See above description
 *  0b11..Reserved
 */
#define ENET_QOS_DMA_MODE_INTM(x)                (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_MODE_INTM_SHIFT)) & ENET_QOS_DMA_MODE_INTM_MASK)
/*! @} */

/*! @name DMA_SYSBUS_MODE - DMA System Bus Mode */
/*! @{ */

#define ENET_QOS_DMA_SYSBUS_MODE_FB_MASK         (0x1U)
#define ENET_QOS_DMA_SYSBUS_MODE_FB_SHIFT        (0U)
/*! FB - Fixed Burst Length When this bit is set to 1, the EQOS-AXI master initiates burst transfers
 *    of specified lengths as given below.
 *  0b0..Fixed Burst Length is disabled
 *  0b1..Fixed Burst Length is enabled
 */
#define ENET_QOS_DMA_SYSBUS_MODE_FB(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_SYSBUS_MODE_FB_SHIFT)) & ENET_QOS_DMA_SYSBUS_MODE_FB_MASK)

#define ENET_QOS_DMA_SYSBUS_MODE_BLEN4_MASK      (0x2U)
#define ENET_QOS_DMA_SYSBUS_MODE_BLEN4_SHIFT     (1U)
/*! BLEN4 - AXI Burst Length 4 When this bit is set to 1 or the FB bit is set to 0, the EQOS-AXI
 *    master can select a burst length of 4 on the AXI interface.
 *  0b0..No effect
 *  0b1..AXI Burst Length 4
 */
#define ENET_QOS_DMA_SYSBUS_MODE_BLEN4(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_SYSBUS_MODE_BLEN4_SHIFT)) & ENET_QOS_DMA_SYSBUS_MODE_BLEN4_MASK)

#define ENET_QOS_DMA_SYSBUS_MODE_BLEN8_MASK      (0x4U)
#define ENET_QOS_DMA_SYSBUS_MODE_BLEN8_SHIFT     (2U)
/*! BLEN8 - AXI Burst Length 8 When this bit is set to 1 or the FB bit is set to 0, the EQOS-AXI
 *    master can select a burst length of 8 on the AXI interface.
 *  0b0..No effect
 *  0b1..AXI Burst Length 8
 */
#define ENET_QOS_DMA_SYSBUS_MODE_BLEN8(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_SYSBUS_MODE_BLEN8_SHIFT)) & ENET_QOS_DMA_SYSBUS_MODE_BLEN8_MASK)

#define ENET_QOS_DMA_SYSBUS_MODE_BLEN16_MASK     (0x8U)
#define ENET_QOS_DMA_SYSBUS_MODE_BLEN16_SHIFT    (3U)
/*! BLEN16 - AXI Burst Length 16 When this bit is set to 1 or the FB bit is set to 0, the EQOS-AXI
 *    master can select a burst length of 16 on the AXI interface.
 *  0b0..No effect
 *  0b1..AXI Burst Length 16
 */
#define ENET_QOS_DMA_SYSBUS_MODE_BLEN16(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_SYSBUS_MODE_BLEN16_SHIFT)) & ENET_QOS_DMA_SYSBUS_MODE_BLEN16_MASK)

#define ENET_QOS_DMA_SYSBUS_MODE_AALE_MASK       (0x400U)
#define ENET_QOS_DMA_SYSBUS_MODE_AALE_SHIFT      (10U)
/*! AALE - Automatic AXI LPI enable When set to 1, enables the AXI master to enter into LPI state
 *    when there is no activity in the DWC_ether_qos for number of system clock cycles programmed in
 *    the LPIEI field of DMA_AXI_LPI_ENTRY_INTERVAL register.
 *  0b0..Automatic AXI LPI is disabled
 *  0b1..Automatic AXI LPI is enabled
 */
#define ENET_QOS_DMA_SYSBUS_MODE_AALE(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_SYSBUS_MODE_AALE_SHIFT)) & ENET_QOS_DMA_SYSBUS_MODE_AALE_MASK)

#define ENET_QOS_DMA_SYSBUS_MODE_AAL_MASK        (0x1000U)
#define ENET_QOS_DMA_SYSBUS_MODE_AAL_SHIFT       (12U)
/*! AAL - Address-Aligned Beats When this bit is set to 1, the EQOS-AXI or EQOS-AHB master performs
 *    address-aligned burst transfers on Read and Write channels.
 *  0b0..Address-Aligned Beats is disabled
 *  0b1..Address-Aligned Beats is enabled
 */
#define ENET_QOS_DMA_SYSBUS_MODE_AAL(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_SYSBUS_MODE_AAL_SHIFT)) & ENET_QOS_DMA_SYSBUS_MODE_AAL_MASK)

#define ENET_QOS_DMA_SYSBUS_MODE_ONEKBBE_MASK    (0x2000U)
#define ENET_QOS_DMA_SYSBUS_MODE_ONEKBBE_SHIFT   (13U)
/*! ONEKBBE - 1 KB Boundary Crossing Enable for the EQOS-AXI Master When set, the burst transfers
 *    performed by the EQOS-AXI master do not cross 1 KB boundary.
 *  0b0..1 KB Boundary Crossing for the EQOS-AXI Master Beats is disabled
 *  0b1..1 KB Boundary Crossing for the EQOS-AXI Master Beats is enabled
 */
#define ENET_QOS_DMA_SYSBUS_MODE_ONEKBBE(x)      (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_SYSBUS_MODE_ONEKBBE_SHIFT)) & ENET_QOS_DMA_SYSBUS_MODE_ONEKBBE_MASK)

#define ENET_QOS_DMA_SYSBUS_MODE_RD_OSR_LMT_MASK (0xF0000U)
#define ENET_QOS_DMA_SYSBUS_MODE_RD_OSR_LMT_SHIFT (16U)
/*! RD_OSR_LMT - AXI Maximum Read Outstanding Request Limit This value limits the maximum outstanding request on the AXI read interface. */
#define ENET_QOS_DMA_SYSBUS_MODE_RD_OSR_LMT(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_SYSBUS_MODE_RD_OSR_LMT_SHIFT)) & ENET_QOS_DMA_SYSBUS_MODE_RD_OSR_LMT_MASK)

#define ENET_QOS_DMA_SYSBUS_MODE_WR_OSR_LMT_MASK (0xF000000U)
#define ENET_QOS_DMA_SYSBUS_MODE_WR_OSR_LMT_SHIFT (24U)
/*! WR_OSR_LMT - AXI Maximum Write Outstanding Request Limit This value limits the maximum
 *    outstanding request on the AXI write interface.
 */
#define ENET_QOS_DMA_SYSBUS_MODE_WR_OSR_LMT(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_SYSBUS_MODE_WR_OSR_LMT_SHIFT)) & ENET_QOS_DMA_SYSBUS_MODE_WR_OSR_LMT_MASK)

#define ENET_QOS_DMA_SYSBUS_MODE_LPI_XIT_PKT_MASK (0x40000000U)
#define ENET_QOS_DMA_SYSBUS_MODE_LPI_XIT_PKT_SHIFT (30U)
/*! LPI_XIT_PKT - Unlock on Magic Packet or Remote Wake-Up Packet When set to 1, this bit enables
 *    the AXI master to come out of the LPI mode only when the magic packet or remote wake-up packet
 *    is received.
 *  0b0..Unlock on Magic Packet or Remote Wake-Up Packet is disabled
 *  0b1..Unlock on Magic Packet or Remote Wake-Up Packet is enabled
 */
#define ENET_QOS_DMA_SYSBUS_MODE_LPI_XIT_PKT(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_SYSBUS_MODE_LPI_XIT_PKT_SHIFT)) & ENET_QOS_DMA_SYSBUS_MODE_LPI_XIT_PKT_MASK)

#define ENET_QOS_DMA_SYSBUS_MODE_EN_LPI_MASK     (0x80000000U)
#define ENET_QOS_DMA_SYSBUS_MODE_EN_LPI_SHIFT    (31U)
/*! EN_LPI - Enable Low Power Interface (LPI) When set to 1, this bit enables the LPI mode supported
 *    by the EQOS-AXI configuration and accepts the LPI request from the AXI System Clock
 *    controller.
 *  0b0..Low Power Interface (LPI) is disabled
 *  0b1..Low Power Interface (LPI) is enabled
 */
#define ENET_QOS_DMA_SYSBUS_MODE_EN_LPI(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_SYSBUS_MODE_EN_LPI_SHIFT)) & ENET_QOS_DMA_SYSBUS_MODE_EN_LPI_MASK)
/*! @} */

/*! @name DMA_INTERRUPT_STATUS - DMA Interrupt Status */
/*! @{ */

#define ENET_QOS_DMA_INTERRUPT_STATUS_DC0IS_MASK (0x1U)
#define ENET_QOS_DMA_INTERRUPT_STATUS_DC0IS_SHIFT (0U)
/*! DC0IS - DMA Channel 0 Interrupt Status This bit indicates an interrupt event in DMA Channel 0.
 *  0b0..DMA Channel 0 Interrupt Status not detected
 *  0b1..DMA Channel 0 Interrupt Status detected
 */
#define ENET_QOS_DMA_INTERRUPT_STATUS_DC0IS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_INTERRUPT_STATUS_DC0IS_SHIFT)) & ENET_QOS_DMA_INTERRUPT_STATUS_DC0IS_MASK)

#define ENET_QOS_DMA_INTERRUPT_STATUS_DC1IS_MASK (0x2U)
#define ENET_QOS_DMA_INTERRUPT_STATUS_DC1IS_SHIFT (1U)
/*! DC1IS - DMA Channel 1 Interrupt Status This bit indicates an interrupt event in DMA Channel 1.
 *  0b0..DMA Channel 1 Interrupt Status not detected
 *  0b1..DMA Channel 1 Interrupt Status detected
 */
#define ENET_QOS_DMA_INTERRUPT_STATUS_DC1IS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_INTERRUPT_STATUS_DC1IS_SHIFT)) & ENET_QOS_DMA_INTERRUPT_STATUS_DC1IS_MASK)

#define ENET_QOS_DMA_INTERRUPT_STATUS_DC2IS_MASK (0x4U)
#define ENET_QOS_DMA_INTERRUPT_STATUS_DC2IS_SHIFT (2U)
/*! DC2IS - DMA Channel 2 Interrupt Status This bit indicates an interrupt event in DMA Channel 2.
 *  0b0..DMA Channel 2 Interrupt Status not detected
 *  0b1..DMA Channel 2 Interrupt Status detected
 */
#define ENET_QOS_DMA_INTERRUPT_STATUS_DC2IS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_INTERRUPT_STATUS_DC2IS_SHIFT)) & ENET_QOS_DMA_INTERRUPT_STATUS_DC2IS_MASK)

#define ENET_QOS_DMA_INTERRUPT_STATUS_DC3IS_MASK (0x8U)
#define ENET_QOS_DMA_INTERRUPT_STATUS_DC3IS_SHIFT (3U)
/*! DC3IS - DMA Channel 3 Interrupt Status This bit indicates an interrupt event in DMA Channel 3.
 *  0b0..DMA Channel 3 Interrupt Status not detected
 *  0b1..DMA Channel 3 Interrupt Status detected
 */
#define ENET_QOS_DMA_INTERRUPT_STATUS_DC3IS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_INTERRUPT_STATUS_DC3IS_SHIFT)) & ENET_QOS_DMA_INTERRUPT_STATUS_DC3IS_MASK)

#define ENET_QOS_DMA_INTERRUPT_STATUS_DC4IS_MASK (0x10U)
#define ENET_QOS_DMA_INTERRUPT_STATUS_DC4IS_SHIFT (4U)
/*! DC4IS - DMA Channel 4 Interrupt Status This bit indicates an interrupt event in DMA Channel 4.
 *  0b0..DMA Channel 4 Interrupt Status not detected
 *  0b1..DMA Channel 4 Interrupt Status detected
 */
#define ENET_QOS_DMA_INTERRUPT_STATUS_DC4IS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_INTERRUPT_STATUS_DC4IS_SHIFT)) & ENET_QOS_DMA_INTERRUPT_STATUS_DC4IS_MASK)

#define ENET_QOS_DMA_INTERRUPT_STATUS_MTLIS_MASK (0x10000U)
#define ENET_QOS_DMA_INTERRUPT_STATUS_MTLIS_SHIFT (16U)
/*! MTLIS - MTL Interrupt Status This bit indicates an interrupt event in the MTL.
 *  0b0..MTL Interrupt Status not detected
 *  0b1..MTL Interrupt Status detected
 */
#define ENET_QOS_DMA_INTERRUPT_STATUS_MTLIS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_INTERRUPT_STATUS_MTLIS_SHIFT)) & ENET_QOS_DMA_INTERRUPT_STATUS_MTLIS_MASK)

#define ENET_QOS_DMA_INTERRUPT_STATUS_MACIS_MASK (0x20000U)
#define ENET_QOS_DMA_INTERRUPT_STATUS_MACIS_SHIFT (17U)
/*! MACIS - MAC Interrupt Status This bit indicates an interrupt event in the MAC.
 *  0b0..MAC Interrupt Status not detected
 *  0b1..MAC Interrupt Status detected
 */
#define ENET_QOS_DMA_INTERRUPT_STATUS_MACIS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_INTERRUPT_STATUS_MACIS_SHIFT)) & ENET_QOS_DMA_INTERRUPT_STATUS_MACIS_MASK)
/*! @} */

/*! @name DMA_DEBUG_STATUS0 - DMA Debug Status 0 */
/*! @{ */

#define ENET_QOS_DMA_DEBUG_STATUS0_AXWHSTS_MASK  (0x1U)
#define ENET_QOS_DMA_DEBUG_STATUS0_AXWHSTS_SHIFT (0U)
/*! AXWHSTS - AXI Master Write Channel When high, this bit indicates that the write channel of the
 *    AXI master is active, and it is transferring data.
 *  0b0..AXI Master Write Channel or AHB Master Status not detected
 *  0b1..AXI Master Write Channel or AHB Master Status detected
 */
#define ENET_QOS_DMA_DEBUG_STATUS0_AXWHSTS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_DEBUG_STATUS0_AXWHSTS_SHIFT)) & ENET_QOS_DMA_DEBUG_STATUS0_AXWHSTS_MASK)

#define ENET_QOS_DMA_DEBUG_STATUS0_AXRHSTS_MASK  (0x2U)
#define ENET_QOS_DMA_DEBUG_STATUS0_AXRHSTS_SHIFT (1U)
/*! AXRHSTS - AXI Master Read Channel Status When high, this bit indicates that the read channel of
 *    the AXI master is active, and it is transferring the data.
 *  0b0..AXI Master Read Channel Status not detected
 *  0b1..AXI Master Read Channel Status detected
 */
#define ENET_QOS_DMA_DEBUG_STATUS0_AXRHSTS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_DEBUG_STATUS0_AXRHSTS_SHIFT)) & ENET_QOS_DMA_DEBUG_STATUS0_AXRHSTS_MASK)

#define ENET_QOS_DMA_DEBUG_STATUS0_RPS0_MASK     (0xF00U)
#define ENET_QOS_DMA_DEBUG_STATUS0_RPS0_SHIFT    (8U)
/*! RPS0 - DMA Channel 0 Receive Process State This field indicates the Rx DMA FSM state for Channel 0.
 *  0b0000..Stopped (Reset or Stop Receive Command issued)
 *  0b0001..Running (Fetching Rx Transfer Descriptor)
 *  0b0010..Reserved for future use
 *  0b0011..Running (Waiting for Rx packet)
 *  0b0100..Suspended (Rx Descriptor Unavailable)
 *  0b0101..Running (Closing the Rx Descriptor)
 *  0b0110..Timestamp write state
 *  0b0111..Running (Transferring the received packet data from the Rx buffer to the system memory)
 */
#define ENET_QOS_DMA_DEBUG_STATUS0_RPS0(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_DEBUG_STATUS0_RPS0_SHIFT)) & ENET_QOS_DMA_DEBUG_STATUS0_RPS0_MASK)

#define ENET_QOS_DMA_DEBUG_STATUS0_TPS0_MASK     (0xF000U)
#define ENET_QOS_DMA_DEBUG_STATUS0_TPS0_SHIFT    (12U)
/*! TPS0 - DMA Channel 0 Transmit Process State This field indicates the Tx DMA FSM state for Channel 0.
 *  0b0000..Stopped (Reset or Stop Transmit Command issued)
 *  0b0001..Running (Fetching Tx Transfer Descriptor)
 *  0b0010..Running (Waiting for status)
 *  0b0011..Running (Reading Data from system memory buffer and queuing it to the Tx buffer (Tx FIFO))
 *  0b0100..Timestamp write state
 *  0b0101..Reserved for future use
 *  0b0110..Suspended (Tx Descriptor Unavailable or Tx Buffer Underflow)
 *  0b0111..Running (Closing Tx Descriptor)
 */
#define ENET_QOS_DMA_DEBUG_STATUS0_TPS0(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_DEBUG_STATUS0_TPS0_SHIFT)) & ENET_QOS_DMA_DEBUG_STATUS0_TPS0_MASK)

#define ENET_QOS_DMA_DEBUG_STATUS0_RPS1_MASK     (0xF0000U)
#define ENET_QOS_DMA_DEBUG_STATUS0_RPS1_SHIFT    (16U)
/*! RPS1 - DMA Channel 1 Receive Process State This field indicates the Rx DMA FSM state for Channel 1.
 *  0b0000..Stopped (Reset or Stop Receive Command issued)
 *  0b0001..Running (Fetching Rx Transfer Descriptor)
 *  0b0010..Reserved for future use
 *  0b0011..Running (Waiting for Rx packet)
 *  0b0100..Suspended (Rx Descriptor Unavailable)
 *  0b0101..Running (Closing the Rx Descriptor)
 *  0b0110..Timestamp write state
 *  0b0111..Running (Transferring the received packet data from the Rx buffer to the system memory)
 */
#define ENET_QOS_DMA_DEBUG_STATUS0_RPS1(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_DEBUG_STATUS0_RPS1_SHIFT)) & ENET_QOS_DMA_DEBUG_STATUS0_RPS1_MASK)

#define ENET_QOS_DMA_DEBUG_STATUS0_TPS1_MASK     (0xF00000U)
#define ENET_QOS_DMA_DEBUG_STATUS0_TPS1_SHIFT    (20U)
/*! TPS1 - DMA Channel 1 Transmit Process State This field indicates the Tx DMA FSM state for Channel 1.
 *  0b0000..Stopped (Reset or Stop Transmit Command issued)
 *  0b0001..Running (Fetching Tx Transfer Descriptor)
 *  0b0010..Running (Waiting for status)
 *  0b0011..Running (Reading Data from system memory buffer and queuing it to the Tx buffer (Tx FIFO))
 *  0b0100..Timestamp write state
 *  0b0101..Reserved for future use
 *  0b0110..Suspended (Tx Descriptor Unavailable or Tx Buffer Underflow)
 *  0b0111..Running (Closing Tx Descriptor)
 */
#define ENET_QOS_DMA_DEBUG_STATUS0_TPS1(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_DEBUG_STATUS0_TPS1_SHIFT)) & ENET_QOS_DMA_DEBUG_STATUS0_TPS1_MASK)

#define ENET_QOS_DMA_DEBUG_STATUS0_RPS2_MASK     (0xF000000U)
#define ENET_QOS_DMA_DEBUG_STATUS0_RPS2_SHIFT    (24U)
/*! RPS2 - DMA Channel 2 Receive Process State This field indicates the Rx DMA FSM state for Channel 2.
 *  0b0000..Stopped (Reset or Stop Receive Command issued)
 *  0b0001..Running (Fetching Rx Transfer Descriptor)
 *  0b0010..Reserved for future use
 *  0b0011..Running (Waiting for Rx packet)
 *  0b0100..Suspended (Rx Descriptor Unavailable)
 *  0b0101..Running (Closing the Rx Descriptor)
 *  0b0110..Timestamp write state
 *  0b0111..Running (Transferring the received packet data from the Rx buffer to the system memory)
 */
#define ENET_QOS_DMA_DEBUG_STATUS0_RPS2(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_DEBUG_STATUS0_RPS2_SHIFT)) & ENET_QOS_DMA_DEBUG_STATUS0_RPS2_MASK)

#define ENET_QOS_DMA_DEBUG_STATUS0_TPS2_MASK     (0xF0000000U)
#define ENET_QOS_DMA_DEBUG_STATUS0_TPS2_SHIFT    (28U)
/*! TPS2 - DMA Channel 2 Transmit Process State This field indicates the Tx DMA FSM state for Channel 2.
 *  0b0000..Stopped (Reset or Stop Transmit Command issued)
 *  0b0001..Running (Fetching Tx Transfer Descriptor)
 *  0b0010..Running (Waiting for status)
 *  0b0011..Running (Reading Data from system memory buffer and queuing it to the Tx buffer (Tx FIFO))
 *  0b0100..Timestamp write state
 *  0b0101..Reserved for future use
 *  0b0110..Suspended (Tx Descriptor Unavailable or Tx Buffer Underflow)
 *  0b0111..Running (Closing Tx Descriptor)
 */
#define ENET_QOS_DMA_DEBUG_STATUS0_TPS2(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_DEBUG_STATUS0_TPS2_SHIFT)) & ENET_QOS_DMA_DEBUG_STATUS0_TPS2_MASK)
/*! @} */

/*! @name DMA_DEBUG_STATUS1 - DMA Debug Status 1 */
/*! @{ */

#define ENET_QOS_DMA_DEBUG_STATUS1_RPS3_MASK     (0xFU)
#define ENET_QOS_DMA_DEBUG_STATUS1_RPS3_SHIFT    (0U)
/*! RPS3 - DMA Channel 3 Receive Process State This field indicates the Rx DMA FSM state for Channel 3.
 *  0b0000..Stopped (Reset or Stop Receive Command issued)
 *  0b0001..Running (Fetching Rx Transfer Descriptor)
 *  0b0010..Reserved for future use
 *  0b0011..Running (Waiting for Rx packet)
 *  0b0100..Suspended (Rx Descriptor Unavailable)
 *  0b0101..Running (Closing the Rx Descriptor)
 *  0b0110..Timestamp write state
 *  0b0111..Running (Transferring the received packet data from the Rx buffer to the system memory)
 */
#define ENET_QOS_DMA_DEBUG_STATUS1_RPS3(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_DEBUG_STATUS1_RPS3_SHIFT)) & ENET_QOS_DMA_DEBUG_STATUS1_RPS3_MASK)

#define ENET_QOS_DMA_DEBUG_STATUS1_TPS3_MASK     (0xF0U)
#define ENET_QOS_DMA_DEBUG_STATUS1_TPS3_SHIFT    (4U)
/*! TPS3 - DMA Channel 3 Transmit Process State This field indicates the Tx DMA FSM state for Channel 3.
 *  0b0000..Stopped (Reset or Stop Transmit Command issued)
 *  0b0001..Running (Fetching Tx Transfer Descriptor)
 *  0b0010..Running (Waiting for status)
 *  0b0011..Running (Reading Data from system memory buffer and queuing it to the Tx buffer (Tx FIFO))
 *  0b0100..Timestamp write state
 *  0b0101..Reserved for future use
 *  0b0110..Suspended (Tx Descriptor Unavailable or Tx Buffer Underflow)
 *  0b0111..Running (Closing Tx Descriptor)
 */
#define ENET_QOS_DMA_DEBUG_STATUS1_TPS3(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_DEBUG_STATUS1_TPS3_SHIFT)) & ENET_QOS_DMA_DEBUG_STATUS1_TPS3_MASK)

#define ENET_QOS_DMA_DEBUG_STATUS1_RPS4_MASK     (0xF00U)
#define ENET_QOS_DMA_DEBUG_STATUS1_RPS4_SHIFT    (8U)
/*! RPS4 - DMA Channel 4 Receive Process State This field indicates the Rx DMA FSM state for Channel 4.
 *  0b0000..Stopped (Reset or Stop Receive Command issued)
 *  0b0001..Running (Fetching Rx Transfer Descriptor)
 *  0b0010..Reserved for future use
 *  0b0011..Running (Waiting for Rx packet)
 *  0b0100..Suspended (Rx Descriptor Unavailable)
 *  0b0101..Running (Closing the Rx Descriptor)
 *  0b0110..Timestamp write state
 *  0b0111..Running (Transferring the received packet data from the Rx buffer to the system memory)
 */
#define ENET_QOS_DMA_DEBUG_STATUS1_RPS4(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_DEBUG_STATUS1_RPS4_SHIFT)) & ENET_QOS_DMA_DEBUG_STATUS1_RPS4_MASK)

#define ENET_QOS_DMA_DEBUG_STATUS1_TPS4_MASK     (0xF000U)
#define ENET_QOS_DMA_DEBUG_STATUS1_TPS4_SHIFT    (12U)
/*! TPS4 - DMA Channel 4 Transmit Process State This field indicates the Tx DMA FSM state for Channel 4.
 *  0b0000..Stopped (Reset or Stop Transmit Command issued)
 *  0b0001..Running (Fetching Tx Transfer Descriptor)
 *  0b0010..Running (Waiting for status)
 *  0b0011..Running (Reading Data from system memory buffer and queuing it to the Tx buffer (Tx FIFO))
 *  0b0100..Timestamp write state
 *  0b0101..Reserved for future use
 *  0b0110..Suspended (Tx Descriptor Unavailable or Tx Buffer Underflow)
 *  0b0111..Running (Closing Tx Descriptor)
 */
#define ENET_QOS_DMA_DEBUG_STATUS1_TPS4(x)       (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_DEBUG_STATUS1_TPS4_SHIFT)) & ENET_QOS_DMA_DEBUG_STATUS1_TPS4_MASK)
/*! @} */

/*! @name DMA_AXI_LPI_ENTRY_INTERVAL - AXI LPI Entry Interval Control */
/*! @{ */

#define ENET_QOS_DMA_AXI_LPI_ENTRY_INTERVAL_LPIEI_MASK (0xFU)
#define ENET_QOS_DMA_AXI_LPI_ENTRY_INTERVAL_LPIEI_SHIFT (0U)
/*! LPIEI - LPI Entry Interval Contains the number of system clock cycles, multiplied by 64, to wait
 *    for an activity in the DWC_ether_qos to enter into the AXI low power state 0 indicates 64
 *    clock cycles
 */
#define ENET_QOS_DMA_AXI_LPI_ENTRY_INTERVAL_LPIEI(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_AXI_LPI_ENTRY_INTERVAL_LPIEI_SHIFT)) & ENET_QOS_DMA_AXI_LPI_ENTRY_INTERVAL_LPIEI_MASK)
/*! @} */

/*! @name DMA_TBS_CTRL0 - DMA_TBS_CTRL0 */
/*! @{ */

#define ENET_QOS_DMA_TBS_CTRL0_FTOV_MASK         (0x1U)
#define ENET_QOS_DMA_TBS_CTRL0_FTOV_SHIFT        (0U)
/*! FTOV - Fetch Time Offset Valid When set indicates the FTOS field is valid. When not set,
 *    indicates the Fetch Offset is not valid and the DMA engine can fetch the frames from host memory
 *    without any time restrictions.
 *  0b0..Fetch Time Offset is invalid
 *  0b1..Fetch Time Offset is valid
 */
#define ENET_QOS_DMA_TBS_CTRL0_FTOV(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_TBS_CTRL0_FTOV_SHIFT)) & ENET_QOS_DMA_TBS_CTRL0_FTOV_MASK)

#define ENET_QOS_DMA_TBS_CTRL0_FGOS_MASK         (0x70U)
#define ENET_QOS_DMA_TBS_CTRL0_FGOS_SHIFT        (4U)
/*! FGOS - Fetch GSN Offset */
#define ENET_QOS_DMA_TBS_CTRL0_FGOS(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_TBS_CTRL0_FGOS_SHIFT)) & ENET_QOS_DMA_TBS_CTRL0_FGOS_MASK)

#define ENET_QOS_DMA_TBS_CTRL0_FTOS_MASK         (0xFFFFFF00U)
#define ENET_QOS_DMA_TBS_CTRL0_FTOS_SHIFT        (8U)
/*! FTOS - Fetch Time Offset */
#define ENET_QOS_DMA_TBS_CTRL0_FTOS(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_TBS_CTRL0_FTOS_SHIFT)) & ENET_QOS_DMA_TBS_CTRL0_FTOS_MASK)
/*! @} */

/*! @name DMA_TBS_CTRL1 - DMA_TBS_CTRL1 */
/*! @{ */

#define ENET_QOS_DMA_TBS_CTRL1_FTOV_MASK         (0x1U)
#define ENET_QOS_DMA_TBS_CTRL1_FTOV_SHIFT        (0U)
/*! FTOV - Fetch Time Offset Valid When set indicates the FTOS field is valid. When not set,
 *    indicates the Fetch Offset is not valid and the DMA engine can fetch the frames from host memory
 *    without any time restrictions.
 *  0b0..Fetch Time Offset is invalid
 *  0b1..Fetch Time Offset is valid
 */
#define ENET_QOS_DMA_TBS_CTRL1_FTOV(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_TBS_CTRL1_FTOV_SHIFT)) & ENET_QOS_DMA_TBS_CTRL1_FTOV_MASK)

#define ENET_QOS_DMA_TBS_CTRL1_FGOS_MASK         (0x70U)
#define ENET_QOS_DMA_TBS_CTRL1_FGOS_SHIFT        (4U)
/*! FGOS - Fetch GSN Offset */
#define ENET_QOS_DMA_TBS_CTRL1_FGOS(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_TBS_CTRL1_FGOS_SHIFT)) & ENET_QOS_DMA_TBS_CTRL1_FGOS_MASK)

#define ENET_QOS_DMA_TBS_CTRL1_FTOS_MASK         (0xFFFFFF00U)
#define ENET_QOS_DMA_TBS_CTRL1_FTOS_SHIFT        (8U)
/*! FTOS - Fetch Time Offset */
#define ENET_QOS_DMA_TBS_CTRL1_FTOS(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_TBS_CTRL1_FTOS_SHIFT)) & ENET_QOS_DMA_TBS_CTRL1_FTOS_MASK)
/*! @} */

/*! @name DMA_TBS_CTRL2 - DMA_TBS_CTRL2 */
/*! @{ */

#define ENET_QOS_DMA_TBS_CTRL2_FTOV_MASK         (0x1U)
#define ENET_QOS_DMA_TBS_CTRL2_FTOV_SHIFT        (0U)
/*! FTOV - Fetch Time Offset Valid When set indicates the FTOS field is valid. When not set,
 *    indicates the Fetch Offset is not valid and the DMA engine can fetch the frames from host memory
 *    without any time restrictions.
 *  0b0..Fetch Time Offset is invalid
 *  0b1..Fetch Time Offset is valid
 */
#define ENET_QOS_DMA_TBS_CTRL2_FTOV(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_TBS_CTRL2_FTOV_SHIFT)) & ENET_QOS_DMA_TBS_CTRL2_FTOV_MASK)

#define ENET_QOS_DMA_TBS_CTRL2_FGOS_MASK         (0x70U)
#define ENET_QOS_DMA_TBS_CTRL2_FGOS_SHIFT        (4U)
/*! FGOS - Fetch GSN Offset */
#define ENET_QOS_DMA_TBS_CTRL2_FGOS(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_TBS_CTRL2_FGOS_SHIFT)) & ENET_QOS_DMA_TBS_CTRL2_FGOS_MASK)

#define ENET_QOS_DMA_TBS_CTRL2_FTOS_MASK         (0xFFFFFF00U)
#define ENET_QOS_DMA_TBS_CTRL2_FTOS_SHIFT        (8U)
/*! FTOS - Fetch Time Offset */
#define ENET_QOS_DMA_TBS_CTRL2_FTOS(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_TBS_CTRL2_FTOS_SHIFT)) & ENET_QOS_DMA_TBS_CTRL2_FTOS_MASK)
/*! @} */

/*! @name DMA_TBS_CTRL3 - DMA_TBS_CTRL3 */
/*! @{ */

#define ENET_QOS_DMA_TBS_CTRL3_FTOV_MASK         (0x1U)
#define ENET_QOS_DMA_TBS_CTRL3_FTOV_SHIFT        (0U)
/*! FTOV - Fetch Time Offset Valid When set indicates the FTOS field is valid. When not set,
 *    indicates the Fetch Offset is not valid and the DMA engine can fetch the frames from host memory
 *    without any time restrictions.
 *  0b0..Fetch Time Offset is invalid
 *  0b1..Fetch Time Offset is valid
 */
#define ENET_QOS_DMA_TBS_CTRL3_FTOV(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_TBS_CTRL3_FTOV_SHIFT)) & ENET_QOS_DMA_TBS_CTRL3_FTOV_MASK)

#define ENET_QOS_DMA_TBS_CTRL3_FGOS_MASK         (0x70U)
#define ENET_QOS_DMA_TBS_CTRL3_FGOS_SHIFT        (4U)
/*! FGOS - Fetch GSN Offset */
#define ENET_QOS_DMA_TBS_CTRL3_FGOS(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_TBS_CTRL3_FGOS_SHIFT)) & ENET_QOS_DMA_TBS_CTRL3_FGOS_MASK)

#define ENET_QOS_DMA_TBS_CTRL3_FTOS_MASK         (0xFFFFFF00U)
#define ENET_QOS_DMA_TBS_CTRL3_FTOS_SHIFT        (8U)
/*! FTOS - Fetch Time Offset */
#define ENET_QOS_DMA_TBS_CTRL3_FTOS(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_TBS_CTRL3_FTOS_SHIFT)) & ENET_QOS_DMA_TBS_CTRL3_FTOS_MASK)
/*! @} */

/*! @name DMA_CHX_CTRL - DMA Channel 0 Control..Channel 4 Control */
/*! @{ */

#define ENET_QOS_DMA_CHX_CTRL_PBLx8_MASK         (0x10000U)
#define ENET_QOS_DMA_CHX_CTRL_PBLx8_SHIFT        (16U)
/*! PBLx8 - 8xPBL mode When this bit is set, the PBL value programmed in Bits[21:16] in
 *    DMA_CH4_TX_CONTROL and Bits[21:16] in DMA_CH4_RX_CONTROL is multiplied by eight times.
 *  0b0..8xPBL mode is disabled
 *  0b1..8xPBL mode is enabled
 */
#define ENET_QOS_DMA_CHX_CTRL_PBLx8(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_CTRL_PBLx8_SHIFT)) & ENET_QOS_DMA_CHX_CTRL_PBLx8_MASK)

#define ENET_QOS_DMA_CHX_CTRL_DSL_MASK           (0x1C0000U)
#define ENET_QOS_DMA_CHX_CTRL_DSL_SHIFT          (18U)
/*! DSL - Descriptor Skip Length This bit specifies the Word, Dword, or Lword number (depending on
 *    the 32-bit, 64-bit, or 128-bit bus) to skip between two unchained descriptors.
 */
#define ENET_QOS_DMA_CHX_CTRL_DSL(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_CTRL_DSL_SHIFT)) & ENET_QOS_DMA_CHX_CTRL_DSL_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_CTRL */
#define ENET_QOS_DMA_CHX_CTRL_COUNT              (5U)

/*! @name DMA_CHX_TX_CTRL - DMA Channel 0 Transmit Control..DMA Channel 4 Transmit Control */
/*! @{ */

#define ENET_QOS_DMA_CHX_TX_CTRL_ST_MASK         (0x1U)
#define ENET_QOS_DMA_CHX_TX_CTRL_ST_SHIFT        (0U)
/*! ST - Start or Stop Transmission Command When this bit is set, transmission is placed in the Running state.
 *  0b0..Stop Transmission Command
 *  0b1..Start Transmission Command
 */
#define ENET_QOS_DMA_CHX_TX_CTRL_ST(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_TX_CTRL_ST_SHIFT)) & ENET_QOS_DMA_CHX_TX_CTRL_ST_MASK)

#define ENET_QOS_DMA_CHX_TX_CTRL_OSF_MASK        (0x10U)
#define ENET_QOS_DMA_CHX_TX_CTRL_OSF_SHIFT       (4U)
/*! OSF - Operate on Second Packet When this bit is set, it instructs the DMA to process the second
 *    packet of the Transmit data even before the status for the first packet is obtained.
 *  0b0..Operate on Second Packet disabled
 *  0b1..Operate on Second Packet enabled
 */
#define ENET_QOS_DMA_CHX_TX_CTRL_OSF(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_TX_CTRL_OSF_SHIFT)) & ENET_QOS_DMA_CHX_TX_CTRL_OSF_MASK)

#define ENET_QOS_DMA_CHX_TX_CTRL_IPBL_MASK       (0x8000U)
#define ENET_QOS_DMA_CHX_TX_CTRL_IPBL_SHIFT      (15U)
/*! IPBL - Ignore PBL Requirement When this bit is set, the DMA does not check for PBL number of
 *    locations in the MTL before initiating a transfer.
 *  0b0..Ignore PBL Requirement is disabled
 *  0b1..Ignore PBL Requirement is enabled
 */
#define ENET_QOS_DMA_CHX_TX_CTRL_IPBL(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_TX_CTRL_IPBL_SHIFT)) & ENET_QOS_DMA_CHX_TX_CTRL_IPBL_MASK)

#define ENET_QOS_DMA_CHX_TX_CTRL_TxPBL_MASK      (0x3F0000U)
#define ENET_QOS_DMA_CHX_TX_CTRL_TxPBL_SHIFT     (16U)
/*! TxPBL - Transmit Programmable Burst Length These bits indicate the maximum number of beats to be
 *    transferred in one DMA block data transfer.
 */
#define ENET_QOS_DMA_CHX_TX_CTRL_TxPBL(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_TX_CTRL_TxPBL_SHIFT)) & ENET_QOS_DMA_CHX_TX_CTRL_TxPBL_MASK)

#define ENET_QOS_DMA_CHX_TX_CTRL_EDSE_MASK       (0x10000000U)
#define ENET_QOS_DMA_CHX_TX_CTRL_EDSE_SHIFT      (28U)
/*! EDSE - Enhanced Descriptor Enable When this bit is set, the corresponding channel uses Enhanced
 *    Descriptors that are 32 Bytes for both Normal and Context Descriptors.
 *  0b0..Enhanced Descriptor is disabled
 *  0b1..Enhanced Descriptor is enabled
 */
#define ENET_QOS_DMA_CHX_TX_CTRL_EDSE(x)         (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_TX_CTRL_EDSE_SHIFT)) & ENET_QOS_DMA_CHX_TX_CTRL_EDSE_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_TX_CTRL */
#define ENET_QOS_DMA_CHX_TX_CTRL_COUNT           (5U)

/*! @name DMA_CHX_RX_CTRL - DMA Channel 0 Receive Control..DMA Channel 4 Receive Control */
/*! @{ */

#define ENET_QOS_DMA_CHX_RX_CTRL_SR_MASK         (0x1U)
#define ENET_QOS_DMA_CHX_RX_CTRL_SR_SHIFT        (0U)
/*! SR - Start or Stop Receive When this bit is set, the DMA tries to acquire the descriptor from
 *    the Receive list and processes the incoming packets.
 *  0b0..Stop Receive
 *  0b1..Start Receive
 */
#define ENET_QOS_DMA_CHX_RX_CTRL_SR(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_RX_CTRL_SR_SHIFT)) & ENET_QOS_DMA_CHX_RX_CTRL_SR_MASK)

#define ENET_QOS_DMA_CHX_RX_CTRL_RBSZ_x_0_MASK   (0xEU)
#define ENET_QOS_DMA_CHX_RX_CTRL_RBSZ_x_0_SHIFT  (1U)
/*! RBSZ_x_0 - Receive Buffer size Low RBSZ[13:0] is split into two fields RBSZ_13_y and RBSZ_x_0. */
#define ENET_QOS_DMA_CHX_RX_CTRL_RBSZ_x_0(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_RX_CTRL_RBSZ_x_0_SHIFT)) & ENET_QOS_DMA_CHX_RX_CTRL_RBSZ_x_0_MASK)

#define ENET_QOS_DMA_CHX_RX_CTRL_RBSZ_13_y_MASK  (0x7FF0U)
#define ENET_QOS_DMA_CHX_RX_CTRL_RBSZ_13_y_SHIFT (4U)
/*! RBSZ_13_y - Receive Buffer size High RBSZ[13:0] is split into two fields higher RBSZ_13_y and lower RBSZ_x_0. */
#define ENET_QOS_DMA_CHX_RX_CTRL_RBSZ_13_y(x)    (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_RX_CTRL_RBSZ_13_y_SHIFT)) & ENET_QOS_DMA_CHX_RX_CTRL_RBSZ_13_y_MASK)

#define ENET_QOS_DMA_CHX_RX_CTRL_RxPBL_MASK      (0x3F0000U)
#define ENET_QOS_DMA_CHX_RX_CTRL_RxPBL_SHIFT     (16U)
/*! RxPBL - Receive Programmable Burst Length These bits indicate the maximum number of beats to be
 *    transferred in one DMA block data transfer.
 */
#define ENET_QOS_DMA_CHX_RX_CTRL_RxPBL(x)        (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_RX_CTRL_RxPBL_SHIFT)) & ENET_QOS_DMA_CHX_RX_CTRL_RxPBL_MASK)

#define ENET_QOS_DMA_CHX_RX_CTRL_RPF_MASK        (0x80000000U)
#define ENET_QOS_DMA_CHX_RX_CTRL_RPF_SHIFT       (31U)
/*! RPF - Rx Packet Flush.
 *  0b0..Rx Packet Flush is disabled
 *  0b1..Rx Packet Flush is enabled
 */
#define ENET_QOS_DMA_CHX_RX_CTRL_RPF(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_RX_CTRL_RPF_SHIFT)) & ENET_QOS_DMA_CHX_RX_CTRL_RPF_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_RX_CTRL */
#define ENET_QOS_DMA_CHX_RX_CTRL_COUNT           (5U)

/*! @name DMA_CHX_TXDESC_LIST_ADDR - Channel 0 Tx Descriptor List Address register..Channel 4 Tx Descriptor List Address */
/*! @{ */

#define ENET_QOS_DMA_CHX_TXDESC_LIST_ADDR_TDESLA_MASK (0xFFFFFFF8U)
#define ENET_QOS_DMA_CHX_TXDESC_LIST_ADDR_TDESLA_SHIFT (3U)
/*! TDESLA - Start of Transmit List This field contains the base address of the first descriptor in the Transmit descriptor list. */
#define ENET_QOS_DMA_CHX_TXDESC_LIST_ADDR_TDESLA(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_TXDESC_LIST_ADDR_TDESLA_SHIFT)) & ENET_QOS_DMA_CHX_TXDESC_LIST_ADDR_TDESLA_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_TXDESC_LIST_ADDR */
#define ENET_QOS_DMA_CHX_TXDESC_LIST_ADDR_COUNT  (5U)

/*! @name DMA_CHX_RXDESC_LIST_ADDR - Channel 0 Rx Descriptor List Address register..Channel 4 Rx Descriptor List Address */
/*! @{ */

#define ENET_QOS_DMA_CHX_RXDESC_LIST_ADDR_RDESLA_MASK (0xFFFFFFF8U)
#define ENET_QOS_DMA_CHX_RXDESC_LIST_ADDR_RDESLA_SHIFT (3U)
/*! RDESLA - Start of Receive List This field contains the base address of the first descriptor in the Rx Descriptor list. */
#define ENET_QOS_DMA_CHX_RXDESC_LIST_ADDR_RDESLA(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_RXDESC_LIST_ADDR_RDESLA_SHIFT)) & ENET_QOS_DMA_CHX_RXDESC_LIST_ADDR_RDESLA_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_RXDESC_LIST_ADDR */
#define ENET_QOS_DMA_CHX_RXDESC_LIST_ADDR_COUNT  (5U)

/*! @name DMA_CHX_TXDESC_TAIL_PTR - Channel 0 Tx Descriptor Tail Pointer..Channel 4 Tx Descriptor Tail Pointer */
/*! @{ */

#define ENET_QOS_DMA_CHX_TXDESC_TAIL_PTR_TDTP_MASK (0xFFFFFFF8U)
#define ENET_QOS_DMA_CHX_TXDESC_TAIL_PTR_TDTP_SHIFT (3U)
/*! TDTP - Transmit Descriptor Tail Pointer This field contains the tail pointer for the Tx descriptor ring. */
#define ENET_QOS_DMA_CHX_TXDESC_TAIL_PTR_TDTP(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_TXDESC_TAIL_PTR_TDTP_SHIFT)) & ENET_QOS_DMA_CHX_TXDESC_TAIL_PTR_TDTP_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_TXDESC_TAIL_PTR */
#define ENET_QOS_DMA_CHX_TXDESC_TAIL_PTR_COUNT   (5U)

/*! @name DMA_CHX_RXDESC_TAIL_PTR - Channel 0 Rx Descriptor Tail Pointer..Channel 4 Rx Descriptor Tail Pointer */
/*! @{ */

#define ENET_QOS_DMA_CHX_RXDESC_TAIL_PTR_RDTP_MASK (0xFFFFFFF8U)
#define ENET_QOS_DMA_CHX_RXDESC_TAIL_PTR_RDTP_SHIFT (3U)
/*! RDTP - Receive Descriptor Tail Pointer This field contains the tail pointer for the Rx descriptor ring. */
#define ENET_QOS_DMA_CHX_RXDESC_TAIL_PTR_RDTP(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_RXDESC_TAIL_PTR_RDTP_SHIFT)) & ENET_QOS_DMA_CHX_RXDESC_TAIL_PTR_RDTP_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_RXDESC_TAIL_PTR */
#define ENET_QOS_DMA_CHX_RXDESC_TAIL_PTR_COUNT   (5U)

/*! @name DMA_CHX_TXDESC_RING_LENGTH - Channel 0 Tx Descriptor Ring Length..Channel 4 Tx Descriptor Ring Length */
/*! @{ */

#define ENET_QOS_DMA_CHX_TXDESC_RING_LENGTH_TDRL_MASK (0x3FFU)
#define ENET_QOS_DMA_CHX_TXDESC_RING_LENGTH_TDRL_SHIFT (0U)
/*! TDRL - Transmit Descriptor Ring Length This field sets the maximum number of Tx descriptors in the circular descriptor ring. */
#define ENET_QOS_DMA_CHX_TXDESC_RING_LENGTH_TDRL(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_TXDESC_RING_LENGTH_TDRL_SHIFT)) & ENET_QOS_DMA_CHX_TXDESC_RING_LENGTH_TDRL_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_TXDESC_RING_LENGTH */
#define ENET_QOS_DMA_CHX_TXDESC_RING_LENGTH_COUNT (5U)

/*! @name DMA_CHX_RX_CONTROL2 - Channel 0 Receive Control 2 register..DMA Channel 4 Receive Control 2 register */
/*! @{ */

#define ENET_QOS_DMA_CHX_RX_CONTROL2_RDRL_MASK   (0x3FFU)
#define ENET_QOS_DMA_CHX_RX_CONTROL2_RDRL_SHIFT  (0U)
/*! RDRL - Receive Descriptor Ring Length This register sets the maximum number of Rx descriptors in the circular descriptor ring. */
#define ENET_QOS_DMA_CHX_RX_CONTROL2_RDRL(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_RX_CONTROL2_RDRL_SHIFT)) & ENET_QOS_DMA_CHX_RX_CONTROL2_RDRL_MASK)

#define ENET_QOS_DMA_CHX_RX_CONTROL2_ARBS_MASK   (0xFE0000U)
#define ENET_QOS_DMA_CHX_RX_CONTROL2_ARBS_SHIFT  (17U)
/*! ARBS - Alternate Receive Buffer Size */
#define ENET_QOS_DMA_CHX_RX_CONTROL2_ARBS(x)     (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_RX_CONTROL2_ARBS_SHIFT)) & ENET_QOS_DMA_CHX_RX_CONTROL2_ARBS_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_RX_CONTROL2 */
#define ENET_QOS_DMA_CHX_RX_CONTROL2_COUNT       (5U)

/*! @name DMA_CHX_INT_EN - Channel 0 Interrupt Enable..Channel 4 Interrupt Enable */
/*! @{ */

#define ENET_QOS_DMA_CHX_INT_EN_TIE_MASK         (0x1U)
#define ENET_QOS_DMA_CHX_INT_EN_TIE_SHIFT        (0U)
/*! TIE - Transmit Interrupt Enable When this bit is set along with the NIE bit, the Transmit Interrupt is enabled.
 *  0b0..Transmit Interrupt is disabled
 *  0b1..Transmit Interrupt is enabled
 */
#define ENET_QOS_DMA_CHX_INT_EN_TIE(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_INT_EN_TIE_SHIFT)) & ENET_QOS_DMA_CHX_INT_EN_TIE_MASK)

#define ENET_QOS_DMA_CHX_INT_EN_TXSE_MASK        (0x2U)
#define ENET_QOS_DMA_CHX_INT_EN_TXSE_SHIFT       (1U)
/*! TXSE - Transmit Stopped Enable When this bit is set along with the AIE bit, the Transmission Stopped interrupt is enabled.
 *  0b0..Transmit Stopped is disabled
 *  0b1..Transmit Stopped is enabled
 */
#define ENET_QOS_DMA_CHX_INT_EN_TXSE(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_INT_EN_TXSE_SHIFT)) & ENET_QOS_DMA_CHX_INT_EN_TXSE_MASK)

#define ENET_QOS_DMA_CHX_INT_EN_TBUE_MASK        (0x4U)
#define ENET_QOS_DMA_CHX_INT_EN_TBUE_SHIFT       (2U)
/*! TBUE - Transmit Buffer Unavailable Enable When this bit is set along with the NIE bit, the
 *    Transmit Buffer Unavailable interrupt is enabled.
 *  0b0..Transmit Buffer Unavailable is disabled
 *  0b1..Transmit Buffer Unavailable is enabled
 */
#define ENET_QOS_DMA_CHX_INT_EN_TBUE(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_INT_EN_TBUE_SHIFT)) & ENET_QOS_DMA_CHX_INT_EN_TBUE_MASK)

#define ENET_QOS_DMA_CHX_INT_EN_RIE_MASK         (0x40U)
#define ENET_QOS_DMA_CHX_INT_EN_RIE_SHIFT        (6U)
/*! RIE - Receive Interrupt Enable When this bit is set along with the NIE bit, the Receive Interrupt is enabled.
 *  0b0..Receive Interrupt is disabled
 *  0b1..Receive Interrupt is enabled
 */
#define ENET_QOS_DMA_CHX_INT_EN_RIE(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_INT_EN_RIE_SHIFT)) & ENET_QOS_DMA_CHX_INT_EN_RIE_MASK)

#define ENET_QOS_DMA_CHX_INT_EN_RBUE_MASK        (0x80U)
#define ENET_QOS_DMA_CHX_INT_EN_RBUE_SHIFT       (7U)
/*! RBUE - Receive Buffer Unavailable Enable When this bit is set along with the AIE bit, the
 *    Receive Buffer Unavailable interrupt is enabled.
 *  0b0..Receive Buffer Unavailable is disabled
 *  0b1..Receive Buffer Unavailable is enabled
 */
#define ENET_QOS_DMA_CHX_INT_EN_RBUE(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_INT_EN_RBUE_SHIFT)) & ENET_QOS_DMA_CHX_INT_EN_RBUE_MASK)

#define ENET_QOS_DMA_CHX_INT_EN_RSE_MASK         (0x100U)
#define ENET_QOS_DMA_CHX_INT_EN_RSE_SHIFT        (8U)
/*! RSE - Receive Stopped Enable When this bit is set along with the AIE bit, the Receive Stopped Interrupt is enabled.
 *  0b0..Receive Stopped is disabled
 *  0b1..Receive Stopped is enabled
 */
#define ENET_QOS_DMA_CHX_INT_EN_RSE(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_INT_EN_RSE_SHIFT)) & ENET_QOS_DMA_CHX_INT_EN_RSE_MASK)

#define ENET_QOS_DMA_CHX_INT_EN_RWTE_MASK        (0x200U)
#define ENET_QOS_DMA_CHX_INT_EN_RWTE_SHIFT       (9U)
/*! RWTE - Receive Watchdog Timeout Enable When this bit is set along with the AIE bit, the Receive
 *    Watchdog Timeout interrupt is enabled.
 *  0b0..Receive Watchdog Timeout is disabled
 *  0b1..Receive Watchdog Timeout is enabled
 */
#define ENET_QOS_DMA_CHX_INT_EN_RWTE(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_INT_EN_RWTE_SHIFT)) & ENET_QOS_DMA_CHX_INT_EN_RWTE_MASK)

#define ENET_QOS_DMA_CHX_INT_EN_ETIE_MASK        (0x400U)
#define ENET_QOS_DMA_CHX_INT_EN_ETIE_SHIFT       (10U)
/*! ETIE - Early Transmit Interrupt Enable When this bit is set along with the AIE bit, the Early Transmit interrupt is enabled.
 *  0b0..Early Transmit Interrupt is disabled
 *  0b1..Early Transmit Interrupt is enabled
 */
#define ENET_QOS_DMA_CHX_INT_EN_ETIE(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_INT_EN_ETIE_SHIFT)) & ENET_QOS_DMA_CHX_INT_EN_ETIE_MASK)

#define ENET_QOS_DMA_CHX_INT_EN_ERIE_MASK        (0x800U)
#define ENET_QOS_DMA_CHX_INT_EN_ERIE_SHIFT       (11U)
/*! ERIE - Early Receive Interrupt Enable When this bit is set along with the NIE bit, the Early Receive interrupt is enabled.
 *  0b0..Early Receive Interrupt is disabled
 *  0b1..Early Receive Interrupt is enabled
 */
#define ENET_QOS_DMA_CHX_INT_EN_ERIE(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_INT_EN_ERIE_SHIFT)) & ENET_QOS_DMA_CHX_INT_EN_ERIE_MASK)

#define ENET_QOS_DMA_CHX_INT_EN_FBEE_MASK        (0x1000U)
#define ENET_QOS_DMA_CHX_INT_EN_FBEE_SHIFT       (12U)
/*! FBEE - Fatal Bus Error Enable When this bit is set along with the AIE bit, the Fatal Bus error interrupt is enabled.
 *  0b0..Fatal Bus Error is disabled
 *  0b1..Fatal Bus Error is enabled
 */
#define ENET_QOS_DMA_CHX_INT_EN_FBEE(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_INT_EN_FBEE_SHIFT)) & ENET_QOS_DMA_CHX_INT_EN_FBEE_MASK)

#define ENET_QOS_DMA_CHX_INT_EN_CDEE_MASK        (0x2000U)
#define ENET_QOS_DMA_CHX_INT_EN_CDEE_SHIFT       (13U)
/*! CDEE - Context Descriptor Error Enable When this bit is set along with the AIE bit, the Descriptor error interrupt is enabled.
 *  0b0..Context Descriptor Error is disabled
 *  0b1..Context Descriptor Error is enabled
 */
#define ENET_QOS_DMA_CHX_INT_EN_CDEE(x)          (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_INT_EN_CDEE_SHIFT)) & ENET_QOS_DMA_CHX_INT_EN_CDEE_MASK)

#define ENET_QOS_DMA_CHX_INT_EN_AIE_MASK         (0x4000U)
#define ENET_QOS_DMA_CHX_INT_EN_AIE_SHIFT        (14U)
/*! AIE - Abnormal Interrupt Summary Enable When this bit is set, the abnormal interrupt summary is enabled.
 *  0b0..Abnormal Interrupt Summary is disabled
 *  0b1..Abnormal Interrupt Summary is enabled
 */
#define ENET_QOS_DMA_CHX_INT_EN_AIE(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_INT_EN_AIE_SHIFT)) & ENET_QOS_DMA_CHX_INT_EN_AIE_MASK)

#define ENET_QOS_DMA_CHX_INT_EN_NIE_MASK         (0x8000U)
#define ENET_QOS_DMA_CHX_INT_EN_NIE_SHIFT        (15U)
/*! NIE - Normal Interrupt Summary Enable When this bit is set, the normal interrupt summary is enabled.
 *  0b0..Normal Interrupt Summary is disabled
 *  0b1..Normal Interrupt Summary is enabled
 */
#define ENET_QOS_DMA_CHX_INT_EN_NIE(x)           (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_INT_EN_NIE_SHIFT)) & ENET_QOS_DMA_CHX_INT_EN_NIE_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_INT_EN */
#define ENET_QOS_DMA_CHX_INT_EN_COUNT            (5U)

/*! @name DMA_CHX_RX_INT_WDTIMER - Channel 0 Receive Interrupt Watchdog Timer..Channel 4 Receive Interrupt Watchdog Timer */
/*! @{ */

#define ENET_QOS_DMA_CHX_RX_INT_WDTIMER_RWT_MASK (0xFFU)
#define ENET_QOS_DMA_CHX_RX_INT_WDTIMER_RWT_SHIFT (0U)
/*! RWT - Receive Interrupt Watchdog Timer Count This field indicates the number of system clock
 *    cycles, multiplied by factor indicated in RWTU field, for which the watchdog timer is set.
 */
#define ENET_QOS_DMA_CHX_RX_INT_WDTIMER_RWT(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_RX_INT_WDTIMER_RWT_SHIFT)) & ENET_QOS_DMA_CHX_RX_INT_WDTIMER_RWT_MASK)

#define ENET_QOS_DMA_CHX_RX_INT_WDTIMER_RWTU_MASK (0x30000U)
#define ENET_QOS_DMA_CHX_RX_INT_WDTIMER_RWTU_SHIFT (16U)
/*! RWTU - Receive Interrupt Watchdog Timer Count Units This fields indicates the number of system
 *    clock cycles corresponding to one unit in RWT field.
 */
#define ENET_QOS_DMA_CHX_RX_INT_WDTIMER_RWTU(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_RX_INT_WDTIMER_RWTU_SHIFT)) & ENET_QOS_DMA_CHX_RX_INT_WDTIMER_RWTU_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_RX_INT_WDTIMER */
#define ENET_QOS_DMA_CHX_RX_INT_WDTIMER_COUNT    (5U)

/*! @name DMA_CHX_SLOT_FUNC_CTRL_STAT - Channel 0 Slot Function Control and Status..Channel 4 Slot Function Control and Status */
/*! @{ */

#define ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_ESC_MASK (0x1U)
#define ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_ESC_SHIFT (0U)
/*! ESC - Enable Slot Comparison When set, this bit enables the checking of the slot numbers
 *    programmed in the Tx descriptor with the current reference given in the RSN field.
 *  0b0..Slot Comparison is disabled
 *  0b1..Slot Comparison is enabled
 */
#define ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_ESC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_ESC_SHIFT)) & ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_ESC_MASK)

#define ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_ASC_MASK (0x2U)
#define ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_ASC_SHIFT (1U)
/*! ASC - Advance Slot Check When set, this bit enables the DMA to fetch the data from the buffer
 *    when the slot number (SLOTNUM) programmed in the Tx descriptor is - equal to the reference slot
 *    number given in the RSN field or - ahead of the reference slot number by up to two slots This
 *    bit is applicable only when the ESC bit is set.
 *  0b0..Advance Slot Check is disabled
 *  0b1..Advance Slot Check is enabled
 */
#define ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_ASC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_ASC_SHIFT)) & ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_ASC_MASK)

#define ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_SIV_MASK (0xFFF0U)
#define ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_SIV_SHIFT (4U)
/*! SIV - Slot Interval Value This field controls the period of the slot interval in which the TxDMA
 *    fetches the scheduled packets.
 */
#define ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_SIV(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_SIV_SHIFT)) & ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_SIV_MASK)

#define ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_RSN_MASK (0xF0000U)
#define ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_RSN_SHIFT (16U)
/*! RSN - Reference Slot Number This field gives the current value of the reference slot number in the DMA. */
#define ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_RSN(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_RSN_SHIFT)) & ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_RSN_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT */
#define ENET_QOS_DMA_CHX_SLOT_FUNC_CTRL_STAT_COUNT (5U)

/*! @name DMA_CHX_CUR_HST_TXDESC - Channel 0 Current Application Transmit Descriptor..Channel 4 Current Application Transmit Descriptor */
/*! @{ */

#define ENET_QOS_DMA_CHX_CUR_HST_TXDESC_CURTDESAPTR_MASK (0xFFFFFFFFU)
#define ENET_QOS_DMA_CHX_CUR_HST_TXDESC_CURTDESAPTR_SHIFT (0U)
/*! CURTDESAPTR - Application Transmit Descriptor Address Pointer The DMA updates this pointer during Tx operation. */
#define ENET_QOS_DMA_CHX_CUR_HST_TXDESC_CURTDESAPTR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_CUR_HST_TXDESC_CURTDESAPTR_SHIFT)) & ENET_QOS_DMA_CHX_CUR_HST_TXDESC_CURTDESAPTR_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_CUR_HST_TXDESC */
#define ENET_QOS_DMA_CHX_CUR_HST_TXDESC_COUNT    (5U)

/*! @name DMA_CHX_CUR_HST_RXDESC - Channel 0 Current Application Receive Descriptor..Channel 4 Current Application Receive Descriptor */
/*! @{ */

#define ENET_QOS_DMA_CHX_CUR_HST_RXDESC_CURRDESAPTR_MASK (0xFFFFFFFFU)
#define ENET_QOS_DMA_CHX_CUR_HST_RXDESC_CURRDESAPTR_SHIFT (0U)
/*! CURRDESAPTR - Application Receive Descriptor Address Pointer The DMA updates this pointer during Rx operation. */
#define ENET_QOS_DMA_CHX_CUR_HST_RXDESC_CURRDESAPTR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_CUR_HST_RXDESC_CURRDESAPTR_SHIFT)) & ENET_QOS_DMA_CHX_CUR_HST_RXDESC_CURRDESAPTR_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_CUR_HST_RXDESC */
#define ENET_QOS_DMA_CHX_CUR_HST_RXDESC_COUNT    (5U)

/*! @name DMA_CHX_CUR_HST_TXBUF - Channel 0 Current Application Transmit Buffer Address..Channel 4 Current Application Transmit Buffer Address */
/*! @{ */

#define ENET_QOS_DMA_CHX_CUR_HST_TXBUF_CURTBUFAPTR_MASK (0xFFFFFFFFU)
#define ENET_QOS_DMA_CHX_CUR_HST_TXBUF_CURTBUFAPTR_SHIFT (0U)
/*! CURTBUFAPTR - Application Transmit Buffer Address Pointer The DMA updates this pointer during Tx operation. */
#define ENET_QOS_DMA_CHX_CUR_HST_TXBUF_CURTBUFAPTR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_CUR_HST_TXBUF_CURTBUFAPTR_SHIFT)) & ENET_QOS_DMA_CHX_CUR_HST_TXBUF_CURTBUFAPTR_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_CUR_HST_TXBUF */
#define ENET_QOS_DMA_CHX_CUR_HST_TXBUF_COUNT     (5U)

/*! @name DMA_CHX_CUR_HST_RXBUF - Channel 0 Current Application Receive Buffer Address..Channel 4 Current Application Receive Buffer Address */
/*! @{ */

#define ENET_QOS_DMA_CHX_CUR_HST_RXBUF_CURRBUFAPTR_MASK (0xFFFFFFFFU)
#define ENET_QOS_DMA_CHX_CUR_HST_RXBUF_CURRBUFAPTR_SHIFT (0U)
/*! CURRBUFAPTR - Application Receive Buffer Address Pointer The DMA updates this pointer during Rx operation. */
#define ENET_QOS_DMA_CHX_CUR_HST_RXBUF_CURRBUFAPTR(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_CUR_HST_RXBUF_CURRBUFAPTR_SHIFT)) & ENET_QOS_DMA_CHX_CUR_HST_RXBUF_CURRBUFAPTR_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_CUR_HST_RXBUF */
#define ENET_QOS_DMA_CHX_CUR_HST_RXBUF_COUNT     (5U)

/*! @name DMA_CHX_STAT - DMA Channel 0 Status..DMA Channel 4 Status */
/*! @{ */

#define ENET_QOS_DMA_CHX_STAT_TI_MASK            (0x1U)
#define ENET_QOS_DMA_CHX_STAT_TI_SHIFT           (0U)
/*! TI - Transmit Interrupt This bit indicates that the packet transmission is complete.
 *  0b0..Transmit Interrupt status not detected
 *  0b1..Transmit Interrupt status detected
 */
#define ENET_QOS_DMA_CHX_STAT_TI(x)              (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_STAT_TI_SHIFT)) & ENET_QOS_DMA_CHX_STAT_TI_MASK)

#define ENET_QOS_DMA_CHX_STAT_TPS_MASK           (0x2U)
#define ENET_QOS_DMA_CHX_STAT_TPS_SHIFT          (1U)
/*! TPS - Transmit Process Stopped This bit is set when the transmission is stopped.
 *  0b0..Transmit Process Stopped status not detected
 *  0b1..Transmit Process Stopped status detected
 */
#define ENET_QOS_DMA_CHX_STAT_TPS(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_STAT_TPS_SHIFT)) & ENET_QOS_DMA_CHX_STAT_TPS_MASK)

#define ENET_QOS_DMA_CHX_STAT_TBU_MASK           (0x4U)
#define ENET_QOS_DMA_CHX_STAT_TBU_SHIFT          (2U)
/*! TBU - Transmit Buffer Unavailable This bit indicates that the application owns the next
 *    descriptor in the Transmit list, and the DMA cannot acquire it.
 *  0b0..Transmit Buffer Unavailable status not detected
 *  0b1..Transmit Buffer Unavailable status detected
 */
#define ENET_QOS_DMA_CHX_STAT_TBU(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_STAT_TBU_SHIFT)) & ENET_QOS_DMA_CHX_STAT_TBU_MASK)

#define ENET_QOS_DMA_CHX_STAT_RI_MASK            (0x40U)
#define ENET_QOS_DMA_CHX_STAT_RI_SHIFT           (6U)
/*! RI - Receive Interrupt This bit indicates that the packet reception is complete.
 *  0b0..Receive Interrupt status not detected
 *  0b1..Receive Interrupt status detected
 */
#define ENET_QOS_DMA_CHX_STAT_RI(x)              (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_STAT_RI_SHIFT)) & ENET_QOS_DMA_CHX_STAT_RI_MASK)

#define ENET_QOS_DMA_CHX_STAT_RBU_MASK           (0x80U)
#define ENET_QOS_DMA_CHX_STAT_RBU_SHIFT          (7U)
/*! RBU - Receive Buffer Unavailable This bit indicates that the application owns the next
 *    descriptor in the Receive list, and the DMA cannot acquire it.
 *  0b0..Receive Buffer Unavailable status not detected
 *  0b1..Receive Buffer Unavailable status detected
 */
#define ENET_QOS_DMA_CHX_STAT_RBU(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_STAT_RBU_SHIFT)) & ENET_QOS_DMA_CHX_STAT_RBU_MASK)

#define ENET_QOS_DMA_CHX_STAT_RPS_MASK           (0x100U)
#define ENET_QOS_DMA_CHX_STAT_RPS_SHIFT          (8U)
/*! RPS - Receive Process Stopped This bit is asserted when the Rx process enters the Stopped state.
 *  0b0..Receive Process Stopped status not detected
 *  0b1..Receive Process Stopped status detected
 */
#define ENET_QOS_DMA_CHX_STAT_RPS(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_STAT_RPS_SHIFT)) & ENET_QOS_DMA_CHX_STAT_RPS_MASK)

#define ENET_QOS_DMA_CHX_STAT_RWT_MASK           (0x200U)
#define ENET_QOS_DMA_CHX_STAT_RWT_SHIFT          (9U)
/*! RWT - Receive Watchdog Timeout This bit is asserted when a packet with length greater than 2,048
 *    bytes (10,240 bytes when Jumbo Packet mode is enabled) is received.
 *  0b0..Receive Watchdog Timeout status not detected
 *  0b1..Receive Watchdog Timeout status detected
 */
#define ENET_QOS_DMA_CHX_STAT_RWT(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_STAT_RWT_SHIFT)) & ENET_QOS_DMA_CHX_STAT_RWT_MASK)

#define ENET_QOS_DMA_CHX_STAT_ETI_MASK           (0x400U)
#define ENET_QOS_DMA_CHX_STAT_ETI_SHIFT          (10U)
/*! ETI - Early Transmit Interrupt This bit when set indicates that the TxDMA has completed the
 *    transfer of packet data to the MTL TXFIFO memory.
 *  0b0..Early Transmit Interrupt status not detected
 *  0b1..Early Transmit Interrupt status detected
 */
#define ENET_QOS_DMA_CHX_STAT_ETI(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_STAT_ETI_SHIFT)) & ENET_QOS_DMA_CHX_STAT_ETI_MASK)

#define ENET_QOS_DMA_CHX_STAT_ERI_MASK           (0x800U)
#define ENET_QOS_DMA_CHX_STAT_ERI_SHIFT          (11U)
/*! ERI - Early Receive Interrupt This bit when set indicates that the RxDMA has completed the
 *    transfer of packet data to the memory.
 *  0b0..Early Receive Interrupt status not detected
 *  0b1..Early Receive Interrupt status detected
 */
#define ENET_QOS_DMA_CHX_STAT_ERI(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_STAT_ERI_SHIFT)) & ENET_QOS_DMA_CHX_STAT_ERI_MASK)

#define ENET_QOS_DMA_CHX_STAT_FBE_MASK           (0x1000U)
#define ENET_QOS_DMA_CHX_STAT_FBE_SHIFT          (12U)
/*! FBE - Fatal Bus Error This bit indicates that a bus error occurred (as described in the EB field).
 *  0b0..Fatal Bus Error status not detected
 *  0b1..Fatal Bus Error status detected
 */
#define ENET_QOS_DMA_CHX_STAT_FBE(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_STAT_FBE_SHIFT)) & ENET_QOS_DMA_CHX_STAT_FBE_MASK)

#define ENET_QOS_DMA_CHX_STAT_CDE_MASK           (0x2000U)
#define ENET_QOS_DMA_CHX_STAT_CDE_SHIFT          (13U)
/*! CDE - Context Descriptor Error This bit indicates that the DMA Tx/Rx engine received a
 *    descriptor error, which indicates invalid context in the middle of packet flow ( intermediate
 *    descriptor) or all one's descriptor in Tx case and on Rx side it indicates DMA has read a descriptor
 *    with either of the buffer address as ones which is considered to be invalid.
 *  0b0..Context Descriptor Error status not detected
 *  0b1..Context Descriptor Error status detected
 */
#define ENET_QOS_DMA_CHX_STAT_CDE(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_STAT_CDE_SHIFT)) & ENET_QOS_DMA_CHX_STAT_CDE_MASK)

#define ENET_QOS_DMA_CHX_STAT_AIS_MASK           (0x4000U)
#define ENET_QOS_DMA_CHX_STAT_AIS_SHIFT          (14U)
/*! AIS - Abnormal Interrupt Summary Abnormal Interrupt Summary bit value is the logical OR of the
 *    following when the corresponding interrupt bits are enabled in the DMA_CH3_INTERRUPT_ENABLE
 *    register: - Bit 1: Transmit Process Stopped - Bit 7: Receive Buffer Unavailable - Bit 8: Receive
 *    Process Stopped - Bit 10: Early Transmit Interrupt - Bit 12: Fatal Bus Error - Bit 13: Context
 *    Descriptor Error Only unmasked bits affect the Abnormal Interrupt Summary bit.
 *  0b0..Abnormal Interrupt Summary status not detected
 *  0b1..Abnormal Interrupt Summary status detected
 */
#define ENET_QOS_DMA_CHX_STAT_AIS(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_STAT_AIS_SHIFT)) & ENET_QOS_DMA_CHX_STAT_AIS_MASK)

#define ENET_QOS_DMA_CHX_STAT_NIS_MASK           (0x8000U)
#define ENET_QOS_DMA_CHX_STAT_NIS_SHIFT          (15U)
/*! NIS - Normal Interrupt Summary Normal Interrupt Summary bit value is the logical OR of the
 *    following bits when the corresponding interrupt bits are enabled in the DMA_CH3_INTERRUPT_ENABLE
 *    register: - Bit 0: Transmit Interrupt - Bit 2: Transmit Buffer Unavailable - Bit 6: Receive
 *    Interrupt - Bit 11: Early Receive Interrupt Only unmasked bits (interrupts for which interrupt
 *    enable is set in DMA_CH3_INTERRUPT_ENABLE register) affect the Normal Interrupt Summary bit.
 *  0b0..Normal Interrupt Summary status not detected
 *  0b1..Normal Interrupt Summary status detected
 */
#define ENET_QOS_DMA_CHX_STAT_NIS(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_STAT_NIS_SHIFT)) & ENET_QOS_DMA_CHX_STAT_NIS_MASK)

#define ENET_QOS_DMA_CHX_STAT_TEB_MASK           (0x70000U)
#define ENET_QOS_DMA_CHX_STAT_TEB_SHIFT          (16U)
/*! TEB - Tx DMA Error Bits This field indicates the type of error that caused a Bus Error. */
#define ENET_QOS_DMA_CHX_STAT_TEB(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_STAT_TEB_SHIFT)) & ENET_QOS_DMA_CHX_STAT_TEB_MASK)

#define ENET_QOS_DMA_CHX_STAT_REB_MASK           (0x380000U)
#define ENET_QOS_DMA_CHX_STAT_REB_SHIFT          (19U)
/*! REB - Rx DMA Error Bits This field indicates the type of error that caused a Bus Error. */
#define ENET_QOS_DMA_CHX_STAT_REB(x)             (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_STAT_REB_SHIFT)) & ENET_QOS_DMA_CHX_STAT_REB_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_STAT */
#define ENET_QOS_DMA_CHX_STAT_COUNT              (5U)

/*! @name DMA_CHX_MISS_FRAME_CNT - Channel 0 Missed Frame Counter..Channel 4 Missed Frame Counter */
/*! @{ */

#define ENET_QOS_DMA_CHX_MISS_FRAME_CNT_MFC_MASK (0x7FFU)
#define ENET_QOS_DMA_CHX_MISS_FRAME_CNT_MFC_SHIFT (0U)
/*! MFC - Dropped Packet Counters This counter indicates the number of packet counters that are
 *    dropped by the DMA either because of bus error or because of programming RPF field in
 *    DMA_CH2_RX_CONTROL register.
 */
#define ENET_QOS_DMA_CHX_MISS_FRAME_CNT_MFC(x)   (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_MISS_FRAME_CNT_MFC_SHIFT)) & ENET_QOS_DMA_CHX_MISS_FRAME_CNT_MFC_MASK)

#define ENET_QOS_DMA_CHX_MISS_FRAME_CNT_MFCO_MASK (0x8000U)
#define ENET_QOS_DMA_CHX_MISS_FRAME_CNT_MFCO_SHIFT (15U)
/*! MFCO - Overflow status of the MFC Counter When this bit is set then the MFC counter does not get incremented further.
 *  0b0..Miss Frame Counter overflow not occurred
 *  0b1..Miss Frame Counter overflow occurred
 */
#define ENET_QOS_DMA_CHX_MISS_FRAME_CNT_MFCO(x)  (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_MISS_FRAME_CNT_MFCO_SHIFT)) & ENET_QOS_DMA_CHX_MISS_FRAME_CNT_MFCO_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_MISS_FRAME_CNT */
#define ENET_QOS_DMA_CHX_MISS_FRAME_CNT_COUNT    (5U)

/*! @name DMA_CHX_RXP_ACCEPT_CNT - Channel 0 RXP Frames Accepted Counter..Channel 4 RXP Frames Accepted Counter */
/*! @{ */

#define ENET_QOS_DMA_CHX_RXP_ACCEPT_CNT_RXPAC_MASK (0x7FFFFFFFU)
#define ENET_QOS_DMA_CHX_RXP_ACCEPT_CNT_RXPAC_SHIFT (0U)
/*! RXPAC - Rx Parser Accept Counter This 31-bit counter is implemented whenever a Rx Parser Accept a packet due to AF =1. */
#define ENET_QOS_DMA_CHX_RXP_ACCEPT_CNT_RXPAC(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_RXP_ACCEPT_CNT_RXPAC_SHIFT)) & ENET_QOS_DMA_CHX_RXP_ACCEPT_CNT_RXPAC_MASK)

#define ENET_QOS_DMA_CHX_RXP_ACCEPT_CNT_RXPACOF_MASK (0x80000000U)
#define ENET_QOS_DMA_CHX_RXP_ACCEPT_CNT_RXPACOF_SHIFT (31U)
/*! RXPACOF - Rx Parser Accept Counter Overflow Bit When set, this bit indicates that the RXPAC
 *    Counter field crossed the maximum limit.
 *  0b0..Rx Parser Accept Counter overflow not occurred
 *  0b1..Rx Parser Accept Counter overflow occurred
 */
#define ENET_QOS_DMA_CHX_RXP_ACCEPT_CNT_RXPACOF(x) (((uint32_t)(((uint32_t)(x)) << ENET_QOS_DMA_CHX_RXP_ACCEPT_CNT_RXPACOF_SHIFT)) & ENET_QOS_DMA_CHX_RXP_ACCEPT_CNT_RXPACOF_MASK)
/*! @} */

/* The count of ENET_QOS_DMA_CHX_RXP_ACCEPT_CNT */
#define ENET_QOS_DMA_CHX_RXP_ACCEPT_CNT_COUNT    (5U)


/*!
 * @}
 */ /* end of group ENET_QOS_Register_Masks */


/*!
 * @}
 */ /* end of group ENET_QOS_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__CWCC__)
  #pragma pop
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


#endif  /* PERI_ENET_QOS_H_ */

