/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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
#define DBG_LVL              DBG_LOG
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
static I2S_HandleTypeDef I2S3_Handler = {0};
static DMA_HandleTypeDef I2S3_TXDMA_Handler = {0};

/**
 * 采样率计算公式:Fs=I2SxCLK/[256*(2*I2SDIV+ODD)]
 * I2SxCLK=(HSE/pllm)*PLLI2SN/PLLI2SR
 * 一般HSE=8Mhz
 * pllm:在Sys_Clock_Set设置的时候确定，一般是8
 * PLLI2SN:一般是192~432
 * PLLI2SR:2~7
 * I2SDIV:2~255
 * ODD:0/1
 * I2S分频系数表@pllm=8,HSE=8Mhz,即vco输入频率为1Mhz
 * 表格式:采样率/10,PLLI2SN,PLLI2SR,I2SDIV,ODD
 */
const uint16_t I2S_PSC_TBL[][5]=
{
    {   800, 256, 5, 12, 1 },   /* 8Khz采样率 */
    {  1102, 429, 4, 19, 0 },   /* 11.025Khz采样率 */
    {  1600, 213, 2, 13, 0 },   /* 16Khz采样率 */
    {  2205, 429, 4,  9, 1 },   /* 22.05Khz采样率 */
    {  3200, 213, 2,  6, 1 },   /* 32Khz采样率 */
    {  4410, 271, 2,  6, 0 },   /* 44.1Khz采样率 */
    {  4800, 258, 3,  3, 1 },   /* 48Khz采样率 */
    {  8820, 316, 2,  3, 1 },   /* 88.2Khz采样率 */
    {  9600, 344, 2,  3, 1 },   /* 96Khz采样率 */
    { 17640, 361, 2,  2, 0 },   /* 176.4Khz采样率 */
    { 19200, 393, 2,  2, 0 },   /* 192Khz采样率 */
};


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

    I2S3_Handler.Instance = SPI3;
    I2S3_Handler.Init.Mode = I2S_MODE_MASTER_TX;
    I2S3_Handler.Init.Standard = I2S_STANDARD_PHILIPS;
    I2S3_Handler.Init.DataFormat = I2S_DATAFORMAT_16B;
    I2S3_Handler.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
    I2S3_Handler.Init.AudioFreq = I2S_AUDIOFREQ_44K;
    I2S3_Handler.Init.CPOL = I2S_CPOL_LOW;
    I2S3_Handler.Init.ClockSource = I2S_CLOCK_PLL;
    I2S3_Handler.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_ENABLE;
    if (HAL_I2S_Init(&I2S3_Handler) != HAL_OK)
    {
        Error_Handler();
    }

    SET_BIT(I2S3_Handler.Instance->CR2, SPI_CR2_TXDMAEN);
    __HAL_I2S_ENABLE(&I2S3_Handler);

    /* Configure DMA used for I2S3 */
    __HAL_RCC_DMA1_CLK_ENABLE();
    I2S3_TXDMA_Handler.Instance = DMA1_Stream7;
    I2S3_TXDMA_Handler.Init.Channel = DMA_CHANNEL_0;
    I2S3_TXDMA_Handler.Init.Direction = DMA_MEMORY_TO_PERIPH;
    I2S3_TXDMA_Handler.Init.PeriphInc = DMA_PINC_DISABLE;
    I2S3_TXDMA_Handler.Init.MemInc = DMA_MINC_ENABLE;
    I2S3_TXDMA_Handler.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    I2S3_TXDMA_Handler.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    I2S3_TXDMA_Handler.Init.Mode = DMA_CIRCULAR;
    I2S3_TXDMA_Handler.Init.Priority = DMA_PRIORITY_HIGH;
    I2S3_TXDMA_Handler.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

    __HAL_LINKDMA(&I2S3_Handler,hdmatx,I2S3_TXDMA_Handler);
    HAL_DMA_DeInit(&I2S3_TXDMA_Handler);
    HAL_DMA_Init(&I2S3_TXDMA_Handler);
    // __HAL_DMA_ENABLE(&I2S3_TXDMA_Handler);

    __HAL_DMA_DISABLE(&I2S3_TXDMA_Handler);
    __HAL_DMA_ENABLE_IT(&I2S3_TXDMA_Handler, DMA_IT_TC);                   /* 开启传输完成中断 */
    __HAL_DMA_CLEAR_FLAG(&I2S3_TXDMA_Handler, DMA_FLAG_TCIF0_4);

    HAL_NVIC_SetPriority(DMA1_Stream7_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);
}

void DMA1_Stream7_IRQHandler(void)
{
    rt_audio_tx_complete(&snd_dev.audio);
    HAL_DMA_IRQHandler(&I2S3_TXDMA_Handler);
}


//void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai)
//{
//    if (hsai == &SAI1A_Handler)
//    {
//        rt_audio_tx_complete(&snd_dev.audio);
//    }
//}

//void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai)
//{
//    if (hsai == &SAI1A_Handler)
//    {
//        rt_audio_tx_complete(&snd_dev.audio);
//    }
//}

