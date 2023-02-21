/**
 * @file hal_i2s.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "hal_i2s.h"
#include "hal_clock.h"
#include "hal_dma.h"
#include "bl808_i2s.h"
#include "bl808_glb.h"
#include "i2s_config.h"

static i2s_device_t i2sx_device[I2S_MAX_INDEX] = {
#ifdef BSP_USING_I2S0
    I2S0_CONFIG,
#endif
};

int i2s_open(struct device *dev, uint16_t oflag)
{
    i2s_device_t *i2s_device = (i2s_device_t *)dev;
    I2S_CFG_Type i2sCfg = { 0 };
    I2S_FifoCfg_Type fifoCfg = { 0 };

    /* todo unify clock configuretion */
    // GLB_Power_On_XTAL_And_PLL_CLK(GLB_XTAL_40M, GLB_PLL_AUPLL);
    if (i2s_device->sampl_freq_hz == 44100) {
        GLB_Config_AUDIO_PLL(GLB_XTAL_40M, audioPllCfg_451P584M);
    }

    i2sCfg.audioFreqHz = 24576000;

    i2sCfg.sampleFreqHz = i2s_device->sampl_freq_hz;

    /*!< default I2S msb first */
    i2sCfg.endianType = I2S_DATA_ENDIAN;

    /* Config the I2S type */
    switch (i2s_device->interface_mode) {
        case I2S_MODE_STD:
            i2sCfg.modeType = I2S_MODE_I2S_LEFT;
            i2sCfg.fsMode = I2S_FS_MODE_EVEN;
            i2sCfg.dataOffset = 1;
            break;

        case I2S_MODE_LEFT:
            i2sCfg.modeType = I2S_MODE_I2S_LEFT;
            i2sCfg.fsMode = I2S_FS_MODE_EVEN;
            i2sCfg.dataOffset = 0;
            break;

        case I2S_MODE_RIGHT:
            i2sCfg.modeType = I2S_MODE_I2S_RIGHT;
            i2sCfg.fsMode = I2S_FS_MODE_EVEN;
            i2sCfg.dataOffset = 0;
            break;

        case I2S_MODE_DSP_A:
            i2sCfg.modeType = I2S_MODE_I2S_DSP;
            i2sCfg.fsMode = I2S_FS_MODE_1T;
            i2sCfg.dataOffset = 1;
            break;

        case I2S_MODE_DSP_B:
            i2sCfg.modeType = I2S_MODE_I2S_DSP;
            i2sCfg.fsMode = I2S_FS_MODE_1T;
            i2sCfg.dataOffset = 0;
            break;

        default:
            return ERROR;
            break;
    }

    /* Config the frame/data Size */
    switch (i2s_device->frame_size) {
        case I2S_FRAME_LEN_8:
            i2sCfg.frameSize = I2S_SIZE_FRAME_8;
            break;

        case I2S_FRAME_LEN_16:
            i2sCfg.frameSize = I2S_SIZE_FRAME_16;
            break;

        case I2S_FRAME_LEN_24:
            i2sCfg.frameSize = I2S_SIZE_FRAME_24;
            break;

        case I2S_FRAME_LEN_32:
            i2sCfg.frameSize = I2S_SIZE_FRAME_32;
            break;

        default:
            return ERROR;
            break;
    }

    switch (i2s_device->data_size) {
        case I2S_DATA_LEN_8:
            i2sCfg.dataSize = I2S_SIZE_DATA_8;
            break;

        case I2S_DATA_LEN_16:
            i2sCfg.dataSize = I2S_SIZE_DATA_16;
            break;

        case I2S_DATA_LEN_24:
            i2sCfg.dataSize = I2S_SIZE_DATA_24;
            break;

        case I2S_DATA_LEN_32:
            i2sCfg.dataSize = I2S_SIZE_DATA_32;
            break;

        default:
            return ERROR;
            break;
    }

    fifoCfg.lRMerge = DISABLE;
    fifoCfg.frameDataExchange = DISABLE;

    /* Config the Channel number */
    switch (i2s_device->channel_num) {
        case I2S_FS_CHANNELS_NUM_MONO:
            i2sCfg.monoMode = ENABLE;
            i2sCfg.fsChannel = I2S_FS_CHANNELS_2;
            i2sCfg.monoModeChannel = I2S_MONO_CHANNEL;
            break;

        case I2S_FS_CHANNELS_NUM_2:
            i2sCfg.monoMode = DISABLE;
            i2sCfg.fsChannel = I2S_FS_CHANNELS_2;

            if (i2s_device->data_size == I2S_DATA_LEN_8 || i2s_device->data_size == I2S_DATA_LEN_16) {
                fifoCfg.lRMerge = ENABLE;
                fifoCfg.frameDataExchange = I2S_LR_EXCHANGE;
            }

            break;

        case I2S_FS_CHANNELS_NUM_3:
            if ((i2s_device->interface_mode != I2S_MODE_DSP_A) && (i2s_device->interface_mode != I2S_MODE_DSP_B)) {
                return ERROR;
            }

            i2sCfg.monoMode = DISABLE;
            i2sCfg.fsChannel = I2S_FS_CHANNELS_3;
            break;

        case I2S_FS_CHANNELS_NUM_4:
            if ((i2s_device->interface_mode != I2S_MODE_DSP_A) && (i2s_device->interface_mode != I2S_MODE_DSP_B)) {
                return ERROR;
            }

            i2sCfg.monoMode = DISABLE;
            i2sCfg.fsChannel = I2S_FS_CHANNELS_4;

        default:
            return ERROR;
            break;
    }

    /* Config the bclk/fs invert */
    i2sCfg.bclkInvert = I2S_BCLK_INVERT;
    i2sCfg.fsInvert = I2S_FS_INVERT;

    if (oflag & DEVICE_OFLAG_INT_TX) {
    }

    if (oflag & DEVICE_OFLAG_INT_RX) {
    }

    fifoCfg.txfifoDmaEnable = (oflag & DEVICE_OFLAG_DMA_TX) ? ENABLE : DISABLE;
    fifoCfg.rxfifoDmaEnable = (oflag & DEVICE_OFLAG_DMA_RX) ? ENABLE : DISABLE;
    fifoCfg.txFifoLevel = i2s_device->fifo_threshold;
    fifoCfg.rxFifoLevel = i2s_device->fifo_threshold;

    /* I2S Init */
    I2S_Disable(i2s_device->id);
    I2S_Init(i2s_device->id, &i2sCfg);
    I2S_FifoConfig(i2s_device->id, &fifoCfg);

    if (i2s_device->iis_mode == I2S_MODE_MASTER)
        I2S_Enable(i2s_device->id, I2S_ROLE_MASTER);
    else if (i2s_device->iis_mode == I2S_MODE_SLAVE)
        I2S_Enable(i2s_device->id, I2S_ROLE_SLAVE);
    return 0;
}

