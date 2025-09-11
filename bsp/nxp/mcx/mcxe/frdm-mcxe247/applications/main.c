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
#include <rtthread.h>

#include "drv_pin.h"

#define LED_PIN ((2 * 32) + 13)          /* PTC13, RGB LED RED */
#define BTN_PIN ((2 * 32) + 10)          /* PTC10, SW3 (User) */

static rt_bool_t s_led_state = RT_FALSE; /* Current LED state */

static void app_btn_irq_callback(void *args)
{
    RT_UNUSED(args);

    rt_kprintf("SW3 pressed\n");
}

int main(void)
{
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(LED_PIN, PIN_LOW);

    rt_pin_mode(BTN_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(BTN_PIN, PIN_IRQ_MODE_FALLING, app_btn_irq_callback, RT_NULL);
    rt_pin_irq_enable(BTN_PIN, PIN_IRQ_ENABLE);

#if defined(__CC_ARM)
    rt_kprintf("using armcc, version: %d\n", __ARMCC_VERSION);
#elif defined(__clang__)
    rt_kprintf("using armclang, version: %d\n", __ARMCC_VERSION);
#elif defined(__ICCARM__)
    rt_kprintf("using iccarm, version: %d\n", __VER__);
#elif defined(__GNUC__)
    rt_kprintf("using gcc, version: %d.%d\n", __GNUC__, __GNUC_MINOR__);
#endif

    rt_kprintf("NXP MCXE247\r\n");

    while (1)
    {
        /* Toggle LED state */
        s_led_state = !s_led_state;
        rt_pin_write(LED_PIN, s_led_state ? PIN_HIGH : PIN_LOW);

        rt_thread_mdelay(500); /* Delay 500mS */
    }
}

// end file
