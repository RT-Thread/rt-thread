/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-30     crazt        first version
 * 2023-12-03     Meco Man     support nano version
 */

#include <board.h>
#include <rtthread.h>
#include <drv_gpio.h>
#ifndef RT_USING_NANO
#include <rtdevice.h>
#endif /* RT_USING_NANO */

/* defined the LED Blue pin: PH10 */
#define LED_B_PIN    GET_PIN(H, 10)

int main(void)
{
    int count = 1;
    /* set LED Blue pin mode to output */
    rt_pin_mode(LED_B_PIN, PIN_MODE_OUTPUT);

    while (count++)
    {
        rt_pin_write(LED_B_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_B_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
