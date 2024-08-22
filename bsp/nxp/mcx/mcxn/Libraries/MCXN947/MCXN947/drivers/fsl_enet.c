/*
 * Copyright 2022-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <math.h>
#include "fsl_enet.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mcx_enet"
#endif

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
/*! @brief ENET miminum ring length. */
#define ENET_MIN_RINGLEN (4U)
/*! @brief ENET wakeup filter numbers. */
#define ENET_WAKEUPFILTER_NUM (8U)
/*! @brief Requried systime timer frequency. */
#define ENET_SYSTIME_REQUIRED_CLK_MHZ (50U)
/*! @brief Ethernet VLAN tag length. */
#define ENET_FRAME_VLAN_TAGLEN 4U

/*! @brief AVB TYPE */
#define ENET_AVBTYPE             0x22F0U
#define ENET_HEAD_TYPE_OFFSET    (12)
#define ENET_HEAD_AVBTYPE_OFFSET (16)

/*! @brief Binary rollover mode count convert */
#define ENET_BINARY_ROLLOVER_SCALE(x) (uint32_t)((uint64_t)(x) * 46566U / 100000U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Increase the index in the ring.
 *
 * @param index The current index.
 * @param max The size.
 * @return the increased index.
 */
static uint16_t ENET_IncreaseIndex(uint16_t index, uint16_t max);

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
 * @param clkSrcHz ENET input reference clock.
 */
static void ENET_SetMacControl(ENET_Type *base, const enet_config_t *config, uint8_t *macAddr, uint32_t clkSrcHz);

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
 * @param channel The channel number, 0 , 1.
 */
static status_t ENET_TxDescriptorsInit(ENET_Type *base, const enet_buffer_config_t *bufferConfig, uint8_t channel);

/*!
 * @brief Set ENET DMA receive buffer descriptors for one channel.
 *
 * @param base ENET peripheral base address.
 * @param config The ENET configuration.
 * @param bufferConfig ENET buffer configuration.
 * @param channel The channel number, 0 , 1.
 */
static status_t ENET_RxDescriptorsInit(ENET_Type *base,
                                       enet_config_t *config,
                                       const enet_buffer_config_t *bufferConfig,
                                       uint8_t channel);

/*!
 * @brief Drop one frame in specified BD channel.
 *
 * @param base ENET peripheral base address.
 * @param handle ENET handler.
 * @param channel The channel number, 0 , 1.
 */
static void ENET_DropFrame(ENET_Type *base, enet_handle_t *handle, uint8_t channel);

#ifdef ENET_PTP1588FEATURE_REQUIRED
/*!
 * @brief Sets the ENET 1588 feature.
 *
 * Enable the enhacement 1588 buffer descriptor mode and start
 * the 1588 timer.
 *
 * @param base ENET peripheral base address.
 * @param config The ENET configuration.
 * @param ptpClkHz The reference clock for ptp 1588.
 */
static void ENET_SetPtp1588(ENET_Type *base, const enet_config_t *config, uint32_t ptpClkHz);
#endif /* ENET_PTP1588FEATURE_REQUIRED */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to enet handles for each instance. */
static enet_handle_t *s_ENETHandle[FSL_FEATURE_SOC_MCX_ENET_COUNT] = {NULL};
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to enet clocks for each instance. */
const clock_ip_name_t s_enetClock[FSL_FEATURE_SOC_MCX_ENET_COUNT] = ETH_CLOCKS;
#endif /*  FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointers to enet bases for each instance. */
static ENET_Type *const s_enetBases[] = ENET_BASE_PTRS;

/*! @brief Pointers to enet IRQ number for each instance. */
static const IRQn_Type s_enetIrqId[] = ENET_IRQS;

/* ENET ISR for transactional APIs. */
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
static enet_isr_t s_enetIsr = (enet_isr_t)DefaultISR;
#else
static enet_isr_t s_enetIsr;
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/
static uint16_t ENET_IncreaseIndex(uint16_t index, uint16_t max)
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
#ifdef SYSCON_ETHPHYSEL_PHY_SEL_MASK
    /* Reset first. */
    SYSCON->PRESETCTRL[2] = SYSCON_PRESETCTRL_ETH_RST_MASK;
    SYSCON->PRESETCTRL[2] &= ~SYSCON_PRESETCTRL_ETH_RST_MASK;
    /* Set MII/RMII before the peripheral ethernet dma reset. */
    SYSCON->ETHPHYSEL = (SYSCON->ETHPHYSEL & ~SYSCON_ETHPHYSEL_PHY_SEL_MASK) | SYSCON_ETHPHYSEL_PHY_SEL(miiMode);
#else
    /* Reset first. */
    SYSCON0->PRESETCTRL2 = SYSCON_PRESETCTRL2_ENET_RST_MASK;
    SYSCON0->PRESETCTRL2 &= ~SYSCON_PRESETCTRL2_ENET_RST_MASK;
    /* Set MII/RMII before the peripheral ethernet dma reset. */
    SYSCON0->ENET_PHY_INTF_SEL = (SYSCON0->ENET_PHY_INTF_SEL & ~SYSCON_ENET_PHY_INTF_SEL_PHY_SEL_MASK) |
                                 SYSCON_ENET_PHY_INTF_SEL_PHY_SEL(miiMode);
#endif
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
    while ((base->DMA_MODE & ENET_DMA_MODE_SWR_MASK) != 0U)
    {
    }

    /* Set the burst length. */
    for (index = 0; index < ENET_RING_NUM_MAX; index++)
    {
        burstLen = (uint32_t)kENET_BurstLen1;
        if (config->multiqueueCfg != NULL)
        {
            burstLen = (uint32_t)config->multiqueueCfg->burstLen;
        }
        base->DMA_CH[index].DMA_CHX_CTRL = burstLen & ENET_DMA_CH_DMA_CHX_CTRL_PBLx8_MASK;

        reg = base->DMA_CH[index].DMA_CHX_TX_CTRL & ~ENET_DMA_CH_DMA_CHX_TX_CTRL_TxPBL_MASK;
        base->DMA_CH[index].DMA_CHX_TX_CTRL = reg | ENET_DMA_CH_DMA_CHX_TX_CTRL_TxPBL(burstLen & 0x3FU);

        reg = base->DMA_CH[index].DMA_CHX_RX_CTRL & ~ENET_DMA_CH_DMA_CHX_RX_CTRL_RxPBL_MASK;
        base->DMA_CH[index].DMA_CHX_RX_CTRL = reg | ENET_DMA_CH_DMA_CHX_RX_CTRL_RxPBL(burstLen & 0x3FU);
    }
}

static void ENET_SetMTL(ENET_Type *base, const enet_config_t *config)
{
    assert(config);

    uint32_t txqOpreg                   = 0;
    uint32_t rxqOpReg                   = 0;
    enet_multiqueue_config_t *multiqCfg = config->multiqueueCfg;
    uint8_t index;

    /* Set transmit operation mode. */
    if ((config->specialControl & (uint16_t)kENET_StoreAndForward) != 0U)
    {
        txqOpreg = ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TSF_MASK;
        rxqOpReg = ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RSF_MASK;
    }
    txqOpreg |= ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_FTQ_MASK |
                ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TQS(ENET_MTL_TXFIFOSIZE / ENET_FIFOSIZE_UNIT - 1UL);
    base->MTL_QUEUE[0].MTL_TXQX_OP_MODE = txqOpreg | ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TXQEN(2);
    base->MTL_QUEUE[1].MTL_TXQX_OP_MODE = txqOpreg;

    /* Set receive operation mode. */
    rxqOpReg |= ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_FUP_MASK |
                ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RQS(ENET_MTL_RXFIFOSIZE / ENET_FIFOSIZE_UNIT - 1UL);
    base->MTL_QUEUE[0].MTL_RXQX_OP_MODE = rxqOpReg;

    /* Set the schedule/arbitration(set for multiple queues). */
    if (multiqCfg != NULL)
    {
        base->MTL_OPERATION_MODE =
            ENET_MTL_OPERATION_MODE_SCHALG(multiqCfg->mtltxSche) | ENET_MTL_OPERATION_MODE_RAA(multiqCfg->mtlrxSche);
        /* Set the Rx queue mapping to dma channel. */
        base->MTL_RXQ_DMA_MAP0 = (uint32_t)multiqCfg->mtlrxQuemap;
        /* Set the Tx/Rx queue operation mode for multi-queue. */
        base->MTL_QUEUE[1].MTL_TXQX_OP_MODE |= ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TXQEN(2);
        base->MTL_QUEUE[1].MTL_RXQX_OP_MODE = rxqOpReg;

        /* Set the Tx/Rx queue weight. */
        for (index = 0; index < ENET_RING_NUM_MAX; index++)
        {
            base->MTL_QUEUE[index].MTL_TXQX_QNTM_WGHT = multiqCfg->txqueweight[index];
            base->MTL_QUEUE[index].MTL_RXQX_CTRL = ENET_MTL_QUEUE_MTL_RXQX_CTRL_RXQ_WEGT(multiqCfg->rxqueweight[index]);
        }
    }
}

static void ENET_SetMacControl(ENET_Type *base, const enet_config_t *config, uint8_t *macAddr, uint32_t clkSrcHz)
{
    assert(config);

    uint32_t reg = 0;

    /* Set Macaddr */
    /* The dma channel 0 is set as to which the Rx packet
     * whose DA matches the MAC address content is routed. */
    if (macAddr != NULL)
    {
        ENET_SetMacAddr(base, macAddr);
    }

    /* Set the receive filter. */
    reg = ENET_MAC_PACKET_FILTER_PR(!((config->specialControl & (uint16_t)kENET_PromiscuousEnable) == 0U)) |
          ENET_MAC_PACKET_FILTER_DBF(!((config->specialControl & (uint16_t)kENET_BroadCastRxDisable) == 0U)) |
          ENET_MAC_PACKET_FILTER_PM(!((config->specialControl & (uint16_t)kENET_MulticastAllEnable) == 0U));
    base->MAC_PACKET_FILTER = reg;
    /* Flow control. */
    if ((config->specialControl & (uint16_t)kENET_FlowControlEnable) != 0U)
    {
        base->MAC_RX_FLOW_CTRL      = ENET_MAC_RX_FLOW_CTRL_RFE_MASK | ENET_MAC_RX_FLOW_CTRL_UP_MASK;
        base->MAC_TX_FLOW_CTRL_Q[0] = ENET_MAC_TX_FLOW_CTRL_Q_PT(config->pauseDuration);
    }

    /* Set the 1us ticket. */
    reg                         = clkSrcHz / ENET_MICRSECS_ONESECOND - 1U;
    base->MAC_ONEUS_TIC_COUNTER = ENET_MAC_ONEUS_TIC_COUNTER_TIC_1US_CNTR(reg);

    /* Set the speed and duplex. */
    reg = ENET_MAC_CONFIGURATION_ECRSFD_MASK | ENET_MAC_CONFIGURATION_PS_MASK |
          ENET_MAC_CONFIGURATION_DM(config->miiDuplex) | ENET_MAC_CONFIGURATION_FES(config->miiSpeed) |
          ENET_MAC_CONFIGURATION_S2KP((config->specialControl & (uint16_t)kENET_8023AS2KPacket) != 0U) |
          ENET_MAC_CONFIGURATION_IPC((config->specialControl & (uint16_t)kENET_RxChecksumOffloadEnable) != 0U);
    if (config->miiDuplex == kENET_MiiHalfDuplex)
    {
        reg |= ENET_MAC_CONFIGURATION_IPG(ENET_HALFDUPLEX_DEFAULTIPG);
    }
    base->MAC_CONFIGURATION = reg;

    /* Enable channel. */
    base->MAC_RXQ_CTRL[0] = ENET_MAC_RXQ_CTRL_RXQ0EN(1) | ENET_MAC_RXQ_CTRL_RXQ1EN(1);
}

