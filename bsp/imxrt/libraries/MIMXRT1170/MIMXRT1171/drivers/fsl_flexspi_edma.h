/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_FLEXSPI_EDMA_H_
#define FSL_FLEXSPI_EDMA_H_

#include "fsl_flexspi.h"
#if defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT
#include "fsl_dmamux.h"
#endif
#include "fsl_edma.h"

/*!
 * @addtogroup flexspi_edma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief FLEXSPI EDMA driver version. */
#define FSL_FLEXSPI_EDMA_DRIVER_VERSION (MAKE_VERSION(2, 3, 3))
/*! @} */

typedef struct _flexspi_edma_handle flexspi_edma_handle_t;

/*! @brief FLEXSPI eDMA transfer callback function for finish and error */
typedef void (*flexspi_edma_callback_t)(FLEXSPI_Type *base,
                                        flexspi_edma_handle_t *handle,
                                        status_t status,
                                        void *userData);

/*! @brief eDMA transfer configuration */
typedef enum _flexspi_edma_ntransfer_size
{
    kFLEXPSI_EDMAnSize1Bytes  = 0x1U,  /*!< Source/Destination data transfer size is 1 byte every time */
    kFLEXPSI_EDMAnSize2Bytes  = 0x2U,  /*!< Source/Destination data transfer size is 2 bytes every time */
    kFLEXPSI_EDMAnSize4Bytes  = 0x4U,  /*!< Source/Destination data transfer size is 4 bytes every time */
    kFLEXPSI_EDMAnSize8Bytes  = 0x8U,  /*!< Source/Destination data transfer size is 8 bytes every time */
    kFLEXPSI_EDMAnSize32Bytes = 0x20U, /*!< Source/Destination data transfer size is 32 bytes every time */
} flexspi_edma_transfer_nsize_t;

/*! @brief FLEXSPI DMA transfer handle, users should not touch the content of the handle.*/
struct _flexspi_edma_handle
{
    edma_handle_t *txDmaHandle;                 /*!< eDMA handler for FLEXSPI Tx. */
    edma_handle_t *rxDmaHandle;                 /*!< eDMA handler for FLEXSPI Rx. */
    size_t transferSize;                        /*!< Bytes need to transfer. */
    flexspi_edma_transfer_nsize_t nsize;        /*!< eDMA SSIZE/DSIZE in each transfer. */
    uint8_t nbytes;                             /*!< eDMA minor byte transfer count initially configured. */
    uint8_t count;                              /*!< The transfer data count in a DMA request. */
    uint32_t state;                             /*!< Internal state for FLEXSPI eDMA transfer. */
    flexspi_edma_callback_t completionCallback; /*!< A callback function called after the eDMA transfer is finished. */
    void *userData;                             /*!< User callback parameter */
};

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name FLEXSPI eDMA Transactional
 * @{
 */

/*!
 * @brief Initializes the FLEXSPI handle for transfer which is used in transactional functions and set the callback.
 *
 * @param base FLEXSPI peripheral base address
 * @param handle Pointer to flexspi_edma_handle_t structure
 * @param callback FLEXSPI callback, NULL means no callback.
 * @param userData User callback function data.
 * @param txDmaHandle User requested DMA handle for TX DMA transfer.
 * @param rxDmaHandle User requested DMA handle for RX DMA transfer.
 */
void FLEXSPI_TransferCreateHandleEDMA(FLEXSPI_Type *base,
                                      flexspi_edma_handle_t *handle,
                                      flexspi_edma_callback_t callback,
                                      void *userData,
                                      edma_handle_t *txDmaHandle,
                                      edma_handle_t *rxDmaHandle);

/*!
 * @brief Update FLEXSPI EDMA transfer source data transfer size(SSIZE) and destination data transfer size(DSIZE).
 *
 * @param base FLEXSPI peripheral base address
 * @param handle Pointer to flexspi_edma_handle_t structure
 * @param nsize FLEXSPI DMA transfer data transfer size(SSIZE/DSIZE), by default the size is
 * kFLEXPSI_EDMAnSize1Bytes(one byte).
 * @see flexspi_edma_transfer_nsize_t               .
 */
void FLEXSPI_TransferUpdateSizeEDMA(FLEXSPI_Type *base,
                                    flexspi_edma_handle_t *handle,
                                    flexspi_edma_transfer_nsize_t nsize);

/*!
 * @brief Transfers FLEXSPI data using an eDMA non-blocking method.
 *
 * This function writes/receives data to/from the FLEXSPI transmit/receive FIFO. This function is non-blocking.
 * @param base FLEXSPI peripheral base address.
 * @param handle Pointer to flexspi_edma_handle_t structure
 * @param xfer FLEXSPI transfer structure.
 * @retval kStatus_FLEXSPI_Busy     FLEXSPI is busy transfer.
 * @retval kStatus_InvalidArgument  The watermark configuration is invalid, the watermark should be power of
                                    2 to do successfully EDMA transfer.
 * @retval kStatus_Success          FLEXSPI successfully start edma transfer.
 */
status_t FLEXSPI_TransferEDMA(FLEXSPI_Type *base, flexspi_edma_handle_t *handle, flexspi_transfer_t *xfer);

/*!
 * @brief Aborts the transfer data using eDMA.
 *
 * This function aborts the transfer data using eDMA.
 *
 * @param base FLEXSPI peripheral base address.
 * @param handle Pointer to flexspi_edma_handle_t structure
 */
void FLEXSPI_TransferAbortEDMA(FLEXSPI_Type *base, flexspi_edma_handle_t *handle);

/*!
 * @brief Gets the transferred counts of transfer.
 *
 * @param base FLEXSPI peripheral base address.
 * @param handle Pointer to flexspi_edma_handle_t structure.
 * @param count Bytes transfer.
 * @retval kStatus_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t FLEXSPI_TransferGetTransferCountEDMA(FLEXSPI_Type *base, flexspi_edma_handle_t *handle, size_t *count);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_FLEXSPI_EDMA_H_ */
