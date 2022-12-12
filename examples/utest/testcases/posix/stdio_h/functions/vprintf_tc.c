#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static void WriteFrmtd(char *format, ...)
{
   va_list args;

   va_start(args, format);
   vprintf(format, args);
   va_end(args);
}

static int vprintf_entry(void)
{
    WriteFrmtd("vprintf test:%s-%d-%c %.02f 0x%x\n","2021" ,8 ,'1' ,3.14 ,0xff);
    return 0;
}

#include <utest.h>
static void test_vprintf(void)
{
    uassert_int_equal(vprintf_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_vprintf);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.vprintf.c", RT_NULL, RT_NULL, 10);

