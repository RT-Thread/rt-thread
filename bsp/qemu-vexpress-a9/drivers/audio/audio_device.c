/*
 * File      : audio_device.c
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

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <string.h>
#include "drv_pl041.h"
#include "drv_ac97.h"
#include "audio_device.h"

struct audio_device
{
    struct rt_device *snd;
    struct rt_mempool mp;

    int state;

    void (*evt_handler)(void *parameter, int state);
    void *parameter;
};

static struct audio_device *_audio_device = NULL;

void *audio_device_get_buffer(int *bufsz)
{
    if (bufsz)
    {
        *bufsz = AUDIO_DEVICE_DECODE_MP_BLOCK_SZ * 2;
    }

    return rt_mp_alloc(&(_audio_device->mp), RT_WAITING_FOREVER);
}

void audio_device_put_buffer(void *ptr)
{
    if (ptr) rt_mp_free(ptr);
    return ;
}

static rt_err_t audio_device_write_done(struct rt_device *device, void *ptr)
{
    if (!ptr)
    {
        rt_kprintf("device buf_release NULL\n");
        return -RT_ERROR;
    }

    rt_mp_free(ptr);
    return RT_EOK;
}

void audio_device_write(void *buffer, int size)
{
    if (_audio_device->snd && size != 0)
    {
        if (_audio_device->state == AUDIO_DEVICE_IDLE)
        {
            if (_audio_device->evt_handler)
                _audio_device->evt_handler(_audio_device->parameter, AUDIO_DEVICE_PLAYBACK);

            /* change audio device state */
            _audio_device->state = AUDIO_DEVICE_PLAYBACK;
        }

        rt_device_write(_audio_device->snd, 0, buffer, size);
    }
    else
    {
        /* release buffer directly */
        rt_mp_free(buffer);
    }

    return ;
}

int audio_device_init(void)
{
    uint8_t *mempool_ptr;

    if (!_audio_device)
    {
        _audio_device = (struct audio_device *) rt_malloc(sizeof(struct audio_device) + AUDIO_DEVICE_DECODE_MP_SZ);
        if (_audio_device == NULL)
        {
            rt_kprintf("malloc memeory for _audio_device failed! \n");
            return -RT_ERROR;
        }

        _audio_device->evt_handler = NULL;
        _audio_device->parameter   = NULL;

        mempool_ptr = (uint8_t *)(_audio_device + 1);
        rt_mp_init(&(_audio_device->mp), "adbuf", mempool_ptr, AUDIO_DEVICE_DECODE_MP_SZ, AUDIO_DEVICE_DECODE_MP_BLOCK_SZ * 2);

        /* find snd device */
        _audio_device->snd = rt_device_find("sound");
        if (_audio_device->snd == NULL)
        {
            rt_kprintf("sound device not found \n");
            return -1;
        }

        /* set tx complete call back function */
        rt_device_set_tx_complete(_audio_device->snd, audio_device_write_done);
    }

    return RT_EOK;
}

int audio_device_set_evt_handler(void (*handler)(void *parameter, int state), void *parameter)
{
    if (_audio_device)
    {
        _audio_device->evt_handler = handler;
        _audio_device->parameter   = parameter;
    }

    return 0;
}

void audio_device_set_rate(int sample_rate)
{
    if (_audio_device->snd)
    {
        int rate = sample_rate;

        rt_device_control(_audio_device->snd, CODEC_CMD_SAMPLERATE, &rate);
    }
}

void audio_device_set_volume(int value)
{
    if (_audio_device->snd)
    {
        rt_device_control(_audio_device->snd, CODEC_CMD_SET_VOLUME, &value);
    }
}

int audio_device_get_volume(void)
{
    int value = 0;

    if (_audio_device->snd)
    {
        rt_device_control(_audio_device->snd, CODEC_CMD_GET_VOLUME, &value);
    }

    return value;
}

void audio_device_open(void)
{
    _audio_device->state = AUDIO_DEVICE_IDLE;
    rt_device_open(_audio_device->snd, RT_DEVICE_OFLAG_WRONLY);
}

void audio_device_close(void)
{
    rt_device_close(_audio_device->snd);

    if (_audio_device->state == AUDIO_DEVICE_PLAYBACK)
    {
        if (_audio_device->evt_handler)
            _audio_device->evt_handler(_audio_device->parameter, AUDIO_DEVICE_CLOSE);
    }

    /* set to idle */
    _audio_device->state = AUDIO_DEVICE_CLOSE;
}
