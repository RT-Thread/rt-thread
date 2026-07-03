/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author             Notes
 * 2026-07-03     Geek_simple        add rt_strcmp and rt_strncmp regression tests
 */

#include <rtklibc.h>
#include <utest.h>

static void TC_rt_strcmp_unsigned_char_order(void)
{
    const char high[] = {(char)0x80, '\0'};
    const char low[] = {(char)0x01, '\0'};
    const char max_byte[] = {(char)0xFF, '\0'};
    const char ascii_high[] = {(char)0x7F, '\0'};

    /* strcmp compares bytes as unsigned char, so 0x80 and 0xFF are greater. */
    uassert_value_greater(rt_strcmp(high, low), 0);
    uassert_value_less(rt_strcmp(low, high), 0);
    uassert_value_greater(rt_strcmp(max_byte, ascii_high), 0);
}

static void TC_rt_strncmp_unsigned_char_order(void)
{
    const char high_first[] = {(char)0xC8, 'Z', '\0'};
    const char low_first[] = {(char)0x01, 'Z', '\0'};
    const char max_byte[] = {(char)0xFF, '\0'};
    const char ascii_high[] = {(char)0x7F, '\0'};

    /* strncmp also compares the first different byte as unsigned char. */
    uassert_value_greater(rt_strncmp(high_first, low_first, 2), 0);
    uassert_value_less(rt_strncmp(low_first, high_first, 2), 0);
    uassert_value_greater(rt_strncmp(max_byte, ascii_high, 1), 0);
}

static void TC_rt_strncmp_count_zero(void)
{
    const char high[] = {(char)0x80, '\0'};
    const char low[] = {(char)0x01, '\0'};

    uassert_int_equal(rt_strncmp(high, low, 0), 0);
}

static void utest_do_tc(void)
{
    UTEST_UNIT_RUN(TC_rt_strcmp_unsigned_char_order);
    UTEST_UNIT_RUN(TC_rt_strncmp_unsigned_char_order);
    UTEST_UNIT_RUN(TC_rt_strncmp_count_zero);
}

UTEST_TC_EXPORT(utest_do_tc, "core.klibc.rt_strcmp", RT_NULL, RT_NULL, 1000);
