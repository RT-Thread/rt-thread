/*
 * Copyright 2020-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_ENET_QOS_H_
#define _FSL_ENET_QOS_H_

#include "fsl_common.h"
#if defined(FSL_ETH_ENABLE_CACHE_CONTROL)
#include "fsl_cache.h"
#endif
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
#include "fsl_memory.h"
#endif

#if !defined(ENET_QOS)
/* Keep reusing ENET_QOS for platforms which renames it to Ethernet Controller with TSN (EQoS-TSN) */
#if defined(ENET_QOS_TSN)
#define ENET_QOS ENET_QOS_TSN
#endif
#endif
/*!
 * @addtogroup enet_qos_qos
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Defines the driver version. */
#define FSL_ENET_QOS_DRIVER_VERSION (MAKE_VERSION(2, 4, 1))
/*@}*/

/*! @name Control and status region bit masks of the receive buffer descriptor. */
/*@{*/
/*! @brief Defines for read format. */
#define ENET_QOS_RXDESCRIP_RD_BUFF1VALID_MASK (1UL << 24U) /*!< Buffer1 address valid. */
#define ENET_QOS_RXDESCRIP_RD_BUFF2VALID_MASK (1UL << 25U) /*!< Buffer2 address valid. */
#define ENET_QOS_RXDESCRIP_RD_IOC_MASK        (1UL << 30U) /*!< Interrupt enable on complete. */
#define ENET_QOS_RXDESCRIP_RD_OWN_MASK        (1UL << 31U) /*!< Own bit. */

/*! @brief Defines for write back format. */
#define ENET_QOS_RXDESCRIP_WR_ERR_MASK        ((1UL << 3U) | (1UL << 7U))
#define ENET_QOS_RXDESCRIP_WR_PYLOAD_MASK     (0x7UL)
#define ENET_QOS_RXDESCRIP_WR_PTPMSGTYPE_MASK (0xF00UL)
#define ENET_QOS_RXDESCRIP_WR_PTPTYPE_MASK    (1UL << 12U)
#define ENET_QOS_RXDESCRIP_WR_PTPVERSION_MASK (1UL << 13U)
#define ENET_QOS_RXDESCRIP_WR_PTPTSA_MASK     (1UL << 14U)
#define ENET_QOS_RXDESCRIP_WR_PACKETLEN_MASK  (0x7FFFUL)
#define ENET_QOS_RXDESCRIP_WR_ERRSUM_MASK     (1UL << 15U)
#define ENET_QOS_RXDESCRIP_WR_TYPE_MASK       (0x30000UL)
#define ENET_QOS_RXDESCRIP_WR_DE_MASK         (1UL << 19U)
#define ENET_QOS_RXDESCRIP_WR_RE_MASK         (1UL << 20U)
#define ENET_QOS_RXDESCRIP_WR_OE_MASK         (1UL << 21U)
#define ENET_QOS_RXDESCRIP_WR_RWT_MASK        (1UL << 22U)
#define ENET_QOS_RXDESCRIP_WR_GP_MASK         (1UL << 22U)
#define ENET_QOS_RXDESCRIP_WR_CRC_MASK        (1UL << 23U)
#define ENET_QOS_RXDESCRIP_WR_RS0V_MASK       (1UL << 25U)
#define ENET_QOS_RXDESCRIP_WR_RS1V_MASK       (1UL << 26U)
#define ENET_QOS_RXDESCRIP_WR_RS2V_MASK       (1UL << 27U)
#define ENET_QOS_RXDESCRIP_WR_LD_MASK         (1UL << 28U)
#define ENET_QOS_RXDESCRIP_WR_FD_MASK         (1UL << 29U)
#define ENET_QOS_RXDESCRIP_WR_CTXT_MASK       (1UL << 30U)
#define ENET_QOS_RXDESCRIP_WR_OWN_MASK        (1UL << 31U)

#define ENET_QOS_RXDESCRIP_WR_SA_FAILURE_MASK (1UL << 16U)
#define ENET_QOS_RXDESCRIP_WR_DA_FAILURE_MASK (1UL << 17U)
/*@}*/

/*! @name Control and status bit masks of the transmit buffer descriptor. */
/*@{*/
/*! @brief Defines for read format. */
#define ENET_QOS_TXDESCRIP_RD_BL1_MASK  (0x3fffUL)
#define ENET_QOS_TXDESCRIP_RD_BL2_MASK  (ENET_QOS_TXDESCRIP_RD_BL1_MASK << 16U)
#define ENET_QOS_TXDESCRIP_RD_BL1(n)    ((uint32_t)(n)&ENET_QOS_TXDESCRIP_RD_BL1_MASK)
#define ENET_QOS_TXDESCRIP_RD_BL2(n)    (((uint32_t)(n)&ENET_QOS_TXDESCRIP_RD_BL1_MASK) << 16)
#define ENET_QOS_TXDESCRIP_RD_TTSE_MASK (1UL << 30UL)
#define ENET_QOS_TXDESCRIP_RD_IOC_MASK  (1UL << 31UL)

#define ENET_QOS_TXDESCRIP_RD_FL_MASK   (0x7FFFUL)
#define ENET_QOS_TXDESCRIP_RD_FL(n)     ((uint32_t)(n)&ENET_QOS_TXDESCRIP_RD_FL_MASK)
#define ENET_QOS_TXDESCRIP_RD_CIC(n)    (((uint32_t)(n)&0x3U) << 16U)
#define ENET_QOS_TXDESCRIP_RD_TSE_MASK  (1UL << 18U)
#define ENET_QOS_TXDESCRIP_RD_SLOT(n)   (((uint32_t)(n)&0x0fU) << 19U)
#define ENET_QOS_TXDESCRIP_RD_SAIC(n)   (((uint32_t)(n)&0x07U) << 23U)
#define ENET_QOS_TXDESCRIP_RD_CPC(n)    (((uint32_t)(n)&0x03U) << 26U)
#define ENET_QOS_TXDESCRIP_RD_LDFD(n)   (((uint32_t)(n)&0x03U) << 28U)
#define ENET_QOS_TXDESCRIP_RD_LD_MASK   (1UL << 28U)
#define ENET_QOS_TXDESCRIP_RD_FD_MASK   (1UL << 29U)
#define ENET_QOS_TXDESCRIP_RD_CTXT_MASK (1UL << 30U)
#define ENET_QOS_TXDESCRIP_RD_OWN_MASK  (1UL << 31U)

/*! @brief Defines for write back format. */
#define ENET_QOS_TXDESCRIP_WB_TTSS_MASK (1UL << 17U)
/*@}*/

/*! @name Bit mask for interrupt enable type. */
/*@{*/
#define ENET_QOS_ABNORM_INT_MASK                                                                                \
    (ENET_QOS_DMA_CHX_INT_EN_TXSE_MASK | ENET_QOS_DMA_CHX_INT_EN_RBUE_MASK | ENET_QOS_DMA_CHX_INT_EN_RSE_MASK | \
     ENET_QOS_DMA_CHX_INT_EN_RWTE_MASK | ENET_QOS_DMA_CHX_INT_EN_FBEE_MASK | ENET_QOS_DMA_CHX_INT_EN_ETIE_MASK)
#define ENET_QOS_NORM_INT_MASK                                                                                 \
    (ENET_QOS_DMA_CHX_INT_EN_TIE_MASK | ENET_QOS_DMA_CHX_INT_EN_TBUE_MASK | ENET_QOS_DMA_CHX_INT_EN_RIE_MASK | \
     ENET_QOS_DMA_CHX_INT_EN_ERIE_MASK)
/*@}*/

/*! @name Defines some Ethernet parameters. */
/*@{*/
#ifndef ENET_QOS_RING_NUM_MAX
#define ENET_QOS_RING_NUM_MAX (5U) /*!< The Maximum number of tx/rx descriptor rings. */
#endif
#define ENET_QOS_FRAME_MAX_FRAMELEN (1518U) /*!< Default maximum Ethernet frame size. */
#define ENET_QOS_FCS_LEN            (4U)    /*!< Ethernet FCS length. */
#define ENET_QOS_ADDR_ALIGNMENT     (0x3U)  /*!< Recommended Ethernet buffer alignment. */
#define ENET_QOS_BUFF_ALIGNMENT     (8U)    /*!< Receive buffer alignment shall be 4bytes-aligned. */
#define ENET_QOS_MTL_RXFIFOSIZE     (8192U) /*!< The rx fifo size. */
#define ENET_QOS_MTL_TXFIFOSIZE     (8192U) /*!< The tx fifo size. */
#define ENET_QOS_MACINT_ENUM_OFFSET (16U)   /*!< The offest for mac interrupt in enum type. */
#define ENET_QOS_RXP_ENTRY_COUNT    (256U)  /*!< RXP table entry count, implied by FRPES in MAC_HW_FEATURE3 */
#define ENET_QOS_RXP_BUFFER_SIZE    (256U)  /*!< RXP Buffer size, implied by FRPBS in MAC_HW_FEATURE3 */
#define ENET_QOS_EST_WID            (24U)   /*!< Width of the time interval in Gate Control List */
#define ENET_QOS_EST_DEP            (512U)  /*!< Maxmimum depth of Gate Control List */
/*@}*/

/*! @brief Defines the status return codes for transaction. */
enum
{
    kStatus_ENET_QOS_InitMemoryFail =
        MAKE_STATUS(kStatusGroup_ENET_QOS, 0U), /*!< Init fails since buffer memory is not enough. */
    kStatus_ENET_QOS_RxFrameError =
        MAKE_STATUS(kStatusGroup_ENET_QOS, 1U), /*!< A frame received but data error happen. */
    kStatus_ENET_QOS_RxFrameFail  = MAKE_STATUS(kStatusGroup_ENET_QOS, 2U), /*!< Failed to receive a frame. */
    kStatus_ENET_QOS_RxFrameEmpty = MAKE_STATUS(kStatusGroup_ENET_QOS, 3U), /*!< No frame arrive. */
    kStatus_ENET_QOS_RxFrameDrop =
        MAKE_STATUS(kStatusGroup_ENET_QOS, 4U), /*!< Rx frame is dropped since no buffer memory. */
    kStatus_ENET_QOS_TxFrameBusy =
        MAKE_STATUS(kStatusGroup_ENET_QOS, 5U), /*!< Transmit descriptors are under process. */
    kStatus_ENET_QOS_TxFrameFail    = MAKE_STATUS(kStatusGroup_ENET_QOS, 6U), /*!< Transmit frame fail. */
    kStatus_ENET_QOS_TxFrameOverLen = MAKE_STATUS(kStatusGroup_ENET_QOS, 7U), /*!< Transmit oversize. */
    kStatus_ENET_QOS_Est_SwListBusy =
        MAKE_STATUS(kStatusGroup_ENET_QOS, 8U), /*!< SW Gcl List not yet processed by HW. */
    kStatus_ENET_QOS_Est_SwListWriteAbort = MAKE_STATUS(kStatusGroup_ENET_QOS, 9U), /*!< SW Gcl List write aborted .*/
    kStatus_ENET_QOS_Est_InvalidParameter =
        MAKE_STATUS(kStatusGroup_ENET_QOS, 10U),                             /*!< Invalid parameter in Gcl List .*/
    kStatus_ENET_QOS_Est_BtrError = MAKE_STATUS(kStatusGroup_ENET_QOS, 11U), /*!< Base Time Error when loading list.*/
    kStatus_ENET_QOS_TrgtBusy     = MAKE_STATUS(kStatusGroup_ENET_QOS, 12U), /*!< Target time register busy.*/
    kStatus_ENET_QOS_Timeout      = MAKE_STATUS(kStatusGroup_ENET_QOS, 13U), /*!< Target time register busy.*/
    kStatus_ENET_QOS_PpsBusy      = MAKE_STATUS(kStatusGroup_ENET_QOS, 14U)  /*!< Pps command busy.*/
};

