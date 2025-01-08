#include <rtthread.h>
#include "utest.h"

static void TC_uassert_true_false(void)
{
    uassert_true(1);
    uassert_false(0);
}

static void TC_uassert_null_not_null(void)
{
    int *ptr = RT_NULL;
    int value = 10;
    int *ptr2 = &value;

    uassert_null(ptr);
    uassert_not_null(ptr2);
}

static void TC_uassert_int_op(void)
{
    int a = 5;
    int b = 10;

    uassert_int_equal(a, a);
    uassert_int_not_equal(a, b);
    uassert_value_less(a, b);
    uassert_value_less_equal(a, b);
    uassert_value_less_equal(a, a);
    uassert_value_greater(b, a);
    uassert_value_greater_equal(b, a);
    uassert_value_greater_equal(b, b);
}

static void TC_uassert_ptr_op(void)
{
    int a = 5;
    int b = 10;
    int *ptr_a = &a;
    int *ptr_b = &b;

    uassert_ptr_equal(ptr_a, ptr_a);
    uassert_ptr_not_equal(ptr_a, ptr_b);
}

static void TC_uassert_str_op(void)
{
    const char *str1 = "Hello";
    const char *str2 = "Hello";
    const char *str3 = "World";

    uassert_str_equal(str1, str2);
    uassert_str_not_equal(str1, str3);
}

static void TC_uassert_in_range(void)
{
    int value = 5;
    uassert_in_range(value, 1, 10);
    uassert_not_in_range(value, 10, 20);
}

static void utest_do_tc(void)
{
    UTEST_UNIT_RUN(TC_uassert_true_false);
    UTEST_UNIT_RUN(TC_uassert_null_not_null);
    UTEST_UNIT_RUN(TC_uassert_int_op);
    UTEST_UNIT_RUN(TC_uassert_ptr_op);
    UTEST_UNIT_RUN(TC_uassert_str_op);
    UTEST_UNIT_RUN(TC_uassert_in_range);
}

UTEST_TC_EXPORT(utest_do_tc, "utest.uassert", RT_NULL, RT_NULL, 10);
