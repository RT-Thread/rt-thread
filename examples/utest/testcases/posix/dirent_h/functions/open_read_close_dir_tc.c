#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

#define DIRFD_TEST_NAME "/"

/* API for: opendir readdir closedir */
static int dir_test_entry(void)
{
    DIR *dirp;
    struct dirent *d;

    dirp = opendir(DIRFD_TEST_NAME);
    if (dirp == RT_NULL)
    {
        printf("open directory error!\n");
    }
    else
    {
        while ((d = readdir(dirp)) != RT_NULL)
        {
            printf("found %s\n", d->d_name);
        }

        closedir(dirp);
    }

    return 0;
}

#include <utest.h>
static void test_dir(void)
{
    uassert_int_equal(dir_test_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_dir);
}
UTEST_TC_EXPORT(testcase, "posix.dirent_h.open_read_close_dir_tc.c", RT_NULL, RT_NULL, 10);

