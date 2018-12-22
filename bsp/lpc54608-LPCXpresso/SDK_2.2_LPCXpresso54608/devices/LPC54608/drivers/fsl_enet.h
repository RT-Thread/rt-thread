/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _FSL_ENET_H_
#define _FSL_ENET_H_

#include "fsl_common.h"

/*!
 * @addtogroup lpc_enet
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Defines the driver version. */
#define FSL_ENET_DRIVER_VERSION (MAKE_VERSION(2, 0, 0)) /*!< Version 2.0.0. */
/*@}*/

/*! @name Control and status region bit masks of the receive buffer descriptor. */
/*@{*/
/*! @brief Defines for read format. */
#define ENET_RXDESCRIP_RD_BUFF1VALID_MASK (1U << 24) /*!< Buffer1 address valid. */
#define ENET_RXDESCRIP_RD_BUFF2VALID_MASK (1U << 25) /*!< Buffer2 address valid. */
#define ENET_RXDESCRIP_RD_IOC_MASK (1U << 30)        /*!< Interrupt enable on complete. */
#define ENET_RXDESCRIP_RD_OWN_MASK (1U << 31)        /*!< Own bit. */

/*! @brief Defines for write back format. */
#define ENET_RXDESCRIP_WR_ERR_MASK ((1U << 3) | (1U << 7))
#define ENET_RXDESCRIP_WR_PYLOAD_MASK (0x7U)
#define ENET_RXDESCRIP_WR_PTPMSGTYPE_MASK (0xF00U)
#define ENET_RXDESCRIP_WR_PTPTYPE_MASK (1U << 12)
#define ENET_RXDESCRIP_WR_PTPVERSION_MASK (1U << 13)
#define ENET_RXDESCRIP_WR_PTPTSA_MASK (1U << 14)
#define ENET_RXDESCRIP_WR_PACKETLEN_MASK (0x7FFFU)
#define ENET_RXDESCRIP_WR_ERRSUM_MASK (1U << 15)
#define ENET_RXDESCRIP_WR_TYPE_MASK (0x30000U)
#define ENET_RXDESCRIP_WR_DE_MASK (1U << 19)
#define ENET_RXDESCRIP_WR_RE_MASK (1U << 20)
#define ENET_RXDESCRIP_WR_OE_MASK (1U << 21)
#define ENET_RXDESCRIP_WR_RS0V_MASK (1U << 25)
#define ENET_RXDESCRIP_WR_RS1V_MASK (1U << 26)
#define ENET_RXDESCRIP_WR_RS2V_MASK (1U << 27)
#define ENET_RXDESCRIP_WR_LD_MASK (1U << 28)
#define ENET_RXDESCRIP_WR_FD_MASK (1U << 29)
#define ENET_RXDESCRIP_WR_CTXT_MASK (1U << 30)
#define ENET_RXDESCRIP_WR_OWN_MASK (1U << 31)
/*@}*/

/*! @name Control and status bit masks of the transmit buffer descriptor. */
/*@{*/
/*! @brief Defines for read format. */
#define ENET_TXDESCRIP_RD_BL1_MASK (0x3fffU)
#define ENET_TXDESCRIP_RD_BL2_MASK (ENET_TXDESCRIP_RD_BL1_MASK << 16)
#define ENET_TXDESCRIP_RD_BL1(n) ((uint32_t)(n) & ENET_TXDESCRIP_RD_BL1_MASK)
#define ENET_TXDESCRIP_RD_BL2(n) (((uint32_t)(n) & ENET_TXDESCRIP_RD_BL1_MASK) << 16)
#define ENET_TXDESCRIP_RD_TTSE_MASK (1U << 30)
#define ENET_TXDESCRIP_RD_IOC_MASK (1U << 31)

#define ENET_TXDESCRIP_RD_FL_MASK (0x7FFFU)
#define ENET_TXDESCRIP_RD_FL(n) ((uint32_t)(n) & ENET_TXDESCRIP_RD_FL_MASK)
#define ENET_TXDESCRIP_RD_CIC(n) (((uint32_t)(n) & 0x3) << 16)
#define ENET_TXDESCRIP_RD_TSE_MASK (1U << 18)
#define ENET_TXDESCRIP_RD_SLOT(n) (((uint32_t)(n) & 0x0f) << 19)
#define ENET_TXDESCRIP_RD_SAIC(n) (((uint32_t)(n) & 0x07) << 23)
#define ENET_TXDESCRIP_RD_CPC(n) (((uint32_t)(n) & 0x03) << 26)
#define ENET_TXDESCRIP_RD_LDFD(n) (((uint32_t)(n) & 0x03) << 28)
#define ENET_TXDESCRIP_RD_LD_MASK (1U << 28)
#define ENET_TXDESCRIP_RD_FD_MASK (1U << 29)
#define ENET_TXDESCRIP_RD_CTXT_MASK (1U << 30)
#define ENET_TXDESCRIP_RD_OWN_MASK (1UL << 31)

/*! @brief Defines for write back format. */
#define ENET_TXDESCRIP_WB_TTSS_MASK (1UL << 17)
/*@}*/

/*! @name Bit mask for interrupt enable type. */
/*@{*/
#define ENET_ABNORM_INT_MASK                                                      \
    (ENET_DMA_CH_DMA_CHX_INT_EN_TSE_MASK | ENET_DMA_CH_DMA_CHX_INT_EN_RBUE_MASK | \
     ENET_DMA_CH_DMA_CHX_INT_EN_RSE_MASK | ENET_DMA_CH_DMA_CHX_INT_EN_RWTE_MASK | \
     ENET_DMA_CH_DMA_CHX_INT_EN_FBEE_MASK | ENET_DMA_CH_DMA_CHX_INT_EN_ETIE_MASK)