/*! @brief Defines the MII/RGMII mode for data interface between the MAC and the PHY. */
typedef enum _enet_qos_mii_mode
{
    kENET_QOS_MiiMode   = 0U, /*!< MII mode for data interface. */
    kENET_QOS_RgmiiMode = 1U, /*!< RGMII mode for data interface. */
    kENET_QOS_RmiiMode  = 4U  /*!< RMII mode for data interface. */
} enet_qos_mii_mode_t;

/*! @brief Defines the 10/100/1000 Mbps speed for the MII data interface. */
typedef enum _enet_qos_mii_speed
{
    kENET_QOS_MiiSpeed10M =
        ENET_QOS_MAC_CONFIGURATION_PS(1U) | ENET_QOS_MAC_CONFIGURATION_FES(0U), /*!< Speed 10 Mbps. */
    kENET_QOS_MiiSpeed100M =
        ENET_QOS_MAC_CONFIGURATION_PS(1U) | ENET_QOS_MAC_CONFIGURATION_FES(1U), /*!< Speed 100 Mbps. */
    kENET_QOS_MiiSpeed1000M =
        ENET_QOS_MAC_CONFIGURATION_PS(0U) | ENET_QOS_MAC_CONFIGURATION_FES(0U), /*!< Speed 1000 Mbps. */
    kENET_QOS_MiiSpeed2500M =
        ENET_QOS_MAC_CONFIGURATION_PS(0U) | ENET_QOS_MAC_CONFIGURATION_FES(1U) /*!< Speed 2500 Mbps. */
} enet_qos_mii_speed_t;

/*! @brief Defines the half or full duplex for the MII data interface. */
typedef enum _enet_qos_mii_duplex
{
    kENET_QOS_MiiHalfDuplex = 0U, /*!< Half duplex mode. */
    kENET_QOS_MiiFullDuplex       /*!< Full duplex mode. */
} enet_qos_mii_duplex_t;

/*! @brief Define the MII opcode for normal MDIO_CLAUSES_22 Frame. */
typedef enum _enet_qos_mii_normal_opcode
{
    kENET_QOS_MiiWriteFrame =
        ENET_QOS_MAC_MDIO_ADDRESS_GOC_1(0U) |
        ENET_QOS_MAC_MDIO_ADDRESS_GOC_0(1U), /*!< Write frame operation for a valid MII management frame. */
    kENET_QOS_MiiReadFrame =
        ENET_QOS_MAC_MDIO_ADDRESS_GOC_1(1U) |
        ENET_QOS_MAC_MDIO_ADDRESS_GOC_0(1U) /*!< Read frame operation for a valid MII management frame. */
} enet_qos_mii_normal_opcode;

/*! @brief Define the DMA maximum transmit burst length. */
typedef enum _enet_qos_dma_burstlen
{
    kENET_QOS_BurstLen1   = 0x00001U, /*!< DMA burst length 1. */
    kENET_QOS_BurstLen2   = 0x00002U, /*!< DMA burst length 2. */
    kENET_QOS_BurstLen4   = 0x00004U, /*!< DMA burst length 4. */
    kENET_QOS_BurstLen8   = 0x00008U, /*!< DMA burst length 8. */
    kENET_QOS_BurstLen16  = 0x00010U, /*!< DMA burst length 16. */
    kENET_QOS_BurstLen32  = 0x00020U, /*!< DMA burst length 32. */
    kENET_QOS_BurstLen64  = 0x10008U, /*!< DMA burst length 64. eight times enabled. */
    kENET_QOS_BurstLen128 = 0x10010U, /*!< DMA burst length 128. eight times enabled. */
    kENET_QOS_BurstLen256 = 0x10020U, /*!< DMA burst length 256. eight times enabled. */
} enet_qos_dma_burstlen;

/*! @brief Define the flag for the descriptor. */
typedef enum _enet_qos_desc_flag
{
    kENET_QOS_MiddleFlag = 0, /*!< It's a middle descriptor of the frame. */
    kENET_QOS_LastFlagOnly,   /*!< It's the last descriptor of the frame. */
    kENET_QOS_FirstFlagOnly,  /*!< It's the first descriptor of the frame. */
    kENET_QOS_FirstLastFlag   /*!< It's the first and last descriptor of the frame. */
} enet_qos_desc_flag;

/*! @brief Define the system time adjust operation control. */
typedef enum _enet_qos_systime_op
{
    kENET_QOS_SystimeAdd      = 0U, /*!< System time add to. */
    kENET_QOS_SystimeSubtract = 1U  /*!< System time subtract. */
} enet_qos_systime_op;

/*! @brief Define the system time rollover control. */
typedef enum _enet_qos_ts_rollover_type
{
    kENET_QOS_BinaryRollover  = 0, /*!< System time binary rollover.*/
    kENET_QOS_DigitalRollover = 1  /*!< System time digital rollover.*/
} enet_qos_ts_rollover_type;

/*! @brief Defines some special configuration for ENET.
 *
 * These control flags are provided for special user requirements.
 * Normally, these is no need to set this control flags for ENET initialization.
 * But if you have some special requirements, set the flags to specialControl
 * in the enet_qos_config_t.
 * @note "kENET_QOS_StoreAndForward" is recommended to be set.
 */
typedef enum _enet_qos_special_config
{

    /***********************DMA CONFGI**********************************************/
    kENET_QOS_DescDoubleBuffer = 0x0001U, /*!< The double buffer is used in the tx/rx descriptor. */
    /**************************MTL************************************/
    kENET_QOS_StoreAndForward = 0x0002U, /*!< The rx/tx store and forward enable. */
    /***********************MAC****************************************/
    kENET_QOS_PromiscuousEnable   = 0x0004U, /*!< The promiscuous enabled. */
    kENET_QOS_FlowControlEnable   = 0x0008U, /*!< The flow control enabled. */
    kENET_QOS_BroadCastRxDisable  = 0x0010U, /*!< The broadcast disabled. */
    kENET_QOS_MulticastAllEnable  = 0x0020U, /*!< All multicast are passed. */
    kENET_QOS_8023AS2KPacket      = 0x0040U, /*!< 8023as support for 2K packets. */
    kENET_QOS_HashMulticastEnable = 0x0080U  /*!< The multicast packets are filtered through hash table. */
} enet_qos_special_config_t;

/*! @brief List of DMA interrupts supported by the ENET interrupt. This
 * enumeration uses one-bot encoding to allow a logical OR of multiple
 * members.
 */
typedef enum _enet_qos_dma_interrupt_enable
{
    kENET_QOS_DmaTx                = ENET_QOS_DMA_CHX_INT_EN_TIE_MASK,  /*!< Tx interrupt. */
    kENET_QOS_DmaTxStop            = ENET_QOS_DMA_CHX_INT_EN_TXSE_MASK, /*!< Tx stop interrupt. */
    kENET_QOS_DmaTxBuffUnavail     = ENET_QOS_DMA_CHX_INT_EN_TBUE_MASK, /*!< Tx buffer unavailable. */
    kENET_QOS_DmaRx                = ENET_QOS_DMA_CHX_INT_EN_RIE_MASK,  /*!< Rx interrupt. */
    kENET_QOS_DmaRxBuffUnavail     = ENET_QOS_DMA_CHX_INT_EN_RBUE_MASK, /*!< Rx buffer unavailable. */
    kENET_QOS_DmaRxStop            = ENET_QOS_DMA_CHX_INT_EN_RSE_MASK,  /*!< Rx stop. */
    kENET_QOS_DmaRxWatchdogTimeout = ENET_QOS_DMA_CHX_INT_EN_RWTE_MASK, /*!< Rx watchdog timeout. */
    kENET_QOS_DmaEarlyTx           = ENET_QOS_DMA_CHX_INT_EN_ETIE_MASK, /*!< Early transmit. */
    kENET_QOS_DmaEarlyRx           = ENET_QOS_DMA_CHX_INT_EN_ERIE_MASK, /*!< Early receive. */
    kENET_QOS_DmaBusErr            = ENET_QOS_DMA_CHX_INT_EN_FBEE_MASK, /*!< Fatal bus error. */
} enet_qos_dma_interrupt_enable_t;

/*! @brief List of mac interrupts supported by the ENET interrupt. This
 * enumeration uses one-bot encoding to allow a logical OR of multiple
 * members.
 */
typedef enum _enet_qos_mac_interrupt_enable
{
    kENET_QOS_MacPmt       = (ENET_QOS_MAC_INTERRUPT_ENABLE_PMTIE_MASK << ENET_QOS_MACINT_ENUM_OFFSET),
    kENET_QOS_MacTimestamp = (ENET_QOS_MAC_INTERRUPT_ENABLE_TSIE_MASK << ENET_QOS_MACINT_ENUM_OFFSET),
} enet_qos_mac_interrupt_enable_t;

/*! @brief Defines the common interrupt event for callback use. */
typedef enum _enet_qos_event
{
    kENET_QOS_RxIntEvent,        /*!< Receive interrupt event. */
    kENET_QOS_TxIntEvent,        /*!< Transmit interrupt event. */
    kENET_QOS_WakeUpIntEvent,    /*!< Wake up interrupt event. */
    kENET_QOS_TimeStampIntEvent, /*!< Time stamp interrupt event. */
} enet_qos_event_t;

/*! @brief Define the MTL mode for multiple queues/rings. */
typedef enum _enet_qos_queue_mode
{
    kENET_QOS_AVB_Mode = 1U, /*!< Enable queue in AVB mode. */
    kENET_QOS_DCB_Mode = 2U, /*!< Enable queue in DCB mode. */
} enet_qos_queue_mode_t;

/*! @brief Define the MTL tx scheduling algorithm for multiple queues/rings. */
typedef enum _enet_qos_mtl_multiqueue_txsche
{
    kENET_QOS_txWeightRR       = 0U, /*!< Tx weight round-robin. */
    kENET_QOS_txWeightFQ       = 1U, /*!< Tx weight fair queuing. */
    kENET_QOS_txDefictWeightRR = 2U, /*!< Tx deficit weighted round-robin. */
    kENET_QOS_txStrPrio        = 3U, /*!< Tx strict priority. */
} enet_qos_mtl_multiqueue_txsche;

/*! @brief Define the MTL rx scheduling algorithm for multiple queues/rings. */
typedef enum _enet_qos_mtl_multiqueue_rxsche
{
    kENET_QOS_rxStrPrio = 0U,  /*!< Rx strict priority, Queue 0 has the lowest priority. */
    kENET_QOS_rxWeightStrPrio, /*!< Weighted Strict Priority. */
} enet_qos_mtl_multiqueue_rxsche;

