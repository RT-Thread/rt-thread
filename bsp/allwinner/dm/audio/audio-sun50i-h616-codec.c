/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "audio.h616"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "audio-sunxi.h"

#define H616_DAC_DPC            0x000
#define H616_DAC_FIFOC          0x010
#define H616_DAC_FIFO_STA       0x014
#define H616_DAC_TXDATA         0x020
#define H616_DAC_CNT            0x024
#define H616_DAC_DAP_CTL        0x0f0
#define H616_DAC_AC_DAC         0x310
#define H616_DAC_AC_MIXER       0x314
#define H616_DAC_AC_RAMP        0x31c

#define H616_DAC_EN             RT_BIT(31)
#define H616_DAC_HPF_EN         RT_BIT(18)
#define H616_DAC_DVOL_MASK      RT_GENMASK(17, 12)
#define H616_DAC_FS_MASK        RT_GENMASK(31, 29)
#define H616_DAC_FIFO_MODE_MASK RT_GENMASK(25, 24)
#define H616_DAC_MONO           RT_BIT(6)
#define H616_DAC_SAMPLE_24      RT_BIT(5)
#define H616_DAC_DRQ_EN         RT_BIT(4)
#define H616_DAC_FIFO_FLUSH     RT_BIT(0)
#define H616_DAC_TXE_INT        RT_BIT(3)
#define H616_DAC_TXU_INT        RT_BIT(2)
#define H616_DAC_TXO_INT        RT_BIT(1)

#define H616_DAC_LEN            RT_BIT(15)
#define H616_DAC_REN            RT_BIT(14)
#define H616_LINEOUTL_EN        RT_BIT(13)
#define H616_DAC_LMUTE          RT_BIT(12)
#define H616_LINEOUTR_EN        RT_BIT(11)
#define H616_DAC_RMUTE          RT_BIT(10)
#define H616_DAC_RAMP_EN        RT_BIT(8)
#define H616_LINEOUT_VOL_MASK   RT_GENMASK(4, 0)
#define H616_LMIX_DACL          RT_BIT(21)
#define H616_RMIX_DACR          RT_BIT(17)
#define H616_LMIX_EN            RT_BIT(11)
#define H616_RMIX_EN            RT_BIT(10)
#define H616_RAMP_RDEN          RT_BIT(0)

struct h616_codec_rate
{
    rt_uint32_t rate;
    rt_uint8_t fifo_rate;
    rt_uint32_t mclk_rate;
};

struct h616_codec
{
    struct sunxi_audio_output output;
    void *base;
    struct rt_clk_array *clks;
    struct rt_clk *clk_1x;
    struct rt_reset_control *reset;
    rt_bool_t clks_enabled;
};

#define to_h616_codec(raw) \
    rt_container_of(raw, struct h616_codec, output)

static const struct h616_codec_rate h616_codec_rates[] = {
    { 8000, 5, 49152000 },
    { 11025, 4, 45158400 },
    { 12000, 4, 49152000 },
    { 16000, 3, 49152000 },
    { 22050, 2, 45158400 },
    { 24000, 2, 49152000 },
    { 32000, 1, 49152000 },
    { 44100, 0, 45158400 },
    { 48000, 0, 49152000 },
    { 88200, 7, 45158400 },
    { 96000, 7, 49152000 },
    { 176400, 6, 45158400 },
    { 192000, 6, 49152000 },
};

static rt_uint32_t h616_codec_readl(struct h616_codec *codec,
                                    rt_uint32_t offset)
{
    return HWREG32(codec->base + offset);
}

static void h616_codec_writel(struct h616_codec *codec, rt_uint32_t value,
                              rt_uint32_t offset)
{
    HWREG32(codec->base + offset) = value;
}

static void h616_codec_update_bits(struct h616_codec *codec,
                                   rt_uint32_t offset, rt_uint32_t mask, rt_uint32_t value)
{
    rt_uint32_t reg = h616_codec_readl(codec, offset);

    h616_codec_writel(codec, (reg & ~mask) | (value & mask), offset);
}

static const struct h616_codec_rate *h616_codec_find_rate(rt_uint32_t rate)
{
    rt_size_t i;

    for (i = 0; i < RT_ARRAY_SIZE(h616_codec_rates); ++i)
    {
        if (h616_codec_rates[i].rate == rate)
        {
            return &h616_codec_rates[i];
        }
    }

    return RT_NULL;
}

