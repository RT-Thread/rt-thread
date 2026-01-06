/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-09-03     Rbb666       the first version for mempool utest
 */
#include <rtthread.h>
#include <stdlib.h>
#include "utest.h"

#define MEMPOOL_BLOCK_SIZE  80
#define MEMPOOL_BLOCK_COUNT 32
#define MEMPOOL_SIZE        (MEMPOOL_BLOCK_SIZE + sizeof(rt_uint8_t *)) * MEMPOOL_BLOCK_COUNT

static rt_uint8_t        mempool_static[MEMPOOL_SIZE];
static struct rt_mempool mp_static;
static rt_mp_t           mp_dynamic;

/* Static memory pool test */
static void test_mp_static_init(void)
{
    rt_err_t err;

    err = rt_mp_init(&mp_static, "mp_static", &mempool_static[0], sizeof(mempool_static), MEMPOOL_BLOCK_SIZE);
    uassert_true(err == RT_EOK);
    uassert_str_equal(mp_static.parent.name, "mp_static");
    uassert_true(mp_static.block_total_count == MEMPOOL_BLOCK_COUNT);
    uassert_true(mp_static.block_free_count == MEMPOOL_BLOCK_COUNT);
}

/* Dynamic memory pool test */
static void test_mp_dynamic_create(void)
{
    mp_dynamic = rt_mp_create("mp_dynamic", MEMPOOL_BLOCK_COUNT, MEMPOOL_BLOCK_SIZE);
    uassert_not_null(mp_dynamic);
    uassert_str_equal(mp_dynamic->parent.name, "mp_dynamic");
    uassert_true(mp_dynamic->block_total_count == MEMPOOL_BLOCK_COUNT);
    uassert_true(mp_dynamic->block_free_count == MEMPOOL_BLOCK_COUNT);
}

/* Allocation and free test for static */
static void test_mp_static_alloc_free(void)
{
    void *block1, *block2, *block3;

    /* Allocate blocks */
    block1 = rt_mp_alloc(&mp_static, 0);
    uassert_not_null(block1);

    block2 = rt_mp_alloc(&mp_static, 0);
    uassert_not_null(block2);

    block3 = rt_mp_alloc(&mp_static, 0);
    uassert_not_null(block3);

    /* Check free count */
    uassert_true(mp_static.block_free_count == MEMPOOL_BLOCK_COUNT - 3);

    /* Free blocks */
    rt_mp_free(block1);
    rt_mp_free(block2);
    rt_mp_free(block3);

    /* Check free count */
    uassert_true(mp_static.block_free_count == MEMPOOL_BLOCK_COUNT);
}

/* Allocation and free test for dynamic */
static void test_mp_dynamic_alloc_free(void)
{
    void *block1, *block2, *block3;

    /* Allocate blocks */
    block1 = rt_mp_alloc(mp_dynamic, 0);
    uassert_not_null(block1);

    block2 = rt_mp_alloc(mp_dynamic, 0);
    uassert_not_null(block2);

    block3 = rt_mp_alloc(mp_dynamic, 0);
    uassert_not_null(block3);

    /* Check free count */
    uassert_true(mp_dynamic->block_free_count == MEMPOOL_BLOCK_COUNT - 3);

    /* Free blocks */
    rt_mp_free(block1);
    rt_mp_free(block2);
    rt_mp_free(block3);

    /* Check free count */
    uassert_true(mp_dynamic->block_free_count == MEMPOOL_BLOCK_COUNT);
}

/* Boundary test: allocate all blocks and try to allocate more */
static void test_mp_boundary_alloc_exceed(void)
{
    void *blocks[MEMPOOL_BLOCK_COUNT];
    void *extra_block;
    int   i;

    /* Allocate all blocks */
    for (i = 0; i < MEMPOOL_BLOCK_COUNT; i++)
    {
        blocks[i] = rt_mp_alloc(&mp_static, 0);
        uassert_not_null(blocks[i]);
    }

    /* Check free count */
    uassert_true(mp_static.block_free_count == 0);

    /* Try to allocate one more (should fail) */
    extra_block = rt_mp_alloc(&mp_static, 0);
    uassert_null(extra_block);

    /* Free all blocks */
    for (i = 0; i < MEMPOOL_BLOCK_COUNT; i++)
    {
        rt_mp_free(blocks[i]);
    }

    /* Check free count */
    uassert_true(mp_static.block_free_count == MEMPOOL_BLOCK_COUNT);
}

/* Boundary test: free invalid block */
static void test_mp_boundary_free_invalid(void)
{
    /* Test freeing NULL - should not crash and do nothing */
    rt_mp_free(RT_NULL);

    /* Check free count remains the same */
    uassert_true(mp_static.block_free_count == MEMPOOL_BLOCK_COUNT);
}

/* Stress test: allocate and free repeatedly */
static void test_mp_stress_alloc_free(void)
{
    void *blocks[MEMPOOL_BLOCK_COUNT];
    int   i, j;

    for (j = 0; j < 100; j++) /* Repeat 100 times */
    {
        /* Allocate all blocks */
        for (i = 0; i < MEMPOOL_BLOCK_COUNT; i++)
        {
            blocks[i] = rt_mp_alloc(&mp_static, 0);
            uassert_not_null(blocks[i]);
        }

        /* Check free count */
        uassert_true(mp_static.block_free_count == 0);

        /* Free all blocks */
        for (i = 0; i < MEMPOOL_BLOCK_COUNT; i++)
        {
            rt_mp_free(blocks[i]);
        }

        /* Check free count */
        uassert_true(mp_static.block_free_count == MEMPOOL_BLOCK_COUNT);
    }
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    /* Detach static mempool */
    rt_mp_detach(&mp_static);

    /* Delete dynamic mempool */
    if (mp_dynamic != RT_NULL)
    {
        rt_mp_delete(mp_dynamic);
    }

    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_mp_static_init);
    UTEST_UNIT_RUN(test_mp_dynamic_create);
    UTEST_UNIT_RUN(test_mp_static_alloc_free);
    UTEST_UNIT_RUN(test_mp_dynamic_alloc_free);
    UTEST_UNIT_RUN(test_mp_boundary_alloc_exceed);
    UTEST_UNIT_RUN(test_mp_boundary_free_invalid);
    UTEST_UNIT_RUN(test_mp_stress_alloc_free);
}

UTEST_TC_EXPORT(testcase, "core.mempool", utest_tc_init, utest_tc_cleanup, 10);