#define ENET_NORM_INT_MASK                                                        \
    (ENET_DMA_CH_DMA_CHX_INT_EN_TIE_MASK | ENET_DMA_CH_DMA_CHX_INT_EN_TBUE_MASK | \
     ENET_DMA_CH_DMA_CHX_INT_EN_RIE_MASK | ENET_DMA_CH_DMA_CHX_INT_EN_ERIE_MASK)
/*@}*/

/*! @name Defines some Ethernet parameters. */
/*@{*/

#define ENET_FRAME_MAX_FRAMELEN (1518U)/*!< Default maximum Ethernet frame size. */
#define ENET_ADDR_ALIGNMENT (0x3U)     /*!< Recommended ethernet buffer alignment. */
#define ENET_BUFF_ALIGNMENT (4U)       /*!< Receive buffer alignment shall be 4bytes-aligned. */
#define ENET_RING_NUM_MAX (2U)         /*!< The Maximum number of tx/rx descriptor rings. */
#define ENET_MTL_RXFIFOSIZE (2048U)    /*!< The rx fifo size. */
#define ENET_MTL_TXFIFOSIZE (2048U)    /*!< The tx fifo size. */
#define ENET_MACINT_ENUM_OFFSET (16U)  /*!< The offest for mac interrupt in enum type. */
/*@}*/

#ifdef ENET_PTP1588FEATURE_REQUIRED
/* Define the buffer length to store the rx buffers address.
 * because the context descriptor will be updated for store the time
 * stamp for rx frame. so we need to reinit the descriptors.
 * This macro shall at least equal to the rxRingLen
 * assigned in the enet_buffer_config. That means if the rx descriptor
 * length is larger than 5, please increse this macro.  */
#define ENET_RXBUFFSTORE_NUM (6)
#endif /* ENET_PTP1588FEATURE_REQUIRED */

/*! @brief Defines the status return codes for transaction. */
enum _enet_status
{
    kStatus_ENET_RxFrameError = MAKE_STATUS(kStatusGroup_ENET, 0U),  /*!< A frame received but data error happen. */
    kStatus_ENET_RxFrameFail = MAKE_STATUS(kStatusGroup_ENET, 1U),   /*!< Failed to receive a frame. */
    kStatus_ENET_RxFrameEmpty = MAKE_STATUS(kStatusGroup_ENET, 2U),  /*!< No frame arrive. */
    kStatus_ENET_TxFrameBusy = MAKE_STATUS(kStatusGroup_ENET, 3U),   /*!< Transmit descriptors are under process. */
    kStatus_ENET_TxFrameFail = MAKE_STATUS(kStatusGroup_ENET, 4U),   /*!< Transmit frame fail. */
    kStatus_ENET_TxFrameOverLen = MAKE_STATUS(kStatusGroup_ENET, 5U) /*!< Transmit oversize. */
#ifdef ENET_PTP1588FEATURE_REQUIRED
    ,
    kStatus_ENET_PtpTsRingFull = MAKE_STATUS(kStatusGroup_ENET, 6U), /*!< Timestamp ring full. */
    kStatus_ENET_PtpTsRingEmpty = MAKE_STATUS(kStatusGroup_ENET, 7U) /*!< Timestamp ring empty. */
#endif                                                               /* ENET_PTP1588FEATURE_REQUIRED */
};

/*! @brief Defines the MII/RMII mode for data interface between the MAC and the PHY. */
typedef enum _enet_mii_mode {
    kENET_MiiMode = 0U, /*!< MII mode for data interface. */
    kENET_RmiiMode = 1U /*!< RMII mode for data interface. */
} enet_mii_mode_t;

/*! @brief Defines the 10/100 Mbps speed for the MII data interface. */
typedef enum _enet_mii_speed {
    kENET_MiiSpeed10M = 0U,  /*!< Speed 10 Mbps. */
    kENET_MiiSpeed100M = 1U, /*!< Speed 100 Mbps. */
} enet_mii_speed_t;

/*! @brief Defines the half or full duplex for the MII data interface. */
typedef enum _enet_mii_duplex {
    kENET_MiiHalfDuplex = 0U, /*!< Half duplex mode. */
    kENET_MiiFullDuplex       /*!< Full duplex mode. */
} enet_mii_duplex_t;

/*! @brief Define the MII opcode for normal MDIO_CLAUSES_22 Frame. */
typedef enum _enet_mii_normal_opcode {
    kENET_MiiWriteFrame = 1U, /*!< Write frame operation for a valid MII management frame. */
    kENET_MiiReadFrame = 3U   /*!< Read frame operation for a valid MII management frame. */
} enet_mii_normal_opcode;

/*! @brief Define the DMA maximum transmit burst length. */
typedef enum _enet_dma_burstlen {
    kENET_BurstLen1 = 0x00001U,   /*!< DMA burst length 1. */
    kENET_BurstLen2 = 0x00002U,   /*!< DMA burst length 2. */
    kENET_BurstLen4 = 0x00004U,   /*!< DMA burst length 4. */
    kENET_BurstLen8 = 0x00008U,   /*!< DMA burst length 8. */
    kENET_BurstLen16 = 0x00010U,  /*!< DMA burst length 16. */
    kENET_BurstLen32 = 0x00020U,  /*!< DMA burst length 32. */
    kENET_BurstLen64 = 0x10008U,  /*!< DMA burst length 64. eight times enabled. */
    kENET_BurstLen128 = 0x10010U, /*!< DMA burst length 128. eight times enabled. */
    kENET_BurstLen256 = 0x10020U, /*!< DMA burst length 256. eight times enabled. */
} enet_dma_burstlen;

