/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 */

#ifndef __DRV_ADC__
#define __DRV_ADC__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

struct n32_adc_config
{
    const char *name;
    ADC_Module* adc_periph;
};

struct n32_adc
{
    struct rt_adc_device adc_device;
    struct n32_adc_config *config;
};

int rt_hw_adc_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_ADC__ */
