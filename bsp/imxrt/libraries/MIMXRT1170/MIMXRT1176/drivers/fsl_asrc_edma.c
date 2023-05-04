/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_asrc_edma.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.asrc_edma"
#endif

/*******************************************************************************
 * Definitations
 ******************************************************************************/
/* Used for 32byte aligned */
#define STCD_ADDR(address) (edma_tcd_t *)(((uint32_t)(address) + 32U) & ~0x1FU)

/*<! Structure definition for uart_edma_private_handle_t. The structure is private. */
typedef struct _asrc_edma_private_handle
{
    ASRC_Type *base;
    asrc_edma_handle_t *handle;
} asrc_edma_private_handle_t;

/*<! Private handle only used for internally. */
static asrc_edma_private_handle_t s_edmaPrivateHandle[FSL_FEATURE_SOC_ASRC_COUNT][FSL_ASRC_CHANNEL_PAIR_COUNT];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief ASRC EDMA callback for input.
 *
 * @param handle pointer to asrc_edma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 * @param done If the DMA transfer finished.
 * @param tcds The TCD index.
 */
static void ASRC_InEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds);

/*!
 * @brief ASRC EDMA callback for output.
 *
 * @param handle pointer to asrc_edma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 * @param done If the DMA transfer finished.
 * @param tcds The TCD index.
 */
static void ASRC_OutEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds);
/*******************************************************************************
 * Code
 ******************************************************************************/
static void ASRC_InEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds)
{
    asrc_edma_private_handle_t *privHandle = (asrc_edma_private_handle_t *)userData;
    asrc_edma_handle_t *asrcHandle         = privHandle->handle;
    asrc_in_edma_handle_t *asrcInHandle    = &(privHandle->handle->in);
    status_t inStatus                      = kStatus_ASRCInIdle;
    /* If finished a block, call the callback function */
    asrcInHandle->asrcQueue[asrcInHandle->queueDriver] = NULL;
    asrcInHandle->queueDriver                          = (asrcInHandle->queueDriver + 1U) % ASRC_XFER_QUEUE_SIZE;

    /* If all data finished, just stop the transfer */
    if (asrcInHandle->asrcQueue[asrcInHandle->queueDriver] == NULL)
    {
        EDMA_AbortTransfer(asrcInHandle->inDmaHandle);
        inStatus = kStatus_ASRCInQueueIdle;
    }

    if (asrcHandle->callback != NULL)
    {
        (asrcHandle->callback)(privHandle->base, asrcHandle, inStatus, asrcHandle->userData);
    }
}

static void ASRC_OutEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds)
{
    asrc_edma_private_handle_t *privHandle = (asrc_edma_private_handle_t *)userData;
    asrc_edma_handle_t *asrcHandle         = privHandle->handle;
    asrc_out_edma_handle_t *asrcOutHandle  = &(privHandle->handle->out);
    uint32_t queueDriverIndex              = asrcOutHandle->queueDriver;
    status_t callbackStatus                = kStatus_ASRCOutIdle;

    /* If finished a block, call the callback function */
    asrcOutHandle->asrcQueue[queueDriverIndex] = NULL;
    asrcOutHandle->queueDriver                 = (uint8_t)((queueDriverIndex + 1U) % ASRC_XFER_OUT_QUEUE_SIZE);

    /* If all data finished, just stop the transfer */
    if (asrcOutHandle->asrcQueue[asrcOutHandle->queueDriver] == NULL)
    {
        EDMA_AbortTransfer(asrcOutHandle->outDmaHandle);
        callbackStatus = kStatus_ASRCOutQueueIdle;
    }

    if (asrcHandle->callback != NULL)
    {
        (asrcHandle->callback)(privHandle->base, asrcHandle, callbackStatus, asrcHandle->userData);
    }
}
/*!
 * brief Initializes the ASRC IN eDMA handle.
 *
 * This function initializes the ASRC DMA handle, which can be used for other ASRC transactional APIs.
 * Usually, for a specified ASRC channel pair, call this API once to get the initialized handle.
 *
 * param base ASRC base pointer.
 * param channelPair ASRC channel pair
 * param handle ASRC eDMA handle pointer.
 * param callback Pointer to user callback function.
 * param txDmaHandle ASRC send edma handle pointer.
 * param periphConfig peripheral configuration.
 * param userData User parameter passed to the callback function.
 */
