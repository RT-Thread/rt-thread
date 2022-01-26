/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-26     lizhirui     the first version
 */

#include <string.h>
#include <stdlib.h>

#include "mips.h"
#include "mips_mmu.h"

void mmu_init()
{
    uint32_t status = read_c0_status();
    status |= 0x07 << 5;//ux = 1,sx = 1,kx = 1
    write_c0_status(status);

    mmu_clear_tlb();
    mmu_clear_itlb();
}

void mmu_set_cpu_mode(cpu_mode_t cpu_mode)
{
    uint32_t status = read_c0_status();
    status &= ~(0x03 << 3);
    status |= ((uint32_t)cpu_mode & 0x03) << 3;
    write_c0_status(status);
}

cpu_mode_t mmu_get_cpu_mode()
{
    uint32_t status = read_c0_status();
    return (cpu_mode_t)((status >> 3) & 0x03);
}

void mmu_clear_tlb()
{
    uint32_t max_tlb_index = mmu_get_max_tlb_index();
    uint64_t va = KSEG0BASE;
    uint32_t entry;
    tlb_item_t tlb_item;

    for(entry = 0;entry <= max_tlb_index;entry++)
    {
        mmu_tlb_item_init(&tlb_item);
        mmu_tlb_write_indexed(entry,&tlb_item);
    }
}

void mmu_clear_itlb()
{
    uint32_t diag = read_c0_diag();
    write_c0_diag(diag | (0x01 << 2));//write ITLB bit
    read_c0_entrylo0();
}

uint32_t mmu_get_max_tlb_index()
{
    uint32_t config1 = read_c0_config1();
    return ((config1 >> 25) & 0x3F);
}

void mmu_tlb_write_indexed(uint32_t index,tlb_item_t *tlb_item)
{
    tlb_item -> entry_lo[0].g |= tlb_item -> entry_lo[1].g;
    tlb_item -> entry_lo[1].g |= tlb_item -> entry_lo[0].g;
    mmu_tlb_set_index(index);
    write_c0_entrylo0(reg_type_convert(tlb_item -> entry_lo[0],uint64_t));
    write_c0_entrylo1(reg_type_convert(tlb_item -> entry_lo[1],uint64_t));
    write_c0_entryhi(reg_type_convert(tlb_item -> entry_hi,uint64_t));
    write_c0_pagemask(reg_type_convert(tlb_item -> page_mask,uint64_t));
    tlb_write_indexed();
    read_c0_entrylo0();
}

void mmu_tlb_write_random(tlb_item_t *tlb_item)
{
    tlb_item -> entry_lo[0].g |= tlb_item -> entry_lo[1].g;
    tlb_item -> entry_lo[1].g |= tlb_item -> entry_lo[0].g;
    write_c0_entrylo0(reg_type_convert(tlb_item -> entry_lo[0],uint64_t));
    write_c0_entrylo1(reg_type_convert(tlb_item -> entry_lo[1],uint64_t));
    write_c0_entryhi(reg_type_convert(tlb_item -> entry_hi,uint64_t));
    write_c0_pagemask(reg_type_convert(tlb_item -> page_mask,uint64_t));
    tlb_write_random();
    read_c0_entrylo0();
}

void mmu_tlb_read(uint32_t index,tlb_item_t *tlb_item)
{
    mmu_tlb_set_index(index);
    tlb_read();
    uint64_t entrylo[2];
    uint64_t entryhi;
    uint64_t page_mask;
    entrylo[0] = read_c0_entrylo0();
    entrylo[1] = read_c0_entrylo1();
    entryhi = read_c0_entryhi();
    page_mask = read_c0_pagemask();
    tlb_item -> entry_lo[0] = reg_type_convert(entrylo[0],entry_lo_t);
    tlb_item -> entry_lo[1] = reg_type_convert(entrylo[1],entry_lo_t);
    tlb_item -> entry_hi = reg_type_convert(entryhi,entry_hi_t);
    tlb_item -> page_mask = reg_type_convert(page_mask,page_mask_t);
}

uint32_t mmu_tlb_find(uint64_t vpn,uint32_t asid,uint32_t *index)
{
    entry_hi_t entry_hi;
    entry_hi.r = (vpn >> 62) & 0x03;
    entry_hi.vpn2 = (vpn >> 13) & 0x7FFFFFFU;
    entry_hi.asid = asid & 0xFFU;
    tlb_item_t tlb_item;
    //mmu_tlb_read(6,&tlb_item);
    //tlb_dump();
    mmu_tlb_item_init(&tlb_item);
    tlb_item.entry_lo[0].g = tlb_item.entry_lo[1].g = 1;
    read_c0_entrylo0();//i don't know why,but if i don't read any register of mmu,tplb will be failed in qemu.
    write_c0_entrylo0(reg_type_convert(tlb_item.entry_lo[0],uint64_t));
    write_c0_entrylo1(reg_type_convert(tlb_item.entry_lo[1],uint64_t));
    write_c0_entryhi(reg_type_convert(entry_hi,uint64_t));
    //__asm__ __volatile__("ehb");
    //read_c0_entryhi();
    //rt_kprintf("entry_hi = %p\n",read_c0_entryhi());
    tlb_probe();
    *index = mmu_tlb_get_index();
    return mmu_tlb_is_matched();
}