/*! @brief Define the flag for the descriptor. */
typedef enum _enet_desc_flag {
    kENET_MiddleFlag = 0, /*!< It's a middle descriptor of the frame. */
    kENET_FirstFlagOnly,  /*!< It's the first descriptor of the frame. */
    kENET_LastFlagOnly,   /*!< It's the last descriptor of the frame. */
    kENET_FirstLastFlag   /*!< It's the first and last descriptor of the frame. */
} enet_desc_flag;

/*! @brief Define the system time adjust operation control. */
typedef enum _enet_systime_op {
    kENET_SystimeAdd = 0U,     /*!< System time add to. */
    kENET_SystimeSubtract = 1U /*!< System time subtract. */
} enet_systime_op;

/*! @brief Define the system time rollover control. */
typedef enum _enet_ts_rollover_type {
    kENET_BinaryRollover = 0, /*!< System time binary rollover.*/
    kENET_DigitalRollover = 1 /*!< System time digital rollover.*/
} enet_ts_rollover_type;

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
typedef enum _enet_special_config {

    /***********************DMA CONFGI**********************************************/
    kENET_DescDoubleBuffer = 0x0001U, /*!< The double buffer is used in the tx/rx descriptor. */
    /**************************MTL************************************/
    kENET_StoreAndForward = 0x0002U, /*!< The rx/tx store and forward enable. */
    /***********************MAC****************************************/
    kENET_PromiscuousEnable = 0x0004U,  /*!< The promiscuous enabled. */
    kENET_FlowControlEnable = 0x0008U,  /*!< The flow control enabled. */
    kENET_BroadCastRxDisable = 0x0010U, /*!< The broadcast disabled. */
    kENET_MulticastAllEnable = 0x0020U, /*!< All multicast are passed. */
    kENET_8023AS2KPacket = 0x0040U      /*!< 8023as support for 2K packets. */
} enet_special_config_t;

/*! @brief List of DMA interrupts supported by the ENET interrupt. This
 * enumeration uses one-bot encoding to allow a logical OR of multiple
 * members.
 */
typedef enum _enet_dma_interrupt_enable {
    kENET_DmaTx = ENET_DMA_CH_DMA_CHX_INT_EN_TIE_MASK,                 /*!< Tx interrupt. */
    kENET_DmaTxStop = ENET_DMA_CH_DMA_CHX_INT_EN_TSE_MASK,             /*!< Tx stop interrupt. */
    kENET_DmaTxBuffUnavail = ENET_DMA_CH_DMA_CHX_INT_EN_TBUE_MASK,     /*!< Tx buffer unavailable. */
    kENET_DmaRx = ENET_DMA_CH_DMA_CHX_INT_EN_RIE_MASK,                 /*!< Rx interrupt. */
    kENET_DmaRxBuffUnavail = ENET_DMA_CH_DMA_CHX_INT_EN_RBUE_MASK,     /*!< Rx buffer unavailable. */
    kENET_DmaRxStop = ENET_DMA_CH_DMA_CHX_INT_EN_RSE_MASK,             /*!< Rx stop. */
    kENET_DmaRxWatchdogTimeout = ENET_DMA_CH_DMA_CHX_INT_EN_RWTE_MASK, /*!< Rx watchdog timeout. */
    kENET_DmaEarlyTx = ENET_DMA_CH_DMA_CHX_INT_EN_ETIE_MASK,           /*!< Early transmit. */
    kENET_DmaEarlyRx = ENET_DMA_CH_DMA_CHX_INT_EN_ERIE_MASK,           /*!< Early receive. */
    kENET_DmaBusErr = ENET_DMA_CH_DMA_CHX_INT_EN_FBEE_MASK,            /*!< Fatal bus error. */
} enet_dma_interrupt_enable_t;

/*! @brief List of mac interrupts supported by the ENET interrupt. This
 * enumeration uses one-bot encoding to allow a logical OR of multiple
 * members.
 */
typedef enum _enet_mac_interrupt_enable {
    kENET_MacPmt = (ENET_MAC_INTR_EN_PMTIE_MASK << ENET_MACINT_ENUM_OFFSET),
    kENET_MacTimestamp = (ENET_MAC_INTR_EN_TSIE_MASK << ENET_MACINT_ENUM_OFFSET),
} enet_mac_interrupt_enable_t;

/*! @brief Defines the common interrupt event for callback use. */
typedef enum _enet_event {
    kENET_RxIntEvent,     /*!< Receive interrupt event. */
    kENET_TxIntEvent,     /*!< Transmit interrupt event. */
    kENET_WakeUpIntEvent, /*!< Wake up interrupt event. */
    kENET_TimeStampIntEvent, /*!< Time stamp interrupt event. */
} enet_event_t;

/*! @brief Define the DMA transmit arbitration for multi-queue. */
typedef enum _enet_dma_tx_sche {
    kENET_FixPri = 0,      /*!< Fixed priority. channel 0 has lower priority than channel 1. */
    kENET_WeightStrPri,    /*!< Weighted(burst length) strict priority. */
    kENET_WeightRoundRobin /*!< Weighted (weight factor) round robin. */
} enet_dma_tx_sche;

/*! @brief Define the MTL tx scheduling algorithm for multiple queues/rings. */
typedef enum _enet_mtl_multiqueue_txsche {
    kENET_txWeightRR = 0U, /*!< Tx weight round-robin. */
    kENET_txStrPrio = 3U,  /*!< Tx strict priority. */
} enet_mtl_multiqueue_txsche;

