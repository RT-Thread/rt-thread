/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED1 pin: PB0 */
#define LED1_PIN    GET_PIN(B, 0)
/* defined the LED2 pin: PB7 */
#define LED2_PIN    GET_PIN(B, 7)
/* defined the LED3 pin: PB14 */
#define LED3_PIN    GET_PIN(B, 14)
/* defined the USER KEY pin: PC13 */
#define KEY_PIN    GET_PIN(C, 13)

int main(void)
{
    int count = 1;
	/* set LED1 pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    /* set LED2 pin mode to output */
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
	/* set LED3 pin mode to output */
    rt_pin_mode(LED3_PIN, PIN_MODE_OUTPUT);
	/* set USER KEY pin mode to input */
    rt_pin_mode(KEY_PIN, PIN_MODE_INPUT_PULLDOWN);

    while (count++)
    {
		if(rt_pin_read(KEY_PIN))
		{
			rt_pin_write(LED1_PIN, PIN_HIGH);
			rt_pin_write(LED2_PIN, PIN_LOW);
			rt_pin_write(LED3_PIN, PIN_LOW);
			rt_thread_mdelay(500);
			rt_pin_write(LED1_PIN, PIN_LOW);
			rt_pin_write(LED2_PIN, PIN_HIGH);
			rt_pin_write(LED3_PIN, PIN_LOW);
			rt_thread_mdelay(500);
			rt_pin_write(LED1_PIN, PIN_LOW);
			rt_pin_write(LED2_PIN, PIN_LOW);
			rt_pin_write(LED3_PIN, PIN_HIGH);
			rt_thread_mdelay(500);
		}
		else
		{
			rt_pin_write(LED1_PIN, PIN_LOW);
			rt_pin_write(LED2_PIN, PIN_LOW);
			rt_pin_write(LED3_PIN, PIN_LOW);
		}
    }

    return RT_EOK;
}
