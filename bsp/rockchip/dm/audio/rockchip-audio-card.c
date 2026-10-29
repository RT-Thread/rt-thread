/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "audio.card"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rockchip-i2s-tdm.h"
#include "rockchip-sai.h"
#include "rockchip-hdmi.h"
#include "codec/rk817-codec.h"
#include "codec/rk3528-codec.h"

#define CARD_PREFIX         "simple-audio-card,"
#define CARD_DAI            "sound-dai"
#define ROCKCHIP_HDMI_CARD  "rockchip,hdmi"
#define DEFAULT_MCLK_FS     256

#ifndef RT_AUDIO_REPLAY_MP_BLOCK_SIZE
#define RT_AUDIO_REPLAY_MP_BLOCK_SIZE   4096
#endif

#ifndef RT_AUDIO_REPLAY_MP_BLOCK_COUNT
#define RT_AUDIO_REPLAY_MP_BLOCK_COUNT  2
#endif

#define ROCKCHIP_AUDIO_PLAYBACK_SIZE    \
    (RT_AUDIO_REPLAY_MP_BLOCK_SIZE * RT_AUDIO_REPLAY_MP_BLOCK_COUNT)

#define ROCKCHIP_I2S_DMA_BURST          8

struct rockchip_audio_card
{
    struct rt_audio_device audio;
    struct rt_audio_configure config;

    struct rt_device *dev;
    struct rockchip_i2s_tdm *i2s;
    struct rockchip_sai *sai;
    struct rk817_codec *codec;
    struct rk3528_codec *acodec;
    struct rt_ofw_node *hdmi_np;

    rt_uint32_t mclk_fs;
    struct rt_spinlock replay_lock;
    struct rt_completion replay_idle;
    rt_uint32_t replay_callbacks;
    rt_bool_t started;
    rt_bool_t is_hdmi;
    rt_bool_t use_dma;
    rt_bool_t playback_coherent;
    rt_uint32_t volume;
    rt_bool_t muted;
    char name[32];

    struct rt_dma_chan *dma_tx;
    void *playback_buf;
    rt_ubase_t playback_dma;
    rt_ubase_t txdr_dma;
};

static struct rt_ofw_node *rockchip_audio_parse_dai_np(struct rt_ofw_node *card_np,
        const char *link_name)
{
    struct rt_ofw_node *link_np, *args_np;
    struct rt_ofw_cell_args args;

    link_np = rt_ofw_get_child_by_tag(card_np, link_name);

    if (!link_np)
    {
        return RT_NULL;
    }

    if (rt_ofw_parse_phandle_cells(link_np, CARD_DAI, "#sound-dai-cells", 0, &args))
    {
        rt_ofw_node_put(link_np);
        return RT_NULL;
    }

    args_np = args.data;
    rt_ofw_node_get(args_np);
    rt_ofw_node_put(link_np);

    return args_np;
}

static rt_err_t rockchip_audio_card_getcaps(struct rt_audio_device *audio,
        struct rt_audio_caps *caps)
{
    struct rockchip_audio_card *card = audio->parent.user_data;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_QUERY:
        switch (caps->sub_type)
        {
        case AUDIO_TYPE_QUERY:
            caps->udata.mask = AUDIO_TYPE_OUTPUT;
            break;
        default:
            caps->udata.mask = AUDIO_TYPE_OUTPUT;
            break;
        }
        break;

    case AUDIO_TYPE_OUTPUT:
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            caps->udata.config.samplerate = card->config.samplerate;
            caps->udata.config.channels = card->config.channels;
            caps->udata.config.samplebits = card->config.samplebits;
            break;
        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate = 48000;
            caps->udata.mask = AUDIO_SAMP_RATE_44K | AUDIO_SAMP_RATE_48K;
            break;
        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels = 2;
            break;
        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits = 16;
            break;
        default:
            break;
        }
        break;

    case AUDIO_TYPE_MIXER:
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_QUERY:
            caps->udata.mask = AUDIO_MIXER_VOLUME | AUDIO_MIXER_MUTE;
            break;
        case AUDIO_MIXER_VOLUME:
            caps->udata.value = card->acodec ? card->volume : AUDIO_VOLUME_MAX;
            break;
        case AUDIO_MIXER_MUTE:
            caps->udata.value = card->muted;
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }

    return RT_EOK;
}

