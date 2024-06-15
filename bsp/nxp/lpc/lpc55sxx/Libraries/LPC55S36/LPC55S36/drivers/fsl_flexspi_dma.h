/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_FLEXSPI_DMA_H_
#define _FSL_FLEXSPI_DMA_H_

#include "fsl_flexspi.h"
#include "fsl_dma.h"

/*!
 * @addtogroup flexspi_dma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief FLEXSPI DMA driver version. */
#define FSL_FLEXSPI_DMA_DRIVER_VERSION (MAKE_VERSION(2, 3, 5))
/*@}*/

typedef struct _flexspi_dma_handle flexspi_dma_handle_t;

/*! @brief FLEXSPI dma transfer callback function for finish and error */
typedef void (*flexspi_dma_callback_t)(FLEXSPI_Type *base,
                                       flexspi_dma_handle_t *handle,
                                       status_t status,
                                       void *userData);

/*! @brief dma transfer configuration */
typedef enum _flexspi_dma_ntransfer_size
{
    kFLEXPSI_DMAnSize1Bytes = 0x1U, /*!< Source/Destination data transfer size is 1 byte every time */
    kFLEXPSI_DMAnSize2Bytes = 0x2U, /*!< Source/Destination data transfer size is 2 bytes every time */
    kFLEXPSI_DMAnSize4Bytes = 0x4U, /*!< Source/Destination data transfer size is 4 bytes every time */
} flexspi_dma_transfer_nsize_t;

/*! @brief FLEXSPI DMA transfer handle, users should not touch the content of the handle.*/
struct _flexspi_dma_handle
{
    dma_handle_t *txDmaHandle;                 /*!< dma handler for FLEXSPI Tx. */
    dma_handle_t *rxDmaHandle;                 /*!< dma handler for FLEXSPI Rx. */
    size_t transferSize;                       /*!< Bytes need to transfer. */
    flexspi_dma_transfer_nsize_t nsize;        /*!< dma SSIZE/DSIZE in each transfer. */
    uint8_t nbytes;                            /*!< dma minor byte transfer count initially configured. */
    uint8_t count;                             /*!< The transfer data count in a DMA request. */
    uint32_t state;                            /*!< Internal state for FLEXSPI dma transfer. */
    flexspi_dma_callback_t completionCallback; /*!< A callback function called after the dma transfer is finished. */
    void *userData;                            /*!< User callback parameter */
};

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name FLEXSPI dma Transactional
 * @{
 */

/*!
 * @brief Initializes the FLEXSPI handle for transfer which is used in transactional functions and set the callback.
 *
 * @param base FLEXSPI peripheral base address
 * @param handle Pointer to flexspi_dma_handle_t structure
 * @param callback FLEXSPI callback, NULL means no callback.
 * @param userData User callback function data.
 * @param txDmaHandle User requested DMA handle for TX DMA transfer.
 * @param rxDmaHandle User requested DMA handle for RX DMA transfer.
 */
void FLEXSPI_TransferCreateHandleDMA(FLEXSPI_Type *base,
                                     flexspi_dma_handle_t *handle,
                                     flexspi_dma_callback_t callback,
                                     void *userData,
                                     dma_handle_t *txDmaHandle,
                                     dma_handle_t *rxDmaHandle);

/*!
 * @brief Update FLEXSPI DMA transfer source data transfer size(SSIZE) and destination data transfer size(DSIZE).
 *
 * @param base FLEXSPI peripheral base address
 * @param handle Pointer to flexspi_dma_handle_t structure
 * @param nsize FLEXSPI DMA transfer data transfer size(SSIZE/DSIZE), by default the size is
 * kFLEXPSI_DMAnSize1Bytes(one byte).
 * @see flexspi_dma_transfer_nsize_t               .
 */
void FLEXSPI_TransferUpdateSizeDMA(FLEXSPI_Type *base,
                                   flexspi_dma_handle_t *handle,
                                   flexspi_dma_transfer_nsize_t nsize);

/*!
 * @brief Transfers FLEXSPI data using an dma non-blocking method.
 *
 * This function writes/receives data to/from the FLEXSPI transmit/receive FIFO. This function is non-blocking.
 * @param base FLEXSPI peripheral base address.
 * @param handle Pointer to flexspi_dma_handle_t structure
 * @param xfer FLEXSPI transfer structure.
 * @retval kStatus_FLEXSPI_Busy     FLEXSPI is busy transfer.
 * @retval kStatus_InvalidArgument  The watermark configuration is invalid, the watermark should be power of
                                    2 to do successfully DMA transfer.
 * @retval kStatus_Success          FLEXSPI successfully start dma transfer.
 */
status_t FLEXSPI_TransferDMA(FLEXSPI_Type *base, flexspi_dma_handle_t *handle, flexspi_transfer_t *xfer);

/*!
 * @brief Aborts the transfer data using dma.
 *
 * This function aborts the transfer data using dma.
 *
 * @param base FLEXSPI peripheral base address.
 * @param handle Pointer to flexspi_dma_handle_t structure
 */
void FLEXSPI_TransferAbortDMA(FLEXSPI_Type *base, flexspi_dma_handle_t *handle);

/*!
 * @brief Gets the transferred counts of transfer.
 *
 * @param base FLEXSPI peripheral base address.
 * @param handle Pointer to flexspi_dma_handle_t structure.
 * @param count Bytes transfer.
 * @retval kStatus_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t FLEXSPI_TransferGetTransferCountDMA(FLEXSPI_Type *base, flexspi_dma_handle_t *handle, size_t *count);

/* @} */

#if defined(__cplusplus)
}
#endif

/* @} */

#endif /* _FSL_FLEXSPI_DMA_H_ */
