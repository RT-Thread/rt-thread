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

#include "fsl_enet.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief IPv4 PTP message IP version offset. */
#define ENET_PTP1588_IPVERSION_OFFSET 0x0EU
/*! @brief IPv4 PTP message UDP protocol offset. */
#define ENET_PTP1588_IPV4_UDP_PROTOCOL_OFFSET 0x17U
/*! @brief IPv4 PTP message UDP port offset. */
#define ENET_PTP1588_IPV4_UDP_PORT_OFFSET 0x24U
/*! @brief IPv4 PTP message UDP message type offset. */
#define ENET_PTP1588_IPV4_UDP_MSGTYPE_OFFSET 0x2AU
/*! @brief IPv4 PTP message UDP version offset. */
#define ENET_PTP1588_IPV4_UDP_VERSION_OFFSET 0x2BU
/*! @brief IPv4 PTP message UDP clock id offset. */
#define ENET_PTP1588_IPV4_UDP_CLKID_OFFSET 0x3EU
/*! @brief IPv4 PTP message UDP sequence id offset. */
#define ENET_PTP1588_IPV4_UDP_SEQUENCEID_OFFSET 0x48U
/*! @brief IPv4 PTP message UDP control offset. */
#define ENET_PTP1588_IPV4_UDP_CTL_OFFSET 0x4AU
/*! @brief IPv6 PTP message UDP protocol offset. */
#define ENET_PTP1588_IPV6_UDP_PROTOCOL_OFFSET 0x14U
/*! @brief IPv6 PTP message UDP port offset. */
#define ENET_PTP1588_IPV6_UDP_PORT_OFFSET 0x38U
/*! @brief IPv6 PTP message UDP message type offset. */
#define ENET_PTP1588_IPV6_UDP_MSGTYPE_OFFSET 0x3EU
/*! @brief IPv6 PTP message UDP version offset. */
#define ENET_PTP1588_IPV6_UDP_VERSION_OFFSET 0x3FU
/*! @brief IPv6 PTP message UDP clock id offset. */
#define ENET_PTP1588_IPV6_UDP_CLKID_OFFSET 0x52U
/*! @brief IPv6 PTP message UDP sequence id offset. */
#define ENET_PTP1588_IPV6_UDP_SEQUENCEID_OFFSET 0x5CU
/*! @brief IPv6 PTP message UDP control offset. */
#define ENET_PTP1588_IPV6_UDP_CTL_OFFSET 0x5EU
/*! @brief PTPv2 message Ethernet packet type offset. */
#define ENET_PTP1588_ETHL2_PACKETTYPE_OFFSET 0x0CU
/*! @brief PTPv2 message Ethernet message type offset. */
#define ENET_PTP1588_ETHL2_MSGTYPE_OFFSET 0x0EU
/*! @brief PTPv2 message Ethernet version type offset. */
#define ENET_PTP1588_ETHL2_VERSION_OFFSET 0X0FU
/*! @brief PTPv2 message Ethernet clock id offset. */
#define ENET_PTP1588_ETHL2_CLOCKID_OFFSET 0x22
/*! @brief PTPv2 message Ethernet sequence id offset. */
#define ENET_PTP1588_ETHL2_SEQUENCEID_OFFSET 0x2c
/*! @brief Packet type Ethernet IEEE802.3 for PTPv2. */
#define ENET_ETHERNETL2 0x88F7U
/*! @brief Packet type IPv4. */
#define ENET_IPV4 0x0800U
/*! @brief Packet type IPv6. */
#define ENET_IPV6 0x86ddU
/*! @brief Packet type VLAN. */
#define ENET_8021QVLAN 0x8100U
/*! @brief UDP protocol type. */
#define ENET_UDPVERSION 0x0011U
/*! @brief Packet IP version IPv4. */
#define ENET_IPV4VERSION 0x0004U
/*! @brief Packet IP version IPv6. */
#define ENET_IPV6VERSION 0x0006U

/*! @brief Defines 10^9 nanosecond. */
#define ENET_NANOSECS_ONESECOND (1000000000U)
/*! @brief Defines 10^6 microsecond.*/
#define ENET_MICRSECS_ONESECOND (1000000U)

/*! @brief Rx buffer LSB ignore bits. */
#define ENET_RXBUFF_IGNORELSB_BITS (2U)
/*! @brief ENET FIFO size unit. */
#define ENET_FIFOSIZE_UNIT (256U)
/*! @brief ENET half-dulpex default IPG. */
#define ENET_HALFDUPLEX_DEFAULTIPG (4U)
/*! @breif ENET miminum ring length. */
#define ENET_MIN_RINGLEN (4U)
/*! @breif ENET wakeup filter numbers. */
#define ENET_WAKEUPFILTER_NUM (8U)
/*! @breif Requried systime timer frequency. */
#define ENET_SYSTIME_REQUIRED_CLK_MHZ (50U)
/*! @brief Ethernet VLAN tag length. */
#define ENET_FRAME_VLAN_TAGLEN 4U

/*! @brief AVB TYPE */
#define ENET_AVBTYPE 0x22F0U
#define ENET_HEAD_TYPE_OFFSET (12)
#define ENET_HEAD_AVBTYPE_OFFSET (16)

/*! @brief Defines the macro for converting constants from host byte order to network byte order. */
#define ENET_HTONS(n) __REV16(n)
#define ENET_HTONL(n) __REV(n)
#define ENET_NTOHS(n) __REV16(n)
#define ENET_NTOHL(n) __REV(n)

/* Typedef for interrupt handler. */
typedef void (*enet_isr_t)(ENET_Type *base, enet_handle_t *handle);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the ENET instance from peripheral base address.
 *
 * @param base ENET peripheral base address.
 * @return ENET instance.
 */
uint32_t ENET_GetInstance(ENET_Type *base);

/*!
 * @brief Increase the index in the ring.
 *
 * @param index The current index.
 * @param max The size.
 * @return the increased index.
 */
static uint32_t ENET_IncreaseIndex(uint32_t index, uint32_t max);

/*!
 * @brief Set ENET system configuration.
 *  This function reset the ethernet module and set the phy selection.
 *  It should be called before any other ethernet operation.
 *
 * @param miiMode  The MII/RMII mode for interface between the phy and ethernet.
 */
static void ENET_SetSYSControl(enet_mii_mode_t miiMode);

/*!
 * @brief Set ENET DMA controller with the configuration.
 *
 * @param base ENET peripheral base address.
 * @param config ENET Mac configuration.
 */
static void ENET_SetDMAControl(ENET_Type *base, const enet_config_t *config);

/*!
 * @brief Set ENET MAC controller with the configuration.
 *
 * @param base ENET peripheral base address.
 * @param config ENET Mac configuration.
 * @param macAddr ENET six-byte mac address.
 */
static void ENET_SetMacControl(ENET_Type *base, const enet_config_t *config, uint8_t *macAddr);
/*!
 * @brief Set ENET MTL with the configuration.
 *
 * @param base ENET peripheral base address.
 * @param config ENET Mac configuration.
 */
static void ENET_SetMTL(ENET_Type *base, const enet_config_t *config);

/*!
 * @brief Set ENET DMA transmit buffer descriptors for one channel.
 *
 * @param base ENET peripheral base address.
 * @param bufferConfig ENET buffer configuration.
 * @param intTxEnable tx interrupt enable.
 * @param channel The channel number, 0 , 1.
 */
static status_t ENET_TxDescriptorsInit(ENET_Type *base,
                                       const enet_buffer_config_t *bufferConfig,
                                       bool intTxEnable,
                                       uint8_t channel);

/*!
 * @brief Set ENET DMA receive buffer descriptors for one channel.
 *
 * @param base ENET peripheral base address.
 * @param bufferConfig ENET buffer configuration.
 * @param intRxEnable tx interrupt enable.
 * @param channel The channel number, 0 , 1.
 * @param doubleBuffEnable Two buffers are enabled.
 */
static status_t ENET_RxDescriptorsInit(ENET_Type *base,
                                       const enet_buffer_config_t *bufferConfig,
                                       bool intRxEnable,
                                       uint8_t channel,
                                       bool doubleBuffEnable);

/*!
 * @brief Set ENET get transmit ring descriptors.
 *
 * @param data The ENET data to be transfered.
 * @param handle ENET handler.
 */
static uint8_t ENET_GetTxRingId(uint8_t *data, enet_handle_t *handle);

#ifdef ENET_PTP1588FEATURE_REQUIRED
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
static void ENET_SetPtp1588(ENET_Type *base, const enet_config_t *config, uint32_t refClk_Hz);

/*!
 * @brief Parses the ENET frame for time-stamp process of PTP 1588 frame.
 *
 * @param data  The ENET read data for frame parse.
 * @param ptpTsData The ENET PTP message and time-stamp data pointer.
 * @param isFastEnabled The fast parse flag.
 *        - true , Fast processing, only check if this is a PTP message.
 *        - false, Store the PTP message data after check the PTP message.
 */
static bool ENET_Ptp1588ParseFrame(uint8_t *data, enet_ptp_time_data_t *ptpTsData, bool isFastEnabled);

/*!
 * @brief Updates the new PTP 1588 time-stamp to the time-stamp buffer ring.
 *
 * @param ptpTsDataRing The PTP message and time-stamp data ring pointer.
 * @param ptpTimeData   The new PTP 1588 time-stamp data pointer.
 */
static status_t ENET_Ptp1588UpdateTimeRing(enet_ptp_time_data_ring_t *ptpTsDataRing, enet_ptp_time_data_t *ptpTimeData);

