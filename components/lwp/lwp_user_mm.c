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
 * 2022-12-25     wangxiaoyao  adapt to new mm
 * 2023-09-13     Shell        Add lwp_memcpy and support run-time choice of memcpy base on memory attr
 */

#include <rtthread.h>
#include <rthw.h>
#include <string.h>

#ifdef ARCH_MM_MMU

#include <lwp.h>
#include <lwp_arch.h>
#include <lwp_mm.h>
#include <lwp_user_mm.h>

#include <mm_aspace.h>
#include <mm_fault.h>
#include <mm_flag.h>
#include <mm_page.h>
#include <mmu.h>
#include <page.h>

#ifdef RT_USING_MUSLLIBC
#include "libc_musl.h"
#endif

#define DBG_TAG "LwP"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

static void _init_lwp_objs(struct rt_lwp_objs *lwp_objs, rt_aspace_t aspace);

int lwp_user_space_init(struct rt_lwp *lwp, rt_bool_t is_fork)
{
    int err = -RT_ENOMEM;

    lwp->lwp_obj = rt_malloc(sizeof(struct rt_lwp_objs));
    if (lwp->lwp_obj)
    {
        _init_lwp_objs(lwp->lwp_obj, lwp->aspace);

        err = arch_user_space_init(lwp);
        if (!is_fork && err == RT_EOK)
        {
            void *addr = (void *)USER_STACK_VSTART;
            err = rt_aspace_map(lwp->aspace, &addr,
                                USER_STACK_VEND - USER_STACK_VSTART,
                                MMU_MAP_U_RWCB, 0, &lwp->lwp_obj->mem_obj, 0);
        }
    }

    return err;
}

void lwp_aspace_switch(struct rt_thread *thread)
{
    struct rt_lwp *lwp = RT_NULL;
    rt_aspace_t aspace;
    void *from_tbl;

    if (thread->lwp)
    {
        lwp = (struct rt_lwp *)thread->lwp;
        aspace = lwp->aspace;
    }
    else
        aspace = &rt_kernel_space;

    from_tbl = rt_hw_mmu_tbl_get();
    if (aspace->page_table != from_tbl)
    {
        rt_hw_aspace_switch(aspace);
    }
}

void lwp_unmap_user_space(struct rt_lwp *lwp)
{
    arch_user_space_free(lwp);
    rt_free(lwp->lwp_obj);
}

static const char *user_get_name(rt_varea_t varea)
{
    char *name;
    if (varea->flag & MMF_TEXT)
    {
        name = "user.text";
    }
    else
    {
        if (varea->start == (void *)USER_STACK_VSTART)
        {
            name = "user.stack";
        }
        else if (varea->start >= (void *)USER_HEAP_VADDR &&
                 varea->start < (void *)USER_HEAP_VEND)
        {
            name = "user.heap";
        }
        else
        {
            name = "user.data";
        }
    }
    return name;
}

#define NO_AUTO_FETCH               0x1
#define VAREA_CAN_AUTO_FETCH(varea) (!((rt_ubase_t)((varea)->data) & NO_AUTO_FETCH))

static void _user_do_page_fault(struct rt_varea *varea,
                                struct rt_aspace_fault_msg *msg)
{
    struct rt_lwp_objs *lwp_objs;
    lwp_objs = rt_container_of(varea->mem_obj, struct rt_lwp_objs, mem_obj);

    if (lwp_objs->source)
    {
        char *paddr = rt_hw_mmu_v2p(lwp_objs->source, msg->fault_vaddr);
        if (paddr != ARCH_MAP_FAILED)
        {
            void *vaddr;
            vaddr = paddr - PV_OFFSET;

            if (!(varea->flag & MMF_TEXT))
            {
                void *cp = rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);
                if (cp)
                {
                    memcpy(cp, vaddr, ARCH_PAGE_SIZE);
                    rt_varea_pgmgr_insert(varea, cp);
                    msg->response.status = MM_FAULT_STATUS_OK;
                    msg->response.vaddr = cp;
                    msg->response.size = ARCH_PAGE_SIZE;
                }
                else
                {
                    LOG_W("%s: page alloc failed at %p", __func__,
                          varea->start);
                }
            }
            else
            {
                rt_page_t page = rt_page_addr2page(vaddr);
                page->ref_cnt += 1;
                rt_varea_pgmgr_insert(varea, vaddr);
                msg->response.status = MM_FAULT_STATUS_OK;
                msg->response.vaddr = vaddr;
                msg->response.size = ARCH_PAGE_SIZE;
            }
        }
        else if (!(varea->flag & MMF_TEXT))
        {
            /* if data segment not exist in source do a fallback */
            rt_mm_dummy_mapper.on_page_fault(varea, msg);
        }
    }
    else if (VAREA_CAN_AUTO_FETCH(varea))
    {
        /* if (!lwp_objs->source), no aspace as source data */
        rt_mm_dummy_mapper.on_page_fault(varea, msg);
    }
}

