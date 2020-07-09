/**
 * Copyright (c) 2016 - 2017 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
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
#ifndef HAL_TASK_H_INCLUDED
#define HAL_TASK_H_INCLUDED

#include <stdint.h>
#include "hal_atomic.h"
#include "sys_utils.h"
#include "sys_task_scheduler.h"

/**@brief Identificators for registered HAL handlers.
 *
 * @details enumeration with identificators of registered HAL handlers.
 * HAL handlers will be called from the HAL task.
 */
typedef enum
{
    HAL_TIMER_TASK_ID,
    HAL_UART_TASK_ID,
    HAL_TIMER_CRITICAL_MANUAL_TASK,
    HAL_TASKS_AMOUNT,
} hal_task_id_t;


/**@brief Prototype of a HAL task handler.
 *
 * @details Handler which will be called from HAL task.
 */
typedef void (* hal_task_handler_t)(void);


void hal_task_handler(void);
void hal_timer_task_handler(void);
void hal_uart_task_handler(void);
void hal_timer_critical_manual_handler(void);

/**@brief Pending HAL tasks.
 *
 * @details Variable which includes markers of pending HAL tasks.
 */
extern volatile uint_fast16_t g_hal_tasks;


/**@brief       Notify task scheduler to add a HAL task for execution.
 *
 * @details     The function sets a marker for the HAL task for execution.
 *
 * @param[in]   hal_task_id  HAL task identifier (see \ref hal_task_id_t enumeration).
 */
static inline void hal_task_post(hal_task_id_t hal_task_id)
{
    atomic_t atomic = 0;

    hal_atomic_start(&atomic);
    g_hal_tasks |= BIT(hal_task_id);
    hal_atomic_end(&atomic);
    
    sys_task_post(HAL_TASK_ID);
}

/**@brief       Removes a task from pending list in HAL task scheduler.
 *
 * @details     The function removes a marker from the HAL execution list.
 *
 * @param[in]   hal_task_id  HAL task identifier (see \ref hal_task_id_t enumeration).
 */
static inline void hal_task_unpost(hal_task_id_t hal_task_id)
{
    atomic_t atomic = 0;

    hal_atomic_start(&atomic);
    g_hal_tasks &= ~BIT(hal_task_id);
    hal_atomic_end(&atomic);
}

#endif // HAL_TASK_H_INCLUDED
