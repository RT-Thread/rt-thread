/**
 * \addtogroup MID_RTO_OSAL
 *
 * \brief OS Abstraction Layer
 *
 * \{
 */

/**
 ****************************************************************************************
 *
 * @file osal.h
 *
 * @brief OS abstraction layer API
 *
 * Copyright (c) 2023-2024 Renesas Electronics. All rights reserved.
 *
 * This software ("Software") is owned by Renesas Electronics.
 *
 * By using this Software you agree that Renesas Electronics retains all
 * intellectual property and proprietary rights in and to this Software and any
 * use, reproduction, disclosure or distribution of the Software without express
 * written permission or a license agreement from Renesas Electronics is
 * strictly prohibited. This Software is solely for use on or in conjunction
 * with Renesas Electronics products.
 *
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, THE
 * SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. EXCEPT AS OTHERWISE
 * PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, IN NO EVENT SHALL
 * RENESAS ELECTRONICS BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THE SOFTWARE.
 *
 ****************************************************************************************
 */

#ifndef OSAL_H_
#define OSAL_H_

#include "FreeRTOS.h"

#if defined(OS_FREERTOS)

 #include <event_groups.h>
 #include <semphr.h>
 #include <task.h>
 #include <timers.h>
 #ifdef RM_STDIO_W
  #include "rm_stdio_w_cfg.h"
 #endif

/**
 * \brief Check whether running in interrupt context.
 *
 * \return true if the CPU is serving an interrupt.
 */
