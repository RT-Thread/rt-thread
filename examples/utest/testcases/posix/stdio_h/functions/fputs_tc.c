#include <stdio.h>
#include <string.h>

static int fputs_entry(void)
{
    FILE *stream;
    char test_data[] = "1a2bxx";
    char gets[sizeof(test_data)] = {0};
    size_t size = 0;
    int ret = 0;

    stream = fopen("fopen_file.txt","w");
    if (stream == NULL)
    {
        perror("fopen fail");
        ret = -1;
        goto __exit;
    }
    fputs(test_data, stream);
    fclose(stream);

    stream = fopen("fopen_file.txt","r");
    fgets(gets, sizeof(gets), stream);

    if(strcmp(test_data, gets))
    {
        printf("%s\n",gets);
        ret = -1;
    }
__exit:
    fclose(stream);
    return ret;
}

#include <utest.h>
static void test_fputs(void)
{
    uassert_int_equal(fputs_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_fputs);
}
UTEST_TC_EXPORT(testcase, "rtt_posix_testcase.stdio_h."__FILE__, RT_NULL, RT_NULL, 10);

