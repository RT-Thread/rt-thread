/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2010-06-29     lgnq         the first version
 *
 * For       : NEC V850E
 * Toolchain : IAR Embedded Workbench for V850 v3.71
*/

#include <rtthread.h>
#include "board.h"
#include "CG_macrodriver.h"
#include "CG_system.h"
#include "CG_port.h"
#include "CG_timer.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "CG_userdefine.h"

static struct rt_thread led;

#if defined(__ICCM16C__) || defined(__ICCV850__)
#pragma data_alignment=4
#endif
static rt_uint8_t led_stack[256];

static void rt_thread_entry_led(void* parameter)
{
    while (1)
    {
        /* led off */
        led_off();
        rt_thread_delay(20); /* sleep 1 second and switch to other thread */
        /* led on */
        led_on();
        rt_thread_delay(40);
    }
}

int rt_application_init(void)
{
    /* create led thread */
	rt_thread_init(&led,
		"led",
		rt_thread_entry_led, RT_NULL,
		&led_stack[0], sizeof(led_stack),
		5, 32);
    
    if (&led != RT_NULL)
        rt_thread_startup(&led);
        
    return 0;
}
