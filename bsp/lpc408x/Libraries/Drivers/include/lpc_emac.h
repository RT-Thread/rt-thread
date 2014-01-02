/**********************************************************************
* $Id$      lpc_emac.h          2011-06-02
*//**
* @file     lpc_emac.h
* @brief    Contains all macro definitions and function prototypes
*           support for Ethernet MAC firmware library on LPC
* @version  1.0
* @date     02. June. 2011
* @author   NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup EMAC  EMAC (Ethernet Media Access Controller)
 * @ingroup LPC_CMSIS_FwLib_Drivers
 * @{
 */

#ifndef __LPC_EMAC_H_
#define __LPC_EMAC_H_

#include "LPC407x_8x_177x_8x.h"
#include "lpc_types.h"


#ifdef __cplusplus
extern "C"
{
#endif

/** @defgroup EMAC_Private_Macros EMAC Private Macros
 * @{
 */

/* Ethernet MAC register definitions --------------------------------------------------------------------- */
/* MAC Configuration Register 1 */
#define EMAC_MAC1_MASK      0xcf1f      /*MAC1 register mask*/
#define EMAC_MAC1_REC_EN         0x00000001  /**< Receive Enable                    */
#define EMAC_MAC1_PASS_ALL       0x00000002  /**< Pass All Receive Frames           */
#define EMAC_MAC1_RX_FLOWC       0x00000004  /**< RX Flow Control                   */
#define EMAC_MAC1_TX_FLOWC       0x00000008  /**< TX Flow Control                   */
#define EMAC_MAC1_LOOPB          0x00000010  /**< Loop Back Mode                    */
#define EMAC_MAC1_RES_TX         0x00000100  /**< Reset TX Logic                    */
#define EMAC_MAC1_RES_MCS_TX     0x00000200  /**< Reset MAC TX Control Sublayer     */
#define EMAC_MAC1_RES_RX         0x00000400  /**< Reset RX Logic                    */
#define EMAC_MAC1_RES_MCS_RX     0x00000800  /**< Reset MAC RX Control Sublayer     */
#define EMAC_MAC1_SIM_RES        0x00004000  /**< Simulation Reset                  */
#define EMAC_MAC1_SOFT_RES       0x00008000  /**< Soft Reset MAC                    */

/* MAC Configuration Register 2 */
#define EMAC_MAC2_MASK      0x73ff      /*MAC2 register mask*/
#define EMAC_MAC2_FULL_DUP       0x00000001  /**< Full-Duplex Mode                  */
#define EMAC_MAC2_FRM_LEN_CHK    0x00000002  /**< Frame Length Checking             */
#define EMAC_MAC2_HUGE_FRM_EN    0x00000004  /**< Huge Frame Enable                 */
#define EMAC_MAC2_DLY_CRC        0x00000008  /**< Delayed CRC Mode                  */
#define EMAC_MAC2_CRC_EN         0x00000010  /**< Append CRC to every Frame         */
#define EMAC_MAC2_PAD_EN         0x00000020  /**< Pad all Short Frames              */
#define EMAC_MAC2_VLAN_PAD_EN    0x00000040  /**< VLAN Pad Enable                   */
#define EMAC_MAC2_ADET_PAD_EN    0x00000080  /**< Auto Detect Pad Enable            */
#define EMAC_MAC2_PPREAM_ENF     0x00000100  /**< Pure Preamble Enforcement         */
#define EMAC_MAC2_LPREAM_ENF     0x00000200  /**< Long Preamble Enforcement         */
#define EMAC_MAC2_NO_BACKOFF     0x00001000  /**< No Backoff Algorithm              */
#define EMAC_MAC2_BACK_PRESSURE  0x00002000  /**< Backoff Presurre / No Backoff     */
#define EMAC_MAC2_EXCESS_DEF     0x00004000  /**< Excess Defer                      */

/* Back-to-Back Inter-Packet-Gap Register */
/** Programmable field representing the nibble time offset of the minimum possible period
 * between the end of any transmitted packet to the beginning of the next */
#define EMAC_IPGT_BBIPG(n)      (n&0x7F)

/** Recommended value for Full Duplex of Programmable field representing the nibble time
 * offset of the minimum possible period between the end of any transmitted packet to the
 * beginning of the next */
#define EMAC_IPGT_FULL_DUP      (EMAC_IPGT_BBIPG(0x15))

/** Recommended value for Half Duplex of Programmable field representing the nibble time
 * offset of the minimum possible period between the end of any transmitted packet to the
 * beginning of the next */
#define EMAC_IPGT_HALF_DUP      (EMAC_IPGT_BBIPG(0x12))

/* Non Back-to-Back Inter-Packet-Gap Register */
/** Programmable field representing the Non-Back-to-Back Inter-Packet-Gap */
#define EMAC_IPGR_NBBIPG_P2(n)  (n&0x7F)

/** Recommended value for Programmable field representing the Non-Back-to-Back Inter-Packet-Gap Part 1 */
#define EMAC_IPGR_P2_DEF        (EMAC_IPGR_NBBIPG_P2(0x12))

/** Programmable field representing the optional carrierSense window referenced in
 * IEEE 802.3/4.2.3.2.1 'Carrier Deference' */
#define EMAC_IPGR_NBBIPG_P1(n)  ((n&0x7F)<<8)

/** Recommended value for Programmable field representing the Non-Back-to-Back Inter-Packet-Gap Part 2 */
#define EMAC_IPGR_P1_DEF        EMAC_IPGR_NBBIPG_P1(0x0C)

/* Collision Window/Retry Register */
/** Programmable field specifying the number of retransmission attempts following a collision before
 * aborting the packet due to excessive collisions */
#define EMAC_CLRT_MAX_RETX(n)   (n&0x0F)

/** Programmable field representing the slot time or collision window during which collisions occur
 * in properly configured networks */
#define EMAC_CLRT_COLL(n)       ((n&0x3F)<<8)

/** Default value for Collision Window / Retry register */
#define EMAC_CLRT_DEF           ((EMAC_CLRT_MAX_RETX(0x0F))|(EMAC_CLRT_COLL(0x37)))

/* Maximum Frame Register */
/** Represents a maximum receive frame of 1536 octets */
#define EMAC_MAXF_MAXFRMLEN(n)  (n&0xFFFF)
#define EMAC_MAXF_MAXFRMLEN_DEF (0x6000)

/* PHY Support Register */
#define EMAC_SUPP_SPEED         0x00000100      /**< Reduced MII Logic Current Speed   */
//#define EMAC_SUPP_RES_RMII      0x00000800    /**< Reset Reduced MII Logic           */

/* Test Register */
#define EMAC_TEST_SHCUT_PQUANTA  0x00000001     /**< Shortcut Pause Quanta             */
#define EMAC_TEST_TST_PAUSE      0x00000002     /**< Test Pause                        */
#define EMAC_TEST_TST_BACKP      0x00000004     /**< Test Back Pressure                */

/* MII Management Configuration Register */
#define EMAC_MCFG_SCAN_INC       0x00000001     /**< Scan Increment PHY Address        */
#define EMAC_MCFG_SUPP_PREAM     0x00000002     /**< Suppress Preamble                 */
#define EMAC_MCFG_CLK_SEL(n)     ((n&0x0F)<<2)  /**< Clock Select Field                 */
#define EMAC_MCFG_RES_MII        0x00008000     /**< Reset MII Management Hardware     */
#define EMAC_MCFG_MII_MAXCLK     2500000UL      /**< MII Clock max */

/* MII Management Command Register */
#define EMAC_MCMD_READ           0x00000001     /**< MII Read                          */
#define EMAC_MCMD_SCAN           0x00000002     /**< MII Scan continuously             */

#define EMAC_MII_WR_TOUT         0x00050000     /**< MII Write timeout count           */
#define EMAC_MII_RD_TOUT         0x00050000     /**< MII Read timeout count            */

/* MII Management Address Register */
#define EMAC_MADR_REG_ADR(n)     (n&0x1F)       /**< MII Register Address field         */
#define EMAC_MADR_PHY_ADR(n)     ((n&0x1F)<<8)  /**< PHY Address Field                  */

/* MII Management Write Data Register */
#define EMAC_MWTD_DATA(n)       (n&0xFFFF)      /**< Data field for MMI Management Write Data register */

/* MII Management Read Data Register */
#define EMAC_MRDD_DATA(n)       (n&0xFFFF)      /**< Data field for MMI Management Read Data register */

/* MII Management Indicators Register */
#define EMAC_MIND_BUSY           0x00000001     /**< MII is Busy                       */
#define EMAC_MIND_SCAN           0x00000002     /**< MII Scanning in Progress          */
#define EMAC_MIND_NOT_VAL        0x00000004     /**< MII Read Data not valid           */
#define EMAC_MIND_MII_LINK_FAIL  0x00000008     /**< MII Link Failed                   */

/* Station Address 0 Register */
/* Station Address 1 Register */
/* Station Address 2 Register */


/* Control register definitions --------------------------------------------------------------------------- */
/* Command Register */
#define EMAC_CR_RX_EN            0x00000001     /**< Enable Receive                    */
#define EMAC_CR_TX_EN            0x00000002     /**< Enable Transmit                   */
#define EMAC_CR_REG_RES          0x00000008     /**< Reset Host Registers              */
#define EMAC_CR_TX_RES           0x00000010     /**< Reset Transmit Datapath           */
#define EMAC_CR_RX_RES           0x00000020     /**< Reset Receive Datapath            */
#define EMAC_CR_PASS_RUNT_FRM    0x00000040     /**< Pass Runt Frames                  */
#define EMAC_CR_PASS_RX_FILT     0x00000080     /**< Pass RX Filter                    */
#define EMAC_CR_TX_FLOW_CTRL     0x00000100     /**< TX Flow Control                   */
#define EMAC_CR_RMII             0x00000200     /**< Reduced MII Interface             */
#define EMAC_CR_FULL_DUP         0x00000400     /**< Full Duplex                       */

/* Status Register */
#define EMAC_SR_RX_EN            0x00000001     /**< Enable Receive                    */
#define EMAC_SR_TX_EN            0x00000002     /**< Enable Transmit                   */

/* Receive Descriptor Base Address Register */
//

/* Receive Status Base Address Register */
//

/* Receive Number of Descriptors Register */
//

/* Receive Produce Index Register */
//

/* Receive Consume Index Register */
//

/* Transmit Descriptor Base Address Register */
//

/* Transmit Status Base Address Register */
//

/* Transmit Number of Descriptors Register */
//

/* Transmit Produce Index Register */
//

/* Transmit Consume Index Register */
//

/* Transmit Status Vector 0 Register */
#define EMAC_TSV0_CRC_ERR        0x00000001  /**< CRC error                         */
#define EMAC_TSV0_LEN_CHKERR     0x00000002  /**< Length Check Error                */
#define EMAC_TSV0_LEN_OUTRNG     0x00000004  /**< Length Out of Range               */
#define EMAC_TSV0_DONE           0x00000008  /**< Tramsmission Completed            */
#define EMAC_TSV0_MCAST          0x00000010  /**< Multicast Destination             */
#define EMAC_TSV0_BCAST          0x00000020  /**< Broadcast Destination             */
#define EMAC_TSV0_PKT_DEFER      0x00000040  /**< Packet Deferred                   */
#define EMAC_TSV0_EXC_DEFER      0x00000080  /**< Excessive Packet Deferral         */
#define EMAC_TSV0_EXC_COLL       0x00000100  /**< Excessive Collision               */
#define EMAC_TSV0_LATE_COLL      0x00000200  /**< Late Collision Occured            */
#define EMAC_TSV0_GIANT          0x00000400  /**< Giant Frame                       */
#define EMAC_TSV0_UNDERRUN       0x00000800  /**< Buffer Underrun                   */
#define EMAC_TSV0_BYTES          0x0FFFF000  /**< Total Bytes Transferred           */
#define EMAC_TSV0_CTRL_FRAME     0x10000000  /**< Control Frame                     */
#define EMAC_TSV0_PAUSE          0x20000000  /**< Pause Frame                       */
#define EMAC_TSV0_BACK_PRESS     0x40000000  /**< Backpressure Method Applied       */
#define EMAC_TSV0_VLAN           0x80000000  /**< VLAN Frame                        */

/* Transmit Status Vector 1 Register */
#define EMAC_TSV1_BYTE_CNT       0x0000FFFF  /**< Transmit Byte Count               */
#define EMAC_TSV1_COLL_CNT       0x000F0000  /**< Transmit Collision Count          */

/* Receive Status Vector Register */
#define EMAC_RSV_BYTE_CNT        0x0000FFFF  /**< Receive Byte Count                */
#define EMAC_RSV_PKT_IGNORED     0x00010000  /**< Packet Previously Ignored         */
#define EMAC_RSV_RXDV_SEEN       0x00020000  /**< RXDV Event Previously Seen        */
#define EMAC_RSV_CARR_SEEN       0x00040000  /**< Carrier Event Previously Seen     */
#define EMAC_RSV_REC_CODEV       0x00080000  /**< Receive Code Violation            */
#define EMAC_RSV_CRC_ERR         0x00100000  /**< CRC Error                         */
#define EMAC_RSV_LEN_CHKERR      0x00200000  /**< Length Check Error                */
#define EMAC_RSV_LEN_OUTRNG      0x00400000  /**< Length Out of Range               */
#define EMAC_RSV_REC_OK          0x00800000  /**< Frame Received OK                 */
#define EMAC_RSV_MCAST           0x01000000  /**< Multicast Frame                   */
#define EMAC_RSV_BCAST           0x02000000  /**< Broadcast Frame                   */
#define EMAC_RSV_DRIB_NIBB       0x04000000  /**< Dribble Nibble                    */
#define EMAC_RSV_CTRL_FRAME      0x08000000  /**< Control Frame                     */
#define EMAC_RSV_PAUSE           0x10000000  /**< Pause Frame                       */
#define EMAC_RSV_UNSUPP_OPC      0x20000000  /**< Unsupported Opcode                */
#define EMAC_RSV_VLAN            0x40000000  /**< VLAN Frame                        */

/* Flow Control Counter Register */
#define EMAC_FCC_MIRR_CNT(n)            (n&0xFFFF)          /**< Mirror Counter                    */
#define EMAC_FCC_PAUSE_TIM(n)           ((n&0xFFFF)<<16)    /**< Pause Timer                       */

/* Flow Control Status Register */
#define EMAC_FCS_MIRR_CNT(n)            (n&0xFFFF)          /**< Mirror Counter Current            */


/* Receive filter register definitions -------------------------------------------------------- */
/* Receive Filter Control Register */
#define EMAC_RFC_UCAST_EN        0x00000001  /**< Accept Unicast Frames Enable      */
#define EMAC_RFC_BCAST_EN        0x00000002  /**< Accept Broadcast Frames Enable    */
#define EMAC_RFC_MCAST_EN        0x00000004  /**< Accept Multicast Frames Enable    */
#define EMAC_RFC_UCAST_HASH_EN   0x00000008  /**< Accept Unicast Hash Filter Frames */
#define EMAC_RFC_MCAST_HASH_EN   0x00000010  /**< Accept Multicast Hash Filter Fram.*/
#define EMAC_RFC_PERFECT_EN      0x00000020  /**< Accept Perfect Match Enable       */
#define EMAC_RFC_MAGP_WOL_EN     0x00001000  /**< Magic Packet Filter WoL Enable    */
#define EMAC_RFC_PFILT_WOL_EN    0x00002000  /**< Perfect Filter WoL Enable         */

/* Receive Filter WoL Status/Clear Registers */
#define EMAC_WOL_UCAST           0x00000001  /**< Unicast Frame caused WoL          */
#define EMAC_WOL_BCAST           0x00000002  /**< Broadcast Frame caused WoL        */
#define EMAC_WOL_MCAST           0x00000004  /**< Multicast Frame caused WoL        */
#define EMAC_WOL_UCAST_HASH      0x00000008  /**< Unicast Hash Filter Frame WoL     */
#define EMAC_WOL_MCAST_HASH      0x00000010  /**< Multicast Hash Filter Frame WoL   */
#define EMAC_WOL_PERFECT         0x00000020  /**< Perfect Filter WoL                */
#define EMAC_WOL_RX_FILTER       0x00000080  /**< RX Filter caused WoL              */
#define EMAC_WOL_MAG_PACKET      0x00000100  /**< Magic Packet Filter caused WoL    */
#define EMAC_WOL_BITMASK         0x01BF     /**< Receive Filter WoL Status/Clear bitmasl value */

/* Hash Filter Table LSBs Register */
//

/* Hash Filter Table MSBs Register */
//


/* Module control register definitions ---------------------------------------------------- */
/* Interrupt Status/Enable/Clear/Set Registers */
#define EMAC_INT_RX_OVERRUN      0x00000001  /**< Overrun Error in RX Queue         */
#define EMAC_INT_RX_ERR          0x00000002  /**< Receive Error                     */
#define EMAC_INT_RX_FIN          0x00000004  /**< RX Finished Process Descriptors   */
#define EMAC_INT_RX_DONE         0x00000008  /**< Receive Done                      */
#define EMAC_INT_TX_UNDERRUN     0x00000010  /**< Transmit Underrun                 */
#define EMAC_INT_TX_ERR          0x00000020  /**< Transmit Error                    */
#define EMAC_INT_TX_FIN          0x00000040  /**< TX Finished Process Descriptors   */
#define EMAC_INT_TX_DONE         0x00000080  /**< Transmit Done                     */
#define EMAC_INT_SOFT_INT        0x00001000  /**< Software Triggered Interrupt      */
#define EMAC_INT_WAKEUP          0x00002000  /**< Wakeup Event Interrupt            */

/* Power Down Register */
#define EMAC_PD_POWER_DOWN       0x80000000  /**< Power Down MAC                    */


/* Descriptor and status formats ------------------------------------------------------ */
/* RX and TX descriptor and status definitions. */

/* EMAC Memory Buffer configuration for 16K Ethernet RAM */
#define EMAC_NUM_RX_FRAG         4           /**< Num.of RX Fragments 4*1536= 6.0kB */
#define EMAC_NUM_TX_FRAG         3           /**< Num.of TX Fragments 3*1536= 4.6kB */
#define EMAC_ETH_MAX_FLEN        1536        /**< Max. Ethernet Frame Size          */
#define EMAC_TX_FRAME_TOUT       0x00100000  /**< Frame Transmit timeout count      */

/* EMAC variables located in 16K Ethernet SRAM */
#define RX_DESC_BASE        LPC_PERI_RAM_BASE
#define RX_STAT_BASE        (RX_DESC_BASE + EMAC_NUM_RX_FRAG*8)
#define TX_DESC_BASE        (RX_STAT_BASE + EMAC_NUM_RX_FRAG*8)
#define TX_STAT_BASE        (TX_DESC_BASE + EMAC_NUM_TX_FRAG*8)
#define RX_BUF_BASE         (TX_STAT_BASE + EMAC_NUM_TX_FRAG*4)
#define TX_BUF_BASE         (RX_BUF_BASE  + EMAC_NUM_RX_FRAG*EMAC_ETH_MAX_FLEN)

/**
 * @brief RX Descriptor structure type definition
 */
#define RX_DESC_PACKET(i)   (*(uint32_t *)(RX_DESC_BASE   + 8*i))
#define RX_DESC_CTRL(i)     (*(uint32_t *)(RX_DESC_BASE+4 + 8*i))

/**
 * @brief RX Status structure type definition
 */
#define RX_STAT_INFO(i)     (*(uint32_t *)(RX_STAT_BASE   + 8*i))
#define RX_STAT_HASHCRC(i)  (*(uint32_t *)(RX_STAT_BASE+4 + 8*i))

/**
 * @brief TX Descriptor structure type definition
 */
#define TX_DESC_PACKET(i)   (*(uint32_t *)(TX_DESC_BASE   + 8*i))
#define TX_DESC_CTRL(i)     (*(uint32_t *)(TX_DESC_BASE+4 + 8*i))

/**
 * @brief TX Status structure type definition
 */
#define TX_STAT_INFO(i)     (*(uint32_t *)(TX_STAT_BASE   + 4*i))


/**
 * @brief TX Data Buffer structure definition
 */
#define RX_BUF(i)           (RX_BUF_BASE + EMAC_ETH_MAX_FLEN*i)
#define TX_BUF(i)           (TX_BUF_BASE + EMAC_ETH_MAX_FLEN*i)

/* RX Descriptor Control Word */
#define EMAC_RCTRL_SIZE(n)       (n&0x7FF)      /**< Buffer size field                  */
#define EMAC_RCTRL_INT           0x80000000     /**< Generate RxDone Interrupt         */

/* RX Status Hash CRC Word */
#define EMAC_RHASH_SA            0x000001FF     /**< Hash CRC for Source Address       */
#define EMAC_RHASH_DA            0x001FF000     /**< Hash CRC for Destination Address  */

/* RX Status Information Word */
#define EMAC_RINFO_SIZE          0x000007FF  /**< Data size in bytes                */
#define EMAC_RINFO_CTRL_FRAME    0x00040000  /**< Control Frame                     */
#define EMAC_RINFO_VLAN          0x00080000  /**< VLAN Frame                        */
#define EMAC_RINFO_FAIL_FILT     0x00100000  /**< RX Filter Failed                  */
#define EMAC_RINFO_MCAST         0x00200000  /**< Multicast Frame                   */
#define EMAC_RINFO_BCAST         0x00400000  /**< Broadcast Frame                   */
#define EMAC_RINFO_CRC_ERR       0x00800000  /**< CRC Error in Frame                */
#define EMAC_RINFO_SYM_ERR       0x01000000  /**< Symbol Error from PHY             */
#define EMAC_RINFO_LEN_ERR       0x02000000  /**< Length Error                      */
#define EMAC_RINFO_RANGE_ERR     0x04000000  /**< Range Error (exceeded max. size)  */
#define EMAC_RINFO_ALIGN_ERR     0x08000000  /**< Alignment Error                   */
#define EMAC_RINFO_OVERRUN       0x10000000  /**< Receive overrun                   */
#define EMAC_RINFO_NO_DESCR      0x20000000  /**< No new Descriptor available       */
#define EMAC_RINFO_LAST_FLAG     0x40000000  /**< Last Fragment in Frame            */
#define EMAC_RINFO_ERR           0x80000000  /**< Error Occured (OR of all errors)  */

/** RX Status Information word mask */
#define EMAC_RINFO_ERR_MASK     (EMAC_RINFO_FAIL_FILT | EMAC_RINFO_CRC_ERR   | EMAC_RINFO_SYM_ERR | \
                                    EMAC_RINFO_LEN_ERR   | EMAC_RINFO_ALIGN_ERR | EMAC_RINFO_OVERRUN)

