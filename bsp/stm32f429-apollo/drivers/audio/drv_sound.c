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
#include <rtdevice.h>
#include <rthw.h>

#include <stdint.h>
#include <string.h>

#include "drv_audio.h"
#include "drv_wm8978.h"
#include <stm32f4xx.h>

#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_COLOR
#define DBG_SECTION_NAME    "Sound"
#include <rtdbg.h>

/**
 * Audio Memory Node Manage
 */
struct rt_data_node
{
    char *data_ptr;
    rt_uint32_t data_size;
};

struct rt_data_node_list
{
    struct rt_data_node *node;
    rt_uint32_t size;
    rt_uint32_t read_index, write_index;
    rt_uint32_t data_offset;
    void (*read_complete)(struct rt_data_node *node, void *user_data);
    void *user_data;
};

int rt_data_node_init(struct rt_data_node_list **node_list, rt_uint32_t size)
{
    int result = RT_EOK;
    struct rt_data_node_list *list = RT_NULL;
    struct rt_data_node *node = RT_NULL;

    list = rt_malloc(sizeof(struct rt_data_node_list));
    if (list == RT_NULL)
    {
        result = -RT_ENOMEM;
        goto __exit;
    }
    memset(list, 0, sizeof(struct rt_data_node_list));

    node = rt_malloc(sizeof(struct rt_data_node) * size);
    if (size == RT_NULL)
    {
        result = -RT_ENOMEM;
        goto __exit;
    }
    memset(node, 0, sizeof(struct rt_data_node));

    list->node = node;
    list->size = size;
    list->read_index = 0;
    list->write_index = 0;
    list->data_offset = 0;
    list->read_complete = RT_NULL;
    list->user_data = 0;

    *node_list = list;

    return result;

__exit:
    if (list)
        rt_free(list);

    if (node)
        rt_free(node);

    return result;
}

int rt_data_node_is_empty(struct rt_data_node_list *node_list)
{
    rt_uint32_t read_index, write_index;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    read_index = node_list->read_index;
    write_index = node_list->write_index;
    rt_hw_interrupt_enable(level);

    if (read_index == write_index)
    {
        return RT_TRUE;
    }
    else
    {
        return RT_FALSE;
    }
}

void wait_node_free(struct rt_data_node_list *node_list)
{
    while (node_list->read_index != node_list->write_index)
        rt_thread_mdelay(5);
}

int rt_data_node_write(struct rt_data_node_list *node_list, void *buffer, rt_uint32_t size)
{
    struct rt_data_node *node = RT_NULL;
    rt_uint32_t read_index, write_index, next_index;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    read_index = node_list->read_index;
    write_index = node_list->write_index;
    rt_hw_interrupt_enable(level);

    next_index = write_index + 1;
    if (next_index >= node_list->size)
        next_index = 0;

    if (next_index == read_index)
    {
        rt_kprintf("[node]:node list full, write index = %d, read index = %d \n", write_index, read_index);
        return -RT_ERROR;
    }

    level = rt_hw_interrupt_disable();
    /* set node attribute */
    node = &node_list->node[write_index];
    node->data_ptr = (char *) buffer;
    node->data_size = size;
    node_list->write_index = next_index;
    rt_hw_interrupt_enable(level);

    return size;
}

int rt_data_node_read(struct rt_data_node_list *node_list, void *buffer, rt_uint32_t size)
{
    struct rt_data_node *node = RT_NULL;
    rt_uint32_t read_index, write_index, next_index;
    rt_int32_t remain_len, copy_size;
    rt_uint32_t read_offset, data_offset;
    rt_base_t level;
    rt_uint32_t result = size;

    level = rt_hw_interrupt_disable();
    read_index = node_list->read_index;
    write_index = node_list->write_index;
    rt_hw_interrupt_enable(level);

    read_offset = 0;
    if (read_index == write_index)
    {
        result = 0;
    }
    else
    {
        do
        {
            node = &node_list->node[node_list->read_index];
            data_offset = node_list->data_offset;
            remain_len = node->data_size - data_offset;
            if (size - read_offset > remain_len)
            {
                /* Full*/
                copy_size = remain_len;
            }
            else
            {
                /* reamain buffer */
                copy_size = size - read_offset;
            }

            memcpy((char *)buffer + read_offset, node->data_ptr + data_offset, copy_size);
            read_offset += copy_size;
            data_offset += copy_size;
            node_list->data_offset = data_offset;

            if (data_offset >= node->data_size)
            {
                /* notify transmitted complete. */
                if (node_list->read_complete != RT_NULL)
                {
                    node_list->read_complete(node, node_list->user_data);
                }

                level = rt_hw_interrupt_disable();
                read_index = node_list->read_index;
                write_index = node_list->write_index;
                rt_hw_interrupt_enable(level);

                next_index = read_index + 1;
                if (next_index >= node_list->size)
                    next_index = 0;

                level = rt_hw_interrupt_disable();
                node_list->read_index = next_index;
                node_list->data_offset = 0;
                rt_hw_interrupt_enable(level);

                if (next_index == write_index)
                {
                    result = read_offset;
                    break;
                }
            }
        }
        while (read_offset < size);
    }

    return result;
}

