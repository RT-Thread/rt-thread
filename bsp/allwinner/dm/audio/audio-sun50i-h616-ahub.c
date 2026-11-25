/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "audio.ahub"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "audio-sunxi.h"
#include "sunxi-h616-hdmi.h"

/* H616 AHUB register layout, shared by all APBIF and I2S instances. */
#define AHUB_RST                  0x008
#define AHUB_GAT                  0x00c
#define AHUB_APBIF_TX_CTL(n)      (0x010 + (n) * 0x30)
#define AHUB_APBIF_TX_IRQ_CTL(n)  (0x014 + (n) * 0x30)
#define AHUB_APBIF_TX_IRQ_STA(n)  (0x018 + (n) * 0x30)
#define AHUB_APBIF_TXFIFO_CTL(n)  (0x020 + (n) * 0x30)
#define AHUB_APBIF_TXFIFO(n)      (0x030 + (n) * 0x30)
#define AHUB_I2S_CTL(n)           (0x200 + (n) * 0x100)
#define AHUB_I2S_FMT0(n)          (0x204 + (n) * 0x100)
#define AHUB_I2S_FMT1(n)          (0x208 + (n) * 0x100)
#define AHUB_I2S_CHCFG(n)         (0x224 + (n) * 0x100)
#define AHUB_I2S_OUT_SLOT0(n)     (0x230 + (n) * 0x100)
#define AHUB_I2S_OUT_CH0MAP0(n)   (0x234 + (n) * 0x100)
#define AHUB_I2S_OUT_CH1MAP0(n)   (0x244 + (n) * 0x100)
#define AHUB_I2S_OUT_CH2MAP0(n)   (0x254 + (n) * 0x100)
#define AHUB_I2S_OUT_CH3MAP0(n)   (0x264 + (n) * 0x100)

#define AHUB_APBIF_TX_WS          RT_GENMASK(18, 16)
#define AHUB_APBIF_TX_CHANS       RT_GENMASK(11, 8)
#define AHUB_APBIF_TX_START       RT_BIT(4)
#define AHUB_APBIF_TX_DRQ         RT_BIT(3)
#define AHUB_APBIF_TX_FIFO_FLUSH  RT_BIT(12)
#define AHUB_APBIF_TX_FIFO_16BIT  RT_BIT(0)
#define AHUB_I2S_CTL_CLK_OUT      RT_BIT(18)
#define AHUB_I2S_CTL_SDO          RT_GENMASK(11, 8)
#define AHUB_I2S_CTL_MODE         RT_GENMASK(5, 4)
#define AHUB_I2S_CTL_TXEN         RT_BIT(2)
#define AHUB_I2S_CTL_GEN          RT_BIT(0)
#define AHUB_I2S_FMT_LRCK_POL     RT_BIT(19)
#define AHUB_I2S_FMT_LRCK_PERIOD  RT_GENMASK(16, 8)
#define AHUB_I2S_FMT_SAMPLE_WIDTH RT_GENMASK(6, 4)
#define AHUB_I2S_FMT_SLOT_WIDTH   RT_GENMASK(2, 0)
#define AHUB_I2S_CHCFG_TX_CHANS   RT_GENMASK(3, 0)
#define AHUB_I2S_SLOT_CHANS       RT_GENMASK(19, 16)
#define AHUB_I2S_SLOT_ENABLE      RT_GENMASK(15, 0)

/* APBIF0 is wired by the H616 AHUB to the internal HDMI I2S1 endpoint. */
#define H616_AHUB_HDMI_APBIF      0
#define H616_AHUB_HDMI_I2S        1
#define H616_AHUB_RST_APBIF0      RT_BIT(31)
#define H616_AHUB_RST_I2S1        RT_BIT(22)

struct h616_ahub
{
    struct sunxi_audio_output output;
    void *base;
    struct rt_clk_array *clks;
    struct rt_clk *codec_clk;
    struct rt_clk *hub_clk;
    struct rt_reset_control *reset;
    struct rt_ofw_node *cpudai_np;
    rt_uint32_t apbif;
    rt_uint32_t i2s;
    rt_bool_t clks_enabled;
};

