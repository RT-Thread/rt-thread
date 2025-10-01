/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-05-01     wumingzi     first version
 */

/* The file can test the rt-thread audio driver framework including following api via memory
 *  simulation.
 *
 *  rt_audio_register
 *  rt_audio_rx_done
 *  rt_audio_tx_complete
 *
 *  When audio devices generate or receive new data, the corresponding buffer in device will
 *  receive date from kernel or surroundings. The same phenomenon will also happen at the
 *  application level. Thus we can fill memory to simulate the generation of data then track
 *  and check memory to ensure kernel processing audio data correctly. And this depends on
 *  implementations of audio drivers.
 *
 *  Therefore, if the player_test testcase failed, it could mean rt_audio_register or
 *  rt_audio_tx_complete existing bugs. Similarly, if mic_test testcase failed, it could mean
 *  rt_audio_register or rt_audio_rx_done existing bugs.
 */

#include "tc_audio_common.h"

rt_uint8_t audio_fsm_step = 0;

/* Allocate and initialize memory filled by fill_byte */
static void *alloc_filled_mem(rt_uint8_t fill_byte, rt_size_t size)
{
    void *ptr = rt_malloc(size);
    if (ptr != NULL)
    {
        rt_memset(ptr, fill_byte, size);
    }
    return ptr;
}

/* Check if the memory is filled with fill_byte */
static rt_err_t check_filled_mem(rt_uint8_t fill_byte, rt_uint8_t *mem, size_t size)
{
    rt_uint8_t *p = mem;
    for (size_t i = 0; i < size; ++i)
    {
        if (*(p+i) != fill_byte)
        {
            return -RT_ERROR;
        }
    }
    return RT_EOK;
}

static void player_test(void)
{
    int res = 0;
    void* player_buffer = RT_NULL;
    rt_device_t dev_obj;

    dev_obj = rt_device_find(SOUND_PLAYER_DEVICE_NAME);
    if (dev_obj == RT_NULL)
    {
        uassert_not_null(dev_obj);
        goto __exit;
    }
    if (dev_obj->type != RT_Device_Class_Sound)
    {
        LOG_E("Not an audio player device\n");
        goto __exit;
    }

    res = rt_device_open(dev_obj, RT_DEVICE_OFLAG_WRONLY);
    if (res != RT_EOK)
    {
        LOG_E("Audio player device failed\n");
        uassert_true(0);
        goto __exit;
    }

    /* The sampling rate is set by the driver default, so there isn't configuration step */

    struct rt_audio_device *audio_dev = rt_container_of(dev_obj, struct rt_audio_device, parent);
    struct rt_audio_buf_info buf_info = audio_dev->replay->buf_info;
    struct sound_device *snd_dev = rt_container_of(audio_dev, struct sound_device, audio);

    player_buffer = alloc_filled_mem(0xAA, TX_DMA_BLOCK_SIZE);
    if (player_buffer == RT_NULL)
    {
        rt_kprintf("Allocate test memory failed\n");
        uassert_true(0);
        goto __exit;
    }

    if(snd_dev->tx_fifo == RT_NULL)
    {
        rt_kprintf("snd_dev->tx_fifo == RT_NULL ");
        uassert_true(0);
        goto __exit;
    }
    res = rt_device_write(dev_obj, 0, player_buffer, TX_DMA_BLOCK_SIZE);
    if (res != RT_EOK  && res != TX_DMA_BLOCK_SIZE)
    {
        rt_kprintf("Failed to write data to the player device, res = %d\n",res);
        uassert_true(0);
        goto __exit;
    }

    audio_fsm_step = 1;
    while (1)
    {
        if(audio_fsm_step == 2)
        {
            break;
        }
        rt_thread_mdelay(10);
    }

    res = check_filled_mem(0xAA, &buf_info.buffer[0], TX_DMA_BLOCK_SIZE);
    if (res != RT_EOK)
    {
        rt_kprintf("The first memory check failed! Buffer dump\n");

        for (rt_size_t i = 0; i < TX_DMA_FIFO_SIZE; i++)
        {
            rt_kprintf("%02X ", buf_info.buffer[i]);
            if (i % 16 == 15) rt_kprintf("\n");
        }
        rt_kprintf("\n");
        uassert_true(0);
        goto __exit;
    }

    rt_free(player_buffer);
    player_buffer = RT_NULL;

    player_buffer = alloc_filled_mem(0x55, TX_DMA_BLOCK_SIZE);
    if (player_buffer == RT_NULL)
    {
        rt_kprintf("Allocate test memory failed\n");
        uassert_true(0);
        goto __exit;
    }

    res = rt_device_write(dev_obj, TX_DMA_BLOCK_SIZE, player_buffer, TX_DMA_BLOCK_SIZE);
    if (res != RT_EOK  && res != TX_DMA_BLOCK_SIZE)
    {
        rt_kprintf("Failed to write data to the player device, res = %d\n",res);
        uassert_true(0);
        goto __exit;
    }

    audio_fsm_step = 2;
    while (res != RT_EOK)
    {
        if(audio_fsm_step == 3)
        {
            break;
        }

        rt_thread_mdelay(10);
    }

    res = check_filled_mem(0x55,&buf_info.buffer[TX_DMA_BLOCK_SIZE], TX_DMA_BLOCK_SIZE);
    if (res != RT_EOK)
    {
        rt_kprintf("The second memory check failed! Buffer dump\n");

        for (rt_size_t i = 0; i < TX_DMA_FIFO_SIZE; i++)
        {
            rt_kprintf("%02X ", buf_info.buffer[i]);
            if (i % 16 == 15) rt_kprintf("\n");
        }
        rt_kprintf("\n");
        uassert_true(0);
        goto __exit;
    }

__exit:

    if (player_buffer)
    {
        rt_free(player_buffer);
        player_buffer = RT_NULL;
    }

    if (dev_obj != RT_NULL)
    {
        audio_fsm_step = 4;
        rt_device_close(dev_obj);
    }
}

