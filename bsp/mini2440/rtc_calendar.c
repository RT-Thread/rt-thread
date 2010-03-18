/*
 * File      : rtc_calendar.c
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
 * 2010-02-21	  Gary Lee	   add __DATA__
 */

#include "rtc_calendar.h"
#include <string.h>

extern void rt_hw_console_putc(char c);
extern rt_uint8_t rt_hw_serial_getc(void);

rt_uint32_t year_seprt=0;
rt_uint8_t  month_seprt=0;
rt_uint8_t  day_seprt=0;

static const rt_int8_t *month_cn[12] ={ "一月", "二月", "三月", "四月", "五月", "六月", "七月", "八月",
						   "九月", "十月", "十一月", "十二月"
						 };
static const rt_int8_t *month_en[12] ={ "January", "February", "March", "April", "May", "June", "July",
						   "Auguest", "September", "October", "November", "December"
						 };

static const rt_int8_t *day_en[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Firday","Saturday"};
static const rt_int8_t *day_cn[7]={"星期日","星期一","星期二","星期三","星期四","星期五","星期六"};
//=====================================================================
//read from uart

rt_int32_t rt_rtc_isleap(rt_uint32_t year)
{
	rt_int32_t leap = 0;
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 4 == 0))
		leap = 1;
	return leap;
}

rt_int32_t rt_rtc_week_of_newyears_day(rt_uint32_t year)
{
	rt_int32_t n = year - 1900;
	n = n + (n - 1) / 4 + 1;
	n = n % 7;
	return n;
}

rt_int32_t rt_rtc_month_day_num(rt_int32_t month, rt_int32_t leapyn)
{
	rt_int32_t len_month = 0;
	if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
		len_month = 30;
	else if (month == 2)
	{
		if (leapyn == 1)
			len_month = 29;
		else
			len_month = 28;
	}
	else
		len_month = 31;
	return len_month;
}

rt_int32_t rt_rtc_space_days(rt_int32_t month, rt_int32_t year)
{
	rt_int32_t all_days = 0;
	rt_int32_t i = 1;
	rt_int32_t leap = rt_rtc_isleap(year);
	for (i = 1; i <= month; i++)
	{
		all_days = all_days + rt_rtc_month_day_num(i, leap);
	}
	return all_days;
}

rt_int32_t rt_rtc_weekday_month(rt_int32_t month, rt_int32_t year)
{
	rt_int32_t space = 0, j, all_days = 0;
	rt_int32_t leap = rt_rtc_isleap(year);
	space = rt_rtc_week_of_newyears_day(year);
	for (j = 1; j <= month - 1; j++)
	{
		all_days = all_days + rt_rtc_month_day_num(j, leap);
	}

	space = (space + all_days) % 7;
	return space;
}

void rt_rtc_print_common_fmt(rt_uint8_t month, rt_uint8_t weekday, rt_uint8_t leapyear)
{
	rt_int32_t day, j, len_of_month;

	rt_kprintf("\n%s	%s	%d\n",
			   month_cn[month - 1], month_en[month - 1], year_seprt);
	rt_kprintf("----------------------------------\n");
	rt_kprintf("SUN  MON  TUE  WED  THU  FRI  SAT\n");
	rt_kprintf("----------------------------------\n");
	for (j = 0; j < weekday; j++)
		rt_kprintf("     ");
	len_of_month = rt_rtc_month_day_num(month, leapyear);

	for (day = 1; day <= len_of_month; day++)
	{
		if (day > 9)
			rt_kprintf("%d   ", day);
		else
			rt_kprintf("%d    ", day);
		weekday = weekday + 1;
		if (weekday == 7)
		{
			weekday = 0;
			rt_kprintf("\n");
		}
	}
	rt_kprintf("\n");
}

void rt_rtc_print_one_month(rt_int32_t month, rt_int32_t year)
{
	rt_int32_t weekday = rt_rtc_weekday_month(month, year);
	rt_int32_t leapyear = rt_rtc_isleap(year);
	rt_rtc_print_common_fmt(month, weekday, leapyear);
}


void rt_rtc_print_calendar(rt_uint32_t year)
{
	rt_uint8_t month;

	if (month_seprt == 0)
	{
		for (month = 1; month <= 12; month = month + 1)
		{
			rt_rtc_print_one_month(month, year);
		}
	}
	else
		rt_rtc_print_one_month(month_seprt, year);

}

