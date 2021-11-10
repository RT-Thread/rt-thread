/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-19     Mr.Tiger     first version
 */

#ifndef __ADC_CONFIG_H__
#define __ADC_CONFIG_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "hal_data.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_ADC0) || defined(BSP_USING_ADC1)
struct ra_adc_map
{
    char name;
    const adc_cfg_t *g_cfg;
    const adc_instance_ctrl_t *g_ctrl;
    const adc_channel_cfg_t   *g_channel_cfg;
};

struct ra_dev
{
    rt_adc_device_t     ra_adc_device_t;
    struct ra_adc_map  *ra_adc_dev;
};
#endif
#endif

#ifdef __cplusplus
}
#endif

