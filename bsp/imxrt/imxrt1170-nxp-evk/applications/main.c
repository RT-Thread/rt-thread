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
#include "drv_gpio.h"

int main(void)
{
    while (1)
    {
      rt_kprintf("test\r\n");
      rt_thread_mdelay(500);
    }
}