/*! @brief Define the MTL rx scheduling algorithm for multiple queues/rings. */
typedef enum _enet_mtl_multiqueue_rxsche {
    kENET_rxStrPrio = 0U,  /*!< Tx weight round-robin, rx strict priority. */
    kENET_rxWeightStrPrio, /*!< Tx strict priority, rx weight strict priority. */
} enet_mtl_multiqueue_rxsche;

/*! @brief Define the MTL rx queue and DMA channel mapping. */
typedef enum _enet_mtl_rxqueuemap {
    kENET_StaticDirctMap = 0x100U, /*!< The received fame in rx Qn(n = 0,1) direclty map to dma channel n. */
    kENET_DynamicMap =
        0x1010U, /*!< The received frame in rx Qn(n = 0,1) map to the dma channel m(m = 0,1) related with the same Mac.
                    */
} enet_mtl_rxqueuemap;

/*! @brief Defines the ENET PTP message related constant. */
typedef enum _enet_ptp_event_type {
    kENET_PtpEventMsgType = 3U,  /*!< PTP event message type. */
    kENET_PtpSrcPortIdLen = 10U, /*!< PTP message sequence id length. */
    kENET_PtpEventPort = 319U,   /*!< PTP event port number. */
    kENET_PtpGnrlPort = 320U     /*!< PTP general port number. */
} enet_ptp_event_type_t;

/*! @brief Defines the receive descriptor structure
 *  has the read-format and write-back format structure. They both
 *  has the same size with different region definition. so
 *  we define the read-format region as the recive descriptor structure
 *  Use the read-format region mask bits in the descriptor initialization
 *  Use the write-back format region mask bits in the receive data process.
 */
typedef struct _enet_rx_bd_struct
{
    __IO uint32_t buff1Addr; /*!< Buffer 1 address */
    __IO uint32_t reserved;  /*!< Reserved */
    __IO uint32_t buff2Addr; /*!< Buffer 2 or next descriptor address */
    __IO uint32_t control;   /*!< Buffer 1/2 byte counts and control */
} enet_rx_bd_struct_t;

/*! @brief Defines the transmit descriptor structure
 *  has the read-format and write-back format structure. They both
 *  has the same size with different region definition. so
 *  we define the read-format region as the transmit descriptor structure
 *  Use the read-format region mask bits in the descriptor initialization
 *  Use the write-back format region mask bits in the transmit data process.
 */
typedef struct _enet_tx_bd_struct
{
    __IO uint32_t buff1Addr;   /*!< Buffer 1 address */
    __IO uint32_t buff2Addr;   /*!< Buffer 2 address */
    __IO uint32_t buffLen;     /*!< Buffer 1/2 byte counts */
    __IO uint32_t controlStat; /*!< TDES control and status word */
} enet_tx_bd_struct_t;

#ifdef ENET_PTP1588FEATURE_REQUIRED
/*! @brief Defines the ENET PTP time stamp structure. */
typedef struct _enet_ptp_time
{
    uint64_t second;     /*!< Second. */
    uint32_t nanosecond; /*!< Nanosecond. */
} enet_ptp_time_t;

/*! @brief Defines the structure for the ENET PTP message data and timestamp data.*/
typedef struct _enet_ptp_time_data
{
    uint8_t version;                             /*!< PTP version. */
    uint8_t sourcePortId[kENET_PtpSrcPortIdLen]; /*!< PTP source port ID. */
    uint16_t sequenceId;                         /*!< PTP sequence ID. */
    uint8_t messageType;                         /*!< PTP message type. */
    enet_ptp_time_t timeStamp;                   /*!< PTP timestamp. */
} enet_ptp_time_data_t;

/*! @brief Defines the ENET PTP ring buffer structure for the PTP message timestamp store.*/
typedef struct _enet_ptp_time_data_ring
{
    uint32_t front;                  /*!< The first index of the ring. */
    uint32_t end;                    /*!< The end index of the ring. */
    uint32_t size;                   /*!< The size of the ring. */
    enet_ptp_time_data_t *ptpTsData; /*!< PTP message data structure. */
} enet_ptp_time_data_ring_t;

/*! @brief Defines the ENET PTP configuration structure. */
typedef struct _enet_ptp_config
{
    bool fineUpdateEnable;            /*!< Use the fine update. */
    bool ptp1588V2Enable;             /*!< ptp 1588 version 2 is used. */
    enet_ts_rollover_type tsRollover; /*!< 1588 time nanosecond rollover. */
} enet_ptp_config_t;
#endif /* ENET_PTP1588FEATURE_REQUIRED */

/*! @brief Defines the buffer descriptor configure structure.
 *
 * Notes:
 * 1. The receive and transmit descriptor start address pointer and tail pointer must be word-aligned.
 * 2. The recommended minimum tx/rx ring length is 4.
 * 3. The tx/rx descriptor tail address shall be the address pointer to the address just after the end
 *    of the last last descriptor. because only the descriptors between the start address and the
 *    tail address will be used by DMA.
 * 4. The decriptor address is the start address of all used contiguous memory.
 *    for example, the rxDescStartAddrAlign is the start address of rxRingLen contiguous descriptor memorise
 *    for rx descriptor ring 0.
 * 5. The "*rxBufferstartAddr" is the first element of  rxRingLen (2*rxRingLen for double buffers)
 *    rx buffers. It means the *rxBufferStartAddr is the rx buffer for the first descriptor
 *    the *rxBufferStartAddr + 1 is the rx buffer for the second descriptor or the rx buffer for
 *    the second buffer in the first descriptor. so please make sure the rxBufferStartAddr is the
 *    address of a rxRingLen or 2*rxRingLen array.
 */
