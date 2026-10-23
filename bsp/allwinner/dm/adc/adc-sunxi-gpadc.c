/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "adc.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SUNXI_GPADC_SR                 0x00
#define SUNXI_GPADC_CTRL               0x04
#define SUNXI_GPADC_CS_EN              0x08
#define SUNXI_GPADC_DATA_BASE          0x80

#define SUNXI_GPADC_DATA_MASK          RT_GENMASK(11, 0)
#define SUNXI_GPADC_VCM_BUF_EN         RT_BIT(0)
#define SUNXI_GPADC_CALIBRATE_EN       RT_BIT(17)
#define SUNXI_GPADC_EN                 RT_BIT(16)
#define SUNXI_GPADC_MODE_MASK          RT_GENMASK(19, 18)
#define SUNXI_GPADC_MODE_CONTINUOUS    (2U << 18)

#define SUNXI_GPADC_OSC_RATE           24000000U
#define SUNXI_GPADC_MIN_RATE           400U
#define SUNXI_GPADC_MAX_RATE           1000000U
#define SUNXI_GPADC_DEFAULT_RATE       1000000U
#define SUNXI_GPADC_MAX_CHANNELS       12U
#define SUNXI_GPADC_RESOLUTION         12U
#define SUNXI_GPADC_VREF_MV            1800U

struct sunxi_gpadc
{
    struct rt_adc_device parent;

    void *regs;
    struct rt_clk *clk;
    struct rt_reset_control *reset;
    rt_uint32_t channels;
    rt_uint32_t enabled_channels;
    struct rt_mutex lock;
    rt_bool_t clk_enabled;
    rt_bool_t lock_initialized;
};

#define to_sunxi_gpadc(raw) rt_container_of(raw, struct sunxi_gpadc, parent)

static rt_err_t sunxi_gpadc_set_rate(struct sunxi_gpadc *gpadc,
        rt_uint32_t sample_rate)
{
    rt_uint32_t div;
    rt_uint32_t tacq;

    if (sample_rate < SUNXI_GPADC_MIN_RATE ||
            sample_rate > SUNXI_GPADC_MAX_RATE)
    {
        return -RT_EINVAL;
    }

    /* One conversion needs TACQ + 1 + 13 conversion + 3 wait cycles. */
    div = SUNXI_GPADC_OSC_RATE / sample_rate - 3;
    tacq = div - 13 - 1;
    if (div > 0xffff || tacq > 0xffff)
    {
        return -RT_EINVAL;
    }

    HWREG32(gpadc->regs + SUNXI_GPADC_SR) = (div << 16) | tacq;

    return RT_EOK;
}

static void sunxi_gpadc_set_channels(struct sunxi_gpadc *gpadc,
        rt_uint32_t channels)
{
    HWREG32(gpadc->regs + SUNXI_GPADC_CS_EN) = channels;
}

static rt_bool_t sunxi_gpadc_valid_channel(struct sunxi_gpadc *gpadc,
        rt_int8_t channel)
{
    return channel >= 0 && (rt_uint32_t)channel < gpadc->channels;
}

static rt_err_t sunxi_gpadc_enabled(struct rt_adc_device *adc,
        rt_int8_t channel, rt_bool_t enabled)
{
    rt_uint32_t mask;
    struct sunxi_gpadc *gpadc = to_sunxi_gpadc(adc);

    if (!sunxi_gpadc_valid_channel(gpadc, channel))
    {
        return -RT_EINVAL;
    }

    mask = RT_BIT(channel);
    rt_mutex_take(&gpadc->lock, RT_WAITING_FOREVER);

    if (enabled)
    {
        gpadc->enabled_channels |= mask;
    }
    else
    {
        gpadc->enabled_channels &= ~mask;
    }
    sunxi_gpadc_set_channels(gpadc, gpadc->enabled_channels);

    rt_mutex_release(&gpadc->lock);

    return RT_EOK;
}

static rt_err_t sunxi_gpadc_convert(struct rt_adc_device *adc,
        rt_int8_t channel, rt_uint32_t *value)
{
    rt_uint32_t mask;
    rt_bool_t temporarily_enabled = RT_FALSE;
    struct sunxi_gpadc *gpadc = to_sunxi_gpadc(adc);

    if (!value || !sunxi_gpadc_valid_channel(gpadc, channel))
    {
        return -RT_EINVAL;
    }

    mask = RT_BIT(channel);
    rt_mutex_take(&gpadc->lock, RT_WAITING_FOREVER);

    if (!(gpadc->enabled_channels & mask))
    {
        sunxi_gpadc_set_channels(gpadc, gpadc->enabled_channels | mask);
        temporarily_enabled = RT_TRUE;
        rt_hw_us_delay(2);
    }

    *value = HWREG32(gpadc->regs + SUNXI_GPADC_DATA_BASE +
            (rt_uint32_t)channel * sizeof(rt_uint32_t)) & SUNXI_GPADC_DATA_MASK;

    if (temporarily_enabled)
    {
        sunxi_gpadc_set_channels(gpadc, gpadc->enabled_channels);
    }

    rt_mutex_release(&gpadc->lock);

    return RT_EOK;
}

