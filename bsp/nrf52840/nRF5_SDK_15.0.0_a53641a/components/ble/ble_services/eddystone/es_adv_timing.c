/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#include "app_timer.h"
#include "es_adv_timing.h"
#include "es_adv_timing_resolver.h"
#include "es_slot.h"


APP_TIMER_DEF(m_es_adv_interval_timer);                         //!< Timer for advertising the set of slots.
APP_TIMER_DEF(m_es_slot_timer);                                 //!< Timer for advertising individual slots.

static nrf_ble_escs_adv_interval_t     m_current_adv_interval;  //!< Current advertisement interval.
static es_adv_timing_callback_t        m_timing_mgr_callback;   //!< Registered callback.
static es_adv_timing_resolver_result_t m_adv_timing_result;     //!< Current advertising timing result.
static bool                            m_non_conn_adv_active;   //!< Is the beacon advertising non-conn advertisements?

/**@brief Function for invoking registered callback.
 *
 * @param[in] p_evt Event to issue to callback.
 */
static void invoke_callback(const es_adv_timing_evt_t * p_evt)
{
    if (m_timing_mgr_callback != NULL && m_non_conn_adv_active)
    {
        m_timing_mgr_callback(p_evt);
    }
}


#if APP_CONFIG_TLM_ADV_INTERLEAVE_RATIO > 1
static bool frame_to_adv_is_tlm(const es_adv_timing_evt_t * p_evt)
{
    const es_slot_reg_t * p_reg = es_slot_get_registry();

    return (p_reg->tlm_configured &&
            (p_evt->slot_no == p_reg->tlm_slot || p_evt->evt_id == ES_ADV_TIMING_EVT_ADV_ETLM));
}


static bool tlm_should_be_advertised(uint32_t adv_event_cnt)
{
    return (adv_event_cnt % APP_CONFIG_TLM_ADV_INTERLEAVE_RATIO) == 0;
}
#endif // APP_CONFIG_TLM_ADV_INTERLEAVE_RATIO > 1


/**@brief Timeout handler for the advertisement slot timer. */
static void adv_slot_timeout(void * p_context)
{

    ret_code_t err_code;
    uint32_t active_slot_index = (uint32_t)p_context;

    es_adv_timing_evt_t evt;

    evt.slot_no = m_adv_timing_result.timing_results[active_slot_index].slot_no;

    evt.evt_id = m_adv_timing_result.timing_results[active_slot_index].is_etlm
                     ? ES_ADV_TIMING_EVT_ADV_ETLM
                     : ES_ADV_TIMING_EVT_ADV_SLOT;

    // Trigger an event for the next slot if this slot is not the last to be advertised in this event.
    // Note: since we check 'm_adv_timing_result.len_timing_results > 1' we can safely cast the result of
    //       the subtraction to a uint32.
    if (m_non_conn_adv_active && \
        m_adv_timing_result.len_timing_results > 1 && \
        active_slot_index < (uint32_t)(m_adv_timing_result.len_timing_results - 1))
    {
        err_code = app_timer_start( m_es_slot_timer,
                                    APP_TIMER_TICKS(m_adv_timing_result.timing_results[active_slot_index].delay_ms),
                                    (void*)(active_slot_index + 1));
        APP_ERROR_CHECK(err_code);
    }

#if APP_CONFIG_TLM_ADV_INTERLEAVE_RATIO > 1
    static uint32_t adv_event_cnt = 0;

    if (active_slot_index == 0)
    {
        adv_event_cnt++;
    }

    if (frame_to_adv_is_tlm(&evt) && !tlm_should_be_advertised(adv_event_cnt))
    {
        return;
    }
#endif // APP_CONFIG_TLM_ADV_INTERLEAVE_RATIO > 1

    invoke_callback(&evt);
}


/**@brief Timeout handler for the advertisement interval timer. */
static void adv_interval_timeout(void * p_context)
{
    if (es_slot_get_registry()->num_configured_slots > 0)
    {
        // Trigger slot timeout for advertising the first slot.
        // Note: The slot number is not the index in the slot registry, it is the index of the active slots.
        adv_slot_timeout(NULL);
    }

    if (m_non_conn_adv_active)
    {
        uint32_t err_code = app_timer_start(m_es_adv_interval_timer,
                                   APP_TIMER_TICKS(m_current_adv_interval),
                                   NULL);
        APP_ERROR_CHECK(err_code);
    }
}


void es_adv_timing_timers_init(void)
{
    ret_code_t err_code;

    err_code = app_timer_create(&m_es_adv_interval_timer,
                                APP_TIMER_MODE_SINGLE_SHOT,
                                adv_interval_timeout);
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_create(&m_es_slot_timer,
                                APP_TIMER_MODE_SINGLE_SHOT,
                                adv_slot_timeout);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for finding and setting advertisement timing configuration. */
static void adv_timing_set(void)
{
    ret_code_t            err_code;
    const es_slot_reg_t * p_reg = es_slot_get_registry();

    es_adv_timing_resolver_input_t resolver_input = {
        .adv_interval             = m_current_adv_interval,
        .p_result                 = &m_adv_timing_result,
        .num_slots_configured     = p_reg->num_configured_slots,
        .p_slots_configured       = p_reg->slots_configured,
        .num_eid_slots_configured = p_reg->num_configured_eid_slots,
        .p_eid_slots_configured   = p_reg->eid_slots_configured,
        .tlm_configured           = p_reg->tlm_configured,
        .tlm_slot                 = p_reg->tlm_slot};

    err_code = es_adv_timing_resolve(&resolver_input);
    APP_ERROR_CHECK(err_code);
}


void es_adv_timing_start(uint16_t adv_interval)
{
    ret_code_t err_code;

    const es_slot_reg_t * p_reg = es_slot_get_registry();

    m_non_conn_adv_active = true;

    if (p_reg->num_configured_slots > 0)
    {
        m_current_adv_interval = adv_interval;

        err_code = app_timer_start(m_es_adv_interval_timer,
                                   APP_TIMER_TICKS(m_current_adv_interval),
                                   NULL);
        APP_ERROR_CHECK(err_code);

        adv_timing_set();
    }
}


void es_adv_timing_stop(void)
{
    m_non_conn_adv_active = false; // Stops timers from being re-fired.
}


void es_adv_timing_init(es_adv_timing_callback_t p_handler)
{
    m_non_conn_adv_active = false;
    m_timing_mgr_callback = p_handler;
    memset(&m_adv_timing_result, 0, sizeof(m_adv_timing_result));
}
