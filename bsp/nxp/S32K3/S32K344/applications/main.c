/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-16     Pillar       first version
 */

#include <rtthread.h>
#include <board.h>

void led_thread(void *parameter)
{
    while (1)
    {
        Dio_WriteChannel(DioConf_DioChannel_LED, STD_HIGH);
        rt_thread_mdelay(500);
        Dio_WriteChannel(DioConf_DioChannel_LED, STD_LOW);
        rt_thread_mdelay(500);
    }
}

int main(void)
{
    rt_thread_t tid;
    tid = rt_thread_create("led", led_thread, RT_NULL, 512, 5, 10);
    if (tid != RT_NULL)
        rt_thread_startup(tid);
}