__STATIC_INLINE bool in_interrupt (void)
{
    return (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0;
}

 #define OS_STACK_WORD_SIZE             (sizeof(StackType_t))

 #define OS_TASK                        TaskHandle_t
 #define OS_TASK_STATUS                 TaskStatus_t
 #define OS_TASK_CREATE_SUCCESS         pdPASS
 #define OS_TASK_NOTIFY_SUCCESS         pdPASS
 #define OS_TASK_NOTIFY_FAIL            pdFALSE
 #define OS_TASK_NOTIFY_NO_WAIT         0
 #define OS_TASK_NOTIFY_FOREVER         portMAX_DELAY
 #define OS_TASK_NOTIFY_ALL_BITS        0xFFFFFFFF

 #ifndef OS_TASK_PRIORITY_LOWEST
  #define OS_TASK_PRIORITY_LOWEST       tskIDLE_PRIORITY
 #endif                                                               // OS_TASK_PRIORITY_LOWEST
 #define OS_TASK_PRIORITY_NORMAL        tskIDLE_PRIORITY + 1
 #define OS_TASK_PRIORITY_NORMAL_MAX    (OS_TASK_PRIORITY_NORMAL + 9) // 10
 #ifndef OS_TASK_PRIORITY_HIGHEST
  #define OS_TASK_PRIORITY_HIGHEST      configMAX_PRIORITIES - 1
 #endif                                                               // OS_TASK_PRIORITY_HIGHEST

 #define OS_MUTEX                       SemaphoreHandle_t
 #define OS_MUTEX_TAKEN                 pdTRUE
 #define OS_MUTEX_NOT_TAKEN             pdFALSE
 #define OS_MUTEX_CREATE_SUCCESS        1
 #define OS_MUTEX_CREATE_FAILED         0
 #define OS_MUTEX_NO_WAIT               0
 #define OS_MUTEX_FOREVER               portMAX_DELAY

 #define OS_EVENT                       SemaphoreHandle_t
 #define OS_EVENT_CREATE_SUCCESS        1
 #define OS_EVENT_CREATE_FAILED         0
 #define OS_EVENT_SIGNALED              pdTRUE
 #define OS_EVENT_NOT_SIGNALED          pdFALSE
 #define OS_EVENT_NO_WAIT               0
 #define OS_EVENT_FOREVER               portMAX_DELAY

 #define OS_EVENT_GROUP                 EventGroupHandle_t
 #define OS_EVENT_GROUP_OK              pdTRUE
 #define OS_EVENT_GROUP_FAIL            pdFALSE
 #define OS_EVENT_GROUP_FOREVER         portMAX_DELAY

 #define OS_QUEUE                       QueueHandle_t
 #define OS_QUEUE_FULL                  errQUEUE_FULL
 #define OS_QUEUE_EMPTY                 pdFALSE
 #define OS_QUEUE_OK                    pdTRUE
 #define OS_QUEUE_NO_WAIT               0
 #define OS_QUEUE_FOREVER               portMAX_DELAY

 #define OS_TIMER                       TimerHandle_t
 #define OS_TIMER_SUCCESS               pdPASS
 #define OS_TIMER_FAIL                  pdFAIL
 #define OS_TIMER_FOREVER               portMAX_DELAY

 #define OS_BASE_TYPE                   BaseType_t
 #define OS_UBASE_TYPE                  UBaseType_t

 #define OS_OK                          pdPASS
 #define OS_FAIL                        pdFAIL

 #define OS_TICK_TIME                   TickType_t
 #define OS_PERIOD_MS                   portTICK_PERIOD_MS

 #define OS_ASSERT                      configASSERT

/**
 * \brief OS Notification action
 */
typedef enum
{
    OS_NOTIFY_NO_ACTION             = eNoAction,                 /**< subject task receives event, but its notification value is not updated */
    OS_NOTIFY_SET_BITS              = eSetBits,                  /**< notification value of subject task will be bitwise ORed with task value */
    OS_NOTIFY_INCREMENT             = eIncrement,                /**< notification value of subject task will be incremented by one */
    OS_NOTIFY_VAL_WITH_OVERWRITE    = eSetValueWithOverwrite,    /**< notification value of subject task is unconditionally set to task value */
    OS_NOTIFY_VAL_WITHOUT_OVERWRITE = eSetValueWithoutOverwrite, /**< if subject task has a notification pending then notification value
                                                                  *   will be set to task value otherwise task value is not updated */
} OS_NOTIFY_ACTION;

/**
 * \brief OS Task state
 */
typedef enum
{
    OS_TASK_RUNNING   = eRunning,      /**< Task is in running state, a task is querying the state of itself */
    OS_TASK_READY     = eReady,        /**< Task is in a ready state */
    OS_TASK_BLOCKED   = eBlocked,      /**< Task is in blocked state */
    OS_TASK_SUSPENDED = eSuspended,    /**< Task is in the suspended state, or is in the blocked state with an infinite time out */
    OS_TASK_DELETED   = eDeleted,      /**< Task is deleted, but its TCB has not yet been freed */
} OS_TASK_STATE;

/**
 * \brief Converts a time in milliseconds to a time in ticks
 *
 * \param [in] time_in_ms time in milliseconds
 *
 * \return time in ticks
 *
 */
 #define OS_TIME_TO_TICKS(time_in_ms)    portCONVERT_MS_2_TICKS(time_in_ms)

/**
 * \brief Return current OS task handle
 *
 * \return current task handle of type OS_TASK
 *
 */
 #define OS_GET_CURRENT_TASK()           xTaskGetCurrentTaskHandle()

/**
 * \brief Create OS task
 *
 * Function creates OS task. Task is added to ready list.
 *
 * \param [in] name task name
 * \param [in] task_func starting point of task
 * \param [in] arg parameter past to \p task_func on task start
 * \param [in] stack_size stack size allocated for task in bytes
 * \param [in] priority number specifying task priority
 * \param [in,out] task OS specific task handle
 *
 * \return OS_TASK_CREATE_SUCCESS if task was created successfully
 *
 */
 #if (dg_configSYSTEMVIEW == 0)
  #define OS_TASK_CREATE(name, task_func, arg, stack_size, priority, task) \
    xTaskCreate((task_func), (name), (((stack_size) - 1) / sizeof(StackType_t) + 1), (arg), (priority), &(task))
 #else
  #define OS_TASK_CREATE(name, task_func, arg, stack_size, priority, task)                           \
    xTaskCreate((task_func),                                                                         \
                (name),                                                                              \
                (((stack_size + dg_configSYSTEMVIEW_STACK_OVERHEAD) - 1) / sizeof(StackType_t) + 1), \
                (arg),                                                                               \
                (priority),                                                                          \
                &(task))
 #endif                                /* (dg_configSYSTEMVIEW == 1) */

/**
 * \brief Delete OS task
 *
 * Function deletes OS task.
 *
 * \param [in,out] task OS specific task handle
 *
 */
 #define OS_TASK_DELETE(task)                                         vTaskDelete(task)

/**
 * \brief Get the priority of an OS task
 *
 * Function returns the priority of an OS task.
 *
 * \param [in] task OS specific task handle. if NULL, the running task is assummed.
 *
 * \return the priority of the task (OS_UBASE_TYPE)
 *
 */
 #define OS_TASK_PRIORITY_GET(task)                                   uxTaskPriorityGet(task)

/**
 * \brief Set the priority of an OS task
 *
 * Function sets the priority of an OS task.
 *
 * \param [in] task OS specific task handle
 * \param [in] prio OS new priority
 *
 */
 #define OS_TASK_PRIORITY_SET(task, prio)                             vTaskPrioritySet(task, prio)

/**
 * \brief The running OS task yields control to the scheduler
 *
 * Function requests a context switch to another task.
 *
 */
 #define OS_TASK_YIELD()                                              portYIELD()

/**
 * \brief Send an event directly to task
 *
 * Must not be called from ISR!
 *
 * \param [in] task id of task to notify
 * \param [in] value used to update the notification value of the subject \p task
 * \param [in] action action that performs when notify is occurred
 *
 * \return OS_TASK_NOTIFY_FAIL if \p action is set as OS_NOTIFY_VAL_WITHOUT_OVERWRITE and \p task
 *         already had a notification pending, OS_TASK_NOTIFY_SUCCESS otherwise
 *
 */
 #define OS_TASK_NOTIFY(task, value, action)                          xTaskNotify((task), (value), (action))

/**
 * \brief Notify OS task sending an event and return previous notification value
 *
 * Must not be called from ISR!
 *
 * \param [in] task id of task to notify
 * \param [in] value used to update the notification value of the subject \p task
 * \param [in] action action that performs when notify is occurred
 * \param [out] prev_value pointer to previous notification value - optional - can be set to NULL
 *
 * \return OS_TASK_NOTIFY_FAIL if \p action is set as OS_NOTIFY_VAL_WITHOUT_OVERWRITE and \p task
 *         already had a notification pending, OS_TASK_NOTIFY_SUCCESS otherwise
 *
 */
 #define OS_TASK_NOTIFY_AND_QUERY(task, value, action, prev_value)    xTaskNotifyAndQuery((task), (value), (action), \
                                                                                          (prev_value))

/**
 * \brief Send an event and unblock OS task with updating notification value
 *
 * A version of OS_TASK_NOTIFY that can be called from ISR.
 *
 * \param [in] task id of task to notify
 * \param [in] value used to update the notification value of the subject \p task
 * \param [in] action action that performs when notify is occurred
 *
 * \return OS_TASK_NOTIFY_FAIL if \p action is set as OS_NOTIFY_VAL_WITHOUT_OVERWRITE and \p task
 *         already had a notification pending, OS_TASK_NOTIFY_SUCCESS otherwise
 *
 */
 #define OS_TASK_NOTIFY_FROM_ISR(task, value, action)                \
    ({                                                               \
        BaseType_t need_switch, ret;                                 \
        ret = xTaskNotifyFromISR(task, value, action, &need_switch); \
        portEND_SWITCHING_ISR(need_switch);                          \
        ret;                                                         \
    })