void I2S_Frequency_Set(uint32_t samplerate)
{

    // uint8_t i = 0;
    // uint32_t tempreg = 0;

    // RCC_PeriphCLKInitTypeDef rcc_i2s_clkinit_struct;

    // for (i = 0; i < (sizeof(I2S_PSC_TBL) / 10); i++)    /* 看看改采样率是否可以支持 */
    // {
    //     if ((samplerate / 10) == I2S_PSC_TBL[i][0])
    //     {
    //         break;
    //     }
    // }
    // if (i == (sizeof(I2S_PSC_TBL) / 10))
    // {
    //     LOG_E("samplerate not supported.");
    //     // return 1;   /* 找不到 */
    // }

    // rcc_i2s_clkinit_struct.PeriphClockSelection = RCC_PERIPHCLK_I2S;        /* 外设时钟源选择 */
    // rcc_i2s_clkinit_struct.PLLI2S.PLLI2SN = (uint32_t)I2S_PSC_TBL[i][1];    /* 设置PLLI2SN */
    // rcc_i2s_clkinit_struct.PLLI2S.PLLI2SR = (uint32_t)I2S_PSC_TBL[i][2];    /* 设置PLLI2SR */
    // HAL_RCCEx_PeriphCLKConfig(&rcc_i2s_clkinit_struct);                     /* 设置时钟 */

    // RCC->CR |= 1 << 26;                 /* 开启I2S时钟 */
    // while((RCC->CR & 1 << 27) == 0);    /* 等待I2S时钟开启成功. */
    // tempreg = I2S_PSC_TBL[i][3] << 0;   /* 设置I2SDIV */
    // tempreg |= I2S_PSC_TBL[i][4] << 8;  /* 设置ODD位 */
    // tempreg |= 1 << 9;                  /* 使能MCKOE位,输出MCK */
    // I2S3_Handler.Instance->I2SPR = tempreg;           /* 设置I2SPR寄存器 */

    // return 0;

//    RCC_PeriphCLKInitTypeDef PeriphClkInit;

//    HAL_RCCEx_GetPeriphCLKConfig(&PeriphClkInit);

//    if ((frequency == SAI_AUDIO_FREQUENCY_11K) || (frequency == SAI_AUDIO_FREQUENCY_22K) || (frequency == SAI_AUDIO_FREQUENCY_44K))
//    {
//        /* Configure and enable PLLSAI1 clock to generate 45.714286MHz */
//        PeriphClkInit.PeriphClockSelection      = RCC_PERIPHCLK_SAI1;
//        PeriphClkInit.Sai1ClockSelection        = RCC_SAI1CLKSOURCE_PLLSAI2;
//        PeriphClkInit.PLLSAI2.PLLSAI2Source     = RCC_PLLSOURCE_HSE;
//        PeriphClkInit.PLLSAI2.PLLSAI2M          = 1;
//        PeriphClkInit.PLLSAI2.PLLSAI2N          = 40;
//        PeriphClkInit.PLLSAI2.PLLSAI2ClockOut   = RCC_PLLSAI2_SAI2CLK;

//        HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
//    }
//    else
//    {
//        /* Configure and enable PLLSAI1 clock to generate 49.142857MHz */
//        PeriphClkInit.PeriphClockSelection      = RCC_PERIPHCLK_SAI1;
//        PeriphClkInit.Sai1ClockSelection        = RCC_SAI1CLKSOURCE_PLLSAI2;
//        PeriphClkInit.PLLSAI2.PLLSAI2Source     = RCC_PLLSOURCE_HSE;
//        PeriphClkInit.PLLSAI2.PLLSAI2M          = 1;
//        PeriphClkInit.PLLSAI2.PLLSAI2N          = 43;
//        PeriphClkInit.PLLSAI2.PLLSAI2P          = RCC_PLLP_DIV7;
//        PeriphClkInit.PLLSAI2.PLLSAI2ClockOut   = RCC_PLLSAI2_SAI2CLK;

//        HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
//    }

//    /* Disable SAI peripheral to allow access to SAI internal registers */
//    __HAL_SAI_DISABLE(&SAI1A_Handler);
//    /* Update the SAI audio frequency configuration */
//    SAI1A_Handler.Init.AudioFrequency         = frequency;
//    HAL_SAI_Init(&SAI1A_Handler);
//    /* Enable SAI peripheral to generate MCLK */
//    __HAL_SAI_ENABLE(&SAI1A_Handler);
}

void SAIA_Channels_Set(uint8_t channels)
{
    // if (channels == 1)
    // {
    //     SAI1A_Handler.Init.MonoStereoMode         = SAI_MONOMODE;
    // }
    // else
    // {
    //     SAI1A_Handler.Init.MonoStereoMode         = SAI_STEREOMODE;
    // }

    // __HAL_SAI_DISABLE(&SAI1A_Handler);
    // HAL_SAI_Init(&SAI1A_Handler);
    // __HAL_SAI_ENABLE(&SAI1A_Handler);
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
            I2S_Frequency_Set(caps->udata.config.samplerate);
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
            I2S_Frequency_Set(caps->udata.config.samplerate);
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

    es8388_init("i2c2", RT_NULL);
    I2S3_Init();
    LOG_I("ES8388 init success.");
    /* set default params */
    I2S_Frequency_Set(snd_dev->replay_config.samplerate);
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
        LOG_D("sound start.");
        es8388_start(ES_MODE_DAC);
        HAL_I2S_Transmit_DMA(&I2S3_Handler, (uint16_t*)snd_dev->tx_fifo, TX_FIFO_SIZE / 2);
    }

    return RT_EOK;
}

static rt_err_t sound_stop(struct rt_audio_device *audio, int stream)
{
    RT_ASSERT(audio != RT_NULL);

    if (stream == AUDIO_STREAM_REPLAY)
    {
        HAL_I2S_DMAStop(&I2S3_Handler);
        es8388_stop(ES_MODE_DAC);
        LOG_D("sound stop.");
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

// INIT_DEVICE_EXPORT(rt_hw_sound_init);
