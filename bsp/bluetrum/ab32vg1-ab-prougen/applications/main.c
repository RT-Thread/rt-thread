/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/12/10     greedyhao    The first version
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
