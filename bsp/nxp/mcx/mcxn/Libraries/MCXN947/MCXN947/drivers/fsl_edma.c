/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_edma.h"
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
#include "fsl_memory.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.edma"
#endif
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Map transfer width.
 *
 * @param width transfer width.
 */
static edma_transfer_size_t EDMA_TransferWidthMapping(uint32_t width);
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Array to map EDMA instance number to base pointer. */
static EDMA_Type *const s_edmaBases[] = EDMA_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Array to map EDMA instance number to clock name. */
static const clock_ip_name_t s_edmaClockName[] = EDMA_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Array to map EDMA instance number to IRQ number. */
static const IRQn_Type s_edmaIRQNumber[][FSL_FEATURE_EDMA_MODULE_MAX_CHANNEL] = EDMA_CHN_IRQS;

/*! @brief Pointers to transfer handle for each EDMA channel. */
static edma_handle_t *s_EDMAHandle[FSL_FEATURE_EDMA_MODULE_COUNT][FSL_FEATURE_EDMA_MODULE_MAX_CHANNEL];
/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t EDMA_GetInstance(EDMA_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_edmaBases); instance++)
    {
        if (s_edmaBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_edmaBases));

    return instance;
}

/*!
 * brief Push content of TCD structure into hardware TCD register.
 *
 * param base EDMA peripheral base address.
 * param channel EDMA channel number.
 * param tcd Point to TCD structure.
 */
void EDMA_InstallTCD(EDMA_Type *base, uint32_t channel, edma_tcd_t *tcd)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));
    assert(tcd != NULL);
    assert(((uint32_t)tcd & 0x1FU) == 0U);

    edma_tcd_t *tcdRegs = EDMA_TCD_BASE(base, channel);

#if FSL_EDMA_SOC_IP_DMA3 || FSL_EDMA_SOC_IP_DMA4
    EDMA_CHANNEL_BASE(base, channel)->CH_CSR |= DMA_CH_CSR_DONE_MASK;
#endif

    /* Push tcd into hardware TCD register */
    tcdRegs->SADDR     = tcd->SADDR;
    tcdRegs->SOFF      = tcd->SOFF;
    tcdRegs->ATTR      = tcd->ATTR;
    tcdRegs->NBYTES    = tcd->NBYTES;
    tcdRegs->SLAST     = (int32_t)tcd->SLAST;
    tcdRegs->DADDR     = tcd->DADDR;
    tcdRegs->DOFF      = tcd->DOFF;
    tcdRegs->CITER     = tcd->CITER;
    tcdRegs->DLAST_SGA = (int32_t)tcd->DLAST_SGA;
    /* Clear DONE bit first, otherwise ESG cannot be set */
    tcdRegs->CSR   = 0;
    tcdRegs->CSR   = tcd->CSR;
    tcdRegs->BITER = tcd->BITER;
}

/*!
 * brief Initializes the eDMA peripheral.
 *
 * This function ungates the eDMA clock and configures the eDMA peripheral according
 * to the configuration structure.
 *
 * param base eDMA peripheral base address.
 * param config A pointer to the configuration structure, see "edma_config_t".
 * note This function enables the minor loop map feature.
 */
void EDMA_Init(EDMA_Type *base, const edma_config_t *config)
{
    assert(config != NULL);

    uint32_t tmpreg, i = 0U;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate EDMA peripheral clock */
    CLOCK_EnableClock(s_edmaClockName[EDMA_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if FSL_EDMA_SOC_IP_EDMA
    /* clear all the enabled request, status to make sure EDMA status is in normal condition */
    EDMA_BASE(base)->ERQ = 0U;
    EDMA_BASE(base)->INT = 0xFFFFFFFFU;
    EDMA_BASE(base)->ERR = 0xFFFFFFFFU;
    /* Configure EDMA peripheral according to the configuration structure. */
    tmpreg = EDMA_BASE(base)->CR;
    tmpreg &= ~(DMA_CR_ERCA_MASK | DMA_CR_HOE_MASK | DMA_CR_CLM_MASK | DMA_CR_EDBG_MASK);
    tmpreg |= (DMA_CR_ERCA(config->enableRoundRobinArbitration) | DMA_CR_HOE(config->enableHaltOnError) |
               DMA_CR_CLM(config->enableContinuousLinkMode) | DMA_CR_EDBG(config->enableDebugMode) | DMA_CR_EMLM(1U));
    EDMA_BASE(base)->CR = tmpreg;
#else
    tmpreg = EDMA_MP_BASE(base)->MP_CSR;
#if defined FSL_FEATURE_EDMA_HAS_GLOBAL_MASTER_ID_REPLICATION && FSL_FEATURE_EDMA_HAS_GLOBAL_MASTER_ID_REPLICATION
    tmpreg = (tmpreg & ~(DMA_MP_CSR_HAE_MASK | DMA_MP_CSR_ERCA_MASK | DMA_MP_CSR_EDBG_MASK | DMA_MP_CSR_GCLC_MASK |
                         DMA_MP_CSR_GMRC_MASK | DMA_MP_CSR_HALT_MASK)) |
             DMA_MP_CSR_GMRC(config->enableMasterIdReplication) | DMA_MP_CSR_HAE(config->enableHaltOnError) |
             DMA_MP_CSR_ERCA(config->enableRoundRobinArbitration) | DMA_MP_CSR_EDBG(config->enableDebugMode) |
             DMA_MP_CSR_GCLC(config->enableGlobalChannelLink);
#else
    tmpreg = (tmpreg & ~(DMA_MP_CSR_HAE_MASK | DMA_MP_CSR_ERCA_MASK | DMA_MP_CSR_EDBG_MASK | DMA_MP_CSR_GCLC_MASK |
                         DMA_MP_CSR_HALT_MASK)) |
             DMA_MP_CSR_HAE(config->enableHaltOnError) | DMA_MP_CSR_ERCA(config->enableRoundRobinArbitration) |
             DMA_MP_CSR_EDBG(config->enableDebugMode) | DMA_MP_CSR_GCLC(config->enableGlobalChannelLink);
#endif
    EDMA_MP_BASE(base)->MP_CSR = tmpreg;
    /* channel transfer configuration */
    for (i = 0U; i < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base); i++)
    {
        if (config->channelConfig[i] != NULL)
        {
            EDMA_InitChannel(base, i, config->channelConfig[i]);
        }
    }
#endif
}

/*!
 * brief Deinitializes the eDMA peripheral.
 *
 * This function gates the eDMA clock.
 *
 * param base eDMA peripheral base address.
 */
void EDMA_Deinit(EDMA_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate EDMA peripheral clock */
    CLOCK_DisableClock(s_edmaClockName[EDMA_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG && FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG
/*!
 * brief EDMA Channel initialization
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param channelConfig pointer to user's eDMA channel config structure, see edma_channel_config_t for detail.
 */
void EDMA_InitChannel(EDMA_Type *base, uint32_t channel, edma_channel_config_t *channelConfig)
{
    assert(channelConfig != NULL);

    EDMA_SetChannelPreemptionConfig(base, channel, &channelConfig->channelPreemptionConfig);

#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_SWAP_SIZE && FSL_FEATURE_EDMA_HAS_CHANNEL_SWAP_SIZE
    EDMA_SetChannelSwapSize(base, channel, channelConfig->channelSwapSize);
#endif

#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_MEMRORY_ATTRIBUTE && FSL_FEATURE_EDMA_HAS_CHANNEL_MEMRORY_ATTRIBUTE
    EDMA_SetChannelMemoryAttribute(base, channel, channelConfig->channelWriteMemoryAttribute,
                                   channelConfig->channelReadMemoryAttribute);
#endif
#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_SIGN_EXTENSION && FSL_FEATURE_EDMA_HAS_CHANNEL_SIGN_EXTENSION
    EDMA_SetChannelSignExtension(base, channel, channelConfig->channelDataSignExtensionBitPosition);
#endif
#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_ACCESS_TYPE && FSL_FEATURE_EDMA_HAS_CHANNEL_ACCESS_TYPE
    EDMA_SetChannelAccessType(base, channel, channelConfig->channelAccessType);
#endif
    if (kDmaRequestDisabled != channelConfig->channelRequestSource)
    {
        /* dma request source */
        EDMA_SetChannelMux(base, channel, channelConfig->channelRequestSource);
    }
    /* master ID replication */
    EDMA_EnableChannelMasterIDReplication(base, channel, channelConfig->enableMasterIDReplication);
    /* dma transfer security level */
    EDMA_SetChannelSecurityLevel(base, channel, channelConfig->securityLevel);
    /* dma transfer protection level */
    EDMA_SetChannelProtectionLevel(base, channel, channelConfig->protectionLevel);
}
#endif

/*!
 * brief Gets the eDMA default configuration structure.
 *
 * This function sets the configuration structure to default values.
 * The default configuration is set to the following values.
 * code
 *   config.enableContinuousLinkMode = false;
 *   config.enableHaltOnError = true;
 *   config.enableRoundRobinArbitration = false;
 *   config.enableDebugMode = false;
 * endcode
 *
 * param config A pointer to the eDMA configuration structure.
 */
void EDMA_GetDefaultConfig(edma_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enableRoundRobinArbitration = false;

    config->enableHaltOnError = true;

#if defined FSL_FEATURE_EDMA_HAS_CONTINUOUS_LINK_MODE && FSL_FEATURE_EDMA_HAS_CONTINUOUS_LINK_MODE
    config->enableContinuousLinkMode = false;
#endif

#if defined FSL_FEATURE_EDMA_HAS_GLOBAL_MASTER_ID_REPLICATION && FSL_FEATURE_EDMA_HAS_GLOBAL_MASTER_ID_REPLICATION
    config->enableMasterIdReplication = false;
#endif

    config->enableDebugMode = false;

    config->enableGlobalChannelLink = true;
}

/*!
 * brief Sets all TCD registers to default values.
 *
 * This function sets TCD registers for this channel to default values.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * note This function must not be called while the channel transfer is ongoing
 *       or it causes unpredictable results.
 * note This function enables the auto stop request feature.
 */
void EDMA_ResetChannel(EDMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));

    /* reset channel CSR  */
    EDMA_ClearChannelStatusFlags(base, channel, (uint32_t)kEDMA_DoneFlag | (uint32_t)kEDMA_ErrorFlag);
    /* reset channel TCD  */
    EDMA_TcdReset(EDMA_TCD_BASE(base, channel));
}

/*!
 * brief Configures the eDMA transfer attribute.
 *
 * This function configures the transfer attribute, including source address, destination address,
 * transfer size, address offset, and so on. It also configures the scatter gather feature if the
 * user supplies the TCD address.
 * Example:
 * code
 *  edma_transfer_t config;
 *  edma_tcd_t tcd;
 *  config.srcAddr = ..;
 *  config.destAddr = ..;
 *  ...
 *  EDMA_SetTransferConfig(DMA0, channel, &config, &stcd);
 * endcode
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param config Pointer to eDMA transfer configuration structure.
 * param nextTcd Point to TCD structure. It can be NULL if users
 *                do not want to enable scatter/gather feature.
 * note If nextTcd is not NULL, it means scatter gather feature is enabled
 *       and DREQ bit is cleared in the previous transfer configuration, which
 *       is set in the eDMA_ResetChannel.
 */
void EDMA_SetTransferConfig(EDMA_Type *base,
                            uint32_t channel,
                            const edma_transfer_config_t *config,
                            edma_tcd_t *nextTcd)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));
    assert(config != NULL);
    assert(((uint32_t)nextTcd & 0x1FU) == 0U);

