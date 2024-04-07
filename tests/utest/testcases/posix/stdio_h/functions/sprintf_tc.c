#include <stdio.h>
#include <string.h>

static int sprintf_entry(void)
{
    char buf[64] = {0};
    char test_data[] = "sprintf test:2021-8-1 3.14 0xff";
    sprintf(buf, "sprintf test:%s-%d-%c %.02f 0x%x","2021" ,8 ,'1' ,3.14 ,0xff);

    if(strcmp(buf, test_data))
    {
        return -1;
    }
    return 0;
}

#include <utest.h>
static void test_sprintf(void)
{
    uassert_int_equal(sprintf_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_sprintf);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.sprintf.c", RT_NULL, RT_NULL, 10);

