/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-29     lizhirui     first version
 */

#include <stdint.h>
#include <rtthread.h>
#include <rthw.h>
#include <board.h>
#include "riscv.h"
#include "riscv_mmu.h"
#include "page.h"

#define PAGE_LIST_SIZE (ADDRESS_WIDTH_BITS - PAGE_OFFSET_BIT)

//#define RT_PAGE_DEBUG

#ifdef RT_PAGE_DEBUG
    #define dprintf rt_kprintf
#else
    #define dprintf(...)
#endif

#define RT_PASSERT RT_ASSERT

struct page
{
    struct page *next;
    struct page *pre;
    rt_size_t size_bits;
    int ref_cnt;
};

static struct page *page_start;
static void *page_addr;
static rt_size_t page_nr;

#define PAGE_VALID(pageobj) RT_PASSERT(!((((rt_size_t)pageobj) - ((rt_size_t)page_start)) % sizeof(struct page)))

static struct page *page_list[ADDRESS_WIDTH_BITS];

//get the correct page_list index according the actual size 
rt_size_t rt_page_bits(rt_size_t size)
{
    rt_base_t bit;

    //get highest 1 bit index
    bit = __builtin_clzl(size);
    bit = sizeof(rt_size_t) * 8 - bit - 1;

    //if bits remained has 1,the large page is needed
    if((size ^ (1UL << bit)) != 0)
    {
        bit++;
    }

    bit -= PAGE_OFFSET_BIT;

    if(bit < 0)
    {
        bit = 0;
    }

    return (rt_size_t)bit;
}

//convert physical address to page object
static struct page *addr_to_page(void *addr)
{
    rt_size_t off;

    if(addr < page_addr)
    {
        return 0;
    }

    RT_PASSERT(__CHECKALIGN(addr,PAGE_OFFSET_BIT));
    off = ((rt_size_t)addr) - ((rt_size_t)page_addr);
    off >>= PAGE_OFFSET_BIT;

    if(off >= page_nr)
    {
        return 0;
    }

    return &page_start[off];
}

//convert page object to physical address
static void *page_to_addr(struct page *p)
{
    if(!p)
    {
        return 0;
    }

    PAGE_VALID(p);
    return (void *)(((rt_size_t)page_addr) + ((p - page_start) << PAGE_OFFSET_BIT));
}

//get the buddy of page specified by p(split a page to two page according to size_bits)
static inline struct page *buddy_get(struct page *p,rt_size_t size_bits)
{
    rt_size_t addr;

    PAGE_VALID(p);
    addr = (rt_size_t)page_to_addr(p);
    RT_PASSERT(__CHECKALIGN(addr,size_bits + PAGE_OFFSET_BIT));
    addr ^= (1UL << (size_bits + PAGE_OFFSET_BIT));
    return addr_to_page((void *)addr);
}

//remove the page from the linked list
static void page_remove(struct page *p,rt_size_t size_bits)
{
    PAGE_VALID(p);

    if(p -> pre)
    {
        p -> pre -> next = p -> next;
    }
    else
    {
        page_list[size_bits] = p -> next;
    }

    if(p -> next)
    {
        p -> next -> pre = p -> pre;
    }

    p -> size_bits = ADDRESS_WIDTH_BITS;
}

static void _pages_ref_inc(struct page *p, uint32_t size_bits)
{
    struct page *page_head;
    int idx;

    /* find page group head */
    idx = p - page_start;
    if (idx < 0 || idx >= page_nr)
    {
        return;
    }
    idx = idx & ~((1UL << size_bits) - 1);

    page_head = page_start + idx;
    page_head->ref_cnt++;
}

void rt_page_ref_inc(void *addr, uint32_t size_bits)
{
    struct page *p;
    rt_base_t level;

    p = addr_to_page(addr);
    level = rt_hw_interrupt_disable();
    _pages_ref_inc(p, size_bits);
    rt_hw_interrupt_enable(level);
}

//add new page to the first item of the linked list
static void page_insert(struct page *p,rt_size_t size_bits)
{
    PAGE_VALID(p);
    
    p -> next = page_list[size_bits];

    if(p -> next)
    {
        p -> next -> pre = p;
    }

    p -> pre = 0;
    page_list[size_bits] = p;
    p -> size_bits = size_bits;
}

static struct page *_pages_alloc(rt_size_t size_bits)
{
    struct page *p;

    if(page_list[size_bits])
    {
        //if appropriate page exists,just get new page from the linked list specified by size_bits
        p = page_list[size_bits];
        page_remove(p,size_bits);
    }
    else
    {
        //otherwise get new page from large linked list
        rt_size_t level;
        rt_size_t high = PAGE_LIST_SIZE;

        for(level = size_bits + 1;level <= high;level++)
        {
            if(page_list[level])
            {
                break;
            }
        }

        RT_ASSERT(level <= (high + 2));

        if(level == high + 2)
        {
            return 0;//couldn't find a appropriate page
        }

        p = page_list[level];
        page_remove(p,level);

        //push down this page,and split it to the size specified by size_bits
        while(level > size_bits)
        {
            page_insert(p,level - 1);
            p = buddy_get(p,level - 1);
            level--;
        }
    }

    dprintf("page_alloc:paddr = 0x%p,size_bits = 0x%p\n",page_to_addr(p),size_bits);
    return p;
}

