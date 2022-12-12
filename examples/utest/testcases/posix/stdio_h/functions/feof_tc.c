#include <stdio.h>
#include <string.h>

static int feof_entry(void)
{
    FILE *stream;
    char data[] = "test fgetc";
    char getc[sizeof(data)] = {0};
    size_t size = 0;
    int ret = 0;
    int i=0;

    stream = fopen("fopen_file.txt","w+");
    if (stream == NULL)
    {
        perror("fopen fail");
        ret = -1;
        goto __exit;
    }

    fwrite(data, sizeof(data), 1, stream);
    fclose(stream);

    stream = fopen("fopen_file.txt","r");
    while(1)
    {
        getc[i] = fgetc(stream);
        i++;
        if( feof(stream) )
        {
            break ;
        }
    }

    if(strcmp(getc, data))
    {
        return -1;
    }

    fclose(stream);
__exit:
    return ret;
}

#include <utest.h>
static void test_feof(void)
{
    uassert_int_equal(feof_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_feof);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.feof.c", RT_NULL, RT_NULL, 10);

