/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_usart.h"
#include "fsl_device_registers.h"
#include "fsl_dma.h"
#include "fsl_flexcomm.h"
#include "fsl_usart_dma.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexcomm_usart_dma"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
enum
{
    kUSART_TxIdle, /* TX idle. */
    kUSART_TxBusy, /* TX busy. */
    kUSART_RxIdle, /* RX idle. */
    kUSART_RxBusy  /* RX busy. */
};

/*! @brief Typedef for usart DMA interrupt handler. */
typedef void (*flexcomm_usart_dma_irq_handler_t)(USART_Type *base, usart_dma_handle_t *handle);

/*<! Structure definition for uart_dma_handle_t. The structure is private. */
typedef struct _usart_dma_private_handle
{
    USART_Type *base;
    usart_dma_handle_t *handle;
} usart_dma_private_handle_t;

/*!
 * @brief Used for conversion from `flexcomm_usart_irq_handler_t` to `flexcomm_irq_handler_t`
 */
typedef union usart_dma_to_flexcomm
{
    flexcomm_usart_dma_irq_handler_t usart_dma_handler;
    flexcomm_irq_handler_t flexcomm_handler;
} usart_dma_to_flexcomm_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief IRQ name array */
static const IRQn_Type s_usartIRQ[] = USART_IRQS;
/*! @brief Array to map USART instance number to base address. */
static const uint32_t s_usartBaseAddrs[] = USART_BASE_ADDRS;
/*<! Private handle only used for internally. */
static usart_dma_private_handle_t s_dmaPrivateHandle[ARRAY_SIZE(s_usartBaseAddrs)];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief USART DMA IRQ handle function.
 *
 * This function handles the USART transmit idle interrupt and invoke call back.
 *
 * @param base USART peripheral base address.
 * @param handle USART handle pointer.
 */
void USART_TransferDMAHandleIRQ(USART_Type *base, usart_dma_handle_t *handle);

/*******************************************************************************
 * Code
 ******************************************************************************/

static void USART_TransferSendDMACallback(dma_handle_t *handle, void *param, bool transferDone, uint32_t intmode)
{
    assert(handle != NULL);
    assert(param != NULL);

    usart_dma_private_handle_t *usartPrivateHandle = (usart_dma_private_handle_t *)param;

    /* Disable UART TX DMA. */
    USART_EnableTxDMA(usartPrivateHandle->base, false);

    /* Enable tx idle interrupt */
    usartPrivateHandle->base->INTENSET = USART_INTENSET_TXIDLEEN_MASK;
}

static void USART_TransferReceiveDMACallback(dma_handle_t *handle, void *param, bool transferDone, uint32_t intmode)
{
    assert(handle != NULL);
    assert(param != NULL);

    usart_dma_private_handle_t *usartPrivateHandle = (usart_dma_private_handle_t *)param;

    /* Disable UART RX DMA. */
    USART_EnableRxDMA(usartPrivateHandle->base, false);

    usartPrivateHandle->handle->rxState = (uint8_t)kUSART_RxIdle;

    if (usartPrivateHandle->handle->callback != NULL)
    {
        usartPrivateHandle->handle->callback(usartPrivateHandle->base, usartPrivateHandle->handle, kStatus_USART_RxIdle,
                                             usartPrivateHandle->handle->userData);
    }
}

/*!
 * brief Initializes the USART handle which is used in transactional functions.
 * param base USART peripheral base address.
 * param handle Pointer to usart_dma_handle_t structure.
 * param callback Callback function.
 * param userData User data.
 * param txDmaHandle User-requested DMA handle for TX DMA transfer.
 * param rxDmaHandle User-requested DMA handle for RX DMA transfer.
 */
