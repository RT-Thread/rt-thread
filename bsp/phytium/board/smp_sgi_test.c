/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2024/07/15  zhangyan     first commit
 */
#include "rtconfig.h"
#ifdef RT_USING_SMP
#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include "fparameters.h"
#include "ftypes.h"
#include "board.h"
#include <rtdbg.h>
#include "interrupt.h"
#include <rtdef.h>
#include "rtatomic.h"

#define RT_TEST_IPI                     3

struct rt_thread core_test_thread[RT_CPUS_NR];

static char *core_thread_name[4] =
{
    "core0_sgi_test",
    "core1_sgi_test",
    "core2_sgi_test",
    "core3_sgi_test",
};
static rt_uint8_t core_stack[RT_CPUS_NR][4096];

static rt_isr_handler_t smp_test_ipi_handle(int vector, void *param)
{
    rt_int32_t cpu_id = rt_hw_cpu_id();
    rt_kprintf("smp_test_ipi_handle, cpu_id = %d\n", cpu_id);
}

static void core_thread(void *parameter)
{
    rt_base_t level;
    rt_int32_t cpu_id = rt_hw_cpu_id();

    /* code */
    level = rt_cpus_lock();
    rt_hw_ipi_handler_install(RT_TEST_IPI, smp_test_ipi_handle);
    rt_hw_interrupt_umask(RT_TEST_IPI);
    rt_kprintf("core%d, rt_hw_interrupt_umask(RT_TEST_IPI) successfully.\n", cpu_id);
    rt_cpus_unlock(level);
}

void demo_core_test(void)
{
    rt_ubase_t i;
    rt_ubase_t cpu_id = 0;
    rt_kprintf("demo_core%d \n", rt_hw_cpu_id());
    for (i = 0; i < RT_CPUS_NR; i++)
    {
        cpu_id = i;
        rt_thread_init(&core_test_thread[i],
                       core_thread_name[i],
                       core_thread,
                       RT_NULL,
                       &core_stack[i],
                       2048,
                       20,
                       32);

        rt_thread_control(&core_test_thread[i], RT_THREAD_CTRL_BIND_CPU, (void *)cpu_id);
        rt_thread_startup(&core_test_thread[i]);
        rt_thread_mdelay(100);
    }
}

/* this function will toggle output pin and test intr of input pin */
static void smp_sgi_test_thread(void *parameter)
{
    rt_uint32_t cpu_mask = 0;

    for (int i = 0; i < RT_CPUS_NR; i++)
    {
        cpu_mask = (1 << i);
        rt_hw_ipi_send(RT_TEST_IPI, cpu_mask);
        rt_thread_mdelay(10);
    }
}

void smp_sgi_sample(int argc, char *argv[])
{
    rt_thread_t thread;
    rt_err_t res;
    demo_core_test();
    rt_thread_mdelay(1000);
    thread = rt_thread_create("smp_test_thread", smp_sgi_test_thread, RT_NULL, 4096, 25, 10);
    res = rt_thread_startup(thread);
    RT_ASSERT(res == RT_EOK);
}

MSH_CMD_EXPORT(smp_sgi_sample, smp toggle sgi sample.);

#endif