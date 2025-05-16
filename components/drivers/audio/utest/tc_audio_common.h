/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-05-02     wumingzi     first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rttypes.h>
#include "utest.h"

/* DMA buffer of audio player device refresh is triggered only when the amount of transmitted data is
 * greater than the size of a single block in the data queue */
#define TX_DMA_BLOCK_SIZE   RT_AUDIO_REPLAY_MP_BLOCK_SIZE
#define TX_DMA_FIFO_SIZE   (RT_AUDIO_REPLAY_MP_BLOCK_SIZE * 2)
#define RX_DMA_BLOCK_SIZE   RT_AUDIO_RECORD_PIPE_SIZE
#define RX_DMA_FIFO_SIZE   (RT_AUDIO_RECORD_PIPE_SIZE * 2)

#define SOUND_PLAYER_DEVICE_NAME    "sound0"
#define SOUND_MIC_DEVICE_NAME    "mic0"

#define PLAYER_SAMPLEBITS   16
#define PLAYER_SAMPLERATE   16000
#define PLAYER_CHANNEL      2
#define PLAYER_VOLUME    30

#define MIC_SAMPLEBITS   16
#define MIC_SAMPLERATE   16000
#define MIC_CHANNEL      2
#define MIC_TIME_MS      5000

extern rt_uint8_t audio_fsm_step ;

struct mic_device
{
    struct rt_audio_device audio;
    struct rt_audio_configure config;
    rt_uint8_t *rx_fifo;
};
struct sound_device
{
    struct rt_audio_device audio;
    struct rt_audio_configure config;
    rt_uint8_t volume;
    rt_uint8_t *tx_fifo;
};