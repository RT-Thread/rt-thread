/**
 * @file os_semaphore.c
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

#include "os_semaphore.h"
#include "os_util.h"
#include <hal_sem.h>


/**
 * @brief Create and initialize a counting semaphore object
 * @param[in] sem Pointer to the semaphore object
 * @param[in] initCount The count value assigned to the semaphore when it is
 *                      created.
 * @param[in] maxCount The maximum count value that can be reached. When the
 *                     semaphore reaches this value it can no longer be
 *                     released.
 * @retval OS_Status, OS_OK on success
 */
OS_Status OS_SemaphoreCreate(OS_Semaphore_t *sem, uint32_t initCount, uint32_t maxCount)
{
//  OS_HANDLE_ASSERT(!OS_SemaphoreIsValid(sem), sem->handle);

    sem->handle = xSemaphoreCreateCounting(maxCount, initCount);
    if (sem->handle == NULL) {
        OS_ERR("err %"OS_HANDLE_F"\n", sem->handle);
        return OS_FAIL;
    }
    OS_DBG("%s,%d\n", __FUNCTION__,__LINE__);

    return OS_OK;
}

/**
 * @brief Create and initialize a binary semaphore object
 * @note A binary semaphore is equal to a counting semaphore created by calling
         OS_SemaphoreCreate(sem, 0, 1).
 * @param[in] sem Pointer to the semaphore object
 * @retval OS_Status, OS_OK on success
 */
OS_Status OS_SemaphoreCreateBinary(OS_Semaphore_t *sem)
{
//  OS_HANDLE_ASSERT(!OS_SemaphoreIsValid(sem), sem->handle);

    sem->handle = xSemaphoreCreateBinary();
    if (sem->handle == NULL) {
        OS_ERR("err %"OS_HANDLE_F"\n", sem->handle);
        return OS_FAIL;
    }

    return OS_OK;
}

/**
 * @brief Delete the semaphore object
 * @param[in] sem Pointer to the semaphore object
 * @retval OS_Status, OS_OK on success
 */
OS_Status OS_SemaphoreDelete(OS_Semaphore_t *sem)
{
    OS_HANDLE_ASSERT(OS_SemaphoreIsValid(sem), sem->handle);

    vSemaphoreDelete(sem->handle);
    OS_SemaphoreSetInvalid(sem);
    return OS_OK;
}

/**
 * @brief Wait until the semaphore object becomes available
 * @param[in] sem Pointer to the semaphore object
 * @param[in] waitMS The maximum amount of time (in millisecond) the thread
 *                   should remain in the blocked state to wait for the
 *                   semaphore to become available.
 *                   OS_WAIT_FOREVER for waiting forever, zero for no waiting.
 * @retval OS_Status, OS_OK on success
 */
OS_Status OS_SemaphoreWait(OS_Semaphore_t *sem, OS_Time_t waitMS)
{
    BaseType_t ret;
    BaseType_t taskWoken;

    OS_HANDLE_ASSERT(OS_SemaphoreIsValid(sem), sem->handle);

    if (OS_IsISRContext()) {
        if (waitMS != 0) {
            OS_ERR("%s() in ISR, wait %u ms\n", __func__, waitMS);
            return OS_E_ISR;
        }
        taskWoken = pdFALSE;
        ret = xSemaphoreTakeFromISR(sem->handle, &taskWoken);
        if (ret != pdPASS) {
            OS_DBG("%s() fail @ %d\n", __func__, __LINE__);
            return OS_E_TIMEOUT;
        }
        portEND_SWITCHING_ISR(taskWoken);
    } else {
        ret = xSemaphoreTake(sem->handle, OS_CalcWaitTicks(waitMS));
        if (ret != pdPASS) {
            OS_DBG("%s() fail @ %d, %"OS_TIME_F" ms\n", __func__, __LINE__, waitMS);
            return OS_E_TIMEOUT;
        }
    }

    return OS_OK;
}

/**
 * @brief Release the semaphore object
 * @param[in] sem Pointer to the semaphore object
 * @retval OS_Status, OS_OK on success
 */
OS_Status OS_SemaphoreRelease(OS_Semaphore_t *sem)
{
    BaseType_t ret;
    BaseType_t taskWoken;


    OS_HANDLE_ASSERT(OS_SemaphoreIsValid(sem), sem->handle);



    if (OS_IsISRContext()) {
        taskWoken = pdFALSE;
        ret = xSemaphoreGiveFromISR(sem->handle, &taskWoken);
        if (ret != pdPASS) {
            OS_DBG("%s() fail @ %d\n", __func__, __LINE__);
            return OS_FAIL;
        }
        portEND_SWITCHING_ISR(taskWoken);
    } else {
        ret = xSemaphoreGive(sem->handle);
        if (ret != pdPASS) {
            OS_DBG("%s() fail @ %d\n", __func__, __LINE__);
            return OS_FAIL;
        }
    }


    return OS_OK;
}

/**
* @brief reset the semaphore object
* @param[in] sem Pointer to the semaphore object
* @retval OS_Status, OS_OK on success
*/
OS_Status OS_SemaphoreReset(OS_Semaphore_t *sem)
{
    hal_sem_t *tmp_sem = (hal_sem_t *)sem;

    OS_HANDLE_ASSERT(OS_SemaphoreIsValid(sem), sem->handle);

    hal_sem_clear(*tmp_sem);

    return OS_OK;
}

