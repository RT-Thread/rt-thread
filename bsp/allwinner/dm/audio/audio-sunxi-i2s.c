/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "audio.sunxi.i2s"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "audio-sunxi.h"

#define SUNXI_I2S_CTL                     0x000
#define SUNXI_I2S_FMT0                    0x004
#define SUNXI_I2S_FMT1                    0x008
#define SUNXI_I2S_INTSTA                  0x00c
#define SUNXI_I2S_FIFOCTL                 0x014
#define SUNXI_I2S_INTCTL                  0x01c
#define SUNXI_I2S_TXFIFO                  0x020
#define SUNXI_I2S_CLKDIV                  0x024
#define SUNXI_I2S_TXCNT                   0x028
#define SUNXI_I2S_CHCFG                   0x030
#define SUNXI_I2S_TX0CHSEL                0x034
#define SUNXI_I2S_TX0CHMAP0               0x044
#define SUNXI_I2S_TX0CHMAP1               0x048

#define SUNXI_I2S_CTL_BCLK_OUT            RT_BIT(18)
#define SUNXI_I2S_CTL_LRCK_OUT            RT_BIT(17)
#define SUNXI_I2S_CTL_MODE_I2S            RT_BIT(4)
#define SUNXI_I2S_CTL_TX_EN               RT_BIT(2)
#define SUNXI_I2S_CTL_GLOBAL_EN           RT_BIT(0)
#define SUNXI_I2S_CTL_SDO0_EN             RT_BIT(8)

#define SUNXI_I2S_FMT0_LRCK_PER_MASK      RT_GENMASK(17, 8)
#define SUNXI_I2S_FMT0_SAMPLE_RES_MASK    RT_GENMASK(6, 4)
#define SUNXI_I2S_FMT0_SLOT_WIDTH_MASK    RT_GENMASK(2, 0)
#define SUNXI_I2S_FIFOCTL_FTX             RT_BIT(25)
#define SUNXI_I2S_FIFOCTL_TXIM            RT_BIT(2)
#define SUNXI_I2S_INTCTL_TXDRQ_EN         RT_BIT(7)
#define SUNXI_I2S_CLKDIV_MCLKOUT_EN       RT_BIT(8)
#define SUNXI_I2S_CLKDIV_BCLK_DIV_MASK    RT_GENMASK(7, 4)
#define SUNXI_I2S_CLKDIV_MCLK_DIV_MASK    RT_GENMASK(3, 0)
#define SUNXI_I2S_CHCFG_TX_SLOT_MASK      RT_GENMASK(3, 0)
#define SUNXI_I2S_TX0CHSEL_OFFSET_MASK    RT_GENMASK(21, 20)
#define SUNXI_I2S_TX0CHSEL_CHSEL_MASK     RT_GENMASK(19, 16)
#define SUNXI_I2S_TX0CHSEL_CHEN_MASK      RT_GENMASK(15, 0)

struct sunxi_i2s_rate
{
    rt_uint32_t rate;
    rt_uint8_t bclk_div;
    rt_uint8_t mclk_div;
};

struct sunxi_i2s
{
    struct sunxi_audio_output output;
    void *base;
    struct rt_clk_array *clks;
    struct rt_reset_control *reset;
    rt_bool_t clks_enabled;
};

#define to_sunxi_i2s(raw) \
    rt_container_of(raw, struct sunxi_i2s, output)

static const struct sunxi_i2s_rate sunxi_i2s_rates[] =
{
    { 8000,  10, 6 },
    { 12000, 9,  5 },
    { 16000, 8,  4 },
    { 24000, 7,  3 },
    { 32000, 6,  2 },
    { 48000, 5,  2 },
    { 96000, 3,  1 },
    { 192000, 2, 0 },
};

static rt_uint32_t sunxi_i2s_readl(struct sunxi_i2s *i2s,
        rt_uint32_t offset)
{
    return HWREG32(i2s->base + offset);
}

static void sunxi_i2s_writel(struct sunxi_i2s *i2s, rt_uint32_t value,
        rt_uint32_t offset)
{
    HWREG32(i2s->base + offset) = value;
}

static void sunxi_i2s_update_bits(struct sunxi_i2s *i2s,
        rt_uint32_t offset, rt_uint32_t mask, rt_uint32_t value)
{
    rt_uint32_t reg = sunxi_i2s_readl(i2s, offset);

    reg &= ~mask;
    reg |= value & mask;
    sunxi_i2s_writel(i2s, reg, offset);
}

