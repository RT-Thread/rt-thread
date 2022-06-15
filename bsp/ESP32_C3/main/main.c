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
#define BLINK_GPIO 12
    rt_pin_mode(BLINK_GPIO, PIN_MODE_OUTPUT);
    while (1)
    {
        printf("Hello!RT-THREAD!\r\n");
        rt_pin_write(BLINK_GPIO, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(BLINK_GPIO, PIN_LOW);
        rt_thread_mdelay(1000);
    }
}
