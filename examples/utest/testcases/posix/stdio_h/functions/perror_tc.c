#include <stdio.h>

static int perror_entry(void)
{
    FILE *stream;
    stream = fopen( "nulltest.txt", "r" );
    if(stream == NULL)
    {
        printf("perror test:");
        perror("nulltest.txt");
    }
    return 0;
}

#include <utest.h>
static void test_perror(void)
{
    uassert_int_equal(perror_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_perror);
}
UTEST_TC_EXPORT(testcase, "rtt_posix_testcase.stdio_h."__FILE__, RT_NULL, RT_NULL, 10);

