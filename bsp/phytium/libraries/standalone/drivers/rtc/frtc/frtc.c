/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: frtc.c
 * Date: 2021-08-25 14:53:42
 * LastEditTime: 2021-08-26 09:02:33
 * Description:  This file is for user API implmentation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   Wangxiaodong   2021/8/26  first commit
 */

#include <string.h>
#include "fgeneric_timer.h"
#include "ftypes.h"
#include "fassert.h"

#include "fdebug.h"
#include "fsleep.h"

#include "frtc.h"
#include "frtc_hw.h"


#define FRTC_DEBUG_TAG "RTC"
#define FRTC_ERROR(format, ...)     FT_DEBUG_PRINT_E(FRTC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FRTC_INFO(format, ...)      FT_DEBUG_PRINT_I(FRTC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FRTC_DEBUG(format, ...)     FT_DEBUG_PRINT_D(FRTC_DEBUG_TAG, format, ##__VA_ARGS__)

#define FRTC_IS_LEAP_YEAR(year)     ((((year) % 4 == 0 ) && ((year) %100 != 0))||( (year) % 400 == 0))

/**
 * @name: FRtcCheckDateTime
 * @msg: check if the date year, month, day, hour, ... is valid
 * @return {u32} whether the date is valid
 * @param  {FRtcDate} *date, pointer to a FRtcDate structure that contains year, month and day
 */
static FError FRtcCheckDateTime(const FRtcDateTime *date_time)
{
    FASSERT(date_time != NULL);
    u8 w_hour = date_time->hour;
    u8 w_minute = date_time->minute;
    u8 w_second = date_time->second;
    u8 w_year = date_time->year;
    u8 w_month = date_time->month;
    u8 w_day = date_time->mday;
    u8 days_of_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; /* 月份天数表 */

    /* 闰年2月+1天 */
    if ((w_month == 2) && (FRTC_IS_LEAP_YEAR(w_year)))
    {
        days_of_month[w_month - 1] += 1;
    }

    /* 判断月份日期是否合法 */
    if ((w_month > 12) || (w_month < 1) || (w_day > days_of_month[w_month - 1]) || (w_day < 1))
    {
        FRTC_ERROR("Invalid input date: month: %d, day: %d", w_month, w_day);
        return FRTC_ERR_DATE_INVALID;
    }

    /* 判断时分秒是否合法 */
    if ((w_hour > 23) || (w_minute > 59) || (w_second > 59))
    {
        FRTC_ERROR("Invalid input time: hour: %d, minute: %d, second: %d",
                   w_hour, w_minute, w_second);
        return FRTC_ERR_TIME_INVALID;
    }

    return FRTC_SUCCESS;
}

/**
 * @name: FRtcSetDateTime
 * @msg: Set current time in FRtcDateTime
 * @return {u32} whether the time setting is successful
 * @param {FRtcCtrl} *pctrl, pointer to a FRtcCtrl structure that contains
  *                the configuration information for the specified rtc module.
 * @param {FRtcDate} *date, pointer to a FRtcDate structure that contains year, month and day
 * @param {FRtcTime} *time, pointer to a FRtcTime structure that contains hour, minute and second
 */
FError FRtcSetDateTime(FRtcCtrl *pctrl, const FRtcDateTime *date_time)
{
    FASSERT(pctrl != NULL);
    FASSERT(date_time != NULL);
    uintptr base_addr = pctrl->config.control_base_addr;
    struct tm tm;
    time_t t;
    u32 ret = 0;

    ret = FRtcCheckDateTime(date_time);
    if (ret != FRTC_SUCCESS)
    {
        return ret;
    }

    tm.tm_sec = date_time->second;
    tm.tm_min = date_time->minute;
    tm.tm_hour = date_time->hour;
    /*  tm->tm_wday  */
    tm.tm_mday = date_time->mday;
    tm.tm_mon  = (date_time->month - 1);
    tm.tm_year = (date_time->year - 1900);

    t = mktime(&tm);

    FRTC_WRITE_AES_SEL(base_addr, FRTC_AES_SEL_COUNTER);

    /* write low 32 bit first */
    FRTC_WRITE_CLR_LOW(base_addr, 0);

    /* write low 32 bit next */
    FRTC_WRITE_CLR(base_addr, t);

    return FT_SUCCESS;
}