/* If there is address offset, convert the address */
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    nextTcd = (edma_tcd_t *)(MEMORY_ConvertMemoryMapAddress((uint32_t)nextTcd, kMEMORY_Local2DMA));
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */

    EDMA_TcdSetTransferConfig(EDMA_TCD_BASE(base, channel), config, nextTcd);
}

/*!
 * brief Configures the eDMA minor offset feature.
 *
 * The minor offset means that the signed-extended value is added to the source address or destination
 * address after each minor loop.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param config A pointer to the minor offset configuration structure.
 */
void EDMA_SetMinorOffsetConfig(EDMA_Type *base, uint32_t channel, const edma_minor_offset_config_t *config)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));
    assert(config != NULL);

    uint32_t tmpreg;

    tmpreg = EDMA_TCD_BASE(base, channel)->NBYTES;
    tmpreg &= ~(DMA_NBYTES_MLOFFYES_SMLOE_MASK | DMA_NBYTES_MLOFFYES_DMLOE_MASK | DMA_NBYTES_MLOFFYES_MLOFF_MASK);
    tmpreg |=
        (DMA_NBYTES_MLOFFYES_SMLOE(config->enableSrcMinorOffset) |
         DMA_NBYTES_MLOFFYES_DMLOE(config->enableDestMinorOffset) | DMA_NBYTES_MLOFFYES_MLOFF(config->minorOffset));
    EDMA_TCD_BASE(base, channel)->NBYTES = tmpreg;
}

/*!
 * brief Configures the eDMA channel TCD major offset feature.
 *
 * Adjustment value added to the source address at the completion of the major iteration count
 *
 * param base eDMA peripheral base address.
 * param channel edma channel number.
 * param sourceOffset source address offset.
 * param destOffset destination address offset.
 */
void EDMA_SetMajorOffsetConfig(EDMA_Type *base, uint32_t channel, int32_t sourceOffset, int32_t destOffset)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));

    EDMA_TCD_BASE(base, channel)->SLAST     = sourceOffset;
    EDMA_TCD_BASE(base, channel)->DLAST_SGA = destOffset;
}

/*!
 * brief Configures the eDMA channel preemption feature.
 *
 * This function configures the channel preemption attribute and the priority of the channel.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number
 * param config A pointer to the channel preemption configuration structure.
 */
void EDMA_SetChannelPreemptionConfig(EDMA_Type *base, uint32_t channel, const edma_channel_Preemption_config_t *config)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));
    assert(config != NULL);

    bool tmpEnablePreemptAbility   = config->enablePreemptAbility;
    bool tmpEnablchannelPreemption = config->enableChannelPreemption;
    uint8_t tmpChannelPriority     = config->channelPriority;

#if FSL_EDMA_SOC_IP_EDMA

    volatile uint8_t *tmpReg = &EDMA_BASE(base)->DCHPRI3;

    ((volatile uint8_t *)tmpReg)[DMA_DCHPRI_INDEX(channel)] =
        (DMA_DCHPRI0_DPA((true == tmpEnablePreemptAbility ? 0U : 1U)) |
         DMA_DCHPRI0_ECP((true == tmpEnablchannelPreemption ? 1U : 0U)) | DMA_DCHPRI0_CHPRI(tmpChannelPriority));
#else
    EDMA_CHANNEL_BASE(base, channel)->CH_PRI = DMA_CH_PRI_ECP(tmpEnablchannelPreemption) |
                                               DMA_CH_PRI_DPA(tmpEnablePreemptAbility) |
                                               DMA_CH_PRI_APL(tmpChannelPriority);
#endif
}

/*!
 * brief Sets the channel link for the eDMA transfer.
 *
 * This function configures either the minor link or the major link mode. The minor link means that the channel link is
 * triggered every time CITER decreases by 1. The major link means that the channel link is triggered when the CITER is
 * exhausted.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param type A channel link type, which can be one of the following:
 *   arg kEDMA_LinkNone
 *   arg kEDMA_MinorLink
 *   arg kEDMA_MajorLink
 * param linkedChannel The linked channel number.
 * note Users should ensure that DONE flag is cleared before calling this interface, or the configuration is invalid.
 */
void EDMA_SetChannelLink(EDMA_Type *base, uint32_t channel, edma_channel_link_type_t type, uint32_t linkedChannel)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));
    assert(linkedChannel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));

    EDMA_TcdSetChannelLink(EDMA_TCD_BASE(base, channel), type, linkedChannel);
}

#if defined FSL_FEATURE_EDMA_HAS_BANDWIDTH && FSL_FEATURE_EDMA_HAS_BANDWIDTH
/*!
 * brief Sets the bandwidth for the eDMA transfer.
 *
 * Because the eDMA processes the minor loop, it continuously generates read/write sequences
 * until the minor count is exhausted. The bandwidth forces the eDMA to stall after the completion of
 * each read/write access to control the bus request bandwidth seen by the crossbar switch.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param bandWidth A bandwidth setting, which can be one of the following:
 *     arg kEDMABandwidthStallNone
 *     arg kEDMABandwidthStall4Cycle
 *     arg kEDMABandwidthStall8Cycle
 */
void EDMA_SetBandWidth(EDMA_Type *base, uint32_t channel, edma_bandwidth_t bandWidth)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));

    EDMA_BASE(base)->TCD[channel].CSR =
        (uint16_t)((EDMA_BASE(base)->TCD[channel].CSR & (~DMA_CSR_BWC_MASK)) | DMA_CSR_BWC(bandWidth));
}
#endif

/*!
 * brief Sets the source modulo and the destination modulo for the eDMA transfer.
 *
 * This function defines a specific address range specified to be the value after (SADDR + SOFF)/(DADDR + DOFF)
 * calculation is performed or the original register value. It provides the ability to implement a circular data
 * queue easily.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param srcModulo A source modulo value.
 * param destModulo A destination modulo value.
 */
void EDMA_SetModulo(EDMA_Type *base, uint32_t channel, edma_modulo_t srcModulo, edma_modulo_t destModulo)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));

    uint16_t tmpreg = EDMA_TCD_BASE(base, channel)->ATTR & (~(uint16_t)(DMA_ATTR_SMOD_MASK | DMA_ATTR_DMOD_MASK));
    EDMA_TCD_BASE(base, channel)->ATTR = tmpreg | DMA_ATTR_DMOD(destModulo) | DMA_ATTR_SMOD(srcModulo);
}

/*!
 * brief Enables the interrupt source for the eDMA transfer.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param mask The mask of interrupt source to be set. Users need to use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_EnablchannelInterrupts(EDMA_Type *base, uint32_t channel, uint32_t mask)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));

    /* Enable error interrupt */
    if (0U != (mask & (uint32_t)kEDMA_ErrorInterruptEnable))
    {
#if FSL_EDMA_SOC_IP_EDMA
        EDMA_BASE(base)->EEI |= ((uint32_t)0x1U << channel);
#else
        EDMA_CHANNEL_BASE(base, channel)->CH_CSR |= DMA_CH_CSR_EEI_MASK;
#endif
    }

    /* Enable Major interrupt */
    if (0U != (mask & (uint32_t)kEDMA_MajorInterruptEnable))
    {
        EDMA_TCD_BASE(base, channel)->CSR |= DMA_CSR_INTMAJOR_MASK;
    }

    /* Enable Half major interrupt */
    if (0U != (mask & (uint32_t)kEDMA_HalfInterruptEnable))
    {
        EDMA_TCD_BASE(base, channel)->CSR |= DMA_CSR_INTHALF_MASK;
    }
}

/*!
 * brief Disables the interrupt source for the eDMA transfer.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param mask The mask of the interrupt source to be set. Use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_DisablchannelInterrupts(EDMA_Type *base, uint32_t channel, uint32_t mask)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));

    /* Disable error interrupt */
    if (0U != (mask & (uint32_t)kEDMA_ErrorInterruptEnable))
    {
#if FSL_EDMA_SOC_IP_EDMA
        EDMA_BASE(base)->EEI &= (~((uint32_t)0x1U << channel));
#else
        EDMA_CHANNEL_BASE(base, channel)->CH_CSR &= ~DMA_CH_CSR_EEI_MASK;
#endif
    }

    /* Disable Major interrupt */
    if (0U != (mask & (uint32_t)kEDMA_MajorInterruptEnable))
    {
        EDMA_TCD_BASE(base, channel)->CSR &= ~(uint16_t)DMA_CSR_INTMAJOR_MASK;
    }

    /* Disable Half major interrupt */
    if (0U != (mask & (uint32_t)kEDMA_HalfInterruptEnable))
    {
        EDMA_TCD_BASE(base, channel)->CSR &= ~(uint16_t)DMA_CSR_INTHALF_MASK;
    }
}

