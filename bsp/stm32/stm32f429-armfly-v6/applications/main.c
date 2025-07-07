/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-18     zylx         first version
 */

#include <rtthread.h>
#ifndef RT_USING_NANO
#include <rtdevice.h>
#endif
#include <board.h>
#include <drv_ext_io.h>

int main(void)
{
#ifndef RT_USING_NANO
    HC574_SetPin(LED1,0);
    HC574_SetPin(LED2,0);
    HC574_SetPin(LED3,0);
    HC574_SetPin(LED4,0);

    while (1)
    {
        HC574_SetPin(LED1,1);
        rt_thread_mdelay(500);
        HC574_SetPin(LED1,0);
        rt_thread_mdelay(500);
    }
#else
#define LED_PB_8 GET_PIN(B, 8)
    rt_pin_mode(LED_PB_8, PIN_MODE_OUTPUT);
    while (1)
    {
        rt_pin_write(LED_PB_8, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PB_8, PIN_LOW);
        rt_thread_mdelay(500);
    }
#endif
}