/**
 * @name: FRtcGetDateTime
 * @msg: Get current time in FRtcDateTime
 * @return {*}
 * @param {FRtcCtrl} *pctrl
 * @param {FRtcDateTime} *date_time
 */
FError FRtcGetDateTime(FRtcCtrl *pctrl, FRtcDateTime *date_time)
{
    FASSERT(pctrl != NULL);
    FASSERT(date_time != NULL);
    time_t seconds = 0;
    struct tm *time_p;

    FRtcReadTimeStamp(pctrl, &seconds, NULL);
    time_p = localtime(&seconds);

    date_time->year = time_p->tm_year + 1900;
    date_time->month = time_p->tm_mon + 1;
    date_time->mday = time_p->tm_mday;
    date_time->hour = time_p->tm_hour;
    date_time->minute = time_p->tm_min;
    date_time->second = time_p->tm_sec;

    return FRTC_SUCCESS;
}

/**
 * @name: FRtcReadTimeStamp
 * @msg: Read time stamp in seconds and milliseconds
 * @return {*} none
 * @param {FRtcCtrl} *pctrl
 * @param {time_t} *sec_p
 * @param {time_t} *msec_p
 */
void FRtcReadTimeStamp(FRtcCtrl *pctrl, time_t *sec_p, time_t *msec_p)
{
    FASSERT(pctrl != NULL);
    time_t sec = 0;
    u32 msec = 0;
    u32 tick = 0;

    uintptr base_addr = pctrl->config.control_base_addr;

    /* tick = 1/32.768k = 0.03ms = 30us, delay more than 4 ticks */
    fsleep_microsec(FRTC_COUNTER_DELAY);

    /* write AES_SEL register, to read CCVR and CDR register */
    FRTC_WRITE_AES_SEL(base_addr, FRTC_AES_SEL_COUNTER);

    /* tick = 1/32.768k = 0.03ms = 30us, delay more than 4 ticks */
    fsleep_microsec(FRTC_COUNTER_DELAY);

    /* read high 32 bit first */
    sec = FRTC_READ_CCVR(base_addr);

    /* read low 32 bit next, The lower 15 bits are valid */
    tick = (FRTC_READ_CDR_LOW(base_addr) & FRTC_COUNTER_LB_MASK);

    /* convert 15 bits tick to milliseconds, count by 32.768k */
    msec = ((tick * 1000) >> FRTC_COUNTER_HB_OFFSET);

    if (sec_p)
    {
        *sec_p = sec;
    }

    if (msec_p)
    {
        *msec_p = msec;
    }

    return;
}

/**
 * @name: FRtcCfgInitialize
 * @msg: Initialize RTC ctrl
 * @return {*}
 * @param {FRtcCtrl} *instance_p
 * @param {FRtcConfig} *input_config_p
 */
FError FRtcCfgInitialize(FRtcCtrl *instance_p, const FRtcConfig *input_config_p)
{
    FASSERT(instance_p && input_config_p);
    uintptr base_addr = instance_p->config.control_base_addr;

    instance_p->config = *input_config_p;
    instance_p->is_ready = FT_COMPONENT_IS_READY;

    return FRTC_SUCCESS;
}

/**
 * @name: FRtcCfgDeInitialize
 * @msg: DeInitialization function for the device instance
 * @param {FRtcCtrl} *instance_p FRTC驱动控制数据
 * @return {*}
 */
void FRtcCfgDeInitialize(FRtcCtrl *pctrl)
{
    FASSERT(pctrl);

    pctrl->is_ready = 0;
    memset(pctrl, 0, sizeof(*pctrl));

    return;
}