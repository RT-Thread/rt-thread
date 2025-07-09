/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021, 2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_SAI_EDMA_H_
#define FSL_SAI_EDMA_H_

#include "fsl_edma.h"
#include "fsl_sai.h"

/*!
 * @addtogroup sai_edma SAI EDMA Driver
 * @ingroup sai
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
#define FSL_SAI_EDMA_DRIVER_VERSION (MAKE_VERSION(2, 7, 3)) /*!< Version 2.7.3 */
/*! @} */

/*! @brief the SAI enable position When calling SAI_TransferReceiveEDMA */
#ifndef MCUX_SDK_SAI_EDMA_RX_ENABLE_INTERNAL
#define MCUX_SDK_SAI_EDMA_RX_ENABLE_INTERNAL 1U
#endif

/*! @brief the SAI enable position When calling SAI_TransferSendEDMA */
#ifndef MCUX_SDK_SAI_EDMA_TX_ENABLE_INTERNAL
#define MCUX_SDK_SAI_EDMA_TX_ENABLE_INTERNAL 1U
#endif

typedef struct sai_edma_handle sai_edma_handle_t;

/*! @brief SAI eDMA transfer callback function for finish and error */
typedef void (*sai_edma_callback_t)(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData);

/*!@brief sai interleave type */
typedef enum _sai_edma_interleave
{
    kSAI_EDMAInterleavePerChannelSample =
        0U, /*!< SAI data interleave per channel sample
             * ---------------------------------------------------------------------------------------------------
             * |LEFT CHANNEL | RIGHT CHANNEL | LEFT CHANNEL | RIGHT CHANNEL | LEFT CHANNEL | RIGHT CHANNEL | ....|
             * ---------------------------------------------------------------------------------------------------
             */
    kSAI_EDMAInterleavePerChannelBlock =
        1U, /*!< SAI data interleave per channel block
             * --------------------------------------------------------------------------------------------------------
             * |LEFT CHANNEL | LEFT CHANNEL | LEFT CHANNEL | ... | RIGHT CHANNEL | RIGHT CHANNEL | RIGHT CHANNEL | ...|
             * --------------------------------------------------------------------------------------------------------
             */
} sai_edma_interleave_t;