void ASRC_TransferInCreateHandleEDMA(ASRC_Type *base,
                                     asrc_edma_handle_t *handle,
                                     asrc_channel_pair_t channelPair,
                                     asrc_edma_callback_t callback,
                                     edma_handle_t *inDmaHandle,
                                     const asrc_p2p_edma_config_t *periphConfig,
                                     void *userData)
{
    assert((handle != NULL) && (inDmaHandle != NULL));

    uint32_t instance = ASRC_GetInstance(base);

    /* Zero the handle */
    (void)memset(&handle->in, 0, sizeof(asrc_in_edma_handle_t));

    handle->in.inDmaHandle = inDmaHandle;
    handle->callback       = callback;
    handle->userData       = userData;

    /* Set ASRC state to idle */
    handle->in.state            = kStatus_ASRCIdle;
    handle->channelPair         = channelPair;
    handle->in.peripheralConfig = periphConfig;

    s_edmaPrivateHandle[instance][channelPair].base   = base;
    s_edmaPrivateHandle[instance][channelPair].handle = handle;

    /* Need to use scatter gather */
    EDMA_InstallTCDMemory(inDmaHandle, (edma_tcd_t *)(STCD_ADDR(handle->in.tcd)), ASRC_XFER_OUT_QUEUE_SIZE);
    /* Install callback for Tx dma channel */
    EDMA_SetCallback(inDmaHandle, ASRC_InEDMACallback, &s_edmaPrivateHandle[instance][channelPair]);
}

/*!
 * brief Initializes the ASRC OUT eDMA handle.
 *
 * This function initializes the ASRC DMA handle, which can be used for other ASRC transactional APIs.
 * Usually, for a specified ASRC channel pair, call this API once to get the initialized handle.
 *
 * param base ASRC base pointer.
 * param channelPair ASRC channel pair
 * param handle ASRC eDMA handle pointer.
 * param callback Pointer to user callback function.
 * param txDmaHandle ASRC send edma handle pointer.
 * param periphConfig peripheral configuration.
 * param userData User parameter passed to the callback function.
 */
void ASRC_TransferOutCreateHandleEDMA(ASRC_Type *base,
                                      asrc_edma_handle_t *handle,
                                      asrc_channel_pair_t channelPair,
                                      asrc_edma_callback_t callback,
                                      edma_handle_t *outDmaHandle,
                                      const asrc_p2p_edma_config_t *periphConfig,
                                      void *userData)
{
    assert((handle != NULL) && (NULL != outDmaHandle));

    uint32_t instance = ASRC_GetInstance(base);

    /* Zero the handle */
    (void)memset(&handle->out, 0, sizeof(asrc_out_edma_handle_t));

    handle->out.outDmaHandle = outDmaHandle;
    handle->callback         = callback;
    handle->userData         = userData;

    /* Set ASRC state to idle */
    handle->out.state            = kStatus_ASRCIdle;
    handle->channelPair          = channelPair;
    handle->out.peripheralConfig = periphConfig;

    s_edmaPrivateHandle[instance][channelPair].base   = base;
    s_edmaPrivateHandle[instance][channelPair].handle = handle;

    /* Need to use scatter gather */
    EDMA_InstallTCDMemory(outDmaHandle, (edma_tcd_t *)(STCD_ADDR(handle->out.tcd)), ASRC_XFER_OUT_QUEUE_SIZE);
    /* Install callback for Tx dma channel */
    EDMA_SetCallback(outDmaHandle, ASRC_OutEDMACallback, &s_edmaPrivateHandle[instance][channelPair]);
}

/*!
 * brief Configures the ASRC channel pair.
 *
 * param base ASRC base pointer.
 * param handle ASRC eDMA handle pointer.
 * param asrcConfig asrc configurations.
 * param periphConfig peripheral configuration.
 * param inputSampleRate ASRC input sample rate.
 * param outputSampleRate ASRC output sample rate.
 */
status_t ASRC_TransferSetChannelPairConfigEDMA(ASRC_Type *base,
                                               asrc_edma_handle_t *handle,
                                               asrc_channel_pair_config_t *asrcConfig,
                                               uint32_t inSampleRate,
                                               uint32_t outSampleRate)
{
    assert((handle != NULL) && (NULL != asrcConfig));

    /* Configure the audio format to ASRC registers */
    if (ASRC_SetChannelPairConfig(base, handle->channelPair, asrcConfig, inSampleRate, outSampleRate) !=
        kStatus_Success)
    {
        return kStatus_ASRCChannelPairConfigureFailed;
    }
    handle->in.fifoThreshold  = (asrcConfig->inFifoThreshold) * (uint32_t)asrcConfig->audioDataChannels;
    handle->out.fifoThreshold = (asrcConfig->outFifoThreshold) * (uint32_t)asrcConfig->audioDataChannels;
    (void)ASRC_MapSamplesWidth(base, handle->channelPair, &handle->in.sampleWidth, &handle->out.sampleWidth);

    return kStatus_Success;
}

/*!
 * brief Get output sample buffer size can be transferred by edma.
 *
 * note This API is depends on the ASRC output configuration, should be called after the
 * ASRC_TransferSetChannelPairConfigEDMA.
 *
 * param base asrc base pointer.
 * param handle ASRC channel pair edma handle.
 * param inSampleRate input sample rate.
 * param outSampleRate output sample rate.
 * param inSamples input sampleS size.
 * retval output buffer size in byte.
 */
uint32_t ASRC_GetOutSamplesSizeEDMA(
    ASRC_Type *base, asrc_edma_handle_t *handle, uint32_t inSampleRate, uint32_t outSampleRate, uint32_t inSamplesize)
{
    uint32_t outputSize = ASRC_GetOutSamplesSize(base, handle->channelPair, inSampleRate, outSampleRate, inSamplesize);

    return outputSize - outputSize % handle->out.fifoThreshold;
}

static status_t ASRC_TransferOutSubmitEDMA(ASRC_Type *base,
                                           asrc_edma_handle_t *handle,
                                           uint32_t *outDataAddr,
                                           uint32_t outDataSize)
{
    assert(outDataAddr != NULL);
    assert(outDataSize != 0U);

    uint32_t outAddr              = ASRC_GetOutputDataRegisterAddress(base, handle->channelPair);
    edma_transfer_config_t config = {0};
    edma_transfer_type_t type     = kEDMA_PeripheralToMemory;

    if (handle->out.asrcQueue[handle->out.queueUser] != NULL)
    {
        return kStatus_ASRCQueueFull;
    }

    if (handle->out.peripheralConfig != NULL)
    {
        type = kEDMA_PeripheralToPeripheral;
    }

    if (handle->out.asrcQueue[handle->out.queueUser] != NULL)
    {
        return kStatus_ASRCQueueFull;
    }

    handle->out.asrcQueue[handle->out.queueUser]    = outDataAddr;
    handle->out.transferSize[handle->out.queueUser] = outDataSize;
    handle->out.queueUser                           = (handle->out.queueUser + 1U) % ASRC_XFER_OUT_QUEUE_SIZE;
    /* Prepare ASRC output edma configuration */
    EDMA_PrepareTransfer(&config, (uint32_t *)outAddr, handle->out.sampleWidth, outDataAddr, handle->out.sampleWidth,
                         handle->out.fifoThreshold * handle->out.sampleWidth, outDataSize, type);

    if (handle->out.state != (uint32_t)kStatus_ASRCBusy)
    {
        (void)EDMA_SubmitTransfer(handle->out.outDmaHandle, &config);

        EDMA_StartTransfer(handle->out.outDmaHandle);

        if ((handle->out.peripheralConfig != NULL) && (handle->out.peripheralConfig->startPeripheral != NULL))
        {
            handle->out.peripheralConfig->startPeripheral(true);
        }
    }

    return kStatus_Success;
}

static status_t ASRC_TransferInSubmitEDMA(ASRC_Type *base,
                                          asrc_edma_handle_t *handle,
                                          uint32_t *inDataAddr,
                                          uint32_t inDataSize)
{
    assert(inDataAddr != NULL);
    assert(inDataSize != 0U);

    uint32_t inAddr               = ASRC_GetInputDataRegisterAddress(base, handle->channelPair);
    edma_transfer_config_t config = {0};

    if (handle->in.asrcQueue[handle->in.queueUser] != NULL)
    {
        return kStatus_ASRCQueueFull;
    }

    /* Add into queue */
    handle->in.asrcQueue[handle->in.queueUser]    = inDataAddr;
    handle->in.transferSize[handle->in.queueUser] = inDataSize;
    handle->in.queueUser                          = (handle->in.queueUser + 1U) % ASRC_XFER_IN_QUEUE_SIZE;

    /* Prepare ASRC input edma configuration */
    EDMA_PrepareTransfer(&config, (uint32_t *)inDataAddr, handle->in.sampleWidth, (uint32_t *)inAddr,
                         handle->in.sampleWidth, handle->in.fifoThreshold * handle->in.sampleWidth, inDataSize,
                         handle->in.peripheralConfig == NULL ? kEDMA_MemoryToPeripheral : kEDMA_PeripheralToPeripheral);

    if (handle->in.state != (uint32_t)kStatus_ASRCBusy)
    {
        (void)EDMA_SubmitTransfer(handle->in.inDmaHandle, &config);
        EDMA_StartTransfer(handle->in.inDmaHandle);
        /* start peripheral */
        if ((handle->in.peripheralConfig != NULL) && (handle->in.peripheralConfig->startPeripheral != NULL))
        {
            handle->in.peripheralConfig->startPeripheral(true);
        }
    }

    return kStatus_Success;
}

/*!
 * brief Performs a non-blocking ASRC convert using EDMA.
 *
 * note This interface returns immediately after the transfer initiates.

 * param base ASRC base pointer.
 * param handle ASRC eDMA handle pointer.
 * param xfer Pointer to the DMA transfer structure.
 * retval kStatus_Success Start a ASRC eDMA send successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 * retval kStatus_ASRCQueueFull ASRC EDMA driver queue is full.
 */