/* TX Descriptor Control Word */
#define EMAC_TCTRL_SIZE          0x000007FF  /**< Size of data buffer in bytes      */
#define EMAC_TCTRL_OVERRIDE      0x04000000  /**< Override Default MAC Registers    */
#define EMAC_TCTRL_HUGE          0x08000000  /**< Enable Huge Frame                 */
#define EMAC_TCTRL_PAD           0x10000000  /**< Pad short Frames to 64 bytes      */
#define EMAC_TCTRL_CRC           0x20000000  /**< Append a hardware CRC to Frame    */
#define EMAC_TCTRL_LAST          0x40000000  /**< Last Descriptor for TX Frame      */
#define EMAC_TCTRL_INT           0x80000000  /**< Generate TxDone Interrupt         */

/* TX Status Information Word */
#define EMAC_TINFO_COL_CNT       0x01E00000  /**< Collision Count                   */
#define EMAC_TINFO_DEFER         0x02000000  /**< Packet Deferred (not an error)    */
#define EMAC_TINFO_EXCESS_DEF    0x04000000  /**< Excessive Deferral                */
#define EMAC_TINFO_EXCESS_COL    0x08000000  /**< Excessive Collision               */
#define EMAC_TINFO_LATE_COL      0x10000000  /**< Late Collision Occured            */
#define EMAC_TINFO_UNDERRUN      0x20000000  /**< Transmit Underrun                 */
#define EMAC_TINFO_NO_DESCR      0x40000000  /**< No new Descriptor available       */
#define EMAC_TINFO_ERR           0x80000000  /**< Error Occured (OR of all errors)  */


