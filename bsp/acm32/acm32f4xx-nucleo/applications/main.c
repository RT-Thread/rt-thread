/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-17     AisinoChip   the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include <drivers/dev_pin.h>

#define LED_PIN_NUM    83     /* PF3 */

int main(void)
{
    rt_pin_mode(LED_PIN_NUM, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED_PIN_NUM, PIN_LOW);
        rt_thread_delay(RT_TICK_PER_SECOND / 2);
        rt_pin_write(LED_PIN_NUM, PIN_HIGH);
        rt_thread_delay(RT_TICK_PER_SECOND / 2);
    }
}
