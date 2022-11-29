/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_I2S_DMA_H_
#define _FSL_I2S_DMA_H_

#include "fsl_device_registers.h"
#include "fsl_common.h"
#include "fsl_flexcomm.h"

#include "fsl_dma.h"
#include "fsl_i2s.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @addtogroup i2s_dma_driver
 * @{
 */

/*! @name Driver version */
/*@{*/
/*! @brief I2S DMA driver version 2.3.1. */
#define FSL_I2S_DMA_DRIVER_VERSION (MAKE_VERSION(2, 3, 1))
/*@}*/

/*! @brief Members not to be accessed / modified outside of the driver. */
typedef struct _i2s_dma_handle i2s_dma_handle_t;

/*!
 * @brief Callback function invoked from DMA API on completion.
 *
 * @param base I2S base pointer.
 * @param handle pointer to I2S transaction.
 * @param completionStatus status of the transaction.
 * @param userData optional pointer to user arguments data.
 */
typedef void (*i2s_dma_transfer_callback_t)(I2S_Type *base,
                                            i2s_dma_handle_t *handle,
                                            status_t completionStatus,
                                            void *userData);
/*! @brief i2s dma handle */
struct _i2s_dma_handle
{
    uint32_t state;                                    /*!< Internal state of I2S DMA transfer */
    uint8_t bytesPerFrame;                             /*!< bytes per frame */
    i2s_dma_transfer_callback_t completionCallback;    /*!< Callback function pointer */
    void *userData;                                    /*!< Application data passed to callback */
    dma_handle_t *dmaHandle;                           /*!< DMA handle */
    volatile i2s_transfer_t i2sQueue[I2S_NUM_BUFFERS]; /*!< Transfer queue storing transfer buffers */
    volatile uint8_t queueUser;                        /*!< Queue index where user's next transfer will be stored */
    volatile uint8_t queueDriver;                      /*!< Queue index of buffer actually used by the driver */

    dma_descriptor_t *i2sLoopDMADescriptor; /*!< descriptor pool pointer */
    size_t i2sLoopDMADescriptorNum;         /*!< number of descriptor in descriptors pool */
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*! @} */

/*!
 * @name DMA API
 * @{
 */

/*!
 * @brief Initializes handle for transfer of audio data.
 *
 * @param base I2S base pointer.
 * @param handle pointer to handle structure.
 * @param dmaHandle pointer to dma handle structure.
 * @param callback function to be called back when transfer is done or fails.
 * @param userData pointer to data passed to callback.
 */
void I2S_TxTransferCreateHandleDMA(I2S_Type *base,
                                   i2s_dma_handle_t *handle,
                                   dma_handle_t *dmaHandle,
                                   i2s_dma_transfer_callback_t callback,
                                   void *userData);

/*!
 * @brief Begins or queue sending of the given data.
 *
 * @param base I2S base pointer.
 * @param handle pointer to handle structure.
 * @param transfer data buffer.
 *
 * @retval kStatus_Success
 * @retval kStatus_I2S_Busy if all queue slots are occupied with unsent buffers.
 */
status_t I2S_TxTransferSendDMA(I2S_Type *base, i2s_dma_handle_t *handle, i2s_transfer_t transfer);

/*!
 * @brief Aborts transfer of data.
 *
 * @param base I2S base pointer.
 * @param handle pointer to handle structure.
 */
void I2S_TransferAbortDMA(I2S_Type *base, i2s_dma_handle_t *handle);

/*!
 * @brief Initializes handle for reception of audio data.
 *
 * @param base I2S base pointer.
 * @param handle pointer to handle structure.
 * @param dmaHandle pointer to dma handle structure.
 * @param callback function to be called back when transfer is done or fails.
 * @param userData pointer to data passed to callback.
 */
void I2S_RxTransferCreateHandleDMA(I2S_Type *base,
                                   i2s_dma_handle_t *handle,
                                   dma_handle_t *dmaHandle,
                                   i2s_dma_transfer_callback_t callback,
                                   void *userData);

/*!
 * @brief Begins or queue reception of data into given buffer.
 *
 * @param base I2S base pointer.
 * @param handle pointer to handle structure.
 * @param transfer data buffer.
 *
 * @retval kStatus_Success
 * @retval kStatus_I2S_Busy if all queue slots are occupied with buffers
 *         which are not full.
 */
status_t I2S_RxTransferReceiveDMA(I2S_Type *base, i2s_dma_handle_t *handle, i2s_transfer_t transfer);

/*!
 * @brief Invoked from DMA interrupt handler.
 *
 * @param handle pointer to DMA handle structure.
 * @param userData argument for user callback.
 * @param transferDone if transfer was done.
 * @param tcds
 */
void I2S_DMACallback(dma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds);

/*!
 * @brief Install DMA descriptor memory for loop transfer only.
 *
 * This function used to register DMA descriptor memory for the i2s loop dma transfer.
 *
 * It must be callbed before I2S_TransferSendLoopDMA/I2S_TransferReceiveLoopDMA and after
 * I2S_RxTransferCreateHandleDMA/I2S_TxTransferCreateHandleDMA.
 *
 * User should be take care about the address of DMA descriptor pool which required align with 16BYTE at least.
 *
 * @param handle Pointer to i2s DMA transfer handle.
 * @param dmaDescriptorAddr DMA descriptor start address.
 * @param dmaDescriptorNum DMA descriptor number.
 */
void I2S_TransferInstallLoopDMADescriptorMemory(i2s_dma_handle_t *handle,
                                                void *dmaDescriptorAddr,
                                                size_t dmaDescriptorNum);

/*!
 * @brief Send link transfer data using DMA.
 *
 * This function receives data using DMA. This is a non-blocking function, which returns
 * right away. When all data is received, the receive callback function is called.
 *
 * This function support loop transfer, such as A->B->...->A, the loop transfer chain
 * will be converted into a chain of descriptor and submit to dma.
 * Application must be aware of that the more counts of the loop transfer, then more DMA descriptor memory required,
 * user can use function I2S_InstallDMADescriptorMemory to register the dma descriptor memory.
 *
 * As the DMA support maximum 1024 transfer count, so application must be aware of that this transfer function support
 * maximum 1024 samples in each transfer, otherwise assert error or error status will be returned. Once the loop
 * transfer start, application can use function I2S_TransferAbortDMA to stop the loop transfer.
 *
 * @param base I2S peripheral base address.
 * @param handle Pointer to usart_dma_handle_t structure.
 * @param xfer I2S DMA transfer structure. See #i2s_transfer_t.
 * @param loopTransferCount loop count
 * @retval kStatus_Success
 */
status_t I2S_TransferSendLoopDMA(I2S_Type *base,
                                 i2s_dma_handle_t *handle,
                                 i2s_transfer_t *xfer,
                                 uint32_t loopTransferCount);

/*!
 * @brief Receive link transfer data using DMA.
 *
 * This function receives data using DMA. This is a non-blocking function, which returns
 * right away. When all data is received, the receive callback function is called.
 *
 * This function support loop transfer, such as A->B->...->A, the loop transfer chain
 * will be converted into a chain of descriptor and submit to dma.
 * Application must be aware of that the more counts of the loop transfer, then more DMA descriptor memory required,
 * user can use function I2S_InstallDMADescriptorMemory to register the dma descriptor memory.
 *
 * As the DMA support maximum 1024 transfer count, so application must be aware of that this transfer function support
 * maximum 1024 samples in each transfer, otherwise assert error or error status will be returned. Once the loop
 * transfer start, application can use function I2S_TransferAbortDMA to stop the loop transfer.
 *
 * @param base I2S peripheral base address.
 * @param handle Pointer to usart_dma_handle_t structure.
 * @param xfer I2S DMA transfer structure. See #i2s_transfer_t.
 * @param loopTransferCount loop count
 * @retval kStatus_Success
 */
status_t I2S_TransferReceiveLoopDMA(I2S_Type *base,
                                    i2s_dma_handle_t *handle,
                                    i2s_transfer_t *xfer,
                                    uint32_t loopTransferCount);

/*! @} */

/*! @} */

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_I2S_DMA_H_ */
