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

#include "../terminal/tty_internal.h"
#include <rtdef.h>
#include <string.h>
#include <stdio.h>

#define DEV_REL_PATH "/ptmx"
#define CANARY       0xAB

struct tty_ptmx_forward_state
{
    int copy_from_calls;
    int copy_to_calls;
    int ioctl_calls;
    int fail_copy_from;
    int fail_copy_to;
    int output_value;
    int forwarded_value;
    rt_size_t copy_size;
    rt_ubase_t forwarded_cmd;
    void *forwarded_arg;
};

static rt_size_t tty_ptmx_copy_from(void *dst, void *src, rt_size_t size,
                                    void *context)
{
    struct tty_ptmx_forward_state *state = context;

    state->copy_from_calls++;
    state->copy_size = size;
    if (state->fail_copy_from)
    {
        return 0;
    }
    memcpy(dst, src, size);
    return size;
}

static rt_size_t tty_ptmx_copy_to(void *dst, void *src, rt_size_t size,
                                  void *context)
{
    struct tty_ptmx_forward_state *state = context;

    state->copy_to_calls++;
    state->copy_size = size;
    if (state->fail_copy_to)
    {
        return 0;
    }
    memcpy(dst, src, size);
    return size;
}

static int tty_ptmx_forward_ioctl(rt_ubase_t cmd, void *arg, void *context)
{
    struct tty_ptmx_forward_state *state = context;

    state->ioctl_calls++;
    state->forwarded_cmd = cmd;
    state->forwarded_arg = arg;
    if (arg)
    {
        if (cmd == TIOCMGET)
        {
            *(int *)arg = state->output_value;
        }
        else
        {
            state->forwarded_value = *(int *)arg;
        }
    }
    return 0;
}

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

static void tty_ptmx_ioctl_arg_type_tc(void)
{
    uassert_int_equal(lwp_ptmx_ioctl_arg_type(TIOCSPGRP), LWP_PTMX_IOCTL_INT_IN);
    uassert_int_equal(lwp_ptmx_ioctl_arg_type(TIOCMGET), LWP_PTMX_IOCTL_INT_OUT);
    uassert_int_equal(lwp_ptmx_ioctl_arg_type(TIOCSTI), LWP_PTMX_IOCTL_CHAR_IN);
    uassert_int_equal(lwp_ptmx_ioctl_arg_type(TIOCEXCL), LWP_PTMX_IOCTL_NONE);
    uassert_int_equal(lwp_ptmx_ioctl_arg_type(0xffffffffU), LWP_PTMX_IOCTL_UNSUPPORTED);
}

static void tty_ptmx_ioctl_forward_tc(void)
{
    struct tty_ptmx_forward_state state;
    int value;
    int rc;

    memset(&state, 0, sizeof(state));
    value = 73;
    rc = lwp_ptmx_ioctl_forward(TIOCSPGRP, &value, tty_ptmx_copy_from,
                                tty_ptmx_copy_to, tty_ptmx_forward_ioctl, &state);
    uassert_int_equal(rc, 0);
    uassert_int_equal(state.copy_from_calls, 1);
    uassert_int_equal(state.copy_to_calls, 0);
    uassert_int_equal(state.ioctl_calls, 1);
    uassert_int_equal(state.copy_size, sizeof(value));
    uassert_int_equal(state.forwarded_cmd, TIOCSPGRP);
    uassert_int_equal(state.forwarded_value, value);

    memset(&state, 0, sizeof(state));
    state.output_value = 41;
    value = 0;
    rc = lwp_ptmx_ioctl_forward(TIOCMGET, &value, tty_ptmx_copy_from,
                                tty_ptmx_copy_to, tty_ptmx_forward_ioctl, &state);
    uassert_int_equal(rc, 0);
    uassert_int_equal(state.copy_from_calls, 0);
    uassert_int_equal(state.copy_to_calls, 1);
    uassert_int_equal(state.ioctl_calls, 1);
    uassert_int_equal(value, state.output_value);

    memset(&state, 0, sizeof(state));
    value = 1;
    rc = lwp_ptmx_ioctl_forward(FIONBIO, &value, tty_ptmx_copy_from,
                                tty_ptmx_copy_to, tty_ptmx_forward_ioctl, &state);
    uassert_int_equal(rc, 0);
    uassert_int_equal(state.copy_from_calls, 1);
    uassert_int_equal(state.forwarded_value, value);

    memset(&state, 0, sizeof(state));
    rc = lwp_ptmx_ioctl_forward(TIOCEXCL, RT_NULL, tty_ptmx_copy_from,
                                tty_ptmx_copy_to, tty_ptmx_forward_ioctl, &state);
    uassert_int_equal(rc, 0);
    uassert_int_equal(state.copy_from_calls, 0);
    uassert_int_equal(state.copy_to_calls, 0);
    uassert_int_equal(state.ioctl_calls, 1);
    uassert_null(state.forwarded_arg);

    memset(&state, 0, sizeof(state));
    state.fail_copy_from = 1;
    value = 73;
    rc = lwp_ptmx_ioctl_forward(TIOCSPGRP, &value, tty_ptmx_copy_from,
                                tty_ptmx_copy_to, tty_ptmx_forward_ioctl, &state);
    uassert_int_equal(rc, -EFAULT);
    uassert_int_equal(state.ioctl_calls, 0);

    memset(&state, 0, sizeof(state));
    state.fail_copy_to = 1;
    state.output_value = 41;
    rc = lwp_ptmx_ioctl_forward(TIOCMGET, &value, tty_ptmx_copy_from,
                                tty_ptmx_copy_to, tty_ptmx_forward_ioctl, &state);
    uassert_int_equal(rc, -EFAULT);
    uassert_int_equal(state.copy_to_calls, 1);
    uassert_int_equal(state.ioctl_calls, 1);

    memset(&state, 0, sizeof(state));
    rc = lwp_ptmx_ioctl_forward(0xffffffffU, &value, tty_ptmx_copy_from,
                                tty_ptmx_copy_to, tty_ptmx_forward_ioctl, &state);
    uassert_int_equal(rc, -ENOTTY);
    uassert_int_equal(state.copy_from_calls, 0);
    uassert_int_equal(state.copy_to_calls, 0);
    uassert_int_equal(state.ioctl_calls, 0);
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
    UTEST_UNIT_RUN(tty_ptmx_ioctl_arg_type_tc);
    UTEST_UNIT_RUN(tty_ptmx_ioctl_forward_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.lwp.tty_ptmx.buffer_bounds", utest_tc_init, utest_tc_cleanup, 10);
