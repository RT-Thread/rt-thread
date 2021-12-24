/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-14     tyx          the first version
 */

#include <rtthread.h>
#include <stdlib.h>
#include "utest.h"

#define TEST_SLAB_SIZE 1024 * 1024

static int _mem_cmp(void *ptr, rt_uint8_t v, rt_size_t size)
{
    while (size-- != 0)
    {
        if (*(rt_uint8_t *)ptr != v)
            return *(rt_uint8_t *)ptr - v;
    }
    return 0;
}

struct slab_alloc_context
{
    rt_list_t node;
    rt_size_t size;
    rt_uint8_t magic;
};

struct slab_alloc_head
{
    rt_list_t list;
    rt_size_t count;
    rt_tick_t start;
    rt_tick_t end;
    rt_tick_t interval;
};

#define SLAB_RANG_ALLOC_BLK_MIN  2
#define SLAB_RANG_ALLOC_BLK_MAX  5
#define SLAB_RANG_ALLOC_TEST_TIME 5

static void slab_alloc_test(void)
{
    struct slab_alloc_head head;
    rt_uint8_t *buf;
    rt_slab_t heap;
    rt_size_t size;
    struct slab_alloc_context *ctx;

    /* init */
    rt_list_init(&head.list);
    head.count = 0;
    head.start = rt_tick_get();
    head.end = rt_tick_get() + rt_tick_from_millisecond(SLAB_RANG_ALLOC_TEST_TIME * 1000);
    head.interval = (head.end - head.start) / 20;
    buf = rt_malloc(TEST_SLAB_SIZE);
    uassert_not_null(buf);
    uassert_int_equal(RT_ALIGN((rt_ubase_t)buf, RT_ALIGN_SIZE), (rt_ubase_t)buf);
    rt_memset(buf, 0xAA, TEST_SLAB_SIZE);
    heap = rt_slab_init("slab_tc", buf, TEST_SLAB_SIZE);
    // test run
    while (head.end - head.start < RT_TICK_MAX / 2)
    {
        if (rt_tick_get() - head.start >= head.interval)
        {
            head.start = rt_tick_get();
            rt_kprintf("#");
        }
        // %60 probability to perform alloc operation
        if (rand() % 10 >= 4)
        {
            size = rand() % SLAB_RANG_ALLOC_BLK_MAX + SLAB_RANG_ALLOC_BLK_MIN;
            size *= sizeof(struct slab_alloc_context);
            ctx = rt_slab_alloc(heap, size);
            if (ctx == RT_NULL)
            {
                if (head.count == 0)
                {
                    break;
                }
                size = head.count / 2;
                while (size != head.count)
                {
                    ctx = rt_list_first_entry(&head.list, struct slab_alloc_context, node);
                    rt_list_remove(&ctx->node);
                    if (ctx->size > sizeof(*ctx))
                    {
                        if (_mem_cmp(&ctx[1], ctx->magic, ctx->size - sizeof(*ctx)) != 0)
                        {
                            uassert_true(0);
                        }
                    }
                    rt_memset(ctx, 0xAA, ctx->size);
                    rt_slab_free(heap, ctx);
                    head.count --;
                }
                continue;
            }
            //if (RT_ALIGN((rt_ubase_t)ctx, RT_ALIGN_SIZE) != (rt_ubase_t)ctx)
            //{
            //    uassert_int_equal(RT_ALIGN((rt_ubase_t)ctx, RT_ALIGN_SIZE), (rt_ubase_t)ctx);
            //}
            rt_memset(ctx, 0, size);
            rt_list_init(&ctx->node);
            ctx->size = size;
            ctx->magic = rand() & 0xff;
            if (ctx->size > sizeof(*ctx))
            {
                rt_memset(&ctx[1], ctx->magic, ctx->size - sizeof(*ctx));
            }
            rt_list_insert_after(&head.list, &ctx->node);
            head.count += 1;
        }
        else
        {
            if (!rt_list_isempty(&head.list))
            {
                ctx = rt_list_first_entry(&head.list, struct slab_alloc_context, node);
                rt_list_remove(&ctx->node);
                if (ctx->size > sizeof(*ctx))
                {
                    if (_mem_cmp(&ctx[1], ctx->magic, ctx->size - sizeof(*ctx)) != 0)
                    {
                        uassert_true(0);
                    }
                }
                rt_memset(ctx, 0xAA, ctx->size);
                rt_slab_free(heap, ctx);
                head.count --;
            }
        }
    }
    while (!rt_list_isempty(&head.list))
    {
        ctx = rt_list_first_entry(&head.list, struct slab_alloc_context, node);
        rt_list_remove(&ctx->node);
        if (ctx->size > sizeof(*ctx))
        {
            if (_mem_cmp(&ctx[1], ctx->magic, ctx->size - sizeof(*ctx)) != 0)
            {
                uassert_true(0);
            }
        }
        rt_memset(ctx, 0xAA, ctx->size);
        rt_slab_free(heap, ctx);
        head.count --;
    }
    uassert_int_equal(head.count, 0);
    // slab heap deinit
    rt_slab_detach(heap);
    /* release test resources */
    rt_free(buf);
}

