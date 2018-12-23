/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-14     ZeroFree     first implementation
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#include <string.h>

#include "drv_audio.h"
#include "drv_wm8978.h"
#include <stm32f4xx.h>

#define DBG_ENABLE
#define DBG_LEVEL DBG_INFO
#define DBG_COLOR
#define DBG_SECTION_NAME    "MIC"
#include <rtdbg.h>

struct micphone_device
{
    struct rt_device parent;
    rt_uint16_t *recv_fifo;
    struct rt_audio_pipe record_pipe;

    /* i2c mode */
    struct rt_i2c_bus_device *i2c_device;
};

#define AUDIO_RECV_BUFFER_SIZE        (2048)

extern SAI_HandleTypeDef SAI1B_Handler;
extern DMA_HandleTypeDef SAI1_RXDMA_Handler;
extern SAI_HandleTypeDef SAI1A_Handler;
extern DMA_HandleTypeDef SAI1_TXDMA_Handler;

static struct micphone_device micphone;
static uint16_t send_fifo[2] = {0, 0};

static void SAIB_Init(void)
{
    HAL_SAI_DeInit(&SAI1B_Handler);
    SAI1B_Handler.Instance = SAI1_Block_B;
    SAI1B_Handler.Init.AudioMode = SAI_MODESLAVE_RX;
    SAI1B_Handler.Init.Synchro = SAI_SYNCHRONOUS;
    SAI1B_Handler.Init.OutputDrive = SAI_OUTPUTDRIVE_ENABLE;
    SAI1B_Handler.Init.NoDivider = SAI_MASTERDIVIDER_ENABLE;
    SAI1B_Handler.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_1QF;
    SAI1B_Handler.Init.ClockSource = SAI_CLKSOURCE_PLLI2S;
    SAI1B_Handler.Init.MonoStereoMode = SAI_MONOMODE;
    SAI1B_Handler.Init.Protocol = SAI_FREE_PROTOCOL;
    SAI1B_Handler.Init.DataSize = SAI_DATASIZE_16;
    SAI1B_Handler.Init.FirstBit = SAI_FIRSTBIT_MSB;
    SAI1B_Handler.Init.ClockStrobing = SAI_CLOCKSTROBING_RISINGEDGE;

    SAI1B_Handler.FrameInit.FrameLength = 64;
    SAI1B_Handler.FrameInit.ActiveFrameLength = 32;
    SAI1B_Handler.FrameInit.FSDefinition = SAI_FS_CHANNEL_IDENTIFICATION;
    SAI1B_Handler.FrameInit.FSPolarity = SAI_FS_ACTIVE_LOW;
    SAI1B_Handler.FrameInit.FSOffset = SAI_FS_BEFOREFIRSTBIT;

    SAI1B_Handler.SlotInit.FirstBitOffset = 0;
    SAI1B_Handler.SlotInit.SlotSize = SAI_SLOTSIZE_32B;
    SAI1B_Handler.SlotInit.SlotNumber = 2;
    SAI1B_Handler.SlotInit.SlotActive = SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_1;

    HAL_SAI_Init(&SAI1B_Handler);
    __HAL_SAI_ENABLE(&SAI1B_Handler);

    SAIA_RX_DMAx_CLK_ENABLE();
    __HAL_LINKDMA(&SAI1B_Handler, hdmarx, SAI1_RXDMA_Handler);
    SAI1_RXDMA_Handler.Instance = SAIA_RX_DMAx_STREAM;
    SAI1_RXDMA_Handler.Init.Channel = SAIA_RX_DMAx_CHANNEL;
    SAI1_RXDMA_Handler.Init.Direction = DMA_PERIPH_TO_MEMORY;
    SAI1_RXDMA_Handler.Init.PeriphInc = DMA_PINC_DISABLE;
    SAI1_RXDMA_Handler.Init.MemInc = DMA_MINC_ENABLE;
    SAI1_RXDMA_Handler.Init.PeriphDataAlignment = SAIA_RX_DMAx_PERIPH_DATA_SIZE;
    SAI1_RXDMA_Handler.Init.MemDataAlignment = SAIA_RX_DMAx_MEM_DATA_SIZE;
    SAI1_RXDMA_Handler.Init.Mode = DMA_CIRCULAR;
    SAI1_RXDMA_Handler.Init.Priority = DMA_PRIORITY_MEDIUM;
    SAI1_RXDMA_Handler.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    SAI1_RXDMA_Handler.Init.MemBurst = DMA_MBURST_SINGLE;
    SAI1_RXDMA_Handler.Init.PeriphBurst = DMA_PBURST_SINGLE;
    HAL_DMA_DeInit(&SAI1_RXDMA_Handler);
    HAL_DMA_Init(&SAI1_RXDMA_Handler);

    HAL_NVIC_SetPriority(SAIA_RX_DMAx_IRQ, 0, 1);
    HAL_NVIC_EnableIRQ(SAIA_RX_DMAx_IRQ);
}

