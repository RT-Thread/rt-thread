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
 * @file     drv/codec.h
 * @brief    head file for codec
 * @version  V1.0
 * @date     17. Mar 2020
 * @model    codec
 ******************************************************************************/
#ifndef _DRV_CODEC_H_
#define _DRV_CODEC_H_

#include <stdint.h>
#include <stdbool.h>
#include <drv/common.h>
#include <drv/dma.h>
#include "drv/ringbuf.h"

typedef enum {
    CODEC_EVENT_PERIOD_READ_COMPLETE        = 0U,  ///< A peroid data read completed
    CODEC_EVENT_PERIOD_WRITE_COMPLETE       = 1U,  ///< A peroid data write completed
    CODEC_EVENT_WRITE_BUFFER_EMPTY          = 2U,  ///< Fifo is empty
    CODEC_EVENT_READ_BUFFER_FULL            = 3U,  ///< Fifo is full
    CODEC_EVENT_ERROR_OVERFLOW              = 4U,  ///< Fifo overflow error
    CODEC_EVENT_ERROR_UNDERFLOW             = 5U,  ///< Fifo underflow error
    CODEC_EVENT_ERROR                       = 6U,  ///< The device has a hardware error
} csi_codec_event_t;

struct csi_codec;
typedef struct csi_codec csi_codec_t;
typedef struct csi_codec_output csi_codec_output_t;
struct csi_codec_output {
    csi_codec_t               *codec;
    uint32_t                  ch_idx;            ///< Codec output channel idx
    void (*callback)(csi_codec_output_t *output, csi_codec_event_t event, void *arg);
    void                      *arg;
    csi_ringbuf_t              *ring_buf;         ///< The csi_ringbuf used to save audio data
    uint32_t                  period;            ///< When the period data is sent, the callback function will be called
    uint32_t                  sound_channel_num; ///< Number of sound channel
    csi_dma_ch_t              *dma;              ///< Dma channel handle
    csi_state_t               state;             ///< Codec output channel current state
    void                      *priv;
    struct csi_codec_output   *next;
};

typedef struct csi_codec_input csi_codec_input_t;
struct csi_codec_input {
    csi_codec_t              *codec;
    uint32_t                  ch_idx;             ///< Codec input channel idx
    void (*callback)(csi_codec_input_t *input, csi_codec_event_t event, void *arg);
    void                      *arg;
    csi_ringbuf_t              *ring_buf;          ///< The csi_ringbuf used to save audio data
    uint32_t                  period;             ///< When the period data is received, the callback function will be called
    uint32_t                  sound_channel_num;  ///< Number of sound channel
    csi_dma_ch_t              *dma;               ///< Codec input channel current state
    csi_state_t               state;              ///< Dma channel handle
    void                      *priv;
    struct csi_codec_input    *next;
};

struct csi_codec {
    csi_dev_t           dev;         ///< Codec hw-device info
    csi_codec_output_t  *output_chs; ///< Codec output channel operate handle
    csi_codec_input_t   *input_chs;  ///< Codec input channel operate handle
    void                *priv;       ///< User private param passed to user callback
};

typedef enum {
    CODEC_OUTPUT_SINGLE_ENDED,      ///< Single-ended output
    CODEC_OUTPUT_DIFFERENCE,        ///< Differential output
} csi_codec_output_mode_t;

typedef enum {
    CODEC_INPUT_SINGLE_ENDED,      ///< Single-ended input
    CODEC_INPUT_DIFFERENCE,        ///< Differential input
} csi_codec_input_mode_t;

typedef struct {
    uint32_t                sample_rate;                ///< Input data sample rate
    uint32_t                bit_width;                  ///< Input data sample width
    csi_codec_input_mode_t  mode;                       ///< Input work mode
    uint8_t                 *buffer;                    ///< The buffer used to save audio data
    uint32_t                buffer_size;                ///< Input buffer size
    uint32_t                period;                     ///< When a peroid data is reached,the callback function is called
    uint32_t                sound_channel_num;          ///< Number of soundtrack per channel
} csi_codec_input_config_t;

typedef struct {
    uint32_t                sample_rate;                ///< Output data sample rate
    uint32_t                bit_width;                  ///< Onput data sample width
    csi_codec_output_mode_t mode;                       ///< Onput work mode
    uint8_t                 *buffer;                    ///< The buffer used to save audio data
    uint32_t                buffer_size;                ///< Output buffer size
    uint32_t                period;                     ///< When a peroid data is reached,the callback function is called
    uint32_t                sound_channel_num;          ///< Number of soundchannel per channel
} csi_codec_output_config_t;

/**
  \brief       Init the codec according to the specified
  \param[in]   codec  Codec handle to operate
  \param[in]   idx    Codec interface idx
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_init(csi_codec_t *codec, uint32_t idx);

/**
  \brief       Codec uninit
  \param[in]   codec    Codec handle to operate
  \return      None
*/
void csi_codec_uninit(csi_codec_t *codec);

