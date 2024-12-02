/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-01     Jesven       The first version
 * 2022-12-13     WangXiaoyao  Hot-pluggable, extensible
 *                             page management algorithm
 * 2023-02-20     WangXiaoyao  Multi-list page-management
 * 2023-11-28     Shell        Bugs fix for page_install on shadow region
 * 2024-06-18     Shell        Added affinity page management for page coloring.
 */
#include <rtthread.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "mm_fault.h"
#include "mm_private.h"
#include "mm_aspace.h"
#include "mm_flag.h"
#include "mm_page.h"
#include <mmu.h>

#define DBG_TAG "mm.page"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

RT_STATIC_ASSERT(order_huge_pg, RT_PAGE_MAX_ORDER > ARCH_PAGE_SHIFT - 2);
RT_STATIC_ASSERT(size_width, sizeof(rt_size_t) == sizeof(void *));

#ifdef RT_USING_SMART
#include "lwp_arch_comm.h"
#endif /* RT_USING_SMART */

static rt_size_t init_mpr_align_start;
static rt_size_t init_mpr_align_end;
static void *init_mpr_cont_start;

static struct rt_varea mpr_varea;

typedef union
{
    struct rt_page *page_list;
    rt_ubase_t aff_page_map;
} pgls_agr_t;

#define PGLS_IS_AFF_MAP(pgls) (!!((pgls).aff_page_map & 0x1))
#define PGLS_FROM_AFF_MAP(pgls, aff_map) \
    ((pgls).aff_page_map = (-(rt_ubase_t)(aff_map)) | 0x1)
#define PGLS_GET_AFF_MAP(pgls) \
    ((struct rt_page **)-((pgls).aff_page_map & ~0x1))
#define PGLS_GET(pgls) \
    (PGLS_IS_AFF_MAP(pgls) ? PGLS_GET_AFF_MAP(pgls) : (pgls).page_list)
#define PAGE_TO_AFFID(page) (RT_PAGE_PICK_AFFID(page_to_paddr(page)))

/* affinity id */
#define AFFID_BLK_BITS \
    ((sizeof(int) * 8 - 1) - __builtin_clz(RT_PAGE_AFFINITY_BLOCK_SIZE) - ARCH_PAGE_SHIFT)
#define AFFID_NUMOF_ID_IN_SET(order) \
    ((RT_PAGE_AFFINITY_BLOCK_SIZE / ARCH_PAGE_SIZE) / (1ul << (order)))
#define AFFID_BITS_MASK(order) \
    (((1 << AFFID_BLK_BITS) - 1) - ((1 << (order)) - 1))

static pgls_agr_t page_list_low[RT_PAGE_MAX_ORDER];
static rt_page_t
    aff_pglist_low[AFFID_NUMOF_ID_IN_SET(0) * 2 - 2];
static pgls_agr_t page_list_high[RT_PAGE_MAX_ORDER];
static rt_page_t
    aff_pglist_high[AFFID_NUMOF_ID_IN_SET(0) * 2 - 2];

/* protect buddy list and page records */
static RT_DEFINE_SPINLOCK(_pgmgr_lock);

#define page_start ((rt_page_t)rt_mpr_start)

static rt_size_t _page_nr, _page_nr_hi;
static rt_size_t _freed_nr, _freed_nr_hi;
static rt_size_t early_offset;

static const char *get_name(rt_varea_t varea)
{
    return "master-page-record";
}

static void hint_free(rt_mm_va_hint_t hint)
{
    hint->flags = MMF_MAP_FIXED;
    hint->limit_start = rt_kernel_space.start;
    hint->limit_range_size = rt_kernel_space.size;
    hint->prefer = rt_mpr_start;
}

static void on_page_fault(struct rt_varea *varea,
                          struct rt_aspace_fault_msg *msg)
{
    char *init_start = (void *)init_mpr_align_start;
    char *init_end = (void *)init_mpr_align_end;
    if ((char *)msg->fault_vaddr < init_end &&
        (char *)msg->fault_vaddr >= init_start)
    {
        rt_size_t offset = (char *)msg->fault_vaddr - init_start;
        msg->response.status = MM_FAULT_STATUS_OK;
        msg->response.vaddr = (char *)init_mpr_cont_start + offset;
        msg->response.size = ARCH_PAGE_SIZE;
    }
    else
    {
        rt_mm_dummy_mapper.on_page_fault(varea, msg);
    }
}

static struct rt_mem_obj mm_page_mapper = {
    .get_name = get_name,
    .on_page_fault = on_page_fault,
    .hint_free = hint_free,
};

#ifdef RT_DEBUGGING_PAGE_LEAK
static volatile int enable;
static rt_page_t _trace_head;
#define TRACE_ALLOC(pg, size)       _trace_alloc(pg, __builtin_return_address(0), size)
#define TRACE_FREE(pgaddr, size)    _trace_free(pgaddr, __builtin_return_address(0), size)

static long _alloc_cnt;

void rt_page_leak_trace_start()
{
    // TODO multicore safety
    _trace_head = NULL;
    _alloc_cnt = 0;
    enable = 1;
}
MSH_CMD_EXPORT(rt_page_leak_trace_start, start page leak tracer);

static void _collect()
{
    rt_page_t page = _trace_head;
    if (!page)
    {
        rt_kprintf("ok! ALLOC CNT %ld\n", _alloc_cnt);
    }
    else
    {
        while (page)
        {
            rt_page_t next = page->tl_next;
            void *pg_va = rt_page_page2addr(page);
            LOG_W("LEAK: %p, allocator: %p, size bits: %lx", pg_va, page->caller, page->trace_size);
            rt_pages_free(pg_va, page->trace_size);
            page = next;
        }
    }
}

