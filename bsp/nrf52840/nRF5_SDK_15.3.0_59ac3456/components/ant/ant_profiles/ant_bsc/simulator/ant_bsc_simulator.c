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
#include "ant_bsc_simulator.h"
#include "ant_bsc_utils.h"
#include "app_util.h"

#define ITERATION_ANT_CYCLES(DEVICE_TYPE) \
        (BSC_PERIOD_TICKS(DEVICE_TYPE, BSC_MSG_PERIOD_4Hz)) ///< period of calculation [1/32678 s], defined in ANT device profile
                                                            //   use the same DEVICE TYPE as in profile definition
#define ITERATION_PERIOD(DEVICE_TYPE) \
        ((ITERATION_ANT_CYCLES(DEVICE_TYPE)) * 1024 / ANT_CLOCK_FREQUENCY) ///< integer part of calculation's period [1/1024 s]
#define ITERATION_FRACTION(DEVICE_TYPE) \
        ((ITERATION_ANT_CYCLES(DEVICE_TYPE)) * 1024 % ANT_CLOCK_FREQUENCY) ///< fractional part of calculation's period [1/32678 s]

#define SPEED_SIM_MIN_VAL                       0u      ///< speed simulation minimum value [m/s]
#define SPEED_SIM_MAX_VAL                       16u     ///< speed simulation maximum value [m/s]
#define SPEED_SIM_INCREMENT                     1u      ///< speed simulation value increment [m/s]
#define CADENCE_SIM_MIN_VAL                     70u     ///< cadence simulation minimum value [rpm]
#define CADENCE_SIM_MAX_VAL                     120u    ///< cadence simulation maximum value [rpm]
#define CADENCE_SIM_INCREMENT                   1u      ///< cadence simulation value increment [rpm]
#define WHEEL_CIRCUMFERENCE                     1766u   ///< bike wheel circumference [mm]
#define MM_TO_METERS(MM_VAL)                    ((MM_VAL) / 1000u)
#define TWO_SEC_TO_TICKS                        2048    ///< number of [1/1024s] ticks in 2 sec period
#define CUMULATIVE_TIME_UNIT                    2       ///< cumulative time unit

void ant_bsc_simulator_init(ant_bsc_simulator_t           * p_simulator,
                            ant_bsc_simulator_cfg_t const * p_config,
                            bool                            auto_change)
{
    p_simulator->p_profile                     = p_config->p_profile;
    p_simulator->_cb.auto_change               = auto_change;
    p_simulator->_cb.speed_sim_val             = SPEED_SIM_MIN_VAL;
    p_simulator->_cb.cadence_sim_val           = CADENCE_SIM_MIN_VAL;
    p_simulator->_cb.time_since_last_s_evt     = 0;
    p_simulator->_cb.fraction_since_last_s_evt = 0;
    p_simulator->_cb.time_since_last_c_evt     = 0;
    p_simulator->_cb.fraction_since_last_c_evt = 0;
    p_simulator->_cb.device_type               = p_config->device_type;

    p_simulator->_cb.sensorsim_s_cfg.min          = SPEED_SIM_MIN_VAL;
    p_simulator->_cb.sensorsim_s_cfg.max          = SPEED_SIM_MAX_VAL;
    p_simulator->_cb.sensorsim_s_cfg.incr         = SPEED_SIM_INCREMENT;
    p_simulator->_cb.sensorsim_s_cfg.start_at_max = false;
    sensorsim_init(&(p_simulator->_cb.sensorsim_s_state),
                   &(p_simulator->_cb.sensorsim_s_cfg));
    p_simulator->_cb.sensorsim_c_cfg.min          = CADENCE_SIM_MIN_VAL;
    p_simulator->_cb.sensorsim_c_cfg.max          = CADENCE_SIM_MAX_VAL;
    p_simulator->_cb.sensorsim_c_cfg.incr         = CADENCE_SIM_INCREMENT;
    p_simulator->_cb.sensorsim_c_cfg.start_at_max = false;
    p_simulator->_cb.stop_cnt                     = 0;
    sensorsim_init(&(p_simulator->_cb.sensorsim_c_state),
                   &(p_simulator->_cb.sensorsim_c_cfg));
}


