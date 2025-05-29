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
 * @file     drv/spi.h
 * @brief    Header File for SPI Driver
 * @version  V1.0
 * @date     08. Apr 2020
 * @model    spi
 ******************************************************************************/

#ifndef _DRV_SPI_H_
#define _DRV_SPI_H_

#include <stdint.h>
#include <drv/common.h>
#include <drv/gpio.h>
#include <drv/dma.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \enum    csi_spi_mode_t
 *  \brief   Function mode of spi
 */
typedef enum {
    SPI_MASTER,             ///< SPI Master (Output on MOSI, Input on MISO); arg = Bus Speed in bps
    SPI_SLAVE,              ///< SPI Slave  (Output on MISO, Input on MOSI)
} csi_spi_mode_t;

/**
 *  \enum     csi_spi_frame_len_t
 *  \brief    SPI data width (4bit ~ 16bit)
 */
typedef enum {
    SPI_FRAME_LEN_4  = 4,
    SPI_FRAME_LEN_5,
    SPI_FRAME_LEN_6,
    SPI_FRAME_LEN_7,
    SPI_FRAME_LEN_8,
    SPI_FRAME_LEN_9,
    SPI_FRAME_LEN_10,
    SPI_FRAME_LEN_11,
    SPI_FRAME_LEN_12,
    SPI_FRAME_LEN_13,
    SPI_FRAME_LEN_14,
    SPI_FRAME_LEN_15,
    SPI_FRAME_LEN_16
} csi_spi_frame_len_t;

/**
 *  \enum     csi_spi_format_t
 *  \brief    Timing format of spi
 */
typedef enum {
    SPI_FORMAT_CPOL0_CPHA0 = 0,  ///< Clock Polarity 0, Clock Phase 0
    SPI_FORMAT_CPOL0_CPHA1,      ///< Clock Polarity 0, Clock Phase 1
    SPI_FORMAT_CPOL1_CPHA0,      ///< Clock Polarity 1, Clock Phase 0
    SPI_FORMAT_CPOL1_CPHA1,      ///< Clock Polarity 1, Clock Phase 1
} csi_spi_cp_format_t;

/**
 *  \enum     csi_spi_event_t
 *  \brief    Signaled event for user by driver
 */
typedef enum {
    SPI_EVENT_SEND_COMPLETE,           ///< Data Send completed. Occurs after call to csi_spi_send_async to indicate that all the data has been send over
    SPI_EVENT_RECEIVE_COMPLETE,        ///< Data Receive completed. Occurs after call to csi_spi_receive_async to indicate that all the data has been received
    SPI_EVENT_SEND_RECEIVE_COMPLETE,   ///< Data Send_receive completed. Occurs after call to csi_spi_send_receive_async to indicate that all the data has been send_received
    SPI_EVENT_ERROR_OVERFLOW,          ///< Data overflow: Receive overflow
    SPI_EVENT_ERROR_UNDERFLOW,         ///< Data underflow: Transmit underflow
    SPI_EVENT_ERROR                    ///< Master Mode Fault (SS deactivated when Master).Occurs in master mode when Slave Select is deactivated and indicates Master Mode Fault
} csi_spi_event_t;

/**
 *  \struct     csi_spi_t
 *  \brief      Ctrl block of spi instance
 */
typedef struct csi_spi csi_spi_t;
struct csi_spi {
    csi_dev_t            dev;          ///< Hw-device info
    void (*callback)(csi_spi_t *spi, csi_spi_event_t event, void *arg); ///< User callback ,signaled by driver event
    void                *arg;          ///< User private param ,passed to user callback
    uint8_t             *tx_data;      ///< Output data buf
    uint32_t             tx_size;      ///< Output data size specified by user
    uint8_t             *rx_data;      ///< Input  data buf
    uint32_t             rx_size;      ///< Input  data size specified by user
    csi_error_t (*send)(csi_spi_t *spi, const void *data, uint32_t size); ///< The send_async func
    csi_error_t (*receive)(csi_spi_t *spi, void *data, uint32_t size);    ///< The receive_async func
    csi_error_t (*send_receive)(csi_spi_t *spi, const void *data_out, void *data_in, uint32_t size); ///< The send_receive_async func
    csi_state_t          state;        ///< Peripheral state
    csi_dma_ch_t        *tx_dma;
    csi_dma_ch_t        *rx_dma;
    void                *priv;
};

/**
  \brief       Initialize SPI Interface
               Initialize the resources needed for the SPI instance
  \param[in]   spi    SPI handle
  \param[in]   idx    SPI instance index
  \return      Error code
*/
csi_error_t csi_spi_init(csi_spi_t *spi, uint32_t idx);

/**
  \brief       De-initialize SPI Interface
               stops Operation and releases the software resources used by the spi instance
  \param[in]   spi    Handle
  \return      None
*/
void    csi_spi_uninit(csi_spi_t *spi);

/**
  \brief       Attach the callback handler to SPI
  \param[in]   spi    Operate handle
  \param[in]   callback    Callback function
  \param[in]   arg         User can define it by himself as callback's param
  \return      Error code
*/
csi_error_t csi_spi_attach_callback(csi_spi_t *spi, void *callback, void *arg);

/**
  \brief       Detach the callback handler
  \param[in]   spi    Operate handle
  \return      None
*/
void        csi_spi_detach_callback(csi_spi_t *spi);

/**
  \brief       Config spi mode (master or slave)
  \param[in]   spi     SPI handle
  \param[in]   mode    The mode of spi (master or slave)
  \return      Error code
*/
csi_error_t csi_spi_mode(csi_spi_t *spi, csi_spi_mode_t mode);

/**
  \brief       Config spi cp format
  \param[in]   spi       SPI handle
  \param[in]   format    SPI cp format
  \return      Error code
*/
csi_error_t csi_spi_cp_format(csi_spi_t *spi, csi_spi_cp_format_t format);

/**
  \brief       Config spi frame len
  \param[in]   spi       SPI handle
  \param[in]   length    SPI frame len
  \return      Error code
*/
csi_error_t csi_spi_frame_len(csi_spi_t *spi, csi_spi_frame_len_t length);

/**
  \brief       Config spi work frequence
  \param[in]   spi     SPI handle
  \param[in]   baud    SPI work baud
  \return      the actual config frequency
*/
uint32_t csi_spi_baud(csi_spi_t *spi, uint32_t baud);

/**
  \brief       Sending data to SPI transmitter,(received data is ignored)
               blocking mode ,return unti all data has been sent or err happened
  \param[in]   spi        Handle to operate
  \param[in]   data       Pointer to buffer with data to send to SPI transmitter
  \param[in]   size       Number of data to send(byte)
  \param[in]   timeout    Unit in mini-second
  \return      If send successful, this function shall return the num of data witch is sent successful
               otherwise, the function shall return Error code
*/
int32_t csi_spi_send(csi_spi_t *spi, const void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Sending data to SPI transmitter,(received data is ignored)
               non-blocking mode,transfer done event will be signaled by driver
  \param[in]   spi     Handle to operate
  \param[in]   data    Pointer to buffer with data to send to SPI transmitter
  \param[in]   size    Number of data items to send(byte)
  \return      Error code
*/
csi_error_t csi_spi_send_async(csi_spi_t *spi, const void *data, uint32_t size);

/**
  \brief       Receiving data from SPI receiver
               blocking mode, return untill curtain data items are readed
  \param[in]   spi        Handle to operate
  \param[out]  data       Pointer to buffer for data to receive from SPI receiver
  \param[in]   size       Number of data items to receive(byte)
  \param[in]   timeout    Unit in mini-second
  \return      If receive successful, this function shall return the num of data witch is  received successful
               otherwise, the function shall return Error code
*/
int32_t csi_spi_receive(csi_spi_t *spi, void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Receiving data from SPI receiver
               not-blocking mode, event will be signaled when receive done or err happend
  \param[in]   spi     Handle to operate
  \param[out]  data    Pointer to buffer for data to receive from SPI receiver
  \param[in]   size    Number of data items to receive(byte)
  \return      Error code
*/
csi_error_t csi_spi_receive_async(csi_spi_t *spi, void *data, uint32_t size);

/**
  \brief       Dulplex,sending and receiving data at the same time
               \ref csi_spi_event_t is signaled when operation completes or error happens
               \ref csi_spi_get_state can get operation status
               blocking mode, this function returns after operation completes or error happens
  \param[in]   spi         SPI handle to operate
  \param[in]   data_out    Pointer to buffer with data to send to SPI transmitter
  \param[out]  data_in     Pointer to buffer for data to receive from SPI receiver
  \param[in]   size        Data size(byte)
  \return      If transfer successful, this function shall return the num of data witch is transfer successful,
               otherwise, the function shall return Error code
*/
int32_t csi_spi_send_receive(csi_spi_t *spi, const void *data_out, void *data_in, uint32_t size, uint32_t timeout);

/**
  \brief       Transmit first then receive ,receive will begin after transmit is done
               if non-blocking mode, this function only starts the transfer,
               \ref csi_spi_event_t is signaled when operation completes or error happens
               \ref csi_spi_get_state can get operation status
  \param[in]   spi         SPI handle to operate
  \param[in]   data_out    Pointer to buffer with data to send to SPI transmitter
  \param[out]  data_in     Pointer to buffer for data to receive from SPI receiver
  \param[in]   size        Data size(byte)
  \return      Error code
*/
csi_error_t csi_spi_send_receive_async(csi_spi_t *spi, const void *data_out, void *data_in, uint32_t size);

/*
  \brief       Set slave select num. Only valid for master
  \param[in]   handle       SPI handle to operate
  \param[in]   slave_num    SPI slave num
  \return      None
 */
void csi_spi_select_slave(csi_spi_t *spi, uint32_t slave_num);

/**
  \brief       Link DMA channel to spi device
  \param[in]   spi       SPI handle to operate
  \param[in]   tx_dma    The DMA channel handle for send, when it is NULL means to unlink the channel
  \param[in]   rx_dma    The DMA channel handle for receive, when it is NULL means to unlink the channel
  \return      Error code
*/
csi_error_t csi_spi_link_dma(csi_spi_t *spi, csi_dma_ch_t *tx_dma, csi_dma_ch_t *rx_dma);

/**
  \brief       Get the state of spi device
  \param[in]   spi      SPI handle to operate
  \param[out]  state    The state of spi device
  \return      Error code
*/
csi_error_t csi_spi_get_state(csi_spi_t *spi, csi_state_t *state);

/**
  \brief       Enable spi power manage
  \param[in]   spi  SPI handle to operate
  \return      Error code
*/
csi_error_t csi_spi_enable_pm(csi_spi_t *spi);

/**
  \brief       Disable spi power manage
  \param[in]   spi    SPI handle to operate
  \return      Error code
*/
void csi_spi_disable_pm(csi_spi_t *spi);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_SPI_H_ */
