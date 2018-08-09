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

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_SDH)

#include "nrf_sdh.h"

#include <stdint.h>

#include "nrf_sdm.h"
#include "nrf_nvic.h"
#include "sdk_config.h"
#include "app_error.h"
#include "app_util_platform.h"


#define NRF_LOG_MODULE_NAME nrf_sdh
#if NRF_SDH_LOG_ENABLED
    #define NRF_LOG_LEVEL       NRF_SDH_LOG_LEVEL
    #define NRF_LOG_INFO_COLOR  NRF_SDH_INFO_COLOR
    #define NRF_LOG_DEBUG_COLOR NRF_SDH_DEBUG_COLOR
#else
    #define NRF_LOG_LEVEL       0
#endif // NRF_SDH_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


// Validate configuration options.

#if (NRF_SDH_DISPATCH_MODEL == NRF_SDH_DISPATCH_MODEL_APPSH)
    #if (!APP_SCHEDULER_ENABLED)
        #error app_scheduler is required when NRF_SDH_DISPATCH_MODEL is set to NRF_SDH_DISPATCH_MODEL_APPSH
    #endif
    #include "app_scheduler.h"
#endif

#if (   (NRF_SDH_CLOCK_LF_SRC      == NRF_CLOCK_LF_SRC_RC)          \
     && (NRF_SDH_CLOCK_LF_ACCURACY != NRF_CLOCK_LF_ACCURACY_500_PPM))
    #warning Please select NRF_CLOCK_LF_ACCURACY_500_PPM when using NRF_CLOCK_LF_SRC_RC
#endif


// Create section "sdh_req_observers".
NRF_SECTION_SET_DEF(sdh_req_observers, nrf_sdh_req_observer_t, NRF_SDH_REQ_OBSERVER_PRIO_LEVELS);

// Create section "sdh_state_observers".
NRF_SECTION_SET_DEF(sdh_state_observers, nrf_sdh_state_observer_t, NRF_SDH_STATE_OBSERVER_PRIO_LEVELS);

// Create section "sdh_stack_observers".
NRF_SECTION_SET_DEF(sdh_stack_observers, nrf_sdh_stack_observer_t, NRF_SDH_STACK_OBSERVER_PRIO_LEVELS);


static bool m_nrf_sdh_enabled;   /**< Variable to indicate whether the SoftDevice is enabled. */
static bool m_nrf_sdh_suspended; /**< Variable to indicate whether this module is suspended. */
static bool m_nrf_sdh_continue;  /**< Variable to indicate whether enable/disable process was started. */


/**@brief   Function for notifying request observers.
 *
 * @param[in]   evt     Type of request event.
 */
static ret_code_t sdh_request_observer_notify(nrf_sdh_req_evt_t req)
{
    nrf_section_iter_t iter;

    NRF_LOG_DEBUG("State request: 0x%08X", req);

    for (nrf_section_iter_init(&iter, &sdh_req_observers);
         nrf_section_iter_get(&iter) != NULL;
         nrf_section_iter_next(&iter))
    {
        nrf_sdh_req_observer_t    * p_observer;
        nrf_sdh_req_evt_handler_t   handler;

        p_observer = (nrf_sdh_req_observer_t *) nrf_section_iter_get(&iter);
        handler    = p_observer->handler;

        if (handler(req, p_observer->p_context))
        {
            NRF_LOG_DEBUG("Notify observer 0x%08X => ready", p_observer);
        }
        else
        {
            // Process is stopped.
            NRF_LOG_DEBUG("Notify observer 0x%08X => blocking", p_observer);
            return NRF_ERROR_BUSY;
        }
    }
    return NRF_SUCCESS;
}


/**@brief   Function for stage request observers.
 *
 * @param[in]   evt Type of stage event.
 */
static void sdh_state_observer_notify(nrf_sdh_state_evt_t evt)
{
    nrf_section_iter_t iter;

    NRF_LOG_DEBUG("State change: 0x%08X", evt);

    for (nrf_section_iter_init(&iter, &sdh_state_observers);
         nrf_section_iter_get(&iter) != NULL;
         nrf_section_iter_next(&iter))
    {
        nrf_sdh_state_observer_t    * p_observer;
        nrf_sdh_state_evt_handler_t   handler;

        p_observer = (nrf_sdh_state_observer_t *) nrf_section_iter_get(&iter);
        handler    = p_observer->handler;

        handler(evt, p_observer->p_context);
    }
}


static void softdevices_evt_irq_enable(void)
{
#ifdef SOFTDEVICE_PRESENT
    ret_code_t ret_code = sd_nvic_EnableIRQ((IRQn_Type)SD_EVT_IRQn);
    APP_ERROR_CHECK(ret_code);
#else
    // In case of serialization, NVIC must be accessed directly.
    NVIC_EnableIRQ(SD_EVT_IRQn);
#endif
}


static void softdevice_evt_irq_disable(void)
{
#ifdef SOFTDEVICE_PRESENT
    ret_code_t ret_code = sd_nvic_DisableIRQ((IRQn_Type)SD_EVT_IRQn);
    APP_ERROR_CHECK(ret_code);
#else
    // In case of serialization, NVIC must be accessed directly.
    NVIC_DisableIRQ(SD_EVT_IRQn);
#endif
}


#ifndef S140
static void swi_interrupt_priority_workaround(void)
{
    // The priority of SoftDevice SWI SD_EVT_IRQn and RADIO_NOTIFICATION_IRQn in
    // S132 v5.0.0, S112 v5.0.0, S212 v5.0.0 and S332 v5.0.0 is set to 6.
    // Change it to APP_IRQ_PRIORITY_LOWEST (7) so that they do not preempt peripherals' interrupts.

#ifdef SOFTDEVICE_PRESENT
    ret_code_t ret_code;
    ret_code = sd_nvic_SetPriority(SD_EVT_IRQn, APP_IRQ_PRIORITY_LOWEST);
    APP_ERROR_CHECK(ret_code);
    ret_code = sd_nvic_SetPriority(RADIO_NOTIFICATION_IRQn, APP_IRQ_PRIORITY_LOWEST);
    APP_ERROR_CHECK(ret_code);
#else
    // In case of serialization, NVIC must be accessed directly.
    NVIC_SetPriority(SD_EVT_IRQn, APP_IRQ_PRIORITY_LOWEST);
    NVIC_SetPriority(RADIO_NOTIFICATION_IRQn, APP_IRQ_PRIORITY_LOWEST);
#endif
}
#endif


ret_code_t nrf_sdh_enable_request(void)
{
    ret_code_t ret_code;

    if (m_nrf_sdh_enabled)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    m_nrf_sdh_continue = true;

    // Notify observers about SoftDevice enable request.
    if (sdh_request_observer_notify(NRF_SDH_EVT_ENABLE_REQUEST) == NRF_ERROR_BUSY)
    {
        // Enable process was stopped.
        return NRF_SUCCESS;
    }

    // Notify observers about starting SoftDevice enable process.
    sdh_state_observer_notify(NRF_SDH_EVT_STATE_ENABLE_PREPARE);

    nrf_clock_lf_cfg_t const clock_lf_cfg =
    {
        .source       = NRF_SDH_CLOCK_LF_SRC,
        .rc_ctiv      = NRF_SDH_CLOCK_LF_RC_CTIV,
        .rc_temp_ctiv = NRF_SDH_CLOCK_LF_RC_TEMP_CTIV,
        .accuracy     = NRF_SDH_CLOCK_LF_ACCURACY
    };

    CRITICAL_REGION_ENTER();
#ifdef ANT_LICENSE_KEY
    ret_code = sd_softdevice_enable(&clock_lf_cfg, app_error_fault_handler, ANT_LICENSE_KEY);
#else
    ret_code = sd_softdevice_enable(&clock_lf_cfg, app_error_fault_handler);
#endif
    m_nrf_sdh_enabled = (ret_code == NRF_SUCCESS);
    CRITICAL_REGION_EXIT();

    if (ret_code != NRF_SUCCESS)
    {
        return ret_code;
    }

    m_nrf_sdh_continue  = false;
    m_nrf_sdh_suspended = false;

#ifndef S140
    // Set the interrupt priority after enabling the SoftDevice, since
    // sd_softdevice_enable() sets the SoftDevice interrupt priority.
    swi_interrupt_priority_workaround();
#endif

    // Enable event interrupt.
    // Interrupt priority has already been set by the stack.
    softdevices_evt_irq_enable();

    // Notify observers about a finished SoftDevice enable process.
    sdh_state_observer_notify(NRF_SDH_EVT_STATE_ENABLED);

    return NRF_SUCCESS;
}


ret_code_t nrf_sdh_disable_request(void)
{
    ret_code_t ret_code;

    if (!m_nrf_sdh_enabled)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    m_nrf_sdh_continue = true;

    // Notify observers about SoftDevice disable request.
    if (sdh_request_observer_notify(NRF_SDH_EVT_DISABLE_REQUEST) == NRF_ERROR_BUSY)
    {
        // Disable process was stopped.
        return NRF_SUCCESS;
    }

    // Notify observers about starting SoftDevice disable process.
    sdh_state_observer_notify(NRF_SDH_EVT_STATE_DISABLE_PREPARE);

    CRITICAL_REGION_ENTER();
    ret_code          = sd_softdevice_disable();
    m_nrf_sdh_enabled = false;
    CRITICAL_REGION_EXIT();

    if (ret_code != NRF_SUCCESS)
    {
        return ret_code;
    }

    m_nrf_sdh_continue = false;

    softdevice_evt_irq_disable();

    // Notify observers about a finished SoftDevice enable process.
    sdh_state_observer_notify(NRF_SDH_EVT_STATE_DISABLED);

    return NRF_SUCCESS;
}


ret_code_t nrf_sdh_request_continue(void)
{
    if (!m_nrf_sdh_continue)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (m_nrf_sdh_enabled)
    {
        return nrf_sdh_disable_request();
    }
    else
    {
        return nrf_sdh_enable_request();
    }
}


bool nrf_sdh_is_enabled(void)
{
    return m_nrf_sdh_enabled;
}


void nrf_sdh_suspend(void)
{
    if (!m_nrf_sdh_enabled)
    {
        return;
    }

    softdevice_evt_irq_disable();
    m_nrf_sdh_suspended = true;
}


void nrf_sdh_resume(void)
{
    if ((!m_nrf_sdh_suspended) || (!m_nrf_sdh_enabled))
    {
        return;
    }

    // Force calling ISR again to make sure that events not previously pulled have been processed.
#ifdef SOFTDEVICE_PRESENT
    ret_code_t ret_code = sd_nvic_SetPendingIRQ((IRQn_Type)SD_EVT_IRQn);
    APP_ERROR_CHECK(ret_code);
#else
    NVIC_SetPendingIRQ((IRQn_Type)SD_EVT_IRQn);
#endif

    softdevices_evt_irq_enable();

    m_nrf_sdh_suspended = false;
}


bool nrf_sdh_is_suspended(void)
{
    return (!m_nrf_sdh_enabled) || (m_nrf_sdh_suspended);
}


void nrf_sdh_evts_poll(void)
{
    nrf_section_iter_t iter;

    // Notify observers about pending SoftDevice event.
    for (nrf_section_iter_init(&iter, &sdh_stack_observers);
         nrf_section_iter_get(&iter) != NULL;
         nrf_section_iter_next(&iter))
    {
        nrf_sdh_stack_observer_t    * p_observer;
        nrf_sdh_stack_evt_handler_t   handler;

        p_observer = (nrf_sdh_stack_observer_t *) nrf_section_iter_get(&iter);
        handler    = p_observer->handler;

        handler(p_observer->p_context);
    }
}


#if (NRF_SDH_DISPATCH_MODEL == NRF_SDH_DISPATCH_MODEL_INTERRUPT)

void SD_EVT_IRQHandler(void)
{
    nrf_sdh_evts_poll();
}

#elif (NRF_SDH_DISPATCH_MODEL == NRF_SDH_DISPATCH_MODEL_APPSH)

/**@brief   Function for polling SoftDevice events.
 *
 * @note    This function is compatible with @ref app_sched_event_handler_t.
 *
 * @param[in]   p_event_data Pointer to the event data.
 * @param[in]   event_size   Size of the event data.
 */
static void appsh_events_poll(void * p_event_data, uint16_t event_size)
{
    UNUSED_PARAMETER(p_event_data);
    UNUSED_PARAMETER(event_size);

    nrf_sdh_evts_poll();
}


void SD_EVT_IRQHandler(void)
{
    ret_code_t ret_code = app_sched_event_put(NULL, 0, appsh_events_poll);
    APP_ERROR_CHECK(ret_code);
}

#elif (NRF_SDH_DISPATCH_MODEL == NRF_SDH_DISPATCH_MODEL_POLLING)

#else

#error "Unknown SoftDevice handler dispatch model."

#endif // NRF_SDH_DISPATCH_MODEL

#endif // NRF_MODULE_ENABLED(NRF_SDH)