/* DP83848C PHY definition ------------------------------------------------------------ */

/** PHY device reset time out definition */
#define EMAC_PHY_RESP_TOUT      0x100000UL

/* ENET Device Revision ID */
#define EMAC_OLD_EMAC_MODULE_ID  0x39022000  /**< Rev. ID for first rev '-'         */


/* PHY Basic Mode Control Register (BMCR) bitmap definitions */
#define EMAC_PHY_BMCR_LOOPBACK              (1<<14)     /**< Loop back */
//#define EMAC_PHY_BMCR_AN                  (1<<12)     /**< Auto Negotiation */

#define EMAC_PHY_BMCR_ISOLATE               (1<<10)     /**< Isolate */
#define EMAC_PHY_BMCR_RE_AN                 (1<<9)      /**< Restart auto negotiation */

#define EMAC_PHY_BMSR_NOPREAM               (1<<6)      /**< MF Preamable Supress */
#define EMAC_PHY_BMSR_AUTO_DONE             (1<<5)      /**< Auto negotiation complete */


#define EMAC_PHY_FULLD_100M      (EMAC_PHY_BMCR_SPEED_SEL | EMAC_PHY_BMCR_DUPLEX)           // Full Duplex 100Mbit
#define EMAC_PHY_HALFD_100M      (EMAC_PHY_BMCR_SPEED_SEL | (~ EMAC_PHY_BMCR_DUPLEX))       // Half Duplex 100Mbit
#define EMAC_PHY_FULLD_10M       ((~ EMAC_PHY_BMCR_SPEED_SEL) | EMAC_PHY_BMCR_DUPLEX)       // Full Duplex 10Mbit
#define EMAC_PHY_HALFD_10M       ((~ EMAC_PHY_BMCR_SPEED_SEL) | (~EMAC_PHY_BMCR_DUPLEX))    // Half Duplex 10MBit
#define EMAC_PHY_AUTO_NEG        (EMAC_PHY_BMCR_SPEED_SEL | EMAC_PHY_BMCR_AN)               // Select Auto Negotiation



