/*
 * File      : clock_time.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-31     Bernard      the first version
 */

#ifndef CLOCK_TIME_H__
#define CLOCK_TIME_H__

/* posix clock and timer */
#define MILLISECOND_PER_SECOND  1000UL
#define MICROSECOND_PER_SECOND  1000000UL
#define NANOSECOND_PER_SECOND   1000000000UL

#define MILLISECOND_PER_TICK    (MILLISECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define MICROSECOND_PER_TICK    (MICROSECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define NANOSECOND_PER_TICK     (NANOSECOND_PER_SECOND  / RT_TICK_PER_SECOND)

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME      1
#endif

#define CLOCK_CPUTIME_ID    2

#ifndef CLOCK_PROCESS_CPUTIME_ID
#define CLOCK_PROCESS_CPUTIME_ID CLOCK_CPUTIME_ID
#endif
#ifndef CLOCK_THREAD_CPUTIME_ID
#define CLOCK_THREAD_CPUTIME_ID  CLOCK_CPUTIME_ID
#endif

#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC     4
#endif

int clock_getres  (clockid_t clockid, struct timespec *res);
int clock_gettime (clockid_t clockid, struct timespec *tp);
int clock_settime (clockid_t clockid, const struct timespec *tp);

#endif