static rt_err_t h616_codec_configure(struct sunxi_audio_output *output,
                                     const struct rt_audio_configure *config)
{
    const struct h616_codec_rate *rate;
    rt_uint32_t fifo;
    struct h616_codec *codec = to_h616_codec(output);

    if (!config->channels || config->channels > 2 ||
        (config->samplebits != 16 && config->samplebits != 24 &&
         config->samplebits != 32))
    {
        return -RT_EINVAL;
    }
    rate = h616_codec_find_rate(config->samplerate);
    if (!rate)
    {
        return -RT_ENOSYS;
    }
    if (rt_clk_set_rate(codec->clk_1x, rate->mclk_rate))
    {
        return -RT_EIO;
    }

    fifo = h616_codec_readl(codec, H616_DAC_FIFOC);
    fifo &= ~(H616_DAC_FS_MASK | H616_DAC_FIFO_MODE_MASK |
              H616_DAC_MONO | H616_DAC_SAMPLE_24);
    fifo |= (rt_uint32_t)rate->fifo_rate << 29;
    if (config->samplebits == 16)
    {
        fifo |= 3U << 24;
    }
    else
    {
        fifo |= H616_DAC_SAMPLE_24;
    }
    if (config->channels == 1)
    {
        fifo |= H616_DAC_MONO;
    }
    h616_codec_writel(codec, fifo, H616_DAC_FIFOC);

    return RT_EOK;
}

static rt_err_t h616_codec_init(struct sunxi_audio_output *output)
{
    struct h616_codec *codec = to_h616_codec(output);

    h616_codec_writel(codec, 0, H616_DAC_DAP_CTL);
    h616_codec_update_bits(codec, H616_DAC_DPC, H616_DAC_HPF_EN | H616_DAC_DVOL_MASK, H616_DAC_HPF_EN);
    h616_codec_update_bits(codec, H616_DAC_AC_DAC, H616_LINEOUT_VOL_MASK | H616_DAC_LMUTE | H616_DAC_RMUTE | H616_DAC_RAMP_EN,
                           0x1a | H616_DAC_LMUTE | H616_DAC_RMUTE | H616_DAC_RAMP_EN);
    h616_codec_update_bits(codec, H616_DAC_AC_MIXER, H616_LMIX_DACL | H616_RMIX_DACR | H616_LMIX_EN | H616_RMIX_EN,
                           H616_LMIX_DACL | H616_RMIX_DACR | H616_LMIX_EN | H616_RMIX_EN);

    return RT_EOK;
}

static rt_err_t h616_codec_start(struct sunxi_audio_output *output)
{
    struct h616_codec *codec = to_h616_codec(output);

    h616_codec_update_bits(codec, H616_DAC_FIFOC, H616_DAC_FIFO_FLUSH,
                           H616_DAC_FIFO_FLUSH);
    h616_codec_writel(codec, H616_DAC_TXE_INT | H616_DAC_TXU_INT | H616_DAC_TXO_INT, H616_DAC_FIFO_STA);
    h616_codec_writel(codec, 0, H616_DAC_CNT);
    h616_codec_update_bits(codec, H616_DAC_DPC, H616_DAC_EN, H616_DAC_EN);
    h616_codec_update_bits(codec, H616_DAC_AC_RAMP, H616_RAMP_RDEN,
                           H616_RAMP_RDEN);
    rt_thread_mdelay(25);
    h616_codec_update_bits(codec, H616_DAC_AC_DAC, H616_LINEOUTL_EN | H616_LINEOUTR_EN, H616_LINEOUTL_EN | H616_LINEOUTR_EN);

    return RT_EOK;
}

static void h616_codec_stop(struct sunxi_audio_output *output)
{
    struct h616_codec *codec = to_h616_codec(output);

    h616_codec_update_bits(codec, H616_DAC_FIFOC, H616_DAC_DRQ_EN, 0);
    h616_codec_update_bits(codec, H616_DAC_AC_RAMP, H616_RAMP_RDEN, 0);
    rt_thread_mdelay(25);
    h616_codec_update_bits(codec, H616_DAC_AC_DAC, H616_LINEOUTL_EN | H616_LINEOUTR_EN, 0);
    h616_codec_update_bits(codec, H616_DAC_DPC, H616_DAC_EN, 0);
}

