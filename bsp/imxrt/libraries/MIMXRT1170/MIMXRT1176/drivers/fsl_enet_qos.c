/*
 * Copyright 2019-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_enet_qos.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.enet_qos"
#endif

/*! @brief Defines 10^9 nanosecond. */
#define ENET_QOS_NANOSECS_ONESECOND (1000000000U)
/*! @brief Defines 10^6 microsecond.*/
#define ENET_QOS_MICRSECS_ONESECOND (1000000U)

/*! @brief Rx buffer LSB ignore bits. */
#define ENET_QOS_RXBUFF_IGNORELSB_BITS (3U)
/*! @brief ENET FIFO size unit. */
#define ENET_QOS_FIFOSIZE_UNIT (256U)
/*! @brief ENET half-dulpex default IPG. */
#define ENET_QOS_HALFDUPLEX_DEFAULTIPG (4U)
/*! @breif ENET miminum ring length. */
#define ENET_QOS_MIN_RINGLEN (4U)
/*! @breif ENET wakeup filter numbers. */
#define ENET_QOS_WAKEUPFILTER_NUM (8U)
/*! @breif Requried systime timer frequency. */
#define ENET_QOS_SYSTIME_REQUIRED_CLK_MHZ (50U)
/*! @brief Ethernet VLAN tag length. */
#define ENET_QOS_FRAME_VLAN_TAGLEN 4U

/*! @brief AVB TYPE */
#define ENET_QOS_AVBTYPE             0x22F0U
#define ENET_QOS_HEAD_TYPE_OFFSET    (12)
#define ENET_QOS_HEAD_AVBTYPE_OFFSET (16)

/*! @brief Defines the macro for converting constants from host byte order to network byte order. */
#define ENET_QOS_HTONS(n) __REV16(n)
#define ENET_QOS_HTONL(n) __REV(n)
#define ENET_QOS_NTOHS(n) __REV16(n)
#define ENET_QOS_NTOHL(n) __REV(n)

#define ENET_QOS_DMA_CHX_RX_CTRL_RBSZ
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*! @brief Mask the cache management code if cache control is disabled. */
#if !defined(FSL_ETH_ENABLE_CACHE_CONTROL)
#define ENET_QOS_DcacheInvalidateByRange(address, sizeByte)
#else
#define ENET_QOS_DcacheInvalidateByRange(address, sizeByte) DCACHE_InvalidateByRange(address, sizeByte)
#endif

/*!
 * @brief Increase the index in the ring.
 *
 * @param index The current index.
 * @param max The size.
 * @return the increased index.
 */
static uint16_t ENET_QOS_IncreaseIndex(uint16_t index, uint16_t max);

/*!
 * @brief Poll status flag.
 *
 * @param regAddr The register address to read out status
 * @param mask The mask to operate the register value.
 * @param readyStatus Indicate readyStatus for the field
 * @retval kStatus_Success Poll readyStatus Success.
 * @retval kStatus_ENET_QOS_Timeout Poll readyStatus timeout.
 */
static status_t ENET_QOS_PollStatusFlag(volatile uint32_t *regAddr, uint32_t mask, uint32_t readyStatus);

/*!
 * @brief Set ENET DMA controller with the configuration.
 *
 * @param base ENET peripheral base address.
 * @param config ENET Mac configuration.
 */
static void ENET_QOS_SetDMAControl(ENET_QOS_Type *base, const enet_qos_config_t *config);

/*!
 * @brief Set ENET MAC controller with the configuration.
 *
 * @param base ENET peripheral base address.
 * @param config ENET Mac configuration.
 * @param macAddr ENET six-byte mac address.
 */
static void ENET_QOS_SetMacControl(ENET_QOS_Type *base,
                                   const enet_qos_config_t *config,
                                   uint8_t *macAddr,
                                   uint8_t macCount);
/*!
 * @brief Set ENET MTL with the configuration.
 *
 * @param base ENET peripheral base address.
 * @param config ENET Mac configuration.
 */
static void ENET_QOS_SetMTL(ENET_QOS_Type *base, const enet_qos_config_t *config);

/*!
 * @brief Set ENET DMA transmit buffer descriptors for one channel.
 *
 * @param base ENET peripheral base address.
 * @param bufferConfig ENET buffer configuration.
 * @param intTxEnable tx interrupt enable.
 * @param channel The channel number, 0 , 1.
 */
static status_t ENET_QOS_TxDescriptorsInit(ENET_QOS_Type *base,
                                           const enet_qos_buffer_config_t *bufferConfig,
                                           bool intTxEnable,
                                           uint8_t channel);

/*!
 * @brief Set ENET DMA receive buffer descriptors for one channel.
 *
 * @param base ENET peripheral base address.
 * @param bufferConfig ENET buffer configuration.
 * @param intRxEnable tx interrupt enable.
 * @param channel The channel number, 0, 1.
 */
static status_t ENET_QOS_RxDescriptorsInit(ENET_QOS_Type *base,
                                           enet_qos_config_t *config,
                                           const enet_qos_buffer_config_t *bufferConfig,
                                           bool intRxEnable,
                                           uint8_t channel);

/*!
 * @brief Sets the ENET 1588 feature.
 *
 * Enable the enhacement 1588 buffer descriptor mode and start
 * the 1588 timer.
 *
 * @param base ENET peripheral base address.
 * @param config The ENET configuration.
 * @param refClk_Hz The reference clock for ptp 1588.
 */
static status_t ENET_QOS_SetPtp1588(ENET_QOS_Type *base, const enet_qos_config_t *config, uint32_t refClk_Hz);

/*!
 * @brief Store the receive time-stamp for event PTP frame in the time-stamp buffer ring.
 *
 * @param base   ENET peripheral base address.
 * @param handle ENET handler.
 * @param rxDesc The ENET receive descriptor pointer.
 * @param channel The rx channel.
 * @param ts The timestamp structure pointer.
 */
static void ENET_QOS_StoreRxFrameTime(ENET_QOS_Type *base,
                                      enet_qos_handle_t *handle,
                                      enet_qos_rx_bd_struct_t *rxDesc,
                                      //                                          uint8_t channel,
                                      enet_qos_ptp_time_t *ts);

/*!
 * @brief Check if txDirtyRing available.
 *
 * @param txDirtyRing pointer to txDirtyRing
 * @retval txDirty available status.
 */
static inline bool ENET_QOS_TxDirtyRingAvailable(enet_qos_tx_dirty_ring_t *txDirtyRing);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to enet bases for each instance. */
static ENET_QOS_Type *const s_enetqosBases[] = ENET_QOS_BASE_PTRS;

/*! @brief Pointers to enet IRQ number for each instance. */
static const IRQn_Type s_enetqosIrqId[] = ENET_QOS_IRQS;

/* ENET ISR for transactional APIs. */
static enet_qos_isr_t s_enetqosIsr;

/*! @brief Pointers to enet handles for each instance. */
static enet_qos_handle_t *s_ENETHandle[ARRAY_SIZE(s_enetqosBases)] = {NULL};

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to enet clocks for each instance. */
const clock_ip_name_t s_enetqosClock[ARRAY_SIZE(s_enetqosBases)] = ENETQOS_CLOCKS;
#endif /*  FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/

