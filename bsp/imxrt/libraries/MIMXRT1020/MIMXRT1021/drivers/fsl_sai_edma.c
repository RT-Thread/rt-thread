/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sai_edma.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.sai_edma"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Used for 32byte aligned */
#define STCD_ADDR(address) (edma_tcd_t *)(((uint32_t)(address) + 32UL) & ~0x1FU)

static I2S_Type *const s_saiBases[] = I2S_BASE_PTRS;
/* Only support 2 and 4 channel */
#define SAI_CHANNEL_MAP_MODULO(channel) (channel == 2U ? kEDMA_Modulo8bytes : kEDMA_Modulo16bytes)

/*<! Structure definition for uart_edma_private_handle_t. The structure is private. */
typedef struct sai_edma_private_handle
{
    I2S_Type *base;
    sai_edma_handle_t *handle;
} sai_edma_private_handle_t;

/*! @brief sai_edma_transfer_state, sai edma transfer state.*/
enum
{
    kSAI_Busy = 0x0U,      /*!< SAI is busy */
    kSAI_BusyLoopTransfer, /*!< SAI is busy for Loop transfer */
    kSAI_Idle,             /*!< Transfer is done. */
};

/*<! Private handle only used for internally. */
static sai_edma_private_handle_t s_edmaPrivateHandle[ARRAY_SIZE(s_saiBases)][2];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the instance number for SAI.
 *
 * @param base SAI base pointer.
 */
static uint32_t SAI_GetInstance(I2S_Type *base);

/*!
 * @brief SAI EDMA callback for send.
 *
 * @param handle pointer to sai_edma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 * @param done If the DMA transfer finished.
 * @param tcds The TCD index.
 */
static void SAI_TxEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds);

/*!
 * @brief SAI EDMA callback for receive.
 *
 * @param handle pointer to sai_edma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 * @param done If the DMA transfer finished.
 * @param tcds The TCD index.
 */
static void SAI_RxEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds);

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t SAI_GetInstance(I2S_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_saiBases); instance++)
    {
        if (s_saiBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_saiBases));

    return instance;
}

static void SAI_TxEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds)
{
    sai_edma_private_handle_t *privHandle = (sai_edma_private_handle_t *)userData;
    sai_edma_handle_t *saiHandle          = privHandle->handle;
    status_t status                       = kStatus_SAI_TxBusy;

    if (saiHandle->state != (uint32_t)kSAI_BusyLoopTransfer)
    {
        if (saiHandle->queueDriver + tcds > (uint32_t)SAI_XFER_QUEUE_SIZE)
        {
            (void)memset(&saiHandle->saiQueue[saiHandle->queueDriver], 0,
                         sizeof(sai_transfer_t) * ((uint32_t)SAI_XFER_QUEUE_SIZE - saiHandle->queueDriver));
            (void)memset(&saiHandle->saiQueue[0U], 0,
                         sizeof(sai_transfer_t) * (saiHandle->queueDriver + tcds - (uint32_t)SAI_XFER_QUEUE_SIZE));
        }
        else
        {
            (void)memset(&saiHandle->saiQueue[saiHandle->queueDriver], 0, sizeof(sai_transfer_t) * tcds);
        }
        saiHandle->queueDriver = (uint8_t)((saiHandle->queueDriver + tcds) % (uint32_t)SAI_XFER_QUEUE_SIZE);

        /* If all data finished, just stop the transfer */
        if (saiHandle->saiQueue[saiHandle->queueDriver].data == NULL)
        {
            /* Disable DMA enable bit */
            SAI_TxEnableDMA(privHandle->base, kSAI_FIFORequestDMAEnable, false);
            EDMA_AbortTransfer(handle);
            status = kStatus_SAI_TxIdle;
        }
    }

    /* If finished a block, call the callback function */
    if (saiHandle->callback != NULL)
    {
        (saiHandle->callback)(privHandle->base, saiHandle, status, saiHandle->userData);
    }
}

static void SAI_RxEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds)
{
    sai_edma_private_handle_t *privHandle = (sai_edma_private_handle_t *)userData;
    sai_edma_handle_t *saiHandle          = privHandle->handle;
    status_t status                       = kStatus_SAI_RxBusy;

    if (saiHandle->state != (uint32_t)kSAI_BusyLoopTransfer)
    {
        if (saiHandle->queueDriver + tcds > (uint32_t)SAI_XFER_QUEUE_SIZE)
        {
            (void)memset(&saiHandle->saiQueue[saiHandle->queueDriver], 0,
                         sizeof(sai_transfer_t) * ((uint32_t)SAI_XFER_QUEUE_SIZE - saiHandle->queueDriver));
            (void)memset(&saiHandle->saiQueue[0U], 0,
                         sizeof(sai_transfer_t) * (saiHandle->queueDriver + tcds - (uint32_t)SAI_XFER_QUEUE_SIZE));
        }
        else
        {
            (void)memset(&saiHandle->saiQueue[saiHandle->queueDriver], 0, sizeof(sai_transfer_t) * tcds);
        }
        saiHandle->queueDriver = (uint8_t)((saiHandle->queueDriver + tcds) % (uint32_t)SAI_XFER_QUEUE_SIZE);

        /* If all data finished, just stop the transfer */
        if (saiHandle->saiQueue[saiHandle->queueDriver].data == NULL)
        {
            /* Disable DMA enable bit */
            SAI_RxEnableDMA(privHandle->base, kSAI_FIFORequestDMAEnable, false);
            EDMA_AbortTransfer(handle);
            status = kStatus_SAI_RxIdle;
        }
    }

    /* If finished a block, call the callback function */
    if (saiHandle->callback != NULL)
    {
        (saiHandle->callback)(privHandle->base, saiHandle, status, saiHandle->userData);
    }
}

/*!
 * brief Initializes the SAI eDMA handle.
 *
 * This function initializes the SAI master DMA handle, which can be used for other SAI master transactional APIs.
 * Usually, for a specified SAI instance, call this API once to get the initialized handle.
 *
 * param base SAI base pointer.
 * param handle SAI eDMA handle pointer.
 * param base SAI peripheral base address.
 * param callback Pointer to user callback function.
 * param userData User parameter passed to the callback function.
 * param dmaHandle eDMA handle pointer, this handle shall be static allocated by users.
 */
void SAI_TransferTxCreateHandleEDMA(
    I2S_Type *base, sai_edma_handle_t *handle, sai_edma_callback_t callback, void *userData, edma_handle_t *txDmaHandle)
{
    assert((handle != NULL) && (txDmaHandle != NULL));

    uint32_t instance = SAI_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set sai base to handle */
    handle->dmaHandle = txDmaHandle;
    handle->callback  = callback;
    handle->userData  = userData;

    /* Set SAI state to idle */
    handle->state = (uint32_t)kSAI_Idle;

    s_edmaPrivateHandle[instance][0].base   = base;
    s_edmaPrivateHandle[instance][0].handle = handle;

    /* Need to use scatter gather */
    EDMA_InstallTCDMemory(txDmaHandle, (edma_tcd_t *)(STCD_ADDR(handle->tcd)), SAI_XFER_QUEUE_SIZE);

    /* Install callback for Tx dma channel */
    EDMA_SetCallback(txDmaHandle, SAI_TxEDMACallback, &s_edmaPrivateHandle[instance][0]);
}

/*!
 * brief Initializes the SAI Rx eDMA handle.
 *
 * This function initializes the SAI slave DMA handle, which can be used for other SAI master transactional APIs.
 * Usually, for a specified SAI instance, call this API once to get the initialized handle.
 *
 * param base SAI base pointer.
 * param handle SAI eDMA handle pointer.
 * param base SAI peripheral base address.
 * param callback Pointer to user callback function.
 * param userData User parameter passed to the callback function.
 * param dmaHandle eDMA handle pointer, this handle shall be static allocated by users.
 */
void SAI_TransferRxCreateHandleEDMA(
    I2S_Type *base, sai_edma_handle_t *handle, sai_edma_callback_t callback, void *userData, edma_handle_t *rxDmaHandle)
{
    assert((handle != NULL) && (rxDmaHandle != NULL));

    uint32_t instance = SAI_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set sai base to handle */
    handle->dmaHandle = rxDmaHandle;
    handle->callback  = callback;
    handle->userData  = userData;

    /* Set SAI state to idle */
    handle->state = (uint32_t)kSAI_Idle;

    s_edmaPrivateHandle[instance][1].base   = base;
    s_edmaPrivateHandle[instance][1].handle = handle;

    /* Need to use scatter gather */
    EDMA_InstallTCDMemory(rxDmaHandle, STCD_ADDR(handle->tcd), SAI_XFER_QUEUE_SIZE);

    /* Install callback for Tx dma channel */
    EDMA_SetCallback(rxDmaHandle, SAI_RxEDMACallback, &s_edmaPrivateHandle[instance][1]);
}

/*!
 * brief Configures the SAI Tx audio format.
 *
 * deprecated Do not use this function.  It has been superceded by ref SAI_TransferTxSetConfigEDMA
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred. This function also sets the eDMA parameter according to formatting requirements.
 *
 * param base SAI base pointer.
 * param handle SAI eDMA handle pointer.
 * param format Pointer to SAI audio data format structure.
 * param mclkSourceClockHz SAI master clock source frequency in Hz.
 * param bclkSourceClockHz SAI bit clock source frequency in Hz. If bit clock source is master
 * clock, this value should equals to masterClockHz in format.
 * retval kStatus_Success Audio format set successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 */
