/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexio_i2s_dma.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexio_i2s_dma"
#endif

/*******************************************************************************
 * Definitations
 ******************************************************************************/

/*<! Structure definition for flexio_i2s_dma_private_handle_t. The structure is private. */
typedef struct _flexio_i2s_dma_private_handle
{
    FLEXIO_I2S_Type *base;
    flexio_i2s_dma_handle_t *handle;
} flexio_i2s_dma_private_handle_t;

/*!brief _flexio_i2s_dma_transfer_state */
enum
{
    kFLEXIO_I2S_Busy = 0x0U, /*!< FLEXIO I2S is busy */
    kFLEXIO_I2S_Idle,        /*!< Transfer is done. */
};

/*<! Private handle only used for internally. */
static flexio_i2s_dma_private_handle_t s_dmaPrivateHandle[2];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief FLEXIO I2S DMA callback for send.
 *
 * @param handle pointer to flexio_i2s_dma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 */
static void FLEXIO_I2S_TxDMACallback(dma_handle_t *handle, void *userData);

/*!
 * @brief FLEXIO I2S DMA callback for receive.
 *
 * @param handle pointer to flexio_i2s_dma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 */
static void FLEXIO_I2S_RxDMACallback(dma_handle_t *handle, void *userData);

/*******************************************************************************
 * Code
 ******************************************************************************/
static void FLEXIO_I2S_TxDMACallback(dma_handle_t *handle, void *userData)
{
    flexio_i2s_dma_private_handle_t *privHandle = (flexio_i2s_dma_private_handle_t *)userData;
    flexio_i2s_dma_handle_t *flexio_i2sHandle   = privHandle->handle;

    /* If finished a block, call the callback function */
    (void)memset(&flexio_i2sHandle->queue[flexio_i2sHandle->queueDriver], 0, sizeof(flexio_i2s_transfer_t));
    flexio_i2sHandle->queueDriver = (flexio_i2sHandle->queueDriver + 1U) % FLEXIO_I2S_XFER_QUEUE_SIZE;
    if (flexio_i2sHandle->callback != NULL)
    {
        (flexio_i2sHandle->callback)(privHandle->base, flexio_i2sHandle, kStatus_Success, flexio_i2sHandle->userData);
    }

    /* If all data finished, just stop the transfer */
    if (flexio_i2sHandle->queue[flexio_i2sHandle->queueDriver].data == NULL)
    {
        FLEXIO_I2S_TransferAbortSendDMA(privHandle->base, flexio_i2sHandle);
    }
}

static void FLEXIO_I2S_RxDMACallback(dma_handle_t *handle, void *userData)
{
    flexio_i2s_dma_private_handle_t *privHandle = (flexio_i2s_dma_private_handle_t *)userData;
    flexio_i2s_dma_handle_t *flexio_i2sHandle   = privHandle->handle;

    /* If finished a block, call the callback function */
    (void)memset(&flexio_i2sHandle->queue[flexio_i2sHandle->queueDriver], 0, sizeof(flexio_i2s_transfer_t));
    flexio_i2sHandle->queueDriver = (flexio_i2sHandle->queueDriver + 1U) % FLEXIO_I2S_XFER_QUEUE_SIZE;
    if (flexio_i2sHandle->callback != NULL)
    {
        (flexio_i2sHandle->callback)(privHandle->base, flexio_i2sHandle, kStatus_Success, flexio_i2sHandle->userData);
    }

    /* If all data finished, just stop the transfer */
    if (flexio_i2sHandle->queue[flexio_i2sHandle->queueDriver].data == NULL)
    {
        FLEXIO_I2S_TransferAbortReceiveDMA(privHandle->base, flexio_i2sHandle);
    }
}

/*!
 * brief Initializes the FlexIO I2S DMA handle.
 *
 * This function initializes the FlexIO I2S master DMA handle which can be used for other FlexIO I2S master
 * transactional APIs.
 * Usually, for a specified FlexIO I2S instance, call this API once to get the initialized handle.
 *
 * param base FlexIO I2S peripheral base address.
 * param handle FlexIO I2S DMA handle pointer.
 * param callback FlexIO I2S DMA callback function called while finished a block.
 * param userData User parameter for callback.
 * param dmaHandle DMA handle for FlexIO I2S. This handle is a static value allocated by users.
 */
void FLEXIO_I2S_TransferTxCreateHandleDMA(FLEXIO_I2S_Type *base,
                                          flexio_i2s_dma_handle_t *handle,
                                          flexio_i2s_dma_callback_t callback,
                                          void *userData,
                                          dma_handle_t *dmaHandle)
{
    assert((handle != NULL) && (dmaHandle != NULL));

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set flexio_i2s base to handle */
    handle->dmaHandle = dmaHandle;
    handle->callback  = callback;
    handle->userData  = userData;

    /* Set FLEXIO I2S state to idle */
    handle->state = (uint32_t)kFLEXIO_I2S_Idle;

    s_dmaPrivateHandle[0].base   = base;
    s_dmaPrivateHandle[0].handle = handle;

    /* Install callback for Tx dma channel */
    DMA_SetCallback(dmaHandle, FLEXIO_I2S_TxDMACallback, &s_dmaPrivateHandle[0]);
}

