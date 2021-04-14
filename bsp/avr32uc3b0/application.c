/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-30     Kyle         First version
 */

#include <rtthread.h>
#include "compiler.h"
#include "gpio.h"

char thread_led1_stack[1024];
struct rt_thread thread_led1;
static void rt_thread_entry_led1(void* parameter)
{
    while (1)
    {
        /* led on */
        rt_kprintf("LED1 on\r\n");
        gpio_tgl_gpio_pin(AVR32_PIN_PA08);
        rt_thread_delay(RT_TICK_PER_SECOND / 2); /* sleep 0.5 second and switch to other thread */

        /* led off */
        rt_kprintf("LED1 off\r\n");
        gpio_tgl_gpio_pin(AVR32_PIN_PA08);
        rt_thread_delay(RT_TICK_PER_SECOND / 2);
    }
}

char thread_led2_stack[1024];
struct rt_thread thread_led2;
void rt_thread_entry_led2(void* parameter)
{
    while (1)
    {
        /* led on */
        rt_kprintf("LED2 on");
        gpio_tgl_gpio_pin(AVR32_PIN_PA07);
        rt_thread_delay(RT_TICK_PER_SECOND);

        /* led off */
        rt_kprintf("LED2 off\r\n");
        gpio_tgl_gpio_pin(AVR32_PIN_PA07);
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}

int rt_application_init()
{
    /* create led1 thread */
    rt_thread_init(&thread_led1,
                   "led1",
                   rt_thread_entry_led1,
                   RT_NULL,
                   &thread_led1_stack[0],
                   sizeof(thread_led1_stack), 5, 5);
    rt_thread_startup(&thread_led1);

    //------- init led2 thread
    rt_thread_init(&thread_led2,
                   "led2",
                   rt_thread_entry_led2,
                   RT_NULL,
                   &thread_led2_stack[0],
                   sizeof(thread_led2_stack),5,10);
    rt_thread_startup(&thread_led2);

    return 0;
}
