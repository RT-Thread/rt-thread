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
 *
 */

#include "rtconfig.h"
#include <rtthread.h>
#include "gicv3.h"
#include "fcpu_info.h"
#include "phytium_cpu.h"

rt_uint64_t rt_cpu_mpidr_table[] =
{
#if defined(TARGET_PE2202)
    [0] = RT_CORE_AFF(0),
    [1] = RT_CORE_AFF(1),
#elif defined(TARGET_PE2204)
    [0] = RT_CORE_AFF(0),
    [1] = RT_CORE_AFF(1),
    [2] = RT_CORE_AFF(2),
    [3] = RT_CORE_AFF(3),
#elif defined(TARGET_PD2408)
    [0] = RT_CORE_AFF(0),
    [1] = RT_CORE_AFF(1),
    [2] = RT_CORE_AFF(2),
    [3] = RT_CORE_AFF(3),
    [4] = RT_CORE_AFF(4),
    [5] = RT_CORE_AFF(5),
    [6] = RT_CORE_AFF(6),
    [7] = RT_CORE_AFF(7),
#endif
    [RT_CPUS_NR] = 0
};

/**
@name: phytium_cpu_id_mapping
@msg: Map Phytium CPU ID
@brief: Map the input CPU ID to a new CPU ID based on the type and quantity of CPUs on the target board.
@param {int} cpu_id Input CPU ID
@return {int} Mapped CPU ID
*/
int phytium_cpu_id_mapping(int cpu_id)
{
#if defined(TARGET_PE2204)
    switch (cpu_id)
    {
        case 0:
            return 2;
        case 1:
            return 3;
        case 2:
            return 0;
        case 3:
            return 1;
        default:
            RT_ASSERT(0);
            return 0;
            break;
    }
#else
    return (int)cpu_id;
#endif
}

#if defined(TARGET_ARMV8_AARCH32)

int rt_hw_cpu_id(void)
{
    FError ret;
    u32 cpu_id;
    ret = GetCpuId(&cpu_id);

    if (ret != ERR_SUCCESS)
    {
        RT_ASSERT(0);
    }
    return phytium_cpu_id_mapping(cpu_id);
}

rt_uint64_t get_main_cpu_affval(void)
{
#if defined(TARGET_PE2204)
    return CORE2_AFF;
#else
    return CORE0_AFF;
#endif
}

extern u32 GetCpuMaskToAffval(u32 *cpu_mask, u32 *cluster_id, u32 *target_list);
rt_uint32_t arm_gic_cpumask_to_affval(rt_uint32_t *cpu_mask, rt_uint32_t *cluster_id, rt_uint32_t *target_list)
{
    return GetCpuMaskToAffval(cpu_mask, cluster_id, target_list);
}

#ifdef RT_USING_SMP

void send_core_isg(void)
{
    for (rt_size_t i = 0; i <= 0xf; i++)
    {
        /* code */
        rt_kprintf("i %x \r\n", i);
        arm_gic_send_affinity_sgi(0, 0, i, 0);
        rt_thread_mdelay(100);
    }
}
MSH_CMD_EXPORT(send_core_isg, send_core_isg);

#endif

#endif
