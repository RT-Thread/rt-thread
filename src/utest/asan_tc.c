/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-30     RT-Thread    the first version
 */

/**
 * Test Case Name: AddressSanitizer Heap Detection Test
 *
 * Test Objectives:
 * - Verify the runtime AddressSanitizer (kernel-address) detects heap memory
 *   violations on real targets
 * - Verify heap-buffer-overflow (read/write), use-after-free (read/write) and
 *   realloc overflow are reported
 * - Verify normal in-bounds accesses do not raise false positives
 *
 * Test Scenarios:
 * - **Scenario 1 (Heap Overflow Write / test_asan_overflow_write):**
 *   1. Allocate a 10-byte block (redzone includes [10, 16))
 *   2. Write at offset 12 which falls into the poisoned redzone
 *   3. Assert the ASan report counter increased
 * - **Scenario 2 (Heap Overflow Read / test_asan_overflow_read):**
 *   1. Allocate a 10-byte block
 *   2. Read at offset 12 inside the poisoned redzone
 *   3. Assert the ASan report counter increased
 * - **Scenario 3 (No False Positive / test_asan_no_false_positive):**
 *   1. Allocate a 10-byte block
 *   2. Write to in-bounds offsets 0 and 9
 *   3. Assert the ASan report counter did not change
 * - **Scenario 4 (Realloc Overflow / test_asan_realloc_overflow):**
 *   1. Allocate 10 bytes and realloc to 20 bytes (redzone includes [20, 24))
 *   2. Write at offset 22 inside the new poisoned redzone
 *   3. Assert the ASan report counter increased
 * - **Scenario 5 (Use-After-Free Read / test_asan_uaf_read):**
 *   (only when RT_ASAN_HAS_UAF_DETECTION is enabled)
 *   1. Allocate and free a block
 *   2. Read from the freed block
 *   3. Assert the ASan report counter increased
 * - **Scenario 6 (Use-After-Free Write / test_asan_uaf_write):**
 *   (only when RT_ASAN_HAS_UAF_DETECTION is enabled)
 *   1. Allocate and free a block
 *   2. Write to the freed block
 *   3. Assert the ASan report counter increased
 *
 * Verification Metrics:
 * - Overflow/UAF accesses increase rt_asan_report_count_get()
 * - In-bounds accesses leave the counter unchanged
 *
 * Dependencies:
 * - RT_USING_ASAN enabled
 * - Heap-based dynamic memory (rt_malloc/rt_free/rt_realloc)
 *
 * Expected Results:
 * - All enabled scenarios pass without assertion failures
 */

#include <rtthread.h>
#include "utest.h"
#include "asan.h"

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void test_asan_overflow_write(void)
{
    rt_uint32_t before;
    rt_uint32_t after;
    volatile char *p;

    p = (char *)rt_malloc(10);
    uassert_not_null(p);
    if (!p)
    {
        return;
    }

    before = rt_asan_report_count_get();
    p[12] = 0x41;   /* heap-buffer-overflow write (redzone [10, 16)) */
    after = rt_asan_report_count_get();

    rt_free((void *)p);

    uassert_true(after > before);
}

static void test_asan_overflow_read(void)
{
    rt_uint32_t before;
    rt_uint32_t after;
    volatile char v;
    volatile char *p;

    p = (char *)rt_malloc(10);
    uassert_not_null(p);
    if (!p)
    {
        return;
    }

    before = rt_asan_report_count_get();
    v = p[12];   /* heap-buffer-overflow read (redzone [10, 16)) */
    after = rt_asan_report_count_get();

    (void)v;
    rt_free((void *)p);

    uassert_true(after > before);
}

static void test_asan_no_false_positive(void)
{
    rt_uint32_t before;
    rt_uint32_t after;
    volatile char *p;

    p = (char *)rt_malloc(10);
    uassert_not_null(p);
    if (!p)
    {
        return;
    }

    before = rt_asan_report_count_get();
    p[0] = 0x01;   /* first in-bounds byte */
    p[9] = 0x02;   /* last in-bounds byte */
    after = rt_asan_report_count_get();

    rt_free((void *)p);

    uassert_int_equal(after, before);
}

