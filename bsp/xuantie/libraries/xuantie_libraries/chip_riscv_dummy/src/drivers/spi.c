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
 * @file     dw_spi.c
 * @brief
 * @version
 * @date     2020-02-11
 ******************************************************************************/

#include <string.h>

#include <drv/spi.h>
#include <drv/irq.h>
#include <drv/tick.h>
#include <drv/porting.h>

///< TODO：SPI_CTRLR0_TMOD_Msk需要根据实际情况进行设置
#define SPI_CTRLR0_TMOD_Msk  3U << 8U ///< 设置SPI模式的寄存器对应的位的掩码
///< TODO：SPI_CTRLR0_TMOD_RX和SPI_CTRLR0_TMOD_TX需要根据实际情况进行设置
#define SPI_CTRLR0_TMOD_RX   2U << 8U ///< SPI发送模式
#define SPI_CTRLR0_TMOD_TX   1U << 8U ///< SPI发送模式

static csi_error_t dw_spi_send_intr(csi_spi_t *spi, const void *data, uint32_t size);
static csi_error_t dw_spi_receive_intr(csi_spi_t *spi, void *data, uint32_t size);
static csi_error_t dw_spi_send_receive_intr(csi_spi_t *spi, const void *data_out, void *data_in, uint32_t num);

static void dw_spi_irqhandler(void *args)
{

    ///< TODO：获取SPI中断的状态

    ///< TODO：根据SPI中断的状态进行接收数据的处理,在接收完成后关闭中断；调用用户回调函数

    ///< TODO：根据SPI中断的状态进行关闭中断，发送数据的处理；调用用户回调函数

    ///< TODO：根据SPI中断的状态进行异常中断的处理，并清除中断，调用用户回调函数

}

static void dw_spi_dma_event_cb(csi_dma_ch_t *dma, csi_dma_event_t event, void *arg)
{
    csi_spi_t *spi = (csi_spi_t *)dma->parent;
    uint32_t mode = 0U;

    ///< TODO：获取SPI传输数据的模式mode：发送模式/接收模式/发送&接收模式

    if (event == DMA_EVENT_TRANSFER_DONE) {
        /* process end of transmit */
        if ((spi->tx_dma != NULL) && (spi->tx_dma->ch_id == dma->ch_id)) {
            ///< 关闭DMA通道
            csi_dma_ch_stop(dma);

            ///< TODO：关闭DMA发送使能

            ///< TODO：如果SPI的BUSY在一定时间内处于空闲状态下
                spi->state.writeable = 1U;
                spi->tx_size = 0U;

                if ((mode & SPI_CTRLR0_TMOD_Msk) == SPI_CTRLR0_TMOD_TX) {
                    ///< TODO：设置发送FIFO的触发级别为0

                    if (spi->callback) {
                        ///< 调用用户回调函数
                        spi->callback(spi, SPI_EVENT_SEND_COMPLETE, spi->arg);
                    }
                } else {
                    if (spi->state.readable == 1U) {
                        ///< 调用用户回调函数
                        spi->callback(spi, SPI_EVENT_SEND_RECEIVE_COMPLETE, spi->arg);
                    }
                }
        } else if ((spi->rx_dma != NULL) && (spi->rx_dma->ch_id == dma->ch_id)) {
            ///< 关闭DMA通道
            ///< TODO：关闭SPI接收DMA
            ///< TODO：设置接收FIFO的触发级别为0
            ///< TODO：设置接收数据的大小为0

            spi->state.readable = 1U;
            spi->rx_size = 0U;

            if ((mode & SPI_CTRLR0_TMOD_Msk) == SPI_CTRLR0_TMOD_RX) {
                if (spi->callback) {
                    ///< 调用用户回调函数
                    spi->callback(spi, SPI_EVENT_RECEIVE_COMPLETE, spi->arg);
                }
            } else {
                if (spi->state.writeable == 1U) {
                    ///< 调用用户回调函数
                    spi->callback(spi, SPI_EVENT_SEND_RECEIVE_COMPLETE, spi->arg);
                }
            }
        }
    }
}

