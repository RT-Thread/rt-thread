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
 * 2009-04-26     yi.qiu       	first version
 * 2010-03-18     Gary Lee	add functions such as GregorianDay
 *                             		and rtc_time_to_tm
 * 2009-03-20     yi.qiu       	clean up
 */

#include <rtthread.h>
#include <time.h>
#include <s3c24x0.h>

// #define RTC_DEBUG

#define RTC_ENABLE		RTCCON |=  0x01;	/*RTC read and write enable */
#define RTC_DISABLE		RTCCON &= ~0x01;	/* RTC read and write disable */
#define BCD2BIN(n)		(((((n) >> 4) & 0x0F) * 10) + ((n) & 0x0F))
#define BIN2BCD(n)		((((n) / 10) << 4) | ((n) % 10))

/**
 * This function get rtc time
 */
void rt_hw_rtc_get(struct tm *ti)
{
	rt_uint8_t sec, min, hour, mday, wday, mon, year;

	/* enable access to RTC registers */
	RTCCON |= RTC_ENABLE;

	/* read RTC registers */
	do
	{
		sec 	= BCDSEC;
		min 	= BCDMIN;
		hour 	= BCDHOUR;
		mday	= BCDDATE;
		wday 	= BCDDAY;
		mon 	= BCDMON;
		year 	= BCDYEAR;
    } while (sec != BCDSEC);

#ifdef RTC_DEBUG
	rt_kprintf("sec:%x min:%x hour:%x mday:%x wday:%x mon:%x year:%x\n",
		sec, min, hour, mday, wday, mon, year);
#endif

	/* disable access to RTC registers */
	RTC_DISABLE

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

	year	= BIN2BCD(ti->tm_year);
	mon 	= BIN2BCD(ti->tm_mon);
	wday 	= BIN2BCD(ti->tm_wday);
	mday 	= BIN2BCD(ti->tm_mday);
	hour 	= BIN2BCD(ti->tm_hour);
	min 	= BIN2BCD(ti->tm_min);
	sec 	= BIN2BCD(ti->tm_sec);

	/* enable access to RTC registers */
	RTC_ENABLE

	do{
		/* write RTC registers */
		BCDSEC 		= sec;
		BCDMIN 		= min;
		BCDHOUR 	= hour;
		BCDDATE 	= mday;
		BCDDAY 		= wday;
		BCDMON 	= mon;
		BCDYEAR 	= year;
	}while (sec != BCDSEC);
	
	/* disable access to RTC registers */
	RTC_DISABLE
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
static rt_err_t rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
	RTC_ENABLE
	return RT_EOK;
}

static rt_err_t rtc_close(rt_device_t dev)
{
	RTC_DISABLE
	return RT_EOK;
}

static rt_size_t rtc_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	return RT_EOK;
}

static rt_err_t rtc_control(rt_device_t dev, int cmd, void *args)
{
	struct tm tm, *tm_ptr;
    time_t *time;
	RT_ASSERT(dev != RT_NULL);

	time = (time_t *)args;
	switch (cmd)
	{
	case RT_DEVICE_CTRL_RTC_GET_TIME:
		/* read device */
		rt_hw_rtc_get(&tm);
		*((rt_time_t *)args) = mktime(&tm);
		break;

	case RT_DEVICE_CTRL_RTC_SET_TIME:
		tm_ptr = localtime(time);
		/* write device */
		rt_hw_rtc_set(tm_ptr);
		break;
	}

	return RT_EOK;
}

void rt_hw_rtc_init(void)
{
	rtc.type	= RT_Device_Class_RTC;

	/* register rtc device */
	rtc.init 	= RT_NULL;
	rtc.open 	= rtc_open;
	rtc.close	= rtc_close;
	rtc.read 	= rtc_read;
	rtc.write	= RT_NULL;
	rtc.control = rtc_control;
	
	/* no private */
	rtc.user_data = RT_NULL;
	
	rt_device_register(&rtc, "rtc", RT_DEVICE_FLAG_RDWR);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void list_date()
{
	time_t time;
	rt_device_t device;

	device = rt_device_find("rtc");
	if (device != RT_NULL)
	{
		rt_device_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &time);

		rt_kprintf("%d, %s\n", time, ctime(&time));
	}
}
FINSH_FUNCTION_EXPORT(list_date, list date);
#endif