static status_t ENET_QOS_PollStatusFlag(volatile uint32_t *regAddr, uint32_t mask, uint32_t readyStatus)
{
    uint8_t retryTimes = 10U;
    status_t result    = kStatus_Success;

    while ((readyStatus != (*regAddr & mask)) && (0U != retryTimes))
    {
        retryTimes--;
        SDK_DelayAtLeastUs(1U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }

    if (retryTimes == 0U)
    {
        result = kStatus_ENET_QOS_Timeout;
    }

    return result;
}

/*!
 * brief Sets the ENET AVB feature.
 *
 * ENET_QOS AVB feature configuration, set transmit bandwidth.
 * This API is called when the AVB feature is required.
 *
 * param base ENET_QOS peripheral base address.
 * param config The ENET_QOS AVB feature configuration structure.
 * param queueIndex ENET_QOS queue index.
 */
void ENET_QOS_AVBConfigure(ENET_QOS_Type *base, const enet_qos_cbs_config_t *config, uint8_t queueIndex)
{
    assert(config != NULL);

    /* Enable AV algorithm */
    base->MTL_QUEUE[queueIndex].MTL_TXQX_ETS_CTRL |= ENET_QOS_MTL_TXQX_ETS_CTRL_AVALG_MASK;
    /* Configure send slope */
    base->MTL_QUEUE[queueIndex].MTL_TXQX_SNDSLP_CRDT = config->sendSlope;
    /* Configure idle slope (same register as tx weight) */
    base->MTL_QUEUE[queueIndex].MTL_TXQX_QNTM_WGHT = config->idleSlope;
    /* Configure high credit */
    base->MTL_QUEUE[queueIndex].MTL_TXQX_HI_CRDT = config->highCredit;
    /* Configure high credit */
    base->MTL_QUEUE[queueIndex].MTL_TXQX_LO_CRDT = config->lowCredit;
}

static uint16_t ENET_QOS_IncreaseIndex(uint16_t index, uint16_t max)
{
    /* Increase the index. */
    index++;
    if (index >= max)
    {
        index = 0;
    }
    return index;
}

static uint32_t ENET_QOS_ReverseBits(uint32_t value)
{
    value = ((value & 0x55555555UL) << 1U) | ((value >> 1U) & 0x55555555UL);
    value = ((value & 0x33333333UL) << 2U) | ((value >> 2U) & 0x33333333UL);
    value = ((value & 0x0F0F0F0FUL) << 4U) | ((value >> 4U) & 0x0F0F0F0FUL);

    return (value >> 24U) | ((value >> 8U) & 0xFF00UL) | ((value & 0xFF00UL) << 8U) | (value << 24U);
}

static void ENET_QOS_SetDMAControl(ENET_QOS_Type *base, const enet_qos_config_t *config)
{
    assert(config != NULL);

    uint8_t index;
    uint32_t reg;
    uint32_t burstLen;

    /* Reset first and wait for the complete
     * The reset bit will automatically be cleared after complete. */
    base->DMA_MODE |= ENET_QOS_DMA_MODE_SWR_MASK;
    while ((base->DMA_MODE & ENET_QOS_DMA_MODE_SWR_MASK) != 0U)
    {
    }

    /* Set the burst length. */
    for (index = 0; index < ENET_QOS_RING_NUM_MAX; index++)
    {
        burstLen = (uint32_t)kENET_QOS_BurstLen1;
        if (config->multiqueueCfg != NULL)
        {
            burstLen = (uint32_t)config->multiqueueCfg->burstLen;
        }
        base->DMA_CH[index].DMA_CHX_CTRL = burstLen & ENET_QOS_DMA_CHX_CTRL_PBLx8_MASK;

        reg = base->DMA_CH[index].DMA_CHX_TX_CTRL & ~ENET_QOS_DMA_CHX_TX_CTRL_TxPBL_MASK;
        base->DMA_CH[index].DMA_CHX_TX_CTRL = reg | ENET_QOS_DMA_CHX_TX_CTRL_TxPBL(burstLen & 0x3FU);

        reg = base->DMA_CH[index].DMA_CHX_RX_CTRL & ~ENET_QOS_DMA_CHX_RX_CTRL_RxPBL_MASK;
        base->DMA_CH[index].DMA_CHX_RX_CTRL = reg | ENET_QOS_DMA_CHX_RX_CTRL_RxPBL(burstLen & 0x3FU);
    }
}

static void ENET_QOS_SetMTL(ENET_QOS_Type *base, const enet_qos_config_t *config)
{
    assert(config != NULL);

    uint32_t txqOpreg                       = 0;
    uint32_t rxqOpReg                       = 0;
    enet_qos_multiqueue_config_t *multiqCfg = config->multiqueueCfg;
    uint8_t index;

    /* Set transmit operation mode. */
    if ((config->specialControl & (uint32_t)kENET_QOS_StoreAndForward) != 0U)
    {
        txqOpreg = ENET_QOS_MTL_TXQX_OP_MODE_TSF_MASK;
        rxqOpReg = ENET_QOS_MTL_RXQX_OP_MODE_RSF_MASK;
    }
    /* Set transmit operation mode. */
    txqOpreg |= ENET_QOS_MTL_TXQX_OP_MODE_FTQ_MASK;
    /* Set receive operation mode. */
    rxqOpReg |= ENET_QOS_MTL_RXQX_OP_MODE_FUP_MASK | ENET_QOS_MTL_RXQX_OP_MODE_RFD(3U) |
                ENET_QOS_MTL_RXQX_OP_MODE_RFA(1U) | ENET_QOS_MTL_RXQX_OP_MODE_EHFC_MASK;

    if (multiqCfg == NULL)
    {
        txqOpreg |=
            ENET_QOS_MTL_TXQX_OP_MODE_TQS(((uint32_t)ENET_QOS_MTL_TXFIFOSIZE / (uint32_t)ENET_QOS_FIFOSIZE_UNIT - 1U));
        rxqOpReg |=
            ENET_QOS_MTL_RXQX_OP_MODE_RQS(((uint32_t)ENET_QOS_MTL_RXFIFOSIZE / (uint32_t)ENET_QOS_FIFOSIZE_UNIT - 1U));
        base->MTL_QUEUE[0].MTL_TXQX_OP_MODE = txqOpreg | ENET_QOS_MTL_TXQX_OP_MODE_TXQEN((uint32_t)kENET_QOS_DCB_Mode);
        base->MTL_QUEUE[0].MTL_RXQX_OP_MODE = rxqOpReg;
    }
    else
    {
        /* Set the schedule/arbitration(set for multiple queues). */
        base->MTL_OPERATION_MODE = ENET_QOS_MTL_OPERATION_MODE_SCHALG(multiqCfg->mtltxSche) |
                                   ENET_QOS_MTL_OPERATION_MODE_RAA(multiqCfg->mtlrxSche);

        for (index = 0; index < multiqCfg->txQueueUse; index++)
        {
            txqOpreg |= ENET_QOS_MTL_TXQX_OP_MODE_TQS(
                ((uint32_t)ENET_QOS_MTL_TXFIFOSIZE / ((uint32_t)multiqCfg->txQueueUse * ENET_QOS_FIFOSIZE_UNIT)) - 1U);
            base->MTL_QUEUE[index].MTL_TXQX_OP_MODE =
                txqOpreg | ENET_QOS_MTL_TXQX_OP_MODE_TXQEN((uint32_t)multiqCfg->txQueueConfig[index].mode);
            if (multiqCfg->txQueueConfig[index].mode == kENET_QOS_AVB_Mode)
            {
                ENET_QOS_AVBConfigure(base, multiqCfg->txQueueConfig[index].cbsConfig, index);
            }
            else
            {
                base->MTL_QUEUE[index].MTL_TXQX_QNTM_WGHT = multiqCfg->txQueueConfig[index].weight;
            }
        }

        volatile uint32_t *mtlrxQuemapReg;
        uint8_t configIndex;
        for (index = 0; index < multiqCfg->rxQueueUse; index++)
        {
            rxqOpReg |= ENET_QOS_MTL_RXQX_OP_MODE_RQS(
                ((uint32_t)ENET_QOS_MTL_RXFIFOSIZE / ((uint32_t)multiqCfg->rxQueueUse * ENET_QOS_FIFOSIZE_UNIT)) - 1U);
            base->MTL_QUEUE[index].MTL_RXQX_OP_MODE = rxqOpReg;
            mtlrxQuemapReg                          = (index < 4U) ? &base->MTL_RXQ_DMA_MAP0 : &base->MTL_RXQ_DMA_MAP1;
            configIndex                             = (index & 0x3U);
            *mtlrxQuemapReg &= ~((uint32_t)ENET_QOS_MTL_RXQ_DMA_MAP0_Q0MDMACH_MASK << (8U * configIndex));
            *mtlrxQuemapReg |= (uint32_t)ENET_QOS_MTL_RXQ_DMA_MAP0_Q0MDMACH(multiqCfg->rxQueueConfig[index].mapChannel)
                               << (8U * configIndex);
        }
    }
}

static void ENET_QOS_SetMacControl(ENET_QOS_Type *base,
                                   const enet_qos_config_t *config,
                                   uint8_t *macAddr,
                                   uint8_t macCount)
{
    assert(config != NULL);

    uint32_t reg = 0;

    /* Set Macaddr */
    /* The dma channel 0 is set as to which the rx packet
     * whose DA matches the MAC address content is routed. */
    if (macAddr != NULL)
    {
        for (uint8_t i = 0; i < macCount; i++)
        {
            ENET_QOS_SetMacAddr(base, macAddr, i);
        }
    }

    /* Set the receive filter. */
    reg =
        ENET_QOS_MAC_PACKET_FILTER_PR(((config->specialControl & (uint32_t)kENET_QOS_PromiscuousEnable) != 0U) ? 1U :
                                                                                                                 0U) |
        ENET_QOS_MAC_PACKET_FILTER_DBF(((config->specialControl & (uint32_t)kENET_QOS_BroadCastRxDisable) != 0U) ? 1U :
                                                                                                                   0U) |
        ENET_QOS_MAC_PACKET_FILTER_PM(((config->specialControl & (uint32_t)kENET_QOS_MulticastAllEnable) != 0U) ? 1U :
                                                                                                                  0U) |
        ENET_QOS_MAC_PACKET_FILTER_HMC(((config->specialControl & (uint32_t)kENET_QOS_HashMulticastEnable) != 0U) ? 1U :
                                                                                                                    0U);
    base->MAC_PACKET_FILTER = reg;
    /* Flow control. */
    if ((config->specialControl & (uint32_t)kENET_QOS_FlowControlEnable) != 0U)
    {
        base->MAC_RX_FLOW_CTRL      = ENET_QOS_MAC_RX_FLOW_CTRL_RFE_MASK | ENET_QOS_MAC_RX_FLOW_CTRL_UP_MASK;
        base->MAC_TX_FLOW_CTRL_Q[0] = ENET_QOS_MAC_TX_FLOW_CTRL_Q_PT(config->pauseDuration);
    }

    /* Set the 1us ticket. */
    reg                         = config->csrClock_Hz / ENET_QOS_MICRSECS_ONESECOND - 1U;
    base->MAC_ONEUS_TIC_COUNTER = ENET_QOS_MAC_ONEUS_TIC_COUNTER_TIC_1US_CNTR(reg);

    /* Set the speed and duplex. */
    reg = ENET_QOS_MAC_CONFIGURATION_DM(config->miiDuplex) | (uint32_t)config->miiSpeed |
          ENET_QOS_MAC_CONFIGURATION_S2KP(((config->specialControl & (uint32_t)kENET_QOS_8023AS2KPacket) != 0U) ? 1U :
                                                                                                                  0U);
    if (config->miiDuplex == kENET_QOS_MiiHalfDuplex)
    {
        reg |= ENET_QOS_MAC_CONFIGURATION_IPG(ENET_QOS_HALFDUPLEX_DEFAULTIPG);
    }
    base->MAC_CONFIGURATION = reg;

    if (config->multiqueueCfg != NULL)
    {
        reg = 0U;
        uint8_t configIndex;
        enet_qos_multiqueue_config_t *multiqCfg = config->multiqueueCfg;
        uint32_t txQueuePrioMap0                = base->MAC_TXQ_PRTY_MAP0;
        uint32_t txQueuePrioMap1                = base->MAC_TXQ_PRTY_MAP1;
        uint32_t rxQueuePrioMap0                = base->MAC_RXQ_CTRL[2];
        uint32_t rxQueuePrioMap1                = base->MAC_RXQ_CTRL[3];
        uint32_t rxCtrlReg1                     = base->MAC_RXQ_CTRL[1];

        for (uint8_t index = 0U; index < multiqCfg->txQueueUse; index++)
        {
            configIndex = index & 0x3U;

            /* Configure tx queue priority. */
            if (index < 4U)
            {
                txQueuePrioMap0 &= ~((uint32_t)ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ0_MASK << (8U * configIndex));
                txQueuePrioMap0 |= (uint32_t)ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ0(multiqCfg->txQueueConfig[index].priority)
                                   << (8U * configIndex);
            }
            else
            {
                txQueuePrioMap1 &= ~((uint32_t)ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ0_MASK << (8U * configIndex));
                txQueuePrioMap1 |= (uint32_t)ENET_QOS_MAC_TXQ_PRTY_MAP0_PSTQ0(multiqCfg->txQueueConfig[index].priority)
                                   << (8U * configIndex);
            }
        }

        for (uint8_t index = 0U; index < multiqCfg->rxQueueUse; index++)
        {
            configIndex = index & 0x3U;

            /* Configure rx queue priority. */
            if (index < 4U)
            {
                rxQueuePrioMap0 &= ~((uint32_t)ENET_QOS_MAC_RXQ_CTRL_PSRQ0_MASK << (8U * configIndex));
                rxQueuePrioMap0 |= (uint32_t)ENET_QOS_MAC_RXQ_CTRL_PSRQ0(multiqCfg->rxQueueConfig[index].priority)
                                   << (8U * configIndex);
            }
            else
            {
                rxQueuePrioMap1 &= ~((uint32_t)ENET_QOS_MAC_RXQ_CTRL_PSRQ0_MASK << (8U * configIndex));
                rxQueuePrioMap1 |= (uint32_t)ENET_QOS_MAC_RXQ_CTRL_PSRQ0(multiqCfg->rxQueueConfig[index].priority)
                                   << (8U * configIndex);
            }

            /* Configure queue enable mode. */
            reg |= ENET_QOS_MAC_RXQ_CTRL_RXQ0EN((uint32_t)multiqCfg->rxQueueConfig[index].mode) << (2U * index);

            /* Configure rx queue routing */
            if (((uint8_t)multiqCfg->rxQueueConfig[index].packetRoute & (uint8_t)kENET_QOS_PacketAVCPQ) != 0U)
            {
                rxCtrlReg1 &= ~ENET_QOS_MAC_RXQ_CTRL_AVCPQ_MASK;
                rxCtrlReg1 |= (ENET_QOS_MAC_RXQ_CTRL_AVCPQ(index) | ENET_QOS_MAC_RXQ_CTRL_TACPQE_MASK);
            }

            if (((uint8_t)multiqCfg->rxQueueConfig[index].packetRoute & (uint8_t)kENET_QOS_PacketPTPQ) != 0U)
            {
                rxCtrlReg1 &= ~ENET_QOS_MAC_RXQ_CTRL_PTPQ_MASK;
                rxCtrlReg1 |= ENET_QOS_MAC_RXQ_CTRL_PTPQ(index);
            }

            if (((uint8_t)multiqCfg->rxQueueConfig[index].packetRoute & (uint8_t)kENET_QOS_PacketDCBCPQ) != 0U)
            {
                rxCtrlReg1 &= ~ENET_QOS_MAC_RXQ_CTRL_DCBCPQ_MASK;
                rxCtrlReg1 |= ENET_QOS_MAC_RXQ_CTRL_DCBCPQ(index);
            }

            if (((uint8_t)multiqCfg->rxQueueConfig[index].packetRoute & (uint8_t)kENET_QOS_PacketUPQ) != 0U)
            {
                rxCtrlReg1 &= ~ENET_QOS_MAC_RXQ_CTRL_UPQ_MASK;
                rxCtrlReg1 |= ENET_QOS_MAC_RXQ_CTRL_UPQ(index);
            }

            if (((uint8_t)multiqCfg->rxQueueConfig[index].packetRoute & (uint8_t)kENET_QOS_PacketMCBCQ) != 0U)
            {
                rxCtrlReg1 &= ~ENET_QOS_MAC_RXQ_CTRL_MCBCQ_MASK;
                rxCtrlReg1 |= (ENET_QOS_MAC_RXQ_CTRL_MCBCQ(index) | ENET_QOS_MAC_RXQ_CTRL_MCBCQEN_MASK);
            }
        }

        base->MAC_TXQ_PRTY_MAP0 = txQueuePrioMap0;
        base->MAC_TXQ_PRTY_MAP1 = txQueuePrioMap1;
        base->MAC_RXQ_CTRL[2]   = rxQueuePrioMap0;
        base->MAC_RXQ_CTRL[3]   = rxQueuePrioMap1;
        base->MAC_RXQ_CTRL[1]   = rxCtrlReg1;
    }
    else
    {
        /* Configure queue enable mode. */
        reg = ENET_QOS_MAC_RXQ_CTRL_RXQ0EN((uint32_t)kENET_QOS_DCB_Mode);
    }

    /* Enable queue. */
    base->MAC_RXQ_CTRL[0] = reg;

    /* Mask MMC counters interrupts as we don't handle
     * them in the interrupt handler.
     */
    base->MAC_MMC_RX_INTERRUPT_MASK     = 0xFFFFFFFFU;
    base->MAC_MMC_TX_INTERRUPT_MASK     = 0xFFFFFFFFU;
    base->MAC_MMC_IPC_RX_INTERRUPT_MASK = 0xFFFFFFFFU;
    base->MAC_MMC_FPE_RX_INTERRUPT_MASK = 0xFFFFFFFFU;
    base->MAC_MMC_FPE_TX_INTERRUPT_MASK = 0xFFFFFFFFU;
}

static status_t ENET_QOS_TxDescriptorsInit(ENET_QOS_Type *base,
                                           const enet_qos_buffer_config_t *bufferConfig,
                                           bool intTxEnable,
                                           uint8_t channel)
{
    uint16_t j;
    enet_qos_tx_bd_struct_t *txbdPtr;
    uint32_t control                        = intTxEnable ? ENET_QOS_TXDESCRIP_RD_IOC_MASK : 0U;
    const enet_qos_buffer_config_t *buffCfg = bufferConfig;
    uint32_t txDescAddr, txDescTail;

    if (buffCfg == NULL)
    {
        return kStatus_InvalidArgument;
    }

    /* Check the ring length. */
    if (buffCfg->txRingLen < ENET_QOS_MIN_RINGLEN)
    {
        return kStatus_InvalidArgument;
    }
    /* Set the tx descriptor start/tail pointer, shall be word aligned. */
    txDescAddr = (uint32_t)(uintptr_t)buffCfg->txDescStartAddrAlign & ENET_QOS_DMA_CHX_TXDESC_LIST_ADDR_TDESLA_MASK;
    txDescTail = (uint32_t)(uintptr_t)buffCfg->txDescTailAddrAlign & ENET_QOS_DMA_CHX_TXDESC_TAIL_PTR_TDTP_MASK;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    txDescAddr = MEMORY_ConvertMemoryMapAddress(txDescAddr, kMEMORY_Local2DMA);
    txDescTail = MEMORY_ConvertMemoryMapAddress(txDescTail, kMEMORY_Local2DMA);
#endif
    base->DMA_CH[channel].DMA_CHX_TXDESC_LIST_ADDR = txDescAddr;
    base->DMA_CH[channel].DMA_CHX_TXDESC_TAIL_PTR  = txDescTail;
    /* Set the tx ring length. */
    base->DMA_CH[channel].DMA_CHX_TXDESC_RING_LENGTH =
        ((uint32_t)buffCfg->txRingLen - 1U) & ENET_QOS_DMA_CHX_TXDESC_RING_LENGTH_TDRL_MASK;

    /* Init the txbdPtr to the transmit descriptor start address. */
    txbdPtr = (enet_qos_tx_bd_struct_t *)(buffCfg->txDescStartAddrAlign);
    for (j = 0; j < buffCfg->txRingLen; j++)
    {
        txbdPtr->buff1Addr   = 0;
        txbdPtr->buff2Addr   = 0;
        txbdPtr->buffLen     = control;
        txbdPtr->controlStat = 0;
        txbdPtr++;
    }

    return kStatus_Success;
}

static status_t ENET_QOS_RxDescriptorsInit(ENET_QOS_Type *base,
                                           enet_qos_config_t *config,
                                           const enet_qos_buffer_config_t *bufferConfig,
                                           bool intRxEnable,
                                           uint8_t channel)
{
    uint16_t j;
    uint32_t reg;
    enet_qos_rx_bd_struct_t *rxbdPtr;
    uint16_t index;
    bool doubleBuffEnable = ((config->specialControl & (uint32_t)kENET_QOS_DescDoubleBuffer) != 0U) ? true : false;
    const enet_qos_buffer_config_t *buffCfg = bufferConfig;
    uint32_t control                        = ENET_QOS_RXDESCRIP_RD_BUFF1VALID_MASK;
    uint32_t rxDescAddr, rxDescTail;

    if (buffCfg == NULL)
    {
        return kStatus_InvalidArgument;
    }

    if (intRxEnable)
    {
        control |= ENET_QOS_RXDESCRIP_RD_IOC_MASK;
    }

    if (doubleBuffEnable)
    {
        control |= ENET_QOS_RXDESCRIP_RD_BUFF2VALID_MASK;
    }

    /* Not give ownership to DMA before Rx buffer is ready */
    if ((config->rxBuffAlloc == NULL) || (config->rxBuffFree == NULL))
    {
        control |= ENET_QOS_RXDESCRIP_WR_OWN_MASK;
    }

    /* Check the ring length. */
    if (buffCfg->rxRingLen < ENET_QOS_MIN_RINGLEN)
    {
        return kStatus_InvalidArgument;
    }

    /* Set the rx descriptor start/tail pointer, shall be word aligned. */
    rxDescAddr = (uint32_t)(uintptr_t)buffCfg->rxDescStartAddrAlign & ENET_QOS_DMA_CHX_RXDESC_LIST_ADDR_RDESLA_MASK;
    rxDescTail = (uint32_t)(uintptr_t)buffCfg->rxDescTailAddrAlign & ENET_QOS_DMA_CHX_RXDESC_TAIL_PTR_RDTP_MASK;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    rxDescAddr = MEMORY_ConvertMemoryMapAddress(rxDescAddr, kMEMORY_Local2DMA);
    rxDescTail = MEMORY_ConvertMemoryMapAddress(rxDescTail, kMEMORY_Local2DMA);
#endif
    base->DMA_CH[channel].DMA_CHX_RXDESC_LIST_ADDR = rxDescAddr;
    base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR  = rxDescTail;
    /* Register DMA_CHX_RXDESC_RING_LENGTH renamed to DMA_CHX_RX_CONTROL2 */
#if defined(ENET_QOS_DMA_CHX_RX_CONTROL2_COUNT) && ENET_QOS_DMA_CHX_RX_CONTROL2_COUNT
    base->DMA_CH[channel].DMA_CHX_RX_CONTROL2 =
        ((uint32_t)buffCfg->rxRingLen - 1U) & ENET_QOS_DMA_CHX_RX_CONTROL2_RDRL_MASK;
#else
    base->DMA_CH[channel].DMA_CHX_RXDESC_RING_LENGTH =
        ((uint32_t)buffCfg->rxRingLen - 1U) & ENET_QOS_DMA_CHX_RXDESC_RING_LENGTH_RDRL_MASK;
#endif
    reg = base->DMA_CH[channel].DMA_CHX_RX_CTRL & ~ENET_QOS_DMA_CHX_RX_CTRL_RBSZ_13_y_MASK;
    reg |= ENET_QOS_DMA_CHX_RX_CTRL_RBSZ_13_y(buffCfg->rxBuffSizeAlign >> ENET_QOS_RXBUFF_IGNORELSB_BITS);
    base->DMA_CH[channel].DMA_CHX_RX_CTRL = reg;

    /* Init the rxbdPtr to the receive descriptor start address. */
    rxbdPtr = (enet_qos_rx_bd_struct_t *)(buffCfg->rxDescStartAddrAlign);
    for (j = 0U; j < buffCfg->rxRingLen; j++)
    {
        if ((config->rxBuffAlloc == NULL) || (config->rxBuffFree == NULL))
        {
            if (doubleBuffEnable)
            {
                index = 2U * j;
            }
            else
            {
                index = j;
            }

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            buffCfg->rxBufferStartAddr[index] =
                MEMORY_ConvertMemoryMapAddress((uintptr_t)buffCfg->rxBufferStartAddr[index], kMEMORY_Local2DMA);
#endif
            rxbdPtr->buff1Addr = buffCfg->rxBufferStartAddr[index];

            /* The second buffer is set with 0 because it is not required for normal case. */
            if (doubleBuffEnable)
            {
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                buffCfg->rxBufferStartAddr[index + 1U] = MEMORY_ConvertMemoryMapAddress(
                    (uintptr_t)buffCfg->rxBufferStartAddr[index + 1U], kMEMORY_Local2DMA);
#endif
                rxbdPtr->buff2Addr = buffCfg->rxBufferStartAddr[index + 1U];
            }
            else
            {
                rxbdPtr->buff2Addr = 0;
            }
        }

        /* Set the valid and DMA own flag.*/
        rxbdPtr->control = control;
        rxbdPtr++;
    }

    return kStatus_Success;
}

static status_t ENET_QOS_SetPtp1588(ENET_QOS_Type *base, const enet_qos_config_t *config, uint32_t refClk_Hz)
{
    assert(config != NULL);
    assert(config->ptpConfig != NULL);
    assert(refClk_Hz != 0U);

    uint32_t control                 = 0U;
    status_t result                  = kStatus_Success;
    enet_qos_ptp_config_t *ptpConfig = config->ptpConfig;
    uint32_t ptpClk_Hz               = refClk_Hz;
    uint32_t ssInc, snsSinc;

    /* Clear the timestamp interrupt first. */
    base->MAC_INTERRUPT_ENABLE &= ~ENET_QOS_MAC_INTERRUPT_ENABLE_TSIE_MASK;

    if (ptpConfig->fineUpdateEnable)
    {
        control |= ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCFUPDT_MASK;
        ptpClk_Hz = ptpConfig->systemTimeClock_Hz; /* PTP clock 50MHz. */
    }

    /* Enable the IEEE 1588 timestamping and snapshot for event message. */
    control |= ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENA_MASK | ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPV4ENA_MASK |
               ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPV6ENA_MASK | ENET_QOS_MAC_TIMESTAMP_CONTROL_TSENALL_MASK |
               ENET_QOS_MAC_TIMESTAMP_CONTROL_TSEVNTENA_MASK | ENET_QOS_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL_MASK |
               ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCTRLSSR(ptpConfig->tsRollover);

    if (ptpConfig->ptp1588V2Enable)
    {
        control |= ENET_QOS_MAC_TIMESTAMP_CONTROL_TSVER2ENA_MASK | ENET_QOS_MAC_TIMESTAMP_CONTROL_TSIPENA_MASK;
    }

    /* Initialize the sub-second increment register. */
    if (ptpConfig->tsRollover == kENET_QOS_DigitalRollover)
    {
        ssInc = (uint32_t)(((uint64_t)ENET_QOS_NANOSECS_ONESECOND << 8U) / ptpClk_Hz);
    }
    else
    {
        ssInc = (uint32_t)((((uint64_t)ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_TSSS_MASK + 1U) << 8U) / ptpClk_Hz);
    }

    snsSinc = ssInc & 0xFFU;
    ssInc   = (ssInc >> 8U) & 0xFFU;

    base->MAC_TIMESTAMP_CONTROL = control;

    /* Initialize the system timer. */
    base->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE = 0;

    /* Set the second.*/
    base->MAC_SYSTEM_TIME_SECONDS_UPDATE      = 0;
    base->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS = 0;

    /* Initialize the system timer. */
    base->MAC_TIMESTAMP_CONTROL |= ENET_QOS_MAC_TIMESTAMP_CONTROL_TSINIT_MASK;

    while ((base->MAC_TIMESTAMP_CONTROL & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSINIT_MASK) != 0U)
    {
    }

    base->MAC_SUB_SECOND_INCREMENT =
        ENET_QOS_MAC_SUB_SECOND_INCREMENT_SSINC(ssInc) | ENET_QOS_MAC_SUB_SECOND_INCREMENT_SNSINC(snsSinc);

    /* Set the initial added value for the fine update. */
    if (ptpConfig->fineUpdateEnable)
    {
        result = ENET_QOS_Ptp1588CorrectTimerInFine(base, ptpConfig->defaultAddend);
    }

    return result;
}

static inline bool ENET_QOS_TxDirtyRingAvailable(enet_qos_tx_dirty_ring_t *txDirtyRing)
{
    return !txDirtyRing->isFull;
}

static void ENET_QOS_StoreRxFrameTime(ENET_QOS_Type *base,
                                      enet_qos_handle_t *handle,
                                      enet_qos_rx_bd_struct_t *rxDesc,
                                      enet_qos_ptp_time_t *ts)
{
    assert(ts != NULL);

    uint32_t nanosecond;

    /* Get transmit time stamp second. */
    nanosecond = rxDesc->buff1Addr;
    if ((base->MAC_TIMESTAMP_CONTROL & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_MASK) == 0U)
    {
        /* Binary rollover, 0.465ns accuracy. */
        nanosecond = (uint32_t)(((uint64_t)nanosecond * 465U) / 1000U);
    }
    ts->second     = rxDesc->reserved;
    ts->nanosecond = nanosecond;
}

uint32_t ENET_QOS_GetInstance(ENET_QOS_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_enetqosBases); instance++)
    {
        if (s_enetqosBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_enetqosBases));

    return instance;
}

/*!
 * brief Gets the ENET default configuration structure.
 *
 * The purpose of this API is to get the default ENET configure
 * structure for ENET_QOS_Init(). User may use the initialized
 * structure unchanged in ENET_QOS_Init(), or modify some fields of the
 * structure before calling ENET_QOS_Init().
 * Example:
   code
   enet_qos_config_t config;
   ENET_QOS_GetDefaultConfig(&config);
   endcode
 * param config The ENET mac controller configuration structure pointer.
 */
