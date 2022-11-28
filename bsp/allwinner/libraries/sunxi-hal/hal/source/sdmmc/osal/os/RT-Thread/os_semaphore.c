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

#include "os_semaphore.h"
#include "os_util.h"


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

    sem->handle = rt_sem_create("os_sem", initCount, RT_IPC_FLAG_PRIO);
    OS_DBG("%s(), handle %p\n", __func__, sem->handle);

    if (sem->handle == NULL) {
        OS_ERR("err %"OS_HANDLE_F"\n", sem->handle);
        return OS_FAIL;
    }

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
    OS_ERR("OS_SemaphoreCreateBinary() NOT SUPPORT!\n");

    return OS_SemaphoreCreate(sem, 0, 1);
}

/**
 * @brief Delete the semaphore object
 * @param[in] sem Pointer to the semaphore object
 * @retval OS_Status, OS_OK on success
 */
OS_Status OS_SemaphoreDelete(OS_Semaphore_t *sem)
{
    rt_err_t ret;

    OS_HANDLE_ASSERT(OS_SemaphoreIsValid(sem), sem->handle);

    ret = rt_sem_delete(sem->handle);
    if (ret != RT_EOK) {
        OS_ERR("err %"OS_BASETYPE_F"\n", ret);
        return OS_FAIL;
    }
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
    rt_err_t ret;

    OS_DBG("%s(), handle %p, wait %u ms\n", __func__, sem->handle, (unsigned int)waitMS);
    OS_HANDLE_ASSERT(OS_SemaphoreIsValid(sem), sem->handle);

    ret = rt_sem_take(sem->handle, OS_CalcWaitTicks(waitMS));
    if (ret != RT_EOK) {
        OS_DBG("%s() fail @ %d, %"OS_TIME_F" ms\n", __func__, __LINE__, (unsigned int)waitMS);
        return OS_E_TIMEOUT;
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
    rt_err_t ret;

    OS_HANDLE_ASSERT(OS_SemaphoreIsValid(sem), sem->handle);

    ret = rt_sem_release(sem->handle);
    if (ret != RT_EOK) {
        OS_DBG("%s() fail @ %d\n", __func__, __LINE__);
        return OS_FAIL;
    }

    return OS_OK;
}

/**
 * @brief Release the semaphore object
 * @param[in] sem Pointer to the semaphore object
 * @retval OS_Status, OS_OK on success
 */
OS_Status OS_SemaphoreReset(OS_Semaphore_t *sem)
{
    rt_err_t ret;

    OS_HANDLE_ASSERT(OS_SemaphoreIsValid(sem), sem->handle);

    ret = rt_sem_control(sem->handle, RT_IPC_CMD_RESET, NULL);
    if (ret != RT_EOK) {
        OS_DBG("%s() fail @ %d\n", __func__, __LINE__);
        return OS_FAIL;
    }

    return OS_OK;
}
