#include <stdio.h>
#include <string.h>

static int fdopen_entry(void)
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
    fprintf(stream, "%d%c%d%c%s",1,'a',2,'b',"xx");
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
static void test_fdopen(void)
{
    uassert_int_equal(fdopen_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_fdopen);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.fprintf.c", RT_NULL, RT_NULL, 10);

