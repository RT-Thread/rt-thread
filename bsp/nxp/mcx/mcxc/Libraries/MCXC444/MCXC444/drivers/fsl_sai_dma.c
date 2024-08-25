/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017,2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sai_dma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.sai_dma"
#endif

/*<! Structure definition for sai_dma_private_handle_t. The structure is private. */
typedef struct _sai_dma_private_handle
{
    I2S_Type *base;
    sai_dma_handle_t *handle;
} sai_dma_private_handle_t;

/*!@brief _sai_dma_states */
enum
{
    kSAI_Idle = 0x0U,
    kSAI_Busy = 0x1U,
};

static I2S_Type *const s_saiBases[] = I2S_BASE_PTRS;

/*<! Private handle only used for internally. */
static sai_dma_private_handle_t s_dmaPrivateHandle[ARRAY_SIZE(s_saiBases)][2];

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
 * @param handle pointer to sai_dma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 */
static void SAI_TxDMACallback(dma_handle_t *handle, void *userData);

/*!
 * @brief SAI EDMA callback for receive.
 *
 * @param handle pointer to sai_dma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 */
static void SAI_RxDMACallback(dma_handle_t *handle, void *userData);

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

static void SAI_TxDMACallback(dma_handle_t *handle, void *userData)
{
    sai_dma_private_handle_t *privHandle = (sai_dma_private_handle_t *)userData;
    sai_dma_handle_t *saiHandle          = privHandle->handle;

    /* Update queue counter */
    (void)memset(&saiHandle->saiQueue[saiHandle->queueDriver], 0, sizeof(sai_transfer_t));
    saiHandle->queueDriver = (saiHandle->queueDriver + 1U) % SAI_XFER_QUEUE_SIZE;

    /* Call callback function */
    if (saiHandle->callback != NULL)
    {
        (saiHandle->callback)(privHandle->base, saiHandle, kStatus_SAI_TxIdle, saiHandle->userData);
    }

    /* If all data finished, just stop the transfer */
    if (saiHandle->saiQueue[saiHandle->queueDriver].data == NULL)
    {
        SAI_TransferAbortSendDMA(privHandle->base, saiHandle);
    }
}

static void SAI_RxDMACallback(dma_handle_t *handle, void *userData)
{
    sai_dma_private_handle_t *privHandle = (sai_dma_private_handle_t *)userData;
    sai_dma_handle_t *saiHandle          = privHandle->handle;

    /* Update queue counter */
    (void)memset(&saiHandle->saiQueue[saiHandle->queueDriver], 0, sizeof(sai_transfer_t));
    saiHandle->queueDriver = (saiHandle->queueDriver + 1U) % SAI_XFER_QUEUE_SIZE;

    /* Call callback function */
    if (saiHandle->callback != NULL)
    {
        (saiHandle->callback)(privHandle->base, saiHandle, kStatus_SAI_RxIdle, saiHandle->userData);
    }

    /* If all data finished, just stop the transfer */
    if (saiHandle->saiQueue[saiHandle->queueDriver].data == NULL)
    {
        SAI_TransferAbortReceiveDMA(privHandle->base, saiHandle);
    }
}

/*!
 * brief Initializes the SAI master DMA handle.
 *
 * This function initializes the SAI master DMA handle, which can be used for other SAI master transactional APIs.
 * Usually, for a specified SAI instance, call this API once to get the initialized handle.
 *
 * param base SAI base pointer.
 * param handle SAI DMA handle pointer.
 * param base SAI peripheral base address.
 * param callback Pointer to user callback function.
 * param userData User parameter passed to the callback function.
 * param dmaHandle DMA handle pointer, this handle shall be static allocated by users.
 */
void SAI_TransferTxCreateHandleDMA(
    I2S_Type *base, sai_dma_handle_t *handle, sai_dma_callback_t callback, void *userData, dma_handle_t *dmaHandle)
{
    assert((handle != NULL) && (dmaHandle != NULL));

    uint32_t instance = SAI_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set sai base to handle */
    handle->dmaHandle = dmaHandle;
    handle->callback  = callback;
    handle->userData  = userData;

    /* Set SAI state to idle */
    handle->state = (uint32_t)kSAI_Idle;

    s_dmaPrivateHandle[instance][0].base   = base;
    s_dmaPrivateHandle[instance][0].handle = handle;

/* Use FIFO error continue nstead of using interrupt to handle error */
#if defined(FSL_FEATURE_SAI_HAS_FIFO_FUNCTION_AFTER_ERROR) && (FSL_FEATURE_SAI_HAS_FIFO_FUNCTION_AFTER_ERROR)
    base->TCR4 |= I2S_TCR4_FCONT_MASK;
#endif

    /* Install callback for Tx dma channel */
    DMA_SetCallback(dmaHandle, SAI_TxDMACallback, &s_dmaPrivateHandle[instance][0]);
}

