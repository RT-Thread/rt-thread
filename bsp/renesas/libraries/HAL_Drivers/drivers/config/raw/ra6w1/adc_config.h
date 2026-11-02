/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-29     rcitach      first version
 */

#ifndef __ADC_CONFIG_H__
#define __ADC_CONFIG_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "hal_data.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_ADC)

#ifndef BSP_USING_ADC0
#define BSP_USING_ADC0
#endif

struct rt_adc_dev
{
    struct rt_adc_ops ops;
    struct rt_adc_device adc_device;
};

struct ra_adc_map
{
    const char *device_name;
    const adc_cfg_t *g_cfg;
    const adc_ctrl_t *g_ctrl;
    const void *g_channel_cfg;
};
#endif

#ifdef __cplusplus
}
#endif

#endif /* __ADC_CONFIG_H__ */
