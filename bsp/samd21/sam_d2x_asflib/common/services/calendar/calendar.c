/**
 * \file
 *
 * \brief Calendar service.
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include "compiler.h"
#include "calendar.h"
#include <stdio.h>

//! Unix epoch year
#define EPOCH_YEAR 1970

//! Number of seconds in a day
#define SECS_PER_DAY 86400UL

//! Number of seconds in an hour
#define SECS_PER_HOUR 3600UL

//! Number of seconds in a minute
#define SECS_PER_MINUTE 60UL

//! Number of days in a specified month. Index 1 for leap year, else 0.
const uint8_t month[2][12] = {
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

/**
 * \internal
 * \brief Check if a year is a leap year
 *
 * Returns true or false depending if the input year is a leap year or not.
 *
 * \param year the year in format YYYY to check for leap year or not
 *
 * \retval true  if the year is a leap year
 * \retval false if the year is not a leap year
 */
static bool calendar_leapyear(uint16_t year)
{
	if(!((year) % 4) && (((year) % 100) || !((year) % 400))) {
		return true;
	} else {
		return false;
	}
}

/**
 * \internal
 * \brief Find number of days in a year
 *
 * Returns the number of days in a year, depending if the input is leap year
 * or not.
 *
 * \param year the year in format YYYY to check number of days
 *
 * \retval 366 if the year is a leap year
 * \retval 365 if the year is not a leap year
 */
static uint16_t calendar_yearsize(uint16_t year)
{
	if (calendar_leapyear(year)) {
		return 366;
	} else {
		return 365;
	}
}

/**
 * \internal
 * \brief Add a year to a date
 *
 * Adds one year to specified date as long as the current year is before 2105.
 *
 * \param *date the date to add a year to
 *
 */
static void calendar_add_year_to_date(struct calendar_date *date)
{
	if (date->year < 2105) {
		date->year++;
	}
}

/**
 * \internal
 * \brief Add a month to a date
 *
 * Adds one month to specified date. If month is december, increment year.
 *
 * \param *date the date to add a month to
 *
 */
static void calendar_add_month_to_date(struct calendar_date *date)
{
	uint8_t months = date->month;
	months++;
	if (months == 12){
		months = 0;
		calendar_add_year_to_date(date);
	}
	date->month = months;
}

/**
 * \internal
 * \brief Add a day to a date
 *
 * Adds one day to specified date. If day is the last of the month, increment
 * month.
 *
 * \param *date the date to add a day to
 *
 */
static void calendar_add_day_to_date(struct calendar_date *date)
{
	uint8_t dates = date->date;
	uint8_t months = date->month;
	uint8_t year = date->year;

	dates++;
	if (dates == month[calendar_leapyear(year)][months]) {
		dates = 0;
		calendar_add_month_to_date(date);
	}
	date->dayofweek++;
	if (date->dayofweek == 7) {
		date->dayofweek = 0;
	}
	date->date = dates;
}

/**
 * \internal
 * \brief Add an hour to a date
 *
 * Adds one hour to specified date. If hour is 23, increment day.
 *
 * \param *date the date to add an hour to
 *
 */
static void calendar_add_hour_to_date(struct calendar_date *date)
{
	int8_t hour = date->hour;
	hour++;
	if (hour == 24){
		hour = 0;
		calendar_add_day_to_date(date);
	}
	date->hour = hour;
}

/**
 * \internal
 * \brief Add a minute to a date
 *
 * Adds one minute to specified date. If minute is 59, increment hour.
 *
 * \param *date the date to add a minute to
 *
 */
static void calendar_add_minute_to_date(struct calendar_date *date)
{
	uint8_t minute = date->minute;
	minute++;
	if (minute == 60){
		minute = 0;
		calendar_add_hour_to_date(date);
	}
	date->minute = minute;
}

/**
 * \brief Check if a date is valid
 *
 * Checks that number of seconds, minutes and hours is a valid value.
 * Checks that number of days does not exceed number of days in current month.
 * Checks that number of months is a valid value, and checks that year is
 * between 1970 (epoch year) and 2106 (overflow year).
 *
 * \param *date the date to check if valid
 *
 */
