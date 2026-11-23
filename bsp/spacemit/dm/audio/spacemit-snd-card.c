/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#define DBG_TAG "audio.card.spacemit"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "spacemit-audio.h"

#define CARD_PREFIX                 "simple-audio-card,"
#define CARD_DAI                    "sound-dai"

#define ANALOG_BLOCK_SIZE           4096
#define ANALOG_BLOCK_COUNT          4
#define ANALOG_BUFFER_SIZE          (ANALOG_BLOCK_SIZE * ANALOG_BLOCK_COUNT)
#define CAPTURE_PERIOD_SIZE         2048
#define CAPTURE_PERIOD_COUNT        4
#define CAPTURE_BUFFER_SIZE         (CAPTURE_PERIOD_SIZE * CAPTURE_PERIOD_COUNT)

#define HDMI_PCM_BLOCK_SIZE         (480 * 4)
#define HDMI_PCM_BLOCK_COUNT        4
#define HDMI_PCM_BUFFER_SIZE        (HDMI_PCM_BLOCK_SIZE * HDMI_PCM_BLOCK_COUNT)
#define HDMI_RAW_BLOCK_SIZE         (HDMI_PCM_BLOCK_SIZE * 2)
#define HDMI_RAW_BUFFER_SIZE        (HDMI_RAW_BLOCK_SIZE * HDMI_PCM_BLOCK_COUNT)

#define AUDIO_DMA_BURST             32
#define AUDIO_TX_THREAD_STACK       4096
#define AUDIO_TX_THREAD_PRIO        12
#define HDMI_SAMPLE_PRESENT         RT_BIT(31)
#define HDMI_FRAME_START            RT_BIT(30)
#define HDMI_PARITY                 RT_BIT(27)
#define HDMI_CHANNEL_STATUS         RT_BIT(26)
#define HDMI_VALID                  RT_BIT(24)

struct spacemit_audio_card
{
    struct rt_audio_device audio;
    struct spacemit_audio_config config;
    struct rt_device *dev;

    struct spacemit_i2s *i2s;
    struct spacemit_hdmi_audio *hdmi;
    struct es8326_codec *codec;
    struct spacemit_pcm *pcm;

    void *playback_buffer;
    rt_ubase_t playback_dma;
    rt_size_t playback_size;
    rt_size_t playback_block_size;

    void *capture_buffer;
    rt_ubase_t capture_dma;
    rt_size_t capture_pos;

    rt_bool_t is_hdmi;
    rt_bool_t replay_started;
    rt_bool_t record_started;
    rt_bool_t tx_running;
    rt_bool_t rx_running;
    rt_bool_t tx_silent;
    rt_bool_t tx_drain;
    rt_bool_t tx_drain_timer_inited;
    rt_bool_t muted;
    rt_uint8_t volume;
    rt_uint8_t iec_offset;
    rt_uint8_t tx_primed_periods;
    rt_uint32_t tx_done_count;
    rt_uint32_t tx_service_count;
    rt_bool_t tx_sem_inited;
    rt_bool_t tx_thread_exit;
    struct rt_semaphore tx_sem;
    rt_thread_t tx_thread;
    struct rt_timer tx_drain_timer;
    char name[32];
};

static void spacemit_hdmi_reformat(struct spacemit_audio_card *card,
        rt_uint32_t *destination, const rt_int16_t *source, rt_size_t frames);

static struct rt_ofw_node *spacemit_audio_parse_dai(struct rt_ofw_node *card_np,
        const char *link_name)
{
    struct rt_ofw_node *link_np, *args_np;
    struct rt_ofw_cell_args args;

    link_np = rt_ofw_get_child_by_tag(card_np, link_name);
    if (!link_np)
    {
        return RT_NULL;
    }

    if (rt_ofw_parse_phandle_cells(link_np, CARD_DAI,
            "#sound-dai-cells", 0, &args))
    {
        rt_ofw_node_put(link_np);
        return RT_NULL;
    }

    args_np = args.data;
    rt_ofw_node_get(args_np);
    rt_ofw_node_put(link_np);

    return args_np;
}

static rt_err_t spacemit_audio_validate_config(
        const struct rt_audio_configure *config)
{
    return config->samplerate == 48000 && config->channels == 2 &&
            config->samplebits == 16 ? RT_EOK : -RT_EINVAL;
}

