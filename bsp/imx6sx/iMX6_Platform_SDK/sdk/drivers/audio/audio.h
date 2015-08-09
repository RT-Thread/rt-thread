/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file audio.h
 * @brief Common herder file for audio drivers
 *
 * @ingroup diag_audio
 */

#ifndef __AUDIO_H
#define __AUDIO_H

#include "i2c/imx_i2c.h"

/*
 * This macro is for test purpose only, do not define it unless you know what you are doing.
 */
//#define ESAI_AC97_SUPPORT

#define AUDIO_RECORD_BUF_LEN    0x100000

//! @brief AUDIO bus types
typedef enum {
    AUDIO_BUS_TYPE_SSI,
    AUDIO_BUS_TYPE_ESAI,
    AUDIO_BUS_TYPE_SPDIF,
} audio_bus_type_e;

//! @brief Audio bus modes
typedef enum {
    AUDIO_BUS_MODE_SLAVE = 0,
    AUDIO_BUS_MODE_MASTER = 1,
    AUDIO_BUS_MODE_EITHER = 2,  //the audio controller or codec can be configured as Master or Slave
} audio_bus_mode_e;

//! @brief Audio bus protocals
typedef enum {
    AUDIO_BUS_PROTOCOL_NORMAL,
    AUDIO_BUS_PROTOCOL_NETWORK,
    AUDIO_BUS_PROTOCOL_I2S,
    AUDIO_BUS_PROTOCOL_LEFT_ALIGNED,
    AUDIO_BUS_PROTOCOL_AC97,
} audio_bus_protocol_e;

//! @brief Trasmit directions
typedef enum {
    AUDIO_TRANS_DIR_TX = 0,
    AUDIO_TRANS_DIR_RX = 1,
    AUDIO_TRANS_DIR_TXRX = 2,	
} audio_trans_dir_e;

//! @brief Sample rates
typedef enum {
    SAMPLERATE_8KHz = 8000,
    SAMPLERATE_16KHz = 16000,
    SAMPLERATE_32KHz = 32000,
    SAMPLERATE_44_1KHz = 44100,
    SAMPLERATE_48KHz = 48000,
} audio_samplerate_e;

//! @brief Word length
typedef enum {
    WL_8 = 8,
    WL_16 = 16,
    WL_20 = 20,
    WL_24 = 24,
    WL_32 = 32,
} audio_word_length_e;

//! @brief  Parameters dedicated with PCM data
typedef struct {
    audio_samplerate_e sample_rate;
    uint32_t channel_number;
    audio_word_length_e word_length;
} audio_pcm_para_t, *audio_pcm_para_p;

//! @brief  Data structure for PCM file
typedef struct {
    const char *name;
    audio_pcm_para_p para;	//!< The PCM data's parameters
    uint8_t *buf;	//!< Pointer to the buffer where the PCM data located
    uint32_t size;	//!< Buffer size fot the PCD data
} audio_pcm_t, *audio_pcm_p;

//! @brief   Parameters dedicated with audio device(controller or codec)
typedef struct {
    audio_bus_mode_e bus_mode;	//!<  Bus mode
    audio_bus_protocol_e bus_protocol;	//!< Protocal
    audio_trans_dir_e trans_dir;	//!< Direction
    audio_samplerate_e sample_rate;	//!< Sample rate
    audio_word_length_e word_length;	//!< Word length
    uint32_t channel_number;		//!< Channel number
} audio_dev_para_t, *audio_dev_para_p;

//! @brief   Operations for audio device(controller or codec)
typedef struct {
    int32_t (*init) (void *priv);	//!< Initialize routine
    int32_t (*deinit) (void *priv);	//!< De-initialize routine
    int32_t (*config) (void *priv, audio_dev_para_p para);	//!< Configuration routine
    int32_t (*ioctl) (void *priv, uint32_t cmd, void *para);	//!< IO control routine
    int32_t (*write) (void *priv, uint8_t * buf, uint32_t byte2write, uint32_t * bytewrittern);	//!< Write routine
    int32_t (*read) (void *priv, uint8_t * buf, uint32_t byte2read, uint32_t * byteread);	//!< Read routine
} audio_dev_ops_t, *audio_dev_ops_p;

//! brief  Data structure for audio codec
typedef struct {
    const char *name;
    const i2c_device_info_t * device;   //!< Pointer to I2C device info.
    audio_bus_type_e bus_type;  //The bus type(ssi, esai or spdif) the codec supports
    audio_bus_mode_e bus_mode;  //the bus mode(master, slave or both)the codec supports
    audio_dev_ops_p ops;	//!< Operations
} audio_codec_t, *audio_codec_p;

//! brief  Data structure for audio controller
typedef struct {
    const char *name;
    uint32_t instance;         // the io base address of the controller
    audio_bus_type_e bus_type;  //The bus type(ssi, esai or spdif) the controller supports
    audio_bus_mode_e bus_mode;  //the bus mode(master, slave or both)the controller supports
    uint32_t irq;                    //the irq number
    uint32_t sdma_ch;                //Will be used for SDMA
    audio_dev_ops_p ops;
} audio_ctrl_t, *audio_ctrl_p;

//! @brief Audio card structure
typedef struct {
    const char *name;
    audio_codec_p codec;	//!< Audio codec
    audio_ctrl_p ctrl;		//!< Audio controller
    audio_dev_ops_p ops;	//!< Operations
} audio_card_t, *audio_card_p;

#endif
