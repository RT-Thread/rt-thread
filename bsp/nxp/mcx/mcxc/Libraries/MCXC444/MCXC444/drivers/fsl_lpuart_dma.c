/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_lpuart_dma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpuart_dma"
#endif

/*<! Structure definition for lpuart_dma_handle_t. The structure is private. */
typedef struct _lpuart_dma_private_handle
{
    LPUART_Type *base;
    lpuart_dma_handle_t *handle;
} lpuart_dma_private_handle_t;

/* LPUART DMA transfer handle. */
enum
{
    kLPUART_TxIdle, /* TX idle. */
    kLPUART_TxBusy, /* TX busy. */
    kLPUART_RxIdle, /* RX idle. */
    kLPUART_RxBusy  /* RX busy. */
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Array of LPUART handle. */
#if (defined(LPUART12))
#define LPUART_HANDLE_ARRAY_SIZE 13
#else /* LPUART12 */
#if (defined(LPUART11))
#define LPUART_HANDLE_ARRAY_SIZE 12
#else /* LPUART11 */
#if (defined(LPUART10))
#define LPUART_HANDLE_ARRAY_SIZE 11
#else /* LPUART10 */
#if (defined(LPUART9))
#define LPUART_HANDLE_ARRAY_SIZE 10
#else /* LPUART9 */
#if (defined(LPUART8))
#define LPUART_HANDLE_ARRAY_SIZE 9
#else /* LPUART8 */
#if (defined(LPUART7))
#define LPUART_HANDLE_ARRAY_SIZE 8
#else /* LPUART7 */
#if (defined(LPUART6))
#define LPUART_HANDLE_ARRAY_SIZE 7
#else /* LPUART6 */
#if (defined(LPUART5))
#define LPUART_HANDLE_ARRAY_SIZE 6
#else /* LPUART5 */
#if (defined(LPUART4))
#define LPUART_HANDLE_ARRAY_SIZE 5
#else /* LPUART4 */
#if (defined(LPUART3))
#define LPUART_HANDLE_ARRAY_SIZE 4
#else /* LPUART3 */
#if (defined(LPUART2))
#define LPUART_HANDLE_ARRAY_SIZE 3
#else /* LPUART2 */
#if (defined(LPUART1))
#define LPUART_HANDLE_ARRAY_SIZE 2
#else /* LPUART1 */
#if (defined(LPUART0))
#define LPUART_HANDLE_ARRAY_SIZE 1
#else /* LPUART0 */
#define LPUART_HANDLE_ARRAY_SIZE FSL_FEATURE_SOC_LPUART_COUNT
#endif /* LPUART 0 */
#endif /* LPUART 1 */
#endif /* LPUART 2 */
#endif /* LPUART 3 */
#endif /* LPUART 4 */
#endif /* LPUART 5 */
#endif /* LPUART 6 */
#endif /* LPUART 7 */
#endif /* LPUART 8 */
#endif /* LPUART 9 */
#endif /* LPUART 10 */
#endif /* LPUART 11 */
#endif /* LPUART 12 */

/*<! Private handle only used for internally. */
static lpuart_dma_private_handle_t s_dmaPrivateHandle[LPUART_HANDLE_ARRAY_SIZE];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief LPUART DMA send finished callback function.
 *
 * This function is called when LPUART DMA send finished. It disables the LPUART
 * TX DMA request and sends @ref kStatus_LPUART_TxIdle to LPUART callback.
 *
 * @param handle The DMA handle.
 * @param param Callback function parameter.
 */
static void LPUART_TransferSendDMACallback(dma_handle_t *handle, void *param);

/*!
 * @brief LPUART DMA receive finished callback function.
 *
 * This function is called when LPUART DMA receive finished. It disables the LPUART
 * RX DMA request and sends @ref kStatus_LPUART_RxIdle to LPUART callback.
 *
 * @param handle The DMA handle.
 * @param param Callback function parameter.
 */
static void LPUART_TransferReceiveDMACallback(dma_handle_t *handle, void *param);

/*******************************************************************************
 * Code
 ******************************************************************************/

static void LPUART_TransferSendDMACallback(dma_handle_t *handle, void *param)
{
    assert(handle != NULL);
    assert(param != NULL);

    lpuart_dma_private_handle_t *lpuartPrivateHandle = (lpuart_dma_private_handle_t *)param;

    /* Disable LPUART TX DMA. */
    LPUART_EnableTxDMA(lpuartPrivateHandle->base, false);

    /* Disable interrupt. */
    DMA_DisableInterrupts(lpuartPrivateHandle->handle->txDmaHandle->base,
                          lpuartPrivateHandle->handle->txDmaHandle->channel);

    /* Enable tx complete interrupt */
    LPUART_EnableInterrupts(lpuartPrivateHandle->base, (uint32_t)kLPUART_TransmissionCompleteInterruptEnable);
}

static void LPUART_TransferReceiveDMACallback(dma_handle_t *handle, void *param)
{
    assert(handle != NULL);
    assert(param != NULL);

    lpuart_dma_private_handle_t *lpuartPrivateHandle = (lpuart_dma_private_handle_t *)param;

    /* Disable LPUART RX DMA. */
    LPUART_EnableRxDMA(lpuartPrivateHandle->base, false);

    /* Disable interrupt. */
    DMA_DisableInterrupts(lpuartPrivateHandle->handle->rxDmaHandle->base,
                          lpuartPrivateHandle->handle->rxDmaHandle->channel);

    lpuartPrivateHandle->handle->rxState = (uint8_t)kLPUART_RxIdle;

    if (lpuartPrivateHandle->handle->callback != NULL)
    {
        lpuartPrivateHandle->handle->callback(lpuartPrivateHandle->base, lpuartPrivateHandle->handle,
                                              kStatus_LPUART_RxIdle, lpuartPrivateHandle->handle->userData);
    }
}

/*!
 * brief Initializes the LPUART handle which is used in transactional functions.
 *
 * note This function disables all LPUART interrupts.
 *
 * param base LPUART peripheral base address.
 * param handle Pointer to lpuart_dma_handle_t structure.
 * param callback Callback function.
 * param userData User data.
 * param txDmaHandle User-requested DMA handle for TX DMA transfer.
 * param rxDmaHandle User-requested DMA handle for RX DMA transfer.
 */
void LPUART_TransferCreateHandleDMA(LPUART_Type *base,
                                    lpuart_dma_handle_t *handle,
                                    lpuart_dma_transfer_callback_t callback,
                                    void *userData,
                                    dma_handle_t *txDmaHandle,
                                    dma_handle_t *rxDmaHandle)
{
    assert(handle != NULL);

    uint32_t instance = LPUART_GetInstance(base);

    (void)memset(handle, 0, sizeof(lpuart_dma_handle_t));

    s_dmaPrivateHandle[instance].base   = base;
    s_dmaPrivateHandle[instance].handle = handle;

    handle->rxState = (uint8_t)kLPUART_RxIdle;
    handle->txState = (uint8_t)kLPUART_TxIdle;

    handle->callback = callback;
    handle->userData = userData;

#if defined(FSL_FEATURE_LPUART_HAS_FIFO) && FSL_FEATURE_LPUART_HAS_FIFO
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
        base->WATER &= (~LPUART_WATER_RXWATER_MASK);
    }
#endif

