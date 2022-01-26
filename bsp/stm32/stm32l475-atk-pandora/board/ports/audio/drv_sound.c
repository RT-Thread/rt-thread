/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2019-07-31     Zero-Free    first implementation
 */

#include <board.h>

#include "drv_sound.h"
#include "drv_es8388.h"

#define DBG_TAG              "drv.sound"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#define TX_FIFO_SIZE         (2048)

struct sound_device
{
    struct rt_audio_device audio;
    struct rt_audio_configure replay_config;
    rt_uint8_t *tx_fifo;
    rt_uint8_t volume;
};

static struct sound_device snd_dev = {0};
SAI_HandleTypeDef SAI1A_Handler = {0};
DMA_HandleTypeDef SAI1_TXDMA_Handler = {0};

static void SAIA_Init(void)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /* Configure and enable PLLSAI1 clock to generate 45.714286MHz */
    PeriphClkInit.PeriphClockSelection        = RCC_PERIPHCLK_SAI1;
    PeriphClkInit.Sai1ClockSelection          = RCC_SAI1CLKSOURCE_PLLSAI2;
    PeriphClkInit.PLLSAI2.PLLSAI2Source       = RCC_PLLSOURCE_HSE;
    PeriphClkInit.PLLSAI2.PLLSAI2M            = 1;
    PeriphClkInit.PLLSAI2.PLLSAI2N            = 40;
    PeriphClkInit.PLLSAI2.PLLSAI2P            = RCC_PLLP_DIV7;
    PeriphClkInit.PLLSAI2.PLLSAI2R            = RCC_PLLR_DIV2;
    PeriphClkInit.PLLSAI2.PLLSAI2ClockOut     = RCC_PLLSAI2_SAI2CLK;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

    HAL_SAI_DeInit(&SAI1A_Handler);
    SAI1A_Handler.Init.AudioFrequency         = SAI_AUDIO_FREQUENCY_44K;
    SAI1A_Handler.Instance                    = SAI1_Block_A;
    SAI1A_Handler.Init.AudioMode              = SAI_MODEMASTER_TX;
    SAI1A_Handler.Init.Synchro                = SAI_ASYNCHRONOUS;
    SAI1A_Handler.Init.OutputDrive            = SAI_OUTPUTDRIVE_ENABLE;
    SAI1A_Handler.Init.NoDivider              = SAI_MASTERDIVIDER_ENABLE;
    SAI1A_Handler.Init.FIFOThreshold          = SAI_FIFOTHRESHOLD_EMPTY;
    SAI1A_Handler.Init.MonoStereoMode         = SAI_STEREOMODE;
    SAI1A_Handler.Init.Protocol               = SAI_FREE_PROTOCOL;
    SAI1A_Handler.Init.DataSize               = SAI_DATASIZE_16;
    SAI1A_Handler.Init.FirstBit               = SAI_FIRSTBIT_MSB;
    SAI1A_Handler.Init.ClockStrobing          = SAI_CLOCKSTROBING_RISINGEDGE;

    SAI1A_Handler.FrameInit.FrameLength       = 64;
    SAI1A_Handler.FrameInit.ActiveFrameLength = 32;
    SAI1A_Handler.FrameInit.FSDefinition      = SAI_FS_CHANNEL_IDENTIFICATION;
    SAI1A_Handler.FrameInit.FSPolarity        = SAI_FS_ACTIVE_LOW;
    SAI1A_Handler.FrameInit.FSOffset          = SAI_FS_BEFOREFIRSTBIT;
    SAI1A_Handler.SlotInit.FirstBitOffset     = 0;
    SAI1A_Handler.SlotInit.SlotSize           = SAI_SLOTSIZE_32B;
    SAI1A_Handler.SlotInit.SlotNumber         = 2;
    SAI1A_Handler.SlotInit.SlotActive         = SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_1;

    HAL_SAI_Init(&SAI1A_Handler);
    __HAL_SAI_ENABLE(&SAI1A_Handler);

    /* Configure DMA used for SAI1 */
    __HAL_RCC_DMA2_CLK_ENABLE();

    SAI1_TXDMA_Handler.Init.Request             = DMA_REQUEST_1;
    SAI1_TXDMA_Handler.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    SAI1_TXDMA_Handler.Init.PeriphInc           = DMA_PINC_DISABLE;
    SAI1_TXDMA_Handler.Init.MemInc              = DMA_MINC_ENABLE;
    SAI1_TXDMA_Handler.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    SAI1_TXDMA_Handler.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
    SAI1_TXDMA_Handler.Init.Mode                = DMA_CIRCULAR;
    SAI1_TXDMA_Handler.Init.Priority            = DMA_PRIORITY_HIGH;
    SAI1_TXDMA_Handler.Instance                 = DMA2_Channel1;
    __HAL_LINKDMA(&SAI1A_Handler, hdmatx, SAI1_TXDMA_Handler);
    HAL_DMA_DeInit(&SAI1_TXDMA_Handler);
    HAL_DMA_Init(&SAI1_TXDMA_Handler);
    __HAL_DMA_ENABLE(&SAI1_TXDMA_Handler);

    HAL_NVIC_SetPriority(DMA2_Channel1_IRQn, 0x01, 0);
    HAL_NVIC_EnableIRQ(DMA2_Channel1_IRQn);
}

