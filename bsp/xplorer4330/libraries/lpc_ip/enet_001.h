/*
 * @brief Ethernet control functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __ENET_001_H_
#define __ENET_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_ENET_001 IP: Ethernet register block and driver
 * @ingroup IP_Drivers
 * @{
 */

/**
 * @brief 10/100 MII & RMII Ethernet with timestamping register block structure
 */
typedef struct {							/*!< ETHERNET Structure */
	__IO uint32_t  MAC_CONFIG;				/*!< MAC configuration register */
	__IO uint32_t  MAC_FRAME_FILTER;		/*!< MAC frame filter */
	__IO uint32_t  MAC_HASHTABLE_HIGH;		/*!< Hash table high register */
	__IO uint32_t  MAC_HASHTABLE_LOW;		/*!< Hash table low register */
	__IO uint32_t  MAC_MII_ADDR;			/*!< MII address register */
	__IO uint32_t  MAC_MII_DATA;			/*!< MII data register */
	__IO uint32_t  MAC_FLOW_CTRL;			/*!< Flow control register */
	__IO uint32_t  MAC_VLAN_TAG;			/*!< VLAN tag register */
	__I  uint32_t  RESERVED0;
	__I  uint32_t  MAC_DEBUG;				/*!< Debug register */
	__IO uint32_t  MAC_RWAKE_FRFLT;			/*!< Remote wake-up frame filter */
	__IO uint32_t  MAC_PMT_CTRL_STAT;		/*!< PMT control and status */
	__I  uint32_t  RESERVED1[2];
	__I  uint32_t  MAC_INTR;				/*!< Interrupt status register */
	__IO uint32_t  MAC_INTR_MASK;			/*!< Interrupt mask register */
	__IO uint32_t  MAC_ADDR0_HIGH;			/*!< MAC address 0 high register */
	__IO uint32_t  MAC_ADDR0_LOW;			/*!< MAC address 0 low register */
	__I  uint32_t  RESERVED2[430];
	__IO uint32_t  MAC_TIMESTP_CTRL;		/*!< Time stamp control register */
	__IO uint32_t  SUBSECOND_INCR;			/*!< Sub-second increment register */
	__I  uint32_t  SECONDS;					/*!< System time seconds register */
	__I  uint32_t  NANOSECONDS;				/*!< System time nanoseconds register */
	__IO uint32_t  SECONDSUPDATE;			/*!< System time seconds update register */
	__IO uint32_t  NANOSECONDSUPDATE;		/*!< System time nanoseconds update register */
	__IO uint32_t  ADDEND;					/*!< Time stamp addend register */
	__IO uint32_t  TARGETSECONDS;			/*!< Target time seconds register */
	__IO uint32_t  TARGETNANOSECONDS;		/*!< Target time nanoseconds register */
	__IO uint32_t  HIGHWORD;				/*!< System time higher word seconds register */
	__I  uint32_t  TIMESTAMPSTAT;			/*!< Time stamp status register */
	__IO uint32_t  PPSCTRL;					/*!< PPS control register */
	__I  uint32_t  AUXNANOSECONDS;			/*!< Auxiliary time stamp nanoseconds register */
	__I  uint32_t  AUXSECONDS;				/*!< Auxiliary time stamp seconds register */
	__I  uint32_t  RESERVED3[562];
	__IO uint32_t  DMA_BUS_MODE;			/*!< Bus Mode Register      */
	__IO uint32_t  DMA_TRANS_POLL_DEMAND;	/*!< Transmit poll demand register */
	__IO uint32_t  DMA_REC_POLL_DEMAND;		/*!< Receive poll demand register */
	__IO uint32_t  DMA_REC_DES_ADDR;		/*!< Receive descriptor list address register */
	__IO uint32_t  DMA_TRANS_DES_ADDR;		/*!< Transmit descriptor list address register */
	__IO uint32_t  DMA_STAT;				/*!< Status register */
	__IO uint32_t  DMA_OP_MODE;				/*!< Operation mode register */
	__IO uint32_t  DMA_INT_EN;				/*!< Interrupt enable register */
	__I  uint32_t  DMA_MFRM_BUFOF;			/*!< Missed frame and buffer overflow register */
	__IO uint32_t  DMA_REC_INT_WDT;			/*!< Receive interrupt watchdog timer register */
	__I  uint32_t  RESERVED4[8];
	__I  uint32_t  DMA_CURHOST_TRANS_DES;	/*!< Current host transmit descriptor register */
	__I  uint32_t  DMA_CURHOST_REC_DES;		/*!< Current host receive descriptor register */
	__I  uint32_t  DMA_CURHOST_TRANS_BUF;	/*!< Current host transmit buffer address register */
	__I  uint32_t  DMA_CURHOST_REC_BUF;		/*!< Current host receive buffer address register */
} IP_ENET_001_Type;

