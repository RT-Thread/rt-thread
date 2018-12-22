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
#ifndef ANT_HRM_UTILS_H__
#define ANT_HRM_UTILS_H__

#include "app_util.h"
#include "nrf_assert.h"
#include "nrf.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @file
 *
 * @defgroup ant_sdk_profiles_hrm_utils Heart Rate Monitor profile utilities
 * @{
 * @ingroup ant_hrm
 * @brief This module implements utilities for the Heart Rate Monitor profile.
 *
 */

/**@brief Unit for HRM operating time.
 *
 * @details According to the ANT HRM specification, the operating time unit is 2 seconds.
 */
#define ANT_HRM_OPERATING_TIME_UNIT                 2u

/**@brief This macro should be used to get the seconds part of the operating time.
 */
#define ANT_HRM_OPERATING_SECONDS(OPERATING_TIME)   (((OPERATING_TIME) * ANT_HRM_OPERATING_TIME_UNIT) % 60)

/**@brief This macro should be used to get the minutes part of the operating time.
 */
#define ANT_HRM_OPERATING_MINUTES(OPERATING_TIME)   ((((OPERATING_TIME) * ANT_HRM_OPERATING_TIME_UNIT) / 60) % 60)

/**@brief This macro should be used to get the hours part of the operating time.
 */
#define ANT_HRM_OPERATING_HOURS(OPERATING_TIME)     ((((OPERATING_TIME) * ANT_HRM_OPERATING_TIME_UNIT) / (60 * 60)) % 24)

/**@brief This macro should be used to get the days part of the operating time.
 */
#define ANT_HRM_OPERATING_DAYS(OPERATING_TIME)      ((((OPERATING_TIME) * ANT_HRM_OPERATING_TIME_UNIT) / (60 * 60)) / 24)

/**@brief Number of HRM beat time counts per second.
 *
 * @details According to the ANT HRM specification, the beat time unit is 1/1024 of a second.
 */
#define ANT_HRM_BEAT_TIME_COUNTS_PER_SEC            1024u

/**@brief Beat time display required precision.
 *
 * @details This value is used to decode the number of milliseconds.
 */
#define ANT_HRM_BEAT_TIME_PRECISION                 1000u

/**@brief This macro should be used to get the seconds part of the HRM beat time.
 */
#define ANT_HRM_BEAT_TIME_SEC(BEAT_TIME)            ((BEAT_TIME) / ANT_HRM_BEAT_TIME_COUNTS_PER_SEC)

/**@brief This macro should be used to get the milliseconds part of the HRM beat time.
 */
#define ANT_HRM_BEAT_TIME_MSEC(BEAT_TIME)           (((((BEAT_TIME) % ANT_HRM_BEAT_TIME_COUNTS_PER_SEC) * ANT_HRM_BEAT_TIME_PRECISION)   \
                                                    + (ANT_HRM_BEAT_TIME_COUNTS_PER_SEC / 2))                                          \
                                                    / ANT_HRM_BEAT_TIME_COUNTS_PER_SEC)
/** @} */


#ifdef __cplusplus
}
#endif

#endif // ANT_HRM_UTILS_H__

