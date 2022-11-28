/*
 * Copyright (C) 2017 XRADIO TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of XRADIO TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _KERNEL_OS_RTTHREAD_OS_TIME_H_
#define _KERNEL_OS_RTTHREAD_OS_TIME_H_

#include "_os_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Parameters used to convert the time values */
#define OS_MSEC_PER_SEC     1000U       /* milliseconds per second */
#define OS_USEC_PER_MSEC    1000U       /* microseconds per millisecond */
#define OS_USEC_PER_SEC     1000000U    /* microseconds per second */

/* system clock's frequency, OS ticks per second */
#define OS_HZ               (RT_TICK_PER_SECOND)

/* microseconds per OS tick (1000000 / OS_HZ) */
#define OS_TICK             (OS_USEC_PER_SEC / OS_HZ)

/** @brief Get the number of ticks since OS start */
/* Due to portTICK_TYPE_IS_ATOMIC is 1, calling xTaskGetTickCount() in ISR is
 * safe also.
 */
#define OS_GetTicks()       ((OS_Time_t)rt_tick_get())

/** @brief Get the number of seconds since OS start */
#define OS_GetTime()        (OS_GetTicks() / OS_HZ)

/**
 * @brief Macros used to convert various time units to each other
 *     - Secs stand for seconds
 *     - MSecs stand for milliseconds
 *     - Ticks stand for OS ticks
 *     - Jiffies stand for OS jiffies, which is a synonym for OS ticks
 */
/* there will be return 0 ticks ,when OS_HZ less than 1000 */
/*
 *#define OS_SecsToTicks(sec)     ((OS_Time_t)(sec) * OS_HZ)
 *#define OS_MSecsToTicks(msec)   ((OS_Time_t)(msec) * (OS_USEC_PER_MSEC / OS_TICK))
*/
#define OS_SecsToTicks(sec)     ((OS_Time_t)(sec) * OS_HZ)
#define OS_MSecsToTicks(msec)   ((OS_Time_t)(msec) * OS_USEC_PER_MSEC / OS_TICK)
/*
 * there will be warned :  division by zero,so change the definition
 *#define OS_TicksToMSecs(t)      ((uint32_t)(t) / (OS_USEC_PER_MSEC / OS_TICK))
 *#define OS_TicksToSecs(t)       ((uint32_t)(t) / (OS_USEC_PER_SEC / OS_TICK))
*/
#define OS_TicksToMSecs(t)      ((uint32_t)(t) * OS_TICK / OS_USEC_PER_MSEC)
#define OS_TicksToSecs(t)       ((uint32_t)(t) * OS_TICK / OS_USEC_PER_SEC)

#define OS_GetJiffies()         OS_GetTicks()
#define OS_SecsToJiffies(sec)   OS_SecsToTicks(sec)
#define OS_MSecsToJiffies(msec) OS_MSecsToTicks(msec)
#define OS_JiffiesToMSecs(j)    OS_TicksToMSecs(j)
#define OS_JiffiesToSecs(j)     OS_TicksToSecs(j)

/**
 * @brief Macros used to sleep for the given time (milliseconds or seconds)
 */
#define OS_MSleep(msec)         rt_thread_delay((rt_tick_t)OS_MSecsToTicks(msec))
#define OS_Sleep(sec)           OS_MSleep((sec) * OS_MSEC_PER_SEC)
#define OS_SSleep(sec)          OS_Sleep(sec)

/**
 * @brief Macros used to compare time values
 *
 *  These inlines deal with timer wrapping correctly. You are
 *  strongly encouraged to use them
 *  1. Because people otherwise forget
 *  2. Because if the timer wrap changes in future you won't have to
 *     alter your code.
 *
 * OS_TimeAfter(a,b) returns true if the time a is after time b.
 *
 * Do this with "<0" and ">=0" to only test the sign of the result. A
 * good compiler would generate better code (and a really good compiler
 * wouldn't care). Gcc is currently neither.
 */
#define OS_TimeAfter(a, b)              ((int32_t)(b) - (int32_t)(a) < 0)
#define OS_TimeBefore(a, b)             OS_TimeAfter(b, a)
#define OS_TimeAfterEqual(a, b)         ((int32_t)(a) - (int32_t)(b) >= 0)
#define OS_TimeBeforeEqual(a, b)        OS_TimeAfterEqual(b, a)

/** @brief Macros used to generate fake random 32-bit value */
/* The fake random 32-bit value is generated by combining OS ticks and
 * the value of rand().
 */
int rand(void);
#define OS_Rand32() ((uint32_t)((rand() & 0xffffff) | (OS_GetTicks() << 24)))

#ifdef __cplusplus
}
#endif

#endif /* _KERNEL_OS_RTTHREAD_OS_TIME_H_ */
