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
 * @file     drv/usi_spi.h
 * @brief    Header File for SPI Driver
 * @version  V1.0
 * @date     02. June 2020
 * @model    usi_spi
 ******************************************************************************/

#ifndef _DRV_SPI_USI_H_
#define _DRV_SPI_USI_H_

#include <stdint.h>
#include <drv/common.h>
#include <drv/spi.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief       Initialize SPI Interface.
               Initializes the resources needed for the SPI instance
  \param[in]   spi      SPI handle
  \param[in]   idx      SPI instance index
  \return      Error code
*/
csi_error_t csi_usi_spi_init(csi_spi_t *spi, uint32_t idx);

/**
  \brief       De-initialize SPI Interface
               Stops operation and releases the software resources used by the spi instance
  \param[in]   spi SPI handle
  \return      None
*/
void    csi_usi_spi_uninit(csi_spi_t *spi);

/**
  \brief       Attach the callback handler to SPI
  \param[in]   spi  Operate handle.
  \param[in]   callback    Callback function
  \param[in]   arg   User can define it by himself as callback's param
  \return      Error code
*/
csi_error_t csi_usi_spi_attach_callback(csi_spi_t *spi, void *callback, void *arg);

/**
  \brief       Detach the callback handler
  \param[in]   spi  Operate handle.
  \return      None
*/
void        csi_usi_spi_detach_callback(csi_spi_t *spi);


/**
  \brief       Config spi mode (master or slave).
  \param[in]   spi    SPI handle
  \param[in]   mode   The mode of spi (master or slave)
  \return      Error code
*/
csi_error_t csi_usi_spi_mode(csi_spi_t *spi, csi_spi_mode_t mode);

/**
  \brief       Config spi cp format.
  \param[in]   spi       SPI handle
  \param[in]   format    SPI cp format
  \return      Error code
*/
csi_error_t csi_usi_spi_cp_format(csi_spi_t *spi, csi_spi_cp_format_t format);

/**
  \brief       Config spi frame len.
  \param[in]   spi       SPI handle
  \param[in]   length    spi frame len
  \return      error code
*/
csi_error_t csi_usi_spi_frame_len(csi_spi_t *spi, csi_spi_frame_len_t length);

/**
  \brief       Config spi work frequence.
  \param[in]   spi     SPI handle
  \param[in]   baud    SPI work baud
  \return      The actual config frequency
*/
uint32_t csi_usi_spi_baud(csi_spi_t *spi, uint32_t baud);

/**
  \brief       Config spi mode.
  \param[in]   Handle spi handle to operate.
  \param[in]   baud      SPI baud rate. If negative, then this attribute not changed
  \param[in]   mode      \ref spi_mode_e . If negative, then this attribute not changed
  \param[in]   format    \ref spi_format_e . If negative, then this attribute not changed
  \param[in]   order     \ref spi_bit_order_e . If negative, then this attribute not changed
  \param[in]   ss_mode   \ref spi_ss_mode_t . If negative, then this attribute not changed
  \param[in]   bit_width SPI data bitwidth: (1 ~ SPI_DATAWIDTH_MAX) . If negative, then this attribute not changed
  \return      Error code
*/
csi_error_t drv_usi_spi_config(csi_spi_t *spi, csi_spi_mode_t mode, csi_spi_frame_len_t width, csi_spi_cp_format_t format);