/**
 * @brief MAC_CONFIG register bit defines
 */
#define MAC_CFG_RE     (1 << 2)		/*!< Receiver enable */
#define MAC_CFG_TE     (1 << 3)		/*!< Transmitter Enable */
#define MAC_CFG_DF     (1 << 4)		/*!< Deferral Check */
#define MAC_CFG_BL(n)  ((n) << 5)	/*!< Back-Off Limit */
#define MAC_CFG_ACS    (1 << 7)		/*!< Automatic Pad/CRC Stripping */
#define MAC_CFG_LUD    (1 << 8)		/*!< Link Up/Down, 1 = up */
#define MAC_CFG_DR     (1 << 9)		/*!< Disable Retry */
#define MAC_CFG_IPC    (1 << 10)	/*!< Checksum Offload */
#define MAC_CFG_DM     (1 << 11)	/*!< Duplex Mode, 1 = full, 0 = half */
#define MAC_CFG_LM     (1 << 12)	/*!< Loopback Mode */
#define MAC_CFG_DO     (1 << 13)	/*!< Disable Receive Own */
#define MAC_CFG_FES    (1 << 14)	/*!< Speed, 1 = 100Mbps, 0 = 10Mbos */
#define MAC_CFG_PS     (1 << 15)	/*!< Port select, must always be 1 */
#define MAC_CFG_DCRS   (1 << 16)	/*!< Disable carrier sense during transmission */
#define MAC_CFG_IFG(n) ((n) << 17)	/*!< Inter-frame gap, 40..96, n incs by 8 */
#define MAC_CFG_JE     (1 << 20)	/*!< Jumbo Frame Enable */
#define MAC_CFG_JD     (1 << 22)	/*!< Jabber Disable */
#define MAC_CFG_WD     (1 << 23)	/*!< Watchdog Disable */

/**
 * @brief MAC_FRAME_FILTER register bit defines
 */
#define MAC_FF_PR      (1 << 0)		/*!< Promiscuous Mode */
#define MAC_FF_DAIF    (1 << 3)		/*!< DA Inverse Filtering */
#define MAC_FF_PM      (1 << 4)		/*!< Pass All Multicast */
#define MAC_FF_DBF     (1 << 5)		/*!< Disable Broadcast Frames */
#define MAC_FF_PCF(n)  ((n) << 6)	/*!< Pass Control Frames, n = see user manual */
#define MAC_FF_SAIF    (1 << 8)		/*!< SA Inverse Filtering */
#define MAC_FF_SAF     (1 << 9)		/*!< Source Address Filter Enable */
#define MAC_FF_RA      (1UL << 31)	/*!< Receive all */

/**
 * @brief MAC_MII_ADDR register bit defines
 */
#define MAC_MIIA_GB    (1 << 0)		/*!< MII busy */
#define MAC_MIIA_W     (1 << 1)		/*!< MII write */
#define MAC_MIIA_CR(n) ((n) << 2)	/*!< CSR clock range, n = see manual */
#define MAC_MIIA_GR(n) ((n) << 6)	/*!< MII register. n = 0..31 */
#define MAC_MIIA_PA(n) ((n) << 11)	/*!< Physical layer address, n = 0..31 */

/**
 * @brief MAC_MII_DATA register bit defines
 */
#define MAC_MIID_GDMSK (0xFFFF)		/*!< MII data mask */

/**
 * @brief MAC_FLOW_CONTROL register bit defines
 */
