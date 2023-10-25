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
 * 2023-08-12     Shell        Fix parameter passing of lwp_mmap()/lwp_munmap()
 * 2023-08-29     Shell        Add API accessible()/data_get()/data_set()/data_put()
 * 2023-09-13     Shell        Add lwp_memcpy and support run-time choice of memcpy base on memory attr
 * 2023-09-19     Shell        add lwp_user_memory_remap_to_kernel
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

#define DBG_TAG "LwP.mman"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <stdlib.h>

#define STACK_OBJ _null_object

static const char *_null_get_name(rt_varea_t varea)
{
    return "null";
}

static void _null_page_fault(struct rt_varea *varea,
                             struct rt_aspace_fault_msg *msg)
{
    static void *null_page;

    if (!null_page)
    {
        null_page = rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);
        if (null_page)
            memset(null_page, 0, ARCH_PAGE_SIZE);
        else
            return;
    }

    msg->response.status = MM_FAULT_STATUS_OK;
    msg->response.size = ARCH_PAGE_SIZE;
    msg->response.vaddr = null_page;
}

static rt_err_t _null_shrink(rt_varea_t varea, void *new_start, rt_size_t size)
{
    return RT_EOK;
}

static rt_err_t _null_split(struct rt_varea *existed, void *unmap_start, rt_size_t unmap_len, struct rt_varea *subset)
{
    return RT_EOK;
}

static rt_err_t _null_expand(struct rt_varea *varea, void *new_vaddr, rt_size_t size)
{
    return RT_EOK;
}

static void _null_page_read(struct rt_varea *varea, struct rt_aspace_io_msg *msg)
{
    void *dest = msg->buffer_vaddr;
    memset(dest, 0, ARCH_PAGE_SIZE);

    msg->response.status = MM_FAULT_STATUS_OK;
    return ;
}

static void _null_page_write(struct rt_varea *varea, struct rt_aspace_io_msg *msg)
{
    /* write operation is not allowed */
    msg->response.status = MM_FAULT_STATUS_UNRECOVERABLE;
    return ;
}

static struct rt_mem_obj _null_object = {
    .get_name = _null_get_name,
    .hint_free = RT_NULL,
    .on_page_fault = _null_page_fault,

    .page_read = _null_page_read,
    .page_write = _null_page_write,

    .on_varea_expand = _null_expand,
    .on_varea_shrink = _null_shrink,
    .on_varea_split = _null_split,
};

