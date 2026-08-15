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

#define DBG_TAG "codec.rk817"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rk8xx.h"
#include "rk817-codec.h"

struct rk817_reg_val
{
    rt_uint8_t reg;
    rt_uint8_t value;
};

struct rk817_codec
{
    struct rk8xx *rk8xx;
    struct rt_clk *mclk;
    struct rt_ofw_node *np;

    rt_uint8_t hp_volume;
    rt_uint8_t spk_volume;
    rt_uint32_t rate;
    rt_bool_t powered;

    rt_list_t list;
};

static rt_list_t codec_list = RT_LIST_OBJECT_INIT(codec_list);
static RT_DEFINE_SPINLOCK(codec_list_lock);

static const struct rk817_reg_val playback_power_up_list[] =
{
    { RK817_CODEC_AREF_RTCFG1, 0x40 },
    { RK817_CODEC_DDAC_POPD_DACST, 0x02 },
    { RK817_CODEC_APLL_CFG1, 0x58 },
    { RK817_CODEC_APLL_CFG2, 0x2d },
    { RK817_CODEC_APLL_CFG5, 0x00 },
    { RK817_CODEC_DI2S_RXCMD_TSD, 0x00 },
    { RK817_CODEC_DI2S_RSD, 0x00 },
    { RK817_CODEC_DI2S_RXCR1, 0x00 },
    { RK817_CODEC_DI2S_RXCMD_TSD, 0x20 },
    { RK817_CODEC_DTOP_VUCTIME, 0xf4 },
    { RK817_CODEC_DDAC_MUTE_MIXCTL, 0x00 },
    { RK817_CODEC_DDAC_VOLL, RK817_DEFAULT_SPK_VOL },
    { RK817_CODEC_DDAC_VOLR, RK817_DEFAULT_SPK_VOL },
};

static const struct rk817_reg_val playback_power_down_list[] =
{
    { RK817_CODEC_DDAC_MUTE_MIXCTL, 0x01 },
    { RK817_CODEC_ADAC_CFG1, 0x0f },
    { RK817_CODEC_AHP_CFG0, 0xe0 },
    { RK817_CODEC_AHP_CP, 0x09 },
    { RK817_CODEC_ACLASSD_CFG1, 0x69 },
};

rt_inline rt_err_t rk817_write(struct rk817_codec *codec, rt_uint16_t reg, rt_uint8_t val)
{
    return rk8xx_write(codec->rk8xx, reg, val);
}

rt_inline rt_err_t rk817_update_bits(struct rk817_codec *codec,
        rt_uint16_t reg, rt_uint8_t mask, rt_uint8_t val)
{
    return rk8xx_update_bits(codec->rk8xx, reg, mask, val);
}

static void rk817_restart_dac_digital_clk(struct rk817_codec *codec)
{
    rk817_update_bits(codec, RK817_CODEC_ADAC_CFG1, PWD_DACBIAS_MASK, PWD_DACBIAS_DOWN);
    rt_hw_us_delay(500);
    rk817_update_bits(codec, RK817_CODEC_DTOP_DIGEN_CLKE, DAC_DIG_CLK_MASK, DAC_DIG_CLK_DIS);
    rt_hw_us_delay(500);
    rk817_update_bits(codec, RK817_CODEC_DTOP_DIGEN_CLKE, DAC_DIG_CLK_MASK, DAC_DIG_CLK_EN);
    rt_hw_us_delay(500);
    rk817_update_bits(codec, RK817_CODEC_ADAC_CFG1, PWD_DACBIAS_MASK, PWD_DACBIAS_ON);
}

static rt_err_t rk817_codec_power_up(struct rk817_codec *codec)
{
    rt_size_t i;

    rk817_update_bits(codec, RK817_CODEC_DTOP_DIGEN_CLKE, DAC_DIG_CLK_MASK, DAC_DIG_CLK_EN);

    for (i = 0; i < RT_ARRAY_SIZE(playback_power_up_list); ++i)
    {
        rk817_write(codec, playback_power_up_list[i].reg, playback_power_up_list[i].value);
    }

    rk817_write(codec, RK817_CODEC_APLL_CFG0, 0x04);
    rk817_write(codec, RK817_CODEC_APLL_CFG4, 0xa5);
    rk817_restart_dac_digital_clk(codec);

    return RT_EOK;
}