/*! @brief Define the MTL rx queue and DMA channel mapping. */
typedef enum _enet_qos_mtl_rxqueuemap
{
    kENET_QOS_StaticDirctMap = 0x100U, /*!< The received fame in rx Qn(n = 0,1) directly map to dma channel n. */
    kENET_QOS_DynamicMap =
        0x1010U, /*!< The received frame in rx Qn(n = 0,1) map to the dma channel m(m = 0,1) related with the same Mac.
                  */
} enet_qos_mtl_rxqueuemap_t;

/*! @brief Defines the package type for receive queue routing. */
typedef enum _enet_qos_rx_queue_route
{
    kENET_QOS_PacketNoQ    = 0x0,        /* Not specific queue */
    kENET_QOS_PacketAVCPQ  = (1U << 0U), /* AV Untagged Control Packets Queue */
    kENET_QOS_PacketPTPQ   = (1U << 1U), /* PTP Packets Queue */
    kENET_QOS_PacketDCBCPQ = (1U << 2U), /* DCB Control Packets Queue */
    kENET_QOS_PacketUPQ    = (1U << 3U), /* Untagged Packets Queue */
    kENET_QOS_PacketMCBCQ  = (1U << 4U), /* Multicast & Broadcast Packets Queue */
} enet_qos_rx_queue_route_t;

/*! @brief Defines the ENET PTP message related constant. */
typedef enum _enet_qos_ptp_event_type
{
    kENET_QOS_PtpEventMsgType = 3U,   /*!< PTP event message type. */
    kENET_QOS_PtpSrcPortIdLen = 10U,  /*!< PTP message sequence id length. */
    kENET_QOS_PtpEventPort    = 319U, /*!< PTP event port number. */
    kENET_QOS_PtpGnrlPort     = 320U  /*!< PTP general port number. */
} enet_qos_ptp_event_type_t;

/*! @brief Defines the PPS instance numbers. */
typedef enum _enet_qos_ptp_pps_instance
{
    kENET_QOS_PtpPpsIstance0 = 0U, /*!< PPS instance 0. */
    kENET_QOS_PtpPpsIstance1,      /*!< PPS instance 1. */
    kENET_QOS_PtpPpsIstance2,      /*!< PPS instance 2. */
    kENET_QOS_PtpPpsIstance3       /*!< PPS instance 3. */
} enet_qos_ptp_pps_instance_t;

/*! @brief Defines the Target Time register mode. */
typedef enum _enet_qos_ptp_pps_trgt_mode
{
    kENET_QOS_PtpPpsTrgtModeOnlyInt = 0U, /*!< Only interrupts. */
    kENET_QOS_PtpPpsTrgtModeIntSt   = 2,  /*!< Both interrupt and output signal. */
    kENET_QOS_PtpPpsTrgtModeOnlySt  = 3,  /*!< Only output signal. */
} enet_qos_ptp_pps_trgt_mode_t;

/*! @brief Defines commands for ppscmd register. */
typedef enum _enet_qos_ptp_pps_cmd
{
    kENET_QOS_PtpPpsCmdNC    = 0U, /*!< No Command. */
    kENET_QOS_PtpPpsCmdSSP   = 1U, /*!< Start Single Pulse. */
    kENET_QOS_PtpPpsCmdSPT   = 2U, /*!< Start Pulse Train. */
    kENET_QOS_PtpPpsCmdCS    = 3U, /*!< Cancel Start. */
    kENET_QOS_PtpPpsCmdSPTAT = 4U, /*!< Stop Pulse Train At Time. */
    kENET_QOS_PtpPpsCmdSPTI  = 5U, /*!< Stop Pulse Train Immediately. */
    kENET_QOS_PtpPpsCmdCSPT  = 6U, /*!< Cancel Stop Pulse Train. */
} enet_qos_ptp_pps_cmd_t;

/*! @brief Defines the enmueration of ETS list length.
 */
typedef enum _enet_qos_ets_list_length
{
    kENET_QOS_Ets_List_64   = 7U,  /*!< List length of 64 */
    kENET_QOS_Ets_List_128  = 8U,  /*!< List length of 128 */
    kENET_QOS_Ets_List_256  = 9U,  /*!< List length of 256 */
    kENET_QOS_Ets_List_512  = 10U, /*!< List length of 512 */
    kENET_QOS_Ets_List_1024 = 11U, /*!< List length of 1024 */
} enet_qos_ets_list_length_t;

/*! @brief Defines the enmueration of ETS gate control address.
 */
typedef enum _enet_qos_ets_gccr_addr
{
    kENET_QOS_Ets_btr_low  = 0U, /*!< BTR Low */
    kENET_QOS_Ets_btr_high = 1U, /*!< BTR High */
    kENET_QOS_Ets_ctr_low  = 2U, /*!< CTR Low */
    kENET_QOS_Ets_ctr_high = 3U, /*!< CTR High */
    kENET_QOS_Ets_ter      = 4U, /*!< TER */
    kENET_QOS_Ets_llr      = 5U, /*!< LLR */
} enet_qos_ets_gccr_addr_t;

/*! @brief Defines the enmueration of DMA channel used
 * for rx parser entry.
 */
typedef enum _enet_qos_rxp_dma_chn
{
    kENET_QOS_Rxp_DMAChn0 = 1U,  /*!< DMA Channel 0 used for RXP entry match */
    kENET_QOS_Rxp_DMAChn1 = 2U,  /*!< DMA Channel 1 used for RXP entry match */
    kENET_QOS_Rxp_DMAChn2 = 4U,  /*!< DMA Channel 2 used for RXP entry match */
    kENET_QOS_Rxp_DMAChn3 = 8U,  /*!< DMA Channel 3 used for RXP entry match */
    kENET_QOS_Rxp_DMAChn4 = 16U, /*!< DMA Channel 4 used for RXP entry match */
} enet_qos_rxp_dma_chn_t;

/*! @brief Defines the receive descriptor structure
 *  has the read-format and write-back format structure. They both
 *  has the same size with different region definition. so
 *  we define the read-format region as the receive descriptor structure
 *  Use the read-format region mask bits in the descriptor initialization
 *  Use the write-back format region mask bits in the receive data process.
 */
typedef struct _enet_qos_rx_bd_struct
{
    __IO uint32_t buff1Addr; /*!< Buffer 1 address */
    __IO uint32_t reserved;  /*!< Reserved */
    __IO uint32_t buff2Addr; /*!< Buffer 2 or next descriptor address */
    __IO uint32_t control;   /*!< Buffer 1/2 byte counts and control */
} enet_qos_rx_bd_struct_t;

/*! @brief Defines the transmit descriptor structure
 *  has the read-format and write-back format structure. They both
 *  has the same size with different region definition. so
 *  we define the read-format region as the transmit descriptor structure
 *  Use the read-format region mask bits in the descriptor initialization
 *  Use the write-back format region mask bits in the transmit data process.
 */
typedef struct _enet_qos_tx_bd_struct
{
    __IO uint32_t buff1Addr;   /*!< Buffer 1 address */
    __IO uint32_t buff2Addr;   /*!< Buffer 2 address */
    __IO uint32_t buffLen;     /*!< Buffer 1/2 byte counts */
    __IO uint32_t controlStat; /*!< TDES control and status word */
} enet_qos_tx_bd_struct_t;

/*! @brief Defines the ENET PTP time stamp structure. */
typedef struct _enet_qos_ptp_time
{
    uint64_t second;     /*!< Second. */
    uint32_t nanosecond; /*!< Nanosecond. */
} enet_qos_ptp_time_t;

/*! @brief Defines the frame info structure. */
typedef struct enet_qos_frame_info
{
    void *context;                 /*!< User specified data, could be buffer address for free */
    bool isTsAvail;                /*!< Flag indicates timestamp available status */
    enet_qos_ptp_time_t timeStamp; /*!< Timestamp of frame */
} enet_qos_frame_info_t;

/*! @brief Defines the ENET transmit dirty addresses ring/queue structure. */
typedef struct _enet_qos_tx_dirty_ring
{
    enet_qos_frame_info_t *txDirtyBase; /*!< Dirty buffer descriptor base address pointer. */
    uint16_t txGenIdx;                  /*!< tx generate index. */
    uint16_t txConsumIdx;               /*!< tx consume index. */
    uint16_t txRingLen;                 /*!< tx ring length. */
    bool isFull;                        /*!< tx ring is full flag, add this parameter to avoid waste one element. */
} enet_qos_tx_dirty_ring_t;

/*! @brief Defines the ENET PTP configuration structure. */
typedef struct _enet_qos_ptp_config
{
    bool fineUpdateEnable;       /*!< Use the fine update. */
    uint32_t defaultAddend;      /*!< Default addend value when fine update is enable, could be 2^32 / (refClk_Hz /
                                    ENET_QOS_MICRSECS_ONESECOND / ENET_QOS_SYSTIME_REQUIRED_CLK_MHZ). */
    uint32_t systemTimeClock_Hz; /*! The desired system time frequency. Must be lower than reference clock. (Only used
                                    with fine correction method). */
    bool ptp1588V2Enable;        /*!< ptp 1588 version 2 is used. */
    enet_qos_ts_rollover_type tsRollover; /*!< 1588 time nanosecond rollover. */
} enet_qos_ptp_config_t;

/*! @brief Defines the EST gate operation structure. */
typedef struct _enet_qos_est_gate_op
{
    uint32_t gate;
    uint32_t interval;
} enet_qos_est_gate_op_t;

/*! @brief Defines the EST gate control list structure. */
typedef struct _enet_qos_est_gcl
{
    bool enable;                    /*!< Enable or disable EST */
    uint64_t baseTime;              /*! Base Time 32 bits seconds 32 bits nanoseconds */
    uint64_t cycleTime;             /*! Cycle Time 32 bits seconds 32 bits nanoseconds */
    uint32_t extTime;               /*! Time Extension 32 bits seconds 32 bits nanoseconds */
    uint32_t numEntries;            /*! Number of entries */
    enet_qos_est_gate_op_t *opList; /*! Pointer to GCL list size */
} enet_qos_est_gcl_t;

/*! @brief Defines the ENET_QOS Rx parser configuration structure.*/
typedef struct _enet_qos_rxp_config
{
    uint32_t matchData;       /*! 4-byte match data used for comparing with incoming packet */
    uint32_t matchEnable;     /*! When matchEnable is set to 1, the matchData is used for comparing */
    uint8_t acceptFrame : 1;  /*! When acceptFrame = 1 and data is matched, the frame will be sent to DMA channel */
    uint8_t rejectFrame : 1;  /*! When rejectFrame = 1 and data is matched, the frame will be dropped */
    uint8_t inverseMatch : 1; /*! Inverse match */
    uint8_t nextControl : 1;  /*! Next instruction indexing control */
    uint8_t reserved : 4;     /*! Reserved control fields */
    uint8_t frameOffset;      /*! Frame offset in the packet data to be compared for match, in terms of 4 bytes. */
    uint8_t okIndex;          /*! Memory Index to be used next. */
    uint8_t dmaChannel; /*! The DMA channel enet_qos_rxp_dma_chn_t used for receiving the frame when frame match and
                           acceptFrame = 1 */
    uint32_t reserved2; /*! Reserved for future enhancements */
} enet_qos_rxp_config_t;

