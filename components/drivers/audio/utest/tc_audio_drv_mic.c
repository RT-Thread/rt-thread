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
static struct mic_device mic_dev;

/* Simulate callback function */
static void thread_simulate_intr(void *parameter)
{
    /* Send the data(0xAA) from DMA buffer to kernel */
    rt_memset((void*)&mic_dev.rx_fifo[0], 0xAA, RX_DMA_BLOCK_SIZE);
    rt_audio_rx_done((struct rt_audio_device *)&(mic_dev.audio), mic_dev.rx_fifo, RX_DMA_BLOCK_SIZE);
    audio_fsm_step = 1;

    while (1)
    {
        if(audio_fsm_step == 2)
        {
            /* Send the the data(0x55) from DMA buffer to kernel */
            rt_memset((void*)&mic_dev.rx_fifo[RX_DMA_BLOCK_SIZE], 0x55, RX_DMA_BLOCK_SIZE);
            rt_audio_rx_done(&mic_dev.audio, &mic_dev.rx_fifo[RX_DMA_BLOCK_SIZE], RX_DMA_BLOCK_SIZE);
            audio_fsm_step = 3;
            break;
        }
        if(audio_fsm_step == 4)
        {
            rt_thread_mdelay(10);
            rt_audio_rx_done(&mic_dev.audio, &mic_dev.rx_fifo[RX_DMA_BLOCK_SIZE], RX_DMA_BLOCK_SIZE);
            break;
        }
        rt_thread_mdelay(10);
    }

    while(1)
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

    if (thread_simulate_intr_handle == RT_NULL)
    {
        rt_kprintf("Error: Failed to create thread!\n");
        return;
    }
    if (rt_thread_startup(thread_simulate_intr_handle) != RT_EOK)
    {
        rt_kprintf("Error: Failed to start thread!\n");
        thread_simulate_intr_handle = RT_NULL;
    }

}

static rt_err_t mic_device_init(struct rt_audio_device *audio)
{
    return RT_EOK;
}

/* Simulate DMA interrupt */
static rt_err_t mic_device_start(struct rt_audio_device *audio, int stream)
{
    thread_simulate_intr_create();
    return RT_EOK;
}

static rt_err_t mic_device_stop(struct rt_audio_device *audio, int stream)
{
    if (thread_simulate_intr_handle != RT_NULL)
    {
        rt_thread_delete(thread_simulate_intr_handle);
        thread_simulate_intr_handle = RT_NULL;
    }
    return RT_EOK;
}

static rt_err_t mic_device_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    return RT_EOK;
}

static rt_err_t mic_device_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    return RT_EOK;
}

static struct rt_audio_ops _mic_audio_ops =
{
    .getcaps     = mic_device_getcaps,
    .configure   = mic_device_configure,
    .init        = mic_device_init,
    .start       = mic_device_start,
    .stop        = mic_device_stop,
    .transmit    = RT_NULL,
    .buffer_info = RT_NULL,
};

static int rt_hw_mic_init(void)
{
    struct rt_audio_device *audio = &mic_dev.audio;
    /* mic default */
    mic_dev.rx_fifo = rt_malloc(RX_DMA_FIFO_SIZE);
    if (mic_dev.rx_fifo == RT_NULL)
    {
        return -RT_ENOMEM;
    }
    mic_dev.config.channels = MIC_CHANNEL;
    mic_dev.config.samplerate = MIC_SAMPLERATE;
    mic_dev.config.samplebits = MIC_SAMPLEBITS;

    /* register mic device */
    audio->ops = &_mic_audio_ops;
    rt_audio_register(audio, SOUND_MIC_DEVICE_NAME, RT_DEVICE_FLAG_RDONLY, (void *)&mic_dev);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_mic_init);