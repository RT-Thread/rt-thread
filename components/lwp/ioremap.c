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

#include <ioremap.h>

#ifdef ARCH_MM_MMU
#include <mmu.h>
#include <lwp_mm_area.h>
#include <lwp_mm.h>

static struct lwp_avl_struct *k_map_area;
extern rt_mmu_info mmu_info;

static void _iounmap_range(void *addr, size_t size)
{
    void *va = RT_NULL, *pa = RT_NULL;
    int i = 0;

    for (va = addr, i = 0; i < size; va = (void *)((char *)va + ARCH_PAGE_SIZE), i += ARCH_PAGE_SIZE)
    {
        pa = rt_hw_mmu_v2p(&mmu_info, va);
        if (pa)
        {
            rt_hw_mmu_unmap(&mmu_info, va, ARCH_PAGE_SIZE);
        }
    }
}

static void *_ioremap_type(void *paddr, size_t size, int type)
{
    void *v_addr = NULL;
    size_t attr;

    switch (type)
    {
    case MM_AREA_TYPE_PHY:
        attr = MMU_MAP_K_DEVICE;
        break;
    case MM_AREA_TYPE_PHY_CACHED:
        attr = MMU_MAP_K_RWCB;
        break;
    default:
        return v_addr;
    }

    rt_mm_lock();
    v_addr = rt_hw_mmu_map(&mmu_info, 0, paddr, size, attr);
    if (v_addr)
    {
        int ret = lwp_map_area_insert(&k_map_area, (size_t)v_addr, size, type);
        if (ret != 0)
        {
            _iounmap_range(v_addr, size);
            v_addr = NULL;
        }
    }
    rt_mm_unlock();
    return v_addr;
}

void *rt_ioremap(void *paddr, size_t size)
{
    return _ioremap_type(paddr, size, MM_AREA_TYPE_PHY);
}

void *rt_ioremap_nocache(void *paddr, size_t size)
{
    return _ioremap_type(paddr, size, MM_AREA_TYPE_PHY);
}

void *rt_ioremap_cached(void *paddr, size_t size)
{
    return _ioremap_type(paddr, size, MM_AREA_TYPE_PHY_CACHED);
}

void rt_iounmap(volatile void *vaddr)
{
    struct lwp_avl_struct *ma_avl_node;

    rt_mm_lock();
    ma_avl_node = lwp_map_find(k_map_area, (size_t)vaddr);
    if (ma_avl_node)
    {
        struct rt_mm_area_struct *ma = (struct rt_mm_area_struct *)ma_avl_node->data;

        _iounmap_range((void *)ma->addr, ma->size);
        lwp_map_area_remove(&k_map_area, (size_t)vaddr);
    }
    rt_mm_unlock();
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
