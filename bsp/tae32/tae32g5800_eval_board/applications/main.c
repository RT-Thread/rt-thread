/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-03-04     yeml   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

int main(void)
{
	rt_base_t LED1_PIN = 0;
	LED1_PIN = rt_pin_get("PB.6");
	rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
	while (1)
	{
		rt_pin_write(LED1_PIN, PIN_HIGH);
		rt_thread_mdelay(500);
		rt_pin_write(LED1_PIN, PIN_LOW);
		rt_thread_mdelay(500);
	}
}



 