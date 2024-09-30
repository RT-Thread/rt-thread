/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_UART_DMA_H_
#define FSL_UART_DMA_H_

#include "fsl_uart.h"
#include "fsl_dma.h"

/*!
 * @addtogroup uart_dma_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief UART DMA driver version. */
#define FSL_UART_DMA_DRIVER_VERSION (MAKE_VERSION(2, 5, 0))
/*! @} */

/* Forward declaration of the handle typedef. */
typedef struct _uart_dma_handle uart_dma_handle_t;

/*! @brief UART transfer callback function. */
typedef void (*uart_dma_transfer_callback_t)(UART_Type *base,
                                             uart_dma_handle_t *handle,
                                             status_t status,
                                             void *userData);

/*!
 * @brief UART DMA handle
 */
struct _uart_dma_handle
{
    UART_Type *base; /*!< UART peripheral base address. */

    uart_dma_transfer_callback_t callback; /*!< Callback function. */
    void *userData;                        /*!< UART callback function parameter.*/
    size_t rxDataSizeAll;                  /*!< Size of the data to receive. */
    size_t txDataSizeAll;                  /*!< Size of the data to send out. */

    dma_handle_t *txDmaHandle; /*!< The DMA TX channel used. */
    dma_handle_t *rxDmaHandle; /*!< The DMA RX channel used. */

    volatile uint8_t txState; /*!< TX transfer state. */
    volatile uint8_t rxState; /*!< RX transfer state */
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name eDMA transactional
 * @{
 */

/*!
 * @brief Initializes the UART handle which is used in transactional functions and sets the callback.
 *
 * @param base UART peripheral base address.
 * @param handle Pointer to the uart_dma_handle_t structure.
 * @param callback UART callback, NULL means no callback.
 * @param userData User callback function data.
 * @param rxDmaHandle User requested DMA handle for the RX DMA transfer.
 * @param txDmaHandle User requested DMA handle for the TX DMA transfer.
 */
void UART_TransferCreateHandleDMA(UART_Type *base,
                                  uart_dma_handle_t *handle,
                                  uart_dma_transfer_callback_t callback,
                                  void *userData,
                                  dma_handle_t *txDmaHandle,
                                  dma_handle_t *rxDmaHandle);

/*!
 * @brief Sends data using DMA.
 *
 * This function sends data using DMA. This is non-blocking function, which returns
 * right away. When all data is sent, the send callback function is called.
 *
 * @param base UART peripheral base address.
 * @param handle UART handle pointer.
 * @param xfer UART DMA transfer structure. See #uart_transfer_t.
 * @retval kStatus_Success if succeeded; otherwise failed.
 * @retval kStatus_UART_TxBusy Previous transfer ongoing.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t UART_TransferSendDMA(UART_Type *base, uart_dma_handle_t *handle, uart_transfer_t *xfer);

/*!
 * @brief Receives data using DMA.
 *
 * This function receives data using DMA. This is non-blocking function, which returns
 * right away. When all data is received, the receive callback function is called.
 *
 * @param base UART peripheral base address.
 * @param handle Pointer to the uart_dma_handle_t structure.
 * @param xfer UART DMA transfer structure. See #uart_transfer_t.
 * @retval kStatus_Success if succeeded; otherwise failed.
 * @retval kStatus_UART_RxBusy Previous transfer on going.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t UART_TransferReceiveDMA(UART_Type *base, uart_dma_handle_t *handle, uart_transfer_t *xfer);

/*!
 * @brief Aborts the send data using DMA.
 *
 * This function aborts the sent data using DMA.
 *
 * @param base UART peripheral base address.
 * @param handle Pointer to uart_dma_handle_t structure.
 */
void UART_TransferAbortSendDMA(UART_Type *base, uart_dma_handle_t *handle);

/*!
 * @brief Aborts the received data using DMA.
 *
 * This function abort receive data which using DMA.
 *
 * @param base UART peripheral base address.
 * @param handle Pointer to uart_dma_handle_t structure.
 */
void UART_TransferAbortReceiveDMA(UART_Type *base, uart_dma_handle_t *handle);

/*!
 * @brief Gets the number of bytes written to UART TX register.
 *
 * This function gets the number of bytes written to UART TX
 * register by DMA.
 *
 * @param base UART peripheral base address.
 * @param handle UART handle pointer.
 * @param count Send bytes count.
 * @retval kStatus_NoTransferInProgress No send in progress.
 * @retval kStatus_InvalidArgument Parameter is invalid.
 * @retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t UART_TransferGetSendCountDMA(UART_Type *base, uart_dma_handle_t *handle, uint32_t *count);

/*!
 * @brief Gets the number of bytes that have been received.
 *
 * This function gets the number of bytes that have been received.
 *
 * @param base UART peripheral base address.
 * @param handle UART handle pointer.
 * @param count Receive bytes count.
 * @retval kStatus_NoTransferInProgress No receive in progress.
 * @retval kStatus_InvalidArgument Parameter is invalid.
 * @retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t UART_TransferGetReceiveCountDMA(UART_Type *base, uart_dma_handle_t *handle, uint32_t *count);

/*!
 * @brief UART DMA IRQ handle function.
 *
 * This function handles the UART transmit complete IRQ request and invoke user callback.
 *
 * @param base UART peripheral base address.
 * @param uartDmaHandle UART handle pointer.
 */
void UART_TransferDMAHandleIRQ(UART_Type *base, void *uartDmaHandle);
/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_UART_DMA_H_ */
