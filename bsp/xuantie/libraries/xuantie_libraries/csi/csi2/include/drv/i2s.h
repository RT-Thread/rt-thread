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
 * @file     drv/i2s.h
 * @brief    header file for i2s driver
 * @version  V1.0
 * @date     16. Mar 2020
 * @model    i2s
 ******************************************************************************/

#ifndef _DRV_I2S_H_
#define _DRV_I2S_H_

#include <stdint.h>
#include <stdbool.h>
#include <drv/common.h>
#include <drv/dma.h>
#include "drv/ringbuf.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    I2S_MODE_MASTER,                                     ///< I2s transmitter master mode
    I2S_MODE_SLAVE,                                      ///< I2s transmitter slave mode
} csi_i2s_mode_t;

typedef enum {
    I2S_PROTOCOL_I2S,                                    ///< I2S protocol
    I2S_PROTOCOL_MSB_JUSTIFIED,                          ///< MSB (left) justified protocol
    I2S_PROTOCOL_LSB_JUSTIFIED,                          ///< LSB (right) justified protocol
    I2S_PROTOCOL_PCM,                                    ///< PCM protocol
} csi_i2s_protocol_t;

typedef enum {
    I2S_LEFT_POLARITY_LOW,                               ///< Low level represents the left channel
    I2S_LEFT_POLARITY_HIGH,                              ///< High level represents the left channel
} csi_i2s_ws_left_polarity_t;

typedef enum {
    I2S_SAMPLE_RATE_8000              = 8000U,           ///< I2S sample rate is 8000
    I2S_SAMPLE_RATE_11025             = 11025U,
    I2S_SAMPLE_RATE_12000             = 12000U,
    I2S_SAMPLE_RATE_16000             = 16000U,
    I2S_SAMPLE_RATE_22050             = 22050U,
    I2S_SAMPLE_RATE_24000             = 24000U,
    I2S_SAMPLE_RATE_32000             = 32000U,
    I2S_SAMPLE_RATE_44100             = 44100U,
    I2S_SAMPLE_RATE_48000             = 48000U,
    I2S_SAMPLE_RATE_96000             = 96000U,
    I2S_SAMPLE_RATE_192000            = 192000U,
    I2S_SAMPLE_RATE_256000            = 256000U,
} csi_i2s_sample_rate_t;

typedef enum {
    I2S_SAMPLE_WIDTH_16BIT = 16U,                        ///< I2S sample width is 16bit
    I2S_SAMPLE_WIDTH_24BIT = 24U,
    I2S_SAMPLE_WIDTH_32BIT = 32U,
} csi_i2s_sample_width_t;

typedef enum {
    I2S_SCLK_16FS = 16U,                                ///< SCLK frequency is 16 times that of I2S sample rate
    I2S_SCLK_32FS = 32U,
    I2S_SCLK_48FS = 48U,
    I2S_SCLK_64FS = 64U,
} csi_i2s_sclk_freq_t;

typedef enum {
    I2S_MCLK_256FS = 256U,                              ///< MCLK frequency is 256 times that of I2S sample rate
    I2S_MCLK_384FS = 384U,
} csi_i2s_mclk_freq_t;

typedef struct {
    csi_i2s_mode_t             mode;                    ///< I2S work mode
    csi_i2s_protocol_t         protocol;                ///< Protocols used by I2S
    csi_i2s_ws_left_polarity_t polarity;                ///< left channel polarity
    csi_i2s_sample_rate_t      rate;                    ///< I2S sample rate
    csi_i2s_sample_width_t     width;                   ///< I2S sample width
    csi_i2s_sclk_freq_t        sclk_nfs;                ///< SCLK frequency is N times that of I2S sample rate
    csi_i2s_mclk_freq_t        mclk_nfs;                ///< MCLK frequency is N times that of I2S sample rate
} csi_i2s_format_t;

typedef enum {
    I2S_LEFT_CHANNEL,
    I2S_RIGHT_CHANNEL,
    I2S_LEFT_RIGHT_CHANNEL,
} csi_i2s_sound_channel_t;

typedef enum {
    I2S_EVENT_SEND_COMPLETE,
    I2S_EVENT_RECEIVE_COMPLETE,
    I2S_EVENT_TX_BUFFER_EMPTY,
    I2S_EVENT_RX_BUFFER_FULL,
    I2S_EVENT_ERROR_OVERFLOW,
    I2S_EVENT_ERROR_UNDERFLOW,
    I2S_EVENT_ERROR,
} csi_i2s_event_t;

typedef struct csi_i2s csi_i2s_t;

struct csi_i2s {
    csi_dev_t               dev;                ///< I2S hw-device info
    void (*callback)(csi_i2s_t *i2s, csi_i2s_event_t event, void *arg); ///< I2S event callback for user
    void                    *arg;               ///< user private param passed to user callback
    csi_ringbuf_t            *tx_buf;            ///< I2S send buffer
    csi_ringbuf_t            *rx_buf;            ///< I2S receive buffer
    csi_dma_ch_t            *tx_dma;            ///< send dma channel handle
    csi_dma_ch_t            *rx_dma;            ///< receive dma channel handle
    uint32_t                tx_period;          ///< I2S send period num data will callback
    uint32_t                rx_period;          ///< I2S receive period num data will callback
    csi_state_t             state;              ///< I2S communication state
    void                    *priv;
};

/**
  \brief       Init i2s
  \param[in]   i2s    I2s handle to operate
  \param[in]   idx    I2s interface idx
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_init(csi_i2s_t *i2s, uint32_t idx);

/**
  \brief       Uninit i2s
  \param[in]   i2s    I2s handle to operate
  \return      none
*/
void csi_i2s_uninit(csi_i2s_t *i2s);

/**
  \brief       Enable i2s
  \param[in]   i2s   I2s handle to operate
  \param[in]   en    True enable, False disable
  \return      None
*/
void csi_i2s_enable(csi_i2s_t *i2s, bool enable);

/**
  \brief       I2s config format
  \param[in]   i2s       I2s handle to operate
  \param[in]   format    I2s config param \ref csi_i2s_format_t
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_format(csi_i2s_t *i2s, csi_i2s_format_t *format);

/**
  \brief       Set the i2s tx mono
  \param[in]   i2s   I2s handle to operate
  \param[in]   ch    Mono channel selection
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_tx_select_sound_channel(csi_i2s_t *i2s, csi_i2s_sound_channel_t ch);

/**
  \brief       Set the i2s rx mono
  \param[in]   i2s   I2s handle to operate
  \param[in]   ch    Mono channel selection
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_rx_select_sound_channel(csi_i2s_t *i2s, csi_i2s_sound_channel_t ch);

/**
  \brief       Link DMA channel to i2s device
  \param[in]   i2s       I2s handle to operate
  \param[in]   rx_dma    The DMA channel  for receive, when it is NULL means to unused dma
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_rx_link_dma(csi_i2s_t *i2s, csi_dma_ch_t *rx_dma);

/**
  \brief       Link DMA channel to i2s device
  \param[in]   i2s       I2s handle to operate
  \param[in]   tx_dma    The DMA channel for send, when it is NULL means to unused dma
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_tx_link_dma(csi_i2s_t *i2s, csi_dma_ch_t *tx_dma);

/**
  \brief       I2s rx buffer config
  \param[in]   i2s       I2s handle to operate
  \param[in]   buffer    I2s rx buffer
  \return      None
*/
void csi_i2s_rx_set_buffer(csi_i2s_t *i2s, csi_ringbuf_t *buffer);

/**
  \brief       I2s tx buffer config
  \param[in]   i2s       I2s handle to operate
  \param[in]   buffer    I2s tx buffer
  \return      None
*/
void csi_i2s_tx_set_buffer(csi_i2s_t *i2s, csi_ringbuf_t *buffer);

/**
  \brief       I2s rx set period.The value of period is to report a receive completion event
               after each period value data is received
  \param[in]   i2s       I2s handle to operate
  \param[in]   period    I2s rx period
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_rx_set_period(csi_i2s_t *i2s, uint32_t period);

/**
  \brief       I2s tx set period.The value of period is to report a receive completion event
               after each period value data is send
  \param[in]   i2s       I2s handle to operate
  \param[in]   period    I2s tx period
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_tx_set_period(csi_i2s_t *i2s, uint32_t period);

/**
  \brief       Get rx csi_ringbuf buffer free space
  \param[in]   i2s    I2s handle to operate
  \return      Buffer free space (bytes)
*/
uint32_t csi_i2s_rx_buffer_avail(csi_i2s_t *i2s);

/**
  \brief       Get rx csi_ringbuf buffer used space
  \param[in]   i2s    I2s handle to operate
  \return      Buffer used space (bytes)
*/
uint32_t csi_i2s_rx_buffer_remain(csi_i2s_t *i2s);

/**
  \brief       Reset the rx csi_ringbuf, discard all data in the buffer
  \param[in]   i2s    I2s handle to operate
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_rx_buffer_reset(csi_i2s_t *i2s);

/**
  \brief        Get tx csi_ringbuf buffer free space
  \param[in]    i2s    I2s handle to operate
  \return       Buffer free space (bytes)
*/
uint32_t    csi_i2s_tx_buffer_avail(csi_i2s_t *i2s);

/**
  \brief        Get tx csi_ringbuf buffer used space
  \param[in]    i2s    I2s handle to operate
  \return       Buffer used space (bytes)
*/
uint32_t    csi_i2s_tx_buffer_remain(csi_i2s_t *i2s);

/**
  \brief       Reset the tx csi_ringbuf, discard all data in the buffer
  \param[in]   i2s    Handle to operate
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_tx_buffer_reset(csi_i2s_t *i2s);

/**
  \brief       Send an amount of data to buffer in blocking mode
  \param[in]   i2s     Operate handle
  \param[in]   data    Pointer to send data buffer
  \param[in]   size    Send data size
  \return      The num of data witch is send successful
*/
int32_t    csi_i2s_send(csi_i2s_t *i2s, const void *data, uint32_t size);

/**
  \brief       Receive an amount of data to buffer in blocking mode
  \param[in]   i2s     Operate handle
  \param[out]  data    Pointer to receive data buffer
  \param[in]   size    Receive data size
  \return      The size of data receive successfully
*/
int32_t    csi_i2s_receive(csi_i2s_t *i2s, void *data, uint32_t size);

/**
  \brief       Write data to the buffer
               With asynchronous sending
               The data is first written to the buffer and then output through the i2s interface
               Return value is the number of data that was successfully written to the buffer
  \param[in]   i2s     Operate handle
  \param[in]   data    Pointer to send data buffer
  \param[in]   size    Send data size
  \return      The data size that write to buffer
*/
uint32_t    csi_i2s_send_async(csi_i2s_t *i2s, const void *data, uint32_t size);

/**
  \brief       Read data from the buffer
               Using asynchronous receive, i2s writes the received data to the buffer
               This function reads data from the buffer, returns the number of successful reads
               Returns 0 if there is no data in the buffer
  \param[in]   i2s     Operate handle
  \param[out]  data    Pointer to receive data buffer
  \param[in]   size    Receive data size
  \return      The size of data read successfully
*/
uint32_t    csi_i2s_receive_async(csi_i2s_t *i2s, void *data, uint32_t size);

/**
  \brief       Start i2s pause asynchronous send
  \param[in]   i2s    Operate handle
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_send_pause(csi_i2s_t *i2s);

/**
  \brief       Start i2s resume asynchronous send
  \param[in]   i2s    Operate handle
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_send_resume(csi_i2s_t *i2s);

/**
  \brief       Start i2s asynchronous send
  \param[in]   i2s    Operate handle
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_send_start(csi_i2s_t *i2s);

/**
  \brief       Start i2s asynchronous receive
  \param[in]   i2s    Operate handle
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_receive_start(csi_i2s_t *i2s);

/**
  \brief       Stop i2s asynchronous send
  \param[in]   i2s    Operate handle
  \return      None
*/
void csi_i2s_send_stop(csi_i2s_t *i2s);

/**
  \brief       Stop i2s asynchronous receive
  \param[in]   i2s    Operate handle
  \return      None
*/
void csi_i2s_receive_stop(csi_i2s_t *i2s);

/**
  \brief       Attach the callback handler to i2s
  \param[in]   i2s    Operate handle
  \param[in]   cb     Callback function
  \param[in]   arg    User private param
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_attach_callback(csi_i2s_t *i2s, void *callback, void *arg);

/**
  \brief       Detach the callback handler
  \param[in]   i2s    Operate handle
  \return      None
*/
void csi_i2s_detach_callback(csi_i2s_t *i2s);

/**
  \brief       Get i2s status
  \param[in]   i2s      I2s handle to operate
  \param[out]  state    I2s state
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_get_state(csi_i2s_t *i2s, csi_state_t *state);

/**
  \brief       Enable i2s power manage
  \param[in]   i2s    I2s handle to operate
  \return      error code \ref csi_error_t
*/
csi_error_t csi_i2s_enable_pm(csi_i2s_t *i2s);

/**
  \brief       Disable i2s power manage
  \param[in]   i2s    I2s handle to operate
  \return      None
*/
void csi_i2s_disable_pm(csi_i2s_t *i2s);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_I2S_H_ */