/*!
 * brief Initializes the SAI slave DMA handle.
 *
 * This function initializes the SAI slave DMA handle, which can be used for other SAI master transactional APIs.
 * Usually, for a specified SAI instance, call this API once to get the initialized handle.
 *
 * param base SAI base pointer.
 * param handle SAI DMA handle pointer.
 * param base SAI peripheral base address.
 * param callback Pointer to user callback function.
 * param userData User parameter passed to the callback function.
 * param dmaHandle DMA handle pointer, this handle shall be static allocated by users.
 */
void SAI_TransferRxCreateHandleDMA(
    I2S_Type *base, sai_dma_handle_t *handle, sai_dma_callback_t callback, void *userData, dma_handle_t *dmaHandle)
{
    assert((handle != NULL) && (dmaHandle != NULL));

    uint32_t instance = SAI_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set sai base to handle */
    handle->dmaHandle = dmaHandle;
    handle->callback  = callback;
    handle->userData  = userData;

    /* Set SAI state to idle */
    handle->state = (uint32_t)kSAI_Idle;

    s_dmaPrivateHandle[instance][1].base   = base;
    s_dmaPrivateHandle[instance][1].handle = handle;

/* Use FIFO error continue nstead of using interrupt to handle error */
#if defined(FSL_FEATURE_SAI_HAS_FIFO_FUNCTION_AFTER_ERROR) && (FSL_FEATURE_SAI_HAS_FIFO_FUNCTION_AFTER_ERROR)
    base->RCR4 |= I2S_RCR4_FCONT_MASK;
#endif

    /* Install callback for Tx dma channel */
    DMA_SetCallback(dmaHandle, SAI_RxDMACallback, &s_dmaPrivateHandle[instance][1]);
}

/*!
 * @brief Configures the SAI Rx.
 *
 *
 * @param base SAI base pointer.
 * @param handle SAI DMA handle pointer.
 * @param saiConfig sai configurations.
 */
void SAI_TransferRxSetConfigDMA(I2S_Type *base, sai_dma_handle_t *handle, sai_transceiver_t *saiConfig)
{
    assert((handle != NULL) && (saiConfig != NULL));

    dma_transfer_config_t config = {0};

    /* Configure the audio format to SAI registers */
    SAI_RxSetConfig(base, saiConfig);

    handle->channel = saiConfig->startChannel;

    /* Configure the data format into DMA register */
    config.srcAddr             = SAI_RxGetDataRegisterAddress(base, handle->channel);
    config.enableDestIncrement = true;
    config.enableSrcIncrement  = false;
    switch (saiConfig->frameSync.frameSyncWidth)
    {
        case 8:
            config.srcSize        = kDMA_Transfersize8bits;
            config.destSize       = kDMA_Transfersize8bits;
            handle->bytesPerFrame = 1U;
            break;
        case 16:
            config.srcSize        = kDMA_Transfersize16bits;
            config.destSize       = kDMA_Transfersize16bits;
            handle->bytesPerFrame = 2U;
            break;
        default:
            config.srcSize        = kDMA_Transfersize32bits;
            config.destSize       = kDMA_Transfersize32bits;
            handle->bytesPerFrame = 4U;
            break;
    }

    /* Configure DMA channel */
    (void)DMA_SubmitTransfer(handle->dmaHandle, &config, 1UL);
}

/*!
 * @brief Configures the SAI Tx.
 *
 *
 * @param base SAI base pointer.
 * @param handle SAI DMA handle pointer.
 * @param saiConfig sai configurations.
 */
