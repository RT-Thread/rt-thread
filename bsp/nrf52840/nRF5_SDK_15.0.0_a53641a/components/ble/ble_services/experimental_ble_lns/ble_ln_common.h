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
/** @file
 *
 * @defgroup ble_sdk_srv_ln_common Location and Navigation common defines
 * @{
 * @ingroup ble_sdk_srv
 * @brief Location and Navigation common defines
 *
 * @details This module contains define values common to LNS and LNCP
 */

#ifndef BLE_LNS_COMMON_H__
#define BLE_LNS_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_LNS_INVALID_ROUTE                                       0xFFFF
#define BLE_LNS_NO_FIX                                              0xFF

#define BLE_LNS_MAX_NUM_ROUTES                                      10                              /**< The maximum number of routes. This affects memory usage only. */
#define BLE_LNS_MAX_ROUTE_NAME_LEN                                  BLE_GATT_ATT_MTU_DEFAULT - 5    /**< The maximum length of length of a route name. */
#define MAX_CTRL_POINT_RESP_PARAM_LEN                               BLE_LNS_MAX_ROUTE_NAME_LEN + 3  /**< Maximum length of a control point response. */

// Location and Navigation Service feature bits
#define BLE_LNS_FEATURE_INSTANT_SPEED_SUPPORTED                     (0x01 << 0)             /**< Instaneous Speed Supported bit. */
#define BLE_LNS_FEATURE_TOTAL_DISTANCE_SUPPORTED                    (0x01 << 1)             /**< Total Distance Supported bit. */
#define BLE_LNS_FEATURE_LOCATION_SUPPORTED                          (0x01 << 2)             /**< Location Supported bit. */
#define BLE_LNS_FEATURE_ELEVATION_SUPPORTED                         (0x01 << 3)             /**< Elevation Supported bit. */
#define BLE_LNS_FEATURE_HEADING_SUPPORTED                           (0x01 << 4)             /**< Heading Supported bit. */
#define BLE_LNS_FEATURE_ROLLING_TIME_SUPPORTED                      (0x01 << 5)             /**< Rolling Time Supported bit. */
#define BLE_LNS_FEATURE_UTC_TIME_SUPPORTED                          (0x01 << 6)             /**< UTC Time Supported bit. */
#define BLE_LNS_FEATURE_REMAINING_DISTANCE_SUPPORTED                (0x01 << 7)             /**< Remaining Distance Supported bit. */
#define BLE_LNS_FEATURE_REMAINING_VERT_DISTANCE_SUPPORTED           (0x01 << 8)             /**< Remaining Vertical Distance Supported bit. */
#define BLE_LNS_FEATURE_EST_TIME_OF_ARRIVAL_SUPPORTED               (0x01 << 9)             /**< Estimated Time of Arrival Supported bit. */
#define BLE_LNS_FEATURE_NUM_SATS_IN_SOLUTION_SUPPORTED              (0x01 << 10)            /**< Number of Satellites in Solution Supported bit. */
#define BLE_LNS_FEATURE_NUM_SATS_IN_VIEW_SUPPORTED                  (0x01 << 11)            /**< Number of Satellites in View Supported bit. */
#define BLE_LNS_FEATURE_TIME_TO_FIRST_FIX_SUPPORTED                 (0x01 << 12)            /**< Time to First Fix Supported bit. */
#define BLE_LNS_FEATURE_EST_HORZ_POS_ERROR_SUPPORTED                (0x01 << 13)            /**< Estimated Horizontal Position Error Supported bit. */
#define BLE_LNS_FEATURE_EST_VERT_POS_ERROR_SUPPORTED                (0x01 << 14)            /**< Estimated Vertical Position Error Supported bit. */
#define BLE_LNS_FEATURE_HORZ_DILUTION_OF_PRECISION_SUPPORTED        (0x01 << 15)            /**< Horizontal Dilution of Precision Supported bit. */
#define BLE_LNS_FEATURE_VERT_DILUTION_OF_PRECISION_SUPPORTED        (0x01 << 16)            /**< Vertical Dilution of Precision Supported bit. */
#define BLE_LNS_FEATURE_LOC_AND_SPEED_CONTENT_MASKING_SUPPORTED     (0x01 << 17)            /**< Location and Speed Characteristic Content Masking Supported bit. */
#define BLE_LNS_FEATURE_FIX_RATE_SETTING_SUPPORTED                  (0x01 << 18)            /**< Fix Rate Setting Supported bit. */
#define BLE_LNS_FEATURE_ELEVATION_SETTING_SUPPORTED                 (0x01 << 19)            /**< Elevation Setting Supported bit. */
#define BLE_LNS_FEATURE_POSITION_STATUS_SUPPORTED                   (0x01 << 20)            /**< Position Status Supported bit. */


#ifdef __cplusplus
}
#endif

#endif /* BLE_LNS_COMMON_H__ */

/** @} */