static void data_node_read_complete(struct rt_data_node *node, void *user_data)
{
    struct rt_device *dev = RT_NULL;

    dev = (struct rt_device *)user_data;
    if (dev->tx_complete != RT_NULL)
    {
        dev->tx_complete(dev, node->data_ptr);
    }
}

/**
 * RT-Thread Audio Device Driver
 */
struct sound_device
{
    struct rt_device parent;
    struct rt_data_node_list *node_list;

    /* i2c mode */
    struct rt_i2c_bus_device *i2c_device;

    char *send_fifo;
};

#define AUDIO_SEND_BUFFER_SIZE (2048 * 2)

SAI_HandleTypeDef SAI1B_Handler;
DMA_HandleTypeDef SAI1_RXDMA_Handler;
SAI_HandleTypeDef SAI1A_Handler;
DMA_HandleTypeDef SAI1_TXDMA_Handler;

static struct sound_device *sound;

static void SAIA_Init(void)
{
    HAL_SAI_DeInit(&SAI1A_Handler);
    // SAI1A_Handler.Init.AudioFrequency = 44100;
    SAI1A_Handler.Instance = SAI1_Block_A;
    SAI1A_Handler.Init.AudioMode = SAI_MODEMASTER_TX;
    SAI1A_Handler.Init.Synchro = SAI_ASYNCHRONOUS;
    SAI1A_Handler.Init.OutputDrive = SAI_OUTPUTDRIVE_ENABLE;
    SAI1A_Handler.Init.NoDivider = SAI_MASTERDIVIDER_ENABLE;
    SAI1A_Handler.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_EMPTY;
    SAI1A_Handler.Init.ClockSource = SAI_CLKSOURCE_PLLI2S;
    SAI1A_Handler.Init.MonoStereoMode = SAI_STEREOMODE;
    SAI1A_Handler.Init.Protocol = SAI_FREE_PROTOCOL;
    SAI1A_Handler.Init.DataSize = SAI_DATASIZE_16;
    SAI1A_Handler.Init.FirstBit = SAI_FIRSTBIT_MSB;
    SAI1A_Handler.Init.ClockStrobing = SAI_CLOCKSTROBING_RISINGEDGE;

    SAI1A_Handler.FrameInit.FrameLength = 64;
    SAI1A_Handler.FrameInit.ActiveFrameLength = 32;
    SAI1A_Handler.FrameInit.FSDefinition = SAI_FS_CHANNEL_IDENTIFICATION;
    SAI1A_Handler.FrameInit.FSPolarity = SAI_FS_ACTIVE_LOW;
    SAI1A_Handler.FrameInit.FSOffset = SAI_FS_BEFOREFIRSTBIT;
    SAI1A_Handler.SlotInit.FirstBitOffset = 0;
    SAI1A_Handler.SlotInit.SlotSize = SAI_SLOTSIZE_32B;
    SAI1A_Handler.SlotInit.SlotNumber = 2;
    SAI1A_Handler.SlotInit.SlotActive = SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_1;

    HAL_SAI_Init(&SAI1A_Handler);
    __HAL_SAI_ENABLE(&SAI1A_Handler);

    /* DMA Configuration */
    SAIA_TX_DMAx_CLK_ENABLE();
    __HAL_LINKDMA(&SAI1A_Handler, hdmatx, SAI1_TXDMA_Handler);
    SAI1_TXDMA_Handler.Instance = SAIA_TX_DMAx_STREAM;
    SAI1_TXDMA_Handler.Init.Channel = SAIA_TX_DMAx_CHANNEL;
    SAI1_TXDMA_Handler.Init.Direction = DMA_MEMORY_TO_PERIPH;
    SAI1_TXDMA_Handler.Init.PeriphInc = DMA_PINC_DISABLE;
    SAI1_TXDMA_Handler.Init.MemInc = DMA_MINC_ENABLE;
    SAI1_TXDMA_Handler.Init.PeriphDataAlignment = SAIA_TX_DMAx_PERIPH_DATA_SIZE;
    SAI1_TXDMA_Handler.Init.MemDataAlignment = SAIA_TX_DMAx_MEM_DATA_SIZE;
    SAI1_TXDMA_Handler.Init.Mode = DMA_CIRCULAR;
    SAI1_TXDMA_Handler.Init.Priority = DMA_PRIORITY_HIGH;
    SAI1_TXDMA_Handler.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    SAI1_TXDMA_Handler.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;
    SAI1_TXDMA_Handler.Init.MemBurst = DMA_MBURST_SINGLE;
    SAI1_TXDMA_Handler.Init.PeriphBurst = DMA_PBURST_SINGLE;
    HAL_DMA_DeInit(&SAI1_TXDMA_Handler);
    HAL_DMA_Init(&SAI1_TXDMA_Handler);

    HAL_NVIC_SetPriority(SAIA_TX_DMAx_IRQ, 0, 0);
    HAL_NVIC_EnableIRQ(SAIA_TX_DMAx_IRQ);
}

