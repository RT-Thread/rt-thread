#include <stdio.h>
#include <string.h>

static int sscanf_entry(void)
{
    int day, year;
    char weekday[20], month[20], dtm[100];

    strcpy( dtm, "Friday January 1 2021" );
    sscanf( dtm, "%s %s %d  %d", weekday, month, &day, &year );

    if(strcmp(month,"January") || strcmp(weekday,"Friday")
        || (year != 2021) ||(day != 1))
    {
        return -1;
    }
    return 0;
}

#include <utest.h>
static void test_sscanf(void)
{
    uassert_int_equal(sscanf_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_sscanf);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.sscanf.c", RT_NULL, RT_NULL, 10);