/*!
 * @brief Search up the right PTP 1588 time-stamp from the time-stamp buffer ring.
 *
 * @param ptpTsDataRing The PTP message and time-stamp data ring pointer.
 * @param ptpTimeData   The find out right PTP 1588 time-stamp data pointer with the specific PTP message.
 */
static status_t ENET_Ptp1588SearchTimeRing(enet_ptp_time_data_ring_t *ptpTsDataRing, enet_ptp_time_data_t *ptpTimedata);

/*!
 * @brief Store the receive time-stamp for event PTP frame in the time-stamp buffer ring.
 *
 * @param base   ENET peripheral base address.
 * @param handle ENET handler.
 * @param rxDesc The ENET receive descriptor pointer.
 * @param channel The rx channel.
 * @param ptpTimeData The PTP 1588 time-stamp data pointer.
 */
static status_t ENET_StoreRxFrameTime(ENET_Type *base,
                                      enet_handle_t *handle,
                                      enet_rx_bd_struct_t *rxDesc,
                                      uint8_t channel,
                                      enet_ptp_time_data_t *ptpTimeData);
#endif /* ENET_PTP1588FEATURE_REQUIRED */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to enet handles for each instance. */
static enet_handle_t *s_ENETHandle[FSL_FEATURE_SOC_LPC_ENET_COUNT] = {NULL};
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to enet clocks for each instance. */
const clock_ip_name_t s_enetClock[FSL_FEATURE_SOC_LPC_ENET_COUNT] = ETH_CLOCKS;
#endif /*  FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointers to enet bases for each instance. */
static ENET_Type *const s_enetBases[] = ENET_BASE_PTRS;

/*! @brief Pointers to enet IRQ number for each instance. */
static const IRQn_Type s_enetIrqId[] = ENET_IRQS;

/* ENET ISR for transactional APIs. */
static enet_isr_t s_enetIsr;
/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t ENET_IncreaseIndex(uint32_t index, uint32_t max)
{
    /* Increase the index. */
    index++;
    if (index >= max)
    {
        index = 0;
    }
    return index;
}

static void ENET_SetSYSControl(enet_mii_mode_t miiMode)
{
    /* Reset first. */
    SYSCON->PRESETCTRL[2] = SYSCON_PRESETCTRL_ETH_RST_MASK;
    SYSCON->PRESETCTRL[2] &= ~SYSCON_PRESETCTRL_ETH_RST_MASK;
    /* Set MII/RMII before the peripheral ethernet dma reset. */
    SYSCON->ETHPHYSEL = (SYSCON->ETHPHYSEL & ~SYSCON_ETHPHYSEL_PHY_SEL_MASK) | SYSCON_ETHPHYSEL_PHY_SEL(miiMode);
}

static void ENET_SetDMAControl(ENET_Type *base, const enet_config_t *config)
{
    assert(config);

    uint8_t index;
    uint32_t reg;
    uint32_t burstLen;

    /* Reset first and wait for the complete
     * The reset bit will automatically be cleared after complete. */
    base->DMA_MODE |= ENET_DMA_MODE_SWR_MASK;
    while (base->DMA_MODE & ENET_DMA_MODE_SWR_MASK)
    {
    }

    /* Set the burst length. */
    for (index = 0; index < ENET_RING_NUM_MAX; index++)
    {
        burstLen = kENET_BurstLen1;
        if (config->multiqueueCfg)
        {
            burstLen = config->multiqueueCfg->burstLen;
        }
        base->DMA_CH[index].DMA_CHX_CTRL = burstLen & ENET_DMA_CH_DMA_CHX_CTRL_PBLx8_MASK;

        reg = base->DMA_CH[index].DMA_CHX_TX_CTRL & ~ENET_DMA_CH_DMA_CHX_TX_CTRL_TxPBL_MASK;
        base->DMA_CH[index].DMA_CHX_TX_CTRL = reg | ENET_DMA_CH_DMA_CHX_TX_CTRL_TxPBL(burstLen & 0x3F);

        reg = base->DMA_CH[index].DMA_CHX_RX_CTRL & ~ENET_DMA_CH_DMA_CHX_RX_CTRL_RxPBL_MASK;
        base->DMA_CH[index].DMA_CHX_RX_CTRL = reg | ENET_DMA_CH_DMA_CHX_RX_CTRL_RxPBL(burstLen & 0x3F);
    }
}

static void ENET_SetMTL(ENET_Type *base, const enet_config_t *config)
{
    assert(config);

    uint32_t txqOpreg = 0;
    uint32_t rxqOpReg = 0;
    enet_multiqueue_config_t *multiqCfg = config->multiqueueCfg;
    uint8_t index;

    /* Set transmit operation mode. */
    if (config->specialControl & kENET_StoreAndForward)
    {
        txqOpreg = ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TSF_MASK;
        rxqOpReg = ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RSF_MASK;
    }
    txqOpreg |= ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_FTQ_MASK |
                ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TQS(ENET_MTL_TXFIFOSIZE / ENET_FIFOSIZE_UNIT - 1);
    base->MTL_QUEUE[0].MTL_TXQX_OP_MODE = txqOpreg | ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TXQEN(2);
    base->MTL_QUEUE[1].MTL_TXQX_OP_MODE = txqOpreg;

    /* Set receive operation mode. */
    rxqOpReg |= ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_FUP_MASK |
                ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RQS(ENET_MTL_RXFIFOSIZE / ENET_FIFOSIZE_UNIT - 1);
    base->MTL_QUEUE[0].MTL_RXQX_OP_MODE = rxqOpReg;

    /* Set the schedule/arbitration(set for multiple queues). */
    if (multiqCfg)
    {
        base->MTL_OP_MODE = ENET_MTL_OP_MODE_SCHALG(multiqCfg->mtltxSche) | ENET_MTL_OP_MODE_RAA(multiqCfg->mtlrxSche);
        /* Set the rx queue mapping to dma channel. */
        base->MTL_RXQ_DMA_MAP = multiqCfg->mtlrxQuemap;
        /* Set the tx/rx queue operation mode for multi-queue. */
        base->MTL_QUEUE[1].MTL_TXQX_OP_MODE |= ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TXQEN(2);
        base->MTL_QUEUE[1].MTL_RXQX_OP_MODE = rxqOpReg;

        /* Set the tx/rx queue weight. */
        for (index = 0; index < ENET_RING_NUM_MAX; index++)
        {
            base->MTL_QUEUE[index].MTL_TXQX_QNTM_WGHT = multiqCfg->txqueweight[index];
            base->MTL_QUEUE[index].MTL_RXQX_CTRL = ENET_MTL_QUEUE_MTL_RXQX_CTRL_RXQ_WEGT(multiqCfg->rxqueweight[index]);
        }
    }
}

static void ENET_SetMacControl(ENET_Type *base, const enet_config_t *config, uint8_t *macAddr)
{
    assert(config);

    uint32_t reg = 0;

    /* Set Macaddr */
    /* The dma channel 0 is set as to which the rx packet
     * whose DA matches the MAC address content is routed. */
    if (macAddr)
    {
        ENET_SetMacAddr(base, macAddr);
    }

    /* Set the receive filter. */
    reg = ENET_MAC_FRAME_FILTER_PR(!!(config->specialControl & kENET_PromiscuousEnable)) |
          ENET_MAC_FRAME_FILTER_DBF(!!(config->specialControl & kENET_BroadCastRxDisable)) |
          ENET_MAC_FRAME_FILTER_PM(!!(config->specialControl & kENET_MulticastAllEnable));
    base->MAC_FRAME_FILTER = reg;
    /* Flow control. */
    if (config->specialControl & kENET_FlowControlEnable)
    {
        base->MAC_RX_FLOW_CTRL = ENET_MAC_RX_FLOW_CTRL_RFE_MASK | ENET_MAC_RX_FLOW_CTRL_UP_MASK;
        base->MAC_TX_FLOW_CTRL_Q[0] = ENET_MAC_TX_FLOW_CTRL_Q_PT(config->pauseDuration);
        base->MAC_TX_FLOW_CTRL_Q[1] = ENET_MAC_TX_FLOW_CTRL_Q_PT(config->pauseDuration);
    }

    /* Set the 1us ticket. */
    reg = CLOCK_GetFreq(kCLOCK_CoreSysClk) / ENET_MICRSECS_ONESECOND - 1;
    base->MAC_1US_TIC_COUNTR = ENET_MAC_1US_TIC_COUNTR_TIC_1US_CNTR(reg);

    /* Set the speed and duplex. */
    reg = ENET_MAC_CONFIG_ECRSFD_MASK | ENET_MAC_CONFIG_PS_MASK | ENET_MAC_CONFIG_DM(config->miiDuplex) |
          ENET_MAC_CONFIG_FES(config->miiSpeed) |
          ENET_MAC_CONFIG_S2KP(!!(config->specialControl & kENET_8023AS2KPacket));
    if (config->miiDuplex == kENET_MiiHalfDuplex)
    {
        reg |= ENET_MAC_CONFIG_IPG(ENET_HALFDUPLEX_DEFAULTIPG);
    }
    base->MAC_CONFIG = reg;

    /* Enable channel. */
    base->MAC_RXQ_CTRL[0] = ENET_MAC_RXQ_CTRL_RXQ0EN(1) | ENET_MAC_RXQ_CTRL_RXQ1EN(1);
}

