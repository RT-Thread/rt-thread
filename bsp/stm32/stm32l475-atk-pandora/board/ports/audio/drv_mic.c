/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2019-07-31     Zero-Free    first implementation
 */

#include <board.h>

#include "drv_es8388.h"

#define DBG_TAG              "drv.mic"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#define RX_FIFO_SIZE (1024)

struct mic_device
{
    struct rt_audio_device audio;
    struct rt_audio_configure record_config;
    rt_uint8_t *rx_fifo;
    rt_uint8_t volume;
};

static struct mic_device mic_dev = {0};
static rt_uint16_t zero_frame[2] = {0};

static SAI_HandleTypeDef SAI1B_Handler = {0};
static DMA_HandleTypeDef SAI1_RXDMA_Handler = {0};

extern SAI_HandleTypeDef SAI1A_Handler;
extern DMA_HandleTypeDef SAI1_RXDMA_Handler;
extern void SAIA_Frequency_Set(uint32_t frequency);

void SAIB_Init(void)
{
    HAL_SAI_DeInit(&SAI1B_Handler);

    SAI1B_Handler.Init.AudioFrequency         = SAI_AUDIO_FREQUENCY_44K;
    SAI1B_Handler.Instance                    = SAI1_Block_B;
    SAI1B_Handler.Init.AudioMode              = SAI_MODESLAVE_RX;
    SAI1B_Handler.Init.Synchro                = SAI_SYNCHRONOUS;
    SAI1B_Handler.Init.OutputDrive            = SAI_OUTPUTDRIVE_ENABLE;
    SAI1B_Handler.Init.NoDivider              = SAI_MASTERDIVIDER_ENABLE;
    SAI1B_Handler.Init.FIFOThreshold          = SAI_FIFOTHRESHOLD_EMPTY;
    SAI1B_Handler.Init.MonoStereoMode         = SAI_MONOMODE;
    SAI1B_Handler.Init.Protocol               = SAI_FREE_PROTOCOL;
    SAI1B_Handler.Init.DataSize               = SAI_DATASIZE_16;
    SAI1B_Handler.Init.FirstBit               = SAI_FIRSTBIT_MSB;
    SAI1B_Handler.Init.ClockStrobing          = SAI_CLOCKSTROBING_RISINGEDGE;

    SAI1B_Handler.FrameInit.FrameLength       = 64;
    SAI1B_Handler.FrameInit.ActiveFrameLength = 32;
    SAI1B_Handler.FrameInit.FSDefinition      = SAI_FS_CHANNEL_IDENTIFICATION;
    SAI1B_Handler.FrameInit.FSPolarity        = SAI_FS_ACTIVE_LOW;
    SAI1B_Handler.FrameInit.FSOffset          = SAI_FS_BEFOREFIRSTBIT;
    SAI1B_Handler.SlotInit.FirstBitOffset     = 0;
    SAI1B_Handler.SlotInit.SlotSize           = SAI_SLOTSIZE_32B;
    SAI1B_Handler.SlotInit.SlotNumber         = 2;
    SAI1B_Handler.SlotInit.SlotActive         = SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_1;

    HAL_SAI_Init(&SAI1B_Handler);
    __HAL_SAI_ENABLE(&SAI1B_Handler);

    /* Configure DMA used for SAI1 */
    __HAL_RCC_DMA2_CLK_ENABLE();

    SAI1_RXDMA_Handler.Init.Request             = DMA_REQUEST_1;
    SAI1_RXDMA_Handler.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    SAI1_RXDMA_Handler.Init.PeriphInc           = DMA_PINC_DISABLE;
    SAI1_RXDMA_Handler.Init.MemInc              = DMA_MINC_ENABLE;
    SAI1_RXDMA_Handler.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    SAI1_RXDMA_Handler.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
    SAI1_RXDMA_Handler.Init.Mode                = DMA_CIRCULAR;
    SAI1_RXDMA_Handler.Init.Priority            = DMA_PRIORITY_HIGH;
    SAI1_RXDMA_Handler.Instance                 = DMA2_Channel2;
    __HAL_LINKDMA(&SAI1B_Handler, hdmarx, SAI1_RXDMA_Handler);
    HAL_DMA_DeInit(&SAI1_RXDMA_Handler);
    HAL_DMA_Init(&SAI1_RXDMA_Handler);
    __HAL_DMA_ENABLE(&SAI1_RXDMA_Handler);

    HAL_NVIC_SetPriority(DMA2_Channel2_IRQn, 0x01, 0);
    HAL_NVIC_EnableIRQ(DMA2_Channel2_IRQn);
}

void SAIB_Channels_Set(uint8_t channels)
{
    if (channels == 1)
    {
        SAI1B_Handler.Init.MonoStereoMode         = SAI_MONOMODE;
    }
    else
    {
        SAI1B_Handler.Init.MonoStereoMode         = SAI_STEREOMODE;
    }

    __HAL_SAI_DISABLE(&SAI1B_Handler);
    HAL_SAI_Init(&SAI1B_Handler);
    __HAL_SAI_ENABLE(&SAI1B_Handler);
}

void DMA2_Channel2_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&SAI1_RXDMA_Handler);
}

void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
    rt_audio_rx_done(&mic_dev.audio, &mic_dev.rx_fifo[0], RX_FIFO_SIZE / 2);
}

void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai)
{
    rt_audio_rx_done(&mic_dev.audio, &mic_dev.rx_fifo[RX_FIFO_SIZE / 2], RX_FIFO_SIZE / 2);
}

