#include <stdio.h>
#include <string.h>

static int ftell_entry(void)
{
    FILE *stream;
    char str[] = "123456789";
    int ret = 0;

    stream = fopen("fopen_file.txt","w");
    if (stream == NULL)
    {
        perror("fopen");
        ret = -1;
    }
    else
    {
        fprintf(stream, "%s",str);
        if(ftell(stream) != strlen(str))
        {
            ret = -1;
        }
        fclose(stream);
    }
    return ret;
}

#include <utest.h>
static void test_ftell(void)
{
    uassert_int_equal(ftell_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_ftell);
}
UTEST_TC_EXPORT(testcase, "rtt_posix_testcase.stdio_h."__FILE__, RT_NULL, RT_NULL, 10);

