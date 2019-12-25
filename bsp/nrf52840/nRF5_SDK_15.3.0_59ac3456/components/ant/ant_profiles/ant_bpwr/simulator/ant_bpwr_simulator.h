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
#ifndef ANT_BPWR_SIMULATOR_H__
#define ANT_BPWR_SIMULATOR_H__

/** @file
 *
 * @defgroup ant_sdk_simulators ANT simulators
 * @ingroup ant_sdk_utils
 * @brief Modules that simulate sensors.
 *
 * @defgroup ant_sdk_bpwr_simulator ANT BPWR simulator
 * @{
 * @ingroup ant_sdk_simulators
 * @brief ANT BPWR simulator module.
 *
 * @details This module simulates power for the ANT BPWR profile. The module calculates
 * abstract values, which are handled by the BPWR pages data model to ensure that they are
 * compatible. It provides a handler for changing the power value manually and functionality
 * for changing the power automatically.
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "bsp.h"
#include "ant_bpwr.h"
#include "sensorsim.h"
#include "ant_bpwr_simulator_local.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief BPWR simulator configuration structure. */
typedef struct
{
    ant_bpwr_profile_t * p_profile;   ///< Related profile.
    ant_bpwr_torque_t    sensor_type; ///< Type of related sensor.
} ant_bpwr_simulator_cfg_t;

/**@brief BPWR simulator structure. */
typedef struct
{
    ant_bpwr_profile_t      * p_profile;    ///< Related profile.
    ant_bpwr_simulator_cb_t   _cb;          ///< Internal control block.
} ant_bpwr_simulator_t;


/**@brief Function for initializing the ANT BPWR simulator instance.
 *
 * @param[in]  p_simulator      Pointer to the simulator instance.
 * @param[in]  p_config         Pointer to the simulator configuration structure.
 * @param[in]  auto_change      Enable or disable automatic changes of the power.
 */
void ant_bpwr_simulator_init(ant_bpwr_simulator_t           * p_simulator,
                             ant_bpwr_simulator_cfg_t const * p_config,
                             bool                             auto_change);

/**@brief Function for simulating a device event.
 *
 * @details Based on this event, the transmitter data is simulated.
 *
 * This function should be called in the BPWR TX event handler.
 */
void ant_bpwr_simulator_one_iteration(ant_bpwr_simulator_t * p_simulator, ant_bpwr_evt_t event);

/**@brief Function for incrementing the power value.
 *
 * @param[in]  p_simulator      Pointer to the simulator instance.
 */
void ant_bpwr_simulator_increment(ant_bpwr_simulator_t * p_simulator);

/**@brief Function for decrementing the power value.
 *
 * @param[in]  p_simulator      Pointer to the simulator instance.
 */
void ant_bpwr_simulator_decrement(ant_bpwr_simulator_t * p_simulator);


#ifdef __cplusplus
}
#endif

#endif // ANT_BPWR_SIMULATOR_H__
/** @} */
