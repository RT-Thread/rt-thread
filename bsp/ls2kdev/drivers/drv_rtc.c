/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 * Copyright (c) 2020, Du Huanpeng <548708880@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-30     armink       the first version
 * 2020-06-23     Du Huanpeng  based on components/drivers/rtc/soft_rtc.c
 */


#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <rtthread.h>
#include "ls2k1000.h"

#ifdef RT_USING_RTC

struct loongson_rtc {
    rt_uint32_t sys_toytrim;
    rt_uint32_t sys_toywrite0;
    rt_uint32_t sys_toywrite1;
    rt_uint32_t sys_toyread0;
    rt_uint32_t sys_toyread1;
    rt_uint32_t sys_toymatch0;
    rt_uint32_t sys_toymatch1;
    rt_uint32_t sys_toymatch2;
    rt_uint32_t sys_rtcctrl;
    rt_uint32_t __pad4[3];
    rt_uint32_t __pad5[4];
    rt_uint32_t sys_rtctrim;
    rt_uint32_t sys_rtcwrite0;
    rt_uint32_t sys_rtcread0;
    rt_uint32_t sys_rtcmatch0;
    rt_uint32_t sys_rtcmatch1;
    rt_uint32_t sys_rtcmatch2;
};

/* bit field helpers. */
#define __M(n)               (~(~0<<(n)))
#define __RBF(number, n)     ((number)&__M(n))
#define __BF(number, n, m)   __RBF((number>>m), (n-m+1))
#define BF(number, n, m)     (m<n ? __BF(number, n, m) : __BF(number, m, n))

struct rtctime {
    rt_uint32_t sys_toyread0;
    rt_uint32_t sys_toyread1;
    rt_uint32_t sys_rtcread0;
};
typedef struct rtctime rtctime_t;

struct tm *localrtctime(const rtctime_t *rtctp)
{
    static struct tm time;
    int msec;

    msec = BF(rtctp->sys_toyread0, 3, 0);
    msec *= 100;

    time.tm_sec   = BF(rtctp->sys_toyread0,  9,  4);
    time.tm_min   = BF(rtctp->sys_toyread0, 15, 10);
    time.tm_hour  = BF(rtctp->sys_toyread0, 20, 16);
    time.tm_mday  = BF(rtctp->sys_toyread0, 21, 25);
    time.tm_mon   = BF(rtctp->sys_toyread0, 26, 31);
    /* struct tm has three more members:
         time.tm_isdst
         time.tm_wday
         time.tm_yday
    */
    time.tm_mon -= 1;
    time.tm_year = rtctp->sys_toyread1;
    return &time;
}

rtctime_t mkrtctime(struct tm *tm)
{
    rtctime_t rtctm;
    struct tm tmptime;

    rtctm.sys_toyread0 <<= 31 - 26 + 1;
    rtctm.sys_toyread0  |= tm->tm_mon + 1;
    rtctm.sys_toyread0 <<= 25 - 21 + 1;
    rtctm.sys_toyread0  |= tm->tm_mday;
    rtctm.sys_toyread0 <<= 20 - 16 + 1;
    rtctm.sys_toyread0  |= tm->tm_hour;
    rtctm.sys_toyread0 <<= 15 - 10 + 1;
    rtctm.sys_toyread0  |= tm->tm_min;
    rtctm.sys_toyread0 <<= 9 - 4 + 1;
    rtctm.sys_toyread0  |= tm->tm_sec;
    /* Fixme: 0.1 second */
    rtctm.sys_toyread0 <<= 3 - 0 + 1;
    rtctm.sys_toyread0  |= 0;

    rtctm.sys_toyread1 = tm->tm_year;

    tmptime = *localrtctime(&rtctm);

    return rtctm;
}

static rt_err_t rt_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_size_t rt_rtc_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    return 0;
}

static rt_err_t rt_rtc_ioctl(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_ENOSYS;

    static int count = 0;

    struct loongson_rtc *hw_rtc;
    rtctime_t rtctm;
    struct tm time;
    struct tm tmptime;
    time_t *t;

    hw_rtc = dev->user_data;

    t = (time_t *)args;
    time = *localtime(t);

    rtctm.sys_toyread0 = hw_rtc->sys_toyread0;
    rtctm.sys_toyread1 = hw_rtc->sys_toyread1;
    rtctm.sys_rtcread0 = hw_rtc->sys_rtcread0;
    tmptime = *localrtctime(&rtctm);

    switch (cmd) {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        *t = mktime(&tmptime);
        break;
    case RT_DEVICE_CTRL_RTC_SET_TIME:
        tmptime.tm_hour = time.tm_hour;
        tmptime.tm_min  = time.tm_min;
        tmptime.tm_sec  = time.tm_sec;

        tmptime.tm_year = time.tm_year;
        tmptime.tm_mon  = time.tm_mon;
        tmptime.tm_mday = time.tm_mday;

        rtctm = mkrtctime(&tmptime);
        /* write to hw RTC */
        hw_rtc->sys_toywrite0 = rtctm.sys_toyread0;
        hw_rtc->sys_toywrite1 = rtctm.sys_toyread1;
        break;
    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        break;
    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        break;
    default:
        break;
    }

    return RT_EOK;
}

int rt_hw_rtc_init(void)
{
    static struct rt_device rtc = {
        .type      = RT_Device_Class_RTC,
        .init      = RT_NULL,
        .open      = rt_rtc_open,
        .close     = RT_NULL,
        .read      = rt_rtc_read,
        .write     = RT_NULL,
        .control   = rt_rtc_ioctl,
        .user_data = (void *)RTC_BASE,
    };
    rt_device_register(&rtc, "rtc", RT_DEVICE_FLAG_RDWR);
}

INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /*RT_USING_RTC*/
