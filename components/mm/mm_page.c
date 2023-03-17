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

RT_CTASSERT(order_huge_pg, RT_PAGE_MAX_ORDER > ARCH_PAGE_SHIFT - 2);
RT_CTASSERT(size_width, sizeof(rt_size_t) == sizeof(void *));

#ifdef RT_USING_SMART
#include "lwp_arch_comm.h"
#endif /* RT_USING_SMART */

static rt_size_t init_mpr_align_start;
static rt_size_t init_mpr_align_end;
static void *init_mpr_cont_start;

static struct rt_varea mpr_varea;

static struct rt_page *page_list[RT_PAGE_MAX_ORDER];

#define page_start ((rt_page_t)rt_mpr_start)

static rt_size_t page_nr;
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

static void on_page_fault(struct rt_varea *varea, struct rt_mm_fault_msg *msg)
{
    void *init_start = (void *)init_mpr_align_start;
    void *init_end = (void *)init_mpr_align_end;
    if (msg->vaddr < init_end && msg->vaddr >= init_start)
    {
        rt_size_t offset = msg->vaddr - init_start;
        msg->response.status = MM_FAULT_STATUS_OK;
        msg->response.vaddr = init_mpr_cont_start + offset;
        msg->response.size = ARCH_PAGE_SIZE;
    }
    else
    {
        void *raw_page = rt_pages_alloc(0);
        msg->response.status = MM_FAULT_STATUS_OK;
        msg->response.vaddr = raw_page;
        msg->response.size = ARCH_PAGE_SIZE;
    }
}

static struct rt_mem_obj mm_page_mapper = {
    .get_name = get_name,
    .on_page_fault = on_page_fault,
    .hint_free = hint_free,
};

static inline void *page_to_addr(rt_page_t page)
{
    return (void *)((page - page_start) << ARCH_PAGE_SHIFT) - PV_OFFSET;
}

static inline rt_page_t addr_to_page(rt_page_t pg_start, void *addr)
{
    addr += PV_OFFSET;
    return &pg_start[((uintptr_t)addr >> ARCH_PAGE_SHIFT)];
}

#define FLOOR(val, align) (((rt_size_t)(val) + (align)-1) & ~((align)-1))

const rt_size_t shadow_mask =
    ((1ul << (RT_PAGE_MAX_ORDER + ARCH_PAGE_SHIFT - 1)) - 1);