static status_t ENET_TxDescriptorsInit(ENET_Type *base, const enet_buffer_config_t *bufferConfig, uint8_t channel)
{
    uint16_t j;
    enet_tx_bd_struct_t *txbdPtr;
    const enet_buffer_config_t *buffCfg = bufferConfig;

    if (buffCfg == NULL)
    {
        return kStatus_InvalidArgument;
    }

    /* Check the ring length. */
    if (buffCfg->txRingLen < ENET_MIN_RINGLEN)
    {
        return kStatus_InvalidArgument;
    }
    /* Set the Tx descriptor start/tail pointer, shall be word aligned. */
    base->DMA_CH[channel].DMA_CHX_TXDESC_LIST_ADDR =
        (uint32_t)buffCfg->txDescStartAddrAlign & ENET_DMA_CH_DMA_CHX_TXDESC_LIST_ADDR_TDESLA_MASK;
    base->DMA_CH[channel].DMA_CHX_TXDESC_TAIL_PTR =
        (uint32_t)buffCfg->txDescTailAddrAlign & ENET_DMA_CH_DMA_CHX_TXDESC_TAIL_PTR_TDTP_MASK;
    /* Set the Tx ring length. */
    base->DMA_CH[channel].DMA_CHX_TXDESC_RING_LENGTH =
        ((uint32_t)buffCfg->txRingLen - 1U) & ENET_DMA_CH_DMA_CHX_TXDESC_RING_LENGTH_TDRL_MASK;

    /* Init the txbdPtr to the transmit descriptor start address. */
    txbdPtr = (enet_tx_bd_struct_t *)(buffCfg->txDescStartAddrAlign);
    for (j = 0; j < buffCfg->txRingLen; j++)
    {
        txbdPtr->tdes0 = 0;
        txbdPtr->tdes1 = 0;
        txbdPtr->tdes2 = 0;
        txbdPtr->tdes3 = 0;
        txbdPtr++;
    }

    return kStatus_Success;
}

static status_t ENET_RxDescriptorsInit(ENET_Type *base,
                                       enet_config_t *config,
                                       const enet_buffer_config_t *bufferConfig,
                                       uint8_t channel)
{
    uint16_t j;
    uint32_t reg;
    enet_rx_bd_struct_t *rxbdPtr;
    uint16_t index;
    bool doubleBuffEnable = ((config->specialControl & (uint16_t)kENET_DescDoubleBuffer) != 0U) ? true : false;
    const enet_buffer_config_t *buffCfg = bufferConfig;
    uint32_t control                    = ENET_RXDESCRIP_RD_BUFF1VALID_MASK;

    if (buffCfg == NULL)
    {
        return kStatus_InvalidArgument;
    }

    if (0U != (config->interrupt & (uint32_t)kENET_DmaRx))
    {
        control |= ENET_RXDESCRIP_RD_IOC_MASK;
    }

    if (doubleBuffEnable)
    {
        control |= ENET_RXDESCRIP_RD_BUFF2VALID_MASK;
    }

    /* Not give ownership to DMA before Rx buffer is ready */
    if ((config->rxBuffAlloc == NULL) || (config->rxBuffFree == NULL))
    {
        control |= ENET_RXDESCRIP_WR_OWN_MASK;
    }

    /* Check the ring length. */
    if (buffCfg->rxRingLen < ENET_MIN_RINGLEN)
    {
        return kStatus_InvalidArgument;
    }

    /* Set the Rx descriptor start/tail pointer, shall be word aligned. */
    base->DMA_CH[channel].DMA_CHX_RXDESC_LIST_ADDR =
        (uint32_t)buffCfg->rxDescStartAddrAlign & ENET_DMA_CH_DMA_CHX_RXDESC_LIST_ADDR_RDESLA_MASK;
    base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR =
        (uint32_t)buffCfg->rxDescTailAddrAlign & ENET_DMA_CH_DMA_CHX_RXDESC_LIST_ADDR_RDESLA_MASK;
    base->DMA_CH[channel].DMA_CHX_RX_CONTROL2 =
        ((uint32_t)buffCfg->rxRingLen - 1U) & ENET_DMA_CH_DMA_CHX_RX_CONTROL2_RDRL_MASK;
    reg = base->DMA_CH[channel].DMA_CHX_RX_CTRL & ~ENET_DMA_CH_DMA_CHX_RX_CTRL_RBSZ_13_Y_MASK;
    reg |= ENET_DMA_CH_DMA_CHX_RX_CTRL_RBSZ_13_Y(buffCfg->rxBuffSizeAlign >> ENET_RXBUFF_IGNORELSB_BITS);
    base->DMA_CH[channel].DMA_CHX_RX_CTRL = reg;

    /* Init the rxbdPtr to the receive descriptor start address. */
    rxbdPtr = (enet_rx_bd_struct_t *)(buffCfg->rxDescStartAddrAlign);

    for (j = 0; j < buffCfg->rxRingLen; j++)
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
            rxbdPtr->rdes0 = buffCfg->rxBufferStartAddr[index];
            /* The second buffer is set with 0 because it is not required for normal case. */
            if (doubleBuffEnable)
            {
                rxbdPtr->rdes2 = buffCfg->rxBufferStartAddr[index + 1U];
            }
            else
            {
                rxbdPtr->rdes2 = 0;
            }
        }

        /* Set the valid and DMA own flag.*/
        rxbdPtr->rdes3 = control;
        rxbdPtr++;
    }

    return kStatus_Success;
}

#ifdef ENET_PTP1588FEATURE_REQUIRED
static void ENET_SetPtp1588(ENET_Type *base, const enet_config_t *config, uint32_t ptpClkHz)
{
    assert(config);
    assert(config->ptpConfig);
    assert(ptpClkHz);

    uint32_t control;
    enet_ptp_config_t *ptpConfig = config->ptpConfig;

    /* Clear the timestamp interrupt first. */
    base->MAC_INTERRUPT_ENABLE &= ~ENET_MAC_INTERRUPT_ENABLE_TSIE_MASK;

    if (ptpConfig->fineUpdateEnable)
    {
        base->MAC_TIMESTAMP_CONTROL |= ENET_MAC_TIMESTAMP_CONTROL_TSCFUPDT_MASK;
        /* Set the initial added value for the fine update. */
        control                    = 100000000U / (ptpClkHz / ENET_MICRSECS_ONESECOND / ENET_SYSTIME_REQUIRED_CLK_MHZ);
        base->MAC_TIMESTAMP_ADDEND = control;
        base->MAC_TIMESTAMP_CONTROL |= ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK;
        while ((base->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK) != 0U)
        {
        }
    }

    /* Enable the IEEE 1588 timestamping and snapshot for event message. */
    control = ENET_MAC_TIMESTAMP_CONTROL_TSENA_MASK | ENET_MAC_TIMESTAMP_CONTROL_TSIPV4ENA_MASK |
              ENET_MAC_TIMESTAMP_CONTROL_TSIPV6ENA_MASK | ENET_MAC_TIMESTAMP_CONTROL_TSENALL_MASK |
              ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA_MASK | ENET_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL_MASK |
              ENET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR(ptpConfig->tsRollover);

    if (ptpConfig->ptp1588V2Enable)
    {
        control |= ENET_MAC_TIMESTAMP_CONTROL_TSVER2ENA_MASK | ENET_MAC_TIMESTAMP_CONTROL_TSIPENA_MASK;
    }

    /* Initialize the sub-second increment register. */
    if (ptpConfig->tsRollover != kENET_BinaryRollover)
    {
        base->MAC_SUB_SECOND_INCREMENT = ENET_MAC_SUB_SECOND_INCREMENT_SNSINC(ENET_NANOSECS_ONESECOND / ptpClkHz);
        base->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE = 0;
    }
    else
    {
        /* Round up. */
        uint32_t data                            = ENET_MAC_SYSTEM_TIME_NANOSECONDS_TSSS_MASK / ptpClkHz;
        base->MAC_SUB_SECOND_INCREMENT           = ENET_MAC_SUB_SECOND_INCREMENT_SNSINC(data);
        base->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE = 0;
    }
    /* Set the second.*/
    base->MAC_SYSTEM_TIME_SECONDS_UPDATE = 0;

    /* Initialize the system timer. */
    base->MAC_TIMESTAMP_CONTROL = control | ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK;
}
#endif /* ENET_PTP1588FEATURE_REQUIRED */

uint32_t ENET_GetInstance(ENET_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0U; instance < (uint32_t)FSL_FEATURE_SOC_MCX_ENET_COUNT; instance++)
    {
        if (s_enetBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < (uint32_t)FSL_FEATURE_SOC_MCX_ENET_COUNT);

    return instance;
}

/*!
 * brief Gets the ENET default configuration structure.
 *
 * The purpose of this API is to get the default ENET configure
 * structure for ENET_Init(). User may use the initialized
 * structure unchanged in ENET_Init(), or modify some fields of the
 * structure before calling ENET_Init().
 * Example:
   code
   enet_config_t config;
   ENET_GetDefaultConfig(&config);
   endcode
 * param config The ENET mac controller configuration structure pointer.
 */
void ENET_GetDefaultConfig(enet_config_t *config)
{
    /* Checks input parameter. */
    assert(config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Sets MII mode, full duplex, 100Mbps for MAC and PHY data interface. */
    config->miiMode   = kENET_RmiiMode;
    config->miiSpeed  = kENET_MiiSpeed100M;
    config->miiDuplex = kENET_MiiFullDuplex;

    /* Sets default configuration for other options. */
    config->specialControl = 0U;
    config->multiqueueCfg  = NULL;
    config->pauseDuration  = 0;

#ifdef ENET_PTP1588FEATURE_REQUIRED
    config->ptpConfig = NULL;
#endif /* ENET_PTP1588FEATURE_REQUIRED */
}

/*!
 * brief Initializes the ENET module.
 *
 * This function ungates the module clock and initializes it with the ENET basic
 * configuration.
 * note As our transactional transmit API use the zero-copy transmit buffer.
 * So there are two thing we emphasize here:
 *  1. Tx buffer free/requeue for application should be done in the Tx
 *  interrupt handler. Please set callback: kENET_TxIntEvent with Tx buffer free/requeue
 *  process APIs.
 *  2. The Tx interrupt is forced to open.
 *
 * param base    ENET peripheral base address.
 * param config  ENET mac configuration structure pointer.
 *        The "enet_config_t" type mac configuration return from ENET_GetDefaultConfig
 *        can be used directly. It is also possible to verify the Mac configuration using other methods.
 * param macAddr  ENET mac address of Ethernet device. This MAC address should be
 *        provided.
 * param clkSrcHz ENET input reference clock.
 */
void ENET_Init(ENET_Type *base, const enet_config_t *config, uint8_t *macAddr, uint32_t clkSrcHz)
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
    ENET_SetMacControl(base, config, macAddr, clkSrcHz);

#ifdef ENET_PTP1588FEATURE_REQUIRED
    ENET_SetPtp1588(base, config, config->ptpClkHz);
#endif /* ENET_PTP1588FEATURE_REQUIRED */

    /* Force to enable Tx interrupt for use transactional API to do Tx buffer free/requeue. */
    ENET_EnableInterrupts(base, (config->interrupt | (uint32_t)kENET_DmaTx));
}

/*!
 * brief Deinitializes the ENET module.

 * This function gates the module clock and disables the ENET module.
 *
 * param base  ENET peripheral base address.
 */
