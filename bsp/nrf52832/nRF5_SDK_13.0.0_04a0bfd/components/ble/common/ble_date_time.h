/**
 * Copyright (c) 2011 - 2017, Nordic Semiconductor ASA
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

/** @file
 * @brief Contains definition of ble_date_time structure.
 */

/** @file
 *
 * @defgroup ble_sdk_srv_date_time BLE Date Time characteristic type
 * @{
 * @ingroup ble_sdk_lib
 * @brief Definition of ble_date_time_t type.
 */

#ifndef BLE_DATE_TIME_H__
#define BLE_DATE_TIME_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Date and Time structure. */
typedef struct
{
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    uint8_t  hours;
    uint8_t  minutes;
    uint8_t  seconds;
} ble_date_time_t;

static __INLINE uint8_t ble_date_time_encode(const ble_date_time_t * p_date_time,
                                             uint8_t *               p_encoded_data)
{
    uint8_t len = uint16_encode(p_date_time->year, p_encoded_data);

    p_encoded_data[len++] = p_date_time->month;
    p_encoded_data[len++] = p_date_time->day;
    p_encoded_data[len++] = p_date_time->hours;
    p_encoded_data[len++] = p_date_time->minutes;
    p_encoded_data[len++] = p_date_time->seconds;

    return len;
}

static __INLINE uint8_t ble_date_time_decode(ble_date_time_t * p_date_time,
                                             const uint8_t *   p_encoded_data)
{
    uint8_t len = sizeof(uint16_t);

    p_date_time->year    = uint16_decode(p_encoded_data);
    p_date_time->month   = p_encoded_data[len++];
    p_date_time->day     = p_encoded_data[len++];
    p_date_time->hours   = p_encoded_data[len++];
    p_date_time->minutes = p_encoded_data[len++];
    p_date_time->seconds = p_encoded_data[len++];

    return len;
}


#ifdef __cplusplus
}
#endif

#endif // BLE_DATE_TIME_H__

/** @} */