#define MAC_FC_FCB     (1 << 0)		/*!< Flow Control Busy/Backpressure Activate */
#define MAC_FC_TFE     (1 << 1)		/*!< Transmit Flow Control Enable */
#define MAC_FC_RFE     (1 << 2)		/*!< Receive Flow Control Enable */
#define MAC_FC_UP      (1 << 3)		/*!< Unicast Pause Frame Detect */
#define MAC_FC_PLT(n)  ((n) << 4)	/*!< Pause Low Threshold, n = see manual */
#define MAC_FC_DZPQ    (1 << 7)		/*!< Disable Zero-Quanta Pause */
#define MAC_FC_PT(n)   ((n) << 16)	/*!< Pause time */

/**
 * @brief MAC_VLAN_TAG register bit defines
 */
#define MAC_VT_VL(n)   ((n) << 0)	/*!< VLAN Tag Identifier for Receive Frames */
#define MAC_VT_ETC     (1 << 7)		/*!< Enable 12-Bit VLAN Tag Comparison */

/**
 * @brief MAC_PMT_CTRL_STAT register bit defines
 */
#define MAC_PMT_PD     (1 << 0)		/*!< Power-down */
#define MAC_PMT_MPE    (1 << 1)		/*!< Magic packet enable */
#define MAC_PMT_WFE    (1 << 2)		/*!< Wake-up frame enable */
#define MAC_PMT_MPR    (1 << 5)		/*!< Magic Packet Received */
#define MAC_PMT_WFR    (1 << 6)		/*!< Wake-up Frame Received */
#define MAC_PMT_GU     (1 << 9)		/*!< Global Unicast */
#define MAC_PMT_WFFRPR (1UL << 31)	/*!< Wake-up Frame Filter Register Pointer Reset */

/**
 * @brief MAC_INTR_MASK register bit defines
 */
#define MAC_IM_PMT     (1 << 3)		/*!< PMT Interrupt Mask */

/**
 * @brief MAC_ADDR0_HIGH register bit defines
 */
#define MAC_ADRH_MO    (1UL << 31)	/*!< Always 1 when writing register */

/**
 * @brief MAC_ADDR0_HIGH register bit defines
 */
#define MAC_ADRH_MO    (1UL << 31)	/*!< Always 1 when writing register */

/**
 * @brief MAC_TIMESTAMP register bit defines
 */
#define MAC_TS_TSENA   (1 << 0)		/*!< Time Stamp Enable */
#define MAC_TS_TSCFUP  (1 << 1)		/*!< Time Stamp Fine or Coarse Update */
#define MAC_TS_TSINIT  (1 << 2)		/*!< Time Stamp Initialize */
#define MAC_TS_TSUPDT  (1 << 3)		/*!< Time Stamp Update */
#define MAC_TS_TSTRIG  (1 << 4)		/*!< Time Stamp Interrupt Trigger Enable */
#define MAC_TS_TSADDR  (1 << 5)		/*!< Addend Reg Update */
#define MAC_TS_TSENAL  (1 << 8)		/*!< Enable Time Stamp for All Frames */
#define MAC_TS_TSCTRL  (1 << 9)		/*!< Time Stamp Digital or Binary rollover control */
#define MAC_TS_TSVER2  (1 << 10)	/*!< Enable PTP packet snooping for version 2 format */
#define MAC_TS_TSIPENA (1 << 11)	/*!< Enable Time Stamp Snapshot for PTP over Ethernet frames */
#define MAC_TS_TSIPV6E (1 << 12)	/*!< Enable Time Stamp Snapshot for IPv6 frames */
#define MAC_TS_TSIPV4E (1 << 13)	/*!< Enable Time Stamp Snapshot for IPv4 frames */
#define MAC_TS_TSEVNT  (1 << 14)	/*!< Enable Time Stamp Snapshot for Event Messages */
#define MAC_TS_TSMSTR  (1 << 15)	/*!< Enable Snapshot for Messages Relevant to Master */
#define MAC_TS_TSCLKT(n) ((n) << 16)	/*!< Select the type of clock node, n = see menual */
#define MAC_TS_TSENMA  (1 << 18)	/*!< Enable MAC address for PTP frame filtering */

/**
 * @brief DMA_BUS_MODE register bit defines
 */
