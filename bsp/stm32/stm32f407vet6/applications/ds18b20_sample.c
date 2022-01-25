/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-24     WillianChan    the first version
 * 2020-07-28     WillianChan    add the inclusion of the board.h
 */

#include <stdlib.h>
#include <rtthread.h>
#include "board.h"
#include "sensor.h"
#include "driver_ds18b20.h"

/* Modify this pin according to the actual wiring situation */
#define DS18B20_DATA_PIN    GET_PIN(B, 13)
#define DS18B20_VCC_PIN    GET_PIN(E, 15)
#define THREAD_PRIORITY			5
static void read_temp_entry(void *parameter)
{
    rt_device_t dev = RT_NULL;
    struct rt_sensor_data sensor_data;
    rt_size_t res;

    dev = rt_device_find(parameter);
    if (dev == RT_NULL)
    {
        rt_kprintf("Can't find device:%s\n", parameter);
        return;
    }

    if (rt_device_open(dev, RT_DEVICE_FLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("open device failed!\n");
        return;
    }
    rt_device_control(dev, RT_SENSOR_CTRL_SET_ODR, (void *)100);

    while (1)
    {
        res = rt_device_read(dev, 0, &sensor_data, 1);
        if (res != 1)
        {
            rt_kprintf("read data failed!size is %d\n", res);
            rt_device_close(dev);
            return;
        }
        else
        {
            if (sensor_data.data.temp >= 0)
            {
                rt_kprintf("temp:%3d.%dC, timestamp:%5d\n",
                           sensor_data.data.temp / 10,
                           sensor_data.data.temp % 10,
                           sensor_data.timestamp);
            }
            else
            {
                rt_kprintf("temp:-%2d.%dC, timestamp:%5d\n",
                           abs(sensor_data.data.temp / 10),
                           abs(sensor_data.data.temp % 10),
                           sensor_data.timestamp);
            }
        }
        rt_thread_mdelay(100);
    }
}

static int ds18b20_read_temp_sample(void)
{
    rt_thread_t ds18b20_thread;

    ds18b20_thread = rt_thread_create("18b20tem",
                                      read_temp_entry,
                                      "temp_ds18b20",
                                      1024,
                                      THREAD_PRIORITY,
                                      20);
    if (ds18b20_thread != RT_NULL)
    {
        rt_thread_startup(ds18b20_thread);
    }

    return RT_EOK;
}
MSH_CMD_EXPORT(ds18b20_read_temp_sample,ds18b20_read_temp_sample);

static int rt_hw_ds18b20_port(void)
{
    struct rt_sensor_config cfg;
    rt_pin_mode(DS18B20_VCC_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(DS18B20_VCC_PIN, PIN_HIGH);	
//     rt_pin_write(DS18B20_VCC_PIN, PIN_LOW);   
    cfg.intf.user_data = (void *)DS18B20_DATA_PIN;
    rt_hw_ds18b20_init("ds18b20", &cfg);
    
    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_ds18b20_port);
