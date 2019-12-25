/**
 * Copyright (c) 2012 - 2019, Nordic Semiconductor ASA
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
/* Attention!
*  To maintain compliance with Nordic Semiconductor ASA’s Bluetooth profile
*  qualification listings, this section of source code must not be modified.
*/

#ifndef BLE_SENSOR_LOCATION_H__
#define BLE_SENSOR_LOCATION_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BLE_SENSOR_LOCATION_OTHER        = 0 ,  /**<-- Other        */
    BLE_SENSOR_LOCATION_TOP_OF_SHOE  = 1 ,  /**<-- Top of shoe  */
    BLE_SENSOR_LOCATION_IN_SHOE      = 2 ,  /**<-- In shoe      */
    BLE_SENSOR_LOCATION_HIP          = 3 ,  /**<-- Hip          */
    BLE_SENSOR_LOCATION_FRONT_WHEEL  = 4 ,  /**<-- Front Wheel  */
    BLE_SENSOR_LOCATION_LEFT_CRANK   = 5 ,  /**<-- Left Crank   */
    BLE_SENSOR_LOCATION_RIGHT_CRANK  = 6 ,  /**<-- Right Crank  */
    BLE_SENSOR_LOCATION_LEFT_PEDAL   = 7 ,  /**<-- Left Pedal   */
    BLE_SENSOR_LOCATION_RIGHT_PEDAL  = 8 ,  /**<-- Right Pedal  */
    BLE_SENSOR_LOCATION_FRONT_HUB    = 9 ,  /**<-- Front Hub    */
    BLE_SENSOR_LOCATION_REAR_DROPOUT = 10,  /**<-- Rear Dropout */
    BLE_SENSOR_LOCATION_CHAINSTAY    = 11,  /**<-- Chainstay    */
    BLE_SENSOR_LOCATION_REAR_WHEEL   = 12,  /**<-- Rear Wheel   */
    BLE_SENSOR_LOCATION_REAR_HUB     = 13,  /**<-- Rear Hub     */
}ble_sensor_location_t;

#define BLE_NB_MAX_SENSOR_LOCATIONS 14


#ifdef __cplusplus
}
#endif

#endif // BLE_SENSOR_LOCATION_H__
