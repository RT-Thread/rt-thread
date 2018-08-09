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
#include "ant_bpwr_simulator.h"
#include "app_util.h"
#include "nordic_common.h"

#define POWER_MIN  0
#define POWER_MAX  2000
#define POWER_INCR 10

#define CADENCE_MIN  0
#define CADENCE_MAX  (UINT8_MAX - 1)
#define CADENCE_INCR 1

#define PEDAL_MIN  0
#define PEDAL_MAX  100
#define PEDAL_INCR 1

#define TORQUE_PERIOD            774
#define SIMULATOR_TIME_INCREMENT BPWR_MSG_PERIOD

#define TORQUE_INCR 10


void ant_bpwr_simulator_init(ant_bpwr_simulator_t           * p_simulator,
                             ant_bpwr_simulator_cfg_t const * p_config,
                             bool                             auto_change)
{
    p_simulator->p_profile      = p_config->p_profile;
    p_simulator->_cb.auto_change = auto_change;
    p_simulator->_cb.tick_incr   = 0;

    p_simulator->_cb.power_sensorsim_cfg.min          = POWER_MIN;
    p_simulator->_cb.power_sensorsim_cfg.max          = POWER_MAX;
    p_simulator->_cb.power_sensorsim_cfg.incr         = POWER_INCR;
    p_simulator->_cb.power_sensorsim_cfg.start_at_max = false;

    p_simulator->_cb.cadence_sensorsim_cfg.min          = CADENCE_MIN;
    p_simulator->_cb.cadence_sensorsim_cfg.max          = CADENCE_MAX;
    p_simulator->_cb.cadence_sensorsim_cfg.incr         = CADENCE_INCR;
    p_simulator->_cb.cadence_sensorsim_cfg.start_at_max = false;

    p_simulator->_cb.pedal_sensorsim_cfg.min          = PEDAL_MIN;
    p_simulator->_cb.pedal_sensorsim_cfg.max          = PEDAL_MAX;
    p_simulator->_cb.pedal_sensorsim_cfg.incr         = PEDAL_INCR;
    p_simulator->_cb.pedal_sensorsim_cfg.start_at_max = false;

    p_simulator->p_profile->BPWR_PROFILE_pedal_power.differentiation = 0x01; // right

    sensorsim_init(&(p_simulator->_cb.power_sensorsim_state),
                   &(p_simulator->_cb.power_sensorsim_cfg));
    sensorsim_init(&(p_simulator->_cb.cadence_sensorsim_state),
                   &(p_simulator->_cb.cadence_sensorsim_cfg));
    sensorsim_init(&(p_simulator->_cb.pedal_sensorsim_state),
                   &(p_simulator->_cb.pedal_sensorsim_cfg));
}


void ant_bpwr_simulator_one_iteration(ant_bpwr_simulator_t * p_simulator, ant_bpwr_evt_t event)
{
    switch (event)
    {
        case ANT_BPWR_PAGE_16_UPDATED:

            if (p_simulator->_cb.auto_change)
            {
                UNUSED_PARAMETER(sensorsim_measure(&(p_simulator->_cb.power_sensorsim_state),
                                                   &(p_simulator->_cb.power_sensorsim_cfg)));
                UNUSED_PARAMETER(sensorsim_measure(&(p_simulator->_cb.cadence_sensorsim_state),
                                                   &(p_simulator->_cb.cadence_sensorsim_cfg)));
                UNUSED_PARAMETER(sensorsim_measure(&(p_simulator->_cb.pedal_sensorsim_state),
                                                   &(p_simulator->_cb.pedal_sensorsim_cfg)));
            }

            p_simulator->p_profile->BPWR_PROFILE_instantaneous_power =
                p_simulator->_cb.power_sensorsim_state.current_val;
            p_simulator->p_profile->BPWR_PROFILE_accumulated_power +=
                p_simulator->_cb.power_sensorsim_state.current_val;

            if (p_simulator->p_profile->BPWR_PROFILE_accumulated_power == UINT16_MAX)
            {
                p_simulator->p_profile->BPWR_PROFILE_accumulated_power = 0;
            }
            p_simulator->p_profile->BPWR_PROFILE_instantaneous_cadence =
                 p_simulator->_cb.cadence_sensorsim_state.current_val;
            p_simulator->p_profile->BPWR_PROFILE_pedal_power.distribution =
                p_simulator->_cb.pedal_sensorsim_state.current_val;
            p_simulator->p_profile->BPWR_PROFILE_power_update_event_count++;
            break;

        case ANT_BPWR_PAGE_17_UPDATED:

            if (p_simulator->_cb.auto_change)
            {
                UNUSED_PARAMETER(sensorsim_measure(&(p_simulator->_cb.cadence_sensorsim_state),
                                                   &(p_simulator->_cb.cadence_sensorsim_cfg)));
            }
            p_simulator->p_profile->BPWR_PROFILE_instantaneous_cadence =
                 p_simulator->_cb.cadence_sensorsim_state.current_val;
            p_simulator->p_profile->BPWR_PROFILE_wheel_period += TORQUE_PERIOD;
            p_simulator->_cb.tick_incr                        +=
                SIMULATOR_TIME_INCREMENT;
            p_simulator->p_profile->BPWR_PROFILE_wheel_tick +=
                p_simulator->_cb.tick_incr / (TORQUE_PERIOD * 16);
            p_simulator->_cb.tick_incr =
                p_simulator->_cb.tick_incr % (TORQUE_PERIOD * 16);
            p_simulator->p_profile->BPWR_PROFILE_wheel_accumulated_torque += TORQUE_INCR;
            p_simulator->p_profile->BPWR_PROFILE_wheel_update_event_count++;
            break;

        case ANT_BPWR_PAGE_18_UPDATED:

            if (p_simulator->_cb.auto_change)
            {
                UNUSED_PARAMETER(sensorsim_measure(&(p_simulator->_cb.cadence_sensorsim_state),
                                                   &(p_simulator->_cb.cadence_sensorsim_cfg)));
            }
            p_simulator->p_profile->BPWR_PROFILE_instantaneous_cadence =
                 p_simulator->_cb.cadence_sensorsim_state.current_val;
            p_simulator->p_profile->BPWR_PROFILE_crank_period = TORQUE_PERIOD;
            p_simulator->_cb.tick_incr                        +=
                SIMULATOR_TIME_INCREMENT;
            p_simulator->p_profile->BPWR_PROFILE_crank_tick +=
                p_simulator->_cb.tick_incr / (TORQUE_PERIOD * 16);
            p_simulator->_cb.tick_incr =
                p_simulator->_cb.tick_incr % (TORQUE_PERIOD * 16);
            p_simulator->p_profile->BPWR_PROFILE_crank_accumulated_torque += TORQUE_INCR;
            p_simulator->p_profile->BPWR_PROFILE_crank_update_event_count++;
            break;

        default:
            break;
    }
}


void ant_bpwr_simulator_increment(ant_bpwr_simulator_t * p_simulator)
{
    if (!p_simulator->_cb.auto_change)
    {
        sensorsim_increment(&(p_simulator->_cb.power_sensorsim_state),
                            &(p_simulator->_cb.power_sensorsim_cfg));
        sensorsim_increment(&(p_simulator->_cb.cadence_sensorsim_state),
                            &(p_simulator->_cb.cadence_sensorsim_cfg));
        sensorsim_increment(&(p_simulator->_cb.pedal_sensorsim_state),
                            &(p_simulator->_cb.pedal_sensorsim_cfg));
    }
}


void ant_bpwr_simulator_decrement(ant_bpwr_simulator_t * p_simulator)
{
    if (!p_simulator->_cb.auto_change)
    {
        sensorsim_decrement(&(p_simulator->_cb.power_sensorsim_state),
                            &(p_simulator->_cb.power_sensorsim_cfg));
        sensorsim_decrement(&(p_simulator->_cb.cadence_sensorsim_state),
                            &(p_simulator->_cb.cadence_sensorsim_cfg));
        sensorsim_decrement(&(p_simulator->_cb.pedal_sensorsim_state),
                            &(p_simulator->_cb.pedal_sensorsim_cfg));
    }
}


