/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-29     Carl    the first version
 *
 */

#include <rtthread.h>
#include "ft2004.h"
#include "gicv3.h"

rt_uint64_t get_main_cpu_affval(void)
{
    return 0;
}

rt_uint32_t arm_gic_cpumask_to_affval(rt_uint32_t *cpu_mask, rt_uint32_t *cluster_id, rt_uint32_t *target_list)
{

    if (*cpu_mask == 0)
    {
        return 0;
    }

    *target_list = 0;
    *cluster_id = 0;

    if (*cpu_mask & 0x3)
    {
        if ((*cpu_mask & 0x3) == 0x3)
        {
            *target_list = 3;
        }
        else if ((*cpu_mask & 0x1))
        {
            *target_list = 1;
        }
        else
        {
            *target_list = 2;
        }
        *cpu_mask &= ~0x3;
    }
    else if (*cpu_mask & 0xc)
    {
        *cluster_id = 0x100;
        if ((*cpu_mask & 0xc) == 0xc)
        {
            *target_list = 3;
        }
        else if ((*cpu_mask & 0x4))
        {
            *target_list = 1;
        }
        else
        {
            *target_list = 2;
        }
        *cpu_mask &= ~0xc;
    }
    else
    {
        *cpu_mask = 0;
        return 0;
    }

    return 1;
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