void SAI_TransferTxSetFormatEDMA(I2S_Type *base,
                                 sai_edma_handle_t *handle,
                                 sai_transfer_format_t *format,
                                 uint32_t mclkSourceClockHz,
                                 uint32_t bclkSourceClockHz)
{
    assert((handle != NULL) && (format != NULL));

    /* Configure the audio format to SAI registers */
    SAI_TxSetFormat(base, format, mclkSourceClockHz, bclkSourceClockHz);

    /* Get the transfer size from format, this should be used in EDMA configuration */
    if (format->bitWidth == 24U)
    {
        handle->bytesPerFrame = 4U;
    }
    else
    {
        handle->bytesPerFrame = (uint8_t)(format->bitWidth / 8U);
    }

    /* Update the data channel SAI used */
    handle->channel = format->channel;

    /* Clear the channel enable bits until do a send/receive */
    base->TCR3 &= ~I2S_TCR3_TCE_MASK;
#if defined(FSL_FEATURE_SAI_FIFO_COUNT) && (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    handle->count = (uint8_t)((uint32_t)FSL_FEATURE_SAI_FIFO_COUNT - format->watermark);
#else
    handle->count = 1U;
#endif /* FSL_FEATURE_SAI_FIFO_COUNT */
}

/*!
 * brief Configures the SAI Tx.
 *
 * note SAI eDMA supports data transfer in a multiple SAI channels if the FIFO Combine feature is supported.
 * To activate the multi-channel transfer enable SAI channels by filling the channelMask
 * of sai_transceiver_t with the corresponding values of _sai_channel_mask enum, enable the FIFO Combine
 * mode by assigning kSAI_FifoCombineModeEnabledOnWrite to the fifoCombine member of sai_fifo_combine_t
 * which is a member of sai_transceiver_t.
 * This is an example of multi-channel data transfer configuration step.
 *  code
 *   sai_transceiver_t config;
 *   SAI_GetClassicI2SConfig(&config, kSAI_WordWidth16bits, kSAI_Stereo, kSAI_Channel0Mask|kSAI_Channel1Mask);
 *   config.fifo.fifoCombine = kSAI_FifoCombineModeEnabledOnWrite;
 *   SAI_TransferTxSetConfigEDMA(I2S0, &edmaHandle, &config);
 *  endcode
 * param base SAI base pointer.
 * param handle SAI eDMA handle pointer.
 * param saiConfig sai configurations.
 */
void SAI_TransferTxSetConfigEDMA(I2S_Type *base, sai_edma_handle_t *handle, sai_transceiver_t *saiConfig)
{
    assert((handle != NULL) && (saiConfig != NULL));

    /* Configure the audio format to SAI registers */
    SAI_TxSetConfig(base, saiConfig);

#if defined(FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE) && FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE
    /* Allow multi-channel transfer only if FIFO Combine mode is enabled */
    assert(
        (saiConfig->channelNums <= 1U) ||
        ((saiConfig->channelNums > 1U) && ((saiConfig->fifo.fifoCombine == kSAI_FifoCombineModeEnabledOnWrite) ||
                                           (saiConfig->fifo.fifoCombine == kSAI_FifoCombineModeEnabledOnReadWrite))));
#endif

    /* Get the transfer size from format, this should be used in EDMA configuration */
    if (saiConfig->serialData.dataWordLength == 24U)
    {
        handle->bytesPerFrame = 4U;
    }
    else
    {
        handle->bytesPerFrame = saiConfig->serialData.dataWordLength / 8U;
    }
    /* Update the data channel SAI used */
    handle->channel     = saiConfig->startChannel;
    handle->channelMask = saiConfig->channelMask;
    handle->channelNums = saiConfig->channelNums;

    /* Clear the channel enable bits until do a send/receive */
    base->TCR3 &= ~I2S_TCR3_TCE_MASK;
#if defined(FSL_FEATURE_SAI_FIFO_COUNT) && (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    handle->count = (uint8_t)((uint32_t)FSL_FEATURE_SAI_FIFO_COUNT - saiConfig->fifo.fifoWatermark);
#else
    handle->count = 1U;
#endif /* FSL_FEATURE_SAI_FIFO_COUNT */
}

/*!
 * brief Configures the SAI Rx audio format.
 *
 * deprecated Do not use this function.  It has been superceded by ref SAI_TransferRxSetConfigEDMA
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred. This function also sets the eDMA parameter according to formatting requirements.
 *
 * param base SAI base pointer.
 * param handle SAI eDMA handle pointer.
 * param format Pointer to SAI audio data format structure.
 * param mclkSourceClockHz SAI master clock source frequency in Hz.
 * param bclkSourceClockHz SAI bit clock source frequency in Hz. If a bit clock source is the master
 * clock, this value should equal to masterClockHz in format.
 * retval kStatus_Success Audio format set successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 */
void SAI_TransferRxSetFormatEDMA(I2S_Type *base,
                                 sai_edma_handle_t *handle,
                                 sai_transfer_format_t *format,
                                 uint32_t mclkSourceClockHz,
                                 uint32_t bclkSourceClockHz)
{
    assert((handle != NULL) && (format != NULL));

    /* Configure the audio format to SAI registers */
    SAI_RxSetFormat(base, format, mclkSourceClockHz, bclkSourceClockHz);

    /* Get the transfer size from format, this should be used in EDMA configuration */
    if (format->bitWidth == 24U)
    {
        handle->bytesPerFrame = 4U;
    }
    else
    {
        handle->bytesPerFrame = (uint8_t)(format->bitWidth / 8U);
    }

    /* Update the data channel SAI used */
    handle->channel = format->channel;

    /* Clear the channel enable bits until do a send/receive */
    base->RCR3 &= ~I2S_RCR3_RCE_MASK;
#if defined(FSL_FEATURE_SAI_FIFO_COUNT) && (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    handle->count = format->watermark;
#else
    handle->count = 1U;
#endif /* FSL_FEATURE_SAI_FIFO_COUNT */
}

