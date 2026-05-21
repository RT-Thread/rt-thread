/*
 * Copyright (c) 2017-2019, MindMotion AE Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-13     henryhuang   first version
 */

#include <rtthread.h>
#include <rtdevice.h>


int main(void)
{
    while (1)
    {
        rt_thread_mdelay(500);       
    }

    return RT_EOK;
}
