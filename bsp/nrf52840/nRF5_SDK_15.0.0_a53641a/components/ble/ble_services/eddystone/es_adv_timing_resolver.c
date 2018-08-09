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

#include "es_adv_timing_resolver.h"
#include "sdk_macros.h"

/**@brief Function for finding delay to use after each non-eTLM advertisement.
 *
 * @param[in] adv_interval          Configured advertisement interval.
 * @param[in] num_slots_configured  Number of configured slots.
 * @param[in] eTLM_required         Is there an eTLM slot.
 */
static uint16_t get_adv_delay(uint16_t adv_interval,
                              uint8_t  num_slots_configured,
                              bool     eTLM_required)
{
    // If eTLM is required, don't count this when calculating delay.
    return adv_interval / (num_slots_configured - (eTLM_required ? 1 : 0));
}


/**@brief Function for checking if given slot_no is an EID slot.
 *
 * @param[in] slot_no                   Slot number to check.
 * @param[in] p_eid_slots_configured    Pointer to list of configured EID slots.
 * @param[in] num_eid_slots_configured  Number of EID slots configured.
 */
static bool is_eid(uint8_t slot_no, const uint8_t * p_eid_slots_configured, uint8_t num_eid_slots_configured)
{
    for (uint32_t i = 0; i < num_eid_slots_configured; ++i)
    {
        if (slot_no == p_eid_slots_configured[i])
        {
            return true;
        }
    }

    return false;
}

ret_code_t es_adv_timing_resolve(es_adv_timing_resolver_input_t * p_input)
{
    VERIFY_PARAM_NOT_NULL(p_input);

    uint8_t  result_index  = 0;
    bool     eTLM_required = p_input->tlm_configured && p_input->num_eid_slots_configured > 0;
    uint16_t base_delay;

    if (p_input->num_slots_configured == 0)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    base_delay = get_adv_delay(p_input->adv_interval, p_input->num_slots_configured, eTLM_required);

    for (uint32_t i = 0; i < p_input->num_slots_configured; ++i)
    {
        uint8_t slot_no = p_input->p_slots_configured[i];

        if (!(eTLM_required && slot_no == p_input->tlm_slot))
        {
            es_adv_timing_resolver_adv_timing_t * p_current_result = &p_input->p_result->timing_results[result_index];
            p_current_result->slot_no = slot_no;
            p_current_result->is_etlm = false;

            // If an eTLM is to be advertised for this frame, this value will be changed.
            p_current_result->delay_ms = base_delay;

            result_index++;

            if (eTLM_required &&
                is_eid(slot_no, p_input->p_eid_slots_configured, p_input->num_eid_slots_configured))
            {
                es_adv_timing_resolver_adv_timing_t * p_eTLM_timing_result =
                    &p_input->p_result->timing_results[result_index];

                p_current_result->delay_ms = APP_CONFIG_ADV_FRAME_ETLM_SPACING_MS; // Update delay from EID to eTLM frame.

                p_eTLM_timing_result->slot_no = slot_no; // Point to EID slot-no, as this will be
                                                         // used for finding the correct EIK.
                p_eTLM_timing_result->is_etlm = true;    // Configure as eTLM frame.

                if (base_delay > APP_CONFIG_ADV_FRAME_ETLM_SPACING_MS)
                {
                    p_eTLM_timing_result->delay_ms =
                        base_delay -
                        APP_CONFIG_ADV_FRAME_ETLM_SPACING_MS; // Set delay of eTLM frame.
                }

                else
                {
                    p_eTLM_timing_result->delay_ms = APP_CONFIG_ADV_FRAME_SPACING_MS_MIN;
                }

                result_index++;
            }
        }
    }

    p_input->p_result->len_timing_results = result_index; // Note: index has been increased to equal length of result.

    if (p_input->p_result->len_timing_results > 0)
    {
        p_input->p_result->timing_results[p_input->p_result->len_timing_results - 1].delay_ms = 0; // Last Slot does not need delay.
    }

    return NRF_SUCCESS;
}
