/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * Refer to https://www.rt-thread.org/document/api/iwdg_sample_8c-example.html
 * This is a watchdog device test routine, the program searches for the watchdog
 * device by device name, then initializes the device and sets the watchdog
 * device overflow time.
 *
 * "test_wdt_feed" tests that the watchdog timer will not time out when the
 * watchdog is fed and will not cause the system to restart.
 *
 * "test_wdt_nofeed" tests that the watchdog timer will time out when the
 * watchdog is not fed and cause the system to restart.
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "../interdrv/wdt/drv_wdt.h"
#include "utest.h"

/* Default watchdog device name */
/* If WDT0 and WDT1 both enabled, we use WDT0 */
#ifdef BSP_USING_WDT0
#define IWDG_DEVICE_NAME "wdt0"
#elif defined(BSP_USING_WDT1)
#define IWDG_DEVICE_NAME "wdt1"
#else
#error "No watchdog device defined!"
#endif

/* Watchdog device handle */
static rt_device_t wdg_dev;

/*
 * Dog feeding flag, 1 means feeding the dog, 0 means not feeding the dog.
 * This flag is used in the idle thread callback function.
 * If the dog is not fed, the system will restart due to watchdog timeout.
 */
static int flag_feed;

/* Overflow time, in seconds. */
static rt_uint32_t timeout = 3;

static void idle_hook(void)
{
    /* Feed the dog in the callback function of the idle thread */
    if (flag_feed)
        rt_device_control(wdg_dev, KD_DEVICE_CTRL_WDT_KEEPALIVE, NULL);

    /* Do not print, otherwise the screen will display too much. */
}

static void waiting_for_timeout(int seconds)
{
    LOG_I("Waiting for watchdog timer time-out...\n");
    for (int i = 0; i < seconds; i++)
    {
        rt_thread_mdelay(1000);
        LOG_I(".");
    }
}

static void test_wdt_feed(void)
{
    rt_err_t ret = RT_EOK;

    /* Find the watchdog device according to the name and obtain the handle */
    wdg_dev = rt_device_find(IWDG_DEVICE_NAME);
    uassert_not_null(wdg_dev);

    /* Initialize the device */
    ret = rt_device_init(wdg_dev);
    uassert_int_equal(ret, RT_EOK);

    /* Set the watchdog timeout time */
    ret = rt_device_control(wdg_dev, KD_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    uassert_int_equal(ret, RT_EOK);

    flag_feed = 1; /* Set feed the dog sign */

    /* start watchdog timer */
    rt_device_control(wdg_dev, KD_DEVICE_CTRL_WDT_START, RT_NULL);
    LOG_I("Watchdog Timer [%s] is launched!\n", IWDG_DEVICE_NAME);

    /* Delay enough time to see if the system will be restarted by the watchdog */
    waiting_for_timeout(10);

    LOG_I("Thanks for feeding me, I'm still alive!\n");
    /* If you feed the dog successfully, you will have a chance to come here and close the gate dog. */
    rt_device_close(wdg_dev);
    LOG_I("Watchdog is closed!\n");

    LOG_I("Test Done with Feed!\n");

    return;
}

static void test_wdt_nofeed(void)
{
    rt_err_t ret = RT_EOK;

    /* Find the watchdog device according to the name and obtain the handle */
    wdg_dev = rt_device_find(IWDG_DEVICE_NAME);
    uassert_not_null(wdg_dev);

    /* Initialize the device */
    ret = rt_device_init(wdg_dev);
    uassert_int_equal(ret, RT_EOK);

    /* Set the watchdog timeout time */
    ret = rt_device_control(wdg_dev, KD_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    uassert_int_equal(ret, RT_EOK);

    flag_feed = 0; /* Do not feed the dog */

    rt_device_control(wdg_dev, KD_DEVICE_CTRL_WDT_START, RT_NULL);
    LOG_I("Watchdog Timer [%s] is launched!\n", IWDG_DEVICE_NAME);

    /* Delay long enough and the system should reboot due to watchdog timeout. */
    LOG_I("Oops, I am so hungary and will be killed in seconds!\n");
    waiting_for_timeout(10);

    LOG_I("SHOULD NOT SEE THIS PRINT!\n");

    return;
}

static void test_wdt (void)
{
    UTEST_UNIT_RUN(test_wdt_feed);
    UTEST_UNIT_RUN(test_wdt_nofeed);
}

static rt_err_t utest_init(void)
{
    flag_feed = 0;
    rt_thread_idle_sethook(idle_hook);
    return RT_EOK;
}

UTEST_TC_EXPORT(test_wdt, "wdt", utest_init, NULL, 10);