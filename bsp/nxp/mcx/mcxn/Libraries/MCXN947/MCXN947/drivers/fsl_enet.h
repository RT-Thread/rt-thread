/*
 * Copyright 2022-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_ENET_H_
#define FSL_ENET_H_

#include "fsl_common.h"

/*!
 * @addtogroup Mcx_enet
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Defines the driver version. */
#define FSL_ENET_DRIVER_VERSION (MAKE_VERSION(2, 1, 3))
/*@}*/

/*! @name Control and status region bit masks of the receive buffer descriptor. */
/*@{*/
/*! @brief Defines for read format. */
#define ENET_RXDESCRIP_RD_BUFF1VALID_MASK (1UL << 24) /*!< Buffer1 address valid. */
#define ENET_RXDESCRIP_RD_BUFF2VALID_MASK (1UL << 25) /*!< Buffer2 address valid. */
#define ENET_RXDESCRIP_RD_IOC_MASK        (1UL << 30) /*!< Interrupt enable on complete. */
#define ENET_RXDESCRIP_RD_OWN_MASK        (1UL << 31) /*!< Own bit. */

/*! @brief Defines for write back format. */
#define ENET_RXDESCRIP_WR_ERR_MASK        ((1UL << 3) | (1UL << 7))
#define ENET_RXDESCRIP_WR_PYLOAD_MASK     (0x7U)
#define ENET_RXDESCRIP_WR_PTPMSGTYPE_MASK (0xF00U)
#define ENET_RXDESCRIP_WR_PTPTYPE_MASK    (1UL << 12)
#define ENET_RXDESCRIP_WR_PTPVERSION_MASK (1UL << 13)
#define ENET_RXDESCRIP_WR_PTPTSA_MASK     (1UL << 14)
#define ENET_RXDESCRIP_WR_PACKETLEN_MASK  (0x7FFFU)
#define ENET_RXDESCRIP_WR_ERRSUM_MASK     (1UL << 15)
#define ENET_RXDESCRIP_WR_TYPE_MASK       (0x30000U)
#define ENET_RXDESCRIP_WR_DE_MASK         (1UL << 19)
#define ENET_RXDESCRIP_WR_RE_MASK         (1UL << 20)
#define ENET_RXDESCRIP_WR_OE_MASK         (1UL << 21)
#define ENET_RXDESCRIP_WR_RS0V_MASK       (1UL << 25)
#define ENET_RXDESCRIP_WR_RS1V_MASK       (1UL << 26)
#define ENET_RXDESCRIP_WR_RS2V_MASK       (1UL << 27)
#define ENET_RXDESCRIP_WR_LD_MASK         (1UL << 28)
#define ENET_RXDESCRIP_WR_FD_MASK         (1UL << 29)
#define ENET_RXDESCRIP_WR_CTXT_MASK       (1UL << 30)
#define ENET_RXDESCRIP_WR_OWN_MASK        (1UL << 31)
/*@}*/

/*! @name Control and status bit masks of the transmit buffer descriptor. */
/*@{*/
/*! @brief Defines for read format. */
#define ENET_TXDESCRIP_RD_BL1_MASK  (0x3fffU)
#define ENET_TXDESCRIP_RD_BL2_MASK  (ENET_TXDESCRIP_RD_BL1_MASK << 16)
#define ENET_TXDESCRIP_RD_BL1(n)    ((uint32_t)(n) & ENET_TXDESCRIP_RD_BL1_MASK)
#define ENET_TXDESCRIP_RD_BL2(n)    (((uint32_t)(n) & ENET_TXDESCRIP_RD_BL1_MASK) << 16)
#define ENET_TXDESCRIP_RD_TTSE_MASK (1UL << 30)
#define ENET_TXDESCRIP_RD_IOC_MASK  (1UL << 31)

#define ENET_TXDESCRIP_RD_FL_MASK   (0x7FFFU)
#define ENET_TXDESCRIP_RD_FL(n)     ((uint32_t)(n) & ENET_TXDESCRIP_RD_FL_MASK)
#define ENET_TXDESCRIP_RD_CIC(n)    (((uint32_t)(n) & 0x3U) << 16)
#define ENET_TXDESCRIP_RD_TSE_MASK  (1UL << 18)
#define ENET_TXDESCRIP_RD_SLOT(n)   (((uint32_t)(n) & 0x0fU) << 19)
#define ENET_TXDESCRIP_RD_SAIC(n)   (((uint32_t)(n) & 0x07U) << 23)
#define ENET_TXDESCRIP_RD_CPC(n)    (((uint32_t)(n) & 0x03U) << 26)
#define ENET_TXDESCRIP_RD_LDFD(n)   (((uint32_t)(n) & 0x03U) << 28)
#define ENET_TXDESCRIP_RD_LD_MASK   (1UL << 28)
#define ENET_TXDESCRIP_RD_FD_MASK   (1UL << 29)
#define ENET_TXDESCRIP_RD_CTXT_MASK (1UL << 30)
#define ENET_TXDESCRIP_RD_OWN_MASK  (1UL << 31)

/*! @brief Defines for write back format. */
#define ENET_TXDESCRIP_WB_TTSS_MASK (1UL << 17)
/*@}*/

/*! @name Bit mask for interrupt enable type. */
/*@{*/
#define ENET_ABNORM_INT_MASK                                                       \
    (ENET_DMA_CH_DMA_CHX_INT_EN_TXSE_MASK | ENET_DMA_CH_DMA_CHX_INT_EN_RBUE_MASK | \
     ENET_DMA_CH_DMA_CHX_INT_EN_RSE_MASK | ENET_DMA_CH_DMA_CHX_INT_EN_RWTE_MASK |  \
     ENET_DMA_CH_DMA_CHX_INT_EN_FBEE_MASK | ENET_DMA_CH_DMA_CHX_INT_EN_ETIE_MASK)
#define ENET_NORM_INT_MASK                                                        \
    (ENET_DMA_CH_DMA_CHX_INT_EN_TIE_MASK | ENET_DMA_CH_DMA_CHX_INT_EN_TBUE_MASK | \
     ENET_DMA_CH_DMA_CHX_INT_EN_RIE_MASK | ENET_DMA_CH_DMA_CHX_INT_EN_ERIE_MASK)
/*@}*/

/*! @name Defines some Ethernet parameters. */
/*@{*/
#define ENET_FRAME_MAX_FRAMELEN      (1518U) /*!< Default maximum ethernet frame size. */
#define ENET_FCS_LEN                 (4U)    /*!< Ethernet Rx frame FCS length. */
#define ENET_ADDR_ALIGNMENT          (0x3U)  /*!< Recommended ethernet buffer alignment. */
#define ENET_BUFF_ALIGNMENT          (4U)    /*!< Receive buffer alignment shall be 4bytes-aligned. */
#define ENET_RING_NUM_MAX            (2U)    /*!< The maximum number of Tx/Rx descriptor rings. */
#define ENET_MTL_RXFIFOSIZE          (2048U) /*!< The Rx fifo size. */
#define ENET_MTL_TXFIFOSIZE          (2048U) /*!< The Tx fifo size. */
#define ENET_MACINT_ENUM_OFFSET      (16U)   /*!< The offset for mac interrupt in enum type. */
#define ENET_FRAME_TX_LEN_LIMITATION (ENET_TXDESCRIP_RD_BL1_MASK) /*!< The Tx frame length software limitation. */
#define ENET_FRAME_RX_ERROR_BITS(x)  (((x) >> 19U) & 0x3FU)       /*!< The Rx frame error bits field. */
/*@}*/

/*! @brief Defines the status return codes for transaction. */
enum
{
    kStatus_ENET_InitMemoryFail =
        MAKE_STATUS(kStatusGroup_ENET, 0U), /*!< Status code 4000. Init failed since buffer memory was not enough. */
    kStatus_ENET_RxFrameError =
        MAKE_STATUS(kStatusGroup_ENET, 1U), /*!< Status code 4001. A frame received but data error occurred. */
    kStatus_ENET_RxFrameFail  = MAKE_STATUS(kStatusGroup_ENET, 2U), /*!< Status code 4002. Failed to receive a frame. */
    kStatus_ENET_RxFrameEmpty = MAKE_STATUS(kStatusGroup_ENET, 3U), /*!< Status code 4003. No frame arrived. */
    kStatus_ENET_RxFrameDrop  = MAKE_STATUS(
        kStatusGroup_ENET, 4U), /*!< Status code 4004. Rx frame was dropped since there's no buffer memory. */
    kStatus_ENET_TxFrameBusy =
        MAKE_STATUS(kStatusGroup_ENET, 5U), /*!< Status code 4005. There were no resources for Tx operation. */
    kStatus_ENET_TxFrameFail = MAKE_STATUS(kStatusGroup_ENET, 6U), /*!< Status code 4006. Transmit frame failed. */
    kStatus_ENET_TxFrameOverLen =
        MAKE_STATUS(kStatusGroup_ENET, 7U) /*!< Status code 4007. Failed to send an oversize frame. */
};

/*! @brief Defines the MII/RMII mode for data interface between the MAC and the PHY. */
typedef enum _enet_mii_mode
{
    kENET_MiiMode  = 0U, /*!< MII mode for data interface. */
    kENET_RmiiMode = 1U  /*!< RMII mode for data interface. */
} enet_mii_mode_t;

/*! @brief Defines the 10/100 Mbps speed for the MII data interface. */
typedef enum _enet_mii_speed
{
    kENET_MiiSpeed10M  = 0U, /*!< Speed 10 Mbps. */
    kENET_MiiSpeed100M = 1U, /*!< Speed 100 Mbps. */
} enet_mii_speed_t;

/*! @brief Defines the half or full duplex for the MII data interface. */
typedef enum _enet_mii_duplex
{
    kENET_MiiHalfDuplex = 0U, /*!< Half duplex mode. */
    kENET_MiiFullDuplex       /*!< Full duplex mode. */
} enet_mii_duplex_t;

/*! @brief Define the DMA maximum transmit burst length. */
typedef enum _enet_dma_burstlen
{
    kENET_BurstLen1   = 0x00001U, /*!< DMA burst length 1. */
    kENET_BurstLen2   = 0x00002U, /*!< DMA burst length 2. */
    kENET_BurstLen4   = 0x00004U, /*!< DMA burst length 4. */
    kENET_BurstLen8   = 0x00008U, /*!< DMA burst length 8. */
    kENET_BurstLen16  = 0x00010U, /*!< DMA burst length 16. */
    kENET_BurstLen32  = 0x00020U, /*!< DMA burst length 32. */
    kENET_BurstLen64  = 0x10008U, /*!< DMA burst length 64. eight times enabled. */
    kENET_BurstLen128 = 0x10010U, /*!< DMA burst length 128. eight times enabled. */
    kENET_BurstLen256 = 0x10020U, /*!< DMA burst length 256. eight times enabled. */
} enet_dma_burstlen_t;

/*! @brief Define the flag for the descriptor. */
typedef enum _enet_desc_flag
{
    kENET_MiddleFlag = 0, /*!< It's a middle descriptor of the frame. */
    kENET_LastFlagOnly,   /*!< It's the last descriptor of the frame. */
    kENET_FirstFlagOnly,  /*!< It's the first descriptor of the frame. */
    kENET_FirstLastFlag   /*!< It's the first and last descriptor of the frame. */
} enet_desc_flag_t;

/*! @brief Define the system time adjust operation control. */
typedef enum _enet_systime_op
{
    kENET_SystimeAdd      = 0U, /*!< System time add to. */
    kENET_SystimeSubtract = 1U  /*!< System time subtract. */
} enet_systime_op_t;

/*! @brief Define the system time rollover control. */
typedef enum _enet_ts_rollover_type
{
    kENET_BinaryRollover  = 0, /*!< System time binary rollover.*/
    kENET_DigitalRollover = 1  /*!< System time digital rollover.*/
} enet_ts_rollover_type_t;

/*! @brief Defines some special configuration for ENET.
 *
 * These control flags are provided for special user requirements.
 * Normally, these is no need to set this control flags for ENET initialization.
 * But if you have some special requirements, set the flags to specialControl
 * in the enet_config_t.
 * @note "kENET_StoreAndForward" is recommended to be set when the
 * ENET_PTP1588FEATURE_REQUIRED is defined or else the timestamp will be mess-up
 * when the overflow happens.
 */
typedef enum _enet_special_config
{
    /***********************DMA CONFGI**********************************************/
    kENET_DescDoubleBuffer = 0x0001U, /*!< The double buffer is used in the Tx/Rx descriptor. */
    /**************************MTL************************************/
    kENET_StoreAndForward = 0x0002U, /*!< The Rx/Tx store and forward enable. */
    /***********************MAC****************************************/
    kENET_PromiscuousEnable       = 0x0004U, /*!< The promiscuous enabled. */
    kENET_FlowControlEnable       = 0x0008U, /*!< The flow control enabled. */
    kENET_BroadCastRxDisable      = 0x0010U, /*!< The broadcast disabled. */
    kENET_MulticastAllEnable      = 0x0020U, /*!< All multicast are passed. */
    kENET_8023AS2KPacket          = 0x0040U, /*!< 8023as support for 2K packets. */
    kENET_RxChecksumOffloadEnable = 0x0080U, /*!< The Rx checksum offload enabled. */
} enet_special_config_t;

/*! @brief List of DMA interrupts supported by the ENET interrupt. This
 * enumeration uses one-hot encoding to allow a logical OR of multiple
 * members.
 */
typedef enum _enet_dma_interrupt_enable
{
    kENET_DmaTx                = ENET_DMA_CH_DMA_CHX_INT_EN_TIE_MASK,  /*!< Tx interrupt. */
    kENET_DmaTxStop            = ENET_DMA_CH_DMA_CHX_INT_EN_TXSE_MASK, /*!< Tx stop interrupt. */
    kENET_DmaTxBuffUnavail     = ENET_DMA_CH_DMA_CHX_INT_EN_TBUE_MASK, /*!< Tx buffer unavailable. */
    kENET_DmaRx                = ENET_DMA_CH_DMA_CHX_INT_EN_RIE_MASK,  /*!< Rx interrupt. */
    kENET_DmaRxBuffUnavail     = ENET_DMA_CH_DMA_CHX_INT_EN_RBUE_MASK, /*!< Rx buffer unavailable. */
    kENET_DmaRxStop            = ENET_DMA_CH_DMA_CHX_INT_EN_RSE_MASK,  /*!< Rx stop. */
    kENET_DmaRxWatchdogTimeout = ENET_DMA_CH_DMA_CHX_INT_EN_RWTE_MASK, /*!< Rx watchdog timeout. */
    kENET_DmaEarlyTx           = ENET_DMA_CH_DMA_CHX_INT_EN_ETIE_MASK, /*!< Early transmit. */
    kENET_DmaEarlyRx           = ENET_DMA_CH_DMA_CHX_INT_EN_ERIE_MASK, /*!< Early receive. */
    kENET_DmaBusErr            = ENET_DMA_CH_DMA_CHX_INT_EN_FBEE_MASK, /*!< Fatal bus error. */
} enet_dma_interrupt_enable_t;

/*! @brief List of mac interrupts supported by the ENET interrupt. This
 * enumeration uses one-hot encoding to allow a logical OR of multiple
 * members.
 */
typedef enum _enet_mac_interrupt_enable
{
    kENET_MacPmt       = (ENET_MAC_INTERRUPT_ENABLE_PMTIE_MASK << ENET_MACINT_ENUM_OFFSET),
    kENET_MacTimestamp = (ENET_MAC_INTERRUPT_ENABLE_TSIE_MASK << ENET_MACINT_ENUM_OFFSET),
} enet_mac_interrupt_enable_t;

/*! @brief Defines the common interrupt event for callback use. */
typedef enum _enet_event
{
    kENET_RxIntEvent,        /*!< Receive interrupt event. */
    kENET_TxIntEvent,        /*!< Transmit interrupt event. */
    kENET_WakeUpIntEvent,    /*!< Wake up interrupt event. */
    kENET_TimeStampIntEvent, /*!< Time stamp interrupt event. */
} enet_event_t;

/*! @brief Define the DMA transmit arbitration for multi-queue. */
typedef enum _enet_dma_tx_sche
{
    kENET_FixPri = 0,      /*!< Fixed priority. channel 0 has lower priority than channel 1. */
    kENET_WeightStrPri,    /*!< Weighted(burst length) strict priority. */
    kENET_WeightRoundRobin /*!< Weighted (weight factor) round robin. */
} enet_dma_tx_sche_t;

/*! @brief Define the MTL Tx scheduling algorithm for multiple queues/rings. */
typedef enum _enet_mtl_multiqueue_txsche
{
    kENET_txWeightRR = 0U, /*!< Tx weight round-robin. */
    kENET_txStrPrio  = 3U, /*!< Tx strict priority. */
} enet_mtl_multiqueue_txsche_t;

/*! @brief Define the MTL Rx scheduling algorithm for multiple queues/rings. */
typedef enum _enet_mtl_multiqueue_rxsche
{
    kENET_rxStrPrio = 0U,  /*!< Tx weight round-robin, Rx strict priority. */
    kENET_rxWeightStrPrio, /*!< Tx strict priority, Rx weight strict priority. */
} enet_mtl_multiqueue_rxsche_t;

