/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#define DBG_TAG "codec.es8326"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "spacemit-audio.h"
#include "es8326.h"

struct es8326_codec
{
    struct rt_i2c_client *client;
    struct rt_ofw_node *np;
    struct rt_mutex lock;

    rt_uint8_t mic1_src;
    rt_uint8_t mic2_src;
    rt_uint8_t jack_pol;
    rt_uint8_t interrupt_clk;
    rt_uint8_t version;
    rt_uint8_t volume;

    rt_base_t speaker_pin;
    rt_uint8_t speaker_active;
    rt_bool_t calibrated;
    rt_bool_t muted;

    rt_list_t list;
};

struct es8326_coeff
{
    rt_uint16_t mclk_fs;
    rt_uint8_t reg[8];
};

static const struct es8326_coeff es8326_coeff_v0[] =
{
    { 64,  { 0xe0, 0x00, 0x03, 0x2d, 0x4a, 0x0a, 0x1f, 0x1f } },
    { 128, { 0xe0, 0x01, 0x03, 0x2d, 0x4a, 0x0a, 0x1f, 0x1f } },
    { 256, { 0xe0, 0x00, 0x30, 0x2d, 0x4a, 0x0a, 0x1f, 0x1f } },
};

static const struct es8326_coeff es8326_coeff_v3[] =
{
    { 64,  { 0xe0, 0x00, 0x31, 0x2d, 0xca, 0x0a, 0x1f, 0x1f } },
    { 128, { 0xe0, 0x00, 0x01, 0x2d, 0xca, 0x0a, 0x1f, 0x1f } },
    { 256, { 0xe0, 0x00, 0x30, 0x2d, 0xca, 0x0a, 0x1f, 0x1f } },
};

static rt_list_t codec_nodes = RT_LIST_OBJECT_INIT(codec_nodes);
static RT_DEFINE_SPINLOCK(codec_nodes_lock);

static rt_err_t es8326_write_reg(struct es8326_codec *codec,
        rt_uint8_t reg, rt_uint8_t value)
{
    rt_uint8_t data[2] = { reg, value };

    return rt_i2c_master_send(codec->client->bus, codec->client->client_addr,
            RT_I2C_WR, data, sizeof(data)) == sizeof(data) ? RT_EOK : -RT_EIO;
}

static rt_err_t es8326_read_reg(struct es8326_codec *codec,
        rt_uint8_t reg, rt_uint8_t *value)
{
    struct rt_i2c_msg messages[2];

    messages[0].addr = codec->client->client_addr;
    messages[0].flags = RT_I2C_WR;
    messages[0].buf = &reg;
    messages[0].len = 1;
    messages[1].addr = codec->client->client_addr;
    messages[1].flags = RT_I2C_RD;
    messages[1].buf = value;
    messages[1].len = 1;

    return rt_i2c_transfer(codec->client->bus, messages, 2) == 2 ?
            RT_EOK : -RT_EIO;
}

static rt_err_t es8326_update_bits(struct es8326_codec *codec,
        rt_uint8_t reg, rt_uint8_t mask, rt_uint8_t value)
{
    rt_err_t err;
    rt_uint8_t old;

    if ((err = es8326_read_reg(codec, reg, &old)))
    {
        return err;
    }

    value = (old & ~mask) | (value & mask);
    return value == old ? RT_EOK : es8326_write_reg(codec, reg, value);
}

static void es8326_speaker_set(struct es8326_codec *codec, rt_bool_t enable)
{
    if (codec->speaker_pin >= 0)
    {
        rt_pin_write(codec->speaker_pin,
                enable ? codec->speaker_active : !codec->speaker_active);
    }
}

static rt_err_t es8326_calibrate(struct es8326_codec *codec)
{
    rt_err_t err;
    rt_uint8_t status, offset_l, offset_r;

    if (codec->version != ES8326_VERSION_B || codec->calibrated)
    {
        return RT_EOK;
    }

    LOG_D("ES8326 B revision headphone calibration begin");

    if ((err = es8326_write_reg(codec, ES8326_CLK_INV, 0xc0)) ||
        (err = es8326_write_reg(codec, ES8326_CLK_DIV1, 0x03)) ||
        (err = es8326_write_reg(codec, ES8326_CLK_DLL, 0x30)) ||
        (err = es8326_write_reg(codec, ES8326_CLK_MUX, 0xed)) ||
        (err = es8326_write_reg(codec, ES8326_CLK_DAC_SEL, 0x08)) ||
        (err = es8326_write_reg(codec, ES8326_CLK_TRI, 0xc1)) ||
        (err = es8326_write_reg(codec, ES8326_DAC_MUTE, 0x03)) ||
        (err = es8326_write_reg(codec, ES8326_ANA_VSEL, 0x7f)) ||
        (err = es8326_write_reg(codec, ES8326_VMIDLOW, 0x23)) ||
        (err = es8326_write_reg(codec, ES8326_DAC2HPMIX, 0x88)))
    {
        return err;
    }

    rt_thread_mdelay(16);
    es8326_write_reg(codec, ES8326_HP_OFFSET_CAL, 0x8c);
    rt_thread_mdelay(16);
    es8326_write_reg(codec, ES8326_RESET, 0xc0);
    rt_thread_mdelay(16);
    es8326_write_reg(codec, ES8326_HP_OFFSET_CAL, ES8326_HP_OFF);

    if (!es8326_read_reg(codec, ES8326_CSM_MUTE_STA, &status) &&
        (status & 0xf0) != 0x40)
    {
        rt_thread_mdelay(50);
    }

    es8326_write_reg(codec, ES8326_HP_CAL, 0xd4);
    rt_thread_mdelay(200);
    es8326_write_reg(codec, ES8326_HP_CAL, 0x4d);
    rt_thread_mdelay(200);
    es8326_write_reg(codec, ES8326_HP_CAL, ES8326_HP_OFF);

    if ((err = es8326_read_reg(codec, ES8326_HPL_OFFSET_INI, &offset_l)) ||
        (err = es8326_read_reg(codec, ES8326_HPR_OFFSET_INI, &offset_r)))
    {
        return err;
    }

    es8326_write_reg(codec, ES8326_HP_OFFSET_CAL, 0x8c);
    es8326_write_reg(codec, ES8326_HPL_OFFSET_INI, offset_l);
    es8326_write_reg(codec, ES8326_HPR_OFFSET_INI, offset_r);
    es8326_write_reg(codec, ES8326_CLK_INV, 0x00);
    codec->calibrated = RT_TRUE;

    return RT_EOK;
}

