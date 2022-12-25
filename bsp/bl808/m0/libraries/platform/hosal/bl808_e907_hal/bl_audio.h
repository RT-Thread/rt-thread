/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __BL_AUDIO_H__
#define __BL_AUDIO_H__

#include <stdint.h>
#include <bl808_dma.h>
#include "bl808_audio.h"

typedef int (*audio_callback_rx_ready_t)(void *usrdata, uint8_t *audiodata, int len, int is_overflow);
typedef int (*audio_callback_tx_ready_t)(void *uerdata, uint8_t *audiodata, int len, int is_underrun);

#define AUDIO_PLAY_DEFAULT_INITIAL_VOLUME    0x0
#define AUDIO_TX_FIFO_ADDR                   AUDIO_BASE + 0x94
#define AUDIO_RX_FIFO_ADDR                   AUDIO_BASE + 0x88
#define AUDIO_DEFAULT_TX_DRQ_THR             8
#define AUDIO_DEFAULT_RX_DRQ_THR             8

typedef enum {
    LEFT_CHANNEL = 1,   /*!< select mono mode left only */
    RIGHT_CHANNEL = 2,  /*!< select mono mode right only */
    STEREO_CHANNEL = 3, /*!< select stereo */
    THREE_CHANNEL = 7,  /*!< select Three */
} Audio_Channel_Type;

typedef enum {
    AUDIO_BIT_WIDTH_16, /*!< 16 bit */
    AUDIO_BIT_WIDTH_24, /*!< 24 bit */
    AUDIO_BIT_WIDTH_32, /*!< 32 bit */
} Audio_BitWidth_Type;

typedef enum {
    AUDIO_8_KHZ,   /*!< Audio DAC Clock set as 8KHZ */
    AUDIO_16_KHZ,  /*!< Audio DAC Clock set as 16KHZ */
    AUDIO_24_KHZ,  /*!< Audio DAC Clock set as 24KHZ */
    AUDIO_32_KHZ,  /*!< Audio DAC Clock set as 32KHZ */
    AUDIO_48_KHZ,  /*!< Audio DAC Clock set as 48KHZ */
    AUDIO_96_KHZ,  /*!< Audio DAC Clock set as 96KHZ */
    AUDIO_192_KHZ, /*!< Audio DAC Clock set as 192KHZ */
} Audio_Samplerate_Type;

typedef struct {
    uint8_t pingpang;
    DMA_LLI_Ctrl_Type lli_tx_list[2];
    DMA_LLI_Ctrl_Type lli_rx_list[2];
    uint8_t *lli_tx_buffer;
    uint32_t lli_tx_buffer_size;
    uint8_t *lli_rx_buffer;
    uint32_t lli_rx_buffer_size;

    int is_underrun;
    int is_overflow;
    audio_callback_tx_ready_t usr_cb;
    audio_callback_rx_ready_t usr_rx_cb;
    void *p_usr_arg;
    void *p_usr_rx_arg;

    Audio_Samplerate_Type samplerate;
    Audio_BitWidth_Type playBitWidth;
    Audio_Channel_Type tx_channel;
    Audio_Channel_Type rx_channel;
    uint8_t rx_enable;

} bl_audio_dev_t;

int bl_audio_init (bl_audio_dev_t *p_dev);

int bl_audio_deinit (bl_audio_dev_t *p_dev);

int bl_audio_start (bl_audio_dev_t *p_dev);

int bl_audio_stop (bl_audio_dev_t *p_dev);

int bl_audio_tx_buffer_config (bl_audio_dev_t *p_dev,
                                   void **ptr_mem,
                                   uint32_t bufsize);

int bl_audio_rx_buffer_config (bl_audio_dev_t *p_dev,
                                   void **ptr_mem,
                                   uint32_t bufsize);

int bl_audio_tx_ready_config(bl_audio_dev_t *p_dev,
                                 audio_callback_tx_ready_t cb,
                                 void *p_arg);

int bl_audio_rx_ready_config(bl_audio_dev_t *p_dev,
                                 audio_callback_rx_ready_t cb,
                                 void *p_arg);

int bl_audio_samplerate_set (bl_audio_dev_t *p_dev,
                                 Audio_Samplerate_Type samplerate);

#endif
