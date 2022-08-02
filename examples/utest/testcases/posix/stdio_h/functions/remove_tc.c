#include <stdio.h>

static int remove_entry(void)
{
    FILE *stream;
    stream = fopen("fopen_file.txt","w");
    if(stream)
    {
        fclose(stream);
        remove("fopen_file.txt");
        stream = fopen("fopen_file.txt","r");
        if(stream)
        {
            fclose(stream);
            return -1;
        }
    }
    else
    {
        return -1;
    }
    return 0;
}

#include <utest.h>
static void test_remove(void)
{
    uassert_int_equal(remove_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_remove);
}
UTEST_TC_EXPORT(testcase, "rtt_posix_testcase.stdio_h."__FILE__, RT_NULL, RT_NULL, 10);

