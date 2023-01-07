/**
 * @file hal_audio.h
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

#ifndef __HAL_AUDIO__
#define __HAL_AUDIO__

#include "audio_reg.h"
#include "bl808_audio.h"
#include "bl808_dma.h"
#include "drv_device.h"

/** @addtogroup  BL808_Middleware_Driver
 *  @{
 */

/** @addtogroup  AUDIO_Middleware
 *  @{
 */

/** @defgroup  AUDIO_Middleware_Public_Types
 *  @{
 */

/**
 *  @brief Audio Flow Type
 */
typedef enum {
    AUDIO_PLAY = 0,  /*!< Audio Play selction */
    AUDIO_RECORDING, /*!< Audio Recording selction */
} Audio_Flow_Type;

/**
 *  @brief Audio Channel Sel
 */
typedef enum {
    LEFT_CHANNEL = 1, /*!< select mono mode left only */
    RIGHT_CHANNEL,    /*!< select mono mode right only */
    STEREO_CHANNEL,   /*!< select stereo */
} Audio_Channel_Type;

/**
 *  @brief Audio mixer option
 */
typedef enum {
    MIX_WITH_ADC_LEFT = 1, /*!< mix With ADC Left */
    MIX_WITH_ADC_RIGHT,    /*!< mix With ADC Right */
} Audio_Mixer_Cfg_Type;

/**
 *  @brief Audio Play/recording bit width
 */
typedef enum {
    AUDIO_BIT_WIDTH_16, /*!< 16 bit */
    AUDIO_BIT_WIDTH_24, /*!< 24 bit */
    AUDIO_BIT_WIDTH_32, /*!< 32 bit */
} Audio_BitWidth_Type;

/**
 *  @brief Audio Input Interface
 */
typedef enum {
    AUDIO_INPUT_PDM_DMIC, /*!< audio input source is Dmic */
    AUDIO_INPUT_ANG_AMIC, /*!< audio input source is Amic */
} Audio_RecordingInterface_Type;

/**
 *  @brief Audio_PlayCfg_Type
 */
typedef struct {
    DMA_ID_Type audioDmaId;                                    /*!< audio dma id */
    DMA_Chan_Type audioDmaChannelId;                           /*!< audio dma channel id */
    uint32_t playSampleRate;                                   /*!< audio play sample rate */
    Audio_BitWidth_Type playBitWidth;                          /*!< audio play bit width */
    Audio_Channel_Type channel;                                /*!< audio play channel number */
    uint16_t audioInitVolume;                                  /*!< initial audio volume */
    void (*pingpongBufferCarryDoneCallback)(uint8_t pp_index); /*!< audio dma carry pingpong buffer done callback function pointer */
    void (*volumeSetDoneCallback)(uint8_t dac_index);          /*!< When the volume is adjusted this function pointer will be run */
    BL_Fun_Type audioMixerEn;                                  /*!< enable mixer or not */
    Audio_Mixer_Cfg_Type dacLeftMixWith;                       /*!< select dac left channel mix with adc right or left */
    Audio_Mixer_Cfg_Type dacRightMixWith;                      /*!< select dac right channel mix with adc right or left */
} Audio_PlayCfg_Type;

/**
 *  @brief Audio_RecordingCfg_Type
 */
typedef struct {
    DMA_ID_Type audioDmaId;                                    /*!< audio dma id */
    DMA_Chan_Type audioDmaChannelId;                           /*!< audio dma channel id */
    uint32_t recordingSampleRate;                              /*!< audio Recording sample rate */
    Audio_RecordingInterface_Type recordinginterface;          /*!< audio Recording input interface */
    Audio_BitWidth_Type recordingBitWidth;                     /*!< audio Recording bit width */
    Audio_Channel_Type channel;                                /*!< audio Recording channel number */
    uint16_t audioInitVolume;                                  /*!< initial audio Recording volume */
    void (*pingpongBufferCarryDoneCallback)(uint8_t pp_index); /*!< audio dma carry pingpong buffer done callback function pointer */
    void (*volumeSetDoneCallback)(uint8_t adc_index);          /*!< When the volume is adjusted this function pointer will be run */
} Audio_RecordingCfg_Type;

