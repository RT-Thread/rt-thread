#include <stdio.h>

static int putchar_entry(void)
{
    char data[] = "putchar testcase\n";
    int i = 0;
    for(;i < sizeof(data);i++)
    {
        putchar(data[i]);
    }
    fflush(stdout);
    return 0;
}

#include <utest.h>
static void test_putchar(void)
{
    uassert_int_equal(putchar_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_putchar);
}
UTEST_TC_EXPORT(testcase, "rtt_posix_testcase.stdio_h."__FILE__, RT_NULL, RT_NULL, 10);