static rt_err_t rk817_codec_power_down(struct rk817_codec *codec)
{
    rt_size_t i;

    rk817_update_bits(codec, RK817_CODEC_DDAC_MUTE_MIXCTL, DACMT_ENABLE, DACMT_ENABLE);

    for (i = 0; i < RT_ARRAY_SIZE(playback_power_down_list); ++i)
    {
        rk817_write(codec, playback_power_down_list[i].reg, playback_power_down_list[i].value);
    }

    rk817_update_bits(codec, RK817_CODEC_DTOP_DIGEN_CLKE, DAC_DIG_CLK_MASK, DAC_DIG_CLK_DIS);
    rk817_write(codec, RK817_CODEC_APLL_CFG5, 0x01);
    rk817_write(codec, RK817_CODEC_AREF_RTCFG1, 0x06);
    codec->rate = 0;

    return RT_EOK;
}

static rt_err_t rk817_set_hp_path(struct rk817_codec *codec)
{
    rk817_write(codec, RK817_CODEC_AHP_CP, 0x11);
    rk817_write(codec, RK817_CODEC_AHP_CFG0, 0x80);
    rk817_write(codec, RK817_CODEC_ADAC_CFG1,
            PWD_DACBIAS_ON | PWD_DACD_DOWN | PWD_DACL_ON | PWD_DACR_ON);
    rk817_update_bits(codec, RK817_CODEC_DDAC_MUTE_MIXCTL, DACMT_ENABLE, DACMT_DISABLE);
    rk817_write(codec, RK817_CODEC_DDAC_VOLL, codec->hp_volume);
    rk817_write(codec, RK817_CODEC_DDAC_VOLR, codec->hp_volume);

    return RT_EOK;
}

struct rk817_codec_rk8xx_find_data
{
    struct rt_ofw_node *np;
    struct rk8xx *rk8xx;
};

static rt_err_t rk817_codec_rk8xx_iter(struct rt_object *object, void *data)
{
    struct rk817_codec_rk8xx_find_data *find = data;
    struct rt_device *dev;

    if (rt_object_get_type(object) != RT_Object_Class_Device)
    {
        return RT_EOK;
    }

    dev = (struct rt_device *)object;

    if (dev->ofw_node == find->np && dev->user_data)
    {
        find->rk8xx = dev->user_data;
        return -RT_EINTR;
    }

    return RT_EOK;
}

struct rk8xx *rk817_codec_rk8xx_from_np(struct rt_ofw_node *np)
{
    struct rk817_codec_rk8xx_find_data find =
    {
        .np = np,
        .rk8xx = RT_NULL,
    };

    rt_object_for_each(RT_Object_Class_Device, rk817_codec_rk8xx_iter, &find);

    return find.rk8xx;
}

rt_err_t rk817_codec_bind_rk8xx(struct rk817_codec **out_codec, struct rk8xx *rk8xx)
{
    struct rk817_codec *codec;

    if (!out_codec || !rk8xx)
    {
        return -RT_EINVAL;
    }

    codec = rt_calloc(1, sizeof(*codec));

    if (!codec)
    {
        return -RT_ENOMEM;
    }

    codec->rk8xx = rk8xx;
    codec->hp_volume = RK817_DEFAULT_HP_VOL;
    codec->spk_volume = RK817_DEFAULT_SPK_VOL;
    codec->np = rk8xx->dev ? rk8xx->dev->ofw_node : RT_NULL;

    rt_spin_lock(&codec_list_lock);
    rt_list_insert_before(&codec_list, &codec->list);
    rt_spin_unlock(&codec_list_lock);

    *out_codec = codec;

    return RT_EOK;
}

struct rk817_codec *rk817_codec_find(struct rt_ofw_node *np)
{
    struct rk817_codec *codec;

    rt_spin_lock(&codec_list_lock);
    rt_list_for_each_entry(codec, &codec_list, list)
    {
        if (codec->np == np)
        {
            rt_spin_unlock(&codec_list_lock);
            return codec;
        }
    }
    rt_spin_unlock(&codec_list_lock);

    return RT_NULL;
}

rt_err_t rk817_codec_hw_params(struct rk817_codec *codec, const struct rk817_codec_config *cfg)
{
    rt_uint8_t apll_cfg3;
    rt_uint8_t dtop_digen_sr_lmt0;

    if (!codec || !cfg)
    {
        return -RT_EINVAL;
    }

    if (codec->mclk)
    {
        rt_clk_set_rate(codec->mclk, cfg->mclk_rate);
        rt_clk_prepare_enable(codec->mclk);
    }

    rk817_update_bits(codec, RK817_CODEC_DI2S_CKM, RK817_I2S_MODE_MASK, RK817_I2S_MODE_SLV);

    switch (cfg->samplerate)
    {
    case 8000:
        apll_cfg3 = 0x03;
        dtop_digen_sr_lmt0 = 0x00;
        break;
    case 16000:
        apll_cfg3 = 0x06;
        dtop_digen_sr_lmt0 = 0x01;
        break;
    case 32000:
    case 44100:
    case 48000:
        apll_cfg3 = 0x0c;
        dtop_digen_sr_lmt0 = 0x02;
        break;
    case 96000:
        apll_cfg3 = 0x18;
        dtop_digen_sr_lmt0 = 0x03;
        break;
    default:
        return -RT_EINVAL;
    }

    if (codec->rate != cfg->samplerate)
    {
        rk817_write(codec, RK817_CODEC_APLL_CFG3, apll_cfg3);
        rk817_update_bits(codec, RK817_CODEC_DDAC_SR_LMT0, DACSRT_MASK, dtop_digen_sr_lmt0);
        rk817_restart_dac_digital_clk(codec);
        codec->rate = cfg->samplerate;
    }

    if (cfg->samplebits == 16)
    {
        rk817_write(codec, RK817_CODEC_DI2S_RXCR2, VDW_RX_16BITS);
        rk817_write(codec, RK817_CODEC_DI2S_TXCR2, VDW_TX_16BITS);
    }

    return RT_EOK;
}

