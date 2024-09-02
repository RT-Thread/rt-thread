/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-12     RT-Thread    first version.
 */
#define DBG_TAG "hw.asid"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <rtthread.h>
#include <board.h>
#include <cache.h>
#include <mm_aspace.h>
#include <mm_page.h>
#include <mmu.h>
#include <riscv_mmu.h>
#include <tlb.h>

static rt_uint8_t ASID_BITS = 0;
static rt_uint32_t next_asid;
static rt_uint64_t global_asid_generation;
#define ASID_MASK ((1 << ASID_BITS) - 1)
#define ASID_FIRST_GENERATION (1 << ASID_BITS)
#define MAX_ASID ASID_FIRST_GENERATION

void rt_hw_asid_init(void)
{
    unsigned int satp_reg = read_csr(satp);
    satp_reg |= (((rt_uint64_t)0xffff) << PPN_BITS);
    write_csr(satp, satp_reg);
    unsigned short valid_asid_bit = ((read_csr(satp) >> PPN_BITS) & 0xffff);

    // The maximal value of ASIDLEN, is 9 for Sv32 or 16 for Sv39, Sv48, and Sv57
    for (unsigned i = 0; i < 16; i++)
    {
        if (!(valid_asid_bit & 0x1))
        {
            break;
        }

        valid_asid_bit >>= 1;
        ASID_BITS++;
    }

    global_asid_generation = ASID_FIRST_GENERATION;
    next_asid = 1;
}

static rt_uint64_t _asid_acquire(rt_aspace_t aspace)
{
    if ((aspace->asid ^ global_asid_generation) >> ASID_BITS) // not same generation
    {
        if (next_asid != MAX_ASID)
        {
            aspace->asid = global_asid_generation | next_asid;
            next_asid++;
        }
        else
        {
            // scroll to next generation
            global_asid_generation += ASID_FIRST_GENERATION;
            next_asid = 1;
            rt_hw_tlb_invalidate_all_local();

            aspace->asid = global_asid_generation | next_asid;
            next_asid++;
        }
    }

    return aspace->asid & ASID_MASK;
}

void rt_hw_asid_switch_pgtbl(struct rt_aspace *aspace, rt_ubase_t pgtbl)
{
    rt_uint64_t asid = _asid_acquire(aspace);
    write_csr(satp, (((size_t)SATP_MODE) << SATP_MODE_OFFSET) |
                        (asid << PPN_BITS) |
                        ((rt_ubase_t)pgtbl >> PAGE_OFFSET_BIT));
    asm volatile("sfence.vma x0,%0"::"r"(asid):"memory");
}

