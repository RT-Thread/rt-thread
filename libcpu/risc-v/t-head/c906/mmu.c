/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <board.h>
#include "page.h"
#include <stdlib.h>
#include <string.h>
#include <cache.h>

#include "riscv.h"
#include "riscv_mmu.h"
#include "mmu.h"

void *current_mmu_table = RT_NULL;

static void rt_hw_cpu_tlb_invalidate()
{
    rt_size_t satpv = read_csr(satp);
    write_csr(satp,satpv);
    mmu_flush_tlb();
}

void *rt_hw_mmu_tbl_get()
{
    return current_mmu_table;
}

void rt_hw_mmu_switch(void *mmu_table)
{
    current_mmu_table = mmu_table;
    RT_ASSERT(__CHECKALIGN(mmu_table,PAGE_OFFSET_BIT));
    mmu_set_pagetable((rt_ubase_t)mmu_table);
    rt_hw_cpu_dcache_clean_all();
    rt_hw_cpu_icache_invalidate_all();
}

int rt_hw_mmu_map_init(rt_mmu_info *mmu_info,void *v_address,rt_size_t size,rt_size_t *vtable,rt_size_t pv_off)
{
    size_t l1_off,va_s,va_e;
    rt_base_t level;

    if((!mmu_info) || (!vtable))
    {
        return -1;
    }

    va_s = (rt_size_t)v_address;
    va_e = ((rt_size_t)v_address) + size - 1;

    if(va_e < va_s)
    {
        return -1;
    }

    //convert address to level 1 page frame id
    va_s = GET_L1(va_s);
    va_e = GET_L1(va_e);

    if(va_s == 0)
    {
        return -1;
    }

    level = rt_hw_interrupt_disable();

    //vtable initialization check
    for(l1_off = va_s;l1_off <= va_e;l1_off++)
    {
        size_t v = vtable[l1_off];

        if(v)
        {
            rt_hw_interrupt_enable(level);
            return 0;
        }
    }

    mmu_info -> vtable = vtable;
    mmu_info -> vstart = va_s;
    mmu_info -> vend = va_e;
    mmu_info -> pv_off = pv_off;

    rt_hw_interrupt_enable(level);
    return 0;
}

void rt_hw_mmu_kernel_map_init(rt_mmu_info *mmu_info,rt_size_t vaddr_start,rt_size_t size)
{
    rt_size_t paddr_start = __UMASKVALUE(VPN_TO_PPN(vaddr_start,mmu_info -> pv_off),PAGE_OFFSET_MASK);
    rt_size_t va_s = GET_L1(vaddr_start);
    rt_size_t va_e = GET_L1(vaddr_start + size - 1);
    rt_size_t i;

    for(i = va_s;i <= va_e;i++)
    {
        mmu_info -> vtable[i] = COMBINEPTE(paddr_start,PAGE_ATTR_RWX | PTE_G | PTE_V | PTE_CACHE | PTE_SHARE | PTE_BUF | PTE_A | PTE_D);
        paddr_start += L1_PAGE_SIZE;
    }

    rt_hw_cpu_tlb_invalidate();
}