static const struct sunxi_i2s_rate *sunxi_i2s_find_rate(rt_uint32_t rate)
{
    rt_size_t index;

    for (index = 0; index < RT_ARRAY_SIZE(sunxi_i2s_rates); ++index)
    {
        if (sunxi_i2s_rates[index].rate == rate)
        {
            return &sunxi_i2s_rates[index];
        }
    }

    return RT_NULL;
}

static rt_err_t sunxi_i2s_configure(struct sunxi_audio_output *output,
        const struct rt_audio_configure *config)
{
    rt_uint32_t sample_resolution;
    rt_uint32_t fmt0;
    rt_uint32_t clkdiv;
    const struct sunxi_i2s_rate *rate;
    struct sunxi_i2s *i2s = to_sunxi_i2s(output);

    if (!config->channels || config->channels > 2)
    {
        return -RT_EINVAL;
    }

    switch (config->samplebits)
    {
    case 16:
        sample_resolution = 3;
        break;
    case 24:
        sample_resolution = 5;
        break;
    case 32:
        sample_resolution = 7;
        break;
    default:
        return -RT_EINVAL;
    }

    rate = sunxi_i2s_find_rate(config->samplerate);
    if (!rate)
    {
        return -RT_ENOSYS;
    }

    fmt0 = (63 << 8) | (sample_resolution << 4) | 7;
    sunxi_i2s_writel(i2s, fmt0, SUNXI_I2S_FMT0);
    sunxi_i2s_writel(i2s, 0, SUNXI_I2S_FMT1);
    sunxi_i2s_writel(i2s, config->channels - 1, SUNXI_I2S_CHCFG);
    sunxi_i2s_writel(i2s, (1 << 20) | (1 << 16) | 0x3,
            SUNXI_I2S_TX0CHSEL);
    sunxi_i2s_writel(i2s, 0xfedcba98, SUNXI_I2S_TX0CHMAP0);
    sunxi_i2s_writel(i2s, 0x76543210, SUNXI_I2S_TX0CHMAP1);

    clkdiv = rate->bclk_div << 4;
    if (rate->mclk_div)
    {
        clkdiv |= SUNXI_I2S_CLKDIV_MCLKOUT_EN | rate->mclk_div;
    }
    sunxi_i2s_writel(i2s, clkdiv, SUNXI_I2S_CLKDIV);
    sunxi_i2s_update_bits(i2s, SUNXI_I2S_FIFOCTL,
            SUNXI_I2S_FIFOCTL_TXIM, config->samplebits == 16 ?
            SUNXI_I2S_FIFOCTL_TXIM : 0);

    return RT_EOK;
}

static rt_err_t sunxi_i2s_init(struct sunxi_audio_output *output)
{
    struct sunxi_i2s *i2s = to_sunxi_i2s(output);

    sunxi_i2s_writel(i2s, 0, SUNXI_I2S_CTL);
    sunxi_i2s_writel(i2s, 0, SUNXI_I2S_INTCTL);

    return RT_EOK;
}

static rt_err_t sunxi_i2s_start(struct sunxi_audio_output *output)
{
    struct sunxi_i2s *i2s = to_sunxi_i2s(output);

    sunxi_i2s_update_bits(i2s, SUNXI_I2S_FIFOCTL,
            SUNXI_I2S_FIFOCTL_FTX, SUNXI_I2S_FIFOCTL_FTX);
    sunxi_i2s_writel(i2s, 0, SUNXI_I2S_TXCNT);
    sunxi_i2s_writel(i2s, RT_BIT(6) | RT_BIT(5) | RT_BIT(4),
            SUNXI_I2S_INTSTA);
    sunxi_i2s_update_bits(i2s, SUNXI_I2S_CTL,
            SUNXI_I2S_CTL_GLOBAL_EN | SUNXI_I2S_CTL_TX_EN |
            SUNXI_I2S_CTL_SDO0_EN | SUNXI_I2S_CTL_BCLK_OUT |
            SUNXI_I2S_CTL_LRCK_OUT | SUNXI_I2S_CTL_MODE_I2S,
            SUNXI_I2S_CTL_GLOBAL_EN | SUNXI_I2S_CTL_TX_EN |
            SUNXI_I2S_CTL_SDO0_EN | SUNXI_I2S_CTL_BCLK_OUT |
            SUNXI_I2S_CTL_LRCK_OUT | SUNXI_I2S_CTL_MODE_I2S);

    return RT_EOK;
}

