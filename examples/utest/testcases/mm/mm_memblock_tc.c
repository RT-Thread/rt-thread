/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-07     zmshahaha    the first version
 */

#include <mm_memblock.h>
#include "common.h"

#define SZ_128M             0x08000000
#define SZ_256M             0x10000000
#define SZ_512M             0x20000000
#define SZ_1G               0x40000000

#define NEXT_MEMREG(prev) rt_slist_entry(prev->node.next, struct rt_mmblk_reg, node)

rt_inline struct rt_mmblk_reg *_nth_reg(rt_uint32_t n)
{
    struct rt_mmblk_reg *ret = RT_NULL;

    rt_slist_for_each_entry(ret, &(mmblk_memory.reg_list), node)
    {
        if(--n == 0)
            return ret;
    }

    return ret;
}

rt_inline rt_uint32_t _reg_cnt()
{
    rt_uint32_t ret = 0;
    struct rt_mmblk_reg *reg;

    rt_slist_for_each_entry(reg, &(mmblk_memory.reg_list), node)
    {
        ret++;
    }

    return ret;
}

static void _reset_memblock(void)
{
    struct rt_mmblk_reg *reg;

    rt_slist_for_each_entry(reg, &(mmblk_memory.reg_list), node)
    {
        reg->alloc = RT_FALSE;
    }
    mmblk_memory.reg_list.next = RT_NULL;
}

static void test_memblock_add_simple(void)
{
    _reset_memblock();

    rt_ubase_t base1 = SZ_1G, size1 = SZ_256M;
    rt_ubase_t base2 = SZ_128M, size2 = SZ_128M;

    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base1,
        .end = (rt_size_t)(base1 + size1),
    });

    uassert_int_equal(_nth_reg(1)->memreg.start, base1);
    uassert_int_equal(_nth_reg(1)->memreg.end, base1 + size1);
    uassert_int_equal(_nth_reg(1)->flags, 0);
    uassert_int_equal(_reg_cnt(), 1);

    rt_memblock_add_memory_ext(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base2,
        .end = (rt_size_t)(base2 + size2),
    }, 1);

    uassert_int_equal(_nth_reg(1)->memreg.start, base2);
    uassert_int_equal(_nth_reg(1)->memreg.end, base2 + size2);
    uassert_int_equal(_nth_reg(1)->flags, 1);
    uassert_int_equal(_nth_reg(2)->memreg.start, base1);
    uassert_int_equal(_nth_reg(2)->memreg.end, base1 + size1);
    uassert_int_equal(_nth_reg(2)->flags, 0);
    uassert_int_equal(_reg_cnt(), 2);
}

static void test_memblock_add_overlap_top(void)
{
    _reset_memblock();

    rt_ubase_t base1 = SZ_512M, size1 = SZ_1G;
    rt_ubase_t base2 = SZ_256M, size2 = SZ_512M;

    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base1,
        .end = (rt_size_t)(base1 + size1),
    });
    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base2,
        .end = (rt_size_t)(base2 + size2),
    });

    uassert_int_equal(_nth_reg(1)->memreg.start, SZ_256M);
    uassert_int_equal(_nth_reg(1)->memreg.end, SZ_1G + SZ_512M);
    uassert_int_equal(_reg_cnt(), 1);
}

static void test_memblock_add_overlap_bottom(void)
{
    _reset_memblock();

    rt_ubase_t base1 = SZ_128M, size1 = SZ_512M;
    rt_ubase_t base2 = SZ_256M, size2 = SZ_1G;

    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base1,
        .end = (rt_size_t)(base1 + size1),
    });
    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base2,
        .end = (rt_size_t)(base2 + size2),
    });

    uassert_int_equal(_nth_reg(1)->memreg.start, SZ_128M);
    uassert_int_equal(_nth_reg(1)->memreg.end, SZ_1G + SZ_256M);
    uassert_int_equal(_reg_cnt(), 1);
}

static void test_memblock_add_within(void)
{
    _reset_memblock();

    rt_ubase_t base1 = SZ_128M, size1 = SZ_1G;
    rt_ubase_t base2 = SZ_256M, size2 = SZ_512M;

    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base1,
        .end = (rt_size_t)(base1 + size1),
    });
    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base2,
        .end = (rt_size_t)(base2 + size2),
    });

    uassert_int_equal(_nth_reg(1)->memreg.start, SZ_128M);
    uassert_int_equal(_nth_reg(1)->memreg.end, SZ_1G + SZ_128M);
    uassert_int_equal(_reg_cnt(), 1);
}

static void test_memblock_add_twice(void)
{
    _reset_memblock();

    rt_ubase_t base1 = SZ_128M, size1 = SZ_1G;

    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base1,
        .end = (rt_size_t)(base1 + size1),
    });
    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base1,
        .end = (rt_size_t)(base1 + size1),
    });

    uassert_int_equal(_nth_reg(1)->memreg.start, SZ_128M);
    uassert_int_equal(_nth_reg(1)->memreg.end, SZ_1G + SZ_128M);
    uassert_int_equal(_reg_cnt(), 1);
}