/*!
 * brief Configures the SAI Rx.
 *
 * note SAI eDMA supports data transfer in a multiple SAI channels if the FIFO Combine feature is supported.
 * To activate the multi-channel transfer enable SAI channels by filling the channelMask
 * of sai_transceiver_t with the corresponding values of _sai_channel_mask enum, enable the FIFO Combine
 * mode by assigning kSAI_FifoCombineModeEnabledOnRead to the fifoCombine member of sai_fifo_combine_t
 * which is a member of sai_transceiver_t.
 * This is an example of multi-channel data transfer configuration step.
 *  code
 *   sai_transceiver_t config;
 *   SAI_GetClassicI2SConfig(&config, kSAI_WordWidth16bits, kSAI_Stereo, kSAI_Channel0Mask|kSAI_Channel1Mask);
 *   config.fifo.fifoCombine = kSAI_FifoCombineModeEnabledOnRead;
 *   SAI_TransferRxSetConfigEDMA(I2S0, &edmaHandle, &config);
 *  endcode
 * param base SAI base pointer.
 * param handle SAI eDMA handle pointer.
 * param saiConfig sai configurations.
 */
void SAI_TransferRxSetConfigEDMA(I2S_Type *base, sai_edma_handle_t *handle, sai_transceiver_t *saiConfig)
{
    assert((handle != NULL) && (saiConfig != NULL));

    /* Configure the audio format to SAI registers */
    SAI_RxSetConfig(base, saiConfig);

#if defined(FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE) && FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE
    /* Allow multi-channel transfer only if FIFO Combine mode is enabled */
    assert(
        (saiConfig->channelNums <= 1U) ||
        ((saiConfig->channelNums > 1U) && ((saiConfig->fifo.fifoCombine == kSAI_FifoCombineModeEnabledOnRead) ||
                                           (saiConfig->fifo.fifoCombine == kSAI_FifoCombineModeEnabledOnReadWrite))));
#endif

    /* Get the transfer size from format, this should be used in EDMA configuration */
    if (saiConfig->serialData.dataWordLength == 24U)
    {
        handle->bytesPerFrame = 4U;
    }
    else
    {
        handle->bytesPerFrame = saiConfig->serialData.dataWordLength / 8U;
    }

    /* Update the data channel SAI used */
    handle->channel     = saiConfig->startChannel;
    handle->channelMask = saiConfig->channelMask;
    handle->channelNums = saiConfig->channelNums;
    /* Clear the channel enable bits until do a send/receive */
    base->RCR3 &= ~I2S_RCR3_RCE_MASK;
#if defined(FSL_FEATURE_SAI_FIFO_COUNT) && (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    handle->count = saiConfig->fifo.fifoWatermark;
#else
    handle->count = 1U;
#endif /* FSL_FEATURE_SAI_FIFO_COUNT */
}

/*!
 * brief Performs a non-blocking SAI transfer using DMA.
 *
 * note This interface returns immediately after the transfer initiates. Call
 * SAI_GetTransferStatus to poll the transfer status and check whether the SAI transfer is finished.
 *
 * This function support multi channel transfer,
 * 1. for the sai IP support fifo combine mode, application should enable the fifo combine mode, no limitation
 *    on channel numbers
 * 2. for the sai IP not support fifo combine mode, sai edma provide another solution which using
 *    EDMA modulo feature, but support 2 or 4 channels only.
 *
 * param base SAI base pointer.
 * param handle SAI eDMA handle pointer.
 * param xfer Pointer to the DMA transfer structure.
 * retval kStatus_Success Start a SAI eDMA send successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 * retval kStatus_TxBusy SAI is busy sending data.
 */
status_t SAI_TransferSendEDMA(I2S_Type *base, sai_edma_handle_t *handle, sai_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));

    edma_transfer_config_t config = {0};
    uint32_t destAddr             = SAI_TxGetDataRegisterAddress(base, handle->channel);
    uint32_t destOffset           = 0U;

    /* Check if input parameter invalid */
    if ((xfer->data == NULL) || (xfer->dataSize == 0U))
    {
        return kStatus_InvalidArgument;
    }

    if (handle->saiQueue[handle->queueUser].data != NULL)
    {
        return kStatus_SAI_QueueFull;
    }

    /* Change the state of handle */
    handle->state = (uint32_t)kSAI_Busy;

    /* Update the queue state */
    handle->transferSize[handle->queueUser]      = xfer->dataSize;
    handle->saiQueue[handle->queueUser].data     = xfer->data;
    handle->saiQueue[handle->queueUser].dataSize = xfer->dataSize;
    handle->queueUser                            = (handle->queueUser + 1U) % (uint8_t)SAI_XFER_QUEUE_SIZE;

#if !(defined(FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE) && FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE)
    if (handle->channelNums > 1U)
    {
        destOffset = sizeof(uint32_t);
    }
#endif

    /* Prepare edma configure */
    EDMA_PrepareTransferConfig(&config, xfer->data, (uint32_t)handle->bytesPerFrame, (int16_t)handle->bytesPerFrame,
                               (uint32_t *)destAddr, (uint32_t)handle->bytesPerFrame, (int16_t)destOffset,
                               (uint32_t)handle->count * handle->bytesPerFrame, xfer->dataSize);

    /* Store the initially configured eDMA minor byte transfer count into the SAI handle */
    handle->nbytes = handle->count * handle->bytesPerFrame;

    if (EDMA_SubmitTransfer(handle->dmaHandle, &config) != kStatus_Success)
    {
        return kStatus_SAI_QueueFull;
    }

#if !(defined(FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE) && FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE)
    if (handle->channelNums > 1U)
    {
        if ((handle->channelNums % 2U) != 0U)
        {
            return kStatus_InvalidArgument;
        }

        EDMA_SetModulo(handle->dmaHandle->base, handle->dmaHandle->channel, kEDMA_ModuloDisable,
                       SAI_CHANNEL_MAP_MODULO(handle->channelNums));
    }
#endif
    /* Start DMA transfer */
    EDMA_StartTransfer(handle->dmaHandle);

    /* Enable DMA enable bit */
    SAI_TxEnableDMA(base, kSAI_FIFORequestDMAEnable, true);

    /* Enable SAI Tx clock */
    SAI_TxEnable(base, true);

    /* Enable the channel FIFO */
    base->TCR3 |= I2S_TCR3_TCE(handle->channelMask);

    return kStatus_Success;
}

/*!
 * brief Performs a non-blocking SAI receive using eDMA.
 *
 * note This interface returns immediately after the transfer initiates. Call
 * the SAI_GetReceiveRemainingBytes to poll the transfer status and check whether the SAI transfer is finished.
 *
 * This function support multi channel transfer,
 * 1. for the sai IP support fifo combine mode, application should enable the fifo combine mode, no limitation
 *    on channel numbers
 * 2. for the sai IP not support fifo combine mode, sai edma provide another solution which using
 *    EDMA modulo feature, but support 2 or 4 channels only.
 *
 * param base SAI base pointer
 * param handle SAI eDMA handle pointer.
 * param xfer Pointer to DMA transfer structure.
 * retval kStatus_Success Start a SAI eDMA receive successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 * retval kStatus_RxBusy SAI is busy receiving data.
 */
status_t SAI_TransferReceiveEDMA(I2S_Type *base, sai_edma_handle_t *handle, sai_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));

    edma_transfer_config_t config = {0};
    uint32_t srcAddr              = SAI_RxGetDataRegisterAddress(base, handle->channel);
    uint32_t srcOffset            = 0U;

    /* Check if input parameter invalid */
    if ((xfer->data == NULL) || (xfer->dataSize == 0U))
    {
        return kStatus_InvalidArgument;
    }

    if (handle->saiQueue[handle->queueUser].data != NULL)
    {
        return kStatus_SAI_QueueFull;
    }

    /* Change the state of handle */
    handle->state = (uint32_t)kSAI_Busy;

    /* Update queue state  */
    handle->transferSize[handle->queueUser]      = xfer->dataSize;
    handle->saiQueue[handle->queueUser].data     = xfer->data;
    handle->saiQueue[handle->queueUser].dataSize = xfer->dataSize;
    handle->queueUser                            = (handle->queueUser + 1U) % (uint8_t)SAI_XFER_QUEUE_SIZE;

#if !(defined(FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE) && FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE)
    if (handle->channelNums > 1U)
    {
        srcOffset = sizeof(uint32_t);
    }
#endif

    /* Prepare edma configure */
    EDMA_PrepareTransferConfig(&config, (uint32_t *)srcAddr, (uint32_t)handle->bytesPerFrame, (int16_t)srcOffset,
                               xfer->data, (uint32_t)handle->bytesPerFrame, (int16_t)handle->bytesPerFrame,
                               (uint32_t)handle->count * handle->bytesPerFrame, xfer->dataSize);
    /* Store the initially configured eDMA minor byte transfer count into the SAI handle */
    handle->nbytes = handle->count * handle->bytesPerFrame;

    if (EDMA_SubmitTransfer(handle->dmaHandle, &config) != kStatus_Success)
    {
        return kStatus_SAI_QueueFull;
    }

#if !(defined(FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE) && FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE)
    if (handle->channelNums > 1U)
    {
        if ((handle->channelNums % 2U) != 0U)
        {
            return kStatus_InvalidArgument;
        }

        EDMA_SetModulo(handle->dmaHandle->base, handle->dmaHandle->channel, SAI_CHANNEL_MAP_MODULO(handle->channelNums),
                       kEDMA_ModuloDisable);
    }
