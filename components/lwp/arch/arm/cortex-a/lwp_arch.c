/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-28     Jesven       first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <stddef.h>

#ifdef ARCH_MM_MMU

#define DBG_TAG "lwp.arch"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <lwp_arch.h>
#include <lwp_user_mm.h>

#define KPTE_START (KERNEL_VADDR_START >> ARCH_SECTION_SHIFT)

int arch_user_space_init(struct rt_lwp *lwp)
{
    size_t *mmu_table;

    mmu_table = (size_t *)rt_pages_alloc(2);
    if (!mmu_table)
    {
        return -RT_ENOMEM;
    }

    lwp->end_heap = USER_HEAP_VADDR;

    rt_memcpy(mmu_table + KPTE_START, (size_t *)rt_kernel_space.page_table + KPTE_START, ARCH_PAGE_SIZE);
    rt_memset(mmu_table, 0, 3 * ARCH_PAGE_SIZE);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, mmu_table, 4 * ARCH_PAGE_SIZE);

    lwp->aspace = rt_aspace_create((void *)USER_VADDR_START, USER_VADDR_TOP - USER_VADDR_START, mmu_table);
    if (!lwp->aspace)
    {
        return -RT_ERROR;
    }

    return 0;
}

static struct rt_varea kuser_varea;

void arch_kuser_init(rt_aspace_t aspace, void *vectors)
{
    const size_t kuser_size = 0x1000;
    int err;
    extern char __kuser_helper_start[], __kuser_helper_end[];
    int kuser_sz = __kuser_helper_end - __kuser_helper_start;

    err = rt_aspace_map_static(aspace, &kuser_varea, &vectors, kuser_size,
                               MMU_MAP_U_RO, MMF_MAP_FIXED | MMF_PREFETCH,
                               &rt_mm_dummy_mapper, 0);
    if (err != 0)
        while (1)
            ; // early failed

    rt_memcpy((void *)((char *)vectors + 0x1000 - kuser_sz), __kuser_helper_start, kuser_sz);
    /*
     * vectors + 0xfe0 = __kuser_get_tls
     * vectors + 0xfe8 = hardware TLS instruction at 0xffff0fe8
     */
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)((char *)vectors + 0x1000 - kuser_sz), kuser_sz);
    rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, (void *)((char *)vectors + 0x1000 - kuser_sz), kuser_sz);
}

void arch_user_space_free(struct rt_lwp *lwp)
{
    if (lwp)
    {
        RT_ASSERT(lwp->aspace);
        void *pgtbl = lwp->aspace->page_table;
        rt_aspace_delete(lwp->aspace);

        /* must be freed after aspace delete, pgtbl is required for unmap */
        rt_pages_free(pgtbl, 2);
        lwp->aspace = RT_NULL;
    }
    else
    {
        LOG_W("%s: NULL lwp as parameter", __func__);
        RT_ASSERT(0);
    }
}

int arch_expand_user_stack(void *addr)
{
    int ret = 0;
    size_t stack_addr = (size_t)addr;

    stack_addr &= ~ARCH_PAGE_MASK;
    if ((stack_addr >= (size_t)USER_STACK_VSTART) && (stack_addr < (size_t)USER_STACK_VEND))
    {
        void *map = lwp_map_user(lwp_self(), (void *)stack_addr, ARCH_PAGE_SIZE, 0);

        if (map || lwp_user_accessable(addr, 1))
        {
            ret = 1;
        }
    }
    return ret;
}

#ifdef LWP_ENABLE_ASID
#define MAX_ASID_BITS 8
#define MAX_ASID (1 << MAX_ASID_BITS)
static uint64_t global_generation = 1;
static char asid_valid_bitmap[MAX_ASID];
unsigned int arch_get_asid(struct rt_lwp *lwp)
{
    if (lwp == RT_NULL)
    {
        // kernel
        return 0;
    }

    if (lwp->generation == global_generation)
    {
        return lwp->asid;
    }

    if (lwp->asid && !asid_valid_bitmap[lwp->asid])
    {
        asid_valid_bitmap[lwp->asid] = 1;
        return lwp->asid;
    }

    for (unsigned i = 1; i < MAX_ASID; i++)
    {
        if (asid_valid_bitmap[i] == 0)
        {
            asid_valid_bitmap[i] = 1;
            lwp->generation = global_generation;
            lwp->asid = i;
            return lwp->asid;
        }
    }

    global_generation++;
    memset(asid_valid_bitmap, 0, MAX_ASID * sizeof(char));

    asid_valid_bitmap[1] = 1;
    lwp->generation = global_generation;
    lwp->asid = 1;

    asm volatile ("mcr p15, 0, r0, c8, c7, 0\ndsb\nisb" ::: "memory");

    return lwp->asid;
}
#endif

#endif