static status_t ENET_TxDescriptorsInit(ENET_Type *base,
                                       const enet_buffer_config_t *bufferConfig,
                                       bool intTxEnable,
                                       uint8_t channel)
{
    uint16_t j;
    enet_tx_bd_struct_t *txbdPtr;
    uint32_t control = intTxEnable ? ENET_TXDESCRIP_RD_IOC_MASK : 0;
    const enet_buffer_config_t *buffCfg = bufferConfig;

    if (!buffCfg)
    {
        return kStatus_InvalidArgument;
    }

    /* Check the ring length. */
    if (buffCfg->txRingLen < ENET_MIN_RINGLEN)
    {
        return kStatus_InvalidArgument;
    }
    /* Set the tx descriptor start/tail pointer, shall be word aligned. */
    base->DMA_CH[channel].DMA_CHX_TXDESC_LIST_ADDR =
        (uint32_t)buffCfg->txDescStartAddrAlign & ENET_DMA_CH_DMA_CHX_TXDESC_LIST_ADDR_STL_MASK;
    base->DMA_CH[channel].DMA_CHX_TXDESC_TAIL_PTR =
        (uint32_t)buffCfg->txDescTailAddrAlign & ENET_DMA_CH_DMA_CHX_TXDESC_LIST_ADDR_STL_MASK;
    /* Set the tx ring length. */
    base->DMA_CH[channel].DMA_CHX_TXDESC_RING_LENGTH =
        (uint16_t)(buffCfg->txRingLen - 1) & ENET_DMA_CH_DMA_CHX_TXDESC_RING_LENGTH_TDRL_MASK;

    /* Init the txbdPtr to the transmit descriptor start address. */
    txbdPtr = (enet_tx_bd_struct_t *)(buffCfg->txDescStartAddrAlign);
    for (j = 0; j < buffCfg->txRingLen; j++)
    {
        txbdPtr->buff1Addr = 0;
        txbdPtr->buff2Addr = 0;
        txbdPtr->buffLen = control;
        txbdPtr->controlStat = 0;
        txbdPtr++;
    }

    return kStatus_Success;
}

static status_t ENET_RxDescriptorsInit(
    ENET_Type *base, const enet_buffer_config_t *bufferConfig, bool intRxEnable, uint8_t channel, bool doubleBuffEnable)
{
    uint16_t j;
    uint32_t reg;
    enet_rx_bd_struct_t *rxbdPtr;
    uint16_t index;
    const enet_buffer_config_t *buffCfg = bufferConfig;
    uint32_t control = ENET_RXDESCRIP_WR_OWN_MASK | ENET_RXDESCRIP_RD_BUFF1VALID_MASK;

    if (!buffCfg)
    {
        return kStatus_InvalidArgument;
    }

    if (intRxEnable)
    {
        control |= ENET_RXDESCRIP_RD_IOC_MASK;
    }

    if (doubleBuffEnable)
    {
        control |= ENET_RXDESCRIP_RD_BUFF2VALID_MASK;
    }

    /* Check the ring length. */
    if (buffCfg->rxRingLen < ENET_MIN_RINGLEN)
    {
        return kStatus_InvalidArgument;
    }

    /* Set the rx descriptor start/tail pointer, shall be word aligned. */
    base->DMA_CH[channel].DMA_CHX_RXDESC_LIST_ADDR =
        (uint32_t)buffCfg->rxDescStartAddrAlign & ENET_DMA_CH_DMA_CHX_RXDESC_LIST_ADDR_SRL_MASK;
    base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR =
        (uint32_t)buffCfg->rxDescTailAddrAlign & ENET_DMA_CH_DMA_CHX_RXDESC_LIST_ADDR_SRL_MASK;
    base->DMA_CH[channel].DMA_CHX_RXDESC_RING_LENGTH =
        (uint16_t)(buffCfg->rxRingLen - 1) & ENET_DMA_CH_DMA_CHX_RXDESC_RING_LENGTH_RDRL_MASK;
    reg = base->DMA_CH[channel].DMA_CHX_RX_CTRL & ~ENET_DMA_CH_DMA_CHX_RX_CTRL_RBSZ_MASK;
    reg |= ENET_DMA_CH_DMA_CHX_RX_CTRL_RBSZ(buffCfg->rxBuffSizeAlign >> ENET_RXBUFF_IGNORELSB_BITS);
    base->DMA_CH[channel].DMA_CHX_RX_CTRL = reg;

    /* Init the rxbdPtr to the receive descriptor start address. */
    rxbdPtr = (enet_rx_bd_struct_t *)(buffCfg->rxDescStartAddrAlign);

    for (j = 0; j < buffCfg->rxRingLen; j++)
    {
        if (doubleBuffEnable)
        {
            index = 2 * j;
        }
        else
        {
            index = j;
        }
        rxbdPtr->buff1Addr = *(buffCfg->rxBufferStartAddr + index);
        /* The second buffer is set with 0 because it is not required for normal case. */
        if (doubleBuffEnable)
        {
            rxbdPtr->buff2Addr = *(buffCfg->rxBufferStartAddr + index + 1);
        }
        else
        {
            rxbdPtr->buff2Addr = 0;
        }

        /* Set the valid and DMA own flag.*/
        rxbdPtr->control = control;
        rxbdPtr++;
    }

    return kStatus_Success;
}

static uint8_t ENET_GetTxRingId(uint8_t *data, enet_handle_t *handle)
{
    /* Defuault use the queue/ring 0. */
    uint8_t ringId = 0;

    if (handle->multiQueEnable)
    {
        /* Parse the frame and choose the queue id for different avb frames
         *  AVB Class frame in queue 1.
         *  non-AVB frame in queue 0.
         */
        if ((*(uint16_t *)(data + ENET_HEAD_TYPE_OFFSET) == ENET_HTONS(ENET_8021QVLAN)) &&
            ((*(uint16_t *)(data + ENET_HEAD_AVBTYPE_OFFSET)) == ENET_HTONS(ENET_AVBTYPE)))
        {
            /* AVBTP stream data frame. */
            ringId = 1;
        }
    }

    return ringId;
}

#ifdef ENET_PTP1588FEATURE_REQUIRED
static void ENET_SetPtp1588(ENET_Type *base, const enet_config_t *config, uint32_t refClk_Hz)
{
    assert(config);
    assert(config->ptpConfig);
    assert(refClk_Hz);

    uint32_t control;
    enet_ptp_config_t *ptpConfig = config->ptpConfig;

    /* Clear the timestamp interrupt first. */
    base->MAC_INTR_EN &= ~ENET_MAC_INTR_EN_TSIE_MASK;

    if (ptpConfig->fineUpdateEnable)
    {
        base->MAC_TIMESTAMP_CTRL |= ENET_MAC_TIMESTAMP_CTRL_TSCFUPDT_MASK;
        /* Set the initial added value for the fine update. */
        control = 100000000U / (refClk_Hz / ENET_MICRSECS_ONESECOND / ENET_SYSTIME_REQUIRED_CLK_MHZ);
        base->MAC_SYS_TIMESTMP_ADDEND = control;
        base->MAC_TIMESTAMP_CTRL |= ENET_MAC_TIMESTAMP_CTRL_TADDREG_MASK;
        while (base->MAC_TIMESTAMP_CTRL & ENET_MAC_TIMESTAMP_CTRL_TADDREG_MASK)
        {
        }
    }

    /* Enable the IEEE 1588 timestamping and snapshot for event message. */
    control = ENET_MAC_TIMESTAMP_CTRL_TSENA_MASK | ENET_MAC_TIMESTAMP_CTRL_TSIPV4ENA_MASK |
              ENET_MAC_TIMESTAMP_CTRL_TSIPV6ENA_MASK | ENET_MAC_TIMESTAMP_CTRL_TSENALL_MASK |
              ENET_MAC_TIMESTAMP_CTRL_TSEVTENA_MASK | ENET_MAC_TIMESTAMP_CTRL_SNAPTYPSEL_MASK |
              ENET_MAC_TIMESTAMP_CTRL_TSCTRLSSR(ptpConfig->tsRollover);

    if (ptpConfig->ptp1588V2Enable)
    {
        control |= ENET_MAC_TIMESTAMP_CTRL_TSVER2ENA_MASK | ENET_MAC_TIMESTAMP_CTRL_TSIPENA_MASK;
    }

    /* Initialize the sub-second increment register. */
    if (ptpConfig->tsRollover)
    {
        base->MAC_SUB_SCND_INCR = ENET_MAC_SUB_SCND_INCR_SSINC(ENET_NANOSECS_ONESECOND / refClk_Hz);
        base->MAC_SYS_TIME_NSCND_UPD = 0;
    }
    else
    {
        /* round up. */
        uint32_t data = ENET_MAC_SYS_TIME_NSCND_TSSS_MASK / refClk_Hz;
        base->MAC_SUB_SCND_INCR = ENET_MAC_SUB_SCND_INCR_SSINC(data);
        base->MAC_SYS_TIME_NSCND_UPD = 0;
    }
    /* Set the second.*/
    base->MAC_SYS_TIME_SCND_UPD = 0;
    base->MAC_SYS_TIME_HWORD_SCND = 0;

    /* Initialize the system timer. */
    base->MAC_TIMESTAMP_CTRL = control | ENET_MAC_TIMESTAMP_CTRL_TSINIT_MASK;
}

