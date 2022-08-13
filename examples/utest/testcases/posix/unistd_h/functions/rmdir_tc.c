#include <unistd.h>
#include <sys/stat.h>

#define RM_DIR "./rmdir"
static int rmdir_entry(void)
{
    int res = 0;
    res = mkdir(RM_DIR, 0x777);
    if(res != 0)
    {
        return -1;
    }

    res = rmdir(RM_DIR);
    if(res != 0)
    {
        return -1;
    }
    return res;
}

#include <utest.h>
static void test_rmdir(void)
{
    uassert_int_equal(rmdir_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_rmdir);
}
UTEST_TC_EXPORT(testcase, "posix.unistd_h.rmdir_tc.c", RT_NULL, RT_NULL, 10);