static void sunxi_i2s_stop(struct sunxi_audio_output *output)
{
    struct sunxi_i2s *i2s = to_sunxi_i2s(output);

    sunxi_i2s_update_bits(i2s, SUNXI_I2S_INTCTL,
            SUNXI_I2S_INTCTL_TXDRQ_EN, 0);
    sunxi_i2s_update_bits(i2s, SUNXI_I2S_CTL,
            SUNXI_I2S_CTL_TX_EN | SUNXI_I2S_CTL_SDO0_EN |
            SUNXI_I2S_CTL_GLOBAL_EN, 0);
}

static void sunxi_i2s_enable_dma(struct sunxi_audio_output *output,
        rt_bool_t enable)
{
    struct sunxi_i2s *i2s = to_sunxi_i2s(output);

    sunxi_i2s_update_bits(i2s, SUNXI_I2S_INTCTL,
            SUNXI_I2S_INTCTL_TXDRQ_EN,
            enable ? SUNXI_I2S_INTCTL_TXDRQ_EN : 0);
}

static const struct sunxi_audio_output_ops sunxi_i2s_output_ops =
{
    .init = sunxi_i2s_init,
    .configure = sunxi_i2s_configure,
    .start = sunxi_i2s_start,
    .stop = sunxi_i2s_stop,
    .enable_dma = sunxi_i2s_enable_dma,
};

static void sunxi_i2s_release(struct sunxi_i2s *i2s)
{
    sunxi_audio_output_release(&i2s->output);
    if (!rt_is_err_or_null(i2s->reset))
    {
        rt_reset_control_assert(i2s->reset);
        rt_reset_control_put(i2s->reset);
    }
    if (!rt_is_err_or_null(i2s->clks))
    {
        if (i2s->clks_enabled)
        {
            rt_clk_array_disable_unprepare(i2s->clks);
        }
        rt_clk_array_put(i2s->clks);
    }
    if (i2s->base)
    {
        rt_iounmap(i2s->base);
    }
    rt_free(i2s);
}

static rt_err_t sunxi_i2s_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_i2s *i2s = rt_calloc(1, sizeof(*i2s));

    if (!i2s)
    {
        return -RT_ENOMEM;
    }

    i2s->output.dev = dev;
    i2s->base = rt_dm_dev_iomap(dev, 0);
    if (!i2s->base)
    {
        err = -RT_EIO;
        goto _fail;
    }
    i2s->clks = rt_clk_get_array(dev);
    i2s->reset = rt_reset_control_get_by_name(dev, "bus");
    if (rt_is_err(i2s->clks) || rt_is_err(i2s->reset))
    {
        err = rt_is_err(i2s->clks) ? rt_ptr_err(i2s->clks) :
                rt_ptr_err(i2s->reset);
        goto _fail;
    }
    err = rt_clk_array_prepare_enable(i2s->clks);
    if (err)
    {
        goto _fail;
    }
    i2s->clks_enabled = RT_TRUE;
    err = rt_reset_control_deassert(i2s->reset);
    if (err)
    {
        goto _fail;
    }

    i2s->output.config.samplerate = 48000;
    i2s->output.config.channels = 2;
    i2s->output.config.samplebits = 16;
    i2s->output.ops = &sunxi_i2s_output_ops;
    i2s->output.playback_buffer = rt_dma_alloc_coherent(dev,
            SUNXI_AUDIO_BUFFER_SIZE, &i2s->output.playback_dma);
    if (!i2s->output.playback_buffer)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }
    i2s->output.dma_tx = rt_dma_chan_request(dev, "tx");
    if (rt_is_err(i2s->output.dma_tx))
    {
        err = rt_ptr_err(i2s->output.dma_tx);
        goto _fail;
    }
    i2s->output.dma_tx->callback = sunxi_audio_output_dma_done;
    i2s->output.dma_tx->priv = &i2s->output;
    i2s->output.fifo_dma = (rt_ubase_t)rt_kmem_v2p(i2s->base) +
            SUNXI_I2S_TXFIFO;

    err = sunxi_audio_output_register(&i2s->output, "sound", i2s);
    if (err)
    {
        goto _fail;
    }
    dev->user_data = i2s;
    return RT_EOK;

_fail:
    sunxi_i2s_release(i2s);
    return err;
}

static rt_err_t sunxi_i2s_remove(struct rt_platform_device *pdev)
{
    struct sunxi_i2s *i2s = pdev->parent.user_data;

    sunxi_audio_output_stop(&i2s->output);
    rt_device_unregister(&i2s->output.parent.parent);
    sunxi_i2s_release(i2s);

    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_i2s_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-i2s" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_i2s_driver =
{
    .name = "sunxi-i2s",
    .ids = sunxi_i2s_ofw_ids,
    .probe = sunxi_i2s_probe,
    .remove = sunxi_i2s_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_i2s_driver);
