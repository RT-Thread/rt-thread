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

#ifndef _KERNEL_OS_RTTHREAD_OS_SEMAPHORE_H_
#define _KERNEL_OS_RTTHREAD_OS_SEMAPHORE_H_

#include "_os_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Semaphore object definition
 */
typedef struct OS_Semaphore {
    rt_sem_t    handle;
} OS_Semaphore_t;

OS_Status OS_SemaphoreCreate(OS_Semaphore_t *sem, uint32_t initCount, uint32_t maxCount);
OS_Status OS_SemaphoreCreateBinary(OS_Semaphore_t *sem);
OS_Status OS_SemaphoreDelete(OS_Semaphore_t *sem);
OS_Status OS_SemaphoreWait(OS_Semaphore_t *sem, OS_Time_t waitMS);
OS_Status OS_SemaphoreRelease(OS_Semaphore_t *sem);
OS_Status OS_SemaphoreReset(OS_Semaphore_t *sem);

/**
 * @brief Check whether the semaphore object is valid or not
 * @param[in] sem Pointer to the semaphore object
 * @return 1 on valid, 0 on invalid
 */
static inline int OS_SemaphoreIsValid(OS_Semaphore_t *sem)
{
    return (sem->handle != OS_INVALID_HANDLE);
}

/**
 * @brief Set the semaphore object to invalid state
 * @param[in] sem Pointer to the semaphore object
 * @return None
 */
static inline void OS_SemaphoreSetInvalid(OS_Semaphore_t *sem)
{
    sem->handle = OS_INVALID_HANDLE;
}

#ifdef __cplusplus
}
#endif

#endif /* _KERNEL_OS_RTTHREAD_OS_SEMAPHORE_H_ */
