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


typedef struct
{
    bool enabled;
} adc_channel_state_t;

typedef struct
{
    char *adc_name;
    struct rt_adc_device hpm_adc_device;
    bool is_adc12;
    bool adc_enabled;
    uint32_t adc_base;
    adc_channel_state_t chn_state[16];
}hpm_rtt_adc;



static uint32_t hpm_adc_init_clock(struct rt_adc_device *device);

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


static uint32_t hpm_adc_init_clock(struct rt_adc_device *device)
{
    hpm_rtt_adc *hpm_adc;
    uint32_t clock_freq = 0;
    RT_ASSERT(device != RT_NULL);
    hpm_adc = (hpm_rtt_adc *)device->parent.user_data;

#if defined(ADC12_SOC_MAX_CH_NUM)
    if (hpm_adc->is_adc12)
    {
        clock_freq = board_init_adc12_clock((ADC12_Type*)hpm_adc->adc_base);
    } else
#endif
    {
        clock_freq = board_init_adc16_clock((ADC16_Type*)hpm_adc->adc_base);
    }
    return clock_freq;
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
        cfg.adc_ahb_en     = true;
        cfg.adc_clk_div    = 3;
        ret = adc12_init((ADC12_Type *)adc->adc_base, &cfg);
        if (ret != status_success) {
            return RT_ERROR;
        }
#endif
    } else {
#ifdef BSP_USING_ADC16
        adc16_config_t cfg;

        adc16_get_default_config(&cfg);
        cfg.conv_mode      = adc16_conv_mode_oneshot;
        cfg.res            = adc16_res_16_bits;
        cfg.adc_clk_div    = 4;
        cfg.sel_sync_ahb   = true;
        cfg.adc_ahb_en     = true;
        cfg.wait_dis = 0;
        ret = adc16_init((ADC16_Type *)adc->adc_base, &cfg);
        if (ret != status_success) {
        return RT_ERROR;
        }
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
        ch_cfg.ch           = adc->channel;
        ch_cfg.diff_sel     = adc12_sample_signal_single_ended;
        ch_cfg.sample_cycle = 20;

        ret = adc12_init_channel((ADC12_Type *)adc->adc_base, &ch_cfg);
        if (ret != status_success) {
            return RT_ERROR;
        }
#endif
    } else {
#ifdef BSP_USING_ADC16
        adc16_channel_config_t ch_cfg;

        adc16_get_channel_default_config(&ch_cfg);
        ch_cfg.ch           = channel;
        ch_cfg.sample_cycle = 20;
        ret = adc16_init_channel((ADC16_Type *)adc->adc_base, &ch_cfg);
        if (ret != status_success) {
            return RT_ERROR;
        }
#endif
    }
    return RT_EOK;
}

static rt_err_t hpm_adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    hpm_rtt_adc *hpm_adc;
    rt_err_t ret;

    RT_ASSERT(device != RT_NULL);
    hpm_adc = (hpm_rtt_adc *)device->parent.user_data;
    if (enabled == RT_TRUE) {
        if (!hpm_adc->chn_state[channel].enabled)
        {
            if (!hpm_adc->adc_enabled)
            {
                (void)hpm_adc_init_clock(device);
                ret = init_adc_config(hpm_adc);
                if (ret != RT_EOK) {
                    return RT_ERROR;
                }
                hpm_adc->adc_enabled = true;
            }
            hpm_adc->chn_state[channel].enabled = true;

            ret = init_channel_config(hpm_adc, channel);
            if (ret != RT_EOK) {
                return RT_ERROR;
            }
        }
    }
    else
    {
        /* Since the ADC channel cannot be truly disabled, do nothing here */
    }

    return RT_EOK;
}

static rt_err_t hpm_get_adc_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    hpm_rtt_adc *hpm_adc;
    rt_err_t ret;
    rt_uint16_t val;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    hpm_adc = (hpm_rtt_adc *)device->parent.user_data;
    uint32_t adc_chn = (uint16_t)channel;
    if (hpm_adc->is_adc12) {
#ifdef BSP_USING_ADC12
        adc12_get_oneshot_result((ADC12_Type *)hpm_adc->adc_base, adc_chn, &val);
        *value = val;
#endif
    } else {
#ifdef BSP_USING_ADC16
        hpm_stat_t status = adc16_get_oneshot_result((ADC16_Type *)hpm_adc->adc_base, adc_chn, &val);
        *value = val;
       // rt_kprintf("%s, status=%d\n", __func__, status);
#endif
    }

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
    return -RT_EIO;
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
           ret = RT_ERROR;
           break;
       }
    }
    return ret;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
