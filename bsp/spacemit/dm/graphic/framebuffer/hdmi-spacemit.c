/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "display-spacemit.h"

#define DBG_TAG "hdmi.spacemit"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SPACEMIT_HDMI_MCLK_RATE         491520000UL
#define SPACEMIT_HDMI_PHY_STATUS        0x000c
#define SPACEMIT_HDMI_PHY_HPD           RT_BIT(12)
#define SPACEMIT_HDMI_PHY_CTRL          0x0028
#define SPACEMIT_HDMI_COLOR_DEPTH       0x0034
#define SPACEMIT_HDMI_PHY_ANALOG        0x00e0
#define SPACEMIT_HDMI_PLL_CTRL          0x00e4
#define SPACEMIT_HDMI_PLL_FRAC          0x00e8
#define SPACEMIT_HDMI_PLL_DIV           0x00ec
#define SPACEMIT_HDMI_PLL_POST          0x00f0

#define SPACEMIT_HDMI_EIGHT_BPP         0U

struct spacemit_hdmi
{
    struct rt_device *dev;
    void *regs;
    struct rt_clk *mclk;
    struct rt_reset_control *rstc;
    struct spacemit_display_connector connector;
    rt_bool_t prepared;
    rt_bool_t enabled;
};

static const struct spacemit_display_timing spacemit_hdmi_1080p60 =
{
    .hactive = 1920,
    .vactive = 1080,
    .hfront_porch = 88,
    .hback_porch = 148,
    .hsync_len = 44,
    .vfront_porch = 4,
    .vback_porch = 36,
    .vsync_len = 5,
    .refresh = 60,
    .pixelclock = 148500000ULL,
    .flags = SPACEMIT_DISPLAY_F_PHSYNC | SPACEMIT_DISPLAY_F_PVSYNC,
};

rt_inline rt_uint32_t spacemit_hdmi_readl(struct spacemit_hdmi *hdmi,
        rt_uint32_t offset)
{
    return HWREG32((rt_uint8_t *)hdmi->regs + offset);
}

rt_inline void spacemit_hdmi_writel(struct spacemit_hdmi *hdmi,
        rt_uint32_t offset, rt_uint32_t value)
{
    HWREG32((rt_uint8_t *)hdmi->regs + offset) = value;
}

static void spacemit_hdmi_update_bits(struct spacemit_hdmi *hdmi,
        rt_uint32_t offset, rt_uint32_t mask, rt_uint32_t value)
{
    rt_uint32_t reg = spacemit_hdmi_readl(hdmi, offset);

    reg &= ~mask;
    reg |= value & mask;
    spacemit_hdmi_writel(hdmi, offset, reg);
}

static int spacemit_hdmi_pll8(rt_uint32_t bit_clock_khz)
{
    bit_clock_khz /= 100U;

    if (bit_clock_khz < 425U)
    {
        return 3;
    }
    if (bit_clock_khz < 850U)
    {
        return 2;
    }
    if (bit_clock_khz < 1700U)
    {
        return 1;
    }

    return 0;
}

static int spacemit_hdmi_pll6(rt_uint32_t bit_clock_khz)
{
    bit_clock_khz /= 100U;

    if (bit_clock_khz <= 337U)
    {
        return 0;
    }
    if (bit_clock_khz < 425U)
    {
        return 1;
    }
    if (bit_clock_khz < 675U)
    {
        return 0;
    }
    if (bit_clock_khz < 850U)
    {
        return 1;
    }
    if (bit_clock_khz < 1350U)
    {
        return 0;
    }
    if (bit_clock_khz < 1700U)
    {
        return 1;
    }

    return 0;
}

static int spacemit_hdmi_pll5(rt_uint32_t bit_clock_khz)
{
    rt_uint32_t value = bit_clock_khz *
            (1U << spacemit_hdmi_pll8(bit_clock_khz)) / 100U;

    if (value < 1830U)
    {
        return 0;
    }
    if (value < 2030U)
    {
        return 1;
    }
    if (value < 2275U)
    {
        return 2;
    }
    if (value < 2520U)
    {
        return 3;
    }
    if (value < 2765U)
    {
        return 4;
    }
    if (value < 3015U)
    {
        return 5;
    }
    if (value < 3260U)
    {
        return 6;
    }

    return 7;
}

