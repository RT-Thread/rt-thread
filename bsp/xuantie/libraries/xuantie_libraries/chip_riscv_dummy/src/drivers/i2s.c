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
#include <csi_config.h>
#include <sys_clk.h>
#include <drv/i2s.h>
#include <drv/irq.h>

extern uint16_t i2s_tx_hs_num[];
extern uint16_t i2s_rx_hs_num[];

void wj_i2s_dma_event_cb(csi_dma_ch_t *dma, csi_dma_event_t event, void *arg)
{
    CSI_PARAM_CHK_NORETVAL(dma);

    csi_i2s_t *i2s = (csi_i2s_t *)dma->parent;

    if (event == DMA_EVENT_TRANSFER_ERROR) {/* DMA transfer ERROR */
        if (i2s->tx_dma->ch_id == dma->ch_id) {
            /* to do tx error action */
            i2s->state.error = 1U;

            if (i2s->callback) {
                i2s->callback(i2s, I2S_EVENT_ERROR, i2s->arg);
            }
        } else if (i2s->rx_dma->ch_id == dma->ch_id) {
            /* to do rx error action */
            i2s->state.error = 1U;

            if (i2s->callback) {
                i2s->callback(i2s, I2S_EVENT_ERROR, i2s->arg);
            }
        }

    } else if (event == DMA_EVENT_TRANSFER_DONE) {/* DMA transfer complete */
        if ((i2s->tx_dma != NULL) && (i2s->tx_dma->ch_id == dma->ch_id)) {
            /* to do tx action */
            uint32_t read_len = i2s->tx_period;
            i2s->tx_buf->read = (i2s->tx_buf->read + read_len) % i2s->tx_buf->size;

            if (i2s->tx_buf->data_len == 0U) {
                i2s->tx_buf->data_len = 0U;

                if (i2s->callback) {
                    i2s->callback(i2s, I2S_EVENT_TX_BUFFER_EMPTY, i2s->arg);
                }

            } else {
                i2s->tx_buf->data_len -= read_len;
            }

            ///< TODO：调用csi_dma_ch_start开始DMA发送数据

            if (i2s->callback) {
                i2s->callback(i2s, I2S_EVENT_SEND_COMPLETE, i2s->arg);
            }
        } else {

            soc_dcache_clean_invalid_range((unsigned long)(i2s->rx_buf->buffer + i2s->rx_buf->write), i2s->rx_period);

            ///< TODO：调用csi_dma_ch_start开启DMA接收数据

            if (i2s->callback && i2s->rx_buf->data_len != 0) {
                i2s->callback(i2s, I2S_EVENT_RECEIVE_COMPLETE, i2s->arg);
            } else {
                i2s->callback(i2s, I2S_EVENT_RX_BUFFER_FULL, i2s->arg);
            }
        }
    }
}

/**
  \brief       I2S init
  \param[in]   i2s i2s handle to operate.
  \param[in]   idx i2s interface idx
  \return      error code
*/
csi_error_t csi_i2s_init(csi_i2s_t *i2s, uint32_t idx)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    ///< 获取中断号、基地址等相关信息
    ret = target_get(DEV_WJ_I2S_TAG, idx, &i2s->dev);

    if (ret == CSI_OK) {
        ///< TODO：清除I2S的中断
    }

    i2s->rx_dma = NULL;
    i2s->tx_dma = NULL;
    i2s->rx_buf = NULL;
    i2s->tx_buf = NULL;
    i2s->state.error = 0U;
    i2s->state.readable = 0U;
    i2s->state.writeable = 0U;
    i2s->priv = (void *)0U;
    i2s->callback = NULL;
    return ret;
}

/**
  \brief       I2S uninit
  \param[in]   i2s i2s handle to operate.
  \return      none
*/
void csi_i2s_uninit(csi_i2s_t *i2s)
{
    CSI_PARAM_CHK_NORETVAL(i2s);
    i2s->rx_dma = NULL;
    i2s->tx_dma = NULL;
    i2s->rx_buf = NULL;
    i2s->tx_buf = NULL;
    i2s->state.error = 0U;
    i2s->state.readable = 0U;
    i2s->state.writeable = 0U;

    ///< TODO：关闭I2S的使能
    ///< TODO：清除I2S的中断

}

