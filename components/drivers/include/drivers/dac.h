/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
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

struct rt_dac_device;
struct rt_dac_ops
{
    rt_err_t (*disabled)(struct rt_dac_device *device, rt_uint32_t channel);
    rt_err_t (*enabled)(struct rt_dac_device *device, rt_uint32_t channel);
    rt_err_t (*convert)(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value);
};

struct rt_dac_device
{
    struct rt_device parent;
    const struct rt_dac_ops *ops;
};
typedef struct rt_dac_device *rt_dac_device_t;

typedef enum
{
    RT_DAC_CMD_ENABLE,
    RT_DAC_CMD_DISABLE,
} rt_dac_cmd_t;

rt_err_t rt_hw_dac_register(rt_dac_device_t dac,const char *name, const struct rt_dac_ops *ops, const void *user_data);

rt_uint32_t rt_dac_write(rt_dac_device_t dev, rt_uint32_t channel, rt_uint32_t value);
rt_err_t rt_dac_enable(rt_dac_device_t dev, rt_uint32_t channel);
rt_err_t rt_dac_disable(rt_dac_device_t dev, rt_uint32_t channel);

#endif /* __dac_H__ */
