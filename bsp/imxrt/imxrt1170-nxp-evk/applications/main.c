/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-06     tyustli      first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_gpio.h>
#include <fsl_gpio.h>

#define EXAMPLE_LED_GPIO     GPIO9
#define EXAMPLE_LED_GPIO_PIN   (3U)
#define EXAMPLE_LED_GPIO_PORT  (3U)
#define LED_PIN GET_PIN(EXAMPLE_LED_GPIO_PORT, EXAMPLE_LED_GPIO_PIN)
int main(void)
{
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
    while (1)
    {
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
    }
}