/**
  \brief       I2S enable
  \param[in]   i2s i2s handle to operate.
  \param[in]   en  1 enable, 0 disable
  \return      none
*/
void csi_i2s_enable(csi_i2s_t *i2s, bool enable)
{
    CSI_PARAM_CHK_NORETVAL(i2s);

    if (enable) {
        ///< TODO：使能I2S
    } else {
        ///< TODO：不使能I2S
    }
}

/**
  \brief       I2S config
  \param[in]   i2s i2s handle to operate.
  \param[in]   config i2s config param
  \return      error code
*/
csi_error_t csi_i2s_format(csi_i2s_t *i2s, csi_i2s_format_t *format)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    CSI_PARAM_CHK(format, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    switch (format->mode) {
        case I2S_MODE_MASTER:
            ///< TODO：设置I2S为主机接收模式
            ///< TODO：设置I2S为主机发送模式
            break;

        case I2S_MODE_SLAVE:
            ///< TODO：设置I2S为从机接收模式
            ///< TODO：设置I2S为从机发送模式
            break;

        default:
            ret = CSI_ERROR;
            break;
    }

    switch (format->protocol) {
        case I2S_PROTOCOL_I2S:
            ///< TODO：设置I2S的接收为I2S格式
            ///< TODO：设置I2S的发送为I2S格式
            break;

        case I2S_PROTOCOL_MSB_JUSTIFIED:
            ///< TODO：设置I2S的接收为left-justified格式
            ///< TODO：设置I2S的发送为left-justified格式
            break;

        case I2S_PROTOCOL_LSB_JUSTIFIED:
            ///< TODO：设置I2S的接收为right-justified格式
            ///< TODO：设置I2S的发送为right-justified格式
            break;

        case I2S_PROTOCOL_PCM:
            ///< TODO：设置I2S的接收为PCM格式
            ///< TODO：设置I2S的发送为PCM格式
            break;

        default:
            ret = CSI_ERROR;
            break;
    }

    switch (format->width) {
        case I2S_SAMPLE_WIDTH_16BIT:
            ///< TODO：设置I2S的数据宽度为16位
            break;

        case I2S_SAMPLE_WIDTH_24BIT:
            ///< TODO：设置I2S的数据宽度为24位
            break;

        case I2S_SAMPLE_WIDTH_32BIT:
            ///< TODO：设置I2S的数据宽度为32位
            break;

        default:
            ret = CSI_UNSUPPORTED;
            break;
    }

    if (format->mode == I2S_MODE_MASTER) {

        ///< TODO：设置I2S获取wsclk对应的分频寄存器
        ///< TODO：设置I2S获取reference clock对应的分频寄存器为0

    } else {
        ///< TODO：设置从机接收模式音频输入速率由硬件自动检测
    }

    if (format->polarity) {
        ///< TODO：配置发送模式高电平对应的时左声道的数据
        ///< TODO：配置接收模式高电平对应的时左声道的数据
    } else {
        ///< TODO：配置发送模式高电平对应的时右声道的数据
        ///< TODO：配置接收模式高电平对应的时右声道的数据
    }

    switch (format->sclk_nfs) {
        case I2S_SCLK_16FS:
            ///< TODO：配置接收模式sclk的频率为16*FS
            break;

        case I2S_SCLK_32FS:
            ///< TODO：配置接收模式sclk的频率为32*FS
            break;

        case I2S_SCLK_48FS:
            ///< TODO：配置接收模式sclk的频率为48*FS
            format->mclk_nfs = I2S_MCLK_384FS;           ///< if SCLK_SEL=01 then mclk_o=384*fs，select MCLK_SEL:384fs
            break;

        case I2S_SCLK_64FS:
            ///< TODO：配置接收模式sclk的频率为64*FS
            break;

        default:
            break;
    }

    if (format->mclk_nfs == I2S_MCLK_384FS) {
        ///< TODO：配置接收模式mclk的频率为384*FS
    } else {
        ///< TODO：配置接收模式mclk的频率为256*FS
    }

    return ret;
}

