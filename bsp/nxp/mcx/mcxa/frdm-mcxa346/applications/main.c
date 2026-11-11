/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 * Copyright (c) 2019-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-24     Magicoe      first version
 * 2020-01-10     Kevin/Karl   Add PS demo
 * 2020-09-21     supperthomas fix the main.c
 * 2025-08-18     Alex Yang    Add P1_7 button with LED blink control
 *
 */

#include <rtdevice.h>
#include "drv_pin.h"

#define LED_PIN        ((3*32)+18)  /* Original LED pin */
#define BUTTON_PIN     ((1*32)+7)   /* P1_7 button pin */

static rt_bool_t led_state = RT_FALSE;        /* Current LED state */


/* Button interrupt callback function */
void button_irq_callback(void *args)
{
    rt_kprintf("SW2 pressed\n");
}

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

    rt_kprintf("FRDM-MCXA346\r\n");

    /* Configure LED pin as output */
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(LED_PIN, PIN_LOW);

    /* Configure button pin as input with pull-up */
    rt_pin_mode(BUTTON_PIN, PIN_MODE_INPUT_PULLUP);

    /* Attach interrupt to button pin */
    rt_pin_attach_irq(BUTTON_PIN, PIN_IRQ_MODE_FALLING, button_irq_callback, RT_NULL);
    rt_pin_irq_enable(BUTTON_PIN, PIN_IRQ_ENABLE);

    while (1)
    {
        /* Toggle LED state */
        led_state = !led_state;

        rt_pin_write(LED_PIN, led_state ? PIN_HIGH : PIN_LOW);

        rt_thread_mdelay(500);
    }
}