/**
  \brief       Sending data to SPI transmitter,(received data is ignored).
               Blocking mode ,return unti all data has been sent or err happened
  \param[in]   spi   Handle to operate.
  \param[in]   data  Pointer to buffer with data to send to SPI transmitter.
  \param[in]   size  Number of data to send(byte)
  \param[in]   timeout  Unit in mini-second
  \return      If send success, this function shall return the num of data witch is sent successful
               otherwise, the function shall return error code
*/
int32_t csi_usi_spi_send(csi_spi_t *spi, const void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Sending data to SPI transmitter,(received data is ignored).
               non-blocking mode,transfer done event will be signaled by driver
  \param[in]   spi   Handle to operate.
  \param[in]   data  Pointer to buffer with data to send to SPI transmitter.
  \param[in]   size  Number of data items to send(byte)
  \return      Error code
*/
csi_error_t csi_usi_spi_send_async(csi_spi_t *spi, const void *data, uint32_t size);

/**
  \brief       Receiving data from SPI receiver.
               Blocking mode, return untill curtain data items are readed
  \param[in]   spi   Handle to operate.
  \param[out]  data  Pointer to buffer for data to receive from SPI receiver
  \param[in]   size  Number of data items to receive(byte)
  \param[in]   timeout  Unit in mini-second
  \return      If receive success, this function shall return the num of data witch is received successful
               Otherwise, the function shall return error code
*/
int32_t csi_usi_spi_receive(csi_spi_t *spi, void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Receiving data from SPI receiver.
               Not-blocking mode, event will be signaled when receive done or err happend
  \param[in]   spi   Handle to operate.
  \param[out]  data  Pointer to buffer for data to receive from SPI receiver
  \param[in]   size  Number of data items to receive(byte)
  \return      Error code
*/
csi_error_t csi_usi_spi_receive_async(csi_spi_t *spi, void *data, uint32_t size);

/**
  \brief       Dulplex,sending and receiving data at the same time
               \ref csi_spi_event_t is signaled when operation completes or error happens.
               \ref csi_spi_get_state can get operation status.
               Blocking mode, this function returns after operation completes or error happens.
  \param[in]   Handle spi handle to operate.
  \param[in]   data_out  Pointer to buffer with data to send to SPI transmitter
  \param[out]  data_in   Pointer to buffer for data to receive from SPI receiver
  \param[in]   size      Data size(byte)
  \return      If transfer success, this function shall return the num of data witch is transfer successful
               otherwise, the function shall return error code
*/
int32_t csi_usi_spi_send_receive(csi_spi_t *spi, const void *data_out, void *data_in, uint32_t size, uint32_t timeout);

/**
  \brief       Transmit first then receive ,receive will begin after transmit is done
               if non-blocking mode, this function only starts the transfer,
               \ref csi_spi_event_t is signaled when operation completes or error happens.
               \ref csi_spi_get_state can get operation status.
  \param[in]   handle spi Handle to operate.
  \param[in]   data_out  Pointer to buffer with data to send to SPI transmitter
  \param[out]  data_in   Pointer to buffer for data to receive from SPI receiver
  \param[in]   size      Data size(byte)
  \return      Error code
*/
csi_error_t csi_usi_spi_send_receive_async(csi_spi_t *spi, const void *data_out, void *data_in, uint32_t size);

/*
  \brief       Set slave select num. Only valid for master
  \param[in]   Handle  spi handle to operate.
  \param[in]   slave_num  SPI slave num.
  \return      None
 */
void csi_usi_spi_select_slave(csi_spi_t *spi, uint32_t slave_num);

/**
  \brief       Link DMA channel to spi device
  \param[in]   spi  SPI handle to operate.
  \param[in]   tx_dma The DMA channel handle for send, when it is NULL means to unlink the channel
  \param[in]   rx_dma The DMA channel handle for receive, when it is NULL means to unlink the channel
  \return      Error code
*/
csi_error_t csi_usi_spi_link_dma(csi_spi_t *spi, csi_dma_ch_t *tx_dma, csi_dma_ch_t *rx_dma);

/**
  \brief       Get the state of spi device
  \param[in]   spi  SPI handle to operate.
  \param[out]  state The state of spi device
  \return      Error code
*/
csi_error_t csi_usi_spi_get_state(csi_spi_t *spi, csi_state_t *state);

/**
  \brief       Enable spi power manage
  \param[in]   spi  SPI handle to operate.
  \return      Error code
*/
csi_error_t csi_usi_spi_enable_pm(csi_spi_t *spi);

/**
  \brief       Disable spi power manage
  \param[in]   spi  SPI handle to operate.
  \return      Error code
*/
void csi_spi_disable_pm(csi_spi_t *spi);
#ifdef __cplusplus
}
#endif

#endif /* _DRV_SPI_USI_H_ */