/*! @brief Define the MTL Rx queue and DMA channel mapping. */
typedef enum _enet_mtl_rxqueuemap
{
    kENET_StaticDirctMap = 0x100U, /*!< The received fame in Rx Qn(n = 0,1) direclty map to dma channel n. */
    kENET_DynamicMap =
        0x1010U, /*!< The received frame in Rx Qn(n = 0,1) map to the dma channel m(m = 0,1) related with the same Mac.
                  */
} enet_mtl_rxqueuemap_t;

/*! @brief Defines the ENET PTP message related constant. */
typedef enum _enet_ptp_event_type
{
    kENET_PtpEventMsgType = 3U,   /*!< PTP event message type. */
    kENET_PtpSrcPortIdLen = 10U,  /*!< PTP message sequence id length. */
    kENET_PtpEventPort    = 319U, /*!< PTP event port number. */
    kENET_PtpGnrlPort     = 320U  /*!< PTP general port number. */
} enet_ptp_event_type_t;

/*! @brief Define the Tx checksum offload options. */
typedef enum _enet_tx_offload
{
    kENET_TxOffloadDisable             = 0U, /*!< Disable Tx checksum offload. */
    kENET_TxOffloadIPHeader            = 1U, /*!< Enable IP header checksum calculation and insertion. */
    kENET_TxOffloadIPHeaderPlusPayload = 2U, /*!< Enable IP header and payload checksum calculation and insertion. */
    kENET_TxOffloadAll = 3U, /*!< Enable IP header, payload and pseudo header checksum calculation and insertion. */
} enet_tx_offload_t;

/*! @brief Ethernet VLAN Tag protocol identifiers. */
typedef enum _enet_vlan_tpid
{
    kENET_StanCvlan = 0x0U, /*!< C-VLAN 0x8100. */
    kENET_StanSvlan,        /*!< S-VLAN 0x88A8. */
} enet_vlan_tpid_t;

/*! @brief Ethernet VLAN operations. */
typedef enum _enet_vlan_ops
{
    kENET_NoOps = 0x0U, /*!< Not do anything. */
    kENET_VlanRemove,   /*!< Remove VLAN Tag. */
    kENET_VlanInsert,   /*!< Insert VLAN Tag. */
    kENET_VlanReplace,  /*!< Replace VLAN Tag. */
} enet_vlan_ops_t;

/*! @brief Ethernet VLAN strip setting. */
typedef enum _enet_vlan_strip
{
    kENET_VlanNotStrip = 0x0U, /*!< Not strip frame. */
    kENET_VlanFilterPassStrip, /*!< Strip if VLAN filter passes. */
    kENET_VlanFilterFailStrip, /*!< Strip if VLAN filter fails. */
    kENET_VlanAlwaysStrip,     /*!< Always strip. */
} enet_vlan_strip_t;

/*! @brief Ethernet VLAN Tx channels. */
typedef enum _enet_vlan_tx_channel
{
    kENET_VlanTagAllChannels = 0xFFU, /*!< VLAN tag is inserted for every packets transmitted by the MAC. */
    kENET_VlanTagChannel0    = 0x0U,  /*!< VLAN tag is inserted for the frames transmitted by channel 0. */
    kENET_VlanTagChannel1,            /*!< VLAN tag is inserted for the frames transmitted by channel 1. */
} enet_vlan_tx_channel_t;

/*! @brief Defines the receive descriptor structure
 *  It has the read-format and write-back format structures. They both
 *  have the same size with different region definition. So we define
 *  common name as the recive descriptor structure. When initialize
 *  the buffer descriptors, read-format region mask bits should be used.
 *  When Rx frame has been in the buffer descriptors, write-back format
 *  region store the Rx result information.
 */
typedef struct _enet_rx_bd_struct
{
    __IO uint32_t rdes0; /*!< Receive descriptor 0 */
    __IO uint32_t rdes1; /*!< Receive descriptor 1 */
    __IO uint32_t rdes2; /*!< Receive descriptor 2 */
    __IO uint32_t rdes3; /*!< Receive descriptor 3 */
} enet_rx_bd_struct_t;

/*! @brief Defines the transmit descriptor structure
 *  It has the read-format and write-back format structure. They both
 *  has the same size with different region definition.  So we define
 *  common name as the transmit descriptor structure. When initialize
 *  the buffer descriptors for Tx, read-format region mask bits should
 *  be used. When frame has been transmitted, write-back format region
 *  store the Tx result information.
 */
typedef struct _enet_tx_bd_struct
{
    __IO uint32_t tdes0; /*!< Transmit descriptor 0 */
    __IO uint32_t tdes1; /*!< Transmit descriptor 1 */
    __IO uint32_t tdes2; /*!< Transmit descriptor 2 */
    __IO uint32_t tdes3; /*!< Transmit descriptor 3 */
} enet_tx_bd_struct_t;

/*! @brief Defines the Tx BD configuration structure. */
typedef struct _enet_tx_bd_config_struct
{
    void *buffer1;                  /*!< The first buffer address in the descriptor. */
    uint32_t bytes1;                /*!< The bytes in the fist buffer. */
    void *buffer2;                  /*!< The second buffer address in the descriptor. */
    uint32_t bytes2;                /*!< The bytes in the second buffer. */
    uint32_t framelen;              /*!< The length of the frame to be transmitted. */
    bool intEnable;                 /*!< Interrupt enable flag. */
    bool tsEnable;                  /*!< The timestamp enable. */
    enet_tx_offload_t txOffloadOps; /*!< The Tx checksum offload option, only vaild for Queue 0. */
    enet_desc_flag_t flag;          /*!< The flag of this tx desciriptor, see "enet_qos_desc_flag". */
    uint8_t slotNum;                /*!< The slot number used for AV mode only. */
} enet_tx_bd_config_struct_t;

#ifdef ENET_PTP1588FEATURE_REQUIRED
/*! @brief Defines the ENET PTP configuration structure. */
typedef struct _enet_ptp_config
{
    bool fineUpdateEnable;              /*!< Use the fine update. */
    bool ptp1588V2Enable;               /*!< ptp 1588 version 2 is used. */
    enet_ts_rollover_type_t tsRollover; /*!< 1588 time nanosecond rollover. */
} enet_ptp_config_t;
#endif                                  /* ENET_PTP1588FEATURE_REQUIRED */

/*! @brief Defines the ENET PTP time stamp structure. */
typedef struct _enet_ptp_time
{
    uint64_t second;     /*!< Second. */
    uint32_t nanosecond; /*!< Nanosecond. */
} enet_ptp_time_t;

/*! @brief Defines the Tx reclaim information structure. */
typedef struct enet_tx_reclaim_info
{
    void *context;             /*!< User specified data, could be buffer address for free */
    bool isTsAvail;            /*!< Flag indicates timestamp available status */
    enet_ptp_time_t timeStamp; /*!< Timestamp of frame */
} enet_tx_reclaim_info_t;

/*! @brief Defines the ENET transmit dirty addresses ring/queue structure. */
typedef struct _enet_tx_dirty_ring
{
    enet_tx_reclaim_info_t *txDirtyBase; /*!< Dirty buffer descriptor base address pointer. */
    uint16_t txGenIdx;                   /*!< Tx generate index. */
    uint16_t txConsumIdx;                /*!< Tx consume index. */
    uint16_t txRingLen;                  /*!< Tx ring length. */
    bool isFull;                         /*!< Tx ring is full flag, add this parameter to avoid waste one element. */
} enet_tx_dirty_ring_t;

/*! @brief Defines the buffer descriptor configure structure.
 *
 * Notes:
 * 1. The receive and transmit descriptor start address pointer and tail pointer must be word-aligned.
 * 2. The recommended minimum Tx/Rx ring length is 4.
 * 3. The Tx/Rx descriptor tail address shall be the address pointer to the address just after the end
 *    of the last last descriptor. because only the descriptors between the start address and the
 *    tail address will be used by DMA.
 * 4. The decriptor address is the start address of all used contiguous memory.
 *    for example, the rxDescStartAddrAlign is the start address of rxRingLen contiguous descriptor memorise
 *    for Rx descriptor ring 0.
 * 5. The "*rxBufferstartAddr" is the first element of  rxRingLen (2*rxRingLen for double buffers)
 *    Rx buffers. It means the *rxBufferStartAddr is the Rx buffer for the first descriptor
 *    the *rxBufferStartAddr + 1 is the Rx buffer for the second descriptor or the Rx buffer for
 *    the second buffer in the first descriptor. So please make sure the rxBufferStartAddr is the
 *    address of a rxRingLen or 2*rxRingLen array.
 */
