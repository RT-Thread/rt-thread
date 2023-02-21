/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-08     WangShun     first version
 */

#include "rtthread.h"
#include "hal_fc_event.h"
#include <stdio.h>
#include <stdint.h>
#include "rtconfig.h"
#include "udma_uart_driver.h"
#include "stdlib.h"
/*Note:Bsp shell switch flag,do not modify*/
int irq_cli_flag = 1;
/*If add CorevMCU_CLI package,please put the code in example.c here*/

#define rtthread_task
static struct rt_thread test1_thread;
static rt_thread_t test2_thread = RT_NULL;

rt_align(RT_ALIGN_SIZE)
static rt_uint8_t rt_test1_thread_stack[1024];
static void test1_thread_entry(void* parameter);
static void test2_thread_entry(void* parameter);

void test_init(void)
{
    rt_kprintf("Hello RT-Thread!\r\n");
}
INIT_APP_EXPORT(test_init);

int main(void)
{
#ifndef rtthread_task
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