static rt_err_t rockchip_audio_card_configure(struct rt_audio_device *audio,
        struct rt_audio_caps *caps)
{
    rt_err_t err;
    struct rockchip_audio_card *card = audio->parent.user_data;
    struct rockchip_i2s_config i2s_cfg;
    struct rk817_codec_config codec_cfg;
    struct rt_audio_configure config;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_MIXER:
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_MUTE:
            if (card->acodec)
            {
                err = rk3528_codec_mute(card->acodec, !!caps->udata.value);
                if (err)
                {
                    return err;
                }
                card->muted = !!caps->udata.value;
            }
            break;
        case AUDIO_MIXER_VOLUME:
            if (card->acodec)
            {
                err = rk3528_codec_set_volume(card->acodec, caps->udata.value);
                if (err)
                {
                    return err;
                }
                card->volume = caps->udata.value;
            }
            if (!card->is_hdmi && card->codec)
            {
                rk817_codec_set_volume(card->codec, caps->udata.value);
            }
            break;
        default:
            break;
        }
        break;

    case AUDIO_TYPE_OUTPUT:
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            if (card->sai && card->started)
            {
                return -RT_EBUSY;
            }
            config = caps->udata.config;

            if (!config.samplerate)
            {
                config.samplerate = 48000;
            }

            if (!config.channels)
            {
                config.channels = 2;
            }

            if (!config.samplebits)
            {
                config.samplebits = 16;
            }

            i2s_cfg.samplerate = config.samplerate;
            i2s_cfg.channels = config.channels;
            i2s_cfg.samplebits = config.samplebits;
            i2s_cfg.mclk_fs = card->mclk_fs;

            codec_cfg.samplerate = config.samplerate;
            codec_cfg.samplebits = config.samplebits;
            codec_cfg.mclk_rate = config.samplerate * card->mclk_fs;

            if (card->sai)
            {
                if (config.channels != 2 || config.samplebits != 16 ||
                    (config.samplerate != 44100 && config.samplerate != 48000))
                {
                    return -RT_EINVAL;
                }
                if ((err = rockchip_sai_hw_params(card->sai, &i2s_cfg)))
                {
                    return err;
                }
                /* SAI2 establishes the shared source before the DAC divider. */
                if (card->acodec && (err = rk3528_codec_hw_params(card->acodec,
                        config.samplerate, config.samplebits, card->mclk_fs)))
                {
                    return err;
                }
                card->config = config;
                return RT_EOK;
            }

            card->config = config;
            if (!card->is_hdmi && card->codec)
            {
                if ((err = rk817_codec_hw_params(card->codec, &codec_cfg)))
                {
                    return err;
                }
            }

            if (card->i2s)
            {
                return rockchip_i2s_tdm_hw_params(card->i2s, &i2s_cfg);
            }
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }

    return RT_EOK;
}

static rt_err_t rockchip_audio_card_init(struct rt_audio_device *audio)
{
    return RT_EOK;
}

static void rockchip_audio_card_queue_frame(struct rockchip_audio_card *card)
{
    rt_base_t level = rt_spin_lock_irqsave(&card->replay_lock);

    if (!card->started)
    {
        rt_spin_unlock_irqrestore(&card->replay_lock, level);
        return;
    }
    ++card->replay_callbacks;
    rt_spin_unlock_irqrestore(&card->replay_lock, level);

    if (card->i2s)
    {
        rockchip_i2s_tdm_dma_check_underrun(card->i2s);
    }
    rt_audio_tx_complete(&card->audio);

    level = rt_spin_lock_irqsave(&card->replay_lock);
    if (!--card->replay_callbacks && !card->started)
    {
        rt_completion_done(&card->replay_idle);
    }
    rt_spin_unlock_irqrestore(&card->replay_lock, level);
}

