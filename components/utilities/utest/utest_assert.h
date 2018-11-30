/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-19     MurphyZhao   the first version
 */

#ifndef __UTEST_ASSERT_H__
#define __UTEST_ASSERT_H__

#include "utest.h"
#include <rtthread.h>

void utest_assert(int value, const char *file, int line, const char *func, const char *msg);
void utest_assert_string(const char *a, const char *b, rt_bool_t equal, const char *file, int line, const char *func, const char *msg);

#define __utest_assert(value, msg) utest_assert(value, __FILE__, __LINE__, __func__, msg)

#define uassert_true(value)      __utest_assert(value, "(" #value ") is false")
#define uassert_false(value)     __utest_assert(!(value), "(" #value ") is true")
#define uassert_null(value)      __utest_assert((value) == NULL, "(" #value ") is not null")
#define uassert_not_null(value)  __utest_assert((value) != NULL, "(" #value ") is null")

#define uassert_int_equal(a, b)      __utest_assert((a) == (b), "(" #a ") not equal to (" #b ")")
#define uassert_int_not_equal(a, b)  __utest_assert((a) != (b), "(" #a ") equal to (" #b ")")

#define uassert_str_equal(a, b)      utest_assert_string((const char*)(a), (const char*)(b), RT_TRUE, __FILE__, __LINE__, __func__, "string not equal")
#define uassert_str_not_equal(a, b)  utest_assert_string((const char*)(a), (const char*)(b), RT_FALSE, __FILE__, __LINE__, __func__, "string equal")

#define uassert_in_range(value, min, max)     __utest_assert(((value >= min) && (value <= max)), "(" #value ") not in range("#min","#max")") 
#define uassert_not_in_range(value, min, max) __utest_assert(!((value >= min) && (value <= max)), "(" #value ") in range("#min","#max")")

#endif /* __UTEST_ASSERT_H__ */
