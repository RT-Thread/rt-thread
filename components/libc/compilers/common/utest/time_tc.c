/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * Test Case Name: POSIX Time Conversion Test
 *
 * Test Objectives:
 * - Verify that timegm normalizes dates across month and year boundaries.
 * - Verify negative values in the time fields are normalized.
 * - Verify leap-year February handling.
 * - Prevent regression of GitHub Issue #11686.
 */

#include <rtthread.h>
#include <sys/time.h>
#include "utest.h"

/* Verify that timegm output agrees with a UTC round-trip conversion. */
static void timegm_assert_consistent(const char *case_name,
                                     struct tm *time_value,
                                     time_t expected_timestamp)
{
    struct tm normalized = { 0 };
    time_t timestamp;

    timestamp = timegm(time_value);

    uassert_int_equal(timestamp, expected_timestamp);
    LOG_I("%s: timestamp=%ld, normalized=%04d-%02d-%02d %02d:%02d:%02d",
          case_name,
          (long)timestamp,
          time_value->tm_year + 1900,
          time_value->tm_mon + 1,
          time_value->tm_mday,
          time_value->tm_hour,
          time_value->tm_min,
          time_value->tm_sec);

    if (gmtime_r(&timestamp, &normalized) == RT_NULL)
    {
        uassert_not_null(RT_NULL);
        return;
    }

    uassert_int_equal(normalized.tm_year, time_value->tm_year);
    uassert_int_equal(normalized.tm_mon, time_value->tm_mon);
    uassert_int_equal(normalized.tm_mday, time_value->tm_mday);
    uassert_int_equal(normalized.tm_hour, time_value->tm_hour);
    uassert_int_equal(normalized.tm_min, time_value->tm_min);
    uassert_int_equal(normalized.tm_sec, time_value->tm_sec);
    uassert_int_equal(normalized.tm_yday, time_value->tm_yday);
    uassert_int_equal(normalized.tm_wday, time_value->tm_wday);
}

/* Verify date normalization across a regular month boundary. */
static void timegm_month_boundary_test(void)
{
    struct tm time_value = { 0 };

    time_value.tm_year = 123;
    time_value.tm_mon = 0;
    time_value.tm_mday = 32;

    timegm(&time_value);

    uassert_int_equal(time_value.tm_year, 123);
    uassert_int_equal(time_value.tm_mon, 1);
    uassert_int_equal(time_value.tm_mday, 1);
}

/* Verify date normalization for February in a leap year. */
static void timegm_leap_year_test(void)
{
    struct tm time_value = { 0 };

    time_value.tm_year = 124;
    time_value.tm_mon = 0;
    time_value.tm_mday = 60;

    timegm(&time_value);

    uassert_int_equal(time_value.tm_year, 124);
    uassert_int_equal(time_value.tm_mon, 1);
    uassert_int_equal(time_value.tm_mday, 29);
}

/* Verify date normalization for a large day offset. */
static void timegm_large_day_test(void)
{
    struct tm time_value = { 0 };

    time_value.tm_year = 126;
    time_value.tm_mon = 7;
    time_value.tm_mday = 425;
    time_value.tm_hour = 8;

    timegm_assert_consistent("large day offset",
                             &time_value,
                             (time_t)1822204800);

    uassert_int_equal(time_value.tm_year, 127);
    uassert_int_equal(time_value.tm_mon, 8);
    uassert_int_equal(time_value.tm_mday, 29);
    uassert_int_equal(time_value.tm_hour, 8);
    uassert_int_equal(time_value.tm_yday, 271);
    uassert_int_equal(time_value.tm_wday, 3);
}

/* Verify zero-day normalization across a year boundary. */
static void timegm_zero_day_test(void)
{
    struct tm time_value = { 0 };

    time_value.tm_year = 123;
    time_value.tm_mon = 0;
    time_value.tm_mday = 0;

    timegm_assert_consistent("zero day",
                             &time_value,
                             (time_t)1672444800);

    uassert_int_equal(time_value.tm_year, 122);
    uassert_int_equal(time_value.tm_mon, 11);
    uassert_int_equal(time_value.tm_mday, 31);
}