typedef struct _enet_buffer_config
{
    uint8_t rxRingLen;                         /*!< The length of receive buffer descriptor ring. */
    uint8_t txRingLen;                         /*!< The length of transmit buffer descriptor ring. */
    enet_tx_bd_struct_t *txDescStartAddrAlign; /*!< Aligned transmit descriptor start address. */
    enet_tx_bd_struct_t *txDescTailAddrAlign;  /*!< Aligned transmit descriptor tail address. */
    enet_tx_reclaim_info_t *txDirtyStartAddr;  /*!< Start address of the dirty Tx frame information. */
    enet_rx_bd_struct_t *rxDescStartAddrAlign; /*!< Aligned receive descriptor start address. */
    enet_rx_bd_struct_t *rxDescTailAddrAlign;  /*!< Aligned receive descriptor tail address. */
    uint32_t *rxBufferStartAddr;               /*!< Start address of the Rx buffers. */
    uint32_t rxBuffSizeAlign;                  /*!< Aligned receive data buffer size. */
} enet_buffer_config_t;

/*! @brief Defines the configuration when multi-queue is used. */
typedef struct enet_multiqueue_config
{
    /***********************DMA block*******************************/
    enet_dma_tx_sche_t dmaTxSche;              /*!< Transmit arbitation. */
    enet_dma_burstlen_t burstLen;              /*!< Burset len for the queue 1. */
    uint8_t txdmaChnWeight[ENET_RING_NUM_MAX]; /*!< Transmit channel weight. */
    /***********************MTL block*******************************/
    enet_mtl_multiqueue_txsche_t mtltxSche;  /*!< Transmit schedule for multi-queue. */
    enet_mtl_multiqueue_rxsche_t mtlrxSche;  /*!< Receive schedule for multi-queue. */
    uint8_t rxqueweight[ENET_RING_NUM_MAX];  /*!< Refer to the MTL RxQ Control register. */
    uint32_t txqueweight[ENET_RING_NUM_MAX]; /*!< Refer to the MTL TxQ Quantum Weight register. */
    uint8_t rxqueuePrio[ENET_RING_NUM_MAX];  /*!< Receive queue priority. */
    uint8_t txqueuePrio[ENET_RING_NUM_MAX];  /*!< Refer to Transmit Queue Priority Mapping register. */
    enet_mtl_rxqueuemap_t mtlrxQuemap;       /*!< Rx queue DMA Channel mapping. */
} enet_multiqueue_config_t;

/*! @brief Defines the Rx memory buffer alloc function pointer. */
typedef void *(*enet_rx_alloc_callback_t)(ENET_Type *base, void *userData, uint8_t channel);

/*! @brief Defines the Rx memory buffer free function pointer. */
typedef void (*enet_rx_free_callback_t)(ENET_Type *base, void *buffer, void *userData, uint8_t channel);

/*! @brief Defines the basic configuration structure for the ENET device.
 *
 * Note:
 *  1. Default the signal queue is used so the "multiqueueCfg" is set default
 *  with NULL. Set the pointer with a valid configration pointer if the multiple
 *  queues are required. If multiple queue is enabled, please make sure the
 *  buffer configuration for all are prepared also.
 */
typedef struct _enet_config
{
    uint16_t specialControl;                 /*!< The logicl or of enet_special_config_t */
    uint32_t ptpClkHz;                       /*!< The PTP module source clock. */
    enet_multiqueue_config_t *multiqueueCfg; /*!< Use both Tx/Rx queue(dma channel) 0 and 1. */
    uint32_t interrupt;                      /*!< MAC interrupt source. A logical OR of enet_dma_interrupt_enable_t and
                                                enet_mac_interrupt_enable_t. */
    /* -----------------MAC block-------------------------------*/
    enet_mii_mode_t miiMode;     /*!< MII mode. */
    enet_mii_speed_t miiSpeed;   /*!< MII Speed. */
    enet_mii_duplex_t miiDuplex; /*!< MII duplex. */
    uint16_t pauseDuration; /*!< Used in the Tx flow control frame, only valid when kENET_FlowControlEnable is set. */
    /* -----------------Timestamp-------------------------------*/
#ifdef ENET_PTP1588FEATURE_REQUIRED
    enet_ptp_config_t *ptpConfig; /*!< PTP 1588 feature configuration */
#endif
    /* -----------Rx zero copy buffer management----------------*/
    enet_rx_alloc_callback_t rxBuffAlloc; /*!< Callback to alloc memory, must be provided for zero-copy Rx. */
    enet_rx_free_callback_t rxBuffFree;   /*!< Callback to free memory, must be provided for zero-copy Rx. */
} enet_config_t;

/* Forward declaration of the handle typedef. */
typedef struct _enet_handle enet_handle_t;

/*! @brief ENET callback function. */
typedef void (*enet_callback_t)(ENET_Type *base,
                                enet_handle_t *handle,
                                enet_event_t event,
                                uint8_t channel,
                                enet_tx_reclaim_info_t *txReclaimInfo,
                                void *userData);

/*! @brief Defines the ENET transmit buffer descriptor ring/queue structure. */
typedef struct _enet_tx_bd_ring
{
    enet_tx_bd_struct_t *txBdBase; /*!< Buffer descriptor base address pointer. */
    uint16_t txGenIdx;             /*!< Tx generate index. */
    uint16_t txConsumIdx;          /*!< Tx consum index. */
    volatile uint16_t txDescUsed;  /*!< Tx descriptor used number. */
    uint16_t txRingLen;            /*!< Tx ring length. */
} enet_tx_bd_ring_t;

/*! @brief Defines the ENET receive buffer descriptor ring/queue structure. */
typedef struct _enet_rx_bd_ring
{
    enet_rx_bd_struct_t *rxBdBase; /*!< Buffer descriptor base address pointer. */
    uint16_t rxGenIdx;             /*!< The current available receive buffer descriptor pointer. */
    uint16_t rxRingLen;            /*!< Receive ring length. */
    uint32_t rxBuffSizeAlign;      /*!< Receive buffer size. */
} enet_rx_bd_ring_t;

/*! @brief Defines the ENET handler structure. */
struct _enet_handle
{
    bool multiQueEnable;                                 /*!< Multi-queue enable status. */
    bool doubleBuffEnable;                               /*!< The double buffer enable status. */
    bool rxintEnable;                                    /*!< Rx interrupt enable status. */
    enet_rx_bd_ring_t rxBdRing[ENET_RING_NUM_MAX];       /*!< Receive buffer descriptor.  */
    enet_tx_bd_ring_t txBdRing[ENET_RING_NUM_MAX];       /*!< Transmit buffer descriptor.  */
    enet_tx_dirty_ring_t txDirtyRing[ENET_RING_NUM_MAX]; /*!< Transmit dirty buffers addresses.  */
    uint32_t *rxBufferStartAddr[ENET_RING_NUM_MAX];      /*!< The Init-Rx buffers used for reinit corrupted BD due to
                                                            write-back operation. */
    uint32_t txLenLimitation[ENET_RING_NUM_MAX];         /*!< Tx frame length limitation. */
    enet_callback_t callback;                            /*!< Callback function. */
    void *userData;                                      /*!< Callback function parameter.*/
    enet_rx_alloc_callback_t rxBuffAlloc; /*!< Callback to alloc memory, must be provided for zero-copy Rx. */
    enet_rx_free_callback_t rxBuffFree;   /*!< Callback to free memory, must be provided for zero-copy Rx. */
};

typedef struct _enet_buffer_struct
{
    void *buffer;    /*!< The buffer stores the whole or partial frame. */
    uint16_t length; /*!< The byte length of this buffer. */
} enet_buffer_struct_t;

/*! @brief Rx frame attribute structure. */
typedef struct _enet_rx_frame_attribute_struct
{
    bool isTsAvail;            /*!< Rx frame timestamp is available or not. */
    enet_ptp_time_t timestamp; /*!< The nanosecond part timestamp of this Rx frame. */
} enet_rx_frame_attribute_t;

/*! @brief Defines the Rx frame error structure. */
typedef struct _enet_rx_frame_error
{
    bool statsDribbleErr : 1;         /*!< The received packet has a non-integer multiple of bytes (odd nibbles). */
    bool statsRxErr : 1;              /*!< Receive error. */
    bool statsOverflowErr : 1;        /*!< Rx FIFO overflow error. */
    bool statsWatchdogTimeoutErr : 1; /*!< Receive watchdog timeout. */
    bool statsGaintPacketErr : 1;     /*!< Receive error. */
    bool statsRxFcsErr : 1;           /*!< Receive CRC error. */
} enet_rx_frame_error_t;

