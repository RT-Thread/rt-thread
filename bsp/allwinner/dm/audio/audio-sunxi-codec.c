/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "audio.sunxi.codec"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SUNXI_CODEC_DAC_DPC            0x000
#define SUNXI_CODEC_DAC_VOL_CTL        0x004
#define SUNXI_CODEC_DAC_FIFO_CTL       0x010
#define SUNXI_CODEC_DAC_FIFO_STA       0x014
#define SUNXI_CODEC_DAC_TXDATA         0x020
#define SUNXI_CODEC_DAC_CNT            0x024
#define SUNXI_CODEC_DAC_AN_REG         0x310
#define SUNXI_CODEC_RAMP_REG           0x31c
#define SUNXI_CODEC_HP2_REG            0x340

#define SUNXI_CODEC_DAC_DIG_EN         RT_BIT(31)
#define SUNXI_CODEC_DAC_DVOL_MASK      RT_GENMASK(17, 12)
#define SUNXI_CODEC_DAC_VOL_SEL        RT_BIT(16)
#define SUNXI_CODEC_DAC_VOL_L_MASK     RT_GENMASK(15, 8)
#define SUNXI_CODEC_DAC_VOL_R_MASK     RT_GENMASK(7, 0)
#define SUNXI_CODEC_DAC_FS_MASK        RT_GENMASK(31, 29)
#define SUNXI_CODEC_DAC_FIFO_MODE_MASK RT_GENMASK(25, 24)
#define SUNXI_CODEC_DAC_MONO_EN        RT_BIT(6)
#define SUNXI_CODEC_DAC_SAMPLE_BITS    RT_BIT(5)
#define SUNXI_CODEC_DAC_DRQ_EN         RT_BIT(4)
#define SUNXI_CODEC_DAC_FIFO_FLUSH     RT_BIT(0)
#define SUNXI_CODEC_DAC_TXE_INT        RT_BIT(3)
#define SUNXI_CODEC_DAC_TXU_INT        RT_BIT(2)
#define SUNXI_CODEC_DAC_TXO_INT        RT_BIT(1)
#define SUNXI_CODEC_DAC_CH_L_EN        RT_BIT(15)
#define SUNXI_CODEC_DAC_CH_R_EN        RT_BIT(14)
#define SUNXI_CODEC_DAC_LMUTE          RT_BIT(12)
#define SUNXI_CODEC_DAC_RMUTE          RT_BIT(10)
#define SUNXI_CODEC_RAMP_RK_OPT_EN     RT_BIT(21)
#define SUNXI_CODEC_RAMP_RMC_EN        RT_BIT(1)
#define SUNXI_CODEC_HP_BUF_EN          RT_BIT(31)
#define SUNXI_CODEC_HP_DRVEN           RT_BIT(21)
#define SUNXI_CODEC_HP_RSWITCH         RT_BIT(19)
#define SUNXI_CODEC_HP_FB_IN_EN        RT_BIT(17)
#define SUNXI_CODEC_HP_RAMP_OUT_EN     RT_BIT(15)

#define SUNXI_CODEC_BUFFER_SIZE        16384
#define SUNXI_CODEC_BLOCK_SIZE         4096
struct sunxi_codec_rate
{
    rt_uint32_t rate;
    rt_uint32_t value;
};

struct sunxi_codec
{
    struct rt_audio_device parent;

    struct rt_device *dev;
    void *base;
    struct rt_clk_array *clks;
    struct rt_reset_control *reset;
    struct rt_dma_chan *dma_tx;
    rt_uint8_t *playback_buffer;
    rt_ubase_t playback_dma;
    rt_ubase_t fifo_dma;
    rt_base_t spk_enable_pin;
    rt_uint8_t spk_enable_active;
    rt_uint32_t spk_enable_delay_ms;
    struct rt_audio_configure config;
    struct rt_work dma_done_work;
    rt_uint32_t volume;
    rt_bool_t clks_enabled;
    rt_bool_t running;
};

#define to_sunxi_codec(raw) \
    rt_container_of(raw, struct sunxi_codec, parent)

