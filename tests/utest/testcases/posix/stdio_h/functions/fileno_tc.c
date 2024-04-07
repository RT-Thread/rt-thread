#include <stdio.h>

static int fdopen_entry(void)
{
    int stdin_no = fileno(stdin);
    int stdout_no = fileno(stdout);
    int stderr_no = fileno(stderr);

    if((stdin_no == 0) && (stdout_no == 1) && (stderr_no == 2))
    {
        return 0;
    }
    return -1;
}

#include <utest.h>
static void test_fdopen(void)
{
    uassert_int_equal(fdopen_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_fdopen);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.fileno.c", RT_NULL, RT_NULL, 10);

