/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-01     Jesven      The first version
 */
#include <stdint.h>

#include <rthw.h>
#include <rtthread.h>

#ifdef RT_USING_USERSPACE

#include <page.h>
#include <mmu.h>

#define ARCH_PAGE_LIST_SIZE     (ARCH_ADDRESS_WIDTH_BITS - ARCH_PAGE_SHIFT)

#define DBG_TAG "PAGE"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

struct page
{
    struct page *next;  // same level next
    struct page *pre;   // same level pre
    uint32_t size_bits; // if is ARCH_ADDRESS_WIDTH_BITS, means not free
};

static struct page* page_start;
static void*  page_addr;
static size_t page_nr;

static struct page *page_list[ARCH_PAGE_LIST_SIZE];

size_t rt_page_bits(size_t size)
{
    int bit;

    bit = __builtin_clz(size);
    bit = (31 - bit);
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

static struct page * addr_to_page(void *addr)
{
    size_t off;

    if (addr < page_addr)
    {
        return 0;
    }
    off = addr - page_addr;
    off >>= ARCH_PAGE_SHIFT;
    if (off >= page_nr)
    {
        return 0;
    }
    return &page_start[off];
}

static void* page_to_addr(struct page* p)
{
    if (!p)
    {
        return 0;
    }
    return page_addr + ((p - page_start) << ARCH_PAGE_SHIFT);
}

static inline struct page *buddy_get(struct page *p, uint32_t size_bits)
{
    size_t addr;

    addr = (size_t)page_to_addr(p);
    addr ^= (1UL << (size_bits + ARCH_PAGE_SHIFT));
    return addr_to_page((void*)addr);
}

static void page_remove(struct page *p, uint32_t size_bits)
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

static void page_insert(struct page *p, uint32_t size_bits)
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

static void _pages_free(struct page *p, uint32_t size_bits)
{
    uint32_t level = size_bits;
    uint32_t high = ARCH_ADDRESS_WIDTH_BITS - size_bits - 1;
    struct page *buddy;

    while (level < high)
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
}

static struct page *_pages_alloc(uint32_t size_bits)
{
    struct page *p;

    if (page_list[size_bits])
    {
        p = page_list[size_bits];
        page_remove(p, size_bits);
    }
    else
    {
        uint32_t level;
        uint32_t high = ARCH_ADDRESS_WIDTH_BITS - size_bits - 1;

        for (level = size_bits + 1; level <= high; level++)
        {
            if (page_list[level])
            {
                break;
            }
        }
        if (level == high + 1)
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
    return p;
}

void *rt_pages_alloc(uint32_t size_bits)
{
    struct page *p;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    p = _pages_alloc(size_bits);
    rt_hw_interrupt_enable(level);
    return page_to_addr(p);
}

void rt_pages_free(void *addr, uint32_t size_bits)
{
    struct page *p;

    p = addr_to_page(addr);
    if (p)
    {
        rt_base_t level;
        level = rt_hw_interrupt_disable();
        _pages_free(p, size_bits);
        rt_hw_interrupt_enable(level);
    }
}

void rt_pageinfo_dump(void)
{
    int i;
    size_t total = 0;

    rt_base_t level;
    level = rt_hw_interrupt_disable();

    for (i = 0; i < ARCH_PAGE_LIST_SIZE; i++)
    {
        struct page *p = page_list[i];

        rt_kprintf("level %d ", i);

        while (p)
        {
            total += (1UL << i);
            rt_kprintf("[0x%08x]", page_to_addr(p));
            p = p->next;
        }
        rt_kprintf("\n");
    }
    rt_hw_interrupt_enable(level);
    rt_kprintf("free pages is %08x\n", total);
    rt_kprintf("-------------------------------\n");
}
MSH_CMD_EXPORT(rt_pageinfo_dump, show page info);

void rt_page_get_info(size_t *total_nr, size_t *free_nr)
{
    int i;
    size_t total_free = 0;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    for (i = 0; i < ARCH_PAGE_LIST_SIZE; i++)
    {
        struct page *p = page_list[i];

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
    uint32_t align_bits;
    uint32_t size_bits;
    int i;

    LOG_D("split 0x%08x 0x%08x\n", reg.start, reg.end);

    reg.start += ARCH_PAGE_MASK;
    reg.start &= ~ARCH_PAGE_MASK;

    reg.end &= ~ARCH_PAGE_MASK;

    {
        int nr = ARCH_PAGE_SIZE/sizeof(struct page);
        int total = (reg.end - reg.start) >> ARCH_PAGE_SHIFT;
        int mnr = (total + nr)/(nr + 1);

        LOG_D("nr = 0x%08x\n", nr);
        LOG_D("total = 0x%08x\n", total);
        LOG_D("mnr = 0x%08x\n", mnr);

        page_start = (struct page*)reg.start;
        reg.start += (mnr << ARCH_PAGE_SHIFT);
        page_addr = (void*)reg.start;
        page_nr = (reg.end - reg.start) >> ARCH_PAGE_SHIFT;
    }

    LOG_D("align 0x%08x 0x%08x\n", reg.start, reg.end);

    /* init page struct */
    for (i = 0; i < page_nr; i++)
    {
        page_start[i].size_bits = ARCH_ADDRESS_WIDTH_BITS;
    }

    /* init free list */
    for (i = 0; i < ARCH_PAGE_LIST_SIZE; i++)
    {
        page_list[i] = 0;
    }

    while (reg.start != reg.end)
    {
        size_bits = ARCH_ADDRESS_WIDTH_BITS - 1 - __builtin_clz(reg.end - reg.start);
        align_bits = __builtin_ctz(reg.start);
        if (align_bits < size_bits)
        {
            size_bits = align_bits;
        }

        _pages_free(addr_to_page((void*)reg.start), size_bits - ARCH_PAGE_SHIFT);

        reg.start += (1U << size_bits);
    }
}
#endif