static const struct sunxi_codec_rate sunxi_codec_rates[] =
{
    { 8000, 5 },
    { 12000, 4 },
    { 16000, 3 },
    { 24000, 2 },
    { 32000, 1 },
    { 48000, 0 },
    { 96000, 7 },
    { 192000, 6 },
};

static rt_uint32_t sunxi_codec_readl(struct sunxi_codec *codec,
        rt_uint32_t offset)
{
    return HWREG32(codec->base + offset);
}

static void sunxi_codec_writel(struct sunxi_codec *codec, rt_uint32_t value,
        rt_uint32_t offset)
{
    HWREG32(codec->base + offset) = value;
}

static void sunxi_codec_update_bits(struct sunxi_codec *codec,
        rt_uint32_t offset, rt_uint32_t mask, rt_uint32_t value)
{
    rt_uint32_t reg = sunxi_codec_readl(codec, offset);

    reg &= ~mask;
    reg |= value & mask;
    sunxi_codec_writel(codec, reg, offset);
}

static const struct sunxi_codec_rate *sunxi_codec_find_rate(rt_uint32_t rate)
{
    rt_size_t index;

    for (index = 0; index < RT_ARRAY_SIZE(sunxi_codec_rates); ++index)
    {
        if (sunxi_codec_rates[index].rate == rate)
        {
            return &sunxi_codec_rates[index];
        }
    }

    return RT_NULL;
}

static void sunxi_codec_set_volume(struct sunxi_codec *codec,
        rt_uint32_t volume)
{
    rt_uint32_t value;

    if (volume > AUDIO_VOLUME_MAX)
    {
        volume = AUDIO_VOLUME_MAX;
    }
    value = 63 - volume * 63 / AUDIO_VOLUME_MAX;
    sunxi_codec_update_bits(codec, SUNXI_CODEC_DAC_DPC,
            SUNXI_CODEC_DAC_DVOL_MASK, value << 12);
    codec->volume = volume;
}

static rt_err_t sunxi_codec_apply_config(struct sunxi_codec *codec,
        const struct rt_audio_configure *config)
{
    const struct sunxi_codec_rate *rate;
    rt_uint32_t fifo_ctl;

    if (!config->channels || config->channels > 2 ||
            (config->samplebits != 16 && config->samplebits != 24 &&
             config->samplebits != 32))
    {
        return -RT_EINVAL;
    }

    rate = sunxi_codec_find_rate(config->samplerate);
    if (!rate)
    {
        return -RT_ENOSYS;
    }

    fifo_ctl = sunxi_codec_readl(codec, SUNXI_CODEC_DAC_FIFO_CTL);
    fifo_ctl &= ~(SUNXI_CODEC_DAC_FS_MASK |
            SUNXI_CODEC_DAC_FIFO_MODE_MASK |
            SUNXI_CODEC_DAC_MONO_EN |
            SUNXI_CODEC_DAC_SAMPLE_BITS);
    fifo_ctl |= rate->value << 29;
    if (config->samplebits == 16)
    {
        fifo_ctl |= 3 << 24;
    }
    else
    {
        fifo_ctl |= SUNXI_CODEC_DAC_SAMPLE_BITS;
    }
    if (config->channels == 1)
    {
        fifo_ctl |= SUNXI_CODEC_DAC_MONO_EN;
    }
    sunxi_codec_writel(codec, fifo_ctl, SUNXI_CODEC_DAC_FIFO_CTL);
    codec->config = *config;

    return RT_EOK;
}

