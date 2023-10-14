/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-28     zmshahaha    the first version
 */

#include <mm_memblock.h>
#include "common.h"
#include <rtservice.h>

#define SZ_128M             0x08000000
#define SZ_256M             0x10000000
#define SZ_512M             0x20000000
#define SZ_1G               0x40000000

static struct rt_memblock *mmblk_memory;
static struct rt_memblock *mmblk_reserved;

void rt_memblock_next_free_region_init(void);
void rt_memblock_next_free_region(mmblk_flag_t flags, rt_size_t *out_start, rt_size_t *out_end);
rt_bool_t rt_memblock_is_last_free(void);
void rt_memblock_merge(void);

struct rt_mmblk_reg *_nth_reg(struct rt_memblock *memblock, rt_uint32_t n)
{
    struct rt_mmblk_reg *ret = RT_NULL;

    rt_slist_for_each_entry(ret, &(memblock->reg_list), node)
    {
        if (--n == 0)
            return ret;
    }

    return ret;
}

rt_uint32_t _reg_cnt(struct rt_memblock *memblock)
{
    rt_uint32_t ret = 0;
    struct rt_mmblk_reg *reg;

    rt_slist_for_each_entry(reg, &(memblock->reg_list), node)
    {
        ret++;
    }

    return ret;
}

void _reset_memblock(void)
{
    struct rt_mmblk_reg *reg;

    rt_slist_for_each_entry(reg, &(mmblk_memory->reg_list), node)
    {
        reg->alloc = RT_FALSE;
    }
    rt_slist_for_each_entry(reg, &(mmblk_reserved->reg_list), node)
    {
        reg->alloc = RT_FALSE;
    }

    mmblk_memory->reg_list.next = RT_NULL;
    mmblk_reserved->reg_list.next = RT_NULL;
}

static void test_memblock_add_simple(void)
{
    _reset_memblock();

    rt_size_t base1 = SZ_1G, size1 = SZ_256M;
    rt_size_t base2 = SZ_128M, size2 = SZ_128M;
    rt_err_t err;

    err = rt_memblock_add_memory("memory1", base1, base1 + size1, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);

    uassert_int_equal(_reg_cnt(mmblk_memory), 1);

    uassert_int_equal(_nth_reg(mmblk_memory, 1)->memreg.start, base1);
    uassert_int_equal(_nth_reg(mmblk_memory, 1)->memreg.end, base1 + size1);
    uassert_int_equal(_nth_reg(mmblk_memory, 1)->flags, MEMBLOCK_NONE);

    err = rt_memblock_add_memory("memory2", base2, base2 + size2, MEMBLOCK_HOTPLUG);
    uassert_int_equal(err, RT_EOK);

    uassert_int_equal(_reg_cnt(mmblk_memory), 2);

    uassert_int_equal(_nth_reg(mmblk_memory, 1)->memreg.start, base2);
    uassert_int_equal(_nth_reg(mmblk_memory, 1)->memreg.end, base2 + size2);
    uassert_int_equal(_nth_reg(mmblk_memory, 1)->flags, MEMBLOCK_HOTPLUG);

    uassert_int_equal(_nth_reg(mmblk_memory, 2)->memreg.start, base1);
    uassert_int_equal(_nth_reg(mmblk_memory, 2)->memreg.end, base1 + size1);
    uassert_int_equal(_nth_reg(mmblk_memory, 2)->flags, MEMBLOCK_NONE);
}

