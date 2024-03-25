/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 */

#include <rtthread.h>

#include <virtio_console.h>

static int console_init()
{
    rt_err_t status = RT_EOK;
    rt_device_t device = rt_device_find("virtio-console0");

    if (device != RT_NULL && rt_device_open(device, 0) == RT_EOK)
    {
        /* Create vport0p1 */
        status = rt_device_control(device, VIRTIO_DEVICE_CTRL_CONSOLE_PORT_CREATE, RT_NULL);
    }

    if (device != RT_NULL)
    {
        rt_device_close(device);
    }

    return status;
}
INIT_ENV_EXPORT(console_init);

static int console(int argc, char **argv)
{
    rt_err_t result = RT_EOK;

    if (argc > 1)
    {
        if (!rt_strcmp(argv[1], "set"))
        {
            rt_kprintf("console change to %s\n", argv[2]);
            rt_console_set_device(argv[2]);
        }
        else
        {
            rt_kprintf("Unknown command. Please enter 'console' for help\n");
            result = -RT_ERROR;
        }
    }
    else
    {
        rt_kprintf("Usage: \n");
        rt_kprintf("console set <name>   - change console by name\n");
        result = -RT_ERROR;
    }
    return result;
}
MSH_CMD_EXPORT(console, set console name);
