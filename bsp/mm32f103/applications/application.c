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
 * 2014-04-27     Bernard      make code cleanup. 
 */

#include <board.h>
#include <rtthread.h>

#include "HAL_device.h"

#define INIT_STACK_SIZE     512
#define LED_STACK_SIZE      128

#ifndef RT_USING_HEAP
/* if there is not enable heap, we should use static thread and stack. */
ALIGN(8)
static rt_uint8_t init_stack[INIT_STACK_SIZE];
static struct rt_thread init_thread;

ALIGN(8)
static rt_uint8_t led_stack[LED_STACK_SIZE];
static struct rt_thread led_thread;
#endif

void rt_init_thread_entry(void* parameter)
{    
     /* initialization RT-Thread Components */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_init();
#endif
    
}

void rt_led_thread_entry(void *parameter)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //开启GPIOA,GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//开启复用时钟，这个一定要开
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//失能JTAG，使能SW
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_SetBits(GPIOB, GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);
    
    while (1)
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_3);
        rt_thread_delay(RT_TIMER_TICK_PER_SECOND / 3);
        GPIO_SetBits(GPIOB, GPIO_Pin_3);
        rt_thread_delay(RT_TIMER_TICK_PER_SECOND / 3);
        
        GPIO_ResetBits(GPIOB, GPIO_Pin_4);
        rt_thread_delay(RT_TIMER_TICK_PER_SECOND / 3);
        GPIO_SetBits(GPIOB, GPIO_Pin_4);
        rt_thread_delay(RT_TIMER_TICK_PER_SECOND / 3);
        
        GPIO_ResetBits(GPIOB, GPIO_Pin_5);
        rt_thread_delay(RT_TIMER_TICK_PER_SECOND / 3);
        GPIO_SetBits(GPIOB, GPIO_Pin_5);
        rt_thread_delay(RT_TIMER_TICK_PER_SECOND / 3);
    }
}

int rt_application_init()
{
    rt_thread_t tid;

#ifdef RT_USING_HEAP
    tid = rt_thread_create("init",
        rt_init_thread_entry, RT_NULL,
        INIT_STACK_SIZE, RT_THREAD_PRIORITY_MAX/3, 20);
#else
    {
        
        rt_err_t result;

        tid = &init_thread;
        result = rt_thread_init(tid, "init", rt_init_thread_entry, RT_NULL,
                                init_stack, sizeof(init_stack), RT_THREAD_PRIORITY_MAX / 3, 20);
        RT_ASSERT(result == RT_EOK);
    }
#endif
    if (tid != RT_NULL)
        rt_thread_startup(tid);
    
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