static bool ENET_Ptp1588ParseFrame(uint8_t *data, enet_ptp_time_data_t *ptpTsData, bool isFastEnabled)
{
    assert(data);
    if (!isFastEnabled)
    {
        assert(ptpTsData);
    }

    bool isPtpMsg = false;
    uint8_t *buffer = data;
    uint16_t ptpType;

    /* Check for VLAN frame. */
    if (*(uint16_t *)(buffer + ENET_PTP1588_ETHL2_PACKETTYPE_OFFSET) == ENET_HTONS(ENET_8021QVLAN))
    {
        buffer += ENET_FRAME_VLAN_TAGLEN;
    }

    ptpType = *(uint16_t *)(buffer + ENET_PTP1588_ETHL2_PACKETTYPE_OFFSET);
    switch (ENET_HTONS(ptpType))
    { /* Ethernet layer 2. */
        case ENET_ETHERNETL2:
            if (*(uint8_t *)(buffer + ENET_PTP1588_ETHL2_MSGTYPE_OFFSET) <= kENET_PtpEventMsgType)
            {
                isPtpMsg = true;
                if (!isFastEnabled)
                {
                    /* It's a ptpv2 message and store the ptp header information. */
                    ptpTsData->version = (*(uint8_t *)(buffer + ENET_PTP1588_ETHL2_VERSION_OFFSET)) & 0x0F;
                    ptpTsData->messageType = (*(uint8_t *)(buffer + ENET_PTP1588_ETHL2_MSGTYPE_OFFSET)) & 0x0F;
                    ptpTsData->sequenceId = ENET_HTONS(*(uint16_t *)(buffer + ENET_PTP1588_ETHL2_SEQUENCEID_OFFSET));
                    memcpy((void *)&ptpTsData->sourcePortId[0], (void *)(buffer + ENET_PTP1588_ETHL2_CLOCKID_OFFSET),
                           kENET_PtpSrcPortIdLen);
                }
            }
            break;
        /* IPV4. */
        case ENET_IPV4:
            if ((*(uint8_t *)(buffer + ENET_PTP1588_IPVERSION_OFFSET) >> 4) == ENET_IPV4VERSION)
            {
                if (((*(uint16_t *)(buffer + ENET_PTP1588_IPV4_UDP_PORT_OFFSET)) == ENET_HTONS(kENET_PtpEventPort)) &&
                    (*(uint8_t *)(buffer + ENET_PTP1588_IPV4_UDP_PROTOCOL_OFFSET) == ENET_UDPVERSION))
                {
                    /* Set the PTP message flag. */
                    isPtpMsg = true;
                    if (!isFastEnabled)
                    {
                        /* It's a IPV4 ptp message and store the ptp header information. */
                        ptpTsData->version = (*(uint8_t *)(buffer + ENET_PTP1588_IPV4_UDP_VERSION_OFFSET)) & 0x0F;
                        ptpTsData->messageType = (*(uint8_t *)(buffer + ENET_PTP1588_IPV4_UDP_MSGTYPE_OFFSET)) & 0x0F;
                        ptpTsData->sequenceId =
                            ENET_HTONS(*(uint16_t *)(buffer + ENET_PTP1588_IPV4_UDP_SEQUENCEID_OFFSET));
                        memcpy((void *)&ptpTsData->sourcePortId[0],
                               (void *)(buffer + ENET_PTP1588_IPV4_UDP_CLKID_OFFSET), kENET_PtpSrcPortIdLen);
                    }
                }
            }
            break;
        /* IPV6. */
        case ENET_IPV6:
            if ((*(uint8_t *)(buffer + ENET_PTP1588_IPVERSION_OFFSET) >> 4) == ENET_IPV6VERSION)
            {
                if (((*(uint16_t *)(buffer + ENET_PTP1588_IPV6_UDP_PORT_OFFSET)) == ENET_HTONS(kENET_PtpEventPort)) &&
                    (*(uint8_t *)(buffer + ENET_PTP1588_IPV6_UDP_PROTOCOL_OFFSET) == ENET_UDPVERSION))
                {
                    /* Set the PTP message flag. */
                    isPtpMsg = true;
                    if (!isFastEnabled)
                    {
                        /* It's a IPV6 ptp message and store the ptp header information. */
                        ptpTsData->version = (*(uint8_t *)(buffer + ENET_PTP1588_IPV6_UDP_VERSION_OFFSET)) & 0x0F;
                        ptpTsData->messageType = (*(uint8_t *)(buffer + ENET_PTP1588_IPV6_UDP_MSGTYPE_OFFSET)) & 0x0F;
                        ptpTsData->sequenceId =
                            ENET_HTONS(*(uint16_t *)(buffer + ENET_PTP1588_IPV6_UDP_SEQUENCEID_OFFSET));
                        memcpy((void *)&ptpTsData->sourcePortId[0],
                               (void *)(buffer + ENET_PTP1588_IPV6_UDP_CLKID_OFFSET), kENET_PtpSrcPortIdLen);
                    }
                }
            }
            break;
        default:
            break;
    }
    return isPtpMsg;
}

static status_t ENET_Ptp1588UpdateTimeRing(enet_ptp_time_data_ring_t *ptpTsDataRing, enet_ptp_time_data_t *ptpTimeData)
{
    assert(ptpTsDataRing);
    assert(ptpTsDataRing->ptpTsData);
    assert(ptpTimeData);

    uint16_t usedBuffer = 0;

    /* Check if the buffers ring is full. */
    if (ptpTsDataRing->end >= ptpTsDataRing->front)
    {
        usedBuffer = ptpTsDataRing->end - ptpTsDataRing->front;
    }
    else
    {
        usedBuffer = ptpTsDataRing->size - (ptpTsDataRing->front - ptpTsDataRing->end);
    }

    if (usedBuffer == ptpTsDataRing->size)
    {
        return kStatus_ENET_PtpTsRingFull;
    }

    /* Copy the new data into the buffer. */
    memcpy((ptpTsDataRing->ptpTsData + ptpTsDataRing->end), ptpTimeData, sizeof(enet_ptp_time_data_t));

    /* Increase the buffer pointer to the next empty one. */
    ptpTsDataRing->end = (ptpTsDataRing->end + 1) % ptpTsDataRing->size;

    return kStatus_Success;
}

static status_t ENET_StoreRxFrameTime(ENET_Type *base,
                                      enet_handle_t *handle,
                                      enet_rx_bd_struct_t *rxDesc,
                                      uint8_t channel,
                                      enet_ptp_time_data_t *ptpTimeData)
{
    assert(ptpTimeData);

    uint32_t nanosecond;
    uint32_t nanoOverSize = ENET_NANOSECS_ONESECOND; /* Default use the digital rollover. */

    /* Get transmit time stamp second. */
    nanosecond = rxDesc->reserved | rxDesc->buff1Addr;
    if (!(base->MAC_TIMESTAMP_CTRL & ENET_MAC_TIMESTAMP_CTRL_TSCTRLSSR_MASK))
    {
        /* Binary rollover. */
        nanoOverSize = ENET_MAC_SYS_TIME_NSCND_TSSS_MASK;
    }
    ptpTimeData->timeStamp.second = nanosecond / nanoOverSize;
    ptpTimeData->timeStamp.nanosecond = nanosecond % nanoOverSize;

    /* Store the timestamp to the receive time stamp ring. */
    /* Check if the buffers ring is full. */
    return ENET_Ptp1588UpdateTimeRing(&handle->rxBdRing[channel].rxPtpTsDataRing, ptpTimeData);
}

static status_t ENET_Ptp1588SearchTimeRing(enet_ptp_time_data_ring_t *ptpTsDataRing, enet_ptp_time_data_t *ptpTimedata)
{
    assert(ptpTsDataRing);
    assert(ptpTsDataRing->ptpTsData);
    assert(ptpTimedata);

    uint32_t index;
    uint32_t size;
    uint16_t usedBuffer = 0;

    /* Check the PTP 1588 timestamp ring. */
    if (ptpTsDataRing->front == ptpTsDataRing->end)
    {
        return kStatus_ENET_PtpTsRingEmpty;
    }

    /* Search the element in the ring buffer */
    index = ptpTsDataRing->front;
    size = ptpTsDataRing->size;
    while (index != ptpTsDataRing->end)
    {
        if (((ptpTsDataRing->ptpTsData + index)->sequenceId == ptpTimedata->sequenceId) &&
            (!memcmp(((void *)&(ptpTsDataRing->ptpTsData + index)->sourcePortId[0]),
                     (void *)&ptpTimedata->sourcePortId[0], kENET_PtpSrcPortIdLen)) &&
            ((ptpTsDataRing->ptpTsData + index)->version == ptpTimedata->version) &&
            ((ptpTsDataRing->ptpTsData + index)->messageType == ptpTimedata->messageType))
        {
            break;
        }

        /* Increase the ptp ring index. */
        index = (index + 1) % size;
    }

    if (index == ptpTsDataRing->end)
    {
        /* Check if buffers is full. */
        if (ptpTsDataRing->end >= ptpTsDataRing->front)
        {
            usedBuffer = ptpTsDataRing->end - ptpTsDataRing->front;
        }
        else
        {
            usedBuffer = ptpTsDataRing->size - (ptpTsDataRing->front - ptpTsDataRing->end);
        }

        if (usedBuffer == ptpTsDataRing->size)
        { /* Drop one in the front. */
            ptpTsDataRing->front = (ptpTsDataRing->front + 1) % size;
        }
        return kStatus_ENET_PtpTsRingFull;
    }

    /* Get the right timestamp of the required ptp messag. */
    ptpTimedata->timeStamp.second = (ptpTsDataRing->ptpTsData + index)->timeStamp.second;
    ptpTimedata->timeStamp.nanosecond = (ptpTsDataRing->ptpTsData + index)->timeStamp.nanosecond;

    /* Increase the index. */
    ptpTsDataRing->front = (ptpTsDataRing->front + 1) % size;

    return kStatus_Success;
}
#endif /* ENET_PTP1588FEATURE_REQUIRED */

uint32_t ENET_GetInstance(ENET_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < FSL_FEATURE_SOC_LPC_ENET_COUNT; instance++)
    {
        if (s_enetBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < FSL_FEATURE_SOC_LPC_ENET_COUNT);

    return instance;
}

