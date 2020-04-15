/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dma.h"
#include "fsl_i2s_dma.h"
#include "fsl_flexcomm.h"
#include <string.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexcomm_i2s_dma"
#endif

#define DMA_MAX_TRANSFER_BYTES (DMA_MAX_TRANSFER_COUNT * sizeof(uint32_t))
#define DMA_DESCRIPTORS (2U)

/*<! @brief Structure for statically allocated private data. */
typedef struct _i2s_dma_private_handle
{
    I2S_Type *base;           /*!< I2S base address */
    i2s_dma_handle_t *handle; /*!< I2S handle */

    volatile uint16_t enqueuedBytes[DMA_DESCRIPTORS]; /*!< Number of bytes being transferred by DMA descriptors */
    volatile uint8_t enqueuedBytesStart;              /*!< First item in enqueuedBytes (for reading) */
    volatile uint8_t enqueuedBytesEnd;                /*!< Last item in enqueuedBytes (for adding) */

    volatile uint8_t
        dmaDescriptorsUsed; /*!< Number of DMA descriptors with valid data (in queue, excluding initial descriptor) */
    volatile uint8_t descriptor; /*!< Index of next DMA descriptor in s_DmaDescriptors to be configured with data (does
                                    not include I2S instance offset) */

    volatile uint8_t queueDescriptor;                         /*!< Queue index of buffer to be actually consumed by DMA
                                                               * (queueUser - advanced when user adds a buffer,
                                                               *  queueDescriptor - advanced when user buffer queued to DMA,
                                                               *  queueDriver - advanced when DMA queued buffer sent out to I2S) */
    volatile i2s_transfer_t descriptorQueue[I2S_NUM_BUFFERS]; /*!< Transfer data to be queued to DMA */

    volatile bool intA; /*!< If next scheduled DMA transfer will cause interrupt A or B */
} i2s_dma_private_handle_t;

