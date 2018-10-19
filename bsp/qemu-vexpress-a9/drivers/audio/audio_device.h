/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-26     RT-Thread    the first version
 */

#ifndef AUDIO_DEVICE_H__
#define AUDIO_DEVICE_H__

enum AUDIO_DEVICE_STATE
{
    AUDIO_DEVICE_IDLE,
    AUDIO_DEVICE_PLAYBACK,
    AUDIO_DEVICE_CLOSE,
};

void *audio_device_get_buffer(int *bufsz);
void audio_device_put_buffer(void *ptr);

void audio_device_write(void *buffer, int size);

int audio_device_init(void);
void audio_device_close(void);

void audio_device_open(void);

int audio_device_set_evt_handler(void (*handler)(void *parameter, int state), void *parameter);

void audio_device_set_rate(int sample_rate);
void audio_device_set_volume(int volume);
void audio_device_wait_free(void);

#endif