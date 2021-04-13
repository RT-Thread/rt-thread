/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-31     Zero-Free    first implementation
 * 2020-07-02     thread-liu   Porting for STM32MP1
 */

#include "board.h"
#include "drv_cs42l51.h"

#ifdef BSP_USING_AUDIO

//#define DRV_DEBUG
#define LOG_TAG             "drv.audio"
#include <drv_log.h>

#define SOUND_BUS_NAME    "i2c4"

/* SYSRAM  */
#define TX_FIFO_SIZE       (4096)
#if defined(__CC_ARM) || defined(__CLANG_ARM)
rt_uint8_t AUDIO_TX_FIFO[TX_FIFO_SIZE] __attribute__((at(0x2FFC3000)));
#elif defined(__ICCARM__)
#pragma location = 0x2FFC3000
rt_uint8_t AUDIO_TX_FIFO[TX_FIFO_SIZE];
#elif defined ( __GNUC__ )
rt_uint8_t AUDIO_TX_FIFO[TX_FIFO_SIZE] __attribute__((at(0x2FFC3000)));
#endif

struct sound_device
{
    struct rt_audio_device audio;
    struct rt_audio_configure replay_config;
    rt_uint8_t *tx_fifo;
    rt_uint8_t volume;
};

static struct sound_device snd_dev = {0};

SAI_HandleTypeDef hsai_BlockA2     = {0};
DMA_HandleTypeDef hdma_sai2_a      = {0};
SAI_HandleTypeDef hsai_BlockB2     = {0};
DMA_HandleTypeDef hdma_sai2_b      = {0};

void HAL_SAI_MspInit(SAI_HandleTypeDef* hsai)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    /* SAI2 */
    if(hsai->Instance==SAI2_Block_A)
    {
        /* Peripheral clock enable */
        if(IS_ENGINEERING_BOOT_MODE())
        {
            /** Initializes the peripherals clock
            */
            PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_SAI2;
            PeriphClkInit.Sai2ClockSelection = RCC_SAI2CLKSOURCE_PLL3_Q;
            if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
            {
                Error_Handler();
            }
        }

        __HAL_RCC_GPIOE_CLK_ENABLE();
        __HAL_RCC_GPIOI_CLK_ENABLE();
        __HAL_RCC_GPIOF_CLK_ENABLE();
        __HAL_RCC_SAI2_CLK_ENABLE();

        /**SAI2_A_Block_A GPIO Configuration
        PE0     ------> SAI2_MCLK_A
        PI7     ------> SAI2_FS_A
        PI5     ------> SAI2_SCK_A
        PI6     ------> SAI2_SD_A
        */
        GPIO_InitStruct.Pin = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_SAI2;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_5|GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_SAI2;
        HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

        /* Configure DMA used for SAI2 */
        __HAL_RCC_DMAMUX_CLK_ENABLE();
        __HAL_RCC_DMA2_CLK_ENABLE();

        hdma_sai2_a.Instance                 = DMA2_Stream5;
        hdma_sai2_a.Init.Request             = DMA_REQUEST_SAI2_A;
        hdma_sai2_a.Init.Direction           = DMA_MEMORY_TO_PERIPH;
        hdma_sai2_a.Init.PeriphInc           = DMA_PINC_DISABLE;
        hdma_sai2_a.Init.MemInc              = DMA_MINC_ENABLE;
        hdma_sai2_a.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
        hdma_sai2_a.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
        hdma_sai2_a.Init.Mode                = DMA_CIRCULAR;
        hdma_sai2_a.Init.Priority            = DMA_PRIORITY_HIGH;
        hdma_sai2_a.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;

        HAL_DMA_DeInit(&hdma_sai2_a);
        if (HAL_DMA_Init(&hdma_sai2_a) != HAL_OK)
        {
          Error_Handler();
        }
        __HAL_LINKDMA(hsai,hdmatx,hdma_sai2_a);
        __HAL_DMA_ENABLE(&hdma_sai2_a);
        HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 2, 0);
        HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);
    }

    if(hsai->Instance==SAI2_Block_B)
    {
          /* Peripheral clock enable */
        if(IS_ENGINEERING_BOOT_MODE())
        {
            /** Initializes the peripherals clock
            */
            PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_SAI2;
            PeriphClkInit.Sai2ClockSelection = RCC_SAI2CLKSOURCE_PLL3_Q;
            if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
            {
              Error_Handler();
            }

        }
        __HAL_RCC_GPIOF_CLK_ENABLE();
        __HAL_RCC_SAI2_CLK_ENABLE();

        /**SAI2_B_Block_B GPIO Configuration
        PF11     ------> SAI2_SD_B
        */
        GPIO_InitStruct.Pin = GPIO_PIN_11;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_SAI2;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

        __HAL_RCC_DMAMUX_CLK_ENABLE();
        __HAL_RCC_DMA2_CLK_ENABLE();

        /* Peripheral DMA init*/
        hdma_sai2_b.Instance                 = DMA2_Stream4;
        hdma_sai2_b.Init.Request             = DMA_REQUEST_SAI2_B;
        hdma_sai2_b.Init.Direction           = DMA_PERIPH_TO_MEMORY;
        hdma_sai2_b.Init.PeriphInc           = DMA_PINC_DISABLE;
        hdma_sai2_b.Init.MemInc              = DMA_MINC_ENABLE;
        hdma_sai2_b.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
        hdma_sai2_b.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
        hdma_sai2_b.Init.Mode                = DMA_CIRCULAR;
        hdma_sai2_b.Init.Priority            = DMA_PRIORITY_HIGH;
        hdma_sai2_b.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
        hdma_sai2_b.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
        hdma_sai2_b.Init.MemBurst            = DMA_MBURST_SINGLE;
        hdma_sai2_b.Init.PeriphBurst         = DMA_PBURST_SINGLE;
        __HAL_LINKDMA(hsai,hdmarx,hdma_sai2_b);
        HAL_DMA_DeInit(&hdma_sai2_b);
        if (HAL_DMA_Init(&hdma_sai2_b) != HAL_OK)
        {
          Error_Handler();
        }
        __HAL_LINKDMA(hsai,hdmarx,hdma_sai2_b);
        __HAL_DMA_ENABLE(&hdma_sai2_b);
        HAL_NVIC_SetPriority(DMA2_Stream4_IRQn, 2, 0);
        HAL_NVIC_EnableIRQ(DMA2_Stream4_IRQn);
    }
}

