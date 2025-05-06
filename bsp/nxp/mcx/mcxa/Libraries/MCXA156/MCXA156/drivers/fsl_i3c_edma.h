/*
 * Copyright 2022-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_I3C_EDMA_H_
#define FSL_I3C_EDMA_H_

#include "fsl_i3c.h"
#include "fsl_edma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief I3C EDMA driver version. */
#define FSL_I3C_EDMA_DRIVER_VERSION (MAKE_VERSION(2, 2, 9))
/*! @} */

/*!
 * @addtogroup i3c_master_edma_driver
 * @{
 */

/* Forward declaration of the transfer descriptor and handle typedefs. */
typedef struct _i3c_master_edma_handle i3c_master_edma_handle_t;

/*! @brief i3c master callback functions. */
typedef struct _i3c_master_edma_callback
{
    void (*slave2Master)(I3C_Type *base, void *userData); /*!< Transfer complete callback */
    void (*ibiCallback)(I3C_Type *base,
                        i3c_master_edma_handle_t *handle,
                        i3c_ibi_type_t ibiType,
                        i3c_ibi_state_t ibiState); /*!< IBI event callback */
    void (*transferComplete)(I3C_Type *base,
                             i3c_master_edma_handle_t *handle,
                             status_t status,
                             void *userData); /*!< Transfer complete callback */
} i3c_master_edma_callback_t;
/*!
 * @brief Driver handle for master EDMA APIs.
 * @note The contents of this structure are private and subject to change.
 */
struct _i3c_master_edma_handle
{
    I3C_Type *base;                      /*!< I3C base pointer. */
    uint8_t state;                       /*!< Transfer state machine current state. */
    uint32_t transferCount;              /*!< Indicates progress of the transfer */
    uint8_t subaddressBuffer[4];         /*!< Saving subaddress command. */
    uint8_t subaddressCount;             /*!< Saving command count. */
    i3c_master_transfer_t transfer;      /*!< Copy of the current transfer info. */
    i3c_master_edma_callback_t callback; /*!< Callback function pointer. */
    void *userData;                      /*!< Application data passed to callback. */
    edma_handle_t *rxDmaHandle;          /*!< Handle for receive DMA channel. */
    edma_handle_t *txDmaHandle;          /*!< Handle for transmit DMA channel. */
    uint8_t ibiAddress;                  /*!< Slave address which request IBI. */
    uint8_t *ibiBuff;                    /*!< Pointer to IBI buffer to keep ibi bytes. */
    size_t ibiPayloadSize;               /*!< IBI payload size. */
    i3c_ibi_type_t ibiType;              /*!< IBI type. */
};

/*! @} */

/*!
 * @addtogroup i3c_slave_edma_driver
 * @{
 */
/* Forward declaration of the transfer descriptor and handle typedefs. */
typedef struct _i3c_slave_edma_handle i3c_slave_edma_handle_t;

/*! @brief I3C slave transfer structure */
typedef struct _i3c_slave_edma_transfer
{
    uint32_t event;            /*!< Reason the callback is being invoked. */
    uint8_t *txData;           /*!< Transfer buffer */
    size_t txDataSize;         /*!< Transfer size */
    uint8_t *rxData;           /*!< Transfer buffer */
    size_t rxDataSize;         /*!< Transfer size */
    status_t completionStatus; /*!< Success or error code describing how the transfer completed. Only applies for
                                  #kI3C_SlaveCompletionEvent. */
} i3c_slave_edma_transfer_t;

/*!
 * @brief Slave event callback function pointer type.
 *
 * This callback is used only for the slave DMA transfer API.
 *
 * @param base Base address for the I3C instance on which the event occurred.
 * @param handle   Pointer to slave DMA transfer handle.
 * @param transfer Pointer to transfer descriptor containing values passed to and/or from the callback.
 * @param userData Arbitrary pointer-sized value passed from the application.
 */
