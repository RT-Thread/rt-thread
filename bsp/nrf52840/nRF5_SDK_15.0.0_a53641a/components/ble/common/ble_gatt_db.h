/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
/**@file
 *
 * @defgroup ble_sdk_lib_gatt_db GATT Database Service Structure
 * @{
 * @ingroup  ble_sdk_lib
 */

#ifndef BLE_GATT_DB_H__
#define BLE_GATT_DB_H__

#include <stdint.h>
#include "ble.h"
#include "ble_gattc.h"
#include "sdk_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BLE_GATT_DB_MAX_CHARS
#define BLE_GATT_DB_MAX_CHARS 6        /**< The maximum number of characteristics present in a service record. */
#endif // BLE_GATT_DB_MAX_CHARS

/**@brief Structure for holding the characteristic and the handle of its CCCD present on a server.
 */
typedef struct
{
    ble_gattc_char_t characteristic;    /**< Structure containing information about the characteristic. */
    uint16_t         cccd_handle;       /**< CCCD Handle value for this characteristic. This will be set to BLE_GATT_HANDLE_INVALID if a CCCD is not present at the server. */
    uint16_t         ext_prop_handle;   /**< Extended Properties Handle value for this characteristic. This will be set to BLE_GATT_HANDLE_INVALID if an Extended Properties descriptor is not present at the server. */
    uint16_t         user_desc_handle;  /**< User Description Handle value for this characteristic. This will be set to BLE_GATT_HANDLE_INVALID if a User Description descriptor is not present at the server. */
    uint16_t         report_ref_handle; /**< Report Reference Handle value for this characteristic. This will be set to BLE_GATT_HANDLE_INVALID if a Report Reference descriptor is not present at the server. */
} ble_gatt_db_char_t;

/**@brief Structure for holding information about the service and the characteristics present on a
 *        server.
 */
typedef struct
{
    ble_uuid_t               srv_uuid;                                  /**< UUID of the service. */
    uint8_t                  char_count;                                /**< Number of characteristics present in the service. */
    ble_gattc_handle_range_t handle_range;                              /**< Service Handle Range. */
    ble_gatt_db_char_t       charateristics[BLE_GATT_DB_MAX_CHARS];     /**< Array of information related to the characteristics present in the service. This list can extend further than one. */
} ble_gatt_db_srv_t;


#ifdef __cplusplus
}
#endif

#endif /* BLE_GATT_DB_H__ */

/** @} */
