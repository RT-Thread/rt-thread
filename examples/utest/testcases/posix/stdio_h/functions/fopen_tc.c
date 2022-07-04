#include <stdio.h>

static int fopen_entry(void)
{
    FILE *stream;
    /* TODO: other mode fopen */
    stream = fopen("fopen_file.txt","a+");
    if (stream == NULL)
    {
        perror("fopen fail");
        return -1;
    }

    fclose(stream);
    return 0;
}

#include <utest.h>
static void test_fopen(void)
{
    uassert_int_equal(fopen_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_fopen);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.fopen.c", RT_NULL, RT_NULL, 10);

