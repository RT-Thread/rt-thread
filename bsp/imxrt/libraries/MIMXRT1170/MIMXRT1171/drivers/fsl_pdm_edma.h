/*
 * Copyright 2019 - 2020,2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_PDM_EDMA_H_
#define FSL_PDM_EDMA_H_

#include "fsl_edma.h"
#include "fsl_pdm.h"

/*!
 * @addtogroup pdm_edma PDM EDMA Driver
 * @ingroup pdm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
#define FSL_PDM_EDMA_DRIVER_VERSION (MAKE_VERSION(2, 6, 5)) /*!< Version 2.6.5 */
/*! @} */

/*! @brief the PDM enable position When calling PDM_TransferReceiveEDMA */
#ifndef MCUX_SDK_PDM_EDMA_PDM_ENABLE_INTERNAL
#define MCUX_SDK_PDM_EDMA_PDM_ENABLE_INTERNAL 1U
#endif

/*! @brief PDM edma handler */
typedef struct _pdm_edma_handle pdm_edma_handle_t;

/*!@brief pdm multi channel interleave type */
typedef enum _pdm_edma_multi_channel_interleave
{
    kPDM_EDMAMultiChannelInterleavePerChannelSample =
        0U, /*!< multi channel PDM data interleave per channel sample
             * -------------------------------------------------------------------------
             * |CHANNEL0 | CHANNEL1 | CHANNEL0 | CHANNEL1 | CHANNEL0 | CHANNEL 1 | ....|
             * -------------------------------------------------------------------------
             */
    kPDM_EDMAMultiChannelInterleavePerChannelBlock =
        1U, /*!< multi channel PDM data interleave per channel block
             * ----------------------------------------------------------------------------------------------------------------------------
             * |CHANNEL0 | CHANNEL0 | CHANNEL0 | ...... | CHANNEL1 | CHANNEL 1 | CHANNEL 1 | ....| CHANNEL2 | CHANNEL 2
             * | CHANNEL 2 | ....|
             * ----------------------------------------------------------------------------------------------------------------------------
             */
} pdm_edma_multi_channel_interleave_t;

/*! @brief PDM edma transfer */
typedef struct _pdm_edma_transfer
{
    volatile uint8_t *data;                  /*!< Data start address to transfer. */
    volatile size_t dataSize;                /*!< Total Transfer bytes size. */
    struct _pdm_edma_transfer *linkTransfer; /*!< linked transfer configurations */
} pdm_edma_transfer_t;

/*! @brief PDM eDMA transfer callback function for finish and error */
typedef void (*pdm_edma_callback_t)(PDM_Type *base, pdm_edma_handle_t *handle, status_t status, void *userData);

/*! @brief PDM DMA transfer handle, users should not touch the content of the handle.*/
struct _pdm_edma_handle
{
    edma_handle_t *dmaHandle;     /*!< DMA handler for PDM send */
    uint8_t count;                /*!< The transfer data count in a DMA request */
    uint32_t receivedBytes;       /*!< total transfer count */
    uint32_t state;               /*!< Internal state for PDM eDMA transfer */
    pdm_edma_callback_t callback; /*!< Callback for users while transfer finish or error occurs */
    bool isLoopTransfer;          /*!< loop transfer */
    void *userData;               /*!< User callback parameter */
    edma_tcd_t *tcd;              /*!< TCD pool for eDMA transfer. */
    uint32_t tcdNum;              /*!< TCD number */
    uint32_t tcdUser;             /*!< Index for user to queue transfer. */
    uint32_t tcdDriver;           /*!< Index for driver to get the transfer data and size */
    volatile uint32_t tcdUsedNum; /*!< Index for user to queue transfer. */

    pdm_edma_multi_channel_interleave_t interleaveType; /*!< multi channel transfer interleave type */

    uint8_t endChannel;  /*!< The last enabled channel */
    uint8_t channelNums; /*!< total channel numbers */
};

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name PDM eDMA Transactional
 * @{
 */

/*!
 * @brief Install EDMA descriptor memory.
 *
 * @param handle Pointer to EDMA channel transfer handle.
 * @param tcdAddr EDMA head descriptor address.
 * @param tcdNum EDMA link descriptor address.
 */
void PDM_TransferInstallEDMATCDMemory(pdm_edma_handle_t *handle, void *tcdAddr, size_t tcdNum);

/*!
 * @brief Initializes the PDM Rx eDMA handle.
 *
 * This function initializes the PDM slave DMA handle, which can be used for other PDM master transactional APIs.
 * Usually, for a specified PDM instance, call this API once to get the initialized handle.
 *
 * @param base PDM base pointer.
 * @param handle PDM eDMA handle pointer.
 * @param callback Pointer to user callback function.
 * @param userData User parameter passed to the callback function.
 * @param dmaHandle eDMA handle pointer, this handle shall be static allocated by users.
 */
void PDM_TransferCreateHandleEDMA(
    PDM_Type *base, pdm_edma_handle_t *handle, pdm_edma_callback_t callback, void *userData, edma_handle_t *dmaHandle);

/*!
 * @brief Initializes the multi PDM channel interleave type.
 *
 * This function initializes the PDM DMA handle member interleaveType, it shall be called only when application would
 * like to use type kPDM_EDMAMultiChannelInterleavePerChannelBlock, since the default interleaveType is
 * kPDM_EDMAMultiChannelInterleavePerChannelSample always
 *
 * @param handle PDM eDMA handle pointer.
 * @param multiChannelInterleaveType Multi channel interleave type.
 */
void PDM_TransferSetMultiChannelInterleaveType(pdm_edma_handle_t *handle,
                                               pdm_edma_multi_channel_interleave_t multiChannelInterleaveType);

/*!
 * @brief Configures the PDM channel.
 *
 * @param base PDM base pointer.
 * @param handle PDM eDMA handle pointer.
 * @param channel channel index.
 * @param config pdm channel configurations.
 */
void PDM_TransferSetChannelConfigEDMA(PDM_Type *base,
                                      pdm_edma_handle_t *handle,
                                      uint32_t channel,
                                      const pdm_channel_config_t *config);

/*!
 * @brief Performs a non-blocking PDM receive using eDMA.
 *
 * @note This interface returns immediately after the transfer initiates. Call
 * the PDM_GetReceiveRemainingBytes to poll the transfer status and check whether the PDM transfer is finished.
 *
 * Mcaro MCUX_SDK_PDM_EDMA_PDM_ENABLE_INTERNAL can control whether PDM is enabled internally or externally.
 *
 * 1. Scatter gather case:
 * This functio support dynamic scatter gather and staic scatter gather,
 * a. for the dynamic scatter gather case:
 * Application should call PDM_TransferReceiveEDMA function continuously to make sure new receive request is submit
 * before the previous one finish. b. for the static scatter gather case: Application should use the link transfer
 * feature and make sure a loop link transfer is provided, such as:
 * @code pdm_edma_transfer_t pdmXfer[2] =
 *   {
 *       {
 *       .data  = s_buffer,
 *       .dataSize = BUFFER_SIZE,
 *       .linkTransfer = &pdmXfer[1],
 *       },
 *
 *       {
 *       .data  = &s_buffer[BUFFER_SIZE],
 *       .dataSize = BUFFER_SIZE,
 *       .linkTransfer = &pdmXfer[0]
 *       },
 *   };
 * @endcode
 *
 * 2. Multi channel case:
 * This function support receive multi pdm channel data, for example, if two channel is requested,
 * @code
 * PDM_TransferSetChannelConfigEDMA(DEMO_PDM, &s_pdmRxHandle_0, DEMO_PDM_ENABLE_CHANNEL_0, &channelConfig);
 * PDM_TransferSetChannelConfigEDMA(DEMO_PDM, &s_pdmRxHandle_0, DEMO_PDM_ENABLE_CHANNEL_1, &channelConfig);
 * PDM_TransferReceiveEDMA(DEMO_PDM, &s_pdmRxHandle_0, pdmXfer);
 * @endcode
 * The output data will be formatted as below if handle->interleaveType =
 * kPDM_EDMAMultiChannelInterleavePerChannelSample :
 * -------------------------------------------------------------------------
 * |CHANNEL0 | CHANNEL1 | CHANNEL0 | CHANNEL1 | CHANNEL0 | CHANNEL 1 | ....|
 * -------------------------------------------------------------------------
 *
 * The output data will be formatted as below if handle->interleaveType = kPDM_EDMAMultiChannelInterleavePerChannelBlock
 * :
 * ----------------------------------------------------------------------------------------------------------------------
 * |CHANNEL3 | CHANNEL3 | CHANNEL3 | .... | CHANNEL4 | CHANNEL 4 | CHANNEL4 |....| CHANNEL5 | CHANNEL 5 | CHANNEL5
 * |....|
 * ----------------------------------------------------------------------------------------------------------------------
 * Note: the dataSize of xfer is the total data size, while application using
 * kPDM_EDMAMultiChannelInterleavePerChannelBlock, the buffer size for each PDM channel is channelSize = dataSize /
 * channelNums, then there are limitation for this feature,
 * 1. 3 DMIC array: the dataSize shall be 4 * (channelSize)
 * The addtional buffer is mandantory for edma modulo feature.
 * 2. The kPDM_EDMAMultiChannelInterleavePerChannelBlock feature support below dmic array only,
 *    2 DMIC array: CHANNEL3, CHANNEL4
 *    3 DMIC array: CHANNEL3, CHANNEL4, CHANNEL5
 *    4 DMIC array: CHANNEL3, CHANNEL4, CHANNEL5, CHANNEL6
 * Any other combinations is not support, that is to SAY, THE FEATURE SUPPORT RECEIVE START FROM CHANNEL3 ONLY AND 4
 * MAXIMUM DMIC CHANNELS.
 *
 * @param base PDM base pointer
 * @param handle PDM eDMA handle pointer.
 * @param xfer Pointer to DMA transfer structure.
 * @retval kStatus_Success Start a PDM eDMA receive successfully.
 * @retval kStatus_InvalidArgument The input argument is invalid.
 * @retval kStatus_RxBusy PDM is busy receiving data.
 */
status_t PDM_TransferReceiveEDMA(PDM_Type *base, pdm_edma_handle_t *handle, pdm_edma_transfer_t *xfer);

/*!
 * @brief Terminate all PDM receive.
 *
 * This function will clear all transfer slots buffered in the pdm queue. If users only want to abort the
 * current transfer slot, please call PDM_TransferAbortReceiveEDMA.
 *
 * @param base PDM base pointer.
 * @param handle PDM eDMA handle pointer.
 */
void PDM_TransferTerminateReceiveEDMA(PDM_Type *base, pdm_edma_handle_t *handle);

/*!
 * @brief Aborts a PDM receive using eDMA.
 *
 * This function only aborts the current transfer slots, the other transfer slots' information still kept
 * in the handler. If users want to terminate all transfer slots, just call PDM_TransferTerminateReceiveEDMA.
 *
 * @param base PDM base pointer
 * @param handle PDM eDMA handle pointer.
 */
void PDM_TransferAbortReceiveEDMA(PDM_Type *base, pdm_edma_handle_t *handle);

/*!
 * @brief Gets byte count received by PDM.
 *
 * @param base PDM base pointer
 * @param handle PDM eDMA handle pointer.
 * @param count Bytes count received by PDM.
 * @retval kStatus_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is no non-blocking transaction in progress.
 */
status_t PDM_TransferGetReceiveCountEDMA(PDM_Type *base, pdm_edma_handle_t *handle, size_t *count);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif
