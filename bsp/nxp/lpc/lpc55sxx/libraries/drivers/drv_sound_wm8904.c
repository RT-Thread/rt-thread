/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-12     Vandoul      the first version
 */

#include <rtthread.h>
#include <drivers/dev_audio.h>
#include <drivers/dev_i2c.h>
#include "drv_sound_wm8904.h"

/**
 * @brief object of wm8904.
 */
struct drv_sound_wm8904{
    struct rt_i2c_bus_device *i2c_bus;
    rt_device_t i2s_bus;
    int i2c_addr;
};

rt_err_t wm8904_write_register(struct drv_sound_wm8904 *dev, rt_uint8_t reg, rt_uint16_t value)
{
    struct rt_i2c_msg msg[2];
    rt_uint8_t buf[2];
    buf[0] = (value>>8)&0xFF;
    buf[1] = value&0xFF;
    msg[0].addr = dev->i2c_addr;
    msg[0].buf = &reg;
    msg[0].flags = RT_I2C_WR;
    msg[0].len = 1;
    msg[1].addr = dev->i2c_addr;
    msg[1].buf = buf;
    msg[1].flags = RT_I2C_WR|RT_I2C_NO_START;
    msg[1].len = 2;
    if(rt_i2c_transfer(dev->i2c_bus, msg, 2) != 2)
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}

rt_err_t wm8904_read_register(struct drv_sound_wm8904 *dev, rt_uint8_t reg, rt_uint16_t *value)
{
    struct rt_i2c_msg msg[2];
    rt_uint8_t buf[2];
    msg[0].addr = dev->i2c_addr;
    msg[0].buf = &reg;
    msg[0].flags = RT_I2C_WR;
    msg[0].len = 1;
    msg[1].addr = dev->i2c_addr;
    msg[1].buf = buf;
    msg[1].flags = RT_I2C_RD|RT_I2C_NO_START;
    msg[1].len = 2;
    if(rt_i2c_transfer(dev->i2c_bus, msg, 2) != 2)
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}

rt_err_t wm8904_modify_register(struct drv_sound_wm8904 *dev, rt_uint8_t reg, rt_uint16_t mask, rt_uint16_t value)
{
    rt_uint16_t reg_value;
    rt_err_t ret;

    ret = wm8904_read_register(dev, reg, &reg_value);
    if(ret != RT_EOK)
    {
        return ret;
    }
    reg_value &= (uint16_t)~mask;
    reg_value |= value;
    return wm8904_write_register(dev, reg, reg_value);
}

static rt_err_t wm8904_wait_on_write_sequencer(struct drv_sound_wm8904 *dev)
{
    rt_err_t ret;
    rt_uint16_t value;

    do {
        ret = wm8904_read_register(dev, WM8904_WRT_SEQUENCER_4, &value);
    }while((ret == RT_EOK) && ((value & 1U) != 0u));
    return ret;
}

static rt_err_t wm8904_updateformat(struct drv_sound_wm8904 *dev, wm8904_fs_ratio_t fs_ratio, wm8904_sample_rate_t sample_rate, wm8904_bit_width_t bit_width)
{
    rt_err_t err = RT_EOK;
    /** Disable SYSCLK */
    err = wm8904_write_register(dev, WM8904_CLK_RATES_2, 0x00);
    if(err != RT_EOK)
    {
        return err;
    }
    /** Set clock ratio and sample rate */
    err = wm8904_write_register(dev, WM8904_CLK_RATES_1, (rt_uint16_t)((rt_uint16_t)fs_ratio << 10U) | (rt_uint16_t)sample_rate);
    if(err != RT_EOK)
    {
        return err;
    }
    /** Set bit resolution. */
    err = wm8904_modify_register(dev, WM8904_AUDIO_IF_1, (0x000CU), (rt_uint16_t)bit_width << 2U);
    if(err != RT_EOK)
    {
        return err;
    }
    /** Enable SYSCLK */
    err = wm8904_write_register(dev, WM8904_CLK_RATES_2, 0x1007);
    if(err != RT_EOK)
    {
        return err;
    }
    return RT_EOK;
}

static rt_err_t wm8904_i2c_bus_init(struct rt_i2c_bus_device *i2c_bus)
{
    (void)i2c_bus;
    return RT_EOK;
}
static rt_err_t wm8904_i2s_bus_init(rt_device_t i2s_bus)
{
    (void)i2s_bus;
    return RT_EOK;
}

