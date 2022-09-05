/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_UART_H__
#define __HAL_UART_H__

#include "hal_common.h"

/*!
 * @addtogroup UART
 * @{
 */

/*!
 * @brief UART driver version number.
 */
#define UART_DRIVER_VERSION 0u /*!< uart_0. */

/*!
 * @addtogroup UART_STATUS
 * @{
 */
#define UART_STATUS_TX_DONE  UART_CSR_TXC_MASK    /*!< Status flag when UART transmiter shifter is empty after the transfer is done. */
#define UART_STATUS_RX_DONE  UART_CSR_RXAVL_MASK  /*!< Status flag when UART receiving buffer is with available data. */
#define UART_STATUS_TX_FULL  UART_CSR_TXFULL_MASK /*!< Status flag when UART transmiter buffer is full. */
#define UART_STATUS_TX_EMPTY UART_CSR_TXEPT_MASK  /*!< Status flag when UART transmiter buffer is empty. */
/*!
 * @}
 */

/*!
 * @addtogroup UART_INT
 * @{
 */
#define UART_INT_TX_EMPTY  UART_ISR_TXINTF_MASK   /*!< Interrupt enable when UART transmiter buffer is empty. */
#define UART_INT_RX_DONE   UART_ISR_RXINTF_MASK   /*!< Interrupt enable when UART receiving buffer is with available data. */
#define UART_INT_TX_DONE   UART_ISR_TXCINTF_MASK  /*!< Interrupt enable when UART transmiter shifter is empty. */
/*!
 * @}
 */

/*!
 * @brief UART word length type.
 */
typedef enum
{
    UART_WordLength_5b = 0u, /*!< Word length 5 bits. */
    UART_WordLength_6b = 1u, /*!< Word length 6 bits. */
    UART_WordLength_7b = 2u, /*!< Word length 7 bits. */
    UART_WordLength_8b = 3u, /*!< Word length 8 bits. */
} UART_WordLength_Type;

/*!
 * @brief UART stop bits type.
 */
typedef enum
{
    UART_StopBits_1   = 0u, /*!< 1 stop bits. */
    UART_StopBits_2   = 1u, /*!< 2 stop bits. */
    UART_StopBits_0_5 = 2u, /*!< 0.5 stop bits. */
    UART_StopBits_1_5 = 3u, /*!< 1.5 stop bits. */
} UART_StopBits_Type;

/*!
 * @brief UART parity type.
 */
typedef enum
{
    UART_Parity_None = 0u, /*!< No parity. */
    UART_Parity_Even = 1u, /*!< Even parity. */
    UART_Parity_Odd  = 2u, /*!< Odd parity. */
} UART_Parity_Type;

/*!
 * @brief UART hardware flow control type.
 */
typedef enum
{
    UART_HwFlowControl_None    = 0u, /*!< No hardware flow control. */
    UART_HwFlowControl_RTS_CTS = 1u, /*!< Enable RTS and CTS hardware flow control.*/
} UART_HwFlowControl_Type;

/*!
 * @brief UART xfer mode type.
 */
typedef enum
{
    UART_XferMode_None   = 0u, /*!< Disable both Tx and Rx. */
    UART_XferMode_RxOnly = 1u, /*!< Enable Rx only. */
    UART_XferMode_TxOnly = 2u, /*!< Enable Tx only. */
    UART_XferMode_RxTx   = 3u, /*!< Enable both Rx and Tx. */
} UART_XferMode_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref UART_Init() to initialize the UART module.
 */
typedef struct
{
    uint32_t                ClockFreqHz;    /*!< Bus Clock Freq. */
    uint32_t                BaudRate;       /*!< Specify the UART communication baud rate. */
    UART_WordLength_Type    WordLength;     /*!< Specify the number of data bits transmitted or received in a frame. */
    UART_StopBits_Type      StopBits;       /*!< Specify the number of stop bits transmitted. */
    UART_Parity_Type        Parity;         /*!< Specify the parity mode. */
    UART_XferMode_Type      XferMode;       /*!< Specify whether the Receive or Transmit mode is enabled or not. */
    UART_HwFlowControl_Type HwFlowControl;  /*!< Specify whether the hardware flow control mode is enabled or not. */
} UART_Init_Type;

