/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-14     Jonas        first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_gpio.h"

/* defined the LED pin: PB4 */
#define LED_PIN         GET_PIN(B,  4)
/* defined the KEY1 pin: PA1 */
#define KEY1_PIN        GET_PIN(A,  1)
/* defined the KEY WakeUp pin: PA0 */
#define WKUP_PIN        GET_PIN(A,  0)

void key_pressed_cb(void *arg)
{
    if (*(rt_base_t *)arg == KEY1_PIN)
    {
        rt_kprintf("key1 pressed\n");
    }
    if (*(rt_base_t *)arg == WKUP_PIN)
    {
        rt_kprintf("key wake up pressed\n");
    }
}

int main(void)
{
    static rt_base_t key1 = KEY1_PIN;
    static rt_base_t key_wkup = WKUP_PIN;
    uint32_t speed = 500;
    /* set LED5 pin mode to output */
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    /* set KEY pin mode to input */
    rt_pin_mode(KEY1_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(KEY1_PIN, PIN_IRQ_MODE_FALLING, key_pressed_cb, &key1);
    rt_pin_irq_enable(KEY1_PIN, PIN_IRQ_ENABLE);

    rt_pin_mode(WKUP_PIN, PIN_MODE_INPUT_PULLDOWN);
    rt_pin_attach_irq(WKUP_PIN, PIN_IRQ_MODE_RISING, key_pressed_cb, &key_wkup);
    rt_pin_irq_enable(WKUP_PIN, PIN_IRQ_ENABLE);

    while (1)
    {
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(speed);
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(speed);
    }
}
