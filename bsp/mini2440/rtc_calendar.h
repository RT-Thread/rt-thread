/*
 * File      : rtc_calendar.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-02-10     Gary Lee     first implementation
 */

#ifndef __RTCLEAP_H__
#define __RTCLEAP_H__

#include <rthw.h>
#include <rtthread.h>

#include "s3c24x0.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_YEAR_MONTH_DAY  (DEFAULT_YEAR*10000+DEFAULT_MONTH*100+DEFAULT_DAY)
#define DEFAULT_YEAR			2010
#define DEFAULT_MONTH			02
#define DEFAULT_DAY				10

rt_int32_t  	rt_rtc_isleap(rt_uint32_t year);
rt_int32_t   	rt_rtc_week_of_newyears_day(rt_uint32_t year);
void 			rt_calendar(void);
void 			rt_rtc_print_calendar(rt_uint32_t year);
rt_int32_t 		rt_rtc_month_day_num(rt_int32_t month, rt_int32_t leapyn);
rt_int32_t 		rt_rtc_space_days(rt_int32_t month, rt_int32_t year);
rt_int32_t 		rt_rtc_weekday_month(rt_int32_t month, rt_int32_t year);
void 			rt_rtc_print_common_fmt(rt_uint8_t month, rt_uint8_t weekday, rt_uint8_t leapyear);
void 			rt_rtc_print_one_month(rt_int32_t month, rt_int32_t year);
void 			rt_rtc_weekdate_calculate(void);

#ifdef __cplusplus
}
#endif

#endif /*__MMU_H__*/
