/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-8-16       Wayne        First version
*
******************************************************************************/

#include <rtthread.h>

#if defined(RT_USING_SMP)
#include "drv_common.h"


#define DEF_COUNTER_ADDR_RTP  (3*1024*1024)
#define DEF_COUNTER_ADDR_A35  ((0x80000000+DEF_COUNTER_ADDR_RTP)|UNCACHEABLE)

#if defined(USE_MA35D1_SUBM)
    #define DEF_COUNTER_ADDR   DEF_COUNTER_ADDR_RTP
#else
    #define DEF_COUNTER_ADDR   DEF_COUNTER_ADDR_A35
#endif

void happy_counter(void *pdata)
{
    uint32_t counter = 0;
    while (1)
    {
        rt_kprintf("cpu-%d %d\r\n", rt_hw_cpu_id(), counter++);
        rt_thread_mdelay(1000);
    }
}

void go_happy_counter(void)
{
    rt_thread_t tid = rt_thread_create("cpu-1", happy_counter, RT_NULL,  2048, 10, 20);
    RT_ASSERT(tid != RT_NULL);

    rt_thread_control(tid, RT_THREAD_CTRL_BIND_CPU, (void *)1);

    rt_thread_startup(tid);
}
MSH_CMD_EXPORT(go_happy_counter, go happy counter);

void happy_memcpy(void *pdata)
{
    volatile uint32_t counter = 0;
    void *srcbuf, *dstbuf;
    rt_tick_t last, now;

#define DEF_BUF_SIZE 4096
#define DEF_TIMES    500000
    srcbuf = rt_malloc_align(DEF_BUF_SIZE, nu_cpu_dcache_line_size());
    dstbuf = rt_malloc_align(DEF_BUF_SIZE, nu_cpu_dcache_line_size());

    now = rt_tick_get();
    while (counter < DEF_TIMES)
    {
        rt_memcpy(dstbuf, srcbuf, DEF_BUF_SIZE);
        counter++;
    }
    last = rt_tick_get();

    if (rt_hw_cpu_id() == 1)
        rt_thread_mdelay(1000);

    rt_kprintf("%d Bytes copied by cpu-%d in %d ms\n", DEF_TIMES * DEF_BUF_SIZE, rt_hw_cpu_id(), last - now);

    rt_free_align(srcbuf);
    rt_free_align(dstbuf);
}

void go_happy_memcpy_0_1(void)
{
    rt_thread_t tid0, tid1;

    tid0 = rt_thread_create("cpu-0", happy_memcpy, RT_NULL,  2048, 10, 20);
    RT_ASSERT(tid0 != RT_NULL);
    rt_thread_control(tid0, RT_THREAD_CTRL_BIND_CPU, (void *)0);

    tid1 = rt_thread_create("cpu-1", happy_memcpy, RT_NULL,  2048, 10, 20);
    RT_ASSERT(tid1 != RT_NULL);
    rt_thread_control(tid1, RT_THREAD_CTRL_BIND_CPU, (void *)1);

    rt_thread_startup(tid0);
    rt_thread_startup(tid1);
}
MSH_CMD_EXPORT(go_happy_memcpy_0_1, go happy memcpy on dual - core);

void go_happy_memcpy_0(void)
{
    rt_thread_t tid0;

    tid0 = rt_thread_create("cpu-0", happy_memcpy, RT_NULL,  2048, 10, 20);
    RT_ASSERT(tid0 != RT_NULL);
    rt_thread_control(tid0, RT_THREAD_CTRL_BIND_CPU, (void *)0);

    rt_thread_startup(tid0);
}
MSH_CMD_EXPORT(go_happy_memcpy_0, go happy memcpy on core0);

void go_happy_memcpy_1(void)
{
    rt_thread_t tid1;

    tid1 = rt_thread_create("cpu-1", happy_memcpy, RT_NULL,  2048, 10, 20);
    RT_ASSERT(tid1 != RT_NULL);
    rt_thread_control(tid1, RT_THREAD_CTRL_BIND_CPU, (void *)1);

    rt_thread_startup(tid1);
}
MSH_CMD_EXPORT(go_happy_memcpy_1, go happy memcpy on core1);

static void happy_mutex(void *parameter)
{
    rt_err_t ret;
    rt_mutex_t psMutex = (rt_mutex_t)parameter;
    uint32_t *pu32Counter = (uint32_t *)DEF_COUNTER_ADDR;

    *pu32Counter = 0;
    while (1)
    {
        ret = rt_mutex_take(psMutex, RT_WAITING_FOREVER);
        if (ret != RT_EOK)
            continue;

        if (*pu32Counter >= 1000)
        {
            rt_mutex_release(psMutex);
            break;
        }
        else
            *pu32Counter = *pu32Counter + 1;

#ifdef RT_USING_SMP
        rt_kprintf("[%08x@CPU-%d] ->Inc %d@%08x\n", rt_thread_self(), rt_hw_cpu_id(), *pu32Counter, DEF_COUNTER_ADDR);
#else
        rt_kprintf("[%08x]-> Inc %d@%08x\n", rt_thread_self(), *pu32Counter, DEF_COUNTER_ADDR);
#endif /* RT_USING_SMP */

        rt_mutex_release(psMutex);
    }
}

static int go_happy_mutex(void)
{
    rt_thread_t thread;
    rt_mutex_t  sem = rt_mutex_create("mutexsem", RT_IPC_FLAG_PRIO);

    if(sem == RT_NULL)
    {
        rt_kprintf("create mutex failed");
        return (int)-RT_ERROR;
    }

    thread = rt_thread_create("mutex0", happy_mutex, (void *)sem, 2048, 25, 20);
    if (thread != RT_NULL)
    {
#ifdef RT_USING_SMP
        rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void *)0);
#endif
        rt_thread_startup(thread);
    }

    thread = rt_thread_create("mutex1", happy_mutex, (void *)sem, 2048, 25, 20);
    if (thread != RT_NULL)
    {
#ifdef RT_USING_SMP
        rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void *)1);
#endif
        rt_thread_startup(thread);
    }

    return 0;
}
MSH_CMD_EXPORT(go_happy_mutex, demo mutex);


#endif
