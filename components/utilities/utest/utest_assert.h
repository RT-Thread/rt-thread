/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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

#ifdef __cplusplus
extern "C" {
#endif

/* No need for the user to use this function directly */
rt_bool_t utest_assert(int value, const char *file, int line, const char *func, const char *msg);

/* No need for the user to use this function directly */
void utest_assert_string(const char *a, const char *b, rt_bool_t equal, const char *file, int line, const char *func, const char *msg);
void utest_assert_buf(const char *a, const char *b, rt_size_t sz, rt_bool_t equal, const char *file, int line, const char *func, const char *msg);

/* No need for the user to use this macro directly */
#define __utest_assert(value, msg) utest_assert(value, __FILE__, __LINE__, __func__, msg)
#define __uassert_value_op(a, b, op)    __utest_assert((a) op (b), "(" #a ") not " #op " (" #b ")")

/**
 * uassert_x macros
 *
 * @brief Get the utest data structure handle.
 *        No need for the user to call this function directly.
 *
 * @macro uassert_true          if @value is true,     not assert, means passing.
 * @macro uassert_false         if @value is false,    not assert, means passing.
 * @macro uassert_null          if @value is null,     not assert, means passing.
 * @macro uassert_not_null      if @value is not null, not assert, means passing.
 * @macro uassert_int_equal     if @a equal to @b,     not assert, means passing. Integer type test.
 * @macro uassert_int_not_equal if @a not equal to @b, not assert, means passing. Integer type test.
 * @macro uassert_str_equal     if @a equal to @b,     not assert, means passing. String type test.
 * @macro uassert_str_not_equal if @a not equal to @b, not assert, means passing. String type test.
 * @macro uassert_buf_equal     if @a equal to @b,     not assert, means passing. buf type test.
 * @macro uassert_buf_not_equal if @a not equal to @b, not assert, means passing. buf type test.
 * @macro uassert_in_range      if @value is in range of min and max,     not assert, means passing.
 * @macro uassert_not_in_range  if @value is not in range of min and max, not assert, means passing.
 *
*/
#define uassert_true(value)      __utest_assert(value, "(" #value ") is false")
#define uassert_false(value)     __utest_assert(!(value), "(" #value ") is true")

#define uassert_null(value)      __utest_assert((const char *)(value) == RT_NULL, "(" #value ") is not null")
#define uassert_not_null(value)  __utest_assert((const char *)(value) != RT_NULL, "(" #value ") is null")

#define uassert_in_range(value, min, max)     __utest_assert(((value >= min) && (value <= max)), "(" #value ") not in range("#min","#max")")
#define uassert_not_in_range(value, min, max) __utest_assert(!((value >= min) && (value <= max)), "(" #value ") in range("#min","#max")")

#define uassert_float_equal(a, b)         uassert_in_range(a, ((double)b - 0.0001), ((double)b + 0.0001))
#define uassert_float_not_equal(a, b)     uassert_not_in_range(a, ((double)b - 0.0001), ((double)b + 0.0001))

#define uassert_int_equal(a, b)           __uassert_value_op(a, b, ==)
#define uassert_int_not_equal(a, b)       __uassert_value_op(a, b, !=)

#define uassert_value_less(a, b)          __uassert_value_op(a, b, <)
#define uassert_value_less_equal(a, b)    __uassert_value_op(a, b, <=)
#define uassert_value_greater(a, b)       __uassert_value_op(a, b, >)
#define uassert_value_greater_equal(a, b) __uassert_value_op(a, b, >=)

#define uassert_ptr_equal(a, b)      __utest_assert((const void*)(a) == (const void*)(b), "(" #a ") not equal to (" #b ")")
#define uassert_ptr_not_equal(a, b)  __utest_assert((const void*)(a) != (const void*)(b), "(" #a ") equal to (" #b ")")

#define uassert_str_equal(a, b)      utest_assert_string((const char*)(a), (const char*)(b), RT_TRUE, __FILE__, __LINE__, __func__, "string not equal")
#define uassert_str_not_equal(a, b)  utest_assert_string((const char*)(a), (const char*)(b), RT_FALSE, __FILE__, __LINE__, __func__, "string equal")

#define uassert_buf_equal(a, b, sz)      utest_assert_buf((const char*)(a), (const char*)(b), (sz), RT_TRUE, __FILE__, __LINE__, __func__, "buf not equal")
#define uassert_buf_not_equal(a, b, sz)  utest_assert_buf((const char*)(a), (const char*)(b), (sz), RT_FALSE, __FILE__, __LINE__, __func__, "buf equal")

#ifdef __cplusplus
}
#endif

#endif /* __UTEST_ASSERT_H__ */
