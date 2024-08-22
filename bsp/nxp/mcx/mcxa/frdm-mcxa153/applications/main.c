/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 * Copyright (c) 2019-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-24     Magicoe      first version
 * 2020-01-10     Kevin/Karl   Add PS demo
 * 2020-09-21     supperthomas fix the main.c
 *
 */
#include <rtdevice.h>
#include "drv_pin.h"

#define LED_PIN        ((3*32)+12)

int main(void)
{
#if defined(__CC_ARM)
    rt_kprintf("using armcc, version: %d\n", __ARMCC_VERSION);
#elif defined(__clang__)
    rt_kprintf("using armclang, version: %d\n", __ARMCC_VERSION);
#elif defined(__ICCARM__)
    rt_kprintf("using iccarm, version: %d\n", __VER__);
#elif defined(__GNUC__)
    rt_kprintf("using gcc, version: %d.%d\n", __GNUC__, __GNUC_MINOR__);
#endif

    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);  /* Set GPIO as Output */
    rt_kprintf("MCXA153 HelloWorld\n");

    while (1)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);    /* Set GPIO output 1 */
        rt_thread_mdelay(500);               /* Delay 500mS */
        rt_pin_write(LED_PIN, PIN_LOW);     /* Set GPIO output 0 */
        rt_thread_mdelay(500);               /* Delay 500mS */
    }
}
