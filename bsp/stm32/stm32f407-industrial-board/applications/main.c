/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-5-26      hywing       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED1 pin: PC1 */
#define LED1_PIN    GET_PIN(F, 10)
/* defined the LED2 pin: PC0 */
#define LED2_PIN    GET_PIN(F, 9)

#define KEY0_PIN        GET_PIN(A, 0)
#define KEY1_PIN        GET_PIN(E, 4)
#define KEY_DEBOUNCE_MS 200

static rt_tick_t key0_last_tick = 0;
static rt_tick_t key1_last_tick = 0;

static void key0_irq_callback(void *arg)
{
    RT_UNUSED(arg);

    if (rt_tick_get() - key0_last_tick < rt_tick_from_millisecond(KEY_DEBOUNCE_MS))
    {
        return;
    }

    if (rt_pin_read(KEY0_PIN) == PIN_HIGH)
    {
        key0_last_tick = rt_tick_get();
        rt_kprintf("KEY0 pressed!\r\n");
    }
}

static void key1_irq_callback(void *arg)
{
    RT_UNUSED(arg);

    if (rt_tick_get() - key1_last_tick < rt_tick_from_millisecond(KEY_DEBOUNCE_MS))
    {
        return;
    }

    if (rt_pin_read(KEY1_PIN) == PIN_LOW)
    {
        key1_last_tick = rt_tick_get();
        rt_kprintf("KEY1 pressed!\r\n");
    }
}

int main(void)
{
    /* set LED pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);

    /* KEY0: pull-down + rising edge; KEY1: pull-up + falling edge (active low) */
    rt_pin_attach_irq(KEY0_PIN, PIN_IRQ_MODE_RISING, key0_irq_callback, RT_NULL);
    rt_pin_attach_irq(KEY1_PIN, PIN_IRQ_MODE_FALLING, key1_irq_callback, RT_NULL);
    rt_pin_irq_enable(KEY0_PIN, PIN_IRQ_ENABLE);
    rt_pin_irq_enable(KEY1_PIN, PIN_IRQ_ENABLE);

    rt_kprintf("Hello RT-Thread!\r\n");

    while (1)
    {
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(250);
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_thread_mdelay(250);
    }

    return RT_EOK;
}
