/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-02-13     yeml   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED0 pin: PB1 */
//#define LED0_PIN    GET_PIN(B, 1)

int main(void)
{
    LL_GPIO_AF_Config(GPIOB, GPIO_PIN_4, GPIO_AF1_OUTPUT);
    while (1)
    {
        LL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
        rt_thread_mdelay(50);
    }

    return RT_EOK;
}