static void test_asan_realloc_overflow(void)
{
    rt_uint32_t before;
    rt_uint32_t after;
    volatile char *p;
    volatile char *q;

    p = (char *)rt_malloc(10);
    uassert_not_null(p);
    if (!p)
    {
        return;
    }

    q = (char *)rt_realloc((void *)p, 20);
    uassert_not_null(q);
    if (!q)
    {
        rt_free((void *)p);
        return;
    }

    before = rt_asan_report_count_get();
    q[22] = 0x41;   /* heap-buffer-overflow write (redzone [20, 24)) */
    after = rt_asan_report_count_get();

    rt_free((void *)q);

    uassert_true(after > before);
}

#if RT_ASAN_HAS_UAF_DETECTION
static void test_asan_uaf_read(void)
{
    rt_uint32_t before;
    rt_uint32_t after;
    volatile char v;
    volatile char *p;

    p = (char *)rt_malloc(10);
    uassert_not_null(p);
    if (!p)
    {
        return;
    }

    rt_free((void *)p);

    before = rt_asan_report_count_get();
    v = p[0];   /* use-after-free read */
    after = rt_asan_report_count_get();

    (void)v;

    uassert_true(after > before);
}

static void test_asan_uaf_write(void)
{
    rt_uint32_t before;
    rt_uint32_t after;
    volatile char *p;

    p = (char *)rt_malloc(10);
    uassert_not_null(p);
    if (!p)
    {
        return;
    }

    rt_free((void *)p);

    before = rt_asan_report_count_get();
    p[0] = 0x41;   /* use-after-free write */
    after = rt_asan_report_count_get();

    uassert_true(after > before);
}
#endif /* RT_ASAN_HAS_UAF_DETECTION */

/* Aligned requests must have a redzone too; exercise every partial granule. */
static void test_asan_boundaries(void)
{
    rt_size_t size;
    for (size = 1; size <= 32; size++)
    {
        volatile char *p = (char *)rt_malloc(size);
        rt_uint32_t before;
        volatile char value;
        uassert_not_null(p);
        if (!p)
        {
            return;
        }
        uassert_true(((rt_uintptr_t)p & (RT_ALIGN_SIZE - 1)) == 0);
        before = rt_asan_report_count_get();
        p[0] = 1;
        p[size - 1] = 2;
        uassert_int_equal(rt_asan_report_count_get(), before);
        value = p[size];
        RT_UNUSED(value);
        uassert_true(rt_asan_report_count_get() > before);
        before = rt_asan_report_count_get();
        p[size] = 3;
        uassert_true(rt_asan_report_count_get() > before);
        rt_free((void *)p);
    }
}

static void test_asan_aligned_boundaries(void)
{
    static const rt_size_t sizes[] = { 1, 8, 13, 16, 31, 32 };
    static const rt_size_t aligns[] = { sizeof(void *), 16, 64, 256 };
    rt_size_t i;
    rt_size_t j;

    for (i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++)
    {
        for (j = 0; j < sizeof(aligns) / sizeof(aligns[0]); j++)
        {
            rt_uint32_t before = rt_asan_report_count_get();
            volatile char *p = (char *)rt_malloc_align(sizes[i], aligns[j]);
            volatile char value;
            uassert_not_null(p);
            if (!p)
            {
                return;
            }
            uassert_true(((rt_uintptr_t)p & (aligns[j] - 1)) == 0);
            p[0] = 1;
            p[sizes[i] - 1] = 2;
            uassert_int_equal(rt_asan_report_count_get(), before);
            value = p[sizes[i]];
            uassert_int_equal(rt_asan_report_count_get(), before + 1);
            p[sizes[i]] = 3;
            uassert_int_equal(rt_asan_report_count_get(), before + 2);
            /* Read the left redzone without corrupting the allocation header. */
            value = p[-1];
            RT_UNUSED(value);
            uassert_int_equal(rt_asan_report_count_get(), before + 3);
            before = rt_asan_report_count_get();
            rt_free_align((void *)p);
            uassert_int_equal(rt_asan_report_count_get(), before);
        }
    }
}

