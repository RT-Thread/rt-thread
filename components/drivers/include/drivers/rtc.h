/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-10-10     aozima       first version.
 * 2021-06-11     iysheng      implement RTC framework V2.0
 * 2021-07-30     Meco Man     move rtc_core.h to rtc.h
 * 2022-04-05     tyx          add timestamp function
 */

#ifndef __RTC_H__
#define __RTC_H__

#include <rtdef.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RT_DEVICE_CTRL_RTC_GET_TIME     (RT_DEVICE_CTRL_BASE(RTC) + 0x01)              /**< get second time */
#define RT_DEVICE_CTRL_RTC_SET_TIME     (RT_DEVICE_CTRL_BASE(RTC) + 0x02)              /**< set second time */
#define RT_DEVICE_CTRL_RTC_GET_TIMEVAL  (RT_DEVICE_CTRL_BASE(RTC) + 0x03)              /**< get timeval for gettimeofday */
#define RT_DEVICE_CTRL_RTC_SET_TIMEVAL  (RT_DEVICE_CTRL_BASE(RTC) + 0x04)              /**< set timeval for gettimeofday */
#define RT_DEVICE_CTRL_RTC_GET_ALARM    (RT_DEVICE_CTRL_BASE(RTC) + 0x05)              /**< get alarm */
#define RT_DEVICE_CTRL_RTC_SET_ALARM    (RT_DEVICE_CTRL_BASE(RTC) + 0x06)              /**< set alarm */
#define RT_DEVICE_CTRL_RTC_GET_TIMESPEC (RT_DEVICE_CTRL_BASE(RTC) + 0x07)              /**< get timespec for clock_gettime */
#define RT_DEVICE_CTRL_RTC_SET_TIMESPEC (RT_DEVICE_CTRL_BASE(RTC) + 0x08)              /**< set timespec for clock_settime */
#define RT_DEVICE_CTRL_RTC_GET_TIMERES  (RT_DEVICE_CTRL_BASE(RTC) + 0x09)              /**< get resolution for clock_getres */

/* used for alarm function */
struct rt_rtc_wkalarm
{
    rt_bool_t  enable;               /* 0 = alarm disabled, 1 = alarm enabled */
    rt_int32_t tm_sec;               /* alarm at tm_sec */
    rt_int32_t tm_min;               /* alarm at tm_min */
    rt_int32_t tm_hour;              /* alarm at tm_hour */
    rt_int32_t tm_mday;              /* alarm at tm_mday */
    rt_int32_t tm_mon;               /* alarm at tm_mon */
    rt_int32_t tm_year;              /* alarm at tm_year */
};

struct rt_rtc_ops
{
    rt_err_t (*init)(void);
    rt_err_t (*get_secs)(time_t *sec);
    rt_err_t (*set_secs)(time_t *sec);
    rt_err_t (*get_alarm)(struct rt_rtc_wkalarm *alarm);
    rt_err_t (*set_alarm)(struct rt_rtc_wkalarm *alarm);
    rt_err_t (*get_timeval)(struct timeval *tv);
    rt_err_t (*set_timeval)(struct timeval *tv);
};

typedef struct rt_rtc_device
{
    struct rt_device parent;
    const struct rt_rtc_ops *ops;
} rt_rtc_dev_t;

rt_err_t rt_hw_rtc_register(rt_rtc_dev_t  *rtc,
                            const char    *name,
                            rt_uint32_t    flag,
                            void          *data);

rt_err_t set_date(rt_uint32_t year, rt_uint32_t month, rt_uint32_t day);
rt_err_t set_time(rt_uint32_t hour, rt_uint32_t minute, rt_uint32_t second);
rt_err_t set_timestamp(time_t timestamp);
rt_err_t get_timestamp(time_t *timestamp);

#ifdef RT_USING_SYSTEM_WORKQUEUE
rt_err_t rt_soft_rtc_sync(void);
rt_err_t rt_soft_rtc_set_source(const char *name);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __RTC_H__ */