void SAI_TransferTxSetConfigDMA(I2S_Type *base, sai_dma_handle_t *handle, sai_transceiver_t *saiConfig)
{
    assert((handle != NULL) && (saiConfig != NULL));

    dma_transfer_config_t config = {0};

    /* Configure the audio format to SAI registers */
    SAI_TxSetConfig(base, saiConfig);

    handle->channel = saiConfig->startChannel;

    /* Configure the data format into DMA register */
    config.destAddr            = SAI_TxGetDataRegisterAddress(base, handle->channel);
    config.enableDestIncrement = false;
    config.enableSrcIncrement  = true;
    switch (saiConfig->frameSync.frameSyncWidth)
    {
        case 8:
            config.srcSize        = kDMA_Transfersize8bits;
            config.destSize       = kDMA_Transfersize8bits;
            handle->bytesPerFrame = 1U;
            break;
        case 16:
            config.srcSize        = kDMA_Transfersize16bits;
            config.destSize       = kDMA_Transfersize16bits;
            handle->bytesPerFrame = 2U;
            break;
        default:
            config.srcSize        = kDMA_Transfersize32bits;
            config.destSize       = kDMA_Transfersize32bits;
            handle->bytesPerFrame = 4U;
            break;
    }

    /* Configure DMA channel */
    (void)DMA_SubmitTransfer(handle->dmaHandle, &config, 1UL);
}

/*!
 * brief Performs a non-blocking SAI transfer using DMA.
 *
 * note This interface returns immediately after the transfer initiates. Call
 * the SAI_GetTransferStatus to poll the transfer status to check whether the SAI transfer finished.
 *
 * param base SAI base pointer.
 * param handle SAI DMA handle pointer.
 * param xfer Pointer to DMA transfer structure.
 * retval kStatus_Success Successfully start the data receive.
 * retval kStatus_SAI_TxBusy Previous receive still not finished.
 * retval kStatus_InvalidArgument The input parameter is invalid.
 */
status_t SAI_TransferSendDMA(I2S_Type *base, sai_dma_handle_t *handle, sai_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));

    /* Check if input parameter invalid */
    if ((xfer->data == NULL) || (xfer->dataSize == 0U))
    {
        return kStatus_InvalidArgument;
    }

    if (handle->saiQueue[handle->queueUser].data != NULL)
    {
        return kStatus_SAI_QueueFull;
    }

    handle->transferSize[handle->queueUser]      = xfer->dataSize;
    handle->saiQueue[handle->queueUser].data     = xfer->data;
    handle->saiQueue[handle->queueUser].dataSize = xfer->dataSize;
    handle->queueUser                            = (handle->queueUser + 1U) % SAI_XFER_QUEUE_SIZE;

    /* Set the source address */
    DMA_SetSourceAddress(handle->dmaHandle->base, handle->dmaHandle->channel, (uint32_t)(xfer->data));

    /* Set the transfer size */
    DMA_SetTransferSize(handle->dmaHandle->base, handle->dmaHandle->channel, xfer->dataSize);

    /* Change the state of handle */
    handle->state = (uint32_t)kSAI_Busy;

    /* Start DMA transfer */
    DMA_StartTransfer(handle->dmaHandle);

/* Enable DMA request and start SAI */
#if defined(FSL_FEATURE_SAI_HAS_FIFO) && (FSL_FEATURE_SAI_HAS_FIFO)
    SAI_TxEnableDMA(base, kSAI_FIFORequestDMAEnable, true);
#else
    SAI_TxEnableDMA(base, kSAI_FIFOWarningDMAEnable, true);
#endif
    SAI_TxEnable(base, true);

    return kStatus_Success;
}

/*!
 * brief Performs a non-blocking SAI transfer using DMA.
 *
 * note This interface returns immediately after transfer initiates. Call
 * SAI_GetTransferStatus to poll the transfer status to check whether the SAI transfer is finished.
 *
 * param base SAI base pointer
 * param handle SAI DMA handle pointer.
 * param xfer Pointer to DMA transfer structure.
 * retval kStatus_Success Successfully start the data receive.
 * retval kStatus_SAI_RxBusy Previous receive still not finished.
 * retval kStatus_InvalidArgument The input parameter is invalid.
 */