static rt_err_t spacemit_audio_apply_config(struct spacemit_audio_card *card)
{
    rt_err_t err;

    if (card->is_hdmi)
    {
        return RT_EOK;
    }

    if ((err = spacemit_i2s_configure(card->i2s, &card->config)))
    {
        return err;
    }

    return es8326_codec_hw_params(card->codec, &card->config);
}

static rt_err_t spacemit_audio_getcaps(struct rt_audio_device *audio,
        struct rt_audio_caps *caps)
{
    struct spacemit_audio_card *card = audio->parent.user_data;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_QUERY:
        caps->udata.mask = AUDIO_TYPE_OUTPUT | AUDIO_TYPE_MIXER;
        if (!card->is_hdmi)
        {
            caps->udata.mask |= AUDIO_TYPE_INPUT;
        }
        break;

    case AUDIO_TYPE_OUTPUT:
    case AUDIO_TYPE_INPUT:
        if (caps->main_type == AUDIO_TYPE_INPUT && card->is_hdmi)
        {
            return -RT_ENOSYS;
        }
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            caps->udata.config.samplerate = card->config.samplerate;
            caps->udata.config.channels = card->config.channels;
            caps->udata.config.samplebits = card->config.samplebits;
            break;
        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate = card->config.samplerate;
            caps->udata.mask = AUDIO_SAMP_RATE_48K;
            break;
        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels = card->config.channels;
            break;
        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits = card->config.samplebits;
            break;
        default:
            return -RT_ENOSYS;
        }
        break;

    case AUDIO_TYPE_MIXER:
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_QUERY:
            caps->udata.mask = AUDIO_MIXER_VOLUME | AUDIO_MIXER_MUTE;
            break;
        case AUDIO_MIXER_VOLUME:
            caps->udata.value = card->volume;
            break;
        case AUDIO_MIXER_MUTE:
            caps->udata.value = card->muted;
            break;
        default:
            return -RT_ENOSYS;
        }
        break;

    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_err_t spacemit_audio_configure(struct rt_audio_device *audio,
        struct rt_audio_caps *caps)
{
    rt_err_t err;
    struct spacemit_audio_card *card = audio->parent.user_data;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_OUTPUT:
    case AUDIO_TYPE_INPUT:
        if (caps->main_type == AUDIO_TYPE_INPUT && card->is_hdmi)
        {
            return -RT_ENOSYS;
        }
        if (caps->sub_type != AUDIO_DSP_PARAM)
        {
            return -RT_ENOSYS;
        }
        if ((err = spacemit_audio_validate_config(&caps->udata.config)))
        {
            LOG_W("%s supports 48000 Hz, stereo, 16-bit PCM only", card->name);
            return err;
        }
        card->config.samplerate = caps->udata.config.samplerate;
        card->config.channels = caps->udata.config.channels;
        card->config.samplebits = caps->udata.config.samplebits;
        return spacemit_audio_apply_config(card);

    case AUDIO_TYPE_MIXER:
        if (caps->sub_type == AUDIO_MIXER_VOLUME)
        {
            int volume = caps->udata.value;

            if (volume < AUDIO_VOLUME_MIN)
            {
                volume = AUDIO_VOLUME_MIN;
            }
            if (volume > AUDIO_VOLUME_MAX)
            {
                volume = AUDIO_VOLUME_MAX;
            }
            card->volume = volume;
            return card->codec ? es8326_codec_set_volume(card->codec, volume) : RT_EOK;
        }
        if (caps->sub_type == AUDIO_MIXER_MUTE)
        {
            card->muted = !!caps->udata.value;
            return card->codec ? es8326_codec_set_mute(card->codec, card->muted) : RT_EOK;
        }
        return -RT_ENOSYS;

    default:
        return -RT_ENOSYS;
    }
}

static rt_err_t spacemit_audio_dma_prepare_tx(struct spacemit_audio_card *card,
        rt_ubase_t source, rt_size_t length, rt_size_t period)
{
    rt_err_t err;
    struct rt_dma_slave_config config = { 0 };
    struct rt_dma_slave_transfer transfer = { 0 };

    config.direction = RT_DMA_MEM_TO_DEV;
    config.src_addr = source;
    config.dst_addr = card->is_hdmi ?
            spacemit_hdmi_audio_fifo_phys(card->hdmi) :
            spacemit_i2s_fifo_phys(card->i2s);
    config.src_addr_width = RT_DMA_SLAVE_BUSWIDTH_4_BYTES;
    config.dst_addr_width = RT_DMA_SLAVE_BUSWIDTH_4_BYTES;
    config.src_maxburst = AUDIO_DMA_BURST;
    config.dst_maxburst = AUDIO_DMA_BURST;

    if (card->is_hdmi)
    {
        LOG_D("%s: TX DMA config begin: src=%08lx dst=%08lx len=%u period=%u",
                card->name, (unsigned long)source,
                (unsigned long)config.dst_addr,
                (unsigned int)length, (unsigned int)period);
    }
    if ((err = rt_dma_chan_config(card->pcm->tx, &config)))
    {
        if (card->is_hdmi)
        {
            LOG_E("%s: TX DMA config failed: %s", card->name,
                    rt_strerror(err));
        }
        return err;
    }
    if (card->is_hdmi)
    {
        LOG_D("%s: TX DMA config done", card->name);
    }

    transfer.src_addr = source;
    transfer.dst_addr = config.dst_addr;
    transfer.buffer_len = length;
    transfer.period_len = period;

    if (card->is_hdmi)
    {
        LOG_D("%s: TX DMA prep begin", card->name);
    }
    if ((err = rt_dma_prep_cyclic(card->pcm->tx, &transfer)))
    {
        if (card->is_hdmi)
        {
            LOG_E("%s: TX DMA prep failed: %s", card->name,
                    rt_strerror(err));
        }
        return err;
    }
    if (card->is_hdmi)
    {
        LOG_D("%s: TX DMA prep done, start begin", card->name);
    }

    err = rt_dma_chan_start(card->pcm->tx);
    if (card->is_hdmi)
    {
        if (err)
        {
            LOG_E("%s: TX DMA start failed: %s", card->name,
                    rt_strerror(err));
        }
        else
        {
            LOG_D("%s: TX DMA start done", card->name);
        }
    }

    return err;
}

static void spacemit_audio_drain_timer(void *parameter)
{
    struct spacemit_audio_card *card = parameter;

    if (card->replay_started && card->tx_drain)
    {
        rt_audio_tx_complete(&card->audio);
    }
}

static void spacemit_audio_start_drain_tx(struct spacemit_audio_card *card)
{
    rt_tick_t tick;

    if (!card->tx_drain_timer_inited)
    {
        return;
    }

    tick = rt_tick_from_millisecond(10);
    if (!tick)
    {
        tick = 1;
    }

    card->tx_running = RT_TRUE;
    card->tx_silent = RT_FALSE;
    card->tx_drain = RT_TRUE;
    rt_timer_control(&card->tx_drain_timer, RT_TIMER_CTRL_SET_TIME, &tick);
    rt_timer_start(&card->tx_drain_timer);
}

static void spacemit_audio_stop_drain_tx(struct spacemit_audio_card *card)
{
    if (card->tx_drain_timer_inited)
    {
        rt_timer_stop(&card->tx_drain_timer);
    }
    card->tx_drain = RT_FALSE;
}

static void spacemit_audio_hdmi_silence(struct spacemit_audio_card *card)
{
    rt_memset(card->pcm->hdmi_buffer, 0, HDMI_RAW_BUFFER_SIZE);
    rt_hw_wmb();
}

static void spacemit_audio_tx_worker(void *parameter)
{
    struct spacemit_audio_card *card = parameter;

    while (!card->tx_thread_exit)
    {
        rt_sem_take(&card->tx_sem, RT_WAITING_FOREVER);

        if (card->tx_thread_exit)
        {
            break;
        }
        if (card->replay_started && !card->tx_silent)
        {
            card->tx_service_count++;
            if (card->tx_service_count <= 4 ||
                !(card->tx_service_count % 100))
            {
                LOG_D("%s: TX service #%u", card->name,
                        card->tx_service_count);
            }
            rt_audio_tx_complete(&card->audio);
        }
    }
}

