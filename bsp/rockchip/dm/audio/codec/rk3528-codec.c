/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-3-15      GuEe-GUI     the first version
 */

#include <rthw.h>

#define DBG_TAG "audio.rk3528"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rk3528-codec.h"

#define DAC_RESET           0x00
#define DAC_FORMAT          0x04
#define DAC_I2S             0x08
#define DAC_DIG_GAIN        0x18
#define DAC_BIAS            0x80
#define DAC_VREF_CURRENT    0x84
#define DAC_LEFT            0xa0
#define DAC_RIGHT           0xb0
#define LINEOUT_LEFT        0xa4
#define LINEOUT_RIGHT       0xb4
#define LINEOUT_GAIN_LEFT   0xac
#define LINEOUT_GAIN_RIGHT  0xbc

#define DAC_SYS_RESET_N     RT_BIT(0)
#define DAC_RESET_N         RT_BIT(4)
#define DAC_I2S_RESET_N     RT_BIT(0)
#define DAC_I2S_MASTER      (RT_BIT(5) | RT_BIT(4))
#define DAC_I2S_FORMAT_MASK (3U << 2)
#define DAC_I2S_FORMAT      (2U << 2)
#define DAC_WORD_MASK       (3U << 4)
#define DAC_VREF            RT_BIT(0)
#define DAC_IBIAS           RT_BIT(1)
#define DAC_ENABLE          RT_BIT(0)
#define DAC_CLK             RT_BIT(1)
#define DAC_BUFFER          RT_BIT(2)
#define DAC_CHANNEL_VREF    RT_BIT(3)
#define DAC_WORK            RT_BIT(4)
#define DAC_POP_MASK        (3U << 5)
#define DAC_POP_ON          RT_BIT(5)
#define LINEOUT_ENABLE      RT_BIT(0)
#define LINEOUT_WORK        RT_BIT(4)
#define LINEOUT_UNMUTE      RT_BIT(5)
#define LINEOUT_GAIN_0DB    0x1a

struct rk3528_codec
{
    rt_list_t list;
    struct rt_ofw_node *np;
    void *regs;
    struct rt_clk *pclk;
    struct rt_clk *mclk;
    struct rt_reset_control *reset;
    rt_base_t pa_pin;
    rt_uint8_t pa_active;
    rt_uint32_t pa_delay_ms;
    rt_uint32_t volume;
    rt_bool_t configured;
    rt_bool_t started;
    rt_bool_t muted;
};

static rt_list_t codec_list = RT_LIST_OBJECT_INIT(codec_list);
static RT_DEFINE_SPINLOCK(codec_lock);

static void codec_update(struct rk3528_codec *codec, rt_uint32_t reg,
        rt_uint32_t mask, rt_uint32_t value)
{
    HWREG32(codec->regs + reg) = (HWREG32(codec->regs + reg) & ~mask) | (value & mask);
}

static void codec_pair(struct rk3528_codec *codec, rt_uint32_t left,
        rt_uint32_t mask, rt_uint32_t value)
{
    codec_update(codec, left, mask, value);
    codec_update(codec, left + 0x10, mask, value);
}

static void codec_pa(struct rk3528_codec *codec, rt_bool_t on)
{
    if (codec->pa_pin >= 0)
    {
        rt_pin_write(codec->pa_pin, on ? codec->pa_active : !codec->pa_active);
        if (on && codec->pa_delay_ms)
        {
            rt_thread_mdelay(codec->pa_delay_ms);
        }
    }
}

static void codec_apply_mute(struct rk3528_codec *codec)
{
    rt_bool_t audible = codec->started && !codec->muted && codec->volume;

    if (!audible)
    {
        codec_pa(codec, RT_FALSE);
    }
    codec_pair(codec, LINEOUT_LEFT, LINEOUT_UNMUTE, audible ? LINEOUT_UNMUTE : 0);
    if (audible)
    {
        codec_pa(codec, RT_TRUE);
    }
}

struct rk3528_codec *rk3528_codec_find(struct rt_ofw_node *np)
{
    struct rk3528_codec *codec;
    struct rk3528_codec *found;

    found = RT_NULL;

    rt_spin_lock(&codec_lock);
    rt_list_for_each_entry(codec, &codec_list, list)
    {
        if (codec->np == np)
        {
            found = codec;
            break;
        }
    }
    rt_spin_unlock(&codec_lock);
    return found;
}

