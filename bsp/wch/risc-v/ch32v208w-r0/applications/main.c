/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-03     WangShun       first version
 */

#include "ch32v20x.h"
#include <rtthread.h>
#include <rthw.h>
#include "drivers/dev_pin.h"
#include <board.h>

#define LED0 rt_pin_get("PA.0")

int main(void)
{
    rt_pin_mode(LED0,PIN_MODE_OUTPUT);
    rt_kprintf("MCU-CH32V208WBU6\r\n");
    while(1)
    {
        rt_pin_write(LED0, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