void ant_bsc_simulator_one_iteration(ant_bsc_simulator_t * p_simulator)
{

    // Set constant battery voltage
    p_simulator->p_profile->BSC_PROFILE_coarse_bat_volt = 2;
    p_simulator->p_profile->BSC_PROFILE_fract_bat_volt  = 200;
    p_simulator->p_profile->BSC_PROFILE_bat_status      = BSC_BAT_STATUS_GOOD;

    // Calculate speed and cadence values
    if (p_simulator->_cb.auto_change)
    {
        p_simulator->_cb.speed_sim_val   = sensorsim_measure(&(p_simulator->_cb.sensorsim_s_state),
                                                            &(p_simulator->_cb.sensorsim_s_cfg));
        p_simulator->_cb.cadence_sim_val = sensorsim_measure(&(p_simulator->_cb.sensorsim_c_state),
                                                            &(p_simulator->_cb.sensorsim_c_cfg));
    }
    else
    {
        p_simulator->_cb.speed_sim_val   = p_simulator->_cb.sensorsim_s_state.current_val;
        p_simulator->_cb.cadence_sim_val = p_simulator->_cb.sensorsim_c_state.current_val;
    }

    // Simulate bicycle stopped for around 10s and go for around 5s only in auto-simulation
    if (p_simulator->_cb.auto_change)
    {
        if ((p_simulator->p_profile->_cb.p_sens_cb->main_page_number == ANT_BSC_PAGE_5) &&
            (p_simulator->_cb.stop_cnt++ < 40))
        {
            p_simulator->_cb.speed_sim_val                     = 0;
            p_simulator->_cb.cadence_sim_val                   = 0;
        }
        else
        {
            if (p_simulator->_cb.stop_cnt == 60)
            {
               p_simulator->_cb.stop_cnt = 0;
            }
        }
    }
    if (p_simulator->_cb.speed_sim_val == 0)
    {
        p_simulator->p_profile->BSC_PROFILE_stop_indicator = 1;
    }
    else
    {
        p_simulator->p_profile->BSC_PROFILE_stop_indicator = 0;
    }

    // @note: Take a local copy within scope in order to assist the compiler in variable register
    // allocation.
    const uint32_t computed_speed   = p_simulator->_cb.speed_sim_val;
    const uint32_t computed_cadence = p_simulator->_cb.cadence_sim_val;

    // @note: This implementation assumes that the current instantaneous speed/cadence can vary and this
    // function is called with static frequency.
    // value and the speed/cadence pulse interval is derived from it. The computation is based on 60
    // seconds in a minute and the used time base is 1/1024 seconds.
    const uint32_t current_speed_pulse_interval   =
                       MM_TO_METERS((WHEEL_CIRCUMFERENCE * 1024u) / computed_speed);
    const uint32_t current_cadence_pulse_interval = (60u * 1024u) / computed_cadence;

    //update time from last evt detected
    p_simulator->_cb.time_since_last_s_evt += ITERATION_PERIOD(p_simulator->_cb.device_type);
    p_simulator->_cb.time_since_last_c_evt += ITERATION_PERIOD(p_simulator->_cb.device_type);

    // extended calculation by fraction make calculating accurate in long time perspective
    p_simulator->_cb.fraction_since_last_s_evt += ITERATION_FRACTION(p_simulator->_cb.device_type);
    p_simulator->_cb.fraction_since_last_c_evt += ITERATION_FRACTION(p_simulator->_cb.device_type);

    uint32_t add_period = p_simulator->_cb.fraction_since_last_s_evt / ANT_CLOCK_FREQUENCY;
    if (add_period > 0)
    {
        p_simulator->_cb.time_since_last_s_evt++;
        p_simulator->_cb.fraction_since_last_s_evt %= ANT_CLOCK_FREQUENCY;
    }

    add_period = p_simulator->_cb.fraction_since_last_c_evt / ANT_CLOCK_FREQUENCY;
    if (add_period > 0)
    {
        p_simulator->_cb.time_since_last_c_evt++;
        p_simulator->_cb.fraction_since_last_c_evt %= ANT_CLOCK_FREQUENCY;
    }

    // Calculate cumulative time based on time since last event (from profile data) in [1/1024] ticks
    int16_t diff = p_simulator->p_profile->BSC_PROFILE_event_time -
                   p_simulator->_cb.prev_time_since_evt;
    p_simulator->_cb.prev_time_since_evt = p_simulator->p_profile->BSC_PROFILE_event_time;

    if (diff >= 0)       // Check for time count overflow
    {
        // No overflow
        p_simulator->_cb.cumulative_time += diff / TWO_SEC_TO_TICKS;
        p_simulator->_cb.cumulative_time_frac += diff % TWO_SEC_TO_TICKS;
    }
    else
    {
        p_simulator->_cb.cumulative_time      += (UINT16_MAX + diff) / TWO_SEC_TO_TICKS;
        p_simulator->_cb.cumulative_time_frac += (UINT16_MAX + diff) % TWO_SEC_TO_TICKS;
    }
    // Check fraction
    if ((p_simulator->_cb.cumulative_time_frac / TWO_SEC_TO_TICKS) > 0)
    {
        p_simulator->_cb.cumulative_time      += p_simulator->_cb.cumulative_time_frac / TWO_SEC_TO_TICKS;
        p_simulator->_cb.cumulative_time_frac %= TWO_SEC_TO_TICKS;
    }
    // Update page data if necessary
    if (p_simulator->_cb.cumulative_time != p_simulator->p_profile->BSC_PROFILE_operating_time)
    {
        p_simulator->p_profile->BSC_PROFILE_operating_time = p_simulator->_cb.cumulative_time;
    }

    //calc number of events as will fill
    uint32_t new_s_events           = p_simulator->_cb.time_since_last_s_evt /
                                      current_speed_pulse_interval;
    uint32_t add_speed_event_time   = new_s_events * current_speed_pulse_interval;
    if ((new_s_events > 0) && ((p_simulator->_cb.device_type == BSC_SPEED_DEVICE_TYPE) ||
                               (p_simulator->_cb.device_type == BSC_COMBINED_DEVICE_TYPE)))
    {
        p_simulator->p_profile->BSC_PROFILE_rev_count       += new_s_events;
        p_simulator->p_profile->BSC_PROFILE_speed_rev_count += new_s_events;

        // Current speed event time is the previous event time plus the current speed
        // pulse interval.
        uint32_t current_speed_event_time = p_simulator->p_profile->BSC_PROFILE_event_time +
                                            add_speed_event_time;
        // Set current event time.
        p_simulator->p_profile->BSC_PROFILE_event_time = current_speed_event_time; // <- B<4,5> <-

        current_speed_event_time = p_simulator->p_profile->BSC_PROFILE_speed_event_time +
                                   add_speed_event_time;
        // Set current event time for combined device.
        p_simulator->p_profile->BSC_PROFILE_speed_event_time = current_speed_event_time;

        p_simulator->_cb.time_since_last_s_evt -= add_speed_event_time;
    }

    uint32_t new_c_events           = p_simulator->_cb.time_since_last_c_evt /
                                      current_cadence_pulse_interval;
    uint32_t add_cadence_event_time = new_c_events * current_cadence_pulse_interval;
    if ((new_c_events > 0) && ((p_simulator->_cb.device_type == BSC_CADENCE_DEVICE_TYPE) ||
                               (p_simulator->_cb.device_type == BSC_COMBINED_DEVICE_TYPE)))
    {
        p_simulator->p_profile->BSC_PROFILE_rev_count         += new_c_events;
        p_simulator->p_profile->BSC_PROFILE_cadence_rev_count += new_c_events;

        // Current speed event time is the previous event time plus the current speed
        // pulse interval.
        uint32_t current_cadence_event_time = p_simulator->p_profile->BSC_PROFILE_event_time +
                                              add_cadence_event_time;
        // Set current event time.
        p_simulator->p_profile->BSC_PROFILE_event_time = current_cadence_event_time; //<- B<4,5> <-

        current_cadence_event_time = p_simulator->p_profile->BSC_PROFILE_cadence_event_time +
                                     add_cadence_event_time;
        // Set current event time for combined device.
        p_simulator->p_profile->BSC_PROFILE_cadence_event_time = current_cadence_event_time;

        p_simulator->_cb.time_since_last_c_evt -= add_cadence_event_time;
    }
}


void ant_bsc_simulator_increment(ant_bsc_simulator_t * p_simulator)
{
    if (!p_simulator->_cb.auto_change)
    {
        // Speed
         sensorsim_increment(&(p_simulator->_cb.sensorsim_s_state),
                             &(p_simulator->_cb.sensorsim_s_cfg));
        // Cadence
         sensorsim_increment(&(p_simulator->_cb.sensorsim_c_state),
                             &(p_simulator->_cb.sensorsim_c_cfg));
    }
}


void ant_bsc_simulator_decrement(ant_bsc_simulator_t * p_simulator)
{
    if (!p_simulator->_cb.auto_change)
    {
        // Speed
         sensorsim_decrement(&(p_simulator->_cb.sensorsim_s_state),
                             &(p_simulator->_cb.sensorsim_s_cfg));
        // Cadence
         sensorsim_decrement(&(p_simulator->_cb.sensorsim_c_state),
                             &(p_simulator->_cb.sensorsim_c_cfg));
    }
}
