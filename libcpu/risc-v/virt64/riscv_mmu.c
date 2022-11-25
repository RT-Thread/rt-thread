/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <stdint.h>
#include <riscv.h>
#include <string.h>
#include <stdlib.h>

#include "riscv_mmu.h"

void mmu_set_pagetable(rt_ubase_t addr)
{
    RT_ASSERT(__CHECKALIGN(addr, PAGE_OFFSET_BIT));
    RT_ASSERT(__CHECKUPBOUND(addr, PHYSICAL_ADDRESS_WIDTH_BITS));

    mmu_flush_tlb();
    write_csr(satp, (((size_t)SATP_MODE) << SATP_MODE_OFFSET) | (addr >> PAGE_OFFSET_BIT));
    mmu_flush_tlb();
}

void mmu_enable_user_page_access()
{
    set_csr(sstatus, SSTATUS_SUM);
}

void mmu_disable_user_page_access()
{
    clear_csr(sstatus, SSTATUS_SUM);
}