int i2s_close(struct device *dev)
{
    i2s_device_t *i2s_device = (i2s_device_t *)dev;
    I2S_Disable(i2s_device->id);
    return 0;
}

int i2s_control(struct device *dev, int cmd, void *args)
{
    i2s_device_t *i2s_device = (i2s_device_t *)dev;

    switch (cmd) {
        case DEVICE_CTRL_SET_INT:
            break;

        case DEVICE_CTRL_CLR_INT:

            break;

        case DEVICE_CTRL_GET_INT:

            break;

        case DEVICE_CTRL_RESUME:

            break;

        case DEVICE_CTRL_SUSPEND:

            break;

        case DEVICE_CTRL_CONFIG:

            break;

        case DEVICE_CTRL_ATTACH_TX_DMA:
            i2s_device->tx_dma = (struct device *)args;
            break;

        case DEVICE_CTRL_ATTACH_RX_DMA:
            i2s_device->rx_dma = (struct device *)args;
            break;

        case DEVICE_CTRL_GET_CONFIG:
            switch ((uint32_t)(size_t)args) {
                case I2S_GET_TX_FIFO_CMD:
                    return I2S_GetTxFIFO_AvlCnt(i2s_device->id);

                case I2S_GET_RX_FIFO_CMD:
                    return I2S_GetRxFIFO_AvlCnt(i2s_device->id);

                default:
                    break;
            }

            break;
        default:
            return ERROR;
            break;
    }

    return SUCCESS;
}

int i2s_write(struct device *dev, uint32_t pos, const void *buffer, uint32_t size)
{
    i2s_device_t *i2s_device = (i2s_device_t *)dev;

    if (dev->oflag & DEVICE_OFLAG_DMA_TX) {
        struct device *dma_ch = (struct device *)i2s_device->tx_dma;

        if (!dma_ch) {
            return -1;
        }

        if (i2s_device->id == 0) {
            dma_reload(dma_ch, (uint32_t)(uintptr_t)buffer, (uint32_t)DMA_ADDR_I2S_TDR, size);
            dma_channel_start(dma_ch);
        } else if (i2s_device->id == 1) {
            dma_reload(dma_ch, (uint32_t)(uintptr_t)buffer, (uint32_t)DMA_ADDR_I2S_TDR, size);
            dma_channel_start(dma_ch);
        }

        return 0;
    } else {
        return 0;
    }
}

int i2s_read(struct device *dev, uint32_t pos, void *buffer, uint32_t size)
{
    i2s_device_t *i2s_device = (i2s_device_t *)dev;

    if (dev->oflag & DEVICE_OFLAG_DMA_RX) {
        struct device *dma_ch = (struct device *)i2s_device->rx_dma;

        if (!dma_ch) {
            return -1;
        }

        if (i2s_device->id == 0) {
            dma_reload(dma_ch, (uint32_t)DMA_ADDR_I2S_RDR, (uint32_t)(uintptr_t)buffer, size);
            dma_channel_start(dma_ch);
        } else if (i2s_device->id == 1) {
            dma_reload(dma_ch, (uint32_t)DMA_ADDR_I2S_RDR, (uint32_t)(uintptr_t)buffer, size);
            dma_channel_start(dma_ch);
        }

        return 0;
    } else {
        return 0;
    }
}

int i2s_register(enum i2s_index_type index, const char *name)
{
    struct device *dev;

    if (I2S_MAX_INDEX == 0) {
        return -DEVICE_EINVAL;
    }

    dev = &(i2sx_device[index].parent);

    dev->open = i2s_open;
    dev->close = i2s_close;
    dev->control = i2s_control;
    dev->write = i2s_write;
    dev->read = i2s_read;

    dev->type = DEVICE_CLASS_I2S;
    dev->handle = NULL;

    return device_register(dev, name);
}

void i2s_isr(i2s_device_t *handle)
{
    return;
}

void I2S_IRQ(void)
{
    i2s_isr(&i2sx_device[0]);
}
