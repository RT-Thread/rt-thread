/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-04     Chushicheng  first version
 */

#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#include <rtdevice.h>
#ifdef BSP_USING_ADC

/* pico adc dirver class */
struct pico_adc
{
    struct rt_adc_ops ops;
    struct rt_adc_device pico_adc_device;
};

/* pico config class */
struct pico_adc_config
{
    rt_uint8_t pin;
    rt_uint8_t channel;
    const char *device_name;
};

#ifdef BSP_USING_ADC0
#define ADC0_CONFIG                                      \
    {                                                    \
        .pin = 26,                                       \
        .channel = 0,                                    \
        .device_name = "adc0",                           \
    }
#endif
#ifdef BSP_USING_ADC1
#define ADC1_CONFIG                                      \
    {                                                    \
        .pin = 27,                                       \
        .channel = 1,                                    \
        .device_name = "adc1",                           \
    }
#endif
#ifdef BSP_USING_ADC2
#define ADC2_CONFIG                                      \
    {                                                    \
        .pin = 28,                                       \
        .channel = 2,                                    \
        .device_name = "adc2",                           \
    }
#endif

int rt_hw_adc_init(void);

#endif /* BSP_USING_ADC */
#endif /* __DRV_ADC_H__ */
