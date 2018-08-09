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
#ifndef ANT_BPWR_UTILS_H__
#define ANT_BPWR_UTILS_H__

#include "app_util.h"
#include "nrf_assert.h"
#include "nrf.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @file
 *
 * @defgroup ant_sdk_profiles_bpwr_utils Bicycle Power profile utilities
 * @{
 * @ingroup ant_bpwr
 * @brief This module implements utilities for the Bicycle Power profile.
 *
 */

/*@brief A reversal of torque period unit.
 *
 * @details According to the ANT BPWR specification, the torque period unit is 1/2048 of a second.
 */
#define ANT_BPWR_TORQUE_PERIOD_UNIT_REVERSAL                2048
#define ANT_BPWR_TORQUE_PERIOD_DISP_PRECISION               1000
#define ANT_BPWR_TORQUE_PERIOD_RESCALE(VALUE)               value_rescale((VALUE), ANT_BPWR_TORQUE_PERIOD_UNIT_REVERSAL,  \
                                                                            ANT_BPWR_TORQUE_PERIOD_DISP_PRECISION)

/*@brief A reversal of accumulated torque unit.
 *
 * @details According to the ANT BPWR specification, the accumulated torque unit is 1/32 of a Nm.
 */
#define ANT_BPWR_ACC_TORQUE_UNIT_REVERSAL                   32
#define ANT_BPWR_ACC_TORQUE_DISP_PRECISION                  10
#define ANT_BPWR_ACC_TORQUE_RESCALE(VALUE)                  value_rescale((VALUE), ANT_BPWR_ACC_TORQUE_UNIT_REVERSAL,  \
                                                                            ANT_BPWR_ACC_TORQUE_DISP_PRECISION)

/** @} */


#ifdef __cplusplus
}
#endif

#endif // ANT_BPWR_UTILS_H__

