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
#ifndef ANT_SDM_UTILS_H__
#define ANT_SDM_UTILS_H__

#include "nrf_assert.h"
#include "nrf.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @file
 *
 * @defgroup ant_sdk_profiles_sdm_utils Stride Based Speed and Distance Monitor profile utilities
 * @{
 * @ingroup ant_sdm
 * @brief This module implements utilities for the Stride Based Speed and Distance Monitor profile.
 *
 */

/*@brief A reversal of time unit.
 *
 * @details According to the ANT SDM specification, the time unit (fractional part) is 1/200 of a second.
 */
#define ANT_SDM_TIME_UNIT_REVERSAL              200
#define ANT_SDM_TIME_DISP_PRECISION             1000
#define ANT_SDM_TIME_RESCALE(VALUE)             value_rescale((VALUE), ANT_SDM_TIME_UNIT_REVERSAL,  \
                                                                 ANT_SDM_TIME_DISP_PRECISION)

/*@brief A reversal of distance unit.
 *
 * @details According to the ANT SDM specification, the distance unit (page 1 - fractional part) is 1/16 of a meter.
 */
#define ANT_SDM_DISTANCE_UNIT_REVERSAL          16
#define ANT_SDM_DISTANCE_DISP_PRECISION         10
#define ANT_SDM_DISTANCE_RESCALE(VALUE)         value_rescale((VALUE), ANT_SDM_DISTANCE_UNIT_REVERSAL,  \
                                                                 ANT_SDM_DISTANCE_DISP_PRECISION)

/*@brief A reversal of speed unit.
 *
 * @details According to the ANT SDM specification, the speed unit (fractional part) is 1/256 of m/s.
 */
#define ANT_SDM_SPEED_UNIT_REVERSAL             256
#define ANT_SDM_SPEED_DISP_PRECISION            100
#define ANT_SDM_SPEED_RESCALE(VALUE)            value_rescale((VALUE), ANT_SDM_SPEED_UNIT_REVERSAL,  \
                                                                 ANT_SDM_SPEED_DISP_PRECISION)

/*@brief A reversal of update latency unit.
 *
 * @details According to the ANT SDM specification, the update latency unit (fractional part) is 1/32 of a second.
 */
#define ANT_SDM_UPDATE_LATENCY_UNIT_REVERSAL    32
#define ANT_SDM_UPDATE_LATENCY_DISP_PRECISION   1000
#define ANT_SDM_UPDATE_LATENCY_RESCALE(VALUE)   value_rescale((VALUE), ANT_SDM_UPDATE_LATENCY_UNIT_REVERSAL,  \
                                                                 ANT_SDM_UPDATE_LATENCY_DISP_PRECISION)

/*@brief A reversal of cadence unit.
 *
 * @details According to the ANT SDM specification, the cadence unit (fractional part) is 1/16 of strides/minute.
 */
#define ANT_SDM_CADENCE_UNIT_REVERSAL           16
#define ANT_SDM_CADENCE_DISP_PRECISION          10
#define ANT_SDM_CADENCE_RESCALE(VALUE)          value_rescale((VALUE), ANT_SDM_CADENCE_UNIT_REVERSAL,  \
                                                                 ANT_SDM_CADENCE_DISP_PRECISION)

/** @} */


#ifdef __cplusplus
}
#endif

#endif // ANT_SDM_UTILS_H__