//find a range of free virtual address specified by pages
static rt_size_t find_vaddr(rt_mmu_info *mmu_info,rt_size_t pages)
{
    rt_size_t l1_off,l2_off,l3_off;
    rt_size_t *mmu_l1,*mmu_l2,*mmu_l3;
    rt_size_t find_l1 = 0,find_l2 = 0,find_l3 = 0;
    rt_size_t n = 0;

    if(!pages)
    {
        return 0;
    }

    if(!mmu_info)
    {
        return 0;
    }

    for(l1_off = mmu_info -> vstart;l1_off <= mmu_info -> vend;l1_off++)
    {
        mmu_l1 = ((rt_size_t *)mmu_info -> vtable) + l1_off;

        if(PTE_USED(*mmu_l1))
        {
            RT_ASSERT(!PAGE_IS_LEAF(*mmu_l1));
            mmu_l2 = (rt_size_t *)PPN_TO_VPN(GET_PADDR(*mmu_l1),mmu_info -> pv_off);

            for(l2_off = 0;l2_off < __SIZE(VPN1_BIT);l2_off++)
            {
                if(PTE_USED(*(mmu_l2 + l2_off)))
                {
                    RT_ASSERT(!PAGE_IS_LEAF(*(mmu_l2 + l2_off)));
                    mmu_l3 = (rt_size_t *)PPN_TO_VPN(GET_PADDR(*(mmu_l2 + l2_off)),mmu_info -> pv_off);

                    for(l3_off = 0;l3_off < __SIZE(VPN0_BIT);l3_off++)
                    {
                        if(PTE_USED(*(mmu_l3 + l3_off)))
                        {
                            RT_ASSERT(PAGE_IS_LEAF(*(mmu_l3 + l3_off)));
                            n = 0;//in use
                        }
                        else
                        {
                            if(!n)
                            {
                                find_l1 = l1_off;
                                find_l2 = l2_off;
                                find_l3 = l3_off;
                            }

                            n++;

                            if(n >= pages)
                            {
                                return COMBINEVADDR(find_l1,find_l2,find_l3);
                            }
                        }
                    }
                }
                else
                {
                    if(!n)
                    {
                        find_l1 = l1_off;
                        find_l2 = l2_off;
                        find_l3 = 0;
                    }

                    n += __SIZE(VPN0_BIT);

                    if(n >= pages)
                    {
                        return COMBINEVADDR(find_l1,find_l2,find_l3);
                    }
                }
            }
        }
        else
        {
            if(!n)
            {
                find_l1 = l1_off;
                find_l2 = 0;
                find_l3 = 0;
            }

            n += __SIZE(VPN1_BIT);

            if(n >= pages)
            {
                return COMBINEVADDR(find_l1,find_l2,find_l3);
            }
        }
    }

    return 0;
}

//check whether the range of virtual address are free
static int check_vaddr(rt_mmu_info *mmu_info,void *va,rt_size_t pages)
{
    rt_size_t loop_va = __UMASKVALUE((rt_size_t)va,PAGE_OFFSET_MASK);
    rt_size_t l1_off,l2_off,l3_off;
    rt_size_t *mmu_l1,*mmu_l2,*mmu_l3;

    if(!pages)
    {
        return -1;
    }

    if(!mmu_info)
    {
        return -1;
    }

    while(pages--)
    {
        l1_off = GET_L1(loop_va);
        l2_off = GET_L2(loop_va);
        l3_off = GET_L3(loop_va);
        mmu_l1 = ((rt_size_t *)mmu_info -> vtable) + l1_off;

        if(PTE_USED(*mmu_l1))
        {
            RT_ASSERT(!PAGE_IS_LEAF(*mmu_l1));
            mmu_l2 = (rt_size_t *)PPN_TO_VPN(GET_PADDR(*mmu_l1),mmu_info -> pv_off) + l2_off;

            if(PTE_USED(*mmu_l2))
            {
                RT_ASSERT(!PAGE_IS_LEAF(*mmu_l2));
                mmu_l3 = (rt_size_t *)PPN_TO_VPN(GET_PADDR(*mmu_l2),mmu_info -> pv_off) + l3_off;

                if(PTE_USED(*mmu_l3))
                {
                    RT_ASSERT(PAGE_IS_LEAF(*mmu_l3));
                    return -1;
                }
            }
        }

        loop_va += PAGE_SIZE;
    }

    return 0;
}

