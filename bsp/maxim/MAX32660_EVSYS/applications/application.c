/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-11     supperthomas first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "gpio.h"

const gpio_cfg_t led_pin[] =
{
    {PORT_0, PIN_13, GPIO_FUNC_OUT, GPIO_PAD_NONE},
};

int main(void)
{
    int count = 1;
    GPIO_Config(&led_pin[0]);
    GPIO_OutSet(&led_pin[0]);
    while (count++)
    {
        rt_thread_mdelay(500);
        GPIO_OutToggle(&led_pin[0]);
    }
    return RT_EOK;
}