/*!
 * brief Sets all fields to default values for the TCD structure.
 *
 * This function sets all fields for this TCD structure to default value.
 *
 * param tcd Pointer to the TCD structure.
 * note This function enables the auto stop request feature.
 */
void EDMA_TcdReset(edma_tcd_t *tcd)
{
    assert(tcd != NULL);
    assert(((uint32_t)tcd & 0x1FU) == 0U);

    /* Reset channel TCD */
    tcd->SADDR     = 0U;
    tcd->SOFF      = 0U;
    tcd->ATTR      = 0U;
    tcd->NBYTES    = 0U;
    tcd->SLAST     = 0U;
    tcd->DADDR     = 0U;
    tcd->DOFF      = 0U;
    tcd->CITER     = 0U;
    tcd->DLAST_SGA = 0U;
    /* Enable auto disable request feature */
    tcd->CSR   = DMA_CSR_DREQ(true);
    tcd->BITER = 0U;
}

/*!
 * brief Configures the eDMA TCD transfer attribute.
 *
 * The TCD is a transfer control descriptor. The content of the TCD is the same as the hardware TCD registers.
 * The TCD is used in the scatter-gather mode.
 * This function configures the TCD transfer attribute, including source address, destination address,
 * transfer size, address offset, and so on. It also configures the scatter gather feature if the
 * user supplies the next TCD address.
 * Example:
 * code
 *   edma_transfer_t config = {
 *   ...
 *   }
 *   edma_tcd_t tcd __aligned(32);
 *   edma_tcd_t nextTcd __aligned(32);
 *   EDMA_TcdSetTransferConfig(&tcd, &config, &nextTcd);
 * endcode
 *
 * param tcd Pointer to the TCD structure.
 * param config Pointer to eDMA transfer configuration structure.
 * param nextTcd Pointer to the next TCD structure. It can be NULL if users
 *                do not want to enable scatter/gather feature.
 * note TCD address should be 32 bytes aligned or it causes an eDMA error.
 * note If the nextTcd is not NULL, the scatter gather feature is enabled
 *       and DREQ bit is cleared in the previous transfer configuration, which
 *       is set in the EDMA_TcdReset.
 */
void EDMA_TcdSetTransferConfig(edma_tcd_t *tcd, const edma_transfer_config_t *config, edma_tcd_t *nextTcd)
{
    assert(tcd != NULL);
    assert(((uint32_t)tcd & 0x1FU) == 0U);
    assert(config != NULL);

    EDMA_ConfigChannelSoftwareTCD(tcd, config);

    if (nextTcd != NULL)
    {
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        tcd->DLAST_SGA = MEMORY_ConvertMemoryMapAddress((uint32_t)nextTcd, kMEMORY_Local2DMA);
#else
        tcd->DLAST_SGA = (uint32_t)nextTcd;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
        /*
            Before call EDMA_TcdSetTransferConfig or EDMA_SetTransferConfig,
            user must call EDMA_TcdReset or EDMA_ResetChannel which will set
            DREQ, so must use "|" or "&" rather than "=".

            Clear the DREQ bit because scatter gather has been enabled, so the
            previous transfer is not the last transfer, and channel request should
            be enabled at the next transfer(the next TCD).
        */
        tcd->CSR = (tcd->CSR | (uint16_t)DMA_CSR_ESG_MASK) & ~(uint16_t)DMA_CSR_DREQ_MASK;
    }
}

/*!
 * brief Sets TCD fields according to the user's channel transfer configuration structure, see
 * edma4_channel_transfer_config_t.
 *
 * Application should be careful about the TCD pool buffer storage class,
 * - For the platform has cache, the software TCD should be put in non cache section
 * - The TCD pool buffer should have a consistent storage class.
 *
 * param tcd Pointer to the TCD structure.
 * param transfer channel transfer configuration pointer.
 *
 */
void EDMA_ConfigChannelSoftwareTCD(edma_tcd_t *tcd, const edma_transfer_config_t *transfer)
{
    assert(transfer != NULL);
    assert((transfer->minorLoopBytes % (1UL << ((uint32_t)transfer->srcTransferSize))) == 0U);
    assert((transfer->minorLoopBytes % (1UL << ((uint32_t)transfer->destTransferSize))) == 0U);
    assert(((uint32_t)transfer->srcOffset % (1UL << ((uint32_t)transfer->srcTransferSize))) == 0U);
    assert(((uint32_t)transfer->destOffset % (1UL << ((uint32_t)transfer->destTransferSize))) == 0U);
    assert((transfer->srcAddr % (1UL << ((uint32_t)transfer->srcTransferSize))) == 0U);
    assert((transfer->destAddr % (1UL << ((uint32_t)transfer->destTransferSize))) == 0U);
    assert((transfer->srcAddr % (1UL << ((uint32_t)transfer->srcAddrModulo))) == 0U);
    assert((transfer->destAddr % (1UL << ((uint32_t)transfer->dstAddrModulo))) == 0U);

    uint16_t tmpreg;

#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    tcd->SADDR = MEMORY_ConvertMemoryMapAddress(transfer->srcAddr, kMEMORY_Local2DMA);
    /* destination address */
    tcd->DADDR = MEMORY_ConvertMemoryMapAddress(transfer->destAddr, kMEMORY_Local2DMA);
#else
    tcd->SADDR = transfer->srcAddr;
    /* destination address */
    tcd->DADDR = transfer->destAddr;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
    /* Source data and destination data transfer size */
    tcd->ATTR = DMA_ATTR_SSIZE(transfer->srcTransferSize) | DMA_ATTR_DSIZE(transfer->destTransferSize);

    /* Source address signed offset */
    tcd->SOFF = (uint16_t)(transfer->srcOffset);
    /* Destination address signed offset */
    tcd->DOFF = (uint16_t)(transfer->destOffset);

    if (((transfer->enableSrcMinorLoopOffset) || (transfer->enableDstMinorLoopOffset)))
    {
        tcd->NBYTES = DMA_NBYTES_MLOFFYES_NBYTES(transfer->minorLoopBytes) |
                      DMA_NBYTES_MLOFFYES_MLOFF(transfer->minorLoopOffset) |
                      DMA_NBYTES_MLOFFYES_DMLOE(transfer->enableDstMinorLoopOffset) |
                      DMA_NBYTES_MLOFFYES_SMLOE(transfer->enableSrcMinorLoopOffset);
    }
    else
    {
        tcd->NBYTES = DMA_NBYTES_MLOFFNO_NBYTES(transfer->minorLoopBytes);
    }

    /* Current major iteration count */
    tcd->CITER = (uint16_t)(transfer->majorLoopCounts);
    /* Starting major iteration count */
    tcd->BITER = (uint16_t)(transfer->majorLoopCounts);
    /* reset CSR firstly */
    tcd->CSR = DMA_CSR_DREQ(true);
    /* Enable scatter/gather processing */
    if (transfer->linkTCD != NULL)
    {
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        tcd->DLAST_SGA = MEMORY_ConvertMemoryMapAddress((uint32_t)transfer->linkTCD, kMEMORY_Local2DMA);
#else
        tcd->DLAST_SGA = (uint32_t)((uint8_t *)transfer->linkTCD);
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
        tcd->CSR |= (uint16_t)DMA_CSR_ESG_MASK;
    }
    else
    {
        tcd->CSR &= ~(uint16_t)DMA_CSR_ESG_MASK;
        tcd->DLAST_SGA = (uint32_t)transfer->dstMajorLoopOffset;
    }

    /* configure interrupt/auto disable channel request */
    tcd->CSR |= (transfer->enabledInterruptMask & (~(uint16_t)kEDMA_ErrorInterruptEnable));

    /* Minor link config */
    if (transfer->enableChannelMinorLoopLink)
    {
        uint16_t tmpreg;

        /* Enable minor link */
        tcd->CITER |= DMA_CITER_ELINKYES_ELINK_MASK;
        tcd->BITER |= DMA_BITER_ELINKYES_ELINK_MASK;
        /* Set linked channel */
        tmpreg = tcd->CITER & (~(uint16_t)DMA_CITER_ELINKYES_LINKCH_MASK);
        tmpreg |= DMA_CITER_ELINKYES_LINKCH(transfer->minorLoopLinkChannel);
        tcd->CITER = tmpreg;
        tmpreg     = tcd->BITER & (~(uint16_t)DMA_BITER_ELINKYES_LINKCH_MASK);
        tmpreg |= DMA_BITER_ELINKYES_LINKCH(transfer->minorLoopLinkChannel);
        tcd->BITER = tmpreg;
    }
    /* Major link config */
    if (transfer->enableChannelMajorLoopLink)
    {
        uint16_t tmpreg;

        /* Enable major link */
        tcd->CSR |= DMA_CSR_MAJORELINK_MASK;
        /* Set major linked channel */
        tmpreg   = tcd->CSR & (~(uint16_t)DMA_CSR_MAJORLINKCH_MASK);
        tcd->CSR = tmpreg | DMA_CSR_MAJORLINKCH(transfer->majorLoopLinkChannel);
    }

    /* clear link relate field if no channel link enabled */
    if ((!transfer->enableChannelMajorLoopLink) && (!transfer->enableChannelMinorLoopLink))
    {
        tcd->CITER &= ~(uint16_t)DMA_CITER_ELINKYES_ELINK_MASK;
        tcd->BITER &= ~(uint16_t)DMA_BITER_ELINKYES_ELINK_MASK;
        tcd->CSR &= ~(uint16_t)DMA_CSR_MAJORELINK_MASK;
    }

    /* major loop offset */
    tcd->SLAST = (uint32_t)transfer->srcMajorLoopOffset;
    /* modulo feature */
    tmpreg    = tcd->ATTR & (~(uint16_t)(DMA_ATTR_SMOD_MASK | DMA_ATTR_DMOD_MASK));
    tcd->ATTR = tmpreg | DMA_ATTR_DMOD(transfer->dstAddrModulo) | DMA_ATTR_SMOD(transfer->srcAddrModulo);
}

/*!
 * brief Configures the eDMA TCD minor offset feature.
 *
 * A minor offset is a signed-extended value added to the source address or a destination
 * address after each minor loop.
 *
 * param tcd A point to the TCD structure.
 * param config A pointer to the minor offset configuration structure.
 */
