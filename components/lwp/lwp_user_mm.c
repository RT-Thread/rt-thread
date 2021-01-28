/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-28     Jesven       first version
 */

#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_USERSPACE

#include <mmu.h>
#include <page.h>
#include <lwp_mm_area.h>
#include <lwp_user_mm.h>
#include <lwp_arch.h>

#ifdef RT_USING_GDBSERVER
#include <lwp_gdbserver.h>
#include <hw_breakpoint.h>
#endif

int lwp_user_space_init(struct rt_lwp *lwp)
{
    return arch_user_space_init(lwp);
}

void switch_mmu(void *mtable);
void *mmu_table_get(void);
void lwp_mmu_switch(struct rt_thread *thread)
{
    struct rt_lwp *l = RT_NULL;
    void *pre_mmu_table = RT_NULL, *new_mmu_table = RT_NULL;

    if (thread->lwp)
    {
        l = (struct rt_lwp*)thread->lwp;
        new_mmu_table = (void*)((char*)l->mmu_info.vtable + l->mmu_info.pv_off);
#ifdef LWP_DEBUG
        {
            int i = 0;
            size_t *p = l->mmu_info.vtable;

            rt_kprintf("vtable = 0x%p\n", l->mmu_info.vtable);
            for (i = 0; i < 0x1000; i++)
            {
                rt_kprintf("0x%08x ", *p++);
                if (( i & 0xf) == 0xf)
                {
                    rt_kprintf("\n");
                }
            }
        }
#endif
    }
    else
    {
        new_mmu_table = arch_kernel_mmu_table_get();
    }

    pre_mmu_table = mmu_table_get();
    if (pre_mmu_table != new_mmu_table)
    {
#ifdef RT_USING_GDBSERVER
        set_process_id((uint32_t)(size_t)l);
#endif
        switch_mmu(new_mmu_table);
    }
#ifdef RT_USING_GDBSERVER
    if (l && l->debug)
    {
        uint32_t step_type = 0;

        step_type = gdb_get_step_type();

        if ((step_type == 2) || (thread->step_exec && (step_type == 1)))
        {
            arch_activate_step();
        }
        else
        {
            arch_deactivate_step();
        }
    }
#endif
}

static void unmap_range(struct rt_lwp *lwp, void *addr, size_t size, int pa_need_free)
{
    void *va = RT_NULL, *pa = RT_NULL;
    int i = 0;

    for (va = addr, i = 0; i < size; va = (void*)((char*)va + ARCH_PAGE_SIZE), i += ARCH_PAGE_SIZE)
    {
        pa = rt_hw_mmu_v2p(&lwp->mmu_info, va);
        if (pa)
        {
            rt_hw_mmu_unmap(&lwp->mmu_info, va, ARCH_PAGE_SIZE);
            if (pa_need_free)
            {
                rt_pages_free((void*)((char*)pa - PV_OFFSET), 0);
            }
        }
    }
}

void lwp_unmap_user_space(struct rt_lwp *lwp)
{
    struct lwp_avl_struct* node = RT_NULL;
    rt_mmu_info *m_info = &lwp->mmu_info;

    while ((node = lwp_map_find_first(lwp->map_area)) != 0)
    {
        struct rt_mm_area_struct *ma = (struct rt_mm_area_struct*)node->data;

        RT_ASSERT(ma->type < MM_AREA_TYPE_UNKNOW);
        unmap_range(lwp, (void*)ma->addr, ma->size, (int)(ma->type == MM_AREA_TYPE_AUTO));
        lwp_map_area_remove(&lwp->map_area, ma->addr);
    }
    rt_pages_free(m_info->vtable, 2);
}

static void *_lwp_map_user(struct rt_lwp *lwp, void *map_va, size_t map_size)
{
    void *va = RT_NULL;
    int ret = 0;
    rt_mmu_info *m_info = &lwp->mmu_info;

    va = rt_hw_mmu_map_auto(m_info, map_va, map_size, MMU_MAP_U_RWCB);
    if (!va)
    {
        return 0;
    }
    ret = lwp_map_area_insert(&lwp->map_area, (size_t)va, map_size, MM_AREA_TYPE_AUTO);
    if (ret != 0)
    {
        unmap_range(lwp, va, map_size, 1);
        return 0;
    }
    return va;
}