#endif
    /* Start DMA transfer */
    EDMA_StartTransfer(handle->dmaHandle);

    /* Enable DMA enable bit */
    SAI_RxEnableDMA(base, kSAI_FIFORequestDMAEnable, true);

    /* Enable the channel FIFO */
    base->RCR3 |= I2S_RCR3_RCE(handle->channelMask);

    /* Enable SAI Rx clock */
    SAI_RxEnable(base, true);

    return kStatus_Success;
}

/*!
 * brief Performs a non-blocking SAI loop transfer using eDMA.
 *
 * note This function support loop transfer only,such as A->B->...->A, application must be aware of
 * that the more counts of the loop transfer, then more tcd memory required, as the function use the tcd pool in
 * sai_edma_handle_t, so application could redefine the SAI_XFER_QUEUE_SIZE to determine the proper TCD pool size.
 *
 * Once the loop transfer start, application can use function SAI_TransferAbortSendEDMA to stop the loop transfer.
 *
 * param base SAI base pointer.
 * param handle SAI eDMA handle pointer.
 * param xfer Pointer to the DMA transfer structure, should be a array with elements counts >=1(loopTransferCount).
 * param loopTransferCount the counts of xfer array.
 * retval kStatus_Success Start a SAI eDMA send successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 */
status_t SAI_TransferSendLoopEDMA(I2S_Type *base,
                                  sai_edma_handle_t *handle,
                                  sai_transfer_t *xfer,
                                  uint32_t loopTransferCount)
{
    assert((handle != NULL) && (xfer != NULL));

    edma_transfer_config_t config = {0};
    uint32_t destAddr             = SAI_TxGetDataRegisterAddress(base, handle->channel);
    sai_transfer_t *transfer      = xfer;
    edma_tcd_t *currentTCD        = STCD_ADDR(handle->tcd);
    uint32_t tcdIndex             = 0U;

    /* Change the state of handle */
    handle->state = (uint32_t)kSAI_Busy;

    for (uint32_t i = 0U; i < loopTransferCount; i++)
    {
        transfer = &xfer[i];

        if ((transfer->data == NULL) || (transfer->dataSize == 0U) || (tcdIndex >= (uint32_t)SAI_XFER_QUEUE_SIZE))
        {
            return kStatus_InvalidArgument;
        }

        /* Update the queue state */
        handle->transferSize[tcdIndex]      = transfer->dataSize;
        handle->saiQueue[tcdIndex].data     = transfer->data;
        handle->saiQueue[tcdIndex].dataSize = transfer->dataSize;

        /* Prepare edma configure */
        EDMA_PrepareTransfer(&config, transfer->data, handle->bytesPerFrame, (uint32_t *)destAddr,
                             handle->bytesPerFrame, (uint32_t)handle->count * handle->bytesPerFrame, transfer->dataSize,
                             kEDMA_MemoryToPeripheral);

        if (i == (loopTransferCount - 1U))
        {
            EDMA_TcdSetTransferConfig(&currentTCD[tcdIndex], &config, &currentTCD[0U]);
            EDMA_TcdEnableInterrupts(&currentTCD[tcdIndex], (uint32_t)kEDMA_MajorInterruptEnable);
            handle->state = (uint32_t)kSAI_BusyLoopTransfer;
            break;
        }
        else
        {
            EDMA_TcdSetTransferConfig(&currentTCD[tcdIndex], &config, &currentTCD[tcdIndex + 1U]);
            EDMA_TcdEnableInterrupts(&currentTCD[tcdIndex], (uint32_t)kEDMA_MajorInterruptEnable);
        }

        tcdIndex = tcdIndex + 1U;
    }

    EDMA_InstallTCD(handle->dmaHandle->base, handle->dmaHandle->channel, &currentTCD[0]);
    /* Start DMA transfer */
    EDMA_StartTransfer(handle->dmaHandle);

    /* Enable DMA enable bit */
    SAI_TxEnableDMA(base, kSAI_FIFORequestDMAEnable, true);

    /* Enable SAI Tx clock */
    SAI_TxEnable(base, true);

    /* Enable the channel FIFO */
    base->TCR3 |= I2S_TCR3_TCE(1UL << handle->channel);

    return kStatus_Success;
}

/*!
 * brief Performs a non-blocking SAI loop transfer using eDMA.
 *
 * note This function support loop transfer only,such as A->B->...->A, application must be aware of
 * that the more counts of the loop transfer, then more tcd memory required, as the function use the tcd pool in
 * sai_edma_handle_t, so application could redefine the SAI_XFER_QUEUE_SIZE to determine the proper TCD pool size.
 *
 * Once the loop transfer start, application can use function SAI_TransferAbortReceiveEDMA to stop the loop transfer.
 *
 * param base SAI base pointer.
 * param handle SAI eDMA handle pointer.
 * param xfer Pointer to the DMA transfer structure, should be a array with elements counts >=1(loopTransferCount).
 * param loopTransferCount the counts of xfer array.
 * retval kStatus_Success Start a SAI eDMA receive successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 */
