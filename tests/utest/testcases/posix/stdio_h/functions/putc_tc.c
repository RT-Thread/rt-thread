#include <stdio.h>

static int putc_entry(void)
{
    FILE *stream;
    int ch = 'a';
    int getc = {0};
    size_t size = 0;
    int ret = 0;

    stream = fopen("fopen_file.txt","w");
    if (stream == NULL)
    {
        perror("fopen fail");
        ret = -1;
        goto __exit;
    }
    putc(ch, stream);
    fclose(stream);

    stream = fopen("fopen_file.txt","r");
    getc = fgetc(stream);

    if(getc != ch)
    {
        printf("fputc test:getc %c",getc);
        ret = -1;
    }
__exit:
    fclose(stream);
    return ret;
}

#include <utest.h>
static void test_putc(void)
{
    uassert_int_equal(putc_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_putc);
}
UTEST_TC_EXPORT(testcase, "rtt_posix_testcase.stdio_h."__FILE__, RT_NULL, RT_NULL, 10);