/*! @brief Defines the Rx frame data structure. */
typedef struct _enet_rx_frame_struct
{
    enet_buffer_struct_t *rxBuffArray;     /*!< Rx frame buffer structure. */
    uint16_t totLen;                       /*!< Rx frame total length. */
    enet_rx_frame_attribute_t rxAttribute; /*!< Rx frame attribute structure. */
    enet_rx_frame_error_t rxFrameError;    /*!< Rx frame error. */
} enet_rx_frame_struct_t;

typedef struct _enet_tx_config_struct
{
    uint8_t intEnable : 1;          /*!< Enable interrupt every time one BD is completed. */
    uint8_t tsEnable : 1;           /*!< Transmit timestamp enable. */
    uint8_t slotNum : 4;            /*!< Slot number control bits in AV mode. */
    enet_tx_offload_t txOffloadOps; /*!< Tx checksum offload option. */
} enet_tx_config_struct_t;

typedef struct _enet_tx_frame_struct
{
    enet_buffer_struct_t *txBuffArray; /*!< Tx frame buffer structure. */
    uint32_t txBuffNum;                /*!< Buffer number of this Tx frame. */
    enet_tx_config_struct_t txConfig;  /*!< Tx extra configuation. */
    void *context;                     /*!< Driver reclaims and gives it in Tx over callback. */
} enet_tx_frame_struct_t;

/*! @brief Ethernet VLAN Tag. */
typedef struct _enet_vlan_tag
{
    enet_vlan_tpid_t tpid; /*!< VLAN TPID. */
    uint16_t pcp : 3;      /*!< VLAN Priority. */
    uint16_t dei : 1;      /*!< Drop Eligible indicator. */
    uint16_t vid : 12;     /*!< VLAN Identifier. */
} enet_vlan_tag_t;

/*! @brief Ethernet VLAN configuration for Tx. */
typedef struct _enet_vlan_tx_config
{
    bool txDescVlan;     /*!< Use VLAN configuration in Tx descriptor. */
    enet_vlan_tag_t tag; /*!< VLAN Tag. */
    enet_vlan_ops_t ops; /*!< VLAN operations. */
} enet_vlan_tx_config_t;

/*! @brief Ethernet VLAN control. */
typedef struct _enet_vlan_ctrl
{
    bool svlanEnable : 1;          /*!< The MAC transmitter and receiver consider the S-VLAN packets. */
    bool vlanInverseMatch : 1;     /*!< True: Marks frames without matching as match, False: Marks matched frames. */
    bool vidComparison : 1;        /*!< Only takes VLAN VID as match. */
    bool disableVlanTypeCheck : 1; /*!< Not check C-VLAN and S-VLAN. */
    bool doubleVlanEnable : 1;     /*!< Enable the inner VLAN operations. */
    bool innerVlanFilterMatch : 1; /*!< Takes Inner VLAN as match. */
    bool outerTagInRxStatus : 1;   /*!< Set outer VLAN in Rx Status. */
    bool innerTagInRxStatus : 1;   /*!< Set inner VLAN in Rx Status. */
    enet_vlan_tag_t rxVlanTag;     /*!< VLAN tag for Rx match. */
    enet_vlan_strip_t rxOuterVlanStrip; /*!< Outer VLAN Rx strip operation. */
    enet_vlan_strip_t rxInnerVlanStrip; /*!< Inner VLAN Rx strip operation. */
} enet_vlan_ctrl_t;

/* Typedef for interrupt handler. */
typedef void (*enet_isr_t)(ENET_Type *base, enet_handle_t *handle);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to enet clocks for each instance. */
extern const clock_ip_name_t s_enetClock[];
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

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
 * structure for ENET_Init(). User may use the initialized
 * structure unchanged in ENET_Init(), or modify some fields of the
 * structure before calling ENET_Init().
 * Example:
   @code
   enet_config_t config;
   ENET_GetDefaultConfig(&config);
   @endcode
 * @param config The ENET mac controller configuration structure pointer.
 */
void ENET_GetDefaultConfig(enet_config_t *config);

/*!
 * @brief Initializes the ENET module.
 *
 * This function ungates the module clock and initializes it with the ENET basic
 * configuration.
 * @note As our transactional transmit API use the zero-copy transmit buffer.
 * So there are two thing we emphasize here:
 *  1. Tx buffer free/requeue for application should be done in the Tx
 *  interrupt handler. Please set callback: kENET_TxIntEvent with Tx buffer free/requeue
 *  process APIs.
 *  2. The Tx interrupt is forced to open.
 *
 * @param base    ENET peripheral base address.
 * @param config  ENET mac configuration structure pointer.
 *        The "enet_config_t" type mac configuration return from ENET_GetDefaultConfig
 *        can be used directly. It is also possible to verify the Mac configuration using other methods.
 * @param macAddr  ENET mac address of Ethernet device. This MAC address should be
 *        provided.
 * @param clkSrcHz ENET input reference clock.
 */
void ENET_Init(ENET_Type *base, const enet_config_t *config, uint8_t *macAddr, uint32_t clkSrcHz);

/*!
 * @brief Deinitializes the ENET module.

 * This function gates the module clock and disables the ENET module.
 *
 * @param base  ENET peripheral base address.
 */
void ENET_Deinit(ENET_Type *base);

/*!
 * @brief Initialize for all ENET descriptors.
 *
 * @note This function finishes all Tx/Rx descriptors initialization. The descriptor initialization
 * should be called after ENET_Init().
 *
 * @param base  ENET peripheral base address.
 * @param config The configuration for ENET.
 * @param bufferConfig All buffers configuration.
 */
status_t ENET_DescriptorInit(ENET_Type *base, enet_config_t *config, enet_buffer_config_t *bufferConfig);

/*!
 * @brief Allocates Rx buffers for all BDs.
 * It's used for zero copy Rx. In zero copy Rx case, Rx buffers are dynamic. This function
 * will populate initial buffers in all BDs for receiving. Then ENET_GetRxFrame() is used
 * to get Rx frame with zero copy, it will allocate new buffer to replace the buffer in BD taken
 * by application, application should free those buffers after they're used.
 *
 * @note This function should be called after ENET_CreateHandler() and buffer allocating callback
 * function should be ready.
 *
 * @param base  ENET peripheral base address.
 * @param handle The ENET handler structure. This is the same handler pointer used in the ENET_Init.
 */
status_t ENET_RxBufferAllocAll(ENET_Type *base, enet_handle_t *handle);

/*!
 * @brief Frees Rx buffers in all BDs.
 * It's used for zero copy Rx. In zero copy Rx case, Rx buffers are dynamic. This function
 * will free left buffers in all BDs.
 *
 * @param base  ENET peripheral base address.
 * @param handle The ENET handler structure. This is the same handler pointer used in the ENET_Init.
 */
void ENET_RxBufferFreeAll(ENET_Type *base, enet_handle_t *handle);

/*!
 * @brief Starts the ENET Tx/Rx.
 * This function enable the Tx/Rx and starts the Tx/Rx DMA.
 * This shall be set after ENET initialization and before
 * starting to receive the data.
 *
 * @param base  ENET peripheral base address.
 * @param rxRingNum  The number of the used Rx rings. It shall not be
 * larger than the ENET_RING_NUM_MAX(2). If the ringNum is set with
 * 1, the ring 0 will be used.
 * @param txRingNum  The number of the used Tx rings. It shall not be
 * larger than the ENET_RING_NUM_MAX(2). If the ringNum is set with
 * 1, the ring 0 will be used.
 *
 * @note This must be called after all the ENET initilization.
 * And should be called when the ENET receive/transmit is required.
 */
void ENET_StartRxTx(ENET_Type *base, uint8_t txRingNum, uint8_t rxRingNum);

/*!
 * @brief Set the second level IRQ handler
 *
 * @param base ENET peripheral base address.
 * @param ISRHandler The handler to install.
 */
void ENET_SetISRHandler(ENET_Type *base, enet_isr_t ISRHandler);

/* @} */

/*!
 * @name MII interface operation
 * @{
 */

/*!
 * @brief Sets the ENET MII speed and duplex.
 *
 * This API is provided to dynamically change the speed and dulpex for MAC.
 *
 * @param base  ENET peripheral base address.
 * @param speed The speed of the RMII mode.
 * @param duplex The duplex of the RMII mode.
 */
static inline void ENET_SetMII(ENET_Type *base, enet_mii_speed_t speed, enet_mii_duplex_t duplex)
{
    uint32_t reg = base->MAC_CONFIGURATION & ~(ENET_MAC_CONFIGURATION_DM_MASK | ENET_MAC_CONFIGURATION_FES_MASK);
    reg |= ENET_MAC_CONFIGURATION_DM(duplex) | ENET_MAC_CONFIGURATION_FES(speed);

    base->MAC_CONFIGURATION = reg;
}

