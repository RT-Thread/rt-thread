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
#if !defined(__FSL_OS_ABSTRACTION_H__)
#define __FSL_OS_ABSTRACTION_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#if defined __CC_ARM
#define inline      __inline
#endif

/*!
 * @addtogroup os_abstraction
 * @{
 */

/*! @brief Defines the return status of OSA's functions */
typedef enum _osa_status_t
{
    kStatus_OSA_Success = 0U, /*!< Success */
    kStatus_OSA_Error   = 1U, /*!< Failed */
    kStatus_OSA_Timeout = 2U, /*!< Timeout occurs while waiting */
    kStatus_OSA_Idle    = 3U  /*!< Used for bare metal only, the wait object is not ready
                                and timeout still not occur */
} osa_status_t;

/*! @brief The event flags are cleared automatically or manually.*/
typedef enum _osa_event_clear_mode_t
{
    kEventAutoClear    = 0U,  /*!< The flags of the event will be cleared automatically. */
    kEventManualClear  = 1U   /*!< The flags of the event will be cleared manually.      */
} osa_event_clear_mode_t;

/*! @brief Locks the task scheduler or disables interrupt in critical section. */
typedef enum _osa_critical_section_mode_t
{
    kCriticalLockSched     = 0U,  /*!< Lock scheduler in critical section.      */
    kCriticalDisableInt  = 1U   /*!< Disable interrupt in critical selection. */
} osa_critical_section_mode_t;

/*! @brief OSA interrupt handler. */
typedef void (*osa_int_handler_t)(void);

/* Include required header file based on RTOS selection */
#if defined (FSL_RTOS_MQX)
    #define USE_RTOS 1
    #include "fsl_os_abstraction_mqx.h"

#elif defined (FSL_RTOS_FREE_RTOS)
    #define USE_RTOS 1
    #include "fsl_os_abstraction_free_rtos.h"

#elif defined (FSL_RTOS_UCOSII)
    #define USE_RTOS 1
    #include "fsl_os_abstraction_ucosii.h"

#elif defined (FSL_RTOS_UCOSIII)
    #define USE_RTOS 1
    #include "fsl_os_abstraction_ucosiii.h"