void ENET_Deinit(ENET_Type *base)
{
    /* Reset first and wait for the complete
     * The reset bit will automatically be cleared after complete. */
    base->DMA_MODE |= ENET_DMA_MODE_SWR_MASK;
    while ((base->DMA_MODE & ENET_DMA_MODE_SWR_MASK) != 0U)
    {
    }

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disables the clock source. */
    CLOCK_DisableClock(s_enetClock[ENET_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Initialize for all ENET descriptors.
 *
 * note This function finishes all Tx/Rx descriptors initialization. The descriptor initialization
 * should be called after ENET_Init().
 *
 * param base  ENET peripheral base address.
 * param config The configuration for ENET.
 * param bufferConfig All buffers configuration.
 */
status_t ENET_DescriptorInit(ENET_Type *base, enet_config_t *config, enet_buffer_config_t *bufferConfig)
{
    assert(config);
    assert(bufferConfig);

    uint8_t ringNum = config->multiqueueCfg == NULL ? 1U : 2U;
    uint8_t channel;

    for (channel = 0; channel < ringNum; channel++)
    {
        if (ENET_TxDescriptorsInit(base, bufferConfig, channel) != kStatus_Success)
        {
            return kStatus_Fail;
        }

        if (ENET_RxDescriptorsInit(base, config, bufferConfig, channel) != kStatus_Success)
        {
            return kStatus_Fail;
        }

        bufferConfig++;
    }
    return kStatus_Success;
}

/*!
 * brief Starts the ENET Tx/Rx.
 *  This function enable the Tx/Rx and starts the Tx/Rx DMA.
 * This shall be set after ENET initialization and before
 * starting to receive the data.
 *
 * param base  ENET peripheral base address.
 * param rxRingNum  The number of the used Rx rings. It shall not be
 * larger than the ENET_RING_NUM_MAX(2). If the ringNum is set with
 * 1, the ring 0 will be used.
 * param txRingNum  The number of the used Tx rings. It shall not be
 * larger than the ENET_RING_NUM_MAX(2). If the ringNum is set with
 * 1, the ring 0 will be used.
 *
 * note This must be called after all the ENET initilization.
 * And should be called when the ENET receive/transmit is required.
 */
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

    /* Enable the RX and TX at same time. */
    base->MAC_CONFIGURATION |= (ENET_MAC_CONFIGURATION_TE_MASK | ENET_MAC_CONFIGURATION_RE_MASK);
}

/*!
 * brief Set the second level IRQ handler
 *
 * param base ENET peripheral base address.
 * param ISRHandler The handler to install.
 */
void ENET_SetISRHandler(ENET_Type *base, enet_isr_t ISRHandler)
{
    s_enetIsr = ISRHandler;
    (void)EnableIRQ(s_enetIrqId[ENET_GetInstance(base)]);
}

/*!
 * brief Enables the ENET DMA and MAC interrupts.
 *
 * This function enables the ENET interrupt according to the provided mask. The mask
 * is a logical OR of enet_dma_interrupt_enable_t and enet_mac_interrupt_enable_t.
 * For example, to enable the dma and mac interrupt, do the following.
 * code
 *     ENET_EnableInterrupts(ENET, kENET_DmaRx | kENET_DmaTx | kENET_MacPmt);
 * endcode
 *
 * param base  ENET peripheral base address.
 * param mask  ENET interrupts to enable. This is a logical OR of both
 *             enumeration :: enet_dma_interrupt_enable_t and enet_mac_interrupt_enable_t.
 */
void ENET_EnableInterrupts(ENET_Type *base, uint32_t mask)
{
    uint32_t interrupt = mask & 0xFFFFU;
    uint8_t index;

    /* For dma interrupt. */
    if (interrupt != 0U)
    {
        for (index = 0; index < ENET_RING_NUM_MAX; index++)
        {
            /* Set for all abnormal interrupts. */
            if ((ENET_ABNORM_INT_MASK & interrupt) != 0U)
            {
                interrupt |= ENET_DMA_CH_DMA_CHX_INT_EN_AIE_MASK;
            }
            /* Set for all normal interrupts. */
            if ((ENET_NORM_INT_MASK & interrupt) != 0U)
            {
                interrupt |= ENET_DMA_CH_DMA_CHX_INT_EN_NIE_MASK;
            }
            base->DMA_CH[index].DMA_CHX_INT_EN = interrupt;
        }
    }
    interrupt = mask >> ENET_MACINT_ENUM_OFFSET;
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
 * is a logical OR of enumeration members. See the ref enet_mac_interrupt_enable_t.
 * For example, to clear the TX frame interrupt and RX frame interrupt, do the following.
 * code
 *     ENET_ClearMacInterruptStatus(ENET, kENET_MacPmt);
 * endcode
 *
 * param base  ENET peripheral base address.
 * param mask  ENET interrupt source to be cleared.
 * This is the logical OR of members of the enumeration :: enet_mac_interrupt_enable_t.
 */
void ENET_ClearMacInterruptStatus(ENET_Type *base, uint32_t mask)
{
    volatile uint32_t dummy;

    if ((mask & (uint32_t)kENET_MacTimestamp) != 0U)
    {
        dummy = base->MAC_TIMESTAMP_STATUS;
    }
    else if ((mask & (uint32_t)kENET_MacPmt) != 0U)
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
 * is a logical OR of enet_dma_interrupt_enable_t and enet_mac_interrupt_enable_t.
 * For example, to disable the dma and mac interrupt, do the following.
 * code
 *     ENET_DisableInterrupts(ENET, kENET_DmaRx | kENET_DmaTx | kENET_MacPmt);
 * endcode
 *
 * param base  ENET peripheral base address.
 * param mask  ENET interrupts to disables. This is a logical OR of both
 *             enumeration :: enet_dma_interrupt_enable_t and enet_mac_interrupt_enable_t.
 */
void ENET_DisableInterrupts(ENET_Type *base, uint32_t mask)
{
    uint32_t interrupt = mask & 0xFFFFU;
    uint8_t index;

    /* For dma interrupt. */
    if (interrupt != 0U)
    {
        for (index = 0; index < ENET_RING_NUM_MAX; index++)
        {
            /* Set for all abnormal interrupts. */
            if ((ENET_ABNORM_INT_MASK & interrupt) != 0U)
            {
                interrupt |= ENET_DMA_CH_DMA_CHX_INT_EN_AIE_MASK;
            }
            /* Set for all normal interrupts. */
            if ((ENET_NORM_INT_MASK & interrupt) != 0U)
            {
                interrupt |= ENET_DMA_CH_DMA_CHX_INT_EN_NIE_MASK;
            }
            base->DMA_CH[index].DMA_CHX_INT_EN &= ~interrupt;
        }
    }
    interrupt = mask >> ENET_MACINT_ENUM_OFFSET;
    if (interrupt != 0U)
    {
        /* MAC interrupt */
        base->MAC_INTERRUPT_ENABLE &= ~interrupt;
    }
}

/*!
 * brief Create ENET Handler
 *
 * This is a transactional API and it's provided to store all datas which are needed
 * during the whole transactional process. This API should not be used when you use
 * functional APIs to do data Tx/Rx. This is funtion will store many data/flag for
 * transactional use.
 *
 * param base  ENET peripheral base address.
 * param handle ENET handler.
 * param config ENET configuration.
 * param bufferConfig ENET buffer configuration.
 * param callback The callback function.
 * param userData The application data.
 */
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

    uint8_t ringNum                  = 1;
    uint8_t count                    = 0;
    uint8_t rxIntEnable              = 0;
    enet_buffer_config_t *buffConfig = bufferConfig;
    uint32_t txFifoSize;
    uint32_t pbl;

    /* Store transfer parameters in handle pointer. */
    (void)memset(handle, 0, sizeof(enet_handle_t));
    if ((config->specialControl & (uint32_t)kENET_DescDoubleBuffer) != 0U)
    {
        handle->doubleBuffEnable = true;
    }
    if (config->multiqueueCfg != NULL)
    {
        ringNum                = 2;
        handle->multiQueEnable = true;
    }
    for (count = 0; count < ringNum; count++)
    {
        handle->rxBdRing[count].rxBdBase        = buffConfig->rxDescStartAddrAlign;
        handle->rxBdRing[count].rxGenIdx        = 0;
        handle->rxBdRing[count].rxRingLen       = buffConfig->rxRingLen;
        handle->rxBdRing[count].rxBuffSizeAlign = buffConfig->rxBuffSizeAlign;

        handle->txBdRing[count].txBdBase    = buffConfig->txDescStartAddrAlign;
        handle->txBdRing[count].txRingLen   = buffConfig->txRingLen;
        handle->txBdRing[count].txGenIdx    = 0;
        handle->txBdRing[count].txConsumIdx = 0;
        handle->txBdRing[count].txDescUsed  = 0;

        handle->txDirtyRing[count].txDirtyBase = buffConfig->txDirtyStartAddr;
        handle->txDirtyRing[count].txRingLen   = buffConfig->txRingLen;
        handle->txDirtyRing[count].txGenIdx    = 0;
        handle->txDirtyRing[count].txConsumIdx = 0;

        handle->rxBufferStartAddr[count] = buffConfig->rxBufferStartAddr;

        /* Check if the Rx interrrupt is enabled. */
        rxIntEnable |= (uint8_t)(uint32_t)(base->DMA_CH[count].DMA_CHX_INT_EN & ENET_DMA_CH_DMA_CHX_INT_EN_RIE_MASK);

        /* Calculate the reserved space for Tx in certain cases. */
        if (0U != (base->MTL_QUEUE[count].MTL_TXQX_OP_MODE & ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TSF_MASK))
        {
            pbl = (base->DMA_CH[count].DMA_CHX_TX_CTRL & ENET_DMA_CH_DMA_CHX_TX_CTRL_TxPBL_MASK) >>
                  ENET_DMA_CH_DMA_CHX_TX_CTRL_TxPBL_SHIFT;
            pbl = ((base->DMA_CH[count].DMA_CHX_CTRL & ENET_DMA_CH_DMA_CHX_CTRL_PBLx8_MASK) != 0U) ? (8U * pbl) : pbl;
            txFifoSize                     = (uint32_t)pow((double)2,
                                                           (double)(uint32_t)(((base->MAC_HW_FEAT[1] & ENET_MAC_HW_FEAT_TXFIFOSIZE_MASK) >>
                                                           ENET_MAC_HW_FEAT_TXFIFOSIZE_SHIFT) +
                                                          7U));
            handle->txLenLimitation[count] = txFifoSize - (pbl + 6U) * (32U / 8U);
        }

        buffConfig++;
    }

    handle->rxintEnable = (rxIntEnable != 0U);

    /* Save the handle pointer in the global variables. */
    s_ENETHandle[ENET_GetInstance(base)] = handle;

    /* Set Rx alloc/free callback. */
    handle->rxBuffAlloc = config->rxBuffAlloc;
    handle->rxBuffFree  = config->rxBuffFree;

    /* Set callback and userData. */
    handle->callback = callback;
    handle->userData = userData;

    /* Set up interrupt and its handler. */
    ENET_SetISRHandler(base, ENET_IRQHandler);
}

/*!
 * brief Gets the ENET module Mac address.
 *
 * param base  ENET peripheral base address.
 * param macAddr The six-byte Mac address pointer.
 *        The pointer is allocated by application and input into the API.
 */
void ENET_GetMacAddr(ENET_Type *base, uint8_t *macAddr)
{
    assert(macAddr);

    uint32_t address = base->MAC_ADDRESS0_LOW;

    /* Get from physical address lower register. */
    macAddr[2] = (uint8_t)(0xFFU & (address >> 24U));
    macAddr[3] = (uint8_t)(0xFFU & (address >> 16U));
    macAddr[4] = (uint8_t)(0xFFU & (address >> 8U));
    macAddr[5] = (uint8_t)(0xFFU & address);

    /* Get from physical address high register. */
    address    = base->MAC_ADDRESS0_HIGH;
    macAddr[0] = (uint8_t)(0xFFU & (address >> 8U));
    macAddr[1] = (uint8_t)(0xFFU & address);
}

/*!
 * brief Sets the ENET SMI(serial management interface)- MII management interface.
 *
 * param base  ENET peripheral base address.
 */
void ENET_SetSMI(ENET_Type *base, uint32_t clkSrcHz)
{
    uint32_t crDiv  = 0;
    uint32_t clkMhz = clkSrcHz / 1000000U;

    assert((clkMhz >= 20U) && (clkMhz < 250U));

    if (clkMhz < 35U)
    {
        crDiv = 2;
    }
    else if (clkMhz < 60U)
    {
        crDiv = 3;
    }
    else if (clkMhz < 100U)
    {
        crDiv = 0;
    }
    else if (clkMhz < 150U)
    {
        crDiv = 1;
    }
    else if (clkMhz < 250U)
    {
        crDiv = 4;
    }
    else
    {
        /* Intentional empty */
    }

    base->MAC_MDIO_ADDRESS = ENET_MAC_MDIO_ADDRESS_CR(crDiv);
}

/*!
 * brief Starts a SMI write command.
 * support both MDIO IEEE802.3 Clause 22 and clause 45.
 *
 * param base  ENET peripheral base address.
 * param phyAddr The PHY address.
 * param regAddr The PHY register.
 * param data The data written to PHY.
 */
void ENET_StartSMIWrite(ENET_Type *base, uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
    uint32_t reg = base->MAC_MDIO_ADDRESS & ENET_MAC_MDIO_ADDRESS_CR_MASK;

    /* Build MII write command. */
    base->MAC_MDIO_ADDRESS =
        reg | ENET_MAC_MDIO_ADDRESS_GOC_0(1) | ENET_MAC_MDIO_ADDRESS_PA(phyAddr) | ENET_MAC_MDIO_ADDRESS_RDA(regAddr);
    base->MAC_MDIO_DATA = data;
    base->MAC_MDIO_ADDRESS |= ENET_MAC_MDIO_ADDRESS_GB_MASK;
}

/*!
 * brief Starts an SMI read command.
 * support both MDIO IEEE802.3 Clause 22 and clause 45.
 *
 * param base  ENET peripheral base address.
 * param phyAddr The PHY address.
 * param regAddr The PHY register.
 */
void ENET_StartSMIRead(ENET_Type *base, uint8_t phyAddr, uint8_t regAddr)
{
    uint32_t reg = base->MAC_MDIO_ADDRESS & ENET_MAC_MDIO_ADDRESS_CR_MASK;

    /* Build MII read command. */
    base->MAC_MDIO_ADDRESS = reg | ENET_MAC_MDIO_ADDRESS_GOC_0(1) | ENET_MAC_MDIO_ADDRESS_GOC_1(1) |
                             ENET_MAC_MDIO_ADDRESS_PA(phyAddr) | ENET_MAC_MDIO_ADDRESS_RDA(regAddr);
    base->MAC_MDIO_ADDRESS |= ENET_MAC_MDIO_ADDRESS_GB_MASK;
}

static status_t ENET_QOS_MDIOWaitTransferOver(ENET_Type *base)
{
    status_t result = kStatus_Success;
#ifdef ENET_MDIO_TIMEOUT_COUNT
    uint32_t counter;
#endif

#ifdef ENET_QOS_MDIO_TIMEOUT_COUNT
    for (counter = ENET_MDIO_TIMEOUT_COUNT; counter > 0U; counter--)
    {
        if (!ENET_IsSMIBusy(base))
        {
            break;
        }
    }
    /* Check for timeout. */
    if (0U == counter)
    {
        result = kStatus_Timeout;
    }
#else
    while (ENET_IsSMIBusy(base))
    {
    }
#endif
    return result;
}

/*!
 * @brief MDIO write.
 *
 * @param base  ENET peripheral base address.
 * @param phyAddr The PHY address.
 * @param regAddr The PHY register.
 * @param data The data written to PHY.
 * @return kStatus_Success  MDIO access succeeds.
 * @return kStatus_Timeout  MDIO access timeout.
 */
status_t ENET_MDIOWrite(ENET_Type *base, uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
    ENET_StartSMIWrite(base, phyAddr, regAddr, data);

    return ENET_QOS_MDIOWaitTransferOver(base);
}

/*!
 * @brief MDIO read.
 *
 * @param base  ENET peripheral base address.
 * @param phyAddr The PHY address.
 * @param regAddr The PHY register.
 * @param pData  The data read from PHY.
 * @return kStatus_Success  MDIO access succeeds.
 * @return kStatus_Timeout  MDIO access timeout.
 */
status_t ENET_MDIORead(ENET_Type *base, uint8_t phyAddr, uint8_t regAddr, uint16_t *pData)
{
    assert(pData);

    status_t result;

    ENET_StartSMIRead(base, phyAddr, regAddr);

    result = ENET_QOS_MDIOWaitTransferOver(base);
    if (result != kStatus_Success)
    {
        return result;
    }
    *pData = ENET_ReadSMIData(base);

    return result;
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
void ENET_EnterPowerDown(ENET_Type *base, uint32_t *wakeFilter)
{
    uint8_t index;
    uint32_t *reg = wakeFilter;

    /* Disable the Tx dma. */
    base->DMA_CH[0].DMA_CHX_TX_CTRL &= ~ENET_DMA_CH_DMA_CHX_TX_CTRL_ST_MASK;
    base->DMA_CH[1].DMA_CHX_TX_CTRL &= ~ENET_DMA_CH_DMA_CHX_TX_CTRL_ST_MASK;

    /* Disable the mac Tx/Rx. */
    base->MAC_CONFIGURATION &= ~(ENET_MAC_CONFIGURATION_RE_MASK | ENET_MAC_CONFIGURATION_TE_MASK);
    /* Enable the remote wakeup packet and enable the power down mode. */
    if (wakeFilter != NULL)
    {
        for (index = 0; index < ENET_WAKEUPFILTER_NUM; index++)
        {
            base->MAC_RWK_PACKET_FILTER = *reg;
            reg++;
        }
    }
    base->MAC_PMT_CONTROL_STATUS = ENET_MAC_PMT_CONTROL_STATUS_MGKPKTEN_MASK |
                                   ENET_MAC_PMT_CONTROL_STATUS_RWKPKTEN_MASK | ENET_MAC_PMT_CONTROL_STATUS_PWRDWN_MASK;

    /* Enable the MAC Rx. */
    base->MAC_CONFIGURATION |= ENET_MAC_CONFIGURATION_RE_MASK;
}

/*!
 * brief Set VLAN control.
 *
 * param base  ENET peripheral base address.
 * param control  VLAN control configuration.
 */
status_t ENET_SetVlanCtrl(ENET_Type *base, enet_vlan_ctrl_t *control)
{
    uint32_t vl = (((uint32_t)control->rxVlanTag.pcp) << 13U) | (((uint32_t)control->rxVlanTag.dei) << 12U) |
                  (uint32_t)control->rxVlanTag.vid;
    uint32_t vlanCtrl;

    if ((control->innerVlanFilterMatch) && (!control->doubleVlanEnable))
    {
        return kStatus_Fail;
    }

    vlanCtrl = ENET_MAC_VLAN_TAG_CTRL_VL(vl) | ENET_MAC_VLAN_TAG_CTRL_ETV(control->vidComparison) |
               ENET_MAC_VLAN_TAG_CTRL_VTIM(control->vlanInverseMatch) |
               ENET_MAC_VLAN_TAG_CTRL_ESVL(control->svlanEnable) |
               ENET_MAC_VLAN_TAG_CTRL_DOVLTC(control->disableVlanTypeCheck) |
               ENET_MAC_VLAN_TAG_CTRL_EVLS(control->rxOuterVlanStrip) |
               ENET_MAC_VLAN_TAG_CTRL_EIVLS(control->rxInnerVlanStrip) |
               ENET_MAC_VLAN_TAG_CTRL_EDVLP(control->doubleVlanEnable) |
               ENET_MAC_VLAN_TAG_CTRL_ERIVLT(control->innerVlanFilterMatch) |
               ENET_MAC_VLAN_TAG_CTRL_EVLRXS(control->outerTagInRxStatus) |
               ENET_MAC_VLAN_TAG_CTRL_EIVLRXS(control->innerTagInRxStatus);

    if (control->rxVlanTag.tpid == kENET_StanSvlan)
    {
        vlanCtrl |= ENET_MAC_VLAN_TAG_CTRL_ERSVLM_MASK;
    }
    base->MAC_VLAN_TAG_CTRL = vlanCtrl;

    return kStatus_Success;
}

/*!
 * brief Set Tx outer VLAN configuration.
 *
 * param base  ENET peripheral base address.
 * param config  Tx VLAN operation configuration.
 * param channel  The channel to apply this configuration.
 */
status_t ENET_SetTxOuterVlan(ENET_Type *base, enet_vlan_tx_config_t *config, enet_vlan_tx_channel_t channel)
{
    uint32_t vlt =
        (((uint32_t)config->tag.pcp) << 13U) | (((uint32_t)config->tag.dei) << 12U) | (uint32_t)config->tag.vid;
    uint32_t vlanConfig = ENET_MAC_VLAN_INCL_VLTI(config->txDescVlan) | ENET_MAC_VLAN_INCL_CSVL(config->tag.tpid) |
                          ENET_MAC_VLAN_INCL_VLC(config->ops) | ENET_MAC_VLAN_INCL_VLT(vlt);

    if ((config->tag.tpid == kENET_StanSvlan) && ((base->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_ESVL_MASK) == 0U))
    {
        return kStatus_Fail;
    }

    if (config->ops != kENET_NoOps)
    {
        vlanConfig |= ENET_MAC_VLAN_INCL_VLP(1);
    }

    if (channel != kENET_VlanTagAllChannels)
    {
        while ((base->MAC_VLAN_INCL & ENET_MAC_VLAN_INCL_BUSY_MASK) != 0U)
        {
        }

        /* Clear and status ans reset the power down. */
        base->MAC_VLAN_INCL |=
            ENET_MAC_VLAN_INCL_CBTI_MASK | ENET_MAC_VLAN_INCL_RDWR_MASK | ENET_MAC_VLAN_INCL_ADDR(channel) | vlanConfig;

        while ((base->MAC_VLAN_INCL & ENET_MAC_VLAN_INCL_BUSY_MASK) != 0U)
        {
        }

        /* Clear set channel bits. */
        base->MAC_VLAN_INCL &= ~(ENET_MAC_VLAN_INCL_RDWR_MASK | ENET_MAC_VLAN_INCL_CBTI_MASK);
    }
    else
    {
        base->MAC_VLAN_INCL = vlanConfig;
    }

    return kStatus_Success;
}

/*!
 * brief Set Tx inner VLAN configuration.
 *
 * param base  ENET peripheral base address.
 * param config  Tx VLAN operation configuration.
 */
status_t ENET_SetTxInnerVlan(ENET_Type *base, enet_vlan_tx_config_t *config)
{
    uint32_t vlt =
        (((uint32_t)config->tag.pcp) << 13U) | (((uint32_t)config->tag.dei) << 12U) | (uint32_t)config->tag.vid;
    uint32_t vlanConfig = ENET_MAC_INNER_VLAN_INCL_VLTI(config->txDescVlan) |
                          ENET_MAC_INNER_VLAN_INCL_CSVL(config->tag.tpid) | ENET_MAC_INNER_VLAN_INCL_VLC(config->ops) |
                          ENET_MAC_INNER_VLAN_INCL_VLT(vlt);

    /* S-VLAN should be enabled first. */
    if ((config->tag.tpid == kENET_StanSvlan) && ((base->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_ESVL_MASK) == 0U))
    {
        return kStatus_Fail;
    }

    /* Double VLAN should be enabled first for inner VLAN. */
    if ((base->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_EDVLP_MASK) == 0U)
    {
        return kStatus_Fail;
    }

    if (config->ops != kENET_NoOps)
    {
        vlanConfig |= ENET_MAC_INNER_VLAN_INCL_VLP(1);
    }
    base->MAC_INNER_VLAN_INCL = vlanConfig;

    return kStatus_Success;
}

/*!
 * brief Gets the size of the read frame.
 * This function gets a received frame size from the ENET buffer descriptors.
 * note The FCS of the frame is automatically removed by MAC and the size is the length without the FCS.
 * After calling ENET_GetRxFrameSize, ENET_ReadFrame() should be called to update the
 * receive buffers If the result is not "kStatus_ENET_RxFrameEmpty".
 *
 * param handle The ENET handler structure. This is the same handler pointer used in the ENET_Init.
 * param length The length of the valid frame received.
 * param channel The DMAC channel for the Rx.
 * retval kStatus_ENET_RxFrameEmpty No frame received. Should not call ENET_ReadFrame to read frame.
 * retval kStatus_ENET_RxFrameError Data error happens. ENET_ReadFrame should be called with NULL data
 *         and NULL length to update the receive buffers.
 * retval kStatus_Success Receive a frame Successfully then the ENET_ReadFrame
 *         should be called with the right data buffer and the captured data length input.
 */
status_t ENET_GetRxFrameSize(ENET_Type *base, enet_handle_t *handle, uint32_t *length, uint8_t channel)
{
    assert(handle);
    assert(length);

    enet_rx_bd_ring_t *rxBdRing = (enet_rx_bd_ring_t *)&handle->rxBdRing[channel];
    enet_rx_bd_struct_t *rxDesc = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
    uint16_t index              = rxBdRing->rxGenIdx;

    /* Reset the length to zero. */
    *length = 0;

    if ((rxDesc->rdes3 & ENET_RXDESCRIP_WR_OWN_MASK) != 0U)
    {
        return kStatus_ENET_RxFrameEmpty;
    }
    else
    {
        do
        {
            /* Application owns the buffer descriptor, get the length. */
            if ((rxDesc->rdes3 & ENET_RXDESCRIP_WR_LD_MASK) != 0U)
            {
                if ((rxDesc->rdes3 & ENET_RXDESCRIP_WR_ERRSUM_MASK) != 0U)
                {
                    return kStatus_ENET_RxFrameError;
                }
                *length = (rxDesc->rdes3 & ENET_RXDESCRIP_WR_PACKETLEN_MASK) - ENET_FCS_LEN;
                return kStatus_Success;
            }

            index  = ENET_IncreaseIndex(index, rxBdRing->rxRingLen);
            rxDesc = rxBdRing->rxBdBase + index;
        } while (index != rxBdRing->rxGenIdx);

        return kStatus_ENET_RxFrameError;
    }
}

/*!
 * brief Reads a frame from the ENET device.
 * This function reads a frame from the ENET DMA descriptors.
 * The ENET_GetRxFrameSize should be used to get the size of the prepared data buffer.
 * For example use Rx dma channel 0:
 * code
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
 * endcode
 * param base  ENET peripheral base address.
 * param handle The ENET handler structure. This is the same handler pointer used in the ENET_Init.
 * param data The data buffer provided by user to store the frame which memory size should be at least "length".
 * param length The size of the data buffer which is still the length of the received frame.
 * param channel The Rx DMA channel. shall not be larger than 2.
 * param timestamp The timestamp address to store received timestamp.
 * return The execute status, successful or failure.
 */
status_t ENET_ReadFrame(
    ENET_Type *base, enet_handle_t *handle, uint8_t *data, uint32_t length, uint8_t channel, enet_ptp_time_t *timestamp)
{
    assert(handle);

    enet_rx_bd_ring_t *rxBdRing = (enet_rx_bd_ring_t *)&handle->rxBdRing[channel];
    uint32_t len                = 0;
    uint32_t offset             = 0;
    bool isLastBuff             = false;
    status_t result             = kStatus_Fail;
    bool suspend                = false;
    enet_rx_bd_struct_t *rxDesc;
#ifdef ENET_PTP1588FEATURE_REQUIRED
    uint32_t buffer;
    uint32_t bufferAdd;
#endif /* ENET_PTP1588FEATURE_REQUIRED */

    /* Suspend and command for Rx. */
    if ((base->DMA_CH[channel].DMA_CHX_STAT & ENET_DMA_CH_DMA_CHX_STAT_RBU_MASK) != 0U)
    {
        suspend = true;
    }

    /* For data-NULL input, only update the buffer descriptor. */
    if (data == NULL)
    {
        ENET_DropFrame(base, handle, channel);
        result = kStatus_Success;
    }
    else
    {
        while (!isLastBuff)
        {
            /* The last buffer descriptor of a frame. */
            rxDesc             = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
            rxBdRing->rxGenIdx = ENET_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);

            if ((rxDesc->rdes3 & ENET_RXDESCRIP_WR_LD_MASK) != 0U)
            {
                /* This is a valid frame. */
                isLastBuff = true;
                if (length == ((rxDesc->rdes3 & ENET_RXDESCRIP_WR_PACKETLEN_MASK) - ENET_FCS_LEN))
                {
                    /* Copy the frame to user's buffer. */
                    len = length - offset;
                    if (len > rxBdRing->rxBuffSizeAlign)
                    {
                        (void)memcpy((void *)(uint32_t *)(uint32_t)(data + offset), (void *)(uint32_t *)rxDesc->rdes0,
                                     rxBdRing->rxBuffSizeAlign);
                        offset += rxBdRing->rxBuffSizeAlign;
                        (void)memcpy((void *)(uint32_t *)(uint32_t)(data + offset), (void *)(uint32_t *)rxDesc->rdes2,
                                     len - rxBdRing->rxBuffSizeAlign);
                    }
                    else
                    {
                        (void)memcpy((void *)(uint32_t *)(uint32_t)(data + offset), (void *)(uint32_t *)rxDesc->rdes0,
                                     len);
                    }

                    result = kStatus_Success;
                }

                /* Updates the receive buffer descriptors. */
                ENET_UpdateRxDescriptor(rxDesc, NULL, NULL, handle->rxintEnable, handle->doubleBuffEnable);
#ifdef ENET_PTP1588FEATURE_REQUIRED
                /* Store the Rx timestamp which is in the next buffer descriptor of the last
                 * descriptor of a frame. */
                rxDesc = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;

                /* Reinit for the context descritor which has been updated by DMA. */
                if ((rxDesc->rdes3 & ENET_RXDESCRIP_WR_CTXT_MASK) != 0U)
                {
                    if (timestamp != NULL)
                    {
                        uint32_t timerCount;

                        /* Get receive frame timestamp. */
                        timestamp->second = rxDesc->rdes1;
                        timerCount        = rxDesc->rdes0;
                        if ((base->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_MASK) == 0U)
                        {
                            /* Binary rollover. */
                            timestamp->nanosecond = ENET_BINARY_ROLLOVER_SCALE(timerCount);
                        }
                        else
                        {
                            timestamp->nanosecond = timerCount;
                        }
                    }

                    if (!handle->doubleBuffEnable)
                    {
                        buffer = handle->rxBufferStartAddr[channel][rxBdRing->rxGenIdx];
                        ENET_UpdateRxDescriptor(rxDesc, (void *)(uint32_t *)buffer, NULL, handle->rxintEnable,
                                                handle->doubleBuffEnable);
                    }
                    else
                    {
                        buffer    = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx];
                        bufferAdd = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx + 1U];
                        ENET_UpdateRxDescriptor(rxDesc, (void *)(uint32_t *)buffer, (void *)(uint32_t *)bufferAdd,
                                                handle->rxintEnable, handle->doubleBuffEnable);
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

                (void)memcpy((void *)(uint32_t *)(uint32_t)(data + offset), (void *)(uint32_t *)rxDesc->rdes0,
                             rxBdRing->rxBuffSizeAlign);
                offset += rxBdRing->rxBuffSizeAlign;
                if (((rxDesc->rdes2) != 0U) && (handle->doubleBuffEnable))
                {
                    (void)memcpy((void *)(uint32_t *)(uint32_t)(data + offset), (void *)(uint32_t *)rxDesc->rdes2,
                                 rxBdRing->rxBuffSizeAlign);
                    offset += rxBdRing->rxBuffSizeAlign;
                }

                /* Updates the receive buffer descriptors. */
                ENET_UpdateRxDescriptor(rxDesc, NULL, NULL, handle->rxintEnable, handle->doubleBuffEnable);
            }
        }
    }

    /* Set command for Rx when it is suspend. */
    if (suspend)
    {
        base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR = base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR;
    }

    return result;
}

/*!
 * brief Updates the buffers and the own status for a given Rx descriptor.
 *  This function is a low level functional API to Updates the
 *  buffers and the own status for a given Rx descriptor.
 *
 * param rxDesc  The given Rx descriptor.
 * param buffer1  The first buffer address in the descriptor.
 * param buffer2  The second buffer address in the descriptor.
 * param intEnable Interrupt enable flag.
 * param doubleBuffEnable The double buffer enable flag.
 *
 * note This must be called after all the ENET initilization.
 * And should be called when the ENET receive/transmit is required.
 */
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
    if (buffer1 != NULL)
    {
        rxDesc->rdes0 = (uint32_t)(uint32_t *)buffer1;
    }
    if (buffer2 != NULL)
    {
        rxDesc->rdes2 = (uint32_t)(uint32_t *)buffer2;
    }
    else
    {
        rxDesc->rdes2 = 0;
    }

    rxDesc->rdes1 = 0;
    rxDesc->rdes3 = control;
}

/*!
 * brief Allocates Rx buffers for all BDs.
 * It's used for zero copy Rx. In zero copy Rx case, Rx buffers are dynamic. This function
 * will populate initial buffers in all BDs for receiving. Then ENET_GetRxFrame() is used
 * to get Rx frame with zero copy, it will allocate new buffer to replace the buffer in BD taken
 * by application, application should free those buffers after they're used.
 *
 * note This function should be called after ENET_CreateHandler() and buffer allocating callback
 * function should be ready.
 *
 * param base  ENET peripheral base address.
 * param handle The ENET handler structure. This is the same handler pointer used in the ENET_Init.
 */
status_t ENET_RxBufferAllocAll(ENET_Type *base, enet_handle_t *handle)
{
    status_t result = kStatus_Success;
    enet_rx_bd_struct_t *rxbdPtr;
    uint32_t buffAddr;
    uint8_t channel;
    uint16_t index;
    uint16_t j;
    uint8_t ringNum = (handle->multiQueEnable) ? 2U : 1U;

    if ((handle->rxBuffAlloc == NULL) || (handle->rxBuffFree == NULL))
    {
        return kStatus_ENET_InitMemoryFail;
    }

    for (channel = 0; channel < ringNum; channel++)
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

            buffAddr = (uint32_t)(uint32_t *)handle->rxBuffAlloc(base, handle->userData, channel);
            if (buffAddr == 0U)
            {
                result = kStatus_ENET_InitMemoryFail;
                break;
            }

            rxbdPtr->rdes0                            = buffAddr;
            handle->rxBufferStartAddr[channel][index] = buffAddr;

            /* The second buffer is set with 0 because it is not required for normal case. */
            if (handle->doubleBuffEnable)
            {
                buffAddr = (uint32_t)(uint32_t *)handle->rxBuffAlloc(base, handle->userData, channel);
                if (buffAddr == 0U)
                {
                    result = kStatus_ENET_InitMemoryFail;
                    break;
                }

                rxbdPtr->rdes2                                 = buffAddr;
                handle->rxBufferStartAddr[channel][index + 1U] = buffAddr;
            }
            else
            {
                rxbdPtr->rdes2 = 0;
            }

            /* Set the valid and DMA own flag.*/
            rxbdPtr->rdes3 |= ENET_RXDESCRIP_WR_OWN_MASK;
            rxbdPtr++;
        }
    }

    if (result == kStatus_ENET_InitMemoryFail)
    {
        ENET_RxBufferFreeAll(base, handle);
    }

    return result;
}