static rt_err_t rockchip_audio_card_start(struct rt_audio_device *audio, int stream)
{
    rt_err_t err;
    struct rockchip_audio_card *card = audio->parent.user_data;

    if (stream != AUDIO_STREAM_REPLAY)
    {
        return -RT_EINVAL;
    }

    if (card->is_hdmi)
    {
        rt_bool_t qp = rt_ofw_node_is_compatible(card->hdmi_np, "rockchip,rk3588-dw-hdmi");

        /* QP enable prepares its controller; legacy DW requires hw_params first. */
        if (qp && (err = rk_hdmi_audio_enable(card->hdmi_np, RT_TRUE)))
        {
            return err;
        }

        err = rk_hdmi_audio_configure(card->hdmi_np,
                card->config.samplerate, card->config.channels,
                card->config.samplebits);
        if (err)
        {
            LOG_E("HDMI audio configure failed: %s", rt_strerror(err));
            rk_hdmi_audio_enable(card->hdmi_np, RT_FALSE);
            return err;
        }
        if (!qp && (err = rk_hdmi_audio_enable(card->hdmi_np, RT_TRUE)))
        {
            return err;
        }
    }
    else if (card->acodec)
    {
        if ((err = rk3528_codec_start(card->acodec)))
        {
            return err;
        }
    }
    else if (card->codec)
    {
        rk817_codec_start(card->codec);
    }

    if (card->sai)
    {
        if ((err = rockchip_sai_start(card->sai)))
        {
            goto _stop_i2s;
        }
    }
    else if (card->i2s)
    {
        if ((err = rockchip_i2s_tdm_start(card->i2s)))
        {
            goto _stop_i2s;
        }

        if (card->use_dma && (err = rockchip_i2s_tdm_dma_enable(card->i2s)))
        {
            goto _stop_i2s;
        }
    }

    card->started = RT_TRUE;
    LOG_D("%s replay via %s", card->name, card->use_dma ? "DMA" : "PIO");

    /* Prime the first replay block; later blocks are queued by DMA callbacks. */
    rockchip_audio_card_queue_frame(card);

    return RT_EOK;

_stop_i2s:
    LOG_E("%s: audio start failed: %s", card->name, rt_strerror(err));

    if (card->sai)
    {
        rockchip_sai_stop(card->sai);
    }
    if (card->i2s && card->use_dma && card->dma_tx)
    {
        rockchip_i2s_tdm_dma_disable(card->i2s);
    }
    if (card->i2s)
    {
        rockchip_i2s_tdm_stop(card->i2s);
    }
    if (card->acodec)
    {
        rk3528_codec_stop(card->acodec);
    }
    if (card->codec)
    {
        rk817_codec_stop(card->codec);
    }
    if (card->is_hdmi)
    {
        rk_hdmi_audio_enable(card->hdmi_np, RT_FALSE);
    }
    return err;
}

static rt_err_t rockchip_audio_card_stop(struct rt_audio_device *audio, int stream)
{
    rt_err_t err, result = RT_EOK;
    rt_base_t level;
    rt_bool_t busy;
    struct rockchip_audio_card *card = audio->parent.user_data;

    if (stream != AUDIO_STREAM_REPLAY)
    {
        return -RT_EINVAL;
    }

    /* The core can wake close() before its callback submits the final silence. */
    level = rt_spin_lock_irqsave(&card->replay_lock);
    card->started = RT_FALSE;
    busy = card->replay_callbacks != 0;
    if (busy)
    {
        rt_completion_init(&card->replay_idle);
    }
    rt_spin_unlock_irqrestore(&card->replay_lock, level);
    if (busy && (result = rt_completion_wait(&card->replay_idle,
            rt_tick_from_millisecond(1000))))
    {
        LOG_E("%s: replay callback did not finish", card->name);
        return result;
    }

    if (card->use_dma && card->dma_tx)
    {
        result = rt_dma_chan_stop(card->dma_tx);
    }

    if (card->i2s)
    {
        if (card->use_dma)
        {
            rockchip_i2s_tdm_dma_disable(card->i2s);
        }

        rockchip_i2s_tdm_stop(card->i2s);
    }
    if (card->sai)
    {
        err = rockchip_sai_stop(card->sai);
        if (!result)
        {
            result = err;
        }
    }
    if (card->acodec)
    {
        rk3528_codec_stop(card->acodec);
    }

    if (!card->is_hdmi && card->codec)
    {
        rk817_codec_stop(card->codec);
    }
    else if (card->is_hdmi)
    {
        rk_hdmi_audio_enable(card->hdmi_np, RT_FALSE);
    }

    if (card->i2s && card->use_dma && rockchip_i2s_tdm_dma_underruns(card->i2s))
    {
        LOG_W("%s: TX FIFO underruns: %u", card->name,
                rockchip_i2s_tdm_dma_underruns(card->i2s));
    }

    return result;
}

