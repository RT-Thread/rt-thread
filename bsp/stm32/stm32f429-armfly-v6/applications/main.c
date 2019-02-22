/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-18     zylx         first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <drv_ext_io.h>

int main(void)
{
    int count = 1;

    HC574_SetPin(LED1,0);
    HC574_SetPin(LED2,0);   
    HC574_SetPin(LED3,0);
    HC574_SetPin(LED4,0);
    
    while (count++)
    {
        HC574_SetPin(LED1,1);
        rt_thread_mdelay(500);
        HC574_SetPin(LED1,0);
        rt_thread_mdelay(500);
    }
    
    return RT_EOK;
}