static rt_err_t spacemit_audio_ensure_tx_thread(struct spacemit_audio_card *card)
{
    if (card->tx_thread)
    {
        return RT_EOK;
    }

    if (!card->tx_sem_inited)
    {
        return -RT_ERROR;
    }

    card->tx_thread_exit = RT_FALSE;
    card->tx_thread = rt_thread_create("audtx",
            spacemit_audio_tx_worker, card,
            AUDIO_TX_THREAD_STACK, AUDIO_TX_THREAD_PRIO, 10);
    if (!card->tx_thread)
    {
        return -RT_ENOMEM;
    }

    return rt_thread_startup(card->tx_thread);
}

static rt_err_t spacemit_audio_start_silent_tx(struct spacemit_audio_card *card)
{
    rt_err_t err;

    rt_memset(card->playback_buffer, 0, card->playback_size);
    if ((err = spacemit_audio_dma_prepare_tx(card, card->playback_dma,
            card->playback_size, card->playback_block_size)))
    {
        return err;
    }

    card->tx_running = RT_TRUE;
    card->tx_silent = RT_TRUE;
    return RT_EOK;
}

static rt_err_t spacemit_audio_start_rx(struct spacemit_audio_card *card)
{
    rt_err_t err;
    struct rt_dma_slave_config config = { 0 };
    struct rt_dma_slave_transfer transfer = { 0 };

    config.direction = RT_DMA_DEV_TO_MEM;
    config.src_addr = spacemit_i2s_fifo_phys(card->i2s);
    config.dst_addr = card->capture_dma;
    config.src_addr_width = RT_DMA_SLAVE_BUSWIDTH_4_BYTES;
    config.dst_addr_width = RT_DMA_SLAVE_BUSWIDTH_4_BYTES;
    config.src_maxburst = AUDIO_DMA_BURST;
    config.dst_maxburst = AUDIO_DMA_BURST;

    if ((err = rt_dma_chan_config(card->pcm->rx, &config)))
    {
        return err;
    }

    transfer.src_addr = config.src_addr;
    transfer.dst_addr = card->capture_dma;
    transfer.buffer_len = CAPTURE_BUFFER_SIZE;
    transfer.period_len = CAPTURE_PERIOD_SIZE;

    if ((err = rt_dma_prep_cyclic(card->pcm->rx, &transfer)))
    {
        return err;
    }
    if ((err = rt_dma_chan_start(card->pcm->rx)))
    {
        return err;
    }

    card->capture_pos = 0;
    card->rx_running = RT_TRUE;
    return RT_EOK;
}

static rt_err_t spacemit_audio_init(struct rt_audio_device *audio)
{
    struct spacemit_audio_card *card = audio->parent.user_data;

    return spacemit_audio_apply_config(card);
}

