/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __DRV_RTC_H__
#define __DRV_RTC_H__

#include <rtthread.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

struct ns800_rtc_ops
{
    rt_err_t (*init)(void *user_data);
    rt_err_t (*get_time)(void *user_data, struct tm *time);
    rt_err_t (*set_time)(void *user_data, const struct tm *time);
};

rt_err_t ns800_rtc_register(const char *name,
                            const struct ns800_rtc_ops *ops,
                            void *user_data);
int rt_hw_rtc_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_RTC_H__ */

