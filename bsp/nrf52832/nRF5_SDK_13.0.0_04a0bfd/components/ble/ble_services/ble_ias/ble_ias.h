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
 * @defgroup ble_ias Immediate Alert Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief Immediate Alert Service module.
 *
 * @details This module implements the Immediate Alert Service with the Alert Level characteristic.
 *          During initialization it adds the Immediate Alert Service and Alert Level characteristic
 *          to the BLE stack database.
 *
 *          The application must supply an event handler for receiving Immediate Alert Service
 *          events. Using this handler, the service will notify the application when the
 *          Alert Level characteristic value changes.
 *
 *          The service also provides a function for letting the application poll the current
 *          value of the Alert Level characteristic.
 *
 * @note The application must propagate BLE stack events to the Immediate Alert Service
 *       module by calling ble_ias_on_ble_evt() from the @ref softdevice_handler callback.
 *
 * @note Attention!
 *  To maintain compliance with Nordic Semiconductor ASA Bluetooth profile
 *  qualification listings, this section of source code must not be modified.
*/

#ifndef BLE_IAS_H__
#define BLE_IAS_H__

#include <stdint.h>
#include "ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Immediate Alert Service event type. */
typedef enum
{
    BLE_IAS_EVT_ALERT_LEVEL_UPDATED                     /**< Alert Level Updated event. */
} ble_ias_evt_type_t;

/**@brief Immediate Alert Service event. */
typedef struct
{
    ble_ias_evt_type_t evt_type;                        /**< Type of event. */
    union
    {
        uint8_t alert_level;                            /**< New Alert Level value. */
    } params;
} ble_ias_evt_t;

// Forward declaration of the ble_ias_t type.
typedef struct ble_ias_s ble_ias_t;

/**@brief Immediate Alert Service event handler type. */
typedef void (*ble_ias_evt_handler_t) (ble_ias_t * p_ias, ble_ias_evt_t * p_evt);

/**@brief Immediate Alert Service init structure. This contains all options and data needed for
 *        initialization of the service. */
typedef struct
{
    ble_ias_evt_handler_t evt_handler;                  /**< Event handler to be called for handling events in the Immediate Alert Service. */
} ble_ias_init_t;

/**@brief Immediate Alert Service structure. This contains various status information for the
 *        service. */
struct ble_ias_s
{
    ble_ias_evt_handler_t     evt_handler;              /**< Event handler to be called for handling events in the Immediate Alert Service. */
    uint16_t                  service_handle;           /**< Handle of Immediate Alert Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t  alert_level_handles;      /**< Handles related to the Alert Level characteristic. */
    uint16_t                  conn_handle;              /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
};

/**@brief Function for initializing the Immediate Alert Service.
 *
 * @param[out]  p_ias       Immediate Alert Service structure. This structure will have to be
 *                          supplied by the application. It will be initialized by this function,
 *                          and will later be used to identify this particular service instance.
 * @param[in]   p_ias_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_ias_init(ble_ias_t * p_ias, const ble_ias_init_t * p_ias_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Immediate Alert Service.
 *
 * @param[in]   p_ias      Immediate Alert Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_ias_on_ble_evt(ble_ias_t * p_ias, ble_evt_t * p_ble_evt);

/**@brief Function for getting current value of the Alert Level characteristic.
 *
 * @param[in]   p_ias          Immediate Alert Service structure.
 * @param[out]  p_alert_level  Current Alert Level value.
 */
uint32_t ble_ias_alert_level_get(ble_ias_t * p_ias, uint8_t * p_alert_level);


#ifdef __cplusplus
}
#endif

#endif // BLE_IAS_H__

/** @} */