static rt_err_t spacemit_audio_start(struct rt_audio_device *audio, int stream)
{
    rt_err_t err;
    rt_bool_t codec_started = RT_FALSE;
    rt_bool_t silent_started = RT_FALSE;
    rt_bool_t was_silent = RT_FALSE;
    struct spacemit_audio_card *card = audio->parent.user_data;

    if (stream == AUDIO_STREAM_REPLAY)
    {
        if (card->replay_started)
        {
            return RT_EOK;
        }

        if (card->tx_running && card->tx_silent)
        {
            was_silent = RT_TRUE;
            rt_dma_chan_stop(card->pcm->tx);
            card->tx_running = RT_FALSE;
            card->tx_silent = RT_FALSE;
        }

        if (card->is_hdmi)
        {
            if ((err = spacemit_hdmi_audio_start(card->hdmi)))
            {
                return err;
            }
        }
        else
        {
            if ((err = es8326_codec_start(card->codec, stream)))
            {
                goto _restore_silent_tx;
            }
            codec_started = RT_TRUE;
            if ((err = spacemit_i2s_start(card->i2s)))
            {
                es8326_codec_stop(card->codec, stream);
                goto _restore_silent_tx;
            }
        }

        card->iec_offset = 0;
        card->replay_started = RT_TRUE;
        card->tx_drain = RT_FALSE;
        card->tx_primed_periods = 0;
        card->tx_done_count = 0;
        card->tx_service_count = 0;
        if (audio->replay)
        {
            audio->replay->read_index = 0;
        }
        if (card->is_hdmi)
        {
            spacemit_audio_hdmi_silence(card);
        }

        /* Prime the first hardware period from a playback worker thread. */
        if ((err = spacemit_audio_ensure_tx_thread(card)))
        {
            card->replay_started = RT_FALSE;
            goto _stop_playback;
        }
        if (card->is_hdmi)
        {
            for (int i = 0; i < HDMI_PCM_BLOCK_COUNT; ++i)
            {
                rt_sem_release(&card->tx_sem);
            }
        }
        else
        {
            rt_sem_release(&card->tx_sem);
        }
        return RT_EOK;
    }

    if (stream == AUDIO_STREAM_RECORD && !card->is_hdmi)
    {
        if (card->record_started)
        {
            return RT_EOK;
        }
        if (!card->tx_running &&
            (err = spacemit_audio_start_silent_tx(card)))
        {
            return err;
        }
        silent_started = !card->replay_started && card->tx_silent;
        if ((err = spacemit_audio_start_rx(card)))
        {
            goto _stop_silent_tx;
        }
        if ((err = es8326_codec_start(card->codec, stream)))
        {
            goto _stop_rx;
        }
        codec_started = RT_TRUE;
        if ((err = spacemit_i2s_start(card->i2s)))
        {
            goto _stop_codec;
        }
        card->record_started = RT_TRUE;
        return RT_EOK;
    }

    return -RT_EINVAL;

_stop_playback:
    if (card->is_hdmi)
    {
        spacemit_hdmi_audio_stop(card->hdmi);
    }
    else
    {
        if (codec_started)
        {
            es8326_codec_stop(card->codec, stream);
        }
        spacemit_i2s_stop(card->i2s);
    }
    return err;

_stop_codec:
    if (codec_started)
    {
        es8326_codec_stop(card->codec, stream);
    }
_stop_rx:
    if (card->rx_running)
    {
        rt_dma_chan_stop(card->pcm->rx);
        card->rx_running = RT_FALSE;
    }
_stop_silent_tx:
    if (silent_started && card->tx_running)
    {
        rt_dma_chan_stop(card->pcm->tx);
        card->tx_running = RT_FALSE;
        card->tx_silent = RT_FALSE;
    }
    return err;

_restore_silent_tx:
    if (was_silent && spacemit_audio_start_silent_tx(card))
    {
        LOG_E("%s: failed to restore capture clock DMA", card->name);
    }
    return err;
}

static rt_err_t spacemit_audio_stop(struct rt_audio_device *audio, int stream)
{
    rt_err_t err = RT_EOK;
    struct spacemit_audio_card *card = audio->parent.user_data;

    if (stream == AUDIO_STREAM_REPLAY && card->replay_started)
    {
        if (card->tx_drain)
        {
            spacemit_audio_stop_drain_tx(card);
        }

        if (card->tx_running)
        {
            rt_dma_chan_stop(card->pcm->tx);
            card->tx_running = RT_FALSE;
        }
        card->tx_silent = RT_FALSE;
        card->tx_primed_periods = 0;
        if (audio->replay)
        {
            audio->replay->read_index = 0;
        }
        card->replay_started = RT_FALSE;

        if (card->is_hdmi)
        {
            err = spacemit_hdmi_audio_stop(card->hdmi);
        }
        else
        {
            es8326_codec_stop(card->codec, stream);
            spacemit_i2s_stop(card->i2s);
            if (card->record_started)
            {
                err = spacemit_audio_start_silent_tx(card);
            }
        }
        return err;
    }

    if (stream == AUDIO_STREAM_RECORD && card->record_started)
    {
        if (card->rx_running)
        {
            rt_dma_chan_stop(card->pcm->rx);
            card->rx_running = RT_FALSE;
        }
        if (!card->replay_started && card->tx_running)
        {
            rt_dma_chan_stop(card->pcm->tx);
            card->tx_running = RT_FALSE;
            card->tx_silent = RT_FALSE;
        }
        card->record_started = RT_FALSE;
        es8326_codec_stop(card->codec, stream);
        return spacemit_i2s_stop(card->i2s);
    }

    return RT_EOK;
}

