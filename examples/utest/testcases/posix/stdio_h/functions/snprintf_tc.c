#include <stdio.h>
#include <string.h>

static int snprintf_entry(void)
{
    char buf[64] = {0};
    char test_data[] = "snprintf test:2021-8-";
    snprintf(buf, 22,"snprintf test:%s-%d-%c %.02f 0x%x","2021" ,8 ,'1' ,3.14 ,0xff);

    if(strcmp(buf, test_data))
    {
        return -1;
    }
    return 0;
}

#include <utest.h>
static void test_snprintf(void)
{
    uassert_int_equal(snprintf_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_snprintf);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.snprintf.c", RT_NULL, RT_NULL, 10);