static void rockchip_audio_card_dma_tx_done(struct rt_dma_chan *chan, rt_size_t size)
{
    struct rockchip_audio_card *card = chan->priv;

    RT_UNUSED(size);

    rockchip_audio_card_queue_frame(card);
}

static rt_ssize_t rockchip_audio_card_dma_transmit(struct rockchip_audio_card *card,
        const void *write_buf, rt_size_t size)
{
    rt_err_t err;
    struct rt_dma_slave_config config;
    struct rt_dma_slave_transfer transfer;

    rt_memset(&config, 0, sizeof(config));
    config.direction = RT_DMA_MEM_TO_DEV;
    config.src_addr_width = RT_DMA_SLAVE_BUSWIDTH_4_BYTES;
    config.dst_addr_width = RT_DMA_SLAVE_BUSWIDTH_4_BYTES;
    config.src_maxburst = ROCKCHIP_I2S_DMA_BURST;
    config.dst_maxburst = ROCKCHIP_I2S_DMA_BURST;
    config.dst_addr = card->txdr_dma;
    config.src_addr = (write_buf - card->playback_buf) + card->playback_dma;

    if ((err = rt_dma_chan_config(card->dma_tx, &config)))
    {
        LOG_E("DMA config failed: %s", rt_strerror(err));
        return err;
    }

    rt_memset(&transfer, 0, sizeof(transfer));
    transfer.src_addr = config.src_addr;
    transfer.dst_addr = config.dst_addr;
    transfer.buffer_len = size;

    if (size % (config.src_addr_width * config.src_maxburst))
    {
        LOG_E("DMA size %u not burst-aligned", size);
        return -RT_EINVAL;
    }

    if ((err = rt_dma_prep_single(card->dma_tx, &transfer)))
    {
        LOG_E("DMA prep failed: %s", rt_strerror(err));
        return err;
    }

    if ((err = rt_dma_chan_start(card->dma_tx)))
    {
        LOG_E("DMA start failed: %s", rt_strerror(err));
        return err;
    }

    return size;
}

static rt_ssize_t rockchip_audio_card_transmit(struct rt_audio_device *audio,
        const void *writeBuf, void *readBuf, rt_size_t size)
{
    struct rockchip_audio_card *card = audio->parent.user_data;

    RT_UNUSED(readBuf);

    if (!card->started || (!card->i2s && !card->sai))
    {
        return 0;
    }

    if (card->use_dma && card->dma_tx)
    {
        return rockchip_audio_card_dma_transmit(card, writeBuf, size);
    }

    return rockchip_i2s_tdm_push(card->i2s, writeBuf, size);
}

static void rockchip_audio_card_buffer_info(struct rt_audio_device *audio,
        struct rt_audio_buf_info *info)
{
    struct rockchip_audio_card *card = audio->parent.user_data;

    RT_ASSERT(card->playback_buf);
    info->buffer = card->playback_buf;
    info->block_size = RT_AUDIO_REPLAY_MP_BLOCK_SIZE;
    info->block_count = RT_AUDIO_REPLAY_MP_BLOCK_COUNT;
    info->total_size = ROCKCHIP_AUDIO_PLAYBACK_SIZE;
}

static const struct rt_audio_ops rockchip_audio_card_ops =
{
    .getcaps = rockchip_audio_card_getcaps,
    .configure = rockchip_audio_card_configure,
    .init = rockchip_audio_card_init,
    .start = rockchip_audio_card_start,
    .stop = rockchip_audio_card_stop,
    .transmit = rockchip_audio_card_transmit,
    .buffer_info = rockchip_audio_card_buffer_info,
};

