/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     misonyo   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <air105_hal.h>

/* defined the LED0 pin: PD14 */
#define LED0_PIN    GPIOD_14
static uint8_t gMainWDTEnable;
int main(void)
{
	gMainWDTEnable = 1;
	while(1)
	{
//		GPIO_Output(LED0_PIN, 1);
//		rt_thread_mdelay(500);
//		GPIO_Output(LED0_PIN, 0);
		rt_thread_mdelay(12000);
		if (gMainWDTEnable)
		{
			WDT_Feed();
		}
	}
    return RT_EOK;
}