#define to_h616_ahub(raw) rt_container_of(raw, struct h616_ahub, output)

static rt_uint32_t h616_ahub_readl(struct h616_ahub *ahub, rt_uint32_t offset)
{
    return HWREG32(ahub->base + offset);
}

static void h616_ahub_writel(struct h616_ahub *ahub, rt_uint32_t value,
                             rt_uint32_t offset)
{
    HWREG32(ahub->base + offset) = value;
}

static void h616_ahub_update_bits(struct h616_ahub *ahub, rt_uint32_t offset,
                                  rt_uint32_t mask, rt_uint32_t value)
{
    rt_uint32_t reg = h616_ahub_readl(ahub, offset);

    h616_ahub_writel(ahub, (reg & ~mask) | (value & mask), offset);
}

static rt_err_t h616_ahub_configure(struct sunxi_audio_output *output,
                                    const struct rt_audio_configure *config)
{
    struct h616_ahub *ahub = to_h616_ahub(output);
    rt_uint32_t width;
    rt_uint32_t channels;
    rt_uint32_t slots;
    rt_uint32_t rate;

    if (!config->channels || config->channels > 8 ||
        (config->samplebits != 16 && config->samplebits != 24 &&
         config->samplebits != 32) ||
        config->samplerate < 8000 ||
        config->samplerate > 192000)
    {
        return -RT_EINVAL;
    }
    width = config->samplebits == 16 ? 3 : config->samplebits == 24 ? 5
                                                                    : 7;
    channels = config->channels - 1;
    rate = config->samplerate * 512;
    if (rt_clk_set_rate(ahub->codec_clk, rate) ||
        rt_clk_set_rate(ahub->hub_clk, rate))
    {
        return -RT_EIO;
    }
    if (sunxi_h616_hdmi_audio_configure(config->samplerate,
                                        config->channels, config->samplebits))
    {
        return -RT_EIO;
    }

    h616_ahub_update_bits(ahub, AHUB_APBIF_TX_CTL(ahub->apbif),
                          AHUB_APBIF_TX_WS | AHUB_APBIF_TX_CHANS, (width << 16) | (channels << 8));
    h616_ahub_update_bits(ahub, AHUB_APBIF_TXFIFO_CTL(ahub->apbif),
                          AHUB_APBIF_TX_FIFO_16BIT,
                          config->samplebits == 16 ? AHUB_APBIF_TX_FIFO_16BIT : 0);
    h616_ahub_update_bits(ahub, AHUB_I2S_FMT0(ahub->i2s),
                          AHUB_I2S_FMT_LRCK_POL | AHUB_I2S_FMT_LRCK_PERIOD |
                              AHUB_I2S_FMT_SAMPLE_WIDTH | AHUB_I2S_FMT_SLOT_WIDTH,
                          AHUB_I2S_FMT_LRCK_POL | (31 << 8) | (width << 4) | 7);
    h616_ahub_writel(ahub, 0x30, AHUB_I2S_FMT1(ahub->i2s));
    h616_ahub_update_bits(ahub, AHUB_I2S_CHCFG(ahub->i2s),
                          AHUB_I2S_CHCFG_TX_CHANS, channels);
    h616_ahub_writel(ahub, 0x10, AHUB_I2S_OUT_CH0MAP0(ahub->i2s));
    h616_ahub_writel(ahub, 0x23, AHUB_I2S_OUT_CH1MAP0(ahub->i2s));
    h616_ahub_writel(ahub, 0x54, AHUB_I2S_OUT_CH2MAP0(ahub->i2s));
    h616_ahub_writel(ahub, 0x76, AHUB_I2S_OUT_CH3MAP0(ahub->i2s));
    slots = (channels << 16) | ((RT_BIT(config->channels) - 1) & 0xffff);
    h616_ahub_update_bits(ahub, AHUB_I2S_OUT_SLOT0(ahub->i2s),
                          AHUB_I2S_SLOT_CHANS | AHUB_I2S_SLOT_ENABLE, slots);
    return RT_EOK;
}