void rt_page_leak_trace_stop()
{
    // TODO multicore safety
    enable = 0;
    _collect();
}
MSH_CMD_EXPORT(rt_page_leak_trace_stop, stop page leak tracer);

static void _trace_alloc(rt_page_t page, void *caller, size_t size_bits)
{
    if (enable)
    {
        page->caller = caller;
        page->trace_size = size_bits;
        page->tl_prev = NULL;
        page->tl_next = NULL;

        _alloc_cnt++;
        if (_trace_head == NULL)
        {
            _trace_head = page;
        }
        else
        {
            _trace_head->tl_prev = page;
            page->tl_next = _trace_head;
            _trace_head = page;
        }
    }
}

void _report(rt_page_t page, size_t size_bits, char *msg)
{
    void *pg_va = rt_page_page2addr(page);
    LOG_W("%s: %p, allocator: %p, size bits: %lx", msg, pg_va, page->caller, page->trace_size);
    rt_kprintf("backtrace\n");
    rt_backtrace();
}

static void _trace_free(rt_page_t page, void *caller, size_t size_bits)
{
    if (enable)
    {
        /* free after free */
        if (page->trace_size == 0xabadcafe)
        {
            _report(page, size_bits, "free after free");
            return ;
        }
        else if (page->trace_size != size_bits)
        {
            rt_kprintf("free with size bits %lx\n", size_bits);
            _report(page, size_bits, "incompatible size bits parameter");
            return ;
        }

        if (page->ref_cnt == 0)
        {
            _alloc_cnt--;
            if (page->tl_prev)
                page->tl_prev->tl_next = page->tl_next;
            if (page->tl_next)
                page->tl_next->tl_prev = page->tl_prev;

            if (page == _trace_head)
                _trace_head = page->tl_next;

            page->tl_prev = NULL;
            page->tl_next = NULL;
            page->trace_size = 0xabadcafe;
        }
    }
}
#else
#define TRACE_ALLOC(x, y)
#define TRACE_FREE(x, y)
#endif

/* page management */
#ifdef RT_DEBUGGING_PAGE_POISON
#include <bitmap.h>
RT_BITMAP_DECLARE(_init_region_usage_trace, (1 << (1 + ARCH_SECTION_SHIFT - ARCH_PAGE_SHIFT)));
#else
typedef char rt_bitmap_t[0];
#define RT_BITMAP_LEN(__name) (__name)
#endif /* RT_DEBUGGING_PAGE_POISON */

static struct installed_page_reg
{
    rt_region_t region_area;
    struct installed_page_reg *next;
    struct rt_spinlock lock;
#ifdef RT_DEBUGGING_PAGE_POISON
    rt_bitmap_t *usage_trace;
#endif /* RT_DEBUGGING_PAGE_POISON */
} _init_region;

static RT_DEFINE_SPINLOCK(_inst_page_reg_lock);
static struct installed_page_reg *_inst_page_reg_head;

static void _print_region_list(void)
{
    struct installed_page_reg *iter;
    int counts = 0;

    rt_spin_lock(&_inst_page_reg_lock);
    iter = _inst_page_reg_head;
    while (iter != RT_NULL)
    {
        rt_kprintf("  %d: [%p, %p]\n", counts++, iter->region_area.start + PV_OFFSET,
                   iter->region_area.end + PV_OFFSET);
        iter = iter->next;
    }
    rt_spin_unlock(&_inst_page_reg_lock);
}

static struct installed_page_reg *_find_page_region(rt_ubase_t page_va)
{
    struct installed_page_reg *iter;
    struct installed_page_reg *rc = RT_NULL;
    rt_bool_t found = RT_FALSE;

    rt_spin_lock(&_inst_page_reg_lock);
    for (iter = _inst_page_reg_head; iter; iter = iter->next)
    {
        if (page_va >= iter->region_area.start &&
            page_va < iter->region_area.end)
        {
            found = RT_TRUE;
            break;
        }
    }
    rt_spin_unlock(&_inst_page_reg_lock);

    if (found)
    {
        rc = iter;
    }
    return rc;
}

rt_bool_t rt_page_is_member(rt_base_t page_pa)
{
    return _find_page_region(page_pa - PV_OFFSET) != RT_NULL;
}

static rt_bool_t _pages_are_member(rt_ubase_t page_va, size_t size_bits)
{
    rt_bool_t rc = RT_TRUE;
    rt_ubase_t iter_frame = page_va;
    size_t frame_end = page_va + (1 << size_bits);

    while (iter_frame < frame_end)
    {
        size_t overlap_size;
        struct installed_page_reg *page_reg = _find_page_region(iter_frame);

        if (!page_reg)
        {
            rc = RT_FALSE;
            LOG_E("Allocated invalid page %p", iter_frame);
            break;
        }

        overlap_size = page_reg->region_area.end - iter_frame;
        iter_frame += overlap_size;
    }

    return rc;
}

#ifdef RT_DEBUGGING_PAGE_POISON
static rt_err_t _unpoisoned_pages(char *head, rt_uint32_t size_bits)
{
    rt_err_t error = RT_EOK;
    struct installed_page_reg *page_reg = _find_page_region((rt_ubase_t)head);

    if (page_reg)
    {
        int pages_count = 1 << size_bits;
        long bit_number = ((rt_ubase_t)head - page_reg->region_area.start) / ARCH_PAGE_SIZE;

        /* mark the pages as allocated */
        for (size_t i = 0; i < pages_count; i++, bit_number++)
        {
            rt_spin_lock(&_inst_page_reg_lock);
            if (rt_bitmap_test_bit(page_reg->usage_trace, bit_number))
            {
                error = RT_ERROR;
                rt_kprintf("%s: Pages[%p, %d] is already in used by others!\n", __func__, head, size_bits);
            }
            rt_bitmap_set_bit(page_reg->usage_trace, bit_number);
            rt_spin_unlock(&_inst_page_reg_lock);
        }
    }
    else
    {
        error = RT_EINVAL;
    }

    return -error;
}