/*!
 * brief Initializes the FlexIO I2S Rx DMA handle.
 *
 * This function initializes the FlexIO I2S slave DMA handle which can be used for other FlexIO I2S master transactional
 * APIs.
 * Usually, for a specified FlexIO I2S instance, call this API once to get the initialized handle.
 *
 * param base FlexIO I2S peripheral base address.
 * param handle FlexIO I2S DMA handle pointer.
 * param callback FlexIO I2S DMA callback function called while finished a block.
 * param userData User parameter for callback.
 * param dmaHandle DMA handle for FlexIO I2S. This handle is a static value allocated by users.
 */
void FLEXIO_I2S_TransferRxCreateHandleDMA(FLEXIO_I2S_Type *base,
                                          flexio_i2s_dma_handle_t *handle,
                                          flexio_i2s_dma_callback_t callback,
                                          void *userData,
                                          dma_handle_t *dmaHandle)
{
    assert((handle != NULL) && (dmaHandle != NULL));

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set flexio_i2s base to handle */
    handle->dmaHandle = dmaHandle;
    handle->callback  = callback;
    handle->userData  = userData;

    /* Set FLEXIO I2S state to idle */
    handle->state = (uint32_t)kFLEXIO_I2S_Idle;

    s_dmaPrivateHandle[1].base   = base;
    s_dmaPrivateHandle[1].handle = handle;

    /* Install callback for Tx dma channel */
    DMA_SetCallback(dmaHandle, FLEXIO_I2S_RxDMACallback, &s_dmaPrivateHandle[1]);
}

/*!
 * brief Configures the FlexIO I2S Tx audio format.
 *
 * Audio format can be changed at run-time of FlexIO I2S. This function configures the sample rate and audio data
 * format to be transferred. This function also sets the DMA parameter according to the format.
 *
 * param base FlexIO I2S peripheral base address.
 * param handle FlexIO I2S DMA handle pointer
 * param format Pointer to FlexIO I2S audio data format structure.
 * param srcClock_Hz FlexIO I2S clock source frequency in Hz. It should be 0 while in slave mode.
 */
void FLEXIO_I2S_TransferSetFormatDMA(FLEXIO_I2S_Type *base,
                                     flexio_i2s_dma_handle_t *handle,
                                     flexio_i2s_format_t *format,
                                     uint32_t srcClock_Hz)
{
    assert((handle != NULL) && (format != NULL));

    /* Configure the audio format to FLEXIO I2S registers */
    if (srcClock_Hz != 0U)
    {
        /* It is master */
        FLEXIO_I2S_MasterSetFormat(base, format, srcClock_Hz);
    }
    else
    {
        FLEXIO_I2S_SlaveSetFormat(base, format);
    }

    /* Get the transfer size from format, this should be used in DMA configuration */
    handle->bytesPerFrame = format->bitWidth / 8U;
}

/*!
 * brief Performs a non-blocking FlexIO I2S transfer using DMA.
 *
 * note This interface returns immediately after transfer initiates. Call
 * FLEXIO_I2S_GetTransferStatus to poll the transfer status and check whether FLEXIO I2S transfer finished.
 *
 * param base FlexIO I2S peripheral base address.
 * param handle FlexIO I2S DMA handle pointer.
 * param xfer Pointer to DMA transfer structure.
 * retval kStatus_Success Start a FlexIO I2S DMA send successfully.
 * retval kStatus_InvalidArgument The input arguments is invalid.
 * retval kStatus_TxBusy FlexIO I2S is busy sending data.
 */
status_t FLEXIO_I2S_TransferSendDMA(FLEXIO_I2S_Type *base, flexio_i2s_dma_handle_t *handle, flexio_i2s_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));

    dma_transfer_config_t config = {0};
    uint32_t destAddr            = FLEXIO_I2S_TxGetDataRegisterAddress(base) + (4UL - handle->bytesPerFrame);

    /* Check if input parameter invalid */
    if ((xfer->data == NULL) || (xfer->dataSize == 0U))
    {
        return kStatus_InvalidArgument;
    }

    if (handle->queue[handle->queueUser].data != NULL)
    {
        return kStatus_FLEXIO_I2S_QueueFull;
    }

    /* Change the state of handle */
    handle->state = (uint32_t)kFLEXIO_I2S_Busy;

    /* Update the queue state */
    handle->queue[handle->queueUser].data     = xfer->data;
    handle->queue[handle->queueUser].dataSize = xfer->dataSize;
    handle->transferSize[handle->queueUser]   = xfer->dataSize;
    handle->queueUser                         = (handle->queueUser + 1U) % FLEXIO_I2S_XFER_QUEUE_SIZE;

    DMA_PrepareTransfer(&config, xfer->data, handle->bytesPerFrame, (uint32_t *)destAddr, handle->bytesPerFrame,
                        xfer->dataSize, kDMA_MemoryToPeripheral);

    /* Configure DMA channel */
    (void)DMA_SubmitTransfer(handle->dmaHandle, &config, 1UL);

    /* Start DMA transfer */
    DMA_StartTransfer(handle->dmaHandle);

    /* Enable DMA enable bit */
    FLEXIO_I2S_TxEnableDMA(base, true);

    /* Enable FLEXIO I2S Tx clock */
    FLEXIO_I2S_Enable(base, true);

    return kStatus_Success;
}

