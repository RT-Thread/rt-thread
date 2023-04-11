/***************************************************************************//**
* \file cyhal_ipc.h
*
* \brief
* Provides a high level interface for interacting with the Infineon IPC.
* This interface abstracts out the chip specific details. If any chip specific
* functionality is necessary, or performance is critical the low level functions
* can be used directly.
*
********************************************************************************
* \copyright
* Copyright 2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/**
* \addtogroup group_hal_ipc IPC (Inter-Processor Communication)
* \ingroup group_hal
* \{
* High level interface for communicating between processors on a multi-core device.
*
* The IPC driver allows communication between multiple CPUs or between multiple tasks
* operating in different domains within a single CPU. It supports binary semaphores
* and message queues, similar to how they are used for task interactions in an RTOS envrionment.
*
* \section subsection_ipc_features Features
* * Binary semaphore for resource access control and general signalling
* * Message queue for passing data between tasks/cores
*
* \section subsection_ipc_quickstart Quick Start
* For binary semaphores, initialize the semaphore for the task/CPU. Then take/give the semaphore.
* For queues, only one task/CPU may initialize a queue. Other tasks/CPUs then get the handle
* of the created queue. Use the get/put functions to take out or put in items to the queue.
*
* \section section_ipc_snippets Code Snippets
*
* \subsection subsection_ipc_snippet1 Snippet 1: Binary semaphore example
* \snippet hal_ipc.c snippet_cyhal_ipc_semaphore
*
* \subsection subsection_ipc_snippet2 Snippet 2: Message queue example
* \snippet hal_ipc.c snippet_cyhal_ipc_queue
*/

#pragma once

#include "cyhal_hw_types.h"
#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_ipc IPC HAL Results
 *  IPC specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** Invalid parameter error */
#define CYHAL_IPC_RSLT_ERR_INVALID_PARAMETER           \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_IPC, 0))
/** Provided queue number already used */
#define CYHAL_IPC_RSLT_ERR_QUEUE_NUM_IN_USE            \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_IPC, 1))
/** Queue is full */
#define CYHAL_IPC_RSLT_ERR_QUEUE_FULL                  \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_IPC, 2))
/** Queue is empty */
#define CYHAL_IPC_RSLT_ERR_QUEUE_EMPTY                 \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_IPC, 3))
/** Queue object is not found */
#define CYHAL_IPC_RSLT_ERR_QUEUE_NOT_FOUND             \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_IPC, 4))
/** IPC interrupt was enabled for one of the cores, but was not (yet) handled */
#define CYHAL_IPC_RSLT_ERR_ISR_WAS_NOT_HANDLED         \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_IPC, 5))
/** Operation can't be performed in ISR context */
#define CYHAL_IPC_RSLT_ERR_CANT_OPERATE_IN_ISR         \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_IPC, 6))

/**
 * \}
 */

/** This define can be used as timeout argument for the IPC HAL driver functions, that take timeout
 * as input parameter, in order to make function never time out (wait forever) */
#define CYHAL_IPC_NEVER_TIMEOUT (0xFFFFFFFFUL)

/** Flags enum of IPC events. Multiple events can be enabled via \ref cyhal_ipc_queue_enable_event and
 * the callback from \ref cyhal_ipc_queue_register_callback will be run to notify. */
typedef enum
{
    CYHAL_IPC_NO_INTR           = 0,      //!< No interrupt
    CYHAL_IPC_QUEUE_WRITE       = 1 << 0, //!< New item was written to the queue
    CYHAL_IPC_QUEUE_READ        = 1 << 1, //!< New item was read from the queue
    CYHAL_IPC_QUEUE_FULL        = 1 << 2, //!< Queue is full
    CYHAL_IPC_QUEUE_EMPTY       = 1 << 3, //!< Queue is empty
    CYHAL_IPC_QUEUE_RESET       = 1 << 4, //!< Queue was reset
} cyhal_ipc_event_t;

/** Event handler for IPC interrupts */
typedef void (*cyhal_ipc_event_callback_t)(void *callback_arg, cyhal_ipc_event_t event);