/**
 * \brief Notify task and receive OS task notification value
 *
 * Must not called from ISR! Use OS_TASK_NOTIFY_GIVE_FROM_ISR instead.
 *
 * \param [in] task id of task to notify
 *
 * \return OS_TASK_NOTIFY_GIVE calls OS_TASK_NOTIFY with action set to OS_NOTIFY_INCREMENT resulting
 *         in all calls returning OS_TASK_NOTIFY_SUCCESS
 *
 */
 #define OS_TASK_NOTIFY_GIVE(task)    xTaskNotifyGive(task)

/**
 * \brief Notify task from ISR
 *
 * Send notification from interrupt service routine (ISR) to \p task that can unblock the receiving
 * task and optionally update the receiving task's notification value.
 * This function is safe to call from ISR.
 *
 * \param [in] task id of task to notify
 *
 */
 #define OS_TASK_NOTIFY_GIVE_FROM_ISR(task)         \
    ({                                              \
        BaseType_t need_switch;                     \
        vTaskNotifyGiveFromISR(task, &need_switch); \
        portEND_SWITCHING_ISR(need_switch);         \
    })

/**
 * \brief Clear to zero or decrement task notification value on exit
 *
 * \param [in] clear_on_exit = pdFASLE: RTOS task's notification value is decremented before
 *                             OS_TASK_NOTIFY_TAKE() exits,
 *                             pdTRUE: the RTOS task's notification value is reset to 0 before
 *                             OS_TASK_NOTIFY_TAKE() exits.
 * \param [in] time_to_wait maximum time to wait in the blocked state for a notification to be
 *                          received if a notification is not already pending when
 *                          OS_TASK_NOTIFY_TAKE() is called
 *
 * \return the value of the task's notification value before it is decremented or cleared
 *
 */
 #define OS_TASK_NOTIFY_TAKE(clear_on_exit, time_to_wait)    ulTaskNotifyTake((clear_on_exit), (time_to_wait))

/**
 * \brief Wait for the calling task to receive a notification
 *
 * \param [in] entry_bits any bits set in entry_bits will be cleared in calling notification value
 *                        before enters to OS_TASK_NOTIFY_WAIT
 * \param [in] exit_bits any bits set in exit_bits will be cleared in calling notification value
 *                       before OS_TASK_NOTIFY_WAIT function exits if a notification was received
 * \param [out] value pointer to task's notification value, if not required can be set to NULL
 * \param [in] ticks_to_wait maximum time to wait in the blocked state for a notification to be
 *                           received if a notification is not already pending when
 *                           OS_TASK_NOTIFY_WAIT is called
 *
 * \return OS_TASK_NOTIFY_SUCCESS if notification was received or was already pending when
 *         OS_TASK_NOTIFY_WAIT was called
 *         OS_TASK_NOTIFY_FAIL if the call OS_TASK_NOTIFY_WAIT timed out before notification was
 *         received
 *
 */
 #define OS_TASK_NOTIFY_WAIT(entry_bits, exit_bits, value, ticks_to_wait) \
    xTaskNotifyWait((entry_bits), (exit_bits), (value), (ticks_to_wait))

/**
 * \brief Resume task
 *
 * Make \p task ready to run.
 *
 * \param [in] task id of task to resume
 *
 */
 #define OS_TASK_RESUME(task)              vTaskResume(task)

/**
 * \brief Resume task
 *
 * Make \p task ready to run. This function is safe to call from ISR.
 *
 * \param [in] task id of task to resume
 *
 */
 #define OS_TASK_RESUME_FROM_ISR(task)     xTaskResumeFromISR(task)

/**
 * \brief Suspend task
 *
 * Remove \p task from execution queue. Task will not be run
 * until OS_TASK_RESUME or OS_TASK_RESUME_FROM_ISR is called.
 *
 * \param [in] task id of task to suspend
 *
 */
 #define OS_TASK_SUSPEND(task)             vTaskSuspend(task)

/**
 * \brief Suspend task
 *
 * Remove \p task from execution queue. Task will not be run
 * until OS_TASK_RESUME or OS_TASK_RESUME_FROM_ISR is called.
 * This function is safe to call from ISR.
 *
 * \param [in] task id of task to suspend
 *
 */
 #define OS_TASK_SUSPEND_FROM_ISR(task)    vTaskSuspendFromISR(task)

/**
 * \brief Create OS mutex
 *
 * Function creates OS mutex.
 *
 * \param [in,out] mutex
 *
 * \return OS_MUTEX_CREATE_SUCCESS when mutex was created successfully, OS_MUTEX_CREATE_FAILED
 *         otherwise
 */
 #define OS_MUTEX_CREATE(mutex)                                           \
    ({                                                                    \
        (mutex) = xSemaphoreCreateRecursiveMutex();                       \
        mutex != NULL ? OS_MUTEX_CREATE_SUCCESS : OS_MUTEX_CREATE_FAILED; \
    })

/**
 * \brief Delete OS mutex
 *
 * Function deletes OS mutex.
 *
 * \param [in] mutex
 *
 */
 #define OS_MUTEX_DELETE(mutex)          vSemaphoreDelete(mutex)

/**
 * \brief Relase mutex
 *
 * Decrease mutex count, when numer of calls to OS_MUTEX_GET equals number of calls to
 * OS_MUTEX_PUT, mutex can be acquired by other task.
 *
 * \param [in] mutex id of mutex to realse
 *
 */
 #define OS_MUTEX_PUT(mutex)             xSemaphoreGiveRecursive(mutex)

