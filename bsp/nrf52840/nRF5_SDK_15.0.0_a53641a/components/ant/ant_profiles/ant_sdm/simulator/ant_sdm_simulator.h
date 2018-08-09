/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
#ifndef ANT_SDM_SIMULATOR_H__
#define ANT_SDM_SIMULATOR_H__

/** @file
 *
 * @defgroup ant_sdk_sdm_simulator ANT SDM simulator
 * @{
 * @ingroup ant_sdk_simulators
 * @brief ANT SDM simulator module.
 *
 * @details This module simulates strides for the ANT SDM profile. The module calculates
 * abstract values, which are handled by the SDM pages data model to ensure that they are
 * compatible. It provides a handler for changing the cadence value manually and functionality
 * for changing the cadence automatically.
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "ant_sdm.h"
#include "ant_sdm_utils.h"
#include "sensorsim.h"
#include "ant_sdm_simulator_local.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief SDM simulator configuration structure. */
typedef struct
{
    ant_sdm_profile_t * p_profile;     ///< Related profile.
    uint32_t            stride_length; ///< Length of a stride in cm.
    uint32_t            burn_rate;     ///< Kcal per kilometer.
    sensorsim_cfg_t     sensorsim_cfg; ///< Sensorsim configuration.
} ant_sdm_simulator_cfg_t;

/**@brief Initialize @ref ant_sdm_simulator_cfg_t.
 */
#define DEFAULT_ANT_SDM_SIMULATOR_CFG(P_PROFILE,                                      \
                                      STRIDE_LEN,                                     \
                                      BURN_RATE,                                      \
                                      MIN_CADENCE,                                    \
                                      MAX_CADENCE,                                    \
                                      INCREMENT)                                      \
    {                                                                                 \
        .p_profile                  = (P_PROFILE),                                    \
        .stride_length              = (STRIDE_LEN),                                   \
        .burn_rate                  = (BURN_RATE),                                    \
        .sensorsim_cfg.min          = (MIN_CADENCE) *(ANT_SDM_CADENCE_UNIT_REVERSAL), \
        .sensorsim_cfg.max          = (MAX_CADENCE) *(ANT_SDM_CADENCE_UNIT_REVERSAL), \
        .sensorsim_cfg.incr         = (INCREMENT) *(ANT_SDM_CADENCE_UNIT_REVERSAL),   \
        .sensorsim_cfg.start_at_max = false,                                          \
    }

/**@brief SDM simulator structure. */
typedef struct
{
    ant_sdm_profile_t      * p_profile;   ///< Related profile.
    ant_sdm_simulator_cb_t   _cb;         ///< Internal control block.
} ant_sdm_simulator_t;


/**@brief Function for initializing the ANT SDM simulator instance.
 *
 * @param[in]  p_simulator      Pointer to the simulator instance.
 * @param[in]  p_config         Pointer to the simulator configuration structure.
 * @param[in]  auto_change      Enable or disable automatic changes of the cadence.
 */
void ant_sdm_simulator_init(ant_sdm_simulator_t           * p_simulator,
                            ant_sdm_simulator_cfg_t const * p_config,
                            bool                            auto_change);

/**@brief Function for simulating a device event.
 *
 * @details Based on this event, the transmitter data is simulated.
 *
 * This function should be called in the SDM TX event handler.
 */
void ant_sdm_simulator_one_iteration(ant_sdm_simulator_t * p_simulator);

/**@brief Function for incrementing the cadence value.
 *
 * @param[in]  p_simulator      Pointer to the simulator instance.
 */
void ant_sdm_simulator_increment(ant_sdm_simulator_t * p_simulator);

/**@brief Function for decrementing the cadence value.
 *
 * @param[in]  p_simulator      Pointer to the simulator instance.
 */
void ant_sdm_simulator_decrement(ant_sdm_simulator_t * p_simulator);


#ifdef __cplusplus
}
#endif

#endif // ANT_SDM_SIMULATOR_H__
/** @} */
