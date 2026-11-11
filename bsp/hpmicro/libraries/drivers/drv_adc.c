/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <rtthread.h>

#ifdef BSP_USING_ADC
#include <rtdevice.h>
#include "board.h"
#include "drv_adc.h"
#ifdef BSP_USING_ADC12
#include "hpm_adc12_drv.h"
#endif
#ifdef BSP_USING_ADC16
#include "hpm_adc16_drv.h"
#endif
#include "hpm_sysctl_drv.h"

#if defined(BSP_USING_ADC16) && defined(ADC16_SOC_TEMP_CH_EN) && ADC16_SOC_TEMP_CH_EN
#define HPM_ADC16_HAS_TEMP_SENSOR (1)
#define HPM_ADC16_TEMP_SAMPLE_CYCLE (511U)
#else
#define HPM_ADC16_HAS_TEMP_SENSOR (0)
#endif

#ifndef BOARD_ADC_VREF_MV
#define BOARD_ADC_VREF_MV (3300)
#endif


typedef struct
{
    char *adc_name;
    struct rt_adc_device hpm_adc_device;
    bool is_adc12;
    bool adc_enabled;
    uint32_t adc_base;
    rt_atomic_t enabled_channels;
}hpm_rtt_adc;

#if defined(ADC12_SOC_MAX_CH_NUM)
extern uint32_t rtt_board_init_adc12_clock(ADC12_Type *ptr, bool clk_src_ahb);
#endif
extern uint32_t rtt_board_init_adc16_clock(ADC16_Type *ptr, bool clk_src_ahb);

static uint32_t hpm_adc_init_clock(struct rt_adc_device *device);
static void hpm_adc_init_pins(struct rt_adc_device *device);
static bool hpm_adc_get_channel(const hpm_rtt_adc *adc, rt_int8_t channel, uint8_t *adc_chn);

static rt_err_t hpm_adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled);
static rt_err_t hpm_get_adc_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value);
static rt_uint8_t hpm_get_resolution(struct rt_adc_device *device);
static rt_int16_t hpm_get_vref(struct rt_adc_device *device);


static const struct rt_adc_ops hpm_adc_ops =
{
    .enabled = hpm_adc_enabled,
    .convert = hpm_get_adc_value,
    .get_resolution = hpm_get_resolution,
    .get_vref = hpm_get_vref,
};


static hpm_rtt_adc hpm_adc_config_tbl[] =
{
#ifdef BSP_USING_ADC0
    {
        .adc_name = "adc0",
#ifdef BSP_USING_ADC12
        .is_adc12 = true,
#else
        .is_adc12 = false,
#endif
        .adc_base = (uint32_t)HPM_ADC0,
    },
#endif

#ifdef BSP_USING_ADC1
    {
        .adc_name = "adc1",
#ifdef BSP_USING_ADC12
        .is_adc12 = true,
#else
        .is_adc12 = false,
#endif
        .adc_base = (uint32_t)HPM_ADC1,
    },
#endif

#ifdef BSP_USING_ADC2
    {
        .adc_name = "adc2",
#ifdef BSP_USING_ADC12
        .is_adc12 = true,
#else
        .is_adc12 = false,
#endif
        .adc_base = (uint32_t)HPM_ADC2,
    },
#endif

#ifdef BSP_USING_ADC3
    {
        .adc_name = "adc3",
        .is_adc12 = false,
        .adc_base = (uint32_t)HPM_ADC3,
    },
#endif
};

static uint8_t adc_nums = sizeof(hpm_adc_config_tbl) / sizeof(hpm_rtt_adc);


static bool hpm_adc_get_channel(const hpm_rtt_adc *adc, rt_int8_t channel, uint8_t *adc_chn)
{
    RT_ASSERT(adc_chn != RT_NULL);

#if HPM_ADC16_HAS_TEMP_SENSOR
    if (!adc->is_adc12 && channel == RT_ADC_INTERN_CH_TEMPER) {
        *adc_chn = ADC16_SOC_TEMP_CH_NUM;
        return true;
    }
#endif

    if (channel < 0) {
        return false;
    }

    *adc_chn = (uint8_t)channel;

    if (adc->is_adc12) {
#ifdef BSP_USING_ADC12
        return !ADC12_IS_CHANNEL_INVALID(*adc_chn);
#else
        return false;
#endif
    }

#ifdef BSP_USING_ADC16
    return !ADC16_IS_CHANNEL_INVALID(*adc_chn);
#else
    return false;
#endif
}


