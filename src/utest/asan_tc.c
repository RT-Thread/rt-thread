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
 *   1. Allocate a 10-byte block (redzone occupies [10, 16))
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
 *   1. Allocate 10 bytes and realloc to 20 bytes (redzone occupies [20, 24))
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
    char *p;

    p = (char *)rt_malloc(10);
    uassert_not_null(p);
    if (!p)
    {
        return;
    }

    before = rt_asan_report_count_get();
    p[12] = 0x41;   /* heap-buffer-overflow write (redzone [10, 16)) */
    after = rt_asan_report_count_get();

    rt_free(p);

    uassert_true(after > before);
}

static void test_asan_overflow_read(void)
{
    rt_uint32_t before;
    rt_uint32_t after;
    volatile char v;
    char *p;

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
    rt_free(p);

    uassert_true(after > before);
}

static void test_asan_no_false_positive(void)
{
    rt_uint32_t before;
    rt_uint32_t after;
    char *p;

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

    rt_free(p);

    uassert_int_equal(after, before);
}

static void test_asan_realloc_overflow(void)
{
    rt_uint32_t before;
    rt_uint32_t after;
    char *p;
    char *q;

    p = (char *)rt_malloc(10);
    uassert_not_null(p);
    if (!p)
    {
        return;
    }

    q = (char *)rt_realloc(p, 20);
    uassert_not_null(q);
    if (!q)
    {
        rt_free(p);
        return;
    }

    before = rt_asan_report_count_get();
    q[22] = 0x41;   /* heap-buffer-overflow write (redzone [20, 24)) */
    after = rt_asan_report_count_get();

    rt_free(q);

    uassert_true(after > before);
}

#if RT_ASAN_HAS_UAF_DETECTION
static void test_asan_uaf_read(void)
{
    rt_uint32_t before;
    rt_uint32_t after;
    volatile char v;
    char *p;

    p = (char *)rt_malloc(10);
    uassert_not_null(p);
    if (!p)
    {
        return;
    }

    rt_free(p);

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
    char *p;

    p = (char *)rt_malloc(10);
    uassert_not_null(p);
    if (!p)
    {
        return;
    }

    rt_free(p);

    before = rt_asan_report_count_get();
    p[0] = 0x41;   /* use-after-free write */
    after = rt_asan_report_count_get();

    uassert_true(after > before);
}
#endif /* RT_ASAN_HAS_UAF_DETECTION */

static void testcase(void)
{
    UTEST_UNIT_RUN(test_asan_overflow_write);
    UTEST_UNIT_RUN(test_asan_overflow_read);
    UTEST_UNIT_RUN(test_asan_no_false_positive);
    UTEST_UNIT_RUN(test_asan_realloc_overflow);
#if RT_ASAN_HAS_UAF_DETECTION
    UTEST_UNIT_RUN(test_asan_uaf_read);
    UTEST_UNIT_RUN(test_asan_uaf_write);
#endif
}

UTEST_TC_EXPORT(testcase, "components.asan_tc", utest_tc_init, utest_tc_cleanup, 1000);