void rt_rtc_year_month_day_seperate(rt_uint32_t year)
{
	rt_uint32_t temp;

	if (year < 1900 || year > 30000000)
	{
		rt_kprintf("\nPlease input year and month, if not, system default is loaded!\n");
		year = DEFAULT_YEAR;
	}
	if (year / 100 < 30 && year / 100 > 18)
	{
		year_seprt = year;
		month_seprt = 0;
		day_seprt = 0;
	}
	else if (year / 100 < 300 && year / 100 > 196)
	{
		year_seprt = year / 10;
		month_seprt = year % 10;
		day_seprt = 0;
	}
	else if (year / 100 < 3000 && year / 100 > 1960)
	{
		year_seprt = year / 100;
		month_seprt = year % 100;
		if (month_seprt > 12)
		{
			temp = month_seprt;
			month_seprt = temp / 10;
			day_seprt = temp % 10;
		}
		else if (month_seprt < 10)
			day_seprt = 0;

	}
	else if (year / 100 < 30000 && year / 100 > 19600)
	{
		year_seprt = year / 1000;
		month_seprt = (year % 1000) / 100;
		if (month_seprt == 0)
		{
			month_seprt = (year % 100) / 10;
			day_seprt = year % 10;
		}
		else
			day_seprt = year % 100;
		temp = rt_rtc_month_day_num(month_seprt, rt_rtc_isleap(year_seprt));
		if (day_seprt > temp)
		{
			rt_kprintf("\nError：There are only %d days this month, using default date\n", temp);
			day_seprt = DEFAULT_DAY;
		}
	}
	else
	{
		year_seprt = year / 10000;
		month_seprt = (year % 10000) / 100;
		if (month_seprt > 12)
		{
			rt_kprintf("\nError: There are only 12 months a year, using default date\n");
			month_seprt = DEFAULT_MONTH;
		}
		day_seprt = year % 100;
		temp = rt_rtc_month_day_num(month_seprt, rt_rtc_isleap(year_seprt));
		if (day_seprt > temp)
		{
			rt_kprintf("\nError: There are %d days in this month, using default date\n", temp);
			day_seprt = DEFAULT_DAY;
		}
	}
}

void rt_rtc_weekdate_calculate(void)
{
	rt_uint32_t temp;

	temp = rt_rtc_weekday_month(month_seprt, year_seprt) - 1;
	temp = (temp + day_seprt) % 7;
	rt_kprintf("%d/%d/%d/:%s\n", year_seprt, month_seprt, day_seprt, day_cn[temp]);

}

static const rt_uint8_t *list_month[12]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
void rt_calendar(void)
{
	//static rt_uint8_t receive_char;
	static rt_int32_t year;
	rt_uint8_t i = 0;
	rt_int32_t result, num_month, num_year;
	rt_uint8_t date_year[5], date_month[4], *date = __DATE__;

	strlcpy((char *)date_month, (const char *)date, 4);
	date += 7;
	strlcpy((char *)date_year,  (const char *)date, 5);
	date = RT_NULL;
	num_year = atoi(date_year);
	do
	{
		result = strcmp((const char *)date_month, (const char *)list_month[i++]);
		if(result !=0)
			result = 1;
		else
			num_month = i;
	}while(result);
	i = 0;
	result = 1;
	year = num_year*100 + num_month;
	//year = Uart_GetIntNum_MT();
	//rt_kprintf("\nThe date is %d\n", year);
	rt_rtc_year_month_day_seperate(year);

	if (day_seprt == 0 && month_seprt == 0)
	{
		//rt_kprintf("\nYear: %d\n", year_seprt);
		rt_rtc_print_calendar(year_seprt);

	}
	else if (day_seprt == 0)
	{
		//rt_kprintf("\n%d/%d\n", year_seprt, month_seprt);
		rt_rtc_print_calendar(year_seprt);

	}
	else
	{
		//rt_kprintf("\n%d/%d/%d\n", year_seprt, month_seprt, day_seprt);
		rt_rtc_weekdate_calculate();
	}
}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(rt_calendar, print calendar)
#endif
