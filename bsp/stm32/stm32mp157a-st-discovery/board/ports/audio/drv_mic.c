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

#include <board.h>

#if defined(BSP_USING_AUDIO_RECORD)

#include "drv_cs42l51.h"

//#define DRV_DEBUG
#define DBG_TAG              "drv.audio"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#define MIC_BUS_NAME    "i2c4"

/* SYSRAM  */
#define RX_FIFO_SIZE (4096)
#if defined(__ARMCC_VERSION)
rt_uint8_t MIC_RX_FIFO[RX_FIFO_SIZE] __attribute__((at(0x2FFC2000)));
#elif defined(__ICCARM__)
#pragma location = 0x2FFC2000
rt_uint8_t MIC_RX_FIFO[RX_FIFO_SIZE];
#elif defined ( __GNUC__ )
rt_uint8_t MIC_RX_FIFO[RX_FIFO_SIZE] __attribute__((at(0x2FFC2000)));
#endif

struct mic_device
{
    struct rt_audio_device audio;
    struct rt_audio_configure record_config;
    rt_uint8_t *rx_fifo;
    rt_uint8_t volume;
};

static struct mic_device mic_dev = {0};
static rt_uint16_t zero_frame[2] = {0};

extern SAI_HandleTypeDef hsai_BlockA2;
extern DMA_HandleTypeDef hdma_sai2_a;
extern SAI_HandleTypeDef hsai_BlockB2;
extern DMA_HandleTypeDef hdma_sai2_b;
extern void SAIA_Frequency_Set(uint32_t frequency);

void SAIB_Init(void)
{
    HAL_SAI_DeInit(&hsai_BlockB2);

    hsai_BlockB2.Instance                    = SAI2_Block_B;
    hsai_BlockB2.Init.AudioFrequency         = SAI_AUDIO_FREQUENCY_44K;
    hsai_BlockB2.Init.AudioMode              = SAI_MODESLAVE_RX;
    hsai_BlockB2.Init.Synchro                = SAI_SYNCHRONOUS;
    hsai_BlockB2.Init.OutputDrive            = SAI_OUTPUTDRIVE_ENABLE;
    hsai_BlockB2.Init.NoDivider              = SAI_MASTERDIVIDER_ENABLE;
    hsai_BlockB2.Init.FIFOThreshold          = SAI_FIFOTHRESHOLD_1QF;
    hsai_BlockB2.Init.Mckdiv                 = 0;
    hsai_BlockB2.Init.MckOverSampling        = SAI_MCK_OVERSAMPLING_DISABLE;
    hsai_BlockB2.Init.MonoStereoMode         = SAI_STEREOMODE;
    hsai_BlockB2.Init.CompandingMode         = SAI_NOCOMPANDING;
    hsai_BlockB2.Init.TriState               = SAI_OUTPUT_NOTRELEASED;
    hsai_BlockB2.Init.PdmInit.Activation     = DISABLE;
    hsai_BlockB2.Init.PdmInit.MicPairsNbr    = 1;
    hsai_BlockB2.Init.PdmInit.ClockEnable    = SAI_PDM_CLOCK1_ENABLE;
    hsai_BlockB2.Init.Protocol               = SAI_FREE_PROTOCOL;
    hsai_BlockB2.Init.DataSize               = SAI_DATASIZE_16;
    hsai_BlockB2.Init.FirstBit               = SAI_FIRSTBIT_MSB;
    hsai_BlockB2.Init.ClockStrobing          = SAI_CLOCKSTROBING_RISINGEDGE;

    hsai_BlockB2.FrameInit.FrameLength       = 64;
    hsai_BlockB2.FrameInit.ActiveFrameLength = 32;
    hsai_BlockB2.FrameInit.FSDefinition      = SAI_FS_CHANNEL_IDENTIFICATION;
    hsai_BlockB2.FrameInit.FSPolarity        = SAI_FS_ACTIVE_LOW;
    hsai_BlockB2.FrameInit.FSOffset          = SAI_FS_BEFOREFIRSTBIT;

    hsai_BlockB2.SlotInit.FirstBitOffset     = 0;
    hsai_BlockB2.SlotInit.SlotSize           = SAI_SLOTSIZE_32B;
    hsai_BlockB2.SlotInit.SlotNumber         = 2;
    hsai_BlockB2.SlotInit.SlotActive         = SAI_SLOTACTIVE_0|SAI_SLOTACTIVE_1;

    /* DeInit SAI PDM input */
    HAL_SAI_DeInit(&hsai_BlockB2);

    /* Init SAI PDM input */
    if(HAL_OK != HAL_SAI_Init(&hsai_BlockB2))
    {
        Error_Handler();
    }

    /* Enable SAI to generate clock used by audio driver */
    __HAL_SAI_ENABLE(&hsai_BlockB2);
}

void SAIB_Channels_Set(uint8_t channels)
{
    if (channels == 1)
    {
        hsai_BlockB2.Init.MonoStereoMode = SAI_MONOMODE;
    }
    else
    {
        hsai_BlockB2.Init.MonoStereoMode = SAI_STEREOMODE;
    }

    __HAL_SAI_DISABLE(&hsai_BlockB2);
    HAL_SAI_Init(&hsai_BlockB2);
    __HAL_SAI_ENABLE(&hsai_BlockB2);
}

void DMA2_Stream4_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_sai2_b);
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
            HAL_SAI_DMAStop(&hsai_BlockB2);
            SAIB_Channels_Set(caps->udata.config.channels);
            HAL_SAI_Transmit(&hsai_BlockA2, (uint8_t *)&zero_frame[0], 2, 0);
            HAL_SAI_Receive_DMA(&hsai_BlockB2, mic_dev->rx_fifo, RX_FIFO_SIZE / 2);

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
            mic_dev->record_config.channels = caps->udata.config.channels;
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
        cs42l51_drv.init(IN_MIC1, MIC_BUS_NAME, 40);
        /* open receive */
        if (HAL_SAI_Receive_DMA(&hsai_BlockB2, mic_dev->rx_fifo, RX_FIFO_SIZE / 2) != HAL_OK)
        {
            return -RT_ERROR;
        }
        /* supply clk */
        HAL_SAI_Transmit(&hsai_BlockA2, (uint8_t *)&zero_frame[0], 2, 0);

        cs42l51_drv.play();
    }

    return RT_EOK;
}

static rt_err_t mic_stop(struct rt_audio_device *audio, int stream)
{
    if (stream == AUDIO_STREAM_RECORD)
    {
        HAL_SAI_DMAStop(&hsai_BlockB2);
        HAL_SAI_Abort(&hsai_BlockB2);
        cs42l51_drv.stop();
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
    rt_err_t result = RT_EOK;
    struct rt_device *device;

    rt_memset(MIC_RX_FIFO, 0, RX_FIFO_SIZE);
    mic_dev.rx_fifo = MIC_RX_FIFO;

    /* init default configuration */
    {
        mic_dev.record_config.samplerate = 44100;
        mic_dev.record_config.channels   = 2;
        mic_dev.record_config.samplebits = 16;
        mic_dev.volume                   = 55;
    }

    /* register sound device */
    mic_dev.audio.ops = &mic_ops;
    result = rt_audio_register(&mic_dev.audio, "mic0", RT_DEVICE_FLAG_RDONLY, &mic_dev);

    if (result != RT_EOK)
    {
        device = &(mic_dev.audio.parent);
        rt_device_unregister(device);
        LOG_E("mic device init error!");
        return -RT_ERROR;
    }

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_mic_init);

#endif