/*!
 * @brief Sets the ENET SMI(serial management interface)- MII management interface.
 *
 * @param base  ENET peripheral base address.
 * @param clkSrcHz  ENET peripheral clock source.
 */
void ENET_SetSMI(ENET_Type *base, uint32_t clkSrcHz);

/*!
 * @brief Checks if the SMI is busy.
 *
 * @param base  ENET peripheral base address.
 * @return The status of MII Busy status.
 */
static inline bool ENET_IsSMIBusy(ENET_Type *base)
{
    return ((base->MAC_MDIO_ADDRESS & ENET_MAC_MDIO_ADDRESS_GB_MASK) != 0U) ? true : false;
}

/*!
 * @brief Reads data from the PHY register through SMI interface.
 *
 * @param base  ENET peripheral base address.
 * @return The data read from PHY
 */
static inline uint16_t ENET_ReadSMIData(ENET_Type *base)
{
    return (uint16_t)(base->MAC_MDIO_DATA & ENET_MAC_MDIO_DATA_GD_MASK);
}

/*!
 * @brief Sends the MDIO IEEE802.3 Clause 22 format write command.
 *
 * @param base  ENET peripheral base address.
 * @param phyAddr The PHY address.
 * @param regAddr The PHY register.
 * @param data The data written to PHY.
 */
void ENET_StartSMIWrite(ENET_Type *base, uint8_t phyAddr, uint8_t regAddr, uint16_t data);

/*!
 * @brief Sends the MDIO IEEE802.3 Clause 22 format read command.
 *
 * @param base  ENET peripheral base address.
 * @param phyAddr The PHY address.
 * @param regAddr The PHY register.
 */
void ENET_StartSMIRead(ENET_Type *base, uint8_t phyAddr, uint8_t regAddr);

/*!
 * @brief MDIO write with IEEE802.3 Clause 22 format.
 *
 * @param base  ENET peripheral base address.
 * @param phyAddr  The PHY address.
 * @param regAddr  The PHY register.
 * @param data  The data written to PHY.
 * @return kStatus_Success  MDIO access succeeds.
 * @return kStatus_Timeout  MDIO access timeout.
 */
status_t ENET_MDIOWrite(ENET_Type *base, uint8_t phyAddr, uint8_t regAddr, uint16_t data);

/*!
 * @brief MDIO read with IEEE802.3 Clause 22 format.
 *
 * @param base  ENET peripheral base address.
 * @param phyAddr  The PHY address.
 * @param regAddr  The PHY register.
 * @param pData  The data read from PHY.
 * @return kStatus_Success  MDIO access succeeds.
 * @return kStatus_Timeout  MDIO access timeout.
 */
status_t ENET_MDIORead(ENET_Type *base, uint8_t phyAddr, uint8_t regAddr, uint16_t *pData);
/* @} */

/*!
 * @name Other basic operation
 * @{
 */

/*!
 * @brief Get the ENET instance from peripheral base address.
 *
 * @param base ENET peripheral base address.
 * @return ENET instance.
 */
uint32_t ENET_GetInstance(ENET_Type *base);

/*!
 * @brief Sets the ENET module Mac address.
 *
 * @param base  ENET peripheral base address.
 * @param macAddr The six-byte Mac address pointer.
 *        The pointer is allocated by application and input into the API.
 */
static inline void ENET_SetMacAddr(ENET_Type *base, uint8_t *macAddr)
{
    assert(macAddr);

    uint32_t lowAddress = ((uint32_t)macAddr[3] << 24) | ((uint32_t)macAddr[2] << 16) | ((uint32_t)macAddr[1] << 8) |
                          ((uint32_t)macAddr[0]);
    uint32_t highAddress = ((uint32_t)macAddr[5] << 8) | ((uint32_t)macAddr[4]);
    /* Set Macaddr, the MAC address registers are configured to be double-synchronized to the MII clock
      domains, then the synchronization is triggered only when bits 31:24 (in little-endian mode)
      or bits 7:0 (in Big-Endian mode) of the MAC address low register are written to.*/
    base->MAC_ADDRESS0_HIGH = highAddress;
    base->MAC_ADDRESS0_LOW  = lowAddress;
}

/*!
 * @brief Gets the ENET module Mac address.
 *
 * @param base  ENET peripheral base address.
 * @param macAddr The six-byte Mac address pointer.
 *        The pointer is allocated by application and input into the API.
 */
void ENET_GetMacAddr(ENET_Type *base, uint8_t *macAddr);

/*!
 * @brief Enable ENET device to accept all multicast frames.
 *
 * @param base    ENET peripheral base address.
 */
static inline void ENET_AcceptAllMulticast(ENET_Type *base)
{
    uint32_t reg = base->MAC_PACKET_FILTER;

    base->MAC_PACKET_FILTER = reg | ENET_MAC_PACKET_FILTER_PM_MASK;
}

/*!
 * @brief ENET device reject to accept all multicast frames.
 *
 * @param base  ENET peripheral base address.
 */
static inline void ENET_RejectAllMulticast(ENET_Type *base)
{
    uint32_t reg = base->MAC_PACKET_FILTER;

    base->MAC_PACKET_FILTER = reg & ~ENET_MAC_PACKET_FILTER_PM_MASK;
}

/*!
 * @brief Set the MAC to enter into power down mode.
 * the remote power wake up frame and magic frame can wake up
 * the ENET from the power down mode.
 *
 * @param base    ENET peripheral base address.
 * @param wakeFilter  The wakeFilter provided to configure the wake up frame fitlter.
 *  Set the wakeFilter to NULL is not required. But if you have the filter requirement,
 *  please make sure the wakeFilter pointer shall be eight continous
 *  32-bits configuration.
 */
void ENET_EnterPowerDown(ENET_Type *base, uint32_t *wakeFilter);

/*!
 * @brief Set the MAC to exit power down mode.
 * Eixt from the power down mode and recover to normal work mode.
 *
 * @param base    ENET peripheral base address.
 */
static inline void ENET_ExitPowerDown(ENET_Type *base)
{
    /* Clear and status ans reset the power down. */
    base->MAC_PMT_CONTROL_STATUS &= ~ENET_MAC_PMT_CONTROL_STATUS_PWRDWN_MASK;

    /* Restore the Tx which is disabled when enter power down mode. */
    base->DMA_CH[0].DMA_CHX_TX_CTRL |= ENET_DMA_CH_DMA_CHX_TX_CTRL_ST_MASK;
    base->DMA_CH[1].DMA_CHX_TX_CTRL |= ENET_DMA_CH_DMA_CHX_TX_CTRL_ST_MASK;
    base->MAC_CONFIGURATION |= ENET_MAC_CONFIGURATION_TE_MASK;
}

/*!
 * @brief Set VLAN control.
 *
 * @param base  ENET peripheral base address.
 * @param control  VLAN control configuration.
 */
status_t ENET_SetVlanCtrl(ENET_Type *base, enet_vlan_ctrl_t *control);

/*!
 * @brief Set Tx outer VLAN configuration.
 *
 * @param base  ENET peripheral base address.
 * @param config  Tx VLAN operation configuration.
 * @param channel  The channel to apply this configuration.
 */
status_t ENET_SetTxOuterVlan(ENET_Type *base, enet_vlan_tx_config_t *config, enet_vlan_tx_channel_t channel);

/*!
 * @brief Set Tx inner VLAN configuration.
 *
 * @param base  ENET peripheral base address.
 * @param config  Tx VLAN operation configuration.
 */
status_t ENET_SetTxInnerVlan(ENET_Type *base, enet_vlan_tx_config_t *config);

/* @} */

/*!
 * @name Interrupts.
 * @{
 */

/*!
 * @brief Enables the ENET DMA and MAC interrupts.
 *
 * This function enables the ENET interrupt according to the provided mask. The mask
 * is a logical OR of enet_dma_interrupt_enable_t and enet_mac_interrupt_enable_t.
 * For example, to enable the dma and mac interrupt, do the following.
 * @code
 *     ENET_EnableInterrupts(ENET, kENET_DmaRx | kENET_DmaTx | kENET_MacPmt);
 * @endcode
 *
 * @param base  ENET peripheral base address.
 * @param mask  ENET interrupts to enable. This is a logical OR of both
 *             enumeration :: enet_dma_interrupt_enable_t and enet_mac_interrupt_enable_t.
 */
void ENET_EnableInterrupts(ENET_Type *base, uint32_t mask);

