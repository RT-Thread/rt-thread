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

#ifndef __FSL_FLEXIO_UART_DRIVER_H__
#define __FSL_FLEXIO_UART_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_os_abstraction.h"
#include "fsl_flexio_uart_hal.h"
#include "fsl_flexio_driver.h"
#include "fsl_flexio_uart_share.h"
#if FSL_FEATURE_SOC_FLEXIO_COUNT

/*!
 * @addtogroup flexio_uart_driver
 * @{
 */
 
/*! @brief UART receive callback function type */
typedef void (* flexio_uart_rx_callback_t)(void * uartState);

/*!
 * @brief User configuration structure for the FlexIO UART driver.
 *
 * Use an instance of this structure with the FLEXIO_UART_DRV_Init()function. This enables configuration of the
 * settings of the FlexIO UART peripheral with a single function call. Settings include:
 * UART baud rate, the number of bits per data word, FlexIO UART mode, TX hardware resource and Rx hardware
 * resource.
 * @internal gui name="UART configuration" id="uartCfg"
 */
typedef struct flexio_uart_userconfig{
    uint32_t baudRate; /*!< UART baud rate @internal gui name="Baudrate" id="uartBaudrate" */
    flexio_uart_bit_count_per_char_t bitCounter; /*!< number of bits, 5/6/7/8 bits configurable @internal gui name="Bits" id="uartBits" */
    flexio_uart_mode_t uartMode; /*!< FLEXIO UART working modes: Tx Only,Rx Only or both @internal gui name="Mode" id="uartMode" */
    flexio_uart_hwconfig_t txConfig; /*!< FLEXIO UART TX device hardware resource config @internal gui name="Tx configuration" id="txConfig" */
    flexio_uart_hwconfig_t rxConfig; /*!< FLEXIO UART RX device hardware resource config @internal gui name="Rx configuration" id="rxConfig" */ 
}flexio_uart_userconfig_t;
/*!
 * @brief Runtime state of the FlexIO UART driver.
 *
 * This structure holds data that are used by the FlexIO UART peripheral driver to
 * communicate between the transfer function and the interrupt handler. The
 * interrupt handler also uses this information to keep track of its progress.
 * The user passes in the memory for the run-time state structure and the
 * FlexIO UART driver fills out the members.
 */
typedef struct flexio_uart_state{
    flexio_uart_mode_t mode;
    flexio_uart_tx_dev_t txDev;    
    flexio_uart_rx_dev_t rxDev;
    const uint8_t *txBuff;
    uint8_t *rxBuff;
    volatile size_t txSize;
    volatile size_t rxSize;
    volatile bool isTxBusy;
    volatile bool isRxBusy;
    volatile bool isTxBlocking;    /*!< True if transmit is blocking transaction. */
    volatile bool isRxBlocking;    /*!< True if receive is blocking transaction. */
    semaphore_t txIrqSync;         /*!< Used to wait for ISR to complete its TX business. */
    semaphore_t rxIrqSync;         /*!< Used to wait for ISR to complete its RX business. */
    flexio_uart_rx_callback_t rxCallback; /*!< Callback to invoke after receiving byte.*/
    void * rxCallbackParam;        /*!< Receive callback parameter pointer.*/
}flexio_uart_state_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif
/*!
 * @name FLEXIO UART Driver
 * @{
 */

/*!
 * @brief Initializes a FlexIO-simulated UART device .
 *
 * This function initializes the run-time state structure to keep track of the on-going
 * transfers and the module to user-defined settings and default settings. It also
 * configures the underlying FlexIO pin, shifter, and timer resource, and enables the FlexIO
 * simulated UART module interrupt.
 * This example shows how to set up the flexio_uart_state_t and the
 * flexio_uart_userconfig_t parameters and how to call the FLEXIO_UART_DRV_Init function 
 * by passing in these parameters:
   @code
    flexio_uart_userconfig_t uartConfig;
    uartConfig.baudRate = 9600;
    uartConfig.bitCountPerChar = kUart8BitsPerChar;
    uartConfig.uartMode = flexioUART_TxRx;
   @endcode
 *
 * @param instance The FlexIO instance number.
 * @param uartState A pointer to the global FlexIOs UART driver state structure memory. 
 *  The user passes in the memory for the run-time state structure. The FlexIO UART driver
 *  populates the members. This run-time state structure keeps track of the
 *  current transfer in progress.
 * @param uartConfig The user configuration structure of type flexio_uart_userconfig_t. 
 *  The user populates the members of this structure and passes the pointer of this structure
 *  to this function.
 * @return An error code or kStatus_FlexIO_UART_Success.
 */
flexio_uart_status_t FLEXIO_UART_DRV_Init(uint32_t instance, flexio_uart_state_t * uartState,
                               const flexio_uart_userconfig_t * uartConfig);
/*!
 * @brief Shuts down the FlexIO UART.
 *
 * This function disables the FlexIO-simulated UART trigger.
 *
 * @param uartState The run-time structure of FlexIO-simulated UART.
 */
void FLEXIO_UART_DRV_Deinit(flexio_uart_state_t *uartState);
/*!
 * @brief Installs callback function for the FlexIO-simulated UART receive.
 *
 * @note Once a callback is installed, it bypasses the UART driver logic.
 * Therefore, the callback needs to handle the rxBuff and rxSize indexes.
 *
 * @param uartState The run-time structure of FlexIO-simulated UART.
 * @param function The UART receive callback function.
 * @param rxBuff The receive buffer used inside IRQHandler. This buffer must be kept as long as the callback is alive.
 * @param callbackParam The UART receive callback parameter pointer.
 * @param alwaysEnableRxIrq Whether always enable Rx IRQ or not.
 * @return Former UART receive callback function pointer.
 */
