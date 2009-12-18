/*
 * File      : rtc.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-04-26     yi.qiu       first version
 */

#include "rtc.h"

/**
 * This function access to rtc
 */
rt_inline void rt_hw_rtc_access(int a)
{
	switch (a)
	{
	case RTC_ENABLE:
		RTCCON |= 0x01;
		break;

	case RTC_DISABLE:
		RTCCON &= ~0x01;
		break;
	}
}

rt_inline rt_uint32_t BCD2BIN(rt_uint8_t n)
{
        return ((((n >> 4) & 0x0F) * 10) + (n & 0x0F));
}

rt_inline rt_uint8_t BIN2BCD(rt_uint32_t n)
{
        return (((n / 10) << 4) | (n % 10));
}

/**
 * This function get rtc time
 */
void rt_hw_rtc_get (struct rtc_time *tmp)
{
	rt_uint8_t sec, min, hour, mday, wday, mon, year;
	rt_uint8_t a_sec,a_min, a_hour, a_date, a_mon, a_year, a_armed;

	/* enable access to RTC registers */
	rt_hw_rtc_access(RTC_ENABLE);

	/* read RTC registers */
	do
	{
		sec = BCDSEC;
		min = BCDMIN;
		hour = BCDHOUR;
		mday = BCDDATE;
		wday = BCDDAY;
		mon = BCDMON;
		year = BCDYEAR;
        } while (sec != BCDSEC);

	/* read ALARM registers */
	a_sec = ALMSEC;
	a_min = ALMMIN;
	a_hour = ALMHOUR;
	a_date = ALMDATE;
	a_mon = ALMMON;
	a_year = ALMYEAR;
	a_armed = RTCALM;

	/* disable access to RTC registers */
	rt_hw_rtc_access(RTC_DISABLE);

#ifdef RTC_DEBUG
	rt_kprintf ( "Get RTC year: %02x mon/cent: %02x mday: %02x wday: %02x "
		"hr: %02x min: %02x sec: %02x\n",
		year, mon, mday, wday,
		hour, min, sec);
	rt_kprintf ( "Alarms: %02x: year: %02x month: %02x date: %02x hour: %02x min: %02x sec: %02x\n",
		a_armed,
		a_year, a_mon, a_date,
		a_hour, a_min, a_sec);
#endif

	tmp->tm_sec  = BCD2BIN(sec  & 0x7F);
	tmp->tm_min  = BCD2BIN(min  & 0x7F);
	tmp->tm_hour = BCD2BIN(hour & 0x3F);
	tmp->tm_mday = BCD2BIN(mday & 0x3F);
	tmp->tm_mon  = BCD2BIN(mon & 0x1F);
	tmp->tm_year = BCD2BIN(year);
	tmp->tm_wday = BCD2BIN(wday & 0x07);
	if(tmp->tm_year < 70) tmp->tm_year += 2000;
	else tmp->tm_year += 1900;
	tmp->tm_yday = 0;
	tmp->tm_isdst = 0;
#ifdef RTC_DEBUG
	rt_kprintf ( "Get DATE: %4d-%02d-%02d (wday=%d)  TIME: %2d:%02d:%02d\n",
		tmp->tm_year, tmp->tm_mon, tmp->tm_mday, tmp->tm_wday,
		tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
#endif
}

/**
 * This function set rtc time
 */
void rt_hw_rtc_set (struct rtc_time *tmp)
{
	rt_uint8_t sec, min, hour, mday, wday, mon, year;

#ifdef RTC_DEBUG
	rt_kprintf ( "Set DATE: %4d-%02d-%02d (wday=%d)  TIME: %2d:%02d:%02d\n",
		tmp->tm_year, tmp->tm_mon, tmp->tm_mday, tmp->tm_wday,
		tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
#endif
	year = BIN2BCD(tmp->tm_year % 100);
	mon = BIN2BCD(tmp->tm_mon);
	wday = BIN2BCD(tmp->tm_wday);
	mday = BIN2BCD(tmp->tm_mday);
	hour = BIN2BCD(tmp->tm_hour);
	min = BIN2BCD(tmp->tm_min);
	sec = BIN2BCD(tmp->tm_sec);

	/* enable access to RTC registers */
	rt_hw_rtc_access(RTC_ENABLE);

	/* write RTC registers */
	BCDSEC = sec;
	BCDMIN = min;
	BCDHOUR = hour;
	BCDDATE = mday;
	BCDDAY = wday;
	BCDMON = mon;
	BCDYEAR = year;

	/* disable access to RTC registers */
	rt_hw_rtc_access(RTC_DISABLE);
}

/**
 * This function reset rtc
 */
void rt_hw_rtc_reset (void)
{
	RTCCON = (RTCCON & ~0x06) | 0x08;
	RTCCON &= ~(0x08|0x01);
}