/*!
 * @brief Disables the ENET DMA and MAC interrupts.
 *
 * This function disables the ENET interrupt according to the provided mask. The mask
 * is a logical OR of enet_dma_interrupt_enable_t and enet_mac_interrupt_enable_t.
 * For example, to disable the dma and mac interrupt, do the following.
 * @code
 *     ENET_DisableInterrupts(ENET, kENET_DmaRx | kENET_DmaTx | kENET_MacPmt);
 * @endcode
 *
 * @param base  ENET peripheral base address.
 * @param mask  ENET interrupts to disables. This is a logical OR of both
 *             enumeration :: enet_dma_interrupt_enable_t and enet_mac_interrupt_enable_t.
 */
void ENET_DisableInterrupts(ENET_Type *base, uint32_t mask);

/*!
 * @brief Gets the ENET DMA interrupt status flag.
 *
 * @param base  ENET peripheral base address.
 * @param channel The DMA Channel. Shall not be larger than ENET_RING_NUM_MAX.
 * @return The event status of the interrupt source. This is the logical OR of members
 *         of the enumeration :: enet_dma_interrupt_enable_t.
 */
static inline uint32_t ENET_GetDmaInterruptStatus(ENET_Type *base, uint8_t channel)
{
    return base->DMA_CH[channel].DMA_CHX_STAT;
}

/*!
 * @brief Clear the ENET DMA interrupt status flag.
 *
 * @param base  ENET peripheral base address.
 * @param channel The DMA Channel. Shall not be larger than ENET_RING_NUM_MAX.
 * @param mask The event status of the interrupt source. This is the logical OR of members
 *         of the enumeration :: enet_dma_interrupt_enable_t.
 */
static inline void ENET_ClearDmaInterruptStatus(ENET_Type *base, uint8_t channel, uint32_t mask)
{
    /* Clear the dam interrupt status bit in dma channel interrupt status register. */
    base->DMA_CH[channel].DMA_CHX_STAT = mask;
}

/*!
 * @brief Gets the ENET MAC interrupt status flag.
 *
 * @param base  ENET peripheral base address.
 * @return The event status of the interrupt source.
 *       Use the enum in enet_mac_interrupt_enable_t and right shift
 *       ENET_MACINT_ENUM_OFFSET to mask the returned value to get the
 *       exact interrupt status.
 */
static inline uint32_t ENET_GetMacInterruptStatus(ENET_Type *base)
{
    return base->MAC_INTERRUPT_STATUS;
}

/*!
 * @brief Clears the ENET mac interrupt events status flag.
 *
 * This function clears enabled ENET interrupts according to the provided mask. The mask
 * is a logical OR of enumeration members. See the @ref enet_mac_interrupt_enable_t.
 * For example, to clear the TX frame interrupt and RX frame interrupt, do the following.
 * @code
 *     ENET_ClearMacInterruptStatus(ENET, kENET_MacPmt);
 * @endcode
 *
 * @param base  ENET peripheral base address.
 * @param mask  ENET interrupt source to be cleared.
 * This is the logical OR of members of the enumeration :: enet_mac_interrupt_enable_t.
 */
void ENET_ClearMacInterruptStatus(ENET_Type *base, uint32_t mask);

/* @} */

/*!
 * @name Functional operation.
 * @{
 */

/*!
 * @brief Get the Tx descriptor DMA Own flag.
 *
 * @param txDesc  The given Tx descriptor.
 * @retval True the dma own Tx descriptor, false application own Tx descriptor.
 *
 */
static inline bool ENET_IsTxDescriptorDmaOwn(enet_tx_bd_struct_t *txDesc)
{
    return ((txDesc->tdes3 & ENET_TXDESCRIP_RD_OWN_MASK) != 0U) ? true : false;
}

/*!
 * @brief Setup a given Tx descriptor.
 *  This function is a low level functional API to setup or prepare
 *  a given Tx descriptor.
 *
 * @param txDesc  The given Tx descriptor.
 * @param buffer1  The first buffer address in the descriptor.
 * @param bytes1  The bytes in the fist buffer.
 * @param buffer2  The second buffer address in the descriptor.
 * @param bytes2  The bytes in the second buffer.
 * @param framelen  The length of the frame to be transmitted.
 * @param intEnable Interrupt enable flag.
 * @param tsEnable The timestamp enable.
 * @param flag The flag of this Tx desciriptor, see "enet_desc_flag_t" .
 * @param slotNum The slot num used for AV mode only.
 *
 * @note This must be called after all the ENET initilization.
 * And should be called when the ENET receive/transmit is required.
 * Transmit buffers are 'zero-copy' buffers, so the buffer must remain in
 * memory until the packet has been fully transmitted. The buffers
 * should be free or requeued in the transmit interrupt irq handler.
 */
void ENET_SetupTxDescriptor(enet_tx_bd_struct_t *txDesc,
                            void *buffer1,
                            uint32_t bytes1,
                            void *buffer2,
                            uint32_t bytes2,
                            uint32_t framelen,
                            bool intEnable,
                            bool tsEnable,
                            enet_desc_flag_t flag,
                            uint8_t slotNum);

/*!
 * @brief Update the Tx descriptor tail pointer.
 *  This function is a low level functional API to update the
 *  the Tx descriptor tail.
 *  This is called after you setup a new Tx descriptor to update
 *  the tail pointer to make the new descritor accessable by DMA.
 *
 * @param base    ENET peripheral base address.
 * @param channel  The Tx DMA channel.
 * @param txDescTailAddrAlign  The new Tx tail pointer address.
 *
 */
static inline void ENET_UpdateTxDescriptorTail(ENET_Type *base, uint8_t channel, uint32_t txDescTailAddrAlign)
{
    base->DMA_CH[channel].DMA_CHX_TXDESC_TAIL_PTR = txDescTailAddrAlign & ~ENET_ADDR_ALIGNMENT;
}

/*!
 * @brief Update the Rx descriptor tail pointer.
 *  This function is a low level functional API to update the
 *  the Rx descriptor tail.
 *  This is called after you setup a new Rx descriptor to update
 *  the tail pointer to make the new descritor accessable by DMA
 *  and to anouse the Rx poll command for DMA.
 *
 * @param base    ENET peripheral base address.
 * @param channel  The Rx DMA channel.
 * @param rxDescTailAddrAlign  The new Rx tail pointer address.
 *
 */
static inline void ENET_UpdateRxDescriptorTail(ENET_Type *base, uint8_t channel, uint32_t rxDescTailAddrAlign)
{
    base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR = rxDescTailAddrAlign & ~ENET_ADDR_ALIGNMENT;
}

/*!
 * @brief Gets the context in the ENET Rx descriptor.
 *  This function is a low level functional API to get the
 *  the status flag from a given Rx descriptor.
 *
 * @param rxDesc  The given Rx descriptor.
 * @retval The RDES3 regions for write-back format Rx buffer descriptor.
 *
 * @note This must be called after all the ENET initilization.
 * And should be called when the ENET receive/transmit is required.
 */
static inline uint32_t ENET_GetRxDescriptor(enet_rx_bd_struct_t *rxDesc)
{
    assert(rxDesc);

    return rxDesc->rdes3;
}
/*!
 * @brief Updates the buffers and the own status for a given Rx descriptor.
 *  This function is a low level functional API to Updates the
 *  buffers and the own status for a given Rx descriptor.
 *
 * @param rxDesc  The given Rx descriptor.
 * @param buffer1  The first buffer address in the descriptor.
 * @param buffer2  The second buffer address in the descriptor.
 * @param intEnable Interrupt enable flag.
 * @param doubleBuffEnable The double buffer enable flag.
 *
 * @note This must be called after all the ENET initilization.
 * And should be called when the ENET receive/transmit is required.
 */
void ENET_UpdateRxDescriptor(
    enet_rx_bd_struct_t *rxDesc, void *buffer1, void *buffer2, bool intEnable, bool doubleBuffEnable);

/* @} */

/*!
 * @name Transactional operation
 * @{
 */

/*!
 * @brief Create ENET Handler
 *
 * This is a transactional API and it's provided to store all datas which are needed
 * during the whole transactional process. This API should not be used when you use
 * functional APIs to do data Tx/Rx. This is funtion will store many data/flag for
 * transactional use.
 *
 * @param base  ENET peripheral base address.
 * @param handle ENET handler.
 * @param config ENET configuration.
 * @param bufferConfig ENET buffer configuration.
 * @param callback The callback function.
 * @param userData The application data.
 */
void ENET_CreateHandler(ENET_Type *base,
                        enet_handle_t *handle,
                        enet_config_t *config,
                        enet_buffer_config_t *bufferConfig,
                        enet_callback_t callback,
                        void *userData);

