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

#include <rtthread.h>
#include <time.h>
#include <s3c24x0.h>

#define BCD2BIN(n)	(((((n) >> 4) & 0x0F) * 10) + ((n) & 0x0F))
#define BIN2BCD(n)	((((n) / 10) << 4) | ((n) % 10))

/**
 * This function get rtc time
 */
void rt_hw_rtc_get(struct tm *ti)
{
	rt_uint8_t sec, min, hour, mday, wday, mon, year;

	/* enable access to RTC registers */
	RTCCON |= 0x01;

	/* read RTC registers */
	do
	{
		sec 		= BCDSEC;
		min 		= BCDMIN;
		hour 	= BCDHOUR;
		mday	= BCDDATE;
		wday 	= BCDDAY;
		mon 	= BCDMON;
		year 	= BCDYEAR;
        } while (sec != BCDSEC);

	/* disable access to RTC registers */
	RTCCON &= ~0x01;

	ti->tm_sec  	= BCD2BIN(sec  & 0x7F);
	ti->tm_min  	= BCD2BIN(min  & 0x7F);
	ti->tm_hour 	= BCD2BIN(hour & 0x3F);
	ti->tm_mday 	= BCD2BIN(mday & 0x3F);
	ti->tm_mon  	= BCD2BIN(mon & 0x1F);
	ti->tm_year 	= BCD2BIN(year);
	ti->tm_wday 	= BCD2BIN(wday & 0x07);
	ti->tm_yday 	= 0;
	ti->tm_isdst 	= 0;
}

/**
 * This function set rtc time
 */
void rt_hw_rtc_set(struct tm *ti)
{
	rt_uint8_t sec, min, hour, mday, wday, mon, year;

	year 	= BIN2BCD(ti->tm_year);
	mon 	= BIN2BCD(ti->tm_mon);
	wday 	= BIN2BCD(ti->tm_wday);
	mday 	= BIN2BCD(ti->tm_mday);
	hour 	= BIN2BCD(ti->tm_hour);
	min 		= BIN2BCD(ti->tm_min);
	sec 		= BIN2BCD(ti->tm_sec);

	/* enable access to RTC registers */
	RTCCON |= 0x01;

	/* write RTC registers */
	BCDSEC 		= sec;
	BCDMIN 		= min;
	BCDHOUR 	= hour;
	BCDDATE 	= mday;
	BCDDAY 		= wday;
	BCDMON 	= mon;
	BCDYEAR 	= year;

	/* disable access to RTC registers */
	RTCCON &= ~0x01;
}

/**
 * This function reset rtc
 */
void rt_hw_rtc_reset (void)
{
	RTCCON = (RTCCON & ~0x06) | 0x08;
	RTCCON &= ~(0x08|0x01);
}

static struct rt_device rtc;
static rt_err_t rt_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_size_t rt_rtc_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	return 0;
}

static rt_err_t rt_rtc_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	struct tm* ti;
	RT_ASSERT(dev != RT_NULL);

	ti = (struct tm*)args;
	switch (cmd)
	{
	case RT_DEVICE_CTRL_RTC_GET_TIME:
		/* read device */
		rt_hw_rtc_get(ti);
		break;

	case RT_DEVICE_CTRL_RTC_SET_TIME:
		/* write device */
		rt_hw_rtc_set(ti);
		break;
	}

	return RT_EOK;
}

void rt_hw_rtc_init(void)
{
	rtc.type	= RT_Device_Class_RTC;

	/* register rtc device */
	rtc.init 	= RT_NULL;
	rtc.open 	= rt_rtc_open;
	rtc.close	= RT_NULL;
	rtc.read 	= rt_rtc_read;
	rtc.write	= RT_NULL;
	rtc.control = rt_rtc_control;
	
	/* no private */
	rtc.private = RT_NULL;
	
	rt_device_register(&rtc, "rtc", RT_DEVICE_FLAG_RDWR);

	return;
}

time_t time(time_t* t)
{
	rt_device_t device;
	struct tm ti;
	time_t time;
	
	device = rt_device_find("rtc");
	if (device != RT_NULL)
	{
		rt_device_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &ti);
		if (t != RT_NULL) 
		{
			time = mktime(&ti);
			*t = time;
		}	
	}
	
	return time;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void set_date(rt_uint32_t year, rt_uint32_t month, rt_uint32_t day)
{
	struct tm ti;
	rt_device_t device;
		
	device = rt_device_find("rtc");
	if (device != RT_NULL)
	{
		rt_rtc_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &ti);
		ti.tm_year 	= year - 1900;
		ti.tm_mon 	= month - 1;
		ti.tm_mday 	= day;
		rt_rtc_control(device, RT_DEVICE_CTRL_RTC_SET_TIME, &ti);
	}
}
FINSH_FUNCTION_EXPORT(set_date, set date)

void set_time(rt_uint32_t hour, rt_uint32_t minute, rt_uint32_t second)
{
	struct tm ti;
	rt_device_t device;
		
	device = rt_device_find("rtc");
	if (device != RT_NULL)
	{
		rt_rtc_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &ti);
		ti.tm_hour	= hour;
		ti.tm_min		= minute;
		ti.tm_sec 	= second;
		rt_rtc_control(device, RT_DEVICE_CTRL_RTC_SET_TIME, &ti);
	}
}
FINSH_FUNCTION_EXPORT(set_time, set second)

void list_date()
{
	time_t now;
	
	time(&now);
	rt_kprintf("%s\n", ctime(&now));
}
FINSH_FUNCTION_EXPORT(list_date, set date)
#endif

