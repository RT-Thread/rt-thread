/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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
    #include "cp15.h"
#endif

#ifdef RT_USING_SMP
#include <interrupt.h>

#if defined(TARGET_ARMV8_AARCH64)
    #include "psci.h"
    extern void _secondary_cpu_entry(void);
#else
    extern void rt_secondary_cpu_entry(void);
#endif

#include "fpsci.h"

rt_uint64_t rt_cpu_mpidr_early[] =
{
#if defined(TARGET_E2000D)
    [0] = 0x80000200,
    [1] = 0x80000201,
#elif defined(TARGET_E2000Q)
    [0] = 0x80000000,
    [1] = 0x80000100,
    [2] = 0x80000200,
    [3] = 0x80000201,
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
#include "fcache.h"
void rt_hw_secondary_cpu_up(void)
{
    rt_uint32_t i;
    rt_uint32_t cpu_mask = 0;
    int cpu_id;
    cpu_id = rt_hw_cpu_id();
    rt_kprintf("rt_hw_secondary_cpu_up is processing \r\n");
    for (i = 0; i < RT_CPUS_NR;i++)
    {
        if(i == cpu_id)
        {
            continue;
        }
        cpu_mask = 1 << phytium_cpu_id_mapping(i);


#if defined(TARGET_ARMV8_AARCH64)
        /* code */
        char *entry = (char *)_secondary_cpu_entry;
        entry += PV_OFFSET;
        PsciCpuOn(cpu_mask, (uintptr)entry);
        __DSB();
#else
            /* code */
        PsciCpuOn(cpu_mask, (uintptr)rt_secondary_cpu_entry);
        __asm__ volatile("dsb" ::: "memory");
#endif

    }
}

void rt_hw_secondary_cpu_bsp_start(void)
{
    /*  spin lock init */
    rt_hw_spin_lock(&_cpus_lock);

    /* mmu init */
#if defined(TARGET_ARMV8_AARCH64)
    extern unsigned long MMUTable[];
    rt_hw_mmu_ktbl_set((unsigned long)MMUTable);
#endif

    /* vector init */
    rt_hw_vector_init();
    /* interrupt init */
#if defined(TARGET_ARMV8_AARCH64)
    arm_gic_cpu_init(0, 0);

    arm_gic_redist_init(0, 0);
    rt_kprintf("arm_gic_redist_init is over rt_hw_cpu_id() is %d \r\n", rt_hw_cpu_id());
#else
    arm_gic_cpu_init(0);
    arm_gic_redist_init(0);
#endif


    /* gtimer init */
#if defined(TARGET_ARMV8_AARCH64)
    rt_hw_gtimer_init();
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
