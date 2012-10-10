/*
 * File      : rtc.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-10-10     aozima       first version.
 */

#ifndef RTC_H_INCLUDED
#define RTC_H_INCLUDED

extern rt_err_t set_date(rt_uint32_t year,
                         rt_uint32_t month,
                         rt_uint32_t day);

extern rt_err_t set_time(rt_uint32_t hour,
                         rt_uint32_t minute,
                         rt_uint32_t second);

#endif // RTC_H_INCLUDED
