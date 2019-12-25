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
#ifndef ANT_SDM_SIMULATOR_LOCAL_H__
#define ANT_SDM_SIMULATOR_LOCAL_H__

#include <stdint.h>
#include <stdbool.h>
#include "ant_sdm.h"
#include "sensorsim.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup ant_sdk_sdm_simulator
 * @brief SDM simulator control block structure. */
typedef struct
{
    bool              auto_change;     ///< Cadence will change automatically (if auto_change is set) or manually.
    uint8_t           stride_length;   ///< Length of a stride (in cm).
    uint8_t           burn_rate;       ///< Kcal per kilometer.
    uint32_t          stride_incr;     ///< Fractional part of stride increment.
    uint64_t          time;            ///< Simulation time.
    sensorsim_state_t sensorsim_state; ///< State of the simulated sensor.
    sensorsim_cfg_t   sensorsim_cfg;   ///< Configuration of the simulated sensor.
}ant_sdm_simulator_cb_t;


#ifdef __cplusplus
}
#endif

#endif // ANT_SDM_SIMULATOR_LOCAL_H__