/*!
 * brief Frees Rx buffers in all BDs.
 * It's used for zero copy Rx. In zero copy Rx case, Rx buffers are dynamic. This function
 * frees left buffers in all BDs.
 *
 * param base  ENET peripheral base address.
 * param handle The ENET handler structure. This is the same handler pointer used in the ENET_Init.
 */
void ENET_RxBufferFreeAll(ENET_Type *base, enet_handle_t *handle)
{
    uint8_t ringNum = (handle->multiQueEnable) ? 2U : 1U;
    uint8_t channel;
    uint32_t buffAddr;
    uint16_t index;
    uint16_t j;

    if (handle->rxBuffFree != NULL)
    {
        for (channel = 0; channel < ringNum; channel++)
        {
            for (j = 0U; j < handle->rxBdRing[channel].rxRingLen; j++)
            {
                index = (handle->doubleBuffEnable) ? (2U * j) : j;

                buffAddr = (uint32_t)handle->rxBufferStartAddr[channel][index];
                if (buffAddr != 0U)
                {
                    handle->rxBuffFree(base, (void *)(uint32_t *)buffAddr, handle->userData, channel);
                }

                /* The second buffer is set with 0 because it is not required for normal case. */
                if (handle->doubleBuffEnable)
                {
                    buffAddr = (uint32_t)handle->rxBufferStartAddr[channel][index + 1U];
                    if (buffAddr != 0U)
                    {
                        handle->rxBuffFree(base, (void *)(uint32_t *)buffAddr, handle->userData, channel);
                    }
                }
            }
        }
    }
}

