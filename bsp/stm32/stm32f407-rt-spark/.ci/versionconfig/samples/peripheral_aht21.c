/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-23     Wangyuqiang  the first version
 * 2024-04-03     Hydevcode
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "aht10.h"

static void aht10_entry(void *parameter)
{
    float humidity, temperature;
    aht10_device_t dev;

    const char *i2c_bus_name = "i2c3";
    int count = 0;

    rt_thread_mdelay(2000);

    dev = aht10_init(i2c_bus_name);
    if (dev == RT_NULL)
    {
        rt_kprintf("The sensor initializes failure");
    }

    rt_kprintf("AHT10 has been initialized!");

    while (1)
    {
        humidity = aht10_read_humidity(dev);
        rt_kprintf("Humidity   : %d.%d %%", (int)humidity, (int)(humidity * 10) % 10);

        temperature = aht10_read_temperature(dev);
        rt_kprintf("Temperature: %d.%d", (int)temperature, (int)(temperature * 10) % 10);

        rt_thread_mdelay(1000);
    }

}

int aht10_thread_port(void)
{
    rt_thread_t res = rt_thread_create("aht10", aht10_entry, RT_NULL, 1024, 20, 50);
    if(res == RT_NULL)
    {
    rt_kprintf("aht10 thread create failed!");
        return -RT_ERROR;
    }

    rt_thread_startup(res);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(aht10_thread_port);