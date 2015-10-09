/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if defined (FSL_RTOS_FREE_RTOS)

#include <string.h>
#include <assert.h>
#include "fsl_os_abstraction.h"
#include "fsl_interrupt_manager.h"

/*! @brief Converts milliseconds to ticks*/
#define MSEC_TO_TICK(msec)  (((uint32_t)(msec)+500uL/(uint32_t)configTICK_RATE_HZ) \
                             *(uint32_t)configTICK_RATE_HZ/1000uL)
#define TICKS_TO_MSEC(tick) ((tick)*1000uL/(uint32_t)configTICK_RATE_HZ)

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_SemaCreate
 * Description   : This function is used to create a semaphore. Return
 * kStatus_OSA_Success if create successfully, otherwise return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaCreate(semaphore_t *pSem, uint8_t initValue)
{
    assert(pSem);

    *pSem = xSemaphoreCreateCounting(0xFF, initValue);
    if (*pSem==NULL)
    {
        return kStatus_OSA_Error; /* creating semaphore failed */
    }
    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_SemaWait
 * Description   : This function checks the semaphore's counting value, if it is
 * positive, decreases it and returns kStatus_OSA_Success, otherwise, timeout
 * will be used for wait. The parameter timeout indicates how long should wait
 * in milliseconds. Pass OSA_WAIT_FOREVER to wait indefinitely, pass 0 will
 * return kStatus_OSA_Timeout immediately if semaphore is not positive.
 * This function returns kStatus_OSA_Success if the semaphore is received, returns
 * kStatus_OSA_Timeout if the semaphore is not received within the specified
 * 'timeout', returns kStatus_OSA_Error if any errors occur during waiting.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaWait(semaphore_t *pSem, uint32_t timeout)
{
    uint32_t timeoutTicks;
    assert(pSem);

    /* Convert timeout from millisecond to tick. */
    if (timeout == OSA_WAIT_FOREVER)
    {
        timeoutTicks = portMAX_DELAY;
    }
    else
    {
        timeoutTicks = MSEC_TO_TICK(timeout);
    }

    if (xSemaphoreTake(*pSem, timeoutTicks)==pdFALSE)
    {
        return kStatus_OSA_Timeout; /* timeout */
    }
    else
    {
        return kStatus_OSA_Success; /* semaphore taken */
    }
}

static osa_status_t OSA_SemaphorePostFromTask(semaphore_t *pSem)
{
    if (pdTRUE == xSemaphoreGive(*pSem))
    {
        return kStatus_OSA_Success; /* sync object given */
    }
    else
    {
        return kStatus_OSA_Error;
    }
}

static osa_status_t OSA_SemaphorePostFromISR(semaphore_t *pSem)
{
    portBASE_TYPE taskToWake = pdFALSE;

    if (pdTRUE==xSemaphoreGiveFromISR(*pSem, &taskToWake))
    {
        if (pdTRUE == taskToWake)
        {
            vPortYieldFromISR();
        }
        return kStatus_OSA_Success;
    }
    else
    {
        return kStatus_OSA_Error;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_SemaPost
 * Description   : This function is used to wake up one task that wating on the
 * semaphore. If no task is waiting, increase the semaphore. The function returns
 * kStatus_OSA_Success if the semaphre is post successfully, otherwise returns
 * kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaPost(semaphore_t *pSem)
{
    assert(pSem);

    if (__get_IPSR())
    {
        return OSA_SemaphorePostFromISR(pSem);
    }
    else
    {
        return OSA_SemaphorePostFromTask(pSem);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_SemaDestroy
 * Description   : This function is used to destroy a semaphore.
 * Return kStatus_OSA_Success if the semaphore is destroyed successfully, otherwise
 * return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaDestroy(semaphore_t *pSem)
{
    assert(pSem);
    assert(*pSem);

    vSemaphoreDelete(*pSem);
    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MutexCreate
 * Description   : This function is used to create a mutex.
 * Return kStatus_OSA_Success if create successfully, otherwise return
 * kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_MutexCreate(mutex_t *pMutex)
{
    assert(pMutex);
    *pMutex = xSemaphoreCreateMutex();
    if (NULL == *pMutex)
    {
        return kStatus_OSA_Error;
    }
    else
    {
        return kStatus_OSA_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MutexLock
 * Description   : This function checks the mutex's status, if it is unlocked,
 * lock it and returns kStatus_OSA_Success, otherwise, timeout will be used for
 * wait. The parameter timeout indicates how long should wait in milliseconds.
 * Pass OSA_WAIT_FOREVER to wait indefinitely, pass 0 will return the value
 * kStatus_OSA_Timeout immediately if mutex is locked.
 * This function returns kStatus_OSA_Success if the mutex is obtained, returns
 * kStatus_OSA_Timeout if the mutex is not obtained within the specified
 * 'timeout', returns kStatus_OSA_Error if any errors occur during waiting.
 *
 *END**************************************************************************/
osa_status_t OSA_MutexLock(mutex_t *pMutex, uint32_t timeout)
{
    uint32_t timeoutTicks;

    assert(pMutex);

    /* If pMutex has been locked by current task, return error. */
    if (xSemaphoreGetMutexHolder(*pMutex) == xTaskGetCurrentTaskHandle())
    {
        return kStatus_OSA_Error;
    }

    /* Convert timeout from millisecond to tick. */
    if (timeout == OSA_WAIT_FOREVER)
    {
        timeoutTicks = portMAX_DELAY;
    }
    else
    {
        timeoutTicks = MSEC_TO_TICK(timeout);
    }

    if (xSemaphoreTake(*pMutex, timeoutTicks)==pdFALSE)
    {
        return kStatus_OSA_Timeout; /* timeout */
    }
    else
    {
        return kStatus_OSA_Success; /* semaphore taken */
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MutexUnlock
 * Description   : This function is used to unlock a mutex.
 *
 *END**************************************************************************/
osa_status_t OSA_MutexUnlock(mutex_t *pMutex)
{
    assert(pMutex);

    /* If pMutex is not locked by current task, return error. */
    if (xSemaphoreGetMutexHolder(*pMutex) != xTaskGetCurrentTaskHandle())
    {
        return kStatus_OSA_Error;
    }

    if (xSemaphoreGive(*pMutex)==pdPASS)
    {
        return kStatus_OSA_Success;
    }
    else
    {
        return kStatus_OSA_Error;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MutexDestroy
 * Description   : This function is used to destroy a mutex.
 * Return kStatus_OSA_Success if the lock object is destroyed successfully,
 * otherwise return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_MutexDestroy(mutex_t *pMutex)
{
    assert(pMutex);
    assert(*pMutex);

    vSemaphoreDelete(*pMutex);
    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EventCreate
 * Description   : This function is used to create a event object. Return
 * kStatus_OSA_Success if create successfully, otherwise return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_EventCreate(event_t *pEvent, osa_event_clear_mode_t clearMode)
{
    assert(pEvent);

    pEvent->eventHandler = xEventGroupCreate();

    if (pEvent->eventHandler)
    {
        pEvent->clearMode = clearMode;
        return kStatus_OSA_Success;
    }
    else
    {
        return kStatus_OSA_Error;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EventWait
 * Description   : This function checks the event's status, if it meets the wait
 * condition, return kStatus_OSA_Success, otherwise, timeout will be used for
 * wait. The parameter timeout indicates how long should wait in milliseconds.
 * Pass OSA_WAIT_FOREVER to wait indefinitely, pass 0 will return the value
 * kStatus_OSA_Timeout immediately if wait condition is not met. The event flags
 * will be cleared if the event is auto clear mode. Flags that wakeup waiting
 * task could be obtained from the parameter setFlags.
 * This function returns kStatus_OSA_Success if wait condition is met, returns
 * kStatus_OSA_Timeout if wait condition is not met within the specified
 * 'timeout', returns kStatus_OSA_Error if any errors occur during waiting.
 *
 *END**************************************************************************/
osa_status_t OSA_EventWait(event_t       *pEvent,
                        event_flags_t  flagsToWait,
                        bool           waitAll,
                        uint32_t       timeout,
                        event_flags_t *setFlags)
{
    assert(pEvent);
    BaseType_t clearMode;
    uint32_t timeoutTicks;
    event_flags_t flagsSave;

    /* Convert timeout from millisecond to tick. */
    if (timeout == OSA_WAIT_FOREVER)
    {
        timeoutTicks = portMAX_DELAY;
    }
    else
    {
        timeoutTicks = timeout/portTICK_PERIOD_MS;
    }

    clearMode = (kEventAutoClear == pEvent->clearMode) ? pdTRUE: pdFALSE;

    flagsSave = xEventGroupWaitBits(pEvent->eventHandler,
                                    flagsToWait,
                                    clearMode,
                                    (BaseType_t)waitAll,
                                    timeoutTicks);

    *setFlags = flagsSave & flagsToWait;

    if (*setFlags)
    {
        return kStatus_OSA_Success;
    }
    else
    {
        return kStatus_OSA_Timeout;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EventSet
 * Description   : Set one or more event flags of an event object.
 * Return kStatus_OSA_Success if set successfully, kStatus_OSA_Error if failed.
 *
 *END**************************************************************************/
osa_status_t OSA_EventSet(event_t *pEvent, event_flags_t flagsToSet)
{
    assert(pEvent);
    portBASE_TYPE taskToWake = pdFALSE;

    if (__get_IPSR())
    {
        xEventGroupSetBitsFromISR(pEvent->eventHandler, flagsToSet, &taskToWake);
        if (pdTRUE == taskToWake)
        {
            vPortYieldFromISR();
        }
    }
    else
    {
        xEventGroupSetBits(pEvent->eventHandler, flagsToSet);
    }
    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EventClear
 * Description   : Clear one or more event flags of an event object.
 * Return kStatus_OSA_Success if clear successfully, kStatus_OSA_Error if failed.
 *
 *END**************************************************************************/
osa_status_t OSA_EventClear(event_t *pEvent, event_flags_t flagsToClear)
{
    assert(pEvent);

	if (__get_IPSR())
	{
	    xEventGroupClearBitsFromISR(pEvent->eventHandler, flagsToClear);
	}
	else
	{
        xEventGroupClearBits(pEvent->eventHandler, flagsToClear);
    }

    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EventGetFlags
 * Description   : Get event flags status.
 * Return current event flags.
 *
 *END**************************************************************************/
event_flags_t OSA_EventGetFlags(event_t *pEvent)
{
    assert(pEvent);

    if (__get_IPSR())
    {
        return xEventGroupGetBitsFromISR(pEvent->eventHandler);
    }
    else
    {
        return xEventGroupGetBits(pEvent->eventHandler);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EventDestroy
 * Description   : This function is used to destroy a event object. Return
 * kStatus_OSA_Success if the event object is destroyed successfully, otherwise
 * return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_EventDestroy(event_t *pEvent)
{
    assert(pEvent);
	vEventGroupDelete(pEvent->eventHandler);
    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskCreate
 * Description   : This function is used to create a task and make it ready.
 * Return kStatus_OSA_Success if register successfully, otherwise return
 * kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_TaskCreate(task_t          task,
                         uint8_t        *name,
                         uint16_t        stackSize,
                         task_stack_t   *stackMem,
                         uint16_t        priority,
                         task_param_t    param,
                         bool            usesFloat,
                         task_handler_t *handler)
{
    if (xTaskCreate(
            task,  /* pointer to the task */
            (char const*)name, /* task name for kernel awareness debugging */
            stackSize/sizeof(portSTACK_TYPE), /* task stack size */
            param, /* optional task startup argument */
            PRIORITY_OSA_TO_RTOS(priority),  /* initial priority */
            handler /* optional task handle to create */
        ) != pdPASS)
    {
        return kStatus_OSA_Error; /* error! probably out of memory */
    }
    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskDestroy
 * Description   : This function destroy a task. Return kStatus_OSA_Success if
 * the task is destroied, otherwise return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_TaskDestroy(task_handler_t handler)
{
#if INCLUDE_vTaskDelete /* vTaskDelete() enabled */
      vTaskDelete(handler);
      return kStatus_OSA_Success;
#else
      return kStatus_OSA_Error; /* vTaskDelete() not available */
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskYield
 * Description   : When a task calls this function, it will give up CPU and put
 * itself to the tail of ready list.
 *
 *END**************************************************************************/
osa_status_t OSA_TaskYield(void)
{
    taskYIELD();
    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskGetHandler
 * Description   : This function is used to get current active task's handler.
 *
 *END**************************************************************************/
task_handler_t OSA_TaskGetHandler(void)
{
    return xTaskGetCurrentTaskHandle();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskGetPriority
 * Description   : This function returns task's priority by task handler.
 *
 *END**************************************************************************/
uint16_t OSA_TaskGetPriority(task_handler_t handler)
{
    return (uint16_t)(PRIORITY_RTOS_TO_OSA(uxTaskPriorityGet(handler)));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskSetPriority
 * Description   : This function sets task's priority by task handler.
 *
 *END**************************************************************************/
osa_status_t OSA_TaskSetPriority(task_handler_t handler, uint16_t priority)
{
    vTaskPrioritySet(handler, PRIORITY_OSA_TO_RTOS(priority));
    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MsgQCreate
 * Description   : This function is used to create a message queue.
 * Return the handle to the message queue if create successfully, otherwise
 * return 0.
 *
 *END**************************************************************************/
msg_queue_handler_t OSA_MsgQCreate(msg_queue_t *queue,
                                        uint16_t  message_number,
                                        uint16_t  message_size)
{
    return xQueueCreate(message_number, message_size*sizeof(uint32_t));
}

static osa_status_t OSA_MessageQueuePutFromTask(msg_queue_handler_t handler, void* pMessage)
{
    if (xQueueSendToBack(handler, pMessage, 0)!=pdPASS)
    {
      return kStatus_OSA_Error; /* not able to send it to the queue? */
    }
    else
    {
      return kStatus_OSA_Success;
    }
}

static osa_status_t OSA_MessageQueuePutFromISR(msg_queue_handler_t handler, void* pMessage)
{
    portBASE_TYPE taskToWake = pdFALSE;

    if (pdTRUE == xQueueSendToBackFromISR(handler, pMessage, &taskToWake))
    {
        if (pdTRUE == taskToWake)
        {
            vPortYieldFromISR();
        }
        return kStatus_OSA_Success;
    }
    else
    {
        return kStatus_OSA_Error;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MsgQPut
 * Description   : This function is used to put a message to a message queue.
 * Return kStatus_OSA_Success if the message is put successfully, otherwise
 * return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_MsgQPut(msg_queue_handler_t handler, void* pMessage)
{
    if (__get_IPSR())
    {
        return OSA_MessageQueuePutFromISR(handler, pMessage);
    }
    else
    {
        return OSA_MessageQueuePutFromTask(handler, pMessage);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MsgQGet
 * Description   : This function checks the queue's status, if it is not empty,
 * get message from it and return kStatus_OSA_Success, otherwise, timeout will
 * be used for wait. The parameter timeout indicates how long should wait in
 * milliseconds. Pass OSA_WAIT_FOREVER to wait indefinitely, pass 0 will return
 * kStatus_OSA_Timeout immediately if queue is empty.
 * This function returns kStatus_OSA_Success if message is got successfully,
 * returns kStatus_OSA_Timeout if message queue is empty within the specified
 * 'timeout', returns kStatus_OSA_Error if any errors occur during waiting.
 *
 *END**************************************************************************/
osa_status_t OSA_MsgQGet(msg_queue_handler_t handler,
                           void               *pMessage,
                           uint32_t            timeout)
{
    uint32_t timeoutTicks;

    if (timeout == OSA_WAIT_FOREVER)
    {
        timeoutTicks = portMAX_DELAY;
    }
    else
    {
        timeoutTicks = MSEC_TO_TICK(timeout);
    }
    if (xQueueReceive(handler, pMessage, timeoutTicks)!=pdPASS)
    {
        return kStatus_OSA_Timeout; /* not able to send it to the queue? */
    }
    else
    {
        return kStatus_OSA_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MsgQDestroy
 * Description   : This function is used to destroy the message queue.
 * Return kStatus_OSA_Success if the message queue is destroyed successfully,
 * otherwise return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_MsgQDestroy(msg_queue_handler_t handler)
{
    vQueueDelete(handler);
    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MemAlloc
 * Description   : This function is used to allocate amount of memory in bytes.
 * Return the pointer to the memory if success, otherwise return NULL;
 *
 *END**************************************************************************/
void *OSA_MemAlloc(size_t size)
{
    return pvPortMalloc(size);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MemAllocZero
 * Description   : This function is used to allocate amount of memory in bytes
 * and initializes it to 0.
 * Return the pointer to the memory if success, otherwise return NULL;
 *
 *END**************************************************************************/
void * OSA_MemAllocZero(size_t size)
{
    void *ptr = pvPortMalloc(size);

    if (ptr==NULL)
    {
      return NULL; /* failed allocating memory */
    }
    return memset(ptr, 0, size);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MemFree
 * Description   : This function is used to free the memory previously allocated.
 *
 *END**************************************************************************/
osa_status_t OSA_MemFree(void *ptr)
{
    vPortFree(ptr);
    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TimeDelay
 * Description   : This function is used to delay for a number of milliseconds.
 *
 *END**************************************************************************/
void OSA_TimeDelay(uint32_t delay)
{
    vTaskDelay(MSEC_TO_TICK(delay));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TimeGetMsec
 * Description   : This function gets current time in milliseconds.
 *
 *END**************************************************************************/
uint32_t OSA_TimeGetMsec(void)
{
    portTickType ticks;

    if (__get_IPSR())
    {
        ticks = xTaskGetTickCountFromISR();
    }
    else
    {
        ticks = xTaskGetTickCount();
    }

    return TICKS_TO_MSEC(ticks);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_InstallIntHandler
 * Description   : This function is used to install interrupt handler.
 *
 *END**************************************************************************/
osa_int_handler_t OSA_InstallIntHandler(int32_t IRQNumber,
                                        osa_int_handler_t handler)
{
#if defined ( __IAR_SYSTEMS_ICC__ )
_Pragma ("diag_suppress = Pm138")
#endif
    return (osa_int_handler_t)INT_SYS_InstallHandler((IRQn_Type)IRQNumber, handler);
#if defined ( __IAR_SYSTEMS_ICC__ )
_Pragma ("diag_remark = PM138")
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EnterCritical
 * Description   : This function is used to ensure some code will not be preempted.
 *
 *END**************************************************************************/
static uint32_t g_base_priority_array[OSA_MAX_ISR_CRITICAL_SECTION_DEPTH];
static int32_t  g_base_priority_top = 0;
void OSA_EnterCritical(osa_critical_section_mode_t mode)
{
    if (kCriticalDisableInt == mode)
    {
        if (__get_IPSR())
        {
            assert(g_base_priority_top < OSA_MAX_ISR_CRITICAL_SECTION_DEPTH);

            g_base_priority_array[g_base_priority_top] = portSET_INTERRUPT_MASK_FROM_ISR();
            g_base_priority_top++;
        }
        else
        {
            portENTER_CRITICAL();
        }
    }
    else
    {
        vTaskSuspendAll();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_ExitCritical
 * Description   : This function is used to exit critical section.
 *
 *END**************************************************************************/
void OSA_ExitCritical(osa_critical_section_mode_t mode)
{
    if (kCriticalDisableInt == mode)
    {
        if (__get_IPSR())
        {
            g_base_priority_top--;
            assert(g_base_priority_top >= 0);

            portCLEAR_INTERRUPT_MASK_FROM_ISR(g_base_priority_array[g_base_priority_top]);
        }
        else
        {
            portEXIT_CRITICAL();
        }
    }
    else
    {
        xTaskResumeAll();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_Init
 * Description   : This function is used to setup the basic services, it should
 * be called first in function main. Return kStatus_OSA_Success if services
 * are initialized successfully, otherwise return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_Init(void)
{
    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_Start
 * Description   : This function is used to start RTOS scheduler.
 *
 *END**************************************************************************/
osa_status_t OSA_Start(void)
{
    vTaskStartScheduler();
    return kStatus_OSA_Success;
}

#endif /* FSL_RTOS_FREE_RTOS */

/*******************************************************************************
 * EOF
 ******************************************************************************/
