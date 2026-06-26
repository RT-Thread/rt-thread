/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-22     Shell        test case for aspace_map with varea_expand
 */
#include "common.h"
#include "lwp_user_mm.h"
#include <mm_aspace.h>

#include <rtthread.h>

static long fd = -1;
static long pgoffset = 0;
static size_t flags = MAP_FIXED | MAP_ANONYMOUS;
static size_t prot1 = PROT_READ | PROT_WRITE;

static char *ex_vaddr = (void *)0x100000000;
static size_t map_size = 0x3000;

static size_t former_vsz;
static size_t former_vcount;

static struct rt_lwp *lwp;

static int _count_vsz(rt_varea_t varea, void *arg)
{
    rt_base_t *pvsz = arg;
    *pvsz += 1;
    return 0;
}

static rt_base_t count_vcount(rt_aspace_t aspace)
{
    rt_base_t vcount = 0;
    rt_aspace_traversal(aspace, _count_vsz, &vcount);
    return vcount;
}

static void test_mmap_expand(void)
{
    char *next_va;

    /* map new pages at ex_vaddr to anonymous */
    next_va = ex_vaddr;
    former_vsz = rt_aspace_count_vsz(lwp->aspace);
    former_vcount = count_vcount(lwp->aspace);
    next_va = lwp_mmap2(lwp, next_va, map_size, prot1, flags, fd, pgoffset);
    uassert_true(next_va == ex_vaddr);
    utest_int_equal(former_vsz + map_size, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount + 1, count_vcount(lwp->aspace));
    former_vsz += map_size;
    former_vcount += 1;

    /* test the RIGHT side expansion of varea by lwp_mmap2 */
    next_va = ex_vaddr + map_size;
    uassert_true(
        lwp_mmap2(lwp, next_va, map_size, prot1, flags, fd, pgoffset)
        == next_va
    );
    utest_int_equal(former_vsz + map_size, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount, count_vcount(lwp->aspace));
    former_vsz += map_size;

    /* test the LEFT side expansion of varea by rt_aspace_map */
    next_va = ex_vaddr - map_size;
    uassert_true(
        lwp_mmap2(lwp, next_va, map_size, prot1, flags, fd, pgoffset)
        == next_va
    );
    utest_int_equal(former_vsz + map_size, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount, count_vcount(lwp->aspace));
    former_vsz += map_size;

    /* test other prot/offset/flags */

    /* clear mapping */
    utest_int_equal(RT_EOK, rt_aspace_unmap_range(lwp->aspace, next_va, 3 * map_size));
}

static void aspace_map_tc(void)
{
    CONSIST_HEAP(test_mmap_expand());
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
    UTEST_UNIT_RUN(aspace_map_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.lwp.mman.mmap_anon.expand", utest_tc_init, utest_tc_cleanup, 10);