static inline void ENET_GetRxFrameErr(enet_rx_bd_struct_t *rxDesc, enet_rx_frame_error_t *rxFrameError)
{
    union _frame_error
    {
        uint32_t data;
        enet_rx_frame_error_t frameError;
    };
    union _frame_error error;

    error.data    = ENET_FRAME_RX_ERROR_BITS(rxDesc->rdes3);
    *rxFrameError = error.frameError;
}

static void ENET_DropFrame(ENET_Type *base, enet_handle_t *handle, uint8_t channel)
{
    enet_rx_bd_ring_t *rxBdRing = (enet_rx_bd_ring_t *)&handle->rxBdRing[channel];
    enet_rx_bd_struct_t *rxDesc;
    uint16_t index = rxBdRing->rxGenIdx;
#ifdef ENET_PTP1588FEATURE_REQUIRED
    bool tsAvailable   = false;
    uint32_t buff1Addr = 0;
    uint32_t buff2Addr = 0;
    uint32_t rdes1;
#endif /* ENET_PTP1588FEATURE_REQUIRED */
    uint32_t rdes3;

    /* Not check DMA ownership here, assume there's at least one valid frame left in BD ring */
    do
    {
        /* Update the BD to idle status. */
        rxDesc = &rxBdRing->rxBdBase[rxBdRing->rxGenIdx];
#ifdef ENET_PTP1588FEATURE_REQUIRED
        rdes1 = rxDesc->rdes1;
#endif
        rdes3 = rxDesc->rdes3;
        ENET_UpdateRxDescriptor(rxDesc, NULL, NULL, handle->rxintEnable, handle->doubleBuffEnable);
        rxBdRing->rxGenIdx = ENET_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);

        /* Find the last buffer descriptor for the frame. */
        if ((rdes3 & ENET_RXDESCRIP_WR_LD_MASK) != 0U)
        {
#ifdef ENET_PTP1588FEATURE_REQUIRED
            if ((rdes3 & ENET_RXDESCRIP_WR_RS1V_MASK) != 0U)
            {
                if ((rdes1 & ENET_RXDESCRIP_WR_PTPTSA_MASK) != 0U)
                {
                    tsAvailable = true;
                }
            }

            /* Reinit for the context descriptor which has been updated by DMA. */
            rxDesc = &rxBdRing->rxBdBase[rxBdRing->rxGenIdx];

            if (tsAvailable && ((rxDesc->rdes3 & ENET_RXDESCRIP_WR_CTXT_MASK) != 0U))
            {
                if (!handle->doubleBuffEnable)
                {
                    buff1Addr = handle->rxBufferStartAddr[channel][rxBdRing->rxGenIdx];
                    ENET_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, NULL, handle->rxintEnable,
                                            handle->doubleBuffEnable);
                }
                else
                {
                    buff1Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx];
                    buff2Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx + 1U];
                    ENET_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, (void *)(uint8_t *)buff2Addr,
                                            handle->rxintEnable, handle->doubleBuffEnable);
                }
                rxBdRing->rxGenIdx = ENET_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);
            }
