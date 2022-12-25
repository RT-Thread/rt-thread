/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdlib.h>
#include <utils_time.h>
//Thu=4, Fri=5, Sat=6, Sun=0, Mon=1, Tue=2, Wed=3

int utils_time_date_from_epoch(unsigned int epoch, utils_time_date_t *date)
{
    int i;
    unsigned short temp_days;
    unsigned char month_days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    unsigned char week_days[7] = {4,5,6,0,1,2,3};

    date->leap_days = 0; 
    date->leap_year_ind = 0;

    // Add or substract time zone here. 
    //epoch += 19800; //GMT +5:30 = +19800 seconds 

    date->ntp_second = epoch%60;
    epoch /= 60;
    date->ntp_minute = epoch%60;
    epoch /= 60;
    date->ntp_hour  = epoch%24;
    epoch /= 24;

    date->days_since_epoch = epoch;      //number of days since epoch
    date->ntp_week_day = week_days[date->days_since_epoch%7];  //Calculating WeekDay

    date->ntp_year = 1970 + (date->days_since_epoch/365); // ball parking year, may not be accurate!
    for (i = 1972, date->leap_days = 0; i < date->ntp_year; i+=4) {
        // Calculating number of leap days since epoch/1970
        if(((i%4==0) && (i%100!=0)) || (i%400==0)) {
            date->leap_days++;
        }
    }

    date->ntp_year = 1970 + ((date->days_since_epoch - date->leap_days)/365); // Calculating accurate current year by (days_since_epoch - extra leap days)
    if (((date->ntp_year%4==0) && (date->ntp_year%100!=0)) || (date->ntp_year%400==0))  {
        month_days[1]=29;     //February = 29 days for leap years
        date->leap_year_ind = 1;    //if current year is leap, set indicator to 1 
    } else {
        month_days[1]=28; //February = 28 days for non-leap years 
        date->leap_year_ind = 0;    //if current year is leap, set indicator to 1 
    }
    for (i = 1972, date->leap_days = 0; i < date->ntp_year; i+=4) {
        // Calculating number of leap days since epoch/1970
        if(((i%4==0) && (i%100!=0)) || (i%400==0)) {
            date->leap_days++;
        }
    }
    date->day_of_year = date->days_since_epoch - date->leap_days - (date->ntp_year - 1970) * 365 + 1;


    temp_days = 0;

    for (date->ntp_month = 0; date->ntp_month <= 11; date->ntp_month++) {
        //calculating current Month
        if (date->day_of_year <= temp_days) {
            break; 
        }
        temp_days = temp_days + month_days[date->ntp_month];
    }

    temp_days = temp_days - month_days[date->ntp_month-1]; //calculating current Date
    date->ntp_date = date->day_of_year - temp_days;

    return 0;
}