static void _init_lwp_objs(struct rt_lwp_objs *lwp_objs, rt_aspace_t aspace)
{
    if (lwp_objs)
    {
        /**
         * @brief one lwp_obj represent an base layout of page based memory in user space
         * This is useful on duplication. Where we only have a (lwp_objs and offset) to
         * provide identical memory. This is implemented by lwp_objs->source.
         */
        lwp_objs->source = NULL;
        lwp_objs->mem_obj.get_name = user_get_name;
        lwp_objs->mem_obj.hint_free = NULL;
        lwp_objs->mem_obj.on_page_fault = _user_do_page_fault;
        lwp_objs->mem_obj.on_page_offload = rt_mm_dummy_mapper.on_page_offload;
        lwp_objs->mem_obj.on_varea_open = rt_mm_dummy_mapper.on_varea_open;
        lwp_objs->mem_obj.on_varea_close = rt_mm_dummy_mapper.on_varea_close;
    }
}

static void *_lwp_map_user(struct rt_lwp *lwp, void *map_va, size_t map_size,
                           int text)
{
    void *va = map_va;
    int ret = 0;
    size_t flags = MMF_PREFETCH;
    if (text)
        flags |= MMF_TEXT;

    rt_mem_obj_t mem_obj = &lwp->lwp_obj->mem_obj;

    ret = rt_aspace_map(lwp->aspace, &va, map_size, MMU_MAP_U_RWCB, flags,
                        mem_obj, 0);
    if (ret != RT_EOK)
    {
        va = RT_NULL;
        LOG_I("lwp_map_user: failed to map %lx with size %lx with errno %d", map_va,
              map_size, ret);
    }

    return va;
}

int lwp_unmap_user(struct rt_lwp *lwp, void *va)
{
    int err = rt_aspace_unmap(lwp->aspace, va);

    return err;
}

static void _dup_varea(rt_varea_t varea, struct rt_lwp *src_lwp,
                       rt_aspace_t dst)
{
    char *vaddr = varea->start;
    char *vend = vaddr + varea->size;
    if (vaddr < (char *)USER_STACK_VSTART || vaddr >= (char *)USER_STACK_VEND)
    {
        while (vaddr != vend)
        {
            void *paddr;
            paddr = lwp_v2p(src_lwp, vaddr);
            if (paddr != ARCH_MAP_FAILED)
            {
                rt_aspace_load_page(dst, vaddr, 1);
            }
            vaddr += ARCH_PAGE_SIZE;
        }
    }
    else
    {
        while (vaddr != vend)
        {
            vend -= ARCH_PAGE_SIZE;
            void *paddr;
            paddr = lwp_v2p(src_lwp, vend);
            if (paddr != ARCH_MAP_FAILED)
            {
                rt_aspace_load_page(dst, vend, 1);
            }
            else
            {
                break;
            }
        }
    }
}

