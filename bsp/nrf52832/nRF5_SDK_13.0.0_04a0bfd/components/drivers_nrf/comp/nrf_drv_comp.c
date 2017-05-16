/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(COMP)
#include "nrf_drv_comp.h"

#include "nrf_assert.h"
#include "nrf_error.h"
#include "nrf_soc.h"
#include "nrf_drv_common.h"
#include "app_util_platform.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define NRF_LOG_MODULE_NAME "COMP"

#if COMP_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       COMP_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  COMP_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR COMP_CONFIG_DEBUG_COLOR
#define EVT_TO_STR(event)   (event == NRF_COMP_EVENT_READY ? "NRF_COMP_EVENT_READY" :                   \
                            (event == NRF_COMP_EVENT_DOWN ? "NRF_COMP_EVENT_DOWN" :                     \
                            (event == NRF_COMP_EVENT_UP ? "NRF_COMP_EVENT_UP" :                         \
                            (event == NRF_COMP_EVENT_CROSS ? "NRF_COMP_EVENT_CROSS" : "UNKNOWN ERROR"))))
#else //COMP_CONFIG_LOG_ENABLED
#define EVT_TO_STR(event)   ""
#define NRF_LOG_LEVEL       0
#endif //COMP_CONFIG_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"



static comp_events_handler_t     m_comp_events_handler = NULL;
static nrf_drv_state_t           m_state = NRF_DRV_STATE_UNINITIALIZED;

static const nrf_drv_comp_config_t m_default_config = NRF_DRV_COMP_DEFAULT_CONFIG(NRF_COMP_INPUT_0);

static void comp_execute_handler(nrf_comp_event_t event, uint32_t event_mask)
{
    if ( nrf_comp_event_check(event) && nrf_comp_int_enable_check(event_mask) )
    {
        nrf_comp_event_clear(event);
        NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(event));

        m_comp_events_handler(event);
    }
}

#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    #define IRQ_HANDLER_NAME   irq_handler_for_comp
    #define IRQ_HANDLER        static void IRQ_HANDLER_NAME(void)

    IRQ_HANDLER;
#else
    #define IRQ_HANDLER void COMP_LPCOMP_IRQHandler(void)
#endif // NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)

IRQ_HANDLER
{
    comp_execute_handler(NRF_COMP_EVENT_READY, COMP_INTENSET_READY_Msk);
    comp_execute_handler(NRF_COMP_EVENT_DOWN, COMP_INTENSET_DOWN_Msk);
    comp_execute_handler(NRF_COMP_EVENT_UP, COMP_INTENSET_UP_Msk);
    comp_execute_handler(NRF_COMP_EVENT_CROSS, COMP_INTENSET_CROSS_Msk);
}


ret_code_t nrf_drv_comp_init(const nrf_drv_comp_config_t * p_config,
                             comp_events_handler_t   event_handler)
{
    ret_code_t err_code;

    if (m_state != NRF_DRV_STATE_UNINITIALIZED)
    { // COMP driver is already initialized
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    if (p_config == NULL)
    {
        p_config = &m_default_config;
    }

#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    if (nrf_drv_common_per_res_acquire(NRF_COMP, IRQ_HANDLER_NAME) != NRF_SUCCESS)
    {
        err_code = NRF_ERROR_BUSY;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
#endif

    nrf_comp_task_trigger(NRF_COMP_TASK_STOP);
    nrf_comp_enable();

    // Clear events to be sure there are no leftovers.
    nrf_comp_event_clear(NRF_COMP_EVENT_READY);
    nrf_comp_event_clear(NRF_COMP_EVENT_DOWN);
    nrf_comp_event_clear(NRF_COMP_EVENT_UP);
    nrf_comp_event_clear(NRF_COMP_EVENT_CROSS);

    nrf_comp_ref_set(p_config->reference);

    //If external source is chosen, write to appropriate register.
    if (p_config->reference == COMP_REFSEL_REFSEL_ARef)
    {
        nrf_comp_ext_ref_set(p_config->ext_ref);
    }

    nrf_comp_th_set(p_config->threshold);
    nrf_comp_main_mode_set(p_config->main_mode);
    nrf_comp_speed_mode_set(p_config->speed_mode);
    nrf_comp_hysteresis_set(p_config->hyst);
    nrf_comp_isource_set(p_config->isource);
    nrf_comp_shorts_disable(NRF_DRV_COMP_SHORT_STOP_AFTER_CROSS_EVT | NRF_DRV_COMP_SHORT_STOP_AFTER_UP_EVT |
                            NRF_DRV_COMP_SHORT_STOP_AFTER_DOWN_EVT);
    nrf_comp_int_disable(COMP_INTENCLR_CROSS_Msk | COMP_INTENCLR_UP_Msk |
                         COMP_INTENCLR_DOWN_Msk | COMP_INTENCLR_READY_Msk);

    if (event_handler)
    {
        m_comp_events_handler = event_handler;
    }
    else
    {
        err_code = NRF_ERROR_INVALID_PARAM;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    nrf_comp_input_select(p_config->input);

    nrf_drv_common_irq_enable(COMP_LPCOMP_IRQn, p_config->interrupt_priority);

    m_state = NRF_DRV_STATE_INITIALIZED;

    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}


void nrf_drv_comp_uninit(void)
{
    ASSERT(m_state != NRF_DRV_STATE_UNINITIALIZED);
    nrf_drv_common_irq_disable(COMP_LPCOMP_IRQn);
    nrf_comp_disable();
#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    nrf_drv_common_per_res_release(NRF_COMP);
#endif
    m_state = NRF_DRV_STATE_UNINITIALIZED;
    m_comp_events_handler = NULL;
    NRF_LOG_INFO("Uninitialized.\r\n");
}

void nrf_drv_comp_pin_select(nrf_comp_input_t psel)
{
    bool comp_enable_state = nrf_comp_enable_check();
    nrf_comp_task_trigger(NRF_COMP_TASK_STOP);
    if (m_state == NRF_DRV_STATE_POWERED_ON)
    {
        m_state = NRF_DRV_STATE_INITIALIZED;
    }
    nrf_comp_disable();
    nrf_comp_input_select(psel);
    if (comp_enable_state == true)
    {
        nrf_comp_enable();
    }
}

void nrf_drv_comp_start(uint32_t comp_int_mask, uint32_t comp_shorts_mask)
{
    ASSERT(m_state == NRF_DRV_STATE_INITIALIZED);
    nrf_comp_int_enable(comp_int_mask);
    nrf_comp_shorts_enable(comp_shorts_mask);
    nrf_comp_task_trigger(NRF_COMP_TASK_START);
    m_state = NRF_DRV_STATE_POWERED_ON;
    NRF_LOG_INFO("Enabled.\r\n");
}

void nrf_drv_comp_stop(void)
{
    ASSERT(m_state == NRF_DRV_STATE_POWERED_ON);
    nrf_comp_shorts_disable(UINT32_MAX);
    nrf_comp_int_disable(UINT32_MAX);
    nrf_comp_task_trigger(NRF_COMP_TASK_STOP);
    m_state = NRF_DRV_STATE_INITIALIZED;
    NRF_LOG_INFO("Disabled.\r\n");
}

uint32_t nrf_drv_comp_sample()
{
    ASSERT(m_state == NRF_DRV_STATE_POWERED_ON);
    nrf_comp_task_trigger(NRF_COMP_TASK_SAMPLE);
    return nrf_comp_result_get();
}
#endif //NRF_MODULE_ENABLED(COMP)
