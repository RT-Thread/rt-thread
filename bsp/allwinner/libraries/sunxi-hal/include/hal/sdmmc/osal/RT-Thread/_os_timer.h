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

#ifndef _KERNEL_OS_RTTHREAD_OS_TIMER_H_
#define _KERNEL_OS_RTTHREAD_OS_TIMER_H_

#include "_os_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Timer type definition
 *     - one shot timer: Timer will be in the dormant state after it expires.
 *     - periodic timer: Timer will auto-reload after it expires.
 */
typedef enum {
    OS_TIMER_ONCE       = 0, /* one shot timer */
    OS_TIMER_PERIODIC   = 1  /* periodic timer */
} OS_TimerType;

/** @brief Timer expire callback function definition */
typedef void (*OS_TimerCallback_t)(void *arg);

/** @brief Timer handle definition */
typedef rt_timer_t OS_TimerHandle_t;

typedef struct OS_Timer
{
    rt_timer_t  handle;
} OS_Timer_t;


OS_Status OS_TimerCreate(OS_Timer_t *timer, OS_TimerType type,
                         OS_TimerCallback_t cb, void *arg, OS_Time_t periodMS);
OS_Status OS_TimerDelete(OS_Timer_t *timer);
OS_Status OS_TimerStart(OS_Timer_t *timer);
OS_Status OS_TimerChangePeriod(OS_Timer_t *timer, OS_Time_t periodMS);
OS_Status OS_TimerStop(OS_Timer_t *timer);

/**
 * @brief Check whether the timer object is valid or not
 * @param[in] timer Pointer to the timer object
 * @return 1 on valid, 0 on invalid
 */
static inline int OS_TimerIsValid(OS_Timer_t *timer)
{
    return (timer->handle != OS_INVALID_HANDLE);
}

/**
 * @brief Set the timer object to invalid state
 * @param[in] timer Pointer to the timer object
 * @return None
 */
static inline void OS_TimerSetInvalid(OS_Timer_t *timer)
{
    timer->handle = OS_INVALID_HANDLE;
}

/**
 * @brief Check whether the timer is active or not
 *
 * A timer is inactive when it is in one of the following cases:
 *     - The timer has been created, but not started.
 *     - The timer is a one shot timer that has not been restarted since it
 *       expired.
 *
 * @param[in] timer Pointer to the timer object
 * @return 1 on active, 0 on inactive
 */
static inline int OS_TimerIsActive(OS_Timer_t *timer)
{
    return ((timer->handle->parent.flag & RT_TIMER_FLAG_ACTIVATED) ? 1 : 0);
}

#ifdef __cplusplus
}
#endif

#endif /* _KERNEL_OS_RTTHREAD_OS_TIMER_H_ */
