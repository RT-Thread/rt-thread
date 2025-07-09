/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_ASRC_P2P_EDMA_H_
#define FSL_ASRC_P2P_EDMA_H_

#include "fsl_edma.h"
#include "fsl_asrc.h"

/*!
 * @addtogroup asrc_edma_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
#define FSL_ASRC_EDMA_DRIVER_VERSION (MAKE_VERSION(2, 2, 0)) /*!< Version 2.2.0 */
/*! @} */
/*!< @brief ASRC IN edma QUEUE size */
#define ASRC_XFER_IN_QUEUE_SIZE  4U
#define ASRC_XFER_OUT_QUEUE_SIZE (ASRC_XFER_QUEUE_SIZE * 2U)

typedef struct _asrc_edma_handle asrc_edma_handle_t;

/*! @brief ASRC eDMA transfer callback function for finish and error */
typedef void (*asrc_edma_callback_t)(ASRC_Type *base, asrc_edma_handle_t *handle, status_t status, void *userData);

/*! @brief ASRC trigger peripheral function pointer */
typedef void (*asrc_start_peripheral_t)(bool start);
/*! @brief destination peripheral configuration */
typedef struct _asrc_p2p_edma_config
{
    asrc_start_peripheral_t startPeripheral; /*!< trigger peripheral start */
} asrc_p2p_edma_config_t;

/*!@ brief asrc in edma handler */
typedef struct _asrc_in_edma_handle
{
    edma_handle_t *inDmaHandle; /*!< DMA handler for ASRC in */

    uint8_t tcd[(ASRC_XFER_IN_QUEUE_SIZE + 1U) * sizeof(edma_tcd_t)]; /*!< TCD pool for eDMA send. */

    uint32_t sampleWidth;                         /*!< input data width */
    uint32_t fifoThreshold;                       /*!< ASRC input fifo threshold */
    uint32_t *asrcQueue[ASRC_XFER_IN_QUEUE_SIZE]; /*!< Transfer queue storing queued transfer. */
    size_t transferSize[ASRC_XFER_IN_QUEUE_SIZE]; /*!< Data bytes need to transfer */
    volatile uint8_t queueUser;                   /*!< Index for user to queue transfer. */
    volatile uint8_t queueDriver;                 /*!< Index for driver to get the transfer data and size */
    uint32_t state;                               /*!< Internal state for ASRC eDMA transfer */

    const asrc_p2p_edma_config_t *peripheralConfig; /*!< peripheral configuration pointer */
} asrc_in_edma_handle_t;

/*!@ brief asrc out edma handler */
typedef struct _asrc_out_edma_handle
{
    edma_handle_t *outDmaHandle; /*!< DMA handler for ASRC out */

    uint8_t tcd[(ASRC_XFER_OUT_QUEUE_SIZE + 1U) * sizeof(edma_tcd_t)]; /*!< TCD pool for eDMA send. */

    uint32_t sampleWidth;                           /*!< output data width */
    uint32_t fifoThreshold;                         /*!< ASRC output fifo threshold */
    uint32_t *asrcQueue[ASRC_XFER_OUT_QUEUE_SIZE];  /*!< Transfer queue storing queued transfer. */
    size_t transferSize[ASRC_XFER_OUT_QUEUE_SIZE];  /*!< Data bytes need to transfer */
    volatile uint8_t queueUser;                     /*!< Index for user to queue transfer. */
    volatile uint8_t queueDriver;                   /*!< Index for driver to get the transfer data and size */
    uint32_t state;                                 /*!< Internal state for ASRC eDMA transfer */
    const asrc_p2p_edma_config_t *peripheralConfig; /*!< peripheral configuration pointer */
} asrc_out_edma_handle_t;

