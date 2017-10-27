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
#if NRF_MODULE_ENABLED(ANT_SDM)

#include "ant_sdm_simulator.h"
#include "ant_sdm_utils.h"

#define SIMULATOR_STRIDE_LENGTH_UNIT_REVERSAL 100                 ///< Stride length unit is cm.
#define SIMULATOR_BURN_RATE_UNIT              1000                ///< Burn rate uinit is kcal per km.
#define SIMULATOR_TIME_INCREMENT              SDM_MSG_PERIOD_4Hz  ///< Ticks between two cycles.
#define SIMULATOR_TIME_UNIT_REVERSAL          ANT_CLOCK_FREQUENCY ///< Simulation time frequency.
#define SEC_PER_MIN                           60                  ///< Number of seconds per minute.
#define SIMULATOR_STRIDE_UNIT_REVERSAL        (SIMULATOR_TIME_UNIT_REVERSAL * \
                                               ANT_SDM_CADENCE_UNIT_REVERSAL * SEC_PER_MIN)


void ant_sdm_simulator_init(ant_sdm_simulator_t           * p_simulator,
                            ant_sdm_simulator_cfg_t const * p_config,
                            bool                            auto_change)
{
    p_simulator->p_profile         = p_config->p_profile;
    p_simulator->_cb.stride_length = p_config->stride_length;
    p_simulator->_cb.burn_rate     = p_config->burn_rate;
    p_simulator->_cb.sensorsim_cfg = p_config->sensorsim_cfg;
    p_simulator->_cb.auto_change   = auto_change;
    p_simulator->_cb.sensorsim_state.current_val       = p_simulator->_cb.sensorsim_cfg.min;
    p_simulator->_cb.stride_incr   = 0;
    p_simulator->_cb.time          = 0;


    sensorsim_init(&(p_simulator->_cb.sensorsim_state), &(p_simulator->_cb.sensorsim_cfg));
}


void ant_sdm_simulator_one_iteration(ant_sdm_simulator_t * p_simulator)
{
    if (p_simulator->_cb.auto_change)
    {
        UNUSED_PARAMETER(sensorsim_measure(&(p_simulator->_cb.sensorsim_state),
                                           &(p_simulator->_cb.sensorsim_cfg)));
    }

    p_simulator->_cb.time += SIMULATOR_TIME_INCREMENT;

    p_simulator->_cb.stride_incr += p_simulator->_cb.sensorsim_state.current_val *
                                   SIMULATOR_TIME_INCREMENT;
    p_simulator->p_profile->SDM_PROFILE_strides += p_simulator->_cb.stride_incr /
                                                   SIMULATOR_STRIDE_UNIT_REVERSAL;
    p_simulator->_cb.stride_incr = p_simulator->_cb.stride_incr %
                                  SIMULATOR_STRIDE_UNIT_REVERSAL;


    uint32_t distance = value_rescale(
        p_simulator->p_profile->SDM_PROFILE_strides * p_simulator->_cb.stride_length,
        SIMULATOR_STRIDE_LENGTH_UNIT_REVERSAL,
        ANT_SDM_DISTANCE_UNIT_REVERSAL);

    if (p_simulator->p_profile->SDM_PROFILE_capabilities.cadency_is_valid)
    {
        p_simulator->p_profile->SDM_PROFILE_cadence = p_simulator->_cb.sensorsim_state.current_val;
    }

    if (p_simulator->p_profile->SDM_PROFILE_capabilities.speed_is_valid)
    {
        p_simulator->p_profile->SDM_PROFILE_speed = value_rescale(
            p_simulator->_cb.sensorsim_state.current_val * p_simulator->_cb.stride_length,
            ANT_SDM_CADENCE_UNIT_REVERSAL * SIMULATOR_STRIDE_LENGTH_UNIT_REVERSAL * SEC_PER_MIN,
            ANT_SDM_SPEED_UNIT_REVERSAL);
    }

    if (p_simulator->p_profile->SDM_PROFILE_capabilities.distance_is_valid)
    {
        p_simulator->p_profile->SDM_PROFILE_distance = distance;
    }

    if (p_simulator->p_profile->SDM_PROFILE_capabilities.calorie_is_valid)
    {
        p_simulator->p_profile->SDM_PROFILE_calories = value_rescale(distance,
                                                                     SIMULATOR_BURN_RATE_UNIT
                                                                     * ANT_SDM_DISTANCE_UNIT_REVERSAL,
                                                                     p_simulator->_cb.burn_rate);
    }

    if (p_simulator->p_profile->SDM_PROFILE_capabilities.time_is_valid)
    {
        p_simulator->p_profile->SDM_PROFILE_time = value_rescale(p_simulator->_cb.time,
                                                                 SIMULATOR_TIME_UNIT_REVERSAL,
                                                                 ANT_SDM_TIME_UNIT_REVERSAL);
    }

    if (p_simulator->p_profile->SDM_PROFILE_capabilities.latency_is_valid)
    {
        p_simulator->p_profile->SDM_PROFILE_update_latency =
            ROUNDED_DIV(((uint64_t)p_simulator->_cb.stride_incr *
                         ANT_SDM_UPDATE_LATENCY_UNIT_REVERSAL),
                        (uint64_t)SIMULATOR_TIME_UNIT_REVERSAL *
                        p_simulator->_cb.sensorsim_state.current_val);
    }
}


void ant_sdm_simulator_increment(ant_sdm_simulator_t * p_simulator)
{
    if (!p_simulator->_cb.auto_change)
    {
        sensorsim_increment(&(p_simulator->_cb.sensorsim_state),
                            &(p_simulator->_cb.sensorsim_cfg));
    }
}


void ant_sdm_simulator_decrement(ant_sdm_simulator_t * p_simulator)
{
    if (!p_simulator->_cb.auto_change)
    {
        sensorsim_decrement(&(p_simulator->_cb.sensorsim_state),
                            &(p_simulator->_cb.sensorsim_cfg));
    }
}

#endif // NRF_MODULE_ENABLED(ANT_SDM)
