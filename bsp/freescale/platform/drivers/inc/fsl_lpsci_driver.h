/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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

#ifndef __FSL_LPSCI_DRIVER_H__
#define __FSL_LPSCI_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_os_abstraction.h"
#include "fsl_clock_manager.h"
#include "fsl_lpsci_hal.h"

/*!
 * @addtogroup lpsci_driver
 * @{
 */

/*!
 * @file
 *
 * This driver is for UART0 if UART0 is a separate chapter in the chip reference
 * manual. For a common UART, use the UART driver.
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Table of base addresses for LPSCI instances. */
extern UART0_Type * const g_lpsciBase[UART0_INSTANCE_COUNT];

/*! @brief Table to save LPSCI IRQ enumeration numbers defined in CMSIS header file */
extern const IRQn_Type g_lpsciRxTxIrqId[UART0_INSTANCE_COUNT];

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief LPSCI receive callback function type. */
typedef void (* lpsci_rx_callback_t)(uint32_t instance, void * lpsciState);

/*! @brief LPSCI transmit callback function type */
typedef void (* lpsci_tx_callback_t)(uint32_t instance, void * lpsciState);

/*!
 * @brief Runtime state of the LPSCI driver.
 *
 * This structure holds data used by the LPSCI peripheral driver to
 * communicate between the transfer function and the interrupt handler. The
 * interrupt handler also uses this information to keep track of its progress.
 * The user passes in the memory for the run-time state structure. The
 * LPSCI driver populates the members.
 */
typedef struct LpsciState {
    const uint8_t * txBuff;        /*!< The buffer of data being sent.*/
    uint8_t * rxBuff;              /*!< The buffer of received data. */
    volatile size_t txSize;        /*!< The remaining number of bytes to be transmitted. */
    volatile size_t rxSize;        /*!< The remaining number of bytes to be received. */
    volatile bool isTxBusy;        /*!< True if there is an active transmit. */
    volatile bool isRxBusy;        /*!< True if there is an active receive. */
    volatile bool isTxBlocking;    /*!< True if transmit is blocking transaction. */
    volatile bool isRxBlocking;    /*!< True if receive is blocking transaction. */
    semaphore_t txIrqSync;         /*!< Used to wait for ISR to complete its TX business. */
    semaphore_t rxIrqSync;         /*!< Used to wait for ISR to complete its RX business. */
    lpsci_rx_callback_t rxCallback; /*!< Callback to invoke after receiving byte.*/
    void * rxCallbackParam;         /*!< Receive callback parameter pointer.*/
    lpsci_tx_callback_t txCallback; /*!< Callback to invoke after transmitting byte.*/
    void * txCallbackParam;         /*!< Transmit callback parameter pointer.*/
} lpsci_state_t;

/*! @brief User configuration structure for the LPSCI driver 
 * @internal gui name="Configuration" id="Configuration" 
 */
