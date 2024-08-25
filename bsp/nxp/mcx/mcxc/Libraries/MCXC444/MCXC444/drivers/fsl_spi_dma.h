/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_SPI_DMA_H_
#define FSL_SPI_DMA_H_

#include "fsl_spi.h"
#include "fsl_dma.h"

/*!
 * @addtogroup spi_dma_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief SPI DMA driver version. */
#define FSL_SPI_DMA_DRIVER_VERSION (MAKE_VERSION(2, 1, 1))
/*! @} */

typedef struct _spi_dma_handle spi_dma_handle_t;

/*! @brief SPI DMA callback called at the end of transfer. */
typedef void (*spi_dma_callback_t)(SPI_Type *base, spi_dma_handle_t *handle, status_t status, void *userData);

/*! @brief SPI DMA transfer handle, users should not touch the content of the handle.*/
struct _spi_dma_handle
{
    bool txInProgress;           /*!< Send transfer finished */
    bool rxInProgress;           /*!< Receive transfer finished */
    dma_handle_t *txHandle;      /*!< DMA handler for SPI send */
    dma_handle_t *rxHandle;      /*!< DMA handler for SPI receive */
    uint8_t bytesPerFrame;       /*!< Bytes in a frame for SPI transfer */
    spi_dma_callback_t callback; /*!< Callback for SPI DMA transfer */
    void *userData;              /*!< User Data for SPI DMA callback */
    uint32_t state;              /*!< Internal state of SPI DMA transfer */
    size_t transferSize;         /*!< Bytes need to be transfer */
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
 * @brief Initialize the SPI master DMA handle.
 *
 * This function initializes the SPI master DMA handle which can be used for other SPI master transactional APIs.
 * Usually, for a specified SPI instance, user need only call this API once to get the initialized handle.
 *
 * @param base SPI peripheral base address.
 * @param handle SPI handle pointer.
 * @param callback User callback function called at the end of a transfer.
 * @param userData User data for callback.
 * @param txHandle DMA handle pointer for SPI Tx, the handle shall be static allocated by users.
 * @param rxHandle DMA handle pointer for SPI Rx, the handle shall be static allocated by users.
 */
void SPI_MasterTransferCreateHandleDMA(SPI_Type *base,
                                       spi_dma_handle_t *handle,
                                       spi_dma_callback_t callback,
                                       void *userData,
                                       dma_handle_t *txHandle,
                                       dma_handle_t *rxHandle);

/*!
 * @brief Perform a non-blocking SPI transfer using DMA.
 *
 * @note This interface returned immediately after transfer initiates, users should call
 * SPI_GetTransferStatus to poll the transfer status to check whether SPI transfer finished.
 *
 * @param base SPI peripheral base address.
 * @param handle SPI DMA handle pointer.
 * @param xfer Pointer to dma transfer structure.
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 * @retval kStatus_SPI_Busy SPI is not idle, is running another transfer.
 */
status_t SPI_MasterTransferDMA(SPI_Type *base, spi_dma_handle_t *handle, spi_transfer_t *xfer);

/*!
 * @brief Abort a SPI transfer using DMA.
 *
 * @param base SPI peripheral base address.
 * @param handle SPI DMA handle pointer.
 */
void SPI_MasterTransferAbortDMA(SPI_Type *base, spi_dma_handle_t *handle);

/*!
 * @brief Get the transferred bytes for SPI slave DMA.
 *
 * @param base SPI peripheral base address.
 * @param handle SPI DMA handle pointer.
 * @param count Transferred bytes.
 * @retval kStatus_SPI_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t SPI_MasterTransferGetCountDMA(SPI_Type *base, spi_dma_handle_t *handle, size_t *count);

/*!
 * @brief Initialize the SPI slave DMA handle.
 *
 * This function initializes the SPI slave DMA handle which can be used for other SPI master transactional APIs.
 * Usually, for a specified SPI instance, user need only call this API once to get the initialized handle.
 *
 * @param base SPI peripheral base address.
 * @param handle SPI handle pointer.
 * @param callback User callback function called at the end of a transfer.
 * @param userData User data for callback.
 * @param txHandle DMA handle pointer for SPI Tx, the handle shall be static allocated by users.
 * @param rxHandle DMA handle pointer for SPI Rx, the handle shall be static allocated by users.
 */
static inline void SPI_SlaveTransferCreateHandleDMA(SPI_Type *base,
                                                    spi_dma_handle_t *handle,
                                                    spi_dma_callback_t callback,
                                                    void *userData,
                                                    dma_handle_t *txHandle,
                                                    dma_handle_t *rxHandle)
{
    SPI_MasterTransferCreateHandleDMA(base, handle, callback, userData, txHandle, rxHandle);
}

/*!
 * @brief Perform a non-blocking SPI transfer using DMA.
 *
 * @note This interface returned immediately after transfer initiates, users should call
 * SPI_GetTransferStatus to poll the transfer status to check whether SPI transfer finished.
 *
 * @param base SPI peripheral base address.
 * @param handle SPI DMA handle pointer.
 * @param xfer Pointer to dma transfer structure.
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 * @retval kStatus_SPI_Busy SPI is not idle, is running another transfer.
 */
static inline status_t SPI_SlaveTransferDMA(SPI_Type *base, spi_dma_handle_t *handle, spi_transfer_t *xfer)
{
    return SPI_MasterTransferDMA(base, handle, xfer);
}

/*!
 * @brief Abort a SPI transfer using DMA.
 *
 * @param base SPI peripheral base address.
 * @param handle SPI DMA handle pointer.
 */
static inline void SPI_SlaveTransferAbortDMA(SPI_Type *base, spi_dma_handle_t *handle)
{
    SPI_MasterTransferAbortDMA(base, handle);
}

/*!
 * @brief Get the transferred bytes for SPI slave DMA.
 *
 * @param base SPI peripheral base address.
 * @param handle SPI DMA handle pointer.
 * @param count Transferred bytes.
 * @retval kStatus_SPI_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
static inline status_t SPI_SlaveTransferGetCountDMA(SPI_Type *base, spi_dma_handle_t *handle, size_t *count)
{
    return SPI_MasterTransferGetCountDMA(base, handle, count);
}

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif
