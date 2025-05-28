/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

 /*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <drivers/hwtimer.h>

#include "../interdrv/hwtimer/drv_timer.h"
#include "utest.h"

/*
 * This test case is designed to test the hardware timer driver.
 * It will:
 * 1. Find two hardware timer devices.
 * 2. Open both devices.
 * 3. Set a custom frequency for timer0 and use the default frequency for timer1.
 * 4. Start both timers with different timeout values.
 * 5. Poll and print the current value of each timer every second.
 * 6. Trigger the interrupt callback when the timer times out and print a message.
 */

#define DEVICE_NAME0 "hwtimer0"
#define DEVICE_NAME1 "hwtimer1"

static rt_device_t tmr_dev_0;
static rt_device_t tmr_dev_1;

#define TIMEOUT_SEC_0 10
#define TIMEOUT_SEC_1 5
#define MAX_TIMEOUT_SEC \
    (TIMEOUT_SEC_0 > TIMEOUT_SEC_1 ? TIMEOUT_SEC_0 : TIMEOUT_SEC_1)

static rt_err_t tmr_timeout_cb(rt_device_t dev, rt_size_t size)
{
    struct rt_hwtimer_device *rt_timer = rt_container_of(dev, struct rt_hwtimer_device, parent);
    struct k230_timer *kd_timer = rt_container_of(rt_timer, struct k230_timer, device);

    LOG_I("---> [%s] timeout callback fucntion!\n", kd_timer->name);
    return RT_EOK;
}

static void test_hwtimer(void)
{
    rt_hwtimerval_t timerval;
    rt_hwtimer_mode_t mode;
    rt_size_t tsize;
    rt_uint32_t freq = 25000000; /* Frequency options: 12.5M 25M 50M 100M */
    rt_err_t ret;
    rt_ssize_t size;
    int loop_count = 0;

    LOG_I("test_hwtimer start");

    tmr_dev_0 = rt_device_find(DEVICE_NAME0);
    uassert_not_null(tmr_dev_0);
    tmr_dev_1 = rt_device_find(DEVICE_NAME1);
    uassert_not_null(tmr_dev_1);

    ret = rt_device_open(tmr_dev_0, RT_DEVICE_OFLAG_RDWR);
    uassert_int_equal(ret, RT_EOK);
    ret = rt_device_open(tmr_dev_1, RT_DEVICE_OFLAG_RDWR);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_device_control(tmr_dev_0, HWTIMER_CTRL_FREQ_SET, &freq);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_device_set_rx_indicate(tmr_dev_0, tmr_timeout_cb);
    uassert_int_equal(ret, RT_EOK);
    ret = rt_device_set_rx_indicate(tmr_dev_1, tmr_timeout_cb);
    uassert_int_equal(ret, RT_EOK);

    timerval.sec = TIMEOUT_SEC_0;
    timerval.usec = 0;
    tsize = sizeof(timerval);
    mode = HWTIMER_MODE_ONESHOT;
    ret = rt_device_control(tmr_dev_0, HWTIMER_CTRL_MODE_SET, &mode);
    uassert_int_equal(ret, RT_EOK);
    size = rt_device_write(tmr_dev_0, 0, &timerval, tsize);
    uassert_int_equal(size, tsize);
    LOG_I("timer0 start: [%d:%d]\n", timerval.sec, timerval.usec);

    timerval.sec = TIMEOUT_SEC_1;
    timerval.usec = 0;
    tsize = sizeof(timerval);
    mode = HWTIMER_MODE_ONESHOT;
    ret = rt_device_control(tmr_dev_1, HWTIMER_CTRL_MODE_SET, &mode);
    uassert_int_equal(ret, RT_EOK);
    size = rt_device_write(tmr_dev_1, 0, &timerval, tsize);
    uassert_int_equal(size, tsize);
    LOG_I("timer1 start: [%d:%d]\n", timerval.sec, timerval.usec);

    while (loop_count++ < MAX_TIMEOUT_SEC + 1)
    {
        size = rt_device_read(tmr_dev_0, 0, &timerval, sizeof(timerval));
        uassert_int_equal(size, sizeof(timerval));
        LOG_I("timer0: [%d:%d]\n", timerval.sec, timerval.usec);

        size = rt_device_read(tmr_dev_1, 0, &timerval, sizeof(timerval));
        uassert_int_equal(size, sizeof(timerval));
        LOG_I("timer1: [%d:%d]\n", timerval.sec, timerval.usec);

        rt_thread_mdelay(1000);
    }

    ret = rt_device_close(tmr_dev_0);
    uassert_int_equal(ret, RT_EOK);
    ret = rt_device_close(tmr_dev_1);
    uassert_int_equal(ret, RT_EOK);
    LOG_I("test_hwtimer end");
}

static void hw_timer_testcase(void)
{
    UTEST_UNIT_RUN(test_hwtimer);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}
static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

UTEST_TC_EXPORT(hw_timer_testcase, "timer", utest_tc_init, utest_tc_cleanup, 10);