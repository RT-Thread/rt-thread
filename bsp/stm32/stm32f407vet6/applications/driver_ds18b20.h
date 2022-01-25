/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2019-07-15     WillianChan     the first version.
 *
 */

#ifndef __DS18B20_H__
#define __DS18B20_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "sensor.h"
#include <stdint.h>
#define CONNECT_SUCCESS  0
#define CONNECT_FAILED   1

struct ds18b20_device
{
    rt_base_t pin;
    rt_mutex_t lock;
};
typedef struct ds18b20_device *ds18b20_device_t;

uint8_t ds18b20_init(rt_base_t pin);
int32_t ds18b20_get_temperature(rt_base_t pin);
int rt_hw_ds18b20_init(const char *name, struct rt_sensor_config *cfg);

#endif /* __DS18B20_H_ */