typedef struct _enet_buffer_config
{
    uint8_t rxRingLen;                         /*!< The length of receive buffer descriptor ring. */
    uint8_t txRingLen;                         /*!< The length of transmit buffer descriptor ring. */
    enet_tx_bd_struct_t *txDescStartAddrAlign; /*!< Aligned transmit descriptor start address. */
    enet_tx_bd_struct_t *txDescTailAddrAlign;  /*!< Aligned transmit descriptor tail address. */
    enet_rx_bd_struct_t *rxDescStartAddrAlign; /*!< Aligned receive descriptor start address. */
    enet_rx_bd_struct_t *rxDescTailAddrAlign;  /*!< Aligned receive descriptor tail address. */
    uint32_t *rxBufferStartAddr;               /*!< Start address of the rx buffers. */
    uint32_t rxBuffSizeAlign;                  /*!< Aligned receive data buffer size. */
#ifdef ENET_PTP1588FEATURE_REQUIRED
    uint8_t ptpTsRxBuffNum;            /*!< Receive 1588 timestamp buffer number*/
    uint8_t ptpTsTxBuffNum;            /*!< Transmit 1588 timestamp buffer number*/
    enet_ptp_time_data_t *rxPtpTsData; /*!< The start address of 1588 receive timestamp buffers */
    enet_ptp_time_data_t *txPtpTsData; /*!< The start address of 1588 transmit timestamp buffers */
#endif                                 /* ENET_PTP1588FEATURE_REQUIRED */
} enet_buffer_config_t;

/*! @brief Defines the configuration when multi-queue is used. */
typedef struct enet_multiqueue_config
{
    /***********************DMA block*******************************/
    enet_dma_tx_sche dmaTxSche;                /*!< Transmit arbitation. */
    enet_dma_burstlen burstLen;                /*!< Burset len for the queue 1. */
    uint8_t txdmaChnWeight[ENET_RING_NUM_MAX]; /*!< Transmit channel weight. */
    /***********************MTL block*******************************/
    enet_mtl_multiqueue_txsche mtltxSche;    /*!< Transmit schedule for multi-queue. */
    enet_mtl_multiqueue_rxsche mtlrxSche;    /*!< Receive schedule for multi-queue. */
    uint8_t rxqueweight[ENET_RING_NUM_MAX];  /*!< Refer to the MTL RxQ Control register. */
    uint32_t txqueweight[ENET_RING_NUM_MAX]; /*!< Refer to the MTL TxQ Quantum Weight register. */
    uint8_t rxqueuePrio[ENET_RING_NUM_MAX];  /*!< Receive queue priority. */
    uint8_t txqueuePrio[ENET_RING_NUM_MAX];  /*!< Refer to Transmit Queue Priority Mapping register. */
    enet_mtl_rxqueuemap mtlrxQuemap;         /*!< Rx queue DMA Channel mapping. */
} enet_multiqueue_config_t;

/*! @brief Defines the basic configuration structure for the ENET device.
 *
 * Note:
 *  1. Default the signal queue is used so the "*multiqueueCfg" is set default
 *  with NULL. Set the pointer with a valid configration pointer if the multiple
 *  queues are required. If multiple queue is enabled, please make sure the
 *  buffer configuration for all are prepared also.
 */
typedef struct _enet_config
{
    uint16_t specialControl;                 /*!< The logicl or of enet_special_config_t */
    enet_multiqueue_config_t *multiqueueCfg; /*!< Use both tx/rx queue(dma channel) 0 and 1. */
    /* -----------------MAC block-------------------------------*/
    enet_mii_mode_t miiMode;     /*!< MII mode. */
    enet_mii_speed_t miiSpeed;   /*!< MII Speed. */
    enet_mii_duplex_t miiDuplex; /*!< MII duplex. */
    uint16_t pauseDuration; /*!< Used in the tx flow control frame, only valid when kENET_FlowControlEnable is set. */
/* -----------------Timestamp -------------------------------*/
#ifdef ENET_PTP1588FEATURE_REQUIRED
    enet_ptp_config_t *ptpConfig; /*!< PTP 1588 feature configuration */
#endif                            /* ENET_PTP1588FEATURE_REQUIRED */
} enet_config_t;

/* Forward declaration of the handle typedef. */
typedef struct _enet_handle enet_handle_t;

/*! @brief ENET callback function. */
typedef void (*enet_callback_t)(
    ENET_Type *base, enet_handle_t *handle, enet_event_t event, uint8_t channel, void *userData);

/*! @brief Defines the ENET transmit buffer descriptor ring/queue structure. */
typedef struct _enet_tx_bd_ring
{
    enet_tx_bd_struct_t *txBdBase; /*!< Buffer descriptor base address pointer. */
    uint16_t txGenIdx;             /*!< tx generate index. */
    uint16_t txConsumIdx;          /*!< tx consum index. */
    volatile uint16_t txDescUsed;  /*!< tx descriptor used number. */
    uint16_t txRingLen;            /*!< tx ring length. */
#ifdef ENET_PTP1588FEATURE_REQUIRED
    enet_ptp_time_data_ring_t txPtpTsDataRing; /*!< Transmit PTP 1588 time stamp data ring buffer. */
#endif                                         /* ENET_PTP1588FEATURE_REQUIRED */
} enet_tx_bd_ring_t;

/*! @brief Defines the ENET receive buffer descriptor ring/queue structure. */
typedef struct _enet_rx_bd_ring
{
    enet_rx_bd_struct_t *rxBdBase; /*!< Buffer descriptor base address pointer. */
    uint16_t rxGenIdx;             /*!< The current available receive buffer descriptor pointer. */
    uint16_t rxRingLen;            /*!< Receive ring length. */
    uint32_t rxBuffSizeAlign;      /*!< Receive buffer size. */
#ifdef ENET_PTP1588FEATURE_REQUIRED
    enet_ptp_time_data_ring_t rxPtpTsDataRing; /*!< Receive PTP 1588 time stamp data ring buffer. */
#endif                                         /* ENET_PTP1588FEATURE_REQUIRED*/
} enet_rx_bd_ring_t;

/*! @brief Defines the ENET handler structure. */
struct _enet_handle
{
    bool multiQueEnable;                           /*!< Enable multi-queue. */
    bool doubleBuffEnable;                         /*!< The double buffer is used in the descriptor. */
    bool rxintEnable;                              /*!< Rx interrup enabled. */
    enet_rx_bd_ring_t rxBdRing[ENET_RING_NUM_MAX]; /*!< Receive buffer descriptor.  */
    enet_tx_bd_ring_t txBdRing[ENET_RING_NUM_MAX]; /*!< Transmit buffer descriptor.  */
#ifdef ENET_PTP1588FEATURE_REQUIRED
    uint32_t rxbuffers[ENET_RXBUFFSTORE_NUM]; /*!< The Initi-rx buffers will be used for reInitialize. */
#endif
    enet_callback_t callback; /*!< Callback function. */
    void *userData;           /*!< Callback function parameter.*/
};

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
 *
 * @param base    ENET peripheral base address.
 * @param config  ENET mac configuration structure pointer.
 *        The "enet_config_t" type mac configuration return from ENET_GetDefaultConfig
 *        can be used directly. It is also possible to verify the Mac configuration using other methods.
 * @param macAddr  ENET mac address of Ethernet device. This MAC address should be
 *        provided.
 * @param refclkSrc_Hz ENET input reference clock.
 */
void ENET_Init(ENET_Type *base, const enet_config_t *config, uint8_t *macAddr, uint32_t refclkSrc_Hz);

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
 * @note This function is do all tx/rx descriptors initialization. Because this API 
 *  read all interrupt registers first and then set the interrupt flag for all descriptos, 
 * if the interrupt register is set. so the descriptor initialization should be called
 * after ENET_Init(), ENET_EnableInterrupts() and ENET_CreateHandle()(if transactional APIs
 * are used).
 *
 * @param base  ENET peripheral base address.
 * @param config The configuration for ENET.
 * @param bufferConfig All buffers configuration.
 */
status_t ENET_DescriptorInit(ENET_Type *base, enet_config_t *config, enet_buffer_config_t *bufferConfig);

/*!
 * @brief Starts the ENET rx/tx.
 *  This function enable the tx/rx and starts the rx/tx DMA.
 * This shall be set after ENET initialization and before
 * starting to receive the data.
 *
 * @param base  ENET peripheral base address.
 * @param rxRingNum  The number of the used rx rings. It shall not be
 * larger than the ENET_RING_NUM_MAX(2). If the ringNum is set with
 * 1, the ring 0 will be used.
 * @param txRingNum  The number of the used tx rings. It shall not be
 * larger than the ENET_RING_NUM_MAX(2). If the ringNum is set with
 * 1, the ring 0 will be used.
 *
 * @note This must be called after all the ENET initilization.
 * And should be called when the ENET receive/transmit is required.
 */
void ENET_StartRxTx(ENET_Type *base, uint8_t txRingNum, uint8_t rxRingNum);

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
    uint32_t reg = base->MAC_CONFIG & ~(ENET_MAC_CONFIG_DM_MASK | ENET_MAC_CONFIG_FES_MASK);
    reg |= ENET_MAC_CONFIG_DM(duplex) | ENET_MAC_CONFIG_FES(speed);

    base->MAC_CONFIG = reg;
}

/*!
 * @brief Sets the ENET SMI(serial management interface)- MII management interface.
 *
 * @param base  ENET peripheral base address.
 */
void ENET_SetSMI(ENET_Type *base);

/*!
 * @brief Checks if the SMI is busy.
 *
 * @param base  ENET peripheral base address.
 * @return The status of MII Busy status.
 */
static inline bool ENET_IsSMIBusy(ENET_Type *base)
{
    return (base->MAC_MDIO_ADDR & ENET_MAC_MDIO_ADDR_MB_MASK) ? true : false;
}

/*!
 * @brief Reads data from the PHY register through SMI interface.
 *
 * @param base  ENET peripheral base address.
 * @return The data read from PHY
 */
static inline uint16_t ENET_ReadSMIData(ENET_Type *base)
{
    return (uint16_t)(base->MAC_MDIO_DATA & ENET_MAC_MDIO_DATA_MD_MASK);
}

/*!
 * @brief Starts an SMI read command.
 * support both MDIO IEEE802.3 Clause 22 and clause 45.
 *
 * @param base  ENET peripheral base address.
 * @param phyAddr The PHY address.
 * @param phyReg The PHY register.
 */
void ENET_StartSMIRead(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg);

/*!
 * @brief Starts a SMI write command.
 * support both MDIO IEEE802.3 Clause 22 and clause 45.
 *
 * @param base  ENET peripheral base address.
 * @param phyAddr The PHY address.
 * @param phyReg The PHY register.
 * @param data The data written to PHY.
 */
void ENET_StartSMIWrite(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t data);
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
 */
