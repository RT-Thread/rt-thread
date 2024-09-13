#include <rtdevice.h>
#include "utest.h"
#include "utest_assert.h"
#include "smp.h"
static int                pass_count = 0;
static int                pass       = 1000;
static struct rt_spinlock lock;

static void test_call(void *data)
{
    rt_spin_lock(&lock);
    int *i   = (int *)data;
    int  id  = rt_hw_cpu_id();
    *i      &= ~(1 << id);
    if (*i == 0)
        pass_count++;
    rt_spin_unlock(&lock);
}


static void test1()
{
    int cpu_mask = 0xf;
    for (int i = 0; i < 1000; i++)
    {
        cpu_mask = rand() % 0xf;
        if (cpu_mask == 0)
            pass--;
        rt_smp_call_any_cpu(cpu_mask,test_call, &cpu_mask, SMP_CALL_WAIT_ALL);
        if (i % 20 == 0)
            rt_kprintf("#");
    }
    rt_kprintf("\n");
    uassert_true(pass_count == pass);
}

static void test_call2(void *data)
{
    rt_spin_lock(&lock);
    int a = 100000;
    while (a--);
    int *i = (int *)data;
    (*i)++;
    rt_spin_unlock(&lock);
}
static void test2(void)
{
    int data = 0;
    rt_smp_call_each_cpu(test_call2, &data, SMP_CALL_WAIT_ALL);
    uassert_true(data == RT_CPUS_NR);
    rt_thread_mdelay(10);
    data = 0;
    rt_smp_call_each_cpu(test_call2, &data, SMP_CALL_NO_WAIT);
    uassert_true(data != RT_CPUS_NR);
}

static rt_err_t utest_tc_init(void)
{
    pass_count = 0;
    pass       = 1000;
    rt_spin_lock_init(&lock);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}
static void testcase(void)
{
    UTEST_UNIT_RUN(test1);
    UTEST_UNIT_RUN(test2);
}

UTEST_TC_EXPORT(testcase, "testcase.smp.smp", utest_tc_init, utest_tc_cleanup, 10);