static rt_err_t _poisoned_pages(char *head, rt_uint32_t size_bits)
{
    rt_err_t error = RT_EOK;
    struct installed_page_reg *page_reg = _find_page_region((rt_ubase_t)head);

    if (page_reg)
    {
        int pages_count = 1 << size_bits;
        long bit_number = ((rt_ubase_t)head - page_reg->region_area.start) / ARCH_PAGE_SIZE;

        /* mark the pages as free */
        for (size_t i = 0; i < pages_count; i++, bit_number++)
        {
            rt_spin_lock(&_inst_page_reg_lock);
            if (!rt_bitmap_test_bit(page_reg->usage_trace, bit_number))
            {
                error = RT_ERROR;
                rt_kprintf("%s: Pages[%p, %d] is freed before!\n", __func__, head, size_bits);
            }
            rt_bitmap_clear_bit(page_reg->usage_trace, bit_number);
            rt_spin_unlock(&_inst_page_reg_lock);
        }
    }
    else
    {
        error = RT_EINVAL;
    }

    return -error;
}

#endif /* RT_DEBUGGING_PAGE_POISON */

static inline void *page_to_addr(rt_page_t page)
{
    return (void *)(((page - page_start) << ARCH_PAGE_SHIFT) - PV_OFFSET);
}

static inline rt_ubase_t page_to_paddr(rt_page_t page)
{
    return (rt_ubase_t)((page - page_start) << ARCH_PAGE_SHIFT);
}

static inline rt_page_t addr_to_page(rt_page_t pg_start, void *addr)
{
    addr = (char *)addr + PV_OFFSET;
    return &pg_start[((rt_ubase_t)addr >> ARCH_PAGE_SHIFT)];
}

#define CEIL(val, align) (((rt_size_t)(val) + (align)-1) & ~((align)-1))

/**
 * shadow is the accessible region by buddy but not usable for page manager.
 * shadow mask is used for calculate the region head from an address.
 */
const rt_size_t shadow_mask =
    ((1ul << (RT_PAGE_MAX_ORDER + ARCH_PAGE_SHIFT - 1)) - 1);

const rt_size_t rt_mpr_size = CEIL(
    ((1ul << (ARCH_VADDR_WIDTH - ARCH_PAGE_SHIFT))) * sizeof(struct rt_page),
    ARCH_PAGE_SIZE);

void *rt_mpr_start;

rt_weak int rt_hw_clz(unsigned long n)
{
    return __builtin_clzl(n);
}

rt_weak int rt_hw_ctz(unsigned long n)
{
    return __builtin_ctzl(n);
}

rt_size_t rt_page_bits(rt_size_t size)
{
    int bit = sizeof(rt_size_t) * 8 - rt_hw_clz(size) - 1;

    if ((size ^ (1UL << bit)) != 0)
    {
        bit++;
    }
    bit -= ARCH_PAGE_SHIFT;
    if (bit < 0)
    {
        bit = 0;
    }
    return bit;
}

struct rt_page *rt_page_addr2page(void *addr)
{
    return addr_to_page(page_start, addr);
}

void *rt_page_page2addr(struct rt_page *p)
{
    return page_to_addr(p);
}

static inline struct rt_page *_buddy_get(struct rt_page *p,
                                         rt_uint32_t size_bits)
{
    rt_size_t addr;

    RT_ASSERT(size_bits < RT_PAGE_MAX_ORDER - 1);

    addr = (rt_size_t)rt_page_page2addr(p);
    addr ^= (1UL << (size_bits + ARCH_PAGE_SHIFT));
    return rt_page_addr2page((void *)addr);
}

static rt_page_t *_get_pgls_head_by_page(pgls_agr_t *agr_pgls, rt_page_t page,
                                         rt_uint32_t size_bits)
{
    rt_page_t *pgls_head;
    int index;

    if (size_bits < AFFID_BLK_BITS)
    {
        index = PAGE_TO_AFFID(page) >> size_bits;
        RT_ASSERT(index < AFFID_NUMOF_ID_IN_SET(size_bits));

        RT_ASSERT(PGLS_IS_AFF_MAP(agr_pgls[size_bits]));
        pgls_head = &PGLS_GET_AFF_MAP(agr_pgls[size_bits])[index];
    }
    else
    {
        RT_ASSERT(!PGLS_IS_AFF_MAP(agr_pgls[size_bits]));
        pgls_head = &agr_pgls[size_bits].page_list;
    }

    return pgls_head;
}

static rt_page_t *_get_pgls_head(pgls_agr_t *agr_pgls, int affid,
                                 rt_uint32_t size_bits)
{
    rt_page_t *pgls_head;
    int index;

    if (size_bits < AFFID_BLK_BITS)
    {
        index = affid >> size_bits;
        RT_ASSERT(index < AFFID_NUMOF_ID_IN_SET(size_bits));

        RT_ASSERT(PGLS_IS_AFF_MAP(agr_pgls[size_bits]));
        pgls_head = &PGLS_GET_AFF_MAP(agr_pgls[size_bits])[index];
    }
    else
    {
        RT_ASSERT(!PGLS_IS_AFF_MAP(agr_pgls[size_bits]));
        pgls_head = &agr_pgls[size_bits].page_list;
    }

    return pgls_head;
}

