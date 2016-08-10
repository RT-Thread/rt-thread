/*
 * Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSL_SMARTCARD_UART_DRIVER_H__
#define __FSL_SMARTCARD_UART_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_os_abstraction.h"
#include "fsl_uart_hal.h"
#if defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
#include "fsl_dma_request.h"
#endif
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
#include "fsl_edma_request.h"
#endif
#include "fsl_smartcard_driver.h"

/*!
 * @addtogroup smartcard_driver
 * @{
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Table of base addresses for UART instances. */
extern UART_Type * const g_uartBase[UART_INSTANCE_COUNT];

/*******************************************************************************
 * Definitions
 ******************************************************************************/ 
#define EMV_RX_NACK_THRESHOLD       (5U)
#define EMV_TX_NACK_THRESHOLD       (3U)
#define EMV_RX_TO_TX_GUARD_TIME_T0  (4U)
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Smart card Interrupt Driver
 * @{
 */

/*!
 * @brief Initializes an UART instance for Smart card/ISO-7816 operation.
 *
 * This function initializes the run-time state structure to keep track of the on-going
 * transfers, un-gates the clock to the Smart card module, initializes the module
 * to user-defined settings and default settings, configures the IRQ state structure, and enables
 * the module-level interrupt to the core, initializes the DMA, and enables the Smart card module 
 * transmitter and receiver.
 *
 * @param instance The UART instance number.
 * @param smartcardStatePtr A pointer to the Smart card driver state structure memory. The user is only
 *  responsible to pass in the memory for this run-time state structure and the Smart card driver
 *  fills out the members. This run-time state structure keeps track of the
 *  current transfer in progress.
 * @param smartcardUserConfig The user configuration structure of type smartcard_user_config_t. The user
 *  is responsible to fill out the members of this structure and to pass the pointer of this structure
 *  into this function.
 * @return An error code or kStatus_SMARTCARD_Success.
 */
smartcard_status_t SMARTCARD_UART_DRV_Init(uint32_t instance, 
                                    smartcard_state_t * smartcardStatePtr,
                                    const smartcard_user_config_t * smartcardUserConfig);

/*!
 * @brief       
 *
 * This function disables the UART interrupts, the transmitter and receiver, and
 * flushes the FIFOs (for modules that support FIFOs).
 *
 * @param instance The UART instance number.
 */
void SMARTCARD_UART_DRV_Deinit(uint32_t instance);

/*!
 * @brief Sends (transmits) data out through the UART module using a blocking method.
 *
 * A blocking (also known as synchronous) function means that the function does not return until
 * the transmit is complete. This blocking function is used to send data through the UART port.
 *
 * @param instance The UART instance number.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_SMARTCARD_Success.
 */
smartcard_status_t SMARTCARD_UART_DRV_SendDataBlocking(uint32_t instance, 
                                      const uint8_t * txBuff,
                                      uint32_t txSize, 
                                      uint32_t timeout);

/*!
 * @brief Sends (transmits) data through the UART module using a non-blocking method.
 *
 * A non-blocking (also known as synchronous) function means that the function returns
 * immediately after initiating the transmit function. The application has to get the
 * transmit status to see when the transmit is complete. In other words, after calling non-blocking
 * (asynchronous) send function, the application must get the transmit status to check if transmit
 * is complete.
 *
 * @param instance The UART module instance number.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @return An error code or kStatus_SMARTCARD_Success.
 */
smartcard_status_t SMARTCARD_UART_DRV_SendData(uint32_t instance, 
                                      const uint8_t * txBuff, 
                                      uint32_t txSize);

/*!
 * @brief Returns whether the previous UART transmit has finished.
 *
 * When performing an a-sync transmit, call this function to ascertain the state of the
 * current transmission: in progress (or busy) or complete (success). If the
 * transmission is still in progress, the user can obtain the number of words that have been
 * transferred.
 *
 * @param instance The UART module instance number.
 * @param bytesRemaining A pointer to a value that is filled in with the number of bytes that
 *                       are remaining in the active transfer.
 * @retval kStatus_UART_Success The transmit has completed successfully.
 * @retval kStatus_SMARTCARD_TxBusy The transmit is still in progress. bytesTransmitted is
 *     filled with the number of bytes which are transmitted up to that point.
 */
smartcard_status_t SMARTCARD_UART_DRV_GetTransmitStatus(uint32_t instance, 
                                      uint32_t * bytesRemaining);

/*!
 * @brief Terminates an asynchronous UART transmission early.
 *
 * During an a-sync UART transmission, the user can terminate the transmission early
 * if the transmission is still in progress.
 *
 * @param instance The UART module instance number.
 * @retval kStatus_SMARTCARD_Success The transmit was successful.
 * @retval kStatus_SMARTCARD_NoTransmitInProgress No transmission is currently in progress.
 */
smartcard_status_t SMARTCARD_UART_DRV_AbortSendingData(uint32_t instance);

/*!
 * @brief Gets (receives) data from the UART module using a blocking method.
 *
 * A blocking (also known as synchronous) function means that the function does not return until
 * the receive is complete. This blocking function receives data through the UART port.
 *
 * @param instance The UART module instance number.
 * @param rxBuff A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @param rcvdSize The number of bytes actually received.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_SMARTCARD_Success.
 */
smartcard_status_t SMARTCARD_UART_DRV_ReceiveDataBlocking(uint32_t instance,
                                      uint8_t * rxBuff,
                                      uint32_t rxSize,
                                      uint32_t * rcvdSize,
                                      uint32_t timeout);

/*!
 * @brief Gets (receives) data from the UART module using a non-blocking method.
 *
 * A non-blocking (also known as synchronous) function means that the function returns
 * immediately after initiating the receive function. The application has to get the
 * receive status to see when the receive is complete. In other words, after calling non-blocking
 * (asynchronous) get function, the application must get the receive status to check if receive
 * is completed or not.
 *
 * @param instance The UART module instance number.
 * @param rxBuff  A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @return An error code or kStatus_SMARTCARD_Success.
 */
smartcard_status_t SMARTCARD_UART_DRV_ReceiveData(uint32_t instance, 
                                      uint8_t * rxBuff, 
                                      uint32_t rxSize);

/*!
 * @brief Returns whether the previous UART receive is complete.
 *
 * When performing an a-sync receive, the user can call this function to ascertain the state of the
 * current receive progress: in progress (or busy) or complete (success). In addition, if the
 * receive is still in progress, the user can obtain the number of words that have been
 * currently received.
 *
 * @param instance The UART module instance number.
 * @param bytesRemaining A pointer to a value that is filled in with the number of bytes which
 *                       still need to be received in the active transfer.
 *
 * @retval kStatus_SMARTCARD_Success The receive has completed successfully.
 * @retval kStatus_SMARTCARD_RxBusy The receive is still in progress. bytesReceived is
 *     filled with the number of bytes which are received up to that point.
 */
smartcard_status_t SMARTCARD_UART_DRV_GetReceiveStatus(uint32_t instance, 
                                      uint32_t * bytesRemaining);

/*!
 * @brief Terminates an asynchronous UART receive early.
 *
 * During an a-sync UART receive, the user can terminate the receive early
 * if the receive is still in progress.
 *
 * @param instance The UART module instance number.
 *
 * @retval kStatus_SMARTCARD_Success The receive was successful.
 * @retval kStatus_SMARTCARD_NoReceiveInProgress No receive is currently in progress.
 */
smartcard_status_t SMARTCARD_UART_DRV_AbortReceivingData(uint32_t instance);

/*!
 * @brief Controls UART module as per different user request.
 *
 * @param instance The UART module instance number.
 * @param control control type
 * @param controlBuff A pointer to parameter specific to control type
 *
 * @retval kStatus_SMARTCARD_Success The control operation was successful.
 */
smartcard_status_t SMARTCARD_UART_DRV_Control(uint32_t instance, 
                                    smartcard_control_t control, 
                                    void *controlBuff);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_SMARTCARD_UART_DRIVER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

