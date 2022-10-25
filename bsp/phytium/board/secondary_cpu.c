/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
 * All Rights Reserved.
 *  
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 * either version 1.0 of the License, or (at your option) any later version. 
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details. 
 *  
 * 
 * FilePath: secondary_cpu.c
 * Date: 2021-04-27 15:08:44
 * LastEditTime: 2022-02-18 08:29:25
 * Description:  This files is for 
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
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

        // rt_hw_ipi_send(RT_SCHEDULE_IPI, cpu_mask);
        // Ft_GenericTimer_UsDelay(1000000);
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
    /* init ipi */
// #if defined(TARGET_ARMV8_AARCH64)
//     arm_gic_umask(0, IRQ_ARM_IPI_KICK);
// #else
//     rt_hw_interrupt_umask(RT_SCHEDULE_IPI);
// #endif
    rt_hw_interrupt_umask(RT_SCHEDULE_IPI);

    /* start scheduler */

    rt_kprintf("\rcall cpu %d on success\n", rt_hw_cpu_id());
    rt_hw_secondary_cpu_idle_exec();
    rt_system_scheduler_start();

    // rt_hw_vector_init();
    // rt_hw_spin_lock(&_cpus_lock);

    // arm_gic_cpu_init(0);
    // arm_gic_redist_init(0);

    // rt_hw_timer_init();

    // rt_hw_interrupt_set_priority(RT_SCHEDULE_IPI, 16);
    // rt_hw_interrupt_umask(RT_SCHEDULE_IPI);

    // rt_system_scheduler_start();
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
