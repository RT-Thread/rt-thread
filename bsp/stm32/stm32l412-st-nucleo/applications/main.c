/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-24     luhuadong    first version
 * 2023-12-03     Meco Man     support nano version
 */

#include <board.h>
#include <rtthread.h>
#include <drv_gpio.h>
#ifndef RT_USING_NANO
#include <rtdevice.h>
#endif /* RT_USING_NANO */

/* defined the LD4 pin: PB13 */
#define LD4_PIN    GET_PIN(B, 13)

int main(void)
{
    /* set LD4 pin mode to output */
    rt_pin_mode(LD4_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LD4_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LD4_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