static void _page_alloc(struct rt_page *p)
{
    p->size_bits = ARCH_ADDRESS_WIDTH_BITS;
    p->ref_cnt = 1;
}

static void _page_remove(rt_page_t *page_head, struct rt_page *p,
                         rt_uint32_t size_bits)
{
    if (p->pre)
    {
        p->pre->next = p->next;
    }
    else
    {
        *page_head = p->next;
    }

    if (p->next)
    {
        p->next->pre = p->pre;
    }

    RT_ASSERT(p->size_bits == size_bits);
    _page_alloc(p);
}

static void _page_insert(rt_page_t *page_head, struct rt_page *p,
                         rt_uint32_t size_bits)
{
    p->next = *page_head;
    if (p->next)
    {
        p->next->pre = p;
    }
    p->pre = 0;
    *page_head = p;
    p->size_bits = size_bits;
}

static void _pages_ref_inc(struct rt_page *p, rt_uint32_t size_bits)
{
    struct rt_page *page_head;
    int idx;

    /* find page group head */
    idx = p - page_start;
    idx = idx & ~((1UL << size_bits) - 1);

    page_head = page_start + idx;
    page_head = (void *)((char *)page_head + early_offset);
    page_head->ref_cnt++;
}

static int _pages_ref_get(struct rt_page *p, rt_uint32_t size_bits)
{
    struct rt_page *page_head;
    int idx;

    /* find page group head */
    idx = p - page_start;
    idx = idx & ~((1UL << size_bits) - 1);

    page_head = page_start + idx;
    return page_head->ref_cnt;
}

static int _pages_free(pgls_agr_t page_list[], struct rt_page *p,
                       char *frame_va, rt_uint32_t size_bits)
{
    rt_uint32_t level = size_bits;
    struct rt_page *buddy;

    RT_ASSERT(p >= page_start);
    RT_ASSERT((char *)p < (char *)rt_mpr_start + rt_mpr_size);
    RT_ASSERT(rt_kmem_v2p(p));
    RT_ASSERT(p->ref_cnt > 0);
    RT_ASSERT(p->size_bits == ARCH_ADDRESS_WIDTH_BITS);
    RT_ASSERT(size_bits < RT_PAGE_MAX_ORDER);
    RT_UNUSED(_pages_are_member);
    RT_ASSERT(_pages_are_member((rt_ubase_t)frame_va, size_bits));

    p->ref_cnt--;
    if (p->ref_cnt != 0)
    {
        return 0;
    }

#ifdef RT_DEBUGGING_PAGE_POISON
    _poisoned_pages(frame_va, size_bits);
#endif /* RT_DEBUGGING_PAGE_POISON */

    while (level < RT_PAGE_MAX_ORDER - 1)
    {
        buddy = _buddy_get(p, level);
        if (buddy && buddy->size_bits == level)
        {
            _page_remove(_get_pgls_head_by_page(page_list, buddy, level),
                         buddy, level);
            p = (p < buddy) ? p : buddy;
            level++;
        }
        else
        {
            break;
        }
    }

    _page_insert(_get_pgls_head_by_page(page_list, p, level),
                 p, level);
    return 1;
}

static struct rt_page *__pages_alloc(
    pgls_agr_t agr_pgls[], rt_uint32_t size_bits, int affid,
    void (*page_remove)(rt_page_t *page_head, struct rt_page *p,
                        rt_uint32_t size_bits),
    void (*page_insert)(rt_page_t *page_head, struct rt_page *p,
                        rt_uint32_t size_bits),
    void (*page_alloc)(rt_page_t page))
{
    rt_page_t *pgls_head = _get_pgls_head(agr_pgls, affid, size_bits);
    rt_page_t p = *pgls_head;

    if (p)
    {
        page_remove(pgls_head, p, size_bits);
    }
    else
    {
        rt_uint32_t level;
        rt_page_t head;

        /* fallback for allocation */
        for (level = size_bits + 1; level < RT_PAGE_MAX_ORDER; level++)
        {
            pgls_head = _get_pgls_head(agr_pgls, affid, level);
            p = *pgls_head;
            if (p)
            {
                break;
            }
        }
        if (level == RT_PAGE_MAX_ORDER)
        {
            return 0;
        }

        page_remove(pgls_head, p, level);

        /* pick the page satisfied the affinity tag */
        head = p;
        p = head + (affid - (affid & AFFID_BITS_MASK(level)));
        page_alloc(p);

        /* release the pages caller don't need */
        while (level > size_bits)
        {
            long lower_bits = level - 1;
            rt_page_t middle = _buddy_get(head, lower_bits);
            if (p >= middle)
            {
                page_insert(
                    _get_pgls_head_by_page(agr_pgls, head, lower_bits),
                    head, lower_bits);
                head = middle;
            }
            else
            {
                page_insert(
                    _get_pgls_head_by_page(agr_pgls, middle, lower_bits),
                    middle, lower_bits);
            }
            level = lower_bits;
        }
    }

    return p;
}

static struct rt_page *_pages_alloc(pgls_agr_t page_list[],
                                    rt_uint32_t size_bits, int affid)
{
    return __pages_alloc(page_list, size_bits, affid, _page_remove,
                         _page_insert, _page_alloc);
}

