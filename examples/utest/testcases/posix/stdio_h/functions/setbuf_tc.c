#include <stdio.h>
#include <string.h>

static char outbuf[BUFSIZ];
static int setbuf_entry(void)
{
    FILE *stream;
    char test_data[] = "test setbuf";
    int ret = 0;

    stream = fopen("fopen_file.txt","w");
    if (stream == NULL)
    {
        perror("fopen fail");
        ret = -1;
        goto __exit;
    }
    setbuf(stream, outbuf);
    fwrite(test_data, sizeof(test_data), 1,stream);

    if(strcmp(test_data, outbuf))
    {
        printf("setbuf test:%s\n",test_data);
        ret = -1;
    }
__exit:
    fclose(stream);
    return ret;
}

#include <utest.h>
static void test_setbuf(void)
{
    uassert_int_equal(setbuf_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_setbuf);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.setbuf.c", RT_NULL, RT_NULL, 10);