/**
 * \brief Acquire mutex
 *
 * Access to shared resource can be guarded by mutex. When task wants to get access
 * to this resource call OS_MUTEX_GET. If mutex was not taken by any task yet it, call
 * will succeed and mutex will be assigned to calling task. Next call to already acquired
 * mutex from same task will succeed. If mutex is already taken by other task calling
 * task will wait for specified time before failing.
 * For non-blocking acquire \p timeout can be OS_MUTEX_NO_WAIT, for infinite wait till
 * mutex is released OS_MUTEX_FOREVER should be used.
 *
 * \param [in] mutex id of mutex to acquire
 * \param [in] timeout number of ticks that to acquire mutex
 *
 */
 #define OS_MUTEX_GET(mutex, timeout)    xSemaphoreTakeRecursive((mutex), (timeout))

/**
 * \brief Create OS event
 *
 * Function creates OS event that can be used to synchronize.
 *
 * \param [in,out] event
 *
 */
 #define OS_EVENT_CREATE(event)          do {(event) = xSemaphoreCreateBinary();} while (0)

/**
 * \brief Delete OS event
 *
 * Function destroys OS event.
 *
 * \param [in] event item to delete
 *
 */
 #define OS_EVENT_DELETE(event)          vSemaphoreDelete(event)

/**
 * \brief Set event in signaled state
 *
 * Set event in signaled stated so OS_EVENT_WAIT will release waiting task if any.
 * Event will remain in signaled stated till call to OS_EVENT_WAIT releases one task.
 * This function should not be called from ISR.
 *
 * \param [in] event
 *
 */
 #define OS_EVENT_SIGNAL(event)          xSemaphoreGive(event)

/**
 * \brief Set event in signaled state
 *
 * Set event in signaled stated so OS_EVENT_WAIT will release waiting task if any.
 * Event will remain in signaled stated till call to OS_EVENT_WAIT releases one task.
 * This function is safe to call from ISR.
 *
 * \param [in] event
 *
 */
 #define OS_EVENT_SIGNAL_FROM_ISR(event)                  \
    ({                                                    \
        BaseType_t need_switch, ret;                      \
        ret = xSemaphoreGiveFromISR(event, &need_switch); \
        portEND_SWITCHING_ISR(need_switch);               \
        ret;                                              \
    })

/**
 * \brief Wait for event
 *
 * This function wait for \p event to be in signaled stated.
 * If event was already in signaled state or become signaled in specified time
 * function will return OS_EVENT_SIGNALED.
 * To check if event is already signaled use OS_EVENT_NO_WAIT as timeout.
 * To wait till event is signaled use OS_EVENT_FOREVERE.
 * This function can't be used in ISR.
 *
 * \param [in] event if of event to wait on
 * \param [in] timeout number of ticks to wait
 *
 * \return OS_EVENT_SIGNALED if event was signaled other value if not
 *
 */
 #define OS_EVENT_WAIT(event, timeout)              xSemaphoreTake((event), (timeout))

/**
 * \brief Check if event is signaled without waiting
 *
 * This function will return immediately with OS_EVENT_SIGNALED if event
 * was in signaled state already. In case the event is signaled, its state
 * changes to not signaled after calling this function.
 *
 * \param [in] event if of event to wait on
 *
 * \return OS_EVENT_SIGNALED if event was signaled other value if not
 *
 */
 #define OS_EVENT_CHECK(event)                      xSemaphoreTake((event), OS_EVENT_NO_WAIT)

 #define OS_EVENT_YIELD(higherPriorityTaskWoken)    portYIELD_FROM_ISR(higherPriorityTaskWoken)

/**
 * \brief Create OS event group
 *
 * Function creates OS event group
 *
 * \return event group handle if successful, otherwise NULL
 *
 */
 #define OS_EVENT_GROUP_CREATE()                    xEventGroupCreate()

/**
 * \brief Event group wait bits
 *
 * Function reads bits within event group optionally entering the Blocked state (with a timeout)
 * to wait for a bit or group of bits to become set.
 *
 * \param [in] event_group the event group in which the bits are being tested
 * \param [in] bits_to_wait a bitwise value to test inside the event group
 * \param [in] clear_on_exit = OS_OK: any bits set in the value passed as the bits_to_wait
 *                             parameter will be cleared in the event group before
 *                             xEventGroupWaitBits returns
 *                             OS_FAIL: bits in the event group are not altered when the call
 *                             to xEventGroupWaitBits() returns
 * \param [in] wait_for_all = OS_OK: xEventGroupWaitBits() will return when either *all* bits
 *                            set in the value passed as the bits_to_wait parameter are set in
 *                            the event group
 *                            OS_FAIL: xEventGroupWaitBits() will return when *any* of the bits set
 *                            in the value passed as the bits_to_wait parameter are set in the event
 *                            group
 * \param [in] timeout maximum amount of time to wait for one/all of the bits specified
 *                     by bits_to_wait to become set
 *
 * \return the value of the event group at the time either the event bits being waited for
 *         became set, or the timeout expired
 *
 */
 #define OS_EVENT_GROUP_WAIT_BITS(event_group, bits_to_wait, clear_on_exit, wait_for_all, timeout) \
    xEventGroupWaitBits((event_group), (bits_to_wait), (clear_on_exit), (wait_for_all), (timeout))

/**
 * \brief Event group set bits
 *
 * Set bits (flags) within an event group
 *
 * \param [in] event_group the event group in which the bits are to be set
 * \param [in] bits_to_set a bitwise value that indicates the bit or bits to set in the event group
 *
 * \return the value of the event group at the time the call to xEventGroupSetBits() returns
 *
 */
 #define OS_EVENT_GROUP_SET_BITS(event_group, bits_to_set)    xEventGroupSetBits((event_group), (bits_to_set))

