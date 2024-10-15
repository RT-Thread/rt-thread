/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dma"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get instance number for DMA.
 *
 * @param base DMA peripheral base address.
 */
static uint32_t DMA_GetInstance(DMA_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Array to map DMA instance number to base pointer. */
static DMA_Type *const s_dmaBases[] = DMA_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Array to map DMA instance number to clock name. */
static const clock_ip_name_t s_dmaClockName[] = DMA_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Array to map DMA instance number to IRQ number. */
static const IRQn_Type s_dmaIRQNumber[][FSL_FEATURE_DMA_MODULE_CHANNEL] = DMA_CHN_IRQS;

/*! @brief Pointers to transfer handle for each DMA channel. */
static dma_handle_t *s_DMAHandle[FSL_FEATURE_DMA_MODULE_CHANNEL * FSL_FEATURE_SOC_DMA_COUNT];

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t DMA_GetInstance(DMA_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_dmaBases); instance++)
    {
        if (s_dmaBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_dmaBases));

    return instance;
}

/*!
 * brief Initializes the DMA peripheral.
 *
 * This function ungates the DMA clock.
 *
 * param base DMA peripheral base address.
 */
void DMA_Init(DMA_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(s_dmaClockName[DMA_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Deinitializes the DMA peripheral.
 *
 * This function gates the DMA clock.
 *
 * param base DMA peripheral base address.
 */
void DMA_Deinit(DMA_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(s_dmaClockName[DMA_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Resets the DMA channel.
 *
 * Sets all register values to reset values and enables
 * the cycle steal and auto stop channel request features.
 *
 * param base DMA peripheral base address.
 * param channel DMA channel number.
 */
void DMA_ResetChannel(DMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    /* clear all status bit */
    base->DMA[channel].DSR_BCR |= DMA_DSR_BCR_DONE(true);
    /* clear all registers */
    base->DMA[channel].SAR     = 0;
    base->DMA[channel].DAR     = 0;
    base->DMA[channel].DSR_BCR = 0;
    /* enable cycle steal and enable auto disable channel request */
    base->DMA[channel].DCR = DMA_DCR_D_REQ(true) | DMA_DCR_CS(true);
}

/*!
 * brief Configures the DMA transfer attribute.
 *
 * This function configures the transfer attribute including the source address,
 * destination address, transfer size, and so on.
 * This example shows how to set up the dma_transfer_config_t
 * parameters and how to call the DMA_ConfigBasicTransfer function.
 * code
 *   dma_transfer_config_t transferConfig;
 *   memset(&transferConfig, 0, sizeof(transferConfig));
 *   transferConfig.srcAddr = (uint32_t)srcAddr;
 *   transferConfig.destAddr = (uint32_t)destAddr;
 *   transferConfig.enbaleSrcIncrement = true;
 *   transferConfig.enableDestIncrement = true;
 *   transferConfig.srcSize = kDMA_Transfersize32bits;
 *   transferConfig.destSize = kDMA_Transfersize32bits;
 *   transferConfig.transferSize = sizeof(uint32_t) * BUFF_LENGTH;
 *   DMA_SetTransferConfig(DMA0, 0, &transferConfig);
 * endcode
 *
 * param base DMA peripheral base address.
 * param channel DMA channel number.
 * param config Pointer to the DMA transfer configuration structure.
 */
void DMA_SetTransferConfig(DMA_Type *base, uint32_t channel, const dma_transfer_config_t *config)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);
    assert(config != NULL);

    uint32_t tmpreg;

    /* Set source address */
    base->DMA[channel].SAR = config->srcAddr;
    /* Set destination address */
    base->DMA[channel].DAR = config->destAddr;
    /* Set transfer bytes */
    base->DMA[channel].DSR_BCR = DMA_DSR_BCR_BCR(config->transferSize);
    /* Set DMA Control Register */
    tmpreg = base->DMA[channel].DCR;
    tmpreg &= ~(DMA_DCR_DSIZE_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SSIZE_MASK | DMA_DCR_SINC_MASK);
    tmpreg |= (DMA_DCR_DSIZE(config->destSize) | DMA_DCR_DINC(config->enableDestIncrement) |
               DMA_DCR_SSIZE(config->srcSize) | DMA_DCR_SINC(config->enableSrcIncrement));
    base->DMA[channel].DCR = tmpreg;
}

/*!
 * brief Configures the DMA channel link feature.
 *
 * This function allows DMA channels to have their transfers linked. The current DMA channel
 * triggers a DMA request to the linked channels (LCH1 or LCH2) depending on the channel link
 * type.
 * Perform a link to channel LCH1 after each cycle-steal transfer followed by a link to LCH2
 * after the BCR decrements to 0 if the type is kDMA_ChannelLinkChannel1AndChannel2.
 * Perform a link to LCH1 after each cycle-steal transfer if the type is kDMA_ChannelLinkChannel1.
 * Perform a link to LCH1 after the BCR decrements to 0 if the type is kDMA_ChannelLinkChannel1AfterBCR0.
 *
 * param base DMA peripheral base address.
 * param channel DMA channel number.
 * param config Pointer to the channel link configuration structure.
 */
void DMA_SetChannelLinkConfig(DMA_Type *base, uint32_t channel, const dma_channel_link_config_t *config)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);
    assert(config != NULL);

    uint32_t tmpreg;

    tmpreg = base->DMA[channel].DCR;
    tmpreg &= ~(DMA_DCR_LINKCC_MASK | DMA_DCR_LCH1_MASK | DMA_DCR_LCH2_MASK);
    tmpreg |= (DMA_DCR_LINKCC(config->linkType) | DMA_DCR_LCH1(config->channel1) | DMA_DCR_LCH2(config->channel2));
    base->DMA[channel].DCR = tmpreg;
}

/*!
 * brief Sets the DMA modulo for the DMA transfer.
 *
 * This function defines a specific address range specified to be the value after (SAR + SSIZE)/(DAR + DSIZE)
 * calculation is performed or the original register value. It provides the ability to implement a circular
 * data queue easily.
 *
 * param base DMA peripheral base address.
 * param channel DMA channel number.
 * param srcModulo source address modulo.
 * param destModulo destination address modulo.
 */
void DMA_SetModulo(DMA_Type *base, uint32_t channel, dma_modulo_t srcModulo, dma_modulo_t destModulo)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    uint32_t tmpreg;

    tmpreg = base->DMA[channel].DCR;
    tmpreg &= ~(DMA_DCR_SMOD_MASK | DMA_DCR_DMOD_MASK);
    tmpreg |= (DMA_DCR_SMOD(srcModulo) | DMA_DCR_DMOD(destModulo));
    base->DMA[channel].DCR = tmpreg;
}

/*!
 * brief Creates the DMA handle.
 *
 * This function is called first if using the transactional API for the DMA. This function
 * initializes the internal state of the DMA handle.
 *
 * param handle DMA handle pointer. The DMA handle stores callback function and
 *               parameters.
 * param base DMA peripheral base address.
 * param channel DMA channel number.
 */
void DMA_CreateHandle(dma_handle_t *handle, DMA_Type *base, uint32_t channel)
{
    assert(handle != NULL);
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    uint32_t dmaInstance;
    uint32_t channelIndex;

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    handle->base    = base;
    handle->channel = (uint8_t)channel;
    /* Get the DMA instance number */
    dmaInstance  = DMA_GetInstance(base);
    channelIndex = (dmaInstance * (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL) + channel;
    /* Store handle */
    s_DMAHandle[channelIndex] = handle;
    /* Enable NVIC interrupt. */
    (void)EnableIRQ(s_dmaIRQNumber[dmaInstance][channelIndex]);
}

/*!
 * brief Prepares the DMA transfer configuration structure.
 *
 * This function prepares the transfer configuration structure according to the user input.
 * The difference between this function and DMA_PrepareTransfer is that this function expose the address increment
 * parameter to application, but in DMA_PrepareTransfer, only parts of the address increment option can be selected by
 * dma_transfer_type_t.
 *
 * param config Pointer to the user configuration structure of type dma_transfer_config_t.
 * param srcAddr DMA transfer source address.
 * param srcWidth DMA transfer source address width (byte).
 * param destAddr DMA transfer destination address.
 * param destWidth DMA transfer destination address width (byte).
 * param transferBytes DMA transfer bytes to be transferred.
 * param srcIncrement source address increment type.
 * param destIncrement dest address increment type.
 */
void DMA_PrepareTransferConfig(dma_transfer_config_t *config,
                               void *srcAddr,
                               uint32_t srcWidth,
                               void *destAddr,
                               uint32_t destWidth,
                               uint32_t transferBytes,
                               dma_addr_increment_t srcIncrement,
                               dma_addr_increment_t destIncrement)
{
    assert(config != NULL);
    assert(srcAddr != NULL);
    assert(destAddr != NULL);
    assert((srcWidth == 1UL) || (srcWidth == 2UL) || (srcWidth == 4UL));
    assert((destWidth == 1UL) || (destWidth == 2UL) || (destWidth == 4UL));

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->srcAddr      = (uint32_t)(uint32_t *)srcAddr;
    config->destAddr     = (uint32_t)(uint32_t *)destAddr;
    config->transferSize = transferBytes;

    if (srcWidth == 1UL)
    {
        config->srcSize = kDMA_Transfersize8bits;
    }
    else if (srcWidth == 2UL)
    {
        config->srcSize = kDMA_Transfersize16bits;
    }
    else
    {
        config->srcSize = kDMA_Transfersize32bits;
    }

    if (destWidth == 1UL)
    {
        config->destSize = kDMA_Transfersize8bits;
    }
    else if (destWidth == 2UL)
    {
        config->destSize = kDMA_Transfersize16bits;
    }
    else
    {
        config->destSize = kDMA_Transfersize32bits;
    }

    config->enableSrcIncrement  = srcIncrement == kDMA_AddrNoIncrement ? false : true;
    config->enableDestIncrement = destIncrement == kDMA_AddrNoIncrement ? false : true;
}

/*!
 * brief Prepares the DMA transfer configuration structure.
 *
 * This function prepares the transfer configuration structure according to the user input.
 *
 * param config Pointer to the user configuration structure of type dma_transfer_config_t.
 * param srcAddr DMA transfer source address.
 * param srcWidth DMA transfer source address width (byte).
 * param destAddr DMA transfer destination address.
 * param destWidth DMA transfer destination address width (byte).
 * param transferBytes DMA transfer bytes to be transferred.
 * param type DMA transfer type.
 */
void DMA_PrepareTransfer(dma_transfer_config_t *config,
                         void *srcAddr,
                         uint32_t srcWidth,
                         void *destAddr,
                         uint32_t destWidth,
                         uint32_t transferBytes,
                         dma_transfer_type_t type)
{
    assert(config != NULL);
    assert(srcAddr != NULL);
    assert(destAddr != NULL);
    assert((srcWidth == 1UL) || (srcWidth == 2UL) || (srcWidth == 4UL));
    assert((destWidth == 1UL) || (destWidth == 2UL) || (destWidth == 4UL));

    dma_addr_increment_t srcIncrement = kDMA_AddrNoIncrement, destIncrement = kDMA_AddrNoIncrement;

    if (type == kDMA_MemoryToMemory)
    {
        srcIncrement  = kDMA_AddrIncrementPerTransferWidth;
        destIncrement = kDMA_AddrIncrementPerTransferWidth;
    }
    else if (type == kDMA_PeripheralToMemory)
    {
        srcIncrement  = kDMA_AddrNoIncrement;
        destIncrement = kDMA_AddrIncrementPerTransferWidth;
    }
    else
    {
        srcIncrement  = kDMA_AddrIncrementPerTransferWidth;
        destIncrement = kDMA_AddrNoIncrement;
    }

    DMA_PrepareTransferConfig(config, srcAddr, srcWidth, destAddr, destWidth, transferBytes, srcIncrement,
                              destIncrement);
}

/*!
 * brief Sets the DMA callback function.
 *
 * This callback is called in the DMA IRQ handler. Use the callback to do something
 * after the current transfer complete.
 *
 * param handle DMA handle pointer.
 * param callback DMA callback function pointer.
 * param userData Parameter for callback function. If it is not needed, just set to NULL.
 */
void DMA_SetCallback(dma_handle_t *handle, dma_callback callback, void *userData)
{
    assert(handle != NULL);

    handle->callback = callback;
    handle->userData = userData;
}

/*!
 * brief Submits the DMA transfer request.
 *
 * This function submits the DMA transfer request according to the transfer configuration structure.
 *
 * param handle DMA handle pointer.
 * param config Pointer to DMA transfer configuration structure.
 * param options Additional configurations for transfer. Use
 *                the defined dma_transfer_options_t type.
 * retval kStatus_DMA_Success It indicates that the DMA submit transfer request succeeded.
 * retval kStatus_DMA_Busy It indicates that the DMA is busy. Submit transfer request is not allowed.
 * note This function can't process multi transfer request.
 */
status_t DMA_SubmitTransfer(dma_handle_t *handle, const dma_transfer_config_t *config, uint32_t options)
{
    assert(handle != NULL);
    assert(config != NULL);

    /* Check if DMA is busy */
    if ((handle->base->DMA[handle->channel].DSR_BCR & DMA_DSR_BCR_BSY_MASK) != 0UL)
    {
        return kStatus_DMA_Busy;
    }
    DMA_ResetChannel(handle->base, handle->channel);
    DMA_SetTransferConfig(handle->base, handle->channel, config);
    if ((options & (uint32_t)kDMA_EnableInterrupt) != 0UL)
    {
        DMA_EnableInterrupts(handle->base, handle->channel);
    }
    return kStatus_Success;
}

/*!
 * brief DMA aborts a transfer.
 *
 * This function disables the channel request and clears all status bits.
 * Submit another transfer after calling this API.
 *
 * param handle DMA handle pointer.
 */
void DMA_AbortTransfer(dma_handle_t *handle)
{
    assert(handle != NULL);

    handle->base->DMA[handle->channel].DCR &= ~DMA_DCR_ERQ_MASK;
    /* clear all status bit */
    handle->base->DMA[handle->channel].DSR_BCR |= DMA_DSR_BCR_DONE(true);
}

/*!
 * brief DMA IRQ handler for current transfer complete.
 *
 * This function clears the channel interrupt flag and calls
 * the callback function if it is not NULL.
 *
 * param handle DMA handle pointer.
 */
void DMA_HandleIRQ(dma_handle_t *handle)
{
    assert(handle != NULL);

    /* Clear interrupt pending bit */
    DMA_ClearChannelStatusFlags(handle->base, handle->channel, kDMA_TransactionsDoneFlag);
    if (handle->callback != NULL)
    {
        (handle->callback)(handle, handle->userData);
    }
}

#if defined(FSL_FEATURE_DMA_MODULE_CHANNEL) && (FSL_FEATURE_DMA_MODULE_CHANNEL == 4U)
void DMA0_DriverIRQHandler(void);
void DMA0_DriverIRQHandler(void)
{
    DMA_HandleIRQ(s_DMAHandle[0]);
    SDK_ISR_EXIT_BARRIER;
}

void DMA1_DriverIRQHandler(void);
void DMA1_DriverIRQHandler(void)
{
    DMA_HandleIRQ(s_DMAHandle[1]);
    SDK_ISR_EXIT_BARRIER;
}

void DMA2_DriverIRQHandler(void);
void DMA2_DriverIRQHandler(void)
{
    DMA_HandleIRQ(s_DMAHandle[2]);
    SDK_ISR_EXIT_BARRIER;
}

void DMA3_DriverIRQHandler(void);
void DMA3_DriverIRQHandler(void)
{
    DMA_HandleIRQ(s_DMAHandle[3]);
    SDK_ISR_EXIT_BARRIER;
}
#endif /* FSL_FEATURE_DMA_MODULE_CHANNEL */