void ENET_GetDefaultConfig(enet_config_t *config)
{
    /* Checks input parameter. */
    assert(config);

    /* Sets MII mode, full duplex, 100Mbps for MAC and PHY data interface. */
    config->miiMode = kENET_RmiiMode;
    config->miiSpeed = kENET_MiiSpeed100M;
    config->miiDuplex = kENET_MiiFullDuplex;

    /* Sets default configuration for other options. */
    config->specialControl = false;
    config->multiqueueCfg = NULL;
    config->pauseDuration = 0;

#ifdef ENET_PTP1588FEATURE_REQUIRED
    config->ptpConfig = NULL;
#endif /* ENET_PTP1588FEATURE_REQUIRED */
}

void ENET_Init(ENET_Type *base, const enet_config_t *config, uint8_t *macAddr, uint32_t refclkSrc_Hz)
{
    assert(config);

    uint32_t instance = ENET_GetInstance(base);
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate ENET clock. */
    CLOCK_EnableClock(s_enetClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    /* System configure fistly. */
    ENET_SetSYSControl(config->miiMode);

    /* Initializes the ENET DMA with basic function. */
    ENET_SetDMAControl(base, config);

    /* Initializes the ENET MTL with basic function. */
    ENET_SetMTL(base, config);

    /* Initializes the ENET MAC with basic function. */
    ENET_SetMacControl(base, config, macAddr);

#ifdef ENET_PTP1588FEATURE_REQUIRED
    ENET_SetPtp1588(base, config, refclkSrc_Hz);
#endif /* ENET_PTP1588FEATURE_REQUIRED */
}

void ENET_Deinit(ENET_Type *base)
{
    /* Reset first and wait for the complete
     * The reset bit will automatically be cleared after complete. */
    base->DMA_MODE |= ENET_DMA_MODE_SWR_MASK;
    while (base->DMA_MODE & ENET_DMA_MODE_SWR_MASK)
    {
    }

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disables the clock source. */
    CLOCK_DisableClock(s_enetClock[ENET_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

status_t ENET_DescriptorInit(ENET_Type *base, enet_config_t *config, enet_buffer_config_t *bufferConfig)
{
    assert(config);
    assert(bufferConfig);

    bool intTxEnable;
    bool intRxEnable;
    bool doubleBuffEnable = (config->specialControl & kENET_DescDoubleBuffer) ? true : false;
    uint8_t ringNum = config->multiqueueCfg == NULL ? 1 : 2;
    uint8_t channel;

    for (channel = 0; channel < ringNum; channel++)
    {
        intRxEnable = (base->DMA_CH[channel].DMA_CHX_INT_EN & ENET_DMA_CH_DMA_CHX_INT_EN_RIE_MASK) ? true : false;

        if (ENET_TxDescriptorsInit(base, bufferConfig, intTxEnable, channel) != kStatus_Success)
        {
            return kStatus_Fail;
        }
        intTxEnable = (base->DMA_CH[channel].DMA_CHX_INT_EN & ENET_DMA_CH_DMA_CHX_INT_EN_TIE_MASK) ? true : false;

        if (ENET_RxDescriptorsInit(base, bufferConfig, intRxEnable, channel, doubleBuffEnable) != kStatus_Success)
        {
            return kStatus_Fail;
        }

        bufferConfig++;
        if (!bufferConfig)
        {
            return kStatus_InvalidArgument;
        }
    }
    return kStatus_Success;
}

void ENET_StartRxTx(ENET_Type *base, uint8_t txRingNum, uint8_t rxRingNum)
{
    assert(txRingNum);
    assert(rxRingNum);

    uint8_t index;

    if (txRingNum > ENET_RING_NUM_MAX)
    {
        txRingNum = ENET_RING_NUM_MAX;
    }
    if (rxRingNum > ENET_RING_NUM_MAX)
    {
        rxRingNum = ENET_RING_NUM_MAX;
    }
    /* Start/Acive the DMA first. */
    for (index = 0; index < rxRingNum; index++)
    {
        base->DMA_CH[index].DMA_CHX_RX_CTRL |= ENET_DMA_CH_DMA_CHX_RX_CTRL_SR_MASK;
    }
    for (index = 0; index < txRingNum; index++)
    {
        base->DMA_CH[index].DMA_CHX_TX_CTRL |= ENET_DMA_CH_DMA_CHX_TX_CTRL_ST_MASK;
    }

    /* Enable the RX/TX then. */
    base->MAC_CONFIG |= ENET_MAC_CONFIG_RE_MASK;
    base->MAC_CONFIG |= ENET_MAC_CONFIG_TE_MASK;
}

void ENET_EnableInterrupts(ENET_Type *base, uint32_t mask)
{
    uint32_t interrupt = mask & 0xFFFFU;
    uint8_t index;

    /* For dma interrupt. */
    if (interrupt)
    {
        for (index = 0; index < ENET_RING_NUM_MAX; index++)
        {
            /* Set for all abnormal interrupts. */
            if (ENET_ABNORM_INT_MASK & interrupt)
            {
                interrupt |= ENET_DMA_CH_DMA_CHX_INT_EN_AIE_MASK;
            }
            /* Set for all normal interrupts. */
            if (ENET_NORM_INT_MASK & interrupt)
            {
                interrupt |= ENET_DMA_CH_DMA_CHX_INT_EN_NIE_MASK;
            }
            base->DMA_CH[index].DMA_CHX_INT_EN = interrupt;
        }
    }
    interrupt = interrupt >> ENET_MACINT_ENUM_OFFSET;
    if (interrupt)
    {
        /* MAC interrupt */
        base->MAC_INTR_EN |= interrupt;
    }
}

void ENET_ClearMacInterruptStatus(ENET_Type *base, uint32_t mask)
{
    volatile uint32_t dummy;

    if (mask & kENET_MacTimestamp)
    {
       dummy = base->MAC_SYS_TIMESTMP_STAT;
    }
    else if (mask & kENET_MacPmt)
    {
       dummy = base->MAC_PMT_CRTL_STAT;
    }
    else
    {
        /* Add for avoid the misra 2004 rule 14.10 */
    }
    (void)dummy;
}

void ENET_DisableInterrupts(ENET_Type *base, uint32_t mask)
{
    uint32_t interrupt = mask & 0xFFFFU;
    uint8_t index;

    /* For dma interrupt. */
    if (interrupt)
    {
        for (index = 0; index < ENET_RING_NUM_MAX; index++)
        {
            /* Set for all abnormal interrupts. */
            if (ENET_ABNORM_INT_MASK & interrupt)
            {
                interrupt |= ENET_DMA_CH_DMA_CHX_INT_EN_AIE_MASK;
            }
            /* Set for all normal interrupts. */
            if (ENET_NORM_INT_MASK & interrupt)
            {
                interrupt |= ENET_DMA_CH_DMA_CHX_INT_EN_NIE_MASK;
            }
            base->DMA_CH[index].DMA_CHX_INT_EN &= ~interrupt;
        }
    }
    interrupt = interrupt >> ENET_MACINT_ENUM_OFFSET;
    if (interrupt)
    {
        /* MAC interrupt */
        base->MAC_INTR_EN &= ~interrupt;
    }
}

void ENET_CreateHandler(ENET_Type *base,
                        enet_handle_t *handle,
                        enet_config_t *config,
                        enet_buffer_config_t *bufferConfig,
                        enet_callback_t callback,
                        void *userData)
{
    assert(config);
    assert(bufferConfig);
    assert(callback);

    uint8_t ringNum = 1;
    uint8_t count = 0;
    uint8_t rxIntEnable = 0;
    enet_buffer_config_t *buffConfig = bufferConfig;

    if (config->multiqueueCfg)
    {
        ringNum = 2;
        handle->multiQueEnable = true;
    }

    /* Store transfer parameters in handle pointer. */
    memset(handle, 0, sizeof(enet_handle_t));
    if (config->specialControl & kENET_DescDoubleBuffer)
    {
        handle->doubleBuffEnable = true;
    }
    if (config->multiqueueCfg)
    {
        handle->multiQueEnable = true;
    }
    for (count = 0; count < ringNum; count++)
    {
        handle->rxBdRing[count].rxBdBase = buffConfig->rxDescStartAddrAlign;
        handle->rxBdRing[count].rxGenIdx = 0;
        handle->rxBdRing[count].rxRingLen = buffConfig->rxRingLen;
        handle->rxBdRing[count].rxBuffSizeAlign = buffConfig->rxBuffSizeAlign;

        handle->txBdRing[count].txBdBase = buffConfig->txDescStartAddrAlign;
        handle->txBdRing[count].txRingLen = buffConfig->txRingLen;
        handle->txBdRing[count].txGenIdx = 0;
        handle->txBdRing[count].txConsumIdx = 0;
        handle->txBdRing[count].txDescUsed = 0;
#ifdef ENET_PTP1588FEATURE_REQUIRED
        assert(bufferConfig->rxPtpTsData);
        assert(bufferConfig->txPtpTsData);
        assert(buffConfig->rxRingLen <= ENET_RXBUFFSTORE_NUM);

        uint32_t index;

        handle->rxBdRing[count].rxPtpTsDataRing.ptpTsData = buffConfig->rxPtpTsData;
        handle->rxBdRing[count].rxPtpTsDataRing.front = 0;
        handle->rxBdRing[count].rxPtpTsDataRing.end = 0;
        handle->rxBdRing[count].rxPtpTsDataRing.size = buffConfig->ptpTsRxBuffNum;
        handle->txBdRing[count].txPtpTsDataRing.ptpTsData = buffConfig->txPtpTsData;
        handle->txBdRing[count].txPtpTsDataRing.front = 0;
        handle->txBdRing[count].txPtpTsDataRing.end = 0;
        handle->txBdRing[count].txPtpTsDataRing.size = buffConfig->ptpTsTxBuffNum;

        for (index = 0; index < buffConfig->rxRingLen; index++)
        {
            handle->rxbuffers[index] = *(buffConfig->rxBufferStartAddr + index);
        }
#endif /* ENET_PTP1588FEATURE_REQUIRED */
        /* Enable tx interrupt for use transactional API to do tx buffer free/requeue. */
        base->DMA_CH[count].DMA_CHX_INT_EN |= ENET_DMA_CH_DMA_CHX_INT_EN_TIE_MASK | ENET_DMA_CH_DMA_CHX_INT_EN_NIE_MASK;
        /* Check if the rx interrrupt is enabled. */
        rxIntEnable |= (base->DMA_CH[count].DMA_CHX_INT_EN & ENET_DMA_CH_DMA_CHX_INT_EN_RIE_MASK);
        buffConfig++;
    }

    handle->rxintEnable = rxIntEnable ? true : false;

    /* Save the handle pointer in the global variables. */
    s_ENETHandle[ENET_GetInstance(base)] = handle;

    /* Set callback and userData. */
    handle->callback = callback;
    handle->userData = userData;

    /* Enable the NVIC for tx. */
    s_enetIsr = ENET_IRQHandler;
    EnableIRQ(s_enetIrqId[ENET_GetInstance(base)]);
}

void ENET_GetMacAddr(ENET_Type *base, uint8_t *macAddr)
{
    assert(macAddr);

    uint32_t address = base->MAC_ADDR_LOW;

    /* Get from physical address lower register. */
    macAddr[2] = 0xFFU & (address >> 24U);
    macAddr[3] = 0xFFU & (address >> 16U);
    macAddr[4] = 0xFFU & (address >> 8U);
    macAddr[5] = 0xFFU & address;

    /* Get from physical address high register. */
    address = base->MAC_ADDR_HIGH;
    macAddr[0] = 0xFFU & (address >> 8U);
    macAddr[1] = 0xFFU & address;
}

void ENET_SetSMI(ENET_Type *base)
{
    uint32_t crDiv;
    uint32_t srcClock_Hz = CLOCK_GetFreq(kCLOCK_CoreSysClk) / 1000000U;

    if ((srcClock_Hz >= 20U) && (srcClock_Hz < 35))
    {
        crDiv = 2;
    }
    else if ((srcClock_Hz >= 35) && (srcClock_Hz < 60))
    {
        crDiv = 3;
    }
    else if ((srcClock_Hz >= 100) && (srcClock_Hz < 150))
    {
        crDiv = 1;
    }
    else
    {
        crDiv = 0;
    }

    base->MAC_MDIO_ADDR = ENET_MAC_MDIO_ADDR_CR(crDiv);
}

void ENET_StartSMIWrite(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t data)
{
    uint32_t reg = base->MAC_MDIO_ADDR & ENET_MAC_MDIO_ADDR_CR_MASK;

    /* Build MII write command. */
    base->MAC_MDIO_ADDR = reg | ENET_MAC_MDIO_ADDR_MOC(kENET_MiiWriteFrame) | ENET_MAC_MDIO_ADDR_PA(phyAddr) |
                          ENET_MAC_MDIO_ADDR_RDA(phyReg);
    base->MAC_MDIO_DATA = data;
    base->MAC_MDIO_ADDR |= ENET_MAC_MDIO_ADDR_MB_MASK;
}

void ENET_StartSMIRead(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg)
{
    uint32_t reg = base->MAC_MDIO_ADDR & ENET_MAC_MDIO_ADDR_CR_MASK;

    /* Build MII read command. */
    base->MAC_MDIO_ADDR = reg | ENET_MAC_MDIO_ADDR_MOC(kENET_MiiReadFrame) | ENET_MAC_MDIO_ADDR_PA(phyAddr) |
                          ENET_MAC_MDIO_ADDR_RDA(phyReg);
    base->MAC_MDIO_ADDR |= ENET_MAC_MDIO_ADDR_MB_MASK;
}

void ENET_EnterPowerDown(ENET_Type *base, uint32_t *wakeFilter)
{
    uint8_t index;
    uint32_t *reg = wakeFilter;

    /* Disable the tx dma. */
    base->DMA_CH[0].DMA_CHX_TX_CTRL &= ~ENET_DMA_CH_DMA_CHX_TX_CTRL_ST_MASK;
    base->DMA_CH[1].DMA_CHX_TX_CTRL &= ~ENET_DMA_CH_DMA_CHX_TX_CTRL_ST_MASK;

    /* Disable the mac tx/rx. */
    base->MAC_CONFIG &= ~(ENET_MAC_CONFIG_RE_MASK | ENET_MAC_CONFIG_TE_MASK);
    /* Enable the remote wakeup packet and enable the power down mode. */
    if (wakeFilter)
    {
        for (index = 0; index < ENET_WAKEUPFILTER_NUM; index++)
        {
            base->MAC_RWAKE_FRFLT = *reg;
            reg++;
        }
    }
    base->MAC_PMT_CRTL_STAT = ENET_MAC_PMT_CRTL_STAT_MGKPKTEN_MASK | ENET_MAC_PMT_CRTL_STAT_RWKPKTEN_MASK |
                              ENET_MAC_PMT_CRTL_STAT_PWRDWN_MASK;

    /* Enable the MAC rx. */
    base->MAC_CONFIG |= ENET_MAC_CONFIG_RE_MASK;
}

status_t ENET_GetRxFrameSize(ENET_Type *base, enet_handle_t *handle, uint32_t *length, uint8_t channel)
{
    assert(handle);
    assert(length);

    enet_rx_bd_ring_t *rxBdRing = (enet_rx_bd_ring_t *)&handle->rxBdRing[channel];
    enet_rx_bd_struct_t *rxDesc = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
    uint16_t index;

    /* Reset the length to zero. */
    *length = 0;

    if (rxDesc->control & ENET_RXDESCRIP_WR_OWN_MASK)
    {
        return kStatus_ENET_RxFrameEmpty;
    }
    else
    {
        do
        {
            /* Application owns the buffer descriptor, get the length. */
            if (rxDesc->control & ENET_RXDESCRIP_WR_LD_MASK)
            {
                if (rxDesc->control & ENET_RXDESCRIP_WR_ERRSUM_MASK)
                {
                    return kStatus_ENET_RxFrameError;
                }
                *length = rxDesc->control & ENET_RXDESCRIP_WR_PACKETLEN_MASK;
                return kStatus_Success;
            }

            index = ENET_IncreaseIndex(index, rxBdRing->rxRingLen);
            rxDesc = rxBdRing->rxBdBase + index;
        } while (index != rxBdRing->rxGenIdx);

        return kStatus_ENET_RxFrameError;
    }
}

status_t ENET_ReadFrame(ENET_Type *base, enet_handle_t *handle, uint8_t *data, uint32_t length, uint8_t channel)
{
    assert(handle);

    uint32_t len = 0;
    uint32_t offset = 0;
    uint32_t control;
    bool isLastBuff = false;
    enet_rx_bd_ring_t *rxBdRing = (enet_rx_bd_ring_t *)&handle->rxBdRing[channel];
    enet_rx_bd_struct_t *rxDesc;
    status_t result = kStatus_Fail;
    uint16_t index = rxBdRing->rxGenIdx;
    bool suspend = false;
#ifdef ENET_PTP1588FEATURE_REQUIRED
    uint32_t buffer;
    uint32_t bufferAdd;
#endif /* ENET_PTP1588FEATURE_REQUIRED  */

    /* Suspend and command for rx. */
    if (base->DMA_CH[channel].DMA_CHX_STAT & ENET_DMA_CH_DMA_CHX_STAT_RBU_MASK)
    {
        suspend = true;
    }

    /* For data-NULL input, only update the buffer descriptor. */
    if ((!data))
    {
        do
        {
            /* Get the control flag. */
            rxDesc = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
            rxBdRing->rxGenIdx = ENET_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);
            control = rxDesc->control;
            /* Updates the receive buffer descriptors. */
            ENET_UpdateRxDescriptor(rxDesc, NULL, NULL, handle->rxintEnable, handle->doubleBuffEnable);

            /* Find the last buffer descriptor for the frame. */
            if (control & ENET_RXDESCRIP_WR_LD_MASK)
            {
#ifdef ENET_PTP1588FEATURE_REQUIRED
                /* Reinit for the context descritor which has been updated by DMA. */
                rxDesc = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
                if (rxDesc->control & ENET_RXDESCRIP_WR_CTXT_MASK)
                {
                    if (!handle->doubleBuffEnable)
                    {
                        buffer = handle->rxbuffers[rxBdRing->rxGenIdx];
                        ENET_UpdateRxDescriptor(rxDesc, (void *)buffer, NULL, handle->rxintEnable,
                                                handle->doubleBuffEnable);
                    }
                    else
                    {
                        buffer = handle->rxbuffers[2 * rxBdRing->rxGenIdx];
                        bufferAdd = handle->rxbuffers[2 * rxBdRing->rxGenIdx + 1];
                        ENET_UpdateRxDescriptor(rxDesc, (void *)buffer, (void *)bufferAdd, handle->rxintEnable,
                                                handle->doubleBuffEnable);
                    }
                    rxBdRing->rxGenIdx = ENET_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);
                }
#endif /*  ENET_PTP1588FEATURE_REQUIRED */
                break;
            }
        } while (rxBdRing->rxGenIdx != index);

        result = kStatus_Success;
    }
    else
    {
#ifdef ENET_PTP1588FEATURE_REQUIRED
        enet_ptp_time_data_t ptpTsData;
        bool ptp1588 = false;
#endif /* ENET_PTP1588FEATURE_REQUIRED */

        while ((!isLastBuff))
        {
            /* The last buffer descriptor of a frame. */
            rxDesc = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
            rxBdRing->rxGenIdx = ENET_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);
#ifdef ENET_PTP1588FEATURE_REQUIRED
            if (rxDesc->control & ENET_RXDESCRIP_WR_FD_MASK)
            {
                ptp1588 = ENET_Ptp1588ParseFrame((uint8_t *)rxDesc->buff1Addr, &ptpTsData, false);
            }
#endif
            if (rxDesc->control & ENET_RXDESCRIP_WR_LD_MASK)
            {
                /* This is a valid frame. */
                isLastBuff = true;
                if (length == (rxDesc->control & ENET_RXDESCRIP_WR_PACKETLEN_MASK))
                {
                    /* Copy the frame to user's buffer. */
                    len = (rxDesc->control & ENET_RXDESCRIP_WR_PACKETLEN_MASK) - offset;
                    if (len > rxBdRing->rxBuffSizeAlign)
                    {
                        memcpy(data + offset, (void *)rxDesc->buff1Addr, rxBdRing->rxBuffSizeAlign);
                        offset += rxBdRing->rxBuffSizeAlign;
                        memcpy(data + offset, (void *)rxDesc->buff2Addr, len - rxBdRing->rxBuffSizeAlign);
                    }
                    else
                    {
                        memcpy(data + offset, (void *)rxDesc->buff1Addr, len);
                    }

                    result = kStatus_Success;
                }

                /* Updates the receive buffer descriptors. */
                ENET_UpdateRxDescriptor(rxDesc, NULL, NULL, handle->rxintEnable, handle->doubleBuffEnable);
#ifdef ENET_PTP1588FEATURE_REQUIRED
                /* Store the rx timestamp which is in the next buffer descriptor of the last
                 * descriptor of a frame. */
                rxDesc = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;

                /* Reinit for the context descritor which has been updated by DMA. */
                if (rxDesc->control & ENET_RXDESCRIP_WR_CTXT_MASK)
                {
                    if (ptp1588)
                    {
                        ENET_StoreRxFrameTime(base, handle, rxDesc, channel, &ptpTsData);
                    }

                    if (!handle->doubleBuffEnable)
                    {
                        buffer = handle->rxbuffers[rxBdRing->rxGenIdx];
                        ENET_UpdateRxDescriptor(rxDesc, (void *)buffer, NULL, handle->rxintEnable,
                                                handle->doubleBuffEnable);
                    }
                    else
                    {
                        buffer = handle->rxbuffers[2 * rxBdRing->rxGenIdx];
                        bufferAdd = handle->rxbuffers[2 * rxBdRing->rxGenIdx + 1];
                        ENET_UpdateRxDescriptor(rxDesc, (void *)buffer, (void *)bufferAdd, handle->rxintEnable,
                                                handle->doubleBuffEnable);
                    }
                    rxBdRing->rxGenIdx = ENET_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);
                }
                base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR = base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR;
#endif /* ENET_PTP1588FEATURE_REQUIRED */
            }
            else
            {
                /* Store a frame on several buffer descriptors. */
                isLastBuff = false;
                /* Length check. */
                if (offset >= length)
                {
                    /* Updates the receive buffer descriptors. */
                    ENET_UpdateRxDescriptor(rxDesc, NULL, NULL, handle->rxintEnable, handle->doubleBuffEnable);
                    break;
                }

                memcpy(data + offset, (void *)rxDesc->buff1Addr, rxBdRing->rxBuffSizeAlign);
                offset += rxBdRing->rxBuffSizeAlign;
                if ((rxDesc->buff2Addr) && (handle->doubleBuffEnable))
                {
                    memcpy(data + offset, (void *)rxDesc->buff2Addr, rxBdRing->rxBuffSizeAlign);
                    offset += rxBdRing->rxBuffSizeAlign;
                }

                /* Updates the receive buffer descriptors. */
                ENET_UpdateRxDescriptor(rxDesc, NULL, NULL, handle->rxintEnable, handle->doubleBuffEnable);
            }
        }
    }

    /* Set command for rx when it is suspend. */
    if (suspend)
    {
        base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR = base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR;
    }

    return result;
}