void EDMA_TcdSetMinorOffsetConfig(edma_tcd_t *tcd, const edma_minor_offset_config_t *config)
{
    assert(tcd != NULL);
    assert(((uint32_t)tcd & 0x1FU) == 0U);

    uint32_t tmpreg;

    tmpreg = tcd->NBYTES &
             ~(DMA_NBYTES_MLOFFYES_SMLOE_MASK | DMA_NBYTES_MLOFFYES_DMLOE_MASK | DMA_NBYTES_MLOFFYES_MLOFF_MASK);
    tmpreg |=
        (DMA_NBYTES_MLOFFYES_SMLOE(config->enableSrcMinorOffset) |
         DMA_NBYTES_MLOFFYES_DMLOE(config->enableDestMinorOffset) | DMA_NBYTES_MLOFFYES_MLOFF(config->minorOffset));
    tcd->NBYTES = tmpreg;
}

/*!
 * brief Configures the eDMA TCD major offset feature.
 *
 * Adjustment value added to the source address at the completion of the major iteration count
 *
 * param tcd A point to the TCD structure.
 * param sourceOffset source address offset.
 * param destOffset destination address offset.
 */
void EDMA_TcdSetMajorOffsetConfig(edma_tcd_t *tcd, int32_t sourceOffset, int32_t destOffset)
{
    assert(tcd != NULL);
    assert(((uint32_t)tcd & 0x1FU) == 0U);

    tcd->SLAST     = (uint32_t)sourceOffset;
    tcd->DLAST_SGA = (uint32_t)destOffset;
}

/*!
 * brief Sets the channel link for the eDMA TCD.
 *
 * This function configures either a minor link or a major link. The minor link means the channel link is
 * triggered every time CITER decreases by 1. The major link means that the channel link  is triggered when the CITER is
 * exhausted.
 *
 * note Users should ensure that DONE flag is cleared before calling this interface, or the configuration is invalid.
 * param tcd Point to the TCD structure.
 * param type Channel link type, it can be one of:
 *   arg kEDMA_LinkNone
 *   arg kEDMA_MinorLink
 *   arg kEDMA_MajorLink
 * param linkedChannel The linked channel number.
 */
void EDMA_TcdSetChannelLink(edma_tcd_t *tcd, edma_channel_link_type_t type, uint32_t linkedChannel)
{
    assert(tcd != NULL);
    assert(((uint32_t)tcd & 0x1FU) == 0U);
    assert(linkedChannel < (uint32_t)FSL_FEATURE_EDMA_MODULE_MAX_CHANNEL);

    if (type == kEDMA_MinorLink) /* Minor link config */
    {
        uint16_t tmpreg;

        /* Enable minor link */
        tcd->CITER |= DMA_CITER_ELINKYES_ELINK_MASK;
        tcd->BITER |= DMA_BITER_ELINKYES_ELINK_MASK;
        /* Set linked channel */
        tmpreg = tcd->CITER & (~(uint16_t)DMA_CITER_ELINKYES_LINKCH_MASK);
        tmpreg |= DMA_CITER_ELINKYES_LINKCH(linkedChannel);
        tcd->CITER = tmpreg;
        tmpreg     = tcd->BITER & (~(uint16_t)DMA_BITER_ELINKYES_LINKCH_MASK);
        tmpreg |= DMA_BITER_ELINKYES_LINKCH(linkedChannel);
        tcd->BITER = tmpreg;
    }
    else if (type == kEDMA_MajorLink) /* Major link config */
    {
        uint16_t tmpreg;

        /* Enable major link */
        tcd->CSR |= DMA_CSR_MAJORELINK_MASK;
        /* Set major linked channel */
        tmpreg   = tcd->CSR & (~(uint16_t)DMA_CSR_MAJORLINKCH_MASK);
        tcd->CSR = tmpreg | DMA_CSR_MAJORLINKCH(linkedChannel);
    }
    else /* Link none */
    {
        tcd->CITER &= ~(uint16_t)DMA_CITER_ELINKYES_ELINK_MASK;
        tcd->BITER &= ~(uint16_t)DMA_BITER_ELINKYES_ELINK_MASK;
        tcd->CSR &= ~(uint16_t)DMA_CSR_MAJORELINK_MASK;
    }
}

/*!
 * brief Sets the source modulo and the destination modulo for the eDMA TCD.
 *
 * This function defines a specific address range specified to be the value after (SADDR + SOFF)/(DADDR + DOFF)
 * calculation is performed or the original register value. It provides the ability to implement a circular data
 * queue easily.
 *
 * param tcd A pointer to the TCD structure.
 * param srcModulo A source modulo value.
 * param destModulo A destination modulo value.
 */
void EDMA_TcdSetModulo(edma_tcd_t *tcd, edma_modulo_t srcModulo, edma_modulo_t destModulo)
{
    assert(tcd != NULL);
    assert(((uint32_t)tcd & 0x1FU) == 0U);

    uint16_t tmpreg;

    tmpreg    = tcd->ATTR & (~(uint16_t)(DMA_ATTR_SMOD_MASK | DMA_ATTR_DMOD_MASK));
    tcd->ATTR = tmpreg | DMA_ATTR_DMOD(destModulo) | DMA_ATTR_SMOD(srcModulo);
}

/*!
 * brief Enables the interrupt source for the eDMA TCD.
 *
 * param tcd Point to the TCD structure.
 * param mask The mask of interrupt source to be set. Users need to use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_TcdEnableInterrupts(edma_tcd_t *tcd, uint32_t mask)
{
    assert(tcd != NULL);

    /* Enable Major interrupt */
    if (0U != (mask & (uint32_t)kEDMA_MajorInterruptEnable))
    {
        tcd->CSR |= DMA_CSR_INTMAJOR_MASK;
    }

    /* Enable Half major interrupt */
    if (0U != (mask & (uint32_t)kEDMA_HalfInterruptEnable))
    {
        tcd->CSR |= DMA_CSR_INTHALF_MASK;
    }
}

/*!
 * brief Disables the interrupt source for the eDMA TCD.
 *
 * param tcd Point to the TCD structure.
 * param mask The mask of interrupt source to be set. Users need to use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_TcdDisableInterrupts(edma_tcd_t *tcd, uint32_t mask)
{
    assert(tcd != NULL);

    /* Disable Major interrupt */
    if (0U != (mask & (uint32_t)kEDMA_MajorInterruptEnable))
    {
        tcd->CSR &= ~(uint16_t)DMA_CSR_INTMAJOR_MASK;
    }

    /* Disable Half major interrupt */
    if (0U != (mask & (uint32_t)kEDMA_HalfInterruptEnable))
    {
        tcd->CSR &= ~(uint16_t)DMA_CSR_INTHALF_MASK;
    }
}

/*!
 * brief Gets the remaining major loop count from the eDMA current channel TCD.
 *
 * This function checks the TCD (Task Control Descriptor) status for a specified
 * eDMA channel and returns the number of major loop count that has not finished.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * return Major loop count which has not been transferred yet for the current TCD.
 * note 1. This function can only be used to get unfinished major loop count of transfer without
 *          the next TCD, or it might be inaccuracy.
 *       2. The unfinished/remaining transfer bytes cannot be obtained directly from registers while
 *          the channel is running.
 *          Because to calculate the remaining bytes, the initial NBYTES configured in DMA_TCDn_NBYTES_MLNO
 *          register is needed while the eDMA IP does not support getting it while a channel is active.
 *          In another word, the NBYTES value reading is always the actual (decrementing) NBYTES value the dma_engine
 *          is working with while a channel is running.
 *          Consequently, to get the remaining transfer bytes, a software-saved initial value of NBYTES (for example
 *          copied before enabling the channel) is needed. The formula to calculate it is shown below:
 *          RemainingBytes = RemainingMajorLoopCount * NBYTES(initially configured)
 */
uint32_t EDMA_GetRemainingMajorLoopCount(EDMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));

    uint32_t remainingCount = 0;

#if defined FSL_EDMA_SOC_IP_EDMA && FSL_EDMA_SOC_IP_EDMA
    if (0U != (DMA_CSR_DONE_MASK & EDMA_TCD_BASE(base, channel)->CSR))
#else
    if ((EDMA_CHANNEL_BASE(base, channel)->CH_CSR & DMA_CH_CSR_DONE_MASK) != 0U)
#endif
    {
        remainingCount = 0;
    }
    else
    {
        /* Calculate the unfinished bytes */
        if (0U != (EDMA_TCD_BASE(base, channel)->CITER & DMA_CITER_ELINKNO_ELINK_MASK))
        {
            remainingCount = (((uint32_t)EDMA_TCD_BASE(base, channel)->CITER & DMA_CITER_ELINKYES_CITER_MASK) >>
                              DMA_CITER_ELINKYES_CITER_SHIFT);
        }
        else
        {
            remainingCount = (((uint32_t)EDMA_TCD_BASE(base, channel)->CITER & DMA_CITER_ELINKNO_CITER_MASK) >>
                              DMA_CITER_ELINKNO_CITER_SHIFT);
        }
    }

    return remainingCount;
}

/*!
 * brief Enables the interrupt source for the eDMA transfer.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param mask The mask of interrupt source to be set. Users need to use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_EnableChannelInterrupts(EDMA_Type *base, uint32_t channel, uint32_t mask)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));

#if FSL_EDMA_SOC_IP_EDMA
    /* Enable error interrupt */
    if (0U != (mask & (uint32_t)kEDMA_ErrorInterruptEnable))
    {
        base->EEI |= ((uint32_t)0x1U << channel);
    }
#else
    /* Enable error interrupt */
    if (0U != (mask & (uint32_t)kEDMA_ErrorInterruptEnable))
    {
        EDMA_CHANNEL_BASE(base, channel)->CH_CSR |= DMA_CH_CSR_EEI_MASK;
    }
#endif

    /* Enable Major interrupt */
    if (0U != (mask & (uint32_t)kEDMA_MajorInterruptEnable))
    {
        EDMA_TCD_BASE(base, channel)->CSR |= DMA_CSR_INTMAJOR_MASK;
    }

    /* Enable Half major interrupt */
    if (0U != (mask & (uint32_t)kEDMA_HalfInterruptEnable))
    {
        EDMA_TCD_BASE(base, channel)->CSR |= DMA_CSR_INTHALF_MASK;
    }
}

