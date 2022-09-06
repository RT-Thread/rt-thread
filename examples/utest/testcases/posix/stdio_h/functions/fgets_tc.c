#include <stdio.h>

static int fgets_entry(void)
{
    FILE *stream;
    char data[] = "test fgets";
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
    fgets(gets, sizeof(gets), stream);

    if(strcmp(gets, data))
    {
        ret = -1;
    }

__exit:
    fclose(stream);
    return ret;
}

#include <utest.h>
static void test_fgets(void)
{
    uassert_int_equal(fgets_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_fgets);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.fgets.c", RT_NULL, RT_NULL, 10);

