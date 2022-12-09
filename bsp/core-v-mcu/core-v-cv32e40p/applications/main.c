/*
<<<<<<< HEAD
 * FreeRTOS Kernel V10.2.1
 * 1 tab == 8 spaces!
 */

/*
 * Create implementation of vPortSetupTimerInterrupt() if the CLINT is not
 * available, but make sure the configCLINT_BASE_ADDRESS constant is still
 * defined.
 * 
 * Define vPortHandleInterrupt to whatever the interrupt handler is called.  In
 * this case done by defining vPortHandleInterrupt=SystemIrqHandler on the
 * assembler command line as SystemIrqHandler is referenced from both FreeRTOS
 * code and the libraries that come with the Vega board.
 *

/* FreeRTOS kernel includes. */ 
//#include <FreeRTOS.h>
/* RT-Thread kernel includes. */
=======
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-08     WangShun     first version
 */

>>>>>>> 1185482745fa76c9094f8cf9227f85d55ed8e2bd
#include "rtthread.h"
#include "hal_fc_event.h"
#include <stdio.h>
#include <stdint.h>
<<<<<<< HEAD
//#include "ringbuffer.h"
#include "rtconfig.h"

#define rtthread_task
static struct rt_thread led1_thread;
static rt_thread_t led2_thread = RT_NULL;

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t rt_led1_thread_stack[1024];
static void led1_thread_entry(void* parameter);
static void led2_thread_entry(void* parameter);

void led_init(void)
{
	rt_kprintf("Hello RT-Thread 1\r\n");
	rt_kprintf("RT-Thread INIT TEST \r\n");
	rt_kprintf("RT-Thread TEST SUCCESS \r\n");
}
INIT_APP_EXPORT(led_init);
=======
#include "rtconfig.h"

#define rtthread_task
static struct rt_thread test1_thread;
static rt_thread_t test2_thread = RT_NULL;

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t rt_test1_thread_stack[1024];
static void test1_thread_entry(void* parameter);
static void test2_thread_entry(void* parameter);

void test_init(void)
{
	rt_kprintf("Hello RT-Thread\r\n");
}
INIT_APP_EXPORT(test_init);
>>>>>>> 1185482745fa76c9094f8cf9227f85d55ed8e2bd

int main(void)
{
#ifndef rtthread_task
<<<<<<< HEAD
	rt_thread_init(&led1_thread,                 /* 线程控制块 */
                   "led1",                       /* 线程名字 */
                   led1_thread_entry,            /* 线程入口函数 */
                   RT_NULL,                      /* 线程入口函数参数 */
                   &rt_led1_thread_stack[0],     /* 线程栈起始地址 */
                   sizeof(rt_led1_thread_stack), /* 线程栈大小 */
                   6,                            /* 线程的优先级 */
                   20);                          /* 线程时间片 */

	/* 启动线程，开启调度 */
    rt_thread_startup(&led1_thread);             /* 启动线程，开启调度 */

    led2_thread = rt_thread_create( "led2",      /* 线程名字 */
                      led2_thread_entry,   		/* 线程入口函数 */
                      RT_NULL,             		/* 线程入口函数参数 */
                      512,                 		/* 线程栈大小 */
                      5,                   		/* 线程的优先级 */
                      20);                 		/* 线程时间片 */
	/* 启动线程，开启调度 */
    rt_thread_startup(led2_thread);
#endif
}

static void led1_thread_entry(void* parameter)
{
    while (1)
    {
    	rt_kprintf("test\r\n");
        rt_thread_delay(500);   /* 延时500个tick */
    }
}

static void led2_thread_entry(void* parameter)
{
	while (1)
	{
		rt_thread_delay(500);   /* 延时500个tick */
	}
}

=======
	rt_thread_init(&test1_thread,                 
                   "test1",                       
                   test1_thread_entry,            
                   RT_NULL,                      
                   &rt_test1_thread_stack[0],     
                   sizeof(rt_test1_thread_stack), 
                   6,                            
                   20);                          

    rt_thread_startup(&test1_thread);             

    test2_thread = rt_thread_create( "test2",      
                      test2_thread_entry,   		
                      RT_NULL,             		
                      512,                 		
                      5,                   		
                      20);                 		

    rt_thread_startup(test2_thread);
#endif
}

static void test1_thread_entry(void* parameter)
{
    while (1)
    {
    	rt_kprintf("test1\r\n");
        rt_thread_delay(500);  
    }
}

static void test2_thread_entry(void* parameter)
{
	while (1)
	{
        rt_kprintf("test2\r\n");
		rt_thread_delay(500); 
	}
}
>>>>>>> 1185482745fa76c9094f8cf9227f85d55ed8e2bd