#define SLAB_RANG_REALLOC_BLK_MIN  0
#define SLAB_RANG_REALLOC_BLK_MAX  5
#define SLAB_RANG_REALLOC_TEST_TIME 5

struct slab_realloc_context
{
    rt_size_t size;
    rt_uint8_t magic;
};

struct slab_realloc_head
{
    struct slab_realloc_context **ctx_tab;
    rt_size_t count;
    rt_tick_t start;
    rt_tick_t end;
    rt_tick_t interval;
};

static void slab_realloc_test(void)
{
    struct slab_realloc_head head;
    rt_uint8_t *buf;
    rt_slab_t heap;
    rt_size_t size, idx;
    struct slab_realloc_context *ctx;
    int res;

    size = RT_ALIGN(sizeof(struct slab_realloc_context), RT_ALIGN_SIZE) + RT_ALIGN_SIZE;
    size = TEST_SLAB_SIZE / size;
    /* init */
    head.ctx_tab = RT_NULL;
    head.count = size;
    head.start = rt_tick_get();
    head.end = rt_tick_get() + rt_tick_from_millisecond(SLAB_RANG_ALLOC_TEST_TIME * 1000);
    head.interval = (head.end - head.start) / 20;
    buf = rt_malloc(TEST_SLAB_SIZE);
    uassert_not_null(buf);
    uassert_int_equal(RT_ALIGN((rt_ubase_t)buf, RT_ALIGN_SIZE), (rt_ubase_t)buf);
    rt_memset(buf, 0xAA, TEST_SLAB_SIZE);
    heap = rt_slab_init("slab_tc", buf, TEST_SLAB_SIZE);
    /* init ctx tab */
    size = head.count * sizeof(struct slab_realloc_context *);
    head.ctx_tab = rt_slab_alloc(heap, size);
    uassert_not_null(head.ctx_tab);
    rt_memset(head.ctx_tab, 0, size);
    // test run
    while (head.end - head.start < RT_TICK_MAX / 2)
    {
        if (rt_tick_get() - head.start >= head.interval)
        {
            head.start = rt_tick_get();
            rt_kprintf("#");
        }
        size = rand() % SLAB_RANG_ALLOC_BLK_MAX + SLAB_RANG_ALLOC_BLK_MIN;
        size *= sizeof(struct slab_realloc_context);
        idx = rand() % head.count;
        ctx = rt_slab_realloc(heap, head.ctx_tab[idx], size);
        if (ctx == RT_NULL)
        {
            if (size == 0)
            {
                if (head.ctx_tab[idx])
                {
                    head.ctx_tab[idx] = RT_NULL;
                }
            }
            else
            {
                for (idx = 0; idx < head.count; idx++)
                {
                    ctx = head.ctx_tab[idx];
                    if (rand() % 2 && ctx)
                    {
                        if (ctx->size > sizeof(*ctx))
                        {
                            res = _mem_cmp(&ctx[1], ctx->magic, ctx->size - sizeof(*ctx));
                            if (res != 0)
                            {
                                uassert_int_equal(res, 0);
                            }
                        }
                        rt_memset(ctx, 0xAA, ctx->size);
                        rt_slab_realloc(heap, ctx, 0);
                        head.ctx_tab[idx] = RT_NULL;
                    }
                }
            }
            continue;
        }
        /* check slab */
        if (head.ctx_tab[idx] != RT_NULL)
        {
            res = 0;
            if (ctx->size < size)
            {
                if (ctx->size > sizeof(*ctx))
                {
                    res = _mem_cmp(&ctx[1], ctx->magic, ctx->size - sizeof(*ctx));
                }
            }
            else
            {
                if (size > sizeof(*ctx))
                {
                    res = _mem_cmp(&ctx[1], ctx->magic, size - sizeof(*ctx));
                }
            }
            if (res != 0)
            {
                uassert_int_equal(res, 0);
            }
        }
        /* init slab */
        ctx->magic = rand() & 0xff;
        ctx->size = size;
        if (ctx->size > sizeof(*ctx))
        {
            rt_memset(&ctx[1], ctx->magic, ctx->size - sizeof(*ctx));
        }
        head.ctx_tab[idx] = ctx;
    }
    // free all slab
    for (idx = 0; idx < head.count; idx++)
    {
        ctx = head.ctx_tab[idx];
        if (ctx == RT_NULL)
        {
            continue;
        }
        if (ctx->size > sizeof(*ctx))
        {
            res = _mem_cmp(&ctx[1], ctx->magic, ctx->size - sizeof(*ctx));
            if (res != 0)
            {
                uassert_int_equal(res, 0);
            }
        }
        rt_memset(ctx, 0xAA, ctx->size);
        rt_slab_realloc(heap, ctx, 0);
        head.ctx_tab[idx] = RT_NULL;
    }
    // slab heap deinit
    rt_slab_detach(heap);
    /* release test resources */
    rt_free(buf);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(slab_alloc_test);
    UTEST_UNIT_RUN(slab_realloc_test);
}
UTEST_TC_EXPORT(testcase, "testcases.kernel.slab_tc", utest_tc_init, utest_tc_cleanup, 20);