#define DMA_BM_SWR     (1 << 0)		/*!< Software reset */
#define DMA_BM_DA      (1 << 1)		/*!< DMA arbitration scheme, 1 = TX has priority over TX */
#define DMA_BM_DSL(n)  ((n) << 2)	/*!< Descriptor skip length, n = see manual */
#define DMA_BM_ATDS    (1 << 7)		/*!< Alternate (Enhanced) descriptor size */
#define DMA_BM_PBL(n)  ((n) << 8)	/*!< Programmable burst length, n = see manual */
#define DMA_BM_PR(n)   ((n) << 14)	/*!< Rx-to-Tx priority ratio, n = see manual */
#define DMA_BM_FB      (1 << 16)	/*!< Fixed burst */
#define DMA_BM_RPBL(n) ((n) << 17)	/*!< RxDMA PBL, n = see manual */
#define DMA_BM_USP     (1 << 23)	/*!< Use separate PBL */
#define DMA_BM_PBL8X   (1 << 24)	/*!< 8 x PBL mode */
#define DMA_BM_AAL     (1 << 25)	/*!< Address-aligned beats */
#define DMA_BM_MB      (1 << 26)	/*!< Mixed burst */
#define DMA_BM_TXPR    (1 << 27)	/*!< Transmit DMA has higher priority than receive DMA */

/**
 * @brief DMA_STAT register bit defines
 */
#define DMA_ST_TI      (1 << 0)		/*!< Transmit interrupt */
#define DMA_ST_TPS     (1 << 1)		/*!< Transmit process stopped */
#define DMA_ST_TU      (1 << 2)		/*!< Transmit buffer unavailable */
#define DMA_ST_TJT     (1 << 3)		/*!< Transmit jabber timeout */
#define DMA_ST_OVF     (1 << 4)		/*!< Receive overflow */
#define DMA_ST_UNF     (1 << 5)		/*!< Transmit underflow */
#define DMA_ST_RI      (1 << 6)		/*!< Receive interrupt */
#define DMA_ST_RU      (1 << 7)		/*!< Receive buffer unavailable */
#define DMA_ST_RPS     (1 << 8)		/*!< Received process stopped */
#define DMA_ST_RWT     (1 << 9)		/*!< Receive watchdog timeout */
#define DMA_ST_ETI     (1 << 10)	/*!< Early transmit interrupt */
#define DMA_ST_FBI     (1 << 13)	/*!< Fatal bus error interrupt */
#define DMA_ST_ERI     (1 << 14)	/*!< Early receive interrupt */
#define DMA_ST_AIE     (1 << 15)	/*!< Abnormal interrupt summary */
#define DMA_ST_NIS     (1 << 16)	/*!< Normal interrupt summary */
#define DMA_ST_ALL     (0x1E7FF)	/*!< All interrupts */

/**
 * @brief DMA_OP_MODE register bit defines
 */
#define DMA_OM_SR      (1 << 1)		/*!< Start/stop receive */
#define DMA_OM_OSF     (1 << 2)		/*!< Operate on second frame */
#define DMA_OM_RTC(n)  ((n) << 3)	/*!< Receive threshold control, n = see manual */
#define DMA_OM_FUF     (1 << 6)		/*!< Forward undersized good frames */
#define DMA_OM_FEF     (1 << 7)		/*!< Forward error frames */
#define DMA_OM_ST      (1 << 13)	/*!< Start/Stop Transmission Command */
#define DMA_OM_TTC(n)  ((n) << 14)	/*!< Transmit threshold control, n = see manual */
#define DMA_OM_FTF     (1 << 20)	/*!< Flush transmit FIFO */
#define DMA_OM_TSF     (1 << 21)	/*!< Transmit store and forward */
#define DMA_OM_DFF     (1 << 24)	/*!< Disable flushing of received frames */
#define DMA_OM_RSF     (1 << 25)	/*!< Receive store and forward */
#define DMA_OM_DT      (1 << 26)	/*!< Disable Dropping of TCP/IP Checksum Error Frames */

/**
 * @brief DMA_INT_EN register bit defines
 */