/** IPC queue structure element
*/
typedef struct cyhal_ipc_queue_s
{
    uint32_t channel_num;       //!< IPC channel number (e.g. CYHAL_IPC_CHAN_0) (populated by user during initialization)
    uint32_t queue_num;         //!< Queue number (populated by user during initialization)
    void *queue_pool;           //!< Pointer to the queue pool (populated by user during initialization). This is pointer to shared memory, in which queue elements will be stored. CYHAL_IPC_QUEUE_POOL_ALLOC macro can be used to allocate memory for pool.
    uint32_t num_items;         //!< Maximum number of items allowed in the queue (populated by user during initialization)
    uint32_t item_size;         //!< Size of each item in the queue (populated by user during initialization)
    uint32_t curr_items;        //!< Current number of items in the queue (not expected to be modified by user)
    void *queue_head;           //!< Pointer to the queue head in circular buffer (not expected to be modified by user)
    void *queue_tail;           //!< Pointer to the queue tail in circular buffer (not expected to be modified by user)
    uint32_t triggered_events;  //!< Events, that were triggered by latest performed operation (not expected to be modified by user)
    struct cyhal_ipc_queue_s *next_queue_obj;   //!< Pointer to the next queue object (not expected to be modified by user)
}cyhal_ipc_queue_t;

/** Creates a single semaphore based on a given number.
 *
 * This function must be called by all tasks/CPUs accessing the semaphore.
 * @param[out] obj              Pointer to an IPC object. The caller must allocate the memory for this object but the
 * init function will initialize its contents.
 * @param[in] semaphore_num     The semaphore number to initialize.
 * @param[in] preemptable       Allows whether the semaphore can be preempted by another task.
 * @return The status of the init request
 */
cy_rslt_t cyhal_ipc_semaphore_init(cyhal_ipc_t *obj, uint32_t semaphore_num, bool preemptable);

/** Frees the IPC semaphore.
 *
 * This function frees the resources associated with the semaphore.
 * @param[in, out] obj          The IPC object.
 */
void cyhal_ipc_semaphore_free(cyhal_ipc_t *obj);

/** Takes/acquires a semaphore.
 *
 * If the semaphore is available, it is acquired and this function and returns.
 * This function has a timeout argument (in microseconds). If the semaphore is not available, it blocks until it
 * times out or succeeds in acquiring it.
 * @param[in] obj               The IPC object.
 * @param[in] timeout_us        Timeout in microseconds. Value 0 can be used if no timeout needed while
 * \ref CYHAL_IPC_NEVER_TIMEOUT can be used to make function block until semaphore is successfully taken.
 * @return The status of the take request
 */
cy_rslt_t cyhal_ipc_semaphore_take(cyhal_ipc_t *obj, uint32_t timeout_us);

/** Gives/releases a semaphore.
 *
 * The semaphore is released allowing other tasks waiting on the semaphore to take it.
 * @param[in] obj               The IPC object.
 * @return The status of the give request
 */
cy_rslt_t cyhal_ipc_semaphore_give(cyhal_ipc_t *obj);

/** Creates a new queue for a given IPC channel based on the given queue number and other parameters.
 *
 * This function requires \ref cyhal_ipc_queue_t (queue handle) pointer to shared memory. Some elements of cyhal_ipc_queue_t
 * structure are expected to be filled by user. One key element of the structure to be filled by user is a pointer to
 * the queue pool allocated in the shared memory.
 * Queue handle is used by other tasks/CPUs to refer to the queue. Note that this function must be called only by one
 * of the tasks/CPUs for the same IPC channel. This CPU can call the function multiple times for the same IPC
 * channel, but with a different queue number.
 * \note CYHAL_IPC_QUEUE_HANDLE_ALLOC and CYHAL_IPC_QUEUE_POOL_ALLOC macro can be used in order to allocate
 * memory for (respectively) queue handle (cyhal_ipc_queue_t) and queue pool in shared section. Please refer to
 * \ref subsection_ipc_snippet2 for initialization guidance.
 * @param[out] obj              Pointer to an IPC object. The caller must allocate the memory for this object
 * but the init function will initialize its contents.
 * @param[in] queue_handle      Queue handle. Fields channel_num, queue_num, queue_pool, num_items and item_size
 * are expected to be filled by user before initialization. Please refer to \ref subsection_ipc_snippet2 for
 * initialization guidance.
 * @return The status of the init request
 */