/*@} end of group AUDIO_Middleware_Public_Types */

/** @defgroup  AUDIO_Middleware_Public_Constants
 *  @{
 */

/** @defgroup  AUDIO_FLOW_TYPE
 *  @{
 */
#define IS_AUDIO_FLOW_TYPE(type) (((type) == AUDIO_PLAY) || \
                                  ((type) == AUDIO_RECORDING))

/** @defgroup  AUDIO_CHANNEL_TYPE
 *  @{
 */
#define IS_AUDIO_CHANNEL_TYPE(type) (((type) == LEFT_CHANNEL) ||  \
                                     ((type) == RIGHT_CHANNEL) || \
                                     ((type) == STEREO_CHANNEL))

/** @defgroup  AUDIO_MIXER_CFG_TYPE
 *  @{
 */
#define IS_AUDIO_MIXER_CFG_TYPE(type) (((type) == MIX_WITH_ADC_LEFT) || \
                                       ((type) == MIX_WITH_ADC_RIGHT))

/** @defgroup  AUDIO_BITWIDTH_TYPE
 *  @{
 */
#define IS_AUDIO_BITWIDTH_TYPE(type) (((type) == AUDIO_BIT_WIDTH_16) || \
                                      ((type) == AUDIO_BIT_WIDTH_24) || \
                                      ((type) == AUDIO_BIT_WIDTH_32))

/** @defgroup  AUDIO_RECORDINGINTERFACE_TYPE
 *  @{
 */
#define IS_AUDIO_RECORDINGINTERFACE_TYPE(type) (((type) == AUDIO_INPUT_PDM_DMIC) || \
                                                ((type) == AUDIO_INPUT_ANG_AMIC))

/*@} end of group AUDIO_Middleware_Public_Constants */

/** @defgroup  AUDIO_Middleware_Public_Macros
 *  @{
 */
#define AUDIO_PLAY_PINGPONG_BUFFER_SIZE      (2 * 1024)
#define AUDIO_RECORDING_PINGPONG_BUFFER_SIZE (2 * 1024)
#define AUDIO_TX_FIFO_ADDR                   AUDIO_BASE + 0x94
#define AUDIO_RX_FIFO_ADDR                   AUDIO_BASE + 0x88
#define AUDIO_DEFAULT_TX_DRQ_THR             8
#define AUDIO_DEFAULT_RX_DRQ_THR             8
/* audio play configuration */
#define AUDIO_PLAY_DEFAULT_DMA_ID         DMA0_ID
#define AUDIO_PLAY_DEFAULT_DMA_CHANNEL    DMA_CH0
#define AUDIO_PLAY_DEFAULT_SAMPLE         48 * 1000
#define AUDIO_PLAY_DEFAULT_BIT_WIDTH      AUDIO_BIT_WIDTH_16
#define AUDIO_PLAY_DEFAULT_INITIAL_VOLUME 0xffad
#define AUDIO_PLAY_DEFAULT_CHANNEL_NUM    STEREO_CHANNEL
#define AUDIO_PLAY_DEFAULT_MIXER_EN       DISABLE
#define AUDIO_PLAY_DEFAULT_LEFT_MIX_WITH  MIX_WITH_ADC_LEFT
#define AUDIO_PLAY_DEFAULT_RIGHT_MIX_WITH MIX_WITH_ADC_RIGHT
/*audio recording configuration */
#define AUDIO_RECORDING_DEFAULT_DMA_ID         DMA0_ID
#define AUDIO_RECORDING_DEFAULT_DMA_CHANNEL    DMA_CH1
#define AUDIO_RECORDING_DEFAULT_SAMPLE         16 * 1000
#define AUDIO_RECORDING_DEFAULT_BIT_WIDTH      AUDIO_BIT_WIDTH_16
#define AUDIO_RECORDING_DEFAULT_INITIAL_VOLUME 60
/* if user want to select more adc channel option ,
* you can write such as
* ADC1_DATA_CHANNEL_FIFO_EN | ADC3_DATA_CHANNEL_FIFO_EN |
* middleware default set is  (ADC1_DATA_CHANNEL_FIFO_EN | ADC2_DATA_CHANNEL_FIFO_EN) equel to STEREO_CHANNEL
**/
#define AUDIO_RECORDING_DEFAULT_CHANNEL_NUM STEREO_CHANNEL
#define AUDIO_RECORDING_DEFAULT_INTERFACE   AUDIO_INPUT_PDM_DMIC