static void __rt_hw_mmu_unmap(rt_mmu_info *mmu_info,void *v_addr,rt_size_t npages)
{
    rt_size_t loop_va = __UMASKVALUE((rt_size_t)v_addr,PAGE_OFFSET_MASK);
    rt_size_t l1_off,l2_off,l3_off;
    rt_size_t *mmu_l1,*mmu_l2,*mmu_l3;
    rt_size_t *ref_cnt;

    RT_ASSERT(mmu_info);

    while(npages--)
    {
        l1_off = (rt_size_t)GET_L1(loop_va);
        RT_ASSERT((l1_off >= mmu_info -> vstart) && (l1_off <= mmu_info -> vend));
        l2_off = (rt_size_t)GET_L2(loop_va);
        l3_off = (rt_size_t)GET_L3(loop_va);
        mmu_l1 = ((rt_size_t *)mmu_info -> vtable) + l1_off;
        RT_ASSERT(PTE_USED(*mmu_l1))
        RT_ASSERT(!PAGE_IS_LEAF(*mmu_l1));
        mmu_l2 = ((rt_size_t *)PPN_TO_VPN(GET_PADDR(*mmu_l1),mmu_info -> pv_off)) + l2_off;
        RT_ASSERT(PTE_USED(*mmu_l2));
        RT_ASSERT(!PAGE_IS_LEAF(*mmu_l2));
        mmu_l3 = ((rt_size_t *)PPN_TO_VPN(GET_PADDR(*mmu_l2),mmu_info -> pv_off)) + l3_off;
        RT_ASSERT(PTE_USED(*mmu_l3));
        RT_ASSERT(PAGE_IS_LEAF(*(mmu_l3)));
        *mmu_l3 = 0;
        rt_hw_cpu_dcache_clean(mmu_l3,sizeof(*mmu_l3));
        mmu_l3 -= l3_off;
        ref_cnt = mmu_l3 + __SIZE(VPN0_BIT);
        (*ref_cnt)--;

        if(!*ref_cnt)
        {
            //release level 3 page
            rt_pages_free(mmu_l3,1);//entry page and ref_cnt page
            *mmu_l2 = 0;
            rt_hw_cpu_dcache_clean(mmu_l2,sizeof(*mmu_l2));
            mmu_l2 -= l2_off;

            ref_cnt = mmu_l2 + __SIZE(VPN1_BIT);
            (*ref_cnt)--;

            if(!*ref_cnt)
            {
                //release level 2 page
                rt_pages_free(mmu_l2,1);//entry page and ref_cnt page
                *mmu_l1 = 0;
                rt_hw_cpu_dcache_clean(mmu_l1,sizeof(*mmu_l1));
            }
        }

        loop_va += PAGE_SIZE;
    }
}

static int __rt_hw_mmu_map(rt_mmu_info *mmu_info,void *v_addr,void *p_addr,rt_size_t npages,rt_size_t attr)
{
    rt_size_t loop_va = __UMASKVALUE((rt_size_t)v_addr,PAGE_OFFSET_MASK);
    rt_size_t loop_pa = __UMASKVALUE((rt_size_t)p_addr,PAGE_OFFSET_MASK);
    rt_size_t l1_off,l2_off,l3_off;
    rt_size_t *mmu_l1,*mmu_l2,*mmu_l3;
    rt_size_t *ref_cnt;
    //rt_kprintf("v_addr = 0x%p,p_addr = 0x%p,npages = %lu\n",v_addr,p_addr,npages);

    if(!mmu_info)
    {
        return -1;
    }

    while(npages--)
    {
        l1_off = GET_L1(loop_va);
        l2_off = GET_L2(loop_va);
        l3_off = GET_L3(loop_va);
        mmu_l1 = ((rt_size_t *)mmu_info -> vtable) + l1_off;

        if(PTE_USED(*mmu_l1))
        {
            RT_ASSERT(!PAGE_IS_LEAF(*mmu_l1));
            mmu_l2 = (rt_size_t *)PPN_TO_VPN(GET_PADDR(*mmu_l1),mmu_info -> pv_off);
        }
        else
        {
            mmu_l2 = (rt_size_t *)rt_pages_alloc(1);

            if(mmu_l2)
            {
                rt_memset(mmu_l2,0,PAGE_SIZE * 2);
                rt_hw_cpu_dcache_clean(mmu_l2,PAGE_SIZE * 2);
                *mmu_l1 = COMBINEPTE((rt_size_t)VPN_TO_PPN(mmu_l2,mmu_info -> pv_off),PAGE_DEFAULT_ATTR_NEXT);
                rt_hw_cpu_dcache_clean(mmu_l1,sizeof(*mmu_l1));
            }
            else
            {
                __rt_hw_mmu_unmap(mmu_info,v_addr,npages);
                return -1;
            }
        }

        if(PTE_USED(*(mmu_l2 + l2_off)))
        {
            RT_ASSERT(!PAGE_IS_LEAF(*(mmu_l2 + l2_off)));
            mmu_l3 = (rt_size_t *)PPN_TO_VPN(GET_PADDR(*(mmu_l2 + l2_off)),mmu_info -> pv_off);
        }
        else
        {
            mmu_l3 = (rt_size_t *)rt_pages_alloc(1);

            if(mmu_l3)
            {
                rt_memset(mmu_l3,0,PAGE_SIZE * 2);
                rt_hw_cpu_dcache_clean(mmu_l3,PAGE_SIZE * 2);
                *(mmu_l2 + l2_off) = COMBINEPTE((rt_size_t)VPN_TO_PPN(mmu_l3,mmu_info -> pv_off),PAGE_DEFAULT_ATTR_NEXT);
                rt_hw_cpu_dcache_clean(mmu_l2,sizeof(*mmu_l2));
                ref_cnt = mmu_l2 + __SIZE(VPN1_BIT);
                (*ref_cnt)++;
            }
            else
            {
                __rt_hw_mmu_unmap(mmu_info,v_addr,npages);
                return -1;
            }
        }

        RT_ASSERT(!PTE_USED(*(mmu_l3 + l3_off)));
        ref_cnt = mmu_l3 + __SIZE(VPN0_BIT);
        (*ref_cnt)++;
        *(mmu_l3 + l3_off) = COMBINEPTE((rt_size_t)loop_pa,PAGE_DEFAULT_ATTR_LEAF);
        rt_hw_cpu_dcache_clean(mmu_l3 + l3_off,sizeof(*(mmu_l3 + l3_off)));

        loop_va += PAGE_SIZE;
        loop_pa += PAGE_SIZE;
    }

    return 0;
}