static rt_uint32_t spacemit_hdmi_parity(rt_uint32_t sample)
{
    sample ^= sample >> 16;
    sample ^= sample >> 8;
    sample ^= sample >> 4;
    sample &= 0xf;
    return (0x6996 >> sample) & 1;
}

static void spacemit_hdmi_reformat(struct spacemit_audio_card *card,
        rt_uint32_t *destination, const rt_int16_t *source, rt_size_t frames)
{
    while (frames--)
    {
        for (int channel = 0; channel < 2; ++channel)
        {
            rt_uint32_t sample = (rt_uint16_t)*source++ << 8;

            sample |= HDMI_SAMPLE_PRESENT | HDMI_VALID;
            if (!card->iec_offset)
            {
                sample |= HDMI_FRAME_START;
            }
            if (card->iec_offset == 25 || card->iec_offset == 32)
            {
                sample |= HDMI_CHANNEL_STATUS;
            }
            sample |= spacemit_hdmi_parity(sample) << 27;
            *destination++ = sample;
        }

        if (++card->iec_offset == 192)
        {
            card->iec_offset = 0;
        }
    }
}

static rt_ssize_t spacemit_audio_transmit(struct rt_audio_device *audio,
        const void *write_buf, void *read_buf, rt_size_t size)
{
    rt_err_t err;
    rt_ubase_t offset;
    struct spacemit_audio_card *card = audio->parent.user_data;

    RT_UNUSED(read_buf);

    if (!card->replay_started || size != card->playback_block_size)
    {
        return 0;
    }

    offset = (const rt_uint8_t *)write_buf -
            (const rt_uint8_t *)card->playback_buffer;
    if (offset >= card->playback_size)
    {
        return -RT_EINVAL;
    }

    if (card->is_hdmi)
    {
        spacemit_hdmi_reformat(card,
                (rt_uint32_t *)((rt_uint8_t *)card->pcm->hdmi_buffer + offset * 2),
                write_buf, size / 4);
        rt_hw_wmb();
    }

    if (!card->tx_running)
    {
        rt_ubase_t dma = card->is_hdmi ? card->pcm->hdmi_dma : card->playback_dma;
        rt_size_t length = card->is_hdmi ? HDMI_RAW_BUFFER_SIZE : card->playback_size;
        rt_size_t period = card->is_hdmi ? HDMI_RAW_BLOCK_SIZE : card->playback_block_size;

        if (card->is_hdmi && ++card->tx_primed_periods < HDMI_PCM_BLOCK_COUNT)
        {
            return size;
        }

        card->tx_done_count = 0;
        card->tx_running = RT_TRUE;
        card->tx_silent = RT_FALSE;
        if ((err = spacemit_audio_dma_prepare_tx(card, dma, length, period)))
        {
            card->tx_running = RT_FALSE;
            card->tx_primed_periods = 0;
            LOG_E("%s: TX DMA start failed: %s", card->name, rt_strerror(err));
            LOG_D("%s: drain playback queue without hardware DMA", card->name);
            spacemit_audio_start_drain_tx(card);
            return size;
        }
    }

    return size;
}

static void spacemit_audio_buffer_info(struct rt_audio_device *audio,
        struct rt_audio_buf_info *info)
{
    struct spacemit_audio_card *card = audio->parent.user_data;

    info->buffer = card->playback_buffer;
    info->block_size = card->playback_block_size;
    info->block_count = card->is_hdmi ? HDMI_PCM_BLOCK_COUNT : ANALOG_BLOCK_COUNT;
    info->total_size = card->playback_size;
}

static const struct rt_audio_ops spacemit_audio_ops =
{
    .getcaps = spacemit_audio_getcaps,
    .configure = spacemit_audio_configure,
    .init = spacemit_audio_init,
    .start = spacemit_audio_start,
    .stop = spacemit_audio_stop,
    .transmit = spacemit_audio_transmit,
    .buffer_info = spacemit_audio_buffer_info,
};

static void spacemit_audio_tx_done(struct rt_dma_chan *channel, rt_size_t size)
{
    struct spacemit_audio_card *card = channel->priv;

    RT_UNUSED(size);

    if (card->replay_started && !card->tx_silent)
    {
        card->tx_done_count++;
        if (card->tx_done_count <= 4 || !(card->tx_done_count % 100))
        {
            LOG_D("%s: TX period done #%u", card->name, card->tx_done_count);
        }
        if (card->tx_sem_inited)
        {
            rt_sem_release(&card->tx_sem);
        }
    }
}

