#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

static int fdopen_entry(void)
{
    int fd;
    FILE *stream;

    fd = open("fdopen_file.txt", O_CREAT | O_RDWR | O_APPEND);
    if (fd < 0)
    {
        printf("open fail.\n");
        return -1;
    }

    /* TODO */
    stream = fdopen(fd, "w");
    if (stream == NULL)
    {
        printf("fdopen fail.\n");
        return -1;
    }

    fclose(stream);
    return 0;
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
UTEST_TC_EXPORT(testcase, "posix.stdio_h.fdopen_tc.c", RT_NULL, RT_NULL, 10);