/*!
 * @brief Gets the size of the read frame.
 * This function gets a received frame size from the ENET buffer descriptors.
 * @note The FCS of the frame is automatically removed by MAC and the size is the length without the FCS.
 * After calling ENET_GetRxFrameSize, ENET_ReadFrame() should be called to update the
 * receive buffers If the result is not "kStatus_ENET_RxFrameEmpty".
 *
 * @param base ENET peripheral base address.
 * @param handle The ENET handler structure. This is the same handler pointer used in the ENET_Init.
 * @param length The length of the valid frame received.
 * @param channel The DMAC channel for the Rx.
 * @retval kStatus_ENET_RxFrameEmpty No frame received. Should not call ENET_ReadFrame to read frame.
 * @retval kStatus_ENET_RxFrameError Data error happens. ENET_ReadFrame should be called with NULL data
 *         and NULL length to update the receive buffers.
 * @retval kStatus_Success Receive a frame Successfully then the ENET_ReadFrame
 *         should be called with the right data buffer and the captured data length input.
 */
status_t ENET_GetRxFrameSize(ENET_Type *base, enet_handle_t *handle, uint32_t *length, uint8_t channel);

/*!
 * @brief Reads a frame from the ENET device.
 * This function reads a frame from the ENET DMA descriptors.
 * The ENET_GetRxFrameSize should be used to get the size of the prepared data buffer.
 * For example use Rx dma channel 0:
 * @code
 *       uint32_t length;
 *       enet_handle_t g_handle;
 *       Comment: Get the received frame size firstly.
 *       status = ENET_GetRxFrameSize(&g_handle, &length, 0);
 *       if (length != 0)
 *       {
 *           Comment: Allocate memory here with the size of "length"
 *           uint8_t *data = memory allocate interface;
 *           if (!data)
 *           {
 *               ENET_ReadFrame(ENET, &g_handle, NULL, 0, 0);
 *           }
 *           else
 *           {
 *              status = ENET_ReadFrame(ENET, &g_handle, data, length, 0);
 *           }
 *       }
 *       else if (status == kStatus_ENET_RxFrameError)
 *       {
 *           Comment: Update the received buffer when a error frame is received.
 *           ENET_ReadFrame(ENET, &g_handle, NULL, 0, 0);
 *       }
 * @endcode
 * @param base  ENET peripheral base address.
 * @param handle The ENET handler structure. This is the same handler pointer used in the ENET_Init.
 * @param data The data buffer provided by user to store the frame which memory size should be at least "length".
 * @param length The size of the data buffer which is still the length of the received frame.
 * @param channel The Rx DMA channel. Shall not be larger than 2.
 * @param timestamp The timestamp address to store received timestamp.
 * @return The execute status, successful or failure.
 */
status_t ENET_ReadFrame(ENET_Type *base,
                        enet_handle_t *handle,
                        uint8_t *data,
                        uint32_t length,
                        uint8_t channel,
                        enet_ptp_time_t *timestamp);

/*!
 * @brief Receives one frame in specified BD ring with zero copy.
 *
 * This function will use the user-defined allocate and free callback. Every time application gets one frame through
 * this function, driver will allocate new buffers for the BDs whose buffers have been taken by application.
 * @note This function will drop current frame and update related BDs as available for DMA if new buffers allocating
 * fails. Application must provide a memory pool including at least BD number + 1 buffers(+2 if enable double buffer)
 * to make this function work normally.
 *
 * @param base   ENET peripheral base address.
 * @param handle The ENET handler pointer. This is the same handler pointer used in the ENET_Init.
 * @param rxFrame The received frame information structure provided by user.
 * @param channel The Rx DMA channel. Shall not be larger than 2.
 * @retval kStatus_Success  Succeed to get one frame and allocate new memory for Rx buffer.
 * @retval kStatus_ENET_RxFrameEmpty  There's no Rx frame in the BD.
 * @retval kStatus_ENET_RxFrameError  There's issue in this receiving. In this function, issue frame will be dropped.
 * @retval kStatus_ENET_RxFrameDrop  There's no new buffer memory for BD, dropped this frame.
 */
status_t ENET_GetRxFrame(ENET_Type *base, enet_handle_t *handle, enet_rx_frame_struct_t *rxFrame, uint8_t channel);

/*!
 * @brief Transmits an ENET frame.
 * @note The CRC is automatically appended to the data. Input the data
 * to send without the CRC. This API uses input buffer for Tx, application
 * should reclaim the buffer after Tx is over.
 *
 * @param base  ENET peripheral base address.
 * @param handle The ENET handler pointer. This is the same handler pointer used in the ENET_Init.
 * @param txFrame The Tx frame structure.
 * @param channel Channel to send the frame, same with queue index.
 * @retval kStatus_Success  Send frame succeed.
 * @retval kStatus_ENET_TxFrameBusy  Transmit buffer descriptor is busy under transmission.
 *         The transmit busy happens when the data send rate is over the MAC capacity.
 *         The waiting mechanism is recommended to be added after each call return with kStatus_ENET_TxFrameBusy.
 *         Also need to pay attention to reclaim Tx frame after Tx is over.
 * @retval kStatus_ENET_TxFrameOverLen  Transmit frme length exceeds the 0x3FFF limit defined by the driver.
 */
status_t ENET_SendFrame(ENET_Type *base, enet_handle_t *handle, enet_tx_frame_struct_t *txFrame, uint8_t channel);

/*!
 * @brief Reclaim Tx descriptors.
 *  This function is used to update the Tx descriptor status and
 *  store the Tx timestamp when the 1588 feature is enabled.
 *  This is called by the transmit interupt IRQ handler after the
 *  complete of a frame transmission.
 *
 * @param base    ENET peripheral base address.
 * @param handle The ENET handler pointer. This is the same handler pointer used in the ENET_Init.
 * @param channel  The Tx DMA channnel.
 *
 */
void ENET_ReclaimTxDescriptor(ENET_Type *base, enet_handle_t *handle, uint8_t channel);

/*!
 * @brief The ENET IRQ handler.
 *
 * @param base  ENET peripheral base address.
 * @param handle The ENET handler pointer.
 */
void ENET_IRQHandler(ENET_Type *base, enet_handle_t *handle);

/* @} */

#ifdef ENET_PTP1588FEATURE_REQUIRED
/*!
 * @name ENET Enhanced function operation
 * @{
 */

/*!
 * @brief Coreect the ENET PTP 1588 timer in coarse method.
 *
 * @param base  ENET peripheral base address.
 * @param operation The system time operation, refer to "enet_systime_op_t"
 * @param second The correction second.
 * @param nanosecond The correction nanosecond.
 */
void ENET_Ptp1588CorrectTimerInCoarse(ENET_Type *base,
                                      enet_systime_op_t operation,
                                      uint32_t second,
                                      uint32_t nanosecond);

/*!
 * @brief Coreect the ENET PTP 1588 timer in fine method.
 *
 *
 * @param base  ENET peripheral base address.
 * @param addend The addend value to be set in the fine method
 * @note Should take refer to the chapter "System time corretion" and
 * see the description for the "fine correction method".
 */
static inline void ENET_Ptp1588CorrectTimerInFine(ENET_Type *base, uint32_t addend)
{
    /* Set the freqCompensation value. */
    base->MAC_TIMESTAMP_ADDEND = addend;
    base->MAC_TIMESTAMP_CONTROL |= ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK;
}

/*!
 * @brief Get the ENET Time stamp current addend value.
 *
 * @param base  ENET peripheral base address.
 * @return The addend value.
 */
static inline uint32_t ENET_Ptp1588GetAddend(ENET_Type *base)
{
    return base->MAC_TIMESTAMP_ADDEND;
}

/*!
 * @brief Gets the current ENET time from the PTP 1588 timer.
 *       Interrupts are not disabled.
 *
 * @param base  ENET peripheral base address.
 * @param second The PTP 1588 system timer second.
 * @param nanosecond The PTP 1588 system timer nanosecond.
 */
void ENET_Ptp1588GetTimerNoIrqDisable(ENET_Type *base, uint64_t *second, uint32_t *nanosecond);

/*!
 * @brief Gets the current ENET time from the PTP 1588 timer.
 *
 * @param base  ENET peripheral base address.
 * @param second The PTP 1588 system timer second.
 * @param nanosecond The PTP 1588 system timer nanosecond.
 * For the unit of the nanosecond is 1ns. So the nanosecond is the real nanosecond.
 */
void ENET_Ptp1588GetTimer(ENET_Type *base, uint64_t *second, uint32_t *nanosecond);
#endif /* ENET_PTP1588FEATURE_REQUIRED */
/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_ENET_H_ */
