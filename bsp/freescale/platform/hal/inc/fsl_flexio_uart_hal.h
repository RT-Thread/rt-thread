/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
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

#ifndef __FSL_FLEXIO_UART_HAL_H__
#define __FSL_FLEXIO_UART_HAL_H__

#include "fsl_flexio_hal.h"
#if FSL_FEATURE_SOC_FLEXIO_COUNT

/*!
 * @addtogroup flexio_uart_hal
 * @{
 */

/*!
 * @brief Define structure of configuring the FlexIO UART transmit device. 
 */
typedef struct
{
    FLEXIO_Type * flexioBase; /*!< FlexIO module base address. */
    uint32_t txPinIdx;        /*!< Pin index for UART transmit in FlexIO. */

    uint32_t shifterIdx;      /*!< Shifter index used for UART transmit in FlexIO. */
    uint32_t timerIdx;        /*!< Timer index used for UART transmit in FlexIO. */
} flexio_uart_tx_dev_t;

 /*!
 * @brief Define structure of configuring the FlexIO UART receive device. 
 */
typedef struct
{
    FLEXIO_Type * flexioBase; /*!< FlexIO module base address. */
    uint32_t rxPinIdx;       /*!< Pin index for UART receive in FlexIO. */

    uint32_t shifterIdx;     /*!< Shifter index used for UART receive in FlexIO. */
    uint32_t timerIdx;       /*!< Timer index used for UART receive in FlexIO. */
} flexio_uart_rx_dev_t;

/*!
 * @brief Define structure of configuring the FlexIO UART bus. 
 */
typedef struct
{
    uint32_t flexioBusClk; /*!< FlexIO bus clock frequency in Hertz. */
    uint32_t baudrate;     /*!< UART transfer bandrate in bps. */
    uint32_t bitCount;     /*!< UART transfer data length in bit. */
} flexio_uart_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/******************************************************************************
 * UART transmit.
 ******************************************************************************/
/*!
 * @brief Configures the FlexIO as a UART transmit device.
 *
 * @param devPtr Pointer to the device.
 * @param configPtr Pointer to configuration structure.
 * @return Execution status.
 */
flexio_status_t FLEXIO_UART_Tx_HAL_Configure(
    flexio_uart_tx_dev_t *devPtr, const flexio_uart_config_t *configPtr);

/*!
 * @brief Gets the flag which indicates whether the transmit buffer is empty.
 *
 * @param devPtr Pointer to the device.
 * @return The assertion of the event.
 */
bool FLEXIO_UART_Tx_HAL_GetTxBufferEmptyFlag(flexio_uart_tx_dev_t *devPtr);

/*!
 * @brief Clears the transmit buffer empty flag manually.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_UART_Tx_HAL_ClearTxBufferEmptyFlag(flexio_uart_tx_dev_t *devPtr);

/*!
 * @brief Switches on/off the interrupt for the buffer empty event.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_UART_Tx_HAL_SetTxBufferEmptyIntCmd(flexio_uart_tx_dev_t *devPtr, bool enable);

/*!
 * @brief Gets the current setting for the transmit buffer empty event.
 *
 * @param devPtr Pointer to the device.
 * @return Setting for the interrupt event.
 */
bool FLEXIO_UART_Tx_HAL_GetTxBufferEmptyIntCmd(flexio_uart_tx_dev_t *devPtr);

/*!
 * @brief Gets the transmit error flag.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of the event.
 */
bool FLEXIO_UART_Tx_HAL_GetTxErrFlag(flexio_uart_tx_dev_t *devPtr);

/*!
 * @brief Clears the transmit error flag manually.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_UART_Tx_HAL_ClearTxErrFlag(flexio_uart_tx_dev_t *devPtr);

/*!
 * @brief Switches on/off the interrupt for the transmit error event.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_UART_Tx_HAL_SetTxErrIntCmd(flexio_uart_tx_dev_t *devPtr, bool enable);

/*!
 * @brief Puts the data into the transmit buffer.
 *
 * @param devPtr Pointer to the device.
 * @param dat Sending data.
 */
void FLEXIO_UART_Tx_HAL_PutData(flexio_uart_tx_dev_t *devPtr, uint32_t dat);

/*!
 * @brief Puts the data into the transmit buffer when empty.
 *
 * @param devPtr Pointer to the device.
 * @param dat Sending data.
 */
void FLEXIO_UART_Tx_HAL_PutDataPolling(flexio_uart_tx_dev_t *devPtr, uint32_t dat);