/*!
 * @brief Initialize the UART module.
 *
 * @param UARTx UART instance.
 * @param init  Pointer to the initialization structure. See to @ref UART_Init_Type.
 * @return None.
 */
void UART_Init(UART_Type * UARTx, UART_Init_Type * init);

/*!
 * @brief Enable the UART module.
 *
 * The UART module should be enabled before sending or receiving data.
 *
 * @param UARTx UART instance.
 * @param enable 'true' to enable the module, 'false' to disable the module.
 * @return None.
 */
void UART_Enable(UART_Type * UARTx, bool enable);

/*!
 * @brief Get the current status flags of the UART module.
 *
 * @param UARTx UART instance.
 * @return Status flags. See to @ref UART_STATUS.
 */
uint32_t UART_GetStatus(UART_Type * UARTx);

/*!
 * @brief Enable interrupts of the UART module.
 *
 * @param UARTx UART instance.
 * @param interrupts Interrupt code masks. See to @ref UART_INT.
 * @param enable 'true' to enable the indicated interrupts, 'false' to disable the indicated interrupts.
 * @return None.
 */
void UART_EnableInterrupts(UART_Type * UARTx, uint32_t interrupts, bool enable);

/*!
 * @brief Get the interrupts status flags of the UART module.
 *
 * @param UARTx UART instance.
 * @return Interrupt status flags. See to @ref UART_INT.
 */
uint32_t UART_GetInterruptStatus(UART_Type * UARTx);

/*!
 * @brief Clear the interrupts status flags of the UART module.
 *
 * @param UARTx UART instance.
 * @param interrupts The mask codes of the indicated interrupt flags to be cleared.
 * @return Interrupt status flags. See to @ref UART_INT.
 */
void UART_ClearInterruptStatus(UART_Type * UARTx, uint32_t interrupts);

/*!
 * @brief Put the data into transmiter buffer of the UART module.
 *
 * @param UARTx UART instance.
 * @param value Data value to be send through the transmiter.
 * @return None.
 */
void UART_PutData(UART_Type * UARTx, uint8_t value);

/*!
 * @brief Get the data from receiver buffer of the UART module.
 *
 * @param UARTx UART instance.
 * @return The data value received from the receiver.
 * @return None.
 */
uint8_t UART_GetData(UART_Type * UARTx);

/*!
 * @brief Enable the DMA trigger from the UART module.
 *
 * The DMA trigger events are the same as the intertupts.
 *
 * @param UARTx UART instance.
 * @param enable 'true' to enable the DMA trigger, 'false' to disable the DMA trigger.
 * @return None.
 */
void UART_EnableDMA(UART_Type * UARTx, bool enable);

/*!
 * @brief Read the current enabled interrupts the UART module.
 *
 * @param UARTx UART instance.
 * @return The mask codes enabled interrupts. See to @ref UART_INT
 */
uint32_t UART_GetEnabledInterrupts(UART_Type * UARTx);

/*!
 * @brief Get the hardware Rx data buffer's address the UART module.
 *
 * The return value of the address is most used with DMA module.
 *
 * @param UARTx UART instance.
 * @return The value of the address for UART module's hardware Rx data buffer.
 */
uint32_t UART_GetRxDataRegAddr(UART_Type * UARTx);

/*!
 * @brief Get the hardware Tx data buffer's address the UART module.
 *
 * The return value of the address is most used with DMA module.
 *
 * @param UARTx UART instance.
 * @return The value of the address for UART module's hardware Tx data buffer.
 */
uint32_t UART_GetTxDataRegAddr(UART_Type * UARTx);

/*!
 *@}
 */

#endif /* __HAL_UART_H__ */