const rt_size_t rt_mpr_size = FLOOR(
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

static inline struct rt_page *buddy_get(struct rt_page *p,
                                        rt_uint32_t size_bits)
{
    rt_size_t addr;

    addr = (rt_size_t)rt_page_page2addr(p);
    addr ^= (1UL << (size_bits + ARCH_PAGE_SHIFT));
    return rt_page_addr2page((void *)addr);
}

static void page_remove(struct rt_page *p, rt_uint32_t size_bits)
{
    if (p->pre)
    {
        p->pre->next = p->next;
    }
    else
    {
        page_list[size_bits] = p->next;
    }

    if (p->next)
    {
        p->next->pre = p->pre;
    }

    p->size_bits = ARCH_ADDRESS_WIDTH_BITS;
}

static void page_insert(struct rt_page *p, rt_uint32_t size_bits)
{
    p->next = page_list[size_bits];
    if (p->next)
    {
        p->next->pre = p;
    }
    p->pre = 0;
    page_list[size_bits] = p;
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
    page_head = (void *)page_head + early_offset;
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

static int _pages_free(struct rt_page *p, rt_uint32_t size_bits)
{
    rt_uint32_t level = size_bits;
    struct rt_page *buddy;

    RT_ASSERT(p >= page_start);
    RT_ASSERT((void *)p < rt_mpr_start + rt_mpr_size);
    RT_ASSERT(rt_kmem_v2p(p));
    RT_ASSERT(p->ref_cnt > 0);
    RT_ASSERT(p->size_bits == ARCH_ADDRESS_WIDTH_BITS);
    RT_ASSERT(size_bits < RT_PAGE_MAX_ORDER);

    p->ref_cnt--;
    if (p->ref_cnt != 0)
    {
        return 0;
    }

    while (level < RT_PAGE_MAX_ORDER - 1)
    {
        buddy = buddy_get(p, level);
        if (buddy && buddy->size_bits == level)
        {
            page_remove(buddy, level);
            p = (p < buddy) ? p : buddy;
            level++;
        }
        else
        {
            break;
        }
    }
    page_insert(p, level);
    return 1;
}

static struct rt_page *_pages_alloc(rt_uint32_t size_bits)
{
    struct rt_page *p;

    if (page_list[size_bits])
    {
        p = page_list[size_bits];
        page_remove(p, size_bits);
    }
    else
    {
        rt_uint32_t level;

        for (level = size_bits + 1; level < RT_PAGE_MAX_ORDER; level++)
        {
            if (page_list[level])
            {
                break;
            }
        }
        if (level == RT_PAGE_MAX_ORDER)
        {
            return 0;
        }

        p = page_list[level];
        page_remove(p, level);
        while (level > size_bits)
        {
            page_insert(p, level - 1);
            p = buddy_get(p, level - 1);
            level--;
        }
    }
    p->size_bits = ARCH_ADDRESS_WIDTH_BITS;
    p->ref_cnt = 1;
    return p;
}

static void _early_page_remove(rt_page_t page, rt_uint32_t size_bits)
{
    rt_page_t page_cont = (void *)page + early_offset;
    if (page_cont->pre)
    {
        rt_page_t pre_cont = (void *)page_cont->pre + early_offset;
        pre_cont->next = page_cont->next;
    }
    else
    {
        page_list[size_bits] = page_cont->next;
    }

    if (page_cont->next)
    {
        rt_page_t next_cont = (void *)page_cont->next + early_offset;
        next_cont->pre = page_cont->pre;
    }

    page_cont->size_bits = ARCH_ADDRESS_WIDTH_BITS;
}

static void _early_page_insert(rt_page_t page, int size_bits)
{
    RT_ASSERT((void *)page >= rt_mpr_start &&
              (void *)page - rt_mpr_start < +rt_mpr_size);
    rt_page_t page_cont = (void *)page + early_offset;

    page_cont->next = page_list[size_bits];
    if (page_cont->next)
    {
        rt_page_t next_cont = (void *)page_cont->next + early_offset;
        next_cont->pre = page;
    }
    page_cont->pre = 0;
    page_list[size_bits] = page;
    page_cont->size_bits = size_bits;
}

static struct rt_page *_early_pages_alloc(rt_uint32_t size_bits)
{
    struct rt_page *p;

    if (page_list[size_bits])
    {
        p = page_list[size_bits];
        _early_page_remove(p, size_bits);
    }
    else
    {
        rt_uint32_t level;

        for (level = size_bits + 1; level < RT_PAGE_MAX_ORDER; level++)
        {
            if (page_list[level])
            {
                break;
            }
        }
        if (level == RT_PAGE_MAX_ORDER)
        {
            return 0;
        }

        p = page_list[level];
        _early_page_remove(p, level);
        while (level > size_bits)
        {
            _early_page_insert(p, level - 1);
            p = buddy_get(p, level - 1);
            level--;
        }
    }
    rt_page_t page_cont = (void *)p + early_offset;
    page_cont->size_bits = ARCH_ADDRESS_WIDTH_BITS;
    page_cont->ref_cnt = 1;
    return p;
}

int rt_page_ref_get(void *addr, rt_uint32_t size_bits)
{
    struct rt_page *p;
    rt_base_t level;
    int ref;

    p = rt_page_addr2page(addr);
    level = rt_hw_interrupt_disable();
    ref = _pages_ref_get(p, size_bits);
    rt_hw_interrupt_enable(level);
    return ref;
}

void rt_page_ref_inc(void *addr, rt_uint32_t size_bits)
{
    struct rt_page *p;
    rt_base_t level;

    p = rt_page_addr2page(addr);
    level = rt_hw_interrupt_disable();
    _pages_ref_inc(p, size_bits);
    rt_hw_interrupt_enable(level);
}

static rt_page_t (*pages_alloc_handler)(rt_uint32_t size_bits);

void *rt_pages_alloc(rt_uint32_t size_bits)
{
    void *alloc_buf = RT_NULL;
    struct rt_page *p;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    p = pages_alloc_handler(size_bits);
    rt_hw_interrupt_enable(level);
    if (p)
    {
        alloc_buf = page_to_addr(p);
    }
    return alloc_buf;
}

int rt_pages_free(void *addr, rt_uint32_t size_bits)
{
    struct rt_page *p;
    int real_free = 0;

    p = rt_page_addr2page(addr);
    if (p)
    {
        rt_base_t level;
        level = rt_hw_interrupt_disable();
        real_free = _pages_free(p, size_bits);
        rt_hw_interrupt_enable(level);
    }
    return real_free;
}

void rt_page_list(void) __attribute__((alias("list_page")));

void list_page(void)
{
    int i;
    rt_size_t total = 0;

    rt_base_t level;
    level = rt_hw_interrupt_disable();

    for (i = 0; i < RT_PAGE_MAX_ORDER; i++)
    {
        struct rt_page *p = page_list[i];

        rt_kprintf("level %d ", i);

        while (p)
        {
            total += (1UL << i);
            rt_kprintf("[0x%08p]", rt_page_page2addr(p));
            p = p->next;
        }
        rt_kprintf("\n");
    }
    rt_hw_interrupt_enable(level);
    rt_kprintf("free pages is 0x%08lx (%ld KB)\n", total, total * ARCH_PAGE_SIZE / 1024);
    rt_kprintf("-------------------------------\n");
}
MSH_CMD_EXPORT(list_page, show page info);

void rt_page_get_info(rt_size_t *total_nr, rt_size_t *free_nr)
{
    int i;
    rt_size_t total_free = 0;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    for (i = 0; i < RT_PAGE_MAX_ORDER; i++)
    {
        struct rt_page *p = page_list[i];

        while (p)
        {
            total_free += (1UL << i);
            p = p->next;
        }
    }
    rt_hw_interrupt_enable(level);
    *total_nr = page_nr;
    *free_nr = total_free;
}

void rt_page_init(rt_region_t reg)
{
    int i;
    rt_region_t shadow;

    /* inclusive start, exclusive end */
    reg.start += ARCH_PAGE_MASK;
    reg.start &= ~ARCH_PAGE_MASK;
    reg.end &= ~ARCH_PAGE_MASK;
    if (reg.end <= reg.start)
    {
        LOG_E("region end(%p) must greater than start(%p)", reg.start, reg.end);
        RT_ASSERT(0);
    }
    page_nr = ((reg.end - reg.start) >> ARCH_PAGE_SHIFT);
    shadow.start = reg.start & ~shadow_mask;
    shadow.end = FLOOR(reg.end, shadow_mask + 1);
    LOG_D("[Init page] start: 0x%lx, end: 0x%lx, total: 0x%lx", reg.start,
          reg.end, page_nr);

    int err;

    /* init free list */
    for (i = 0; i < RT_PAGE_MAX_ORDER; i++)
    {
        page_list[i] = 0;
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
        FLOOR(addr_to_page(page_start, (void *)shadow.end), ARCH_PAGE_SIZE);
    rt_size_t init_mpr_size = init_mpr_align_end - init_mpr_align_start;
    rt_size_t init_mpr_npage = init_mpr_size >> ARCH_PAGE_SHIFT;

    init_mpr_cont_start = (void *)reg.start;
    void *init_mpr_cont_end = init_mpr_cont_start + init_mpr_size;
    early_offset = init_mpr_cont_start - (void *)init_mpr_align_start;
    rt_page_t mpr_cont = rt_mpr_start + early_offset;

    /* mark init mpr pages as illegal */
    rt_page_t head_cont = addr_to_page(mpr_cont, (void *)reg.start);
    rt_page_t tail_cont = addr_to_page(mpr_cont, (void *)reg.end);
    for (rt_page_t iter = head_cont; iter < tail_cont; iter++)
    {
        iter->size_bits = ARCH_ADDRESS_WIDTH_BITS;
    }

    /* mark shadow pages as illegal */
    rt_page_t shad_head_cont = addr_to_page(mpr_cont, (void *)shadow.start);
    for (rt_page_t iter = shad_head_cont; iter < head_cont; iter++)
    {
        iter->size_bits = ARCH_ADDRESS_WIDTH_BITS;
    }
    rt_page_t shad_tail_cont = addr_to_page(mpr_cont, (void *)shadow.end);
    for (rt_page_t iter = tail_cont; iter < shad_tail_cont; iter++)
    {
        iter->size_bits = ARCH_ADDRESS_WIDTH_BITS;
    }

    /* insert reserved pages to list */
    reg.start = (rt_size_t)init_mpr_cont_end;
    const int max_order = RT_PAGE_MAX_ORDER + ARCH_PAGE_SHIFT - 1;
    while (reg.start != reg.end)
    {
        struct rt_page *p;
        int align_bits;
        int size_bits;

        size_bits =
            ARCH_ADDRESS_WIDTH_BITS - 1 - rt_hw_clz(reg.end - reg.start);
        align_bits = rt_hw_ctz(reg.start);
        if (align_bits < size_bits)
        {
            size_bits = align_bits;
        }
        if (size_bits > max_order)
        {
            size_bits = max_order;
        }

        p = addr_to_page(mpr_cont, (void *)reg.start);
        p->size_bits = ARCH_ADDRESS_WIDTH_BITS;
        p->ref_cnt = 0;

        /* insert to list */
        _early_page_insert((void *)p - early_offset,
                           size_bits - ARCH_PAGE_SHIFT);
        reg.start += (1UL << size_bits);
    }

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
    void *iter = (void *)((uintptr_t)head & ~ARCH_PAGE_MASK);
    tail = (void *)FLOOR(tail, ARCH_PAGE_SIZE);

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

int rt_page_install(rt_region_t region)
{
    int err = -RT_EINVAL;
    if (region.end != region.start && !(region.start & ARCH_PAGE_MASK) &&
        !(region.end & ARCH_PAGE_MASK) &&
        !((region.end - region.start) & shadow_mask))
    {
        void *head = addr_to_page(page_start, (void *)region.start);
        void *tail = addr_to_page(page_start, (void *)region.end);

        page_nr += ((region.end - region.start) >> ARCH_PAGE_SHIFT);

        err = _load_mpr_area(head, tail);

        if (err == RT_EOK)
        {
            while (region.start != region.end)
            {
                struct rt_page *p;
                int size_bits;

                size_bits = RT_PAGE_MAX_ORDER - 1;
                p = addr_to_page(page_start, (void *)region.start);
                p->size_bits = ARCH_ADDRESS_WIDTH_BITS;
                p->ref_cnt = 1;

                _pages_free(p, size_bits);
                region.start += (1UL << (size_bits + ARCH_PAGE_SHIFT));
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