#endif /*  ENET_PTP1588FEATURE_REQUIRED */
            break;
        }
    } while (rxBdRing->rxGenIdx != index);

    /* Always try to start receive, in case it had stopped */
    base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR = (uint32_t)(uint8_t *)&rxBdRing->rxBdBase[rxBdRing->rxRingLen];
}

/*!
 * brief Receives one frame in specified BD ring with zero copy.
 *
 * This function will use the user-defined allocate and free callback. Every time application gets one frame through
 * this function, driver will allocate new buffers for the BDs whose buffers have been taken by application.
 * note This function will drop current frame and update related BDs as available for DMA if new buffers allocating
 * fails. Application must provide a memory pool including at least BD number + 1 buffers(+2 if enable double buffer)
 * to make this function work normally.
 *
 * param base   ENET peripheral base address.
 * param handle The ENET handler pointer. This is the same handler pointer used in the ENET_Init.
 * param rxFrame The received frame information structure provided by user.
 * param channel The Rx DMA channel. Shall not be larger than 2.
 * retval kStatus_Success  Succeed to get one frame and allocate new memory for Rx buffer.
 * retval kStatus_ENET_RxFrameEmpty  There's no Rx frame in the BD.
 * retval kStatus_ENET_RxFrameError  There's issue in this receiving. In this function, issue frame will be dropped.
 * retval kStatus_ENET_RxFrameDrop  There's no new buffer memory for BD, dropped this frame.
 */
status_t ENET_GetRxFrame(ENET_Type *base, enet_handle_t *handle, enet_rx_frame_struct_t *rxFrame, uint8_t channel)
{
    assert(handle != NULL);
    assert(channel < ENET_RING_NUM_MAX);

    enet_rx_bd_ring_t *rxBdRing = (enet_rx_bd_ring_t *)&handle->rxBdRing[channel];
    enet_rx_bd_struct_t *rxDesc = &rxBdRing->rxBdBase[rxBdRing->rxGenIdx];
    uint16_t index              = rxBdRing->rxGenIdx;
    status_t result             = kStatus_Success;
    uint32_t buff1Addr          = 0;
    uint32_t buff2Addr          = 0;
    uint16_t buff1Len           = 0;
    uint16_t buff2Len           = 0;
    uint16_t offset             = 0;
    void *newBuff1              = NULL;
    void *newBuff2              = NULL;
    bool isDrop                 = false;
    bool isLastBuff             = false;
#ifdef ENET_PTP1588FEATURE_REQUIRED
    bool tsAvailable = false;
#endif /* ENET_PTP1588FEATURE_REQUIRED */

    /* Check the frame status. */
    do
    {
        if ((rxDesc->rdes3 & ENET_RXDESCRIP_WR_OWN_MASK) != 0U)
        {
            result = kStatus_ENET_RxFrameEmpty;
            break;
        }

        /* Check timestamp and error. */
        if ((rxDesc->rdes3 & ENET_RXDESCRIP_WR_LD_MASK) != 0U)
        {
#ifdef ENET_PTP1588FEATURE_REQUIRED
            if ((rxDesc->rdes3 & ENET_RXDESCRIP_WR_RS1V_MASK) != 0U)
            {
                if ((rxDesc->rdes1 & ENET_RXDESCRIP_WR_PTPTSA_MASK) != 0U)
                {
                    tsAvailable = true;
                }
            }
#endif /* ENET_PTP1588FEATURE_REQUIRED */

            /* Get the frame error if there is. */
            if ((rxDesc->rdes3 & ENET_RXDESCRIP_WR_ERRSUM_MASK) != 0U)
            {
                ENET_GetRxFrameErr(rxDesc, &rxFrame->rxFrameError);
                result = kStatus_ENET_RxFrameError;
            }
            else if ((rxDesc->rdes3 & ENET_RXDESCRIP_WR_PACKETLEN_MASK) == 0U)
            {
                result = kStatus_ENET_RxFrameEmpty;
            }
            else
            {
                /* Intentional empty */
            }
            break;
        }

        index = ENET_IncreaseIndex(index, rxBdRing->rxRingLen);
        if (index == rxBdRing->rxGenIdx)
        {
            result = kStatus_ENET_RxFrameEmpty;
            break;
        }
        rxDesc = &rxBdRing->rxBdBase[index];
    } while (index != rxBdRing->rxGenIdx);

    /* Drop the error frame and return error. */
    if (result != kStatus_Success)
    {
        if (result == kStatus_ENET_RxFrameError)
        {
            ENET_DropFrame(base, handle, channel);
        }
        return result;
    }

    /* Get the valid frame */
    index = 0;
    do
    {
        rxDesc = &rxBdRing->rxBdBase[rxBdRing->rxGenIdx];

        /* Calculate the buffer and frame length. */
        if ((rxDesc->rdes3 & ENET_RXDESCRIP_WR_LD_MASK) != 0U)
        {
            isLastBuff      = true;
            rxFrame->totLen = (uint16_t)(rxDesc->rdes3 & ENET_RXDESCRIP_WR_PACKETLEN_MASK);

            if (rxFrame->totLen - offset > (uint16_t)rxBdRing->rxBuffSizeAlign)
            {
                /* Here must be double buffer. */
                assert(handle->doubleBuffEnable);

                buff1Len = (uint16_t)rxBdRing->rxBuffSizeAlign;
                buff2Len = rxFrame->totLen - offset - (uint16_t)rxBdRing->rxBuffSizeAlign;
            }
            else
            {
                buff1Len = rxFrame->totLen - offset;
            }
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
                buff1Addr                          = handle->rxBufferStartAddr[channel][rxBdRing->rxGenIdx];
                rxFrame->rxBuffArray[index].buffer = (void *)(uint32_t *)buff1Addr;
                rxFrame->rxBuffArray[index].length = buff1Len;
                index++;
            }
            else
            {
                buff1Addr                          = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx];
                rxFrame->rxBuffArray[index].buffer = (void *)(uint32_t *)buff1Addr;
                rxFrame->rxBuffArray[index].length = buff1Len;
                index++;

                /* If there's no data in buffer2, not add it into rxFrame */
                if (buff2Len != 0U)
                {
                    buff2Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx + 1U];
                    rxFrame->rxBuffArray[index].buffer = (void *)(uint32_t *)buff2Addr;
                    rxFrame->rxBuffArray[index].length = buff2Len;
                    index++;
                }
            }

            /* Give new buffer from application to BD */
            if (!handle->doubleBuffEnable)
            {
                buff1Addr                                              = (uint32_t)(uint32_t *)newBuff1;
                handle->rxBufferStartAddr[channel][rxBdRing->rxGenIdx] = buff1Addr;
                ENET_UpdateRxDescriptor(rxDesc, (void *)(uint32_t *)buff1Addr, NULL, handle->rxintEnable,
                                        handle->doubleBuffEnable);
            }
            else
            {
                buff1Addr                                                   = (uint32_t)(uint32_t *)newBuff1;
                handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx] = buff1Addr;

                if (buff2Len != 0U)
                {
                    buff2Addr                                                        = (uint32_t)(uint32_t *)newBuff2;
                    handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx + 1U] = buff2Addr;
                }
                else
                {
                    /* If there's no data in buffer2, keep it */
                    buff2Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx + 1U];
                }

                ENET_UpdateRxDescriptor(rxDesc, (void *)(uint32_t *)buff1Addr, (void *)(uint32_t *)buff2Addr,
                                        handle->rxintEnable, handle->doubleBuffEnable);
            }
            rxBdRing->rxGenIdx = ENET_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);

