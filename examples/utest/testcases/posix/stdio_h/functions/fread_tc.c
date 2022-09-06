#include <stdio.h>
#include <string.h>


static int fread_entry(void)
{
    FILE *stream;
    char data[] = "test fread";
    char gets[sizeof(data)] = {0};
    size_t size = 0;
    int ret = 0;

    stream = fopen("fopen_file.txt","w");
    if (stream == NULL)
    {
        perror("fopen fail");
        ret = -1;
        goto __exit;
    }
    fwrite(data, sizeof(data), 1, stream);
    fclose(stream);

    stream = fopen("fopen_file.txt","r");
    fread(gets, sizeof(gets), 1, stream);
    if(strcmp(gets, data))
    {
        ret = -1;
    }
__exit:
    fclose(stream);
    return ret;
}

#include <utest.h>
static void test_fread(void)
{
    uassert_int_equal(fread_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_fread);
}
UTEST_TC_EXPORT(testcase, "rtt_posix_testcase.stdio_h."__FILE__, RT_NULL, RT_NULL, 10);

