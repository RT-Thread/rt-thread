/*
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-05     DongBowen    first version
 */

#include "board.h"

#include <rtthread.h>
#include <rtdevice.h>

#define LED_PIN                 GET_PIN(C, 13)
#define LED_PERIOD              (RT_TICK_PER_SECOND / 5)

#define KEY_PIN                 GET_PIN(B, 12)

void key_handle(void *args)
{
    rt_kprintf("key pressed!\n");
}

int main(void)
{
    rt_pin_mode(KEY_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(KEY_PIN, PIN_IRQ_MODE_FALLING, key_handle, RT_NULL);
    rt_pin_irq_enable(KEY_PIN, PIN_IRQ_ENABLE);

    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_delay(LED_PERIOD / 2);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_delay(LED_PERIOD / 2);
    };

}

