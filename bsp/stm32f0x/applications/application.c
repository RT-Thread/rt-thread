/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <stdio.h>

#include <board.h>
#include <rtthread.h>

/*
LED_GREEN: PC8
LED_RED  : PC9
*/
#define rt_hw_led_on()   GPIO_SetBits(GPIOC, GPIO_Pin_9)
#define rt_hw_led_off()  GPIO_ResetBits(GPIOC, GPIO_Pin_9)

static void rt_hw_led_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Enable the GPIO_LED Clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

    /* Configure the GPIO_LED pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

ALIGN(RT_ALIGN_SIZE)
static char led_stack[384];
static struct rt_thread led_thread;

static void led_thread_entry(void* parameter)
{
    rt_hw_led_init();

    while(1)
    {
        rt_hw_led_on();
        rt_thread_delay(RT_TICK_PER_SECOND/4);

        rt_hw_led_off();
        rt_thread_delay(RT_TICK_PER_SECOND/4);
    }
}

int rt_application_init()
{
    rt_err_t result;

    result = rt_thread_init(&led_thread,
                            "led",
                            led_thread_entry,
                            RT_NULL,
                            &led_stack[0],
                            sizeof(led_stack),
                            4,
                            2);
    if(result == RT_EOK) rt_thread_startup(&led_thread);

    return 0;
}

/*@}*/
