#ifndef __RT_HW_SERIAL_H__
#define __RT_HW_SERIAL_H__

#include <rthw.h>
#include <rtthread.h>

#include "s3c24x0.h"

#define RTC_DEBUG

#define	RTC_ENABLE()		    (RTCCON |=  0x01)	//RTC read and write enable
#define	RTC_DISABLE()		    (RTCCON &= ~0x01)	//RTC read and write disable

#define BCD2BIN(n)			    (((((n) >> 4) & 0x0F) * 10) + ((n) & 0x0F))
#define BIN2BCD(n)			    ((((n) / 10) << 4) | ((n) % 10))

#define LEAPS_THRU_END_OF(y)    ((y)/4 - (y)/100 + (y)/400)
#define LEAP_YEAR(year) 	    ((!(year % 4) && (year % 100)) || !(year % 400))

#define FEBRUARY		        2
#define	STARTOFTIME		        1970
#define SECDAY			        86400L
#define SECYR			        (SECDAY * 365)
#define	days_in_year(a)		    (LEAP_YEAR(a) ? 366 : 365)
#define	days_in_month(a)	    (month_days[(a) - 1])

static unsigned char month_days[] = 
{
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

struct rtc_time 
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

void rt_hw_rtc_get (struct rtc_time *tmp);
void rt_hw_rtc_set (struct rtc_time *tmp);
void rt_hw_rtc_reset (void);
void GregorianDay (struct rtc_time *);
void rt_rtc_time_to_tm(rt_uint32_t tim, struct rtc_time *tm);

#endif
