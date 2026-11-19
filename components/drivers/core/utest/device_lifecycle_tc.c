/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* A counting device checks init/open, close/open and exclusive first opens.
 * A lower-priority witness on the opener's CPU releases the mock callback
 * only after the opener has either finished or blocked. No hardware required. */
#include <rtthread.h>
#include "utest.h"

#if defined(RT_USING_DEVICE_LIFECYCLE_LOCK) && defined(RT_USING_SEMAPHORE) && defined(RT_USING_HEAP)

static struct rt_device dev;
static struct rt_semaphore witness_done, opener_done;
static int init_calls, open_calls, close_calls;
static int callback_cpu, opener_cpu;
static rt_err_t open_result;
static enum
{
    NO_OVERLAP,
    DURING_INIT,
    DURING_OPEN,
    DURING_CLOSE
} overlap;
static rt_bool_t contender_started;

static void open_entry(void *arg)
{
    opener_cpu = rt_cpu_get_id();
    open_result = rt_device_open(&dev, RT_DEVICE_OFLAG_RDONLY);
    rt_sem_release(&opener_done);
}

static void witness_entry(void *arg)
{
    rt_sem_release(&witness_done);
}

static rt_err_t run_contender(void)
{
    rt_err_t result = -RT_ENOMEM;
    rt_thread_t opener, witness;
#ifdef RT_USING_SMP
    rt_ubase_t target;
    rt_base_t level;
#endif

    overlap = NO_OVERLAP;
    opener = rt_thread_create("lcopen", open_entry, RT_NULL, 1024, RT_THREAD_PRIORITY_MAX / 2, 10);
    witness = rt_thread_create("lcseen", witness_entry, RT_NULL, 1024, RT_THREAD_PRIORITY_MAX / 2 + 1, 10);
    if (!opener || !witness)
    {
        goto fail;
    }

    /* The witness cannot run ahead of the higher-priority opener on that CPU. */
#ifdef RT_USING_SMP
    level = rt_enter_critical();
    callback_cpu = rt_cpu_get_id();
    rt_exit_critical_safe(level);
    target = (callback_cpu + 1) % RT_CPUS_NR;
    result = rt_thread_control(opener, RT_THREAD_CTRL_BIND_CPU, (void *)target);
    if (result != RT_EOK)
    {
        goto fail;
    }
    result = rt_thread_control(witness, RT_THREAD_CTRL_BIND_CPU, (void *)target);
    if (result != RT_EOK)
    {
        goto fail;
    }
#else
    callback_cpu = 0;
#endif
    contender_started = RT_TRUE;
    rt_thread_startup(opener);
    rt_thread_startup(witness);
    return rt_sem_take(&witness_done, RT_WAITING_FOREVER);

fail:
    if (opener)
    {
        rt_thread_delete(opener);
    }
    if (witness)
    {
        rt_thread_delete(witness);
    }
    return result;
}

static void wait_for_opener(rt_err_t expected)
{
    uassert_true(contender_started);
    if (contender_started)
    {
        rt_sem_take(&opener_done, RT_WAITING_FOREVER);
        contender_started = RT_FALSE;
        uassert_int_equal(open_result, expected);
    }
}

static rt_err_t mock_init(rt_device_t device)
{
    init_calls++;
    return overlap == DURING_INIT ? run_contender() : RT_EOK;
}

static rt_err_t mock_open(rt_device_t device, rt_uint16_t oflag)
{
    open_calls++;
    device->open_flag = oflag & RT_DEVICE_OFLAG_MASK;
    return overlap == DURING_OPEN ? run_contender() : RT_EOK;
}

static rt_err_t mock_close(rt_device_t device)
{
    close_calls++;
    return overlap == DURING_CLOSE ? run_contender() : RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops ops = {
    .init = mock_init,
    .open = mock_open,
    .close = mock_close,
};
#endif

static void test_shared_open(void)
{
    overlap = DURING_INIT;
    uassert_int_equal(rt_device_init(&dev), RT_EOK);
    wait_for_opener(RT_EOK);
    uassert_int_equal(rt_device_open(&dev, RT_DEVICE_OFLAG_RDONLY), RT_EOK);
    rt_kprintf("device lifecycle: init calls %d, first-open calls %d, refs %d\n", init_calls, open_calls, dev.ref_count);
    uassert_int_equal(init_calls, 1);
    uassert_int_equal(open_calls, 1);
    uassert_int_equal(dev.ref_count, 2);
    uassert_int_equal(rt_device_close(&dev), RT_EOK);
    uassert_int_equal(close_calls, 0);
    uassert_int_equal(rt_device_close(&dev), RT_EOK);
    uassert_int_equal(close_calls, 1);
}

static void test_reopen_during_close(void)
{
    int before;

    uassert_int_equal(rt_device_open(&dev, RT_DEVICE_OFLAG_RDONLY), RT_EOK);
    before = open_calls;
    overlap = DURING_CLOSE;
    uassert_int_equal(rt_device_close(&dev), RT_EOK);
    wait_for_opener(RT_EOK);
    uassert_int_equal(dev.ref_count, 1);
    uassert_int_equal(dev.open_flag, RT_DEVICE_OFLAG_OPEN | RT_DEVICE_OFLAG_RDONLY);
    uassert_int_equal(open_calls, before + 1);
#if defined(RT_USING_SMP) && RT_CPUS_NR > 1
    uassert_int_not_equal(callback_cpu, opener_cpu);
#endif
    rt_kprintf("device lifecycle: close cpu %d, open cpu %d, refs %d, flags 0x%x, driver reopens %d\n",
               callback_cpu, opener_cpu, dev.ref_count, dev.open_flag, open_calls - before);
    uassert_int_equal(rt_device_close(&dev), RT_EOK);
    uassert_int_equal(dev.ref_count, 0);
    uassert_int_equal(dev.open_flag, RT_DEVICE_OFLAG_CLOSE);
}

static void test_standalone_open(void)
{
    int before = open_calls;

    /* This private device is closed and has no other users. */
    dev.flag |= RT_DEVICE_FLAG_STANDALONE;
    overlap = DURING_OPEN;
    uassert_int_equal(rt_device_open(&dev, RT_DEVICE_OFLAG_RDONLY), RT_EOK);
    wait_for_opener(-RT_EBUSY);
    rt_kprintf("device lifecycle: standalone refs %d, driver opens %d\n", dev.ref_count, open_calls - before);
    uassert_int_equal(dev.ref_count, 1);
    uassert_int_equal(open_calls, before + 1);

    if (open_result == RT_EOK)
    {
        rt_device_close(&dev);
    }
    uassert_int_equal(rt_device_close(&dev), RT_EOK);
}

static rt_err_t testcase_init(void)
{
    rt_err_t result;

    rt_memset(&dev, 0, sizeof(dev));
    dev.type = RT_Device_Class_Char;
    /* Install the counting callbacks after devfs has published the test node. */
    result = rt_device_register(&dev, "lcdev", RT_DEVICE_FLAG_RDWR);
    if (result != RT_EOK)
    {
        return result;
    }
#ifdef RT_USING_DEVICE_OPS
    dev.ops = &ops;
#else
    dev.init = mock_init;
    dev.open = mock_open;
    dev.close = mock_close;
#endif
    rt_sem_init(&witness_done, "lcseen", 0, RT_IPC_FLAG_PRIO);
    rt_sem_init(&opener_done, "lcdone", 0, RT_IPC_FLAG_PRIO);
    init_calls = open_calls = close_calls = 0;
    return RT_EOK;
}

static rt_err_t testcase_cleanup(void)
{
    rt_sem_detach(&opener_done);
    rt_sem_detach(&witness_done);
    return rt_device_unregister(&dev);
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_shared_open);
    UTEST_UNIT_RUN(test_reopen_during_close);
    UTEST_UNIT_RUN(test_standalone_open);
}
UTEST_TC_EXPORT(testcase, "components.drivers.core.lifecycle", testcase_init, testcase_cleanup, 10);
#endif