/*!
 * brief Disables the interrupt source for the eDMA transfer.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param mask The mask of the interrupt source to be set. Use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_DisableChannelInterrupts(EDMA_Type *base, uint32_t channel, uint32_t mask)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));

#if FSL_EDMA_SOC_IP_EDMA
    /* Disable error interrupt */
    if (0U != (mask & (uint32_t)kEDMA_ErrorInterruptEnable))
    {
        base->EEI &= (~((uint32_t)0x1U << channel));
    }
#else
    /* Enable error interrupt */
    if (0U != (mask & (uint32_t)kEDMA_ErrorInterruptEnable))
    {
        EDMA_CHANNEL_BASE(base, channel)->CH_CSR &= ~DMA_CH_CSR_EEI_MASK;
    }
#endif

    /* Disable Major interrupt */
    if (0U != (mask & (uint32_t)kEDMA_MajorInterruptEnable))
    {
        EDMA_TCD_BASE(base, channel)->CSR &= ~(uint16_t)DMA_CSR_INTMAJOR_MASK;
    }

    /* Disable Half major interrupt */
    if (0U != (mask & (uint32_t)kEDMA_HalfInterruptEnable))
    {
        EDMA_TCD_BASE(base, channel)->CSR &= ~(uint16_t)DMA_CSR_INTHALF_MASK;
    }
}

/*!
 * brief Gets the eDMA channel status flags.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * return The mask of channel status flags. Users need to use the
 *         _edma_channel_status_flags type to decode the return variables.
 */
uint32_t EDMA_GetChannelStatusFlags(EDMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));

    uint32_t retval = 0;

#if FSL_EDMA_SOC_IP_EDMA
    /* Get DONE bit flag */
    retval |= (((uint32_t)EDMA_TCD_BASE(base, channel)->CSR & DMA_CSR_DONE_MASK) >> DMA_CSR_DONE_SHIFT);
    /* Get ERROR bit flag */
    retval |= ((((uint32_t)EDMA_BASE(base)->ERR >> channel) & 0x1U) << 1U);
    /* Get INT bit flag */
    retval |= ((((uint32_t)EDMA_BASE(base)->INT >> channel) & 0x1U) << 2U);
#else
    /* Get DONE bit flag */
    retval |= (((uint32_t)EDMA_CHANNEL_BASE(base, channel)->CH_CSR & DMA_CH_CSR_DONE_MASK) >> DMA_CH_CSR_DONE_SHIFT);
    /* Get ERROR bit flag */
    retval |= ((((uint32_t)EDMA_CHANNEL_BASE(base, channel)->CH_ES >> DMA_CH_ES_ERR_SHIFT) & 0x1U) << 1U);
    /* Get INT bit flag */
    retval |= ((((uint32_t)EDMA_CHANNEL_BASE(base, channel)->CH_INT) & 0x1U) << 2U);
#endif
    return retval;
}

/*!
 * brief Clears the eDMA channel status flags.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param mask The mask of channel status to be cleared. Users need to use
 *             the defined _edma_channel_status_flags type.
 */
void EDMA_ClearChannelStatusFlags(EDMA_Type *base, uint32_t channel, uint32_t mask)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));

#if FSL_EDMA_SOC_IP_EDMA
    /* Clear DONE bit flag */
    if (0U != (mask & (uint32_t)kEDMA_DoneFlag))
    {
        EDMA_BASE(base)->CDNE = (uint8_t)channel;
    }
    /* Clear ERROR bit flag */
    if (0U != (mask & (uint32_t)kEDMA_ErrorFlag))
    {
        EDMA_BASE(base)->CERR = (uint8_t)channel;
    }
    /* Clear INT bit flag */
    if (0U != (mask & (uint32_t)kEDMA_InterruptFlag))
    {
        EDMA_BASE(base)->CINT = (uint8_t)channel;
    }
#else
    /* Clear DONE bit flag */
    if (0U != (mask & (uint32_t)kEDMA_DoneFlag))
    {
        EDMA_CHANNEL_BASE(base, channel)->CH_CSR |= DMA_CH_CSR_DONE_MASK;
    }
    /* Clear ERROR bit flag */
    else if (0U != (mask & (uint32_t)kEDMA_ErrorFlag))
    {
        EDMA_CHANNEL_BASE(base, channel)->CH_ES |= DMA_CH_ES_ERR_MASK;
    }
    /* Clear INT bit flag */
    if (0U != (mask & (uint32_t)kEDMA_InterruptFlag))
    {
        EDMA_CHANNEL_BASE(base, channel)->CH_INT = DMA_CH_INT_INT_MASK;
    }
#endif
}

/*!
 * brief Creates the eDMA handle.
 *
 * This function is called if using the transactional API for eDMA. This function
 * initializes the internal state of the eDMA handle.
 *
 * param handle eDMA handle pointer. The eDMA handle stores callback function and
 *               parameters.
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 */
void EDMA_CreateHandle(edma_handle_t *handle, EDMA_Type *base, uint32_t channel)
{
    assert(handle != NULL);
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL(base));

    uint32_t edmaInstance;
    edma_tcd_t *tcdRegs;

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    handle->channel = channel;

    /* Get the DMA instance number */
    edmaInstance                        = EDMA_GetInstance(base);
    s_EDMAHandle[edmaInstance][channel] = handle;
    /* Enable NVIC interrupt */
    (void)EnableIRQ(s_edmaIRQNumber[edmaInstance][channel]);

    handle->tcdBase     = EDMA_TCD_BASE(base, channel);
    handle->channelBase = EDMA_CHANNEL_BASE(base, channel);
    handle->base        = base;
    /*
       Reset TCD registers to zero. Unlike the EDMA_TcdReset(DREQ will be set),
       CSR will be 0. Because in order to suit EDMA busy check mechanism in
       EDMA_SubmitTransfer, CSR must be set 0.
    */
    tcdRegs            = handle->tcdBase;
    tcdRegs->SADDR     = 0;
    tcdRegs->SOFF      = 0;
    tcdRegs->ATTR      = 0;
    tcdRegs->NBYTES    = 0;
    tcdRegs->SLAST     = 0;
    tcdRegs->DADDR     = 0;
    tcdRegs->DOFF      = 0;
    tcdRegs->CITER     = 0;
    tcdRegs->DLAST_SGA = 0;
    tcdRegs->CSR       = 0;
    tcdRegs->BITER     = 0;
}

/*!
 * brief Installs the TCDs memory pool into the eDMA handle.
 *
 * This function is called after the EDMA_CreateHandle to use scatter/gather feature. This function shall only be used
 * while users need to use scatter gather mode. Scatter gather mode enables EDMA to load a new transfer control block
 * (tcd) in hardware, and automatically reconfigure that DMA channel for a new transfer.
 * Users need to prepare tcd memory and also configure tcds using interface EDMA_SubmitTransfer.
 *
 * param handle eDMA handle pointer.
 * param tcdPool A memory pool to store TCDs. It must be 32 bytes aligned.
 * param tcdSize The number of TCD slots.
 */
void EDMA_InstallTCDMemory(edma_handle_t *handle, edma_tcd_t *tcdPool, uint32_t tcdSize)
{
    assert(handle != NULL);
    assert(((uint32_t)tcdPool & 0x1FU) == 0U);

    /* Initialize tcd queue attribute. */
    /* header should initial as 1, since that it is used to point to the next TCD to be loaded into TCD memory,
     * In EDMA driver IRQ handler, header will be used to calculate how many tcd has done, for example,
     * If application submit 4 transfer request, A->B->C->D,
     * when A finshed, the header is 0, C is the next TCD to be load, since B is already loaded,
     * according to EDMA driver IRQ handler, tcdDone = C - A - header = 2 - header = 2, but actually only 1 TCD done,
     * so the issue will be the wrong TCD done count will pass to application in first TCD interrupt.
     * During first submit, the header should be assigned to 1, since 0 is current one and 1 is next TCD to be loaded,
     * but software cannot know which submission is the first one, so assign 1 to header here.
     */
    handle->header  = 1;
    handle->tcdUsed = 0;
    handle->tcdSize = (int8_t)tcdSize;
    handle->tcdPool = tcdPool;
}

/*!
 * brief Installs a callback function for the eDMA transfer.
 *
 * This callback is called in the eDMA IRQ handler. Use the callback to do something after
 * the current major loop transfer completes. This function will be called every time one tcd finished transfer.
 *
 * param handle eDMA handle pointer.
 * param callback eDMA callback function pointer.
 * param userData A parameter for the callback function.
 */
void EDMA_SetCallback(edma_handle_t *handle, edma_callback callback, void *userData)
{
    assert(handle != NULL);

    handle->callback = callback;
    handle->userData = userData;
}

static edma_transfer_size_t EDMA_TransferWidthMapping(uint32_t width)
{
    edma_transfer_size_t transferSize = kEDMA_TransferSize1Bytes;

    /* map width to register value */
    switch (width)
    {
        /* width 8bit */
        case 1U:
            transferSize = kEDMA_TransferSize1Bytes;
            break;
        /* width 16bit */
        case 2U:
            transferSize = kEDMA_TransferSize2Bytes;
            break;
        /* width 32bit */
        case 4U:
            transferSize = kEDMA_TransferSize4Bytes;
            break;
#if (defined(FSL_FEATURE_EDMA_SUPPORT_8_BYTES_TRANSFER) && FSL_FEATURE_EDMA_SUPPORT_8_BYTES_TRANSFER)
        /* width 64bit */
        case 8U:
            transferSize = kEDMA_TransferSize8Bytes;
            break;
#endif
#if (defined(FSL_FEATURE_EDMA_SUPPORT_16_BYTES_TRANSFER) && FSL_FEATURE_EDMA_SUPPORT_16_BYTES_TRANSFER)
        /* width 128bit */
        case 16U:
            transferSize = kEDMA_TransferSize16Bytes;
            break;
#endif
        /* width 256bit */
        case 32U:
            transferSize = kEDMA_TransferSize32Bytes;
            break;
#if (defined(FSL_FEATURE_EDMA_SUPPORT_64_BYTES_TRANSFER) && FSL_FEATURE_EDMA_SUPPORT_64_BYTES_TRANSFER)
        /* width 512bit */
        case 64U:
            transferSize = kEDMA_TransferSize64Bytes;
            break;
#endif
#if (defined(FSL_FEATURE_EDMA_SUPPORT_128_BYTES_TRANSFER) && FSL_FEATURE_EDMA_SUPPORT_128_BYTES_TRANSFER)
        /* width 1024bit */
        case 128U:
            transferSize = kEDMA_TransferSize128Bytes;
            break;
#endif
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            assert(false);
            break;
    }

    return transferSize;
}

