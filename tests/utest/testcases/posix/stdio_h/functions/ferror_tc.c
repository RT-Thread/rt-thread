#include <stdio.h>

static int ferror_entry(void)
{
    int c;
    putc( 'c', stdin );
    if( ferror( stdin ) )
    {
        clearerr( stdin );
    }
    else
    {
        return -1;
    }
    return 0;
}

#include <utest.h>
static void test_ferror(void)
{
    uassert_int_equal(ferror_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_ferror);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.ferror.c", RT_NULL, RT_NULL, 10);

