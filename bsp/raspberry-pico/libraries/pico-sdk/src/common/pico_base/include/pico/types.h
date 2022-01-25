/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_TYPES_H
#define _PICO_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef unsigned int uint;

#ifdef NDEBUG
/*! \typedef absolute_time_t
    \brief An opaque 64 bit timestamp in microseconds

    The type is used instead of a raw uint64_t to prevent accidentally passing relative times or times in the wrong
    time units where an absolute time is required. It is equivalent to uint64_t in release builds.

    \see to_us_since_boot
    \see update_us_since_boot
*/
typedef uint64_t absolute_time_t;

/*! fn to_us_since_boot
 * \brief convert an absolute_time_t into a number of microseconds since boot.
 * \param t the number of microseconds since boot
 * \return an absolute_time_t value equivalent to t
 */
static inline uint64_t to_us_since_boot(absolute_time_t t) {
    return t;
}

/*! fn update_us_since_boot
 * \brief update an absolute_time_t value to represent a given number of microseconds since boot
 * \param t the absolute time value to update
 * \param us_since_boot the number of microseconds since boot to represent
 */
static inline void update_us_since_boot(absolute_time_t *t, uint64_t us_since_boot) {
    *t = us_since_boot;
}

#define ABSOLUTE_TIME_INITIALIZED_VAR(name, value) name = value
#else
typedef struct {
    uint64_t _private_us_since_boot;
} absolute_time_t;

static inline uint64_t to_us_since_boot(absolute_time_t t) {
    return t._private_us_since_boot;
}

static inline void update_us_since_boot(absolute_time_t *t, uint64_t us_since_boot) {
    t->_private_us_since_boot = us_since_boot;
}
#define ABSOLUTE_TIME_INITIALIZED_VAR(name, value) name = {value}
#endif

/** \struct datetime_t
 *  \ingroup util_datetime
 *  \brief Structure containing date and time information
 *
 *    When setting an RTC alarm, set a field to -1 tells
 *    the RTC to not match on this field
 */
typedef struct {
    int16_t year;    ///< 0..4095
    int8_t month;    ///< 1..12, 1 is January
    int8_t day;      ///< 1..28,29,30,31 depending on month
    int8_t dotw;     ///< 0..6, 0 is Sunday
    int8_t hour;     ///< 0..23
    int8_t min;      ///< 0..59
    int8_t sec;      ///< 0..59
} datetime_t;

#endif
