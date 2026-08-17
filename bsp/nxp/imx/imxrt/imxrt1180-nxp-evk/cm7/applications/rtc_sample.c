/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-14     nxp-ran      RTC test for MIMXRT1180 CM33 BBNSM driver.
 * 2026-08-16     nxp-ran      v2: updated for drv_rtc_bbnsm v2 (hw counter).
 * 2026-08-17     nxp-ran      Ported to CM7 (same BBNSM peripheral, same driver).
 */

/*
 * MSH commands for testing the BBNSM RTC driver on MIMXRT1180 CM7.
 *
 * The driver (drv_rtc_bbnsm.c) uses the BBNSM 47-bit 32768 Hz hardware
 * counter as the time source and stores a sync point (epoch + tick snapshot)
 * in battery-backed BBNSM GPR registers so time survives warm resets.
 *
 * Note: Both CM33 and CM7 share the same BBNSM peripheral.  Only one core
 * should own the RTC driver at a time to avoid conflicting GPR writes.
 *
 * Usage in FinSH/MSH console:
 *
 *   rtc_set 2025 1 1 12 0 0   -- set RTC to 2025-01-01 12:00:00 UTC
 *   rtc_get                   -- read and print current RTC time
 *   rtc_tick 10               -- print time once per second for N seconds
 *
 * Warm-reset persistence test:
 *   1.  rtc_set 2025 6 1 8 0 0
 *   2.  Wait >5 s (watch with rtc_tick 10)
 *   3.  Press reset button (or run 'reboot' command)
 *   4.  rtc_get  -- should show ~08:00:0x, NOT 1970-01-01
 *
 * Time is always handled as UTC.  No timezone conversion is applied.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

#ifdef BSP_USING_RTC

#define RTC_DEVICE_NAME "rtc"

/*
 * Convert a UTC broken-down time to a Unix epoch (seconds since
 * 1970-01-01 00:00:00 UTC) without using mktime() (which applies the
 * local timezone offset).
 */
static time_t utc_to_epoch(int y, int mo, int d, int h, int mi, int s)
{
    static const int days_in_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    long days = 0;
    int year, m;
    int leap;

    for (year = 1970; year < y; year++)
    {
        leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
        days += leap ? 366 : 365;
    }
    leap = ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
    for (m = 1; m < mo; m++)
    {
        days += (m == 2 && leap) ? 29 : days_in_month[m - 1];
    }
    days += d - 1;

    return (time_t)(days * 86400L + h * 3600L + mi * 60L + s);
}

/* ------------------------------------------------------------------
 * rtc_set  year month day hour minute second   (all UTC)
 * ------------------------------------------------------------------ */
static int rtc_set(int argc, char *argv[])
{
    int y, mo, d, h, mi, s;
    time_t epoch;
    rt_device_t dev;
    rt_err_t ret;

    if (argc != 7)
    {
        rt_kprintf("Usage: rtc_set <year> <month> <day> <hour> <minute> <second> (UTC)\r\n");
        rt_kprintf("  e.g. rtc_set 2025 6 1 8 0 0\r\n");
        return -1;
    }

    y = atoi(argv[1]);
    mo = atoi(argv[2]);
    d = atoi(argv[3]);
    h = atoi(argv[4]);
    mi = atoi(argv[5]);
    s = atoi(argv[6]);

    if (y < 1970 || mo < 1 || mo > 12 || d < 1 || d > 31 ||
        h < 0 || h > 23 || mi < 0 || mi > 59 || s < 0 || s > 59)
    {
        rt_kprintf("Invalid date/time values.\r\n");
        return -1;
    }

    epoch = utc_to_epoch(y, mo, d, h, mi, s);

    dev = rt_device_find(RTC_DEVICE_NAME);
    if (dev == RT_NULL)
    {
        rt_kprintf("RTC device '%s' not found.\r\n", RTC_DEVICE_NAME);
        return -1;
    }

    ret = rt_device_control(dev, RT_DEVICE_CTRL_RTC_SET_TIME, &epoch);
    if (ret != RT_EOK)
    {
        rt_kprintf("RT_DEVICE_CTRL_RTC_SET_TIME failed: %d\r\n", ret);
        return (int)ret;
    }

    rt_kprintf("RTC set to %04d-%02d-%02d %02d:%02d:%02d UTC (epoch=%u)\r\n",
               y, mo, d, h, mi, s, (unsigned)epoch);
    return 0;
}
MSH_CMD_EXPORT(rtc_set, set RTC(UTC) : rtc_set year month day hour minute second);

/* ------------------------------------------------------------------
 * rtc_get  -- read and display current RTC time
 * ------------------------------------------------------------------ */
static int rtc_get(int argc, char *argv[])
{
    time_t now;
    struct tm *t;

    (void)argc;
    (void)argv;

    now = time(RT_NULL);
    t = gmtime(&now);
    if (t == RT_NULL)
    {
        rt_kprintf("gmtime() failed.\r\n");
        return -1;
    }

    rt_kprintf("RTC: %04d-%02d-%02d %02d:%02d:%02d UTC  (epoch=%u)\r\n",
               t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
               t->tm_hour, t->tm_min, t->tm_sec,
               (unsigned)now);
    return 0;
}
MSH_CMD_EXPORT(rtc_get, get current RTC time(UTC));

/* ------------------------------------------------------------------
 * rtc_tick [count]  -- print time once per second for count seconds
 * ------------------------------------------------------------------ */
static int rtc_tick(int argc, char *argv[])
{
    int count = 10;
    int i;
    time_t now;
    struct tm *t;

    if (argc >= 2)
    {
        count = atoi(argv[1]);
        if (count <= 0 || count > 3600)
        {
            rt_kprintf("count must be 1..3600\r\n");
            return -1;
        }
    }

    rt_kprintf("RTC tick test (%d s):\r\n", count);
    for (i = 0; i < count; i++)
    {
        rt_thread_mdelay(1000);
        now = time(RT_NULL);
        t = gmtime(&now);
        if (t != RT_NULL)
        {
            rt_kprintf("  [%3d] %04d-%02d-%02d %02d:%02d:%02d UTC\r\n",
                       i + 1,
                       t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
                       t->tm_hour, t->tm_min, t->tm_sec);
        }
    }
    rt_kprintf("rtc_tick done.\r\n");
    return 0;
}
MSH_CMD_EXPORT(rtc_tick, print RTC time every second : rtc_tick[count]);

#endif /* BSP_USING_RTC */
