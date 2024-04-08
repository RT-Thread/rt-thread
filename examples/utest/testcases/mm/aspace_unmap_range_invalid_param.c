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
static size_t unmap_size = 0x2000;
static size_t former_vsz;
static struct rt_lwp *lwp;
static size_t flags = MMF_PREFETCH | MMF_MAP_FIXED;

static void test_unmap_range_invalid_param(void)
{
    rt_mem_obj_t notsupp_object;

    /* create an existed mapping */
    former_vsz = rt_aspace_count_vsz(lwp->aspace);
    uassert_true(!rt_aspace_map(lwp->aspace, &vaddr, existed_size, MMU_MAP_K_RWCB, flags, &rt_mm_dummy_mapper, 0));
    utest_int_equal(former_vsz + existed_size, rt_aspace_count_vsz(lwp->aspace));
    former_vsz += existed_size;

    /* test unaligned vaddr start */
    unmap_start = (char *)vaddr - 0x1234;
    utest_int_equal(-RT_EINVAL, rt_aspace_unmap_range(lwp->aspace, unmap_start, unmap_size));
    utest_int_equal(former_vsz, rt_aspace_count_vsz(lwp->aspace));

    /* test unaligned size */
    unmap_size = 0x2000;
    unmap_start = (char *)vaddr + existed_size - unmap_size;
    utest_int_equal(RT_EOK, rt_aspace_unmap_range(lwp->aspace, unmap_start, unmap_size - 0x123));
    utest_int_equal(former_vsz - unmap_size, rt_aspace_count_vsz(lwp->aspace));

    /* create another mapping binding to mem_obj without proper handler */
    notsupp_object = rt_mem_obj_create(&rt_mm_dummy_mapper);
    notsupp_object->on_varea_shrink = RT_NULL;

    utest_int_equal(
        RT_EOK,
        rt_aspace_map(lwp->aspace, (void *)&unmap_start, unmap_size, MMU_MAP_K_RWCB, flags, notsupp_object, 0)
    );

    utest_int_equal(-RT_EPERM, rt_aspace_unmap_range(lwp->aspace, unmap_start, 0x1000));
    utest_int_equal(RT_EOK, rt_aspace_unmap_range(lwp->aspace, vaddr, existed_size));
    rt_free(notsupp_object);
}

static void aspace_unmap_tc(void)
{
    CONSIST_HEAP(test_unmap_range_invalid_param());
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
UTEST_TC_EXPORT(testcase, "testcases.mm.aspace_unmap_range.invalid_param", utest_tc_init, utest_tc_cleanup, 10);
