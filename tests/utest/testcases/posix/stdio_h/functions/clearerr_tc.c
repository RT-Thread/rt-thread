#include <stdio.h>

static int clearerr_entry(void)
{
    putc( 'c', stdin );
    if( ferror( stdin ) )
    {
        perror( "Write error" );
        clearerr( stdin );
    }

    if( ferror( stdin ))
    {
        perror( "clearerr error" );
        return -1;
    }

    return 0;
}

#include <utest.h>
static void test_clearerr(void)
{
    uassert_int_equal(clearerr_entry(), 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test_clearerr);
}
UTEST_TC_EXPORT(testcase, "posix.stdio_h.clearerr.c", RT_NULL, RT_NULL, 10);