void *_rt_hw_mmu_map(rt_mmu_info *mmu_info,void *v_addr,void *p_addr,rt_size_t size,rt_size_t attr)
{
    rt_size_t pa_s,pa_e;
    rt_size_t vaddr;
    rt_size_t pages;
    int ret;

    if(!size)
    {
        return 0;
    }

    pa_s = (rt_size_t)p_addr;
    pa_e = ((rt_size_t)p_addr) + size - 1;
    pa_s = GET_PF_ID(pa_s);
    pa_e = GET_PF_ID(pa_e);
    pages = pa_e - pa_s + 1;

    if(v_addr)
    {
        vaddr = (rt_size_t)v_addr;
        pa_s = (rt_size_t)p_addr;

        if(GET_PF_OFFSET(vaddr) != GET_PF_OFFSET(pa_s))
        {
            return 0;
        }

        vaddr = __UMASKVALUE(vaddr,PAGE_OFFSET_MASK);

        if(check_vaddr(mmu_info,(void *)vaddr,pages) != 0)
        {
            return 0;
        }
    }
    else
    {
        vaddr = find_vaddr(mmu_info,pages);
    }

    if(vaddr)
    {
        ret = __rt_hw_mmu_map(mmu_info,(void *)vaddr,p_addr,pages,attr);

        if(ret == 0)
        {
            rt_hw_cpu_tlb_invalidate();
            return (void *)(vaddr | GET_PF_OFFSET((rt_size_t)p_addr));
        }
    }

    return 0;
}

static int __rt_hw_mmu_map_auto(rt_mmu_info *mmu_info,void *v_addr,rt_size_t npages,rt_size_t attr)
{
    rt_size_t loop_va = __UMASKVALUE((rt_size_t)v_addr,PAGE_OFFSET_MASK);
    rt_size_t loop_pa;
    rt_size_t l1_off,l2_off,l3_off;
    rt_size_t *mmu_l1,*mmu_l2,*mmu_l3;
    rt_size_t *ref_cnt;
    rt_size_t i;
    void *va,*pa;

    if(!mmu_info)
    {
        return -1;
    }

    while(npages--)
    {
        loop_pa = (rt_size_t)rt_pages_alloc(0);

        if(!loop_pa)
        {
            goto err;
        }

        if(__rt_hw_mmu_map(mmu_info,(void *)loop_va,(void *)loop_pa,1,attr) < 0)
        {
            goto err;
        }

        loop_va += PAGE_SIZE;
    }

    return 0;

    err:
        va = (void *)__UMASKVALUE((rt_size_t)v_addr,PAGE_OFFSET_MASK);

        for(i = 0;i < npages;i++)
        {
            pa = rt_hw_mmu_v2p(mmu_info,va);

            if(pa)
            {
                rt_pages_free((void *)PPN_TO_VPN(pa,mmu_info -> pv_off),0);
            }

            va = (void *)((rt_uint8_t *)va + PAGE_SIZE);
        }

        __rt_hw_mmu_unmap(mmu_info,v_addr,npages);
        return -1;
}

