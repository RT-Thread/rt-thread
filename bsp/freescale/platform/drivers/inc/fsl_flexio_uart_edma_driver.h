/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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

#ifndef __FSL_FLEXIO_UART_EDMA_DRIVER_H__
#define __FSL_FLEXIO_UART_EDMA_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_os_abstraction.h"
#include "fsl_flexio_uart_hal.h"
#include "fsl_edma_driver.h"
#include "fsl_flexio_driver.h"
#include "fsl_flexio_uart_share.h"

#if FSL_FEATURE_SOC_EDMA_COUNT

/*!
 * @addtogroup flexio_uart_driver
 * @{
 */
 
/*!
 * @brief User configuration structure for the FlexIO UART driver.
 *
 * Use an instance of this structure with the FLEXIO_UART_DRV_Init()function to enable configuration of the
 * settings of the FlexIO UART peripheral with a single function call. Settings include:
 * UART baud rate, the number of bits per data word, FlexIO UART mode, transmit hardware resource and receive hardware
 * resource.
 */
typedef struct flexio_uartedma_userconfig{
    uint32_t baudRate;
    flexio_uart_bit_count_per_char_t bitCounter;
    flexio_uart_mode_t uartMode;
    flexio_uart_hwconfig_t txConfig;
    flexio_uart_hwconfig_t rxConfig; 
}flexio_uartedma_userconfig_t;
/*!
 * @brief Runtime state of the FlexIO UART driver.
 *
 * This structure holds data that is used by the FlexIO UART peripheral driver to
 * communicate between the transfer function and the interrupt handler. The
 * interrupt handler also uses this information to keep track of its progress.
 * The user passes in the memory for the run-time state structure and the
 * FlexIO UART driver fills out the members.
 */
