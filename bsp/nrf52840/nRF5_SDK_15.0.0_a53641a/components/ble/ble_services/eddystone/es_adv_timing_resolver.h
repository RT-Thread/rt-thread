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
#ifndef ES_ADV_TIMING_RESOLVER_H__
#define ES_ADV_TIMING_RESOLVER_H__

#include <stdbool.h>
#include <stdint.h>
#include "es_app_config.h"

/**
 * @file
 * @addtogroup eddystone_adv_timing
 * @{
 */

/** @brief Timing parameters for a single slot. */
typedef struct
{
    bool    is_etlm;   //!< Flag that specifies if the slot is an eTLM.
    uint8_t slot_no;   /**< @brief Slot number. @details
                        * For non-eTLM slots: The slot number of the given frame.
                        *
                        * For eTLM slots: The slot number of the corresponding EID frame. */
    uint16_t delay_ms; //!< Delay from this frame to the next.
} es_adv_timing_resolver_adv_timing_t;

/**@brief Results of calculating advertisement delays. */
typedef struct
{
    es_adv_timing_resolver_adv_timing_t timing_results[APP_MAX_ADV_SLOTS - APP_MAX_EID_SLOTS +
                                                       (APP_MAX_EID_SLOTS * 2)]; //!< List of timing results.
    uint8_t len_timing_results;                                                  //!< Length of results.
} es_adv_timing_resolver_result_t;

/**@brief Input to the timing resolver. */
typedef struct
{
    uint16_t        adv_interval;               //!< Global advertisement interval.
    uint8_t         num_slots_configured;       //!< Number of configured slots.
    const uint8_t * p_slots_configured;         //!< Pointer to the list of configured slots.
    uint8_t         num_eid_slots_configured;   //!< Number of configured EID slots.
    const uint8_t * p_eid_slots_configured;     //!< Pointer to the list of configured EID slots.
    bool            tlm_configured;             //!< Flag that specifies if TLM slot is configured.
    uint8_t         tlm_slot;                   //!< Slot number of the TLM slot (if @p tlm_configured is true).
    es_adv_timing_resolver_result_t * p_result; //!< Output result.
} es_adv_timing_resolver_input_t;

/**@brief Function for getting the input for advertisement interval calculation.
 *
 * @param[in,out]    p_input Input to advertisement interval calculation (see @ref es_adv_timing_resolver_input_t).
 * @retval           NRF_SUCCESS If the operation was successful. Otherwise, an error code is returned.
 */
ret_code_t es_adv_timing_resolve(es_adv_timing_resolver_input_t * p_input);

/**
 * @}
 */

#endif // ES_ADV_TIMING_RESOLVER_H__