/*! @brief SAI DMA transfer handle, users should not touch the content of the handle.*/
struct sai_edma_handle
{
    edma_handle_t *dmaHandle;     /*!< DMA handler for SAI send */
    uint8_t nbytes;               /*!< eDMA minor byte transfer count initially configured. */
    uint8_t bytesPerFrame;        /*!< Bytes in a frame */
    uint8_t channelMask;          /*!< Enabled channel mask value, reference _sai_channel_mask */
    uint8_t channelNums;          /*!< total enabled channel nums */
    uint8_t channel;              /*!< Which data channel */
    uint8_t count;                /*!< The transfer data count in a DMA request */
    uint32_t state;               /*!< Internal state for SAI eDMA transfer */
    sai_edma_callback_t callback; /*!< Callback for users while transfer finish or error occurs */
    void *userData;               /*!< User callback parameter */
    uint8_t tcd[(SAI_XFER_QUEUE_SIZE + 1U) * sizeof(edma_tcd_t)]; /*!< TCD pool for eDMA transfer. */
    sai_transfer_t saiQueue[SAI_XFER_QUEUE_SIZE];                 /*!< Transfer queue storing queued transfer. */
    size_t transferSize[SAI_XFER_QUEUE_SIZE];                     /*!< Data bytes need to transfer */
    sai_edma_interleave_t interleaveType;                         /*!< Transfer interleave type */
    volatile uint8_t queueUser;                                   /*!< Index for user to queue transfer. */
    volatile uint8_t queueDriver; /*!< Index for driver to get the transfer data and size */
};

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name eDMA Transactional
 * @{
 */

/*!
 * @brief Initializes the SAI eDMA handle.
 *
 * This function initializes the SAI master DMA handle, which can be used for other SAI master transactional APIs.
 * Usually, for a specified SAI instance, call this API once to get the initialized handle.
 *
 * @param base SAI base pointer.
 * @param handle SAI eDMA handle pointer.
 * @param callback Pointer to user callback function.
 * @param userData User parameter passed to the callback function.
 * @param txDmaHandle eDMA handle pointer, this handle shall be static allocated by users.
 */
void SAI_TransferTxCreateHandleEDMA(I2S_Type *base,
                                    sai_edma_handle_t *handle,
                                    sai_edma_callback_t callback,
                                    void *userData,
                                    edma_handle_t *txDmaHandle);

/*!
 * @brief Initializes the SAI Rx eDMA handle.
 *
 * This function initializes the SAI slave DMA handle, which can be used for other SAI master transactional APIs.
 * Usually, for a specified SAI instance, call this API once to get the initialized handle.
 *
 * @param base SAI base pointer.
 * @param handle SAI eDMA handle pointer.
 * @param callback Pointer to user callback function.
 * @param userData User parameter passed to the callback function.
 * @param rxDmaHandle eDMA handle pointer, this handle shall be static allocated by users.
 */
void SAI_TransferRxCreateHandleEDMA(I2S_Type *base,
                                    sai_edma_handle_t *handle,
                                    sai_edma_callback_t callback,
                                    void *userData,
                                    edma_handle_t *rxDmaHandle);

/*!
 * @brief Initializes the SAI interleave type.
 *
 * This function initializes the SAI DMA handle member interleaveType, it shall be called only when application would
 * like to use type kSAI_EDMAInterleavePerChannelBlock, since the default interleaveType is
 * kSAI_EDMAInterleavePerChannelSample always
 *
 * @param handle SAI eDMA handle pointer.
 * @param interleaveType Multi channel interleave type.
 */
void SAI_TransferSetInterleaveType(sai_edma_handle_t *handle, sai_edma_interleave_t interleaveType);

/*!
 * @brief Configures the SAI Tx.
 *
 * @note SAI eDMA supports data transfer in a multiple SAI channels if the FIFO Combine feature is supported.
 * To activate the multi-channel transfer enable SAI channels by filling the channelMask
 * of sai_transceiver_t with the corresponding values of _sai_channel_mask enum, enable the FIFO Combine
 * mode by assigning kSAI_FifoCombineModeEnabledOnWrite to the fifoCombine member of sai_fifo_combine_t
 * which is a member of sai_transceiver_t.
 * This is an example of multi-channel data transfer configuration step.
 *  @code
 *   sai_transceiver_t config;
 *   SAI_GetClassicI2SConfig(&config, kSAI_WordWidth16bits, kSAI_Stereo, kSAI_Channel0Mask|kSAI_Channel1Mask);
 *   config.fifo.fifoCombine = kSAI_FifoCombineModeEnabledOnWrite;
 *   SAI_TransferTxSetConfigEDMA(I2S0, &edmaHandle, &config);
 *  @endcode
 *
 * @param base SAI base pointer.
 * @param handle SAI eDMA handle pointer.
 * @param saiConfig sai configurations.
 */
void SAI_TransferTxSetConfigEDMA(I2S_Type *base, sai_edma_handle_t *handle, sai_transceiver_t *saiConfig);

/*!
 * @brief Configures the SAI Rx.
 *
 * @note SAI eDMA supports data transfer in a multiple SAI channels if the FIFO Combine feature is supported.
 * To activate the multi-channel transfer enable SAI channels by filling the channelMask
 * of sai_transceiver_t with the corresponding values of _sai_channel_mask enum, enable the FIFO Combine
 * mode by assigning kSAI_FifoCombineModeEnabledOnRead to the fifoCombine member of sai_fifo_combine_t
 * which is a member of sai_transceiver_t.
 * This is an example of multi-channel data transfer configuration step.
 *  @code
 *   sai_transceiver_t config;
 *   SAI_GetClassicI2SConfig(&config, kSAI_WordWidth16bits, kSAI_Stereo, kSAI_Channel0Mask|kSAI_Channel1Mask);
 *   config.fifo.fifoCombine = kSAI_FifoCombineModeEnabledOnRead;
 *   SAI_TransferRxSetConfigEDMA(I2S0, &edmaHandle, &config);
 *  @endcode
 * @param base SAI base pointer.
 * @param handle SAI eDMA handle pointer.
 * @param saiConfig sai configurations.
 */
void SAI_TransferRxSetConfigEDMA(I2S_Type *base, sai_edma_handle_t *handle, sai_transceiver_t *saiConfig);

/*!
 * @brief Performs a non-blocking SAI transfer using DMA.
 *
 * @note This interface returns immediately after the transfer initiates. Call
 * SAI_GetTransferStatus to poll the transfer status and check whether the SAI transfer is finished.
 *
 * This function support multi channel transfer,
 * 1. for the sai IP support fifo combine mode, application should enable the fifo combine mode, no limitation
 *    on channel numbers
 * 2. for the sai IP not support fifo combine mode, sai edma provide another solution which using
 *    EDMA modulo feature, but support 2 or 4 channels only.
 *
 * @param base SAI base pointer.
 * @param handle SAI eDMA handle pointer.
 * @param xfer Pointer to the DMA transfer structure.
 * @retval kStatus_Success Start a SAI eDMA send successfully.
 * @retval kStatus_InvalidArgument The input argument is invalid.
 * @retval kStatus_TxBusy SAI is busy sending data.
 */
status_t SAI_TransferSendEDMA(I2S_Type *base, sai_edma_handle_t *handle, sai_transfer_t *xfer);

/*!
 * @brief Performs a non-blocking SAI receive using eDMA.
 *
 * @note This interface returns immediately after the transfer initiates. Call
 * the SAI_GetReceiveRemainingBytes to poll the transfer status and check whether the SAI transfer is finished.
 *
 * This function support multi channel transfer,
 * 1. for the sai IP support fifo combine mode, application should enable the fifo combine mode, no limitation
 *    on channel numbers
 * 2. for the sai IP not support fifo combine mode, sai edma provide another solution which using
 *    EDMA modulo feature, but support 2 or 4 channels only.
 *
 * @param base SAI base pointer
 * @param handle SAI eDMA handle pointer.
 * @param xfer Pointer to DMA transfer structure.
 * @retval kStatus_Success Start a SAI eDMA receive successfully.
 * @retval kStatus_InvalidArgument The input argument is invalid.
 * @retval kStatus_RxBusy SAI is busy receiving data.
 */
status_t SAI_TransferReceiveEDMA(I2S_Type *base, sai_edma_handle_t *handle, sai_transfer_t *xfer);

/*!
 * @brief Performs a non-blocking SAI loop transfer using eDMA.
 *
 * @note This function support loop transfer only,such as A->B->...->A, application must be aware of
 * that the more counts of the loop transfer, then more tcd memory required, as the function use the tcd pool in
 * sai_edma_handle_t, so application could redefine the SAI_XFER_QUEUE_SIZE to determine the proper TCD pool size.
 * This function support one sai channel only.
 *
 * Once the loop transfer start, application can use function SAI_TransferAbortSendEDMA to stop the loop transfer.
 *
 * @param base SAI base pointer.
 * @param handle SAI eDMA handle pointer.
 * @param xfer Pointer to the DMA transfer structure, should be a array with elements counts >=1(loopTransferCount).
 * @param loopTransferCount the counts of xfer array.
 * @retval kStatus_Success Start a SAI eDMA send successfully.
 * @retval kStatus_InvalidArgument The input argument is invalid.
 */
status_t SAI_TransferSendLoopEDMA(I2S_Type *base,
                                  sai_edma_handle_t *handle,
                                  sai_transfer_t *xfer,
                                  uint32_t loopTransferCount);

/*!
 * @brief Performs a non-blocking SAI loop transfer using eDMA.
 *
 * @note This function support loop transfer only,such as A->B->...->A, application must be aware of
 * that the more counts of the loop transfer, then more tcd memory required, as the function use the tcd pool in
 * sai_edma_handle_t, so application could redefine the SAI_XFER_QUEUE_SIZE to determine the proper TCD pool size.
 * This function support one sai channel only.
 *
 * Once the loop transfer start, application can use function SAI_TransferAbortReceiveEDMA to stop the loop transfer.
 *
 * @param base SAI base pointer.
 * @param handle SAI eDMA handle pointer.
 * @param xfer Pointer to the DMA transfer structure, should be a array with elements counts >=1(loopTransferCount).
 * @param loopTransferCount the counts of xfer array.
 * @retval kStatus_Success Start a SAI eDMA receive successfully.
 * @retval kStatus_InvalidArgument The input argument is invalid.
 */
status_t SAI_TransferReceiveLoopEDMA(I2S_Type *base,
                                     sai_edma_handle_t *handle,
                                     sai_transfer_t *xfer,
                                     uint32_t loopTransferCount);

/*!
 * @brief Terminate all SAI send.
 *
 * This function will clear all transfer slots buffered in the sai queue. If users only want to abort the
 * current transfer slot, please call SAI_TransferAbortSendEDMA.
 *
 * @param base SAI base pointer.
 * @param handle SAI eDMA handle pointer.
 */
void SAI_TransferTerminateSendEDMA(I2S_Type *base, sai_edma_handle_t *handle);

/*!
 * @brief Terminate all SAI receive.
 *
 * This function will clear all transfer slots buffered in the sai queue. If users only want to abort the
 * current transfer slot, please call SAI_TransferAbortReceiveEDMA.
 *
 * @param base SAI base pointer.
 * @param handle SAI eDMA handle pointer.
 */
void SAI_TransferTerminateReceiveEDMA(I2S_Type *base, sai_edma_handle_t *handle);

/*!
 * @brief Aborts a SAI transfer using eDMA.
 *
 * This function only aborts the current transfer slots, the other transfer slots' information still kept
 * in the handler. If users want to terminate all transfer slots, just call SAI_TransferTerminateSendEDMA.
 *
 * @param base SAI base pointer.
 * @param handle SAI eDMA handle pointer.
 */
void SAI_TransferAbortSendEDMA(I2S_Type *base, sai_edma_handle_t *handle);

/*!
 * @brief Aborts a SAI receive using eDMA.
 *
 * This function only aborts the current transfer slots, the other transfer slots' information still kept
 * in the handler. If users want to terminate all transfer slots, just call SAI_TransferTerminateReceiveEDMA.
 *
 * @param base SAI base pointer
 * @param handle SAI eDMA handle pointer.
 */
void SAI_TransferAbortReceiveEDMA(I2S_Type *base, sai_edma_handle_t *handle);

/*!
 * @brief Gets byte count sent by SAI.
 *
 * @param base SAI base pointer.
 * @param handle SAI eDMA handle pointer.
 * @param count Bytes count sent by SAI.
 * @retval kStatus_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is no non-blocking transaction in progress.
 */
status_t SAI_TransferGetSendCountEDMA(I2S_Type *base, sai_edma_handle_t *handle, size_t *count);

/*!
 * @brief Gets byte count received by SAI.
 *
 * @param base SAI base pointer
 * @param handle SAI eDMA handle pointer.
 * @param count Bytes count received by SAI.
 * @retval kStatus_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is no non-blocking transaction in progress.
 */
status_t SAI_TransferGetReceiveCountEDMA(I2S_Type *base, sai_edma_handle_t *handle, size_t *count);

/*!
 * @brief Gets valid transfer slot.
 *
 * This function can be used to query the valid transfer request slot that the application can submit.
 * It should be called in the critical section, that means the application could call it in the corresponding callback
 * function or disable IRQ before calling it in the application, otherwise, the returned value may not correct.
 *
 * @param base SAI base pointer
 * @param handle SAI eDMA handle pointer.
 * @retval valid slot count that application submit.
 */
uint32_t SAI_TransferGetValidTransferSlotsEDMA(I2S_Type *base, sai_edma_handle_t *handle);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif
