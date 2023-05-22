#include <stdio.h>

static int fclose_entry(void)
{
    FILE *stream;
    stream = fopen("fopen_file.txt","a+");
    if (stream == NULL)
    {
        perror("fopen fail");
        return -1;
    }
    if(fclose(stream) != 0)
    {
        perror("fclose fail");
        return -1;
    }
    else 
    {
        printf("fclose success \n");
    }
    return 0;
}

#include <utest.h>
static void test_fclose(void)
{
    uassert_int_equal(fclose_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_fclose);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.fclose.c", RT_NULL, RT_NULL, 10);