/**
 * \brief Set event group bits from ISR
 *
 * Set bits (flags) within an RTOS event group that can be called from an ISR.
 *
 * \param [in] event_group the event group in which the bits are to be set
 * \param [in] bits_to_set a bitwise value that indicates the bit or bits to set in the event group
 *
 * \return if the message was sent to the RTOS daemon task then OS_OK is returned,
 *         otherwise OS_FAIL is returned
 *
 */
 #define OS_EVENT_GROUP_SET_BITS_FROM_ISR(event_group, bits_to_set)                    \
    ({                                                                                 \
        BaseType_t need_switch, ret;                                                   \
        ret = xEventGroupSetBitsFromISR((event_group), (bits_to_set), &(need_switch)); \
        portEND_SWITCHING_ISR(need_switch);                                            \
        ret;                                                                           \
    })

/**
 * \brief Clear event group bits
 *
 * Function clear bits (flags) within an event group.
 *
 * \param [in] event_group the event group in which the bits are to be cleared
 * \param [in] bits_to_clear a bitwise value that indicates the bit or bits to clear
 *                           in the event group
 *
 * \return value of the event group before the specified bits were cleared
 *
 */
 #define OS_EVENT_GROUP_CLEAR_BITS(event_group, bits_to_clear)    xEventGroupClearBits((event_group), (bits_to_clear))

/**
 * \brief Clear event group bits from an interrupt
 *
 * Function clear bits (flags) within an event group from an interrupt.
 *
 * \param [in] event_group the event group in which the bits are to be cleared
 * \param [in] bits_to_clear a bitwise value that indicates the bit or bits to clear
 *                           in the event group
 *
 * \return value of the event group before the specified bits were cleared
 *
 */
 #define OS_EVENT_GROUP_CLEAR_BITS_FROM_ISR(event_group, bits_to_clear) \
    xEventGroupClearBitsFromISR((event_group), (bits_to_clear))

/**
 * \brief Get event group bits
 *
 * Function returns the current value of the event bits (event flags) in an event group.
 *
 * \param [in] event_group the event group being queried
 *
 * \return value of the event bits in the event group at the time
 *         OS_EVENT_GROUP_GET_BITS() was called
 *
 */
 #define OS_EVENT_GROUP_GET_BITS(event_group)             xEventGroupGetBits(event_group)

/**
 * \brief Get event group bits from an interrupt
 *
 * Function returns the current value of the event bits (event flags) in an event group from an
 * interrupt
 *
 * \param [in] event_group the event group being queried
 *
 * \return value of the event bits in the event group at the time OS_EVENT_GROUP_GET_BITS_FROM_ISR()
 *         was called
 *
 */
 #define OS_EVENT_GROUP_GET_BITS_FROM_ISR(event_group)    xEventGroupGetBitsFromISR(event_group)

/**
 * \brief Synchronize event group bits
 *
 * Atomically set bits (flags) within an event group, then wait for a combination of bits to be
 * set within the same event group.
 *
 * \param [in] event_group event group in which the bits are being set and tested
 * \param [in] bits_to_set bit or bits to set in the event group before determining if all
 *                         the bits specified by the bits_to_wait parameter are set
 * \param [in] bits_to_wait a bitwise value that indicates the bit or bits to test inside
 *                          the event group
 * \param [in] timeout maximum amount of time (specified in 'ticks') to wait for all the bits
 *                     specified by the bits_to_wait parameter value to become set
 *
 * \return value of the event group at the time either the bits being waited for became set,
 *         or the block time expired
 *
 */
 #define OS_EVENT_GROUP_SYNC(event_group, bits_to_set, bits_to_wait, timeout) \
    xEventGroupSync((event_group), (bits_to_set), (bits_to_wait), (timeout))

/**
 * \brief Delete event group
 *
 * Function deletes an event group.
 *
 * \param [in] event_group the event group being deleted.
 *
 */
 #define OS_EVENT_GROUP_DELETE(event_group)    vEventGroupDelete(event_group)

/**
 * \brief Create OS queue
 *
 * Function creates OS queue that can contain \p max_items of specified size.
 *
 * \param [in,out] queue queue to initialize
 * \param [in] item_size queue element size
 * \param [in] max_items max number of items that queue can store
 *
 */
 #define OS_QUEUE_CREATE(queue, item_size, max_items) \
    do {(queue) = xQueueCreate((max_items), (item_size));} while (0)

/**
 * \brief Deletes OS queue
 *
 * Function deletes OS.
 *
 * \param [in] queue queue to delete
 *
 */
 #define OS_QUEUE_DELETE(queue)                vQueueDelete(queue)

/**
 * \brief Put element in queue
 *
 * Function adds element into queue if there is enough room for it.
 * If there is no room in queue for \p timeout ticks element is not
 * put in queue and error is returned.
 *
 * \param [in] queue id of queue to put item to
 * \param [in] item pointer to element to enqueue
 * \param [in] timeout max time in ticks to wait for space in queue
 *
 * \return OS_QUEUE_FULL if there was no place in queue
 *         OS_QUEUE_OK if message was put in queue
 *
 */
 #define OS_QUEUE_PUT(queue, item, timeout)    xQueueSendToBack((queue), (item), (timeout))

/**
 * \brief Put element in queue
 *
 * Function adds element into queue if there is enough room for it.
 * If there is no room in queue error is returned immediately.
 *
 * This is safe to call from ISR.
 *
 * \param [in] queue id of queue to put item to
 * \param [in] item pointer to element to enqueue
 *
 * \return OS_QUEUE_FULL if there was no place in queue
 *         OS_QUEUE_OK if message was put in queue
 *
 */
 #define OS_QUEUE_PUT_FROM_ISR(queue, item)                           \
    ({                                                                \
        BaseType_t need_switch, ret;                                  \
        ret = xQueueSendToBackFromISR((queue), (item), &need_switch); \
        portEND_SWITCHING_ISR(need_switch);                           \
        ret;                                                          \
    })

/**
 * \brief Get element from queue
 *
 * Function adds element into queue if there is enough room for it.
 * If there is nothing in queue for \p timeout ticks error is returned.
 * Use OS_QUEUE_NO_WAIT for \p timeout to get message without waiting.
 * Use OS_QUEUE_FOREVER to wait till message arrives.
 *
 * \param [in] queue id of queue to get item from
 * \param [out] item pointer to buffer that will receive element from queue
 * \param [in] timeout max time in ticks to wait for element in queue
 *
 * \return OS_QUEUE_EMPTY if there was nothing in queue
 *         OS_QUEUE_OK if message was get from queue
 *
 */
 #define OS_QUEUE_GET(queue, item, timeout)     xQueueReceive((queue), (item), (timeout))

/**
 * \brief Peek element on queue
 *
 * Function gets element from queue without removing it.
 * If there is nothing in queue for \p timeout ticks error is returned.
 * Use OS_QUEUE_NO_WAIT for \p timeout to get message without waiting.
 * Use OS_QUEUE_FOREVER to wait till message arrives.
 *
 * \param [in] queue id of queue to peek item from
 * \param [out] item pointer to buffer that will receive element from queue
 * \param [in] timeout max time in ticks to wait for element in queue
 *
 * \return OS_QUEUE_EMPTY if there was nothing in queue
 *         OS_QUEUE_OK if message was get from queue
 *
 */
 #define OS_QUEUE_PEEK(queue, item, timeout)    xQueuePeek((queue), (item), (timeout))

/**
 * \brief Get the number of messages stored in the queue
 *
 * \param [in] queue id of the queue to check.
 */
 #define OS_QUEUE_MESSAGES_WAITING(queue)       uxQueueMessagesWaiting((queue))

/**
 * \brief Create software timer
 *
 * Function creates software timer with given timeout
 *
 * \param [in] name     timer name
 * \param [in] period   timer period in ticks
 * \param [in] reload   indicates if callback will be called once or multiple times
 * \param [in] timer_id identifier which can be used to identify timer in callback function
 * \param [in] callback callback called when timer expires
 *
 * \return OS_TIMER if timer created successfully, otherwise null
 */
 #define OS_TIMER_CREATE(name, period, reload, timer_id, callback) \
    xTimerCreate((name), (period), ((reload) ? pdTRUE : pdFALSE), ((void *) (timer_id)), (callback))

/**
 * \brief Get timer ID
 *
 * Function returns timer_id assigned in OS_TIMER_CREATE
 *
 * \param [in] timer timer handle
 *
 * \return timer id
 */
 #define OS_TIMER_GET_TIMER_ID(timer)      pvTimerGetTimerID(timer)

/**
 * \brief Check if timer is active
 *
 * Function checks timer status
 *
 * \param [in] timer timer handle
 *
 * \return true if timer is active, otherwise false
 */
 #define OS_TIMER_IS_ACTIVE(timer)         xTimerIsTimerActive(timer)

/**
 * \brief Start timer
 *
 * Function starts timer
 *
 * \param [in]  timer timer handle returned in OS_TIMER_CREATE
 * \param [in]  timeout max time in ticks to wait until command is sent
 *
 * \return OS_TIMER_SUCCESS if command has been sent successfully,
 * or OS_TIMER_FAIL if timeout occur
 */
 #define OS_TIMER_START(timer, timeout)    xTimerStart((timer), (timeout))

/**
 * \brief Stop timer
 *
 * Function stops timer
 *
 * \param [in]  timer timer handle returned in OS_TIMER_CREATE
 * \param [in]  timeout max time in ticks to wait until command is sent
 *
 * \return OS_TIMER_SUCCESS if command has been sent successfully,
 * or OS_TIMER_FAIL if timeout occur
 */
 #define OS_TIMER_STOP(timer, timeout)     xTimerStop((timer), (timeout))

/**
 * \brief Change timer's period
 *
 * Functions updates timer's period
 *
 * \param [in] timer timer handle
 * \param [in] period new timer's period
 * \param [in] timeout max time in ticks to wait until command is sent
 *
 * \return OS_TIMER_SUCCESS if command has been sent successfully,
 * or OS_TIMER_FAIL if timeout occur
 */
 #define OS_TIMER_CHANGE_PERIOD(timer, period, timeout) \
    xTimerChangePeriod((timer), (period), (timeout))

/**
 * \brief Delete timer
 *
 * Function deletes previously created timer
 *
 * \param [in] timer timer handle
 * \param [in] timeout max time in ticks to wait until command is sent
 *
 * \return OS_TIMER_SUCCESS if command has been sent successfully,
 * or OS_TIMER_FAIL if timeout occur
 */
 #define OS_TIMER_DELETE(timer, timeout)    xTimerDelete((timer), (timeout))

/**
 * \brief Reset timer
 *
 * Function restarts previously created timer
 *
 * \param [in] timer timer handle
 * \param [in] timeout max time in ticks to wait until command is sent
 *
 * \return OS_TIMER_SUCCESS if command has been sent successfully,
 * or OS_TIMER_FAIL if timeout occur
 */
 #define OS_TIMER_RESET(timer, timeout)     xTimerReset((timer), (timeout))

/**
 * \brief Start timer from ISR
 *
 * Version of OS_TIMER_START that can be called from an interrupt service
 * routine
 *
 * \param [in] timer timer handle
 *
 * \return OS_TIMER_SUCCESS if command has been sent successfully,
 * otherwise OS_TIMER_FAIL
 *
 * \sa OS_TIMER_START()
 */
 #define OS_TIMER_START_FROM_ISR(timer)                    \
    ({                                                     \
        BaseType_t need_switch, ret;                       \
        ret = xTimerStartFromISR((timer), &(need_switch)); \
        portEND_SWITCHING_ISR(need_switch);                \
        ret;                                               \
    })

