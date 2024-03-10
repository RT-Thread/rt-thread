/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_DMIC_DMA_H_
#define _FSL_DMIC_DMA_H_

#include "fsl_common.h"
#include "fsl_dma.h"

/*!
 * @addtogroup dmic_dma_driver
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @name DMIC DMA version
 * @{
 */

/*! @brief DMIC DMA driver version 2.3.0 */
#define FSL_DMIC_DMA_DRIVER_VERSION (MAKE_VERSION(2, 3, 0))
/*@}*/

/*! @brief DMIC transfer structure. */
typedef struct _dmic_transfer
{
    void *data;                     /*!< The buffer of data to be transfer.*/
    uint8_t dataWidth;              /*!< DMIC support 16bit/32bit */
    size_t dataSize;                /*!< The byte count to be transfer. */
    uint8_t dataAddrInterleaveSize; /*!< destination address interleave size */

    struct _dmic_transfer *linkTransfer; /*!< use to support link transfer */
} dmic_transfer_t;

/* Forward declaration of the handle typedef. */
typedef struct _dmic_dma_handle dmic_dma_handle_t;

/*! @brief DMIC transfer callback function. */
typedef void (*dmic_dma_transfer_callback_t)(DMIC_Type *base,
                                             dmic_dma_handle_t *handle,
                                             status_t status,
                                             void *userData);

/*!
 * @brief DMIC DMA handle
 */
struct _dmic_dma_handle
{
    DMIC_Type *base;                       /*!< DMIC peripheral base address. */
    dma_handle_t *rxDmaHandle;             /*!< The DMA RX channel used. */
    dmic_dma_transfer_callback_t callback; /*!< Callback function. */
    void *userData;                        /*!< DMIC callback function parameter.*/
    size_t transferSize;                   /*!< Size of the data to receive. */
    volatile uint8_t state;                /*!< Internal state of DMIC DMA transfer */

    dma_descriptor_t *desLink; /*!< descriptor pool pointer */
    size_t linkNum;            /*!< number of descriptor in descriptors pool */
};

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* _cplusplus */

/*!
 * @name DMA transactional
 * @{
 */

/*!
 * @brief Initializes the DMIC handle which is used in transactional functions.
 * @param base DMIC peripheral base address.
 * @param handle Pointer to dmic_dma_handle_t structure.
 * @param callback Callback function.
 * @param userData User data.
 * @param rxDmaHandle User-requested DMA handle for RX DMA transfer.
 */
status_t DMIC_TransferCreateHandleDMA(DMIC_Type *base,
                                      dmic_dma_handle_t *handle,
                                      dmic_dma_transfer_callback_t callback,
                                      void *userData,
                                      dma_handle_t *rxDmaHandle);

/*!
 * @brief Receives data using DMA.
 *
 * This function receives data using DMA. This is a non-blocking function, which returns
 * right away. When all data is received, the receive callback function is called.
 *
 * @param base USART peripheral base address.
 * @param handle Pointer to usart_dma_handle_t structure.
 * @param xfer DMIC DMA transfer structure. See #dmic_transfer_t.
 * @param channel DMIC start channel number.
 * @retval kStatus_Success
 */
status_t DMIC_TransferReceiveDMA(DMIC_Type *base, dmic_dma_handle_t *handle, dmic_transfer_t *xfer, uint32_t channel);

/*!
 * @brief Aborts the received data using DMA.
 *
 * This function aborts the received data using DMA.
 *
 * @param base DMIC peripheral base address
 * @param handle Pointer to dmic_dma_handle_t structure
 */
void DMIC_TransferAbortReceiveDMA(DMIC_Type *base, dmic_dma_handle_t *handle);

/*!
 * @brief Get the number of bytes that have been received.
 *
 * This function gets the number of bytes that have been received.
 *
 * @param base DMIC peripheral base address.
 * @param handle DMIC handle pointer.
 * @param count Receive bytes count.
 * @retval kStatus_NoTransferInProgress No receive in progress.
 * @retval kStatus_InvalidArgument Parameter is invalid.
 * @retval kStatus_Success Get successfully through the parameter count;
 */
status_t DMIC_TransferGetReceiveCountDMA(DMIC_Type *base, dmic_dma_handle_t *handle, uint32_t *count);

/*!
 * @brief Install DMA descriptor memory.
 *
 * This function used to register DMA descriptor memory for linked transfer, a typical case is ping pong
 * transfer which will request more than one DMA descriptor memory space, it should be called after
 * DMIC_TransferCreateHandleDMA.
 * User should be take care about the address of DMA descriptor pool which required align with 16BYTE at least.
 *
 * @param handle Pointer to DMA channel transfer handle.
 * @param linkAddr DMA link descriptor address.
 * @param linkNum DMA link descriptor number.
 */
void DMIC_InstallDMADescriptorMemory(dmic_dma_handle_t *handle, void *linkAddr, size_t linkNum);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_DMIC_DMA_H_ */
