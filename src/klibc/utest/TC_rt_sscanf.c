/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-04     Meco Man     the first version
 */

#include <rtklibc.h>
#include "utest.h"

static void TC_rt_sscanf_char(void)
{
    const char str[] = "A B";
    char a, b;
    rt_sscanf(str, "%c %c", &a, &b);
    uassert_true(a == 'A' && b == 'B');
    /* Move to the next character after space for the second %c */
    rt_sscanf(str + 2, "%c", &b);
    uassert_true(b == 'B');
}

static void TC_rt_sscanf_basic_int(void)
{
    const char str[] = "12345";
    int value;
    int result = rt_sscanf(str, "%d", &value);
    uassert_int_equal(result, 1);
    uassert_int_equal(value, 12345);
}

static void TC_rt_sscanf_basic_float(void)
{
    const char str[] = "123.45";
    float value;
    int result = rt_sscanf(str, "%f", &value);
    uassert_int_equal(result, 1);
    uassert_float_equal(value, 123.45);
}

static void TC_rt_sscanf_basic_string(void)
{
    const char str[] = "Hello, World!";
    char buffer[20];
    int result = rt_sscanf(str, "%s", buffer);
    uassert_int_equal(result, 1);
    uassert_str_equal(buffer, "Hello,");
}

static void TC_rt_sscanf_string_with_space(void)
{
    const char str[] = "Hello   World";
    char a[20];
    rt_sscanf(str, "%*s %s", a);
    uassert_str_equal(a, "World");
}

static void TC_rt_sscanf_basic_char(void)
{
    const char str[] = "A";
    char value;
    int result = rt_sscanf(str, "%c", &value);
    uassert_int_equal(result, 1);
    uassert_int_equal(value, 'A');
}

static void TC_rt_sscanf_hex_1(void)
{
    const char str[] = "0x1A3F";
    int value;
    int result = rt_sscanf(str, "%x", &value);
    uassert_int_equal(result, 1);
    uassert_int_equal(value, 0x1A3F);
}

static void TC_rt_sscanf_hex_2(void)
{
    const char str[] = "0x1A 0XFF";
    int a, b;
    rt_sscanf(str, "%x %x", &a, &b);
    uassert_true(a == 0x1A && b == 0XFF);
}

static void TC_rt_sscanf_oct_1(void)
{
    const char str[] = "0755";
    int value;
    int result = rt_sscanf(str, "%o", &value);
    uassert_int_equal(result, 1);
    uassert_int_equal(value, 0755);
}

static void TC_rt_sscanf_oct_2(void)
{
    const char str[] = "012 077";
    int a, b;
    rt_sscanf(str, "%o %o", &a, &b);
    uassert_true(a == 012 && b == 077);
}

static void TC_rt_sscanf_multiple_args(void)
{
    const char str[] = "123 Hello";
    int int_value;
    char str_value[20];
    int result = rt_sscanf(str, "%d %s", &int_value, str_value);
    uassert_int_equal(result, 2);
    uassert_int_equal(int_value, 123);
    uassert_str_equal(str_value, "Hello");
}

static void TC_rt_sscanf_pointer(void)
{
    const char str[] = "0x12345678";
    void *ptr;
    int result = rt_sscanf(str, "%p", &ptr);
    uassert_int_equal(result, 1);
    uassert_ptr_equal(ptr, (void *)0x12345678);
}

static void TC_rt_sscanf_width_specifier(void)
{
    const char str[] = "123456789";
    int value;
    int result = rt_sscanf(str, "%4d", &value);
    uassert_int_equal(result, 1);
    uassert_int_equal(value, 1234);
}

static void TC_rt_sscanf_suppression(void)
{
    const char str[] = "123 456";
    int second_value;
    int result = rt_sscanf(str, "%*d %d", &second_value);
    uassert_int_equal(result, 1);
    uassert_int_equal(second_value, 456);
}

static void TC_rt_sscanf_match_set(void)
{
    const char str[] = "abc123";
    char buffer[10] = {0};
    int result = rt_sscanf(str, "%[a-z]", buffer);
    uassert_int_equal(result, 1);
    uassert_str_equal(buffer, "abc");
}

