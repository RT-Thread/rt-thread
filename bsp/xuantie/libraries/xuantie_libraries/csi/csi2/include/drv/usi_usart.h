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
 * @file     drv/usi_usart.h
 * @brief    Header File for USART Driver
 * @version  V1.0
 * @date     02. June 2020
 * @model    usi_usart
 ******************************************************************************/

#ifndef _DRV_USI_USART_H_
#define _DRV_USI_USART_H_

#include <drv/common.h>
#include <drv/uart.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief       Initialize UART Interface. 1. Initializes the resources needed for the UART interface 2.registers event callback function
  \param[in]   uart      Operate handle.
  \param[in]   idx       The device idx
  \param[in]   cb_event  Event call back function \ref uart_event_cb_t
  \param[in]   arg       User can define it by himself
  \return      error code
*/
csi_error_t csi_usi_uart_init(csi_uart_t *uart, uint32_t idx);

/**
  \brief       De-initialize UART Interface. stops operation and releases the software resources used by the interface
  \param[in]   uart  Operate handle.
  \return      Error code
*/
void csi_usi_uart_uninit(csi_uart_t *uart);

/**
  \brief       Attach the callback handler to UART
  \param[in]   uart  Operate handle.
  \param[in]   cb    Callback function
  \param[in]   arg   User can define it by himself as callback's param
  \return      Error code
*/
csi_error_t csi_usi_uart_attach_callback(csi_uart_t *uart, void * cb, void *arg);

/**
  \brief       Detach the callback handler
  \param[in]   uart  Operate handle.
*/
void  csi_usi_uart_detach_callback(csi_uart_t *uart);

/**
  \brief       Config the baudrate.
  \param[in]   uart  UART handle to operate.
  \param[in]   baud  UART baudrate
  \return      Error code
*/
csi_error_t csi_usi_uart_baud(csi_uart_t *uart, uint32_t baud);

/**
  \brief       Config the uart format.
  \param[in]   uart      UART handle to operate.
  \param[in]   data_bit  UART data bits
  \param[in]   parity    UART data parity
  \param[in]   stop_bit  UART stop bits
  \return      Error code
*/
csi_error_t csi_usi_uart_format(csi_uart_t *uart,  csi_uart_data_bits_t data_bits,
                            csi_uart_parity_t parity, csi_uart_stop_bits_t stop_bits);

/**
  \brief       Config the uart flow control.
  \param[in]   uart      UART handle to operate.
  \param[in]   flowctrl  UART flow control
  \return      Error code
*/
csi_error_t csi_usi_uart_flowctrl(csi_uart_t *uart,  csi_uart_flowctrl_t flowctrl);

/**
  \brief       Start sending data to UART transmitter.
  \param[in]   uart     UART handle to operate.
  \param[in]   data     Pointer to buffer with data to send to UART transmitter. data_type is : uint8_t for 5..8 data bits, uint16_t for 9 data bits
  \param[in]   num      Number of data items to send (byte)
  \param[in]   Timeout  is the number of queries, not time
  \return      The num of data witch is send successful
*/
int32_t csi_usi_uart_send(csi_uart_t *uart, const void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Start sending data to UART transmitter (interrupt mode).
  \param[in]   uart   UART handle to operate.
  \param[in]   data     Pointer to buffer with data to send to UART transmitter. data_type is : uint8_t for 5..8 data bits, uint16_t for 9 data bits
  \param[in]   num      Number of data items to send
  \return      The status of send func
*/
csi_error_t csi_usi_uart_send_async(csi_uart_t *uart, const void *data, uint32_t size);

/**
  \brief       Get the num of data in RX_FIFO.
  \param[in]   uart   UART handle to operate.
  \return      The num of data in RX_FIFO
*/
uint32_t csi_usi_uart_get_recvfifo_waiting_num(csi_uart_t *uart);

/**
  \brief       Start receiving data from UART receiver. \n
               This function is non-blocking,\ref uart_event_e is signaled when operation completes or error happens.
               \ref csi_uart_get_status can get operation status.
  \param[in]   uart  UART handle to operate.
  \param[out]  data  Pointer to buffer for data to receive from UART receiver.data_type is : uint8_t for 5..8 data bits, uint16_t for 9 data bits
  \param[in]   num   Number of data items to receive
  \return      Error code
*/
csi_error_t csi_usi_uart_receive_async(csi_uart_t *uart, void *data, uint32_t size);

/**
  \brief       Query data from UART receiver FIFO.
  \param[in]   uart  UART handle to operate.
  \param[out]  data  Pointer to buffer for data to receive from UART receiver
  \param[in]   num   Number of data items to receive
  \param[in]   Timeout  is the number of queries, not time
  \return      FIFO data num to receive
*/
int32_t csi_usi_uart_receive(csi_uart_t *uart, void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Get character in query mode.
  \param[in]   uart  UART handle to operate.
  \param[out]  ch The pointer to the received character.
  \return      Error code
*/
uint8_t  csi_usi_uart_getchar(csi_uart_t *uart);

/**
  \brief       Transmit character in query mode.
  \param[in]   uart  UART handle to operate.
  \param[in]   ch  The input character
  \return      Error code
*/
void csi_usi_uart_putchar(csi_uart_t *uart, uint8_t ch);

/**
  \brief       Link DMA channel to uart device
  \param[in]   uart  UART handle to operate.
  \param[in]   tx_dma The DMA channel handle for send, when it is NULL means to unlink the channel
  \param[in]   rx_dma The DMA channel handle for receive, when it is NULL means to unlink the channel
  \return      Error code
*/
csi_error_t csi_usi_uart_link_dma(csi_uart_t *uart, csi_dma_ch_t *tx_dma, csi_dma_ch_t *rx_dma);

/**
  \brief       Get the state of uart device.
  \param[in]   uart   UART handle to operate.
  \param[out]  state  The state of uart device.
  \return      Error code.
*/
csi_error_t csi_usi_uart_get_state(csi_uart_t *uart, csi_state_t *state);

/**
  \brief       Enable uart power manage.
  \param[in]   uart   UART handle to operate.
  \return      Error code.
*/
csi_error_t csi_usi_uart_enable_pm(csi_uart_t *uart);

/**
  \brief       Disable uart power manage.
  \param[in]   uart   UART handle to operate.
*/
void csi_usi_uart_disable_pm(csi_uart_t *uart);
#ifdef __cplusplus
}
#endif

#endif /* _DRV_USI_USART_H_ */
