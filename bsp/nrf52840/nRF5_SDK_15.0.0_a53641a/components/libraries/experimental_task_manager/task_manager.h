/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__


/**
* @defgroup task_manager Task manager (Cooperative Scheduler)
* @{
* @ingroup app_common
* @brief Functions for managing tasks
*/

#include <stdbool.h>
#include <stdint.h>

#include "nrf.h"
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Main function of the task. */
typedef void (* task_main_t)(void * p_context);

/**@brief Task ID */
typedef uint8_t task_id_t;

/**@brief Invalid task ID */
#define TASK_ID_INVALID ((task_id_t)(-1))

/**@brief Start task manager.
 *
 * @details This function starts the task manager and configures given function as idle task.
 *          This function never returns.
 *
 * @param[in]   idle_task           Main function of the task scheduled when no other tasks could be run.
 * @param[in]   p_idle_task_context Context passed to idle task.
 */
void task_manager_start(task_main_t idle_task, void * p_idle_task_context);

/**@brief Create new task.
 *
 * @param[in]   task        Function which become main procedure of new task.
 * @param[in]   p_task_name Task name.
 * @param[in]   p_context   Context passed to task procedure.
 *
 * @return      ID of the task on success, otherwise TASK_ID_INVALID.
 */
task_id_t task_create(task_main_t task, char const * p_task_name, void * p_context);

/**@brief Yield CPU to other tasks.
 */
void task_yield(void);

/**@brief Complete current task.
 *
 * Task stack returns to the pool of available stacks.
 */
void task_exit(void);

/**@brief Wait for events. Set events are cleared after this function returns.
 *
 * @param[in] evt_mask Mask of events to wait
 *
 * @return Mask with set events (can be a subset of evt_mask).
 */
uint32_t task_events_wait(uint32_t evt_mask);

/**@brief Set events for given task.
 *
 * @param[in]  task_id  Id of the task which shall receive events.
 * @param[in]  evt_mask Events for the task.
 *
 */
void task_events_set(task_id_t task_id, uint32_t evt_mask);

/**@brief Returns maximum depth of task stack.
 *
 * @param[in] task_id Id of the task (use @ref TASK_ID_INVALID for current task).
 * @return Number of bytes ever used on task stack.
 */
uint32_t task_stack_max_usage_get(task_id_t task_id);

/**@brief Returns ID of currently running task.
 *
 * @return ID of active task.
 */
task_id_t task_id_get(void);

/**@brief Set events for given task.
 *
 * @param[in]   task_id  Id of the task which name will be returned.
 * @return      Task name
 *
 */
char const * task_name_get(task_id_t task_id);


#ifdef __cplusplus
}
#endif

#endif /* __TASK_MANAGER_H__ */
/** @} */