static void TC_rt_sscanf_match_set_negated(void)
{
    const char str[] = "abc123";
    char buffer[10];
    int result = rt_sscanf(str, "%[^0-9]", buffer);
    uassert_int_equal(result, 1);
    uassert_str_equal(buffer, "abc");
}

static void TC_rt_sscanf_match_set_range(void)
{
    const char str[] = "a-zA-Z";
    char buffer[10];
    int result = rt_sscanf(str, "%[a-z-A-Z]", buffer);
    uassert_int_equal(result, 1);
    uassert_str_equal(buffer, "a-zA-Z");
}

static void TC_rt_sscanf_whitespace_skip(void)
{
    const char str[] = "   12345";
    int value;
    int result = rt_sscanf(str, "%d", &value);
    uassert_int_equal(result, 1);
    uassert_int_equal(value, 12345);
}

static void TC_rt_sscanf_unsigned_int(void)
{
    const char str[] = "4294967295";
    unsigned int value;
    int result = rt_sscanf(str, "%u", &value);
    uassert_int_equal(result, 1);
    uassert_int_equal(value, 4294967295U);
}

static void TC_rt_sscanf_long_long_int(void)
{
    const char str[] = "9223372036854775807";
    long long value;
    int result = rt_sscanf(str, "%lld", &value);
    uassert_int_equal(result, 1);
    uassert_int_equal(value, 9223372036854775807LL);
}

static void TC_rt_sscanf_short_int(void)
{
    const char str[] = "32767";
    short value;
    int result = rt_sscanf(str, "%hd", &value);
    uassert_int_equal(result, 1);
    uassert_int_equal(value, 32767);
}

static void TC_rt_sscanf_null_string(void)
{
    const char str[] = "";
    int value;
    int result = rt_sscanf(str, "%d", &value);
    uassert_int_equal(result, -1);
}

/* https://github.com/RT-Thread/rt-thread/issues/9853 */
static void TC_rt_sscanf_issue_9853(void)
{
    int device_socket = 255;
    int bfsz = 255;
    const char str[] = "+MIPURC: \"rtcp\",0,240,HTTP/1.1 200 OK";
    rt_sscanf(str, "+MIPURC:%*[^,],%d,%d", &device_socket, (int *)&bfsz);
    uassert_int_equal(device_socket, 0);
    uassert_int_equal(bfsz, 240);
}

static void utest_do_tc(void)
{
    UTEST_UNIT_RUN(TC_rt_sscanf_char);
    UTEST_UNIT_RUN(TC_rt_sscanf_basic_int);
    UTEST_UNIT_RUN(TC_rt_sscanf_basic_float);
    UTEST_UNIT_RUN(TC_rt_sscanf_basic_string);
    UTEST_UNIT_RUN(TC_rt_sscanf_string_with_space);
    UTEST_UNIT_RUN(TC_rt_sscanf_basic_char);
    UTEST_UNIT_RUN(TC_rt_sscanf_hex_1);
    UTEST_UNIT_RUN(TC_rt_sscanf_hex_2);
    UTEST_UNIT_RUN(TC_rt_sscanf_oct_1);
    UTEST_UNIT_RUN(TC_rt_sscanf_oct_2);
    UTEST_UNIT_RUN(TC_rt_sscanf_multiple_args);
    UTEST_UNIT_RUN(TC_rt_sscanf_pointer);
    UTEST_UNIT_RUN(TC_rt_sscanf_width_specifier);
    UTEST_UNIT_RUN(TC_rt_sscanf_suppression);
    UTEST_UNIT_RUN(TC_rt_sscanf_match_set);
    UTEST_UNIT_RUN(TC_rt_sscanf_match_set_negated);
    UTEST_UNIT_RUN(TC_rt_sscanf_match_set_range);
    UTEST_UNIT_RUN(TC_rt_sscanf_whitespace_skip);
    UTEST_UNIT_RUN(TC_rt_sscanf_unsigned_int);
    UTEST_UNIT_RUN(TC_rt_sscanf_long_long_int);
    UTEST_UNIT_RUN(TC_rt_sscanf_short_int);
    UTEST_UNIT_RUN(TC_rt_sscanf_null_string);
    UTEST_UNIT_RUN(TC_rt_sscanf_issue_9853);
}

UTEST_TC_EXPORT(utest_do_tc, "klibc.rt_sscanf", RT_NULL, RT_NULL, 1000);
