/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-17     Shell        test case for aspace_unmap_range
 */
#include "common.h"
#include "lwp_user_mm.h"
#include <mm_aspace.h>

#include <rtthread.h>

static void *vaddr = (void *)0x100000000;
static size_t existed_size = 0x5000;
static char *unmap_start;
static char *unmap_end;
static size_t former_vsz;
static size_t unmap_size = 0x2000;
static struct rt_lwp *lwp;

static void test_unmap_range_shrink(void)
{
    /* create an existed mapping */
    former_vsz = rt_aspace_count_vsz(lwp->aspace);
    uassert_true(!rt_aspace_map(lwp->aspace, &vaddr, existed_size, MMU_MAP_K_RWCB, MMF_PREFETCH, &rt_mm_dummy_mapper, 0));
    utest_int_equal(former_vsz + existed_size, rt_aspace_count_vsz(lwp->aspace));
    former_vsz += existed_size;

    /* test the shrink mode of unmap from LEFT side */
    unmap_start = (char *)vaddr - unmap_size/2;
    uassert_true(!rt_aspace_unmap_range(lwp->aspace, unmap_start, unmap_size));
    unmap_end = unmap_start + unmap_size;
    uassert_true(rt_hw_mmu_v2p(lwp->aspace, unmap_end) != ARCH_MAP_FAILED);
    utest_int_equal(former_vsz - (unmap_end - (char *)vaddr), rt_aspace_count_vsz(lwp->aspace));
    former_vsz -= unmap_end - (char *)vaddr;

    /* test the shrink mode of unmap from RIGHT side */
    unmap_start = (char *)vaddr + existed_size - unmap_size / 2;
    uassert_true(!rt_aspace_unmap_range(lwp->aspace, unmap_start, unmap_size));
    uassert_true(rt_hw_mmu_v2p(lwp->aspace, unmap_start - 1) != ARCH_MAP_FAILED);
    utest_int_equal(former_vsz - (unmap_end - (char *)vaddr), rt_aspace_count_vsz(lwp->aspace));
    former_vsz -= unmap_end - (char *)vaddr;

    utest_int_equal(RT_EOK, rt_aspace_unmap_range(lwp->aspace, vaddr, existed_size));
}

static void aspace_unmap_tc(void)
{
    CONSIST_HEAP(test_unmap_range_shrink());
}

static rt_err_t utest_tc_init(void)
{
    lwp = lwp_create(0);
    if (lwp)
        lwp_user_space_init(lwp, 1);
    else
        return -RT_ENOMEM;
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    lwp_ref_dec(lwp);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(aspace_unmap_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.mm.aspace_unmap_range.shrink", utest_tc_init, utest_tc_cleanup, 10);
