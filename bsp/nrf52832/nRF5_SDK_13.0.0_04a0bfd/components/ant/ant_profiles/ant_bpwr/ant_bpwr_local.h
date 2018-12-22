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
#ifndef ANT_BPWR_LOCAL_H__
#define ANT_BPWR_LOCAL_H__

#include <stdint.h>
#include <stdbool.h>
#include "ant_bpwr.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup ant_bpwr
 * @{
 */

/** @brief Bicycle Power Sensor control block. */
typedef struct
{
    uint8_t           message_counter;
    ant_bpwr_torque_t torque_use;
    enum
    {
        BPWR_SENS_CALIB_NONE,      ///< Idle state.
        BPWR_SENS_CALIB_REQUESTED, ///< Received request for general calibration result message by the sensor.
        BPWR_SENS_CALIB_READY,     ///< Calibration response message is ready to be transmitted.
    }                        calib_stat;
    ant_bpwr_calib_handler_t calib_handler;
} ant_bpwr_sens_cb_t;

/**@brief Bicycle Power Sensor RX control block. */
typedef struct
{
    uint8_t calib_timeout;
    enum
    {
        BPWR_DISP_CALIB_NONE,      ///< Idle state.
        BPWR_DISP_CALIB_REQUESTED, ///< Calibration requested.
    } calib_stat;
} ant_bpwr_disp_cb_t;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // ANT_BPWR_LOCAL_H__
