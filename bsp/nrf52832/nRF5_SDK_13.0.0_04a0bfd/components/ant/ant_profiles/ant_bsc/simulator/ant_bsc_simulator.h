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
#ifndef ANT_BSC_SIMULATOR_H__
#define ANT_BSC_SIMULATOR_H__

/** @file
 *
 * @defgroup ant_sdk_bsc_simulator ANT BSC simulator
 * @{
 * @ingroup ant_sdk_simulators
 * @brief ANT BSC simulator module.
 *
 * @details This module simulates a pulse for the ANT Bicycle Speed and Cadence profile. The module
 * calculates abstract values, which are handled by the BSC pages data model to ensure that
 * they are compatible. It provides a handler for changing the cadence and speed values manually
 * as well as functionality to change the values automatically.
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "ant_bsc.h"
#include "ant_bsc_utils.h"
#include "sensorsim.h"
#include "ant_bsc_simulator_local.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief BSC simulator configuration structure. */
typedef struct
{
    ant_bsc_profile_t * p_profile;      ///< Related profile.
    uint8_t             device_type;    ///< BSC device type (must be consistent with the type chosen for the profile). Supported types:
                                        //   @ref BSC_SPEED_DEVICE_TYPE, @ref BSC_CADENCE_DEVICE_TYPE, @ref BSC_COMBINED_DEVICE_TYPE.
} ant_bsc_simulator_cfg_t;

/**@brief BSC simulator structure. */
typedef struct
{
    ant_bsc_profile_t    * p_profile;   ///< Related profile.
    ant_bsc_simulator_cb_t _cb;         ///< Internal control block.
} ant_bsc_simulator_t;


/**@brief Function for initializing the ANT BSC simulator instance.
 *
 * @param[in]  p_simulator      Pointer to the simulator instance.
 * @param[in]  p_config         Pointer to the simulator configuration structure.
 * @param[in]  auto_change      Enable or disable automatic changes of speed or cadence.
 */
void ant_bsc_simulator_init(ant_bsc_simulator_t           * p_simulator,
                            ant_bsc_simulator_cfg_t const * p_config,
                            bool                            auto_change);

/**@brief Function for simulating a device event.
 *
 * @details Based on this event, the transmitter data is simulated.
 *
 * This function should be called in the BSC Sensor event handler.
 */
void ant_bsc_simulator_one_iteration(ant_bsc_simulator_t * p_simulator);

/**@brief Function for incrementing the cadence value.
 *
 * @param[in]  p_simulator      Pointer to the simulator instance.
 */
void ant_bsc_simulator_increment(ant_bsc_simulator_t * p_simulator);

/**@brief Function for decrementing the cadence value.
 *
 * @param[in]  p_simulator      Pointer to the simulator instance.
 */
void ant_bsc_simulator_decrement(ant_bsc_simulator_t * p_simulator);


#ifdef __cplusplus
}
#endif

#endif // ANT_BSC_SIMULATOR_H__
/** @} */
