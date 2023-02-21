/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-14     WangXiaoyao  the first version
 */

#include <rtthread.h>
#define DBG_TAG "mm.kmem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "mm_aspace.h"
#include "mm_private.h"
#include <mmu.h>

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

#define _KMEM_LO_OFF(addr) ((rt_ubase_t)(addr) & ARCH_PAGE_MASK)

int rt_kmem_map_phy(void *va, void *pa, rt_size_t length, rt_size_t attr)
{
    int err;
    size_t lo_off;
    lo_off = _KMEM_LO_OFF(pa);

    if (va == RT_NULL)
    {
        LOG_E("%s: va NULL is not a valid input", __func__);
        err = -RT_EINVAL;
    }
    else if (_KMEM_LO_OFF(pa) != _KMEM_LO_OFF(va))
    {
        LOG_E("%s: misaligned PA(%p) to VA(%p)", __func__, pa, va);
        err = -RT_EINVAL;
    }
    else
    {
        struct rt_mm_va_hint hint = {.flags = MMF_MAP_FIXED,
                                    .limit_range_size = rt_kernel_space.size,
                                    .limit_start = rt_kernel_space.start,
                                    .prefer = va,
                                    .map_size = RT_ALIGN(length + lo_off, ARCH_PAGE_SIZE)};

        err = rt_aspace_map_phy(&rt_kernel_space, &hint, attr, MM_PA_TO_OFF(pa), &va);

        if (err)
        {
            LOG_W("%s: map %p to %p (%p bytes) failed(err %d)", __func__, pa, va, length, err);
        }
    }

    return err;
}

void *rt_kmem_v2p(void *vaddr)
{
    return rt_hw_mmu_v2p(&rt_kernel_space, vaddr);
}