rt_err_t rk3528_codec_hw_params(struct rk3528_codec *codec,
        rt_uint32_t rate, rt_uint16_t bits, rt_uint32_t mclk_fs)
{
    rt_err_t err;
    rt_uint32_t mclk;
    rt_uint64_t actual;
    rt_uint64_t delta;

    if (bits != 16 || (rate != 44100 && rate != 48000) || mclk_fs != 256)
    {
        return -RT_EINVAL;
    }
    if (codec->started)
    {
        return -RT_EBUSY;
    }
    codec->configured = RT_FALSE;
    mclk = rate * mclk_fs;
    if ((err = rt_clk_set_rate(codec->mclk, mclk)))
    {
        return err;
    }
    actual = rt_clk_get_rate(codec->mclk);
    delta = actual > mclk ? actual - mclk : mclk - actual;
    if (delta > mclk / 100000)
    {
        return -RT_EINVAL;
    }
    codec_update(codec, DAC_FORMAT, DAC_WORD_MASK | DAC_I2S_FORMAT_MASK,
            DAC_I2S_FORMAT);
    codec_update(codec, DAC_I2S, DAC_I2S_MASTER | DAC_I2S_RESET_N,
            DAC_I2S_RESET_N);
    codec->configured = RT_TRUE;
    return RT_EOK;
}

rt_err_t rk3528_codec_set_volume(struct rk3528_codec *codec, rt_uint32_t volume)
{
    if (volume > AUDIO_VOLUME_MAX)
    {
        return -RT_EINVAL;
    }
    codec->volume = volume;
    codec_pair(codec, LINEOUT_GAIN_LEFT, 0x1f,
            volume * LINEOUT_GAIN_0DB / AUDIO_VOLUME_MAX);
    codec_apply_mute(codec);
    return RT_EOK;
}

rt_err_t rk3528_codec_mute(struct rk3528_codec *codec, rt_bool_t mute)
{
    codec->muted = mute;
    codec_apply_mute(codec);
    return RT_EOK;
}

rt_err_t rk3528_codec_start(struct rk3528_codec *codec)
{
    if (!codec->configured)
    {
        return -RT_EINVAL;
    }
    if (codec->started)
    {
        return RT_EOK;
    }

    /* Enable both channels in the vendor analog power-up order, still muted. */
    codec_update(codec, DAC_BIAS, DAC_IBIAS, DAC_IBIAS);
    codec_pair(codec, DAC_LEFT, DAC_BUFFER, DAC_BUFFER);
    codec_pair(codec, DAC_LEFT, DAC_POP_MASK, DAC_POP_ON);
    codec_pair(codec, LINEOUT_LEFT, LINEOUT_ENABLE, LINEOUT_ENABLE);
    codec_pair(codec, LINEOUT_LEFT, LINEOUT_WORK, LINEOUT_WORK);
    codec_pair(codec, DAC_LEFT, DAC_CHANNEL_VREF, DAC_CHANNEL_VREF);
    codec_pair(codec, DAC_LEFT, DAC_CLK, DAC_CLK);
    codec_pair(codec, DAC_LEFT, DAC_ENABLE, DAC_ENABLE);
    codec_pair(codec, DAC_LEFT, DAC_WORK, DAC_WORK);
    codec->started = RT_TRUE;
    codec_apply_mute(codec);
    return RT_EOK;
}

rt_err_t rk3528_codec_stop(struct rk3528_codec *codec)
{
    codec->started = RT_FALSE;
    codec_apply_mute(codec);
    codec_pair(codec, LINEOUT_LEFT, LINEOUT_WORK, 0);
    codec_pair(codec, LINEOUT_LEFT, LINEOUT_ENABLE, 0);
    codec_pair(codec, DAC_LEFT, DAC_ENABLE, 0);
    codec_pair(codec, DAC_LEFT, DAC_CLK, 0);
    codec_pair(codec, DAC_LEFT, DAC_CHANNEL_VREF, 0);
    codec_pair(codec, DAC_LEFT, DAC_POP_MASK, 0);
    codec_pair(codec, DAC_LEFT, DAC_BUFFER, 0);
    codec_update(codec, DAC_BIAS, DAC_IBIAS, 0);
    codec_pair(codec, DAC_LEFT, DAC_WORK, 0);
    return RT_EOK;
}

