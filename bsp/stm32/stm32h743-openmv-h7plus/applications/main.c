/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-14     supperthomas first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define LED1_PIN    GET_PIN(C, 0)

int main(void)
{
    /* set LED2 pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    #ifdef BSP_USING_USBD
        rt_console_set_device("vcom");
    #endif
    while (1)
    {
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(2000);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(2000);
    }
}
