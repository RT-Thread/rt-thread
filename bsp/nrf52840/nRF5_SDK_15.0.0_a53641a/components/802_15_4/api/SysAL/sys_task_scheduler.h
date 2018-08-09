/**
 * Copyright (c) 2016 - 2018 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 * 
 * All Rights Reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
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
#ifndef SYS_TASK_SCHEDULER_H_INCLUDED
#define SYS_TASK_SCHEDULER_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include "sys_utils.h"
#include "hal_atomic.h"
#include "sys_events.h"

/** @file
 * @defgroup sys_task_scheduler Task scheduler
 * @ingroup sys_15_4
 * @{
 * @brief Module for task scheduling.
 */

/**@brief Identificators for registered handlers.
 *
 * Handlers will be called from the task scheduler.
 */
typedef enum
{
    PHY_TASK_ID,
    HAL_TASK_ID,
#if (CONFIG_HIGHEST_LAYER_PHY == 0)
    MAC_TASK_ID,
#endif
    APP_TASK_ID,
    SYS_TASK_ID,
    SYS_TASKS_AMOUNT
} sys_task_ids_t;

/**@brief Prototype of a task handler.
 *
 * @details Handler which will be called by the scheduler.
 */
typedef void (* sys_task_handler_t)(void);

/**@brief Pending tasks.
 *
 * @details Variable which includes markers of pending tasks.
 */
extern volatile uint_fast16_t g_tasks;

/**@brief       Notify task scheduler to add a task for execution.
 *
 * @details     The function sets a marker for the task for execution.
 *              The task handler implements a tree architecture.
 *              Task handler of each layer includes handlers of the layer's components.
 *
 * @param[in]   task_id  Task identificator.
 */
static inline void sys_task_post(sys_task_ids_t task_id)
{
    atomic_t atomic = 0;

    hal_atomic_start(&atomic);
    g_tasks |= BIT(task_id);
#if (CONFIG_USE_SYS_TASK_NOTIFIER == 1)
    sys_event_post(SYS_EVENT_NEW_TASK, NULL);
#endif
    hal_atomic_end(&atomic);
}

/**@brief Returns true, if there are any event flags awaiting in the system scheduler.
 */
static inline bool sys_tasks_pending(void)
{
    return g_tasks != 0;
}

/**@brief Handle tasks in the main function.
 *
 * @details   Handle tasks in the main function.
 */
void sys_task_run(void);

/** @} */

#endif // SYS_TASK_SCHEDULER_H_INCLUDED
