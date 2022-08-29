#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

#define NEW_CURR_DIR "./chdir_test"

static int chdir_entry(void)
{
    __attribute__((unused)) long path_max;
    size_t size;
    char *buf;
    char *ptr;

    __attribute__((unused)) char *old_dir;

    size = 1024;

    for (buf = ptr = NULL; ptr == NULL; size *= 2)
    {
        if ((buf = realloc(buf, size)) == NULL)
        {
            printf("error\n");
        }
        ptr = getcwd(buf, size);
        printf("ptr %s\n",ptr);

        if (ptr == NULL)
        {
            printf("error\n");
        }
        printf("old curr dir is %s\n", ptr);

        mkdir(NEW_CURR_DIR, 0x777);
        chdir(NEW_CURR_DIR);

        ptr = getcwd(buf, size);
        if (ptr == NULL)
        {
            printf("error\n");
        }
        printf("new curr dir is %s\n", ptr);
    }
    free(buf);
    return 0;
}

#include <utest.h>
static void test_chdir(void)
{
    uassert_int_equal(chdir_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_chdir);
}
UTEST_TC_EXPORT(testcase, "posix.unistd_h.chdir_tc.c", RT_NULL, RT_NULL, 10);