static void sunxi_codec_output_enable(struct sunxi_codec *codec)
{
    sunxi_codec_update_bits(codec, SUNXI_CODEC_DAC_FIFO_CTL,
            SUNXI_CODEC_DAC_FIFO_FLUSH, SUNXI_CODEC_DAC_FIFO_FLUSH);
    sunxi_codec_writel(codec, SUNXI_CODEC_DAC_TXE_INT |
            SUNXI_CODEC_DAC_TXU_INT | SUNXI_CODEC_DAC_TXO_INT,
            SUNXI_CODEC_DAC_FIFO_STA);
    sunxi_codec_writel(codec, 0, SUNXI_CODEC_DAC_CNT);
    sunxi_codec_update_bits(codec, SUNXI_CODEC_DAC_AN_REG,
            SUNXI_CODEC_DAC_CH_L_EN | SUNXI_CODEC_DAC_CH_R_EN |
            SUNXI_CODEC_DAC_LMUTE | SUNXI_CODEC_DAC_RMUTE,
            SUNXI_CODEC_DAC_CH_L_EN | SUNXI_CODEC_DAC_CH_R_EN |
            SUNXI_CODEC_DAC_LMUTE | SUNXI_CODEC_DAC_RMUTE);
    sunxi_codec_update_bits(codec, SUNXI_CODEC_HP2_REG,
            SUNXI_CODEC_HP_BUF_EN | SUNXI_CODEC_HP_FB_IN_EN |
            SUNXI_CODEC_HP_RAMP_OUT_EN | SUNXI_CODEC_HP_RSWITCH |
            SUNXI_CODEC_HP_DRVEN,
            SUNXI_CODEC_HP_BUF_EN | SUNXI_CODEC_HP_FB_IN_EN |
            SUNXI_CODEC_HP_RAMP_OUT_EN | SUNXI_CODEC_HP_RSWITCH |
            SUNXI_CODEC_HP_DRVEN);
    sunxi_codec_update_bits(codec, SUNXI_CODEC_DAC_DPC,
            SUNXI_CODEC_DAC_DIG_EN, SUNXI_CODEC_DAC_DIG_EN);
    if (codec->spk_enable_pin >= 0)
    {
        rt_pin_write(codec->spk_enable_pin, codec->spk_enable_active);
        if (codec->spk_enable_delay_ms)
        {
            rt_thread_mdelay(codec->spk_enable_delay_ms);
        }
    }
}

static void sunxi_codec_output_disable(struct sunxi_codec *codec)
{
    if (codec->spk_enable_pin >= 0)
    {
        rt_pin_write(codec->spk_enable_pin, !codec->spk_enable_active);
    }
    sunxi_codec_update_bits(codec, SUNXI_CODEC_DAC_FIFO_CTL,
            SUNXI_CODEC_DAC_DRQ_EN, 0);
    sunxi_codec_update_bits(codec, SUNXI_CODEC_HP2_REG,
            SUNXI_CODEC_HP_DRVEN | SUNXI_CODEC_HP_RAMP_OUT_EN |
            SUNXI_CODEC_HP_RSWITCH | SUNXI_CODEC_HP_BUF_EN |
            SUNXI_CODEC_HP_FB_IN_EN, 0);
    sunxi_codec_update_bits(codec, SUNXI_CODEC_DAC_DPC,
            SUNXI_CODEC_DAC_DIG_EN, 0);
    sunxi_codec_update_bits(codec, SUNXI_CODEC_DAC_AN_REG,
            SUNXI_CODEC_DAC_CH_L_EN | SUNXI_CODEC_DAC_CH_R_EN |
            SUNXI_CODEC_DAC_LMUTE | SUNXI_CODEC_DAC_RMUTE, 0);
}

static rt_err_t sunxi_codec_getcaps(struct rt_audio_device *audio,
        struct rt_audio_caps *caps)
{
    struct sunxi_codec *codec = to_sunxi_codec(audio);

    switch (caps->main_type)
    {
    case AUDIO_TYPE_QUERY:
        if (caps->sub_type != AUDIO_TYPE_QUERY)
        {
            return -RT_ENOSYS;
        }
        caps->udata.mask = AUDIO_TYPE_OUTPUT | AUDIO_TYPE_MIXER;
        return RT_EOK;

    case AUDIO_TYPE_OUTPUT:
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            caps->udata.config = codec->config;
            return RT_EOK;
        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate = codec->config.samplerate;
            return RT_EOK;
        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels = codec->config.channels;
            return RT_EOK;
        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits = codec->config.samplebits;
            return RT_EOK;
        default:
            return -RT_ENOSYS;
        }