/* EMAC PHY status type definitions */
#define EMAC_PHY_STAT_LINK          (0)     /**< Link Status */
#define EMAC_PHY_STAT_SPEED         (1)     /**< Speed Status */
#define EMAC_PHY_STAT_DUP           (2)     /**< Duplex Status */

/* EMAC PHY device Speed definitions */
#define EMAC_MODE_AUTO              (0)     /**< Auto-negotiation mode */
#define EMAC_MODE_10M_FULL          (1)     /**< 10Mbps FullDuplex mode */
#define EMAC_MODE_10M_HALF          (2)     /**< 10Mbps HalfDuplex mode */
#define EMAC_MODE_100M_FULL         (3)     /**< 100Mbps FullDuplex mode */
#define EMAC_MODE_100M_HALF         (4)     /**< 100Mbps HalfDuplex mode */

/* EMAC User Buffers*/
#define EMAC_MAX_FRAME_SIZE          (0x600)  /* 1536 */
#define EMAC_MAX_FRAME_NUM           (2)

/* EMAC Error Codes */
#define EMAC_ALIGN_ERR              ( 1 << 0)
#define EMAC_RANGE_ERR              ( 1 << 1)
#define EMAC_LENGTH_ERR             ( 1 << 2)
#define EMAC_SYMBOL_ERR             ( 1 << 3)
#define EMAC_CRC_ERR                ( 1 << 4)
#define EMAC_RX_NO_DESC_ERR         ( 1 << 5)
#define EMAC_OVERRUN_ERR            ( 1 << 6)
#define EMAC_LATE_COLLISION_ERR     ( 1 << 7)
#define EMAC_EXCESSIVE_COLLISION_ERR ( 1 << 8)
#define EMAC_EXCESSIVE_DEFER_ERR     ( 1 << 9)
#define EMAC_UNDERRUN_ERR           ( 1 << 10)
#define EMAC_TX_NO_DESC_ERR         ( 1 << 11)
#define EMAC_FILTER_FAILED_ERR      ( 1 << 12)


