/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-19     Quintin.Z    the first version
 */

#include <stdio.h>
#include <rthw.h>
#include <rtdevice.h>
#include "board.h"
#include <rtthread.h>

#include "gpio.h"


void led_thread_entry(void* parameter)
{

    GPIO_Init  (GPIOA, GPIO_PTB5_MASK, GPIO_PinOutput);

    while(1)
    {
        GPIO_Toggle  (GPIOA, GPIO_PTB5_MASK);
        rt_thread_delay(RT_TICK_PER_SECOND / 10);

    }
}
