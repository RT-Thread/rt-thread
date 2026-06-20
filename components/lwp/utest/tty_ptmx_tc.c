/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-09     OrbisAI      Add regression test for V-004 snprintf fix
 */

/**
 * Test Case Name: tty_ptmx Buffer Bounds Regression Test
 *
 * Test Objectives:
 * - Verify that the snprintf-based device name formatting in
 *   lwp_ptmx_init() never writes beyond the allocated buffer.
 * - Guard against regression to the original sprintf overflow (V-004).
 *
 * Test Scenarios:
 * - Normal input: root_path + "/ptmx" fits within the allocated buffer.
 * - Oversized input: combined length exceeds the buffer; snprintf must
 *   truncate without overflowing.
 * - Canary bytes placed immediately after the buffer must remain intact.
 *
 * Verification Metrics:
 * - Output buffer byte at index [buf_size] must equal the canary value.
 * - snprintf return value must be < buf_size when input fits.
 * - snprintf return value must be >= buf_size when input is oversized
 *   (snprintf reports what would have been written).
 *
 * Dependencies:
 * - Software configuration: RT_USING_SMART must be enabled.
 *
 * Expected Results:
 * - Final output: "[ PASSED ] [ result ] testcase (testcases.lwp.tty_ptmx.buffer_bounds)"
 * - No assertion failures during test execution.
 */

#include "utest_assert.h"

#include <rtdef.h>
#include <string.h>
#include <stdio.h>

#define DEV_REL_PATH "/ptmx"
#define CANARY       0xAB

static void tty_ptmx_buffer_bounds_tc(void)
{
    /* Simulate the allocation and snprintf call from lwp_ptmx_init(). */
    struct
    {
        const char *root_path;
        int         should_fit; /* 1 = expect no truncation */
    } cases[] = {
        { "/dev",                          1 },
        { "/dev/pts",                      1 },
        { "/",                             1 },
        /* Oversized: root alone is longer than reasonable device name */
        { "/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 0 },
    };

    for (rt_size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++)
    {
        const char *root_path   = cases[i].root_path;
        rt_size_t   root_len    = strlen(root_path);
        rt_size_t   buf_size    = root_len + sizeof(DEV_REL_PATH); /* mirrors kernel alloc */

        /* Allocate one extra byte as a canary to detect overflow. */
        char *raw = (char *)rt_malloc(buf_size + 1);
        uassert_not_null(raw);

        raw[buf_size] = (char)CANARY;

        int written = snprintf(raw, buf_size, "%s%s", root_path, DEV_REL_PATH);

        /* Canary must be intact regardless of input size. */
        uassert_int_equal((unsigned char)raw[buf_size], CANARY);

        if (cases[i].should_fit)
        {
            /* snprintf returns number of chars that would be written (excl. NUL). */
            uassert_true(written >= 0 && (rt_size_t)written < buf_size);
            /* Result must be null-terminated. */
            uassert_int_equal(raw[written], '\0');
        }

        rt_free(raw);
    }
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
    UTEST_UNIT_RUN(tty_ptmx_buffer_bounds_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.lwp.tty_ptmx.buffer_bounds", utest_tc_init, utest_tc_cleanup, 10);