static void spacemit_audio_rx_done(struct rt_dma_chan *channel, rt_size_t size)
{
    struct spacemit_audio_card *card = channel->priv;

    RT_UNUSED(size);

    if (card->record_started)
    {
        rt_audio_rx_done(&card->audio,
                (rt_uint8_t *)card->capture_buffer + card->capture_pos,
                CAPTURE_PERIOD_SIZE);
        card->capture_pos += CAPTURE_PERIOD_SIZE;
        card->capture_pos %= CAPTURE_BUFFER_SIZE;
    }
}

static void spacemit_audio_card_free(struct spacemit_audio_card *card)
{
    if (!card)
    {
        return;
    }

    if (card->capture_buffer)
    {
        rt_dma_free_coherent(card->dev, CAPTURE_BUFFER_SIZE,
                card->capture_buffer, card->capture_dma);
    }
    if (card->tx_drain_timer_inited)
    {
        rt_timer_stop(&card->tx_drain_timer);
        rt_timer_detach(&card->tx_drain_timer);
    }
    if (card->tx_thread)
    {
        card->tx_thread_exit = RT_TRUE;
        rt_sem_release(&card->tx_sem);
        rt_thread_delete(card->tx_thread);
    }
    if (card->tx_sem_inited)
    {
        rt_sem_detach(&card->tx_sem);
    }
    if (card->playback_buffer)
    {
        rt_dma_free_coherent(card->dev, card->playback_size,
                card->playback_buffer, card->playback_dma);
    }
    rt_free(card);
}