status_t SAI_TransferReceiveLoopEDMA(I2S_Type *base,
                                     sai_edma_handle_t *handle,
                                     sai_transfer_t *xfer,
                                     uint32_t loopTransferCount)
{
    assert((handle != NULL) && (xfer != NULL));

    edma_transfer_config_t config = {0};
    uint32_t srcAddr              = SAI_RxGetDataRegisterAddress(base, handle->channel);
    sai_transfer_t *transfer      = xfer;
    edma_tcd_t *currentTCD        = STCD_ADDR(handle->tcd);
    uint32_t tcdIndex             = 0U;

    /* Change the state of handle */
    handle->state = (uint32_t)kSAI_Busy;

    for (uint32_t i = 0U; i < loopTransferCount; i++)
    {
        transfer = &xfer[i];

        if ((tcdIndex >= (uint32_t)SAI_XFER_QUEUE_SIZE) || (xfer->data == NULL) || (xfer->dataSize == 0U))
        {
            return kStatus_InvalidArgument;
        }

        /* Update the queue state */
        handle->transferSize[tcdIndex]      = transfer->dataSize;
        handle->saiQueue[tcdIndex].data     = transfer->data;
        handle->saiQueue[tcdIndex].dataSize = transfer->dataSize;

        /* Prepare edma configure */
        EDMA_PrepareTransfer(&config, (uint32_t *)srcAddr, handle->bytesPerFrame, transfer->data, handle->bytesPerFrame,
                             (uint32_t)handle->count * handle->bytesPerFrame, transfer->dataSize,
                             kEDMA_PeripheralToMemory);

        if (i == (loopTransferCount - 1U))
        {
            EDMA_TcdSetTransferConfig(&currentTCD[tcdIndex], &config, &currentTCD[0U]);
            EDMA_TcdEnableInterrupts(&currentTCD[tcdIndex], (uint32_t)kEDMA_MajorInterruptEnable);
            handle->state = (uint32_t)kSAI_BusyLoopTransfer;
            break;
        }
        else
        {
            EDMA_TcdSetTransferConfig(&currentTCD[tcdIndex], &config, &currentTCD[tcdIndex + 1U]);
            EDMA_TcdEnableInterrupts(&currentTCD[tcdIndex], (uint32_t)kEDMA_MajorInterruptEnable);
        }

        tcdIndex = tcdIndex + 1U;
    }

    EDMA_InstallTCD(handle->dmaHandle->base, handle->dmaHandle->channel, &currentTCD[0]);
    /* Start DMA transfer */
    EDMA_StartTransfer(handle->dmaHandle);
    /* Enable DMA enable bit */
    SAI_RxEnableDMA(base, kSAI_FIFORequestDMAEnable, true);

    /* Enable the channel FIFO */
    base->RCR3 |= I2S_RCR3_RCE(1UL << handle->channel);

    /* Enable SAI Rx clock */
    SAI_RxEnable(base, true);

    return kStatus_Success;
}

/*!
 * brief Aborts a SAI transfer using eDMA.
 *
 * This function only aborts the current transfer slots, the other transfer slots' information still kept
 * in the handler. If users want to terminate all transfer slots, just call SAI_TransferTerminateSendEDMA.
 *
 * param base SAI base pointer.
 * param handle SAI eDMA handle pointer.
 */
void SAI_TransferAbortSendEDMA(I2S_Type *base, sai_edma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    EDMA_AbortTransfer(handle->dmaHandle);

    /* Disable the channel FIFO */
    base->TCR3 &= ~I2S_TCR3_TCE_MASK;

    /* Disable DMA enable bit */
    SAI_TxEnableDMA(base, kSAI_FIFORequestDMAEnable, false);

    /* Disable Tx */
    SAI_TxEnable(base, false);

    /* If Tx is disabled, reset the FIFO pointer and clear error flags */
    if ((base->TCSR & I2S_TCSR_TE_MASK) == 0UL)
    {
        base->TCSR |= (I2S_TCSR_FR_MASK | I2S_TCSR_SR_MASK);
        base->TCSR &= ~I2S_TCSR_SR_MASK;
    }

    /* Handle the queue index */
    (void)memset(&handle->saiQueue[handle->queueDriver], 0, sizeof(sai_transfer_t));
    handle->queueDriver = (handle->queueDriver + 1U) % (uint8_t)SAI_XFER_QUEUE_SIZE;

    /* Set the handle state */
    handle->state = (uint32_t)kSAI_Idle;
}

/*!
 * brief Aborts a SAI receive using eDMA.
 *
 * This function only aborts the current transfer slots, the other transfer slots' information still kept
 * in the handler. If users want to terminate all transfer slots, just call SAI_TransferTerminateReceiveEDMA.
 *
 * param base SAI base pointer.
 * param handle SAI eDMA handle pointer.
 */