static rt_uint8_t sunxi_gpadc_get_resolution(struct rt_adc_device *adc)
{
    return SUNXI_GPADC_RESOLUTION;
}

static rt_int16_t sunxi_gpadc_get_vref(struct rt_adc_device *adc)
{
    return SUNXI_GPADC_VREF_MV;
}

static const struct rt_adc_ops sunxi_gpadc_ops =
{
    .enabled = sunxi_gpadc_enabled,
    .convert = sunxi_gpadc_convert,
    .get_resolution = sunxi_gpadc_get_resolution,
    .get_vref = sunxi_gpadc_get_vref,
};

static void sunxi_gpadc_release(struct sunxi_gpadc *gpadc)
{
    if (gpadc->regs)
    {
        HWREG32(gpadc->regs + SUNXI_GPADC_CS_EN) = 0;
        HWREG32(gpadc->regs + SUNXI_GPADC_CTRL) &= ~SUNXI_GPADC_EN;
    }
    if (!rt_is_err_or_null(gpadc->reset))
    {
        rt_reset_control_assert(gpadc->reset);
        rt_reset_control_put(gpadc->reset);
    }
    if (gpadc->clk_enabled)
    {
        rt_clk_disable_unprepare(gpadc->clk);
    }
    if (!rt_is_err_or_null(gpadc->clk))
    {
        rt_clk_put(gpadc->clk);
    }
    if (gpadc->lock_initialized)
    {
        rt_mutex_detach(&gpadc->lock);
    }
    if (gpadc->regs)
    {
        rt_iounmap(gpadc->regs);
    }
    rt_free(gpadc);
}

static rt_err_t sunxi_gpadc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t channels = SUNXI_GPADC_MAX_CHANNELS;
    rt_uint32_t sample_rate = SUNXI_GPADC_DEFAULT_RATE;
    rt_uint32_t ctrl;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_gpadc *gpadc = rt_calloc(1, sizeof(*gpadc));

    if (!gpadc)
    {
        return -RT_ENOMEM;
    }

    gpadc->regs = rt_dm_dev_iomap(dev, 0);
    if (!gpadc->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    gpadc->clk = rt_clk_get_by_name(dev, "bus");
    gpadc->reset = rt_reset_control_get_by_name(dev, "bus");
    if (rt_is_err(gpadc->clk) || rt_is_err(gpadc->reset))
    {
        err = rt_is_err(gpadc->clk) ? rt_ptr_err(gpadc->clk) :
                rt_ptr_err(gpadc->reset);
        goto _fail;
    }

    if ((err = rt_reset_control_deassert(gpadc->reset)) ||
            (err = rt_clk_prepare_enable(gpadc->clk)))
    {
        goto _fail;
    }
    gpadc->clk_enabled = RT_TRUE;

    rt_ofw_prop_read_u32(dev->ofw_node, "allwinner,channel-count", &channels);
    if (!channels || channels > SUNXI_GPADC_MAX_CHANNELS)
    {
        err = -RT_EINVAL;
        goto _fail;
    }
    gpadc->channels = channels;

    rt_ofw_prop_read_u32(dev->ofw_node, "allwinner,sample-rate", &sample_rate);
    if ((err = sunxi_gpadc_set_rate(gpadc, sample_rate)))
    {
        goto _fail;
    }

    ctrl = HWREG32(gpadc->regs + SUNXI_GPADC_CTRL);
    ctrl |= SUNXI_GPADC_VCM_BUF_EN | SUNXI_GPADC_CALIBRATE_EN |
            SUNXI_GPADC_EN;
    ctrl &= ~SUNXI_GPADC_MODE_MASK;
    ctrl |= SUNXI_GPADC_MODE_CONTINUOUS;
    HWREG32(gpadc->regs + SUNXI_GPADC_CTRL) = ctrl;
    sunxi_gpadc_set_channels(gpadc, 0);

    if ((err = rt_dm_dev_set_name_auto(&gpadc->parent.parent, "adc")) < 0)
    {
        goto _fail;
    }
    dev_name = rt_dm_dev_get_name(&gpadc->parent.parent);
    rt_mutex_init(&gpadc->lock, dev_name, RT_IPC_FLAG_PRIO);
    gpadc->lock_initialized = RT_TRUE;

    if ((err = rt_hw_adc_register(&gpadc->parent, dev_name,
                    &sunxi_gpadc_ops, gpadc)))
    {
        goto _fail;
    }

    dev->user_data = gpadc;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, gpadc);

    return RT_EOK;

_fail:
    sunxi_gpadc_release(gpadc);

    return err;
}

static rt_err_t sunxi_gpadc_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct sunxi_gpadc *gpadc = dev->user_data;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);
    rt_device_unregister(&gpadc->parent.parent);
    sunxi_gpadc_release(gpadc);

    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_gpadc_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-gpadc" },
    { .compatible = "allwinner,sun50i-h616-gpadc" },
    { .compatible = "allwinner,sun20i-d1-gpadc" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_gpadc_driver =
{
    .name = "sunxi-gpadc",
    .ids = sunxi_gpadc_ofw_ids,
    .probe = sunxi_gpadc_probe,
    .remove = sunxi_gpadc_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_gpadc_driver);
