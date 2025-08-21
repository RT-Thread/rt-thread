/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_LPUART_DMA_H_
#define FSL_LPUART_DMA_H_

#include "fsl_lpuart.h"
#include "fsl_dma.h"

/*!
 * @addtogroup lpuart_dma_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief LPUART DMA driver version. */
#define FSL_LPUART_DMA_DRIVER_VERSION (MAKE_VERSION(2, 6, 0))
/*! @} */

/* Forward declaration of the handle typedef. */
typedef struct _lpuart_dma_handle lpuart_dma_handle_t;

/*! @brief LPUART transfer callback function. */
typedef void (*lpuart_dma_transfer_callback_t)(LPUART_Type *base,
                                               lpuart_dma_handle_t *handle,
                                               status_t status,
                                               void *userData);

/*!
 * @brief LPUART DMA handle
 */
struct _lpuart_dma_handle
{
    lpuart_dma_transfer_callback_t callback; /*!< Callback function. */
    void *userData;                          /*!< LPUART callback function parameter.*/
    size_t rxDataSizeAll;                    /*!< Size of the data to receive. */
    size_t txDataSizeAll;                    /*!< Size of the data to send out. */

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
 * @name EDMA transactional
 * @{
 */

/*!
 * @brief Initializes the LPUART handle which is used in transactional functions.
 *
 * @note This function disables all LPUART interrupts.
 *
 * @param base LPUART peripheral base address.
 * @param handle Pointer to lpuart_dma_handle_t structure.
 * @param callback Callback function.
 * @param userData User data.
 * @param txDmaHandle User-requested DMA handle for TX DMA transfer.
 * @param rxDmaHandle User-requested DMA handle for RX DMA transfer.
 */
void LPUART_TransferCreateHandleDMA(LPUART_Type *base,
                                    lpuart_dma_handle_t *handle,
                                    lpuart_dma_transfer_callback_t callback,
                                    void *userData,
                                    dma_handle_t *txDmaHandle,
                                    dma_handle_t *rxDmaHandle);

/*!
 * @brief Sends data using DMA.
 *
 * This function sends data using DMA. This is a non-blocking function, which returns
 * right away. When all data is sent, the send callback function is called.
 *
 * @param base LPUART peripheral base address.
 * @param handle LPUART handle pointer.
 * @param xfer LPUART DMA transfer structure. See #lpuart_transfer_t.
 * @retval kStatus_Success if succeed, others failed.
 * @retval kStatus_LPUART_TxBusy Previous transfer on going.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t LPUART_TransferSendDMA(LPUART_Type *base, lpuart_dma_handle_t *handle, lpuart_transfer_t *xfer);

/*!
 * @brief Receives data using DMA.
 *
 * This function receives data using DMA. This is a non-blocking function, which returns
 * right away. When all data is received, the receive callback function is called.
 *
 * @param base LPUART peripheral base address.
 * @param handle Pointer to lpuart_dma_handle_t structure.
 * @param xfer LPUART DMA transfer structure. See #lpuart_transfer_t.
 * @retval kStatus_Success if succeed, others failed.
 * @retval kStatus_LPUART_RxBusy Previous transfer on going.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t LPUART_TransferReceiveDMA(LPUART_Type *base, lpuart_dma_handle_t *handle, lpuart_transfer_t *xfer);

/*!
 * @brief Aborts the sent data using DMA.
 *
 * This function aborts send data using DMA.
 *
 * @param base LPUART peripheral base address
 * @param handle Pointer to lpuart_dma_handle_t structure
 */
void LPUART_TransferAbortSendDMA(LPUART_Type *base, lpuart_dma_handle_t *handle);

/*!
 * @brief Aborts the received data using DMA.
 *
 * This function aborts the received data using DMA.
 *
 * @param base LPUART peripheral base address
 * @param handle Pointer to lpuart_dma_handle_t structure
 */
void LPUART_TransferAbortReceiveDMA(LPUART_Type *base, lpuart_dma_handle_t *handle);

/*!
 * @brief Gets the number of bytes written to the LPUART TX register.
 *
 * This function gets the number of bytes that have been written to LPUART TX
 * register by DMA.
 *
 * @param base LPUART peripheral base address.
 * @param handle LPUART handle pointer.
 * @param count Send bytes count.
 * @retval kStatus_NoTransferInProgress No send in progress.
 * @retval kStatus_InvalidArgument Parameter is invalid.
 * @retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t LPUART_TransferGetSendCountDMA(LPUART_Type *base, lpuart_dma_handle_t *handle, uint32_t *count);

/*!
 * @brief Gets the number of received bytes.
 *
 * This function gets the number of received bytes.
 *
 * @param base LPUART peripheral base address.
 * @param handle LPUART handle pointer.
 * @param count Receive bytes count.
 * @retval kStatus_NoTransferInProgress No receive in progress.
 * @retval kStatus_InvalidArgument Parameter is invalid.
 * @retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t LPUART_TransferGetReceiveCountDMA(LPUART_Type *base, lpuart_dma_handle_t *handle, uint32_t *count);

/*!
 * @brief LPUART DMA IRQ handle function.
 *
 * This function handles the LPUART tx complete IRQ request and invoke user callback.
 * @note This function is used as default IRQ handler by double weak mechanism.
 * If user's specific IRQ handler is implemented, make sure this function is invoked in the handler.
 *
 * @param base LPUART peripheral base address.
 * @param lpuartDmaHandle LPUART handle pointer.
 */
void LPUART_TransferDMAHandleIRQ(LPUART_Type *base, void *lpuartDmaHandle);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_LPUART_DMA_H_ */
