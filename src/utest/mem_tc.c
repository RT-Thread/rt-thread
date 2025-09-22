/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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

struct rt_small_mem_item
{
    rt_ubase_t              pool_ptr;         /**< small memory object addr */
    rt_size_t               next;             /**< next free item */
    rt_size_t               prev;             /**< prev free item */
#ifdef RT_USING_MEMTRACE
#ifdef ARCH_CPU_64BIT
    rt_uint8_t              thread[8];       /**< thread name */
#else
    rt_uint8_t              thread[4];       /**< thread name */
#endif /* ARCH_CPU_64BIT */
#endif /* RT_USING_MEMTRACE */
};

struct rt_small_mem
{
    struct rt_memory            parent;                 /**< inherit from rt_memory */
    rt_uint8_t                 *heap_ptr;               /**< pointer to the heap */
    struct rt_small_mem_item   *heap_end;
    struct rt_small_mem_item   *lfree;
    rt_size_t                   mem_size_aligned;       /**< aligned memory size */
};

#define MEM_SIZE(_heap, _mem)      \
    (((struct rt_small_mem_item *)(_mem))->next - ((rt_ubase_t)(_mem) - \
    (rt_ubase_t)((_heap)->heap_ptr)) - RT_ALIGN(sizeof(struct rt_small_mem_item), RT_ALIGN_SIZE))

#define TEST_MEM_SIZE 1024

static rt_size_t max_block(struct rt_small_mem *heap)
{
    struct rt_small_mem_item *mem;
    rt_size_t max = 0, size;

    for (mem = (struct rt_small_mem_item *)heap->heap_ptr;
         mem != heap->heap_end;
         mem = (struct rt_small_mem_item *)&heap->heap_ptr[mem->next])
    {
        if (((rt_ubase_t)mem->pool_ptr & 0x1) == 0)
        {
            size = MEM_SIZE(heap, mem);
            if (size > max)
            {
                max = size;
            }
        }
    }
    return max;
}

static int _mem_cmp(void *ptr, rt_uint8_t v, rt_size_t size)
{
    while (size-- != 0)
    {
        if (*(rt_uint8_t *)ptr != v)
            return *(rt_uint8_t *)ptr - v;
    }
    return 0;
}

struct mem_test_context
{
    void *ptr;
    rt_size_t size;
    rt_uint8_t magic;
};

static void mem_functional_test(void)
{
    rt_size_t total_size;
    rt_uint8_t *buf;
    struct rt_small_mem *heap;
    rt_uint8_t magic = __LINE__;

    /* Prepare test memory */
    buf = rt_malloc(TEST_MEM_SIZE);
    uassert_not_null(buf);
    uassert_int_equal(RT_ALIGN((rt_ubase_t)buf, RT_ALIGN_SIZE), (rt_ubase_t)buf);
    rt_memset(buf, 0xAA, TEST_MEM_SIZE);
    /* small heap init */
    heap = (struct rt_small_mem *)rt_smem_init("mem_tc", buf, TEST_MEM_SIZE);
    /* get total size */
    total_size = max_block(heap);
    uassert_int_not_equal(total_size, 0);
    /*
     * Allocate all memory at a time and test whether
     * the memory allocation release function is effective
     */
    {
        struct mem_test_context ctx;
        ctx.magic = magic++;
        ctx.size = max_block(heap);
        ctx.ptr = rt_smem_alloc(&heap->parent, ctx.size);
        uassert_not_null(ctx.ptr);
        rt_memset(ctx.ptr, ctx.magic, ctx.size);
        uassert_int_equal(_mem_cmp(ctx.ptr, ctx.magic, ctx.size), 0);
        rt_smem_free(ctx.ptr);
        uassert_int_equal(max_block(heap), total_size);
    }
    /*
     * Apply for memory release sequentially and
     * test whether memory block merging is effective
     */
    {
        rt_size_t i, max_free = 0;
        struct mem_test_context ctx[3];
        /* alloc mem */
        for (i = 0; i < sizeof(ctx) / sizeof(ctx[0]); i++)
        {
            ctx[i].magic = magic++;
            ctx[i].size = max_block(heap) / (sizeof(ctx) / sizeof(ctx[0]) - i);
            ctx[i].ptr = rt_smem_alloc(&heap->parent, ctx[i].size);
            uassert_not_null(ctx[i].ptr);
            rt_memset(ctx[i].ptr, ctx[i].magic, ctx[i].size);
        }
        /* All memory has been applied. The remaining memory should be 0 */
        uassert_int_equal(max_block(heap), 0);
        /* Verify that the memory data is correct */
        for (i = 0; i < sizeof(ctx) / sizeof(ctx[0]); i++)
        {
            uassert_int_equal(_mem_cmp(ctx[i].ptr, ctx[i].magic, ctx[i].size), 0);
        }
        /* Sequential memory release */
        for (i = 0; i < sizeof(ctx) / sizeof(ctx[0]); i++)
        {
            uassert_int_equal(_mem_cmp(ctx[i].ptr, ctx[i].magic, ctx[i].size), 0);
            rt_smem_free(ctx[i].ptr);
            max_free += ctx[i].size;
            uassert_true(max_block(heap) >= max_free);
        }
        /* Check whether the memory is fully merged */
        uassert_int_equal(max_block(heap), total_size);
    }
    /*
     * Apply for memory release at an interval to
     * test whether memory block merging is effective
     */
    {
        rt_size_t i, max_free = 0;
        struct mem_test_context ctx[3];
        /* alloc mem */
        for (i = 0; i < sizeof(ctx) / sizeof(ctx[0]); i++)
        {
            ctx[i].magic = magic++;
            ctx[i].size = max_block(heap) / (sizeof(ctx) / sizeof(ctx[0]) - i);
            ctx[i].ptr = rt_smem_alloc(&heap->parent, ctx[i].size);
            uassert_not_null(ctx[i].ptr);
            rt_memset(ctx[i].ptr, ctx[i].magic, ctx[i].size);
        }
        /* All memory has been applied. The remaining memory should be 0 */
        uassert_int_equal(max_block(heap), 0);
        /* Verify that the memory data is correct */
        for (i = 0; i < sizeof(ctx) / sizeof(ctx[0]); i++)
        {
            uassert_int_equal(_mem_cmp(ctx[i].ptr, ctx[i].magic, ctx[i].size), 0);
        }
        /* Release even address */
        for (i = 0; i < sizeof(ctx) / sizeof(ctx[0]); i++)
        {
            if (i % 2 == 0)
            {
                uassert_int_equal(_mem_cmp(ctx[i].ptr, ctx[i].magic, ctx[i].size), 0);
                rt_smem_free(ctx[i].ptr);
                uassert_true(max_block(heap) >= ctx[0].size);
            }
        }
        /* Release odd addresses and merge memory blocks */
        for (i = 0; i < sizeof(ctx) / sizeof(ctx[0]); i++)
        {
            if (i % 2 != 0)
            {
                uassert_int_equal(_mem_cmp(ctx[i].ptr, ctx[i].magic, ctx[i].size), 0);
                rt_smem_free(ctx[i].ptr);
                max_free += ctx[i - 1].size + ctx[i + 1].size;
                uassert_true(max_block(heap) >= max_free);
            }
        }
        /* Check whether the memory is fully merged */
        uassert_int_equal(max_block(heap), total_size);
    }
    /* mem realloc test,Small - > Large */
    {
        /* Request a piece of memory for subsequent reallocation operations */
        struct mem_test_context ctx[3];
        ctx[0].magic = magic++;
        ctx[0].size = max_block(heap) / 3;
        ctx[0].ptr = rt_smem_alloc(&heap->parent, ctx[0].size);
        uassert_not_null(ctx[0].ptr);
        rt_memset(ctx[0].ptr, ctx[0].magic, ctx[0].size);
        /* Apply for a small piece of memory and split the continuous memory */
        ctx[1].magic = magic++;
        ctx[1].size = RT_ALIGN_SIZE;
        ctx[1].ptr = rt_smem_alloc(&heap->parent, ctx[1].size);
        uassert_not_null(ctx[1].ptr);
        rt_memset(ctx[1].ptr, ctx[1].magic, ctx[1].size);
        /* Check whether the maximum memory block is larger than the first piece of memory */
        uassert_true(max_block(heap) > ctx[0].size);
        /* Reallocate the first piece of memory */
        ctx[2].magic = magic++;
        ctx[2].size = max_block(heap);
        ctx[2].ptr = rt_smem_realloc(&heap->parent, ctx[0].ptr, ctx[2].size);
        uassert_not_null(ctx[2].ptr);
        uassert_int_not_equal(ctx[0].ptr, ctx[2].ptr);
        uassert_int_equal(_mem_cmp(ctx[2].ptr, ctx[0].magic, ctx[0].size), 0);
        rt_memset(ctx[2].ptr, ctx[2].magic, ctx[2].size);
        /* Free the second piece of memory */
        uassert_int_equal(_mem_cmp(ctx[1].ptr, ctx[1].magic, ctx[1].size), 0);
        rt_smem_free(ctx[1].ptr);
        /* Free reallocated memory */
        uassert_int_equal(_mem_cmp(ctx[2].ptr, ctx[2].magic, ctx[2].size), 0);
        rt_smem_free(ctx[2].ptr);
        /* Check memory integrity */
        uassert_int_equal(max_block(heap), total_size);
    }
    /* mem realloc test,Large - > Small */
    {
        rt_size_t max_free;
        struct mem_test_context ctx;
        /* alloc a piece of memory */
        ctx.magic = magic++;
        ctx.size = max_block(heap) / 2;
        ctx.ptr = rt_smem_alloc(&heap->parent, ctx.size);
        uassert_not_null(ctx.ptr);
        rt_memset(ctx.ptr, ctx.magic, ctx.size);
        uassert_int_equal(_mem_cmp(ctx.ptr, ctx.magic, ctx.size), 0);
        /* Get remaining memory */
        max_free = max_block(heap);
        /* Change memory size */
        ctx.size = ctx.size / 2;
        uassert_int_equal((rt_ubase_t)rt_smem_realloc(&heap->parent, ctx.ptr, ctx.size), (rt_ubase_t)ctx.ptr);
        /* Get remaining size */
        uassert_true(max_block(heap) > max_free);
        /* Free memory */
        uassert_int_equal(_mem_cmp(ctx.ptr, ctx.magic, ctx.size), 0);
        rt_smem_free(ctx.ptr);
        /* Check memory integrity */
        uassert_int_equal(max_block(heap), total_size);
    }
    /* mem realloc test,equal */
    {
        rt_size_t max_free;
        struct mem_test_context ctx;
        /* alloc a piece of memory */
        ctx.magic = magic++;
        ctx.size = max_block(heap) / 2;
        ctx.ptr = rt_smem_alloc(&heap->parent, ctx.size);
        uassert_not_null(ctx.ptr);
        rt_memset(ctx.ptr, ctx.magic, ctx.size);
        uassert_int_equal(_mem_cmp(ctx.ptr, ctx.magic, ctx.size), 0);
        /* Get remaining memory */
        max_free = max_block(heap);
        /* Do not change memory size */
        uassert_int_equal((rt_ubase_t)rt_smem_realloc(&heap->parent, ctx.ptr, ctx.size), (rt_ubase_t)ctx.ptr);
        /* Get remaining size */
        uassert_true(max_block(heap) == max_free);
        /* Free memory */
        uassert_int_equal(_mem_cmp(ctx.ptr, ctx.magic, ctx.size), 0);
        rt_smem_free(ctx.ptr);
        /* Check memory integrity */
        uassert_int_equal(max_block(heap), total_size);
    }
    /* small heap deinit */
    rt_smem_detach(&heap->parent);
    /* release test resources */
    rt_free(buf);
}

struct mem_alloc_context
{
    rt_list_t node;
    rt_size_t size;
    rt_uint8_t magic;
};

struct mem_alloc_head
{
    rt_list_t list;
    rt_size_t count;
    rt_tick_t start;
    rt_tick_t end;
    rt_tick_t interval;
};

#define MEM_RANG_ALLOC_BLK_MIN  2
#define MEM_RANG_ALLOC_BLK_MAX  5
#define MEM_RANG_ALLOC_TEST_TIME 5

static void mem_alloc_test(void)
{
    struct mem_alloc_head head;
    rt_uint8_t *buf;
    struct rt_small_mem *heap;
    rt_size_t total_size, size;
    struct mem_alloc_context *ctx;

    /* init */
    rt_list_init(&head.list);
    head.count = 0;
    head.start = rt_tick_get();
    head.end = rt_tick_get() + rt_tick_from_millisecond(MEM_RANG_ALLOC_TEST_TIME * 1000);
    head.interval = (head.end - head.start) / 20;
    buf = rt_malloc(TEST_MEM_SIZE);
    uassert_not_null(buf);
    uassert_int_equal(RT_ALIGN((rt_ubase_t)buf, RT_ALIGN_SIZE), (rt_ubase_t)buf);
    rt_memset(buf, 0xAA, TEST_MEM_SIZE);
    heap =  (struct rt_small_mem *)rt_smem_init("mem_tc", buf, TEST_MEM_SIZE);
    total_size = max_block(heap);
    uassert_int_not_equal(total_size, 0);
    /* test run */
    while (head.end - head.start < RT_TICK_MAX / 2)
    {
        if (rt_tick_get() - head.start >= head.interval)
        {
            head.start = rt_tick_get();
            rt_kprintf("#");
        }
        /* %60 probability to perform alloc operation */
        if (rand() % 10 >= 4)
        {
            size = rand() % MEM_RANG_ALLOC_BLK_MAX + MEM_RANG_ALLOC_BLK_MIN;
            size *= sizeof(struct mem_alloc_context);
            ctx = rt_smem_alloc(&heap->parent, size);
            if (ctx == RT_NULL)
            {
                if (head.count == 0)
                {
                    break;
                }
                size = head.count / 2;
                while (size != head.count)
                {
                    ctx = rt_list_first_entry(&head.list, struct mem_alloc_context, node);
                    rt_list_remove(&ctx->node);
                    if (ctx->size > sizeof(*ctx))
                    {
                        if (_mem_cmp(&ctx[1], ctx->magic, ctx->size - sizeof(*ctx)) != 0)
                        {
                            uassert_true(0);
                        }
                    }
                    rt_memset(ctx, 0xAA, ctx->size);
                    rt_smem_free(ctx);
                    head.count --;
                }
                continue;
            }
            if (RT_ALIGN((rt_ubase_t)ctx, RT_ALIGN_SIZE) != (rt_ubase_t)ctx)
            {
                uassert_int_equal(RT_ALIGN((rt_ubase_t)ctx, RT_ALIGN_SIZE), (rt_ubase_t)ctx);
            }
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
                ctx = rt_list_first_entry(&head.list, struct mem_alloc_context, node);
                rt_list_remove(&ctx->node);
                if (ctx->size > sizeof(*ctx))
                {
                    if (_mem_cmp(&ctx[1], ctx->magic, ctx->size - sizeof(*ctx)) != 0)
                    {
                        uassert_true(0);
                    }
                }
                rt_memset(ctx, 0xAA, ctx->size);
                rt_smem_free(ctx);
                head.count --;
            }
        }
    }
    while (!rt_list_isempty(&head.list))
    {
        ctx = rt_list_first_entry(&head.list, struct mem_alloc_context, node);
        rt_list_remove(&ctx->node);
        if (ctx->size > sizeof(*ctx))
        {
            if (_mem_cmp(&ctx[1], ctx->magic, ctx->size - sizeof(*ctx)) != 0)
            {
                uassert_true(0);
            }
        }
        rt_memset(ctx, 0xAA, ctx->size);
        rt_smem_free(ctx);
        head.count --;
    }
    uassert_int_equal(head.count, 0);
    uassert_int_equal(max_block(heap), total_size);
    /* small heap deinit */
    rt_smem_detach(&heap->parent);
    /* release test resources */
    rt_free(buf);
}