/**
  \brief       Open a codec output channel
  \param[in]   codec     Codec handle to operate
  \param[in]   ch        Codec output channel handle
  \param[in]   ch_idx    Codec output channel idx
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_output_open(csi_codec_t *codec, csi_codec_output_t *ch, uint32_t ch_idx);

/**
  \brief       Config codec output channel
  \param[in]   ch        Codec output channel handle
  \param[in]   config    Codec channel param. \ref csi_codec_output_config_t
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_output_config(csi_codec_output_t *ch, csi_codec_output_config_t *config);

/**
  \brief       Attach the callback handler to codec output
  \param[in]   ch     Codec output channel handle
  \param[in]   cb     Callback function
  \param[in]   arg    User private param
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_output_attach_callback(csi_codec_output_t *ch, void *callback, void *arg);

/**
  \brief       Detach the callback handler
  \param[in]   ch    Codec output channel handle
  \return      None
*/
void csi_codec_output_detach_callback(csi_codec_output_t *ch);

/**
  \brief       Close a codec output channel
  \param[in]   ch    Codec output channel handle
  \return      error code \ref csi_error_t
*/
void csi_codec_output_close(csi_codec_output_t *ch);

/**
  \brief       Link DMA channel to codec output channel
  \param[in]   ch     Codec output channel handle
  \param[in]   dma    The codec output DMA channel handle, when it is NULL means to unlink the channel
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_output_link_dma(csi_codec_output_t *ch, csi_dma_ch_t *dma);

/**
  \brief       Send an amount of data to buffer in blocking mode
  \param[in]   ch      The codec output channel
  \param[in]   data    Pointer to send data buffer
  \param[in]   size    Send data size
  \return      the num of data witch is send successful
*/
uint32_t csi_codec_output_write(csi_codec_output_t *ch, const void *data, uint32_t size);

/**
  \brief       Send data to the buffer with asynchronous sending
               The data is first written to the buffer and then output through the codec interface
               This function does not block, and the return value is the number
               Of data that was successfully written to the buffer
  \param[in]   ch      The codec output channel
  \param[in]   data    Pointer to send data buffer
  \param[in]   size    Send data size
  \return      The data size that send to buffer
*/
uint32_t csi_codec_output_write_async(csi_codec_output_t *ch, const void *data, uint32_t size);

/**
  \brief       Start sending data from the buffer
  \param[in]   ch    Codec output channel handle
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_output_start(csi_codec_output_t *ch);

/**
  \brief       Stop sending data from the buffer
  \param[in]   ch    Codec output channel handle
  \return      None
*/
void csi_codec_output_stop(csi_codec_output_t *ch);

/**
  \brief       Pause sending data from the buffer
  \param[in]   ch    Codec output channel handle
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_output_pause(csi_codec_output_t *ch);

/**
  \brief       Resume sending data from the buffer
  \param[in]   ch    Codec output channel handle
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_output_resume(csi_codec_output_t *ch);

/**
  \brief       Get output-buffer free space
  \param[in]   ch    Codec output channel handle
  \return      Buffer free space (bytes)
*/
uint32_t csi_codec_output_buffer_avail(csi_codec_output_t *ch);

/**
  \brief       Get used space of output-buffer
  \param[in]   ch    Codec output channel handle
  \return      Buffer free space (bytes)
*/
uint32_t csi_codec_output_buffer_remain(csi_codec_output_t *ch);

/**
  \brief       Reset the buf, discard all data in the buffer
  \param[in]   ch    Codec output channel handle
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_output_buffer_reset(csi_codec_output_t *ch);

/**
  \brief       Mute codec ouput channel
  \param[in]   ch    Codec output channel handle
  \param[in]   en    True enable codec mute. false disable codec mute
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_output_mute(csi_codec_output_t *ch, bool enable);

/**
  \brief       Set codec ouput channel digital gain
  \param[in]   ch     Codec output channel handle
  \param[in]   val    Gain val
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_output_digital_gain(csi_codec_output_t *ch, uint32_t val);

/**
  \brief       Set codec ouput channel analog gain
  \param[in]   ch     Codec output channel handle
  \param[in]   val    Gain val
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_output_analog_gain(csi_codec_output_t *ch, uint32_t val);

/**
  \brief       Set codec ouput channel mix gain
  \param[in]   ch     Codec output channel handle
  \param[in]   val    Gain val
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_output_mix_gain(csi_codec_output_t *ch, uint32_t val);

/**
  \brief       Get codec output channel state
  \param[in]   ch       Codec output channel handle
  \param[out]  state    Channel state. \ref csi_state_t
  \return      channel state
*/
csi_error_t csi_codec_output_get_state(csi_codec_output_t *ch, csi_state_t *state);

/**
  \brief       Open a codec input channel
  \param[in]   codec     Codec handle to operate
  \param[in]   ch        Codec input channel handle
  \param[in]   ch_idx    Codec input channel idx
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_input_open(csi_codec_t *codec, csi_codec_input_t *ch, uint32_t ch_idx);

/**
  \brief       Config codec input channel
  \param[in]   ch        Codec input channel handle
  \param[in]   config    Codec channel prarm. \ref csi_codec_input_config_t
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_input_config(csi_codec_input_t *ch, csi_codec_input_config_t *config);

/**
  \brief       Attach the callback handler to codec output
  \param[in]   ch     Codec input channel handle
  \param[in]   cb     Callback function
  \param[in]   arg    User private param for event callback
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_input_attach_callback(csi_codec_input_t *ch, void *callback, void *arg);

/**
  \brief       Detach the callback handler
  \param[in]   ch    Codec input channel handle
  \return      None
*/
void csi_codec_input_detach_callback(csi_codec_input_t *ch);

/**
  \brief       Close a codec input channel
  \param[in]   ch    Codec input channel handle
  \return      None
*/
void csi_codec_input_close(csi_codec_input_t *ch);

/**
  \brief       Link DMA channel to codec input channel
  \param[in]   ch     Codec input channel handle
  \param[in]   dma    The codec input DMA channel handle, when it is NULL means to unlink the channel
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_input_link_dma(csi_codec_input_t *ch, csi_dma_ch_t *dma);

/**
  \brief       Read an amount of data in blocking mode
  \param[in]   ch      Codec input channel handle
  \param[in]   data    Pointer to receive data buffer
  \param[in]   size    Receive data size
  \return      The size of data read successfully
*/
uint32_t csi_codec_input_read(csi_codec_input_t *ch, void *data, uint32_t size);

/**
  \brief       Read data from the buffer
               using asynchronous receive
               this function read data from the buffer, returns the number of successful receive
               and returns 0 if there is no data in the buffer
  \param[in]   ch      Codec input channel handle
  \param[in]   data    Pointer to receive data buffer
  \param[in]   size    Receive data size
  \return      The size of data read successfully
*/
uint32_t csi_codec_input_read_async(csi_codec_input_t *ch, void *data, uint32_t size);

/**
  \brief       Start receive data to the buffer
  \param[in]   ch    Codec input channel handle
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_input_start(csi_codec_input_t *ch);

/**
  \brief       Stop receive data
  \param[in]   ch    Codec input channel handle
  \return      None
*/
void csi_codec_input_stop(csi_codec_input_t *ch);

/**
  \brief       Reset the buf, discard all data in the buffer
  \param[in]   ch    Codec input channel handle
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_input_buffer_reset(csi_codec_input_t *ch);

/**
  \brief       Get input-buffer free space
  \param[in]   ch    Codec input channel handle
  \return      Buffer free space (bytes)
*/
uint32_t csi_codec_input_buffer_avail(csi_codec_input_t *ch);

/**
  \brief       Get used space of input-buffer
  \param[in]   ch    Codec input channel handle
  \return      Buffer free space (bytes)
*/
uint32_t csi_codec_input_buffer_remain(csi_codec_input_t *ch);

/**
  \brief       Mute codec input channel
  \param[in]   ch    Codec input channel handle
  \param[in]   en    True enable codec mute. false disable codec mute
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_input_mute(csi_codec_input_t *ch, bool en);

/**
  \brief       Set codec input channel digital gain
  \param[in]   ch     Codec input channel handle
  \param[in]   val    Gain val
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_input_digital_gain(csi_codec_input_t *ch, uint32_t val);

/**
  \brief       Set codec input channel analog gain
  \param[in]   ch     Codec input channel handle
  \param[in]   val    Gain val
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_input_analog_gain(csi_codec_input_t *ch, uint32_t val);

/**
  \brief       Set codec input channel mix gain
  \param[in]   ch     Codec input channel handle
  \param[in]   val    Gain val
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_input_mix_gain(csi_codec_input_t *ch, uint32_t val);

/**
  \brief       Get codec input channel state
  \param[in]   ch       Codec input channel handle
  \param[out]  state    Channel state
  \return      Channel state
*/
csi_error_t csi_codec_input_get_state(csi_codec_input_t *ch, csi_state_t *state);

/**
  \brief       Enable codec power manage
  \param[in]   codec    Codec handle to operate
  \return      error code \ref csi_error_t
*/
csi_error_t csi_codec_enable_pm(csi_codec_t *codec);

/**
  \brief       Disable codec power manage
  \param[in]   codec    Codec handle to operate
  \return      None
*/
void csi_codec_disable_pm(csi_codec_t *codec);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_CODEC_H_  */

