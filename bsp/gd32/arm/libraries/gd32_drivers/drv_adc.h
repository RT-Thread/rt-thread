/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-03     BruceOu      first implementation
 */

#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#include <rthw.h>
#include <rtthread.h>
#include <board.h>
#include "drv_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* gd32 adc dirver class */
struct gd32_adc
{
    uint32_t adc_periph;
    rcu_periph_enum adc_clk;
    rt_base_t adc_pins[16];
    struct rt_adc_device *adc;
    char *device_name;
};

#ifdef __cplusplus
}
#endif

#endif /* __DRV_ADC_H__ */