static rt_err_t rk3528_codec_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rk3528_codec *codec;

    codec = rt_calloc(1, sizeof(*codec));

    if (!codec)
    {
        return -RT_ENOMEM;
    }
    codec->np = dev->ofw_node;
    codec->pa_pin = PIN_NONE;
    if (rt_dm_dev_prop_read_bool(dev, "pa-ctl-gpios"))
    {
        codec->pa_pin = rt_pin_get_named_pin(dev, "pa-ctl", 0, RT_NULL,
                &codec->pa_active);
        if (codec->pa_pin < 0)
        {
            err = codec->pa_pin;
            goto _free;
        }
        rt_pin_mode(codec->pa_pin, PIN_MODE_OUTPUT);
        codec_pa(codec, RT_FALSE);
    }
    rt_dm_dev_prop_read_u32(dev, "pa-ctl-delay-ms", &codec->pa_delay_ms);
    if (codec->pa_delay_ms > 1000)
    {
        err = -RT_EINVAL;
        goto _free;
    }
    codec->regs = rt_dm_dev_iomap(dev, 0);
    if (!codec->regs)
    {
        err = -RT_EIO;
        goto _free;
    }
    codec->pclk = rt_clk_get_by_name(dev, "pclk");
    codec->mclk = rt_clk_get_by_name(dev, "mclk");
    codec->reset = rt_reset_control_get_by_name(dev, "acodec");
    if (rt_is_err(codec->pclk) || rt_is_err(codec->mclk) ||
            rt_is_err(codec->reset))
    {
        err = -RT_EIO;
        LOG_E("Missing codec clock or reset");
        goto _put;
    }
    if ((err = rt_clk_prepare_enable(codec->pclk)))
    {
        goto _put;
    }
    if ((err = rt_clk_prepare_enable(codec->mclk)))
    {
        goto _disable_pclk;
    }
    if ((err = rt_reset_control_assert(codec->reset)))
    {
        goto _disable_mclk;
    }
    rt_thread_mdelay(10);
    if ((err = rt_reset_control_deassert(codec->reset)))
    {
        goto _disable_mclk;
    }
    codec_update(codec, DAC_RESET, DAC_RESET_N | DAC_SYS_RESET_N, 0);
    codec_update(codec, DAC_I2S, DAC_I2S_RESET_N, 0);
    rt_thread_mdelay(10);
    codec_update(codec, DAC_RESET, DAC_RESET_N | DAC_SYS_RESET_N,
            DAC_RESET_N | DAC_SYS_RESET_N);
    codec_update(codec, DAC_I2S, DAC_I2S_RESET_N, DAC_I2S_RESET_N);

    codec_pair(codec, DAC_LEFT, DAC_POP_MASK, DAC_POP_ON);
    codec_update(codec, DAC_VREF_CURRENT, 0xff, 0xff);
    codec_update(codec, DAC_BIAS, DAC_VREF, DAC_VREF);
    rt_thread_mdelay(20);
    codec_update(codec, DAC_VREF_CURRENT, 0xff, 2);
    rk3528_codec_stop(codec);
    codec_update(codec, DAC_DIG_GAIN, 0xff, 0xe1);
    rk3528_codec_set_volume(codec, AUDIO_VOLUME_MAX);

    rt_spin_lock(&codec_lock);
    rt_list_insert_before(&codec_list, &codec->list);
    rt_spin_unlock(&codec_lock);
    dev->user_data = codec;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, codec);
    LOG_D("%s: internal DAC ready", codec->np->name);
    return RT_EOK;

_disable_mclk:
    rt_clk_disable_unprepare(codec->mclk);

_disable_pclk:
    rt_clk_disable_unprepare(codec->pclk);

_put:
    if (!rt_is_err_or_null(codec->reset))
    {
        rt_reset_control_put(codec->reset);
    }
    if (!rt_is_err_or_null(codec->mclk))
    {
        rt_clk_put(codec->mclk);
    }
    if (!rt_is_err_or_null(codec->pclk))
    {
        rt_clk_put(codec->pclk);
    }
    rt_iounmap(codec->regs);

_free:
    rt_free(codec);

    return err;
}

static rt_err_t rk3528_codec_remove(struct rt_platform_device *pdev)
{
    struct rk3528_codec *codec = pdev->parent.user_data;

    rk3528_codec_stop(codec);
    codec_update(codec, DAC_VREF_CURRENT, 0xff, 0xff);
    codec_update(codec, DAC_BIAS, DAC_VREF, 0);
    rt_thread_mdelay(20);

    rt_dm_dev_unbind_fwdata(&pdev->parent, RT_NULL);

    rt_spin_lock(&codec_lock);
    rt_list_remove(&codec->list);
    rt_spin_unlock(&codec_lock);

    rt_reset_control_assert(codec->reset);
    rt_reset_control_put(codec->reset);

    rt_clk_disable_unprepare(codec->mclk);
    rt_clk_disable_unprepare(codec->pclk);
    rt_clk_put(codec->mclk);
    rt_clk_put(codec->pclk);

    rt_iounmap(codec->regs);
    rt_free(codec);

    return RT_EOK;
}

static const struct rt_ofw_node_id rk3528_codec_ids[] =
{
    { .compatible = "rockchip,rk3528-codec" },
    { /* sentinel */ }
};

static struct rt_platform_driver rk3528_codec_driver =
{
    .name = "rk3528-codec",
    .ids = rk3528_codec_ids,
    .probe = rk3528_codec_probe,
    .remove = rk3528_codec_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rk3528_codec_driver);