static void _early_page_remove(rt_page_t *pgls_head, rt_page_t page,
                               rt_uint32_t size_bits)
{
    rt_page_t page_cont = (rt_page_t)((char *)page + early_offset);
    if (page_cont->pre)
    {
        rt_page_t pre_cont = (rt_page_t)((char *)page_cont->pre + early_offset);
        pre_cont->next = page_cont->next;
    }
    else
    {
        *pgls_head = page_cont->next;
    }

    if (page_cont->next)
    {
        rt_page_t next_cont = (rt_page_t)((char *)page_cont->next + early_offset);
        next_cont->pre = page_cont->pre;
    }

    RT_ASSERT(page_cont->size_bits == size_bits);
    page_cont->size_bits = ARCH_ADDRESS_WIDTH_BITS;
    page_cont->ref_cnt = 1;
}

static void _early_page_alloc(rt_page_t page)
{
    rt_page_t page_cont = (rt_page_t)((char *)page + early_offset);
    page_cont->size_bits = ARCH_ADDRESS_WIDTH_BITS;
    page_cont->ref_cnt = 1;
}

static void _early_page_insert(rt_page_t *pgls_head, rt_page_t page,
                               rt_uint32_t size_bits)
{
    RT_ASSERT((void *)page >= rt_mpr_start &&
              ((char *)page - (char *)rt_mpr_start) < rt_mpr_size);
    rt_page_t page_cont = (rt_page_t)((char *)page + early_offset);

    page_cont->next = *pgls_head;
    if (page_cont->next)
    {
        rt_page_t next_cont = (rt_page_t)((char *)page_cont->next + early_offset);
        next_cont->pre = page;
    }
    page_cont->pre = 0;
    *pgls_head = page;
    page_cont->size_bits = size_bits;
}

static struct rt_page *_early_pages_alloc(pgls_agr_t page_list[],
                                          rt_uint32_t size_bits, int affid)
{
    return __pages_alloc(page_list, size_bits, affid, _early_page_remove,
                         _early_page_insert, _early_page_alloc);
}

static pgls_agr_t *_get_page_list(void *vaddr)
{
    rt_ubase_t pa_int = (rt_ubase_t)vaddr + PV_OFFSET;
    pgls_agr_t *list;
    if (pa_int > UINT32_MAX)
    {
        list = page_list_high;
    }
    else
    {
        list = page_list_low;
    }
    return list;
}

int rt_page_ref_get(void *addr, rt_uint32_t size_bits)
{
    struct rt_page *p;
    rt_base_t level;
    int ref;

    p = rt_page_addr2page(addr);
    level = rt_spin_lock_irqsave(&_pgmgr_lock);
    ref = _pages_ref_get(p, size_bits);
    rt_spin_unlock_irqrestore(&_pgmgr_lock, level);
    return ref;
}

void rt_page_ref_inc(void *addr, rt_uint32_t size_bits)
{
    struct rt_page *p;
    rt_base_t level;

    p = rt_page_addr2page(addr);
    level = rt_spin_lock_irqsave(&_pgmgr_lock);
    _pages_ref_inc(p, size_bits);
    rt_spin_unlock_irqrestore(&_pgmgr_lock, level);
}

static rt_page_t (*pages_alloc_handler)(pgls_agr_t page_list[],
                                        rt_uint32_t size_bits, int affid);

/* if not, we skip the finding on page_list_high */
static size_t _high_page_configured = 0;

static pgls_agr_t *_flag_to_page_list(size_t flags)
{
    pgls_agr_t *page_list;
    if (_high_page_configured && (flags & PAGE_ANY_AVAILABLE))
    {
        page_list = page_list_high;
    }
    else
    {
        page_list = page_list_low;
    }
    return page_list;
}

volatile static rt_ubase_t _last_alloc;

rt_inline void *_do_pages_alloc(rt_uint32_t size_bits, size_t flags, int affid)
{
    void *alloc_buf = RT_NULL;
    struct rt_page *p;
    rt_base_t level;
    pgls_agr_t *page_list = _flag_to_page_list(flags);

    level = rt_spin_lock_irqsave(&_pgmgr_lock);
    p = pages_alloc_handler(page_list, size_bits, affid);
    if (p)
    {
        _freed_nr -= 1 << size_bits;
    }
    rt_spin_unlock_irqrestore(&_pgmgr_lock, level);

    if (!p && page_list != page_list_low)
    {
        /* fall back */
        page_list = page_list_low;

        level = rt_spin_lock_irqsave(&_pgmgr_lock);
        p = pages_alloc_handler(page_list, size_bits, affid);
        if (p)
        {
            _freed_nr -= 1 << size_bits;
            _freed_nr_hi -= 1 << size_bits;
        }
        rt_spin_unlock_irqrestore(&_pgmgr_lock, level);
    }

    if (p)
    {
        alloc_buf = page_to_addr(p);
        _last_alloc = (rt_ubase_t)alloc_buf;

        #ifdef RT_DEBUGGING_PAGE_LEAK
            level = rt_spin_lock_irqsave(&_spinlock);
            TRACE_ALLOC(p, size_bits);
            rt_spin_unlock_irqrestore(&_spinlock, level);
        #endif

#ifdef RT_DEBUGGING_PAGE_POISON
        _unpoisoned_pages(alloc_buf, size_bits);
#endif /* RT_DEBUGGING_PAGE_POISON */

    }

    return alloc_buf;
}

rt_inline int _get_balanced_id(rt_uint32_t size_bits)
{
    rt_ubase_t last_alloc = (_last_alloc / RT_PAGE_AFFINITY_BLOCK_SIZE);
    return (last_alloc + (1u << size_bits)) & AFFID_BITS_MASK(size_bits);
}

