/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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

#include <assert.h>
#include "fsl_os_abstraction.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"

#if (FSL_OSA_BM_TIMER_CONFIG == FSL_OSA_BM_TIMER_LPTMER)
#include "fsl_lptmr_hal.h"

/* Only one lptmr and always use it. */
#define BM_LPTMR_INSTANCE 0
#define BM_LPTMR_BASE LPTMR0
#endif

/* Weak function. */
#if defined(__GNUC__)
#define __WEAK_FUNC __attribute__((weak))
#elif defined(__ICCARM__)
#define __WEAK_FUNC __weak
#elif defined( __CC_ARM )
#define __WEAK_FUNC __weak
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TimeInit
 * Description   : This function initializes the timer used in BM OSA, the
 * functions such as OSA_TimeDelay, OSA_TimeGetMsec, and the timeout are all
 * based on this timer.
 *
 *END**************************************************************************/
__WEAK_FUNC void OSA_TimeInit(void)
{
#if (FSL_OSA_BM_TIMER_CONFIG == FSL_OSA_BM_TIMER_LPTMER)
    lptmr_prescaler_user_config_t prescaler_config;
    lptmr_working_mode_user_config_t lptmr_config;

    /*
     * Setup LP Timer for timeout and delay.
     * Use 1kHz LPO as clock source, disable prescaler, freerun mode.
     */
    CLOCK_SYS_EnableLptmrClock(BM_LPTMR_INSTANCE);

    LPTMR_HAL_Disable(BM_LPTMR_BASE);

    prescaler_config.prescalerBypass = true;
    prescaler_config.prescalerClockSelect = (lptmr_prescaler_clock_select_t)kClockLptmrSrcLpoClk;
    LPTMR_HAL_SetPrescalerMode(BM_LPTMR_BASE, prescaler_config);

    lptmr_config.freeRunningEnable = true;
    lptmr_config.timerModeSelect = kLptmrTimerModeTimeCounter;
    LPTMR_HAL_SetTimerWorkingMode(BM_LPTMR_BASE, lptmr_config);

    LPTMR_HAL_SetIntCmd(BM_LPTMR_BASE,false);

    LPTMR_HAL_Enable(BM_LPTMR_BASE);
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TimeDiff
 * Description   : This function gets the difference between two time stamp,
 * time overflow is considered.
 *
 *END**************************************************************************/
__WEAK_FUNC uint32_t OSA_TimeDiff(uint32_t time_start, uint32_t time_end)
{
    if (time_end >= time_start)
    {
        return time_end - time_start;
    }
    else
    {
        /* lptmr count is 16 bits. */
        return FSL_OSA_TIME_RANGE - time_start + time_end + 1;
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
    assert(pSem);

    pSem->semCount  = initValue;
    pSem->isWaiting = false;
    pSem->time_start = 0u;
    pSem->timeout = 0u;

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
 * 'timeout', returns kStatus_OSA_Error if any errors occur during waiting,
 * returns kStatus_OSA_Idle if the semaphore is not available and 'timeout' is
 * not exhausted, because wait functions should not block with bare metal.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaWait(semaphore_t *pSem, uint32_t timeout)
{
#if (FSL_OSA_BM_TIMER_CONFIG != FSL_OSA_BM_TIMER_NONE)
    uint32_t currentTime;
#endif

    assert(pSem);

    /* Check the sem count first. Deal with timeout only if not already set */
    if (pSem->semCount)
    {
        INT_SYS_DisableIRQGlobal();
        pSem->semCount --;
        pSem->isWaiting = false;
        INT_SYS_EnableIRQGlobal();
        return kStatus_OSA_Success;
    }
    else
    {
        if (0 == timeout)
        {
            /* If timeout is 0 and semaphore is not available, return kStatus_OSA_Timeout. */
            return kStatus_OSA_Timeout;
        }
#if (FSL_OSA_BM_TIMER_CONFIG != FSL_OSA_BM_TIMER_NONE)
        else if (pSem->isWaiting)
        {
            /* Check for timeout */
            currentTime = OSA_TimeGetMsec();
            if (pSem->timeout < OSA_TimeDiff(pSem->time_start, currentTime))
            {
                INT_SYS_DisableIRQGlobal();
                pSem->isWaiting = false;
                INT_SYS_EnableIRQGlobal();
                return kStatus_OSA_Timeout;
            }
        }
        else if (timeout != OSA_WAIT_FOREVER)    /* If don't wait forever, start the timer */
        {
            /* Start the timeout counter */
            INT_SYS_DisableIRQGlobal();
            pSem->isWaiting = true;
            INT_SYS_EnableIRQGlobal();
            pSem->time_start = OSA_TimeGetMsec();
            pSem->timeout = timeout;
        }
#endif
    }

    return kStatus_OSA_Idle;
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
    /* The max value is 0xFF */
    if (0xFF == pSem->semCount)
    {
        return kStatus_OSA_Error;
    }
    INT_SYS_DisableIRQGlobal();
    ++pSem->semCount;
    INT_SYS_EnableIRQGlobal();

    return kStatus_OSA_Success;
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

    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MutexCreate
 * Description   : This function is used to create a mutex.
 * Return kStatus_OSA_Success if create successfully, otherwise return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_MutexCreate(mutex_t *pMutex)
{
    assert(pMutex);

    pMutex->isLocked  = false;
    pMutex->isWaiting = false;
    pMutex->time_start = 0u;
    pMutex->timeout = 0u;

    return kStatus_OSA_Success;
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
 * 'timeout', returns kStatus_OSA_Error if any errors occur during waiting,
 * returns kStatus_OSA_Idle if the mutex is not available and 'timeout' is
 * not exhausted, because wait functions should not block with bare metal.
 *
 *END**************************************************************************/
osa_status_t OSA_MutexLock(mutex_t *pMutex, uint32_t timeout)
{
#if (FSL_OSA_BM_TIMER_CONFIG != FSL_OSA_BM_TIMER_NONE)
    uint32_t currentTime;
#endif

    assert(pMutex);

    /* Always check first. Deal with timeout only if not available. */
    if (pMutex->isLocked == false)
    {
        /* Get the lock and return success */
        INT_SYS_DisableIRQGlobal();
        pMutex->isLocked = true;
        pMutex->isWaiting = false;
        INT_SYS_EnableIRQGlobal();
        return kStatus_OSA_Success;
    }
    else
    {
        if (0 == timeout)
        {
            /* If timeout is 0 and mutex is not available, return kStatus_OSA_Timeout. */
            return kStatus_OSA_Timeout;
        }
#if (FSL_OSA_BM_TIMER_CONFIG != FSL_OSA_BM_TIMER_NONE)
        else if (pMutex->isWaiting)
        {
            /* Check for timeout */
            currentTime = OSA_TimeGetMsec();
            if (pMutex->timeout < OSA_TimeDiff(pMutex->time_start, currentTime))
            {
                INT_SYS_DisableIRQGlobal();
                pMutex->isWaiting = false;
                INT_SYS_EnableIRQGlobal();
                return kStatus_OSA_Timeout;
            }
        }
        else if (timeout != OSA_WAIT_FOREVER)    /* If dont't wait forever, start timer. */
        {
            /* Start the timeout counter */
            INT_SYS_DisableIRQGlobal();
            pMutex->isWaiting = true;
            INT_SYS_EnableIRQGlobal();
            pMutex->time_start = OSA_TimeGetMsec();
            pMutex->timeout = timeout;
        }
#endif
    }

    return kStatus_OSA_Idle;
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

    INT_SYS_DisableIRQGlobal();
    pMutex->isLocked = false;
    INT_SYS_EnableIRQGlobal();

    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MutexDestroy
 * Description   : This function is used to destroy a mutex.
 * Return kStatus_OSA_Success if the lock object is destroyed successfully, otherwise
 * return kStatus_OSA_Error.
 *
 *END**************************************************************************/
osa_status_t OSA_MutexDestroy(mutex_t *pMutex)
{
    assert(pMutex);

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

    pEvent->isWaiting = false;
    pEvent->flags     = 0;
    pEvent->clearMode = clearMode;
    pEvent->time_start = 0u;
    pEvent->timeout = 0u;

    return kStatus_OSA_Success;
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
 * 'timeout', returns kStatus_OSA_Error if any errors occur during waiting,
 * returns kStatus_OSA_Idle if wait condition is not met  and 'timeout' is
 * not exhausted, because wait functions should not block with bare metal.
 *
 *END**************************************************************************/
osa_status_t OSA_EventWait(event_t       *pEvent,
                        event_flags_t  flagsToWait,
                        bool           waitAll,
                        uint32_t       timeout,
                        event_flags_t *setFlags)
{
#if (FSL_OSA_BM_TIMER_CONFIG != FSL_OSA_BM_TIMER_NONE)
    uint32_t currentTime;
#endif

    assert(pEvent);
    assert(setFlags);

    osa_status_t retVal = kStatus_OSA_Idle;

    *setFlags = pEvent->flags & flagsToWait;

    /* Check the event flag first, if does not meet wait condition, deal with timeout. */
    if ((((!waitAll) && (*setFlags))) || (*setFlags == flagsToWait))
    {
        INT_SYS_DisableIRQGlobal();
        pEvent->isWaiting = false;
        if(kEventAutoClear == pEvent->clearMode)
        {
            pEvent->flags &= ~flagsToWait;
        }
        INT_SYS_EnableIRQGlobal();
        return kStatus_OSA_Success;
    }
    else
    {
        if (0 == timeout)
        {
            /* If timeout is 0 and wait condition is not met, return kStatus_OSA_Timeout. */
            return kStatus_OSA_Timeout;
        }
#if (FSL_OSA_BM_TIMER_CONFIG != FSL_OSA_BM_TIMER_NONE)
        else if (pEvent->isWaiting)
        {
            /* Check for timeout */
            currentTime = OSA_TimeGetMsec();
            if (pEvent->timeout < OSA_TimeDiff(pEvent->time_start, currentTime))
            {
                INT_SYS_DisableIRQGlobal();
                pEvent->isWaiting = false;
                INT_SYS_EnableIRQGlobal();
                retVal = kStatus_OSA_Timeout;
            }
        }
        else if(timeout != OSA_WAIT_FOREVER)    /* If no timeout, don't start the timer */
        {
            /* Start the timeout counter */
            INT_SYS_DisableIRQGlobal();
            pEvent->isWaiting = true;
            INT_SYS_EnableIRQGlobal();
            pEvent->time_start = OSA_TimeGetMsec();
            pEvent->timeout = timeout;
        }
#endif
    }

    return retVal;
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

    return pEvent->flags;
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
    /* Set flags ensuring atomic operation */
    INT_SYS_DisableIRQGlobal();
    pEvent->flags |= flagsToSet;
    INT_SYS_EnableIRQGlobal();

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
    /* Clear flags ensuring atomic operation */
    INT_SYS_DisableIRQGlobal();
    pEvent->flags &= ~flagsToClear;
    INT_SYS_EnableIRQGlobal();

    return kStatus_OSA_Success;
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

    return kStatus_OSA_Success;
}

/* The task APIs are only available if TASK_MAX_NUM>0. */
#if (TASK_MAX_NUM > 0)

/* Global variales for task. */
static task_handler_t g_curTask; /* Current task. */

/*
 * All task control blocks in g_taskControlBlockPool will be linked as a
 * list, and the list is managed by the pointer g_freeTaskControlBlock.
 */
static task_control_block_t g_taskControlBlockPool[TASK_MAX_NUM];

/*
 * Pointer to the free task control blocks. To create a task, we should get
 * task control block from this pointer. When task is destroyed, the control
 * block will be returned and managed by this pointer.
 */
static task_control_block_t *g_freeTaskControlBlock;

/* Head node of task list, all tasks will be linked to this head node. */
static task_control_block_t g_taskListHead;

/*FUNCTION**********************************************************************
 *
 * Function Name : task_init
 * Description   : This function is used to initialize bare metal's task system,
 * it will prepare task control block pool and initialize corresponding
 * structures. This function should be called before creating any tasks.
 *
 *END**************************************************************************/
void task_init(void)
{
    int32_t i = TASK_MAX_NUM-1;

    g_taskControlBlockPool[i].next = NULL;

    while (i--)
    {
        /* Link all task control blocks to a list. */
        g_taskControlBlockPool[i].next = &g_taskControlBlockPool[i+1];
    }

    g_freeTaskControlBlock = g_taskControlBlockPool;

    /* Initialize task list. */
    g_taskListHead.next = &g_taskListHead;
    g_taskListHead.prev = &g_taskListHead;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskCreate
 * Description   : This function will register the task function and parameter
 * to task list, so that the task functions can be called in turn. Return
 * kStatus_OSA_Success if register successfully, otherwise return kStatus_OSA_Error;
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
    task_control_block_t *p_newTaskControlBlock;
    task_control_block_t *p_taskListTail;

    if (!g_freeTaskControlBlock)
    {
        /* No more task control blocks can be got. */
        return kStatus_OSA_Error;
    }
    else
    {
        /* Get new task control block from pool. */
        p_newTaskControlBlock         = g_freeTaskControlBlock;
        g_freeTaskControlBlock        = g_freeTaskControlBlock->next;
        /* Set task entry and parameter.*/
        p_newTaskControlBlock->p_func = task;
        p_newTaskControlBlock->param  = param;
        /* Add p_newTaskControlBlock to the tail of task list. */
        p_taskListTail                = g_taskListHead.prev;
        p_taskListTail->next          = p_newTaskControlBlock;
        p_newTaskControlBlock->next   = &g_taskListHead;
        g_taskListHead.prev           = p_newTaskControlBlock;
        p_newTaskControlBlock->prev   = p_taskListTail;
        /* Task handler is pointer of task control block. */
        *handler = p_newTaskControlBlock;

        return kStatus_OSA_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskDestroy
 * Description   : This function will remove task control block from task list,
 * so that the task functions will not called by anymore.
 * Return kStatus_OSA_Success if successfully, otherwise return kStatus_OSA_Error;
 *
 *END**************************************************************************/
osa_status_t OSA_TaskDestroy(task_handler_t handler)
{
    assert(handler);
    /* Remove task control block from task list. */
    handler->prev->next = handler->next;
    handler->next->prev = handler->prev;

    /*
     * If current task is destroyed, then g_curTask will point to the previous
     * task, so that the subsequent tasks could be called. Check the function
     * OSA_Start for more details.
     */
    if (handler == g_curTask)
    {
        g_curTask = handler->prev;
    }

    /* Put task control block back to pool. */
    handler->prev = NULL;
    handler->next = g_freeTaskControlBlock;
    g_freeTaskControlBlock = handler;

    return kStatus_OSA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskYield
 * Description   : This function is not implement with bare metal.
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
    return g_curTask;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskGetPriority
 * Description   : This function is not implement with bare metal.
 *
 *END**************************************************************************/
uint16_t OSA_TaskGetPriority(task_handler_t handler)
{
    return 0;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskSetPriority
 * Description   : This function is not implement with bare metal.
 *
 *END**************************************************************************/
osa_status_t OSA_TaskSetPriority(task_handler_t handler, uint16_t priority)
{
    return kStatus_OSA_Success;
}
#endif

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
    assert(queue);

    queue->number  = message_number;
    queue->size    = message_size;
    queue->head    = 0;
    queue->tail    = 0;
    queue->isEmpty = true;

    if(kStatus_OSA_Success == OSA_SemaCreate(&queue->queueSem, 0))
    {
        return queue;
    }
    else
    {
        return NULL;
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
    assert(handler);
    uint32_t *from_ptr, *to_ptr;
    uint16_t msgSize;

    /* Check that there is room in the queue */
    INT_SYS_DisableIRQGlobal();
    if((handler->tail != handler->head) || (handler->isEmpty))
    {
        from_ptr = (uint32_t*)pMessage;
        to_ptr   = &handler->queueMem[handler->tail * handler->size];

        /* Copy entire message into the queue, based on the size configured at creation */
        msgSize = handler->size;
        while(msgSize--)
        {
            *to_ptr++ = *from_ptr++;
        }

        /* Adjust tail pointer and wrap in case the end of the buffer is reached */
        ++handler->tail;
        if(handler->tail == handler->number)
        {
            handler->tail = 0;
        }

        /* If queue was empty, clear the empty flag and signal that it is not empty anymore */
        if(handler->isEmpty)
        {
            handler->isEmpty = false;
            OSA_SemaPost(&handler->queueSem);
        }
        INT_SYS_EnableIRQGlobal();

        return kStatus_OSA_Success;
    }
    else
    {
        INT_SYS_EnableIRQGlobal();
        return kStatus_OSA_Error;
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
 * 'timeout', returns kStatus_OSA_Error if any errors occur during waiting,
 * returns kStatus_OSA_Idle if message queue is empty and 'timeout' is
 * not exhausted, because wait functions should not block with bare metal.
 *
 *END**************************************************************************/
osa_status_t OSA_MsgQGet(msg_queue_handler_t handler,
                           void               *pMessage,
                           uint32_t            timeout)
{
    assert(handler);
    osa_status_t retVal = kStatus_OSA_Error;
    uint32_t *from_ptr, *to_ptr;
    uint16_t msgSize;

    INT_SYS_DisableIRQGlobal();
    /* Check if the queue is not empty */
    if(!handler->isEmpty)
    {
        from_ptr = &handler->queueMem[handler->head * handler->size];
        to_ptr   = (uint32_t*)(pMessage);

        /* Copy entire message into the queue, based on the size configured at creation */
        msgSize = handler->size;
        while(msgSize--)
        {
            *to_ptr++ = *from_ptr++;
        }

        /* Adjust head pointer and wrap in case the end of the buffer is reached */
        ++handler->head;
        if(handler->head == handler->number)
        {
            handler->head = 0;
        }

        /* If queue is empty, clear the semaphore. */
        if(handler->head == handler->tail)
        {
            handler->isEmpty = true;
            /* Set semapohre to 0 because the queue is empty. */
            (void)OSA_SemaWait(&handler->queueSem, 0);
        }
        INT_SYS_EnableIRQGlobal();

        retVal = kStatus_OSA_Success;
    }
    else
    {
        INT_SYS_EnableIRQGlobal();
        /* Wait for the semaphore if the queue was empty */
        retVal = OSA_SemaWait(&handler->queueSem, timeout);
    }

    return retVal;
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
    assert(handler);
    return OSA_SemaDestroy(&handler->queueSem);
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
    return malloc(size);
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
    return calloc(1, size);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MemFree
 * Description   : This function is used to free the memory previously allocated.
 *
 *END**************************************************************************/
osa_status_t OSA_MemFree(void *ptr)
{
    free(ptr);
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
    uint32_t currTime, timeStart;

    timeStart = OSA_TimeGetMsec();

    do {
        currTime = OSA_TimeGetMsec(); /* Get current time stamp */
    } while (delay >= OSA_TimeDiff(timeStart, currTime));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TimeGetMsec
 * Description   : This function gets current time in milliseconds.
 *
 *END**************************************************************************/
__WEAK_FUNC uint32_t OSA_TimeGetMsec(void)
{
#if (FSL_OSA_BM_TIMER_CONFIG == FSL_OSA_BM_TIMER_NONE)
    return 0U;
#elif (FSL_OSA_BM_TIMER_CONFIG == FSL_OSA_BM_TIMER_LPTMER)
    return LPTMR_HAL_GetCounterValue(BM_LPTMR_BASE);
#else
    return 0U;
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : interrupt_handler_register
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
        INT_SYS_DisableIRQGlobal();
    }
    else
    {
        return;
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
        INT_SYS_EnableIRQGlobal();
    }
    else
    {
        return;
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
#if (TASK_MAX_NUM > 0)
    task_init();
#endif

#if (FSL_OSA_BM_TIMER_CONFIG != FSL_OSA_BM_TIMER_NONE)
    OSA_TimeInit();
#endif

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
#if (TASK_MAX_NUM > 0)
    g_curTask = &g_taskListHead;

    for(;;)
    {
        if (g_curTask->p_func)
        {
            g_curTask->p_func(g_curTask->param);
        }
        g_curTask = g_curTask->next;
    }
#else
    for(;;)
    {
    }
#endif
}

#if (TASK_MAX_NUM > 0)
/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_PollAllOtherTasks
 * Description   : This function calls all task functions except current task
 * one time. It is only for bare metal.
 *
 *END**************************************************************************/
void OSA_PollAllOtherTasks(void)
{
    task_handler_t curTaskSave = g_curTask;
    g_curTask = g_taskListHead.next;

    while ((g_curTask->p_func) && (g_curTask!=curTaskSave))
    {
        g_curTask->p_func(g_curTask->param);
        g_curTask = g_curTask->next;
    }
    g_curTask = curTaskSave;
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
