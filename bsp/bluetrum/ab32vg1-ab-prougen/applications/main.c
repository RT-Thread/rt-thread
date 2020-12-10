/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/09/30     Bernard      The first version
 */

#include <rtthread.h>
#include "board.h"

int main(void)
{
    uint32_t cnt = 0;
    uint8_t pin = rt_pin_get("PE.1");

    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_kprintf("Hello, world\n");

    while (1)
    {
        if (cnt % 2 == 0) {
            rt_pin_write(pin, PIN_LOW);
        } else {
            rt_pin_write(pin, PIN_HIGH);
        }
        cnt++;
        rt_thread_mdelay(1000);
    }

    return 0;
}