static void *_do_pages_alloc_noaff(rt_uint32_t size_bits, size_t flags)
{
    void *rc = RT_NULL;

    if (size_bits < AFFID_BLK_BITS)
    {
        int try_affid = _get_balanced_id(size_bits);
        size_t numof_id = AFFID_NUMOF_ID_IN_SET(size_bits);
        size_t valid_affid_mask = numof_id - 1;

        for (size_t i = 0; i < numof_id; i++, try_affid += 1 << size_bits)
        {
            rc = _do_pages_alloc(size_bits, flags, try_affid & valid_affid_mask);
            if (rc)
            {
                break;
            }
        }
    }
    else
    {
        rc = _do_pages_alloc(size_bits, flags, 0);
    }

    if (!rc)
    {
        RT_ASSERT(0);
    }
    return rc;
}

void *rt_pages_alloc(rt_uint32_t size_bits)
{
    return _do_pages_alloc_noaff(size_bits, 0);
}

void *rt_pages_alloc_ext(rt_uint32_t size_bits, size_t flags)
{
    return _do_pages_alloc_noaff(size_bits, flags);
}

void *rt_pages_alloc_tagged(rt_uint32_t size_bits, long affid, size_t flags)
{
    rt_page_t current;

    current = _do_pages_alloc(size_bits, flags, affid);
    if (current && RT_PAGE_PICK_AFFID(current) != affid)
    {
        RT_ASSERT(0);
    }

    return current;
}

int rt_pages_free(void *addr, rt_uint32_t size_bits)
{
    struct rt_page *p;
    pgls_agr_t *page_list = _get_page_list(addr);
    int real_free = 0;

    p = rt_page_addr2page(addr);
    if (p)
    {
        rt_base_t level;
        level = rt_spin_lock_irqsave(&_pgmgr_lock);
        real_free = _pages_free(page_list, p, addr, size_bits);
        if (real_free)
        {
            _freed_nr += 1 << size_bits;
            if (page_list == page_list_high)
            {
                _freed_nr_hi += 1 << size_bits;
            }
            TRACE_FREE(p, size_bits);
        }
        rt_spin_unlock_irqrestore(&_pgmgr_lock, level);
    }

    return real_free;
}

/* debug command */
int rt_page_list(void) __attribute__((alias("list_page")));

#define PGNR2SIZE(nr) ((nr)*ARCH_PAGE_SIZE / 1024)

static void _dump_page_list(int order, rt_page_t lp, rt_page_t hp,
                            rt_size_t *pfree)
{
    rt_size_t free = 0;

    rt_kprintf("level %d ", order);

    while (lp)
    {
        free += (1UL << order);
        rt_kprintf("[L:0x%08p]", rt_page_page2addr(lp));
        lp = lp->next;
    }
    while (hp)
    {
        free += (1UL << order);
        rt_kprintf("[H:0x%08p]", rt_page_page2addr(hp));
        hp = hp->next;
    }

    rt_kprintf("\n");

    *pfree += free;
}

int list_page(void)
{
    int i;
    rt_size_t free = 0;
    rt_size_t installed = _page_nr;
    rt_base_t level;

    level = rt_spin_lock_irqsave(&_pgmgr_lock);

    /* dump affinity map area */
    for (i = 0; i < AFFID_BLK_BITS; i++)
    {
        rt_page_t *iter_lo = PGLS_GET_AFF_MAP(page_list_low[i]);
        rt_page_t *iter_hi = PGLS_GET_AFF_MAP(page_list_high[i]);
        rt_size_t list_len = AFFID_NUMOF_ID_IN_SET(i);
        for (size_t j = 0; j < list_len; j++)
        {
            _dump_page_list(i, iter_lo[j], iter_hi[j], &free);
        }
    }

    /* dump normal page list */
    for (; i < RT_PAGE_MAX_ORDER; i++)
    {
        rt_page_t lp = page_list_low[i].page_list;
        rt_page_t hp = page_list_high[i].page_list;

        _dump_page_list(i, lp, hp, &free);
    }

    rt_spin_unlock_irqrestore(&_pgmgr_lock, level);
    rt_kprintf("-------------------------------\n");
    rt_kprintf("Page Summary:\n => free/installed:\n  0x%lx/0x%lx (%ld/%ld KB)\n",
               free, installed, PGNR2SIZE(free), PGNR2SIZE(installed));

    rt_kprintf(" => Installed Pages Region:\n");
    _print_region_list();
    rt_kprintf("-------------------------------\n");

    return 0;
}
MSH_CMD_EXPORT(list_page, show page info);

void rt_page_get_info(rt_size_t *total_nr, rt_size_t *free_nr)
{
    *total_nr = _page_nr;
    *free_nr = _freed_nr;
}

void rt_page_high_get_info(rt_size_t *total_nr, rt_size_t *free_nr)
{
    *total_nr = _page_nr_hi;
    *free_nr = _freed_nr_hi;
}

static void _invalid_uninstalled_shadow(rt_page_t start, rt_page_t end)
{
    for (rt_page_t iter = start; iter < end; iter++)
    {
        rt_base_t frame = (rt_base_t)rt_page_page2addr(iter);
        struct installed_page_reg *page_reg = _find_page_region(frame);
        if (page_reg)
        {
            continue;
        }
        iter->size_bits = ARCH_ADDRESS_WIDTH_BITS;
    }
}