static void spacemit_hdmi_pll_fraction(rt_uint32_t bit_clock_khz,
        int *integer_part, rt_uint32_t *frac_reg)
{
    const rt_int64_t scale = 1000000000LL;
    const int pll8 = spacemit_hdmi_pll8(bit_clock_khz);
    const int pll6 = spacemit_hdmi_pll6(bit_clock_khz);
    const rt_int64_t numerator =
            (rt_int64_t)(1U << pll8) * bit_clock_khz;
    const rt_int64_t denominator = 100LL * (pll6 + 1) * 24LL;
    rt_int64_t value = numerator * scale / denominator;
    rt_int64_t integer = numerator / denominator * scale;
    rt_int64_t fraction = value - integer;
    rt_int64_t bit = 0;
    rt_uint32_t frac20 = 0;
    rt_bool_t negative = fraction > scale / 2;
    int frac_hi;

    fraction = negative ? scale - fraction : fraction;
    *integer_part = (int)(integer / scale) + (negative ? 1 : 0);

    for (int i = 0; i < 20; ++i)
    {
        if (bit >= scale)
        {
            frac20 |= 1U << (19 - i);
            fraction -= scale;
        }
        fraction *= 2;
        bit = fraction;
    }

    if (negative)
    {
        frac20 = (~frac20 + 1U) & 0xfffffU;
        frac_hi = 0x10 | ((frac20 >> 16) & 0xf) | RT_BIT(5);
    }
    else
    {
        frac_hi = ((frac20 >> 16) & 0xf) | RT_BIT(5);
    }

    *frac_reg = (0x20U << 24) | ((rt_uint32_t)frac_hi << 16) |
            (frac20 & 0xffffU);
}

static void spacemit_hdmi_pll_program(struct spacemit_hdmi *hdmi,
        rt_uint32_t pixel_clock_khz)
{
    int integer_part;
    rt_uint32_t frac_reg;
    rt_uint32_t div_reg, post_reg;
    int pll8 = spacemit_hdmi_pll8(pixel_clock_khz);
    int pll6 = spacemit_hdmi_pll6(pixel_clock_khz);
    int pll5 = spacemit_hdmi_pll5(pixel_clock_khz);

    spacemit_hdmi_pll_fraction(pixel_clock_khz, &integer_part, &frac_reg);

    div_reg = (0x50U << 24) |
            ((0x0dU | ((rt_uint32_t)pll6 << 4) | (2U << 6)) << 16) |
            ((0x40U | (rt_uint32_t)pll5) << 8) |
            ((rt_uint32_t)integer_part & 0xffU);
    post_reg = (8U << 8) | ((rt_uint32_t)pll8 << 5) | 1U;

    spacemit_hdmi_writel(hdmi, SPACEMIT_HDMI_PLL_FRAC, frac_reg);
    spacemit_hdmi_writel(hdmi, SPACEMIT_HDMI_PLL_DIV, div_reg);
    spacemit_hdmi_writel(hdmi, SPACEMIT_HDMI_PLL_POST, post_reg);
}

static rt_err_t spacemit_hdmi_detect(
        struct spacemit_display_connector *connector, rt_bool_t *connected)
{
    struct spacemit_hdmi *hdmi;

    if (!connector || !connected)
    {
        return -RT_EINVAL;
    }

    hdmi = connector->priv;
    *connected = !!(spacemit_hdmi_readl(hdmi,
            SPACEMIT_HDMI_PHY_STATUS) & SPACEMIT_HDMI_PHY_HPD);

    return RT_EOK;
}

static rt_err_t spacemit_hdmi_get_timing(
        struct spacemit_display_connector *connector,
        struct spacemit_display_timing *timing)
{
    if (!connector || !timing)
    {
        return -RT_EINVAL;
    }

    *timing = spacemit_hdmi_1080p60;
    return RT_EOK;
}

static rt_err_t spacemit_hdmi_prepare(struct spacemit_hdmi *hdmi)
{
    rt_err_t err;

    if (hdmi->prepared)
    {
        return RT_EOK;
    }

    if ((err = rt_clk_prepare_enable(hdmi->mclk)))
    {
        return err;
    }
    if ((err = rt_clk_set_rate(hdmi->mclk, SPACEMIT_HDMI_MCLK_RATE)))
    {
        rt_clk_disable_unprepare(hdmi->mclk);
        return err;
    }
    if ((err = rt_reset_control_deassert(hdmi->rstc)))
    {
        rt_clk_disable_unprepare(hdmi->mclk);
        return err;
    }

    rt_hw_us_delay(10);
    hdmi->prepared = RT_TRUE;
    return RT_EOK;
}

static rt_err_t spacemit_hdmi_enable(
        struct spacemit_display_connector *connector,
        const struct spacemit_display_timing *timing)
{
    rt_err_t err;
    rt_bool_t connected;
    rt_uint32_t pixel_clock_khz;
    struct spacemit_hdmi *hdmi;

    if (!connector || !timing || !timing->pixelclock)
    {
        return -RT_EINVAL;
    }

    hdmi = connector->priv;
    if (hdmi->enabled)
    {
        return RT_EOK;
    }
    if ((err = spacemit_hdmi_prepare(hdmi)))
    {
        return err;
    }

    pixel_clock_khz = (rt_uint32_t)(timing->pixelclock / 1000ULL);

    spacemit_hdmi_writel(hdmi, SPACEMIT_HDMI_PHY_ANALOG, 0xae5c410fU);
    spacemit_hdmi_update_bits(hdmi, SPACEMIT_HDMI_PHY_ANALOG,
            0x3U << 29, 0x1U << 29);
    spacemit_hdmi_update_bits(hdmi, SPACEMIT_HDMI_PHY_ANALOG,
            0xfU << 18, 0x7U << 18);
    spacemit_hdmi_update_bits(hdmi, SPACEMIT_HDMI_PHY_ANALOG,
            0x3U << 14, 0);

    spacemit_hdmi_writel(hdmi, SPACEMIT_HDMI_COLOR_DEPTH,
            0x0000000dU | (4U << 4));
    spacemit_hdmi_pll_program(hdmi, pixel_clock_khz);
    spacemit_hdmi_writel(hdmi, SPACEMIT_HDMI_PLL_CTRL, 0);
    spacemit_hdmi_writel(hdmi, SPACEMIT_HDMI_PLL_CTRL, 3);
    rt_hw_us_delay(100);
    spacemit_hdmi_writel(hdmi, SPACEMIT_HDMI_PHY_CTRL,
            0x1c208000U | SPACEMIT_HDMI_EIGHT_BPP);
    rt_hw_dsb();

    hdmi->enabled = RT_TRUE;
    spacemit_hdmi_detect(connector, &connected);
    LOG_D("%ux%u@%u, pclk=%u kHz, mclk=%lu Hz, HPD=%d, pll=0x%08x",
            timing->hactive, timing->vactive, timing->refresh,
            pixel_clock_khz, rt_clk_get_rate(hdmi->mclk), connected,
            spacemit_hdmi_readl(hdmi, SPACEMIT_HDMI_PLL_CTRL));

    return RT_EOK;
}

static rt_err_t spacemit_hdmi_disable(
        struct spacemit_display_connector *connector)
{
    struct spacemit_hdmi *hdmi;

    if (!connector)
    {
        return -RT_EINVAL;
    }

    hdmi = connector->priv;
    if (hdmi->enabled)
    {
        spacemit_hdmi_writel(hdmi, SPACEMIT_HDMI_PLL_CTRL, 0);
        rt_hw_us_delay(100);
        hdmi->enabled = RT_FALSE;
    }

    if (hdmi->prepared)
    {
        rt_clk_disable_unprepare(hdmi->mclk);
        hdmi->prepared = RT_FALSE;
    }

    return RT_EOK;
}

static const struct spacemit_display_connector_ops spacemit_hdmi_ops =
{
    .detect = spacemit_hdmi_detect,
    .get_timing = spacemit_hdmi_get_timing,
    .enable = spacemit_hdmi_enable,
    .disable = spacemit_hdmi_disable,
};

static rt_err_t spacemit_hdmi_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_hdmi *hdmi = rt_calloc(1, sizeof(*hdmi));

    if (!hdmi)
    {
        return -RT_ENOMEM;
    }

    hdmi->dev = dev;
    hdmi->regs = rt_dm_dev_iomap(dev, 0);
    if (!hdmi->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    hdmi->mclk = rt_clk_get_by_name(dev, "hmclk");
    if (rt_is_err(hdmi->mclk))
    {
        err = rt_ptr_err(hdmi->mclk);
        hdmi->mclk = RT_NULL;
        goto _fail_unmap;
    }

    hdmi->rstc = rt_reset_control_get_by_name(dev, "hdmi_reset");
    if (rt_is_err(hdmi->rstc))
    {
        err = rt_ptr_err(hdmi->rstc);
        hdmi->rstc = RT_NULL;
        goto _fail_clk;
    }

    if ((err = spacemit_display_connector_register(&hdmi->connector,
            dev->ofw_node, &spacemit_hdmi_ops, hdmi)))
    {
        goto _fail_reset;
    }

    pdev->parent.user_data = hdmi;
    LOG_D("connector ready: %s", rt_ofw_node_full_name(dev->ofw_node));

    return RT_EOK;

_fail_reset:
    rt_reset_control_put(hdmi->rstc);
_fail_clk:
    rt_clk_put(hdmi->mclk);
_fail_unmap:
    rt_iounmap(hdmi->regs);
_fail:
    rt_free(hdmi);
    return err;
}

static rt_err_t spacemit_hdmi_remove(struct rt_platform_device *pdev)
{
    struct spacemit_hdmi *hdmi = pdev->parent.user_data;

    if (!hdmi)
    {
        return RT_EOK;
    }

    spacemit_hdmi_disable(&hdmi->connector);
    spacemit_display_connector_unregister(&hdmi->connector);
    rt_reset_control_assert(hdmi->rstc);
    rt_reset_control_put(hdmi->rstc);
    rt_clk_put(hdmi->mclk);
    rt_iounmap(hdmi->regs);
    rt_free(hdmi);
    pdev->parent.user_data = RT_NULL;

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_hdmi_ids[] =
{
    { .compatible = "spacemit,hdmi" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_hdmi_driver =
{
    .name = "hdmi-spacemit",
    .ids = spacemit_hdmi_ids,
    .probe = spacemit_hdmi_probe,
    .remove = spacemit_hdmi_remove,
};

rt_err_t spacemit_hdmi_driver_register(void)
{
    return rt_platform_driver_register(&spacemit_hdmi_driver);
}
