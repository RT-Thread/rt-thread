#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static void WriteFrmtd(FILE *stream ,char *format, ...)
{
   va_list args;

   va_start(args, format);
   vfprintf(stream, format, args);
   va_end(args);
}

static int vfprintf_entry(void)
{
    int ret = 0;
    char buf[64] = {0};
    char test_data[] = "vfprintf test:2021-8-1 3.14 0xff";
    FILE *stream = fopen("fopen_file.txt", "w");
    if(stream)
    {
        WriteFrmtd(stream, "vfprintf test:%s-%d-%c %.02f 0x%x","2021" ,8 ,'1' ,3.14 ,0xff);
        fclose(stream);

        stream = fopen("fopen_file.txt","r");
        fread(buf, 1, sizeof(test_data), stream);
        if(strcmp(buf, test_data))
        {
            ret = -1;
        }
        fclose(stream);
    }
    else
    {
        ret = -1;
    }

    return ret;
}

#include <utest.h>
static void test_vfprintf(void)
{
    uassert_int_equal(vfprintf_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_vfprintf);
}
UTEST_TC_EXPORT(testcase, "rtt_posix_testcase.stdio_h."__FILE__, RT_NULL, RT_NULL, 10);

