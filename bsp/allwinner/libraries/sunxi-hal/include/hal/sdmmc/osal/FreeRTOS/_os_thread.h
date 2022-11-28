/**
 * @file os_thread.h
 * @author ALLWINNERTECH IOT WLAN Team
 */

/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
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
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
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

#ifndef _KERNEL_OS_FREERTOS_OS_THREAD_H_
#define _KERNEL_OS_FREERTOS_OS_THREAD_H_

#include "_os_common.h"
#include "_os_time.h"
#include <FreeRTOS.h>
#include "task.h"

#ifdef __cplusplus
extern "C" {
#endif

/* thread priority */
#define OS_THREAD_PRIO_SYS_CTRL OS_PRIORITY_ABOVE_NORMAL
#define OS_THREAD_PRIO_LWIP     OS_PRIORITY_NORMAL
#define OS_THREAD_PRIO_CONSOLE  OS_PRIORITY_ABOVE_NORMAL
#define OS_THREAD_PRIO_APP      OS_PRIORITY_NORMAL

/** @brief Thread entry definition, which is a pointer to a function */
typedef TaskFunction_t OS_ThreadEntry_t;

/** @brief Thread handle definition */
typedef TaskHandle_t OS_ThreadHandle_t;

/**
 * @brief Thread object definition
 */
typedef struct OS_Thread {
    OS_ThreadHandle_t   handle;
} OS_Thread_t;

OS_Status OS_ThreadCreate(OS_Thread_t *thread, const char *name,
                          OS_ThreadEntry_t entry, void *arg,
                          OS_Priority priority, uint32_t stackSize);
OS_Status OS_ThreadDelete(OS_Thread_t *thread);

/**
 * @brief Check whether the thread object is valid or not
 * @param[in] thread Pointer to the thread object
 * @return 1 on valid, 0 on invalid
 */
static __always_inline int OS_ThreadIsValid(OS_Thread_t *thread)
{
    return (thread->handle != OS_INVALID_HANDLE);
}

/**
 * @brief Set the thread object to invalid state
 * @param[in] thread Pointer to the thread object
 * @return None
 */
static __always_inline void OS_ThreadSetInvalid(OS_Thread_t *thread)
{
    thread->handle = OS_INVALID_HANDLE;
}

/**
 * @brief Sleep for the given milliseconds
 *
 * This function causes the calling thread to sleep and block for the given
 * milliseconds.
 *
 * @param[in] msec Milliseconds to sleep
 * @return None
 */
static __always_inline void OS_ThreadSleep(OS_Time_t msec)
{
    vTaskDelay((TickType_t)OS_MSecsToTicks(msec));
}

/**
 * @brief Yield to another thread of equal priority
 *
 * Yielding is where a thread volunteers to leave the running state, without
 * being pre-empted, and before its time slice has been fully utilized.
 *
 * @return None
 */
static __always_inline void OS_ThreadYield(void)
{
    taskYIELD();
}

/**
 * @brief Get the handle of the current running thread
 * @return Handle of the current running thread
 */
static __always_inline OS_ThreadHandle_t OS_ThreadGetCurrentHandle(void)
{
    return (OS_ThreadHandle_t)xTaskGetCurrentTaskHandle();
}

/**
 * @brief Start the thread scheduler running.
 * @return None
 */
static __always_inline void OS_ThreadStartScheduler(void)
{
    vTaskStartScheduler();
}

/**
 * @brief Suspend the thread scheduler
 *
 * Suspending the scheduler prevents a context switch from occurring but leaves
 * interrupts enabled. If an interrupt requests a context switch while the
 * scheduler is suspended, then the request is held pending and is performed
 * only when the scheduler is resumed (un-suspended).
 *
 * @return None
 */
static __always_inline void OS_ThreadSuspendScheduler(void)
{
    vTaskSuspendAll();
}

/**
 * @brief Resume the thread scheduler
 *
 * Resume scheduler activity, following a previous call to
 * OS_ThreadSuspendScheduler(), by transitioning the scheduler into the
 * active state from the suspended state.
 *
 * @return None
 */
static __always_inline void OS_ThreadResumeScheduler(void)
{
    xTaskResumeAll();
}

/**
 * @brief Check whether the thread scheduler is running or not
 * @return 1 on runing, 0 on not running
 */
static __always_inline int OS_ThreadIsSchedulerRunning(void)
{
    return (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING);
}

#if INCLUDE_uxTaskGetStackHighWaterMark
uint32_t OS_ThreadGetStackMinFreeSize(OS_Thread_t *thread);
#endif

#if (configUSE_TRACE_FACILITY == 1)
void OS_ThreadList(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _KERNEL_OS_FREERTOS_OS_THREAD_H_ */
