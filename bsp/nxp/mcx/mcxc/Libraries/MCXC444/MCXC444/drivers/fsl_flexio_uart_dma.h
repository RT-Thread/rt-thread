/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_FLEXIO_UART_DMA_H_
#define FSL_FLEXIO_UART_DMA_H_

#include "fsl_flexio_uart.h"
#include "fsl_dma.h"

/*!
 * @addtogroup flexio_dma_uart
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief FlexIO UART DMA driver version. */
#define FSL_FLEXIO_UART_DMA_DRIVER_VERSION (MAKE_VERSION(2, 4, 0))
/*! @} */

/* Forward declaration of the handle typedef. */
typedef struct _flexio_uart_dma_handle flexio_uart_dma_handle_t;

/*! @brief UART transfer callback function. */
typedef void (*flexio_uart_dma_transfer_callback_t)(FLEXIO_UART_Type *base,
                                                    flexio_uart_dma_handle_t *handle,
                                                    status_t status,
                                                    void *userData);

/*!
 * @brief UART DMA handle
 */
struct _flexio_uart_dma_handle
{
    flexio_uart_dma_transfer_callback_t callback; /*!< Callback function. */
    void *userData;                               /*!< UART callback function parameter.*/

    size_t txDataSizeAll; /*!< Total bytes to be sent. */
    size_t rxDataSizeAll; /*!< Total bytes to be received. */

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
 * @brief Initializes the FLEXIO_UART handle which is used in transactional functions.
 *
 * @param base Pointer to FLEXIO_UART_Type structure.
 * @param handle Pointer to flexio_uart_dma_handle_t structure.
 * @param callback FlexIO UART callback, NULL means no callback.
 * @param userData User callback function data.
 * @param txDmaHandle User requested DMA handle for TX DMA transfer.
 * @param rxDmaHandle User requested DMA handle for RX DMA transfer.
 * @retval kStatus_Success Successfully create the handle.
 * @retval kStatus_OutOfRange The FlexIO UART DMA type/handle table out of range.
 */
status_t FLEXIO_UART_TransferCreateHandleDMA(FLEXIO_UART_Type *base,
                                             flexio_uart_dma_handle_t *handle,
                                             flexio_uart_dma_transfer_callback_t callback,
                                             void *userData,
                                             dma_handle_t *txDmaHandle,
                                             dma_handle_t *rxDmaHandle);

/*!
 * @brief Sends data using DMA.
 *
 * This function send data using DMA. This is non-blocking function, which returns
 * right away. When all data is sent out, the send callback function is called.
 *
 * @param base Pointer to FLEXIO_UART_Type structure
 * @param handle Pointer to flexio_uart_dma_handle_t structure
 * @param xfer FLEXIO_UART DMA transfer structure, see #flexio_uart_transfer_t.
 * @retval kStatus_Success if succeed, others failed.
 * @retval kStatus_FLEXIO_UART_TxBusy Previous transfer on going.
 */
status_t FLEXIO_UART_TransferSendDMA(FLEXIO_UART_Type *base,
                                     flexio_uart_dma_handle_t *handle,
                                     flexio_uart_transfer_t *xfer);

/*!
 * @brief Receives data using DMA.
 *
 * This function receives data using DMA. This is non-blocking function, which returns
 * right away. When all data is received, the receive callback function is called.
 *
 * @param base Pointer to FLEXIO_UART_Type structure
 * @param handle Pointer to flexio_uart_dma_handle_t structure
 * @param xfer FLEXIO_UART DMA transfer structure, see #flexio_uart_transfer_t.
 * @retval kStatus_Success if succeed, others failed.
 * @retval kStatus_FLEXIO_UART_RxBusy Previous transfer on going.
 */
status_t FLEXIO_UART_TransferReceiveDMA(FLEXIO_UART_Type *base,
                                        flexio_uart_dma_handle_t *handle,
                                        flexio_uart_transfer_t *xfer);

/*!
 * @brief Aborts the sent data which using DMA.
 *
 * This function aborts the sent data which using DMA.
 *
 * @param base Pointer to FLEXIO_UART_Type structure
 * @param handle Pointer to flexio_uart_dma_handle_t structure
 */
void FLEXIO_UART_TransferAbortSendDMA(FLEXIO_UART_Type *base, flexio_uart_dma_handle_t *handle);

/*!
 * @brief Aborts the receive data which using DMA.
 *
 * This function aborts the receive data which using DMA.
 *
 * @param base Pointer to FLEXIO_UART_Type structure
 * @param handle Pointer to flexio_uart_dma_handle_t structure
 */
void FLEXIO_UART_TransferAbortReceiveDMA(FLEXIO_UART_Type *base, flexio_uart_dma_handle_t *handle);

/*!
 * @brief Gets the number of bytes sent out.
 *
 * This function gets the number of bytes sent out.
 *
 * @param base Pointer to FLEXIO_UART_Type structure
 * @param handle Pointer to flexio_uart_dma_handle_t structure
 * @param count Number of bytes sent so far by the non-blocking transaction.
 * @retval kStatus_NoTransferInProgress transfer has finished or no transfer in progress.
 * @retval kStatus_Success Successfully return the count.
 */
status_t FLEXIO_UART_TransferGetSendCountDMA(FLEXIO_UART_Type *base, flexio_uart_dma_handle_t *handle, size_t *count);

/*!
 * @brief Gets the number of bytes received.
 *
 * This function gets the number of bytes received.
 *
 * @param base Pointer to FLEXIO_UART_Type structure
 * @param handle Pointer to flexio_uart_dma_handle_t structure
 * @param count Number of bytes received so far by the non-blocking transaction.
 * @retval kStatus_NoTransferInProgress transfer has finished or no transfer in progress.
 * @retval kStatus_Success Successfully return the count.
 */
status_t FLEXIO_UART_TransferGetReceiveCountDMA(FLEXIO_UART_Type *base,
                                                flexio_uart_dma_handle_t *handle,
                                                size_t *count);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_UART_DMA_H_ */
