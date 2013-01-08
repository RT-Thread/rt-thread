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

#include "stm32f4xx.h"
#include <board.h>
#include <rtthread.h>

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#include "stm32_eth.h"
#endif

void rt_init_thread_entry(void* parameter)
{
    /* LwIP Initialization */
#ifdef RT_USING_LWIP
    {
        extern void lwip_sys_init(void);

        /* register ethernetif device */
        eth_system_device_init();

        rt_hw_stm32_eth_init();
        /* re-init device driver */
        rt_device_init_all();

        /* init lwip system */
        lwip_sys_init();
        rt_kprintf("TCP/IP initialized!\n");
    }
#endif

//FS

//GUI
}

float f_var1;
float f_var2;
float f_var3;
float f_var4;

ALIGN(RT_ALIGN_SIZE)
static char thread_led1_stack[1024];
struct rt_thread thread_led1;
static void rt_thread_entry_led1(void* parameter)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* GPIOD Periph clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    f_var1 = 3.141592653;
    f_var2 = 123.456;
    f_var3 = 0.123456789;
    f_var4 = 1.00001;

    while (1)
    {
        /* PD12 to be toggled */
        GPIO_SetBits(GPIOD, GPIO_Pin_12);

        /* Insert delay */
        rt_thread_delay(RT_TICK_PER_SECOND/2);
        f_var3 += f_var4;
        f_var4 = f_var4 * f_var4;

        /* PD13 to be toggled */
        GPIO_SetBits(GPIOD, GPIO_Pin_13);

        /* Insert delay */
        rt_thread_delay(RT_TICK_PER_SECOND/2);
        f_var3 += f_var4;
        f_var4 = f_var4 * f_var4;

        /* PD14 to be toggled */
        GPIO_SetBits(GPIOD, GPIO_Pin_14);

        /* Insert delay */
        rt_thread_delay(RT_TICK_PER_SECOND/2);
        f_var3 += f_var4;
        f_var4 = f_var4 * f_var4;

        /* PD15 to be toggled */
        GPIO_SetBits(GPIOD, GPIO_Pin_15);

        /* Insert delay */
        rt_thread_delay(RT_TICK_PER_SECOND*2);
        f_var3 += f_var4;
        f_var4 = f_var4 * f_var4;

        GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

        /* Insert delay */
        rt_thread_delay(RT_TICK_PER_SECOND);
        f_var3 += f_var4;
        f_var4 = f_var4 * f_var4;
    }
}


ALIGN(RT_ALIGN_SIZE)
static char thread_led2_stack[1024];
struct rt_thread thread_led2;
static void rt_thread_entry_led2(void* parameter)
{
    float f_var_me;

    char str_buffer[256];
    while(1)
    {
        f_var_me = f_var1 * f_var2 + f_var3;
        sprintf(str_buffer, "%f", f_var_me);
        rt_kprintf("thread1 %s\r\n", str_buffer);
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}

int rt_application_init()
{
    rt_thread_t init_thread;

#if (RT_THREAD_PRIORITY_MAX == 32)
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 8, 20);
#else
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 80, 20);
#endif

    if (init_thread != RT_NULL)
        rt_thread_startup(init_thread);

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
                   sizeof(thread_led2_stack),11,5);
    rt_thread_startup(&thread_led2);

    return 0;
}

/*@}*/
