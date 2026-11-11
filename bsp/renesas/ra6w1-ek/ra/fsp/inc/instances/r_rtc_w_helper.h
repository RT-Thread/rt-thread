/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_RTC_W_HELPER_H
#define R_RTC_W_HELPER_H

#include <time.h>
#include "bsp_api.h"
#include "sdk_defs.h"
#include "bsp_rtm.h"

/**
 ****************************************************************************************
 * @brief Get timezone offset from GMT
 * @return  Returns a value of type time_t(long) that represents a timezone offset value.
 ****************************************************************************************
 */
long ra6w1_Tzoff(void);

/**
 ****************************************************************************************
 * @brief Set the timezone offset from GMT
 * param[in]    offset  Set time zone offset value of type time_t(long)
 ****************************************************************************************
 */
void ra6w1_SetTzoff(long offset);

/// Convert time_t to tm as UTC time
#define gmtime(p)       ra6w1_gmtime64(p)

/// Convert tm structure to time_t
#define localtime(p)    ra6w1_localtime64(p)

/**
 ****************************************************************************************
 * @brief Get / Set current GMT time (for 64bit) & check and fix bsp system count wraparround.
 * @param[in]   p   Set the time of p value to the current time.\n
 * If NULL, no current time is set.
 * @param[out]  now Get the current time.
 ****************************************************************************************
 */
void ra6w1_time64(__time64_t * p, __time64_t * now);

/**
 ****************************************************************************************
 * @brief Convert __time64_t to tm as UTC time
 * @param[in]   tod Pointer to an object of type time_t that contains a time value.\n
 * __time64_t is an alias of a fundamental arithmetic type capable of representing times as returned by function time.
 * @return      A pointer to a tm structure with its members filled with the values that correspond to the UTC time representation of tod.
 ****************************************************************************************
 */
struct tm * ra6w1_gmtime64(const __time64_t * tod);

/**
 ****************************************************************************************
 * @brief Convert __time64_t to tm as local time
 * @param[in]   tod Pointer to an object of type __time64_t that contains a time value.\n
 * time_t is an alias of a fundamental arithmetic type capable of representing times as returned by function time.
 * @return      A pointer to a tm structure with its members filled with the values that correspond to the local time representation of tod.
 ****************************************************************************************
 */
struct tm * ra6w1_localtime64(const __time64_t * tod);

/**
 ****************************************************************************************
 * @brief Convert tm structure to __time64_t
 * @param[in]   t   Pointer to a tm structure that contains a calendar gmt time broken down into its components (see struct tm)
 * @param[out]  now Returns the value of type __time64_t that represents the time described by the tm structure pointed by t
 ****************************************************************************************
 */
void ra6w1_mktime64(struct tm * t, __time64_t * now);

/**
 ****************************************************************************************
 * @brief Get elapsed time after RTOS boot(for 64bit)
 * param[out]   boottime    Pointer to an object of type time_t that contains a time value.
 ****************************************************************************************
 */
void __boottime(__time64_t * boottime);

/**
 ****************************************************************************************
 * @brief Format time as string
 * @param[out] ptr Pointer to the destination array where the resulting C string is copied.
 * @param[in] maxsize Maximum number of characters to be copied to ptr, including the terminating null-character.
 * @param[in] format C string containing any combination of regular characters and special format specifiers.\n
 *            These format specifiers are replaced by the function to the corresponding values to represent
 *            the time specified in timeptr.
 * @param[in] t Pointer to struct tm to convert to a string
 * @return  If the length of the resulting C string, including the terminating null-character, doesn't exceed maxsize,\n
 * the function returns the total number of characters copied to ptr (not including the terminating null-character).\n
 * Otherwise, it returns zero, and the contents of the array pointed by ptr are indeterminate.
 ****************************************************************************************
 */
size_t ra6w1_strftime(char * ptr, size_t maxsize, const char * format, const struct tm * t);

void rtc_w_lock_take(void);
void rtc_w_lock_give(void);

#endif                                 // R_RTC_W_HELPER_H