/**
 * \brief Stop timer from ISR
 *
 * Version of OS_TIMER_STOP that can be called from an interrupt service
 * routine
 *
 * \param [in] timer timer handle
 *
 * \return OS_TIMER_SUCCESS if command has been sent successfully,
 * otherwise OS_TIMER_FAIL
 *
 * \sa OS_TIMER_STOP()
 */
 #define OS_TIMER_STOP_FROM_ISR(timer)                    \
    ({                                                    \
        BaseType_t need_switch, ret;                      \
        ret = xTimerStopFromISR((timer), &(need_switch)); \
        portEND_SWITCHING_ISR(need_switch);               \
        ret;                                              \
    })

/**
 * \brief Reset timer from ISR
 *
 * Version of OS_TIMER_RESET that can be called from an interrupt service
 * routine
 *
 * \param [in] timer timer handle
 *
 * \return OS_TIMER_SUCCESS if command has been sent successfully,
 * otherwise OS_TIMER_FAIL
 *
 * \sa OS_TIMER_RESET()
 */
 #define OS_TIMER_RESET_FROM_ISR(timer)                    \
    ({                                                     \
        BaseType_t need_switch, ret;                       \
        ret = xTimerResetFromISR((timer), &(need_switch)); \
        portEND_SWITCHING_ISR(need_switch);                \
        ret;                                               \
    })

/**
 * \brief Change timer period from ISR
 *
 * Version of OS_TIMER_CHANGE_PERIOD that can be called from an interrupt service
 * routine
 *
 * \param [in] timer timer handle
 * \param [in] period new timer period
 *
 * \return OS_TIMER_SUCCESS if command has been sent successfully,
 * otherwise OS_TIMER_FAIL
 *
 * \sa OS_TIMER_CHANGE_PERIOD
 */
 #define OS_TIMER_CHANGE_PERIOD_FROM_ISR(timer, period)                     \
    ({                                                                      \
        BaseType_t need_switch, ret;                                        \
        ret = xTimerChangePeriodFromISR((timer), (period), &(need_switch)); \
        portEND_SWITCHING_ISR(need_switch);                                 \
        ret;                                                                \
    })

/**
 * \brief Reset timer from ISR
 *
 * Version of OS_TIMER_RESET that can be called from an interrupt service
 * routine
 *
 * \param [in] timer timer handle
 *
 * \return OS_TIMER_SUCCESS if command has been sent successfully,
 * otherwise OS_TIMER_FAIL
 *
 * \sa OS_TIMER_RESET()
 */
 #define OS_TIMER_RESET_FROM_ISR(timer)                    \
    ({                                                     \
        BaseType_t need_switch, ret;                       \
        ret = xTimerResetFromISR((timer), &(need_switch)); \
        portEND_SWITCHING_ISR(need_switch);                \
        ret;                                               \
    })

/**
 * \brief Delay execution of task for specified time
 *
 * This function delays in OS specific way execution of current task.
 *
 * \param [in] ticks number of ticks to wait
 *
 */
 #define OS_DELAY(ticks)         vTaskDelay(ticks)

/**
 * \brief Get current tick count
 *
 * \return current tick count
 *
 */
 #define OS_GET_TICK_COUNT()     xTaskGetTickCount()

/**
 * \brief Convert from OS ticks to ms
 *
 * \param [in] ticks tick count to convert
 *
 * \return value in ms
 *
 */
 #define OS_TICKS_2_MS(ticks)    portCONVERT_TICKS_2_MS(ticks)

/**
 * \brief Convert from ms to OS ticks
 *
 * \param [in] ms milliseconds to convert
 *
 * \return value in OS ticks
 *
 */
 #define OS_MS_2_TICKS(ms)       portCONVERT_MS_2_TICKS(ms)

/**
 * \brief Delay execution of task for specified time
 *
 * This function delays in OS specific way execution of current task.
 *
 * \param [in] ms number of ms to wait
 *
 */
 #define OS_DELAY_MS(ms)         OS_DELAY(OS_MS_2_TICKS(ms))

/**
 * \brief Enter critical section from non-ISR context
 *
 * This allows to enter critical section from non-ISR context.
 * Implementation will disable interrupts with nesting counter.
 * This function can be called several times by task but requires same
 * number of OS_LEAVE_CRITICAL_SECTION calls to allow task switching and interrupts
 * again.
 *
 * \sa OS_LEAVE_CRITICAL_SECTION
 *
 */
 #define OS_ENTER_CRITICAL_SECTION() \
    do {                             \
        OS_ASSERT(!in_interrupt());  \
        portENTER_CRITICAL();        \
    } while (0)

/**
 * \brief Enter critical section from ISR context
 *
 * This function allows to enter critical section from ISR context.
 * It can be called several times from within ISR context but requires same
 * number of OS_LEAVE_CRITICAL_SECTION calls to restore interrupt status.
 *
 * \sa OS_LEAVE_CRITICAL_SECTION_FROM_ISR
 *
 */
 #define OS_ENTER_CRITICAL_SECTION_FROM_ISR(critical_section_status) \
    do {                                                             \
        OS_ASSERT(in_interrupt());                                   \
        critical_section_status = portSET_INTERRUPT_MASK_FROM_ISR(); \
    } while (0)

/**
 * \brief Leave critical section from non-ISR context.
 *
 * Function restores interrupts and task switching.
 * Number of calls to this function must match number of calls to OS_ENTER_CRITICAL_SECTION.
 *
 * \sa OS_ENTER_CRITICAL_SECTION
 *
 */
 #define OS_LEAVE_CRITICAL_SECTION() \
    do {                             \
        OS_ASSERT(!in_interrupt());  \
        portEXIT_CRITICAL();         \
    } while (0)