/* Verify negative-day normalization in a leap year. */
static void timegm_negative_day_test(void)
{
    struct tm time_value = { 0 };

    time_value.tm_year = 124;
    time_value.tm_mon = 2;
    time_value.tm_mday = -1;

    timegm_assert_consistent("negative day",
                             &time_value,
                             (time_t)1709078400);

    uassert_int_equal(time_value.tm_year, 124);
    uassert_int_equal(time_value.tm_mon, 1);
    uassert_int_equal(time_value.tm_mday, 28);
}

/* Verify negative-second normalization across a year boundary. */
static void timegm_negative_second_test(void)
{
    struct tm time_value = { 0 };

    time_value.tm_year = 123;
    time_value.tm_mon = 0;
    time_value.tm_mday = 1;
    time_value.tm_sec = -61;

    timegm(&time_value);

    uassert_int_equal(time_value.tm_year, 122);
    uassert_int_equal(time_value.tm_mon, 11);
    uassert_int_equal(time_value.tm_mday, 31);
    uassert_int_equal(time_value.tm_hour, 23);
    uassert_int_equal(time_value.tm_min, 58);
    uassert_int_equal(time_value.tm_sec, 59);
}

/* Verify negative-minute normalization across a year boundary. */
static void timegm_negative_minute_test(void)
{
    struct tm time_value = { 0 };

    time_value.tm_year = 123;
    time_value.tm_mon = 0;
    time_value.tm_mday = 1;
    time_value.tm_min = -1;

    timegm(&time_value);

    uassert_int_equal(time_value.tm_year, 122);
    uassert_int_equal(time_value.tm_mon, 11);
    uassert_int_equal(time_value.tm_mday, 31);
    uassert_int_equal(time_value.tm_hour, 23);
    uassert_int_equal(time_value.tm_min, 59);
    uassert_int_equal(time_value.tm_sec, 0);
}

/* Verify negative-hour normalization across a year boundary. */
static void timegm_negative_hour_test(void)
{
    struct tm time_value = { 0 };

    time_value.tm_year = 123;
    time_value.tm_mon = 0;
    time_value.tm_mday = 1;
    time_value.tm_hour = -1;

    timegm(&time_value);

    uassert_int_equal(time_value.tm_year, 122);
    uassert_int_equal(time_value.tm_mon, 11);
    uassert_int_equal(time_value.tm_mday, 31);
    uassert_int_equal(time_value.tm_hour, 23);
    uassert_int_equal(time_value.tm_min, 0);
    uassert_int_equal(time_value.tm_sec, 0);
}

/* Verify negative-month normalization across a year boundary. */
static void timegm_negative_month_test(void)
{
    struct tm time_value = { 0 };

    time_value.tm_year = 123;
    time_value.tm_mon = -13;
    time_value.tm_mday = 1;

    timegm(&time_value);

    uassert_int_equal(time_value.tm_year, 121);
    uassert_int_equal(time_value.tm_mon, 11);
    uassert_int_equal(time_value.tm_mday, 1);
}

/* Verify positive overflow across all time fields. */
static void timegm_positive_overflow_test(void)
{
    struct tm time_value = { 0 };

    time_value.tm_year = 123;
    time_value.tm_mon = 12;
    time_value.tm_mday = 1;
    time_value.tm_hour = 25;
    time_value.tm_min = 61;
    time_value.tm_sec = 61;

    timegm_assert_consistent("positive overflow",
                             &time_value,
                             (time_t)1704160921);

    uassert_int_equal(time_value.tm_year, 124);
    uassert_int_equal(time_value.tm_mon, 0);
    uassert_int_equal(time_value.tm_mday, 2);
    uassert_int_equal(time_value.tm_hour, 2);
    uassert_int_equal(time_value.tm_min, 2);
    uassert_int_equal(time_value.tm_sec, 1);
}

/* Verify negative overflow across all time fields. */
static void timegm_combined_negative_test(void)
{
    struct tm time_value = { 0 };

    time_value.tm_year = 123;
    time_value.tm_mon = -13;
    time_value.tm_mday = 1;
    time_value.tm_hour = -25;
    time_value.tm_min = -61;
    time_value.tm_sec = -61;

    timegm_assert_consistent("combined negative overflow",
                             &time_value,
                             (time_t)1638223079);

    uassert_int_equal(time_value.tm_year, 121);
    uassert_int_equal(time_value.tm_mon, 10);
    uassert_int_equal(time_value.tm_mday, 29);
    uassert_int_equal(time_value.tm_hour, 21);
    uassert_int_equal(time_value.tm_min, 57);
    uassert_int_equal(time_value.tm_sec, 59);
}