cy_rslt_t cyhal_ipc_queue_init(cyhal_ipc_t *obj, cyhal_ipc_queue_t *queue_handle);

/** Frees the queue.
 *
 * This operation only removes the queue handle from the list of available queues. The queue pool and the queue
 * handle allocated in the shared memory needs to be freed (if dynamically allocated) by the application.
 * @param[in, out] obj          The IPC object
 */
void cyhal_ipc_queue_free(cyhal_ipc_t *obj);

/** Gets a handle pointer for a given IPC channel and queue number.
 *
 * This function should be called by other tasks/CPUs that have not called the initialization function.
 * @param[out] obj              The IPC object handle.
 * @param[in] channel_num       IPC channel to use for the queue messaging.
 * @param[in] queue_num         Queue number.
 * @return The status of the get handle request
 */
cy_rslt_t cyhal_ipc_queue_get_handle(cyhal_ipc_t *obj, uint32_t channel_num, uint32_t queue_num);

/** Registers a callback to be executed when certain events occur.
 *
 * @param[in] obj               The IPC object.
 * @param[in] callback          The callback handler which will be invoked when an event triggers.
 * @param[in] callback_arg      Generic argument that will be provided to the callback when called.
 */
void cyhal_ipc_queue_register_callback(cyhal_ipc_t *obj, cyhal_ipc_event_callback_t callback, void *callback_arg);

/** Enables which events trigger the callback execution.
 *
 * It can trigger when a new item is written to the queue, read from the queue, when the queue becomes full,
 * when the queue becomes empty or when there is a reset. Note that these events might execute callbacks
 * associated to all queues that belong to an IPC channel. When defining the ISR priority, the last call to
 * this function overwrites the priority for all queue callbacks registered to the same IPC channel.
 * @param[in] obj               The IPC object
 * @param[in] event             The IPC event type
 * @param[in] intr_priority     The priority for NVIC interrupt events
 * @param[in] enable            True to turn on specified events, False to turn off
 */
void cyhal_ipc_queue_enable_event(cyhal_ipc_t *obj, cyhal_ipc_event_t event, uint8_t intr_priority, bool enable);

/** Adds one item to the queue.
 *
 * This function can be called by any task/CPU. This function has a timeout argument (in microseconds).
 * If the queue is full, it stays there until it times out or the queue is no longer full.
 * This function can be blocking or non-blocking (timeout set to ZERO).
 * @param[in] obj               The IPC object
 * @param[in] msg               Location of message queue item
 * @param[in] timeout_us        Timeout in microseconds. Value 0 can be used if no timeout needed while
 * \ref CYHAL_IPC_NEVER_TIMEOUT can be used to make function block until element is successfully put into the queue.
 * @return The status of the put request
 */
cy_rslt_t cyhal_ipc_queue_put(cyhal_ipc_t *obj, void *msg, uint32_t timeout_us);

/** Removes one item from the queue.
 *
 * This function can be called by any task/CPU. This function has a timeout argument (in microseconds).
 * If the queue is empty, it stays there until it times out or the queue receives a new item.
 * This function can be blocking or non-blocking (timeout set to ZERO).
 * @param[in] obj               The IPC object
 * @param[out] msg              Location of message queue item
 * @param[in] timeout_us        Timeout in microseconds. Value 0 can be used if no timeout needed while
 * \ref CYHAL_IPC_NEVER_TIMEOUT can be used to make function block until element is successfully taken from the queue.
 * @return The status of the get request
 */
cy_rslt_t cyhal_ipc_queue_get(cyhal_ipc_t *obj, void *msg, uint32_t timeout_us);

/** Returns how many items are in the queue.
 *
 * This function can be called by any task/CPU.
 * @param[in] obj               The IPC object
 * @return Number of items in the queue
 */
uint32_t cyhal_ipc_queue_count(cyhal_ipc_t *obj);

/** Clear all the items in the queue.
 *
 * This function can be called by the any task/CPU.
 * @param[in] obj               The IPC object
 * @return The status of the reset request
 */
cy_rslt_t cyhal_ipc_queue_reset(cyhal_ipc_t *obj);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_IPC_IMPL_HEADER
#include CYHAL_IPC_IMPL_HEADER
#endif /* CYHAL_IPC_IMPL_HEADER */

/** \} group_hal_ipc */