#ifdef ENET_PTP1588FEATURE_REQUIRED
            /* Update context BD if there is */
            if (isLastBuff && tsAvailable)
            {
                rxDesc = &rxBdRing->rxBdBase[rxBdRing->rxGenIdx];
                if ((rxDesc->rdes3 & ENET_RXDESCRIP_WR_CTXT_MASK) != 0U)
                {
                    uint32_t timerCount;

                    /* Get receive frame timestamp. */
                    rxFrame->rxAttribute.timestamp.second = rxDesc->rdes1;
                    timerCount                            = rxDesc->rdes0;
                    if ((base->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_MASK) == 0U)
                    {
                        /* Binary rollover. */
                        rxFrame->rxAttribute.timestamp.nanosecond = ENET_BINARY_ROLLOVER_SCALE(timerCount);
                    }
                    else
                    {
                        rxFrame->rxAttribute.timestamp.nanosecond = timerCount;
                    }
                    rxFrame->rxAttribute.isTsAvail = true;

                    if (!handle->doubleBuffEnable)
                    {
                        buff1Addr = handle->rxBufferStartAddr[channel][rxBdRing->rxGenIdx];
                        ENET_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, NULL, handle->rxintEnable,
                                                handle->doubleBuffEnable);
                    }
                    else
                    {
                        buff1Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx];
                        buff2Addr = handle->rxBufferStartAddr[channel][2U * rxBdRing->rxGenIdx + 1U];
                        ENET_UpdateRxDescriptor(rxDesc, (void *)(uint8_t *)buff1Addr, (void *)(uint8_t *)buff2Addr,
                                                handle->rxintEnable, handle->doubleBuffEnable);
                    }
                    rxBdRing->rxGenIdx = ENET_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);
                }
            }
#else
            rxFrame->rxAttribute.isTsAvail = false;
#endif /* ENET_PTP1588FEATURE_REQUIRED */

            /* Always try to start receive, in case it had stopped */
            base->DMA_CH[channel].DMA_CHX_RXDESC_TAIL_PTR =
                (uint32_t)(uint8_t *)&rxBdRing->rxBdBase[rxBdRing->rxRingLen];
        }
        else
        {
            /* Drop frame if there's no new buffer memory */

            /* Free the incomplete frame buffers. */
            while (index-- != 0U)
            {
                handle->rxBuffFree(base, rxFrame->rxBuffArray[index].buffer, handle->userData, channel);
            }

            /* Update all left BDs of this frame from current index. */
            ENET_DropFrame(base, handle, channel);

            result = kStatus_ENET_RxFrameDrop;
            break;
        }
    } while (!isLastBuff);

    /* Remove 4 bytes FCS. */
    if (result == kStatus_Success)
    {
        /* Find the last 4 bytes in the linked buffers and remove these FCS data. */
        buff1Len = rxFrame->rxBuffArray[--index].length;
        if (buff1Len > ENET_FCS_LEN)
        {
            rxFrame->rxBuffArray[index].length -= ENET_FCS_LEN;
        }
        else
        {
            rxFrame->rxBuffArray[index].length = 0;
            handle->rxBuffFree(base, rxFrame->rxBuffArray[index].buffer, handle->userData, channel);
            if (buff1Len < ENET_FCS_LEN)
            {
                rxFrame->rxBuffArray[--index].length -= (ENET_FCS_LEN - buff1Len);
            }
        }
        rxFrame->totLen -= ENET_FCS_LEN;
    }

    return result;
}

/*!
 * brief Setup a given Tx descriptor.
 *  This function is a low level functional API to setup or prepare
 *  a given Tx descriptor.
 *
 * param txDesc  The given Tx descriptor.
 * param buffer1  The first buffer address in the descriptor.
 * param bytes1  The bytes in the fist buffer.
 * param buffer2  The second buffer address in the descriptor.
 * param bytes2  The bytes in the second buffer.
 * param framelen  The length of the frame to be transmitted.
 * param intEnable Interrupt enable flag.
 * param tsEnable The timestamp enable.
 * param flag The flag of this Tx desciriptor, see "enet_desc_flag_t" .
 * param slotNum The slot num used for AV mode only.
 *
 * note This must be called after all the ENET initilization.
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
                            uint8_t slotNum)
{
    uint32_t control = ENET_TXDESCRIP_RD_BL1(bytes1) | ENET_TXDESCRIP_RD_BL2(bytes2);

    if ((flag == kENET_FirstFlagOnly) || (flag == kENET_FirstLastFlag))
    {
        if (tsEnable)
        {
            control |= ENET_TXDESCRIP_RD_TTSE_MASK;
        }
        else
        {
            control &= ~ENET_TXDESCRIP_RD_TTSE_MASK;
        }
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
    txDesc->tdes0 = (uint32_t)(uint32_t *)buffer1;
    txDesc->tdes1 = (uint32_t)(uint32_t *)buffer2;
    txDesc->tdes2 = control;

    control = ENET_TXDESCRIP_RD_SLOT(slotNum) | ENET_TXDESCRIP_RD_FL(framelen) | ENET_TXDESCRIP_RD_LDFD(flag) |
              ENET_TXDESCRIP_RD_OWN_MASK;

    txDesc->tdes3 = control;
}

/*!
 * brief Configure a given Tx descriptor.
 *  This function is a low level functional API to setup or prepare
 *  a given Tx descriptor.
 *
 * param txDesc  The given Tx descriptor.
 * param config The Tx descriptor configuration.
 *
 * note This must be called after all the ENET initilization.
 * And should be called when the ENET receive/transmit is required.
 * Transmit buffers are 'zero-copy' buffers, so the buffer must remain in
 * memory until the packet has been fully transmitted. The buffers
 * should be free or requeued in the transmit interrupt irq handler.
 */
static void ENET_ConfigTxDescriptor(enet_tx_bd_struct_t *txDesc, enet_tx_bd_config_struct_t *config)
{
    uint32_t control                = ENET_TXDESCRIP_RD_BL1(config->bytes1) | ENET_TXDESCRIP_RD_BL2(config->bytes2);
    enet_tx_offload_t txOffloadMode = kENET_TxOffloadDisable;

    if ((config->flag == kENET_FirstFlagOnly) || (config->flag == kENET_FirstLastFlag))
    {
        if (config->tsEnable)
        {
            control |= ENET_TXDESCRIP_RD_TTSE_MASK;
        }
        else
        {
            control &= ~ENET_TXDESCRIP_RD_TTSE_MASK;
        }
        txOffloadMode = config->txOffloadOps;
    }

    if (config->intEnable)
    {
        control |= ENET_TXDESCRIP_RD_IOC_MASK;
    }
    else
    {
        control &= ~ENET_TXDESCRIP_RD_IOC_MASK;
    }

    /* Preare the descriptor for transmit. */
    txDesc->tdes0 = (uint32_t)(uint32_t *)config->buffer1;
    txDesc->tdes1 = (uint32_t)(uint32_t *)config->buffer2;
    txDesc->tdes2 = control;

    control = ENET_TXDESCRIP_RD_SLOT(config->slotNum) | ENET_TXDESCRIP_RD_FL(config->framelen) |
              ENET_TXDESCRIP_RD_CIC(txOffloadMode) | ENET_TXDESCRIP_RD_LDFD(config->flag) | ENET_TXDESCRIP_RD_OWN_MASK;

    txDesc->tdes3 = control;
}

/*!
 * brief Reclaim Tx descriptors.
 *  This function is used to update the Tx descriptor status and
 *  store the Tx timestamp when the 1588 feature is enabled.
 *  This is called by the transmit interupt IRQ handler after the
 *  complete of a frame transmission.
 *
 * param base    ENET peripheral base address.
 * param handle The ENET handler pointer. This is the same handler pointer used in the ENET_Init.
 * param channel  The Tx DMA channnel.
 *
 */
void ENET_ReclaimTxDescriptor(ENET_Type *base, enet_handle_t *handle, uint8_t channel)
{
    enet_tx_bd_ring_t *txBdRing       = &handle->txBdRing[channel];
    enet_tx_bd_struct_t *txDesc       = txBdRing->txBdBase + txBdRing->txConsumIdx;
    enet_tx_dirty_ring_t *txDirtyRing = (enet_tx_dirty_ring_t *)&handle->txDirtyRing[channel];
    enet_tx_reclaim_info_t *txDirty   = NULL;

    /* Need to update the first index for transmit buffer free. */
    while ((txBdRing->txDescUsed > 0U) && ((txDesc->tdes3 & ENET_TXDESCRIP_RD_OWN_MASK) == 0U))
    {
        if ((txDesc->tdes3 & ENET_TXDESCRIP_RD_LD_MASK) != 0U)
        {
            txDirty                  = &txDirtyRing->txDirtyBase[txDirtyRing->txConsumIdx];
            txDirtyRing->txConsumIdx = ENET_IncreaseIndex(txDirtyRing->txConsumIdx, txDirtyRing->txRingLen);
            txDirty->isTsAvail       = false;

#ifdef ENET_PTP1588FEATURE_REQUIRED
            uint32_t nanosecond = 0;

            if ((txDesc->tdes3 & ENET_TXDESCRIP_WB_TTSS_MASK) != 0U)
            {
                /* Get transmit time stamp second. */
                nanosecond = txDesc->tdes0;
                if ((base->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_MASK) == 0U)
                {
                    /* Binary rollover. */
                    txDirty->timeStamp.nanosecond = ENET_BINARY_ROLLOVER_SCALE(nanosecond);
                }
                else
                {
                    txDirty->timeStamp.nanosecond = nanosecond;
                }
                txDirty->timeStamp.second = txDesc->tdes1;
                txDirty->isTsAvail        = true;
            }
#endif /* ENET_PTP1588FEATURE_REQUIRED */
            /* For Tx buffer free or requeue for each descriptor.
             * The Tx interrupt callback should free/requeue the Tx buffer. */
            if (handle->callback != NULL)
            {
                handle->callback(base, handle, kENET_TxIntEvent, channel, txDirty, handle->userData);
            }
        }

        /* Update the used Tx descriptor count. */
        txBdRing->txDescUsed--;

        /* Update the txConsumIdx/txDesc. */
        txBdRing->txConsumIdx = ENET_IncreaseIndex(txBdRing->txConsumIdx, txBdRing->txRingLen);
        txDesc                = txBdRing->txBdBase + txBdRing->txConsumIdx;
    }
}

/*!
 * brief Transmits an ENET frame.
 * note The CRC is automatically appended to the data. Input the data
 * to send without the CRC. This API uses input buffer for Tx, application
 * should reclaim the buffer after Tx is over.
 *
 * param base  ENET peripheral base address.
 * param handle The ENET handler pointer. This is the same handler pointer used in the ENET_Init.
 * param txFrame The Tx frame structure.
 * param channel Channel to send the frame, same with queue index.
 * retval kStatus_Success  Send frame succeed.
 * retval kStatus_ENET_TxFrameBusy  Transmit buffer descriptor is busy under transmission.
 *        The transmit busy happens when the data send rate is over the MAC capacity.
 *        The waiting mechanism is recommended to be added after each call return with kStatus_ENET_TxFrameBusy.
 *        Also need to pay attention to reclaim Tx frame after Tx is over.
 * retval kStatus_ENET_TxFrameOverLen  Transmit frme length exceeds the 0x3FFF limit defined by the driver.
 */
