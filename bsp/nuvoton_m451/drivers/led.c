/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-12-05     Pluto        first implementation
 */

#include "led.h"

/*
    LED: PC9 for M451 SDK
*/
#define LED_PORT PC
#define LED_DATA(dat) (PC9 = dat)
#define LED_BIT BIT9

/* Initial led gpio pin  */
int rt_hw_led_init(void)
{
    /* Configure the GPIO_LED pin */
    GPIO_SetMode(LED_PORT, LED_BIT, GPIO_MODE_OUTPUT);
    return 0;
}

void rt_hw_led_on(void)
{
    LED_DATA(0);
}

void rt_hw_led_off(void)
{
    LED_DATA(1);
}

/* Initial components for device */
INIT_DEVICE_EXPORT(rt_hw_led_init);