void *_rt_hw_mmu_map_auto(rt_mmu_info *mmu_info,void *v_addr,rt_size_t size,rt_size_t attr)
{
    rt_size_t vaddr;
    rt_size_t offset;
    rt_size_t pages;
    int ret;

    if(!size)
    {
        return 0;
    }

    offset = GET_PF_OFFSET((rt_size_t)v_addr);
    size += (offset + PAGE_SIZE - 1);
    pages = size >> PAGE_OFFSET_BIT;

    if(v_addr)
    {
        vaddr = __UMASKVALUE((rt_size_t)v_addr,PAGE_OFFSET_MASK);

        if(check_vaddr(mmu_info,(void *)vaddr,pages) != 0)
        {
            return 0;
        }
    }
    else
    {
        vaddr = find_vaddr(mmu_info,pages);
    }

    if(vaddr)
    {
        ret = __rt_hw_mmu_map_auto(mmu_info,(void *)vaddr,pages,attr);

        if(ret == 0)
        {
            rt_hw_cpu_tlb_invalidate();
            return (void *)(vaddr | offset);
        }
    }

    return 0;
}

void _rt_hw_mmu_unmap(rt_mmu_info *mmu_info,void *v_addr,rt_size_t size)
{
    rt_size_t va_s,va_e;
    rt_size_t pages;

    va_s = ((rt_size_t)v_addr) >> PAGE_OFFSET_BIT;
    va_e = (((rt_size_t)v_addr) + size - 1) >> PAGE_OFFSET_BIT;
    pages = va_e - va_s + 1;
    __rt_hw_mmu_unmap(mmu_info,v_addr,pages);
    rt_hw_cpu_tlb_invalidate();
}

void *rt_hw_mmu_map(rt_mmu_info *mmu_info,void *v_addr,void *p_addr,rt_size_t size,rt_size_t attr)
{
    void *ret;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    ret = _rt_hw_mmu_map(mmu_info,v_addr,p_addr,size,attr);
    rt_hw_interrupt_enable(level);
    return ret;
}

void *rt_hw_mmu_map_auto(rt_mmu_info *mmu_info,void *v_addr,rt_size_t size,rt_size_t attr)
{
    void *ret;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    ret = _rt_hw_mmu_map_auto(mmu_info,v_addr,size,attr);
    rt_hw_interrupt_enable(level);
    return ret;
}

void rt_hw_mmu_unmap(rt_mmu_info *mmu_info,void *v_addr,rt_size_t size)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    _rt_hw_mmu_unmap(mmu_info,v_addr,size);
    rt_hw_interrupt_enable(level);
}

void *_rt_hw_mmu_v2p(rt_mmu_info *mmu_info,void *v_addr)
{
    rt_size_t l1_off,l2_off,l3_off;
    rt_size_t *mmu_l1,*mmu_l2,*mmu_l3;
    rt_size_t pa;

    l1_off = GET_L1((rt_size_t)v_addr);
    l2_off = GET_L2((rt_size_t)v_addr);
    l3_off = GET_L3((rt_size_t)v_addr);

    if(!mmu_info)
    {
        return RT_NULL;
    }

    mmu_l1 = ((rt_size_t *)mmu_info -> vtable) + l1_off;

    if(PTE_USED(*mmu_l1))
    {
        RT_ASSERT(!PAGE_IS_LEAF(*mmu_l1));
        mmu_l2 = (rt_size_t *)PPN_TO_VPN(GET_PADDR(*mmu_l1),mmu_info -> pv_off);

        if(PTE_USED(*(mmu_l2 + l2_off)))
        {
            RT_ASSERT(!PAGE_IS_LEAF(*(mmu_l2 + l2_off)));
            mmu_l3 = (rt_size_t *)PPN_TO_VPN(GET_PADDR(*(mmu_l2 + l2_off)),mmu_info -> pv_off);

            if(PTE_USED(*(mmu_l3 + l3_off)))
            {
                RT_ASSERT(PAGE_IS_LEAF(*(mmu_l3 + l3_off)));
                return (void *)(GET_PADDR(*(mmu_l3 + l3_off)) | GET_PF_OFFSET((rt_size_t)v_addr));
            }
        }
    }

    return RT_NULL;
}

void *rt_hw_mmu_v2p(rt_mmu_info *mmu_info,void *v_addr)
{
    void *ret;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    ret = _rt_hw_mmu_v2p(mmu_info,v_addr);
    rt_hw_interrupt_enable(level);
    return ret;
}