bool calendar_is_date_valid(struct calendar_date *date)
{
	// Make sure time is valid
	if ((date->second >= 60) || (date->minute >= 60) || (date->hour >= 24)) {
		return false;
	}

	// Make sure month and date is valid
	if ((date->month >= 12) || (date->date >=31)) {
		return false;
	}

	// Make sure days in month are not more than it should be
	if (date->date >= month[calendar_leapyear(date->year)][date->month]) {
		return false;
	}

	// Make sure year is not earlier than 1970 and before 2106
	if ((date->year < EPOCH_YEAR) || (date->year >= 2106)) {
		return false;
	} else {
		return true;
	}
}

/**
 * \brief Convert a UNIX timestamp to a date
 *
 * Finds the corresponding date and time for a UNIX timestamp.
 *
 * \param timestamp  UNIX timestamp
 * \param date_out   Date to store result
 *
 */
void calendar_timestamp_to_date(uint32_t timestamp,
		struct calendar_date *date_out)
{
	uint32_t day_number;
	uint32_t day_clock;

	date_out->year = EPOCH_YEAR;
	date_out->month = 0;

	day_clock = timestamp % SECS_PER_DAY;
	day_number = timestamp / SECS_PER_DAY;

	date_out->second = day_clock % SECS_PER_MINUTE;
	date_out->minute = (day_clock % SECS_PER_HOUR) / SECS_PER_MINUTE;
	date_out->hour = day_clock / SECS_PER_HOUR;
	date_out->dayofweek = (day_number + 4) % 7;

	while (day_number >= calendar_yearsize(date_out->year)) {
		day_number -= calendar_yearsize(date_out->year);
		date_out->year++;
	}

	while (day_number >=
			month[calendar_leapyear(date_out->year)][date_out->month]) {
		day_number -= month[calendar_leapyear(date_out->year)][date_out->month];
		date_out->month++;
	}
	date_out->date = day_number;
}

/**
 * \brief Convert a UNIX timestamp to a date in a given time zone.
 *
 * The provided UNIX timestamp is converted to the corresponding time in the
 * provided time zone.
 *
 * \param timestamp  UNIX timestamp
 * \param hour       Hour offset from UTC (UTC-12 to UTC+14)
 * \param min        Minute offset from UTC (0, 15, 30, 45)
 * \param date_out   Date to store result
 *
 */
void calendar_timestamp_to_date_tz(uint32_t timestamp, int8_t hour,
		uint8_t min, struct calendar_date *date_out)
{
	// Multiply timezone offset by seconds, and add to timestamp
	if (hour >= 0) {
		calendar_timestamp_to_date((timestamp + (SECS_PER_HOUR * hour) +
				(SECS_PER_MINUTE * min)), date_out);
	} else {
		calendar_timestamp_to_date((timestamp + (SECS_PER_HOUR * hour) -
				(SECS_PER_MINUTE * min)), date_out);
	}
}

/**
 * \brief Convert a date to a UNIX timestamp.
 *
 * \note
 * If date is invalid, timestamp 0 will be returned.
 *
 * \param date  Date
 *
 * \return The corresponding UNIX timestamp
 * \retval 0 if date is not valid
 */
uint32_t calendar_date_to_timestamp(struct calendar_date *date)
{

	// Make sure date is valid
	if (!calendar_is_date_valid(date))
		return 0;

	uint32_t timestamp = 0;
	uint8_t date_month;
	uint16_t date_year;

	date_month = date->month;
	date_year = date->year;

	// Add number of seconds elapsed in current month
	timestamp += (date->date * SECS_PER_DAY) + (date->hour * SECS_PER_HOUR) +
			(date->minute * SECS_PER_MINUTE) + date->second;

	while (date_month != 0) {
		date_month--;
		// Add number of seconds in months of current year
		timestamp += month[calendar_leapyear(date_year)][date_month]
				* SECS_PER_DAY;
	}
	while (date_year > EPOCH_YEAR) {
		date_year--;
		// Add number of seconds in all years since epoch year
		timestamp += calendar_yearsize(date_year) * SECS_PER_DAY;
	}

	return timestamp;
}

