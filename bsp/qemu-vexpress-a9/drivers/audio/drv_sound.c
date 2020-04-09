/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 * 
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2019-07-23     Zero-Free    first implementation
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <drv_sound.h>
#include <drv_pl041.h>
#include <drv_ac97.h>

#define DBG_TAG              "drv.sound"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#define TX_FIFO_SIZE         (3840)

struct sound_device
{
    struct rt_audio_device audio;
    struct rt_audio_configure replay_config;
    rt_uint8_t *tx_fifo;
    rt_uint8_t volume;
};

static struct sound_device snd_dev = {0};

static void rt_hw_aaci_isr(rt_uint32_t status, void *user_data)
{
    if (status & AACI_SR_TXHE)
    {
        rt_audio_tx_complete(&snd_dev.audio);
    }
}

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
            caps->udata.value = snd_dev->volume;
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
    struct rt_audio_replay *replay;

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

            snd_dev->volume = volume;
            ac97_set_vol(volume);
            LOG_I("set volume %d", volume);
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
            ac97_set_rate(caps->udata.config.samplerate);

            /* update buffer fifo informaition according samplerate */
            replay = snd_dev->audio.replay;
            replay->buf_info.total_size = caps->udata.config.samplerate / 50 * 4;
            replay->buf_info.block_size = replay->buf_info.total_size / 2;

            /* save configs */
            snd_dev->replay_config.samplerate = caps->udata.config.samplerate;
            snd_dev->replay_config.channels   = caps->udata.config.channels;
            snd_dev->replay_config.samplebits = caps->udata.config.samplebits;
            LOG_D("set samplerate %d", snd_dev->replay_config.samplerate);
            break;
        }

        case AUDIO_DSP_SAMPLERATE:
        {
            ac97_set_rate(caps->udata.config.samplerate);

            snd_dev->replay_config.samplerate = caps->udata.config.samplerate;
            LOG_D("set samplerate %d", snd_dev->replay_config.samplerate);
            break;
        }

        case AUDIO_DSP_CHANNELS:
        {
            /* not support */
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
    struct pl041_cfg _cfg;

    RT_ASSERT(audio != RT_NULL);
    snd_dev = (struct sound_device *)audio->parent.user_data;

    aaci_pl041_init();

    _cfg.itype = PL041_CHANNEL_LEFT_ADC | PL041_CHANNEL_RIGHT_ADC;
    _cfg.otype = PL041_CHANNEL_LEFT_DAC | PL041_CHANNEL_RIGHT_DAC;
    _cfg.vol   = snd_dev->volume;
    _cfg.rate  = snd_dev->replay_config.samplerate;

    ac97_reset();
    aaci_pl041_channel_cfg(0, &_cfg);
    aaci_pl041_irq_register(0, rt_hw_aaci_isr, RT_NULL);

    return result;
}

static rt_err_t sound_start(struct rt_audio_device *audio, int stream)
{
    RT_ASSERT(audio != RT_NULL);

    if (stream == AUDIO_STREAM_REPLAY)
    {
        LOG_D("open sound device");
        aaci_pl041_channel_enable(0);
        aaci_pl041_irq_enable(0, AACI_IE_UR | AACI_IE_TX | AACI_IE_TXC);
    }

    return RT_EOK;
}

static rt_err_t sound_stop(struct rt_audio_device *audio, int stream)
{
    RT_ASSERT(audio != RT_NULL);

    if (stream == AUDIO_STREAM_REPLAY)
    {
        /* wait codec free */
        rt_thread_mdelay(100);
        /* disable irq and channels 0 */
        aaci_pl041_irq_disable(0, AACI_IE_UR | AACI_IE_TX | AACI_IE_TXC);
        aaci_pl041_channel_disable(0);
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
    info->block_size  = TX_FIFO_SIZE/2;
    info->block_count = 2;
}

static rt_size_t sound_transmit(struct rt_audio_device *audio, const void *writeBuf, void *readBuf, rt_size_t size)
{
    RT_ASSERT(audio != RT_NULL);

    /* write data to channel_0 fifo */
    aaci_pl041_channel_write(0, (rt_uint16_t *)writeBuf, size >> 1);

    return size;
}

static struct rt_audio_ops snd_ops =
{
    .getcaps     = sound_getcaps,
    .configure   = sound_configure,
    .init        = sound_init,
    .start       = sound_start,
    .stop        = sound_stop,
    .transmit    = sound_transmit,
    .buffer_info = sound_buffer_info,
};

int rt_hw_audio_init(void)
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

INIT_DEVICE_EXPORT(rt_hw_audio_init);