status_t USART_TransferCreateHandleDMA(USART_Type *base,
                                       usart_dma_handle_t *handle,
                                       usart_dma_transfer_callback_t callback,
                                       void *userData,
                                       dma_handle_t *txDmaHandle,
                                       dma_handle_t *rxDmaHandle)
{
    uint32_t instance = 0;

    /* check 'base' */
    assert(!(NULL == base));
    if (NULL == base)
    {
        return kStatus_InvalidArgument;
    }
    /* check 'handle' */
    assert(!(NULL == handle));
    if (NULL == handle)
    {
        return kStatus_InvalidArgument;
    }

    instance = USART_GetInstance(base);

    (void)memset(handle, 0, sizeof(*handle));
    /* assign 'base' and 'handle' */
    s_dmaPrivateHandle[instance].base   = base;
    s_dmaPrivateHandle[instance].handle = handle;

    /* set tx/rx 'idle' state */
    handle->rxState = (uint8_t)kUSART_RxIdle;
    handle->txState = (uint8_t)kUSART_TxIdle;

    handle->callback = callback;
    handle->userData = userData;

    handle->rxDmaHandle = rxDmaHandle;
    handle->txDmaHandle = txDmaHandle;

    /* Set USART_TransferDMAHandleIRQ as DMA IRQ handler */
    usart_dma_to_flexcomm_t handler;
    handler.usart_dma_handler = USART_TransferDMAHandleIRQ;
    FLEXCOMM_SetIRQHandler(base, handler.flexcomm_handler, handle);
    /* Enable NVIC IRQ. */
    (void)EnableIRQ(s_usartIRQ[instance]);

    /* Configure TX. */
    if (txDmaHandle != NULL)
    {
        DMA_SetCallback(txDmaHandle, USART_TransferSendDMACallback, &s_dmaPrivateHandle[instance]);
    }

    /* Configure RX. */
    if (rxDmaHandle != NULL)
    {
        DMA_SetCallback(rxDmaHandle, USART_TransferReceiveDMACallback, &s_dmaPrivateHandle[instance]);
    }

    return kStatus_Success;
}