/*!
 * brief Prepares the eDMA transfer structure configurations.
 *
 * This function prepares the transfer configuration structure according to the user input.
 *
 * param config The user configuration structure of type edma_transfer_t.
 * param srcAddr eDMA transfer source address.
 * param srcWidth eDMA transfer source address width(bytes).
 * param srcOffset source address offset.
 * param destAddr eDMA transfer destination address.
 * param destWidth eDMA transfer destination address width(bytes).
 * param destOffset destination address offset.
 * param bytesEachRequest eDMA transfer bytes per channel request.
 * param transferBytes eDMA transfer bytes to be transferred.
 * note The data address and the data width must be consistent. For example, if the SRC
 *       is 4 bytes, the source address must be 4 bytes aligned, or it results in
 *       source address error (SAE).
 */
void EDMA_PrepareTransferConfig(edma_transfer_config_t *config,
                                void *srcAddr,
                                uint32_t srcWidth,
                                int16_t srcOffset,
                                void *destAddr,
                                uint32_t destWidth,
                                int16_t destOffset,
                                uint32_t bytesEachRequest,
                                uint32_t transferBytes)
{
    assert(config != NULL);
    assert(srcAddr != NULL);
    assert(destAddr != NULL);
#if (defined(FSL_FEATURE_EDMA_SUPPORT_128_BYTES_TRANSFER) && FSL_FEATURE_EDMA_SUPPORT_128_BYTES_TRANSFER)
    assert((srcWidth != 0U) && (srcWidth <= 128U) && ((srcWidth & (srcWidth - 1U)) == 0U));
    assert((destWidth != 0U) && (destWidth <= 128U) && ((destWidth & (destWidth - 1U)) == 0U));
#elif (defined(FSL_FEATURE_EDMA_SUPPORT_64_BYTES_TRANSFER) && FSL_FEATURE_EDMA_SUPPORT_64_BYTES_TRANSFER)
    assert((srcWidth != 0U) && (srcWidth <= 64U) && ((srcWidth & (srcWidth - 1U)) == 0U));
    assert((destWidth != 0U) && (destWidth <= 64U) && ((destWidth & (destWidth - 1U)) == 0U));
#else
    assert((srcWidth != 0U) && (srcWidth <= 32U) && ((srcWidth & (srcWidth - 1U)) == 0U));
    assert((destWidth != 0U) && (destWidth <= 32U) && ((destWidth & (destWidth - 1U)) == 0U));
#endif
#if (!defined(FSL_FEATURE_EDMA_SUPPORT_8_BYTES_TRANSFER) || !FSL_FEATURE_EDMA_SUPPORT_8_BYTES_TRANSFER)
    assert(srcWidth != 8U);
    assert(srcWidth != 8U);
#endif
#if (!defined(FSL_FEATURE_EDMA_SUPPORT_16_BYTES_TRANSFER) || !FSL_FEATURE_EDMA_SUPPORT_16_BYTES_TRANSFER)
    assert(srcWidth != 16U);
    assert(srcWidth != 16U);
#endif
#if (!defined(FSL_FEATURE_EDMA_SUPPORT_64_BYTES_TRANSFER) || !FSL_FEATURE_EDMA_SUPPORT_64_BYTES_TRANSFER)
    assert(srcWidth != 64U);
    assert(srcWidth != 64U);
#endif
    assert((transferBytes % bytesEachRequest) == 0U);
    assert((((uint32_t)(uint32_t *)srcAddr) % srcWidth) == 0U);
    assert((((uint32_t)(uint32_t *)destAddr) % destWidth) == 0U);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    config->srcAddr  = MEMORY_ConvertMemoryMapAddress((uint32_t)(uint32_t *)srcAddr, kMEMORY_Local2DMA);
    config->destAddr = MEMORY_ConvertMemoryMapAddress((uint32_t)(uint32_t *)destAddr, kMEMORY_Local2DMA);
#else
    config->destAddr = (uint32_t)(uint32_t *)destAddr;
    config->srcAddr  = (uint32_t)(uint32_t *)srcAddr;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
    config->minorLoopBytes   = bytesEachRequest;
    config->majorLoopCounts  = transferBytes / bytesEachRequest;
    config->srcTransferSize  = EDMA_TransferWidthMapping(srcWidth);
    config->destTransferSize = EDMA_TransferWidthMapping(destWidth);
    config->destOffset       = destOffset;
    config->srcOffset        = srcOffset;
    /* enable major interrupt by default */
    config->enabledInterruptMask = kEDMA_MajorInterruptEnable;
}

/*!
 * brief Prepares the eDMA transfer structure.
 *
 * This function prepares the transfer configuration structure according to the user input.
 *
 * param config The user configuration structure of type edma_transfer_t.
 * param srcAddr eDMA transfer source address.
 * param srcWidth eDMA transfer source address width(bytes).
 * param destAddr eDMA transfer destination address.
 * param destWidth eDMA transfer destination address width(bytes).
 * param bytesEachRequest eDMA transfer bytes per channel request.
 * param transferBytes eDMA transfer bytes to be transferred.
 * param type eDMA transfer type.
 * note The data address and the data width must be consistent. For example, if the SRC
 *       is 4 bytes, the source address must be 4 bytes aligned, or it results in
 *       source address error (SAE).
 */
void EDMA_PrepareTransfer(edma_transfer_config_t *config,
                          void *srcAddr,
                          uint32_t srcWidth,
                          void *destAddr,
                          uint32_t destWidth,
                          uint32_t bytesEachRequest,
                          uint32_t transferBytes,
                          edma_transfer_type_t type)
{
    assert(config != NULL);

    int16_t srcOffset = 0, destOffset = 0;

    switch (type)
    {
        case kEDMA_MemoryToMemory:
            destOffset = (int16_t)destWidth;
            srcOffset  = (int16_t)srcWidth;
            break;
        case kEDMA_MemoryToPeripheral:
            destOffset = 0;
            srcOffset  = (int16_t)srcWidth;
            break;
        case kEDMA_PeripheralToMemory:
            destOffset = (int16_t)destWidth;
            srcOffset  = 0;
            break;
        case kEDMA_PeripheralToPeripheral:
            destOffset = 0;
            srcOffset  = 0;
            break;
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            assert(false);
            break;
    }

    EDMA_PrepareTransferConfig(config, srcAddr, srcWidth, srcOffset, destAddr, destWidth, destOffset, bytesEachRequest,
                               transferBytes);
}

/*!
 * brief Submits the eDMA transfer request.
 *
 * This function submits the eDMA transfer request according to the transfer configuration structure.
 * In scatter gather mode, call this function will add a configured tcd to the circular list of tcd pool.
 * The tcd pools is setup by call function EDMA_InstallTCDMemory before.
 *
 * param handle eDMA handle pointer.
 * param config Pointer to eDMA transfer configuration structure.
 * retval kStatus_EDMA_Success It means submit transfer request succeed.
 * retval kStatus_EDMA_QueueFull It means TCD queue is full. Submit transfer request is not allowed.
 * retval kStatus_EDMA_Busy It means the given channel is busy, need to submit request later.
 */
status_t EDMA_SubmitTransfer(edma_handle_t *handle, const edma_transfer_config_t *config)
{
    assert(handle != NULL);
    assert(config != NULL);
    assert(handle->tcdBase != NULL);

    edma_tcd_t *tcdRegs = handle->tcdBase;

    if (handle->tcdPool == NULL)
    {
        /*
         *    Check if EDMA channel is busy:
         *    1. if channel active bit is set, it implies that minor loop is executing, then channel is busy
         *    2. if channel active bit is not set and BITER not equal to CITER, it implies that major loop is executing,
         * then channel is busy
         *
         *    There is one case can not be covered in below condition:
         *    When transfer request is submitted, but no request from peripheral, that is to say channel sevice doesn't
         *    begin, if application would like to submit another transfer , then the TCD will be overwritten, since the
         *    ACTIVE is 0 and BITER = CITER, for such case, it is a scatter gather(link TCD) case actually, so
         *    application should enabled TCD pool for dynamic scatter gather mode by calling EDMA_InstallTCDMemory.
         */
#if defined FSL_EDMA_SOC_IP_EDMA && FSL_EDMA_SOC_IP_EDMA
        if (((tcdRegs->CSR & DMA_CSR_ACTIVE_MASK) != 0U) ||
#else
        if (((handle->channelBase->CH_CSR & DMA_CH_CSR_ACTIVE_MASK) != 0U) ||
#endif
            (((tcdRegs->CITER & DMA_CITER_ELINKNO_CITER_MASK) != (tcdRegs->BITER & DMA_BITER_ELINKNO_BITER_MASK))))
        {
            return kStatus_EDMA_Busy;
        }
        else
        {
            EDMA_TcdSetTransferConfig(tcdRegs, config, NULL);
            /* Enable auto disable request feature */
            tcdRegs->CSR |= DMA_CSR_DREQ_MASK;
            /* Enable major interrupt */
            tcdRegs->CSR |= DMA_CSR_INTMAJOR_MASK;

            return kStatus_Success;
        }
    }
    else /* Use the TCD queue. */
    {
        uint32_t primask;
        uint16_t csr;
        int8_t currentTcd;
        int8_t previousTcd;
        int8_t nextTcd;
        int8_t tmpTcdUsed;
        int8_t tmpTcdSize;

        /* Check if tcd pool is full. */
        primask    = DisableGlobalIRQ();
        tmpTcdUsed = handle->tcdUsed;
        tmpTcdSize = handle->tcdSize;
        if (tmpTcdUsed >= tmpTcdSize)
        {
            EnableGlobalIRQ(primask);

            return kStatus_EDMA_QueueFull;
        }
        currentTcd = handle->tail;
        handle->tcdUsed++;
        /* Calculate index of next TCD */
        nextTcd = currentTcd + 1;
        if (nextTcd == handle->tcdSize)
        {
            nextTcd = 0;
        }
        /* Advance queue tail index */
        handle->tail = nextTcd;
        EnableGlobalIRQ(primask);
        /* Calculate index of previous TCD */
        previousTcd = currentTcd != 0 ? currentTcd - 1 : (handle->tcdSize - 1);
        /* Configure current TCD block. */
        EDMA_TcdReset(&handle->tcdPool[currentTcd]);
        EDMA_TcdSetTransferConfig(&handle->tcdPool[currentTcd], config, NULL);
        /* Enable major interrupt */
        handle->tcdPool[currentTcd].CSR |= DMA_CSR_INTMAJOR_MASK;
        /* Link current TCD with next TCD for identification of current TCD */
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        handle->tcdPool[currentTcd].DLAST_SGA =
            MEMORY_ConvertMemoryMapAddress((uint32_t)&handle->tcdPool[nextTcd], kMEMORY_Local2DMA);
#else
        handle->tcdPool[currentTcd].DLAST_SGA = (uint32_t)&handle->tcdPool[nextTcd];
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
        /* Chain from previous descriptor unless tcd pool size is 1(this descriptor is its own predecessor). */
        if (currentTcd != previousTcd)
        {
            /* Enable scatter/gather feature in the previous TCD block. */
            csr = handle->tcdPool[previousTcd].CSR | ((uint16_t)DMA_CSR_ESG_MASK);
            csr &= ~((uint16_t)DMA_CSR_DREQ_MASK);
            handle->tcdPool[previousTcd].CSR = csr;
            /*
                Check if the TCD block in the registers is the previous one (points to current TCD block). It
                is used to check if the previous TCD linked has been loaded in TCD register. If so, it need to
                link the TCD register in case link the current TCD with the dead chain when TCD loading occurs
                before link the previous TCD block.
            */
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            if (tcdRegs->DLAST_SGA ==
                MEMORY_ConvertMemoryMapAddress((uint32_t)&handle->tcdPool[currentTcd], kMEMORY_Local2DMA))
#else
            if (tcdRegs->DLAST_SGA == (uint32_t)&handle->tcdPool[currentTcd])
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
            {
                /* Clear the DREQ bits for the dynamic scatter gather */
                tcdRegs->CSR |= DMA_CSR_DREQ_MASK;
                /* Enable scatter/gather also in the TCD registers. */
                csr = tcdRegs->CSR | DMA_CSR_ESG_MASK;
                /* Must write the CSR register one-time, because the transfer maybe finished anytime. */
                tcdRegs->CSR = csr;
                /*
                    It is very important to check the ESG bit!
                    Because this hardware design: if DONE bit is set, the ESG bit can not be set. So it can
                    be used to check if the dynamic TCD link operation is successful. If ESG bit is not set
                    and the DLAST_SGA is not the next TCD address(it means the dynamic TCD link succeed and
                    the current TCD block has been loaded into TCD registers), it means transfer finished
                    and TCD link operation fail, so must install TCD content into TCD registers and enable
                    transfer again. And if ESG is set, it means transfer has not finished, so TCD dynamic
                    link succeed.
                */
                if (0U != (tcdRegs->CSR & DMA_CSR_ESG_MASK))
                {
                    tcdRegs->CSR &= ~(uint16_t)DMA_CSR_DREQ_MASK;
                    return kStatus_Success;
                }
                /*
                    Check whether the current TCD block is already loaded in the TCD registers. It is another
                    condition when ESG bit is not set: it means the dynamic TCD link succeed and the current
                    TCD block has been loaded into TCD registers.
                */
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                if (tcdRegs->DLAST_SGA ==
                    MEMORY_ConvertMemoryMapAddress((uint32_t)&handle->tcdPool[nextTcd], kMEMORY_Local2DMA))
#else
                if (tcdRegs->DLAST_SGA == (uint32_t)&handle->tcdPool[nextTcd])
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
                {
                    return kStatus_Success;
                }
                /*
                    If go to this, means the previous transfer finished, and the DONE bit is set.
                    So shall configure TCD registers.
                */
            }
            else if (tcdRegs->DLAST_SGA != 0UL)
            {
                /* The current TCD block has been linked successfully. */
                return kStatus_Success;
            }
            else
            {
                /*
                    DLAST_SGA is 0 and it means the first submit transfer, so shall configure
                    TCD registers.
                */
            }
        }
        /* There is no live chain, TCD block need to be installed in TCD registers. */
        EDMA_InstallTCD(handle->base, handle->channel, &handle->tcdPool[currentTcd]);

        return kStatus_Success;
    }
}

/*!
 * brief Submits the eDMA scatter gather transfer configurations.
 *
 * The function is target for submit loop transfer request,
 * the ring transfer request means that the transfer request TAIL is link to HEAD, such as,
 * A->B->C->D->A, or A->A
 *
 * To use the ring transfer feature, the application should allocate several transfer object, such as
 * @code
 * edma_channel_transfer_config_t transfer[2];
 * EDMA_TransferSubmitLoopTransfer(handle, &transfer, 2U);
 * @endcode
 * Then eDMA driver will link transfer[0] and transfer[1] to each other
 *
 * note Application should check the return value of this function to avoid transfer request
 * submit failed
 *
 * param handle eDMA handle pointer
 * param transfer pointer to user's eDMA channel configure structure, see edma_channel_transfer_config_t for detail
 * param transferLoopCount the count of the transfer ring, if loop count is 1, that means that the one will link to
 * itself.
 *
 * retval #kStatus_Success It means submit transfer request succeed
 * retval #kStatus_EDMA_ChannelBusy channel is in busy status
 * retval #kStatus_EDMA_ChannelQueueFull It means TCD pool is not len enough for the ring transfer request
 */
status_t EDMA_SubmitLoopTransfer(edma_handle_t *handle, edma_transfer_config_t *transfer, uint32_t transferLoopCount)
{
    assert(transfer != NULL);
    assert(handle != NULL);
    assert(handle->tcdPool != NULL);

    uint32_t i = 0U;

    if (handle->tcdSize < transferLoopCount)
    {
        return kStatus_InvalidArgument;
    }

    /*
     *    Check if EDMA channel is busy:
     *    1. if channel active bit is set, it implies that minor loop is executing, then channel is busy
     *    2. if channel active bit is not set and BITER not equal to CITER, it implies that major loop is executing,
     *       then channel is busy
     *
     *    There is one case can not be covered in below condition:
     *    When transfer request is submitted, but no request from peripheral, that is to say channel service doesn't
     *    begin, if application would like to submit another transfer , then the TCD will be overwritten, since the
     *    ACTIVE is 0 and BITER = CITER, for such case, it is a scatter gather(link TCD) case actually, so
     *    application should enabled TCD pool for dynamic scatter gather mode by calling EDMA_InstallTCDMemory.
     */
#if defined FSL_EDMA_SOC_IP_EDMA && FSL_EDMA_SOC_IP_EDMA
    if (((handle->tcdBase->CSR & DMA_CSR_ACTIVE_MASK) != 0U) ||
#else
    if (((handle->channelBase->CH_CSR & DMA_CH_CSR_ACTIVE_MASK) != 0U) ||
#endif
        (((handle->tcdBase->CITER & DMA_CITER_ELINKNO_CITER_MASK) !=
          (handle->tcdBase->BITER & DMA_BITER_ELINKNO_BITER_MASK))))
    {
        return kStatus_EDMA_Busy;
    }

    (void)memset(handle->tcdPool, 0, handle->tcdSize * sizeof(edma_tcd_t));
    for (i = 0U; i < transferLoopCount - 1UL; i++)
    {
        transfer[i].linkTCD = &handle->tcdPool[i + 1UL];
        EDMA_ConfigChannelSoftwareTCD(&(handle->tcdPool[i]), &transfer[i]);
    }

    /* prepare last one in the ring and link it to the HEAD of the ring */
    transfer[i].linkTCD = &handle->tcdPool[0];
    EDMA_ConfigChannelSoftwareTCD(&(handle->tcdPool[i]), &transfer[i]);

#if FSL_EDMA_SOC_IP_EDMA
    if (((transfer->enableSrcMinorLoopOffset) || (transfer->enableDstMinorLoopOffset)))
    {
        EDMA_EnableMinorLoopMapping(handle->psBase, true);
    }
#endif
    /* There is no live chain, TCD block need to be installed in TCD registers. */
    EDMA_InstallTCD(handle->base, handle->channel, &handle->tcdPool[0U]);

    /* enable interrupt */
    EDMA_EnableChannelInterrupts(handle->base, handle->channel,
                                 transfer->enabledInterruptMask & ~((uint16_t)kEDMA_ErrorInterruptEnable));

    return kStatus_Success;
}

/*!
 * brief eDMA starts transfer.
 *
 * This function enables the channel request. Users can call this function after submitting the transfer request
 * or before submitting the transfer request.
 *
 * param handle eDMA handle pointer.
 */
void EDMA_StartTransfer(edma_handle_t *handle)
{
    assert(handle != NULL);

    edma_tcd_t *tcdRegs = handle->tcdBase;

#if FSL_EDMA_SOC_IP_EDMA
    if (handle->tcdPool == NULL)
    {
        handle->base->SERQ = DMA_SERQ_SERQ(handle->channel);
    }
    else /* Use the TCD queue. */
    {
        uint32_t primask;

        /* Check if there was at least one descriptor submitted since reset (TCD in registers is valid) */
        if (tcdRegs->DLAST_SGA != 0U)
        {
            primask = DisableGlobalIRQ();
            /* Check if channel request is actually disable. */
            if ((handle->base->ERQ & ((uint32_t)1U << handle->channel)) == 0U)
            {
                /* Check if transfer is paused. */
                tmpCSR = tcdRegs->CSR;
                if ((0U == (tmpCSR & DMA_CSR_DONE_MASK)) || (0U != (tmpCSR & DMA_CSR_ESG_MASK)))
                {
                    /*
                        Re-enable channel request must be as soon as possible, so must put it into
                        critical section to avoid task switching or interrupt service routine.
                    */
                    handle->base->SERQ = DMA_SERQ_SERQ(handle->channel);
                }
            }
            EnableGlobalIRQ(primask);
        }
    }
#else
    if (handle->channelBase->CH_MUX == 0U)
    {
        tcdRegs->CSR |= DMA_CSR_START_MASK;
    }
    else if (handle->tcdPool == NULL)
    {
        handle->channelBase->CH_CSR |= DMA_CH_CSR_ERQ_MASK;
    }
    else
    {
        /* Check if channel request is actually disable. */
        if ((handle->channelBase->CH_CSR & DMA_CH_CSR_ERQ_MASK) == 0U)
        {
            /* Check if transfer is paused. */
            if ((!((handle->channelBase->CH_CSR & DMA_CH_CSR_DONE_MASK) != 0U)) ||
                ((tcdRegs->CSR & DMA_CSR_ESG_MASK) != 0U))
            {
                /*
                    Re-enable channel request must be as soon as possible, so must put it into
                    critical section to avoid task switching or interrupt service routine.
                */
                handle->channelBase->CH_CSR |= DMA_CH_CSR_ERQ_MASK;
            }
        }
    }
#endif
}

/*!
 * brief eDMA stops transfer.
 *
 * This function disables the channel request to pause the transfer. Users can call EDMA_StartTransfer()
 * again to resume the transfer.
 *
 * param handle eDMA handle pointer.
 */
void EDMA_StopTransfer(edma_handle_t *handle)
{
    assert(handle != NULL);
#if FSL_EDMA_SOC_IP_EDMA
    handle->base->CERQ = DMA_CERQ_CERQ(handle->channel);
#else
    handle->channelBase->CH_CSR = handle->channelBase->CH_CSR & (~(DMA_CH_CSR_DONE_MASK | DMA_CH_CSR_ERQ_MASK));
#endif
}

/*!
 * brief eDMA aborts transfer.
 *
 * This function disables the channel request and clear transfer status bits.
 * Users can submit another transfer after calling this API.
 *
 * param handle DMA handle pointer.
 */
void EDMA_AbortTransfer(edma_handle_t *handle)
{
    EDMA_StopTransfer(handle);
    /*
        Clear CSR to release channel. Because if the given channel started transfer,
        CSR will be not zero. Because if it is the last transfer, DREQ will be set.
        If not, ESG will be set.
    */
    EDMA_TcdReset(handle->tcdBase);

    /* Handle the tcd */
    if (handle->tcdPool != NULL)
    {
        handle->header  = 1;
        handle->tail    = 0;
        handle->tcdUsed = 0;
    }
}

/*!
 * brief eDMA IRQ handler for the current major loop transfer completion.
 *
 * This function clears the channel major interrupt flag and calls
 * the callback function if it is not NULL.
 *
 * Note:
 * For the case using TCD queue, when the major iteration count is exhausted, additional operations are performed.
 * These include the final address adjustments and reloading of the BITER field into the CITER.
 * Assertion of an optional interrupt request also occurs at this time, as does a possible fetch of a new TCD from
 * memory using the scatter/gather address pointer included in the descriptor (if scatter/gather is enabled).
 *
 * For instance, when the time interrupt of TCD[0] happens, the TCD[1] has already been loaded into the eDMA engine.
 * As sga and sga_index are calculated based on the DLAST_SGA bitfield lies in the TCD_CSR register, the sga_index
 * in this case should be 2 (DLAST_SGA of TCD[1] stores the address of TCD[2]). Thus, the "tcdUsed" updated should be
 * (tcdUsed - 2U) which indicates the number of TCDs can be loaded in the memory pool (because TCD[0] and TCD[1] have
 * been loaded into the eDMA engine at this point already.).
 *
 * For the last two continuous ISRs in a scatter/gather process, they  both load the last TCD (The last ISR does not
 * load a new TCD) from the memory pool to the eDMA engine when major loop completes.
 * Therefore, ensure that the header and tcdUsed updated are identical for them.
 * tcdUsed are both 0 in this case as no TCD to be loaded.
 *
 * See the "eDMA basic data flow" in the eDMA Functional description section of the Reference Manual for
 * further details.
 *
 * param handle eDMA handle pointer.
 */
void EDMA_HandleIRQ(edma_handle_t *handle)
{
    assert(handle != NULL);

    bool transfer_done;

#if FSL_EDMA_SOC_IP_EDMA
    /* Check if transfer is already finished. */
    transfer_done = ((handle->tcdBase->CSR & DMA_CSR_DONE_MASK) != 0U);
#else
    transfer_done               = handle->channelBase->CH_CSR & DMA_CH_CSR_DONE_MASK;
#endif

#if FSL_EDMA_SOC_IP_EDMA
    if ((handle->base->INT >> channel) != 0U)
    {
        handle->base->CINT = channel;
    }
#else
    if ((handle->channelBase->CH_INT & DMA_CH_INT_INT_MASK) != 0U)
    {
        handle->channelBase->CH_INT |= DMA_CH_INT_INT_MASK;
    }
#endif

    if (handle->tcdPool == NULL)
    {
        if (handle->callback != NULL)
        {
            (handle->callback)(handle, handle->userData, transfer_done, 0);
        }
    }
    else /* Use the TCD queue. Please refer to the API descriptions in the eDMA header file for detailed information. */
    {
        uint32_t sga = (uint32_t)((edma_tcd_t *)(handle->tcdBase))->DLAST_SGA;
        uint32_t sga_index;
        int32_t tcds_done;
        uint8_t new_header;
        bool esg = ((handle->tcdBase->CSR & DMA_CSR_ESG_MASK) != 0U);

        /* Get the offset of the next transfer TCD blocks to be loaded into the eDMA engine. */
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        sga -= MEMORY_ConvertMemoryMapAddress((uint32_t)handle->tcdPool, kMEMORY_Local2DMA);
#else
        sga -= (uint32_t)handle->tcdPool;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
        /* Get the index of the next transfer TCD blocks to be loaded into the eDMA engine. */
        sga_index = sga / sizeof(edma_tcd_t);
        /* Adjust header positions. */
        if (transfer_done)
        {
            /* New header shall point to the next TCD to be loaded (current one is already finished) */
            new_header = (uint8_t)sga_index;
        }
        else
        {
            /* New header shall point to this descriptor currently loaded (not finished yet) */
            new_header = sga_index != 0U ? (uint8_t)sga_index - 1U : (uint8_t)handle->tcdSize - 1U;
        }
        /* Calculate the number of finished TCDs */
        if (new_header == (uint8_t)handle->header)
        {
            int8_t tmpTcdUsed = handle->tcdUsed;
            int8_t tmpTcdSize = handle->tcdSize;

            /* check esg here for the case that application submit only one request, once the request complete:
             * new_header(1) = handle->header(1)
             * tcdUsed(1) != tcdSize(>1)
             * As the application submit only once, so scatter gather must not enabled, then tcds_done should be 1
             */
            if ((tmpTcdUsed == tmpTcdSize) || (!esg))
            {
                tcds_done = handle->tcdUsed;
            }
            else
            {
                /* No TCD in the memory are going to be loaded or internal error occurs. */
                tcds_done = 0;
            }
        }
        else
        {
            tcds_done = (int32_t)new_header - (int32_t)handle->header;
            if (tcds_done < 0)
            {
                tcds_done += handle->tcdSize;
            }
            /*
             * While code run to here, it means a TCD transfer Done and a new TCD has loaded to the hardware
             * so clear DONE here to allow submit scatter gather transfer request in the callback to avoid TCD
             * overwritten.
             */
            if (transfer_done)
            {
#if FSL_EDMA_SOC_IP_EDMA
                handle->base->CDNE = handle->channel;
#else
                handle->channelBase->CH_CSR |= DMA_CH_CSR_DONE_MASK;
#endif
            }
        }
        /* Advance header which points to the TCD to be loaded into the eDMA engine from memory. */
        handle->header = (int8_t)new_header;
        /* Release TCD blocks. tcdUsed is the TCD number which can be used/loaded in the memory pool. */
        handle->tcdUsed -= (int8_t)tcds_done;
        /* Invoke callback function. */
        if (NULL != handle->callback)
        {
            (handle->callback)(handle, handle->userData, transfer_done, tcds_done);
        }

        /*
         * 1.clear the DONE bit here is meaningful for below cases:
         * A new TCD has been loaded to EDMA already:
         * need to clear the DONE bit in the IRQ handler to avoid TCD in EDMA been overwritten
         * if peripheral request isn't coming before next transfer request.
         * 2. Don't clear DONE bit for below case,
         * for the case that transfer request submitted in the privious edma callback, this is a case that doesn't
         * need scatter gather, so keep DONE bit during the next transfer request submission will re-install the TCD and
         * the DONE bit will be cleared together with TCD re-installation.
         */
        if (transfer_done)
        {
            if ((handle->tcdBase->CSR & DMA_CSR_ESG_MASK) != 0U)
            {
#if FSL_EDMA_SOC_IP_EDMA
                handle->base->CDNE = handle->channel;
#else
                handle->channelBase->CH_CSR |= DMA_CH_CSR_DONE_MASK;
#endif
            }
        }
    }
}

void EDMA_DriverIRQHandler(uint32_t instance, uint32_t channel);
void EDMA_DriverIRQHandler(uint32_t instance, uint32_t channel)
{
#if FSL_EDMA_SOC_IP_EDMA
    if ((s_edmaBases[instance]->INT >> channel) != 0U)
    {
        EDMA_HandleIRQ(s_EDMAHandle[instance][channel]);
    }
#else
    if ((EDMA_CHANNEL_BASE(s_edmaBases[instance], channel)->CH_INT & DMA_CH_INT_INT_MASK) != 0U)
    {
        EDMA_HandleIRQ(s_EDMAHandle[instance][channel]);
    }
#endif
    SDK_ISR_EXIT_BARRIER;
}