typedef struct LpsciUserConfig {
    clock_lpsci_src_t clockSource;      /*!< LPSCI clock source in fsl_sim_hal_'device'.h @internal gui name="Clock source" id="ClockSource" */
    uint32_t baudRate;                  /*!< LPSCI baud rate @internal gui name="Baud rate" id="BaudRate" */
    lpsci_parity_mode_t parityMode;     /*!< parity mode, disabled (default), even, odd @internal gui name="Parity mode" id="Parity" */
    lpsci_stop_bit_count_t stopBitCount; /*!< number of stop bits, 1 stop bit (default) or 2 stop bits @internal gui name="Stop bits" id="StopBits" */
    lpsci_bit_count_per_char_t bitCountPerChar; /*!< number of bits, 8-bit (default) or 9-bit in
                                                    a word (up to 10-bits in some LPSCI instances) @internal gui name="Bits per char" id="DataBits" */
} lpsci_user_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name LPSCI Interrupt Driver
 * @{
 */

/*!
 * @brief Initializes an LPSCI instance for operation.
 *
 * This function initializes the run-time state structure to keep track of the on-going
 * transfers, un-gates the clock to the LPSCI module, initializes the module
 * to user-defined settings and default settings, configures the IRQ state structure and enables
 * the module-level interrupt to the core, and enables the LPSCI module transmitter and receiver.
 * This example shows how to set up the lpsci_state_t and the
 * lpsci_user_config_t parameters and how to call the LPSCI_DRV_Init function by passing
 * in these parameters:
   @code
    lpsci_user_config_t lpsciConfig;
    lpsciConfig.clockSource = kClockLpsciSrcPllFllSel;
    lpsciConfig.baudRate = 9600;
    lpsciConfig.bitCountPerChar = kLpsci8BitsPerChar;
    lpsciConfig.parityMode = kLpsciParityDisabled;
    lpsciConfig.stopBitCount = kLpsciOneStopBit;
    lpsci_state_t lpsciState;
    LPSCI_DRV_Init(instance, &lpsciState, &lpsciConfig);
    @endcode
 *
 * @param instance The LPSCI instance number.
 * @param lpsciStatePtr A pointer to the LPSCI driver state structure memory. The user
 *  passes in the memory for the run-time state structure. The LPSCI driver
 *  populates the members. The run-time state structure keeps track of the
 *  current transfer in progress.
 * @param lpsciUserConfig The user configuration structure of type lpsci_user_config_t. The user
 *  populates the members of this structure and passes the pointer of the
 *  structure to the function.
 * @return An error code or kStatus_LPSCI_Success.
 */
lpsci_status_t LPSCI_DRV_Init(uint32_t instance,
                              lpsci_state_t * lpsciStatePtr,
                              const lpsci_user_config_t * lpsciUserConfig);

/*!
 * @brief Shuts down the LPSCI by disabling interrupts and the transmitter/receiver.
 *
 * This function disables the LPSCI interrupts, disables the transmitter and receiver, and
 * flushes the FIFOs (for modules that support FIFOs).
 *
 * @param instance The LPSCI instance number.
 * @return An error code or kStatus_LPSCI_Success.
 */
lpsci_status_t LPSCI_DRV_Deinit(uint32_t instance);

/*!
 * @brief Installs callback function for the LPSCI receive.
 *
 * @param instance The LPSCI instance number.
 * @param function The LPSCI receive callback function.
 * @param rxBuff The receive buffer used inside IRQHandler. This buffer must be kept as long as the callback is functional.
 * @param callbackParam The LPSCI receive callback parameter pointer.
 * @param alwaysEnableRxIrq Whether always enable receive IRQ or not.
 * @return Former LPSCI receive callback function pointer.
 */
lpsci_rx_callback_t LPSCI_DRV_InstallRxCallback(uint32_t instance,
                                                lpsci_rx_callback_t function,
                                                uint8_t * rxBuff,
                                                void * callbackParam,
                                                bool alwaysEnableRxIrq);
/*!
 * @brief Installs callback function for the LPSCI transmit.
 *
 * @note After the callback is installed, it bypasses part of the LPSCI IRQHandler logic.
 * Therefore, the callback needs to handle the indexes of txBuff and txSize.
 *
 * @param instance The LPSCI instance number.
 * @param function The LPSCI transmit callback function.
 * @param txBuff The transmit buffer used inside IRQHandler. This buffer must be kept as long as the callback is alive.
 * @param callbackParam The LPSCI transmit callback parameter pointer.
 * @return Former LPSCI transmit callback function pointer.
 */
lpsci_tx_callback_t LPSCI_DRV_InstallTxCallback(uint32_t instance, 
                                                lpsci_tx_callback_t function, 
                                                uint8_t * txBuff, 
                                                void * callbackParam);

/*!
 * @brief Sends (transmits) data out through the LPSCI module using a blocking method.
 *
 * A blocking (also known as synchronous) function means that the function does not return until
 * the transmit is complete. This blocking function sends data through the LPSCI port.
 *
 * @param instance The LPSCI instance number.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_LPSCI_Success.
 */
lpsci_status_t LPSCI_DRV_SendDataBlocking(uint32_t instance,
                                          const uint8_t * txBuff,
                                          uint32_t txSize,
                                          uint32_t timeout);

/*!
 * @brief Sends (transmits) data through the LPSCI module using a non-blocking method.
 *
 * A non-blocking (also known as synchronous) function means that the function returns
 * immediately after initiating the transmit function. The application has to get the
 * transmit status to see when the transmit is complete. In other words, after calling non-blocking
 * (asynchronous) send function, the application must get the transmit status to check if transmit
 * is complete.
 * The asynchronous method of transmitting and receiving allows the LPSCI to perform a full duplex
 * operation (simultaneously transmit and receive).
 *
 * @param instance The LPSCI module base address.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @return An error code or kStatus_LPSCI_Success.
 */
lpsci_status_t LPSCI_DRV_SendData(uint32_t instance, const uint8_t * txBuff, uint32_t txSize);

/*!
 * @brief Returns whether the previous LPSCI transmit has finished.
 *
 * When performing an a-sync transmit, call this function to ascertain the state of the
 * current transmission: in progress (or busy) or complete (success). If the
 * transmission is still in progress, the user can obtain the number of words that have been
 * transferred.
 *
 * @param instance The LPSCI module base address.
 * @param bytesRemaining A pointer to a value that is filled in with the number of bytes that
 *                       are remaining in the active transfer.
 * @return Current transmission status.
 * @retval kStatus_LPSCI_Success The transmit has completed successfully.
 * @retval kStatus_LPSCI_TxBusy The transmit is still in progress. @a bytesRemaining is
 *     filled with the number of bytes which are transmitted up to that point.
 */
lpsci_status_t LPSCI_DRV_GetTransmitStatus(uint32_t instance, uint32_t * bytesRemaining);

/*!
 * @brief Terminates an asynchronous LPSCI transmission early.
 *
 * During an a-sync LPSCI transmission, the user can terminate the transmission early
 * if the transmission is still in progress.
 *
 * @param instance The LPSCI module base address.
 * @return Whether the aborting was successful or not. 
 * @retval kStatus_LPSCI_Success The transmit was successful.
 * @retval kStatus_LPSCI_NoTransmitInProgress No transmission is currently in progress.
 */
lpsci_status_t LPSCI_DRV_AbortSendingData(uint32_t instance);

/*!
 * @brief Gets (receives) data from the LPSCI module using a blocking method.
 *
 * A blocking (also known as synchronous) function does not return until
 * the receive is complete. This blocking function sends data through the LPSCI port.
 *
 * @param instance The LPSCI module base address.
 * @param rxBuff A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_LPSCI_Success.
 */
lpsci_status_t LPSCI_DRV_ReceiveDataBlocking(uint32_t instance,
                                           uint8_t * rxBuff,
                                           uint32_t rxSize,
                                           uint32_t timeout);

/*!
 * @brief Gets (receives) data from the LPSCI module using a non-blocking method.
 *
 * A non-blocking (also known as synchronous) function returns
 * immediately after initiating the receive function. The application has to get the
 * receive status to see when the receive is complete.
 * The asynchronous method of transmitting and receiving allows the LPSCI to perform a full duplex
 * operation (simultaneously transmit and receive).
 *
 * @param instance The LPSCI module base address.
 * @param rxBuff  A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @return An error code or kStatus_LPSCI_Success.
 */
lpsci_status_t LPSCI_DRV_ReceiveData(uint32_t instance, uint8_t * rxBuff, uint32_t rxSize);

/*!
 * @brief Returns whether the previous LPSCI receive is complete.
 *
 * When performing an a-sync receive, call this function to ascertain the state of the
 * current receive progress: in progress (or busy) or complete (success). If the
 * receive is still in progress, the user can obtain the number of words that have been
 * received.
 *
 * @param instance The LPSCI module base address.
 * @param bytesRemaining A pointer to a value that is filled in with the number of bytes which
 *                       still need to be received in the active transfer.
 * @return Current receive status.
 * @retval kStatus_LPSCI_Success The receive has completed successfully.
 * @retval kStatus_LPSCI_RxBusy The receive is still in progress. @a bytesRemaining is
 *     filled with the number of bytes which are received up to that point.
 */
lpsci_status_t LPSCI_DRV_GetReceiveStatus(uint32_t instance, uint32_t * bytesRemaining);

/*!
 * @brief Terminates an asynchronous LPSCI receive early.
 *
 * During an a-sync LPSCI receive, the user can terminate the receive early
 * if the receive is still in progress.
 *
 * @param instance The LPSCI module base address.
 * @return Whether the action success or not.
 * @retval kStatus_LPSCI_Success The receive was successful.
 * @retval kStatus_LPSCI_NoTransmitInProgress No receive is currently in progress.
 */
lpsci_status_t LPSCI_DRV_AbortReceivingData(uint32_t instance);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_LPSCI_DRIVER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