/*!
 * brief Sends data using DMA.
 *
 * This function sends data using DMA. This is a non-blocking function, which returns
 * right away. When all data is sent, the send callback function is called.
 *
 * param base USART peripheral base address.
 * param handle USART handle pointer.
 * param xfer USART DMA transfer structure. See #usart_transfer_t.
 * retval kStatus_Success if succeed, others failed.
 * retval kStatus_USART_TxBusy Previous transfer on going.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t USART_TransferSendDMA(USART_Type *base, usart_dma_handle_t *handle, usart_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(handle->txDmaHandle != NULL);
    assert(xfer != NULL);
    assert(xfer->data != NULL);
    assert(xfer->dataSize != 0U);

    dma_transfer_config_t xferConfig;
    status_t status;
    uint32_t address = (uint32_t)&base->FIFOWR;

    /* If previous TX not finished. */
    if ((uint8_t)kUSART_TxBusy == handle->txState)
    {
        status = kStatus_USART_TxBusy;
    }
    else
    {
        handle->txState       = (uint8_t)kUSART_TxBusy;
        handle->txDataSizeAll = xfer->dataSize;

        /* Enable DMA request from txFIFO */
        USART_EnableTxDMA(base, true);

        /* Prepare transfer. */
        DMA_PrepareTransfer(&xferConfig, xfer->data, (uint32_t *)address, sizeof(uint8_t), xfer->dataSize,
                            kDMA_MemoryToPeripheral, NULL);

        /* Submit transfer. */
        (void)DMA_SubmitTransfer(handle->txDmaHandle, &xferConfig);
        DMA_StartTransfer(handle->txDmaHandle);

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
 * param base USART peripheral base address.
 * param handle Pointer to usart_dma_handle_t structure.
 * param xfer USART DMA transfer structure. See #usart_transfer_t.
 * retval kStatus_Success if succeed, others failed.
 * retval kStatus_USART_RxBusy Previous transfer on going.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t USART_TransferReceiveDMA(USART_Type *base, usart_dma_handle_t *handle, usart_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(handle->rxDmaHandle != NULL);
    assert(xfer != NULL);
    assert(xfer->data != NULL);
    assert(xfer->dataSize != 0U);

    dma_transfer_config_t xferConfig;
    status_t status;
    uint32_t address = (uint32_t)&base->FIFORD;

    /* If previous RX not finished. */
    if ((uint8_t)kUSART_RxBusy == handle->rxState)
    {
        status = kStatus_USART_RxBusy;
    }
    else
    {
        handle->rxState       = (uint8_t)kUSART_RxBusy;
        handle->rxDataSizeAll = xfer->dataSize;

        /* Enable DMA request from rxFIFO */
        USART_EnableRxDMA(base, true);

        /* Prepare transfer. */
        DMA_PrepareTransfer(&xferConfig, (uint32_t *)address, xfer->data, sizeof(uint8_t), xfer->dataSize,
                            kDMA_PeripheralToMemory, NULL);

        /* Submit transfer. */
        (void)DMA_SubmitTransfer(handle->rxDmaHandle, &xferConfig);
        DMA_StartTransfer(handle->rxDmaHandle);

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Aborts the sent data using DMA.
 *
 * This function aborts send data using DMA.
 *
 * param base USART peripheral base address
 * param handle Pointer to usart_dma_handle_t structure
 */
void USART_TransferAbortSendDMA(USART_Type *base, usart_dma_handle_t *handle)
{
    assert(NULL != handle);
    assert(NULL != handle->txDmaHandle);

    /* Stop transfer. */
    DMA_AbortTransfer(handle->txDmaHandle);
    handle->txState = (uint8_t)kUSART_TxIdle;
}

/*!
 * brief Aborts the received data using DMA.
 *
 * This function aborts the received data using DMA.
 *
 * param base USART peripheral base address
 * param handle Pointer to usart_dma_handle_t structure
 */
void USART_TransferAbortReceiveDMA(USART_Type *base, usart_dma_handle_t *handle)
{
    assert(NULL != handle);
    assert(NULL != handle->rxDmaHandle);

    /* Stop transfer. */
    DMA_AbortTransfer(handle->rxDmaHandle);
    handle->rxState = (uint8_t)kUSART_RxIdle;
}

/*!
 * brief Get the number of bytes that have been received.
 *
 * This function gets the number of bytes that have been received.
 *
 * param base USART peripheral base address.
 * param handle USART handle pointer.
 * param count Receive bytes count.
 * retval kStatus_NoTransferInProgress No receive in progress.
 * retval kStatus_InvalidArgument Parameter is invalid.
 * retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t USART_TransferGetReceiveCountDMA(USART_Type *base, usart_dma_handle_t *handle, uint32_t *count)
{
    assert(NULL != handle);
    assert(NULL != handle->rxDmaHandle);
    assert(NULL != count);

    if ((uint8_t)kUSART_RxIdle == handle->rxState)
    {
        return kStatus_NoTransferInProgress;
    }

    *count = handle->rxDataSizeAll - DMA_GetRemainingBytes(handle->rxDmaHandle->base, handle->rxDmaHandle->channel);

    return kStatus_Success;
}

/*!
 * brief Get the number of bytes that have been sent.
 *
 * This function gets the number of bytes that have been sent.
 *
 * param base USART peripheral base address.
 * param handle USART handle pointer.
 * param count Sent bytes count.
 * retval kStatus_NoTransferInProgress No receive in progress.
 * retval kStatus_InvalidArgument Parameter is invalid.
 * retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t USART_TransferGetSendCountDMA(USART_Type *base, usart_dma_handle_t *handle, uint32_t *count)
{
    assert(NULL != handle);
    assert(NULL != handle->txDmaHandle);
    assert(NULL != count);

    if ((uint8_t)kUSART_TxIdle == handle->txState)
    {
        return kStatus_NoTransferInProgress;
    }

    *count = handle->txDataSizeAll - DMA_GetRemainingBytes(handle->txDmaHandle->base, handle->txDmaHandle->channel);

    return kStatus_Success;
}

void USART_TransferDMAHandleIRQ(USART_Type *base, usart_dma_handle_t *handle)
{
    /* Check arguments */
    assert((NULL != base) && (NULL != handle));

    /* Tx idle interrupt happens means that all the tx data have been sent out to bus, set the tx state to idle */
    handle->txState = (uint8_t)kUSART_TxIdle;

    /* Disable tx idle interrupt */
    base->INTENCLR = USART_INTENCLR_TXIDLECLR_MASK;

    /* Invoke callback */
    if (handle->callback != NULL)
    {
        handle->callback(base, handle, kStatus_USART_TxIdle, handle->userData);
    }
}