#if RT_ASAN_HAS_UAF_DETECTION
static void test_asan_aligned_uaf(void)
{
    volatile char *p = (char *)rt_malloc_align(13, 64);
    volatile char value;
    rt_uint32_t before;

    uassert_not_null(p);
    if (!p)
    {
        return;
    }
    rt_free_align((void *)p);
    before = rt_asan_report_count_get();
    value = p[0];
    RT_UNUSED(value);
    uassert_int_equal(rt_asan_report_count_get(), before + 1);
    p[12] = 1;
    uassert_int_equal(rt_asan_report_count_get(), before + 2);
}
#endif

static void test_asan_realloc_lifecycle(void)
{
    volatile char *p = (char *)rt_realloc(RT_NULL, 13);
    volatile char *q;
    rt_uint32_t before = rt_asan_report_count_get();
    rt_size_t i;

    uassert_not_null(p);
    if (!p)
    {
        return;
    }
    for (i = 0; i < 13; i++)
    {
        p[i] = (char)i;
    }
    q = (char *)rt_realloc((void *)p, 64);
    uassert_not_null(q);
    if (!q)
    {
        rt_free((void *)p);
        return;
    }
    for (i = 0; i < 13; i++)
    {
        uassert_int_equal(q[i], (char)i);
    }
    uassert_int_equal(rt_asan_report_count_get(), before);
    p = (char *)rt_realloc((void *)q, 16);
    uassert_true(p == q);
    before = rt_asan_report_count_get();
    p[16] = 1;
    uassert_true(rt_asan_report_count_get() > before);
    before = rt_asan_report_count_get();
    p = (char *)rt_realloc((void *)q, 32);
    uassert_true(p == q);
    p[31] = 7;
    uassert_null(rt_realloc((void *)p, (rt_size_t)-1));
    uassert_int_equal(p[31], 7);
    uassert_int_equal(rt_asan_report_count_get(), before);
    uassert_null(rt_realloc((void *)p, 0));
#if RT_ASAN_HAS_UAF_DETECTION
    before = rt_asan_report_count_get();
    {
        volatile char value = p[0];
        RT_UNUSED(value);
    }
    uassert_true(rt_asan_report_count_get() > before);
#endif
    uassert_null(rt_malloc((rt_size_t)-1));
    uassert_null(rt_malloc((rt_size_t)-16));
    uassert_null(rt_malloc((rt_size_t)-64));
    uassert_null(rt_calloc((rt_size_t)-1 / 2 + 1, 2));
    uassert_null(rt_realloc(RT_NULL, 0));
    rt_free(RT_NULL);
}

/* Run with RT_ASAN_TRACK_MAX=1 as well: correctness must not need a free slot. */
static void test_asan_calloc_reuse(void)
{
    rt_size_t i;
    rt_uint32_t before = rt_asan_report_count_get();
    for (i = 0; i < 64; i++)
    {
        char *p = (char *)rt_calloc(3, 5);
        uassert_not_null(p);
        if (!p)
        {
            return;
        }
        uassert_int_equal(p[0], 0);
        uassert_int_equal(p[14], 0);
        rt_free(p);
    }
    uassert_int_equal(rt_asan_report_count_get(), before);
}

#ifdef RT_USING_SEMAPHORE
static struct rt_semaphore asan_done;
static rt_uint32_t asan_worker_errors[2];

static void asan_worker(void *parameter)
{
    rt_size_t id = (rt_size_t)parameter;
    rt_size_t i;
    for (i = 0; i < 200; i++)
    {
        rt_size_t size = i % 63 + 1;
        char *p = (char *)rt_malloc(size);
        char *q;
        if (!p)
        {
            asan_worker_errors[id]++;
            break;
        }
        rt_memset(p, (int)(id + 1), size);
        /* Let the creator start both workers even if it has lower priority. */
        rt_thread_mdelay(1);
        q = (char *)rt_realloc(p, 96);
        if (!q)
        {
            rt_free(p);
            asan_worker_errors[id]++;
            break;
        }
        if (q[0] != (char)(id + 1) || q[size - 1] != (char)(id + 1))
        {
            asan_worker_errors[id]++;
        }
        rt_thread_yield();
        p = (char *)rt_realloc(q, 1);
        if (p != q || p[0] != (char)(id + 1))
        {
            asan_worker_errors[id]++;
        }
        rt_free(p);
        p = (char *)rt_malloc_align(size, 64);
        if (!p)
        {
            asan_worker_errors[id]++;
            break;
        }
        rt_thread_yield();
        p[0] = (char)(id + 1);
        p[size - 1] = (char)(id + 1);
        rt_free_align(p);
    }
    rt_sem_release(&asan_done);
}

static void test_asan_concurrent_realloc(void)
{
    rt_thread_t threads[2];
    rt_size_t i;
    rt_size_t started = 0;
    rt_uint32_t before = rt_asan_report_count_get();

    rt_sem_init(&asan_done, "asan_done", 0, RT_IPC_FLAG_PRIO);
    for (i = 0; i < 2; i++)
    {
        asan_worker_errors[i] = 0;
        threads[i] = rt_thread_create("asan_work", asan_worker, (void *)i, 2048,
                                      RT_THREAD_PRIORITY_MAX / 2, 1);
        uassert_not_null(threads[i]);
        if (threads[i])
        {
#ifdef RT_USING_SMP
            rt_thread_control(threads[i], RT_THREAD_CTRL_BIND_CPU, (void *)(i % RT_CPUS_NR));
#endif
            rt_thread_startup(threads[i]);
            started++;
        }
    }
    for (i = 0; i < started; i++)
    {
        rt_sem_take(&asan_done, RT_WAITING_FOREVER);
    }
    rt_sem_detach(&asan_done);
    uassert_int_equal(asan_worker_errors[0], 0);
    uassert_int_equal(asan_worker_errors[1], 0);
    uassert_int_equal(rt_asan_report_count_get(), before);
}
#endif

#ifdef RT_USING_CPLUSPLUS
extern void test_asan_cpp(void);
#endif

extern rt_base_t rt_heap_lock(void);
extern void rt_heap_unlock(rt_base_t level);

/* Statistics and page APIs must use the heap owned by the overriding adapter. */
static void test_asan_heap_adapter(void)
{
    rt_size_t total = 0, used = 0, maximum = 0;
    rt_uint32_t before = rt_asan_report_count_get();
    void *p = rt_malloc(64);
    rt_base_t level = rt_heap_lock();

    rt_heap_unlock(level);

    uassert_not_null(p);
    rt_memory_info(&total, &used, &maximum);
    uassert_true(total > 0);
    uassert_true(used >= 64);
    uassert_true(maximum >= used);
    uassert_true(total >= used);
    rt_free(p);

#if defined(RT_USING_SLAB_AS_HEAP)
    p = rt_page_alloc(1);
    uassert_not_null(p);
    if (p)
    {
        uassert_true(((rt_uintptr_t)p & (RT_MM_PAGE_SIZE - 1)) == 0);
        rt_memset(p, 0x5a, RT_MM_PAGE_SIZE);
        rt_page_free(p, 1);
    }
#endif
    uassert_int_equal(rt_asan_report_count_get(), before);
}

#ifdef RT_HOOK_USING_FUNC_PTR
static rt_thread_t probe_thread;
static unsigned probe_malloc, probe_entry, probe_exit, probe_free;
static void *probe_old, *probe_new;
static void probe_alloc_hook(void **ptr, rt_size_t size)
{
    if (rt_thread_self() == probe_thread && *ptr && size == 37)
        probe_malloc++;
}
static void probe_entry_hook(void **ptr, rt_size_t size)
{
    if (rt_thread_self() == probe_thread && size == 73)
    {
        probe_old = *ptr;
        probe_entry++;
    }
}
static void probe_exit_hook(void **ptr, rt_size_t size)
{
    if (rt_thread_self() == probe_thread && size == 73)
    {
        probe_new = *ptr;
        probe_exit++;
    }
}
static void probe_free_hook(void **ptr)
{
    if (rt_thread_self() == probe_thread && *ptr == probe_new)
        probe_free++;
}
static void test_asan_hook_probe(void)
{
    void *p, *q;
    /* The public API has no getters. Leave application hooks untouched.
     * Run this unit without concurrent hook registration, just like other
     * tests which temporarily change global callbacks.
     */
    if (rt_asan_test_hooks_in_use())
    {
        rt_kprintf("[asan] hook test skipped: application hooks are installed\n");
        return;
    }
    probe_thread = rt_thread_self();
    probe_malloc = probe_entry = probe_exit = probe_free = 0;
    rt_malloc_sethook(probe_alloc_hook);
    rt_realloc_set_entry_hook(probe_entry_hook);
    rt_realloc_set_exit_hook(probe_exit_hook);
    rt_free_sethook(probe_free_hook);
    p = rt_malloc(37);
    q = rt_realloc(p, 73);
    rt_free(q ? q : p);
    rt_malloc_sethook(RT_NULL);
    rt_realloc_set_entry_hook(RT_NULL);
    rt_realloc_set_exit_hook(RT_NULL);
    rt_free_sethook(RT_NULL);
    uassert_false(rt_asan_test_hooks_in_use());
    uassert_not_null(p);
    uassert_not_null(q);
    uassert_true(probe_old == p);
    uassert_true(probe_new == q);
    uassert_int_equal(probe_malloc, 1);
    uassert_int_equal(probe_entry, 1);
    uassert_int_equal(probe_exit, 1);
    uassert_int_equal(probe_free, 1);
}
#endif

/* utest_unit_run resets its counters; retain failures from every unit. */
#define ASAN_UNIT_RUN(unit)                         \
    do                                              \
    {                                               \
        UTEST_UNIT_RUN(unit);                       \
        failures += utest_handle_get()->failed_num; \
    } while (0)

static void testcase(void)
{
    rt_size_t failures = 0;
#ifdef RT_HOOK_USING_FUNC_PTR
    ASAN_UNIT_RUN(test_asan_hook_probe);
#endif
    ASAN_UNIT_RUN(test_asan_heap_adapter);
    ASAN_UNIT_RUN(test_asan_overflow_write);
    ASAN_UNIT_RUN(test_asan_overflow_read);
    ASAN_UNIT_RUN(test_asan_no_false_positive);
    ASAN_UNIT_RUN(test_asan_realloc_overflow);
    ASAN_UNIT_RUN(test_asan_boundaries);
    ASAN_UNIT_RUN(test_asan_aligned_boundaries);
    ASAN_UNIT_RUN(test_asan_realloc_lifecycle);
    ASAN_UNIT_RUN(test_asan_calloc_reuse);
#ifdef RT_USING_SEMAPHORE
    ASAN_UNIT_RUN(test_asan_concurrent_realloc);
#endif
#ifdef RT_USING_CPLUSPLUS
    ASAN_UNIT_RUN(test_asan_cpp);
#endif
#if RT_ASAN_HAS_UAF_DETECTION
    ASAN_UNIT_RUN(test_asan_aligned_uaf);
    ASAN_UNIT_RUN(test_asan_uaf_read);
    ASAN_UNIT_RUN(test_asan_uaf_write);
#endif
    uassert_int_equal(failures, 0);
}
#undef ASAN_UNIT_RUN

UTEST_TC_EXPORT(testcase, "components.asan_tc", utest_tc_init, utest_tc_cleanup, 1000);