static void _pages_free(struct page *p,rt_size_t size_bits)
{
    rt_size_t level = size_bits;
    rt_size_t high = ADDRESS_WIDTH_BITS - size_bits - 1;
    struct page *buddy;

    dprintf("page_free:paddr = 0x%p,size_bits = 0x%p\n",page_to_addr(p),size_bits);
    PAGE_VALID(p);

    while(level < high)
    {
        buddy = buddy_get(p,level);

        if(buddy && (buddy -> size_bits == level))
        {
            page_remove(buddy,level);
            p = (p < buddy) ? p : buddy;
            level++;
        }
        else
        {
            break;
        }
    }

    page_insert(p,level);
}

void *rt_pages_alloc(rt_size_t size_bits)
{
    struct page *p;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    p = _pages_alloc(size_bits);
    rt_hw_interrupt_enable(level);
    return page_to_addr(p);
}

void rt_pages_free(void *addr,rt_size_t size_bits)
{
    struct page *p;
    RT_PASSERT(__CHECKALIGN(addr,size_bits));
    p = addr_to_page(addr);

    if(p)
    {
        rt_base_t level;
        level = rt_hw_interrupt_disable();
        _pages_free(p,size_bits);
        rt_hw_interrupt_enable(level);
    }
}

void rt_pageinfo_dump()
{
    rt_size_t i;
    rt_size_t total = 0;

    rt_base_t level;
    level = rt_hw_interrupt_disable();

    for(i = 0;i < PAGE_LIST_SIZE;i++)
    {
        struct page *p = page_list[i];

        rt_kprintf("level %d ",i);

        while(p)
        {
            total += (1UL << i);
            rt_kprintf("[0x%08x]",page_to_addr(p));
            p = p -> next;
        }

        rt_kprintf("\n");
    }

    rt_hw_interrupt_enable(level);
    rt_kprintf("free pages is %08x\n",total);
    rt_kprintf("-------------------------------\n");
}
MSH_CMD_EXPORT(rt_pageinfo_dump, show page info);

void rt_page_get_info(size_t *total_nr, size_t *free_nr)
{
    rt_size_t i;
    rt_size_t total_free = 0;
    rt_base_t level;

    level = rt_hw_interrupt_disable();

    for (i = 0;i < PAGE_LIST_SIZE;i++)
    {
        struct page *p = page_list[i];

        while (p)
        {
            total_free += (1UL << i);
            p = p -> next;
        }
    }

    rt_hw_interrupt_enable(level);
    *total_nr = page_nr;
    *free_nr = total_free;
}

void rt_page_init(rt_region_t reg)
{
    rt_size_t align_bits;
    rt_size_t size_bits;
    rt_size_t i;

    dprintf("split 0x%08x 0x%08x\n",reg.start,reg.end);

    reg.start = __ALIGNUP(reg.start,PAGE_OFFSET_BIT);
    reg.end = __ALIGNDOWN(reg.end,PAGE_OFFSET_BIT);

    rt_size_t nr = PAGE_SIZE / sizeof(struct page);
    rt_size_t total = (reg.end - reg.start) >> PAGE_OFFSET_BIT;
    
    /*
        equation:cell((total - mnr) / nr) = mnr
        let total - mnr = knr + p(k is integer,0 <= p < nr)
        then,k + cell(p / nr) = mnr
        when p = 0,k = (total - mnr) / nr,mnr = total / (nr + 1)
        when p > 0,k = (total - mnr - p) / nr,cell(p / nr) = 1,mnr = (total - p + nr) / (nr + 1)
        to be simple,let all free memory remained can be indicated in page struct memory,so let use the upbound of mnr
        let p = 0,mnr = max(total / (nr + 1),(total - p + nr) / (nr + 1)) = (total + nr) / (nr + 1)
    */
    rt_size_t mnr = (total + nr) / (nr + 1);

    dprintf("nr = 0x%08x\n",nr);
    dprintf("total = 0x%08x\n",total);
    dprintf("mnr = 0x%08x\n",mnr);

    page_start = (struct page *)reg.start;
    reg.start += (mnr << PAGE_OFFSET_BIT);//now reg.start is the start point of free memory remained
    page_addr = (void *)reg.start;
    page_nr = (reg.end - reg.start) >> PAGE_OFFSET_BIT;

    dprintf("align 0x%08x 0x%08x\n",reg.start,reg.end);

    //init page struct
    for(i = 0;i < page_nr;i++)
    {
        page_start[i].size_bits = ADDRESS_WIDTH_BITS;
    }

    //init free list
    for(i = 0;i < PAGE_LIST_SIZE;i++)
    {
        page_list[i] = RT_NULL;
    }

    //init buddy list
    while(reg.start != reg.end)
    {
        size_bits = ADDRESS_WIDTH_BITS - 1 - __builtin_clzl(reg.end - reg.start);
        align_bits = __builtin_ctzl(reg.start);

        /*
            align_bits < size_bits:a small page exists
            align_bits = size_bits:this is a page
            align_bits > size_bits:the size of memory is less than the align size of current addr
        */
        if(align_bits < size_bits)
        {
            size_bits = align_bits;
        }
        
        _pages_free(addr_to_page((void *)reg.start),size_bits - PAGE_OFFSET_BIT);
        reg.start += (1U << size_bits);
    }
}