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
#if !defined(__FSL_OS_ABSTRACTION_BM_H__)
#define __FSL_OS_ABSTRACTION_BM_H__


/*!
 * @addtogroup os_abstraction_bm
 * @{
 */

/*******************************************************************************
 * Declarations
 ******************************************************************************/

/*! @brief Bare Metal does not use timer. */
#define FSL_OSA_BM_TIMER_NONE   0U

/*! @brief Bare Metal uses LPTMR as timer. */
#define FSL_OSA_BM_TIMER_LPTMER 1U

/*! @brief Configure what timer is used in Bare Metal. */
#ifndef FSL_OSA_BM_TIMER_CONFIG
#define FSL_OSA_BM_TIMER_CONFIG FSL_OSA_BM_TIMER_LPTMER
#endif

/*! @brief Type for an semaphore */
typedef struct Semaphore
{
    volatile bool    isWaiting;  /*!< Is any task waiting for a timeout on this object */
    volatile uint8_t semCount;   /*!< The count value of the object                    */
    uint32_t         time_start; /*!< The time to start timeout                        */
    uint32_t         timeout;    /*!< Timeout to wait in milliseconds                  */
} semaphore_t;

/*! @brief Type for a mutex */
typedef struct Mutex
{
    volatile bool    isWaiting;  /*!< Is any task waiting for a timeout on this mutex */
    volatile bool    isLocked;   /*!< Is the object locked or not                     */
    uint32_t         time_start; /*!< The time to start timeout                       */
    uint32_t         timeout;    /*!< Timeout to wait in milliseconds                 */
} mutex_t;

/*! @brief Type for an event flags group, bit 32 is reserved */
typedef uint32_t event_flags_t;

/*! @brief Type for an event object */
typedef struct Event
{
    volatile bool             isWaiting;   /*!< Is any task waiting for a timeout on this event  */
    uint32_t         time_start;           /*!< The time to start timeout                        */
    uint32_t         timeout;              /*!< Timeout to wait in milliseconds                  */
    volatile event_flags_t    flags;       /*!< The flags status                                 */
    osa_event_clear_mode_t    clearMode;   /*!< Auto clear or manual clear                       */
} event_t;

/*! @brief Type for task parameter */
typedef void* task_param_t;

/*! @brief Type for a task pointer */
typedef void (* task_t)(task_param_t param);

/*! @brief Task control block for bare metal. */
typedef struct TaskControlBlock
{
    task_t p_func;                          /*!< Task's entry                           */
    task_param_t  param;                    /*!< Task's parameter                       */
    struct TaskControlBlock *next;          /*!< Pointer to next task control block     */
    struct TaskControlBlock *prev;          /*!< Pointer to previous task control block */
} task_control_block_t;

/*! @brief Type for a task handler, returned by the OSA_TaskCreate function */
typedef task_control_block_t* task_handler_t;

/*! @brief Type for a task stack */
typedef uint32_t task_stack_t;

/*! @brief Type for a message queue */
typedef struct MsgQueue
{
    uint32_t              *queueMem;      /*!< Points to the queue memory               */
    uint16_t               number;        /*!< The number of messages in the queue      */
    uint16_t               size;          /*!< The size in words of each message        */
    uint16_t               head;          /*!< Index of the next message to be read     */
    uint16_t               tail;          /*!< Index of the next place to write to      */
    semaphore_t            queueSem;      /*!< Semaphore wakeup tasks waiting for msg   */
    volatile bool          isEmpty;       /*!< Whether queue is empty                   */
}msg_queue_t;

/*! @brief Type for a message queue handler */
typedef msg_queue_t*  msg_queue_handler_t;

/*! @brief Constant to pass as timeout value in order to wait indefinitely. */
#define OSA_WAIT_FOREVER  0xFFFFFFFFU

/*! @brief How many tasks can the bare metal support. */
#define TASK_MAX_NUM  5

/*! @brief OSA's time range in millisecond, OSA time wraps if exceeds this value. */
#define FSL_OSA_TIME_RANGE 0xFFFFU

/*! @brief The default interrupt handler installed in vector table. */
#define OSA_DEFAULT_INT_HANDLER  ((osa_int_handler_t)(&DefaultISR))

/*! @brief The default interrupt handler installed in vector table. */
extern void DefaultISR(void);

/*!
 * @name Thread management
 * @{
 */

/*!
 * @brief Defines a task.
 *
 * This macro defines resources for a task statically. Then, the OSA_TaskCreate 
 * creates the task based-on these resources.
 *
 * @param task The task function.
 * @param stackSize The stack size this task needs in bytes.
 */
#define OSA_TASK_DEFINE(task, stackSize) \
    task_stack_t* task##_stack = NULL;   \
    task_handler_t task##_task_handler

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief Calls all task functions one time except for the current task.
 *
 * This function calls all other task functions one time. If current
 * task is waiting for an event triggered by other tasks, this function
 * could be used to trigger the event.
 *
 * @note There should be only one task calls this function, if more than
 * one task call this function, stack overflow may occurs. Be careful
 * to use this function.
 *
 */
void OSA_PollAllOtherTasks(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/* @} */

/*!
 * @name Message queues
 * @{
 */

/*!
 * @brief This macro statically reserves the memory required for the queue.
 *
 * @param name Identifier for the memory region.
 * @param number Number of elements in the queue. 
 * @param size Size of every element in words.
 */
#define MSG_QUEUE_DECLARE(name, number, size) uint32_t queueMem_##name[number * size]; \
                                              msg_queue_t entity_##name = {            \
                                                  .queueMem = queueMem_##name          \
                                              };                                       \
                                              msg_queue_t *name = &(entity_##name)

/* @} */


/*! @}*/

#endif /* __FSL_OS_ABSTRACTION_BM_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