/*@} end of group AUDIO_Middleware_Public_Macros */

/** @defgroup  AUDIO_Middleware_Public_Functions
 *  @{
 */
/* Audio Play Profile API */
BL_Err_Type Audio_PlayDeInit(void);
BL_Err_Type Audio_PlayInit(Audio_PlayCfg_Type *cfg);
BL_Err_Type Audio_PlayParameterInit(Audio_PlayCfg_Type *cfg);
BL_Err_Type Audio_PlaySetVolume(Audio_Channel_Type channel, int16_t volume);
int16_t Audio_PlayGetVolume(Audio_Channel_Type channel);
BL_Err_Type Audio_PlayStart(Audio_PlayCfg_Type *cfg);
BL_Err_Type Audio_PlayStop(Audio_PlayCfg_Type *cfg);
/* Audio Recording API */
BL_Err_Type Audio_RecordingDeInit(void);
BL_Err_Type Audio_RecordingInit(Audio_RecordingCfg_Type *cfg);
BL_Err_Type Audio_RecordingParameterInit(Audio_RecordingCfg_Type *cfg);
BL_Err_Type Audio_RecordingSetVolume(Audio_Channel_Type channel, int16_t volume);
int16_t Audio_RecordingGetVolume(Audio_Channel_Type channel);
BL_Err_Type Audio_RecordingStart(Audio_RecordingCfg_Type *cfg);
BL_Err_Type Audio_RecordingStop(Audio_RecordingCfg_Type *cfg);
/* Audio AEC API */
BL_Err_Type Audio_AecInit(BL_Fun_Type sw, Audio_Channel_Type channel,
                          Audio_AEC_Atten_Mode aecDrop, Audio_PlayCfg_Type *playCfg, Audio_RecordingCfg_Type *recordingCfg);
uint32_t Audio_GetPingpongBufferAddr(Audio_Flow_Type flowType);
uint32_t Audio_GetPingBufferAddr(Audio_Flow_Type flowType);
uint32_t Audio_GetPongBufferAddr(Audio_Flow_Type flowType);
uint32_t Audio_GetPingpongBufferLength(Audio_Flow_Type flowType);
void Audio_FlushPingpongBuffer(Audio_Flow_Type flowType);

//--adapt

#define DEVICE_CTRL_UART_GET_TX_FIFO 0x10
#define DEVICE_CTRL_UART_GET_RX_FIFO 0x11

enum audio_index_type {
#ifdef BSP_USING_AUDIO
    AUDIO0_INDEX,
#endif
    AUDIO_MAX_INDEX
};

typedef struct audio_device {
    struct device parent;
    uint32_t sampleRate;
    Audio_BitWidth_Type bitWidth;
    Audio_Channel_Type channel;
    uint16_t audioInitVolume;
    void (*pingpongBufferCarryDoneCallback)(uint8_t pp_index);
    void (*volumeSetDoneCallback)(uint8_t dac_index);
    void *tx_dma;
    void *rx_dma;
} audio_device_t;

#define AUDIO_DEV(dev) ((audio_device_t *)dev)

#define DEVICE_CTRL_PLAY_VOLUME      0x0E
#define DEVICE_CTRL_RECORDING_VOLUME 0x0F

#define DEVICE_CTRL_RECORDING_START 0x10
#define DEVICE_CTRL_RECORDING_STOP  0x11
#define DEVICE_CTRL_PLAY_START      0x12
#define DEVICE_CTRL_PLAY_STOP       0x13

#define DEVICE_CTRL_GET_PLAY_PING_BUF   0x14
#define DEVICE_CTRL_GET_PLAY_PONG_BUF   0x15
#define DEVICE_CTRL_GET_RECORD_PING_BUF 0x16
#define DEVICE_CTRL_GET_RECORD_PONG_BUF 0x17

int audio_register(enum audio_index_type index, const char *name);
#endif