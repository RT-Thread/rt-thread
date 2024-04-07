#include <stdio.h>
#include <string.h>

static int fdopen_entry(void)
{
    long l;
    char s[81] = {0};
    char c;
    int ret = 0;
    FILE* stream = fopen("fopen_file.txt","w+");
    if(stream == NULL)
    {
        ret = -1;
        perror("fopen");
    }
    else
    {
        fprintf(stream,"%s %d %c","a_string",6500,'x');
        fseek(stream,0L,SEEK_SET);
        fscanf(stream,"%s",s);
        fscanf(stream,"%ld",&l);
        fscanf(stream," %c",&c);

        if((strcmp(s,"a_string") != 0) || (l != 6500) || (c != 'x'))
        {
            ret = -1;
        }

        fclose(stream);
    }
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
UTEST_TC_EXPORT(testcase, "rtt_posix_testcase.stdio_h."__FILE__, RT_NULL, RT_NULL, 10);