/**
 * \brief Leave critical section from ISR context
 *
 * Function restores interrupts from ISR context.
 * Number of calls to this function must match number of calls to OS_ENTER_CRITICAL_SECTION_FROM_ISR.
 *
 * \sa OS_ENTER_CRITICAL_SECTION_FROM_ISR
 *
 */
 #define OS_LEAVE_CRITICAL_SECTION_FROM_ISR(critical_section_status) \
    do {                                                             \
        OS_ASSERT(in_interrupt());                                   \
        portCLEAR_INTERRUPT_MASK_FROM_ISR(critical_section_status);  \
    } while (0)

/**
 * \brief Name for OS memory allocation function
 *
 * \sa OS_MALLOC
 *
 */
 #define OS_MALLOC_FUNC          pvPortMalloc

/**
 * \brief Name for non-retain memory allocation function
 *
 * \sa OS_MALLOC_FUNC
 *
 */
 #define OS_MALLOC_NORET_FUNC    pvPortMalloc

/**
 * \brief Allocate memory from OS provided heap
 *
 * \sa OS_FREE
 *
 */
 #define OS_MALLOC(size)          OS_MALLOC_FUNC(size)

/**
 * \brief Allocate memory from non-retain heap
 *
 * \sa OS_FREE
 *
 */
 #define OS_MALLOC_NORET(size)    OS_MALLOC_NORET_FUNC(size)

/**
 * \brief Name for OS free memory function
 *
 * \sa OS_FREE
 *
 */
 #define OS_FREE_FUNC          vPortFree

/**
 * \brief Name for non-retain memory free function
 *
 * \sa OS_FREE_NORET
 * \sa OS_MALLOC_NORET
 *
 */
 #define OS_FREE_NORET_FUNC    vPortFree

/**
 * \brief Free memory allocated by OS_MALLOC()
 *
 * \sa OS_MALLOC
 *
 */
 #define OS_FREE(addr)                                     OS_FREE_FUNC(addr)

/**
 * \brief Free memory allocated by OS_MALLOC_NORET()
 *
 * \sa OS_MALLOC_NORET
 *
 */
 #define OS_FREE_NORET(addr)                               OS_FREE_NORET_FUNC(addr)

 #if (configUSE_TRACE_FACILITY == 1)

/**
 * \brief Get task status
 *
 * Function gets the status of a task
 *
 * \param [in] task_status where the status of the task is stored
 * \param [in] status_size the size of the above container
 *
 * \return the number of the monitored tasks
 *
 */
  #define OS_GET_TASKS_STATUS(task_status, status_size)    uxTaskGetSystemState(task_status, status_size, NULL)
 #else
  #define OS_GET_TASKS_STATUS(task_status, status_size)
 #endif

 #if (INCLUDE_uxTaskGetStackHighWaterMark == 1)

/**
 * \brief Get task status
 *
 * Function gets the status of a task
 *
 * \param [in] task_id the task id of the tracked task
 *
 * \return high water mark of the stack in bytes
 *
 */
  #define OS_GET_STACK_WATERMARK(task_id)    uxTaskGetStackHighWaterMark(task_id)
 #else
  #define OS_GET_STACK_WATERMARK(task_id)
 #endif

/**
 * \brief Get heap min water mark size
 *
 * Function gets heap min water mark size
 *
 *
 * \return The heap min water mark size in bytes
 *
 */
 #define OS_GET_HEAP_WATERMARK()       xPortGetMinimumEverFreeHeapSize()

/**
 * \brief Get current free heap size
 *
 * Function gets heap current available size
 *
 *
 * \return Current free heap size in bytes
 *
 */
 #define OS_GET_FREE_HEAP_SIZE()       xPortGetFreeHeapSize()

/**
 * \brief Get current number OS tasks
 *
 * Function gets current number OS tasks
 *
 *
 * \return the current number of OS tasks
 *
 */
 #define OS_GET_TASKS_NUMBER()         uxTaskGetNumberOfTasks()

 #if (INCLUDE_pcTaskGetTaskName == 1)

/**
 * \brief Get task name
 *
 * Function gets task name
 *
 * \param [in] task_id the task id of the monitored task
 *
 * \return a string pointer, points to the name of task
 *
 */
  #define OS_GET_TASK_NAME(task_id)    pcTaskGetTaskName(task_id)
 #else
  #define OS_GET_TASK_NAME(task_id)
 #endif

 #if (INCLUDE_eTaskGetState == 1)

/**
 * \brief Get task state
 *
 * Function gets task state
 *
 * \param [in] task_id the task id of the monitored task
 *
 * \return the task state in OS_TASK_STATE
 *
 */
  #define OS_GET_TASK_STATE(task_id)    eTaskGetState(task_id)
 #else
  #define OS_GET_TASK_STATE(task_id)
 #endif

 #if (INCLUDE_uxTaskPriorityGet == 1)

/**
 * \brief Get task priority
 *
 * Function gets task priority
 *
 * \param [in] task_id the task id of the monitored task
 *
 * \return the task priority
 *
 */
  #define OS_GET_TASK_PRIOTITY(task_id)    uxTaskPriorityGet(task_id)
 #else
  #define OS_GET_TASK_PRIOTITY(task_id)
 #endif

#endif                                 /*defined(OS_FREERTOS)*/

#if defined OS_BAREMETAL
 #include <stdlib.h>

/*
 * Basic set of macros that can be used in non OS environment.
 */
 #define PRIVILEGED_DATA
 #define OS_MALLOC    malloc
 #define OS_FREE      free
 #ifndef RELEASE_BUILD
  #define OS_ASSERT(a)    do {if (!(a)) {__BKPT(0);}} while (0)
 #else
  #define OS_ASSERT(a)    ((void) (a))
 #endif

#endif

#endif                                 /* OSAL_H_ */

/**
 * \}
 * \}
 */
