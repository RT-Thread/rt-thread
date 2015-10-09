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
#if defined (FSL_RTOS_UCOSII)

#include <assert.h>
#include "fsl_os_abstraction.h"
#include "fsl_interrupt_manager.h"

extern uint32_t SystemCoreClock;

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Converts milliseconds to ticks*/
#define MSEC_TO_TICK(msec)  (((INT32U)(msec)+500uL/OS_TICKS_PER_SEC)*OS_TICKS_PER_SEC/1000uL)
#define TICKS_TO_MSEC(tick) ((tick)*1000uL/OS_TICKS_PER_SEC)

/*******************************************************************************
 * Code
 ******************************************************************************/

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
    INT8U err;

#if OS_CRITICAL_METHOD == 3U
    OS_CPU_SR   cpu_sr = 0U;
#endif

    uint32_t stackSizeLocal = stackSize/sizeof(task_stack_t);
    /*
     * To provide unified task piority for upper layer, OSA layer makes conversion.
     * uC/OS-II's highest 4 priorities are reserved for system, so add 4 here.
     */
    INT8U localPriority = PRIORITY_OSA_TO_RTOS(priority);

    err = OSTaskCreateExt(task,            /* Task pointer*/
                          param,           /* Task input parameter*/
                          &stackMem[stackSizeLocal - 1],   /* Pointer to top of stack*/
                          localPriority,   /* Task priority*/
                          localPriority,   /* Task id. should be the same as priority*/
                          stackMem,        /* Pointer to the bottom of the stack*/
                          stackSizeLocal,  /* Size of the stack*/
                          (void*)0,   /* TCB extension not supported by this abstraction*/
                          usesFloat ? OS_TASK_OPT_SAVE_FP : OS_TASK_OPT_NONE
                          );
    if (OS_ERR_NONE != err)
    {
        return kStatus_OSA_Error;
    }
#if OS_TASK_NAME_EN > 0u
    OSTaskNameSet(localPriority, name, &err);
    if (OS_ERR_NONE != err)
    {
        return kStatus_OSA_Error;
    }
#else
    name = name;
#endif
    OS_ENTER_CRITICAL();
    *handler = OSTCBPrioTbl[localPriority];
    OS_EXIT_CRITICAL();
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
    if (OS_ERR_NONE == OSTaskDel(handler->OSTCBPrio))
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
 * Function Name : OSA_TaskYield
 * Description   : This function is not implemented, because one task priority
 * can not be shared by multi-tasks on uC/OS-II.
 *
 *END**************************************************************************/
osa_status_t OSA_TaskYield(void)
{
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
    return OSTCBCur;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskGetPriority
 * Description   : This function returns task's priority by task handler.
 *
 *END**************************************************************************/
uint16_t OSA_TaskGetPriority(task_handler_t handler)
{
    return (uint16_t)PRIORITY_RTOS_TO_OSA(handler->OSTCBPrio);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskSetPriority
 * Description   : This function sets task's priority by task handler.
 *
 *END**************************************************************************/
osa_status_t OSA_TaskSetPriority(task_handler_t handler, uint16_t priority)
{
    if (OS_ERR_NONE == OSTaskChangePrio(handler->OSTCBPrio, PRIORITY_OSA_TO_RTOS(priority)))
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
 * Function Name : wait_timeout_msec_to_tick
 * Description   : This function converts timeout from millisecond to tick for
 * wait functions.
 *
 *END**************************************************************************/
static uint32_t wait_timeout_msec_to_tick(uint32_t timeout)
{
    if (OSA_WAIT_FOREVER == timeout)   /* Wait forever. */
    {
        return 0U; /* Timeout 0 means wait forever for uC/OS-II. */
    }
    else
    {
        timeout = MSEC_TO_TICK(timeout); /* Change timeout to tick. */
        /*
         * If timeout is too short that changed to 0 tick, reset it to 1 tick
         * in case of infinitely wait.
         */
        if (!timeout)
        {
            timeout = 1U;
        }
        return timeout;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_SemaCreate
 * Description   : This function is used to create a semaphore. Return
 * kStatus_OSA_Success if create successfully, otherwise return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaCreate(semaphore_t *pSem, uint8_t initValue)
{
    *pSem = OSSemCreate(initValue);

    if (*pSem)
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
    INT8U err;

    /* If timeout is 0, try to get the semaphore. */
    if (!timeout)
    {
        if (OSSemAccept(*pSem) > 0)
        {
            return kStatus_OSA_Success;
        }
        else
        {
            return kStatus_OSA_Timeout;
        }
    }

    /* If timeout is not 0, convert it to tickes. */
    timeout = wait_timeout_msec_to_tick(timeout);

    OSSemPend(*pSem, timeout, &err);

    if (OS_ERR_NONE == err)
    {
        return kStatus_OSA_Success;
    }
    else if (OS_ERR_TIMEOUT == err)
    {
        return kStatus_OSA_Timeout;
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
    if (OS_ERR_NONE == OSSemPost(*pSem))
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
 * Function Name : OSA_SemaDestroy
 * Description   : This function is used to destroy a semaphore.
 * Return kStatus_OSA_Success if the semaphore is destroyed successfully, otherwise
 * return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaDestroy(semaphore_t *pSem)
{
    INT8U err;

    OSSemDel(*pSem, OS_DEL_ALWAYS, &err);

    if (OS_ERR_NONE == err)
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
 * Function Name : OSA_MutexCreate
 * Description   : This function is used to create a mutex.
 * Return kStatus_OSA_Success if create successfully, otherwise return
 * kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_MutexCreate(mutex_t *pMutex)
{
    INT8U err;

    /* NOTE: uC/OS-II does not support priority inherit but only priority protect */
    *pMutex = OSMutexCreate(OS_PRIO_MUTEX_CEIL_DIS, &err);

    if (OS_ERR_NONE == err)
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
    INT8U err;

    /* Avoid to get the mutex current task has already got. */
    if ((*pMutex)->OSEventPtr == (void *)OSTCBCur)
    {
        return kStatus_OSA_Error;
    }

    if (!timeout) /* If timeout is 0, try to lock the mutex. */
    {
        BOOLEAN pollResult = OSMutexAccept(*pMutex, &err);

        if (OS_ERR_NONE == err)
        {
            if (OS_TRUE == pollResult)
            {
                return kStatus_OSA_Success;
            }
            else
            {
                return kStatus_OSA_Timeout;
            }
        }
        else
        {
            return kStatus_OSA_Error;
        }
    }

    /* If timeout is not 0, convert it to tickes. */
    timeout = wait_timeout_msec_to_tick(timeout);

    OSMutexPend(*pMutex, timeout, &err);

    if (OS_ERR_NONE == err)
    {
        return kStatus_OSA_Success;
    }
    else if (OS_ERR_TIMEOUT == err)
    {
        return kStatus_OSA_Timeout;
    }
    else
    {
        return kStatus_OSA_Error;
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
    if (OS_ERR_NONE == OSMutexPost(*pMutex))
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
    INT8U err;

    OSMutexDel(*pMutex, OS_DEL_ALWAYS, &err);

    if (OS_ERR_NONE == err)
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
 * Function Name : OSA_EventCreate
 * Description   : This function is used to create a event object. Return
 * kStatus_OSA_Success if create successfully, otherwise return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_EventCreate(event_t *pEvent, osa_event_clear_mode_t clearMode)
{
    INT8U err;
    pEvent->pGroup = OSFlagCreate(0u, &err);
    if (OS_ERR_NONE == err)
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
    INT8U err, opt;

    /* Prepare wait options base on wait type and clear type. */
    if (waitAll)
    {
        opt = OS_FLAG_WAIT_SET_ALL;
    }
    else
    {
        opt = OS_FLAG_WAIT_SET_ANY;
    }

    if (kEventAutoClear == pEvent->clearMode)
    {
        opt |= OS_FLAG_CONSUME;
    }

    /* If timeout is 0, try to wait. */
    if (0U == timeout)
    {
        *setFlags = OSFlagAccept (pEvent->pGroup, flagsToWait, opt, &err);
    }
    else
    {
        /* If timeout is not 0, convert it to tickes. */
        timeout = wait_timeout_msec_to_tick(timeout);
        *setFlags = OSFlagPend(pEvent->pGroup, flagsToWait, opt, timeout, &err);
    }

    if (OS_ERR_NONE == err)
    {
        return kStatus_OSA_Success;
    }
    else if ((OS_ERR_TIMEOUT      == err) ||
             (OS_ERR_FLAG_NOT_RDY == err))
    {
        return kStatus_OSA_Timeout;
    }
    else
    {
        return kStatus_OSA_Error;
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
    INT8U err;

    OSFlagPost(pEvent->pGroup, flagsToSet, OS_FLAG_SET, &err);

    if (OS_ERR_NONE == err)
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
 * Function Name : OSA_EventClear
 * Description   : Clear one or more event flags of an event object.
 * Return kStatus_OSA_Success if clear successfully, kStatus_OSA_Error if failed.
 *
 *END**************************************************************************/
osa_status_t OSA_EventClear(event_t *pEvent, event_flags_t flagsToClear)
{
    INT8U err;

    OSFlagPost(pEvent->pGroup, flagsToClear, OS_FLAG_CLR, &err);

    if (OS_ERR_NONE == err)
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
 * Function Name : OSA_EventGetFlags
 * Description   : Get event flags status.
 * Return current event flags.
 *
 *END**************************************************************************/
event_flags_t OSA_EventGetFlags(event_t *pEvent)
{
    INT8U err;
    return OSFlagQuery(pEvent->pGroup, &err);
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
    INT8U err;

    OSFlagDel(pEvent->pGroup, OS_DEL_ALWAYS, &err);

    if (OS_ERR_NONE == err)
    {
        pEvent->pGroup = (OS_FLAG_GRP*)0;
        return kStatus_OSA_Success;
    }
    else
    {
        return kStatus_OSA_Error;
    }
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
    INT8U  err;

    queue->pQueue = OSQCreate(queue->msgTbl, message_number);
    if (!queue->pQueue)
    {
        return (msg_queue_handler_t)0;
    }

    /* Use OS_MEM to manage the memory which is used to save messages*/
    queue->pMem = OSMemCreate(queue->msgs,
                              message_number,
                              message_size*sizeof(int32_t),
                              &err);
    if (!queue->pMem)
    {
        OSQDel(queue->pQueue, OS_DEL_ALWAYS, &err);
        return (msg_queue_handler_t)0;
    }

    queue->size = message_size;
    return (msg_queue_handler_t)queue;
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
    INT8U err;
    void  *localMsg;
    int32_t  *from_ptr, *to_ptr;
    uint32_t msg_size = handler->size;

    /* Get a memory to save the message. */
    localMsg = OSMemGet(handler->pMem, &err);
    if (!localMsg)
    {
        return kStatus_OSA_Error;
    }

    /* Copy msg to localMsg */
    from_ptr = (int32_t*)pMessage;
    to_ptr   = (int32_t*)localMsg;
    while (msg_size--)
    {
        *to_ptr++ = *from_ptr++;
    }

    if (OS_ERR_NONE != OSQPost(handler->pQueue, localMsg))
    {
        OSMemPut(handler->pMem, localMsg);
        return kStatus_OSA_Error;
    }

    return kStatus_OSA_Success;
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
    INT8U err;
    void* localMsg;
    int32_t  *from_ptr, *to_ptr;
    uint16_t msg_size = handler->size;

    if (0U != timeout)
    {
        /* If timeout is not 0, convert it to tickes. */
        timeout  = wait_timeout_msec_to_tick(timeout);
        localMsg = OSQPend(handler->pQueue, timeout, &err);
    }
    else
    {
        localMsg = OSQAccept(handler->pQueue, &err);
    }

    if (OS_ERR_NONE == err)
    {
        /* Copy localMsg to msg */
        to_ptr   = (int32_t*)(pMessage);
        from_ptr = (int32_t*)localMsg;
        while (msg_size--)
        {
            *to_ptr++ = *from_ptr++;
        }

        OSMemPut(handler->pMem, localMsg);

        return kStatus_OSA_Success;
    }
    else if ((OS_ERR_Q_EMPTY == err) ||
             (OS_ERR_TIMEOUT == err))
    {
        return kStatus_OSA_Timeout;
    }
    else
    {
        return kStatus_OSA_Error;
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
#if OS_CRITICAL_METHOD == 3u
    OS_CPU_SR  cpu_sr = 0u;
#endif
    INT8U err;
    OS_MEM* pMem;

    OSQDel(handler->pQueue, OS_DEL_ALWAYS, &err);

    if (OS_ERR_NONE != err)
    {
        return kStatus_OSA_Error;
    }

    /* return OS_MEM to OS */
    OS_ENTER_CRITICAL();
    pMem = handler->pMem;
    pMem->OSMemFreeList = OSMemFreeList;
    OSMemFreeList = pMem;
    OS_EXIT_CRITICAL();

    handler->pMem     = (OS_MEM   *)0;
    handler->pQueue   = (OS_EVENT *)0;

    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MemAlloc
 * Description   : This function is used to allocate amount of memory in bytes.
 * Return the pointer to the memory if success, otherwise return NULL;
 *
 *END**************************************************************************/
void * OSA_MemAlloc(size_t size)
{
    void *pMem;

    OSSchedLock();
    pMem = malloc(size);
    OSSchedUnlock();

    return pMem;
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
    void *pMem;

    OSSchedLock();
    pMem = calloc(1, size);
    OSSchedUnlock();

    return pMem;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MemFree
 * Description   : This function is used to free the memory previously allocated.
 *
 *END**************************************************************************/
osa_status_t OSA_MemFree(void *ptr)
{
    OSSchedLock();
    free(ptr);
    OSSchedUnlock();
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
    delay = MSEC_TO_TICK(delay);
    /*
     * If delay is too short that changed to 0 tick, reset it to 1 tick
     * in case of no delay.
     */
    if (!delay)
    {
        delay = 1U;
    }
    OSTimeDly(delay);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TimeGetMsec
 * Description   : This function gets current time in milliseconds.
 *
 *END**************************************************************************/
uint32_t OSA_TimeGetMsec(void)
{
    INT32U timeTick = OSTimeGet();
    return TICKS_TO_MSEC(timeTick);
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
void OSA_EnterCritical(osa_critical_section_mode_t mode)
{
    if (kCriticalDisableInt == mode)
    {
        OS_ENTER_CRITICAL();
    }
    else
    {
        OSSchedLock();
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
        OS_EXIT_CRITICAL();
    }
    else
    {
        OSSchedUnlock();
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
    OSInit();
    OS_CPU_SysTickInit(SystemCoreClock/(uint32_t)OS_TICKS_PER_SEC);
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
    OSStart();
    return kStatus_OSA_Success;
}

#endif
/*******************************************************************************
 * EOF
 ******************************************************************************/