#define DMA_IE_TIE     (1 << 0)		/*!< Transmit interrupt enable */
#define DMA_IE_TSE     (1 << 1)		/*!< Transmit stopped enable */
#define DMA_IE_TUE     (1 << 2)		/*!< Transmit buffer unavailable enable */
#define DMA_IE_TJE     (1 << 3)		/*!< Transmit jabber timeout enable */
#define DMA_IE_OVE     (1 << 4)		/*!< Overflow interrupt enable */
#define DMA_IE_UNE     (1 << 5)		/*!< Underflow interrupt enable */
#define DMA_IE_RIE     (1 << 6)		/*!< Receive interrupt enable */
#define DMA_IE_RUE     (1 << 7)		/*!< Receive buffer unavailable enable */
#define DMA_IE_RSE     (1 << 8)		/*!< Received stopped enable */
#define DMA_IE_RWE     (1 << 9)		/*!< Receive watchdog timeout enable */
#define DMA_IE_ETE     (1 << 10)	/*!< Early transmit interrupt enable */
#define DMA_IE_FBE     (1 << 13)	/*!< Fatal bus error enable */
#define DMA_IE_ERE     (1 << 14)	/*!< Early receive interrupt enable */
#define DMA_IE_AIE     (1 << 15)	/*!< Abnormal interrupt summary enable */
#define DMA_IE_NIE     (1 << 16)	/*!< Normal interrupt summary enable */

/**
 * @brief DMA_MFRM_BUFOF register bit defines
 */
#define DMA_MFRM_FMCMSK (0xFFFF)	/*!< Number of frames missed mask */
#define DMA_MFRM_OC    (1 << 16)	/*!< Overflow bit for missed frame counter */
#define DMA_MFRM_FMA(n) (((n) & 0x0FFE0000) >> 17)	/*!< Number of frames missed by the application mask/shift */
#define DMA_MFRM_OF    (1 << 28)	/*!< Overflow bit for FIFO overflow counter */

/**
 * @brief Common TRAN_DESC_T and TRAN_DESC_ENH_T CTRLSTAT field bit defines
 */
#define TDES_DB        (1 << 0)		/*!< Deferred Bit */
#define TDES_UF        (1 << 1)		/*!< Underflow Error */
#define TDES_ED        (1 << 2)		/*!< Excessive Deferral */
#define TDES_CCMSK(n)  (((n) & 0x000000F0) >> 3)/*!< CC: Collision Count (Status field) mask and shift */
#define TDES_VF        (1 << 7)		/*!< VLAN Frame */
#define TDES_EC        (1 << 8)		/*!< Excessive Collision */
#define TDES_LC        (1 << 9)		/*!< Late Collision */
#define TDES_NC        (1 << 10)	/*!< No Carrier */
#define TDES_LCAR      (1 << 11)	/*!< Loss of Carrier */
#define TDES_IPE       (1 << 12)	/*!< IP Payload Error */
#define TDES_FF        (1 << 13)	/*!< Frame Flushed */
#define TDES_JT        (1 << 14)	/*!< Jabber Timeout */
#define TDES_ES        (1 << 15)	/*!< Error Summary */
#define TDES_IHE       (1 << 16)	/*!< IP Header Error */
#define TDES_TTSS      (1 << 17)	/*!< Transmit Timestamp Status */
#define TDES_OWN       (1UL << 31)	/*!< Own Bit */

/**
 * @brief TRAN_DESC_ENH_T only CTRLSTAT field bit defines
 */
#define TDES_ENH_IC   (1UL << 30)	/*!< Interrupt on Completion, enhanced descriptor */
#define TDES_ENH_LS   (1 << 29)		/*!< Last Segment, enhanced descriptor */
#define TDES_ENH_FS   (1 << 28)		/*!< First Segment, enhanced descriptor */
#define TDES_ENH_DC   (1 << 27)		/*!< Disable CRC, enhanced descriptor */
#define TDES_ENH_DP   (1 << 26)		/*!< Disable Pad, enhanced descriptor */
#define TDES_ENH_TTSE (1 << 25)		/*!< Transmit Timestamp Enable, enhanced descriptor */
#define TDES_ENH_CIC(n) ((n) << 22)	/*!< Checksum Insertion Control, enhanced descriptor */
#define TDES_ENH_TER  (1 << 21)		/*!< Transmit End of Ring, enhanced descriptor */
#define TDES_ENH_TCH  (1 << 20)		/*!< Second Address Chained, enhanced descriptor */

/**
 * @brief TRAN_DESC_T only BSIZE field bit defines
 */