/**
 * \brief This function converts a date in a given time zone to a UNIX
 * timestamp
 * \note
 * If date is invalid, timestamp 0 will be returned.
 *
 * \param date   Date
 * \param hour   Hour offset from UTC (UTC-12 to UTC+14)
 * \param min    Minute offset from UTC (0, 15, 30, 45)
 *
 * \return The corresponding UNIX timestamp
 * \retval 0 if date is not valid
 */
uint32_t calendar_date_to_timestamp_tz(struct calendar_date *date, int8_t hour,
		uint8_t min)
{
	uint32_t timestamp = calendar_date_to_timestamp(date);
	if (timestamp == 0) {
		return 0;
	} else {
		// Subtract the seconds of offset in time zone offset from timestamp
		if (hour >= 0) {
			return (timestamp - (SECS_PER_HOUR * hour + SECS_PER_MINUTE *
					min));
		} else {
			return (timestamp - (SECS_PER_HOUR * hour - SECS_PER_MINUTE *
					min));
		}
	}
}

/**
 * \brief This function calculates the time difference between to dates.
 *
 * The time difference is provided as number of years, months, days, hours,
 * minutes and seconds between the dates. If end date is before start date,
 * the dates are switched.
 *
 * \param date_end         The end date
 * \param date_start       The start date
 * \param date_out         The time between the dates
 *
 */
void calendar_time_between_dates(struct calendar_date *date_end,
		struct calendar_date *date_start, struct calendar_date *date_out)
{
	uint32_t timestamp_start;
	uint32_t timestamp_end;
	struct calendar_date *temp;

	timestamp_start = calendar_date_to_timestamp(date_start);
	timestamp_end = calendar_date_to_timestamp(date_end);

	// Switch dates if date_end is before date_start
	if (timestamp_end < timestamp_start) {
		temp = date_end;
		date_end = date_start;
		date_start = temp;
	}

	// Calculate number of years
	date_out->year = date_end->year - date_start->year;

	// Check if months wrap around new year
	if (date_end->month - date_start->month < 0 ) {
		date_end->month += 12;
		if (date_out->year != 0) {
			date_out->year--;
		}
	}
	// Calculate number of months
	date_out->month = date_end->month - date_start->month;

	// Check if dates wrap around month
	if(date_end->date - date_start->date < 0) {
		// Add number of days in last month to get number of days correct
		date_end->date +=
			month[calendar_leapyear(date_end->year)][date_end->month-1];
		if (date_out->month != 0) {
			date_out->month--;
		}
	}
	// Calculate number of days
	date_out->date = date_end->date - date_start->date;

	// Check if hours wrap around midnight
	if (date_end->hour - date_start->hour < 0) {
		date_end->hour += 24;
		if (date_out->date != 0) {
			date_out->date--;
		}
	}
	// Calculate number of hours
	date_out->hour = date_end->hour - date_start->hour;

	// Check if minutes wrap around hour
	if (date_end->minute - date_start->minute < 0) {
		date_end->minute += 60;
		if (date_out->hour != 0) {
			date_out->hour--;
		}
	}
	// Calculate number of minutes
	date_out->minute = date_end->minute - date_start->minute;

	// Check if seconds wrap around minute
	if (date_end->second - date_start->second < 0) {
		date_end->second += 60;
		if (date_out->minute != 0) {
			date_out->minute--;
		}
	}
	// Calculate number of seconds
	date_out->second = date_end->second - date_start->second;

}

/**
 * \brief Increments a date with one second.
 *
 * This function will add one second to specified date. If second is 59,
 * it will increment minute.
 *
 * \param date The date to add a second to
 *
 */
void calendar_add_second_to_date(struct calendar_date *date)
{
	// Check if input date is valid
	Assert(calendar_is_date_valid(date));

	if (++date->second == 60) {
		date->second = 0;
		calendar_add_minute_to_date(date);
	}
}
