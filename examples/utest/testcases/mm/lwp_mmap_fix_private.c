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
#include "mm_fault.h"
#include <mm_aspace.h>

#include <rtthread.h>

static long fd = -1;
static long pgoffset = 0;
static size_t flags = MAP_FIXED | MAP_ANONYMOUS;
static size_t prot = PROT_READ | PROT_WRITE;

static char *ex_vaddr = (char *)0x100000000;
static size_t ex_size = 0x5000;
static char *private0 = (char *)0x100000000;
static char *private1 = (char *)0x100000000 + 0x1000;
static char *private2 = (char *)0x100000000 + 0x2000;
static char *private3 = (char *)0x100000000 + 0x3000;
static char *private4 = (char *)0x100000000 + 0x4000;

/**
 * todo: suppoprt prefetch pages, so more than 1 page can install to private at a time
 * static size_t priv_size = 0x1000;
 */

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

static void test_mmap_fix_private(void)
{
    char *next_va;
    struct rt_aspace_fault_msg msg;
    msg.fault_op = MM_FAULT_OP_WRITE;
    msg.fault_type = MM_FAULT_TYPE_RWX_PERM;

    /* map new pages at ex_vaddr to anonymous */
    next_va = ex_vaddr;
    former_vsz = rt_aspace_count_vsz(lwp->aspace);
    former_vcount = count_vcount(lwp->aspace);
    next_va = lwp_mmap2(lwp, next_va, ex_size, prot, flags, fd, pgoffset);
    uassert_true(next_va == ex_vaddr);
    utest_int_equal(former_vsz + ex_size, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount + 1, count_vcount(lwp->aspace));
    former_vsz += ex_size;
    former_vcount += 1;

    /* fix private in the middle */
    msg.fault_vaddr = private2;
    utest_int_equal(MM_FAULT_FIXABLE_TRUE, rt_aspace_fault_try_fix(lwp->aspace, &msg));
    utest_int_equal(former_vsz, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount + 2, count_vcount(lwp->aspace));
    former_vcount += 2;

    /* fix private from left most */
    msg.fault_vaddr = private0;
    utest_int_equal(MM_FAULT_FIXABLE_TRUE, rt_aspace_fault_try_fix(lwp->aspace, &msg));
    utest_int_equal(former_vsz, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount + 1, count_vcount(lwp->aspace));
    former_vcount += 1;

    /* fix private from right most */
    msg.fault_vaddr = private4;
    utest_int_equal(MM_FAULT_FIXABLE_TRUE, rt_aspace_fault_try_fix(lwp->aspace, &msg));
    utest_int_equal(former_vsz, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount + 1, count_vcount(lwp->aspace));
    former_vcount += 1;

    /* fix private from left-middle */
    msg.fault_vaddr = private1;
    utest_int_equal(MM_FAULT_FIXABLE_TRUE, rt_aspace_fault_try_fix(lwp->aspace, &msg));
    utest_int_equal(former_vsz, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount - 1, count_vcount(lwp->aspace));
    former_vcount -= 1;

    /* fix private from right-middle */
    msg.fault_vaddr = private3;
    utest_int_equal(MM_FAULT_FIXABLE_TRUE, rt_aspace_fault_try_fix(lwp->aspace, &msg));
    utest_int_equal(former_vsz, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount - 1, count_vcount(lwp->aspace));
    former_vcount -= 1;

    /* clear mapping */
    utest_int_equal(RT_EOK, rt_aspace_unmap_range(lwp->aspace, ex_vaddr, ex_size));
    rt_free(lwp->aspace->private_object);
    lwp->aspace->private_object = RT_NULL;
}

static void testcase_main(void)
{
    CONSIST_HEAP(test_mmap_fix_private());
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
    UTEST_UNIT_RUN(testcase_main);
}
UTEST_TC_EXPORT(testcase, "testcases.lwp.mman.mmap_anon.fix_private", utest_tc_init, utest_tc_cleanup, 10);