static rt_err_t spacemit_audio_card_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t mclk_fs = 64;
    rt_uint32_t flags;
    const char *name = "spacemit-audio";
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *cpu_np = RT_NULL, *plat_np = RT_NULL, *codec_np = RT_NULL;
    struct spacemit_audio_card *card = rt_calloc(1, sizeof(*card));

    if (!card)
    {
        return -RT_ENOMEM;
    }

    card->dev = dev;
    card->volume = 70;
    card->config.samplerate = 48000;
    card->config.channels = 2;
    card->config.samplebits = 16;
    rt_ofw_prop_read_string(dev->ofw_node, CARD_PREFIX "name", &name);
    rt_strncpy(card->name, name, sizeof(card->name) - 1);
    if (rt_ofw_prop_read_u32(dev->ofw_node, "spacemit,mclk-fs", &mclk_fs))
    {
        rt_ofw_prop_read_u32(dev->ofw_node, CARD_PREFIX "mclk-fs", &mclk_fs);
    }
    card->config.mclk_fs = mclk_fs;

    cpu_np = spacemit_audio_parse_dai(dev->ofw_node, CARD_PREFIX "cpu");
    plat_np = spacemit_audio_parse_dai(dev->ofw_node, CARD_PREFIX "plat");
    codec_np = spacemit_audio_parse_dai(dev->ofw_node, CARD_PREFIX "codec");
    if (!cpu_np || !plat_np)
    {
        err = -RT_EINVAL;
        LOG_E("%s: missing CPU or platform DAI", card->name);
        goto _fail;
    }

    card->pcm = spacemit_pcm_find(plat_np);
    card->is_hdmi = rt_ofw_node_is_compatible(cpu_np,
            "spacemit,spacemit-snd-sspa");
    if (!card->pcm)
    {
        err = -RT_ENOSYS;
        LOG_E("%s: DMA platform is not ready", card->name);
        goto _fail;
    }

    if (card->is_hdmi)
    {
        card->hdmi = spacemit_hdmi_audio_find(cpu_np);
        if (!card->hdmi || !card->pcm->is_hdmi ||
            card->pcm->hdmi_size < HDMI_RAW_BUFFER_SIZE)
        {
            err = -RT_ENOSYS;
            LOG_E("%s: HDMI audio resources are not ready", card->name);
            goto _fail;
        }
        card->playback_size = HDMI_PCM_BUFFER_SIZE;
        card->playback_block_size = HDMI_PCM_BLOCK_SIZE;
        flags = RT_DEVICE_FLAG_WRONLY;
    }
    else
    {
        card->i2s = spacemit_i2s_find(cpu_np);
        card->codec = es8326_codec_find(codec_np);
        if (!card->i2s || !card->codec || card->pcm->is_hdmi || !card->pcm->rx)
        {
            err = -RT_ENOSYS;
            LOG_E("%s: I2S or ES8326 is not ready", card->name);
            goto _fail;
        }
        card->playback_size = ANALOG_BUFFER_SIZE;
        card->playback_block_size = ANALOG_BLOCK_SIZE;
        flags = RT_DEVICE_FLAG_RDWR;
    }

    card->playback_buffer = rt_dma_alloc_coherent(dev, card->playback_size,
            &card->playback_dma);
    if (!card->playback_buffer)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }
    rt_memset(card->playback_buffer, 0, card->playback_size);

    if (!card->is_hdmi)
    {
        card->capture_buffer = rt_dma_alloc_coherent(dev, CAPTURE_BUFFER_SIZE,
                &card->capture_dma);
        if (!card->capture_buffer)
        {
            err = -RT_ENOMEM;
            goto _fail;
        }
        rt_memset(card->capture_buffer, 0, CAPTURE_BUFFER_SIZE);
    }

    card->audio.ops = (struct rt_audio_ops *)&spacemit_audio_ops;
    card->audio.parent.user_data = card;
    rt_timer_init(&card->tx_drain_timer, "auddrn",
            spacemit_audio_drain_timer, card,
            rt_tick_from_millisecond(10),
            RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);
    card->tx_drain_timer_inited = RT_TRUE;
    rt_sem_init(&card->tx_sem, "audtx", 0, RT_IPC_FLAG_PRIO);
    card->tx_sem_inited = RT_TRUE;

    if ((err = rt_audio_register(&card->audio, card->name, flags, card)))
    {
        if (rt_device_find(card->name) == &card->audio.parent)
        {
            rt_device_unregister(&card->audio.parent);
        }
        goto _fail;
    }
    card->pcm->tx->callback = spacemit_audio_tx_done;
    card->pcm->tx->priv = card;
    if (card->pcm->rx)
    {
        card->pcm->rx->callback = spacemit_audio_rx_done;
        card->pcm->rx->priv = card;
    }

    dev->user_data = card;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, card);
    rt_ofw_node_put(cpu_np);
    rt_ofw_node_put(plat_np);
    rt_ofw_node_put(codec_np);

    LOG_I("%s: 48 kHz stereo 16-bit %s audio ready", card->name,
            card->is_hdmi ? "HDMI" : "ES8326");
    return RT_EOK;

_fail:
    rt_ofw_node_put(cpu_np);
    rt_ofw_node_put(plat_np);
    rt_ofw_node_put(codec_np);
    spacemit_audio_card_free(card);
    return err;
}

static rt_err_t spacemit_audio_card_remove(struct rt_platform_device *pdev)
{
    struct spacemit_audio_card *card = pdev->parent.user_data;

    if (!card)
    {
        return RT_EOK;
    }
    if (card->replay_started || card->record_started)
    {
        return -RT_EBUSY;
    }

    rt_device_unregister(&card->audio.parent);
    rt_dm_dev_unbind_fwdata(&pdev->parent, RT_NULL);
    card->pcm->tx->callback = RT_NULL;
    card->pcm->tx->priv = RT_NULL;
    if (card->pcm->rx)
    {
        card->pcm->rx->callback = RT_NULL;
        card->pcm->rx->priv = RT_NULL;
    }
    spacemit_audio_card_free(card);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_audio_card_ofw_ids[] =
{
    { .compatible = "spacemit,simple-audio-card" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_audio_card_driver =
{
    .name = "spacemit-audio-card",
    .ids = spacemit_audio_card_ofw_ids,
    .probe = spacemit_audio_card_probe,
    .remove = spacemit_audio_card_remove,
};

static int spacemit_audio_card_register(void)
{
    rt_platform_driver_register(&spacemit_audio_card_driver);
    return 0;
}
INIT_COMPONENT_EXPORT(spacemit_audio_card_register);