static void _install_page(rt_page_t mpr_head, rt_region_t region,
                          void (*insert)(rt_page_t *ppg, rt_page_t page, rt_uint32_t size_bits))
{
    pgls_agr_t *page_list;
    rt_page_t *page_head;
    rt_region_t shadow;
    const rt_base_t pvoffset = PV_OFFSET;

    _page_nr += ((region.end - region.start) >> ARCH_PAGE_SHIFT);
    _freed_nr += ((region.end - region.start) >> ARCH_PAGE_SHIFT);

    shadow.start = region.start & ~shadow_mask;
    shadow.end = CEIL(region.end, shadow_mask + 1);

    if (shadow.end + pvoffset > UINT32_MAX)
        _high_page_configured = 1;

    rt_page_t shad_head = addr_to_page(mpr_head, (void *)shadow.start);
    rt_page_t shad_tail = addr_to_page(mpr_head, (void *)shadow.end);
    rt_page_t head = addr_to_page(mpr_head, (void *)region.start);
    rt_page_t tail = addr_to_page(mpr_head, (void *)region.end);

    /* mark shadow page records not belongs to other region as illegal */
    _invalid_uninstalled_shadow(shad_head, head);
    _invalid_uninstalled_shadow(tail, shad_tail);

    /* insert reserved pages to list */
    const int max_order = RT_PAGE_MAX_ORDER + ARCH_PAGE_SHIFT - 1;
    while (region.start != region.end)
    {
        struct rt_page *p;
        int align_bits;
        int size_bits;
        int page_order;

        size_bits =
            ARCH_ADDRESS_WIDTH_BITS - 1 - rt_hw_clz(region.end - region.start);
        align_bits = rt_hw_ctz(region.start);
        if (align_bits < size_bits)
        {
            size_bits = align_bits;
        }
        if (size_bits > max_order)
        {
            size_bits = max_order;
        }

        p = addr_to_page(mpr_head, (void *)region.start);
        p->size_bits = ARCH_ADDRESS_WIDTH_BITS;
        p->ref_cnt = 0;

        /* insert to list */
        page_list = _get_page_list((void *)region.start);
        if (page_list == page_list_high)
        {
            _page_nr_hi += 1 << (size_bits - ARCH_PAGE_SHIFT);
            _freed_nr_hi += 1 << (size_bits - ARCH_PAGE_SHIFT);
        }

        page_order = size_bits - ARCH_PAGE_SHIFT;
        page_head = _get_pgls_head_by_page(page_list, p, page_order);
        insert(page_head, (rt_page_t)((char *)p - early_offset), page_order);
        region.start += (1UL << size_bits);
    }
}

static void *_aligned_to_affinity(rt_ubase_t head_page_pa, void *mapped_to)
{
#define AFFBLK_MASK (RT_PAGE_AFFINITY_BLOCK_SIZE - 1)
    rt_ubase_t head_page_pg_aligned;
    rt_ubase_t aligned_affblk_tag = (long)mapped_to & AFFBLK_MASK;

    head_page_pg_aligned =
        ((long)head_page_pa & ~AFFBLK_MASK) | aligned_affblk_tag;
    if (head_page_pg_aligned < head_page_pa)
    {
        /* find the page forward */
        head_page_pg_aligned += RT_PAGE_AFFINITY_BLOCK_SIZE;
    }

    return (void *)head_page_pg_aligned;
}

void rt_page_init(rt_region_t reg)
{
    int i;
    rt_region_t shadow;

    /* setup install page status */
    rt_spin_lock_init(&_init_region.lock);
    _init_region.region_area = reg;
    _init_region.next = RT_NULL;
#ifdef RT_DEBUGGING_PAGE_POISON
    _init_region.usage_trace = _init_region_usage_trace;
#endif /* RT_DEBUGGING_PAGE_POISON */
    _inst_page_reg_head = &_init_region;

    /* adjust install region. inclusive start, exclusive end */
    reg.start += ARCH_PAGE_MASK;
    reg.start &= ~ARCH_PAGE_MASK;
    reg.end &= ~ARCH_PAGE_MASK;
    if (reg.end <= reg.start)
    {
        LOG_E("region end(%p) must greater than start(%p)", reg.start, reg.end);
        RT_ASSERT(0);
    }

    shadow.start = reg.start & ~shadow_mask;
    shadow.end = CEIL(reg.end, shadow_mask + 1);
    LOG_D("[Init page] start: 0x%lx, end: 0x%lx, total: 0x%lx", reg.start,
          reg.end, page_nr);

    int err;

    /* init free list */
    rt_page_t *aff_pgls_iter_lo = aff_pglist_low;
    rt_page_t *aff_pgls_iter_hi = aff_pglist_high;
    for (i = 0; i < AFFID_BLK_BITS; i++)
    {
        long stride = AFFID_NUMOF_ID_IN_SET(i);
        PGLS_FROM_AFF_MAP(page_list_low[i], aff_pgls_iter_lo);
        PGLS_FROM_AFF_MAP(page_list_high[i], aff_pgls_iter_hi);
        aff_pgls_iter_lo += stride;
        aff_pgls_iter_hi += stride;
    }

    for (; i < RT_PAGE_MAX_ORDER; i++)
    {
        page_list_low[i].page_list = 0;
        page_list_high[i].page_list = 0;
    }

    /* map MPR area */
    err = rt_aspace_map_static(&rt_kernel_space, &mpr_varea, &rt_mpr_start,
                               rt_mpr_size, MMU_MAP_K_RWCB, MMF_MAP_FIXED,
                               &mm_page_mapper, 0);

    if (err != RT_EOK)
    {
        LOG_E("MPR map failed with size %lx at %p", rt_mpr_size, rt_mpr_start);
        RT_ASSERT(0);
    }

    /* calculate footprint */
    init_mpr_align_start =
        (rt_size_t)addr_to_page(page_start, (void *)shadow.start) &
        ~ARCH_PAGE_MASK;
    init_mpr_align_end =
        CEIL(addr_to_page(page_start, (void *)shadow.end), ARCH_PAGE_SIZE);
    rt_size_t init_mpr_size = init_mpr_align_end - init_mpr_align_start;
    rt_size_t init_mpr_npage = init_mpr_size >> ARCH_PAGE_SHIFT;

    /* find available aligned page */
    init_mpr_cont_start = _aligned_to_affinity(reg.start,
                                               (void *)init_mpr_align_start);

    rt_size_t init_mpr_cont_end = (rt_size_t)init_mpr_cont_start + init_mpr_size;
    early_offset = (rt_size_t)init_mpr_cont_start - init_mpr_align_start;
    rt_page_t mpr_cont = (void *)((char *)rt_mpr_start + early_offset);

    /* mark init mpr pages as illegal */
    rt_page_t head_cont = addr_to_page(mpr_cont, (void *)reg.start);
    rt_page_t tail_cont = addr_to_page(mpr_cont, (void *)reg.end);
    for (rt_page_t iter = head_cont; iter < tail_cont; iter++)
    {
        iter->size_bits = ARCH_ADDRESS_WIDTH_BITS;
    }

    reg.start = init_mpr_cont_end;
    _install_page(mpr_cont, reg, _early_page_insert);

    pages_alloc_handler = _early_pages_alloc;
    /* doing the page table bushiness */
    if (rt_aspace_load_page(&rt_kernel_space, (void *)init_mpr_align_start, init_mpr_npage))
    {
        LOG_E("%s: failed to load pages", __func__);
        RT_ASSERT(0);
    }

    if (rt_hw_mmu_tbl_get() == rt_kernel_space.page_table)
        rt_page_cleanup();
}

