/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date        Author     Email                   Notes
 * 2023-09-16  luhuadong  luhuadong@163.com       First Release
 */

#include <rtthread.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <shell.h>
#endif

#include "atmel_start.h"
#include <hal_gpio.h>

#ifdef SAM_CAN_EXAMPLE
#include "can_demo.h"
#endif

#ifdef SAM_I2C_EXAMPLE
#include "i2c_demo.h"
#endif

#ifdef SAM_ADC_EXAMPLE
#include "adc_demo.h"
#endif

#ifdef SAM_LWIP_EXAMPLE
#include "lwip_demo.h"
#endif

static rt_uint8_t led_stack[512];
static struct rt_thread led_thread;

static void led_thread_entry(void* parameter)
{
    unsigned int count=0;

    while (1)
    {
        /* toggle led */
#ifndef RT_USING_FINSH
        rt_kprintf("led toggle, count : %d\n",count);
#endif
        count++;
        gpio_toggle_pin_level(LED0);
        rt_thread_delay( RT_TICK_PER_SECOND/2 ); /* sleep 0.5 second and switch to other thread */
    }
}

int main(void)
{
    rt_err_t result;

    /* initialize led thread */
    result = rt_thread_init(&led_thread,
                            "led",
                            led_thread_entry,
                            RT_NULL,
                            (rt_uint8_t*)&led_stack[0],
                            sizeof(led_stack),
                            RT_THREAD_PRIORITY_MAX/3,
                            5);
    if (result == RT_EOK)
    {
        rt_thread_startup(&led_thread);
    }

#ifdef SAM_I2C_EXAMPLE
    i2c_demo_run();
#endif

#ifdef SAM_ADC_EXAMPLE
    adc_demo_run();
#endif

    return 0;
}
