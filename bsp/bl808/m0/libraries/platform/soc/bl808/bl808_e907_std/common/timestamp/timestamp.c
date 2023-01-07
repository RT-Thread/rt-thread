/**
 * @file timestamp.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */

#include "timestamp.h"

#define FOUR_YEAR_DAY ((365 << 2) + 1) //The total number of days in a 4-year cycle
#define TIMEZONE      (8)              //Beijing time Zone adjustment

#define SEC_NUM_PER_DAY    (24 * 60 * 60)
#define SEC_NUM_PER_HOUR   (60 * 60)
#define SEC_NUM_PER_MINUTE (60)

static uint8_t month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };      //平年
static uint8_t Leap_month_day[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //闰年

/**
* @bref judge if it is a leap year
* @para year to be judge
* @return 1：leap year  0： nonleap year
*/
bool check_leap_year(uint16_t year)
{
    if (year % 4) {
        return false;
    } else {
        if ((year % 100 == 0) && (year % 400 != 0)) {
            return false;
        } else {
            return true;
        }
    }
}

void cal_weekday(rtc_time *beijing_time)
{
	uint32_t y,m,d,w;

	y=beijing_time->year;
	m=beijing_time->month;
	d=beijing_time->day;

	if((m==1)||(m==2))
	{
		m+=12;
		y--;
	}
	/*
	把一月和二月看成是上一年的十三月和十四月，例：如果是2004-1-10则换算成：2003-13-10来代入公式计算。
	以公元元年为参考，公元元年1月1日为星期一</PRE><PRE>程序如下：
	利用基姆拉尔森计算日期公式  w=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)
	*/
	w=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400+1)%7;

	beijing_time->week=(uint8_t)w;
}

void unixtime2bejingtime(uint32_t unixtime, rtc_time *beijing_time)
{
    uint32_t totle_day_num;
    uint32_t current_sec_num;

    uint16_t remain_day;

    uint16_t temp_year;

    uint8_t *p = NULL;

    totle_day_num = unixtime / SEC_NUM_PER_DAY;   //The total number of days
    current_sec_num = unixtime % SEC_NUM_PER_DAY; //The number of seconds this day

    /* use the number of seconds this day, To calculate hour\minute\second */
    beijing_time->hour = current_sec_num / SEC_NUM_PER_HOUR;
    beijing_time->minute = (current_sec_num % SEC_NUM_PER_HOUR) / SEC_NUM_PER_MINUTE;
    beijing_time->second = (current_sec_num % SEC_NUM_PER_HOUR) % SEC_NUM_PER_MINUTE;

    /* Adjust the time zone and check whether the date is +1 */
    beijing_time->hour += 8;
    if (beijing_time->hour > 23) {
        beijing_time->hour -= 24;
        totle_day_num++;
    }


    /* calculate year */
    beijing_time->year = 1970 + (totle_day_num / FOUR_YEAR_DAY) * 4; // 4-year as a cycle
    remain_day = totle_day_num % FOUR_YEAR_DAY;                      //remaining day nym( < 4 year )

    /* calculate year & day */
    temp_year = check_leap_year(beijing_time->year) ? 366 : 365;
    while (remain_day >= temp_year) {
        beijing_time->year++;
        remain_day -= temp_year;
        temp_year = check_leap_year(beijing_time->year) ? 366 : 365;
    }

    /* Calculate specific dates(month\day)*/
    p = check_leap_year(beijing_time->year) ? Leap_month_day : month_day;
    remain_day++; //The actual day starts at 1
    beijing_time->month = 0;
    while (remain_day > *(p + beijing_time->month)) {
        remain_day -= *(p + beijing_time->month);
        beijing_time->month++;
    }

    beijing_time->month++; //The actual month starts at 1
    beijing_time->day = remain_day;



	/*利用基姆拉尔森计算日期公式  w=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)*/

	beijing_time->week = beijing_time->day + 2*beijing_time->month + 3*(beijing_time->month+1)/5 + \
	beijing_time->year + beijing_time->year/4 - beijing_time->year/100 +beijing_time->year/400 ;

	cal_weekday(beijing_time);
}