void ENET_UpdateRxDescriptor(
    enet_rx_bd_struct_t *rxDesc, void *buffer1, void *buffer2, bool intEnable, bool doubleBuffEnable)
{
    assert(rxDesc);
    uint32_t control = ENET_RXDESCRIP_RD_OWN_MASK | ENET_RXDESCRIP_RD_BUFF1VALID_MASK;

    if (intEnable)
    {
        control |= ENET_RXDESCRIP_RD_IOC_MASK;
    }

    if (doubleBuffEnable)
    {
        control |= ENET_RXDESCRIP_RD_BUFF2VALID_MASK;
    }

    /* Update the buffer if needed. */
    if (buffer1)
    {
        rxDesc->buff1Addr = (uint32_t)buffer1;
    }
    if (buffer2)
    {
        rxDesc->buff2Addr = (uint32_t)buffer2;
    }
    else
    {
        rxDesc->buff2Addr = 0;
    }

    rxDesc->reserved = 0;
    rxDesc->control = control;
}

void ENET_SetupTxDescriptor(enet_tx_bd_struct_t *txDesc,
                            void *buffer1,
                            uint32_t bytes1,
                            void *buffer2,
                            uint32_t bytes2,
                            uint32_t framelen,
                            bool intEnable,
                            bool tsEnable,
                            enet_desc_flag flag,
                            uint8_t slotNum)
{
    uint32_t control = ENET_TXDESCRIP_RD_BL1(bytes1) | ENET_TXDESCRIP_RD_BL2(bytes2);

    if (tsEnable)
    {
        control |= ENET_TXDESCRIP_RD_TTSE_MASK;
    }
    else
    {
        control &= ~ENET_TXDESCRIP_RD_TTSE_MASK;
    }

    if (intEnable)
    {
        control |= ENET_TXDESCRIP_RD_IOC_MASK;
    }
    else
    {
        control &= ~ENET_TXDESCRIP_RD_IOC_MASK;
    }

    /* Preare the descriptor for transmit. */
    txDesc->buff1Addr = (uint32_t)buffer1;
    txDesc->buff2Addr = (uint32_t)buffer2;
    txDesc->buffLen = control;

    control = ENET_TXDESCRIP_RD_FL(framelen) | ENET_TXDESCRIP_RD_LDFD(flag) | ENET_TXDESCRIP_RD_OWN_MASK;

    txDesc->controlStat = control;
}