/*! @brief Defines the buffer descriptor configure structure.
 *
 * @note
 * 1. The receive and transmit descriptor start address pointer and tail pointer must be word-aligned.
 * 2. The recommended minimum tx/rx ring length is 4.
 * 3. The tx/rx descriptor tail address shall be the address pointer to the address just after the end
 *    of the last last descriptor. because only the descriptors between the start address and the
 *    tail address will be used by DMA.
 * 4. The descriptor address is the start address of all used contiguous memory.
 *    for example, the rxDescStartAddrAlign is the start address of rxRingLen contiguous descriptor memories
 *    for rx descriptor ring 0.
 * 5. The "*rxBufferstartAddr" is the first element of  rxRingLen (2*rxRingLen for double buffers)
 *    rx buffers. It means the *rxBufferStartAddr is the rx buffer for the first descriptor
 *    the *rxBufferStartAddr + 1 is the rx buffer for the second descriptor or the rx buffer for
 *    the second buffer in the first descriptor. so please make sure the rxBufferStartAddr is the
 *    address of a rxRingLen or 2*rxRingLen array.
 */
typedef struct _enet_qos_buffer_config
{
    uint8_t rxRingLen;                             /*!< The length of receive buffer descriptor ring. */
    uint8_t txRingLen;                             /*!< The length of transmit buffer descriptor ring. */
    enet_qos_tx_bd_struct_t *txDescStartAddrAlign; /*!< Aligned transmit descriptor start address. */
    enet_qos_tx_bd_struct_t *txDescTailAddrAlign;  /*!< Aligned transmit descriptor tail address. */
    enet_qos_frame_info_t *txDirtyStartAddr;       /*!< Start address of the dirty tx frame information. */
    enet_qos_rx_bd_struct_t *rxDescStartAddrAlign; /*!< Aligned receive descriptor start address. */
    enet_qos_rx_bd_struct_t *rxDescTailAddrAlign;  /*!< Aligned receive descriptor tail address. */
    uint32_t *rxBufferStartAddr;                   /*!< Start address of the rx buffers. */
    uint32_t rxBuffSizeAlign;                      /*!< Aligned receive data buffer size. */
    bool rxBuffNeedMaintain;                       /*!< Whether receive data buffer need cache maintain. */
} enet_qos_buffer_config_t;

/*! @brief Defines the CBS configuration for queue. */
typedef struct _enet_qos_cbs_config
{
    uint16_t sendSlope;  /*!< Send slope configuration. */
    uint16_t idleSlope;  /*!< Idle slope configuration. */
    uint32_t highCredit; /*!< High credit. */
    uint32_t lowCredit;  /*!< Low credit. */
} enet_qos_cbs_config_t;

/*! @brief Defines the queue configuration structure. */
typedef struct enet_qos_tx_queue_config
{
    enet_qos_queue_mode_t mode;       /*!< tx queue mode configuration. */
    uint32_t weight;                  /*!< Refer to the MTL TxQ Quantum Weight register. */
    uint32_t priority;                /*!< Refer to Transmit Queue Priority Mapping register. */
    enet_qos_cbs_config_t *cbsConfig; /*!< CBS configuration if queue use AVB mode. */
} enet_qos_queue_tx_config_t;

/*! @brief Defines the queue configuration structure. */
typedef struct enet_qos_rx_queue_config
{
    enet_qos_queue_mode_t mode;            /*!< rx queue mode configuration. */
    uint8_t mapChannel;                    /*!< tx queue map dma channel. */
    uint32_t priority;                     /*!< Rx queue priority. */
    enet_qos_rx_queue_route_t packetRoute; /*!< Receive packet routing. */
} enet_qos_queue_rx_config_t;

/*! @brief Defines the configuration when multi-queue is used. */
typedef struct enet_qos_multiqueue_config
{
    enet_qos_dma_burstlen burstLen;                                  /*!< Burst len for the multi-queue. */
    uint8_t txQueueUse;                                              /*!< Used Tx queue count. */
    enet_qos_mtl_multiqueue_txsche mtltxSche;                        /*!< Transmit schedule for multi-queue. */
    enet_qos_queue_tx_config_t txQueueConfig[ENET_QOS_RING_NUM_MAX]; /*!< Tx Queue configuration. */
    uint8_t rxQueueUse;                                              /*!< Used Rx queue count. */
    enet_qos_mtl_multiqueue_rxsche mtlrxSche;                        /*!< Receive schedule for multi-queue. */
    enet_qos_queue_rx_config_t rxQueueConfig[ENET_QOS_RING_NUM_MAX]; /*!< Rx Queue configuration. */
} enet_qos_multiqueue_config_t;

/*! @brief Defines the Rx memory buffer alloc function pointer. */
typedef void *(*enet_qos_rx_alloc_callback_t)(ENET_QOS_Type *base, void *userData, uint8_t channel);

/*! @brief Defines the Rx memory buffer free function pointer. */
typedef void (*enet_qos_rx_free_callback_t)(ENET_QOS_Type *base, void *buffer, void *userData, uint8_t channel);

/*! @brief Defines the basic configuration structure for the ENET device.
 *
 *  @note Default the signal queue is used so the "*multiqueueCfg" is set default
 *  with NULL. Set the pointer with a valid configuration pointer if the multiple
 *  queues are required. If multiple queue is enabled, please make sure the
 *  buffer configuration for all are prepared also.
 */
typedef struct _enet_qos_config
{
    uint16_t specialControl;                     /*!< The logic or of enet_qos_special_config_t */
    enet_qos_multiqueue_config_t *multiqueueCfg; /*!< Use multi-queue. */
    /* -----------------MAC block-------------------------------*/
    enet_qos_mii_mode_t miiMode;     /*!< MII mode. */
    enet_qos_mii_speed_t miiSpeed;   /*!< MII Speed. */
    enet_qos_mii_duplex_t miiDuplex; /*!< MII duplex. */
    uint16_t
        pauseDuration; /*!< Used in the tx flow control frame, only valid when kENET_QOS_FlowControlEnable is set. */
                       /* -----------------Timestamp -------------------------------*/
    enet_qos_ptp_config_t *ptpConfig;         /*!< PTP 1588 feature configuration */
    uint32_t csrClock_Hz;                     /*!< CSR clock frequency in HZ. */
    enet_qos_rx_alloc_callback_t rxBuffAlloc; /*!< Callback to alloc memory, must be provided for zero-copy Rx. */
    enet_qos_rx_free_callback_t rxBuffFree;   /*!< Callback to free memory, must be provided for zero-copy Rx. */
} enet_qos_config_t;

/* Forward declaration of the handle typedef. */
typedef struct _enet_qos_handle enet_qos_handle_t;

/*! @brief ENET callback function. */
typedef void (*enet_qos_callback_t)(
    ENET_QOS_Type *base, enet_qos_handle_t *handle, enet_qos_event_t event, uint8_t channel, void *userData);

/*! @brief Defines the ENET transmit buffer descriptor ring/queue structure. */
typedef struct _enet_qos_tx_bd_ring
{
    enet_qos_tx_bd_struct_t *txBdBase; /*!< Buffer descriptor base address pointer. */
    uint16_t txGenIdx;                 /*!< tx generate index. */
    uint16_t txConsumIdx;              /*!< tx consume index. */
    volatile uint16_t txDescUsed;      /*!< tx descriptor used number. */
    uint16_t txRingLen;                /*!< tx ring length. */
} enet_qos_tx_bd_ring_t;

/*! @brief Defines the ENET receive buffer descriptor ring/queue structure. */
typedef struct _enet_qos_rx_bd_ring
{
    enet_qos_rx_bd_struct_t *rxBdBase; /*!< Buffer descriptor base address pointer. */
    uint16_t rxGenIdx;                 /*!< The current available receive buffer descriptor pointer. */
    uint16_t rxRingLen;                /*!< Receive ring length. */
    uint32_t rxBuffSizeAlign;          /*!< Receive buffer size. */
} enet_qos_rx_bd_ring_t;

/*! @brief Defines the ENET handler structure. */
struct _enet_qos_handle
{
    uint8_t txQueueUse;                                          /*!< Used tx queue count. */
    uint8_t rxQueueUse;                                          /*!< Used rx queue count. */
    bool doubleBuffEnable;                                       /*!< The double buffer is used in the descriptor. */
    bool rxintEnable;                                            /*!< Rx interrupt enabled. */
    bool rxMaintainEnable[ENET_QOS_RING_NUM_MAX];                /*!< Rx buffer cache maintain enabled. */
    enet_qos_rx_bd_ring_t rxBdRing[ENET_QOS_RING_NUM_MAX];       /*!< Receive buffer descriptor.  */
    enet_qos_tx_bd_ring_t txBdRing[ENET_QOS_RING_NUM_MAX];       /*!< Transmit buffer descriptor.  */
    enet_qos_tx_dirty_ring_t txDirtyRing[ENET_QOS_RING_NUM_MAX]; /*!< Transmit dirty buffers addresses.  */
    uint32_t *rxBufferStartAddr[ENET_QOS_RING_NUM_MAX];          /*!< Rx buffer start address for reInitialize. */
    enet_qos_callback_t callback;                                /*!< Callback function. */
    void *userData;                                              /*!< Callback function parameter.*/
    uint8_t multicastCount[64];                                  /*!< Multicast collisions counter */
    enet_qos_rx_alloc_callback_t rxBuffAlloc; /*!< Callback to alloc memory, must be provided for zero-copy Rx. */
    enet_qos_rx_free_callback_t rxBuffFree;   /*!< Callback to free memory, must be provided for zero-copy Rx. */
};

/*! @brief Defines the frame buffer structure. */
typedef struct _enet_qos_buffer_struct
{
    void *buffer;    /*!< The buffer store the whole or partial frame. */
    uint16_t length; /*!< The byte length of this buffer. */
} enet_qos_buffer_struct_t;

/*! @brief Defines the Rx frame error structure. */
typedef struct _enet_qos_rx_frame_error
{
    bool rxDstAddrFilterErr : 1; /*!< Destination Address Filter Fail. */
    bool rxSrcAddrFilterErr : 1; /*!< SA Address Filter Fail. */
    bool rxDribbleErr : 1;       /*!< Dribble error. */
    bool rxReceiveErr : 1;       /*!< Receive error. */
    bool rxOverFlowErr : 1;      /*!< Receive over flow. */
    bool rxWatchDogErr : 1;      /*!< Watch dog timeout. */
    bool rxGaintPacketErr : 1;   /*!< Receive gaint packet. */
    bool rxCrcErr : 1;           /*!< Receive CRC error. */
} enet_qos_rx_frame_error_t;

typedef struct _enet_qos_rx_frame_attribute_struct
{
    bool isTsAvail;                /*!< Rx frame timestamp is available or not. */
    enet_qos_ptp_time_t timestamp; /*!< The nanosecond part timestamp of this Rx frame. */
} enet_qos_rx_frame_attribute_t;

/*! @brief Defines the Rx frame data structure. */
typedef struct _enet_qos_rx_frame_struct
{
    enet_qos_buffer_struct_t *rxBuffArray;     /*!< Rx frame buffer structure. */
    uint16_t totLen;                           /*!< Rx frame total length. */
    enet_qos_rx_frame_attribute_t rxAttribute; /*!< Rx frame attribute structure. */
    enet_qos_rx_frame_error_t rxFrameError;    /*!< Rx frame error. */
} enet_qos_rx_frame_struct_t;