int lwp_unmap_user(struct rt_lwp *lwp, void *va)
{
    rt_base_t level = 0;
    struct lwp_avl_struct *ma_avl_node = RT_NULL;
    struct rt_mm_area_struct *ma = RT_NULL;

    level = rt_hw_interrupt_disable();
    ma_avl_node = lwp_map_find(lwp->map_area, (size_t)va);
    if (!ma_avl_node)
    {
        rt_hw_interrupt_enable(level);
        return -1;
    }
    ma = (struct rt_mm_area_struct *)ma_avl_node->data;
    RT_ASSERT(ma->type < MM_AREA_TYPE_UNKNOW);
    unmap_range(lwp, (void *)ma->addr, ma->size, (int)(ma->type == MM_AREA_TYPE_AUTO));
    lwp_map_area_remove(&lwp->map_area, (size_t)va);
    rt_hw_interrupt_enable(level);
    return 0;
}

int lwp_unmap_user_phy(struct rt_lwp *lwp, void *va)
{
    return lwp_unmap_user(lwp, va);
}

int lwp_unmap_user_type(struct rt_lwp *lwp, void *va)
{
    return lwp_unmap_user(lwp, va);
}

void *lwp_map_user(struct rt_lwp *lwp, void *map_va, size_t map_size)
{
    rt_base_t level = 0;
    void *ret = RT_NULL;
    size_t offset = 0;

    if (!map_size)
    {
        return 0;
    }
    offset = (size_t)map_va & ARCH_PAGE_MASK;
    map_size += (offset + ARCH_PAGE_SIZE - 1);
    map_size &= ~ARCH_PAGE_MASK;
    map_va = (void*)((size_t)map_va & ~ARCH_PAGE_MASK);

    level = rt_hw_interrupt_disable();
    ret = _lwp_map_user(lwp, map_va, map_size);
    rt_hw_interrupt_enable(level);
    if (ret)
    {
        ret = (void*)((char*)ret + offset);
    }
    return ret;
}

static void *_lwp_map_user_type(struct rt_lwp *lwp, void *map_va, void *map_pa, size_t map_size, int cached, int type)
{
    void *va = RT_NULL;
    rt_mmu_info *m_info = &lwp->mmu_info;
    size_t attr = 0;
    int ret = 0;

    if (cached)
    {
        attr = MMU_MAP_U_RWCB;
    }
    else
    {
        attr = MMU_MAP_U_RW;
    }

    va = rt_hw_mmu_map(m_info, map_va, map_pa, map_size, attr);
    ret = lwp_map_area_insert(&lwp->map_area, (size_t)va, map_size, type);
    if (ret != 0)
    {
        unmap_range(lwp, va, map_size, 0);
        return 0;
    }
    return va;
}

void *lwp_map_user_type(struct rt_lwp *lwp, void *map_va, void *map_pa, size_t map_size, int cached, int type)
{
    rt_base_t level = 0;
    void *ret = RT_NULL;
    size_t offset = 0;

    if (!map_size)
    {
        return 0;
    }
    if (map_va)
    {
        if (((size_t)map_va & ARCH_PAGE_MASK) != ((size_t)map_pa & ARCH_PAGE_MASK))
        {
            return 0;
        }
    }
    offset = (size_t)map_pa & ARCH_PAGE_MASK;
    map_size += (offset + ARCH_PAGE_SIZE - 1);
    map_size &= ~ARCH_PAGE_MASK;
    map_pa = (void*)((size_t)map_pa & ~ARCH_PAGE_MASK);

    level = rt_hw_interrupt_disable();
    ret = _lwp_map_user_type(lwp, map_va, map_pa, map_size, cached, type);
    rt_hw_interrupt_enable(level);
    if (ret)
    {
        ret = (void*)((char*)ret + offset);
    }
    return ret;
}

