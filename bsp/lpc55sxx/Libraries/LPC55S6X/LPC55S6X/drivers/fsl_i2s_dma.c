/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
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
#define DMA_DESCRIPTORS        (2U)

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
    kI2S_DmaStateIdle = 0x0U,      /*!< I2S is in idle state */
    kI2S_DmaStateTx,               /*!< I2S is busy transmitting data */
    kI2S_DmaStateRx,               /*!< I2S is busy receiving data */
    kI2S_DmaStateBusyLoopTransfer, /*!< I2S is busy loop transfer */
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
#if (defined(CPU_MIMXRT685SEVKA_dsp) || defined(CPU_MIMXRT685SFVKB_dsp))
AT_NONCACHEABLE_SECTION_ALIGN(static dma_descriptor_t s_DmaDescriptors[DMA_DESCRIPTORS * FSL_FEATURE_SOC_I2S_COUNT],
                              FSL_FEATURE_DMA_LINK_DESCRIPTOR_ALIGN_SIZE);
#else
SDK_ALIGN(static dma_descriptor_t s_DmaDescriptors[DMA_DESCRIPTORS * FSL_FEATURE_SOC_I2S_COUNT],
          FSL_FEATURE_DMA_LINK_DESCRIPTOR_ALIGN_SIZE);
#endif

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

    assert(handle != NULL);
    if (handle == NULL)
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

    if (handle->i2sQueue[handle->queueUser].dataSize != 0UL)
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
    if (handle->state != (uint32_t)kI2S_DmaStateIdle)
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
    assert(handle != NULL);
    assert(dmaHandle != NULL);

    uint32_t instance                       = I2S_GetInstance(base);
    i2s_dma_private_handle_t *privateHandle = &(s_DmaPrivateHandle[instance]);

    (void)memset(handle, 0, sizeof(*handle));
    handle->state              = (uint32_t)kI2S_DmaStateIdle;
    handle->dmaHandle          = dmaHandle;
    handle->completionCallback = callback;
    handle->userData           = userData;

    handle->bytesPerFrame = (uint8_t)((((base->CFG1 & I2S_CFG1_DATALEN_MASK) >> I2S_CFG1_DATALEN_SHIFT) + 1U) / 8U);
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

    (void)memset(privateHandle, 0, sizeof(*privateHandle));
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
    if (handle->state == (uint32_t)kI2S_DmaStateIdle)
    {
        handle->state = (uint32_t)kI2S_DmaStateTx;
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
    assert(handle != NULL);
    assert(handle->dmaHandle != NULL);

    uint32_t instance                       = I2S_GetInstance(base);
    i2s_dma_private_handle_t *privateHandle = &(s_DmaPrivateHandle[instance]);

    I2S_DisableDMAInterrupts(handle);

    /* Abort operation */
    DMA_AbortTransfer(handle->dmaHandle);

    if (handle->state == (uint32_t)kI2S_DmaStateTx)
    {
        /* Disable TX */
        I2S_TxEnableDMA(base, false);
    }
    else
    {
        /* Disable RX */
        I2S_RxEnableDMA(base, false);
    }

    I2S_Disable(base);

    /* Reset state */
    handle->state = (uint32_t)kI2S_DmaStateIdle;

    /* Clear transfer queue */
    (void)memset((void *)&(handle->i2sQueue), 0, sizeof(handle->i2sQueue));
    handle->queueDriver = 0U;
    handle->queueUser   = 0U;

    /* Clear internal state */
    (void)memset((void *)&(privateHandle->descriptorQueue), 0, sizeof(privateHandle->descriptorQueue));
    (void)memset((void *)&(privateHandle->enqueuedBytes), 0, sizeof(privateHandle->enqueuedBytes));
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
    if (handle->state == (uint32_t)kI2S_DmaStateIdle)
    {
        handle->state = (uint32_t)kI2S_DmaStateRx;
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
    assert(transfer != NULL);

    uint16_t transferBytes;

    if (transfer->dataSize >= (2UL * DMA_MAX_TRANSFER_BYTES))
    {
        transferBytes = DMA_MAX_TRANSFER_BYTES;
    }
    else if (transfer->dataSize > DMA_MAX_TRANSFER_BYTES)
    {
        transferBytes = (uint16_t)(transfer->dataSize / 2U);
        if ((transferBytes % 4U) != 0U)
        {
            transferBytes -= (transferBytes % 4U);
        }
    }
    else
    {
        transferBytes = (uint16_t)transfer->dataSize;
    }

    return transferBytes;
}

/*!
 * brief Install DMA descriptor memory for loop transfer only.
 *
 * This function used to register DMA descriptor memory for the i2s loop dma transfer.
 *
 * It must be callbed before I2S_TransferSendLoopDMA/I2S_TransferReceiveLoopDMA and after
 * I2S_RxTransferCreateHandleDMA/I2S_TxTransferCreateHandleDMA.
 *
 * User should be take care about the address of DMA descriptor pool which required align with 16BYTE at least.
 *
 * param handle Pointer to i2s DMA transfer handle.
 * param dmaDescriptorAddr DMA descriptor start address.
 * param dmaDescriptorNum DMA descriptor number.
 */
void I2S_TransferInstallLoopDMADescriptorMemory(i2s_dma_handle_t *handle,
                                                void *dmaDescriptorAddr,
                                                size_t dmaDescriptorNum)
{
    assert(handle != NULL);
    assert((((uint32_t)(uint32_t *)dmaDescriptorAddr) & ((uint32_t)FSL_FEATURE_DMA_LINK_DESCRIPTOR_ALIGN_SIZE - 1UL)) ==
           0UL);

    handle->i2sLoopDMADescriptor    = (dma_descriptor_t *)dmaDescriptorAddr;
    handle->i2sLoopDMADescriptorNum = dmaDescriptorNum;
}

static status_t I2S_TransferLoopDMA(I2S_Type *base,
                                    i2s_dma_handle_t *handle,
                                    i2s_transfer_t *xfer,
                                    uint32_t loopTransferCount)
{
    assert(handle != NULL);
    assert(handle->dmaHandle != NULL);
    assert(xfer != NULL);

    uint32_t *srcAddr = NULL, *destAddr = NULL, srcInc = 4UL, destInc = 4UL;
    i2s_transfer_t *currentTransfer = xfer;
    bool intA                       = true;

    if (handle->i2sLoopDMADescriptor == NULL)
    {
        return kStatus_InvalidArgument;
    }

    if (handle->state == (uint32_t)kI2S_DmaStateBusyLoopTransfer)
    {
        return kStatus_I2S_Busy;
    }

    for (uint32_t i = 0U; i < loopTransferCount; i++)
    {
        currentTransfer = &xfer[i];

        if ((currentTransfer->data == NULL) || (currentTransfer->dataSize == 0U) ||
            (i >= handle->i2sLoopDMADescriptorNum) ||
            (currentTransfer->dataSize / handle->bytesPerFrame > DMA_MAX_TRANSFER_COUNT))
        {
            return kStatus_InvalidArgument;
        }

        if (handle->state == (uint32_t)kI2S_DmaStateTx)
        {
            srcAddr  = (uint32_t *)(uint32_t)currentTransfer->data;
            destAddr = (uint32_t *)(uint32_t)(&(base->FIFOWR));
            srcInc   = 1U;
            destInc  = 0UL;
        }
        else
        {
            srcAddr  = (uint32_t *)(uint32_t)(&(base->FIFORD));
            destAddr = (uint32_t *)(uint32_t)currentTransfer->data;
            srcInc   = 0U;
            destInc  = 1UL;
        }

        intA = intA == true ? false : true;

        if (i == (loopTransferCount - 1U))
        {
            /* set up linked descriptor */
            DMA_SetupDescriptor(&handle->i2sLoopDMADescriptor[i],
                                DMA_CHANNEL_XFER(1UL, 0UL, intA, !intA, handle->bytesPerFrame, srcInc, destInc,
                                                 currentTransfer->dataSize),
                                srcAddr, destAddr, &handle->i2sLoopDMADescriptor[0U]);
        }
        else
        {
            /* set up linked descriptor */
            DMA_SetupDescriptor(&handle->i2sLoopDMADescriptor[i],
                                DMA_CHANNEL_XFER(1UL, 0UL, intA, !intA, handle->bytesPerFrame, srcInc, destInc,
                                                 currentTransfer->dataSize),
                                srcAddr, destAddr, &handle->i2sLoopDMADescriptor[i + 1U]);
        }
    }

    /* transferSize make sense to non link transfer only */
    if (handle->state == (uint32_t)kI2S_DmaStateTx)
    {
        srcAddr  = (uint32_t *)(uint32_t)xfer->data;
        destAddr = (uint32_t *)(uint32_t)(&(base->FIFOWR));
        srcInc   = 1U;
        destInc  = 0UL;
    }
    else
    {
        srcAddr  = (uint32_t *)(uint32_t)(&(base->FIFORD));
        destAddr = (uint32_t *)(uint32_t)xfer->data;
        srcInc   = 0U;
        destInc  = 1UL;
    }

    DMA_SubmitChannelTransferParameter(
        handle->dmaHandle,
        DMA_CHANNEL_XFER(1UL, 0UL, 0UL, 1UL, handle->bytesPerFrame, srcInc, destInc, (uint32_t)xfer->dataSize), srcAddr,
        destAddr, (void *)&handle->i2sLoopDMADescriptor[1U]);

    /* Submit and start initial DMA transfer */
    if (handle->state == (uint32_t)kI2S_DmaStateTx)
    {
        I2S_TxEnableDMA(base, true);
    }
    else
    {
        I2S_RxEnableDMA(base, true);
    }
    DMA_EnableChannelPeriphRq(handle->dmaHandle->base, handle->dmaHandle->channel);
    /* start transfer */
    DMA_StartTransfer(handle->dmaHandle);
    I2S_Enable(base);

    handle->state = (uint32_t)kI2S_DmaStateBusyLoopTransfer;

    return kStatus_Success;
}

/*!
 * brief Send loop transfer data using DMA.
 *
 * This function receives data using DMA. This is a non-blocking function, which returns
 * right away. When all data is received, the receive callback function is called.
 *
 * This function support loop transfer, such as A->B->...->A, the loop transfer chain
 * will be converted into a chain of descriptor and submit to dma.
 * Application must be aware of that the more counts of the loop transfer, then more DMA descriptor memory required,
 * user can use function I2S_InstallDMADescriptorMemory to register the dma descriptor memory.
 *
 * As the DMA support maximum 1024 transfer count, so application must be aware of that this transfer function support
 * maximum 1024 samples in each transfer, otherwise assert error or error status will be returned. Once the loop
 * transfer start, application can use function I2S_TransferAbortDMA to stop the loop transfer.
 *
 * param base I2S peripheral base address.
 * param handle Pointer to usart_dma_handle_t structure.
 * param xfer I2S DMA transfer structure. See #i2s_transfer_t.
 * param i2s_channel I2S start channel number
 * retval kStatus_Success
 */
status_t I2S_TransferSendLoopDMA(I2S_Type *base,
                                 i2s_dma_handle_t *handle,
                                 i2s_transfer_t *xfer,
                                 uint32_t loopTransferCount)
{
    assert(handle != NULL);
    assert(handle->i2sLoopDMADescriptor != NULL);

    handle->state = (uint32_t)kI2S_DmaStateTx;

    return I2S_TransferLoopDMA(base, handle, xfer, loopTransferCount);
}

/*!
 * brief Receive loop transfer data using DMA.
 *
 * This function receives data using DMA. This is a non-blocking function, which returns
 * right away. When all data is received, the receive callback function is called.
 *
 * This function support loop transfer, such as A->B->...->A, the loop transfer chain
 * will be converted into a chain of descriptor and submit to dma.
 * Application must be aware of that the more counts of the loop transfer, then more DMA descriptor memory required,
 * user can use function I2S_InstallDMADescriptorMemory to register the dma descriptor memory.
 *
 * As the DMA support maximum 1024 transfer count, so application must be aware of that this transfer function support
 * maximum 1024 samples in each transfer, otherwise assert error or error status will be returned. Once the loop
 * transfer start, application can use function I2S_TransferAbortDMA to stop the loop transfer.
 *
 * param base I2S peripheral base address.
 * param handle Pointer to usart_dma_handle_t structure.
 * param xfer I2S DMA transfer structure. See #i2s_transfer_t.
 * param i2s_channel I2S start channel number
 * retval kStatus_Success
 */
status_t I2S_TransferReceiveLoopDMA(I2S_Type *base,
                                    i2s_dma_handle_t *handle,
                                    i2s_transfer_t *xfer,
                                    uint32_t loopTransferCount)
{
    assert(handle != NULL);
    assert(handle->i2sLoopDMADescriptor != NULL);

    handle->state = (uint32_t)kI2S_DmaStateRx;

    return I2S_TransferLoopDMA(base, handle, xfer, loopTransferCount);
}

static status_t I2S_StartTransferDMA(I2S_Type *base, i2s_dma_handle_t *handle)
{
    uint32_t instance                       = I2S_GetInstance(base);
    i2s_dma_private_handle_t *privateHandle = &(s_DmaPrivateHandle[instance]);
    volatile i2s_transfer_t *transfer       = &(privateHandle->descriptorQueue[privateHandle->queueDescriptor]);
    uint16_t transferBytes                  = I2S_GetTransferBytes(transfer);
    uint32_t i                              = 0U;
    uint32_t xferConfig                     = 0U;
    uint32_t *srcAddr = NULL, *destAddr = NULL, srcInc = 4UL, destInc = 4UL;

    if (handle->state == (uint32_t)kI2S_DmaStateTx)
    {
        srcAddr  = (uint32_t *)(uint32_t)transfer->data;
        destAddr = (uint32_t *)(uint32_t)(&(base->FIFOWR));
        srcInc   = 1U;
        destInc  = 0UL;
    }
    else
    {
        srcAddr  = (uint32_t *)(uint32_t)(&(base->FIFORD));
        destAddr = (uint32_t *)(uint32_t)transfer->data;
        srcInc   = 0U;
        destInc  = 1UL;
    }
    /* Initial descriptor is stored in another place in memory, but treat it as another descriptor for simplicity */
    privateHandle->dmaDescriptorsUsed = 1U;
    privateHandle->intA               = false;

    /* submit transfer parameter directly */
    xferConfig = DMA_CHANNEL_XFER(1UL, 0UL, 0UL, 1UL, handle->bytesPerFrame, srcInc, destInc, (uint32_t)transferBytes);

    DMA_SubmitChannelTransferParameter(handle->dmaHandle, xferConfig, srcAddr, destAddr,
                                       (void *)&(s_DmaDescriptors[(instance * DMA_DESCRIPTORS) + 0U]));

    privateHandle->enqueuedBytes[privateHandle->enqueuedBytesEnd] = transferBytes;
    privateHandle->enqueuedBytesEnd = (privateHandle->enqueuedBytesEnd + 1U) % DMA_DESCRIPTORS;

    transfer->dataSize -= transferBytes;
    transfer->data = (uint8_t *)((uint32_t)transfer->data + transferBytes);

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
        /* DMA_CHANNEL_XFER(1UL, 0UL, 0UL, 0UL, sizeof(uint32_t), 0U, 0U, 8U) = 0x10203UL  */
        DMA_SetupDescriptor(
            &(s_DmaDescriptors[(instance * DMA_DESCRIPTORS) + i]), 0x10203UL,
            ((handle->state == (uint32_t)kI2S_DmaStateTx) ? &s_DummyBufferTx : (uint32_t *)(uint32_t)(&(base->FIFORD))),
            ((handle->state == (uint32_t)kI2S_DmaStateTx) ? (uint32_t *)(uint32_t)(&(base->FIFOWR)) : &s_DummyBufferRx),
            &(s_DmaDescriptors[(instance * DMA_DESCRIPTORS) + ((i + 1U) % DMA_DESCRIPTORS)]));
    }

    /* Submit and start initial DMA transfer */
    if (handle->state == (uint32_t)kI2S_DmaStateTx)
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
    bool intA           = false;
    uint32_t *srcAddr = NULL, *destAddr = NULL, srcInc = 4UL, destInc = 4UL;

    instance      = I2S_GetInstance(base);
    privateHandle = &(s_DmaPrivateHandle[instance]);

    while (privateHandle->dmaDescriptorsUsed < DMA_DESCRIPTORS)
    {
        transfer = &(privateHandle->descriptorQueue[privateHandle->queueDescriptor]);
        intA     = privateHandle->intA;
        if (transfer->dataSize == 0U)
        {
            /* Nothing to be added */
            return;
        }

        if (handle->state == (uint32_t)kI2S_DmaStateTx)
        {
            srcAddr  = (uint32_t *)(uint32_t)transfer->data;
            destAddr = (uint32_t *)(uint32_t)(&(base->FIFOWR));
            srcInc   = 1U;
            destInc  = 0UL;
        }
        else
        {
            srcAddr  = (uint32_t *)(uint32_t)(&(base->FIFORD));
            destAddr = (uint32_t *)(uint32_t)transfer->data;
            srcInc   = 0U;
            destInc  = 1UL;
        }

        /* Determine currently configured descriptor and the other which it will link to */
        descriptor                = &(s_DmaDescriptors[(instance * DMA_DESCRIPTORS) + privateHandle->descriptor]);
        privateHandle->descriptor = (privateHandle->descriptor + 1U) % DMA_DESCRIPTORS;
        nextDescriptor            = &(s_DmaDescriptors[(instance * DMA_DESCRIPTORS) + privateHandle->descriptor]);

        transferBytes                                                 = I2S_GetTransferBytes(transfer);
        privateHandle->enqueuedBytes[privateHandle->enqueuedBytesEnd] = transferBytes;
        privateHandle->enqueuedBytesEnd = (privateHandle->enqueuedBytesEnd + 1U) % DMA_DESCRIPTORS;

        xferConfig =
            DMA_CHANNEL_XFER(1UL, 0UL, !intA, intA, handle->bytesPerFrame, srcInc, destInc, (uint32_t)transferBytes);

        DMA_SetupDescriptor(descriptor, xferConfig, srcAddr, destAddr, nextDescriptor);

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
    uint8_t queueDriverIndex                = i2sHandle->queueDriver;
    uint32_t enqueueBytes                   = privateHandle->enqueuedBytes[privateHandle->enqueuedBytesStart];
    uint32_t queueDataAddr                  = (uint32_t)i2sHandle->i2sQueue[queueDriverIndex].data;

    if ((!transferDone) || (i2sHandle->state == (uint32_t)kI2S_DmaStateIdle))
    {
        return;
    }

    if (privateHandle->dmaDescriptorsUsed > 0U)
    {
        /* Finished descriptor, decrease amount of data to be processed */

        i2sHandle->i2sQueue[queueDriverIndex].dataSize -= enqueueBytes;
        i2sHandle->i2sQueue[queueDriverIndex].data                      = (uint8_t *)(queueDataAddr + enqueueBytes);
        privateHandle->enqueuedBytes[privateHandle->enqueuedBytesStart] = 0U;
        privateHandle->enqueuedBytesStart = (privateHandle->enqueuedBytesStart + 1U) % DMA_DESCRIPTORS;
        privateHandle->dmaDescriptorsUsed--;
    }

    if (i2sHandle->i2sQueue[queueDriverIndex].dataSize == 0U)
    {
        /* Entire user buffer sent or received - advance to next one */
        i2sHandle->i2sQueue[queueDriverIndex].data = NULL;
        i2sHandle->queueDriver                     = (queueDriverIndex + 1U) % I2S_NUM_BUFFERS;
        /* Notify user about buffer completion */
        if (i2sHandle->completionCallback != NULL)
        {
            (i2sHandle->completionCallback)(base, i2sHandle, kStatus_I2S_BufferComplete, i2sHandle->userData);
        }
    }

    if (i2sHandle->state != (uint32_t)kI2S_DmaStateBusyLoopTransfer)
    {
        /* check next buffer queue is avaliable or not */
        if (i2sHandle->i2sQueue[i2sHandle->queueDriver].dataSize == 0U)
        {
            if (i2sHandle->state == (uint32_t)kI2S_DmaStateTx)
            {
                (void)I2S_EmptyTxFifo(base);
            }
            /* All user buffers processed */
            I2S_TransferAbortDMA(base, i2sHandle);
        }
        else
        {
            /* Enqueue another user buffer to DMA if it could not be done when in I2S_Rx/TxTransferSendDMA */
            I2S_AddTransferDMA(base, i2sHandle);
        }
    }
}