static void test_memblock_add_adjacent_top(void)
{
    _reset_memblock();

    rt_size_t base1 = SZ_128M, size1 = SZ_128M;
    rt_size_t base2 = SZ_256M, size2 = SZ_128M;
    rt_err_t err;

    err = rt_memblock_add_memory("memory1", base1, base1 + size1, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_add_memory("memory2", base2, base2 + size2, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);

    uassert_int_equal(_reg_cnt(mmblk_memory), 2);

    uassert_int_equal(_nth_reg(mmblk_memory, 1)->memreg.start, base1);
    uassert_int_equal(_nth_reg(mmblk_memory, 1)->memreg.end, base1 + size1);
    uassert_int_equal(_nth_reg(mmblk_memory, 1)->flags, MEMBLOCK_NONE);

    uassert_int_equal(_nth_reg(mmblk_memory, 2)->memreg.start, base2);
    uassert_int_equal(_nth_reg(mmblk_memory, 2)->memreg.end, base2 + size2);
    uassert_int_equal(_nth_reg(mmblk_memory, 2)->flags, MEMBLOCK_NONE);
}

static void test_memblock_add_adjacent_bottom(void)
{
    _reset_memblock();

    rt_size_t base1 = SZ_256M, size1 = SZ_128M;
    rt_size_t base2 = SZ_128M, size2 = SZ_128M;
    rt_err_t err;

    err = rt_memblock_add_memory("memory1", base1, base1 + size1, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_add_memory("memory2", base2, base2 + size2, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);

    uassert_int_equal(_reg_cnt(mmblk_memory), 2);

    uassert_int_equal(_nth_reg(mmblk_memory, 1)->memreg.start, base2);
    uassert_int_equal(_nth_reg(mmblk_memory, 1)->memreg.end, base2 + size2);
    uassert_int_equal(_nth_reg(mmblk_memory, 1)->flags, MEMBLOCK_NONE);

    uassert_int_equal(_nth_reg(mmblk_memory, 2)->memreg.start, base1);
    uassert_int_equal(_nth_reg(mmblk_memory, 2)->memreg.end, base1 + size1);
    uassert_int_equal(_nth_reg(mmblk_memory, 2)->flags, MEMBLOCK_NONE);
}

static void test_memblock_add_between(void)
{
    _reset_memblock();

    rt_size_t base1 = SZ_512M, size1 = SZ_256M;
    rt_size_t base2 = SZ_1G, size2 = SZ_512M;
    rt_size_t base3 = SZ_512M + SZ_256M, size3 = SZ_256M;
    rt_err_t err;

    err = rt_memblock_add_memory("memory1", base1, base1 + size1, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_add_memory("memory2", base2, base2 + size2, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_add_memory("memory3", base3, base3 + size3, MEMBLOCK_HOTPLUG);
    uassert_int_equal(err, RT_EOK);

    uassert_int_equal(_reg_cnt(mmblk_memory), 3);

    uassert_int_equal(_nth_reg(mmblk_memory, 1)->memreg.start, base1);
    uassert_int_equal(_nth_reg(mmblk_memory, 1)->memreg.end, base1 + size1);
    uassert_int_equal(_nth_reg(mmblk_memory, 1)->flags, MEMBLOCK_NONE);

    uassert_int_equal(_nth_reg(mmblk_memory, 2)->memreg.start, base3);
    uassert_int_equal(_nth_reg(mmblk_memory, 2)->memreg.end, base3 + size3);
    uassert_int_equal(_nth_reg(mmblk_memory, 2)->flags, MEMBLOCK_HOTPLUG);

    uassert_int_equal(_nth_reg(mmblk_memory, 3)->memreg.start, base2);
    uassert_int_equal(_nth_reg(mmblk_memory, 3)->memreg.end, base2 + size2);
    uassert_int_equal(_nth_reg(mmblk_memory, 3)->flags, MEMBLOCK_NONE);
}

static void test_memblock_merge(void)
{
    _reset_memblock();

    rt_size_t base1 = 0, size1 = SZ_256M;
    rt_size_t base2 = SZ_256M, size2 = SZ_256M;
    rt_size_t base3 = SZ_512M, size3 = SZ_256M;
    rt_size_t base4 = SZ_512M + SZ_256M, size4 = SZ_256M;
    rt_size_t base5 = SZ_1G, size5 = SZ_512M;
    rt_err_t err;

    err = rt_memblock_add_memory("memory1", base1, base1 + size1, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_add_memory("memory2", base2, base2 + size2, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_add_memory("memory3", base3, base3 + size3, MEMBLOCK_HOTPLUG);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_add_memory("memory4", base4, base4 + size4, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_add_memory("memory5", base5, base5 + size5, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);

    rt_memblock_merge();

    uassert_int_equal(_reg_cnt(mmblk_memory), 3);

    uassert_int_equal(_nth_reg(mmblk_memory, 1)->memreg.start, base1);
    uassert_int_equal(_nth_reg(mmblk_memory, 1)->memreg.end, base2 + size2);
    uassert_int_equal(_nth_reg(mmblk_memory, 1)->flags, MEMBLOCK_NONE);

    uassert_int_equal(_nth_reg(mmblk_memory, 2)->memreg.start, base3);
    uassert_int_equal(_nth_reg(mmblk_memory, 2)->memreg.end, base3 + size3);
    uassert_int_equal(_nth_reg(mmblk_memory, 2)->flags, MEMBLOCK_HOTPLUG);

    uassert_int_equal(_nth_reg(mmblk_memory, 3)->memreg.start, base4);
    uassert_int_equal(_nth_reg(mmblk_memory, 3)->memreg.end, base5 + size5);
    uassert_int_equal(_nth_reg(mmblk_memory, 3)->flags, MEMBLOCK_NONE);
}

static void test_memblock_add(void)
{
    test_memblock_add_simple();
    test_memblock_add_adjacent_top();
    test_memblock_add_adjacent_bottom();
    test_memblock_add_between();
    test_memblock_merge();
}

static void test_memblock_reserve_in_memory_start(void)
{
    _reset_memblock();

    rt_size_t base1 = SZ_128M, size1 = SZ_256M;
    rt_size_t baser = SZ_128M, sizer = SZ_128M;
    rt_size_t free_start, free_end;
    rt_err_t err;

    err = rt_memblock_add_memory("memory", base1, base1 + size1, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_reserve_memory("reserve", baser, baser + sizer, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);

    rt_memblock_next_free_region_init();

    rt_memblock_next_free_region(MEMBLOCK_NONE, &free_start, &free_end);
    uassert_int_equal(free_start, SZ_256M);
    uassert_int_equal(free_end, SZ_128M + SZ_256M);

    rt_memblock_next_free_region(MEMBLOCK_NONE, &free_start, &free_end);
    uassert_int_equal(rt_memblock_is_last_free(), RT_TRUE);
}

static void test_memblock_reserve_in_memory_end(void)
{
    _reset_memblock();

    rt_size_t base1 = SZ_128M, size1 = SZ_256M;
    rt_size_t baser = SZ_256M, sizer = SZ_128M;
    rt_size_t free_start, free_end;
    rt_err_t err;

    err = rt_memblock_add_memory("memory", base1, base1 + size1, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_reserve_memory("reserve", baser, baser + sizer, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);

    rt_memblock_next_free_region_init();

    rt_memblock_next_free_region(MEMBLOCK_NONE, &free_start, &free_end);
    uassert_int_equal(free_start, SZ_128M);
    uassert_int_equal(free_end, SZ_256M);

    rt_memblock_next_free_region(MEMBLOCK_NONE, &free_start, &free_end);
    uassert_int_equal(rt_memblock_is_last_free(), RT_TRUE);
}

static void test_memblock_reserve_many_in_one_region(void)
{
    _reset_memblock();

    rt_size_t base = 0, size = SZ_1G;
    rt_size_t baser1 = 0, sizer1 = SZ_128M;
    rt_size_t baser2 = SZ_256M, sizer2 = SZ_128M;
    rt_size_t baser3 = SZ_256M + SZ_128M, sizer3 = SZ_128M;
    rt_size_t baser4 = SZ_512M + SZ_128M, sizer4 = SZ_128M;
    rt_size_t baser5 = SZ_1G - SZ_128M, sizer5 = SZ_128M;
    rt_size_t free_start, free_end;
    rt_err_t err;

    err = rt_memblock_add_memory("memory", base, base + size, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_reserve_memory("reserve1", baser1, baser1 + sizer1, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_reserve_memory("reserve2", baser2, baser2 + sizer2, MEMBLOCK_NOMAP);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_reserve_memory("reserve3", baser3, baser3 + sizer3, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_reserve_memory("reserve4", baser4, baser4 + sizer4, MEMBLOCK_NOMAP);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_reserve_memory("reserve5", baser5, baser5 + sizer5, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);

    rt_memblock_next_free_region_init();

    rt_memblock_next_free_region(MEMBLOCK_NONE, &free_start, &free_end);
    uassert_int_equal(free_start, SZ_128M);
    uassert_int_equal(free_end, SZ_256M);

    rt_memblock_next_free_region(MEMBLOCK_NONE, &free_start, &free_end);
    uassert_int_equal(free_start, SZ_512M);
    uassert_int_equal(free_end, SZ_512M + SZ_128M);

    rt_memblock_next_free_region(MEMBLOCK_NONE, &free_start, &free_end);
    uassert_int_equal(free_start, SZ_512M + SZ_256M);
    uassert_int_equal(free_end, SZ_1G - SZ_128M);

    rt_memblock_next_free_region(MEMBLOCK_NONE, &free_start, &free_end);
    uassert_int_equal(rt_memblock_is_last_free(), RT_TRUE);
}

static void test_memblock_reserve_large_region(void)
{
    _reset_memblock();

    rt_size_t base1 = 0, size1 = SZ_256M;
    rt_size_t base2 = SZ_256M, size2 = SZ_256M;
    rt_size_t base3 = SZ_512M, size3 = SZ_256M;
    rt_size_t base4 = SZ_512M + SZ_256M, size4 = SZ_256M;
    rt_size_t baser = SZ_256M + SZ_128M, sizer = SZ_512M;
    rt_size_t free_start, free_end;
    rt_err_t err;

    err = rt_memblock_add_memory("memory1", base1, base1 + size1, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_add_memory("memory2", base2, base2 + size2, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_add_memory("memory3", base3, base3 + size3, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_add_memory("memory4", base4, base4 + size4, MEMBLOCK_NONE);
    uassert_int_equal(err, RT_EOK);
    err = rt_memblock_reserve_memory("reserve", baser, baser + sizer, MEMBLOCK_NOMAP);
    uassert_int_equal(err, RT_EOK);

    rt_memblock_next_free_region_init();

    rt_memblock_next_free_region(MEMBLOCK_NONE, &free_start, &free_end);
    uassert_int_equal(free_start, 0);
    uassert_int_equal(free_end, SZ_256M);

    rt_memblock_next_free_region(MEMBLOCK_NONE, &free_start, &free_end);
    uassert_int_equal(free_start, SZ_256M);
    uassert_int_equal(free_end, SZ_256M + SZ_128M);

    rt_memblock_next_free_region(MEMBLOCK_NONE, &free_start, &free_end);
    uassert_int_equal(free_start, SZ_512M + SZ_256M + SZ_128M);
    uassert_int_equal(free_end, SZ_1G);

    rt_memblock_next_free_region(MEMBLOCK_NONE, &free_start, &free_end);
    uassert_int_equal(rt_memblock_is_last_free(), RT_TRUE);
}

static void test_memblock_reserve(void)
{
    test_memblock_reserve_in_memory_start();
    test_memblock_reserve_in_memory_end();
    test_memblock_reserve_many_in_one_region();
    test_memblock_reserve_large_region();
}

static rt_err_t utest_tc_init(void)
{
    mmblk_memory = rt_memblock_get_memory();
    mmblk_reserved = rt_memblock_get_reserved();
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
}
UTEST_TC_EXPORT(testcase, "testcases.mm.memblock_tc", utest_tc_init, utest_tc_cleanup, 20);
