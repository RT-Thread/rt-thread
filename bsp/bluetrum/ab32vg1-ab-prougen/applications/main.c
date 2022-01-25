/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/12/10     greedyhao    The first version
 */

/**
 * Notice!
 * All functions or data that are called during an interrupt need to be in RAM.
 * You can do it the way exception_isr() does.
 */

#include <rtthread.h>
#include "board.h"

int main(void)
{
    uint8_t pin = rt_pin_get("PE.1");

    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_kprintf("Hello, world\n");

    while (1)
    {
        rt_pin_write(pin, PIN_LOW);
        rt_thread_mdelay(500);
        rt_pin_write(pin, PIN_HIGH);
        rt_thread_mdelay(500);
    }
}