static int _load_mpr_area(void *head, void *tail)
{
    int err = 0;
    char *iter = (char *)((rt_ubase_t)head & ~ARCH_PAGE_MASK);
    tail = (void *)CEIL(tail, ARCH_PAGE_SIZE);

    while (iter != tail)
    {
        void *paddr = rt_kmem_v2p(iter);
        if (paddr == ARCH_MAP_FAILED)
        {
            err = rt_aspace_load_page(&rt_kernel_space, iter, 1);
            if (err != RT_EOK)
            {
                LOG_E("%s: failed to load page", __func__);
                break;
            }
        }
        iter += ARCH_PAGE_SIZE;
    }
    return err;
}

static int _get_mpr_ready_n_install(rt_ubase_t inst_head, rt_ubase_t inst_end)
{
    int err;
    rt_region_t shadow;
    rt_region_t region =
    {
        .start = inst_head,
        .end = inst_end,
    };
    void *head, *tail;

    shadow.start = region.start & ~shadow_mask;
    shadow.end = CEIL(region.end, shadow_mask + 1);
    head = addr_to_page(page_start, (void *)shadow.start);
    tail = addr_to_page(page_start, (void *)shadow.end);

    err = _load_mpr_area(head, tail);

    if (err == RT_EOK)
    {
        rt_ubase_t level = rt_spin_lock_irqsave(&_pgmgr_lock);
        _install_page(rt_mpr_start, region, _page_insert);
        rt_spin_unlock_irqrestore(&_pgmgr_lock, level);
    }

    return err;
}

static void _update_region_list(struct installed_page_reg *member,
                                rt_ubase_t inst_head, rt_ubase_t inst_end,
                                rt_bitmap_t *ut_bitmap)
{
    rt_spin_lock_init(&member->lock);

    rt_spin_lock(&_inst_page_reg_lock);

    member->region_area.start = inst_head;
    member->region_area.end = inst_end;

#ifdef RT_DEBUGGING_PAGE_POISON
    member->usage_trace = ut_bitmap;
#else
    RT_UNUSED(ut_bitmap);
#endif /* RT_DEBUGGING_PAGE_POISON */

    member->next = _inst_page_reg_head;
    _inst_page_reg_head = member;

    rt_spin_unlock(&_inst_page_reg_lock);
}

#define _PAGE_STRIPE (1 << (RT_PAGE_MAX_ORDER + ARCH_PAGE_SHIFT - 1))
int rt_page_install(rt_region_t region)
{
    int err = -RT_EINVAL;

    if (region.end != region.start && !(region.start & ARCH_PAGE_MASK) &&
        !(region.end & ARCH_PAGE_MASK))
    {
        rt_ubase_t inst_head = region.start;
        rt_ubase_t inst_end = region.end;
        rt_ubase_t iter = inst_head;
        int pages_count = (inst_end - inst_head) / ARCH_PAGE_SIZE;
        struct installed_page_reg *installed_pgreg =
            rt_calloc(1, sizeof(struct installed_page_reg) +
                      RT_BITMAP_LEN(pages_count) * sizeof(rt_bitmap_t));

        if (installed_pgreg)
        {
            _update_region_list(installed_pgreg, inst_head, inst_end,
                                (rt_bitmap_t *)(installed_pgreg + 1));

            if ((rt_ubase_t)iter & shadow_mask)
            {
                iter = RT_ALIGN((rt_ubase_t)inst_head, _PAGE_STRIPE);
                _get_mpr_ready_n_install(inst_head, iter < inst_end ? iter : inst_end);
            }

            for (rt_ubase_t next = iter + _PAGE_STRIPE; next < inst_end;
                 iter = next, next += _PAGE_STRIPE)
            {
                _get_mpr_ready_n_install(iter, next);
            }

            if (iter < inst_end)
            {
                _get_mpr_ready_n_install(iter, inst_end);
            }
        }
    }
    return err;
}

void rt_page_cleanup(void)
{
    early_offset = 0;
    pages_alloc_handler = _pages_alloc;
}
