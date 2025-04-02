/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-03     Hydevcode  the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "icm20608.h"

static void icm20608_entry(void *parameter)
{
    icm20608_device_t dev = RT_NULL;
    rt_int16_t x, y, z;
    rt_uint32_t i;

    const char *i2c_bus_name = "i2c2";
    int count = 0;

    rt_thread_mdelay(2000);

    dev = icm20608_init(i2c_bus_name);
    if (dev == RT_NULL)
    {
        rt_kprintf("The sensor initializes failure");
    }

    rt_kprintf("ICM20608 has been initialized!");

    while (1)
    {
        /* read the sensor digital output */
        icm20608_get_accel(dev, &x, &y, &z);

        rt_kprintf("accelerometer: X%6d    Y%6d    Z%6d\n", x, y, z);

        icm20608_get_gyro(dev, &x, &y, &z);

        rt_kprintf("gyroscope    : X%6d    Y%6d    Z%6d\n", x, y, z);

        rt_thread_mdelay(1000);
    }

}

int icm20608_thread_port(void)
{
    rt_thread_t res = rt_thread_create("icm20608", icm20608_entry, RT_NULL, 1024, 20, 50);
    if(res == RT_NULL)
    {
    rt_kprintf("icm20608 thread create failed!");
        return -RT_ERROR;
    }

    rt_thread_startup(res);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(icm20608_thread_port);