status_t SAI_TransferReceiveDMA(I2S_Type *base, sai_dma_handle_t *handle, sai_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));

    /* Check if input parameter invalid */
    if ((xfer->data == NULL) || (xfer->dataSize == 0U))
    {
        return kStatus_InvalidArgument;
    }

    if (handle->saiQueue[handle->queueUser].data != NULL)
    {
        return kStatus_SAI_QueueFull;
    }

    /* Add into queue */
    handle->transferSize[handle->queueUser]      = xfer->dataSize;
    handle->saiQueue[handle->queueUser].data     = xfer->data;
    handle->saiQueue[handle->queueUser].dataSize = xfer->dataSize;
    handle->queueUser                            = (handle->queueUser + 1U) % SAI_XFER_QUEUE_SIZE;

    /* Set the source address */
    DMA_SetDestinationAddress(handle->dmaHandle->base, handle->dmaHandle->channel, (uint32_t)(xfer->data));

    /* Set the transfer size */
    DMA_SetTransferSize(handle->dmaHandle->base, handle->dmaHandle->channel, xfer->dataSize);

    /* Change the state of handle */
    handle->state = (uint32_t)kSAI_Busy;

    /* Start DMA transfer */
    DMA_StartTransfer(handle->dmaHandle);

/* Enable DMA request and start SAI */
#if defined(FSL_FEATURE_SAI_HAS_FIFO) && (FSL_FEATURE_SAI_HAS_FIFO)
    SAI_RxEnableDMA(base, kSAI_FIFORequestDMAEnable, true);
#else
    SAI_RxEnableDMA(base, kSAI_FIFOWarningDMAEnable, true);
#endif
    SAI_RxEnable(base, true);

    return kStatus_Success;
}

/*!
 * brief Aborts a SAI transfer using DMA.
 *
 * param base SAI base pointer.
 * param handle SAI DMA handle pointer.
 */
void SAI_TransferAbortSendDMA(I2S_Type *base, sai_dma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    DMA_AbortTransfer(handle->dmaHandle);

/* Disable DMA enable bit */
#if defined(FSL_FEATURE_SAI_HAS_FIFO) && (FSL_FEATURE_SAI_HAS_FIFO)
    SAI_TxEnableDMA(base, kSAI_FIFORequestDMAEnable, false);
#else
    SAI_TxEnableDMA(base, kSAI_FIFOWarningDMAEnable, false);
#endif

    /* Disable Tx */
    SAI_TxEnable(base, false);

    /* Set the handle state */
    handle->state = (uint32_t)kSAI_Idle;

    /* Clear the queue */
    (void)memset(handle->saiQueue, 0, sizeof(sai_transfer_t) * SAI_XFER_QUEUE_SIZE);
    handle->queueDriver = 0;
    handle->queueUser   = 0;
}

/*!
 * brief Aborts a SAI transfer using DMA.
 *
 * param base SAI base pointer.
 * param handle SAI DMA handle pointer.
 */
void SAI_TransferAbortReceiveDMA(I2S_Type *base, sai_dma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    DMA_AbortTransfer(handle->dmaHandle);

/* Disable DMA enable bit */
#if defined(FSL_FEATURE_SAI_HAS_FIFO) && (FSL_FEATURE_SAI_HAS_FIFO)
    SAI_RxEnableDMA(base, kSAI_FIFORequestDMAEnable, false);
#else
    SAI_RxEnableDMA(base, kSAI_FIFOWarningDMAEnable, false);
#endif

    /* Disable Rx */
    SAI_RxEnable(base, false);

    /* Set the handle state */
    handle->state = (uint32_t)kSAI_Idle;

    /* Clear the queue */
    (void)memset(handle->saiQueue, 0, sizeof(sai_transfer_t) * SAI_XFER_QUEUE_SIZE);
    handle->queueDriver = 0;
    handle->queueUser   = 0;
}

/*!
 * brief Gets byte count sent by SAI.
 *
 * param base SAI base pointer.
 * param handle SAI DMA handle pointer.
 * param count Bytes count sent by SAI.
 * retval kStatus_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t SAI_TransferGetSendCountDMA(I2S_Type *base, sai_dma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kSAI_Busy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = handle->transferSize[handle->queueDriver] -
                 DMA_GetRemainingBytes(handle->dmaHandle->base, handle->dmaHandle->channel);
    }

    return status;
}

/*!
 * brief Gets byte count received by SAI.
 *
 * param base SAI base pointer.
 * param handle SAI DMA handle pointer.
 * param count Bytes count received by SAI.
 * retval kStatus_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t SAI_TransferGetReceiveCountDMA(I2S_Type *base, sai_dma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kSAI_Busy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = handle->transferSize[handle->queueDriver] -
                 DMA_GetRemainingBytes(handle->dmaHandle->base, handle->dmaHandle->channel);
    }

    return status;
}
