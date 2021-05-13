/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-28     Jesven       first version
 * 2021-02-03     lizhirui     port to riscv64
 */

#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_USERSPACE

#include <mmu.h>
#include <page.h>
#include <lwp_mm_area.h>
#include <lwp_user_mm.h>
#include <lwp_arch.h>

extern size_t MMUTable[];

int arch_user_space_init(struct rt_lwp *lwp)
{
    size_t *mmu_table;

    mmu_table = (size_t*)rt_pages_alloc(0);
    if (!mmu_table)
    {
        return -1;
    }

    lwp->end_heap = USER_HEAP_VADDR;
    memcpy(mmu_table, MMUTable, PAGE_SIZE);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, mmu_table, 4 * PAGE_SIZE);
    rt_hw_mmu_map_init(&lwp->mmu_info,(void *)0x100000000UL,0xFFFFFFFEFFFFFFFFUL,(rt_size_t *)mmu_table,0);

    return 0;
}

void *arch_kernel_mmu_table_get(void)
{
    return (void*)((char*)MMUTable);
}

void arch_user_space_vtable_free(struct rt_lwp *lwp)
{
    if (lwp && lwp->mmu_info.vtable)
    {
        rt_pages_free(lwp->mmu_info.vtable, 0);
    }
}
#endif
