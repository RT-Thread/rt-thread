/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-05-23     aozima       first implementation for PIC32.
 */

// Adds support for PIC32 Peripheral library functions and macros
#include <plib.h>
#include <rtthread.h>

ALIGN(RT_ALIGN_SIZE)
int thread_led1_stack[512];
struct rt_thread thread_led1;
void thread_led1_entry(void* parameter)
{
    // configure PORTD.RD1 = output
    mPORTDSetPinsDigitalOut(BIT_1);
    while(1)
    {
        // .. Toggle the LED
        mPORTDToggleBits(BIT_1);
        rt_thread_delay( RT_TICK_PER_SECOND ); /* delay 1s */
    }
}

static void thread_led2_entry(void* parameter)
{
    // configure PORTD.RD2 = output
    mPORTDSetPinsDigitalOut(BIT_2);

    while (1)
    {
        // .. Toggle the LED
        mPORTDToggleBits(BIT_2);
        rt_thread_delay( RT_TICK_PER_SECOND/2 ); /* delay 0.5s */
    }
}

int rt_application_init(void)
{
    rt_thread_t thread;

    rt_thread_init(&thread_led1,
                   "led1",
                   thread_led1_entry, RT_NULL,
                   &thread_led1_stack[0], sizeof(thread_led1_stack),
                   20, 10);
    rt_thread_startup(&thread_led1);

    /* create led2 thread */
    thread = rt_thread_create("led2",
                              thread_led2_entry, RT_NULL,
                              1024,
                              20, 5);
    if (thread != RT_NULL)
        rt_thread_startup(thread);

    return 0;
}
