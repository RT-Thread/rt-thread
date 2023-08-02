/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-06     Jesven       first version
 */
#include <rthw.h>
#include <rtthread.h>

#include <mmu.h>
#include <mm_aspace.h>
#include <ioremap.h>

void *rt_ioremap_start;
size_t rt_ioremap_size;

#ifdef RT_USING_SMART

#include <lwp_mm.h>
#define DBG_TAG "mm.ioremap"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

enum ioremap_type
{
    MM_AREA_TYPE_PHY,
    MM_AREA_TYPE_PHY_WT,
    MM_AREA_TYPE_PHY_CACHED
};

static void *_ioremap_type(void *paddr, size_t size, enum ioremap_type type)
{
    char *v_addr = NULL;
    size_t attr;
    size_t lo_off;
    int err;

    lo_off = (rt_ubase_t)paddr & ARCH_PAGE_MASK;

    struct rt_mm_va_hint hint = {
        .prefer = RT_NULL,
        .map_size = RT_ALIGN(size + lo_off, ARCH_PAGE_SIZE),
        .flags = 0,
        .limit_start = rt_ioremap_start,
        .limit_range_size = rt_ioremap_size,
    };

    switch (type)
    {
    case MM_AREA_TYPE_PHY:
        attr = MMU_MAP_K_DEVICE;
        break;
    case MM_AREA_TYPE_PHY_WT:
        attr = MMU_MAP_K_RW;
        break;
    case MM_AREA_TYPE_PHY_CACHED:
        attr = MMU_MAP_K_RWCB;
        break;
    default:
        return v_addr;
    }
    err = rt_aspace_map_phy(&rt_kernel_space, &hint, attr, MM_PA_TO_OFF(paddr), (void **)&v_addr);

    if (err)
    {
        LOG_W("IOREMAP 0x%lx failed %d\n", paddr, err);
        v_addr = NULL;
    }
    else
    {
        v_addr = v_addr + lo_off;
    }
    return v_addr;
}

rt_weak void *rt_ioremap_early(void *paddr, size_t size)
{
    if (!size)
    {
        return RT_NULL;
    }

    return paddr;
}

void *rt_ioremap(void *paddr, size_t size)
{
    return _ioremap_type(paddr, size, MM_AREA_TYPE_PHY);
}

void *rt_ioremap_nocache(void *paddr, size_t size)
{
    return _ioremap_type(paddr, size, MM_AREA_TYPE_PHY);
}

void *rt_ioremap_wt(void *paddr, size_t size)
{
    return _ioremap_type(paddr, size, MM_AREA_TYPE_PHY_WT);
}

void *rt_ioremap_cached(void *paddr, size_t size)
{
    return _ioremap_type(paddr, size, MM_AREA_TYPE_PHY_CACHED);
}

void rt_iounmap(volatile void *vaddr)
{
    rt_aspace_unmap(&rt_kernel_space, (void *)vaddr);
}

#else
void *rt_ioremap(void *paddr, size_t size)
{
    return paddr;
}

void *rt_ioremap_nocache(void *paddr, size_t size)
{
    return paddr;
}

void *rt_ioremap_cached(void *paddr, size_t size)
{
    return paddr;
}

void rt_iounmap(volatile void *vaddr)
{
}
#endif