void HAL_SAI_MspDeInit(SAI_HandleTypeDef* hsai)
{
    /* SAI2 */
    if(hsai->Instance==SAI2_Block_A)
    {

        /* Peripheral clock disable */
        __HAL_RCC_SAI2_CLK_DISABLE();

        /**SAI2_A_Block_A GPIO Configuration
        PE0     ------> SAI2_MCLK_A
        PI7     ------> SAI2_FS_A
        PI5     ------> SAI2_SCK_A
        PI6     ------> SAI2_SD_A
        */
        HAL_GPIO_DeInit(GPIOE, GPIO_PIN_0);

        HAL_GPIO_DeInit(GPIOI, GPIO_PIN_7|GPIO_PIN_5|GPIO_PIN_6);

        HAL_DMA_DeInit(hsai->hdmarx);
        HAL_DMA_DeInit(hsai->hdmatx);
    }

    if(hsai->Instance==SAI2_Block_B)
    {
        /* Peripheral clock disable */
        __HAL_RCC_SAI2_CLK_DISABLE();

        /**SAI2_B_Block_B GPIO Configuration
        PF11     ------> SAI2_SD_B
        */
        HAL_GPIO_DeInit(GPIOF, GPIO_PIN_11);

        HAL_DMA_DeInit(hsai->hdmarx);
        HAL_DMA_DeInit(hsai->hdmatx);
    }
}

