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
#ifndef ANT_BSC_SIMULATOR_LOCAL_H__
#define ANT_BSC_SIMULATOR_LOCAL_H__

#include <stdint.h>
#include <stdbool.h>
#include "ant_bsc.h"
#include "sensorsim.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@brief BSC simulator control block structure. */
typedef struct
{
    uint8_t             device_type;
    bool                auto_change;                ///< Cadence will change automatically (if auto_change is set) or manually.
    uint16_t            speed_sim_val;              ///< Instantaneous speed value.
    uint16_t            cadence_sim_val;            ///< Instantaneous cadence value.
    uint32_t            time_since_last_s_evt;      ///< Time since last speed event occurred (integer part).
    uint64_t            fraction_since_last_s_evt;  ///< Time since last speed event occurred (fractional part).
    uint32_t            time_since_last_c_evt;      ///< Time since last cadence event occurred (integer part).
    uint64_t            fraction_since_last_c_evt;  ///< Time since last cadence event occurred (fractional part).
    sensorsim_state_t   sensorsim_s_state;          ///< State of the simulated speed sensor.
    sensorsim_cfg_t     sensorsim_s_cfg;            ///< Configuration of the simulated speed sensor.
    sensorsim_state_t   sensorsim_c_state;          ///< State of the simulated cadence sensor.
    sensorsim_cfg_t     sensorsim_c_cfg;            ///< Configuration of the simulated cadence sensor.
    uint16_t            prev_time_since_evt;        ///< Previous value of time since the last event.
    uint32_t            cumulative_time;            ///< Cumulative time in 2 s ticks used for updating the cumulative time.
    uint32_t            cumulative_time_frac;       ///< Cumulative time in 2 s ticks (fractional part), used for updating the cumulative time.
    uint8_t             stop_cnt;                   ///< Counter used for simulating bicycle stopped state.
} ant_bsc_simulator_cb_t;


#ifdef __cplusplus
}
#endif

#endif // ANT_BSC_SIMULATOR_LOCAL_H__
