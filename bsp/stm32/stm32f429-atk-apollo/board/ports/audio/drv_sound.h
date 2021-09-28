/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-28     Ernest         the first version
 */

#ifndef __DRV_SOUND_H_
#define __DRV_SOUND_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define AUDIO_FREQUENCY_048K ((rt_uint32_t) 48000)
#define AUDIO_FREQUENCY_044K ((rt_uint32_t) 44100)
#define AUDIO_FREQUENCY_032K ((rt_uint32_t) 32000)
#define AUDIO_FREQUENCY_022K ((rt_uint32_t) 22050)
#define AUDIO_FREQUENCY_016K ((rt_uint32_t) 16000)
#define AUDIO_FREQUENCY_011K ((rt_uint32_t) 11025)
#define AUDIO_FREQUENCY_008K ((rt_uint32_t)  8000)

struct drv_sai
{
    SAI_HandleTypeDef hsai;
    DMA_HandleTypeDef hdma;
};

void SAIA_samplerate_set(rt_uint32_t samplerate);
void SAIA_channels_set(rt_uint16_t channels);
void SAIA_samplebits_set(rt_uint16_t samplebits);
void SAIA_config_set(struct rt_audio_configure config);

rt_err_t SAIA_tx_dma(void);
rt_err_t SAIA_config_init(void);

#endif
