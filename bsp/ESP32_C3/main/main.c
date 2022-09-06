/*
 * Copyright (c) 2021-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-24     supperthomas first version
 * 2022-06-02     supperthomas fix version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

int rtt_main(void)
{
    /* show RT-Thread version */
    rt_show_version();
    rt_kprintf("Hello!RT-THREAD!\r\n");
    rt_pin_mode(RT_BSP_LED_PIN, PIN_MODE_OUTPUT);
    while (1)
    {
        rt_pin_write(RT_BSP_LED_PIN, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(RT_BSP_LED_PIN, PIN_LOW);
        rt_thread_mdelay(1000);
    }
}
