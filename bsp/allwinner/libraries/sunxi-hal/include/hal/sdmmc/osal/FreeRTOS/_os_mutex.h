/**
 * @file os_mutex.h
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

#ifndef _KERNEL_OS_FREERTOS_OS_MUTEX_H_
#define _KERNEL_OS_FREERTOS_OS_MUTEX_H_

#include "_os_common.h"
#include "_os_time.h"
#include "_os_thread.h"
#include "semphr.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Mutex object definition
 */
typedef struct OS_Mutex {
    SemaphoreHandle_t   handle;
} OS_Mutex_t;

OS_Status OS_MutexCreate(OS_Mutex_t *mutex);
OS_Status OS_MutexDelete(OS_Mutex_t *mutex);
OS_Status OS_MutexLock(OS_Mutex_t *mutex, OS_Time_t waitMS);
OS_Status OS_MutexUnlock(OS_Mutex_t *mutex);

OS_Status OS_RecursiveMutexCreate(OS_Mutex_t *mutex);
OS_Status OS_RecursiveMutexLock(OS_Mutex_t *mutex, OS_Time_t waitMS);
OS_Status OS_RecursiveMutexUnlock(OS_Mutex_t *mutex);

/**
 * @brief Delete the recursive mutex object
 * @param[in] mutex Pointer to the recursive mutex object
 * @retval OS_Status, OS_OK on success
 */
static __always_inline OS_Status OS_RecursiveMutexDelete(OS_Mutex_t *mutex)
{
    return OS_MutexDelete(mutex);
}

/**
 * @brief Check whether the mutex object is valid or not
 * @param[in] mutex Pointer to the mutex object
 * @return 1 on valid, 0 on invalid
 */
static __always_inline int OS_MutexIsValid(OS_Mutex_t *mutex)
{
    return (mutex->handle != OS_INVALID_HANDLE);
}

/**
 * @brief Set the mutex object to invalid state
 * @param[in] mutex Pointer to the mutex object
 * @return None
 */
static __always_inline void OS_MutexSetInvalid(OS_Mutex_t *mutex)
{
    mutex->handle = OS_INVALID_HANDLE;
}

/**
 * @brief Get the mutex object's owner
 * @note A mutex object's owner is a thread that locks the mutex
 * @param[in] mutex Pointer to the mutex object
 * @return The handle of the thread that locks the mutex object.
 *         NULL when the mutex is not locked by any thread.
 */
static __always_inline OS_ThreadHandle_t OS_MutexGetOwner(OS_Mutex_t *mutex)
{
    return (OS_ThreadHandle_t)xSemaphoreGetMutexHolder(mutex->handle);
}

#ifdef __cplusplus
}
#endif

#endif /* _KERNEL_OS_FREERTOS_OS_MUTEX_H_ */
