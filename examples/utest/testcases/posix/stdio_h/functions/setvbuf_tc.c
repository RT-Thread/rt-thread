#include <stdio.h>
#include <string.h>

static char outbuf[BUFSIZ];
static int setvbuf_entry(void)
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
    setvbuf(stream, outbuf, _IOLBF, BUFSIZ);
    fwrite(test_data, sizeof(test_data), 1,stream);

    if(strcmp(test_data, outbuf))
    {
        printf("setvbuf test:%s\n",test_data);
        ret = -1;
    }
__exit:
    fclose(stream);
    return ret;
}

#include <utest.h>
static void test_setvbuf(void)
{
    uassert_int_equal(setvbuf_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_setvbuf);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.setvbuf.c", RT_NULL, RT_NULL, 10);

