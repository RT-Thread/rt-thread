/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2010-03-30     Kyle             First version
 * 2023-10-20     Raman Gopalan    Access GPIO using RT's pin abstractions
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "compiler.h"
#include "gpio.h"

#define USER_LED_1    AVR32_PIN_PA08
#define USER_LED_2    AVR32_PIN_PA07

char thread_led1_stack[1024];
struct rt_thread thread_led1;
static void rt_thread_entry_led1(void* parameter)
{
    rt_pin_mode(USER_LED_1, PIN_MODE_OUTPUT);
    while (1)
    {
        rt_pin_write(USER_LED_1, 1);
        rt_thread_delay(RT_TICK_PER_SECOND / 2); /* sleep 0.5 second and switch to other thread */

        rt_pin_write(USER_LED_1, 0);
        rt_thread_delay(RT_TICK_PER_SECOND / 2);
    }
}

char thread_led2_stack[1024];
struct rt_thread thread_led2;
void rt_thread_entry_led2(void* parameter)
{
    rt_pin_mode(USER_LED_2, PIN_MODE_OUTPUT);
    while (1)
    {
        rt_pin_write(USER_LED_2, 1);
        rt_thread_delay(RT_TICK_PER_SECOND);

        rt_pin_write(USER_LED_2, 0);
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