/**
  \brief       Set the i2s tx mono
  \param[in]   i2s i2s handle to operate.
  \param[in]   Mono channel selection.
  \param[in]   bool mono mode enable
  \return      error code
*/
csi_error_t csi_i2s_tx_select_sound_channel(csi_i2s_t *i2s, csi_i2s_sound_channel_t ch)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    switch (ch) {
        case I2S_LEFT_CHANNEL:
            ///< TODO：配置发送数据模式数据源是单声道数据（左右声道数据相同）
            ///< TODO：配置发送模式低电平对应的数据是左声道的数据
            break;

        case I2S_RIGHT_CHANNEL:
            ///< TODO：配置发送数据模式数据源是单通道数据（左右声道数据相同）
            ///< TODO：配置发送模式高电平对应的数据是左声道的数据
            break;

        case I2S_LEFT_RIGHT_CHANNEL:
            ///< TODO：配置发送数据模式数据源是双声道数据
            break;

        default:
            break;
    }

    return ret;
}

/**
  \brief       Set the i2s rx mono
  \param[in]   i2s i2s handle to operate.
  \param[in]   Mono channel selection.
  \param[in]   bool mono mode enable
  \return      error code
*/
csi_error_t csi_i2s_rx_select_sound_channel(csi_i2s_t *i2s, csi_i2s_sound_channel_t ch)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    switch (ch) {
        case I2S_LEFT_CHANNEL:
            ///< TODO：配置接收数据模式数据源是单声道数据（左右声道数据相同）
            ///< TODO：配置接收模式接收的的数据是左声道的数据
            break;

        case I2S_RIGHT_CHANNEL:
            ///< TODO：配置接收数据模式数据源是单声道数据（左右声道数据相同）
            ///< TODO：配置接收模式接收的的数据是右声道的数据
            break;

        case I2S_LEFT_RIGHT_CHANNEL:
            ///< TODO：配置接收数据模式数据源是双声道数据
            break;

        default:
            break;
    }

    return ret;
}

/**
  \brief       link DMA channel to i2s device
  \param[in]   i2s  i2s handle to operate.
  \param[in]   rx_dma the DMA channel  for receive, when it is NULL means to unused dma.
  \return      error code
*/
csi_error_t csi_i2s_rx_link_dma(csi_i2s_t *i2s, csi_dma_ch_t *rx_dma)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    if (rx_dma != NULL) {
        rx_dma->parent = i2s;
        /// 申请DMA通道
        ret = csi_dma_ch_alloc(rx_dma, -1, -1);

        if (ret == CSI_OK) {
            /// 注册DMA传输完成回调函数
            csi_dma_ch_attach_callback(rx_dma, wj_i2s_dma_event_cb, NULL);
            i2s->rx_dma = rx_dma;
        } else {
            rx_dma->parent = NULL;
            ret = CSI_ERROR;
        }
    } else {
        if (i2s->rx_dma) {
            /// 注销DMA传输完成回调函数
            csi_dma_ch_detach_callback(i2s->rx_dma);
            /// 释放DMA通道
            csi_dma_ch_free(i2s->rx_dma);
            i2s->rx_dma = NULL;
        } else {
            ret = CSI_ERROR;
        }
    }

    return ret;
}

