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

#ifdef BSP_USING_AUDIO
#include "drv_wm8994.h"
#include <dfs_posix.h>

#define DRV_DEBUG
#define LOG_TAG             "drv.sound"
#include <drv_log.h>

#define SOUND_BUS_NAME       "i2c2"

#define TX_FIFO_SIZE         (4096)
#if defined(__CC_ARM) || defined(__CLANG_ARM)
__attribute__((at(0x2FFC2000))) static rt_uint8_t AUDIO_TX_FIFO[TX_FIFO_SIZE];
#elif defined ( __GNUC__ )
static rt_uint8_t AUDIO_TX_FIFO[TX_FIFO_SIZE] __attribute__((section(".AudioSection")));
#elif defined(__ICCARM__)
#pragma location = 0x2FFC2000
__no_init static rt_uint8_t AUDIO_TX_FIFO[TX_FIFO_SIZE];
#endif

struct sound_device
{
    struct rt_audio_device audio;
    struct rt_audio_configure replay_config;
    rt_device_t decoder;
    rt_uint8_t *tx_fifo;
    rt_uint8_t volume;
};
static struct sound_device snd_dev = {0};

SAI_HandleTypeDef hsai_BlockA2 = {0};
extern DMA_HandleTypeDef hdma_sai2_a;

static void rt_hw_sai2a_init(void)
{
    hsai_BlockA2.Instance                    = SAI2_Block_A;
    hsai_BlockA2.Init.Protocol               = SAI_FREE_PROTOCOL;
    hsai_BlockA2.Init.AudioMode              = SAI_MODEMASTER_TX;
    hsai_BlockA2.Init.DataSize               = SAI_DATASIZE_16;
    hsai_BlockA2.Init.FirstBit               = SAI_FIRSTBIT_MSB;
    hsai_BlockA2.Init.ClockStrobing          = SAI_CLOCKSTROBING_FALLINGEDGE;
    hsai_BlockA2.Init.Synchro                = SAI_ASYNCHRONOUS;
    hsai_BlockA2.Init.OutputDrive            = SAI_OUTPUTDRIVE_ENABLE;
    hsai_BlockA2.Init.NoDivider              = SAI_MASTERDIVIDER_ENABLE;
    hsai_BlockA2.Init.FIFOThreshold          = SAI_FIFOTHRESHOLD_1QF;
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
    hsai_BlockA2.SlotInit.SlotSize           = SAI_SLOTSIZE_DATASIZE;
    hsai_BlockA2.SlotInit.SlotNumber         = 2;
    hsai_BlockA2.SlotInit.SlotActive         = (SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_1 | SAI_SLOTACTIVE_2 | SAI_SLOTACTIVE_3);

    if(HAL_OK != HAL_SAI_Init(&hsai_BlockA2))
    {
        Error_Handler();
    }
    /* Enable SAI to generate clock used by audio driver */
    __HAL_SAI_ENABLE(&hsai_BlockA2);
}

void DMA1_Stream0_IRQHandler(void)
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
    /* Disable SAI peripheral to allow access to SAI internal registers */
    __HAL_SAI_DISABLE(&hsai_BlockA2);
    /* Update the SAI audio frequency configuration */
    hsai_BlockA2.Init.AudioFrequency = frequency;
    HAL_SAI_Init(&hsai_BlockA2);
    /* Enable SAI peripheral to generate MCLK */
    __HAL_SAI_ENABLE(&hsai_BlockA2);
}