#define TDES_NORM_IC   (1UL << 31)	/*!< Interrupt on Completion, normal descriptor */
#define TDES_NORM_FS   (1 << 30)	/*!< First Segment, normal descriptor */
#define TDES_NORM_LS   (1 << 29)	/*!< Last Segment, normal descriptor */
#define TDES_NORM_CIC(n) ((n) << 27)	/*!< Checksum Insertion Control, normal descriptor */
#define TDES_NORM_DC   (1 << 26)	/*!< Disable CRC, normal descriptor */
#define TDES_NORM_TER  (1 << 25)	/*!< Transmit End of Ring, normal descriptor */
#define TDES_NORM_TCH  (1 << 24)	/*!< Second Address Chained, normal descriptor */
#define TDES_NORM_DP   (1 << 23)	/*!< Disable Pad, normal descriptor */
#define TDES_NORM_TTSE (1 << 22)	/*!< Transmit Timestamp Enable, normal descriptor */
#define TDES_NORM_BS2(n) (((n) & 0x3FF) << 11)	/*!< Buffer 2 size, normal descriptor */
#define TDES_NORM_BS1(n) (((n) & 0x3FF) << 0)	/*!< Buffer 1 size, normal descriptor */

/**
 * @brief TRAN_DESC_ENH_T only BSIZE field bit defines
 */
#define TDES_ENH_BS2(n) (((n) & 0xFFF) << 16)	/*!< Buffer 2 size, enhanced descriptor */
#define TDES_ENH_BS1(n) (((n) & 0xFFF) << 0)	/*!< Buffer 1 size, enhanced descriptor */

/**
 * @brief Common REC_DESC_T and REC_DESC_ENH_T STATUS field bit defines
 */
#define RDES_ESA      (1 << 0)		/*!< Extended Status Available/Rx MAC Address */
#define RDES_CE       (1 << 1)		/*!< CRC Error */
#define RDES_DRE      (1 << 2)		/*!< Dribble Bit Error */
#define RDES_RE       (1 << 3)		/*!< Receive Error */
#define RDES_RWT      (1 << 4)		/*!< Receive Watchdog Timeout */
#define RDES_FT       (1 << 5)		/*!< Frame Type */
#define RDES_LC       (1 << 6)		/*!< Late Collision */
#define RDES_TSA      (1 << 7)		/*!< Timestamp Available/IP Checksum Error (Type1) /Giant Frame */
#define RDES_LS       (1 << 8)		/*!< Last Descriptor */
#define RDES_FS       (1 << 9)		/*!< First Descriptor */
#define RDES_VLAN     (1 << 10)		/*!< VLAN Tag */
#define RDES_OE       (1 << 11)		/*!< Overflow Error */
#define RDES_LE       (1 << 12)		/*!< Length Error */
#define RDES_SAF      (1 << 13)		/*!< Source Address Filter Fail */
#define RDES_DE       (1 << 14)		/*!< Descriptor Error */
#define RDES_ES       (1 << 15)		/*!< ES: Error Summary */
#define RDES_FLMSK(n) (((n) & 0x3FFF0000) >> 16)/*!< Frame Length mask and shift */
#define RDES_AFM      (1 << 30)		/*!< Destination Address Filter Fail */
#define RDES_OWN      (1UL << 31)	/*!< Own Bit */

/**
 * @brief Common REC_DESC_T and REC_DESC_ENH_T CTRL field bit defines
 */
#define RDES_DINT     (1UL << 31)	/*!< Disable interrupt on completion */

/**
 * @brief REC_DESC_T pnly CTRL field bit defines
 */
#define RDES_NORM_RER (1 << 25)		/*!< Receive End of Ring, normal descriptor */
#define RDES_NORM_RCH (1 << 24)		/*!< Second Address Chained, normal descriptor */
#define RDES_NORM_BS2(n) (((n) & 0x3FF) << 11)	/*!< Buffer 2 size, normal descriptor */
#define RDES_NORM_BS1(n) (((n) & 0x3FF) << 0)	/*!< Buffer 1 size, normal descriptor */

/**
 * @brief REC_DESC_ENH_T only CTRL field bit defines
 */
#define RDES_ENH_RER  (1 << 15)		/*!< Receive End of Ring, enhanced descriptor */
#define RDES_ENH_RCH  (1 << 14)		/*!< Second Address Chained, enhanced descriptor */
#define RDES_ENH_BS2(n) (((n) & 0xFFF) << 16)	/*!< Buffer 2 size, enhanced descriptor */
#define RDES_ENH_BS1(n) (((n) & 0xFFF) << 0)	/*!< Buffer 1 size, enhanced descriptor */