/**
  \brief       link DMA channel to i2s device
  \param[in]   i2s  i2s handle to operate.
  \param[in]   rx_dma the DMA channel  for receive, when it is NULL means to unused dma.
  \return      error code
*/
csi_error_t csi_i2s_tx_link_dma(csi_i2s_t *i2s, csi_dma_ch_t *tx_dma)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    if (tx_dma != NULL) {
        tx_dma->parent = i2s;
        /// 申请DMA通道
        ret = csi_dma_ch_alloc(tx_dma, -1, -1);

        if (ret == CSI_OK) {
            /// 注册DMA传输完成回调函数
            csi_dma_ch_attach_callback(tx_dma, wj_i2s_dma_event_cb, NULL);
            i2s->tx_dma = tx_dma;
        } else {
            tx_dma->parent = NULL;
            ret = CSI_ERROR;
        }
    } else {
        if (i2s->tx_dma) {
            /// 注销DMA传输完成回调函数
            csi_dma_ch_detach_callback(i2s->tx_dma);
            /// 释放DMA通道
            csi_dma_ch_free(i2s->tx_dma);
            i2s->tx_dma = NULL;
        } else {
            ret = CSI_ERROR;
        }
    }

    return ret;
}

/**
  \brief       I2S rx cache config
  \param[in]   i2s i2s handle to operate.
  \param[in]   buffer i2s rx cache
  \return      none
*/
void csi_i2s_rx_set_buffer(csi_i2s_t *i2s, csi_ringbuf_t *buffer)
{
    CSI_PARAM_CHK_NORETVAL(i2s);
    CSI_PARAM_CHK_NORETVAL(buffer);
    i2s->rx_buf = buffer;
}

/**
  \brief       I2S tx cache config
  \param[in]   i2s i2s handle to operate.
  \param[in]   buffer i2s tx cache
  \return      none
*/
void csi_i2s_tx_set_buffer(csi_i2s_t *i2s, csi_ringbuf_t *buffer)
{
    CSI_PARAM_CHK_NORETVAL(i2s);
    CSI_PARAM_CHK_NORETVAL(buffer);
    i2s->tx_buf = buffer;
}

/**
  \brief       I2S rx set period.The value of period is to report a receive completion event
  \            after each period value data is received.
  \param[in]   i2s i2s handle to operate.
  \param[in]   buffer i2s rx cache
  \return      none
*/
csi_error_t csi_i2s_rx_set_period(csi_i2s_t *i2s, uint32_t period)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    if (period == 0U) {
        ret = CSI_ERROR;
    } else {
        if ((i2s->rx_buf->size % period) != 0U) {
            ret = CSI_ERROR;
        } else {
            i2s->rx_period = period;
        }
    }

    return ret;
}

/**
  \brief       I2S tx set period.The value of period is to report a receive completion event
  \            after each period value data is send.
  \param[in]   i2s i2s handle to operate.
  \param[in]   buffer i2s tx cache
  \return      none
*/
csi_error_t csi_i2s_tx_set_period(csi_i2s_t *i2s, uint32_t period)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    if (period == 0U) {
        ret = CSI_ERROR;
    } else {
        if ((i2s->tx_buf->size % period) != 0U) {
            ret = CSI_ERROR;
        } else {
            i2s->tx_period = period;
        }
    }

    return ret;
}

/**
  \brief  Get rx csi_ringbuf cache free space
   \param[in]   i2s i2s handle to operate.
  \return buffer free space (bytes)
*/
uint32_t csi_i2s_rx_buffer_avail(csi_i2s_t *i2s)
{
    CSI_PARAM_CHK(i2s, 0U);
    return csi_ringbuf_avail(i2s->rx_buf);
}

/**
  \brief  Reset the rx csi_ringbuf, discard all data in the cache
  \param[in]   i2s i2s handle to operate.
  \return      error code
*/
csi_error_t csi_i2s_rx_buffer_reset(csi_i2s_t *i2s)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    csi_error_t ret = CSI_ERROR;
    csi_ringbuf_reset(i2s->rx_buf);

    if (i2s->rx_buf->buffer != NULL) {
        memset(i2s->rx_buf->buffer, 0, i2s->rx_buf->size);
    }

    if ((i2s->rx_buf->read == 0U) && (i2s->rx_buf->write == 0U)) {
        ret = CSI_OK;
    }

    return ret;
}