void SAIA_RX_DMAx_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&SAI1_RXDMA_Handler);
}

void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
    if (hsai == &SAI1B_Handler)
    {
        rt_device_write(&micphone.record_pipe.parent, 0, micphone.recv_fifo, AUDIO_RECV_BUFFER_SIZE / 2);
    }
}

void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai)
{
    if (hsai == &SAI1B_Handler)
    {
        rt_device_write(&micphone.record_pipe.parent, 0, micphone.recv_fifo + (AUDIO_RECV_BUFFER_SIZE /  4), AUDIO_RECV_BUFFER_SIZE / 2);
    }
}

static rt_err_t micphone_init(rt_device_t dev)
{
    SAIB_Init();

    return RT_EOK;
}

static rt_err_t micphone_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct micphone_device *mic = RT_NULL;

    mic = (struct micphone_device *)dev;

    if (oflag & RT_DEVICE_OFLAG_RDONLY)
    {
        LOG_I("Open Micphone Device!");

        rt_device_open(&mic->record_pipe.parent, RT_DEVICE_OFLAG_RDONLY);
        /* Disable DMA Interruption */
        __HAL_DMA_DISABLE_IT(&SAI1_TXDMA_Handler, DMA_IT_TC | DMA_IT_HT);
        HAL_DMA_Start(&SAI1_TXDMA_Handler, (uint32_t)&send_fifo[0], (uint32_t)&SAI1_Block_A->DR, 2);
        /* Start RX DMA */
        HAL_SAI_Receive_DMA(&SAI1B_Handler, (uint8_t *)(micphone.recv_fifo), AUDIO_RECV_BUFFER_SIZE / 2);
    }

    return RT_EOK;
}

static rt_size_t micphone_read(rt_device_t dev, rt_off_t pos,
                               void *buffer, rt_size_t size)
{
    struct micphone_device *mic = RT_NULL;

    mic = (struct micphone_device *)dev;
    return rt_device_read(&mic->record_pipe.parent, pos, buffer, size);
}

static rt_err_t micphone_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t value, result = RT_EOK;

    switch (cmd)
    {
    case CODEC_CMD_SET_VOLUME:
    {
        // TODO
        break;
    }

    case CODEC_CMD_SAMPLERATE:
    {
        value = *(int *)args;
        LOG_I("Set Samplerate %d", value);
        result = SAIA_SampleRate_Set(value);
        break;
    }

    default:
        break;
    }

    return result;
}

static rt_err_t micphone_close(rt_device_t dev)
{
    struct micphone_device *mic = RT_NULL;

    mic = (struct micphone_device *)dev;
    HAL_SAI_DMAStop(&SAI1A_Handler);
    HAL_SAI_DMAStop(&SAI1B_Handler);
    rt_device_close(&mic->record_pipe.parent);
    LOG_I("Close Micphone Device!");

    return RT_EOK;
}

int rt_hw_micphone_init(char *i2c_bus_name)
{
    int result = RT_EOK;
    struct micphone_device *mic = &micphone;

    if (mic->recv_fifo != RT_NULL)
    {
        return RT_EOK;
    }

    mic->recv_fifo = rt_malloc(AUDIO_RECV_BUFFER_SIZE);
    if (mic->recv_fifo == RT_NULL)
    {
        result = -RT_ENOMEM;
        goto __exit;
    }
    memset(mic->recv_fifo, 0, AUDIO_RECV_BUFFER_SIZE);

    mic->parent.type      = RT_Device_Class_Sound;
    mic->parent.init      = micphone_init;
    mic->parent.open      = micphone_open;
    mic->parent.control   = micphone_control;
    mic->parent.write     = RT_NULL;
    mic->parent.read      = micphone_read;
    mic->parent.close     = micphone_close;
    mic->parent.user_data = mic;

    /* register the device */
    rt_device_register(&mic->parent, "mic", RT_DEVICE_FLAG_RDONLY | RT_DEVICE_FLAG_DMA_RX);

    rt_device_init(&mic->parent);

    {
        rt_uint8_t *buffer = rt_malloc(AUDIO_RECV_BUFFER_SIZE);
        if (buffer == RT_NULL)
        {
            result = -RT_ENOMEM;
            goto __exit;
        }
        memset(buffer, 0, AUDIO_RECV_BUFFER_SIZE);

        rt_audio_pipe_init(&mic->record_pipe,
                           "voice",
                           RT_PIPE_FLAG_FORCE_WR | RT_PIPE_FLAG_BLOCK_RD,
                           buffer,
                           AUDIO_RECV_BUFFER_SIZE);
    }

    return RT_EOK;

__exit:
    if (mic->recv_fifo)
    {
        rt_free(mic->recv_fifo);
        mic->recv_fifo = RT_NULL;
    }

    return result;
}
