/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-25     hywing       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define LED0_PIN    GET_PIN(B, 0)
#define LED1_PIN    GET_PIN(E, 1)
#define LED2_PIN    GET_PIN(B, 14)
#define USER_KEY    GET_PIN(C, 13)
#define DELAY       500

void irq_callback(void *arg)
{
    if(rt_pin_read(USER_KEY) == 1)
    {
        rt_kprintf("Key pressed!\r\n");
    }
}

int main(void)
{
    /* set GPIO pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(USER_KEY, PIN_MODE_INPUT_PULLDOWN);
    rt_pin_attach_irq(USER_KEY, PIN_IRQ_MODE_RISING, irq_callback, RT_NULL);
    rt_pin_irq_enable(USER_KEY, PIN_IRQ_ENABLE);

    rt_kprintf("Welcome to the world of IoT Stuff!\r\n");

    while (1)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_thread_mdelay(DELAY);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_thread_mdelay(DELAY);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(DELAY);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_thread_mdelay(DELAY);
    }
}