/**
  \brief  Get tx csi_ringbuf cache free space
   \param[in]   i2s i2s handle to operate.
  \return buffer free space (bytes)
*/
uint32_t csi_i2s_tx_buffer_avail(csi_i2s_t *i2s)
{
    CSI_PARAM_CHK(i2s, 0U);
    return csi_ringbuf_avail(i2s->tx_buf);
}

/**
  \brief  Reset the tx csi_ringbuf, discard all data in the cache
  \param[in]   i2s i2s handle to operate.
  \return      error code
*/
csi_error_t csi_i2s_tx_buffer_reset(csi_i2s_t *i2s)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    csi_error_t ret = CSI_ERROR;
    csi_ringbuf_reset(i2s->tx_buf);

    if (i2s->tx_buf->buffer != NULL) {
        memset(i2s->tx_buf->buffer, 0, i2s->tx_buf->size);
    }

    if ((i2s->tx_buf->read == 0U) && (i2s->tx_buf->write == 0U)) {
        ret = CSI_OK;
    }

    return ret;
}
/**
  \brief  Receive an amount of data to cache in blocking mode.
  \param[in]   i2s   operate handle.
  \param[in]   data  save receive data.
  \param[in]   size  receive data size.
  \param[in]   timeout  is the number of queries, not time
  \return      The size of data receive successfully
*/
int32_t csi_i2s_receive(csi_i2s_t *i2s, void *data, uint32_t size)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    uint8_t *read_data = (void *)data;
    int32_t read_size = 0;

    if (i2s->rx_dma == NULL) {
        ///< TODO：关闭i2s
        ///< TODO：设置i2s为接收模式
        ///< TODO：打开i2s
        ///< TODO：循环读数据寄存器接收数据直到接收到指定长度的数据，并把接收到的数据长度存放到read_size
    } else {

        while (1) {
            read_size += (int32_t)csi_ringbuf_out(i2s->rx_buf, (void *)(read_data + (uint32_t)read_size), (size - (uint32_t)read_size));

            if ((size - (uint32_t)read_size) <= 0U) {
                break;
            }
        }

    }

    return read_size;
}

/**
  \brief Write data to the cache.
  \With asynchronous sending,
  \the data is first written to the cache and then output through the I2S interface.
  \This function does not block, and the return value is the number
  \of data that was successfully written to the cache.
  \param[in]   i2s   operate handle.
  \param[in]   data  send data.
  \param[in]   size  receive data size.
  \return      The data size that write to cache
*/
uint32_t csi_i2s_send_async(csi_i2s_t *i2s, const void *data, uint32_t size)
{
    CSI_PARAM_CHK(i2s, 0U);
    CSI_PARAM_CHK(data, 0U);
    uint32_t write_len;
    write_len = csi_ringbuf_in(i2s->tx_buf, data, size);

    if ((uint8_t *)i2s->priv) { ///< if dma is stop, then start it
        soc_dcache_clean_invalid_range((unsigned long)(i2s->tx_buf->buffer + i2s->tx_buf->read), i2s->tx_period);
        ///< TODO：调用csi_dma_ch_start开启DMA通道发送数据
        i2s->priv = (void *)0U;
    }

    return write_len;
}

/**
  \brief  Transmits an amount of data to cache in blocking mode.
  \param[in]   i2s   operate handle.
  \param[in]   data  send data.
  \param[in]   size  receive data size.
  \param[in]   timeout  is the number of queries, not time
  \return      The num of data witch is send successful
*/
int32_t csi_i2s_send(csi_i2s_t *i2s, const void *data, uint32_t size)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    int32_t write_size = 0;
    uint8_t *send_data = (void *)data;

    if (i2s->tx_dma == NULL) {

        ///< TODO：清除中断
        ///< TODO：关闭i2s
        ///< TODO：设置i2s为发送模式
        ///< TODO：打开i2s
        ///< TODO：写数据寄存器发送数据，并把发送数据的大小写到write_size

    } else {
        while (1) {
            write_size += (int32_t)csi_ringbuf_in(i2s->tx_buf, (void *)(send_data + (uint32_t)write_size), (size - (uint32_t)write_size));

            if ((uint8_t *)i2s->priv) { ///< if dma is stop, then start it
                soc_dcache_clean_invalid_range((unsigned long)(i2s->tx_buf->buffer + i2s->tx_buf->read), i2s->tx_period);

                ///< TODO：调用csi_dma_ch_start开启DMA通道发送数据
                i2s->priv = (void *)0U;
            }

            if ((size - (uint32_t)write_size) <= 0U) {
                break;
            }
        }

        while (!csi_ringbuf_is_empty(i2s->tx_buf));
    }

    return write_size;
}

