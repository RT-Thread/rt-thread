/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-07     aozima       the first version
 * 2018-11-16     Ernest Chen  add finsh command and update adc function
 * 2022-05-11     Stanley Lwin add finsh voltage conversion command
 */

#ifndef __ADC_H__
#define __ADC_H__

#include <rtthread.h>

#define RT_ADC_INTERN_CH_TEMPER     (-1)
#define RT_ADC_INTERN_CH_VREF       (-2)
#define RT_ADC_INTERN_CH_VBAT       (-3)

struct rt_adc_device;
struct rt_adc_ops
{
    rt_err_t (*enabled)(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled);
    rt_err_t (*convert)(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value);
    rt_uint8_t (*get_resolution)(struct rt_adc_device *device);
    rt_int16_t (*get_vref) (struct rt_adc_device *device);
};

struct rt_adc_device
{
    struct rt_device parent;
    const struct rt_adc_ops *ops;
};
typedef struct rt_adc_device *rt_adc_device_t;

typedef enum
{
    RT_ADC_CMD_ENABLE = RT_DEVICE_CTRL_BASE(ADC) + 1,
    RT_ADC_CMD_DISABLE = RT_DEVICE_CTRL_BASE(ADC) + 2,
    RT_ADC_CMD_GET_RESOLUTION = RT_DEVICE_CTRL_BASE(ADC) + 3, /* get the resolution in bits */
    RT_ADC_CMD_GET_VREF = RT_DEVICE_CTRL_BASE(ADC) + 4, /* get reference voltage */
} rt_adc_cmd_t;

rt_err_t rt_hw_adc_register(rt_adc_device_t adc,const char *name, const struct rt_adc_ops *ops, const void *user_data);
rt_uint32_t rt_adc_read(rt_adc_device_t dev, rt_int8_t channel);
rt_err_t rt_adc_enable(rt_adc_device_t dev, rt_int8_t channel);
rt_err_t rt_adc_disable(rt_adc_device_t dev, rt_int8_t channel);
rt_int16_t rt_adc_voltage(rt_adc_device_t dev, rt_int8_t channel);

#endif /* __ADC_H__ */