/*! @brief ASRC DMA transfer handle.*/
struct _asrc_edma_handle
{
    asrc_in_edma_handle_t in;        /*!< asrc in handler */
    asrc_out_edma_handle_t out;      /*!< asrc out handler */
    asrc_channel_pair_t channelPair; /*!< channel pair */
    void *userData;                  /*!< User callback parameter */
    asrc_edma_callback_t callback;   /*!< Callback for users while transfer finish or error occurs */
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
 * @brief Initializes the ASRC IN eDMA handle.
 *
 * This function initializes the ASRC DMA handle, which can be used for other ASRC transactional APIs.
 * Usually, for a specified ASRC channel pair, call this API once to get the initialized handle.
 *
 * @param base ASRC base pointer.
 * @param channelPair ASRC channel pair
 * @param handle ASRC eDMA handle pointer.
 * @param callback Pointer to user callback function.
 * @param inDmaHandle DMA handler for ASRC in.
 * @param periphConfig peripheral configuration.
 * @param userData User parameter passed to the callback function.
 */
void ASRC_TransferInCreateHandleEDMA(ASRC_Type *base,
                                     asrc_edma_handle_t *handle,
                                     asrc_channel_pair_t channelPair,
                                     asrc_edma_callback_t callback,
                                     edma_handle_t *inDmaHandle,
                                     const asrc_p2p_edma_config_t *periphConfig,
                                     void *userData);

/*!
 * @brief Initializes the ASRC OUT eDMA handle.
 *
 * This function initializes the ASRC DMA handle, which can be used for other ASRC transactional APIs.
 * Usually, for a specified ASRC channel pair, call this API once to get the initialized handle.
 *
 * @param base ASRC base pointer.
 * @param channelPair ASRC channel pair
 * @param handle ASRC eDMA handle pointer.
 * @param callback Pointer to user callback function.
 * @param outDmaHandle DMA handler for ASRC out.
 * @param periphConfig peripheral configuration.
 * @param userData User parameter passed to the callback function.
 */
void ASRC_TransferOutCreateHandleEDMA(ASRC_Type *base,
                                      asrc_edma_handle_t *handle,
                                      asrc_channel_pair_t channelPair,
                                      asrc_edma_callback_t callback,
                                      edma_handle_t *outDmaHandle,
                                      const asrc_p2p_edma_config_t *periphConfig,
                                      void *userData);

/*!
 * @brief Configures the ASRC P2P channel pair.
 *
 *
 * @param base ASRC base pointer.
 * @param handle ASRC eDMA handle pointer.
 * @param asrcConfig asrc configurations.
 * @param inSampleRate ASRC input sample rate.
 * @param outSampleRate ASRC output sample rate.
 */
status_t ASRC_TransferSetChannelPairConfigEDMA(ASRC_Type *base,
                                               asrc_edma_handle_t *handle,
                                               asrc_channel_pair_config_t *asrcConfig,
                                               uint32_t inSampleRate,
                                               uint32_t outSampleRate);

/*!
 * @brief Get output sample buffer size can be transferred by edma.
 *
 * @note This API is depends on the ASRC output configuration, should be called after the
 * ASRC_TransferSetChannelPairConfigEDMA.
 *
 * @param base asrc base pointer.
 * @param handle ASRC channel pair edma handle.
 * @param inSampleRate input sample rate.
 * @param outSampleRate output sample rate.
 * @param inSamplesize input sampleS size.
 * @retval output buffer size in byte.
 */
uint32_t ASRC_GetOutSamplesSizeEDMA(
    ASRC_Type *base, asrc_edma_handle_t *handle, uint32_t inSampleRate, uint32_t outSampleRate, uint32_t inSamplesize);

/*!
 * @brief Performs a non-blocking ASRC m2m convert using EDMA.
 *
 * @note This interface returns immediately after the transfer initiates.

 * @param base ASRC base pointer.
 * @param handle ASRC eDMA handle pointer.
 * @param xfer Pointer to the DMA transfer structure.
 * @retval kStatus_Success Start a ASRC eDMA send successfully.
 * @retval kStatus_InvalidArgument The input argument is invalid.
 * @retval kStatus_ASRCQueueFull ASRC EDMA driver queue is full.
 */
status_t ASRC_TransferEDMA(ASRC_Type *base, asrc_edma_handle_t *handle, asrc_transfer_t *xfer);

/*!
 * @brief Aborts a ASRC IN transfer using eDMA.
 *
 * This function only aborts the current transfer slots, the other transfer slots' information still kept
 * in the handler. If users want to terminate all transfer slots, just call ASRC_TransferTerminalP2PEDMA.
 *
 * @param base ASRC base pointer.
 * @param handle ASRC eDMA handle pointer.
 */
void ASRC_TransferInAbortEDMA(ASRC_Type *base, asrc_edma_handle_t *handle);

/*!
 * @brief Aborts a ASRC OUT transfer using eDMA.
 *
 * This function only aborts the current transfer slots, the other transfer slots' information still kept
 * in the handler. If users want to terminate all transfer slots, just call ASRC_TransferTerminalP2PEDMA.
 *
 * @param base ASRC base pointer.
 * @param handle ASRC eDMA handle pointer.
 */
void ASRC_TransferOutAbortEDMA(ASRC_Type *base, asrc_edma_handle_t *handle);

/*!
 * @brief Terminate In ASRC Convert.
 *
 * This function will clear all transfer slots buffered in the asrc queue. If users only want to abort the
 * current transfer slot, please call ASRC_TransferAbortPP2PEDMA.
 *
 * @param base ASRC base pointer.
 * @param handle ASRC eDMA handle pointer.
 */
void ASRC_TransferInTerminalEDMA(ASRC_Type *base, asrc_edma_handle_t *handle);

/*!
 * @brief Terminate Out ASRC Convert.
 *
 * This function will clear all transfer slots buffered in the asrc queue. If users only want to abort the
 * current transfer slot, please call ASRC_TransferAbortPP2PEDMA.
 *
 * @param base ASRC base pointer.
 * @param handle ASRC eDMA handle pointer.
 */
void ASRC_TransferOutTerminalEDMA(ASRC_Type *base, asrc_edma_handle_t *handle);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif
