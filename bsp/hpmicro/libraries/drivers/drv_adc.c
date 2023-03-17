/*
 * Copyright (c) 2021 - 2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-08     hpmicro      the first version
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
    char *adc_name;
    struct rt_adc_device hpm_adc_device;
    uint16_t channel;
#ifdef BSP_USING_ADC12
    ADC12_Type *adc_base;
#endif
#ifdef BSP_USING_ADC16
    ADC16_Type *adc_base;
#endif
}hpm_rtt_adc;

static hpm_rtt_adc hpm_adc_config_tbl[] =
{
#ifdef BSP_USING_ADC0
    {
        .adc_name = "adc0",
#ifdef BSP_USING_ADC12
        .adc_base = HPM_ADC0,
#endif
#ifdef BSP_USING_ADC16
        .adc_base = HPM_ADC0,
#endif
    },
#endif

#ifdef BSP_USING_ADC1
    {
        .adc_name = "adc1",
#ifdef BSP_USING_ADC12
        .adc_base = HPM_ADC1,
#endif
#ifdef BSP_USING_ADC16
        .adc_base = HPM_ADC1,
#endif
    },
#endif

#ifdef BSP_USING_ADC2
    {
        .adc_name = "adc2",
#ifdef BSP_USING_ADC12
        .adc_base = HPM_ADC2,
#endif
#ifdef BSP_USING_ADC16
        .adc_base = HPM_ADC2,
#endif
    },
#endif

#ifdef BSP_USING_ADC3
    {
        .adc_name = "adc3",
#ifdef BSP_USING_ADC12
        .adc_base = HPM_ADC3,
#endif
#ifdef BSP_USING_ADC16
        .adc_base = HPM_ADC3,
#endif
    },
#endif
};

static uint8_t adc_nums = sizeof(hpm_adc_config_tbl) / sizeof(hpm_rtt_adc);

static rt_err_t init_adc_config(hpm_rtt_adc *adc)
{
#ifdef BSP_USING_ADC12
    adc12_config_t cfg;
    hpm_stat_t ret;

    adc12_get_default_config(&cfg);
    cfg.res            = adc12_res_12_bits;
    cfg.conv_mode      = adc12_conv_mode_oneshot;
    cfg.adc_clk_div    = 1;
    ret = adc12_init(adc->adc_base, &cfg);
    if (ret != status_success) {
        return -RT_ERROR;
    }
#endif

#ifdef BSP_USING_ADC16
    adc16_config_t cfg;
    hpm_stat_t ret;

    adc16_get_default_config(&cfg);
    cfg.conv_mode      = adc16_conv_mode_oneshot;
    cfg.adc_clk_div    = 3;
    cfg.sel_sync_ahb   = true;
    ret = adc16_init(adc->adc_base, &cfg);
    if (ret != status_success) {
       return -RT_ERROR;
    }
#endif
    return RT_EOK;
}

static rt_err_t init_channel_config(hpm_rtt_adc *adc)
{
#ifdef BSP_USING_ADC12
    adc12_channel_config_t ch_cfg;;
    hpm_stat_t ret;

    ch_cfg.ch           = adc->channel;
    ch_cfg.diff_sel     = adc12_sample_signal_single_ended;
    ch_cfg.sample_cycle = 20;

    ret = adc12_init_channel(adc->adc_base, &ch_cfg);
    if (ret != status_success) {
        return -RT_ERROR;
    }
#endif

#ifdef BSP_USING_ADC16

    adc16_channel_config_t ch_cfg;;
    hpm_stat_t ret;

    ch_cfg.ch           = adc->channel;
    ch_cfg.sample_cycle = 20;

    ret = adc16_init_channel(adc->adc_base, &ch_cfg);
    if (ret != status_success) {
        return -RT_ERROR;
    }
#endif
    return RT_EOK;
}

static rt_err_t hpm_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    hpm_rtt_adc *hpm_adc_handler;
    rt_err_t ret;

    RT_ASSERT(device != RT_NULL);
    hpm_adc_handler = (hpm_rtt_adc *)device->parent.user_data;
    ret = init_adc_config(hpm_adc_handler);
    if (ret != RT_EOK) {
        return -RT_ERROR;
    }
    hpm_adc_handler->channel = channel;
    ret = init_channel_config(hpm_adc_handler);
    if (ret != RT_EOK) {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t hpm_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    hpm_rtt_adc hpm_adc_handler;
    rt_err_t ret;
    rt_uint16_t val;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    hpm_adc_handler = *(hpm_rtt_adc *)device->parent.user_data;
    hpm_adc_handler.channel = channel;
#ifdef BSP_USING_ADC12
    adc12_get_oneshot_result(hpm_adc_handler.adc_base, hpm_adc_handler.channel, &val);
    *value = (val >> 4);
#endif

#ifdef BSP_USING_ADC16
    adc16_get_oneshot_result(hpm_adc_handler.adc_base, hpm_adc_handler.channel, &val);
    *value = val;
#endif

    return RT_EOK;
}

static const struct rt_adc_ops hpm_adc_ops =
{
    .enabled = hpm_adc_enabled,
    .convert = hpm_get_adc_value,
};

int rt_hw_adc_init(void)
{
    rt_err_t ret = RT_EOK;

    for (uint32_t i = 0; i < adc_nums; i++) {
       ret = rt_hw_adc_register(&hpm_adc_config_tbl[i].hpm_adc_device, hpm_adc_config_tbl[i].adc_name, &hpm_adc_ops, &hpm_adc_config_tbl[i]);
       if (ret != RT_EOK) {
           ret = -RT_ERROR;
           break;
       }
    }
    return ret;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif
