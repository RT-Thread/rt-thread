/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#ifndef ANT_HRM_SIMULATOR_H__
#define ANT_HRM_SIMULATOR_H__

/** @file
 *
 * @defgroup ant_sdk_hrm_simulator ANT HRM simulator
 * @{
 * @ingroup ant_sdk_simulators
 * @brief ANT HRM simulator module.
 *
 * @details This module simulates a pulse for the ANT HRM profile. The module calculates abstract values, which are handled
 * by the HRM pages data model to ensure that they are compatible. It provides a handler for changing the heart rate
 * value manually and functionality to change the heart rate value automatically.
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "ant_hrm.h"
#include "ant_hrm_utils.h"
#include "sensorsim.h"
#include "ant_hrm_simulator_local.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@brief HRM simulator configuration structure. */
typedef struct
{
    ant_hrm_profile_t * p_profile;     ///< Related profile.
    sensorsim_cfg_t     sensorsim_cfg; ///< Sensorsim configuration.
} ant_hrm_simulator_cfg_t;

/**@brief Initialize @ref ant_hrm_simulator_cfg_t.
 */
#define DEFAULT_ANT_HRM_SIMULATOR_CFG(P_PROFILE, MIN_HEART_RATE, MAX_HEART_RATE, INCREMENT) \
    {                                                                                       \
        .p_profile                  = (P_PROFILE),                                          \
        .sensorsim_cfg.min          = (MIN_HEART_RATE),                                     \
        .sensorsim_cfg.max          = (MAX_HEART_RATE),                                     \
        .sensorsim_cfg.incr         = (INCREMENT),                                          \
        .sensorsim_cfg.start_at_max = false,                                                \
    }

/**@brief HRM simulator structure. */
typedef struct
{
    ant_hrm_profile_t       * p_profile;    ///< Related profile.
    ant_hrm_simulator_cb_t    _cb;          ///< Internal control block.
} ant_hrm_simulator_t;


/**@brief Function for initializing the ANT HRM simulator instance.
 *
 * @param[in]  p_simulator      Pointer to the simulator instance.
 * @param[in]  p_config         Pointer to the simulator configuration structure.
 * @param[in]  auto_change      Enable or disable automatic changes of the cadence.
 */
void ant_hrm_simulator_init(ant_hrm_simulator_t           * p_simulator,
                            ant_hrm_simulator_cfg_t const * p_config,
                            bool                            auto_change);

/**@brief Function for simulating a device event.
 *
 * @details Based on this event, the transmitter data is simulated.
 *
 * This function should be called in the HRM TX event handler.
 */
void ant_hrm_simulator_one_iteration(ant_hrm_simulator_t * p_simulator);

/**@brief Function for incrementing the cadence value.
 *
 * @param[in]  p_simulator      Pointer to the simulator instance.
 */
void ant_hrm_simulator_increment(ant_hrm_simulator_t * p_simulator);

/**@brief Function for decrementing the cadence value.
 *
 * @param[in]  p_simulator      Pointer to the simulator instance.
 */
void ant_hrm_simulator_decrement(ant_hrm_simulator_t * p_simulator);


#ifdef __cplusplus
}
#endif

#endif // ANT_HRM_SIMULATOR_H__
/** @} */
