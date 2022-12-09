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

/*
 * hal_fc_event.c
 *
 *  Created on: Feb 19, 2021
 *      Author: qlblue
 */

//#include "pmsis/implem/drivers/fc_event/fc_event.h"
#include "hal_fc_event.h"
//#include "pmsis/implem/hal/hal.h"
#include "hal_soc_eu_periph.h"
//#include "pmsis/implem/drivers/pmsis_it.h"
//#include "FreeRTOS.h"
//#include "semphr.h"
#include "rtthread.h"

#define unuse_freertos_in_event
/*******************************************************************************
 * Variables, macros, structures,... definition
 ******************************************************************************/

/*******************************************************************************
 * Function definition
 ******************************************************************************/

static void fc_event_null_event(void *arg);

static volatile pi_fc_event_handler_t fc_event_handlers[SOC_EU_NB_FC_EVENTS];
//static SemaphoreHandle_t  fc_event_semaphores[SOC_EU_NB_FC_EVENTS];

static void fc_event_null_event(void *arg)
{
	return;
}

void pi_fc_event_handler_init(uint32_t fc_event_irq)
{
	/* TODO: fix this mess, that should be 8 32-bit writes */
	/* open the mask for fc_soc_event irq */
	for (int i = 0; i < SOC_EU_NB_FC_EVENTS; i++) {
		pi_fc_event_handler_clear(i);
	}
	/* NVIC_SetVector(fc_event_irq, (uint32_t)__handler_wrapper_light_fc_event_handler);*/
	//irqn_enable(fc_event_irq);
}

#if 0  
void pi_fc_event_handler_set(uint32_t event_id,
			     pi_fc_event_handler_t event_handler,
					SemaphoreHandle_t semaphoreHandle)
{
	if (event_handler != NULL) {
		fc_event_handlers[event_id] = event_handler;
	}
	if (semaphoreHandle != NULL) {
		fc_event_semaphores[event_id] = semaphoreHandle;
	}
}
#endif 

void user_pi_fc_event_handler_set(uint32_t event_id,
			     pi_fc_event_handler_t event_handler)
{
	if (event_handler != NULL) {
		fc_event_handlers[event_id] = event_handler;
	}
}

void pi_fc_event_handler_clear(uint32_t event_id)
{
	fc_event_handlers[event_id] = (pi_fc_event_handler_t)fc_event_null_event;
	//fc_event_semaphores[event_id] = NULL;// remove  from  project 
}

/* TODO: Use Eric's FIRQ ABI */
void fc_soc_event_handler1 (uint32_t mcause)
{
	uint32_t val = 0;
	//static BaseType_t xHigherPriorityTaskWoken;

	uint32_t event_id = *(uint32_t*)(0x1a106090); // new event fifo address

	event_id &= 0xFF;

	/* redirect to handler with jump table */
	if (fc_event_handlers[event_id] != NULL) {
		fc_event_handlers[event_id]((void *)event_id);
	}
	#if 0
	if (fc_event_semaphores[event_id] != NULL) {
		/* Unblock the task by releasing the semaphore. */
		#ifdef  unuse_freertos_in_event
		 SemaphoreHandle_t xSemaphoreHandle = fc_event_semaphores[event_id];
		 xSemaphoreGiveFromISR( xSemaphoreHandle, &xHigherPriorityTaskWoken );
		 //rt_schedule();
		 //portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
		 //__asm volatile( "ecall" );
		#endif 
	}
	#endif
}