const uint16_t SAI_PSC_TBL[][5] =
{
    {800, 344, 7, 0, 12},
    {1102, 429, 2, 18, 2},
    {1600, 344, 7, 0, 6},
    {2205, 429, 2, 18, 1},
    {3200, 344, 7, 0, 3},
    {4410, 429, 2, 18, 0},
    {4800, 344, 7, 0, 2},
    {8820, 271, 2, 2, 1},
    {9600, 344, 7, 0, 1},
    {17640, 271, 2, 2, 0},
    {19200, 344, 7, 0, 0},
};

void SAIA_DMA_Enable(void)
{
    SAI1_Block_A->CR1 |= SAI_xCR1_DMAEN;
}

void SAIA_DMA_Disable(void)
{
    SAI1_Block_A->CR1 &= ~SAI_xCR1_DMAEN;
}

int SAIA_SampleRate_Set(uint32_t samplerate)
{
    uint16_t i = 0;

    RCC_PeriphCLKInitTypeDef RCCSAI1_Sture;
    for (i = 0; i < (sizeof(SAI_PSC_TBL) / 10); i++)
    {
        if ((samplerate / 10) == SAI_PSC_TBL[i][0])
            break;
    }
    if (i == (sizeof(SAI_PSC_TBL) / 10))
        return -RT_ERROR;
    RCCSAI1_Sture.PeriphClockSelection = RCC_PERIPHCLK_SAI_PLLI2S;
    RCCSAI1_Sture.PLLI2S.PLLI2SN = (uint32_t)SAI_PSC_TBL[i][1];
    RCCSAI1_Sture.PLLI2S.PLLI2SQ = (uint32_t)SAI_PSC_TBL[i][2];
    RCCSAI1_Sture.PLLI2SDivQ = SAI_PSC_TBL[i][3] + 1;
    HAL_RCCEx_PeriphCLKConfig(&RCCSAI1_Sture);

    __HAL_RCC_SAI_BLOCKACLKSOURCE_CONFIG(RCC_SAIACLKSOURCE_PLLI2S);

    __HAL_SAI_DISABLE(&SAI1A_Handler);
    SAIA_DMA_Disable();
    SAI1A_Handler.Init.AudioFrequency = samplerate;
    HAL_SAI_Init(&SAI1A_Handler);
    SAIA_DMA_Enable();
    __HAL_SAI_ENABLE(&SAI1A_Handler);

    return RT_EOK;
}

void HAL_SAI_MspInit(SAI_HandleTypeDef *hsai)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_SAI1_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_Initure.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;
    GPIO_Initure.Alternate = GPIO_AF6_SAI1;
    HAL_GPIO_Init(GPIOE, &GPIO_Initure);
}

void SAIA_TX_DMAx_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&SAI1_TXDMA_Handler);
}

void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
    int result;
    struct sound_device *snd = sound;

    if (hsai == &SAI1A_Handler)
    {
        result = rt_data_node_is_empty(snd->node_list);
        if (result)
        {
            rt_kprintf("# ");
            memset(snd->send_fifo, 0, AUDIO_SEND_BUFFER_SIZE / 2);
        }
        else
        {
            memset(snd->send_fifo, 0, AUDIO_SEND_BUFFER_SIZE / 2);
            rt_data_node_read(snd->node_list, snd->send_fifo, AUDIO_SEND_BUFFER_SIZE / 2);
        }
    }
}

void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai)
{
    int result;
    struct sound_device *snd = sound;

    if (hsai == &SAI1A_Handler)
    {
        result = rt_data_node_is_empty(snd->node_list);
        if (result)
        {
            rt_kprintf("* ");
            memset(snd->send_fifo + (AUDIO_SEND_BUFFER_SIZE / 2), 0, AUDIO_SEND_BUFFER_SIZE / 2);
        }
        else
        {
            memset(snd->send_fifo + (AUDIO_SEND_BUFFER_SIZE / 2), 0, AUDIO_SEND_BUFFER_SIZE / 2);
            rt_data_node_read(snd->node_list, snd->send_fifo + (AUDIO_SEND_BUFFER_SIZE / 2), AUDIO_SEND_BUFFER_SIZE / 2);
        }

    }
}