/**
 * @}
 */


/**************************** GLOBAL/PUBLIC TYPES ***************************/

/** @defgroup EMAC_Public_Types EMAC Public Types
 * @{
 */

/**
 * @brief TX Data Buffer structure definition
 */
typedef struct {
    uint32_t ulDataLen;         /**< Data length */
    uint32_t *pbDataBuf;        /**< A word-align data pointer to data buffer */
} EMAC_PACKETBUF_Type;

/**
 * @brief PHY Configuration structure definition
 */
typedef struct {
   uint32_t Mode;                       /**< Supported EMAC PHY device speed, should be one of the following:
                                            - EMAC_MODE_AUTO
                                            - EMAC_MODE_10M_FULL
                                            - EMAC_MODE_10M_HALF
                                            - EMAC_MODE_100M_FULL
                                            - EMAC_MODE_100M_HALF
                                            */
} EMAC_PHY_CFG_Type;


/** EMAC Call back function type definition */
typedef int32_t (PHY_INIT_FUNC)(EMAC_PHY_CFG_Type* pPhyCfg);
typedef int32_t (PHY_RESET_FUNC)(void);
typedef void (EMAC_FRAME_RECV_FUNC)(uint16_t* pData, uint32_t size);
typedef void (EMAC_TRANSMIT_FINISH_FUNC)(void);
typedef void (EMAC_ERR_RECV_FUNC)(int32_t ulErrCode);
typedef void (EMAC_WAKEUP_FUNC)(void);
typedef void (SOFT_INT_FUNC)(void);

