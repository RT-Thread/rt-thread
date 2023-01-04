/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-28     Jesven       first version
 * 2021-02-06     lizhirui     fixed fixed vtable size problem
 * 2021-02-12     lizhirui     add 64-bit support for lwp_brk
 * 2021-02-19     lizhirui     add riscv64 support for lwp_user_accessable and lwp_get_from_user
 * 2021-06-07     lizhirui     modify user space bound check
 */

#include <rtthread.h>
#include <rthw.h>

#ifdef ARCH_MM_MMU

#include <mmu.h>
#include <page.h>
#include <lwp_mm_area.h>
#include <lwp_user_mm.h>
#include <lwp_arch.h>
#include <lwp_mm.h>

int lwp_user_space_init(struct rt_lwp *lwp)
{
    return arch_user_space_init(lwp);
}

#ifdef LWP_ENABLE_ASID
void rt_hw_mmu_switch(void *mtable, unsigned int pid, unsigned int asid);
#else
void rt_hw_mmu_switch(void *mtable);
#endif
void *rt_hw_mmu_tbl_get(void);
void lwp_mmu_switch(struct rt_thread *thread)
{
    struct rt_lwp *l = RT_NULL;
    void *pre_mmu_table = RT_NULL, *new_mmu_table = RT_NULL;

    if (thread->lwp)
    {
        l = (struct rt_lwp *)thread->lwp;
        new_mmu_table = (void *)((char *)l->mmu_info.vtable + l->mmu_info.pv_off);
    }
    else
    {
        new_mmu_table = arch_kernel_mmu_table_get();
    }

    pre_mmu_table = rt_hw_mmu_tbl_get();
    if (pre_mmu_table != new_mmu_table)
    {
#ifdef LWP_ENABLE_ASID
        rt_hw_mmu_switch(new_mmu_table, l ? l->pid : 0, arch_get_asid(l));
#else
        rt_hw_mmu_switch(new_mmu_table);
#endif
    }
}

static void unmap_range(struct rt_lwp *lwp, void *addr, size_t size, int pa_need_free)
{
    void *va = RT_NULL, *pa = RT_NULL;
    int i = 0;

    for (va = addr, i = 0; i < size; va = (void *)((char *)va + ARCH_PAGE_SIZE), i += ARCH_PAGE_SIZE)
    {
        pa = rt_hw_mmu_v2p(&lwp->mmu_info, va);
        if (pa)
        {
            rt_hw_mmu_unmap(&lwp->mmu_info, va, ARCH_PAGE_SIZE);
            if (pa_need_free)
            {
                rt_pages_free((void *)((char *)pa - PV_OFFSET), 0);
            }
        }
    }
}

void lwp_unmap_user_space(struct rt_lwp *lwp)
{
    struct lwp_avl_struct *node = RT_NULL;

    while ((node = lwp_map_find_first(lwp->map_area)) != 0)
    {
        struct rt_mm_area_struct *ma = (struct rt_mm_area_struct *)node->data;
        int pa_need_free = 0;

        RT_ASSERT(ma->type < MM_AREA_TYPE_UNKNOW);

        switch (ma->type)
        {
            case MM_AREA_TYPE_DATA:
            case MM_AREA_TYPE_TEXT:
                pa_need_free = 1;
                break;
            case MM_AREA_TYPE_SHM:
                lwp_shm_ref_dec(lwp, (void *)ma->addr);
                break;
        }
        unmap_range(lwp, (void *)ma->addr, ma->size, pa_need_free);
        lwp_map_area_remove(&lwp->map_area, ma->addr);
    }

    arch_user_space_vtable_free(lwp);
}

static void *_lwp_map_user(struct rt_lwp *lwp, void *map_va, size_t map_size, int text)
{
    void *va = RT_NULL;
    int ret = 0;
    rt_mmu_info *m_info = &lwp->mmu_info;
    int area_type;

    va = rt_hw_mmu_map_auto(m_info, map_va, map_size, MMU_MAP_U_RWCB);
    if (!va)
    {
        return 0;
    }

    area_type = text ? MM_AREA_TYPE_TEXT : MM_AREA_TYPE_DATA;
    ret = lwp_map_area_insert(&lwp->map_area, (size_t)va, map_size, area_type);
    if (ret != 0)
    {
        unmap_range(lwp, va, map_size, 1);
        return 0;
    }
    return va;
}