/**
  \brief Read data from the cache.
  \Using asynchronous receive, i2s writes the received data to the cache.
  \This function reads data from the cache, returns the number of successful reads,
  \and returns 0 if there is no data in the cache.
  \param[in]   i2s   operate handle.
  \param[in]   data  the buf save receive data.
  \param[in]   size  receive data size.
  \return      The size of data read successfully
*/
uint32_t csi_i2s_receive_async(csi_i2s_t *i2s, void *data, uint32_t size)
{
    CSI_PARAM_CHK(i2s, 0U);
    CSI_PARAM_CHK(data, 0U);
    uint32_t read_len;
    read_len = csi_ringbuf_out(i2s->rx_buf, (void *)data, size);
    return read_len;
}

/**
  \brief       start i2s pause asynchronous send
  \param[in]   i2s  operate handle.
  \return      error code
*/
csi_error_t csi_i2s_send_pause(csi_i2s_t *i2s)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    ///< TODO：关闭DMA通道
    i2s->state.writeable = 0U;
    return ret;
}

/**
  \brief       start i2s resume asynchronous send
  \param[in]   i2s  operate handle.
  \return      error code
*/
csi_error_t csi_i2s_send_resume(csi_i2s_t *i2s)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    soc_dcache_clean_invalid_range((unsigned long)(i2s->tx_buf->buffer + i2s->tx_buf->read), i2s->tx_period);
    ///< TODO：调用csi_dma_ch_start开启DMA通道发送数据

    i2s->state.writeable = 1U;
    return ret;
}

/**
  \brief       start i2s asynchronous send
  \param[in]   i2s  operate handle.
  \return      error code
*/
csi_error_t csi_i2s_send_start(csi_i2s_t *i2s)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    csi_dma_ch_config_t config;
    memset(&config, 0, sizeof(csi_dma_ch_config_t));
    csi_dma_ch_t *dma_ch = (csi_dma_ch_t *)i2s->tx_dma;

    ///< TODO：清除i2s中断
    ///< TODO：关闭i2s
    ///< TODO：设置i2s为发送模式
    ///< TODO：使能i2s发送DMA
    ///< TODO：设置DMA的触发级别为64


    config.src_inc = DMA_ADDR_INC;
    config.dst_inc = DMA_ADDR_CONSTANT;
    config.src_tw = DMA_DATA_WIDTH_32_BITS;
    config.dst_tw = DMA_DATA_WIDTH_32_BITS;
    config.trans_dir = DMA_MEM2PERH;
    config.half_int_en = 0U;
    config.handshake = i2s_tx_hs_num[i2s->dev.idx];

    ///< TODO：使能打开i2s
    memset(i2s->tx_buf->buffer, 0, i2s->tx_buf->size);
    ///< 配置DMA通道
    ret = csi_dma_ch_config(dma_ch, &config);
    soc_dcache_clean_invalid_range((unsigned long)(i2s->tx_buf->buffer + i2s->tx_buf->read), i2s->tx_period);
    ///< TODO：调用csi_dma_ch_start开启DMA通道，开始传输数据
    ///< TODO：清FIFO
    i2s->state.writeable = 1U;

    return ret;
}