/*! @brief I2S DMA transfer private state. */
enum _i2s_dma_state
{
    kI2S_DmaStateIdle = 0x0U, /*!< I2S is in idle state */
    kI2S_DmaStateTx,          /*!< I2S is busy transmitting data */
    kI2S_DmaStateRx,          /*!< I2S is busy receiving data */
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static status_t I2S_EnqueueUserBuffer(I2S_Type *base, i2s_dma_handle_t *handle, i2s_transfer_t transfer);
static uint32_t I2S_GetInstance(I2S_Type *base);
static inline void I2S_DisableDMAInterrupts(i2s_dma_handle_t *handle);
static inline void I2S_EnableDMAInterrupts(i2s_dma_handle_t *handle);
static void I2S_TxEnableDMA(I2S_Type *base, bool enable);
static void I2S_RxEnableDMA(I2S_Type *base, bool enable);
static uint16_t I2S_GetTransferBytes(volatile i2s_transfer_t *transfer);
static status_t I2S_StartTransferDMA(I2S_Type *base, i2s_dma_handle_t *handle);
static void I2S_AddTransferDMA(I2S_Type *base, i2s_dma_handle_t *handle);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*<! @brief Allocate DMA transfer descriptors. */
DMA_ALLOCATE_LINK_DESCRIPTORS(s_DmaDescriptors, DMA_DESCRIPTORS *FSL_FEATURE_SOC_I2S_COUNT);

/*<! @brief Buffer with dummy TX data. */
SDK_ALIGN(static uint32_t s_DummyBufferTx, 4U);

/*<! @brief Buffer to fill with RX data to discard. */
SDK_ALIGN(static uint32_t s_DummyBufferRx, 4U);

/*<! @brief Private array of data associated with available I2S peripherals. */
static i2s_dma_private_handle_t s_DmaPrivateHandle[FSL_FEATURE_SOC_I2S_COUNT];

/*<! @brief Base addresses of available I2S peripherals. */
static const uint32_t s_I2sBaseAddrs[FSL_FEATURE_SOC_I2S_COUNT] = I2S_BASE_ADDRS;

/*******************************************************************************
 * Code
 ******************************************************************************/

static status_t I2S_EnqueueUserBuffer(I2S_Type *base, i2s_dma_handle_t *handle, i2s_transfer_t transfer)
{
    uint32_t instance                       = I2S_GetInstance(base);
    i2s_dma_private_handle_t *privateHandle = &(s_DmaPrivateHandle[instance]);

    /* Validate input data and transfer buffer */

    assert(handle);
    if (!handle)
    {
        return kStatus_InvalidArgument;
    }

    assert((((uint32_t)transfer.data) % 4U) == 0U);
    if ((((uint32_t)transfer.data) % 4U) != 0U)
    {
        /* Data not 4-bytes aligned */
        return kStatus_InvalidArgument;
    }

    assert(transfer.dataSize != 0U);
    if (transfer.dataSize == 0U)
    {
        /* No data to send or receive */
        return kStatus_InvalidArgument;
    }

    assert((transfer.dataSize % 4U) == 0U);
    if ((transfer.dataSize % 4U) != 0U)
    {
        /* Data length not multiply of 4 bytes */
        return kStatus_InvalidArgument;
    }

    if (handle->i2sQueue[handle->queueUser].dataSize)
    {
        /* Previously prepared buffers not processed yet, reject request */
        return kStatus_I2S_Busy;
    }

    /* Enqueue data */
    privateHandle->descriptorQueue[handle->queueUser].data     = transfer.data;
    privateHandle->descriptorQueue[handle->queueUser].dataSize = transfer.dataSize;
    handle->i2sQueue[handle->queueUser].data                   = transfer.data;
    handle->i2sQueue[handle->queueUser].dataSize               = transfer.dataSize;
    handle->queueUser                                          = (handle->queueUser + 1U) % I2S_NUM_BUFFERS;

    return kStatus_Success;
}

static uint32_t I2S_GetInstance(I2S_Type *base)
{
    uint32_t i;

    for (i = 0U; i < ARRAY_SIZE(s_I2sBaseAddrs); i++)
    {
        if ((uint32_t)base == s_I2sBaseAddrs[i])
        {
            return i;
        }
    }

    assert(false);
    return 0U;
}

static inline void I2S_DisableDMAInterrupts(i2s_dma_handle_t *handle)
{
    DMA_DisableChannelInterrupts(handle->dmaHandle->base, handle->dmaHandle->channel);
}

static inline void I2S_EnableDMAInterrupts(i2s_dma_handle_t *handle)
{
    if (handle->state != kI2S_DmaStateIdle)
    {
        DMA_EnableChannelInterrupts(handle->dmaHandle->base, handle->dmaHandle->channel);
    }
}

/*!
 * brief Initializes handle for transfer of audio data.
 *
 * param base I2S base pointer.
 * param handle pointer to handle structure.
 * param dmaHandle pointer to dma handle structure.
 * param callback function to be called back when transfer is done or fails.
 * param userData pointer to data passed to callback.
 */
void I2S_TxTransferCreateHandleDMA(I2S_Type *base,
                                   i2s_dma_handle_t *handle,
                                   dma_handle_t *dmaHandle,
                                   i2s_dma_transfer_callback_t callback,
                                   void *userData)
{
    assert(handle);
    assert(dmaHandle);

    uint32_t instance                       = I2S_GetInstance(base);
    i2s_dma_private_handle_t *privateHandle = &(s_DmaPrivateHandle[instance]);

    memset(handle, 0U, sizeof(*handle));
    handle->state              = kI2S_DmaStateIdle;
    handle->dmaHandle          = dmaHandle;
    handle->completionCallback = callback;
    handle->userData           = userData;

    handle->bytesPerFrame = (((base->CFG1 & I2S_CFG1_DATALEN_MASK) >> I2S_CFG1_DATALEN_SHIFT) + 1U) / 8U;
    /* if one channel is disabled, bytesPerFrame should be 4U, user should pay attention that when data length is
     * shorter than 16, the data format: left data put in 0-15 bit and right data should put in 16-31
     */
    if (((base->CFG1 & I2S_CFG1_ONECHANNEL_MASK) == 0U))
    {
        handle->bytesPerFrame = 4U;
    }
    /* since DMA do not support 24bit transfer width, use 32bit instead */
    if (handle->bytesPerFrame == 3U)
    {
        handle->bytesPerFrame = 4U;
    }

    memset(privateHandle, 0U, sizeof(*privateHandle));
    privateHandle->base   = base;
    privateHandle->handle = handle;

    DMA_SetCallback(dmaHandle, I2S_DMACallback, privateHandle);
}

/*!
 * brief Begins or queue sending of the given data.
 *
 * param base I2S base pointer.
 * param handle pointer to handle structure.
 * param transfer data buffer.
 *
 * retval kStatus_Success
 * retval kStatus_I2S_Busy if all queue slots are occupied with unsent buffers.
 */
status_t I2S_TxTransferSendDMA(I2S_Type *base, i2s_dma_handle_t *handle, i2s_transfer_t transfer)
{
    status_t status;

    I2S_DisableDMAInterrupts(handle);

    /* Enqueue transfer buffer */
    status = I2S_EnqueueUserBuffer(base, handle, transfer);
    if (status != kStatus_Success)
    {
        I2S_EnableDMAInterrupts(handle);
        return status;
    }

    /* Initialize DMA transfer */
    if (handle->state == kI2S_DmaStateIdle)
    {
        handle->state = kI2S_DmaStateTx;
        status        = I2S_StartTransferDMA(base, handle);
        if (status != kStatus_Success)
        {
            I2S_EnableDMAInterrupts(handle);
            return status;
        }
    }

    I2S_AddTransferDMA(base, handle);
    I2S_EnableDMAInterrupts(handle);

    return kStatus_Success;
}

/*!
 * brief Aborts transfer of data.
 *
 * param base I2S base pointer.
 * param handle pointer to handle structure.
 */
void I2S_TransferAbortDMA(I2S_Type *base, i2s_dma_handle_t *handle)
{
    assert(handle);
    assert(handle->dmaHandle);

    uint32_t instance                       = I2S_GetInstance(base);
    i2s_dma_private_handle_t *privateHandle = &(s_DmaPrivateHandle[instance]);

    I2S_DisableDMAInterrupts(handle);

    /* Abort operation */
    DMA_AbortTransfer(handle->dmaHandle);

    if (handle->state == kI2S_DmaStateTx)
    {
        /* Wait until all transmitted data get out of FIFO */
        while ((base->FIFOSTAT & I2S_FIFOSTAT_TXEMPTY_MASK) == 0U)
        {
        }
        /* The last piece of valid data can be still being transmitted from I2S at this moment */

        /* Write additional data to FIFO */
        base->FIFOWR = 0U;
        while ((base->FIFOSTAT & I2S_FIFOSTAT_TXEMPTY_MASK) == 0U)
        {
        }
        /* At this moment the additional data are out of FIFO, starting being transmitted.
         * This means the preceding valid data has been just transmitted and we can stop I2S. */
        I2S_TxEnableDMA(base, false);
    }
    else
    {
        I2S_RxEnableDMA(base, false);
    }

    I2S_Disable(base);

    /* Reset state */
    handle->state = kI2S_DmaStateIdle;

    /* Clear transfer queue */
    memset((void *)&(handle->i2sQueue), 0U, sizeof(handle->i2sQueue));
    handle->queueDriver = 0U;
    handle->queueUser   = 0U;

    /* Clear internal state */
    memset((void *)&(privateHandle->descriptorQueue), 0U, sizeof(privateHandle->descriptorQueue));
    memset((void *)&(privateHandle->enqueuedBytes), 0U, sizeof(privateHandle->enqueuedBytes));
    privateHandle->enqueuedBytesStart = 0U;
    privateHandle->enqueuedBytesEnd   = 0U;
    privateHandle->dmaDescriptorsUsed = 0U;
    privateHandle->descriptor         = 0U;
    privateHandle->queueDescriptor    = 0U;
    privateHandle->intA               = false;
}

/*!
 * brief Initializes handle for reception of audio data.
 *
 * param base I2S base pointer.
 * param handle pointer to handle structure.
 * param dmaHandle pointer to dma handle structure.
 * param callback function to be called back when transfer is done or fails.
 * param userData pointer to data passed to callback.
 */
void I2S_RxTransferCreateHandleDMA(I2S_Type *base,
                                   i2s_dma_handle_t *handle,
                                   dma_handle_t *dmaHandle,
                                   i2s_dma_transfer_callback_t callback,
                                   void *userData)
{
    I2S_TxTransferCreateHandleDMA(base, handle, dmaHandle, callback, userData);
}

/*!
 * brief Begins or queue reception of data into given buffer.
 *
 * param base I2S base pointer.
 * param handle pointer to handle structure.
 * param transfer data buffer.
 *
 * retval kStatus_Success
 * retval kStatus_I2S_Busy if all queue slots are occupied with buffers
 *         which are not full.
 */
status_t I2S_RxTransferReceiveDMA(I2S_Type *base, i2s_dma_handle_t *handle, i2s_transfer_t transfer)
{
    status_t status;

    I2S_DisableDMAInterrupts(handle);

    /* Enqueue transfer buffer */
    status = I2S_EnqueueUserBuffer(base, handle, transfer);
    if (status != kStatus_Success)
    {
        I2S_EnableDMAInterrupts(handle);
        return status;
    }

    /* Initialize DMA transfer */
    if (handle->state == kI2S_DmaStateIdle)
    {
        handle->state = kI2S_DmaStateRx;
        status        = I2S_StartTransferDMA(base, handle);
        if (status != kStatus_Success)
        {
            I2S_EnableDMAInterrupts(handle);
            return status;
        }
    }

    I2S_AddTransferDMA(base, handle);
    I2S_EnableDMAInterrupts(handle);

    return kStatus_Success;
}

static void I2S_TxEnableDMA(I2S_Type *base, bool enable)
{
    if (enable)
    {
        base->FIFOCFG |= I2S_FIFOCFG_DMATX_MASK;
    }
    else
    {
        base->FIFOCFG &= (~I2S_FIFOCFG_DMATX_MASK);
        base->FIFOCFG |= I2S_FIFOCFG_EMPTYTX_MASK;
    }
}

static void I2S_RxEnableDMA(I2S_Type *base, bool enable)
{
    if (enable)
    {
        base->FIFOCFG |= I2S_FIFOCFG_DMARX_MASK;
    }
    else
    {
        base->FIFOCFG &= (~I2S_FIFOCFG_DMARX_MASK);
        base->FIFOCFG |= I2S_FIFOCFG_EMPTYRX_MASK;
    }
}

static uint16_t I2S_GetTransferBytes(volatile i2s_transfer_t *transfer)
{
    assert(transfer);

    uint16_t transferBytes;

    if (transfer->dataSize >= (2 * DMA_MAX_TRANSFER_BYTES))
    {
        transferBytes = DMA_MAX_TRANSFER_BYTES;
    }
    else if (transfer->dataSize > DMA_MAX_TRANSFER_BYTES)
    {
        transferBytes = transfer->dataSize / 2U;
        if ((transferBytes % 4U) != 0U)
        {
            transferBytes -= (transferBytes % 4U);
        }
    }
    else
    {
        transferBytes = transfer->dataSize;
    }

    return transferBytes;
}

static status_t I2S_StartTransferDMA(I2S_Type *base, i2s_dma_handle_t *handle)
{
    uint32_t instance                       = I2S_GetInstance(base);
    i2s_dma_private_handle_t *privateHandle = &(s_DmaPrivateHandle[instance]);
    volatile i2s_transfer_t *transfer       = &(privateHandle->descriptorQueue[privateHandle->queueDescriptor]);
    uint16_t transferBytes                  = I2S_GetTransferBytes(transfer);
    int i                                   = 0U;
    uint32_t xferConfig                     = 0U;

    /* Initial descriptor is stored in another place in memory, but treat it as another descriptor for simplicity */
    privateHandle->dmaDescriptorsUsed = 1U;
    privateHandle->intA               = false;

    /* submit transfer parameter directly */
    xferConfig = DMA_CHANNEL_XFER(true, false, privateHandle->intA, !privateHandle->intA, handle->bytesPerFrame,
                                  (handle->state == kI2S_DmaStateTx) ? 1U : 0U,
                                  (handle->state == kI2S_DmaStateTx) ? 0U : 1U, transferBytes);
    DMA_SubmitChannelTransferParameter(
        handle->dmaHandle, xferConfig,
        (void *)((handle->state == kI2S_DmaStateTx) ? (uint32_t)transfer->data : (uint32_t)(&(base->FIFORD))),
        (void *)((handle->state == kI2S_DmaStateTx) ? (uint32_t)(&(base->FIFOWR)) : (uint32_t)transfer->data),
        (void *)&(s_DmaDescriptors[(instance * DMA_DESCRIPTORS) + 0U]));

    privateHandle->enqueuedBytes[privateHandle->enqueuedBytesEnd] = transferBytes;
    privateHandle->enqueuedBytesEnd = (privateHandle->enqueuedBytesEnd + 1U) % DMA_DESCRIPTORS;

    transfer->dataSize -= transferBytes;
    transfer->data += transferBytes;

    if (transfer->dataSize == 0U)
    {
        transfer->data                 = NULL;
        privateHandle->queueDescriptor = (privateHandle->queueDescriptor + 1U) % I2S_NUM_BUFFERS;
    }

    /* Link the DMA descriptors for the case when no additional transfer is queued before the initial one finishes
     * The configuration for the DMA dummy descriptor make no sense to tx or rx transfer, since it will be overwritten
     * when another transfer request comes before the previous finished.
     * To make sure the audio data transfer continuously, application must request another transfer by call
     * I2S_RxTransferReceiveDMA or I2S_TxTransferSendDMA before previous transfer finished.
     */
    for (i = 0; i < DMA_DESCRIPTORS; i++)
    {
        DMA_SetupDescriptor(&(s_DmaDescriptors[(instance * DMA_DESCRIPTORS) + i]),
                            DMA_CHANNEL_XFER(true, false, false, false, sizeof(uint32_t), 0U, 0U, 8U),
                            ((handle->state == kI2S_DmaStateTx) ? (void *)(uint32_t)&s_DummyBufferTx :
                                                                  (void *)(uint32_t)(&(base->FIFORD))),
                            ((handle->state == kI2S_DmaStateTx) ? (void *)(uint32_t)(&(base->FIFOWR)) :
                                                                  (void *)(uint32_t)&s_DummyBufferRx),
                            &(s_DmaDescriptors[(instance * DMA_DESCRIPTORS) + ((i + 1) % DMA_DESCRIPTORS)]));
    }

    /* Submit and start initial DMA transfer */
    if (handle->state == kI2S_DmaStateTx)
    {
        I2S_TxEnableDMA(base, true);
    }
    else
    {
        I2S_RxEnableDMA(base, true);
    }
    /* enable I2S peripheral request and put the channel into triggered status */
    DMA_EnableChannelPeriphRq(handle->dmaHandle->base, handle->dmaHandle->channel);
    DMA_StartTransfer(handle->dmaHandle);

    I2S_Enable(base);

    return kStatus_Success;
}

static void I2S_AddTransferDMA(I2S_Type *base, i2s_dma_handle_t *handle)
{
    volatile i2s_transfer_t *transfer;
    uint16_t transferBytes;
    uint32_t instance;
    i2s_dma_private_handle_t *privateHandle;
    dma_descriptor_t *descriptor;
    dma_descriptor_t *nextDescriptor;
    uint32_t xferConfig = 0U;

    instance      = I2S_GetInstance(base);
    privateHandle = &(s_DmaPrivateHandle[instance]);

    while (privateHandle->dmaDescriptorsUsed < DMA_DESCRIPTORS)
    {
        transfer = &(privateHandle->descriptorQueue[privateHandle->queueDescriptor]);

        if (transfer->dataSize == 0U)
        {
            /* Nothing to be added */
            return;
        }

        /* Determine currently configured descriptor and the other which it will link to */
        descriptor                = &(s_DmaDescriptors[(instance * DMA_DESCRIPTORS) + privateHandle->descriptor]);
        privateHandle->descriptor = (privateHandle->descriptor + 1U) % DMA_DESCRIPTORS;
        nextDescriptor            = &(s_DmaDescriptors[(instance * DMA_DESCRIPTORS) + privateHandle->descriptor]);

        transferBytes                                                 = I2S_GetTransferBytes(transfer);
        privateHandle->enqueuedBytes[privateHandle->enqueuedBytesEnd] = transferBytes;
        privateHandle->enqueuedBytesEnd = (privateHandle->enqueuedBytesEnd + 1U) % DMA_DESCRIPTORS;

        xferConfig = DMA_CHANNEL_XFER(true, false, !privateHandle->intA, privateHandle->intA, handle->bytesPerFrame,
                                      (handle->state == kI2S_DmaStateTx) ? 1U : 0U,
                                      (handle->state == kI2S_DmaStateTx) ? 0U : 1U, transferBytes);

        DMA_SetupDescriptor(descriptor, xferConfig,
                            ((handle->state == kI2S_DmaStateTx) ? (void *)(uint32_t)transfer->data :
                                                                  (void *)(uint32_t) & (base->FIFORD)),
                            ((handle->state == kI2S_DmaStateTx) ? (void *)(uint32_t) & (base->FIFOWR) :
                                                                  (void *)(uint32_t)transfer->data),
                            nextDescriptor);

        /* Advance internal state */
        privateHandle->dmaDescriptorsUsed++;
        privateHandle->intA = !privateHandle->intA;

        transfer->dataSize -= transferBytes;
        transfer->data += transferBytes;
        if (transfer->dataSize == 0U)
        {
            transfer->data                 = NULL;
            privateHandle->queueDescriptor = (privateHandle->queueDescriptor + 1U) % I2S_NUM_BUFFERS;
        }
    }
}

/*!
 * brief Invoked from DMA interrupt handler.
 *
 * param handle pointer to DMA handle structure.
 * param userData argument for user callback.
 * param transferDone if transfer was done.
 * param tcds
 */
void I2S_DMACallback(dma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds)
{
    i2s_dma_private_handle_t *privateHandle = (i2s_dma_private_handle_t *)userData;
    i2s_dma_handle_t *i2sHandle             = privateHandle->handle;
    I2S_Type *base                          = privateHandle->base;

    if ((!transferDone) || (i2sHandle->state == kI2S_DmaStateIdle))
    {
        return;
    }

    if (privateHandle->dmaDescriptorsUsed > 0U)
    {
        /* Finished descriptor, decrease amount of data to be processed */

        i2sHandle->i2sQueue[i2sHandle->queueDriver].dataSize -=
            privateHandle->enqueuedBytes[privateHandle->enqueuedBytesStart];
        i2sHandle->i2sQueue[i2sHandle->queueDriver].data +=
            privateHandle->enqueuedBytes[privateHandle->enqueuedBytesStart];
        privateHandle->enqueuedBytes[privateHandle->enqueuedBytesStart] = 0U;
        privateHandle->enqueuedBytesStart = (privateHandle->enqueuedBytesStart + 1U) % DMA_DESCRIPTORS;
        privateHandle->dmaDescriptorsUsed--;
    }

    if (i2sHandle->i2sQueue[i2sHandle->queueDriver].dataSize == 0U)
    {
        /* Entire user buffer sent or received - advance to next one */
        i2sHandle->i2sQueue[i2sHandle->queueDriver].data = NULL;
        i2sHandle->queueDriver                           = (i2sHandle->queueDriver + 1U) % I2S_NUM_BUFFERS;
        /* Notify user about buffer completion */
        if (i2sHandle->completionCallback)
        {
            (i2sHandle->completionCallback)(base, i2sHandle, kStatus_I2S_BufferComplete, i2sHandle->userData);
        }
    }
    /* check next buffer queue is avaliable or not */
    if (i2sHandle->i2sQueue[i2sHandle->queueDriver].dataSize == 0U)
    {
        /* All user buffers processed */
        I2S_TransferAbortDMA(base, i2sHandle);
    }
    else
    {
        /* Enqueue another user buffer to DMA if it could not be done when in I2S_Rx/TxTransferSendDMA */
        I2S_AddTransferDMA(base, i2sHandle);
    }
}