int lwp_dup_user(rt_varea_t varea, void *arg)
{
    int err;
    struct rt_lwp *self_lwp = lwp_self();
    struct rt_lwp *new_lwp = (struct rt_lwp *)arg;

    void *pa = RT_NULL;
    void *va = RT_NULL;
    rt_mem_obj_t mem_obj = varea->mem_obj;

    if (!mem_obj)
    {
        /* duplicate a physical mapping */
        pa = lwp_v2p(self_lwp, (void *)varea->start);
        RT_ASSERT(pa != ARCH_MAP_FAILED);
        struct rt_mm_va_hint hint = {.flags = MMF_MAP_FIXED,
                                     .limit_range_size = new_lwp->aspace->size,
                                     .limit_start = new_lwp->aspace->start,
                                     .prefer = varea->start,
                                     .map_size = varea->size};
        err = rt_aspace_map_phy(new_lwp->aspace, &hint, varea->attr,
                                MM_PA_TO_OFF(pa), &va);
        if (err != RT_EOK)
        {
            LOG_W("%s: aspace map failed at %p with size %p", __func__,
                  varea->start, varea->size);
        }
    }
    else
    {
        /* duplicate a mem_obj backing mapping */
        va = varea->start;
        err = rt_aspace_map(new_lwp->aspace, &va, varea->size, varea->attr,
                            varea->flag, &new_lwp->lwp_obj->mem_obj,
                            varea->offset);
        if (err != RT_EOK)
        {
            LOG_W("%s: aspace map failed at %p with size %p", __func__,
                  varea->start, varea->size);
        }
        else
        {
            /* loading page frames for !MMF_PREFETCH varea */
            if (!(varea->flag & MMF_PREFETCH))
            {
                _dup_varea(varea, self_lwp, new_lwp->aspace);
            }
        }
    }

    if (va != (void *)varea->start)
    {
        return -1;
    }
    return 0;
}

int lwp_unmap_user_phy(struct rt_lwp *lwp, void *va)
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

    ret = _lwp_map_user(lwp, map_va, map_size, text);

    if (ret)
    {
        ret = (void *)((char *)ret + offset);
    }
    return ret;
}

static inline size_t _flags_to_attr(size_t flags)
{
    size_t attr;

    if (flags & LWP_MAP_FLAG_NOCACHE)
    {
        attr = MMU_MAP_U_RW;
    }
    else
    {
        attr = MMU_MAP_U_RWCB;
    }

    return attr;
}

static inline mm_flag_t _flags_to_aspace_flag(size_t flags)
{
    mm_flag_t mm_flag = 0;

    return mm_flag;
}

static rt_varea_t _lwp_map_user_varea(struct rt_lwp *lwp, void *map_va, size_t map_size, size_t flags)
{
    void *va = map_va;
    int ret = 0;
    rt_mem_obj_t mem_obj = &lwp->lwp_obj->mem_obj;
    rt_varea_t varea;
    mm_flag_t mm_flags;
    size_t attr;

    varea = rt_malloc(sizeof(*varea));
    if (varea)
    {
        attr = _flags_to_attr(flags);
        mm_flags = _flags_to_aspace_flag(flags);
        ret = rt_aspace_map_static(lwp->aspace, varea, &va, map_size,
                                   attr, mm_flags, mem_obj, 0);
        /* let aspace handle the free of varea */
        varea->flag &= ~MMF_STATIC_ALLOC;
        /* don't apply auto fetch on this */
        varea->data = (void *)NO_AUTO_FETCH;
    }
    else
    {
        ret = -RT_ENOMEM;
    }

    if (ret != RT_EOK)
    {
        LOG_I("lwp_map_user: failed to map %lx with size %lx with errno %d", map_va,
              map_size, ret);
    }

    return varea;
}

static rt_varea_t _map_user_varea_ext(struct rt_lwp *lwp, void *map_va, size_t map_size, size_t flags)
{
    rt_varea_t varea = RT_NULL;
    size_t offset = 0;

    if (!map_size)
    {
        return 0;
    }
    offset = (size_t)map_va & ARCH_PAGE_MASK;
    map_size += (offset + ARCH_PAGE_SIZE - 1);
    map_size &= ~ARCH_PAGE_MASK;
    map_va = (void *)((size_t)map_va & ~ARCH_PAGE_MASK);

    varea = _lwp_map_user_varea(lwp, map_va, map_size, flags);

    return varea;
}

rt_varea_t lwp_map_user_varea_ext(struct rt_lwp *lwp, void *map_va, size_t map_size, size_t flags)
{
    return _map_user_varea_ext(lwp, map_va, map_size, flags);
}

rt_varea_t lwp_map_user_varea(struct rt_lwp *lwp, void *map_va, size_t map_size)
{
    return _map_user_varea_ext(lwp, map_va, map_size, LWP_MAP_FLAG_NONE);
}

