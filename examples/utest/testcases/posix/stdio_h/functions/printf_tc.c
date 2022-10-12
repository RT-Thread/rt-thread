#include <stdio.h>

static int printf_entry(void)
{
    printf("printf test:%s-%d-%c %f 0x%x","2021" ,8 ,'1' ,3.14 ,0xff);
    return 0;
}

#include <utest.h>
static void test_printf(void)
{
    uassert_int_equal(printf_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_printf);
}
UTEST_TC_EXPORT(testcase, "rtt_posix_testcase.stdio_h."__FILE__, RT_NULL, RT_NULL, 10);

