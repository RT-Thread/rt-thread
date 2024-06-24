/*
 * Copyright 2019,2021,2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_FLEXIO_MCULCD_SMARTDMA_H_
#define FSL_FLEXIO_MCULCD_SMARTDMA_H_

#include "fsl_smartdma.h"
#include "fsl_flexio_mculcd.h"

/*!
 * @addtogroup flexio_smartdma_mculcd
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*@{*/
/*! @brief FlexIO MCULCD SMARTDMA driver version. */
#define FSL_FLEXIO_MCULCD_SMARTDMA_DRIVER_VERSION (MAKE_VERSION(2, 0, 4))
/*@}*/

/*! @brief SMARTDMA transfer size should be multiple of 64 bytes. */
#define FLEXIO_MCULCD_SMARTDMA_TX_LEN_ALIGN 64U

/*! @brief SMARTDMA transfer memory address should be 4 byte aligned. */
#define FLEXIO_MCULCD_SMARTDMA_TX_ADDR_ALIGN 4U

/*! @brief  typedef for flexio_mculcd_smartdma_handle_t in advance. */
typedef struct _flexio_mculcd_smartdma_handle flexio_mculcd_smartdma_handle_t;

/*! @brief FlexIO MCULCD master callback for transfer complete.
 *
 * When transfer finished, the callback function is called and returns the
 * @p status as kStatus_FLEXIO_MCULCD_Idle.
 */
typedef void (*flexio_mculcd_smartdma_transfer_callback_t)(FLEXIO_MCULCD_Type *base,
                                                           flexio_mculcd_smartdma_handle_t *handle,
                                                           status_t status,
                                                           void *userData);

/*! @brief FlexIO MCULCD SMARTDMA transfer handle, users should not touch the
 * content of the handle.*/
struct _flexio_mculcd_smartdma_handle
{
    FLEXIO_MCULCD_Type *base;       /*!< Pointer to the FLEXIO_MCULCD_Type. */
    size_t dataCount;               /*!< Total count to be transferred. */
    uint32_t dataAddrOrSameValue;   /*!< When sending the same value for many times,
                                       this is the value to send. When writing or reading array,
                                       this is the address of the data array. */
    size_t dataCountUsingEzh;       /*!< Data transfered using SMARTDMA. */
    volatile size_t remainingCount; /*!< Remaining count to transfer. */
    volatile uint32_t state;        /*!< FlexIO MCULCD driver internal state. */
    uint8_t smartdmaApi;            /*!< The SMARTDMA API used during transfer. */
    bool needColorConvert;          /*!< Need color convert or not. */
    uint8_t blockingXferBuffer[FLEXIO_MCULCD_SMARTDMA_TX_LEN_ALIGN * 3 /
                               2];                                 /*!< Used for blocking method color space convet. */
    flexio_mculcd_smartdma_transfer_callback_t completionCallback; /*!< Callback for MCULCD SMARTDMA transfer */
    void *userData;                                                /*!< User Data for MCULCD SMARTDMA callback */
    smartdma_flexio_mculcd_param_t smartdmaParam;                  /*!< SMARTDMA function parameters. */
    uint32_t smartdmaStack[1];                                     /*!< SMARTDMA function stack. */
};

/*! @brief FlexIO MCULCD SMARTDMA configuration. */
typedef struct _flexio_mculcd_smartdma_config
{
    flexio_mculcd_pixel_format_t inputPixelFormat;  /*!< The pixel format in the frame buffer. */
    flexio_mculcd_pixel_format_t outputPixelFormat; /*!< The pixel format on the 8080/68k bus. */
} flexio_mculcd_smartdma_config_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name SMARTDMA Transactional
 * @{
 */

/*!
 * @brief Initializes the FLEXO MCULCD master SMARTDMA handle.
 *
 * This function initializes the FLEXO MCULCD master SMARTDMA handle which can be
 * used for other FLEXO MCULCD transactional APIs. For a specified FLEXO MCULCD
 * instance, call this API once to get the initialized handle.
 *
 * @param base Pointer to FLEXIO_MCULCD_Type structure.
 * @param handle Pointer to flexio_mculcd_smartdma_handle_t structure to store the
 * transfer state.
 * @param config Pointer to the configuration.
 * @param callback MCULCD transfer complete callback, NULL means no callback.
 * @param userData callback function parameter.
 * @retval kStatus_Success Successfully create the handle.
 */
status_t FLEXIO_MCULCD_TransferCreateHandleSMARTDMA(FLEXIO_MCULCD_Type *base,
                                                    flexio_mculcd_smartdma_handle_t *handle,
                                                    const flexio_mculcd_smartdma_config_t *config,
                                                    flexio_mculcd_smartdma_transfer_callback_t callback,
                                                    void *userData);

/*!
 * @brief Performs a non-blocking FlexIO MCULCD transfer using SMARTDMA.
 *
 * This function returns immediately after transfer initiates. Use the callback
 * function to check whether the transfer is completed.
 *
 * @param base pointer to FLEXIO_MCULCD_Type structure.
 * @param handle pointer to flexio_mculcd_smartdma_handle_t structure to store the
 * transfer state.
 * @param xfer Pointer to FlexIO MCULCD transfer structure.
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 * @retval kStatus_FLEXIO_MCULCD_Busy FlexIO MCULCD is not idle, it is running another
 * transfer.
 */
status_t FLEXIO_MCULCD_TransferSMARTDMA(FLEXIO_MCULCD_Type *base,
                                        flexio_mculcd_smartdma_handle_t *handle,
                                        flexio_mculcd_transfer_t *xfer);

/*!
 * @brief Aborts a FlexIO MCULCD transfer using SMARTDMA.
 *
 * @param base pointer to FLEXIO_MCULCD_Type structure.
 * @param handle FlexIO MCULCD SMARTDMA handle pointer.
 */
void FLEXIO_MCULCD_TransferAbortSMARTDMA(FLEXIO_MCULCD_Type *base, flexio_mculcd_smartdma_handle_t *handle);

/*!
 * @brief Gets the remaining bytes for FlexIO MCULCD SMARTDMA transfer.
 *
 * @param base pointer to FLEXIO_MCULCD_Type structure.
 * @param handle FlexIO MCULCD SMARTDMA handle pointer.
 * @param count Number of count transferred so far by the SMARTDMA transaction.
 * @retval kStatus_Success Get the transferred count Successfully.
 * @retval kStatus_NoTransferInProgress No transfer in process.
 */
status_t FLEXIO_MCULCD_TransferGetCountSMARTDMA(FLEXIO_MCULCD_Type *base,
                                                flexio_mculcd_smartdma_handle_t *handle,
                                                size_t *count);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* FSL_FLEXIO_MCULCD_SMARTDMA_H_ */