void ENET_QOS_GetDefaultConfig(enet_qos_config_t *config)
{
    /* Checks input parameter. */
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Sets RGMII mode, full duplex, 1000Mbps for MAC and PHY data interface. */
    config->miiMode   = kENET_QOS_RgmiiMode;
    config->miiSpeed  = kENET_QOS_MiiSpeed1000M;
    config->miiDuplex = kENET_QOS_MiiFullDuplex;

    /* Sets default configuration for other options. */
    config->specialControl = 0;
    config->multiqueueCfg  = NULL;
    config->pauseDuration  = 0;

    config->ptpConfig = NULL;
}

/*!
 * brief Initializes the ENET module.
 *
 * This function set up the with ENET basic configuration.
 *
 * param base    ENET peripheral base address.
 * param config  ENET mac configuration structure pointer.
 *        The "enet_qos_config_t" type mac configuration return from ENET_QOS_GetDefaultConfig
 *        can be used directly. It is also possible to verify the Mac configuration using other methods.
 * param macAddr  ENET mac address of Ethernet device. This MAC address should be
 *        provided.
 * param refclkSrc_Hz ENET input reference clock.
 */
status_t ENET_QOS_Up(
    ENET_QOS_Type *base, const enet_qos_config_t *config, uint8_t *macAddr, uint8_t macCount, uint32_t refclkSrc_Hz)
{
    assert(config != NULL);
    status_t result = kStatus_Success;

    /* Initializes the ENET MTL with basic function. */
    ENET_QOS_SetMTL(base, config);

    /* Initializes the ENET MAC with basic function. */
    ENET_QOS_SetMacControl(base, config, macAddr, macCount);

    return result;
}

/*!
 * brief Initializes the ENET module.
 *
 * This function ungates the module clock and initializes it with the ENET basic
 * configuration.
 *
 * param base    ENET peripheral base address.
 * param config  ENET mac configuration structure pointer.
 *        The "enet_qos_config_t" type mac configuration return from ENET_QOS_GetDefaultConfig
 *        can be used directly. It is also possible to verify the Mac configuration using other methods.
 * param macAddr  ENET mac address of Ethernet device. This MAC address should be
 *        provided.
 * param refclkSrc_Hz ENET input reference clock.
 */
status_t ENET_QOS_Init(
    ENET_QOS_Type *base, const enet_qos_config_t *config, uint8_t *macAddr, uint8_t macCount, uint32_t refclkSrc_Hz)
{
    assert(config != NULL);

    status_t result = kStatus_Success;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = ENET_QOS_GetInstance(base);

    /* Ungate ENET clock. */
    (void)CLOCK_EnableClock(s_enetqosClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* System configure fistly. */
    ENET_QOS_SetSYSControl(config->miiMode);

    /* Initializes the ENET DMA with basic function. */
    ENET_QOS_SetDMAControl(base, config);

    (void)ENET_QOS_Up(base, config, macAddr, macCount, refclkSrc_Hz);

    if (config->ptpConfig != NULL)
    {
        result = ENET_QOS_SetPtp1588(base, config, refclkSrc_Hz);
    }

    return result;
}

/*!
 * brief Stops the ENET module.

 * This function disables the ENET module.
 *
 * param base  ENET peripheral base address.
 */
void ENET_QOS_Down(ENET_QOS_Type *base)
{
    enet_qos_handle_t *handle = s_ENETHandle[ENET_QOS_GetInstance(base)];
    enet_qos_tx_bd_struct_t *txbdPtr;
    uint8_t index;
    uint32_t primask, j;
    uint32_t txDescAddr;

    /* Disable all interrupts */
    ENET_QOS_DisableInterrupts(base, 0xFF);

    for (index = 0; index < handle->txQueueUse; index++)
    {
        enet_qos_tx_bd_ring_t *txBdRing       = &handle->txBdRing[index];
        enet_qos_tx_dirty_ring_t *txDirtyRing = (enet_qos_tx_dirty_ring_t *)&handle->txDirtyRing[index];

        /* Clear pending descriptors */
        if (handle->callback != NULL)
        {
            while (txBdRing->txDescUsed > 0U)
            {
                enet_qos_frame_info_t *txDirty = &txDirtyRing->txDirtyBase[txDirtyRing->txConsumIdx];

                txDirty->isTsAvail = false;

                handle->callback(base, handle, kENET_QOS_TxIntEvent, index, handle->userData);

                primask = DisableGlobalIRQ();
                txBdRing->txDescUsed--;
                EnableGlobalIRQ(primask);
            }
        }

        /* Disable Tx DMA */
        base->DMA_CH[index].DMA_CHX_TX_CTRL &= ~ENET_QOS_DMA_CHX_TX_CTRL_ST_MASK;

        /* Flush Tx Queue */
        base->MTL_QUEUE[index].MTL_TXQX_OP_MODE |= ENET_QOS_MTL_TXQX_OP_MODE_FTQ_MASK;

        /* Wait until Tx Queue is empty */
        while ((base->MTL_QUEUE[index].MTL_TXQX_DBG &
                (ENET_QOS_MTL_TXQX_DBG_TXQSTS_MASK | ENET_QOS_MTL_TXQX_DBG_PTXQ_MASK)) != 0U)
        {
        }

        /* Reset hardware ring buffer */
        txDescAddr =
            (uint32_t)(uintptr_t)handle->txBdRing[index].txBdBase & ENET_QOS_DMA_CHX_TXDESC_LIST_ADDR_TDESLA_MASK;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        txDescAddr = MEMORY_ConvertMemoryMapAddress(txDescAddr, kMEMORY_Local2DMA);
#endif
        base->DMA_CH[index].DMA_CHX_TXDESC_LIST_ADDR = txDescAddr;

        /* Reset software ring buffer */
        handle->txBdRing[index].txGenIdx    = 0;
        handle->txBdRing[index].txConsumIdx = 0;
        handle->txBdRing[index].txDescUsed  = 0;

        handle->txDirtyRing[index].txGenIdx    = 0;
        handle->txDirtyRing[index].txConsumIdx = 0;
        handle->txDirtyRing[index].isFull      = false;

        txbdPtr = (enet_qos_tx_bd_struct_t *)(handle->txBdRing[index].txBdBase);
        for (j = 0; j < handle->txBdRing[index].txRingLen; j++)
        {
            txbdPtr->buff1Addr   = 0;
            txbdPtr->buff2Addr   = 0;
            txbdPtr->buffLen     = 0;
            txbdPtr->controlStat = 0;
            txbdPtr++;
        }
    }

    /* Disable MAC Rx/Tx */
    base->MAC_CONFIGURATION &= ~(ENET_QOS_MAC_CONFIGURATION_TE_MASK | ENET_QOS_MAC_CONFIGURATION_RE_MASK);

    /* Disable Rx DMA */
    for (index = 0; index < handle->rxQueueUse; index++)
    {
        base->DMA_CH[index].DMA_CHX_RX_CTRL &= ~ENET_QOS_DMA_CHX_RX_CTRL_SR_MASK;
    }
}

/*!
 * brief Deinitializes the ENET module.

 * This function gates the module clock and disables the ENET module.
 *
 * param base  ENET peripheral base address.
 */
void ENET_QOS_Deinit(ENET_QOS_Type *base)
{
    /* Reset first and wait for the complete
     * The reset bit will automatically be cleared after complete. */
    base->DMA_MODE |= ENET_QOS_DMA_MODE_SWR_MASK;
    while ((base->DMA_MODE & ENET_QOS_DMA_MODE_SWR_MASK) != 0U)
    {
    }

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disables the clock source. */
    (void)CLOCK_DisableClock(s_enetqosClock[ENET_QOS_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Initialize for all ENET descriptors.
 *
 * note This function is do all tx/rx descriptors initialization. Because this API
 *  read all interrupt registers first and then set the interrupt flag for all descriptos,
 * if the interrupt register is set. so the descriptor initialization should be called
 * after ENET_QOS_Init(), ENET_QOS_EnableInterrupts() and ENET_QOS_CreateHandle()(if transactional APIs
 * are used).
 *
 * param base  ENET peripheral base address.
 * param config The configuration for ENET.
 * param bufferConfig All buffers configuration.
 */
status_t ENET_QOS_DescriptorInit(ENET_QOS_Type *base, enet_qos_config_t *config, enet_qos_buffer_config_t *bufferConfig)
{
    assert(config != NULL);
    assert(bufferConfig != NULL);

    bool intTxEnable   = false;
    bool intRxEnable   = false;
    uint8_t ringNum    = 1;
    uint8_t txQueueUse = 1;
    uint8_t rxQueueUse = 1;
    uint8_t channel;

    if (config->multiqueueCfg != NULL)
    {
        ringNum    = MAX(config->multiqueueCfg->txQueueUse, config->multiqueueCfg->rxQueueUse);
        txQueueUse = config->multiqueueCfg->txQueueUse;
        rxQueueUse = config->multiqueueCfg->rxQueueUse;
    }

    for (channel = 0; channel < ringNum; channel++)
    {
        intRxEnable = ((base->DMA_CH[channel].DMA_CHX_INT_EN & ENET_QOS_DMA_CHX_INT_EN_RIE_MASK) != 0U) ? true : false;
        intTxEnable = ((base->DMA_CH[channel].DMA_CHX_INT_EN & ENET_QOS_DMA_CHX_INT_EN_TIE_MASK) != 0U) ? true : false;

        if (channel < txQueueUse)
        {
            if ((ENET_QOS_TxDescriptorsInit(base, bufferConfig, intTxEnable, channel) != kStatus_Success))
            {
                return kStatus_Fail;
            }
        }

        if (channel < rxQueueUse)
        {
            if ((ENET_QOS_RxDescriptorsInit(base, config, bufferConfig, intRxEnable, channel) != kStatus_Success))
            {
                return kStatus_Fail;
            }
        }

        bufferConfig++;
    }
    return kStatus_Success;
}

/*!
 * brief Allocates Rx buffers for all BDs.
 * It's used for zero copy Rx. In zero copy Rx case, Rx buffers are dynamic. This function
 * will populate initial buffers in all BDs for receiving. Then ENET_QOS_GetRxFrame() is used
 * to get Rx frame with zero copy, it will allocate new buffer to replace the buffer in BD taken
 * by application application should free those buffers after they're used.
 *
 * note This function should be called after ENET_QOS_CreateHandler() and buffer allocating callback
 * function should be ready.
 *
 * param base  ENET_QOS peripheral base address.
 * param handle The ENET_QOS handler structure. This is the same handler pointer used in the ENET_QOS_Init.
 */
status_t ENET_QOS_RxBufferAllocAll(ENET_QOS_Type *base, enet_qos_handle_t *handle)
{
    status_t result = kStatus_Success;
    enet_qos_rx_bd_struct_t *rxbdPtr;
    uint32_t buffAddr;
    uint8_t channel;
    uint16_t index;
    uint16_t j;

    if ((handle->rxBuffAlloc == NULL) || (handle->rxBuffFree == NULL))
    {
        return kStatus_ENET_QOS_InitMemoryFail;
    }

    for (channel = 0; channel < handle->rxQueueUse; channel++)
    {
        /* Init the rxbdPtr to the receive descriptor start address. */
        rxbdPtr = handle->rxBdRing[channel].rxBdBase;
        for (j = 0U; j < handle->rxBdRing[channel].rxRingLen; j++)
        {
            if (handle->doubleBuffEnable)
            {
                index = 2U * j;
            }
            else
            {
                index = j;
            }

            buffAddr = (uint32_t)(uintptr_t)(uint8_t *)handle->rxBuffAlloc(base, handle->userData, channel);
            if (buffAddr == 0U)
            {
                result = kStatus_ENET_QOS_InitMemoryFail;
                break;
            }

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            buffAddr = (uint32_t)MEMORY_ConvertMemoryMapAddress(buffAddr, kMEMORY_Local2DMA);
#endif
            rxbdPtr->buff1Addr                        = buffAddr;
            handle->rxBufferStartAddr[channel][index] = buffAddr;

            /* The second buffer is set with 0 because it is not required for normal case. */
            if (handle->doubleBuffEnable)
            {
                buffAddr = (uint32_t)(uintptr_t)(uint8_t *)handle->rxBuffAlloc(base, handle->userData, channel);
                if (buffAddr == 0U)
                {
                    result = kStatus_ENET_QOS_InitMemoryFail;
                    break;
                }

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                buffAddr = (uint32_t)MEMORY_ConvertMemoryMapAddress(buffAddr, kMEMORY_Local2DMA);
#endif
                rxbdPtr->buff2Addr                             = buffAddr;
                handle->rxBufferStartAddr[channel][index + 1U] = buffAddr;
            }
            else
            {
                rxbdPtr->buff2Addr = 0;
            }

            /* Set the valid and DMA own flag.*/
            rxbdPtr->control |= ENET_QOS_RXDESCRIP_WR_OWN_MASK;
            rxbdPtr++;
        }
    }

    if (result == kStatus_ENET_QOS_InitMemoryFail)
    {
        ENET_QOS_RxBufferFreeAll(base, handle);
    }

    return result;
}

/*!
 * brief Frees Rx buffers in all BDs.
 * It's used for zero copy Rx. In zero copy Rx case, Rx buffers are dynamic. This function
 * will free left buffers in all BDs.
 *
 * param base  ENET_QOS peripheral base address.
 * param handle The ENET_QOS handler structure. This is the same handler pointer used in the ENET_QOS_Init.
 */
void ENET_QOS_RxBufferFreeAll(ENET_QOS_Type *base, enet_qos_handle_t *handle)
{
    uint32_t buffAddr;
    uint8_t channel;
    uint16_t index;
    uint16_t j;

    if (handle->rxBuffFree != NULL)
    {
        for (channel = 0; channel < handle->rxQueueUse; channel++)
        {
            for (j = 0U; j < handle->rxBdRing[channel].rxRingLen; j++)
            {
                if (handle->doubleBuffEnable)
                {
                    index = 2U * j;
                }
                else
                {
                    index = j;
                }

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                buffAddr = MEMORY_ConvertMemoryMapAddress((uintptr_t)handle->rxBufferStartAddr[channel][index],
                                                          kMEMORY_DMA2Local);
#else
                buffAddr = (uint32_t)handle->rxBufferStartAddr[channel][index];
#endif
                if (buffAddr != 0U)
                {
                    handle->rxBuffFree(base, (void *)(uint8_t *)(uintptr_t)buffAddr, handle->userData, channel);
                }

                /* The second buffer is set with 0 because it is not required for normal case. */
                if (handle->doubleBuffEnable)
                {
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                    buffAddr = MEMORY_ConvertMemoryMapAddress((uintptr_t)handle->rxBufferStartAddr[channel][index + 1U],
                                                              kMEMORY_DMA2Local);
#else
                    buffAddr = (uint32_t)handle->rxBufferStartAddr[channel][index + 1U];
#endif
                    if (buffAddr != 0U)
                    {
                        handle->rxBuffFree(base, (void *)(uint8_t *)(uintptr_t)buffAddr, handle->userData, channel);
                    }
                }
            }
        }
    }
}

/*!
 * brief Starts the ENET rx/tx.
 *  This function enable the tx/rx and starts the rx/tx DMA.
 * This shall be set after ENET initialization and before
 * starting to receive the data.
 *
 * param base  ENET peripheral base address.
 * param rxRingNum  The number of the used rx rings. It shall not be
 * larger than the ENET_QOS_RING_NUM_MAX(2). If the ringNum is set with
 * 1, the ring 0 will be used.
 * param txRingNum  The number of the used tx rings. It shall not be
 * larger than the ENET_QOS_RING_NUM_MAX(2). If the ringNum is set with
 * 1, the ring 0 will be used.
 *
 * note This must be called after all the ENET initilization.
 * And should be called when the ENET receive/transmit is required.
 */
void ENET_QOS_StartRxTx(ENET_QOS_Type *base, uint8_t txRingNum, uint8_t rxRingNum)
{
    assert(txRingNum != 0U);
    assert(rxRingNum != 0U);

    uint8_t index;

    if (txRingNum > ENET_QOS_RING_NUM_MAX)
    {
        txRingNum = ENET_QOS_RING_NUM_MAX;
    }
    if (rxRingNum > ENET_QOS_RING_NUM_MAX)
    {
        rxRingNum = ENET_QOS_RING_NUM_MAX;
    }
    /* Start/Acive the DMA first. */
    for (index = 0; index < rxRingNum; index++)
    {
        base->DMA_CH[index].DMA_CHX_RX_CTRL |= ENET_QOS_DMA_CHX_RX_CTRL_SR_MASK;
    }
    for (index = 0; index < txRingNum; index++)
    {
        base->DMA_CH[index].DMA_CHX_TX_CTRL |= ENET_QOS_DMA_CHX_TX_CTRL_ST_MASK;
    }

    /* Enable the RX and TX at same time. */
    base->MAC_CONFIGURATION |= (ENET_QOS_MAC_CONFIGURATION_TE_MASK | ENET_QOS_MAC_CONFIGURATION_RE_MASK);
}

/*!
 * brief Enables the ENET DMA and MAC interrupts.
 *
 * This function enables the ENET interrupt according to the provided mask. The mask
 * is a logical OR of enet_qos_dma_interrupt_enable_t and enet_qos_mac_interrupt_enable_t.
 * For example, to enable the dma and mac interrupt, do the following.
 * code
 *     ENET_QOS_EnableInterrupts(ENET, kENET_QOS_DmaRx | kENET_QOS_DmaTx | kENET_QOS_MacPmt);
 * endcode
 *
 * param base  ENET peripheral base address.
 * param mask  ENET interrupts to enable. This is a logical OR of both
 *             enumeration :: enet_qos_dma_interrupt_enable_t and enet_qos_mac_interrupt_enable_t.
 */
void ENET_QOS_EnableInterrupts(ENET_QOS_Type *base, uint32_t mask)
{
    uint32_t interrupt = mask & 0xFFFFU;
    uint8_t index;

    /* For dma interrupt. */
    if (interrupt != 0U)
    {
        for (index = 0; index < ENET_QOS_RING_NUM_MAX; index++)
        {
            /* Set for all abnormal interrupts. */
            if ((ENET_QOS_ABNORM_INT_MASK & interrupt) != 0U)
            {
                interrupt |= ENET_QOS_DMA_CHX_INT_EN_AIE_MASK;
            }
            /* Set for all normal interrupts. */
            if ((ENET_QOS_NORM_INT_MASK & interrupt) != 0U)
            {
                interrupt |= ENET_QOS_DMA_CHX_INT_EN_NIE_MASK;
            }
            base->DMA_CH[index].DMA_CHX_INT_EN = interrupt;
        }
    }
    interrupt = mask >> ENET_QOS_MACINT_ENUM_OFFSET;
    if (interrupt != 0U)
    {
        /* MAC interrupt */
        base->MAC_INTERRUPT_ENABLE |= interrupt;
    }
}

/*!
 * brief Clears the ENET mac interrupt events status flag.
 *
 * This function clears enabled ENET interrupts according to the provided mask. The mask
 * is a logical OR of enumeration members. See the ref enet_qos_mac_interrupt_enable_t.
 * For example, to clear the TX frame interrupt and RX frame interrupt, do the following.
 * code
 *     ENET_QOS_ClearMacInterruptStatus(ENET, kENET_QOS_MacPmt);
 * endcode
 *
 * param base  ENET peripheral base address.
 * param mask  ENET interrupt source to be cleared.
 * This is the logical OR of members of the enumeration :: enet_qos_mac_interrupt_enable_t.
 */
void ENET_QOS_ClearMacInterruptStatus(ENET_QOS_Type *base, uint32_t mask)
{
    volatile uint32_t dummy;

    if ((mask & (uint32_t)kENET_QOS_MacTimestamp) != 0U)
    {
        dummy = base->MAC_TIMESTAMP_STATUS;
    }
    else if ((mask & (uint32_t)kENET_QOS_MacPmt) != 0U)
    {
        dummy = base->MAC_PMT_CONTROL_STATUS;
    }
    else
    {
        /* Add for avoid the misra 2004 rule 14.10 */
    }
    (void)dummy;
}

/*!
 * brief Disables the ENET DMA and MAC interrupts.
 *
 * This function disables the ENET interrupt according to the provided mask. The mask
 * is a logical OR of enet_qos_dma_interrupt_enable_t and enet_qos_mac_interrupt_enable_t.
 * For example, to disable the dma and mac interrupt, do the following.
 * code
 *     ENET_QOS_DisableInterrupts(ENET, kENET_QOS_DmaRx | kENET_QOS_DmaTx | kENET_QOS_MacPmt);
 * endcode
 *
 * param base  ENET peripheral base address.
 * param mask  ENET interrupts to disables. This is a logical OR of both
 *             enumeration :: enet_qos_dma_interrupt_enable_t and enet_qos_mac_interrupt_enable_t.
 */
void ENET_QOS_DisableInterrupts(ENET_QOS_Type *base, uint32_t mask)
{
    uint32_t interrupt = mask & 0xFFFFU;
    uint8_t index;

    /* For dma interrupt. */
    if (interrupt != 0U)
    {
        for (index = 0; index < ENET_QOS_RING_NUM_MAX; index++)
        {
            /* Set for all abnormal interrupts. */
            if ((ENET_QOS_ABNORM_INT_MASK & interrupt) != 0U)
            {
                interrupt |= ENET_QOS_DMA_CHX_INT_EN_AIE_MASK;
            }
            /* Set for all normal interrupts. */
            if ((ENET_QOS_NORM_INT_MASK & interrupt) != 0U)
            {
                interrupt |= ENET_QOS_DMA_CHX_INT_EN_NIE_MASK;
            }
            base->DMA_CH[index].DMA_CHX_INT_EN &= ~interrupt;
        }
    }
    interrupt = mask >> ENET_QOS_MACINT_ENUM_OFFSET;
    if (interrupt != 0U)
    {
        /* MAC interrupt */
        base->MAC_INTERRUPT_ENABLE &= ~interrupt;
    }
}

/*!
 * @brief Set the second level IRQ handler, allow user to overwrite the default
 * second level weak IRQ handler.
 *
 * @param ISRHandler  he handler to install.
 */
void ENET_QOS_SetISRHandler(ENET_QOS_Type *base, enet_qos_isr_t ISRHandler)
{
    /* Update IRQ entry. */
    s_enetqosIsr = ISRHandler;
    /* Enable NVIC. */
    (void)EnableIRQ(s_enetqosIrqId[ENET_QOS_GetInstance(base)]);
}

/*!
 * brief Create ENET Handler
 *
 * This is a transactional API and it's provided to store all datas which are needed
 * during the whole transactional process. This API should not be used when you use
 * functional APIs to do data tx/rx. This is funtion will store many data/flag for
 * transactional use, so all configure API such as ENET_QOS_Init(), ENET_QOS_DescriptorInit(),
 * ENET_QOS_EnableInterrupts() etc.
 *
 * note as our transactional transmit API use the zero-copy transmit buffer.
 * so there are two thing we emphasize here:
 *  1. tx buffer free/requeue for application should be done in the tx
 *  interrupt handler. Please set callback: kENET_QOS_TxIntEvent with tx buffer free/requeue
 *  process APIs.
 *  2. the tx interrupt is forced to open.
 *
 * param base  ENET peripheral base address.
 * param handle ENET handler.
 * param config ENET configuration.
 * param bufferConfig ENET buffer configuration.
 * param callback The callback function.
 * param userData The application data.
 */
void ENET_QOS_CreateHandler(ENET_QOS_Type *base,
                            enet_qos_handle_t *handle,
                            enet_qos_config_t *config,
                            enet_qos_buffer_config_t *bufferConfig,
                            enet_qos_callback_t callback,
                            void *userData)
{
    assert(config != NULL);
    assert(bufferConfig != NULL);
    assert(callback != NULL);

    uint8_t ringNum                      = 1;
    uint8_t count                        = 0;
    uint32_t rxIntEnable                 = 0;
    uint8_t txQueueUse                   = 1;
    uint8_t rxQueueUse                   = 1;
    enet_qos_buffer_config_t *buffConfig = bufferConfig;

    /* Store transfer parameters in handle pointer. */
    (void)memset(handle, 0, sizeof(enet_qos_handle_t));

    if (config->multiqueueCfg != NULL)
    {
        txQueueUse = config->multiqueueCfg->txQueueUse;
        rxQueueUse = config->multiqueueCfg->rxQueueUse;
        ringNum    = MAX(txQueueUse, rxQueueUse);
    }

    handle->txQueueUse = txQueueUse;
    handle->rxQueueUse = rxQueueUse;

    if ((config->specialControl & (uint32_t)kENET_QOS_DescDoubleBuffer) != 0U)
    {
        handle->doubleBuffEnable = true;
    }

    for (count = 0; count < ringNum; count++)
    {
        if (count < txQueueUse)
        {
            handle->txBdRing[count].txBdBase    = buffConfig->txDescStartAddrAlign;
            handle->txBdRing[count].txRingLen   = buffConfig->txRingLen;
            handle->txBdRing[count].txGenIdx    = 0;
            handle->txBdRing[count].txConsumIdx = 0;
            handle->txBdRing[count].txDescUsed  = 0;

            handle->txDirtyRing[count].txDirtyBase = buffConfig->txDirtyStartAddr;
            handle->txDirtyRing[count].txRingLen   = buffConfig->txRingLen;
            handle->txDirtyRing[count].txGenIdx    = 0;
            handle->txDirtyRing[count].txConsumIdx = 0;

            /* Enable tx interrupt for use transactional API to do tx buffer free/requeue. */
            base->DMA_CH[count].DMA_CHX_INT_EN |= ENET_QOS_DMA_CHX_INT_EN_TIE_MASK | ENET_QOS_DMA_CHX_INT_EN_NIE_MASK;
        }

        if (count < rxQueueUse)
        {
            handle->rxBdRing[count].rxBdBase        = buffConfig->rxDescStartAddrAlign;
            handle->rxBdRing[count].rxGenIdx        = 0;
            handle->rxBdRing[count].rxRingLen       = buffConfig->rxRingLen;
            handle->rxBdRing[count].rxBuffSizeAlign = buffConfig->rxBuffSizeAlign;

            /* Record rx buffer address for re-init Rx buffer descriptor */
            handle->rxBufferStartAddr[count] = buffConfig->rxBufferStartAddr;

            /* Record rx buffer need cache maintain */
            handle->rxMaintainEnable[count] = buffConfig->rxBuffNeedMaintain;

            /* Check if the rx interrrupt is enabled. */
            rxIntEnable |= (base->DMA_CH[count].DMA_CHX_INT_EN & ENET_QOS_DMA_CHX_INT_EN_RIE_MASK);
        }

        buffConfig++;
    }

    handle->rxintEnable = (rxIntEnable != 0U) ? true : false;

    /* Save the handle pointer in the global variables. */
    s_ENETHandle[ENET_QOS_GetInstance(base)] = handle;

    /* Set Rx alloc/free callback. */
    handle->rxBuffAlloc = config->rxBuffAlloc;
    handle->rxBuffFree  = config->rxBuffFree;

    /* Set callback and userData. */
    handle->callback = callback;
    handle->userData = userData;

    /* Use default ENET_QOS_CommonIRQHandler as default weak IRQ handler. */
    ENET_QOS_SetISRHandler(base, ENET_QOS_CommonIRQHandler);
}

/*!
 * brief Gets the ENET module Mac address.
 *
 * param base  ENET peripheral base address.
 * param macAddr The six-byte Mac address pointer.
 *        The pointer is allocated by application and input into the API.
 */
void ENET_QOS_GetMacAddr(ENET_QOS_Type *base, uint8_t *macAddr, uint8_t index)
{
    assert(macAddr != NULL);

    uint32_t address = base->MAC_ADDRESS[index].LOW;

    /* Get from physical address lower register. */
    macAddr[2] = (uint8_t)(0xFFU & (address >> 24U));
    macAddr[3] = (uint8_t)(0xFFU & (address >> 16U));
    macAddr[4] = (uint8_t)(0xFFU & (address >> 8U));
    macAddr[5] = (uint8_t)(0xFFU & address);

    /* Get from physical address high register. */
    address    = base->MAC_ADDRESS[index].HIGH;
    macAddr[0] = (uint8_t)(0xFFU & (address >> 8U));
    macAddr[1] = (uint8_t)(0xFFU & address);
}

/*!
 * brief Adds the ENET_QOS device to a multicast group.
 *
 * param base    ENET_QOS peripheral base address.
 * param address The six-byte multicast group address which is provided by application.
 */
void ENET_QOS_AddMulticastGroup(ENET_QOS_Type *base, uint8_t *address)
{
    assert(address != NULL);

    enet_qos_handle_t *handle = s_ENETHandle[ENET_QOS_GetInstance(base)];
    uint32_t crc              = 0xFFFFFFFFU;
    uint32_t count1           = 0;
    uint32_t count2           = 0;

    /* Calculates the CRC-32 polynomial on the multicast group address. */
    for (count1 = 0; count1 < 6U; count1++)
    {
        uint8_t c = address[count1];
        for (count2 = 0; count2 < 0x08U; count2++)
        {
            if (((c ^ crc) & 1U) != 0U)
            {
                crc >>= 1U;
                c >>= 1U;
                crc ^= 0xEDB88320U;
            }
            else
            {
                crc >>= 1U;
                c >>= 1U;
            }
        }
    }

    /* Calculate bitwise reverse value. */
    crc = ENET_QOS_ReverseBits(~crc);

    /* Get highest 6 bits*/
    crc = crc >> 26U;

    handle->multicastCount[crc]++;

    if (0U != (crc & 0x20U))
    {
        base->MAC_HASH_TABLE_REG1 |= (1UL << (crc & 0x1FU));
    }
    else
    {
        base->MAC_HASH_TABLE_REG0 |= (1UL << (crc & 0x1FU));
    }
}

/*!
 * brief Moves the ENET_QOS device from a multicast group.
 *
 * param base  ENET_QOS peripheral base address.
 * param address The six-byte multicast group address which is provided by application.
 */
void ENET_QOS_LeaveMulticastGroup(ENET_QOS_Type *base, uint8_t *address)
{
    assert(address != NULL);

    enet_qos_handle_t *handle = s_ENETHandle[ENET_QOS_GetInstance(base)];
    uint32_t crc              = 0xFFFFFFFFU;
    uint32_t count1           = 0;
    uint32_t count2           = 0;

    /* Calculates the CRC-32 polynomial on the multicast group address. */
    for (count1 = 0; count1 < 6U; count1++)
    {
        uint8_t c = address[count1];
        for (count2 = 0; count2 < 0x08U; count2++)
        {
            if (((c ^ crc) & 1U) != 0U)
            {
                crc >>= 1U;
                c >>= 1U;
                crc ^= 0xEDB88320U;
            }
            else
            {
                crc >>= 1U;
                c >>= 1U;
            }
        }
    }

    /* Calculate bitwise reverse value. */
    crc = ENET_QOS_ReverseBits(~crc);

    /* Get highest 6 bits*/
    crc = crc >> 26U;

    handle->multicastCount[crc]--;

    /* Set the hash table if no collisions */
    if (0U == handle->multicastCount[crc])
    {
        if (0U != (crc & 0x20U))
        {
            base->MAC_HASH_TABLE_REG1 &= ~((1UL << (crc & 0x1FU)));
        }
        else
        {
            base->MAC_HASH_TABLE_REG0 &= ~((1UL << (crc & 0x1FU)));
        }
    }
}

/*!
 * brief Sets the ENET SMI(serial management interface)- MII management interface.
 *
 * param base  ENET peripheral base address.
 */
void ENET_QOS_SetSMI(ENET_QOS_Type *base, uint32_t csrClock_Hz)
{
    uint32_t crDiv       = 0;
    uint32_t srcClock_Hz = csrClock_Hz / 1000000U;

    assert((srcClock_Hz >= 20U) && (srcClock_Hz < 800U));

    if (srcClock_Hz < 35U)
    {
        crDiv = 2;
    }
    else if (srcClock_Hz < 60U)
    {
        crDiv = 3;
    }
    else if (srcClock_Hz < 100U)
    {
        crDiv = 0;
    }
    else if (srcClock_Hz < 150U)
    {
        crDiv = 1;
    }
    else if (srcClock_Hz < 250U)
    {
        crDiv = 4;
    }
    else if (srcClock_Hz < 300U)
    {
        crDiv = 5;
    }
    else if (srcClock_Hz < 500U)
    {
        crDiv = 6;
    }
    else if (srcClock_Hz < 800U)
    {
        crDiv = 7;
    }
    else
    {
        /* Empty else */
    }

    base->MAC_MDIO_ADDRESS = ENET_QOS_MAC_MDIO_ADDRESS_CR(crDiv);
}

/*!
 * brief Starts a SMI write command.
 * It supports MDIO IEEE802.3 Clause 22.
 * After send command, user needs to check whether the transmission is over
 * with ENET_QOS_IsSMIBusy().
 *
 * param base  ENET peripheral base address.
 * param phyAddr The PHY address.
 * param phyReg The PHY register.
 * param data The data written to PHY.
 */
void ENET_QOS_StartSMIWrite(ENET_QOS_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t data)
{
    uint32_t reg = base->MAC_MDIO_ADDRESS & ENET_QOS_MAC_MDIO_ADDRESS_CR_MASK;

    /* Build MII write command. */
    base->MAC_MDIO_ADDRESS = reg | (uint32_t)kENET_QOS_MiiWriteFrame | ENET_QOS_MAC_MDIO_ADDRESS_PA(phyAddr) |
                             ENET_QOS_MAC_MDIO_ADDRESS_RDA(phyReg);
    base->MAC_MDIO_DATA = data;
    base->MAC_MDIO_ADDRESS |= ENET_QOS_MAC_MDIO_ADDRESS_GB_MASK;
}

/*!
 * brief Starts an SMI read command.
 * It supports MDIO IEEE802.3 Clause 22.
 * After send command, user needs to check whether the transmission is over
 * with ENET_QOS_IsSMIBusy().
 *
 * param base  ENET peripheral base address.
 * param phyAddr The PHY address.
 * param phyReg The PHY register.
 */
void ENET_QOS_StartSMIRead(ENET_QOS_Type *base, uint32_t phyAddr, uint32_t phyReg)
{
    uint32_t reg = base->MAC_MDIO_ADDRESS & ENET_QOS_MAC_MDIO_ADDRESS_CR_MASK;

    /* Build MII read command. */
    base->MAC_MDIO_ADDRESS = reg | (uint32_t)kENET_QOS_MiiReadFrame | ENET_QOS_MAC_MDIO_ADDRESS_PA(phyAddr) |
                             ENET_QOS_MAC_MDIO_ADDRESS_RDA(phyReg);
    base->MAC_MDIO_ADDRESS |= ENET_QOS_MAC_MDIO_ADDRESS_GB_MASK;
}

/*!
 * brief Starts a SMI write command.
 * It supports MDIO IEEE802.3 Clause 45.
 * After send command, user needs to check whether the transmission is over
 * with ENET_QOS_IsSMIBusy().
 *
 * param base  ENET peripheral base address.
 * param phyAddr The PHY address.
 * param device The PHY device type.
 * param phyReg The PHY register address.
 * param data The data written to PHY.
 */
void ENET_QOS_StartExtC45SMIWrite(
    ENET_QOS_Type *base, uint32_t phyAddr, uint32_t device, uint32_t phyReg, uint32_t data)
{
    uint32_t reg = base->MAC_MDIO_ADDRESS & ENET_QOS_MAC_MDIO_ADDRESS_CR_MASK;

    /* Build MII write command. */
    base->MAC_MDIO_ADDRESS = reg | ENET_QOS_MAC_MDIO_ADDRESS_C45E_MASK | (uint32_t)kENET_QOS_MiiWriteFrame |
                             ENET_QOS_MAC_MDIO_ADDRESS_PA(phyAddr) | ENET_QOS_MAC_MDIO_ADDRESS_RDA(device);
    base->MAC_MDIO_DATA = data | ENET_QOS_MAC_MDIO_DATA_RA(phyReg);
    base->MAC_MDIO_ADDRESS |= ENET_QOS_MAC_MDIO_ADDRESS_GB_MASK;
}

/*!
 * brief Starts a SMI write command.
 * It supports MDIO IEEE802.3 Clause 45.
 * After send command, user needs to check whether the transmission is over
 * with ENET_QOS_IsSMIBusy().
 *
 * param base  ENET peripheral base address.
 * param phyAddr The PHY address.
 * param device The PHY device type.
 * param phyReg The PHY register address.
 */
void ENET_QOS_StartExtC45SMIRead(ENET_QOS_Type *base, uint32_t phyAddr, uint32_t device, uint32_t phyReg)
{
    uint32_t reg = base->MAC_MDIO_ADDRESS & ENET_QOS_MAC_MDIO_ADDRESS_CR_MASK;

    /* Build MII read command. */
    base->MAC_MDIO_ADDRESS = reg | ENET_QOS_MAC_MDIO_ADDRESS_C45E_MASK | (uint32_t)kENET_QOS_MiiReadFrame |
                             ENET_QOS_MAC_MDIO_ADDRESS_PA(phyAddr) | ENET_QOS_MAC_MDIO_ADDRESS_RDA(device);
    base->MAC_MDIO_DATA = ENET_QOS_MAC_MDIO_DATA_RA(phyReg);
    base->MAC_MDIO_ADDRESS |= ENET_QOS_MAC_MDIO_ADDRESS_GB_MASK;
}

/*!
 * brief Set the MAC to enter into power down mode.
 * the remote power wake up frame and magic frame can wake up
 * the ENET from the power down mode.
 *
 * param base    ENET peripheral base address.
 * param wakeFilter  The wakeFilter provided to configure the wake up frame fitlter.
 *  Set the wakeFilter to NULL is not required. But if you have the filter requirement,
 *  please make sure the wakeFilter pointer shall be eight continous
 *  32-bits configuration.
 */
void ENET_QOS_EnterPowerDown(ENET_QOS_Type *base, uint32_t *wakeFilter)
{
    uint8_t index;
    uint32_t *reg = wakeFilter;

    /* Disable the tx dma. */
    base->DMA_CH[0].DMA_CHX_TX_CTRL &= ~ENET_QOS_DMA_CHX_TX_CTRL_ST_MASK;
    base->DMA_CH[1].DMA_CHX_TX_CTRL &= ~ENET_QOS_DMA_CHX_TX_CTRL_ST_MASK;

    /* Disable the mac tx/rx. */
    base->MAC_CONFIGURATION &= ~(ENET_QOS_MAC_CONFIGURATION_RE_MASK | ENET_QOS_MAC_CONFIGURATION_TE_MASK);
    /* Enable the remote wakeup packet and enable the power down mode. */
    if (wakeFilter != NULL)
    {
        for (index = 0; index < ENET_QOS_WAKEUPFILTER_NUM; index++)
        {
            base->MAC_RWK_PACKET_FILTER = *reg;
            reg++;
        }
    }
    base->MAC_PMT_CONTROL_STATUS = ENET_QOS_MAC_PMT_CONTROL_STATUS_MGKPKTEN_MASK |
                                   ENET_QOS_MAC_PMT_CONTROL_STATUS_RWKPKTEN_MASK |
                                   ENET_QOS_MAC_PMT_CONTROL_STATUS_PWRDWN_MASK;

    /* Enable the MAC rx. */
    base->MAC_CONFIGURATION |= ENET_QOS_MAC_CONFIGURATION_RE_MASK;
}

/*!
 * brief Enable/Disable Rx parser, please notice that for enable/disable Rx Parser,
 * should better disable Receive first.
 *
 * param base    ENET_QOS peripheral base address.
 * param enable    Enable/Disable Rx parser function
 */
status_t ENET_QOS_EnableRxParser(ENET_QOS_Type *base, bool enable)
{
    status_t result = kStatus_Success;

    if (enable)
    {
        base->MTL_OPERATION_MODE |= ENET_QOS_MTL_OPERATION_MODE_FRPE_MASK;
    }
    else
    {
        base->MTL_OPERATION_MODE &= ~ENET_QOS_MTL_OPERATION_MODE_FRPE_MASK;
        result = ENET_QOS_PollStatusFlag(&(base->MTL_RXP_CONTROL_STATUS), ENET_QOS_MTL_RXP_CONTROL_STATUS_RXPI_MASK,
                                         ENET_QOS_MTL_RXP_CONTROL_STATUS_RXPI_MASK);
    }

    return result;
}

/*!
 * brief Gets the size of the read frame.
 * This function gets a received frame size from the ENET buffer descriptors.
 * note The FCS of the frame is automatically removed by MAC and the size is the length without the FCS.
 * After calling ENET_QOS_GetRxFrameSize, ENET_QOS_ReadFrame() should be called to update the
 * receive buffers If the result is not "kStatus_ENET_QOS_RxFrameEmpty".
 *
 * param handle The ENET handler structure. This is the same handler pointer used in the ENET_QOS_Init.
 * param length The length of the valid frame received.
 * param channel The DMAC channel for the rx.
 * retval kStatus_ENET_QOS_RxFrameEmpty No frame received. Should not call ENET_QOS_ReadFrame to read frame.
 * retval kStatus_ENET_QOS_RxFrameError Data error happens. ENET_QOS_ReadFrame should be called with NULL data
 *         and NULL length to update the receive buffers.
 * retval kStatus_Success Receive a frame Successfully then the ENET_QOS_ReadFrame
 *         should be called with the right data buffer and the captured data length input.
 */
status_t ENET_QOS_GetRxFrameSize(ENET_QOS_Type *base, enet_qos_handle_t *handle, uint32_t *length, uint8_t channel)
{
    assert(handle != NULL);
    assert(length != NULL);

    enet_qos_rx_bd_ring_t *rxBdRing = (enet_qos_rx_bd_ring_t *)&handle->rxBdRing[channel];
    enet_qos_rx_bd_struct_t *rxDesc = &rxBdRing->rxBdBase[rxBdRing->rxGenIdx];
    uint16_t index                  = rxBdRing->rxGenIdx;
    uint32_t control                = rxDesc->control;

    /* Reset the length to zero. */
    *length = 0;

    if ((control & ENET_QOS_RXDESCRIP_WR_OWN_MASK) != 0U)
    {
        return kStatus_ENET_QOS_RxFrameEmpty;
    }
    else
    {
        do
        {
            /* Application owns the buffer descriptor, get the length. */
            if ((control & ENET_QOS_RXDESCRIP_WR_LD_MASK) != 0U)
            {
                if ((control & ENET_QOS_RXDESCRIP_WR_ERRSUM_MASK) != 0U)
                {
                    return kStatus_ENET_QOS_RxFrameError;
                }
                *length = (control & ENET_QOS_RXDESCRIP_WR_PACKETLEN_MASK) - ENET_QOS_FCS_LEN;
                return kStatus_Success;
            }

            index   = ENET_QOS_IncreaseIndex(index, rxBdRing->rxRingLen);
            rxDesc  = &rxBdRing->rxBdBase[index];
            control = rxDesc->control;
        } while (index != rxBdRing->rxGenIdx);

        return kStatus_ENET_QOS_RxFrameError;
    }
}

static void ENET_QOS_DropFrame(ENET_QOS_Type *base, enet_qos_handle_t *handle, uint8_t channel)
{
    enet_qos_rx_bd_ring_t *rxBdRing = (enet_qos_rx_bd_ring_t *)&handle->rxBdRing[channel];
    enet_qos_rx_bd_struct_t *rxDesc;
    uint16_t index      = rxBdRing->rxGenIdx;
    bool tsAvailable    = false;
    uintptr_t buff1Addr = 0;
    uintptr_t buff2Addr = 0;
    uint32_t rxDescTail;
    uint32_t rdesc1;
    uint32_t rdesc3;

    /* Not check DMA ownership here, assume there's at least one valid frame left in BD ring */
    do
    {
        /* Get the control flag. */
        rxDesc = &rxBdRing->rxBdBase[rxBdRing->rxGenIdx];
        rdesc1 = rxDesc->reserved;
        rdesc3 = rxDesc->control;

        if (!handle->doubleBuffEnable)
        {
            buff1Addr = handle->rxBufferStartAddr[channel][rxBdRing->rxGenIdx];
            ENET_QOS_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, NULL, handle->rxintEnable,
                                        handle->doubleBuffEnable);
        }
        else
        {
            buff1Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx];
            buff2Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx + 1U];
            ENET_QOS_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, (void *)(uint8_t *)buff2Addr,
                                        handle->rxintEnable, handle->doubleBuffEnable);
        }

        rxBdRing->rxGenIdx = ENET_QOS_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);

        /* Find the last buffer descriptor for the frame. */
        if ((rdesc3 & ENET_QOS_RXDESCRIP_WR_LD_MASK) != 0U)
        {
            if ((rdesc3 & ENET_QOS_RXDESCRIP_WR_RS1V_MASK) != 0U)
            {
                if ((rdesc1 & ENET_QOS_RXDESCRIP_WR_PTPTSA_MASK) != 0U)
                {
                    tsAvailable = true;
                }
            }

            /* Reinit for the context descriptor which has been updated by DMA. */
            rxDesc = &rxBdRing->rxBdBase[rxBdRing->rxGenIdx];

            if (tsAvailable && ((rxDesc->control & ENET_QOS_RXDESCRIP_WR_CTXT_MASK) != 0U))
            {
                if (!handle->doubleBuffEnable)
                {
                    buff1Addr = handle->rxBufferStartAddr[channel][rxBdRing->rxGenIdx];
                    ENET_QOS_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, NULL, handle->rxintEnable,
                                                handle->doubleBuffEnable);
                }
                else
                {
                    buff1Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx];
                    buff2Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx + 1U];
                    ENET_QOS_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, (void *)(uint8_t *)buff2Addr,
                                                handle->rxintEnable, handle->doubleBuffEnable);
                }
                rxBdRing->rxGenIdx = ENET_QOS_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);
            }
            break;
        }
    } while (rxBdRing->rxGenIdx != index);

    /* Always try to start receive, in case it had stopped */
    rxDescTail = (uint32_t)(uintptr_t)&rxBdRing->rxBdBase[rxBdRing->rxRingLen];
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    rxDescTail = MEMORY_ConvertMemoryMapAddress(rxDescTail, kMEMORY_Local2DMA);
#endif
    base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR = rxDescTail;
}

/*!
 * brief Reads a frame from the ENET device.
 * This function reads a frame from the ENET DMA descriptors.
 * The ENET_QOS_GetRxFrameSize should be used to get the size of the prepared data buffer.
 * For example use rx dma channel 0:
 * code
 *       uint32_t length;
 *       enet_qos_handle_t g_handle;
 *       enet_qos_ptp_time_t ts;
 *       status = ENET_QOS_GetRxFrameSize(&g_handle, &length, 0);
 *       if (length != 0)
 *       {
 *           uint8_t *data = memory allocate interface;
 *           if (!data)
 *           {
 *               ENET_QOS_ReadFrame(ENET, &g_handle, NULL, 0, 0, &ts);
 *           }
 *           else
 *           {
 *              status = ENET_QOS_ReadFrame(ENET, &g_handle, data, length, 0, &ts);
 *           }
 *       }
 *       else if (status == kStatus_ENET_QOS_RxFrameError)
 *       {
 *           ENET_QOS_ReadFrame(ENET, &g_handle, NULL, 0, 0, &ts);
 *       }
 * endcode
 * param base  ENET peripheral base address.
 * param handle The ENET handler structure. This is the same handler pointer used in the ENET_QOS_Init.
 * param data The data buffer provided by user to store the frame which memory size should be at least "length".
 * param length The size of the data buffer which is still the length of the received frame.
 * param channel The rx DMA channel. shall not be larger than 2.
 * return The execute status, successful or failure.
 */
status_t ENET_QOS_ReadFrame(ENET_QOS_Type *base,
                            enet_qos_handle_t *handle,
                            uint8_t *data,
                            uint32_t length,
                            uint8_t channel,
                            enet_qos_ptp_time_t *ts)
{
    assert(handle != NULL);
    assert(channel < handle->rxQueueUse);

    uint32_t len    = 0;
    uint32_t offset = 0;
    uint32_t control;
    bool isLastBuff                 = false;
    enet_qos_rx_bd_ring_t *rxBdRing = (enet_qos_rx_bd_ring_t *)&handle->rxBdRing[channel];
    enet_qos_rx_bd_struct_t *rxDesc;
    status_t result     = kStatus_Fail;
    uintptr_t buff1Addr = 0; /*!< Buffer 1 address */
    uintptr_t buff2Addr = 0; /*!< Buffer 2 or next descriptor address */
    uint32_t rxDescTail;

    bool tsAvailable = false;

    /* For data-NULL input, only update the buffer descriptor. */
    if (data == NULL)
    {
        ENET_QOS_DropFrame(base, handle, channel);
        result = kStatus_Success;
    }
    else
    {
        while (!isLastBuff)
        {
            /* The last buffer descriptor of a frame. */
            rxDesc  = &rxBdRing->rxBdBase[rxBdRing->rxGenIdx];
            control = rxDesc->control;

            if (!handle->doubleBuffEnable)
            {
                buff1Addr = handle->rxBufferStartAddr[channel][rxBdRing->rxGenIdx];
                if (handle->rxMaintainEnable[channel])
                {
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                    /* Add the cache invalidate maintain. */
                    ENET_QOS_DcacheInvalidateByRange(MEMORY_ConvertMemoryMapAddress(buff1Addr, kMEMORY_DMA2Local),
                                                     rxBdRing->rxBuffSizeAlign);
#else
                    /* Add the cache invalidate maintain. */
                    ENET_QOS_DcacheInvalidateByRange(buff1Addr, rxBdRing->rxBuffSizeAlign);
#endif
                }
            }
            else
            {
                buff1Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx];
                buff2Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx + 1U];
                if (handle->rxMaintainEnable[channel])
                {
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                    /* Add the cache invalidate maintain. */
                    ENET_QOS_DcacheInvalidateByRange(MEMORY_ConvertMemoryMapAddress(buff1Addr, kMEMORY_DMA2Local),
                                                     rxBdRing->rxBuffSizeAlign);
                    /* Add the cache invalidate maintain. */
                    ENET_QOS_DcacheInvalidateByRange(MEMORY_ConvertMemoryMapAddress(buff2Addr, kMEMORY_DMA2Local),
                                                     rxBdRing->rxBuffSizeAlign);
#else
                    /* Add the cache invalidate maintain. */
                    ENET_QOS_DcacheInvalidateByRange(buff1Addr, rxBdRing->rxBuffSizeAlign);
                    /* Add the cache invalidate maintain. */
                    ENET_QOS_DcacheInvalidateByRange(buff2Addr, rxBdRing->rxBuffSizeAlign);
#endif
                }
            }

            rxBdRing->rxGenIdx = ENET_QOS_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);

            if ((control & ENET_QOS_RXDESCRIP_WR_LD_MASK) != 0U)
            {
                /* This is a valid frame. */
                isLastBuff = true;

                /* Remove FCS */
                len = (control & ENET_QOS_RXDESCRIP_WR_PACKETLEN_MASK) - ENET_QOS_FCS_LEN;

                if (length == len)
                {
                    /* Copy the frame to user's buffer. */
                    len -= offset;

                    if (len > rxBdRing->rxBuffSizeAlign)
                    {
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                        (void)memcpy((void *)&data[offset],
                                     (void *)(uint8_t *)MEMORY_ConvertMemoryMapAddress(buff1Addr, kMEMORY_DMA2Local),
                                     rxBdRing->rxBuffSizeAlign);
#else
                        (void)memcpy((void *)&data[offset], (void *)(uint8_t *)buff1Addr, rxBdRing->rxBuffSizeAlign);
#endif
                        offset += rxBdRing->rxBuffSizeAlign;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                        (void)memcpy((void *)&data[offset],
                                     (void *)(uint8_t *)MEMORY_ConvertMemoryMapAddress(buff2Addr, kMEMORY_DMA2Local),
                                     len - rxBdRing->rxBuffSizeAlign);
#else
                        (void)memcpy((void *)&data[offset], (void *)(uint8_t *)buff2Addr,
                                     len - rxBdRing->rxBuffSizeAlign);
#endif
                    }
                    else
                    {
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                        (void)memcpy((void *)&data[offset],
                                     (void *)(uint8_t *)MEMORY_ConvertMemoryMapAddress(buff1Addr, kMEMORY_DMA2Local),
                                     len);
#else
                        (void)memcpy((void *)&data[offset], (void *)(uint8_t *)buff1Addr, len);
#endif
                    }

                    result = kStatus_Success;
                }

                if ((rxDesc->reserved & ENET_QOS_RXDESCRIP_WR_PTPTSA_MASK) != 0U)
                {
                    tsAvailable = true;
                }
                /* Updates the receive buffer descriptors. */
                ENET_QOS_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, (void *)(uint8_t *)buff2Addr,
                                            handle->rxintEnable, handle->doubleBuffEnable);
                /* Store the rx timestamp which is in the next buffer descriptor of the last
                 * descriptor of a frame. */
                rxDesc  = &rxBdRing->rxBdBase[rxBdRing->rxGenIdx];
                control = rxDesc->control;

                /* If tsAvailable is true, a context descriptor is expected but might not be yet
                 * available.
                 */
                if (tsAvailable)
                {
                    uint8_t retryTimes = 10;

                    while (((control & ENET_QOS_RXDESCRIP_WR_OWN_MASK) != 0U) ||
                           ((control & ENET_QOS_RXDESCRIP_WR_CTXT_MASK) == 0U))
                    {
                        SDK_DelayAtLeastUs(1U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
                        if (0U == retryTimes--)
                        {
                            assert(false);
                        }
                        control = rxDesc->control;
                    }
                }

                /* Reinit for the context descritor which has been updated by DMA. */
                if ((control & ENET_QOS_RXDESCRIP_WR_CTXT_MASK) != 0U)
                {
                    if (tsAvailable && (NULL != ts))
                    {
                        ENET_QOS_StoreRxFrameTime(base, handle, rxDesc, ts);
                    }

                    if (!handle->doubleBuffEnable)
                    {
                        buff1Addr = handle->rxBufferStartAddr[channel][rxBdRing->rxGenIdx];
                        ENET_QOS_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, NULL, handle->rxintEnable,
                                                    handle->doubleBuffEnable);
                    }
                    else
                    {
                        buff1Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx];
                        buff2Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx + 1U];
                        ENET_QOS_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, (void *)(uint8_t *)buff2Addr,
                                                    handle->rxintEnable, handle->doubleBuffEnable);
                    }
                    rxBdRing->rxGenIdx = ENET_QOS_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);
                }
            }
            else
            {
                /* Store a frame on several buffer descriptors. */
                isLastBuff = false;
                /* Length check. */
                if (offset >= length)
                {
                    /* Updates the receive buffer descriptors. */
                    ENET_QOS_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, (void *)(uint8_t *)buff2Addr,
                                                handle->rxintEnable, handle->doubleBuffEnable);
                    break;
                }

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                (void)memcpy((void *)&data[offset],
                             (void *)(uint8_t *)MEMORY_ConvertMemoryMapAddress(buff1Addr, kMEMORY_DMA2Local),
                             rxBdRing->rxBuffSizeAlign);
#else
                (void)memcpy((void *)&data[offset], (void *)(uint8_t *)buff1Addr, rxBdRing->rxBuffSizeAlign);
#endif

                offset += rxBdRing->rxBuffSizeAlign;
                if (buff2Addr != 0U)
                {
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                    (void)memcpy((void *)&data[offset],
                                 (void *)(uint8_t *)MEMORY_ConvertMemoryMapAddress(buff2Addr, kMEMORY_DMA2Local),
                                 rxBdRing->rxBuffSizeAlign);
#else
                    (void)memcpy((void *)&data[offset], (void *)(uint8_t *)buff2Addr, rxBdRing->rxBuffSizeAlign);
#endif
                    offset += rxBdRing->rxBuffSizeAlign;
                }

                ENET_QOS_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, (void *)(uint8_t *)buff2Addr,
                                            handle->rxintEnable, handle->doubleBuffEnable);
            }
        }

        /* Always try to start receive, in case it had stopped */
        rxDescTail = (uint32_t)(uintptr_t)&rxBdRing->rxBdBase[rxBdRing->rxRingLen];
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        rxDescTail = MEMORY_ConvertMemoryMapAddress(rxDescTail, kMEMORY_Local2DMA);
#endif
        base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR = rxDescTail;
    }

    return result;
}

/*!
 * brief Updates the buffers and the own status for a given rx descriptor.
 *  This function is a low level functional API to Updates the
 *  buffers and the own status for a given rx descriptor.
 *
 * param rxDesc  The given rx descriptor.
 * param buffer1  The first buffer address in the descriptor.
 * param buffer2  The second buffer address in the descriptor.
 * param intEnable Interrupt enable flag.
 * param doubleBuffEnable The double buffer enable flag.
 *
 * note This must be called after all the ENET initilization.
 * And should be called when the ENET receive/transmit is required.
 */
void ENET_QOS_UpdateRxDescriptor(
    enet_qos_rx_bd_struct_t *rxDesc, void *buffer1, void *buffer2, bool intEnable, bool doubleBuffEnable)
{
    assert(rxDesc != NULL);
    uint32_t control = ENET_QOS_RXDESCRIP_RD_OWN_MASK | ENET_QOS_RXDESCRIP_RD_BUFF1VALID_MASK;

    if (intEnable)
    {
        control |= ENET_QOS_RXDESCRIP_RD_IOC_MASK;
    }

    if (doubleBuffEnable)
    {
        control |= ENET_QOS_RXDESCRIP_RD_BUFF2VALID_MASK;
    }

    /* Update the buffer if needed. */
    if (buffer1 != NULL)
    {
        rxDesc->buff1Addr = (uint32_t)(uintptr_t)(uint8_t *)buffer1;
    }
    if (buffer2 != NULL)
    {
        rxDesc->buff2Addr = (uint32_t)(uintptr_t)(uint8_t *)buffer2;
    }
    else
    {
        rxDesc->buff2Addr = 0;
    }

    rxDesc->reserved = 0;

    /* Add a data barrier to be sure that the address is written before the
      ownership bit status. */
    __DMB();

    rxDesc->control = control;
}

/*!
 * brief Setup a given tx descriptor.
 *  This function is a low level functional API to setup or prepare
 *  a given tx descriptor.
 *
 * param txDesc  The given tx descriptor.
 * param buffer1  The first buffer address in the descriptor.
 * param bytes1  The bytes in the fist buffer.
 * param buffer2  The second buffer address in the descriptor.
 * param bytes1  The bytes in the second buffer.
 * param framelen  The length of the frame to be transmitted.
 * param intEnable Interrupt enable flag.
 * param tsEnable The timestamp enable.
 * param flag The flag of this tx desciriptor, see "enet_qos_desc_flag" .
 * param slotNum The slot num used for AV  only.
 *
 * note This must be called after all the ENET initilization.
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
                                uint8_t slotNum)
{
    uint32_t control = ENET_QOS_TXDESCRIP_RD_BL1(bytes1) | ENET_QOS_TXDESCRIP_RD_BL2(bytes2);

    if (tsEnable)
    {
        control |= ENET_QOS_TXDESCRIP_RD_TTSE_MASK;
    }
    else
    {
        control &= ~ENET_QOS_TXDESCRIP_RD_TTSE_MASK;
    }

    if (intEnable)
    {
        control |= ENET_QOS_TXDESCRIP_RD_IOC_MASK;
    }
    else
    {
        control &= ~ENET_QOS_TXDESCRIP_RD_IOC_MASK;
    }

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    buffer1 = (void *)(uint8_t *)MEMORY_ConvertMemoryMapAddress((uintptr_t)(uint8_t *)buffer1, kMEMORY_Local2DMA);
    buffer2 = (void *)(uint8_t *)MEMORY_ConvertMemoryMapAddress((uintptr_t)(uint8_t *)buffer2, kMEMORY_Local2DMA);
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */

    /* Preare the descriptor for transmit. */
    txDesc->buff1Addr = (uint32_t)(uintptr_t)(uint8_t *)buffer1;
    txDesc->buff2Addr = (uint32_t)(uintptr_t)(uint8_t *)buffer2;
    txDesc->buffLen   = control;

    /* Make sure all fields of descriptor are written before setting ownership */
    __DMB();

    control = ENET_QOS_TXDESCRIP_RD_FL(framelen) | ENET_QOS_TXDESCRIP_RD_LDFD(flag) | ENET_QOS_TXDESCRIP_RD_OWN_MASK;

    txDesc->controlStat = control;

    /* Make sure the descriptor is written in memory (before MAC starts checking it) */
    __DSB();
}

/*!
 * brief Reclaim tx descriptors.
 *  This function is used to update the tx descriptor status and
 *  store the tx timestamp when the 1588 feature is enabled.
 *  This is called by the transmit interupt IRQ handler after the
 *  complete of a frame transmission.
 *
 * param base    ENET peripheral base address.
 * param handle The ENET handler pointer. This is the same handler pointer used in the ENET_QOS_Init.
 * param channel  The tx DMA channnel.
 *
 */
void ENET_QOS_ReclaimTxDescriptor(ENET_QOS_Type *base, enet_qos_handle_t *handle, uint8_t channel)
{
    enet_qos_tx_bd_ring_t *txBdRing       = &handle->txBdRing[channel];
    enet_qos_tx_bd_struct_t *txDesc       = &txBdRing->txBdBase[txBdRing->txConsumIdx];
    enet_qos_tx_dirty_ring_t *txDirtyRing = (enet_qos_tx_dirty_ring_t *)&handle->txDirtyRing[channel];
    enet_qos_frame_info_t *txDirty        = NULL;
    uint32_t control, primask;

    control = txDesc->controlStat;

    /* Need to update the first index for transmit buffer free. */
    while ((txBdRing->txDescUsed > 0U) && (0U == (control & ENET_QOS_TXDESCRIP_RD_OWN_MASK)))
    {
        if ((control & ENET_QOS_TXDESCRIP_RD_LD_MASK) != 0U)
        {
            if (ENET_QOS_TxDirtyRingAvailable(txDirtyRing))
            {
                txDirty               = &txDirtyRing->txDirtyBase[txBdRing->txConsumIdx];
                txDirtyRing->txGenIdx = ENET_QOS_IncreaseIndex(txDirtyRing->txGenIdx, txDirtyRing->txRingLen);
                if (txDirtyRing->txGenIdx == txDirtyRing->txConsumIdx)
                {
                    txDirtyRing->isFull = true;
                }

                if ((control & ENET_QOS_TXDESCRIP_WB_TTSS_MASK) != 0U)
                {
                    enet_qos_ptp_time_t *ts = &txDirty->timeStamp;
                    uint32_t nanosecond;
                    /* Get transmit time stamp second. */
                    nanosecond         = txDesc->buff1Addr;
                    txDirty->isTsAvail = true;
                    if (0U == (base->MAC_TIMESTAMP_CONTROL & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_MASK))
                    {
                        /* Binary rollover, 0.465ns accuracy. */
                        nanosecond = (nanosecond * 465U) / 1000U;
                    }
                    ts->second     = txDesc->buff2Addr;
                    ts->nanosecond = nanosecond;
                }
                else
                {
                    txDirty->isTsAvail = false;
                }
            }
        }

        /* For tx buffer free or requeue for each descriptor.
         * The tx interrupt callback should free/requeue the tx buffer. */
        if (handle->callback != NULL)
        {
            handle->callback(base, handle, kENET_QOS_TxIntEvent, channel, handle->userData);
        }

        primask = DisableGlobalIRQ();
        txBdRing->txDescUsed--;
        EnableGlobalIRQ(primask);

        /* Update the txConsumIdx/txDesc. */
        txBdRing->txConsumIdx = ENET_QOS_IncreaseIndex(txBdRing->txConsumIdx, txBdRing->txRingLen);
        txDesc                = &txBdRing->txBdBase[txBdRing->txConsumIdx];
        control               = txDesc->controlStat;
    }
}

/*!
 * brief Transmits an ENET frame.
 * note The CRC is automatically appended to the data. Input the data
 * to send without the CRC.
 *
 * param base  ENET peripheral base address.
 * param handle The ENET handler pointer. This is the same handler pointer used in the ENET_QOS_Init.
 * param data The data buffer provided by user to be send.
 * param length The length of the data to be send.
 * param channel Channel to send the frame, same with queue index.
 * param isNeedTs True means save timestamp
 * param context pointer to user context to be kept in the tx dirty frame information.
 * retval kStatus_Success  Send frame succeed.
 * retval kStatus_ENET_QOS_TxFrameBusy  Transmit buffer descriptor is busy under transmission.
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
                            void *context)
{
    assert(handle != NULL);
    assert(data != NULL);
    assert(channel < handle->txQueueUse);

    enet_qos_tx_bd_ring_t *txBdRing;
    enet_qos_tx_bd_struct_t *txDesc;
    enet_qos_tx_dirty_ring_t *txDirtyRing;
    enet_qos_frame_info_t *txDirty;
    uint32_t primask;
    uint32_t txDescTail;

    if (length > 2U * ENET_QOS_TXDESCRIP_RD_BL1_MASK)
    {
        return kStatus_ENET_QOS_TxFrameOverLen;
    }

    /* Check if the DMA owns the descriptor. */
    txBdRing = (enet_qos_tx_bd_ring_t *)&handle->txBdRing[channel];
    txDesc   = &txBdRing->txBdBase[txBdRing->txGenIdx];
    if (txBdRing->txRingLen == txBdRing->txDescUsed)
    {
        return kStatus_ENET_QOS_TxFrameBusy;
    }

    txDirtyRing      = (enet_qos_tx_dirty_ring_t *)&handle->txDirtyRing[channel];
    txDirty          = &txDirtyRing->txDirtyBase[txBdRing->txGenIdx];
    txDirty->context = context;

    /* Fill the descriptor. */
    if (length <= ENET_QOS_TXDESCRIP_RD_BL1_MASK)
    {
        ENET_QOS_SetupTxDescriptor(txDesc, data, length, NULL, 0, length, true, isNeedTs, kENET_QOS_FirstLastFlag, 0);
    }
    else
    {
        ENET_QOS_SetupTxDescriptor(txDesc, data, ENET_QOS_TXDESCRIP_RD_BL1_MASK, &data[ENET_QOS_TXDESCRIP_RD_BL1_MASK],
                                   (length - ENET_QOS_TXDESCRIP_RD_BL1_MASK), length, true, isNeedTs,
                                   kENET_QOS_FirstLastFlag, 0);
    }

    /* Increase the index. */
    txBdRing->txGenIdx = ENET_QOS_IncreaseIndex(txBdRing->txGenIdx, txBdRing->txRingLen);
    /* Disable interrupt first and then enable interrupt to avoid the race condition. */
    primask = DisableGlobalIRQ();
    txBdRing->txDescUsed++;
    EnableGlobalIRQ(primask);

    /* Update the transmit tail address. */
    txDesc = &txBdRing->txBdBase[txBdRing->txGenIdx];
    if (txBdRing->txGenIdx == 0U)
    {
        txDesc = &txBdRing->txBdBase[txBdRing->txRingLen];
    }
    txDescTail = (uint32_t)(uintptr_t)txDesc & ~ENET_QOS_ADDR_ALIGNMENT;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    txDescTail = MEMORY_ConvertMemoryMapAddress(txDescTail, kMEMORY_Local2DMA);
#endif
    base->DMA_CH[channel].DMA_CHX_TXDESC_TAIL_PTR = txDescTail;

    return kStatus_Success;
}

/*!
 * brief Gets the sent frame.
 *
 * This function is used to get the sent frame for timestamp and buffer clean operation.
 *
 * param handle The ENET handler pointer.This is the same state pointer used in
 *        ENET_QOS_Init.
 * param txFrame Input parameter, pointer to enet_qos_frame_info_t for saving read out frame information.
 * param channel Read out frame from specified channel.
 */
void ENET_QOS_GetTxFrame(enet_qos_handle_t *handle, enet_qos_frame_info_t *txFrame, uint8_t channel)
{
    assert(handle != NULL);
    assert(channel < handle->txQueueUse);

    enet_qos_tx_dirty_ring_t *txDirtyRing = (enet_qos_tx_dirty_ring_t *)&handle->txDirtyRing[channel];
    enet_qos_frame_info_t *txDirty        = &txDirtyRing->txDirtyBase[txDirtyRing->txConsumIdx];

    (void)memcpy(txFrame, txDirty, sizeof(enet_qos_frame_info_t));

    txDirtyRing->isFull      = false;
    txDirtyRing->txConsumIdx = ENET_QOS_IncreaseIndex(txDirtyRing->txConsumIdx, txDirtyRing->txRingLen);
}

static inline void ENET_QOS_GetRxFrameErr(enet_qos_rx_bd_struct_t *rxDesc, enet_qos_rx_frame_error_t *rxFrameError)
{
    uint32_t rdes2 = rxDesc->buff2Addr;
    uint32_t rdes3 = rxDesc->control;

    (void)memset(rxFrameError, 0, sizeof(enet_qos_rx_frame_error_t));

    if ((rdes2 & ENET_QOS_RXDESCRIP_WR_SA_FAILURE_MASK) != 0U)
    {
        rxFrameError->rxSrcAddrFilterErr = true;
    }
    if ((rdes2 & ENET_QOS_RXDESCRIP_WR_DA_FAILURE_MASK) != 0U)
    {
        rxFrameError->rxDstAddrFilterErr = true;
    }
    if ((rdes3 & ENET_QOS_RXDESCRIP_WR_DE_MASK) != 0U)
    {
        rxFrameError->rxDstAddrFilterErr = true;
    }
    if ((rdes3 & ENET_QOS_RXDESCRIP_WR_RE_MASK) != 0U)
    {
        rxFrameError->rxReceiveErr = true;
    }
    if ((rdes3 & ENET_QOS_RXDESCRIP_WR_OE_MASK) != 0U)
    {
        rxFrameError->rxOverFlowErr = true;
    }
    if ((rdes3 & ENET_QOS_RXDESCRIP_WR_RWT_MASK) != 0U)
    {
        rxFrameError->rxWatchDogErr = true;
    }
    if ((rdes3 & ENET_QOS_RXDESCRIP_WR_GP_MASK) != 0U)
    {
        rxFrameError->rxGaintPacketErr = true;
    }
    if ((rdes3 & ENET_QOS_RXDESCRIP_WR_CRC_MASK) != 0U)
    {
        rxFrameError->rxCrcErr = true;
    }
}

/*!
 * brief Receives one frame in specified BD ring with zero copy.
 *
 * This function will use the user-defined allocate and free callback. Every time application gets one frame through
 * this function, driver will allocate new buffers for the BDs whose buffers have been taken by application.
 * note This function will drop current frame and update related BDs as available for DMA if new buffers allocating
 * fails. Application must provide a memory pool including at least BD number + 1 buffers(+2 if enable double buffer)
 * to make this function work normally. If user calls this function in Rx interrupt handler, be careful that this
 * function makes Rx BD ready with allocating new buffer(normal) or updating current BD(out of memory). If there's
 * always new Rx frame input, Rx interrupt will be triggered forever. Application need to disable Rx interrupt according
 * to specific design in this case.
 *
 * param base   ENET peripheral base address.
 * param handle The ENET handler pointer. This is the same handler pointer used in the ENET_Init.
 * param rxFrame The received frame information structure provided by user.
 * param ringId The ring index or ring number.
 * retval kStatus_Success  Succeed to get one frame and allocate new memory for Rx buffer.
 * retval kStatus_ENET_QOS_RxFrameEmpty  There's no Rx frame in the BD.
 * retval kStatus_ENET_QOS_RxFrameError  There's issue in this receiving.
 * retval kStatus_ENET_QOS_RxFrameDrop  There's no new buffer memory for BD, drop this frame.
 */
status_t ENET_QOS_GetRxFrame(ENET_QOS_Type *base,
                             enet_qos_handle_t *handle,
                             enet_qos_rx_frame_struct_t *rxFrame,
                             uint8_t channel)
{
    assert(handle != NULL);
    assert(channel < handle->rxQueueUse);

    enet_qos_rx_bd_ring_t *rxBdRing = (enet_qos_rx_bd_ring_t *)&handle->rxBdRing[channel];
    enet_qos_rx_bd_struct_t *rxDesc = &rxBdRing->rxBdBase[rxBdRing->rxGenIdx];
    uint16_t index                  = rxBdRing->rxGenIdx;
    status_t result                 = kStatus_Success;
    uintptr_t buff1Addr             = 0;
    uintptr_t buff2Addr             = 0;
    uint16_t buff1Len               = 0;
    uint16_t buff2Len               = 0;
    uint16_t offset                 = 0;
    void *newBuff1                  = NULL;
    void *newBuff2                  = NULL;
    bool isDrop                     = false;
    bool isLastBuff                 = false;
    bool tsAvailable                = false;
    uint32_t rxDescTail;

    /* Check the frame status. */
    do
    {
        if ((rxDesc->control & ENET_QOS_RXDESCRIP_WR_OWN_MASK) != 0U)
        {
            result = kStatus_ENET_QOS_RxFrameEmpty;
            break;
        }

        /* Check timestamp and error. */
        if ((rxDesc->control & ENET_QOS_RXDESCRIP_WR_LD_MASK) != 0U)
        {
            if ((rxDesc->control & ENET_QOS_RXDESCRIP_WR_RS1V_MASK) != 0U)
            {
                if ((rxDesc->reserved & ENET_QOS_RXDESCRIP_WR_PTPTSA_MASK) != 0U)
                {
                    /* Context descriptor is expected but might not be yet available. */
                    uint8_t retryTimes = 10;

                    while (((rxDesc->control & ENET_QOS_RXDESCRIP_WR_OWN_MASK) != 0U) ||
                           ((rxDesc->control & ENET_QOS_RXDESCRIP_WR_CTXT_MASK) == 0U))
                    {
                        /* Timsstamp value is not corrupted. */
                        if ((rxDesc->buff1Addr != 0xFFFFFFFFU) && (rxDesc->buff2Addr != 0xFFFFFFFFU))
                        {
                            break;
                        }
                        if (retryTimes-- == 0U)
                        {
                            break;
                        }
                    }

                    if (retryTimes != 0U)
                    {
                        tsAvailable = true;
                    }
                    else
                    {
                        result = kStatus_ENET_QOS_RxFrameEmpty;
                        break;
                    }
                }
            }

            /* Get the frame error if there is. */
            if ((rxDesc->control & ENET_QOS_RXDESCRIP_WR_ERRSUM_MASK) != 0U)
            {
                ENET_QOS_GetRxFrameErr(rxDesc, &rxFrame->rxFrameError);
                result = kStatus_ENET_QOS_RxFrameError;
            }
            else if ((rxDesc->control & ENET_QOS_RXDESCRIP_WR_PACKETLEN_MASK) == 0U)
            {
                result = kStatus_ENET_QOS_RxFrameEmpty;
            }
            else
            {
                /* Intentional empty */
            }
            break;
        }

        index = ENET_QOS_IncreaseIndex(index, rxBdRing->rxRingLen);
        if (index == rxBdRing->rxGenIdx)
        {
            result = kStatus_ENET_QOS_RxFrameEmpty;
            break;
        }
        rxDesc = &rxBdRing->rxBdBase[index];
    } while (index != rxBdRing->rxGenIdx);

    /* Drop the error frame and return error. */
    if (result != kStatus_Success)
    {
        if (result == kStatus_ENET_QOS_RxFrameError)
        {
            ENET_QOS_DropFrame(base, handle, channel);
        }
        return result;
    }

    /* Get the valid frame */
    index = 0;
    do
    {
        rxDesc = &rxBdRing->rxBdBase[rxBdRing->rxGenIdx];

        /* Caculate the buffer and frame length. */
        if ((rxDesc->control & ENET_QOS_RXDESCRIP_WR_LD_MASK) != 0U)
        {
            isLastBuff      = true;
            rxFrame->totLen = (uint16_t)(rxDesc->control & ENET_QOS_RXDESCRIP_WR_PACKETLEN_MASK);

            if (rxFrame->totLen - offset > (uint16_t)rxBdRing->rxBuffSizeAlign)
            {
                buff1Len = (uint16_t)rxBdRing->rxBuffSizeAlign;
                if (handle->doubleBuffEnable)
                {
                    buff2Len = rxFrame->totLen - offset - (uint16_t)rxBdRing->rxBuffSizeAlign - ENET_QOS_FCS_LEN;
                }
            }
            else
            {
                buff1Len = rxFrame->totLen - offset - ENET_QOS_FCS_LEN;
            }
            rxFrame->totLen -= ENET_QOS_FCS_LEN;
        }
        else
        {
            if (!handle->doubleBuffEnable)
            {
                buff1Len = (uint16_t)rxBdRing->rxBuffSizeAlign;
                offset += buff1Len;
            }
            else
            {
                buff1Len = (uint16_t)rxBdRing->rxBuffSizeAlign;
                buff2Len = (uint16_t)rxBdRing->rxBuffSizeAlign;
                offset += buff1Len + buff2Len;
            }
        }

        /* Allocate new buffer to replace the buffer taken by application */
        newBuff1 = handle->rxBuffAlloc(base, handle->userData, channel);
        if (newBuff1 == NULL)
        {
            isDrop = true;
        }
        else if (handle->doubleBuffEnable && (buff2Len != 0U))
        {
            newBuff2 = handle->rxBuffAlloc(base, handle->userData, channel);
            if (newBuff2 == NULL)
            {
                handle->rxBuffFree(base, newBuff1, handle->userData, channel);
                isDrop = true;
            }
        }
        else
        {
            /* Intentional empty */
        }

        if (!isDrop)
        {
            /* Get the frame data information into Rx frame structure. */
            if (!handle->doubleBuffEnable)
            {
                buff1Addr = handle->rxBufferStartAddr[channel][rxBdRing->rxGenIdx];
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                buff1Addr = MEMORY_ConvertMemoryMapAddress(buff1Addr, kMEMORY_DMA2Local);
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
                if (handle->rxMaintainEnable[channel])
                {
                    ENET_QOS_DcacheInvalidateByRange(buff1Addr, rxBdRing->rxBuffSizeAlign);
                }
                rxFrame->rxBuffArray[index].buffer = (void *)(uint8_t *)buff1Addr;
                rxFrame->rxBuffArray[index].length = buff1Len;
                index++;
            }
            else
            {
                buff1Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx];
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                buff1Addr = MEMORY_ConvertMemoryMapAddress(buff1Addr, kMEMORY_DMA2Local);
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
                if (handle->rxMaintainEnable[channel])
                {
                    ENET_QOS_DcacheInvalidateByRange(buff1Addr, rxBdRing->rxBuffSizeAlign);
                }
                rxFrame->rxBuffArray[index].buffer = (void *)(uint8_t *)buff1Addr;
                rxFrame->rxBuffArray[index].length = buff1Len;
                index++;

                /* If there's no data in buffer2, not add it into rxFrame */
                if (buff2Len != 0U)
                {
                    buff2Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx + 1U];
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                    buff2Addr = MEMORY_ConvertMemoryMapAddress(buff2Addr, kMEMORY_DMA2Local);
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
                    if (handle->rxMaintainEnable[channel])
                    {
                        ENET_QOS_DcacheInvalidateByRange(buff2Addr, rxBdRing->rxBuffSizeAlign);
                    }
                    rxFrame->rxBuffArray[index].buffer = (void *)(uint8_t *)buff2Addr;
                    rxFrame->rxBuffArray[index].length = buff2Len;
                    index++;
                }
            }

            /* Give new buffer from application to BD */
            if (!handle->doubleBuffEnable)
            {
                if (handle->rxMaintainEnable[channel])
                {
                    ENET_QOS_DcacheInvalidateByRange((uintptr_t)(uint8_t *)newBuff1, rxBdRing->rxBuffSizeAlign);
                }
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                buff1Addr = MEMORY_ConvertMemoryMapAddress((uintptr_t)(uint8_t *)newBuff1, kMEMORY_Local2DMA);
#else
                buff1Addr = (uintptr_t)(uint8_t *)newBuff1;
#endif
                handle->rxBufferStartAddr[channel][rxBdRing->rxGenIdx] = buff1Addr;
                ENET_QOS_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, NULL, handle->rxintEnable,
                                            handle->doubleBuffEnable);
            }
            else
            {
                if (handle->rxMaintainEnable[channel])
                {
                    ENET_QOS_DcacheInvalidateByRange((uintptr_t)(uint8_t *)newBuff1, rxBdRing->rxBuffSizeAlign);
                }
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                buff1Addr = MEMORY_ConvertMemoryMapAddress((uintptr_t)(uint8_t *)newBuff1, kMEMORY_Local2DMA);
#else
                buff1Addr = (uintptr_t)(uint8_t *)newBuff1;
#endif
                handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx] = buff1Addr;

                if (buff2Len != 0U)
                {
                    if (handle->rxMaintainEnable[channel])
                    {
                        ENET_QOS_DcacheInvalidateByRange((uintptr_t)(uint8_t *)newBuff2, rxBdRing->rxBuffSizeAlign);
                    }
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                    buff2Addr =
                        (uint32_t)MEMORY_ConvertMemoryMapAddress((uintptr_t)(uint8_t *)newBuff2, kMEMORY_Local2DMA);
#else
                    buff2Addr = (uintptr_t)(uint8_t *)newBuff2;
#endif
                    handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx + 1U] = buff2Addr;
                }
                else
                {
                    /* If there's no data in buffer2, keep it */
                    buff2Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx + 1U];
                }

                ENET_QOS_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, (void *)(uint8_t *)buff2Addr,
                                            handle->rxintEnable, handle->doubleBuffEnable);
            }
            rxBdRing->rxGenIdx = ENET_QOS_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);

            /* Update context BD if there is */
            if (isLastBuff && tsAvailable)
            {
                rxDesc = &rxBdRing->rxBdBase[rxBdRing->rxGenIdx];
                if ((rxDesc->control & ENET_QOS_RXDESCRIP_WR_CTXT_MASK) != 0U)
                {
                    ENET_QOS_StoreRxFrameTime(base, handle, rxDesc, &rxFrame->rxAttribute.timestamp);
                    rxFrame->rxAttribute.isTsAvail = true;

                    if (!handle->doubleBuffEnable)
                    {
                        buff1Addr = handle->rxBufferStartAddr[channel][rxBdRing->rxGenIdx];
                        ENET_QOS_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, NULL, handle->rxintEnable,
                                                    handle->doubleBuffEnable);
                    }
                    else
                    {
                        buff1Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx];
                        buff2Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx + 1U];
                        ENET_QOS_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, (void *)(uint8_t *)buff2Addr,
                                                    handle->rxintEnable, handle->doubleBuffEnable);
                    }
                    rxBdRing->rxGenIdx = ENET_QOS_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);
                }
            }
            /* Always try to start receive, in case it had stopped */
            rxDescTail = (uint32_t)(uintptr_t)&rxBdRing->rxBdBase[rxBdRing->rxRingLen];
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            rxDescTail = MEMORY_ConvertMemoryMapAddress(rxDescTail, kMEMORY_Local2DMA);
#endif
            base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR = rxDescTail;
        }
        else
        {
            /* Drop frame if there's no new buffer memory */

            /* Free the incomplete frame buffers. */
            while (index-- != 0U)
            {
                handle->rxBuffFree(base, &rxFrame->rxBuffArray[index].buffer, handle->userData, channel);
            }

            /* Update all left BDs of this frame from current index. */
            ENET_QOS_DropFrame(base, handle, channel);

            result = kStatus_ENET_QOS_RxFrameDrop;
            break;
        }
    } while (!isLastBuff);

    return result;
}

/*!
 * brief Gets the current ENET time from the PTP 1588 timer without IRQ disable.
 *
 * param base  ENET peripheral base address.
 * param second The PTP 1588 system timer second.
 * param nanosecond The PTP 1588 system timer nanosecond.
 * For the unit of the nanosecond is 1ns. so the nanosecond is the real nanosecond.
 */
void ENET_QOS_Ptp1588GetTimerNoIRQDisable(ENET_QOS_Type *base, uint64_t *second, uint32_t *nanosecond)
{
    assert(second != NULL);
    assert(nanosecond != NULL);

    uint32_t high_sec[2];
    uint32_t sec[2];

    /* Get the current PTP time. */
    /* Since register reads are not atomic, we need to check for wraps during the read */
    high_sec[1] = base->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS & ENET_QOS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_MASK;

    do
    {
        high_sec[0] = high_sec[1];

        sec[1] = base->MAC_SYSTEM_TIME_SECONDS;

        do
        {
            sec[0]      = sec[1];
            *nanosecond = base->MAC_SYSTEM_TIME_NANOSECONDS & ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_TSSS_MASK;
            sec[1]      = base->MAC_SYSTEM_TIME_SECONDS;
        } while (sec[1] != sec[0]);

        high_sec[1] =
            base->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS & ENET_QOS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_MASK;
    } while (high_sec[1] != high_sec[0]);

    *second = ((uint64_t)high_sec[1] << 32U) | sec[1];

    if ((base->MAC_TIMESTAMP_CONTROL & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_MASK) == 0U)
    {
        /* Binary rollover, the unit of the increment is ~ 0.465 ns. */
        *nanosecond = (*nanosecond * 465U) / 1000U;
    }
}

/*!
 * brief Gets the current ENET time from the PTP 1588 timer, get a more accurate value
 * with IRQ disabled during get timer.
 *
 * param base  ENET peripheral base address.
 * param second The PTP 1588 system timer second.
 * param nanosecond The PTP 1588 system timer nanosecond.
 * For the unit of the nanosecond is 1ns. so the nanosecond is the real nanosecond.
 */
void ENET_QOS_Ptp1588GetTimer(ENET_QOS_Type *base, uint64_t *second, uint32_t *nanosecond)
{
    uint32_t primask;

    /* Disables the interrupt. */
    primask = DisableGlobalIRQ();

    ENET_QOS_Ptp1588GetTimerNoIRQDisable(base, second, nanosecond);

    /* Enables the interrupt. */
    EnableGlobalIRQ(primask);
}

/*!
 * brief Coreect the ENET PTP 1588 timer in coarse method.
 *
 * param base  ENET peripheral base address.
 * param operation The system time operation, refer to "enet_qos_systime_op"
 * param second The correction second.
 * param nanosecond The correction nanosecond.
 */
status_t ENET_QOS_Ptp1588CorrectTimerInCoarse(ENET_QOS_Type *base,
                                              enet_qos_systime_op operation,
                                              uint32_t second,
                                              uint32_t nanosecond)
{
    uint32_t corrSecond = second;
    uint32_t corrNanosecond;
    status_t result = kStatus_Success;

    /* Set the system timer. */
    if ((base->MAC_TIMESTAMP_CONTROL & ENET_QOS_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_MASK) != 0U)
    {
        if (operation == kENET_QOS_SystimeSubtract)
        {
            /* Set with the complement of the sub-second. */
            corrSecond     = ENET_QOS_MAC_SYSTEM_TIME_SECONDS_UPDATE_TSS_MASK - (second - 1U);
            corrNanosecond = ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB_MASK |
                             ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS(ENET_QOS_NANOSECS_ONESECOND - nanosecond);
        }
        else
        {
            corrNanosecond = ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS(nanosecond);
        }
    }
    else
    {
        nanosecond = ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_MASK / ENET_QOS_NANOSECS_ONESECOND * nanosecond;
        if (operation == kENET_QOS_SystimeSubtract)
        {
            /* Set with the complement of the sub-second. */
            corrSecond     = ENET_QOS_MAC_SYSTEM_TIME_SECONDS_UPDATE_TSS_MASK - (second - 1U);
            corrNanosecond = ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB_MASK |
                             ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS(
                                 ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_MASK + 1U - nanosecond);
        }
        else
        {
            corrNanosecond = ENET_QOS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS(nanosecond);
        }
    }

    base->MAC_SYSTEM_TIME_SECONDS_UPDATE     = corrSecond;
    base->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE = corrNanosecond;

    /* Update the timer. */
    base->MAC_TIMESTAMP_CONTROL |= ENET_QOS_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK;

    /* Wait for update finish */
    result = ENET_QOS_PollStatusFlag(&(base->MAC_TIMESTAMP_CONTROL), ENET_QOS_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK, 0U);

    return result;
}

/*!
 * brief Correct the ENET PTP 1588 timer in fine method.
 *
 *
 * param base  ENET peripheral base address.
 * param addend The addend value to be set in the fine method
 * note Should take refer to the chapter "System time correction" and
 * see the description for the "fine correction method".
 */
status_t ENET_QOS_Ptp1588CorrectTimerInFine(ENET_QOS_Type *base, uint32_t addend)
{
    status_t result = kStatus_Success;

    base->MAC_TIMESTAMP_ADDEND = addend;
    base->MAC_TIMESTAMP_CONTROL |= ENET_QOS_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK;

    result = ENET_QOS_PollStatusFlag(&(base->MAC_TIMESTAMP_CONTROL), ENET_QOS_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK, 0U);

    return result;
}

/*!
 * @brief Sets the ENET OQS PTP 1588 PPS target time registers.
 *
 * param base  ENET QOS peripheral base address.
 * param instance The ENET QOS PTP PPS instance.
 * param seconds The target seconds.
 * param nanoseconds The target nanoseconds.
 */
status_t ENET_QOS_Ptp1588PpsSetTrgtTime(ENET_QOS_Type *base,
                                        enet_qos_ptp_pps_instance_t instance,
                                        uint32_t seconds,
                                        uint32_t nanoseconds)
{
    uint32_t *mac_pps_trgt_ns;
    uint32_t *mac_pps_trgt_s;

    mac_pps_trgt_ns = (uint32_t *)((uintptr_t)&base->MAC_PPS0_TARGET_TIME_NANOSECONDS + 0x10U * (uint32_t)instance);
    mac_pps_trgt_s  = (uint32_t *)((uintptr_t)&base->MAC_PPS0_TARGET_TIME_SECONDS + 0x10U * (uint32_t)instance);

    if ((*mac_pps_trgt_ns & ENET_QOS_MAC_PPS0_TARGET_TIME_NANOSECONDS_TRGTBUSY0_MASK) != 0U)
    {
        return kStatus_ENET_QOS_TrgtBusy;
    }

    *mac_pps_trgt_ns = ENET_QOS_MAC_PPS0_TARGET_TIME_NANOSECONDS_TTSL0(nanoseconds);
    *mac_pps_trgt_s  = ENET_QOS_MAC_PPS0_TARGET_TIME_SECONDS_TSTRH0(seconds);

    return kStatus_Success;
}