void SAIA_Channels_Set(uint8_t channels)
{
    if (channels == 1)
    {
        hsai_BlockA2.Init.MonoStereoMode = SAI_MONOMODE;
    }
    else
    {
        hsai_BlockA2.Init.MonoStereoMode = SAI_STEREOMODE;
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
            caps->udata.config.samplerate  = snd_dev->replay_config.samplerate;
            caps->udata.config.channels    = snd_dev->replay_config.channels;
            caps->udata.config.samplebits  = snd_dev->replay_config.samplebits;
            break;

        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate = snd_dev->replay_config.samplerate;
            break;

        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels = snd_dev->replay_config.channels;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits = snd_dev->replay_config.samplebits;
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
            rt_device_control(snd_dev->decoder, GET_VOLUME, &(caps->udata.value));
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

            rt_device_control(snd_dev->decoder, SET_VOLUME, &volume);

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
            snd_dev->replay_config.channels = caps->udata.config.channels;
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
    rt_uint16_t play_type = OUTPUT_DEVICE_HEADPHONE;

    RT_ASSERT(audio != RT_NULL);
    snd_dev = (struct sound_device *)audio->parent.user_data;

    rt_hw_sai2a_init();

    /* set default params */
    SAIA_Frequency_Set(snd_dev->replay_config.samplerate);
    SAIA_Channels_Set(snd_dev->replay_config.channels);

    /* set audio play type */
    rt_device_control(snd_dev->decoder, SET_PLAY_TYPE, &play_type);
    /* open lowlevel audio device */
    rt_device_open(snd_dev->decoder, RT_DEVICE_OFLAG_WRONLY);
    rt_device_init(snd_dev->decoder);
    /* check device id */
    result = rt_device_control(snd_dev->decoder, GET_ID, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("can't find low level audio device!");
        return RT_ERROR;
    }

    return result;
}

static rt_err_t sound_start(struct rt_audio_device *audio, int stream)
{
    struct sound_device *snd_dev;
    rt_uint16_t play_type = OUTPUT_DEVICE_HEADPHONE;

    RT_ASSERT(audio != RT_NULL);
    snd_dev = (struct sound_device *)audio->parent.user_data;

    if (stream == AUDIO_STREAM_REPLAY)
    {
        LOG_D("open sound device");

        rt_device_control(snd_dev->decoder, SET_PLAY_TYPE, &play_type);
        rt_device_control(snd_dev->decoder, START_PLAY, RT_NULL);

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

        LOG_D("close sound device");
    }

    return RT_EOK;
}

static void sound_buffer_info(struct rt_audio_device *audio, struct rt_audio_buf_info *info)
{
    struct sound_device *device;

    RT_ASSERT(audio != RT_NULL);
    device = (struct sound_device *)audio->parent.user_data;

    info->buffer      = device->tx_fifo;
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

    /* find lowlevel decoder device*/
    snd_dev.decoder = rt_device_find("decoder");
    if (snd_dev.decoder == RT_NULL)
    {
        LOG_E("cant't find lowlevel decoder deivce!");
        return RT_ERROR;
    }

    /* register sound device */
    snd_dev.audio.ops = &snd_ops;
    result = rt_audio_register(&snd_dev.audio, "sound0", RT_DEVICE_FLAG_WRONLY, &snd_dev);
    /* check sound device register success or not */
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


struct RIFF_HEADER_DEF
{
    char riff_id[4];     // 'R','I','F','F'
    uint32_t riff_size;
    char riff_format[4]; // 'W','A','V','E'
};

struct WAVE_FORMAT_DEF
{
    uint16_t FormatTag;
    uint16_t Channels;
    uint32_t SamplesPerSec;
    uint32_t AvgBytesPerSec;
    uint16_t BlockAlign;
    uint16_t BitsPerSample;
};

struct FMT_BLOCK_DEF
{
    char fmt_id[4];    // 'f','m','t',' '
    uint32_t fmt_size;
    struct WAVE_FORMAT_DEF wav_format;
};

struct DATA_BLOCK_DEF
{
    char data_id[4];     // 'R','I','F','F'
    uint32_t data_size;
};

struct wav_info
{
    struct RIFF_HEADER_DEF header;
    struct FMT_BLOCK_DEF   fmt_block;
    struct DATA_BLOCK_DEF  data_block;
};

int wavplay_sample(int argc, char **argv)
{
#define BUFSZ   1024
#define SOUND_DEVICE_NAME    "sound0"
static rt_device_t sound_dev;

    int fd = -1;
    uint8_t *buffer = NULL;
    struct wav_info *info = NULL;
    struct rt_audio_caps caps = {0};

    if (argc != 2)
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("wavplay_sample song.wav\n");
        return 0;
    }

    fd = open(argv[1], O_WRONLY);
    if (fd < 0)
    {
        rt_kprintf("open file failed!\n");
        goto __exit;
    }

    buffer = rt_malloc(BUFSZ);
    if (buffer == RT_NULL)
        goto __exit;

    info = (struct wav_info *) rt_malloc(sizeof * info);
    if (info == RT_NULL)
        goto __exit;

    if (read(fd, &(info->header), sizeof(struct RIFF_HEADER_DEF)) <= 0)
        goto __exit;
    if (read(fd, &(info->fmt_block),  sizeof(struct FMT_BLOCK_DEF)) <= 0)
        goto __exit;
    if (read(fd, &(info->data_block), sizeof(struct DATA_BLOCK_DEF)) <= 0)
        goto __exit;

    rt_kprintf("wav information:\n");
    rt_kprintf("samplerate %d\n", info->fmt_block.wav_format.SamplesPerSec);
    rt_kprintf("channel %d\n", info->fmt_block.wav_format.Channels);

    sound_dev = rt_device_find(SOUND_DEVICE_NAME);

    rt_device_open(sound_dev, RT_DEVICE_OFLAG_WRONLY);

    caps.main_type               = AUDIO_TYPE_OUTPUT;
    caps.sub_type                = AUDIO_DSP_PARAM;
    caps.udata.config.samplerate = info->fmt_block.wav_format.SamplesPerSec;
    caps.udata.config.channels   = info->fmt_block.wav_format.Channels;
    caps.udata.config.samplebits = 16;
    rt_device_control(sound_dev, AUDIO_CTL_CONFIGURE, &caps);

    while (1)
    {
        int length;

        length = read(fd, buffer, BUFSZ);

        if (length <= 0)
            break;

        rt_device_write(sound_dev, 0, buffer, length);
    }

    rt_device_close(sound_dev);

__exit:

    if (fd >= 0)
        close(fd);

    if (buffer)
        rt_free(buffer);

    if (info)
        rt_free(info);

    return 0;
}

MSH_CMD_EXPORT(wavplay_sample,  play wav file);

#endif
