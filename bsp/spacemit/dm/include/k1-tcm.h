/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __K1_TCM_H__
#define __K1_TCM_H__

#include <rthw.h>
#include <rtthread.h>

void *tcm_alloc_cpu(int cpuid, rt_size_t size);
void tcm_free_cpu(int cpuid, void *ptr);

rt_inline void *tcm_alloc(rt_size_t size)
{
    return tcm_alloc_cpu(rt_hw_cpu_id(), size);
}

rt_inline void tcm_free(void *ptr)
{
    return tcm_free_cpu(rt_hw_cpu_id(), ptr);
}

#endif /* __K1_TCM_H__ */