void *lwp_map_user_phy(struct rt_lwp *lwp, void *map_va, void *map_pa, size_t map_size, int cached)
{
    return lwp_map_user_type(lwp, map_va, map_pa, map_size, cached, MM_AREA_TYPE_PHY);
}

int lwp_brk(void *addr)
{
    rt_base_t level = 0;
    int ret = -1;
    struct rt_lwp *lwp = RT_NULL;

    level = rt_hw_interrupt_disable();
    lwp = rt_thread_self()->lwp;

    if ((size_t)addr <= lwp->end_heap)
    {
        ret = (int)lwp->end_heap;
    }
    else
    {
        size_t size;
        void *va;

        size = (((size_t)addr - lwp->end_heap) + ARCH_PAGE_SIZE - 1) & ~ARCH_PAGE_MASK;
        va = lwp_map_user(lwp, (void*)lwp->end_heap, size);
        if (va)
        {
            lwp->end_heap += size;
            ret = 0;
        }
        else
        {
            ret = -1;
        }
    }
    rt_hw_interrupt_enable(level);
    return ret;
}

void* lwp_mmap2(void *addr, size_t length, int prot,
        int flags, int fd, off_t pgoffset)
{
    rt_base_t level = 0;
    void *ret = (void*)-1;
    struct rt_lwp *lwp = RT_NULL;

    level = rt_hw_interrupt_disable();
    if (fd == -1)
    {
        lwp = rt_thread_self()->lwp;
        ret = lwp_map_user(lwp, addr, length);
        if (!ret)
        {
            ret = (void*)-1;
        }
    }
    rt_hw_interrupt_enable(level);
    return ret;
}

int lwp_munmap(void *addr)
{
    rt_base_t level = 0;
    int ret = 0;
    struct rt_lwp *lwp = RT_NULL;

    level = rt_hw_interrupt_disable();
    lwp = rt_thread_self()->lwp;
    ret = lwp_unmap_user(lwp, addr);
    rt_hw_interrupt_enable(level);
    return ret;
}

size_t lwp_get_from_user(void *dst, void *src, size_t size)
{
    struct rt_lwp *lwp = RT_NULL;
    rt_mmu_info *m_info = RT_NULL;

    /* check src */
    if (src >= (void*)KERNEL_VADDR_START)
    {
        return 0;
    }
    if ((void*)((char*)src + size) > (void*)KERNEL_VADDR_START)
    {
        return 0;
    }

    lwp = lwp_self();
    if (!lwp)
    {
        return 0;
    }
    m_info = &lwp->mmu_info;

    return lwp_data_get(m_info, dst, src, size);
}

size_t lwp_put_to_user(void *dst, void *src, size_t size)
{
    struct rt_lwp *lwp = RT_NULL;
    rt_mmu_info *m_info = RT_NULL;

    /* check dst */
    if (dst >= (void*)KERNEL_VADDR_START)
    {
        return 0;
    }
    if ((void*)((char*)dst + size) > (void*)KERNEL_VADDR_START)
    {
        return 0;
    }

    lwp = lwp_self();
    if (!lwp)
    {
        return 0;
    }
    m_info = &lwp->mmu_info;
    return lwp_data_put(m_info, dst, src, size);
}

int lwp_user_accessable(void *addr, size_t size)
{
    void *addr_start = RT_NULL, *addr_end = RT_NULL, *next_page = RT_NULL;
    void *tmp_addr = RT_NULL;
    struct rt_lwp *lwp = lwp_self();
    rt_mmu_info *mmu_info = RT_NULL;

    if (!lwp)
    {
        return 0;
    }
    if (!size || !addr)
    {
        return 0;
    }
    addr_start = addr;
    addr_end = (void*)((char*)addr + size);
    if (addr_start >= (void*)KERNEL_VADDR_START)
    {
        return 0;
    }
    if (addr_start > (void *)KERNEL_VADDR_START)
    {
        return 0;
    }

    mmu_info = &lwp->mmu_info;
    next_page = (void*)(((size_t)addr_start + ARCH_PAGE_SIZE) & ~(ARCH_PAGE_SIZE - 1));
    do
    {
        size_t len = (char*)next_page - (char*)addr_start;

        if (size < len)
        {
            len = size;
        }
        tmp_addr = rt_hw_mmu_v2p(mmu_info, addr_start);
        if (!tmp_addr)
        {
            return 0;
        }
        addr_start = (void*)((char*)addr_start + len);
        size -= len;
        next_page = (void*)((char*)next_page + ARCH_PAGE_SIZE);
    } while (addr_start < addr_end);
    return 1;
}

/* src is in mmu_info space, dst is in current thread space */
size_t lwp_data_get(rt_mmu_info *mmu_info, void *dst, void *src, size_t size)
{
    size_t copy_len = 0;
    void *addr_start = RT_NULL, *addr_end = RT_NULL, *next_page = RT_NULL;
    void *tmp_dst = RT_NULL, *tmp_src = RT_NULL;

    if (!size || !dst)
    {
        return 0;
    }
    tmp_dst = dst;
    addr_start = src;
    addr_end = (void*)((char*)src + size);
    next_page = (void*)(((size_t)addr_start + ARCH_PAGE_SIZE) & ~(ARCH_PAGE_SIZE - 1));
    do
    {
        size_t len = (char*)next_page - (char*)addr_start;

        if (size < len)
        {
            len = size;
        }
        tmp_src = rt_hw_mmu_v2p(mmu_info, addr_start);
        if (!tmp_src)
        {
            break;
        }
        tmp_src = (void*)((char*)rt_hw_mmu_v2p(mmu_info, addr_start) - PV_OFFSET);
        rt_memcpy(tmp_dst, tmp_src, len);
        tmp_dst = (void*)((char*)tmp_dst + len);
        addr_start = (void*)((char*)addr_start + len);
        size -= len;
        next_page = (void*)((char*)next_page + ARCH_PAGE_SIZE);
        copy_len += len;
    } while (addr_start < addr_end);
    return copy_len;
}

/* dst is in mmu_info space, src is in current thread space */
size_t lwp_data_put(rt_mmu_info *mmu_info, void *dst, void *src, size_t size)
{
    size_t copy_len = 0;
    void *addr_start = RT_NULL, *addr_end = RT_NULL, *next_page = RT_NULL;
    void *tmp_dst = RT_NULL, *tmp_src = RT_NULL;

    if (!size || !dst)
    {
        return 0;
    }
    tmp_src = src;
    addr_start = dst;
    addr_end = (void*)((char*)dst + size);
    next_page = (void*)(((size_t)addr_start + ARCH_PAGE_SIZE) & ~(ARCH_PAGE_SIZE - 1));
    do
    {
        size_t len = (char*)next_page - (char*)addr_start;

        if (size < len)
        {
            len = size;
        }
        tmp_dst = rt_hw_mmu_v2p(mmu_info, addr_start);
        if (!tmp_dst)
        {
            break;
        }
        tmp_dst = (void*)((char*)rt_hw_mmu_v2p(mmu_info, addr_start) - PV_OFFSET);
        rt_memcpy(tmp_dst, tmp_src, len);
        tmp_src = (void*)((char*)tmp_src + len);
        addr_start = (void*)((char*)addr_start + len);
        size -= len;
        next_page = (void*)((char*)next_page + ARCH_PAGE_SIZE);
        copy_len += len;
    } while (addr_start < addr_end);
    return copy_len;
}

void lwp_data_cache_flush(rt_mmu_info *mmu_info, void *vaddr, size_t size)
{
    void *paddr = RT_NULL;

    paddr = rt_hw_mmu_v2p(mmu_info, vaddr);
    paddr = (void*)((char*)paddr - PV_OFFSET);

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, paddr, size);
}
#endif
