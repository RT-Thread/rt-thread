 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     drv/uart.h
 * @brief    Header File for UART Driver
 * @version  V1.0
 * @date     08. Apr 2020
 * @model    uart
 ******************************************************************************/

#ifndef _DRV_UART_H_
#define _DRV_UART_H_

#include <drv/common.h>
#include <drv/dma.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----- UART Control Codes: Mode Parameters: Data Bits -----*/
typedef enum {
    UART_DATA_BITS_5               = 0,    ///< 5 Data bits
    UART_DATA_BITS_6,                      ///< 6 Data bit
    UART_DATA_BITS_7,                      ///< 7 Data bits
    UART_DATA_BITS_8,                      ///< 8 Data bits (default)
    UART_DATA_BITS_9                       ///< 9 Data bits
} csi_uart_data_bits_t;

/*----- UART Control Codes: Mode Parameters: Parity -----*/
typedef enum {
    UART_PARITY_NONE               = 0,    ///< No Parity (default)
    UART_PARITY_EVEN,                      ///< Even Parity
    UART_PARITY_ODD,                       ///< Odd Parity
} csi_uart_parity_t;

/*----- UART Control Codes: Mode Parameters: Stop Bits -----*/
typedef enum {
    UART_STOP_BITS_1               = 0,    ///< 1 Stop bit (default)
    UART_STOP_BITS_2,                      ///< 2 Stop bits
    UART_STOP_BITS_1_5,                    ///< 1.5 Stop bits
} csi_uart_stop_bits_t;

/*----- UART Control Codes: Mode Parameters: Flow Control -----*/
typedef enum {
    UART_FLOWCTRL_NONE             = 0,    ///< none flowctrl
    UART_FLOWCTRL_RTS,                     ///< RTS
    UART_FLOWCTRL_CTS,                     ///< CTS
    UART_FLOWCTRL_RTS_CTS                  ///< RTS & CTS
} csi_uart_flowctrl_t;

/****** UART Event *****/
typedef enum {
    UART_EVENT_SEND_COMPLETE        = 0,        ///< Send data completed.
    UART_EVENT_RECEIVE_COMPLETE,                ///< Receive data completed.
    UART_EVENT_RECEIVE_FIFO_READABLE,           ///< Data in uart fifo, call csi_uart_receive() get the data.
    UART_ENENT_BREAK_INTR,                      ///< the serial input,sin, is held in a logic '0' state for longer than the sum of start time+data bits+parity+stop bits.
    UART_EVENT_ERROR_OVERFLOW,                  ///< A new data character was received before the previous data was read.
    UART_EVENT_ERROR_PARITY,                    ///< Occur parity error in the receiver.
    UART_EVENT_ERROR_FRAMING                    ///< the receiver does not detect a valid STOP bit in the received data.
} csi_uart_event_t;

///< definition for uart.
typedef struct csi_uart csi_uart_t;

struct csi_uart {
    csi_dev_t             dev;
    void                  (*callback)(csi_uart_t *uart, csi_uart_event_t event, void *arg);
    void                  *arg;
    uint8_t               *tx_data;
    uint32_t              tx_size;
    uint8_t               *rx_data;
    uint32_t              rx_size;
    csi_dma_ch_t          *tx_dma;
    csi_dma_ch_t          *rx_dma;
    csi_error_t           (*send)(csi_uart_t *uart, const void *data, uint32_t size);
    csi_error_t           (*receive)(csi_uart_t *uart, void *data, uint32_t size);
    csi_state_t           state;
    void                  *priv;
};

/**
  \brief       Initializes the resources needed for the UART interface.
  \param[in]   uart      Operate handle.
  \param[in]   idx       The device idx.
  \return      Error code.
*/
csi_error_t csi_uart_init(csi_uart_t *uart, uint32_t idx);

/**
  \brief       De-initialize UART Interface. stops operation and releases the software resources used by the interface.
  \param[in]   uart  Operate handle.
  \return      Error code.
*/
void        csi_uart_uninit(csi_uart_t *uart);

/**
  \brief       Attach the callback handler to UART.
  \param[in]   uart       Operate handle.
  \param[in]   callback   Callback function.
  \param[in]   arg        User can define it by himself as callback's param.
  \return      Error code.
*/
csi_error_t csi_uart_attach_callback(csi_uart_t *uart, void *callback, void *arg);

