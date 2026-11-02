/*
 * Copyright (C) 2022-2026, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-03     CDT          first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <tca9539_port.h>

int main(void)
{
    /* set LED_BLUE_PIN pin mode to output */
    TCA9539_ConfigPin(LED_BLUE_PORT, LED_BLUE_PIN, TCA9539_DIR_OUT);

    while (1)
    {
        TCA9539_WritePin(LED_BLUE_PORT, LED_BLUE_PIN, TCA9539_PIN_SET);
        rt_thread_mdelay(500);
        TCA9539_WritePin(LED_BLUE_PORT, LED_BLUE_PIN, TCA9539_PIN_RESET);
        rt_thread_mdelay(500);
    }
}