static void mic_test(void)
{
    rt_device_t dev_obj;
    rt_uint8_t *mic_buffer = RT_NULL;
    rt_ssize_t res = 0;
    rt_ssize_t length = 0;
    mic_buffer = (rt_uint8_t *)rt_malloc(RX_DMA_BLOCK_SIZE);
    if (mic_buffer == RT_NULL)
    {
        rt_kprintf("The mic_buffer memory allocate failed\n");
        uassert_true(0);
        goto __exit;
    }


    dev_obj = rt_device_find(SOUND_MIC_DEVICE_NAME);
    if (dev_obj == RT_NULL)
    {
        LOG_E("Not a mic device\n");
        uassert_true(0);
        goto __exit;
    }

    res = rt_device_open(dev_obj, RT_DEVICE_OFLAG_RDONLY);
    if (res != RT_EOK)
    {
        LOG_E("Audio player device failed\n");
        uassert_true(0);
        goto __exit;
    }

    length = rt_device_read(dev_obj, 0, mic_buffer,RX_DMA_BLOCK_SIZE);
    if(length < 0)
    {
        LOG_E("Mic device read err\n");
    }
    if(audio_fsm_step == 1)
    {
        res = check_filled_mem(0xAA, (rt_uint8_t*)(mic_buffer), length);
    }
    if (res != RT_EOK)
    {
        LOG_E("The first memory check failed! Buffer dump\n");
        for (rt_size_t i = 0; i < RX_DMA_FIFO_SIZE; i++)
        {
            rt_kprintf("%02X ",mic_buffer[i]);
            if (i % 16 == 15) rt_kprintf("\n");
        }
        rt_kprintf("\n");
        uassert_true(0);
        goto __exit;
    }
    audio_fsm_step = 2;

    while (1)
    {
        if(audio_fsm_step == 3)
        {
            length = rt_device_read(dev_obj, 0, mic_buffer, RX_DMA_FIFO_SIZE);
            if(length < 0)
            {
                LOG_E("Mic device read err\n");
            }
            res = check_filled_mem(0x55, (rt_uint8_t*)(&mic_buffer[0]), length);

            if(res != RT_EOK)
            {
                LOG_E("The second memory check failed! Buffer dump\n");
                for (rt_size_t i = 0; i < RX_DMA_FIFO_SIZE; i++)
                {
                    rt_kprintf("%02X ",mic_buffer[i]);
                    if (i % 16 == 15) rt_kprintf("\n");
                }
                rt_kprintf("\n");
                uassert_true(0);
                goto __exit;
            }

            break;
        }
        rt_thread_mdelay(100);
    }

__exit:
    if (mic_buffer)
    {
        rt_free(mic_buffer);
    }

    if (dev_obj != RT_NULL)
    {
        audio_fsm_step = 4;
        rt_device_close(dev_obj);
    }
}

static void testcase(void)
{
    UTEST_UNIT_RUN(player_test);
    UTEST_UNIT_RUN(mic_test);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

UTEST_TC_EXPORT(testcase, "components.drivers.audio.tc_audio_main", utest_tc_init, utest_tc_cleanup, 10);