/*
 * File      : audio_device.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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