rt_err_t rk817_codec_start(struct rk817_codec *codec)
{
    if (!codec)
    {
        return -RT_EINVAL;
    }

    if (!codec->powered)
    {
        rk817_codec_power_up(codec);
        codec->powered = RT_TRUE;
    }

    rk817_set_hp_path(codec);
    rk817_update_bits(codec, RK817_CODEC_DTOP_DIGEN_CLKE, I2STX_EN_MASK, I2STX_EN);

    return RT_EOK;
}

rt_err_t rk817_codec_stop(struct rk817_codec *codec)
{
    if (!codec)
    {
        return -RT_EINVAL;
    }

    rk817_update_bits(codec, RK817_CODEC_DTOP_DIGEN_CLKE, I2STX_EN_MASK, I2STX_DIS);

    if (codec->powered)
    {
        rk817_codec_power_down(codec);
        codec->powered = RT_FALSE;
    }

    if (codec->mclk)
    {
        rt_clk_disable_unprepare(codec->mclk);
    }

    return RT_EOK;
}

rt_err_t rk817_codec_set_volume(struct rk817_codec *codec, rt_uint8_t volume)
{
    rt_uint8_t reg_val;

    if (!codec)
    {
        return -RT_EINVAL;
    }

    if (volume > AUDIO_VOLUME_MAX)
    {
        volume = AUDIO_VOLUME_MAX;
    }

    reg_val = RK817_DAC_VOL_MAX -
            ((volume * (RK817_DAC_VOL_MAX - RK817_DAC_VOL_MIN)) / AUDIO_VOLUME_MAX);

    if (reg_val < RK817_DAC_VOL_MIN)
    {
        reg_val = RK817_DAC_VOL_MIN;
    }

    codec->hp_volume = reg_val;
    rk817_write(codec, RK817_CODEC_DDAC_VOLL, reg_val);
    rk817_write(codec, RK817_CODEC_DDAC_VOLR, reg_val);

    return RT_EOK;
}

static rt_err_t rk817_codec_probe(struct rt_platform_device *pdev)
{
    struct rk8xx *rk8xx = pdev->priv;
    struct rk817_codec *codec;
    rt_uint32_t hp_vol = RK817_DEFAULT_HP_VOL;

    if (!rk8xx)
    {
        return -RT_EINVAL;
    }

    if (rk817_codec_bind_rk8xx(&codec, rk8xx))
    {
        return -RT_ENOMEM;
    }

    codec->mclk = rt_clk_get_by_name(&pdev->parent, "mclk");

    if (!rt_is_err(codec->mclk))
    {
        rt_ofw_prop_read_u32(pdev->parent.ofw_node, "hp-volume", &hp_vol);
        codec->hp_volume = (rt_uint8_t)hp_vol;
    }

    pdev->parent.user_data = codec;

    return RT_EOK;
}

static rt_err_t rk817_codec_remove(struct rt_platform_device *pdev)
{
    struct rk817_codec *codec = pdev->parent.user_data;

    if (codec)
    {
        rt_spin_lock(&codec_list_lock);
        rt_list_remove(&codec->list);
        rt_spin_unlock(&codec_list_lock);
        rt_free(codec);
    }

    return RT_EOK;
}

static const struct rt_ofw_node_id rk817_codec_ofw_ids[] =
{
    { .compatible = "rockchip,rk817-codec" },
    { .compatible = "rockchip,rk809-codec" },
    { /* sentinel */ }
};

static struct rt_platform_driver rk817_codec_driver =
{
    .name = "rk817-codec",
    .ids = rk817_codec_ofw_ids,
    .probe = rk817_codec_probe,
    .remove = rk817_codec_remove,
};

static int rk817_codec_register(void)
{
    rt_platform_driver_register(&rk817_codec_driver);

    return 0;
}
INIT_DEVICE_EXPORT(rk817_codec_register);
