/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SMARTCARD_EMVSIM_H_
#define _FSL_SMARTCARD_EMVSIM_H_

#include "fsl_smartcard.h"

/*!
 * @addtogroup smartcard_emvsim_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief EMV RX NACK interrupt generation threshold */
#define SMARTCARD_EMV_RX_NACK_THRESHOLD (5u)

/*! @brief EMV TX NACK interrupt generation threshold */
#define SMARTCARD_EMV_TX_NACK_THRESHOLD (5u)

/*! @brief Smart card Word Wait Timer adjustment value */
#define SMARTCARD_WWT_ADJUSTMENT (160u)

/*! @brief Smart card Character Wait Timer adjustment value */
#define SMARTCARD_CWT_ADJUSTMENT (3u)

/*! @brief General Purpose Counter clock selections */
typedef enum _emvsim_gpc_clock_select
{
    kEMVSIM_GPCClockDisable = 0u, /*!< Disabled */
    kEMVSIM_GPCCardClock    = 1u, /*!< Card clock */
    kEMVSIM_GPCRxClock      = 2u, /*!< Receive clock */
    kEMVSIM_GPCTxClock      = 3u, /*!< Transmit ETU clock */
} emvsim_gpc_clock_select_t;

/*! @brief EMVSIM card presence detection edge control */
typedef enum _presence_detect_edge
{
    kEMVSIM_DetectOnFallingEdge = 0u, /*!< Presence detected on the falling edge */
    kEMVSIM_DetectOnRisingEdge  = 1u, /*!< Presence detected on the rising edge */
} emvsim_presence_detect_edge_t;

/*! @brief EMVSIM card presence detection status */
typedef enum _presence_detect_status
{
    kEMVSIM_DetectPinIsLow  = 0u, /*!< Presence detected pin is logic low */
    kEMVSIM_DetectPinIsHigh = 1u, /*!< Presence detected pin is logic high */
} emvsim_presence_detect_status_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Smart card EMVSIM Driver
 * @{
 */

/*!
 * @brief Fills in the smartcard_card_params structure with default values according to the EMV 4.3 specification.
 *
 * @param cardParams The configuration structure of type smartcard_interface_config_t.
 * Function fill in members:
 *        Fi = 372;
 *        Di = 1;
 *        currentD = 1;
 *        WI = 0x0A;
 *        GTN = 0x00;
 * with default values.
 */
void SMARTCARD_EMVSIM_GetDefaultConfig(smartcard_card_params_t *cardParams);

/*!
 * @brief Initializes an EMVSIM peripheral for the Smart card/ISO-7816 operation.
 *
 * This function un-gates the EMVSIM clock, initializes the module to EMV default settings,
 * configures the IRQ, enables the module-level interrupt to the core and, initializes the driver context.
 *
 * @param base The EMVSIM peripheral base address.
 * @param context A pointer to the smart card driver context structure.
 * @param srcClock_Hz Smart card clock generation module source clock.
 *
 * @return An error code or kStatus_SMARTCARD_Success.
 */
status_t SMARTCARD_EMVSIM_Init(EMVSIM_Type *base, smartcard_context_t *context, uint32_t srcClock_Hz);

/*!
 * @brief This function disables the EMVSIM interrupts, disables the transmitter and receiver,
 * flushes the FIFOs, and gates EMVSIM clock in SIM.
 *
 * @param base The EMVSIM module base address.
 */
void SMARTCARD_EMVSIM_Deinit(EMVSIM_Type *base);

/*!
 * @brief Returns whether the previous EMVSIM transfer has finished.
 *
 * When performing an async transfer, call this function to ascertain the context of the
 * current transfer: in progress (or busy) or complete (success). If the
 * transfer is still in progress, the user can obtain the number of words that have not been
 * transferred.
 *
 * @param base The EMVSIM module base address.
 * @param context A pointer to a smart card driver context structure.
 *
 * @return The number of bytes not transferred.
 */
int32_t SMARTCARD_EMVSIM_GetTransferRemainingBytes(EMVSIM_Type *base, smartcard_context_t *context);

/*!
 * @brief Terminates an asynchronous EMVSIM transfer early.
 *
 * During an async EMVSIM transfer, the user can terminate the transfer early
 * if the transfer is still in progress.
 *
 * @param base The EMVSIM peripheral address.
 * @param context A pointer to a smart card driver context structure.
 * @retval kStatus_SMARTCARD_Success The transmit abort was successful.
 * @retval kStatus_SMARTCARD_NoTransmitInProgress No transmission is currently in progress.
 */
status_t SMARTCARD_EMVSIM_AbortTransfer(EMVSIM_Type *base, smartcard_context_t *context);

/*!
 * @brief Transfer data using interrupts.
 *
 * A non-blocking (also known as asynchronous) function means that the function returns
 * immediately after initiating the transfer function. The application has to get the
 * transfer status to see when the transfer is complete. In other words, after calling the non-blocking
 * (asynchronous) transfer function, the application must get the transfer status to check if the transmit
 * is completed or not.
 *
 * @param base The EMVSIM peripheral base address.
 * @param context A pointer to a smart card driver context structure.
 * @param xfer A pointer to the smart card transfer structure where the linked buffers and sizes are stored.
 *
 * @return An error code or kStatus_SMARTCARD_Success.
 */
status_t SMARTCARD_EMVSIM_TransferNonBlocking(EMVSIM_Type *base, smartcard_context_t *context, smartcard_xfer_t *xfer);

/*!
 * @brief Controls the EMVSIM module per different user request.
 *
 * @param base The EMVSIM peripheral base address.
 * @param context A pointer to a smart card driver context structure.
 * @param control Control type.
 * @param param Integer value of specific to control command.
 *
 * return kStatus_SMARTCARD_Success in success.
 * return kStatus_SMARTCARD_OtherError in case of error.
 */
status_t SMARTCARD_EMVSIM_Control(EMVSIM_Type *base,
                                  smartcard_context_t *context,
                                  smartcard_control_t control,
                                  uint32_t param);

/*!
 * @brief Handles EMVSIM module interrupts.
 *
 * @param base The EMVSIM peripheral base address.
 * @param context A pointer to a smart card driver context structure.
 */
void SMARTCARD_EMVSIM_IRQHandler(EMVSIM_Type *base, smartcard_context_t *context);
/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_SMARTCARD_EMVSIM_H_*/
