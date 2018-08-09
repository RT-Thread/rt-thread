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

#include "nrf_sdh_freertos.h"
#include "nrf_sdh.h"

/* Group of FreeRTOS-related includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define NRF_LOG_MODULE_NAME nrf_sdh_freertos
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define NRF_BLE_FREERTOS_SDH_TASK_STACK 256


static TaskHandle_t                 m_softdevice_task;  //!< Reference to SoftDevice FreeRTOS task.
static nrf_sdh_freertos_task_hook_t m_task_hook;        //!< A hook function run by the SoftDevice task before entering its loop.


void SD_EVT_IRQHandler(void)
{
     BaseType_t xYieldRequired;

     xYieldRequired = xTaskResumeFromISR( m_softdevice_task );

     if( xYieldRequired == pdTRUE )
     {
         portYIELD_FROM_ISR(xYieldRequired);
     }
}


/* This function gets events from the SoftDevice and processes them. */
static void softdevice_task(void * pvParameter)
{
    NRF_LOG_DEBUG("Enter softdevice_task.");

    if (m_task_hook != NULL)
    {
        m_task_hook(pvParameter);
    }

    while (true)
    {
        nrf_sdh_evts_poll(); // Let the handlers run first, in case the EVENT occured before creating this task.
        vTaskSuspend(NULL);
    }
}


void nrf_sdh_freertos_init(nrf_sdh_freertos_task_hook_t hook_fn, void * p_context)
{
    NRF_LOG_DEBUG("Creating a SoftDevice task.");

    m_task_hook = hook_fn;

    BaseType_t xReturned = xTaskCreate(softdevice_task,
                                       "BLE",
                                       NRF_BLE_FREERTOS_SDH_TASK_STACK,
                                       p_context,
                                       2,
                                       &m_softdevice_task);
    if (xReturned != pdPASS)
    {
        NRF_LOG_ERROR("SoftDevice task not created.");
        APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
    }
}
