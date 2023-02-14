/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-14     WangXiaoyao  the first version
 */

#include "mm_aspace.h"
#include "mm_private.h"

static void list_kernel_space(void)
{
    rt_aspace_print_all(&rt_kernel_space);
}
MSH_CMD_EXPORT(list_kernel_space, List varea in kernel space);

void rt_kmem_list_varea(void) __attribute__((alias("list_kernel_space")));

static rt_ubase_t rt_pv_offset;

rt_ubase_t rt_kmem_pvoff(void)
{
    return rt_pv_offset;
}

void rt_kmem_pvoff_set(rt_ubase_t pvoff)
{
    rt_pv_offset = pvoff;
}
