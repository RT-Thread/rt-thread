/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-14     aozima       first implementation for Nios II.
 * 2011-03-04     aozima       add led.
 */

#include <rtthread.h>
#include "board.h"

/**
 * @addtogroup NIOS_II
 */

/*@{*/

#include "system.h"
#include "altera_avalon_pio_regs.h"

// trun on led n
#define rt_hw_led_on(n)  IOWR_ALTERA_AVALON_PIO_DATA(\
                         LED_BASE,\
                         IORD_ALTERA_AVALON_PIO_DATA(LED_BASE) | 1<<n)
// trun off led n
#define rt_hw_led_off(n) IOWR_ALTERA_AVALON_PIO_DATA(\
                         LED_BASE,\
                         IORD_ALTERA_AVALON_PIO_DATA(LED_BASE) & ~(1<<n) )

ALIGN(RT_ALIGN_SIZE)
static char thread_led1_stack[1024];
struct rt_thread thread_led1;
static void rt_thread_entry_led1(void* parameter)
{
    unsigned int count=0;
    while (1)
    {
        /* led1 on */
#ifndef RT_USING_FINSH
        rt_kprintf("led1 on,count : %d\r\n",count);
#endif
        count++;
        rt_hw_led_on(1);
        /* sleep 0.5 second and switch to other thread */
        rt_thread_delay(RT_TICK_PER_SECOND/2);

        /* led1 off */
#ifndef RT_USING_FINSH
        rt_kprintf("led1 off\r\n");
#endif
        rt_hw_led_off(1);
        rt_thread_delay(RT_TICK_PER_SECOND/2);
    }
}

ALIGN(RT_ALIGN_SIZE)
static char thread_led2_stack[1024];
struct rt_thread thread_led2;
void rt_thread_entry_led2(void* parameter)
{
    unsigned int count=0;
    while (1)
    {
        /* led2 on */
#ifndef RT_USING_FINSH
        rt_kprintf("led2 on,count : %d\r\n",count);
#endif
        count++;
        rt_hw_led_on(2);
        rt_thread_delay(RT_TICK_PER_SECOND);

        /* led2 off */
#ifndef RT_USING_FINSH
        rt_kprintf("led2 off\r\n");
#endif
        rt_hw_led_off(2);
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}

int rt_application_init()
{
    // led_init();

    //------- init led1 thread
    rt_thread_init(&thread_led1,
                   "led1",
                   rt_thread_entry_led1,
                   RT_NULL,
                   &thread_led1_stack[0],
                   sizeof(thread_led1_stack),11,5);
    rt_thread_startup(&thread_led1);

    //------- init led2 thread
    rt_thread_init(&thread_led2,
                   "led2",
                   rt_thread_entry_led2,
                   RT_NULL,
                   &thread_led2_stack[0],
                   sizeof(thread_led2_stack),12,5);
    rt_thread_startup(&thread_led2);

    return 0;
}

/*@}*/