int lwp_user_space_init(struct rt_lwp *lwp, rt_bool_t is_fork)
{
    void *stk_addr;
    int err = -RT_ENOMEM;
    const size_t flags = MMF_MAP_PRIVATE;

    err = arch_user_space_init(lwp);
    if (err == RT_EOK)
    {
        if (!is_fork)
        {
            stk_addr = (void *)USER_STACK_VSTART;
            err = rt_aspace_map(lwp->aspace, &stk_addr,
                                USER_STACK_VEND - USER_STACK_VSTART,
                                MMU_MAP_U_RWCB, flags, &STACK_OBJ, 0);
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
}


static void *_lwp_map_user(struct rt_lwp *lwp, void *map_va, size_t map_size,
                           int text)
{
    void *va = map_va;
    int ret = 0;
    rt_size_t flags = MMF_PREFETCH;

    if (text)
        flags |= MMF_TEXT;
    if (va != RT_NULL)
        flags |= MMF_MAP_FIXED;

    ret = rt_aspace_map_private(lwp->aspace, &va, map_size, MMU_MAP_U_RWCB, flags);
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

/** fork the src_lwp->aspace in current */
int lwp_fork_aspace(struct rt_lwp *dest_lwp, struct rt_lwp *src_lwp)
{
    int err;
    err = rt_aspace_fork(&src_lwp->aspace, &dest_lwp->aspace);
    if (!err)
    {
        /* do a explicit aspace switch if the page table is changed */
        lwp_aspace_switch(rt_thread_self());
    }
    return err;
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
    if (flags & LWP_MAP_FLAG_MAP_FIXED)
        mm_flag |= MMF_MAP_FIXED;
    if (flags & LWP_MAP_FLAG_PREFETCH)
        mm_flag |= MMF_PREFETCH;

    return mm_flag;
}

static rt_varea_t _lwp_map_user_varea(struct rt_lwp *lwp, void *map_va, size_t map_size, size_t flags)
{
    void *va = map_va;
    int ret = 0;
    rt_varea_t varea = RT_NULL;
    mm_flag_t mm_flags;
    size_t attr;

    attr = _flags_to_attr(flags);
    mm_flags = _flags_to_aspace_flag(flags);
    ret = rt_aspace_map_private(lwp->aspace, &va, map_size,
                                attr, mm_flags);
    if (ret == RT_EOK)
    {
        varea = rt_aspace_query(lwp->aspace, va);
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
    size_t offset = 0;

    if (!map_size)
    {
        return 0;
    }
    offset = (size_t)map_va & ARCH_PAGE_MASK;
    map_size += (offset + ARCH_PAGE_SIZE - 1);
    map_size &= ~ARCH_PAGE_MASK;
    map_va = (void *)((size_t)map_va & ~ARCH_PAGE_MASK);

    return _lwp_map_user_varea(lwp, map_va, map_size, flags);
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

    struct rt_mm_va_hint hint = {.flags = 0,
                                 .limit_range_size = lwp->aspace->size,
                                 .limit_start = lwp->aspace->start,
                                 .prefer = map_va,
                                 .map_size = map_size};
    if (map_va != RT_NULL)
        hint.flags |= MMF_MAP_FIXED;

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
    rt_varea_t varea = RT_NULL;
    struct rt_lwp *lwp = RT_NULL;
    size_t size = 0;

    lwp = lwp_self();

    if ((size_t)addr == RT_NULL)
    {
        addr = (char *)lwp->end_heap + 1;
    }

    if ((size_t)addr <= lwp->end_heap && (size_t)addr > USER_HEAP_VADDR)
    {
        ret = (size_t)addr;
    }
    else if ((size_t)addr <= USER_HEAP_VEND)
    {
        size = RT_ALIGN((size_t)addr - lwp->end_heap, ARCH_PAGE_SIZE);
        varea = lwp_map_user_varea_ext(lwp, (void *)lwp->end_heap, size, LWP_MAP_FLAG_PREFETCH);
        if (varea)
        {
            lwp->end_heap = (long)(varea->start + varea->size);
            ret = lwp->end_heap;
        }
    }

    return ret;
}

rt_inline rt_mem_obj_t _get_mmap_obj(struct rt_lwp *lwp)
{
    return &_null_object;
}

rt_inline rt_bool_t _memory_threshold_ok(void)
{
    #define GUARDIAN_BITS (10)
    size_t total, free;

    rt_page_get_info(&total, &free);
    if (free * (0x1000) < 0x100000)
    {
        LOG_I("%s: low of system memory", __func__);
        return RT_FALSE;
    }

    return RT_TRUE;
}

rt_inline long _uflag_to_kernel(long flag)
{
    flag &= ~MMF_MAP_FIXED;
    flag &= ~MMF_MAP_PRIVATE;
    flag &= ~MMF_MAP_PRIVATE_DONT_SYNC;
    return flag;
}

rt_inline long _uattr_to_kernel(long attr)
{
    /* Warning: be careful with the case if user attribution is unwritable */
    return attr;
}

static void _prefetch_mmap(rt_aspace_t aspace, void *addr, long size)
{
    struct rt_aspace_fault_msg msg;

    msg.fault_op = MM_FAULT_OP_WRITE;
    msg.fault_type = MM_FAULT_TYPE_PAGE_FAULT;

    for (char *base = addr; size > 0; base += ARCH_PAGE_SIZE, size -= ARCH_PAGE_SIZE)
    {
        msg.fault_vaddr = base;
        msg.off = (long)base >> MM_PAGE_SHIFT;
        rt_aspace_fault_try_fix(aspace, &msg);
    }
    return ;
}

void *lwp_user_memory_remap_to_kernel(rt_lwp_t lwp, void *uaddr, size_t length)
{
    long kattr;
    long kflag;
    long offset_in_mobj;
    long offset_in_page;
    rt_err_t error;
    rt_varea_t uarea;
    rt_mem_obj_t mobj;
    void *kaddr = 0;

    uarea = rt_aspace_query(lwp->aspace, uaddr);
    if (uarea)
    {
        /* setup the identical mapping, and align up for address & length */
        kattr = _uattr_to_kernel(uarea->attr);
        kflag = _uflag_to_kernel(uarea->flag);
        offset_in_mobj = uarea->offset + ((long)uaddr - (long)uarea->start) / ARCH_PAGE_SIZE;
        mobj = uarea->mem_obj;
        offset_in_page = (long)uaddr & ARCH_PAGE_MASK;
        length = RT_ALIGN(length + offset_in_page, ARCH_PAGE_SIZE);
        error = rt_aspace_map(&rt_kernel_space, &kaddr, length, kattr, kflag, mobj, offset_in_mobj);
        if (error)
        {
            LOG_I("%s(length=0x%lx,attr=0x%lx,flags=0x%lx): do map failed", __func__, length, kattr, kflag);
            kaddr = 0;
        }
        else
        {
            /* TODO: {make a memory lock?} */
            LOG_D("%s(length=0x%lx,attr=0x%lx,flags=0x%lx,offset=0x%lx) => %p", __func__, length, kattr, kflag, offset_in_mobj, kaddr);
            _prefetch_mmap(&rt_kernel_space, kaddr, length);
            kaddr += offset_in_page;
        }
    }

    return kaddr;
}

void *lwp_mmap2(struct rt_lwp *lwp, void *addr, size_t length, int prot,
                int flags, int fd, off_t pgoffset)
{
    rt_err_t rc;
    rt_size_t k_attr;
    rt_size_t k_flags;
    rt_size_t k_offset;
    rt_aspace_t uspace;
    rt_mem_obj_t mem_obj;
    void *ret = 0;
    LOG_D("%s(addr=0x%lx,length=%ld,fd=%d)", __func__, addr, length, fd);

    if (fd == -1)
    {
        /**
         * todo: add threshold
         */
        if (!_memory_threshold_ok())
            return (void *)-ENOMEM;

        k_offset = MM_PA_TO_OFF(addr);
        k_flags = lwp_user_mm_flag_to_kernel(flags) | MMF_MAP_PRIVATE;
        k_attr = lwp_user_mm_attr_to_kernel(prot);

        uspace = lwp->aspace;
        length = RT_ALIGN(length, ARCH_PAGE_SIZE);
        mem_obj = _get_mmap_obj(lwp);

        rc = rt_aspace_map(uspace, &addr, length, k_attr, k_flags, mem_obj, k_offset);
        if (rc == RT_EOK)
        {
            ret = addr;
        }
        else
        {
            ret = (void *)lwp_errno_to_posix(rc);
        }
    }
    else
    {
        struct dfs_file *d;

        d = fd_get(fd);
        if (d)
        {
            struct dfs_mmap2_args mmap2;

            mmap2.addr = addr;
            mmap2.length = length;
            mmap2.prot = prot;
            mmap2.flags = flags;
            mmap2.pgoffset = pgoffset;
            mmap2.ret = (void *)-1;
            mmap2.lwp = lwp;

            rc = dfs_file_mmap2(d, &mmap2);
            if (rc == RT_EOK)
            {
                ret = mmap2.ret;
            }
            else
            {
                ret = (void *)lwp_errno_to_posix(rc);
            }
        }
    }

    if ((long)ret <= 0)
        LOG_D("%s() => %ld", __func__, ret);
    return ret;
}

int lwp_munmap(struct rt_lwp *lwp, void *addr, size_t length)
{
    int ret;

    RT_ASSERT(lwp);
    ret = rt_aspace_unmap_range(lwp->aspace, addr, length);
    return lwp_errno_to_posix(ret);
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
        if (tmp_addr == ARCH_MAP_FAILED &&
            !rt_aspace_query(lwp->aspace, addr_start))
        {
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

#define ALIGNED(addr) (!((rt_size_t)(addr) & ARCH_PAGE_MASK))

/* src is in lwp address space, dst is in current thread space */
size_t lwp_data_get(struct rt_lwp *lwp, void *dst, void *src, size_t size)
{
    size_t copy_len = 0;
    char *temp_page = 0;
    char *dst_iter, *dst_next_page;
    char *src_copy_end, *src_iter, *src_iter_aligned;

    if (!size || !dst)
    {
        return 0;
    }
    dst_iter = dst;
    src_iter = src;
    src_copy_end = src + size;
    dst_next_page =
        (char *)(((size_t)src_iter + ARCH_PAGE_SIZE) & ~(ARCH_PAGE_SIZE - 1));
    do
    {
        size_t bytes_to_copy = (char *)dst_next_page - (char *)src_iter;
        if (bytes_to_copy > size)
        {
            bytes_to_copy = size;
        }

        if (ALIGNED(src_iter) && bytes_to_copy == ARCH_PAGE_SIZE)
        {
            /* get page to kernel buffer */
            if (rt_aspace_page_get(lwp->aspace, src_iter, dst_iter))
                break;
        }
        else
        {
            if (!temp_page)
                temp_page = rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);
            if (!temp_page)
                break;

            src_iter_aligned = (char *)((long)src_iter & ~ARCH_PAGE_MASK);
            if (rt_aspace_page_get(lwp->aspace, src_iter_aligned, temp_page))
                break;
            memcpy(dst_iter, temp_page + (src_iter - src_iter_aligned), bytes_to_copy);
        }

        dst_iter = dst_iter + bytes_to_copy;
        src_iter = src_iter + bytes_to_copy;
        size -= bytes_to_copy;
        dst_next_page = (void *)((char *)dst_next_page + ARCH_PAGE_SIZE);
        copy_len += bytes_to_copy;
    } while (src_iter < src_copy_end);

    if (temp_page)
        rt_pages_free(temp_page, 0);
    return copy_len;
}

/* dst is in lwp address space, src is in current thread space */
size_t lwp_data_put(struct rt_lwp *lwp, void *dst, void *src, size_t size)
{
    size_t copy_len = 0;
    char *temp_page = 0;
    char *dst_iter, *dst_iter_aligned, *dst_next_page;
    char *src_put_end, *src_iter;

    if (!size || !dst)
    {
        return 0;
    }

    src_iter = src;
    dst_iter = dst;
    src_put_end = dst + size;
    dst_next_page =
        (char *)(((size_t)dst_iter + ARCH_PAGE_SIZE) & ~(ARCH_PAGE_SIZE - 1));
    do
    {
        size_t bytes_to_put = (char *)dst_next_page - (char *)dst_iter;
        if (bytes_to_put > size)
        {
            bytes_to_put = size;
        }

        if (ALIGNED(dst_iter) && bytes_to_put == ARCH_PAGE_SIZE)
        {
            /* write to page in kernel */
            if (rt_aspace_page_put(lwp->aspace, dst_iter, src_iter))
                break;
        }
        else
        {
            if (!temp_page)
                temp_page = rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);
            if (!temp_page)
                break;

            dst_iter_aligned = (void *)((long)dst_iter & ~ARCH_PAGE_MASK);
            if (rt_aspace_page_get(lwp->aspace, dst_iter_aligned, temp_page))
                break;
            memcpy(temp_page + (dst_iter - dst_iter_aligned), src_iter, bytes_to_put);
            if (rt_aspace_page_put(lwp->aspace, dst_iter_aligned, temp_page))
                break;
        }

        src_iter = src_iter + bytes_to_put;
        dst_iter = dst_iter + bytes_to_put;
        size -= bytes_to_put;
        dst_next_page = dst_next_page + ARCH_PAGE_SIZE;
        copy_len += bytes_to_put;
    } while (dst_iter < src_put_end);

    if (temp_page)
        rt_pages_free(temp_page, 0);
    return copy_len;
}

/* Set N bytes of S to C */
size_t lwp_data_set(struct rt_lwp *lwp, void *dst, int byte, size_t size)
{
    size_t copy_len = 0;
    char *temp_page = 0;
    char *dst_iter, *dst_iter_aligned, *dst_next_page;
    char *dst_put_end;

    if (!size || !dst)
    {
        return 0;
    }

    dst_iter = dst;
    dst_put_end = dst + size;
    dst_next_page =
        (char *)(((size_t)dst_iter + ARCH_PAGE_SIZE) & ~(ARCH_PAGE_SIZE - 1));
    temp_page = rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);
    if (temp_page)
    {
        do
        {
            size_t bytes_to_put = (char *)dst_next_page - (char *)dst_iter;
            if (bytes_to_put > size)
            {
                bytes_to_put = size;
            }

            dst_iter_aligned = (void *)((long)dst_iter & ~ARCH_PAGE_MASK);
            if (!ALIGNED(dst_iter) || bytes_to_put != ARCH_PAGE_SIZE)
                if (rt_aspace_page_get(lwp->aspace, dst_iter_aligned, temp_page))
                    break;

            memset(temp_page + (dst_iter - dst_iter_aligned), byte, bytes_to_put);
            if (rt_aspace_page_put(lwp->aspace, dst_iter_aligned, temp_page))
                break;

            dst_iter = dst_iter + bytes_to_put;
            size -= bytes_to_put;
            dst_next_page = dst_next_page + ARCH_PAGE_SIZE;
            copy_len += bytes_to_put;
        } while (dst_iter < dst_put_end);

        rt_pages_free(temp_page, 0);
    }

    return copy_len;
}

size_t lwp_user_strlen_ext(struct rt_lwp *lwp, const char *s)
{
    int len = 0;
    char *temp_buf = RT_NULL;
    void *addr_start = RT_NULL;
    int get_bytes = 0;
    int index = 0;

    if (s == RT_NULL)
        return 0;

    if (lwp == RT_NULL)
    {
        LOG_W("%s: lwp is NULL", __func__);
        return -1;
    }

    addr_start = (void *)s;
    temp_buf = rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);
    if (!temp_buf)
    {
        LOG_W("%s: No memory", __func__);
        return -1;
    }

    get_bytes = lwp_data_get(lwp, temp_buf, addr_start, ARCH_PAGE_SIZE);
    if (get_bytes == 0)
    {
        LOG_I("lwp_data_get(lwp=%p,dst=0x%lx,src=0x%lx,size=0x1000) failed", lwp, temp_buf, addr_start);
        rt_pages_free(temp_buf, 0);
        return -1;
    }

    while (temp_buf[index] != '\0')
    {
        len++;
        index++;
        if (index == get_bytes)
        {
            if (get_bytes == ARCH_PAGE_SIZE)
            {
                get_bytes = lwp_data_get(lwp, temp_buf, addr_start + len, ARCH_PAGE_SIZE);
                if (get_bytes == 0)
                {
                    LOG_I("lwp_data_get(lwp=%p,dst=0x%lx,src=0x%lx,size=0x1000): user data unaccessible",
                        lwp, temp_buf, addr_start);
                    len = -1;
                    break;
                }
                index = 0;
            }
            else
            {
                LOG_I("lwp_data_get(lwp=%p,dst=0x%lx,src=0x%lx,size=0x1000): user data unaccessible",
                    lwp, temp_buf, addr_start);
                len = -1;
                break;
            }
        }
    }

    rt_pages_free(temp_buf, 0);
    return len;
}

size_t lwp_user_strlen(const char *s)
{
    struct rt_lwp *lwp = RT_NULL;

    lwp = lwp_self();
    RT_ASSERT(lwp != RT_NULL);

    return lwp_user_strlen_ext(lwp, s);
}


char** lwp_get_command_line_args(struct rt_lwp *lwp)
{
    size_t argc = 0;
    char** argv = NULL;
    int ret;
    size_t i;
    size_t len;

    if (lwp)
    {
        ret = lwp_data_get(lwp, &argc, lwp->args, sizeof(argc));
        if (ret == 0)
        {
            return RT_NULL;
        }
        argv = (char**)rt_malloc((argc + 1) * sizeof(char*));

        if (argv)
        {
            for (i = 0; i < argc; i++)
            {
                char *argvp = NULL;
                ret = lwp_data_get(lwp, &argvp, &((char **)lwp->args)[1 + i], sizeof(argvp));
                if (ret == 0)
                {
                    lwp_free_command_line_args(argv);
                    return RT_NULL;
                }
                len = lwp_user_strlen_ext(lwp, argvp);

                if (len > 0)
                {
                    argv[i] = (char*)rt_malloc(len + 1);
                    ret = lwp_data_get(lwp, argv[i], argvp, len);
                    if (ret == 0)
                    {
                        lwp_free_command_line_args(argv);
                        return RT_NULL;
                    }
                    argv[i][len] = '\0';
                }
                else
                {
                    argv[i] = NULL;
                }
            }
            argv[argc] = NULL;
        }
    }

    return argv;
}

void lwp_free_command_line_args(char** argv)
{
    size_t i;

    if (argv)
    {
        for (i = 0; argv[i]; i++)
        {
            rt_free(argv[i]);
        }
        rt_free(argv);
    }
}

#endif