status_t ASRC_TransferEDMA(ASRC_Type *base, asrc_edma_handle_t *handle, asrc_transfer_t *xfer)
{
    assert(handle != NULL);

    if (ASRC_TransferOutSubmitEDMA(base, handle, xfer->outData, xfer->outDataSize) != kStatus_Success)
    {
        return kStatus_ASRCQueueFull;
    }

    if (ASRC_TransferInSubmitEDMA(base, handle, xfer->inData, xfer->inDataSize) != kStatus_Success)
    {
        return kStatus_ASRCQueueFull;
    }

    return kStatus_Success;
}

/*!
 * brief Aborts a ASRC IN transfer using eDMA.
 *
 * This function only aborts the current transfer slots, the other transfer slots' information still kept
 * in the handler. If users want to terminate all transfer slots, just call ASRC_TransferTerminalP2PEDMA.
 *
 * param base ASRC base pointer.
 * param handle ASRC eDMA handle pointer.
 */
void ASRC_TransferInAbortEDMA(ASRC_Type *base, asrc_edma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    EDMA_AbortTransfer(handle->in.inDmaHandle);

    /* Handle the queue index */
    handle->in.asrcQueue[handle->in.queueDriver] = NULL;
    handle->in.queueDriver                       = (handle->in.queueDriver + 1U) % ASRC_XFER_QUEUE_SIZE;

    /* Set the handle state */
    handle->in.state = kStatus_ASRCIdle;
}

/*!
 * brief Aborts a ASRC OUT transfer using eDMA.
 *
 * This function only aborts the current transfer slots, the other transfer slots' information still kept
 * in the handler. If users want to terminate all transfer slots, just call ASRC_TransferTerminalP2PEDMA.
 *
 * param base ASRC base pointer.
 * param handle ASRC eDMA handle pointer.
 */
void ASRC_TransferOutAbortEDMA(ASRC_Type *base, asrc_edma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    EDMA_AbortTransfer(handle->out.outDmaHandle);

    /* Handle the queue index */
    handle->out.asrcQueue[handle->out.queueDriver] = NULL;
    handle->out.queueDriver                        = (handle->out.queueDriver + 1U) % ASRC_XFER_QUEUE_SIZE;

    /* Set the handle state */
    handle->out.state = kStatus_ASRCIdle;
}

/*!
 * brief Terminate In ASRC Convert.
 *
 * This function will clear all transfer slots buffered in the asrc queue. If users only want to abort the
 * current transfer slot, please call ASRC_TransferAbortPP2PEDMA.
 *
 * param base ASRC base pointer.
 * param handle ASRC eDMA handle pointer.
 */
void ASRC_TransferInTerminalEDMA(ASRC_Type *base, asrc_edma_handle_t *handle)
{
    assert(handle != NULL);

    /* Abort the current transfer */
    ASRC_TransferInAbortEDMA(base, handle);
    /* stop peripheral */
    if ((handle->in.peripheralConfig != NULL) && (handle->in.peripheralConfig->startPeripheral != NULL))
    {
        handle->in.peripheralConfig->startPeripheral(false);
    }

    /* Clear all the internal information */
    (void)memset(handle->in.tcd, 0, sizeof(handle->in.tcd));
    (void)memset(handle->in.asrcQueue, 0, sizeof(handle->in.asrcQueue));
    (void)memset(handle->in.transferSize, 0, sizeof(handle->in.transferSize));
    handle->in.queueUser   = 0U;
    handle->in.queueDriver = 0U;
}

/*!
 * brief Terminate Out ASRC Convert.
 *
 * This function will clear all transfer slots buffered in the asrc queue. If users only want to abort the
 * current transfer slot, please call ASRC_TransferAbortPP2PEDMA.
 *
 * param base ASRC base pointer.
 * param handle ASRC eDMA handle pointer.
 */
void ASRC_TransferOutTerminalEDMA(ASRC_Type *base, asrc_edma_handle_t *handle)
{
    assert(handle != NULL);

    /* Abort the current transfer */
    ASRC_TransferOutAbortEDMA(base, handle);

    if ((handle->out.peripheralConfig != NULL) && (handle->out.peripheralConfig->startPeripheral != NULL))
    {
        handle->out.peripheralConfig->startPeripheral(false);
    }

    (void)memset(handle->out.tcd, 0, sizeof(handle->out.tcd));
    (void)memset(handle->out.asrcQueue, 0, sizeof(handle->out.asrcQueue));
    (void)memset(handle->out.transferSize, 0, sizeof(handle->out.transferSize));
    handle->out.queueUser   = 0U;
    handle->out.queueDriver = 0U;
}