static rt_err_t es8326_hw_init(struct es8326_codec *codec)
{
    rt_err_t err;
    rt_uint8_t id1, id2;

    if ((err = es8326_read_reg(codec, ES8326_CHIP_ID1, &id1)) ||
        (err = es8326_read_reg(codec, ES8326_CHIP_ID2, &id2)) ||
        (err = es8326_read_reg(codec, ES8326_CHIP_VERSION, &codec->version)))
    {
        return err;
    }

    es8326_write_reg(codec, ES8326_RESET, 0x1f);
    es8326_write_reg(codec, ES8326_VMIDSEL, 0x0e);
    es8326_write_reg(codec, ES8326_ANA_LP, 0xf0);
    rt_thread_mdelay(10);
    es8326_write_reg(codec, ES8326_HPJACK_TIMER, 0xd9);
    es8326_write_reg(codec, ES8326_ANA_MICBIAS, 0xd8);
    es8326_write_reg(codec, ES8326_HPDET_TYPE, 0x83);
    es8326_write_reg(codec, ES8326_CLK_RESAMPLE, 0x05);
    es8326_write_reg(codec, ES8326_CLK_DIV_CPC, 0x89);
    es8326_write_reg(codec, ES8326_CLK_CTL, ES8326_CLK_ON);
    es8326_write_reg(codec, ES8326_RESET, 0x17);
    es8326_write_reg(codec, ES8326_HP_MISC, 0x3d);
    es8326_write_reg(codec, ES8326_PULLUP_CTL, 0x00);

    es8326_write_reg(codec, ES8326_HP_VOL, 0xc4);
    es8326_write_reg(codec, ES8326_HP_DRIVER, 0xa7);
    rt_hw_us_delay(2000);
    es8326_write_reg(codec, ES8326_HP_DRIVER_REF, 0x23);
    es8326_write_reg(codec, ES8326_HP_DRIVER_REF, 0x33);
    es8326_write_reg(codec, ES8326_HP_DRIVER, 0xa1);

    es8326_write_reg(codec, ES8326_CLK_INV, 0x00);
    es8326_write_reg(codec, ES8326_CLK_VMIDS1, 0xc4);
    es8326_write_reg(codec, ES8326_CLK_VMIDS2, 0x81);
    es8326_write_reg(codec, ES8326_CLK_CAL_TIME, 0x00);

    if ((err = es8326_calibrate(codec)))
    {
        return err;
    }

    es8326_write_reg(codec, ES8326_DAC_CROSSTALK, 0xaa);
    es8326_write_reg(codec, ES8326_DAC_RAMPRATE, 0x00);
    es8326_write_reg(codec, ES8326_HP_CAL, ES8326_HP_OFF);
    es8326_write_reg(codec, ES8326_ANA_LP, 0xf0);
    es8326_write_reg(codec, ES8326_ANA_VSEL, 0x7f);
    es8326_write_reg(codec, ES8326_VMIDLOW, 0x03);
    es8326_write_reg(codec, ES8326_DAC_DSM, 0x08);
    es8326_write_reg(codec, ES8326_DAC_VPPSCALE, 0x15);
    es8326_write_reg(codec, ES8326_HPDET_TYPE, 0x80 |
            ES8326_HP_DET_SRC_PIN9 | codec->jack_pol |
            (codec->version == ES8326_VERSION_B ? 0 : 0x04));
    rt_thread_mdelay(60);
    es8326_update_bits(codec, ES8326_HPDET_TYPE, 0x03, 0x00);
    es8326_write_reg(codec, ES8326_INT_SOURCE, ES8326_INT_SRC_PIN9);
    es8326_write_reg(codec, ES8326_INTOUT_IO, codec->interrupt_clk);
    es8326_write_reg(codec, ES8326_SDINOUT1_IO,
            ES8326_IO_DMIC_CLK << ES8326_SDINOUT1_SHIFT);
    es8326_write_reg(codec, ES8326_SDINOUT23_IO, ES8326_IO_INPUT);
    es8326_write_reg(codec, ES8326_ANA_PDN, 0x00);
    es8326_write_reg(codec, ES8326_RESET, ES8326_CSM_ON);
    es8326_update_bits(codec, ES8326_PGAGAIN,
            ES8326_MIC_SEL_MASK, ES8326_MIC1_SEL);
    es8326_update_bits(codec, ES8326_DAC_MUTE,
            ES8326_MUTE_MASK, ES8326_MUTE);
    es8326_write_reg(codec, ES8326_ADC_MUTE, 0x0f);
    es8326_write_reg(codec, ES8326_ADC1_SRC, codec->mic1_src);
    es8326_write_reg(codec, ES8326_ADC2_SRC, codec->mic2_src);
    es8326_write_reg(codec, ES8326_FMT, ES8326_S16_LE);

    codec->muted = RT_TRUE;
    LOG_D("ES8326 id=%02x%02x revision=%u", id1, id2, codec->version);

    return RT_EOK;
}

struct es8326_codec *es8326_codec_find(struct rt_ofw_node *np)
{
    struct es8326_codec *codec;

    rt_spin_lock(&codec_nodes_lock);
    rt_list_for_each_entry(codec, &codec_nodes, list)
    {
        if (codec->np == np)
        {
            rt_spin_unlock(&codec_nodes_lock);
            return codec;
        }
    }
    rt_spin_unlock(&codec_nodes_lock);

    return RT_NULL;
}

rt_err_t es8326_codec_hw_params(struct es8326_codec *codec,
        const struct spacemit_audio_config *config)
{
    const struct es8326_coeff *coeffs;
    rt_size_t count;
    rt_err_t err = -RT_EINVAL;

    if (!codec || !config || config->samplerate != 48000 ||
        config->channels != 2 || config->samplebits != 16)
    {
        return -RT_EINVAL;
    }

    if (codec->version == 0)
    {
        coeffs = es8326_coeff_v0;
        count = RT_ARRAY_SIZE(es8326_coeff_v0);
    }
    else
    {
        coeffs = es8326_coeff_v3;
        count = RT_ARRAY_SIZE(es8326_coeff_v3);
    }

    rt_mutex_take(&codec->lock, RT_WAITING_FOREVER);
    for (rt_size_t i = 0; i < count; ++i)
    {
        if (coeffs[i].mclk_fs == config->mclk_fs)
        {
            err = es8326_update_bits(codec, ES8326_FMT,
                    ES8326_DATA_LEN_MASK, ES8326_S16_LE);
            for (rt_size_t reg = 0; !err && reg < sizeof(coeffs[i].reg); ++reg)
            {
                err = es8326_write_reg(codec, ES8326_CLK_DIV1 + reg,
                        coeffs[i].reg[reg]);
            }
            break;
        }
    }
    rt_mutex_release(&codec->lock);

    return err;
}

rt_err_t es8326_codec_start(struct es8326_codec *codec, int stream)
{
    rt_err_t err = RT_EOK;
    rt_uint8_t hpdet;

    if (!codec || (stream != AUDIO_STREAM_REPLAY && stream != AUDIO_STREAM_RECORD))
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&codec->lock, RT_WAITING_FOREVER);
    if (stream == AUDIO_STREAM_REPLAY)
    {
        es8326_update_bits(codec, ES8326_DAC_DSM, 0x01, 0x01);
        rt_hw_us_delay(1000);
        es8326_update_bits(codec, ES8326_DAC_DSM, 0x01, 0x00);
        rt_hw_us_delay(1000);
        es8326_update_bits(codec, ES8326_HP_DRIVER_REF, 0x30, 0x20);
        es8326_update_bits(codec, ES8326_HP_DRIVER_REF, 0x30, 0x30);
        es8326_write_reg(codec, ES8326_HP_DRIVER, 0xa1);
        es8326_write_reg(codec, ES8326_HP_CAL, ES8326_HP_ON);
        err = es8326_update_bits(codec, ES8326_DAC_MUTE,
                ES8326_MUTE_MASK, 0);
        codec->muted = RT_FALSE;

        if (es8326_read_reg(codec, ES8326_HPDET_STA, &hpdet) ||
            !(hpdet & ES8326_HPINSERT_FLAG))
        {
            es8326_speaker_set(codec, RT_TRUE);
        }
    }
    else
    {
        rt_thread_mdelay(300);
        err = es8326_update_bits(codec, ES8326_ADC_MUTE, 0x0f, 0x00);
    }
    rt_mutex_release(&codec->lock);

    return err;
}

rt_err_t es8326_codec_stop(struct es8326_codec *codec, int stream)
{
    rt_err_t err;

    if (!codec || (stream != AUDIO_STREAM_REPLAY && stream != AUDIO_STREAM_RECORD))
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&codec->lock, RT_WAITING_FOREVER);
    if (stream == AUDIO_STREAM_REPLAY)
    {
        es8326_speaker_set(codec, RT_FALSE);
        es8326_write_reg(codec, ES8326_HP_CAL, ES8326_HP_OFF);
        err = es8326_update_bits(codec, ES8326_DAC_MUTE,
                ES8326_MUTE_MASK, ES8326_MUTE);
        es8326_update_bits(codec, ES8326_HP_DRIVER_REF, 0x30, 0x00);
        codec->muted = RT_TRUE;
    }
    else
    {
        err = es8326_update_bits(codec, ES8326_ADC_MUTE, 0x0f, 0x0f);
    }
    rt_mutex_release(&codec->lock);

    return err;
}

rt_err_t es8326_codec_set_volume(struct es8326_codec *codec, int volume)
{
    rt_err_t err;

    if (!codec)
    {
        return -RT_EINVAL;
    }

    if (volume < AUDIO_VOLUME_MIN)
    {
        volume = AUDIO_VOLUME_MIN;
    }
    if (volume > AUDIO_VOLUME_MAX)
    {
        volume = AUDIO_VOLUME_MAX;
    }
    rt_mutex_take(&codec->lock, RT_WAITING_FOREVER);
    err = es8326_write_reg(codec, ES8326_DAC_VOL,
            (rt_uint8_t)(volume * 0xbf / AUDIO_VOLUME_MAX));
    if (!err)
    {
        codec->volume = volume;
    }
    rt_mutex_release(&codec->lock);

    return err;
}