typedef struct flexio_uart_edmastate{
    flexio_uart_mode_t mode;
    flexio_uart_tx_dev_t txDev;    
    flexio_uart_rx_dev_t rxDev;
    volatile bool isTxBusy;
    volatile bool isRxBusy;
    volatile bool isTxBlocking;    /*!< True if transmit is blocking transaction. */
    volatile bool isRxBlocking;    /*!< True if receive is blocking transaction. */
    semaphore_t txIrqSync;         /*!< Used to wait for ISR to complete the transmit. */
    semaphore_t rxIrqSync;         /*!< Used to wait for ISR to complete the receive. */
    edma_chn_state_t edmaUartTx; /*!< Structure definition for the eDMA channel */
    edma_chn_state_t edmaUartRx; /*!< Structure definition for the eDMA channel */
}flexio_uart_edmastate_t;
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name FlexIO UART eDMA Driver
 * @{
 */

/*!
 * @brief Initializes a FlexIO-simulated UART device to work with eDMA.
 *
 * This function initializes the run-time state structure to keep track of the on-going
 * transfers, initializes the module to user-defined settings and default settings, 
 * configures underlying FlexIO pin, shifter, and timer resource, and enables the
 * FlexIO-simulated UART module eDMA interrupt.
 * This example shows how to set up the flexio_uartedma_state_t and the
 * flexio_uartedma_userconfig_t parameters and how to call the FLEXIO_UART_DRV_EdmaInit function 
 * by passing in these parameters:
   @code
    flexio_uartedma_userconfig_t uartEdmaConfig;
    uartEdmaConfig.baudRate = 9600;
    uartEdmaConfig.bitCountPerChar = kUart8BitsPerChar;
    uartEdmaConfig.uartMode = flexioUART_TxRx;
   @endcode
 *
 * @param instance The FlexIO instance number.
 * @param uartEdmaState A pointer to the global FlexIO UART driver state structure memory. 
 *  The user passes in the memory for the run-time state structure. The FlexIO UART driver
 *  populates the members. This run-time state structure keeps track of the
 *  current transfer in progress.
 * @param uartEdmaConfig The user configuration structure of type flexio_uartedma_userconfig_t. 
 *  The user populates the members of this structure and passes the pointer of this structure
 *  to this function.
 * @return An error code or kStatus_FlexIO_UART_Success.
 */
flexio_uart_status_t FLEXIO_UART_DRV_EdmaInit(uint32_t instance, flexio_uart_edmastate_t * uartEdmaState,
                               const flexio_uartedma_userconfig_t * uartEdmaConfig);
/*!
 * @brief Shuts down the FlexIO UART.
 *
 * This function disables the FlexIO-simulated UART eDMA trigger.
 *
 * @param uartEdmaState The run-time structure of FlexIO-simulated UART.
 */
void FLEXIO_UART_DRV_EdmaDeinit(flexio_uart_edmastate_t * uartEdmaState);

/*!
 * @brief Sends (transmits) data through the FlexIO-simulated UART eDMA module using a 
 * blocking method.
 * @param uartEdmaState The run-time structure of FlexIO-simulated UART.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_FlexIO_UART_Success.
 */
flexio_uart_status_t FLEXIO_UART_DRV_EdmaSendDataBlocking(flexio_uart_edmastate_t * uartEdmaState,
                                           const uint8_t * txBuff,
                                           uint32_t txSize,
                                           uint32_t timeout);

/*!
 * @brief Sends (transmits) data through the FlexIO-simulated UART eDMA module using a 
 * non-blocking method.
 * @param uartEdmaState The run-time structure of FlexIO-simulated UART.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @return An error code or kStatus_FlexIO_UART_Success.
 */
flexio_uart_status_t FLEXIO_UART_DRV_EdmaSendData(flexio_uart_edmastate_t * uartEdmaState,
                                   const uint8_t * txBuff,
                                   uint32_t txSize);
/*!
 * @brief Returns whether the previous FlexIO-simulated UART eDMA transmit has finished.
 *
 * @param uartEdmaState The run-time structure of FlexIO-simulated UART.
 * @param bytesRemaining A pointer to a value that is populated with the number of bytes that
 *                       are remaining in the active transfer.
 * @return An error code or kStatus_FlexIO_UART_Success.
 * @retval kStatus_FlexIO_UART_Success The transmit has completed successfully.
 * @retval kStatus_FlexIO_UART_TxBusy The transmit is still in progress. @a bytesTransmitted is
 *     filled with the number of bytes which are transmitted up to that point.
 */
flexio_uart_status_t FLEXIO_UART_DRV_EdmaGetTransmitStatus(flexio_uart_edmastate_t * uartEdmaState, 
                                   uint32_t * bytesRemaining);
/*!
 * @brief Terminates a non-blocking FlexIO-simulated UART eDMA transmission early.
 *
 * @param uartEdmaState The run-time structure of FlexIO-simulated UART.
 * @return An error code or kStatus_FlexIO_UART_Success.
 * @retval kStatus_FlexIO_UART_Success The transmit was successful.
 * @retval kStatus_FlexIO_UART_NoTransmitInProgress No transmission is currently in progress.
 */
flexio_uart_status_t FLEXIO_UART_DRV_EdmaAbortSendingData(flexio_uart_edmastate_t * uartEdmaState);

/*!
 * @brief Gets (receives) data from the FlexIO-simulated UART eDMA module using a blocking method.
 *
 * @param uartEdmaState The run-time structure of FlexIO-simulated UART.
 * @param rxBuff A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_FlexIO_UART_Success.
 */
flexio_uart_status_t FLEXIO_UART_DRV_EdmaReceiveDataBlocking(flexio_uart_edmastate_t * uartEdmaState,
                                              uint8_t * rxBuff,
                                              uint32_t rxSize,
                                              uint32_t timeout);
/*!
 * @brief Gets (receives) data from the FlexIO-simulated UART eDMA module using a non-blocking method.
 *
 * @param uartEdmaState The run-time structure of FlexIO-simulated UART.
 * @param rxBuff  A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @return An error code or kStatus_FlexIO_UART_Success.
 */
flexio_uart_status_t FLEXIO_UART_DRV_EdmaReceiveData(flexio_uart_edmastate_t * uartEdmaState,
                                      uint8_t * rxBuff,
                                      uint32_t rxSize);

/*!
 * @brief Returns whether the previous FlexIO-simulated UART eDMA receive is complete.
 *
 * @param uartEdmaState The run-time structure of FlexIO-simulated UART.
 * @param bytesRemaining A pointer to a value that is populated with the number of bytes which
 *                       still need to be received in the active transfer.
 * @return An error code or kStatus_FlexIO_UART_Success.
 * @retval kStatus_FlexIO_UART_Success The receive has completed successfully.
 * @retval kStatus_FlexIO_UART_RxBusy The receive is still in progress. @a bytesReceived is
 *     filled with the number of bytes which are received up to that point.
 */
flexio_uart_status_t FLEXIO_UART_DRV_EdmaGetReceiveStatus(flexio_uart_edmastate_t * uartEdmaState, 
                                  uint32_t * bytesRemaining);
/*!
 * @brief Terminates a non-blocking FlexIO-simulated UART eDMA receive early.
 *
 * @param uartEdmaState The run-time structure of FlexIO-simulated UART.
 * @return An error code or kStatus_UART_Success.
 * @retval kStatus_FlexIO_UART_Success The receive was successful.
 * @retval kStatus_FlexIO_UART_NoTransmitInProgress No receive is currently in progress.
 */
flexio_uart_status_t FLEXIO_UART_DRV_EdmaAbortReceivingData(flexio_uart_edmastate_t * uartEdmaState);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif

#endif /* __FSL_FLEXIO_UART_DRIVER_H__*/