/*
 * gmtime_r() against timestamps before the epoch.
 *
 * Every field is checked, not only the date: the defective implementation returned
 * a non-NULL struct tm holding impossible values (negative tm_sec, zero tm_mday,
 * negative tm_wday / tm_yday), so tm_wday and tm_yday are part of the contract
 * that has to be pinned down here.
 */
struct gmtime_r_case
{
    const char *name;
    time_t      timestamp;
    int         year;   /* tm_year, i.e. years since 1900 */
    int         mon;    /* tm_mon, 0 based */
    int         mday;
    int         hour;
    int         min;
    int         sec;
    int         wday;   /* 0 = Sunday */
    int         yday;   /* 0 based */
};

static const struct gmtime_r_case gmtime_r_cases[] =
{
    /* 1970-01-01 00:00:00, Thursday */
    { "epoch zero",    (time_t)0,         70, 0,  1,  0,  0,  0, 4,   0 },
    /* 1969-12-31 23:59:59, Wednesday */
    { "t = -1",        (time_t)-1,        69, 11, 31, 23, 59, 59, 3, 364 },
    /* 1969-12-31 00:00:00, Wednesday */
    { "t = -86400",    (time_t)-86400,    69, 11, 31,  0,  0,  0, 3, 364 },
    /* 1969-12-30 23:59:59, Tuesday */
    { "t = -86401",    (time_t)-86401,    69, 11, 30, 23, 59, 59, 2, 363 },
    /* 1968-02-29 00:00:00, Thursday, 672 days before the epoch (1968 is a leap year) */
    { "1968 leap day", (time_t)-58060800, 68,  1, 29,  0,  0,  0, 4,  59 },
};

/* Check every field gmtime_r() fills in, for timestamps before the epoch. */
static void gmtime_r_before_epoch_test(void)
{
    size_t i;

    for (i = 0; i < sizeof(gmtime_r_cases) / sizeof(gmtime_r_cases[0]); i++)
    {
        const struct gmtime_r_case *c = &gmtime_r_cases[i];
        struct tm r;
        time_t timestamp = c->timestamp;

        rt_memset(&r, 0, sizeof(r));

        uassert_not_null(gmtime_r(&timestamp, &r));

        LOG_I("%s: %04d-%02d-%02d %02d:%02d:%02d wday=%d yday=%d",
              c->name,
              r.tm_year + 1900, r.tm_mon + 1, r.tm_mday,
              r.tm_hour, r.tm_min, r.tm_sec,
              r.tm_wday, r.tm_yday);

        uassert_int_equal(r.tm_year, c->year);
        uassert_int_equal(r.tm_mon,  c->mon);
        uassert_int_equal(r.tm_mday, c->mday);
        uassert_int_equal(r.tm_hour, c->hour);
        uassert_int_equal(r.tm_min,  c->min);
        uassert_int_equal(r.tm_sec,  c->sec);
        uassert_int_equal(r.tm_wday, c->wday);
        uassert_int_equal(r.tm_yday, c->yday);
    }
}

/* Initialize the time conversion tests. */
static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

/* Clean up the time conversion tests. */
static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

/* Run all time conversion tests in one unit so failures are retained. */
static void timegm_all_test(void)
{
    timegm_month_boundary_test();
    timegm_leap_year_test();
    timegm_large_day_test();
    timegm_zero_day_test();
    timegm_negative_day_test();
    timegm_negative_second_test();
    timegm_negative_minute_test();
    timegm_negative_hour_test();
    timegm_negative_month_test();
    timegm_positive_overflow_test();
    timegm_combined_negative_test();
}

/* Run the time conversion test case. */
static void testcase(void)
{
    UTEST_UNIT_RUN(timegm_all_test);
    UTEST_UNIT_RUN(gmtime_r_before_epoch_test);
}

UTEST_TC_EXPORT(testcase, "components.libc.time", utest_tc_init, utest_tc_cleanup, 10);
