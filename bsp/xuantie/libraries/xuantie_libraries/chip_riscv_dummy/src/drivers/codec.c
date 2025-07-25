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

#include <stdio.h>
#include <string.h>
#include <sys_clk.h>
#include <drv/i2s.h>
#include <drv/irq.h>
#include <drv/codec.h>
#include <drv/iic.h>
#include <drv/pin.h>
#include "es7210.h"
#include "es8156.h"
#include "es_port.h"

extern uint16_t i2s_tx_hs_num[];
extern uint16_t i2s_rx_hs_num[];

static csi_i2s_t i2s_codec_output;
static csi_i2s_t i2s_codec_input;
static csi_i2s_t i2s_mclk;

es7210_dev_t es7210_dev;
es8156_dev_t es8156_dev;

#define INPUT_I2S_IDX       4U
#define OUTPUT_I2S_IDX      1U

static void es_codec_irq(csi_i2s_t *i2s, csi_i2s_event_t event, void *arg)
{
    csi_codec_t *codec_cb = (csi_codec_t *) arg;

    if (event == I2S_EVENT_RECEIVE_COMPLETE) {
        if (codec_cb->input_chs->callback) {
            codec_cb->input_chs->callback(codec_cb->input_chs, CODEC_EVENT_PERIOD_READ_COMPLETE, codec_cb->input_chs->arg);
        }
    } else if (event == I2S_EVENT_SEND_COMPLETE) {
        if (codec_cb->output_chs->callback) {
            codec_cb->output_chs->callback(codec_cb->output_chs, CODEC_EVENT_PERIOD_WRITE_COMPLETE, codec_cb->output_chs->arg);
        }
    } else if (event == I2S_EVENT_ERROR) {
        if (i2s->dev.idx == OUTPUT_I2S_IDX) {
            if (codec_cb->output_chs->callback) {
                codec_cb->output_chs->callback(codec_cb->output_chs, CODEC_EVENT_ERROR, codec_cb->output_chs->arg);
            }
        } else if (i2s->dev.idx == INPUT_I2S_IDX) {
            if (codec_cb->input_chs->callback) {
                codec_cb->input_chs->callback(codec_cb->input_chs, CODEC_EVENT_ERROR, codec_cb->input_chs->arg);
            }
        }
    } else if (event == I2S_EVENT_TX_BUFFER_EMPTY) {
        if (i2s->dev.idx == OUTPUT_I2S_IDX) {
            if (codec_cb->output_chs->callback) {
                codec_cb->output_chs->callback(codec_cb->output_chs, CODEC_EVENT_WRITE_BUFFER_EMPTY, codec_cb->output_chs->arg);
            }
        }
    } else if (event == I2S_EVENT_RX_BUFFER_FULL) {
        if (i2s->dev.idx == INPUT_I2S_IDX) {
            if (codec_cb->input_chs->callback) {
                codec_cb->input_chs->callback(codec_cb->input_chs, CODEC_EVENT_READ_BUFFER_FULL, codec_cb->input_chs->arg);
            }
        }
    }

}