/*!
 * @brief Sends an array of data by FlexIO UART transmit device.
 *
 * @param devPtr Pointer to the device.
 * @param txBufPtr Pointer to the sending buffer.
 * @param txLen Length of sending buffer.
 */
void FLEXIO_UART_Tx_HAL_SendDataPolling(flexio_uart_tx_dev_t *devPtr, uint32_t *txBufPtr, uint32_t txLen);

/*!
 * @brief Switches on/off the DMA on the FlexIO UART transmit device.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_UART_Tx_HAL_SetTxDmaCmd(flexio_uart_tx_dev_t *devPtr, bool enable);

/*!
 * @brief Gets the transmit buffer's address for the DMA use.
 *
 * @param devPtr Pointer to the device.
 * @return tx buffer's address.
 */
uint32_t FLEXIO_UART_Tx_HAL_GetTxBufferAddr(flexio_uart_tx_dev_t *devPtr);

/******************************************************************************
 * UART receive.
******************************************************************************/
/*!
 * @brief Configures the FlexIO as a UART receive device.
 *
 * @param devPtr Pointer to the device.
 * @param configPtr Pointer to configuration structure.
 * @return Execution status.
 */
flexio_status_t FLEXIO_UART_Rx_HAL_Configure(
    flexio_uart_rx_dev_t *devPtr, const flexio_uart_config_t *configPtr);

/*!
 * @brief Gets the flag which indicates whether the receive buffer is full.
 *
 * @param devPtr Pointer to the device.
 * @return The assertion of the event.
 */
bool FLEXIO_UART_Rx_HAL_GetRxBufferFullFlag(flexio_uart_rx_dev_t *devPtr);

/*!
 * @brief Clears the flag manually that indicates that the receive buffer is full.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_UART_Rx_HAL_ClearRxBufferFullFlag(flexio_uart_rx_dev_t *devPtr);

/*!
 * @brief Switches on/off the interrupt for the receive buffer full event.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_UART_Rx_HAL_SetRxBufferFullIntCmd(flexio_uart_rx_dev_t *devPtr, bool enable);

/*!
 * @brief Gets the current setting that indicates whether the interrupt is enabled.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of the event.
 */
bool FLEXIO_UART_Rx_HAL_GetRxBufferFullIntCmd(flexio_uart_rx_dev_t *devPtr);

/*!
 * @brief Gets the flag of the receive error event.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of the event.
 */
bool FLEXIO_UART_Rx_HAL_GetRxErrFlag(flexio_uart_rx_dev_t *devPtr);

/*!
 * @brief Clears the flag of the receive error event manually.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_UART_Rx_HAL_ClearRxErrFlag(flexio_uart_rx_dev_t *devPtr);

/*!
 * @brief Switches on/off the interrupt for the receive error event.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_UART_Rx_HAL_SetRxErrIntCmd(flexio_uart_rx_dev_t *devPtr, bool enable);

/*!
 * @brief Gets the data from the receive buffer.
 *
 * @param devPtr Pointer to the device.
 * @return Data from the receive buffer.
 */
uint32_t FLEXIO_UART_Rx_HAL_GetData(flexio_uart_rx_dev_t *devPtr);

/*!
 * @brief Gets the data from the receive buffer when full.
 *
 * @param devPtr Pointer to the device.
 * @return Data from the receive buffer.
 */
uint32_t FLEXIO_UART_Rx_HAL_GetDataPolling(flexio_uart_rx_dev_t *devPtr);

/*!
 * @brief Receives an array of data through the receive buffer.
 *
 * @param devPtr Pointer to the device.
 * @param rxBufPtr Pointer to the receive buffer.
 * @param rxLen Length of the receive buffer.
 */
void FLEXIO_UART_Rx_HAL_ReceiveDataPolling(flexio_uart_rx_dev_t *devPtr, uint32_t *rxBufPtr, uint32_t rxLen);

/*!
 * @brief Switches on/off the receive DMA support.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_UART_Rx_HAL_SetRxDmaCmd(flexio_uart_rx_dev_t *devPtr, bool enable);

/*!
 * @brief Gets the receive buffer's address for DMA use.
 *
 * @param devPtr Pointer to the device.
 * @return rx buffer's address.
 */
uint32_t FLEXIO_UART_Rx_HAL_GetRxBufferAddr(flexio_uart_rx_dev_t *devPtr);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
#endif /* __FSL_FLEXIO_UART_HAL_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

