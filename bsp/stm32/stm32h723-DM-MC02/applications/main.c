/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-05     whj4674672   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED0 pin: PB1 */
#define LED0_PIN    GET_PIN(B, 1)

int main(void)
{
    int count = 1;
    /* set LED0 pin mode to output */	
   
	
    while (count++)
    {
        
        rt_thread_mdelay(1000);
    }
    return RT_EOK;
}