void SAI_TransferAbortReceiveEDMA(I2S_Type *base, sai_edma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    EDMA_AbortTransfer(handle->dmaHandle);

    /* Disable the channel FIFO */
    base->RCR3 &= ~I2S_RCR3_RCE_MASK;

    /* Disable DMA enable bit */
    SAI_RxEnableDMA(base, kSAI_FIFORequestDMAEnable, false);

    /* Disable Rx */
    SAI_RxEnable(base, false);

    /* If Rx is disabled, reset the FIFO pointer and clear error flags */
    if ((base->RCSR & I2S_RCSR_RE_MASK) == 0UL)
    {
        base->RCSR |= (I2S_RCSR_FR_MASK | I2S_RCSR_SR_MASK);
        base->RCSR &= ~I2S_RCSR_SR_MASK;
    }

    /* Handle the queue index */
    (void)memset(&handle->saiQueue[handle->queueDriver], 0, sizeof(sai_transfer_t));
    handle->queueDriver = (handle->queueDriver + 1U) % (uint8_t)SAI_XFER_QUEUE_SIZE;

    /* Set the handle state */
    handle->state = (uint32_t)kSAI_Idle;
}

/*!
 * brief Terminate all SAI send.
 *
 * This function will clear all transfer slots buffered in the sai queue. If users only want to abort the
 * current transfer slot, please call SAI_TransferAbortSendEDMA.
 *
 * param base SAI base pointer.
 * param handle SAI eDMA handle pointer.
 */
void SAI_TransferTerminateSendEDMA(I2S_Type *base, sai_edma_handle_t *handle)
{
    assert(handle != NULL);

    /* Abort the current transfer */
    SAI_TransferAbortSendEDMA(base, handle);

    /* Clear all the internal information */
    (void)memset(handle->tcd, 0, sizeof(handle->tcd));
    (void)memset(handle->saiQueue, 0, sizeof(handle->saiQueue));
    (void)memset(handle->transferSize, 0, sizeof(handle->transferSize));

    handle->queueUser   = 0U;
    handle->queueDriver = 0U;
}

/*!
 * brief Terminate all SAI receive.
 *
 * This function will clear all transfer slots buffered in the sai queue. If users only want to abort the
 * current transfer slot, please call SAI_TransferAbortReceiveEDMA.
 *
 * param base SAI base pointer.
 * param handle SAI eDMA handle pointer.
 */
void SAI_TransferTerminateReceiveEDMA(I2S_Type *base, sai_edma_handle_t *handle)
{
    assert(handle != NULL);

    /* Abort the current transfer */
    SAI_TransferAbortReceiveEDMA(base, handle);

    /* Clear all the internal information */
    (void)memset(handle->tcd, 0, sizeof(handle->tcd));
    (void)memset(handle->saiQueue, 0, sizeof(handle->saiQueue));
    (void)memset(handle->transferSize, 0, sizeof(handle->transferSize));

    handle->queueUser   = 0U;
    handle->queueDriver = 0U;
}

/*!
 * brief Gets byte count sent by SAI.
 *
 * param base SAI base pointer.
 * param handle SAI eDMA handle pointer.
 * param count Bytes count sent by SAI.
 * retval kStatus_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is no non-blocking transaction in progress.
 */
status_t SAI_TransferGetSendCountEDMA(I2S_Type *base, sai_edma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kSAI_Busy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = (handle->transferSize[handle->queueDriver] -
                  (uint32_t)handle->nbytes *
                      EDMA_GetRemainingMajorLoopCount(handle->dmaHandle->base, handle->dmaHandle->channel));
    }

    return status;
}

/*!
 * brief Gets byte count received by SAI.
 *
 * param base SAI base pointer
 * param handle SAI eDMA handle pointer.
 * param count Bytes count received by SAI.
 * retval kStatus_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is no non-blocking transaction in progress.
 */
status_t SAI_TransferGetReceiveCountEDMA(I2S_Type *base, sai_edma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kSAI_Busy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = (handle->transferSize[handle->queueDriver] -
                  (uint32_t)handle->nbytes *
                      EDMA_GetRemainingMajorLoopCount(handle->dmaHandle->base, handle->dmaHandle->channel));
    }

    return status;
}

/*!
 * @rief Gets valid transfer slot.
 *
 * This function can be used to query the valid transfer request slot that the application can submit.
 * It should be called in the critical section, that means the application could call it in the corresponding callback
 * function or disable IRQ before calling it in the application, otherwise, the returned value may not correct.
 *
 * param base SAI base pointer
 * param handle SAI eDMA handle pointer.
 * retval valid slot count that application submit.
 */
uint32_t SAI_TransferGetValidTransferSlotsEDMA(I2S_Type *base, sai_edma_handle_t *handle)
{
    uint32_t validSlot = 0U;

    for (uint32_t i = 0U; i < (uint32_t)SAI_XFER_QUEUE_SIZE; i++)
    {
        if (handle->saiQueue[i].data == NULL)
        {
            validSlot++;
        }
    }

    return validSlot;
}