status_t ENET_SendFrame(ENET_Type *base, enet_handle_t *handle, enet_tx_frame_struct_t *txFrame, uint8_t channel)
{
    assert(handle);
    assert(handle->txDirtyRing[channel].txDirtyBase != NULL);
    assert(txFrame);
    assert(txFrame->txBuffNum != 0U);
    assert(txFrame->txBuffArray != NULL);

    enet_tx_bd_ring_t *txBdRing       = (enet_tx_bd_ring_t *)&handle->txBdRing[channel];
    enet_tx_dirty_ring_t *txDirtyRing = (enet_tx_dirty_ring_t *)&handle->txDirtyRing[channel];
    enet_tx_reclaim_info_t *txDirty   = &txDirtyRing->txDirtyBase[txDirtyRing->txGenIdx];
    enet_buffer_struct_t *txBuff      = txFrame->txBuffArray;
    uint32_t frameLen                 = 0;
    uint32_t index                    = 0;
    enet_tx_bd_struct_t *txDesc;
    enet_desc_flag_t descFlag;
    uint32_t leftBuffNum;

    /* Calculate total frame length and the Tx buffer number if it's scattered. */
    for (index = 0; index < txFrame->txBuffNum; index++)
    {
        frameLen += txBuff[index].length;
    }

    /* Here use maximum length of single buffer in hardware as transmit length limitation, cause it's long enough.
     * And it simplifies the check of buffer length. There's no need to check each buffer length. */
    if (frameLen > ENET_FRAME_TX_LEN_LIMITATION)
    {
        return kStatus_ENET_TxFrameOverLen;
    }

    /* Check Tx FIFO whether can store enough frame data. */
    if (0U != handle->txLenLimitation[channel])
    {
        if (frameLen > handle->txLenLimitation[channel])
        {
            return kStatus_ENET_TxFrameOverLen;
        }
    }

    /* Check whether the available BD number is enough for Tx data buffer. */
    if (txFrame->txBuffNum > (((uint32_t)txBdRing->txRingLen - (uint32_t)txBdRing->txDescUsed) * 2U))
    {
        return kStatus_ENET_TxFrameBusy;
    }

    /* Update the context in Tx dirty ring for reclaim */
    txDirty->context      = txFrame->context;
    txDirtyRing->txGenIdx = ENET_IncreaseIndex(txDirtyRing->txGenIdx, txDirtyRing->txRingLen);

    index       = 0;
    leftBuffNum = txFrame->txBuffNum;
    do
    {
        txDesc = &txBdRing->txBdBase[txBdRing->txGenIdx];

        /* Get the right flag for current BD */
        if (leftBuffNum == txFrame->txBuffNum)
        {
            descFlag = (leftBuffNum > 2U) ? kENET_FirstFlagOnly : kENET_FirstLastFlag;
        }
        else
        {
            descFlag = (leftBuffNum > 2U) ? kENET_MiddleFlag : kENET_LastFlagOnly;
        }

        enet_tx_bd_config_struct_t txDescConfig = {0};

        txDescConfig.framelen     = frameLen;
        txDescConfig.intEnable    = (bool)txFrame->txConfig.intEnable;
        txDescConfig.tsEnable     = (bool)txFrame->txConfig.tsEnable;
        txDescConfig.txOffloadOps = txFrame->txConfig.txOffloadOps;
        txDescConfig.flag         = descFlag;
        txDescConfig.slotNum      = txFrame->txConfig.slotNum;

        /* Fill the descriptor. */
        txDescConfig.buffer1 = txBuff[index].buffer;
        txDescConfig.bytes1  = txBuff[index].length;
        if (leftBuffNum < 2U)
        {
            txDescConfig.buffer2 = NULL;
            txDescConfig.bytes2  = 0;
            leftBuffNum--;
        }
        else
        {
            txDescConfig.buffer2 = txBuff[index + 1U].buffer;
            txDescConfig.bytes2  = txBuff[index + 1U].length;
            index += 2U;
            leftBuffNum -= 2U;
        }
        ENET_ConfigTxDescriptor(txDesc, &txDescConfig);

        /* Increase the index. */
        txBdRing->txGenIdx = ENET_IncreaseIndex(txBdRing->txGenIdx, txBdRing->txRingLen);

        /* Disable interrupt first and then enable interrupt to avoid the race condition. */
        (void)DisableIRQ(s_enetIrqId[ENET_GetInstance(base)]);
        txBdRing->txDescUsed++;
        (void)EnableIRQ(s_enetIrqId[ENET_GetInstance(base)]);
    } while (leftBuffNum != 0U);

    /* Update the transmit tail address. */
    txDesc = (txBdRing->txGenIdx == 0U) ? (&txBdRing->txBdBase[txBdRing->txRingLen]) :
                                          (&txBdRing->txBdBase[txBdRing->txGenIdx]);
    base->DMA_CH[channel].DMA_CHX_TXDESC_TAIL_PTR = (uint32_t)txDesc & ~ENET_ADDR_ALIGNMENT;

    return kStatus_Success;
}

#ifdef ENET_PTP1588FEATURE_REQUIRED
/*!
 * brief Gets the current ENET time from the PTP 1588 timer.
 *       Interrupts are not disabled.
 *
 * param base  ENET peripheral base address.
 * param second The PTP 1588 system timer second.
 * param nanosecond The PTP 1588 system timer nanosecond.
 */
void ENET_Ptp1588GetTimerNoIrqDisable(ENET_Type *base, uint64_t *second, uint32_t *nanosecond)
{
    assert(second);
    assert(nanosecond);

    /* Get the current PTP time. */
    *second     = base->MAC_SYSTEM_TIME_SECONDS;
    *nanosecond = base->MAC_SYSTEM_TIME_NANOSECONDS & ENET_MAC_SYSTEM_TIME_NANOSECONDS_TSSS_MASK;
    if (!((base->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_MASK) != 0U))
    {
        /* Binary rollover, the unit of the increment is ~ 0.466 ns. */
        *nanosecond = ENET_BINARY_ROLLOVER_SCALE(*nanosecond);
    }
}

/*!
 * brief Gets the current ENET time from the PTP 1588 timer.
 *
 * param base  ENET peripheral base address.
 * param second The PTP 1588 system timer second.
 * param nanosecond The PTP 1588 system timer nanosecond.
 * For the unit of the nanosecond is 1ns. So the nanosecond is the real nanosecond.
 */
void ENET_Ptp1588GetTimer(ENET_Type *base, uint64_t *second, uint32_t *nanosecond)
{
    assert(second);
    assert(nanosecond);

    uint32_t primask;

    /* Disables the interrupt. */
    primask = DisableGlobalIRQ();

    ENET_Ptp1588GetTimerNoIrqDisable(base, second, nanosecond);

    /* Enables the interrupt. */
    EnableGlobalIRQ(primask);
}

/*!
 * brief Correct the ENET PTP 1588 timer in coarse method.
 *
 * param base  ENET peripheral base address.
 * param operation The system time operation, refer to "enet_systime_op_t"
 * param second The correction second.
 * param nanosecond The correction nanosecond.
 */
void ENET_Ptp1588CorrectTimerInCoarse(ENET_Type *base,
                                      enet_systime_op_t operation,
                                      uint32_t second,
                                      uint32_t nanosecond)
{
    uint32_t corrSecond = second;
    uint32_t corrNanosecond;

    /* Set the system timer. */
    if ((base->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_MASK) != 0U)
    {
        if (operation == kENET_SystimeSubtract)
        {
            /* Set with the complement of the sub-second. */
            corrSecond     = ENET_MAC_SYSTEM_TIME_SECONDS_UPDATE_TSS_MASK - (second - 1U);
            corrNanosecond = ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB_MASK |
                             ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS(ENET_NANOSECS_ONESECOND - nanosecond);
        }
        else
        {
            corrNanosecond = ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS(nanosecond);
        }
    }
    else
    {
        nanosecond = ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_MASK / ENET_NANOSECS_ONESECOND * nanosecond;
        if (operation == kENET_SystimeSubtract)
        {
            /* Set with the complement of the sub-second. */
            corrSecond     = ENET_MAC_SYSTEM_TIME_SECONDS_UPDATE_TSS_MASK - (second - 1U);
            corrNanosecond = ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB_MASK |
                             ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS(
                                 ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_MASK + 1U - nanosecond);
        }
        else
        {
            corrNanosecond = ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS(nanosecond);
        }
    }

    base->MAC_SYSTEM_TIME_SECONDS_UPDATE     = corrSecond;
    base->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE = corrNanosecond;

    /* Update the timer. */
    base->MAC_TIMESTAMP_CONTROL |= ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK;
    while ((base->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK) != 0U)
    {
    }
}
#endif /* ENET_PTP1588FEATURE_REQUIRED */

/*!
 * brief The ENET IRQ handler.
 *
 * param base  ENET peripheral base address.
 * param handle The ENET handler pointer.
 */
void ENET_IRQHandler(ENET_Type *base, enet_handle_t *handle)
{
    /* Check for the interrupt source type. */
    /* DMA CHANNEL 0. */
    if ((base->DMA_INTERRUPT_STATUS & ENET_DMA_INTERRUPT_STATUS_DC0IS_MASK) != 0U)
    {
        uint32_t flag = base->DMA_CH[0].DMA_CHX_STAT;
        if ((flag & ENET_DMA_CH_DMA_CHX_STAT_RI_MASK) != 0U)
        {
            base->DMA_CH[0].DMA_CHX_STAT = ENET_DMA_CH_DMA_CHX_STAT_RI_MASK | ENET_DMA_CH_DMA_CHX_STAT_NIS_MASK;
            if (handle->callback != NULL)
            {
                handle->callback(base, handle, kENET_RxIntEvent, 0, NULL, handle->userData);
            }
        }
        if ((flag & ENET_DMA_CH_DMA_CHX_STAT_TI_MASK) != 0U)
        {
            base->DMA_CH[0].DMA_CHX_STAT = ENET_DMA_CH_DMA_CHX_STAT_TI_MASK | ENET_DMA_CH_DMA_CHX_STAT_NIS_MASK;
            ENET_ReclaimTxDescriptor(base, handle, 0);
        }
    }

    /* DMA CHANNEL 1. */
    if ((base->DMA_INTERRUPT_STATUS & ENET_DMA_INTERRUPT_STATUS_DC1IS_MASK) != 0U)
    {
        uint32_t flag = base->DMA_CH[1].DMA_CHX_STAT;
        if ((flag & ENET_DMA_CH_DMA_CHX_STAT_RI_MASK) != 0U)
        {
            base->DMA_CH[1].DMA_CHX_STAT = ENET_DMA_CH_DMA_CHX_STAT_RI_MASK | ENET_DMA_CH_DMA_CHX_STAT_NIS_MASK;
            if (handle->callback != NULL)
            {
                handle->callback(base, handle, kENET_RxIntEvent, 1, NULL, handle->userData);
            }
        }
        if ((flag & ENET_DMA_CH_DMA_CHX_STAT_TI_MASK) != 0U)
        {
            base->DMA_CH[1].DMA_CHX_STAT = ENET_DMA_CH_DMA_CHX_STAT_TI_MASK | ENET_DMA_CH_DMA_CHX_STAT_NIS_MASK;
            ENET_ReclaimTxDescriptor(base, handle, 1);
        }
    }

#ifdef ENET_PTP1588FEATURE_REQUIRED
    /* MAC TIMESTAMP. */
    if ((base->DMA_INTERRUPT_STATUS & ENET_DMA_INTERRUPT_STATUS_MACIS_MASK) != 0U)
    {
        if ((base->MAC_INTERRUPT_STATUS & ENET_MAC_INTERRUPT_STATUS_TSIS_MASK) != 0U)
        {
            if (handle->callback != NULL)
            {
                handle->callback(base, handle, kENET_TimeStampIntEvent, 0, NULL, handle->userData);
            }
        }
    }
#endif /* ENET_PTP1588FEATURE_REQUIRED */
    SDK_ISR_EXIT_BARRIER;
}

void ETHERNET_DriverIRQHandler(void);
void ETHERNET_DriverIRQHandler(void)
{
    s_enetIsr(ENET0, s_ENETHandle[0]);
    SDK_ISR_EXIT_BARRIER;
}