rt_err_t es8326_codec_set_mute(struct es8326_codec *codec, rt_bool_t mute)
{
    rt_err_t err;
    rt_uint8_t hpdet;

    if (!codec)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&codec->lock, RT_WAITING_FOREVER);
    err = es8326_update_bits(codec, ES8326_DAC_MUTE,
            ES8326_MUTE_MASK, mute ? ES8326_MUTE : 0);
    if (!err)
    {
        codec->muted = mute;
        if (mute)
        {
            es8326_speaker_set(codec, RT_FALSE);
        }
        else if (es8326_read_reg(codec, ES8326_HPDET_STA, &hpdet) ||
                 !(hpdet & ES8326_HPINSERT_FLAG))
        {
            es8326_speaker_set(codec, RT_TRUE);
        }
    }
    rt_mutex_release(&codec->lock);

    return err;
}

static rt_err_t es8326_probe(struct rt_i2c_client *client)
{
    rt_err_t err;
    rt_uint8_t pin_mode;
    struct es8326_codec *codec = rt_calloc(1, sizeof(*codec));

    if (!codec)
    {
        return -RT_ENOMEM;
    }

    codec->client = client;
    codec->np = client->parent.ofw_node;
    codec->mic1_src = ES8326_ADC_AMIC;
    codec->mic2_src = ES8326_ADC_DMIC;
    codec->jack_pol = ES8326_HP_TYPE_AUTO;
    codec->volume = 70;
    codec->speaker_pin = -1;
    rt_mutex_init(&codec->lock, "es8326", RT_IPC_FLAG_PRIO);

    rt_ofw_prop_read_u8(codec->np, "everest,mic1-src", &codec->mic1_src);
    rt_ofw_prop_read_u8(codec->np, "everest,mic2-src", &codec->mic2_src);
    rt_ofw_prop_read_u8(codec->np, "everest,jack-pol", &codec->jack_pol);
    rt_ofw_prop_read_u8(codec->np, "everest,interrupt-clk", &codec->interrupt_clk);

    codec->speaker_pin = rt_pin_get_named_pin(&client->parent, "spk-ctl", 0,
            &pin_mode, &codec->speaker_active);
    if (codec->speaker_pin >= 0)
    {
        rt_pin_mode(codec->speaker_pin, PIN_MODE_OUTPUT);
        es8326_speaker_set(codec, RT_FALSE);
    }

    if ((err = es8326_hw_init(codec)) ||
        (err = es8326_codec_hw_params(codec,
            &(struct spacemit_audio_config){ 48000, 2, 16, 64 })) ||
        (err = es8326_codec_set_volume(codec, codec->volume)))
    {
        LOG_E("ES8326 initialization failed: %s", rt_strerror(err));
        rt_mutex_detach(&codec->lock);
        rt_free(codec);
        return err;
    }

    rt_spin_lock(&codec_nodes_lock);
    rt_list_insert_before(&codec_nodes, &codec->list);
    rt_spin_unlock(&codec_nodes_lock);

    client->parent.user_data = codec;
    rt_dm_dev_bind_fwdata(&client->parent, RT_NULL, codec);

    return RT_EOK;
}

static rt_err_t es8326_remove(struct rt_i2c_client *client)
{
    struct es8326_codec *codec = client->parent.user_data;

    if (!codec)
    {
        return RT_EOK;
    }

    es8326_speaker_set(codec, RT_FALSE);
    rt_spin_lock(&codec_nodes_lock);
    rt_list_remove(&codec->list);
    rt_spin_unlock(&codec_nodes_lock);
    rt_dm_dev_unbind_fwdata(&client->parent, RT_NULL);
    rt_mutex_detach(&codec->lock);
    rt_free(codec);

    return RT_EOK;
}

static const struct rt_ofw_node_id es8326_ofw_ids[] =
{
    { .compatible = "everest,es8326" },
    { /* sentinel */ }
};

static struct rt_i2c_driver es8326_driver =
{
    .ofw_ids = es8326_ofw_ids,
    .probe = es8326_probe,
    .remove = es8326_remove,
};
RT_I2C_DRIVER_EXPORT(es8326_driver);