static rt_err_t h616_ahub_init(struct sunxi_audio_output *output)
{
    struct h616_ahub *ahub = to_h616_ahub(output);

    h616_ahub_update_bits(ahub, AHUB_RST,
                          H616_AHUB_RST_APBIF0 | H616_AHUB_RST_I2S1,
                          H616_AHUB_RST_APBIF0 | H616_AHUB_RST_I2S1);
    h616_ahub_update_bits(ahub, AHUB_GAT,
                          H616_AHUB_RST_APBIF0 | H616_AHUB_RST_I2S1,
                          H616_AHUB_RST_APBIF0 | H616_AHUB_RST_I2S1);
    h616_ahub_update_bits(ahub, AHUB_I2S_CTL(ahub->i2s),
                          AHUB_I2S_CTL_CLK_OUT | AHUB_I2S_CTL_SDO | AHUB_I2S_CTL_MODE |
                              AHUB_I2S_CTL_GEN,
                          (1 << 4) | AHUB_I2S_CTL_GEN | AHUB_I2S_CTL_SDO);
    return RT_EOK;
}

static rt_err_t h616_ahub_start(struct sunxi_audio_output *output)
{
    struct h616_ahub *ahub = to_h616_ahub(output);

    h616_ahub_update_bits(ahub, AHUB_APBIF_TXFIFO_CTL(ahub->apbif),
                          AHUB_APBIF_TX_FIFO_FLUSH, AHUB_APBIF_TX_FIFO_FLUSH);
    h616_ahub_writel(ahub, RT_BIT(1) | RT_BIT(0), AHUB_APBIF_TX_IRQ_STA(ahub->apbif));
    h616_ahub_update_bits(ahub, AHUB_I2S_CTL(ahub->i2s), AHUB_I2S_CTL_TXEN,
                          AHUB_I2S_CTL_TXEN);
    h616_ahub_update_bits(ahub, AHUB_APBIF_TX_CTL(ahub->apbif),
                          AHUB_APBIF_TX_START, AHUB_APBIF_TX_START);
    sunxi_h616_hdmi_audio_enable(RT_TRUE);
    return RT_EOK;
}

static void h616_ahub_stop(struct sunxi_audio_output *output)
{
    struct h616_ahub *ahub = to_h616_ahub(output);

    sunxi_h616_hdmi_audio_enable(RT_FALSE);
    h616_ahub_update_bits(ahub, AHUB_APBIF_TX_IRQ_CTL(ahub->apbif),
                          AHUB_APBIF_TX_DRQ, 0);
    h616_ahub_update_bits(ahub, AHUB_APBIF_TX_CTL(ahub->apbif),
                          AHUB_APBIF_TX_START, 0);
    h616_ahub_update_bits(ahub, AHUB_I2S_CTL(ahub->i2s), AHUB_I2S_CTL_TXEN, 0);
}

static void h616_ahub_enable_dma(struct sunxi_audio_output *output,
                                 rt_bool_t enable)
{
    struct h616_ahub *ahub = to_h616_ahub(output);

    h616_ahub_update_bits(ahub, AHUB_APBIF_TX_IRQ_CTL(ahub->apbif),
                          AHUB_APBIF_TX_DRQ, enable ? AHUB_APBIF_TX_DRQ : 0);
}

static const struct sunxi_audio_output_ops h616_ahub_output_ops = {
    .init = h616_ahub_init,
    .configure = h616_ahub_configure,
    .start = h616_ahub_start,
    .stop = h616_ahub_stop,
    .enable_dma = h616_ahub_enable_dma,
};

static struct rt_ofw_node *h616_ahub_find_cpudai(rt_uint32_t id)
{
    struct rt_ofw_node *np;
    rt_uint32_t value;

    rt_ofw_foreach_node_by_compatible(np, "allwinner,sunxi-ahub-cpudai")
    {
        if (!rt_ofw_prop_read_u32(np, "id", &value) && value == id)
        {
            return np;
        }
    }
    return RT_NULL;
}

static void h616_ahub_release(struct h616_ahub *ahub)
{
    sunxi_audio_output_release(&ahub->output);
    if (ahub->cpudai_np)
    {
        rt_ofw_node_put(ahub->cpudai_np);
    }
    if (!rt_is_err_or_null(ahub->reset))
    {
        rt_reset_control_assert(ahub->reset);
        rt_reset_control_put(ahub->reset);
    }
    if (!rt_is_err_or_null(ahub->codec_clk))
    {
        rt_clk_put(ahub->codec_clk);
    }
    if (!rt_is_err_or_null(ahub->hub_clk))
    {
        rt_clk_put(ahub->hub_clk);
    }
    if (!rt_is_err_or_null(ahub->clks))
    {
        if (ahub->clks_enabled)
        {
            rt_clk_array_disable_unprepare(ahub->clks);
        }
        rt_clk_array_put(ahub->clks);
    }
    if (ahub->base)
    {
        rt_iounmap(ahub->base);
    }
    rt_free(ahub);
}

static rt_err_t h616_ahub_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct h616_ahub *ahub = rt_calloc(1, sizeof(*ahub));
    rt_uint32_t apbif = H616_AHUB_HDMI_APBIF;
    rt_uint32_t tdm = H616_AHUB_HDMI_I2S;
    rt_err_t err;

    if (!ahub)
    {
        return -RT_ENOMEM;
    }
    rt_ofw_prop_read_u32(dev->ofw_node, "tdm_num", &tdm);
    rt_ofw_prop_read_u32(dev->ofw_node, "allwinner,apbif-id", &apbif);
    LOG_D("AHUB: apbif=%u i2s=%u", apbif, tdm);

    if (tdm != H616_AHUB_HDMI_I2S || apbif != H616_AHUB_HDMI_APBIF)
    {
        LOG_E("unsupported AHUB route: apbif=%u i2s=%u", apbif, tdm);
        err = -RT_ENOSYS;
        goto fail;
    }
    ahub->output.dev = dev;
    ahub->apbif = apbif;
    ahub->i2s = tdm;
    ahub->base = rt_dm_dev_iomap(dev, 0);
    ahub->clks = rt_clk_get_array(dev);
    ahub->codec_clk = rt_clk_get_by_name(dev, "audio-codec-1x");
    ahub->hub_clk = rt_clk_get_by_name(dev, "audio-hub");
    ahub->reset = rt_reset_control_get_by_index(dev, 0);
    ahub->cpudai_np = h616_ahub_find_cpudai(apbif);

    if (!ahub->base)
    {
        err = -RT_EIO;
        LOG_E("AHUB: failed to map registers");
        goto fail;
    }
    if (rt_is_err_or_null(ahub->clks))
    {
        err = -RT_EIO;
        LOG_E("AHUB: invalid clock array");
        goto fail;
    }
    if (rt_is_err_or_null(ahub->codec_clk))
    {
        err = -RT_EIO;
        LOG_E("AHUB: missing audio-codec-1x clock");
        goto fail;
    }
    if (rt_is_err_or_null(ahub->hub_clk))
    {
        err = -RT_EIO;
        LOG_E("AHUB: missing audio-hub clock");
        goto fail;
    }
    if (rt_is_err_or_null(ahub->reset))
    {
        /*
         * Vendor H616 DTs put the shared AHUB reset on the sunxi-ahub
         * node, not on individual sunxi-ahub-daudio endpoints.  Firmware
         * has already released that reset before handing over to us.
         */
        LOG_W("AHUB: no endpoint reset; using shared AHUB state");
    }
    if (!ahub->cpudai_np)
    {
        err = -RT_EIO;
        LOG_E("AHUB: missing cpudai%u node", apbif);
        goto fail;
    }
    if ((err = rt_platform_ofw_request(ahub->cpudai_np)))
    {
        LOG_E("AHUB: request cpudai%u failed: %d", apbif, err);
        goto fail;
    }
    if (!ahub->cpudai_np->dev)
    {
        err = -RT_EIO;
        LOG_E("AHUB: cpudai%u did not bind a device", apbif);
        goto fail;
    }
    /* Codec 1x and AHUB use one PLL_AUDIO family at 48 kHz. */
    if ((err = rt_clk_set_rate(ahub->codec_clk, 49152000)))
    {
        LOG_E("AHUB: set audio-codec-1x rate failed: %d", err);
        goto fail;
    }
    if ((err = rt_clk_set_rate(ahub->hub_clk, 24576000)))
    {
        LOG_E("AHUB: set audio-hub rate failed: %d", err);
        goto fail;
    }
    if ((err = rt_clk_array_prepare_enable(ahub->clks)))
    {
        LOG_E("AHUB: enable clocks failed: %d", err);
        goto fail;
    }
    if (!rt_is_err_or_null(ahub->reset) &&
        (err = rt_reset_control_deassert(ahub->reset)))
    {
        LOG_E("AHUB: deassert reset failed: %d", err);
        goto fail;
    }
    ahub->clks_enabled = RT_TRUE;
    ahub->output.config.samplerate = 48000;
    ahub->output.config.channels = 2;
    ahub->output.config.samplebits = 16;
    ahub->output.ops = &h616_ahub_output_ops;
    ahub->output.playback_buffer = rt_dma_alloc_coherent(dev,
                                                         SUNXI_AUDIO_BUFFER_SIZE, &ahub->output.playback_dma);
    if (!ahub->output.playback_buffer)
    {
        err = -RT_ENOMEM;
        goto fail;
    }
    ahub->output.dma_tx = rt_dma_chan_request(ahub->cpudai_np->dev, "tx");
    if (rt_is_err(ahub->output.dma_tx))
    {
        err = rt_ptr_err(ahub->output.dma_tx);
        goto fail;
    }
    ahub->output.dma_tx->callback = sunxi_audio_output_dma_done;
    ahub->output.dma_tx->priv = &ahub->output;
    ahub->output.fifo_dma = (rt_ubase_t)rt_kmem_v2p(ahub->base) +
                            AHUB_APBIF_TXFIFO(ahub->apbif);
    if ((err = sunxi_audio_output_register(&ahub->output, "hdmi-sound", ahub)))
    {
        goto fail;
    }
    dev->user_data = ahub;
    return RT_EOK;

