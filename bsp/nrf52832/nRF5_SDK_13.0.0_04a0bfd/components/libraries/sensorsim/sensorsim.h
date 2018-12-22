/**
 * Copyright (c) 2012 - 2017, Nordic Semiconductor ASA
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
/** @file
 *
 * @defgroup ble_sdk_lib_sensorsim Sensor Data Simulator
 * @{
 * @ingroup ble_sdk_lib
 * @brief Functions for simulating sensor data.
 *
 * @details Currently only a triangular waveform simulator is implemented.
 */

#ifndef SENSORSIM_H__
#define SENSORSIM_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Triangular waveform sensor simulator configuration. */
typedef struct
{
    uint32_t min;                       /**< Minimum simulated value. */
    uint32_t max;                       /**< Maximum simulated value. */
    uint32_t incr;                      /**< Increment between each measurement. */
    bool     start_at_max;              /**< TRUE is measurement is to start at the maximum value, FALSE if it is to start at the minimum. */
} sensorsim_cfg_t;

/**@brief Triangular waveform sensor simulator state. */
typedef struct
{
    uint32_t current_val;               /**< Current sensor value. */
    bool     is_increasing;             /**< TRUE if the simulator is in increasing state, FALSE otherwise. */
} sensorsim_state_t;

/**@brief Function for initializing a triangular waveform sensor simulator.
 *
 * @param[out]  p_state  Current state of simulator.
 * @param[in]   p_cfg    Simulator configuration.
 */
void sensorsim_init(sensorsim_state_t *     p_state,
                        const sensorsim_cfg_t * p_cfg);

/**@brief Function for generating a simulated sensor measurement using a triangular waveform generator.
 *
 * @param[in,out]  p_state  Current state of simulator.
 * @param[in]      p_cfg    Simulator configuration.
 *
 * @return         Simulator output.
 */
uint32_t sensorsim_measure(sensorsim_state_t *     p_state,
                               const sensorsim_cfg_t * p_cfg);

/**@brief Function for incrementing a simulated sensor measurement value.
 *
 * @param[in,out]  p_state  Current state of simulator.
 * @param[in]      p_cfg    Simulator configuration.
 *
 * @return         Simulator output.
 */
void sensorsim_increment(sensorsim_state_t *     p_state,
                         const sensorsim_cfg_t * p_cfg);

/**@brief Function for decrementing a simulated sensor measurement value.
 *
 * @param[in,out]  p_state  Current state of simulator.
 * @param[in]      p_cfg    Simulator configuration.
 *
 * @return         Simulator output.
 */
void sensorsim_decrement(sensorsim_state_t *     p_state,
                         const sensorsim_cfg_t * p_cfg);


#ifdef __cplusplus
}
#endif

#endif // SENSORSIM_H__

/** @} */