    handle->rxDmaHandle = rxDmaHandle;
    handle->txDmaHandle = txDmaHandle;

    /* Save the handle in global variables to support the double weak mechanism. */
    s_lpuartHandle[instance] = handle;
    /* Set LPUART_TransferDMAHandleIRQ as DMA IRQ handler */
    s_lpuartIsr[instance] = LPUART_TransferDMAHandleIRQ;
    /* Disable all LPUART internal interrupts */
    LPUART_DisableInterrupts(base, (uint32_t)kLPUART_AllInterruptEnable);
    /* Enable interrupt in NVIC. */
#if defined(FSL_FEATURE_LPUART_HAS_SEPARATE_RX_TX_IRQ) && FSL_FEATURE_LPUART_HAS_SEPARATE_RX_TX_IRQ
    (void)EnableIRQ(s_lpuartTxIRQ[instance]);
#else
    (void)EnableIRQ(s_lpuartIRQ[instance]);
#endif

    /* Configure TX. */
    if (txDmaHandle != NULL)
    {
        DMA_SetCallback(txDmaHandle, LPUART_TransferSendDMACallback, &s_dmaPrivateHandle[instance]);
    }

    /* Configure RX. */
    if (rxDmaHandle != NULL)
    {
        DMA_SetCallback(rxDmaHandle, LPUART_TransferReceiveDMACallback, &s_dmaPrivateHandle[instance]);
    }
}

