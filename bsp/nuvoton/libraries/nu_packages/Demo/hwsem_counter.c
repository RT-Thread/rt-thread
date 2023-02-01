/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-10-5       Wayne        First version
*
******************************************************************************/

#include <rtthread.h>

#if defined(BSP_USING_HWSEM)

#include "drv_common.h"
#include "drv_hwsem.h"

#define DEF_COUNTER_ADDR_RTP  (3*1024*1024)
#define DEF_COUNTER_ADDR_A35  ((0x80000000+DEF_COUNTER_ADDR_RTP)|UNCACHEABLE)

#if defined(USE_MA35D1_SUBM)
    #define DEF_COUNTER_ADDR   DEF_COUNTER_ADDR_RTP
#else
    #define DEF_COUNTER_ADDR   DEF_COUNTER_ADDR_A35
#endif

static void hwsem_counter_go(void *parameter)
{
    rt_err_t ret;
    rt_device_t psNuHwSem = (rt_device_t)parameter;
    uint32_t *pu32Counter = (uint32_t *)DEF_COUNTER_ADDR;

    nu_mutex_t psNuMutex = nu_mutex_init(psNuHwSem, evHWSEM0);
    if (psNuMutex == RT_NULL)
        return;

    *pu32Counter = 0;
    while (1)
    {
        ret = nu_mutex_take(psNuMutex, RT_WAITING_FOREVER);
        if (ret != RT_EOK)
            continue;

        if (*pu32Counter >= 10)
        {
            nu_mutex_release(psNuMutex);
            break;
        }
        else
            *pu32Counter = *pu32Counter + 1;

#ifdef RT_USING_SMP
        rt_kprintf("[%08x@CPU-%d] ->Inc %d@%08x\n", rt_thread_self(), rt_hw_cpu_id(), *pu32Counter, DEF_COUNTER_ADDR);
#else
        rt_kprintf("[%08x]-> Inc %d@%08x\n", rt_thread_self(), *pu32Counter, DEF_COUNTER_ADDR);
#endif /* RT_USING_SMP */

        nu_mutex_release(psNuMutex);

        /* Relax, fair to get the mutex. */
        rt_thread_mdelay(500);
    }

    nu_mutex_deinit(psNuHwSem, evHWSEM0);
}

static int hwsem_counter_app(void)
{
    rt_err_t result = 0;
    rt_thread_t thread;
    rt_device_t psNuHwSem = rt_device_find("hwsem0");
    if (psNuHwSem == RT_NULL)
        return -1;

    thread = rt_thread_create("hwsa35", hwsem_counter_go, (void *)psNuHwSem, 2048, 25, 20);
    if (thread != RT_NULL)
    {
#ifdef RT_USING_SMP
        rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void *)0);
#endif
        result = rt_thread_startup(thread);
        RT_ASSERT(result == RT_EOK);
    }

    return 0;
}
INIT_APP_EXPORT(hwsem_counter_app);
MSH_CMD_EXPORT(hwsem_counter_app, demo hwsem);

#endif /* #if defined(BSP_USING_HWSEM)*/