/**
 * @brief EMAC configuration structure definition
 */
typedef struct {
    EMAC_PHY_CFG_Type PhyCfg;               /* PHY Configuration */
    uint8_t           bPhyAddr;                    /* 5-bit PHY Address field */    
    uint8_t     *pbEMAC_Addr;               /**< Pointer to EMAC Station address that contains 6-bytes
                                            of MAC address, it must be sorted in order (bEMAC_Addr[0]..[5])
                                            */
    uint16_t     nMaxFrameSize;              /* maximum frame length */
    PHY_INIT_FUNC *pfnPHYInit;               /* point to the funtion which will be called to initialize PHY */
    PHY_RESET_FUNC *pfnPHYReset;             /* point to the function which will be called to reset PHY */
    EMAC_FRAME_RECV_FUNC *pfnFrameReceive;     /* point to the function which will be called when a frame is received*/
    EMAC_TRANSMIT_FINISH_FUNC* pfnTransmitFinish;  /*point to the function which will be called when transmit finished*/
    EMAC_ERR_RECV_FUNC    *pfnErrorReceive;     /* point to an array of functions which will be called error occur. */
                                               /* Errors:
                                                                 EMAC_ALIGN_ERR 
                                                        EMAC_RANGE_ERR
                                                        EMAC_LENGTH_ERR
                                                        EMAC_SYMBOL_ERR 
                                                        EMAC_CRC_ERR
                                                        EMAC_RX_NO_DESC_ERR
                                                        EMAC_OVERRUN_ERR
                                                        EMAC_LATE_COLLISION_ERR
                                                        EMAC_EXCESSIVE_COLLISION_ERR
                                                        EMAC_EXCESSIVE_DEFER_ERR
                                                        EMAC_UNDERRUN_ERR
                                                        EMAC_TX_NO_DESC_ERR
                                                  */
    EMAC_WAKEUP_FUNC *pfnWakeup;               /* point to the function which will be called when receiving wakeup interrupt */
    SOFT_INT_FUNC *pfnSoftInt;                /* point to the function which will be called when the interrupt caused by software occurs */                    
} EMAC_CFG_Type;