/**
 * @brief REC_DESC_ENH_T only EXTSTAT field bit defines
 */
#define RDES_ENH_IPPL(n)  (((n) & 0x7) >> 2)	/*!< IP Payload Type mask and shift, enhanced descripto */
#define RDES_ENH_IPHE     (1 << 3)	/*!< IP Header Error, enhanced descripto */
#define RDES_ENH_IPPLE    (1 << 4)	/*!< IP Payload Error, enhanced descripto */
#define RDES_ENH_IPCSB    (1 << 5)	/*!< IP Checksum Bypassed, enhanced descripto */
#define RDES_ENH_IPV4     (1 << 6)	/*!< IPv4 Packet Received, enhanced descripto */
#define RDES_ENH_IPV6     (1 << 7)	/*!< IPv6 Packet Received, enhanced descripto */
#define RDES_ENH_MTMSK(n) (((n) & 0xF) >> 8)	/*!< Message Type mask and shift, enhanced descripto */

/**
 * @brief Maximum size of an ethernet buffer
 */
#define EMAC_ETH_MAX_FLEN (1536)

/**
 * @brief Structure of a transmit descriptor (without timestamp)
 */
typedef struct {
	__IO uint32_t CTRLSTAT;		/*!< TDES control and status word */
	__IO uint32_t BSIZE;		/*!< Buffer 1/2 byte counts */
	__IO uint32_t B1ADD;		/*!< Buffer 1 address */
	__IO uint32_t B2ADD;		/*!< Buffer 2 or next descriptor address */
} IP_ENET_001_TXDESC_Type;

/**
 * @brief Structure of a enhanced transmit descriptor (with timestamp)
 */
typedef struct {
	__IO uint32_t CTRLSTAT;		/*!< TDES control and status word */
	__IO uint32_t BSIZE;		/*!< Buffer 1/2 byte counts */
	__IO uint32_t B1ADD;		/*!< Buffer 1 address */
	__IO uint32_t B2ADD;		/*!< Buffer 2 or next descriptor address */
	__IO uint32_t TDES4;		/*!< Reserved */
	__IO uint32_t TDES5;		/*!< Reserved */
	__IO uint32_t TTSL;			/*!< Timestamp value low */
	__IO uint32_t TTSH;			/*!< Timestamp value high */
} IP_ENET_001_ENHTXDESC_Type;

/**
 * @brief Structure of a receive descriptor (without timestamp)
 */
typedef struct {
	__IO uint32_t STATUS;		/*!< RDES status word */
	__IO uint32_t CTRL;			/*!< Buffer 1/2 byte counts and control */
	__IO uint32_t B1ADD;		/*!< Buffer 1 address */
	__IO uint32_t B2ADD;		/*!< Buffer 2 or next descriptor address */
} IP_ENET_001_RXDESC_Type;

/**
 * @brief Structure of a enhanced receive descriptor (with timestamp)
 */
typedef struct {
	__IO uint32_t STATUS;		/*!< RDES status word */
	__IO uint32_t CTRL;			/*!< Buffer 1/2 byte counts */
	__IO uint32_t B1ADD;		/*!< Buffer 1 address */
	__IO uint32_t B2ADD;		/*!< Buffer 2 or next descriptor address */
	__IO uint32_t EXTSTAT;		/*!< Extended Status */
	__IO uint32_t RDES5;		/*!< Reserved */
	__IO uint32_t RTSL;			/*!< Timestamp value low */
	__IO uint32_t RTSH;			/*!< Timestamp value high */
} IP_ENET_001_ENHRXDESC_Type;

/**
 * @brief	Resets the ethernet interface
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @return	Nothing
 * Resets the ethernet interface. This should be called prior to
 * IP_ENET_Init with a small delay after this call.
 */
void IP_ENET_Reset(IP_ENET_001_Type *LPC_ENET);

/**
 * @brief	Sets the address of the interface
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @param	macAddr		: Pointer to the 6 bytes used for the MAC address
 * @return	Nothing
 */
void IP_ENET_SetADDR(IP_ENET_001_Type *LPC_ENET, const uint8_t *macAddr);