void *lwp_map_user_phy(struct rt_lwp *lwp, void *map_va, void *map_pa,
                       size_t map_size, int cached)
{
    int err;
    char *va;
    size_t offset = 0;

    if (!map_size)
    {
        return 0;
    }
    if (map_va)
    {
        if (((size_t)map_va & ARCH_PAGE_MASK) !=
            ((size_t)map_pa & ARCH_PAGE_MASK))
        {
            return 0;
        }
    }
    offset = (size_t)map_pa & ARCH_PAGE_MASK;
    map_size += (offset + ARCH_PAGE_SIZE - 1);
    map_size &= ~ARCH_PAGE_MASK;
    map_pa = (void *)((size_t)map_pa & ~ARCH_PAGE_MASK);

    struct rt_mm_va_hint hint = {.flags = MMF_MAP_FIXED,
                                 .limit_range_size = lwp->aspace->size,
                                 .limit_start = lwp->aspace->start,
                                 .prefer = map_va,
                                 .map_size = map_size};
    rt_size_t attr = cached ? MMU_MAP_U_RWCB : MMU_MAP_U_RW;

    err =
        rt_aspace_map_phy(lwp->aspace, &hint, attr, MM_PA_TO_OFF(map_pa), (void **)&va);
    if (err != RT_EOK)
    {
        va = RT_NULL;
        LOG_W("%s", __func__);
    }
    else
    {
        va += offset;
    }

    return va;
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
            size = (((size_t)addr - lwp->end_heap) + ARCH_PAGE_SIZE - 1) &
                   ~ARCH_PAGE_MASK;
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

void *lwp_mmap2(void *addr, size_t length, int prot, int flags, int fd,
                off_t pgoffset)
{
    void *ret = (void *)-1;

    if (fd == -1)
    {

        ret = lwp_map_user(lwp_self(), addr, length, 0);

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
        struct dfs_file *d;

        d = fd_get(fd);
        if (d && d->vnode->type == FT_DEVICE)
        {
            struct dfs_mmap2_args mmap2;

            mmap2.addr = addr;
            mmap2.length = length;
            mmap2.prot = prot;
            mmap2.flags = flags;
            mmap2.pgoffset = pgoffset;
            mmap2.ret = (void *)-1;

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

    return lwp_data_get(lwp, dst, src, size);
}

size_t lwp_put_to_user(void *dst, void *src, size_t size)
{
    struct rt_lwp *lwp = RT_NULL;

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

    return lwp_data_put(lwp, dst, src, size);
}

rt_inline rt_bool_t _in_user_space(const char *addr)
{
    return (addr >= (char *)USER_VADDR_START && addr < (char *)USER_VADDR_TOP);
}

rt_inline rt_bool_t _can_unaligned_access(const char *addr)
{
    return rt_kmem_v2p((char *)addr) - PV_OFFSET == addr;
}

void *lwp_memcpy(void * __restrict dst, const void * __restrict src, size_t size)
{
    void *rc = dst;
    long len;

    if (_in_user_space(dst))
    {
        if (!_in_user_space(src))
        {
            len = lwp_put_to_user(dst, (void *)src, size);
            if (!len)
            {
                LOG_E("lwp_put_to_user(lwp=%p, dst=%p,src=%p,size=0x%lx) failed", lwp_self(), dst, src, size);
            }
        }
        else
        {
            /* not support yet */
            LOG_W("%s(dst=%p,src=%p,size=0x%lx): operation not support", dst, src, size, __func__);
        }
    }
    else
    {
        if (_in_user_space(src))
        {
            len = lwp_get_from_user(dst, (void *)src, size);
            if (!len)
            {
                LOG_E("lwp_get_from_user(lwp=%p, dst=%p,src=%p,size=0x%lx) failed", lwp_self(), dst, src, size);
            }
        }
        else
        {
            if (_can_unaligned_access(dst) && _can_unaligned_access(src))
            {
                rc = memcpy(dst, src, size);
            }
            else
            {
                rt_memcpy(dst, src, size);
            }
        }
    }

    return rc;
}

int lwp_user_accessible_ext(struct rt_lwp *lwp, void *addr, size_t size)
{
    void *addr_start = RT_NULL, *addr_end = RT_NULL, *next_page = RT_NULL;
    void *tmp_addr = RT_NULL;

    if (!lwp)
    {
        return RT_FALSE;
    }
    if (!size || !addr)
    {
        return RT_FALSE;
    }
    addr_start = addr;
    addr_end = (void *)((char *)addr + size);

#ifdef ARCH_RISCV64
    if (addr_start < (void *)USER_VADDR_START)
    {
        return RT_FALSE;
    }
#else
    if (addr_start >= (void *)USER_VADDR_TOP)
    {
        return RT_FALSE;
    }
    if (addr_end > (void *)USER_VADDR_TOP)
    {
        return RT_FALSE;
    }
#endif

    next_page =
        (void *)(((size_t)addr_start + ARCH_PAGE_SIZE) & ~(ARCH_PAGE_SIZE - 1));
    do
    {
        size_t len = (char *)next_page - (char *)addr_start;

        if (size < len)
        {
            len = size;
        }
        tmp_addr = lwp_v2p(lwp, addr_start);
        if (tmp_addr == ARCH_MAP_FAILED)
        {
            if ((rt_ubase_t)addr_start >= USER_STACK_VSTART && (rt_ubase_t)addr_start < USER_STACK_VEND)
            {
                struct rt_aspace_fault_msg msg = {
                    .fault_op = MM_FAULT_OP_WRITE,
                    .fault_type = MM_FAULT_TYPE_PAGE_FAULT,
                    .fault_vaddr = addr_start,
                };
                if (!rt_aspace_fault_try_fix(lwp->aspace, &msg))
                    return RT_FALSE;
            }
            else
                return RT_FALSE;
        }
        addr_start = (void *)((char *)addr_start + len);
        size -= len;
        next_page = (void *)((char *)next_page + ARCH_PAGE_SIZE);
    } while (addr_start < addr_end);
    return RT_TRUE;
}

int lwp_user_accessable(void *addr, size_t size)
{
    return lwp_user_accessible_ext(lwp_self(), addr, size);
}

/* src is in mmu_info space, dst is in current thread space */
size_t lwp_data_get(struct rt_lwp *lwp, void *dst, void *src, size_t size)
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
    next_page =
        (void *)(((size_t)addr_start + ARCH_PAGE_SIZE) & ~(ARCH_PAGE_SIZE - 1));
    do
    {
        size_t len = (char *)next_page - (char *)addr_start;

        if (size < len)
        {
            len = size;
        }
        tmp_src = lwp_v2p(lwp, addr_start);
        if (tmp_src == ARCH_MAP_FAILED)
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

/* dst is in kernel space, src is in current thread space */
size_t lwp_data_put(struct rt_lwp *lwp, void *dst, void *src, size_t size)
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
    next_page =
        (void *)(((size_t)addr_start + ARCH_PAGE_SIZE) & ~(ARCH_PAGE_SIZE - 1));
    do
    {
        size_t len = (char *)next_page - (char *)addr_start;

        if (size < len)
        {
            len = size;
        }
        tmp_dst = lwp_v2p(lwp, addr_start);
        if (tmp_dst == ARCH_MAP_FAILED)
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

size_t lwp_user_strlen_ext(struct rt_lwp *lwp, const char *s)
{
    int len = 0;
    char *new_buf = RT_NULL;
    void *addr_start = RT_NULL;
    int size = 0;
    int err = 0;

    if (s == RT_NULL)
        return 0;

    addr_start = (void *)s;
    new_buf = rt_malloc(ARCH_PAGE_SIZE);

    if (lwp == RT_NULL)
    {
        LOG_W("%s: lwp is NULL", __func__);
        return -1;
    }

    err = lwp_data_get(lwp, new_buf, addr_start, ARCH_PAGE_SIZE);
    if (err == 0)
    {
        rt_free(new_buf);
        return -1;
    }

    while (new_buf[size] != '\0')
    {
        len ++;
        if (size == (ARCH_PAGE_SIZE -1))
        {
            err = lwp_data_get(lwp, new_buf, addr_start + len, ARCH_PAGE_SIZE);
            if (err == 0)
            {
                rt_free(new_buf);
                return -1;
            }

            size = 0;
        }
        else
        {
            size ++;
        }
    }

    rt_free(new_buf);

    return len;
}

size_t lwp_user_strlen(const char *s)
{
    struct rt_lwp *lwp = RT_NULL;

    lwp = lwp_self();
    RT_ASSERT(lwp != RT_NULL);

    return lwp_user_strlen_ext(lwp, s);
}

#endif