/*!
 * brief Sends data using DMA.
 *
 * This function sends data using DMA. This is a non-blocking function, which returns
 * right away. When all data is sent, the send callback function is called.
 *
 * param base LPUART peripheral base address.
 * param handle LPUART handle pointer.
 * param xfer LPUART DMA transfer structure. See #lpuart_transfer_t.
 * retval kStatus_Success if succeed, others failed.
 * retval kStatus_LPUART_TxBusy Previous transfer on going.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t LPUART_TransferSendDMA(LPUART_Type *base, lpuart_dma_handle_t *handle, lpuart_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(handle->txDmaHandle != NULL);
    assert(xfer != NULL);
    assert(xfer->data != NULL);
    assert(xfer->dataSize != 0U);

    status_t status;
    dma_transfer_config_t xferConfig;

    /* If previous TX not finished. */
    if ((uint8_t)kLPUART_TxBusy == handle->txState)
    {
        status = kStatus_LPUART_TxBusy;
    }
    else
    {
        handle->txState       = (uint8_t)kLPUART_TxBusy;
        handle->txDataSizeAll = xfer->dataSize;

        /* Prepare transfer. */
        uint32_t address = LPUART_GetDataRegisterAddress(base);
        DMA_PrepareTransfer(&xferConfig, xfer->data, sizeof(uint8_t), (uint32_t *)address, sizeof(uint8_t),
                            xfer->dataSize, kDMA_MemoryToPeripheral);

        /* Submit transfer. */
        (void)DMA_SubmitTransfer(handle->txDmaHandle, &xferConfig, (uint32_t)kDMA_EnableInterrupt);
        DMA_StartTransfer(handle->txDmaHandle);

        /* Enable LPUART TX DMA. */
        LPUART_EnableTxDMA(base, true);

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Receives data using DMA.
 *
 * This function receives data using DMA. This is a non-blocking function, which returns
 * right away. When all data is received, the receive callback function is called.
 *
 * param base LPUART peripheral base address.
 * param handle Pointer to lpuart_dma_handle_t structure.
 * param xfer LPUART DMA transfer structure. See #lpuart_transfer_t.
 * retval kStatus_Success if succeed, others failed.
 * retval kStatus_LPUART_RxBusy Previous transfer on going.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t LPUART_TransferReceiveDMA(LPUART_Type *base, lpuart_dma_handle_t *handle, lpuart_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(handle->rxDmaHandle != NULL);
    assert(xfer != NULL);
    assert(xfer->data != NULL);
    assert(xfer->dataSize != 0U);

    status_t status;
    dma_transfer_config_t xferConfig;

    /* If previous RX not finished. */
    if ((uint8_t)kLPUART_RxBusy == handle->rxState)
    {
        status = kStatus_LPUART_RxBusy;
    }
    else
    {
        handle->rxState       = (uint8_t)kLPUART_RxBusy;
        handle->rxDataSizeAll = xfer->dataSize;

        /* Prepare transfer. */
        uint32_t address = LPUART_GetDataRegisterAddress(base);
        DMA_PrepareTransfer(&xferConfig, (uint32_t *)address, sizeof(uint8_t), xfer->data, sizeof(uint8_t),
                            xfer->dataSize, kDMA_PeripheralToMemory);

        /* Submit transfer. */
        (void)DMA_SubmitTransfer(handle->rxDmaHandle, &xferConfig, (uint32_t)kDMA_EnableInterrupt);
        DMA_StartTransfer(handle->rxDmaHandle);

        /* Enable LPUART RX DMA. */
        LPUART_EnableRxDMA(base, true);

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Aborts the sent data using DMA.
 *
 * This function aborts send data using DMA.
 *
 * param base LPUART peripheral base address
 * param handle Pointer to lpuart_dma_handle_t structure
 */
void LPUART_TransferAbortSendDMA(LPUART_Type *base, lpuart_dma_handle_t *handle)
{
    assert(handle != NULL);
    assert(handle->txDmaHandle != NULL);

    /* Disable LPUART TX DMA. */
    LPUART_EnableTxDMA(base, false);

    /* Stop transfer. */
    DMA_AbortTransfer(handle->txDmaHandle);

    /* Write DMA->DSR[DONE] to abort transfer and clear status. */
    DMA_ClearChannelStatusFlags(handle->txDmaHandle->base, handle->txDmaHandle->channel,
                                (uint32_t)kDMA_TransactionsDoneFlag);

    handle->txState = (uint8_t)kLPUART_TxIdle;
}

/*!
 * brief Aborts the received data using DMA.
 *
 * This function aborts the received data using DMA.
 *
 * param base LPUART peripheral base address
 * param handle Pointer to lpuart_dma_handle_t structure
 */
void LPUART_TransferAbortReceiveDMA(LPUART_Type *base, lpuart_dma_handle_t *handle)
{
    assert(handle != NULL);
    assert(handle->rxDmaHandle != NULL);

    /* Disable LPUART RX DMA. */
    LPUART_EnableRxDMA(base, false);

    /* Stop transfer. */
    DMA_AbortTransfer(handle->rxDmaHandle);

    /* Write DMA->DSR[DONE] to abort transfer and clear status. */
    DMA_ClearChannelStatusFlags(handle->rxDmaHandle->base, handle->rxDmaHandle->channel,
                                (uint32_t)kDMA_TransactionsDoneFlag);

    handle->rxState = (uint8_t)kLPUART_RxIdle;
}

/*!
 * brief Gets the number of bytes written to the LPUART TX register.
 *
 * This function gets the number of bytes that have been written to LPUART TX
 * register by DMA.
 *
 * param base LPUART peripheral base address.
 * param handle LPUART handle pointer.
 * param count Send bytes count.
 * retval kStatus_NoTransferInProgress No send in progress.
 * retval kStatus_InvalidArgument Parameter is invalid.
 * retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t LPUART_TransferGetSendCountDMA(LPUART_Type *base, lpuart_dma_handle_t *handle, uint32_t *count)
{
    assert(handle != NULL);
    assert(handle->txDmaHandle != NULL);
    assert(count != NULL);

    if ((uint8_t)kLPUART_TxIdle == handle->txState)
    {
        return kStatus_NoTransferInProgress;
    }

    *count = handle->txDataSizeAll - DMA_GetRemainingBytes(handle->txDmaHandle->base, handle->txDmaHandle->channel);

    return kStatus_Success;
}

/*!
 * brief Gets the number of received bytes.
 *
 * This function gets the number of received bytes.
 *
 * param base LPUART peripheral base address.
 * param handle LPUART handle pointer.
 * param count Receive bytes count.
 * retval kStatus_NoTransferInProgress No receive in progress.
 * retval kStatus_InvalidArgument Parameter is invalid.
 * retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t LPUART_TransferGetReceiveCountDMA(LPUART_Type *base, lpuart_dma_handle_t *handle, uint32_t *count)
{
    assert(handle != NULL);
    assert(handle->rxDmaHandle != NULL);
    assert(count != NULL);

    if ((uint8_t)kLPUART_RxIdle == handle->rxState)
    {
        return kStatus_NoTransferInProgress;
    }

    *count = handle->rxDataSizeAll - DMA_GetRemainingBytes(handle->rxDmaHandle->base, handle->rxDmaHandle->channel);

    return kStatus_Success;
}

/*!
 * brief LPUART DMA IRQ handle function.
 *
 * This function handles the LPUART tx complete IRQ request and invoke user callback.
 * note This function is used as default IRQ handler by double weak mechanism.
 * If user's specific IRQ handler is implemented, make sure this function is invoked in the handler.
 *
 * param base LPUART peripheral base address.
 * param lpuartDmaHandle LPUART handle pointer.
 */
void LPUART_TransferDMAHandleIRQ(LPUART_Type *base, void *lpuartDmaHandle)
{
    assert(lpuartDmaHandle != NULL);

    if (((uint32_t)kLPUART_TransmissionCompleteFlag & LPUART_GetStatusFlags(base)) != 0U)
    {
        lpuart_dma_handle_t *handle = (lpuart_dma_handle_t *)lpuartDmaHandle;

        /* Disable tx complete interrupt */
        LPUART_DisableInterrupts(base, (uint32_t)kLPUART_TransmissionCompleteInterruptEnable);

        handle->txState = (uint8_t)kLPUART_TxIdle;

        if (handle->callback != NULL)
        {
            handle->callback(base, handle, kStatus_LPUART_TxIdle, handle->userData);
        }
    }
}