typedef void (*i3c_slave_edma_callback_t)(I3C_Type *base, i3c_slave_edma_transfer_t *transfer, void *userData);
/*!
 * @brief I3C slave edma handle structure.
 * @note The contents of this structure are private and subject to change.
 */
struct _i3c_slave_edma_handle
{
    I3C_Type *base;                     /*!< I3C base pointer. */
    i3c_slave_edma_transfer_t transfer; /*!< I3C slave transfer copy. */
    bool isBusy;                        /*!< Whether transfer is busy. */
    bool wasTransmit;                   /*!< Whether the last transfer was a transmit. */
    uint32_t eventMask;                 /*!< Mask of enabled events. */
    i3c_slave_edma_callback_t callback; /*!< Callback function called at transfer event. */
    edma_handle_t *rxDmaHandle;         /*!< Handle for receive DMA channel. */
    edma_handle_t *txDmaHandle;         /*!< Handle for transmit DMA channel. */
    void *userData;                     /*!< Callback parameter passed to callback. */
};
/*! @} */
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @addtogroup i3c_master_edma_driver
 * @{
 */

/*! @name Master DMA */
/*! @{ */

/*!
 * @brief Create a new handle for the I3C master DMA APIs.
 *
 * The creation of a handle is for use with the DMA APIs. Once a handle
 * is created, there is not a corresponding destroy handle. If the user wants to
 * terminate a transfer, the I3C_MasterTransferAbortDMA() API shall be called.
 *
 * For devices where the I3C send and receive DMA requests are OR'd together, the @a txDmaHandle
 * parameter is ignored and may be set to NULL.
 *
 * @param base The I3C peripheral base address.
 * @param handle Pointer to the I3C master driver handle.
 * @param callback User provided pointer to the asynchronous callback function.
 * @param userData User provided pointer to the application callback data.
 * @param rxDmaHandle Handle for the DMA receive channel. Created by the user prior to calling this function.
 * @param txDmaHandle Handle for the DMA transmit channel. Created by the user prior to calling this function.
 */
void I3C_MasterTransferCreateHandleEDMA(I3C_Type *base,
                                        i3c_master_edma_handle_t *handle,
                                        const i3c_master_edma_callback_t *callback,
                                        void *userData,
                                        edma_handle_t *rxDmaHandle,
                                        edma_handle_t *txDmaHandle);

/*!
 * @brief Performs a non-blocking DMA-based transaction on the I3C bus.
 *
 * The callback specified when the @a handle was created is invoked when the transaction has
 * completed.
 *
 * @param base The I3C peripheral base address.
 * @param handle Pointer to the I3C master driver handle.
 * @param transfer The pointer to the transfer descriptor.
 * @retval kStatus_Success The transaction was started successfully.
 * @retval #kStatus_I3C_Busy Either another master is currently utilizing the bus, or another DMA
 *      transaction is already in progress.
 */
status_t I3C_MasterTransferEDMA(I3C_Type *base, i3c_master_edma_handle_t *handle, i3c_master_transfer_t *transfer);

/*!
 * @brief Returns number of bytes transferred so far.
 *
 * @param base The I3C peripheral base address.
 * @param handle Pointer to the I3C master driver handle.
 * @param[out] count Number of bytes transferred so far by the non-blocking transaction.
 * @retval kStatus_Success
 * @retval kStatus_NoTransferInProgress There is not a DMA transaction currently in progress.
 */
status_t I3C_MasterTransferGetCountEDMA(I3C_Type *base, i3c_master_edma_handle_t *handle, size_t *count);

/*!
 * @brief Terminates a non-blocking I3C master transmission early.
 *
 * @note It is not safe to call this function from an IRQ handler that has a higher priority than the
 *      DMA peripheral's IRQ priority.
 *
 * @param base The I3C peripheral base address.
 * @param handle Pointer to the I3C master driver handle.
 */
void I3C_MasterTransferAbortEDMA(I3C_Type *base, i3c_master_edma_handle_t *handle);

/*!
 * @brief Reusable routine to handle master interrupts.
 * @note This function does not need to be called unless you are reimplementing the
 *  nonblocking API's interrupt handler routines to add special functionality.
 * @param base The I3C peripheral base address.
 * @param i3cHandle Pointer to the I3C master DMA driver handle.
 */
void I3C_MasterTransferEDMAHandleIRQ(I3C_Type *base, void *i3cHandle);
/*! @} */

/*! @} */

/*!
 * @addtogroup i3c_slave_edma_driver
 * @{
 */

/*! @name Slave DMA */
/*! @{ */
/*!
 * @brief Create a new handle for the I3C slave DMA APIs.
 *
 * The creation of a handle is for use with the DMA APIs. Once a handle
 * is created, there is not a corresponding destroy handle. If the user wants to
 * terminate a transfer, the I3C_SlaveTransferAbortDMA() API shall be called.
 *
 * For devices where the I3C send and receive DMA requests are OR'd together, the @a txDmaHandle
 * parameter is ignored and may be set to NULL.
 *
 * @param base The I3C peripheral base address.
 * @param handle Pointer to the I3C slave driver handle.
 * @param callback User provided pointer to the asynchronous callback function.
 * @param userData User provided pointer to the application callback data.
 * @param rxDmaHandle Handle for the DMA receive channel. Created by the user prior to calling this function.
 * @param txDmaHandle Handle for the DMA transmit channel. Created by the user prior to calling this function.
 */
void I3C_SlaveTransferCreateHandleEDMA(I3C_Type *base,
                                       i3c_slave_edma_handle_t *handle,
                                       i3c_slave_edma_callback_t callback,
                                       void *userData,
                                       edma_handle_t *rxDmaHandle,
                                       edma_handle_t *txDmaHandle);

/*!
 * @brief Prepares for a non-blocking DMA-based transaction on the I3C bus.
 *
 * The API will do DMA configuration according to the input transfer descriptor, and the data will be transferred when
 * there's bus master requesting transfer from/to this slave. So the timing of call to this API need be aligned
 * with master application to ensure the transfer is executed as expected.
 * Callback specified when the @a handle was created is invoked when the transaction has completed.
 *
 * @param base The I3C peripheral base address.
 * @param handle Pointer to the I3C slave driver handle.
 * @param transfer The pointer to the transfer descriptor.
 * @param eventMask Bit mask formed by OR'ing together #i3c_slave_transfer_event_t enumerators to specify
 *      which events to send to the callback. The transmit and receive events is not allowed to be enabled.
 * @retval kStatus_Success The transaction was started successfully.
 * @retval #kStatus_I3C_Busy Either another master is currently utilizing the bus, or another DMA
 *      transaction is already in progress.
 * @retval #kStatus_Fail The transaction can't be set.
 */
status_t I3C_SlaveTransferEDMA(I3C_Type *base,
                               i3c_slave_edma_handle_t *handle,
                               i3c_slave_edma_transfer_t *transfer,
                               uint32_t eventMask);
/*!
 * @brief Abort a slave edma non-blocking transfer in a early time
 *
 * @param base I3C peripheral base address
 * @param handle pointer to i3c_slave_edma_handle_t structure
 */
void I3C_SlaveTransferAbortEDMA(I3C_Type *base, i3c_slave_edma_handle_t *handle);

/*!
 * @brief Reusable routine to handle slave interrupts.
 * @note This function does not need to be called unless you are reimplementing the
 *  nonblocking API's interrupt handler routines to add special functionality.
 * @param base The I3C peripheral base address.
 * @param i3cHandle Pointer to the I3C slave DMA driver handle.
 */
void I3C_SlaveTransferEDMAHandleIRQ(I3C_Type *base, void *i3cHandle);
/*! @} */

/*! @} */
#if defined(__cplusplus)
}
#endif

#endif /* FSL_I3C_EDMA_H_ */