/**
  \brief  Init the codec according to the specified
  \param[in]   codec codec handle to operate.
  \param[in]   idx   codec interface idx
  \return      error code
*/
csi_error_t csi_codec_init(csi_codec_t *codec, uint32_t idx)
{
    CSI_PARAM_CHK(codec, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    csi_i2s_format_t i2s_format;
    /* adc i2s0 pinmux init */
    csi_pin_set_mux(PA10, PA10_I2S0_MCLK);
    /* DAC i2s1 pinmux init */
    csi_pin_set_mux(PA2, PA2_I2S1_SCLK);
    csi_pin_set_mux(PA3, PA3_I2S1_WSCLK);
    csi_pin_set_mux(PA5, PA5_I2S1_SDA);
    csi_pin_set_mux(PA26, PA26_I2S1_MCLK);

    es_port_iic_init();

    ret = csi_i2s_init(&i2s_codec_output, OUTPUT_I2S_IDX);    ///< init output i2s
    csi_i2s_attach_callback(&i2s_codec_output, es_codec_irq, (void *)codec);
    csi_i2s_enable(&i2s_codec_output, false);
    i2s_format.mode = I2S_MODE_MASTER;
    i2s_format.protocol = I2S_PROTOCOL_I2S;
    i2s_format.width = I2S_SAMPLE_WIDTH_16BIT;
    i2s_format.rate = I2S_SAMPLE_RATE_48000;
    i2s_format.polarity = I2S_LEFT_POLARITY_LOW;
    csi_i2s_format(&i2s_codec_output, &i2s_format);

    ret = csi_i2s_init(&i2s_codec_input, INPUT_I2S_IDX);   ///< init input i2s
    csi_i2s_attach_callback(&i2s_codec_input, es_codec_irq, (void *)codec);
    i2s_format.mode = I2S_MODE_MASTER;
    i2s_format.protocol = I2S_PROTOCOL_I2S;
    i2s_format.width = I2S_SAMPLE_WIDTH_16BIT;
    i2s_format.rate = I2S_SAMPLE_RATE_48000;
    i2s_format.polarity = I2S_LEFT_POLARITY_LOW;
    csi_i2s_format(&i2s_codec_input, &i2s_format);

    ret = csi_i2s_init(&i2s_mclk, 0);   ///< init input i2s
    csi_i2s_attach_callback(&i2s_mclk, es_codec_irq, (void *)codec);
    i2s_format.mode = I2S_MODE_MASTER;
    i2s_format.protocol = I2S_PROTOCOL_I2S;
    i2s_format.width = I2S_SAMPLE_WIDTH_16BIT;
    i2s_format.rate = I2S_SAMPLE_RATE_8000;
    i2s_format.polarity = I2S_LEFT_POLARITY_LOW;
    csi_i2s_format(&i2s_mclk, &i2s_format);
    csi_i2s_enable(&i2s_mclk,true);

    return ret;
}

/**
  \brief       codec uninit
  \param[in]   codec codec handle to operate.
  \return      none
*/
void csi_codec_uninit(csi_codec_t *codec)
{
    CSI_PARAM_CHK_NORETVAL(codec);
    return;
}

/**
  \brief  Open a codec output channel
  \param[in]   codec codec handle to operate.
  \param[in]   ch codec output channel handle.
  \param[in]   ch_idx codec output channel idx.
  \return      error code
*/
csi_error_t csi_codec_output_open(csi_codec_t *codec, csi_codec_output_t *ch, uint32_t ch_idx)
{
    CSI_PARAM_CHK(codec, CSI_ERROR);
    CSI_PARAM_CHK(ch, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    codec->output_chs = ch;
    ch->state.error = 0U;
    ch->state.readable = 0U;
    ch->state.writeable = 0U;
    ch->callback = NULL;
    return ret;
}

/**
  \brief  Config codec output channel
  \param[in]   ch codec output channel handle.
  \param[in]   config codec channel prarm.
  \return      error code
*/
csi_error_t csi_codec_output_config(csi_codec_output_t *ch, csi_codec_output_config_t *config)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    CSI_PARAM_CHK(config, CSI_ERROR);
    csi_error_t ret =  CSI_OK;
    csi_i2s_format_t i2s_format;

    es8156_config_t es8156_config;
    es8156_config.data_len      = ES8156_16BIT_LENGTH;
    es8156_config.i2s_mode      = ES8156_I2S_MODE_SLAVE;
    es8156_config.i2s_protocol  = ES8156_NORMAL_I2S;
    es8156_config.i2s_sclk_freq = ES8156_I2S_SCLK_32FS;
    es8156_config.mclk_freq     = ES8156_MCLK_256FS;
    es8156_config.i2s_rate      = ES8156_I2S_SAMPLE_RATE_48000;

    es8156_dev.es8156_iic_read = es_port_iic_read;
    es8156_dev.es8156_iic_write = es_port_iic_write;
    es8156_dev.es8156_addr = 0x9U;

    es8156_init(&es8156_dev, &es8156_config);

    ch->ring_buf->buffer = config->buffer;
    ch->ring_buf->size = config->buffer_size;
    ch->period = config->period;
    ch->sound_channel_num = config->sound_channel_num;

    if (i2s_codec_output.dev.reg_base == 0U) {
        ret = CSI_ERROR;
    } else {
        csi_i2s_enable(&i2s_codec_output, false);
        i2s_format.mode = I2S_MODE_MASTER;
        i2s_format.protocol = I2S_PROTOCOL_I2S;
        i2s_format.width = (csi_i2s_sample_width_t)config->bit_width;
        i2s_format.rate = (csi_i2s_sample_rate_t)config->sample_rate;
        i2s_format.polarity = I2S_LEFT_POLARITY_LOW;
        csi_i2s_format(&i2s_codec_output, &i2s_format);

        csi_i2s_tx_set_buffer(&i2s_codec_output, ch->ring_buf);
        csi_i2s_tx_buffer_reset(&i2s_codec_output);
        ret = csi_i2s_tx_set_period(&i2s_codec_output, ch->period);
    }

    return ret;
}

/**
  \brief       Attach the callback handler to codec output
  \param[in]   ch codec output channel handle.
  \param[in]   cb    callback function
  \param[in]   arg   user can define it by himself as callback's param
  \return      error code
*/
csi_error_t csi_codec_output_attach_callback(csi_codec_output_t *ch, void *callback, void *arg)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    ch->callback = callback;
    ch->arg = arg;
    return ret;
}

