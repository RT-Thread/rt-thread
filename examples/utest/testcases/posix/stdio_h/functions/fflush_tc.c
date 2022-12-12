#include <stdio.h>

static int fflush_entry(void)
{
    fflush(stdout);
    printf("test fflush\n");

    printf("t");
    printf("e");
    printf("s");
    printf("t");
    fflush(stdout);
    printf(" fflush");
    fflush(stdout);
    printf("\n");
    return 0;
}

#include <utest.h>
static void test_fflush(void)
{
    uassert_int_equal(fflush_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_fflush);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.fflush.c", RT_NULL, RT_NULL, 10);