/**
 * @brief EMAC Buffer status definition
 */
typedef enum {
   EMAC_BUFF_EMPTY,                /* buffer is empty */
   EMAC_BUFF_PARTIAL_FULL,         /* buffer contains some packets */
   EMAC_BUFF_FULL,                 /* buffer is full */
} EMAC_BUFF_STATUS;

/**
 * @brief EMAC Buffer Index definition
 */

typedef enum {
    EMAC_TX_BUFF,                   /* transmit buffer */
    EMAC_RX_BUFF,                   /* receive buffer */
} EMAC_BUFF_IDX;

/**
 * @}
 */


/** @defgroup EMAC_Public_Functions EMAC Public Functions
 * @{
 */

/** Init/DeInit */
int32_t EMAC_Init(EMAC_CFG_Type *EMAC_ConfigStruct);
void EMAC_DeInit(void);

/** Send/Receive data */
void EMAC_TxEnable( void );
void EMAC_RxEnable( void );
void EMAC_SetHashFilter(uint8_t dstMAC_addr[], FunctionalState NewState);
int32_t EMAC_CRCCalc(uint8_t frame_no_fcs[], int32_t frame_len);
void EMAC_WritePacketBuffer(EMAC_PACKETBUF_Type *pDataStruct);

/** PHY Setup */
void EMAC_Write_PHY (uint8_t PhyReg, uint16_t Value);
uint16_t EMAC_Read_PHY (uint8_t PhyReg);
void EMAC_SetFullDuplexMode(uint8_t full_duplex);
void EMAC_SetPHYSpeed(uint8_t mode_100Mbps);

/** Filter */
void EMAC_SetFilterMode(uint32_t ulFilterMode, FunctionalState NewState);
FlagStatus EMAC_GetWoLStatus(uint32_t ulWoLMode);
void EMAC_IntCmd(uint32_t ulIntType, FunctionalState NewState);
IntStatus EMAC_IntGetStatus(uint32_t ulIntType);
EMAC_BUFF_STATUS EMAC_GetBufferSts(EMAC_BUFF_IDX idx);


/**
 * @}
 */



#ifdef __cplusplus
}
#endif

#endif /* __LPC_EMAC_DRIVER_H_ */

/**
 * @}
 */