/**
  \brief       detach the callback handler
  \param[in]   ch codec output channel handle.
  \return      none
*/
void csi_codec_output_detach_callback(csi_codec_output_t *ch)
{
    CSI_PARAM_CHK_NORETVAL(ch);
    ch->callback = NULL;
    ch->arg = NULL;
    csi_i2s_detach_callback(&i2s_codec_output);
}

/**
  \brief  Close a CODEC output channel
  \param[in]   ch codec output channel handle.
  \return      error code
*/
void csi_codec_output_close(csi_codec_output_t *ch)
{
    CSI_PARAM_CHK_NORETVAL(ch);
    ch->state.writeable = 0U;
    ch->state.readable  = 0U;
    ch->state.error     = 0U;
    csi_i2s_uninit(&i2s_codec_output);
}

/**
  \brief       link DMA channel to codec output channel
  \param[in]   ch codec output channel handle.
  \param[in]   dma dma channel info.
  \return      error code
*/
csi_error_t csi_codec_output_link_dma(csi_codec_output_t *ch, csi_dma_ch_t *dma)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    ch->dma = dma;
    ret = csi_i2s_tx_link_dma(&i2s_codec_output, dma);
    return ret;
}

/**
  \brief       write an amount of data to cache in blocking mode.
  \param[in]   ch    the codec output channel
  \param[in]   data  send data.
  \param[in]   size  receive data size.
  \return      The num of data witch is send successful
*/
uint32_t csi_codec_output_write(csi_codec_output_t *ch, const void *data, uint32_t size)
{
    return csi_i2s_send(&i2s_codec_output, data, size);
}

/**
  \brief Write data to the cache.
  \With asynchronous sending,
  \the data is first written to the cache and then output through the codec interface.
  \This function does not block, and the return value is the number
  \of data that was successfully written to the cache.
  \param[in]   ch    the codec output channel
  \param[in]   data  send data.
  \param[in]   size  receive data size.
  \return      The data size that write to cache
*/
uint32_t csi_codec_output_write_async(csi_codec_output_t *ch, const void *data, uint32_t size)
{
    return csi_i2s_send_async(&i2s_codec_output, data, size);
}

/**
  \brief       Start sending data from the cache
  \param[in]   ch codec output channel handle.
  \return      error code
*/
csi_error_t csi_codec_output_start(csi_codec_output_t *ch)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    ch->state.writeable = 1U;
    return csi_i2s_send_start(&i2s_codec_output);
}

/**
  \brief       Stop sending data from the cache
  \param[in]   ch codec output channel handle.
  \return      error code
*/
void csi_codec_output_stop(csi_codec_output_t *ch)
{
    CSI_PARAM_CHK_NORETVAL(ch);
    ch->state.writeable = 0U;
    csi_i2s_send_stop(&i2s_codec_output);
}

/**
  \brief       Pause sending data from the cache
  \param[in]   ch codec output channel handle.
  \return      error code
*/
csi_error_t csi_codec_output_pause(csi_codec_output_t *ch)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    ch->state.writeable = 0U;
    return csi_i2s_send_pause(&i2s_codec_output);
}

/**
  \brief       Resume sending data from the cache
  \param[in]   ch codec output channel handle.
  \return      error code
*/
csi_error_t csi_codec_output_resume(csi_codec_output_t *ch)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    ch->state.writeable = 1U;
    return csi_i2s_send_resume(&i2s_codec_output);
}

/**
  \brief  Get cache free space
  \param[in]   ch codec output channel handle.
  \return buffer free space (bytes)
*/
uint32_t csi_codec_output_buffer_avail(csi_codec_output_t *ch)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    return csi_ringbuf_avail(ch->ring_buf);
}

/**
  \brief       Get buffer data num
  \param[in]   ch    Codec output channel handle
  \return      Buffer free space (bytes)
*/
uint32_t csi_codec_output_buffer_remain(csi_codec_output_t *ch)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    return csi_ringbuf_len(ch->ring_buf);
}

/**
  \brief  Reset the buf, discard all data in the cache
  \param[in]   ch codec output channel handle.
  \return      error code
*/
csi_error_t csi_codec_output_buffer_reset(csi_codec_output_t *ch)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    csi_error_t ret = CSI_ERROR;
    csi_ringbuf_reset(ch->ring_buf);

    if (ch->ring_buf->buffer != NULL) {
        memset(ch->ring_buf->buffer, 0, ch->ring_buf->size);
    }

    if ((ch->ring_buf->read == 0U) && (ch->ring_buf->write == 0U)) {
        ret = CSI_OK;
    }

    return ret;
}

/**
  \brief       mute codec ouput channel
  \param[in]   ch codec output channel handle.
  \param[in]   en true codec mute.
  \return      error code
*/
csi_error_t csi_codec_output_mute(csi_codec_output_t *ch, bool enable)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    es8156_set_software_mute(&es8156_dev, true);
    return ret;
}

/**
  \brief       Set codec ouput channel digital gain.
  \param[in]   ch codec output channel handle.
  \param[in]   val gain val.
  \return      error code
*/
csi_error_t csi_codec_output_digital_gain(csi_codec_output_t *ch, uint32_t val)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    csi_error_t ret = CSI_UNSUPPORTED;
    return ret;
}

/**
  \brief       Set codec ouput channel analog gain.
  \param[in]   ch codec output channel handle.
  \param[in]   val gain val.
  \return      error code
*/
csi_error_t csi_codec_output_analog_gain(csi_codec_output_t *ch, uint32_t val)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    /*
      range0 ~ 0xff, step:0.75DB
      0（-95.5DB）... 0xbf(0DB) ... 0xff(32DB)
    */
    if (val > 0xff) {
        val = 0xff;
    }

    ret = es8156_set_volume(&es8156_dev, val);

    return ret;
}

/**
  \brief       Set codec ouput channel mix gain.
  \param[in]   ch codec output channel handle.
  \param[in]   val gain val.
  \return      error code
*/
csi_error_t csi_codec_output_mix_gain(csi_codec_output_t *ch, uint32_t val)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    csi_error_t ret = CSI_UNSUPPORTED;
    return ret;
}

/**
  \brief       Get codec output channel state.
  \param[in]   ch codec output channel handle.
  \param[out]  state channel state.
  \return      channel state
*/
csi_error_t csi_codec_output_get_state(csi_codec_output_t *ch, csi_state_t *state)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    CSI_PARAM_CHK(state, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    memcpy(state, &(ch->state), sizeof(csi_state_t));
    return ret;
}

/**
  \brief  Open a CODEC input channel
  \param[in]   codec codec handle to operate.
  \param[in]   ch codec input channel handle.
  \param[in]   ch_idx codec input channel idx.
  \return      error code
*/
csi_error_t csi_codec_input_open(csi_codec_t *codec, csi_codec_input_t *ch, uint32_t ch_idx)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    CSI_PARAM_CHK(codec, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    codec->input_chs = ch;
    ch->state.error = 0U;
    ch->state.readable = 0U;
    ch->state.writeable = 0U;
    ch->callback = NULL;
    return ret;
}

