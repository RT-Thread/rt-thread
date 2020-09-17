/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-17     maoxiaochuan    first version
 */


#include <rtthread.h>

static void reboot()
{
    rt_hw_cpu_reset();
}
MSH_CMD_EXPORT(reboot, reboot system);


static void poweroff()
{
    rt_hw_cpu_shutdown();
}
MSH_CMD_EXPORT(poweroff, shutdown system);

