/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-10     Sherman       first version
 */
#include <rtthread.h>
#include "hal_data.h"
#include <rtdevice.h>

#define LED3_PIN    "P015" /* Onboard LED pins */
#define USER_INPUT  "P004"

void hal_entry(void)
{
    // rt_kprintf("\nHello RT-Thread!\n");
    rt_uint32_t led3_pin = rt_pin_get(LED3_PIN);

    while (1)
    {
        rt_thread_mdelay(1000);
        rt_pin_write(led3_pin, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(led3_pin, PIN_LOW);
    }
}

// void irq_callback_test(void *args)
// {
//     rt_kprintf("\n IRQ03 triggered \n");
// }

// void icu_sample(void)
// {
//     /* init */
//     rt_uint32_t pin = rt_pin_get(USER_INPUT);
//     rt_kprintf("\n pin number : 0x%04X \n", pin);
//     rt_err_t err = rt_pin_attach_irq(pin, PIN_IRQ_MODE_RISING, irq_callback_test, RT_NULL);
//     if (RT_EOK != err)
//     {
//         rt_kprintf("\n attach irq failed. \n");
//     }
//     err = rt_pin_irq_enable(pin, PIN_IRQ_ENABLE);
//     if (RT_EOK != err)
//     {
//         rt_kprintf("\n enable irq failed. \n");
//     }
// }
// MSH_CMD_EXPORT(icu_sample, icu sample);