/**
  \brief  Config codec input channel
  \param[in]   ch codec input channel handle.
  \param[in]   config codec channel prarm.
  \return      error code
*/
csi_error_t csi_codec_input_config(csi_codec_input_t *ch, csi_codec_input_config_t *config)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    CSI_PARAM_CHK(config, CSI_ERROR);
    csi_error_t ret =  CSI_OK;
    csi_i2s_format_t i2s_format;
    es7210_config_t es7210_config;

    ch->ring_buf->buffer = config->buffer;
    ch->ring_buf->size = config->buffer_size;
    ch->period = config->period;
    ch->sound_channel_num = config->sound_channel_num;

    es7210_config.data_len      = ES7210_16BIT_LENGTH;
    es7210_config.i2s_mode      = ES7210_I2S_MODE_SLAVE;
    es7210_config.i2s_protocol  = ES7210_NORMAL_I2S;
    es7210_config.i2s_sclk_freq = ES7210_I2S_SCLK_32FS;
    es7210_config.mclk_freq     = ES7210_MCLK_256FS;

    es7210_dev.es7210_iic_read = es_port_iic_read;
    es7210_dev.es7210_iic_write = es_port_iic_write;
    es7210_dev.es7210_addr = 0x40U;

    es7210_init(&es7210_dev, &es7210_config);

    if (i2s_codec_input.dev.reg_base == 0U) {
        ret = CSI_ERROR;
    } else {
        csi_i2s_enable(&i2s_codec_input, false);

        i2s_format.mode = I2S_MODE_MASTER;
        i2s_format.protocol = I2S_PROTOCOL_I2S;
        i2s_format.width = (csi_i2s_sample_width_t)config->bit_width;
        i2s_format.rate = (csi_i2s_sample_rate_t)config->sample_rate;
        i2s_format.polarity = I2S_LEFT_POLARITY_LOW;
        i2s_format.sclk_nfs = I2S_SCLK_32FS;
        i2s_format.mclk_nfs = I2S_MCLK_256FS;
        csi_i2s_format(&i2s_codec_input, &i2s_format);

        csi_i2s_rx_set_buffer(&i2s_codec_input, ch->ring_buf);
        csi_i2s_rx_buffer_reset(&i2s_codec_input);
        ret = csi_i2s_rx_set_period(&i2s_codec_input, ch->period);
    }

    return ret;
}

/**
  \brief       Attach the callback handler to codec output
  \param[in]   ch codec input channel handle.
  \param[in]   cb    callback function
  \param[in]   arg   user can define it by himself as callback's param
  \return      error code
*/
csi_error_t csi_codec_input_attach_callback(csi_codec_input_t *ch, void *callback, void *arg)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    ch->callback = callback;
    ch->arg = arg;
    return ret;
}

/**
  \brief       detach the callback handler
  \param[in]   ch codec input channel handle.
  \return      none
*/
void csi_codec_input_detach_callback(csi_codec_input_t *ch)
{
    CSI_PARAM_CHK_NORETVAL(ch);
    ch->callback = NULL;
    ch->arg = NULL;
    csi_i2s_detach_callback(&i2s_codec_input);
}

/**
  \brief  Close a CODEC input channel
  \param[in]   ch codec input channel handle..
  \return      error code
*/
void csi_codec_input_close(csi_codec_input_t *ch)
{
    CSI_PARAM_CHK_NORETVAL(ch);
    ch->state.writeable = 0U;
    ch->state.readable  = 0U;
    ch->state.error     = 0U;
    csi_i2s_uninit(&i2s_codec_input);
}

/**
  \brief       link DMA channel to codec input channel
  \param[in]   ch codec input channel handle.
  \param[in]   dma dma channel info.
  \return      error code
*/
csi_error_t csi_codec_input_link_dma(csi_codec_input_t *ch, csi_dma_ch_t *dma)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    ch->dma = dma;
    ret = csi_i2s_rx_link_dma(&i2s_codec_input, dma);
    return ret;
}

/**
  \brief  read an amount of data in blocking mode.
  \param[in]   ch codec input channel handle.
  \param[in]   data  save receive data.
  \param[in]   size  receive data size.
  \return      The size of data receive successfully
*/
uint32_t csi_codec_input_read(csi_codec_input_t *ch, void *data, uint32_t size)
{
    return csi_i2s_receive(&i2s_codec_input, data, size);
}

/**
  \brief Read data from the cache.
  \Using asynchronous receive.
  \This function read data from the cache, returns the number of successful reads,
  \and returns 0 if there is no data in the cache.
  \param[in]   ch codec input channel handle.
  \param[in]   data  the buf save receive data.
  \param[in]   size  receive data size.
  \return      The size of data read successfully
*/
uint32_t csi_codec_input_read_async(csi_codec_input_t *ch, void *data, uint32_t size)
{
    return csi_i2s_receive_async(&i2s_codec_input, data, size);
}

/**
  \brief       Start receive data, writes the recording data to the cache
  \param[in]   ch codec input channel handle.
  \return      error code
*/
csi_error_t csi_codec_input_start(csi_codec_input_t *ch)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    ch->state.readable = 1U;
    return csi_i2s_receive_start(&i2s_codec_input);
}

/**
  \brief       Stop receive data.
  \param[in]   ch codec input channel handle.
  \return      error code
*/
void csi_codec_input_stop(csi_codec_input_t *ch)
{
    CSI_PARAM_CHK_NORETVAL(ch);
    ch->state.readable = 0U;
    csi_i2s_receive_stop(&i2s_codec_input);
}

/**
  \brief       Get buffer free space
  \param[in]   ch    Codec input channel handle
  \return      Buffer free space (bytes)
*/
uint32_t csi_codec_input_buffer_avail(csi_codec_input_t *ch)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    return csi_ringbuf_avail(ch->ring_buf);
}

/**
  \brief       Get buffer data num
  \param[in]   ch    Codec input channel handle
  \return      Buffer free space (bytes)
*/
uint32_t csi_codec_input_buffer_remain(csi_codec_input_t *ch)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    return csi_ringbuf_len(ch->ring_buf);
}

/**
  \brief  Reset the buf, discard all data in the cache
  \param[in]   ch codec input channel handle.
  \return      error code
*/
csi_error_t csi_codec_input_buffer_reset(csi_codec_input_t *ch)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    csi_error_t ret = CSI_ERROR;
    csi_ringbuf_reset(ch->ring_buf);

    if (ch->ring_buf->buffer != NULL) {
        memset(ch->ring_buf->buffer, 0, ch->ring_buf->size);
    }

    if ((ch->ring_buf->read == 0U) && (ch->ring_buf->write == 0U)) {
        ret = CSI_OK;
    }

    return ret;
}

/**
  \brief       mute codec input channel
  \param[in]   ch codec input channel handle.
  \param[in]   en true codec mute.
  \return      error code
*/
csi_error_t csi_codec_input_mute(csi_codec_input_t *ch, bool en)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    es7210_mic1_set_mute(&es7210_dev, en);
    es7210_mic2_set_mute(&es7210_dev, en);
    return ret;
}

/**
  \brief       Set codec input channel digital gain.
  \param[in]   ch codec input channel handle.
  \param[in]   val gain val.
  \return      error code
*/
csi_error_t csi_codec_input_digital_gain(csi_codec_input_t *ch, uint32_t val)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    csi_error_t ret = CSI_UNSUPPORTED;
    return ret;
}

/**
  \brief       Set codec input channel analog gain.
  \param[in]   ch codec input channel handle.
  \param[in]   val gain val.
  \return      error code
*/
csi_error_t csi_codec_input_analog_gain(csi_codec_input_t *ch, uint32_t val)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    /*
      range0 ~ 14, step:3DB
      0（-95.5DBDB）... 0xBF(0DB) ... 0xff(32DB)
    */
    if (val > 0xff) {
        val = 0xff;
    }

    ret = es7210_adc1_set_gain(&es7210_dev, val);
    ret = es7210_adc2_set_gain(&es7210_dev, val);
    ret = es7210_adc3_set_gain(&es7210_dev, val);
    ret = es7210_adc4_set_gain(&es7210_dev, val);
    return ret;
}

/**
  \brief       Set codec input channel mix gain.
  \param[in]   ch codec input channel handle.
  \param[in]   val gain val.
  \return      error code
*/
csi_error_t csi_codec_input_mix_gain(csi_codec_input_t *ch, uint32_t val)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    csi_error_t ret = CSI_UNSUPPORTED;
    return ret;
}

/**
  \brief       Get codec input channel state.
  \param[in]   ch codec input channel handle.
  \param[out]  state channel state.
  \return      channel state
*/
csi_error_t csi_codec_input_get_state(csi_codec_input_t *ch, csi_state_t *state)
{
    CSI_PARAM_CHK(ch, CSI_ERROR);
    CSI_PARAM_CHK(state, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    memcpy(state, &(ch->state), sizeof(csi_state_t));
    return ret;
}




