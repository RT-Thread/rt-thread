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

#include "os_timer.h"
#include "os_util.h"


/**
 * @brief Create and initialize a timer object
 *
 * @note Creating a timer does not start the timer running. The OS_TimerStart()
 *       and OS_TimerChangePeriod() API functions can all be used to start the
 *       timer running.
 *
 * @param[in] timer Pointer to the timer object
 * @param[in] type Timer type
 * @param[in] cb Timer expire callback function
 * @param[in] arg Argument of Timer expire callback function
 * @param[in] periodMS Timer period in milliseconds
 * @retval OS_Status, OS_OK on success
 */
OS_Status OS_TimerCreate(OS_Timer_t *timer, OS_TimerType type,
                         OS_TimerCallback_t cb, void *arg, OS_Time_t periodMS)
{
    rt_uint8_t flag;

    OS_HANDLE_ASSERT(!OS_TimerIsValid(timer), timer->handle);

    flag = RT_TIMER_FLAG_SOFT_TIMER;
    if (type == OS_TIMER_PERIODIC) {
        flag |= RT_TIMER_FLAG_PERIODIC;
    } else {
        flag |= RT_TIMER_FLAG_ONE_SHOT;
    }

    timer->handle = rt_timer_create("os_timer", cb, arg,
                                    OS_MSecsToTicks(periodMS), flag);
    OS_DBG("%s(), handle %p\n", __func__, timer->handle);

    if (timer->handle == NULL) {
        OS_ERR("err %"OS_HANDLE_F"\n", timer->handle);
        return OS_FAIL;
    }
    return OS_OK;
}

OS_Status OS_TimerDelete(OS_Timer_t *timer)
{
    rt_err_t ret;

    OS_DBG("%s(), handle %p\n", __func__, timer->handle);
    OS_HANDLE_ASSERT(OS_TimerIsValid(timer), timer->handle);

    ret = rt_timer_delete(timer->handle);
    if (ret != RT_EOK) {
        OS_ERR("err %"OS_BASETYPE_F"\n", ret);
        return OS_FAIL;
    }

    OS_TimerSetInvalid(timer);
    return OS_OK;
}

/**
 * @brief Start a timer running.
 * @note If the timer is already running, this function will re-start the timer.
 * @param[in] timer Pointer to the timer object
 * @retval OS_Status, OS_OK on success
 */
OS_Status OS_TimerStart(OS_Timer_t *timer)
{
    rt_err_t ret;

    OS_DBG("%s(), handle %p\n", __func__, timer->handle);
    OS_HANDLE_ASSERT(OS_TimerIsValid(timer), timer->handle);

    ret = rt_timer_start(timer->handle);
    if (ret != RT_EOK) {
        OS_ERR("err %"OS_BASETYPE_F"\n", ret);
        return OS_FAIL;
    }

    return OS_OK;
}

/**
 * @brief Change the period of a timer
 *
 * If OS_TimerChangePeriod() is used to change the period of a timer that is
 * already running, then the timer will use the new period value to recalculate
 * its expiry time. The recalculated expiry time will then be relative to when
 * OS_TimerChangePeriod() was called, and not relative to when the timer was
 * originally started.

 * If OS_TimerChangePeriod() is used to change the period of a timer that is
 * not already running, then the timer will use the new period value to
 * calculate an expiry time, and the timer will start running.
 *
 * @param[in] timer Pointer to the timer object
 * @retval OS_Status, OS_OK on success
 */
OS_Status OS_TimerChangePeriod(OS_Timer_t *timer, OS_Time_t periodMS)
{
    rt_err_t ret;

    OS_DBG("%s(), handle %p\n", __func__, timer->handle);
    OS_HANDLE_ASSERT(OS_TimerIsValid(timer), timer->handle);

    if (OS_TimerIsActive(timer)) {
        ret = rt_timer_stop(timer->handle);
        if (ret != RT_EOK) {
            OS_ERR("err %"OS_BASETYPE_F"\n", ret);
            return OS_FAIL;
        }
    }
    ret = rt_timer_control(timer->handle, RT_TIMER_CTRL_SET_TIME, &periodMS);
    if (ret != RT_EOK) {
        OS_ERR("err %"OS_BASETYPE_F"\n", ret);
        return OS_FAIL;
    }
    ret = rt_timer_start(timer->handle);
    if (ret != RT_EOK) {
        OS_ERR("err %"OS_BASETYPE_F"\n", ret);
        return OS_FAIL;
    }

    return OS_OK;
}

/**
 * @brief Stop a timer running.
 * @param[in] timer Pointer to the timer object
 * @retval OS_Status, OS_OK on success
 */
OS_Status OS_TimerStop(OS_Timer_t *timer)
{
    rt_err_t ret;

    OS_DBG("%s(), handle %p\n", __func__, timer->handle);
    OS_HANDLE_ASSERT(OS_TimerIsValid(timer), timer->handle);

    if (!OS_TimerIsActive(timer)) {
        return OS_OK;
    }

    ret = rt_timer_stop(timer->handle);
    if (ret != RT_EOK) {
        OS_ERR("err %"OS_BASETYPE_F"\n", ret);
        return OS_FAIL;
    }

    return OS_OK;
}
