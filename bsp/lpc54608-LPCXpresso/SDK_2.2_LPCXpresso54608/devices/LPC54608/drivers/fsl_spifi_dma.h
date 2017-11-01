/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _FSL_SPIFI_DMA_H_
#define _FSL_SPIFI_DMA_H_

#include "fsl_dma.h"
#include "fsl_spifi.h"

/*!
 * @addtogroup spifi
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef struct _spifi_dma_handle spifi_dma_handle_t;

/*! @brief SPIFI DMA transfer callback function for finish and error */
typedef void (*spifi_dma_callback_t)(SPIFI_Type *base, spifi_dma_handle_t *handle, status_t status, void *userData);

/*! @brief SPIFI DMA transfer handle, users should not touch the content of the handle.*/
struct _spifi_dma_handle
{
    dma_handle_t *dmaHandle;       /*!< DMA handler for SPIFI send */
    size_t transferSize;           /*!< Bytes need to transfer. */
    uint32_t state;                /*!< Internal state for SPIFI DMA transfer */
    spifi_dma_callback_t callback; /*!< Callback for users while transfer finish or error occurred */
    void *userData;                /*!< User callback parameter */
};

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name DMA Transactional
 * @{
 */

/*!
 * @brief Initializes the SPIFI handle for send which is used in transactional functions and set the callback.
 *
 * @param base SPIFI peripheral base address
 * @param handle Pointer to spifi_dma_handle_t structure
 * @param callback SPIFI callback, NULL means no callback.
 * @param userData User callback function data.
 * @param rxDmaHandle User requested DMA handle for DMA transfer
 */
void SPIFI_TransferTxCreateHandleDMA(SPIFI_Type *base,
                                     spifi_dma_handle_t *handle,
                                     spifi_dma_callback_t callback,
                                     void *userData,
                                     dma_handle_t *dmaHandle);

/*!
 * @brief Initializes the SPIFI handle for receive which is used in transactional functions and set the callback.
 *
 * @param base SPIFI peripheral base address
 * @param handle Pointer to spifi_dma_handle_t structure
 * @param callback SPIFI callback, NULL means no callback.
 * @param userData User callback function data.
 * @param rxDmaHandle User requested DMA handle for DMA transfer
 */
void SPIFI_TransferRxCreateHandleDMA(SPIFI_Type *base,
                                     spifi_dma_handle_t *handle,
                                     spifi_dma_callback_t callback,
                                     void *userData,
                                     dma_handle_t *dmaHandle);

/*!
 * @brief Transfers SPIFI data using an DMA non-blocking method.
 *
 * This function writes data to the SPIFI transmit FIFO. This function is non-blocking.
 * @param base Pointer to QuadSPI Type.
 * @param handle Pointer to spifi_dma_handle_t structure
 * @param xfer SPIFI transfer structure.
 */
status_t SPIFI_TransferSendDMA(SPIFI_Type *base, spifi_dma_handle_t *handle, spifi_transfer_t *xfer);

/*!
 * @brief Receives data using an DMA non-blocking method.
 *
 * This function receive data from the SPIFI receive buffer/FIFO. This function is non-blocking.
 * @param base Pointer to QuadSPI Type.
 * @param handle Pointer to spifi_dma_handle_t structure
 * @param xfer SPIFI transfer structure.
 */
status_t SPIFI_TransferReceiveDMA(SPIFI_Type *base, spifi_dma_handle_t *handle, spifi_transfer_t *xfer);

/*!
 * @brief Aborts the sent data using DMA.
 *
 * This function aborts the sent data using DMA.
 *
 * @param base SPIFI peripheral base address.
 * @param handle Pointer to spifi_dma_handle_t structure
 */
void SPIFI_TransferAbortSendDMA(SPIFI_Type *base, spifi_dma_handle_t *handle);

/*!
 * @brief Aborts the receive data using DMA.
 *
 * This function abort receive data which using DMA.
 *
 * @param base SPIFI peripheral base address.
 * @param handle Pointer to spifi_dma_handle_t structure
 */
void SPIFI_TransferAbortReceiveDMA(SPIFI_Type *base, spifi_dma_handle_t *handle);

/*!
 * @brief Gets the transferred counts of send.
 *
 * @param base Pointer to QuadSPI Type.
 * @param handle Pointer to spifi_dma_handle_t structure.
 * @param count Bytes sent.
 * @retval kStatus_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t SPIFI_TransferGetSendCountDMA(SPIFI_Type *base, spifi_dma_handle_t *handle, size_t *count);

/*!
 * @brief Gets the status of the receive transfer.
 *
 * @param base Pointer to QuadSPI Type.
 * @param handle Pointer to spifi_dma_handle_t structure
 * @param count Bytes received.
 * @retval kStatus_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t SPIFI_TransferGetReceiveCountDMA(SPIFI_Type *base, spifi_dma_handle_t *handle, size_t *count);

/* @} */

#if defined(__cplusplus)
}
#endif

/* @} */

#endif /* _FSL_SPIFI_DMA_H_ */