void ENET_ReclaimTxDescriptor(ENET_Type *base, enet_handle_t *handle, uint8_t channel)
{
    enet_tx_bd_ring_t *txBdRing = &handle->txBdRing[channel];
    enet_tx_bd_struct_t *txDesc = txBdRing->txBdBase + txBdRing->txConsumIdx;

    /* Need to update the first index for transmit buffer free. */
    while ((txBdRing->txDescUsed > 0) && (!(txDesc->controlStat & ENET_TXDESCRIP_RD_OWN_MASK)))
    {
#ifdef ENET_PTP1588FEATURE_REQUIRED
        uint32_t nanosecond;
        uint32_t nanoOverSize = ENET_NANOSECS_ONESECOND; /* Default use the digital rollover. */

        if (txDesc->controlStat & ENET_TXDESCRIP_RD_LD_MASK)
        {
            enet_ptp_time_data_t *ptpTsData = txBdRing->txPtpTsDataRing.ptpTsData + txBdRing->txPtpTsDataRing.end;
            if (txDesc->controlStat & ENET_TXDESCRIP_WB_TTSS_MASK)
            {
                /* Get transmit time stamp second. */
                nanosecond = txDesc->buff2Addr | txDesc->buff1Addr;
                if (!(base->MAC_TIMESTAMP_CTRL & ENET_MAC_TIMESTAMP_CTRL_TSCTRLSSR_MASK))
                {
                    /* Binary rollover. */
                    nanoOverSize = ENET_MAC_SYS_TIME_NSCND_TSSS_MASK;
                }
                ptpTsData->timeStamp.second = nanosecond / nanoOverSize;
                ptpTsData->timeStamp.nanosecond = nanosecond % nanoOverSize;

                /* Store the timestamp to the transmit timestamp ring. */
                ENET_Ptp1588UpdateTimeRing(&txBdRing->txPtpTsDataRing, ptpTsData);
            }
        }
#endif  /* ENET_PTP1588FEATURE_REQUIRED */

        /* For tx buffer free or requeue for each descriptor.
         * The tx interrupt callback should free/requeue the tx buffer. */
        if (handle->callback)
        {
            handle->callback(base, handle, kENET_TxIntEvent, channel, handle->userData);
        }

        txBdRing->txDescUsed--;

        /* Update the txConsumIdx/txDesc. */
        txBdRing->txConsumIdx = ENET_IncreaseIndex(txBdRing->txConsumIdx, txBdRing->txRingLen);
        txDesc = txBdRing->txBdBase + txBdRing->txConsumIdx;
    }
}