static inline void ENET_SetMacAddr(ENET_Type *base, uint8_t *macAddr)
{
    assert(macAddr);

    /* Set Macaddr */
    base->MAC_ADDR_LOW = ((uint32_t)macAddr[3] << 24) | ((uint32_t)macAddr[2] << 16) | ((uint32_t)macAddr[1] << 8) |
                         ((uint32_t)macAddr[0]);
    base->MAC_ADDR_HIGH = ((uint32_t)macAddr[5] << 8) | ((uint32_t)macAddr[4]);
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
 * Eixt from the power down mode and recover to noraml work mode.
 *
 * @param base    ENET peripheral base address.
 */
static inline void ENET_ExitPowerDown(ENET_Type *base)
{
    /* Clear and status ans reset the power down. */
    base->MAC_PMT_CRTL_STAT &= ~ENET_MAC_PMT_CRTL_STAT_PWRDWN_MASK;

    /* Restore the tx which is disabled when enter power down mode. */
    base->DMA_CH[0].DMA_CHX_TX_CTRL |= ENET_DMA_CH_DMA_CHX_TX_CTRL_ST_MASK;
    base->DMA_CH[1].DMA_CHX_TX_CTRL |= ENET_DMA_CH_DMA_CHX_TX_CTRL_ST_MASK;
    base->MAC_CONFIG |= ENET_MAC_CONFIG_TE_MASK;
}

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
 * @return The event status of the interrupt source. This is the logical OR of members
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
    return base->MAC_INTR_STAT;
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
 * @brief Get the tx descriptor DMA Own flag.
 *
 * @param txDesc  The given tx descriptor.
 * @retval True the dma own tx descriptor, false application own tx descriptor.
 *
 */
static inline bool ENET_IsTxDescriptorDmaOwn(enet_tx_bd_struct_t *txDesc)
{
    return (txDesc->controlStat & ENET_TXDESCRIP_RD_OWN_MASK) ? true : false;
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
 * @param bytes1  The bytes in the second buffer.
 * @param framelen  The length of the frame to be transmitted.
 * @param intEnable Interrupt enable flag.
 * @param tsEnable The timestamp enable.
 * @param flag The flag of this tx desciriptor, see "enet_desc_flag" .
 * @param slotNum The slot num used for AV  only.
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
                            enet_desc_flag flag,
                            uint8_t slotNum);

/*!
 * @brief Update the tx descriptor tail pointer.
 *  This function is a low level functional API to update the
 *  the tx descriptor tail.
 *  This is called after you setup a new tx descriptor to update
 *  the tail pointer to make the new descritor accessable by DMA.
 *
 * @param base    ENET peripheral base address.
 * @param channel  The tx DMA channel.
 * @param txDescTailAddrAlign  The new tx tail pointer address.
 *
 */
static inline void ENET_UpdateTxDescriptorTail(ENET_Type *base, uint8_t channel, uint32_t txDescTailAddrAlign)
{
    base->DMA_CH[channel].DMA_CHX_TXDESC_TAIL_PTR = txDescTailAddrAlign & ~ENET_ADDR_ALIGNMENT;
}

/*!
 * @brief Update the rx descriptor tail pointer.
 *  This function is a low level functional API to update the
 *  the rx descriptor tail.
 *  This is called after you setup a new rx descriptor to update
 *  the tail pointer to make the new descritor accessable by DMA
 *  and to anouse the rx poll command for DMA.
 *
 * @param base    ENET peripheral base address.
 * @param channel  The rx DMA channel.
 * @param rxDescTailAddrAlign  The new rx tail pointer address.
 *
 */
static inline void ENET_UpdateRxDescriptorTail(ENET_Type *base, uint8_t channel, uint32_t rxDescTailAddrAlign)
{
    base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR = rxDescTailAddrAlign & ~ENET_ADDR_ALIGNMENT;
}

/*!
 * @brief Gets the context in the ENET rx descriptor.
 *  This function is a low level functional API to get the
 *  the status flag from a given rx descriptor.
 *
 * @param rxDesc  The given rx descriptor.
 * @retval The RDES3 regions for write-back format rx buffer descriptor.
 *
 * @note This must be called after all the ENET initilization.
 * And should be called when the ENET receive/transmit is required.
 */
static inline uint32_t ENET_GetRxDescriptor(enet_rx_bd_struct_t *rxDesc)
{
    assert(rxDesc);

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
 * functional APIs to do data tx/rx. This is funtion will store many data/flag for 
 * transactional use, so all configure API such as ENET_Init(), ENET_DescriptorInit(),
 * ENET_EnableInterrupts() etc.
 *
 * @note as our transactional transmit API use the zero-copy transmit buffer.
 * so there are two thing we emphasize here:
 *  1. tx buffer free/requeue for application should be done in the tx 
 *  interrupt handler. Please set callback: kENET_TxIntEvent with tx buffer free/requeue
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
* @param handle The ENET handler structure. This is the same handler pointer used in the ENET_Init.
* @param length The length of the valid frame received.
* @param channel The DMAC channel for the rx.
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
 * For example use rx dma channel 0:
 * @code
 *       uint32_t length;
 *       enet_handle_t g_handle;
 *       //Get the received frame size firstly.
 *       status = ENET_GetRxFrameSize(&g_handle, &length, 0);
 *       if (length != 0)
 *       {
 *           //Allocate memory here with the size of "length"
 *           uint8_t *data = memory allocate interface;
 *           if (!data)
 *           {
 *               ENET_ReadFrame(ENET, &g_handle, NULL, 0, 0);
 *               //Add the console warning log.
 *           }
 *           else
 *           {
 *              status = ENET_ReadFrame(ENET, &g_handle, data, length, 0);
 *              //Call stack input API to deliver the data to stack
 *           }
 *       }
 *       else if (status == kStatus_ENET_RxFrameError)
 *       {
 *          //Update the received buffer when a error frame is received.
 *           ENET_ReadFrame(ENET, &g_handle, NULL, 0, 0);
 *       }
 * @endcode
 * @param base  ENET peripheral base address.
 * @param handle The ENET handler structure. This is the same handler pointer used in the ENET_Init.
 * @param data The data buffer provided by user to store the frame which memory size should be at least "length".
 * @param length The size of the data buffer which is still the length of the received frame.
 * @param channel The rx DMA channel. shall not be larger than 2.
 * @return The execute status, successful or failure.
 */
status_t ENET_ReadFrame(ENET_Type *base, enet_handle_t *handle, uint8_t *data, uint32_t length, uint8_t channel);

/*!
 * @brief Transmits an ENET frame.
 * @note The CRC is automatically appended to the data. Input the data
 * to send without the CRC.
 *
 * @param base  ENET peripheral base address.
 * @param handle The ENET handler pointer. This is the same handler pointer used in the ENET_Init.
 * @param data The data buffer provided by user to be send.
 * @param length The length of the data to be send.
 * @retval kStatus_Success  Send frame succeed.
 * @retval kStatus_ENET_TxFrameBusy  Transmit buffer descriptor is busy under transmission.
 *         The transmit busy happens when the data send rate is over the MAC capacity.
 *         The waiting mechanism is recommended to be added after each call return with
 *         kStatus_ENET_TxFrameBusy.
 */
status_t ENET_SendFrame(ENET_Type *base, enet_handle_t *handle, uint8_t *data, uint32_t length);

/*!
 * @brief Reclaim tx descriptors.
 *  This function is used to update the tx descriptor status and
 *  store the tx timestamp when the 1588 feature is enabled.
 *  This is called by the transmit interupt IRQ handler after the
 *  complete of a frame transmission.
 *
 * @param base    ENET peripheral base address.
 * @param handle The ENET handler pointer. This is the same handler pointer used in the ENET_Init.
 * @param channel  The tx DMA channnel.
 *
 */
void ENET_ReclaimTxDescriptor(ENET_Type *base, enet_handle_t *handle, uint8_t channel);

/*!
 * @brief The ENET PMT IRQ handler.
 *
 * @param base  ENET peripheral base address.
 * @param handle The ENET handler pointer.
 */
void ENET_PMTIRQHandler(ENET_Type *base, enet_handle_t *handle);

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
 * @brief Starts the ENET PTP 1588 Timer.
 * This function is used to initialize the PTP timer. After the PTP starts,
 * the PTP timer starts running.
 *
 * @param base  ENET peripheral base address.
 * @param ptpClkSrc The clock source of the PTP timer.
 */
void ENET_Ptp1588StartTimer(ENET_Type *base, uint32_t ptpClkSrc);

/*!
 * @brief Coreect the ENET PTP 1588 timer in coarse method.
 *
 * @param base  ENET peripheral base address.
 * @param operation The system time operation, refer to "enet_systime_op"
 * @param second The correction second.
 * @param nanosecond The correction nanosecond.
 */
void ENET_Ptp1588CorrectTimerInCoarse(ENET_Type *base, enet_systime_op operation, uint32_t second, uint32_t nanosecond);

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
    base->MAC_SYS_TIMESTMP_ADDEND = addend;
    base->MAC_TIMESTAMP_CTRL |= ENET_MAC_TIMESTAMP_CTRL_TADDREG_MASK;
}

/*!
 * @brief Get the ENET Time stamp current addend value.
 *
 * @param base  ENET peripheral base address.
 * @return The addend value.
 */
static inline uint32_t ENET_Ptp1588GetAddend(ENET_Type *base)
{
    return base->MAC_SYS_TIMESTMP_ADDEND;
}

/*!
 * @brief Gets the current ENET time from the PTP 1588 timer.
 *
 * @param base  ENET peripheral base address.
 * @param second The PTP 1588 system timer second.
 * @param nanosecond The PTP 1588 system timer nanosecond.
 * For the unit of the nanosecond is 1ns. so the nanosecond is the real nanosecond.
 */
void ENET_Ptp1588GetTimer(ENET_Type *base, uint64_t *second, uint32_t *nanosecond);

/*!
 * @brief Gets the time stamp of the received frame.
 *
 * This function is used for PTP stack to get the timestamp captured by the ENET driver.
 *
 * @param handle The ENET handler pointer.This is the same state pointer used in
 *        ENET_Init.
 * @param ptpTimeData The special PTP timestamp data for search the receive timestamp.
 * @retval kStatus_Success Get 1588 timestamp success.
 * @retval kStatus_ENET_PtpTsRingEmpty 1588 timestamp ring empty.
 * @retval kStatus_ENET_PtpTsRingFull 1588 timestamp ring full.
 */
status_t ENET_GetRxFrameTime(enet_handle_t *handle, enet_ptp_time_data_t *ptpTimeData);

/*!
 * @brief Gets the time stamp of the transmit frame.
 *
 * This function is used for PTP stack to get the timestamp captured by the ENET driver.
 *
 * @param handle The ENET handler pointer.This is the same state pointer used in
 *        ENET_Init.
 * @param ptpTimeData The special PTP timestamp data for search the receive timestamp.
 * @retval kStatus_Success Get 1588 timestamp success.
 * @retval kStatus_ENET_PtpTsRingEmpty 1588 timestamp ring empty.
 * @retval kStatus_ENET_PtpTsRingFull 1588 timestamp ring full.
 */
status_t ENET_GetTxFrameTime(enet_handle_t *handle, enet_ptp_time_data_t *ptpTimeData);
#endif /* ENET_PTP1588FEATURE_REQUIRED */
/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_ENET_H_ */
