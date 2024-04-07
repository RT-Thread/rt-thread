#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#define ACCESS_DIR "./access_dir"

#include <utest.h>
static int access_entry(void)
{
    int i = 0;

    /* file/dir that not exist*/
    char *files[] =
    {
        "/usr/local/nginx/conf/nginx.conf",
        "./a.out",
        "/usr/include/libgen.h",
        "/ff/last",
        NULL
    };

    for (i = 0; files[i] != NULL; i++)
    {
        /* mode=0: file/dir exist or not */
        uassert_int_not_equal(access(files[i], 0), 0);
    }

    mkdir(ACCESS_DIR, 0x777);
    uassert_int_equal(access(ACCESS_DIR, 0), 0);
    return 0;
}

static void test_access(void)
{
    uassert_int_equal(access_entry(), 0);
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_access);
}
UTEST_TC_EXPORT(testcase, "posix.unistd_h.access_tc.c", RT_NULL, RT_NULL, 10);