/**
  \brief       start i2s asynchronous receive
  \param[in]   i2s  operate handle.
  \return      error code
*/
csi_error_t csi_i2s_receive_start(csi_i2s_t *i2s)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    csi_dma_ch_config_t config;
    memset(&config, 0, sizeof(csi_dma_ch_config_t));
    csi_dma_ch_t *dma_ch = (csi_dma_ch_t *)i2s->rx_dma;

    ///< TODO：关闭i2s
    ///< TODO：设置i2s为接收模式
    ///< TODO：使能i2s接收DMA
    ///< TODO：设置DMA的触发级别

    config.src_inc = DMA_ADDR_CONSTANT;
    config.dst_inc = DMA_ADDR_INC;
    config.src_tw = DMA_DATA_WIDTH_32_BITS;
    config.dst_tw = DMA_DATA_WIDTH_32_BITS;
    config.trans_dir = DMA_PERH2MEM;
    config.half_int_en = 0U;
    config.handshake = i2s_rx_hs_num[i2s->dev.idx];

    ///< TODO：使能打开i2s

    memset(i2s->rx_buf->buffer, 0, i2s->rx_buf->size);
    ///< 配置DMA通道
    ret = csi_dma_ch_config(dma_ch, &config);

    ///< TODO：获取接收FIFO中有多少数据
    ///< TODO：根据接收FIFO中的数据量读数据寄存器，清空接收FIFO

    soc_dcache_clean_invalid_range((unsigned long)(i2s->rx_buf->buffer + i2s->rx_buf->write), i2s->rx_period);
    ///< TODO：调用csi_dma_ch_start开启DMA通道，开始传输数据
    i2s->state.readable = 1U;
    return ret;
}

/**
  \brief       stop i2s asynchronous send
  \param[in]   i2s  operate handle.
*/
void csi_i2s_send_stop(csi_i2s_t *i2s)
{
    CSI_PARAM_CHK_NORETVAL(i2s);

    ///< 关闭DMA通道
    csi_dma_ch_stop(i2s->tx_dma);
    csi_ringbuf_reset(i2s->tx_buf);
    memset(i2s->tx_buf->buffer, 0, i2s->tx_buf->size);

    ///< TODO：等待发送FIFO为空

    ///< TODO：清FIFO
    i2s->state.writeable = 0U;
}

/**
  \brief       stop i2s asynchronous receive
  \param[in]   i2s  operate handle.
  \return      error code
*/
void csi_i2s_receive_stop(csi_i2s_t *i2s)
{
    CSI_PARAM_CHK_NORETVAL(i2s);
    ///< 关闭DMA通道
    csi_dma_ch_stop(i2s->rx_dma);
    csi_ringbuf_reset(i2s->rx_buf);
    memset(i2s->rx_buf->buffer, 0, i2s->rx_buf->size);
    ///< TODO ：清FIFO
    i2s->state.readable = 0U;
}

/**
  \brief       attach the callback handler to i2s
  \param[in]   i2s  operate handle.
  \param[in]   cb    callback function
  \param[in]   arg   user can define it by himself as callback's param
  \return      error code
*/
csi_error_t csi_i2s_attach_callback(csi_i2s_t *i2s, void *callback, void *arg)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    i2s->callback = callback;
    i2s->arg = arg;
    return ret;
}

/**
  \brief       detach the callback handler
  \param[in]   i2s  operate handle.
  \return      none
*/
void csi_i2s_detach_callback(csi_i2s_t *i2s)
{
    CSI_PARAM_CHK_NORETVAL(i2s);
    i2s->callback = NULL;
    i2s->arg = NULL;
}

/**
  \brief       Get i2s status.
  \param[in]   i2s i2s handle to operate.
  \param[out]  state i2s state.
  \return      i2s error code
*/
csi_error_t csi_i2s_get_state(csi_i2s_t *i2s, csi_state_t *state)
{
    CSI_PARAM_CHK(i2s, CSI_ERROR);
    CSI_PARAM_CHK(state, CSI_ERROR);
    *state = i2s->state;
    return CSI_OK;
}

#ifdef CONFIG_PM
csi_error_t csi_i2s_enable_pm(csi_i2s_t *i2s)
{
    return CSI_UNSUPPORTED;
}

void csi_i2s_disable_pm(csi_i2s_t *i2s)
{

}
#endif
