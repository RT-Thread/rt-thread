/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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
static I2S_HandleTypeDef I2S3_Handler = {0};
static DMA_HandleTypeDef I2S3_RXDMA_Handler = {0};

static void I2S3_Init(void)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
    PeriphClkInitStruct.PeriphClockSelection |= RCC_PERIPHCLK_I2S;
    PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
    PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_I2S_DeInit(&I2S3_Handler);

    I2S3_Handler.Instance = I2S3ext;
    I2S3_Handler.Init.Mode = I2S_MODE_SLAVE_RX;
    I2S3_Handler.Init.Standard = I2S_STANDARD_PHILIPS;
    I2S3_Handler.Init.DataFormat = I2S_DATAFORMAT_16B;
    I2S3_Handler.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
    I2S3_Handler.Init.AudioFreq = I2S_AUDIOFREQ_DEFAULT;
    I2S3_Handler.Init.CPOL = I2S_CPOL_LOW;
    I2S3_Handler.Init.ClockSource = I2S_CLOCK_PLL;
    I2S3_Handler.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_ENABLE;
    if (HAL_I2S_Init(&I2S3_Handler) != HAL_OK)
    {
        Error_Handler();
    }

    SET_BIT(I2S3_Handler.Instance->CR2, SPI_CR2_RXDMAEN);
    __HAL_I2S_ENABLE(&I2S3_Handler);

    /* Configure DMA used for I2S3 */
    __HAL_RCC_DMA1_CLK_ENABLE();
    I2S3_RXDMA_Handler.Instance = DMA1_Stream2;
    I2S3_RXDMA_Handler.Init.Channel = DMA_CHANNEL_2;
    I2S3_RXDMA_Handler.Init.Direction = DMA_PERIPH_TO_MEMORY;
    I2S3_RXDMA_Handler.Init.PeriphInc = DMA_PINC_DISABLE;
    I2S3_RXDMA_Handler.Init.MemInc = DMA_MINC_ENABLE;
    I2S3_RXDMA_Handler.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    I2S3_RXDMA_Handler.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    I2S3_RXDMA_Handler.Init.Mode = DMA_CIRCULAR;
    I2S3_RXDMA_Handler.Init.Priority = DMA_PRIORITY_MEDIUM;
    I2S3_RXDMA_Handler.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

    __HAL_LINKDMA(&I2S3_Handler,hdmarx,I2S3_RXDMA_Handler);
    HAL_DMA_DeInit(&I2S3_RXDMA_Handler);
    HAL_DMA_Init(&I2S3_RXDMA_Handler);

    __HAL_DMA_DISABLE(&I2S3_RXDMA_Handler);
    __HAL_DMA_ENABLE_IT(&I2S3_RXDMA_Handler, DMA_IT_TC);                   /* 开启传输完成中断 */
    __HAL_DMA_CLEAR_FLAG(&I2S3_RXDMA_Handler, DMA_FLAG_TCIF2_6);

    HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
}

void DMA1_Stream2_IRQHandler(void)
{
    rt_audio_rx_done(&mic_dev.audio, &mic_dev.rx_fifo[0], RX_FIFO_SIZE);
    HAL_DMA_IRQHandler(&I2S3_RXDMA_Handler);
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
            // SAIA_Frequency_Set(caps->udata.config.samplerate);
            HAL_I2S_DMAStop(&I2S3_Handler);
            // SAIB_Channels_Set(caps->udata.config.channels);
            HAL_I2S_Transmit(&I2S3_Handler, (uint16_t *)&zero_frame[0], 2, 0);
            HAL_I2S_Receive_DMA(&I2S3_Handler, (uint16_t *)mic_dev->rx_fifo, RX_FIFO_SIZE / 2);

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

    es8388_init("i2c2", RT_NULL);
    I2S3_Init();
    LOG_I("ES8388 init success.");
    /* set default params */
    // SAIB_Channels_Set(mic_dev->record_config.channels);

    return RT_EOK;
}
static rt_err_t sound_init(struct rt_audio_device *audio)
{
    rt_err_t result = RT_EOK;
    struct sound_device *snd_dev;

    RT_ASSERT(audio != RT_NULL);
    snd_dev = (struct sound_device *)audio->parent.user_data;

    I2S3_Init();
    es8388_init("i2c2", RT_NULL);
    /* set default params */
    // I2S_Frequency_Set(snd_dev->replay_config.samplerate);
    // SAIA_Channels_Set(snd_dev->replay_config.channels);

    return result;
}
static rt_err_t mic_start(struct rt_audio_device *audio, int stream)
{
    struct mic_device *mic_dev;

    RT_ASSERT(audio != RT_NULL);
    mic_dev = (struct mic_device *)audio->parent.user_data;

    if (stream == AUDIO_STREAM_RECORD)
    {
        es8388_start(ES_MODE_ADC);
        HAL_I2S_Transmit(&I2S3_Handler, (uint16_t *)&zero_frame[0], 2, 0);
        // HAL_I2S_Receive_DMA(&I2S3_Handler, (uint16_t *)mic_dev->rx_fifo, RX_FIFO_SIZE / 2);
        while(1)
        {
            HAL_I2S_Receive(&I2S3_Handler, (uint16_t *)mic_dev->rx_fifo, RX_FIFO_SIZE / 2,10);
            for(int i=0;i<RX_FIFO_SIZE;i++)
            {
                rt_kprintf("%x",mic_dev->rx_fifo[i]);
            }
        }
    }

    return RT_EOK;
}

static rt_err_t mic_stop(struct rt_audio_device *audio, int stream)
{
    if (stream == AUDIO_STREAM_RECORD)
    {
        HAL_I2S_DMAStop(&I2S3_Handler);
        es8388_stop(ES_MODE_ADC);
        LOG_D("mic stop.");
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