/*! @brief Defines the ENET QOS transfer statistics structure. */
typedef struct _enet_qos_transfer_stats
{
    uint32_t statsRxFrameCount;      /*!< Rx frame number. */
    uint32_t statsRxCrcErr;          /*!< Rx frame number with CRC error. */
    uint32_t statsRxAlignErr;        /*!< Rx frame number with alignment error. */
    uint32_t statsRxLengthErr;       /*!< Rx frame length field doesn't equal to packet size. */
    uint32_t statsRxFifoOverflowErr; /*!< Rx FIFO overflow count. */
    uint32_t statsTxFrameCount;      /*!< Tx frame number. */
    uint32_t statsTxFifoUnderRunErr; /*!< Tx FIFO underrun count. */
} enet_qos_transfer_stats_t;

/* Typedef for interrupt handler. */
typedef void (*enet_qos_isr_t)(ENET_QOS_Type *base, enet_qos_handle_t *handle);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to enet clocks for each instance. */
extern const clock_ip_name_t s_enetqosClock[];
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*!
 * @brief Set ENET system configuration.
 * @note User needs to provide the implementation because the implementation is SoC specific.
 *  This function set the phy selection and enable clock.
 *  It should be called before any other ethernet operation.
 *
 * @param miiMode  The MII/RGMII/RMII mode for interface between the phy and Ethernet.
 */