#else
    #define USE_RTOS 0
    #include "fsl_os_abstraction_bm.h"
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Counting Semaphore
 * @{
 */

/*!
 * @brief Creates a semaphore with a given value.
 *
 * This function creates a semaphore and sets the value to the parameter
 * initValue.
 *
 * @param pSem      Pointer to the semaphore.
 * @param initValue Initial value the semaphore will be set to.
 *
 * @retval kStatus_OSA_Success The semaphore is created successfully.
 * @retval kStatus_OSA_Error   The semaphore cannot be created.
 *
 * Example:
   @code
   semaphore_t mySem;
   OSA_SemaCreate(&mySem, 0);
   @endcode
 *
 */
osa_status_t OSA_SemaCreate(semaphore_t *pSem, uint8_t initValue);

/*!
 * @brief Pending a semaphore with timeout.
 *
 * This function checks the semaphore's counting value. If it is positive,
 * decreases it and returns kStatus_OSA_Success. Otherwise, a timeout is used
 * to wait.
 *
 * @param pSem    Pointer to the semaphore.
 * @param timeout The maximum number of milliseconds to wait if semaphore is not
 *                positive. Pass OSA_WAIT_FOREVER to wait indefinitely, pass 0
 *                will return kStatus_OSA_Timeout immediately.
 *
 * @retval kStatus_OSA_Success The semaphore is received.
 * @retval kStatus_OSA_Timeout The semaphore is not received within the specified 'timeout'.
 * @retval kStatus_OSA_Error   An incorrect parameter was passed.
 * @retval kStatus_OSA_Idle    The semaphore is not available and 'timeout' is not exhausted,
 *                             This is only for bare metal.
 *
 * @note With bare metal, a semaphore cannot be waited on by more than one task
 * at the same time.
 *
 * Example:
 * @code
   osa_status_t status;
   status = OSA_SemaWait(&mySem, 100);
   switch(status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_SemaWait(semaphore_t *pSem, uint32_t timeout);

/*!
 * @brief Signals for someone waiting on the semaphore to wake up.
 *
 * Wakes up one task that is waiting on the semaphore. If no task is waiting, increases
 * the semaphore's counting value.
 *
 * @param pSem Pointer to the semaphore to signal.
 *
 * @retval kStatus_OSA_Success The semaphore is successfully signaled.
 * @retval kStatus_OSA_Error   The object cannot be signaled or invalid parameter.
 *
 * Example:
 * @code
   osa_status_t status;
   status = OSA_SemaPost(&mySem);
   switch(status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_SemaPost(semaphore_t *pSem);

/*!
 * @brief Destroys a previously created semaphore.
 *
 * @param pSem Pointer to the semaphore to destroy.
 *
 * @retval kStatus_OSA_Success The semaphore is successfully destroyed.
 * @retval kStatus_OSA_Error   The semaphore cannot be destroyed.
 *
 * Example:
 * @code
   osa_status_t status;
   status = OSA_SemaDestroy(&mySem);
   switch(status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_SemaDestroy(semaphore_t *pSem);

/* @} */

/*!
 * @name Mutex
 * @{
 */

/*!
 * @brief Create an unlocked mutex.
 *
 * This function creates a non-recursive mutex and sets it to unlocked status.
 *
 * @param pMutex Pointer to the Mutex.
 *
 * @retval kStatus_OSA_Success The mutex is created successfully.
 * @retval kStatus_OSA_Error   The mutex cannot be created.
 *
 * Example:
   @code
   mutex_t myMutex;
   osa_status_t status;
   status = OSA_MutexCreate(&myMutex);
   switch (status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_MutexCreate(mutex_t *pMutex);

/*!
 * @brief Waits for a mutex and locks it.
 *
 * This function checks the mutex's status. If it is unlocked, locks it and returns the
 * kStatus_OSA_Success. Otherwise, waits for a timeout in milliseconds to lock.
 *
 * @param pMutex Pointer to the Mutex.
 * @param timeout The maximum number of milliseconds to wait for the mutex.
 *                If the mutex is locked, Pass the value OSA_WAIT_FOREVER will
 *                wait indefinitely, pass 0 will return kStatus_OSA_Timeout
 *                immediately.
 *
 * @retval kStatus_OSA_Success The mutex is locked successfully.
 * @retval kStatus_OSA_Timeout Timeout occurred.
 * @retval kStatus_OSA_Error   Incorrect parameter was passed.
 * @retval kStatus_OSA_Idle    The mutex is not available and 'timeout' is not exhausted,
 *                             This is only for bare metal.
 *
 * @note This is non-recursive mutex, a task cannot try to lock the mutex it has locked.
 *
 * Example:
   @code
   osa_status_t status;
   status = OSA_MutexLock(&myMutex, 100);
   switch (status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_MutexLock(mutex_t *pMutex, uint32_t timeout);

/*!
 * @brief Unlocks a previously locked mutex.
 *
 * @param pMutex Pointer to the Mutex.
 *
 * @retval kStatus_OSA_Success The mutex is successfully unlocked.
 * @retval kStatus_OSA_Error   The mutex cannot be unlocked or invalid parameter.
 *
 * Example:
   @code
   osa_status_t status;
   status = OSA_MutexUnlock(&myMutex);
   switch (status)
   {
       //...
   }
   @endcode
 */
osa_status_t OSA_MutexUnlock(mutex_t *pMutex);

/*!
 * @brief Destroys a previously created mutex.
 *
 * @param pMutex Pointer to the Mutex.
 *
 * @retval kStatus_OSA_Success The mutex is successfully destroyed.
 * @retval kStatus_OSA_Error   The mutex cannot be destroyed.
 *
 * Example:
   @code
   osa_status_t status;
   status = OSA_MutexDestroy(&myMutex);
   switch (status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_MutexDestroy(mutex_t *pMutex);

/* @} */

/*!
 * @name Event signalling
 * @{
 */

/*!
 * @brief Initializes an event object with all flags cleared.
 *
 * This function creates an event object and set its clear mode. If clear mode
 * is kEventAutoClear, when a task gets the event flags, these flags will be
 * cleared automatically. If clear mode is kEventManualClear, these flags must
 * be cleared manually.
 *
 * @param pEvent    Pointer to the event object to initialize.
 * @param clearMode The event is auto-clear or manual-clear.
 *
 * @retval kStatus_OSA_Success The event object is successfully created.
 * @retval kStatus_OSA_Error   The event object is not created.
 *
 * Example:
   @code
   event_t myEvent;
   OSA_EventCreate(&myEvent, kEventAutoClear);
   @endcode
 *
 */
osa_status_t OSA_EventCreate(event_t *pEvent, osa_event_clear_mode_t clearMode);

/*!
 * @brief Waits for specified event flags to be set.
 *
 * This function waits for a combination of flags to be set in an event object.
 * Applications can wait for any/all bits to be set. Also this function could
 * obtain the flags who wakeup the waiting task.
 *
 * @param pEvent      Pointer to the event.
 * @param flagsToWait Flags that to wait.
 * @param waitAll     Wait all flags or any flag to be set.
 * @param timeout     The maximum number of milliseconds to wait for the event.
 *                    If the wait condition is not met, pass OSA_WAIT_FOREVER will
 *                    wait indefinitely, pass 0 will return kStatus_OSA_Timeout
 *                    immediately.
 * @param setFlags    Flags that wakeup the waiting task are obtained by this parameter.
 *
 * @retval kStatus_OSA_Success The wait condition met and function returns successfully.
 * @retval kStatus_OSA_Timeout Has not met wait condition within timeout.
 * @retval kStatus_OSA_Error   An incorrect parameter was passed.
 * @retval kStatus_OSA_Idle    The wait condition is not met and 'timeout' is not exhausted,
 *                             This is only for bare metal.
 *
 * @note 1. With bare metal, a event object cannot be waited on by more than one tasks
 *          at the same time.
 *       2. Please pay attention to the flags bit width, FreeRTOS uses the most
 *          significant 8 bis as control bits, so do not wait these bits while using
 *          FreeRTOS.
 *
 * Example:
   @code
   osa_status_t  status;
   event_flags_t setFlags;
   status = OSA_EventWait(&myEvent, 0x01, true, 100, &setFlags);
   switch (status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_EventWait(event_t       *pEvent,
                        event_flags_t  flagsToWait,
                        bool           waitAll,
                        uint32_t       timeout,
                        event_flags_t *setFlags);

/*!
 * @brief Sets one or more event flags.
 *
 * Sets specified flags of an event object.
 *
 * @param pEvent     Pointer to the event.
 * @param flagsToSet Flags to be set.
 *
 * @retval kStatus_OSA_Success The flags were successfully set.
 * @retval kStatus_OSA_Error   An incorrect parameter was passed.
 *
 * Example:
   @code
   osa_status_t  status;
   status = OSA_EventSet(&myEvent, 0x01);
   switch (status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_EventSet(event_t *pEvent, event_flags_t flagsToSet);

/*!
 * @brief Clears one or more flags.
 *
 * Clears specified flags of an event object.
 *
 * @param pEvent       Pointer to the event.
 * @param flagsToClear Flags to be clear.
 *
 * @retval kStatus_OSA_Success The flags were successfully cleared.
 * @retval kStatus_OSA_Error   An incorrect parameter was passed.
 *
 * Example:
   @code
   osa_status_t  status;
   status = OSA_EventClear(&myEvent, 0x01);
   switch (status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_EventClear(event_t *pEvent, event_flags_t flagsToClear);

/*!
 * @brief Gets event flags status.
 *
 * Gets the event flags status.
 *
 * @param pEvent Pointer to the event.
 *
 * @return event_flags_t Current event flags.
 *
 * Example:
   @code
   event_flags_t flags;
   flags = OSA_EventGetFlags(&myEvent);
   @endcode
 *
 */
event_flags_t OSA_EventGetFlags(event_t *pEvent);

/*!
 * @brief Destroys a previously created event object.
 *
 * @param pEvent Pointer to the event.
 *
 * @retval kStatus_OSA_Success The event is successfully destroyed.
 * @retval kStatus_OSA_Error   Event destruction failed.
 *
 * Example:
   @code
   osa_status_t  status;
   status = OSA_EventDestroy(&myEvent);
   switch (status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_EventDestroy(event_t *pEvent);
/* @} */

/*!
 * @name Task management
 * @{
 */

/*!
 * @brief Creates a task.
 *
 * This function is used to create task based on the resources defined
 * by the macro OSA_TASK_DEFINE.
 *
 * @param task      The task function entry.
 * @param name      The name of this task.
 * @param stackSize The stack size in byte.
 * @param stackMem  Pointer to the stack.
 * @param priority  Initial priority of the task.
 * @param param     Pointer to be passed to the task when it is created.
 * @param usesFloat This task will use float register or not.
 * @param handler   Pointer to the task handler.
 *
 * @retval kStatus_OSA_Success The task is successfully created.
 * @retval kStatus_OSA_Error   The task cannot be created..
 *
 * Example:
   @code
   osa_status_t status;
   OSA_TASK_DEFINE(task_func, stackSize);
   status = OSA_TaskCreate(task_func,
                        "task_name",
                        stackSize,
                        task_func_stack,
                        prio,
                        param,
                        false,
                        &task_func_task_handler);
   switch (status)
   {
       //...
   }
   @endcode
 *
 * @note Use the return value to check whether the task is
 *       created successfully. DO NOT check handler. For uC/OS-III,
 *       handler is not NULL even if the task creation has failed.
 */
osa_status_t OSA_TaskCreate(task_t          task,
                         uint8_t        *name,
                         uint16_t        stackSize,
                         task_stack_t   *stackMem,
                         uint16_t        priority,
                         task_param_t    param,
                         bool            usesFloat,
                         task_handler_t *handler);

/*!
 * @brief Destroys a previously created task.
 *
 * @param handler The handler of the task to destroy. Returned by the OSA_TaskCreate function.
 *
 * @retval kStatus_OSA_Success The task was successfully destroyed.
 * @retval kStatus_OSA_Error   Task destruction failed or invalid parameter.
 *
 * Example:
   @code
   osa_status_t status;
   status = OSA_TaskDestroy(myTaskHandler);
   switch (status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_TaskDestroy(task_handler_t handler);

/*!
 * @brief Puts the active task to the end of scheduler's queue.
 *
 * When a task calls this function, it gives up the CPU and puts itself to the
 * end of a task ready list.
 *
 * @retval kStatus_OSA_Success The function is called successfully.
 * @retval kStatus_OSA_Error   Error occurs with this function.
 *
 * Example:
   @code
   osa_status_t status;
   status = OSA_TaskYield();
   switch (status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_TaskYield(void);

/*!
 * @brief Gets the handler of active task.
 *
 * @return Handler to current active task.
 *
 * Example:
   @code
   task_handler_t handler = OSA_TaskYield();
   @endcode
 *
 */
task_handler_t OSA_TaskGetHandler(void);

/*!
 * @brief Gets the priority of a task.
 *
 * @param handler The handler of the task whose priority is received.
 *
 * @return Task's priority.
 *
 * Example:
   @code
   uint16_t taskPrio = OSA_TaskGetPriority(taskHandler);
   @endcode
 *
 */
uint16_t OSA_TaskGetPriority(task_handler_t handler);

/*!
 * @brief Sets the priority of a task.
 *
 * @param handler  The handler of the task whose priority is received.
 * @param priority The priority to set.
 *
 * @retval kStatus_OSA_Success Task's priority is set successfully.
 * @retval kStatus_OSA_Error   Task's priority cannot be set.
 *
 * Example:
   @code
   osa_status_t status;
   status = OSA_TaskSetPriority(taskHandler, newPrio);
   switch (status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_TaskSetPriority(task_handler_t handler, uint16_t priority);

/* @} */

/*!
 * @name Message queues
 * @{
 */

/*!
 * @brief Initializes a message queue.
 *
 * This function  initializes the message queue that was declared previously.
 * This is an example demonstrating the use of the function:
   @code
   msg_queue_handler_t handler;
   MSG_QUEUE_DECLARE(my_message, msg_num, msg_size);
   handler = OSA_MsgQCreate(my_message, msg_num, msg_size);
   @endcode
 *
 * @param queue The queue declared through the MSG_QUEUE_DECLARE macro.
 * @param message_number The number of elements in the queue.
 * @param message_size Size of every elements in words.
 *
 * @return Handler to access the queue for put and get operations. If message queue
 *         created failed, return 0.
 */
msg_queue_handler_t OSA_MsgQCreate(msg_queue_t *queue,
                                        uint16_t  message_number,
                                        uint16_t  message_size);

/*!
 * @brief Puts a message at the end of the queue.
 *
 * This function puts a message to the end of the message queue. If the queue
 * is full, this function returns the kStatus_OSA_Error;
 *
 * @param handler  Queue handler returned by the OSA_MsgQCreate function.
 * @param pMessage Pointer to the message to be put into the queue.
 *
 * @retval kStatus_OSA_Success Message successfully put into the queue.
 * @retval kStatus_OSA_Error   The queue was full or an invalid parameter was passed.
 *
 * Example:
   @code
   osa_status_t status;
   struct MESSAGE messageToPut = ...;
   status = OSA_MsgQPut(queueHandler, &messageToPut);
   switch (status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_MsgQPut(msg_queue_handler_t handler, void* pMessage);

/*!
 * @brief Reads and remove a message at the head of the queue.
 *
 * This function gets a message from the head of the message queue. If the
 * queue is empty, timeout is used to wait.
 *
 * @param handler  Queue handler returned by the OSA_MsgQCreate function.
 * @param pMessage Pointer to a memory to save the message.
 * @param timeout  The number of milliseconds to wait for a message. If the
 *                 queue is empty, pass OSA_WAIT_FOREVER will wait indefinitely,
 *                 pass 0 will return kStatus_OSA_Timeout immediately.
 *
 * @retval kStatus_OSA_Success Message successfully obtained from the queue.
 * @retval kStatus_OSA_Timeout The queue remains empty after timeout.
 * @retval kStatus_OSA_Error   Invalid parameter.
 * @retval kStatus_OSA_Idle    The queue is empty and 'timeout' is not exhausted,
 *                             This is only for bare metal.
 *
 * @note With bere metal, there should be only one process waiting on the queue.
 *
 * Example:
   @code
   osa_status_t status;
   struct MESSAGE messageToGet;
   status = OSA_MsgQGet(queueHandler, &messageToGet, 100);
   switch (status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_MsgQGet(msg_queue_handler_t handler,
                           void               *pMessage,
                           uint32_t            timeout);

/*!
 * @brief Destroys a previously created queue.
 *
 * @param handler Queue handler returned by the OSA_MsgQCreate function.
 *
 * @retval kStatus_OSA_Success The queue was successfully destroyed.
 * @retval kStatus_OSA_Error   Message queue destruction failed.
 *
 * Example:
   @code
   osa_status_t status;
   status = OSA_MsgQDestroy(queueHandler);
   switch (status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_MsgQDestroy(msg_queue_handler_t handler);

/* @} */

/*!
 * @name Memory Management
 * @{
 */

/*!
 * @brief Reserves the requested amount of memory in bytes.
 *
 * @param size Amount of bytes to reserve.
 *
 * @return Pointer to the reserved memory. NULL if memory could not be allocated.
 */
void * OSA_MemAlloc(size_t size);

/*!
 * @brief Reserves the requested amount of memory in bytes and initializes it to 0.
 *
 * @param size Amount of bytes to reserve.
 *
 * @return Pointer to the reserved memory. NULL if memory could not be allocated.
 */
void * OSA_MemAllocZero(size_t size);

/*!
 * @brief Releases the memory previously reserved.
 *
 * @param ptr Pointer to the start of the memory block previously reserved.
 *
 * @retval kStatus_OSA_Success Memory correctly freed.
 * @retval kStatus_OSA_Error Error occurs during free the memory.
 */
osa_status_t OSA_MemFree(void *ptr);

/* @} */

/*!
 * @name Time management
 * @{
 */

/*!
 * @brief Delays execution for a number of milliseconds.
 *
 * @param delay The time in milliseconds to wait.
 */
void OSA_TimeDelay(uint32_t delay);

/*!
 * @brief Gets the current time since system boot in milliseconds.
 *
 * @return Current time in milliseconds.
 */
uint32_t OSA_TimeGetMsec(void);

/* @} */

/*!
 * @name Interrupt management
 * @{
 */

/*!
 * @brief Installs the interrupt handler.
 *
 * @param IRQNumber IRQ number of the interrupt.
 * @param handler The interrupt handler to install.
 *
 * @return This function returns the old interrupt handler installed in vector
 *         table. If could not install ISR, this function returns NULL; The
 *         return value could be compared with OSA_DEFAULT_INT_HANDLER to
 *         detect whether this is the first interrupt handler installed.
 */
osa_int_handler_t OSA_InstallIntHandler(int32_t IRQNumber,
                                        osa_int_handler_t handler);

/* @} */

/*!
 * @name Critical section
 * @{
 */

/*!
 * @brief Enters the critical section to ensure some code is not preempted.
 *
 * @param mode Lock task scheduler of disable interrupt in critical section.
 *             Pass kCriticalLockSched to lock task scheduler,
 *             pass kCriticalDisableInt to disable interrupt.
 */
void OSA_EnterCritical(osa_critical_section_mode_t mode);

/*!
 * @brief Exits the critical section.
 *
 * @param mode Lock task scheduler of disable interrupt in critical section.
 *             Pass kCriticalLockSched to lock task scheduler,
 *             pass kCriticalDisableInt to disable interrupt.
 */
void OSA_ExitCritical(osa_critical_section_mode_t mode);

/* @} */

/*!
 * @name OSA initialize
 * @{
 */

/*!
 * @brief Initializes the RTOS services.
 *
 * This function sets up the basic RTOS services. It should be called
 * first in the main function.
 *
 * @retval kStatus_OSA_Success RTOS services are initialized successfully.
 * @retval kStatus_OSA_Error   Error occurs during initialization.
 */
osa_status_t OSA_Init(void);

/*!
 * @brief Starts the RTOS.
 *
 * This function starts the RTOS scheduler and may never return.
 *
 * @retval kStatus_OSA_Success RTOS starts to run successfully.
 * @retval kStatus_OSA_Error   Error occurs when start RTOS.
 */
osa_status_t OSA_Start(void);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_OS_ABSTRACTION_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

