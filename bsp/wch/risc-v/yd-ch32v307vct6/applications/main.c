/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-06     GSunwinder   first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "ch32v30x.h"
#include "board.h"

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */

int main(void)
{
    printf("SystemClk: %d Hz\r\n", SystemCoreClock);

    rt_pin_mode(LED_BLUE, PIN_MODE_OUTPUT);
    rt_pin_mode(LED_RED,  PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED_RED,  PIN_LOW);
        rt_pin_write(LED_BLUE, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(LED_RED,  PIN_HIGH);
        rt_pin_write(LED_BLUE, PIN_LOW);
        rt_thread_mdelay(1000);
    }
}