static rt_err_t mic_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    struct mic_device *mic_dev;

    RT_ASSERT(audio != RT_NULL);
    mic_dev = (struct mic_device *)audio->parent.user_data;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_QUERY: /* qurey the types of hw_codec device */
    {
        switch (caps->sub_type)
        {
        case AUDIO_TYPE_QUERY:
            caps->udata.mask = AUDIO_TYPE_INPUT | AUDIO_TYPE_MIXER;
            break;

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    case AUDIO_TYPE_INPUT: /* Provide capabilities of INPUT unit */
    {
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            caps->udata.config.samplerate   = mic_dev->record_config.samplerate;
            caps->udata.config.channels     = mic_dev->record_config.channels;
            caps->udata.config.samplebits   = mic_dev->record_config.samplebits;
            break;

        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate   = mic_dev->record_config.samplerate;
            break;

        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels     = mic_dev->record_config.channels;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits   = mic_dev->record_config.samplebits;
            break;

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    case AUDIO_TYPE_MIXER: /* report the Mixer Units */
    {
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_QUERY:
            caps->udata.mask = AUDIO_MIXER_VOLUME | AUDIO_MIXER_LINE;
            break;

        case AUDIO_MIXER_VOLUME:
            caps->udata.value = mic_dev->volume;
            break;

        case AUDIO_MIXER_LINE:
            break;

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}

static rt_err_t mic_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    struct mic_device *mic_dev;

    RT_ASSERT(audio != RT_NULL);
    mic_dev = (struct mic_device *)audio->parent.user_data;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_MIXER:
    {
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_VOLUME:
        {
            rt_uint32_t volume = caps->udata.value;
            mic_dev->volume = volume;
            LOG_D("set volume %d", volume);
            break;
        }

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    case AUDIO_TYPE_INPUT:
    {
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
        {
            SAIA_Frequency_Set(caps->udata.config.samplerate);
            HAL_SAI_DMAStop(&SAI1B_Handler);
            SAIB_Channels_Set(caps->udata.config.channels);
            HAL_SAI_Transmit(&SAI1A_Handler, (uint8_t *)&zero_frame[0], 2, 0);
            HAL_SAI_Receive_DMA(&SAI1B_Handler, mic_dev->rx_fifo, RX_FIFO_SIZE / 2);

            /* save configs */
            mic_dev->record_config.samplerate = caps->udata.config.samplerate;
            mic_dev->record_config.channels   = caps->udata.config.channels;
            mic_dev->record_config.samplebits = caps->udata.config.samplebits;
            LOG_D("set samplerate %d", mic_dev->record_config.samplerate);
            LOG_D("set channels %d", mic_dev->record_config.channels);
            break;
        }

        case AUDIO_DSP_SAMPLERATE:
        {
            mic_dev->record_config.samplerate = caps->udata.config.samplerate;
            LOG_D("set channels %d", mic_dev->record_config.channels);
            break;
        }

        case AUDIO_DSP_CHANNELS:
        {
            mic_dev->record_config.channels   = caps->udata.config.channels;
            LOG_D("set channels %d", mic_dev->record_config.channels);
            break;
        }

        default:
            break;
        }

        break;
    }

    default:
        break;
    }

    return result;
}

static rt_err_t mic_init(struct rt_audio_device *audio)
{
    struct mic_device *mic_dev;

    RT_ASSERT(audio != RT_NULL);
    mic_dev = (struct mic_device *)audio->parent.user_data;

    SAIB_Init();

    /* set default params */
    SAIB_Channels_Set(mic_dev->record_config.channels);

    return RT_EOK;
}

static rt_err_t mic_start(struct rt_audio_device *audio, int stream)
{
    struct mic_device *mic_dev;

    RT_ASSERT(audio != RT_NULL);
    mic_dev = (struct mic_device *)audio->parent.user_data;

    if (stream == AUDIO_STREAM_RECORD)
    {
        es8388_start(ES_MODE_ADC);
        HAL_SAI_Transmit(&SAI1A_Handler, (uint8_t *)&zero_frame[0], 2, 0);
        HAL_SAI_Receive_DMA(&SAI1B_Handler, mic_dev->rx_fifo, RX_FIFO_SIZE / 2);
    }

    return RT_EOK;
}

static rt_err_t mic_stop(struct rt_audio_device *audio, int stream)
{
    if (stream == AUDIO_STREAM_RECORD)
    {
        HAL_SAI_DMAStop(&SAI1B_Handler);
        HAL_SAI_Abort(&SAI1A_Handler);
        es8388_stop(ES_MODE_ADC);
    }

    return RT_EOK;
}

static struct rt_audio_ops mic_ops =
{
    .getcaps     = mic_getcaps,
    .configure   = mic_configure,
    .init        = mic_init,
    .start       = mic_start,
    .stop        = mic_stop,
    .transmit    = RT_NULL,
    .buffer_info = RT_NULL,
};

int rt_hw_mic_init(void)
{
    rt_uint8_t *rx_fifo;

    if (mic_dev.rx_fifo)
        return RT_EOK;

    rx_fifo = rt_malloc(RX_FIFO_SIZE);
    if (rx_fifo == RT_NULL)
        return -RT_ENOMEM;
    rt_memset(rx_fifo, 0, RX_FIFO_SIZE);
    mic_dev.rx_fifo = rx_fifo;

    /* init default configuration */
    {
        mic_dev.record_config.samplerate = 44100;
        mic_dev.record_config.channels   = 2;
        mic_dev.record_config.samplebits = 16;
        mic_dev.volume                   = 55;
    }

    /* register sound device */
    mic_dev.audio.ops = &mic_ops;
    rt_audio_register(&mic_dev.audio, "mic0", RT_DEVICE_FLAG_RDONLY, &mic_dev);

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_mic_init);