static struct rk817_codec *rockchip_audio_card_get_codec(struct rt_ofw_node *codec_np)
{
    struct rk817_codec *codec;
    struct rk8xx *rk8xx;

    codec = rk817_codec_find(codec_np);

    if (codec)
    {
        return codec;
    }

    rk8xx = rk817_codec_rk8xx_from_np(codec_np);

    if (!rk8xx)
    {
        return RT_NULL;
    }

    if (rk817_codec_bind_rk8xx(&codec, rk8xx))
    {
        return RT_NULL;
    }

    return codec;
}

static rt_err_t rockchip_audio_card_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *card_np = dev->ofw_node;
    struct rt_ofw_node *cpu_np, *codec_np;
    struct rockchip_audio_card *card;
    const char *card_name = "rockchip-audio";
    rt_bool_t vendor_hdmi;

    card = rt_calloc(1, sizeof(*card));

    if (!card)
    {
        return -RT_ENOMEM;
    }

    rt_spin_lock_init(&card->replay_lock);
    rt_completion_init(&card->replay_idle);

    vendor_hdmi = rt_ofw_node_is_compatible(card_np, ROCKCHIP_HDMI_CARD);
    rt_ofw_prop_read_string(card_np, vendor_hdmi ? "rockchip,card-name" :
            CARD_PREFIX "name", &card_name);
    rt_strncpy(card->name, card_name, sizeof(card->name) - 1);
    rt_ofw_prop_read_u32(card_np, vendor_hdmi ? "rockchip,mclk-fs" :
            CARD_PREFIX "mclk-fs", &card->mclk_fs);

    if (!card->mclk_fs)
    {
        card->mclk_fs = DEFAULT_MCLK_FS;
    }

    cpu_np = vendor_hdmi ? rt_ofw_parse_phandle(card_np, "rockchip,cpu", 0) :
            rockchip_audio_parse_dai_np(card_np, CARD_PREFIX "cpu");
    codec_np = vendor_hdmi ? rt_ofw_parse_phandle(card_np, "rockchip,codec", 0) :
            rockchip_audio_parse_dai_np(card_np, CARD_PREFIX "codec");

    if (!cpu_np)
    {
        LOG_E("Missing CPU DAI in %s", card->name);
        err = -RT_EINVAL;
        goto _fail;
    }

    card->i2s = rockchip_i2s_tdm_find(cpu_np);
    card->sai = rockchip_sai_find(cpu_np);

    if (!card->i2s && !card->sai)
    {
        LOG_E("CPU DAI %s not ready for %s", cpu_np->name, card->name);
        err = -RT_ENOSYS;
        goto _fail;
    }

    if (codec_np)
    {
        if (rt_ofw_node_is_compatible(codec_np, "rockchip,rk3568-dw-hdmi") ||
            rt_ofw_node_is_compatible(codec_np, "rockchip,rk3528-dw-hdmi") ||
            rt_ofw_node_is_compatible(codec_np, "rockchip,rk3588-dw-hdmi"))
        {
            card->is_hdmi = RT_TRUE;
            card->hdmi_np = codec_np;
            rt_ofw_node_get(card->hdmi_np);
        }
        else if (rt_ofw_node_is_compatible(codec_np, "rockchip,rk3528-codec"))
        {
            card->acodec = rk3528_codec_find(codec_np);
            if (!card->acodec)
            {
                LOG_E("RK3528 codec not ready for %s", card->name);
                err = -RT_ENOSYS;
                goto _fail;
            }
        }
        else
        {
            card->codec = rockchip_audio_card_get_codec(codec_np);

            if (!card->codec)
            {
                LOG_W("Codec not ready for %s", card->name);
            }
        }
    }

    card->config.samplerate = 48000;
    card->config.channels = 2;
    card->config.samplebits = 16;
    card->volume = AUDIO_VOLUME_MAX;
    card->dev = dev;
    card->dma_tx = card->sai ? rockchip_sai_dma_tx(card->sai) :
            rockchip_i2s_tdm_get_dma_tx(card->i2s);
    card->txdr_dma = card->sai ? rockchip_sai_txdr_phys(card->sai) :
            rockchip_i2s_tdm_txdr_phys(card->i2s);

    if (card->dma_tx && card->txdr_dma)
    {
        card->playback_buf = rt_dma_alloc_coherent(dev,
                ROCKCHIP_AUDIO_PLAYBACK_SIZE, &card->playback_dma);

        if (card->playback_buf)
        {
            card->dma_tx->callback = rockchip_audio_card_dma_tx_done;
            card->dma_tx->priv = card;
            card->use_dma = RT_TRUE;
            card->playback_coherent = RT_TRUE;
            LOG_D("%s: DMA playback enabled", card->name);
        }
        else if (!card->sai)
        {
            LOG_W("%s: DMA buffer alloc failed, using PIO", card->name);
        }
    }
    else
    {
        LOG_W("%s: No DMA channel, using PIO", card->name);
    }

    if (!card->playback_buf)
    {
        if (card->sai)
        {
            LOG_E("%s: SAI playback requires DMA and a coherent buffer", card->name);
            err = -RT_ENOMEM;
            goto _fail;
        }
        card->playback_buf = rt_malloc(ROCKCHIP_AUDIO_PLAYBACK_SIZE);
        if (!card->playback_buf)
        {
            err = -RT_ENOMEM;
            goto _fail;
        }
    }

    card->audio.ops = (struct rt_audio_ops *)&rockchip_audio_card_ops;
    card->audio.parent.user_data = card;

    if ((err = rt_audio_register(&card->audio, card->name, RT_DEVICE_FLAG_WRONLY, card)))
    {
        goto _fail;
    }

    dev->user_data = card;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, card);

    rt_ofw_node_put(cpu_np);
    rt_ofw_node_put(codec_np);

    LOG_D("Registered audio card %s", card->name);

    return RT_EOK;

