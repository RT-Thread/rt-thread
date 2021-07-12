/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-11     iysheng      first version.
 */

#ifndef __RTC_CORE_H__
#define __RTC_CORE_H__

#include <rtthread.h>

#define RT_DEVICE_CTRL_RTC_GET_TIME     0x10            /**< get second time */
#define RT_DEVICE_CTRL_RTC_SET_TIME     0x11            /**< set second time */
#define RT_DEVICE_CTRL_RTC_GET_TIME_US  0x12            /**< get microsecond time */
#define RT_DEVICE_CTRL_RTC_SET_TIME_US  0x13            /**< set microsecond time */
#define RT_DEVICE_CTRL_RTC_GET_ALARM    0x14            /**< get alarm */
#define RT_DEVICE_CTRL_RTC_SET_ALARM    0x15            /**< set alarm */

struct rt_rtc_ops
{
    rt_err_t (*init)(void);
    rt_err_t (*get_secs)(void *arg);
    rt_err_t (*set_secs)(void *arg);
    rt_err_t (*get_alarm)(void *arg);
    rt_err_t (*set_alarm)(void *arg);
    rt_err_t (*get_usecs)(void *arg);
    rt_err_t (*set_usecs)(void *arg);
};

typedef struct rt_rtc_device
{
    struct rt_device parent;
    const struct rt_rtc_ops *ops;
} rt_rtc_dev_t;

rt_err_t rt_rtc_dev_register(rt_rtc_dev_t *rtc,
                            const char    *name,
                            rt_uint32_t    flag,
                            void          *data);

#endif /* __RTC_CORE_H__ */
