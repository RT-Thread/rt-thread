/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-19     thread-liu   the first version
 */

#ifndef __DAC_H__
#define __DAC_H__
#include <rtthread.h>
/**
 * @addtogroup  Drivers          RTTHREAD Driver
 * @defgroup    DAC           DAC
 *
 * @brief       DAC driver api
 *
 * <b>Example</b>
 * @code {.c}
 *
 * #include <rtthread.h>
 * #include <rtdevice.h>
 * #include <stdlib.h>
 * #define DAC_DEV_NAME        "dac1"
 * #define DAC_DEV_CHANNEL     1
 * #define REFER_VOLTAGE       330
 * #define CONVERT_BITS        (1 << 12)
 *
 * static int dac_vol_sample(int argc, char *argv[])
 * {
 *     rt_dac_device_t dac_dev;
 *     rt_uint32_t value, vol;
 *     rt_err_t ret = RT_EOK;
 *
 *     dac_dev = (rt_dac_device_t)rt_device_find(DAC_DEV_NAME);
 *     if (dac_dev == RT_NULL)
 *     {
 *         rt_kprintf("dac sample run failed! can't find %s device!\n", DAC_DEV_NAME);
 *         return -RT_ERROR;
 *     }
 *
 *     ret = rt_dac_enable(dac_dev, DAC_DEV_CHANNEL);
 *
 *     value = atoi(argv[1]);
 *     rt_dac_write(dac_dev, DAC_DEV_NAME, DAC_DEV_CHANNEL, value);
 *     rt_kprintf("the value is :%d \n", value);
 *
 *     vol = value * REFER_VOLTAGE / CONVERT_BITS;
 *     rt_kprintf("the voltage is :%d.%02d \n", vol / 100, vol % 100);
 *
 *     rt_thread_mdelay(500);
 *
 *     ret = rt_dac_disable(dac_dev, DAC_DEV_CHANNEL);
 *
 *     return ret;
 * }
 * MSH_CMD_EXPORT(dac_vol_sample, dac voltage convert sample);
 *
 * @endcode
 *
 * @ingroup Drivers
 */

/*!
 * @addtogroup DAC
 * @{
 */
struct rt_dac_device;
/**
 * @brief Configuration of DAC device
 */
struct rt_dac_ops
{
    rt_err_t (*disabled)(struct rt_dac_device *device, rt_uint32_t channel);
    rt_err_t (*enabled)(struct rt_dac_device *device, rt_uint32_t channel);
    rt_err_t (*convert)(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value);
    rt_uint8_t (*get_resolution)(struct rt_dac_device *device);
};
/**
 * @brief DAC device structure
 *
 */
struct rt_dac_device
{
    struct rt_device parent;
    const struct rt_dac_ops *ops;
};
typedef struct rt_dac_device *rt_dac_device_t;

typedef enum
{
    RT_DAC_CMD_ENABLE = RT_DEVICE_CTRL_BASE(DAC) + 0,
    RT_DAC_CMD_DISABLE = RT_DEVICE_CTRL_BASE(DAC) + 1,
    RT_DAC_CMD_GET_RESOLUTION = RT_DEVICE_CTRL_BASE(DAC) + 2,
} rt_dac_cmd_t;

/**
 * @brief Register a DAC device
 * @param dac DAC device
 * @param name DAC name
 * @param ops the operations of DAC device
 * @param user_data device private data
 * @return rt_err_t  error code
 */
rt_err_t rt_hw_dac_register(rt_dac_device_t dac,const char *name, const struct rt_dac_ops *ops, const void *user_data);

/**
 * @brief set the value of DAC
 * @param dev DAC device
 * @param channel DAC channel
 * @param value the value of DAC
 * @return rt_err_t  error code
 */
rt_err_t rt_dac_write(rt_dac_device_t dev, rt_uint32_t channel, rt_uint32_t value);

/**
 * @brief enable the DAC channel
 * @param dev DAC device
 * @param channel DAC channel
 * @return rt_err_t  error code
 */
rt_err_t rt_dac_enable(rt_dac_device_t dev, rt_uint32_t channel);

/**
 * @brief disable the DAC channel
 * @param dev DAC device
 * @param channel DAC channel
 * @return rt_err_t  error code
 */
rt_err_t rt_dac_disable(rt_dac_device_t dev, rt_uint32_t channel);

/*! @}*/

#endif /* __dac_H__ */