static void test_memblock_add_between(void)
{
    _reset_memblock();

    rt_ubase_t base1 = SZ_512M, size1 = SZ_256M;
    rt_ubase_t base2 = SZ_1G, size2 = SZ_512M;
    rt_ubase_t base3 = SZ_512M + SZ_256M, size3 = SZ_256M;

    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base1,
        .end = (rt_size_t)(base1 + size1),
    });
    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base2,
        .end = (rt_size_t)(base2 + size2),
    });
    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base3,
        .end = (rt_size_t)(base3 + size3),
    });

    uassert_int_equal(_nth_reg(1)->memreg.start, SZ_512M);
    uassert_int_equal(_nth_reg(1)->memreg.end, SZ_1G + SZ_512M);
    uassert_int_equal(_reg_cnt(), 1);
}

static void test_memblock_add(void)
{
    test_memblock_add_simple();
    test_memblock_add_overlap_top();
    test_memblock_add_overlap_bottom();
    test_memblock_add_within();
    test_memblock_add_twice();
    test_memblock_add_between();
}

static void test_memblock_reserve(void)
{
    _reset_memblock();

    rt_ubase_t base1 = SZ_128M, size1 = SZ_256M;
    rt_ubase_t base2 = SZ_512M, size2 = SZ_256M;
    rt_ubase_t base3 = SZ_1G, size3 = SZ_512M;
    rt_ubase_t base_reserve = SZ_256M, size_reserve = SZ_1G;

    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base1,
        .end = (rt_size_t)(base1 + size1),
    });
    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base2,
        .end = (rt_size_t)(base2 + size2),
    });
    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base3,
        .end = (rt_size_t)(base3 + size3),
    });
    rt_memblock_reserve(&(rt_region_t)
    {
        .name = "reserve",
        .start = (rt_size_t)base_reserve,
        .end = (rt_size_t)(base_reserve + size_reserve),
    });

    uassert_int_equal(_reg_cnt(), 3);
    uassert_int_equal(_nth_reg(1)->memreg.start, SZ_128M);
    uassert_int_equal(_nth_reg(1)->memreg.end, SZ_256M);
    uassert_int_equal(_nth_reg(1)->flags, MEMBLOCK_NORMAL);
    uassert_int_equal(_nth_reg(2)->memreg.start, SZ_256M);
    uassert_int_equal(_nth_reg(2)->memreg.end, SZ_256M + SZ_1G);
    uassert_int_equal(_nth_reg(2)->flags, MEMBLOCK_RESERVED);
    uassert_int_equal(_nth_reg(3)->memreg.start, SZ_256M + SZ_1G);
    uassert_int_equal(_nth_reg(3)->memreg.end, SZ_512M + SZ_1G);
    uassert_int_equal(_nth_reg(3)->flags, MEMBLOCK_NORMAL);
}

static void test_memblock_reserve_before_add(void)
{
    _reset_memblock();

    rt_ubase_t base1 = SZ_128M, size1 = SZ_256M;
    rt_ubase_t base2 = SZ_512M, size2 = SZ_256M;
    rt_ubase_t base3 = SZ_1G, size3 = SZ_512M;
    rt_ubase_t base_reserve = SZ_256M, size_reserve = SZ_1G;

    rt_memblock_reserve(&(rt_region_t)
    {
        .name = "reserve",
        .start = (rt_size_t)base_reserve,
        .end = (rt_size_t)(base_reserve + size_reserve),
    });
    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base1,
        .end = (rt_size_t)(base1 + size1),
    });
    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base2,
        .end = (rt_size_t)(base2 + size2),
    });
    rt_memblock_add_memory(&(rt_region_t)
    {
        .name = "memory",
        .start = (rt_size_t)base3,
        .end = (rt_size_t)(base3 + size3),
    });

    uassert_int_equal(_reg_cnt(), 3);
    uassert_int_equal(_nth_reg(1)->memreg.start, SZ_128M);
    uassert_int_equal(_nth_reg(1)->memreg.end, SZ_256M);
    uassert_int_equal(_nth_reg(1)->flags, MEMBLOCK_NORMAL);
    uassert_int_equal(_nth_reg(2)->memreg.start, SZ_256M);
    uassert_int_equal(_nth_reg(2)->memreg.end, SZ_256M + SZ_1G);
    uassert_int_equal(_nth_reg(2)->flags, MEMBLOCK_RESERVED);
    uassert_int_equal(_nth_reg(3)->memreg.start, SZ_256M + SZ_1G);
    uassert_int_equal(_nth_reg(3)->memreg.end, SZ_512M + SZ_1G);
    uassert_int_equal(_nth_reg(3)->flags, MEMBLOCK_NORMAL);
}

static rt_err_t utest_tc_init(void)
{
    _reset_memblock();

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_memblock_add);
    UTEST_UNIT_RUN(test_memblock_reserve);
    UTEST_UNIT_RUN(test_memblock_reserve_before_add);
}
UTEST_TC_EXPORT(testcase, "testcases.mm.memblock_tc", utest_tc_init, utest_tc_cleanup, 20);
