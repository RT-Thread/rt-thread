/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexio_uart_dma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexio_uart_dma"
#endif

/*<! @brief Structure definition for DMA callback param pass in. */
typedef struct _flexio_uart_dma_private_handle
{
    FLEXIO_UART_Type *base;
    flexio_uart_dma_handle_t *handle;
} flexio_uart_dma_private_handle_t;

/*<! @brief uart transfer state. */
enum _flexio_uart_dma_transfer_states
{
    kFLEXIO_UART_TxIdle, /* TX idle. */
    kFLEXIO_UART_TxBusy, /* TX busy. */
    kFLEXIO_UART_RxIdle, /* RX idle. */
    kFLEXIO_UART_RxBusy  /* RX busy. */
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*< @brief user configurable flexio uart handle count. */
#define FLEXIO_UART_HANDLE_COUNT 2

/*<! Private handle only used for internally. */
static flexio_uart_dma_private_handle_t s_dmaPrivateHandle[FLEXIO_UART_HANDLE_COUNT];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief FLEXIO UART DMA send finished callback function.
 *
 * This function is called when FLEXIO UART DMA send finished. It disables the UART
 * TX DMA request and sends @ref kStatus_FLEXIO_UART_TxIdle to FLEXIO UART callback.
 *
 * @param handle The DMA handle.
 * @param param Callback function parameter.
 */
static void FLEXIO_UART_TransferSendDMACallback(dma_handle_t *handle, void *param);

/*!
 * @brief FLEXIO UART DMA receive finished callback function.
 *
 * This function is called when FLEXIO UART DMA receive finished. It disables the FLEXIO
 * UART RX DMA request and sends @ref kStatus_FLEXIO_UART_RxIdle to UART callback.
 *
 * @param handle The DMA handle.
 * @param param Callback function parameter.
 */
static void FLEXIO_UART_TransferReceiveDMACallback(dma_handle_t *handle, void *param);

/*******************************************************************************
 * Code
 ******************************************************************************/

static void FLEXIO_UART_TransferSendDMACallback(dma_handle_t *handle, void *param)
{
    flexio_uart_dma_private_handle_t *uartPrivateHandle = (flexio_uart_dma_private_handle_t *)param;

    /* Disable UART TX DMA. */
    FLEXIO_UART_EnableTxDMA(uartPrivateHandle->base, false);

    /* Disable interrupt. */
    DMA_DisableInterrupts(handle->base, handle->channel);

    uartPrivateHandle->handle->txState = (uint8_t)kFLEXIO_UART_TxIdle;

    if (uartPrivateHandle->handle->callback != NULL)
    {
        uartPrivateHandle->handle->callback(uartPrivateHandle->base, uartPrivateHandle->handle,
                                            kStatus_FLEXIO_UART_TxIdle, uartPrivateHandle->handle->userData);
    }
}

static void FLEXIO_UART_TransferReceiveDMACallback(dma_handle_t *handle, void *param)
{
    flexio_uart_dma_private_handle_t *uartPrivateHandle = (flexio_uart_dma_private_handle_t *)param;

    /* Disable UART RX DMA. */
    FLEXIO_UART_EnableRxDMA(uartPrivateHandle->base, false);

    /* Disable interrupt. */
    DMA_DisableInterrupts(handle->base, handle->channel);

    uartPrivateHandle->handle->rxState = (uint8_t)kFLEXIO_UART_RxIdle;

    if (uartPrivateHandle->handle->callback != NULL)
    {
        uartPrivateHandle->handle->callback(uartPrivateHandle->base, uartPrivateHandle->handle,
                                            kStatus_FLEXIO_UART_RxIdle, uartPrivateHandle->handle->userData);
    }
}

/*!
 * brief Initializes the FLEXIO_UART handle which is used in transactional functions.
 *
 * param base Pointer to FLEXIO_UART_Type structure.
 * param handle Pointer to flexio_uart_dma_handle_t structure.
 * param callback FlexIO UART callback, NULL means no callback.
 * param userData User callback function data.
 * param txDmaHandle User requested DMA handle for TX DMA transfer.
 * param rxDmaHandle User requested DMA handle for RX DMA transfer.
 * retval kStatus_Success Successfully create the handle.
 * retval kStatus_OutOfRange The FlexIO UART DMA type/handle table out of range.
 */
status_t FLEXIO_UART_TransferCreateHandleDMA(FLEXIO_UART_Type *base,
                                             flexio_uart_dma_handle_t *handle,
                                             flexio_uart_dma_transfer_callback_t callback,
                                             void *userData,
                                             dma_handle_t *txDmaHandle,
                                             dma_handle_t *rxDmaHandle)
{
    assert(handle != NULL);

    dma_transfer_config_t dmaXferConfig;
    uint8_t index = 0;

    /* Find the an empty handle pointer to store the handle. */
    for (index = 0U; index < (uint8_t)FLEXIO_UART_HANDLE_COUNT; index++)
    {
        if (s_dmaPrivateHandle[index].base == NULL)
        {
            s_dmaPrivateHandle[index].base   = base;
            s_dmaPrivateHandle[index].handle = handle;
            break;
        }
    }

    if (index == (uint8_t)FLEXIO_UART_HANDLE_COUNT)
    {
        return kStatus_OutOfRange;
    }

    (void)memset(handle, 0, sizeof(*handle));

    handle->rxState = (uint8_t)kFLEXIO_UART_RxIdle;
    handle->txState = (uint8_t)kFLEXIO_UART_TxIdle;

    handle->callback = callback;
    handle->userData = userData;

    handle->rxDmaHandle = rxDmaHandle;
    handle->txDmaHandle = txDmaHandle;

    /* Set DMA channel configuration. */
    (void)memset(&dmaXferConfig, 0, sizeof(dmaXferConfig));
    dmaXferConfig.srcSize  = kDMA_Transfersize8bits;
    dmaXferConfig.destSize = kDMA_Transfersize8bits;

    /* Configure TX. */
    if (txDmaHandle != NULL)
    {
        DMA_SetCallback(txDmaHandle, FLEXIO_UART_TransferSendDMACallback, &s_dmaPrivateHandle[index]);

        DMA_ResetChannel(txDmaHandle->base, txDmaHandle->channel);

        dmaXferConfig.destAddr            = FLEXIO_UART_GetTxDataRegisterAddress(base);
        dmaXferConfig.enableSrcIncrement  = true;
        dmaXferConfig.enableDestIncrement = false;
        DMA_SetTransferConfig(txDmaHandle->base, txDmaHandle->channel, &dmaXferConfig);
    }

    /* Configure RX. */
    if (rxDmaHandle != NULL)
    {
        DMA_SetCallback(rxDmaHandle, FLEXIO_UART_TransferReceiveDMACallback, &s_dmaPrivateHandle[index]);

        DMA_ResetChannel(rxDmaHandle->base, rxDmaHandle->channel);

        dmaXferConfig.destAddr            = 0U;
        dmaXferConfig.srcAddr             = FLEXIO_UART_GetRxDataRegisterAddress(base);
        dmaXferConfig.enableSrcIncrement  = false;
        dmaXferConfig.enableDestIncrement = true;
        DMA_SetTransferConfig(rxDmaHandle->base, rxDmaHandle->channel, &dmaXferConfig);
    }

    return kStatus_Success;
}

/*!
 * brief Sends data using DMA.
 *
 * This function send data using DMA. This is non-blocking function, which returns
 * right away. When all data is sent out, the send callback function is called.
 *
 * param base Pointer to FLEXIO_UART_Type structure
 * param handle Pointer to flexio_uart_dma_handle_t structure
 * param xfer FLEXIO_UART DMA transfer structure, see #flexio_uart_transfer_t.
 * retval kStatus_Success if succeed, others failed.
 * retval kStatus_FLEXIO_UART_TxBusy Previous transfer on going.
 */
status_t FLEXIO_UART_TransferSendDMA(FLEXIO_UART_Type *base,
                                     flexio_uart_dma_handle_t *handle,
                                     flexio_uart_transfer_t *xfer)
{
    assert(handle->txDmaHandle != NULL);

    status_t status;

    /* Return error if xfer invalid. */
    if ((0U == xfer->dataSize) || (NULL == xfer->data))
    {
        return kStatus_InvalidArgument;
    }

    /* If previous TX not finished. */
    if ((uint8_t)kFLEXIO_UART_TxBusy == handle->txState)
    {
        status = kStatus_FLEXIO_UART_TxBusy;
    }
    else
    {
        handle->txState       = (uint8_t)kFLEXIO_UART_TxBusy;
        handle->txDataSizeAll = xfer->dataSize;

        /* Set transfer data address and data size. */
        DMA_SetSourceAddress(handle->txDmaHandle->base, handle->txDmaHandle->channel, (uint32_t)xfer->data);
        DMA_SetTransferSize(handle->txDmaHandle->base, handle->txDmaHandle->channel, xfer->dataSize);

        /* Enable FLEXIO UART TX DMA. */
        FLEXIO_UART_EnableTxDMA(base, true);

        /* Enable DMA transfer complete interrupt and start transfer. */
        DMA_EnableInterrupts(handle->txDmaHandle->base, handle->txDmaHandle->channel);
        DMA_EnableChannelRequest(handle->txDmaHandle->base, handle->txDmaHandle->channel);

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Receives data using DMA.
 *
 * This function receives data using DMA. This is non-blocking function, which returns
 * right away. When all data is received, the receive callback function is called.
 *
 * param base Pointer to FLEXIO_UART_Type structure
 * param handle Pointer to flexio_uart_dma_handle_t structure
 * param xfer FLEXIO_UART DMA transfer structure, see #flexio_uart_transfer_t.
 * retval kStatus_Success if succeed, others failed.
 * retval kStatus_FLEXIO_UART_RxBusy Previous transfer on going.
 */
status_t FLEXIO_UART_TransferReceiveDMA(FLEXIO_UART_Type *base,
                                        flexio_uart_dma_handle_t *handle,
                                        flexio_uart_transfer_t *xfer)
{
    assert(handle->rxDmaHandle != NULL);

    status_t status;

    /* Return error if xfer invalid. */
    if ((0U == xfer->dataSize) || (NULL == xfer->data))
    {
        return kStatus_InvalidArgument;
    }

    /* If previous RX not finished. */
    if ((uint8_t)kFLEXIO_UART_RxBusy == handle->rxState)
    {
        status = kStatus_FLEXIO_UART_RxBusy;
    }
    else
    {
        handle->rxState       = (uint8_t)kFLEXIO_UART_RxBusy;
        handle->rxDataSizeAll = xfer->dataSize;

        /* Set transfer data address and data size. */
        DMA_SetDestinationAddress(handle->rxDmaHandle->base, handle->rxDmaHandle->channel, (uint32_t)xfer->data);
        DMA_SetTransferSize(handle->rxDmaHandle->base, handle->rxDmaHandle->channel, xfer->dataSize);

        /* Enable FLEXIO UART RX DMA. */
        FLEXIO_UART_EnableRxDMA(base, true);

        /* Enable DMA transfer complete interrupt and start transfer. */
        DMA_EnableInterrupts(handle->rxDmaHandle->base, handle->rxDmaHandle->channel);
        DMA_EnableChannelRequest(handle->rxDmaHandle->base, handle->rxDmaHandle->channel);

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Aborts the sent data which using DMA.
 *
 * This function aborts the sent data which using DMA.
 *
 * param base Pointer to FLEXIO_UART_Type structure
 * param handle Pointer to flexio_uart_dma_handle_t structure
 */
void FLEXIO_UART_TransferAbortSendDMA(FLEXIO_UART_Type *base, flexio_uart_dma_handle_t *handle)
{
    assert(handle->txDmaHandle != NULL);

    /* Disable FLEXIO UART TX DMA. */
    FLEXIO_UART_EnableTxDMA(base, false);

    /* Stop transfer. */
    DMA_StopTransfer(handle->txDmaHandle);

    /* Write DMA->DSR[DONE] to abort transfer and clear status. */
    DMA_ClearChannelStatusFlags(handle->txDmaHandle->base, handle->txDmaHandle->channel,
                                (uint32_t)kDMA_TransactionsDoneFlag);

    handle->txState = (uint8_t)kFLEXIO_UART_TxIdle;
}

/*!
 * brief Aborts the receive data which using DMA.
 *
 * This function aborts the receive data which using DMA.
 *
 * param base Pointer to FLEXIO_UART_Type structure
 * param handle Pointer to flexio_uart_dma_handle_t structure
 */
void FLEXIO_UART_TransferAbortReceiveDMA(FLEXIO_UART_Type *base, flexio_uart_dma_handle_t *handle)
{
    assert(handle->rxDmaHandle != NULL);

    /* Disable FLEXIO UART RX DMA. */
    FLEXIO_UART_EnableRxDMA(base, false);

    /* Stop transfer. */
    DMA_StopTransfer(handle->rxDmaHandle);

    /* Write DMA->DSR[DONE] to abort transfer and clear status. */
    DMA_ClearChannelStatusFlags(handle->rxDmaHandle->base, handle->rxDmaHandle->channel,
                                (uint32_t)kDMA_TransactionsDoneFlag);

    handle->rxState = (uint8_t)kFLEXIO_UART_RxIdle;
}

/*!
 * brief Gets the number of bytes sent out.
 *
 * This function gets the number of bytes sent out.
 *
 * param base Pointer to FLEXIO_UART_Type structure
 * param handle Pointer to flexio_uart_dma_handle_t structure
 * param count Number of bytes sent so far by the non-blocking transaction.
 * retval kStatus_NoTransferInProgress transfer has finished or no transfer in progress.
 * retval kStatus_Success Successfully return the count.
 */
status_t FLEXIO_UART_TransferGetSendCountDMA(FLEXIO_UART_Type *base, flexio_uart_dma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);
    assert(handle->txDmaHandle != NULL);
    assert(count != NULL);

    if ((uint8_t)kFLEXIO_UART_TxIdle == handle->txState)
    {
        return kStatus_NoTransferInProgress;
    }

    *count = handle->txDataSizeAll - DMA_GetRemainingBytes(handle->txDmaHandle->base, handle->txDmaHandle->channel);

    return kStatus_Success;
}

/*!
 * brief Gets the number of bytes received.
 *
 * This function gets the number of bytes received.
 *
 * param base Pointer to FLEXIO_UART_Type structure
 * param handle Pointer to flexio_uart_dma_handle_t structure
 * param count Number of bytes received so far by the non-blocking transaction.
 * retval kStatus_NoTransferInProgress transfer has finished or no transfer in progress.
 * retval kStatus_Success Successfully return the count.
 */
status_t FLEXIO_UART_TransferGetReceiveCountDMA(FLEXIO_UART_Type *base, flexio_uart_dma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);
    assert(handle->rxDmaHandle != NULL);
    assert(count != NULL);

    if ((uint8_t)kFLEXIO_UART_RxIdle == handle->rxState)
    {
        return kStatus_NoTransferInProgress;
    }

    *count = handle->rxDataSizeAll - DMA_GetRemainingBytes(handle->rxDmaHandle->base, handle->rxDmaHandle->channel);

    return kStatus_Success;
}