flexio_uart_rx_callback_t FLEXIO_UART_DRV_InstallRxCallback(flexio_uart_state_t *uartState,flexio_uart_rx_callback_t function, 
                                              uint8_t * rxBuff,void * callbackParam,bool alwaysEnableRxIrq);
/*!
 * @brief Sends (transmits) data out through the FlexIO-simulated UART module using a 
 * blocking method.
 * @param uartState The run-time structure of FlexIO-simulated UART.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_FlexIO_UART_Success.
 */
flexio_uart_status_t FLEXIO_UART_DRV_SendDataBlocking(flexio_uart_state_t *uartState, 
                                        const uint8_t * txBuff,
                                        uint32_t txSize, 
                                        uint32_t timeout);
/*!
 * @brief Sends (transmits) data through the FlexIO-simulated UART module using a 
 * non-blocking method.
 * @param uartState The run-time structure of FlexIO-simulated UART.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @return An error code or kStatus_FlexIO_UART_Success.
 */
flexio_uart_status_t FLEXIO_UART_DRV_SendData(flexio_uart_state_t *uartState,
                                const uint8_t * txBuff,
                                uint32_t txSize);
/*!
 * @brief Returns whether the previous FlexIO-simulated UART transmit has finished.
 *
 * @param uartState The run-time structure of FlexIO-simulated UART.
 * @param bytesRemaining A pointer to a value that is populated with the number of bytes that
 *                       are remaining in the active transfer.
 * @return An error code or kStatus_FlexIO_UART_Success.
 * @retval kStatus_FlexIO_UART_Success The transmit has completed successfully.
 * @retval kStatus_FlexIO_UART_TxBusy The transmit is still in progress. @a bytesTransmitted is
 *     filled with the number of bytes which are transmitted up to that point.
 */
flexio_uart_status_t FLEXIO_UART_DRV_GetTransmitStatus(flexio_uart_state_t *uartState, uint32_t * bytesRemaining);
/*!
 * @brief Terminates a non-blocking FlexIO-simulated UART transmission early.
 *
 * @param uartState The run-time structure of FlexIO-simulated UART.
 * @return An error code or kStatus_FlexIO_UART_Success.
 * @retval kStatus_FlexIO_UART_Success The transmit was successful.
 * @retval kStatus_FlexIO_UART_NoTransmitInProgress No transmission is currently in progress.
 */
flexio_uart_status_t FLEXIO_UART_DRV_AbortSendingData(flexio_uart_state_t *uartState);
/*!
 * @brief Gets (receives) data from the FlexIO-simulated UART module using a blocking method.
 *
 * @param uartState The run-time structure of FlexIO-simulated UART.
 * @param rxBuff A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_FlexIO_UART_Success.
 */
flexio_uart_status_t FLEXIO_UART_DRV_ReceiveDataBlocking(flexio_uart_state_t *uartState, uint8_t * rxBuff,
                                           uint32_t rxSize, uint32_t timeout);
/*!
 * @brief Gets (receives) data from the FlexIO-simulated UART module using a non-blocking method.
 *
 * @param uartState The run-time structure of FlexIO-simulated UART.
 * @param rxBuff  A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @return An error code or kStatus_FlexIO_UART_Success.
 */
flexio_uart_status_t FLEXIO_UART_DRV_ReceiveData(flexio_uart_state_t *uartState,
                                   uint8_t * rxBuff,
                                   uint32_t rxSize);
/*!
 * @brief Returns whether the previous FlexIO-simulated UART receive is complete.
 *
 * @param uartState The run-time structure of FlexIO-simulated UART.
 * @param bytesRemaining A pointer to a value that is populated with the number of bytes which
 *                       still need to be received in the active transfer.
 * @return An error code or kStatus_FlexIO_UART_Success.
 * @retval kStatus_FlexIO_UART_Success The receive has completed successfully.
 * @retval kStatus_FlexIO_UART_RxBusy The receive is still in progress. @a bytesReceived is
 *     filled with the number of bytes which are received up to that point.
 */
flexio_uart_status_t FLEXIO_UART_DRV_GetReceiveStatus(flexio_uart_state_t *uartState,
                                        uint32_t * bytesRemaining);
/*!
 * @brief Terminates a non-blocking FlexIO-simulated UART receive early.
 *
 * @param uartState The run-time structure of FlexIO-simulated UART.
 * @return An error code or kStatus_UART_Success.
 * @retval kStatus_FlexIO_UART_Success The receive was successful.
 * @retval kStatus_FlexIO_UART_NoTransmitInProgress No receive is currently in progress.
 */
flexio_uart_status_t FLEXIO_UART_DRV_AbortReceivingData(flexio_uart_state_t *uartState);
/*!
 * @brief Interrupt handler for FlexIO-simulated UART TX.
 * @param param The run-time structure of FlexIO-simulated UART.
 */
void FLEXIO_UART_DRV_TX_IRQHandler(void *param);
/*!
 * @brief Interrupt handler for FlexIO-simulated UART RX.
 * @param param The run-time structure of FlexIO-simulated UART.
 */
void FLEXIO_UART_DRV_RX_IRQHandler(void *param);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif

#endif /* __FSL_FLEXIO_UART_DRIVER_H__*/