static uint32_t hpm_adc_init_clock(struct rt_adc_device *device)
{
    hpm_rtt_adc *hpm_adc;
    uint32_t clock_freq = 0;
    RT_ASSERT(device != RT_NULL);
    hpm_adc = (hpm_rtt_adc *)device->parent.user_data;

#if defined(ADC12_SOC_MAX_CH_NUM)
    if (hpm_adc->is_adc12)
    {
        clock_freq = rtt_board_init_adc12_clock((ADC12_Type *)hpm_adc->adc_base, true);
    } else
#endif
    {
        clock_freq = rtt_board_init_adc16_clock((ADC16_Type*)hpm_adc->adc_base,true);
    }
    return clock_freq;
}

static void hpm_adc_init_pins(struct rt_adc_device *device)
{
    hpm_rtt_adc *hpm_adc;
    RT_ASSERT(device != RT_NULL);
    hpm_adc = (hpm_rtt_adc *)device->parent.user_data;

#if defined(ADC12_SOC_MAX_CH_NUM)
    if (hpm_adc->is_adc12)
    {
        board_init_adc12_pins();
    } else
#endif
    {
        board_init_adc16_pins();
    }
}
static rt_err_t init_adc_config(hpm_rtt_adc *adc)
{
    hpm_stat_t ret;

    if (adc->is_adc12) {
#ifdef BSP_USING_ADC12
        adc12_config_t cfg;
        adc12_get_default_config(&cfg);
        cfg.res            = adc12_res_12_bits;
        cfg.conv_mode      = adc12_conv_mode_oneshot;
        cfg.adc_clk_div    = 3;
        cfg.wait_dis       = false;
        ret = adc12_init((ADC12_Type *)adc->adc_base, &cfg);
        if (ret != status_success) {
            return -RT_ERROR;
        }
#endif
    } else {
#ifdef BSP_USING_ADC16
        adc16_config_t cfg;

        adc16_get_default_config(&cfg);
        cfg.conv_mode      = adc16_conv_mode_oneshot;
        cfg.res            = adc16_res_16_bits;
        cfg.adc_clk_div    = 4;
#if !defined(HPM_IP_FEATURE_ADC16_FORCE_SYNC_AHB) || !HPM_IP_FEATURE_ADC16_FORCE_SYNC_AHB
        cfg.sel_sync_ahb   = true;
#endif
        cfg.wait_dis = 0;
        ret = adc16_init((ADC16_Type *)adc->adc_base, &cfg);
        if (ret != status_success) {
        return -RT_ERROR;
        }
#endif
#if defined(ADC_SOC_BUSMODE_ENABLE_CTRL_SUPPORT) && ADC_SOC_BUSMODE_ENABLE_CTRL_SUPPORT
    /* enable oneshot mode */
    adc16_enable_oneshot_mode((ADC16_Type *)adc->adc_base);
#endif
    }
    return RT_EOK;
}

static rt_err_t init_channel_config(hpm_rtt_adc *adc, uint16_t channel)
{
    hpm_stat_t ret;

    if (adc->is_adc12) {
#ifdef BSP_USING_ADC12
        adc12_channel_config_t ch_cfg;

        adc12_get_channel_default_config(&ch_cfg);
        ch_cfg.ch           = channel;
        ch_cfg.diff_sel     = adc12_sample_signal_single_ended;
        ch_cfg.sample_cycle = 20;

        ret = adc12_init_channel((ADC12_Type *)adc->adc_base, &ch_cfg);
        if (ret != status_success) {
            return -RT_ERROR;
        }
#endif
    } else {
#ifdef BSP_USING_ADC16
        adc16_channel_config_t ch_cfg;

        adc16_get_channel_default_config(&ch_cfg);
        ch_cfg.ch           = channel;
#if HPM_ADC16_HAS_TEMP_SENSOR
        if (channel == ADC16_SOC_TEMP_CH_NUM) {
            ch_cfg.sample_cycle = HPM_ADC16_TEMP_SAMPLE_CYCLE;
        } else
#endif
        {
            ch_cfg.sample_cycle = 20;
        }
        ret = adc16_init_channel((ADC16_Type *)adc->adc_base, &ch_cfg);
        if (ret != status_success) {
            return -RT_ERROR;
        }
#if HPM_ADC16_HAS_TEMP_SENSOR
        if (channel == ADC16_SOC_TEMP_CH_NUM) {
            adc16_enable_temp_sensor((ADC16_Type *)adc->adc_base);
        }
#endif
#endif
    }
    return RT_EOK;
}

static rt_err_t hpm_adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    hpm_rtt_adc *hpm_adc;
    rt_err_t ret = RT_EOK;
    rt_base_t critical_level;
    rt_atomic_t channel_mask;
    uint8_t adc_chn;

    RT_ASSERT(device != RT_NULL);
    hpm_adc = (hpm_rtt_adc *)device->parent.user_data;
    if (!hpm_adc_get_channel(hpm_adc, channel, &adc_chn)) {
        return -RT_EINVAL;
    }

    channel_mask = (rt_atomic_t)1U << adc_chn;
    critical_level = rt_enter_critical();
    if (enabled == RT_TRUE) {
        if ((rt_atomic_load(&hpm_adc->enabled_channels) & channel_mask) == 0)
        {
            if (!hpm_adc->adc_enabled)
            {
                hpm_adc_init_pins(device);
                (void)hpm_adc_init_clock(device);
                ret = init_adc_config(hpm_adc);
                if (ret != RT_EOK) {
                    goto exit;
                }
                hpm_adc->adc_enabled = true;
            }

            ret = init_channel_config(hpm_adc, adc_chn);
            if (ret != RT_EOK) {
                goto exit;
            }
            (void)rt_atomic_or(&hpm_adc->enabled_channels, channel_mask);
        }
    }
    else
    {
        /* The hardware has no per-channel disable in oneshot mode. */
#if HPM_ADC16_HAS_TEMP_SENSOR
        rt_atomic_t old_channels;

        old_channels = rt_atomic_and(&hpm_adc->enabled_channels, ~channel_mask);
        if (!hpm_adc->is_adc12 && adc_chn == ADC16_SOC_TEMP_CH_NUM
            && (old_channels & channel_mask) != 0) {
            adc16_disable_temp_sensor((ADC16_Type *)hpm_adc->adc_base);
        }
#else
        (void)rt_atomic_and(&hpm_adc->enabled_channels, ~channel_mask);
#endif
    }

exit:
    rt_exit_critical_safe(critical_level);
    return ret;
}

static rt_err_t hpm_get_adc_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    hpm_rtt_adc *hpm_adc;
    hpm_stat_t status;
    rt_uint16_t val;
    uint8_t adc_chn;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    hpm_adc = (hpm_rtt_adc *)device->parent.user_data;
    if (!hpm_adc_get_channel(hpm_adc, channel, &adc_chn)) {
        return -RT_EINVAL;
    }
    if ((rt_atomic_load(&hpm_adc->enabled_channels) & ((rt_atomic_t)1U << adc_chn)) == 0) {
        return -RT_EINVAL;
    }

    if (hpm_adc->is_adc12) {
#ifdef BSP_USING_ADC12
        status = adc12_get_oneshot_result((ADC12_Type *)hpm_adc->adc_base, adc_chn, &val);
#else
        return -RT_ENOSYS;
#endif
    } else {
#ifdef BSP_USING_ADC16
        status = adc16_get_oneshot_result((ADC16_Type *)hpm_adc->adc_base, adc_chn, &val);
#else
        return -RT_ENOSYS;
#endif
    }

    if (status != status_success) {
        return -RT_ERROR;
    }
    *value = val;

    return RT_EOK;
}

static rt_uint8_t hpm_get_resolution(struct rt_adc_device *device)
{
    hpm_rtt_adc *hpm_adc;

    RT_ASSERT(device != RT_NULL);
    hpm_adc = (hpm_rtt_adc *)device->parent.user_data;
    if (hpm_adc->is_adc12) {
        return 12;
    } else {
        return 16;
    }
}

static rt_int16_t hpm_get_vref(struct rt_adc_device *device)
{
    RT_UNUSED(device);

    return BOARD_ADC_VREF_MV;
}

int rt_hw_adc_init(void)
{
    rt_err_t ret = RT_EOK;

    for (uint32_t i = 0; i < adc_nums; i++) {
       ret = rt_hw_adc_register(&hpm_adc_config_tbl[i].hpm_adc_device,
                                hpm_adc_config_tbl[i].adc_name,
                                &hpm_adc_ops,
                                &hpm_adc_config_tbl[i]);
       if (ret != RT_EOK) {
           ret = -RT_ERROR;
           break;
       }
    }
    return ret;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
