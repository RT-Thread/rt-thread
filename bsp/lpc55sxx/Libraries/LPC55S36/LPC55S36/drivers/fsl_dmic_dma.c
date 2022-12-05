/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dmic_dma.h"
#include "fsl_dmic.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dmic_dma"
#endif

/*! @brief _dmic_dma_states_t DMIC transfer state, which is used for DMIC transactiaonl APIs' internal state. */
enum
{
    kDMIC_Idle = 0x0, /*!< DMIC is idle state */
    kDMIC_Busy        /*!< DMIC is busy tranferring data. */
};
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ********************************************************************************/

static void DMIC_TransferReceiveDMACallback(dma_handle_t *handle, void *param, bool transferDone, uint32_t intmode)
{
    assert(handle != NULL);
    assert(param != NULL);

    dmic_dma_handle_t *dmicHandle = (dmic_dma_handle_t *)param;

    /* if no link transfer, dmic status set to IDLE. */
    if (dmicHandle->desLink == NULL)
    {
        dmicHandle->state = kDMIC_Idle;
    }

    if (dmicHandle->callback != NULL)
    {
        dmicHandle->callback(dmicHandle->base, dmicHandle, kStatus_DMIC_Idle, dmicHandle->userData);
    }
}

/*!
 * brief Install DMA descriptor memory.
 *
 * This function used to register DMA descriptor memory for linked transfer, a typical case is ping pong
 * transfer which will request more than one DMA descriptor memory space.
 * User should be take care about the address of DMA descriptor pool which required align with 512BYTE.
 *
 * param handle Pointer to DMA channel transfer handle.
 * param linkAddr DMA link descriptor address.
 * param num DMA link descriptor number.
 */
void DMIC_InstallDMADescriptorMemory(dmic_dma_handle_t *handle, void *linkAddr, size_t linkNum)
{
    assert(handle != NULL);

    handle->desLink = (dma_descriptor_t *)linkAddr;
    handle->linkNum = linkNum;
}

/*!
 * brief Initializes the DMIC handle which is used in transactional functions.
 * param base DMIC peripheral base address.
 * param handle Pointer to dmic_dma_handle_t structure.
 * param callback Callback function.
 * param userData User data.
 * param rxDmaHandle User-requested DMA handle for RX DMA transfer.
 */
status_t DMIC_TransferCreateHandleDMA(DMIC_Type *base,
                                      dmic_dma_handle_t *handle,
                                      dmic_dma_transfer_callback_t callback,
                                      void *userData,
                                      dma_handle_t *rxDmaHandle)
{
    assert(NULL != base);
    assert(NULL != handle);
    assert(NULL != rxDmaHandle);

    (void)memset(handle, 0, sizeof(*handle));

    handle->callback    = callback;
    handle->userData    = userData;
    handle->rxDmaHandle = rxDmaHandle;

    /* Set DMIC state to idle */
    handle->state = kDMIC_Idle;
    /* register callback. */
    DMA_SetCallback(rxDmaHandle, DMIC_TransferReceiveDMACallback, handle);

    return kStatus_Success;
}

/*!
 * brief Receives data using DMA.
 *
 * This function receives data using DMA. This is a non-blocking function, which returns
 * right away. When all data is received, the receive callback function is called.
 *
 * param base USART peripheral base address.
 * param handle Pointer to usart_dma_handle_t structure.
 * param xfer DMIC DMA transfer structure. See #dmic_transfer_t.
 * param dmic_channel DMIC start channel number
 * retval kStatus_Success
 */
status_t DMIC_TransferReceiveDMA(DMIC_Type *base, dmic_dma_handle_t *handle, dmic_transfer_t *xfer, uint32_t channel)
{
    assert(handle != NULL);
    assert(handle->rxDmaHandle != NULL);
    assert(xfer != NULL);

    dma_channel_config_t transferConfig = {0U};
    uint32_t srcAddr                    = (uint32_t)&base->CHANNEL[channel].FIFO_DATA;
    uint32_t desNum                     = 0U;
    dma_descriptor_t *linkDesc          = (handle->desLink != NULL) ? &(handle->desLink[desNum + 1U]) : NULL;
    dmic_transfer_t *currentTransfer    = xfer->linkTransfer;
    bool loopEnd = false, intA = true;
    uint32_t interleaveWidth = kDMA_AddressInterleave0xWidth;

    if ((xfer->linkTransfer != NULL) && (handle->desLink == NULL))
    {
        return kStatus_InvalidArgument;
    }

    if (handle->state == (uint8_t)kDMIC_Busy)
    {
        return kStatus_DMIC_Busy;
    }

    while (currentTransfer != NULL)
    {
        /* set up linked descriptor */
        DMA_SetupDescriptor(&handle->desLink[desNum],
                            DMA_CHANNEL_XFER(currentTransfer->linkTransfer != NULL ? 1UL : 0UL, 0UL, intA, !intA,
                                             currentTransfer->dataWidth, interleaveWidth,
                                             currentTransfer->dataAddrInterleaveSize, currentTransfer->dataSize),
                            (uint32_t *)srcAddr, currentTransfer->data, linkDesc);

        intA = intA == true ? false : true;
        /* break for wrap transfer */
        if (loopEnd)
        {
            break;
        }

        if (++desNum == handle->linkNum)
        {
            return kStatus_Fail;
        }

        linkDesc = &handle->desLink[desNum + 1U];

        currentTransfer = currentTransfer->linkTransfer;
        /* if current transfer need wrap, then create one more descriptor, since the first descriptor cannot be used
         * anymore, this is
         * the limitation of the DMA module
         */
        if (currentTransfer == xfer)
        {
            linkDesc = handle->desLink; /* point to the first one */
            loopEnd  = true;
            continue;
        }
    }
    /* transferSize make sense to non link transfer only */
    handle->transferSize += xfer->dataSize;

    /* code to keep compatibility for the case that not use link transfer */
    if ((xfer->dataWidth != (uint8_t)kDMA_Transfer16BitWidth) && (xfer->dataWidth != (uint8_t)kDMA_Transfer32BitWidth))
    {
        xfer->dataWidth = kDMA_Transfer16BitWidth; /* use 16bit width as default value */
    }
    /* code to keep compatibility for the case that not use link transfer*/
    if ((xfer->dataAddrInterleaveSize == (uint8_t)kDMA_AddressInterleave0xWidth) ||
        (xfer->dataAddrInterleaveSize > (uint8_t)kDMA_AddressInterleave4xWidth))
    {
        xfer->dataAddrInterleaveSize = kDMA_AddressInterleave1xWidth; /* use interleave1Xwidth as default value. */
    }

    /* prepare channel tranfer */
    DMA_PrepareChannelTransfer(
        &transferConfig, (uint32_t *)srcAddr, xfer->data,
        DMA_CHANNEL_XFER(xfer->linkTransfer == NULL ? 0UL : 1UL, 0UL, intA, !intA, xfer->dataWidth, interleaveWidth,
                         xfer->dataAddrInterleaveSize, xfer->dataSize),
        kDMA_PeripheralToMemory, NULL, handle->desLink);
    /* Submit transfer. */
    if (DMA_SubmitChannelTransfer(handle->rxDmaHandle, &transferConfig) == kStatus_DMA_Busy)
    {
        return kStatus_DMIC_Busy;
    }

    /* enable channel */
    DMIC_EnableChannnel(DMIC0, 1UL << channel);
    /* enable dmic channel dma request */
    DMIC_EnableChannelDma(DMIC0, (dmic_channel_t)channel, true);

    /* start transfer */
    DMA_StartTransfer(handle->rxDmaHandle);

    handle->state = kDMIC_Busy;

    return kStatus_Success;
}

/*!
 * brief Aborts the received data using DMA.
 *
 * This function aborts the received data using DMA.
 *
 * param base DMIC peripheral base address
 * param handle Pointer to dmic_dma_handle_t structure
 */
void DMIC_TransferAbortReceiveDMA(DMIC_Type *base, dmic_dma_handle_t *handle)
{
    assert(NULL != handle);
    assert(NULL != handle->rxDmaHandle);

    /* Stop transfer. */
    DMA_AbortTransfer(handle->rxDmaHandle);
    handle->state = kDMIC_Idle;
}

/*!
 * brief Get the number of bytes that have been received.
 *
 * This function gets the number of bytes that have been received.
 * Note: Do not trying to use this api to get the number of received bytes, it make no sense to link transfer.
 * param base DMIC peripheral base address.
 * param handle DMIC handle pointer.
 * param count Receive bytes count.
 * retval kStatus_NoTransferInProgress No receive in progress.
 * retval kStatus_InvalidArgument Parameter is invalid.
 * retval kStatus_Success Get successfully through the parameter count;
 */
status_t DMIC_TransferGetReceiveCountDMA(DMIC_Type *base, dmic_dma_handle_t *handle, uint32_t *count)
{
    assert(handle != NULL);
    assert(handle->rxDmaHandle != NULL);
    assert(count != NULL);

    if ((uint8_t)kDMIC_Idle == handle->state)
    {
        return kStatus_NoTransferInProgress;
    }

    *count = handle->transferSize - DMA_GetRemainingBytes(handle->rxDmaHandle->base, handle->rxDmaHandle->channel);

    return kStatus_Success;
}