const static uint16_t wm8904_init_list[][2] = {
    /* TOCLK_RATE_DIV16=0, TOCLK_RATE_x4=1, SR_MODE=0, MCLK_DIV=1
     * (Required for MMCs: SGY, KRT see erratum CE000546) */
    {WM8904_CLK_RATES_0, 0xA45F},
    /* INL_ENA=1, INR ENA=1 */
    {WM8904_POWER_MGMT_0, 0x0003},
    /* HPL_PGA_ENA=1, HPR_PGA_ENA=1 */
    {WM8904_POWER_MGMT_2, 0x0003},
    /* DACL_ENA=1, DACR_ENA=1, ADCL_ENA=1, ADCR_ENA=1 */
    {WM8904_POWER_MGMT_6, 0x000F},
    /* ADC_OSR128=1 */
    {WM8904_ANALOG_ADC_0, 0x0001},
    /* DACL_DATINV=0, DACR_DATINV=0, DAC_BOOST=00, LOOPBACK=0, AIFADCL_SRC=0,
     * AIFADCR_SRC=1, AIFDACL_SRC=0, AIFDACR_SRC=1, ADC_COMP=0, ADC_COMPMODE=0,
     * DAC_COMP=0, DAC_COMPMODE=0 */
    {WM8904_AUDIO_IF_0, 0x0050},
    /* DAC_MONO=0, DAC_SB_FILT-0, DAC_MUTERATE=0, DAC_UNMUTE RAMP=0,
     * DAC_OSR128=1, DAC_MUTE=0, DEEMPH=0 (none) */
    {WM8904_DAC_DIG_1, 0x0040},
    /* LINMUTE=0, LIN_VOL=0_0101 */
    {WM8904_ANALOG_LEFT_IN_0, 0x0005},
    /* RINMUTE=0, RIN VOL=0_0101 LINEOUTL RMV SHORT-1, LINEOUTL ENA_OUTP=1,
     * LINEOUTL_ENA_DLY=1, LINEOUTL_ENA=1, LINEOUTR_RMV_SHORT-1,
     * LINEOUTR_ENA_OUTP=1 */
    {WM8904_ANALOG_RIGHT_IN_0, 0x0005},
    /* HPOUTL_MUTE=0, HPOUT_VU=0, HPOUTLZC=0, HPOUTL_VOL=10_1101 */
    {WM8904_ANALOG_OUT1_LEFT, 0x00AD},
    /* HPOUTR_MUTE=0, HPOUT_VU=0, HPOUTRZC=0, HPOUTR_VOL=10_1101 */
    {WM8904_ANALOG_OUT1_RIGHT, 0x00AD},
    /* Enable DC servos for headphone out */
    {WM8904_DC_SERVO_0, 0x0003},
    /* HPL_RMV_SHORT=1, HPL_ENA_OUTP=1, HPL_ENA_DLY=1, HPL_ENA=1,
     * HPR_RMV_SHORT=1, HPR_ENA_OUTP=1, HPR_ENA_DLY=1, HPR_ENA=1 */
    {WM8904_ANALOG_HP_0, 0x00FF},
    /* CP_DYN_PWR=1 */
    {WM8904_CLS_W_0, 0x0001},
    /* CP_ENA=1 */
    {WM8904_CHRG_PUMP_0, 0x0001},
    /* TOCLK_RATE_DIV16=0, TOCLK_RATE_x4=1, SR_MODE=0, MCLK_DIV=1
     * (Required for MMCs: SGY, KRT see erratum CE000546) */
    {WM8904_CLK_RATES_0, 0xA45F},
    /* INL_ENA=1, INR ENA=1 */
    {WM8904_POWER_MGMT_0, 0x0003},
    /* HPL_PGA_ENA=1, HPR_PGA_ENA=1 */
    {WM8904_POWER_MGMT_2, 0x0003},
    /* DACL_ENA=1, DACR_ENA=1, ADCL_ENA=1, ADCR_ENA=1 */
    {WM8904_POWER_MGMT_6, 0x000F},
    /* ADC_OSR128=1 */
    {WM8904_ANALOG_ADC_0, 0x0001},
    /* DACL_DATINV=0, DACR_DATINV=0, DAC_BOOST=00, LOOPBACK=0, AIFADCL_SRC=0,
     * AIFADCR_SRC=1, AIFDACL_SRC=0, AIFDACR_SRC=1, ADC_COMP=0, ADC_COMPMODE=0,
     * DAC_COMP=0, DAC_COMPMODE=0 */
    {WM8904_AUDIO_IF_0, 0x0050},
    /* DAC_MONO=0, DAC_SB_FILT-0, DAC_MUTERATE=0, DAC_UNMUTE RAMP=0,
     * DAC_OSR128=1, DAC_MUTE=0, DEEMPH=0 (none) */
    {WM8904_DAC_DIG_1, 0x0040},
    /* LINMUTE=0, LIN_VOL=0_0101 */
    {WM8904_ANALOG_LEFT_IN_0, 0x0005},
    /* RINMUTE=0, RIN VOL=0_0101 LINEOUTL RMV SHORT-1, LINEOUTL ENA_OUTP=1,
     * LINEOUTL_ENA_DLY=1, LINEOUTL_ENA=1, LINEOUTR_RMV_SHORT-1,
     * LINEOUTR_ENA_OUTP=1 */
    {WM8904_ANALOG_RIGHT_IN_0, 0x0005},
    /* HPOUTL_MUTE=0, HPOUT_VU=0, HPOUTLZC=0, HPOUTL_VOL=10_1101 */
    {WM8904_ANALOG_OUT1_LEFT, 0x00AD},
    /* HPOUTR_MUTE=0, HPOUT_VU=0, HPOUTRZC=0, HPOUTR_VOL=10_1101 */
    {WM8904_ANALOG_OUT1_RIGHT, 0x00AD},
    /* Enable DC servos for headphone out */
    {WM8904_DC_SERVO_0, 0x0003},
    /* HPL_RMV_SHORT=1, HPL_ENA_OUTP=1, HPL_ENA_DLY=1, HPL_ENA=1,
     * HPR_RMV_SHORT=1, HPR_ENA_OUTP=1, HPR_ENA_DLY=1, HPR_ENA=1 */
    {WM8904_ANALOG_HP_0, 0x00FF},
    /* CP_DYN_PWR=1 */
    {WM8904_CLS_W_0, 0x0001},
    /* CP_ENA=1 */
    {WM8904_CHRG_PUMP_0, 0x0001},
};
rt_err_t wm8904_init(struct drv_sound_wm8904 *dev, struct wm8904_config *config)
{
    rt_err_t ret;

    dev->i2c_bus = rt_i2c_bus_device_find(config->i2c_bus_name);
    if(dev->i2c_bus == RT_NULL)
    {
        return -RT_EINVAL;
    }
    dev->i2s_bus = rt_device_find(config->i2s_bus_name);
    if(dev->i2s_bus == RT_NULL)
    {
        return -RT_EINVAL;
    }

    wm8904_i2c_bus_init(dev->i2c_bus);
    wm8904_i2s_bus_init(dev->i2s_bus);

    ret = wm8904_write_register(dev, WM8904_RESET, 0x0000);
    if(ret != RT_EOK)
    {
        return ret;
    }

    /* MCLK_INV=0, SYSCLK_SRC=0, TOCLK_RATE=0, OPCLK_ENA=1,
     * CLK_SYS_ENA=1, CLK_DSP_ENA=1, TOCLK_ENA=1 */
    ret = wm8904_write_register(dev, WM8904_CLK_RATES_2, 0x000F);
    if(ret != RT_EOK)
    {
        return ret;
    }

    /* WSEQ_ENA=1, WSEQ_WRITE_INDEX=0_0000 */
    ret = wm8904_write_register(dev, WM8904_WRT_SEQUENCER_0, 0x0100);
    if(ret != RT_EOK)
    {
        return ret;
    }

    /* WSEQ_ABORT=0, WSEQ_START=1, WSEQ_START_INDEX=00_0000 */
    ret = wm8904_write_register(dev, WM8904_WRT_SEQUENCER_3, 0x0100);
    if(ret != RT_EOK)
    {
        return ret;
    }

    /* WSEQ_ENA=1, WSEQ_SRITE_INDEX=0_0000 */
    ret = wm8904_write_register(dev, WM8904_WRT_SEQUENCER_0, 0x0100);
    if(ret != RT_EOK)
    {
        return ret;
    }

    ret = wm8904_wait_on_write_sequencer(dev);
    if(ret != RT_EOK)
    {
        return ret;
    }

    for(int i=0; i<sizeof(wm8904_init_list)/sizeof(wm8904_init_list[0]); i++)
    {
        ret = wm8904_write_register(dev, wm8904_init_list[i][0], wm8904_init_list[i][1]);
        if(ret != RT_EOK)
        {
            return ret;
        }
    }

    return ret;
}

rt_err_t wm8904_deinit(struct drv_sound_wm8904 *dev)
{
    return wm8904_write_register(dev, WM8904_RESET, 0x0000);
}

rt_err_t wm8904_set_master_clock(struct drv_sound_wm8904 *dev, rt_uint32_t sysclk, rt_uint32_t sample_rate, rt_uint32_t bit_width)
{
    rt_uint32_t bclk = sample_rate * bit_width * 2U;
    rt_uint32_t bclk_div = 0U;
    rt_uint16_t audio_interface = 0U;
    rt_err_t err = RT_EOK;
    rt_uint16_t sysclk_div = 0;

    err = wm8904_read_register(dev, WM8904_CLK_RATES_0, &sysclk_div);
    sysclk = sysclk >> (sysclk_div & 0x1U);

    if((sysclk / bclk > 48U) || (bclk / sample_rate > 2047U) || (bclk / sample_rate < 8U))
    {
        return -RT_EINVAL;
    }

    err = wm8904_read_register(dev, WM8904_AUDIO_IF_2, &audio_interface);
    if(err != RT_EOK)
    {
        return err;
    }

    audio_interface &= ~(rt_uint16_t)0x1FU;
    bclk_div = (sysclk * 10U) / bclk;

    switch(bclk_div)
    {
        case 10:
            audio_interface |= 0U;
            break;
        case 15:
            audio_interface |= 1U;
            break;
        case 20:
            audio_interface |= 2U;
            break;
        case 30:
            audio_interface |= 3U;
            break;
        case 40:
            audio_interface |= 4U;
            break;
        case 50:
            audio_interface |= 5U;
            break;
        case 55:
            audio_interface |= 6U;
            break;
        case 60:
            audio_interface |= 7U;
            break;
        case 80:
            audio_interface |= 8U;
            break;
        case 100:
            audio_interface |= 9U;
            break;
        case 110:
            audio_interface |= 10U;
            break;
        case 120:
            audio_interface |= 11U;
            break;
        case 160:
            audio_interface |= 12U;
            break;
        case 200:
            audio_interface |= 13U;
            break;
        case 220:
            audio_interface |= 14U;
            break;
        case 240:
            audio_interface |= 15U;
            break;
        case 250:
            audio_interface |= 16U;
            break;
        case 300:
            audio_interface |= 17U;
            break;
        case 320:
            audio_interface |= 18U;
            break;
        case 440:
            audio_interface |= 19U;
            break;
        case 480:
            audio_interface |= 20U;
            break;
        default:
            err = -RT_EINVAL;
            break;
    }
    if(err != RT_EOK)
    {
        return err;
    }

    /** bclk divider */
    err = wm8904_write_register(dev, WM8904_AUDIO_IF_2, audio_interface);
    if(err != RT_EOK)
    {
        return err;
    }

    err = wm8904_modify_register(dev, WM8904_GPIO_CONTROL_4, 0x8FU, 1U);
    if(err != RT_EOK)
    {
        return err;
    }
    /** LRCLK direction and divider */
    audio_interface = (rt_uint16_t)((1UL << 11U) | (bclk / sample_rate));
    err = wm8904_modify_register(dev, WM8904_AUDIO_IF_3, 0xFFFU, audio_interface);
    if(err != RT_EOK)
    {
        return err;
    }
    return RT_EOK;
}

rt_err_t wm8904_set_fll_config(struct drv_sound_wm8904 *dev, wm8904_fll_config_t *config)
{
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(config != RT_NULL);

    rt_uint32_t reference_clock = config->ref_clock_hz;
    rt_uint32_t input_divider = 0U;
    rt_uint32_t fvco = 0U, output_div = 0U, ratio = 0U;
    rt_uint32_t n = 0U, k = 0U;

    /* it is recommended that the highest possible frequency - within the 13.5MHz limit - should be selected */
    if(reference_clock < 13500000U)
    {
        input_divider = 0;
    }
    else if(reference_clock / 2U < 13500000U)
    {
        input_divider = 1;
    }
    else if(reference_clock / 4U < 13500000U)
    {
        input_divider = 2;
    }
    else
    {
        input_divider = 3;
    }

    if(reference_clock / (1UL << input_divider) > 13500000)
    {
        return -RT_EINVAL;
    }

    reference_clock = reference_clock / (1UL << input_divider);

    for (output_div = 4U; output_div <= 64U; output_div++)
    {
        fvco = output_div * config->output_clock_hz;
        if ((fvco >= 90000000U) && (fvco <= 100000000U))
        {
            break;
        }
    }

    if(reference_clock <= 64000U)
    {
        ratio = 4U;
    }
    else if(reference_clock <= 128000U)
    {
        ratio = 3U;
    }
    else if(reference_clock <= 256000U)
    {
        ratio = 2U;
    }
    else if(reference_clock <= 1000000U)
    {
        ratio = 1U;
    }
    else
    {
        ratio = 0U;
    }

    n = fvco / ((ratio + 1U) * reference_clock);
    k = (rt_uint32_t)((rt_uint64_t)fvco * 1000000U) / ((ratio + 1U) * reference_clock);
    if(n != 0U)
    {
        k = k - n * 1000000U;
    }
    k = (rt_uint32_t)((rt_uint64_t)k * 65536U) / 1000000U;

    /* configure WM8904 */
    if (wm8904_modify_register(dev, WM8904_FLL_CONTROL_1, 7U, 4U) != RT_EOK)
    {
        return -RT_ERROR;
    }

    /* configure WM8904 */
    if (wm8904_modify_register(dev, WM8904_FLL_CONTROL_2, 0x3F07U, (rt_uint16_t)(((output_div - 1U) << 8U) | ratio)) != RT_EOK)
    {
        return -RT_ERROR;
    }

    if (wm8904_write_register(dev, WM8904_FLL_CONTROL_3, (rt_uint16_t)k) != RT_EOK)
    {
        return -RT_ERROR;
    }

    if (wm8904_modify_register(dev, WM8904_FLL_CONTROL_4, 0x7FE0U, (rt_uint16_t)(n << 5U)) != RT_EOK)
    {
        return -RT_ERROR;
    }

    if (wm8904_write_register(dev, WM8904_FLL_CONTROL_5, (rt_uint16_t)((input_divider << 3U) | (rt_uint16_t)config->source)) != RT_EOK)
    {
        return -RT_ERROR;
    }

    if (wm8904_modify_register(dev, WM8904_FLL_CONTROL_1, 1U, 1) != RT_EOK)
    {
        return -RT_ERROR;
    }

    /** enable GPIO1 output fll output clock */
    if (wm8904_write_register(dev, WM8904_GPIO_CONTROL_1, (rt_uint16_t)9U) != RT_EOK)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

rt_err_t wm8904_set_protocol(struct drv_sound_wm8904 *dev, wm8904_protocol_t p)
{
    return wm8904_modify_register(dev, WM8904_AUDIO_IF_1, (0x0003U | (1U << 4U)), (rt_uint16_t)p);
}

rt_err_t wm8904_select_lrc_polarity(struct drv_sound_wm8904 *dev, rt_uint32_t polarity)
{
    return wm8904_modify_register(dev, WM8904_AUDIO_IF_1, 0x0010U, (rt_uint16_t)polarity);
}

rt_err_t wm8904_enable_dac_time_slot(struct drv_sound_wm8904 *dev, wm8904_timeslot_t timeslot)
{
    return wm8904_modify_register(dev, WM8904_AUDIO_IF_1, ((rt_uint16_t)3U << 12U), (((rt_uint16_t)1U << 13U) | ((rt_uint16_t)timeslot << 12U)));
}

rt_err_t wm8904_enable_adc_time_slot(struct drv_sound_wm8904 *dev, wm8904_timeslot_t timeslot)
{
    return wm8904_modify_register(dev, WM8904_AUDIO_IF_1, ((rt_uint16_t)3U << 10U), (((rt_uint16_t)1U << 11U) | ((rt_uint16_t)timeslot << 10U)));
}

rt_err_t wm8904_check_audio_format(struct drv_sound_wm8904 *dev, wm8904_audio_format_t *format, rt_uint32_t mclk_freq)
{
    RT_ASSERT((dev != RT_NULL) && (format != RT_NULL));

    rt_err_t err = RT_EOK;
    rt_uint16_t mclk_div = 0U;
    rt_uint32_t sample_rate = 0U;
    rt_uint32_t fs_ratio = 0;
    wm8904_sample_rate_t reg_sample_rate = format->sampleRate;

    err = wm8904_read_register(dev, WM8904_CLK_RATES_0, &mclk_div);
    if(err != RT_EOK)
    {
        return err;
    }

    switch(format->sampleRate)
    {
        case WM8904_SAMPLERATE_8kHz:
            sample_rate = 8000;
            break;
        case WM8904_SAMPLERATE_12kHz  :
            sample_rate = 12000;
            break;
        case WM8904_SAMPLERATE_16kHz  :
            sample_rate = 16000;
            break;
        case WM8904_SAMPLERATE_24kHz  :
            sample_rate = 24000;
            break;
        case WM8904_SAMPLERATE_32kHz  :
            sample_rate = 32000;
            break;
        case WM8904_SAMPLERATE_48kHz  :
            sample_rate = 48000;
            break;
        case WM8904_SAMPLERATE_11025Hz:
            sample_rate = 11025;
            reg_sample_rate = WM8904_SAMPLERATE_12kHz;
            break;
        case WM8904_SAMPLERATE_22050Hz:
            sample_rate = 22050;
            reg_sample_rate = WM8904_SAMPLERATE_24kHz;
            break;
        case WM8904_SAMPLERATE_44100Hz:
            sample_rate = 44100;
            reg_sample_rate = WM8904_SAMPLERATE_48kHz;
            break;
        default:
            err = -RT_EINVAL;
            break;
    }

    if(err != RT_EOK)
    {
        return err;
    }

    fs_ratio = (mclk_freq >> (mclk_div & 0x1U)) / sample_rate;

    switch(fs_ratio)
    {
        case 64:
            format->fsRatio = WM8904_FSRATIO_64X;
            break;
        case 128 :
            format->fsRatio = WM8904_FSRATIO_128X;
            break;
        case 192 :
            format->fsRatio = WM8904_FSRATIO_192X;
            break;
        case 256 :
            format->fsRatio = WM8904_FSRATIO_256X;
            break;
        case 384 :
            format->fsRatio = WM8904_FSRATIO_384X;
            break;
        case 512 :
            format->fsRatio = WM8904_FSRATIO_512X;
            break;
        case 768 :
            format->fsRatio = WM8904_FSRATIO_768X;
            break;
        case 1024:
            format->fsRatio = WM8904_FSRATIO_1024X;
            break;
        case 1408:
            format->fsRatio = WM8904_FSRATIO_1408X;
            break;
        case 1536:
            format->fsRatio = WM8904_FSRATIO_1536X;
            break;
        default:
            err = -RT_EINVAL;
            break;
    }

    if(err != RT_EOK)
    {
        return err;
    }
    return wm8904_updateformat(dev, format->fsRatio, reg_sample_rate, format->bitWidth);
}

rt_err_t wm8904_set_audio_format(struct drv_sound_wm8904 *dev, rt_uint32_t sysclk, rt_uint32_t sample_rate, rt_uint32_t bit_width)
{
    rt_uint32_t ratio = 0;
    rt_err_t err = RT_EOK;
    wm8904_bit_width_t reg_bit_width = WM8904_BITWIDTH_32;
    wm8904_sample_rate_t reg_sample_reate = WM8904_SAMPLERATE_48kHz;
    wm8904_fs_ratio_t reg_fsratio = WM8904_FSRATIO_1536X;

    rt_uint16_t temp_reg = 0U;

    err = wm8904_read_register(dev, WM8904_CLK_RATES_0, &temp_reg);
    if(err != RT_EOK)
    {
        return err;
    }

    switch(sample_rate)
    {
        case 8000:
            sample_rate = WM8904_SAMPLERATE_8kHz;
            break;
        case 11025:
            sample_rate = WM8904_SAMPLERATE_12kHz;
            break;
        case 12000:
            sample_rate = WM8904_SAMPLERATE_12kHz;
            break;
        case 16000:
            sample_rate = WM8904_SAMPLERATE_16kHz;
            break;
        case 22050:
            sample_rate = WM8904_SAMPLERATE_24kHz;
            break;
        case 24000:
            sample_rate = WM8904_SAMPLERATE_24kHz;
            break;
        case 32000:
            sample_rate = WM8904_SAMPLERATE_32kHz;
            break;
        case 44100:
            sample_rate = WM8904_SAMPLERATE_48kHz;
            break;
        case 48000:
            sample_rate = WM8904_SAMPLERATE_48kHz;
            break;
        default:
            err = -RT_EINVAL;
            break;
    }
    if(err != RT_EOK)
    {
        return err;
    }

    switch(bit_width)
    {
        case 16:
            reg_bit_width = WM8904_BITWIDTH_16;
            break;
        case 20:
            reg_bit_width = WM8904_BITWIDTH_20;
            break;
        case 24:
            reg_bit_width = WM8904_BITWIDTH_24;
            break;
        case 32:
            reg_bit_width = WM8904_BITWIDTH_32;
            break;
        default:
            err = -RT_EINVAL;
            break;
    }
    if(err != RT_EOK)
    {
        return err;
    }

    ratio = (sysclk >> (temp_reg & 0x1U)) / sample_rate;

    switch(ratio)
    {
        case 64:
            reg_fsratio = WM8904_FSRATIO_64X;
            break;
        case 128 :
            reg_fsratio = WM8904_FSRATIO_128X;
            break;
        case 192 :
            reg_fsratio = WM8904_FSRATIO_192X;
            break;
        case 256 :
            reg_fsratio = WM8904_FSRATIO_256X;
            break;
        case 384 :
            reg_fsratio = WM8904_FSRATIO_384X;
            break;
        case 512 :
            reg_fsratio = WM8904_FSRATIO_512X;
            break;
        case 768 :
            reg_fsratio = WM8904_FSRATIO_768X;
            break;
        case 1024:
            reg_fsratio = WM8904_FSRATIO_1024X;
            break;
        case 1408:
            reg_fsratio = WM8904_FSRATIO_1408X;
            break;
        case 1536:
            reg_fsratio = WM8904_FSRATIO_1536X;
            break;
        default:
            err = -RT_EINVAL;
            break;
    }

    if(err != RT_EOK)
    {
        return err;
    }
    err = wm8904_updateformat(dev, reg_fsratio, reg_sample_reate, reg_bit_width);
    if(err != RT_EOK)
    {
        return err;
    }
    err = wm8904_read_register(dev, WM8904_AUDIO_IF_1, &temp_reg);
    if(err != RT_EOK)
    {
        return err;
    }
    if((temp_reg & (1UL << 6U)) != 0)
    {
        err = wm8904_set_master_clock(dev, sysclk, sample_rate, bit_width);
    }
    return err;
}

rt_err_t wm8904_set_volume(struct drv_sound_wm8904 *dev, rt_uint16_t volume_left, rt_uint16_t volume_right)
{
    RT_ASSERT(volume_left <= WM8904_MAP_HEADPHONE_LINEOUT_MAX_VOLUME);
    RT_ASSERT(volume_right <= WM8904_MAP_HEADPHONE_LINEOUT_MAX_VOLUME);

    rt_err_t err = RT_EOK;

    err = wm8904_modify_register(dev, WM8904_ANALOG_OUT1_LEFT, 0x1BF, volume_left);
    if(err != RT_EOK)
    {
        return err;
    }
    err = wm8904_modify_register(dev, WM8904_ANALOG_OUT1_RIGHT, 0x1BF, ((rt_uint16_t)volume_right | 0x0080U));
    if(err != RT_EOK)
    {
        return err;
    }

    return RT_EOK;
}

rt_err_t wm8904_set_mute(struct drv_sound_wm8904 *dev, rt_bool_t mute_left, rt_bool_t mute_right)
{
    rt_err_t err = RT_EOK;
    rt_uint16_t left = (rt_uint16_t)(mute_left ? 0x0100U : 0x0000U);
    rt_uint16_t right = (rt_uint16_t)(mute_right ? 0x0100U : 0x0000U);

    err = wm8904_modify_register(dev, WM8904_ANALOG_OUT1_LEFT, 0x0100U, left);
    if(err != RT_EOK)
    {
        return err;
    }
    err = wm8904_modify_register(dev, WM8904_ANALOG_OUT1_RIGHT, 0x0180U, ((rt_uint16_t)right | 0x0080U));
    if(err != RT_EOK)
    {
        return err;
    }

    return err;
}

rt_err_t wm8904_set_channel_volume(struct drv_sound_wm8904 *dev, rt_uint32_t channel, rt_uint32_t volume)
{
    RT_ASSERT(volume <= WM8904_MAP_HEADPHONE_LINEOUT_MAX_VOLUME);

    rt_err_t err = RT_EOK;

    /* headphone left channel 0x1BF means unmute the OUT and reset the OUT volume update bit and volume range fields */
    if((channel & (rt_uint32_t)WM8904_HEADPHONE_LEFT) != 0U)
    {
        err = wm8904_modify_register(dev, WM8904_ANALOG_OUT1_LEFT, 0x1BFU, (rt_uint16_t)volume | 0x80U);
    }
    /* headphone right channel */
    if((channel & (rt_uint32_t)WM8904_HEADPHONE_RIGHT) != 0U)
    {
        err = wm8904_modify_register(dev, WM8904_ANALOG_OUT1_RIGHT, 0x1BFU, (rt_uint16_t)volume | 0x80U);
    }
    /* line out left channel */
    if((channel & (rt_uint32_t)WM8904_LINEOUT_LEFT) != 0U)
    {
        err = wm8904_modify_register(dev, WM8904_ANALOG_OUT2_LEFT, 0x1BFU, (rt_uint16_t)volume | 0x80U);
    }
    /* line out right channel */
    if((channel & (rt_uint32_t)WM8904_LINEOUT_RIGHT) != 0U)
    {
        err = wm8904_modify_register(dev, WM8904_ANALOG_OUT2_RIGHT, 0x1BFU, (rt_uint16_t)volume | 0x80U);
    }

    return err;
}

rt_err_t wm8904_set_channel_mute(struct drv_sound_wm8904 *dev, rt_uint32_t channel, rt_bool_t is_mute)
{
    rt_err_t err = RT_EOK;
    rt_uint16_t reg_value = 0U, reg_mask = 0U;

    reg_value = is_mute ? 0x180U : 0x80U;
    reg_mask = 0x100U;

    /* headphone left channel */
    if((channel & (rt_uint32_t)WM8904_HEADPHONE_LEFT) != 0U)
    {
        err = wm8904_modify_register(dev, WM8904_ANALOG_OUT1_LEFT, reg_mask, reg_value);
    }

    /* headphone right channel */
    if((channel & (rt_uint32_t)WM8904_HEADPHONE_RIGHT) != 0U)
    {
        err = wm8904_modify_register(dev, WM8904_ANALOG_OUT1_RIGHT, reg_mask, reg_value);
    }

    /* line out left channel */
    if((channel & (rt_uint32_t)WM8904_LINEOUT_LEFT) != 0U)
    {
        err = wm8904_modify_register(dev, WM8904_ANALOG_OUT2_LEFT, reg_mask, reg_value);
    }

    /* line out right channel */
    if((channel & (rt_uint32_t)WM8904_LINEOUT_RIGHT) != 0U)
    {
        err = wm8904_modify_register(dev, WM8904_ANALOG_OUT2_RIGHT, reg_mask, reg_value);
    }
    return err;
}

rt_err_t wm8904_enable_dac_volume(struct drv_sound_wm8904 *dev, rt_uint8_t volume)
{
    rt_err_t err = RT_EOK;
    err = wm8904_write_register(dev, WM8904_DAC_DIGITAL_VOLUME_LEFT, (rt_uint16_t)(volume | 0x100UL));
    if(err == RT_EOK)
    {
        err = wm8904_write_register(dev, WM8904_DAC_DIGITAL_VOLUME_RIGHT, (rt_uint16_t)(volume | 0x100UL));
    }
    return err;
}

rt_err_t wm8904_set_module_power(struct drv_sound_wm8904 *dev, wm8904_module_t module, rt_bool_t is_enabled)
{
    rt_uint8_t reg_addr = 0, reg_bit_mask = 0U, reg_value = 0U;
    rt_err_t err = RT_EOK;

    switch(module)
    {
        case WM8904_MODULE_ADC:
            reg_addr = WM8904_POWER_MGMT_6;
            reg_bit_mask = 3U;
            reg_value = is_enabled ? 3U : 0U;
            break;
        case WM8904_MODULE_DAC:
            reg_addr = WM8904_POWER_MGMT_6;
            reg_bit_mask = 0xCU;
            reg_value = is_enabled ? 0xCU : 0U;
            break;
        case WM8904_MODULE_PGA:
            reg_addr = WM8904_POWER_MGMT_0;
            reg_bit_mask = 3U;
            reg_value = is_enabled ? 3U : 0U;
            break;
        case WM8904_MODULE_HEADPHONE:
            reg_addr = WM8904_POWER_MGMT_2;
            reg_bit_mask = 3U;
            reg_value = is_enabled ? 3U : 0U;
            break;
        case WM8904_MODULE_LINEOUT:
            reg_addr = WM8904_POWER_MGMT_3;
            reg_bit_mask = 3U;
            reg_value = is_enabled ? 3U : 0U;
            break;
        default:
            err = -RT_EINVAL;
            break;
    }

    if(err == RT_EOK)
    {
        err = wm8904_modify_register(dev, reg_addr, reg_bit_mask, reg_value);
    }
    return err;
}

rt_err_t wm8904_set_record(struct drv_sound_wm8904 *dev, rt_uint32_t record_source)
{
    rt_uint8_t reg_left_addr = WM8904_ANALOG_LEFT_IN_1, reg_right_addr = WM8904_ANALOG_RIGHT_IN_1;
    rt_uint16_t reg_left_value = 0U, reg_right_value = 0U, reg_bit_mask = 0U;
    rt_err_t err = RT_EOK;

    switch(record_source)
    {
        case WM8904_RECORD_SOURCE_DIFFERENTIAL_LINE:
            reg_left_value = 1U;
            reg_right_value = 1U;
            reg_bit_mask = 0x3FU;
            break;
        case WM8904_RECORD_SOURCE_DIFFERENTIAL_MIC:
            reg_left_value = 2U;
            reg_right_value = 2U;
            reg_bit_mask = 0x3FU;
            break;
        case WM8904_RECORD_SOURCE_LINE_INPUT:
            reg_left_value = 0U;
            reg_right_value = 0U;
            reg_bit_mask = 0x3FU;
            break;
        case WM8904_RECORD_SOURCE_DIGITAL_MIC:
            reg_left_value = 1U << 12;
            reg_left_addr = WM8904_DAC_DIG_0;
            reg_right_addr = 0U;
            reg_bit_mask = 1U << 12;
            break;
        default:
            err = -RT_EINVAL;
            break;
    }

    if(err != RT_EOK)
    {
        return err;
    }
    err = wm8904_modify_register(dev, reg_left_addr, reg_bit_mask, reg_left_value);
    if((err == RT_EOK) && (reg_right_addr != 0U))
    {
        err = wm8904_modify_register(dev, reg_right_addr, reg_bit_mask, reg_right_value);
    }
    return err;
}

rt_err_t wm8904_set_record_channel(struct drv_sound_wm8904 *dev, rt_uint32_t left_record_channel, rt_uint32_t right_record_channel)
{
    rt_uint8_t reg_left_addr = WM8904_ANALOG_LEFT_IN_1, reg_right_addr = WM8904_ANALOG_RIGHT_IN_1;
    rt_uint16_t reg_left_value = 0U, reg_right_value = 0U, reg_bit_mask;
    rt_err_t err = RT_EOK;
    rt_uint8_t left_positive_channel = 0U, left_negative_channel = 0U, right_positive_channel = 0U, right_negative_channel = 0U;

    if((left_record_channel & (rt_uint32_t)WM8904_RECORD_CHANNEL_DIFFERENTIAL_POSITIVE1) != 0U)
    {
        left_positive_channel = 0U;
    }
    else if((left_record_channel & (rt_uint32_t)WM8904_RECORD_CHANNEL_DIFFERENTIAL_POSITIVE2) != 0U)
    {
        left_positive_channel = 1U;
    }
    else
    {
        left_positive_channel = 2U;
    }

    if((left_record_channel & (rt_uint32_t)WM8904_RECORD_CHANNEL_DIFFERENTIAL_NEGATIVE1) != 0U)
    {
        left_negative_channel = 0U;
    }
    else if((left_record_channel & (rt_uint32_t)WM8904_RECORD_CHANNEL_DIFFERENTIAL_NEGATIVE2) != 0U)
    {
        left_negative_channel = 1U;
    }
    else if((left_record_channel & (rt_uint32_t)WM8904_RECORD_CHANNEL_DIFFERENTIAL_NEGATIVE3) != 0U)
    {
        left_negative_channel = 2U;
    }
    else
    {
        left_negative_channel = left_positive_channel;
    }

    if((right_record_channel & (rt_uint32_t)WM8904_RECORD_CHANNEL_DIFFERENTIAL_POSITIVE1) != 0U)
    {
        right_positive_channel = 0U;
    }
    else if((right_record_channel & (rt_uint32_t)WM8904_RECORD_CHANNEL_DIFFERENTIAL_POSITIVE2) != 0U)
    {
        right_positive_channel = 1U;
    }
    else
    {
        right_positive_channel = 2U;
    }

    if((right_record_channel & (rt_uint32_t)WM8904_RECORD_CHANNEL_DIFFERENTIAL_NEGATIVE1) != 0U)
    {
        right_negative_channel = 0U;
    }
    else if((right_record_channel & (rt_uint32_t)WM8904_RECORD_CHANNEL_DIFFERENTIAL_NEGATIVE2) != 0U)
    {
        right_negative_channel = 1U;
    }
    else if((right_record_channel & (rt_uint32_t)WM8904_RECORD_CHANNEL_DIFFERENTIAL_NEGATIVE3) != 0U)
    {
        right_negative_channel = 2U;
    }
    else
    {
        right_negative_channel = right_positive_channel;
    }

    reg_left_value = (((rt_uint16_t)left_negative_channel & 3U) << 4U) | (((rt_uint16_t)left_positive_channel & 3U) << 2U);
    reg_right_value = (((rt_uint16_t)right_negative_channel & 3U) << 4U) | (((rt_uint16_t)right_positive_channel & 3U) << 2U);
    reg_bit_mask = 0x3CU;

    err = wm8904_modify_register(dev, reg_left_addr, reg_bit_mask, reg_left_value);
    if(err == RT_EOK)
    {
        return wm8904_modify_register(dev, reg_right_addr, reg_bit_mask, reg_right_value);
    }
    return -RT_ERROR;
}

rt_err_t wm8904_set_play(struct drv_sound_wm8904 *dev, rt_uint32_t play_source)
{
    rt_uint16_t reg_value = 0U, reg_bit_mask = 0xFU;

    /* source from PGA */
    if(play_source == (rt_uint32_t)WM8904_PLAY_SOURCE_PGA)
    {
        reg_value |= (3U << 2U) | 3U;
    } else
    /* source from DAC */
    if(play_source == (rt_uint32_t)WM8904_PLAY_SOURCE_DAC)
    {
        reg_value &= (rt_uint16_t) ~((3U << 2U) | 3U);
    }

    return wm8904_modify_register(dev, WM8904_ANALOG_OUT12_ZC, reg_bit_mask, reg_value);
}

/*******************************************************************************************/
rt_err_t wm8904_audio_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    return RT_EOK;
}
rt_err_t wm8904_audio_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    return RT_EOK;
}
rt_err_t wm8904_audio_init(struct rt_audio_device *audio)
{
    return RT_EOK;
}
rt_err_t wm8904_audio_start(struct rt_audio_device *audio, int stream)
{
    return RT_EOK;
}
rt_err_t wm8904_audio_stop(struct rt_audio_device *audio, int stream)
{
    return RT_EOK;
}
rt_ssize_t wm8904_audio_transmit(struct rt_audio_device *audio, const void *writeBuf, void *readBuf, rt_size_t size)
{
    return 0;
}
void wm8904_audio_buffer_info(struct rt_audio_device *audio, struct rt_audio_buf_info *info)
{
}
/**
 *
 */
struct rt_audio_ops wm8904_audio_ops =
{
    .getcaps     = wm8904_audio_getcaps,
    .configure   = wm8904_audio_configure,
    .init        = wm8904_audio_init,
    .start       = wm8904_audio_start,
    .stop        = wm8904_audio_stop,
    .transmit    = wm8904_audio_transmit,
    .buffer_info = wm8904_audio_buffer_info,
};