extern void ENET_QOS_SetSYSControl(enet_qos_mii_mode_t miiMode);

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and De-initialization
 * @{
 */

/*!
 * @brief Gets the ENET default configuration structure.
 *
 * The purpose of this API is to get the default ENET configure
 * structure for @ref ENET_QOS_Init(). User may use the initialized
 * structure unchanged in @ref ENET_QOS_Init(), or modify some fields of the
 * structure before calling @ref ENET_QOS_Init().
 * Example:
   @code
   enet_qos_config_t config;
   ENET_QOS_GetDefaultConfig(&config);
   @endcode
 * @param config The ENET mac controller configuration structure pointer.
 */
void ENET_QOS_GetDefaultConfig(enet_qos_config_t *config);

/*!
 * @brief Initializes the ENET module.
 *
 * This function initializes it with the ENET basic
 * configuration.
 *
 * @param base    ENET peripheral base address.
 * @param config  ENET mac configuration structure pointer.
 *        The "enet_qos_config_t" type mac configuration return from ENET_QOS_GetDefaultConfig
 *        can be used directly. It is also possible to verify the Mac configuration using other methods.
 * @param macAddr  Pointer to ENET mac address array of Ethernet device. This MAC address should be
 *        provided.
 * @param macCount Count of macAddr in the ENET mac address array
 * @param refclkSrc_Hz ENET input reference clock.
 */
status_t ENET_QOS_Up(
    ENET_QOS_Type *base, const enet_qos_config_t *config, uint8_t *macAddr, uint8_t macCount, uint32_t refclkSrc_Hz);

/*!
 * @brief Initializes the ENET module.
 *
 * This function ungates the module clock and initializes it with the ENET basic
 * configuration.
 *
 * @param base    ENET peripheral base address.
 * @param config  ENET mac configuration structure pointer.
 *        The "enet_qos_config_t" type mac configuration return from ENET_QOS_GetDefaultConfig
 *        can be used directly. It is also possible to verify the Mac configuration using other methods.
 * @param macAddr  Pointer to ENET mac address array of Ethernet device. This MAC address should be
 *        provided.
 * @param macCount Count of macAddr in the ENET mac address array
 * @param refclkSrc_Hz ENET input reference clock.
 */
status_t ENET_QOS_Init(
    ENET_QOS_Type *base, const enet_qos_config_t *config, uint8_t *macAddr, uint8_t macCount, uint32_t refclkSrc_Hz);

/*!
 * @brief Stops the ENET module.

 * This function disables the ENET module.
 *
 * @param base  ENET peripheral base address.
 */
void ENET_QOS_Down(ENET_QOS_Type *base);

/*!
 * @brief Deinitializes the ENET module.

 * This function gates the module clock and disables the ENET module.
 *
 * @param base  ENET peripheral base address.
 */
void ENET_QOS_Deinit(ENET_QOS_Type *base);

/*!
 * @brief Get the ENET instance from peripheral base address.
 *
 * @param base ENET peripheral base address.
 * @return ENET instance.
 */
uint32_t ENET_QOS_GetInstance(ENET_QOS_Type *base);

/*!
 * @brief Initialize for all ENET descriptors.
 *
 * @note This function is do all tx/rx descriptors initialization. Because this API
 *  read all interrupt registers first and then set the interrupt flag for all descriptors,
 * if the interrupt register is set. so the descriptor initialization should be called
 * after ENET_QOS_Init(), ENET_QOS_EnableInterrupts() and ENET_QOS_CreateHandle()(if transactional APIs
 * are used).
 *
 * @param base  ENET peripheral base address.
 * @param config The configuration for ENET.
 * @param bufferConfig All buffers configuration.
 */
status_t ENET_QOS_DescriptorInit(ENET_QOS_Type *base,
                                 enet_qos_config_t *config,
                                 enet_qos_buffer_config_t *bufferConfig);

/*!
 * @brief Allocates Rx buffers for all BDs.
 * It's used for zero copy Rx. In zero copy Rx case, Rx buffers are dynamic. This function
 * will populate initial buffers in all BDs for receiving. Then ENET_QOS_GetRxFrame() is used
 * to get Rx frame with zero copy, it will allocate new buffer to replace the buffer in BD taken
 * by application application should free those buffers after they're used.
 *
 * @note This function should be called after ENET_QOS_CreateHandler() and buffer allocating callback
 * function should be ready.
 *
 * @param base  ENET_QOS peripheral base address.
 * @param handle The ENET_QOS handler structure. This is the same handler pointer used in the ENET_QOS_Init.
 */
status_t ENET_QOS_RxBufferAllocAll(ENET_QOS_Type *base, enet_qos_handle_t *handle);

/*!
 * @brief Frees Rx buffers in all BDs.
 * It's used for zero copy Rx. In zero copy Rx case, Rx buffers are dynamic. This function
 * will free left buffers in all BDs.
 *
 * @param base  ENET_QOS peripheral base address.
 * @param handle The ENET_QOS handler structure. This is the same handler pointer used in the ENET_QOS_Init.
 */
void ENET_QOS_RxBufferFreeAll(ENET_QOS_Type *base, enet_qos_handle_t *handle);

/*!
 * @brief Starts the ENET rx/tx.
 *  This function enable the tx/rx and starts the rx/tx DMA.
 * This shall be set after ENET initialization and before
 * starting to receive the data.
 *
 * @param base  ENET peripheral base address.
 * @param rxRingNum  The number of the used rx rings. It shall not be
 * larger than the ENET_QOS_RING_NUM_MAX(2). If the ringNum is set with
 * 1, the ring 0 will be used.
 * @param txRingNum  The number of the used tx rings. It shall not be
 * larger than the ENET_QOS_RING_NUM_MAX(2). If the ringNum is set with
 * 1, the ring 0 will be used.
 *
 * @note This must be called after all the ENET initialization.
 * And should be called when the ENET receive/transmit is required.
 */
void ENET_QOS_StartRxTx(ENET_QOS_Type *base, uint8_t txRingNum, uint8_t rxRingNum);

/* @} */

/*!
 * @name MII interface operation
 * @{
 */

/*!
 * @brief Sets the ENET MII speed and duplex.
 *
 * This API is provided to dynamically change the speed and duplex for MAC.
 *
 * @param base  ENET peripheral base address.
 * @param speed The speed of the RMII mode.
 * @param duplex The duplex of the RMII mode.
 */
static inline void ENET_QOS_SetMII(ENET_QOS_Type *base, enet_qos_mii_speed_t speed, enet_qos_mii_duplex_t duplex)
{
    uint32_t reg = base->MAC_CONFIGURATION & ~(ENET_QOS_MAC_CONFIGURATION_DM_MASK | ENET_QOS_MAC_CONFIGURATION_PS_MASK |
                                               ENET_QOS_MAC_CONFIGURATION_FES_MASK);
    reg |= ENET_QOS_MAC_CONFIGURATION_DM(duplex) | (uint32_t)speed;

    base->MAC_CONFIGURATION = reg;
}

/*!
 * @brief Sets the ENET SMI(serial management interface)- MII management interface.
 *
 * @param base  ENET peripheral base address.
 * @param csrClock_Hz  CSR clock frequency in HZ
 */
void ENET_QOS_SetSMI(ENET_QOS_Type *base, uint32_t csrClock_Hz);

/*!
 * @brief Checks if the SMI is busy.
 *
 * @param base  ENET peripheral base address.
 * @return The status of MII Busy status.
 */
static inline bool ENET_QOS_IsSMIBusy(ENET_QOS_Type *base)
{
    return ((base->MAC_MDIO_ADDRESS & ENET_QOS_MAC_MDIO_ADDRESS_GB_MASK) != 0U) ? true : false;
}

/*!
 * @brief Reads data from the PHY register through SMI interface.
 *
 * @param base  ENET peripheral base address.
 * @return The data read from PHY
 */
static inline uint16_t ENET_QOS_ReadSMIData(ENET_QOS_Type *base)
{
    return (uint16_t)(base->MAC_MDIO_DATA & ENET_QOS_MAC_MDIO_DATA_GD_MASK);
}

/*!
 * @brief Starts an SMI read command.
 * It supports MDIO IEEE802.3 Clause 22.
 * After send command, user needs to check whether the transmission is over
 * with ENET_QOS_IsSMIBusy().
 *
 * @param base  ENET peripheral base address.
 * @param phyAddr The PHY address.
 * @param phyReg The PHY register.
 */
void ENET_QOS_StartSMIRead(ENET_QOS_Type *base, uint32_t phyAddr, uint32_t phyReg);

/*!
 * @brief Starts a SMI write command.
 * It supports MDIO IEEE802.3 Clause 22.
 * After send command, user needs to check whether the transmission is over
 * with ENET_QOS_IsSMIBusy().
 *
 * @param base  ENET peripheral base address.
 * @param phyAddr The PHY address.
 * @param phyReg The PHY register.
 * @param data The data written to PHY.
 */
void ENET_QOS_StartSMIWrite(ENET_QOS_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t data);

/*!
 * @brief Starts a SMI write command.
 * It supports MDIO IEEE802.3 Clause 45.
 * After send command, user needs to check whether the transmission is over
 * with ENET_QOS_IsSMIBusy().
 *
 * @param base  ENET peripheral base address.
 * @param phyAddr The PHY address.
 * @param device The PHY device type.
 * @param phyReg The PHY register address.
 * @param data The data written to PHY.
 */
void ENET_QOS_StartExtC45SMIWrite(
    ENET_QOS_Type *base, uint32_t phyAddr, uint32_t device, uint32_t phyReg, uint32_t data);

/*!
 * @brief Starts a SMI read command.
 * It supports MDIO IEEE802.3 Clause 45.
 * After send command, user needs to check whether the transmission is over
 * with ENET_QOS_IsSMIBusy().
 *
 * @param base  ENET peripheral base address.
 * @param phyAddr The PHY address.
 * @param device The PHY device type.
 * @param phyReg The PHY register address.
 */
void ENET_QOS_StartExtC45SMIRead(ENET_QOS_Type *base, uint32_t phyAddr, uint32_t device, uint32_t phyReg);
/* @} */

/*!
 * @name Other basic operation
 * @{
 */

/*!
 * @brief Sets the ENET module Mac address.
 *
 * @param base  ENET peripheral base address.
 * @param macAddr The six-byte Mac address pointer.
 *        The pointer is allocated by application and input into the API.
 * @param index Configure macAddr to MAC_ADDRESS[index] register.
 */
static inline void ENET_QOS_SetMacAddr(ENET_QOS_Type *base, uint8_t *macAddr, uint8_t index)
{
    uint32_t lowAddress;
    uint32_t highAddress;

    assert(macAddr != NULL);

    lowAddress = ((uint32_t)macAddr[3] << 24U) | ((uint32_t)macAddr[2] << 16U) | ((uint32_t)macAddr[1] << 8U) |
                 ((uint32_t)macAddr[0]);
    highAddress = ((uint32_t)macAddr[5] << 8U) | ((uint32_t)macAddr[4]);
    /* Set Macaddr, the MAC address registers are configured to be double-synchronized to the MII clock
      domains, then the synchronization is triggered only when bits 31:24 (in little-endian mode)
      or bits 7:0 (in Big-Endian mode) of the MAC address low register are written to.*/
    base->MAC_ADDRESS[index].HIGH = highAddress | ENET_QOS_HIGH_AE_MASK;
    base->MAC_ADDRESS[index].LOW  = lowAddress;
}

/*!
 * @brief Gets the ENET module Mac address.
 *
 * @param base  ENET peripheral base address.
 * @param macAddr The six-byte Mac address pointer.
 *        The pointer is allocated by application and input into the API.
 * @param index Get macAddr from MAC_ADDRESS[index] register.
 */
void ENET_QOS_GetMacAddr(ENET_QOS_Type *base, uint8_t *macAddr, uint8_t index);

/*!
 * @brief Adds the ENET_QOS device to a multicast group.
 *
 * @param base    ENET_QOS peripheral base address.
 * @param address The six-byte multicast group address which is provided by application.
 */
void ENET_QOS_AddMulticastGroup(ENET_QOS_Type *base, uint8_t *address);

/*!
 * @brief Moves the ENET_QOS device from a multicast group.
 *
 * @param base  ENET_QOS peripheral base address.
 * @param address The six-byte multicast group address which is provided by application.
 */
void ENET_QOS_LeaveMulticastGroup(ENET_QOS_Type *base, uint8_t *address);

/*!
 * @brief Enable ENET device to accept all multicast frames.
 *
 * @param base    ENET peripheral base address.
 */
static inline void ENET_QOS_AcceptAllMulticast(ENET_QOS_Type *base)
{
    uint32_t reg = base->MAC_PACKET_FILTER;

    base->MAC_PACKET_FILTER = reg | ENET_QOS_MAC_PACKET_FILTER_PM_MASK;
}

/*!
 * @brief ENET device reject to accept all multicast frames.
 *
 * @param base  ENET peripheral base address.
 */
static inline void ENET_QOS_RejectAllMulticast(ENET_QOS_Type *base)
{
    uint32_t reg = base->MAC_PACKET_FILTER;

    base->MAC_PACKET_FILTER = reg & ~ENET_QOS_MAC_PACKET_FILTER_PM_MASK;
}

/*!
 * @brief Set the MAC to enter into power down mode.
 * the remote power wake up frame and magic frame can wake up
 * the ENET from the power down mode.
 *
 * @param base    ENET peripheral base address.
 * @param wakeFilter  The wakeFilter provided to configure the wake up frame filter.
 *  Set the wakeFilter to NULL is not required. But if you have the filter requirement,
 *  please make sure the wakeFilter pointer shall be eight continuous
 *  32-bits configuration.
 */
void ENET_QOS_EnterPowerDown(ENET_QOS_Type *base, uint32_t *wakeFilter);

/*!
 * @brief Set the MAC to exit power down mode.
 * Exit from the power down mode and recover to normal work mode.
 *
 * @param base    ENET peripheral base address.
 */
static inline void ENET_QOS_ExitPowerDown(ENET_QOS_Type *base)
{
    /* Clear and status ans reset the power down. */
    base->MAC_PMT_CONTROL_STATUS &= ~ENET_QOS_MAC_PMT_CONTROL_STATUS_PWRDWN_MASK;

    /* Restore the tx which is disabled when enter power down mode. */
    base->DMA_CH[0].DMA_CHX_TX_CTRL |= ENET_QOS_DMA_CHX_TX_CTRL_ST_MASK;
    base->DMA_CH[1].DMA_CHX_TX_CTRL |= ENET_QOS_DMA_CHX_TX_CTRL_ST_MASK;
    base->MAC_CONFIGURATION |= ENET_QOS_MAC_CONFIGURATION_TE_MASK;
}

/*!
 * @brief Enable/Disable Rx parser,please notice that for enable/disable Rx Parser,
 * should better disable Receive first.
 *
 * @param base    ENET_QOS peripheral base address.
 * @param enable    Enable/Disable Rx parser function
 * @retval kStatus_Success Configure rx parser success.
 * @retval kStatus_ENET_QOS_Timeout Poll status flag timeout.
 */
status_t ENET_QOS_EnableRxParser(ENET_QOS_Type *base, bool enable);
/* @} */

/*!
 * @name Interrupts.
 * @{
 */

/*!
 * @brief Enables the ENET DMA and MAC interrupts.
 *
 * This function enables the ENET interrupt according to the provided mask. The mask
 * is a logical OR of enet_qos_dma_interrupt_enable_t and enet_qos_mac_interrupt_enable_t.
 * For example, to enable the dma and mac interrupt, do the following.
 * @code
 *     ENET_QOS_EnableInterrupts(ENET, kENET_QOS_DmaRx | kENET_QOS_DmaTx | kENET_QOS_MacPmt);
 * @endcode
 *
 * @param base  ENET peripheral base address.
 * @param mask  ENET interrupts to enable. This is a logical OR of both
 *             enumeration :: enet_qos_dma_interrupt_enable_t and enet_qos_mac_interrupt_enable_t.
 */
void ENET_QOS_EnableInterrupts(ENET_QOS_Type *base, uint32_t mask);

/*!
 * @brief Disables the ENET DMA and MAC interrupts.
 *
 * This function disables the ENET interrupt according to the provided mask. The mask
 * is a logical OR of enet_qos_dma_interrupt_enable_t and enet_qos_mac_interrupt_enable_t.
 * For example, to disable the dma and mac interrupt, do the following.
 * @code
 *     ENET_QOS_DisableInterrupts(ENET, kENET_QOS_DmaRx | kENET_QOS_DmaTx | kENET_QOS_MacPmt);
 * @endcode
 *
 * @param base  ENET peripheral base address.
 * @param mask  ENET interrupts to disables. This is a logical OR of both
 *             enumeration :: enet_qos_dma_interrupt_enable_t and enet_qos_mac_interrupt_enable_t.
 */
void ENET_QOS_DisableInterrupts(ENET_QOS_Type *base, uint32_t mask);

/*!
 * @brief Gets the ENET DMA interrupt status flag.
 *
 * @param base  ENET peripheral base address.
 * @param channel The DMA Channel. Shall not be larger than ENET_QOS_RING_NUM_MAX.
 * @return The event status of the interrupt source. This is the logical OR of members
 *         of the enumeration :: enet_qos_dma_interrupt_enable_t.
 */
static inline uint32_t ENET_QOS_GetDmaInterruptStatus(ENET_QOS_Type *base, uint8_t channel)
{
    return base->DMA_CH[channel].DMA_CHX_STAT;
}

/*!
 * @brief Clear the ENET DMA interrupt status flag.
 *
 * @param base  ENET peripheral base address.
 * @param channel The DMA Channel. Shall not be larger than ENET_QOS_RING_NUM_MAX.
 * @param mask The interrupt status to be cleared. This is the logical OR of members
 *         of the enumeration :: enet_qos_dma_interrupt_enable_t.
 */
static inline void ENET_QOS_ClearDmaInterruptStatus(ENET_QOS_Type *base, uint8_t channel, uint32_t mask)
{
    /* Clear the dam interrupt status bit in dma channel interrupt status register. */
    base->DMA_CH[channel].DMA_CHX_STAT = mask;
}

/*!
 * @brief Gets the ENET MAC interrupt status flag.
 *
 * @param base  ENET peripheral base address.
 * @return The event status of the interrupt source.
 *       Use the enum in enet_qos_mac_interrupt_enable_t and right shift
 *       ENET_QOS_MACINT_ENUM_OFFSET to mask the returned value to get the
 *       exact interrupt status.
 */
static inline uint32_t ENET_QOS_GetMacInterruptStatus(ENET_QOS_Type *base)
{
    return base->MAC_INTERRUPT_STATUS;
}

/*!
 * @brief Clears the ENET mac interrupt events status flag.
 *
 * This function clears enabled ENET interrupts according to the provided mask. The mask
 * is a logical OR of enumeration members. See the @ref enet_qos_mac_interrupt_enable_t.
 * For example, to clear the TX frame interrupt and RX frame interrupt, do the following.
 * @code
 *     ENET_QOS_ClearMacInterruptStatus(ENET, kENET_QOS_MacPmt);
 * @endcode
 *
 * @param base  ENET peripheral base address.
 * @param mask  ENET interrupt source to be cleared.
 * This is the logical OR of members of the enumeration :: enet_qos_mac_interrupt_enable_t.
 */
void ENET_QOS_ClearMacInterruptStatus(ENET_QOS_Type *base, uint32_t mask);

/* @} */

/*!
 * @name Functional operation.
 * @{
 */

/*!
 * @brief Get the tx descriptor DMA Own flag.
 *
 * @param txDesc  The given tx descriptor.
 * @retval True the dma own tx descriptor, false application own tx descriptor.
 *
 */
static inline bool ENET_QOS_IsTxDescriptorDmaOwn(enet_qos_tx_bd_struct_t *txDesc)
{
    return ((txDesc->controlStat & ENET_QOS_TXDESCRIP_RD_OWN_MASK) != 0U) ? true : false;
}

/*!
 * @brief Setup a given tx descriptor.
 *  This function is a low level functional API to setup or prepare
 *  a given tx descriptor.
 *
 * @param txDesc  The given tx descriptor.
 * @param buffer1  The first buffer address in the descriptor.
 * @param bytes1  The bytes in the fist buffer.
 * @param buffer2  The second buffer address in the descriptor.
 * @param bytes2  The bytes in the second buffer.
 * @param framelen  The length of the frame to be transmitted.
 * @param intEnable Interrupt enable flag.
 * @param tsEnable The timestamp enable.
 * @param flag The flag of this tx descriptor, @ref enet_qos_desc_flag .
 * @param slotNum The slot num used for AV  only.
 *
 * @note This must be called after all the ENET initialization.
 * And should be called when the ENET receive/transmit is required.
 * Transmit buffers are 'zero-copy' buffers, so the buffer must remain in
 * memory until the packet has been fully transmitted. The buffers
 * should be free or requeued in the transmit interrupt irq handler.
 */
void ENET_QOS_SetupTxDescriptor(enet_qos_tx_bd_struct_t *txDesc,
                                void *buffer1,
                                uint32_t bytes1,
                                void *buffer2,
                                uint32_t bytes2,
                                uint32_t framelen,
                                bool intEnable,
                                bool tsEnable,
                                enet_qos_desc_flag flag,
                                uint8_t slotNum);

/*!
 * @brief Update the tx descriptor tail pointer.
 *  This function is a low level functional API to update the
 *  the tx descriptor tail.
 *  This is called after you setup a new tx descriptor to update
 *  the tail pointer to make the new descriptor accessible by DMA.
 *
 * @param base    ENET peripheral base address.
 * @param channel  The tx DMA channel.
 * @param txDescTailAddrAlign  The new tx tail pointer address.
 *
 */
static inline void ENET_QOS_UpdateTxDescriptorTail(ENET_QOS_Type *base, uint8_t channel, uint32_t txDescTailAddrAlign)
{
    base->DMA_CH[channel].DMA_CHX_TXDESC_TAIL_PTR = txDescTailAddrAlign & ~ENET_QOS_ADDR_ALIGNMENT;
}

/*!
 * @brief Update the rx descriptor tail pointer.
 *  This function is a low level functional API to update the
 *  the rx descriptor tail.
 *  This is called after you setup a new rx descriptor to update
 *  the tail pointer to make the new descriptor accessible by DMA
 *  and to anouse the rx poll command for DMA.
 *
 * @param base    ENET peripheral base address.
 * @param channel  The rx DMA channel.
 * @param rxDescTailAddrAlign  The new rx tail pointer address.
 *
 */
static inline void ENET_QOS_UpdateRxDescriptorTail(ENET_QOS_Type *base, uint8_t channel, uint32_t rxDescTailAddrAlign)
{
    base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR = rxDescTailAddrAlign & ~ENET_QOS_ADDR_ALIGNMENT;
}

/*!
 * @brief Gets the context in the ENET rx descriptor.
 *  This function is a low level functional API to get the
 *  the status flag from a given rx descriptor.
 *
 * @param rxDesc  The given rx descriptor.
 * @retval The RDES3 regions for write-back format rx buffer descriptor.
 *
 * @note This must be called after all the ENET initialization.
 * And should be called when the ENET receive/transmit is required.
 */
static inline uint32_t ENET_QOS_GetRxDescriptor(enet_qos_rx_bd_struct_t *rxDesc)
{
    assert(rxDesc != NULL);

    return rxDesc->control;
}
/*!
 * @brief Updates the buffers and the own status for a given rx descriptor.
 *  This function is a low level functional API to Updates the
 *  buffers and the own status for a given rx descriptor.
 *
 * @param rxDesc  The given rx descriptor.
 * @param buffer1  The first buffer address in the descriptor.
 * @param buffer2  The second buffer address in the descriptor.
 * @param intEnable Interrupt enable flag.
 * @param doubleBuffEnable The double buffer enable flag.
 *
 * @note This must be called after all the ENET initialization.
 * And should be called when the ENET receive/transmit is required.
 */
void ENET_QOS_UpdateRxDescriptor(
    enet_qos_rx_bd_struct_t *rxDesc, void *buffer1, void *buffer2, bool intEnable, bool doubleBuffEnable);

/*!
 * @brief Configure flexible rx parser.
 *
 * This function is used to configure the flexible rx parser table.
 *
 * @param base  ENET peripheral base address..
 * @param rxpConfig The rx parser configuration pointer.
 * @param entryCount The rx parser entry count.
 * @retval kStatus_Success Configure rx parser success.
 * @retval kStatus_ENET_QOS_Timeout Poll status flag timeout.
 */
status_t ENET_QOS_ConfigureRxParser(ENET_QOS_Type *base, enet_qos_rxp_config_t *rxpConfig, uint16_t entryCount);

/*!
 * @brief Read flexible rx parser configuration at specified index.
 *
 * This function is used to read flexible rx parser configuration at specified index.
 *
 * @param base  ENET peripheral base address..
 * @param rxpConfig The rx parser configuration pointer.
 * @param entryIndex The rx parser entry index to read, start from 0.
 * @retval kStatus_Success Configure rx parser success.
 * @retval kStatus_ENET_QOS_Timeout Poll status flag timeout.
 */
status_t ENET_QOS_ReadRxParser(ENET_QOS_Type *base, enet_qos_rxp_config_t *rxpConfig, uint16_t entryIndex);

/*!
 * @brief Program Gate Control List.
 *
 * This function is used to program the Enhanced Scheduled Transmisson. (IEEE802.1Qbv)
 *
 * @param base  ENET peripheral base address..
 * @param gcl Pointer to the Gate Control List structure.
 * @param ptpClk_Hz frequency of the PTP clock.
 */
status_t ENET_QOS_EstProgramGcl(ENET_QOS_Type *base, enet_qos_est_gcl_t *gcl, uint32_t ptpClk_Hz);

/*!
 * @brief Read Gate Control List.
 *
 * This function is used to read the Enhanced Scheduled Transmisson list. (IEEE802.1Qbv)
 *
 * @param base  ENET peripheral base address..
 * @param gcl Pointer to the Gate Control List structure.
 * @param listLen length of the provided opList array in gcl structure.
 * @param hwList Boolean if True read HW list, false read SW list.
 */
status_t ENET_QOS_EstReadGcl(ENET_QOS_Type *base, enet_qos_est_gcl_t *gcl, uint32_t listLen, bool hwList);

/*!
 * @brief Enable Frame Preemption.
 *
 * This function is used to enable frame preemption. (IEEE802.1Qbu)
 *
 * @param base  ENET peripheral base address..
 */
static inline void ENET_QOS_FpeEnable(ENET_QOS_Type *base)
{
    base->MAC_FPE_CTRL_STS |= ENET_QOS_MAC_FPE_CTRL_STS_EFPE_MASK;
}

/*!
 * @brief Disable Frame Preemption.
 *
 * This function is used to disable frame preemption. (IEEE802.1Qbu)
 *
 * @param base  ENET peripheral base address..
 */
static inline void ENET_QOS_FpeDisable(ENET_QOS_Type *base)
{
    base->MAC_FPE_CTRL_STS &= ~ENET_QOS_MAC_FPE_CTRL_STS_EFPE_MASK;
}

/*!
 * @brief Configure preemptable transmit queues.
 *
 * This function is used to configure the preemptable queues. (IEEE802.1Qbu)
 *
 * @param base  ENET peripheral base address..
 * @param queueMask  bitmask representing queues to set in preemptable mode.
 *                   The N-th bit represents the queue N.
 */
static inline void ENET_QOS_FpeConfigPreemptable(ENET_QOS_Type *base, uint8_t queueMask)
{
    uint32_t control;

    control = base->MTL_FPE_CTRL_STS & ~ENET_QOS_MTL_FPE_CTRL_STS_PEC_MASK;
    control |= ENET_QOS_MTL_FPE_CTRL_STS_PEC(queueMask);
    base->MTL_FPE_CTRL_STS = control;
}

/*!
 * @brief Sets the ENET AVB feature.
 *
 * ENET_QOS AVB feature configuration, set transmit bandwidth.
 * This API is called when the AVB feature is required.
 *
 * @param base ENET_QOS peripheral base address.
 * @param config The ENET_QOS AVB feature configuration structure.
 * @param queueIndex ENET_QOS queue index.
 */
void ENET_QOS_AVBConfigure(ENET_QOS_Type *base, const enet_qos_cbs_config_t *config, uint8_t queueIndex);

/*!
 * @brief Gets statistical data in transfer.
 *
 * @param base  ENET_QOS peripheral base address.
 * @param statistics The statistics structure pointer.
 */
void ENET_QOS_GetStatistics(ENET_QOS_Type *base, enet_qos_transfer_stats_t *statistics);

/* @} */

/*!
 * @name Transactional operation
 * @{
 */

/*!
 * @brief Create ENET Handler
 *
 * This is a transactional API and it's provided to store all data which are needed
 * during the whole transactional process. This API should not be used when you use
 * functional APIs to do data tx/rx. This is function will store many data/flag for
 * transactional use, so all configure API such as ENET_QOS_Init(), ENET_QOS_DescriptorInit(),
 * ENET_QOS_EnableInterrupts() etc.
 *
 * @note as our transactional transmit API use the zero-copy transmit buffer.
 * so there are two thing we emphasize here:
 *  1. tx buffer free/requeue for application should be done in the tx
 *  interrupt handler. Please set callback: kENET_QOS_TxIntEvent with tx buffer free/requeue
 *  process APIs.
 *  2. the tx interrupt is forced to open.
 *
 * @param base  ENET peripheral base address.
 * @param handle ENET handler.
 * @param config ENET configuration.
 * @param bufferConfig ENET buffer configuration.
 * @param callback The callback function.
 * @param userData The application data.
 */
void ENET_QOS_CreateHandler(ENET_QOS_Type *base,
                            enet_qos_handle_t *handle,
                            enet_qos_config_t *config,
                            enet_qos_buffer_config_t *bufferConfig,
                            enet_qos_callback_t callback,
                            void *userData);

/*!
 * @brief Gets the size of the read frame.
 * This function gets a received frame size from the ENET buffer descriptors.
 * @note The FCS of the frame is automatically removed by MAC and the size is the length without the FCS.
 * After calling @ref ENET_QOS_GetRxFrameSize, @ref ENET_QOS_ReadFrame() should be called to update the
 * receive buffers If the result is not "kStatus_ENET_QOS_RxFrameEmpty".
 *
 * @param base  ENET peripheral base address.
 * @param handle The ENET handler structure. This is the same handler pointer used in the ENET_QOS_Init.
 * @param length The length of the valid frame received.
 * @param channel The DMAC channel for the rx.
 * @retval kStatus_ENET_QOS_RxFrameEmpty No frame received. Should not call ENET_QOS_ReadFrame to read frame.
 * @retval kStatus_ENET_QOS_RxFrameError Data error happens. @ref ENET_QOS_ReadFrame should be called with NULL data
 *         and NULL length to update the receive buffers.
 * @retval kStatus_Success Receive a frame Successfully then the @ref ENET_QOS_ReadFrame
 *         should be called with the right data buffer and the captured data length input.
 */
status_t ENET_QOS_GetRxFrameSize(ENET_QOS_Type *base, enet_qos_handle_t *handle, uint32_t *length, uint8_t channel);

/*!
 * @brief Reads a frame from the ENET device.
 * This function reads a frame from the ENET DMA descriptors.
 * The ENET_QOS_GetRxFrameSize should be used to get the size of the prepared data buffer.
 * For example use rx dma channel 0:
 * @code
 *       uint32_t length;
 *       enet_qos_handle_t g_handle;
 *       status = ENET_QOS_GetRxFrameSize(&g_handle, &length, 0);
 *       if (length != 0)
 *       {
 *           uint8_t *data = memory allocate interface;
 *           if (!data)
 *           {
 *               ENET_QOS_ReadFrame(ENET, &g_handle, NULL, 0, 0);
 *           }
 *           else
 *           {
 *              status = ENET_QOS_ReadFrame(ENET, &g_handle, data, length, 0);
 *           }
 *       }
 *       else if (status == kStatus_ENET_QOS_RxFrameError)
 *       {
 *           ENET_QOS_ReadFrame(ENET, &g_handle, NULL, 0, 0);
 *       }
 * @endcode
 * @param base  ENET peripheral base address.
 * @param handle The ENET handler structure. This is the same handler pointer used in the ENET_QOS_Init.
 * @param data The data buffer provided by user to store the frame which memory size should be at least "length".
 * @param length The size of the data buffer which is still the length of the received frame.
 * @param channel The rx DMA channel. shall not be larger than 2.
 * @param ts     Pointer to the structure @ref enet_qos_ptp_time_t to save frame timestamp.
 * @return The execute status, successful or failure.
 */
status_t ENET_QOS_ReadFrame(ENET_QOS_Type *base,
                            enet_qos_handle_t *handle,
                            uint8_t *data,
                            uint32_t length,
                            uint8_t channel,
                            enet_qos_ptp_time_t *ts);

/*!
 * @brief Transmits an ENET frame.
 * @note The CRC is automatically appended to the data. Input the data
 * to send without the CRC.
 *
 * @param base  ENET peripheral base address.
 * @param handle The ENET handler pointer. This is the same handler pointer used in the ENET_QOS_Init.
 * @param data The data buffer provided by user to be send.
 * @param length The length of the data to be send.
 * @param channel Channel to send the frame, same with queue index.
 * @param isNeedTs True to enable timestamp save for the frame
 * @param context pointer to user context to be kept in the tx dirty frame information.
 * @retval kStatus_Success  Send frame succeed.
 * @retval kStatus_ENET_QOS_TxFrameBusy  Transmit buffer descriptor is busy under transmission.
 *         The transmit busy happens when the data send rate is over the MAC capacity.
 *         The waiting mechanism is recommended to be added after each call return with
 *         kStatus_ENET_QOS_TxFrameBusy.
 */
status_t ENET_QOS_SendFrame(ENET_QOS_Type *base,
                            enet_qos_handle_t *handle,
                            uint8_t *data,
                            uint32_t length,
                            uint8_t channel,
                            bool isNeedTs,
                            void *context);

/*!
 * @brief Reclaim tx descriptors.
 *  This function is used to update the tx descriptor status and
 *  store the tx timestamp when the 1588 feature is enabled.
 *  This is called by the transmit interrupt IRQ handler after the
 *  complete of a frame transmission.
 *
 * @param base    ENET peripheral base address.
 * @param handle The ENET handler pointer. This is the same handler pointer used in the ENET_QOS_Init.
 * @param channel  The tx DMA channel.
 *
 */
void ENET_QOS_ReclaimTxDescriptor(ENET_QOS_Type *base, enet_qos_handle_t *handle, uint8_t channel);

/*!
 * @brief The ENET IRQ handler.
 *
 * @param base  ENET peripheral base address.
 * @param handle The ENET handler pointer.
 */
void ENET_QOS_CommonIRQHandler(ENET_QOS_Type *base, enet_qos_handle_t *handle);

/*!
 * @brief Set the second level IRQ handler, allow user to overwrite the default
 * second level weak IRQ handler.
 *
 * @param base  ENET peripheral base address.
 * @param ISRHandler  The handler to install.
 */
void ENET_QOS_SetISRHandler(ENET_QOS_Type *base, enet_qos_isr_t ISRHandler);

/* @} */
/*!
 * @name ENET Enhanced function operation
 * @{
 */

/*!
 * @brief Correct the ENET PTP 1588 timer in coarse method.
 *
 * @param base  ENET peripheral base address.
 * @param operation The system time operation, refer to "enet_qos_systime_op"
 * @param second The correction second.
 * @param nanosecond The correction nanosecond.
 */
status_t ENET_QOS_Ptp1588CorrectTimerInCoarse(ENET_QOS_Type *base,
                                              enet_qos_systime_op operation,
                                              uint32_t second,
                                              uint32_t nanosecond);

/*!
 * @brief Correct the ENET PTP 1588 timer in fine method.
 *
 *
 * @param base  ENET peripheral base address.
 * @param addend The addend value to be set in the fine method
 * @note Should take refer to the chapter "System time correction" and
 * see the description for the "fine correction method".
 */
status_t ENET_QOS_Ptp1588CorrectTimerInFine(ENET_QOS_Type *base, uint32_t addend);

/*!
 * @brief Get the ENET Time stamp current addend value.
 *
 * @param base  ENET peripheral base address.
 * @return The addend value.
 */
static inline uint32_t ENET_QOS_Ptp1588GetAddend(ENET_QOS_Type *base)
{
    return base->MAC_TIMESTAMP_ADDEND;
}

/*!
 * @brief Gets the current ENET time from the PTP 1588 timer without IRQ disable.
 *
 * @param base  ENET peripheral base address.
 * @param second The PTP 1588 system timer second.
 * @param nanosecond The PTP 1588 system timer nanosecond.
 * For the unit of the nanosecond is 1ns. so the nanosecond is the real nanosecond.
 */
void ENET_QOS_Ptp1588GetTimerNoIRQDisable(ENET_QOS_Type *base, uint64_t *second, uint32_t *nanosecond);

/*!
 * @brief Sets the ENET PTP 1588 PPS control.
 * All channels operate in flexible PPS output mode.
 *
 * @param base  ENET peripheral base address.
 * @param instance The ENET QOS PTP PPS instance.
 * @param trgtMode The target time register mode.
 * @param cmd The target flexible PPS output control command.
 */
static inline status_t ENET_Ptp1588PpsControl(ENET_QOS_Type *base,
                                              enet_qos_ptp_pps_instance_t instance,
                                              enet_qos_ptp_pps_trgt_mode_t trgtMode,
                                              enet_qos_ptp_pps_cmd_t cmd)
{
    uint32_t reg        = 0UL;
    uint8_t shift       = (uint8_t)instance * 8U;
    uint32_t pps_config = ENET_QOS_MAC_PPS_CONTROL_TRGTMODSEL0((uint32_t)trgtMode) |
                          ENET_QOS_MAC_PPS_CONTROL_PPSCTRL_PPSCMD((uint32_t)cmd);

    reg = base->MAC_PPS_CONTROL;

    /* Make sure CMD field is all zero */
    if ((reg & (0xFUL << shift)) != 0UL)
    {
        return kStatus_ENET_QOS_PpsBusy;
    }

    reg &= ~(0xFFUL << shift);
    reg |= (pps_config << shift) | ENET_QOS_MAC_PPS_CONTROL_PPSEN0(1U);

    base->MAC_PPS_CONTROL = reg;

    return kStatus_Success;
}

/*!
 * @brief Sets the ENET OQS PTP 1588 PPS target time registers.
 *
 * @param base  ENET QOS peripheral base address.
 * @param instance The ENET QOS PTP PPS instance.
 * @param seconds The target seconds.
 * @param nanoseconds The target nanoseconds.
 */
status_t ENET_QOS_Ptp1588PpsSetTrgtTime(ENET_QOS_Type *base,
                                        enet_qos_ptp_pps_instance_t instance,
                                        uint32_t seconds,
                                        uint32_t nanoseconds);

/*!
 * @brief Sets the ENET OQS PTP 1588 PPS output signal interval
 *
 * @param base  ENET QOS peripheral base address.
 * @param instance The ENET QOS PTP PPS instance.
 * @param width Signal Width. It is stored in terms of number of
 * units of sub-second increment value. The width value must be
 * lesser than interval value.
 */
static inline void ENET_QOS_Ptp1588PpsSetWidth(ENET_QOS_Type *base,
                                               enet_qos_ptp_pps_instance_t instance,
                                               uint32_t width)
{
    uint32_t *mac_pps_width;

    mac_pps_width = (uint32_t *)((uintptr_t)&base->MAC_PPS0_WIDTH + 0x10U * (uint32_t)instance);

    *mac_pps_width = ENET_QOS_MAC_PPS0_WIDTH_PPSWIDTH0(width);
}

/*!
 * @brief Sets the ENET OQS PTP 1588 PPS output signal width
 *
 * @param base  ENET QOS peripheral base address.
 * @param instance The ENET QOS PTP PPS instance.
 * @param interval Signal Interval. It is stored in terms of number of
 * units of sub-second increment value.
 */
static inline void ENET_QOS_Ptp1588PpsSetInterval(ENET_QOS_Type *base,
                                                  enet_qos_ptp_pps_instance_t instance,
                                                  uint32_t interval)
{
    uint32_t *mac_pps_interval;

    mac_pps_interval = (uint32_t *)((uintptr_t)&base->MAC_PPS0_INTERVAL + 0x10U * (uint32_t)instance);

    *mac_pps_interval = ENET_QOS_MAC_PPS0_INTERVAL_PPSINT0(interval);
}

/*!
 * @brief Gets the current ENET time from the PTP 1588 timer.
 *
 * @param base  ENET peripheral base address.
 * @param second The PTP 1588 system timer second.
 * @param nanosecond The PTP 1588 system timer nanosecond.
 * For the unit of the nanosecond is 1ns.so the nanosecond is the real nanosecond.
 */
void ENET_QOS_Ptp1588GetTimer(ENET_QOS_Type *base, uint64_t *second, uint32_t *nanosecond);

/*!
 * @brief Gets the time stamp of the transmit frame.
 *
 * This function is used for PTP stack to get the timestamp captured by the ENET driver.
 *
 * @param handle The ENET handler pointer.This is the same state pointer used in
 *        ENET_QOS_Init.
 * @param txFrame Input parameter, pointer to @ref enet_qos_frame_info_t for saving read out frame information.
 * @param channel Channel for searching the tx frame.
 */
void ENET_QOS_GetTxFrame(enet_qos_handle_t *handle, enet_qos_frame_info_t *txFrame, uint8_t channel);

/*!
 * @brief Receives one frame in specified BD ring with zero copy.
 *
 * This function will use the user-defined allocate and free callback. Every time application gets one frame through
 * this function, driver will allocate new buffers for the BDs whose buffers have been taken by application.
 * @note This function will drop current frame and update related BDs as available for DMA if new buffers allocating
 * fails. Application must provide a memory pool including at least BD number + 1 buffers(+2 if enable double buffer)
 * to make this function work normally. If user calls this function in Rx interrupt handler, be careful that this
 * function makes Rx BD ready with allocating new buffer(normal) or updating current BD(out of memory). If there's
 * always new Rx frame input, Rx interrupt will be triggered forever. Application need to disable Rx interrupt according
 * to specific design in this case.
 *
 * @param base   ENET peripheral base address.
 * @param handle The ENET handler pointer. This is the same handler pointer used in the ENET_Init.
 * @param rxFrame The received frame information structure provided by user.
 * @param channel Channel for searching the rx frame.
 * @retval kStatus_Success  Succeed to get one frame and allocate new memory for Rx buffer.
 * @retval kStatus_ENET_QOS_RxFrameEmpty  There's no Rx frame in the BD.
 * @retval kStatus_ENET_QOS_RxFrameError  There's issue in this receiving.
 * @retval kStatus_ENET_QOS_RxFrameDrop  There's no new buffer memory for BD, drop this frame.
 */
status_t ENET_QOS_GetRxFrame(ENET_QOS_Type *base,
                             enet_qos_handle_t *handle,
                             enet_qos_rx_frame_struct_t *rxFrame,
                             uint8_t channel);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_ENET_QOS_H_ */
