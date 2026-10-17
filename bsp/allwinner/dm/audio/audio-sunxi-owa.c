/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "audio.sunxi.owa"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "audio-sunxi.h"

#define SUNXI_OWA_CTL                       0x000
#define SUNXI_OWA_TXCFG                     0x004
#define SUNXI_OWA_INT_STA                   0x00c
#define SUNXI_OWA_FIFO_CTL                  0x014
#define SUNXI_OWA_INT                       0x01c
#define SUNXI_OWA_TXFIFO                    0x020
#define SUNXI_OWA_TXCNT                     0x024
#define SUNXI_OWA_TXCH_STA0                 0x02c
#define SUNXI_OWA_TXCH_STA1                 0x030

#define SUNXI_OWA_CTL_RESET                 RT_BIT(0)
#define SUNXI_OWA_CTL_GEN_EN                RT_BIT(1)
#define SUNXI_OWA_TXCFG_TX_EN               RT_BIT(0)
#define SUNXI_OWA_TXCFG_CHAN_STA            RT_BIT(1)
#define SUNXI_OWA_TXCFG_BITS_MASK           RT_GENMASK(3, 2)
#define SUNXI_OWA_TXCFG_CLKDIV_MASK         RT_GENMASK(8, 4)
#define SUNXI_OWA_TXCFG_SINGLE              RT_BIT(31)
#define SUNXI_OWA_FIFO_CTL_TXIM             RT_BIT(2)
#define SUNXI_OWA_FIFO_CTL_FTX              RT_BIT(30)
#define SUNXI_OWA_INT_TXDRQ_EN              RT_BIT(7)
#define SUNXI_OWA_TXCH_STA0_SAMFREQ_MASK    RT_GENMASK(27, 24)
#define SUNXI_OWA_TXCH_STA0_CHNUM_MASK      RT_GENMASK(23, 20)
#define SUNXI_OWA_TXCH_STA1_WORDLEN_MASK    RT_GENMASK(3, 0)
#define SUNXI_OWA_TXCH_STA1_ORIGFREQ_MASK   RT_GENMASK(7, 4)

struct sunxi_owa_rate
{
    rt_uint32_t rate;
    rt_uint8_t divider;
    rt_uint8_t sample_frequency;
    rt_uint8_t original_frequency;
};

struct sunxi_owa
{
    struct sunxi_audio_output output;
    void *base;
    struct rt_clk_array *clks;
    struct rt_reset_control *reset;
    rt_bool_t clks_enabled;
};

#define to_sunxi_owa(raw) \
    rt_container_of(raw, struct sunxi_owa, output)

static const struct sunxi_owa_rate sunxi_owa_rates[] =
{
    { 8000,  23, 0, 0 },
    { 12000, 15, 0, 0 },
    { 16000, 11, 0, 0 },
    { 24000, 7,  6, 9 },
    { 32000, 5,  3, 12 },
    { 48000, 3,  2, 13 },
    { 96000, 1,  10, 5 },
    { 192000, 0, 14, 1 },
};

static rt_uint32_t sunxi_owa_readl(struct sunxi_owa *owa,
        rt_uint32_t offset)
{
    return HWREG32(owa->base + offset);
}

static void sunxi_owa_writel(struct sunxi_owa *owa, rt_uint32_t value,
        rt_uint32_t offset)
{
    HWREG32(owa->base + offset) = value;
}

static void sunxi_owa_update_bits(struct sunxi_owa *owa,
        rt_uint32_t offset, rt_uint32_t mask, rt_uint32_t value)
{
    rt_uint32_t reg = sunxi_owa_readl(owa, offset);

    reg &= ~mask;
    reg |= value & mask;
    sunxi_owa_writel(owa, reg, offset);
}

static const struct sunxi_owa_rate *sunxi_owa_find_rate(rt_uint32_t rate)
{
    rt_size_t index;

    for (index = 0; index < RT_ARRAY_SIZE(sunxi_owa_rates); ++index)
    {
        if (sunxi_owa_rates[index].rate == rate)
        {
            return &sunxi_owa_rates[index];
        }
    }

    return RT_NULL;
}

static rt_err_t sunxi_owa_configure(struct sunxi_audio_output *output,
        const struct rt_audio_configure *config)
{
    rt_uint32_t sample_bits;
    rt_uint32_t word_length;
    const struct sunxi_owa_rate *rate;
    struct sunxi_owa *owa = to_sunxi_owa(output);

    if (!config->channels || config->channels > 2)
    {
        return -RT_EINVAL;
    }

    switch (config->samplebits)
    {
    case 16:
        sample_bits = 0;
        word_length = 2;
        break;
    case 24:
    case 32:
        sample_bits = 2;
        word_length = 11;
        break;
    default:
        return -RT_EINVAL;
    }

    rate = sunxi_owa_find_rate(config->samplerate);
    if (!rate)
    {
        return -RT_ENOSYS;
    }

    sunxi_owa_update_bits(owa, SUNXI_OWA_TXCFG,
            SUNXI_OWA_TXCFG_BITS_MASK | SUNXI_OWA_TXCFG_CLKDIV_MASK |
            SUNXI_OWA_TXCFG_SINGLE,
            (sample_bits << 2) | (rate->divider << 4) |
            (config->channels == 1 ? SUNXI_OWA_TXCFG_SINGLE : 0));
    sunxi_owa_update_bits(owa, SUNXI_OWA_FIFO_CTL,
            SUNXI_OWA_FIFO_CTL_TXIM,
            config->samplebits == 16 ? SUNXI_OWA_FIFO_CTL_TXIM : 0);
    sunxi_owa_update_bits(owa, SUNXI_OWA_TXCH_STA0,
            SUNXI_OWA_TXCH_STA0_SAMFREQ_MASK |
            SUNXI_OWA_TXCH_STA0_CHNUM_MASK,
            (rate->sample_frequency << 24) | (2 << 20));
    sunxi_owa_update_bits(owa, SUNXI_OWA_TXCH_STA1,
            SUNXI_OWA_TXCH_STA1_WORDLEN_MASK |
            SUNXI_OWA_TXCH_STA1_ORIGFREQ_MASK,
            word_length | (rate->original_frequency << 4));

    return RT_EOK;
}

static rt_err_t sunxi_owa_init(struct sunxi_audio_output *output)
{
    struct sunxi_owa *owa = to_sunxi_owa(output);

    sunxi_owa_writel(owa, 0, SUNXI_OWA_INT);
    sunxi_owa_update_bits(owa, SUNXI_OWA_FIFO_CTL, RT_GENMASK(19, 12),
            0x40 << 12);
    sunxi_owa_update_bits(owa, SUNXI_OWA_TXCFG,
            SUNXI_OWA_TXCFG_CHAN_STA, SUNXI_OWA_TXCFG_CHAN_STA);

    return RT_EOK;
}

static rt_err_t sunxi_owa_start(struct sunxi_audio_output *output)
{
    struct sunxi_owa *owa = to_sunxi_owa(output);

    sunxi_owa_update_bits(owa, SUNXI_OWA_CTL,
            SUNXI_OWA_CTL_GEN_EN, 0);
    sunxi_owa_update_bits(owa, SUNXI_OWA_FIFO_CTL,
            SUNXI_OWA_FIFO_CTL_FTX, SUNXI_OWA_FIFO_CTL_FTX);
    sunxi_owa_writel(owa, 0, SUNXI_OWA_TXCNT);
    sunxi_owa_writel(owa, RT_BIT(6) | RT_BIT(5) | RT_BIT(4),
            SUNXI_OWA_INT_STA);
    sunxi_owa_update_bits(owa, SUNXI_OWA_CTL,
            SUNXI_OWA_CTL_RESET | SUNXI_OWA_CTL_GEN_EN,
            SUNXI_OWA_CTL_RESET | SUNXI_OWA_CTL_GEN_EN);
    sunxi_owa_update_bits(owa, SUNXI_OWA_TXCFG,
            SUNXI_OWA_TXCFG_TX_EN, SUNXI_OWA_TXCFG_TX_EN);

    return RT_EOK;
}

static void sunxi_owa_stop(struct sunxi_audio_output *output)
{
    struct sunxi_owa *owa = to_sunxi_owa(output);

    sunxi_owa_update_bits(owa, SUNXI_OWA_INT,
            SUNXI_OWA_INT_TXDRQ_EN, 0);
    sunxi_owa_update_bits(owa, SUNXI_OWA_TXCFG,
            SUNXI_OWA_TXCFG_TX_EN, 0);
    sunxi_owa_update_bits(owa, SUNXI_OWA_CTL,
            SUNXI_OWA_CTL_GEN_EN, 0);
}

