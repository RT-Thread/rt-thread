#include <rtthread.h>
#include <utest.h>


#ifdef TC_USING_UTEST_DEMO_TC
static void test_assert_pass(void)
{
    uassert_true(1);
    uassert_true(0);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static rt_err_t testcase(void)
{
    UTEST_UNIT_RUN(test_assert_pass);
}

UTEST_TC_EXPORT(testcase,"app.utilities.utest_tc",utest_tc_init,utest_tc_cleanup,10);

#endif
