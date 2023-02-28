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
 * 2022-10-26  zhugengyu    support aarch64
 *
 */

#include <rtthread.h>
#include "board.h"
#include <gicv3.h>
#include "rtconfig.h"
#include "phytium_cpu.h"

#if defined(TARGET_ARMV8_AARCH64)
    #include "cpuport.h"
    #include "gtimer.h"
    #include "mmu.h"
#endif

#ifdef RT_USING_SMP
#include <interrupt.h>

#if defined(TARGET_ARMV8_AARCH64)
    #include "psci.h"
#endif

#include "fpsci.h"

rt_uint64_t rt_cpu_mpidr_early[] =
{
#if defined(TARGET_E2000D)
    [0] = 0x80000200,
    [1] = 0x80000201,
#elif defined(TARGET_E2000Q)
    [0] = 0x80000200,
    [1] = 0x80000201,
    [2] = 0x80000000,
    [3] = 0x80000100,
#elif defined(TARGET_F2000_4) || defined(TARGET_D2000)
    [0] = 0x80000000,
    [1] = 0x80000001,
    [2] = 0x80000100,
    [3] = 0x80000101,
#if defined(TARGET_D2000)
    [4] = 0x80000200,
    [5] = 0x80000201,
    [6] = 0x80000300,
    [7] = 0x80000301,
#endif
#endif

};

extern int rt_hw_timer_init(void);
extern void secondary_cpu_start(void);

void rt_hw_secondary_cpu_up(void)
{
    rt_uint32_t i;
    rt_uint32_t cpu_mask = 0;

    rt_kprintf("rt_hw_secondary_cpu_up is processing \r\n");
    for (i = 1; i < RT_CPUS_NR; i++)
    {

        cpu_mask = 1 << phytium_cpu_id_mapping(i);

        /* code */
        PsciCpuOn(cpu_mask, (uintptr)secondary_cpu_start);


#if defined(TARGET_ARMV8_AARCH64)
        __DSB();
#else
        __asm__ volatile("dsb" ::: "memory");
#endif
    }
}

void secondary_cpu_c_start(void)
{
    /* mmu init */
#if defined(TARGET_ARMV8_AARCH64)
    rt_hw_mmu_init();
#endif
    /*  spin lock init */
    rt_hw_spin_lock(&_cpus_lock);
    /* interrupt init */
#if defined(TARGET_ARMV8_AARCH64)
    arm_gic_cpu_init(0, platform_get_gic_cpu_base());
    arm_gic_redist_init(0, platform_get_gic_redist_base());
#else
    arm_gic_cpu_init(0);
    arm_gic_redist_init(0);
#endif

    /* vector init */
    rt_hw_vector_init();
    /* gtimer init */
#if defined(TARGET_ARMV8_AARCH64)
    rt_hw_gtimer_local_enable();
#else
    rt_hw_timer_init();
#endif
    rt_hw_interrupt_umask(RT_SCHEDULE_IPI);

    /* start scheduler */

    rt_kprintf("\rcall cpu %d on success\n", rt_hw_cpu_id());
    rt_hw_secondary_cpu_idle_exec();
    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
#if defined(TARGET_ARMV8_AARCH64)
    __WFE();
#else
    asm volatile("wfe" ::
                 : "memory", "cc");
#endif
}

#endif