void DMA2_Channel1_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&SAI1_TXDMA_Handler);
}

void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
    if (hsai == &SAI1A_Handler)
    {
        rt_audio_tx_complete(&snd_dev.audio);
    }
}

void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai)
{
    if (hsai == &SAI1A_Handler)
    {
        rt_audio_tx_complete(&snd_dev.audio);
    }
}

void SAIA_Frequency_Set(uint32_t frequency)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInit;

    HAL_RCCEx_GetPeriphCLKConfig(&PeriphClkInit);

    if ((frequency == SAI_AUDIO_FREQUENCY_11K) || (frequency == SAI_AUDIO_FREQUENCY_22K) || (frequency == SAI_AUDIO_FREQUENCY_44K))
    {
        /* Configure and enable PLLSAI1 clock to generate 45.714286MHz */
        PeriphClkInit.PeriphClockSelection      = RCC_PERIPHCLK_SAI1;
        PeriphClkInit.Sai1ClockSelection        = RCC_SAI1CLKSOURCE_PLLSAI2;
        PeriphClkInit.PLLSAI2.PLLSAI2Source     = RCC_PLLSOURCE_HSE;
        PeriphClkInit.PLLSAI2.PLLSAI2M          = 1;
        PeriphClkInit.PLLSAI2.PLLSAI2N          = 40;
        PeriphClkInit.PLLSAI2.PLLSAI2ClockOut   = RCC_PLLSAI2_SAI2CLK;

        HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
    }
    else
    {
        /* Configure and enable PLLSAI1 clock to generate 49.142857MHz */
        PeriphClkInit.PeriphClockSelection      = RCC_PERIPHCLK_SAI1;
        PeriphClkInit.Sai1ClockSelection        = RCC_SAI1CLKSOURCE_PLLSAI2;
        PeriphClkInit.PLLSAI2.PLLSAI2Source     = RCC_PLLSOURCE_HSE;
        PeriphClkInit.PLLSAI2.PLLSAI2M          = 1;
        PeriphClkInit.PLLSAI2.PLLSAI2N          = 43;
        PeriphClkInit.PLLSAI2.PLLSAI2P          = RCC_PLLP_DIV7;
        PeriphClkInit.PLLSAI2.PLLSAI2ClockOut   = RCC_PLLSAI2_SAI2CLK;

        HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
    }

    /* Disable SAI peripheral to allow access to SAI internal registers */
    __HAL_SAI_DISABLE(&SAI1A_Handler);
    /* Update the SAI audio frequency configuration */
    SAI1A_Handler.Init.AudioFrequency         = frequency;
    HAL_SAI_Init(&SAI1A_Handler);
    /* Enable SAI peripheral to generate MCLK */
    __HAL_SAI_ENABLE(&SAI1A_Handler);
}

void SAIA_Channels_Set(uint8_t channels)
{
    if (channels == 1)
    {
        SAI1A_Handler.Init.MonoStereoMode         = SAI_MONOMODE;
    }
    else
    {
        SAI1A_Handler.Init.MonoStereoMode         = SAI_STEREOMODE;
    }

    __HAL_SAI_DISABLE(&SAI1A_Handler);
    HAL_SAI_Init(&SAI1A_Handler);
    __HAL_SAI_ENABLE(&SAI1A_Handler);
}

/**
 * RT-Thread Audio Device Driver Interface
 */
static rt_err_t sound_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    struct sound_device *snd_dev;

    RT_ASSERT(audio != RT_NULL);
    snd_dev = (struct sound_device *)audio->parent.user_data;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_QUERY: /* qurey the types of hw_codec device */
    {
        switch (caps->sub_type)
        {
        case AUDIO_TYPE_QUERY:
            caps->udata.mask = AUDIO_TYPE_OUTPUT | AUDIO_TYPE_MIXER;
            break;

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    case AUDIO_TYPE_OUTPUT: /* Provide capabilities of OUTPUT unit */
    {
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            caps->udata.config.samplerate   = snd_dev->replay_config.samplerate;
            caps->udata.config.channels     = snd_dev->replay_config.channels;
            caps->udata.config.samplebits   = snd_dev->replay_config.samplebits;
            break;

        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate   = snd_dev->replay_config.samplerate;
            break;

        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels     = snd_dev->replay_config.channels;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits   = snd_dev->replay_config.samplebits;
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
            caps->udata.mask = AUDIO_MIXER_VOLUME;
            break;

        case AUDIO_MIXER_VOLUME:
            caps->udata.value =  es8388_volume_get();
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

static rt_err_t sound_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    struct sound_device *snd_dev;

    RT_ASSERT(audio != RT_NULL);
    snd_dev = (struct sound_device *)audio->parent.user_data;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_MIXER:
    {
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_VOLUME:
        {
            rt_uint8_t volume = caps->udata.value;

            es8388_volume_set(volume);
            snd_dev->volume = volume;
            LOG_D("set volume %d", volume);
            break;
        }

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    case AUDIO_TYPE_OUTPUT:
    {
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
        {
            /* set samplerate */
            SAIA_Frequency_Set(caps->udata.config.samplerate);
            /* set channels */
            SAIA_Channels_Set(caps->udata.config.channels);

            /* save configs */
            snd_dev->replay_config.samplerate = caps->udata.config.samplerate;
            snd_dev->replay_config.channels   = caps->udata.config.channels;
            snd_dev->replay_config.samplebits = caps->udata.config.samplebits;
            LOG_D("set samplerate %d", snd_dev->replay_config.samplerate);
            break;
        }

        case AUDIO_DSP_SAMPLERATE:
        {
            SAIA_Frequency_Set(caps->udata.config.samplerate);
            snd_dev->replay_config.samplerate = caps->udata.config.samplerate;
            LOG_D("set samplerate %d", snd_dev->replay_config.samplerate);
            break;
        }

        case AUDIO_DSP_CHANNELS:
        {
            SAIA_Channels_Set(caps->udata.config.channels);
            snd_dev->replay_config.channels   = caps->udata.config.channels;
            LOG_D("set channels %d", snd_dev->replay_config.channels);
            break;
        }

        case AUDIO_DSP_SAMPLEBITS:
        {
            /* not support */
            snd_dev->replay_config.samplebits = caps->udata.config.samplebits;
            break;
        }

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    default:
        break;
    }

    return result;
}

static rt_err_t sound_init(struct rt_audio_device *audio)
{
    rt_err_t result = RT_EOK;
    struct sound_device *snd_dev;

    RT_ASSERT(audio != RT_NULL);
    snd_dev = (struct sound_device *)audio->parent.user_data;

    es8388_init("i2c3", GET_PIN(A, 5));
    SAIA_Init();

    /* set default params */
    SAIA_Frequency_Set(snd_dev->replay_config.samplerate);
    SAIA_Channels_Set(snd_dev->replay_config.channels);

    return result;
}

static rt_err_t sound_start(struct rt_audio_device *audio, int stream)
{
    struct sound_device *snd_dev;

    RT_ASSERT(audio != RT_NULL);
    snd_dev = (struct sound_device *)audio->parent.user_data;

    if (stream == AUDIO_STREAM_REPLAY)
    {
        LOG_D("open sound device");
        es8388_start(ES_MODE_DAC);
        HAL_SAI_Transmit_DMA(&SAI1A_Handler, snd_dev->tx_fifo, TX_FIFO_SIZE / 2);
    }

    return RT_EOK;
}

static rt_err_t sound_stop(struct rt_audio_device *audio, int stream)
{
    RT_ASSERT(audio != RT_NULL);

    if (stream == AUDIO_STREAM_REPLAY)
    {
        HAL_SAI_DMAStop(&SAI1A_Handler);
        es8388_stop(ES_MODE_DAC);
        LOG_D("close sound device");
    }

    return RT_EOK;
}

static void sound_buffer_info(struct rt_audio_device *audio, struct rt_audio_buf_info *info)
{
    struct sound_device *snd_dev;

    RT_ASSERT(audio != RT_NULL);
    snd_dev = (struct sound_device *)audio->parent.user_data;

    /**
     *               TX_FIFO
     * +----------------+----------------+
     * |     block1     |     block2     |
     * +----------------+----------------+
     *  \  block_size  /
     */
    info->buffer      = snd_dev->tx_fifo;
    info->total_size  = TX_FIFO_SIZE;
    info->block_size  = TX_FIFO_SIZE / 2;
    info->block_count = 2;
}

static struct rt_audio_ops snd_ops =
{
    .getcaps     = sound_getcaps,
    .configure   = sound_configure,
    .init        = sound_init,
    .start       = sound_start,
    .stop        = sound_stop,
    .transmit    = RT_NULL,
    .buffer_info = sound_buffer_info,
};

int rt_hw_sound_init(void)
{
    rt_uint8_t *tx_fifo;

    if (snd_dev.tx_fifo)
        return RT_EOK;

    tx_fifo = rt_malloc(TX_FIFO_SIZE);
    if (tx_fifo == RT_NULL)
        return -RT_ENOMEM;
    rt_memset(tx_fifo, 0, TX_FIFO_SIZE);
    snd_dev.tx_fifo = tx_fifo;

    /* init default configuration */
    {
        snd_dev.replay_config.samplerate = 44100;
        snd_dev.replay_config.channels   = 2;
        snd_dev.replay_config.samplebits = 16;
        snd_dev.volume                   = 55;
    }

    /* register sound device */
    snd_dev.audio.ops = &snd_ops;
    rt_audio_register(&snd_dev.audio, "sound0", RT_DEVICE_FLAG_WRONLY, &snd_dev);

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_sound_init);