    case AUDIO_TYPE_MIXER:
        if (caps->sub_type != AUDIO_MIXER_VOLUME)
        {
            return -RT_ENOSYS;
        }
        caps->udata.value = codec->volume;
        return RT_EOK;

    default:
        return -RT_ENOSYS;
    }
}

static rt_err_t sunxi_codec_configure(struct rt_audio_device *audio,
        struct rt_audio_caps *caps)
{
    struct rt_audio_configure config;
    struct sunxi_codec *codec = to_sunxi_codec(audio);

    if (codec->running)
    {
        return -RT_EBUSY;
    }

    if (caps->main_type == AUDIO_TYPE_MIXER)
    {
        if (caps->sub_type != AUDIO_MIXER_VOLUME || caps->udata.value < 0 ||
                caps->udata.value > AUDIO_VOLUME_MAX)
        {
            return -RT_EINVAL;
        }
        sunxi_codec_set_volume(codec, caps->udata.value);
        return RT_EOK;
    }

    if (caps->main_type != AUDIO_TYPE_OUTPUT)
    {
        return -RT_ENOSYS;
    }

    config = codec->config;
    switch (caps->sub_type)
    {
    case AUDIO_DSP_PARAM:
        config = caps->udata.config;
        break;
    case AUDIO_DSP_SAMPLERATE:
        config.samplerate = caps->udata.config.samplerate;
        break;
    case AUDIO_DSP_CHANNELS:
        config.channels = caps->udata.config.channels;
        break;
    case AUDIO_DSP_SAMPLEBITS:
        config.samplebits = caps->udata.config.samplebits;
        break;
    default:
        return -RT_ENOSYS;
    }

    return sunxi_codec_apply_config(codec, &config);
}

static rt_err_t sunxi_codec_init(struct rt_audio_device *audio)
{
    struct sunxi_codec *codec = to_sunxi_codec(audio);
    struct rt_audio_configure config;

    config.samplerate = 48000;
    config.channels = 2;
    config.samplebits = 16;

    sunxi_codec_update_bits(codec, SUNXI_CODEC_RAMP_REG,
            SUNXI_CODEC_RAMP_RMC_EN | SUNXI_CODEC_RAMP_RK_OPT_EN,
            SUNXI_CODEC_RAMP_RMC_EN | SUNXI_CODEC_RAMP_RK_OPT_EN);
    sunxi_codec_update_bits(codec, SUNXI_CODEC_DAC_VOL_CTL,
            SUNXI_CODEC_DAC_VOL_SEL | SUNXI_CODEC_DAC_VOL_L_MASK |
            SUNXI_CODEC_DAC_VOL_R_MASK,
            SUNXI_CODEC_DAC_VOL_SEL | (160 << 8) | 160);
    sunxi_codec_set_volume(codec, AUDIO_VOLUME_MAX);

    return sunxi_codec_apply_config(codec, &config);
}

static rt_err_t sunxi_codec_start(struct rt_audio_device *audio, int stream)
{
    struct sunxi_codec *codec = to_sunxi_codec(audio);

    if (stream != AUDIO_STREAM_REPLAY)
    {
        return -RT_ENOSYS;
    }

    sunxi_codec_output_enable(codec);
    codec->running = RT_TRUE;
    rt_audio_tx_complete(&codec->parent);

    return RT_EOK;
}

static rt_err_t sunxi_codec_stop(struct rt_audio_device *audio, int stream)
{
    struct sunxi_codec *codec = to_sunxi_codec(audio);

    if (stream != AUDIO_STREAM_REPLAY)
    {
        return -RT_ENOSYS;
    }

    codec->running = RT_FALSE;
    rt_dma_chan_stop(codec->dma_tx);
    rt_work_cancel(&codec->dma_done_work);
    sunxi_codec_output_disable(codec);

    return RT_EOK;
}