#define MEM_RANG_REALLOC_BLK_MIN  0
#define MEM_RANG_REALLOC_BLK_MAX  5
#define MEM_RANG_REALLOC_TEST_TIME 5

struct mem_realloc_context
{
    rt_size_t size;
    rt_uint8_t magic;
};

struct mem_realloc_head
{
    struct mem_realloc_context **ctx_tab;
    rt_size_t count;
    rt_tick_t start;
    rt_tick_t end;
    rt_tick_t interval;
};

static void mem_realloc_test(void)
{
    struct mem_realloc_head head;
    rt_uint8_t *buf;
    struct rt_small_mem *heap;
    rt_size_t total_size, size, idx;
    struct mem_realloc_context *ctx;
    int res;

    size = RT_ALIGN(sizeof(struct mem_realloc_context), RT_ALIGN_SIZE) + RT_ALIGN_SIZE;
    size = TEST_MEM_SIZE / size;
    /* init */
    head.ctx_tab = RT_NULL;
    head.count = size;
    head.start = rt_tick_get();
    head.end = rt_tick_get() + rt_tick_from_millisecond(MEM_RANG_ALLOC_TEST_TIME * 1000);
    head.interval = (head.end - head.start) / 20;
    buf = rt_malloc(TEST_MEM_SIZE);
    uassert_not_null(buf);
    uassert_int_equal(RT_ALIGN((rt_ubase_t)buf, RT_ALIGN_SIZE), (rt_ubase_t)buf);
    rt_memset(buf, 0xAA, TEST_MEM_SIZE);
    heap =  (struct rt_small_mem *)rt_smem_init("mem_tc", buf, TEST_MEM_SIZE);
    total_size = max_block(heap);
    uassert_int_not_equal(total_size, 0);
    /* init ctx tab */
    size = head.count * sizeof(struct mem_realloc_context *);
    head.ctx_tab = rt_smem_alloc(&heap->parent, size);
    uassert_not_null(head.ctx_tab);
    rt_memset(head.ctx_tab, 0, size);
    /* test run */
    while (head.end - head.start < RT_TICK_MAX / 2)
    {
        if (rt_tick_get() - head.start >= head.interval)
        {
            head.start = rt_tick_get();
            rt_kprintf("#");
        }
        size = rand() % MEM_RANG_ALLOC_BLK_MAX + MEM_RANG_ALLOC_BLK_MIN;
        size *= sizeof(struct mem_realloc_context);
        idx = rand() % head.count;
        ctx = rt_smem_realloc(&heap->parent, head.ctx_tab[idx], size);
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
                        rt_smem_realloc(&heap->parent, ctx, 0);
                        head.ctx_tab[idx] = RT_NULL;
                    }
                }
            }
            continue;
        }
        /* check mem */
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
        /* init mem */
        ctx->magic = rand() & 0xff;
        ctx->size = size;
        if (ctx->size > sizeof(*ctx))
        {
            rt_memset(&ctx[1], ctx->magic, ctx->size - sizeof(*ctx));
        }
        head.ctx_tab[idx] = ctx;
    }
    /* free all mem */
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
        rt_smem_realloc(&heap->parent, ctx, 0);
        head.ctx_tab[idx] = RT_NULL;
    }
    uassert_int_not_equal(max_block(heap), total_size);
    /* small heap deinit */
    rt_smem_detach(&heap->parent);
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
    UTEST_UNIT_RUN(mem_functional_test);
    UTEST_UNIT_RUN(mem_alloc_test);
    UTEST_UNIT_RUN(mem_realloc_test);
}
UTEST_TC_EXPORT(testcase, "testcases.kernel.mem_tc", utest_tc_init, utest_tc_cleanup, 20);