/**
  \brief       Detach the callback handler.
  \param[in]   uart  Operate handle.
*/
void        csi_uart_detach_callback(csi_uart_t *uart);

/**
  \brief       Config the baudrate.
  \param[in]   uart  UART handle to operate.
  \param[in]   baud  UART baudrate.
  \return      Error code.
*/
csi_error_t csi_uart_baud(csi_uart_t *uart, uint32_t baud);

/**
  \brief       Config the uart format.
  \param[in]   uart      UART handle to operate.
  \param[in]   data_bit  UART data bits.
  \param[in]   parity    UART data parity.
  \param[in]   stop_bit  UART stop bits.
  \return      Error code.
*/
csi_error_t csi_uart_format(csi_uart_t *uart,  csi_uart_data_bits_t data_bits,
                            csi_uart_parity_t parity, csi_uart_stop_bits_t stop_bits);

/**
  \brief       Config the uart flow control.
  \param[in]   uart      UART handle to operate.
  \param[in]   flowctrl  UART flow control.
  \return      Error code.
*/
csi_error_t csi_uart_flowctrl(csi_uart_t *uart,  csi_uart_flowctrl_t flowctrl);

/**
  \brief       Start send data to UART transmitter, this function is blocking.
  \param[in]   uart     UART handle to operate.
  \param[in]   data     Pointer to buffer with data to send to UART transmitter.
  \param[in]   size     Number of data to send (byte).
  \param[in]   timeout  The timeout between bytes(ms).
  \return      the num of data which is sent successfully or CSI_ERROR.
*/
int32_t csi_uart_send(csi_uart_t *uart, const void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Start send data to UART transmitter, this function is non-blocking.
  \param[in]   uart     UART handle to operate.
  \param[in]   data     Pointer to buffer with data to send to UART transmitter.
  \param[in]   size     Number of data to send (byte).
  \return      Error code.
*/
csi_error_t csi_uart_send_async(csi_uart_t *uart, const void *data, uint32_t size);

/**
  \brief       Query data from UART receiver FIFO, this function is blocking.
  \param[in]   uart     UART handle to operate.
  \param[out]  data     Pointer to buffer for data to receive from UART receiver.
  \param[in]   size     Number of data to receive.
  \param[in]   timeout  The timeout between bytes(ms).
  \return      the num of data witch is received successfully or CSI_ERROR.
*/
int32_t csi_uart_receive(csi_uart_t *uart, void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Start receiving data from UART receiver, this function is non-blocking.
  \param[in]   uart  UART handle to operate.
  \param[out]  data  Pointer to buffer for data to receive from UART receiver.
  \param[in]   size  Number of data to receive (byte).
  \return      Error code.
*/
csi_error_t csi_uart_receive_async(csi_uart_t *uart, void *data, uint32_t size);

/**
  \brief       Get character in query mode.
  \param[in]   uart  UART handle to operate.
  \return      the character to get.
*/
uint8_t  csi_uart_getc(csi_uart_t *uart);

/**
  \brief       Send character in query mode.
  \param[in]   uart UART handle to operate.
  \param[in]   ch   The character to be send.
*/
void csi_uart_putc(csi_uart_t *uart, uint8_t ch);

/**
  \brief       Link DMA channel to uart device.
  \param[in]   uart     UART handle to operate.
  \param[in]   tx_dma   The DMA channel handle for send, when it is NULL means to unlink the channel.
  \param[in]   rx_dma   The DMA channel handle for receive, when it is NULL means to unlink the channel.
  \return      Error code.
*/
csi_error_t csi_uart_link_dma(csi_uart_t *uart, csi_dma_ch_t *tx_dma, csi_dma_ch_t *rx_dma);

/**
  \brief       Get the state of uart device.
  \param[in]   uart   UART handle to operate.
  \param[out]  state  The state of uart device.
  \return      Error code.
*/
csi_error_t csi_uart_get_state(csi_uart_t *uart, csi_state_t *state);

/**
  \brief       Enable uart power manage.
  \param[in]   uart   UART handle to operate.
  \return      Error code.
*/
csi_error_t csi_uart_enable_pm(csi_uart_t *uart);

/**
  \brief       Disable uart power manage.
  \param[in]   uart   UART handle to operate.
*/
void csi_uart_disable_pm(csi_uart_t *uart);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_UART_H_ */