static void h616_codec_enable_dma(struct sunxi_audio_output *output,
                                  rt_bool_t enable)
{
    struct h616_codec *codec = to_h616_codec(output);

    h616_codec_update_bits(codec, H616_DAC_FIFOC, H616_DAC_DRQ_EN,
                           enable ? H616_DAC_DRQ_EN : 0);
}

static const struct sunxi_audio_output_ops h616_codec_output_ops = {
    .init = h616_codec_init,
    .configure = h616_codec_configure,
    .start = h616_codec_start,
    .stop = h616_codec_stop,
    .enable_dma = h616_codec_enable_dma,
};

static void h616_codec_release(struct h616_codec *codec)
{
    sunxi_audio_output_release(&codec->output);
    if (!rt_is_err_or_null(codec->reset))
    {
        rt_reset_control_assert(codec->reset);
        rt_reset_control_put(codec->reset);
    }
    if (!rt_is_err_or_null(codec->clk_1x))
    {
        rt_clk_put(codec->clk_1x);
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

static rt_err_t h616_codec_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct h616_codec *codec = rt_calloc(1, sizeof(*codec));

    if (!codec)
    {
        return -RT_ENOMEM;
    }
    codec->output.dev = dev;
    codec->base = rt_dm_dev_iomap(dev, 0);
    codec->clks = rt_clk_get_array(dev);
    codec->clk_1x = rt_clk_get_by_name(dev, "audio-codec-1x");
    codec->reset = rt_reset_control_get_by_index(dev, 0);
    if (!codec->base || rt_is_err(codec->clks) || rt_is_err(codec->clk_1x) ||
        rt_is_err(codec->reset))
    {
        err = -RT_EIO;
        goto fail;
    }
    /* Program a valid audio PLL before the array enables its module gates. */
    if ((err = rt_clk_set_rate(codec->clk_1x, 49152000)) ||
        (err = rt_clk_array_prepare_enable(codec->clks)) ||
        (err = rt_reset_control_deassert(codec->reset)))
    {
        goto fail;
    }
    codec->clks_enabled = RT_TRUE;
    codec->output.config.samplerate = 48000;
    codec->output.config.channels = 2;
    codec->output.config.samplebits = 16;
    codec->output.ops = &h616_codec_output_ops;
    codec->output.playback_buffer = rt_dma_alloc_coherent(dev,
                                                          SUNXI_AUDIO_BUFFER_SIZE, &codec->output.playback_dma);
    if (!codec->output.playback_buffer)
    {
        err = -RT_ENOMEM;
        goto fail;
    }
    codec->output.dma_tx = rt_dma_chan_request(dev, "tx");
    if (rt_is_err(codec->output.dma_tx))
    {
        err = rt_ptr_err(codec->output.dma_tx);
        goto fail;
    }
    codec->output.dma_tx->callback = sunxi_audio_output_dma_done;
    codec->output.dma_tx->priv = &codec->output;
    codec->output.fifo_dma = (rt_ubase_t)rt_kmem_v2p(codec->base) +
                             H616_DAC_TXDATA;
    if ((err = sunxi_audio_output_register(&codec->output, "sound", codec)))
    {
        goto fail;
    }

    dev->user_data = codec;
    return RT_EOK;

fail:
    LOG_E("probe failed: %s", rt_strerror(err));
    h616_codec_release(codec);
    return err;
}

static rt_err_t h616_codec_remove(struct rt_platform_device *pdev)
{
    struct h616_codec *codec = pdev->parent.user_data;

    sunxi_audio_output_stop(&codec->output);
    rt_device_unregister(&codec->output.parent.parent);
    h616_codec_release(codec);
    return RT_EOK;
}

static const struct rt_ofw_node_id h616_codec_ofw_ids[] = {
    { .compatible = "allwinner,sun50i-h616-codec" },
    {}
};

static struct rt_platform_driver h616_codec_driver = {
    .name = "sun50i-h616-codec",
    .ids = h616_codec_ofw_ids,
    .probe = h616_codec_probe,
    .remove = h616_codec_remove,
};
RT_PLATFORM_DRIVER_EXPORT(h616_codec_driver);
