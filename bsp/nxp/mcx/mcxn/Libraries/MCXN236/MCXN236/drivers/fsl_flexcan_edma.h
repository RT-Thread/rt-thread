/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_FLEXCAN_EDMA_H_
#define FSL_FLEXCAN_EDMA_H_

#include "fsl_flexcan.h"
#include "fsl_edma.h"

/*!
 * @addtogroup flexcan_edma_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief FlexCAN EDMA driver version. */
#define FSL_FLEXCAN_EDMA_DRIVER_VERSION (MAKE_VERSION(2, 11, 3))
/*@}*/

/* Forward declaration of the handle typedef. */
typedef struct _flexcan_edma_handle flexcan_edma_handle_t;

/*! @brief FlexCAN transfer callback function. */
typedef void (*flexcan_edma_transfer_callback_t)(CAN_Type *base,
                                                 flexcan_edma_handle_t *handle,
                                                 status_t status,
                                                 void *userData);

/*!
 * @brief FlexCAN eDMA handle
 */
struct _flexcan_edma_handle
{
    flexcan_edma_transfer_callback_t callback; /*!< Callback function. */
    void *userData;                            /*!< FlexCAN callback function parameter.*/
    edma_handle_t *rxFifoEdmaHandle;           /*!< The EDMA handler for Rx FIFO. */
    volatile uint8_t rxFifoState;              /*!< Rx FIFO transfer state. */
    size_t frameNum;                           /*!< The number of messages that need to be received. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
    flexcan_fd_frame_t *framefd; /*!< Point to the buffer of CAN Message to be received from Enhanced Rx FIFO. */
#endif
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
 * @brief Initializes the FlexCAN handle, which is used in transactional functions.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle Pointer to flexcan_edma_handle_t structure.
 * @param callback The callback function.
 * @param userData The parameter of the callback function.
 * @param rxFifoEdmaHandle User-requested DMA handle for Rx FIFO DMA transfer.
 */
void FLEXCAN_TransferCreateHandleEDMA(CAN_Type *base,
                                      flexcan_edma_handle_t *handle,
                                      flexcan_edma_transfer_callback_t callback,
                                      void *userData,
                                      edma_handle_t *rxFifoEdmaHandle);

/*!
 * @brief Prepares the eDMA transfer configuration for FLEXCAN Legacy RX FIFO.
 *
 * This function prepares the eDMA transfer configuration structure according to FLEXCAN Legacy RX FIFO.
 *
 * @param base FlexCAN peripheral base address.
 * @param pFifoXfer FlexCAN Rx FIFO EDMA transfer structure, see #flexcan_fifo_transfer_t.
 * @param pEdmaConfig The user configuration structure of type edma_transfer_t.
 *
 */
void FLEXCAN_PrepareTransfConfiguration(CAN_Type *base,
                                        flexcan_fifo_transfer_t *pFifoXfer,
                                        edma_transfer_config_t *pEdmaConfig);

/*!
 * @brief Start Transfer Data from the FLEXCAN Legacy Rx FIFO using eDMA.
 *
 * This function to Update edma transfer confiugration and Start eDMA transfer
 *
 * @param base FlexCAN peripheral base address.
 * @param handle Pointer to flexcan_edma_handle_t structure.
 * @param pEdmaConfig The user configuration structure of type edma_transfer_t.
 * @retval kStatus_Success if succeed, others failed.
 * @retval kStatus_FLEXCAN_RxFifoBusy Previous transfer ongoing.
 */
status_t FLEXCAN_StartTransferDatafromRxFIFO(CAN_Type *base,
                                             flexcan_edma_handle_t *handle,
                                             edma_transfer_config_t *pEdmaConfig);

/*!
 * @brief Receives the CAN Message from the Legacy Rx FIFO using eDMA.
 *
 * This function receives the CAN Message using eDMA. This is a non-blocking function, which returns
 * right away. After the CAN Message is received, the receive callback function is called.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle Pointer to flexcan_edma_handle_t structure.
 * @param pFifoXfer FlexCAN Rx FIFO EDMA transfer structure, see #flexcan_fifo_transfer_t.
 * @retval kStatus_Success if succeed, others failed.
 * @retval kStatus_FLEXCAN_RxFifoBusy Previous transfer ongoing.
 */
status_t FLEXCAN_TransferReceiveFifoEDMA(CAN_Type *base,
                                         flexcan_edma_handle_t *handle,
                                         flexcan_fifo_transfer_t *pFifoXfer);
/*!
 * @brief Gets the Legacy Rx Fifo transfer status during a interrupt non-blocking receive.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 * @param count Number of CAN messages receive so far by the non-blocking transaction.
 * @retval kStatus_InvalidArgument count is Invalid.
 * @retval kStatus_Success Successfully return the count.
 */

status_t FLEXCAN_TransferGetReceiveFifoCountEMDA(CAN_Type *base, flexcan_edma_handle_t *handle, size_t *count);
/*!
 * @brief Aborts the receive Legacy/Enhanced Rx FIFO process which used eDMA.
 *
 * This function aborts the receive Legacy/Enhanced Rx FIFO process which used eDMA.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle Pointer to flexcan_edma_handle_t structure.
 */
void FLEXCAN_TransferAbortReceiveFifoEDMA(CAN_Type *base, flexcan_edma_handle_t *handle);

#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
/*!
 * @brief Receives the CAN FD Message from the Enhanced Rx FIFO using eDMA.
 *
 * This function receives the CAN FD Message using eDMA. This is a non-blocking function, which returns
 * right away. After the CAN Message is received, the receive callback function is called.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle Pointer to flexcan_edma_handle_t structure.
 * @param pFifoXfer FlexCAN Rx FIFO EDMA transfer structure, see #flexcan_fifo_transfer_t.
 * @retval kStatus_Success if succeed, others failed.
 * @retval kStatus_FLEXCAN_RxFifoBusy Previous transfer ongoing.
 */
status_t FLEXCAN_TransferReceiveEnhancedFifoEDMA(CAN_Type *base,
                                                 flexcan_edma_handle_t *handle,
                                                 flexcan_fifo_transfer_t *pFifoXfer);
/*!
 * @brief Gets the Enhanced Rx Fifo transfer status during a interrupt non-blocking receive.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 * @param count Number of CAN messages receive so far by the non-blocking transaction.
 * @retval kStatus_InvalidArgument count is Invalid.
 * @retval kStatus_Success Successfully return the count.
 */

static inline status_t FLEXCAN_TransferGetReceiveEnhancedFifoCountEMDA(CAN_Type *base,
                                                                       flexcan_edma_handle_t *handle,
                                                                       size_t *count)
{
    return FLEXCAN_TransferGetReceiveFifoCountEMDA(base, handle, count);
}
#endif

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FLEXCAN_EDMA_H_ */
