/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-11-23     Bright      first implementation
 */

#include "led.h"

/*
    LED: P3.6
*/
#define LED_PORT P3
#define LED_DATA(dat) (P36 = dat)
#define LED_BIT BIT6

/* Initial led gpio pin  */
int rt_hw_led_init(void)
{
    /* Configure the GPIO_LED pin */
    GPIO_SetMode(LED_PORT, LED_BIT, GPIO_PMD_OUTPUT);
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
