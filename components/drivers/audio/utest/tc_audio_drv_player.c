/*
* Copyright (c) 2006-2025 RT-Thread Development Team
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date           Author       Notes
* 2025-05-02     wumingzi     First version
*/

#include "tc_audio_common.h"

#define THREAD_PRIORITY 9
#define THREAD_TIMESLICE 5
#define thread_simulate_intr_create_stacksize 1024
static rt_thread_t thread_simulate_intr_handle;
static struct sound_device snd_dev;

static void thread_simulate_intr(void *parameter)
{
    rt_flag_t exec_once = 0;
    while(1)
    {
        if(audio_fsm_step == 1 && exec_once == 0)
        {
            /* Move the data(0xAA) from kernel to DMA buffer */
            rt_audio_tx_complete(&snd_dev.audio);
            audio_fsm_step = 2;
            exec_once = 1;
            rt_thread_mdelay(10);
        }
        else if(audio_fsm_step == 2 && exec_once == 1)
        {
            /* Move the data(0x55) from kernel to DMA buffer */
            rt_audio_tx_complete(&snd_dev.audio);
            audio_fsm_step = 3;
            rt_thread_mdelay(10);
        }
        else if(audio_fsm_step == 4)
        {
            /* rt_device_close will call rt_completion_wait(FOREVER), so we need delay to
             * let system run the point */
            rt_thread_mdelay(10);
            rt_audio_tx_complete(&snd_dev.audio);
            break;
        }
        rt_thread_mdelay(10);
    }
    while (1)
    {
        rt_thread_mdelay(10);
    }
}

static void thread_simulate_intr_create(void)
{
    thread_simulate_intr_handle = rt_thread_create(
        "thread_simulate_intr",
        thread_simulate_intr,
        RT_NULL,
        thread_simulate_intr_create_stacksize,
        THREAD_PRIORITY - 1, THREAD_TIMESLICE);

    rt_thread_startup(thread_simulate_intr_handle);
}

static rt_err_t player_device_init(struct rt_audio_device *audio)
{
    return RT_EOK;
}

/* Simulate DMA interrupt */
static rt_err_t player_device_start(struct rt_audio_device *audio, int stream)
{
    thread_simulate_intr_create();
    return RT_EOK;
}

static rt_err_t player_device_stop(struct rt_audio_device *audio, int stream)
{
    rt_thread_delete(thread_simulate_intr_handle);
    return RT_EOK;
}

static rt_err_t player_device_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    return RT_EOK;
}

static rt_err_t player_device_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    return RT_EOK;
}

static rt_ssize_t player_device_transmit(struct rt_audio_device *audio, const void *writeBuf, void *readBuf, rt_size_t size)
{
    return size;
}

static void player_device_buffer_info(struct rt_audio_device *audio, struct rt_audio_buf_info *info)
{
    RT_ASSERT(audio != RT_NULL);
    /**
    *               TX_FIFO
    * +----------------+----------------+
    * |     block1     |     block2     |
    * +----------------+----------------+
    *  \  block_size  /
    */
    info->buffer      = snd_dev.tx_fifo;
    info->total_size  = TX_DMA_FIFO_SIZE;
    info->block_size  = TX_DMA_BLOCK_SIZE;
    info->block_count = RT_AUDIO_REPLAY_MP_BLOCK_COUNT;
}

static struct rt_audio_ops audio_ops =
{
    .getcaps = player_device_getcaps,
    .configure = player_device_configure,
    .init = player_device_init,
    .start = player_device_start,
    .stop = player_device_stop,
    .transmit = player_device_transmit,
    .buffer_info = player_device_buffer_info,
};

static int rt_hw_sound_init(void)
{
    rt_uint8_t *tx_fifo = RT_NULL;

    tx_fifo = rt_malloc(TX_DMA_FIFO_SIZE);
    if (tx_fifo == NULL)
    {
        return -RT_ENOMEM;
    }
    snd_dev.tx_fifo = tx_fifo;

    /* Init default configuration */
    {
        snd_dev.config.samplerate = PLAYER_SAMPLERATE;
        snd_dev.config.channels   = PLAYER_CHANNEL;
        snd_dev.config.samplebits = PLAYER_SAMPLEBITS;
        snd_dev.volume            = PLAYER_VOLUME;
    }

    snd_dev.audio.ops = &audio_ops;
    rt_audio_register(&snd_dev.audio, SOUND_PLAYER_DEVICE_NAME, RT_DEVICE_FLAG_WRONLY, &snd_dev);
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_sound_init);