fail:
    h616_ahub_release(ahub);
    return err;
}

static rt_err_t h616_ahub_remove(struct rt_platform_device *pdev)
{
    struct h616_ahub *ahub = pdev->parent.user_data;

    if (!ahub)
    {
        return RT_EOK;
    }
    sunxi_audio_output_stop(&ahub->output);
    rt_device_unregister(&ahub->output.parent.parent);
    h616_ahub_release(ahub);
    return RT_EOK;
}

/*
 * AHUB cpudai nodes carry the DMA specifiers for APBIF endpoints.  They have
 * no separate register block, but need a platform device so the DMA core can
 * resolve their dmas property when an AHUB endpoint requests a channel.
 */
static rt_err_t h616_ahub_cpudai_probe(struct rt_platform_device *pdev)
{
    rt_uint32_t id;

    if (rt_ofw_prop_read_u32(pdev->parent.ofw_node, "id", &id) || id > 2)
    {
        return -RT_EINVAL;
    }

    LOG_D("AHUB: cpudai%u DMA endpoint ready", id);

    return RT_EOK;
}

static const struct rt_ofw_node_id h616_ahub_cpudai_ofw_ids[] = {
    { .compatible = "allwinner,sunxi-ahub-cpudai" },
    {}
};

static struct rt_platform_driver h616_ahub_cpudai_driver = {
    .name = "sun50i-h616-ahub-cpudai",
    .ids = h616_ahub_cpudai_ofw_ids,
    .probe = h616_ahub_cpudai_probe,
};

static const struct rt_ofw_node_id h616_ahub_ofw_ids[] = {
    { .compatible = "allwinner,sunxi-ahub-daudio" },
    {}
};

static struct rt_platform_driver h616_ahub_driver = {
    .name = "sun50i-h616-ahub",
    .ids = h616_ahub_ofw_ids,
    .probe = h616_ahub_probe,
    .remove = h616_ahub_remove,
};
RT_PLATFORM_DRIVER_EXPORT(h616_ahub_cpudai_driver);
RT_PLATFORM_DRIVER_EXPORT(h616_ahub_driver);
