/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2022-10-26  huanghe      first commit
 *
 */

#include <rthw.h>
#include <rtthread.h>

#include <board.h>

#define ASSERT_STATIC(expression) \
    extern int assert_static[(expression) ? 1 : -1]

/* check if SMP related setting ok */
#ifndef RT_USING_SMP
    ASSERT_STATIC(RT_CPUS_NR == 1U); /* please set RT_CPUS_NR = 1 when SMP off */
#else
    #if defined(TARGET_E2000D)
        ASSERT_STATIC(RT_CPUS_NR <= 2U); /* use 2 cores at most */
    #elif defined(TARGET_E2000Q) || defined(TARGET_PHYTIUMPI)
        ASSERT_STATIC(RT_CPUS_NR <= 4U); /* use 4 cores at most */
    #endif
#endif

#ifdef RT_USING_SMP

struct rt_thread test_core[RT_CPUS_NR];
static char *core_thread_name[8] =
{
    "core0_test",
    "core1_test",
    "core2_test",
    "core3_test",
    "core4_test",
    "core5_test",
    "core6_test",
    "core7_test"
};
static rt_uint8_t core_stack[RT_CPUS_NR][4096];

static void demo_core_thread(void *parameter)
{
    rt_base_t level;
    while (1)
    {
        /* code */
        level = rt_cpus_lock();
        rt_kprintf("Hi, core%d \r\n", rt_hw_cpu_id());
        rt_cpus_unlock(level);
        rt_thread_mdelay(20000);
    }
}

void demo_core(void)
{
    rt_ubase_t i;
    rt_ubase_t cpu_id = 0;
    for (i = 0; i < RT_CPUS_NR; i++)
    {
        cpu_id = i;
        rt_thread_init(&test_core[i],
                       core_thread_name[i],
                       demo_core_thread,
                       RT_NULL,
                       &core_stack[i],
                       2048,
                       20,
                       32);

        rt_thread_control(&test_core[i], RT_THREAD_CTRL_BIND_CPU, (void *)cpu_id);
        rt_thread_startup(&test_core[i]);
    }
}
#endif

int main(void)
{
#ifdef RT_USING_SMP
    demo_core();
#endif
    return RT_EOK;
}