status_t ENET_SendFrame(ENET_Type *base, enet_handle_t *handle, uint8_t *data, uint32_t length)
{
    assert(handle);
    assert(data);

    enet_tx_bd_ring_t *txBdRing;
    enet_tx_bd_struct_t *txDesc;
    uint8_t channel = 0;
    bool ptp1588 = false;

    if (length > 2 * ENET_TXDESCRIP_RD_BL1_MASK)
    {
        return kStatus_ENET_TxFrameOverLen;
    }

    /* Choose the transit queue. */
    channel = ENET_GetTxRingId(data, handle);

    /* Check if the DMA owns the descriptor. */
    txBdRing = (enet_tx_bd_ring_t *)&handle->txBdRing[channel];
    txDesc = txBdRing->txBdBase + txBdRing->txGenIdx;
    if (txBdRing->txRingLen == txBdRing->txDescUsed)
    {
        return kStatus_ENET_TxFrameBusy;
    }

#ifdef ENET_PTP1588FEATURE_REQUIRED
    enet_ptp_time_data_t ptpTsData;

    ptp1588 = ENET_Ptp1588ParseFrame(data, &ptpTsData, true);
#endif /* ENET_PTP1588FEATURE_REQUIRED */

    /* Fill the descriptor. */
    if (length <= ENET_TXDESCRIP_RD_BL1_MASK)
    {
        ENET_SetupTxDescriptor(txDesc, data, length, NULL, 0, length, true, ptp1588, kENET_FirstLastFlag, 0);
    }
    else
    {
        ENET_SetupTxDescriptor(txDesc, data, ENET_TXDESCRIP_RD_BL1_MASK, data + ENET_TXDESCRIP_RD_BL1_MASK,
                               (length - ENET_TXDESCRIP_RD_BL1_MASK), length, true, ptp1588, kENET_FirstLastFlag, 0);
    }

    /* Increase the index. */
    txBdRing->txGenIdx = ENET_IncreaseIndex(txBdRing->txGenIdx, txBdRing->txRingLen);
    /* Disable interrupt first and then enable interrupt to avoid the race condition. */
    DisableIRQ(s_enetIrqId[ENET_GetInstance(base)]);
    txBdRing->txDescUsed++;
    EnableIRQ(s_enetIrqId[ENET_GetInstance(base)]);

    /* Update the transmit tail address. */
    txDesc = txBdRing->txBdBase + txBdRing->txGenIdx;
    if (!txBdRing->txGenIdx)
    {
        txDesc = txBdRing->txBdBase + txBdRing->txRingLen;
    }
    base->DMA_CH[channel].DMA_CHX_TXDESC_TAIL_PTR = (uint32_t)txDesc & ~ENET_ADDR_ALIGNMENT;

    return kStatus_Success;
}

#ifdef ENET_PTP1588FEATURE_REQUIRED
void ENET_Ptp1588GetTimer(ENET_Type *base, uint64_t *second, uint32_t *nanosecond)
{
    assert(second);
    assert(nanosecond);

    uint32_t primask;

    /* Disables the interrupt. */
    primask = DisableGlobalIRQ();

    /* Get the current PTP time. */
    *second = ((uint64_t)(base->MAC_SYS_TIME_HWORD_SCND & ENET_MAC_SYS_TIME_HWORD_SCND_TSHWR_MASK) << 32U) |
              base->MAC_SYS_TIME_SCND;
    *nanosecond = base->MAC_SYS_TIME_NSCND & ENET_MAC_SYS_TIME_NSCND_TSSS_MASK;
    if (!(base->MAC_TIMESTAMP_CTRL & ENET_MAC_TIMESTAMP_CTRL_TSCTRLSSR_MASK))
    {
        /* Binary rollover, the unit of the increment is ~ 0.466 ns. */
        *nanosecond = *nanosecond / 1000U * 466U;
    }

    /* Enables the interrupt. */
    EnableGlobalIRQ(primask);
}

void ENET_Ptp1588CorrectTimerInCoarse(ENET_Type *base, enet_systime_op operation, uint32_t second, uint32_t nanosecond)
{
    uint32_t corrSecond = second;
    uint32_t corrNanosecond;

    /* Set the system timer. */
    if (base->MAC_TIMESTAMP_CTRL & ENET_MAC_TIMESTAMP_CTRL_TSCTRLSSR_MASK)
    {
        if (operation == kENET_SystimeSubtract)
        {
            /* Set with the complement of the sub-second. */
            corrSecond = ENET_MAC_SYS_TIME_SCND_UPD_TSS_MASK - (second - 1);
            corrNanosecond = ENET_MAC_SYS_TIME_NSCND_UPD_ADDSUB_MASK |
                             ENET_MAC_SYS_TIME_NSCND_UPD_TSSS(ENET_NANOSECS_ONESECOND - nanosecond);
        }
        else
        {
            corrNanosecond = ENET_MAC_SYS_TIME_NSCND_UPD_TSSS(nanosecond);
        }
    }
    else
    {
        nanosecond = ENET_MAC_SYS_TIME_NSCND_UPD_TSSS_MASK / ENET_NANOSECS_ONESECOND * nanosecond;
        if (operation == kENET_SystimeSubtract)
        {
            /* Set with the complement of the sub-second. */
            corrSecond = ENET_MAC_SYS_TIME_SCND_UPD_TSS_MASK - (second - 1);
            corrNanosecond = ENET_MAC_SYS_TIME_NSCND_UPD_ADDSUB_MASK |
                             ENET_MAC_SYS_TIME_NSCND_UPD_TSSS(ENET_MAC_SYS_TIME_NSCND_UPD_TSSS_MASK + 1 - nanosecond);
        }
        else
        {
            corrNanosecond = ENET_MAC_SYS_TIME_NSCND_UPD_TSSS(nanosecond);
        }
    }

    base->MAC_SYS_TIME_SCND_UPD = corrSecond;
    base->MAC_SYS_TIME_NSCND_UPD = corrNanosecond;

    /* Update the timer. */
    base->MAC_TIMESTAMP_CTRL |= ENET_MAC_TIMESTAMP_CTRL_TSUPDT_MASK;
    while (base->MAC_TIMESTAMP_CTRL & ENET_MAC_TIMESTAMP_CTRL_TSUPDT_MASK)
        ;
}

status_t ENET_GetTxFrameTime(enet_handle_t *handle, enet_ptp_time_data_t *ptpTimeData)
{
    assert(handle);
    assert(ptpTimeData);

    uint32_t result = kStatus_Success;
    uint8_t count;
    uint8_t index = handle->multiQueEnable ? 2 : 1;

    for (count = 0; count < index; count++)
    {
        result = ENET_Ptp1588SearchTimeRing(&handle->txBdRing[count].txPtpTsDataRing, ptpTimeData);
        if (result == kStatus_Success)
        {
            break;
        }
    }

    return result;
}

status_t ENET_GetRxFrameTime(enet_handle_t *handle, enet_ptp_time_data_t *ptpTimeData)
{
    assert(handle);
    assert(ptpTimeData);

    uint32_t result = kStatus_Success;
    uint8_t count;
    uint8_t index = handle->multiQueEnable ? 2 : 1;

    for (count = 0; count < index; count++)
    {
        result = ENET_Ptp1588SearchTimeRing(&handle->rxBdRing[count].rxPtpTsDataRing, ptpTimeData);
        if (result == kStatus_Success)
        {
            break;
        }
    }

    return result;
}

#endif /* ENET_PTP1588FEATURE_REQUIRED */

void ENET_IRQHandler(ENET_Type *base, enet_handle_t *handle)
{
    /* Check for the interrupt source type. */
    /* DMA CHANNEL 0. */
    if (base->DMA_INTR_STAT & ENET_DMA_INTR_STAT_DC0IS_MASK)
    {
        uint32_t flag = base->DMA_CH[0].DMA_CHX_STAT;
        if (flag & ENET_DMA_CH_DMA_CHX_STAT_RI_MASK)
        {
            base->DMA_CH[0].DMA_CHX_STAT = ENET_DMA_CH_DMA_CHX_STAT_RI_MASK | ENET_DMA_CH_DMA_CHX_STAT_NIS_MASK;
            if (handle->callback)
            {
                handle->callback(base, handle, kENET_RxIntEvent, 0, handle->userData);
            }
        }
        if (flag & ENET_DMA_CH_DMA_CHX_STAT_TI_MASK)
        {
            base->DMA_CH[0].DMA_CHX_STAT = ENET_DMA_CH_DMA_CHX_STAT_TI_MASK | ENET_DMA_CH_DMA_CHX_STAT_NIS_MASK;
            ENET_ReclaimTxDescriptor(base, handle, 0);
        }
    }

    /* DMA CHANNEL 1. */
    if (base->DMA_INTR_STAT & ENET_DMA_INTR_STAT_DC1IS_MASK)
    {
        uint32_t flag = base->DMA_CH[1].DMA_CHX_STAT;
        if (flag & ENET_DMA_CH_DMA_CHX_STAT_RI_MASK)
        {
            base->DMA_CH[1].DMA_CHX_STAT = ENET_DMA_CH_DMA_CHX_STAT_RI_MASK | ENET_DMA_CH_DMA_CHX_STAT_NIS_MASK;
            if (handle->callback)
            {
                handle->callback(base, handle, kENET_RxIntEvent, 1, handle->userData);
            }
        }
        if (flag & ENET_DMA_CH_DMA_CHX_STAT_TI_MASK)
        {
            base->DMA_CH[1].DMA_CHX_STAT = ENET_DMA_CH_DMA_CHX_STAT_TI_MASK | ENET_DMA_CH_DMA_CHX_STAT_NIS_MASK;
            ENET_ReclaimTxDescriptor(base, handle, 1);
        }
    }

#ifdef ENET_PTP1588FEATURE_REQUIRED
    /* MAC TIMESTAMP. */
    if (base->DMA_INTR_STAT & ENET_DMA_INTR_STAT_MACIS_MASK)
    {
        if (base->MAC_INTR_STAT & ENET_MAC_INTR_STAT_TSIS_MASK)
        {
            if (handle->callback)
            {
                handle->callback(base, handle, kENET_TimeStampIntEvent, 0, handle->userData);
            }
        }
    }
#endif /* ENET_PTP1588FEATURE_REQUIRED */
}

void ETHERNET_DriverIRQHandler(void)
{
    s_enetIsr(ENET, s_ENETHandle[0]);
}
