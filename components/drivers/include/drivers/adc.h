/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
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
/**
 * @addtogroup  Drivers          RTTHREAD Driver
 * @defgroup    ADC           ADC
 *
 * @brief       ADC driver api
 *
 * <b>Example</b>
 * @code {.c}
 * #define ADC_DEV_NAME        "adc1"
 * #define ADC_DEV_CHANNEL     5
 * #define REFER_VOLTAGE       330
 * #define CONVERT_BITS        (1 << 12)
 *
 * static int adc_vol_sample(int argc, char *argv[])
 * {
 *     rt_adc_device_t adc_dev;
 *     rt_uint32_t value, vol;
 *
 *     rt_err_t ret = RT_EOK;
 *
 *     adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
 *     if (adc_dev == RT_NULL)
 *     {
 *         rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
 *         return -RT_ERROR;
 *     }
 *
 *     ret = rt_adc_enable(adc_dev, ADC_DEV_CHANNEL);
 *
 *     value = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
 *     rt_kprintf("the value is :%d \n", value);
 *
 *     vol = value * REFER_VOLTAGE / CONVERT_BITS;
 *     rt_kprintf("the voltage is :%d.%02d \n", vol / 100, vol % 100);
 *
 *     ret = rt_adc_disable(adc_dev, ADC_DEV_CHANNEL);
 *
 *     return ret;
 * }
 * MSH_CMD_EXPORT(adc_vol_sample, adc voltage convert sample);
 *
 * @endcode
 *
 * @ingroup     Drivers
 */


/*!
 * @addtogroup ADC
 * @{
 */
#define RT_ADC_INTERN_CH_TEMPER     (-1)
#define RT_ADC_INTERN_CH_VREF       (-2)
#define RT_ADC_INTERN_CH_VBAT       (-3)

struct rt_adc_device;
/**
 * @brief Configure the adc device
 */
struct rt_adc_ops
{
    rt_err_t (*enabled)(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled);
    rt_err_t (*convert)(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value);
    rt_uint8_t (*get_resolution)(struct rt_adc_device *device);
    rt_int16_t (*get_vref) (struct rt_adc_device *device);
};
/**
 * @brief adc device
 */
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

/**
 * @brief register the adc device
 * @param adc adc device
 * @param name device name
 * @param ops device ops
 * @param user_data device private data
 * @return rt_err_t        error code
 * @ingroup  ADC
 */
rt_err_t rt_hw_adc_register(rt_adc_device_t adc,const char *name, const struct rt_adc_ops *ops, const void *user_data);

/**
 * @brief read the adc value
 * @param dev adc device
 * @param channel adc channel
 * @return rt_uint32_t adc value
 * @ingroup  ADC
 */
rt_uint32_t rt_adc_read(rt_adc_device_t dev, rt_int8_t channel);

/**
 * @brief enable the adc channel
 * @param dev adc device
 * @param channel adc channel
 * @return rt_err_t error code
 * @ingroup  ADC
 */
rt_err_t rt_adc_enable(rt_adc_device_t dev, rt_int8_t channel);

/**
 * @brief disable the adc channel
 * @param dev adc device
 * @param channel adc channel
 * @return rt_err_t error code
 * @ingroup  ADC
 */
rt_err_t rt_adc_disable(rt_adc_device_t dev, rt_int8_t channel);

/**
 * @brief get the adc resolution
 * @param dev adc device
 * @param channel adc channel
 * @return rt_int16_t adc resolution
 * @ingroup  ADC
 */
rt_int16_t rt_adc_voltage(rt_adc_device_t dev, rt_int8_t channel);

/*! @}*/

#endif /* __ADC_H__ */