void HAL_SAI_ErrorCallback(SAI_HandleTypeDef *hsai)
{
    rt_kprintf("x ");
}


static rt_err_t sound_init(rt_device_t dev)
{
    int result;
    struct sound_device *snd = (struct sound_device *)dev;

    SAIA_Init();
    result = wm8978_init(snd->i2c_device);

    return result;
}

static rt_err_t sound_open(rt_device_t dev, rt_uint16_t oflag)
{
    int result = RT_EOK;
    struct sound_device *snd = (struct sound_device *)dev;

    LOG_I("Open Sound Device!");

    /* Configure DMA transmit */
    result = HAL_SAI_Transmit_DMA(&SAI1A_Handler, (uint8_t *)(snd->send_fifo), AUDIO_SEND_BUFFER_SIZE / 2);
    if (result != HAL_OK)
    {
        LOG_E("Start DMA Transmit Failed!");
        result = -RT_ERROR;
    }

    return result;
}

static rt_err_t sound_control(rt_device_t dev, int cmd, void *args)
{
    int value, result = RT_EOK;
    struct sound_device *snd = (struct sound_device *)dev;

    switch (cmd)
    {
    case CODEC_CMD_SET_VOLUME:
        value = *(int *)args;
        if (value < 0 || value > 99)
        {
            LOG_W("Please volume level 0 ~ 99");
            result = -RT_EINVAL;
        }
        else
        {
            LOG_I("Set volume level to %d", value);
            wm8978_set_volume(snd->i2c_device, value);
            result = RT_EOK;
        }
        break;

    case CODEC_CMD_SAMPLERATE:
        value = *(int *)args;
        LOG_I("Set Samplerate %d", value);
        SAIA_SampleRate_Set(value);
        break;

    default:
        result = RT_EOK;
    }
    return result;
}

static rt_size_t sound_write(rt_device_t dev, rt_off_t pos,
                             const void *buffer, rt_size_t size)
{
    int result = RT_EOK;
    struct sound_device *snd = (struct sound_device *)dev;

    result = rt_data_node_write(snd->node_list, (void *)buffer, size);

    return result;
}

static rt_err_t sound_close(rt_device_t dev)
{
    HAL_SAI_DMAStop(&SAI1A_Handler);
    LOG_I("Close Sound Device!");

    return RT_EOK;
}

int rt_hw_sound_hw_init(char *i2c_bus_name)
{
    int result = RT_EOK;

    if (sound != RT_NULL)
        return RT_EOK;

    HAL_SAI_MspInit(NULL);
    sound = rt_malloc(sizeof(struct sound_device));
    if (sound == RT_NULL)
    {
        LOG_E("malloc memory for sound device failed!");
        result = -RT_ENOMEM;
        goto __exit;
    }
    memset(sound, 0, sizeof(struct sound_device));

    sound->i2c_device = rt_i2c_bus_device_find(i2c_bus_name);
    if (sound->i2c_device == RT_NULL)
    {
        LOG_E("i2c bus device %s not found!", i2c_bus_name);
        result = -RT_ENOSYS;
        goto __exit;
    }

    sound->send_fifo = rt_malloc(AUDIO_SEND_BUFFER_SIZE);
    if (sound->send_fifo == RT_NULL)
    {
        result = -RT_ENOMEM;
        goto __exit;
    }
    memset(sound->send_fifo, 0, AUDIO_SEND_BUFFER_SIZE);

    rt_data_node_init(&sound->node_list, 10);
    sound->node_list->read_complete = data_node_read_complete;
    sound->node_list->user_data = sound;

    sound->parent.type      = RT_Device_Class_Sound;
    sound->parent.init      = sound_init;
    sound->parent.open      = sound_open;
    sound->parent.control   = sound_control;
    sound->parent.write     = sound_write;
    sound->parent.read      = RT_NULL;
    sound->parent.close     = sound_close;
    sound->parent.user_data = sound;

    /* register the device */
    rt_device_register(&sound->parent, "sound", RT_DEVICE_FLAG_WRONLY | RT_DEVICE_FLAG_DMA_TX);
    rt_device_init(&sound->parent);

    return RT_EOK;

__exit:
    if (sound->send_fifo != RT_NULL)
    {
        rt_free(sound->send_fifo);
        sound->send_fifo = RT_NULL;
    }

    if (sound != RT_NULL)
    {
        rt_free(sound);
        sound = RT_NULL;
    }

    return result;
}

extern int rt_hw_micphone_init(char *i2c_bus_name);

int rt_hw_audio_init(char *i2c_bus_name)
{
    rt_hw_sound_hw_init(i2c_bus_name);
    rt_hw_micphone_init(i2c_bus_name);

    return RT_EOK;
}
