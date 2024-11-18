/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2014-04-27     Bernard      make code cleanup.
 */

#include <board.h>
#include <rtthread.h>

#include "peri_driver.h"

#define INIT_STACK_SIZE     512
#define LED_STACK_SIZE      256

#ifndef RT_USING_HEAP
/* if there is not enable heap, we should use static thread and stack. */

rt_align(8)
static rt_uint8_t led_stack[LED_STACK_SIZE];
static struct rt_thread led_thread;
#endif

static int led_app();

int main(void)
{
    rt_kprintf("Hello RT-Thread!\n");

    while(1)
    {
        rt_thread_mdelay(1000);
    }

    return 0;
}

/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
    rt_kprintf("\n\r Wrong parameter value detected on\r\n");
    rt_kprintf("       file  %s\r\n", file);
    rt_kprintf("       line  %d\r\n", line);

    while (1) ;
}

void rt_led_thread_entry(void *parameter)
{
    /* Initialize GPIO */
    Chip_GPIO_Init(LPC_GPIO_PORT);
    Chip_GPIO_PinSetDIR(LPC_GPIO_PORT, 0, 7, 1);
    Chip_GPIO_PinSetState(LPC_GPIO_PORT, 0, 7, true);

    while (1)
    {
        Chip_GPIO_PinSetState(LPC_GPIO_PORT, 0, 7, true);
        rt_thread_delay(RT_TICK_PER_SECOND / 2);

        Chip_GPIO_PinSetState(LPC_GPIO_PORT, 0, 7, false);
        rt_thread_delay(RT_TICK_PER_SECOND / 2);
    }
}

static int led_app()
{
    rt_thread_t tid;

#ifdef RT_USING_HEAP
    tid = rt_thread_create("led",
        rt_led_thread_entry, RT_NULL,
        LED_STACK_SIZE, RT_THREAD_PRIORITY_MAX/3, 20);
#else
    {

        rt_err_t result;

        tid = &led_thread;
        result = rt_thread_init(tid, "led", rt_led_thread_entry, RT_NULL,
                                led_stack, sizeof(led_stack), RT_THREAD_PRIORITY_MAX / 4, 20);
        RT_ASSERT(result == RT_EOK);
    }
#endif
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
