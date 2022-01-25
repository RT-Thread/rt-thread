/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t led_stack[256];

static void rt_thread_entry_led(void *parameter)
{
    while (1)
    {
        led_off();
        rt_thread_delay(20);
        led_on();
        rt_thread_delay(40);
    }
}

int rt_application_init(void)
{
    rt_err_t result;

    result = rt_thread_init(&led,
                            "led",
                            rt_thread_entry_led,
                            RT_NULL,
                            &led_stack[0],
                            sizeof(led_stack),
                            RT_THREAD_PRIORITY_MAX / 2,
                            32);

    if (result == RT_EOK)
        rt_thread_startup(&led);

    return 0;
}