static void sunxi_owa_enable_dma(struct sunxi_audio_output *output,
        rt_bool_t enable)
{
    struct sunxi_owa *owa = to_sunxi_owa(output);

    sunxi_owa_update_bits(owa, SUNXI_OWA_INT,
            SUNXI_OWA_INT_TXDRQ_EN,
            enable ? SUNXI_OWA_INT_TXDRQ_EN : 0);
}

static const struct sunxi_audio_output_ops sunxi_owa_output_ops =
{
    .init = sunxi_owa_init,
    .configure = sunxi_owa_configure,
    .start = sunxi_owa_start,
    .stop = sunxi_owa_stop,
    .enable_dma = sunxi_owa_enable_dma,
};

static void sunxi_owa_release(struct sunxi_owa *owa)
{
    sunxi_audio_output_release(&owa->output);
    if (!rt_is_err_or_null(owa->reset))
    {
        rt_reset_control_assert(owa->reset);
        rt_reset_control_put(owa->reset);
    }
    if (!rt_is_err_or_null(owa->clks))
    {
        if (owa->clks_enabled)
        {
            rt_clk_array_disable_unprepare(owa->clks);
        }
        rt_clk_array_put(owa->clks);
    }
    if (owa->base)
    {
        rt_iounmap(owa->base);
    }
    rt_free(owa);
}

static rt_err_t sunxi_owa_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_owa *owa = rt_calloc(1, sizeof(*owa));

    if (!owa)
    {
        return -RT_ENOMEM;
    }

    owa->output.dev = dev;
    owa->base = rt_dm_dev_iomap(dev, 0);
    if (!owa->base)
    {
        err = -RT_EIO;
        goto _fail;
    }
    owa->clks = rt_clk_get_array(dev);
    owa->reset = rt_reset_control_get_by_name(dev, "bus");
    if (rt_is_err(owa->clks) || rt_is_err(owa->reset))
    {
        err = rt_is_err(owa->clks) ? rt_ptr_err(owa->clks) :
                rt_ptr_err(owa->reset);
        goto _fail;
    }
    err = rt_clk_array_prepare_enable(owa->clks);
    if (err)
    {
        goto _fail;
    }
    owa->clks_enabled = RT_TRUE;
    err = rt_reset_control_deassert(owa->reset);
    if (err)
    {
        goto _fail;
    }

    owa->output.config.samplerate = 48000;
    owa->output.config.channels = 2;
    owa->output.config.samplebits = 16;
    owa->output.ops = &sunxi_owa_output_ops;
    owa->output.playback_buffer = rt_dma_alloc_coherent(dev,
            SUNXI_AUDIO_BUFFER_SIZE, &owa->output.playback_dma);
    if (!owa->output.playback_buffer)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }
    owa->output.dma_tx = rt_dma_chan_request(dev, "tx");
    if (rt_is_err(owa->output.dma_tx))
    {
        err = rt_ptr_err(owa->output.dma_tx);
        goto _fail;
    }
    owa->output.dma_tx->callback = sunxi_audio_output_dma_done;
    owa->output.dma_tx->priv = &owa->output;
    owa->output.fifo_dma = (rt_ubase_t)rt_kmem_v2p(owa->base) +
            SUNXI_OWA_TXFIFO;

    err = sunxi_audio_output_register(&owa->output, "sound", owa);
    if (err)
    {
        goto _fail;
    }
    dev->user_data = owa;
    return RT_EOK;

_fail:
    sunxi_owa_release(owa);
    return err;
}

static rt_err_t sunxi_owa_remove(struct rt_platform_device *pdev)
{
    struct sunxi_owa *owa = pdev->parent.user_data;

    sunxi_audio_output_stop(&owa->output);
    rt_device_unregister(&owa->output.parent.parent);
    sunxi_owa_release(owa);

    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_owa_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-owa" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_owa_driver =
{
    .name = "sunxi-owa",
    .ids = sunxi_owa_ofw_ids,
    .probe = sunxi_owa_probe,
    .remove = sunxi_owa_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_owa_driver);
