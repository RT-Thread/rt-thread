/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_uart_dma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.uart_dma"
#endif

/* Array of UART handle. */
#if (defined(UART5))
#define UART_HANDLE_ARRAY_SIZE 6
#else /* UART5 */
#if (defined(UART4))
#define UART_HANDLE_ARRAY_SIZE 5
#else /* UART4 */
#if (defined(UART3))
#define UART_HANDLE_ARRAY_SIZE 4
#else /* UART3 */
#if (defined(UART2))
#define UART_HANDLE_ARRAY_SIZE 3
#else /* UART2 */
#if (defined(UART1))
#define UART_HANDLE_ARRAY_SIZE 2
#else /* UART1 */
#if (defined(UART0))
#define UART_HANDLE_ARRAY_SIZE 1
#else /* UART0 */
#error No UART instance.
#endif /* UART 0 */
#endif /* UART 1 */
#endif /* UART 2 */
#endif /* UART 3 */
#endif /* UART 4 */
#endif /* UART 5 */

/*<! Structure definition for uart_dma_handle_t. The structure is private. */
typedef struct _uart_dma_private_handle
{
    UART_Type *base;
    uart_dma_handle_t *handle;
} uart_dma_private_handle_t;

/* UART DMA transfer handle. */
enum
{
    kUART_TxIdle, /* TX idle. */
    kUART_TxBusy, /* TX busy. */
    kUART_RxIdle, /* RX idle. */
    kUART_RxBusy  /* RX busy. */
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*<! Private handle only used for internally. */
static uart_dma_private_handle_t s_dmaPrivateHandle[UART_HANDLE_ARRAY_SIZE];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief UART DMA send finished callback function.
 *
 * This function is called when UART DMA send finished. It disables the UART
 * TX DMA request and sends @ref kStatus_UART_TxIdle to UART callback.
 *
 * @param handle The DMA handle.
 * @param param Callback function parameter.
 */
static void UART_TransferSendDMACallback(dma_handle_t *handle, void *param);

/*!
 * @brief UART DMA receive finished callback function.
 *
 * This function is called when UART DMA receive finished. It disables the UART
 * RX DMA request and sends @ref kStatus_UART_RxIdle to UART callback.
 *
 * @param handle The DMA handle.
 * @param param Callback function parameter.
 */
static void UART_TransferReceiveDMACallback(dma_handle_t *handle, void *param);

/*******************************************************************************
 * Code
 ******************************************************************************/

static void UART_TransferSendDMACallback(dma_handle_t *handle, void *param)
{
    assert(handle != NULL);
    assert(param != NULL);

    uart_dma_private_handle_t *uartPrivateHandle = (uart_dma_private_handle_t *)param;

    /* Disable UART TX DMA. */
    UART_EnableTxDMA(uartPrivateHandle->base, false);

    /* Disable interrupt. */
    DMA_DisableInterrupts(handle->base, handle->channel);

    /* Enable tx complete interrupt */
    UART_EnableInterrupts(uartPrivateHandle->base, (uint32_t)kUART_TransmissionCompleteInterruptEnable);
}

static void UART_TransferReceiveDMACallback(dma_handle_t *handle, void *param)
{
    assert(handle != NULL);
    assert(param != NULL);

    uart_dma_private_handle_t *uartPrivateHandle = (uart_dma_private_handle_t *)param;

    /* Disable UART RX DMA. */
    UART_EnableRxDMA(uartPrivateHandle->base, false);

    /* Disable interrupt. */
    DMA_DisableInterrupts(handle->base, handle->channel);

    uartPrivateHandle->handle->rxState = (uint8_t)kUART_RxIdle;

    if (uartPrivateHandle->handle->callback != NULL)
    {
        uartPrivateHandle->handle->callback(uartPrivateHandle->base, uartPrivateHandle->handle, kStatus_UART_RxIdle,
                                            uartPrivateHandle->handle->userData);
    }
}

/*!
 * brief Initializes the UART handle which is used in transactional functions and sets the callback.
 *
 * param base UART peripheral base address.
 * param handle Pointer to the uart_dma_handle_t structure.
 * param callback UART callback, NULL means no callback.
 * param userData User callback function data.
 * param rxDmaHandle User requested DMA handle for the RX DMA transfer.
 * param txDmaHandle User requested DMA handle for the TX DMA transfer.
 */
void UART_TransferCreateHandleDMA(UART_Type *base,
                                  uart_dma_handle_t *handle,
                                  uart_dma_transfer_callback_t callback,
                                  void *userData,
                                  dma_handle_t *txDmaHandle,
                                  dma_handle_t *rxDmaHandle)
{
    assert(handle != NULL);

    uint32_t instance = UART_GetInstance(base);

    (void)memset(handle, 0, sizeof(*handle));

    s_dmaPrivateHandle[instance].base   = base;
    s_dmaPrivateHandle[instance].handle = handle;

    handle->rxState = (uint8_t)kUART_RxIdle;
    handle->txState = (uint8_t)kUART_TxIdle;

    handle->callback = callback;
    handle->userData = userData;

#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    /* Note:
       Take care of the RX FIFO, DMA request only assert when received bytes
       equal or more than RX water mark, there is potential issue if RX water
       mark larger than 1.
       For example, if RX FIFO water mark is 2, upper layer needs 5 bytes and
       5 bytes are received. the last byte will be saved in FIFO but not trigger
       DMA transfer because the water mark is 2.
     */
    if (rxDmaHandle != NULL)
    {
        base->RWFIFO = 1U;
    }
#endif

    handle->rxDmaHandle = rxDmaHandle;
    handle->txDmaHandle = txDmaHandle;

    /* Save the handle in global variables to support the double weak mechanism. */
    s_uartHandle[instance] = handle;
    /* Save IRQ handler into static ISR function pointer. */
    s_uartIsr = UART_TransferDMAHandleIRQ;
    /* Disable internal IRQs and enable global IRQ. */
    UART_DisableInterrupts(base, (uint32_t)kUART_AllInterruptsEnable);
    (void)EnableIRQ(s_uartIRQ[instance]);

    /* Configure TX. */
    if (txDmaHandle != NULL)
    {
        DMA_SetCallback(txDmaHandle, UART_TransferSendDMACallback, &s_dmaPrivateHandle[instance]);
    }

    /* Configure RX. */
    if (rxDmaHandle != NULL)
    {
        DMA_SetCallback(rxDmaHandle, UART_TransferReceiveDMACallback, &s_dmaPrivateHandle[instance]);
    }
}

/*!
 * brief Sends data using DMA.
 *
 * This function sends data using DMA. This is non-blocking function, which returns
 * right away. When all data is sent, the send callback function is called.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param xfer UART DMA transfer structure. See #uart_transfer_t.
 * retval kStatus_Success if succeeded; otherwise failed.
 * retval kStatus_UART_TxBusy Previous transfer ongoing.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t UART_TransferSendDMA(UART_Type *base, uart_dma_handle_t *handle, uart_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(handle->txDmaHandle != NULL);
    assert(xfer != NULL);
    assert(xfer->data != NULL);
    assert(xfer->dataSize != 0U);

    dma_transfer_config_t xferConfig;
    status_t status;

    /* If previous TX not finished. */
    if ((uint8_t)kUART_TxBusy == handle->txState)
    {
        status = kStatus_UART_TxBusy;
    }
    else
    {
        handle->txState       = (uint8_t)kUART_TxBusy;
        handle->txDataSizeAll = xfer->dataSize;

        /* Prepare transfer. */
        DMA_PrepareTransfer(&xferConfig, xfer->data, sizeof(uint8_t), (uint32_t *)UART_GetDataRegisterAddress(base),
                            sizeof(uint8_t), xfer->dataSize, kDMA_MemoryToPeripheral);

        /* Submit transfer. */
        (void)DMA_SubmitTransfer(handle->txDmaHandle, &xferConfig, (uint32_t)kDMA_EnableInterrupt);
        DMA_StartTransfer(handle->txDmaHandle);

        /* Enable UART TX DMA. */
        UART_EnableTxDMA(base, true);

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
 * param base UART peripheral base address.
 * param handle Pointer to the uart_dma_handle_t structure.
 * param xfer UART DMA transfer structure. See #uart_transfer_t.
 * retval kStatus_Success if succeeded; otherwise failed.
 * retval kStatus_UART_RxBusy Previous transfer on going.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t UART_TransferReceiveDMA(UART_Type *base, uart_dma_handle_t *handle, uart_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(handle->rxDmaHandle != NULL);
    assert(xfer != NULL);
    assert(xfer->data != NULL);
    assert(xfer->dataSize != 0U);

    dma_transfer_config_t xferConfig;
    status_t status;

    /* If previous RX not finished. */
    if ((uint8_t)kUART_RxBusy == handle->rxState)
    {
        status = kStatus_UART_RxBusy;
    }
    else
    {
        handle->rxState       = (uint8_t)kUART_RxBusy;
        handle->rxDataSizeAll = xfer->dataSize;

        /* Prepare transfer. */
        DMA_PrepareTransfer(&xferConfig, (uint32_t *)UART_GetDataRegisterAddress(base), sizeof(uint8_t), xfer->data,
                            sizeof(uint8_t), xfer->dataSize, kDMA_PeripheralToMemory);

        /* Submit transfer. */
        (void)DMA_SubmitTransfer(handle->rxDmaHandle, &xferConfig, (uint32_t)kDMA_EnableInterrupt);
        DMA_StartTransfer(handle->rxDmaHandle);

        /* Enable UART RX DMA. */
        UART_EnableRxDMA(base, true);

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Aborts the send data using DMA.
 *
 * This function aborts the sent data using DMA.
 *
 * param base UART peripheral base address.
 * param handle Pointer to uart_dma_handle_t structure.
 */
void UART_TransferAbortSendDMA(UART_Type *base, uart_dma_handle_t *handle)
{
    assert(handle != NULL);
    assert(handle->txDmaHandle != NULL);

    /* Disable UART TX DMA. */
    UART_EnableTxDMA(base, false);

    /* Stop transfer. */
    DMA_AbortTransfer(handle->txDmaHandle);

    /* Write DMA->DSR[DONE] to abort transfer and clear status. */
    DMA_ClearChannelStatusFlags(handle->txDmaHandle->base, handle->txDmaHandle->channel,
                                (uint32_t)kDMA_TransactionsDoneFlag);

    handle->txState = (uint8_t)kUART_TxIdle;
}

/*!
 * brief Aborts the received data using DMA.
 *
 * This function abort receive data which using DMA.
 *
 * param base UART peripheral base address.
 * param handle Pointer to uart_dma_handle_t structure.
 */
void UART_TransferAbortReceiveDMA(UART_Type *base, uart_dma_handle_t *handle)
{
    assert(handle != NULL);
    assert(handle->rxDmaHandle != NULL);

    /* Disable UART RX DMA. */
    UART_EnableRxDMA(base, false);

    /* Stop transfer. */
    DMA_AbortTransfer(handle->rxDmaHandle);

    /* Write DMA->DSR[DONE] to abort transfer and clear status. */
    DMA_ClearChannelStatusFlags(handle->rxDmaHandle->base, handle->rxDmaHandle->channel,
                                (uint32_t)kDMA_TransactionsDoneFlag);

    handle->rxState = (uint8_t)kUART_RxIdle;
}

/*!
 * brief Gets the number of bytes written to UART TX register.
 *
 * This function gets the number of bytes written to UART TX
 * register by DMA.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param count Send bytes count.
 * retval kStatus_NoTransferInProgress No send in progress.
 * retval kStatus_InvalidArgument Parameter is invalid.
 * retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t UART_TransferGetSendCountDMA(UART_Type *base, uart_dma_handle_t *handle, uint32_t *count)
{
    assert(handle != NULL);
    assert(handle->txDmaHandle != NULL);
    assert(count != NULL);

    if ((uint8_t)kUART_TxIdle == handle->txState)
    {
        return kStatus_NoTransferInProgress;
    }

    *count = handle->txDataSizeAll - DMA_GetRemainingBytes(handle->txDmaHandle->base, handle->txDmaHandle->channel);

    return kStatus_Success;
}

/*!
 * brief Gets the number of bytes that have been received.
 *
 * This function gets the number of bytes that have been received.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param count Receive bytes count.
 * retval kStatus_NoTransferInProgress No receive in progress.
 * retval kStatus_InvalidArgument Parameter is invalid.
 * retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t UART_TransferGetReceiveCountDMA(UART_Type *base, uart_dma_handle_t *handle, uint32_t *count)
{
    assert(handle != NULL);
    assert(handle->rxDmaHandle != NULL);
    assert(count != NULL);

    if ((uint8_t)kUART_RxIdle == handle->rxState)
    {
        return kStatus_NoTransferInProgress;
    }

    *count = handle->rxDataSizeAll - DMA_GetRemainingBytes(handle->rxDmaHandle->base, handle->rxDmaHandle->channel);

    return kStatus_Success;
}

void UART_TransferDMAHandleIRQ(UART_Type *base, void *uartDmaHandle)
{
    assert(uartDmaHandle != NULL);

    uart_dma_handle_t *handle = (uart_dma_handle_t *)uartDmaHandle;

    handle->txState = (uint8_t)kUART_TxIdle;

    /* Disable tx complete interrupt */
    UART_DisableInterrupts(base, (uint32_t)kUART_TransmissionCompleteInterruptEnable);

    if (handle->callback != NULL)
    {
        handle->callback(base, handle, kStatus_UART_TxIdle, handle->userData);
    }
}