static rt_ssize_t sunxi_codec_transmit(struct rt_audio_device *audio,
        const void *write_buf, void *read_buf, rt_size_t size)
{
    rt_err_t err;
    enum rt_dma_slave_buswidth width;
    rt_ubase_t offset;
    const rt_uint8_t *buffer = write_buf;
    struct rt_dma_slave_config config;
    struct rt_dma_slave_transfer transfer;
    struct sunxi_codec *codec = to_sunxi_codec(audio);

    if (!codec->running || !write_buf || read_buf || !size ||
            size > SUNXI_CODEC_BLOCK_SIZE)
    {
        return -RT_EINVAL;
    }

    if (buffer < codec->playback_buffer ||
            buffer >= codec->playback_buffer + SUNXI_CODEC_BUFFER_SIZE)
    {
        return -RT_EINVAL;
    }

    offset = buffer - codec->playback_buffer;
    if (offset + size > SUNXI_CODEC_BUFFER_SIZE)
    {
        return -RT_EINVAL;
    }

    width = codec->config.samplebits == 16 ?
            RT_DMA_SLAVE_BUSWIDTH_2_BYTES : RT_DMA_SLAVE_BUSWIDTH_4_BYTES;
    if ((offset % width) || (size % width))
    {
        return -RT_EINVAL;
    }

    rt_memset(&config, 0, sizeof(config));
    config.direction = RT_DMA_MEM_TO_DEV;
    config.src_addr_width = width;
    config.dst_addr_width = width;
    config.src_maxburst = 4;
    config.dst_maxburst = 4;
    config.src_addr = codec->playback_dma + offset;
    config.dst_addr = codec->fifo_dma;
    if ((err = rt_dma_chan_config(codec->dma_tx, &config)))
    {
        return err;
    }

    rt_memset(&transfer, 0, sizeof(transfer));
    transfer.buffer = (void *)write_buf;
    transfer.buffer_len = size;
    transfer.src_addr = config.src_addr;
    transfer.dst_addr = config.dst_addr;
    if ((err = rt_dma_prep_single(codec->dma_tx, &transfer)))
    {
        return err;
    }

    if ((err = rt_dma_chan_start(codec->dma_tx)))
    {
        return err;
    }
    sunxi_codec_update_bits(codec, SUNXI_CODEC_DAC_FIFO_CTL,
            SUNXI_CODEC_DAC_DRQ_EN, SUNXI_CODEC_DAC_DRQ_EN);

    return size;
}

static void sunxi_codec_buffer_info(struct rt_audio_device *audio,
        struct rt_audio_buf_info *info)
{
    struct sunxi_codec *codec = to_sunxi_codec(audio);

    info->buffer = codec->playback_buffer;
    info->total_size = SUNXI_CODEC_BUFFER_SIZE;
    info->block_size = SUNXI_CODEC_BLOCK_SIZE;
    info->block_count = SUNXI_CODEC_BUFFER_SIZE / SUNXI_CODEC_BLOCK_SIZE;
}

static const struct rt_audio_ops sunxi_codec_ops =
{
    .getcaps = sunxi_codec_getcaps,
    .configure = sunxi_codec_configure,
    .init = sunxi_codec_init,
    .start = sunxi_codec_start,
    .stop = sunxi_codec_stop,
    .transmit = sunxi_codec_transmit,
    .buffer_info = sunxi_codec_buffer_info,
};

static void sunxi_codec_dma_done_work(struct rt_work *work, void *work_data)
{
    struct sunxi_codec *codec = work_data;

    RT_UNUSED(work);

    if (codec->running)
    {
        rt_audio_tx_complete(&codec->parent);
    }
}

static void sunxi_codec_dma_done(struct rt_dma_chan *chan, rt_size_t size)
{
    struct sunxi_codec *codec = chan->priv;

    if (codec->running && size)
    {
        rt_work_submit(&codec->dma_done_work, 0);
    }
}

