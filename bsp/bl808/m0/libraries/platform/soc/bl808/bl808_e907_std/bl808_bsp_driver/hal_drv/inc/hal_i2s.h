/**
 * @file hal_i2s.h
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
#ifndef __HAL_I2S__H__
#define __HAL_I2S__H__

#include "hal_common.h"
#include "drv_device.h"
#include "bl808_config.h"

#define I2S_GET_TX_FIFO_CMD           0x10
#define I2S_GET_RX_FIFO_CMD           0x11
#define DEVICE_CTRL_I2S_ATTACH_TX_DMA 0x12
#define DEVICE_CTRL_I2S_ATTACH_RX_DMA 0x13

enum i2s_index_type {
#ifdef BSP_USING_I2S0
    I2S0_INDEX,
#endif
    I2S_MAX_INDEX
};

#define I2S_DEFAULT_RTO_TIMEOUT 15

/*!
 *  @brief    I2S mode type settings
 *
 *  This enumeration defines the I2S mode type
 */
typedef enum {
    I2S_MODE_STD,   /*!< I2S STD Mode */
    I2S_MODE_LEFT,  /*!< Left-Justified Mode */
    I2S_MODE_RIGHT, /*!< Right-Justified Mode */
    I2S_MODE_DSP_A, /*!< DSP/PCM Mode A*/
    I2S_MODE_DSP_B, /*!< DSP/PCM Mode B*/
} interface_mode_t;

/*!
 *  @brief    I2S frame size settings
 *
 *  This enumeration defines the frame size type
 */
typedef enum {
    I2S_FRAME_LEN_8 = 1,  /*!< I2S frame size 8 bits */
    I2S_FRAME_LEN_16 = 2, /*!< I2S frame size 16 bits */
    I2S_FRAME_LEN_24 = 3, /*!< I2S frame size 24 bits */
    I2S_FRAME_LEN_32 = 4, /*!< I2S frame size 32 bits */
} i2s_frame_size_t;

/*!
 *  @brief    I2S data size settings
 *
 *  This enumeration defines the data size type
 */
typedef enum {
    I2S_DATA_LEN_8 = 1,  /*!< I2S data size 8 bits */
    I2S_DATA_LEN_16 = 2, /*!< I2S data size 16 bits */
    I2S_DATA_LEN_24 = 3, /*!< I2S data size 24 bits */
    I2S_DATA_LEN_32 = 4, /*!< I2S data size 32 bits */
} i2s_data_size_t;

/*!
 *  @brief    I2S frame channel settings
 *
 *  This enumeration defines the frame channel mode type
 */
typedef enum {
    I2S_FS_CHANNELS_NUM_MONO = 1, /*!< I2S frame is for 1 channels */
    I2S_FS_CHANNELS_NUM_2 = 2,    /*!< I2S frame is for 2 channels */
    I2S_FS_CHANNELS_NUM_3 = 3,    /*!< I2S frame is for 3 channels, DSP mode only, frame_size must equal data_size*/
    I2S_FS_CHANNELS_NUM_4 = 4,    /*!< I2S frame is for 4 channels, DSP mode only, frame_size must equal data_size*/
} i2s_channel_num_t;

typedef enum {
    I2S_MODE_MASTER = 0, /*!< I2S as master */
    I2S_MODE_SLAVE,      /*!< I2S as slave */
} i2s_mode_t;

typedef struct i2s_device {
    struct device parent;
    uint8_t id;

    i2s_mode_t iis_mode;
    interface_mode_t interface_mode;
    uint32_t sampl_freq_hz; /*!< I2S sample data frequency in Hz */
    i2s_channel_num_t channel_num;
    i2s_frame_size_t frame_size;
    i2s_data_size_t data_size;
    uint8_t fifo_threshold; /*!< I2S receive and transmit threshold*/
    void *tx_dma;
    void *rx_dma;
} i2s_device_t;

#define I2S_DEV(dev) ((i2s_device_t *)dev)

int i2s_register(enum i2s_index_type index, const char *name);

#endif