_fail:
    if (card->dma_tx && card->dma_tx->priv == card)
    {
        card->dma_tx->callback = RT_NULL;
        card->dma_tx->priv = RT_NULL;
    }
    rt_ofw_node_put(cpu_np);
    rt_ofw_node_put(codec_np);
    rt_ofw_node_put(card->hdmi_np);
    if (card->playback_buf)
    {
        if (card->playback_coherent)
        {
            rt_dma_free_coherent(card->dev, ROCKCHIP_AUDIO_PLAYBACK_SIZE,
                    card->playback_buf, card->playback_dma);
        }
        else
        {
            rt_free(card->playback_buf);
        }
    }
    rt_free(card);

    return err;
}

static rt_err_t rockchip_audio_card_remove(struct rt_platform_device *pdev)
{
    struct rockchip_audio_card *card = pdev->parent.user_data;

    if (!card)
    {
        return RT_EOK;
    }

    if (card->started)
    {
        rt_err_t err = rockchip_audio_card_stop(&card->audio, AUDIO_STREAM_REPLAY);
        if (err)
        {
            return err;
        }
    }
    if (card->dma_tx && card->dma_tx->priv == card)
    {
        card->dma_tx->callback = RT_NULL;
        card->dma_tx->priv = RT_NULL;
    }
    rt_device_unregister(&card->audio.parent);
    rt_dm_dev_unbind_fwdata(&pdev->parent, RT_NULL);

    if (card->playback_buf)
    {
        if (card->playback_coherent)
        {
            rt_dma_free_coherent(card->dev, ROCKCHIP_AUDIO_PLAYBACK_SIZE,
                    card->playback_buf, card->playback_dma);
        }
        else
        {
            rt_free(card->playback_buf);
        }
    }

    rt_ofw_node_put(card->hdmi_np);

    rt_free(card);

    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_audio_card_ofw_ids[] =
{
    { .compatible = "simple-audio-card" },
    { .compatible = "rockchip,hdmi" },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_audio_card_driver =
{
    .name = "rockchip-audio-card",
    .ids = rockchip_audio_card_ofw_ids,
    .probe = rockchip_audio_card_probe,
    .remove = rockchip_audio_card_remove,
};

static int rockchip_audio_card_register(void)
{
    rt_platform_driver_register(&rockchip_audio_card_driver);

    return 0;
}
INIT_COMPONENT_EXPORT(rockchip_audio_card_register);
