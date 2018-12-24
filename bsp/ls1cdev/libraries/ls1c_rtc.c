/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-06     sundm75       first version
 */
#include "ls1c.h"
#include "ls1c_public.h"
#include "ls1c_rtc.h"

#define LS1C_SEC_OFFSET		(4)
#define LS1C_MIN_OFFSET		(10)
#define LS1C_HOUR_OFFSET	(16)
#define LS1C_DAY_OFFSET		(21)
#define LS1C_MONTH_OFFSET	(26)

#define LS1C_SEC_MASK		(0x3f)
#define LS1C_MIN_MASK		(0x3f)
#define LS1C_HOUR_MASK		(0x1f)
#define LS1C_DAY_MASK		(0x1f)
#define LS1C_MONTH_MASK		(0x3f)
#define LS1C_YEAR_MASK		(0xff)

#define ls1c_get_sec(t)		(((t) >> LS1C_SEC_OFFSET) & LS1C_SEC_MASK)
#define ls1c_get_min(t)		(((t) >> LS1C_MIN_OFFSET) & LS1C_MIN_MASK)
#define ls1c_get_hour(t)	(((t) >> LS1C_HOUR_OFFSET) & LS1C_HOUR_MASK)
#define ls1c_get_day(t)		(((t) >> LS1C_DAY_OFFSET) & LS1C_DAY_MASK)
#define ls1c_get_month(t)	(((t) >> LS1C_MONTH_OFFSET) & LS1C_MONTH_MASK)

int RTC_SetTime(RTC_TypeDef *hrtc, RTC_TimeTypeDef *sTime)
{

	hrtc->SYS_TOYWRITE0
		= (sTime->Month  << LS1C_MONTH_OFFSET)
		| (sTime->Date << LS1C_DAY_OFFSET)
		| (sTime->Hours << LS1C_HOUR_OFFSET)
		| (sTime->Minutes  << LS1C_MIN_OFFSET)
		| (sTime->Seconds  << LS1C_SEC_OFFSET);
	hrtc->SYS_TOYWRITE1 =  sTime->Year % 100;
	printf("\r\ntoy_read0 = 0x%x, toy_read1 = 0x%x.\r\n", hrtc->SYS_TOYREAD0, hrtc->SYS_TOYREAD1);

   return 0;
}

int RTC_GetTime(RTC_TypeDef *hrtc, RTC_TimeTypeDef *sTime)
{
  unsigned long toy_read0, toy_read1; 
  toy_read0 = hrtc->SYS_TOYREAD0;
  toy_read1 = hrtc->SYS_TOYREAD1; 
  sTime->Seconds = ls1c_get_sec(toy_read0);
  sTime->Minutes = ls1c_get_min(toy_read0);
  sTime->Hours = ls1c_get_hour(toy_read0);
  sTime->Date = ls1c_get_day(toy_read0);
  sTime->Month = ls1c_get_month(toy_read0);
  sTime->Year = toy_read1 & LS1C_YEAR_MASK;  
  return 0 ;
}

unsigned char RTC_IsLeapYear(unsigned int nYear)
{
  if((nYear % 4U) != 0U) 
  {
    return 0U;
  }
  
  if((nYear % 100U) != 0U) 
  {
    return 1U;
  }
  
  if((nYear % 400U) == 0U)
  {
    return 1U;
  }
  else
  {
    return 0U;
  }
}

unsigned char RTC_WeekDayNum(unsigned long nYear, unsigned char nMonth, unsigned char nDay)
{
  unsigned long year = 0U, weekday = 0U;

  year = 2000U + nYear;
  
  if(nMonth < 3U)
  {
    /*D = { [(23 x month)/9] + day + 4 + year + [(year-1)/4] - [(year-1)/100] + [(year-1)/400] } mod 7*/
    weekday = (((23U * nMonth)/9U) + nDay + 4U + year + ((year-1U)/4U) - ((year-1U)/100U) + ((year-1U)/400U)) % 7U;
  }
  else
  {
    /*D = { [(23 x month)/9] + day + 4 + year + [year/4] - [year/100] + [year/400] - 2 } mod 7*/
    weekday = (((23U * nMonth)/9U) + nDay + 4U + year + (year/4U) - (year/100U) + (year/400U) - 2U ) % 7U; 
  }

  return (unsigned char)weekday;
}
