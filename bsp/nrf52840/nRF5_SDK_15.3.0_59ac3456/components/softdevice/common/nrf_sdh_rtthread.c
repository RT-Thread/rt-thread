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

#include "nrf_sdh_rtthread.h"
#include "nrf_sdh.h"
#include "app_error.h"
/* Group of RT-Rthread-related includes. */
#include <rthw.h>
#include <rtthread.h>

#define NRF_LOG_MODULE_NAME nrf_sdh_rtthread
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
NRF_LOG_MODULE_REGISTER();

#define USE_SEMAPHORE_FLAG 1
#define NRF_BLE_RTTHREAD_SDH_TASK_STACK 512

#if USE_SEMAPHORE_FLAG
static rt_sem_t sd_evt_sem=RT_NULL;
#endif
static nrf_sdh_rtthread_task_hook_t m_task_hook=RT_NULL;        //!< A hook function run by the SoftDevice task before entering its loop.
static rt_thread_t   m_softdevice_task =RT_NULL;;  //!< Reference to SoftDevice RT-Rthread task.
void SD_EVT_IRQHandler(void)
{ 
#if USE_SEMAPHORE_FLAG
      rt_sem_release(sd_evt_sem);
#else
      rt_thread_resume(m_softdevice_task);
#endif
}


/* This function gets events from the SoftDevice and processes them. */
static void softdevice_task(void * pvParameter)
{
//    NRF_LOG_INFO("Enter softdevice_task.");

    if (m_task_hook != NULL)
    {
        m_task_hook(pvParameter);
    }
    while (true)
    {       
#if USE_SEMAPHORE_FLAG
       rt_sem_take(sd_evt_sem, RT_WAITING_FOREVER);
#endif
        nrf_sdh_evts_poll(); // Let the handlers run first, in case the EVENT occured before creating this task.
#if !USE_SEMAPHORE_FLAG
        rt_thread_suspend(m_softdevice_task);
        rt_schedule();
#endif
    }
}


void nrf_sdh_rtthread_init(nrf_sdh_rtthread_task_hook_t hook_fn, void * p_context)
{
    rt_kprintf("Creating a SoftDevice task.");
    m_task_hook = hook_fn;

#if USE_SEMAPHORE_FLAG
    sd_evt_sem = rt_sem_create("sdsem", 0, RT_IPC_FLAG_FIFO);

    if (!sd_evt_sem)
    {
        rt_kprintf("sd_evt_sem create failure\n");
        APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
    }
#endif
    m_softdevice_task = rt_thread_create("BLE", softdevice_task, RT_NULL, NRF_BLE_RTTHREAD_SDH_TASK_STACK, 2, 10);

    if (m_softdevice_task != RT_NULL)
    {
        rt_thread_startup(m_softdevice_task);
    }
    else
    {
        rt_kprintf("SoftDevice task not created.");
        APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
    }

}
