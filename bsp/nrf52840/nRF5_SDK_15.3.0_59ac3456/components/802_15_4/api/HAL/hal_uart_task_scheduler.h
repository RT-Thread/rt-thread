/**
 * Copyright (c) 2016 - 2019 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
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
#ifndef HAL_UART_TASK_SCHEDULER_H_INCLUDED
#define HAL_UART_TASK_SCHEDULER_H_INCLUDED

#include <stdint.h>
#include "hal_atomic.h"
#include "hal_task_scheduler.h"
#include "sys_utils.h"

/**
 * @defgroup hal_uart_task_scheduler HAL UART Task Scheduler
 * @ingroup hal_15_4
 * @{
 * @brief Module to declare HAL UART Task Scheduler interface
 */

/**@brief Identifiers for registered UART event handlers.
 *
 * @details enumeration with identifiers of registered UART event handlers.
 * UART handlers will be called from the HAL_UART task. */
typedef enum
{
    HAL_UART_RX_TASK_ID,
    HAL_UART_TX_TASK_ID,
    HAL_UART_ERROR_TASK_ID,
    HAL_UART_TASKS_AMOUNT,
} hal_uart_task_id_t;

/**@brief Prototype of a UART task handler.
 *
 * @details Handler which will be called from HAL_UART task. */
typedef void (* hal_uart_task_handler_t)(uint32_t channel);

void hal_uart_rx_handler(uint32_t channel);
void hal_uart_tx_handler(uint32_t channel);
void hal_uart_error_handler(uint32_t channel);

/**@brief UART channels.
 *
 * @details Array which includes event id for every channel it happened. */
extern volatile uint16_t g_hal_uart_modules_tasks[CONFIG_HAL_UART_CHANNELS];


/**@brief Notifies HAL task scheduler to add an UART task for execution.
 *
 * @details The function sets a marker for the UART event task for execution.
 * And sets this marker for a channel where event happened.
 *
 * @param[in] channel event channel.
 * @param[in] hal_uart_task_id HAL task identificator. */
static inline void hal_uart_task_post(uint32_t channel,
                                      uint8_t hal_uart_task_id)
{
    atomic_t atomic = 0;

    hal_atomic_start(&atomic);
    g_hal_uart_modules_tasks[channel] |= BIT(hal_uart_task_id);
    hal_atomic_end(&atomic);

    hal_task_post(HAL_UART_TASK_ID);
}

/** @} */

#endif /* HAL_UART_TASK_SCHEDULER_H_INCLUDED */