void mmu_tlb_item_init(tlb_item_t *tlb_item)
{
    memset(tlb_item,0,sizeof(tlb_item_t));
    tlb_item -> entry_lo[0].c = 0x03;
    tlb_item -> entry_lo[1].c = 0x03;
}

void mmu_set_map(uint64_t vpn,uint64_t ppn,page_mask_enum_t page_mask,uint32_t asid,uint32_t global)
{
    uint64_t page_mask_v = (uint64_t)page_mask;

    /*if(page_mask_v & (1 << 13))
    {
        page_mask_v |= (1 << 12);
    }*/

    uint64_t lb = lowbit((~(page_mask_v)) << 12);
    uint64_t pn_remained = ((~(page_mask_v)) << 12) | lb;
    vpn &= pn_remained;
    ppn &= pn_remained;
    uint64_t odd_vpn = vpn | lb;
    uint64_t even_vpn = vpn & (~lb);
    uint32_t index;
    tlb_item_t tlb_item,tlb2_item;

    mmu_tlb_item_init(&tlb_item);
    mmu_tlb_item_init(&tlb2_item);
    tlb_item.page_mask.mask = page_mask;

    if(mmu_tlb_find(vpn & (~lb),asid,&index))
    {
        mmu_tlb_read(index,&tlb_item);
        mmu_tlb_write_indexed(index,&tlb2_item);
    }

    entry_lo_t *entry_lo = &tlb_item.entry_lo[vpn == even_vpn ? 0 : 1];
    tlb_item.entry_lo[0].g = tlb_item.entry_lo[1].g = global;
    entry_lo -> d = 1;
    entry_lo -> ri = 0;
    entry_lo -> xi = 0;
    entry_lo -> v = 1;
    entry_lo -> pfn = ppn >> 12;
    tlb_item.entry_hi.r = (vpn >> 62) & 0x03;
    tlb_item.entry_hi.vpn2 = (vpn >> 13) & 0x7FFFFFFU;
    tlb_item.entry_hi.asid = asid & 0xFFU;
    mmu_tlb_write_random(&tlb_item);
}

uint32_t mmu_tlb_get_random()
{
    return read_c0_random();
}

uint32_t mmu_tlb_get_index()
{
    return read_c0_index() & 0x3F;
}

void mmu_tlb_set_index(uint32_t index)
{
    write_c0_index(index & 0x3F);
}

uint32_t mmu_tlb_is_matched()
{
    return (read_c0_index() & 0x80000000) == 0;
}

uint64_t mmu_tlb_get_bad_vaddr()
{
    return read_c0_badvaddr();
}

void tlb_dump()
{
    uint32_t max_index = mmu_get_max_tlb_index();
    //uint32_t max_index = 10;
    uint32_t entry;
    tlb_item_t tlb_item;

    for(entry = 0;entry <= max_index;entry++)
    {
        mmu_tlb_read(entry,&tlb_item);
        //mmu_tlb_write_indexed(entry,&tlb_item);
        //mmu_tlb_read(entry,&tlb_item);
        rt_kprintf("vpn = 0x%p,ppn0 = 0x%p,ppn1 = 0x%p\n",(uint64_t)tlb_item.entry_hi.vpn2 << 13 | (uint64_t)tlb_item.entry_hi.asid << 62,(uint64_t)tlb_item.entry_lo[0].pfn << 12,(uint64_t)tlb_item.entry_lo[1].pfn << 12);
        rt_kprintf("v = %d,d = %d,g = %d,ri = %d,xi = %d,c = %d\n",tlb_item.entry_lo[0].v,tlb_item.entry_lo[0].d,tlb_item.entry_lo[0].g,tlb_item.entry_lo[0].ri,tlb_item.entry_lo[0].xi,tlb_item.entry_lo[0].c);
        rt_kprintf("v = %d,d = %d,g = %d,ri = %d,xi = %d,c = %d\n",tlb_item.entry_lo[1].v,tlb_item.entry_lo[1].d,tlb_item.entry_lo[1].g,tlb_item.entry_lo[1].ri,tlb_item.entry_lo[1].xi,tlb_item.entry_lo[1].c);
    }
}