csi_error_t csi_spi_init(csi_spi_t *spi, uint32_t idx)
{
    CSI_PARAM_CHK(spi, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    ///< 获取中断号、基地址等相关信息
    if (target_get(DEV_DW_SPI_TAG, idx, &spi->dev) != CSI_OK) {
        ret = CSI_ERROR;
    } else {
        spi->state.writeable = 1U;
        spi->state.readable  = 1U;
        spi->state.error     = 0U;
        spi->send            = NULL;
        spi->receive         = NULL;
        spi->send_receive    = NULL;
        spi->rx_dma          = NULL;
        spi->tx_dma          = NULL;
        spi->rx_data         = NULL;
        spi->tx_data         = NULL;
        spi->callback        = NULL;
        spi->arg             = NULL;
        spi->priv            = 0;

        ///< TODO：关闭SPI所有的中断
        ///< TODO：关闭SPI

    }

    return ret;
}

void csi_spi_uninit(csi_spi_t *spi)
{
    CSI_PARAM_CHK_NORETVAL(spi);

    ///< TODO：复位SPI使用到的寄存器

    ///< 禁止中断控制器对应的中断，注销中断服务函数
    csi_irq_disable((uint32_t)spi->dev.irq_num);
    csi_irq_detach((uint32_t)spi->dev.irq_num);
}

csi_error_t csi_spi_attach_callback(csi_spi_t *spi, void *callback, void *arg)
{
    CSI_PARAM_CHK(spi, CSI_ERROR);
    CSI_PARAM_CHK(callback, CSI_ERROR);

    ///< 注册用户回调函数
    spi->callback     = callback;
    spi->arg          = arg;
    spi->send         = NULL;
    spi->receive      = NULL;
    spi->send_receive = NULL;

    return CSI_OK;
}


void csi_spi_detach_callback(csi_spi_t *spi)
{
    CSI_PARAM_CHK_NORETVAL(spi);

    ///< 注销用户回调函数
    spi->callback     = NULL;
    spi->arg          = NULL;
    spi->send         = NULL;
    spi->receive      = NULL;
    spi->send_receive = NULL;
}


csi_error_t csi_spi_mode(csi_spi_t *spi, csi_spi_mode_t mode)
{
    CSI_PARAM_CHK(spi, CSI_ERROR);

    csi_error_t   ret = CSI_OK;

    switch (mode) {
        case SPI_MASTER:
            ///< TODO：设置SPI为主机模式
            break;

        case SPI_SLAVE:
            ///< TODO：设置SPI为从机模式
            break;

        default:
            ret = CSI_ERROR;
            break;
    }

    return ret;
}

csi_error_t csi_spi_cp_format(csi_spi_t *spi, csi_spi_cp_format_t format)
{
    CSI_PARAM_CHK(spi, CSI_ERROR);

    csi_error_t   ret = CSI_OK;

    switch (format) {
        case SPI_FORMAT_CPOL0_CPHA0:
            ///< TODO：设置SPI时钟的极性
            ///< TODO：设置SPI时钟的相位
            break;

        case SPI_FORMAT_CPOL0_CPHA1:
            ///< TODO：设置SPI时钟的极性
            ///< TODO：设置SPI时钟的相位
            break;

        case SPI_FORMAT_CPOL1_CPHA0:
            ///< TODO：设置SPI时钟的极性
            ///< TODO：设置SPI时钟的相位
            break;

        case SPI_FORMAT_CPOL1_CPHA1:
            ///< TODO：设置SPI时钟的极性
            ///< TODO：设置SPI时钟的相位
            break;

        default:
            ret = CSI_ERROR;
            break;
    }

    return ret;
}

uint32_t csi_spi_baud(csi_spi_t *spi, uint32_t baud)
{
    CSI_PARAM_CHK(spi,  CSI_ERROR);
    CSI_PARAM_CHK(baud, CSI_ERROR);

    uint32_t freq = 0U;

    ///< TODO：根据SPI工作频率设置传输频率（baud）
    ///< TODO：获取SPI时钟的分频div
    ///< TODO：根据分频div获取SPI实际传输的频率

    return freq;

}

csi_error_t csi_spi_frame_len(csi_spi_t *spi, csi_spi_frame_len_t length)
{
    CSI_PARAM_CHK(spi, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    if ((length < SPI_FRAME_LEN_4) || (length > SPI_FRAME_LEN_16)) {
        ret = CSI_ERROR;
    } else {
        ///< TODO：设置SPI数据帧的大小
    }

    return ret;
}

int32_t csi_spi_send(csi_spi_t *spi, const void *data, uint32_t size, uint32_t timeout)
{
    CSI_PARAM_CHK(spi,  CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    int32_t  ret   = CSI_OK;

    if ((spi->state.writeable == 0U) || (spi->state.readable == 0U)) {
        ret = CSI_BUSY;
        return ret;
    }

    spi->state.writeable = 0U;

    ///< TODO：关闭SPI
    ///< TODO：设置SPI为发送模式
    ///< TODO：设置SPI发送FIFO的阈值
    ///< TODO：打开SPI


    ///< TODO：轮询发送数据，超时则超时退出
    ///< TODO：发送完成后在一定时间内判断发送FIFO是否为空，空则退出，不空则超时退出
    ///< TODO：发送完成后在一定时间内判断SPI BUSY是否为0，0则退出，不为0则超时退出

    spi->state.writeable = 1U;

    return ret;
}

csi_error_t csi_spi_send_async(csi_spi_t *spi, const void *data, uint32_t size)
{
    CSI_PARAM_CHK(spi,  CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    if ((spi->state.writeable == 0U) || (spi->state.readable == 0U)) {
        ret = CSI_BUSY;
    }

    if ((ret == CSI_OK) && (spi->callback != NULL)) {
        if (spi->send) {
            spi->state.writeable = 0U;
            ///< TODO：调用spi->send发送数据
        } else {
            spi->state.writeable = 0U;
            ///< 注册SPI的中断服务函数，使能中断控制器对应的中断
            csi_irq_attach((uint32_t)spi->dev.irq_num, &dw_spi_irqhandler, &spi->dev);
            csi_irq_enable((uint32_t)spi->dev.irq_num);
            ///< TODO：调用dw_spi_send_intr中断模式发送数据
        }
    } else {
        ret = CSI_ERROR;
    }

    return ret;
}

static csi_error_t dw_spi_send_intr(csi_spi_t *spi, const void *data, uint32_t size)
{
    csi_error_t ret = CSI_OK;
    spi->tx_data = (uint8_t *)data;

    ///< TODO：关闭SPI
    ///< TODO：设置SPI为发送模式
    ///< TODO：设置SPI发送FIFO的阈值
    ///< TODO：打开SPI
    ///< TODO：打开SPI发送FIFO空中断

    return ret;
}

static csi_error_t dw_spi_send_dma(csi_spi_t *spi, const void *data, uint32_t size)
{
    CSI_PARAM_CHK(spi,  CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    csi_dma_ch_config_t config;
    csi_dma_ch_t        *dma_ch;
    csi_error_t         ret = CSI_OK;

    dma_ch   = (csi_dma_ch_t *)spi->tx_dma;
    spi->tx_data = (uint8_t *)data;
    memset(&config, 0, sizeof(csi_dma_ch_config_t));

    ///< TODO：配置DMA的config.src_tw和config.dst_tw
    config.src_inc = DMA_ADDR_INC;
    config.dst_inc = DMA_ADDR_CONSTANT;
    config.trans_dir = DMA_MEM2PERH;
    ///< TODO：配置SPI的硬件握手号config.handshake

    ///< 配置DMA通道
    csi_dma_ch_config(dma_ch, &config);

    ///< TODO：关闭SPI
    ///< TODO：设置SPI为发送模式
    ///< TODO：使能SPI发送DMA

    soc_dcache_clean_invalid_range((unsigned long)spi->tx_data, size);
    ///< TODO：调用csi_dma_ch_start打开SPI发送数据的DMA通道

    ///< TODO：打开SPI

    return ret;
}

int32_t csi_spi_receive(csi_spi_t *spi, void *data, uint32_t size, uint32_t timeout)
{
    CSI_PARAM_CHK(spi,  CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    int32_t  ret = CSI_OK;

    if ((spi->state.writeable == 0U) || (spi->state.readable == 0U)) {
        ret = CSI_BUSY;
        return ret;
    }

    spi->state.readable = 0U;
    spi->rx_data = (uint8_t *)data;

    ///< 关闭SPI
    ///< 设置SPI为接收模式
    ///< 设置SPI接收数据的大小
    ///< 打开SPI

    ///< TODO：轮询接收数据，超时则超时退出
    ///< TODO：接收完成后再一定时间内判断SPI BUSY是否为0，为0则退出，不为0则超时退出

    spi->state.readable = 1U;

    return ret;
}


csi_error_t csi_spi_receive_async(csi_spi_t *spi, void *data, uint32_t size)
{
    CSI_PARAM_CHK(spi, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    if ((spi->state.writeable == 0U) || (spi->state.readable == 0U)) {
        ret = CSI_BUSY;
    } else {

        if ((ret == CSI_OK) && (spi->callback != NULL)) {
            if (spi->receive) {
                spi->state.readable = 0U;
                ret = spi->receive(spi, data, size);
            } else {
                spi->state.readable = 0U;
                ///< 注册SPI的中断服务函数，使能中断控制器对应的中断
                csi_irq_attach((uint32_t)spi->dev.irq_num, &dw_spi_irqhandler, &spi->dev);
                csi_irq_enable((uint32_t)spi->dev.irq_num);
                ///< 调用dw_spi_receive_intr中断模式接收数据
                ret = dw_spi_receive_intr(spi, data, size);
            }
        } else {
            ret = CSI_ERROR;
        }
    }

    return ret;
}

static csi_error_t dw_spi_receive_intr(csi_spi_t *spi, void *data, uint32_t size)
{
    csi_error_t ret = CSI_OK;

    spi->rx_data = (uint8_t *)data;

    ///< TODO：关闭SPI
    ///< TODO：设置SPI为接收模式
    ///< TODO：设置SPI接收数据的大小
    ///< TODO：设置SPI接收FIFO的阈值
    ///< TODO：打开SPI
    ///< TODO：打开SPI接收FIFO满中断

    ///< TODO：如果SPI工作在主机模式下
        ///< TODO：写SPI数据寄存器为0

    return ret;
}

static csi_error_t dw_spi_receive_dma(csi_spi_t *spi, void *data, uint32_t size)
{
    csi_dma_ch_config_t config;
    csi_dma_ch_t        *dma_ch;
    csi_error_t         ret = CSI_OK;

    dma_ch   = (csi_dma_ch_t *)spi->rx_dma;
    spi->rx_data = (uint8_t *)data;
    memset(&config, 0, sizeof(csi_dma_ch_config_t));

    ///< TODO：配置DMA的config.src_tw和config.dst_tw
    config.src_inc = DMA_ADDR_CONSTANT;
    config.dst_inc = DMA_ADDR_INC;
    config.trans_dir = DMA_PERH2MEM;
    ///< TODO：配置SPI的硬件握手号config.handshake

    ///< 配置DMA通道
    csi_dma_ch_config(dma_ch, &config);

    ///< TODO：关闭SPI
    ///< TODO：设置SPI为接收模式
    ///< TODO：设置SPI接收数据的大小
    ///< TODO：设置SPI接收FIFO的触发级别
    ///< TODO：使能SPI接收DMA

    soc_dcache_clean_invalid_range((unsigned long)spi->rx_data, size);
    ///< TODO：调用csi_dma_ch_start打开SPI接收数据的DMA通道

    ///< TODO：打开SPI

    ///< TODO：如果SPI工作在主机模式下
        ///< TODO：写SPI数据寄存器为0

    return ret;
}

int32_t csi_spi_send_receive(csi_spi_t *spi, const void *data_out, void *data_in, uint32_t size, uint32_t timeout)
{
    CSI_PARAM_CHK(spi,      CSI_ERROR);
    CSI_PARAM_CHK(data_out, CSI_ERROR);
    CSI_PARAM_CHK(data_in,  CSI_ERROR);
    CSI_PARAM_CHK(size,     CSI_ERROR);

    int32_t  ret   = CSI_OK;

    if ((spi->state.writeable == 0U) || (spi->state.readable == 0U)) {
        ret = CSI_BUSY;
        return ret;
    }

    spi->state.writeable = 0U;
    spi->state.readable  = 0U;

    ///< TODO：关闭SPI
    ///< TODO：设置SPI为发送和接收模式
    ///< TODO：设置SPI发送FIFO的阈值
    ///< TODO：设置SPI接收FIFO的阈值
    ///< TODO：打开SPI

    ///< TODO：轮询发送数据
    ///< TODO：轮询接收数据
    ///< TODO：超时退出
    ///< TODO：在一定时间内判断SPI的BUSY是否为0，为0退出，否则超时退出

    spi->state.writeable = 1U;
    spi->state.readable  = 1U;

    return ret;
}


csi_error_t csi_spi_send_receive_async(csi_spi_t *spi, const void *data_out, void *data_in, uint32_t size)
{
    CSI_PARAM_CHK(spi, CSI_ERROR);
    CSI_PARAM_CHK(data_out, CSI_ERROR);
    CSI_PARAM_CHK(data_in, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    if ((spi->state.writeable == 0U) || (spi->state.readable == 0U)) {
        ret = CSI_BUSY;
    }

    if ((ret == CSI_OK) && (spi->callback != NULL)) {
        if (spi->send_receive) {
            spi->state.readable  = 0U;
            spi->state.writeable = 0U;
            ret = spi->send_receive(spi, data_out, data_in, size);
        } else {
            spi->state.readable  = 0U;
            spi->state.writeable = 0U;
            ///< 注册SPI的中断服务函数，使能中断控制器对应的中断
            csi_irq_attach((uint32_t)spi->dev.irq_num, &dw_spi_irqhandler, &spi->dev);
            csi_irq_enable((uint32_t)spi->dev.irq_num);
            ///< 调用dw_spi_send_receive_intr中断模式发送接收数据
            ret = dw_spi_send_receive_intr(spi, data_out, data_in, size);
        }
    } else {
        ret = CSI_ERROR;
    }

    return ret;
}

static csi_error_t dw_spi_send_receive_intr(csi_spi_t *spi, const void *data_out, void *data_in, uint32_t size)
{
    csi_error_t ret = CSI_OK;

    spi->tx_data = (uint8_t *)data_out;
    spi->rx_data = (uint8_t *)data_in;

    ///< TODO：关闭SPI
    ///< TODO：设置SPI为发送接收模式
    ///< TODO：设置接收数据的大小
    ///< TODO：设置发送FIFO的阈值
    ///< TODO：设置接收FIFO的阈值
    ///< TODO：打开SPI
    ///< TODO：打开SPI接收FIFO满中断
    ///< TODO：打开SPI发送FIFO空中断

    return ret;
}

static csi_error_t dw_spi_send_receive_dma(csi_spi_t *spi, const void *data_out, void *data_in, uint32_t size)
{
    csi_dma_ch_config_t config;
    csi_dma_ch_t        *dma_ch;
    csi_error_t         ret = CSI_OK;
    spi->tx_data = (uint8_t *)data_out;
    memset(&config, 0, sizeof(csi_dma_ch_config_t));

    ///< TODO：配置DMA的config.src_tw和config.dst_tw

    spi->rx_data = (uint8_t *)data_in;

    dma_ch   = (csi_dma_ch_t *)spi->tx_dma;
    config.src_inc = DMA_ADDR_INC;
    config.dst_inc = DMA_ADDR_CONSTANT;
    config.trans_dir = DMA_MEM2PERH;
    ///< TODO：配置SPI的硬件握手号config.handshake

    ///< 配置发送DMA通道
    csi_dma_ch_config(dma_ch, &config);

    dma_ch   = (csi_dma_ch_t *)spi->rx_dma;
    config.src_inc = DMA_ADDR_CONSTANT;
    config.dst_inc = DMA_ADDR_INC;
    config.trans_dir = DMA_PERH2MEM;
    ///< TODO：配置SPI的硬件握手号config.handshake

    ///< 配置接收DMA通道
    csi_dma_ch_config(dma_ch, &config);

    ///< TODO：关闭SPI
    ///< TODO：设置SPI为发送接收模式
    ///< TODO：设置SPI接收数据的大小
    ///< TODO：设置SPI接收数据FIFO的触发级别
    ///< TODO：使能SPI接收DMA
    ///< TODO：使能SPI发送DMA

    ///< 打开发送接收的DMA通道

    soc_dcache_clean_invalid_range((unsigned long)spi->tx_data, size);
    soc_dcache_clean_invalid_range((unsigned long)spi->rx_data, size);
    ///< TODO：调用csi_dma_ch_start打开SPI接收数据的DMA通道
    ///< TODO：调用csi_dma_ch_start打开SPI发送数据的DMA通道

    ///< TODO：打开SPI
    return ret;
}

csi_error_t csi_spi_get_state(csi_spi_t *spi, csi_state_t *state)
{
    CSI_PARAM_CHK(spi, CSI_ERROR);
    CSI_PARAM_CHK(state, CSI_ERROR);

    *state = spi->state;
    return CSI_OK;
}

csi_error_t csi_spi_link_dma(csi_spi_t *spi, csi_dma_ch_t *tx_dma, csi_dma_ch_t *rx_dma)
{
    CSI_PARAM_CHK(spi, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    if (tx_dma != NULL) {
        tx_dma->parent = spi;
        ///< 申请DMA通道
        ret = csi_dma_ch_alloc(tx_dma, -1, -1);

        if (ret == CSI_OK) {
            ///< 注册DMA传输完成中断回调服务函数
            csi_dma_ch_attach_callback(tx_dma, dw_spi_dma_event_cb, NULL);
            spi->tx_dma = tx_dma;
            spi->send = dw_spi_send_dma;
        } else {
            tx_dma->parent = NULL;
        }
    } else {
        if (spi->tx_dma) {
            ///< 注销DMA传输完成中断回调服务函数，释放DMA通道
            csi_dma_ch_detach_callback(spi->tx_dma);
            csi_dma_ch_free(spi->tx_dma);
            spi->tx_dma = NULL;
        }

        spi->send = NULL;
    }

    if (ret == CSI_OK) {
        if (rx_dma != NULL) {
            rx_dma->parent = spi;
            ///< 申请DMA通道
            ret = csi_dma_ch_alloc(rx_dma, -1, -1);

            if (ret == CSI_OK) {
                ///< 注册DMA传输完成中断回调服务函数
                csi_dma_ch_attach_callback(rx_dma, dw_spi_dma_event_cb, NULL);
                spi->rx_dma = rx_dma;
                ///< 调用DMA接收函数开启DMA的接收
                spi->receive = dw_spi_receive_dma;
            } else {
                rx_dma->parent = NULL;
            }
        } else {
            if (spi->rx_dma) {
                ///< 注销DMA传输完成中断回调服务函数，释放DMA通道
                csi_dma_ch_detach_callback(spi->rx_dma);
                csi_dma_ch_free(spi->rx_dma);
                spi->rx_dma = NULL;
            }

            spi->receive = NULL;
        }
    }


    if (ret == CSI_OK) {
        if ((tx_dma != NULL) && (rx_dma != NULL)) {
            ///< 调用DMA发送接收函数开启DMA的发送接收
            spi->send_receive =  dw_spi_send_receive_dma;
        } else {
            spi->send_receive = NULL;
        }
    }

    return ret;
}

void csi_spi_select_slave(csi_spi_t *spi, uint32_t slave_num)
{
    CSI_PARAM_CHK_NORETVAL(spi);

    ///< TODO：使能SPI的从机
}

#ifdef CONFIG_PM
csi_error_t dw_spi_pm_action(csi_dev_t *dev, csi_pm_dev_action_t action)
{
    CSI_PARAM_CHK(dev, CSI_ERROR);

    csi_error_t ret = CSI_OK;
    csi_pm_dev_t *pm_dev = &dev->pm_dev;

    switch (action) {
        case PM_DEV_SUSPEND:
            ///< TODO：恢复SPI寄存器
            break;

        case PM_DEV_RESUME:
            ///< TODO：保存SPI寄存器
            break;

        default:
            ret = CSI_ERROR;
            break;
    }

    return ret;
}

csi_error_t csi_spi_enable_pm(csi_spi_t *spi)
{
    ///< TODO：注册WDT低功耗处理函数dw_spi_pm_action
}

void csi_spi_disable_pm(csi_spi_t *spi)
{
    csi_pm_dev_unregister(&spi->dev);
}
#endif
