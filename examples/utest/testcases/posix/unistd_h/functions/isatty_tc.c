#include <unistd.h>

#include <utest.h>
static void test_isatty(void)
{
    int i = 0;

    for (i = 0; i < 3; i++) /* 3: Number of terminals */
    {
        uassert_int_equal(isatty(i), 1);
    }
    for (i = 3; i < 32; i++) /* 32: DFS_FD_MAX */
    {
        uassert_int_equal(isatty(i), 0);
    }
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_isatty);
}
UTEST_TC_EXPORT(testcase, "posix.unistd_h.isatty_tc.c", RT_NULL, RT_NULL, 10);