/**
 * @brief	Initialize ethernet interface
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @return	Nothing
 * Performs basic initialization of the ethernet interface in a default
 * state. This is enough to place the interface in a usable state, but
 * may require more setup outside this function.
 */
void IP_ENET_Init(IP_ENET_001_Type *LPC_ENET);

/**
 * @brief	Sets up the PHY link clock divider and PHY address
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @param	div			: Divider value, may vary per chip
 * @param	addr		: PHY address, used with MII read and write
 * @return	Nothing
 */
void IP_ENET_SetupMII(IP_ENET_001_Type *LPC_ENET, uint32_t div, uint8_t addr);

/**
 * @brief	De-initialize the ethernet interface
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @return	Nothing
 */
void IP_ENET_DeInit(IP_ENET_001_Type *LPC_ENET);

/**
 * @brief	Starts a PHY write via the MII
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @param	reg			: PHY register to write
 * @param	data		: Data to write to PHY register
 * @return	Nothing
 * Start a PHY write operation. Does not block, requires calling
 * IP_ENET_IsMIIBusy to determine when write is complete.
 */
void IP_ENET_StartMIIWrite(IP_ENET_001_Type *LPC_ENET, uint8_t reg, uint16_t data);

/**
 * @brief	Starts a PHY read via the MII
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @param	reg			: PHY register to read
 * @return	Nothing
 * Start a PHY read operation. Does not block, requires calling
 * IP_ENET_IsMIIBusy to determine when read is complete and calling
 * IP_ENET_ReadMIIData to get the data.
 */
void IP_ENET_StartMIIRead(IP_ENET_001_Type *LPC_ENET, uint8_t reg);

/**
 * @brief	Returns MII link (PHY) busy status
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @return	Returns true if busy, otherwise false
 */
bool IP_ENET_IsMIIBusy(IP_ENET_001_Type *LPC_ENET);

/**
 * @brief	Returns the value read from the PHY
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @return	Read value from PHY
 */
STATIC INLINE uint16_t IP_ENET_ReadMIIData(IP_ENET_001_Type *LPC_ENET)
{
	return LPC_ENET->MAC_MII_DATA;
}

/**
 * @brief	Enables or disables ethernet transmit
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @param	Enable		: true to enable transmit, false to disable
 * @return	Nothing
 */
void IP_ENET_TXEnable(IP_ENET_001_Type *LPC_ENET, bool Enable);

/**
 * @brief	Enables or disables ethernet packet reception
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @param	Enable		: true to enable receive, false to disable
 * @return	Nothing
 */
void IP_ENET_RXEnable(IP_ENET_001_Type *LPC_ENET, bool Enable);

/**
 * @brief	Sets full or half duplex for the interface
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @param	full		: true to selected full duplex, false for half
 * @return	Nothing
 */
void IP_ENET_SetDuplex(IP_ENET_001_Type *LPC_ENET, bool full);

/**
 * @brief	Sets speed for the interface
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @param	speed100	: true to select 100Mbps mode, false for 10Mbps
 * @return	Nothing
 */
void IP_ENET_SetSpeed(IP_ENET_001_Type *LPC_ENET, bool speed100);

/**
 * @brief	Configures the initial ethernet descriptors
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @param	pTXDescs	: Pointer to TX descriptor list
 * @param	pRXDescs	: Pointer to RX descriptor list
 * @return	Nothing
 */
void IP_ENET_InitDescriptors(IP_ENET_001_Type *LPC_ENET,
							 IP_ENET_001_ENHTXDESC_Type *pTXDescs, IP_ENET_001_ENHRXDESC_Type *pRXDescs);

/**
 * @brief	Starts receive polling of RX descriptors
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @return	Nothing
 */
STATIC INLINE void IP_ENET_RXStart(IP_ENET_001_Type *LPC_ENET)
{
	/* Start receive polling */
	LPC_ENET->DMA_REC_POLL_DEMAND = 1;
}

/**
 * @brief	Starts transmit polling of TX descriptors
 * @param	LPC_ENET	: Pointer to selected ENET peripheral
 * @return	Nothing
 */
STATIC INLINE void IP_ENET_TXStart(IP_ENET_001_Type *LPC_ENET)
{
	/* Start transmit polling */
	LPC_ENET->DMA_TRANS_POLL_DEMAND = 1;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ENET_001_H_ */