static void rt_hw_sai2a_init(void)
{
    HAL_SAI_DeInit(&hsai_BlockA2);
    hsai_BlockA2.Instance                    = SAI2_Block_A;
    hsai_BlockA2.Init.Protocol               = SAI_FREE_PROTOCOL;
    hsai_BlockA2.Init.AudioMode              = SAI_MODEMASTER_TX;
    hsai_BlockA2.Init.DataSize               = SAI_DATASIZE_16;
    hsai_BlockA2.Init.FirstBit               = SAI_FIRSTBIT_MSB;
    hsai_BlockA2.Init.ClockStrobing          = SAI_CLOCKSTROBING_RISINGEDGE;
    hsai_BlockA2.Init.Synchro                = SAI_ASYNCHRONOUS;
    hsai_BlockA2.Init.OutputDrive            = SAI_OUTPUTDRIVE_ENABLE;
    hsai_BlockA2.Init.NoDivider              = SAI_MASTERDIVIDER_ENABLE;
    hsai_BlockA2.Init.FIFOThreshold          = SAI_FIFOTHRESHOLD_EMPTY;
    hsai_BlockA2.Init.AudioFrequency         = SAI_AUDIO_FREQUENCY_44K;
    hsai_BlockA2.Init.SynchroExt             = SAI_SYNCEXT_DISABLE;
    hsai_BlockA2.Init.MonoStereoMode         = SAI_STEREOMODE;
    hsai_BlockA2.Init.CompandingMode         = SAI_NOCOMPANDING;
    hsai_BlockA2.Init.TriState               = SAI_OUTPUT_NOTRELEASED;
    hsai_BlockA2.Init.PdmInit.Activation     = DISABLE;
    hsai_BlockA2.Init.PdmInit.MicPairsNbr    = 0;
    hsai_BlockA2.Init.PdmInit.ClockEnable    = SAI_PDM_CLOCK1_ENABLE;

    hsai_BlockA2.FrameInit.FrameLength       = 64;
    hsai_BlockA2.FrameInit.ActiveFrameLength = 32;
    hsai_BlockA2.FrameInit.FSDefinition      = SAI_FS_CHANNEL_IDENTIFICATION;
    hsai_BlockA2.FrameInit.FSPolarity        = SAI_FS_ACTIVE_LOW;
    hsai_BlockA2.FrameInit.FSOffset          = SAI_FS_BEFOREFIRSTBIT;

    hsai_BlockA2.SlotInit.FirstBitOffset     = 0;
    hsai_BlockA2.SlotInit.SlotSize           = SAI_SLOTSIZE_32B;
    hsai_BlockA2.SlotInit.SlotNumber         = 2;
    hsai_BlockA2.SlotInit.SlotActive         = SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_1;

    if(HAL_OK != HAL_SAI_Init(&hsai_BlockA2))
    {
        Error_Handler();
    }
    /* Enable SAI to generate clock used by audio driver */
    __HAL_SAI_ENABLE(&hsai_BlockA2);
}

void DMA2_Stream5_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_sai2_a);
}

void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
    if (hsai == &hsai_BlockA2)
    {
        rt_audio_tx_complete(&snd_dev.audio);
    }
}

void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai)
{
    if (hsai == &hsai_BlockA2)
    {
        rt_audio_tx_complete(&snd_dev.audio);
    }
}

void SAIA_Frequency_Set(uint32_t frequency)
{
    return;
}

void SAIA_Channels_Set(uint8_t channels)
{
    if (channels == 1)
    {
        hsai_BlockA2.Init.MonoStereoMode = SAI_MONOMODE;
    }
    else
    {
        hsai_BlockA2.Init.MonoStereoMode  = SAI_STEREOMODE;
    }

    __HAL_SAI_DISABLE(&hsai_BlockA2);
    HAL_SAI_Init(&hsai_BlockA2);
    __HAL_SAI_ENABLE(&hsai_BlockA2);
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
            caps->udata.value =  cs42l51_drv.get_volume();
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

            cs42l51_drv.set_volume(volume);

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

    cs42l51_drv.init(OUT_HEADPHONE, SOUND_BUS_NAME, 40);

    if (cs42l51_drv.read_id() != RT_EOK)
    {
        LOG_E("can't find low level audio device!");
        return RT_ERROR;
    }

    rt_hw_sai2a_init();

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

        cs42l51_drv.init(OUT_HEADPHONE, SOUND_BUS_NAME, 60); /* set work mode */
        cs42l51_drv.play();

        if (HAL_SAI_Transmit_DMA(&hsai_BlockA2, snd_dev->tx_fifo, TX_FIFO_SIZE / 2) != HAL_OK)
        {
            return RT_ERROR;
        }
    }

    return RT_EOK;
}

static rt_err_t sound_stop(struct rt_audio_device *audio, int stream)
{
    RT_ASSERT(audio != RT_NULL);

    if (stream == AUDIO_STREAM_REPLAY)
    {
        HAL_SAI_DMAStop(&hsai_BlockA2);
        HAL_SAI_Abort(&hsai_BlockA2);
        cs42l51_drv.stop();

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
    rt_err_t result = RT_EOK;
    struct rt_device *device = RT_NULL;

    rt_memset(AUDIO_TX_FIFO, 0, TX_FIFO_SIZE);
    snd_dev.tx_fifo = AUDIO_TX_FIFO;

    /* init default configuration */
    snd_dev.replay_config.samplerate = 44100;
    snd_dev.replay_config.channels   = 2;
    snd_dev.replay_config.samplebits = 16;
    snd_dev.volume                   = 55;

    /* register sound device */
    snd_dev.audio.ops = &snd_ops;
    result = rt_audio_register(&snd_dev.audio, "sound0", RT_DEVICE_FLAG_WRONLY, &snd_dev);
    if (result != RT_EOK)
    {
        device = &(snd_dev.audio.parent);
        rt_device_unregister(device);
        LOG_E("sound device init error!");
        return RT_ERROR;
    }

    return RT_EOK;
}

INIT_APP_EXPORT(rt_hw_sound_init);

#endif
