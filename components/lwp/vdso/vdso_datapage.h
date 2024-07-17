/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
 */

#ifndef _VDSO_DATAPAGE_H
#define _VDSO_DATAPAGE_H

#include <time.h>
#include <sys/types.h>
#include "vdso_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef signed char         __s8;
typedef signed short        __s16;
typedef signed int          __s32;
typedef signed long         __s64;

typedef unsigned char       __u8;
typedef unsigned short      __u16;
typedef unsigned int        __u32;
typedef unsigned long       __u64;

#define MAX_CLOCKS          16

#define VDSO_BASES  (CLOCK_TAI + 1)
#define VDSO_REALTIME   (BIT_MASK(CLOCK_REALTIME)    | \
             BIT_MASK(CLOCK_REALTIME_COARSE))
#define VDSO_MONOTIME   (BIT_MASK(CLOCK_MONOTONIC)   | \
             BIT_MASK(CLOCK_MONOTONIC_COARSE)        | \
             BIT_MASK(CLOCK_MONOTONIC_RAW)           | \
             BIT_MASK(CLOCK_BOOTTIME))

#define CS_HRES_COARSE  0
#define CS_RAW      1
#define CS_BASES    (CS_RAW + 1)

/* 2018-01-30 14:44:50 = RTC_TIME_INIT(2018, 1, 30, 14, 44, 50)  */
#define RTC_VDSOTIME_INIT(year, month, day, hour, minute, second)        \
    {.tm_year = year - 1900, .tm_mon = month - 1, .tm_mday = day, .tm_hour = hour, .tm_min = minute, .tm_sec = second}

#ifndef SOFT_RTC_VDSOTIME_DEFAULT
#define SOFT_RTC_VDSOTIME_DEFAULT                    RTC_VDSOTIME_INIT(2018, 1, 1, 0, 0 ,0)
#endif

struct vdso_data {
    uint32_t       seq;
    uint32_t       clock_mode;
    uint64_t       realtime_initdata;
    uint64_t       cycle_last;
    struct timespec basetime[VDSO_BASES];
};
typedef struct vdso_data *vdso_data_t;

#define MSEC_PER_SEC    1000L
#define USEC_PER_MSEC   1000L
#define NSEC_PER_USEC   1000L
#define NSEC_PER_MSEC   1000000L
#define USEC_PER_SEC    1000000L
#define NSEC_PER_SEC    1000000000L
#define FSEC_PER_SEC    1000000000000000LL

#ifdef __cplusplus
}
#endif

#endif /* _VDSO_DATAPAGE_H */