int lwp_unmap_user(struct rt_lwp *lwp, void *va)
{
    struct lwp_avl_struct *ma_avl_node = RT_NULL;
    struct rt_mm_area_struct *ma = RT_NULL;
    int pa_need_free = 0;

    rt_mm_lock();
    va = (void *)((size_t)va & ~ARCH_PAGE_MASK);
    ma_avl_node = lwp_map_find(lwp->map_area, (size_t)va);
    if (!ma_avl_node)
    {
        rt_mm_unlock();
        return -1;
    }
    ma = (struct rt_mm_area_struct *)ma_avl_node->data;

    RT_ASSERT(ma->type < MM_AREA_TYPE_UNKNOW);
    if ((ma->type == MM_AREA_TYPE_DATA) || (ma->type == MM_AREA_TYPE_TEXT))
    {
        pa_need_free = 1;
    }
    unmap_range(lwp, (void *)ma->addr, ma->size, pa_need_free);
    lwp_map_area_remove(&lwp->map_area, (size_t)va);
    rt_mm_unlock();
    return 0;
}

int lwp_dup_user(struct lwp_avl_struct *ptree, void *arg)
{
    struct rt_lwp *self_lwp = lwp_self();
    struct rt_lwp *new_lwp = (struct rt_lwp *)arg;
    struct rt_mm_area_struct *ma = (struct rt_mm_area_struct *)ptree->data;
    void *pa = RT_NULL;
    void *va = RT_NULL;

    switch (ma->type)
    {
        case MM_AREA_TYPE_PHY:
            pa = rt_hw_mmu_v2p(&self_lwp->mmu_info, (void *)ma->addr);
            va = lwp_map_user_type(new_lwp, (void *)ma->addr, pa, ma->size, 0, MM_AREA_TYPE_PHY);
            break;
        case MM_AREA_TYPE_PHY_CACHED:
            pa = rt_hw_mmu_v2p(&self_lwp->mmu_info, (void *)ma->addr);
            va = lwp_map_user_type(new_lwp, (void *)ma->addr, pa, ma->size, 0, MM_AREA_TYPE_PHY_CACHED);
            break;
        case MM_AREA_TYPE_SHM:
            va = (void *)ma->addr;
            if (lwp_shm_ref_inc(self_lwp, va) > 0)
            {
                pa = rt_hw_mmu_v2p(&self_lwp->mmu_info, va);
                va = lwp_map_user_type(new_lwp, va, pa, ma->size, 1, MM_AREA_TYPE_SHM);
            }
            break;
        case MM_AREA_TYPE_DATA:
            va = lwp_map_user(new_lwp, (void *)ma->addr, ma->size, 0);
            if (va == (void *)ma->addr)
            {
                lwp_data_put(&new_lwp->mmu_info, va, va, ma->size);
            }
            break;
        case MM_AREA_TYPE_TEXT:
            {
                char *addr = (char *)ma->addr;
                size_t size = ma->size;

                while (size)
                {
                    pa = rt_hw_mmu_v2p(&self_lwp->mmu_info, (void *)addr);
                    rt_page_ref_inc((char *)pa - self_lwp->mmu_info.pv_off, 0);
                    va = lwp_map_user_type(new_lwp, addr, pa, ARCH_PAGE_SIZE, 1, MM_AREA_TYPE_TEXT);
                    if (va != addr)
                    {
                        return -1;
                    }
                    addr += ARCH_PAGE_SIZE;
                    size -= ARCH_PAGE_SIZE;
                }
                va = (void *)ma->addr;
            }
            break;
        default:
            RT_ASSERT(0);
            break;
    }
    if (va != (void *)ma->addr)
    {
        return -1;
    }
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

void *lwp_map_user(struct rt_lwp *lwp, void *map_va, size_t map_size, int text)
{
    void *ret = RT_NULL;
    size_t offset = 0;

    if (!map_size)
    {
        return 0;
    }
    offset = (size_t)map_va & ARCH_PAGE_MASK;
    map_size += (offset + ARCH_PAGE_SIZE - 1);
    map_size &= ~ARCH_PAGE_MASK;
    map_va = (void *)((size_t)map_va & ~ARCH_PAGE_MASK);

    rt_mm_lock();
    ret = _lwp_map_user(lwp, map_va, map_size, text);
    rt_mm_unlock();
    if (ret)
    {
        ret = (void *)((char *)ret + offset);
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
        if (type == MM_AREA_TYPE_PHY)
        {
            type = MM_AREA_TYPE_PHY_CACHED;
        }
    }
    else
    {
        attr = MMU_MAP_U_RW;
    }

    va = rt_hw_mmu_map(m_info, map_va, map_pa, map_size, attr);
    if (va)
    {
        ret = lwp_map_area_insert(&lwp->map_area, (size_t)va, map_size, type);
        if (ret != 0)
        {
            unmap_range(lwp, va, map_size, 0);
            return 0;
        }
    }
    return va;
}

void *lwp_map_user_type(struct rt_lwp *lwp, void *map_va, void *map_pa, size_t map_size, int cached, int type)
{
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
    map_pa = (void *)((size_t)map_pa & ~ARCH_PAGE_MASK);

    rt_mm_lock();
    ret = _lwp_map_user_type(lwp, map_va, map_pa, map_size, cached, type);
    rt_mm_unlock();
    if (ret)
    {
        ret = (void *)((char *)ret + offset);
    }
    return ret;
}

void *lwp_map_user_phy(struct rt_lwp *lwp, void *map_va, void *map_pa, size_t map_size, int cached)
{
    return lwp_map_user_type(lwp, map_va, map_pa, map_size, cached, MM_AREA_TYPE_PHY);
}

rt_base_t lwp_brk(void *addr)
{
    rt_base_t ret = -1;
    struct rt_lwp *lwp = RT_NULL;

    rt_mm_lock();
    lwp = rt_thread_self()->lwp;

    if ((size_t)addr <= lwp->end_heap)
    {
        ret = (rt_base_t)lwp->end_heap;
    }
    else
    {
        size_t size = 0;
        void *va = RT_NULL;

        if ((size_t)addr <= USER_HEAP_VEND)
        {
            size = (((size_t)addr - lwp->end_heap) + ARCH_PAGE_SIZE - 1) & ~ARCH_PAGE_MASK;
            va = lwp_map_user(lwp, (void *)lwp->end_heap, size, 0);
        }
        if (va)
        {
            lwp->end_heap += size;
            ret = lwp->end_heap;
        }
    }
    rt_mm_unlock();
    return ret;
}

#define MAP_ANONYMOUS  0x20

void* lwp_mmap2(void *addr, size_t length, int prot,
        int flags, int fd, off_t pgoffset)
{
    void *ret = (void *)-1;

    if (fd == -1)
    {
        rt_mm_lock();
        ret = lwp_map_user(lwp_self(), addr, length, 0);
        rt_mm_unlock();

        if (ret)
        {
            if ((flags & MAP_ANONYMOUS) != 0)
            {
                rt_memset(ret, 0, length);
            }
        }
        else
        {
            ret = (void *)-1;
        }
    }
    else
    {
        struct dfs_fd *d;

        d = fd_get(fd);
        if (d && d->vnode->type == FT_DEVICE)
        {
            struct dfs_mmap2_args mmap2;

            mmap2.addr = addr;
            mmap2.length = length;
            mmap2.prot = prot;
            mmap2.flags = flags;
            mmap2.pgoffset = pgoffset;
            mmap2.ret = (void*) -1;

            if (dfs_file_mmap2(d, &mmap2) == 0)
            {
                ret = mmap2.ret;
            }
        }
    }

    return ret;
}

int lwp_munmap(void *addr)
{
    int ret = 0;

    rt_mm_lock();
    ret = lwp_unmap_user(lwp_self(), addr);
    rt_mm_unlock();

    return ret;
}

size_t lwp_get_from_user(void *dst, void *src, size_t size)
{
    struct rt_lwp *lwp = RT_NULL;
    rt_mmu_info *m_info = RT_NULL;

    /* check src */

    if (src < (void *)USER_VADDR_START)
    {
        return 0;
    }
    if (src >= (void *)USER_VADDR_TOP)
    {
        return 0;
    }
    if ((void *)((char *)src + size) > (void *)USER_VADDR_TOP)
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
    if (dst < (void *)USER_VADDR_START)
    {
        return 0;
    }
    if (dst >= (void *)USER_VADDR_TOP)
    {
        return 0;
    }
    if ((void *)((char *)dst + size) > (void *)USER_VADDR_TOP)
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
    addr_end = (void *)((char *)addr + size);

#ifdef ARCH_RISCV64
    if(addr_start < (void *)USER_VADDR_START)
    {
        return 0;
    }
#else
    if (addr_start >= (void *)USER_VADDR_TOP)
    {
        return 0;
    }
    if (addr_end > (void *)USER_VADDR_TOP)
    {
        return 0;
    }
#endif

    mmu_info = &lwp->mmu_info;
    next_page = (void *)(((size_t)addr_start + ARCH_PAGE_SIZE) & ~(ARCH_PAGE_SIZE - 1));
    do
    {
        size_t len = (char *)next_page - (char *)addr_start;

        if (size < len)
        {
            len = size;
        }
        tmp_addr = rt_hw_mmu_v2p(mmu_info, addr_start);
        if (!tmp_addr)
        {
            return 0;
        }
        addr_start = (void *)((char *)addr_start + len);
        size -= len;
        next_page = (void *)((char *)next_page + ARCH_PAGE_SIZE);
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
    addr_end = (void *)((char *)src + size);
    next_page = (void *)(((size_t)addr_start + ARCH_PAGE_SIZE) & ~(ARCH_PAGE_SIZE - 1));
    do
    {
        size_t len = (char *)next_page - (char *)addr_start;

        if (size < len)
        {
            len = size;
        }
        tmp_src = rt_hw_mmu_v2p(mmu_info, addr_start);
        if (!tmp_src)
        {
            break;
        }
        tmp_src = (void *)((char *)tmp_src - PV_OFFSET);
        rt_memcpy(tmp_dst, tmp_src, len);
        tmp_dst = (void *)((char *)tmp_dst + len);
        addr_start = (void *)((char *)addr_start + len);
        size -= len;
        next_page = (void *)((char *)next_page + ARCH_PAGE_SIZE);
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
    addr_end = (void *)((char *)dst + size);
    next_page = (void *)(((size_t)addr_start + ARCH_PAGE_SIZE) & ~(ARCH_PAGE_SIZE - 1));
    do
    {
        size_t len = (char *)next_page - (char *)addr_start;

        if (size < len)
        {
            len = size;
        }
        tmp_dst = rt_hw_mmu_v2p(mmu_info, addr_start);
        if (!tmp_dst)
        {
            break;
        }
        tmp_dst = (void *)((char *)tmp_dst - PV_OFFSET);
        rt_memcpy(tmp_dst, tmp_src, len);
        tmp_src = (void *)((char *)tmp_src + len);
        addr_start = (void *)((char *)addr_start + len);
        size -= len;
        next_page = (void *)((char *)next_page + ARCH_PAGE_SIZE);
        copy_len += len;
    } while (addr_start < addr_end);
    return copy_len;
}

void lwp_data_cache_flush(rt_mmu_info *mmu_info, void *vaddr, size_t size)
{
    void *paddr = RT_NULL;

    paddr = rt_hw_mmu_v2p(mmu_info, vaddr);
    paddr = (void *)((char *)paddr - PV_OFFSET);

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, paddr, size);
}
#endif
