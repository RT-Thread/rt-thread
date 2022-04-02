/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-10-10     aozima       first version.
 * 2021-06-11     iysheng      implement RTC framework V2.0
 * 2021-07-30     Meco Man     move rtc_core.h to rtc.h
 */

#ifndef __RTC_H__
#define __RTC_H__

#include <rtdef.h>

#define RT_DEVICE_CTRL_RTC_GET_TIME     (RT_DEVICE_CTRL_BASE(RTC) + 0x01)              /**< get second time */
#define RT_DEVICE_CTRL_RTC_SET_TIME     (RT_DEVICE_CTRL_BASE(RTC) + 0x02)              /**< set second time */
#define RT_DEVICE_CTRL_RTC_GET_TIMEVAL  (RT_DEVICE_CTRL_BASE(RTC) + 0x03)              /**< get timeval for gettimeofday */
#define RT_DEVICE_CTRL_RTC_SET_TIMEVAL  (RT_DEVICE_CTRL_BASE(RTC) + 0x04)              /**< set timeval for gettimeofday */
#define RT_DEVICE_CTRL_RTC_GET_ALARM    (RT_DEVICE_CTRL_BASE(RTC) + 0x05)              /**< get alarm */
#define RT_DEVICE_CTRL_RTC_SET_ALARM    (RT_DEVICE_CTRL_BASE(RTC) + 0x06)              /**< set alarm */

struct rt_rtc_ops
{
    rt_err_t (*init)(void);
    rt_err_t (*get_secs)(void *arg);
    rt_err_t (*set_secs)(void *arg);
    rt_err_t (*get_alarm)(void *arg);
    rt_err_t (*set_alarm)(void *arg);
    rt_err_t (*get_timeval)(void *arg);
    rt_err_t (*set_timeval)(void *arg);
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

#endif /* __RTC_H__ */
