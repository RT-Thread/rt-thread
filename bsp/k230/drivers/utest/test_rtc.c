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
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <time.h>
#include <utest.h>
#include <finsh.h>
#include "drv_rtc.h"

/*
 * 测试 RTC 的时间功能与闹钟功能，在RTCd的寄存器中保存的时间信息
 * 是以 UTC 时间保存的，要使用本地时间需要配置时区，当前配置的时
 * 区是东八区，即北京时间（CST）
 *
 * 在设置时间日期时使用 set_time() 与 set_date() 接口，设置的时
 * 间这两个接口内部会做时区转换
 *
 * 测试说明：
 * 基于庐山派开发板测试（01Studio 的开发板无法使用硬件RTC，
 * 因为没有接 int0/4 的上拉）
 *  RTC 为 K230 自带的 RTC
 * RTC 的时钟源为外部 32.768KHz 晶振
 * 在测试终端运行该测试后，会分别进行 test_rtc_set(),
 * test_rtc_alarm() 与 test_rtc_interface() 三个测试。
 * 其中 test_rtc_set() 会通过 set_time() 与 set_date() 设置时间，
 * 注意设置的时间需要为本地时间，内部会转换成 UTC 时间，然后调用
 * drv_rtc.c 内的接口设置到 RTC 寄存器中；
 * test_rtc_alarm() 会设置一个 5 秒后的闹钟时间，并注册一个闹钟
 * 中断回调函数，同样用户设置的闹钟时间为本地时间，内部会转换成UTC
 * 时间然后保存进 RTC 中；
 * test_rtc_interface() 会测试读写 RTC 的接口，写 RTC 时同样需要
 * 提供本地时间，读出来后需要转换成本地时间（如果有需要）。
 */

#define RTC_NAME       "rtc"

static void test_rtc_set(void)
{
    rt_err_t ret = RT_EOK;
    time_t now;
    uint32_t i;
    rt_device_t rtc_dev = RT_NULL;

    LOG_I("rtc set time test\n");
    rtc_dev = rt_device_find(RTC_NAME);
    uassert_not_null(rtc_dev);
    ret = rt_device_open(rtc_dev, RT_DEVICE_OFLAG_RDWR);
    uassert_int_equal(ret, RT_EOK);
    ret = set_time(23, 59, 59);
    uassert_int_equal(ret, RT_EOK);
    ret = set_date(2025, 9, 16);
    uassert_int_equal(ret, RT_EOK);
    rt_thread_mdelay(500);
    /* 设置完时间后打印10次时间 */
    for (i=0; i<10; i++)
    {
        now = time(RT_NULL);
        LOG_I("%s\n", ctime(&now));
        rt_thread_mdelay(1000);
    }

    rt_device_close(rtc_dev);
}

static void test_rtc_alarm_callback(void)
{
    LOG_I("rtc alarm triggered!\n");
}

static void test_rtc_alarm(void)
{
    rt_err_t ret = RT_EOK;
    time_t now;
    uint32_t i;
    struct tm p_tm;
    rt_device_t rtc_dev = RT_NULL;
    struct rt_alarm *alarm = RT_NULL;
    rtc_alarm_setup_t setup;

    LOG_I("rtc alarm test\n");
    rtc_dev = rt_device_find(RTC_NAME);
    uassert_not_null(rtc_dev);
    ret = rt_device_open(rtc_dev, RT_DEVICE_OFLAG_RDWR);
    uassert_int_equal(ret, RT_EOK);
    ret = set_time(23, 59, 59);
    uassert_int_equal(ret, RT_EOK);
    ret = set_date(2025, 9, 16);
    uassert_int_equal(ret, RT_EOK);
    rt_thread_mdelay(500);
    now = time(RT_NULL);
    LOG_I("%s\n", ctime(&now));
    now += 5; //alarm after 5s
    localtime_r(&now, &p_tm);

    setup.flag = RTC_INT_ALARM_MINUTE | RTC_INT_ALARM_SECOND;
    setup.tm.tm_year = p_tm.tm_year;
    setup.tm.tm_mon = p_tm.tm_mon;
    setup.tm.tm_mday = p_tm.tm_mday;
    setup.tm.tm_wday = p_tm.tm_wday;
    setup.tm.tm_hour = p_tm.tm_hour;
    setup.tm.tm_min = p_tm.tm_min;
    setup.tm.tm_sec = p_tm.tm_sec;

    rt_device_control(rtc_dev, RT_DEVICE_CTRL_RTC_SET_CALLBACK, &test_rtc_alarm_callback); //set rtc intr callback
    rt_device_control(rtc_dev, RT_DEVICE_CTRL_RTC_SET_ALARM, &setup);   //set alarm time
    rt_memset(&p_tm, 0, sizeof(p_tm));
    rt_device_control(rtc_dev, RT_DEVICE_CTRL_RTC_GET_ALARM, &p_tm);   //get alarm time
    now = timegm(&p_tm);
    LOG_I("get alarm time: %s\n", ctime(&now));

    for (i=0; i<10; i++)
    {
        now = time(RT_NULL);
        LOG_I("%s\n", ctime(&now));
        rt_thread_mdelay(1000);
    }
    rt_device_control(rtc_dev, RT_DEVICE_CTRL_RTC_STOP_ALARM, RT_NULL); //stop alarm

    rt_device_close(rtc_dev);
}

static void test_rtc_interface(void)
{
    rt_err_t ret = RT_EOK;
    uint32_t i;
    rt_device_t rtc_dev = RT_NULL;
    time_t now;
    struct tm tm;

    LOG_I("rtc interface test\n");
    rtc_dev = rt_device_find(RTC_NAME);
    uassert_not_null(rtc_dev);
    ret = rt_device_open(rtc_dev, RT_DEVICE_OFLAG_RDWR);
    uassert_int_equal(ret, RT_EOK);

    LOG_I("write rtc\n");
    tm.tm_year = 2025 - 1900;
    tm.tm_mon = 9 - 1;
    tm.tm_mday = 16;
    tm.tm_wday = 2;
    tm.tm_hour = 23;
    tm.tm_min = 59;
    tm.tm_sec = 59;
    rt_device_write(rtc_dev, RT_NULL, (void*)&tm, sizeof(tm));
    rt_thread_mdelay(500);

    /* 设置完时间后打印10次时间 */
    for (i=0; i<10; i++)
    {
        now = time(RT_NULL);
        LOG_I("[sys]:%s\n", ctime(&now));
        rt_thread_mdelay(1000);
    }

    LOG_I("read rtc\n");
    for (i=0; i<10; i++)
    {
        rt_device_read(rtc_dev, RT_NULL, (void*)&now, sizeof(now));
        LOG_I("[read]: %s\n", ctime(&now));
        rt_thread_mdelay(1000);
    }

    rt_device_close(rtc_dev);
}

static void test_rtc(void)
{
    test_rtc_set();
    test_rtc_alarm();
    test_rtc_interface();
}

static void testcase(void)
{
    LOG_I("This is a rtc test case.\n");
    UTEST_UNIT_RUN(test_rtc);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}
UTEST_TC_EXPORT(testcase, "bsp.k230.drivers.rtc", utest_tc_init, utest_tc_cleanup, 100);
