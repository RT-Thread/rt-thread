#include <stdio.h>

static int puts_entry(void)
{
    char data[] = "puts testcase\n";
    printf("puts testcase:");
    puts(data);

    return 0;
}

#include <utest.h>
static void test_puts(void)
{
    uassert_int_equal(puts_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_puts);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.puts.c", RT_NULL, RT_NULL, 10);