static status_t ENET_QOS_EstReadWriteWord(
    ENET_QOS_Type *base, uint32_t addr, uint32_t *data, uint8_t gcrr, uint8_t read, uint8_t dbgm)
{
    uint32_t ctrl;
    int retry = 10;

    ctrl = ENET_QOS_MTL_EST_GCL_CONTROL_ADDR(addr) | ENET_QOS_MTL_EST_GCL_CONTROL_SRWO(1) |
           ENET_QOS_MTL_EST_GCL_CONTROL_DBGM(dbgm) | ENET_QOS_MTL_EST_GCL_CONTROL_GCRR(gcrr);

    if (read != 0U)
    {
        ctrl |= ENET_QOS_MTL_EST_GCL_CONTROL_R1W0(1);
    }
    else
    {
        base->MTL_EST_GCL_DATA = *data;
    }

    base->MTL_EST_GCL_CONTROL = ctrl;

    while ((base->MTL_EST_GCL_CONTROL & ENET_QOS_MTL_EST_GCL_CONTROL_SRWO_MASK) != 0U)
    {
        if (retry-- < 0)
        {
            return kStatus_Timeout;
        }
        SDK_DelayAtLeastUs(1, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }

    if (read != 0U)
    {
        *data = base->MTL_EST_GCL_DATA;
    }

    if ((base->MTL_EST_GCL_CONTROL & ENET_QOS_MTL_EST_GCL_CONTROL_ERR0_MASK) != 0U)
    {
        return kStatus_ENET_QOS_Est_SwListWriteAbort;
    }

    return kStatus_Success;
}

static status_t ENET_QOS_EstProgramWord(ENET_QOS_Type *base, uint32_t addr, uint32_t *data, uint8_t gcrr)
{
    return ENET_QOS_EstReadWriteWord(base, addr, data, gcrr, 0, 0);
}

static status_t ENET_QOS_EstReadWord(ENET_QOS_Type *base, uint32_t addr, uint32_t *data, uint8_t gcrr, uint8_t dbgm)
{
    return ENET_QOS_EstReadWriteWord(base, addr, data, gcrr, 1, dbgm);
}

/*!
 * @brief Program Gate Control List.
 *
 * This function is used to program the Enhanced Scheduled Transmisson. (IEEE802.1Qbv)
 *
 * @param base  ENET peripheral base address..
 * @param gcl Pointer to the Gate Control List structure.
 * @param ptpClk_Hz frequency of the PTP clock.
 */
status_t ENET_QOS_EstProgramGcl(ENET_QOS_Type *base, enet_qos_est_gcl_t *gcl, uint32_t ptpClk_Hz)
{
    assert(gcl != NULL);
    uint32_t i, control, data;
    enet_qos_est_gate_op_t *gateOp;
    status_t rc;

#define EST_MAX_INTERVAL ((1UL << ENET_QOS_EST_WID) - 1U)
#define EST_MAX_GATE     ((1UL << (32U - ENET_QOS_EST_WID)) - 1U)

    if (!gcl->enable)
    {
        goto exit;
    }

    /* Sanity checks */
    if (gcl->numEntries > ENET_QOS_EST_DEP)
    {
        return kStatus_ENET_QOS_Est_InvalidParameter;
    }

    if (gcl->opList == NULL)
    {
        return kStatus_ENET_QOS_Est_InvalidParameter;
    }

    gateOp = gcl->opList;

    for (i = 0; i < gcl->numEntries; i++)
    {
        if (gateOp->interval > EST_MAX_INTERVAL)
        {
            return kStatus_ENET_QOS_Est_InvalidParameter;
        }
        if (gateOp->gate > EST_MAX_GATE)
        {
            return kStatus_ENET_QOS_Est_InvalidParameter;
        }
        gateOp++;
    }

    /* Check if sw list is busy */
    if ((base->MTL_EST_CONTROL & ENET_QOS_MTL_EST_CONTROL_SSWL_MASK) != 0U)
    {
        return kStatus_ENET_QOS_Est_SwListBusy;
    }

    gateOp = gcl->opList;

    for (i = 0; i < gcl->numEntries; i++)
    {
        data = gateOp->interval | (gateOp->gate << ENET_QOS_EST_WID);
        rc   = ENET_QOS_EstProgramWord(base, i, &data, 0);
        if (rc != kStatus_Success)
        {
            return rc;
        }

        gateOp++;
    }

    /* BTR High */
    data = (uint32_t)(gcl->baseTime >> 32U);
    rc   = ENET_QOS_EstProgramWord(base, (uint32_t)kENET_QOS_Ets_btr_high, &data, 1U);
    if (rc != kStatus_Success)
    {
        return rc;
    }

    /* BTR Low */
    data = (uint32_t)gcl->baseTime;
    rc   = ENET_QOS_EstProgramWord(base, (uint32_t)kENET_QOS_Ets_btr_low, &data, 1);
    if (rc != kStatus_Success)
    {
        return rc;
    }

    /* CTR High */
    data = (uint32_t)(gcl->cycleTime >> 32U);
    rc   = ENET_QOS_EstProgramWord(base, (uint32_t)kENET_QOS_Ets_ctr_high, &data, 1);
    if (rc != kStatus_Success)
    {
        return rc;
    }

    /* CTR Low */
    data = (uint32_t)gcl->cycleTime;
    rc   = ENET_QOS_EstProgramWord(base, (uint32_t)kENET_QOS_Ets_ctr_low, &data, 1);
    if (rc != kStatus_Success)
    {
        return rc;
    }

    /* TER */
    data = gcl->extTime;
    rc   = ENET_QOS_EstProgramWord(base, (uint32_t)kENET_QOS_Ets_ter, &data, 1);
    if (rc != kStatus_Success)
    {
        return rc;
    }

    /* LLR */
    data = gcl->numEntries;
    rc   = ENET_QOS_EstProgramWord(base, (uint32_t)kENET_QOS_Ets_llr, &data, 1);
    if (rc != kStatus_Success)
    {
        return rc;
    }

exit:
    control = base->MTL_EST_CONTROL;

    if (gcl->enable)
    {
        control &= ~ENET_QOS_MTL_EST_CONTROL_PTOV_MASK;
        control |= ENET_QOS_MTL_EST_CONTROL_SSWL_MASK | ENET_QOS_MTL_EST_CONTROL_EEST_MASK |
                   ENET_QOS_MTL_EST_CONTROL_PTOV((1000000000U / ptpClk_Hz) * 6U);
    }
    else
    {
        control &= ~ENET_QOS_MTL_EST_CONTROL_EEST_MASK;
    }

    base->MTL_EST_CONTROL = control;

    return kStatus_Success;
}

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
status_t ENET_QOS_EstReadGcl(ENET_QOS_Type *base, enet_qos_est_gcl_t *gcl, uint32_t listLen, bool hwList)
{
    assert(gcl != NULL);
    assert(gcl->opList != NULL);
    uint8_t dbgm = 0;
    uint32_t data, i;
    enet_qos_est_gate_op_t *gateOp;
    status_t rc;

    if (hwList == true)
    {
        dbgm = 1;
    }

    /* LLR */
    rc = ENET_QOS_EstReadWord(base, (uint32_t)kENET_QOS_Ets_llr, &data, 1, dbgm);
    if (rc != kStatus_Success)
    {
        return rc;
    }

    gcl->numEntries = data;

    if (gcl->numEntries > listLen)
    {
        return kStatus_ENET_QOS_Est_InvalidParameter;
    }

    /* BTR High */
    rc = ENET_QOS_EstReadWord(base, (uint32_t)kENET_QOS_Ets_btr_high, &data, 1, dbgm);
    if (rc != kStatus_Success)
    {
        return rc;
    }

    gcl->baseTime = (uint64_t)data << 32U;

    /* BTR Low */
    rc = ENET_QOS_EstReadWord(base, (uint32_t)kENET_QOS_Ets_btr_low, &data, 1, dbgm);
    if (rc != kStatus_Success)
    {
        return rc;
    }

    gcl->baseTime |= data;

    /* CTR High */
    rc = ENET_QOS_EstReadWord(base, (uint32_t)kENET_QOS_Ets_ctr_high, &data, 1, dbgm);
    if (rc != kStatus_Success)
    {
        return rc;
    }

    gcl->cycleTime = (uint64_t)data << 32U;

    /* CTR Low */
    rc = ENET_QOS_EstReadWord(base, (uint32_t)kENET_QOS_Ets_ctr_low, &data, 1, dbgm);
    if (rc != kStatus_Success)
    {
        return rc;
    }

    gcl->cycleTime |= data;

    /* TER */
    rc = ENET_QOS_EstReadWord(base, (uint32_t)kENET_QOS_Ets_ter, &data, 1, dbgm);
    if (rc != kStatus_Success)
    {
        return rc;
    }

    gcl->extTime = data;

    gateOp = gcl->opList;

    for (i = 0; i < gcl->numEntries; i++)
    {
        rc = ENET_QOS_EstReadWord(base, i, &data, 0, dbgm);
        if (rc != kStatus_Success)
        {
            return rc;
        }

        gateOp->interval = data & (EST_MAX_INTERVAL);
        gateOp->gate     = data >> ENET_QOS_EST_WID;
        gateOp++;
    }

    return kStatus_Success;
}

/*!
 * brief Read flexible rx parser configuration at specified index.
 *
 * This function is used to read flexible rx parser configuration at specified index.
 *
 * param base  ENET peripheral base address..
 * param rxpConfig The rx parser configuration pointer.
 * param entryIndex The rx parser entry index to read, start from 0.
 * retval kStatus_Success Configure rx parser success.
 * retval kStatus_ENET_QOS_Timeout Poll status flag timeout.
 */
status_t ENET_QOS_ReadRxParser(ENET_QOS_Type *base, enet_qos_rxp_config_t *rxpConfig, uint16_t entryIndex)
{
    assert(rxpConfig != NULL);
    assert(entryIndex < ENET_QOS_RXP_ENTRY_COUNT);

    uint32_t *dataPtr;
    uint8_t entrySize = sizeof(enet_qos_rxp_config_t) / sizeof(uint32_t);
    uint32_t value    = 0U;
    status_t result   = kStatus_Success;

    /* Wait hardware not busy */
    result = ENET_QOS_PollStatusFlag(&(base->MTL_RXP_INDIRECT_ACC_CONTROL_STATUS),
                                     ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY_MASK, 0U);
    if (kStatus_Success != result)
    {
        return result;
    }

    for (uint8_t i = 0; i < entrySize; i++)
    {
        /* Read address. */
        value = ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_ADDR((uint32_t)entrySize * entryIndex + i);

        /* Issue read command. */
        value &= ~ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_WRRDN_MASK;
        base->MTL_RXP_INDIRECT_ACC_CONTROL_STATUS = value;

        /* Start Read */
        value |= ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY_MASK;
        base->MTL_RXP_INDIRECT_ACC_CONTROL_STATUS = value;

        /* Wait hardware not busy */
        result = ENET_QOS_PollStatusFlag(&base->MTL_RXP_INDIRECT_ACC_CONTROL_STATUS,
                                         ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY_MASK, 0U);
        if (kStatus_Success != result)
        {
            return result;
        }

        dataPtr = (uint32_t *)(void *)&rxpConfig[entryIndex];
        dataPtr = &dataPtr[i];
        /* Read data */
        *dataPtr = base->MTL_RXP_INDIRECT_ACC_DATA;
    }

    return result;
}

/*!
 * brief Configure flexible rx parser.
 *
 * This function is used to configure the flexible rx parser table.
 *
 * param base  ENET peripheral base address..
 * param rxpConfig The rx parser configuration pointer.
 * param entryCount The rx parser entry count.
 * retval kStatus_Success Configure rx parser success.
 * retval kStatus_ENET_QOS_Timeout Poll status flag timeout.
 */
status_t ENET_QOS_ConfigureRxParser(ENET_QOS_Type *base, enet_qos_rxp_config_t *rxpConfig, uint16_t entryCount)
{
    assert(rxpConfig != NULL);
    assert(entryCount <= ENET_QOS_RXP_ENTRY_COUNT);

    uint32_t *dataPtr;
    uint32_t entrySize = sizeof(enet_qos_rxp_config_t) / sizeof(uint32_t);
    uint32_t value     = 0U;
    status_t result    = kStatus_Success;
    bool enableRx      = false;

    /* Disable the MAC rx. */
    if (0U != (base->MAC_CONFIGURATION & ENET_QOS_MAC_CONFIGURATION_RE_MASK))
    {
        base->MAC_CONFIGURATION &= ~ENET_QOS_MAC_CONFIGURATION_RE_MASK;
        enableRx = true;
    }

    /* Disable frame parser. */
    result = ENET_QOS_EnableRxParser(base, false);

    if (kStatus_Success != result)
    {
        return result;
    }

    for (uint8_t count = 0; count < entryCount; count++)
    {
        for (uint8_t i = 0; i < entrySize; i++)
        {
            /* Wait hardware not busy */
            result = ENET_QOS_PollStatusFlag(&base->MTL_RXP_INDIRECT_ACC_CONTROL_STATUS,
                                             ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY_MASK, 0U);
            if (kStatus_Success != result)
            {
                return result;
            }

            dataPtr = (uint32_t *)(void *)&rxpConfig[count];
            dataPtr = &dataPtr[i];

            /* Write data before issue write command */
            base->MTL_RXP_INDIRECT_ACC_DATA = *dataPtr;

            /* Write address and issue write command */
            value = ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_ADDR(entrySize * count + i);
            // base->MTL_RXP_INDIRECT_ACC_CONTROL_STATUS = value;

            value |= ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_WRRDN_MASK;
            base->MTL_RXP_INDIRECT_ACC_CONTROL_STATUS = value;

            /* Start write */
            value |= ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY_MASK;
            base->MTL_RXP_INDIRECT_ACC_CONTROL_STATUS = value;
        }
    }

    /* Wait hardware not busy */
    result = ENET_QOS_PollStatusFlag(&(base->MTL_RXP_INDIRECT_ACC_CONTROL_STATUS),
                                     ENET_QOS_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY_MASK, 0U);
    if (kStatus_Success != result)
    {
        return result;
    }

    /* Program NVE and NPE. */
    value = base->MTL_RXP_CONTROL_STATUS;
    value &= ~(ENET_QOS_MTL_RXP_CONTROL_STATUS_NVE_MASK | ENET_QOS_MTL_RXP_CONTROL_STATUS_NPE_MASK);

    value |= ENET_QOS_MTL_RXP_CONTROL_STATUS_NPE((uint32_t)entryCount - 1U);
    if (entryCount < 3U)
    {
        value |= ENET_QOS_MTL_RXP_CONTROL_STATUS_NVE(2U);
    }
    else
    {
        value |= ENET_QOS_MTL_RXP_CONTROL_STATUS_NVE((uint32_t)entryCount - 1U);
    }

    base->MTL_RXP_CONTROL_STATUS = value;

    /* Enable frame parser. */
    result = ENET_QOS_EnableRxParser(base, true);

    /* Enable Receive */
    if (enableRx)
    {
        base->MAC_CONFIGURATION |= ENET_QOS_MAC_CONFIGURATION_RE_MASK;
    }

    return result;
}

/*!
 * brief Gets statistical data in transfer.
 *
 * param base  ENET_QOS peripheral base address.
 * param statistics The statistics structure pointer.
 */
void ENET_QOS_GetStatistics(ENET_QOS_Type *base, enet_qos_transfer_stats_t *statistics)
{
    /* Rx statistics */
    statistics->statsRxFrameCount      = base->MAC_RX_PACKETS_COUNT_GOOD_BAD;
    statistics->statsRxCrcErr          = base->MAC_RX_CRC_ERROR_PACKETS;
    statistics->statsRxAlignErr        = base->MAC_RX_ALIGNMENT_ERROR_PACKETS;
    statistics->statsRxLengthErr       = base->MAC_RX_LENGTH_ERROR_PACKETS;
    statistics->statsRxFifoOverflowErr = base->MAC_RX_FIFO_OVERFLOW_PACKETS;

    /* Tx statistics */
    statistics->statsTxFrameCount      = base->MAC_TX_PACKET_COUNT_GOOD_BAD;
    statistics->statsTxFifoUnderRunErr = base->MAC_TX_UNDERFLOW_ERROR_PACKETS;
}

/*!
 * brief The ENET IRQ handler.
 *
 * param base  ENET peripheral base address.
 * param handle The ENET handler pointer.
 */
void ENET_QOS_CommonIRQHandler(ENET_QOS_Type *base, enet_qos_handle_t *handle)
{
    /* Check for the interrupt source type. */
    /* DMA CHANNEL 0. */
    if ((base->DMA_INTERRUPT_STATUS & ENET_QOS_DMA_INTERRUPT_STATUS_DC0IS_MASK) != 0U)
    {
        uint32_t flag = base->DMA_CH[0].DMA_CHX_STAT;
        if ((flag & ENET_QOS_DMA_CHX_STAT_RI_MASK) != 0U)
        {
            base->DMA_CH[0].DMA_CHX_STAT = ENET_QOS_DMA_CHX_STAT_RI_MASK | ENET_QOS_DMA_CHX_STAT_NIS_MASK;
            if (handle->callback != NULL)
            {
                handle->callback(base, handle, kENET_QOS_RxIntEvent, 0, handle->userData);
            }
        }
        if ((flag & ENET_QOS_DMA_CHX_STAT_TI_MASK) != 0U)
        {
            base->DMA_CH[0].DMA_CHX_STAT = ENET_QOS_DMA_CHX_STAT_TI_MASK | ENET_QOS_DMA_CHX_STAT_NIS_MASK;
            ENET_QOS_ReclaimTxDescriptor(base, handle, 0);
        }
    }

    /* DMA CHANNEL 1. */
    if ((base->DMA_INTERRUPT_STATUS & ENET_QOS_DMA_INTERRUPT_STATUS_DC1IS_MASK) != 0U)
    {
        uint32_t flag = base->DMA_CH[1].DMA_CHX_STAT;
        if ((flag & ENET_QOS_DMA_CHX_STAT_RI_MASK) != 0U)
        {
            base->DMA_CH[1].DMA_CHX_STAT = ENET_QOS_DMA_CHX_STAT_RI_MASK | ENET_QOS_DMA_CHX_STAT_NIS_MASK;
            if (handle->callback != NULL)
            {
                handle->callback(base, handle, kENET_QOS_RxIntEvent, 1, handle->userData);
            }
        }
        if ((flag & ENET_QOS_DMA_CHX_STAT_TI_MASK) != 0U)
        {
            base->DMA_CH[1].DMA_CHX_STAT = ENET_QOS_DMA_CHX_STAT_TI_MASK | ENET_QOS_DMA_CHX_STAT_NIS_MASK;
            ENET_QOS_ReclaimTxDescriptor(base, handle, 1);
        }
    }

    /* DMA CHANNEL 2. */
    if ((base->DMA_INTERRUPT_STATUS & ENET_QOS_DMA_INTERRUPT_STATUS_DC2IS_MASK) != 0U)
    {
        uint32_t flag = base->DMA_CH[2].DMA_CHX_STAT;
        if ((flag & ENET_QOS_DMA_CHX_STAT_RI_MASK) != 0U)
        {
            base->DMA_CH[2].DMA_CHX_STAT = ENET_QOS_DMA_CHX_STAT_RI_MASK | ENET_QOS_DMA_CHX_STAT_NIS_MASK;
            if (handle->callback != NULL)
            {
                handle->callback(base, handle, kENET_QOS_RxIntEvent, 2, handle->userData);
            }
        }
        if ((flag & ENET_QOS_DMA_CHX_STAT_TI_MASK) != 0U)
        {
            base->DMA_CH[2].DMA_CHX_STAT = ENET_QOS_DMA_CHX_STAT_TI_MASK | ENET_QOS_DMA_CHX_STAT_NIS_MASK;
            ENET_QOS_ReclaimTxDescriptor(base, handle, 2);
        }
    }

    /* DMA CHANNEL 3. */
    if ((base->DMA_INTERRUPT_STATUS & ENET_QOS_DMA_INTERRUPT_STATUS_DC3IS_MASK) != 0U)
    {
        uint32_t flag = base->DMA_CH[3].DMA_CHX_STAT;
        if ((flag & ENET_QOS_DMA_CHX_STAT_RI_MASK) != 0U)
        {
            base->DMA_CH[3].DMA_CHX_STAT = ENET_QOS_DMA_CHX_STAT_RI_MASK | ENET_QOS_DMA_CHX_STAT_NIS_MASK;
            if (handle->callback != NULL)
            {
                handle->callback(base, handle, kENET_QOS_RxIntEvent, 3, handle->userData);
            }
        }
        if ((flag & ENET_QOS_DMA_CHX_STAT_TI_MASK) != 0U)
        {
            base->DMA_CH[3].DMA_CHX_STAT = ENET_QOS_DMA_CHX_STAT_TI_MASK | ENET_QOS_DMA_CHX_STAT_NIS_MASK;
            ENET_QOS_ReclaimTxDescriptor(base, handle, 3);
        }
    }

    /* MAC TIMESTAMP. */
    if ((base->DMA_INTERRUPT_STATUS & ENET_QOS_DMA_INTERRUPT_STATUS_MACIS_MASK) != 0U)
    {
        if ((base->MAC_INTERRUPT_STATUS & ENET_QOS_MAC_INTERRUPT_STATUS_TSIS_MASK) != 0U)
        {
            if (handle->callback != NULL)
            {
                handle->callback(base, handle, kENET_QOS_TimeStampIntEvent, 0, handle->userData);
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}

#if defined(ENET_QOS)
void ENET_QOS_DriverIRQHandler(void);
void ENET_QOS_DriverIRQHandler(void)
{
    s_enetqosIsr(ENET_QOS, s_ENETHandle[0]);
}
#endif

#if defined(CONNECTIVITY__ENET_QOS)
void CONNECTIVITY_EQOS_INT_DriverIRQHandler(void);
void CONNECTIVITY_EQOS_INT_DriverIRQHandler(void)
{
    s_enetqosIsr(CONNECTIVITY__ENET_QOS, s_ENETHandle[0]);
}
#endif