static void sunxi_codec_release(struct sunxi_codec *codec)
{
    codec->running = RT_FALSE;
    rt_work_cancel(&codec->dma_done_work);
    if (!rt_is_err_or_null(codec->dma_tx))
    {
        rt_dma_chan_stop(codec->dma_tx);
        rt_dma_chan_release(codec->dma_tx);
    }
    if (codec->playback_buffer)
    {
        rt_dma_free_coherent(codec->dev, SUNXI_CODEC_BUFFER_SIZE,
                codec->playback_buffer, codec->playback_dma);
    }
    if (!rt_is_err_or_null(codec->reset))
    {
        rt_reset_control_assert(codec->reset);
        rt_reset_control_put(codec->reset);
    }
    if (!rt_is_err_or_null(codec->clks))
    {
        if (codec->clks_enabled)
        {
            rt_clk_array_disable_unprepare(codec->clks);
        }
        rt_clk_array_put(codec->clks);
    }
    if (codec->base)
    {
        rt_iounmap(codec->base);
    }
    rt_free(codec);
}

static rt_err_t sunxi_codec_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *name;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_codec *codec = rt_calloc(1, sizeof(*codec));

    if (!codec)
    {
        return -RT_ENOMEM;
    }

    rt_work_init(&codec->dma_done_work, sunxi_codec_dma_done_work, codec);

    codec->dev = dev;
    codec->spk_enable_pin = PIN_NONE;
    codec->base = rt_dm_dev_iomap(dev, 0);
    if (!codec->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    codec->clks = rt_clk_get_array(dev);
    codec->reset = rt_reset_control_get_by_name(dev, "bus");
    if (rt_is_err(codec->clks) || rt_is_err(codec->reset))
    {
        err = rt_is_err(codec->clks) ? rt_ptr_err(codec->clks) :
                rt_ptr_err(codec->reset);
        goto _fail;
    }
    if ((err = rt_clk_array_prepare_enable(codec->clks)))
    {
        goto _fail;
    }
    codec->clks_enabled = RT_TRUE;
    if ((err = rt_reset_control_deassert(codec->reset)))
    {
        goto _fail;
    }

    codec->spk_enable_pin = rt_pin_get_named_pin(dev, "spk-enable", 0,
            RT_NULL, &codec->spk_enable_active);
    if (codec->spk_enable_pin >= 0)
    {
        rt_pin_mode(codec->spk_enable_pin, PIN_MODE_OUTPUT);
        rt_pin_write(codec->spk_enable_pin, !codec->spk_enable_active);
    }
    rt_dm_dev_prop_read_u32(dev, "allwinner,spk-enable-delay-ms",
            &codec->spk_enable_delay_ms);

    codec->playback_buffer = rt_dma_alloc_coherent(dev,
            SUNXI_CODEC_BUFFER_SIZE, &codec->playback_dma);
    if (!codec->playback_buffer)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    codec->dma_tx = rt_dma_chan_request(dev, "tx");
    if (rt_is_err(codec->dma_tx))
    {
        err = rt_ptr_err(codec->dma_tx);
        LOG_E("request TX DMA channel failed: %s", rt_strerror(err));
        goto _fail;
    }
    codec->dma_tx->callback = sunxi_codec_dma_done;
    codec->dma_tx->priv = codec;
    codec->fifo_dma = (rt_ubase_t)rt_kmem_v2p(codec->base) +
            SUNXI_CODEC_DAC_TXDATA;

    rt_dm_dev_set_name_auto(&codec->parent.parent, "sound");
    name = rt_dm_dev_get_name(&codec->parent.parent);
    codec->parent.ops = (struct rt_audio_ops *)&sunxi_codec_ops;
    if ((err = rt_audio_register(&codec->parent, name,
            RT_DEVICE_FLAG_WRONLY, codec)))
    {
        goto _fail;
    }

    dev->user_data = codec;
    return RT_EOK;

_fail:
    LOG_E("probe failed: %s", rt_strerror(err));
    sunxi_codec_release(codec);
    return err;
}

static rt_err_t sunxi_codec_remove(struct rt_platform_device *pdev)
{
    struct sunxi_codec *codec = pdev->parent.user_data;

    sunxi_codec_stop(&codec->parent, AUDIO_STREAM_REPLAY);
    rt_device_unregister(&codec->parent.parent);
    sunxi_codec_release(codec);

    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_codec_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-codec" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_codec_driver =
{
    .name = "sunxi-codec",
    .ids = sunxi_codec_ofw_ids,
    .probe = sunxi_codec_probe,
    .remove = sunxi_codec_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_codec_driver);
