/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-06     tyustli      first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_gpio.h>
#include <fsl_rgpio.h>

static rt_err_t _print_device(rt_object_t object, void *data)
{
    rt_kprintf("  %s\r\n", object->name);
    return RT_EOK;
}

static void print_devices(void)
{
    rt_kprintf("device list:\r\n");
    rt_object_for_each(RT_Object_Class_Device, _print_device, RT_NULL);
}

int main(void)
{
    rt_kprintf("MIMXRT1180_CM33 Hello_World\r\n");
    print_devices();

    while (1)
    {
        rt_thread_mdelay(500);
    }
}
