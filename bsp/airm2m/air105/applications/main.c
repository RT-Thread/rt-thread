/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <air105_hal.h>

static uint8_t gMainWDTEnable;
int main(void)
{
    gMainWDTEnable = 1;
    while(1)
    {
        rt_thread_mdelay(12000);
        if (gMainWDTEnable)
        {
            WDT_Feed();
        }
    }
    return RT_EOK;
}
