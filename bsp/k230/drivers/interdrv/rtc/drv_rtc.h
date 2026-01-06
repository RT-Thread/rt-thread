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

#ifndef __DRV_RTC_H__
#define __DRV_RTC_H__
#include <stdint.h>
#include <drivers/dev_rtc.h>

#define RT_DEVICE_CTRL_RTC_SET_CALLBACK     0x44
#define RT_DEVICE_CTRL_RTC_STOP_ALARM       0x45
#define RT_DEVICE_CTRL_RTC_STOP_TICK        0x46
#define BIT(n)  (1 << n)

/* date register(reset value 0x10101, offset address 0x00) */
typedef struct _rtc_date
{
    uint32_t day : 5;
    uint32_t resv0 : 3;
    uint32_t month : 4;
    uint32_t resv1 : 4;
    uint32_t year_l : 7;
    uint32_t leap_year : 1;
    uint32_t year_h : 7;
    uint32_t resv2 : 1;
} __attribute__((packed, aligned(4))) rtc_date_t;

/* time register(reset value 0x00, offset address 0x04) */
typedef struct _rtc_time
{
    uint32_t second : 6;
    uint32_t resv0 : 2;
    uint32_t minute : 6;
    uint32_t resv1 : 2;
    uint32_t hour : 5;
    uint32_t resv2 : 3;
    uint32_t week : 3;
    uint32_t resv3 : 5;
} __attribute__((packed, aligned(4))) rtc_time_t;

/* alarm date register(reset value 0x10101, offset address 0x08) */
typedef struct _rtc_alarm_date
{
    uint32_t alarm_day : 5;
    uint32_t resv0 : 3;
    uint32_t alarm_month : 4;
    uint32_t resv1 : 4;
    uint32_t alarm_year_l : 7;
    uint32_t resv2 : 1;
    uint32_t alarm_year_h : 7;
    uint32_t resv3 : 1;
} __attribute__((packed, aligned(4))) rtc_alarm_date_t;

/* alarm time register(reset value 0x00, offset address 0x0C) */
typedef struct _rtc_alarm_time
{
    uint32_t alarm_second : 6;
    uint32_t resv0 : 2;
    uint32_t alarm_minute : 6;
    uint32_t resv1 : 2;
    uint32_t alarm_hour : 5;
    uint32_t resv2 : 3;
    uint32_t alarm_week : 3;
    uint32_t resv3 : 5;
} __attribute__((packed, aligned(4))) rtc_alarm_time_t;

/* count register(reset value 0x7FFF0000, offset address 0x10) */
typedef struct _rtc_count
{
    uint32_t curr_count : 15; /*!< RTC counter currunt value */
    uint32_t resv0 : 1;
    uint32_t sum_count : 15;   /*!< RTC counter max value */
    uint32_t resv1 : 1;
} __attribute__((packed, aligned(4))) rtc_count_t;

/* interrupt control register(reset value 0x00, offset address 0x14) */
typedef struct _rtc_int_ctrl
{
    uint32_t timer_w_en : 1;
    uint32_t timer_r_en : 1;
    uint32_t resv0 : 6;
    uint32_t tick_en : 1;
    uint32_t tick_sel : 4;
    uint32_t resv1 : 3;
    uint32_t alarm_en : 1;
    uint32_t alarm_clr : 1;
    uint32_t resv2 : 6;
    uint32_t second_cmp : 1;
    uint32_t minute_cmp : 1;
    uint32_t hour_cmp : 1;
    uint32_t week_cmp : 1;
    uint32_t day_cmp : 1;
    uint32_t month_cmp : 1;
    uint32_t year_cmp : 1;
    uint32_t resv3 : 1;
} __attribute__((packed, aligned(4))) rtc_int_ctrl_t;

/* rtc register */
typedef struct _rtc
{
    rtc_date_t date;
    rtc_time_t time;
    rtc_alarm_date_t alarm_date;
    rtc_alarm_time_t alarm_time;
    rtc_count_t count;
    rtc_int_ctrl_t int_ctrl;
} __attribute__((packed, aligned(4))) rtc_t;

typedef enum _rtc_tick_interrupt_mode_e
{
    RTC_INT_ALARM_YEAR = BIT(0),
    RTC_INT_ALARM_MONTH = BIT(1),
    RTC_INT_ALARM_DAY = BIT(2),
    RTC_INT_ALARM_WEEK = BIT(3),
    RTC_INT_ALARM_HOUR = BIT(4),
    RTC_INT_ALARM_MINUTE = BIT(5),
    RTC_INT_ALARM_SECOND = BIT(6),
    RTC_INT_TICK_YEAR = BIT(7),
    RTC_INT_TICK_MONTH,
    RTC_INT_TICK_DAY,
    RTC_INT_TICK_WEEK,
    RTC_INT_TICK_HOUR,
    RTC_INT_TICK_MINUTE,
    RTC_INT_TICK_SECOND,
    RTC_INT_TICK_S8,
    RTC_INT_TICK_S64,
} rtc_interrupt_mode_t;

typedef struct _rtc_alarm_setup
{
    rt_uint32_t flag;               /* alarm flag */
    struct tm tm;                   /* when will the alarm wake up user */
} rtc_alarm_setup_t;

#endif /* __DRV_RTC_H__ */