/*!
 * brief Performs a non-blocking FlexIO I2S receive using DMA.
 *
 * note This interface returns immediately after transfer initiates. Call
 * FLEXIO_I2S_GetReceiveRemainingBytes to poll the transfer status to check whether the FlexIO I2S transfer is finished.
 *
 * param base FlexIO I2S peripheral base address.
 * param handle FlexIO I2S DMA handle pointer.
 * param xfer Pointer to DMA transfer structure.
 * retval kStatus_Success Start a FlexIO I2S DMA receive successfully.
 * retval kStatus_InvalidArgument The input arguments is invalid.
 * retval kStatus_RxBusy FlexIO I2S is busy receiving data.
 */
status_t FLEXIO_I2S_TransferReceiveDMA(FLEXIO_I2S_Type *base,
                                       flexio_i2s_dma_handle_t *handle,
                                       flexio_i2s_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));

    dma_transfer_config_t config = {0};
    uint32_t srcAddr             = FLEXIO_I2S_RxGetDataRegisterAddress(base);

    /* Check if input parameter invalid */
    if ((xfer->data == NULL) || (xfer->dataSize == 0U))
    {
        return kStatus_InvalidArgument;
    }

    if (handle->queue[handle->queueUser].data != NULL)
    {
        return kStatus_FLEXIO_I2S_QueueFull;
    }

    /* Change the state of handle */
    handle->state = (uint32_t)kFLEXIO_I2S_Busy;

    /* Update queue state  */
    handle->queue[handle->queueUser].data     = xfer->data;
    handle->queue[handle->queueUser].dataSize = xfer->dataSize;
    handle->transferSize[handle->queueUser]   = xfer->dataSize;
    handle->queueUser                         = (handle->queueUser + 1U) % FLEXIO_I2S_XFER_QUEUE_SIZE;

    /* Prepare dma configure */
    DMA_PrepareTransfer(&config, (uint32_t *)srcAddr, handle->bytesPerFrame, xfer->data, handle->bytesPerFrame,
                        xfer->dataSize, kDMA_PeripheralToMemory);

    (void)DMA_SubmitTransfer(handle->dmaHandle, &config, 1UL);

    /* Start DMA transfer */
    DMA_StartTransfer(handle->dmaHandle);

    /* Enable DMA enable bit */
    FLEXIO_I2S_RxEnableDMA(base, true);

    /* Enable FLEXIO I2S Rx clock */
    FLEXIO_I2S_Enable(base, true);

    return kStatus_Success;
}

/*!
 * brief Aborts a FlexIO I2S transfer using DMA.
 *
 * param base FlexIO I2S peripheral base address.
 * param handle FlexIO I2S DMA handle pointer.
 */
void FLEXIO_I2S_TransferAbortSendDMA(FLEXIO_I2S_Type *base, flexio_i2s_dma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    DMA_AbortTransfer(handle->dmaHandle);

    /* Disable DMA enable bit */
    FLEXIO_I2S_TxEnableDMA(base, false);

    /* Set the handle state */
    handle->state = (uint32_t)kFLEXIO_I2S_Idle;
}

/*!
 * brief Aborts a FlexIO I2S receive using DMA.
 *
 * param base FlexIO I2S peripheral base address.
 * param handle FlexIO I2S DMA handle pointer.
 */
void FLEXIO_I2S_TransferAbortReceiveDMA(FLEXIO_I2S_Type *base, flexio_i2s_dma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    DMA_AbortTransfer(handle->dmaHandle);

    /* Disable DMA enable bit */
    FLEXIO_I2S_RxEnableDMA(base, false);

    /* Set the handle state */
    handle->state = (uint32_t)kFLEXIO_I2S_Idle;
}

/*!
 * brief Gets the remaining bytes to be sent.
 *
 * param base FlexIO I2S peripheral base address.
 * param handle FlexIO I2S DMA handle pointer.
 * param count Bytes sent.
 * retval kStatus_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t FLEXIO_I2S_TransferGetSendCountDMA(FLEXIO_I2S_Type *base, flexio_i2s_dma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kFLEXIO_I2S_Busy)
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
 * brief Gets the remaining bytes to be received.
 *
 * param base FlexIO I2S peripheral base address.
 * param handle FlexIO I2S DMA handle pointer.
 * param count Bytes received.
 * retval kStatus_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t FLEXIO_I2S_TransferGetReceiveCountDMA(FLEXIO_I2S_Type *base, flexio_i2s_dma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kFLEXIO_I2S_Busy)
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
