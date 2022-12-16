/*
 * Copyright 2020 GreenWaves Technologies
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
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef HAL_INCLUDE_HAL_FC_EVENT_H_
#define HAL_INCLUDE_HAL_FC_EVENT_H_

#include "core-v-mcu-pmsis.h"
#ifdef PKG_USING_FREERTOS_WRAPPER
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>
#endif 
/*!
 * @addtogroup FC_EventHandler
 * @{
 */

/*******************************************************************************
 * Variables, macros, structures,... definitions
 ******************************************************************************/

/*******************************************************************************
 * APIs
 ******************************************************************************/

#define NB_SOC_EVENTS    ( SOC_EU_NB_FC_EVENTS )

typedef void (*pi_fc_event_handler_t)(void* arg);

void pi_fc_event_handler_init(uint32_t fc_event_irq);

/*!
 * @brief FC event handler.
 *
 * This function pops an event and executes the handler corresponding to the event.
 */
void fc_soc_event_handler(void);
#ifdef PKG_USING_FREERTOS_WRAPPER
void pi_fc_event_handler_set(uint32_t event_id, pi_fc_event_handler_t event_handler, SemaphoreHandle_t semaphoreHandle);//This function based on  freertos 
#endif
void user_pi_fc_event_handler_set(uint32_t event_id,pi_fc_event_handler_t event_handler);

void pi_fc_event_handler_clear(uint32_t event_id);

void clear_fc_event_handler(uint32_t event_id);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* @} */


#endif /* HAL_INCLUDE_HAL_FC_EVENT_H_ */
